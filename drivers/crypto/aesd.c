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

	dma_reset_channel(desc->xfer.dma.rx.channel);

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

#ifdef CONFIG_HAVE_AES_GCM
static uint32_t _aesd_gcm_tag(struct _aesd_desc* desc)
{
	if(desc->cfg.entag) {
		if ((aes_get_status() & AES_ISR_TAGRDY) != AES_ISR_TAGRDY) {
			printf("AES GCM TAG did not ready/r/n");
			return AESD_ERROR_TRANSFER;
		}
	} else {
		// TODO
	}
	if(desc->cfg.entag) {
		aes_get_gcm_tag(&desc->cfg.tag[0]);
	} else {
		aes_get_output(&desc->cfg.tag[0], AES_BLOCK_SIZE);
	}
	return 0;
}
#endif

static void _aesd_transfer_buffer_polling(struct _aesd_desc* desc)
{
	uint32_t i;
	uint8_t num_of_data_words;

	num_of_data_words = _aesd_get_size_per_trans(desc);
	aes_enable_it(AES_IER_DATRDY);
	for (i = 0; i < desc->xfer.bufin->size; i+= num_of_data_words) {
		aes_set_input((void *)((desc->xfer.bufin->data) + i), num_of_data_words);
		if (desc->cfg.transfer_mode == AESD_TRANS_POLLING_MANUAL)
			/* Set the START bit in the AES Control register
			 to begin the encrypt. or decrypt. process. */
			aes_start();
		while ((aes_get_status() & AES_ISR_DATRDY) != AES_ISR_DATRDY);
		aes_get_output((void *)((desc->xfer.bufout->data) + i), num_of_data_words);
	}
	mutex_unlock(&desc->mutex);
#ifdef CONFIG_HAVE_AES_GCM
	if(desc->cfg.mode == AESD_MODE_GCM) {
		_aesd_gcm_tag(desc);
	}
#endif
	callback_call(&desc->xfer.callback, NULL);
}

static void _aesd_write_key(uint32_t* key, enum _aesd_key_size size, bool subkey)
{
	/* Write the 128-bit/192-bit/256-bit key in the Key Word Registers */
	if (size == AESD_AES128)
		aes_write_key(key, 16);
	else if (size == AESD_AES192)
		aes_write_key(key, 24);
	else
		aes_write_key(key, 32);
	if (subkey)
	/* Set KEYW in AES_KEYWRx and wait until DATRDY bit of AES_ISR is set (GCM hash subkey generation complete */
	while ((aes_get_status() & AES_ISR_DATRDY) != AES_ISR_DATRDY);
}
/*----------------------------------------------------------------------------
 *        Public functions

 *----------------------------------------------------------------------------*/
uint32_t aesd_transfer(struct _aesd_desc* desc,
					   struct _buffer* buffer_in,
					   struct _buffer* buffer_out,
					   struct _buffer* buffer_aad,
					   struct _callback* cb)
{
#ifdef CONFIG_HAVE_AES_GCM
	uint32_t padlen, aadlen, datalen;
	uint32_t i;
	uint32_t vsize;
	uint32_t j0[4];
	uint32_t j0_tmp;
	uint8_t *data;
#endif

#ifdef CONFIG_HAVE_AES_GCM
	uint32_t tweak[AES_BLOCK_SIZE / sizeof(uint32_t)];
	uint8_t *tweak_bytes = (uint8_t *)tweak;
	static uint32_t one[AES_BLOCK_SIZE / sizeof(uint32_t)] = {BIG_ENDIAN_TO_HOST(1), };
#endif

	aes_soft_reset();
	if (desc->cfg.mode != AESD_MODE_XTS) {
		aes_set_op_mode(desc->cfg.mode);
		aes_encrypt_enable(desc->cfg.encrypt);
	}
	aes_set_start_mode(AESD_TRANS_POLLING_AUTO);
#ifdef CONFIG_HAVE_AES_GCM
	aes_tag_enable(desc->cfg.entag);
#endif
	aes_set_key_size(desc->cfg.key_size);
	aes_set_cfbs(desc->cfg.cfbs);

#ifdef CONFIG_HAVE_AES_GCM
	if (desc->cfg.mode == AESD_MODE_GCM) {
		vsize = desc->cfg.vsize;
		if (vsize == IV_LENGTH_96) {
			/* Calculate the J0 value as described in NIST documentation J0 = IV || 031 || 1 when len(IV) = 96 */
			for (i = 0; i < IV_LENGTH_96 / 4; i++) {
				j0[i] = desc->cfg.vector[i];
			}
			j0[3] = 0x01000000;
		} else {
			/* Calculate the J0 value as described in NIST documentation J0 = GHASHH(IV || 0(s+64) || [len(IV)]64) if len(IV) ≠ 96 */
			for (i = 0; i < AES_BLOCK_SIZE / 4; i++) {
				j0[i] = desc->cfg.vector[i];
			}
			data = desc->buffer;
			padlen = vsize & (AES_BLOCK_SIZE -1);
			padlen = padlen > 0 ? 16 - padlen : 0;
			datalen = desc->cfg.vsize + padlen + AES_BLOCK_SIZE;
			memcpy(data, j0, vsize);
			memset(data + vsize, 0, padlen + 8);
			((uint64_t *)(data + datalen))[-1] = BIG_ENDIAN_TO_HOST_64((uint64_t)vsize * 8);
			_aesd_write_key(&desc->cfg.key[0], desc->cfg.key_size, true);
			aes_set_aad_len(desc->cfg.aadsize);
			aes_set_data_len(0);
			while (datalen > 0) {
				aes_set_input((void *)(data), AES_BLOCK_SIZE);
				data += 4;
				datalen -= AES_BLOCK_SIZE;
				while ((aes_get_status() & AES_ISR_DATRDY) != AES_ISR_DATRDY);
			}
			/* Read the computed hash from GHASHRx. */
			aes_get_gcm_hash(j0);
		}
	}
#endif
#ifdef CONFIG_HAVE_AES_XTS
	if (desc->cfg.mode == AESD_MODE_XTS) {
		/* In AES_MR, set OPMODE to ECB, CIPHER bit to ‘1' */
		aes_set_op_mode(AESD_MODE_ECB);
		aes_encrypt_enable(true);
		/* Set KEYW in AES_KEYWRx with Key2 */
		_aesd_write_key(&desc->cfg.key2[0], desc->cfg.key_size, false);
		/* Compute the tweak ecb(aes) mode. */
		aes_set_input((void *)(desc->cfg.tweakin), AES_BLOCK_SIZE);
		while ((aes_get_status() & AES_ISR_DATRDY) != AES_ISR_DATRDY);
		/* Read the computed ciphered tweak value. */
		aes_get_output((void *)(tweak), AES_BLOCK_SIZE);
		for (i = 0; i < AES_BLOCK_SIZE / 2; ++i) {
			uint8_t tmp = tweak_bytes[AES_BLOCK_SIZE - 1 - i];
			tweak_bytes[AES_BLOCK_SIZE - 1 - i] = tweak_bytes[i];
			tweak_bytes[i] = tmp;
		}
		/* it is required to fill the AES_TWRx register with the encrypted Tweak Value */
		aes_set_tweak(tweak);
		/* Fill the AES_ALPHARx register with the alpha primitive corresponding to the block number in the data unit */
		aes_set_alpha(one);
		aes_set_op_mode(desc->cfg.mode);
		aes_encrypt_enable(desc->cfg.encrypt);
	}
#endif

	if (desc->cfg.mode == AESD_MODE_GCM) {
		_aesd_write_key(&desc->cfg.key[0], desc->cfg.key_size, true);
	} else {
		_aesd_write_key(&desc->cfg.key[0], desc->cfg.key_size, false);
	}

#ifdef CONFIG_HAVE_AES_GCM
	if (desc->cfg.mode == AESD_MODE_GCM) {
		/* Set IV in AES_IVRx with inc32(J0) (J0 + 1 on 32 bits). */
		j0_tmp = j0[3];
		j0[3] = BIG_ENDIAN_TO_HOST((j0[3]) + 1);
		if (desc->cfg.mode != AES_MR_OPMOD_ECB)
			aes_set_vector(j0);
		j0[3] = j0_tmp;
		/* Set AADLEN field in AES_AADLENR and CLEN field in AES_CLENR */
		aes_set_aad_len(desc->cfg.aadsize);
		aes_set_data_len(desc->xfer.bufin->size);
		desc->xfer.aad = buffer_aad;
	}
#endif
	if ((desc->cfg.mode != AES_MR_OPMOD_ECB)
		|| (desc->cfg.mode != AESD_MODE_GCM)
		|| (desc->cfg.mode != AESD_MODE_XTS)
		)
		aes_set_vector(&desc->cfg.vector[0]);

#ifdef CONFIG_HAVE_AES_GCM
	if (desc->cfg.mode == AESD_MODE_GCM) {
		if (desc->cfg.aadsize != 0) {
			padlen = desc->cfg.aadsize & (AES_BLOCK_SIZE - 1) ;
			padlen = padlen > 0 ? AES_BLOCK_SIZE - padlen : 0;
			aadlen = padlen + desc->cfg.aadsize;
			for (i = 0; i < aadlen; i+= AES_BLOCK_SIZE) {
				aes_set_input((void *)((desc->xfer.aad->data) + i), AES_BLOCK_SIZE);
				while ((aes_get_status() & AES_ISR_DATRDY) != AES_ISR_DATRDY);
			}
		}
	}
#endif

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
