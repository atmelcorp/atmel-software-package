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
/** \cond usb_iad_cdc_hid
 * \page usb_iad_cdc_hid USB CDC(Serial)+HID(Keyboard) Example
 *
 * \section Purpose
 *
 * The USB CDCHID Project will help you to get familiar with the
 * USB Device Port(UDP)interface and also some of the other interfaces in
 * SAM9 microcontrollers. Also it can help you to be familiar with the USB
 * Framework that is used for rapid development of USB-compliant class
 * drivers such as USB Communication Device class (CDC), and how to combine
 * two USB functions to a single composite device (such as CDC + HID).
 *
 * \section Requirements
 *
 * This package can be used with some of Atmel evaluation kits that have UDP
 * interface, depending on the functions included.
 *
 * \section win_drv_update Windows Driver Update
 *
 * The composite device is generally supported by Microsoft windows, but some
 * patches are needed for muti-interface functions such as CDC & Audio. The
 * example composite devices are tested under windows XP (SP3). For CDC
 * serial port, additional windows driver file (CompositeCDCSerial.inf) can
 * be found at
 * libraries\\usb\\device\\composite\\drv\\CompositeCDCSerial.inf.
 *
 * The following is alternate update to fix the composite device support
 * on windows XP:
 *
 * \subsection install_win_sp3 Install Windows Service Pack 3 (SP3)
 *
 * All the fixes for USB generic driver are included in window XP service pack
 * 3. It can be found at
 * http://technet.microsoft.com/zh-cn/windows/bb794714(en-us).aspx .
 *
 * \subsection install_win_hotfix Install Windows Hot Fixes
 *
 * Two hot fixes are necessary for window to recognize the composite device
 * correctly:
 *
 * -# http://support.microsoft.com/kb/814560
 * -# http://support.microsoft.com/kb/918365
 *
 * \section Description
 *
 * This demo simulates a USB composite device that has USB Serial RS232
 * Converter and USB HID Keyboard functions.
 *
 * When an EK running this program connected to a host (PC for example), with
 * USB cable, host will notice the attachment of a USB device. No device
 * driver offered for the device now.
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
 *     -- USB CDC HID Device Project xxx --
 *     -- SAMxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 * -# When connecting USB cable to windows, the LED blinks, and the host
 *    reports a new USB device attachment.
 * -# For the windows driver installation and the test functions, please
 *      refer to "USB CDC serial converter" &
 *      "USB HID Keyboard Project".
 * -# You can use the inf file
 *    libraries\\usb\\device\\composite\\drv\\CompositeCDCSerial.inf
 *    to install the CDC serial  port.
 *
 * \section Reference
 * - usb_iad_cdc_hid/main.c
 * - pio: Pin configurations and peripheral configure.
 * - usb: USB Device Framework, USB CDC driver and UDP interface driver
 *    - \ref usbd_framework
 *        - \ref usbd_api
 *    - \ref usbd_composite "composite"
 *       - \ref usbd_composite_drv
 *    - \ref usbd_hid "hid" \\ \ref usbd_hid_key "hid-keyboard"
 *       - \ref usbd_hid_kbd_drv
 *    - \ref usbd_cdc "cdc-serial"
 *       - \ref usbd_cdc_serial_drv
 * - projects:
 *    - \ref usb_hid_keyboard
 *    - \ref usb_cdc_serial
 *
 */

/**
 * \file
 *
 * This file contains all the specific code for the
 * usb_iad_cdc_hid project
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"

#include "serial/console.h"
#include "led/led.h"

#include "gpio/pio.h"
#include "peripherals/pit.h"
#include "peripherals/pmc.h"

#include "usb/device/cdc/cdcd_serial.h"
#include "usb/device/composite/cdc_hidd_driver.h"
#include "usb/device/hid/hidd_keyboard.h"
#include "usb/device/usbd_hal.h"

#include "main_descriptors.h"
#include "../usb_common/main_usb_common.h"

#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/*---------------------------------------------------------------------------
 *      Definitions
 *---------------------------------------------------------------------------*/

/** Number of keys used in the example. */
#define NUM_KEYS       (3)

#ifdef CONFIG_HAVE_LED
/** Num lock LED index. */
#define LED_NUMLOCK    0
#endif

/** Size in bytes of the packet used for reading data from USB */
#define DATAPACKETSIZE \
    CHIP_USB_ENDPOINT_MAXPACKETSIZE(CDCD_Descriptors_DATAIN0)

/** Size in bytes of the buffer used for reading data from the USB & USART */
#define DATABUFFERSIZE (DATAPACKETSIZE+2)

/*----------------------------------------------------------------------------
 *      External variables
 *----------------------------------------------------------------------------*/

extern const USBDDriverDescriptors cdc_hidd_driver_descriptors;

/*---------------------------------------------------------------------------
 *      Internal variables
 *---------------------------------------------------------------------------*/

/** Buffer for storing incoming USB data. */
static uint8_t usb_serial_buffer0[DATABUFFERSIZE];

/** Serial port opened */
static uint8_t is_serial_port_on = 0;

/*- HID */

#ifdef PIN_PUSHBUTTON_1
/** Push button pin to configure for the application. */
static struct _pin pin_push_button = PIN_PUSHBUTTON_1;
#endif

/** Array of key codes produced by each button. */
static uint8_t key_codes[NUM_KEYS] = {
    HIDKeypad_T,
    HIDKeypad_U,
    HIDKeypad_NUMLOCK,
};

/** Current status (pressed or not) for each key. */
static bool key_status[NUM_KEYS];

/*-----------------------------------------------------------------------------
 *         Callback re-implementation
 *-----------------------------------------------------------------------------*/

/**
 * Invoked when the configuration of the device changes. Parse used endpoints.
 * \param cfgnum New configuration number.
 */
void usbd_driver_callbacks_configuration_changed(uint8_t cfgnum)
{
	cdc_hidd_driver_configuration_changed_handler(cfgnum);
}

/**
 * Invoked when a new SETUP request is received from the host. Forwards the
 * request to the Mass Storage device driver handler function.
 * \param request  Pointer to a USBGenericRequest instance.
 */
void usbd_callbacks_request_received(const USBGenericRequest *request)
{
	cdc_hidd_driver_request_handler(request);
}

/*----------------------------------------------------------------------------
 *         Callbacks
 *----------------------------------------------------------------------------*/

/**
 * Invoked when the CDC ControlLineState is changed
 * \param DTR   New DTR value.
 * \param RTS   New RTS value.
 */
void cdcd_serial_control_line_state_changed(uint8_t DTR,
                                        uint8_t RTS)
{
	is_serial_port_on = DTR;
	RTS = RTS; /* dummy */
}

/**
 * Invoked when the status of the keyboard LEDs changes. Turns the num. lock
 * LED on or off.
 * \param num_lock_status Indicates the current status of the num. lock key.
 * \param caps_lock_status Indicates the current status of the caps lock key.
 * \param scroll_lock_status Indicates the current status of the scroll lock key
 */
void hidd_keyboard_callbacks_leds_changed(
	uint8_t num_lock_status,
	uint8_t caps_lock_status,
	uint8_t scroll_lock_status)
{
	caps_lock_status = caps_lock_status;
	scroll_lock_status = scroll_lock_status;
#ifdef CONFIG_HAVE_LED
	/* Num. lock */
	if (num_lock_status) {
		led_set(LED_NUMLOCK);
	}
	else {
		led_clear(LED_NUMLOCK);
	}
#endif
}

/*---------------------------------------------------------------------------
 *         Internal functions
 *---------------------------------------------------------------------------*/

/**
 * Monitor keyboard buttons & Update key status in HID driver
 */
static void _hidd_keyboard_process_keys(void)
{
	uint32_t i;
	uint8_t pressed_keys[NUM_KEYS];
	uint8_t pressed_keys_size = 0;
	uint8_t released_keys[NUM_KEYS];
	uint8_t released_keys_size = 0;

	/* Monitor buttons */
	if (console_is_rx_ready()) {
		uint8_t key = console_get_char();
		switch(key) {
			case '1':
			case '2':
				i = key - '1' + 1;
				key_status[i] = !key_status[i];
				if (key_status[i]) {
					/* Key press simulation */
					trace_info("Key %u pressed\n\r", (unsigned)i);
					pressed_keys[pressed_keys_size] = key_codes[i];
					pressed_keys_size++;
					hidd_keyboard_remote_wakeup();
				} else {
					/* Key release simulation */
					trace_info("Key %u released\n\r", (unsigned)i);
					released_keys[released_keys_size] = key_codes[i];
					released_keys_size++;
				}
				break;
			default:
				console_put_char(key);
		}
	}

#ifdef PIN_PUSHBUTTON_1
	/* Check if button state has changed */
	bool is_button_pressed = !pio_get(&pin_push_button);
	if (is_button_pressed != key_status[0]) {
		/* Update button state */
		key_status[0] = !key_status[0];
		if (key_status[0]) {
			/* Key has been pressed */
			trace_info("BP has been pressed\n\r");
			pressed_keys[pressed_keys_size] = key_codes[0];
			pressed_keys_size++;
			hidd_keyboard_remote_wakeup();
		} else {
			/* Key has been released */
			trace_info("BP has been released\n\r");
			released_keys[released_keys_size] = key_codes[0];
			released_keys_size++;
		}
	}
#endif

	/* Update key status in the HID driver if necessary */
	if ((pressed_keys_size != 0) || (released_keys_size != 0)) {
		uint8_t status;

		do {
			status = hidd_keyboard_change_keys(pressed_keys,
											pressed_keys_size,
											released_keys,
											released_keys_size);
		} while (status != USBD_STATUS_SUCCESS);
	}
}

/*---------------------------------------------------------------------------
 *         Exported function
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 *          Main
 *---------------------------------------------------------------------------*/

/**
 * Initializes drivers and start the USB CDCHID device.
 */
int main(void)
{
	uint8_t usb_connected = 0, serial_on = 0;

	/* Output example information */
	console_example_info("USB CDC HID Device Example");

	/* If there is on board power, switch it off */
	usb_power_configure();

	/* ----- HID Function Initialize */
	printf( "-- : DBG key 1 2 used as buttons\n\r" );
	printf( "-- : 1st press to push, 2nd press to release\n\r" );

#ifdef PIN_PUSHBUTTON_1
	/* Initialize key statuses and configure push buttons */
	pio_configure(&pin_push_button, 1);
#endif

	memset(key_status, 0, sizeof(key_status));

	/* USB CDCHID driver initialization */
	cdc_hidd_driver_initialize(&cdc_hidd_driver_descriptors);

	/* connect if needed */
	usb_vbus_configure();

	/* Driver loop */
	while (1) {
		/* Device is not configured */
		if (usbd_get_state() < USBD_STATE_CONFIGURED) {
			if (usb_connected) {

				printf("-I- USB Disconnect/Suspend\n\r");
				usb_connected = 0;

				/* Serial port closed */
				is_serial_port_on = 0;
			}
		} else {

			if (usb_connected == 0) {

				printf("-I- USB Connect\n\r");
				usb_connected = 1;
			}

			if (!serial_on && is_serial_port_on) {

				printf("-I- SerialPort ON\n\r");
				/* Start receiving data on the USB */
				cdcd_serial_read(usb_serial_buffer0,
							DATAPACKETSIZE,
							0,
							0);
				serial_on = 1;

			} else if (serial_on && !is_serial_port_on) {
				printf("-I- SeriaoPort OFF\n\r");
				serial_on = 0;
			}

			_hidd_keyboard_process_keys();
		}
	}
}
/** \endcond */
