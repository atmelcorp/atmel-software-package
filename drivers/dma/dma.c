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

#include "callback.h"
#include "compiler.h"
#include "dma/dma.h"
#include "errno.h"
#include "mm/cache.h"
#include "mutex.h"
#include "peripherals/pmc.h"

/*----------------------------------------------------------------------------
 *        Macros
 *----------------------------------------------------------------------------*/

#if defined(CONFIG_HAVE_XDMAC)
#define DMA_SG_DESC_GET_NEXT(d) ((struct _dma_sg_desc*)(d)->desc.mbr_nda)
#define DMA_SG_DESC_SET_NEXT(d, next) (d)->desc.mbr_nda = (void*)(next)
#elif defined(CONFIG_HAVE_DMAC)
#define DMA_SG_DESC_GET_NEXT(d) ((struct _dma_sg_desc*)(d)->desc.dscr)
#define DMA_SG_DESC_SET_NEXT(d, next) (d)->desc.dscr = (void*)(next)
#endif

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

CACHE_ALIGNED static struct _dma_sg_pool _dma_sg_pool;

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

	_dma_sg_pool.mutex = 0;

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
	i = 0;
	curr = list_head;
	next = DMA_SG_DESC_GET_NEXT(curr);
	while (i < count) {
		curr = DMA_SG_DESC_GET_NEXT(curr);
		next = DMA_SG_DESC_GET_NEXT(curr);
		if (i == (count - 1))
			DMA_SG_DESC_SET_NEXT(curr, 0);
		i++;
	}

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

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void dma_initialize(bool polling)
{
	_dma_sg_init();

#if defined(CONFIG_HAVE_XDMAC)
	xdmacd_initialize(polling);
#elif defined(CONFIG_HAVE_DMAC)
	dmacd_initialize(polling);
#endif
}

int dma_free_channel(struct _dma_channel* channel)
{
	switch (channel->state) {
	case DMA_STATE_STARTED:
		return -EBUSY;
	case DMA_STATE_ALLOCATED:
	case DMA_STATE_DONE:
		channel->state = DMA_STATE_FREE;
		break;
	}
	return 0;
}

int dma_configure_transfer(struct _dma_channel* channel, const struct dma_xfer_cfg *cfg)
{
	bool src_is_periph, dst_is_periph;
	uint32_t divisor;

#if defined(CONFIG_HAVE_XDMAC)
	struct _xdmacd_cfg xdma_cfg;
#elif defined(CONFIG_HAVE_DMAC)
	struct _dmacd_cfg dma_cfg;
	struct _dmac_desc dma_regs;
#endif

	src_is_periph = is_source_periph(channel);
	dst_is_periph = is_dest_periph(channel);

#if defined(CONFIG_HAVE_XDMAC)
/* for DMAC */
	if (cfg->blk_size > DMA_MAX_BT_SIZE) {
		/* Block size (microblock length) is limited to 16,777,215 data elements */
		return -EOVERFLOW;
	}
	if (!cfg->blk_size) {
		if (cfg->len <= DMA_MAX_BT_SIZE) {
			/* If blk_size is zero and len is <= 16,777,215, the driver will transfer a
			single block, those size will be len data elements. */
			xdma_cfg.ubc = cfg->len;
			xdma_cfg.bc = 0;
		} else {
			/* If blk_size is zero and len exceeds 16,777,215, split the transfer in
				multiple blocks (microblocks), calculating and using the greatest block
				size possible for this transfer. */
			for (divisor = DMA_MAX_BT_SIZE; divisor > 1; divisor--) {
				if (cfg->len % divisor)
					continue;
				if ((cfg->len / divisor) <= XDMAC_MAX_BLOCK_LEN) {
					xdma_cfg.ubc = divisor;
					xdma_cfg.bc = (cfg->len / divisor) - 1;
					break;
				}
			}
			if (divisor == 1)
				return -EINVAL;
		}
	} else {
		if (cfg->len <= XDMAC_MAX_BLOCK_LEN) {
			xdma_cfg.ubc = cfg->blk_size;
			xdma_cfg.bc = cfg->len - 1;
		} else {
			return -EOVERFLOW;
		}
	}
	xdma_cfg.sa = cfg->sa;
	xdma_cfg.da = cfg->da;
	xdma_cfg.cfg = (src_is_periph | dst_is_periph) ?
					XDMAC_CC_TYPE_PER_TRAN : XDMAC_CC_TYPE_MEM_TRAN;
	xdma_cfg.cfg |= src_is_periph ? XDMAC_CC_DSYNC_PER2MEM:
					 XDMAC_CC_DSYNC_MEM2PER;
	xdma_cfg.cfg |= (src_is_periph ? XDMAC_CC_CSIZE(cfg->chunk_size) : 0)
				 | (dst_is_periph ? XDMAC_CC_CSIZE(cfg->chunk_size) : 0);
	xdma_cfg.cfg |= XDMAC_CC_DWIDTH(cfg->data_width);
	xdma_cfg.cfg |= src_is_periph ? XDMAC_CC_SIF_AHB_IF1:
					XDMAC_CC_SIF_AHB_IF0;
	xdma_cfg.cfg |= dst_is_periph ? XDMAC_CC_DIF_AHB_IF1:
					XDMAC_CC_DIF_AHB_IF0;
	xdma_cfg.cfg |= cfg->upd_sa_per_data ? XDMAC_CC_SAM_INCREMENTED_AM :
					XDMAC_CC_SAM_FIXED_AM;
	xdma_cfg.cfg |= cfg->upd_da_per_data ? XDMAC_CC_DAM_INCREMENTED_AM :
					XDMAC_CC_DAM_FIXED_AM;
	xdma_cfg.cfg |= (src_is_periph | dst_is_periph) ? 0: XDMAC_CC_SWREQ_SWR_CONNECTED;
	xdma_cfg.ds = 0;
	xdma_cfg.sus = 0;
	xdma_cfg.dus = 0;

	return xdmacd_configure_transfer(channel, &xdma_cfg, 0, 0);

#elif defined(CONFIG_HAVE_DMAC)

	/* for DMAC */
	dma_regs.ctrla = 0;
	dma_regs.ctrlb = 0;
	dma_cfg.s_decr_fetch = 1;
	dma_cfg.d_decr_fetch = 1;
	dma_cfg.sa_rep = 0;
	dma_cfg.da_rep = 0;
	dma_cfg.trans_auto = 0;
	dma_cfg.blocks = 0;

	if (cfg->blk_size > DMA_MAX_BT_SIZE) {
		/* Block size (microblock length) is limited to 65535 data elements */
		return -EOVERFLOW;
	}
	if (!cfg->blk_size) {
		if (cfg->len <= DMA_MAX_BT_SIZE) {
			/* If blk_size is zero and len is <= 65535, the driver will transfer a
			single block, those size will be len data elements. */
			dma_regs.ctrla = cfg->len;
		} else {
			/* If blk_size is zero and len exceeds 16,777,215, split the transfer in
				multiple blocks (microblocks), calculating and using the greatest block
				size possible for this transfer. */
			for (divisor = DMA_MAX_BT_SIZE; divisor > 1; divisor--) {
				if (cfg->len % divisor)
					continue;
				if ((cfg->len / divisor ) <= DMA_MAX_BLOCK_LEN) {
					dma_regs.ctrla = divisor;
					dma_cfg.blocks = (cfg->len / divisor) - 1;
					dma_cfg.trans_auto = 1;
					dma_cfg.sa_rep = src_is_periph ? 1 : 0 ;
					dma_cfg.da_rep = dst_is_periph ? 1 : 0 ;
					break;
				}
			}
		if (divisor == 1)
			return -EINVAL;
		}
	} else {
		dma_regs.ctrla = cfg->blk_size;
		dma_cfg.blocks = cfg->len - 1;
		dma_cfg.trans_auto = dma_cfg.blocks ? 1 : 0;
		if (dma_cfg.blocks) {
			dma_cfg.sa_rep = src_is_periph ? 1 : 0 ;
			dma_cfg.da_rep = dst_is_periph ? 1 : 0 ;
		}
	}
	dma_cfg.cfg = src_is_periph ? DMAC_CFG_SRC_H2SEL_HW : 0;
	dma_cfg.cfg |= dst_is_periph ? DMAC_CFG_DST_H2SEL_HW : 0;

	dma_regs.saddr = cfg->sa;
	dma_regs.daddr = cfg->da;

	dma_regs.ctrla |= (cfg->data_width << DMAC_CTRLA_SRC_WIDTH_Pos)
				   | (cfg->data_width << DMAC_CTRLA_DST_WIDTH_Pos)
				   | (cfg->chunk_size << DMAC_CTRLA_SCSIZE_Pos)
				   | (cfg->chunk_size << DMAC_CTRLA_DCSIZE_Pos);

#if defined(CONFIG_SOC_SAMA5D3)
	dma_regs.ctrlb = src_is_periph ? DMAC_CTRLB_SIF_AHB_IF2 : DMAC_CTRLB_SIF_AHB_IF0;
	dma_regs.ctrlb |= dst_is_periph ? DMAC_CTRLB_DIF_AHB_IF2 : DMAC_CTRLB_DIF_AHB_IF0;
#elif defined(CONFIG_SOC_SAM9XX5)
	dma_regs.ctrlb = src_is_periph ? DMAC_CTRLB_SIF_AHB_IF1 : DMAC_CTRLB_SIF_AHB_IF0;
	dma_regs.ctrlb |= dst_is_periph ? DMAC_CTRLB_DIF_AHB_IF1 : DMAC_CTRLB_DIF_AHB_IF0;
#else
#error Unknown SoC!
#endif
	dma_regs.ctrlb |= ((src_is_periph) ? DMAC_CTRLB_FC_PER2MEM_DMA_FC :
					   ((dst_is_periph) ? DMAC_CTRLB_FC_MEM2PER_DMA_FC :
					   DMAC_CTRLB_FC_MEM2MEM_DMA_FC));
	dma_regs.ctrlb |= (cfg->upd_sa_per_data ? DMAC_CTRLB_SRC_INCR_INCREMENTING:
						DMAC_CTRLB_SRC_INCR_FIXED)
					 | (cfg->upd_da_per_data ? DMAC_CTRLB_DST_INCR_INCREMENTING:
						DMAC_CTRLB_DST_INCR_FIXED);
	dma_regs.ctrlb |= DMAC_CTRLB_SRC_DSCR_FETCH_DISABLE | DMAC_CTRLB_DST_DSCR_FETCH_DISABLE;

	return dmacd_configure_transfer(channel, &dma_cfg, &dma_regs);
#endif
}

int dma_sg_configure_transfer(struct _dma_channel* channel,
			      struct _dma_sg_cfg* cfg,
			      struct _dma_sg_list* list_head, uint8_t list_size)
{
	struct _dma_sg_desc* _sg_head;
	struct _dma_sg_desc* curr;
	struct _dma_sg_list* data = list_head;
	bool src_is_periph, dst_is_periph;

	if ((list_head == NULL) || (list_size == 0))
		return -EINVAL;

	_sg_head = _dma_sg_desc_alloc(list_size);
	if (_sg_head == NULL)
		return -ENOMEM;
	curr = _sg_head;

	src_is_periph = is_source_periph(channel);
	dst_is_periph = is_dest_periph(channel);

	/* Update linked list */
	while (data != NULL) {
#if defined(CONFIG_HAVE_XDMAC)

		curr->desc.mbr_sa = data->saddr;
		curr->desc.mbr_da = data->daddr;
		curr->desc.mbr_ubc = XDMA_UBC_NVIEW_NDV1
			| XDMA_UBC_NSEN_UPDATED
			| XDMA_UBC_NDEN_UPDATED
			| XDMA_UBC_NDE_FETCH_EN
			| XDMA_UBC_UBLEN(data->len);

		if (!cfg->loop) {
			if (DMA_SG_DESC_GET_NEXT(curr) == 0)
				curr->desc.mbr_ubc &= ~XDMA_UBC_NDE_FETCH_EN;
		}

#elif defined(CONFIG_HAVE_DMAC)
		curr->desc.ctrla = (cfg->data_width << DMAC_CTRLA_SRC_WIDTH_Pos)
			| (cfg->data_width << DMAC_CTRLA_DST_WIDTH_Pos)
			| (cfg->chunk_size << DMAC_CTRLA_SCSIZE_Pos)
			| (cfg->chunk_size << DMAC_CTRLA_DCSIZE_Pos)
			| DMAC_CTRLA_BTSIZE(data->len);

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

		curr->desc.ctrlb |= cfg->incr_saddr ? DMAC_CTRLB_SRC_INCR_INCREMENTING : DMAC_CTRLB_SRC_INCR_FIXED;
		curr->desc.ctrlb |= cfg->incr_daddr ? DMAC_CTRLB_DST_INCR_INCREMENTING : DMAC_CTRLB_DST_INCR_FIXED;

		curr->desc.ctrlb |= DMAC_CTRLB_SRC_DSCR_FETCH_FROM_MEM | DMAC_CTRLB_DST_DSCR_FETCH_FROM_MEM;

#endif
		if (DMA_SG_DESC_GET_NEXT(curr) == 0)
			if (cfg->loop)
				DMA_SG_DESC_SET_NEXT(curr, _sg_head);
		curr = DMA_SG_DESC_GET_NEXT(curr);
		data = data->next;
	}
	channel->sg_list = _sg_head;

	/* Update configuration */
#if defined(CONFIG_HAVE_XDMAC)

	struct _xdmacd_cfg xdmacd_cfg;
	uint32_t desc_ctrl;

	xdmacd_cfg.cfg = (src_is_periph | dst_is_periph) ? XDMAC_CC_TYPE_PER_TRAN : XDMAC_CC_TYPE_MEM_TRAN;
	xdmacd_cfg.cfg |= src_is_periph ? XDMAC_CC_DSYNC_PER2MEM : XDMAC_CC_DSYNC_MEM2PER;
	xdmacd_cfg.cfg |= XDMAC_CC_CSIZE(cfg->chunk_size);
	xdmacd_cfg.cfg |= XDMAC_CC_DWIDTH(cfg->data_width);
	xdmacd_cfg.cfg |= src_is_periph ? XDMAC_CC_SIF_AHB_IF1 : XDMAC_CC_SIF_AHB_IF0;
	xdmacd_cfg.cfg |= dst_is_periph ? XDMAC_CC_DIF_AHB_IF1 : XDMAC_CC_DIF_AHB_IF0;
	xdmacd_cfg.cfg |= cfg->incr_saddr ? XDMAC_CC_SAM_INCREMENTED_AM : XDMAC_CC_SAM_FIXED_AM;
	xdmacd_cfg.cfg |= cfg->incr_daddr ? XDMAC_CC_DAM_INCREMENTED_AM : XDMAC_CC_DAM_FIXED_AM;
	xdmacd_cfg.cfg |= (src_is_periph | dst_is_periph) ? 0 : XDMAC_CC_SWREQ_SWR_CONNECTED;
	xdmacd_cfg.bc = 0;
	xdmacd_cfg.ds = 0;
	xdmacd_cfg.sus = 0;
	xdmacd_cfg.dus = 0;

	desc_ctrl = XDMAC_CNDC_NDVIEW_NDV1
	           | XDMAC_CNDC_NDE_DSCR_FETCH_EN
	           | XDMAC_CNDC_NDSUP_SRC_PARAMS_UPDATED
	           | XDMAC_CNDC_NDDUP_DST_PARAMS_UPDATED;

	cache_clean_region(_dma_sg_pool.desc, sizeof(_dma_sg_pool.desc));

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

	cache_clean_region(_dma_sg_pool.desc, sizeof(_dma_sg_pool.desc));

	return dmacd_configure_transfer(channel, &dmacd_cfg, (void *)_sg_head);
#endif
}

uint32_t dma_get_transferred_data_len(struct _dma_channel* channel, uint8_t chunk_size, uint32_t len)
{
#if defined(CONFIG_HAVE_XDMAC)
	return len - xdmacd_get_remaining_data_len(channel) * (1 << chunk_size);
#elif defined(CONFIG_HAVE_DMAC)
	return dmacd_get_transferred_data_len(channel) * (1 << chunk_size);
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
