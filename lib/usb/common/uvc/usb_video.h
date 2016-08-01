/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
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
/** \cond usb_video */
/** \file */

#ifndef _USBVID_H_
#define _USBVID_H_
/** \addtogroup usb_video
 *@{
 */

/*----------------------------------------------------------------------------
 *         Includes
 *----------------------------------------------------------------------------*/

#include <stdint.h>

#include "compiler.h"

#include "usb/common/usb_requests.h"

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

/* Video Interface Class Code */
#define CC_VIDEO                        0x0E
/* Video Interface Subclass Code */
#define SC_UNDEFINED                    0x00
#define SC_VIDEOCONTROL                 0x01
#define SC_VIDEOSTREAMING               0x02
#define SC_VIDEO_INTERFACE_COLLECTION   0x03
/* Video Interface Protocol Codes */
#define PC_PROTOCOL_UNDEFINED           0x00
/* Video Class-Specific Descriptor Types */
#define CS_UNDEFINED                    0x20
#define CS_DEVICE                       0x21
#define CS_CONFIGURATION                0x22
#define CS_STRING                       0x23
#define CS_INTERFACE                    0x24
#define CS_ENDPOINT                     0x25
/* Video Class-Specific VC Interface Descriptor Subtypes */
#define VC_DESCRIPTOR_UNDEFINED         0x00
#define VC_HEADER                       0x01
#define VC_INPUT_TERMINAL               0x02
#define VC_OUTPUT_TERMINAL              0x03
#define VC_SELECTOR_UNIT                0x04
#define VC_PROCESSING_UNIT              0x05
#define VC_EXTENSION_UNIT               0x06
/* Video Class-Specific VS Interface Descriptor Subtypes */
#define VS_UNDEFINED                    0x00
#define VS_INPUT_HEADER                 0x01
#define VS_OUTPUT_HEADER                0x02
#define VS_STILL_IMAGE_FRAME            0x03
#define VS_FORMAT_UNCOMPRESSED          0x04
#define VS_FRAME_UNCOMPRESSED           0x05
#define VS_FORMAT_MJPEG                 0x06
#define VS_FRAME_MJPEG                  0x07
#define VS_FORMAT_MPEG1                 0x08
#define VS_FORMAT_MPEG2PS               0x09
#define VS_FORMAT_MPEG2TS               0x0A
#define VS_FORMAT_MPEG4SL               /* TBD(not 0x0B) */
#define VS_FORMAT_DV                    0x0C
#define VS_COLORFORMAT                  0x0D
#define VS_FORMAT_VENDOR                0x0E
#define VS_FRAME_VENDOR                 0x0F
/* Video Class-Specific Endpoint Descriptor Subtypes */
#define EP_UNDEFINED                    0x00
#define EP_GENERAL                      0x01
#define EP_ENDPOINT                     0x02
#define EP_INTERRUPT                    0x03
/* USB Terminal Types */
#define TT_VENDOR_SPECIFIC              0x0100
#define TT_STREAMING                    0x0101
/* Input Terminal Types */
#define ITT_VENDOR_SPECIFIC             0x0200
#define ITT_CAMERA                      0x0201
#define ITT_MEDIA_TRANSPORT_INPUT       0x0202
/* Output Terminal Types */
#define OTT_VENDOR_SPECIFIC             0x0300
#define OTT_DISPLAY                     0x0301
#define OTT_MEDIA_TRANSPORT_OUTPUT      0x0302
/* External Terminal Types */
#define EXTERNAL_VENDOR_SPECIFIC        0x0400
#define COMPOSITE_CONNECTOR             0x0401
#define SVIDEO_CONNECTOR                0x0402
#define COMPONENT_CONNECTOR             0x0403
/* Compression formats GUID */
#define guidYUY2    {0x32595559, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71}}
#define guidNV12    {0x3231564E, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71}}

/* Video Class-Specific Request Codes */
#define RC_UNDEFINED                    0x00
#define SET_CUR                         0x01
#define GET_CUR                         0x81
#define GET_MIN                         0x82
#define GET_MAX                         0x83
#define GET_RES                         0x84
#define GET_LEN                         0x85
#define GET_INFO                        0x86
#define GET_DEF                         0x87
/* VideoControl Interface Control Selectors */
#define VC_CONTROL_UNDEFINED                    0x00
#define VC_VIDEO_POWER_MODE_CONTROL             0x01
#define VC_REQUEST_ERROR_CODE_CONTROL           0x02
#define VC_REQUEST_INDICATE_HOST_CLOCK_CONTROL  0x03
/* Terminal Control Selectors */
#define TE_CONTROL_UNDEFINED            0x00
/* Selector Unit Control Selectors */
#define SU_CONTROL_UNDEFINED            0x00
#define SU_INPUT_SELECT_CONTROL         0x01
/* Camera Terminal Control Selectors */
#define CT_CONTROL_UNDEFINED                0x00
#define CT_SCANNING_MODE_CONTROL            0x01
#define CT_AE_MODE_CONTROL                  0x02
#define CT_AE_PRIORITY_CONTROL              0x03
#define CT_EXPOSURE_TIME_ABSOLUTE_CONTROL   0x04
#define CT_EXPOSURE_TIME_RELATIVE_CONTROL   0x05
#define CT_FOCUS_ABSOLUTE_CONTROL           0x06
#define CT_FOCUS_RELATIVE_CONTROL           0x07
#define CT_FOCUS_AUTO_CONTROL               0x08
#define CT_IRIS_ABSOLUTE_CONTROL            0x09
#define CT_IRIS_RELATIVE_CONTROL            0x0A
#define CT_ZOOM_ABSOLUTE_CONTROL            0x0B
#define CT_ZOOM_RELATIVE_CONTROL            0x0C
#define CT_PANTILT_ABSOLUTE_CONTROL         0x0D
#define CT_PANTILT_RELATIVE_CONTROL         0x0E
#define CT_ROLL_ABSOLUTE_CONTROL            0x0F
#define CT_ROLL_RELATIVE_CONTROL            0x10
#define CT_PRIVACY_CONTROL                  0x11
/* Processing Unit Control Selectors */
#define PU_CONTROL_UNDEFINED                0x00
#define PU_BACKLIGHT_COMPENSATION_CONTROL   0x01
#define PU_BRIGHTNESS_CONTROL               0x02
#define PU_CONTRAST_CONTROL                 0x03
#define PU_GAIN_CONTROL                     0x04
#define PU_POWER_LINE_FREQUENCY_CONTROL     0x05
#define PU_HUE_CONTROL                      0x06
#define PU_STATURATION_CONTROL              0x07
#define PU_SHARPNESS_CONTROL                0x08
#define PU_GAMMA_CONTROL                    0x09
#define PU_WHITE_BALANCE_TEMPERATURE_CONTROL        0x0A
#define PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL   0x0B
#define PU_WHITE_BALANCE_COMPONENT_CONTROL          0x0C
#define PU_WHITE_BALANCE_COMPONENT_AUTO_CONTROL     0x0D
#define PU_DIGITAL_MULTIPLIER_CONTROL               0x0E
#define PU_DIGITAL_MULTIPLIER_LIMIT_CONTROL         0x0F
#define PU_HUE_AUTO_CONTROL                         0x10
/* Extension Unit Control Selectors */
#define XU_CONTROL_UNDEFINED                0x00
/* VideoStreaming Interface Control Selectors */
#define VS_CONTROL_UNDEFINED                0x00
#define VS_PROBE_CONTROL                    0x01
#define VS_COMMIT_CONTROL                   0x02
#define VS_STILL_PROBE_CONTROL              0x03
#define VS_STILL_COMMIT_CONTROL             0x04
#define VS_STILL_IMAGE_TRIGGER_CONTROL      0x05
#define VS_STREAM_ERROR_CODE_CONTROL        0x06
#define VS_GENERATE_KEY_FRAME_CONTROL       0x07
#define VS_UPDATE_FRAME_SEGMENT_CONTROL     0x08
#define VS_SYNCH_DELAY_CONTROL              0x09

/** \addtogroup usb_video_desc_type USB Video descriptor types
 *      @{
 * This section lists the available types for USB video-specific descriptors.
 */

/** Descriptor gives detail about the whole device (CS_DEVICE).*/
#define VIDGenericDescriptor_DEVICE                     0x21
/** Descriptor gives detail about a configuration (CS_CONFIGURATION).*/
#define VIDGenericDescriptor_CONFIGURATION              0x22
/** Descriptor gives detail about a string (CS_STRING).*/
#define VIDGenericDescriptor_STRING                     0x23
/** Descriptor gives detail about an interface (CS_INTERFACE).*/
#define VIDGenericDescriptor_INTERFACE                  0x24
/** Descriptor gives detail about an endpoint (CS_ENDPOINT).  */
#define VIDGenericDescriptor_ENDPOINT                   0x25
/**     @}*/

/** \addtogroup usb_video_desc_subtype USB Video descriptor subtypes
 *      @{
 * This section lists the possible subtypes for USB video-specific descriptors.
 */
/** Header descriptor subtype(VC_HEADER).*/
#define VIDGenericDescriptor_HEADER                     0x01
/** Input terminal descriptor subtype(VC_INPUT_TERMINAL).*/
#define VIDGenericDescriptor_INPUTTERMINAL              0x02
/** Output terminal descriptor subtype(VC_OUTPUT_TERMINAL).*/
#define VIDGenericDescriptor_OUTPUTTERMINAL             0x03
/** Selector unit descriptor subtype(VC_SELECTOR_UNIT).*/
#define VIDGenericDescriptor_SELECTORUNIT               0x04
/** Processing unit descriptor subtype(VC_PROCESSING_UNIT).*/
#define VIDGenericDescriptor_PROCESSINGUNIT             0x05
/** Extension unit descriptor subtype(VC_EXTENSION_UNIT).*/
#define VIDGenericDescriptor_EXTENSIONUNIT              0x06
/**     @}*/


/** \addtogroup usb_video_desc USB Video Descriptors
 *      @{
 * USB Video device descriptor values
 *
 * This section lists the class, subclass & protocol codes that a USB video
 * device should display in its device descriptor.
 */
/** Class code for a USB video device. */
#define VIDDeviceDescriptor_CLASS                           0xEF
/** Subclass code for a USB video device. */
#define VIDDeviceDescriptor_SUBCLASS                        0x02
/** Protocol code for a USB video device. */
#define VIDDeviceDescriptor_PROTOCOL                        0x01
/**     @}*/

/** \addtogroup usb_iad USB IAD
 *      @{
 */
/** Video Interface Class Code (CC_VIDEO) */
#define VIDIADDescriptor_CLASS                              0x0E
/** Video Interface SubClass Code (SC_VIDEO_INTERFACE_COLLECTION) */
#define VIDIADDescriptor_SUBCLASS                           0x03
/** Protocol (PC_PROTOCOL_UNDEFINED) */
#define VIDIADDescriptor_PROTOCOL                           0x00
/**     @}*/

/** \addtogroup usb_video_ctrl_if USB Video Control Interface
 *      @{
 * This section lists the class, subclass and protocol codes that a USB Video
 * Control interface descriptor should display.
 */
/** Class code for an video control interface (CC_VIDEO). */
#define VIDControlInterfaceDescriptor_CLASS                 0x0E
/** Subclass code for an video control interface (SC_VIDEOCONTROL). */
#define VIDControlInterfaceDescriptor_SUBCLASS              0x01
/** Protocol code for an video control interface (PC_PROTOCOL_UNDEFINED). */
#define VIDControlInterfaceDescriptor_PROTOCOL              0x00
/**     @}*/

/**
 *  \addtogroup usb_video_stream_if USB VideoStreaming interface codes
 *      @{
 * This section lists the class, subclass and protocol codes that an Video
 * Streaming interface should display in its descriptor.
 */
/** Class code for an USB video streaming interface (CC_VIDEO).*/
#define VIDStreamingInterfaceDescriptor_CLASS               0x0E
/** Subclass code for an video streaming interface (SC_VIDEOSTREAMING).*/
#define VIDStreamingInterfaceDescriptor_SUBCLASS            0x02
/** Protocol code for an video streaming interface (PC_PROTOCOL_UNDEFINED).*/
#define VIDStreamingInterfaceDescriptor_PROTOCOL            0x00
/**     @}*/

/**
 * \addtogroup usb_video_stream_subtype USB Video streaming descriptor subtypes
 *      @{
 * This section lists the possible subtypes for video-specific descriptor
 * appended to an Video Streaming interface.
 */
/** Undefined */
#define VIDStreamingInterfaceDescriptor_UNDEFINED           0x00
/** Input header.*/
#define VIDStreamingInterfaceDescriptor_INPUTHEADER         0x01
/** Output Header.*/
#define VIDStreamingInterfaceDescriptor_OUTPUTHEADER        0x02
/** Still Image Frame.*/
#define VIDStreamingInterfaceDescriptor_STI_FRAME           0x03
#define VIDStreamingInterfaceDescriptor_FMT_UNCOMPRESSED    0x04
#define VIDStreamingInterfaceDescriptor_FRM_UNCOMPRESSED    0x05
#define VIDStreamingInterfaceDescriptor_FMT_MJPEG           0x06
#define VIDStreamingInterfaceDescriptor_FRM_MJPEG           0x07
#define VIDStreamingInterfaceDescriptor_FMT_MPEG1           0x08
#define VIDStreamingInterfaceDescriptor_FMT_MPEG2PS         0x09
#define VIDStreamingInterfaceDescriptor_FMT_MPEG2TS         0x0A
#define VIDStreamingInterfaceDescriptor_FMT_DV              0x0C
#define VIDStreamingInterfaceDescriptor_COLORFORMAT         0x0D
#define VIDStreamingInterfaceDescriptor_FMT_VENDOR          0x0E
#define VIDStreamingInterfaceDescriptor_FRM_VENDOR          0x0F
/**     @}*/

/** \addtogroup usb_video_ep_subtype USB Video Endpoint descriptor subtypes
 *      @{
 */
/** EP_UNDEFINED */
#define VIDEndpointDescriptor_UNDEFINED         0x00
/** EP_GENERAL */
#define VIDEndpointDescriptor_GENERAL           0x01
/** EP_ENDPOINT */
#define VIDEndpointDescriptor_ENDPOINT          0x02
/** EP_INTERRUPT */
#define VIDEndpointDescriptor_INTERRUPT         0x03
/**     @}*/

/** \addtogroup usb_video_class_ver USB Video class releases
 *      @{
 * This section lists the existing versions of the Video class specification.
 * - \ref VIDHeaderDescriptor_VID1_00
 */

/** Identifies the USB video specification release 1.00.*/
#define VIDHeaderDescriptor_VID1_00                 0x0110
/**     @}*/

/** TT_STREAMING */
#define VIDTerminalDescriptor_STREAMING             0x0101

/** \addtogroup usb_video_in_term USB Video Input terminal types
 *  @{
 * This section lists the available types for an Input terminal.
 */
/** ITT_VENDOR_SPECIFIC */
#define VIDInputTerminalDescriptor_VENDOR           0x0200
/** ITT_CAMERA */
#define VIDInputTerminalDescriptor_CAMERA           0x0201
/** ITT_MEDIA_TRANSPORT_INPUT */
#define VIDInputTerminalDescriptor_MED_TRAN_INPUT   0x0202
/** @}*/

/** \addtogroup usb_video_out_term USB Video Output terminal types
 *  @{
 * This section lists the available types for an output terminal.
 */
/** OTT_VENDOR_SPECIFIC */
#define VIDOutputTerminalDescriptor_VENDOR              0x0300
/** OTT_DISPLAY */
#define VIDOutputTerminalDescriptor_DISPLAY             0x0301
/** OTT_MEDIA_TRANSPORT_OUTPUT */
#define VIDOutputTerminalDescriptor_MED_TRAN_OUTPUT     0x0302
/** @}*/

/** \addtogroup usb_video_out_term USB Video External terminal types
 *  @{
 * This section lists the available types for an external terminal.
 */
/** OTT_VENDOR_SPECIFIC */
#define VIDExtTerminalDescriptor_VENDOR              0x0400
/** COMPOSITE_CONNECTOR */
#define VIDExtTerminalDescriptor_COMPOSITE_CONN      0x0401
/** SVIDEO_CONNECTOR */
#define VIDExtTerminalDescriptor_SVID_CONN           0x0402
/** COMPONENT_CONNECTOR */
#define VIDExtTerminalDescriptor_COMPONENT_CONN      0x0403
/** @}*/

/** \addtogroup usb_video_request USB Video request codes
 *      @{
 * This section lists the codes of the existing Video requests.
 */
/** SET_CUR request code.*/
#define VIDGenericRequest_SETCUR                0x01
/** GET_CUR request code.*/
#define VIDGenericRequest_GETCUR                0x81
/** GET_MIN request code.*/
#define VIDGenericRequest_GETMIN                0x82
/** GET_MAX request code.*/
#define VIDGenericRequest_GETMAX                0x83
/** GET_RES request code.*/
#define VIDGenericRequest_GETRES                0x84
#define VIDGenericRequest_GETLEN                0x85
#define VIDGenericRequest_GETINFO               0x86
#define VIDGenericRequest_GETDEF                0x87
/**     @}*/



/*----------------------------------------------------------------------------
 *         Types
 *----------------------------------------------------------------------------*/


/** GUID */
typedef PACKED_STRUCT _sGDID {
	uint32_t data1;
	uint16_t data2;
	uint16_t data3;
	uint8_t  data4[8];
} sGUID; /* GCC */

/* USB Video, 2.4.2.2 */
/**
 * Status packet header
 */
typedef PACKED_STRUCT _USBVideoStatusHdr {
	uint8_t bStatusType; /**< Originator VideoControl(1) or VideoStreaming(2) */
	uint8_t bOriginator; /**< ID of the Terminal, Unit or Interface */
}  USBVideoStatusHdr; /* GCC */
/**
 * Status packet for VideoControl Interface
 */
typedef PACKED_STRUCT _USBVideoStatusVC {
	uint8_t bStatusType; /**< Originator: VideoControl(1) */
	uint8_t bOriginator; /**< ID of the Terminal, Unit or Interface */
	uint8_t bEvent;      /**< 0x00: Control Change */
	uint8_t bSelector;   /**< Control change selector */
	uint8_t bAttribute;  /**< Type of control change: value(0), info(1), failure(2) */
	uint8_t bValue;      /**< Control request description value \sa "VideoControl Requests" */
} USBVideoStatusVC;
/**
 * Status packet for VideoStreaming Interface
 */
typedef PACKED_STRUCT _USBVideoStatusVS {
	uint8_t bStatusType; /**< Originator VideoStreaming(2) */
	uint8_t bOriginator; /**< ID of the Terminal, Unit or Interface */
	uint8_t bEvent;      /**< 0x00: Button Press, others: Stream Error */
	uint8_t bValue;      /**< Button Pressed/Released */
} USBVideoStatusVS; /* GCC */

/* USB Video, 2.4.3.3 */
/**
 * Payload Header
 */
typedef PACKED_STRUCT _USBVideoPayloadHeader {
	uint8_t bHeaderLength; /**< Length of header including this field */
	union _USBVideoHeaderInfo {
		uint8_t B;
		struct _USBVideoHeaderInfoBits {
			uint8_t FID:1, /**< D0: Frame ID */
					EoF:1, /**< D1: End of Frame */
					PTS:1, /**< D2: Presentation Time */
					SCR:1, /**< D3: Source Clock Reference */
					reserved:1,
					STI:1, /**< D4: Still Image */
					ERR:1, /**< D5: Error */
					EOH:1; /**< D6: End of Header */
		} bm;
	} bmHeaderInfo;  /**< Information on the sample data following header */
} USBVideoPayloadHeader;
/**
 * Payload header with extended fields
 */
typedef PACKED_STRUCT _USBVideoPayloadHdrExt {
	uint8_t  bHeaderLength; /**< Length of header including this field */
	uint8_t  bmHeaderInfo;  /**< Information on the sample data following header */
	uint32_t dwPresentationTime; /**< Source Clock Time in native device clock units when the raw frame capture begins */
	struct _SourceClockReference {
		uint32_t dwSrcTimeClk;  /**< Source Time Clock in native device clock units */
		uint16_t sofCounter:11, /**< 1KHz SOF token counter */
				 reserved;      /**< Reserved, 0 */
	} scrSourceClock; /**< SourceClockReference SCR */
}  USBVideoPayloadHdrExt;

/* USB Video, 3.7.2 */
/**
 * Class-specific VideoControl Interface Header Descriptor
 * (With 1 streaming interface).
 */
typedef PACKED_STRUCT _USBVideoControlInterfaceDescriptor {
	uint8_t  bLength; /**< Size of descriptor: 12 + 1 bytes */
	uint8_t  bDescriptorType; /**< CS_INTERFACE descriptor type */
	uint8_t  bDescriptorSubType; /**< VC_HEADER descriptor subtype */
	uint16_t bcdVDC; /**< Video Device Class Specification release number in BCD */
	uint16_t wTotalLength; /**< Total number of bytes, including combined header and all unit and terminal descriptors */
	uint32_t dwClockFrequency; /**< Device clock frequency in Hz */
	uint8_t  bInCollection; /**< Number of VS interfaces in the Video Interface Collection */
	uint8_t  baInterfaceNr[1]; /**< Interface numbers of the VS interface in collection */
}USBVideoControlInterfaceDescriptor;
/**
 * Input Terminal Descriptor (ITD)
 * (With no additional fields depending on the Terminal Type)
 */
typedef PACKED_STRUCT _USBVideoInputTerminalDescriptor {
	uint8_t  bLength; /**< Size of descriptor: 8 + 0 bytes */
	uint8_t  bDescriptorType; /**< CS_INTERFACE descriptor type */
	uint8_t  bDescriptorSubType; /**< VC_INPUTTERMINAL descriptor subtype */
	uint8_t  bTerminalID; /**< None-zero Terminal ID */
	uint16_t wTerminalType; /**< Type of Terminal */
	uint8_t  bAssocTerminal; /**< ID of the output terminal to which this input terminal is associated */
	uint8_t  iTerminal; /**< Index of string descriptor */
} USBVideoInputTerminalDescriptor;
/**
 * Output Terminal Descriptor (OTD)
 * (With no additional fields depending on the Terminal Type)
 */
typedef PACKED_STRUCT _USBVideoOutputTerminalDescriptor {
	uint8_t  bLength; /**< Size of descriptor: 9 + 0 bytes */
	uint8_t  bDescriptorType; /**< CS_INTERFACE descriptor type */
	uint8_t  bDescriptorSubType; /**< VC_OUTPUT_TERMINAL descriptor subtype */
	uint8_t  bTerminalID; /**< None-zero Terminal ID */
	uint16_t wTerminalType; /**< Type of Terminal */
	uint8_t  bAssocTerminal; /**< Input Terminal to which this Output Terminal is connected */
	uint8_t  bSourceID; /**< ID of the Unit or Terminal to which this terminal is connected */
	uint8_t  iTerminal; /**< Index of string descriptor */
} USBVideoOutputTerminalDescriptor;
/**
 * Camera Terminal Descriptor
 */
typedef PACKED_STRUCT _USBVideoCameraTerminalDescriptor {
	uint8_t  bLength; /**< Size of descriptor: 15 + 3 bytes */
	uint8_t  bDescriptorType; /**< CS_INTERFACE descriptor type */
	uint8_t  bDescriptorSubType; /**< VC_INPUT_TERMINAL descriptor subtype */
	uint8_t  bTerminalID; /**< None-zero Terminal ID */
	uint16_t wTerminalType; /**< Type of Terminal: ITT_CAMERA */
	uint8_t  bAssocTerminal; /**< ID of the output terminal to which this input terminal is associated */
	uint8_t  iTerminal; /**< Index of string descriptor */
	uint16_t wObjectiveFocalLengthMin;
	uint16_t wObjectiveFocalLengthMax;
	uint16_t wOcularFocalLength;
	uint8_t  bControlSize; /**< Size in bytes of bmControls: 3 */
	uint8_t  bmControls[3];
} USBVideoCameraTerminalDescriptor;
/**
 * Selector Unit Descriptor (SUD)
 * (with 1 input pin)
 */
typedef PACKED_STRUCT _USBVideoSelectorUnitDescriptor {
	uint8_t  bLength; /**< Size of descriptor: 6 + 1 bytes */
	uint8_t  bDescriptorType; /**< CS_INTERFACE descriptor type */
	uint8_t  bDescriptorSubType; /**< VC_SELECTOR_UNIT descriptor subtype */
	uint8_t  bUnitID; /**< None-zero Unit ID */
	uint8_t  bNrInPins; /**< Number of Input Pins of this Unit */
	uint8_t  baSourceID[1]; /**< ID of the Unit or Terminal to which the Input Pins is connected */
	uint8_t  iSelector; /**< Index of string descriptor */
} USBVideoSelectorUnitDescriptor;
/**
 * Processing Unit Descriptor (PUD)
 */
typedef PACKED_STRUCT _USBVideoProcessingUnitDescriptor {
	uint8_t  bLength; /**< Size of descriptor: 9 + 2 bytes */
	uint8_t  bDescriptorType; /**< CS_INTERFACE descriptor type */
	uint8_t  bDescriptorSubType; /**< VC_PROCESSING_UNIT descriptor subtype */
	uint8_t  bUnitID; /**< None-zero Unit ID */
	uint8_t  bSourceID; /**< ID of the Unit or Terminal to which this Unit is connected */
	uint16_t wMaxMultiplier; /**< Max digital magnification, multiplied by 100 */
	uint8_t  bControlSize; /**< Size of bmControls: 2 */
	uint8_t  bmControls[2];
	uint8_t  iProcessing; /**< Index of string descriptor */
} USBVideoProcessingUnitDescriptor;
/**
 * Extension Unit Descriptor (XUD)
 * (with 1 input pin)
 */
typedef PACKED_STRUCT _USBVideoExtensionUnitDescriptor {
	uint8_t  bLength; /**< Size of descriptor: 24 + 1 + 1 bytes */
	uint8_t  bDescriptorType; /**< CS_INTERFACE descriptor type */
	uint8_t  bDescriptorSubType; /**< VC_EXTENSION_UNIT descriptor subtype */
	uint8_t  bUnitID; /**< None-zero Unit ID */
	sGUID    guidExtensionCode; /**< Vendor-specific code identifying the Extension Unit */
	uint8_t  bNumControls; /**< Number of controls in this extension unit */
	uint8_t  bNrInPins; /**< Number of Input Pins of this Unit */
	uint8_t  baSourceID[1]; /** ID of the Unit or Terminal to which the Input Pins of this extension unit is connected */
	uint8_t  bControlSize; /**< Size of bmControls field */
	uint8_t  bmControls[1];
	uint8_t  iExtension; /**< Index of string descriptor */
}  USBVideoExtensionUnitDescriptor;

/* USB Video, 3.8.2.2 */
/**
 * Class-specific VC Interrupt Endpoint Descriptor
 */
typedef PACKED_STRUCT _USBVideoControlInterruptEndpointDescriptor {
	uint8_t  bLength; /**< Size of descriptor: 5 bytes */
	uint8_t  bDescriptorType; /**< CS_ENDPOINT descriptor type */
	uint8_t  bDescriptorSubType; /**< EP_INTERRUPT descriptor subtype */
	uint16_t wMaxTransferSize; /**< Max interrupt structure size */
} USBVideoControlInterruptEndpointDescriptor;

/* USB Video, 3.9.2 */
/**
 * Class-specific VS Interface Input Header Descriptor
 * (with 1 format)
 */
typedef PACKED_STRUCT _USBVideoStreamingInputHeaderDescriptor {
	uint8_t  bLength; /**< Size of descriptor: 13 + (1*1) bytes */
	uint8_t  bDescriptorType; /**< CS_INTERFACE descriptor type */
	uint8_t  bDescriptorSubType; /**< VS_INPUT_HEADER descriptor subtype */
	uint8_t  bNumFormats; /**< Number of video payload format descriptors following (excluding frame descriptors) */
	uint16_t wTotalLength; /**< Total number of bytes returned for the VS interface descriptors */
	uint8_t  bEndpointAddress; /**< EP address for video data */
	uint8_t  bmInfo; /**< Capabilities, D0: Dynamic Format Change Supported */
	uint8_t  bTerminalLink; /**< Terminal ID of the Output Terminal to which the video EP is connected */
	uint8_t  bStillCaptureMethod; /**< Method of still image capture */
	uint8_t  bTriggerSupport; /**< If hardware trigger is supported */
	uint8_t  bTriggerUsage; /**< How host respond to HW trigger interrupt event: 0 initialize still image capture, 1 general purpose button */
	uint8_t  bControlSize; /**< Size of each bmaControls(x):8 */
	uint8_t  bmaControls[1][1];
}  USBVideoStreamingInputHeaderDescriptor;
/**
 * Class-specific VS Interface Output Header Descriptor
 */
typedef PACKED_STRUCT _USBVideoStreamingOutputHeaderDescriptor {
	uint8_t  bLength; /**< Size of descriptor: 8 bytes */
	uint8_t  bDescriptorType; /**< CS_INTERFACE descriptor type */
	uint8_t  bDescriptorSubType; /**< VS_OUTPUT_HEADER descriptor subtype */
	uint8_t  bNumFormats; /**< Number of video payload format descriptors following (excluding frame descriptors) */
	uint16_t wTotalLength; /**< Total number of bytes returned for the VS interface descriptors */
	uint8_t  bEndpointAddress; /**< EP address for video data */
	uint8_t  bTerminalLink; /**< Terminal ID of the Input Terminal to which the video EP is connected */
}  USBVideoStreamingOutputHeaderDescriptor;

/* USB Video Payload Uncompressed, 2.3 */
/**
 * Stream Header Format for Uncompressed Streams
 */
typedef USBVideoPayloadHeader USBVideoUncompressedStreamHeader;
/**
 * Stream Header Format for Uncompressed Streams with extension
 */
typedef USBVideoPayloadHdrExt USBVideoUncompressedStreamHeaderExt;

/* USB Video Payload Uncompressed, 3.1 */
/**
 * Uncompressed Video Format Descriptor
 */
typedef PACKED_STRUCT _USBVideoUncompressedFormatDescriptor {
	uint8_t  bLength; /**< Size of descriptor: 27 bytes */
	uint8_t  bDescriptorType; /**< CS_INTERFACE descriptor type */
	uint8_t  bDescriptorSubType; /**< VS_FORMAT_UNCOMPRESSED descriptor subtype */
	uint8_t  bFormatIndex; /**< Index of this format descriptor */
	uint8_t  bNumFrameDescriptors; /**< Number of frame descriptors following */
	sGUID    guidFormat; /**< GUID for stream-encoding format */
	uint8_t  bBitsPerPixel; /**< Number of bits per pixel used to specify color */
	uint8_t  bDefaultFrameIndex; /**< Optimum Frame Index (used to select resolution) for this stream */
	uint8_t  bAspectRatioX; /**< The X dimension of the picture aspect ratio */
	uint8_t  bAspectRatioY; /**< The Y dimension of the picture aspect ratio */
	uint8_t  bmInterlaceFlags; /**< interlace information */
	uint8_t  bCopyProtect; /**< Whether duplication of the video stream is restricted */
}  USBVideoUncompressedFormatDescriptor;
/**
 * Uncompressed Video Frame Descriptor
 * (bFrameIntervalType is 0, continuous)
 */
typedef PACKED_STRUCT _USBVideoUncompressedFrameDescriptor {
	uint8_t  bLength; /**< Size of descriptor: 27 bytes */
	uint8_t  bDescriptorType; /**< CS_INTERFACE descriptor type */
	uint8_t  bDescriptorSubType; /**< VS_FRAME_UNCOMPRESSED descriptor subtype */
	uint8_t  bFrameIndex; /**< Index of this frame descriptor */
	uint8_t  bmCapabilities; /**< Whether still images are supported */
	uint16_t wWidth; /**< Width of decoded bitmap frame in pixels */
	uint16_t wHeight; /**< Height of decoded bitmap frame in pixels */
	uint32_t dwMinBitRate; /**< Minimum bit rate at the longest frame interval, in bps */
	uint32_t dwMaxBitRate; /**< Maximum bit rate at the longest frame interval, in bps */
	uint32_t dwMaxVideoFrameBufferSize; /**< Max number of bytes that the compressor will produce for a video frame or still image */
	uint32_t dwDefaultFrameInterval; /**< Frame interval the device uses as default */
	uint8_t  bFrameIntervalType; /**< 0: Continuous frame interval */

	uint32_t dwMinFrameInterval; /**< shortest interval, in 100ns */
	uint32_t dwMaxFrameInterval; /**< longest interval, in 100ns */
	uint32_t dwFrameIntervalStep;/**< granularity of interval range, in 100ns */
}USBVideoUncompressedFrameDescriptor;
/**
 * Uncompressed Video Frame Descriptor
 * (with 1 interval setting)
 */
typedef PACKED_STRUCT _USBVideoUncompressedFrameDescriptor1 {
	uint8_t  bLength; /**< Size of descriptor: 26 + 4*1 bytes */
	uint8_t  bDescriptorType; /**< CS_INTERFACE descriptor type */
	uint8_t  bDescriptorSubType; /**< VS_FRAME_UNCOMPRESSED descriptor subtype */
	uint8_t  bFrameIndex; /**< Index of this frame descriptor */
	uint8_t  bmCapabilities; /**< Whether still images are supported */
	uint16_t wWidth; /**< Width of decoded bitmap frame in pixels */
	uint16_t wHeight; /**< Height of decoded bitmap frame in pixels */
	uint32_t dwMinBitRate; /**< Minimum bit rate at the longest frame interval, in bps */
	uint32_t dwMaxBitRate; /**< Maximum bit rate at the longest frame interval, in bps */
	uint32_t dwMaxVideoFrameBufferSize; /**< Max number of bytes that the compressor will produce for a video frame or still image */
	uint32_t dwDefaultFrameInterval; /**< Frame interval the device uses as default */
	uint8_t  bFrameIntervalType; /**< 1: The number of discrete frame intervals */

	uint32_t dwFrameInterva[1]; /**< shortest interval, in 100ns ... following are longer */
} USBVideoUncompressedFrameDescriptor1;

/* USB Video, 3.9.2.5, Table 3-17 */
/**
 * Still Image Frame Descriptor
 * (with 1 size and 1 compression format)
 */
typedef PACKED_STRUCT _USBVideoStillImageFrameDescriptor {
	uint8_t  bLength; /**< Size of descriptor: 10 + 4*1-4 + 1 bytes */
	uint8_t  bDescriptorType; /**< CS_INTERFACE descriptor type */
	uint8_t  bDescriptorSubType; /**< VS_STILL_IMAGE_FRAME descriptor subtype */
	uint8_t  bEndpointAddress; /**< EP address if method 3 of still image capture is used */
	uint8_t  bNumImageSizePatterns; /**< Number of Image Size patterns */
	uint16_t wWidth; /**< Width of image pattern 1 */
	uint16_t wHeight; /**< Height of image pattern 1 */
	uint8_t  bNumCompressionPattern; /**< Number of Compression pattern */
	uint8_t  bCompression[1]; /**< Compression of the still image */
} USBVideoStillImageFrameDescriptor;

/* USB Video, 3.9.2.6, Table 3-18 */
/**
 * Color Matching Descriptor
 */
typedef PACKED_STRUCT _USBVideoColorMatchingDescriptor {
	uint8_t  bLength; /**< Size of descriptor: 6 bytes */
	uint8_t  bDescriptorType; /**< CS_INTERFACE descriptor type */
	uint8_t  bDescriptorSubType; /**< VS_COLORFORMAT descriptor subtype */
	uint8_t  bColorPrimaries; /**< 1: BT.709, sRGB (default) */
	uint8_t  bTransferCharacteristics; /**< 1: BT.709 (default) */
	uint8_t  bMarixCoefficients; /**< 4: SMPTE 170M (BT.601, default) */
} USBVideoColorMatchingDescriptor;

/* USB Video, 4.3.1.1 */
/**
 * Video Probe and Commit Control Data
 */
typedef PACKED_STRUCT _USBVideoProbeCommitData {
	uint16_t bmHint; /**< Parameters shall be kept fixed */
	uint8_t  bFormatIndex; /**< Video format index from a format descriptor */
	uint8_t  bFrameIndex; /**< Video frame index from a frame descriptor */
	uint32_t dwFrameInterval; /**< Frame interval in 100ns units */
	uint16_t wKeyFrameRate; /**< Key frame rate in key frame/video frame units */
	uint16_t wPFrameRate; /**< PFrame rate in PFrame/key frame units */
	uint16_t wCompQuality; /**< Compression quality control in abstract units 0(lowest) to 10000(highest) */
	uint16_t wCompWindowSize; /**< Window size for average bit rate control */
	uint16_t wDelay; /**< Internal video streaming interface latency in ms from video data capture to presentation on the USB */
	uint32_t dwMaxVideoFrameSize; /**< Maximum video frame size in bytes */
	uint32_t dwMaxPayloadTransferSize; /**< Maximum number of bytes that the device can transmit in a single payload transfer */
	uint32_t dwClockFrequency; /**< The device clock frequency in Hz for the specified format */
	uint8_t  bmFramingInfo; /**< This control indicates to the function whether payload transfers will contain out-of-band framing information in the Video Payload Header */
	uint8_t  bPreferedVersion; /**< The preferred payload format version supported by the host or device for the specified bFormatIndex value */
	uint8_t  bMinVersion; /**< The minimum payload format version supported by the device for the specified bFormatIndex value */
	uint8_t  bMaxVersion; /**< The maximum payload format version supported by the device for the specified bFormatIndex value */
} USBVideoProbeData, USBVideoCommitData;


/*----------------------------------------------------------------------------
 *         Functions
 *----------------------------------------------------------------------------*/

/**
 * Return Control selector (CS), the high byte of wValue.
 */
static inline uint8_t USBVideoRequest_GetControlSelector(const USBGenericRequest *req)
{
	return ((req->wValue >> 8) & 0xFF);
}


/**@}*/
#endif /* _VIDDESCRIPTORS_H_ */
/** \endcond */
