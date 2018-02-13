/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2017, Atmel Corporation
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
 *  \page qt2_surface Getting Started with sama5d2 Microcontrollers
 *
 *  \section Purpose
 *
 *  The qt2_surface example shows the startup sequence of a chip 
 *  and how to use its PTC in surface mode.
 *
 *  \section Requirements
 *
 *  This package can be used with SAMA5D2-PTC-EK and QT1 XPLAINED QTOUCH SURFACE board.
 *
 *  \section Description
 *
 *  The demonstration load the PPP firmware and configure the mailbox, 
 *  then start PPP co-processor to run.
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
 *  -# In the terminal window, the following text should appear 
 *     (values depend on the board and chip used):
 *     \code
 *      -- QT2_SURFACE Example xxx --
 *      -- SAMxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 *
 *  \section References
 *  - qt2_surface/main.c
 *  - qtm.h
 *  - is31f13728.h
 *  - console.h
 *  - qt2_support.h
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

#include <ctype.h>
#include <string.h>

#include "board.h"
#include "ptc/qtm.h"
#include "led/is31fl3728.h"
#include "serial/console.h"
#include "trace.h"

#include "qtouch/qt2_support.h"

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static uint8_t is31fl3728_fb[7];

static struct _is31fl3728 is31fl3728 = {
	.twi = {
		.bus = BUS(BUS_TYPE_I2C, 0),
	},
	.desc = {
		.name = "is31fl3728",
		.matrix = {
			.cols = 7,
			.rows = 7,
		},
	},
	.settings = {
		.config = 0,
		.column = 0,
		.lighting = 0,
	},
};


/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static int _on_scroller_event(void* arg, void* arg2)
{
	struct atmel_qtm_mailbox* _mb = (struct atmel_qtm_mailbox*)0x804000;
	struct atmel_qtm_touch_events* events = (struct atmel_qtm_touch_events*)arg2;

	printf("%u/%u\r\n", _mb->scroller_data[0].position, _mb->scroller_data[1].position);

	if (events->scroller_event_id != 0) {
		if (events->key_enable_state0 != 0) {
			is31fl3728_fb_reset(&is31fl3728, 0);
			is31fl3728_fb_set(&is31fl3728, _mb->scroller_data[0].position / 8, 7 - _mb->scroller_data[1].position / 8);
			is31fl3728_refresh(&is31fl3728);
		} else {
			is31fl3728_fb_reset(&is31fl3728, 0);
			is31fl3728_refresh(&is31fl3728);
		}
	} else {
		is31fl3728_fb_reset(&is31fl3728, 0);
		is31fl3728_refresh(&is31fl3728);
	}

	return 0;
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief getting-started Application entry point.
 * terminal
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	static struct _qtm qtm;
	console_example_info("QT2 XPRO Surface Example");

	qt2_xpro_init();
	is31fl3728_configure(&is31fl3728, 0x60, is31fl3728_fb);
	is31fl3728_fb_reset(&is31fl3728, 0);
	is31fl3728_refresh(&is31fl3728);

	qtm_configure(&qtm);
	qtm_event_request(&qtm, QTM_EVENT_SCROLLER, _on_scroller_event);
	qtm_start(&qtm);
	while(1);
}
