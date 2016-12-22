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

#ifndef _DMA_H_
#define _DMA_H_

/*----------------------------------------------------------------------------
 *        Includes
 *----------------------------------------------------------------------------*/

#include <stdbool.h>

#include "callback.h"
#include "chip.h"
#if defined(CONFIG_HAVE_DMAC)
#include "dma/dma_dmac.h"
#elif defined(CONFIG_HAVE_XDMAC)
#include "dma/dma_xdmac.h"
#else
#error "Requires a DMA controller to be enabled"
#endif

/*------------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

/** DMA state for channel */
enum {
	DMA_STATE_FREE = 0,  /**< Free channel */
	DMA_STATE_ALLOCATED, /**< Allocated to some peripheral */
	DMA_STATE_STARTED,   /**< DMA started */
	DMA_STATE_DONE,      /**< DMA transfer done */
	DMA_STATE_SUSPENDED, /**< DMA suspended */
};

#define DMA_PERIPH_MEMORY  0xFF

#define DMA_DATA_WIDTH_BYTE        0
#define DMA_DATA_WIDTH_HALF_WORD   1
#define DMA_DATA_WIDTH_WORD        2
#if defined(CONFIG_HAVE_XDMAC_DATA_WIDTH_DWORD) ||\
    defined(CONFIG_HAVE_DMAC_DATA_WIDTH_DWORD)
#define DMA_DATA_WIDTH_DWORD       3
#endif

#ifdef CONFIG_HAVE_XDMAC

#define DMA_CHANNELS XDMAC_CHANNELS

#define DMA_MAX_BT_SIZE    XDMAC_MAX_BT_SIZE
#define DMA_MAX_BLOCK_LEN  XDMAC_MAX_BLOCK_LEN

#define DMA_CHUNK_SIZE_1   0
#define DMA_CHUNK_SIZE_2   1
#define DMA_CHUNK_SIZE_4   2
#define DMA_CHUNK_SIZE_8   3
#define DMA_CHUNK_SIZE_16  4

#elif defined(CONFIG_HAVE_DMAC)

#define DMA_CHANNELS DMAC_CHANNELS

#define DMA_MAX_BT_SIZE    DMAC_MAX_BT_SIZE
#define DMA_MAX_BLOCK_LEN  DMAC_MAX_BLOCK_LEN

#define DMA_CHUNK_SIZE_1   0
#define DMA_CHUNK_SIZE_4   1
#define DMA_CHUNK_SIZE_8   2
#define DMA_CHUNK_SIZE_16  3
#define DMA_CHUNK_SIZE_32  4
#define DMA_CHUNK_SIZE_64  5
#define DMA_CHUNK_SIZE_128 6
#define DMA_CHUNK_SIZE_256 7

#endif

#ifndef DMA_SG_ITEM_POOL_SIZE
#define DMA_SG_ITEM_POOL_SIZE   64
#endif

#define DMA_DATA_WIDTH_IN_BYTE(w)   (1 << w)

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

/** \addtogroup dma_structs DMA Driver Structs
		@{*/

/** DMA driver channel */
struct _dma_channel {
#if defined(CONFIG_HAVE_DMAC)
	Dmac* hw;  /* DMAC instance */
#elif defined(CONFIG_HAVE_XDMAC)
	Xdmac* hw; /* XDMAC instance */
#endif
	uint32_t id; /* Channel ID */

	struct _callback callback;	/* Callback */

	uint8_t src_txif;			/* Source TX Interface ID */
	uint8_t src_rxif;			/* Source RX Interface ID */
	uint8_t dest_txif;			/* Destination TX Interface ID */
	uint8_t dest_rxif;			/* Destination RX Interface ID */
#ifdef CONFIG_HAVE_DMAC
	volatile uint32_t rep_count;/* repeat count in auto mode */
#endif
	volatile uint8_t state;		/* Channel State */

	struct _dma_sg_desc* sg_list;
};

struct _dma_transfer_cfg {
	const void* saddr;
	void* daddr;
	uint32_t len;
};

struct _dma_cfg {
	uint32_t data_width;
	uint32_t chunk_size;
	bool incr_saddr;
	bool incr_daddr;
	bool loop; /* Used by scatter/gather only */
};

struct _dma_controller {
	uint32_t pid;
#if defined(CONFIG_HAVE_XDMAC)
	Xdmac* hw;
#elif defined(CONFIG_HAVE_DMAC)
	Dmac* hw;
#endif
	struct _dma_channel channels[DMA_CHANNELS];
};

/**     @}*/

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/** \addtogroup dma_functions DMA Driver functions
		@{*/

/**
 * \brief Initialize DMA driver instance.
 * \param polling if true, interrupts will not be configured and dma_poll
 * must be called to poll for transfer completion
 */
extern void dma_initialize(bool polling);

/**
 * \brief Poll for transfers completion.
 * If polling mode is enabled, this function will call callbacks for completed
 * transfers.  If interrupt mode is enabled, this function will do nothing.
 */
extern void dma_poll(void);

/**
 * \brief Enable clock of the DMA peripheral, Enable the peripheral,
 * setup configuration register for transfer.
 * \param channel Channel pointer
 */
extern int dma_prepare_channel(struct _dma_channel* channel);

/**
 * \brief Allocate an DMA channel
 * \param src Source peripheral ID, DMA_PERIPH_MEMORY for memory.
 * \param dest Destination peripheral ID, DMA_PERIPH_MEMORY for memory.
 * \return Channel pointer if allocation successful, or NULL if channel
 * allocation failed.
 */
extern struct _dma_channel* dma_allocate_channel(uint8_t src, uint8_t dest);

/**
 * \brief Start DMA transfer.
 * \param channel Channel pointer
 */
extern int dma_start_transfer(struct _dma_channel* channel);

/**
 * \brief Set the callback function for an DMA channel transfer.
 * \param channel Channel pointer
 * \param callback Pointer to callback function.
 * \param user_arg Pointer to user argument for callback.
 */
extern int dma_set_callback(struct _dma_channel* channel, struct _callback* callback);

/**
 * \brief Configure DMA for a transfer of contiguous data.
 * \param channel Channel pointer
 * \param cfg_dma DMA transfer configuration
 * \param cfg     List of transfer specific configuration
 * \list_size     0: single/multi block transfer, 1-n: scatter/gather transfer
 * \return error code
 */
extern int dma_configure_transfer(struct _dma_channel* channel,
				  struct _dma_cfg* cfg_dma,
				  struct _dma_transfer_cfg* list,
				  uint8_t list_size);

/**
 * \brief Stop DMA transfer.
 * \param channel Channel pointer
 */
extern int dma_stop_transfer(struct _dma_channel* channel);

/**
 * \brief Suspend DMA transfer.
 * \param channel Channel pointer
 */
extern int dma_suspend_transfer(struct _dma_channel* channel);

/**
 * \brief Resume DMA transfer.
 * \param channel Channel pointer
 */
extern int dma_resume_transfer(struct _dma_channel* channel);

/**
 * \brief Free the specified DMA channel.
 * \param channel Channel pointer
 */
extern int dma_free_channel(struct _dma_channel* channel);

/**
 * \brief Reset the specified DMA channel.
 * \param channel Channel pointer
 */
extern int dma_reset_channel(struct _dma_channel* channel);

/**
 * \brief Check if DMA transfer is finished.
 * \param channel Channel pointer
 */
extern bool dma_is_transfer_done(struct _dma_channel* channel);

/**
 * \brief Flush FIFO of DMA.
 * \param channel Channel pointer
 */
extern void dma_fifo_flush(struct _dma_channel* channel);

/**
 * \brief Transferred data by DMA
 * \param channel Channel pointer
 * \param chunk_size Size of a data chunk
 * \param len Length of data to transfer
 */
extern uint32_t dma_get_transferred_data_len(struct _dma_channel* channel, uint8_t chunk_size, uint32_t len);

/**
 * \brief DMA interrupt handler
 * \param source Peripheral ID of DMA controller
 */
extern void dma_irq_handler(uint32_t source, void* user_arg);

/**     @}*/

#endif /* _DMA_H_ */
