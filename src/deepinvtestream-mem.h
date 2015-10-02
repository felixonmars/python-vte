/*
 * Copyright (C) 2009,2010 Red Hat, Inc.
 * Copyright (C) 2012 Kees Cook
 *
 * This is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Library General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * Red Hat Author(s): Behdad Esfahbod
 * Ubuntu Authors(s): Kees Cook <kees@ubuntu.com>
 */

#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <gio/gunixinputstream.h>

/*
 * DeepinvteMemStream: A memory-based stream
 */

struct mem_region {
	gchar * region;
	gsize allocated; /* How much memory exists in the region. */
	gsize length; /* Current length of valid written data in the region. */
	gsize seekpos; /* Where in the region we are positioned from seeking. */
};

typedef struct _DeepinvteMemStream {
	DeepinvteStream parent;

	/* The first is for the write head, second is for last page */
	struct mem_region page[2];
	gsize offset[2]; /* Offset into... ? */
} DeepinvteMemStream;

typedef DeepinvteStreamClass DeepinvteMemStreamClass;

static GType _deepinvte_mem_stream_get_type (void);
#define DEEPINVTE_TYPE_MEM_STREAM _deepinvte_mem_stream_get_type ()

G_DEFINE_TYPE (DeepinvteMemStream, _deepinvte_mem_stream, DEEPINVTE_TYPE_STREAM)

static void
_deepinvte_mem_stream_init (DeepinvteMemStream *stream G_GNUC_UNUSED)
{
}

DeepinvteStream *
_deepinvte_mem_stream_new (void)
{
	return (DeepinvteStream *) g_object_new (DEEPINVTE_TYPE_MEM_STREAM, NULL);
}

static void
_deepinvte_mem_stream_finalize (GObject *object)
{
	DeepinvteMemStream *stream = (DeepinvteMemStream *) object;
	gint i;

	for (i = 0; i < 2; i ++) {
		if (stream->page[i].region) g_free (stream->page[i].region);
		memset(&stream->page[i], 0, sizeof (stream->page[i]));
		stream->offset[i] = 0;
	}

	G_OBJECT_CLASS (_deepinvte_mem_stream_parent_class)->finalize(object);
}

static gsize
_mem_xseek (DeepinvteMemStream *stream, gint id, gsize pos, int whence)
{
	g_assert (id == 0 || id == 1);

	switch (whence) {
	case SEEK_SET:
		if (pos > stream->page[id].length)
			pos = stream->page[id].length;
		stream->page[id].seekpos = pos;
		break;
	case SEEK_END:
		stream->page[id].seekpos = stream->page[id].length;
		break;
	}
	return stream->page[id].seekpos;
}

static gsize
_mem_xread (DeepinvteMemStream *stream, gint id, char *data, gsize len)
{
	g_assert (id == 0 || id == 1);

	if (G_UNLIKELY (len && !stream->page[id].region))
		return 0;

	if (len > stream->page[id].length - stream->page[id].seekpos)
		len = stream->page[id].length - stream->page[id].seekpos;

	g_memmove (data, stream->page[id].region + stream->page[id].seekpos, len);
	stream->page[id].seekpos += len;

	return len;
}

static void
_mem_xwrite (DeepinvteMemStream *stream, gint id, const char *data, gsize len)
{
	g_assert (id == 0 || id == 1);

	if (G_UNLIKELY (!stream->page[id].region))
		return;

	while (stream->page[id].seekpos + len > stream->page[id].allocated) {
		gsize want = stream->page[id].allocated * 2;
		stream->page[id].region = g_realloc (stream->page[id].region, want);
		/* TODO: handle alloc failure. */
		stream->page[id].allocated = want;
	}

	g_memmove (stream->page[id].region + stream->page[id].seekpos, data, len);
	stream->page[id].seekpos += len;
	if (stream->page[id].seekpos > stream->page[id].length)
		stream->page[id].length = stream->page[id].seekpos;
}

static void
_mem_xtruncate (DeepinvteMemStream *stream, gint id, gsize size)
{
	g_assert (id == 0 || id == 1);

	if (G_UNLIKELY (!stream->page[id].region))
		return;

	/* This only expects the region to be reduced in size. */
	g_assert (size <= stream->page[id].length);

	stream->page[id].region = g_realloc(stream->page[id].region, size);
	/* TODO: handle alloc failure. */
	stream->page[id].length = stream->page[id].allocated = size;
	if (stream->page[id].seekpos > size)
		stream->page[id].seekpos = size;
}

static gboolean
_mem_xwrite_contents (DeepinvteMemStream *stream, gint id, GOutputStream *output,
		  GCancellable *cancellable, GError **error)
{
	gboolean ret;
	gsize written;

	g_assert (id == 0 || id == 1);

	if (G_UNLIKELY (!stream->page[id].region))
		return TRUE;

	ret = g_output_stream_write_all (output,
					 stream->page[id].region + stream->page[id].seekpos,
					 stream->page[id].length - stream->page[id].seekpos,
					 &written, cancellable, error);
	stream->page[id].seekpos = stream->page[id].length;

	return ret;
}

static void
_deepinvte_mem_stream_reset (DeepinvteStream *astream, gsize offset)
{
	DeepinvteMemStream *stream = (DeepinvteMemStream *) astream;

	if (stream->page[0].region) _mem_xtruncate (stream, 0, 0);
	if (stream->page[1].region) _mem_xtruncate (stream, 1, 0);

	stream->offset[0] = stream->offset[1] = offset;
}

static inline void
_deepinvte_mem_stream_ensure_region0 (DeepinvteMemStream *stream)
{
	if (G_LIKELY (stream->page[0].region))
		return;

	stream->page[0].allocated = 4096;	/* Arbitrary initial size. */
	stream->page[0].region = g_malloc(stream->page[0].allocated);
	/* TODO: how to handle malloc failure? */
}

static gsize
_deepinvte_mem_stream_append (DeepinvteStream *astream, const char *data, gsize len)
{
	DeepinvteMemStream *stream = (DeepinvteMemStream *) astream;
	gsize ret;

	_deepinvte_mem_stream_ensure_region0 (stream);

	ret = _mem_xseek (stream, 0, 0, SEEK_END);
	_mem_xwrite (stream, 0, data, len);

	return stream->offset[0] + ret;
}

static gboolean
_deepinvte_mem_stream_read (DeepinvteStream *astream, gsize offset, char *data, gsize len)
{
	DeepinvteMemStream *stream = (DeepinvteMemStream *) astream;
	gsize l;

	if (G_UNLIKELY (offset < stream->offset[1]))
		return FALSE;

	if (offset < stream->offset[0]) {
		_mem_xseek (stream, 1, offset - stream->offset[1], SEEK_SET);
		l = _mem_xread (stream, 1, data, len);
		offset += l; data += l; len -= l; if (!len) return TRUE;
	}

	_mem_xseek (stream, 0, offset - stream->offset[0], SEEK_SET);
	l = _mem_xread (stream, 0, data, len);
	offset += l; data += l; len -= l; if (!len) return TRUE;

	return FALSE;
}

static void
_deepinvte_mem_stream_swap_regions (DeepinvteMemStream *stream)
{
	struct mem_region temp;

	temp = stream->page[0];
	stream->page[0] = stream->page[1];
	stream->page[1] = temp;
}

static void
_deepinvte_mem_stream_truncate (DeepinvteStream *astream, gsize offset)
{
	DeepinvteMemStream *stream = (DeepinvteMemStream *) astream;

	if (G_UNLIKELY (offset < stream->offset[1])) {
		_mem_xtruncate (stream, 1, 0);
		stream->offset[1] = offset;
	}

	if (G_UNLIKELY (offset < stream->offset[0])) {
		_mem_xtruncate (stream, 0, 0);
		stream->offset[0] = stream->offset[1];
		_deepinvte_mem_stream_swap_regions (stream);
	} else {
		_mem_xtruncate (stream, 0, offset - stream->offset[0]);
	}
}

static void
_deepinvte_mem_stream_new_page (DeepinvteStream *astream)
{
	DeepinvteMemStream *stream = (DeepinvteMemStream *) astream;

	stream->offset[1] = stream->offset[0];
	if (stream->page[0].region)
		stream->offset[0] += _mem_xseek (stream, 0, 0, SEEK_END);
	_deepinvte_mem_stream_swap_regions (stream);
	_mem_xtruncate (stream, 0, 0);
}

static gsize
_deepinvte_mem_stream_head (DeepinvteStream *astream)
{
	DeepinvteMemStream *stream = (DeepinvteMemStream *) astream;

	if (stream->page[0].region)
		return stream->offset[0] + _mem_xseek (stream, 0, 0, SEEK_END);
	else
		return stream->offset[0];
}

static gboolean
_deepinvte_mem_stream_write_contents (DeepinvteStream *astream, GOutputStream *output,
				 gsize offset,
				 GCancellable *cancellable, GError **error)
{
	DeepinvteMemStream *stream = (DeepinvteMemStream *) astream;

	if (G_UNLIKELY (offset < stream->offset[1]))
		return FALSE;

	if (offset < stream->offset[0]) {
		_mem_xseek (stream, 1, offset - stream->offset[1], SEEK_SET);
		if (!_mem_xwrite_contents (stream, 1, output, cancellable, error))
			return FALSE;
		offset = stream->offset[0];
	}

	_mem_xseek (stream, 0, offset - stream->offset[0], SEEK_SET);
	return _mem_xwrite_contents (stream, 0, output, cancellable, error);
}

static void
_deepinvte_mem_stream_class_init (DeepinvteMemStreamClass *klass)
{
	GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

	gobject_class->finalize = _deepinvte_mem_stream_finalize;

	klass->reset = _deepinvte_mem_stream_reset;
	klass->append = _deepinvte_mem_stream_append;
	klass->read = _deepinvte_mem_stream_read;
	klass->truncate = _deepinvte_mem_stream_truncate;
	klass->new_page = _deepinvte_mem_stream_new_page;
	klass->head = _deepinvte_mem_stream_head;
	klass->write_contents = _deepinvte_mem_stream_write_contents;
}
