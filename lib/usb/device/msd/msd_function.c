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
 *  Implements Mass storage Function for USB device.
 */

/*------------------------------------------------------------------------------
 *      Includes
 *------------------------------------------------------------------------------*/

#include "trace.h"
#include "chip.h"
#include "compiler.h"

#include "mm/cache.h"

#include "usb/common/msd/msd_descriptors.h"
#include "usb/device/msd/msd_driver.h"
#include "usb/device/usbd_driver.h"
#include "usb/device/usbd.h"

#include <assert.h>
#include <string.h>

/*-----------------------------------------------------------------------------
 *         Internal Types
 *-----------------------------------------------------------------------------*/

/** Parse data extension */
typedef struct _MSDParseData {
	/** Pointer to driver instance */
	MSDDriver *p_msdd;
	/** Pointer to currently processed interface descriptor */
	USBInterfaceDescriptor *p_if;
} MSDParseData;


/*-----------------------------------------------------------------------------
 *         Internal variables
 *-----------------------------------------------------------------------------*/

/**
 * MSD Driver instance for device function
 * Contains a MSCbw buffer that will receive data transferred from the device by
 * the DMA. As the L1 data cache won't notice when RAM contents is altered, the
 * driver will invalidate any matching cache lines.
 * May this buffer fail to be aligned on cache lines, cached changes to adjacent
 * data would be lost at the time the dirty and shared cache lines were
 * invalidated.
 */
CACHE_ALIGNED static MSDDriver msd_function;

/*-----------------------------------------------------------------------------
 *      Internal functions
 *-----------------------------------------------------------------------------*/

/**
 * Parse descriptors: Bulk EP IN/OUT.
 * \param desc Pointer to current processed descriptor.
 * \param arg  Pointer to data extention struct for parsing.
 */
static uint8_t msd_function_parse(USBGenericDescriptor* desc, MSDParseData* arg)
{
	MSDDriver *p_msdd = arg->p_msdd;
	USBInterfaceDescriptor *p_if;

	/* Not a valid descriptor */
	if (desc->bLength == 0) {
		return USBD_STATUS_INVALID_PARAMETER;
	}
	/* Find interface descriptor */
	if (desc->bDescriptorType == USBGenericDescriptor_INTERFACE) {
		p_if = (USBInterfaceDescriptor*)desc;
		if (p_if->bInterfaceClass == MSInterfaceDescriptor_CLASS) {
			/* First found IF */
			if (p_msdd->interfaceNb == 0xFF) {
				p_msdd->interfaceNb = p_if->bInterfaceNumber;
				arg->p_if = p_if;
			}
			/* Specific IF */
			else if (p_msdd->interfaceNb == p_if->bInterfaceNumber) {
				arg->p_if = p_if;
			}
		}
	}
	/* Start parse endpoints */
	if (arg->p_if) {
		if (desc->bDescriptorType == USBGenericDescriptor_ENDPOINT) {
			USBEndpointDescriptor *pEP = (USBEndpointDescriptor*)desc;
			if (pEP->bmAttributes == USBEndpointDescriptor_BULK) {
				if (pEP->bEndpointAddress & 0x80)
					p_msdd->commandState.pipeIN = pEP->bEndpointAddress & 0x7F;
				else
					p_msdd->commandState.pipeOUT = pEP->bEndpointAddress;
			}
		}

		/* Finish when found all pipes */
		if (p_msdd->commandState.pipeIN != 0
			&& p_msdd->commandState.pipeOUT != 0) {
			return USBRC_FINISHED;
		}
	}
	return 0;
}

/**
 * Resets the state of the MSD driver
 */
static void msd_function_reset(void)
{
	MSDDriver *p_msdd = &msd_function;

	LIBUSB_TRACE("MSDReset ");

	p_msdd->state = MSDD_STATE_READ_CBW;
	p_msdd->waitResetRecovery = 0;
	p_msdd->commandState.state = 0;
}

/*-----------------------------------------------------------------------------
 *      Exported functions
 *-----------------------------------------------------------------------------*/

/**
 * Initializes the MSD driver and the associated USB driver.
 * \param  bInterfaceNb Interface number for the function.
 * \param  pLuns        Pointer to a list of LUNs
 * \param  numLuns      Number of LUN in list
 * \see MSDLun
 */
void msd_function_initialize(uint8_t bInterfaceNb,
	MSDLun *p_luns, uint8_t numLuns)
{
	MSDDriver *p_msd_driver = &msd_function;
#ifndef NDEBUG
	uint8_t lun_ix;
#endif

	LIBUSB_TRACE("MSDFunInit ");

	memset(&msd_function, 0, sizeof msd_function);

	/* Verify that all fields that may receive data from the DMA are aligned
	 * on data cache lines.
	 * It is assumed that, in MSDCommandState struct, next to cbw is csw. */
	assert((uint32_t)&p_msd_driver->commandState.cbw % L1_CACHE_BYTES == 0
	    && (uint32_t)&p_msd_driver->commandState.csw
	    >= (uint32_t)&p_msd_driver->commandState.cbw + ROUND_UP_MULT(
	    sizeof(p_msd_driver->commandState.cbw), L1_CACHE_BYTES));
#ifndef NDEBUG
	for (lun_ix = 0; lun_ix < numLuns; lun_ix++)
		assert((uint32_t)p_luns[lun_ix].ioFifo.pBuffer
		    % L1_CACHE_BYTES == 0
		    && p_luns[lun_ix].ioFifo.bufferSize % L1_CACHE_BYTES == 0);
#endif

	/* Driver instance */
	p_msd_driver->interfaceNb = bInterfaceNb;

	/* Command state initialization */
	p_msd_driver->commandState.state = 0;
	p_msd_driver->commandState.postprocess = 0;
	p_msd_driver->commandState.length = 0;
	p_msd_driver->commandState.transfer.semaphore = 0;

	/* LUNs */
	p_msd_driver->luns = p_luns;
	p_msd_driver->maxLun = (uint8_t) (numLuns - 1);

	/* Reset BOT driver */
	msd_function_reset();
}

/**
 * Invoked when the configuration of the device changes.
 * Pass endpoints and resets the mass storage function.
 * \p_descriptors Pointer to the descriptors for function configure.
 * \length      Length of descriptors in number of bytes.
 */
void msd_function_configure(USBGenericDescriptor *p_descriptors,
						   uint16_t length)
{
	MSDDriver *p_msd_driver = &msd_function;
	MSDParseData parse_data;

	LIBUSB_TRACE("MSDFunCfg ");

	p_msd_driver->state = MSDD_STATE_READ_CBW;
	p_msd_driver->waitResetRecovery = 0;
	p_msd_driver->commandState.state = 0;

	parse_data.p_if = 0;
	parse_data.p_msdd = p_msd_driver;
	usb_generic_descriptor_parse((USBGenericDescriptor*)p_descriptors, length,
				(USBDescriptorParseFunction)msd_function_parse, &parse_data);

	msd_function_reset();
}

/**
 * Handler for incoming SETUP requests on default Control endpoint 0.
 *
 * Standard requests are forwarded to the usbd_driver_request_handler
 * method.
 * \param  p_msd_driver  Pointer to MSDDriver instance.
 * \param  request Pointer to a USBGenericRequest instance
 */
uint32_t msd_function_request_handler(
	const USBGenericRequest *request)
{
	MSDDriver *p_msd_driver = &msd_function;
	uint32_t req_code = (usb_generic_request_get_type(request) << 8)
					 | (usb_generic_request_get_request(request));

	LIBUSB_TRACE("Msdf ");

	/* Handle requests */
	switch (req_code) {
	/*--------------------- */
	case USBGenericRequest_CLEARFEATURE:
	/*--------------------- */
		LIBUSB_TRACE("ClrFeat ");

		switch (usb_feature_request_get_feature_selector(request)) {

		/*--------------------- */
		case USBFeatureRequest_ENDPOINTHALT:
		/*--------------------- */
			LIBUSB_TRACE("Hlt ");

			/* Do not clear the endpoint halt status if the device is waiting */
			/* for a reset recovery sequence */
			if (!p_msd_driver->waitResetRecovery) {

				/* Forward the request to the standard handler */
				usbd_driver_request_handler(request);
			}
			else {

				LIBUSB_TRACE("No ");
				usbd_write(0, 0, 0, 0, 0);
			}


			return USBRC_SUCCESS; /* Handled */

		}
		break;

	/*------------------- */
	case (USBGenericRequest_CLASS<<8)|MSD_GET_MAX_LUN:
	/*------------------- */
		LIBUSB_TRACE("gMaxLun ");

		/* Check request parameters */
		if ((request->wValue == 0)
			&& (request->wIndex == p_msd_driver->interfaceNb)
			&& (request->wLength == 1)) {

			usbd_write(0, &(p_msd_driver->maxLun), 1, 0, 0);

		}
		else {

			trace_warning("msd_driver_request_handler: GetMaxLUN(%d,%d,%d)\n\r",
				request->wValue, request->wIndex, request->wLength);
			usbd_stall(0);
		}
		return USBRC_SUCCESS; /* Handled */

	/*----------------------- */
	case (USBGenericRequest_CLASS<<8)|MSD_BULK_ONLY_RESET:
	/*----------------------- */
		LIBUSB_TRACE("Rst ");

		/* Check parameters */
		if ((request->wValue == 0)
			&& (request->wIndex == p_msd_driver->interfaceNb)
			&& (request->wLength == 0)) {

			/* Reset the MSD driver */
			msd_function_reset();
			usbd_write(0, 0, 0, 0, 0);
		}
		else {

			trace_warning("msd_driver_request_handler: Reset(%d,%d,%d)\n\r",
				request->wValue, request->wIndex, request->wLength);
			usbd_stall(0);
		}
		return USBRC_SUCCESS; /* Handled */
	}

	return USBRC_PARAM_ERR;
}

/**
 * State machine for the MSD driver
 */
void msd_function_state_machine(void)
{
	if (usbd_get_state() < USBD_STATE_CONFIGURED){}
	else msdd_state_machine(&msd_function);

}

/**@}*/

