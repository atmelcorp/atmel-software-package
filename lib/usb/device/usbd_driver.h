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
 *    USB Device Driver class definition.
 *
 * \section Usage
 *
 *    -# Instantiate a USBDDriver object and initialize it using
 *       usbd_driver_initialize.
 *    -# When a USB SETUP request is received, forward it to the standard
 *       driver using usbd_driver_request_handler.
 *    -# Check the Remote Wakeup setting via usbd_driver_is_remote_wakeup_enabled.
 */

#ifndef USBDDRIVER_H
#define USBDDRIVER_H

/** \addtogroup usbd_interface
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>

#include "compiler.h"

#include "usb/common/usb_requests.h"
#include "usb/common/usb_descriptors.h"
#include "usb/device/usb_lib_types.h"

/*------------------------------------------------------------------------------
 *         Types
 *------------------------------------------------------------------------------*/

/**
 * \typedef USBDDriverDescriptors
 * \brief List of all descriptors used by a USB device driver. Each descriptor
 *        can be provided in two versions: full-speed and high-speed. Devices
 *        which are not high-speed capable do not need to provided high-speed
 *        descriptors and the full-speed qualifier & other speed descriptors.
 */
typedef struct _USBDDriverDescriptors {
	/** Pointer to the full-speed device descriptor */
	const USBDeviceDescriptor *pFsDevice;

	/** Pointer to the full-speed configuration descriptor */
	const USBConfigurationDescriptor *pFsConfiguration;

	/** Pointer to the full-speed qualifier descriptor */
	const USBDeviceQualifierDescriptor *pFsQualifier;

	/** Pointer to the full-speed other speed configuration descriptor */
	const USBConfigurationDescriptor *pFsOtherSpeed;

	/** Pointer to the high-speed device descriptor */
	const USBDeviceDescriptor *pHsDevice;

	/** Pointer to the high-speed configuration descriptor */
	const USBConfigurationDescriptor *pHsConfiguration;

	/** Pointer to the high-speed qualifier descriptor */
	const USBDeviceQualifierDescriptor *pHsQualifier;

	/** Pointer to the high-speed other speed configuration descriptor */
	const USBConfigurationDescriptor *pHsOtherSpeed;

	/** Pointer to the list of string descriptors */
	const uint8_t **pStrings;

	/** Number of string descriptors in list */
	uint8_t numStrings;
} USBDDriverDescriptors;

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

extern void usbd_driver_initialize(const USBDDriverDescriptors *descriptors, uint8_t *interfaces, uint32_t size);

extern const USBDDriverDescriptors *usbd_driver_get_descriptors(void);

extern USBConfigurationDescriptor* usbd_driver_get_cfg_descriptors(uint8_t cfgnum);

extern void usbd_driver_request_handler(const USBGenericRequest *request);

extern bool usbd_driver_is_remote_wakeup_enabled(void);

extern uint8_t usbd_driver_return_otg_features(void);

extern void usbd_driver_clear_otg_features(void);

extern void usbd_driver_callbacks_configuration_changed(uint8_t cfgnum);

extern void usbd_driver_callbacks_interface_setting_changed(uint8_t interface,
		uint8_t setting);

/**@}*/

#endif /*#ifndef USBDDRIVER_H*/

