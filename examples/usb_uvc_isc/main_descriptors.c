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
#include "usb/common/usb_descriptors.h"
#include "usb/common/uvc/uvc_descriptors.h"
#include "usb/device/usbd_driver.h"

/* ------------------- USB Video ----------------------- */
/** USB Device descriptor. */

const USBDeviceDescriptor usbDeviceDescriptor =
{
	sizeof(USBDeviceDescriptor),
	USBGenericDescriptor_DEVICE,
	USBDeviceDescriptor_USB2_00,
	VIDDeviceDescriptor_CLASS,
	VIDDeviceDescriptor_SUBCLASS,
	VIDDeviceDescriptor_PROTOCOL,
	CHIP_USB_ENDPOINT_MAXPACKETSIZE(0),
	0x03EB, // Atmel vendor ID
    0x6136, // Product ID
    0x0001, // Product release 0.01
	0, // No manufacturer string descriptor
	0, // No product string descriptor
	0, // No serial number string descriptor
	1 // One possible configuration
};

/** Device qualifier descriptor (to pass USB test). */

static const USBDeviceQualifierDescriptor qualifierDescriptor = {

	sizeof(USBDeviceQualifierDescriptor),
	USBGenericDescriptor_DEVICEQUALIFIER,
	USBDeviceDescriptor_USB2_00,
	VIDDeviceDescriptor_CLASS,
	VIDDeviceDescriptor_SUBCLASS,
	VIDDeviceDescriptor_PROTOCOL,
	CHIP_USB_ENDPOINT_MAXPACKETSIZE(0),
    1, // Device has one possible configuration.
	0x00
};

/**  Configuration descriptors. */

const struct UsbVideoCamConfigurationDescriptors configurationDescriptorsFS =
{
	/* Configuration descriptor */
	{
		sizeof(USBConfigurationDescriptor),
		USBGenericDescriptor_CONFIGURATION,
		sizeof(struct UsbVideoCamConfigurationDescriptors),
		2, /* 2 interface in this configuration */
		1, /* This is configuration #1 */
		0, /* No string descriptor for this configuration */
		BOARD_USB_BMATTRIBUTES,
		USBConfigurationDescriptor_POWER(100)
	},
	/* IAD */
	{
		sizeof(USBInterfaceAssociationDescriptor),
		USBGenericDescriptor_INTERFACEASSOCIATION,
		VIDCAMD_ControlInterfaceNum, /* Start interface is #0 */
		2, /* 2 interface is associated */
		VIDIADDescriptor_CLASS,
		VIDIADDescriptor_SUBCLASS,
		VIDIADDescriptor_PROTOCOL,
		0
	},
	/* VC Interface descriptor */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		VIDCAMD_ControlInterfaceNum, /* This is interface #0 */
		0, /* This is setting #0 for interface */
		0,
		VIDControlInterfaceDescriptor_CLASS,    /* CC_VIDEO */
		VIDControlInterfaceDescriptor_SUBCLASS, /* SC_VIDEOCONTROL */
		VIDControlInterfaceDescriptor_PROTOCOL, /* PC_PROTOCOL_UNDEFINED */
		0, /* No string descriptor */
	},
	/* VC Class defined descriptors */
	{
		/* VC Header */
		{
			sizeof(UsbVideoControlInterfaceHeader1),
			VIDGenericDescriptor_INTERFACE, /* CS_INTERFACE */
			VIDGenericDescriptor_HEADER,    /* VC_HEADER */
			VIDHeaderDescriptor_VID1_00,
			sizeof(UsbVideoControlInterfaceDescriptor),
			176000000,
			1, /* 1 VideoStreaming interface */
			VIDCAMD_StreamInterfaceNum, /* VideoStreaming interface 1: interface #1 */
		},
		/* VC Camera Terminal */
		{
			sizeof(USBVideoCameraTerminalDescriptor),
			VIDGenericDescriptor_INTERFACE, /* CS_INTERFACE */
			VIDGenericDescriptor_INPUTTERMINAL, /* VC_INPUT_TERMINAL */
			1, /* Terminal ID: #1 */
			VIDInputTerminalDescriptor_CAMERA, /* ITT_CAMERA */
			0, /* Assoc: None */
			0, /* No string */
			0, /* Optical Zoom not supported */
			0, /* Optical Zoom not supported */
			0, /* Optical Zoom not supported */
			3, /* 3 bytes for bmControls */
			{0, 0, 0}
		},
		/* VC Output Terminal */
		{
			sizeof(USBVideoOutputTerminalDescriptor),
			VIDGenericDescriptor_INTERFACE, /* CS_INTERFACE */
			VIDGenericDescriptor_OUTPUTTERMINAL, /* VC_OUTPUT_TERMINAL */
			2, /* Terminal ID: #2 */
			VIDTerminalDescriptor_STREAMING, /* Streaming terminal */
			0, /* Assoc: None */
			1, /* Source: Terminal is connected to #1 */
			0  /* No string */
		}
	},
	/* VS Interface descriptor */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		VIDCAMD_StreamInterfaceNum, /* interface #1 */
		0, /* alternate 0 */
		0, /* no endpoint */
		VIDStreamingInterfaceDescriptor_CLASS,
		VIDStreamingInterfaceDescriptor_SUBCLASS,
		VIDStreamingInterfaceDescriptor_PROTOCOL,
		0  /* No string */
	},
	/* VS Class defined descriptors */
	{
		/* VS Input Header */
		{
			sizeof(UsbVideoInputHeaderDescriptor1),
			VIDGenericDescriptor_INTERFACE, /* CS_INTERFACE */
			VIDStreamingInterfaceDescriptor_INPUTHEADER, /* VS_INPUT_HEADER */
			1, /* Only 1 payload format */
			sizeof(UsbVideoStreamingInterfaceDescriptor),
			0x80 | VIDCAMD_IsoInEndpointNum, /* Endpoint address is 0x82 */
			0x00, /* Dynamic Format Change not supported */
			2, /* Terminal Link to #2 */
			0, /* Still Capture not supported */
			0, /* Trigger not supported */
			0, /* No trigger usage */
			1, /* 1 bmaControls */
			0  /* No bmaControls */
		},
		/* VS Format Uncompressed */
		{
			/* Payload uncompressed format */
			{
				sizeof(USBVideoUncompressedFormatDescriptor),
				VIDGenericDescriptor_INTERFACE, /* CS_INTERFACE */
				VIDStreamingInterfaceDescriptor_FMT_UNCOMPRESSED,
				/* VS_FORMAT_UNCOMPRESSED */
				1, /* Format index #1 */
				VIDCAMD_NumFrameTypes, /* 3 frame types */
				guidYUY2, /* guid YUY2 32595559-0000-0010-8000-00AA00389B71 */
				FRAME_BPP, /* 16 bits per pixel */
				1, /* Default frame index: #1 */
				0, /* bAspectRatioX */
				0, /* bAspectRatioY */
				0, /* No interlace */
				0  /* No copy protect restrictions */
			},
			/* Frame format 320x240 */
			{
				sizeof(USBVideoUncompressedFrameDescriptor1),
				VIDGenericDescriptor_INTERFACE, /* CS_INTERFACE */
				VIDStreamingInterfaceDescriptor_FRM_UNCOMPRESSED,
				/* VS_FRAME_UNCOMPRESSED */
				1, /* Frame index #1 */
				0, /* Still image not supported */
				VIDCAMD_FW_1, /* wWidth */
				VIDCAMD_FH_1, /* wHeight */
				FRAME_BITRATEC(VIDCAMD_FW_1, VIDCAMD_FH_1, 30), /* Min bitrate */
				FRAME_BITRATEC(VIDCAMD_FW_1, VIDCAMD_FH_1, 30), /* Max bitrate */
				FRAME_BUFFER_SIZEC(VIDCAMD_FW_1, VIDCAMD_FH_1),
				/* maxFrameBufferSize: 320*240*2 */
				FRAME_INTERVALC(30), /* Default interval: 4F/s */
				1, /* 1 Interval setting */
				{
					FRAME_INTERVALC(30), /* 4F/s, 614.4KB/s */
				},
			},
			/* Frame format 640x480 */
			{
				sizeof(USBVideoUncompressedFrameDescriptor1),
				VIDGenericDescriptor_INTERFACE, /* CS_INTERFACE */
				VIDStreamingInterfaceDescriptor_FRM_UNCOMPRESSED, /* VS_FRAME_UNCOMPRESSED */
				2, /* Frame index #2 */
				0, /* Still image not supported */
				VIDCAMD_FW_2, /* wWidth */
				VIDCAMD_FH_2, /* wHeight */
				FRAME_BITRATEC(VIDCAMD_FW_2, VIDCAMD_FH_2, 15), /* Min bitrate */
				FRAME_BITRATEC(VIDCAMD_FW_2, VIDCAMD_FH_2, 15), /* Max bitrate */
				FRAME_BUFFER_SIZEC(VIDCAMD_FW_2, VIDCAMD_FH_2),
				/* maxFrameBufferSize: 640*480*2 */
				FRAME_INTERVALC(15), /* Default interval: 1F/s */
				1, /* 1 Interval setting */
				{
					FRAME_INTERVALC(15), /* 1F/s, 614.4KB/s */
				},
			},
			/* Frame format 176x144 */
			{
				sizeof(USBVideoUncompressedFrameDescriptor1),
				VIDGenericDescriptor_INTERFACE, /* CS_INTERFACE */
				VIDStreamingInterfaceDescriptor_FRM_UNCOMPRESSED,
				/* VS_FRAME_UNCOMPRESSED */
				3, /* Frame index #3 */
				0, /* Still image not supported */
				VIDCAMD_FW_3, /* wWidth */
				VIDCAMD_FH_3, /* wHeight */
				FRAME_BITRATEC(VIDCAMD_FW_3, VIDCAMD_FH_3, 30), /* Min bitrate */
				FRAME_BITRATEC(VIDCAMD_FW_3, VIDCAMD_FH_3, 30), /* Max bitrate */
				FRAME_BUFFER_SIZEC(VIDCAMD_FW_3, VIDCAMD_FH_3),
				/* maxFrameBufferSize: 176*144*2 = 50688 */
				FRAME_INTERVALC(30), /* Default interval: 12F/s */
				1, /* 1 Interval setting */
				{
					FRAME_INTERVALC(30), /* 12F/s, 608.256KB/s */
				},
			},
			/* Color format Uncompressed */
			{
				sizeof(USBVideoColorMatchingDescriptor),
				VIDGenericDescriptor_INTERFACE, /* CS_INTERFACE */
				VIDStreamingInterfaceDescriptor_COLORFORMAT, /* VS_COLORFORMAT */
				1, /* BT.709, sRGB */
				1, /* BT.709 */
				4, /* BT.601 */
			}
		}
	},
	/* VS Interface Descriptor: 400K */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		VIDCAMD_StreamInterfaceNum, /* interface #1 */
		1, /* alternate 1 */
		1, /* 1 endpoint */
		VIDStreamingInterfaceDescriptor_CLASS,
		VIDStreamingInterfaceDescriptor_SUBCLASS,
		VIDStreamingInterfaceDescriptor_PROTOCOL,
		0  /* No string */
	},
	/* ISO IN EP 6 Descriptor */
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		0x80 | VIDCAMD_IsoInEndpointNum, /* EP2, IN */
		(USBEndpointDescriptor_ISOCHRONOUS),
		//|USBEndpointDescriptor_Asynchronous_ISOCHRONOUS),
		FRAME_PACKET_SIZE_FS,
		1
	}
};

/**  Configuration descriptors. */
const struct UsbVideoCamConfigurationDescriptors configurationDescriptorsHS =
{
	/* Configuration descriptor */
	{
		sizeof(USBConfigurationDescriptor),
		USBGenericDescriptor_CONFIGURATION,
		sizeof(struct UsbVideoCamConfigurationDescriptors),
		2, /* 2 interface in this configuration */
		1, /* This is configuration #1 */
		0, /* No string descriptor for this configuration */
		BOARD_USB_BMATTRIBUTES,
		USBConfigurationDescriptor_POWER(100)
	},
	/* IAD */
	{
		sizeof(USBInterfaceAssociationDescriptor),
		USBGenericDescriptor_INTERFACEASSOCIATION,
		VIDCAMD_ControlInterfaceNum, /* Start interface is #0 */
		2, /* 2 interface is associated */
		VIDIADDescriptor_CLASS,
		VIDIADDescriptor_SUBCLASS,
		VIDIADDescriptor_PROTOCOL,
		0
	},
	/* VC Interface descriptor */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		VIDCAMD_ControlInterfaceNum, /* This is interface #0 */
		0, /* This is setting #0 for interface */
		0,
		VIDControlInterfaceDescriptor_CLASS,    /* CC_VIDEO */
		VIDControlInterfaceDescriptor_SUBCLASS, /* SC_VIDEOCONTROL */
		VIDControlInterfaceDescriptor_PROTOCOL, /* PC_PROTOCOL_UNDEFINED */
		0, /* No string descriptor */
	},
	/* VC Class defined descriptors */
	{
		/* VC Header */
		{
			sizeof(UsbVideoControlInterfaceHeader1),
			VIDGenericDescriptor_INTERFACE, /* CS_INTERFACE */
			VIDGenericDescriptor_HEADER,    /* VC_HEADER */
			VIDHeaderDescriptor_VID1_00,
			sizeof(UsbVideoControlInterfaceDescriptor),
			176000000,
			1, /* 1 VideoStreaming interface */
			VIDCAMD_StreamInterfaceNum, /* VideoStreaming interface 1: interface #1 */
		},
		/* VC Camera Terminal */
		{
			sizeof(USBVideoCameraTerminalDescriptor),
			VIDGenericDescriptor_INTERFACE, /* CS_INTERFACE */
			VIDGenericDescriptor_INPUTTERMINAL, /* VC_INPUT_TERMINAL */
			1, /* Terminal ID: #1 */
			VIDInputTerminalDescriptor_CAMERA, /* ITT_CAMERA */
			0, /* Assoc: None */
			0, /* No string */
			0, /* Optical Zoom not supported */
			0, /* Optical Zoom not supported */
			0, /* Optical Zoom not supported */
			3, /* 3 bytes for bmControls */
			{0, 0, 0}
		},
		/* VC Output Terminal */
		{
			sizeof(USBVideoOutputTerminalDescriptor),
			VIDGenericDescriptor_INTERFACE, /* CS_INTERFACE */
			VIDGenericDescriptor_OUTPUTTERMINAL, /* VC_OUTPUT_TERMINAL */
			2, /* Terminal ID: #2 */
			VIDTerminalDescriptor_STREAMING, /* Streaming terminal */
			0, /* Assoc: None */
			1, /* Source: Terminal is connected to #1 */
			0  /* No string */
		}
	},
	/* VS Interface descriptor */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		VIDCAMD_StreamInterfaceNum, /* interface #1 */
		0, /* alternate 0 */
		0, /* no endpoint */
		VIDStreamingInterfaceDescriptor_CLASS,
		VIDStreamingInterfaceDescriptor_SUBCLASS,
		VIDStreamingInterfaceDescriptor_PROTOCOL,
		0  /* No string */
	},
	/* VS Class defined descriptors */
	{
		/* VS Input Header */
		{
			sizeof(UsbVideoInputHeaderDescriptor1),
			VIDGenericDescriptor_INTERFACE, /* CS_INTERFACE */
			VIDStreamingInterfaceDescriptor_INPUTHEADER, /* VS_INPUT_HEADER */
			1, /* Only 1 payload format */
			sizeof(UsbVideoStreamingInterfaceDescriptor),
			0x80 | VIDCAMD_IsoInEndpointNum, /* Endpoint address is 0x82 */
			0x00, /* Dynamic Format Change not supported */
			2, /* Terminal Link to #2 */
			0, /* Still Capture not supported */
			0, /* Trigger not supported */
			0, /* No trigger usage */
			1, /* 1 bmaControls */
			0  /* No bmaControls */
		},
		/* VS Format Uncompressed */
		{
			/* Payload uncompressed format */
			{
				sizeof(USBVideoUncompressedFormatDescriptor),
				VIDGenericDescriptor_INTERFACE, /* CS_INTERFACE */
				VIDStreamingInterfaceDescriptor_FMT_UNCOMPRESSED,
				/* VS_FORMAT_UNCOMPRESSED */
				1, /* Format index #1 */
				VIDCAMD_NumFrameTypes, /* 3 frame types */
				guidYUY2, /* guid YUY2 32595559-0000-0010-8000-00AA00389B71 */
				FRAME_BPP, /* 16 bits per pixel */
				1, /* Default frame index: #1 */
				0, /* bAspectRatioX */
				0, /* bAspectRatioY */
				0, /* No interlace */
				0  /* No copy protect restrictions */
			},
			/* Frame format 320x240 */
			{
				sizeof(USBVideoUncompressedFrameDescriptor1),
				VIDGenericDescriptor_INTERFACE, /* CS_INTERFACE */
				VIDStreamingInterfaceDescriptor_FRM_UNCOMPRESSED,
				/* VS_FRAME_UNCOMPRESSED */
				1, /* Frame index #1 */
				0, /* Still image not supported */
				VIDCAMD_FW_1, /* wWidth */
				VIDCAMD_FH_1, /* wHeight */
				FRAME_BITRATEC(VIDCAMD_FW_1, VIDCAMD_FH_1, 1), /* Min bitrate */
				FRAME_BITRATEC(VIDCAMD_FW_1, VIDCAMD_FH_1, 1), /* Max bitrate */
				FRAME_BUFFER_SIZEC(VIDCAMD_FW_1, VIDCAMD_FH_1),
				/* maxFrameBufferSize: 320*240*2 */
				FRAME_INTERVALC(1), /* Default interval: 30F/s */
				1, /* 1 Interval setting */
				{
					FRAME_INTERVALC(1), /* 30F/s, 4608KB/s */
				},
			},
			/* Frame format 640x480 */
			{
				sizeof(USBVideoUncompressedFrameDescriptor1),
				VIDGenericDescriptor_INTERFACE, /* CS_INTERFACE */
				VIDStreamingInterfaceDescriptor_FRM_UNCOMPRESSED,
				/* VS_FRAME_UNCOMPRESSED */
				2, /* Frame index #4 */
				0, /* Still image not supported */
				VIDCAMD_FW_2, /* wWidth */
				VIDCAMD_FH_2, /* wHeight */
				FRAME_BITRATEC(VIDCAMD_FW_2, VIDCAMD_FH_2, 1), /* Min bitrate */
				FRAME_BITRATEC(VIDCAMD_FW_2, VIDCAMD_FH_2, 1), /* Max bitrate */
				FRAME_BUFFER_SIZEC(VIDCAMD_FW_2, VIDCAMD_FH_2),
				/* maxFrameBufferSize: 640*480*2 */
				FRAME_INTERVALC(1), /* Default interval: 12F/s */
				1, /* 1 Interval setting */
				{
					FRAME_INTERVALC(1), /* 12F/s, 7372.8KB/s */
				},
			},
			/* Frame format 176x144 */
			{
				sizeof(USBVideoUncompressedFrameDescriptor1),
				VIDGenericDescriptor_INTERFACE, /* CS_INTERFACE */
				VIDStreamingInterfaceDescriptor_FRM_UNCOMPRESSED,
				/* VS_FRAME_UNCOMPRESSED */
				3, /* Frame index #1 */
				0, /* Still image not supported */
				VIDCAMD_FW_3, /* wWidth */
				VIDCAMD_FH_3, /* wHeight */
				FRAME_BITRATEC(VIDCAMD_FW_3, VIDCAMD_FH_3, 30), /* Min bitrate */
				FRAME_BITRATEC(VIDCAMD_FW_3, VIDCAMD_FH_3, 30), /* Max bitrate */
				FRAME_BUFFER_SIZEC(VIDCAMD_FW_3, VIDCAMD_FH_3),
				/* maxFrameBufferSize: 176*144*2 = 50680 */
				FRAME_INTERVALC(30), /* Default interval: 30F/s */
				1, /* 1 Interval setting */
				{
					FRAME_INTERVALC(30), /* 30F/s, 1520.4KB/s */
				}
			},
			/* Color format Uncompressed */
			{
				sizeof(USBVideoColorMatchingDescriptor),
				VIDGenericDescriptor_INTERFACE, /* CS_INTERFACE */
				VIDStreamingInterfaceDescriptor_COLORFORMAT, /* VS_COLORFORMAT */
				1, /* BT.709, sRGB */
				1, /* BT.709 */
				4, /* BT.601 */
			}
		}
	},
	/* VS Interface Descriptor: 400K */
	{
		sizeof(USBInterfaceDescriptor),
		USBGenericDescriptor_INTERFACE,
		VIDCAMD_StreamInterfaceNum, /* interface #1 */
		1, /* alternate 1 */
		1, /* 1 endpoint */
		VIDStreamingInterfaceDescriptor_CLASS,
		VIDStreamingInterfaceDescriptor_SUBCLASS,
		VIDStreamingInterfaceDescriptor_PROTOCOL,
		0  /* No string */
	},
	/* ISO IN EP 2 Descriptor */
	{
		sizeof(USBEndpointDescriptor),
		USBGenericDescriptor_ENDPOINT,
		0x80 | VIDCAMD_IsoInEndpointNum, /* EP2, IN */
		(USBEndpointDescriptor_ISOCHRONOUS ),
		//|USBEndpointDescriptor_Asynchronous_ISOCHRONOUS),
		VIDCAMD_EpDesc_MaxPacketSize,
		1
	}
};

/**  List of descriptors used by the device. */

const USBDDriverDescriptors usbdDriverDescriptors =
{
	&usbDeviceDescriptor,
	(const USBConfigurationDescriptor *) &configurationDescriptorsFS,
	&qualifierDescriptor,
	0, // No full-speed other speed configuration descriptor
	0, // No high-speed device descriptor (Uses FS one)
	(const USBConfigurationDescriptor *) &configurationDescriptorsHS,
	&qualifierDescriptor,
	0, // No high-speed other speed configuration descriptor
	0, // No string descriptor
	0  // No string descriptor
};

/**@}*/

