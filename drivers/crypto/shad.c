/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2019, Atmel Corporation
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
#include "swab.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

#define SHA_MAX_PADDING_LEN (2 * 128)

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

CACHE_ALIGNED static uint8_t sha_buffer[SHA_MAX_PADDING_LEN];
CACHE_ALIGNED static uint8_t ipad[1024];
CACHE_ALIGNED static uint8_t opad[1024];

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
#if defined(CONFIG_SOC_SAM9X60) || defined(CONFIG_SOC_SAMA5D2) || defined(CONFIG_SOC_SAMA5D4)
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
	cfg->len =  CEIL_INT_DIV(len , sizeof(uint32_t));
}

static int _shad_update_dma(struct _shad_desc* desc, const uint8_t* data, uint32_t data_size, bool auto_padding)
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

	if (!auto_padding) {
#ifdef CONFIG_HAVE_SHA_HMAC
		sha_set_msr(0);
		sha_set_bcr(0);
#endif
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
				return 0;
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
	} else {
#ifdef CONFIG_HAVE_SHA_HMAC
		sg_count = 0;
		sha_set_msr(data_size);
		sha_set_bcr(data_size);
		_shad_prepare_dma_sg(&cfg[sg_count], data, data_size);
		dma_configure_transfer(desc->dma_channel, &cfg_dma, cfg, sg_count+1);
		dma_start_transfer(desc->dma_channel);
		/* If automatic padding is enabled, the end of SHA processing requires only one
		interrupt to be verified . The DMA end of transfer is not required, so the SHA DATRDY
		interrupt must be enabled prior to start the DMA and DATRDY interrupt is the only one
		to be verified. */
		while ((sha_get_status() & SHA_ISR_DATRDY) == 0);
		mutex_unlock(&desc->mutex);
#else
		return -EINVAL;
#endif
	}
	return 0;
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

static uint32_t _shad_process_blocks_polling(const uint8_t* data, uint32_t len, int block_size, bool auto_padding)
{
	uint32_t processed = 0;

	while ((len - processed) >= block_size) {
		/* Write the block to be processed in the Input Data Registers */
		sha_set_input(&data[processed], block_size);

		/* Wait for the DATRDY bit (Data Ready) in the status register */
		while ((sha_get_status() & SHA_ISR_DATRDY) == 0);

		processed += block_size;
	}
	if (auto_padding) {
#ifdef CONFIG_HAVE_SHA_HMAC
		if (len - processed) {
			/* Write the block to be processed in the Input Data Registers */
			sha_set_input(&data[processed], len - - processed);
			/* Wait for the DATRDY bit (Data Ready) in the status register */
			while ((sha_get_status() & SHA_ISR_DATRDY) == 0);
			processed += block_size;
		}
#endif
	}
	return processed;
}

static int _shad_update_polling(struct _shad_desc* desc, const uint8_t* data, uint32_t data_size, bool auto_padding)
{
	const uint32_t block_size = _shad_get_block_size(desc->cfg.algo);
	uint32_t processed;

	if (!auto_padding) {
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
				_shad_process_blocks_polling(sha_buffer, desc->xfer.remaining, block_size, auto_padding);
				desc->xfer.processed += block_size;
				desc->xfer.remaining = 0;
			} else {
				/* Data will be processed on next shad_update or
				* shad_finish call, consider processing done */
				mutex_unlock(&desc->mutex);
				callback_call(&desc->xfer.callback, NULL);
				return 0;
			}
		}

		/* Process data by blocks */
		processed = _shad_process_blocks_polling(data, data_size, block_size, auto_padding);
		desc->xfer.processed += processed;

		/* If there is some data remaining, store it in sha_buffer for later
		* processing */
		desc->xfer.remaining = data_size - processed;
		if (desc->xfer.remaining)
			memcpy(sha_buffer, &data[processed], desc->xfer.remaining);

		/* Release mutex and execute callback function */
		mutex_unlock(&desc->mutex);
		callback_call(&desc->xfer.callback, NULL);
		return 0;
	} else {
#ifdef CONFIG_HAVE_SHA_HMAC
		sha_set_msr(data_size);
		sha_set_bcr(data_size);
		_shad_process_blocks_polling(data, data_size, block_size, auto_padding);
		while ((sha_get_status() & SHA_ISR_DATRDY) == 0);
		mutex_unlock(&desc->mutex);
		return 0;
#else
		return -EINVAL;
#endif
	}
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

int shad_get_digest_size(enum _shad_algo algo)
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

int shad_update(struct _shad_desc* desc, struct _buffer* buffer, bool auto_padding,
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
		_shad_update_dma(desc, buffer->data, buffer->size, auto_padding);
		break;
	case SHAD_TRANS_POLLING:
		_shad_update_polling(desc, buffer->data, buffer->size, auto_padding);
		break;
	default:
		mutex_unlock(&desc->mutex);
		return -EINVAL;
	}
	return 0;
}

int shad_finish(struct _shad_desc* desc, struct _buffer* buffer,
				bool auto_padding, struct _callback* cb)
{
	const uint32_t block_size = _shad_get_block_size(desc->cfg.algo);
	uint32_t padding_len;

	if (auto_padding) {
#ifdef CONFIG_HAVE_SHA_HMAC
		/* Get output data */
		sha_get_output(buffer->data, buffer->size);
		callback_call(&desc->xfer.callback, NULL);
		return 0;
#else
		return -EAGAIN;
#endif
	}

	if (!mutex_try_lock(&desc->mutex)) {
		trace_error("SHAD mutex already locked!\r\n");
		return -EAGAIN;
	}

	if (buffer->size != shad_get_digest_size(desc->cfg.algo))
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
		_shad_process_blocks_polling(sha_buffer, desc->xfer.remaining + padding_len, block_size, auto_padding);
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

static void hmac_precompute_key(struct _shad_desc* desc, struct _buffer* key)
{
	uint32_t digest_size = shad_get_digest_size(desc->cfg.algo);
	struct _buffer key0 = {
		.data = (uint8_t*)ipad,
		.size = digest_size,
	};
	bool autopading;

#ifdef CONFIG_HAVE_SHA_HMAC
	autopading = true;
#else
	autopading = false;
#endif
	/* If the length of K > B: hash K to obtain an L byte string, then append (B-L)
	   zeros to create a B-byte string K0 (i.e., K0 = H(K) || 00...00). */
	shad_update(desc, key, autopading, NULL);
	shad_wait_completion(desc);
	shad_finish(desc, &key0, autopading, NULL);
	shad_wait_completion(desc);
}

static void hmac_determine_k0(struct _shad_desc* desc, struct _buffer* key)
{
	const uint32_t B = _shad_get_block_size(desc->cfg.algo);
	uint32_t K = key->size;

	/* If the length of K = B: set K0 = K. */
	if (K == B ) {
		memcpy(ipad, key->data, K);
	}
	/* If the length of K < B: append zeros to the end of K to create a B-byte string K0
	(e.g., if K is 20 bytes in length and B = 64, then K will be appended with 44 zero bytes 0x00). */
	else if ( K < B) {
		memset (ipad, 0x0, 1024);
		memcpy((uint8_t *)ipad, key->data, K);
	} else {
	/* If the length of K > B: hash K to obtain an L byte string, then append (B-L)
	   zeros to create a B-byte string K0 (i.e., K0 = H(K) || 00...00). */
		memset (ipad, 0x0, 1024);
		hmac_precompute_key(desc, key);
	}
}

static void hmac_init_pad(uint32_t block_size)
{
	/* Conceptually, the intermediate results of the compression function on the B-byte blocks (K0 xor ipad)
	and (K0 xor opad) can be precomputed once, at the time of generation of the key K, or before its first use.*/
	memcpy(opad, ipad, block_size);
	for (int i = 0; i < block_size; ++i) {
		/* Exclusive-Or K0 with ipad to produce a B-byte string: K0 xor ipad */
		ipad[i] ^= 0x36; /* ipad Inner pad; the byte 0x36 repeated B times */
		/* Exclusive-Or K0 with opad: K0 xor opad. */
		opad[i] ^= 0x5C; /* opad Outer pad; the byte 0x5C repeated B times.*/
	}
}

#ifdef CONFIG_HAVE_SHA_HMAC
static void hmac_precompute_intermediate(struct _shad_desc* desc)
{
	const uint32_t B = _shad_get_block_size(desc->cfg.algo);
	uint32_t digest_size = shad_get_digest_size(desc->cfg.algo);
	uint32_t mr;

	shad_start(desc);
	mr = SHA->SHA_MR;
	sha_configure((mr & ~SHA_MR_SMOD_IDATAR0_START) | SHA_MR_SMOD_AUTO_START);

	/* Apply H to the stream generated : H(K0 xor ipad) */
	sha_first_block();
	sha_set_input(ipad, B);
	/* Wait for the DATRDY bit (Data Ready) in the status register */
	while ((sha_get_status() & SHA_ISR_DATRDY) == 0);
	sha_get_output(ipad, digest_size);

	sha_first_block();
	/* Apply H to the stream generated : H(K0 xor opad) */
	sha_set_input(opad, B);
	/* Wait for the DATRDY bit (Data Ready) in the status register */
	while ((sha_get_status() & SHA_ISR_DATRDY) == 0);
	sha_get_output(opad, digest_size);
	sha_configure(mr);
}

static int hmac_computer_with_intermediate(struct _shad_desc* desc,
                                           struct _buffer* text,
                                           struct _buffer* hmac)
{
	const uint32_t B = _shad_get_block_size(desc->cfg.algo);
	uint32_t digest_size = shad_get_digest_size(desc->cfg.algo);

	shad_start(desc);
	sha_set_ir0(1);
	sha_set_input(ipad, digest_size);
	sha_set_ir1(1);
	sha_set_input(opad, digest_size);
	sha_enable_hmac();
	sha_first_block();
	shad_update(desc, text, true, NULL);
	shad_wait_completion(desc);
	shad_finish(desc, hmac, true, NULL);
	shad_wait_completion(desc);
	return 0;
}
#else
static void hmac_hash_ipad_text(struct _shad_desc* desc, struct _buffer* text)
{
	const uint32_t B = _shad_get_block_size(desc->cfg.algo);
	uint32_t digest_size = shad_get_digest_size(desc->cfg.algo);
	struct _buffer buf_io = {
		.data = (uint8_t*)ipad,
		.size = B,
	};
	shad_start(desc);
	shad_update(desc, &buf_io, false, NULL);
	shad_wait_completion(desc);
	buf_io.data = text->data;
	buf_io.size = text->size;
	shad_update(desc, &buf_io, false, NULL);
	shad_wait_completion(desc);
	buf_io.data = ipad;
	buf_io.size = digest_size;
	shad_finish(desc, &buf_io, false, NULL);
	shad_wait_completion(desc);
}

static void hmac_hash_opad_ipad_text(struct _shad_desc* desc,
                                     struct _buffer* hmac)
{
	const uint32_t B = _shad_get_block_size(desc->cfg.algo);
	uint32_t digest_size = shad_get_digest_size(desc->cfg.algo);

	struct _buffer buf_io = {
		.data = (uint8_t*)opad,
		.size = B + digest_size,
	};
	/* Append the result from hmac_compute_ipad_hash(): (K0 xor opad) || H((K0 xor ipad) || text)*/
	memcpy(opad + B, ipad, digest_size);
	shad_start(desc);
	shad_update(desc, &buf_io, false, NULL);
	shad_wait_completion(desc);
	shad_finish(desc, hmac, false, NULL);
	shad_wait_completion(desc);
}

static int hmac_computer_without_intermediate(struct _shad_desc* desc,
                                               struct _buffer* text,
                                               struct _buffer* mac)
{
	/* FIPS Publication 198, Apply H to the stream generated in step 5: H((K0 xor ipad) || text). */
	hmac_hash_ipad_text(desc, text);
	/* FIPS Publication 198, Apply H to the result from step 8: H((K0 xor opad )|| H((K0 xor ipad) || text)). */
	hmac_hash_opad_ipad_text(desc, mac);
	return 0;
}
#endif

int shad_compute_hash(struct _shad_desc* desc,
					  struct _buffer* text,
					  struct _buffer* digest,
					  struct _callback* cb)
{
	bool autopading;

	shad_start(desc);
#ifdef CONFIG_HAVE_SHA_HMAC
	autopading = true;
#else
	autopading = false;
#endif
	shad_update(desc, text, autopading, NULL);
	shad_wait_completion(desc);
	shad_finish(desc, digest, autopading, NULL);
	shad_wait_completion(desc);
	return 0;
}

int shad_hmac_set_key(struct _shad_desc* desc,
					  struct _buffer* key)
{
	const uint32_t B = _shad_get_block_size(desc->cfg.algo);

	/* FIPS Publication 198 :
	To compute a MAC over the data ‘text’ using the HMAC function, the following operation is performed:
	HMAC(text) = HMAC(K, text) = H((K0 xor opad )|| H((K0 xor ipad) || text)) */

	/* Step 1 - 3 :
		If the length of K = B: set K0 = K.
		If the length of K > B: hash K to obtain an L byte string, then append (B-L) zeros to create a B-byte string K0.
		If the length of K < B: append zeros to the end of K to create a B-byte string K0. */
	shad_start(desc);
	hmac_determine_k0(desc, key);
	hmac_init_pad(B);
#ifdef CONFIG_HAVE_SHA_HMAC
	/* These pre-computed first blocks speed up the HMAC computation by saving the time to compute the intermediate
		hash values of the first block which is constant while the secret key is constant */
	hmac_precompute_intermediate(desc);
#endif
	return 0;
}

int shad_compute_hmac(struct _shad_desc* desc,
					  struct _buffer* text,
					  struct _buffer* digest,
					  struct _callback* cb)
{
	shad_start(desc);
#ifdef CONFIG_HAVE_SHA_HMAC
	return hmac_computer_with_intermediate(desc, text, digest);
#else
	return hmac_computer_without_intermediate(desc, text, digest);
#endif
}