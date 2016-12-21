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
 *        Local constants
 *----------------------------------------------------------------------------*/

static Xdmac* controllers[] = {
#ifdef XDMAC0
	XDMAC0,
#endif
#ifdef XDMAC1
	XDMAC1,
#endif
};

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/* Compatibility for devices with no secure matrix */
#ifndef XDMAC_CC_PROT_UNSEC
#define XDMAC_CC_PROT_UNSEC 0
#endif

#define XDMAC_CONTROLLERS ARRAY_SIZE(controllers)
#define XDMACD_CHANNELS (XDMAC_CONTROLLERS * XDMAC_CHANNELS)

/** DMA driver instance */
struct _xdmacd {
	struct _dma_channel channels[XDMACD_CHANNELS];
	bool                polling;
	uint8_t             polling_timeout;
};

static struct _xdmacd _xdmacd;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Enable clock of the DMA peripheral, Enable the peripheral,
 * setup configuration register for transfer.
 * \param channel Channel pointer
 */
static int _xdmacd_prepare_channel(struct _dma_channel* channel)
{
	Xdmac* xdmac = channel->xdmac;

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

static struct _dma_channel* _xdmacd_channel(Xdmac* dmac, uint32_t channel)
{
	int i;
	struct _dma_channel* ch = NULL;
	for (i = 0; i < ARRAY_SIZE(controllers); i++) {
		if (controllers[i] == dmac)
			ch = &_xdmacd.channels[i * XDMAC_CHANNELS + channel];
	}
	assert(ch != NULL);
	return ch;
}

/**
 * \brief xDMA interrupt handler
 * \param source Peripheral ID of DMA controller
 */
static void _xdmacd_handler(uint32_t source, void* user_arg)
{
	uint32_t chan, gis, gcs;
	Xdmac* xdmac = (Xdmac*)user_arg;

	gis = xdmac_get_global_isr(xdmac);
	if ((gis & 0xFFFF) == 0)
		return;

	gcs = xdmac_get_global_channel_status(xdmac);
	for (chan = 0; chan < XDMAC_CHANNELS; chan++) {
		struct _dma_channel* channel;
		bool exec = false;

		if (!(gis & (1 << chan)))
			continue;

		channel = _xdmacd_channel(xdmac, chan);
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
		if (exec) {
			callback_call(&channel->callback);
		}
	}
}


/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void xdmacd_initialize(bool polling)
{
	uint32_t cont, chan;

	_xdmacd.polling = polling;

	for (cont = 0; cont < XDMAC_CONTROLLERS; cont++) {
		Xdmac* xdmac = controllers[cont];
		for (chan = 0; chan < XDMAC_CHANNELS; chan++) {
			xdmac_get_channel_isr(xdmac, chan);
			struct _dma_channel* channel = _xdmacd_channel(xdmac, chan);
			channel->xdmac = xdmac;
			channel->id = chan;
			callback_set(&channel->callback, NULL, NULL);
			channel->src_txif = 0;
			channel->src_rxif = 0;
			channel->dest_txif = 0;
			channel->dest_rxif = 0;
			channel->state = DMA_STATE_FREE;
		}

		if (!polling) {
			uint32_t pid = get_xdmac_id_from_addr(xdmac);
			/* enable interrupts */
			irq_add_handler(pid, _xdmacd_handler, xdmac);
			irq_enable(pid);
		}
	}
}

void dma_poll(void)
{
	if (_xdmacd.polling) {
		int i;
		for (i = 0; i < XDMAC_CONTROLLERS; i++)
			_xdmacd_handler(get_xdmac_id_from_addr(controllers[i]), controllers[i]);
	}
}

struct _dma_channel* dma_allocate_channel(uint8_t src, uint8_t dest)
{
	uint32_t i;

	/* Reject peripheral to peripheral transfers */
	if (src != XDMACD_PERIPH_MEMORY && dest != XDMACD_PERIPH_MEMORY) {
		return NULL;
	}

	for (i = 0; i < XDMACD_CHANNELS; i++) {
		struct _dma_channel* channel = &_xdmacd.channels[i];
		Xdmac* xdmac = channel->xdmac;

		if (channel->state == DMA_STATE_FREE) {
			/* Check if source peripheral matches this channel controller */
			if (src != XDMACD_PERIPH_MEMORY)
				if (!is_peripheral_on_xdma_controller(src, xdmac))
					continue;

			/* Check if destination peripheral matches this channel controller */
			if (dest != XDMACD_PERIPH_MEMORY)
				if (!is_peripheral_on_xdma_controller(dest, xdmac))
					continue;

			/* Allocate the channel */
			channel->state = DMA_STATE_ALLOCATED;
			channel->src_txif = get_peripheral_xdma_channel(src, xdmac, true);
			channel->src_rxif = get_peripheral_xdma_channel(src, xdmac, false);
			channel->dest_txif = get_peripheral_xdma_channel(dest, xdmac, true);
			channel->dest_rxif = get_peripheral_xdma_channel(dest, xdmac, false);

			_xdmacd_prepare_channel(channel);

			channel->sg_list = NULL;

			return channel;
		}
	}
	return NULL;
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

	Xdmac* xdmac = channel->xdmac;
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
		xdmac_disable_channel_it(xdmac, channel->id,
					 XDMAC_CID_BID | XDMAC_CID_DID |
					 XDMAC_CID_FID | XDMAC_CID_RBEID |
					 XDMAC_CID_WBEID | XDMAC_CID_ROID);
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
		xdmac_enable_channel_it(xdmac, channel->id,
					XDMAC_CIE_BIE | XDMAC_CIE_DIE |
					XDMAC_CIE_FIE | XDMAC_CIE_RBIE |
					XDMAC_CIE_WBIE | XDMAC_CIE_ROIE);
	}
	return 0;
}

int dma_start_transfer(struct _dma_channel* channel)
{
	if (channel->state == DMA_STATE_FREE)
		return -EPERM;
	else if (channel->state == DMA_STATE_STARTED)
		return -EBUSY;

	/* Change state to 'started' */
	channel->state = DMA_STATE_STARTED;

	/* Start DMA transfer */
	xdmac_enable_channel(channel->xdmac, channel->id);
	if (!_xdmacd.polling) {
		xdmac_enable_global_it(channel->xdmac, 1 << channel->id);
	}

	return 0;
}

int dma_stop_transfer(struct _dma_channel* channel)
{
	Xdmac* xdmac = channel->xdmac;

	/* Disable channel */
	xdmac_disable_channel(xdmac, channel->id);

	/* Disable interrupts */
	xdmac_disable_channel_it(xdmac, channel->id, -1);

	/* Clear pending status */
	xdmac_get_channel_isr(xdmac, channel->id);
	xdmac_get_global_channel_status(xdmac);

	/* Change state to 'allocated' */
	channel->state = DMA_STATE_ALLOCATED;

	return 0;
}

int dma_reset_channel(struct _dma_channel* channel)
{
	Xdmac* xdmac = channel->xdmac;

	if (channel->state == DMA_STATE_ALLOCATED)
		return 0;

	if (channel->state == DMA_STATE_STARTED)
		return -EBUSY;

	/* Disable channel */
	xdmac_disable_channel(xdmac, channel->id);

	/* Disable interrupts */
	xdmac_disable_channel_it(xdmac, channel->id, -1);

	/* Change state to 'allocated' */
	channel->state = DMA_STATE_ALLOCATED;

	return 0;
}

int dma_suspend_transfer(struct _dma_channel* channel)
{
	Xdmac* xdmac = channel->xdmac;

	/* suspend channel */
	xdmac_suspend_channel(xdmac, channel->id);

	/* Change state to 'suspended' */
	channel->state = DMA_STATE_SUSPENDED;

	return 0;
}

int dma_resume_transfer(struct _dma_channel* channel)
{
	Xdmac* xdmac = channel->xdmac;

	/* resume dedicated channel */
	xdmac_resume_read_write_channel(xdmac, channel->id);

	/* Change state to 'started' */
	channel->state = DMA_STATE_STARTED;

	return 0;
}

uint32_t xdmacd_get_remaining_data_len(struct _dma_channel* channel)
{
	Xdmac* xdmac = channel->xdmac;

	return xdmac_get_microblock_control(xdmac, channel->id);
}

void dma_fifo_flush(struct _dma_channel* channel)
{
	Xdmac* xdmac = channel->xdmac;

	xdmac_fifo_flush(xdmac, channel->id);
}
