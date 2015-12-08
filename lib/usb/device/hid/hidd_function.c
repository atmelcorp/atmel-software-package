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
 *  Implementation of the HIDDFunction class methods.
 */
/** \addtogroup usbd_hid
 * @{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "trace.h"

#include "usb/common/usb_descriptors.h"
#include "usb/common/hid/hid_descriptors.h"
#include "usb/device/hid/hidd_function.h"

/*------------------------------------------------------------------------------
 *         Types
 *------------------------------------------------------------------------------*/

/** Parse data extension for HID descriptor */
typedef struct _HIDDParseData {
	HIDDFunction * p_hidd;
	USBInterfaceDescriptor * pIfDesc;
} HIDDParseData;


/*------------------------------------------------------------------------------
 *         Internal functions
 *------------------------------------------------------------------------------*/

/**
 *  Returns the descriptor requested by the host.
 * \param p_hidd   Pointer to HIDDFunction instance
 * \param b_type   Descriptor type.
 * \param length Maximum number of bytes to send.
 * \return USBRC_SUCCESS if the request has been handled by this function,
 *         otherwise USBRC_PARAM_ERR.
 */
static uint32_t hidd_function_get_descriptor(HIDDFunction *p_hidd,
		uint8_t b_type, uint32_t length)
{
	HIDDescriptor1 *hid_descriptor =
		(HIDDescriptor1 *)p_hidd->pHidDescriptor;
	uint16_t descriptor_length;

	LIBUSB_TRACE("gDesc{%x) ", b_type);

	switch (b_type) {
	case HIDGenericDescriptor_REPORT:
		/* Adjust length and send report descriptor */
		descriptor_length = hid_descriptor->bDescriptorLength0[0] +
			(hid_descriptor->bDescriptorLength0[1] << 8);
		if (length > descriptor_length)
			length = descriptor_length;

		LIBUSB_TRACE("Report(%d) ", (unsigned)length);

		usbd_write(0, p_hidd->pReportDescriptor, length, 0, 0);
		break;

	case HIDGenericDescriptor_HID:
		/* Adjust length and send HID descriptor */
		if (length > sizeof(HIDDescriptor1))
			length = sizeof(HIDDescriptor1);

		LIBUSB_TRACE("HID(%d) ", (unsigned)length);

		usbd_write(0, hid_descriptor, length, 0, 0);
		break;

	default:
		return USBRC_PARAM_ERR;
	}

	return USBRC_SUCCESS;
}

/**
 * Return expected report header pointer.
 * \param p_hidd Pointer to HIDDFunction instance
 * \param type Report type.
 * \param id   Report ID.
 */
static HIDDReport* hidd_function_find_report(const HIDDFunction *p_hidd,
		uint8_t type, uint8_t id)
{
	HIDDReport** report_list;
	int32_t list_size, i;

	switch (type) {
	case HIDReportRequest_INPUT:
		report_list = p_hidd->pInputList;
		list_size = p_hidd->bInputListSize;
		break;
	case HIDReportRequest_OUTPUT:
		report_list = p_hidd->pOutputList;
		list_size = p_hidd->bOutputListSize;
		break;
	/* No other reports supported */
	default:
		trace_warning("Report %x.%x not supported\n\r", type, id);
		return 0;
	}

	/* No list */
	if (report_list == 0)
		return 0;

	/* Find report in the list */
	for (i = 0; i < list_size; i ++) {
		if (report_list[i]->bID == id)
			return report_list[i];
	}

	/* Not found */
	return 0;
}

/**
 * Sends the current Idle rate of the input report to the host.
 * \param p_hidd Pointer to HIDDFunction instance
 * \param id   Report ID
 */
static void hidd_function_get_idle(HIDDFunction *p_hidd, uint8_t id)
{
	HIDDReport *report = hidd_function_find_report(p_hidd,
			HIDReportRequest_INPUT, id);

	LIBUSB_TRACE("gIdle(%x) ", id);

	if (report == 0) {
		usbd_stall(0);
		return;
	}

	usbd_write(0, &report->bIdleRate, 1, 0, 0);
}

/**
 * Retrieves the new idle rate of the input report from the USB host.
 * \param p_hidd     Pointer to HIDDFunction instance
 * \param b_type     Report type
 * \param b_id       Report ID
 * \param b_idle_rate Report idle rate.
 */
static void hidd_function_set_idle(HIDDFunction *p_hidd, uint8_t id, uint8_t idle_rate)
{
	HIDDReport *report = hidd_function_find_report(p_hidd,
			HIDReportRequest_INPUT, id);

	idle_rate = idle_rate;

	LIBUSB_TRACE("sIdle(%x<%x) ", id, idle_rate);

	if (report == 0) {
		usbd_stall(0);
		return;
	}

	usbd_write(0, 0, 0, 0, 0);
}

/**
 * Callback function when GetReport request data sent to host
 * \param arg Pointer to report information.
 * \param status  Result status
 * \param transferred Number of bytes transferred
 * \param remaining Number of bytes that are not transferred yet
 */
static void _get_report_callback(void *arg, uint8_t status,
		uint32_t transferred, uint32_t remaining)
{
	HIDDReport *report = (HIDDReport*)arg;

	report->wTransferred = transferred;
	if (report->fCallback)
		report->fCallback(HIDD_EC_GETREPORT, report->pArg);

	usbd_read(0, 0, 0, 0, 0);
}

/**
 * Sends the requested report to the host.
 * \param p_hidd   Pointer to HIDDFunction instance
 * \param b_type   Report type.
 * \param bID     Report ID.
 * \param length Maximum number of bytes to send.
 */
static void hidd_function_get_report(HIDDFunction *p_hidd,
		uint8_t type, uint8_t id, uint8_t length)
{
	HIDDReport *report = hidd_function_find_report(p_hidd,
			type, id);

	LIBUSB_TRACE("gReport(%x.%x) ", type, id);

	if (report == 0) {
		usbd_stall(0);
		return;
	}

	if (length >= report->wMaxSize) {
		length = report->wMaxSize;
	}

	usbd_write(0, report->bData, length,
			_get_report_callback, report);
}

/**
 * Callback function when GetReport request data sent to host
 * \param arg Pointer to report information.
 * \param status  Result status
 * \param transferred Number of bytes transferred
 * \param remaining Number of bytes that are not transferred yet
 */
static void _set_report_callback(void *arg, uint8_t status,
		uint32_t transferred, uint32_t remaining)
{
	HIDDReport *report = arg;

	report->wTransferred = transferred;
	if (report->fCallback) {
		report->fCallback(HIDD_EC_SETREPORT, report->pArg);
	}
}

/**
 * Reads the requested report from the host.
 * \param p_hidd   Pointer to HIDDFunction instance
 * \param b_type   Report type.
 * \param b_id     Report ID.
 * \param length Maximum number of bytes to read.
 */
static void hidd_function_set_report(HIDDFunction *p_hidd,
		uint8_t type, uint8_t id, uint8_t length)
{
	HIDDReport *report = hidd_function_find_report(p_hidd, type, id);

	LIBUSB_TRACE("sReport(%x.%x) ", type, id);

	if (report == 0) {
		usbd_stall(0);
		return;
	}

	if (length >= report->wMaxSize) {
		length = report->wMaxSize;
	}

	usbd_read(0, report->bData, length,
			_set_report_callback, report);
}

/**
 * Parse descriptors: Interface, Interrupt IN/OUT.
 * \param desc Pointer to descriptor list.
 * \param p_arg  Argument, pointer to HIDDParseData instance.
 */
static uint32_t hidd_function_parse(USBGenericDescriptor *p_desc,
		HIDDParseData *p_arg)
{
	/* Find HID Interface */
	if (p_arg->pIfDesc == 0) {
		if (p_desc->bDescriptorType == USBGenericDescriptor_INTERFACE) {
			USBInterfaceDescriptor *p_if = (USBInterfaceDescriptor*)p_desc;
			/* Right interface for HID:
				   HID Class + at least 1 endpoint */
			if (p_if->bInterfaceClass == HIDInterfaceDescriptor_CLASS
				&& p_if->bNumEndpoints >= 1) {
				/* Obtain new interface setting */
				if (p_arg->p_hidd->bInterface == 0xFF) {
					p_arg->p_hidd->bInterface = p_if->bInterfaceNumber;
					p_arg->pIfDesc = p_if;
				}
				/* Find specific interface setting */
				else if (p_arg->p_hidd->bInterface == p_if->bInterfaceNumber) {
					p_arg->pIfDesc = p_if;
				}
			}
		}
	}
	/* Interface end */
	else {
		/* Start another interface ? */
		if (p_desc->bDescriptorType == USBGenericDescriptor_INTERFACE) {
			/* Terminate the parse */
			return USBRC_PARTIAL_DONE;
		}
		/* Parse HID descriptor */
		else if (p_desc->bDescriptorType == HIDGenericDescriptor_HID) {
			p_arg->p_hidd->pHidDescriptor = (HIDDescriptor*)p_desc;
		}
		/* Parse endpoints */
		else if (p_desc->bDescriptorType == USBGenericDescriptor_ENDPOINT) {
			USBEndpointDescriptor *p_ep = (USBEndpointDescriptor*)p_desc;
			if (p_ep->bEndpointAddress & 0x80) {
				p_arg->p_hidd->bPipeIN = p_ep->bEndpointAddress & 0x7F;
			} else {
				p_arg->p_hidd->bPipeOUT = p_ep->bEndpointAddress;
			}
		}

		/* Check if all data is OK */
		if (p_arg->p_hidd->bInterface  != 0xFF
			&& p_arg->p_hidd->bPipeIN  != 0xFF
			&& p_arg->p_hidd->bPipeOUT != 0xFF)
			return USBRC_FINISHED;
	}
	return 0;
}

/**
 * Callback function when interrupt OUT data received from host
 * \param arg  Pointer to HIDDFunction instance
 * \param status Result status
 * \param transferred Number of bytes transferred
 * \param remaining Number of bytes that are not transferred yet
 */
static void hidd_function_report_received(void *arg, uint8_t status,
		uint32_t transferred, uint32_t remaining)
{
	HIDDFunction *p_hidd = (HIDDFunction *)arg;
	HIDDReport *p_out = p_hidd->pOutputList[p_hidd->bCurrOutput];
	remaining = remaining;
	if (status != USBRC_SUCCESS) {

		trace_error("HIDDFun::ReadReport: %x\n\r", status);
		return;
	}

	/* Transfered information */
	p_out->wTransferred = transferred;

	/* Data Change callback */
	if (p_out->fCallback)
		p_out->fCallback(HIDD_EC_REPORTCHANGED, p_out->pArg);

	/* Proceed to next output report */
	p_hidd->bCurrOutput ++;
	if (p_hidd->bCurrOutput >= p_hidd->bOutputListSize)
		p_hidd->bCurrOutput = 0;

	/* Start reading a report */
	usbd_read(p_hidd->bPipeOUT,
			  p_hidd->pOutputList[p_hidd->bCurrOutput]->bData,
			  p_hidd->pOutputList[p_hidd->bCurrOutput]->wMaxSize,
			  hidd_function_report_received,
			  (void*)p_hidd);
}

/**
 * Callback function when interrupt IN data sent to host
 * \param arg  Pointer to HIDDFunction instance
 * \param status Result status
 * \param transferred Number of bytes transferred
 * \param remaining Number of bytes that are not transferred yet
 */
static void hidd_function_report_sent(void *arg, uint8_t status,
		uint32_t transferred, uint32_t remaining)
{
	HIDDFunction *p_hidd = (HIDDFunction *)arg;
	HIDDReport *p_in = p_hidd->pInputList[p_hidd->bCurrInput];
	remaining = remaining;
	if (status != USBRC_SUCCESS) {

		trace_error("HIDDFun::WriteReport: %x\n\r", status);
		return;
	}

	/* Transfered information */
	p_in->wTransferred = transferred;

	/* Report Sent Callback */
	if (p_in->fCallback)
		p_in->fCallback(HIDD_EC_REPORTSENT, p_in->pArg);

	/* Proceed to next output report */
	p_hidd->bCurrInput ++;
	if (p_hidd->bCurrInput >= p_hidd->bInputListSize)
		p_hidd->bCurrInput = 0;

	/* Start writing a report */
	usbd_write(p_hidd->bPipeIN,
			   p_hidd->pInputList[p_hidd->bCurrInput]->bData,
			   p_hidd->pInputList[p_hidd->bCurrInput]->wMaxSize,
			  hidd_function_report_received,
			  p_hidd);
}


/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

/**
 * Initialize the USB Device HID function, for general HID device support.
 * \param p_hidd             Pointer to HIDDFunction instance.
 * \param interface_nb      Interface number,
 *                          can be 0xFF to obtain from descriptors.
 * \param report_descriptor Pointer to report descriptor.
 * \param input_list        Pointer to an HID input report list
 * \param input_list_size    HID input report list size
 * \param output_list       Pointer to an HID output report list
 * \param output_list_size   HID output report list size
 */
void hidd_function_initialize(HIDDFunction *p_hidd, uint8_t interface_nb,
		const uint8_t *report_descriptor,
		HIDDReport* input_list[], uint8_t input_list_size,
		HIDDReport* output_list[], uint8_t output_list_size)
{
	LIBUSB_TRACE("hidd_function_initialize ");

	p_hidd->pReportDescriptor = (uint8_t*)report_descriptor;
	p_hidd->pHidDescriptor = 0;
	p_hidd->bInterface = interface_nb;
	p_hidd->bPipeIN    = 0xFF;
	p_hidd->bPipeOUT   = 0xFF;
	p_hidd->bProtocol  = HIDProtocol_REPORT;    /* Non-boot protocol */
	p_hidd->pInputList = input_list;
	p_hidd->pOutputList = output_list;
	p_hidd->bInputListSize = input_list_size;
	p_hidd->bOutputListSize = output_list_size;
	p_hidd->bCurrInput = 0;
	p_hidd->bCurrOutput = 0;
}

/**
 * Parse the USB HID Function Interface.
 * Only first interface and its endpoints parsed.
 * \param p_hidd Pointer to HIDDFunction instance.
 * \param descriptors Pointer to descriptor list.
 * \param length     Descriptor list block length in bytes.
 * \return Pointer to next descriptor. 0 means no other descriptor.
 */
const USBGenericDescriptor *hidd_function_parse_interface(HIDDFunction *p_hidd,
		USBGenericDescriptor *descriptors, uint32_t length)
{
	HIDDParseData data;

	p_hidd->bPipeIN = 0xFF;
	p_hidd->bPipeOUT = 0xFF;

	data.p_hidd = p_hidd;
	data.pIfDesc = 0;

	return usb_generic_descriptor_parse(descriptors, length,
			(USBDescriptorParseFunction)hidd_function_parse,
			(void*)&data);
}

/**
 * Start polling interrupt OUT pipe
 * (output report, host to device) if there is.
 * \param p_hidd Pointer to HIDDFunction instance.
 */
uint32_t hidd_function_start_polling_outputs(HIDDFunction *p_hidd)
{
	/* No report, do nothing */
	if (p_hidd->bOutputListSize == 0 ||
			p_hidd->pOutputList == 0)
		return USBRC_PARAM_ERR;

	/* Start reading a report */
	return usbd_read(p_hidd->bPipeOUT,
			p_hidd->pOutputList[p_hidd->bCurrOutput]->bData,
			p_hidd->pOutputList[p_hidd->bCurrOutput]->wMaxSize,
			hidd_function_report_received, p_hidd);
}

/**
 * Start sending reports via interrupt IN pipe
 * (input report, device to host) if there is.
 * \param p_hidd Pointer to HIDDFunction instance.
 */
uint32_t hidd_function_start_sending_inputs(HIDDFunction *p_hidd)
{
	/* No report, do nothing */
	if (p_hidd->bInputListSize == 0 ||
			p_hidd->pInputList == 0)
		return USBRC_PARAM_ERR;

	/* Start sending a report */
	return usbd_write(p_hidd->bPipeIN,
			p_hidd->pInputList[p_hidd->bCurrInput]->bData,
			p_hidd->pInputList[p_hidd->bCurrInput]->wMaxSize,
			hidd_function_report_sent, p_hidd);
}

/**
 * Handles HID-specific SETUP request sent by the host.
 * \param p_hidd Pointer to HIDDFunction instance.
 * \param request Pointer to a USBGenericRequest instance
 */
uint32_t hidd_function_request_handler(HIDDFunction *p_hidd,
		const USBGenericRequest *request)
{
	uint32_t reqCode = (request->bmRequestType << 8) |
		request->bRequest;

	switch (reqCode) {
	/* Get_Descriptor */
	case USBGenericRequest_GETDESCRIPTOR | (0x81 << 8):
		return hidd_function_get_descriptor(p_hidd,
				usb_get_descriptor_request_get_descriptor_type(request),
				usb_generic_request_get_length(request));

	/* Clear_Feature (EP) */
	case USBGenericRequest_CLEARFEATURE | (0x02 << 8):
		if (usb_feature_request_get_feature_selector(request) ==
				USBFeatureRequest_ENDPOINTHALT) {
			uint8_t ep = usb_generic_request_get_endpoint_number(request);
			if (usbd_is_halted(ep)) {
				/* Unhalt EP */
				usbd_unhalt(ep);

				/* Restart Polling OUT */
				if (ep == p_hidd->bPipeOUT) {
					hidd_function_start_polling_outputs(p_hidd);
				}

				/* and send a zero-length packet */
				usbd_write(0, 0, 0, 0, 0);
			}
			break; /* Handled success */
		}
		return USBRC_PARAM_ERR;

	/* Set_Descriptor */
	case USBGenericRequest_SETDESCRIPTOR | (0x01 << 8):
		/* Optional, not implemented */
		usbd_stall(0);
		break;

	/* Get_Idle */
	case HIDGenericRequest_GETIDLE | (0xa1 << 8):
		hidd_function_get_idle(p_hidd,
				hid_report_request_get_report_id(request));
		break;

	/* Set_Idle */
	case HIDGenericRequest_SETIDLE | (0x21 << 8):
		hidd_function_set_idle(p_hidd,
				hid_report_request_get_report_id(request),
				hid_idle_request_get_idle_rate(request));
		break;

	/* Get_Report */
	case HIDGenericRequest_GETREPORT | (0xa1 << 8):
		hidd_function_get_report(p_hidd,
				hid_report_request_get_report_type(request),
				hid_report_request_get_report_id(request),
				usb_generic_request_get_length(request));
		break;

	/* Set_Report */
	case HIDGenericRequest_SETREPORT | (0x21 << 8):
		hidd_function_set_report(p_hidd,
				hid_report_request_get_report_type(request),
				hid_report_request_get_report_id(request),
				usb_generic_request_get_length(request));
		break;

	/* Set_Protocol */
	case HIDGenericRequest_SETPROTOCOL | (0xa1 << 8):
		p_hidd->bProtocol = request->wValue;
		usbd_write(0, 0, 0, 0, 0);
		break;

	/* Get_Protocol */
	case HIDGenericRequest_GETPROTOCOL | (0x21 << 8):
		usbd_write(0, &p_hidd->bProtocol, 1, 0, 0);
		break;

	default:
		return USBRC_PARAM_ERR;
	}

	return USBRC_SUCCESS;
}

/**
 * Read raw data through USB interrupt OUT EP.
 * \param p_hidd     Pointer to HIDDFunction instance.
 * \param data     Pointer to the data buffer.
 * \param length  The data length.
 * \param callback Callback function invoked when transferring done.
 * \param callback_arg Pointer to additional arguments.
 */
uint32_t hidd_function_read(const HIDDFunction *p_hidd,
		void* data, uint32_t length,
		usbd_xfer_cb_t callback, void* callback_arg)
{
	return usbd_read(p_hidd->bPipeOUT, data, length,
			callback, callback_arg);
}

/**
 * Write raw data through USB interrupt IN EP.
 * \param p_hidd     Pointer to HIDDFunction instance.
 * \param data     Pointer to the data sent.
 * \param length  The data length.
 * \param callback Callback function invoked when transferring done.
 * \param callback_arg Pointer to additional arguments.
 */
uint32_t hidd_function_write(const HIDDFunction *p_hidd,
		void* data, uint32_t length,
		usbd_xfer_cb_t callback, void* callback_arg)
{
	return usbd_write(p_hidd->bPipeIN, data, length,
			callback, callback_arg);
}

/**
 * Initialize a report.
 * \param report   Pointer to HIDDReport instance.
 * \param size     Size of the report data.
 * \param id       Report ID.
 * \param callback Callback function for report events.
 * \param callback_arg      Pointer to event handler arguments.
 */
void hidd_function_initialize_report(HIDDReport* report,
		uint16_t size, uint8_t id,
		HIDDReportEventCallback callback, void* callback_arg)
{
	report->wMaxSize = size;
	report->wTransferred = 0;
	report->bIdleRate = 0x7F;
	report->bDelay = 0;
	report->bID = id;
	report->fCallback = callback;
	report->pArg = callback_arg;
}

/**@}*/

