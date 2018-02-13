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
 *  \page qt1_xpro_selfcap Getting Started with sama5d2 Microcontrollers
 *
 *  \section Purpose
 *
 *  The qt1_xpro_selfcap example shows the startup sequence of a chip 
 *  and how to use its PTC.
 *
 *  \section Requirements
 *
 *  This package can be used with SAMA5D2-PTC-EK and QT1 XPLAINED QTOUCH SELF CAPACITTANCE board.
 *
 *  \section Description
 *
 *  The demonstration load the PPP firmware and configure the mailbox, 
 *  then start PPP co-processor to run.
 *  Three touch mode for test in MUTCAP mode: Two button, Wheel, Slider
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
 *      -- QT1_xpro_selfcap Example xxx --
 *      -- SAMxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 *
 *  \section References
 *  - qt1_xpro_selfcap/main.c
 *  - qtm.h
 *  - console.h
 *  - qt1_sc_support.h
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

#include "qtouch/qt1_sc_support.h"

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/* static struct atmel_qtm_mailbox mb; */

static int _on_key_event(void* arg, void* arg2)
{
	struct atmel_qtm_touch_events* events = (struct atmel_qtm_touch_events*)arg2;

	if ((events->key_event_id0 & 0x40) == 0x40) {
		if ((events->key_enable_state0 & 0x40) == 0x40)
			qt1_xpro_sc_set_button_led(1);
		else
			qt1_xpro_sc_clear_button_led(1);
	}
	return 0;
}

static int _on_scroller_event(void* arg, void* arg2)
{
	struct atmel_qtm_mailbox* _mb = (struct atmel_qtm_mailbox*)0x804000;
	struct atmel_qtm_touch_events* events = (struct atmel_qtm_touch_events*)arg2;
	int i;
	static uint8_t RGB_Val[3];
	static uint8_t PWM_Count; // Counter for RGB LED

	if (PWM_Count < 20)
		PWM_Count++;
	else
		PWM_Count = 0;

	/* SLIDER */
	if ((events->scroller_event_id & 0x01) == 0x01) {
		if (_mb->scroller_data[0].status > 0) {
			for (i = 0; i < (_mb->scroller_config[0].key_count * 2 + 2); i++) { // +1 added to include led 6
				if ((_mb->scroller_data[0].position) > (i << 3))
					qt1_xpro_sc_set_slider_led(i);
				else
					qt1_xpro_sc_clear_slider_led(i);
			}
		} else {
			for (i = 0; i < (_mb->scroller_config[0].key_count * 2 + 2); i++)//// +1 added to include led 6
				qt1_xpro_sc_clear_slider_led(i);
		}
	}

	/* WHEEL */
	if ((events->scroller_event_id & 0x02) == 0x02) {
		if (_mb->scroller_data[1].status > 0) {
			qt1_xpro_sc_get_rgb_val(_mb->scroller_data[1].position, &RGB_Val[0]);

			if (PWM_Count < RGB_Val[0])
				qt1_xpro_sc_set_wheel_led(0);
			else
				qt1_xpro_sc_clear_wheel_led(0);

			if (PWM_Count < RGB_Val[1])
				qt1_xpro_sc_set_wheel_led(1);
			else
				qt1_xpro_sc_clear_wheel_led(1);

			if (PWM_Count < RGB_Val[2])
				qt1_xpro_sc_set_wheel_led(2);
			else
				qt1_xpro_sc_clear_wheel_led(2);
		} else {
			qt1_xpro_sc_clear_wheel_led(0);
			qt1_xpro_sc_clear_wheel_led(1);
			qt1_xpro_sc_clear_wheel_led(2);
		}
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
	console_example_info("QT1 XPRO SLEFCAP Example");

	qt1_xpro_sc_init();
	qtm_configure(&qtm);

	qtm_event_request(&qtm, QTM_EVENT_KEY, _on_key_event);
	qtm_event_request(&qtm, QTM_EVENT_SCROLLER, _on_scroller_event);

	qtm_start(&qtm);
	while(1);
}
