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

#include <stdint.h>

#include "chip.h"
#include "trace.h"
#include "compiler.h"
#include "intmath.h"
#include "plugin_sha.h"
#include "peripherals/pmc.h"
#include "peripherals/aic.h"
#include "peripherals/l2cc.h"
#include "peripherals/xdmad.h"
#include "peripherals/sha.h"

#include <assert.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static volatile bool busy = false;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Pad message data as per FIPS requirement.
 * \param data  Output data buffer ready to receive padding data, up to 72
 * bytes. It should point to the end of message data.
 * \param length  Size of the whole message (upcoming padding excluded), in
 * bytes.
 * \return Number of padding bytes added.
 */
static uint8_t pad_message(uint8_t *data, uint32_t length)
{
	/* k ranges from 7 to 511 */
	const uint16_t k = (512 + 448 - (((length << 3) % 512) + 1)) % 512;
	uint8_t ofs = 0;

	/* Append a bit '1' to the message, followed by k zero bits */
	data[ofs++] = 0x80;
	memset(data + ofs, 0, (k - 7) / 8);
	ofs += (uint8_t)((k - 7) / 8);
	/* Then append the block length, expressed in bits, in a 64-bit field */
	memset(data + ofs, 0, 3);
	ofs += 3;
	data[ofs++] = length >> 29 & 0x7;
	data[ofs++] = length >> 21 & 0xff;
	data[ofs++] = length >> 13 & 0xff;
	data[ofs++] = length >> 5 & 0xff;
	data[ofs++] = length << 3 & 0xff;
	return ofs;
}

/**
 * \brief Have the DMA execute the transfer previously programmed by
 * calling write_blocks() several times.
 */
static void run_dma_xfer(struct sha_set *set)
{
	struct _xdmad_cfg dma_cfg = {
		/* Configure a single microblock per block */
		.block_size = 1,
		/* Configure 4 bytes per data, and 16 data per chunk */
		.cfg.uint32_value = XDMAC_CC_TYPE_PER_TRAN
		    | XDMAC_CC_MBSIZE_SINGLE | XDMAC_CC_DSYNC_MEM2PER
		    | XDMAC_CC_MEMSET_NORMAL_MODE | XDMAC_CC_CSIZE_CHK_16
		    | XDMAC_CC_DWIDTH_WORD | XDMAC_CC_SIF_AHB_IF0
		    | XDMAC_CC_DIF_AHB_IF1 | XDMAC_CC_SAM_INCREMENTED_AM
		    | XDMAC_CC_DAM_FIXED_AM,
	};
	struct _xdmad_desc_view1 *desc = NULL, *last_desc = NULL;
	uint32_t addr, rc;

	assert(set->dma_ch);
	assert(set->dlist_len <= ARRAY_SIZE(set->dma_dlist));
	if (set->dlist_len == 0)
		return;
	if (set->dlist_len == 1) {
		desc = set->dma_dlist;
		/* Configure data count per microblock */
		dma_cfg.ublock_size = desc->ublock_size;
		/* Configure source and destination addresses */
		dma_cfg.src_addr = desc->src_addr;
		dma_cfg.dest_addr = (void*)&SHA->SHA_IDATAR[0];
		/* Configure a single block per master transfer, i.e. no linked
		 * list */
		xdmad_configure_transfer(set->dma_ch, &dma_cfg,
		    XDMAC_CNDC_NDE_DSCR_FETCH_DIS, NULL);
	}
	else {
		last_desc = set->dma_dlist + (set->dlist_len - 1);
		for (desc = set->dma_dlist; desc <= last_desc; desc++) {
			/* Complete descriptor contents */
			desc->ublock_size = (desc == last_desc
			    ? XDMA_UBC_NDE_FETCH_DIS
			    : XDMA_UBC_NVIEW_NDV1 | XDMA_UBC_NDEN_UNCHANGED
			    | XDMA_UBC_NSEN_UPDATED | XDMA_UBC_NDE_FETCH_EN)
			    | XDMA_UBC_UBLEN(desc->ublock_size);
			desc->dest_addr = (void*)&SHA->SHA_IDATAR[0];
			desc->next_desc = desc == last_desc ? NULL : desc + 1;
		}
		/* Clean the underlying cache lines, to ensure the DMA gets our
		 * descriptors when it reads from RAM.
		 * CPU access to the table is write-only, DMA access is
		 * read-only, hence there is no need to invalidate. */
		addr = (uint32_t)set->dma_dlist;
		l2cc_clean_region(addr, addr + sizeof(*last_desc)
		    * (uint32_t)set->dlist_len);
		xdmad_configure_transfer(set->dma_ch, &dma_cfg,
		    XDMAC_CNDC_NDVIEW_NDV1 | XDMAC_CNDC_NDDUP_DST_PARAMS_UPDATED
		    | XDMAC_CNDC_NDSUP_SRC_PARAMS_UPDATED
		    | XDMAC_CNDC_NDE_DSCR_FETCH_EN, set->dma_dlist);
	}

	rc = xdmad_start_transfer(set->dma_ch);
	if (rc == XDMAD_OK) {
		while (!xdmad_is_transfer_done(set->dma_ch))
			xdmad_poll();
		xdmad_stop_transfer(set->dma_ch);
	}
	else
		trace_error("Couldn't start xDMA transfer\n\r");
	set->dlist_len = 0;
}

/**
 * \brief Send data blocks to the SHA peripheral.
 * Synchronous if the DMA is not used.
 * Or asynchronous if the DMA is enabled; in this case the contents of the
 * accompanying data buffer shall be preserved until run_dma_xfer() is called
 * and returns. May be called several times in order to complete the list of
 * transfer descriptors, before running run_dma_xfer() just once.
 */
static void write_blocks(struct sha_set *set, const uint32_t *data,
    uint32_t blocks)
{
	struct _xdmad_desc_view1 *desc = NULL;
	const uint32_t ubl_len_max = min_u32(XDMAC_CUBC_UBLEN_Msk
	    >> XDMAC_CUBC_UBLEN_Pos, XDMA_UBC_UBLEN_Msk >> XDMA_UBC_UBLEN_Pos);
	uint32_t ix, limited;

	assert(set);
	assert(data);
	assert(blocks);

	if (set->count == 0) {
		while (busy) ;
		sha_first_block();
	}
	if (set->dma_ch)
		/* Enqueue one (additional) descriptor, no more, no less */
		for (ix = 0; ix < blocks; ) {
			assert(set->dlist_len <= 1);
			limited = min_u32(blocks - ix, ubl_len_max / 16ul);
			desc = set->dma_dlist + set->dlist_len;
			/* Configure data count per microblock */
			desc->ublock_size = limited * 16ul;
			desc->src_addr = (void*)(data + ix * 16ul);
			/* The other parameters in the descriptor will be
			 * configured by run_dma_xfer() */
			set->dlist_len++;
			ix += limited;
			set->count += limited * 64ul;
			if (ix < blocks)
				run_dma_xfer(set);
		}
	else
		for (ix = 0; ix < blocks; ix++, set->count += 64) {
			while (busy) ;
			busy = true;
			/* It looks like the DATRDY interrupt triggers on
			 * ISR.DATRDY flag's level (vs its rising edge), and
			 * once a block has been processed, ISR.DATRDY is set.
			 */
			sha_set_input(data + ix * 16ul, 16);
			/* Setting CR.START has cleared ISR.DATRDY, hence we can
			 * now enable the DATRDY interrupt. */
			sha_enable_it(SHA_IER_DATRDY);
		}
}

/**
 * \brief SHA interrupt handler.
 */
static void handle_sha_irq(void)
{
	if ((sha_get_status() & SHA_ISR_DATRDY) == SHA_ISR_DATRDY) {
		sha_disable_it(SHA_IER_DATRDY);
		busy = false;
	}
}

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

void sha_plugin_initialize(struct sha_set *set, bool use_dma)
{
	assert(set);
	assert(!((uint32_t)&set->pending_data & 0x3));

	memset(set, 0, sizeof(*set));
	if (use_dma) {
		/* Initialize xDMA driver instance with polling mode */
		xdmad_initialize(true);
		/* Allocate a xDMA channel, Write accesses into SHA_IDATARx */
		set->dma_ch = xdmad_allocate_channel(XDMAD_PERIPH_MEMORY,
		    ID_SHA);
		if (!set->dma_ch)
			trace_error("Couldn't allocate xDMA channel\n\r");
		else
			xdmad_prepare_channel(set->dma_ch);
	}
	/* Enable peripheral clock */
	pmc_enable_peripheral(ID_SHA);
	/* Perform a software-triggered hardware reset of the SHA interface */
	sha_soft_reset();
	busy = false;
	aic_set_source_vector(ID_SHA, handle_sha_irq);
	aic_enable(ID_SHA);
	sha_configure(SHA_MR_ALGO_SHA1 | SHA_MR_PROCDLY_SHORTEST
	    | (set->dma_ch ? SHA_MR_SMOD_IDATAR0_START
	    : SHA_MR_SMOD_AUTO_START));
}

void sha_plugin_feed(struct sha_set *set, bool open, bool close,
    const uint8_t *data, uint32_t count)
{
	uint32_t chunk;
	bool pending_async = false;

	assert(set);
	assert(data);

	if (open) {
		set->count = 0;
		set->pending = 0;
		set->dlist_len = 0;
	}
	else if (set->pending && count) {
		if (set->pending + count > 64ul)
			chunk = 64 - set->pending;
		else
			chunk = count;
		memcpy(set->pending_data + set->pending, data, chunk);
		set->pending += (uint8_t)chunk;
		data += chunk;
		count -= chunk;
		if (set->pending == 64) {
			if (set->dma_ch)
				/* Ensure the outgoing data can be fetched
				 * directly from RAM */
				l2cc_clean_region((uint32_t)set->pending_data,
				    (uint32_t)set->pending_data + 64ul);
			write_blocks(set, (const uint32_t*)set->pending_data, 1);
			pending_async = set->dma_ch != NULL;
			set->pending = 0;
		}
	}
	if (count >= 64ul) {
		/* Warning, if the user buffer was not word-aligned, we would
		 * have to memcpy data to an aligned local buffer */
		assert(!((uint32_t)data & 0x3));
		chunk = count / 64ul;
		write_blocks(set, (const uint32_t*)data, chunk);
		chunk *= 64ul;
		data += chunk;
		count -= chunk;
	}
	if (count) {
		assert(set->pending == 0);
		assert(count < 64ul);
		if (pending_async) {
			run_dma_xfer(set);
			pending_async = false;
		}
		memcpy(set->pending_data, data, count);
		set->pending = (uint8_t)count;
	}
	if (close) {
		if (pending_async) {
			run_dma_xfer(set);
		}
		chunk = pad_message(set->pending_data + set->pending, set->count
		    + set->pending);
		chunk += set->pending;
		assert(chunk == 64 || chunk == 128);
		set->pending = 0;
		if (set->dma_ch)
			l2cc_clean_region((uint32_t)set->pending_data,
			    (uint32_t)set->pending_data + chunk);
		write_blocks(set, (const uint32_t*)set->pending_data,
		    chunk / 64);
	}
	if (set->dlist_len)
		run_dma_xfer(set);
}

void sha_plugin_get_hash(struct sha_set *set, uint32_t hash[5])
{
	uint32_t val;
	uint8_t ix;

	assert(set);
	assert(hash);
	assert(set->pending == 0);

	while (busy) ;
	sha_get_output(hash);
#ifndef NDEBUG
	val = SHA->SHA_ISR;
	if (val & SHA_ISR_DATRDY || val & SHA_ISR_URAD)
		trace_error("Error status 0x%08lx\n\r", val);
#endif
	/* Convert from little-endian memory to standard FIPS i.e. big-endian
	 * representation */
	for (ix = 0; ix < 5; ix++) {
		val = hash[ix];
		val = (val << 8 & 0xff00ff00) | (val >> 8 & 0x00ff00ff);
		hash[ix] = val << 16 | val >> 16;
	}
}
