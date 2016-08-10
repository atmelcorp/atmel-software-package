/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012, Atmel Corporation
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

/** \addtogroup usbd_composite_cdchid
 *@{
 */

/*----------------------------------------------------------------------------
 *      Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "usb/device/cdc/cdcd_serial.h"
#include "usb/device/composite/cdc_hidd_driver.h"
#include "usb/device/hid/hidd_keyboard.h"

#include "main_descriptors.h"

/*---------------------------------------------------------------------------
 *         Definitions
 *---------------------------------------------------------------------------*/

/** Address of the CDC interrupt-in endpoint. */
#define CDCD_Descriptors_NOTIFICATION0              3
/** Address of the CDC bulk-in endpoint. */
#define CDCD_Descriptors_DATAIN0                    2
/** Address of the CDC bulk-out endpoint. */
#define CDCD_Descriptors_DATAOUT0                   1

/** Address of the HID interrupt IN endpoint. */
#define HIDD_Descriptors_INTERRUPTIN                4
/** Address of the HID interrupt OUT endpoint. */
#define HIDD_Descriptors_INTERRUPTOUT               5


/** Device product ID. */
#define CDCHIDDDriverDescriptors_PRODUCTID       0x6130
/** Device vendor ID (Atmel). */
#define CDCHIDDDriverDescriptors_VENDORID        0x03EB
/** Device release number. */
#define CDCHIDDDriverDescriptors_RELEASE         0x0003

/*---------------------------------------------------------------------------
 *         Macros
 *---------------------------------------------------------------------------*/

/** Returns the minimum between two values. */
#define MIN(a, b)       ((a < b) ? a : b)

/*---------------------------------------------------------------------------
 *         Internal structures
 *---------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------
 *         Exported variables
 *----------------------------------------------------------------------------*/

/** Standard USB device descriptor for the composite device driver */
static const USBDeviceDescriptor deviceDescriptor = {

	sizeof(USBDeviceDescriptor),
	USBGenericDescriptor_DEVICE,
	USBDeviceDescriptor_USB2_00,
	0xEF,/* MI */
	0x02,/* */
	0x01,/* */
	CHIP_USB_ENDPOINT_MAXPACKETSIZE(0),
	CDCHIDDDriverDescriptors_VENDORID,
	CDCHIDDDriverDescriptors_PRODUCTID,
	CDCHIDDDriverDescriptors_RELEASE,
	0, /* No string descriptor for manufacturer */
	1, /* Index of product string descriptor is #1 */
	0, /* No string descriptor for serial number */
	1 /* Device has 1 possible configuration */
};

/** Device qualifier descriptor (to pass USB test). */
static const USBDeviceQualifierDescriptor qualifierDescriptor = {

	sizeof(USBDeviceQualifierDescriptor),
	USBGenericDescriptor_DEVICEQUALIFIER,
	USBDeviceDescriptor_USB2_00,
	0xEF,/* MI */
	0x02,/* */
	0x01,/* */
	CHIP_USB_ENDPOINT_MAXPACKETSIZE(0),
	0, // Device has no other speed configuration.
	0x00
};

/** USB configuration descriptors for the composite device driver */
static const CdcHidDriverConfigurationDescriptors configurationDescriptorsFS =
{

	/* Standard configuration descriptor */
	{
		sizeof(USBConfigurationDescriptor),
		USBGenericDescriptor_CONFIGURATION,
		sizeof(CdcHidDriverConfigurationDescriptors),
		CDCHIDDDriverDescriptors_NUMINTERFACE,
		1, /* This is configuration #1 */
		0, /* No string descriptor for this configuration */
		BOARD_USB_BMATTRIBUTES,
		USBConfigurationDescriptor_POWER(100)
	},

	/* CDC 0 */
	/* IAD for CDC/ACM port */
	{
		sizeof(USBInterfaceAssociationDescriptor),
		USBGenericDescriptor_INTERFACEASSOCIATION,
		CDCHIDDDriverDescriptors_CDC_INTERFACE,
		2,
		CDCCommunicationInterfaceDescriptor_CLASS,
		CDCCommunicationInterfaceDescriptor_ABSTRACTCONTROLMODEL,
		CDCCommunicationInterfaceDescriptor_NOPROTOCOL,
		0  /* No string descriptor for this interface */
	},
	/* Communication class interface standard descriptor */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		CDCHIDDDriverDescriptors_CDC_INTERFACE, /* This is interface #0 */
		0, /* This is alternate setting #0 for this interface */
		1, /* This interface uses 1 endpoint */
		CDCCommunicationInterfaceDescriptor_CLASS,
		CDCCommunicationInterfaceDescriptor_ABSTRACTCONTROLMODEL,
		CDCCommunicationInterfaceDescriptor_NOPROTOCOL,
		0  /* No string descriptor for this interface */
	},
	/* Class-specific header functional descriptor */
	{
		sizeof(CDCHeaderDescriptor),
		CDCGenericDescriptor_INTERFACE,
		CDCGenericDescriptor_HEADER,
		CDCGenericDescriptor_CDC1_10
	},
	/* Class-specific call management functional descriptor */
	{
		sizeof(CDCCallManagementDescriptor),
		CDCGenericDescriptor_INTERFACE,
		CDCGenericDescriptor_CALLMANAGEMENT,
		CDCCallManagementDescriptor_SELFCALLMANAGEMENT,
		CDCHIDDDriverDescriptors_CDC_INTERFACE + 1 /* No associated data interface */
	},
	/* Class-specific abstract control management functional descriptor */
	{
		sizeof(CDCAbstractControlManagementDescriptor),
		CDCGenericDescriptor_INTERFACE,
		CDCGenericDescriptor_ABSTRACTCONTROLMANAGEMENT,
		CDCAbstractControlManagementDescriptor_LINE
	},
	/* Class-specific union functional descriptor with one slave interface */
	{
		sizeof(CDCUnionDescriptor),
		CDCGenericDescriptor_INTERFACE,
		CDCGenericDescriptor_UNION,
		CDCHIDDDriverDescriptors_CDC_INTERFACE, /* Number of master interface is #0 */
		CDCHIDDDriverDescriptors_CDC_INTERFACE + 1 /* First slave interface is #1 */
	},
	/* Notification endpoint standard descriptor */
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_IN, CDCD_Descriptors_NOTIFICATION0),
		USBEndpointDescriptor_INTERRUPT,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(CDCD_Descriptors_NOTIFICATION0),
			CDCDSerialPort_INTERRUPT_MAXPACKETSIZE),
		CDCDSerialPort_INTERRUPT_INTERVAL_FS
	},
	/* Data class interface standard descriptor */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		CDCHIDDDriverDescriptors_CDC_INTERFACE + 1, /* This is interface #1 */
		0, /* This is alternate setting #0 for this interface */
		2, /* This interface uses 2 endpoints */
		CDCDataInterfaceDescriptor_CLASS,
		CDCDataInterfaceDescriptor_SUBCLASS,
		CDCDataInterfaceDescriptor_NOPROTOCOL,
		0  /* No string descriptor for this interface */
	},
	/* Bulk-OUT endpoint standard descriptor */
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_OUT, CDCD_Descriptors_DATAOUT0),
		USBEndpointDescriptor_BULK,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(CDCD_Descriptors_DATAOUT0),
			USBEndpointDescriptor_MAXBULKSIZE_FS),
		0 /* Must be 0 for full-speed bulk endpoints */
	},
	/* Bulk-IN endpoint descriptor */
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_IN, CDCD_Descriptors_DATAIN0),
		USBEndpointDescriptor_BULK,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(CDCD_Descriptors_DATAIN0),
			USBEndpointDescriptor_MAXBULKSIZE_FS),
		0 /* Must be 0 for full-speed bulk endpoints */
	},

	/* HID */
	/* Interface descriptor */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		CDCHIDDDriverDescriptors_HID_INTERFACE,
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
		/*
		{
		 HIDDKeyboard_REPORTDESCRIPTORSIZE & 0xFF,
		(HIDDKeyboard_REPORTDESCRIPTORSIZE >> 8) & 0xFF
		}*/
	},
	/* Interrupt IN endpoint descriptor */
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(
			USBEndpointDescriptor_IN,
			HIDD_Descriptors_INTERRUPTIN),
		USBEndpointDescriptor_INTERRUPT,
		sizeof(HIDDKeyboardInputReport),
		HIDDKeyboardDescriptors_INTERRUPTIN_POLLING_FS
	},
	/* Interrupt OUT endpoint descriptor */
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(
			USBEndpointDescriptor_OUT,
			HIDD_Descriptors_INTERRUPTOUT),
		USBEndpointDescriptor_INTERRUPT,
		sizeof(HIDDKeyboardOutputReport),
		HIDDKeyboardDescriptors_INTERRUPTOUT_POLLING_FS
	}
};

/** USB configuration descriptors for the composite device driver */
static const CdcHidDriverConfigurationDescriptors configurationDescriptorsHS =
{

	/* Standard configuration descriptor */
	{
		sizeof(USBConfigurationDescriptor),
		USBGenericDescriptor_CONFIGURATION,
		sizeof(CdcHidDriverConfigurationDescriptors),
		CDCHIDDDriverDescriptors_NUMINTERFACE,
		1, /* This is configuration #1 */
		0, /* No string descriptor for this configuration */
		BOARD_USB_BMATTRIBUTES,
		USBConfigurationDescriptor_POWER(100)
	},

	/* CDC 0 */
	/* IAD for CDC/ACM port */
	{
		sizeof(USBInterfaceAssociationDescriptor),
		USBGenericDescriptor_INTERFACEASSOCIATION,
		CDCHIDDDriverDescriptors_CDC_INTERFACE,
		2,
		CDCCommunicationInterfaceDescriptor_CLASS,
		CDCCommunicationInterfaceDescriptor_ABSTRACTCONTROLMODEL,
		CDCCommunicationInterfaceDescriptor_NOPROTOCOL,
		0  /* No string descriptor for this interface */
	},
	/* Communication class interface standard descriptor */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		CDCHIDDDriverDescriptors_CDC_INTERFACE, /* This is interface #0 */
		0, /* This is alternate setting #0 for this interface */
		1, /* This interface uses 1 endpoint */
		CDCCommunicationInterfaceDescriptor_CLASS,
		CDCCommunicationInterfaceDescriptor_ABSTRACTCONTROLMODEL,
		CDCCommunicationInterfaceDescriptor_NOPROTOCOL,
		0  /* No string descriptor for this interface */
	},
	/* Class-specific header functional descriptor */
	{
		sizeof(CDCHeaderDescriptor),
		CDCGenericDescriptor_INTERFACE,
		CDCGenericDescriptor_HEADER,
		CDCGenericDescriptor_CDC1_10
	},
	/* Class-specific call management functional descriptor */
	{
		sizeof(CDCCallManagementDescriptor),
		CDCGenericDescriptor_INTERFACE,
		CDCGenericDescriptor_CALLMANAGEMENT,
		CDCCallManagementDescriptor_SELFCALLMANAGEMENT,
		CDCHIDDDriverDescriptors_CDC_INTERFACE + 1 /* No associated data interface */
	},
	/* Class-specific abstract control management functional descriptor */
	{
		sizeof(CDCAbstractControlManagementDescriptor),
		CDCGenericDescriptor_INTERFACE,
		CDCGenericDescriptor_ABSTRACTCONTROLMANAGEMENT,
		CDCAbstractControlManagementDescriptor_LINE
	},
	/* Class-specific union functional descriptor with one slave interface */
	{
		sizeof(CDCUnionDescriptor),
		CDCGenericDescriptor_INTERFACE,
		CDCGenericDescriptor_UNION,
		CDCHIDDDriverDescriptors_CDC_INTERFACE, /* Number of master interface is #0 */
		CDCHIDDDriverDescriptors_CDC_INTERFACE + 1 /* First slave interface is #1 */
	},
	/* Notification endpoint standard descriptor */
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_IN, CDCD_Descriptors_NOTIFICATION0),
		USBEndpointDescriptor_INTERRUPT,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(CDCD_Descriptors_NOTIFICATION0),
			CDCDSerialPort_INTERRUPT_MAXPACKETSIZE),
		CDCDSerialPort_INTERRUPT_INTERVAL_HS
	},
	/* Data class interface standard descriptor */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		CDCHIDDDriverDescriptors_CDC_INTERFACE + 1, /* This is interface #1 */
		0, /* This is alternate setting #0 for this interface */
		2, /* This interface uses 2 endpoints */
		CDCDataInterfaceDescriptor_CLASS,
		CDCDataInterfaceDescriptor_SUBCLASS,
		CDCDataInterfaceDescriptor_NOPROTOCOL,
		0  /* No string descriptor for this interface */
	},
	/* Bulk-OUT endpoint standard descriptor */
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_OUT, CDCD_Descriptors_DATAOUT0),
		USBEndpointDescriptor_BULK,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(CDCD_Descriptors_DATAOUT0),
			USBEndpointDescriptor_MAXBULKSIZE_HS),
		0 /* Must be 0 for full-speed bulk endpoints */
	},
	/* Bulk-IN endpoint descriptor */
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_IN, CDCD_Descriptors_DATAIN0),
		USBEndpointDescriptor_BULK,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(CDCD_Descriptors_DATAIN0),
			USBEndpointDescriptor_MAXBULKSIZE_HS),
		0 /* Must be 0 for full-speed bulk endpoints */
	},

	/* HID */
	/* Interface descriptor */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		CDCHIDDDriverDescriptors_HID_INTERFACE,
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
		/*
		{
		 HIDDKeyboard_REPORTDESCRIPTORSIZE & 0xFF,
		(HIDDKeyboard_REPORTDESCRIPTORSIZE >> 8) & 0xFF
		}*/
	},
	/* Interrupt IN endpoint descriptor */
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(
			USBEndpointDescriptor_IN,
			HIDD_Descriptors_INTERRUPTIN),
		USBEndpointDescriptor_INTERRUPT,
		sizeof(HIDDKeyboardInputReport),
		HIDDKeyboardDescriptors_INTERRUPTIN_POLLING_HS
	},
	/* Interrupt OUT endpoint descriptor */
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(
			USBEndpointDescriptor_OUT,
			HIDD_Descriptors_INTERRUPTOUT),
		USBEndpointDescriptor_INTERRUPT,
		sizeof(HIDDKeyboardOutputReport),
		HIDDKeyboardDescriptors_INTERRUPTOUT_POLLING_HS
	}
};

/** String descriptor with the supported languages. */
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
	USBStringDescriptor_UNICODE('t'),
	USBStringDescriptor_UNICODE('m'),
	USBStringDescriptor_UNICODE('e'),
	USBStringDescriptor_UNICODE('l')
};

/** Product name. */
static const unsigned char productDescriptor[] = {

	USBStringDescriptor_LENGTH(14),
	USBGenericDescriptor_STRING,
	USBStringDescriptor_UNICODE('C'),
	USBStringDescriptor_UNICODE('o'),
	USBStringDescriptor_UNICODE('m'),
	USBStringDescriptor_UNICODE('p'),
	USBStringDescriptor_UNICODE('o'),
	USBStringDescriptor_UNICODE('s'),
	USBStringDescriptor_UNICODE('i'),
	USBStringDescriptor_UNICODE('t'),
	USBStringDescriptor_UNICODE('e'),
	USBStringDescriptor_UNICODE(' '),
	USBStringDescriptor_UNICODE('D'),
	USBStringDescriptor_UNICODE('e'),
	USBStringDescriptor_UNICODE('m'),
	USBStringDescriptor_UNICODE('o')
};

/** Product serial number. */
static const unsigned char serialNumberDescriptor[] = {

	USBStringDescriptor_LENGTH(4),
	USBGenericDescriptor_STRING,
	USBStringDescriptor_UNICODE('0'),
	USBStringDescriptor_UNICODE('1'),
	USBStringDescriptor_UNICODE('2'),
	USBStringDescriptor_UNICODE('3')
};

/** Array of pointers to the four string descriptors. */
static const unsigned char *stringDescriptors[] = {

	languageIdDescriptor,
	manufacturerDescriptor,
	productDescriptor,
	serialNumberDescriptor,
};

/*----------------------------------------------------------------------------
 *         Exported variables
 *----------------------------------------------------------------------------*/

/** List of descriptors required by an USB audio speaker device driver. */
const USBDDriverDescriptors cdc_hidd_driver_descriptors = {

	&deviceDescriptor,
	(const USBConfigurationDescriptor *) &configurationDescriptorsFS,
	&qualifierDescriptor,
	0,
	0,
	(const USBConfigurationDescriptor *) &configurationDescriptorsHS,
	&qualifierDescriptor,
	0,
	stringDescriptors,
	4 /* Number of string descriptors */
};
/**@}*/

