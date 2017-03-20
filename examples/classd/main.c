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

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "audio/classd.h"
#include "board.h"
#include "chip.h"
#include "compiler.h"
#include "dma/dma.h"
#include "gpio/pio.h"
#include "mm/cache.h"
#include "peripherals/pmc.h"
#include "serial/console.h"
#include "timer.h"
#include "trace.h"

#include "music_data.h"

/*----------------------------------------------------------------------------
 *         Local constants
 *----------------------------------------------------------------------------*/

#define INITIAL_ATTENUATION 30

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/


/** ClassD Configuration */
static struct _classd_desc classd_desc = {
	.addr = BOARD_CLASSD0_ADDR,
	.sample_rate = 48000,
	.mode = BOARD_CLASSD0_MODE,
	.non_ovr = CLASSD_NONOVR_10NS,
	.swap_channels = false,
	.mono = BOARD_CLASSD0_MONO,
	.mono_mode = BOARD_CLASSD0_MONO_MODE,
	.left_enable = true,
	.right_enable = true,
	.transfer_mode = CLASSD_MODE_DMA,
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
	printf("1 -> Play the Demo Audio in polling mode\n\r");
	printf("2 -> Play the Demo Audio in DMA mode\n\r");
	printf("3 -> Output Audio PMC Clock to PCK1 IOS2\n\r");
	printf("+ -> Increase the volume (attenuation reduced by 3dB)\n\r");
	printf("- -> Decrease the volume (attenuation increased by 3dB)\n\r");
	printf("=>");
}

static void _set_attenuation(uint8_t attn)
{
	printf("Setting attenuation to -%udB\r\n", (unsigned)attn);
	classd_set_left_attenuation(&classd_desc, attn);
	classd_set_right_attenuation(&classd_desc, attn);
}

static volatile uint32_t start_tick;

static void _playback_start(void)
{
	classd_volume_unmute(&classd_desc, true, true);
	printf("<Playback Start>\r\n");
	start_tick = timer_get_tick();
}

static void _playback_stop(void)
{
	uint32_t elapsed = timer_get_interval(start_tick, timer_get_tick());
	printf("<Playback Stop (%ums elapsed)>\r\n",
			(unsigned)elapsed);
	classd_volume_mute(&classd_desc, true, true);
}

static int _classd_transfer_callback(void* arg, void* arg2)
{
	_playback_stop();

	return 0;
}

/**
 * \brief Play demonstration audio music with DMA/polling.
 */
static void _playback(uint8_t attn, bool dma)
{
	struct _callback _cb;

	_playback_start();

	struct _buffer _tx = {
		.data = (uint8_t*)music_data,
		.size = ARRAY_SIZE(music_data) / sizeof(uint8_t),
		.attr = CLASSD_BUF_ATTR_WRITE,
	};

	if (dma)
		classd_desc.transfer_mode = CLASSD_MODE_DMA;
	else
		classd_desc.transfer_mode = CLASSD_MODE_POLLING;

	callback_set(&_cb, _classd_transfer_callback, &classd_desc);
	classd_transfer(&classd_desc, &_tx, &_cb);

	while (!classd_tx_transfer_is_done(&classd_desc));
}

static void _configure_classd(void)
{
	printf("Configuring ClassD: Full H-Bridge at %uHz\n\r",
			(unsigned)classd_desc.sample_rate);
	if (classd_configure(&classd_desc) == 0) {
		classd_set_equalizer(&classd_desc, CLASSD_EQCFG_FLAT);
		printf("ClassD configured\r\n");
	} else {
		printf("ClassD configuration failed!\r\n");
	}
}

static void _output_audio_pmc_clock_to_pck1(void)
{
	struct _pin pck1_pin = PIN_PCK1_IOS2;
	pio_configure(&pck1_pin, 1);
	pmc_configure_pck(1, PMC_PCK_CSS_AUDIO_CLK, 0);
	pmc_enable_pck(1);
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

	/* output example information */
	console_example_info("CLASSD Example");

	/* configure ClassD */
	_configure_classd();
	_set_attenuation(attn);

	while (1) {
		_display_menu();
		key = console_get_char();
		printf("%c\r\n", key);
		if (key == '1') {
			_playback(attn, false);
		} else if (key == '2') {
			_playback(attn, true);
		} else if (key == '3') {
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
