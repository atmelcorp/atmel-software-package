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

#ifndef _DMACD_H_
#define _DMACD_H_

#ifdef CONFIG_HAVE_DMAC

/*----------------------------------------------------------------------------
 *        Includes
 *----------------------------------------------------------------------------*/

#include "callback.h"
#include "chip.h"
#include "dma/dmac.h"

#include <stdbool.h>

/*----------------------------------------------------------------------------
 *        Consts
 *----------------------------------------------------------------------------*/

/** \addtogroup dmacd_defines DMA Driver Defines
        @{*/

/** Pseudo Peripheral ID for memory transfers */
#define DMACD_PERIPH_MEMORY 0xFF

/**     @}*/

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

/** \addtogroup dmacd_structs DMA Driver Structs
        @{*/

/** DMA status or return code */
enum {
	DMACD_AUTO_DIS = 0, /**< Auto mode is disabled */
	DMACD_AUTO_EN,      /**< Auto mode is enabled */
	DMACD_AUTO_CLEARED  /**< Auto mode is cleared */
};

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
 * \brief Initialize DMA driver instance.
 * \param polling if true, interrupts will not be configured and dmacd_poll
 * must be called to poll for transfer completion
 */
extern void dmacd_initialize(bool polling);

/**
 * \brief Poll for transfer completion.
 * If polling mode is enabled, this function will call callbacks for completed
 * transfers.  If interrupt mode is enabled, this function will do nothing.
 */
extern void dmacd_poll(void);

/**
 * \brief Allocate a DMA channel
 * \param src Source peripheral ID, DMACD_PERIPH_MEMORY for memory.
 * \param dest Destination peripheral ID, DMACD_PERIPH_MEMORY for memory.
 * \return Channel pointer if allocation successful, or NULL if channel
 * allocation failed.
 */
extern struct _dma_channel *dmacd_allocate_channel(uint8_t src, uint8_t dest);

/**
 * \brief Free the specified DMA channel.
 * \param channel Channel pointer
 */
extern int dmacd_free_channel(struct _dma_channel* channel);

/**
 * \brief Set the callback function for an DMA channel transfer.
 * \param channel Channel pointer
 * \param callback Pointer to callback function.
 * \param user_arg Pointer to user argument for callback.
 */
extern int dmacd_set_callback(struct _dma_channel* channel, struct _callback* cb);

/**
 * \brief Configure DMA for a single transfer.
 * \param channel Channel pointer
 * \param cfg DMA transfer configuration
 * \param desc optional descriptor
 */
extern int dmacd_configure_transfer(struct _dma_channel* channel,
                                    struct _dmacd_cfg* cfg,
                                    struct _dmac_desc* desc);

/**
 * \brief Start DMA transfer.
 * \param channel Channel pointer
 */
extern int dmacd_start_transfer(struct _dma_channel* channel);

/**
 * \brief Check if DMA transfer is finished.
 * \param channel Channel pointer
 */
extern bool dmacd_is_transfer_done(struct _dma_channel* channel);

/**
 * \brief Stop DMA transfer.
 * \param channel Channel pointer
 */
extern int dmacd_stop_transfer(struct _dma_channel* channel);

/**
 * \brief Reset the specified  DMA channel.
 * \param channel Channel pointer
 */
extern int dmacd_reset_channel(struct _dma_channel* channel);

/**
 * \brief Suspend DMA transfer.
 * \param channel Channel pointer
 */
extern int dmacd_suspend_transfer(struct _dma_channel* channel);

/**
 * \brief Resume DMA transfer.
 * \param channel Channel pointer
 */
extern int dmacd_resume_transfer(struct _dma_channel* channel);

/**
 * \brief Flush the relevant channel's FIFO of given DMAC.
 *
 * \param channel Channel pointer
 */
extern void dmacd_fifo_flush(struct _dma_channel* channel);

/**
 * \brief Get size of already trasnferred data by DMA.
 * \param channel Channel pointer
 */
extern uint32_t dmacd_get_transferred_data_len(struct _dma_channel* channel);

/**
 * \brief Get next descriptor's address for the relevant channel of given DMAC.
 * \param channel Channel pointer
 */
extern uint32_t dmacd_get_desc_addr(struct _dma_channel* channel);

/**     @}*/

/**@}*/

#endif /* CONFIG_HAVE_DMAC */

#endif /* _DMACD_H_ */
