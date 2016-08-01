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

/**
 * \file
 *
 * \section Purpose
 *
 *   Definitions and methods for USB composite device implement.
 *
 */

#ifndef HIDAUDDDRIVER_H
#define HIDAUDDDRIVER_H
/** \addtogroup usbd_composite_hidaud
 *@{
 */

/*---------------------------------------------------------------------------
 *         Headers
 *---------------------------------------------------------------------------*/

#include "compiler.h"

#include "usb/common/audio/aud_descriptors.h"
#include "usb/common/hid/hid_descriptors.h"
#include "usb/common/usb_requests.h"
#include "usb/device/usbd_driver.h"
#include "usb/device/usbd.h"

/*---------------------------------------------------------------------------
 *         Definitions
 *---------------------------------------------------------------------------*/

/** \addtogroup usbd_hid_aud_desc USB HID(Keyboard) + AUD(Speaker) Definitions
 *      @{
 */
/** Number of interfaces of the device 1+2 */
#define HIDAUDDDriverDescriptors_NUMINTERFACE       3
/** Number of the CDC interface. */
#define HIDAUDDDriverDescriptors_HID_INTERFACE      0
/** Number of the Audio interface. */
#define HIDAUDDDriverDescriptors_AUD_INTERFACE      1
/**     @}*/

/*---------------------------------------------------------------------------
 *         Types
 *---------------------------------------------------------------------------*/


/** Structure of audio header descriptor*/
typedef PACKED_STRUCT _AUDHeaderDescriptor1{

	/** Header descriptor.*/
	AUDHeaderDescriptor header;
	/** Id of the first grouped interface.*/
	unsigned char bInterface0;

} AUDHeaderDescriptor1;

/**
 * Feature unit descriptor with 3 channel controls (master, right, left).
 */
typedef PACKED_STRUCT _AUDFeatureUnitDescriptor3{

	/** Feature unit descriptor.*/
	AUDFeatureUnitDescriptor feature;
	/** Available controls for each channel.*/
	unsigned char bmaControls[3];
	/** Index of a string descriptor for the feature unit.*/
	unsigned char iFeature;

} AUDFeatureUnitDescriptor3;

/**
 * List of descriptors for detailing the audio control interface of a
 * device using a USB audio speaker driver.
 */
typedef PACKED_STRUCT _AUDDSpeakerDriverAudioControlDescriptors{

	/** Header descriptor (with one slave interface).*/
	AUDHeaderDescriptor1 header;
	/** Input terminal descriptor.*/
	AUDInputTerminalDescriptor input;
	/** Output terminal descriptor.*/
	AUDOutputTerminalDescriptor output;
	/** Feature unit descriptor.*/
	AUDFeatureUnitDescriptor3 feature;

} AUDDSpeakerDriverAudioControlDescriptors;

/**
 * Format type I descriptor with one discrete sampling frequency.
 */
typedef PACKED_STRUCT _AUDFormatTypeOneDescriptor1{

	/** Format type I descriptor.*/
	AUDFormatTypeOneDescriptor formatType;
	/** Sampling frequency in Hz.*/
	unsigned char tSamFreq[3];

} AUDFormatTypeOneDescriptor1;

/**
 * \typedef CdcAudDriverConfigurationDescriptors
 * \brief Configuration descriptor list for a device implementing a
 *        composite HID (Keyboard) + Audio (Speaker) driver.
 */
typedef PACKED_STRUCT _HidAuddDriverConfigurationDescriptors {

	/** Standard configuration descriptor. */
	USBConfigurationDescriptor configuration;

	/* --- HID */
	/** HID interface. */
	USBInterfaceDescriptor hidInterface;
	/** HID descriptor */
	HIDDescriptor1 hid;
	/** HID interrupt IN */
	USBEndpointDescriptor hidInterruptIn;
	/** HID interrupt OUT */
	USBEndpointDescriptor hidInterruptOut;

	/* --- AUDIO (AC) */
	/** Audio IAD */
	USBInterfaceAssociationDescriptor audIAD;
	/** Audio control interface.*/
	USBInterfaceDescriptor audInterface;
	/** Descriptors for the audio control interface.*/
	AUDDSpeakerDriverAudioControlDescriptors audControl;
	/* -- AUDIO out (AS) */
	/** Streaming out interface descriptor (with no endpoint, required).*/
	USBInterfaceDescriptor audStreamingOutNoIsochronous;
	/** Streaming out interface descriptor.*/
	USBInterfaceDescriptor audStreamingOut;
	/** Audio class descriptor for the streaming out interface.*/
	AUDStreamingInterfaceDescriptor audStreamingOutClass;
	/** Stream format descriptor.*/
	AUDFormatTypeOneDescriptor1 audStreamingOutFormatType;
	/** Streaming out endpoint descriptor.*/
	AUDEndpointDescriptor audStreamingOutEndpoint;
	/** Audio class descriptor for the streaming out endpoint.*/
	AUDDataEndpointDescriptor audStreamingOutDataEndpoint;

} HidAuddDriverConfigurationDescriptors;


/*---------------------------------------------------------------------------
 *         Exported functions
 *---------------------------------------------------------------------------*/

extern void hid_audd_driver_initialize(const USBDDriverDescriptors * pDescriptors);
extern void hid_audd_driver_configuration_changed_handler(uint8_t cfgnum);
extern void hid_audd_driver_interface_setting_changed_handler(
	uint8_t interface, uint8_t setting);
extern void hid_audd_driver_request_handler(const USBGenericRequest *request);

/**@}*/
#endif //#ifndef CDCHIDDDRIVER_H

