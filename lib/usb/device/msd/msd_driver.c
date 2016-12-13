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
 *  \addtogroup usbd_msd
 *@{
 *  Implement a single interface device with single MS function in.
 */

/*------------------------------------------------------------------------------
 *      Includes
 *------------------------------------------------------------------------------*/

#include "trace.h"

#include "usb/device/msd/msd_driver.h"
#include "usb/device/msd/msd_function.h"
#include "usb/device/usbd_driver.h"

/*-----------------------------------------------------------------------------
 *         Internal variables
 *-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 *      Internal functions
 *-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 *      Exported functions
 *-----------------------------------------------------------------------------*/

/**
 * Initializes the MSD driver and the associated USB driver.
 * \param  p_descriptors Pointer to Descriptors list for MSD Device.
 * \param  p_luns        Pointer to a list of LUNs
 * \param  num_luns      Number of LUN in list
 * \see MSDLun
 */
void msd_driver_initialize(const USBDDriverDescriptors *descriptors,
		MSDLun *luns, unsigned char num_luns)
{
	usbd_driver_initialize(descriptors, NULL, 0);
	msd_function_initialize(0, luns, num_luns);
	usbd_init();
}

/**
 * Invoked when the configuration of the device changes. Resets the mass
 * storage driver.
 * \param  pMsdDriver  Pointer to MSDDriver instance.
 * \param  cfgnum      New configuration number.
 */
void msd_driver_configuration_change_handler(uint8_t cfgnum)
{
	USBConfigurationDescriptor *desc;
	if (cfgnum) {
		desc = usbd_driver_get_cfg_descriptors(cfgnum);
		msd_function_configure((USBGenericDescriptor*)desc,
				desc->wTotalLength);
	}
}

/**
 * Handler for incoming SETUP requests on default Control endpoint 0.
 *
 * Standard requests are forwarded to the usbd_driver_request_handler
 * method.
 * \param  pMsdDriver  Pointer to MSDDriver instance.
 * \param  request Pointer to a USBGenericRequest instance
 */
void msd_driver_request_handler(const USBGenericRequest *request)
{
	LIBUSB_TRACE("NewReq ");
	if (msd_function_request_handler(request)) {
		usbd_driver_request_handler(request);
	}
}

/**@}*/

