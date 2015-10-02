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

/* The interfaces in this file are subject to change at any time. */

#ifndef deepinvte_deepinvteconv_h_included
#define deepinvte_deepinvteconv_h_included


#include <glib.h>

G_BEGIN_DECLS

#define DEEPINVTE_CONV_GUNICHAR_TYPE "X-DEEPINVTE-GUNICHAR"
#define DEEPINVTE_INVALID_CONV ((DeepinvteConv)-1)

struct _DeepinvteConv;
typedef struct _DeepinvteConv *DeepinvteConv;

DeepinvteConv _deepinvte_conv_open(const char *target, const char *source);
size_t _deepinvte_conv(DeepinvteConv converter,
		 const guchar **inbuf, gsize *inbytes_left,
		 guchar **outbuf, gsize *outbytes_left);
size_t _deepinvte_conv_uc(DeepinvteConv converter,
		    const gunichar **inbuf, gsize *inbytes_left,
		    guchar **outbuf, gsize *outbytes_left);
size_t _deepinvte_conv_uu(DeepinvteConv converter,
		    const gunichar **inbuf, gsize *inbytes_left,
		    gunichar **outbuf, gsize *outbytes_left);
size_t _deepinvte_conv_cu(DeepinvteConv converter,
		    const guchar **inbuf, gsize *inbytes_left,
		    gunichar **outbuf, gsize *outbytes_left);
gint _deepinvte_conv_close(DeepinvteConv converter);

G_END_DECLS

#endif
