/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2019, Atmel Corporation
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
 * \addtogroup usbd_printer
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "trace.h"
#include "mm/cache.h"
#include "usb/device/usbd.h"
#include "usb/device/printer/printer_driver.h"

#include <string.h>

/*------------------------------------------------------------------------------
 *         Internal variables
 *------------------------------------------------------------------------------*/
static uint8_t* device_id_string;
static uint8_t device_id_string_len;
static printer_instance prnInstance;

/*------------------------------------------------------------------------------
 *         Internal functions
 *------------------------------------------------------------------------------*/

/**
 * Parse descriptors: Bulk EP IN/OUT.
 * \param desc Pointer to current processed descriptor.
 * \param arg  Pointer to data extention struct for parsing.
 */
static uint8_t printer_function_parse(USBGenericDescriptor* desc, printer_instance* arg)
{
	/* Not a valid descriptor */
	if (desc->bLength == 0) {
		return USBD_STATUS_INVALID_PARAMETER;
	}

	/* Start parse endpoints */
	if (desc->bDescriptorType == USBGenericDescriptor_ENDPOINT) {
		USBEndpointDescriptor *pEP = (USBEndpointDescriptor*)desc;
		if (pEP->bmAttributes == USBEndpointDescriptor_BULK) {
			if (pEP->bEndpointAddress & 0x80)
				arg->bPipeIn = pEP->bEndpointAddress & 0x7F;
			else
				arg->bPipeOut = pEP->bEndpointAddress;
		}
	}
	return 0;
}

void printer_driver_request_handler(const USBGenericRequest *request)
{
	uint32_t req_type = usb_generic_request_get_type(request);
	uint32_t bReq = request->bRequest;
	uint8_t portStatus;

	LIBUSB_TRACE("Printer req ");

	if( req_type & USB_PRINTER_REQUEST_CLASS_SPECIFIC ) {
		/* Handle requests */
		switch (bReq) {
		case USB_PRINTER_GET_DEVICE_ID:
			/* Return the device ID string that is compatible with IEEE 1284. */
			usbd_write(0, device_id_string, device_id_string_len, NULL, NULL);
			break;

		case USB_PRINTER_GET_PORT_STATUS:
			/* First make sure all request parameters are correct as per the Class Definition for
				Printing Devices wValue to be == 0x0000, and wLengh == 1 */
			if((request->wValue != 0) || (request->wLength != 1)) {
				usbd_stall(0);
				return ;
			}
			/* Issue a control send request to send this request to the host. */
			printet_driver_get_port_status(&portStatus);
			usbd_write(0, &portStatus, 1, NULL, NULL);
			break;

		case USB_PRINTER_SOFT_RESET:
			/* First make sure all request parameters are correct */
			if((request->wValue != 0) || (request->wLength != 0)) {
				usbd_stall(0);
				return ;
			}
			/* Cancel all the IRPs */
			usbd_write(0, 0, 0, NULL, NULL);
			break;

		default:
			/* Stall other requests. */
			usbd_stall(0);
			break;
		}
	} else {
		/* STD requests */
		usbd_driver_request_handler(request);
		return;
	}
}

/**
 * Invoked when the configuration of the device changes. Resets the usb printer driver.
 * \param  cfgnum  New configuration number.
 */
void printer_driver_configuration_change_handler(uint8_t cfgnum)
{
	USBConfigurationDescriptor *desc;
	if (cfgnum) {
		desc = usbd_driver_get_cfg_descriptors(cfgnum);
		usb_generic_descriptor_parse((USBGenericDescriptor*)desc,
									desc->wTotalLength,
									(USBDescriptorParseFunction)printer_function_parse,
									&prnInstance);
	}
}

/*------------------------------------------------------------------------------
 *      Exported functions
 *------------------------------------------------------------------------------*/

/**
 * Initializes the USB printer %device driver.
 * \param p_descriptors Pointer to descriptor list for the printer.
 */
void printer_driver_initialize(const USBDDriverDescriptors *descriptors,
							   uint8_t *id_string,
							   uint8_t length)
{
	device_id_string = id_string;
	device_id_string_len = length;
	/* Initialize USBD Driver instance */
	usbd_driver_initialize(descriptors, NULL, 0);
	usbd_init();
}

uint32_t printer_driver_read(void *data,
							 uint32_t length,
							 usbd_xfer_cb_t callback,
							 void *callback_arg)
{
	if (prnInstance.bPipeOut == 0)
		return USBRC_PARAM_ERR;

	return usbd_read(prnInstance.bPipeOut, data, length, callback, callback_arg);
}

WEAK void printet_driver_get_port_status(uint8_t* status)
{
	*status = *status;
}

/**@}*/

