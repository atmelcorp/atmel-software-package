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
 *  \section Purpose
 *
 *    Implements for USB requests described by the USB specification.
 */

/** \addtogroup usb_request
 * @{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "usb/common/usb_requests.h"

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

/**
 * Returns the type of the given request.
 * \param request Pointer to a USBGenericRequest instance.
 * \return "USB Request Types"
 */
extern uint8_t usb_generic_request_get_type(const USBGenericRequest *request)
{
	return (request->bmRequestType >> 5) & 0x3;
}

/**
 * Returns the request code of the given request.
 * \param request Pointer to a USBGenericRequest instance.
 * \return Request code.
 * \sa "USB Request Codes"
 */
uint8_t usb_generic_request_get_request(const USBGenericRequest *request)
{
	return request->bRequest;
}

/**
 * Returns the wValue field of the given request.
 * \param request - Pointer to a USBGenericRequest instance.
 * \return Request value.
 */
uint16_t usb_generic_request_get_value(const USBGenericRequest *request)
{
	return request->wValue;
}

/**
 * Returns the wIndex field of the given request.
 * \param request Pointer to a USBGenericRequest instance.
 * \return Request index;
 */
uint16_t usb_generic_request_get_index(const USBGenericRequest *request)
{
	return request->wIndex;
}

/**
 * Returns the expected length of the data phase following a request.
 * \param request Pointer to a USBGenericRequest instance.
 * \return Length of data phase.
 */
uint16_t usb_generic_request_get_length(const USBGenericRequest *request)
{
	return request->wLength;
}

/**
 * Returns the endpoint number targeted by a given request.
 * \param request Pointer to a USBGenericRequest instance.
 * \return Endpoint number.
 */
uint8_t usb_generic_request_get_endpoint_number(
	const USBGenericRequest *request)
{
	return usb_generic_request_get_index(request) & 0xf;
}

/**
 * Returns the intended recipient of a given request.
 * \param request Pointer to a USBGenericRequest instance.
 * \return Request recipient.
 * \sa "USB Request Recipients"
 */
uint8_t usb_generic_request_get_recipient(const USBGenericRequest *request)
{
	/* Recipient is in bits [0..4] of the bmRequestType field */
	return request->bmRequestType & 0xf;
}

/**
 * Returns the direction of the data transfer following the given request.
 * \param request Pointer to a USBGenericRequest instance.
 * \return Transfer direction.
 * \sa "USB Request Directions"
 */
uint8_t usb_generic_request_get_direction(const USBGenericRequest *request)
{
	/* Transfer direction is located in bit D7 of the bmRequestType field */
	if ((request->bmRequestType & 0x80) != 0) {
		return USBGenericRequest_IN;
	}
	else {
		return USBGenericRequest_OUT;
	}
}


/**
 * Returns the type of the descriptor requested by the host given the
 * corresponding GET_DESCRIPTOR request.
 * \param request Pointer to a USBGenericDescriptor instance.
 * \return Type of the requested descriptor.
 */
uint8_t usb_get_descriptor_request_get_descriptor_type(
	const USBGenericRequest *request)
{
	/* Requested descriptor type is in the high-byte of the wValue field */
	return (usb_generic_request_get_value(request) >> 8) & 0xff;
}

/**
 * Returns the index of the requested descriptor, given the corresponding
 * GET_DESCRIPTOR request.
 * \param request Pointer to a USBGenericDescriptor instance.
 * \return Index of the requested descriptor.
 */
uint8_t usb_get_descriptor_request_get_descriptor_index(
	const USBGenericRequest *request)
{
	/* Requested descriptor index if in the low byte of the wValue field */
	return usb_generic_request_get_value(request) & 0xff;
}


/**
 * Returns the address that the device must take in response to a
 * SET_ADDRESS request.
 * \param request Pointer to a USBGenericRequest instance.
 * \return New device address.
 */
uint8_t usb_set_address_request_get_address(const USBGenericRequest *request)
{
	return usb_generic_request_get_value(request) & 0x7f;
}


/**
 * Returns the number of the configuration that should be set in response
 * to the given SET_CONFIGURATION request.
 * \param request Pointer to a USBGenericRequest instance.
 * \return Number of the requested configuration.
 */
uint8_t usb_set_configuration_request_get_configuration(
	const USBGenericRequest *request)
{
	return usb_generic_request_get_value(request);
}


/**
 * Indicates which interface is targeted by a GET_INTERFACE or
 * SET_INTERFACE request.
 * \param request Pointer to a USBGenericRequest instance.
 * \return Interface number.
 */
uint8_t usb_interface_request_get_interface(const USBGenericRequest *request)
{
	return usb_generic_request_get_index(request) & 0xff;
}

/**
 * Indicates the new alternate setting that the interface targeted by a
 * SET_INTERFACE request should use.
 * \param request Pointer to a USBGenericRequest instance.
 * \return New active setting for the interface.
 */
uint8_t usb_interface_request_get_alternate_setting(
	const USBGenericRequest *request)
{
	return usb_generic_request_get_value(request) & 0xff;
}


/**
 *  Returns the feature selector of a given CLEAR_FEATURE or SET_FEATURE
 *  request.
 *  \param request Pointer to a USBGenericRequest instance.
 *  \return Feature selector.
 */
uint8_t usb_feature_request_get_feature_selector(
	const USBGenericRequest *request)
{
	return usb_generic_request_get_value(request);
}

/**
 *  Indicates the test that the device must undertake following a
 *  SET_FEATURE request.
 *  \param request Pointer to a USBGenericRequest instance.
 *  \return Test selector.
 */
uint8_t usb_feature_request_get_test_selector(
	const USBGenericRequest *request)
{
	return (usb_generic_request_get_index(request) >> 8) & 0xff;
}

/**@}*/
