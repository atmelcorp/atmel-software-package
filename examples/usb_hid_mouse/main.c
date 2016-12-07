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
/** \cond usb_hid_mouse
 * \page usb_hid_mouse USB HID Mouse Example
 *
 * \section Purpose
 *
 * The USB HID Mouse Example will help you to get familiar with the
 * USB Device Port(UDP) and PIO interface on SAM9 microcontrollers. Also
 * it can help you to be familiar with the USB Framework that is used for
 * rapid development of USB-compliant class drivers such as USB Human
 * Interface Device class (HID).
 *
 * \section Requirements
 *
 * This example can be run on SAMA5D4-EK and SAMA5D4-XULT boards.
 *
 * \section Description
 *
 * When an EK/XULT board running this program connected to a host (PC for example), with
 * USB cable, the EK appears as a HID-compliant mouse for the host. Then you
 * can enter 'W'/'S'/'A'/'D' into the console to control the pointer on the host.
 * E.g., to move it.
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board. Please
 *    refer to the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6421.pdf">
 *    SAM-BA User Guide</a>, the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *    GNU-Based Software Development</a> application note or to the
 *    <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *    IAR EWARM User Guide</a>, depending on your chosen solution.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *     \code
 *     -- USB Device HID Mouse Project xxx --
 *     -- SAMxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 * -# When connecting USB cable to windows, the
 *    new "HID Mouse Device" appears in the
 *    hardware %device list.
 * -# Once the device is connected and configured, pressing the joystick or
 *    the configurated board buttons move the cursor.
 *
 * \section References
 * - usb_hid_mouse/main.c
 * - pio: PIO interface driver
 *    - pio.h
 *    - pio_it.h
 * - usb: USB Framework, USB HID driver and UDP interface driver
 *    - \ref usbd_framework
 *       - \ref usbd_api
 *    - hid-mouse
 *       - \ref usbd_hid_mouse_drv
 *
 */

/**
 * \file
 *
 * This file contains all the specific code for the
 * usb_hid_mouse
 *
 * \section Contents
 *
 * The code can be roughly broken down as follows:
 *    - Configuration functions
 *       - vbus_configure
 *       - PIO & Timer configurations in start of main
 *    - Interrupt handlers
 *       - ISR_Vbus
 *    - The main function, which implements the program behavior
 */

/*-----------------------------------------------------------------------------
 *         Headers
 *-----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"

#include "gpio/pio.h"
#include "peripherals/pit.h"
#include "peripherals/pmc.h"
#include "peripherals/tc.h"

#include "serial/console.h"

#include "usb/device/hid/hidd_mouse_driver.h"
#include "usb/device/usbd.h"
#include "usb/device/usbd_hal.h"

#include "../usb_common/main_usb_common.h"

#include <string.h>
#include <stdbool.h>
#include <stdint.h>

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

#define NO_PUSHBUTTON

/** Speed of pointer movement X */
#define SPEED_X             4

/** Speed of pointer movement Y */
#define SPEED_Y             4

/*----------------------------------------------------------------------------
 *         External variables
 *----------------------------------------------------------------------------*/

extern USBDDriverDescriptors hidd_mouse_driver_descriptors;

/*----------------------------------------------------------------------------
 *         Internal variables
 *----------------------------------------------------------------------------*/

#ifndef NO_PUSHBUTTON
/** List of pins_joystick (push button) to configure for the application. */
static const struct _pin pins_joystick[] = { PINS_PUSHBUTTONS };
#endif

/*----------------------------------------------------------------------------
 *         Internal functions
 *----------------------------------------------------------------------------*/

/**
 * Monitor buttons of joystick status.
 * \param p_btn_status Pointer to button status bitmap.
 * \param p_dx        Pointer to fill x value.
 * \param p_dy        Pointer to fill y value.
 */
static uint8_t _buttons_monitor(uint8_t *btn_status, int8_t *dx, int8_t *dy)
{
	uint8_t is_changed = 0;
	btn_status = btn_status; /*dummy */

#ifdef NO_PUSHBUTTON
	/* - Movement W S A D */
	if (console_is_rx_ready())
	{
		uint8_t key = console_get_char();
		*dx = 0;
		*dy = 0;
		switch (key)
		{
		case 'i':
		case 'I':
			*dy = -SPEED_Y;
			is_changed = 1;
			break;
		case 'k':
		case 'K':
			*dy = +SPEED_Y;
			is_changed = 1;
			break;
		case 'j':
		case 'J':
			*dx = -SPEED_X;
			is_changed = 1;
			break;
		case 'l':
		case 'L':
			*dx = +SPEED_X;
			is_changed = 1;
			break;
		default:
			break;
		}
	}
#else
	/* - Movement buttons, Joystick or Push buttons */
	if (pio_get(&pins_joystick[JOYSTICK_LEFT]) == 0) {
		*dx = -SPEED_X;
		is_changed = 1;
	} else if (pio_get(&pins_joystick[JOYSTICK_RIGHT]) == 0) {
		*dx = SPEED_X;
		is_changed = 1;
	} else {
		*dx = 0;
	}
#endif

	return is_changed;
}

/*----------------------------------------------------------------------------
 *         Callbacks re-implementation
 *----------------------------------------------------------------------------*/

/**
 *  Invoked whenever a SETUP request is received from the host. Forwards the
 *  request to the standard handler.
 */
void usbd_callbacks_request_received(const USBGenericRequest *request)
{
	hidd_mouse_driver_request_handler(request);
}

/**
 * Invoked when the configuration of the device changes. Start reading
 * output reports.
 * \param cfgnum New configuration number.
 */
void usbd_driver_callbacks_configuration_changed(uint8_t cfgnum)
{
	hidd_mouse_driver_configuration_changed_handler(cfgnum);
}

/*----------------------------------------------------------------------------
 *         Exported function
 *----------------------------------------------------------------------------*/

/**
 * usb_hid_mouse application entry.
 *
 * Initializes the system and then monitors buttons, sending the
 * corresponding character when one is pressed.
 */
int main(void)
{
	uint8_t bm_buttons = 0;
	int8_t dx = 0, dy = 0;
	uint8_t is_changed;

	/* Output example information */
	console_example_info("USB Device HID Mouse Example");

	/* Initialize all USB power (off) */
	usb_power_configure();

#ifdef NO_PUSHBUTTON
	printf("-- Press I J K L to move cursor\n\r");
#else
	/* Initialize key statuses and configure push buttons */
	pio_configure(pins_joystick, ARRAY_SIZE(pins_joystick));
#endif

	/* HID driver initialization */
	hidd_mouse_driver_initialize(&hidd_mouse_driver_descriptors);

	/* connect if needed */
	usb_vbus_configure();

	/* Infinite loop */
	while (1) {
		if (usbd_get_state() < USBD_STATE_CONFIGURED)
			continue;

		is_changed = _buttons_monitor(&bm_buttons, &dx, &dy);
		if (is_changed) {
			uint8_t status;
			do {
				status = hidd_mouse_driver_change_points(bm_buttons, dx, dy);
			} while (status != USBD_STATUS_SUCCESS);
		}
	}
}
/** \endcond */
