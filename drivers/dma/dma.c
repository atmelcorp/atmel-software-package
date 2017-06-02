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

/** \file
 *
 * The DMA API features a generic layer on top of the supported DMA peripherals.
 * The generic layer is device independent and provides the common API for
 * low level driver and generic functionality.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "callback.h"
#include "compiler.h"
#include "dma/dma.h"
#include "irq/irq.h"
#include "errno.h"
#include "mm/cache.h"
#include "mutex.h"
#include "peripherals/pmc.h"

/*----------------------------------------------------------------------------
 *        Macros
 *----------------------------------------------------------------------------*/

#if defined(CONFIG_HAVE_XDMAC)
#define DMA_MAX_BLOCK_LEN XDMAC_MAX_BLOCK_LEN

#define DMA_SG_DESC_GET_NEXT(d) ((struct _dma_sg_desc*)(d)->desc.mbr_nda)
#define DMA_SG_DESC_SET_NEXT(d, next) (d)->desc.mbr_nda = (void*)(next)
#define DMA_SG_DESC_SET_SADDR(d, addr) (d)->desc.mbr_sa = (void*)(addr)
#define DMA_SG_DESC_SET_DADDR(d, addr) (d)->desc.mbr_da = (void*)(addr)

#define DMA_DESC_SET_SADDR(d, addr) (d)->sa = (void*)(addr)
#define DMA_DESC_SET_DADDR(d, addr) (d)->da = (void*)(addr)

#elif defined(CONFIG_HAVE_DMAC)
#define DMA_MAX_BLOCK_LEN DMAC_MAX_BLOCK_LEN

#define DMA_SG_DESC_GET_NEXT(d) ((struct _dma_sg_desc*)(d)->desc.dscr)
#define DMA_SG_DESC_SET_NEXT(d, next) (d)->desc.dscr = (void*)(next)
#define DMA_SG_DESC_SET_SADDR(d, addr) (d)->desc.saddr = (void*)(addr)
#define DMA_SG_DESC_SET_DADDR(d, addr) (d)->desc.daddr = (void*)(addr)

#define DMA_DESC_SET_SADDR(d, addr) (d)->saddr = (void*)(addr)
#define DMA_DESC_SET_DADDR(d, addr) (d)->daddr = (void*)(addr)
#endif

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

static uint32_t controllers[] = {
#ifdef XDMAC0
	ID_XDMAC0,
#endif
#ifdef XDMAC1
	ID_XDMAC1,
#endif
#ifdef DMAC0
	ID_DMAC0,
#endif
#ifdef DMAC1
	ID_DMAC1,
#endif
};

#define DMA_CONTROLLERS ARRAY_SIZE(controllers)

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** Types for specifying a transfer of scattered data, or a transfer of
 * contiguous data that may be reconfigured on a block-by-block basis. */

/** Elementary transfer descriptor, AKA linked list item.
 * Allocate the items, but do not access their members. Please use the dedicated
 * functions defined below. */
struct _dma_sg_desc {
#ifdef CONFIG_HAVE_XDMAC
	struct _xdmac_desc_view1 desc;
#elif defined(CONFIG_HAVE_DMAC)
	struct _dmac_desc desc;
#endif
};

struct _dma_sg_pool {
	struct _dma_sg_desc desc[DMA_SG_ITEM_POOL_SIZE];
	struct _dma_sg_desc* head;
	struct _dma_sg_desc* tail;

	uint16_t count; /* Count elements in list  */
	mutex_t mutex;
};


/** DMA driver instance */
struct _dma_ctrl {
	struct _dma_controller controllers[DMA_CONTROLLERS];
	bool polling;
	uint8_t polling_timeout;
};

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

CACHE_ALIGNED static struct _dma_sg_pool _dma_sg_pool;

static struct _dma_ctrl _dma_ctrl;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static inline bool is_source_periph(struct _dma_channel* channel)
{
	return ((channel->src_txif != 0xff) | (channel->src_rxif != 0xff));
}

static inline bool is_dest_periph(struct _dma_channel* channel)
{
	return ((channel->dest_txif != 0xff) | (channel->dest_rxif != 0xff));
}

/**
 * \brief Preinitialize all descriptors and pool and link them together
 */
static void _dma_sg_init(void)
{
	uint32_t i;

	memset(&_dma_sg_pool, 0, sizeof(_dma_sg_pool));

	mutex_lock(&_dma_sg_pool.mutex);

	for (i = 0; i < ARRAY_SIZE(_dma_sg_pool.desc); i++)
		DMA_SG_DESC_SET_NEXT(&_dma_sg_pool.desc[i], &_dma_sg_pool.desc[i + 1]);
	DMA_SG_DESC_SET_NEXT(&_dma_sg_pool.desc[i - 1], 0);

	_dma_sg_pool.head = _dma_sg_pool.desc;
	_dma_sg_pool.tail = &_dma_sg_pool.desc[i - 1];
	_dma_sg_pool.count = ARRAY_SIZE(_dma_sg_pool.desc);

	mutex_unlock(&_dma_sg_pool.mutex);
}

static struct _dma_sg_desc* _dma_sg_desc_alloc(uint8_t count)
{
	struct _dma_sg_desc* list_head;
	struct _dma_sg_desc* curr;
	struct _dma_sg_desc* next;
	uint8_t i;

	if (count == 0)
		return NULL;
	if (count > _dma_sg_pool.count)
		return NULL;

	mutex_lock(&_dma_sg_pool.mutex);

	list_head = _dma_sg_pool.head;
	curr = list_head;
	for (i = 0; i < (count - 1); i++) {
		curr = DMA_SG_DESC_GET_NEXT(curr);
	}
		next = DMA_SG_DESC_GET_NEXT(curr);
	DMA_SG_DESC_SET_NEXT(curr, 0);

	_dma_sg_pool.count -= count;
	_dma_sg_pool.head = next;

	if (_dma_sg_pool.count == 0) {
		_dma_sg_pool.head = NULL;
		_dma_sg_pool.tail = NULL;
	}

	mutex_unlock(&_dma_sg_pool.mutex);

	return list_head;
}

static void _dma_sg_desc_free(struct _dma_sg_desc* list_head)
{
	struct _dma_sg_desc* curr = list_head;
	struct _dma_sg_desc* tail;

	if (list_head == NULL)
		return;

	do {
		tail = curr;
		curr = DMA_SG_DESC_GET_NEXT(curr);
	} while ((curr != NULL) && (curr != list_head));
	curr = list_head;

	mutex_lock(&_dma_sg_pool.mutex);

	if (_dma_sg_pool.head == NULL)
		_dma_sg_pool.head = list_head;

	if (_dma_sg_pool.tail != NULL)
		DMA_SG_DESC_SET_NEXT(_dma_sg_pool.tail, list_head);
	_dma_sg_pool.tail = tail;
	DMA_SG_DESC_SET_NEXT(_dma_sg_pool.tail, 0);

	mutex_unlock(&_dma_sg_pool.mutex);
}

static int _dma_configure_transfer(struct _dma_channel* channel,
				   struct _dma_cfg* cfg_dma,
				   struct _dma_transfer_cfg *cfg)
{
	bool src_is_periph, dst_is_periph;
	uint32_t divisor;

#if defined(CONFIG_HAVE_XDMAC)
	struct _xdmacd_cfg desc;
#elif defined(CONFIG_HAVE_DMAC)
	struct _dmac_desc desc;
	struct _dmacd_cfg dma_cfg;
#endif

	memset(&desc, 0, sizeof(desc));

	src_is_periph = is_source_periph(channel);
	dst_is_periph = is_dest_periph(channel);

	if (cfg->len <= DMA_MAX_BT_SIZE) {
		/* If len is <= 16,777,215, the driver will transfer a
		   single block, those size will be len data elements. */
#if defined(CONFIG_HAVE_XDMAC)
		desc.ubc = cfg->len;
		desc.bc = 0;
#elif defined(CONFIG_HAVE_DMAC)
		desc.ctrla = cfg->len;
#endif
	} else {
		/* If len exceeds 16,777,215, split the transfer in
		   multiple blocks (microblocks), calculating and using the greatest block
		   size possible for this transfer. */
		for (divisor = DMA_MAX_BT_SIZE; divisor > 1; divisor--) {
			if (cfg->len % divisor)
				continue;
			if ((cfg->len / divisor) <= DMA_MAX_BLOCK_LEN) {
#if defined(CONFIG_HAVE_XDMAC)
				desc.ubc = divisor;
				desc.bc = (cfg->len / divisor) - 1;
#elif defined(CONFIG_HAVE_DMAC)
				desc.ctrla = divisor;
				dma_cfg.blocks = (cfg->len / divisor) - 1;
				dma_cfg.trans_auto = 1;
				dma_cfg.sa_rep = src_is_periph ? 1 : 0 ;
				dma_cfg.da_rep = dst_is_periph ? 1 : 0 ;
#endif
				break;
			}
		}
		if (divisor == 1)
			return -EINVAL;
	}

	DMA_DESC_SET_SADDR(&desc, cfg->saddr);
	DMA_DESC_SET_DADDR(&desc, cfg->daddr);

#if defined(CONFIG_HAVE_XDMAC)
	if (src_is_periph || dst_is_periph)
		desc.cfg = XDMAC_CC_TYPE_PER_TRAN;
	else
		desc.cfg = XDMAC_CC_TYPE_MEM_TRAN;
	desc.cfg |= src_is_periph ? XDMAC_CC_DSYNC_PER2MEM : XDMAC_CC_DSYNC_MEM2PER;
	desc.cfg |= XDMAC_CC_CSIZE(cfg_dma->chunk_size);
	desc.cfg |= XDMAC_CC_DWIDTH(cfg_dma->data_width);
	desc.cfg |= src_is_periph ? XDMAC_CC_SIF_AHB_IF1 : XDMAC_CC_SIF_AHB_IF0;
	desc.cfg |= dst_is_periph ? XDMAC_CC_DIF_AHB_IF1 : XDMAC_CC_DIF_AHB_IF0;
	desc.cfg |= cfg_dma->incr_saddr ? XDMAC_CC_SAM_INCREMENTED_AM : XDMAC_CC_SAM_FIXED_AM;
	desc.cfg |= cfg_dma->incr_daddr ? XDMAC_CC_DAM_INCREMENTED_AM : XDMAC_CC_DAM_FIXED_AM;
	desc.cfg |= (src_is_periph || dst_is_periph) ? 0 : XDMAC_CC_SWREQ_SWR_CONNECTED;
	desc.ds = 0;
	desc.sus = 0;
	desc.dus = 0;

	return xdmacd_configure_transfer(channel, &desc, 0, 0);
#elif defined(CONFIG_HAVE_DMAC)
	dma_cfg.s_decr_fetch = 1;
	dma_cfg.d_decr_fetch = 1;
	dma_cfg.sa_rep = 0;
	dma_cfg.da_rep = 0;
	dma_cfg.trans_auto = 0;
	dma_cfg.blocks = 0;

	dma_cfg.cfg = src_is_periph ? DMAC_CFG_SRC_H2SEL_HW : 0;
	dma_cfg.cfg |= dst_is_periph ? DMAC_CFG_DST_H2SEL_HW : 0;

	desc.ctrla |= (cfg_dma->data_width << DMAC_CTRLA_SRC_WIDTH_Pos)
		| (cfg_dma->data_width << DMAC_CTRLA_DST_WIDTH_Pos)
		| (cfg_dma->chunk_size << DMAC_CTRLA_SCSIZE_Pos)
		| (cfg_dma->chunk_size << DMAC_CTRLA_DCSIZE_Pos);

#if defined(CONFIG_SOC_SAMA5D3)
	desc.ctrlb = src_is_periph ? DMAC_CTRLB_SIF_AHB_IF2 : DMAC_CTRLB_SIF_AHB_IF0;
	desc.ctrlb |= dst_is_periph ? DMAC_CTRLB_DIF_AHB_IF2 : DMAC_CTRLB_DIF_AHB_IF0;
#elif defined(CONFIG_SOC_SAM9XX5)
	desc.ctrlb = src_is_periph ? DMAC_CTRLB_SIF_AHB_IF1 : DMAC_CTRLB_SIF_AHB_IF0;
	desc.ctrlb |= dst_is_periph ? DMAC_CTRLB_DIF_AHB_IF1 : DMAC_CTRLB_DIF_AHB_IF0;
#endif
	if (src_is_periph)
		desc.ctrlb |= DMAC_CTRLB_FC_PER2MEM_DMA_FC;
	else if (dst_is_periph)
		desc.ctrlb |= DMAC_CTRLB_FC_MEM2PER_DMA_FC;
	else
		desc.ctrlb |= DMAC_CTRLB_FC_MEM2MEM_DMA_FC;
	desc.ctrlb |= cfg_dma->incr_saddr ? DMAC_CTRLB_SRC_INCR_INCREMENTING : DMAC_CTRLB_SRC_INCR_FIXED;
	desc.ctrlb |= cfg_dma->incr_daddr ? DMAC_CTRLB_DST_INCR_INCREMENTING : DMAC_CTRLB_DST_INCR_FIXED;
	desc.ctrlb |= DMAC_CTRLB_SRC_DSCR_FETCH_DISABLE | DMAC_CTRLB_DST_DSCR_FETCH_DISABLE;

	return dmacd_configure_transfer(channel, &dma_cfg, &desc);
#endif /* CONFIG_HAVE_DMAC */
}

static int _dma_sg_configure_transfer(struct _dma_channel* channel,
				      struct _dma_cfg* cfg_dma,
				      struct _dma_transfer_cfg* sg_list, uint8_t sg_list_size)
{
	struct _dma_sg_desc* _sg_head;
	struct _dma_sg_desc* curr;
	struct _dma_transfer_cfg* cfg;
	bool src_is_periph, dst_is_periph;
	uint8_t idx;

	if ((sg_list == NULL) || (sg_list_size == 0))
		return -EINVAL;

	src_is_periph = is_source_periph(channel);
	dst_is_periph = is_dest_periph(channel);

	_sg_head = _dma_sg_desc_alloc(sg_list_size);
	if (_sg_head == NULL)
		return -ENOMEM;
	curr = _sg_head;

	src_is_periph = is_source_periph(channel);
	dst_is_periph = is_dest_periph(channel);

	/* Update linked list */
	for (idx = 0; idx < sg_list_size; idx++) {
		cfg = &sg_list[idx];

		DMA_SG_DESC_SET_SADDR(curr, cfg->saddr);
		DMA_SG_DESC_SET_DADDR(curr, cfg->daddr);

#if defined(CONFIG_HAVE_XDMAC)
		curr->desc.mbr_ubc = XDMA_UBC_NVIEW_NDV1
			| XDMA_UBC_NSEN_UPDATED
			| XDMA_UBC_NDEN_UPDATED
			| XDMA_UBC_NDE_FETCH_EN
			| XDMA_UBC_UBLEN(cfg->len);

		if (!cfg_dma->loop) {
			if (DMA_SG_DESC_GET_NEXT(curr) == 0)
				curr->desc.mbr_ubc &= ~XDMA_UBC_NDE_FETCH_EN;
		}

#elif defined(CONFIG_HAVE_DMAC)
		curr->desc.ctrla = (cfg_dma->data_width << DMAC_CTRLA_SRC_WIDTH_Pos)
			| (cfg_dma->data_width << DMAC_CTRLA_DST_WIDTH_Pos)
			| (cfg_dma->chunk_size << DMAC_CTRLA_SCSIZE_Pos)
			| (cfg_dma->chunk_size << DMAC_CTRLA_DCSIZE_Pos)
			| DMAC_CTRLA_BTSIZE(cfg->len);

#if defined(CONFIG_SOC_SAMA5D3)
		curr->desc.ctrlb = src_is_periph ? DMAC_CTRLB_SIF_AHB_IF2 : DMAC_CTRLB_SIF_AHB_IF0;
		curr->desc.ctrlb |= dst_is_periph ? DMAC_CTRLB_DIF_AHB_IF2 : DMAC_CTRLB_DIF_AHB_IF0;
#elif defined(CONFIG_SOC_SAM9XX5)
		curr->desc.ctrlb = src_is_periph ? DMAC_CTRLB_SIF_AHB_IF1 : DMAC_CTRLB_SIF_AHB_IF0;
		curr->desc.ctrlb |= dst_is_periph ? DMAC_CTRLB_DIF_AHB_IF1 : DMAC_CTRLB_DIF_AHB_IF0;
#endif
		if (src_is_periph)
			curr->desc.ctrlb |= DMAC_CTRLB_FC_PER2MEM_DMA_FC;
		else if (dst_is_periph)
			curr->desc.ctrlb |= DMAC_CTRLB_FC_MEM2PER_DMA_FC;
		else
			curr->desc.ctrlb |= DMAC_CTRLB_FC_MEM2MEM_DMA_FC;

		curr->desc.ctrlb |= cfg_dma->incr_saddr ? DMAC_CTRLB_SRC_INCR_INCREMENTING : DMAC_CTRLB_SRC_INCR_FIXED;
		curr->desc.ctrlb |= cfg_dma->incr_daddr ? DMAC_CTRLB_DST_INCR_INCREMENTING : DMAC_CTRLB_DST_INCR_FIXED;

		curr->desc.ctrlb |= DMAC_CTRLB_SRC_DSCR_FETCH_FROM_MEM | DMAC_CTRLB_DST_DSCR_FETCH_FROM_MEM;

#endif
		if (DMA_SG_DESC_GET_NEXT(curr) == 0)
			if (cfg_dma->loop)
				DMA_SG_DESC_SET_NEXT(curr, _sg_head);
		curr = DMA_SG_DESC_GET_NEXT(curr);
	}
	channel->sg_list = _sg_head;

	cache_clean_region(_dma_sg_pool.desc, sizeof(_dma_sg_pool.desc));

	/* Update configuration */
#if defined(CONFIG_HAVE_XDMAC)
	struct _xdmacd_cfg xdmacd_cfg;
	uint32_t desc_ctrl;

	xdmacd_cfg.cfg = (src_is_periph | dst_is_periph) ? XDMAC_CC_TYPE_PER_TRAN : XDMAC_CC_TYPE_MEM_TRAN;
	xdmacd_cfg.cfg |= src_is_periph ? XDMAC_CC_DSYNC_PER2MEM : XDMAC_CC_DSYNC_MEM2PER;
	xdmacd_cfg.cfg |= XDMAC_CC_CSIZE(cfg_dma->chunk_size);
	xdmacd_cfg.cfg |= XDMAC_CC_DWIDTH(cfg_dma->data_width);
	xdmacd_cfg.cfg |= src_is_periph ? XDMAC_CC_SIF_AHB_IF1 : XDMAC_CC_SIF_AHB_IF0;
	xdmacd_cfg.cfg |= dst_is_periph ? XDMAC_CC_DIF_AHB_IF1 : XDMAC_CC_DIF_AHB_IF0;
	xdmacd_cfg.cfg |= cfg_dma->incr_saddr ? XDMAC_CC_SAM_INCREMENTED_AM : XDMAC_CC_SAM_FIXED_AM;
	xdmacd_cfg.cfg |= cfg_dma->incr_daddr ? XDMAC_CC_DAM_INCREMENTED_AM : XDMAC_CC_DAM_FIXED_AM;
	xdmacd_cfg.cfg |= (src_is_periph | dst_is_periph) ? 0 : XDMAC_CC_SWREQ_SWR_CONNECTED;
	xdmacd_cfg.bc = 0;
	xdmacd_cfg.ds = 0;
	xdmacd_cfg.sus = 0;
	xdmacd_cfg.dus = 0;

	desc_ctrl = XDMAC_CNDC_NDVIEW_NDV1
	           | XDMAC_CNDC_NDE_DSCR_FETCH_EN
	           | XDMAC_CNDC_NDSUP_SRC_PARAMS_UPDATED
	           | XDMAC_CNDC_NDDUP_DST_PARAMS_UPDATED;

	return xdmacd_configure_transfer(channel, &xdmacd_cfg, desc_ctrl, (void *)_sg_head);
#elif defined(CONFIG_HAVE_DMAC)
	struct _dmacd_cfg dmacd_cfg;

	dmacd_cfg.s_decr_fetch = 0;
	dmacd_cfg.d_decr_fetch = 0;
	dmacd_cfg.sa_rep = 0;
	dmacd_cfg.da_rep = 0;
	dmacd_cfg.trans_auto = 0;
	dmacd_cfg.blocks = 0;
	dmacd_cfg.s_pip = 0;
	dmacd_cfg.d_pip = 0;
	dmacd_cfg.cfg = src_is_periph ? DMAC_CFG_SRC_H2SEL_HW : 0;
	dmacd_cfg.cfg |= dst_is_periph ? DMAC_CFG_DST_H2SEL_HW : 0;

	return dmacd_configure_transfer(channel, &dmacd_cfg, (void*)_sg_head);
#endif
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void dma_initialize(bool polling)
{
	uint32_t ctrl, chan;

	_dma_sg_init();

	_dma_ctrl.polling = polling;

	for (ctrl = 0; ctrl < DMA_CONTROLLERS; ctrl++) {
		struct _dma_controller* controller = &_dma_ctrl.controllers[ctrl];
		controller->pid = controllers[ctrl];
#if defined(CONFIG_HAVE_XDMAC)
		controller->hw = get_xdmac_addr_from_id(controller->pid);
#elif defined(CONFIG_HAVE_DMAC)
		controller->hw = get_dmac_addr_from_id(controller->pid);
#endif
		for (chan = 0; chan < DMA_CHANNELS; chan++) {
#if defined(CONFIG_HAVE_XDMAC)
			xdmac_get_channel_isr(controller->hw, chan);
#endif
			struct _dma_channel* channel = &controller->channels[chan];
			channel->hw = controller->hw;
			channel->id = chan;
			callback_set(&channel->callback, NULL, NULL);
			channel->src_txif = 0;
			channel->src_rxif = 0;
			channel->dest_txif = 0;
			channel->dest_rxif = 0;
			channel->state = DMA_STATE_FREE;
		}

		if (!polling) {
			/* enable interrupts */
			irq_add_handler(controller->pid, dma_irq_handler, controller);
			irq_enable(controller->pid);
		}
	}
}

void dma_poll(void)
{
	if (_dma_ctrl.polling) {
		uint32_t ctrl;
		for (ctrl = 0; ctrl < DMA_CONTROLLERS; ctrl++) {
			struct _dma_controller* controller = &_dma_ctrl.controllers[ctrl];
			dma_irq_handler(controller->pid, controller);
		}
	}
}

struct _dma_channel* dma_allocate_channel(uint8_t src, uint8_t dest)
{
	uint32_t chan, ctrl;

	/* Reject peripheral to peripheral transfers */
	if (src != DMA_PERIPH_MEMORY && dest != DMA_PERIPH_MEMORY)
		return NULL;

	for (ctrl = 0; ctrl < DMA_CONTROLLERS; ctrl++) {
		for (chan = 0; chan < DMA_CHANNELS; chan++) {
			struct _dma_channel* channel = &_dma_ctrl.controllers[ctrl].channels[chan];

			if (channel->state == DMA_STATE_FREE) {
				/* Check if source peripheral matches this channel controller */
				if (src != DMA_PERIPH_MEMORY)
					if (!is_peripheral_on_dma_controller(src, channel->hw))
						continue;

				/* Check if destination peripheral matches this channel controller */
				if (dest != DMA_PERIPH_MEMORY)
					if (!is_peripheral_on_dma_controller(dest, channel->hw))
						continue;

				/* Allocate the channel */
				channel->state = DMA_STATE_ALLOCATED;
				channel->src_txif = get_peripheral_dma_channel(src, channel->hw, true);
				channel->src_rxif = get_peripheral_dma_channel(src, channel->hw, false);
				channel->dest_txif = get_peripheral_dma_channel(dest, channel->hw, true);
				channel->dest_rxif = get_peripheral_dma_channel(dest, channel->hw, false);
				dma_prepare_channel(channel);

				channel->sg_list = NULL;

				return channel;
			}
		}
	}
	return NULL;
}

int dma_reset_channel(struct _dma_channel* channel)
{
	if (channel->state == DMA_STATE_ALLOCATED)
		return 0;

	if (channel->state == DMA_STATE_STARTED)
		return -EBUSY;

#if defined(CONFIG_HAVE_XDMAC)
	/* Disable channel */
	xdmac_disable_channel(channel->hw, channel->id);

	/* Disable interrupts */
	xdmac_disable_channel_it(channel->hw, channel->id, -1);
#elif defined(CONFIG_HAVE_DMAC)
	/* Disable channel */
	dmac_disable_channel(channel->hw, channel->id);

	/* Disable interrupts */
	dmac_disable_global_it(channel->hw, (DMAC_EBCIDR_CBTC0 | DMAC_EBCIER_BTC0 | DMAC_EBCIER_ERR0) << channel->id);
#endif

	_dma_sg_desc_free(channel->sg_list);
	channel->sg_list = NULL;

	/* Change state to 'allocated' */
	channel->state = DMA_STATE_ALLOCATED;

	return 0;
}

int dma_free_channel(struct _dma_channel* channel)
{
	switch (channel->state) {
	case DMA_STATE_STARTED:
		return -EBUSY;
	case DMA_STATE_ALLOCATED:
	case DMA_STATE_DONE:
		channel->state = DMA_STATE_FREE;
		_dma_sg_desc_free(channel->sg_list);
		channel->sg_list = NULL;
		break;
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
	if (!_dma_ctrl.polling) {
#if defined(CONFIG_HAVE_XDMAC)
		xdmac_enable_global_it(channel->hw, 1 << channel->id);
#elif defined(CONFIG_HAVE_DMAC)
		dmac_enable_global_it(channel->hw, (DMAC_EBCIDR_CBTC0 | DMAC_EBCIER_BTC0 | DMAC_EBCIER_ERR0) << channel->id);
#endif
	}
#if defined(CONFIG_HAVE_XDMAC)
	xdmac_enable_channel(channel->hw, channel->id);
#elif defined(CONFIG_HAVE_DMAC)
	dmac_enable_channel(channel->hw, channel->id);
#endif
	return 0;
}

int dma_stop_transfer(struct _dma_channel* channel)
{
#if defined(CONFIG_HAVE_XDMAC)
	/* Disable channel */
	xdmac_disable_channel(channel->hw, channel->id);
	/* Disable interrupts */
	xdmac_disable_channel_it(channel->hw, channel->id, -1);
	/* Clear pending status */
	xdmac_get_channel_isr(channel->hw, channel->id);
	xdmac_get_global_channel_status(channel->hw);
#elif defined(CONFIG_HAVE_DMAC)
	/* Disable channel */
	dmac_disable_channel(channel->hw, channel->id);
	/* Clear pending status */
	dmac_get_global_isr(channel->hw);
#endif

	/* Change state to 'allocated' */
	channel->state = DMA_STATE_ALLOCATED;

	return 0;
}

int dma_suspend_transfer(struct _dma_channel* channel)
{
	/* Suspend channel */
#if defined(CONFIG_HAVE_XDMAC)
	xdmac_suspend_channel(channel->hw, channel->id);
#elif defined(CONFIG_HAVE_DMAC)
	dmac_suspend_channel(channel->hw, channel->id);
#endif
	/* Change state to 'suspended' */
	channel->state = DMA_STATE_SUSPENDED;

	return 0;
}

int dma_resume_transfer(struct _dma_channel* channel)
{
	/* Resume channel */
#if defined(CONFIG_HAVE_XDMAC)
	xdmac_resume_read_write_channel(channel->hw, channel->id);
#elif defined(CONFIG_HAVE_DMAC)
	dmac_resume_channel(channel->hw, channel->id);
#endif
	/* Change state to 'started */
	channel->state = DMA_STATE_STARTED;

	return 0;
}

void dma_fifo_flush(struct _dma_channel* channel)
{
#if defined(CONFIG_HAVE_XDMAC)
	xdmac_fifo_flush(channel->hw, channel->id);
#elif defined(CONFIG_HAVE_DMAC)
	dmac_fifo_flush(channel->hw, channel->id);
#endif
}

int dma_configure_transfer(struct _dma_channel* channel,
			   struct _dma_cfg* cfg_dma,
			   struct _dma_transfer_cfg* list, uint8_t list_size)
{
	if (list_size == 0)
		return -EINVAL;

	if ((list_size == 1) && (!cfg_dma->loop))
		return _dma_configure_transfer(channel, cfg_dma, list);
	else
		return _dma_sg_configure_transfer(channel, cfg_dma, list, list_size);
}

uint32_t dma_get_transferred_data_len(struct _dma_channel* channel, uint8_t chunk_size, uint32_t len)
{
#if defined(CONFIG_HAVE_XDMAC)
	return len - xdmac_get_microblock_control(channel->hw, channel->id) * (1 << chunk_size);
#elif defined(CONFIG_HAVE_DMAC)
	return dmac_get_btsize(channel->hw, channel->id) * (1 << chunk_size);
#endif
}

int dma_set_callback(struct _dma_channel* channel, struct _callback* cb)
{
	if (channel->state == DMA_STATE_FREE)
		return -EPERM;
	else if (channel->state == DMA_STATE_STARTED)
		return -EBUSY;

	callback_copy(&channel->callback, cb);

	return 0;
}

bool dma_is_transfer_done(struct _dma_channel* channel)
{
	return ((channel->state != DMA_STATE_STARTED)
		&& (channel->state != DMA_STATE_SUSPENDED));
}

/**@}*/
