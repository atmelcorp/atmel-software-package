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

/** \file
 * \addtogroup usbd_msd
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "usb/common/msd/msd_descriptors.h"
#include "usb/device/msd/msd_driver.h"

/*------------------------------------------------------------------------------
 *         Internal definitions
 *----------------------------------------------------------------------------*/



/** \addtogroup usbd_msd_device_descriptor_ids MSD Device Descriptor IDs
 *      @{
 * \section IDs
 * - MSDDriverDescriptors_VENDORID
 * - MSDDriverDescriptors_PRODUCTID
 * - MSDDriverDescriptors_RELEASE
 */

/** Vendor ID for the Mass Storage device driver. */
#define MSDDriverDescriptors_VENDORID       0x03EB
/** Product ID for the Mass Storage device driver. */
#define MSDDriverDescriptors_PRODUCTID      0x6129
/** Device release number for the Mass Storage device driver. */
#define MSDDriverDescriptors_RELEASE        0x0100

/** \addtogroup usbd_msdd_config USB MassStorage Configure
 *      @{
 * This page lists the defines used by the Mass Storage driver.
 *
 * \section msd_ep_addr Endpoint Addresses
 * - \ref MSDDriverDescriptors_BULKOUT
 * - \ref MSDDriverDescriptors_BULKIN
 */
/** Address of the Mass Storage bulk-out endpoint.*/
#define MSDDriverDescriptors_BULKOUT                2
/** Address of the Mass Storage bulk-in endpoint.*/
#define MSDDriverDescriptors_BULKIN                 3
/**      @}*/

/*---------------------------------------------------------------------------- */

/**      @}*/

/*------------------------------------------------------------------------------
 *         Macros
 *----------------------------------------------------------------------------*/

/** Returns the minimum between two values. */
#define MIN(a, b)       ((a < b) ? a : b)

/*------------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

/** Mass storage driver device descriptor. */
static const USBDeviceDescriptor deviceDescriptor = {

	sizeof(USBDeviceDescriptor),
	USBGenericDescriptor_DEVICE,
	USBDeviceDescriptor_USB2_00,
	MSDeviceDescriptor_CLASS,
	MSDeviceDescriptor_SUBCLASS,
	MSDeviceDescriptor_PROTOCOL,
	CHIP_USB_ENDPOINT_MAXPACKETSIZE(0),
	MSDDriverDescriptors_VENDORID,
	MSDDriverDescriptors_PRODUCTID,
	MSDDriverDescriptors_RELEASE,
	1, /* Manufacturer string descriptor index. */
	2, /* Product string descriptor index. */
	3, /* Serial number string descriptor index. */
	1  /* Device has one possible configuration. */
};

/** Device qualifier descriptor (Necessary to pass USB test). */
static const USBDeviceQualifierDescriptor qualifierDescriptor = {

	sizeof(USBDeviceQualifierDescriptor),
	USBGenericDescriptor_DEVICEQUALIFIER,
	USBDeviceDescriptor_USB2_00,
	MSDeviceDescriptor_CLASS,
	MSDeviceDescriptor_SUBCLASS,
	MSDeviceDescriptor_PROTOCOL,
	CHIP_USB_ENDPOINT_MAXPACKETSIZE(0),
	1, // Device has one possible configuration.
	0x00
};

/** Full-speed configuration descriptor. */
static const MSDConfigurationDescriptors configurationDescriptorsFS = {

	/* Standard configuration descriptor. */
	{
		sizeof(USBConfigurationDescriptor),
		USBGenericDescriptor_CONFIGURATION,
		sizeof(MSDConfigurationDescriptors),
		1, /* Configuration has one interface. */
		1, /* This is configuration #1. */
		0, /* No string descriptor for configuration. */
		BOARD_USB_BMATTRIBUTES,
		USBConfigurationDescriptor_POWER(100)
	},
	/* Mass Storage interface descriptor. */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		0, /* This is interface #0. */
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
			MSDDriverDescriptors_BULKOUT),
		USBEndpointDescriptor_BULK,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(MSDDriverDescriptors_BULKOUT),
			USBEndpointDescriptor_MAXBULKSIZE_FS),
		0 /* Must be 0 for full-speed Bulk endpoints. */
	},
	/* Bulk-IN endpoint descriptor */
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(
			USBEndpointDescriptor_IN,
			MSDDriverDescriptors_BULKIN),
		USBEndpointDescriptor_BULK,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(MSDDriverDescriptors_BULKIN),
			USBEndpointDescriptor_MAXBULKSIZE_FS),
		0 /* Must be 0 for full-speed Bulk endpoints. */

	}
};

/** Full-speed other speed configuration descriptor. */
static const MSDConfigurationDescriptors otherSpeedDescriptorsFS = {

	/* Standard configuration descriptor. */
	{
		sizeof(USBConfigurationDescriptor),
		USBGenericDescriptor_OTHERSPEEDCONFIGURATION,
		sizeof(MSDConfigurationDescriptors),
		1, /* Configuration has one interface. */
		1, /* This is configuration #1. */
		0, /* No string descriptor for configuration. */
		BOARD_USB_BMATTRIBUTES,
		USBConfigurationDescriptor_POWER(100)
	},
	/* Mass Storage interface descriptor. */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		0, /* This is interface #0. */
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
			MSDDriverDescriptors_BULKOUT),
		USBEndpointDescriptor_BULK,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(MSDDriverDescriptors_BULKOUT),
			USBEndpointDescriptor_MAXBULKSIZE_HS),
		0 /* No string descriptor for endpoint. */
	},
	/* Bulk-IN endpoint descriptor */
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(
			USBEndpointDescriptor_IN,
			MSDDriverDescriptors_BULKIN),
		USBEndpointDescriptor_BULK,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(MSDDriverDescriptors_BULKIN),
			USBEndpointDescriptor_MAXBULKSIZE_HS),
		0 /* No string descriptor for endpoint. */
	}
};

/** High-speed configuration descriptor. */
static const MSDConfigurationDescriptors configurationDescriptorsHS = {

	/* Standard configuration descriptor. */
	{
		sizeof(USBConfigurationDescriptor),
		USBGenericDescriptor_CONFIGURATION,
		sizeof(MSDConfigurationDescriptors),
		1, /* Configuration has one interface. */
		1, /* This is configuration #1. */
		0, /* No string descriptor for configuration. */
		BOARD_USB_BMATTRIBUTES,
		USBConfigurationDescriptor_POWER(100)
	},
	/* Mass Storage interface descriptor. */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		0, /* This is interface #0. */
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
			MSDDriverDescriptors_BULKOUT),
		USBEndpointDescriptor_BULK,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(MSDDriverDescriptors_BULKOUT),
			USBEndpointDescriptor_MAXBULKSIZE_HS),
		0 /* No string descriptor for endpoint. */
	},
	/* Bulk-IN endpoint descriptor */
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(
			USBEndpointDescriptor_IN,
			MSDDriverDescriptors_BULKIN),
		USBEndpointDescriptor_BULK,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(MSDDriverDescriptors_BULKIN),
			USBEndpointDescriptor_MAXBULKSIZE_HS),
		0 /* No string descriptor for endpoint. */
	}
};

/** High-speed other speed configuration descriptor. */
static const MSDConfigurationDescriptors otherSpeedDescriptorsHS = {

	/* Standard configuration descriptor. */
	{
		sizeof(USBConfigurationDescriptor),
		USBGenericDescriptor_OTHERSPEEDCONFIGURATION,
		sizeof(MSDConfigurationDescriptors),
		1, /* Configuration has one interface. */
		1, /* This is configuration #1. */
		0, /* No string descriptor for configuration. */
		BOARD_USB_BMATTRIBUTES,
		USBConfigurationDescriptor_POWER(100)
	},
	/* Mass Storage interface descriptor. */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		0, /* This is interface #0. */
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
			MSDDriverDescriptors_BULKOUT),
		USBEndpointDescriptor_BULK,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(MSDDriverDescriptors_BULKOUT),
			USBEndpointDescriptor_MAXBULKSIZE_FS),
		0 /* No string descriptor for endpoint. */
	},
	/* Bulk-IN endpoint descriptor */
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(
			USBEndpointDescriptor_IN,
			MSDDriverDescriptors_BULKIN),
		USBEndpointDescriptor_BULK,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(MSDDriverDescriptors_BULKIN),
			USBEndpointDescriptor_MAXBULKSIZE_FS),
		0 /* No string descriptor for endpoint. */
	}
};

/** Language ID string descriptor. */
static const unsigned char languageIdDescriptor[] = {

	USBStringDescriptor_LENGTH(1),
	USBGenericDescriptor_STRING,
	USBStringDescriptor_ENGLISH_US
};

/** Manufacturer string descriptor. */
static const unsigned char manufacturerDescriptor[] = {

	USBStringDescriptor_LENGTH(5),
	USBGenericDescriptor_STRING,
	USBStringDescriptor_UNICODE('A'),
	USBStringDescriptor_UNICODE('T'),
	USBStringDescriptor_UNICODE('M'),
	USBStringDescriptor_UNICODE('E'),
	USBStringDescriptor_UNICODE('L')
};

/** Product string descriptor. */
static const unsigned char productDescriptor[] = {

	USBStringDescriptor_LENGTH(14),
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
	USBStringDescriptor_UNICODE('M'),
	USBStringDescriptor_UNICODE('S'),
	USBStringDescriptor_UNICODE('D')
};

/** Serial number string descriptor. The serial number must be at least 12 */
/** characters long and made up of only letters & numbers to be compliant with */
/** the MSD specification. */
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

/** List of all string descriptors used. */
static const unsigned char *stringDescriptors[] = {

	languageIdDescriptor,
	manufacturerDescriptor,
	productDescriptor,
	serialNumberDescriptor
};

/*--------------------------------------------------------------------------- */
/*         Global variables */
/*--------------------------------------------------------------------------- */


/** List of the standard descriptors used by the Mass Storage driver. */
const USBDDriverDescriptors msd_driver_descriptors = {

	&deviceDescriptor,
	(USBConfigurationDescriptor *) &configurationDescriptorsFS,
	&qualifierDescriptor,
	(USBConfigurationDescriptor *) &otherSpeedDescriptorsFS,
	0, /* No high-speed device descriptor (uses FS one) */
	(USBConfigurationDescriptor *) &configurationDescriptorsHS,
	&qualifierDescriptor,
	(USBConfigurationDescriptor *) &otherSpeedDescriptorsHS,
	stringDescriptors,
	4 /* Four string descriptors in array */
};

/**@}*/
