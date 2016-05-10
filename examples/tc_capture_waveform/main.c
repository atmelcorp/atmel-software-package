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
 * This package can be used with SAMA5D2-XULT, SAMA5D2-EK and SAMA5D4-XULT.
 *
 * Requirements before running this example on SAMA5D2-XULT:
 * Connect EXP_PA19 (J21 pin 2) and EXP_PB22 (J22 pin 6) on the board.
 *
 * Requirements before running this example on SAMA5D4-EK:
 * Connect USBC_EN5V_PE12 (J19 pin 44) and MCI1_PWR_PE15 (J19 pin 47) on the board.
 *
 * Requirements before running this example on SAMA5D4-XULT:
 * Connect EXP_PE12 (J15 pin 9) and EXP_PE15 (J18 pin 6) on the board.
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

#include "board.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"
#include <assert.h>

#include "peripherals/aic.h"
#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/twid.h"
#include "peripherals/tc.h"
#include "peripherals/xdmad.h"
#include "peripherals/wdt.h"

#include "misc/console.h"

#include "power/act8945a.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#if defined(CONFIG_BOARD_SAMA5D2_XPLAINED)
	#include "config_sama5d2-xplained.h"
#elif defined(CONFIG_BOARD_SAMA5D4_EK)
	#include "config_sama5d4-ek.h"
#elif defined(CONFIG_BOARD_SAMA5D4_XPLAINED)
	#include "config_sama5d4-xplained.h"
#else
	#error Unsupported board!
#endif

/** Timer Counter descriptor definition */
struct _tc_desc;

/** Timer Counter mode definition */
enum _tc_mode {
	TC_MODE_CAPTURE,
	TC_MODE_WAVEFORM
};

/** Timer Counter descriptor definition */
struct _tc_desc {
	Tc* addr;
	uint8_t channel;
	uint8_t duty_cycle;
	uint8_t tc_mode;
	uint8_t reserved;
	uint32_t frequency;
};

/** Describes a possible Timer configuration as waveform mode */
struct _waveform {
	uint32_t clock_selection; /** Internal clock signals selection. */
	uint32_t frequency;       /** Waveform frequency (in Hz). */
	uint32_t duty_cycle;      /** Duty cycle in percent (positive). */
};

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

#ifdef CONFIG_HAVE_PMIC_ACT8945A
struct _pin act8945a_pins[] = ACT8945A_PINS;
struct _twi_desc act8945a_twid = {
	.addr = ACT8945A_ADDR,
	.freq = ACT8945A_FREQ,
	.transfert_mode = TWID_MODE_POLLING
};
struct _act8945a act8945a = {
	.desc = {
		.pin_chglev = ACT8945A_PIN_CHGLEV,
		.pin_irq = ACT8945A_PIN_IRQ,
		.pin_lbo = ACT8945A_PIN_LBO
	}
};
#endif

/** PIOs for TC capture, waveform */
static const struct _pin pins_tc[] = {
	PIN_TC_CAPTURE_IN, PIN_TC_WAVEFORM_OUT
};

/** define Timer Counter descriptor for capture */
static struct _tc_desc tc_capture = {
	.addr = TC0,
	.channel = CHANNEL_TC_CAPTURE_IN,
	.tc_mode = TC_MODE_CAPTURE
};

/** define Timer Counter descriptor for output waveform */
static struct _tc_desc tc_waveform = {
	.addr = TC0,
	.channel = CHANNEL_TC_WAVEFORM_OUT,
	.tc_mode = TC_MODE_WAVEFORM
};

/** TC waveform configurations (base on 66MHz peripheral clock)*/
static const struct _waveform waveforms[] = {
	{ TC_CMR_TCCLKS_TIMER_CLOCK4, 80, 30 },
	{ TC_CMR_TCCLKS_TIMER_CLOCK3, 180, 50 },
	{ TC_CMR_TCCLKS_TIMER_CLOCK3, 400, 75 },
	{ TC_CMR_TCCLKS_TIMER_CLOCK2, 500, 80 },
	{ TC_CMR_TCCLKS_TIMER_CLOCK2, 2000, 55 }
};

/** Current waveform index */
static uint8_t waveform_idx = 0;

/** Clock selection for capture channel */
static uint8_t capture_clock_sel = 1;

/** Capture status*/
static uint32_t captured_pulses;

/** Capture channel register A value */
static uint32_t captured_ra;

/** Capture channel register B value */
static uint32_t captured_rb;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Displays the user menu.
 */
static void _display_menu(void)
{
	uint32_t i;

	printf("\n\rMenu :\n\r");
	printf("------\n\r");
	printf("  Output waveform property:\n\r");
	for (i = 0; i < ARRAY_SIZE(waveforms); i++) {
		printf("  %u: Set Frequency = %4u Hz, Duty Cycle = %2u%%\n\r",
			(unsigned)i,
			(unsigned)waveforms[i].frequency,
			(unsigned)waveforms[i].duty_cycle);
	}
	printf("  -------------------------------------------\n\r");
	printf("  c: Capture waveform from TC capture channel \n\r");
	printf("  s: Stop capture and display what have been captured \n\r");
	printf("  h: Display menu \n\r");
	printf("  ------\n\r\n\r");
}

/**
 * \brief Interrupt handler for the TC capture.
 */
static void _tc_capture_handler(void)
{
	uint32_t status = tc_get_status(tc_capture.addr, tc_capture.channel);

	if ((status & TC_SR_LDRBS) == TC_SR_LDRBS) {
		captured_pulses++;
		tc_get_ra_rb_rc(tc_capture.addr, tc_capture.channel,
			&captured_ra, &captured_rb, 0);
	}
}

/**
 * \brief Configure clock, frequency and duty cycle for TC in waveform mode.
 */
static void _tc_waveform_configure(struct _tc_desc *tcd, uint32_t tc_clks)
{
	uint32_t frequency;
	uint32_t mode;
	uint32_t ra, rc;

	mode = tc_clks
	     | TC_CMR_WAVE
	     | TC_CMR_ACPA_SET
	     | TC_CMR_ACPC_CLEAR
	     | TC_CMR_CPCTRG;
	tc_configure(tcd->addr, tcd->channel, mode);

	frequency = tc_get_available_freq(tcd->addr, tc_clks);
	rc = frequency / tcd->frequency;
	ra = (100 - tcd->duty_cycle) * rc / 100;
	tc_set_ra_rb_rc(tcd->addr, tcd->channel, &ra, 0, &rc);
}

/**
 * \brief Configure a TC channel as waveform operating mode.
 */
static void _tc_waveform_initialize(struct _tc_desc *tcd)
{
	uint32_t tc_clks;

	tcd->frequency = waveforms[waveform_idx].frequency;
	tcd->duty_cycle = waveforms[waveform_idx].duty_cycle;
	tc_clks = waveforms[waveform_idx].clock_selection;

	/*  Disable TC clock */
	tc_stop(tcd->addr, tcd->channel);

	/*  Clear status register */
	tc_get_status(tcd->addr, tcd->channel);

	/* Configure waveform frequency and duty cycle */
	_tc_waveform_configure(tcd, tc_clks);

	/* Enable TC */
	tc_start(tcd->addr, tcd->channel);

	printf ("Start waveform: Frequency = %d Hz,Duty Cycle = %2d%%\n\r",
			(int)tcd->frequency, (int)tcd->duty_cycle);
}

/**
 * \brief Configure a TC channel as capture operating mode.
 */
static void _tc_capture_initialize(struct _tc_desc *tcd)
{
	uint32_t tc_id = get_tc_id_from_addr(tc_capture.addr);

	uint32_t mode = capture_clock_sel
		| TC_CMR_LDRA_RISING
		| TC_CMR_LDRB_FALLING
		| TC_CMR_ABETRG
		| TC_CMR_ETRGEDG_FALLING;;

	pmc_enable_peripheral(tc_id);
	tc_configure(tcd->addr, tcd->channel, mode);

	aic_set_source_vector(tc_id, _tc_capture_handler);
	aic_enable(tc_id);
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
	uint32_t frequency;
	uint32_t duty_cycle;
	uint32_t tc_id;

	/* Disable watchdog */
	wdt_disable();

	/* Disable all PIO interrupts */
	pio_reset_all_it();

	/* Configure console */
	board_cfg_console(0);

	/* Output example information */
	printf("-- TC capture waveform Example %s --\n\r", SOFTPACK_VERSION);
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

#ifdef CONFIG_HAVE_PMIC_ACT8945A
	pio_configure(act8945a_pins, ARRAY_SIZE(act8945a_pins));
	if (act8945a_configure(&act8945a, &act8945a_twid)) {
		act8945a_set_regulator_voltage(&act8945a, 6, 2500);
		act8945a_enable_regulator(&act8945a, 6, true);
	} else {
		printf("--E-- Error initializing ACT8945A PMIC\n\r");
	}
#endif

	/* Configure PIO Pins for TC0 */
	pio_configure(pins_tc, ARRAY_SIZE(pins_tc));

	tc_id = get_tc_id_from_addr(tc_waveform.addr);
	pmc_enable_peripheral(tc_id);

	/* Configure one TC as waveform operating mode */
	printf("Configure TC channel %d as waveform operating mode \n\r",
		tc_waveform.channel);
	_tc_waveform_initialize(&tc_waveform);

	/* Configure one TC channel as capture operating mode */
	printf("Configure TC channel %d as capture operating mode \n\r",
		tc_capture.channel);
	_tc_capture_initialize(&tc_capture);

	_display_menu();

	while (1) {
		key = console_get_char();
		switch (key) {
		case 'H':
		case 'h':
			_display_menu();
			break;
		case 'S':
		case 's':
			if (captured_pulses) {
				tc_stop(tc_capture.addr, tc_capture.channel);
				printf("Captured %u pulses from TC capture channel, "
						"RA = %u, RB = %u \n\r",
						(unsigned int)captured_pulses,
						(unsigned int)captured_ra,
						(unsigned int)captured_rb);

				frequency = tc_get_available_freq(tc_waveform.addr, capture_clock_sel);
				frequency /= captured_rb;
				duty_cycle = (captured_rb - captured_ra) * 100 / captured_rb;
				printf("Captured wave frequency = %d Hz, "
					"Duty cycle = %d%% \n\r", (int)frequency, (int)duty_cycle);

				captured_pulses = 0;
			} else {
				printf("No waveform has been captured\n\r");
			}
			printf("\n\rPress 'h' to display menu\n\r");
			break;
		case 'c' :
			printf ("Start capture, press 's' to stop\n\r");
			tc_enable_it(tc_capture.addr, tc_capture.channel, TC_IER_LDRBS);
			/* Reset and enable the timer counter for TC capture channel */
			tc_start(tc_capture.addr, tc_capture.channel);
			break;
		default:
			/* Set waveform configuration #n */
			if ((key >= '0') && (key <= ('0' + ARRAY_SIZE(waveforms) - 1))) {
				if (!captured_pulses) {
					waveform_idx = key - '0';
					_tc_waveform_initialize(&tc_waveform);
				} else {
					printf("In capturing ... , press 's' to stop capture first"
						"\n\r");
				}
			}
			break;
		}
	}
}

