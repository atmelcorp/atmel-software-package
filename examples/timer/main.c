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
 *  \page timer TC timer example
 *
 *  \section Purpose
 *
 *  The example shows how to use timer sleep function.
 *
 *  \section Requirements
 *
 *  This package can be used with SAMA5 and SAM9XX5.
 *
 *  \section Description
 *
 *  The program demostrates how to use the sleep function.
 *	The timer is configured to 1Mhz,1 interrupt per 1000 ticks.
 *	It allows the user to wait in different granularity.
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
 *  -# In the terminal window, the following text should appear:
 *     \code
 *      ==== Timer Example xxx ====
 *      a count ->sleep count s
 *      b count ->sleep count ms
 *	c count ->sleep count us
 *     \endcode
 * -# Choose an item in the menu to test.
 *  \section References
 *  - timer/main.c
 *  - timer.h
 *  - trace.h
 */

/** \file
 *
 *  This file contains all the specific code for the timer example.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"
#include "timer.h"


#include "mm/cache.h"
#include "serial/console.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/
static volatile uint32_t cmd_length = 0;
static volatile bool cmd_complete = false;
CACHE_ALIGNED static uint8_t cmd_buffer[32];
static uint32_t time_count = 0;

/*------------------------------------------------------------------------------
*			Local Functions
*------------------------------------------------------------------------------*/
	
/**
* \brief Displays the user interface on the terminal.
 */
static void print_menu(void)
{
	
	printf(" |================= Timer Example ==============|\r\n");
	printf(" | a count -> sleep count s			|\r\n");
	printf(" | b count -> sleep count ms			|\r\n");
	printf(" | c count -> sleep count us			|\r\n");
	printf(" | h  -> Display this menu			|\r\n");
	printf(" |==============================================|\r\n");

}


static uint32_t _timer_arg_parser(const uint8_t* buffer, uint32_t len)
{	
	char* end_count = NULL;
	unsigned long count = strtoul((char*)buffer, &end_count, 0);
	if (end_count == (char*)buffer) {
		printf("Args: %s\r\n Invalid Count\r\n", buffer);
		return 0;
	}
	return count;
}

/**
 * \brief Get timer sleep unit and count.
 */
static void get_time(void)
{
	char ucKey;
 
	/* input wait uint (s,ms and us) and wait count */
	while (1) {
		ucKey = console_get_char();

		/* end input */
		if (ucKey == 0x0d || ucKey == 0x0a) {
			cmd_buffer[cmd_length] = '\0';
			cmd_complete = true;
			printf("\r\n");
			break;
		}
		
		/* DEL or BACKSPACE */
		if (ucKey == 0x7f || ucKey == 0x08) {
			if (cmd_length > 0) {
				console_echo(ucKey);
				cmd_length--;
				cmd_buffer[cmd_length] = '\0';
				continue;
			}
		}
		
		if (cmd_length < (ARRAY_SIZE(cmd_buffer) - 1)) {
			console_echo(ucKey);
			cmd_buffer[cmd_length] = ucKey;
			cmd_length++;
		}
	}
	
	/* parse input arg to get time count */
	if (cmd_complete)
		time_count = _timer_arg_parser((uint8_t*)&cmd_buffer[2], cmd_length - 2);
}


/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Application entry point for Timer example.
 *
 * \return Unused (ANSI-C compatibility).
 */

int main(void)
{
	uint64_t start, end;

	/* Output example information */
	console_example_info("Timer Example");

	print_menu();

	while (1) {
		get_time();
		switch (cmd_buffer[0]) {
		case 'a':
			start = timer_get_tick();
			sleep(time_count);
			end = timer_get_tick();
			printf("%dms elapsed!\r\n", (unsigned)(end - start));
			break;
		case 'b':
			start = timer_get_tick();
			msleep(time_count);
			end = timer_get_tick();
			printf("%dms elapsed!\r\n", (unsigned)(end - start));
			break;
		case 'c':
			start = timer_get_tick();
			usleep(time_count);
			end = timer_get_tick();
			printf("%dms elapsed!\r\n", (unsigned)(end - start));
			break;
		case 'h':
			print_menu();
			break;
		default:
			printf("Invalid sleep count! \r\n");
			break;
		}

		cmd_length = 0;
		cmd_complete = false;
	}
}
