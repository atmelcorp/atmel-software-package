/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2011, Atmel Corporation
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

/**\file
	Title: HIDDKeyboardDriverDescriptors

	About: Purpose
		Declaration of the descriptors used by the HID device keyboard driver.
*/

/** \addtogroup usbd_hid_key
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "usb/common/hid/hid_descriptors.h"
#include "usb/common/usb_descriptors.h"
#include "usb/device/hid/hidd_keyboard_driver.h"
#include "usb/device/usbd_driver.h"

/*------------------------------------------------------------------------------
 *         Definitions
 *------------------------------------------------------------------------------*/

/** \addtogroup usbd_hid_device_desc HID Device Descriptor IDs
 *      @{
 * This page lists VID, PID & Release number.
 *
 * \section IDs
 * - HIDDKeyboardDriverDescriptors_PRODUCTID
 * - HIDDKeyboardDriverDescriptors_VENDORID
 * - HIDDKeyboardDriverDescriptors_RELEASE
 */

/** Device product ID. */
#define HIDDKeyboardDriverDescriptors_PRODUCTID       0x6127
/** Device vendor ID. */
#define HIDDKeyboardDriverDescriptors_VENDORID        0x03EB
/** Device release number. */
#define HIDDKeyboardDriverDescriptors_RELEASE         0x0100
/**      @}*/

/** \addtogroup usbd_hid_keyboard_config USB HID Keyboard Device Configure
 *      @{
 * This page lists the defines used by the HID Keyboard Device Driver.
 *
 * \section hidd_k_ep_addr Endpoint Addresses
 * - \ref HIDDKeyboardDriverDescriptors_INTERRUPTIN
 * - \ref HIDDKeyboardDriverDescriptors_INTERRUPTOUT
 * \section hidd_k_ep_polling Endpoint Polling Rate
 * - \ref HIDDKeyboardDriverDescriptors_INTERRUPTIN_POLLING
 * - \ref HIDDKeyboardDriverDescriptors_INTERRUPTOUT_POLLING
 */
/** Interrupt IN endpoint number */
#define HIDDKeyboardDriverDescriptors_INTERRUPTIN           1
/** Interrupt IN endpoint polling rate (in milliseconds) */
#define HIDDKeyboardDriverDescriptors_INTERRUPTIN_POLLING   10
/** Interrupt OUT endpoint number */
#define HIDDKeyboardDriverDescriptors_INTERRUPTOUT          2
/** Interrupt OUT endpoint polling rate (in milliseconds) */
#define HIDDKeyboardDriverDescriptors_INTERRUPTOUT_POLLING  10
/**     @}*/

/*------------------------------------------------------------------------------
 *         Internal types
 *------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 *         Internal variables
 *------------------------------------------------------------------------------*/

/** Device descriptor. */
static const USBDeviceDescriptor deviceDescriptor = {

    sizeof(USBDeviceDescriptor),
    USBGenericDescriptor_DEVICE,
    USBDeviceDescriptor_USB2_00,
    HIDDeviceDescriptor_CLASS,
    HIDDeviceDescriptor_SUBCLASS,
    HIDDeviceDescriptor_PROTOCOL,
    CHIP_USB_ENDPOINT_MAXPACKETSIZE(0),
    HIDDKeyboardDriverDescriptors_VENDORID,
    HIDDKeyboardDriverDescriptors_PRODUCTID,
    HIDDKeyboardDriverDescriptors_RELEASE,
    1, /* Index of manufacturer description */
    2, /* Index of product description */
    3, /* Index of serial number description */
    1  /* One possible configuration */
};

/** Device qualifier descriptor (to pass USB test). */
static const USBDeviceQualifierDescriptor qualifierDescriptor = {

	sizeof(USBDeviceQualifierDescriptor),
	USBGenericDescriptor_DEVICEQUALIFIER,
	USBDeviceDescriptor_USB2_00,
	HIDDeviceDescriptor_CLASS,
	HIDDeviceDescriptor_SUBCLASS,
	HIDDeviceDescriptor_PROTOCOL,
	CHIP_USB_ENDPOINT_MAXPACKETSIZE(0),
	0, // Device has no other speed configuration
	0x00
};

/** Configuration descriptor. */
static const HIDDKeyboardDriverConfigurationDescriptors configurationDescriptors = {

    /* Configuration descriptor */
    {
        sizeof(USBConfigurationDescriptor),
        USBGenericDescriptor_CONFIGURATION,
        sizeof(HIDDKeyboardDriverConfigurationDescriptors),
        1, /* One interface in this configuration */
        1, /* This is configuration #1 */
        0, /* No associated string descriptor */
        BOARD_USB_BMATTRIBUTES,
        USBConfigurationDescriptor_POWER(100)
    },
    /* Interface descriptor */
    {
        sizeof(USBInterfaceDescriptor),
        USBGenericDescriptor_INTERFACE,
        0, /* This is interface #0 */
        0, /* This is alternate setting #0 */
        2, /* Two endpoints used */
        HIDInterfaceDescriptor_CLASS,
        HIDInterfaceDescriptor_SUBCLASS_NONE,
        HIDInterfaceDescriptor_PROTOCOL_NONE,
        0  /* No associated string descriptor */
    },
    /* HID descriptor */
    {
        sizeof(HIDDescriptor1),
        HIDGenericDescriptor_HID,
        HIDDescriptor_HID1_11,
        0, /* Device is not localized, no country code */
        1, /* One HID-specific descriptor (apart from this one) */
        HIDGenericDescriptor_REPORT,
        {HIDDKeyboard_REPORTDESCRIPTORSIZE}
    },
    /* Interrupt IN endpoint descriptor */
    {
        sizeof(USBEndpointDescriptor),
        USBGenericDescriptor_ENDPOINT,
        USBEndpointDescriptor_ADDRESS(
            USBEndpointDescriptor_IN,
            HIDDKeyboardDriverDescriptors_INTERRUPTIN),
        USBEndpointDescriptor_INTERRUPT,
        sizeof(HIDDKeyboardInputReport),
        HIDDKeyboardDriverDescriptors_INTERRUPTIN_POLLING
    },
    /* Interrupt OUT endpoint descriptor */
    {
        sizeof(USBEndpointDescriptor),
        USBGenericDescriptor_ENDPOINT,
        USBEndpointDescriptor_ADDRESS(
            USBEndpointDescriptor_OUT,
            HIDDKeyboardDriverDescriptors_INTERRUPTOUT),
        USBEndpointDescriptor_INTERRUPT,
        sizeof(HIDDKeyboardOutputReport),
        HIDDKeyboardDriverDescriptors_INTERRUPTIN_POLLING
    }
};

/** Language ID string descriptor. */
static const unsigned char languageIdDescriptor[] = {

    USBStringDescriptor_LENGTH(1),
    USBGenericDescriptor_STRING,
    USBStringDescriptor_ENGLISH_US
};

/** Manufacturer name. */
static const unsigned char manufacturerDescriptor[] = {

    USBStringDescriptor_LENGTH(5),
    USBGenericDescriptor_STRING,
    USBStringDescriptor_UNICODE('A'),
    USBStringDescriptor_UNICODE('T'),
    USBStringDescriptor_UNICODE('M'),
    USBStringDescriptor_UNICODE('E'),
    USBStringDescriptor_UNICODE('L')
};

/** Product name. */
static const unsigned char productDescriptor[] = {

    USBStringDescriptor_LENGTH(23),
    USBGenericDescriptor_STRING,
    USBStringDescriptor_UNICODE('A'),
    USBStringDescriptor_UNICODE('T'),
    USBStringDescriptor_UNICODE('M'),
    USBStringDescriptor_UNICODE('E'),
    USBStringDescriptor_UNICODE('L'),
    USBStringDescriptor_UNICODE(' '),
    USBStringDescriptor_UNICODE('A'),
    USBStringDescriptor_UNICODE('T'),
    USBStringDescriptor_UNICODE('9'),
    USBStringDescriptor_UNICODE('1'),
    USBStringDescriptor_UNICODE(' '),
    USBStringDescriptor_UNICODE('H'),
    USBStringDescriptor_UNICODE('I'),
    USBStringDescriptor_UNICODE('D'),
    USBStringDescriptor_UNICODE(' '),
    USBStringDescriptor_UNICODE('K'),
    USBStringDescriptor_UNICODE('E'),
    USBStringDescriptor_UNICODE('Y'),
    USBStringDescriptor_UNICODE('B'),
    USBStringDescriptor_UNICODE('O'),
    USBStringDescriptor_UNICODE('A'),
    USBStringDescriptor_UNICODE('R'),
    USBStringDescriptor_UNICODE('D')
};

/** Product serial number. */
static const unsigned char serialNumberDescriptor[] = {

    USBStringDescriptor_LENGTH(12),
    USBGenericDescriptor_STRING,
    USBStringDescriptor_UNICODE('0'),
    USBStringDescriptor_UNICODE('1'),
    USBStringDescriptor_UNICODE('2'),
    USBStringDescriptor_UNICODE('3'),
    USBStringDescriptor_UNICODE('4'),
    USBStringDescriptor_UNICODE('5'),
    USBStringDescriptor_UNICODE('6'),
    USBStringDescriptor_UNICODE('7'),
    USBStringDescriptor_UNICODE('8'),
    USBStringDescriptor_UNICODE('9'),
    USBStringDescriptor_UNICODE('A'),
    USBStringDescriptor_UNICODE('F')
};

/** Array of pointers to string descriptors. */
static const unsigned char *stringDescriptors[] = {

    languageIdDescriptor,
    manufacturerDescriptor,
    productDescriptor,
    serialNumberDescriptor
};

/*------------------------------------------------------------------------------
 *         Exported variables
 *------------------------------------------------------------------------------*/

/** List of descriptors used by the HID keyboard driver. */
USBDDriverDescriptors hidd_keyboard_driver_descriptors = {

    &deviceDescriptor,
    (USBConfigurationDescriptor *) &configurationDescriptors,
    &qualifierDescriptor,
    0, /* No full-speed other speed configuration */
    0, /* No high-speed device descriptor */
    0, /* No high-speed configuration descriptor */
    &qualifierDescriptor,
    0, /* No high-speed other speed configuration descriptor */
    stringDescriptors,
    4 /* Four string descriptors in list */
};

/**@}*/
