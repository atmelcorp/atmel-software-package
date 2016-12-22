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

#ifndef _DMA_XDMAC_H_
#define _DMA_XDMAC_H_

#ifdef CONFIG_HAVE_XDMAC
/*----------------------------------------------------------------------------
 *        Includes
 *----------------------------------------------------------------------------*/

#include "callback.h"
#include "chip.h"
#include "dma/xdmac.h"

#include <stdbool.h>

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

/** \addtogroup dmad_structs DMA Driver Structs
        @{*/

struct _dma_channel;

struct _xdmacd_cfg {
	uint32_t  ubc;      /**< Microblock Size */
	uint32_t  bc;       /**< Block Control */
	uint32_t  ds;       /**< Data Stride */
	uint32_t  sus;      /**< Source Microblock Stride */
	uint32_t  dus;      /**< Destination Microblock Stride */
	void     *sa;       /**< Source Address */
	void     *da;       /**< Destination Address */
	uint32_t  cfg;      /**< Configuration Register */
};

/**     @}*/

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/** \addtogroup dmad_functions DMA Driver Functionos
        @{*/
/**
 * \brief Configure DMA for a single transfer.
 * \param channel Channel pointer
 * \param cfg DMA transfer configuration
 * \param desc_ctrl optional descriptor control
 * \param desc_addr optional descriptor address
 */
extern int xdmacd_configure_transfer(struct _dma_channel* channel,
				     struct _xdmacd_cfg* cfg,
				     uint32_t desc_ctrl,
				     void* desc_addr);

/**     @}*/

/**@}*/

#endif /* CONFIG_HAVE_XDMAC */

#endif /* _DMA_XDMAC_H_ */
