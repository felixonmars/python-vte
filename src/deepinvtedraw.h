/*
 * Copyright (C) 2003 Red Hat, Inc.
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

#ifndef deepinvte_deepinvtedraw_h_included
#define deepinvte_deepinvtedraw_h_included


#include <glib.h>
#include <gtk/gtk.h>
#include "deepinvtebg.h"
#include "deepinvte.h"
#include "deepinvteunistr.h"
#include "deepinvte-gtk-compat.h"

G_BEGIN_DECLS

#define DEEPINVTE_DRAW_SINGLE_WIDE_CHARACTERS	\
					" !\"#$%&'()*+,-./" \
					"0123456789" \
					":;<=>?@" \
					"ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
					"[\\]^_`" \
					"abcdefghijklmnopqrstuvwxyz" \
					"{|}~" \
					""
#define DEEPINVTE_DRAW_DOUBLE_WIDE_CHARACTERS 0x4e00, 0x4e8c, 0x4e09, 0x56db, 0x4e94,\
					0xac00, 0xac01, 0xac04, 0xac08, 0xac10
/* For Pango, we have to use CJK Ideographs alone. Otherwise, 'width'
   returned by pango_layout would be screwed up for Chinese and Japanese
   fonts without Hangul */
#define DEEPINVTE_DRAW_DOUBLE_WIDE_IDEOGRAPHS 0x4e00, 0x4e8c, 0x4e09, 0x56db, 0x4e94
#define DEEPINVTE_DRAW_OPAQUE 0xff
#define DEEPINVTE_DRAW_MAX_LENGTH 1024

struct _deepinvte_draw;

/* A request to draw a particular character spanning a given number of columns
   at the given location.  Unlike most APIs, (x,y) specifies the top-left
   corner of the cell into which the character will be drawn instead of the
   left end of the baseline. */
struct _deepinvte_draw_text_request {
	deepinvteunistr c;
	gshort x, y, columns;
};

/* Create and destroy a draw structure. */
struct _deepinvte_draw *_deepinvte_draw_new(GtkWidget *widget);
void _deepinvte_draw_free(struct _deepinvte_draw *draw);

/* Begin and end a drawing operation.  If anything is buffered locally, it is
   flushed to the window system when _end() is called. */
void _deepinvte_draw_start(struct _deepinvte_draw *draw);
void _deepinvte_draw_end(struct _deepinvte_draw *draw);

void _deepinvte_draw_set_background_solid(struct _deepinvte_draw *draw,
				    double red,
				    double green,
				    double blue,
				    double opacity);
void _deepinvte_draw_set_background_image(struct _deepinvte_draw *draw,
				    DeepinvteBgSourceType type,
				    GdkPixbuf *pixbuf,
				    const char *file,
				    const PangoColor *color,
				    double saturation);
void _deepinvte_draw_set_background_scroll(struct _deepinvte_draw *draw,
				     gint x, gint y);

void _deepinvte_draw_clip(struct _deepinvte_draw *draw, GdkRegion *region);
void _deepinvte_draw_clear(struct _deepinvte_draw *draw,
		     gint x, gint y, gint width, gint height);

void _deepinvte_draw_set_text_font(struct _deepinvte_draw *draw,
			     const PangoFontDescription *fontdesc,
			     DeepinvteTerminalAntiAlias anti_alias);
void _deepinvte_draw_get_text_metrics(struct _deepinvte_draw *draw,
				gint *width, gint *height, gint *ascent);
int _deepinvte_draw_get_char_width(struct _deepinvte_draw *draw, deepinvteunistr c, int columns,
			     gboolean bold);

void _deepinvte_draw_text(struct _deepinvte_draw *draw,
		    struct _deepinvte_draw_text_request *requests, gsize n_requests,
		    const PangoColor *color, guchar alpha, gboolean);
gboolean _deepinvte_draw_char(struct _deepinvte_draw *draw,
			struct _deepinvte_draw_text_request *request,
			const PangoColor *color, guchar alpha, gboolean bold);
gboolean _deepinvte_draw_has_char(struct _deepinvte_draw *draw, deepinvteunistr c, gboolean bold);


void _deepinvte_draw_fill_rectangle(struct _deepinvte_draw *draw,
			      gint x, gint y, gint width, gint height,
			      const PangoColor *color, guchar alpha);
void _deepinvte_draw_draw_rectangle(struct _deepinvte_draw *draw,
			      gint x, gint y, gint width, gint height,
			      const PangoColor *color, guchar alpha);

G_END_DECLS

#endif
