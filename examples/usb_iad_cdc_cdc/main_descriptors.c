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
/** \addtogroup usbd_composite_cdccdc
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "board.h"
#include "usb/device/composite/dual_cdcd_driver.h"

/*------------------------------------------------------------------------------
 *         Definitions
 *------------------------------------------------------------------------------*/

/** Address of the CDC0 interrupt-in endpoint. */
#define CDCD_Descriptors_NOTIFICATION0              3
/** Address of the CDC0 bulk-in endpoint. */
#define CDCD_Descriptors_DATAIN0                    2
/** Address of the CDC0 bulk-out endpoint. */
#define CDCD_Descriptors_DATAOUT0                   1

/** Address of the CDC1 interrupt-in endpoint. */
#define CDCD_Descriptors_NOTIFICATION1              6
/** Address of the CDC1 bulk-in endpoint. */
#define CDCD_Descriptors_DATAIN1                    5
/** Address of the CDC1 bulk-out endpoint. */
#define CDCD_Descriptors_DATAOUT1                   4


/** Device product ID. */
#define DUALCDCDDriverDescriptors_PRODUCTID       0x6133

/** Device vendor ID (Atmel). */
#define DUALCDCDDriverDescriptors_VENDORID        0x03EB

/** Device release number. */
#define DUALCDCDDriverDescriptors_RELEASE         0x0003

/*---------------------------------------------------------------------------
 *         Macros
 *---------------------------------------------------------------------------*/

/** Returns the minimum between two values. */
#define MIN(a, b)       ((a < b) ? a : b)

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

/** Standard USB device descriptor for the composite device driver */
static const USBDeviceDescriptor deviceDescriptor = {

	sizeof(USBDeviceDescriptor),
	USBGenericDescriptor_DEVICE,
	USBDeviceDescriptor_USB2_00,
	0xEF,/* MI */
	0x02,
	0x01,
	CHIP_USB_ENDPOINT_MAXPACKETSIZE(0),
	DUALCDCDDriverDescriptors_VENDORID,
	DUALCDCDDriverDescriptors_PRODUCTID,
	DUALCDCDDriverDescriptors_RELEASE,
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
	CDCDeviceDescriptor_CLASS,
	CDCDeviceDescriptor_SUBCLASS,
	CDCDeviceDescriptor_PROTOCOL,
	CHIP_USB_ENDPOINT_MAXPACKETSIZE(0),
	0, // Device has no other speed configuration.
	0x00
};

/** USB configuration descriptors for the composite device driver */
static const DualCdcDriverConfigurationDescriptors configurationDescriptorsFS =
{

	/* Standard configuration descriptor */
	{
		sizeof(USBConfigurationDescriptor),
		USBGenericDescriptor_CONFIGURATION,
		sizeof(DualCdcDriverConfigurationDescriptors),
		DUALCDCDDriverDescriptors_NUMINTERFACE,
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
		DUALCDCDDriverDescriptors_INTERFACENUM0,
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
		DUALCDCDDriverDescriptors_INTERFACENUM0, /* This is interface #0 */
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
		DUALCDCDDriverDescriptors_INTERFACENUM0 + 1 /* No associated data interface */
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
		DUALCDCDDriverDescriptors_INTERFACENUM0, /* Number of master interface is #0 */
		DUALCDCDDriverDescriptors_INTERFACENUM0 + 1 /* First slave interface is #1 */
	},
	/* Notification endpoint standard descriptor */
	{
		sizeof(USBEndpointDescriptor), 
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_IN,
										CDCD_Descriptors_NOTIFICATION0),
		USBEndpointDescriptor_INTERRUPT,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(CDCD_Descriptors_NOTIFICATION0),
			USBEndpointDescriptor_MAXINTERRUPTSIZE_FS),
		CDCDSerialPort_INTERRUPT_INTERVAL_FS
	},
	/* Data class interface standard descriptor */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		DUALCDCDDriverDescriptors_INTERFACENUM0 + 1, /* This is interface #1 */
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

	/* CDC 1 */
	/* IAD for CDC/ACM port 1 */
	{
		sizeof(USBInterfaceAssociationDescriptor),
		USBGenericDescriptor_INTERFACEASSOCIATION,
		DUALCDCDDriverDescriptors_INTERFACENUM1,
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
		DUALCDCDDriverDescriptors_INTERFACENUM1, /* This is interface #2 */
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
		DUALCDCDDriverDescriptors_INTERFACENUM1 + 1 /* No associated data interface */
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
		DUALCDCDDriverDescriptors_INTERFACENUM1, /* Number of master interface is #2 */
		DUALCDCDDriverDescriptors_INTERFACENUM1+1 /* First slave interface is #3 */
	},
	/* Notification endpoint standard descriptor */
	{
		sizeof(USBEndpointDescriptor), 
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_IN,
											CDCD_Descriptors_NOTIFICATION1),
		USBEndpointDescriptor_INTERRUPT,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(CDCD_Descriptors_NOTIFICATION1),
			USBEndpointDescriptor_MAXINTERRUPTSIZE_FS),
		CDCDSerialPort_INTERRUPT_INTERVAL_FS
	},
	/* Data class interface standard descriptor */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		DUALCDCDDriverDescriptors_INTERFACENUM1 + 1, /* This is interface #3 */
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
										CDCD_Descriptors_DATAOUT1),
		USBEndpointDescriptor_BULK,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(CDCD_Descriptors_DATAOUT1),
			USBEndpointDescriptor_MAXBULKSIZE_FS),
		0 /* Must be 0 for full-speed bulk endpoints */
	},
	/* Bulk-IN endpoint descriptor */
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_IN,
										CDCD_Descriptors_DATAIN1),
		USBEndpointDescriptor_BULK,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(CDCD_Descriptors_DATAIN1),
			USBEndpointDescriptor_MAXBULKSIZE_FS),
		0 /* Must be 0 for full-speed bulk endpoints */
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

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

/** List of descriptors required by an USB audio speaker device driver. */
const USBDDriverDescriptors dual_cdcd_driver_descriptors = {

	&deviceDescriptor,
	(const USBConfigurationDescriptor *) &configurationDescriptorsFS,
	&qualifierDescriptor,
	0, /* No full-speed other speed configuration */
	0, /* No high-speed device descriptor (uses FS one) */
	0, /* No high-speed configuration descriptor (uses FS one) */
	&qualifierDescriptor,
	0, /* No high-speed other speed configuration descriptor */
	stringDescriptors,
	4 /*  Number of string descriptors */
};
/**@}*/

