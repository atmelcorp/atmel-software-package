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

/** \file
 * \addtogroup usbd_hid_key
 *@{
 * Implement HID Keyboard Function For USB Device.
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "trace.h"

#include "chip.h"
#include "mm/cache.h"
#include "usb/common/usb_requests.h"
#include "usb/common/hid/hid_descriptors.h"
#include "usb/common/hid/hid_reports.h"
#include "usb/common/hid/hid_requests.h"
#include "usb/common/hid/hid_usages.h"
#include "usb/device/hid/hidd_function.h"
#include "usb/device/hid/hidd_keyboard.h"
#include "usb/device/usbd_driver.h"
#include "usb/device/usbd.h"

/*------------------------------------------------------------------------------
 *         Internal types
 *------------------------------------------------------------------------------*/

/**
 * Extended struct for an HID Keyboard Input report, for transfer driver to
 * send reports.
 */
typedef struct _KBDInputReport {
	/** Callback when report done */
	HIDDReportEventCallback fCallback;
	/** Callback arguments */
	void* pArg;

	/** Report size (ID + DATA) */
	uint16_t wMaxSize;
	/** Transfered size */
	uint16_t wTransferred;
	/** Report idle rate */
	uint8_t bIdleRate;
	/** Delay count for Idle */
	uint8_t bDelay;
	/** Report ID */
	uint8_t bID;
	/* Padding to reach L1_CACHE_BYTES alignement */
	uint8_t padding[17];
	/** Input Report Data Block */
	HIDDKeyboardInputReport sReport;
} KBDInputReport;

/**
 * Extended struct for an HID Keyboard Output report, for transfer driver to
 * polling reports.
 */
typedef struct _KBDOutputReport {
	/** Callback when report done */
	HIDDReportEventCallback fCallback;
	/** Callback arguments */
	void* pArg;

	/** Report size (ID + DATA) */
	uint16_t wMaxSize;
	/** Transfered size */
	uint16_t wTransferred;
	/** Report idle rate */
	uint8_t bIdleRate;
	/** Delay count for Idle */
	uint8_t bDelay;
	/** Report ID */
	uint8_t bID;
	/* Padding to reach L1_CACHE_BYTES alignement */
	uint8_t padding[17];
	/** Output Report Data Block */
	HIDDKeyboardOutputReport sReport;
} KBDOutputReport;

/**
 *  Driver structure for an HID device implementing keyboard functionalities.
 */
typedef struct _HIDDKeyboard {

	/** USB HID Functionn */
	HIDDFunction hid_drv;
	/** Input report list */
	HIDDReport *input_reports[1];
	/** Output report list */
	HIDDReport *output_reports[1];
} HIDDKeyboard;

/*------------------------------------------------------------------------------
 *         Internal variables
 *------------------------------------------------------------------------------*/

/** HIDD Keyboard Input Report Instance */
CACHE_ALIGNED static KBDInputReport input_report;

/** HIDD Keyboard Output Report Instance */
CACHE_ALIGNED static KBDOutputReport output_report;

/** Static instance of the HIDD keyboard device driver. */
static HIDDKeyboard hidd_keyboard;

/** Report descriptor used by the driver. */
static const uint8_t hidd_keyboard_report_descriptor[] = {

	HIDReport_GLOBAL_USAGEPAGE + 1, HIDGenericDesktop_PAGEID,
	HIDReport_LOCAL_USAGE + 1, HIDGenericDesktop_KEYBOARD,
	HIDReport_COLLECTION + 1, HIDReport_COLLECTION_APPLICATION,

		/* Input report: modifier keys */
		HIDReport_GLOBAL_REPORTSIZE + 1, 1,
		HIDReport_GLOBAL_REPORTCOUNT + 1, 8,
		HIDReport_GLOBAL_USAGEPAGE + 1, HIDKeypad_PAGEID,
		HIDReport_LOCAL_USAGEMINIMUM + 1,
			HIDDKeyboardDescriptors_FIRSTMODIFIERKEY,
		HIDReport_LOCAL_USAGEMAXIMUM + 1,
			HIDDKeyboardDescriptors_LASTMODIFIERKEY,
		HIDReport_GLOBAL_LOGICALMINIMUM + 1, 0,
		HIDReport_GLOBAL_LOGICALMAXIMUM + 1, 1,
		HIDReport_INPUT + 1, HIDReport_VARIABLE,

		/* Input report: standard keys */
		HIDReport_GLOBAL_REPORTCOUNT + 1, 3,
		HIDReport_GLOBAL_REPORTSIZE + 1, 8,
		HIDReport_GLOBAL_LOGICALMINIMUM + 1,
			HIDDKeyboardDescriptors_FIRSTSTANDARDKEY,
		HIDReport_GLOBAL_LOGICALMAXIMUM + 1,
			HIDDKeyboardDescriptors_LASTSTANDARDKEY,
		HIDReport_GLOBAL_USAGEPAGE + 1, HIDKeypad_PAGEID,
		HIDReport_LOCAL_USAGEMINIMUM + 1,
			HIDDKeyboardDescriptors_FIRSTSTANDARDKEY,
		HIDReport_LOCAL_USAGEMAXIMUM + 1,
			HIDDKeyboardDescriptors_LASTSTANDARDKEY,
		HIDReport_INPUT + 1, 0 /* Data array */,

		/* Output report: LEDs */
		HIDReport_GLOBAL_REPORTCOUNT + 1, 3,
		HIDReport_GLOBAL_REPORTSIZE + 1, 1,
		HIDReport_GLOBAL_USAGEPAGE + 1, HIDLeds_PAGEID,
		HIDReport_GLOBAL_LOGICALMINIMUM + 1, 0,
		HIDReport_GLOBAL_LOGICALMAXIMUM + 1, 1,
		HIDReport_LOCAL_USAGEMINIMUM + 1, HIDLeds_NUMLOCK,
		HIDReport_LOCAL_USAGEMAXIMUM + 1, HIDLeds_SCROLLLOCK,
		HIDReport_OUTPUT + 1, HIDReport_VARIABLE,

		/* Output report: padding */
		HIDReport_GLOBAL_REPORTCOUNT + 1, 1,
		HIDReport_GLOBAL_REPORTSIZE + 1, 5,
		HIDReport_OUTPUT + 1, HIDReport_CONSTANT,

	HIDReport_ENDCOLLECTION
};

/*------------------------------------------------------------------------------
 *         Internal functions
 *------------------------------------------------------------------------------*/

/**
 * Callback invoked when an output report has been received from the host.
 * Forward the new status of the LEDs to the user program via the
 * hidd_keyboard_callbacks_leds_changed callback.
 */
static void hidd_keyboard_report_received(void)
{
	HIDDKeyboardOutputReport *out = &output_report.sReport;

	/* Trigger callback */
	hidd_keyboard_callbacks_leds_changed(out->numLockStatus,
			out->capsLockStatus, out->scrollLockStatus);
}

/*------------------------------------------------------------------------------
 *      Exported functions
 *------------------------------------------------------------------------------*/

/**
 * Initializes the HID keyboard device driver SW.
 * (Init USBDDriver .., Init function driver .., Init USBD ...)
 * \param pUsbd        Pointer to USBDDriver instance.
 * \param bInterfaceNb Interface number for the function.
 */
void hidd_keyboard_initialize(uint8_t bInterfaceNb)
{
	HIDDKeyboard *p_keyboard = &hidd_keyboard;
	HIDDFunction *p_hidd = &p_keyboard->hid_drv;

	/* input report */
	hidd_function_initialize_report((HIDDReport*)&input_report,
			sizeof(HIDDKeyboardInputReport),
			0,
			NULL,
			NULL);
	hidd_keyboard_input_report_initialize(&input_report.sReport);

	/* output report */
	hidd_function_initialize_report((HIDDReport*)&output_report,
			sizeof(HIDDKeyboardOutputReport),
			0,
			(HIDDReportEventCallback)hidd_keyboard_report_received,
			NULL);
	hidd_keyboard_output_report_initialize(&output_report.sReport);

	/* Function initialize */
	p_keyboard->input_reports[0] = (HIDDReport*)&input_report;
	p_keyboard->output_reports[0] = (HIDDReport*)&output_report;
	hidd_function_initialize(p_hidd, bInterfaceNb,
			hidd_keyboard_report_descriptor,
			p_keyboard->input_reports, 1,
			p_keyboard->output_reports, 1);
}

/**
 * Configure function with expected descriptors and start functionality.
 * Usually invoked when device is configured.
 * \param descriptors Pointer to the descriptors for function configure.
 * \param length      Length of descriptors in number of bytes.
 */
void hidd_keyboard_configure_function(USBGenericDescriptor *descriptors,
		uint16_t length)
{
	HIDDKeyboard *p_keyboard = &hidd_keyboard;
	HIDDFunction *p_hidd = &p_keyboard->hid_drv;

	hidd_function_parse_interface(p_hidd, descriptors, length);

	/* Start receiving output reports */
	hidd_function_start_polling_outputs(p_hidd);
}

/**
 * Handles HID-specific SETUP request sent by the host.
 * \param request Pointer to a USBGenericRequest instance.
 * \return USBRC_SUCCESS if request is handled.
 */
uint32_t hidd_keyboard_request_handler(const USBGenericRequest *request)
{
	HIDDKeyboard *p_keyboard = &hidd_keyboard;
	HIDDFunction *p_hidd = &p_keyboard->hid_drv;

	LIBUSB_TRACE("Kbd ");

	/* Process HID requests */
	return hidd_function_request_handler(p_hidd, request);
}

/**
 * Reports a change in which keys are currently pressed or release to the
 * host.
 *
 * \param pressed_keys Pointer to an array of key codes indicating keys that have
 *                    been pressed since the last call to
 *                    hidd_keyboard_driver_change_keys().
 * \param pressed_keys_size Number of key codes in the pressed_keys array.
 * \param released_keys Pointer to an array of key codes indicates keys that have
 *                     been released since the last call to
 *                     hidd_keyboard_driver_change_keys().
 * \param released_keys_size Number of key codes in the released_keys array.
 * \return USBD_STATUS_SUCCESS if the report has been sent to the host;
 *        otherwise an error code.
 */
uint32_t hidd_keyboard_change_keys(uint8_t *pressed_keys, uint8_t pressed_keys_size,
		uint8_t *released_keys, uint8_t released_keys_size)
{
	HIDDKeyboard *p_keyboard = &hidd_keyboard;
	HIDDFunction *p_hidd = &p_keyboard->hid_drv;
	HIDDKeyboardInputReport *p_report =
		(HIDDKeyboardInputReport*)p_keyboard->input_reports[0]->bData;

	/* Press keys */
	while (pressed_keys_size > 0) {
		/* Check if this is a standard or modifier key */
		if (hid_keypad_is_modifier_key(*pressed_keys)) {
			hidd_keyboard_input_report_press_modifier_key(
					p_report, *pressed_keys);
		} else {
			hidd_keyboard_input_report_press_standard_key(
					p_report, *pressed_keys);
		}
		pressed_keys_size--;
		pressed_keys++;
	}

	/* Release keys */
	while (released_keys_size > 0) {
		/* Check if this is a standard or modifier key */
		if (hid_keypad_is_modifier_key(*released_keys)) {
			hidd_keyboard_input_report_release_modifier_key(
					p_report, *released_keys);
		} else {
			hidd_keyboard_input_report_release_standard_key(
					p_report, *released_keys);
		}
		released_keys_size--;
		released_keys++;
	}

	/* Send input report through the interrupt IN endpoint */
	return usbd_write(p_hidd->bPipeIN,
					  p_report, sizeof(HIDDKeyboardInputReport), 0, 0);
}

/**
 * Starts a remote wake-up sequence if the host has explicitly enabled it
 * by sending the appropriate SET_FEATURE request.
 */
void hidd_keyboard_remote_wakeup(void)
{
	/* Remote wake-up has been enabled */
	if (usbd_driver_is_remote_wakeup_enabled()) {
		usbd_remote_wakeup();
	}
}

/**@}*/
