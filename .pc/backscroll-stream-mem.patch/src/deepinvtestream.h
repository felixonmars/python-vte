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

#ifndef deepinvtestream_h_included
#define deepinvtestream_h_included

#include <glib-object.h>
#include <gio/gio.h>

G_BEGIN_DECLS

typedef struct _DeepinvteStream DeepinvteStream;

void _deepinvte_stream_reset (DeepinvteStream *stream, gsize offset);
gsize _deepinvte_stream_append (DeepinvteStream *stream, const char *data, gsize len);
gboolean _deepinvte_stream_read (DeepinvteStream *stream, gsize offset, char *data, gsize len);
void _deepinvte_stream_truncate (DeepinvteStream *stream, gsize offset);
void _deepinvte_stream_new_page (DeepinvteStream *stream);
gsize _deepinvte_stream_head (DeepinvteStream *stream);
gboolean _deepinvte_stream_write_contents (DeepinvteStream *stream, GOutputStream *output,
				     gsize start_offset,
				     GCancellable *cancellable, GError **error);


/* Various streams */

DeepinvteStream *
_deepinvte_file_stream_new (void);

G_END_DECLS

#endif
