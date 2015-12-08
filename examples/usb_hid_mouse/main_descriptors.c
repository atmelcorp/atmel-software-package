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

/**\file
 * Declaration of the descriptors used by the HID device keyboard driver.
 */

/** \addtogroup usbd_hid_mouse
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "board.h"
#include "usb/device/hid/hidd_mouse_driver.h"

/*------------------------------------------------------------------------------
 *         Definitions
 *------------------------------------------------------------------------------*/

/** \addtogroup usbd_hid_mouse_id
 *      @{
 *
 * \section IDs
 * - HIDDMouseDriverDescriptors_PRODUCTID
 * - HIDDMouseDriverDescriptors_VENDORID
 * - HIDDMouseDriverDescriptors_RELEASE
 */

/** Device product ID. */
#define HIDDMouseDriverDescriptors_PRODUCTID       0x6200
/** Device vendor ID. */
#define HIDDMouseDriverDescriptors_VENDORID        0x03EB
/** Device release number. */
#define HIDDMouseDriverDescriptors_RELEASE         0x0100
/**      @}*/

/** \addtogroup usbd_hid_mouse_config USB HID Mouse Device Configure
 *      @{
 * This page lists the defines used by the HID Mouse Device Driver.
 *
 * \section hidd_m_ep_addr Endpoint Addresses
 * - \ref HIDDMouseDriverDescriptors_INTERRUPTIN
 * \section hidd_m_ep_polling Endpoint Polling Rate
 * - \ref HIDDMouseDriverDescriptors_INTERRUPTIN_POLLING
 */
/** Interrupt IN endpoint number */
#define HIDDMouseDriverDescriptors_INTERRUPTIN           1
/** Interrupt IN endpoint polling rate (in milliseconds) */
#define HIDDMouseDriverDescriptors_INTERRUPTIN_POLLING   10
/**     @}*/

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
	HIDDMouseDriverDescriptors_VENDORID,
	HIDDMouseDriverDescriptors_PRODUCTID,
	HIDDMouseDriverDescriptors_RELEASE,
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
	0, // Device has no other speed configuration.
	0x00
};

/** Configuration descriptor. */
static const HIDDMouseDriverConfigurationDescriptors configurationDescriptors = {

	/* Configuration descriptor */
	{
		sizeof(USBConfigurationDescriptor),
		USBGenericDescriptor_CONFIGURATION,
		sizeof(HIDDMouseDriverConfigurationDescriptors),
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
		1, /* One endpoints used */
		HIDInterfaceDescriptor_CLASS,
		HIDInterfaceDescriptor_SUBCLASS_NONE,
		HIDInterfaceDescriptor_PROTOCOL_MOUSE,
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
		{HIDDMouseDriver_REPORTDESCRIPTORSIZE}
	},
	/* Interrupt IN endpoint descriptor */
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(
			USBEndpointDescriptor_IN,
			HIDDMouseDriverDescriptors_INTERRUPTIN),
		USBEndpointDescriptor_INTERRUPT,
		sizeof(HIDDMouseInputReport),
		HIDDMouseDriverDescriptors_INTERRUPTIN_POLLING
	}
};

/**
 *   Variables: String descriptors
 *       languageIdDescriptor - Language ID string descriptor.
 *       manufacturerDescriptor - Manufacturer name.
 *       productDescriptor - Product name.
 *       serialNumberDescriptor - Product serial number.
 *       stringDescriptors - Array of pointers to string descriptors.
 */
static const unsigned char languageIdDescriptor[] = {

	USBStringDescriptor_LENGTH(1),
	USBGenericDescriptor_STRING,
	USBStringDescriptor_ENGLISH_US
};

static const unsigned char manufacturerDescriptor[] = {

	USBStringDescriptor_LENGTH(5),
	USBGenericDescriptor_STRING,
	USBStringDescriptor_UNICODE('A'),
	USBStringDescriptor_UNICODE('T'),
	USBStringDescriptor_UNICODE('M'),
	USBStringDescriptor_UNICODE('E'),
	USBStringDescriptor_UNICODE('L')
};

static const unsigned char productDescriptor[] = {

	USBStringDescriptor_LENGTH(19),
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
	USBStringDescriptor_UNICODE('M'),
	USBStringDescriptor_UNICODE('O'),
	USBStringDescriptor_UNICODE('U'),
	USBStringDescriptor_UNICODE('S'),
	USBStringDescriptor_UNICODE('E'),
};

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

static const unsigned char *stringDescriptors[] = {

	languageIdDescriptor,
	manufacturerDescriptor,
	productDescriptor,
	serialNumberDescriptor
};

/*------------------------------------------------------------------------------ */
/*         Exported variables */
/*------------------------------------------------------------------------------ */

/** List of descriptors used by the HID keyboard driver. */
USBDDriverDescriptors hidd_mouse_driver_descriptors = {

	&deviceDescriptor,
	(USBConfigurationDescriptor *) &configurationDescriptors,
	&qualifierDescriptor,
	0, /* No full-speed other speed configuration */
	0, /* No high-speed device descriptor (uses FS one) */
	0, /* No high-speed configuration descriptor (uses FS one) */
	&qualifierDescriptor,
	0, /* No high-speed other speed configuration descriptor */
	stringDescriptors,
	4 /* Four string descriptors in list */
};

/**@}*/
