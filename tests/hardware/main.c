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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"

#include "peripherals/aic.h"
#include "peripherals/pmc.h"
#include "peripherals/wdt.h"
#include "peripherals/pio.h"
#include "cortex-a/mmu.h"

#include "misc/led.h"
#include "power/act8945a.h"

#include "misc/console.h"

#include <stdbool.h>
#include <stdio.h>

#include "peripherals/tc.h"
#include "peripherals/pit.h"

#include "trace.h"
#include "compiler.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** LED0 blink time, LED1 blink half this time, in ms */
#define BLINK_PERIOD        1000

/** Delay for pushbutton debouncing (in milliseconds). */
#define DEBOUNCE_TIME       500

/** Maximum number of handled led */
#define MAX_LEDS            3

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

#ifdef PINS_PUSHBUTTONS
/** Pushbutton \#1 pin instance. */
static const struct _pin button_pins[] = PINS_PUSHBUTTONS;
#endif

/* Only used to get the number of available leds */
static const struct _pin pinsLeds[] = PINS_LEDS;

volatile bool led_status[MAX_LEDS] = {0};

/** Global timestamp in milliseconds since start of application */
volatile uint32_t dwTimeStamp = 0;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief Process Buttons Events
 *
 */
static void process_button_evt(uint8_t bt)
{

}

/**
 *  \brief Handler for Buttons rising edge interrupt.
 *
 */
static void pio_handler(uint32_t status)
{
	int i = 0;
	for (i = 0; i < PIO_LISTSIZE(button_pins); ++i) {
		if (status & button_pins[i].mask)
			process_button_evt(i);
	}
	ACT8945A_IrqHandler(status);
}

/**
 *  \brief Handler for PIT interrupt.
 */
static void pit_handler(void)
{
	uint32_t status;

	/* Read the PIT status register */
	status = pit_get_status() & PIT_SR_PITS;
	if (status != 0) {
		dwTimeStamp += (pit_get_pivr() >> 20);
	}
}

/**
 *  \brief Configure the periodic interval timer (PIT) to generate an interrupt
 *  every interrupt every millisecond
 */
static void configure_pit(void)
{
	/* Enable PIT controller */
	pmc_enable_peripheral(ID_PIT);
	/* Initialize the PIT to the desired frequency */
	pit_init(BLINK_PERIOD);
	/* Configure interrupt on PIT */
	aic_enable(ID_PIT);
	aic_set_source_vector(ID_PIT, pit_handler);
	pit_enable_it();
	/* Enable the pit */
	pit_enable();
}

/**
 *  \brief Configure the Pushbuttons
 *
 *  Configure the PIO as inputs and generate corresponding interrupt when
 *  pressed or released.
 */
static void configure_buttons(void)
{
	int i = 0;
	for (i = 0; i < PIO_LISTSIZE(button_pins); ++i)
	{
		/* Configure pios as inputs. */
		pio_configure(&button_pins[i], 1);
		/* Adjust pio debounce filter parameters, uses 10 Hz filter. */
		pio_set_debounce_filter(&button_pins[i], 10);
		/* Initialize pios interrupt with its handlers, see
		 * PIO definition in board.h. */
		pio_configure_it(&button_pins[i]);
		pio_set_group_handler(button_pins[i].id, pio_handler);
		/* Enable PIO line interrupts. */
		pio_enable_it(button_pins);
	}
}

/**
 *  \brief Configure LEDs
 *
 *  Configures LEDs \#1 and \#2 (cleared by default).
 */
static void configure_leds(void)
{
	led_configure(LED_RED);
	led_configure(LED_GREEN);
	led_configure(LED_BLUE);
}

/**
 *  Interrupt handler for TC0 interrupt. Toggles the state of LED\#2.
 */
static void tc_handler(void)
{
	uint32_t dummy;
	/* Clear status bit to acknowledge interrupt */
	dummy = tc_get_status(TC0, 0);
	(void) dummy;

	if (led_status[LED_RED]) led_toggle(LED_RED);
	if (led_status[LED_GREEN]) led_toggle(LED_GREEN);
	if (led_status[LED_BLUE]) led_toggle(LED_BLUE);
}

/**
 *  Configure Timer Counter 0 to generate an interrupt every 250ms.
 */
static void configure_tc(void)
{
	/** Enable peripheral clock. */
	pmc_enable_peripheral(ID_TC0);
	/* Put the source vector */
	aic_set_source_vector(ID_TC0, tc_handler);
	/** Configure TC for a 4Hz frequency and trigger on RC compare. */
	tc_trigger_on_freq(TC0, 0, 4);
	/* Configure and enable interrupt on RC compare */
	tc_enable_it(TC0, 0, TC_IER_CPCS);
	aic_enable(ID_TC0);
	/* Start the counter */
	tc_start(TC0, 0);
}

/**
 *  Waits for the given number of milliseconds (using the dwTimeStamp generated
 *  by the SAM3's microcontrollers's system tick).
 *  \param delay  Delay to wait for, in milliseconds.
 */
static void _Wait(unsigned long delay)
{
	uint32_t start = dwTimeStamp;
	uint32_t elapsed;

	do {
		elapsed = dwTimeStamp;
		elapsed -= start;
	} while (elapsed < delay);
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief getting-started Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t status;

	/* Disable watchdog */
	WDT_Disable(WDT);

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

	/* Configure PIT. */
	printf("Configure PIT \n\r");
	configure_pit();

#ifdef CONFIG_HAVE_PMIC_ACT8945A
	status = ACT8945A_begin();
	if(status) printf("--E-- Error init ACT8945A \n\r");
	ACT8945A_set_regulator_voltage_out4to7 (V_OUT6, 2500);
	ACT8945A_set_regulator_state_out4to7 (V_OUT6, ACT8945A_REG_ON);
#endif


	//ACT8945A_test();

	/* PIO configuration for LEDs */
	printf("Configure LED PIOs.\n\r");
	configure_leds();
	led_set(LED_RED);
	_Wait(500);
	led_clear(LED_RED);

	/* PIO configuration for Buttons. */
	printf("Configure buttons with debouncing.\n\r");
	configure_buttons();

	/* Configure TC */
	printf("Configure TC.\n\r");
	configure_tc();

	led_status[LED_BLUE] = 1;
	check_hw_on_board();

	while (1) {;};
}
