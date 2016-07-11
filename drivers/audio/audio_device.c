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

#include "chip.h"

#include "peripherals/l2cc.h"
#include "peripherals/pio.h"
#include "peripherals/pit.h"
#include "peripherals/pmc.h"

#include "peripherals/dma.h"
#include "peripherals/twi.h"
#include "peripherals/twid.h"
#include "audio_device.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "misc/cache.h"

#if defined(CONFIG_HAVE_CLASSD)
/**
 * Configure the CLASSD for audio output.
 */
static void _configure_classd(struct _audio_desc* desc)
{
	/* Configure Class D */
	if(desc->num_channels == 1) {
		desc->device.classd.desc.swap_channels = true,
		desc->device.classd.desc.left_enable = false;
		desc->device.classd.desc.right_enable = true;
	} else {
		desc->device.classd.desc.swap_channels = false;
		desc->device.classd.desc.left_enable = true;
		desc->device.classd.desc.right_enable = true;
	}
	classd_configure(&desc->device.classd.desc);
	classd_set_left_attenuation(30);
	classd_set_right_attenuation(30);
	classd_volume_unmute(true, true);
	classd_enable_channels(true, true);
}
#endif

#if defined(CONFIG_HAVE_SSC)
/**
 * Configure the SSC for audio output.
 */
static void _configure_ssc(struct _audio_desc *desc)
{
	/* configure codec clock supply pin */
	pio_configure(desc->device.ssc.codec_chip->clk_pin, 
						desc->device.ssc.codec_chip->clk_pin_size);

	desc->device.ssc.desc.addr = desc->device.ssc.addr;
	desc->device.ssc.desc.sample_rate = desc->sample_rate;
	desc->device.ssc.desc.slot_num = desc->num_channels;
	desc->device.ssc.desc.slot_length = desc->bits_per_sample;

	ssc_configure(&desc->device.ssc.desc);
	ssc_disable_transmitter(&desc->device.ssc.desc);
	ssc_disable_receiver(&desc->device.ssc.desc);

#ifdef CONFIG_HAVE_AUDIO_WM8904
	/* Configure TWI pins. */
	pio_configure(desc->device.ssc.codec_chip->codec_twid_pin, 
						desc->device.ssc.codec_chip->codec_twid_pin_size);

	/* -- WM8904 Initialize -- */
	twid_configure(desc->device.ssc.codec_chip->codec_twid);
	/* check that WM8904 is present */
	wm8904_write(desc->device.ssc.codec_chip->codec_twid, WM8904_SLAVE_ADDRESS, 22, 0);

	wm8904_write(desc->device.ssc.codec_chip->codec_twid, WM8904_SLAVE_ADDRESS, WM8904_REG_RESET, 0);
	/* WM8904 as master */
	if(wm8904_read(desc->device.ssc.codec_chip->codec_twid, WM8904_SLAVE_ADDRESS, 0)!=0x8904){
		printf("WM8904 not found!\n\r");
		while(1);
	}

	wm8904_init(desc->device.ssc.codec_chip->codec_twid,
				WM8904_SLAVE_ADDRESS,
				PMC_MCKR_CSS_SLOW_CLK,
				desc->device.ssc.codec_chip->input_path);
#endif

	pmc_select_internal_crystal();
	pmc_disable_pck(desc->device.ssc.pck);
	pmc_configure_pck(desc->device.ssc.pck, PMC_PCK_CSS_SLOW_CLK, 0);
	pmc_enable_pck(desc->device.ssc.pck);

	/* Mute */
	audio_enable(desc, false);
}

#endif

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
		return ID_PDMIC;
#endif
	}
	return ID_PERIPH_COUNT;
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
				classd_enable_channels(true, true);
			else
				classd_disable_channels(true, true);
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
			break;;
		}
		break;
#endif
#if defined(CONFIG_HAVE_PDMIC)
	case AUDIO_DEVICE_PDMIC:
		switch (desc->direction) {
		case AUDIO_DEVICE_PLAY:
			return;
		case AUDIO_DEVICE_RECORD:
			pdmic_stream_convert(enable);
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
			classd_volume_mute(true, true);
			break;
#endif
#if defined(CONFIG_HAVE_SSC)
		case AUDIO_DEVICE_SSC:
#ifdef CONFIG_HAVE_AUDIO_WM8904
			wm8904_volume_mute(desc->device.ssc.codec_chip->codec_twid,
							WM8904_SLAVE_ADDRESS, true, true);
#endif
			break;
#endif
		default:
			return;
		}
	} else {
		switch (desc->type) {
#if defined(CONFIG_HAVE_CLASSD)
		case AUDIO_DEVICE_CLASSD:
			classd_volume_unmute(true, true);
			break;
#endif
#if defined(CONFIG_HAVE_SSC)
		case AUDIO_DEVICE_SSC:
#ifdef CONFIG_HAVE_AUDIO_WM8904
			wm8904_volume_mute(desc->device.ssc.codec_chip->codec_twid,
							WM8904_SLAVE_ADDRESS, false, false);
#endif
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
			val = (AUDIO_PLAY_MAX_VOLUME-vol)*77/AUDIO_PLAY_MAX_VOLUME;
			classd_set_left_attenuation(val);
			classd_set_right_attenuation(val);
			break;
#endif

#if defined(CONFIG_HAVE_SSC)
		case AUDIO_DEVICE_SSC:
#ifdef CONFIG_HAVE_AUDIO_WM8904
			/* wm8904 heardphone output volume range -57db~6db */
			val = (vol*63)/AUDIO_PLAY_MAX_VOLUME;
			wm8904_set_left_volume(desc->device.ssc.codec_chip->codec_twid,
							WM8904_SLAVE_ADDRESS, val);
			wm8904_set_right_volume(desc->device.ssc.codec_chip->codec_twid,
							WM8904_SLAVE_ADDRESS, val);
#endif
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
	if (desc->dma.channel)
		dma_stop_transfer(desc->dma.channel);
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
		case AUDIO_DEVICE_PLAY:
			src_addr = buffer;
			dst_addr = (uint32_t*)&((desc->device.classd.addr)->CLASSD_THR);
			desc->dma.cfg.upd_sa_per_data = 1;
			desc->dma.cfg.upd_da_per_data = 0;
			if(desc->num_channels > 1)
				dma_data_width =  DMA_DATA_WIDTH_WORD;
			break;
		case AUDIO_DEVICE_RECORD:
			/* Do not supported */
			return;
		}
		break;
#endif
#if  defined(CONFIG_HAVE_SSC)
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

		case AUDIO_DEVICE_RECORD:
			pdmic_dma_transfer(buffer, size, cb, NULL);
			return;
		}
		break;
#endif

	default:
		/* No audio device */
		return;
	}

	if (!desc->dma.configured) {
		desc->dma.cfg.chunk_size = DMA_CHUNK_SIZE_1;
		desc->dma.cfg.data_width = dma_data_width;
		desc->dma.cfg.blk_size = 0;
		desc->dma.configured = true;
	}
	if (dma_data_width == DMA_DATA_WIDTH_WORD) {
		desc->dma.cfg.len = size / 4;
	} else if (dma_data_width  == DMA_DATA_WIDTH_HALF_WORD) {
		desc->dma.cfg.len = size / 2;
	}

	if (dst_addr)
		_audio_dma_start_transfer(desc, src_addr, (void*)dst_addr, size, cb);
}

bool audio_dma_transfer_is_done(struct _audio_desc *desc)
{
	if (desc->dma.channel)
		return dma_is_transfer_done(desc->dma.channel);
	return false;
}

void audio_set_dma_callback(struct _audio_desc *desc, audio_callback_t cb, void* arg)
{
	dma_set_callback(desc->dma.channel, cb, arg);
}

void audio_sync_adjust(struct _audio_desc *desc, int32_t adjust)
{
#if defined(CONFIG_HAVE_SSC)
#if defined(CONFIG_HAVE_AUDIO_WM8904)
	if (adjust > 0) {
		/* Fractional multiply for FLL_K, Fref = 0x8000 (1/2) */
		wm8904_write(desc->device.ssc.codec_chip->codec_twid,  WM8904_SLAVE_ADDRESS, WM8904_REG_FLL_CRTL3, 0xFF00);
	} else if (adjust < 0) {
		/* Fractional multiply for FLL_K, Fref = 0x8000 (1/2) */
		wm8904_write(desc->device.ssc.codec_chip->codec_twid,  WM8904_SLAVE_ADDRESS, WM8904_REG_FLL_CRTL3, 0x5000);
	} else {
		/* Default: 32K -> 48K*256, FLL: 32768*187.5/16/8 */
		/* FLL_FRATIO=4 (/16), FLL_OUTDIV= 7 (/8) */
		/* Fractional multiply for FLL_K, Fref = 0x8000 (1/2) */
		wm8904_write(desc->device.ssc.codec_chip->codec_twid, WM8904_SLAVE_ADDRESS, WM8904_REG_FLL_CRTL3,
				 0x8000 + 0x3000);
	}
	return;
#endif
#endif
}
