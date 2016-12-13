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

/** \addtogroup usbd_composite_cdcaud
 *@{
 */
/*---------------------------------------------------------------------------
 *      Headers
 *---------------------------------------------------------------------------*/

#include "trace.h"

#include "usb/device/audio/audd_function.h"
#include "usb/device/cdc/cdcd_serial.h"
#include "usb/device/composite/cdc_audd_driver.h"

/*---------------------------------------------------------------------------
 *         Defines
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 *         Types
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 *         Internal variables
 *---------------------------------------------------------------------------*/

/** Array for storing the current setting of each interface */
static uint8_t b_alt_interfaces[CDCAUDDDriverDescriptors_MaxNumInterfaces];

/*---------------------------------------------------------------------------
 *         Internal functions
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 *         Exported functions
 *---------------------------------------------------------------------------*/

/**
 * Initializes the USB device composite device driver.
 */
void cdc_audd_driver_initialize(const USBDDriverDescriptors *descriptors)
{
	/* Initialize the standard USB driver */
	usbd_driver_initialize(descriptors, b_alt_interfaces, sizeof(b_alt_interfaces));

	/* CDC */
	cdcd_serial_initialize(CDCAUDDDriverDescriptors_CDC_INTERFACE);

	/* Audio */
	audd_function_initialize(CDCAUDDDriverDescriptors_AUD_INTERFACE);

	/* Initialize the USB driver */
	usbd_init();
}

/**
 * Invoked whenever the configuration value of a device is changed by the host
 * \param cfgnum Configuration number.
 */
void cdc_audd_driver_configuration_changed_handler(uint8_t cfgnum)
{
	USBConfigurationDescriptor *desc;
	if (cfgnum > 0) {
		desc = usbd_driver_get_cfg_descriptors(cfgnum);

		/* CDC */
		cdcd_serial_configure_function((USBGenericDescriptor*)desc,
				desc->wTotalLength);

		/* AUD */
		audd_function_configure((USBGenericDescriptor*)desc,
				desc->wTotalLength);
	}
}

/**
 * Invoked whenever the active setting of an interface is changed by the
 * host. Changes the status of the third LED accordingly.
 * \param interface Interface number.
 * \param setting Newly active setting.
 */
void cdc_audd_driver_interface_setting_changed_handler(uint8_t interface,
		uint8_t setting)
{
	audd_function_interface_setting_changed_handler(interface, setting);
}

/**
 * Handles composite-specific USB requests sent by the host, and forwards
 * standard ones to the USB device driver.
 * \param request Pointer to a USBGenericRequest instance.
 */
void cdc_audd_driver_request_handler(const USBGenericRequest *request)
{
	LIBUSB_TRACE("NewReq ");

	if (cdcd_serial_request_handler(request) == USBRC_SUCCESS)
		return;

	if (audd_function_request_handler(request) == USBRC_SUCCESS)
		return;

	usbd_driver_request_handler(request);
}

/**@}*/

