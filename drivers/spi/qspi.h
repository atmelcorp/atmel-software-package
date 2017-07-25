/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
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
 */

#ifndef	QSPI_H_
#define	QSPI_H_

#ifdef CONFIG_HAVE_QSPI_DMA
#include "dma/dma.h"
#include "mm/cache.h"
#endif

/* Forward declaration */
struct spi_flash;
struct spi_flash_cfg;

/*----------------------------------------------------------------------------
 *        TYPES
 *----------------------------------------------------------------------------*/

struct qspi_priv {
	Qspi* addr;
	void* mem;
#ifdef CONFIG_HAVE_AESB
	void* mem_aesb;
#endif
#ifdef CONFIG_HAVE_QSPI_DMA
	struct _dma_channel *dma_ch;
#endif
};

/*----------------------------------------------------------------------------
 *        EXPORTED FUNCTIONS
 *----------------------------------------------------------------------------*/

extern void qspi_configure(struct spi_flash *flash, const struct spi_flash_cfg *cfg);

extern int qspi_xip(struct spi_flash *flash, void **mem);

#endif /* QSPI_H_ */
