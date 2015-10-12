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
#include "trace.h"
#include "compiler.h"

#include "cortex-a/mmu.h"

#include "peripherals/aic.h"
#include "peripherals/pmc.h"
#include "peripherals/wdt.h"
#include "peripherals/pio.h"
#include "peripherals/tc.h"
#include "peripherals/pit.h"
#include "peripherals/twid.h"
#include "peripherals/rtc.h"
#include "peripherals/shdwc.h"

#include "misc/led.h"
#include "misc/console.h"
#include "utils/timer.h"

#include "power/act8945a.h"
#include "video/lcdd.h"
#include "utils/widget.h"

#include "mxt_device.h"

#include "test_lcd.h"
#include "test_rtc.h"
#include "board_info.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
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

volatile bool led_status[MAX_LEDS];

char buf[64] = {0};

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief Process Buttons Events
 *
 */
static void process_button_evt(uint8_t bt)
{
	printf(" PushButton %x\n\r", bt);
}

/**
 *  \brief Handler for Buttons rising edge interrupt.
 *
 */
static void push_button_handler(uint32_t mask, uint32_t status, void* user_arg)
{
	int i = 0;
	(void)user_arg;
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
		/* Adjust pio debounce filter parameters, uses 1 Hz filter. */
		pio_set_debounce_filter(&button_pins[i], 1);
		/* Initialize pios interrupt with its handlers */
		pio_configure_it(&button_pins[i]);
		pio_add_handler_to_group(button_pins[i].group,
					 button_pins[i].mask,
					 push_button_handler,
					 NULL);
		pio_enable_it(button_pins);
	}
}

/**
 *  \brief Configure the Leds
 *
 */
static void configure_leds(void)
{
	uint8_t i = 0;
	for (i = 0; i<MAX_LEDS; ++i) {
		led_configure(i);
		led_status[i] = 0;
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

struct _text txt = {
	.org.x = 380, // with font 8x8
	.org.y = 2,
	.size.w = 0,
	.size.h = 0,
	.font_sel = FONT8x8,
	.bg_color = COLOR_BLUE,
	.txt_color = COLOR_WHITE
};

void _display_hms (struct _time* mtu)
{
	//display_hms(LCDD_BASE, mtu);
	sprintf(buf, " %02dh%02dm%02ds ", mtu->hour, mtu->min, mtu->sec);
	display_widget_string_on_layer(LCDD_BASE, &txt, buf);
}


#define VREF	3.3
#define VBAT	4.2
#define SAMPLE	4096


void display_adc_value (void)
{
	float x;

	x = (float)get_adc_conv(0);
	x = x * (VBAT / SAMPLE) ;
	printf(" CH0 %.03f v",x);
	x = get_adc_conv(1);
	x = x * (VREF / SAMPLE) ;
	printf(" CH1 %.03f v",x);
	printf("\r");
	/* restart conversion */
	x = get_adc_conv(0xFF);
}


/**
 *  Launch power down if Low Battery Output detected.
 */
void _launch_power_down (void)
{
		printf("\r\n *** Starting Shutdown Mode *** \r\n");
		shdwc_configure_wakeup_mode(SHDW_MR_LPDBCEN0_ENABLE |
				SHDW_MR_LPDBC_2_RTCOUT0 |
				SHDW_MR_WKUPDBC_32_SLCK);
		shdwc_set_wakeup_input(SHDW_WUIR_WKUPEN0_ENABLE,
				SHDW_WUIR_WKUPT0_LOW);
		shdwc_do_shutdown();
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

extern enum status_code launch_mxt_device (void);

/**
 *  \brief getting-started Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t status, frtc;
	struct _time LMTU;

	/* Disable watchdog */
	wdt_disable();

	/* Disable all PIO interrupts */
	pio_reset_all_it();

	/* Initialize console */
	console_configure(CONSOLE_BAUDRATE);
	console_clear_screen();
	console_reset_cursor();

	/* Configure PIT. Must be always ON, used for delay */
	printf("Configure PIT \n\r");
	timer_configure(BLINK_PERIOD);

#ifdef CONFIG_HAVE_PMIC_ACT8945A
	pio_configure(act8945a_pins, ARRAY_SIZE(act8945a_pins));
	if (act8945a_configure(&act8945a, &act8945a_twid)) {
		act8945a_set_regulator_voltage(&act8945a, 6, 2500);
		act8945a_enable_regulator(&act8945a, 6, true);
		act8945a_set_regulator_voltage(&act8945a, 7, 1800);
		act8945a_enable_regulator(&act8945a, 7, true);
	} else {
		printf("--E-- Error initializing ACT8945A PMIC\n\r");
	}
#endif

	/* PIO configuration for LEDs */
	printf("Configure LED PIOs.\n\r");
	configure_leds();
	led_set(LED_GREEN);
	timer_wait(500);
	led_clear(LED_GREEN);
	led_status[LED_BLUE] = 1;

	/* PIO configuration for Buttons. */
	printf("Configure buttons with debouncing.\n\r");
	configure_buttons();
	/* Configure TC */
	printf("Configure TC.\n\r");
	configure_tc();
	/* Configure RTC */
	printf("Configure Real Time Clock.\n\r");
	configure_rtc();

	status = check_hw_on_board();
	if (status) {
		led_status[LED_BLUE] = 0;
		led_clear(LED_BLUE);
		led_status[LED_RED] = 1;
	}

	/*  */
	enum status_code mxt_status;
	mxt_status = launch_mxt_device();

	launch_adc();
	//test_adc();

	do {
		frtc = get_flag_rtc();
		if(frtc&RTC_SR_SEC) {
			/* ewery second */
			frtc &= ~RTC_SR_SEC;
			set_flag_rtc(frtc);
			rtc_get_time(&LMTU);
			_display_hms (&LMTU);

			display_adc_value();

			act8945a_display_charge_state(&act8945a);
			if(act8945a.lbo_count >= 10)
				_launch_power_down();
		}
		lcd_app_qtouch();

	} while(1);

}
