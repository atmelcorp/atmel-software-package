/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2018, Atmel Corporation
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
#include "trace.h"

#include "serial/console.h"

#include "irq/irq.h"
#include "peripherals/rtt.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** Device state: in the main menu. */
#define STATE_MAIN_MENU      0
/** Device state: user is setting an alarm time. */
#define STATE_SET_ALARM      1

/** ASCII char definition for backspace. */
#define ASCII_BS    8
/** ASCII char definition for carriage return. */
#define ASCII_CR    13

/** Current device state. */
volatile uint8_t state;

/** New alarm time being currently entered. */
volatile uint32_t new_alarm;

/** Indicate that an alarm has occurred but has not been cleared. */
volatile uint8_t alarmed;

/**
 * \brief Refresh display on terminal.
 *
 * Update the terminal display to show the current menu and the current time
 * depending on the device state.
 */
static void refresh_display(void)
{
	printf("%c[2J\r", 27);
	printf("Time: %u\n\r", (unsigned int)rtt_get_timer());

	/* Display alarm */
	if (alarmed) {
		printf("\r\n!!! ALARM !!!\r\n");
	}

	/* Main menu */
	if (state == STATE_MAIN_MENU) {
		printf("Menu:\n\r"
				" r - Reset timer\n\r"
				" s - Set alarm\r");
		if (alarmed) {
			printf(" c - Clear alarm notification\r");
		}
		printf("\n\rChoice? ");
	} else {
		if (state == STATE_SET_ALARM) {
			printf("Enter alarm time (recommend > current timer): ");
			if (new_alarm != 0) {
				printf("%u", (unsigned)new_alarm);
			}
		}
	}
}

/**
 * \brief RTT configuration function.
 *
 * Configure the RTT to generate a one second tick, which triggers the RTT
 * interrupt.
 */
static void configure_rtt(void)
{
	uint32_t previous_time;

	rtt_init(32768);
	previous_time = rtt_get_timer();
	while (previous_time == rtt_get_timer());
	rtt_enable_alarm_it();
	rtt_enable_timer_it();
}


/**
 * \brief Interrupt handler for the RTT.
 *
 * Display the current time on the terminal.
 */
static void rtt_handler(uint32_t source, void* user_arg)
{
	uint32_t status;

	/* Get RTT status */
	status = rtt_get_status();

	/* Time has changed, refresh display */
	if ((status & RTT_SR_RTTINC) == RTT_SR_RTTINC) {
		refresh_display();
	}

	/* Alarm */
	if ((status & RTT_SR_ALMS) == RTT_SR_ALMS) {
		alarmed = 1;
		refresh_display();
	}
}

/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Application entry point for RTT example.
 *
 * \return Unused (ANSI-C compatibility).
 */

int main(void)
{
	uint8_t key;

	/* Output example information */
	console_example_info("RTT Example");

	configure_rtt();
	/* Configure RTT interrupts */
	irq_add_handler(ID_RTT, rtt_handler, NULL);
	irq_enable(ID_RTT);

	/* Handle keypresses */
	while (1) {
		key = console_get_char();

		/* Main menu mode */
		if (state == STATE_MAIN_MENU) {
			/* Reset timer */
			if (key == 'r') {
				configure_rtt();
				refresh_display();
			} else if (key == 's') { /* Set alarm */
				state = STATE_SET_ALARM;
				new_alarm = 0;
				refresh_display();
			} else { /* Clear alarm */
				if ((key == 'c') && alarmed) {
					alarmed = 0;
					refresh_display();
				}
			}
		} else if (state == STATE_SET_ALARM) { /* Set alarm mode */
			/* Number */
			if ((key >= '0') && (key <= '9')) {
				new_alarm = new_alarm * 10 + key - '0';
				refresh_display();
			} else if (key == ASCII_BS) {
				printf("%c", key);
				new_alarm /= 10;
				refresh_display();
			} else if (key == ASCII_CR) {
				/* Avoid newAlarm = 0 case */
				if (new_alarm != 0) {
					rtt_set_time_alarm(new_alarm);
				}
				state = STATE_MAIN_MENU;
				refresh_display();
			}
		}
	}
}