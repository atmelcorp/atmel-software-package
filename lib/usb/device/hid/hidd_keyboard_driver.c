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
 * \addtogroup usbd_hid_key
 *@{
 * Implement a USB device that only have HID Keyboard Function.
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "trace.h"

#include "usb/common/usb_requests.h"
#include "usb/common/hid/hid_descriptors.h"
#include "usb/common/hid/hid_reports.h"
#include "usb/common/hid/hid_requests.h"
#include "usb/common/hid/hid_usages.h"
#include "usb/device/hid/hidd_function.h"
#include "usb/device/hid/hidd_keyboard_driver.h"
#include "usb/device/usbd_driver.h"
#include "usb/device/usbd.h"

/*------------------------------------------------------------------------------
 *         Internal types
 *------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *         Internal variables
 *------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *         Internal functions
 *------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *      Exported functions
 *------------------------------------------------------------------------------*/

/**
 * Initializes the HID keyboard device driver.
 */
void hidd_keyboard_driver_initialize(const USBDDriverDescriptors *descriptors)
{
	usbd_driver_initialize(descriptors, NULL, 0);
	hidd_keyboard_initialize(0);
	usbd_init();
}

/**
 * Handles configureation changed event.
 * \param cfgnum New configuration number
 */
void hidd_keyboard_driver_configuration_changed_handler(uint8_t cfgnum)
{
	const USBDDriverDescriptors *descriptors = usbd_driver_get_descriptors();
	USBConfigurationDescriptor *desc;

	if (cfgnum > 0) {
		if (usbd_is_high_speed() && descriptors->pHsConfiguration)
			desc = (USBConfigurationDescriptor*)descriptors->pHsConfiguration;
		else
			desc = (USBConfigurationDescriptor*)descriptors->pFsConfiguration;
		hidd_keyboard_configure_function((USBGenericDescriptor*)desc, desc->wTotalLength);
	}
}

/**
 * Handles HID-specific SETUP request sent by the host.
 * \param request Pointer to a USBGenericRequest instance.
 */
void hidd_keyboard_driver_request_handler(const USBGenericRequest *request)
{
	LIBUSB_TRACE("NewReq ");

	/* Process HID requests */
	if (USBRC_SUCCESS == hidd_keyboard_request_handler(request)) {
		return;
	}
	/* Process STD requests */
	else {
		usbd_driver_request_handler(request);
	}
}

/**@}*/

