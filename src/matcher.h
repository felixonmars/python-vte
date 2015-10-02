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

#ifndef deepinvte_matcher_h_included
#define deepinvte_matcher_h_included


#include <glib-object.h>
#include "deepinvtetc.h"

G_BEGIN_DECLS

struct _deepinvte_matcher;

struct _deepinvte_matcher_impl {
	const struct _deepinvte_matcher_class *klass;
	/* private */
};

typedef struct _deepinvte_matcher_impl *(*_deepinvte_matcher_create_func)(void);
typedef const char *(*_deepinvte_matcher_match_func)(struct _deepinvte_matcher_impl *impl,
		const gunichar *pattern, gssize length,
		const char **res, const gunichar **consumed,
		GQuark *quark, GValueArray **array);
typedef void (*_deepinvte_matcher_add_func)(struct _deepinvte_matcher_impl *impl,
		const char *pattern, gssize length,
		const char *result, GQuark quark);
typedef void (*_deepinvte_matcher_print_func)(struct _deepinvte_matcher_impl *impl);
typedef void (*_deepinvte_matcher_destroy_func)(struct _deepinvte_matcher_impl *impl);
struct _deepinvte_matcher_class{
	_deepinvte_matcher_create_func create;
	_deepinvte_matcher_add_func add;
	_deepinvte_matcher_print_func print;
	_deepinvte_matcher_match_func match;
	_deepinvte_matcher_destroy_func destroy;
};

/* Create and init matcher. */
struct _deepinvte_matcher *_deepinvte_matcher_new(const char *emulation,
				      struct _deepinvte_termcap *termcap);

/* Free a matcher. */
void _deepinvte_matcher_free(struct _deepinvte_matcher *matcher);

/* Check if a string matches a sequence the matcher knows about. */
const char *_deepinvte_matcher_match(struct _deepinvte_matcher *matcher,
			       const gunichar *pattern, gssize length,
			       const char **res, const gunichar **consumed,
			       GQuark *quark, GValueArray **array);

/* Dump out the contents of a matcher, mainly for debugging. */
void _deepinvte_matcher_print(struct _deepinvte_matcher *matcher);

/* Free a parameter array. */
void _deepinvte_matcher_free_params_array(struct _deepinvte_matcher *matcher, GValueArray *params);

G_END_DECLS

#endif
