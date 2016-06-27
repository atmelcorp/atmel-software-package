/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

#ifndef DDRAM_HEADER
#define DDRAM_HEADER

#include "peripherals/mpddrc.h"

enum _ddram_devices {
#ifdef CONFIG_HAVE_MPDDRC_DDR2
  #ifdef CONFIG_HAVE_DDR2_MT47H128M8CF
	MT47H128M8CF,  /* DDR2 */
  #endif
  #ifdef CONFIG_HAVE_DDR2_MT47H64M16
	MT47H64M16,    /* DDR2 */
  #endif
  #ifdef CONFIG_HAVE_DDR2_MT47H128M16
	MT47H128M16,   /* DDR2 */
  #endif
#endif
#ifdef CONFIG_HAVE_MPDDRC_LPDDR2
  #ifdef CONFIG_HAVE_LPDDR2_MT42L128M16
	MT42L128M16,   /* LPDDR2 */
  #endif
#endif
#ifdef CONFIG_HAVE_MPDDRC_DDR3
  #ifdef CONFIG_HAVE_DDR3_MT41K128M16
	MT41K128M16,   /* DDR3 512 MB */
  #endif
#endif
#ifdef CONFIG_HAVE_MPDDRC_LPDDR3
  #ifdef CONFIG_HAVE_LPDDR3_EDF8164A3MA
	EDF8164A3MA,   /* LPDDR3 512MB */
  #endif
#endif
};

#ifdef __cplusplus
extern "C" {
#endif

extern void ddram_init_descriptor(struct _mpddrc_desc* desc,
				  enum _ddram_devices device);

extern void ddram_configure(struct _mpddrc_desc* desc, uint32_t tc_id, uint32_t tc_ch);

#ifdef __cplusplus
}
#endif
#endif
