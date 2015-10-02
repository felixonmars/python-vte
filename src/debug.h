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

#ifndef deepinvte_debug_h_included
#define deepinvte_debug_h_included

#include <config.h>

#include <glib.h>

G_BEGIN_DECLS

typedef enum {
	DEEPINVTE_DEBUG_MISC		= 1 << 0,
	DEEPINVTE_DEBUG_PARSE		= 1 << 1,
	DEEPINVTE_DEBUG_IO		= 1 << 2,
	DEEPINVTE_DEBUG_UPDATES	= 1 << 3,
	DEEPINVTE_DEBUG_EVENTS	= 1 << 4,
	DEEPINVTE_DEBUG_SIGNALS	= 1 << 5,
	DEEPINVTE_DEBUG_SELECTION	= 1 << 6,
	DEEPINVTE_DEBUG_SUBSTITUTION	= 1 << 7,
	DEEPINVTE_DEBUG_RING		= 1 << 8,
	DEEPINVTE_DEBUG_PTY		= 1 << 9,
	DEEPINVTE_DEBUG_CURSOR	= 1 << 10,
	DEEPINVTE_DEBUG_KEYBOARD	= 1 << 11,
	DEEPINVTE_DEBUG_LIFECYCLE	= 1 << 12,
	DEEPINVTE_DEBUG_TRIE		= 1 << 13,
	DEEPINVTE_DEBUG_WORK		= 1 << 14,
	DEEPINVTE_DEBUG_CELLS		= 1 << 15,
	DEEPINVTE_DEBUG_TIMEOUT	= 1 << 16,
	DEEPINVTE_DEBUG_DRAW		= 1 << 17,
	DEEPINVTE_DEBUG_ALLY		= 1 << 18,
	DEEPINVTE_DEBUG_ADJ		= 1 << 19,
	DEEPINVTE_DEBUG_PANGOCAIRO    = 1 << 20,
	DEEPINVTE_DEBUG_WIDGET_SIZE   = 1 << 21,
        DEEPINVTE_DEBUG_BG            = 1 << 22
} DeepinvteDebugFlags;

void _deepinvte_debug_init(void);

extern DeepinvteDebugFlags _deepinvte_debug_flags;
static inline gboolean _deepinvte_debug_on(DeepinvteDebugFlags flags) G_GNUC_CONST G_GNUC_UNUSED;

static inline gboolean
_deepinvte_debug_on(DeepinvteDebugFlags flags)
{
	return (_deepinvte_debug_flags & flags) == flags;
}

#ifdef DEEPINVTE_DEBUG
#define _DEEPINVTE_DEBUG_IF(flags) if (G_UNLIKELY (_deepinvte_debug_on (flags)))
#else
#define _DEEPINVTE_DEBUG_IF(flags) if (0)
#endif

#if defined(__GNUC__) && G_HAVE_GNUC_VARARGS
#define _deepinvte_debug_print(flags, fmt, ...) \
	G_STMT_START { _DEEPINVTE_DEBUG_IF(flags) g_printerr(fmt, ##__VA_ARGS__); } G_STMT_END
#else
#include <stdarg.h>
#include <glib/gstdio.h>
static void _deepinvte_debug_print(guint flags, const char *fmt, ...)
{
	_DEEPINVTE_DEBUG_IF(flags) {
		va_list  ap;
		va_start (ap, fmt);
		g_vfprintf (stderr, fmt, ap);
		va_end (ap);
	}
}
#endif

G_END_DECLS

#endif
