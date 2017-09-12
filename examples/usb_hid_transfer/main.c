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
/** \cond usb_hid_transfer
 *  \page usb_hid_transfer USB HID Transfer Example
 *
 *  \section Purpose
 *
 *  The USB HID Transfer Project will help you to get familiar with the
 *  USB Device Port(UDP) and PIO interface on SAMA5D2x microcontrollers. Also
 *  it can help you to be familiar with the USB Framework that is used for
 *  rapid development of USB-compliant class drivers such as USB Human
 *  Interface Device class (HID).
 *
 *  \section Requirements
 *
 *  This package can be used with all Atmel evaluation kits that has UDP
 *  interface.
 *
 *  \section Description
 *
 *  The demo simulates a customized HID device that reports customized data
 *  stream, in which informations on LEDs and buttons are packed, to host.
 *
 *  When an EK running this program connected to a host (PC for example), with
 *  USB cable, the EK appears as a "USB Human Interface Device" for the host.
 *  Then you can use the client application to read/write on it.
 *
 *  \section Usage
 *
 *  -# Build the program and download it inside the evaluation board. Please
 *     refer to the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6421.pdf">
 *     SAM-BA User Guide</a>, the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *     GNU-Based Software Development</a> application note or to the
 *     <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *     IAR EWARM User Guide</a>, depending on your chosen solution.
 *  -# On the computer, open and configure a terminal application
 *     (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *    - 115200 bauds
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# Start the application.
 *  -# In the terminal window, the following text should appear:
 *      \code
 *      -- USB Device HID Transfer Project xxx --
 *      -- SAMxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *      \endcode
 *  -# When connecting USB cable to windows, the LED blinks.
 *     Then new "HID Transfer Device" appears in the
 *     hardware %device list.
 *  -# Then you can use the PC program !hidTest.exe to check the !device
 *     information and run tests.
 *  -# Find the HID Device whose VID is 03EB and PID is 6201, select item type
 *     and item to see its attributes.
 *  -# Type what you want to send in output edit box, use buttons on the right
 *     side to send. You can see data information in debug terminal.
 *  -# You can use the buttons above the input edit box to read data from
 *     !device of monitor the data, then the data and the status of the buttons
 *     on the board is read and the gray buttons is up or down based on the
 *     buttons status on the board.
 *
 *  \section References
 *  - usb_hid_transfer/main.c
 *  - pio: PIO interface driver
 *     - pio.h
 *     - pio_it.h
 *  - usb: USB Framework, USB HID driver and UDP interface driver
 *     - \ref usbd_framework
 *        - \ref usbd_api
 *     - \ref usbd_hid_tran "hid-Transfer"
 *        - \ref usbd_hid_xfr_drv
 */

/**
 *  \file
 *
 *  This file contains all the specific code for the
 *  usb_hid_transfer example
 */

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/
#include "board.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"

#include "gpio/pio.h"
#include "peripherals/pit.h"
#include "peripherals/pmc.h"
#include "peripherals/tc.h"

#include "mm/cache.h"
#include "serial/console.h"
#include "led/led.h"


#include "usb/device/hid/hidd_transfer_driver.h"
#include "usb/device/usbd.h"
#include "usb/device/usbd_hal.h"

#include "../usb_common/main_usb_common.h"

#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *         Local Definitions
 *----------------------------------------------------------------------------*/
/** Delay for pushbutton debouncing (ms) */
#define DEBOUNCE_TIME      10
#define NO_PUSHBUTTON

/**  Size of buffer in bytes. */
#define BUFFER_SIZE   (64)

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

CACHE_ALIGNED uint8_t in_buffer[BUFFER_SIZE];
CACHE_ALIGNED uint8_t out_buffer[BUFFER_SIZE];

/*----------------------------------------------------------------------------
 *         External variables
 *----------------------------------------------------------------------------*/


/** HID Transfer driver descriptors */
extern USBDDriverDescriptors hidd_transfer_driver_descriptors;

/*----------------------------------------------------------------------------
 *         Internal variables
 *----------------------------------------------------------------------------*/

/** Pins for Buttons */
#ifndef NO_PUSHBUTTON
static struct _pin pins_buttons[] = {PINS_PUSHBUTTONS};
#endif

#ifndef NO_PUSHBUTTON
/**
 *  Remote wake-up support (optional)
 */

/** Button for Wake-UP the USB device. */
static const struct _pin pin_wake_up = PIN_PUSHBUTTON_1;

/**
 *  Interrupt service routine for the remote wake-up pin. Starts the debouncing
 *  sequence.
 */
static void wake_up_handler( const struct _pin *pin )
{
	trace_debug("Wake-up handler\n\r");

	/* Check current level on the remote wake-up pin */
	if (!pio_get( &pin_wake_up ))
		hidd_transfer_driver_remote_wake_up();
}

/**
 *  Configures the wake-up pin to generate interrupts.
 */
static void configure_wake_up( void )
{
	trace_info("Wake-up configuration\n\r");

	/* Configure PIO */
	pio_set_debounce_filter(DEBOUNCE_TIME);
	pio_configure(&pin_wake_up, 1);
	pio_enable_it(&pin_wake_up);
}
#endif
	
/*----------------------------------------------------------------------------
 *         Internal Functions
 *----------------------------------------------------------------------------*/

/**
 *  Display the buffer, 8 byte a line
 *
 *  \param buffer   Pointer to the data location
 *  \param data_len    Size of the data
 */
static void _show_buffer( uint8_t *puc_buffer, uint32_t data_len )
{
	uint32_t dw;

	for (dw = 0; dw < data_len; dw++) {
		if ((dw & 0x7) == 0)
			printf("\n\r" );

		printf(" %02x", puc_buffer[dw]);
	}

	printf("\n\r");
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
	hidd_transfer_driver_request_handler(request);
}

/**
 * Invoked when the configuration of the device changes. Start reading
 * output reports.
 * \param cfgnum New configuration number.
 */
void usbd_driver_callbacks_configuration_changed(uint8_t cfgnum)
{
	hidd_transfer_driver_configuration_changed_handler(cfgnum);
}

/*----------------------------------------------------------------------------
 *         Main function
 *----------------------------------------------------------------------------*/

/**
 *  Initializes the system and then monitors buttons, sending the
 *  corresponding character when one is pressed.
 *  \callgraph
 */
int main( void )
{
	uint32_t count = 0;
	uint32_t data_len;
	uint8_t  led_stat = 0;
	uint8_t  update;

	/* Output example information */
	console_example_info("USB Device HID Transfer Example");

	/* If there is on board power, switch it off */
	usb_power_configure();

#ifndef NO_PUSHBUTTON
	/* If there is wakeup pin, configure it */
	_configure_wake_up();
#endif

#ifdef NO_PUSHBUTTON
	printf("-- : DBG key 1 2 used as monitored buttons\n\r");
	printf("-- : Test program display corresponding status\n\r");
#else
	pio_configure(pins_push_buttons, ARRAY_SIZE(pins_push_buttons));
#endif

	/* HID driver initialization */
	hidd_transfer_driver_initialize(&hidd_transfer_driver_descriptors);

	/* connect if needed */
	usb_vbus_configure();

	memset(out_buffer, 0x80, sizeof out_buffer);

	/* Infinite loop */
	while (1) {
		if (usbd_get_state() < USBD_STATE_CONFIGURED)
			continue;

		update = 0;

		data_len = hidd_transfer_driver_read(in_buffer, BUFFER_SIZE);

		if (data_len) {
			printf("Data In(%u):", (unsigned int) data_len);
			_show_buffer(in_buffer, data_len);

			led_stat = in_buffer[0];
			update = 1;
		}

		data_len = hidd_transfer_driver_read_report(in_buffer, BUFFER_SIZE);

		if (data_len) {
			printf("OutputReport In(%u):", (unsigned int)data_len);
			_show_buffer(in_buffer, data_len);

			led_stat = in_buffer[0];
			update = 1;
		}

		data_len = hidd_transfer_driver_read_feature(in_buffer, BUFFER_SIZE);

		if (data_len) {
			printf("FeatureReport In(%u):", (unsigned int)data_len);
			_show_buffer(in_buffer, data_len);

			led_stat = in_buffer[0];
			update = 1;
		}

		/* Update the status of LEDs */
		if (update && (0x80 & led_stat)) {
#if NUM_LEDS > 0 
			/* LED1 */
			if (led_stat & 0x01)
				led_set(0);
			else
				led_clear(0);
#endif

#if NUM_LEDS > 1 
			/* LED2 */
			if (led_stat & 0x02)
				led_set(1);
			else
				led_clear(1);
#endif
		}
		
		/* Update the status of the buttons */
#ifdef NO_PUSHBUTTON

		if (console_is_rx_ready()) {
			uint8_t key = console_get_char();
			switch (key) {
			case '1' :
				if (out_buffer[0] & 0x01) 
					out_buffer[0] &= ~0x01u;
				else 
					out_buffer[0] |=  0x01u;
				break;

			case '2' :
				if (out_buffer[0] & 0x02) 
					out_buffer[0] &= ~0x02u;
				else
					out_buffer[0] |=  0x02u;
				break;
			}
		}

#else
		out_buffer[0] = 0x80;

		if (pio_get(&pins_buttons[PUSHBUTTON_BP1]) == 0 )
			out_buffer[0] |= 0x01;

		if (pio_get(&pins_buttons[PUSHBUTTON_BP2]) == 0 )
			out_buffer[0] |= 0x02;

#endif

		sprintf( (char *)&out_buffer[5], ":%04x:%05u!", (unsigned int)count,
				 (unsigned int)count );
		out_buffer[1] = (uint8_t)(count);
		out_buffer[2] = (uint8_t)(count >> 8);
		out_buffer[3] = (uint8_t)(count >> 16);
		out_buffer[4] = (uint8_t)(count >> 24);

		if (USBD_STATUS_SUCCESS == hidd_transfer_driver_write( out_buffer,
														BUFFER_SIZE, 0, 0))
			count++;

	}
}
/** \endcond */
