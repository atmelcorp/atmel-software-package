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
#include "peripherals/tc.h"
#include "peripherals/rtc.h"

#include "cortex-a/mmu.h"
#include "misc/led.h"
#include "misc/console.h"

#include "power/act8945a.h"
#include "services/test_rtc.h"

#include "timer.h"

#include "trace.h"
#include "compiler.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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

volatile bool led_status[MAX_LEDS] = {0};

/** Global timestamp in milliseconds since start of application */
volatile uint32_t dwTimeStamp = 0;

static const struct _pin vbus_pin[] = PIN_USB_VBUS;

static const struct _pin en5v_usbb_pin[] = PIN_USB_POWER_ENB;


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
static void push_button_handler(uint32_t mask, uint32_t status)
{
	int i = 0;
	for (i = 0; i < ARRAY_SIZE(button_pins); ++i) {
		if (status & button_pins[i].mask)
			process_button_evt(i);
	}
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
	for (i = 0; i <  ARRAY_SIZE(button_pins); ++i)
	{
		/* Configure pios as inputs. */
		pio_configure(&button_pins[i], 1);
		/* Adjust pio debounce filter parameters, uses 10 Hz filter. */
		pio_set_debounce_filter(&button_pins[i], 10);
		/* Initialize pios interrupt with its handlers */
		pio_configure_it(&button_pins[i]);
		pio_add_handler_to_group(button_pins[i].group,
					 button_pins[i].mask, push_button_handler);
		pio_enable_it(button_pins);
	}
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

	if (led_status[LED_RED])
		led_toggle(LED_RED);
	if (led_status[LED_GREEN])
		led_toggle(LED_GREEN);
	if (led_status[LED_BLUE])
		led_toggle(LED_BLUE);
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
 *  Interrupt handler VBUS pin.
 */
static void vbus_change_handler(uint32_t mask, uint32_t status)
{
	uint8_t state = pio_get(&vbus_pin[0]);
	printf("Switching power USB mode:%1x \n\r", state);
}

/**
 *  Configure pin VBus change state
 */
static void configure_pin_vbus_state(void)
{
	/* Configure Pio and interrupt (both edge)*/
	pio_configure(&vbus_pin[0], 1);
	/* Adjust pio debounce filter parameters, uses 10 Hz filter. */
	pio_set_debounce_filter(&vbus_pin[0], 10);

	pio_configure_it(&vbus_pin[0]);
	pio_add_handler_to_group(vbus_pin[0].group, vbus_pin[0].mask, vbus_change_handler);
	pio_enable_it(&vbus_pin[0]);
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
	wdt_disable();

	/* Disable all PIO interrupts */
	pio_reset_all_it();

	/* Initialize console */
	console_configure(CONSOLE_BAUDRATE);
	/* Clear console */
	console_clear_screen();
	console_reset_cursor();

	/* Initialize pin Enable power USBB */
	pio_configure(&en5v_usbb_pin[0], 1);

#if defined (ddram)
	mmu_initialize((uint32_t *) 0x20C000);
	cp15_enable_mmu();
	cp15_enable_dcache();
	cp15_enable_icache();
#endif

	/* Configure PIT. */
	printf("Configure PIT \n\r");
	//configure_pit();
	timer_configure(BLINK_PERIOD);

#ifdef CONFIG_HAVE_PMIC_ACT8945A
	status = ACT8945A_begin();
	if(status) printf("--E-- Error init ACT8945A \n\r");
	ACT8945A_set_regulator_voltage_out4to7 (V_OUT6, 2500);
	ACT8945A_set_regulator_state_out4to7 (V_OUT6, ACT8945A_REG_ON);
	ACT8945A_set_regulator_voltage_out4to7 (V_OUT7, 1800);
	ACT8945A_set_regulator_state_out4to7 (V_OUT7, ACT8945A_REG_ON);
#endif

	test_flexcom_usart();


	/* PIO configuration for LEDs */
	printf("Configure LED PIOs.\n\r");
	led_configure(LED_GREEN);
	led_set(LED_GREEN);
	timer_wait(500);
	led_clear(LED_GREEN);

	/* PIO configuration for Buttons. */
	printf("Configure buttons with debouncing.\n\r");
	configure_buttons();

	/* Configure TC */
	printf("Configure TC.\n\r");
	configure_tc();

	led_configure(LED_BLUE);
	led_status[LED_BLUE] = 1;

	status = check_hw_on_board();

	led_configure(LED_RED);

	/* Configure interrupt on VBUS state change */
	configure_pin_vbus_state();

	/* Configure RTC */
	_configure_rtc();

	uint8_t frtc;
	struct _time LMTU;
	do {
		frtc = get_flag_rtc();
		if(frtc&RTC_SR_SEC) {
			frtc &= ~RTC_SR_SEC;
			set_flag_rtc(frtc);
			memset (&LMTU, 0xFF, sizeof(LMTU));
			rtc_get_time(&LMTU);
			printf("%02dh %02dm %02ds \n\r", LMTU.hour, LMTU.min, LMTU.sec);
		}
	} while(1);
}
