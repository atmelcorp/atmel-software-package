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

/** \file */

/*-------------------------------------------------------------------------
 *        Headers
 *------------------------------------------------------------------------*/

#include <assert.h>
#include <stdlib.h>

#include "callback.h"
#include "dma/dma.h"
#include "mm/cache.h"
#include "nand_flash_common.h"
#include "nand_flash_dma.h"

/*--------------------------------------------------------------------------
 *        Local Variables
 *------------------------------------------------------------------------*/

/* DMA driver instance */
static struct _dma_channel *nand_dma_rx_channel;
static struct _dma_channel *nand_dma_tx_channel;

/** DMA transfer completion notifier */
static volatile bool transfer_complete = false;

/*-------------------------------------------------------------------------
 *        Local functions
 *------------------------------------------------------------------------*/

/**
 * \brief Callback function called when DMA transfer is completed
 */
static int _nand_dma_callback(void* arg, void* arg2)
{
	transfer_complete = true;

	return 0;
}

/*--------------------------------------------------------------------------
 *        Exported functions
 *------------------------------------------------------------------------*/
/**
 * \brief Configure the DMA Channels.
 * Channels are disabled after configure.
 * \returns 0 if the DMA channel configuration successfully; otherwise returns
 * NandCommon_ERROR_XXX.
 */
uint8_t nand_dma_configure(void)
{
	struct _callback _cb;

	callback_set(&_cb, _nand_dma_callback, NULL);
	/* Allocate a DMA channel for NAND RX. */
	nand_dma_rx_channel = dma_allocate_channel(
			DMA_PERIPH_MEMORY, DMA_PERIPH_MEMORY);
	assert(nand_dma_rx_channel);
	dma_set_callback(nand_dma_rx_channel, &_cb);

	/* Allocate a DMA channel for NAND TX. */
	nand_dma_tx_channel = dma_allocate_channel(
			DMA_PERIPH_MEMORY, DMA_PERIPH_MEMORY);
	assert(nand_dma_tx_channel);
	dma_set_callback(nand_dma_tx_channel, &_cb);

	return 0;
}

/**
 * \brief Configure the DMA Channels for TX.
 * \param src_address Source address to be transferred.
 * \param dest_address Destination address to be transferred.
 * \param size Transfer size in byte.
 * \returns 0 if the DMA channel configuration and transfer successfully;
 * otherwise returns NandCommon_ERROR_XXX.
 */
uint8_t nand_dma_write(uint32_t src_address, uint32_t dest_address,
		uint32_t size)
{
	struct _dma_cfg cfg_dma;
	struct _dma_transfer_cfg cfg;

	dma_reset_channel(nand_dma_tx_channel);
	cache_clean_region((uint32_t *)src_address, size);

	cfg.saddr = (uint32_t *)src_address;
	cfg.daddr = (uint32_t *)dest_address;
	cfg.len = size;
	cfg_dma.incr_saddr = true;
	cfg_dma.incr_daddr = true;
	cfg_dma.loop = false;
	cfg_dma.data_width = DMA_DATA_WIDTH_BYTE;
	cfg_dma.chunk_size = DMA_CHUNK_SIZE_1;

	dma_configure_transfer(nand_dma_tx_channel, &cfg_dma, &cfg, 1);

	/* Start transfer */
	transfer_complete = false;
	dma_start_transfer(nand_dma_tx_channel);
	/* Wait for completion */
	while (!transfer_complete) {
		/* always call dma_poll, it will do nothing if polling mode
		 * is disabled */
		dma_poll();
	}
	return 0;
}

/**
 * \brief Configure the DMA Channels for RX.
 * \param src_address Source address to be transferred.
 * \param dest_address Destination address to be transferred.
 * \param size Transfer size in byte.
 * \returns 0 if the DMA channel configuration and transfer successfully;
 * otherwise returns NandCommon_ERROR_XXX.
 */
uint8_t nand_dma_read(uint32_t src_address, uint32_t dest_address,
		uint32_t size)
{
	struct _dma_cfg cfg_dma;
	struct _dma_transfer_cfg cfg;

	dma_reset_channel(nand_dma_rx_channel);
	cfg.saddr = (uint32_t *)src_address;
	cfg.daddr = (uint32_t *)dest_address;
	cfg.len = size;

	cfg_dma.incr_saddr = true;
	cfg_dma.incr_daddr = true;
	cfg_dma.loop = false;
	cfg_dma.data_width = DMA_DATA_WIDTH_BYTE;
	cfg_dma.chunk_size = DMA_CHUNK_SIZE_1;

	dma_configure_transfer(nand_dma_rx_channel, &cfg_dma, &cfg, 1);

	/* Start transfer */
	transfer_complete = false;
	dma_start_transfer(nand_dma_rx_channel);
	/* Wait for completion */
	while (!transfer_complete) {
		/* always call dma_poll, it will do nothing if polling mode
		 * is disabled */
		dma_poll();
	}
	cache_invalidate_region((uint32_t *)dest_address, size);
	return 0;
}

/**
 * \brief Free the NAND DMA RX and TX channel.
 */
void nand_dma_free(void)
{
	dma_free_channel(nand_dma_rx_channel);
	dma_free_channel(nand_dma_tx_channel);
}
