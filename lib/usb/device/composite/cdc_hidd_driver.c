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

/** \addtogroup usbd_composite_cdchid
 *@{
 */
/*---------------------------------------------------------------------------
 *      Headers
 *---------------------------------------------------------------------------*/

#include "trace.h"

#include "usb/device/cdc/cdcd_serial.h"
#include "usb/device/composite/cdc_hidd_driver.h"
#include "usb/device/hid/hidd_keyboard.h"

/*---------------------------------------------------------------------------
 *         Defines
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 *         Types
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 *         Internal variables
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 *         Internal functions
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 *         Exported functions
 *---------------------------------------------------------------------------*/

/**
 * Initializes the USB device composite device driver.
 */
void cdc_hidd_driver_initialize(const USBDDriverDescriptors *descriptors)
{
	/* Initialize the standard USB driver */
	usbd_driver_initialize(descriptors, NULL, 0);

	/* CDC */
	cdcd_serial_initialize(CDCHIDDDriverDescriptors_CDC_INTERFACE);

	/* HID */
	hidd_keyboard_initialize(CDCHIDDDriverDescriptors_HID_INTERFACE);

	/* Initialize the USB driver */
	usbd_init();
}

/**
 * Invoked whenever the configuration value of a device is changed by the host
 * \param cfgnum Configuration number.
 */
void cdc_hidd_driver_configuration_changed_handler(uint8_t cfgnum)
{
	USBConfigurationDescriptor *desc;
	if (cfgnum > 0) {
		desc = usbd_driver_get_cfg_descriptors(cfgnum);

		/* CDC */
		cdcd_serial_configure_function((USBGenericDescriptor*)desc,
				desc->wTotalLength);

		/* HID */
		hidd_keyboard_configure_function((USBGenericDescriptor*)desc,
				desc->wTotalLength);
	}
}

/**
 * Handles composite-specific USB requests sent by the host, and forwards
 * standard ones to the USB device driver.
 * \param request Pointer to a USBGenericRequest instance.
 */
void cdc_hidd_driver_request_handler(const USBGenericRequest *request)
{
	LIBUSB_TRACE("NewReq ");

	if (cdcd_serial_request_handler(request) == USBRC_SUCCESS)
		return;

	if (hidd_keyboard_request_handler(request) == USBRC_SUCCESS)
		return;

	usbd_driver_request_handler(request);
}

/**
 * Starts a remote wake-up sequence if the host has explicitely enabled it
 * by sending the appropriate SET_FEATURE request.
 */
void cdc_hidd_driver_remote_wakeup(void)
{
	/* Remote wake-up has been enabled */
	if (usbd_driver_is_remote_wakeup_enabled()) {
		usbd_remote_wakeup();
	}
}

/**@}*/
