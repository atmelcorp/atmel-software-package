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
 *  \page wdt WatchDog timer example
 *
 *  \section Purpose
 *
 *  This application show how to configure different mode/interrupt of watchdog
 *  timer. This basic application can be configure to reset WDT at every fix
 *  period to restart it or it can be configured to interrupt before allowed
 *  window to generate error interrupt.
 *
 *  \section Description
 *
 *  The demonstration program reset WDT at regular interval without provoking any
 *  error underflow interrupt. User can choose to generate interrupt(underflow/error)
 *  and choose if WDT generates interrupt or resets the system.
 *  By default WDT is Counter value is set to 10 sec and Delta counter value is set
 *  to 6 sec and fault interrupt is enable and WDT reset disable.
 *  WDT values can not be changed or it can not be put to reset within first 4 sec
 *  (forbidden window)after it starts. Doing so will generate fault interrupt
 *  and it restart. Resetting WDT before it reaches zero and after 4 seconds has
 *  past will reset it properly without generating any fault or interrupt. If it
 *  does not get re-serviced before 10 seconds it will generate underflow error
 *  and depending on whether reset is enabled or not it will reset the system.
 *
 *  \section Usage
 *
 *  -# Build the program and download it inside the evaluation board. Please
 *     refer to the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *     SAM-BA User Guide</a>, the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *     GNU-Based Software Development</a>
 *     application note or to the
 *     <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *     IAR EWARM User Guide</a>,
 *     depending on your chosen solution.
 *  -# On the computer, open and configure a terminal application
 *     (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *    - 115200 bauds
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# Start the application.
 *  -# WDT starts with 10 sec count down timer and 6 sec of delta timer. Timer 0 is used
 *     to reset it at every 5 seconds.
 *     \code
 *      -- WDT Example xxx --
 *      -- SAMxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 *  -# By giving input "1", "2", "3" or "4" you can switch between different configurations
 *
 */

/** \file
 *
 *  This file contains all the specific code for the getting-started example.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "board.h"
#include "irq/irq.h"
#include "peripherals/pmc.h"
#include "peripherals/tcd.h"
#include "peripherals/wdt.h"
#include "serial/console.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/* Delays for watchdog (in milliseconds). */

#define WDT_DELTATIME 6000 /* 6 secs */

#define WDT_COUNTER 10000 /* 10 secs */

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static struct _tcd_desc _tc = {
	.addr = TC0,
	.channel = 0,
};

/** Global timestamp in 1/4 seconds since last watchdog reset */
static volatile uint32_t _countdown_timer = 0;

static volatile uint32_t _change_period = 1;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 *  Configure WDT with fault interrupt enable and reset disable,
 *  wdv value is equal to WDT_COUNTER and wdd is WDT_DELTATIME
 */
static void _configure_wdt(uint32_t timer, uint32_t delta_timer)
{
	wdt_enable(WDT_MR_WDFIEN | WDT_MR_WDDBGHLT | WDT_MR_WDIDLEHLT,
	           delta_timer, timer);
	wdt_get_status();
}

/**
 *  Interrupt handler for WDT interrupt.
 */
static void _wdt_handler(uint32_t source, void* user_arg)
{
	assert(source == ID_WDT);

	uint8_t status = wdt_get_status();
	printf("WDT interrupt - Watchdog UnderFlow:%d - Watchdog Error:%d\n\r",
		status & WDT_SR_WDUNF  ? 1 : 0, status & WDT_SR_WDERR ? 1 : 0);
}

/**
 * Callback for TC
 * Resets WDT at different periods depending on user input
 */
static int _tc_handler(void* arg, void* arg2)
{
	if (_countdown_timer > (16000 / 250) && _change_period == 0) {
		printf("WDT has been Reset after 16s\n\r");
		_countdown_timer = 0;
		wdt_restart();
	} else if (_countdown_timer > (5000 / 250) && _change_period == 1) {
		printf("WDT has been Reset after 5s\n\r");
		_countdown_timer = 0;
		wdt_restart();
	} else if (_countdown_timer > (2000 / 250) && _change_period == 2) {
		printf( "WDT has been Reset after 2s\n\r");
		_countdown_timer = 0;
		wdt_restart();
	} else if (_countdown_timer > (16000 / 250) && _change_period == 3) {
		printf("Watchdog Reset interrupt has been enabled, system will restart after %dms\n\r", WDT_COUNTER);
		_countdown_timer = 0;
		wdt_enable(WDT_MR_WDRSTEN | WDT_MR_WDFIEN | WDT_MR_WDDBGHLT | WDT_MR_WDIDLEHLT,
		           500, WDT_COUNTER);
	} else {
		_countdown_timer++;
	}

	return 0;
}

/**
 *  Configure Timer Counter to generate an interrupt every 250ms.
 */
static void _configure_tc(void)
{
	struct _callback _cb;

	tcd_configure_counter(&_tc, 0, 4); /* 4 Hz */
	callback_set(&_cb, _tc_handler, NULL);
	tcd_start(&_tc, &_cb);
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief getting-started Application entry point.
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t key;

	/* Output example information */
	console_example_info("WDT Example");

	/* Enable watchdog */
	_configure_wdt(WDT_COUNTER, WDT_DELTATIME);

	printf("Configure TC.\n\r");
	_configure_tc() ;

	printf("Configure WDT.\n\r");
	irq_add_handler(ID_WDT, _wdt_handler, NULL);
	irq_enable(ID_WDT);

	printf("uses DBG key 1/2/3/4.\n\r");
	printf("Press 1 to generate WatchDog Underflow error.\n\r");
	printf("Press 2 to reset WatchDog and enable Watchdog Reset.\n\r");
	printf("Press 3 to generate WatchDog error.\n\r") ;
	printf("Press 4 to Enable WatchDog reset interrupt.\n\r");

	while (1)
	{
		key = console_get_char();
		switch (key)
		{
		case '1':
			_change_period = 0;
			printf("-I- WDT will be reset every 16 seconds\n\r");
			break;
		case '2':
			_change_period = 1;
			printf("-I- WDT will be reset every 5 seconds\n\r");
			break;
		case '3':
			_change_period = 2;
			printf("-I- WDT will be reset every 2 seconds\n\r");
			break;
		case '4':
			_change_period = 3;
			printf("-I- System will be restarted by WDT after 16 seconds\n\r");
			break;
		default:
			printf("-E- Invalid input!\n\r");
			break;
		}
	}
}
