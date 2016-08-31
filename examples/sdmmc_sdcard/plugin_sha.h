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
 *
 * This module implements routines to compute the SHA-1 (Secure Hash Algorithm)
 * hash of a binary stream.
 * The stream may be split in successive blocks of varying size.
 * The final size of the stream is not required to be known in advance.
 * ----------------------------------------------------------------------------
 */

#ifdef CONFIG_HAVE_SHA

#ifndef _SHA_PLUG_IN_
#define _SHA_PLUG_IN_

#include <stdint.h>
#include <stdbool.h>

#include "mutex.h"
#include "peripherals/dma.h"

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

struct dma_xfer {
	struct dma_xfer_item dma_item;
	uint32_t blk_size;   /**< Size */
	void *src_addr;      /**< Source Address */
};

/* This structure is private to the SHA plug-in.
 * Allocate it but ignore its members. */
struct sha_set
{
	uint8_t *pending_data;    /* Excess data not processed yet */
	uint32_t count;           /* Number of bytes processed */
	uint8_t pending;          /* Number of excess bytes */
	struct dma_channel *dma_ch;
				      /* xDMA instance, or NULL when DMA is not
				       * used */
	struct dma_xfer *dma_dlist;
				      /* xDMA linked list of xfer descriptors,
				       * stored contiguously as a table */
	uint32_t dlist_len; /* Count of descriptors added to the xDMA
				            linked list */
	bool dma_polling;  /* use dma polling mode */
	mutex_t dma_unlocks_mutex;
};

/*----------------------------------------------------------------------------*/
/*         Exported functions                                                 */
/*----------------------------------------------------------------------------*/

/**
 * \brief Initialize the driver and the SHA peripheral.
 * \param set  Pointer to uninitialized driver instance data.
 * \param use_dma  True to use DMA. False to have the CPU write data, word by
 * word.
 */
extern void sha_plugin_initialize(struct sha_set *set, bool use_dma);

/**
 * \brief Provide message data.
 * \param set  Pointer to driver instance data.
 * \param open  True to start a new message (a new hash). False to append data
 * to the current message (continue hashing).
 * \param close  True to complete the current message and add implicit padding.
 * False to append data to the current message (defer padding).
 * \param data  Data chunk to append to the message. Shall be word-aligned.
 * Not padded; the driver will pad the message as per FIPS requirement.
 * If DMA is used: the caller shall ensure that these data bytes can be fetched
 * directly from RAM; typically the underlying cache lines should have been
 * cleaned.
 * Upon return of this function, the data will have been entirely copied, hence
 * this buffer is allowed to become invalid then.
 * \param count  Size of the data chunk, in bytes.
 */
extern void sha_plugin_feed(struct sha_set *set, bool open, bool close,
    const uint8_t *data, uint32_t count);

/**
 * \brief Get the resulting SHA-1.
 * The caller will have previously opened, written and closed the message with
 * one or several calls to sha_plugin_feed().
 * \param set  Pointer to driver instance data.
 * \param hash  Table the resulting 160-bit hash will be written to.
 */
extern void sha_plugin_get_hash(struct sha_set *set, uint32_t hash[5]);

#endif /* !_SHA_PLUG_IN_ */

#endif /* CONFIG_HAVE_SHA */

