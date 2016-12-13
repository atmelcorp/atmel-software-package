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

/**\file
 *   Title: CDCDSerialDriver implementation
 *
 *   About: Purpose
 *       Implementation of the CDCDSerialDriver class methods.
 */

/** \addtogroup usbd_cdc
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "trace.h"

#include "usb/device/cdc/cdcd_serial_driver.h"
#include "usb/device/usbd_driver.h"

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

/**
 *  Initializes the USB Device CDC serial driver & USBD Driver.
 *  \param  pDescriptors Pointer to Descriptors list for CDC Serial Device.
 */
void cdcd_serial_driver_initialize(const USBDDriverDescriptors *pDescriptors)
{
	/* Initialize the standard driver */
	usbd_driver_initialize(pDescriptors, NULL, 0); /* Multiple settings for interfaces not supported */
	cdcd_serial_initialize(CDCDSerialDriver_CC_INTERFACE);

	/* Initialize the USB driver */
	usbd_init();
}

/**
 * Invoked whenever the active configuration of device is changed by the
 * host.
 * \param cfgnum Configuration number.
 */
void cdcd_serial_driver_configuration_changed_handler(uint8_t cfgnum)
{
	USBConfigurationDescriptor *desc;
	if (cfgnum) {
		desc = usbd_driver_get_cfg_descriptors(cfgnum);
		cdcd_serial_configure_function((USBGenericDescriptor*)desc,
				desc->wTotalLength);
	}
}

/**
 * Handles CDC-specific SETUP requests. Should be called from a
 * re-implementation of usbd_callbacks_request_received() method.
 * \param request Pointer to a USBGenericRequest instance.
 */
void cdcd_serial_driver_request_handler(const USBGenericRequest *request)
{
	LIBUSB_TRACE("NewReq ");
	if (cdcd_serial_request_handler(request))
		usbd_driver_request_handler(request);
}

/**@}*/

