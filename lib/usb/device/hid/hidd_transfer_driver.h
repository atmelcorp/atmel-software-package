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

/**
 *\file
 *
 *\section Purpose
 *
 *Definition of methods for using a HID transfer %device driver.
 *
 *\section Usage
 *
 *-# Re-implement the usbd_callbacks_request_received callback to forward
 *      requests to hidd_transfer_driver_request_handler. This is done
 *      automatically unless the NOAUTOCALLBACK symbol is defined during
 *      compilation.
 *-# Initialize the driver using hidd_transfer_driver_initialize. The
 *   USB driver is automatically initialized by this method.
 *-# Call the hidd_transfer_driver_write method when sending data to host.
 *-# Call the HIDDTransferRead, HIDDTransferReadReport when checking and getting
 *   received data from host.
 */

#ifndef HIDDKEYBOARDDRIVER_H
#define HIDDKEYBOARDDRIVER_H

/** \addtogroup usbd_hid_tran
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "compiler.h"

#include "usb/common/usb_descriptors.h"
#include "usb/common/usb_requests.h"
#include "usb/common/hid/hid_descriptors.h"
#include "usb/device/usbd_driver.h"
#include "usb/device/usbd.h"

/*------------------------------------------------------------------------------
 *         Definitions
 *------------------------------------------------------------------------------*/

/** Size of the input and output report, in bytes */
#define HIDDTransferDriver_REPORTSIZE               32

/** Size of the report descriptor, in bytes */
#define HIDDTransferDriver_REPORTDESCRIPTORSIZE     44

/*------------------------------------------------------------------------------
 *         Types
 *------------------------------------------------------------------------------*/


/**
 * \typedef HIDDTransferDriverConfigurationDescriptors
 * \brief List of descriptors that make up the configuration descriptors of a
 *        device using the HID Transfer driver.
 */
typedef PACKED_STRUCT _HIDDTransferDriverConfigurationDescriptors {

	/** Configuration descriptor. */
	USBConfigurationDescriptor configuration;
	/** Interface descriptor. */
	USBInterfaceDescriptor interface;
	/** HID descriptor. */
	HIDDescriptor1 hid;
	/** Interrupt IN endpoint descriptor. */
	USBEndpointDescriptor interruptIn;
	/** Interrupt OUT endpoint descriptor. */
	USBEndpointDescriptor interruptOut;

} HIDDTransferDriverConfigurationDescriptors;


/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

extern void hidd_transfer_driver_initialize(
	const USBDDriverDescriptors *descriptors);

extern void hidd_transfer_driver_configuration_changed_handler(uint8_t cfg_num);

extern void hidd_transfer_driver_request_handler(
	const USBGenericRequest *request);

extern uint16_t hidd_transfer_driver_read(void *data, uint32_t length);

extern uint16_t hidd_transfer_driver_read_report(
		void *data, uint32_t length);

extern uint16_t hidd_transfer_driver_read_feature(
		void *data, uint32_t length);

extern uint8_t hidd_transfer_driver_write(const void *data, uint32_t length,
		usbd_xfer_cb_t callback, void *callback_rg);


extern void hidd_transfer_driver_remote_wakeup(void);

/**@}*/

#endif /*#ifndef HIDDKEYBOARDDRIVER_H*/

