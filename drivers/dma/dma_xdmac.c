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

/*----------------------------------------------------------------------------
 *        Includes
 *----------------------------------------------------------------------------*/

#include <assert.h>

#include "callback.h"
#include "compiler.h"
#include "dma/dma.h"
#include "dma/dma_xdmac.h"
#include "errno.h"
#include "irq/irq.h"
#include "peripherals/pmc.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/* Compatibility for devices with no secure matrix */
#ifndef XDMAC_CC_PROT_UNSEC
#define XDMAC_CC_PROT_UNSEC 0
#endif

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Enable clock of the DMA peripheral, Enable the peripheral,
 * setup configuration register for transfer.
 * \param channel Channel pointer
 */
int dma_prepare_channel(struct _dma_channel* channel)
{
	Xdmac* xdmac = channel->hw;

	if (channel->state == DMA_STATE_FREE)
		return -EPERM;
	else if (channel->state == DMA_STATE_STARTED)
		return -EBUSY;

	/* Clear status */
	xdmac_get_global_channel_status(xdmac);
	xdmac_get_global_isr(xdmac);

	/* Enable clock of the DMA peripheral */
	pmc_configure_peripheral(get_xdmac_id_from_addr(xdmac), NULL, true);

	/* Clear status */
	xdmac_get_channel_isr(xdmac, channel->id);

	/* Disables XDMAC interrupt for the given channel */
	xdmac_disable_global_it(xdmac, 1 << channel->id);
	xdmac_disable_channel_it(xdmac, channel->id, -1);

	/* Disable the given dma channel */
	xdmac_disable_channel(xdmac, channel->id);
	xdmac_set_src_addr(xdmac, channel->id, 0);
	xdmac_set_dest_addr(xdmac, channel->id, 0);
	xdmac_set_block_control(xdmac, channel->id, 0);
	xdmac_set_channel_config(xdmac, channel->id, XDMAC_CC_PROT_UNSEC);
	xdmac_set_descriptor_addr(xdmac, channel->id, 0, 0);
	xdmac_set_descriptor_control(xdmac, channel->id, 0);

	return 0;
}

int xdmacd_configure_transfer(struct _dma_channel* channel,
			      struct _xdmacd_cfg *cfg,
			      uint32_t desc_cntrl,
			      void *desc_addr)
{
	if (channel->state == DMA_STATE_FREE)
		return -EPERM;
	else if (channel->state == DMA_STATE_STARTED)
		return -EBUSY;

	Xdmac* xdmac = channel->hw;
	const uint32_t first_view = desc_cntrl & XDMAC_CNDC_NDVIEW_Msk;

	cfg->cfg &= ~XDMAC_CC_PERID_Msk;
	if ((cfg->cfg & XDMAC_CC_TYPE_PER_TRAN) == XDMAC_CC_TYPE_PER_TRAN) {
		if ((cfg->cfg & XDMAC_CC_DSYNC) == XDMAC_CC_DSYNC_PER2MEM) {
			cfg->cfg |= XDMAC_CC_PERID(channel->src_rxif);
		} else {
			cfg->cfg |= XDMAC_CC_PERID(channel->dest_txif);
		}
	} else {
		/* Use PERID mask as 'unused peripheral number' for MEM2MEM */
		cfg->cfg |= XDMAC_CC_PERID_Msk;
	}

	/* Clear status */
	xdmac_get_global_isr(xdmac);
	xdmac_get_channel_isr(xdmac, channel->id);

	if ((desc_cntrl & XDMAC_CNDC_NDE) == XDMAC_CNDC_NDE_DSCR_FETCH_EN) {
		/* Linked List is enabled */
		if (first_view <= XDMAC_CNDC_NDVIEW_NDV2) {
			xdmac_set_block_control(xdmac, channel->id, cfg->bc);
			xdmac_set_data_stride_mem_pattern(xdmac, channel->id, cfg->ds);
			xdmac_set_src_microblock_stride(xdmac, channel->id, cfg->sus);
			xdmac_set_dest_microblock_stride(xdmac, channel->id, cfg->dus);
		}
		xdmac_set_channel_config(xdmac, channel->id, cfg->cfg);
		xdmac_set_descriptor_addr(xdmac, channel->id, desc_addr, 0);
		xdmac_set_descriptor_control(xdmac, channel->id, desc_cntrl);
		xdmac_disable_channel_it(xdmac, channel->id, XDMAC_CID_BID
					 | XDMAC_CID_LID | XDMAC_CID_DID
					 | XDMAC_CID_FID | XDMAC_CID_RBEID
					 | XDMAC_CID_WBEID | XDMAC_CID_ROID);
		xdmac_enable_channel_it(xdmac, channel->id, XDMAC_CIE_LIE);
	} else {
		/* Linked List is disabled. */
		xdmac_set_src_addr(xdmac, channel->id, cfg->sa);
		xdmac_set_dest_addr(xdmac, channel->id, cfg->da);
		xdmac_set_microblock_control(xdmac, channel->id, cfg->ubc);
		xdmac_set_block_control(xdmac, channel->id, cfg->bc);
		xdmac_set_data_stride_mem_pattern(xdmac, channel->id, cfg->ds);
		xdmac_set_src_microblock_stride(xdmac, channel->id, cfg->sus);
		xdmac_set_dest_microblock_stride(xdmac, channel->id, cfg->dus);
		xdmac_set_channel_config(xdmac, channel->id, cfg->cfg);
		xdmac_set_descriptor_addr(xdmac, channel->id, 0, 0);
		xdmac_set_descriptor_control(xdmac, channel->id, 0);
		xdmac_disable_channel_it(xdmac, channel->id, XDMAC_CID_LID);
		xdmac_enable_channel_it(xdmac, channel->id, XDMAC_CIE_BIE
					| XDMAC_CIE_LIE | XDMAC_CIE_DIE
					| XDMAC_CIE_FIE | XDMAC_CIE_RBIE
					| XDMAC_CIE_WBIE | XDMAC_CIE_ROIE);
	}
	return 0;
}

void dma_irq_handler(uint32_t source, void* user_arg)
{
	uint32_t chan, gis, gcs;
	struct _dma_controller* ctrl = (struct _dma_controller*)user_arg;
	Xdmac* xdmac = ctrl->hw;

	gis = xdmac_get_global_isr(xdmac);
	if ((gis & ((1ull << DMA_CHANNELS) - 1)) == 0)
		return;

	gcs = xdmac_get_global_channel_status(xdmac);
	for (chan = 0; chan < DMA_CHANNELS; chan++) {
		struct _dma_channel* channel = &ctrl->channels[chan];
		bool exec = false;

		if (!(gis & (1 << chan)))
			continue;
		if (channel->state == DMA_STATE_FREE)
			continue;

		if (!(gcs & (1 << chan))) {
			uint32_t cis = xdmac_get_channel_isr(xdmac, chan);

			if (cis & XDMAC_CIS_BIS) {
				if (!(xdmac_get_channel_it_mask(xdmac, chan) & XDMAC_CIM_LIM)) {
					channel->state = DMA_STATE_DONE;
					exec = 1;
				}
			}

			if (cis & XDMAC_CIS_LIS) {
				channel->state = DMA_STATE_DONE;
				exec = 1;
			}

			if (cis & XDMAC_CIS_DIS) {
				channel->state = DMA_STATE_DONE;
				exec = 1;
			}
		}

		/* Execute callback */
		if (exec)
			callback_call(&channel->callback, NULL);
	}
}
