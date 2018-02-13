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
 *  \page qt6_surface Getting Started with sama5d2 Microcontrollers
 *
 *  \section Purpose
 *
 *  The qt6_surface example shows the startup sequence of a chip 
 *  and how to use its PTC in surface mode.
 *
 *  \section Requirements
 *
 *  This package can be used with SAMA5D2-PTC-EK and QT6 XPLAINED QTOUCH SURFACE board.
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
 *      -- QT6_SURFACE Example xxx --
 *      -- SAMxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 *
 *  \section References
 *  - qt6_surface/main.c
 *  - qtm.h
 *  - console.h
 *  - qt6_support.h
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
#include "serial/console.h"
#include "trace.h"

#include "qtouch/qt6_support.h"

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static int _on_scroller_event(void* arg, void* arg2)
{
	struct atmel_qtm_mailbox* _mb = (struct atmel_qtm_mailbox*)0x804000;

	printf("%u/%u\r\n", _mb->scroller_data[0].position, _mb->scroller_data[1].position);

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
	console_example_info("QT6 XPRO Surface Example");

	qt6_xpro_init();
	qtm_configure(&qtm);

	qtm_event_request(&qtm, QTM_EVENT_SCROLLER, _on_scroller_event);
	qtm_start(&qtm);
	while(1);
}
