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
 * \addtogroup usbd_composite_cdcaud
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "board.h"
#include "usb/device/audio/audd_function.h"
#include "usb/device/cdc/cdcd_serial.h"
#include "usb/device/composite/cdc_audd_driver.h"

#include "main_descriptors.h"

/*---------------------------------------------------------------------------
 *         Macros
 *---------------------------------------------------------------------------*/

/** Returns the minimum between two values. */
#define MIN(a, b)       ((a < b) ? a : b)

/*------------------------------------------------------------------------------
 *         Exported variables
 *------------------------------------------------------------------------------*/

/** Device descriptor for a USB Audio Speakerphone driver. */
const USBDeviceDescriptor deviceDescriptor = {

	sizeof(USBDeviceDescriptor),
	USBGenericDescriptor_DEVICE,
	USBDeviceDescriptor_USB2_00,
	0xEF,/* MI */
	0x02,
	0x01,
	CHIP_USB_ENDPOINT_MAXPACKETSIZE(0),
	CDCAUDDDriverDescriptors_VENDORID,
	CDCAUDDDriverDescriptors_PRODUCTID,
	CDCAUDDDriverDescriptors_RELEASE,
	1, /* Manufacturer string descriptor index */
	2, /* Product string descriptor index */
	3, /* Index of serial number string descriptor */
	1  /* One possible configuration */
};

/** Device qualifier descriptor (Necessary to pass USB test). */
static const USBDeviceQualifierDescriptor qualifierDescriptor = {

	sizeof(USBDeviceQualifierDescriptor),
	USBGenericDescriptor_DEVICEQUALIFIER,
	USBDeviceDescriptor_USB2_00,
	0xEF,
	0x02,
	0x01,
	CHIP_USB_ENDPOINT_MAXPACKETSIZE(0),
	1, // Device has one possible configuration.
	0x00
};

/** FS Configuration descriptors for a USB Audio Speakerphone driver. */
const CdcAudspkdDriverConfigurationDescriptors fsConfigurationDescriptors = {

	/* Configuration descriptor */
	{
		sizeof(USBConfigurationDescriptor),
		USBGenericDescriptor_CONFIGURATION,
		sizeof(CdcAudspkdDriverConfigurationDescriptors),
		4, /* This configuration has 5 interfaces */
		1, /* This is configuration #1 */
		0, /* No string descriptor */
		BOARD_USB_BMATTRIBUTES,
		USBConfigurationDescriptor_POWER(100)
	},
	/* CDC */
	/* IAD for CDC/ACM port */
	{
		sizeof(USBInterfaceAssociationDescriptor),
		USBGenericDescriptor_INTERFACEASSOCIATION,
		CDCAUDDDriverDescriptors_CDC_INTERFACE,
		2,
		CDCCommunicationInterfaceDescriptor_CLASS,
		CDCCommunicationInterfaceDescriptor_ABSTRACTCONTROLMODEL,
		CDCCommunicationInterfaceDescriptor_NOPROTOCOL,
		0  /* No string descriptor for this interface*/
	},
	/* Communication class interface standard descriptor*/
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		CDCAUDDDriverDescriptors_CDC_INTERFACE, /* This is interface #0*/
		0, /* This is alternate setting #0 for this interface*/
		1, /* This interface uses 1 endpoint*/
		CDCCommunicationInterfaceDescriptor_CLASS,
		CDCCommunicationInterfaceDescriptor_ABSTRACTCONTROLMODEL,
		CDCCommunicationInterfaceDescriptor_NOPROTOCOL,
		0  /* No string descriptor for this interface*/
	},
	/* Class-specific header functional descriptor*/
	{
		sizeof(CDCHeaderDescriptor),
		CDCGenericDescriptor_INTERFACE,
		CDCGenericDescriptor_HEADER,
		CDCGenericDescriptor_CDC1_10
	},
	/* Class-specific call management functional descriptor*/
	{
		sizeof(CDCCallManagementDescriptor),
		CDCGenericDescriptor_INTERFACE,
		CDCGenericDescriptor_CALLMANAGEMENT,
		CDCCallManagementDescriptor_SELFCALLMANAGEMENT,
		CDCAUDDDriverDescriptors_CDC_INTERFACE + 1 /* No associated data interface*/
	},
	/* Class-specific abstract control management functional descriptor*/
	{
		sizeof(CDCAbstractControlManagementDescriptor),
		CDCGenericDescriptor_INTERFACE,
		CDCGenericDescriptor_ABSTRACTCONTROLMANAGEMENT,
		CDCAbstractControlManagementDescriptor_LINE
	},
	/* Class-specific union functional descriptor with one slave interface*/
	{
		sizeof(CDCUnionDescriptor),
		CDCGenericDescriptor_INTERFACE,
		CDCGenericDescriptor_UNION,
		CDCAUDDDriverDescriptors_CDC_INTERFACE, /* Number of master interface is #0*/
		CDCAUDDDriverDescriptors_CDC_INTERFACE + 1 /* First slave interface is #1*/
	},
	/* Notification endpoint standard descriptor*/
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_IN, CDCD_Descriptors_NOTIFICATION0),
		USBEndpointDescriptor_INTERRUPT,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(CDCD_Descriptors_NOTIFICATION0),
			CDCDSerialPort_INTERRUPT_MAXPACKETSIZE),
		CDCDSerialPort_INTERRUPT_INTERVAL_FS /* Endpoint is polled every 10ms*/
	},
	/* Data class interface standard descriptor*/
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		CDCAUDDDriverDescriptors_CDC_INTERFACE + 1, /* This is interface #1*/
		0, /* This is alternate setting #0 for this interface*/
		2, /* This interface uses 2 endpoints*/
		CDCDataInterfaceDescriptor_CLASS,
		CDCDataInterfaceDescriptor_SUBCLASS,
		CDCDataInterfaceDescriptor_NOPROTOCOL,
		0  /* No string descriptor for this interface*/
	},
	/* Bulk-OUT endpoint standard descriptor*/
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_OUT, CDCD_Descriptors_DATAOUT0),
		USBEndpointDescriptor_BULK,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(CDCD_Descriptors_DATAOUT0),
			USBEndpointDescriptor_MAXBULKSIZE_FS),
		0 /* Must be 0 for full-speed bulk endpoints*/
	},
	/* Bulk-IN endpoint descriptor*/
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_IN, CDCD_Descriptors_DATAIN0),
		USBEndpointDescriptor_BULK,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(CDCD_Descriptors_DATAIN0),
			USBEndpointDescriptor_MAXBULKSIZE_FS),
		0 /* Must be 0 for full-speed bulk endpoints*/
	},

	/* AUDIO */
	/* IAD for AUDIO function */
	{
		sizeof(USBInterfaceAssociationDescriptor),
		USBGenericDescriptor_INTERFACEASSOCIATION,
		CDCAUDDDriverDescriptors_AUD_INTERFACE,
		2, /* AS + Spk */
		AUDControlInterfaceDescriptor_CLASS,
		AUDControlInterfaceDescriptor_SUBCLASS,
		AUDControlInterfaceDescriptor_PROTOCOL,
		0  // No string descriptor for this interface
	},
	/* Audio control interface standard descriptor */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		CDCAUDDDriverDescriptors_AUD_INTERFACE,
		0, /* This is alternate setting #0 */
		0, /* This interface uses no endpoint */
		AUDControlInterfaceDescriptor_CLASS,
		AUDControlInterfaceDescriptor_SUBCLASS,
		AUDControlInterfaceDescriptor_PROTOCOL,
		0 /* No string descriptor */
	},
	/* Audio control interface descriptors */
	{
		/* Header descriptor */
		{
			{
				sizeof(AUDHeaderDescriptor1),
				AUDGenericDescriptor_INTERFACE,
				AUDGenericDescriptor_HEADER,
				AUDHeaderDescriptor_AUD1_00,
				sizeof(AUDDSpeakerAcDescriptors),
				1 /* One streaming interface */
			},
			CDCAUDDDriverDescriptors_AUD_INTERFACE + 1,
		},
		/* Input terminal descriptor ( speaker ) */
		{
			sizeof(AUDInputTerminalDescriptor),
			AUDGenericDescriptor_INTERFACE,
			AUDGenericDescriptor_INPUTTERMINAL,
			AUDDFunction_INPUTTERMINAL,
			AUDInputTerminalDescriptor_USBSTREAMING,
			AUDDFunction_OUTPUTTERMINAL,
			AUDDevice_NUMCHANNELS, /* L,R */
			AUDInputTerminalDescriptor_LEFTFRONT
			| AUDInputTerminalDescriptor_RIGHTFRONT,
			0, /* No string descriptor for channels */
			0 /* No string descriptor for input terminal */
		},
		/* Output terminal descriptor ( speaker ) */
		{
			sizeof(AUDOutputTerminalDescriptor),
			AUDGenericDescriptor_INTERFACE,
			AUDGenericDescriptor_OUTPUTTERMINAL,
			AUDDFunction_OUTPUTTERMINAL,
			AUDOutputTerminalDescriptor_SPEAKER,
			AUDDFunction_INPUTTERMINAL,
			AUDDFunction_FEATUREUNIT,
			0 /* No string descriptor */
		},
		/* Feature unit descriptor ( speaker ) */
		{
			{
				sizeof(AUDFeatureUnitDescriptor3),
				AUDGenericDescriptor_INTERFACE,
				AUDGenericDescriptor_FEATUREUNIT,
				AUDDFunction_FEATUREUNIT,
				AUDDFunction_INPUTTERMINAL,
				1, /* 1 byte per channel for controls */
			},
			{
				AUDFeatureUnitDescriptor_MUTE, /* Master channel controls */
				0, /* Right channel controls */
				0  /* Left channel controls */
			},
			0 /* No string descriptor */
		}
	},
	/* - AUIDO OUT */
	/* Audio streaming interface with 0 endpoints */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		CDCAUDDDriverDescriptors_AUD_INTERFACE + 1,
		0, /* This is alternate setting #0 */
		0, /* This interface uses no endpoints */
		AUDStreamingInterfaceDescriptor_CLASS,
		AUDStreamingInterfaceDescriptor_SUBCLASS,
		AUDStreamingInterfaceDescriptor_PROTOCOL,
		0 /* No string descriptor */
	},
	/* Audio streaming interface with data endpoint */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		CDCAUDDDriverDescriptors_AUD_INTERFACE + 1,
		1, /* This is alternate setting #1 */
		1, /* This interface uses 1 endpoint */
		AUDStreamingInterfaceDescriptor_CLASS,
		AUDStreamingInterfaceDescriptor_SUBCLASS,
		AUDStreamingInterfaceDescriptor_PROTOCOL,
		0 /* No string descriptor */
	},
	/* Audio streaming class-specific descriptor */
	{
		sizeof(AUDStreamingInterfaceDescriptor),
		AUDGenericDescriptor_INTERFACE,
		AUDStreamingInterfaceDescriptor_GENERAL,
		AUDDFunction_INPUTTERMINAL,
		0, /* No internal delay because of data path */
		AUDFormatTypeOneDescriptor_PCM
	},
	/* Format type I descriptor */
	{
		{
			sizeof(AUDFormatTypeOneDescriptor1),
			AUDGenericDescriptor_INTERFACE,
			AUDStreamingInterfaceDescriptor_FORMATTYPE,
			AUDFormatTypeOneDescriptor_FORMATTYPEONE,
			AUDDevice_NUMCHANNELS,
			AUDDevice_BYTESPERSAMPLE,
			AUDDevice_BYTESPERSAMPLE*8,
			1 /* One discrete frequency supported */
		},
		{
			AUDDevice_SAMPLERATE & 0xFF,
			(AUDDevice_SAMPLERATE >> 8) & 0xFF,
			(AUDDevice_SAMPLERATE >> 16) & 0xFF
		}
	},
	/* Audio streaming endpoint standard descriptor */
	{
		sizeof(AUDEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(
			USBEndpointDescriptor_OUT, AUDD_Descriptors_DATAOUT),
		USBEndpointDescriptor_ISOCHRONOUS,
		AUDDevice_BYTESPERFRAME,
		AUDDFunction_FS_INTERVAL, /* Polling interval = 1 ms */
		0, /* This is not a synchronization endpoint */
		0 /* No associated synchronization endpoint */
	},
	/* Audio streaming endpoint class-specific descriptor */
	{
		sizeof(AUDDataEndpointDescriptor),
		AUDGenericDescriptor_ENDPOINT,
		AUDDataEndpointDescriptor_SUBTYPE,
		0, /* No attributes */
		0, /* Endpoint is not synchronized */
		0 /* Endpoint is not synchronized */
	}
};

/** HS Configuration descriptors for a USB Audio Speakerphone driver. */
const CdcAudspkdDriverConfigurationDescriptors hsConfigurationDescriptors = {

	/* Configuration descriptor */
	{
		sizeof(USBConfigurationDescriptor),
		USBGenericDescriptor_CONFIGURATION,
		sizeof(CdcAudspkdDriverConfigurationDescriptors),
		4, /* This configuration has 5 interfaces */
		1, /* This is configuration #1 */
		0, /* No string descriptor */
		BOARD_USB_BMATTRIBUTES,
		USBConfigurationDescriptor_POWER(100)
	},
	/* CDC */
	/* IAD for CDC/ACM port */
	{
		sizeof(USBInterfaceAssociationDescriptor),
		USBGenericDescriptor_INTERFACEASSOCIATION,
		CDCAUDDDriverDescriptors_CDC_INTERFACE,
		2,
		CDCCommunicationInterfaceDescriptor_CLASS,
		CDCCommunicationInterfaceDescriptor_ABSTRACTCONTROLMODEL,
		CDCCommunicationInterfaceDescriptor_NOPROTOCOL,
		0  /* No string descriptor for this interface*/
	},
	/* Communication class interface standard descriptor*/
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		CDCAUDDDriverDescriptors_CDC_INTERFACE, /* This is interface #0*/
		0, /* This is alternate setting #0 for this interface*/
		1, /* This interface uses 1 endpoint*/
		CDCCommunicationInterfaceDescriptor_CLASS,
		CDCCommunicationInterfaceDescriptor_ABSTRACTCONTROLMODEL,
		CDCCommunicationInterfaceDescriptor_NOPROTOCOL,
		0  /* No string descriptor for this interface*/
	},
	/* Class-specific header functional descriptor*/
	{
		sizeof(CDCHeaderDescriptor),
		CDCGenericDescriptor_INTERFACE,
		CDCGenericDescriptor_HEADER,
		CDCGenericDescriptor_CDC1_10
	},
	/* Class-specific call management functional descriptor*/
	{
		sizeof(CDCCallManagementDescriptor),
		CDCGenericDescriptor_INTERFACE,
		CDCGenericDescriptor_CALLMANAGEMENT,
		CDCCallManagementDescriptor_SELFCALLMANAGEMENT,
		CDCAUDDDriverDescriptors_CDC_INTERFACE + 1 /* No associated data interface*/
	},
	/* Class-specific abstract control management functional descriptor*/
	{
		sizeof(CDCAbstractControlManagementDescriptor),
		CDCGenericDescriptor_INTERFACE,
		CDCGenericDescriptor_ABSTRACTCONTROLMANAGEMENT,
		CDCAbstractControlManagementDescriptor_LINE
	},
	/* Class-specific union functional descriptor with one slave interface*/
	{
		sizeof(CDCUnionDescriptor),
		CDCGenericDescriptor_INTERFACE,
		CDCGenericDescriptor_UNION,
		CDCAUDDDriverDescriptors_CDC_INTERFACE, /* Number of master interface is #0*/
		CDCAUDDDriverDescriptors_CDC_INTERFACE + 1 /* First slave interface is #1*/
	},
	/* Notification endpoint standard descriptor*/
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_IN, CDCD_Descriptors_NOTIFICATION0),
		USBEndpointDescriptor_INTERRUPT,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(CDCD_Descriptors_NOTIFICATION0),
			CDCDSerialPort_INTERRUPT_MAXPACKETSIZE),
		CDCDSerialPort_INTERRUPT_INTERVAL_FS /* Endpoint is polled every 10ms*/
	},
	/* Data class interface standard descriptor*/
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		CDCAUDDDriverDescriptors_CDC_INTERFACE + 1, /* This is interface #1*/
		0, /* This is alternate setting #0 for this interface*/
		2, /* This interface uses 2 endpoints*/
		CDCDataInterfaceDescriptor_CLASS,
		CDCDataInterfaceDescriptor_SUBCLASS,
		CDCDataInterfaceDescriptor_NOPROTOCOL,
		0  /* No string descriptor for this interface*/
	},
	/* Bulk-OUT endpoint standard descriptor*/
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_OUT, CDCD_Descriptors_DATAOUT0),
		USBEndpointDescriptor_BULK,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(CDCD_Descriptors_DATAOUT0),
			USBEndpointDescriptor_MAXBULKSIZE_HS),
		0 /* Must be 0 for full-speed bulk endpoints*/
	},
	/* Bulk-IN endpoint descriptor*/
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(USBEndpointDescriptor_IN, CDCD_Descriptors_DATAIN0),
		USBEndpointDescriptor_BULK,
		MIN(CHIP_USB_ENDPOINT_MAXPACKETSIZE(CDCD_Descriptors_DATAIN0),
			USBEndpointDescriptor_MAXBULKSIZE_HS),
		0 /* Must be 0 for full-speed bulk endpoints*/
	},

	/* AUDIO */
	/* IAD for AUDIO function */
	{
		sizeof(USBInterfaceAssociationDescriptor),
		USBGenericDescriptor_INTERFACEASSOCIATION,
		CDCAUDDDriverDescriptors_AUD_INTERFACE,
		2, /* AS + Spk */
		AUDControlInterfaceDescriptor_CLASS,
		AUDControlInterfaceDescriptor_SUBCLASS,
		AUDControlInterfaceDescriptor_PROTOCOL,
		0  // No string descriptor for this interface
	},
	/* Audio control interface standard descriptor */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		CDCAUDDDriverDescriptors_AUD_INTERFACE,
		0, /* This is alternate setting #0 */
		0, /* This interface uses no endpoint */
		AUDControlInterfaceDescriptor_CLASS,
		AUDControlInterfaceDescriptor_SUBCLASS,
		AUDControlInterfaceDescriptor_PROTOCOL,
		0 /* No string descriptor */
	},
	/* Audio control interface descriptors */
	{
		/* Header descriptor */
		{
			{
				sizeof(AUDHeaderDescriptor1),
				AUDGenericDescriptor_INTERFACE,
				AUDGenericDescriptor_HEADER,
				AUDHeaderDescriptor_AUD1_00,
				sizeof(AUDDSpeakerAcDescriptors),
				1 /* One streaming interface */
			},
			CDCAUDDDriverDescriptors_AUD_INTERFACE + 1,
		},
		/* Input terminal descriptor ( speaker ) */
		{
			sizeof(AUDInputTerminalDescriptor),
			AUDGenericDescriptor_INTERFACE,
			AUDGenericDescriptor_INPUTTERMINAL,
			AUDDFunction_INPUTTERMINAL,
			AUDInputTerminalDescriptor_USBSTREAMING,
			AUDDFunction_OUTPUTTERMINAL,
			AUDDevice_NUMCHANNELS, /* L,R */
			AUDInputTerminalDescriptor_LEFTFRONT
			| AUDInputTerminalDescriptor_RIGHTFRONT,
			0, /* No string descriptor for channels */
			0 /* No string descriptor for input terminal */
		},
		/* Output terminal descriptor ( speaker ) */
		{
			sizeof(AUDOutputTerminalDescriptor),
			AUDGenericDescriptor_INTERFACE,
			AUDGenericDescriptor_OUTPUTTERMINAL,
			AUDDFunction_OUTPUTTERMINAL,
			AUDOutputTerminalDescriptor_SPEAKER,
			AUDDFunction_INPUTTERMINAL,
			AUDDFunction_FEATUREUNIT,
			0 /* No string descriptor */
		},
		/* Feature unit descriptor ( speaker ) */
		{
			{
				sizeof(AUDFeatureUnitDescriptor3),
				AUDGenericDescriptor_INTERFACE,
				AUDGenericDescriptor_FEATUREUNIT,
				AUDDFunction_FEATUREUNIT,
				AUDDFunction_INPUTTERMINAL,
				1, /* 1 byte per channel for controls */
			},
			{
				AUDFeatureUnitDescriptor_MUTE, /* Master channel controls */
				0, /* Right channel controls */
				0  /* Left channel controls */
			},
			0 /* No string descriptor */
		}
	},
	/* - AUIDO OUT */
	/* Audio streaming interface with 0 endpoints */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		CDCAUDDDriverDescriptors_AUD_INTERFACE + 1,
		0, /* This is alternate setting #0 */
		0, /* This interface uses no endpoints */
		AUDStreamingInterfaceDescriptor_CLASS,
		AUDStreamingInterfaceDescriptor_SUBCLASS,
		AUDStreamingInterfaceDescriptor_PROTOCOL,
		0 /* No string descriptor */
	},
	/* Audio streaming interface with data endpoint */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		CDCAUDDDriverDescriptors_AUD_INTERFACE + 1,
		1, /* This is alternate setting #1 */
		1, /* This interface uses 1 endpoint */
		AUDStreamingInterfaceDescriptor_CLASS,
		AUDStreamingInterfaceDescriptor_SUBCLASS,
		AUDStreamingInterfaceDescriptor_PROTOCOL,
		0 /* No string descriptor */
	},
	/* Audio streaming class-specific descriptor */
	{
		sizeof(AUDStreamingInterfaceDescriptor),
		AUDGenericDescriptor_INTERFACE,
		AUDStreamingInterfaceDescriptor_GENERAL,
		AUDDFunction_INPUTTERMINAL,
		0, /* No internal delay because of data path */
		AUDFormatTypeOneDescriptor_PCM
	},
	/* Format type I descriptor */
	{
		{
			sizeof(AUDFormatTypeOneDescriptor1),
			AUDGenericDescriptor_INTERFACE,
			AUDStreamingInterfaceDescriptor_FORMATTYPE,
			AUDFormatTypeOneDescriptor_FORMATTYPEONE,
			AUDDevice_NUMCHANNELS,
			AUDDevice_BYTESPERSAMPLE,
			AUDDevice_BYTESPERSAMPLE*8,
			1 /* One discrete frequency supported */
		},
		{
			AUDDevice_SAMPLERATE & 0xFF,
			(AUDDevice_SAMPLERATE >> 8) & 0xFF,
			(AUDDevice_SAMPLERATE >> 16) & 0xFF
		}
	},
	/* Audio streaming endpoint standard descriptor */
	{
		sizeof(AUDEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		USBEndpointDescriptor_ADDRESS(
			USBEndpointDescriptor_OUT, AUDD_Descriptors_DATAOUT),
		USBEndpointDescriptor_ISOCHRONOUS,
		AUDDevice_BYTESPERFRAME,
		AUDDFunction_HS_INTERVAL, /* Polling interval = 1 ms */
		0, /* This is not a synchronization endpoint */
		0 /* No associated synchronization endpoint */
	},
	/* Audio streaming endpoint class-specific descriptor */
	{
		sizeof(AUDDataEndpointDescriptor),
		AUDGenericDescriptor_ENDPOINT,
		AUDDataEndpointDescriptor_SUBTYPE,
		0, /* No attributes */
		0, /* Endpoint is not synchronized */
		0 /* Endpoint is not synchronized */
	}
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
	USBStringDescriptor_UNICODE('t'),
	USBStringDescriptor_UNICODE('m'),
	USBStringDescriptor_UNICODE('e'),
	USBStringDescriptor_UNICODE('l')
};

/** Product name. */
const unsigned char productDescriptor[] = {

	USBStringDescriptor_LENGTH(15),
	USBGenericDescriptor_STRING,
	USBStringDescriptor_UNICODE('C'),
	USBStringDescriptor_UNICODE('D'),
	USBStringDescriptor_UNICODE('C'),
	USBStringDescriptor_UNICODE(' '),
	USBStringDescriptor_UNICODE('C'),
	USBStringDescriptor_UNICODE('O'),
	USBStringDescriptor_UNICODE('M'),
	USBStringDescriptor_UNICODE('&'),
	USBStringDescriptor_UNICODE('S'),
	USBStringDescriptor_UNICODE('p'),
	USBStringDescriptor_UNICODE('e'),
	USBStringDescriptor_UNICODE('a'),
	USBStringDescriptor_UNICODE('k'),
	USBStringDescriptor_UNICODE('e'),
	USBStringDescriptor_UNICODE('r')
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

/** Array of pointers to the four string descriptors. */
const unsigned char *stringDescriptors[] = {

	languageIdDescriptor,
	manufacturerDescriptor,
	productDescriptor,
	serialNumberDescriptor,
};

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

/** List of descriptors required by an USB Audio Speakerphoneer device driver. */
const USBDDriverDescriptors cdc_audd_driver_descriptors = {

	&deviceDescriptor,
	(const USBConfigurationDescriptor *) &fsConfigurationDescriptors,
	&qualifierDescriptor,
	0,
	0,
	(const USBConfigurationDescriptor *) &hsConfigurationDescriptors,
	&qualifierDescriptor,
	0,
	stringDescriptors, 4 /* Number of string descriptors */
};

/**@}*/
