/*
 * Copyright (C) 2002 Red Hat, Inc.
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
 */

/* The interfaces in this file are subject to change at any time. */

#ifndef deepinvterowdata_h_included
#define deepinvterowdata_h_included

#include "deepinvteunistr.h"

G_BEGIN_DECLS


#define DEEPINVTE_DEF_FG			256
#define DEEPINVTE_DEF_BG			257
#define DEEPINVTE_BOLD_FG			258
#define DEEPINVTE_DIM_FG			259
#define DEEPINVTE_DEF_HL                      260
#define DEEPINVTE_CUR_BG			261
#define DEEPINVTE_PALETTE_SIZE		262


/*
 * DeepinvteCellAttr: A single cell style attributes
 *
 * Ordered by most commonly changed attributes, to
 * optimize the compact representation.
 */

typedef struct _DeepinvteCellAttr {
	guint32 fragment: 1;	/* A continuation cell. */
	guint32 columns: 4;	/* Number of visible columns
				   (as determined by g_unicode_iswide(c)).
				   Also abused for tabs; bug 353610
				   Keep at least 4 for tabs to work
				   */
	guint32 bold: 1;
	guint32 fore: 9;	/* Index into color palette */
	guint32 back: 9;	/* Index into color palette. */

	guint32 standout: 1;
	guint32 underline: 1;
	guint32 strikethrough: 1;

	guint32 reverse: 1;
	guint32 blink: 1;
	guint32 half: 1;

	guint32 invisible: 1;
	/* unused; bug 499893
	guint32 protect: 1;
	 */

	/* 30 bits */
} DeepinvteCellAttr;
G_STATIC_ASSERT (sizeof (DeepinvteCellAttr) == 4);

typedef union _DeepinvteIntCellAttr {
	DeepinvteCellAttr s;
	guint32 i;
} DeepinvteIntCellAttr;
G_STATIC_ASSERT (sizeof (DeepinvteCellAttr) == sizeof (DeepinvteIntCellAttr));

/*
 * DeepinvteCell: A single cell's data
 */

typedef struct _DeepinvteCell {
	deepinvteunistr c;
	DeepinvteCellAttr attr;
} DeepinvteCell;
G_STATIC_ASSERT (sizeof (DeepinvteCell) == 8);

typedef union _DeepinvteIntCell {
	DeepinvteCell cell;
	struct {
		guint32 c;
		guint32 attr;
	} i;
} DeepinvteIntCell;
G_STATIC_ASSERT (sizeof (DeepinvteCell) == sizeof (DeepinvteIntCell));

static const DeepinvteIntCell basic_cell = {
	{
		0,
		{
			0, /* fragment */
			1, /* columns */
			0, /* bold */
			DEEPINVTE_DEF_FG, /* fore */
			DEEPINVTE_DEF_BG, /* back */

			0, /* standout */
			0, /* underline */
			0, /* strikethrough */

			0, /* reverse */
			0, /* blink */
			0, /* half */

			0  /* invisible */
		}
	}
};


/*
 * DeepinvteRowAttr: A single row's attributes
 */

typedef struct _DeepinvteRowAttr {
	guint8 soft_wrapped: 1;
} DeepinvteRowAttr;
G_STATIC_ASSERT (sizeof (DeepinvteRowAttr) == 1);

/*
 * DeepinvteRowData: A single row's data
 */

typedef struct _DeepinvteRowData {
	DeepinvteCell *cells;
	guint16 len;
	DeepinvteRowAttr attr;
} DeepinvteRowData;


#define _deepinvte_row_data_length(__row)			((__row)->len + 0)

static inline const DeepinvteCell *
_deepinvte_row_data_get (const DeepinvteRowData *row, gulong col)
{
	if (G_UNLIKELY (row->len <= col))
		return NULL;

	return &row->cells[col];
}

static inline DeepinvteCell *
_deepinvte_row_data_get_writable (DeepinvteRowData *row, gulong col)
{
	if (G_UNLIKELY (row->len <= col))
		return NULL;

	return &row->cells[col];
}

void _deepinvte_row_data_init (DeepinvteRowData *row);
void _deepinvte_row_data_clear (DeepinvteRowData *row);
void _deepinvte_row_data_fini (DeepinvteRowData *row);
void _deepinvte_row_data_insert (DeepinvteRowData *row, gulong col, const DeepinvteCell *cell);
void _deepinvte_row_data_append (DeepinvteRowData *row, const DeepinvteCell *cell);
void _deepinvte_row_data_remove (DeepinvteRowData *row, gulong col);
void _deepinvte_row_data_fill (DeepinvteRowData *row, const DeepinvteCell *cell, gulong len);
void _deepinvte_row_data_shrink (DeepinvteRowData *row, gulong max_len);


G_END_DECLS

#endif
