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

/** \file */

/*-------------------------------------------------------------------------
 *        Headers
 *------------------------------------------------------------------------*/

#include "peripherals/xdmad.h"

#include "nand_flash_dma.h"

#include <assert.h>
#include <stdlib.h>

/*--------------------------------------------------------------------------
 *        Local Variables
 *------------------------------------------------------------------------*/

/* DMA driver instance */
static struct _xdmad_channel *nand_dma_rx_channel;
static struct _xdmad_channel *nand_dma_tx_channel;

/** DMA transfer completion notifier */
static volatile bool transfer_complete = false;

/*-------------------------------------------------------------------------
 *        Local functions
 *------------------------------------------------------------------------*/

/**
 * \brief Callback function called when DMA transfer is completed
 */
static void _nand_dma_callback(struct _xdmad_channel *channel, void *arg)
{
	transfer_complete = true;
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
uint8_t nand_dma_configure( void)
{
	/* Allocate a DMA channel for NAND RX. */
	nand_dma_rx_channel = xdmad_allocate_channel(
								XDMAD_PERIPH_MEMORY, XDMAD_PERIPH_MEMORY);
	assert(nand_dma_rx_channel);
	xdmad_set_callback(nand_dma_rx_channel, _nand_dma_callback, NULL);
	xdmad_prepare_channel(nand_dma_rx_channel);

	/* Allocate a DMA channel for NAND TX. */
	nand_dma_tx_channel = xdmad_allocate_channel(
								XDMAD_PERIPH_MEMORY, XDMAD_PERIPH_MEMORY);
	assert(nand_dma_tx_channel);
	xdmad_prepare_channel(nand_dma_tx_channel);
	xdmad_set_callback(nand_dma_tx_channel, _nand_dma_callback, NULL);
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
uint8_t nand_dma_write(uint32_t src_address,
						uint32_t dest_address,
						uint32_t size)
{
	struct _xdmad_cfg xdmadCfg;

	xdmadCfg.ubc = size;
	xdmadCfg.sa = (uint32_t *)src_address;
	xdmadCfg.da = (uint32_t *)dest_address;
	xdmadCfg.cfg = XDMAC_CC_TYPE_MEM_TRAN
	             | XDMAC_CC_MEMSET_NORMAL_MODE
	             | XDMAC_CC_CSIZE_CHK_1
	             | XDMAC_CC_DWIDTH_BYTE
	             | XDMAC_CC_SIF_AHB_IF0
	             | XDMAC_CC_DIF_AHB_IF0
	             | XDMAC_CC_SAM_INCREMENTED_AM
	             | XDMAC_CC_DAM_INCREMENTED_AM;
	xdmadCfg.bc = 0;
	xdmadCfg.ds = 0;
	xdmadCfg.sus = 0;
	xdmadCfg.dus = 0;
	xdmad_configure_transfer( nand_dma_tx_channel, &xdmadCfg, 0, 0);

	/* Start transfer */
	transfer_complete = false;
	xdmad_start_transfer(nand_dma_tx_channel);
	/* Wait for completion */
	while (!transfer_complete) {
		/* always call xdmad_poll, it will do nothing if polling mode
		 * is disabled */
		xdmad_poll();
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
uint8_t nand_dma_read(uint32_t src_address,
						uint32_t dest_address,
						uint32_t size)
{
	struct _xdmad_cfg xdmadCfg;

	xdmadCfg.ubc = size;
	xdmadCfg.sa = (uint32_t *)src_address;
	xdmadCfg.da = (uint32_t * )dest_address;
	xdmadCfg.cfg = XDMAC_CC_TYPE_MEM_TRAN
	             | XDMAC_CC_MEMSET_NORMAL_MODE
	             | XDMAC_CC_CSIZE_CHK_1
	             | XDMAC_CC_DWIDTH_BYTE
	             | XDMAC_CC_SIF_AHB_IF0
	             | XDMAC_CC_DIF_AHB_IF0
	             | XDMAC_CC_SAM_INCREMENTED_AM
	             | XDMAC_CC_DAM_INCREMENTED_AM;
	xdmadCfg.bc = 0;
	xdmadCfg.ds = 0;
	xdmadCfg.sus = 0;
	xdmadCfg.dus = 0;
	xdmad_configure_transfer( nand_dma_rx_channel, &xdmadCfg, 0, 0);

	/* Start transfer */
	transfer_complete = false;
	xdmad_start_transfer(nand_dma_rx_channel);
	/* Wait for completion */
	while (!transfer_complete) {
		/* always call xdmad_poll, it will do nothing if polling mode
		 * is disabled */
		xdmad_poll();
	}
	return 0;
}

/**
 * \brief Free the NAND DMA RX and TX channel.
 */
void nand_dma_free( void )
{
	while(xdmad_free_channel(nand_dma_rx_channel ));
	while(xdmad_free_channel(nand_dma_tx_channel ));
}

