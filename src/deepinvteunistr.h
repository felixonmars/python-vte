/*
 * Copyright (C) 2008 Red Hat, Inc.
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
 * Author(s):
 * 	Behdad Esfahbod
 */

#ifndef deepinvte_deepinvteunistr_h_included
#define deepinvte_deepinvteunistr_h_included

#include <glib.h>

G_BEGIN_DECLS

/**
 * deepinvteunistr:
 *
 * deepinvteunistr is a gunichar-compatible way to store strings.  A string
 * consisting of a single unichar c is represented as the same value
 * as c itself.  In that sense, gunichars can be readily used as
 * deepinvteunistrs.  Longer strings can be built by appending a unichar
 * to an already existing string.
 *
 * deepinvteunistr is essentially just a gunicode-compatible quark value.
 * It can be used to store strings (of a base followed by combining
 * characters) where the code was designed to only allow one character.
 *
 * Strings are internalized efficiently and never freed.  No memory
 * management of deepinvteunistr values is needed.
 **/
typedef guint32 deepinvteunistr;

/**
 * _deepinvte_unistr_append_unichar:
 * @s: a #deepinvteunistr
 * @c: Unicode character to append to @s
 *
 * Creates a deepinvteunistr value for the string @s followed by the
 * character @c.
 *
 * Returns: the new #deepinvteunistr value
 **/
deepinvteunistr
_deepinvte_unistr_append_unichar (deepinvteunistr s, gunichar c);

gunichar
_deepinvte_unistr_get_base (deepinvteunistr s);

/**
 * _deepinvte_unistr_append_to_string:
 * @s: a #deepinvteunistr
 * @gs: a #GString to append @s to
 *
 * Appends @s to @gs.  This is how one converts a #deepinvteunistr to a
 * traditional string.
 **/
void
_deepinvte_unistr_append_to_string (deepinvteunistr s, GString *gs);

/**
 * _deepinvte_unistr_strlen:
 * @s: a #deepinvteunistr
 *
 * Counts the number of character in @s.
 *
 * Returns: length of @s in characters.
 **/
int
_deepinvte_unistr_strlen (deepinvteunistr s);

G_END_DECLS

#endif
