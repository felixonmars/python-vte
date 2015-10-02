/*
 * Copyright (C) 2002,2003 Red Hat, Inc.
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

#include <glib.h>
#include "debug.h"

DeepinvteDebugFlags _deepinvte_debug_flags;

void
_deepinvte_debug_init(void)
{
#ifdef DEEPINVTE_DEBUG
  const GDebugKey keys[] = {
    { "misc",         DEEPINVTE_DEBUG_MISC         },
    { "io",           DEEPINVTE_DEBUG_IO           },
    { "adj",          DEEPINVTE_DEBUG_ADJ          },
    { "updates",      DEEPINVTE_DEBUG_UPDATES      },
    { "events",       DEEPINVTE_DEBUG_EVENTS       },
    { "parse",        DEEPINVTE_DEBUG_PARSE        },
    { "signals",      DEEPINVTE_DEBUG_SIGNALS      },
    { "selection",    DEEPINVTE_DEBUG_SELECTION    },
    { "substitution", DEEPINVTE_DEBUG_SUBSTITUTION },
    { "ring",         DEEPINVTE_DEBUG_RING         },
    { "pty",          DEEPINVTE_DEBUG_PTY          },
    { "cursor",       DEEPINVTE_DEBUG_CURSOR       },
    { "keyboard",     DEEPINVTE_DEBUG_KEYBOARD     },
    { "lifecycle",    DEEPINVTE_DEBUG_LIFECYCLE    },
    { "trie",         DEEPINVTE_DEBUG_TRIE         },
    { "work",         DEEPINVTE_DEBUG_WORK         },
    { "cells",        DEEPINVTE_DEBUG_CELLS        },
    { "timeout",      DEEPINVTE_DEBUG_TIMEOUT      },
    { "draw",         DEEPINVTE_DEBUG_DRAW         },
    { "ally",         DEEPINVTE_DEBUG_ALLY         },
    { "pangocairo",   DEEPINVTE_DEBUG_PANGOCAIRO   },
    { "widget-size",  DEEPINVTE_DEBUG_WIDGET_SIZE  },
    { "bg",           DEEPINVTE_DEBUG_BG           }
  };

  _deepinvte_debug_flags = g_parse_debug_string (g_getenv("DEEPINVTE_DEBUG"),
                                           keys, G_N_ELEMENTS (keys));
  _deepinvte_debug_print(0xFFFFFFFF, "DEEPINVTE debug flags = %x\n", _deepinvte_debug_flags);
#endif /* DEEPINVTE_DEBUG */
}
