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

#ifndef deepinvte_deepinvteint_h_included
#define deepinvte_deepinvteint_h_included


#include "deepinvte.h"

G_BEGIN_DECLS

void _deepinvte_terminal_accessible_ref(DeepinvteTerminal *terminal);
char* _deepinvte_terminal_get_selection(DeepinvteTerminal *terminal);
void _deepinvte_terminal_get_start_selection(DeepinvteTerminal *terminal, long *x, long *y);
void _deepinvte_terminal_get_end_selection(DeepinvteTerminal *terminal, long *x, long *y);
void _deepinvte_terminal_select_text(DeepinvteTerminal *terminal, long start_x, long start_y, long end_x, long end_y, int start_offset, int end_offset);
void _deepinvte_terminal_remove_selection(DeepinvteTerminal *terminal);

G_END_DECLS

#endif
