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
#include "board.h"

#include "peripherals/l2cc.h"
#include "peripherals/pio.h"
#include "peripherals/pit.h"
#include "peripherals/pmc.h"

#include "peripherals/xdmad.h"
#include "peripherals/twi.h"
#include "peripherals/twid.h"
#include "audio_device.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "misc/cache.h"

#if defined(CONFIG_HAVE_CLASSD)
#include "peripherals/classd.h"
#endif

#if defined(CONFIG_HAVE_SSC)
#include "peripherals/ssc.h"
#ifdef CONFIG_HAVE_AUDIO_WM8904
#include "audio/wm8904.h"
#endif
#endif

static struct _xdmad_cfg xdmad_cfg;

static bool dma_configured = false;

/** DMA channel for audio data TX */
static struct _xdmad_channel *audio_dma_tx_channel = NULL;


#if defined(CONFIG_HAVE_CLASSD)
/**
 * Configure the CLASSD for audio output.
 */
static void _configure_classd(struct _audio_desc* desc)
{
	/* Configure Class D */
	struct _classd_desc classd_desc = {
		.sample_rate = desc->sample_rate,
		.mode = BOARD_CLASSD_MODE,
		.non_ovr = CLASSD_NONOVR_10NS,
		.swap_channels = false,
		.mono = BOARD_CLASSD_MONO,
		.mono_mode = BOARD_CLASSD_MONO_MODE
	};
	if(desc->num_channels == 1) {
		classd_desc.left_enable = false;
		classd_desc.right_enable = true;
	}else {
		classd_desc.left_enable = true;
		classd_desc.right_enable = true;
	}
	classd_configure(&classd_desc);
	classd_set_left_attenuation(30);
	classd_set_right_attenuation(30);
	classd_volume_unmute(true, true);
	classd_enable_channels(true, true);
}
#endif

#if defined(CONFIG_HAVE_SSC)
/** SSC instance*/
struct _ssc_desc ssc_dev = {
	.bit_rate = 0,
	.rx_auto_cfg = false,
	.tx_auto_cfg = true,
};
/**
 * Configure the SSC for audio output.
 */
static void _configure_ssc(struct _audio_desc *desc)
{
	/* configure codec clock supply pin */
	pio_configure(desc->device.ssc.codec_chip->clk_pin, 
						desc->device.ssc.codec_chip->clk_pin_size);

	ssc_dev.addr = desc->device.ssc.addr;
	ssc_dev.sample_rate = desc->sample_rate;
	ssc_dev.slot_num = desc->num_channels;
	ssc_dev.slot_length = desc->bits_per_sample;

	ssc_configure(&ssc_dev);
	ssc_disable_transmitter(&ssc_dev);

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

	wm8904_init(desc->device.ssc.codec_chip->codec_twid, WM8904_SLAVE_ADDRESS, PMC_MCKR_CSS_SLOW_CLK);
#endif

	pmc_select_internal_crystal();
	pmc_disable_pck2();
	pmc_configure_pck2(PMC_PCK_CSS_SLOW_CLK, 0);
	pmc_enable_pck2();

	/* Mute */
	audio_play_enable(desc, false);
}

#endif

/**
 *  \brief Start sending next buffer to audio play device using DMA.
 */
static void _audio_dma_start_transfer(void *src_address, void *dest_address, uint16_t size,
										audio_callback_t cb)
{
	if(size)
		cache_clean_region(src_address, size);

	xdmad_cfg.src_addr = (uint32_t*)src_address;
	xdmad_cfg.dest_addr = (uint32_t*)dest_address;

	xdmad_configure_transfer(audio_dma_tx_channel, &xdmad_cfg, 0, 0);
	xdmad_set_callback(audio_dma_tx_channel, cb, NULL);
	xdmad_start_transfer(audio_dma_tx_channel);
}

static void _configure_audio_device(struct _audio_desc *desc)
{
	/* configure PIO muxing for audio play device */
	pio_configure(desc->audio_pin, desc->audio_pin_size);
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
	}
	return ID_PERIPH_COUNT;
}
/**
 * Configure audio play
 */
void audio_play_configure(struct _audio_desc *desc)
{
	uint32_t audio_id = _get_audio_id_from_addr(desc);

	_configure_audio_device(desc);

	/* Allocate DMA TX channels for Audio play device */
	audio_dma_tx_channel = xdmad_allocate_channel(XDMAD_PERIPH_MEMORY, audio_id);
	if (!audio_dma_tx_channel) {
		printf("xDMA channel allocation error\n\r");
	} else {
		xdmad_prepare_channel(audio_dma_tx_channel);
	}
}
/**
 * Enable/Disable audio channels
 */
void audio_play_enable(struct _audio_desc *desc, bool enable)
{
	if (enable) {
		switch (desc->type) {
#if defined(CONFIG_HAVE_CLASSD)
		case AUDIO_DEVICE_CLASSD:
			classd_enable_channels(true, true);
			break;
#endif
#if defined(CONFIG_HAVE_SSC)
		case AUDIO_DEVICE_SSC:
			ssc_enable_transmitter(&ssc_dev);
			break;
#endif
		default:
			return;
		}
	} else {
		switch (desc->type) {
#if defined(CONFIG_HAVE_CLASSD)
		case AUDIO_DEVICE_CLASSD:
			classd_disable_channels(true, true);
			break;
#endif
#if defined(CONFIG_HAVE_SSC)
		case AUDIO_DEVICE_SSC:
			ssc_disable_transmitter(&ssc_dev);
			break;
#endif
		default:
			return;
		}
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
			audio_play_enable(desc, false);
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
			audio_play_enable(desc, true);
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
void audio_play_stop(struct _audio_desc *desc)
{
	if (audio_dma_tx_channel)
		xdmad_stop_transfer(audio_dma_tx_channel);
}

void audio_dma_transfer(struct _audio_desc *desc, void *buffer, uint16_t size,
						audio_callback_t cb)
{
	uint32_t *dest_addr = NULL;
	uint32_t dma_data_width;

	switch (desc->type) {
#if defined(CONFIG_HAVE_CLASSD)
	case AUDIO_DEVICE_CLASSD:
		dest_addr = (uint32_t*)&((desc->device.classd.addr)->CLASSD_THR);
		dma_data_width =  XDMAC_CC_DWIDTH_WORD;
		break;
#endif
#if  defined(CONFIG_HAVE_SSC)
	case AUDIO_DEVICE_SSC:
		dest_addr = (uint32_t*)&((desc->device.ssc.addr)->SSC_THR);
		dma_data_width =  XDMAC_CC_DWIDTH_HALFWORD;
		break;
#endif
	default:
		/* No audio device */
		return;
	}
	if(!dma_configured) {

		xdmad_cfg.cfg.uint32_value = XDMAC_CC_TYPE_PER_TRAN |
			XDMAC_CC_MBSIZE_SINGLE |
			XDMAC_CC_DSYNC_MEM2PER |
			XDMAC_CC_CSIZE_CHK_1 |
			dma_data_width |
			XDMAC_CC_SIF_AHB_IF0 |
			XDMAC_CC_DIF_AHB_IF1 |
			XDMAC_CC_SAM_INCREMENTED_AM |
			XDMAC_CC_DAM_FIXED_AM;

		xdmad_cfg.block_size = 0;
		dma_configured = true;

	}
	if(dma_data_width == XDMAC_CC_DWIDTH_WORD) {
		xdmad_cfg.ublock_size = size / 4;
	} else if(dma_data_width  == XDMAC_CC_DWIDTH_HALFWORD) {
		xdmad_cfg.ublock_size = size / 2;
	}

	if(dest_addr)
		_audio_dma_start_transfer(buffer, (void*)dest_addr, size, cb);
}
