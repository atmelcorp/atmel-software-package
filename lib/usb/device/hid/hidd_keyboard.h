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
 * \file
 * Definition of methods for using a HID keyboard function.
 */

#ifndef HIDDKEYBOARD_H
#define HIDDKEYBOARD_H

/** \addtogroup usbd_hid_key
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "compiler.h"

#include "usb/common/usb_descriptors.h"
#include "usb/common/usb_requests.h"
#include "usb/common/hid/hid_descriptors.h"
#include "usb/device/usbd_driver.h"

/*------------------------------------------------------------------------------
 *         Definitions
 *------------------------------------------------------------------------------*/

/** \addtogroup usbd_hid_kbd_desc HIDD Keyboard Driver Definitions
 *  @{
 */

/** Maximum number of simultaneous key presses. */
#define HIDDKeyboardInputReport_MAXKEYPRESSES           3

/** \addtogroup usbd_hid_kbd_keys HID Keypad keys
 *      @{
 * This page lists definition for HID keypad keys.
 *
 * \section Keys
 * - HIDDKeyboardDescriptors_FIRSTMODIFIERKEY
 * - HIDDKeyboardDescriptors_LASTMODIFIERKEY
 * - HIDDKeyboardDescriptors_FIRSTSTANDARDKEY
 * - HIDDKeyboardDescriptors_LASTSTANDARDKEY
 */
/** Key code of the first accepted modifier key */
#define HIDDKeyboardDescriptors_FIRSTMODIFIERKEY  HIDKeypad_LEFTCONTROL
/** Key code of the last accepted modifier key */
#define HIDDKeyboardDescriptors_LASTMODIFIERKEY   HIDKeypad_RIGHTGUI
/** Key code of the first accepted standard key */
#define HIDDKeyboardDescriptors_FIRSTSTANDARDKEY  0
/** Key code of the last accepted standard key */
#define HIDDKeyboardDescriptors_LASTSTANDARDKEY   HIDKeypad_NUMLOCK
/**      @}*/

/** \addtogroup usbd_hid_kbd_polling HID Keyboard Default Polling Rates
 *      @{
 */
/** Default HID interrupt IN endpoint polling rate FS (16ms). */
#define HIDDKeyboardDescriptors_INTERRUPTIN_POLLING_FS     16
/** Default HID interrupt IN endpoint polling rate HS (16ms). */
#define HIDDKeyboardDescriptors_INTERRUPTIN_POLLING_HS     8
/** Default interrupt OUT endpoint polling rate FS (16ms). */
#define HIDDKeyboardDescriptors_INTERRUPTOUT_POLLING_FS    16
/** Default interrupt OUT endpoint polling rate HS (16ms). */
#define HIDDKeyboardDescriptors_INTERRUPTOUT_POLLING_HS    8
/**     @}*/

/** Size of the report descriptor in bytes */
#define HIDDKeyboard_REPORTDESCRIPTORSIZE                   61

/** @}*/

/*------------------------------------------------------------------------------
 *         Types
 *------------------------------------------------------------------------------*/


/**
 * \typedef HIDDKeyboardOutputReport
 * \brief HID output report structure used by the host to control the state of
 *        the keyboard LEDs.
 *
 * Only the first three bits are relevant, the other 5 are used as
 * padding bits.
 */
typedef PACKED_STRUCT _HIDDKeyboardOutputReport {

	uint8_t numLockStatus:1,      /** State of the num. lock LED. */
				  capsLockStatus:1,     /** State of the caps lock LED. */
				  scrollLockStatus:1,   /** State of the scroll lock LED. */
				  padding:5;            /** Padding bits. */

} HIDDKeyboardOutputReport;

/**
 * \typedef HIDDKeyboardInputReport
 * \brief HID input report structure used by the keyboard driver to notify the
 *        host of pressed keys.
 *
 * The first byte is used to report the state of modifier keys. The
 * other three contains the keycodes of the currently pressed keys.
 */
typedef PACKED_STRUCT _HIDDKeyboardInputReport {

	/** State of modifier keys. */
	uint8_t bmModifierKeys:8;
	/** Key codes of pressed keys. */
	uint8_t pressedKeys[HIDDKeyboardInputReport_MAXKEYPRESSES];
} HIDDKeyboardInputReport;


/**
 * \typedef HIDDKeyboardDriverConfigurationDescriptors
 * \brief List of descriptors that make up the configuration descriptors of a
 *        device using the HID keyboard driver.
 */
typedef PACKED_STRUCT _HIDDKeyboardDriverConfigurationDescriptors {

	/** Configuration descriptor. */
	USBConfigurationDescriptor configuration;
	/** Interface descriptor. */
	USBInterfaceDescriptor interface;
	/** HID descriptor. */
	HIDDescriptor1 hid;
	/** Interrupt IN endpoint descriptor. */
	USBEndpointDescriptor interruptIn;
	/** Interrupt OUT endpoint descriptor. */
	USBEndpointDescriptor interruptOut;

} HIDDKeyboardDriverConfigurationDescriptors;


/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

extern void hidd_keyboard_initialize(uint8_t bInterfaceNb);

extern void hidd_keyboard_configure_function(
	USBGenericDescriptor * pDescriptors,
	uint16_t wLength);

extern uint32_t hidd_keyboard_request_handler(
	const USBGenericRequest *request);

extern uint32_t hidd_keyboard_change_keys(
	uint8_t *pressedKeys,
	uint8_t pressedKeysSize,
	uint8_t *releasedKeys,
	uint8_t releasedKeysSize);

extern void hidd_keyboard_remote_wakeup(void);

extern void hidd_keyboard_callbacks_leds_changed(
	uint8_t numLockStatus,
	uint8_t capsLockStatus,
	uint8_t scrollLockStatus);


extern void hidd_keyboard_input_report_initialize(HIDDKeyboardInputReport *report);

extern void hidd_keyboard_input_report_press_standard_key(
	HIDDKeyboardInputReport *report,
	uint8_t key);

extern void hidd_keyboard_input_report_release_standard_key(
	HIDDKeyboardInputReport *report,
	uint8_t key);

extern void hidd_keyboard_input_report_press_modifier_key(
	HIDDKeyboardInputReport *report,
	uint8_t key);

extern void hidd_keyboard_input_report_release_modifier_key(
	HIDDKeyboardInputReport *report,
	uint8_t key);


extern void hidd_keyboard_output_report_initialize(
	HIDDKeyboardOutputReport *report);

extern uint8_t hidd_keyboard_output_report_get_numlock_status(
	const HIDDKeyboardOutputReport *report);

extern uint8_t hidd_keyboard_output_report_get_capslock_status(
	const HIDDKeyboardOutputReport *report);

extern uint8_t hidd_keyboard_output_report_get_scrolllock_status(
	const HIDDKeyboardOutputReport *report);

/**@}*/

#endif /*#ifndef HIDDKEYBOARD_H*/

