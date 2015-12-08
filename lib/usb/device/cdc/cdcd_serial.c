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
 * Implementation of a single CDC serial port function for USB device.
 */

/** \addtogroup usbd_cdc
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "trace.h"

#include "usb/device/cdc/cdcd_serial.h"
#include "usb/device/usbd_driver.h"

/*------------------------------------------------------------------------------
 *         Types
 *------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *         Internal variables
 *------------------------------------------------------------------------------*/

/** Serial Port instance list */
static CDCDSerialPort cdcd_serial;

/*------------------------------------------------------------------------------
 *         Internal functions
 *------------------------------------------------------------------------------*/

/**
 * USB CDC Serial Port Event Handler.
 * \param event Event code.
 * \param param Event parameter.
 */
static uint32_t cdcd_serial_event_handler(uint32_t event, uint32_t param)
{
	switch (event) {
	case CDCDSerialPortEvent_SETCONTROLLINESTATE:
		cdcd_serial_control_line_state_changed(
			(param & CDCControlLineState_DTR) > 0,
			(param & CDCControlLineState_RTS) > 0);
		break;
	case CDCDSerialPortEvent_SETLINECODING:
		event = cdcd_serial_line_coding_is_to_change((CDCLineCoding*)param);
		if (event != USBRC_SUCCESS)
			return event;
		break;
	default:
		return USBRC_SUCCESS;
	}

	return USBRC_SUCCESS;
}

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

/**
 *  Initializes the USB Device CDC serial driver & USBD Driver.
 * \param p_usbd         Pointer to USBDDriver instance.
 * \param b_interface_nb  Interface number for the function.
 */
void cdcd_serial_initialize(uint8_t b_interface_nb)
{
	CDCDSerialPort *p_cdcd = &cdcd_serial;

	LIBUSB_TRACE("cdcd_serial_initialize ");

	/* Initialize serial port function */
	cdcd_serial_port_initialize(p_cdcd,
			(CDCDSerialPortEventHandler)cdcd_serial_event_handler, 0,
			b_interface_nb, 2);
}

/**
 * Invoked whenever the device is changed by the
 * host.
 * \p_descriptors Pointer to the descriptors for function configure.
 * \wLength      length of descriptors in number of bytes.
 */
void cdcd_serial_configure_function(USBGenericDescriptor *descriptors,
		uint16_t length)
{
	CDCDSerialPort *p_cdcd = &cdcd_serial;
	cdcd_serial_port_parse_interfaces(p_cdcd,
			(USBGenericDescriptor*)descriptors, length);
}

/**
 * Handles CDC-specific SETUP requests. Should be called from a
 * re-implementation of usbd_callbacks_request_received() method.
 * \param request Pointer to a USBGenericRequest instance.
 */
uint32_t cdcd_serial_request_handler(const USBGenericRequest *request)
{
	CDCDSerialPort * p_cdcd = &cdcd_serial;

	LIBUSB_TRACE("Cdcf ");
	return cdcd_serial_port_request_handler(p_cdcd, request);
}

/**
 * Receives data from the host through the virtual COM port created by
 * the CDC device serial driver. This function behaves like usbd_read.
 * \param data Pointer to the data buffer to put received data.
 * \param size Size of the data buffer in bytes.
 * \param callback Optional callback function to invoke when the transfer
 *                 finishes.
 * \param callback_arg Optional argument to the callback function.
 * \return USBD_STATUS_SUCCESS if the read operation has been started normally;
 *         otherwise, the corresponding error code.
 */
uint32_t cdcd_serial_read(void *data, uint32_t size,
		usbd_xfer_cb_t callback, void *callback_arg)
{
	CDCDSerialPort * p_cdcd = &cdcd_serial;
	return cdcd_serial_port_read(p_cdcd, data, size,
			callback, callback_arg);
}

/**
 * Sends a data buffer through the virtual COM port created by the CDC
 * device serial driver. This function behaves exactly like usbd_write.
 * \param data Pointer to the data buffer to send.
 * \param size Size of the data buffer in bytes.
 * \param callback Optional callback function to invoke when the transfer
 *                 finishes.
 * \param callback_arg Optional argument to the callback function.
 * \return USBD_STATUS_SUCCESS if the read operation has been started normally;
 *         otherwise, the corresponding error code.
 */
uint32_t cdcd_serial_write(void *data, uint32_t size,
		usbd_xfer_cb_t callback, void *callback_arg)
{
	CDCDSerialPort * p_cdcd = &cdcd_serial;
	return cdcd_serial_port_write(p_cdcd, data, size,
			callback, callback_arg);
}

/**
 * Returns the current control line state of the RS-232 line.
 */
uint8_t cdcd_serial_get_control_line_state(void)
{
	CDCDSerialPort *p_cdcd = &cdcd_serial;
	return cdcd_serial_port_get_control_line_state(p_cdcd);
}

/**
 * Copy current line coding settings to pointered space.
 * \param p_line_coding Pointer to CDCLineCoding instance.
 */
void cdcd_serial_get_line_coding(CDCLineCoding* p_line_coding)
{
	CDCDSerialPort *p_cdcd = &cdcd_serial;
	cdcd_serial_port_get_line_coding(p_cdcd, p_line_coding);
}

/**
 * Returns the current status of the RS-232 line.
 */
uint16_t cdcd_serial_get_serial_state(void)
{
	CDCDSerialPort *p_cdcd = &cdcd_serial;
	return cdcd_serial_port_get_serial_state(p_cdcd);
}

/**
 * Sets the current serial state of the device to the given value.
 * \param serial_state  New device state.
 */
void cdcd_serial_set_serial_state(uint16_t serial_state)
{
	CDCDSerialPort *p_cdcd = &cdcd_serial;
	cdcd_serial_port_set_serial_state(p_cdcd, serial_state);
}

/**@}*/
