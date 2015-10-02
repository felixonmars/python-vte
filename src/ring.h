/*
 * Copyright (C) 2002,2009,2010 Red Hat, Inc.
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

/* The interfaces in this file are subject to change at any time. */

#ifndef deepinvte_ring_h_included
#define deepinvte_ring_h_included

#include <gio/gio.h>
#include "deepinvte.h"

#include "deepinvterowdata.h"
#include "deepinvtestream.h"

G_BEGIN_DECLS


typedef struct _DeepinvteCellAttrChange {
	gsize text_offset;
	DeepinvteIntCellAttr attr;
} DeepinvteCellAttrChange;


/*
 * DeepinvteRing: A scrollback buffer ring
 */

typedef struct _DeepinvteRing DeepinvteRing;
struct _DeepinvteRing {
	gulong max;

	gulong start, end;

	/* Writable */
	gulong writable, mask;
	DeepinvteRowData *array;

	/* Storage */
	gulong last_page;
	DeepinvteStream *attr_stream, *text_stream, *row_stream;
	DeepinvteCellAttrChange last_attr;
	GString *utf8_buffer;

	DeepinvteRowData cached_row;
	gulong cached_row_num;

};

#define _deepinvte_ring_contains(__ring, __position) \
	(((gulong) (__position) >= (__ring)->start) && \
	 ((gulong) (__position) < (__ring)->end))
#define _deepinvte_ring_delta(__ring) ((glong) (__ring)->start)
#define _deepinvte_ring_length(__ring) ((glong) ((__ring)->end - (__ring)->start))
#define _deepinvte_ring_next(__ring) ((glong) (__ring)->end)

const DeepinvteRowData *_deepinvte_ring_index (DeepinvteRing *ring, gulong position);
DeepinvteRowData *_deepinvte_ring_index_writable (DeepinvteRing *ring, gulong position);

void _deepinvte_ring_init (DeepinvteRing *ring, gulong max_rows);
void _deepinvte_ring_fini (DeepinvteRing *ring);
void _deepinvte_ring_resize (DeepinvteRing *ring, gulong max_rows);
void _deepinvte_ring_shrink (DeepinvteRing *ring, gulong max_len);
DeepinvteRowData *_deepinvte_ring_insert (DeepinvteRing *ring, gulong position);
DeepinvteRowData *_deepinvte_ring_append (DeepinvteRing *ring);
void _deepinvte_ring_remove (DeepinvteRing *ring, gulong position);
gboolean _deepinvte_ring_write_contents (DeepinvteRing *ring,
				   GOutputStream *stream,
				   DeepinvteTerminalWriteFlags flags,
				   GCancellable *cancellable,
				   GError **error);

G_END_DECLS

#endif
