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


#include "irq/irq.h"
#include "peripherals/pmc.h"
#include "crypto/tdes.h"
#include "crypto/tdesd.h"
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

static void _tdesd_dma_callback(struct dma_channel *channel, void *arg)
{
	struct _tdesd_desc* desc = (struct _tdesd_desc*)arg;
	/* For read, invalidate region */
	if (channel == desc->xfer.dma.rx.channel) {
		cache_invalidate_region((uint32_t*)desc->xfer.bufout->data,
								desc->xfer.bufout->size);
		mutex_unlock(&desc->mutex);
	}
}

/* Operation Mode Chunk Size Destination/Source Data Transfer Type
	ECB 			1 			Word
	CBC 			1 			Word
	OFB 			1 			Word
	CFB 64-bit 		1 			Word
	CFB 32-bit 		1 			Word
	CFB 16-bit 		1 			Half-word
	CFB 8-bit 		1 			Byte
*/
static uint8_t _tdesd_get_dma_data_width(struct _tdesd_desc* desc)
{
	uint8_t width = DMA_DATA_WIDTH_WORD;

	if ((desc->cfg.mode == TDESD_MODE_CFB)) {
		if (desc->cfg.cfbs == TDESD_CFBS_16)
			width = DMA_DATA_WIDTH_HALF_WORD;
		if (desc->cfg.cfbs == TDESD_CFBS_8)
			width = DMA_DATA_WIDTH_BYTE;
	}
	return width;
}

static void _tdesd_transfer_buffer_dma(struct _tdesd_desc* desc)
{
	struct dma_xfer_item* ll;
	struct dma_xfer_item_tmpl cfg;
	uint32_t i;
	uint32_t remains, offset;
	uint32_t width_in_byte;
	uint32_t blk_size;

	cache_clean_region((uint32_t*)desc->xfer.bufin->data,
						desc->xfer.bufin->size);

	/* Allocate one DMA channel for writing message blocks to AES_IDATARx */
	desc->xfer.dma.tx.channel = dma_allocate_channel(DMA_PERIPH_MEMORY, ID_TDES);
	assert(desc->xfer.dma.tx.channel);

	remains = desc->xfer.bufin->size;
	width_in_byte = DMA_DATA_WIDTH_IN_BYTE(_tdesd_get_dma_data_width(desc));
	offset = 0;

	for (i = 0; ; i++) {
		ll = dma_allocate_item(desc->xfer.dma.tx.channel);
		blk_size = (remains / width_in_byte) <= DMA_MAX_BLOCK_LEN
					? (remains / width_in_byte) : DMA_MAX_BLOCK_LEN;
		cfg.sa = (void *)((desc->xfer.bufin->data) + offset);
		cfg.da = (void*)TDES->TDES_IDATAR;
		cfg.upd_sa_per_data = 1;
		cfg.upd_da_per_data = 0;
		cfg.upd_sa_per_blk  = 1;
		cfg.upd_da_per_blk  = 0;
		/* The data size depends on the mode of operation, and is listed
		in Datasheet Table 50-4.*/
		cfg.data_width = _tdesd_get_dma_data_width(desc);
		cfg.chunk_size = DMA_CHUNK_SIZE_1;
		cfg.blk_size = blk_size;
		offset += blk_size * width_in_byte;
		remains -= blk_size * width_in_byte;
		dma_prepare_item(desc->xfer.dma.tx.channel, &cfg, ll);
		dma_link_last_item(desc->xfer.dma.tx.channel, ll);
		if (!remains)
			break;
	}
	dma_link_item(desc->xfer.dma.tx.channel, ll, NULL);
	dma_configure_sg_transfer(desc->xfer.dma.tx.channel, &cfg, NULL);
	dma_set_callback(desc->xfer.dma.tx.channel, _tdesd_dma_callback, (void*)desc);

	/* Allocate one DMA channel for obtaining the result from AES_ODATARx.*/
	desc->xfer.dma.rx.channel = dma_allocate_channel(ID_TDES, DMA_PERIPH_MEMORY);
	assert(desc->xfer.dma.rx.channel);

	remains = desc->xfer.bufout->size;
	offset = 0;

	for (i = 0; ; i++) {
		ll = dma_allocate_item(desc->xfer.dma.rx.channel);
		blk_size = (remains / width_in_byte) <= DMA_MAX_BLOCK_LEN
					? (remains / width_in_byte) : DMA_MAX_BLOCK_LEN;
		cfg.sa = (void*)TDES->TDES_ODATAR;
		cfg.da = (void *)((desc->xfer.bufout->data) + offset);
		cfg.upd_sa_per_data = 0;
		cfg.upd_da_per_data = 1;
		cfg.upd_sa_per_blk  = 0;
		cfg.upd_da_per_blk  = 1;
		/* The data size depends on the mode of operation, and is listed in
		Datasheet Table 50-4.*/
		cfg.data_width = _tdesd_get_dma_data_width(desc);
		cfg.chunk_size = DMA_CHUNK_SIZE_1;
		cfg.blk_size = blk_size;
		offset += blk_size * width_in_byte;
		remains -= blk_size * width_in_byte;
		dma_prepare_item(desc->xfer.dma.rx.channel, &cfg, ll);
		dma_link_last_item(desc->xfer.dma.rx.channel, ll);
		if (!remains)
			break;
	}
	dma_link_item(desc->xfer.dma.rx.channel, ll, NULL);
	dma_configure_sg_transfer(desc->xfer.dma.rx.channel, &cfg, NULL);

	dma_set_callback(desc->xfer.dma.rx.channel, _tdesd_dma_callback, (void*)desc);
	dma_start_transfer(desc->xfer.dma.tx.channel);
	dma_start_transfer(desc->xfer.dma.rx.channel);

	tdesd_wait_transfer(desc);
	dma_free_channel(desc->xfer.dma.tx.channel);
	dma_free_channel(desc->xfer.dma.rx.channel);
	if (desc->xfer.callback)
		desc->xfer.callback(desc->xfer.cb_args);
}

static void _tdesd_handler(uint32_t source, void* user_arg)
{
	assert(source == ID_TDES);
	if ((tdes_get_status() & TDES_ISR_DATRDY) == TDES_ISR_DATRDY) {
		tdes_disable_it(TDES_IER_DATRDY);
		single_transfer_ready = true;
	}
}

static void _tdesd_transfer_buffer_polling(struct _tdesd_desc* desc)
{
	uint32_t i;
	uint8_t size = 8;

	if (desc->cfg.mode == TDESD_MODE_CFB) {
		if (desc->cfg.cfbs == TDESD_CFBS_32)
			size = 4;
		else if (desc->cfg.cfbs == TDESD_CFBS_16)
			size = 2;
		else if (desc->cfg.cfbs == TDESD_CFBS_8)
			size = 1;
	}

	/* Iterate per 64-bit data block */
	for (i = 0; i < desc->xfer.bufin->size; i+= size) {
		single_transfer_ready = false;
		tdes_enable_it(TDES_IER_DATRDY);
		/* Write one 64/32-bit input data block to the authorized
		Input Data Registers */
		if (size == 8)
			tdes_set_input((uint32_t *)((desc->xfer.bufin->data) + i),
							(uint32_t *)((desc->xfer.bufin->data) + i + 4));
		else
			tdes_set_input((uint32_t *)((desc->xfer.bufin->data) + i), NULL);

		if (desc->cfg.transfer_mode == TDES_MR_SMOD_MANUAL_START)
			/* Set the START bit in the TDES Control
			 * register to begin the encryption or
			 * decryption process. */
			tdes_start();

		while(!single_transfer_ready);

		if (size == 8)
			tdes_get_output((uint32_t *)((desc->xfer.bufout->data) + i),
							(uint32_t *)((desc->xfer.bufout->data) + i + 4));
		else
			tdes_get_output((uint32_t *)((desc->xfer.bufout->data) + i), NULL);
	}
	if (desc->xfer.callback)
			desc->xfer.callback(desc->xfer.cb_args);
	mutex_unlock(&desc->mutex);
}

static void _tdesd_transfer_buffer(struct _tdesd_desc* desc)
{
	switch (desc->cfg.transfer_mode) {
	case TDESD_TRANS_POLLING_MANUAL:
	case TDESD_TRANS_POLLING_AUTO:
		_tdesd_transfer_buffer_polling(desc);
		break;

	case TDESD_TRANS_DMA:
		_tdesd_transfer_buffer_dma(desc);
		break;

	default:
		trace_fatal("Unknown AES transfer mode\r\n");
	}
}

/*----------------------------------------------------------------------------
 *        Public functions
 *----------------------------------------------------------------------------*/
uint32_t tdesd_transfer(struct _tdesd_desc* desc, struct _buffer* buffer_in,
	struct _buffer* buffer_out, tdesd_callback_t cb, void* user_args)
{
	desc->xfer.bufin = buffer_in;
	desc->xfer.bufout = buffer_out;
	desc->xfer.callback = cb;
	desc->xfer.cb_args = user_args;

	assert(!(desc->xfer.bufin->size % (1 << _tdesd_get_dma_data_width(desc))));
	assert(!(desc->xfer.bufout->size % (1 << _tdesd_get_dma_data_width(desc))));

	if (!mutex_try_lock(&desc->mutex)) {
		trace_error("AESD mutex already locked!\r\n");
		return ADES_ERROR_LOCK;
	}
	_tdesd_transfer_buffer(desc);

	return TDESD_SUCCESS;
}

bool tdesd_is_busy(struct _tdesd_desc* desc)
{
	return mutex_is_locked(&desc->mutex);
}

void tdesd_wait_transfer(struct _tdesd_desc* desc)
{
	while (tdesd_is_busy(desc)) {
		if (desc->cfg.transfer_mode == TDESD_TRANS_DMA)
			dma_poll();
	}
}

void tdesd_init(void)
{
	/* Enable peripheral clock */
	pmc_configure_peripheral(ID_TDES, NULL, true);
	/* Enable peripheral interrupt */
	irq_add_handler(ID_TDES, _tdesd_handler, NULL);
	irq_enable(ID_TDES);
}

void tdesd_configure_mode(struct _tdesd_desc* desc)
{
	/* Perform a software-triggered hardware reset of the TDES interface */
	tdes_soft_reset();

	tdes_configure((desc->cfg.encrypt ?
					TDES_MR_CIPHER_ENCRYPT : TDES_MR_CIPHER_DECRYPT)
					| desc->cfg.algo << TDES_MR_TDESMOD_Pos
					| desc->cfg.transfer_mode << TDES_MR_SMOD_Pos
					| desc->cfg.key_mode << 4
					| desc->cfg.mode << TDES_MR_OPMOD_Pos
					| desc->cfg.cfbs << TDES_MR_CFBS_Pos
					);
	/* Write the 64-bit key(s) in the different Key Word Registers,
	 * depending on whether one, two or three keys are required. */
	tdes_write_key1(desc->cfg.key[0], desc->cfg.key[1]);
	tdes_write_key2(desc->cfg.key[2], desc->cfg.key[3]);
	if (desc->cfg.key_mode == TDESD_KEY_THREE)
		tdes_write_key3(desc->cfg.key[4], desc->cfg.key[5]);
	else
		tdes_write_key3(0, 0);
	/* The Initialization Vector Registers apply to all modes except ECB. */
	if (desc->cfg.mode != TDESD_MODE_ECB)
		tdes_set_vector(desc->cfg.vector[0], desc->cfg.vector[1]);
	if (desc->cfg.algo == TDESD_ALGO_XTEA)
		tdes_set_xtea_rounds(32);
}
