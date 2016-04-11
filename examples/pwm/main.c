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
 * \page pwm PWM Example
 *
 * \section Purpose
 *
 * This example demonstrates how to use PWM module.
 *
 * \section Requirements
 *
 * This package can be used with SAMA5D4-XULT and SAMA5D2-XULT.
 *
 * Requirements before running this example on SAMA5D2-XULT:
 * Connect EXP/XPRO_PB5 (J20 pin 2) and EXP_PB22 (J22 pin 6) on the board to
 * capture the PWM output using TC.
 *
 * Requirements before running this example on SAMA5D4-EK:
 * Connect EXP_PB28 (J19A pin 19) and USBC_EN5V_PE12 (J19C pin 44).
 *
 * Requirements before running this example on SAMA5D4-XULT:
 * Connect EXP_PB11 (J15 pin 26) and EXP_PE12 (J15 pin 9) on the board to
 * capture the PWM output using TC.
 *
 * \section Descriptions
 *
 * This example demonstrates how to configure a single PWM channel to generate
 * variable duty cycle signals; how to use DMA feature for synchronous channels;
 * and how to work with fault/override/dead-time modes. A TC is also used to
 * capture the signal PWM outputs for analyzing.
 *
 * The code can be roughly broken down as follows:
 * <ul>
 * <li>Configure TC to capture the signal PWM outputs. 'c' to start capture.
 * <li>Captured information would be dumped to console when finished.
 * <li>PWM outputs can also be watched with the help of an oscillator.
 * <li>PWM asynchronous channel operations. 'a' to configure the channel.
 * <li>PWM DMA operations for synchronous channels. 'd' to start DMA.
 * <li>PWM fault mode test. 'f' to lunch the fault from TC0, 'F' to clear it.
 * <li>PWM output overide/dead-time test. 'o' to configure the parameters.
 * </ul>
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board. Please refer to the
 * <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6132.pdf">
 * SAM-BA User Guide</a>, the
 * <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6132.pdf">
 * GNU-Based Software Development</a> application note or to the
 * <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6132.pdf">
 * IAR EWARM User Guide</a>, depending on your chosen solution.
 * -# Optionally, on the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *    \code
 *     -- PWM Example xxx --
 *      -- SAMxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *    \endcode
 *
 * \section References
 * - pwm/main.c
 * - pwmc.c
 * - pwmc.h
 */

/**
 * \file
 *
 * This file contains all the specific code for the PWM example.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"

#include "peripherals/aic.h"
#include "peripherals/pmc.h"
#include "peripherals/pwmc.h"
#include "peripherals/pit.h"
#include "peripherals/pio.h"
#include "peripherals/tc.h"
#include "peripherals/wdt.h"
#include "peripherals/xdmad.h"

#include "cortex-a/mmu.h"
#include "misc/console.h"

#include "power/act8945a.h"

#include "timer.h"
#include "trace.h"
#include "compiler.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** Timer Counter descriptor definition */
struct _tc_desc {
	Tc* addr;
	uint8_t channel;
};

/** maximum captures */
#define MAX_CAPTURES 32

/** define IDLE status for capturing */
#define TC_CAPTURE_IDLE ((uint32_t)-1)

#if defined(CONFIG_BOARD_SAMA5D2_XPLAINED)
	#include "config_sama5d2-xplained.h"
#elif defined(CONFIG_BOARD_SAMA5D4_EK)
	#include "config_sama5d4-ek.h"
#elif defined(CONFIG_BOARD_SAMA5D4_XPLAINED)
	#include "config_sama5d4-xplained.h"
#else
#error Unsupported board!
#endif

#ifdef CONFIG_HAVE_PWM_DMA
/** Duty cycle buffer length for synchronous channels */
#define DUTY_BUFFER_LENGTH 100
#endif

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

/** Global timestamp in milliseconds since start of application */
volatile uint32_t dwTimeStamp = 0;

/** Pio pins to configure. */
static const struct _pin pins_pwm[] = { PIN_PWM };

#ifdef CONFIG_HAVE_PWM_DMA
/** Duty cycle buffer synchronous channels */
static uint16_t duty_buffer[DUTY_BUFFER_LENGTH];
#endif

/** PIOs for TC capture, waveform */
static const struct _pin pins_tc[] = { PIN_TC_CAPTURE_IN };

/** define Timer Counter descriptor for capture */
static struct _tc_desc tc_capture = {
	.addr = TC0,
	.channel = CHANNEL_TC_CAPTURE_IN,
};

/** Clock selection for capture channel */
static uint8_t capture_clock_sel = TC_CMR_TCCLKS_TIMER_CLOCK4;

/** capture index */
static uint32_t captured_pulses = TC_CAPTURE_IDLE;

/** capturing buffer */
static uint32_t captured_rarb[MAX_CAPTURES][2];

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Displays the user menu.
 */
static void _display_menu(void)
{
	printf("\n\rMenu :\n\r");
	printf("  -------------------------------------------\n\r");
	printf("  a: PWM operations for asynchronous channels \n\r");
#ifdef CONFIG_HAVE_PWM_DMA
	printf("  d: PWM DMA operations with synchronous channels \n\r");
#endif
	printf("  f: PWM fault mode initialize \n\r");
	printf("  F: PWM fault mode clear and disable \n\r");
	printf("  m: PWM 2-bit Gray Up/Down Counter for Stepper Motor \n\r");
	printf("  o: PWM output override / dead time settings \n\r");
	printf("  c: Capture waveform from TC capture channel \n\r");
	printf("  h: Display menu \n\r");
	printf("  -------------------------------------------\n\r\n\r");
}

/**
 * \brief Interrupt handler for the TC capture.
 */
static void _tc_capture_handler(void)
{
	uint32_t status = tc_get_status(tc_capture.addr, tc_capture.channel);

	if ((status & TC_SR_LDRBS) == TC_SR_LDRBS) {
		tc_get_ra_rb_rc(tc_capture.addr, tc_capture.channel,
			&captured_rarb[captured_pulses][0],
			&captured_rarb[captured_pulses][1],
			0);
		captured_pulses++;
		if (captured_pulses >= MAX_CAPTURES)
			tc_stop(tc_capture.addr, tc_capture.channel);
	}
}

/**
 * \brief Configure a TC channel as capture operating mode.
 */
static void _tc_capture_initialize(struct _tc_desc *tcd)
{
	uint32_t tc_id = get_tc_id_from_addr(tc_capture.addr);

	uint32_t mode = TC_CMR_TCCLKS(capture_clock_sel)
	              | TC_CMR_LDRA_RISING
	              | TC_CMR_LDRB_FALLING
	              | TC_CMR_ABETRG
	              | TC_CMR_ETRGEDG_FALLING;

	pmc_enable_peripheral(tc_id);

	tc_configure(tcd->addr, tcd->channel, mode);

	aic_set_source_vector(tc_id, _tc_capture_handler);
	aic_enable(tc_id);
}

/**
 * \brief start capture
 */
static void _start_capture(void)
{
	if (TC_CAPTURE_IDLE != captured_pulses) {
		printf ("Capturing, can not start new capture\n\r");
		return;
	}
	printf("Start capture, result will be dumped to console when finished.\n\r");
	tc_enable_it(tc_capture.addr, tc_capture.channel, TC_IER_LDRBS);
	captured_pulses = 0;
	/* Reset and enable the timer counter for TC capture channel */
	tc_start(tc_capture.addr, tc_capture.channel);
}

/**
 * \brief dump captured results to console
 */
static void _show_captured_results(void)
{
	uint32_t i;
	uint32_t frequency;
	uint32_t duty_cycle;

	if ((captured_pulses < MAX_CAPTURES)
		|| (TC_CAPTURE_IDLE == captured_pulses)) {
		return;
	}

	printf("\n\rCaptured %u pulses from TC capture channel:\n\r",
			(unsigned int)captured_pulses);
	for (i = 0; i < MAX_CAPTURES; ++i)
	{
		frequency = tc_get_available_freq(tc_capture.addr, capture_clock_sel);
		frequency /= captured_rarb[i][1];
		duty_cycle = (captured_rarb[i][1] - captured_rarb[i][0]) * 100;
		duty_cycle /= captured_rarb[i][1];
		printf("Captured[%d] frequency = %d Hz, Duty cycle = %d%% \n\r",
			(int)i, (int)frequency, (int)duty_cycle);
	}
	printf("\n\r");

	captured_pulses = TC_CAPTURE_IDLE;
}

/**
 * \brief Interrupt handler for the PWM.
 */
static void _pwm_handler(void)
{
	trace_debug("PWM handler, interrupt status 0x%08x 0x%08x, "
		"fault status 0x%08x\r\n",
		(unsigned)pwmc_get_it_status1(PWM),
		(unsigned)pwmc_get_it_status2(PWM),
		(unsigned)pwmc_get_fault_status(PWM));
}

/**
 * \brief Configure outputs for a PWM asynchronous channel
 */
static void _pwm_demo_asynchronous_channel(uint32_t init, uint8_t channel,
		uint32_t cprd, uint32_t clock)
{
	static uint32_t duty_cycle;
	static bool duty_cycle_inc;

	if (init) {
		/* Configure PWM channel 0 */
		pwmc_disable_channel(PWM, channel);
		pwmc_configure_channel(PWM, channel,
			PWM_CMR_CPOL | PWM_CMR_CALG | PWM_CMR_CPRE_CLKA);
		pwmc_set_period(PWM, channel, cprd);
		pwmc_set_duty_cycle(PWM, channel, 0);
		pwmc_enable_channel(PWM, channel);
		duty_cycle = 0;
		duty_cycle_inc = true;
		return;
	}
	printf("-- PWM Channel %u Duty cycle: %lu%% Signal Period: %lu ms--\n\r",
			(unsigned)channel,
			(unsigned)(duty_cycle*100)/cprd,
			(unsigned)((2*cprd*1024*32))/(clock/1000));

	pwmc_set_duty_cycle(PWM, channel, duty_cycle);
	timer_wait(50);

	if (duty_cycle_inc) {
		if (duty_cycle < (cprd - 1))
			duty_cycle++;
		else
			duty_cycle_inc = false;;
	} else {
		if (duty_cycle > 0)
			duty_cycle--;
		else
			duty_cycle_inc = true;
	}
}

/**
 * \brief PWM call-back routine for DMA operations
 */
static void _pwmc_callback(void* args)
{
	trace_debug("PWM DMA Transfer Finished\r\n");
}

#ifdef CONFIG_HAVE_PWM_DMA
/**
 * \brief Configure DMA operation for PWM synchronous channel
 */
static void _pwm_demo_dma(uint8_t channel, uint32_t cprd, uint32_t clock)
{
	int i;
	bool flag = false;

	pwmc_disable_channel(PWM, channel);
	pwmc_configure_sync_channels(PWM,
		PWM_SCM_UPDM_MODE2 | (1 << channel) | (1 << 0));
	pwmc_configure_channel(PWM, 0,
		PWM_CMR_CPOL | PWM_CMR_CALG | PWM_CMR_CPRE_CLKA);
	pwmc_set_period(PWM, 0, cprd);
	pwmc_set_duty_cycle(PWM, 0, 0);
	pwmc_set_sync_channels_update_period(PWM, 0, 8);
	/* Enable the synchronous channels */
	pwmc_enable_channel(PWM, 0);
	for (i = 0; i < ARRAY_SIZE(duty_buffer); i++) {
		if (0 == (i % cprd))
			flag = !flag;
		duty_buffer[i] = flag ? (i % cprd) : (cprd - (i % cprd));
	}
	pwmc_set_dma_finished_callback(_pwmc_callback, 0);
	pwmc_dma_duty_cycle(PWM, duty_buffer, ARRAY_SIZE(duty_buffer));
}
#endif

/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Application entry point for PWM example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t key;
	uint32_t mode, cprd;
	uint32_t clock;
	uint32_t pwm_channel;
	uint8_t current_demo = 'h';

	/* Disable watchdog */
	wdt_disable();

	/* Disable all PIO interrupts */
	pio_reset_all_it();

	/* Configure console */
	board_cfg_console();
	console_clear_screen();
	console_reset_cursor();

	/* Output example information */
	printf("-- PWM Example %s --\n\r", SOFTPACK_VERSION);
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

	/* Initialize XDMA subsystem */
	xdmad_initialize(false);

	/* Configure PIO Pins for TC0 */
	pio_configure(pins_tc, ARRAY_SIZE(pins_tc));

	/* Configure one TC channel as capture operating mode */
	printf("Configure TC channel %d as capture operating mode \n\r",
		tc_capture.channel);
	_tc_capture_initialize(&tc_capture);

	/* PIO configuration */
	pio_configure(pins_pwm, ARRAY_SIZE(pins_pwm));

	/* Enable PWM peripheral clock */
	pmc_enable_peripheral(ID_PWM);

	/* Set clock A and clock B */
	/* CLKA clock is clock selected by PREA : 0x0A Peripheral clock/1024 */
	/* divided by DIVB factor : 32 */
	mode = PWM_CLK_PREB_CLK_DIV1024 | (PWM_CLK_DIVB(32)) |
			PWM_CLK_PREA_CLK_DIV1024 | (PWM_CLK_DIVA(32));
	pwmc_configure_clocks(PWM, mode);
	clock = pmc_get_peripheral_clock(ID_PWM);
	printf("-- PWM Peripheral Clock: %u MHz --\n\r",
			(unsigned)(clock/1000000));

	cprd = 26;

	_display_menu();
	while (1) {
		if (console_is_rx_ready()) {
			key = console_get_char();
			printf("Input %c\n\r", key);
			switch (key) {
			case 'a':
				current_demo = key;
				pwm_channel = CHANNEL_PWM;
				_pwm_demo_asynchronous_channel(1, pwm_channel, cprd, clock);
				break;
#ifdef CONFIG_HAVE_PWM_DMA
			case 'd':
				current_demo = key;
				pwm_channel = CHANNEL_PWM;
				_pwm_demo_dma(pwm_channel, cprd, clock);
				break;
#endif
			case 'f':
				pwmc_set_fault_mode(PWM,
					PWM_FMR_FPOL(1 << PWM_FAULT_INPUT_TIMER0)
					| PWM_FMR_FMOD(0) | PWM_FMR_FFIL(0));
				pwmc_set_fault_protection(PWM, PWM_FPV1_FPVH2 | PWM_FPV1_FPVL2, 0);
				pwmc_enable_fault_protection(PWM, pwm_channel, PWM_FAULT_INPUT_TIMER0);
				aic_set_source_vector(ID_PWM, _pwm_handler);
				pwmc_enable_it(PWM, PWM_IER1_FCHID0, 0);
				aic_enable(ID_PWM);

				pmc_enable_peripheral(ID_TC0);
				tc_configure(TC0, 0,
					TC_CMR_TCCLKS(4) | TC_CMR_WAVE | TC_CMR_CPCTRG);
				tc_set_fault_mode(TC0, TC_FMR_ENCF0);
				{
					uint32_t rc = 0x10000;
					tc_set_ra_rb_rc(TC0, 0, NULL, NULL, &rc);
				}
				tc_start(TC0, 0);
				break;
			case 'F':
				pwmc_fault_clear(PWM, PWM_FAULT_INPUT_TIMER0);
				tc_set_fault_mode(TC0, 0);
				break;
			case 'm':
				pwmc_configure_stepper_motor_mode(PWM,
					PWM_SMMR_GCEN0 | PWM_SMMR_GCEN1 | PWM_SMMR_DOWN0);
				break;
			case 'o':
				printf("\n\r  ---- Input options: ----\r\n");
				printf("  0/1: override to 0/1\n\r  others: set dead-time\n\r");
				key = console_get_char();
				switch (key) {
				case '0':
					pwmc_output_override(PWM, pwm_channel, 0, 0, 0);
					pwmc_output_override(PWM, pwm_channel, 1, 0, 0);
					break;
				case '1':
					pwmc_output_override(PWM, pwm_channel, 0, 1, 0);
					pwmc_output_override(PWM, pwm_channel, 1, 1, 0);
					break;
				default:
					pwmc_output_dead_time(PWM, pwm_channel, 0, 0);
					pwmc_disable_output_override(PWM, pwm_channel, 0, 0);
					pwmc_disable_output_override(PWM, pwm_channel, 1, 0);
					break;
				}
				break;
			case 'c':
				_start_capture();
				break;
			case 'h':
			default:
				current_demo = key;
				pwmc_disable_channel(PWM, 0);
				pwmc_disable_channel(PWM, pwm_channel);
				/* no PWM synchronous channels */
				pwmc_configure_sync_channels(PWM, 0);
				pwmc_set_dma_finished_callback(NULL, 0);
				pwmc_configure_stepper_motor_mode(PWM, 0);
				_display_menu();
				break;
			}
		}
		_show_captured_results();
		if ('a' == current_demo)
			_pwm_demo_asynchronous_channel(0, pwm_channel, cprd, clock);
	}
}

