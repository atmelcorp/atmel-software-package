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

/**
 * \page ssc_dma_audio SSC with DMA Audio Example
 *
 * \section Purpose
 *
 * This example uses the Synchronous Serial Controller (SSC) of SAMA5D3/4
 * and SAM9XX5 microcontroller to output an audio stream through the on-board
 * WM8904/WM8731 CODEC.
 *
 * \section Requirements
 *
 * \section Description
 * This program plays a WAV file from PC via Line-In. The audio stream is
 * sent through the SSC interface connected to the on-board audio codec, enabling
 * the sound to be audible using a pair of headphones.
 *
 * \section Usage
 * -# Build the program and download it inside the evaluation board. Please
 *    refer to the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *    SAM-BA User Guide</a>, the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *    GNU-Based Software Development</a> application note or to the
 *    <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *    IAR EWARM User Guide</a>, depending on your chosen solution.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *    \code
 *     -- SSC DMA Audio Example xxx --
 *      -- SAMxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *    \endcode
 * The user can then choose any of the available options to perform the described action.
 *
 * \section References
 * - ssc_dma_audio/main.c
 * - ssc.c
 * - wm8904.c
 * - wm8731.c
 * - dma.c
 */

/**
 * \file
 *
 * This file contains all the specific code for the ssc audio example.
 */


/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "audio/ssc.h"
#if defined(CONFIG_HAVE_AUDIO_WM8904)
#include "audio/wm8904.h"
#elif defined(CONFIG_HAVE_AUDIO_WM8731)
#include "audio/wm8731.h"
#endif
#include "board.h"
#include "chip.h"
#include "compiler.h"
#include "dma/dma.h"
#include "gpio/pio.h"
#include "led/led.h"
#include "mm/cache.h"
#include "peripherals/pit.h"
#include "peripherals/pmc.h"
#include "serial/console.h"
#include "timer.h"
#include "trace.h"

#if defined(CONFIG_BOARD_SAMA5D3_EK)
	#include "config_sama5d3-ek.h"
#elif defined(CONFIG_BOARD_SAMA5D4_EK)
	#include "config_sama5d4-ek.h"
#elif defined(CONFIG_BOARD_SAM9G15_EK)
	#include "config_sam9xx5-ek.h"
#elif defined(CONFIG_BOARD_SAM9G25_EK)
	#include "config_sam9xx5-ek.h"
#elif defined(CONFIG_BOARD_SAM9G35_EK)
	#include "config_sam9xx5-ek.h"
#elif defined(CONFIG_BOARD_SAM9X25_EK)
	#include "config_sam9xx5-ek.h"
#elif defined(CONFIG_BOARD_SAM9X35_EK)
	#include "config_sam9xx5-ek.h"
#elif defined(CONFIG_BOARD_SAMV71_XPLAINED)
	#include "config_samv71-xplained.h"
#else
#error Unsupported board!
#endif

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

#define BUFFERS (32)

#define BUFFER_SIZE ROUND_UP_MULT(192, L1_CACHE_BYTES)

#define BUFFER_THRESHOLD (8)

/*----------------------------------------------------------------------------
 *         Internal variables
 *----------------------------------------------------------------------------*/

/** Audio record buffer */
CACHE_ALIGNED_DDR static uint16_t _sound_buffer[BUFFERS][BUFFER_SIZE];

static struct _audio_ctx {
	uint32_t threshold;
	struct {
		uint16_t rx;
		uint16_t tx;
		uint32_t count;
	} circ;
	uint8_t volume;
	bool playing;
	bool recording;
} _audio_ctx = {
	.threshold = BUFFER_THRESHOLD,
	.circ = {
		.rx = 0,
		.tx = 0,
		.count = 0,
	},
	.volume = 30,
	.recording = false,
	.playing = false,
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
	printf("-----------------\n\r");
	printf("R -> Start to record the sound and play \n\r");
	printf("S -> Stop recording sound \n\r");
	printf("+ -> Increase the volume of playback sound \n\r");
	printf("- -> Decrease the volume of playback sound \n\r");
	printf("-----------------\n\r");
}


/**
 *  \brief Audio RX callback
 */
static int _ssc_tx_transfer_callback(void* arg, void* arg2)
{
	struct _ssc_desc* desc = (struct _ssc_desc*)arg;
	struct _callback _cb;

	if (_audio_ctx.playing && (_audio_ctx.circ.count > 0)){
		struct _buffer _tx = {
			.data = (unsigned char*)&_sound_buffer[_audio_ctx.circ.tx],
			.size = BUFFER_SIZE,
			.attr = SSC_BUF_ATTR_WRITE,
		};

		callback_set(&_cb, _ssc_tx_transfer_callback, desc);
		ssc_transfer(desc, &_tx, &_cb);
		_audio_ctx.circ.tx = (_audio_ctx.circ.tx + 1) % BUFFERS;
		_audio_ctx.circ.count--;

		if (_audio_ctx.circ.count == 0) {
			ssc_disable_transmitter(&ssc_dev_desc);

			_audio_ctx.playing = false;
		}
	}

	return 0;
}

/**
 *  \brief Audio RX callback
 */
static int _ssc_rx_transfer_callback(void* arg, void* arg2)
{
	struct _ssc_desc* desc = (struct _ssc_desc*)arg;
	struct _callback _cb;

	/* New buffer received */
	_audio_ctx.circ.rx = (_audio_ctx.circ.rx + 1) % BUFFERS;
	_audio_ctx.circ.count++;

	if (!_audio_ctx.playing && (_audio_ctx.circ.count > _audio_ctx.threshold)) {
		_audio_ctx.playing = true;
		ssc_enable_transmitter(&ssc_dev_desc);
		_ssc_tx_transfer_callback(desc, NULL);
	}

	struct _buffer _rx = {
		.data = (unsigned char*)&_sound_buffer[_audio_ctx.circ.rx],
		.size = BUFFER_SIZE,
		.attr = SSC_BUF_ATTR_READ,
	};

	callback_set(&_cb, _ssc_rx_transfer_callback, desc);
	ssc_transfer(desc, &_rx, &_cb);

	return 0;
}

/**
 * \brief Play recording.
 */

static void _set_volume(uint8_t vol)
{
#if defined(CONFIG_HAVE_AUDIO_WM8904)
	printf("Setting volume to %ddB\r\n", (signed)(vol-57));
	wm8904_set_left_volume(&wm8904, vol);
	wm8904_set_right_volume(&wm8904, vol);
#elif defined(CONFIG_HAVE_AUDIO_WM8731)
	printf("Setting volume to %ddB\r\n", (signed)(vol-73));
	wm8731_set_left_volume(&wm8731, vol);
	wm8731_set_right_volume(&wm8731, vol);
#endif
}

static void console_handler(uint8_t key)
{
	switch (key) {
	case '+':
		if (_audio_ctx.volume < 63) {
			_audio_ctx.volume += 3;
			_set_volume(_audio_ctx.volume);
		}
		break;
	case '-':
		if (_audio_ctx.volume > 1) {
			_audio_ctx.volume -= 3;
			_set_volume(_audio_ctx.volume);
		}
		break;

	case 'R':
	case 'r':
		_audio_ctx.recording = true;
		ssc_enable_receiver(&ssc_dev_desc);

		{ /* Start recording */
			struct _callback _cb;
			callback_set(&_cb, _ssc_rx_transfer_callback, &ssc_dev_desc);
			struct _buffer _rx = {
				.data = (unsigned char*)&_sound_buffer[_audio_ctx.circ.rx],
				.size = BUFFER_SIZE,
				.attr = SSC_BUF_ATTR_READ,
			};

			ssc_transfer(&ssc_dev_desc, &_rx, &_cb);
		}

		printf("SSC start to record and play sound\r\n");
		break;

	case 'S':
	case 's':
		_audio_ctx.recording = false;
		ssc_disable_transmitter(&ssc_dev_desc);
		ssc_disable_receiver(&ssc_dev_desc);
		printf("SSC stop to record and play sound\r\n");
		break;

	default:
		break;
	}
}

/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Application entry point for tc_capture_waveform example.
 *
 * \return Unused (ANSI-C compatibility).
 */
extern int main( void )
{
	/* Output example information */
	console_example_info("SSC DMA Audio Example");

	console_set_rx_handler(console_handler);
	console_enable_rx_interrupt();

	/* Configure SSC */
	ssc_configure(&ssc_dev_desc);

	ssc_disable_receiver(&ssc_dev_desc);
	ssc_disable_transmitter(&ssc_dev_desc);

	/* Initialize the audio DAC */
#if defined(CONFIG_HAVE_AUDIO_WM8904)
	wm8904_configure(&wm8904);
#elif defined(CONFIG_HAVE_AUDIO_WM8731)
	wm8731_configure(&wm8731);
#endif

	_set_volume(_audio_ctx.volume);

	_display_menu();

	/* Infinite loop */
	while (1);
}
