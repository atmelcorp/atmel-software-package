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

#include "chip.h"
#if defined(CONFIG_HAVE_DMAC)
#include "dma/dmacd.h"
#elif defined(CONFIG_HAVE_XDMAC)
#include "dma/xdmacd.h"
#else
#error "Requires a DMA controller to be enabled"
#endif

/*------------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

#define DMA_PERIPH_MEMORY  0xFF

#ifdef CONFIG_HAVE_XDMAC
#define DMA_MAX_BT_SIZE    XDMAC_MAX_BT_SIZE
#define DMA_MAX_BLOCK_LEN  XDMAC_MAX_BLOCK_LEN

#elif defined(CONFIG_HAVE_DMAC)
#define DMA_MAX_BT_SIZE    DMAC_MAX_BT_SIZE
#define DMA_MAX_BLOCK_LEN  DMAC_MAX_BLOCK_LEN
#endif

#define DMA_DATA_WIDTH_BYTE        0
#define DMA_DATA_WIDTH_HALF_WORD   1
#define DMA_DATA_WIDTH_WORD        2
#if defined(CONFIG_HAVE_XDMAC_DATA_WIDTH_DWORD) ||\
    defined(CONFIG_HAVE_DMAC_DATA_WIDTH_DWORD)
#define DMA_DATA_WIDTH_DWORD       3
#endif

#ifdef CONFIG_HAVE_XDMAC
#define DMA_CHUNK_SIZE_1   0
#define DMA_CHUNK_SIZE_2   1
#define DMA_CHUNK_SIZE_4   2
#define DMA_CHUNK_SIZE_8   3
#define DMA_CHUNK_SIZE_16  4

#elif defined(CONFIG_HAVE_DMAC)
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

/** DMA channel */
struct dma_channel;

/** DMA transfer completion callback */
typedef void (*dma_callback_t)(struct dma_channel *channel, void *arg);

/* Set of parameters to specify a transfer of contiguous data.
   Structure members that are zeroed will get assigned their default value.*/
struct dma_xfer_cfg {
	uint8_t upd_sa_per_data : 1; /* increment source address when proceeding to the next data element (set by default if memory)
					0: The source address remains unchanged
					1: The source address is incremented */

	uint8_t upd_da_per_data : 1;/* increment destination address when proceeding to the next data element (set by default if memory)
				       0: The destination address remains unchanged
				       1: The destination address is incremented */
	void* sa; /* initial source address; alignment shall match data width */
	void* da; /* initial destination address; alignment shall match data width */

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
extern struct dma_channel* dma_allocate_channel(uint8_t src, uint8_t dest);

/**
 * \brief Start DMA transfer.
 * \param channel Channel pointer
 */
extern int dma_start_transfer(struct dma_channel *channel);

/**
 * \brief Set the callback function for an DMA channel transfer.
 * \param channel Channel pointer
 * \param callback Pointer to callback function.
 * \param user_arg Pointer to user argument for callback.
 */
extern int dma_set_callback(struct dma_channel *channel,
				dma_callback_t callback, void *user_arg);

/**
 * \brief Configure DMA for a transfer of contiguous data.
 * \param channel Channel pointer
 * \param cfg DMA transfer configuration
 * \return error code
 */
extern int dma_configure_transfer(struct dma_channel *channel, const struct dma_xfer_cfg *cfg);

/**
 * \brief Prepare the provided transfer descriptor, AKA linked list item.
 * \param channel Channel pointer
 * \param tmpl The transfer parameters to be used
 * \param item Pointer to the uninitialized transfer descriptor
 * \return result code
 */
extern int dma_sg_prepare_item(struct dma_channel *channel,
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
extern int dma_sg_link_item(struct dma_channel *channel,
			      struct dma_xfer_item *item,
			      struct dma_xfer_item *next_item);

/**
 * \brief Link the specified transfer descriptor at the end of current list.
 * \param channel Channel pointer
 * \param item Pointer to the transfer descriptor to be amended.
 * \note The transfers descriptors pointed by item shall have
 * been allocated from linked list pool.
 * \return result code
 */
extern int dma_sg_link_last_item(struct dma_channel *channel,
		       struct dma_xfer_item *item);

/**
 * \brief insert the specified transfer descriptor to its successor in the list.
 * \param channel Channel pointer
 * \param pre_item Pointer to the previous transfer descriptor which to be linked
 * with new transfer descriptor. NULL if item will end the list.
 * \param item Pointer to the transfer descriptor to be inserted.
 * \param desc_list Linked list of transfer descriptors. Shall be word-aligned.
 * \note To insert a item at the end of linked list, the dma channel shall be
   suspended using dma_suspend_transfer. Then the transfers descriptors pointed by
   item shall have been properly initialized, using dma_prepare_item. Finally,
   using dma_resume_transfer to continue dma transfer.
 * \return result code
 */
extern int dma_sg_insert_item(struct dma_channel *channel,
				struct dma_xfer_item *pre_item,
				struct dma_xfer_item *item);

/**
 * \brief insert the specified transfer descriptor at the end of its linked list.
 * \param channel Channel pointer
 * \param item Pointer to the transfer descriptor to be inserted.
 * \param desc_list Linked list of transfer descriptors. Shall be word-aligned.
 * \note To insert a item at the end of linked list, the dma channel shall be
   suspended using dma_suspend_transfer. Then the transfers descriptors pointed by
   item shall have been properly initialized, using dma_prepare_item. Finally,
   using dma_resume_transfer to continue dma transfer.
 * \return result code
 */
extern int dma_sg_append_item(struct dma_channel *channel,
				struct dma_xfer_item *item);

/**
 * \brief Delete the last transfer descriptor of its linked list.
 * \param channel Channel pointer
 * \note To delect the last item of linked list, the dma channel shall be
   suspended using dma_suspend_transfer, and using dma_resume_transfer to
   continue dma transfer after the item was delected.
 * \return result code
 */
extern int dma_sg_remove_last_item(struct dma_channel *channel);

/**
 * \brief Configure DMA for a transfer of scattered data, or a transfer of
 * contiguous data that may be reconfigured on a block-by-block basis.
 * \param channel Channel pointer
 * \param tmpl The parameters that were used to prepare the first transfer
 * descriptor in the list.
 * \param desc_list Linked list of transfer descriptors. Shall be word-aligned.
 * NULL if the list was allocated from linked list pool.
 * \return result code
 */
extern int dma_sg_configure_transfer(struct dma_channel *channel,
				     struct dma_xfer_item_tmpl *tmpl,
				     struct dma_xfer_item *desc_list);

/**
 * \brief Stop DMA transfer.
 * \param channel Channel pointer
 */
extern int dma_stop_transfer(struct dma_channel *channel);

/**
 * \brief Suspend DMA transfer.
 * \param channel Channel pointer
 */
extern int dma_suspend_transfer(struct dma_channel *channel);

/**
 * \brief Resume DMA transfer.
 * \param channel Channel pointer
 */
extern int dma_resume_transfer(struct dma_channel *channel);

/**
 * \brief Free the specified DMA channel.
 * \param channel Channel pointer
 */
extern int dma_free_channel(struct dma_channel *channel);

/**
 * \brief Reset the specified DMA channel.
 * \param channel Channel pointer
 */
extern int dma_reset_channel(struct dma_channel *channel);

/**
 * \brief Check if DMA transfer is finished.
 * \param channel Channel pointer
 */
extern bool dma_is_transfer_done(struct dma_channel *channel);

/**
 * \brief Flush FIFO of DMA.
 * \param channel Channel pointer
 */
extern void dma_fifo_flush(struct dma_channel *channel);

/**
 * \brief Transferred data by DMA
 * \param channel Channel pointer
 * \param chunk_size Size of a data chunk
 * \param len Length of data to transfer
 */
extern uint32_t dma_get_transferred_data_len(struct dma_channel *channel, uint8_t chunk_size, uint32_t len);

/**
 * \brief Get next descriptor's address for the relevant channel
 * \param channel Channel pointer
 */
extern struct dma_xfer_item* dma_get_desc_addr(struct dma_channel *channel);

/**
 * \brief Allocate a unused linked list emelment the relevant channel
 * \param channel Channel pointer
 * \return linked list pointer if allocation successful, or NULL if allocation
 * failed.
 */
extern struct dma_xfer_item* dma_sg_allocate_item(struct dma_channel *channel);

/**
 * \brief Free all linked list elements for the relevant channel
 * \param channel Channel pointer
 */
extern void dma_sg_free_item(struct dma_channel *channel);
/**     @}*/

#endif /* _DMA_H_ */
