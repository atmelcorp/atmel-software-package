/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
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

/**
 * \page  CLASSD Example
 *
 * \section Purpose
 *
 * The CLASSD example will help new users get familiar with Atmel's
 * SAMA5D2X family of microcontrollers. This basic application shows the
 * usage of CLASSD and can play the demonstration music with speaker.
 *
 * \section Requirements
 *
 * This package can be used with SAMA5D2-EK and SAMA5D2-XPLAINED.
 *
 * \section Description
 *
 * The demonstration program evaluates the CLASSD parameter set. The process
 * of CLASSD parameter set can be switched by the corresponding buttons.
 *
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board. Please
 *    refer to the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *    SAM-BA User Guide</a>, the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *    GNU-Based Software Development</a>
 *    application note or to the
 *    <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *    IAR EWARM User Guide</a>,
 *    depending on your chosen solution.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *     \code
 *      -- CLASSD Example xxx --
 *      -- SAMxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 * -# Connect the speaker to the A5D2 board first;
 * -# the demo audio music in softpack is 48K frame, 16bit and 2 channels;
 * -# Press one of the keys listed in the menu to perform the corresponding action;
 * -# Press key '1' to display the demo audio information, than press key '2' to
 * -# set the corresponding parameters to the Classd, press key '3' or key '4' to
 * -# increase or decrease the volume, at last press key '5' to play the music
 * -# without DMA or key '6' to play the music wit DMA.
 * \section References
 * - classd/main.c
 * - classd.h
 * - classd.c
 */

/** \file
 *
 *  This file contains all the specific code for the CLASSD example.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "board.h"
#include "compiler.h"
#include "trace.h"
#include "timer.h"
#include "wav.h"

#include "peripherals/aic.h"
#include "peripherals/classd.h"
#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/wdt.h"
#include "peripherals/xdmad.h"

#include "misc/console.h"

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "music_data.h"

/*----------------------------------------------------------------------------
 *         Local constants
 *----------------------------------------------------------------------------*/

#define INITIAL_ATTENUATION 30

static const struct _pin classd_pins[] = BOARD_CLASSD_PINS;

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** DMA channel for TX */
static struct _xdmad_channel*  dma_channel;

/** ClassD Configuration */
static struct _classd_desc classd_desc = {
	.sample_rate = 48000,
	.mode = BOARD_CLASSD_MODE,
	.non_ovr = CLASSD_NONOVR_10NS,
	.swap_channels = false,
	.mono = BOARD_CLASSD_MONO,
	.mono_mode = BOARD_CLASSD_MONO_MODE,
	.left_enable = true,
	.right_enable = true,
};

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Display main menu.
 */
static void _display_menu(void)
{
	printf("\n\r");
	printf("Select an option:\n\r");
	printf("-----------------\n\r");
	printf("1 -> Display Demo Audio Information \n\r");
	printf("2 -> Play the Demo Audio without DMA\n\r");
	printf("3 -> Play the Demo Audio with DMA\n\r");
	printf("4 -> Output Audio PMC Clock to PCK1 IOS2\n\r");
	printf("+ -> Increase the volume (attenuation reduced by 3dB)\n\r");
	printf("- -> Decrease the volume (attenuation increased by 3dB)\n\r");
	printf("=>");
}

/**
 * \brief Display demonstration audio music information.
 */
static void _display_audio_info(const struct _wav_header *audio_data)
{
	if (audio_data && wav_is_valid(audio_data)) {
		wav_display_info(audio_data);
	}
}

static void _set_attenuation(uint8_t attn)
{
	printf("Setting attenuation to -%udB\r\n", (unsigned)attn);
	classd_set_left_attenuation(attn);
	classd_set_right_attenuation(attn);
}

static volatile uint32_t start_tick;

static void _playback_start(void)
{
	classd_volume_unmute(true, true);
	printf("<Playback Start>\r\n");
	start_tick = timer_get_tick();
}

static void _playback_stop(void)
{
	uint32_t elapsed = timer_get_interval(start_tick, timer_get_tick());
	printf("<Playback Stop (%ums elapsed)>\r\n",
			(unsigned)elapsed);
	classd_volume_mute(true, true);
}

/**
 * \brief DMA driver configuration
 */
static void _initialize_dma(void)
{
	/* Driver initialize */
	xdmad_initialize(false);

	/* Allocate DMA TX channels for CLASSD */
	dma_channel = xdmad_allocate_channel(XDMAD_PERIPH_MEMORY, ID_CLASSD);
	if (dma_channel)
	{
		printf("DMA channel allocated\n\r");
		xdmad_prepare_channel(dma_channel);
	} else {
		printf("DMA channel allocation error\n\r");
	}
}

/**
 *  \brief Configure DMA transfer
 */
static void _setup_dma_transfer(void* buffer, uint32_t size)
{
	struct _xdmad_cfg cfg;

	cfg.ublock_size = size / 4;
	cfg.block_size = 1;
	cfg.data_stride = 0;
	cfg.src_ublock_stride = 0;
	cfg.dest_ublock_stride = 0;
	cfg.src_addr = buffer;
	cfg.dest_addr = (void*)&CLASSD->CLASSD_THR;
	cfg.cfg.uint32_value = XDMAC_CC_TYPE_PER_TRAN
		| XDMAC_CC_MBSIZE_SINGLE
		| XDMAC_CC_DSYNC_MEM2PER
		| XDMAC_CC_CSIZE_CHK_1
		| XDMAC_CC_DWIDTH_WORD
		| XDMAC_CC_SIF_AHB_IF0
		| XDMAC_CC_DIF_AHB_IF1
		| XDMAC_CC_SAM_INCREMENTED_AM
		| XDMAC_CC_DAM_FIXED_AM;

	xdmad_configure_transfer(dma_channel, &cfg, 0, NULL);
}

/**
 *  \brief DMA callback
 */
static void _dma_callback(struct _xdmad_channel *channel, void* arg)
{
	bool *done = arg;
	if (xdmad_is_transfer_done(channel))
		*done = true;
}

/**
 * \brief Play demonstration audio music with DMA.
 */
static void _playback_with_dma(uint8_t attn)
{
	uint32_t* audio = (uint32_t*)(music_data + sizeof(struct _wav_header));
	uint32_t  audio_length = ((struct _wav_header*)music_data)->subchunk2_size;
	volatile bool done = false;

	_playback_start();
	_setup_dma_transfer(audio, audio_length);
	xdmad_set_callback(dma_channel, _dma_callback, &done);
	xdmad_start_transfer(dma_channel);
	while (!done);
	_playback_stop();
}


/**
 * \brief Play demonstration audio music without DMA.
 */
static void _playback_without_dma(uint8_t attn)
{
	uint32_t* audio = (uint32_t*)(music_data + sizeof(struct _wav_header));
	uint32_t  audio_length = ((struct _wav_header*)music_data)->subchunk2_size;
	uint32_t* audio_end = audio + audio_length / 4;

	_playback_start();
	while (1) {
		if (CLASSD->CLASSD_ISR & CLASSD_ISR_DATRDY) {
			CLASSD->CLASSD_THR = *audio;
			audio++;
		}
		if (audio > audio_end)
			break;
	}
	_playback_stop();

}

static void _configure_classd(void)
{
	classd_desc.sample_rate = ((struct _wav_header*)music_data)->sample_rate;
	printf("Configuring ClassD: Full H-Bridge at %uHz\n\r",
			(unsigned)classd_desc.sample_rate);
	if (classd_configure(&classd_desc)) {
		classd_set_equalizer(CLASSD_EQCFG_FLAT);
		printf("ClassD configured\r\n");
	} else {
		printf("ClassD configuration failed!\r\n");
	}
}

static void _output_audio_pmc_clock_to_pck1(void)
{
	struct _pin pck1_pins[] = PINS_PCK1_IOS2;
	pio_configure(pck1_pins, ARRAY_SIZE(pck1_pins));
	pmc_configure_pck1(PMC_PCK_CSS_AUDIO_CLK, 0);
	pmc_enable_pck1();
}

/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief classd Application entry point
 *  \return Unused (ANSI-C compatibility)
 */
extern int main(void)
{
	uint8_t key;
	uint8_t attn = INITIAL_ATTENUATION;

	/* disable watchdog */
	wdt_disable();

	/* configure console */
	board_cfg_console();

	/* output example information */
	printf("-- CLASSD Example " SOFTPACK_VERSION " --\n\r");
	printf("-- " BOARD_NAME "\n\r");
	printf("-- Compiled: " __DATE__ " " __TIME__ " --\n\r");

	/* configure PIO muxing for ClassD */
	pio_configure(classd_pins, ARRAY_SIZE(classd_pins));

	/* initialize ClassD DMA channel */
	_initialize_dma();

	/* configure ClassD */
	_configure_classd();
	_set_attenuation(attn);

	while (1) {
		_display_menu();
		key = console_get_char();
		printf("%c\r\n", key);
		if (key == '1') {
			_display_audio_info((const struct _wav_header *)music_data);
		} else if (key == '2') {
			_playback_without_dma(attn);
		} else if (key == '3') {
			_playback_with_dma(attn);
		} else if (key == '4') {
			_output_audio_pmc_clock_to_pck1();
		} else if (key == '+') {
			if (attn > 1) {
				attn -= 3;
				_set_attenuation(attn);
			} else {
				printf("Attenuation is already at min (-1dB)\r\n");
			}
		} else if (key == '-') {
			if (attn < 76) {
				attn += 3;
				_set_attenuation(attn);
			} else {
				printf("Attenuation is already at max (-76dB)\r\n");
			}
		}
	}
}
