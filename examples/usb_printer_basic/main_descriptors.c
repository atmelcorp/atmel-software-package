/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2019, Atmel Corporation
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

/** \addtogroup usbd_printer
 *@{
 */

/*----------------------------------------------------------------------------
 *      Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "usb/device/printer/printer_driver.h"

#include "main_descriptors.h"

/*---------------------------------------------------------------------------
 *         Definitions
 *---------------------------------------------------------------------------*/
/** Address of the PRINTER bulk-out endpoint. */
#define PRINTER_Descriptors_DATAOUT0                   1

/*---------------------------------------------------------------------------
 *         Macros
 *---------------------------------------------------------------------------*/

/** Returns the minimum between two values. */
#define MIN(a, b)       ((a < b) ? a : b)

/*----------------------------------------------------------------------------
 *         Exported variables
 *----------------------------------------------------------------------------*/

/** Standard USB device descriptor for the composite device driver */
static const USBDeviceDescriptor deviceDescriptor = {

	sizeof(USBDeviceDescriptor),
	USBGenericDescriptor_DEVICE,
	USBDeviceDescriptor_USB2_00,
	0x00,/* Class Code - see interface descriptor */
	0x00,/* Subclass code - see interface descriptor */
	0x00,/* Protocol code - see interface descriptor */
	CHIP_USB_ENDPOINT_MAXPACKETSIZE(0),
	PRINTERDriverDescriptors_VENDORID,/* Vendor ID */
	PRINTERDriverDescriptors_PRODUCTID,/* Product ID */
	PRINTERDriverDescriptors_RELEASE,/* Device release number in BCD format */
	0x1, /* Manufacturer string index */
	0x2, /* Index of product string descriptor  */
	0x3, /* No string descriptor for serial number */
	1 /* Device has 1 possible configuration */
};

/** Device qualifier descriptor (to pass USB test). */
static const USBDeviceQualifierDescriptor qualifierDescriptor = {

	sizeof(USBDeviceQualifierDescriptor),
	USBGenericDescriptor_DEVICEQUALIFIER,
	USBDeviceDescriptor_USB2_00,
	0x00,/* */
	0x00,/* */
	0x00,/* */
	CHIP_USB_ENDPOINT_MAXPACKETSIZE(0),
	0, // Device has no other speed configuration.
	0x00
};

/** USB configuration descriptors for the composite device driver */
static const PRINTERDriverConfigurationDescriptors configurationDescriptorsFS =
{

	/* Standard configuration descriptor */
	{
		sizeof(USBConfigurationDescriptor),
		USBGenericDescriptor_CONFIGURATION,
		sizeof(PRINTERDriverConfigurationDescriptors),
		1, /* Number of interfaces in this configuration */
		1, /* This is configuration #1 */
		0, /* No string descriptor for this configuration */
		BOARD_USB_BMATTRIBUTES,
		USBConfigurationDescriptor_POWER(100)
	},

	/* interface standard descriptor */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		0, /* Interface Number */
		0x00, /* Alternate Setting Number */
		0x01, /* Number of endpoints in this interface */
		PRINTERDeviceDescriptor_CLASS, /* Class code */
		PRINTERDeviceDescriptor_SUBCLASS, /* Subclass code */
		PRINTERDeviceDescriptor_PROTOCOL, /* Protocol code */
		0x00, /* Interface string index */
	},
	/* Class-specific header functional descriptor */
	{
		/* Bulk Endpoint (OUT) Descriptor */
		sizeof(USBEndpointDescriptor), /* Size of this descriptor */
		USBGenericDescriptor_ENDPOINT, /* Endpoint Descriptor */
		USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_OUT, PRINTER_Descriptors_DATAOUT0), /* EndpointAddress */
		USBEndpointDescriptor_BULK, /* Attributes type of EP (BULK) */
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(PRINTER_Descriptors_DATAOUT0),/* Max packet size of this EP */
		USBEndpointDescriptor_MAXBULKSIZE_FS),
		0x00, /* Interval for full speed (in ms) */
	},
};

/** USB configuration descriptors for the composite device driver */
static const PRINTERDriverConfigurationDescriptors configurationDescriptorsHS =
{
	/* Standard configuration descriptor */
	{
		sizeof(USBConfigurationDescriptor),
		USBGenericDescriptor_CONFIGURATION,
		sizeof(PRINTERDriverConfigurationDescriptors),
		1, /* Number of interfaces in this configuration */
		1, /* This is configuration #1 */
		0, /* No string descriptor for this configuration */
		BOARD_USB_BMATTRIBUTES,
		USBConfigurationDescriptor_POWER(100)
	},

	/* interface standard descriptor */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		0, /* Interface Number */
		0x00, /* Alternate Setting Number */
		0x01, /* Number of endpoints in this interface */
		PRINTERDeviceDescriptor_CLASS, /* Class code */
		PRINTERDeviceDescriptor_SUBCLASS, /* Subclass code */
		PRINTERDeviceDescriptor_PROTOCOL, /* Protocol code */
		0x00, /* Interface string index */
	},
	/* Class-specific header functional descriptor */
	{
		/* Bulk Endpoint (OUT) Descriptor */
		sizeof(USBEndpointDescriptor), /* Size of this descriptor */
		USBGenericDescriptor_ENDPOINT, /* Endpoint Descriptor */
		USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_OUT, PRINTER_Descriptors_DATAOUT0), /* EndpointAddress */
		USBEndpointDescriptor_BULK, /* Attributes type of EP (BULK) */
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(PRINTER_Descriptors_DATAOUT0),/* Max packet size of this EP */
		USBEndpointDescriptor_MAXBULKSIZE_HS),
		0x00, /* Interval for full speed (in ms) */
	},
};

/** String descriptor with the supported languages. */
const unsigned char languageIdDescriptor[] = {

	USBStringDescriptor_LENGTH(1),
	USBGenericDescriptor_STRING,
	USBStringDescriptor_ENGLISH_US
};

/** Manufacturer name. */
const unsigned char manufacturerDescriptor[] = {

	USBStringDescriptor_LENGTH(5),
	USBGenericDescriptor_STRING,
	USBStringDescriptor_UNICODE('A'),
	USBStringDescriptor_UNICODE('T'),
	USBStringDescriptor_UNICODE('M'),
	USBStringDescriptor_UNICODE('E'),
	USBStringDescriptor_UNICODE('L')
};

/** Product name. */
const unsigned char productDescriptor[] = {

	USBStringDescriptor_LENGTH(25),
	USBGenericDescriptor_STRING,
	USBStringDescriptor_UNICODE('G'),
	USBStringDescriptor_UNICODE('e'),
	USBStringDescriptor_UNICODE('n'),
	USBStringDescriptor_UNICODE('e'),
	USBStringDescriptor_UNICODE('r'),
	USBStringDescriptor_UNICODE('i'),
	USBStringDescriptor_UNICODE('c'),
	USBStringDescriptor_UNICODE(' '),
	USBStringDescriptor_UNICODE('T'),
	USBStringDescriptor_UNICODE('e'),
	USBStringDescriptor_UNICODE('x'),
	USBStringDescriptor_UNICODE('t'),
	USBStringDescriptor_UNICODE(' '),
	USBStringDescriptor_UNICODE('P'),
	USBStringDescriptor_UNICODE('r'),
	USBStringDescriptor_UNICODE('i'),
	USBStringDescriptor_UNICODE('n'),
	USBStringDescriptor_UNICODE('t'),
	USBStringDescriptor_UNICODE('e'),
	USBStringDescriptor_UNICODE('r'),
	USBStringDescriptor_UNICODE(' '),
	USBStringDescriptor_UNICODE('D'),
	USBStringDescriptor_UNICODE('e'),
	USBStringDescriptor_UNICODE('m'),
	USBStringDescriptor_UNICODE('o')
};

/** Product serial number. */
const unsigned char serialNumberDescriptor[] = {

	USBStringDescriptor_LENGTH(4),
	USBGenericDescriptor_STRING,
	USBStringDescriptor_UNICODE('0'),
	USBStringDescriptor_UNICODE('1'),
	USBStringDescriptor_UNICODE('2'),
	USBStringDescriptor_UNICODE('3')
};

/** Array of pointers to string descriptors. */
static const unsigned char *stringDescriptors[] = {
	languageIdDescriptor,
	manufacturerDescriptor,
	productDescriptor,
	serialNumberDescriptor
};

/**  List of descriptors used by the device. */

const USBDDriverDescriptors printer_driver_descriptors =
{
	&deviceDescriptor,
	(const USBConfigurationDescriptor *) &configurationDescriptorsFS,
	&qualifierDescriptor,
	0,/* No full-speed other speed configuration descriptor */
	0,/* No high-speed device descriptor (Uses FS one) */
	(const USBConfigurationDescriptor *) &configurationDescriptorsHS,
	&qualifierDescriptor,
	0,/* No high-speed other speed configuration descriptor */
	stringDescriptors,
	4 /* Four string descriptors in list */
};

/**@}*/

