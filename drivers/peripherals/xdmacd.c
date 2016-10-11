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

/** \addtogroup xdmacd_module
 *
 * \section Xdma xDma Configuration Usage
 *
 * To configure a XDMA channel, the user has to follow these few steps :
 * <ul>
 * <li> Initialize a XDMA driver instance by XDMACD_Initialize().</li>
 * <li> choose an available (disabled) channel using XDMACD_AllocateChannel().</li>
 * <li> After the XDMAC selected channel has been programmed, XDMACD_PrepareChannel() is to enable
 * clock and dma peripheral of the DMA, and set Configuration register to set up the transfer type
 * (memory or non-memory peripheral for source and destination) and flow control device.</li>
 * <li> Invoke XDMACD_StartTransfer() to start DMA transfer  or XDMACD_StopTransfer() to force stop DMA transfer.</li>
  * <li> Once the buffer of data is transferred, XDMACD_IsTransferDone() checks if DMA transfer is finished.</li>
 * <li> XDMACD_Handler() handles XDMA interrupt, and invoking XDMACD_SetCallback() if provided.</li>
 * </ul>
 *
 * Related files:\n
 * \ref xdmacd.h\n
 * \ref xdmacd.c\n
 */

/** \file */

/** \addtogroup dmad_functions
  @{*/

/*----------------------------------------------------------------------------
 *        Includes
 *----------------------------------------------------------------------------*/

#include "peripherals/aic.h"
#include "peripherals/pmc.h"
#include "peripherals/xdmacd.h"
#include "peripherals/dma.h"
#include <assert.h>
#include "compiler.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#define XDMACD_CHANNELS (XDMAC_CONTROLLERS * XDMAC_CHANNELS)

/** DMA state for channel */
enum {
	XDMACD_STATE_FREE = 0,  /**< Free channel */
	XDMACD_STATE_ALLOCATED, /**< Allocated to some peripheral */
	XDMACD_STATE_STARTED,   /**< DMA started */
	XDMACD_STATE_DONE,      /**< DMA transfer done */
	XDMACD_STATE_SUSPENDED, /**< DMA suspended */
};

/** DMA driver channel */
struct _xdmacd_channel
{
	Xdmac           *xdmac;     /**< XDMAC instance */
	uint32_t         id;        /**< Channel ID */
	xdmacd_callback_t callback; /**< Callback */
	void            *user_arg;  /**< Callback argument */
	uint8_t          src_txif;  /**< Source TX Interface ID */
	uint8_t          src_rxif;  /**< Source RX Interface ID */
	uint8_t          dest_txif; /**< Destination TX Interface ID */
	uint8_t          dest_rxif; /**< Destination RX Interface ID */
	volatile uint8_t state;     /**< Channel State */
	char             dummy[4];  /** Aligned with dma_channel */
};

/** DMA driver instance */
struct _xdmacd {
	struct _xdmacd_channel channels[XDMACD_CHANNELS];
	bool                  polling;
	uint8_t               polling_timeout;
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
static uint32_t xdmacd_prepare_channel(struct _xdmacd_channel *channel);

static inline struct _xdmacd_channel *_xdmacd_channel(uint32_t controller, uint32_t channel)
{
	return &_xdmacd.channels[controller * XDMAC_CHANNELS + channel];
}

/**
 * \brief xDMA interrupt handler
 * \param pXdmacd Pointer to DMA driver instance.
 */
static void xdmacd_handler(void)
{
	uint32_t cont;

	for (cont= 0; cont< XDMAC_CONTROLLERS; cont++) {
		uint32_t chan, gis, gcs;

		Xdmac *xdmac = xdmac_get_instance(cont);

		gis = xdmac_get_global_isr(xdmac);
		if ((gis & 0xFFFF) == 0)
			continue;

		gcs = xdmac_get_global_channel_status(xdmac);
		for (chan = 0; chan < XDMAC_CHANNELS; chan++) {
			struct _xdmacd_channel *channel;
			bool exec = false;

			if (!(gis & (1 << chan)))
				continue;

			channel = _xdmacd_channel(cont, chan);
			if (channel->state == XDMACD_STATE_FREE)
				continue;

			if (!(gcs & (1 << chan))) {
				uint32_t cis = xdmac_get_channel_isr(xdmac, chan);

				if (cis & XDMAC_CIS_BIS) {
					if (!(xdmac_get_channel_it_mask(xdmac, chan) & XDMAC_CIM_LIM)) {
						channel->state = XDMACD_STATE_DONE;
						exec = 1;
					}
				}

				if (cis & XDMAC_CIS_LIS) {
					channel->state = XDMACD_STATE_DONE;
					exec = 1;
				}

				if (cis & XDMAC_CIS_DIS) {
					channel->state = XDMACD_STATE_DONE;
					exec = 1;
				}
			}

			/* Execute callback */
			if (exec && channel->callback) {
				channel->callback(channel, channel->user_arg);
				dma_free_item((struct dma_channel *)channel);
			}
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
		Xdmac* xdmac = xdmac_get_instance(cont);
		for (chan = 0; chan < XDMAC_CHANNELS; chan++) {
			xdmac_get_channel_isr(xdmac, chan);
			struct _xdmacd_channel *channel = _xdmacd_channel(cont, chan);
			channel->xdmac = xdmac;
			channel->id = chan;
			channel->callback = 0;
			channel->user_arg = 0;
			channel->src_txif = 0;
			channel->src_rxif = 0;
			channel->dest_txif = 0;
			channel->dest_rxif = 0;
			channel->state = XDMACD_STATE_FREE;
		}

		if (!polling) {
			uint32_t pid = xdmac_get_periph_id(xdmac);
			/* enable interrupts */
			aic_set_source_vector(pid, xdmacd_handler);
			aic_enable(pid);
		}
	}
}

void xdmacd_poll(void)
{
	if (_xdmacd.polling)
		xdmacd_handler();
}

struct _xdmacd_channel *xdmacd_allocate_channel(uint8_t src, uint8_t dest)
{
	uint32_t i;

	/* Reject peripheral to peripheral transfers */
	if (src != XDMACD_PERIPH_MEMORY && dest != XDMACD_PERIPH_MEMORY) {
		return NULL;
	}

	for (i = 0; i < XDMACD_CHANNELS; i++) {
		struct _xdmacd_channel *channel = &_xdmacd.channels[i];
		Xdmac *xdmac = channel->xdmac;

		if (channel->state == XDMACD_STATE_FREE) {
			/* Check if source peripheral matches this channel controller */
			if (src != XDMACD_PERIPH_MEMORY)
				if (!is_peripheral_on_xdma_controller(src, xdmac))
					continue;

			/* Check if destination peripheral matches this channel controller */
			if (dest != XDMACD_PERIPH_MEMORY)
				if (!is_peripheral_on_xdma_controller(dest, xdmac))
					continue;

			/* Allocate the channel */
			channel->state = XDMACD_STATE_ALLOCATED;
			channel->src_txif = get_peripheral_xdma_channel(src, xdmac, true);
			channel->src_rxif = get_peripheral_xdma_channel(src, xdmac, false);
			channel->dest_txif = get_peripheral_xdma_channel(dest, xdmac, true);
			channel->dest_rxif = get_peripheral_xdma_channel(dest, xdmac, false);

			xdmacd_prepare_channel(channel);

			return channel;
		}
	}
	return NULL;
}

uint32_t xdmacd_free_channel(struct _xdmacd_channel *channel)
{
	switch (channel->state) {
	case XDMACD_STATE_STARTED:
		return XDMACD_BUSY;
	case XDMACD_STATE_ALLOCATED:
	case XDMACD_STATE_DONE:
		channel->state = XDMACD_STATE_FREE;
		break;
	}
	return XDMACD_OK;
}

uint32_t xdmacd_set_callback(struct _xdmacd_channel *channel,
		xdmacd_callback_t callback, void *user_arg)
{
	if (channel->state == XDMACD_STATE_FREE)
		return XDMACD_ERROR;
	else if (channel->state == XDMACD_STATE_STARTED)
		return XDMACD_BUSY;

	channel->callback = callback;
	channel->user_arg = user_arg;

	return XDMACD_OK;
}

static uint32_t xdmacd_prepare_channel(struct _xdmacd_channel *channel)
{
	Xdmac *xdmac = channel->xdmac;

	if (channel->state == XDMACD_STATE_FREE)
		return XDMACD_ERROR;
	else if (channel->state == XDMACD_STATE_STARTED)
		return XDMACD_BUSY;

	/* Clear status */
	xdmac_get_global_channel_status(xdmac);
	xdmac_get_global_isr(xdmac);

	/* Enable clock of the DMA peripheral */
	pmc_enable_peripheral(xdmac_get_periph_id(xdmac));

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

	return XDMACD_OK;
}

bool xdmacd_is_transfer_done(struct _xdmacd_channel *channel)
{
	return ((channel->state != XDMACD_STATE_STARTED) 
			&& (channel->state != XDMACD_STATE_SUSPENDED));
}

uint32_t xdmacd_configure_transfer(struct _xdmacd_channel *channel,
				  struct _xdmacd_cfg *cfg,
				  uint32_t desc_cntrl,
				  void *desc_addr)
{
	if (channel->state == XDMACD_STATE_FREE)
		return XDMACD_ERROR;
	else if (channel->state == XDMACD_STATE_STARTED)
		return XDMACD_BUSY;

	Xdmac *xdmac = channel->xdmac;
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
	return XDMACD_OK;
}

uint32_t xdmacd_start_transfer(struct _xdmacd_channel *channel)
{
	if (channel->state == XDMACD_STATE_FREE)
		return XDMACD_ERROR;
	else if (channel->state == XDMACD_STATE_STARTED)
		return XDMACD_BUSY;

	/* Change state to 'started' */
	channel->state = XDMACD_STATE_STARTED;

	/* Start DMA transfer */
	xdmac_enable_channel(channel->xdmac, channel->id);
	if (!_xdmacd.polling) {
		xdmac_enable_global_it(channel->xdmac, 1 << channel->id);
	}

	return XDMACD_OK;
}

uint32_t xdmacd_stop_transfer(struct _xdmacd_channel *channel)
{
	Xdmac *xdmac = channel->xdmac;

	/* Disable channel */
	xdmac_disable_channel(xdmac, channel->id);

	/* Disable interrupts */
	xdmac_disable_channel_it(xdmac, channel->id, -1);

	/* Clear pending status */
	xdmac_get_channel_isr(xdmac, channel->id);
	xdmac_get_global_channel_status(xdmac);

	/* Change state to 'allocated' */
	channel->state = XDMACD_STATE_ALLOCATED;

	return XDMACD_OK;
}

uint32_t xdmacd_suspend_transfer(struct _xdmacd_channel *channel)
{
	Xdmac *xdmac = channel->xdmac;

	/* suspend channel */
	xdmac_suspend_channel(xdmac, channel->id);

	/* Change state to 'suspended' */
	channel->state = XDMACD_STATE_SUSPENDED;

	return XDMACD_OK;
}

uint32_t xdmacd_resume_transfer(struct _xdmacd_channel *channel)
{
	Xdmac *xdmac = channel->xdmac;

	/* resume dedicated channel */
	xdmac_resume_read_write_channel(xdmac, channel->id);

	/* Change state to 'started' */
	channel->state = XDMACD_STATE_STARTED;

	return XDMACD_OK;
}

uint32_t xdmacd_get_remaining_data_len(struct _xdmacd_channel *channel)
{
	Xdmac *xdmac = channel->xdmac;

	return xdmac_get_microblock_control(xdmac, channel->id);
}

uint32_t xdmacd_get_desc_addr(struct _xdmacd_channel *channel)
{
	Xdmac *xdmac = channel->xdmac;

	return xdmac_get_descriptor_addr(xdmac, channel->id);
}

void xdmacd_fifo_flush(struct _xdmacd_channel *channel)
{
	Xdmac *xdmac = channel->xdmac;

	xdmac_fifo_flush(xdmac, channel->id);
}

/**@}*/
