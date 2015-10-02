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

#ifndef deepinvte_deepinvtebg_included
#define deepinvte_deepinvtebg_included

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define DEEPINVTE_TYPE_BG            (deepinvte_bg_get_type())
#define DEEPINVTE_BG(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), DEEPINVTE_TYPE_BG, DeepinvteBg))
#define DEEPINVTE_BG_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  DEEPINVTE_TYPE_BG, DeepinvteBgClass))
#define DEEPINVTE_IS_BG(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), DEEPINVTE_TYPE_BG))
#define DEEPINVTE_IS_BG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  DEEPINVTE_TYPE_BG))
#define DEEPINVTE_BG_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  DEEPINVTE_TYPE_BG, DeepinvteBgClass))

typedef struct _DeepinvteBg         DeepinvteBg;
typedef struct _DeepinvteBgPrivate  DeepinvteBgPrivate;
typedef struct _DeepinvteBgClass    DeepinvteBgClass;

struct _DeepinvteBg {
	GObject parent;

        /*< private >*/
	DeepinvteBgPrivate *pvt;
};

struct _DeepinvteBgClass {
	GObjectClass parent_class;
};

GType deepinvte_bg_get_type(void);

DeepinvteBg *deepinvte_bg_get_for_screen(GdkScreen *screen);

typedef enum {
	DEEPINVTE_BG_SOURCE_NONE,
	DEEPINVTE_BG_SOURCE_ROOT,
	DEEPINVTE_BG_SOURCE_PIXBUF,
	DEEPINVTE_BG_SOURCE_FILE
} DeepinvteBgSourceType;

cairo_surface_t *
deepinvte_bg_get_surface(DeepinvteBg *bg,
		   DeepinvteBgSourceType source_type,
		   GdkPixbuf *source_pixbuf,
		   const char *source_file,
		   const PangoColor *tint,
		   double saturation,
		   cairo_surface_t *other);

G_END_DECLS

#endif
