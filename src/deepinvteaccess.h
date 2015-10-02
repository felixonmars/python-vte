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

#ifndef deepinvte_deepinvteaccess_h_included
#define deepinvte_deepinvteaccess_h_included


#include <glib.h>
#include <gtk/gtk.h>
#include "deepinvte.h"

G_BEGIN_DECLS

#define DEEPINVTE_TYPE_TERMINAL_ACCESSIBLE            (deepinvte_terminal_accessible_get_type ())
#define DEEPINVTE_TERMINAL_ACCESSIBLE(object)         (G_TYPE_CHECK_INSTANCE_CAST ((object), DEEPINVTE_TYPE_TERMINAL_ACCESSIBLE, DeepinvteTerminalAccessible))
#define DEEPINVTE_TERMINAL_ACCESSIBLE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), DEEPINVTE_TYPE_TERMINAL_ACCESSIBLE, DeepinvteTerminalAccessibleClass))
#define DEEPINVTE_IS_TERMINAL_ACCESSIBLE(object)      (G_TYPE_CHECK_INSTANCE_TYPE ((object), DEEPINVTE_TYPE_TERMINAL_ACCESSIBLE))
#define DEEPINVTE_IS_TERMINAL_ACCESSIBLE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), DEEPINVTE_TYPE_TERMINAL_ACCESSIBLE))
#define DEEPINVTE_TERMINAL_ACCESSIBLE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), DEEPINVTE_TYPE_TERMINAL_ACCESSIBLE, DeepinvteTerminalAccessibleClass))

typedef struct _DeepinvteTerminalAccessible DeepinvteTerminalAccessible;
typedef struct _DeepinvteTerminalAccessibleClass DeepinvteTerminalAccessibleClass;

/**
 * DeepinvteTerminalAccessible:
 *
 * The accessible peer for #DeepinvteTerminal.
 */
struct _DeepinvteTerminalAccessible {
	GtkAccessible parent;
	/*< private > */
	/* Unknown GailWidget implementation stuffs, exact size of which is
	 * worked out at run-time. */
};

struct _DeepinvteTerminalAccessibleClass {
	GtkAccessibleClass parent_class;
	/*< private > */
	/* Unknown GailWidgetClass implementation stuffs, exact size of which
	 * is worked out at run-time. */
};

GType deepinvte_terminal_accessible_get_type(void);

AtkObject *deepinvte_terminal_accessible_new(DeepinvteTerminal *terminal);

#define DEEPINVTE_TYPE_TERMINAL_ACCESSIBLE_FACTORY            (deepinvte_terminal_accessible_factory_get_type ())
#define DEEPINVTE_TERMINAL_ACCESSIBLE_FACTORY(object)         (G_TYPE_CHECK_INSTANCE_CAST ((object), DEEPINVTE_TYPE_TERMINAL_ACCESSIBLE_FACTORY, DeepinvteTerminalAccessibleFactory))
#define DEEPINVTE_TERMINAL_ACCESSIBLE_FACTORY_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), DEEPINVTE_TYPE_TERMINAL_ACCESSIBLE_FACTORY, DeepinvteTerminalAccessibleFactoryClass))
#define DEEPINVTE_IS_TERMINAL_ACCESSIBLE_FACTORY(object)      (G_TYPE_CHECK_INSTANCE_TYPE ((object), DEEPINVTE_TYPE_TERMINAL_ACCESSIBLE_FACTORY))
#define DEEPINVTE_IS_TERMINAL_ACCESSIBLE_FACTORY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), DEEPINVTE_TYPE_TERMINAL_ACCESSIBLE_FACTORY))
#define DEEPINVTE_TERMINAL_ACCESSIBLE_FACTORY_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), DEEPINVTE_TYPE_TERMINAL_ACCESSIBLE_FACTORY, DeepinvteTerminalAccessibleFactoryClass))

typedef struct _DeepinvteTerminalAccessibleFactory DeepinvteTerminalAccessibleFactory;
typedef struct _DeepinvteTerminalAccessibleFactoryClass DeepinvteTerminalAccessibleFactoryClass;

struct _DeepinvteTerminalAccessibleFactory {
	AtkObjectFactory parent;
};

struct _DeepinvteTerminalAccessibleFactoryClass {
	AtkObjectFactoryClass parent;
};

GType deepinvte_terminal_accessible_factory_get_type(void);

AtkObjectFactory *deepinvte_terminal_accessible_factory_new(void);

G_END_DECLS

#endif
