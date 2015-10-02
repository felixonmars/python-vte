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


#include <config.h>
#include <sys/types.h>
#include <string.h>
#include <glib-object.h>
#include "debug.h"
#include "caps.h"
#include "matcher.h"
#include "table.h"
#include "trie.h"

struct _deepinvte_matcher {
	_deepinvte_matcher_match_func match; /* shortcut to the most common op */
	struct _deepinvte_matcher_impl *impl;
	GValueArray *free_params;
};

static GStaticMutex _deepinvte_matcher_mutex = G_STATIC_MUTEX_INIT;
static GCache *_deepinvte_matcher_cache = NULL;
static struct _deepinvte_matcher_impl dummy_deepinvte_matcher_trie = {
	&_deepinvte_matcher_trie
};
static struct _deepinvte_matcher_impl dummy_deepinvte_matcher_table = {
	&_deepinvte_matcher_table
};

/* Add a string to the matcher. */
static void
_deepinvte_matcher_add(const struct _deepinvte_matcher *matcher,
		 const char *pattern, gssize length,
		 const char *result, GQuark quark)
{
	matcher->impl->klass->add(matcher->impl, pattern, length, result, quark);
}

/* Loads all sequences into matcher */
static void
_deepinvte_matcher_init(struct _deepinvte_matcher *matcher, const char *emulation,
		  struct _deepinvte_termcap *termcap)
{
	const char *code, *value;
	gboolean found_cr = FALSE, found_lf = FALSE;
	gssize stripped_length;
	char *stripped;
	int i;

	_deepinvte_debug_print(DEEPINVTE_DEBUG_LIFECYCLE, "_deepinvte_matcher_init()\n");

	if (termcap != NULL) {
		/* Load the known capability strings from the termcap
		 * structure into the table for recognition. */
		for (i = 0;
				_deepinvte_terminal_capability_strings[i].capability[0];
				i++) {
			if (_deepinvte_terminal_capability_strings[i].key) {
				continue;
			}
			code = _deepinvte_terminal_capability_strings[i].capability;
			stripped = _deepinvte_termcap_find_string_length(termcap,
					emulation,
					code,
					&stripped_length);
			if (stripped[0] != '\0') {
				_deepinvte_matcher_add(matcher,
						stripped, stripped_length,
						code, 0);
				if (stripped[0] == '\r') {
					found_cr = TRUE;
				} else
					if (stripped[0] == '\n') {
						if (strcmp(code, "sf") == 0 ||
								strcmp(code, "do") == 0) {
							found_lf = TRUE;
						}
					}
			}
			g_free(stripped);
		}
	}

	/* Add emulator-specific sequences. */
	if (strstr(emulation, "xterm") || strstr(emulation, "dtterm")) {
		/* Add all of the xterm-specific stuff. */
		for (i = 0;
		     _deepinvte_xterm_capability_strings[i].value != NULL;
		     i++) {
			code = _deepinvte_xterm_capability_strings[i].code;
			value = _deepinvte_xterm_capability_strings[i].value;
			_deepinvte_matcher_add(matcher, code, strlen (code),
					 value, 0);
		}
	}

	/* Always define cr and lf. */
	if (!found_cr) {
		_deepinvte_matcher_add(matcher, "\r", 1, "cr", 0);
	}
	if (!found_lf) {
		_deepinvte_matcher_add(matcher, "\n", 1, "sf", 0);
	}

	_DEEPINVTE_DEBUG_IF(DEEPINVTE_DEBUG_TRIE) {
		g_printerr("Trie contents:\n");
		_deepinvte_matcher_print(matcher);
		g_printerr("\n");
	}
}

/* Allocates new matcher structure. */
static gpointer
_deepinvte_matcher_create(gpointer key)
{
	char *emulation = key;
	struct _deepinvte_matcher *ret = NULL;

	_deepinvte_debug_print(DEEPINVTE_DEBUG_LIFECYCLE, "_deepinvte_matcher_create()\n");
	ret = g_slice_new(struct _deepinvte_matcher);
	ret->impl = &dummy_deepinvte_matcher_trie;
	ret->match = NULL;
	ret->free_params = NULL;

	if (strcmp(emulation, "xterm") == 0) {
		ret->impl = &dummy_deepinvte_matcher_table;
	} else
	if (strcmp(emulation, "dtterm") == 0) {
		ret->impl = &dummy_deepinvte_matcher_table;
	}

	return ret;
}

/* Noone uses this matcher, free it. */
static void
_deepinvte_matcher_destroy(gpointer value)
{
	struct _deepinvte_matcher *matcher = value;

	_deepinvte_debug_print(DEEPINVTE_DEBUG_LIFECYCLE, "_deepinvte_matcher_destroy()\n");
	if (matcher->free_params != NULL) {
		g_value_array_free (matcher->free_params);
	}
	if (matcher->match != NULL) /* do not call destroy on dummy values */
		matcher->impl->klass->destroy(matcher->impl);
	g_slice_free(struct _deepinvte_matcher, matcher);
}

/* Create and init matcher. */
struct _deepinvte_matcher *
_deepinvte_matcher_new(const char *emulation, struct _deepinvte_termcap *termcap)
{
	struct _deepinvte_matcher *ret = NULL;
	g_static_mutex_lock(&_deepinvte_matcher_mutex);

	if (emulation == NULL) {
		emulation = "";
	}

	if (_deepinvte_matcher_cache == NULL) {
		_deepinvte_matcher_cache = g_cache_new(_deepinvte_matcher_create,
				_deepinvte_matcher_destroy,
				(GCacheDupFunc) g_strdup, g_free,
				g_str_hash, g_direct_hash, g_str_equal);
	}

	ret = g_cache_insert(_deepinvte_matcher_cache, (gpointer) emulation);

	if (ret->match == NULL) {
		ret->impl = ret->impl->klass->create();
		ret->match = ret->impl->klass->match;
		_deepinvte_matcher_init(ret, emulation, termcap);
	}

	g_static_mutex_unlock(&_deepinvte_matcher_mutex);
	return ret;
}

/* Free a matcher. */
void
_deepinvte_matcher_free(struct _deepinvte_matcher *matcher)
{
	g_assert(_deepinvte_matcher_cache != NULL);
	g_static_mutex_lock(&_deepinvte_matcher_mutex);
	g_cache_remove(_deepinvte_matcher_cache, matcher);
	g_static_mutex_unlock(&_deepinvte_matcher_mutex);
}

/* Check if a string matches a sequence the matcher knows about. */
const char *
_deepinvte_matcher_match(struct _deepinvte_matcher *matcher,
		   const gunichar *pattern, gssize length,
		   const char **res, const gunichar **consumed,
		   GQuark *quark, GValueArray **array)
{
	if (G_UNLIKELY (array != NULL && matcher->free_params != NULL)) {
		*array = matcher->free_params;
		matcher->free_params = NULL;
	}
	return matcher->match(matcher->impl, pattern, length,
					res, consumed, quark, array);
}

/* Dump out the contents of a matcher, mainly for debugging. */
void
_deepinvte_matcher_print(struct _deepinvte_matcher *matcher)
{
	matcher->impl->klass->print(matcher->impl);
}

/* Free a parameter array.  Most of the GValue elements can clean up after
 * themselves, but we're using gpointers to hold unicode character strings, and
 * we need to free those ourselves. */
void
_deepinvte_matcher_free_params_array(struct _deepinvte_matcher *matcher,
		               GValueArray *params)
{
	guint i;
	for (i = 0; i < params->n_values; i++) {
		GValue *value = &params->values[i];
		if (G_UNLIKELY (g_type_is_a (value->g_type, G_TYPE_POINTER))) {
			g_free (g_value_get_pointer (value));
		}
	}
	if (G_UNLIKELY (matcher == NULL || matcher->free_params != NULL)) {
		g_value_array_free (params);
	} else {
		matcher->free_params = params;
		params->n_values = 0;
	}
}

