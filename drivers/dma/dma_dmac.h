/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
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

#ifndef _DMA_DMAC_H_
#define _DMA_DMAC_H_

#ifdef CONFIG_HAVE_DMAC

/*----------------------------------------------------------------------------
 *        Includes
 *----------------------------------------------------------------------------*/

#include "callback.h"
#include "chip.h"
#include "dma/dmac.h"

#include <stdbool.h>

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

/** \addtogroup dmacd_structs DMA Driver Structs
        @{*/

struct _dma_channel;

struct _dmacd_cfg {
	uint8_t  s_decr_fetch:1; /* Buffer Descriptor Fetch operation is disabled for the source */
	uint8_t  d_decr_fetch:1; /* Buffer Descriptor Fetch operation is disabled for the destination */
	uint8_t  sa_rep:1;       /* Source Reloaded from Previous */
	uint8_t  da_rep:1;       /* Destination Reloaded from Previous */
	uint8_t  trans_auto:1;
	uint32_t blocks;
	uint32_t s_pip;          /* source pip config */
	uint32_t d_pip;          /* destination pip config */
	uint32_t cfg;            /* Configuration Register */
};

/**     @}*/

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/** \addtogroup dmacd_functions DMA Driver Functionos
        @{*/

/**
 * \brief Configure DMA for a single transfer.
 * \param channel Channel pointer
 * \param cfg DMA transfer configuration
 * \param desc optional descriptor
 */
extern int dmacd_configure_transfer(struct _dma_channel* channel,
                                    struct _dmacd_cfg* cfg,
                                    struct _dmac_desc* desc);

/**     @}*/

/**@}*/

#endif /* CONFIG_HAVE_DMAC */

#endif /* _DMA_DMAC_H_ */
