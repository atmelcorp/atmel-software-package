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

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "crypto/shad.h"
#include "crypto/sha.h"
#include "dma/dma.h"
#include "errno.h"
#include "intmath.h"
#include "irq/irq.h"
#include "mm/cache.h"
#include "peripherals/pmc.h"
#include "serial/console.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

#define SHA_MAX_PADDING_LEN (2 * 128)

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

CACHE_ALIGNED
static uint8_t sha_buffer[SHA_MAX_PADDING_LEN];

volatile static bool single_transfer_ready;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static uint8_t _shad_get_block_size(enum _shad_algo algo)
{
	if (algo == ALGO_SHA_384 || algo == ALGO_SHA_512)
		return 128;
	else
		return 64;
}

static uint32_t _shad_get_padded_message_len(uint8_t mode, uint32_t len)
{
	uint32_t k;

	switch (mode) {
	case ALGO_SHA_1:
	case ALGO_SHA_224:
	case ALGO_SHA_256:
		k = (512 + 448 - (((len * 8) % 512) + 1)) % 512;
		len += (k - 7) / 8 + 9;
		break;
	case ALGO_SHA_384:
	case ALGO_SHA_512:
		k = (1024 + 896 - (((len * 8) % 1024) + 1)) % 1024;
		len += (k - 7) / 8 + 17;
		break;
	}
	return len;
}

static uint32_t _shad_fill_padding(enum _shad_algo algo, uint32_t len, uint8_t* buffer, uint32_t buffer_len)
{
	uint32_t padding_len = _shad_get_padded_message_len(algo, len) - len;
	uint32_t k = padding_len - 9;

	assert(padding_len <= buffer_len);

	/* Append "1" bit and seven "0" bits to the end of the message */
	*buffer++ = 0x80;
	/* Followed by k "0" bits */
	memset(buffer, 0, k);
	buffer += k;
	/* Then append the 64-bit length (in bits) */
	*buffer++ = 0;
	*buffer++ = 0;
	*buffer++ = 0;
	*buffer++ = (len >> 29) & 0xff;
	*buffer++ = (len >> 21) & 0xff;
	*buffer++ = (len >> 13) & 0xff;
	*buffer++ = (len >> 5) & 0xff;
	*buffer++ = (len << 3) & 0xff;
	return padding_len;
}

static uint8_t _shad_get_dma_chunk_size(enum _shad_algo algo)
{
#if defined(CONFIG_SOC_SAMA5D2) || defined(CONFIG_SOC_SAMA5D4)
	return DMA_CHUNK_SIZE_16;
#elif defined(CONFIG_SOC_SAMA5D3)
	if (algo == ALGO_SHA_384 || algo == ALGO_SHA_512)
		return DMA_CHUNK_SIZE_32;
	else
		return DMA_CHUNK_SIZE_16;
#endif
}

static void _shad_finish(struct _shad_desc* desc)
{
	/* Get output data */
	sha_get_output(desc->xfer.buffer->data, desc->xfer.buffer->size);

	/* Release mutex and execute callback function */
	mutex_unlock(&desc->mutex);
	callback_call(&desc->xfer.callback, NULL);
}

static int _shad_dma_update_callback(void *arg, void* arg2)
{
	struct _shad_desc* desc = (struct _shad_desc*)arg;

	dma_reset_channel(desc->dma_channel);

	/* Wait for the DATRDY bit (Data Ready) in the status register */
	while ((sha_get_status() & SHA_ISR_DATRDY) == 0);

	/* Release mutex and execute callback function */
	mutex_unlock(&desc->mutex);
	callback_call(&desc->xfer.callback, NULL);

	return 0;
}

static void _shad_prepare_dma_sg(struct _dma_transfer_cfg* cfg, const uint8_t* data, uint32_t len)
{
	cache_clean_region(data, len);
	memset(cfg, 0, sizeof(*cfg));
	cfg->saddr = data;
	cfg->daddr = (void*)&SHA->SHA_IDATAR[0];
	cfg->len = len / sizeof(uint32_t);
}

static void _shad_update_dma(struct _shad_desc* desc, const uint8_t* data, uint32_t data_size)
{
	const uint32_t block_size = _shad_get_block_size(desc->cfg.algo);
	uint32_t processed;
	struct _dma_cfg cfg_dma;
	struct _dma_transfer_cfg cfg[2];
	struct _callback _cb;
	uint32_t sg_count = 0;

	memset(&cfg_dma, 0, sizeof(cfg_dma));
	cfg_dma.incr_saddr = true;
	cfg_dma.incr_daddr = false;
	cfg_dma.data_width = DMA_DATA_WIDTH_WORD;
	cfg_dma.chunk_size = _shad_get_dma_chunk_size(desc->cfg.algo);

	callback_set(&_cb, _shad_dma_update_callback, (void*)desc);
	dma_set_callback(desc->dma_channel, &_cb);

	/* Check if remaining data to process from previous update */
	if (desc->xfer.remaining) {
		/* Append some data from current buffer to complete previous pending data */
		uint32_t complement = min_u32(data_size, block_size - desc->xfer.remaining);
		memcpy(&sha_buffer[desc->xfer.remaining], data, complement);
		desc->xfer.remaining += complement;
		data += complement;
		data_size -= complement;

		/* Do we have enough data to process? */
		if (desc->xfer.remaining == block_size) {
			/* Yes, process the block */
			_shad_prepare_dma_sg(&cfg[sg_count], sha_buffer, desc->xfer.remaining);
			sg_count++;
			desc->xfer.processed += block_size;
			desc->xfer.remaining = 0;
		} else {
			/* Data will be processed on next shad_update or
			 * shad_finish call, consider processing done */
			mutex_unlock(&desc->mutex);
			callback_call(&desc->xfer.callback, NULL);
			return;
		}
	}

	/* Process data by blocks */
	processed = data_size & ~(block_size - 1);
	if (processed > 0) {
		_shad_prepare_dma_sg(&cfg[sg_count], data, processed);
		sg_count++;
		desc->xfer.processed += processed;
	}

	/* If there is some data remaining, store it in sha_buffer for later
	 * processing */
	desc->xfer.remaining = data_size - processed;
	if (desc->xfer.remaining)
		memcpy(sha_buffer, &data[processed], desc->xfer.remaining);

	if (sg_count == 0) {
		/* No more data, consider processing done */
		mutex_unlock(&desc->mutex);
		callback_call(&desc->xfer.callback, NULL);
	} else {
		/* Configure & start DMA transfer */
		dma_configure_transfer(desc->dma_channel, &cfg_dma, cfg, sg_count);
		dma_start_transfer(desc->dma_channel);
	}
}

static int _shad_dma_finish_callback(void *arg, void* arg2)
{
	struct _shad_desc* desc = (struct _shad_desc*)arg;

	dma_reset_channel(desc->dma_channel);

	/* Wait for the DATRDY bit (Data Ready) in the status register */
	while ((sha_get_status() & SHA_ISR_DATRDY) == 0);

	/* Get output data, release mutex & execute callback */
	_shad_finish(desc);

	return 0;
}

static void _shad_finish_dma(struct _shad_desc* desc, uint32_t data_len)
{
	struct _dma_cfg cfg_dma;
	struct _dma_transfer_cfg cfg;
	struct _callback _cb;

	memset(&cfg_dma, 0, sizeof(cfg_dma));
	cfg_dma.incr_saddr = true;
	cfg_dma.incr_daddr = false;
	cfg_dma.data_width = DMA_DATA_WIDTH_WORD;
	cfg_dma.chunk_size = _shad_get_dma_chunk_size(desc->cfg.algo);

	callback_set(&_cb, _shad_dma_finish_callback, (void*)desc);
	dma_set_callback(desc->dma_channel, &_cb);

	_shad_prepare_dma_sg(&cfg, sha_buffer, data_len);

	/* Configure & start DMA transfer */
	dma_configure_transfer(desc->dma_channel, &cfg_dma, &cfg, 1);
	dma_start_transfer(desc->dma_channel);
}

static uint32_t _shad_process_blocks_polling(const uint8_t* data, uint32_t len, int block_size)
{
	uint32_t processed = 0;

	while ((len - processed) >= block_size) {
		/* Write the block to be processed in the Input Data Registers */
		sha_set_input(&data[processed], block_size);

		/* Wait for the DATRDY bit (Data Ready) in the status register */
		while ((sha_get_status() & SHA_ISR_DATRDY) == 0);

		processed += block_size;
	}

	return processed;
}

static void _shad_update_polling(struct _shad_desc* desc, const uint8_t* data, uint32_t data_size)
{
	const uint32_t block_size = _shad_get_block_size(desc->cfg.algo);
	uint32_t processed;

	/* Check if remaining data to process from previous update */
	if (desc->xfer.remaining) {
		/* Append some data from current buffer to complete previous pending data */
		uint32_t complement = min_u32(data_size, block_size - desc->xfer.remaining);
		memcpy(&sha_buffer[desc->xfer.remaining], data, complement);
		desc->xfer.remaining += complement;
		data += complement;
		data_size -= complement;

		/* Do we have enough data to process? */
		if (desc->xfer.remaining == block_size) {
			/* Yes, process the block */
			_shad_process_blocks_polling(sha_buffer, desc->xfer.remaining, block_size);
			desc->xfer.processed += block_size;
			desc->xfer.remaining = 0;
		} else {
			/* Data will be processed on next shad_update or
			 * shad_finish call, consider processing done */
			mutex_unlock(&desc->mutex);
			callback_call(&desc->xfer.callback, NULL);
			return;
		}
	}

	/* Process data by blocks */
	processed = _shad_process_blocks_polling(data, data_size, block_size);
	desc->xfer.processed += processed;

	/* If there is some data remaining, store it in sha_buffer for later
	 * processing */
	desc->xfer.remaining = data_size - processed;
	if (desc->xfer.remaining)
		memcpy(sha_buffer, &data[processed], desc->xfer.remaining);

	/* Release mutex and execute callback function */
	mutex_unlock(&desc->mutex);
	callback_call(&desc->xfer.callback, NULL);
}

/*----------------------------------------------------------------------------
 *        Public functions
 *----------------------------------------------------------------------------*/

void shad_init(struct _shad_desc* desc)
{
	/* Enable peripheral clock */
	pmc_configure_peripheral(ID_SHA, NULL, true);

	/* Allocate one DMA channel for writing message blocks to SHA_IDATARx */
	desc->dma_channel = dma_allocate_channel(DMA_PERIPH_MEMORY, ID_SHA);
	assert(desc->dma_channel);
}

int shad_get_output_size(enum _shad_algo algo)
{
	switch (algo) {
	case ALGO_SHA_1:
		return 20;
	case ALGO_SHA_224:
		return 28;
	case ALGO_SHA_256:
		return 32;
	case ALGO_SHA_384:
		return 48;
	case ALGO_SHA_512:
		return 64;
	default:
		return -EINVAL;
	}
}

int shad_start(struct _shad_desc* desc)
{
	uint32_t algo, mode;

	switch (desc->cfg.algo) {
	case ALGO_SHA_1:
		algo = SHA_MR_ALGO_SHA1;
		break;
	case ALGO_SHA_224:
		algo = SHA_MR_ALGO_SHA224;
		break;
	case ALGO_SHA_256:
		algo = SHA_MR_ALGO_SHA256;
		break;
#ifdef SHA_MR_ALGO_SHA384
	case ALGO_SHA_384:
		algo = SHA_MR_ALGO_SHA384;
		break;
#endif
#ifdef SHA_MR_ALGO_SHA512
	case ALGO_SHA_512:
		algo = SHA_MR_ALGO_SHA512;
		break;
#endif
	default:
		return -EINVAL;
	}

	switch (desc->cfg.transfer_mode) {
	case SHAD_TRANS_POLLING:
		mode = SHA_MR_SMOD_AUTO_START;
		break;
	case SHAD_TRANS_DMA:
		mode = SHA_MR_SMOD_IDATAR0_START;
		break;
	default:
		return -EINVAL;
	}

	sha_soft_reset();
	sha_configure(algo | mode | SHA_MR_PROCDLY_LONGEST);

	memset(&desc->xfer, 0, sizeof(desc->xfer));

	return 0;
}

int shad_update(struct _shad_desc* desc, struct _buffer* buffer,
                     struct _callback* cb)
{
	if (!mutex_try_lock(&desc->mutex)) {
		trace_error("SHAD mutex already locked!\r\n");
		return -EAGAIN;
	}

	callback_copy(&desc->xfer.callback, cb);

	/* For the first block of a message, the FIRST command must be set by
	 * setting the corresponding bit of the Control Register (SHA_CR). */
	if (!desc->xfer.processed)
		sha_first_block();

	switch (desc->cfg.transfer_mode) {
	case SHAD_TRANS_DMA:
		/* Check that remaining data size and buffer address are
		 * aligned correctly */
		assert((desc->xfer.remaining & 3) == 0);
		assert((((uint32_t)buffer->data) & (L1_CACHE_BYTES - 1)) == 0);
		_shad_update_dma(desc, buffer->data, buffer->size);
		break;
	case SHAD_TRANS_POLLING:
		_shad_update_polling(desc, buffer->data, buffer->size);
		break;
	default:
		mutex_unlock(&desc->mutex);
		return -EINVAL;
	}

	return 0;
}

int shad_finish(struct _shad_desc* desc, struct _buffer* buffer,
                     struct _callback* cb)
{
	const uint32_t block_size = _shad_get_block_size(desc->cfg.algo);
	uint32_t padding_len;

	if (!mutex_try_lock(&desc->mutex)) {
		trace_error("SHAD mutex already locked!\r\n");
		return -EAGAIN;
	}

	if (buffer->size != shad_get_output_size(desc->cfg.algo))
		return -EINVAL;

	callback_copy(&desc->xfer.callback, cb);
	desc->xfer.buffer = buffer;

	/* Fill end of buffer with padding data */
	padding_len = _shad_fill_padding(desc->cfg.algo,
	                                 desc->xfer.processed + desc->xfer.remaining,
	                                 &sha_buffer[desc->xfer.remaining],
	                                 ARRAY_SIZE(sha_buffer) - desc->xfer.remaining);

	switch (desc->cfg.transfer_mode) {
	case SHAD_TRANS_DMA:
		_shad_finish_dma(desc, desc->xfer.remaining + padding_len);
		break;
	case SHAD_TRANS_POLLING:
		_shad_process_blocks_polling(sha_buffer, desc->xfer.remaining + padding_len, block_size);
		_shad_finish(desc);
		break;
	default:
		mutex_unlock(&desc->mutex);
		return -EINVAL;
	}

	return 0;
}

bool shad_is_busy(struct _shad_desc* desc)
{
	return mutex_is_locked(&desc->mutex);
}

void shad_wait_completion(struct _shad_desc* desc)
{
	while (shad_is_busy(desc)) {
		if (desc->cfg.transfer_mode == SHAD_TRANS_DMA)
			dma_poll();
	}
}
