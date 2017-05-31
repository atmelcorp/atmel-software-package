/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014-2016, Atmel Corporation
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
#include "trace.h"

#include "serial/console.h"

#include "irq/irq.h"
#include "peripherals/pmc.h"
#include "peripherals/rtc.h"
#include "peripherals/tcd.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** Main menu is being displayed. */
#define STATE_MENU              0
/** RTC mode is being edited. */
#define STATE_SET_MODE          1
/** Time is being edited. */
#define STATE_SET_TIME          2
/** Date is being edited. */
#define STATE_SET_DATE          3
/** Time alarm is being edited. */
#define STATE_SET_TIME_ALARM    4
/** Date alarm is being edited. */
#define STATE_SET_DATE_ALARM    5

/** Macro for check digit character */
#define is_digit(c) ((c) >= '0' && (c) <='9')

/** Macro for converting char to digit */
#define to_digit(c) ((c) - '0')

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

#ifdef CONFIG_HAVE_RTC_CALIBRATION
static struct _tcd_desc calibration_tc = {
        .addr = TC0,
        .channel = 0,
};
#endif

volatile uint16_t temperature = 0;
volatile uint32_t count_down_timer = 0;

/** Current state of application. */
static unsigned int state = STATE_MENU;

/** Indicates if alarm has been triggered and not yet cleared. */
static volatile bool alarm_triggered = false;

/** week string */
static const char* day_names[7] =
	{ "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

/** for idendify refreshing menu */
static volatile bool menu_shown = false;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static bool input_text_with_mask(char* input, const char* mask)
{
	char key;
	int i, len = strlen(mask);
	bool cancel = false;


	/* copy template into destination buffer */
	memcpy(input, mask, len + 1);


	for (i = 0; i < len; i++)
		console_put_char(input[i]);
	for (i = 0; i < len; i++)
		console_put_char('\b');

	i = 0;
	while (1) {
		while (!is_digit(input[i]) && i < len) {
			console_put_char(input[i]);
			i++;
		}

		key = console_get_char();

		/* validate input */
		if (key == '\r' || key == '\n')
			break;

		/* cancel input */
		if (key == '\033') {
			cancel = true;
			break;
		}

		/* DEL or BACKSPACE */
		if (key == 0x7f || key == 0x08) {
			while (i > 0) {
				i--;
				input[i] = mask[i];
				console_put_char('\b');
				console_put_char(input[i]);
				console_put_char('\b');

				if (is_digit(mask[i]))
					break;
			}
			continue;
		}

		if (is_digit(key) && is_digit(mask[i]) && i < len) {
			console_put_char(key);
			input[i++] = key;
		}
	}

	printf("\r\n");
	return !cancel;
}

/**
 * \brief Get new time, successful value is put in new_time.hour, new_time.min, new_time.sec.
 */
static bool get_new_time(struct _time* time)
{
	static const char mask[] = "00:00:00";
	char input[sizeof(mask) + 1];

	/* clear result variable */
	time->hour = time->min = time->sec = 0xff;

	if (!input_text_with_mask(input, mask))
		return false;

	time->hour = to_digit(input[0]) * 10 + to_digit(input[1]);
	time->min = to_digit(input[3]) * 10 + to_digit(input[4]);
	time->sec = to_digit(input[6]) * 10 + to_digit(input[7]);
	return true;
}

#ifdef CONFIG_HAVE_RTC_MODE_UTC
static bool get_new_utc_time(uint32_t* time)
{
	static const char mask[] = "00000000";
	char input[sizeof(mask) + 1];

	/* clear result variable */
	*time = 0xffffffff;

	if (!input_text_with_mask(input, mask))
		return false;

	*time = atoi(input);
	return true;
}
#endif

/**
 * \brief Calculate week from year, month,day.
 */
static int compute_week(int year, int month, int day)
{
	int week;

	if (month == 1 || month == 2) {
		month += 12;
		year--;
	}

	week = (day + 2 * month + 3 * (month + 1) / 5 + year + year / 4 -
		year / 100 + year / 400) % 7;
	week++;

	return week;
}

/**
 * \brief Get new date, successful value is put in new_date.year, new_date.month, new_date.day, new_date.week.
 */
static bool get_new_date(struct _date* date)
{
	static const char mask[] = "00/00/0000";
	char input[sizeof(mask) + 1];

	/* clear result variable */
	date->year = 0xffff;
	date->month = date->day = date->week = 0xff;

	if (!input_text_with_mask(input, mask))
		return false;

	/* MM-DD-YY */
	date->month = to_digit(input[0]) * 10 + to_digit(input[1]);
	date->day = to_digit(input[3]) * 10 + to_digit(input[4]);
	date->year = to_digit(input[6]) * 1000 + to_digit(input[7]) * 100 +
		to_digit(input[8]) * 10 + to_digit(input[9]);
	date->week = compute_week(date->year, date->month, date->day);

	return true;
}

/**
 * \brief Get new date, successful value is put in new_date.month, new_date.day.
 */
static bool get_new_alarm_date(struct _date* date)
{
	static const char mask[] = "00/00";
	char input[sizeof(mask) + 1];

	/* clear result variable */
	date->year = 0xffff;
	date->month = date->day = date->week = 0xff;

	if (!input_text_with_mask(input, mask))
		return false;

	/* MM-DD-YY */
	date->month = to_digit(input[0]) * 10 + to_digit(input[1]);
	date->day = to_digit(input[3]) * 10 + to_digit(input[4]);

	return true;
}

static void set_new_time(void)
{
	enum _rtc_mode mode = rtc_get_mode();

	switch (mode) {
#ifdef CONFIG_HAVE_RTC_MODE_UTC
	case RTC_MODE_UTC:
		{
			uint32_t new_utc_time;
			printf("\r\n\r\n Set utc format decimal time: ");
			if (get_new_utc_time(&new_utc_time))
				if (rtc_set_utc_time (new_utc_time))
					printf("\r\n UTC Time not set, invalid input!\n\r");
		}
		break;
#endif
#ifdef CONFIG_HAVE_RTC_MODE_PERSIAN
	case RTC_MODE_PERSIAN:
#endif
	case RTC_MODE_GREGORIAN:
		{
			struct _time new_time;
			printf("\r\n\r\n Set time (HH:MM:SS): ");
			if (get_new_time(&new_time))
				if (rtc_set_time(&new_time))
					printf("\r\n Time not set, invalid input!\n\r");
		}
		break;
	}
}

static void set_new_time_alarm(void)
{
	enum _rtc_mode mode = rtc_get_mode();

	switch (mode) {
#ifdef CONFIG_HAVE_RTC_MODE_UTC
	case RTC_MODE_UTC:
		{
			uint32_t new_utc_alarm_time;
			printf("\r\n\r\n Set utc format decimal alarm time: ");
			if (get_new_utc_time(&new_utc_alarm_time))
				if (rtc_set_utc_time_alarm(new_utc_alarm_time))
					printf("\r\n UTC Alarm Time not set, invalid input!\n\r");
		}
		break;
#endif
#ifdef CONFIG_HAVE_RTC_MODE_PERSIAN
	case RTC_MODE_PERSIAN:
#endif
	case RTC_MODE_GREGORIAN:
		{
			struct _time new_time;
			printf("\r\n\r\n Set time alarm (HH:MM:SS): ");
			if (get_new_time(&new_time)) {
				if (rtc_set_time_alarm(&new_time))
					printf("\r\n Time alarm not set, invalid input!\r\n");
				else
					printf("\r\n Time alarm is set at %02d:%02d:%02d!",
							new_time.hour, new_time.min, new_time.sec);
			}
		}
		break;
	}
}

static void set_new_date(void)
{
	enum _rtc_mode mode = rtc_get_mode();

	switch (mode) {
#ifdef CONFIG_HAVE_RTC_MODE_UTC
	case RTC_MODE_UTC:
		// nothing
		break;
#endif
#ifdef CONFIG_HAVE_RTC_MODE_PERSIAN
	case RTC_MODE_PERSIAN:
#endif
	case RTC_MODE_GREGORIAN:
		{
			struct _date new_date;
			printf("\r\n\r\n Set date (MM/DD/YYYY): ");
			if (get_new_date(&new_date))
				if (rtc_set_date(&new_date))
					printf("\r\n Date not set, invalid input!\r\n");
		}
		break;
	}
}

static void set_new_date_alarm(void)
{
	enum _rtc_mode mode = rtc_get_mode();

	switch (mode) {
#ifdef CONFIG_HAVE_RTC_MODE_UTC
	case RTC_MODE_UTC:
		// nothing
		break;
#endif
#ifdef CONFIG_HAVE_RTC_MODE_PERSIAN
	case RTC_MODE_PERSIAN:
#endif
	case RTC_MODE_GREGORIAN:
		{
			struct _date new_date;
			printf("\r\n\r\n Set date alarm (mm/dd): ");
			if (get_new_alarm_date(&new_date)) {
				if (rtc_set_date_alarm(&new_date))
					printf("\r\n Date alarm not set, invalid input!\r\n");
				else
					printf("\r\n Date alarm is set on %02d/%02d!",
						new_date.month, new_date.day);
			}
			alarm_triggered = false;
		}
		break;
	}
}

/**
 * \brief Displays the user interface on the terminal.
 */
static void _refresh_display(void)
{
	struct _time current_time;
	struct _date current_date;
#ifdef CONFIG_HAVE_RTC_MODE_UTC
	enum _rtc_mode mode = rtc_get_mode();
#endif

	/* not in menu display mode, in set mode */
	if (state == STATE_MENU) {
		/* display */
		if (!menu_shown) {
			printf("\r\nMenu:\r\n");
#if defined(CONFIG_HAVE_RTC_MODE_PERSIAN) || defined(CONFIG_HAVE_RTC_MODE_UTC)
			printf("  g - Set time mode to Gregorian calendar.\r\n");
#endif
#ifdef CONFIG_HAVE_RTC_MODE_PERSIAN
			printf("  b - Set time mode to Persian calendar.\r\n");
#endif
#ifdef CONFIG_HAVE_RTC_MODE_UTC
			printf("  u - Set time mode to UTC.\r\n");
			if (mode != RTC_MODE_UTC) {
#endif
				printf("  d - Set date\r\n");
				printf("  m - Set date alarm\r\n");
#ifdef CONFIG_HAVE_RTC_MODE_UTC
			}
#endif
			printf("  t - Set time\r\n");
			printf("  i - Set time alarm\r\n");
#ifdef CONFIG_HAVE_RTC_CALIBRATION
			printf("  p - PPM calibration of RTC\r\n");
#endif
			if (alarm_triggered)
				printf("  c - Clear alarm notification\r\n");
			printf("\r\n");
			menu_shown = true;
		}

		/* update current date and time */
#ifdef CONFIG_HAVE_RTC_MODE_UTC
		if (mode == RTC_MODE_UTC) {
			uint32_t utc_time;
			rtc_get_utc_time(&utc_time);
			printf("\r[UTC Time: %u seconds elapsed]%s",
					(unsigned)utc_time,
					alarm_triggered ? "[Alarm Triggered]" : "");
		} else
#endif
		{
			rtc_get_time(&current_time);
			rtc_get_date(&current_date);
			printf("\r[Date/Time: %s %02d/%02d/%04d %02d:%02d:%02d]%s",
					day_names[current_date.week - 1],
					current_date.month, current_date.day, current_date.year,
					current_time.hour, current_time.min, current_time.sec,
					alarm_triggered ? "[Alarm Triggered]" : "");
		}
	}
}

/**
 * \brief Interrupt handler for the RTC. Refreshes the display.
 */
static void rtc_handler(uint32_t source, void* user_arg)
{
	bool need_display_refresh = false;
	uint32_t status = RTC->RTC_SR;

	/* Second increment interrupt */
	if ((status & RTC_SR_SEC) == RTC_SR_SEC) {
		RTC->RTC_SCCR = RTC_SCCR_SECCLR;
		need_display_refresh = true;
	}

	/* Time or date alarm */
	if ((status & RTC_SR_ALARM) == RTC_SR_ALARM) {
		alarm_triggered = true;
		need_display_refresh = true;
		menu_shown = false; /* force display */
		RTC->RTC_SCCR = RTC_SCCR_ALRCLR;
	}

	if (need_display_refresh)
		_refresh_display();
}

#ifdef CONFIG_HAVE_RTC_CALIBRATION

/**
 *  Interrupt handler for TC0 interrupt. resets wdt at different period depending on user input
 */
static int calibration_tc_handler(void* arg, void* arg2)
{
	 // Recalibrate at every 1 minute
	if (count_down_timer >= 60) {
		rtc_calibration(temperature);
		trace_info("RTC has been re-calibrated \r\n");
		count_down_timer = 0;
	}
	count_down_timer++;

	return 0;
}

static void disable_calibration_tc(void)
{
	tcd_stop(&calibration_tc);
}

static void enable_calibration_tc(void)
{
	struct _callback _cb;

	callback_set(&_cb, calibration_tc_handler, NULL);

	count_down_timer = 0;
	tcd_start(&calibration_tc, &_cb);
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
	uint8_t key;

	/* Output example information */
	console_example_info("RTC Example");

	/* put 25 degree celsius as a default temp since there is no temperature sensor */
	temperature = 25;

	/* Default RTC configuration */
	rtc_set_mode(RTC_MODE_GREGORIAN); /* set Gregorian mode */
	rtc_set_hour_mode(RTC_HOUR_MODE_24); /* 24-hour mode */
	struct _time empty_time = { 0, 0, 0 };
	if (rtc_set_time_alarm(&empty_time))
		printf("\r\n Disable time alarm fail!");
	struct _date empty_date = { 0, 0, 0 };
	if (rtc_set_date_alarm(&empty_date))
		printf("\r\n Disable date alarm fail!");

#ifdef CONFIG_HAVE_RTC_CALIBRATION
	printf("Configuring TC for periodic re-calibration.\r\n");
	tcd_configure_counter(&calibration_tc, 0, 1); /* 1 Hz */
	enable_calibration_tc();
	rtc_calibration(temperature);
#endif

	/* Refresh display once */
	alarm_triggered = false;
	menu_shown = false;
	_refresh_display();

	/* Configure RTC interrupts */
	irq_add_handler(ID_RTC, rtc_handler, NULL);
	rtc_enable_it(RTC_IER_SECEN | RTC_IER_ALREN);
	irq_enable(ID_RTC);

	/* Handle keypresses */
	while (1) {
		key = console_get_char();

		disable_calibration_tc();

		switch (key) {
#if defined(CONFIG_HAVE_RTC_MODE_PERSIAN) || defined(CONFIG_HAVE_RTC_MODE_UTC)
		case 'g':
		case 'G':
			state = STATE_SET_MODE;
			rtc_set_mode(RTC_MODE_GREGORIAN);
			printf("\r\n\r\n Set time mode (Gregorian calendar)");
			break;
#endif /* CONFIG_HAVE_RTC_MODE_PERSIAN || CONFIG_HAVE_RTC_MODE_UTC */
#ifdef CONFIG_HAVE_RTC_MODE_PERSIAN
		case 'b':
		case 'B':
			state = STATE_SET_MODE;
			rtc_set_mode(RTC_MODE_PERSIAN);
			printf("\r\n\r\n Set time mode (Persian calendar)");
			break;
#endif /* CONFIG_HAVE_RTC_MODE_PERSIAN */
#ifdef CONFIG_HAVE_RTC_MODE_UTC
		case 'u':
		case 'U':
			state = STATE_SET_MODE;
			rtc_set_mode(RTC_MODE_UTC);
			printf("\r\n\r\n Set time mode(UTC format)");
			break;
#endif /* CONFIG_HAVE_RTC_MODE_UTC */
		/* set time */
		case 't':
		case 'T':
			state = STATE_SET_TIME;
			set_new_time();
			break;
#ifdef CONFIG_HAVE_RTC_CALIBRATION
		/* clock calibration */
		case 'p':
		case 'P':
			rtc_calibration(30);
			break;
#endif /* CONFIG_HAVE_RTC_CALIBRATION */
		/* set date */
		case 'd':
		case 'D':
			state = STATE_SET_DATE;
			set_new_date();
			break;
		/* set time alarm */
		case 'i':
		case 'I':
			state = STATE_SET_TIME_ALARM;
			set_new_time_alarm();
			break;
		/* set date alarm */
		case 'm':
		case 'M':
			state = STATE_SET_DATE_ALARM;
			set_new_date_alarm();
			break;
		/* clear trigger flag */
		case 'c':
		case 'C':
			alarm_triggered = false;
			break;
		}

		state = STATE_MENU;
		menu_shown = false;
		_refresh_display();
		enable_calibration_tc();
	}
}
