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
 * \addtogroup usbd_hid_tran
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "trace.h"

#include "chip.h"
#include "mm/cache.h"
#include "usb/common/usb_requests.h"
#include "usb/common/hid/hid_descriptors.h"
#include "usb/device/hid/hidd_function.h"
#include "usb/device/hid/hidd_transfer_driver.h"

#include <stdint.h>
#include <string.h>

/*------------------------------------------------------------------------------
 *         Internal types
 *------------------------------------------------------------------------------*/

/**
 * Report struct for HID transfer.
 */
typedef struct _HIDDTransferReport {
	/** Callback when report done */
	HIDDReportEventCallback fCallback;

	/** Callback arguments */
	void* pArg;

	/** Report size (ID + DATA) */
	uint16_t wMaxSize;

	/** Transfered size */
	uint16_t wTransferred;

	/** Report idle rate */
	uint8_t bIdleRate;

	/** Delay count for Idle */
	uint8_t bDelay;

	/** Report ID */
	uint8_t bID;

	/** padding one byte */
	uint8_t padding[17];

	/** Report data address */
	uint8_t bData[HIDDTransferDriver_REPORTSIZE];
} HIDDTransferReport;

/**
 * Driver structure for an HID device implementing simple transfer
 * functionalities.
 */
typedef struct _HIDDTransferDriver {

	/** Standard HID function interface. */
	HIDDFunction hidFunction;

	/** HID Input report list */
	HIDDReport *inputReports[1];

	/** HID Output report list */
	HIDDReport *outputReports[1];

	/** HID Feature report list */
	HIDDReport *featureReports[1];

	/* OUT Report - block input for SET_REPORT */

	/**< Output report block size */
	uint16_t iReportLen;

	/**<  Feature report block size */
	uint16_t iFeatureLen;

	/**< Output report data buffer */
	uint8_t  iReportBuf[HIDDTransferDriver_REPORTSIZE];
	
	/**< Feature report data buffer */
	uint8_t  iFeatureBuf[HIDDTransferDriver_REPORTSIZE];

} HIDDTransferDriver;

/*------------------------------------------------------------------------------
 *         Internal variables
 *------------------------------------------------------------------------------*/

/** Input report buffers */
CACHE_ALIGNED static HIDDTransferReport input_report;

/** Output report buffers */
CACHE_ALIGNED static HIDDTransferReport output_report;

/** Feature report buffers */
CACHE_ALIGNED static HIDDTransferReport feature_report;

/** Static instance of the HID Transfer device driver. */
static HIDDTransferDriver hidd_transfer_driver;

/** Report descriptor used by the driver. */
static const uint8_t hidd_transfer_report_descriptor[] = {
	/* Global Usage Page */
	HIDReport_GLOBAL_USAGEPAGE + 2, 0xFF, 0xFF, /* Vendor-defined */
	/* Collection: Application */
	HIDReport_LOCAL_USAGE + 1, 0xFF, /* Vendor-defined */
	HIDReport_COLLECTION + 1, HIDReport_COLLECTION_APPLICATION,
		/* Input report: Vendor-defined */
		HIDReport_LOCAL_USAGE + 1, 0xFF, /* Vendor-defined usage */
		HIDReport_GLOBAL_REPORTCOUNT + 1, HIDDTransferDriver_REPORTSIZE,
		HIDReport_GLOBAL_REPORTSIZE + 1, 8,
		HIDReport_GLOBAL_LOGICALMINIMUM + 1, (uint8_t) -128,
		HIDReport_GLOBAL_LOGICALMAXIMUM + 1, (uint8_t)  127,
		HIDReport_INPUT + 1, 0,    /* No Modifiers */
		/* Output report: vendor-defined */
		HIDReport_LOCAL_USAGE + 1, 0xFF, /* Vendor-defined usage */
		HIDReport_GLOBAL_REPORTCOUNT + 1, HIDDTransferDriver_REPORTSIZE,
		HIDReport_GLOBAL_REPORTSIZE + 1, 8,
		HIDReport_GLOBAL_LOGICALMINIMUM + 1, (uint8_t) -128,
		HIDReport_GLOBAL_LOGICALMAXIMUM + 1, (uint8_t)  127,
		HIDReport_OUTPUT + 1, 0,    /* No Modifiers */
		/* Feature report: vendor-defined */

		HIDReport_LOCAL_USAGE + 1, 0xFF, /* Vendor-defined usage */
		HIDReport_GLOBAL_REPORTSIZE + 1, 8,
		HIDReport_GLOBAL_REPORTCOUNT + 1, HIDDTransferDriver_REPORTSIZE,
		HIDReport_GLOBAL_LOGICALMINIMUM + 1, (uint8_t) -128,
		HIDReport_GLOBAL_LOGICALMAXIMUM + 1, (uint8_t)  127,
		HIDReport_FEATURE + 1, 0x02,    /* FEATURE (Data,Var,Abs) */

	HIDReport_ENDCOLLECTION
};

/*------------------------------------------------------------------------------
 *         Internal functions
 *------------------------------------------------------------------------------*/

/**
 * Returns the descriptor requested by the host.
 * \param type Descriptor type.
 * \param length Maximum number of bytes to send.
 * \return 1 if the request has been handled by this function, otherwise 0.
 */
static uint8_t hidd_transfer_driver_get_descriptor(uint8_t type, uint8_t length)
{
	const USBConfigurationDescriptor *p_configuration;
	HIDDescriptor *hid_descriptors[2];

	switch (type) {

		case HIDGenericDescriptor_REPORT:
			LIBUSB_TRACE("Report ");

			/* Adjust length and send report descriptor */
			if (length > HIDDTransferDriver_REPORTDESCRIPTORSIZE) {
				length = HIDDTransferDriver_REPORTDESCRIPTORSIZE;
			}

			usbd_write(0, &hidd_transfer_report_descriptor, length, 0, 0);
			break;

		case HIDGenericDescriptor_HID:
			LIBUSB_TRACE("HID ");

			/* Configuration descriptor is different depending on configuration */
			if (usbd_is_high_speed()) {
				p_configuration = usbd_driver_get_descriptors()->pHsConfiguration;
			} else {
				p_configuration = usbd_driver_get_descriptors()->pFsConfiguration;
			}

			/* Parse the device configuration to get the HID descriptor */
			usb_configuration_descriptor_parse(
					p_configuration, 0, 0,
					(USBGenericDescriptor **)hid_descriptors);

			/* Adjust length and send HID descriptor */
			if (length > sizeof(HIDDescriptor)) {
				length = sizeof(HIDDescriptor);
			}

			usbd_write(0, hid_descriptors[0], length, 0, 0);
			break;

		default:
			return 0;
	}

	return 1;
}

/**
 * Callback function when SetReport request data received from host
 * \param p_arg Pointer to additional argument struct
 * \param status Result status
 * \param transferred Number of bytes transferred
 * \param remaining Number of bytes that are not transferred yet
 */
static void hidd_transfer_driver_report_received(void *p_arg, uint8_t status,
		uint32_t transferred, uint32_t remaining)
{
	HIDDTransferDriver *p_drv = &hidd_transfer_driver;
	remaining = remaining;
	status = status;
	p_arg = p_arg;
	p_drv->iReportLen = transferred;
	usbd_write(0, 0, 0, 0, 0);
}

/**
 * Callback function when GetReport request data received from host
 * \param p_arg Pointer to additional argument struct
 * \param status Result status
 * \param transferred Number of bytes transferred
 * \param remaining Number of bytes that are not transferred yet
 */
static void hidd_transfer_driver_get_report_received(void *p_arg, uint8_t status,
		uint32_t transferred, uint32_t remaining)
{
	HIDDTransferDriver *p_drv = &hidd_transfer_driver;
	remaining = remaining;
	status = status;
	p_arg = p_arg;
	p_drv = p_drv;
	/* Do nothing at present */
}

/**
 * Callback function when SetReport(feature) request data received from host
 * \param p_arg Pointer to additional argument struct
 * \param status Result status
 * \param transferred Number of bytes transferred
 * \param remaining Number of bytes that are not transferred yet
 */
static void hidd_transfer_driver_set_feature_received(void *p_arg, uint8_t status,
		uint32_t transferred, uint32_t remaining)
{
	HIDDTransferDriver *p_drv = &hidd_transfer_driver;
	remaining = remaining;
	status = status;
	p_arg = p_arg;
	p_drv->iFeatureLen = transferred;
	usbd_write(0, 0, 0, 0, 0);
}

/**
 * Callback function when GetReport(feature) request data received from host
 * \param p_arg Pointer to additional argument struct
 * \param status Result status
 * \param transferred Number of bytes transferred
 * \param remaining Number of bytes that are not transferred yet
 */
static void hidd_transfer_driver_get_feature_received(void *p_arg, uint8_t status,
		uint32_t transferred, uint32_t remaining)
{
	HIDDTransferDriver *p_drv = &hidd_transfer_driver;
	remaining = remaining;
	status = status;
	p_arg = p_arg;
	p_drv = p_drv;
	/* Do nothing at present */
}

/*------------------------------------------------------------------------------
 *      Exported functions
 *------------------------------------------------------------------------------*/

/**
 * Initializes the HID Transfer %device driver.
 * \param p_descriptors Pointer to USBDDriverDescriptors instance.
 */
void hidd_transfer_driver_initialize(const USBDDriverDescriptors *descriptors)
{
	HIDDTransferDriver *p_drv = &hidd_transfer_driver;

	/* One input report */
	p_drv->inputReports[0] = (HIDDReport*)&input_report;
	hidd_function_initialize_report((HIDDReport *)p_drv->inputReports[0],
			HIDDTransferDriver_REPORTSIZE, 0, 0, 0);
	memset(&input_report.bData, 0, sizeof input_report.bData);

	/* One output report */
	p_drv->outputReports[0] = (HIDDReport*)&output_report;
	hidd_function_initialize_report((HIDDReport *)p_drv->outputReports[0],
			HIDDTransferDriver_REPORTSIZE, 0, 0, 0); 
	memset(&output_report.bData, 0, sizeof output_report.bData);

	/* One feature report */
	p_drv->featureReports[0] = (HIDDReport*)&feature_report;
	hidd_function_initialize_report((HIDDReport *)p_drv->featureReports[0],
			HIDDTransferDriver_REPORTSIZE, 0, 0, 0);
	memset(&feature_report.bData, 0, sizeof feature_report.bData);

	/* Initialize USBD Driver instance */
	usbd_driver_initialize(descriptors, NULL, 0);

	/* Function instance initialize */
	hidd_function_initialize(&p_drv->hidFunction, 0,
			hidd_transfer_report_descriptor,
			(HIDDReport **)(&p_drv->inputReports), 1,
			(HIDDReport **)(&p_drv->outputReports), 1);

	/* Initialize USBD */
	usbd_init();
}

/**
 * Handles configureation changed event.
 * \param cfgnum New configuration number
 */
void hidd_transfer_driver_configuration_changed_handler(uint8_t cfg_num)
{
	const USBDDriverDescriptors * p_descriptors = usbd_driver_get_descriptors();
	HIDDTransferDriver * p_drv = &hidd_transfer_driver;
	HIDDFunction * p_hidd = &p_drv->hidFunction;

	USBConfigurationDescriptor *pDesc;

	if (cfg_num > 0) {
		/* Parse endpoints for reports */
		if (usbd_is_high_speed() && p_descriptors->pHsConfiguration)
			pDesc = (USBConfigurationDescriptor*)p_descriptors->pHsConfiguration;
		else
			pDesc = (USBConfigurationDescriptor*)p_descriptors->pFsConfiguration;

		hidd_function_parse_interface(p_hidd,
				(USBGenericDescriptor*)pDesc, pDesc->wTotalLength);

		/* Start polling for Output Reports */
		hidd_function_start_polling_outputs(p_hidd);
	}
}

/**
 * Handles HID-specific SETUP request sent by the host.
 * \param request Pointer to a USBGenericRequest instance
 */
void hidd_transfer_driver_request_handler(const USBGenericRequest *request)
{
	HIDDTransferDriver *p_drv = &hidd_transfer_driver;
	HIDDFunction *p_hidd = &p_drv->hidFunction;

	LIBUSB_TRACE("NewReq ");

	/* Check if this is a standard request */
	if (usb_generic_request_get_type(request) == USBGenericRequest_STANDARD) {
		/* This is a standard request */
		switch (usb_generic_request_get_request(request)) {
		case USBGenericRequest_GETDESCRIPTOR:
			/* Check if this is a HID descriptor, otherwise forward it to
			   the standard driver */
			if (!hidd_transfer_driver_get_descriptor(
					usb_get_descriptor_request_get_descriptor_type(request),
					usb_generic_request_get_length(request))) {
				usbd_driver_request_handler(request);
			}
			return; /* Handled, no need to do others */

		case USBGenericRequest_CLEARFEATURE:
			/* Check which is the requested feature */
			switch (usb_feature_request_get_feature_selector(request)) {
			case USBFeatureRequest_ENDPOINTHALT:
				{
					uint8_t ep = usb_generic_request_get_endpoint_number(request);
					if (usbd_is_halted(ep)) {
						/* Unhalt endpoint restart OUT EP */
						usbd_unhalt(ep);
						if (ep == p_hidd->bPipeOUT) {
							hidd_function_start_polling_outputs(p_hidd);
						}
					}
					/* and send a zero-length packet */
					usbd_write(0, 0, 0, 0, 0);
					return; /* Handled, no need to do others */
				}
			}
			break;
		}
	}
	/* We use different buffer for SetReport */
	else if (usb_generic_request_get_type(request) == USBGenericRequest_CLASS) {
		switch (usb_generic_request_get_request(request)) {
		case HIDGenericRequest_SETREPORT:
			{
				uint16_t length = usb_generic_request_get_length(request);
				uint8_t  type = hid_report_request_get_report_type(request);
				if (type == HIDReportRequest_OUTPUT) {
					if (length > HIDDTransferDriver_REPORTSIZE)
						length = HIDDTransferDriver_REPORTSIZE;
					usbd_read(0, p_drv->iReportBuf, length,
							hidd_transfer_driver_report_received, NULL);
				} else if (type == HIDReportRequest_FEATURE) {
					if (length > HIDDTransferDriver_REPORTSIZE)
						length = HIDDTransferDriver_REPORTSIZE;
					usbd_read(0, p_drv->iFeatureBuf, length,
							hidd_transfer_driver_set_feature_received, NULL);
				} else {
					usbd_stall(0);
				}
			}
			return; /* Handled, no need do others */
		case HIDGenericRequest_GETREPORT:
		  {
				uint16_t length = usb_generic_request_get_length(request);
				uint8_t  type = hid_report_request_get_report_type(request);
				if (type == HIDReportRequest_INPUT) {
					if (length > HIDDTransferDriver_REPORTSIZE)
						length = HIDDTransferDriver_REPORTSIZE;
					usbd_write(0, p_drv->iReportBuf, length,
							hidd_transfer_driver_get_report_received, NULL);
				} else if (type== HIDReportRequest_FEATURE) {
					if (length > HIDDTransferDriver_REPORTSIZE)
						length = HIDDTransferDriver_REPORTSIZE;
					usbd_write(0, p_drv->iFeatureBuf, length,
							hidd_transfer_driver_get_feature_received, NULL);
				} else {
					usbd_stall(0);
				}
			}
			return;
		}
	}
	/* Process HID requests */
	if (hidd_function_request_handler(p_hidd, request) != USBRC_SUCCESS) {
		usbd_driver_request_handler(request);
	}
}

/**
 * Try to read request buffer of SetReport.
 * Set pData to 0 to get current data length only.
 * \param data Pointer to data buffer
 * \param length Data buffer length
 * \return Number of bytes read
 */
uint16_t hidd_transfer_driver_read_report(void *data, uint32_t length)
{
	HIDDTransferDriver *p_drv = &hidd_transfer_driver;

	if (data == 0) {
		return p_drv->iReportLen;
	}

	if (length > HIDDTransferDriver_REPORTSIZE) {
		length = HIDDTransferDriver_REPORTSIZE;
	}

	if (length > p_drv->iReportLen) {
		length = p_drv->iReportLen;
	}

	p_drv->iReportLen = 0;
	memcpy(data, p_drv->iReportBuf, length);

	return length;
}

/**
 * Try to read request buffer of SetReport(feature).
 * Set pData to 0 to get current data length only.
 * \param data Pointer to data buffer
 * \param length Data buffer length
 * \return Number of bytes read
 */
uint16_t hidd_transfer_driver_read_feature(void *data, uint32_t length)
{
	HIDDTransferDriver *p_drv = &hidd_transfer_driver;

	if (data == 0) {
		return p_drv->iFeatureLen;
	}

	if (length > HIDDTransferDriver_REPORTSIZE) {
		length = HIDDTransferDriver_REPORTSIZE;
	}

	if (length > p_drv->iFeatureLen) {
		length = p_drv->iFeatureLen;
	}

	p_drv->iFeatureLen = 0;
	memcpy(data, p_drv->iFeatureBuf, length);

	return length;
}

/**
 * Try to read request buffer of interrupt OUT EP.
 * Set data to 0 to get current data length only.
 * \param data Pointer to data buffer
 * \param length Data buffer length
 * \return Number of bytes read
 */
uint16_t hidd_transfer_driver_read(void *data, uint32_t length)
{
	HIDDTransferDriver *p_drv = &hidd_transfer_driver;

	if (data == 0) {
		return p_drv->outputReports[0]->wTransferred;
	}

	if (length > HIDDTransferDriver_REPORTSIZE) {
		length = HIDDTransferDriver_REPORTSIZE;
	}

	if (length > p_drv->outputReports[0]->wTransferred) {
		length = p_drv->outputReports[0]->wTransferred;
	}

	p_drv->outputReports[0]->wTransferred = 0;
	memcpy(data, p_drv->outputReports[0]->bData, length);

	return length;
}

/**
 * Write data through USB interrupt IN EP.
 * \param data Pointer to the data sent.
 * \param length The data length.
 * \param callback Callback function invoked when transferring done.
 * \param callback_arg Pointer to additional arguments.
 */
uint8_t hidd_transfer_driver_write(const void *data, uint32_t length,
		usbd_xfer_cb_t callback, void *callback_arg)
{
	HIDDTransferDriver *p_drv = &hidd_transfer_driver;

	if (length != HIDDTransferDriver_REPORTSIZE) {
		length = HIDDTransferDriver_REPORTSIZE;
	}

	return usbd_write(p_drv->hidFunction.bPipeIN, data, length,
			callback, callback_arg);
}

/**
 * Starts a remote wake-up sequence if the host has explicitly enabled it
 * by sending the appropriate SET_FEATURE request.
 */
void hidd_transfer_driver_remote_wakeup(void)
{
	/* Remote wake-up has been enabled */
	if (usbd_driver_is_remote_wakeup_enabled()) {
		usbd_remote_wakeup();
	}
}

/**@}*/
