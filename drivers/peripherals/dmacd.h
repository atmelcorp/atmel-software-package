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

#include "chip.h"
#include "peripherals/dmac.h"

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
	DMACD_OK = 0,	     /**< Operation is sucessful */
	DMACD_PARTIAL_DONE,
	DMACD_DONE,
	DMACD_BUSY,	     /**< Channel occupied or transfer not finished */
	DMACD_ERROR,	     /**< Operation failed */
	DMACD_CANCELED	     /**< Operation canceled */
};

/** DMA status or return code */
enum {
	DMACD_AUTO_DIS = 0,		 /**< Auto mode is disabled */
	DMACD_AUTO_EN,			 /**< Auto mode is enabled */
	DMACD_AUTO_CLEARED		 /**< Auto mode is cleared */
};

/** DMA channel */
struct _dmacd_channel;

/** DMA transfer callback */
typedef void (*dmacd_callback_t)(struct _dmacd_channel *channel, void *arg);


struct _dmacd_cfg {
	uint8_t s_decr_fetch : 1;	/* Buffer Descriptor Fetch operation is disabled for the source (0 by default) */
	uint8_t d_decr_fetch : 1;	/* Buffer Descriptor Fetch operation is disabled for the destination (0 by default)*/
	uint8_t sa_rep : 1;			/* Source Reloaded from Previous (0 by default)*/
	uint8_t da_rep : 1;			/* Destination Reloaded from Previous (0 by default)*/
	uint8_t trans_auto : 1;		/* Destination Reloaded from Previous (0 by default)*/
	uint32_t blocks; 
	uint32_t s_pip;      /* source pip config */
	uint32_t d_pip;      /* destination pip config */
	uint32_t cfg;        /* Configuration Register */
};

/** DMA Transfer Descriptor as well as Linked List Item */
struct _dma_desc {
    void * sa;           /* Source buffer address */
    void * da;           /* Destination buffer address */
    uint32_t ctrla;      /* Control A register settings */
    uint32_t ctrlb;      /* Control B register settings */
    void * desc;         /* Next descriptor address */
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
extern struct _dmacd_channel *dmacd_allocate_channel(uint8_t src, uint8_t dest);

/**
 * \brief Free the specified DMA channel.
 * \param channel Channel pointer
 */
extern uint32_t dmacd_free_channel(struct _dmacd_channel *channel);

/**
 * \brief Set the callback function for an DMA channel transfer.
 * \param channel Channel pointer
 * \param callback Pointer to callback function.
 * \param user_arg Pointer to user argument for callback.
 */
extern uint32_t dmacd_set_callback(struct _dmacd_channel *channel,
		dmacd_callback_t callback, void *user_arg);

/**
 * \brief Configure DMA for a single transfer.
 * \param channel Channel pointer
 * \param cfg DMA transfer configuration
 * \param desc_cntrl optional descriptor control
 * \param desc_addr optional descriptor address
 */
extern uint32_t dmacd_configure_transfer(struct _dmacd_channel *channel,
		struct _dmacd_cfg *cfg,  void *desc_addr);

/**
 * \brief Start DMA transfer.
 * \param channel Channel pointer
 */
extern uint32_t dmacd_start_transfer(struct _dmacd_channel *channel);

/**
 * \brief Check if DMA transfer is finished.
 * \param channel Channel pointer
 */
extern bool dmacd_is_transfer_done(struct _dmacd_channel *channel);

/**
 * \brief Stop DMA transfer.
 * \param channel Channel pointer
 */
extern uint32_t dmacd_stop_transfer(struct _dmacd_channel *channel);


/**     @}*/

/**@}*/

#endif /* CONFIG_HAVE_DMAC */

#endif /* _DMACD_H_ */
