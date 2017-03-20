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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <assert.h>

#include "compiler.h"
#include "dma/dma.h"
#include "dma/dma_dmac.h"
#include "errno.h"
#include "irq/irq.h"
#include "peripherals/pmc.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#ifdef CONFIG_SOC_SAM9XX5
#define DMAC_CFG_SRC_PER_MSB_Msk 0
#define DMAC_CFG_DST_PER_MSB_Msk 0
#define DMAC_CFG_SRC_PER_MSB(x) 0
#define DMAC_CFG_DST_PER_MSB(x) 0
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
	Dmac *dmac = channel->hw;

	if (channel->state == DMA_STATE_FREE)
		return -EPERM;
	else if (channel->state == DMA_STATE_STARTED)
		return -EBUSY;

	/* Clear status */
	dmac_get_global_isr(dmac);

	/* Enable clock of the DMA peripheral */
	pmc_configure_peripheral(get_dmac_id_from_addr(dmac), NULL, true);

	/* Clear status */
	dmac_get_channel_status(dmac);

	/* Disables DMAC interrupt for the given channel */
	dmac_disable_global_it(dmac, -1);

	dmac_enable(dmac);
	/* Disable the given dma channel */
	dmac_disable_channel(dmac, channel->id);
	dmac_set_src_addr(dmac, channel->id, 0);
	dmac_set_dest_addr(dmac, channel->id, 0);

	dmac_set_channel_config(dmac, channel->id, 0);
	dmac_set_descriptor_addr(dmac, channel->id, 0, 0);

	return 0;
}

int dmacd_configure_transfer(struct _dma_channel* channel,
			     struct _dmacd_cfg* cfg,
			     struct _dmac_desc* desc)
{
	Dmac *dmac = channel->hw;
	uint32_t ctrlb;

	if (channel->state == DMA_STATE_FREE)
		return -EPERM;
	else if (channel->state == DMA_STATE_STARTED)
		return -EBUSY;

	ctrlb = desc->ctrlb;

	cfg->cfg &= ~(DMAC_CFG_SRC_PER_Msk | DMAC_CFG_SRC_PER_MSB_Msk |
	              DMAC_CFG_DST_PER_Msk | DMAC_CFG_DST_PER_MSB_Msk);

	if ((ctrlb & DMAC_CTRLB_FC_Msk) == DMAC_CTRLB_FC_PER2MEM_DMA_FC) {
		cfg->cfg |= DMAC_CFG_SRC_PER(channel->src_rxif);
		cfg->cfg |= DMAC_CFG_SRC_PER_MSB(channel->src_rxif >> 4);
	}

	if ((ctrlb & DMAC_CTRLB_FC_Msk) == DMAC_CTRLB_FC_MEM2PER_DMA_FC) {
		cfg->cfg |= DMAC_CFG_DST_PER(channel->dest_txif);
		cfg->cfg |= DMAC_CFG_DST_PER_MSB(channel->dest_txif >> 4);
	}

	dmac_get_global_isr(dmac);
	dmac_get_channel_status(dmac);

	/* if DMAC_CTRLBx.AUTO bit is enabled, and source or destination is not fetched
		from linker list, set the channel with AUTO mode, in this mode, the hardware
		sets the Buffer Transfer Completed Interrupt when the buffer transfer has
		completed, It then stalls until STALx bit of DMAC_CHSR is cleared by writing
		in the KEEPx bit of DMAC_CHER */
	if (cfg->trans_auto) {
		if ((cfg->s_decr_fetch) && (cfg->d_decr_fetch)){
			ctrlb |= DMAC_CTRLB_AUTO_ENABLE;
			channel->rep_count = cfg->blocks;
		}
	}

	dmac_set_descriptor_addr(dmac, channel->id, 0, 0);

	if (cfg->s_decr_fetch)
		/* *Buffer Descriptor fetch operation is disabled for the source */
		dmac_set_src_addr(dmac, channel->id, desc->saddr);
	else
		/* Source address is updated when the descriptor is fetched from the memory */
		dmac_set_descriptor_addr(dmac, channel->id, desc, 0);

	if (cfg->d_decr_fetch)
		/* *Buffer Descriptor fetch operation is disabled for the destination */
		dmac_set_dest_addr(dmac, channel->id, desc->daddr);
	else
		/* destination address is updated when the descriptor is fetched from the memory */
		dmac_set_descriptor_addr(dmac, channel->id, desc, 0);

	dmac_set_control_a(dmac, channel->id, desc->ctrla);
	dmac_set_control_b(dmac, channel->id, ctrlb);
	dmac_set_channel_config(dmac, channel->id, cfg->cfg);

	return 0;
}

void dma_irq_handler(uint32_t source, void* user_arg)
{
	uint32_t chan, gis;
	struct _dma_controller* ctrl = (struct _dma_controller*)user_arg;
	Dmac* dmac = ctrl->hw;

	gis = dmac_get_global_isr(dmac);
	if ((gis & 0xFFFFFFFF) == 0)
		return;

	for (chan = 0; chan < DMA_CHANNELS; chan++) {
		struct _dma_channel* channel = &ctrl->channels[chan];
		bool exec = false;
		if (!(gis & ((DMAC_EBCISR_BTC0 | DMAC_EBCISR_CBTC0 | DMAC_EBCISR_ERR0) << chan)))
			continue;
		if (channel->state == DMA_STATE_FREE)
			continue;
		if (gis & (DMAC_EBCISR_CBTC0 << chan)) {
			if (channel->rep_count) {
				if (channel->rep_count == 1) {
					dmac_auto_clear(dmac, chan);
				}
				dmac_resume_channel(dmac, chan);
				channel->rep_count--;

			} else {
				channel->state = DMA_STATE_DONE;
				exec = 1;
			}
		}
		/* Execute callback */
		if (exec)
			callback_call(&channel->callback, NULL);
	}
}
