/*
 * Copyright © 2009, 2010 Christian Persch
 *
 * This is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#if !defined (__DEEPINVTE_DEEPINVTE_H_INSIDE__) && !defined (DEEPINVTE_COMPILATION)
#error "Only <deepinvte/deepinvte.h> can be included directly."
#endif

#ifndef DEEPINVTE_PTY_H
#define DEEPINVTE_PTY_H

#include <glib-object.h>

G_BEGIN_DECLS

/**
 * DeepinvtePtyFlags:
 * @DEEPINVTE_PTY_NO_LASTLOG: don't record the session in lastlog
 * @DEEPINVTE_PTY_NO_UTMP: don't record the session in utmp
 * @DEEPINVTE_PTY_NO_WTMP: don't record the session in wtmp
 * @DEEPINVTE_PTY_NO_HELPER: don't use the GNOME PTY helper to allocate the PTY
 * @DEEPINVTE_PTY_NO_FALLBACK: when allocating the PTY with the PTY helper fails,
 *   don't fall back to try using PTY98
 * @DEEPINVTE_PTY_DEFAULT: the default flags
 *
 * Since: 0.26
 */
typedef enum {
  DEEPINVTE_PTY_NO_LASTLOG  = 1 << 0,
  DEEPINVTE_PTY_NO_UTMP     = 1 << 1,
  DEEPINVTE_PTY_NO_WTMP     = 1 << 2,
  DEEPINVTE_PTY_NO_HELPER   = 1 << 3,
  DEEPINVTE_PTY_NO_FALLBACK = 1 << 4,
  DEEPINVTE_PTY_DEFAULT     = 0
} DeepinvtePtyFlags;

/**
 * DeepinvtePtyError:
 * @DEEPINVTE_PTY_ERROR_PTY_HELPER_FAILED: failure when using the GNOME PTY helper to
 *   allocate the PTY
 * @DEEPINVTE_PTY_ERROR_PTY98_FAILED: failure when using PTY98 to allocate the PTY
 *
 * Since: 0.26
 */
typedef enum {
  DEEPINVTE_PTY_ERROR_PTY_HELPER_FAILED = 0,
  DEEPINVTE_PTY_ERROR_PTY98_FAILED
} DeepinvtePtyError;

GQuark deepinvte_pty_error_quark (void);

/**
 * DEEPINVTE_PTY_ERROR:
 *
 * Error domain for DEEPINVTE PTY errors. Errors in this domain will be from the #DeepinvtePtyError
 * enumeration. See #GError for more information on error domains.
 *
 * Since: 0.26
 */
#define DEEPINVTE_PTY_ERROR (deepinvte_pty_error_quark ())

/* DEEPINVTE PTY object */

#define DEEPINVTE_TYPE_PTY            (deepinvte_pty_get_type())
#define DEEPINVTE_PTY(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), DEEPINVTE_TYPE_PTY, DeepinvtePty))
#define DEEPINVTE_PTY_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  DEEPINVTE_TYPE_PTY, DeepinvtePtyClass))
#define DEEPINVTE_IS_PTY(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), DEEPINVTE_TYPE_PTY))
#define DEEPINVTE_IS_PTY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  DEEPINVTE_TYPE_PTY))
#define DEEPINVTE_PTY_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  DEEPINVTE_TYPE_PTY, DeepinvtePtyClass))

typedef struct _DeepinvtePty        DeepinvtePty;
typedef struct _DeepinvtePtyClass   DeepinvtePtyClass;

GType deepinvte_pty_get_type (void);

DeepinvtePty *deepinvte_pty_new (DeepinvtePtyFlags flags,
                     GError **error);

DeepinvtePty *deepinvte_pty_new_foreign (int fd,
                             GError **error);

int deepinvte_pty_get_fd (DeepinvtePty *pty);

void deepinvte_pty_close (DeepinvtePty *pty);

void deepinvte_pty_child_setup (DeepinvtePty *pty);

gboolean deepinvte_pty_get_size (DeepinvtePty *pty,
                           int *rows,
                           int *columns,
                           GError **error);

gboolean deepinvte_pty_set_size (DeepinvtePty *pty,
                           int rows,
                           int columns,
                           GError **error);

gboolean deepinvte_pty_set_utf8 (DeepinvtePty *pty,
                           gboolean utf8,
                           GError **error);

void deepinvte_pty_set_term (DeepinvtePty *pty,
                       const char *emulation);

G_END_DECLS

#endif /* DEEPINVTE_PTY_H */
