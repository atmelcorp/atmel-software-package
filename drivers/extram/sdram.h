/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2018, Microchip Technology
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

#ifndef SDRAM_HEADER
#define SDRAM_HEADER

#include <stdint.h>

#include "extram/sdramc.h"

enum _sdram_devices {
#ifdef CONFIG_HAVE_SDRAM_MT48LC16M16
	MT48LC16M16,
	MT48LC16M16X2,
#endif
#ifdef CONFIG_HAVE_LPSDR_MT48H32M16
	MT48H32M16,
#endif
#ifdef CONFIG_HAVE_SDRAM_W9864G6KH
	W9864G6KH,
#endif
	DUMMY_DEVICE,
};

#ifdef __cplusplus
extern "C" {
#endif

extern void sdram_init_descriptor(struct _sdramc_desc* desc,
				  enum _sdram_devices device);

extern void sdram_configure(const struct _sdramc_desc* desc);

#ifdef __cplusplus
}
#endif
#endif /* SDRAM_HEADER */
