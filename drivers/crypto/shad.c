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

#include "peripherals/irq.h"
#include "peripherals/pmc.h"
#include "crypto/shad.h"
#include "crypto/sha.h"
#include "dma/dma.h"
#include "misc/cache.h"

#include "trace.h"

#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

volatile static bool single_transfer_ready;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static void _shad_dma_callback(struct dma_channel *channel, void *arg)
{
	struct _shad_desc* desc = (struct _shad_desc*)arg;

	mutex_unlock(&desc->mutex);
}

/**
 * \brief SHA interrupt handler.
 */
static void _shad_handler(uint32_t source, void* user_arg)
{
	assert(source == ID_SHA);

	if ((sha_get_status() & SHA_ISR_DATRDY) == SHA_ISR_DATRDY) {
		sha_disable_it(SHA_IER_DATRDY);
		single_transfer_ready = true;
	}
}

static void _shad_transfer_buffer_dma(struct _shad_desc* desc)
{
	struct dma_xfer_item* ll;
	struct dma_xfer_item_tmpl cfg;
	uint32_t remains;
	uint32_t offset = 0;
	uint32_t blk_size;

	cache_clean_region((uint32_t*)desc->xfer.bufin->data,
						desc->xfer.bufin->size);

	/* Allocate one DMA channel for writing message blocks to SHA_IDATARx */
	desc->xfer.dma.tx.channel = dma_allocate_channel(DMA_PERIPH_MEMORY, ID_SHA);
	assert(desc->xfer.dma.tx.channel);
	
	/* For the first block of a message, the FIRST command must be set by
	 * setting the corresponding bit of the Control Register (SHA_CR). For
	 * the other blocks, there is nothing to write in this Control Register. */
	sha_first_block();
	remains = desc->xfer.bufin->size;
	for (;;) {
		ll = dma_allocate_item(desc->xfer.dma.tx.channel);

		blk_size = (remains / 4) <= ROUND_UP_MULT(DMA_MAX_BLOCK_LEN - 32, 32)
					? (remains / 4) : ROUND_UP_MULT(DMA_MAX_BLOCK_LEN - 32, 32);
		cfg.sa = (void *)((desc->xfer.bufin->data) + offset);
		cfg.da = (void*)&SHA->SHA_IDATAR[0];
		cfg.upd_sa_per_data = 1;
		cfg.upd_da_per_data = 0;
		cfg.upd_sa_per_blk  = 1;
		cfg.upd_da_per_blk  = 0;
		cfg.data_width = DMA_DATA_WIDTH_WORD;
		cfg.chunk_size = sha_get_dma_chunk_size((uint8_t)desc->cfg.mode);
		cfg.blk_size = blk_size;
		offset += blk_size * 4;
		remains -= blk_size * 4;
		dma_prepare_item(desc->xfer.dma.tx.channel, &cfg, ll);
		dma_link_last_item(desc->xfer.dma.tx.channel, ll);
		if (!remains)
			break;
	}

	dma_link_item(desc->xfer.dma.tx.channel, ll, NULL);
	dma_configure_sg_transfer(desc->xfer.dma.tx.channel, &cfg, NULL);
	dma_set_callback(desc->xfer.dma.tx.channel, _shad_dma_callback, (void*)desc);

	dma_start_transfer(desc->xfer.dma.tx.channel);
	shad_wait_transfer(desc);
	dma_free_channel(desc->xfer.dma.tx.channel);

	sha_get_output((uint32_t*)desc->xfer.bufout->data);
	if (desc->xfer.callback)
		desc->xfer.callback(desc->xfer.cb_args);
}

static void _shad_transfer_buffer_polling(struct _shad_desc* desc)
{
	uint32_t i;
	uint32_t l;
	uint32_t* p;
	uint32_t blk_cnt;

	if (desc->cfg.mode == SHAD_MODE_SHA1
	    || desc->cfg.mode == SHAD_MODE_SHA256
	    || desc->cfg.mode == SHAD_MODE_SHA224) {
		l = 16;
		blk_cnt = desc->xfer.bufin->size / 64;
	} else {
		l = 32;
		blk_cnt = desc->xfer.bufin->size / 128;
	}

	/* For the first block of a message, the FIRST command must be set by
	 * setting the corresponding bit of the Control Register (SHA_CR). For
	 * the other blocks, there is nothing to write in this Control Register. */
	sha_first_block();

	for (p = (uint32_t*)desc->xfer.bufin->data, i = 0; i < blk_cnt; i++, p+= l) {
		single_transfer_ready = false;
		/* Write the block to be processed in the Input Data Registers */
		sha_set_input(p, l);
		if (desc->cfg.transfer_mode == SHAD_TRANS_POLLING_MANUAL) {
			/* Set the START bit in the SHA Control Register SHA_CR to begin the processing. */
			sha_start();
		}
		/* Set the bit DATRDY (Data Ready) in the SHA Interrupt Enable Register (SHA_IER) */
		sha_enable_it(SHA_IER_DATRDY);
		/* When the processing completes, the bit DATRDY in the
		 * SHA Interrupt Status Register (SHA_ISR) raises. If an
		 * interrupt has been enabled by setting the bit DATRDY
		 * in SHA_IER, the interrupt line of the SHA is activated. */
		while (!single_transfer_ready);
		/* Repeat the write procedure for each block, start
		 * procedure and wait for the interrupt procedure up to
		 * the last block of the entire message. Each time the
		 * start procedure is complete, the DATRDY flag is cleared. */
	}

	sha_get_output((uint32_t*)desc->xfer.bufout->data);

	if (desc->xfer.callback)
		desc->xfer.callback(desc->xfer.cb_args);
	mutex_unlock(&desc->mutex);
}

static void _shad_transfer_buffer(struct _shad_desc* desc)
{
	switch (desc->cfg.transfer_mode) {
	case SHAD_TRANS_POLLING_MANUAL:
	case SHAD_TRANS_POLLING_AUTO:
		_shad_transfer_buffer_polling(desc);
		break;

	case SHAD_TRANS_DMA:
		_shad_transfer_buffer_dma(desc);
		break;

	default:
		trace_fatal("Unknown SHA transfer mode\r\n");
	}
}

/*----------------------------------------------------------------------------
 *        Public functions

 *----------------------------------------------------------------------------*/
uint32_t shad_transfer(struct _shad_desc* desc, struct _buffer* buffer_in,
	struct _buffer* buffer_out, shad_callback_t cb, void* user_args)
{

	sha_soft_reset();
	sha_configure(desc->cfg.mode << SHA_MR_ALGO_Pos
		      | desc->cfg.transfer_mode << SHA_MR_SMOD_Pos
		      | SHA_MR_PROCDLY_LONGEST);

	desc->xfer.bufin = buffer_in;
	desc->xfer.bufout = buffer_out;
	desc->xfer.callback = cb;
	desc->xfer.cb_args = user_args;

	if (!mutex_try_lock(&desc->mutex)) {
		trace_error("SHAD mutex already locked!\r\n");
		return SHAD_ERROR_LOCK;
	}
	_shad_transfer_buffer(desc);

	return SHAD_SUCCESS;
}

bool shad_is_busy(struct _shad_desc* desc)
{
	return mutex_is_locked(&desc->mutex);
}

void shad_wait_transfer(struct _shad_desc* desc)
{
	while (shad_is_busy(desc)) {
		if (desc->cfg.transfer_mode == SHAD_TRANS_DMA)
			dma_poll();
	}
}

void shad_init(void)
{
	/* Enable peripheral clock */
	pmc_enable_peripheral(ID_SHA);
	/* Enable peripheral interrupt */
	irq_add_handler(ID_SHA, _shad_handler, NULL);
	irq_enable(ID_SHA);
}

/**
 * \brief According to the standard, the message must be padded to an even
 * 512 bits.  The first padding bit must be a '1'.  The last 64 bits represent
 * the length of the original message.  All bits in between should be 0.
 * \param message The context to pad
 * \param l length of message in byte
 * \param mode SHA mode
 * \note: the size of massage is limit to 32 bytes.
*/
uint32_t shad_pad_message(uint8_t *message, uint32_t len, uint8_t mode)
{
	uint32_t k;
	uint32_t l = len * 8;
	uint8_t *p = (uint8_t *)message;
	uint32_t sl = 0;

	switch (mode) {
	case SHAD_MODE_SHA1:
	case SHAD_MODE_SHA256:
	case SHAD_MODE_SHA224:
		k = (512 + 448 - ((l % 512) + 1)) % 512;
		break;
	case SHAD_MODE_SHA384:
	case SHAD_MODE_SHA512:
		k = (1024 + 896 - ((l % 1024) + 1)) % 1024;
		break;
	default:
		k = 7;
	}

	/* Append the bit “1” to the end of the message */
	p += len;
	sl += len;
	*p++ = 0x80;
	sl ++;

	/* Followed by k zero bits */
	memset(p, 0, (k - 7) / 8);
	p += (k - 7) / 8;
	sl += (k - 7) / 8;

	if (mode == SHAD_MODE_SHA384 || mode == SHAD_MODE_SHA512) {
		memset(p, 0, 8);
		p += 8;
		sl += 8;
	}
	/* Then append the 64-bit block length */
	memset(p, 0, 4);
	p += 4;
	*p++ = l >> 24 & 0xff;
	*p++ = l >> 16 & 0xff;
	*p++ = l >> 8 & 0xff;
	*p++ = l & 0xff;
	sl += 8;
	return sl;
}
