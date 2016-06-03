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
/** \cond usb_audio_speaker
 *  \page usb_audio_speaker USB Audio Speaker Example
 *
 *  \section Purpose
 *
 *  The USB Audio Speaker Example will help you to get familiar with the
 *  USB Device Port(UDP) and CLASSD on SAMA5D2 microcontrollers. Also
 *  it can help you to be familiar with the USB Framework that is used for
 *  rapid development of USB-compliant class drivers such as USB Audio Device
 *  class.
 *
 *  \section Requirements
 *
 *  This package can be used with SAMA5D2-EK and SAMA5D2-XPLAINED that have
 *  both UDP and CLASSD.
 *
 *  \section Description
 *
 *  The demo simulates an USB Desktop Speaker.
 *
 *  When an EK running this program connected to a host (PC for example), with
 *  USB cable, the EK appears as a desktop speaker for the host. Then the host
 *  can play sound through host software. The audio stream from the host is
 *  then sent to the EK, and eventually sent to audio DAC connected to the
 *  amplifier. At the same time, the audio stream received is also sent
 *  back to host from EK for recording.
 *
 *  \section Usage
 *
 *  -# Build the program and download it inside the evaluation board. Please
 *     refer to the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6421.pdf">
 *     SAM-BA User Guide</a>, the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *     GNU-Based Software Development</a> application note or to the
 *     <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *     IAR EWARM User Guide</a>, depending on your chosen solution.
 *  -# On the computer, open and configure a terminal application
 *     (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *    - 115200 bauds
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# Start the application.
 *  -# In the terminal window, the following text should appear:
 *  \code
 *  -- USB Device Audio Speaker Example xxx --
 *  -- SAMxxxxx-xx
 *  -- Compiled: xxx xx xxxx xx:xx:xx --
 *  \endcode
 *  -# When connecting USB cable to windowss, the host
 *     reports a new USB device attachment (if it's the first time you connect
 *     an audio speaker demo board to your host). You can find new
 *     "USB Composite Device" and "USB Audio Device" appear in the hardware
 *     device list.
 *  -# You can play sound in host side through the USB Audio Device, and it
 *     can be heard from the speaker connected to the EK.
 *
 *  \section References
 *  - usb_audio_speaker/main.c
 *  - classd: CLASSD interface driver
 *  - usb: USB Framework, Audio Device Class driver and UDP interface driver
 *      - \ref usbd_framework
 *      - \ref usbd_api
 *      - \ref usbd_audio_speaker
 */

/**
 *  \file
 *
 *  This file contains all the specific code for the
 *  usb_audio_speaker example.
 */

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "board.h"
#include "compiler.h"
#include "trace.h"
#include "timer.h"
#include "wav.h"

#include "peripherals/aic.h"
#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/wdt.h"

#include "compiler.h"

#include "misc/console.h"

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#if defined(CONFIG_BOARD_SAMA5D2_XPLAINED)
	#include "config_sama5d2-xplained.h"
#elif defined(CONFIG_BOARD_SAMA5D4_EK)
	#include "config_sama5d4-ek.h"
#else
#error Unsupported board!
#endif

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

#define SAMPLE_RATE (48000)

/* record 10 seconds */
#define SAMPLE_COUNT (10 * SAMPLE_RATE)


/*----------------------------------------------------------------------------
 *         Internal variables
 *----------------------------------------------------------------------------*/
static uint32_t _start_tick;

SECTION(".region_ddr")
ALIGNED(L1_CACHE_BYTES)
static uint16_t _sound_buffer[ROUND_UP_MULT(SAMPLE_COUNT * sizeof(uint16_t), L1_CACHE_BYTES)];

static volatile bool _sound_recorded = false;

/** audio playing volume */
static uint8_t play_vol = AUDIO_PLAY_MAX_VOLUME/2;

static volatile bool record_done = false;

static volatile bool playback_done = false;
/*----------------------------------------------------------------------------
 *         Internal functions
 *----------------------------------------------------------------------------*/
/**
 *  \brief DMA TX callback
 */
static void audio_play_finish_callback(struct _xdmad_channel *channel, void* p_arg)
{
	p_arg = p_arg; /* dummy */

	playback_done = true;
}

/**
 *  \brief DMA RX callback
 */
static void audio_record_finish_callback(struct _xdmad_channel *channel, void* p_arg)
{
	p_arg = p_arg; /* dummy */

	record_done = true;
}

/**
 * \brief Display main menu.
 */
static void _display_menu(void)
{
	printf("\n\r");
	printf("Select an option:\n\r");
	printf("-----------------\n\r");
	printf("R -> Record the sound \n\r");
	printf("P -> Playback the record sound \n\r");
	printf("+ -> Increase the volume of playback sound \n\r");
	printf("- -> Decrease the volume of playback sound \n\r");
	printf("=>");
}

static void _record_start(void)
{
	printf("<Record Start>\r\n");
	_start_tick = timer_get_tick();
	_sound_recorded = false;
	audio_enable(&audio_record_device, true);
}

static void _record_stop(void)
{
	uint32_t elapsed = timer_get_interval(_start_tick, timer_get_tick());
	printf("<Record Stop (%ums elapsed)>\r\n", (unsigned)elapsed);
	_sound_recorded = true;
	audio_enable(&audio_record_device, false);
}

static void _play_start(void)
{
	printf("<Play Start>\r\n");
	_start_tick = timer_get_tick();
	audio_enable(&audio_play_device, true);
}

static void _play_stop(void)
{
	uint32_t elapsed = timer_get_interval(_start_tick, timer_get_tick());
	printf("<Play Stop (%ums elapsed)>\r\n", (unsigned)elapsed);
	audio_enable(&audio_play_device, false);
}

/**
 * \brief Record sound.
 */
static void _record_sound(void)
{
	uint32_t  audio_length = SAMPLE_COUNT * 2;

	_record_start();
	audio_dma_transfer(&audio_record_device, (void *)_sound_buffer, audio_length,
					   audio_record_finish_callback);
	while (!record_done);
	_record_stop();
	record_done = false;
}


/**
 * \brief Playback recorded sound.
 */
static void _playback_sound(void)
{
	/* our Classd support 16 bit sound only*/
	uint32_t  audio_length = SAMPLE_COUNT * 2;	

	if (!_sound_recorded) {
	       printf("Please record the sound first\n\r");
	       return;
	}

	audio_play_mute(&audio_play_device, false);
	_play_start();

	audio_dma_transfer(&audio_play_device, (void *)_sound_buffer, audio_length,
						audio_play_finish_callback);

	while (!playback_done);
	_play_stop();
	playback_done = false;
	audio_play_mute(&audio_play_device, true);
}


/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief usb_audio_speaker Application entry point.
 *
 *  Starts the driver and waits for an audio input stream to forward to the DAC.
 */
extern int main(void)
{
	uint8_t key;

	/* output example information */
	console_example_info("Audio Recorder Example");
	
	/* Configure Audio play*/
	audio_configure(&audio_play_device);

	/* Configure Audio record */
	audio_configure(&audio_record_device);

	/* Configure audio play volume */
	audio_play_set_volume(&audio_play_device, play_vol);

	/* Infinite loop */
	while (1) {
		_display_menu();
		key = console_get_char();
		printf("%c\r\n", key);

		if (key == 'r' || key == 'R')
			_record_sound();
		else if (key == 'p' || key == 'P')
			_playback_sound();
		else if (key == '+') {
			if (play_vol < AUDIO_PLAY_MAX_VOLUME) {
				play_vol += 10;
				audio_play_set_volume(&audio_play_device, play_vol);
			}
		} else if (key == '-') {
			if (play_vol > 10) {
				play_vol -= 10;
				audio_play_set_volume(&audio_play_device, play_vol);
			}
		} 
	}
}
