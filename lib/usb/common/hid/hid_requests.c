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
	Title: HIDReportRequest implementation

	About: Purpose
		Implementation of the HIDReportRequest methods.
*/

/**\addtogroup usb_hid
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "usb/common/hid/hid_requests.h"

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

/**
 * Indicates the type of report targeted by a SET_REPORT or GET_REPORT
 * request.
 * \param request Pointer to a USBGenericRequest instance.
 * \return Requested report type (see "HID Report Types").
 */
uint8_t hid_report_request_get_report_type(const USBGenericRequest *request)
{
	return (usb_generic_request_get_value(request) >> 8) & 0xff;
}

/**
 * Indicates the ID of the report targeted by a SET_REPORT or GET_REPORT
 * request. This value should be 0 if report IDs are not used.
 * \param request Pointer to a USBGenericRequest instance.
 * \return Requested report ID.
 */
uint8_t hid_report_request_get_report_id(const USBGenericRequest *request)
{
	return usb_generic_request_get_value(request) & 0xff;
}

/**
 * Indicates the ID of the report targeted by a SET_IDLE or GET_IDLE
 * request. This value should be 0 if report IDs are not used.
 * \param request Pointer to a USBGenericRequest instance.
 * \return Requested report ID.
 */
uint8_t hid_idle_request_get_report_id(const USBGenericRequest *request)
{
	return usb_generic_request_get_value(request) & 0xff;
}

/**
 * Retrieves the Idle rate (in milliseconds) indicated by a SET_IDLE
 * request.
 * \param request Pointer to a USBGenericRequest instance.
 * \return New idle rate for the report.
 */
uint8_t hid_idle_request_get_idle_rate(const USBGenericRequest *request)
{
	return (usb_generic_request_get_value(request) >> 8) & 0xff;
}

/**@}*/
