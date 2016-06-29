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
#include <assert.h>
#include "compiler.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/
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
	xdmad_callback_t callback;	/* Callback */
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
};

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

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void dma_initialize(bool polling)
{
#if defined(CONFIG_HAVE_XDMAC)
	xdmad_initialize(polling);
#elif defined(CONFIG_HAVE_DMAC)
	dmacd_initialize(polling);
#endif
}

struct dma_channel *dma_allocate_channel(uint8_t src, uint8_t dest)
{
#if defined(CONFIG_HAVE_XDMAC)
	return (struct dma_channel *)xdmad_allocate_channel(src, dest);
#elif defined(CONFIG_HAVE_DMAC)
	return (struct dma_channel *)dmacd_allocate_channel(src, dest);
#endif
}

uint32_t dma_free_channel(struct dma_channel *channel)
{
#if defined(CONFIG_HAVE_XDMAC)
	return xdmad_free_channel((struct _xdmad_channel *)channel);
#elif defined(CONFIG_HAVE_DMAC)
	return dmacd_free_channel((struct _dmacd_channel *)channel);
#endif
}

uint32_t dma_set_callback(struct dma_channel *channel,
		dma_callback_t callback, void *user_arg)
{
#if defined(CONFIG_HAVE_XDMAC)
	return xdmad_set_callback((struct _xdmad_channel *)channel,
	(xdmad_callback_t)callback, user_arg);
#elif defined(CONFIG_HAVE_DMAC)
	return dmacd_set_callback((struct _dmacd_channel *)channel,
	(dmacd_callback_t)callback, user_arg);
#endif
}

uint32_t dma_configure_transfer(struct dma_channel *channel,
								const struct dma_xfer_cfg *cfg)
{
	bool src_is_periph, dst_is_periph;
	uint32_t i;
	uint32_t divisor;

#if defined(CONFIG_HAVE_XDMAC)
	struct _xdmad_cfg xdma_cfg;
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
			for (i = 2; i < DMA_MAX_BT_SIZE; i++) {
				divisor = DMA_MAX_BT_SIZE / i;
				if (cfg->len % divisor)
					continue;
				if ((cfg->len / divisor) <= XDMAC_MAX_BLOCK_LEN) {
					xdma_cfg.ubc = i;
					xdma_cfg.bc = (cfg->len / divisor) - 1;
					break;
				}
			}
			if (i == DMA_MAX_BT_SIZE)
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

	return xdmad_configure_transfer((struct _xdmad_channel *)channel, &xdma_cfg, 0, 0);

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
			for (i = 2; i < DMA_MAX_BT_SIZE; i++) {
				divisor = DMA_MAX_BT_SIZE / i;
				if (cfg->len % divisor)
					continue;
				if ((cfg->len / divisor ) <= DMA_MAX_BLOCK_LEN) {
					dma_regs.ctrla = i;
					dma_cfg.blocks = cfg->len - 1;
					dma_cfg.trans_auto = 1;
					dma_cfg.sa_rep = src_is_periph ? 1 : 0 ;
					dma_cfg.da_rep = dst_is_periph ? 1 : 0 ;
					break;
				}
			}
			if (i == DMA_MAX_BT_SIZE)
				return DMA_ERROR;
		}
	} else {
		dma_regs.ctrla = cfg->blk_size;
		dma_cfg.blocks = cfg->len - 1;
		dma_cfg.trans_auto = dma_cfg.blocks ? 1 : 0;
		dma_cfg.sa_rep = src_is_periph ? 1 : 0 ;
		dma_cfg.da_rep = dst_is_periph ? 1 : 0 ;
	}
	dma_cfg.cfg = src_is_periph ? DMAC_CFG_SRC_H2SEL_HW : 0;
	dma_cfg.cfg |= dst_is_periph ? DMAC_CFG_DST_H2SEL_HW : 0;

	dma_regs.sa = cfg->sa;
	dma_regs.da = cfg->da;

	dma_regs.ctrla |= (cfg->data_width << DMAC_CTRLA_SRC_WIDTH_Pos)
				   | (cfg->data_width << DMAC_CTRLA_DST_WIDTH_Pos)
				   | (cfg->chunk_size << DMAC_CTRLA_SCSIZE_Pos)
				   | (cfg->chunk_size << DMAC_CTRLA_DCSIZE_Pos);

	dma_regs.ctrlb = (src_is_periph ? DMAC_CTRLB_SIF_AHB_IF2: DMAC_CTRLB_SIF_AHB_IF0)
					 | (dst_is_periph ? DMAC_CTRLB_DIF_AHB_IF2: DMAC_CTRLB_DIF_AHB_IF0);

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

	ctrlb = src_is_periph ? DMAC_CTRLB_SIF_AHB_IF2: DMAC_CTRLB_SIF_AHB_IF0;
	ctrlb |= dst_is_periph ? DMAC_CTRLB_DIF_AHB_IF2: DMAC_CTRLB_DIF_AHB_IF0;
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

uint32_t dma_link_item(struct dma_channel *channel,
				struct dma_xfer_item *item,
				struct dma_xfer_item *next_item)
{
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

uint32_t dma_configure_sg_transfer(struct dma_channel *channel,
				struct dma_xfer_item_tmpl *tmpl,
				struct dma_xfer_item *desc_list)
{
#if defined(CONFIG_HAVE_XDMAC)
	struct _xdmad_cfg xdma_cfg;
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

	return xdmad_configure_transfer((struct _xdmad_channel *)channel, &xdma_cfg, desc_cntrl, (void *)desc_list);
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

	return dmacd_configure_transfer((struct _dmacd_channel *)channel, &dma_cfg, (void *)desc_list);
#endif
}

uint32_t dma_start_transfer(struct dma_channel *channel)
{
#if defined(CONFIG_HAVE_XDMAC)
	return xdmad_start_transfer((struct _xdmad_channel *)channel);
#elif defined(CONFIG_HAVE_DMAC)
	return dmacd_start_transfer((struct _dmacd_channel *)channel);
#endif
}

bool dma_is_transfer_done(struct dma_channel *channel)
{
#if defined(CONFIG_HAVE_XDMAC)
	return xdmad_is_transfer_done((struct _xdmad_channel *)channel);
#elif defined(CONFIG_HAVE_DMAC)
	return dmacd_is_transfer_done((struct _dmacd_channel *)channel);
#endif
}

uint32_t dma_stop_transfer(struct dma_channel *channel)
{
#if defined(CONFIG_HAVE_XDMAC)
	return xdmad_stop_transfer((struct _xdmad_channel *)channel);
#elif defined(CONFIG_HAVE_DMAC)
	return dmacd_stop_transfer((struct _dmacd_channel *)channel);
#endif
}

void dma_poll(void)
{
#if defined(CONFIG_HAVE_XDMAC)
	xdmad_poll();
#elif defined(CONFIG_HAVE_DMAC)
	dmacd_poll();
#endif
}

/**@}*/
