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

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "callback.h"
#include "crypto/aes.h"
#include "crypto/aesd.h"
#include "dma/dma.h"
#include "irq/irq.h"
#include "mm/cache.h"
#include "peripherals/pmc.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static int _aesd_dma_read_callback(void* arg, void* arg2)
{
	struct _aesd_desc* desc = (struct _aesd_desc*)arg;

	dma_reset_channel(desc->xfer.dma.tx.channel);

	cache_invalidate_region((uint32_t*)desc->xfer.bufout->data, desc->xfer.bufout->size);

	mutex_unlock(&desc->mutex);

	return callback_call(&desc->xfer.callback, NULL);
}

/* Operation Mode Chunk Size Data Transfer Type
	ECB           4          Word
	CBC           4          Word
	OFB           4          Word
	CFB 128-bit   4          Word
	CFB 64-bit    1          Word
	CFB 32-bit    1          Word
	CFB 16-bit    1          Half-word
	CFB 8-bit     1          Byte
	CTR           4          Word
	GCM           4          Word
*/
static uint8_t _aesd_get_dma_chunk_size(struct _aesd_desc* desc)
{
	if ((desc->cfg.mode == AESD_MODE_CFB) && (desc->cfg.cfbs != AESD_CFBS_128))
		return DMA_CHUNK_SIZE_1;
	else
		return DMA_CHUNK_SIZE_4;
}

static uint8_t _aesd_get_dma_data_width(struct _aesd_desc* desc)
{
	uint8_t width = DMA_DATA_WIDTH_WORD;

	if ((desc->cfg.mode == AESD_MODE_CFB)) {
		if (desc->cfg.cfbs == AESD_CFBS_16)
			width = DMA_DATA_WIDTH_HALF_WORD;
		if (desc->cfg.cfbs == AESD_CFBS_8)
			width = DMA_DATA_WIDTH_BYTE;
	}
	return width;
}

static uint8_t _aesd_get_size_per_trans(struct _aesd_desc* desc)
{
	uint8_t size = 16;

	if ((desc->cfg.mode == AESD_MODE_CFB)) {
		switch (desc->cfg.cfbs){
			case AESD_CFBS_128:
				size = 16;
				break;
			case AESD_CFBS_64:
				size = 8;
				break;
			case AESD_CFBS_32:
				size = 4;
				break;
			case AESD_CFBS_16:
				size = 2;
				break;
			case AESD_CFBS_8:
				size = 1;
				break;
		}
	}
	return size;
}

static void _aesd_transfer_buffer_dma(struct _aesd_desc* desc)
{
	struct _dma_transfer_cfg cfg;
	struct _dma_cfg cfg_dma;
	struct _callback _cb;

	cache_clean_region((uint32_t*)desc->xfer.bufin->data, desc->xfer.bufin->size);

	memset(&cfg_dma, 0, sizeof(cfg_dma));
	cfg_dma.incr_saddr = true;
	cfg_dma.incr_daddr = false;
	cfg_dma.data_width = _aesd_get_dma_data_width(desc);
	cfg_dma.chunk_size = _aesd_get_dma_chunk_size(desc);

	memset(&cfg, 0, sizeof(cfg));
	cfg.saddr = (void *)desc->xfer.bufin->data;
	cfg.daddr = (void *)AES->AES_IDATAR;
	cfg.len = desc->xfer.bufin->size / DMA_DATA_WIDTH_IN_BYTE(cfg_dma.data_width);
	dma_configure_transfer(desc->xfer.dma.tx.channel, &cfg_dma, &cfg, 1);
	dma_set_callback(desc->xfer.dma.tx.channel, NULL);

	dma_reset_channel(desc->xfer.dma.rx.channel);
	cfg_dma.incr_saddr = false;
	cfg_dma.incr_daddr = true;

	memset(&cfg, 0, sizeof(cfg));
	cfg.saddr = (void *)AES->AES_ODATAR;
	cfg.daddr = (void *)desc->xfer.bufout->data;
	cfg.len = desc->xfer.bufout->size / DMA_DATA_WIDTH_IN_BYTE(cfg_dma.data_width);
	dma_configure_transfer(desc->xfer.dma.rx.channel, &cfg_dma, &cfg, 1);

	callback_set(&_cb, _aesd_dma_read_callback, (void*)desc);
	dma_set_callback(desc->xfer.dma.rx.channel, &_cb);

	dma_start_transfer(desc->xfer.dma.tx.channel);
	dma_start_transfer(desc->xfer.dma.rx.channel);

	aesd_wait_transfer(desc);
}

static void _aesd_transfer_buffer_polling(struct _aesd_desc* desc)
{
	uint32_t i;

	aes_enable_it(AES_IER_DATRDY);
	for (i = 0; i < desc->xfer.bufin->size; i+= _aesd_get_size_per_trans(desc)) {
		aes_set_input((uint32_t *)((desc->xfer.bufin->data) + i));
		if (desc->cfg.transfer_mode == AESD_TRANS_POLLING_MANUAL)
			/* Set the START bit in the AES Control register
			 to begin the encrypt. or decrypt. process. */
			aes_start();
		while ((aes_get_status() & AES_ISR_DATRDY) != AES_ISR_DATRDY);
		aes_get_output((uint32_t *)((desc->xfer.bufout->data) + i));
	}
	mutex_unlock(&desc->mutex);

	callback_call(&desc->xfer.callback, NULL);
}

/*----------------------------------------------------------------------------
 *        Public functions

 *----------------------------------------------------------------------------*/
uint32_t aesd_transfer(struct _aesd_desc* desc, struct _buffer* buffer_in,
	struct _buffer* buffer_out, struct _callback* cb)
{
	aes_encrypt_enable(desc->cfg.encrypt);
	aes_set_start_mode(desc->cfg.transfer_mode);
	desc->xfer.bufin = buffer_in;
	desc->xfer.bufout = buffer_out;
	callback_copy(&desc->xfer.callback, cb);

	assert(!(desc->xfer.bufin->size % _aesd_get_size_per_trans(desc)));
	assert(!(desc->xfer.bufout->size % _aesd_get_size_per_trans(desc)));

	if (!mutex_try_lock(&desc->mutex)) {
		trace_error("AESD mutex already locked!\r\n");
		return ADES_ERROR_LOCK;
	}

	switch (desc->cfg.transfer_mode) {
	case AESD_TRANS_POLLING_MANUAL:
	case AESD_TRANS_POLLING_AUTO:
		_aesd_transfer_buffer_polling(desc);
		break;

	case AESD_TRANS_DMA:
		_aesd_transfer_buffer_dma(desc);
		break;

	default:
		mutex_unlock(&desc->mutex);
		trace_fatal("Unknown AES transfer mode\r\n");
	}

	return AESD_SUCCESS;
}

bool aesd_is_busy(struct _aesd_desc* desc)
{
	return mutex_is_locked(&desc->mutex);
}

void aesd_wait_transfer(struct _aesd_desc* desc)
{
	while (aesd_is_busy(desc)) {
		if (desc->cfg.transfer_mode == AESD_TRANS_DMA)
			dma_poll();
	}
}

void aesd_configure_mode(struct _aesd_desc* desc)
{
	aes_soft_reset();

	aes_set_op_mode(desc->cfg.mode);
	aes_set_key_size(desc->cfg.key_size);
	aes_set_cfbs(desc->cfg.cfbs);

	/* Write the 128-bit/192-bit/256-bit key in the Key Word Registers */
	if (desc->cfg.key_size == AESD_AES128)
		aes_write_key(&desc->cfg.key[0], 16);
	else if (desc->cfg.key_size == AESD_AES192)
		aes_write_key(&desc->cfg.key[0], 24);
	else
		aes_write_key(&desc->cfg.key[0], 32);

	/* The Initialization Vector Registers apply to all modes except
	 * ECB. */
	if (desc->cfg.mode != AES_MR_OPMOD_ECB)
		aes_set_vector(&desc->cfg.vector[0]);
}

void aesd_init(struct _aesd_desc* desc)
{
	/* Enable peripheral clock */
	pmc_configure_peripheral(ID_AES, NULL, true);

	/* Allocate one DMA channel for writing message blocks to AES_IDATARx */
	desc->xfer.dma.tx.channel = dma_allocate_channel(DMA_PERIPH_MEMORY, ID_AES);
	assert(desc->xfer.dma.tx.channel);

	/* Allocate one DMA channel for obtaining the result from AES_ODATARx.*/
	desc->xfer.dma.rx.channel = dma_allocate_channel(ID_AES, DMA_PERIPH_MEMORY);
	assert(desc->xfer.dma.rx.channel);
}
