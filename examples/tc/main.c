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
 * \page tc_capture_waveform TC Capture Waveform Example
 *
 * \section Purpose
 *
 * This example indicates how to use TC in capture mode to measure the pulse
 * frequency and count the total pulse number of an external signal injected
 * on TIOA pin.
 *
 * \section Requirements
 *
 * This package can be used with SAMA5D2, SAMA5D3, SAMA5D3, SAM9XX5 and SAMV71
 * targets.
 * A jumper cable must connected between the TC Waveform pin and the TC capture
 * pin, please read README.md for information.
 *
 * \section Descriptions
 *
 * This example shows how to configure TC in waveform and capture mode.
 * In capture mode, pulse signal is set as an input, RA and RB will be loaded when
 * programmed event occurs. When TC interrupt happens, we could read RA and RB
 * value for calculating pulse frequency and pulse number be increased. The current
 * pulse frequency and total pulse number is output on DBGU.
 *
 * The code can be roughly broken down as follows:
 * <ul>
 * <li>Select pre-defined waveform frequency and duty cycle to be generated.
 * <li>Configure TC channel 1 as waveform output.
 * <li>Configure TC channel 2 as capture input.
 * <li>Configure capture Register A be loaded when rising edge of TIOA occurs.
 * <li>Configure capture Register B be loaded when failing edge of TIOA occurs.
 * <li>Configure an interrupt for TC and enable the RB load interrupt.
 * <li> 'c' start capture.
 * <li> 's' will stop capture,and dump the informations what have been captured.
 * </ul>
 *
 * \section Usage
 *
 * -# Compile the application and connect the DBGU port of the evaluation board
 *    to the computer.
 * -# Open and configure a terminal application on PC
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Download the program inside the evaluation board and run it. Please refer to
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *    SAM-BA User Guide</a>, the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *    GNU-Based Software Development</a> application note or to the
 *    <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *    IAR EWARM User Guide</a>, depending on your chosen solution.
 * -# Upon startup, the application will output the following line on the DBGU:
 *    \code
 *     -- TC Capture Waveform Example  xxx --
 *     -- SAMxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *    \endcode
 * -# Choose the item in the following menu to test.
 *    \code
 *     Menu :
 *     ------
 *       Output waveform property:
 *       0: Set Frequency =  80 Hz, Duty Cycle = 30%
 *       1: Set Frequency =  180 Hz, Duty Cycle = 50%
 *       2: Set Frequency =  400 Hz, Duty Cycle = 75%
 *       3: Set Frequency =  500 Hz, Duty Cycle = 80%
 *       4: Set Frequency = 2000 Hz, Duty Cycle = 55%
 *       -------------------------------------------
 *       c: Capture waveform from TC capture channel
 *       s: Stop capture and display informations what have been captured
 *       h: Display menu
 *     ------
 *    \endcode
 *
 * \section References
 * - tc_capture_waveform/main.c
 */

/**
 * \file
 *
 * This file contains all the specific code for the tc capture waveform example.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "board.h"
#include "callback.h"
#include "chip.h"
#include "compiler.h"
#include "dma/dma.h"
#include "gpio/pio.h"
#include "irq/irq.h"
#include "mm/cache.h"
#include "peripherals/pmc.h"
#include "peripherals/tc.h"
#include "peripherals/tcd.h"
#include "serial/console.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#if defined(CONFIG_BOARD_SAMA5D2_XPLAINED)
	#include "config_sama5d2-xplained.h"
#elif defined(CONFIG_BOARD_SAMA5D4_EK)
	#include "config_sama5d4-ek.h"
#elif defined(CONFIG_BOARD_SAMA5D4_XPLAINED)
	#include "config_sama5d4-xplained.h"
#elif defined(CONFIG_BOARD_SAMA5D3_EK)
	#include "config_sama5d3-ek.h"
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
#elif defined(CONFIG_BOARD_SAME70_XPLAINED)
	#include "config_same70-xplained.h"
#elif defined(CONFIG_BOARD_SAMV71_XPLAINED)
	#include "config_samv71-xplained.h"
#else
	#error Unsupported board!
#endif

#define CAPTURE_FREQ  100000 /* 100 KHz */
#define CAPTURE_COUNT     50
#define COUNTER_FREQ    1000

/** Describes a possible Timer configuration as waveform mode */
struct _waveform {
	uint32_t min_timer_freq;
	uint32_t frequency;       /** Waveform frequency (in Hz). */
	uint32_t duty_cycle;      /** Duty cycle in percent (positive). */
};

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** PIOs for TC capture, waveform */
static const struct _pin pins_tc[] = { PIN_TC_CAPTURE_IN, PIN_TC_WAVEFORM_OUT };

/** define Timer Counter descriptor for counter/timer */
static struct _tcd_desc tc_counter = {
	.addr = EXAMPLE_TC,
	.channel = EXAMPLE_TC_CHANNEL_COUNTER,
};

/** define Timer Counter descriptor for capture */
static struct _tcd_desc tc_capture = {
	.addr = TC0,
	.channel = EXAMPLE_TC_CHANNEL_CAPTURE_IN,
	.cfg = {
		.capture = {
			.use_ext_clk = false,
			.transfer_mode = TCD_TRANSFER_MODE_POLLING,
		},
	},
};

/** define Timer Counter descriptor for waveform */
static struct _tcd_desc tc_waveform = {
	.addr = EXAMPLE_TC,
	.channel = EXAMPLE_TC_CHANNEL_WAVEFORM_OUT,
};

/** TC waveform configurations (base on 66MHz peripheral clock)*/
static const struct _waveform waveforms[] = {
	{ 100000, 80, 30 },
	{ 100000, 180, 50 },
	{ 100000, 400, 75 },
	{ 100000, 500, 80 },
	{ 100000, 2000, 55 },
	{ 100000, 5000, 20 },
};

CACHE_ALIGNED static uint32_t capture_buf[CAPTURE_COUNT * 2];

static uint32_t _tick = 0;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static int _tc_capture_callback(void* arg, void* arg2)
{
	tcd_stop(&tc_capture);
	printf("TC: Waveform captured...\r\n");
	return 0;
}

static int _tc_counter_callback(void* arg, void* arg2)
{
	_tick++;

	if (_tick % 10000 == 0)
		printf("time: %us\r\n", (unsigned)_tick / 1000);
	return 0;
}

/**
 * \brief Displays the user menu.
 */
static void _display_menu(void)
{
	uint32_t i;

	printf("\r\nMenu :\r\n");
	printf("------\r\n");
	printf("  Output waveform property:\r\n");
	for (i = 0; i < ARRAY_SIZE(waveforms); i++) {
		printf("  %u: Set Frequency = %4u Hz, Duty Cycle = %2u%%\r\n",
			(unsigned)i,
			(unsigned)waveforms[i].frequency,
			(unsigned)waveforms[i].duty_cycle);
	}
	printf("  -------------------------------------------\r\n");
#ifdef CONFIG_HAVE_TC_DMA_MODE
	printf("  [p|d] to set capture mode (polling/dma) \r\n");
#endif
	printf("  c: Capture waveform from TC capture channel \r\n");
	printf("  h: Display menu \r\n");
	printf("  ------\r\n\r\n");
}


static void _tc_counter_initialize(uint32_t freq)
{
	uint32_t frequency;
	struct _callback _cb;

	printf("* Configure TC: channel %d: counter mode\r\n", tc_counter.channel);

	frequency = tcd_configure_counter(&tc_counter, freq, freq);

	printf("  - Required frequency = %uHz\r\n", (unsigned)freq);
	printf("  - Configured frequency = %uHz\r\n", (unsigned)frequency);
	callback_set(&_cb, _tc_counter_callback, NULL);
	tcd_start(&tc_counter, &_cb);
}

/**
 * \brief Configure a TC channel as waveform operating mode.
 */
static void _tc_waveform_initialize(uint8_t waveform_idx)
{
	uint32_t frequency;

	printf("* Configure TC: channel %d: waveform generator mode\r\n", tc_waveform.channel);

	frequency = tcd_configure_waveform(&tc_waveform,
					   waveforms[waveform_idx].min_timer_freq,
					   waveforms[waveform_idx].frequency,
					   waveforms[waveform_idx].duty_cycle * 10);

	printf("  - Duty Cycle = %2d%%\r\n",(int)waveforms[waveform_idx].duty_cycle);
	printf("  - Required frequency = %dHz\r\n", (int)waveforms[waveform_idx].frequency);
	printf("  - Configured frequency = %dHz\r\n", (int)frequency);
	tcd_start(&tc_waveform, NULL);
}

static uint32_t _tc_capture_initialize(uint32_t freq, uint8_t* buf, uint32_t buf_size)
{
	uint32_t frequency;

	struct _buffer _buf = {
		.data = buf,
		.size = buf_size,
	};

	/* Configure one TC channel as capture operating mode */
	printf("* Configure TC: channel %d: capture mode\r\n", tc_capture.channel);

	frequency = tcd_configure_capture(&tc_capture, freq, &_buf);

	printf("  - Required frequency = %dHz\r\n", (int)freq);
	printf("  - Configured frequency = %dHz\r\n", (int)frequency);

	return frequency;
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief tc_capture_waveform Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t key;
	uint32_t frequency, freq;
	uint32_t duty_cycle;
	struct _callback _cb;

	/* Output example information */
	console_example_info("TC Example");

	/* Configure PIO Pins for TC0 */
	pio_configure(pins_tc, ARRAY_SIZE(pins_tc));

	_tc_waveform_initialize(0);
	frequency = _tc_capture_initialize(CAPTURE_FREQ, (uint8_t*)capture_buf, sizeof(capture_buf));
	_tc_counter_initialize(COUNTER_FREQ);

	_display_menu();

	while (1) {
		key = console_get_char();
		switch (key) {
		case 'H':
		case 'h':
			_display_menu();
			break;
#ifdef CONFIG_HAVE_TC_DMA_MODE
		case 'p':
		case 'P':
			tc_capture.cfg.capture.transfer_mode = TCD_TRANSFER_MODE_POLLING;
			printf("TC capture in polling mode\r\n");
			break;
		case 'D':
		case 'd':
			tc_capture.cfg.capture.transfer_mode = TCD_TRANSFER_MODE_DMA;
			printf("TC capture in DMA mode\r\n");
			break;
#endif
		case 'c':
		case 'C':
			printf("TC: capture...\r\n");
			callback_set(&_cb, _tc_capture_callback, NULL);
			tcd_start(&tc_capture, &_cb);
			tcd_wait(&tc_capture);
			/* Compute frequency and duty cycle using RA/RB average */
			{
				int i;
				uint32_t ra = 0, rb = 0;
				/* The first sample is ignored since it may not
				 * be reliable depending on the capture /
				 * waveform sync */
				for (i = 1; i < CAPTURE_COUNT; i++) {
					ra += capture_buf[2 * i];
					rb += capture_buf[2 * i + 1];
				}
				ra /= (CAPTURE_COUNT - 1);
				rb /= (CAPTURE_COUNT - 1);
				freq = frequency / rb;
				duty_cycle = (rb - ra) * 100 / rb;
			}
			printf("Captured wave\r\n");
			printf("- frequency=%uHz\r\n", (unsigned)freq);
			printf("- duty cycle=%u%%\r\n", (unsigned)duty_cycle);
			printf("\r\nPress 'h' to display menu\r\n");
			break;
		default:
			/* Set waveform configuration #n */
			if ((key >= '0') && (key <= ('0' + ARRAY_SIZE(waveforms) - 1))) {
				_tc_waveform_initialize(key - '0');
			}
			break;
		}
	}
}
