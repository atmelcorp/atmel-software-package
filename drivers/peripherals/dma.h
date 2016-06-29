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

#include "chip.h"


#if defined(CONFIG_HAVE_XDMAC)
#include "peripherals/xdmad.h"
#elif defined(CONFIG_HAVE_DMAC)
#include "peripherals/dmacd.h"
#else
#  error "Requires a DMA controller to be enabled"
#endif
#include <stdbool.h>


/*------------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/
#define DMA_PERIPH_MEMORY  0xFF

#ifdef CONFIG_HAVE_XDMAC
/* Max DMA single transfer size */
#define DMA_MAX_BT_SIZE    XDMAC_MAX_BT_SIZE
#define DMA_MAX_BLOCK_LEN  XDMAC_MAX_BLOCK_LEN

#elif defined(CONFIG_HAVE_DMAC)
/* Max DMA single transfer size */
#define DMA_MAX_BT_SIZE    DMAC_MAX_BT_SIZE
#define DMA_MAX_BLOCK_LEN  0xFFFF
#endif

#define DMA_DATA_WIDTH_BYTE        0
#define DMA_DATA_WIDTH_HALF_WORD   1
#define DMA_DATA_WIDTH_WORD        2
#define DMA_DATA_WIDTH_DWORD       3

#ifdef CONFIG_HAVE_XDMAC

#define DMA_CHUNK_SIZE_1   0
#define DMA_CHUNK_SIZE_2   1
#define DMA_CHUNK_SIZE_4   2
#define DMA_CHUNK_SIZE_8   3
#define DMA_CHUNK_SIZE_16  4

#elif defined(CONFIG_HAVE_DMAC)
#define DMA_CHUNK_SIZE_1   0
#define DMA_CHUNK_SIZE_2   0
#define DMA_CHUNK_SIZE_4   1
#define DMA_CHUNK_SIZE_8   2
#define DMA_CHUNK_SIZE_16  3
#define DMA_CHUNK_SIZE_32  4
#define DMA_CHUNK_SIZE_64  5
#define DMA_CHUNK_SIZE_128 6
#define DMA_CHUNK_SIZE_256 7

#endif


/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/
/** DMA status or return code */
enum {
	DMA_OK = 0,				/* Operation is sucessful */
	DMA_PARTIAL_DONE,		/* Transfer partial finished */
	DMA_DONE,				/* Transfer finished */
	DMA_BUSY,				/* Channel occupied or transfer not finished */
	DMA_ERROR,				/* Operation failed */
	DMA_CANCELED			/* Operation canceled */
};

/** \addtogroup dma_structs DMA Driver Structs
		@{*/

/** DMA channel */
struct dma_channel;

/** DMA transfer completion callback */
typedef void (*dma_callback_t)(struct dma_channel *channel, void *arg);

/* Set of parameters to specify a transfer of contiguous data.
   Structure members that are zeroed will get assigned their default value.*/
struct dma_xfer_cfg {

	uint8_t upd_sa_per_data : 1;/* increment source address when proceeding to the next data element (set by default if memory)
									0: The source address remains unchanged
									1: The source address is incremented */

	uint8_t upd_da_per_data : 1;/* increment destination address when proceeding to the next data element (set by default if memory)
									0: The destination address remains unchanged
									1: The destination address is incremented */
	void *sa; 					/* initial source address; alignment shall match data width */
	void *da;					/* initial destination address; alignment shall match data width */

	uint8_t data_width;			/* data element width (AKA transfer width), expressed in bytes (1/2/4/8) */
	uint8_t chunk_size;			/* chunk size (if transferring with a peripheral), expressed in data elements (1/(2)/4/8/16) */
	uint32_t blk_size;			/* block size (optional), expressed in data elements */
	uint32_t len;				/* transfer length, expressed in data elements; if blk_size is non-zero, then len shall be a multiple of blk_size */
};

/** Types for specifying a transfer of scattered data, or a transfer of
 * contiguous data that may be reconfigured on a block-by-block basis. */

 /** Template structure used to gather the values required to fill a given
 * linked list item.
 * Structure members that are zeroed will get assigned their default value. */
struct dma_xfer_item_tmpl {

	uint8_t upd_sa_per_data : 1;/* increment source address when proceeding to the next data element (set by default if memory)
									0: The source address remains unchanged
									1: The source address is incremented */
	uint8_t upd_da_per_data : 1;/* increment destination address when proceeding to the next data element (set by default if memory)
									0: The destination address remains unchanged
									1: The destination address is incremented */
	uint8_t upd_sa_per_blk : 1;	/* update source address when proceeding to the next block when the descriptor is fetched from the memory.*/
	uint8_t upd_da_per_blk : 1;	/* update destination address when proceeding to the next block when the descriptor is fetched from the memory.*/
	const void *sa;				/* initial source address; alignment shall match data width */
	void* da;					/* initial destination address; alignment shall match data width */

	uint8_t data_width;			/* data element width (AKA transfer width), expressed in bytes (1/2/4/8) */
	uint8_t chunk_size;			/* chunk size (if transferring with a peripheral), expressed in data elements (1/(2)/4/8/16) */
	uint32_t blk_size;			/* block size, expressed in data elements */
};

/** Elementary transfer descriptor, AKA linked list item.
 * Allocate the items, but do not access their members. Please use the dedicated
 * functions defined below. */
#ifdef CONFIG_HAVE_XDMAC
struct dma_xfer_item {
	const void *mbr_nda;	/* Next Descriptor Address */
	uint32_t    mbr_ubc;	/* Microblock Control */
	const void *mbr_sa;		/* Source Address */
	void       *mbr_da;		/* Destination Address */
};
#elif defined(CONFIG_HAVE_DMAC)
struct dma_xfer_item {
	const void *saddr;		/* Source Address */
	void       *daddr;		/* Destination Address */
	uint32_t    ctrla;		/* Buffer Control A */
	uint32_t    ctrlb;		/* Buffer Control B */
	const void *dscr;		/* Next Descriptor Address */
};
#else
#  error "Requires a DMA controller to be enabled"
#endif

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
 * \brief Allocate an DMA channel
 * \param src Source peripheral ID, DMA_PERIPH_MEMORY for memory.
 * \param dest Destination peripheral ID, DMA_PERIPH_MEMORY for memory.
 * \return Channel pointer if allocation successful, or NULL if channel
 * allocation failed.
 */
extern struct dma_channel *dma_allocate_channel(uint8_t src, uint8_t dest);

/**
 * \brief Start DMA transfer.
 * \param channel Channel pointer
 */
extern uint32_t dma_start_transfer(struct dma_channel *channel);

/**
 * \brief Set the callback function for an DMA channel transfer.
 * \param channel Channel pointer
 * \param callback Pointer to callback function.
 * \param user_arg Pointer to user argument for callback.
 */
extern uint32_t dma_set_callback(struct dma_channel *channel,
				dma_callback_t callback, void *user_arg);

/**
 * \brief Configure DMA for a transfer of contiguous data.
 * \param channel Channel pointer
 * \param cfg DMA transfer configuration
 * \return result code
 */
extern uint32_t dma_configure_transfer(struct dma_channel *channel,
				const struct dma_xfer_cfg *cfg);

/**
 * \brief Prepare the provided transfer descriptor, AKA linked list item.
 * \param channel Channel pointer
 * \param tmpl The transfer parameters to be used
 * \param item Pointer to the uninitialized transfer descriptor
 * \return result code
 */
extern uint32_t dma_prepare_item(struct dma_channel *channel,
				const struct dma_xfer_item_tmpl *tmpl,
				struct dma_xfer_item *item);

/**
 * \brief Link the specified transfer descriptor to its successor in the list.
 * \param channel Channel pointer
 * \param item Pointer to the transfer descriptor to be amended.
 * \param next_item Pointer to the next transfer descriptor in the list. NULL if
 * item will end the list.
 * \note The transfers descriptors pointed by item and next_item shall have
 * been properly initialized, using dma_prepare_item.
 * \return result code
 */
extern uint32_t dma_link_item(struct dma_channel *channel,
				struct dma_xfer_item *item,
				struct dma_xfer_item *next_item);

/**
 * \brief Configure DMA for a transfer of scattered data, or a transfer of
 * contiguous data that may be reconfigured on a block-by-block basis.
 * \param channel Channel pointer
 * \param tmpl The parameters that were used to prepare the first transfer
 * descriptor in the list.
 * \param desc_list Linked list of transfer descriptors. Shall be word-aligned.
 * \return result code
 */
extern uint32_t dma_configure_sg_transfer(struct dma_channel *channel,
				struct dma_xfer_item_tmpl *tmpl,
				struct dma_xfer_item *desc_list);

/**
 * \brief Stop DMA transfer.
 * \param channel Channel pointer
 */
extern uint32_t dma_stop_transfer(struct dma_channel *channel);

/**
 * \brief Free the specified DMA channel.
 * \param channel Channel pointer
 */
extern uint32_t dma_free_channel(struct dma_channel *channel);

/**
 * \brief Check if DMA transfer is finished.
 * \param channel Channel pointer
 */
extern bool dma_is_transfer_done(struct dma_channel *channel);
/**     @}*/

#endif /* _DMA_H_ */
