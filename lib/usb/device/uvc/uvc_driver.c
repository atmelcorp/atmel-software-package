/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
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

/*------------------------------------------------------------------------------
 *      Includes
 *------------------------------------------------------------------------------*/

#include "trace.h"

#include "usb/device/usbd_driver.h"
#include "usb/device/usbd_hal.h"
#include "usb/device/uvc/uvc_driver.h"
#include "usb/device/uvc/uvc_function.h"


/*-----------------------------------------------------------------------------
 *         Internal variables
 *-----------------------------------------------------------------------------*/

/** Static instance of the UVC device driver. */
static struct _uvc_driver uvc_driver;

/*-----------------------------------------------------------------------------
 *      Exported functions
 *-----------------------------------------------------------------------------*/


void uvc_driver_initialize(const USBDDriverDescriptors *descriptors, uint32_t buff_addr, uint8_t multi_buffers)
{
	uvc_driver.frm_offset = 0;
	uvc_driver.is_frame_xfring = 0;
	uvc_driver.buf_start_addr = buff_addr;
	uvc_driver.multi_buffers = multi_buffers;

	/* Initialize USBD Driver instance */
	usbd_driver_initialize(descriptors, uvc_driver.alternate_interfaces, sizeof(uvc_driver.alternate_interfaces));

	/* Function instance initialize */
	uvc_function_initialize(&uvc_driver);

	/* Initialize the USB driver */
	usbd_init();
}

/**
 * Handler for incoming SETUP requests on default Control endpoint 0.
 *
 * Standard requests are forwarded to the usbd_driver_request_handler
 * method.
 * \param  pUvcDriver  Pointer to UVCDriver instance.
 * \param  request Pointer to a USBGenericRequest instance
 */
void uvc_driver_request_handler(const USBGenericRequest *request)
{
	LIBUSB_TRACE("NewReq ");
	/* STD requests */
	if (usb_generic_request_get_type(request) != USBGenericRequest_CLASS) {
		usbd_driver_request_handler(request);
		return;
	}

	/* Video requests */
	trace_info_wp("Vid ");

	switch (usb_generic_request_get_request(request)) {
	case VIDGenericRequest_SETCUR:
		uvc_function_set_cur(request);
		break;
	case VIDGenericRequest_GETCUR:
		uvc_function_get_cur(request);
		break;
	case VIDGenericRequest_GETDEF:
		uvc_function_get_def(request);
		break;
	case VIDGenericRequest_GETINFO:
		uvc_function_get_info(request);
		break;
	case VIDGenericRequest_GETMIN:
		uvc_function_get_min(request);
		break;
	case VIDGenericRequest_GETMAX:
		uvc_function_get_max(request);
		break;
	case VIDGenericRequest_GETRES:
		uvc_function_get_res(request);
		break;
	default:
		trace_info_wp("REQ: %x %x %x %x\n\r",
			usb_generic_request_get_type(request),
			usb_generic_request_get_request(request),
			usb_generic_request_get_value(request),
			usb_generic_request_get_length(request));
		usbd_stall(0);
	}
	trace_info_wp("\n\r");
}

void uvc_driver_interface_setting_changed_handler(uint8_t interface,
		uint8_t setting)
{
	if (interface != VIDCAMD_StreamInterfaceNum)
		return;

	if (setting) {
		uvc_driver.is_video_on = 1;
		uvc_driver.frm_count = 0;
		uvc_driver.frm_offset = 0;
	} else {
		uvc_driver.is_video_on = 0;
		uvc_driver.is_frame_xfring = 0;
	}

	usbd_hal_reset_endpoints(1 << VIDCAMD_IsoInEndpointNum, USBRC_CANCELED, 1);
}

/**@}*/
