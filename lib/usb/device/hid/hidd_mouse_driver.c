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
 * \addtogroup usbd_hid_mouse
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "trace.h"
#include "mm/cache.h"

#include "usb/device/hid/hidd_function.h"
#include "usb/device/hid/hidd_mouse_driver.h"
#include "usb/device/usbd_driver.h"
#include "usb/device/usbd.h"

#include <string.h>

/*------------------------------------------------------------------------------
 *         Internal Defines
 *------------------------------------------------------------------------------*/

/** Tag bit (Always 1) */
#define HIDDMouse_TAG       (1 << 3)

/** Xsign bit */
#define HIDDMouse_Xsign     (1 << 4)

/** Ysign bit */
#define HIDDMouse_Ysign     (1 << 5)

/*------------------------------------------------------------------------------
 *         Internal types
 *------------------------------------------------------------------------------*/

/**
 * Struct for an HID Mouse report.
 */
typedef struct _HIDDMouseReport {
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

	/** padding to reach L1_CACHE_BYTES alignment */
	uint8_t padding[17];

	/** Report data block */
	HIDDMouseInputReport report;
} HIDDMouseReport;

/**
 * Driver structure for an HID device implementing keyboard functionalities.
 */
typedef struct _HIDDMouseDriver {
	/** Mouse function instance */
	HIDDFunction hidDrv;

	/** Mouse input report */
	HIDDReport   *inputReports[1];
} HIDDMouseDriver;

/*------------------------------------------------------------------------------
 *         Internal variables
 *------------------------------------------------------------------------------*/

/** Static instance of the HID mouse device driver. */
static HIDDMouseDriver hidd_mouse_driver;

/** Input report */
CACHE_ALIGNED static HIDDMouseReport hidd_input_report;

/** Report descriptor used by the driver. */
static const uint8_t hidd_report_descriptor[] = {
	/* Global Usage Page */
	HIDReport_GLOBAL_USAGEPAGE + 1, HIDGenericDesktop_PAGEID,
	/* Collection: Application */
	HIDReport_LOCAL_USAGE + 1, HIDGenericDesktop_MOUSE,
	HIDReport_COLLECTION + 1, HIDReport_COLLECTION_APPLICATION,
		/* Physical collection: Pointer */
		HIDReport_LOCAL_USAGE + 1, HIDGenericDesktop_POINTER,
		HIDReport_COLLECTION + 1, HIDReport_COLLECTION_PHYSICAL,
			/* Input report: buttons */
			HIDReport_GLOBAL_USAGEPAGE + 1, HIDButton_PAGEID,
			HIDReport_GLOBAL_REPORTCOUNT + 1, 3,
			HIDReport_GLOBAL_REPORTSIZE + 1, 1,
			HIDReport_LOCAL_USAGEMINIMUM + 1, 1,
			HIDReport_LOCAL_USAGEMAXIMUM + 1, 3,
			HIDReport_GLOBAL_LOGICALMINIMUM + 1, 0,
			HIDReport_GLOBAL_LOGICALMAXIMUM + 1, 1,
			HIDReport_INPUT + 1, HIDReport_VARIABLE,    /* 3 button bits */
			/* Input report: padding */
			HIDReport_GLOBAL_REPORTCOUNT + 1, 1,
			HIDReport_GLOBAL_REPORTSIZE + 1, 5,
			HIDReport_INPUT + 1, HIDReport_CONSTANT,    /* 5 bit padding */
			/* Input report: pointer */
			HIDReport_GLOBAL_USAGEPAGE + 1, HIDGenericDesktop_PAGEID,
			HIDReport_GLOBAL_REPORTSIZE + 1, 8,
			HIDReport_GLOBAL_REPORTCOUNT + 1, 2,
			HIDReport_LOCAL_USAGE + 1, HIDGenericDesktop_X,
			HIDReport_LOCAL_USAGE + 1, HIDGenericDesktop_Y,
			HIDReport_GLOBAL_LOGICALMINIMUM + 1, (uint8_t) -127,
			HIDReport_GLOBAL_LOGICALMAXIMUM + 1, 127,
			HIDReport_INPUT + 1, HIDReport_VARIABLE | HIDReport_RELATIVE,
		HIDReport_ENDCOLLECTION,
	HIDReport_ENDCOLLECTION
};

/*------------------------------------------------------------------------------
 *         Internal functions
 *------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *      Exported functions
 *------------------------------------------------------------------------------*/

/**
 * Initializes the HID Mouse %device driver.
 * \param p_descriptors Pointer to descriptor list for the HID Mouse.
 */
void hidd_mouse_driver_initialize(const USBDDriverDescriptors *descriptors)
{
	HIDDMouseDriver* p_mouse = &hidd_mouse_driver;
	HIDDFunction* p_hidd = &p_mouse->hidDrv;

	/* One input report */
	p_mouse->inputReports[0] = (HIDDReport*)&hidd_input_report;
	hidd_function_initialize_report(p_mouse->inputReports[0],
			HIDDMouseDriver_REPORTDESCRIPTORSIZE, 0, 0, 0);
	memset(&hidd_input_report.report, 0, sizeof hidd_input_report.report);

	/* Initialize USBD Driver instance */
	usbd_driver_initialize(descriptors, NULL, 0);

	/* Function initialize */
	hidd_function_initialize(p_hidd, 0, hidd_report_descriptor,
			(HIDDReport**)(&p_mouse->inputReports), 1, 0, 0);

	usbd_init();
}

/**
 * Handles configureation changed event.
 * \param cfg_num New configuration number
 */
void hidd_mouse_driver_configuration_changed_handler(uint8_t cfg_num)
{
	HIDDMouseDriver *p_mouse = &hidd_mouse_driver;
	HIDDFunction *p_hidd = &p_mouse->hidDrv;
	USBConfigurationDescriptor *p_desc;

	if (cfg_num > 0) {
		/* Parse endpoints for reports */
		p_desc = usbd_driver_get_cfg_descriptors(cfg_num);
		hidd_function_parse_interface(p_hidd,
				(USBGenericDescriptor*)p_desc, p_desc->wTotalLength);
	}
}

/**
 * Handles HID-specific SETUP request sent by the host.
 * \param request Pointer to a USBGenericRequest instance
 */
void hidd_mouse_driver_request_handler(const USBGenericRequest *request)
{
	HIDDMouseDriver *p_mouse = &hidd_mouse_driver;
	HIDDFunction *p_hidd = &p_mouse->hidDrv;

	LIBUSB_TRACE("NewReq ");

	/* Process HID requests */
	if (hidd_function_request_handler(p_hidd, request) != USBRC_SUCCESS) {
		/* Process STD requests */
		usbd_driver_request_handler(request);
	}

}

/**
 * Update the Mouse button status and location changes via input report
 * to host
 * \param bm_buttons Bit map of the button status
 * \param delta_x Movement on X direction
 * \param delta_y Movement on Y direction
 */
uint8_t hidd_mouse_driver_change_points(uint8_t bm_buttons,
		int8_t delta_x, int8_t delta_y)
{
	HIDDMouseDriver *p_mouse = &hidd_mouse_driver;
	HIDDFunction *p_hidd = &p_mouse->hidDrv;
	HIDDMouseInputReport *p_report = &hidd_input_report.report;

	p_report->bmButtons = (bm_buttons & 0x07) | HIDDMouse_TAG;
	p_report->bX        = delta_x;
	p_report->bY        = delta_y;

	/* Send input report through the interrupt IN endpoint */
	return usbd_write(p_hidd->bPipeIN,
			(void*)p_report, sizeof(HIDDMouseInputReport),
			NULL, NULL);
}

/**
 * Starts a remote wake-up sequence if the host has explicitly enabled it
 * by sending the appropriate SET_FEATURE request.
 */
void hidd_mouse_driver_remote_wakeup(void)
{
	/* Remote wake-up has been enabled */
	if (usbd_driver_is_remote_wakeup_enabled()) {
		usbd_remote_wakeup();
	}
}

/**@}*/

