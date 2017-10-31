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
 *  Implementation of the CDCDSerialPort class methods.
 */

/** \addtogroup usbd_cdc
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "trace.h"

#include "usb/common/cdc/cdc_descriptors.h"
#include "usb/device/cdc/cdcd_serial_port.h"

/*------------------------------------------------------------------------------
 *         Types
 *------------------------------------------------------------------------------*/

/** Parse data extention for descriptor parsing  */
typedef struct _CDCDParseData {
	/** Pointer to CDCDSerialPort instance */
	CDCDSerialPort * p_cdcd;

	/** Pointer to found interface descriptor */
	USBInterfaceDescriptor * p_if_desc;
} CDCDParseData;

/*------------------------------------------------------------------------------
 *         Internal variables
 *------------------------------------------------------------------------------*/

/** Line coding values */
static CDCLineCoding line_coding;

static struct {
	CDCSerialNotification notification;
	uint16_t serial_state;
} notification_data;

/*------------------------------------------------------------------------------
 *         Internal functions
 *------------------------------------------------------------------------------*/

/**
 * Parse descriptors: Interface, Bulk IN/OUT, Interrupt IN.
 * \param p_desc Pointer to descriptor list.
 * \param p_arg  Argument, pointer to AUDDParseData instance.
 */
static uint32_t _interfaces_parse(USBGenericDescriptor *desc, CDCDParseData *p_arg)
{
	CDCDSerialPort *p_cdcd = p_arg->p_cdcd;

	/* Not a valid descriptor */
	if (desc->bLength == 0)
		return USBRC_PARAM_ERR;

	/* Find interface descriptor */
	if (desc->bDescriptorType == USBGenericDescriptor_INTERFACE) {
		USBInterfaceDescriptor *pIf = (USBInterfaceDescriptor*)desc;

		/* Obtain interface from descriptor */
		if (p_cdcd->bInterfaceNdx == 0xFF) {
			/* First interface is communication */
			if (pIf->bInterfaceClass ==
				CDCCommunicationInterfaceDescriptor_CLASS) {
				p_cdcd->bInterfaceNdx = pIf->bInterfaceNumber;
				p_cdcd->bNumInterface = 2;
			}
			/* Only data interface */
			else if(pIf->bInterfaceClass == CDCDataInterfaceDescriptor_CLASS) {
				p_cdcd->bInterfaceNdx = pIf->bInterfaceNumber;
				p_cdcd->bNumInterface = 1;
			}
			p_arg->p_if_desc = pIf;
		} else if (p_cdcd->bInterfaceNdx <= pIf->bInterfaceNumber &&
				p_cdcd->bInterfaceNdx + p_cdcd->bNumInterface > pIf->bInterfaceNumber) {
			p_arg->p_if_desc = pIf;
		}
	}

	/* Parse valid interfaces */
	if (p_arg->p_if_desc == 0)
		return 0;

	/* Find endpoint descriptors */
	if (desc->bDescriptorType == USBGenericDescriptor_ENDPOINT) {
		USBEndpointDescriptor *pEp = (USBEndpointDescriptor*)desc;
		switch(pEp->bmAttributes & 0x3) {
			case USBEndpointDescriptor_INTERRUPT:
				if (pEp->bEndpointAddress & 0x80)
					p_cdcd->bIntInPIPE = pEp->bEndpointAddress & 0x7F;
				break;
			case USBEndpointDescriptor_BULK:
				if (pEp->bEndpointAddress & 0x80)
					p_cdcd->bBulkInPIPE = pEp->bEndpointAddress & 0x7F;
				else
					p_cdcd->bBulkOutPIPE = pEp->bEndpointAddress;
		}
	}

	if (p_cdcd->bInterfaceNdx != 0xFF &&
			p_cdcd->bBulkInPIPE != 0 &&
			p_cdcd->bBulkOutPIPE != 0)
		return USBRC_FINISHED;

	return 0;
}

/**
 * Callback function which should be invoked after the data of a
 * SetLineCoding request has been retrieved. Sends a zero-length packet
 * to the host for acknowledging the request.
 * \param p_cdcd Pointer to CDCDSerialPort instance.
 */
static void _set_line_coding_callback(void *arg, uint8_t status,
		uint32_t transferred, uint32_t remaining)
{
	CDCDSerialPort *p_cdcd = (CDCDSerialPort*)arg;
	bool ok = true;

	if (p_cdcd->fEventHandler) {
		uint32_t rc = p_cdcd->fEventHandler(
				CDCDSerialPortEvent_SETLINECODING,
				(uint32_t)&line_coding, p_cdcd->pArg);

		if (rc == USBD_STATUS_SUCCESS) {
			p_cdcd->lineCoding.dwDTERate   = line_coding.dwDTERate;
			p_cdcd->lineCoding.bCharFormat = line_coding.bCharFormat;
			p_cdcd->lineCoding.bParityType = line_coding.bParityType;
			p_cdcd->lineCoding.bDataBits   = line_coding.bDataBits;
		}
		else {
			ok = false;
		}
	}

	if (ok)
		usbd_write(0, 0, 0, 0, 0);
	else
		usbd_stall(0);
}

/**
 * Receives new line coding information from the USB host.
 * \param p_cdcd Pointer to CDCDSerialPort instance.
 */
static void _set_line_coding(CDCDSerialPort *p_cdcd)
{
	LIBUSB_TRACE("sLineCoding ");

	usbd_read(0, &line_coding, sizeof(CDCLineCoding),
			_set_line_coding_callback, p_cdcd);
}

/**
 * Sends the current line coding information to the host through Control
 * endpoint 0.
 * \param p_cdcd Pointer to CDCDSerialPort instance.
 */
static void _get_line_coding(CDCDSerialPort *p_cdcd)
{
	LIBUSB_TRACE("gLineCoding ");

	usbd_write(0, &p_cdcd->lineCoding, sizeof(CDCLineCoding),
			NULL, NULL);
}

/**
 * Changes the state of the serial driver according to the information
 * sent by the host via a SetControlLineState request, and acknowledges
 * the request with a zero-length packet.
 * \param p_cdcd Pointer to CDCDSerialPort instance.
 * \param request Pointer to a USBGenericRequest instance.
 */
static void _set_control_line_state(CDCDSerialPort * p_cdcd,
		const USBGenericRequest *request)
{
	LIBUSB_TRACE("sControlLineState(%d, %d) ",
		((request->wValue & CDCControlLineState_DTR) > 0),
		((request->wValue & CDCControlLineState_RTS) > 0));

	p_cdcd->bControlLineState = (uint8_t)request->wValue;
	usbd_write(0, 0, 0, 0, 0);

	if (p_cdcd->fEventHandler)
		p_cdcd->fEventHandler(
				CDCDSerialPortEvent_SETCONTROLLINESTATE,
				(uint32_t)p_cdcd->bControlLineState,
				p_cdcd->pArg);
}

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

/**
 * Initializes the USB Device CDC serial port function.
 * \param p_cdcd Pointer to CDCDSerialPort instance.
 * \param p_usbd Pointer to USBDDriver instance.
 * \param f_event_handler Pointer to event handler function.
 * \param first_interface First interface index for the function
 *                       (0xFF to parse from descriptors).
 * \param num_interface   Number of interfaces for the function.
 */
void cdcd_serial_port_initialize(CDCDSerialPort *p_cdcd,
		CDCDSerialPortEventHandler f_event_handler,
		void *p_arg, uint8_t first_interface, uint8_t num_interface)
{
	LIBUSB_TRACE("cdcd_serial_port_initialize ");

	/* Initialize event handler */
	p_cdcd->fEventHandler = f_event_handler;
	p_cdcd->pArg = p_arg;

	/* Initialize USB Device Driver interface */
	p_cdcd->bInterfaceNdx = first_interface;
	p_cdcd->bNumInterface = num_interface;
	p_cdcd->bIntInPIPE   = 0;
	p_cdcd->bBulkInPIPE  = 0;
	p_cdcd->bBulkOutPIPE = 0;

	/* Initialize Abstract Control Model attributes */
	p_cdcd->bControlLineState = 0;
	p_cdcd->wSerialState      = 0;
	cdc_line_coding_initialize(&(p_cdcd->lineCoding), 115200,
			CDCLineCoding_ONESTOPBIT, CDCLineCoding_NOPARITY, 8);
}

/**
 * Parse CDC Serial Port information for CDCDSerialPort instance.
 * Accepted interfaces:
 * - Communication Interface + Data Interface
 * - Data Interface ONLY
 * \param p_cdcd        Pointer to CDCDSerialPort instance.
 * \param descriptors Pointer to descriptor list.
 * \param length     Descriptor list size in bytes.
 */
const USBGenericDescriptor *cdcd_serial_port_parse_interfaces(
		CDCDSerialPort *p_cdcd,
		const USBGenericDescriptor *descriptors, uint32_t length)
{
	CDCDParseData parse_data;

	parse_data.p_cdcd = p_cdcd;
	parse_data.p_if_desc = 0;

	return usb_generic_descriptor_parse(descriptors, length,
			(USBDescriptorParseFunction)_interfaces_parse, &parse_data);
}

/**
 * Handles CDC-specific SETUP requests. Should be called from a
 * re-implementation of usbd_callbacks_request_received() method.
 * \param p_cdcd Pointer to CDCDSerialPort instance.
 * \param request Pointer to a USBGenericRequest instance.
 * \return USBRC_SUCCESS if request handled, otherwise error.
 */
uint32_t cdcd_serial_port_request_handler(CDCDSerialPort *p_cdcd,
		const USBGenericRequest *request)
{
	if (usb_generic_request_get_type(request) != USBGenericRequest_CLASS)
		return USBRC_PARAM_ERR;

	LIBUSB_TRACE("Cdcs ");

	/* Validate interface */
	if (request->wIndex >= p_cdcd->bInterfaceNdx &&
		request->wIndex < p_cdcd->bInterfaceNdx + p_cdcd->bNumInterface) {
	} else {
		return USBRC_PARAM_ERR;
	}

	/* Handle the request */
	switch (usb_generic_request_get_request(request)) {
	case CDCGenericRequest_SETLINECODING:
		_set_line_coding(p_cdcd);
		break;

	case CDCGenericRequest_GETLINECODING:
		_get_line_coding(p_cdcd);
		break;

	case CDCGenericRequest_SETCONTROLLINESTATE:
		_set_control_line_state(p_cdcd, request);
		break;

	default:
		return USBRC_PARAM_ERR;
	}

	return USBRC_SUCCESS;
}

/**
 * Receives data from the host through the virtual COM port created by
 * the CDC device serial driver. This function behaves like usbd_read.
 * \param p_cdcd  Pointer to CDCDSerialPort instance.
 * \param data  Pointer to the data buffer to put received data.
 * \param length Size of the data buffer in bytes.
 * \param callback Optional callback function to invoke when the transfer
 *                  finishes.
 * \param callback_arg      Optional argument to the callback function.
 * \return USBD_STATUS_SUCCESS if the read operation has been started normally;
 *         otherwise, the corresponding error code.
 */
uint32_t cdcd_serial_port_read(const CDCDSerialPort *p_cdcd,
		void *data, uint32_t length,
		usbd_xfer_cb_t callback, void *callback_arg)
{
	if (p_cdcd->bBulkOutPIPE == 0)
		return USBRC_PARAM_ERR;

	return usbd_read(p_cdcd->bBulkOutPIPE, data, length,
			callback, callback_arg);
}

/**
 * Sends a data buffer through the virtual COM port created by the CDC
 * device serial driver. This function behaves exactly like usbd_write.
 * \param p_cdcd  Pointer to CDCDSerialPort instance.
 * \param data  Pointer to the data buffer to send.
 * \param length Size of the data buffer in bytes.
 * \param callback Optional callback function to invoke when the transfer
 *                  finishes.
 * \param callback_arg      Optional argument to the callback function.
 * \return USBD_STATUS_SUCCESS if the read operation has been started normally;
 *         otherwise, the corresponding error code.
 */
uint32_t cdcd_serial_port_write(const CDCDSerialPort *p_cdcd,
		void *data, uint32_t length,
		usbd_xfer_cb_t callback, void *callback_arg)
{
	if (p_cdcd->bBulkInPIPE == 0)
		return USBRC_PARAM_ERR;

	return usbd_write(p_cdcd->bBulkInPIPE, data, length,
			callback, callback_arg);
}

/**
 * Returns the current control line state of the RS-232 line.
 * \param p_cdcd  Pointer to CDCDSerialPort instance.
 */
uint8_t cdcd_serial_port_get_control_line_state(const CDCDSerialPort *p_cdcd)
{
	return p_cdcd->bControlLineState;
}

/**
 * Copy current line coding settings to pointered space.
 * \param p_cdcd  Pointer to CDCDSerialPort instance.
 * \param pLineCoding Pointer to CDCLineCoding instance.
 */
void cdcd_serial_port_get_line_coding(const CDCDSerialPort *p_cdcd,
		CDCLineCoding* coding)
{
	if (coding) {
		coding->dwDTERate   = p_cdcd->lineCoding.dwDTERate;
		coding->bCharFormat = p_cdcd->lineCoding.bCharFormat;
		coding->bParityType = p_cdcd->lineCoding.bParityType;
		coding->bDataBits   = p_cdcd->lineCoding.bDataBits;
	}
}

/**
 * Returns the current status of the RS-232 line.
 * \param p_cdcd  Pointer to CDCDSerialPort instance.
 */
uint16_t cdcd_serial_port_get_serial_state(const CDCDSerialPort *p_cdcd)
{
	return p_cdcd->wSerialState;
}

/**
 * Sets the current serial state of the device to the given value.
 * \param p_cdcd  Pointer to CDCDSerialPort instance.
 * \param wSerialState  New device state.
 */
void cdcd_serial_port_set_serial_state(CDCDSerialPort *p_cdcd,
		uint16_t wSerialState)
{


	notification_data.notification.bmRequestType = 0xA1;
	notification_data.notification.bNotificationType = 0x20;
	notification_data.notification.wValue = 0;
	notification_data.notification.wIndex = 0;
	notification_data.notification.wLength = 2;
	notification_data.serial_state = p_cdcd->wSerialState;

	if (p_cdcd->bIntInPIPE == 0)
		return;

	/* If new state is different from previous one, send a notification to the
	   host */
	if (p_cdcd->wSerialState != wSerialState) {
		p_cdcd->wSerialState = wSerialState;
		usbd_write(p_cdcd->bIntInPIPE, (uint8_t*)&notification_data,
			sizeof(notification_data), NULL, NULL);
		/* Reset one-time flags */
		p_cdcd->wSerialState &= ~(CDCSerialState_OVERRUN |
				CDCSerialState_PARITY |
				CDCSerialState_FRAMING |
				CDCSerialState_RINGSIGNAL |
				CDCSerialState_BREAK);
	}
}

/**@}*/

