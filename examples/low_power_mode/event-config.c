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
/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "assert.h"
#include <stdio.h>

#include "board.h"
#include "irq/irq.h"
#include "gpio/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/rtc.h"
#include "event-config.h"

/*----------------------------------------------------------------------------
 *        Variables
 *----------------------------------------------------------------------------*/

#ifdef PINS_PUSHBUTTONS
/* Pushbutton \#1 pin instance. */
static const struct _pin button_pins[] = PINS_PUSHBUTTONS;
#endif

const char *event_menu[] = { 
					"user_btn:  Use PB_USER button to wake up",
					"rtc_int:   Auto wakeup by RTC interrupt after 3 second",
					"rtc_alarm: Auto wakeup by RTC alarm after 3 second",
					"wake_up:   Use WKUP button to wake up",
					NULL,
};

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------
 */

/**
 *  \brief Handler for Buttons rising edge interrupt.
 *
 *  Handle process led1 status change.
 */
#ifdef PINS_PUSHBUTTONS 
static void _pio_handler(uint32_t group, uint32_t status, void *user_arg)
{
	/* unused */
	(void)group;
	(void)user_arg;

	/* Handle process led1 status change: to do */

}
#endif

/**
 * \brief Interrupt handler for the RTC. Refreshes the display.
 */
static void _rtc_handler(uint32_t source, void* user_arg)
{
	uint32_t dwStatus = rtc_get_sr(0xffffffff);

	assert(source == ID_RTC);

	/* Second increment interrupt */
	if ((dwStatus & RTC_SR_SEC) == RTC_SR_SEC) {
		/* Disable RTC interrupt */
		rtc_disable_it(RTC_IDR_SECDIS);
		rtc_clear_sccr(RTC_SCCR_SECCLR);
	}
	/* Time or date alarm */
	else {
		if ((dwStatus & RTC_SR_ALARM) == RTC_SR_ALARM) {
			/* Disable RTC interrupt */
			rtc_disable_it(RTC_IDR_ALRDIS);
			rtc_clear_sccr(RTC_SCCR_ALRCLR);
		}
	}
}

/**
 * \brief Configure rtc event
 * wakup_in_seconds   set wait time
 * enable   true: enable rtc irq; false: disable rtc irq
 */
static void _start_rtc_timer_for_wakeup(unsigned int wakup_in_seconds, bool enable)
{
	struct _time new_time;

	rtc_disable_it(RTC_IER_SECEN | RTC_IER_ALREN);

	/* Default RTC configuration */
	/* 24-hour mode */
	rtc_set_hour_mode(RTC_HOUR_MODE_24);
	struct _time empty_time = {0, 0, 0};

	if (rtc_set_time_alarm(&empty_time))
		printf("\r\n Disable time alarm fail!");

	struct _date empty_date = {0, 0, 0};

	if (rtc_set_date_alarm(&empty_date))
		printf("\r\n Disable date alarm fail!");

	new_time.hour = 0;
	new_time.min = 0;
	new_time.sec = 0;
	rtc_set_time(&new_time);

	/* Configure RTC interrupts */
	if (enable == true) {
		rtc_enable_it(RTC_IER_ALREN);
		irq_add_handler(ID_RTC, _rtc_handler, NULL);
		irq_enable(ID_RTC);
	}

	new_time.hour = 0;
	new_time.min = 0;
	new_time.sec = wakup_in_seconds;
	rtc_set_time_alarm(&new_time);
}

/**
 *  \brief Configure the Pushbuttons
 *
 *  Configure the PIO as inputs and generate corresponding interrupt when
 *  pressed or released.
 */
static void _configure_buttons(void)
{
#ifdef PINS_PUSHBUTTONS 
	int i;

	/* Adjust pio debounce filter parameters, uses 10 Hz filter. */
	pio_set_debounce_filter(10);

	for (i = 0; i < ARRAY_SIZE(button_pins); ++i) {
		/* Configure pios as inputs. */
		pio_configure(&button_pins[i], 1);

		/* Initialize pios interrupt with its handlers, see */
		/* PIO definition in board.h. */
		pio_add_handler_to_group(button_pins[i].group,
			button_pins[i].mask, _pio_handler, NULL);
		/* Enable PIO line interrupts. */
		pio_enable_it(button_pins);
	}
#endif
}

/*----------------------------------------------------------------------------
 *        Exported function
 *----------------------------------------------------------------------------*/

void wakeup_event(uint32_t event){
	/* set wake up event */
	switch (event) {
	case USER_BTN:
		_configure_buttons();
		break;
	case RTC_INT:
		/* set RTC interrupt */
		_start_rtc_timer_for_wakeup(3, true);

		break;
	case RTC_ALARM:
		/* set RTC alarm */
		_start_rtc_timer_for_wakeup(3, false);

#if defined(PMC_FSMR_LPM) && defined(PMC_FSMR_RTCAL)
		/* config wake up sources */
		pmc_set_fast_startup_mode(PMC_FSMR_RTCAL | PMC_FSMR_LPM);
#elif defined(PMC_FSMR_RTCAL)
		pmc_set_fast_startup_mode(PMC_FSMR_RTCAL);
#endif
		break;
	case WAKE_UP:
		/* set WKUP0 pin */
#ifdef PMC_FSMR_LPM
		/* config wake up sources */
		pmc_set_fast_startup_mode(PMC_FSMR_FSTT0 | PMC_FSMR_LPM);
#endif
		break;
	default:
		break;
	}
}
