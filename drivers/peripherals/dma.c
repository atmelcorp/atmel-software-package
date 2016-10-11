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
 *        Includes
 *----------------------------------------------------------------------------*/

#include "peripherals/aic.h"
#include "peripherals/pmc.h"
#include "peripherals/dma.h"
#include "misc/cache.h"

#include <assert.h>
#include "compiler.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/
struct _ll_item {
	struct dma_xfer_item *ll;
	struct _ll_item* next;
};

/** DMA driver channel */
struct dma_channel
{
#if defined(CONFIG_HAVE_XDMAC)
	Xdmac *dmac;				/* XDMAC instance */
#elif defined(CONFIG_HAVE_DMAC)
	Dmac *dmac;					/* XDMAC instance */
#endif
	uint32_t id;				/* Channel ID */

#if defined(CONFIG_HAVE_XDMAC)
	xdmacd_callback_t callback;	/* Callback */
#elif defined(CONFIG_HAVE_DMAC)
	dmacd_callback_t callback;	/* Callback */
#endif
	void *user_arg;				/* Callback argument */
	uint8_t src_txif;			/* Source TX Interface ID */
	uint8_t src_rxif;			/* Source RX Interface ID */
	uint8_t dest_txif;			/* Destination TX Interface ID */
	uint8_t dest_rxif;			/* Destination RX Interface ID */
#ifdef CONFIG_HAVE_DMAC
	volatile uint32_t rep_count;/* repeat count in auto mode */
#endif
	volatile uint8_t state;		/* Channel State */
	struct _ll_item* ll_head;	/* pointer to the head of linked list */
};


static struct _ll_item  _ll_item_pool[DMA_LL_POOL_SIZE];
static struct _ll_item* _ll_next_free_item;

/** DMA Linked List */
CACHE_ALIGNED static struct dma_xfer_item _item_pool[DMA_LL_POOL_SIZE];

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
static inline bool is_source_periph(struct dma_channel *channel)
{
	return ((channel->src_txif != 0xff) | (channel->src_rxif != 0xff));
}

static inline bool is_dest_periph(struct dma_channel *channel)
{
	return ((channel->dest_txif != 0xff) | (channel->dest_rxif != 0xff));
}

static void _initialize_item_pool(void)
{
	uint32_t i;

	for (i = 0; i < ARRAY_SIZE(_ll_item_pool); i++) {
#if defined(CONFIG_HAVE_XDMAC)
		_item_pool[i].mbr_nda = NULL;
#elif defined(CONFIG_HAVE_DMAC)
		_item_pool[i].dscr = NULL;
#endif
		_ll_item_pool[i].ll = &_item_pool[i];
		_ll_item_pool[i].next = &_ll_item_pool[i + 1];
	}
	_ll_item_pool[i - 1].next = NULL;
	_ll_next_free_item = &_ll_item_pool[0];
}

static struct _ll_item* _allocate_ll_item(void)
{
	struct _ll_item* item;

	assert(_ll_next_free_item);

	item = _ll_next_free_item;
#if defined(CONFIG_HAVE_XDMAC)
		item->ll->mbr_nda = NULL;
#elif defined(CONFIG_HAVE_DMAC)
		item->ll->dscr = NULL;
#endif
	_ll_next_free_item = _ll_next_free_item->next;
	item->next = NULL;
	return item;
}

static struct dma_xfer_item* _get_last_ll_item(struct dma_channel *channel)
{
	struct _ll_item* last = channel->ll_head;

	if (channel->ll_head == NULL) {
		return NULL;
	} else {
		while (last->next) {
#if defined(CONFIG_HAVE_XDMAC)
			if (!last->ll->mbr_nda)
				break;
#elif defined(CONFIG_HAVE_DMAC)
			if (!last->ll->dscr)
				break;
#endif
			last = last->next;
		}
	}
	return last->ll;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void dma_initialize(bool polling)
{
	_initialize_item_pool();
#if defined(CONFIG_HAVE_XDMAC)
	xdmacd_initialize(polling);
#elif defined(CONFIG_HAVE_DMAC)
	dmacd_initialize(polling);
#endif
}

struct dma_channel *dma_allocate_channel(uint8_t src, uint8_t dest)
{
	struct dma_channel *chan;
#if defined(CONFIG_HAVE_XDMAC)
	chan =  (struct dma_channel *)xdmacd_allocate_channel(src, dest);
#elif defined(CONFIG_HAVE_DMAC)
	chan = (struct dma_channel *)dmacd_allocate_channel(src, dest);
#endif
	chan->ll_head = NULL;
	return chan;
}

uint32_t dma_free_channel(struct dma_channel *channel)
{
	uint32_t status;

#if defined(CONFIG_HAVE_XDMAC)
	status = xdmacd_free_channel((struct _xdmacd_channel *)channel);
#elif defined(CONFIG_HAVE_DMAC)
	status = dmacd_free_channel((struct _dmacd_channel *)channel);
#endif
	dma_free_item(channel);
	return status;
}

uint32_t dma_set_callback(struct dma_channel *channel,
		dma_callback_t callback, void *user_arg)
{
#if defined(CONFIG_HAVE_XDMAC)
	return xdmacd_set_callback((struct _xdmacd_channel *)channel,
	(xdmacd_callback_t)callback, user_arg);
#elif defined(CONFIG_HAVE_DMAC)
	return dmacd_set_callback((struct _dmacd_channel *)channel,
	(dmacd_callback_t)callback, user_arg);
#endif
}

uint32_t dma_configure_transfer(struct dma_channel *channel,
								const struct dma_xfer_cfg *cfg)
{
	bool src_is_periph, dst_is_periph;
	uint32_t divisor;

#if defined(CONFIG_HAVE_XDMAC)
	struct _xdmacd_cfg xdma_cfg;
#elif defined(CONFIG_HAVE_DMAC)
	struct _dmacd_cfg dma_cfg;
	struct _dma_desc dma_regs;
#endif

	src_is_periph = is_source_periph(channel);
	dst_is_periph = is_dest_periph(channel);

#if defined(CONFIG_HAVE_XDMAC)
/* for DMAC */
	if (cfg->blk_size > DMA_MAX_BT_SIZE) {
		/* Block size (microblock length) is limited to 16,777,215 data elements */
		return DMA_ERROR;
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
				return DMA_ERROR;
		}
	} else {
		if (cfg->len <= XDMAC_MAX_BLOCK_LEN) {
			xdma_cfg.ubc = cfg->blk_size;
			xdma_cfg.bc = cfg->len - 1;
		} else {
			return DMA_ERROR;
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

	return xdmacd_configure_transfer((struct _xdmacd_channel *)channel, &xdma_cfg, 0, 0);

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
		return DMA_ERROR;
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
			return DMA_ERROR;
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

	dma_regs.sa = cfg->sa;
	dma_regs.da = cfg->da;

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

	return dmacd_configure_transfer((struct _dmacd_channel *)channel, &dma_cfg, &dma_regs);
#endif
}

uint32_t dma_prepare_item(struct dma_channel *channel,
				const struct dma_xfer_item_tmpl *tmpl,
				struct dma_xfer_item *item)
{

#if defined(CONFIG_HAVE_XDMAC)

	if (tmpl->blk_size > DMA_MAX_BT_SIZE) {
				/* Block size (microblock length) is limited to 65535 data elements */
		return DMA_ERROR;
	}
	item->mbr_ubc = XDMA_UBC_NVIEW_NDV1
					| (tmpl->upd_sa_per_blk ? XDMA_UBC_NSEN_UPDATED :
						XDMA_UBC_NSEN_UNCHANGED)
					| (tmpl->upd_da_per_blk ? XDMA_UBC_NDEN_UPDATED :
						XDMA_UBC_NDEN_UNCHANGED)
					| XDMA_UBC_NDE_FETCH_EN
					| tmpl->blk_size;
	item->mbr_sa = tmpl->sa;
	item->mbr_da = tmpl->da;
	item->mbr_nda = 0;

	return DMA_OK;

#elif defined(CONFIG_HAVE_DMAC)

	bool src_is_periph, dst_is_periph;
	uint32_t ctrla,ctrlb;

	src_is_periph = is_source_periph(channel);
	dst_is_periph = is_dest_periph(channel);

	if (tmpl->blk_size > DMA_MAX_BT_SIZE) {
		/* Block size (microblock length) is limited to 65535 data elements */
		return DMA_ERROR;
	}
	ctrla = (tmpl->data_width << DMAC_CTRLA_SRC_WIDTH_Pos)
		  | (tmpl->data_width << DMAC_CTRLA_DST_WIDTH_Pos)
		  | (tmpl->chunk_size << DMAC_CTRLA_SCSIZE_Pos)
		  | (tmpl->chunk_size << DMAC_CTRLA_DCSIZE_Pos)
		  | tmpl->blk_size ;

#if defined(CONFIG_SOC_SAMA5D3)
	ctrlb = src_is_periph ? DMAC_CTRLB_SIF_AHB_IF2 : DMAC_CTRLB_SIF_AHB_IF0;
	ctrlb |= dst_is_periph ? DMAC_CTRLB_DIF_AHB_IF2 : DMAC_CTRLB_DIF_AHB_IF0;
#elif defined(CONFIG_SOC_SAM9XX5)
	ctrlb = src_is_periph ? DMAC_CTRLB_SIF_AHB_IF1 : DMAC_CTRLB_SIF_AHB_IF0;
	ctrlb |= dst_is_periph ? DMAC_CTRLB_DIF_AHB_IF1 : DMAC_CTRLB_DIF_AHB_IF0;
#else
#error Unknown SoC!
#endif
	ctrlb |= ((src_is_periph) ? DMAC_CTRLB_FC_PER2MEM_DMA_FC :
		    ((dst_is_periph) ? DMAC_CTRLB_FC_MEM2PER_DMA_FC :  DMAC_CTRLB_FC_MEM2MEM_DMA_FC));
	ctrlb |= (tmpl->upd_sa_per_data ? DMAC_CTRLB_SRC_INCR_INCREMENTING:
			  DMAC_CTRLB_SRC_INCR_FIXED)
		   | (tmpl->upd_da_per_data ? DMAC_CTRLB_DST_INCR_INCREMENTING:
			 DMAC_CTRLB_DST_INCR_FIXED);

	ctrlb |= tmpl->upd_sa_per_blk ? DMAC_CTRLB_SRC_DSCR_FETCH_FROM_MEM :
				DMAC_CTRLB_SRC_DSCR_FETCH_DISABLE
		   | tmpl->upd_da_per_blk ? DMAC_CTRLB_DST_DSCR_FETCH_FROM_MEM :
				DMAC_CTRLB_DST_DSCR_FETCH_DISABLE ;
	item->saddr = tmpl->sa;
	item->daddr = tmpl->da;
	item->ctrla = ctrla;
	item->ctrlb = ctrlb;

	return DMA_OK;
#endif
}

struct dma_xfer_item* dma_allocate_item(struct dma_channel *channel)
{
	struct _ll_item* item = _allocate_ll_item();
	struct _ll_item* last = channel->ll_head;

	if (item) {
		if (channel->ll_head == NULL) {
			channel->ll_head = item;
		} else {
			while (last->next)
				last = last->next;
			last->next = item;
		}
		return item->ll;
	}

	return NULL;
}

void dma_free_item(struct dma_channel *channel)
{
	struct _ll_item* item = channel->ll_head;
	struct _ll_item* next = _ll_next_free_item;

	while (next->next)
		next = next->next;
	next->next = item;
	channel->ll_head = NULL;
}

uint32_t dma_link_item(struct dma_channel *channel,
		       struct dma_xfer_item *item,
		       struct dma_xfer_item *next_item)
{
	if (item == NULL)
		return DMA_ERROR;

	if (!dma_is_transfer_done(channel)) {
		/* DMA is being transmitted */
		return DMA_CANCELED;
	}

#if defined(CONFIG_HAVE_XDMAC)
	if (next_item == NULL) {
		item->mbr_ubc &= ~XDMA_UBC_NDE_FETCH_EN;
		item->mbr_nda = 0;
	} else {
		item->mbr_nda = next_item;
	}
#elif defined(CONFIG_HAVE_DMAC)
	if (next_item == NULL)
		item->dscr = 0;
	else
		item->dscr = next_item;
#endif
	return DMA_OK;
}

uint32_t dma_link_last_item(struct dma_channel *channel,
							struct dma_xfer_item *item)
{
	struct dma_xfer_item *last;

	if (item == NULL)
		return DMA_ERROR;

	if (!dma_is_transfer_done(channel)) {
		/* DMA is being transmitted */
		return DMA_CANCELED;
	}
	last = _get_last_ll_item(channel);
	if (!last)
		return DMA_ERROR;
	
	if ((uint32_t)(channel->ll_head->ll) == (uint32_t)item)
		return DMA_OK;

#if defined(CONFIG_HAVE_XDMAC)
	if (item == NULL) {
		last->mbr_ubc &= ~XDMA_UBC_NDE_FETCH_EN;
		last->mbr_nda = 0;
	} else {
		last->mbr_nda = item;
	}
#elif defined(CONFIG_HAVE_DMAC)
	if (item == NULL)
		last->dscr = 0;
	else
		last->dscr = item;
#endif
	return DMA_OK;
}

uint32_t dma_insert_item(struct dma_channel *channel,
			 struct dma_xfer_item *pre_item,
			 struct dma_xfer_item *item)
{
	struct dma_xfer_item* next;

	if (item == NULL || pre_item == NULL) {
		return DMA_ERROR;
	}
	if (dma_is_transfer_done(channel)) {
		/* DMA was done*/
		return DMA_CANCELED;
	}
	if (!(dma_get_desc_addr(channel))) {
		/* LL transfer was done or it is a single transfer */
		return DMA_CANCELED;
	}

#if defined(CONFIG_HAVE_XDMAC)
	next =(struct dma_xfer_item*) pre_item->mbr_nda;
	pre_item->mbr_nda = item;
	item->mbr_nda = next;
	if (next == NULL) {
		pre_item->mbr_ubc |= XDMA_UBC_NDE_FETCH_EN;
		item->mbr_ubc &= ~XDMA_UBC_NDE_FETCH_EN;
		item->mbr_nda = 0;
	}
#elif defined(CONFIG_HAVE_DMAC)
	next = (struct dma_xfer_item*)pre_item->dscr;
	pre_item->dscr = item;
	item->dscr = next;
	if (next == NULL)
		item->dscr = 0;
#endif
	return DMA_OK;
}

uint32_t dma_append_item(struct dma_channel *channel, struct dma_xfer_item *item)
{
	struct dma_xfer_item* last;
	struct dma_xfer_item* descriptor_addr;

	if (item == NULL)
		return DMA_ERROR;

	if (dma_is_transfer_done(channel)) {
		/* DMA was done*/
		return DMA_CANCELED;
	}
	descriptor_addr = dma_get_desc_addr(channel);
	if (descriptor_addr == NULL) {
		/* LL transfer was done or it is a single transfer */
		return DMA_CANCELED;
	}
	last = descriptor_addr;

#if defined(CONFIG_HAVE_XDMAC)
	while (last->mbr_nda)
		last = (struct dma_xfer_item *)last->mbr_nda;
	last->mbr_nda = item;
	last->mbr_ubc |= XDMA_UBC_NDE_FETCH_EN;
	item->mbr_ubc &= ~XDMA_UBC_NDE_FETCH_EN;
	item->mbr_nda = 0;

#elif defined(CONFIG_HAVE_DMAC)
	while (last->dscr)
		last =(struct dma_xfer_item*)last->dscr;
	last->dscr = item;
	item->dscr = 0;
#endif
	return DMA_OK;
}

uint32_t dma_remove_last_item(struct dma_channel *channel)
{
	struct dma_xfer_item* last;
	struct dma_xfer_item* descriptor_addr;

	if (dma_is_transfer_done(channel)) {
		/* DMA was done*/
		return DMA_CANCELED;
	}
	descriptor_addr = dma_get_desc_addr(channel);
	if (descriptor_addr == NULL) {
		/* LL transfer was done or it is a single transfer */
		return DMA_CANCELED;
	}
	last = descriptor_addr;

#if defined(CONFIG_HAVE_XDMAC)
	if (last->mbr_nda == NULL)
		return DMA_OK;
	while (((struct dma_xfer_item*)(last->mbr_nda))->mbr_nda) {
		last =(struct dma_xfer_item*)last->mbr_nda;
	}
	last->mbr_ubc &= ~XDMA_UBC_NDE_FETCH_EN;
	last->mbr_nda = 0;

#elif defined(CONFIG_HAVE_DMAC)
	if (last->dscr == NULL)
		return DMA_OK;
	while (((struct dma_xfer_item*)(last->dscr))->dscr) {
		last =(struct dma_xfer_item*)last->dscr;
	}
	last->dscr = 0;
#endif
	return DMA_OK;
}

uint32_t dma_configure_sg_transfer(struct dma_channel *channel,
				struct dma_xfer_item_tmpl *tmpl,
				struct dma_xfer_item *desc_list)
{
	if (!desc_list) {
		if (channel->ll_head == NULL)
			return DMA_ERROR;
		else 
			desc_list = channel->ll_head->ll;
	}

#if defined(CONFIG_HAVE_XDMAC)
	struct _xdmacd_cfg xdma_cfg;
	bool src_is_periph, dst_is_periph;
	uint32_t desc_cntrl;

	if (tmpl->blk_size > DMA_MAX_BT_SIZE) {
		/* Block size (microblock length) is limited to 65535 data elements */
		return DMA_ERROR;
	}

	src_is_periph = is_source_periph(channel);
	dst_is_periph = is_dest_periph(channel);
	xdma_cfg.cfg = (src_is_periph | dst_is_periph) ?
					XDMAC_CC_TYPE_PER_TRAN : XDMAC_CC_TYPE_MEM_TRAN;
	xdma_cfg.cfg |= src_is_periph ? XDMAC_CC_DSYNC_PER2MEM:
					 XDMAC_CC_DSYNC_MEM2PER;
	xdma_cfg.cfg |= (src_is_periph ? XDMAC_CC_CSIZE(tmpl->chunk_size) : 0)
				 | (dst_is_periph ? XDMAC_CC_CSIZE(tmpl->chunk_size) : 0);
	xdma_cfg.cfg |= XDMAC_CC_DWIDTH(tmpl->data_width);
	xdma_cfg.cfg |= src_is_periph ? XDMAC_CC_SIF_AHB_IF1:
					XDMAC_CC_SIF_AHB_IF0;
	xdma_cfg.cfg |= dst_is_periph ? XDMAC_CC_DIF_AHB_IF1:
					XDMAC_CC_DIF_AHB_IF0;
	xdma_cfg.cfg |= tmpl->upd_sa_per_data ? XDMAC_CC_SAM_INCREMENTED_AM :
					XDMAC_CC_SAM_FIXED_AM;
	xdma_cfg.cfg |= tmpl->upd_da_per_data ? XDMAC_CC_DAM_INCREMENTED_AM :
					XDMAC_CC_DAM_FIXED_AM;
	xdma_cfg.cfg |= (src_is_periph | dst_is_periph) ? 0: XDMAC_CC_SWREQ_SWR_CONNECTED;
	xdma_cfg.bc = 0;
	xdma_cfg.ds = 0;
	xdma_cfg.sus = 0;
	xdma_cfg.dus = 0;

	desc_cntrl = XDMAC_CNDC_NDVIEW_NDV1
				| XDMAC_CNDC_NDE_DSCR_FETCH_EN
				| XDMAC_CNDC_NDSUP_SRC_PARAMS_UPDATED
				| XDMAC_CNDC_NDDUP_DST_PARAMS_UPDATED;
	if (channel->ll_head != NULL)
		cache_clean_region(_item_pool, sizeof(_item_pool));
	return xdmacd_configure_transfer((struct _xdmacd_channel *)channel, &xdma_cfg, desc_cntrl, (void *)desc_list);
#elif defined(CONFIG_HAVE_DMAC)

	bool src_is_periph, dst_is_periph;
	struct _dmacd_cfg dma_cfg;

	src_is_periph = is_source_periph(channel);
	dst_is_periph = is_dest_periph(channel);

	dma_cfg.s_decr_fetch = tmpl->upd_sa_per_blk ? 0 : 1;
	dma_cfg.d_decr_fetch = tmpl->upd_da_per_blk ? 0 : 1;
	dma_cfg.sa_rep = 0;
	dma_cfg.da_rep = 0;
	dma_cfg.trans_auto = 0;
	dma_cfg.blocks = 0;
	dma_cfg.s_pip = 0;
	dma_cfg.d_pip = 0;
	dma_cfg.cfg = src_is_periph ? DMAC_CFG_SRC_H2SEL_HW : 0;
	dma_cfg.cfg |= dst_is_periph ? DMAC_CFG_DST_H2SEL_HW : 0;
	if (channel->ll_head != NULL)
		cache_clean_region(_item_pool, sizeof(_item_pool));

	return dmacd_configure_transfer((struct _dmacd_channel *)channel, &dma_cfg, (void *)desc_list);
#endif
}

uint32_t dma_start_transfer(struct dma_channel *channel)
{
#if defined(CONFIG_HAVE_XDMAC)
	return xdmacd_start_transfer((struct _xdmacd_channel *)channel);
#elif defined(CONFIG_HAVE_DMAC)
	return dmacd_start_transfer((struct _dmacd_channel *)channel);
#endif
}

bool dma_is_transfer_done(struct dma_channel *channel)
{
#if defined(CONFIG_HAVE_XDMAC)
	return xdmacd_is_transfer_done((struct _xdmacd_channel *)channel);
#elif defined(CONFIG_HAVE_DMAC)
	return dmacd_is_transfer_done((struct _dmacd_channel *)channel);
#endif
}

uint32_t dma_stop_transfer(struct dma_channel *channel)
{
#if defined(CONFIG_HAVE_XDMAC)
	return xdmacd_stop_transfer((struct _xdmacd_channel *)channel);
#elif defined(CONFIG_HAVE_DMAC)
	return dmacd_stop_transfer((struct _dmacd_channel *)channel);
#endif
}

uint32_t dma_suspend_transfer(struct dma_channel *channel)
{
#if defined(CONFIG_HAVE_XDMAC)
	return xdmacd_suspend_transfer((struct _xdmacd_channel *)channel);
#elif defined(CONFIG_HAVE_DMAC)
	return dmacd_suspend_transfer((struct _dmacd_channel *)channel);
#endif
}

uint32_t dma_resume_transfer(struct dma_channel *channel)
{
#if defined(CONFIG_HAVE_XDMAC)
	return xdmacd_resume_transfer((struct _xdmacd_channel *)channel);
#elif defined(CONFIG_HAVE_DMAC)
	return dmacd_resume_transfer((struct _dmacd_channel *)channel);
#endif
}

void dma_poll(void)
{
#if defined(CONFIG_HAVE_XDMAC)
	xdmacd_poll();
#elif defined(CONFIG_HAVE_DMAC)
	dmacd_poll();
#endif
}

uint32_t dma_get_transferred_data_len(struct dma_channel *channel, uint8_t chunk_size, uint32_t len)
{
#if defined(CONFIG_HAVE_XDMAC)
	return len - xdmacd_get_remaining_data_len((struct _xdmacd_channel *)channel) * (1 << chunk_size);
#elif defined(CONFIG_HAVE_DMAC)
	return dmacd_get_transferred_data_len((struct _dmacd_channel *)channel) * (1 << chunk_size);
#endif
}

struct dma_xfer_item* dma_get_desc_addr(struct dma_channel *channel)
{
	uint32_t _xfer_item = 0;

#if defined(CONFIG_HAVE_XDMAC)
	_xfer_item = xdmacd_get_desc_addr((struct _xdmacd_channel *)channel);
#elif defined(CONFIG_HAVE_DMAC)
	_xfer_item = dmacd_get_desc_addr((struct _dmacd_channel *)channel);
#endif

	return ((struct dma_xfer_item*)_xfer_item);
}

void dma_fifo_flush(struct dma_channel *channel)
{
#if defined(CONFIG_HAVE_XDMAC)
	xdmacd_fifo_flush((struct _xdmacd_channel *)channel);
#elif defined(CONFIG_HAVE_DMAC)
	dmacd_fifo_flush((struct _dmacd_channel *)channel);
#endif
}

/**@}*/
