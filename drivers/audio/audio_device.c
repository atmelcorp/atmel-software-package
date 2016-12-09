/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2016, Atmel Corporation                                        */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Atmel's name may not be used to endorse or promote products derived from     */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR   */
/* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE   */
/* DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,      */
/* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,  */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    */
/* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING         */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/* ---------------------------------------------------------------------------- */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "audio_device.h"
#include "chip.h"
#include "dma/dma.h"
#include "mm/cache.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

#if defined(CONFIG_HAVE_CLASSD)
/**
 * Configure the CLASSD for audio output.
 */
static void _configure_classd(struct _audio_desc* desc)
{
	/* Configure Class D */
	if (desc->num_channels == 1) {
		desc->device.classd.desc.swap_channels = true,
		desc->device.classd.desc.left_enable = false;
		desc->device.classd.desc.right_enable = true;
	} else {
		desc->device.classd.desc.swap_channels = false;
		desc->device.classd.desc.left_enable = true;
		desc->device.classd.desc.right_enable = true;
	}
	desc->device.classd.desc.transfer_mode = CLASSD_MODE_DMA;
	desc->device.classd.desc.addr = desc->device.classd.addr;
	classd_configure(&desc->device.classd.desc);
	classd_set_left_attenuation(&desc->device.classd.desc, 30);
	classd_set_right_attenuation(&desc->device.classd.desc, 30);
	classd_volume_unmute(&desc->device.classd.desc, true, true);
	classd_enable_channels(&desc->device.classd.desc, true, true);
}
#endif

#if defined(CONFIG_HAVE_SSC)
/**
 * Configure the SSC for audio output.
 */
static void _configure_ssc(struct _audio_desc *desc)
{
	desc->device.ssc.desc.addr = desc->device.ssc.addr;
	desc->device.ssc.desc.sample_rate = desc->sample_rate;
	desc->device.ssc.desc.slot_num = desc->num_channels;
	desc->device.ssc.desc.slot_length = desc->bits_per_sample;

	ssc_configure(&desc->device.ssc.desc);
	ssc_disable_transmitter(&desc->device.ssc.desc);
	ssc_disable_receiver(&desc->device.ssc.desc);

	switch (desc->device.ssc.codec->type) {
	case AUDIO_CODEC_NONE:
		trace_warning("SSC: no codec defined\r\n");
		break;
#ifdef CONFIG_HAVE_AUDIO_WM8904
	case AUDIO_CODEC_WM8904:
		wm8904_configure(&desc->device.ssc.codec->wm8904);
		break;
#endif
#ifdef CONFIG_HAVE_AUDIO_WM8731
	case AUDIO_CODEC_WM8731:
		wm8731_configure(&desc->device.ssc.codec->wm8731);
		break;
#endif
#ifdef CONFIG_HAVE_AUDIO_AD1934
	case AUDIO_CODEC_AD1934:
		ad1934_configure(&desc->device.ssc.codec->ad1934);
		ad1934_set_sample_rate(&desc->device.ssc.codec->ad1934,
				desc->device.ssc.desc.sample_rate);
		/* walk around setting */
		ad1934_set_tdm_slot(&desc->device.ssc.codec->ad1934,
				desc->device.ssc.desc.slot_num * 2);
		ad1934_set_word_width(&desc->device.ssc.codec->ad1934,
				desc->device.ssc.desc.slot_length);
		break;
#endif
	default:
		trace_fatal("SSC: no supported codec defined\r\n");
	}

	/* Mute */
	audio_enable(desc, false);
}

#endif /* CONFIG_HAVE_SSC */

#if defined(CONFIG_HAVE_PDMIC)
static void _configure_pdmic(struct _audio_desc *desc)
{
	/* configure PIO muxing for pdmic */
	desc->device.pdmic.desc.sample_rate = desc->sample_rate;
	desc->device.pdmic.desc.channels = desc->num_channels;
	desc->device.pdmic.desc.dsp_size = desc->bits_per_sample;

	pdmic_init(&desc->device.pdmic.desc);
}
#endif
/**
 *  \brief Start sending next buffer to audio play device using DMA.
 */
static void _audio_dma_start_transfer(struct _audio_desc *desc, void *src_address, void *dest_address,
									uint32_t size, audio_callback_t cb)
{
	if (size)
		cache_clean_region(src_address, size);

	desc->dma.cfg.sa = (uint32_t*)src_address;
	desc->dma.cfg.da = (uint32_t*)dest_address;

	dma_configure_transfer(desc->dma.channel, &desc->dma.cfg);
	if(cb)
		dma_set_callback(desc->dma.channel, cb, NULL);
	dma_start_transfer(desc->dma.channel);
}

static void _configure_audio_device(struct _audio_desc *desc)
{
	switch (desc->type) {
#if defined(CONFIG_HAVE_CLASSD)
	case AUDIO_DEVICE_CLASSD:
		_configure_classd(desc);
		break;
#endif
#if defined(CONFIG_HAVE_SSC)
	case AUDIO_DEVICE_SSC:
		_configure_ssc(desc);
		break;
#endif
#if defined(CONFIG_HAVE_PDMIC)
	case AUDIO_DEVICE_PDMIC:
		_configure_pdmic(desc);
		break;
#endif
	default:
		return;

	}
}

static uint32_t _get_audio_id_from_addr(struct _audio_desc *desc)
{
	switch (desc->type) {
#if defined(CONFIG_HAVE_CLASSD)
	case AUDIO_DEVICE_CLASSD:
		return get_classd_id_from_addr(desc->device.classd.addr);
#endif
#if defined(CONFIG_HAVE_SSC)
	case AUDIO_DEVICE_SSC:
		return get_ssc_id_from_addr(desc->device.ssc.addr);
#endif
#if defined(CONFIG_HAVE_PDMIC)
	case AUDIO_DEVICE_PDMIC:
		return get_pdmic_id_from_addr(desc->device.pdmic.addr);
#endif
	default:
		return ID_PERIPH_COUNT;
	}
}

/**
 * Configure audio play/record
 */
void audio_configure(struct _audio_desc *desc)
{
	uint32_t audio_id = _get_audio_id_from_addr(desc);

	if (!audio_id)
		return;

	_configure_audio_device(desc);

	switch (desc->direction) {
	case AUDIO_DEVICE_PLAY:
		/* Allocate DMA TX channels for Audio play device */
		desc->dma.channel = dma_allocate_channel(DMA_PERIPH_MEMORY, audio_id);
		break;

	case AUDIO_DEVICE_RECORD:
		/* Allocate DMA RX channels for Audio record device */
		desc->dma.channel = dma_allocate_channel(audio_id, DMA_PERIPH_MEMORY);
		break;
	}
	if (!desc->dma.channel) {
		printf("DMA channel allocation error\n\r");
	}
}

/**
 * Enable/Disable audio channels
 */
void audio_enable(struct _audio_desc *desc, bool enable)
{
	switch (desc->type) {
#if defined(CONFIG_HAVE_CLASSD)
	case AUDIO_DEVICE_CLASSD:
		switch (desc->direction) {
		case AUDIO_DEVICE_PLAY:
			if (enable)
				classd_enable_channels(&desc->device.classd.desc, true, true);
			else
				classd_disable_channels(&desc->device.classd.desc, true, true);
			break;
		case AUDIO_DEVICE_RECORD:
			return;
		}
		break;
#endif
#if defined(CONFIG_HAVE_SSC)
	case AUDIO_DEVICE_SSC:
		switch (desc->direction) {
		case AUDIO_DEVICE_PLAY:
			if (enable)
				ssc_enable_transmitter(&desc->device.ssc.desc);
			else
				ssc_disable_transmitter(&desc->device.ssc.desc);
			break;
		case AUDIO_DEVICE_RECORD:
			if (enable)
				ssc_enable_receiver(&desc->device.ssc.desc);
			else
				ssc_disable_receiver(&desc->device.ssc.desc);
			break;
		}
		break;
#endif
#if defined(CONFIG_HAVE_PDMIC)
	case AUDIO_DEVICE_PDMIC:
		switch (desc->direction) {
		case AUDIO_DEVICE_PLAY:
			return;
		case AUDIO_DEVICE_RECORD:
			pdmic_stream_convert(&desc->device.pdmic.desc, enable);
			break;
		}
		break;
#endif
	default:
		return;
	}
}

/**
 * Mute/Unmute audio channels
 */
void audio_play_mute(struct _audio_desc *desc, bool mute)
{
	if (mute) {
		switch (desc->type) {
#if defined(CONFIG_HAVE_CLASSD)
		case AUDIO_DEVICE_CLASSD:
			classd_volume_mute(&desc->device.classd.desc, true, true);
			break;
#endif
#if defined(CONFIG_HAVE_SSC)
		case AUDIO_DEVICE_SSC:
			switch (desc->device.ssc.codec->type) {
#ifdef CONFIG_HAVE_AUDIO_WM8904
			case AUDIO_CODEC_WM8904:
				wm8904_volume_mute(&desc->device.ssc.codec->wm8904, true, true);
				break;
#endif
#ifdef CONFIG_HAVE_AUDIO_WM8731
			case AUDIO_CODEC_WM8731:
				wm8731_volume_mute(&desc->device.ssc.codec->wm8731, true);
				break;
#endif
#ifdef CONFIG_HAVE_AUDIO_AD1934
			case AUDIO_CODEC_AD1934:
				ad1934_master_volume_mute(&desc->device.ssc.codec->ad1934, true);
				break;
#endif
			default:
				return;
			};
			break;
#endif
		default:
			return;
		}
	} else {
		switch (desc->type) {
#if defined(CONFIG_HAVE_CLASSD)
		case AUDIO_DEVICE_CLASSD:
			classd_volume_unmute(&desc->device.classd.desc, true, true);
			break;
#endif
#if defined(CONFIG_HAVE_SSC)
		case AUDIO_DEVICE_SSC:
			switch (desc->device.ssc.codec->type) {
#ifdef CONFIG_HAVE_AUDIO_WM8904
			case AUDIO_CODEC_WM8904:
				wm8904_volume_mute(&desc->device.ssc.codec->wm8904, false, false);
				break;
#endif
#ifdef CONFIG_HAVE_AUDIO_WM8731
			case AUDIO_CODEC_WM8731:
				wm8731_volume_mute(&desc->device.ssc.codec->wm8731, false);
				break;
#endif
#ifdef CONFIG_HAVE_AUDIO_AD1934
			case AUDIO_CODEC_AD1934:
				ad1934_master_volume_mute(&desc->device.ssc.codec->ad1934, false);
				break;
#endif
			default:
				return;
			};
			break;
#endif
		default:
			return;
		}
	}
}

/**
 * Set audio play volume
 */
void audio_play_set_volume(struct _audio_desc *desc, uint8_t vol)
{
	/* unify the volume value for different codec chip */
	/* vol=0 means min volume, vol=100 means max volume */
	uint8_t val;
	if (vol <= AUDIO_PLAY_MAX_VOLUME) {
		switch (desc->type) {
#if defined(CONFIG_HAVE_CLASSD)
		case AUDIO_DEVICE_CLASSD:
			/* classd attenuation range 0~-77db*/
			val = (AUDIO_PLAY_MAX_VOLUME - vol) * 77 / AUDIO_PLAY_MAX_VOLUME;
			classd_set_left_attenuation(&desc->device.classd.desc, val);
			classd_set_right_attenuation(&desc->device.classd.desc, val);
			break;
#endif

#if defined(CONFIG_HAVE_SSC)
		case AUDIO_DEVICE_SSC:
			switch (desc->device.ssc.codec->type) {
#ifdef CONFIG_HAVE_AUDIO_WM8904
			case AUDIO_CODEC_WM8904:
				/* wm8904 heardphone output volume range -57db~6db */
				val = (vol * 63) / AUDIO_PLAY_MAX_VOLUME;
				wm8904_set_left_volume(&desc->device.ssc.codec->wm8904, val);
				wm8904_set_right_volume(&desc->device.ssc.codec->wm8904, val);
				break;
#endif
#ifdef CONFIG_HAVE_AUDIO_WM8731
			case AUDIO_CODEC_WM8731:
				/* wm8731 heardphone output volume range -73~6db */
				val = (vol * 79) / AUDIO_PLAY_MAX_VOLUME;
				wm8731_set_left_volume(&desc->device.ssc.codec->wm8731, val);
				wm8731_set_right_volume(&desc->device.ssc.codec->wm8731, val);
				break;
#endif
#ifdef CONFIG_HAVE_AUDIO_AD1934
			case AUDIO_CODEC_AD1934:
				/* AD1934 channel volume control, 1 to 254 -> -3/8dB per  step */
				val = (AUDIO_PLAY_MAX_VOLUME-vol)*255/AUDIO_PLAY_MAX_VOLUME;
				ad1934_set_channel_volume(&desc->device.ssc.codec->ad1934, AD1934_DAC_L1_CHANNEL, val);
				ad1934_set_channel_volume(&desc->device.ssc.codec->ad1934, AD1934_DAC_R1_CHANNEL, val);
				break;
#endif
			default:
				return;
			};
			break;
#endif
		default:
			return;
		}
	}
}

/**
 * Stop audio data transfer
 */
void audio_dma_stop(struct _audio_desc *desc)
{
	switch (desc->type) {
#if defined(CONFIG_HAVE_CLASSD)
	case AUDIO_DEVICE_CLASSD:
		classd_dma_stop(&desc->device.classd.desc);
		break;
#endif
#if defined(CONFIG_HAVE_SSC)
	case AUDIO_DEVICE_SSC:
		break;
#endif
#if defined(CONFIG_HAVE_PDMIC)
	case AUDIO_DEVICE_PDMIC:
		pdmic_dma_stop(&desc->device.pdmic.desc);
		break;
#endif
	default:
		if (desc->dma.channel)
			dma_stop_transfer(desc->dma.channel);
		return;

	}
}

void audio_dma_transfer(struct _audio_desc *desc, void *buffer, uint32_t size,
						audio_callback_t cb)
{
	uint32_t *src_addr = NULL;
	uint32_t *dst_addr = NULL;
	uint32_t dma_data_width = DMA_DATA_WIDTH_HALF_WORD;

	switch (desc->type) {
#if defined(CONFIG_HAVE_CLASSD)
	case AUDIO_DEVICE_CLASSD:
		switch (desc->direction) {
		case AUDIO_DEVICE_PLAY: {
			struct _buffer _tx = {
				.data = (uint8_t*)buffer,
				.size = size,
				.attr = CLASSD_BUF_ATTR_WRITE,
			};

			classd_transfer(&desc->device.classd.desc, &_tx, (classd_callback_t)cb, NULL);
		}
		break;

		case AUDIO_DEVICE_RECORD:
			/* Do not supported */
			return;
		}
		break;
#endif
#if defined(CONFIG_HAVE_SSC)
	case AUDIO_DEVICE_SSC:
		switch (desc->direction) {
		case AUDIO_DEVICE_PLAY:
			src_addr = buffer;
			dst_addr = (uint32_t*)&((desc->device.ssc.addr)->SSC_THR);
			desc->dma.cfg.upd_sa_per_data = 1;
			desc->dma.cfg.upd_da_per_data = 0;
			break;

		case AUDIO_DEVICE_RECORD:
			src_addr = (uint32_t*)&((desc->device.ssc.addr)->SSC_RHR);
			dst_addr = buffer;
			desc->dma.cfg.upd_sa_per_data = 0;
			desc->dma.cfg.upd_da_per_data = 1;
			break;
		}
		break;
#endif
#if defined(CONFIG_HAVE_PDMIC)
	case AUDIO_DEVICE_PDMIC:
		switch (desc->direction) {
		case AUDIO_DEVICE_PLAY:
			/* Do not supported */
			return;

		case AUDIO_DEVICE_RECORD: {
			struct _buffer _rx = {
				.data = (uint8_t*)buffer,
				.size = size,
				.attr = PDMIC_BUF_ATTR_READ,
			};

			pdmic_transfer(&desc->device.pdmic.desc, &_rx, (pdmic_callback_t)cb, NULL);
		} break;
		}
		break;
#endif
	default:
		/* No audio device */
		return;
	}

	if (!desc->dma.configured) {
#if defined(CONFIG_HAVE_SSC)
		if (desc->device.ssc.desc.slot_length == 8)
			dma_data_width = DMA_DATA_WIDTH_BYTE;
		else if (desc->device.ssc.desc.slot_length == 16)
			dma_data_width = DMA_DATA_WIDTH_HALF_WORD;
		else if (desc->device.ssc.desc.slot_length == 32)
			dma_data_width = DMA_DATA_WIDTH_WORD;
#endif
		desc->dma.cfg.chunk_size = DMA_CHUNK_SIZE_1;
		desc->dma.cfg.data_width = dma_data_width;
		desc->dma.cfg.blk_size = 0;
		desc->dma.configured = true;
	}
	if (dma_data_width == DMA_DATA_WIDTH_WORD) {
		desc->dma.cfg.len = size / 4;
	} else if (dma_data_width == DMA_DATA_WIDTH_HALF_WORD) {
		desc->dma.cfg.len = size / 2;
	} else if (dma_data_width == DMA_DATA_WIDTH_BYTE) {
		desc->dma.cfg.len = size;
	}

	if (dst_addr)
		_audio_dma_start_transfer(desc, src_addr, (void*)dst_addr, size, cb);
}

bool audio_dma_transfer_is_done(struct _audio_desc *desc)
{
	switch (desc->type) {
#if defined(CONFIG_HAVE_CLASSD)
	case AUDIO_DEVICE_CLASSD:
		return classd_transfer_is_done(&desc->device.classd.desc);
#endif
#if defined(CONFIG_HAVE_SSC)
	case AUDIO_DEVICE_SSC:
		break;
#endif
#if defined(CONFIG_HAVE_PDMIC)
	case AUDIO_DEVICE_PDMIC:
		return pdmic_transfer_is_done(&desc->device.pdmic.desc);
#endif
	default:
		if (desc->dma.channel)
			return dma_is_transfer_done(desc->dma.channel);
	}
	return false;
}

void audio_set_dma_callback(struct _audio_desc *desc, audio_callback_t cb, void* arg)
{
	switch (desc->type) {
#if defined(CONFIG_HAVE_CLASSD)
	case AUDIO_DEVICE_CLASSD:
		classd_dma_tx_set_callback(&desc->device.classd.desc, (classd_callback_t)cb, arg);
		break;
#endif
#if defined(CONFIG_HAVE_SSC)
	case AUDIO_DEVICE_SSC:
		break;
#endif
#if defined(CONFIG_HAVE_PDMIC)
	case AUDIO_DEVICE_PDMIC:
		pdmic_dma_set_callback(&desc->device.pdmic.desc, (pdmic_callback_t)cb, arg);
		break;
#endif
	default:
		dma_set_callback(desc->dma.channel, cb, arg);
	}
}

void audio_sync_adjust(struct _audio_desc *desc, int32_t adjust)
{
#if defined(CONFIG_HAVE_SSC)
#if defined(CONFIG_HAVE_AUDIO_WM8904)
	wm8904_sync(&desc->device.ssc.codec->wm8904, adjust);
#endif
#endif
}
