/* ----------------------------------------------------------------------------
 *		   SAM Software Package License
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
/** \cond usb_hid_keyboard
 * \page usb_hid_keyboard USB HID Keyboard Example
 *
 * \section Purpose
 *
 * The USB HID Keyboard Example will help you to get familiar with the
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
 * The demo simulates a simple keyboard with a capslock and 'a' on it.
 *
 * When EK/XULT board running this program connected to a host (PC for example), with
 * USB cable, the board appears as a HID Keyboard for the host. Then you can use
 * the enter '1' into the console to input letter to the host. E.g, to open a
 * editor and input a letter 'a'; you can also enter '2' into the console to emulate the
 * NumLock key; Changes of NumLock, CapsLock, ScrollLock would be printed on the console too.
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board. Please
 *	  refer to the
 *	  <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6421.pdf">
 *	  SAM-BA User Guide</a>, the
 *	  <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *	  GNU-Based Software Development</a> application note or to the
 *	  <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *	  IAR EWARM User Guide</a>, depending on your chosen solution.
 * -# On the computer, open and configure a terminal application
 *	  (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *	 - 115200 bauds
 *	 - 8 bits of data
 *	 - No parity
 *	 - 1 stop bit
 *	 - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *	   \code
 *	   -- USB Device HID Keyboard Project xxx --
 *	   -- SAMxxxxx-xx
 *	   -- Compiled: xxx xx xxxx xx:xx:xx --
 *	   \endcode
 * -# When connecting USB cable to windows, the
 *	  new "HID Keyboard Device" appears in the
 *	  hardware %device list.
 * -# Once the device is connected and configured, pressing any of the board buttons
 *	  should send characters to the host PC. Pressing num. lock should also make the third
 *	  LED toggle its state (on/off).
 *
 * \section References
 * - usb_hid_keyboard/main.c
 * - pio: PIO interface driver
 *	  - pio.h
 *	  - pio_it.h
 * - usb: USB Framework, USB HID driver and UDP interface driver
 *	  - \ref usbd_framework
 *		- \ref usbd_api
 *	  - \ref usbd_hid_kbd_drv
 */

/**
 * \file
 *
 * This file contains all the specific code for the
 * usb_hid_keyboard
 *
 * \section Contents
 *
 * The code can be roughly broken down as follows:
 *	  - Configuration functions
 *		 - vbus_configure
 *		 - ConfigurePit
 *		 - ConfigureWakeUp
 *		 - PIO & Timer configurations in start of main
 *	  - Interrupt handlers
 *		 - ISR_Vbus
 *		 - ISR_Pit
 *		 - WakeUpHandler
 *	  - Callback functions
 *		 - hidd_keyboard_callbacks_leds_changed
 *	  - The main function, which implements the program behavior
 *
 */

/*-----------------------------------------------------------------------------
 *		   Headers
 *-----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"

#include "cortex-a/mmu.h"
#include "cortex-a/cp15.h"

#include "peripherals/pio.h"
#include "peripherals/pit.h"
#include "peripherals/pmc.h"
#include "peripherals/tc.h"
#include "peripherals/twid.h"
#include "peripherals/wdt.h"

#include "misc/console.h"
#include "misc/led.h"

#include "usbd.h"
#include "usbd_hal.h"
#include "hidd_keyboard_driver.h"

#include <string.h>
#include <stdbool.h>
#include <stdint.h>


/*-----------------------------------------------------------------------------
 *		   Definitions
-------------------------------------------------*/
#define NO_PUSHBUTTON

/** Number of keys used in the example. */
#define NUM_KEYS        (2)

/** Number of non-modifiers keys. */
#define NUM_NORMAL_KEYS        (1)

/** Number of modifier keys. */
#define NUM_MODIFIER_KEYS        (NUM_KEYS - NUM_NORMAL_KEYS)

/** Num lock LED index. */
#define LED_NUMLOCK        LED_BLUE

/*---------------------------------------------------------------------------
 *       External variables
 *---------------------------------------------------------------------------*/

/** Descriptor list for HID keyboard device */
extern USBDDriverDescriptors hidd_keyboard_driver_descriptors;

/*---------------------------------------------------------------------------
 *       Internal variables
 *---------------------------------------------------------------------------*/

#ifdef NO_PUSHBUTTON
#else
/** List of pins_push_buttons to configure for the application. */
static struct _pin pins_push_buttons[] = { PINS_PUSHBUTTONS };
#endif

/** Array of key codes produced by each button. */
static uint8_t key_codes[NUM_KEYS] = {
	HIDKeypad_A,
	HIDKeypad_NUMLOCK,
};

/** Current status (pressed or not) for each key. */
static uint8_t key_status[NUM_KEYS];

/*---------------------------------------------------------------------------
 *       VBus monitoring (optional)
 *---------------------------------------------------------------------------*/

/** VBus pin instance. */
static const struct _pin pin_vbus = PIN_USB_VBUS;


/**
 * Handles interrupts coming from PIO controllers.
 */

/**
 * \brief Handler for Buttons rising edge interrupt.
 *
 * Handle process led1 status change.
 */
static void pio_handler(uint32_t mask, uint32_t status, void* user_arg)
{

	if (status & pin_vbus.mask){
		usbd_connect();
	} else {
		usbd_disconnect();
	}
}

/**
 * Configures the VBus pin to trigger an interrupt when the level on that pin
 * changes.
 */
static void vbus_configure( void )
{
	printf("vbus configuration\n\r");

	/* Configure PIO */
	pio_configure(&pin_vbus, 1);

	/*
	 * Initialize pios interrupt with its handlers, see
	 * PIO definition in board.h.
	 */
	pio_configure_it(&pin_vbus);
	pio_add_handler_to_group(pin_vbus.group,
				pin_vbus.mask, pio_handler, NULL);

	/* Enable PIO line interrupts. */
	pio_enable_it(&pin_vbus);

	/* Check current level on VBus */
	if (pio_get(&pin_vbus)) {

		/* if VBUS present, force the connect */
		printf("conn\n\r");
		usbd_connect();
	}
	else {
		printf("disconn\n\r");
		usbd_disconnect();
	}
}

/*----------------------------------------------------------------------------
 *       USB Power Control
 *----------------------------------------------------------------------------*/

#ifdef PIN_USB_POWER_ENA
/** Power Enable A (MicroAB Socket) pin instance. */
static const struct _pin pin_pon_a = PIN_USB_POWER_ENA;
#endif
#ifdef PIN_USB_POWER_ENB
/** Power Enable B (A Socket) pin instance. */
static const struct _pin pin_pon_b = PIN_USB_POWER_ENB;
#endif
#ifdef PIN_USB_OVCUR
/** Power Enable C (A Socket) pin instance. */
static const struct _pin pin_pon_c = PIN_USB_OVCUR;
#endif
/**
 * Configures the Power Enable pin to disable self power.
 */
static void usb_power_configure( void )
{
#ifdef PIN_USB_POWER_ENA
	pio_configure(&pin_pon_a, 1);
#endif
#ifdef PIN_USB_POWER_ENB
	pio_configure(&pin_pon_b, 1);
#endif
#ifdef PIN_USB_OVCUR
	pio_configure(&pin_pon_c, 1);
#endif
}

/*---------------------------------------------------------------------------
 *    Callbacks re-implementation
 *---------------------------------------------------------------------------*/

/**
 * Invoked whenever a SETUP request is received from the host. Forwards the
 * request to the standard handler.
 */
void usbd_callbacks_request_received(const USBGenericRequest *request)
{
	hidd_keyboard_driver_request_handler(request);
}

/**
 * Invoked when the configuration of the device changes. Start reading
 * output reports.
 * \param cfgnum New configuration number.
 */
void usbd_driver_callbacks_configuration_changed(uint8_t cfgnum)
{
	hidd_keyboard_driver_configuration_changed_handler(cfgnum);
}

/**
 * Invoked when the status of the keyboard LEDs changes. Turns the num. lock
 * LED on or off.
 * \param num_lock_status    Indicates the current status of the num. lock key.
 * \param caps_lock_status   Indicates the current status of the caps lock key.
 * \param scroll_lock_status Indicates the current status of the scroll lock key.
 */
void hidd_keyboard_callbacks_leds_changed(
	uint8_t num_lock_status,
	uint8_t caps_lock_status,
	uint8_t scroll_lock_status)
{
	printf("%c %c %c\n\r",
		num_lock_status ? 'N':'_',
		caps_lock_status ? 'C':'_',
		scroll_lock_status ? 'S':'_'
		);
	/* Num. lock */
	if (num_lock_status) {

		led_set(LED_NUMLOCK);
	}
	else {

		led_clear(LED_NUMLOCK);
	}
}

/*----------------------------------------------------------------------------
 *       Internal functions
 *----------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
 *       Exported function
 *---------------------------------------------------------------------------*/

/**
 * Initializes the system and then monitors buttons, sending the
 * corresponding character when one is pressed.
 * \callgraph
 */
int main(void)
{
	uint8_t pressed_keys[NUM_KEYS];
	uint8_t pressed_keys_size;
	uint8_t released_keys[NUM_KEYS];
	uint8_t released_keys_size;
	uint32_t i;

	/* Disable watchdog */
	wdt_disable();

#ifndef VARIANT_DDRAM
	mmu_initialize();
	cp15_enable_mmu();
	cp15_enable_dcache();
	cp15_enable_icache();
#endif

	printf("-- USB Device HID Keyboard Project %s --\n\r", SOFTPACK_VERSION);
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	/* If they are present, configure Vbus & Wake-up pins */
	pio_reset_all_it();

	/* Initialize all USB power (off) */
	usb_power_configure();

#ifdef NO_PUSHBUTTON
	printf( "-- : DBG key 1 2 used as buttons\n\r" );
	printf( "-- : 1st press to push, 2nd press to release\n\r" );
#else
	/* Initialize key statuses and configure push buttons */
	pio_configure(pins_push_buttons, ARRAY_SIZE(pins_push_buttons));
#endif
	memset(key_status, 1, NUM_KEYS);

	/* Configure LEDs */
	led_configure(LED_NUMLOCK);

	/* HID driver initialization */
	hidd_keyboard_driver_initialize(&hidd_keyboard_driver_descriptors);

	/* connect if needed */
	vbus_configure();

	/* Infinite loop */
	while (1) {
		pressed_keys_size = 0;
		released_keys_size = 0;

		if (usbd_get_state() < USBD_STATE_CONFIGURED)
			continue;

#ifdef NO_PUSHBUTTON
		if (console_is_rx_ready())
		{
			uint8_t key = console_get_char();
			switch(key)
			{
			case '1':
			case '2':
				i = key - '1';
				if (key_status[i])
				{
					/* Key press simulation */
					trace_info("Key %u pressed\n\r", (unsigned int)i);
					key_status[i] = 0;
					pressed_keys[pressed_keys_size] = key_codes[i];
					pressed_keys_size ++;
					hidd_keyboard_remote_wakeup();
				}
				else
				{
					/* Key release simulation */
					trace_info("Key %u released\n\r", (unsigned int)i);
					key_status[i] = 1;
					released_keys[released_keys_size] = key_codes[i];
					released_keys_size++;
				}
				break;
			default:
				console_put_char(key);
			}
		}
#else
		/* Monitor buttons */
		for (i = 0; i < ARRAY_SIZE(pins_push_buttons); i++) {
			/* Check if button state has changed */
			uint8_t is_button_pressed = pio_get(&(pins_push_buttons[i]));
			if (is_button_pressed != key_status[i]) {
				/* Update button state */
				if (!is_button_pressed) {
					/* Key has been pressed */
					printf("BP %u pressed\n\r", (unsigned int)i);
					key_status[i] = 0;
					pressed_keys[pressed_keys_size] = key_codes[i];
					pressed_keys_size++;
					hidd_keyboard_driver_remote_wakeup();
				} else {
					/* Key has been released */
					printf("BP %u released\n\r", (unsigned int)i);
					key_status[i] = 1;
					released_keys[released_keys_size] = key_codes[i];
					released_keys_size++;
				}
			}
		}
#endif

		/* Update key status in the HID driver if necessary */
		if (pressed_keys_size > 0 || released_keys_size > 0) {
			uint8_t status;
			do {
				status = hidd_keyboard_driver_change_keys(
						pressed_keys, pressed_keys_size,
						released_keys, released_keys_size);
			}
			while (status != USBD_STATUS_SUCCESS);
		}

	}
}
/** \endcond */
