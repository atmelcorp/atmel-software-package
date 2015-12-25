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
 * This example demonstrates a simple configuration of a single PWM channel to
 * generate variable duty cycle signals.

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
static const struct _pin pins_pwm_led[] = PINS_PWM_LEDS;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Configure outputs for a PWM asynchronous channel
 */
static void _pwm_demo_asynchronous_channel(uint32_t init, uint8_t channel,
		uint32_t cprd, uint32_t clock)
{
	uint32_t mode;
	static uint32_t duty_cycle;
	static bool duty_cycle_inc;

	if (init) {
		/* Configure PWM channel 0 */
		pwmc_disable_channel(PWM, channel);
		mode = PWM_CMR_CPOL | PWM_CMR_CALG | PWM_CMR_CPRE_CLKA ;
		pwmc_configure_channel(PWM, channel, mode);
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

/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Application entry point for PWM example.
 *
 * Outputs a PWM on LED0.
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

	/* Initialize console */
	console_configure(CONSOLE_BAUDRATE);

	/* Clear console */
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

	/* Configure PIT for timer_wait */
	printf("Configure PIT \n\r");
	timer_configure(1000);

	/* PIO configuration */
	pio_configure(pins_pwm_led, ARRAY_SIZE(pins_pwm_led));

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

	while (1) {
		if (console_is_rx_ready()) {
			key = console_get_char();
			printf("Input %c\n\r", key);
			switch (key) {
			case 'a':
				current_demo = key;
				pwm_channel = PWM_LED_CH_0;
				_pwm_demo_asynchronous_channel(1, pwm_channel, cprd, clock);
				break;
			default:
				break;
			}
		}
		if ('a' == current_demo)
			_pwm_demo_asynchronous_channel(0, pwm_channel, cprd, clock);
	}
}

