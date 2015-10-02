/*
 * Copyright (C) 2001,2002,2003,2009,2010 Red Hat, Inc.
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

#if !defined (__DEEPINVTE_DEEPINVTE_H_INSIDE__) && !defined (DEEPINVTE_COMPILATION)
#error "Only <deepinvte/deepinvte.h> can be included directly."
#endif

#ifndef DEEPINVTE_DISABLE_DEPRECATED

#ifndef deepinvte_deprecated_h_included
#define deepinvte_deprecated_h_included

#include <sys/types.h> /* for pid_t */

G_BEGIN_DECLS

/**
 * DEEPINVTE_IS_TERMINAL_ERASE_BINDING:
 *
 * Does nothing.
 *
 * Returns: %FALSE
 *
 * @Deprecated: 0.20
 */
#define DEEPINVTE_IS_TERMINAL_ERASE_BINDING(obj)  (FALSE)

/**
 * DEEPINVTE_IS_TERMINAL_ANTI_ALIAS:
 *
 * Does nothing.
 *
 * Returns: %FALSE
 *
 * @Deprecated: 0.20
 */
#define DEEPINVTE_IS_TERMINAL_ANTI_ALIAS(obj)     (FALSE)

/**
 * DeepinvteTerminalAntiAlias:
 * @DEEPINVTE_ANTI_ALIAS_USE_DEFAULT: Use the system default anti-alias setting
 * @DEEPINVTE_ANTI_ALIAS_FORCE_ENABLE: Force enable anti-aliasing
 * @DEEPINVTE_ANTI_ALIAS_FORCE_DISABLE: Force disable anti-aliasing
 *
 * An enumeration describing which anti-alias setting to use.
 *
 * @Deprecated: 0.20
 */
typedef enum {
	DEEPINVTE_ANTI_ALIAS_USE_DEFAULT,
	DEEPINVTE_ANTI_ALIAS_FORCE_ENABLE,
	DEEPINVTE_ANTI_ALIAS_FORCE_DISABLE
} DeepinvteTerminalAntiAlias;

void deepinvte_terminal_set_cursor_blinks(DeepinvteTerminal *terminal,
				    gboolean blink) G_GNUC_DEPRECATED;
gboolean deepinvte_terminal_get_using_xft(DeepinvteTerminal *terminal) G_GNUC_DEPRECATED;
int deepinvte_terminal_match_add(DeepinvteTerminal *terminal, const char *match) G_GNUC_DEPRECATED;
glong deepinvte_terminal_get_char_descent(DeepinvteTerminal *terminal) G_GNUC_DEPRECATED;
glong deepinvte_terminal_get_char_ascent(DeepinvteTerminal *terminal) G_GNUC_DEPRECATED;
void deepinvte_terminal_set_font_full(DeepinvteTerminal *terminal,
				const PangoFontDescription *font_desc,
				DeepinvteTerminalAntiAlias antialias) G_GNUC_DEPRECATED;
void deepinvte_terminal_set_font_from_string_full(DeepinvteTerminal *terminal,
					    const char *name,
					    DeepinvteTerminalAntiAlias antialias) G_GNUC_DEPRECATED;
pid_t deepinvte_terminal_fork_command(DeepinvteTerminal *terminal,
				const char *command, char **argv,
				char **envv, const char *working_directory,
				gboolean lastlog,
				gboolean utmp,
				gboolean wtmp) G_GNUC_DEPRECATED;
pid_t deepinvte_terminal_forkpty(DeepinvteTerminal *terminal,
			   char **envv, const char *working_directory,
			   gboolean lastlog,
			   gboolean utmp,
			   gboolean wtmp) G_GNUC_DEPRECATED;
void deepinvte_terminal_get_padding(DeepinvteTerminal *terminal, int *xpad, int *ypad) G_GNUC_DEPRECATED;
void deepinvte_terminal_set_pty(DeepinvteTerminal *terminal, int pty_master);
int deepinvte_terminal_get_pty(DeepinvteTerminal *terminal);

#if GTK_CHECK_VERSION (2, 91, 2)
GtkAdjustment *deepinvte_terminal_get_adjustment(DeepinvteTerminal *terminal);
#endif

G_END_DECLS

#endif /* !deepinvte_deprecated_h_included */

#endif /* !DEEPINVTE_DISABLE_DEPRECATED */
