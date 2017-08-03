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
/** \file */
/** \addtogroup usbd_composite_cdcmsd
 *@{
 */
/*------------------------------------------------------------------------------
 *      Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "usb/device/composite/cdc_msd_driver.h"
#include "usb/device/cdc/cdcd_serial.h"
#include "usb/device/msd/msd_function.h"

/*-----------------------------------------------------------------------------
 *         Definitions
 *---------------------------------------------------------------------------*/

/** Address of the CDC interrupt-in endpoint. */
#define CDCD_Descriptors_NOTIFICATION0              3
/** Address of the CDC bulk-in endpoint. */
#define CDCD_Descriptors_DATAIN0                    2
/** Address of the CDC bulk-out endpoint. */
#define CDCD_Descriptors_DATAOUT0                   1
/** Address of the Mass Storage bulk-out endpoint. */
#define MSDD_Descriptors_BULKOUT                    4
/** Address of the Mass Storage bulk-in endpoint. */
#define MSDD_Descriptors_BULKIN                     5

/** Device product ID. */
#define CDCMSDDDriverDescriptors_PRODUCTID       0x6132
/** Device vendor ID (Atmel). */
#define CDCMSDDDriverDescriptors_VENDORID        0x03EB
/** Device release number. */
#define CDCMSDDDriverDescriptors_RELEASE         0x0100

/*-----------------------------------------------------------------------------
 *         Macros
 *---------------------------------------------------------------------------*/

/** Returns the minimum between two values. */
#define MIN(a, b)       ((a < b) ? a : b)

/*------------------------------------------------------------------------------
 *         Internal variables
 *----------------------------------------------------------------------------*/

/** Standard USB device descriptor for the CDCMSD device driver */
static const USBDeviceDescriptor deviceDescriptor = {

	sizeof(USBDeviceDescriptor),
	USBGenericDescriptor_DEVICE,
	USBDeviceDescriptor_USB2_00,
	0xEF, /* MI */
	0x02,
	0x01,
	CHIP_USB_ENDPOINT_MAXPACKETSIZE(0),
	CDCMSDDDriverDescriptors_VENDORID,
	CDCMSDDDriverDescriptors_PRODUCTID,
	CDCMSDDDriverDescriptors_RELEASE,
	0, /* No string descriptor for manufacturer */
	1, /* Index of product string descriptor is #1 */
	3, /* No string descriptor for serial number */
	1  /* Device has 1 possible configuration */
};

/** Device qualifier descriptor (to pass USB test). */
static const USBDeviceQualifierDescriptor qualifierDescriptor = {

	sizeof(USBDeviceQualifierDescriptor),
	USBGenericDescriptor_DEVICEQUALIFIER,
	USBDeviceDescriptor_USB2_00,
	CDCDeviceDescriptor_CLASS,
	CDCDeviceDescriptor_SUBCLASS,
	CDCDeviceDescriptor_PROTOCOL,
	CHIP_USB_ENDPOINT_MAXPACKETSIZE(0),
	0, // Device has no other speed configuration.
	0x00
};

/** USB configuration descriptors for the CDCMSD device driver */
static const CDCMSDDriverConfigurationDescriptors configurationDescriptorsFS = {

	/* Standard configuration descriptor */
	{
		sizeof(USBConfigurationDescriptor),
		USBGenericDescriptor_CONFIGURATION,
		sizeof(CDCMSDDriverConfigurationDescriptors),
		CDCMSDDriverDescriptors_NUMINTERFACE,
		1, /* This is configuration #1 */
		0, /* No string descriptor for this configuration */
		BOARD_USB_BMATTRIBUTES,
		USBConfigurationDescriptor_POWER(100)
	},

	/* CDC */
	/* IAD for CDC/ACM port */
	{
		sizeof(USBInterfaceAssociationDescriptor),
		USBGenericDescriptor_INTERFACEASSOCIATION,
		CDCMSDDriverDescriptors_CDC_INTERFACE,
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
		CDCMSDDriverDescriptors_CDC_INTERFACE, /* This is interface #0 */
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
		CDCMSDDriverDescriptors_CDC_INTERFACE + 1 /* No associated data interface */
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
		CDCMSDDriverDescriptors_CDC_INTERFACE, /* Number of master interface is #0 */
		CDCMSDDriverDescriptors_CDC_INTERFACE + 1 /* First slave interface is #1 */
	},
	/* Notification endpoint standard descriptor */
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_IN,
		CDCD_Descriptors_NOTIFICATION0),
		USBEndpointDescriptor_INTERRUPT,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(CDCD_Descriptors_NOTIFICATION0),
		CDCDSerialPort_INTERRUPT_MAXPACKETSIZE),
		CDCDSerialPort_INTERRUPT_INTERVAL_FS
	},
	/* Data class interface standard descriptor */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		CDCMSDDriverDescriptors_CDC_INTERFACE + 1, /* This is interface #1 */
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
		USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_OUT,
		CDCD_Descriptors_DATAOUT0),
		USBEndpointDescriptor_BULK,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(CDCD_Descriptors_DATAOUT0),
		USBEndpointDescriptor_MAXBULKSIZE_HS),
		0 /* Must be 0 for full-speed bulk endpoints */
	},
	/* Bulk-IN endpoint descriptor */
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_IN,
		CDCD_Descriptors_DATAIN0),
		USBEndpointDescriptor_BULK,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(CDCD_Descriptors_DATAIN0),
		USBEndpointDescriptor_MAXBULKSIZE_HS),
		0 /* Must be 0 for full-speed bulk endpoints */
	},

	/* Mass Storage interface descriptor. */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		CDCMSDDriverDescriptors_MSD_INTERFACE,
		0, /* This is alternate setting #0. */
		2, /* Interface uses two endpoints. */
		MSInterfaceDescriptor_CLASS,
		MSInterfaceDescriptor_SCSI,
		MSInterfaceDescriptor_BULKONLY,
		0 /* No string descriptor for interface. */
	},
	/* Bulk-OUT endpoint descriptor */
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(
			USBEndpointDescriptor_OUT,
			MSDD_Descriptors_BULKOUT),
		USBEndpointDescriptor_BULK,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(MSDD_Descriptors_BULKOUT),
		USBEndpointDescriptor_MAXBULKSIZE_FS),
		0 /* No string descriptor for endpoint. */
	},
	/* Bulk-IN endpoint descriptor */
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(
			USBEndpointDescriptor_IN,
			MSDD_Descriptors_BULKIN),
		USBEndpointDescriptor_BULK,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(MSDD_Descriptors_BULKIN),
		USBEndpointDescriptor_MAXBULKSIZE_FS),
		0 /* No string descriptor for endpoint. */
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
	USBStringDescriptor_UNICODE('B')
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
const USBDDriverDescriptors cdc_msdd_driver_descriptors = {

	&deviceDescriptor,
	(const USBConfigurationDescriptor *) &configurationDescriptorsFS,
	&qualifierDescriptor,
	0, /* No full-speed other speed configuration */
	0, /* No high-speed device descriptor (uses FS one) */
	0, /* No high-speed configuration descriptor (uses FS one) */
	&qualifierDescriptor,
	0, /* No high-speed other speed configuration descriptor */
	stringDescriptors,
	4 /* Number of string descriptors */
};
/**@}*/

