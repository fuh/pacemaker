/*
 * Copyright 2021 the Pacemaker project contributors
 *
 * The version control history for this file may have further details.
 *
 * This source code is licensed under the GNU Lesser General Public License
 * version 2.1 or later (LGPLv2.1+) WITHOUT ANY WARRANTY.
 */

#ifndef PCMK__COMMON_CIB__H
#  define PCMK__COMMON_CIB__H

#ifdef __cplusplus
extern "C" {
#endif

const char *pcmk_cib_xpath_for(const char *element_name);

#ifdef __cplusplus
}
#endif

#endif // PCMK__COMMON_CIB__H
