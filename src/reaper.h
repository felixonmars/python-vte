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

#ifndef DEEPINVTE_DISABLE_DEPRECATED

#ifndef deepinvte_reaper_h_included
#define deepinvte_reaper_h_included

#include <sys/wait.h>
#include <signal.h>
#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

/**
 * DeepinvteReaper:
 *
 * The reaper object.
 */
struct _DeepinvteReaper {
	GObject object;

        /*< private >*/
	GIOChannel *_channel; /* unused */
	int _iopipe[2]; /* unused */
};
typedef struct _DeepinvteReaper DeepinvteReaper;

struct _DeepinvteReaperClass {
	GObjectClass parent_class;
        /*< private >*/
	guint child_exited_signal;
};
typedef struct _DeepinvteReaperClass DeepinvteReaperClass;

GType deepinvte_reaper_get_type(void);

#define DEEPINVTE_TYPE_REAPER			(deepinvte_reaper_get_type())
#define DEEPINVTE_REAPER(obj)			(G_TYPE_CHECK_INSTANCE_CAST((obj), \
							DEEPINVTE_TYPE_REAPER, \
							DeepinvteReaper))
#define DEEPINVTE_REAPER_CLASS(klass)		G_TYPE_CHECK_CLASS_CAST((klass), \
							     DEEPINVTE_TYPE_REAPER, \
							     DeepinvteReaperClass)
#define DEEPINVTE_IS_REAPER(obj)		G_TYPE_CHECK_INSTANCE_TYPE((obj), DEEPINVTE_TYPE_REAPER)
#define DEEPINVTE_IS_REAPER_CLASS(klass)	G_TYPE_CHECK_CLASS_TYPE((klass), \
							     DEEPINVTE_TYPE_REAPER)
#define DEEPINVTE_REAPER_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS((obj), \
								   DEEPINVTE_TYPE_REAPER, \
								   DeepinvteReaperClass))

DeepinvteReaper *deepinvte_reaper_get(void);
int deepinvte_reaper_add_child(GPid pid);

G_END_DECLS

#endif

#endif /* !DEEPINVTE_DISABLE_DEPRECATED */
