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

/**
 *  \page Automatic test for pio features with sama5dX Microcontrollers
 *
 *  \section Purpose
 *
 *  Automatic test for PIO
 *
 *  \section Requirements
 *
 *  This package can be used with:
 *  -# SAMA5D2-XULT
 *  -# SAMA5D3-XULT
 *  -# SAMA5D4-EK
 *  -# SAMA5D4-XULT
 *
 *  \section Description
 *
 * This test application automatically test the various mode and 
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
 *  -# 
 *
 *  \section References
 *  - test-pio/main.c
 *  - pio.h
 *  - pio_it.h
 *  - trace.h
 */

/** \file
 *
 *  This file contains all the specific code for the getting-started example.
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

#include "gpio/pio.h"
#include "peripherals/pmc.h"

#include "serial/console.h"

#include <stdbool.h>
#include <stdio.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/* Only used to get the number of available leds */
#if defined(CONFIG_BOARD_SAMA5D2_XPLAINED)
static struct _pin pio_output = { PIO_GROUP_C, PIO_PC10, PIO_OUTPUT_0, PIO_DEFAULT };
static struct _pin pio_input = { PIO_GROUP_C, PIO_PC11, PIO_INPUT, PIO_DEFAULT };
#elif defined(CONFIG_BOARD_SAMA5D27_SOM1_EK)
static struct _pin pio_output = { PIO_GROUP_D, PIO_PD6, PIO_OUTPUT_0, PIO_DEFAULT };
static struct _pin pio_input = { PIO_GROUP_D, PIO_PD7, PIO_INPUT, PIO_DEFAULT };
#elif defined(CONFIG_BOARD_SAMA5D3_XPLAINED)
static struct _pin pio_output = { PIO_GROUP_D, PIO_PD14, PIO_OUTPUT_0, PIO_DEFAULT };
static struct _pin pio_input = { PIO_GROUP_D, PIO_PD15, PIO_INPUT, PIO_DEFAULT };
#elif defined(CONFIG_BOARD_SAMA5D4_XPLAINED)
static struct _pin pio_output = { PIO_GROUP_B, PIO_PB14, PIO_OUTPUT_0, PIO_DEFAULT };
static struct _pin pio_input = { PIO_GROUP_B, PIO_PB15, PIO_INPUT, PIO_DEFAULT };
#elif defined(CONFIG_BOARD_SAMA5D4_EK)
static struct _pin pio_output = { PIO_GROUP_E, PIO_PE26, PIO_OUTPUT_0, PIO_DEFAULT };
static struct _pin pio_input = { PIO_GROUP_E, PIO_PE27, PIO_INPUT, PIO_DEFAULT };
#elif defined(CONFIG_BOARD_SAM9G15_EK) || \
      defined(CONFIG_BOARD_SAM9G25_EK) || \
      defined(CONFIG_BOARD_SAM9G35_EK) || \
      defined(CONFIG_BOARD_SAM9X25_EK) || \
      defined(CONFIG_BOARD_SAM9X35_EK)
static struct _pin pio_output = { PIO_GROUP_D, PIO_PD16, PIO_OUTPUT_0, PIO_DEFAULT };
static struct _pin pio_input = { PIO_GROUP_D, PIO_PD17, PIO_INPUT, PIO_DEFAULT };
#elif defined(CONFIG_BOARD_SAMV71_XPLAINED) || \
      defined(CONFIG_BOARD_SAME70_XPLAINED)
static struct _pin pio_output = { PIO_GROUP_A, PIO_PA2, PIO_OUTPUT_0, PIO_DEFAULT };
static struct _pin pio_input = { PIO_GROUP_C, PIO_PC19, PIO_INPUT, PIO_DEFAULT };
#else
#error Unsupported architecture
#endif

static volatile int _pio_event;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief Handler for Buttons rising edge interrupt.
 *
 *  Handle process led1 status change.
 */
static void pio_handler(uint32_t group, uint32_t status, void* user_arg)
{
	/* unused */
	(void)group;
	(void)user_arg;

	if (group == pio_input.group && (status & pio_input.mask)) {
		_pio_event++;
		/* disable interrupt after too many occurences */
		if (_pio_event > 5)
			pio_disable_it(&pio_input);
	}
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
	int tests = 0;
	int test_fail = 0;

	printf("<?xml version=\"1.0\" encoding=\"UTF-8\">\r\n\r\n");
	printf("<testsuite>\r\n");
	printf("  <testcase classname=\"pio.setup\" name=\"Setup\">\r\n");
	printf("    <system-out>\r\n");

	/* Output example information */
	console_example_info("PIO Testing Example");

	/* Configure PIO for input acquisition */
	pio_configure(&pio_input, 1);
	pio_set_debounce_filter(100);

	/* Initialize pios interrupt with its handlers, see
	 * PIO definition in board.h. */
	pio_add_handler_to_group(pio_input.group, pio_input.mask, pio_handler, NULL);

	/* Configure PIO for output generation */
	pio_configure(&pio_output, 1);

	printf("    </system-out>\r\n");
	printf("  </testcase>\r\n");

	printf("<testsuite>\r\n");
	printf("  <testcase classname=\"pio.level.low\" name='PIO: Set/Get PIO LOW LEVEL'>\r\n");
	printf("    <system-out>\r\n");
	pio_clear(&pio_output);
	msleep(10);
	printf("    </system-out>\r\n");
	if ((pio_get(&pio_input) != 0) || (pio_get(&pio_output) != 0)) {
		test_fail++;
		printf("    <error type=\"error\" />\r\n");
	}
	tests++;
	printf("  </testcase>\r\n");
	
	printf("  <testcase classname=\"pio.level.high\" name=\"PIO: Get PIO HIGH LEVEL\">\r\n");
	printf("    <system-out>\r\n");
	pio_set(&pio_output);
	msleep(10);
	printf("    </system-out>\r\n");
	if ((pio_get(&pio_input) != pio_input.mask) || (pio_get(&pio_output) != pio_output.mask)) {
		test_fail++;
		printf("    <error type=\"error\" />\r\n");
	}
	tests++;
	printf("  </testcase>\r\n");
	
	printf("  <testcase classname=\"pio.irq.edge.falling\" name=\"PIO: Get PIO IRQ FALLING EDGE\">\r\n");
	printf("    <system-out>\r\n");
	_pio_event = 0;
	pio_set(&pio_output);

	pio_input.attribute |= PIO_IT_FALL_EDGE;
	pio_configure(&pio_input, 1);
	pio_enable_it(&pio_input);

	pio_clear(&pio_output);
	msleep(10);
	printf("    </system-out>\r\n");
	if (_pio_event != 1) {
		test_fail++;
		printf("    <error error=\"error\">event(s): %d</error>\r\n", _pio_event);
	}
	tests++;
	pio_input.attribute &= ~PIO_IT_FALL_EDGE;
	pio_disable_it(&pio_input);
	printf("  </test>\r\n");
	
	printf("  <testcase classname=\"pio.irq.edge.rising\" name=\"PIO: Get PIO IRQ RISING EDGE\">\r\n");
	printf("    <system-out>\r\n");
	_pio_event = 0;
	pio_clear(&pio_output);

	pio_input.attribute |= PIO_IT_RISE_EDGE;
	pio_configure(&pio_input, 1);
	pio_enable_it(&pio_input);

	pio_set(&pio_output);
	msleep(10);
	printf("    </system-out>\r\n");
	if (_pio_event != 1) {
		test_fail++;
		printf("    <error error=\"error\">event(s): %d</error>\r\n", _pio_event);
	}
	tests++;
	pio_input.attribute &= ~PIO_IT_RISE_EDGE;
	pio_disable_it(&pio_input);
	printf("  </test>\r\n");
	
	printf("  <testcase classname=\"pio.irq.edge.both\" name=\"PIO: Get PIO IRQ BOTH EDGE\">\r\n");
#ifdef PIO_IT_BOTH_EDGE
	printf("    <system-out>\r\n");
	_pio_event = 0;
	pio_set(&pio_output);

	pio_input.attribute |= PIO_IT_BOTH_EDGE;
	pio_configure(&pio_input, 1);
	pio_enable_it(&pio_input);

	pio_clear(&pio_output);
	msleep(10);

	pio_set(&pio_output);
	msleep(10);
	printf("    </system-out>\r\n");
	if (_pio_event != 2) {
		test_fail++;
		printf("    <error error=\"error\">event(s): %d</error>\r\n", _pio_event);
	}
	tests++;
	pio_input.attribute &= ~PIO_IT_BOTH_EDGE;
	pio_disable_it(&pio_input);
#else
	printf("    <skip />\r\n");
#endif	
	printf("  </testcase>\r\n");
	
	printf("  <testcase classname=\"pio.irq.level.low\" name=\"PIO: Get PIO IRQ LEVEL LOW\">\r\n");
	printf("    <system-out>\r\n");
	pio_set(&pio_output);

	pio_input.attribute |= PIO_IT_LOW_LEVEL;
	pio_configure(&pio_input, 1);
	pio_enable_it(&pio_input);

	_pio_event = 0;
	pio_clear(&pio_output);
	msleep(10);
	pio_set(&pio_output);
	printf("    </system-out>\r\n");
	if (_pio_event < 1) {
		test_fail++;
		printf("    <error error=\"error\">event(s): %d</error>\r\n", _pio_event);
	}
	tests++;
	pio_input.attribute &= ~PIO_IT_LOW_LEVEL;
	pio_disable_it(&pio_input);
	printf("  </testcase>\r\n");
	
	printf("  <testcase classname=\"pio.irq.level.high\" name=\"PIO: Get PIO IRQ LEVEL HIGH\">\r\n");
	printf("    <system-out>\r\n");
	_pio_event = 0;
	pio_clear(&pio_output);

	pio_input.attribute |= PIO_IT_HIGH_LEVEL;
	pio_configure(&pio_input, 1);
	pio_enable_it(&pio_input);
	pio_set(&pio_output);
	msleep(10);
	pio_clear(&pio_output);
	printf("    </system-out>\r\n");
	if (_pio_event < 1) {
		test_fail++;
		printf("    <error error=\"error\">event(s): %d</error>\r\n", _pio_event);
	}
	tests++;
	pio_input.attribute &= ~PIO_IT_HIGH_LEVEL;
	pio_disable_it(&pio_input);
	printf("  </test>\r\n");
	
	printf("  <testcase classname=\"pio.mode.pull.up\" name=\"PIO: Get PIO PULL UP\">\r\n");
	printf("    <system-out>\r\n");
	pio_clear(&pio_output);
	pio_output.type = PIO_INPUT;
	pio_output.attribute |= PIO_PULLUP;
	pio_configure(&pio_output, 1);
	pio_configure(&pio_input, 1);

	printf("    </system-out>\r\n");
	if (pio_get(&pio_input) != pio_input.mask) {
		test_fail++;
		printf("   <error type=\"error\" />\r\n");
	}
	tests++;
	pio_output.attribute &= ~PIO_PULLUP;
	pio_output.type = PIO_OUTPUT_0;
	pio_configure(&pio_output, 1);
	printf("  </testcase>\r\n");

	printf("  <statistics>\r\n");
	printf("    <failures>%d</failures>\r\n", test_fail);
	printf("    <tests>%d</tests>\r\n", tests);
	printf("  </statistics>\r\n");
	printf("</testsuite>\r\n");
	
	while (1);
}
