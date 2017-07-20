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

#include <stddef.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "callback.h"
#include "crypto/tdes.h"
#include "crypto/tdesd.h"
#include "dma/dma.h"
#include "irq/irq.h"
#include "mm/cache.h"
#include "peripherals/pmc.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static int _tdesd_dma_rx_callback(void* arg, void* arg2)
{
	struct _tdesd_desc* desc = (struct _tdesd_desc*)arg;

	/* To read, invalidate region */
	dma_reset_channel(desc->xfer.dma.tx.channel);
	dma_reset_channel(desc->xfer.dma.rx.channel);
	cache_invalidate_region((uint32_t*)desc->xfer.bufout->data,
				desc->xfer.bufout->size);
	mutex_unlock(&desc->mutex);

	return callback_call(&desc->xfer.callback, NULL);
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
	struct _dma_transfer_cfg cfg;
	struct _dma_cfg cfg_dma;
	struct _callback _cb;

	cache_clean_region((uint32_t*)desc->xfer.bufin->data, desc->xfer.bufin->size);

	memset(&cfg_dma, 0, sizeof(cfg_dma));
	cfg_dma.incr_saddr = true;
	cfg_dma.incr_daddr = false;
	cfg_dma.data_width = _tdesd_get_dma_data_width(desc);
	cfg_dma.chunk_size = DMA_CHUNK_SIZE_1;

	memset(&cfg, 0, sizeof(cfg));
	cfg.saddr = (void*)desc->xfer.bufin->data;
	cfg.daddr = (void*)TDES->TDES_IDATAR;
	cfg.len = desc->xfer.bufin->size / DMA_DATA_WIDTH_IN_BYTE(cfg_dma.data_width);
	dma_configure_transfer(desc->xfer.dma.tx.channel, &cfg_dma, &cfg, 1);

	memset(&cfg, 0, sizeof(cfg));
	cfg_dma.incr_saddr = false;
	cfg_dma.incr_daddr = true;

	cfg.saddr = (void*)TDES->TDES_ODATAR;
	cfg.daddr = (void*)desc->xfer.bufout->data;
	cfg.len = desc->xfer.bufout->size / DMA_DATA_WIDTH_IN_BYTE(cfg_dma.data_width);
	dma_configure_transfer(desc->xfer.dma.rx.channel, &cfg_dma, &cfg, 1);

	dma_set_callback(desc->xfer.dma.tx.channel, NULL);
	callback_set(&_cb, _tdesd_dma_rx_callback, (void*)desc);
	dma_set_callback(desc->xfer.dma.rx.channel, &_cb);

	dma_start_transfer(desc->xfer.dma.tx.channel);
	dma_start_transfer(desc->xfer.dma.rx.channel);

	tdesd_wait_transfer(desc);
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

		while ((tdes_get_status() & TDES_ISR_DATRDY) != TDES_ISR_DATRDY);

		if (size == 8)
			tdes_get_output((uint32_t *)((desc->xfer.bufout->data) + i),
							(uint32_t *)((desc->xfer.bufout->data) + i + 4));
		else
			tdes_get_output((uint32_t *)((desc->xfer.bufout->data) + i), NULL);
	}
	mutex_unlock(&desc->mutex);
	callback_call(&desc->xfer.callback, NULL);
}

/*----------------------------------------------------------------------------
 *        Public functions
 *----------------------------------------------------------------------------*/

uint32_t tdesd_transfer(struct _tdesd_desc* desc, struct _buffer* buffer_in,
			struct _buffer* buffer_out, struct _callback* cb)
{
	desc->xfer.bufin = buffer_in;
	desc->xfer.bufout = buffer_out;
	callback_copy(&desc->xfer.callback, cb);

	assert(!(desc->xfer.bufin->size % (1 << _tdesd_get_dma_data_width(desc))));
	assert(!(desc->xfer.bufout->size % (1 << _tdesd_get_dma_data_width(desc))));

	if (!mutex_try_lock(&desc->mutex)) {
		trace_error("AESD mutex already locked!\r\n");
		return ADES_ERROR_LOCK;
	}

	switch (desc->cfg.transfer_mode) {
	case TDESD_TRANS_POLLING_MANUAL:
	case TDESD_TRANS_POLLING_AUTO:
		_tdesd_transfer_buffer_polling(desc);
		break;

	case TDESD_TRANS_DMA:
		_tdesd_transfer_buffer_dma(desc);
		break;

	default:
		mutex_unlock(&desc->mutex);
		trace_fatal("Unknown AES transfer mode\r\n");
	}

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

void tdesd_init(struct _tdesd_desc* desc)
{
	/* Enable peripheral clock */
	pmc_configure_peripheral(ID_TDES, NULL, true);

	/* Allocate one DMA channel for writing message blocks to TDESx`_IDATAR */
	desc->xfer.dma.tx.channel = dma_allocate_channel(DMA_PERIPH_MEMORY, ID_TDES);
	assert(desc->xfer.dma.tx.channel);

	/* Allocate one DMA channel for obtaining the result from TAESx_ODATARx.*/
	desc->xfer.dma.rx.channel = dma_allocate_channel(ID_TDES, DMA_PERIPH_MEMORY);
	assert(desc->xfer.dma.rx.channel);
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
