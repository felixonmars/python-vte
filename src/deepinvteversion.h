/*
 * Copyright © 2008 Christian Persch
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along
 * with this library; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02110-1301  USA
 */

#if !defined (__DEEPINVTE_DEEPINVTE_H_INSIDE__) && !defined (DEEPINVTE_COMPILATION)
#error "Only <deepinvte/deepinvte.h> can be included directly."
#endif

#ifndef deepinvte_deepinvteversion_h_included
#define deepinvte_deepinvteversion_h_included

/**
 * SECTION:deepinvte-version
 * @short_description: Library version checks
 *
 * These macros enable compile time checks of the library version.
 *
 * Since: 0.16.15
 */

/**
 * DEEPINVTE_MAJOR_VERSION:
 *
 * The major version number of the DEEPINVTE library
 * (e.g. in version 3.1.4 this is 3).
 *
 * Since: 0.16.15
 */
#define DEEPINVTE_MAJOR_VERSION (0)

/**
 * DEEPINVTE_MINOR_VERSION:
 *
 * The minor version number of the DEEPINVTE library
 * (e.g. in version 3.1.4 this is 1).
 *
 * Since: 0.16.15
 */
#define DEEPINVTE_MINOR_VERSION (28)

/**
 * DEEPINVTE_MICRO_VERSION:
 *
 * The micro version number of the DEEPINVTE library
 * (e.g. in version 3.1.4 this is 4).
 *
 * Since: 0.16.15
 */
#define DEEPINVTE_MICRO_VERSION (2)

/**
 * DEEPINVTE_CHECK_VERSION:
 * @major: required major version
 * @minor: required minor version
 * @micro: required micro version
 *
 * Macro to check the library version at compile time.
 * It returns %1 if the version of DEEPINVTE is greater or
 * equal to the required one, and %0 otherwise.
 *
 * Since: 0.16.15
 */
#define DEEPINVTE_CHECK_VERSION(major,minor,micro) \
  (DEEPINVTE_MAJOR_VERSION > (major) || \
   (DEEPINVTE_MAJOR_VERSION == (major) && DEEPINVTE_MINOR_VERSION > (minor)) || \
   (DEEPINVTE_MAJOR_VERSION == (major) && DEEPINVTE_MINOR_VERSION == (minor) && DEEPINVTE_MICRO_VERSION >= (micro)))

#endif /* !deepinvte_deepinvteversion_h_included */
