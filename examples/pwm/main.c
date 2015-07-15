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
 * This example demonstrates a simple configuration of two PWM channels to
 * generate variable duty cycle and frequence signals.

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
 * This file contains all the specific code for the pwm example.
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
#include "misc/led.h"
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

/** Global timestamp in milliseconds since start of application */
volatile uint32_t dwTimeStamp = 0;

/** Pio pins to configure. */
static const struct _pin pin_pwm_led_red[] = PWM_LED_0;
static const struct _pin pin_pwm_led_green[] = PWM_LED_1;
static const struct _pin pin_pwm_led_blue[] = PWM_LED_2;
static const struct _pin pins_pwm_led[] = PINS_PWM_LEDS;

static const struct _pin pins_led[] = PINS_LEDS;

/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/

void _led_pulse (uint8_t nled, uint32_t pulse)
{
	led_set(nled);
	timer_wait(pulse);
	led_clear(nled);
}


/**
 * \brief Application entry point for PWM example.
 *
 * Outputs a PWM on LED0 & LED1.
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t status;
    uint32_t mode, cprd;
	double clock;

    /* Disable watchdog */
    wdt_disable();
	/* Disable all PIO interrupts */
	pio_reset_all_it();

	/* Initialize console */
	console_configure(CONSOLE_BAUDRATE);
	/* Clear console */
	console_clear_screen();
	console_reset_cursor();

#if defined (ddram)
	mmu_initialize((uint32_t *) 0x20C000);
	cp15_enable_mmu();
	cp15_enable_dcache();
	cp15_enable_icache();
#endif

    /* Output example information */
    printf("-- PWM Example %s --\n\r", SOFTPACK_VERSION);
    printf("-- %s\n\r", BOARD_NAME);
    printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

#ifdef CONFIG_HAVE_PMIC_ACT8945A
	status = act8945a_begin();
	if(status) {
		printf("--E-- Error init ACT8945A \n\r");
	} else {
		act8945a_set_regulator_voltage_out4to7 (V_OUT6, 2800);
		act8945a_set_regulator_state_out4to7 (V_OUT6, ACT8945A_SET_ON);
	}
#endif

	/* Configure PIT for timer_wait */
	printf("Configure PIT \n\r");
	timer_configure(1000);

	/* Configuration PIOs Led as output */
	pio_configure(pins_led, ARRAY_SIZE(pins_led));
	_led_pulse(LED_RED, 500);
	_led_pulse(LED_GREEN, 500);
	_led_pulse(LED_BLUE, 500);

    /* Enable PWM peripheral clock */
    pmc_enable_peripheral(ID_PWM);
    /* Set clock A and clock B */
	/* CLKA clock is clock selected by PREA : 0x0A Peripheral clock/1024 */
	/* divided by DIVB factor : 32 */
	mode = 	PWM_CLK_PREB_CLK_DIV1024 | (PWM_CLK_DIVB(32)) |
			PWM_CLK_PREA_CLK_DIV1024 | (PWM_CLK_DIVA(32));
    pwmc_configure_clocks(PWM, mode);
	clock = pmc_get_peripheral_clock(ID_PWM);
	printf("-- PWM Peripheral Clock: %3.2f MHz --\n\r", clock/1000000);

	/* Configure PWM channel 1 for LED2 (BLUE)*/
	pwmc_disable_channel(PWM, PWM1_CH);
	mode =  PWM_CMR_CPRE_CLKB;
	pwmc_configure_channel(PWM, PWM1_CH, mode);
	cprd = 512;
	pwmc_set_period(PWM, PWM1_CH, cprd);
	pwmc_set_duty_cycle(PWM, PWM1_CH, cprd/3);
	pwmc_enable_channel(PWM, PWM1_CH);

	/* cprd / f(peripheral clock) */
	printf("-- Led2  ClockB Duty cycle: 1/3 Signal Period: %4.3f ms  --\n\r", ((cprd*1024*32))/(clock/1000));

	do {
		printf("** Led Red and Led Blue blinking **\n\r");
    	/* PIO configuration */
		printf("-- Led1 Green off --\n\r");
		led_configure(LED_GREEN);
    	pio_configure(pin_pwm_led_red, ARRAY_SIZE(pin_pwm_led_red));
		pio_configure(pin_pwm_led_blue, ARRAY_SIZE(pin_pwm_led_blue));

		/* Configure PWM channel 2 for LED0 (RED)  */
		pwmc_disable_channel(PWM, PWM2_CH);
		mode = PWM_CMR_CPOL | PWM_CMR_CALG | PWM_CMR_CPRE_CLKA ; //| PWM_CMR_DPOLI;
		pwmc_configure_channel(PWM, PWM2_CH, mode);
		cprd = 1267;
		pwmc_set_period(PWM, PWM2_CH, cprd);
		pwmc_set_duty_cycle(PWM, PWM2_CH, cprd/2); // Duty cycle 50%
		pwmc_enable_channel(PWM, PWM2_CH);

		printf("-- Led0  ClockA Duty cycle: 50%% Signal Period: %4.3f ms  --\n\r", ((2*cprd*1024*32))/(clock/1000));

		timer_wait(5000);

		printf("-- Led0 Red off --\n\r");
		led_configure(LED_RED);
		printf("** Led Green and Led Blue blinking **\n\r");
		pio_configure(pin_pwm_led_green, ARRAY_SIZE(pin_pwm_led_green));

		/* Configure PWM channel 2 for LED1 (GREEN)  */
		pwmc_disable_channel(PWM, PWM2_CH);
		mode = PWM_CMR_CPOL | PWM_CMR_CALG | PWM_CMR_CPRE_CLKA ; //| PWM_CMR_DPOLI;
		pwmc_configure_channel(PWM, PWM2_CH, mode);
		cprd = 1267*2;
		pwmc_set_period(PWM, PWM2_CH, cprd);
		pwmc_set_duty_cycle(PWM, PWM2_CH, cprd/2); // Duty cycle 50%
		pwmc_enable_channel(PWM, PWM2_CH);

		printf("-- Led1  ClockA Duty cycle: 50%% Signal Period: %4.3f ms  --\n\r", ((2*cprd*1024*32))/(clock/1000));

		timer_wait(10000);

	} while(1);
}

