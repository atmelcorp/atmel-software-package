/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, Atmel Corporation
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
 * \page rtc RTC Example
 *
 * \section Purpose
 *
 * This basic example shows how to use the Real-Time Clock (RTC) peripheral
 * available on the Atmel SAMA5D microcontrollers. The RTC enables easy
 * time and date management and allows the user to monitor events like a
 * configurable alarm, second change, and calendar change.
 *
 * \section Requirements
 *
 * This package can be used with SAMA5D4-EK and SAMA5D4-XULT. Refer to \ref rtc_requirement for detail.
 *
 * \section Description
 *
 * Upon startup, the program displays the currently set time and date
 * and a menu to perform the following:
 *     \code
 *     Menu:
 *        t - Set time
 *        d - Set date
 *        i - Set time alarm
 *        m - Set date alarm
 *        c - Clear the alarm notification (only if it has been triggered)
 *     \endcode
 *
 * Setting the time, date and time alarm is done by using Menu option "t", "d",
 * the display is updated accordingly.
 *
 * The time alarm is triggered only when the second, minute and hour match the preset
 * values; the date alarm is triggered only when the month and date match the preset
 * values. If both time alarm and date alarm are set, only when the second, minute,
 * hour, month and date match the preset values, the alarm will be triggered.
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board. Please
 *    refer to the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *    SAM-BA User Guide</a>, the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *    GNU-Based Software Development</a> application note or to the
 *    <a href="http://www.iar.com/website1/1.0.1.0/78/1/">
 *    IAR EWARM User and reference guides</a>, depending on your chosen solution.
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
 *     -- RTC Example xxx --
 *     -- xxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *
 *     Menu:
 *     t - Set time
 *     d - Set date
 *     i - Set time alarm
 *     m - Set date alarm
 *     q - Quit
 *    \endcode
 * -# Press one of the keys listed in the menu to perform the corresponding action.
 *
 * \section References
 * - rtc/main.c
 * - rtc.c
 * - rtc.h
 */

/**
 * \file
 *
 * This file contains all the specific code for the rtc example.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "misc/console.h"
#include "peripherals/rtc.h"
#include "peripherals/tc.h"
#include "peripherals/pmc.h"
#include "peripherals/aic.h"
#include "trace.h"

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** Main menu is being displayed. */
#define STATE_MENU              0
/** Time is being edited. */
#define STATE_SET_TIME          1
/** Date is being edited. */
#define STATE_SET_DATE          2
/** Time alarm is being edited. */
#define STATE_SET_TIME_ALARM    3
/** Date alarm is being edited. */
#define STATE_SET_DATE_ALARM    4
/** Wave generating is being edited. */
#define STATE_WAVEFORM            5

/** Maximum size of edited string */
#define MAX_EDIT_SIZE       10

/** Macro for check digit character */
#define is_digit(c) ((c) >= '0' && (c) <='9')
/** Macro for converting char to digit */
#define to_digit(c) ((c) - '0')
/** (SCR) Sleep deep bit */
#define SCR_SLEEPDEEP   (0x1 <<  2)

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/
volatile uint16_t Temperature = 0;
volatile uint32_t CountDownTimer = 0;
/** Current state of application. */
static unsigned int bState = STATE_MENU;

/** Edited time */
struct _time new_time;

/** Edited date */
struct _date new_date;

/** Indicates if alarm has been triggered and not yet cleared. */
static unsigned char alarmTriggered = 0;

/** store time string */
static char rtc_time[8 + 1] = { '0', '0', ':', '0', '0', ':', '0', '0', '\0' };

/** store date string */
static char date[10 + 1] =
    { '0', '0', '/', '0', '0', '/', '0', '0', '0', '0', '\0' };
/** week string */
static char pDayNames[7][4] =
    { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
/** console erase sequence */
static char pEraseSeq[] = "\b \b";
/** output format string buffer */
static char calendar[80];
/** for idendify refreshing menu */
static unsigned int bMenuShown = 0;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Print a formatted string into a buffer.
 */
static signed int print_to_buf(char *pBuf, const char *pFormat, ...)
{
	va_list ap;
	signed int rc;

	va_start(ap, pFormat);
	rc = vsprintf(pBuf, pFormat, ap);
	va_end(ap);

	return rc;
}

/**
 * \brief Get new time, successful value is put in new_time.hour, new_time.min, new_time.sec.
 */
static int get_new_time(void)
{
	char ucKey;
	int i = 0;

	/* clear setting variable */
	new_time.hour = new_time.min = new_time.sec = 0xFF;

	/* use time[] as a format template */
	while (1) {
		ucKey = console_get_char();

		/* end input */
		if (ucKey == 0x0d || ucKey == 0x0a) {
			printf("\r\n");
			break;
		}

		/* DEL or BACKSPACE */
		if (ucKey == 0x7f || ucKey == 0x08) {
			if (i > 0) {
				/* end of time[], index then one more back */
				if (!rtc_time[i]) {
					--i;
				}

				printf(pEraseSeq);
				--i;

				/* delimitor ':' for time is uneditable */
				if (!is_digit(rtc_time[i]) && i > 0) {
					printf(pEraseSeq);
					--i;
				}
			}
		}

		/* end of time[], no more input except above DEL/BS or enter to end */
		if (!rtc_time[i]) {
			continue;
		}

		if (!is_digit(ucKey)) {
			continue;
		}

		console_put_char(ucKey);
		rtc_time[i++] = ucKey;

		/* ignore non digit position if not end */
		if (!is_digit(rtc_time[i]) && i < 8) {
			console_put_char(rtc_time[i]);
			++i;
		}
	}

	if (i == 0) {
		return 0;
	}

	if (i != 0 && rtc_time[i] != '\0') {
		return 1;	/* failure input */
	}

	new_time.hour = to_digit(rtc_time[0]) * 10 + to_digit(rtc_time[1]);
	new_time.min = to_digit(rtc_time[3]) * 10 + to_digit(rtc_time[4]);
	new_time.sec = to_digit(rtc_time[6]) * 10 + to_digit(rtc_time[7]);

	/* success input. verification of data is left to RTC internal Error Checking */
	return 0;
}

/**
 * \brief Calculate week from year, month,day.
 */
static char compute_week(int year, int month, int day)
{
	char week;

	if (month == 1 || month == 2) {
		month += 12;
		--year;
	}

	week =
	    (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 -
	     year / 100 + year / 400) % 7;

	++week;

	return week;
}

/**
 * \brief Get new time, successful value is put in new_date.year, new_date.month, new_date.day, new_date.week.
 */
static int get_new_date(void)
{
	char ucKey;
	int i = 0;

	/* clear setting variable */
	new_date.year = 0xFFFF;
	new_date.month = new_date.day = new_date.week = 0xFF;

	/* use time[] as a format template */
	while (1) {
		ucKey = console_get_char();

		/* end input */
		if (ucKey == 0x0d || ucKey == 0x0a) {
			printf("\r\n");
			break;
		}

		/* DEL or BACKSPACE */
		if (ucKey == 0x7f || ucKey == 0x08) {
			if (i > 0) {
				/* end of date[], index then one more back */
				if (!date[i]) {
					--i;
				}

				printf(pEraseSeq);
				--i;

				/* delimitor '/' for date is uneditable */
				if (!is_digit(date[i]) && i > 0) {
					printf(pEraseSeq);
					--i;
				}
			}
		}

		/* end of time[], no more input except above DEL/BS or enter to end */
		if (!date[i]) {
			continue;
		}

		if (!is_digit(ucKey)) {
			continue;
		}

		console_put_char(ucKey);
		date[i++] = ucKey;

		/* ignore non digit position */
		if (!is_digit(date[i]) && i < 10) {
			console_put_char(date[i]);
			++i;
		}
	}

	if (i == 0) {
		return 0;
	}

	if (i != 0 && date[i] != '\0' && i != 6) {
		return 1;	/* failure input */
	}

	/* MM-DD-YY */
	new_date.month = to_digit(date[0]) * 10 + to_digit(date[1]);
	new_date.day = to_digit(date[3]) * 10 + to_digit(date[4]);
	/* not scenario of getting mm/dd/ only for alarm */
	if (i != 6) {
		new_date.year =
		    to_digit(date[6]) * 1000 + to_digit(date[7]) * 100 +
		    to_digit(date[8]) * 10 + to_digit(date[9]);
		new_date.week = compute_week(new_date.year, new_date.month, new_date.day);
	}

	/* success input. verification of data is left to RTC internal Error Checking */
	return 0;
}

/**
 * \brief Displays the user interface on the terminal.
 */
static void _RefreshDisplay(void)
{
	struct _time current_time;
	/* unsigned char hour, minute, second; */
	struct _date current_date;
	/* unsigned short year; */
	/* unsigned char month, day, week; */

	/* not in menu display mode, in set mode */
	if (bState == STATE_MENU) {
		/* Retrieve date and time */
		rtc_get_time(&current_time);
		rtc_get_date(&current_date);

		/* display */
		if (!bMenuShown) {
			printf("\r\nMenu:\r\n");
			printf("  t - Set time\r\n");
			printf("  d - Set date\r\n");
			printf("  i - Set time alarm\r\n");
			printf("  m - Set date alarm\r\n");
#ifdef CONFIG_HAVE_RTC_CALIBRATION
			printf("  p - PPM calibration of RTC\r\n");
#endif

			if (alarmTriggered) {
				printf("  c - Clear alarm notification\r\n");
			}

			printf("  q - Quit!\r\n");

			printf("\r\n");

			bMenuShown = 1;
		}

		/* update current date and time */
		print_to_buf(rtc_time, "%02d:%02d:%02d", current_time.hour, current_time.min, current_time.sec);
		print_to_buf(date, "%02d/%02d/%04d", current_date.month, current_date.day, current_date.year);
		print_to_buf(calendar, " [Time/Date: %s, %s %s ][Alarm status:%s]",
			  rtc_time, date, pDayNames[current_date.week - 1],
			  alarmTriggered ? "Triggered!" : "");

		printf("\r%s", calendar);
	}
}

/**
 * \brief Interrupt handler for the RTC. Refreshes the display.
 */
static void sysc_handler(void)
{
	uint32_t dwStatus = RTC->RTC_SR;

	/* Second increment interrupt */
	if ((dwStatus & RTC_SR_SEC) == RTC_SR_SEC) {
		/* Disable RTC interrupt */
		rtc_disable_it(RTC_IDR_SECDIS);

		_RefreshDisplay();

		RTC->RTC_SCCR = RTC_SCCR_SECCLR;

		rtc_enable_it(RTC_IER_SECEN);
	}
	/* Time or date alarm */
	else {
		if ((dwStatus & RTC_SR_ALARM) == RTC_SR_ALARM) {
			/* Disable RTC interrupt */
			rtc_disable_it(RTC_IDR_ALRDIS);

			alarmTriggered = 1;
			_RefreshDisplay();
			printf("\t Done \r");
			/* shown additional menu item for clear notification */
			bMenuShown = 0;
			RTC->RTC_SCCR = RTC_SCCR_ALRCLR;

			rtc_enable_it(RTC_IER_ALREN);
		}
	}
}

#ifdef CONFIG_HAVE_RTC_CALIBRATION

/**
 *  Interrupt handler for TC0 interrupt. resets wdt at different period depending on user input
 */
static void calibration_tc_handler(void)
{
	/* Clear status bit to acknowledge interrupt */
	tc_get_status(TC0, 0);

	 // Recalibrate at every 1 minute
	if (CountDownTimer >= 60) {
		rtc_calibration(Temperature);
		trace_info("RTC has been re-calibrated \r\n");
		CountDownTimer = 0;
	}
	CountDownTimer++;
}

/**
 *  Configure Timer Counter 0 to generate an interrupt every 250ms.
 */
static void configure_calibration_tc(void)
{
	/** Enable peripheral clock. */
	pmc_enable_peripheral(ID_TC0);

	/* Put the source vector */
	aic_set_source_vector(ID_TC0, calibration_tc_handler);

	/** Configure TC for a 4Hz frequency and trigger on RC compare. */
	tc_trigger_on_freq(TC0, 0, 1);

	/* Configure and enable interrupt on RC compare */
	tc_enable_it(TC0, 0, TC_IER_CPCS);
	aic_enable(ID_TC0);

	/* Start the counter */
	tc_start(TC0, 0);
}

static void disable_calibration_tc(void)
{
	tc_stop(TC0, 0);
}

static void enable_calibration_tc(void)
{
	CountDownTimer = 0;
	tc_start(TC0, 0);
}

#else /* CONFIG_HAVE_RTC_CALIBRATION */

static void disable_calibration_tc(void) { }
static void enable_calibration_tc(void) { }

#endif /* !CONFIG_HAVE_RTC_CALIBRATION */

/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Application entry point for RTC example.
 *
 * \return Unused (ANSI-C compatibility).
 */

int main(void)
{
	uint8_t ucKey;

	/* Output example information */
	console_example_info("RTC Example");

	// put 25 °C as a default temp, if there is no temprature sensor
	Temperature = 25;

	/* Default RTC configuration */
	rtc_set_hour_mode(0);	/* 24-hour mode */
	struct _time empty_time = {0,0,0};
	if (rtc_set_time_alarm(&empty_time)) {
		printf("\r\n Disable time alarm fail!");
	}
	struct _date empty_date = {0,0,0};
	if (rtc_set_date_alarm(&empty_date)) {
		printf("\r\n Disable date alarm fail!");
	}

#ifdef CONFIG_HAVE_RTC_CALIBRATION
	printf("Configuring TC for periodic re-calibration.\r\n");
	configure_calibration_tc();
	rtc_calibration(Temperature);
#endif

	/* Configure RTC interrupts */
	rtc_enable_it(RTC_IER_SECEN | RTC_IER_ALREN);
	aic_set_source_vector(ID_RTC, sysc_handler);
	aic_enable(ID_RTC);

	/* Refresh display once */
	_RefreshDisplay();
	new_time.hour = 0;
	new_time.min = 0;
	new_time.sec = 30;
	rtc_set_time_alarm(&new_time);
	bMenuShown = 0;
	alarmTriggered = 0;

	/* Handle keypresses */
	while (1) {
		ucKey = console_get_char();

		/* set time */
		if (ucKey == 't') {
			bState = STATE_SET_TIME;
			disable_calibration_tc();

			do {
				printf("\r\n\r\n Set time(hh:mm:ss): ");
			} while (get_new_time());

			/* if valid input, none of variable for time is 0xff */
			if (new_time.hour != 0xFF) {
				if (rtc_set_time (&new_time)) {
					printf
					    ("\r\n Time not set, invalid input!\n\r");
				}
			}

			bState = STATE_MENU;
			bMenuShown = 0;
			_RefreshDisplay();
			enable_calibration_tc();
		}

#ifdef CONFIG_HAVE_RTC_CALIBRATION
		/* clock calibration */
		else if (ucKey == 'p') {

			rtc_calibration(30);

			bState = STATE_MENU;
			bMenuShown = 0;
			_RefreshDisplay();
		}
#endif /* CONFIG_HAVE_RTC_CALIBRATION */

		/* set date */
		else if (ucKey == 'd') {
			bState = STATE_SET_DATE;
			aic_disable(ID_TC0);

			do {
				printf("\r\n\r\n Set date(mm/dd/yyyy): ");
			} while (get_new_date());

			/* if valid input, none of variable for date is 0xff(ff) */
			if (new_date.year != 0xFFFF) {
				if (rtc_set_date(&new_date)) {
					printf
					    ("\r\n Date not set, invalid input!\r\n");
				}
			}

			/* only 'mm/dd' inputed */
			if (new_date.month != 0xFF && new_date.year == 0xFFFF) {
				printf("\r\n Not Set for no year field!\r\n");
			}

			bState = STATE_MENU;
			bMenuShown = 0;
			CountDownTimer = 0;
			aic_enable(ID_TC0);
			_RefreshDisplay();
		}

		/* set time alarm */
		else if (ucKey == 'i') {
			bState = STATE_SET_TIME_ALARM;
			aic_disable(ID_TC0);

			do {
				printf("\r\n\r\n Set time alarm(hh:mm:ss): ");
			} while (get_new_time());

			if (new_time.hour != 0xFF) {
				if (rtc_set_time_alarm(&new_time)) {
					printf
					    ("\r\n Time alarm not set, invalid input!\r\n");
				} else {
					printf
					    ("\r\n Time alarm is set at %02d:%02d:%02d!",
					     new_time.hour, new_time.min, new_time.sec);
				}
			}
			bState = STATE_MENU;
			bMenuShown = 0;
			alarmTriggered = 0;
			CountDownTimer = 0;
			aic_enable(ID_TC0);
			_RefreshDisplay();
		}

		/* set date alarm */
		else if (ucKey == 'm') {
			bState = STATE_SET_DATE_ALARM;
			aic_disable(ID_TC0);

			do {
				printf("\r\n\r\n Set date alarm(mm/dd/): ");
			} while (get_new_date());

			if (new_date.year == 0xFFFF && new_date.month != 0xFF) {
				if (rtc_set_date_alarm(&new_date)) {
					printf
					    ("\r\n Date alarm not set, invalid input!\r\n");
				} else {
					printf
					    ("\r\n Date alarm is set on %02d/%02d!",
					     new_date.month, new_date.day);
				}

			}
			bState = STATE_MENU;
			bMenuShown = 0;
			alarmTriggered = 0;
			CountDownTimer = 0;
			aic_enable(ID_TC0);
			_RefreshDisplay();
		}

		/* clear trigger flag */
		else if (ucKey == 'c') {
			alarmTriggered = 0;
			bMenuShown = 0;
			_RefreshDisplay();
		}

		/* quit */
		else if (ucKey == 'q') {
			break;
		}
	}

	return 0;
}
