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
 */

/** \addtogroup usbd_composite_hidmsd
 *@{
 */

/*---------------------------------------------------------------------------
 *      Headers
 *---------------------------------------------------------------------------*/

#include "trace.h"

#include "usb/device/composite/hid_msd_driver.h"
#include "usb/device/hid/hidd_keyboard.h"
#include "usb/device/msd/msd_function.h"

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
 * Initializes the USB device HIDMSD device driver.
 */
void hid_msdd_driver_initialize(const USBDDriverDescriptors *descriptors,
	MSDLun *luns, uint8_t num_luns)
{
	/* Initialize the standard USB driver */
	usbd_driver_initialize(descriptors, NULL, 0);

	/* HID */
	hidd_keyboard_initialize(HIDMSDDriverDescriptors_HID_INTERFACE);

	/* MSD */
	msd_function_initialize(HIDMSDDriverDescriptors_MSD_INTERFACE,
			luns, num_luns);

	/* Initialize the USB driver */
	usbd_init();
}

/**
 * Invoked whenever the configuration value of a device is changed by the host
 * \param cfgnum Configuration number.
 */
void hid_msdd_driver_configuration_changed_handler(uint8_t cfgnum)
{
	USBConfigurationDescriptor *desc;
	if (cfgnum > 0) {
		desc = usbd_driver_get_cfg_descriptors(cfgnum);

		/* HID */
		hidd_keyboard_configure_function((USBGenericDescriptor*)desc,
				desc->wTotalLength);

		/* MSD */
		msd_function_configure((USBGenericDescriptor*)desc,
				desc->wTotalLength);
	}
}

/**
 * Handles HIDMSD-specific USB requests sent by the host, and forwards
 * standard ones to the USB device driver.
 * \param request Pointer to a USBGenericRequest instance.
 */
void hid_msdd_driver_request_handler(const USBGenericRequest *request)
{
	LIBUSB_TRACE("NewReq ");

	if (msd_function_request_handler(request) == USBRC_SUCCESS)
		return;

	if (hidd_keyboard_request_handler(request) == USBRC_SUCCESS)
		return;

	usbd_driver_request_handler(request);
}

/**
 * Starts a remote wake-up sequence if the host has explicitely enabled it
 * by sending the appropriate SET_FEATURE request.
 */
void hid_msdd_driver_remote_wakeup(void)
{
	/* Remote wake-up has been enabled */
	if (usbd_driver_is_remote_wakeup_enabled()) {
		usbd_remote_wakeup();
	}
	/* Remote wake-up NOT enabled */
	else {
		trace_warning("HIDMSDDDriver_RemoteWakeUp: not enabled\n\r");
	}
}
/**@}*/

