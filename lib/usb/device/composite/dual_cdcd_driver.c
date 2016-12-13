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

/** \file */
/** \addtogroup usbd_composite_cdccdc
 *@{
 */
/*---------------------------------------------------------------------------
 *      Headers
 *---------------------------------------------------------------------------*/

#include "trace.h"

#include "usb/device/composite/dual_cdcd_driver.h"
#include "usb/device/usbd_driver.h"
#include "usb/device/usbd.h"

/*---------------------------------------------------------------------------
 *         Defines
 *---------------------------------------------------------------------------*/

/** Number of CDC serial ports */
#define NUM_PORTS       2

/** Interface setting spaces (4 byte aligned) */
#define NUM_INTERFACES  ((DUALCDCDDriverDescriptors_NUMINTERFACE+3)&0xFC)

/*---------------------------------------------------------------------------
 *         Types
 *---------------------------------------------------------------------------*/

/** Dual-CDC-Serial device driver struct */
typedef struct _DualCdcdSerialDriver {
	/** CDC Serial Port List */
	CDCDSerialPort cdcd_serial_port[NUM_PORTS];
} DualCdcdSerialDriver;

/*---------------------------------------------------------------------------
 *         Internal variables
 *---------------------------------------------------------------------------*/

/** Dual CDC Serial device driver instance */
DualCdcdSerialDriver dual_cdcd_driver;

/*---------------------------------------------------------------------------
 *         Internal functions
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 *         Exported functions
 *---------------------------------------------------------------------------*/

/**
 * Initializes the USB device composite device driver.
 * \param  p_descriptors Pointer to Descriptors list for CDC Serial Device.
 */
void dual_cdcd_driver_initialize(const USBDDriverDescriptors *p_descriptors)
{
	CDCDSerialPort *p_cdcd = &dual_cdcd_driver.cdcd_serial_port[0];

	LIBUSB_TRACE("dual_cdcd_driver_initialize\n\r");

	p_cdcd = &dual_cdcd_driver.cdcd_serial_port[0];
	cdcd_serial_port_initialize(p_cdcd, 0, 0, DUALCDCDDriverDescriptors_INTERFACENUM0, 2);

	p_cdcd = &dual_cdcd_driver.cdcd_serial_port[1];
	cdcd_serial_port_initialize(p_cdcd, 0, 0, DUALCDCDDriverDescriptors_INTERFACENUM1, 2);

	/*  Initialize the standard USB driver */
	usbd_driver_initialize(p_descriptors, NULL, 0);

	/*  Initialize the USB driver */
	usbd_init();
}

/**
 * Invoked whenever the active configuration of device is changed by the
 * host.
 * \param cfgnum Configuration number.
 */
void dual_cdcd_driver_configuration_change_handler(uint8_t cfgnum)
{
	CDCDSerialPort *p_cdcd = &dual_cdcd_driver.cdcd_serial_port[0];
	USBConfigurationDescriptor *p_desc;
	const USBGenericDescriptor *pd;
	uint32_t i, len;

	if (cfgnum > 0) {

		/* Parse endpoints for data & notification */
		p_desc = usbd_driver_get_cfg_descriptors(cfgnum);

		pd = (USBGenericDescriptor *)p_desc;
		len = p_desc->wTotalLength;

		for (i = 0; i < NUM_PORTS; i ++) {
			p_cdcd = &dual_cdcd_driver.cdcd_serial_port[i];
			pd = cdcd_serial_port_parse_interfaces(p_cdcd, pd, len);
			len = p_desc->wTotalLength - ((uint32_t)pd - (uint32_t)p_desc);
		}
	}
}


/**
 * Handles composite-specific USB requests sent by the host, and forwards
 * standard ones to the USB device driver.
 * \param request Pointer to a USBGenericRequest instance.
 */
void dual_cdcd_driver_request_handler(const USBGenericRequest *request)
{
	CDCDSerialPort *p_cdcd = 0;
	uint32_t rc, i;

	LIBUSB_TRACE("NewReq ");

	for (i = 0; i < NUM_PORTS; i ++) {
		p_cdcd = &dual_cdcd_driver.cdcd_serial_port[i];
		rc = cdcd_serial_port_request_handler(p_cdcd, request);
		if (rc == USBRC_SUCCESS)
			break;
	}

	/* Not handled by CDC Serial */
	if (rc != USBRC_SUCCESS) {
		if (usb_generic_request_get_type(request) == USBGenericRequest_STANDARD) {
			usbd_driver_request_handler(request);
		}
		else {
			trace_warning("dual_cdcd_driver_request_handler: Unsupported request (%d,%d)\n\r",
			  usb_generic_request_get_type(request),
			  usb_generic_request_get_request(request));
			usbd_stall(0);
		}
	}

}

/**
 * Return CDCDSerialPort for serial port operations.
 * \param port Port number.
 */
CDCDSerialPort *dual_cdcd_driver_get_serialport(uint32_t port)
{
	if (port < NUM_PORTS)
		return &dual_cdcd_driver.cdcd_serial_port[port];

	return 0;
}

/**@}*/

