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
 * \file
 *
 * \section Purpose
 *
 * Definition of a class for implementing a USB device CDC serial driver.
 *
 * \section Usage
 *
 * -# Re-implement the usbd_callbacks_request_received method to pass
 *    received requests to cdcd_serial_driver_request_handler. *This is
 *    automatically done unless the NOAUTOCALLBACK symbol is defined*.
 * -# Initialize the CDC serial and USB drivers using
 *    cdcd_serial_driver_initialize.
 * -# Logically connect the device to the host using usbd_connect.
 * -# Send serial data to the USB host using cdcd_serial_driver_write.
 * -# Receive serial data from the USB host using cdcd_serial_driver_read.
 */

#ifndef CDCDSERIALDRIVER_H
#define CDCDSERIALDRIVER_H

/** \addtogroup usbd_cdc
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include <stdint.h>

#include "compiler.h"

#include "usb/common/usb_requests.h"
#include "usb/common/cdc/cdc_requests.h"
#include "usb/common/cdc/cdc_descriptors.h"
#include "usb/common/cdc/cdc_notifications.h"
#include "usb/device/cdc/cdcd_serial.h"

/*------------------------------------------------------------------------------
 *         Definitions
 *------------------------------------------------------------------------------*/

/** \addtogroup usbd_cdc_if USB Device CDC Serial Interface IDs
 *      @{
 */
/** Communication Class Interface ID */
#define CDCDSerialDriver_CC_INTERFACE           0
/** Data Class Interface ID */
#define CDCDSerialDriver_DC_INTERFACE           1
/**     @}*/

/*------------------------------------------------------------------------------
 *         Types
 *------------------------------------------------------------------------------*/


/**
 * \typedef CDCDSerialDriverConfigurationDescriptors
 * \brief Configuration descriptor list for a device implementing a
 *        CDC serial driver.
 */
typedef PACKED_STRUCT _CDCDSerialDriverConfigurationDescriptors {

	/** Standard configuration descriptor. */
	USBConfigurationDescriptor configuration;
	/** Communication interface descriptor. */
	USBInterfaceDescriptor  communication;
	/** CDC header functional descriptor. */
	CDCHeaderDescriptor header;
	/** CDC call management functional descriptor. */
	CDCCallManagementDescriptor callManagement;
	/** CDC abstract control management functional descriptor. */
	CDCAbstractControlManagementDescriptor abstractControlManagement;
	/** CDC union functional descriptor (with one slave interface). */
	CDCUnionDescriptor union1;
	/** Notification endpoint descriptor. */
	USBEndpointDescriptor notification;
	/** Data interface descriptor. */
	USBInterfaceDescriptor data;
	/** Data OUT endpoint descriptor. */
	USBEndpointDescriptor dataOut;
	/** Data IN endpoint descriptor. */
	USBEndpointDescriptor dataIn;

} CDCDSerialDriverConfigurationDescriptors;

/**
 * \typedef CDCDSerialDriverConfigurationDescriptorsOTG
 * \brief Configuration descriptor list for a device implementing a
 *        CDC serial OTG driver.
 */
typedef PACKED_STRUCT _CDCDSerialDriverConfigurationDescriptorsOTG {

	/** Standard configuration descriptor. */
	USBConfigurationDescriptor configuration;
	/* OTG descriptor */
	USBOtgDescriptor otgDescriptor;
	/** Communication interface descriptor. */
	USBInterfaceDescriptor  communication;
	/** CDC header functional descriptor. */
	CDCHeaderDescriptor header;
	/** CDC call management functional descriptor. */
	CDCCallManagementDescriptor callManagement;
	/** CDC abstract control management functional descriptor. */
	CDCAbstractControlManagementDescriptor abstractControlManagement;
	/** CDC union functional descriptor (with one slave interface). */
	CDCUnionDescriptor union1;
	/** Notification endpoint descriptor. */
	USBEndpointDescriptor notification;
	/** Data interface descriptor. */
	USBInterfaceDescriptor data;
	/** Data OUT endpoint descriptor. */
	USBEndpointDescriptor dataOut;
	/** Data IN endpoint descriptor. */
	USBEndpointDescriptor dataIn;

} CDCDSerialDriverConfigurationDescriptorsOTG;


/*------------------------------------------------------------------------------
 *      Exported functions
 *------------------------------------------------------------------------------*/

extern void cdcd_serial_driver_initialize(
	const USBDDriverDescriptors *pDescriptors);

extern void cdcd_serial_driver_configuration_changed_handler(uint8_t cfgnum);

extern void cdcd_serial_driver_request_handler(
	const USBGenericRequest *request);

/**
 * Sends a data buffer through the virtual COM port created by the CDC
 * device serial driver. This function behaves exactly like usbd_write.
 * \param data Pointer to the data buffer to send.
 * \param size Size of the data buffer in bytes.
 * \param callback Optional callback function to invoke when the transfer
 *                 finishes.
 * \param argument Optional argument to the callback function.
 * \return USBD_STATUS_SUCCESS if the read operation has been started normally;
 *         otherwise, the corresponding error code.
 */
static inline uint32_t cdcd_serial_driver_write(
	void *data,
	uint32_t size,
	usbd_xfer_cb_t callback,
	void *argument)
{
	return cdcd_serial_write(data, size, callback, argument);
}

/**
 * Receives data from the host through the virtual COM port created by
 * the CDC device serial driver. This function behaves like usbd_read.
 * \param data Pointer to the data buffer to put received data.
 * \param size Size of the data buffer in bytes.
 * \param callback Optional callback function to invoke when the transfer
 *                 finishes.
 * \param argument Optional argument to the callback function.
 * \return USBD_STATUS_SUCCESS if the read operation has been started normally;
 *         otherwise, the corresponding error code.
 */
static inline uint32_t cdcd_serial_driver_read(
	void *data,
	uint32_t size,
	usbd_xfer_cb_t callback,
	void *argument)
{
	return cdcd_serial_read(data, size, callback, argument);
}

/**
 * Copy current line coding settings to pointed space.
 * \param pLineCoding Pointer to CDCLineCoding instance.
 */
static inline void cdcd_serial_driver_get_line_coding(CDCLineCoding * pLineCoding)
{
	cdcd_serial_get_line_coding(pLineCoding);
}

/**
 * Returns the current control line state of the RS-232 line.
 */
static inline uint8_t cdcd_serial_driver_get_control_line_state(void)
{
	return cdcd_serial_get_control_line_state();
}

/**
 * Returns the current status of the RS-232 line.
 */
static inline uint16_t cdcd_serial_driver_get_serial_state(void)
{
	return cdcd_serial_get_serial_state();
}

/**
 * Sets the current serial state of the device to the given value.
 * \param serialState  New device state.
 */
static inline void cdcd_serial_driver_set_serial_state(uint16_t serialState)
{
	cdcd_serial_set_serial_state(serialState);
}

/**@}*/

#endif /*#ifndef CDCSERIALDRIVER_H*/

