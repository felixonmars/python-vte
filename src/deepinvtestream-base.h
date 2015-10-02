/*
 * Copyright (C) 2009,2010 Red Hat, Inc.
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
 */

#include <glib-object.h>
#include <gio/gio.h>

/*
 * DeepinvteStream: Abstract base stream class
 */

struct _DeepinvteStream {
	GObject parent;
};

typedef struct _DeepinvteStreamClass {
	GObjectClass parent_class;

	void (*reset) (DeepinvteStream *stream, gsize offset);
	gsize (*append) (DeepinvteStream *stream, const char *data, gsize len);
	gboolean (*read) (DeepinvteStream *stream, gsize offset, char *data, gsize len);
	void (*truncate) (DeepinvteStream *stream, gsize offset);
	void (*new_page) (DeepinvteStream *stream);
	gsize (*head) (DeepinvteStream *stream);
	gboolean (*write_contents) (DeepinvteStream *stream, GOutputStream *output,
				    gsize start_offset,
				    GCancellable *cancellable, GError **error);
} DeepinvteStreamClass;

static GType _deepinvte_stream_get_type (void);
#define DEEPINVTE_TYPE_STREAM _deepinvte_stream_get_type ()
#define DEEPINVTE_STREAM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), DEEPINVTE_TYPE_STREAM, DeepinvteStreamClass))

G_DEFINE_ABSTRACT_TYPE (DeepinvteStream, _deepinvte_stream, G_TYPE_OBJECT)

static void
_deepinvte_stream_class_init (DeepinvteStreamClass *klass G_GNUC_UNUSED)
{
}

static void
_deepinvte_stream_init (DeepinvteStream *stream G_GNUC_UNUSED)
{
}

void
_deepinvte_stream_reset (DeepinvteStream *stream, gsize offset)
{
	DEEPINVTE_STREAM_GET_CLASS (stream)->reset (stream, offset);
}

gsize
_deepinvte_stream_append (DeepinvteStream *stream, const char *data, gsize len)
{
	return DEEPINVTE_STREAM_GET_CLASS (stream)->append (stream, data, len);
}

gboolean
_deepinvte_stream_read (DeepinvteStream *stream, gsize offset, char *data, gsize len)
{
	return DEEPINVTE_STREAM_GET_CLASS (stream)->read (stream, offset, data, len);
}

void
_deepinvte_stream_truncate (DeepinvteStream *stream, gsize offset)
{
	DEEPINVTE_STREAM_GET_CLASS (stream)->truncate (stream, offset);
}

void
_deepinvte_stream_new_page (DeepinvteStream *stream)
{
	DEEPINVTE_STREAM_GET_CLASS (stream)->new_page (stream);
}

gsize
_deepinvte_stream_head (DeepinvteStream *stream)
{
	return DEEPINVTE_STREAM_GET_CLASS (stream)->head (stream);
}

gboolean
_deepinvte_stream_write_contents (DeepinvteStream *stream, GOutputStream *output,
			    gsize start_offset,
			    GCancellable *cancellable, GError **error)
{
	return DEEPINVTE_STREAM_GET_CLASS (stream)->write_contents (stream, output,
							      start_offset,
							      cancellable, error);
}
