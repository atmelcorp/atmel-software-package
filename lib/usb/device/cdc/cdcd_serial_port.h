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
 *  Definition of a class for implementing a USB device
 *  CDC serial port function.
 */

#ifndef _CDCDSERIALPORT_H_
#define _CDCDSERIALPORT_H_

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include <stdint.h>

#include "compiler.h"

#include "usb/common/cdc/cdc_notifications.h"
#include "usb/common/cdc/cdc_requests.h"
#include "usb/common/usb_requests.h"
#include "usb/device/usbd_driver.h"
#include "usb/device/usbd.h"

/** \addtogroup usbd_cdc
 *@{
 */

/*------------------------------------------------------------------------------
 *         Defines
 *------------------------------------------------------------------------------*/

/** \addtogroup usbd_cdc_serial_desc USB Device Serial Port Descriptor Values
 *      @{
 */
/** Default CDC interrupt endpoints max packat size (8). */
#define CDCDSerialPort_INTERRUPT_MAXPACKETSIZE          8
/** Default CDC interrupt endpoint polling rate of High Speed (16ms). */
#define CDCDSerialPort_INTERRUPT_INTERVAL_HS            8
/** Default CDC interrupt endpoint polling rate of Full Speed (16ms). */
#define CDCDSerialPort_INTERRUPT_INTERVAL_FS            16
/** Default CDC bulk endpoints max packat size (512, for HS actually). */
#define CDCDSerialPort_BULK_MAXPACKETSIZE_HS            512
/** Default CDC bulk endpoints max packat size (64, for FS actually). */
#define CDCDSerialPort_BULK_MAXPACKETSIZE_FS            64
/**     @}*/

/** \addtogroup usbd_cdc_serial_events USB Device Serial Port Events
 *      @{
 */
/** SetControlLineState event, value is changed */
#define CDCDSerialPortEvent_SETCONTROLLINESTATE         0
/** SetLineCoding event, value is to changed according to return value */
#define CDCDSerialPortEvent_SETLINECODING               1
/**     @}*/

/*------------------------------------------------------------------------------
 *         Types
 *------------------------------------------------------------------------------*/

/** Callback function for serial port events */
typedef uint32_t (*CDCDSerialPortEventHandler)(uint32_t dwEvent,
											   uint32_t dwParam,
											   void * pArguments);

/**
 * Struct for USB CDC virtual COM serial port function.
 */
typedef struct _CDCDSerialPort {
	/** Callback for serial port events */
	CDCDSerialPortEventHandler fEventHandler;
	/** Callback arguments */
	void *pArg;
	/** USB starting interface index */
	uint8_t bInterfaceNdx;
	/** USB number of interfaces */
	uint8_t bNumInterface;
	/** USB interrupt IN endpoint address */
	uint8_t bIntInPIPE;
	/** USB bulk IN endpoint address */
	uint8_t bBulkInPIPE;
	/** USB bulk OUT endpoint address */
	uint8_t bBulkOutPIPE;

	/** Serial port ControlLineState */
	uint8_t        bControlLineState;
	/** Serial port SerialState */
	uint16_t       wSerialState;
	/** Serial port linecoding */
	CDCLineCoding  lineCoding;

	uint8_t  bReserved;
} CDCDSerialPort;

/*------------------------------------------------------------------------------
 *         Functions
 *------------------------------------------------------------------------------*/

extern void cdcd_serial_port_initialize(CDCDSerialPort *pCdcd,
									  CDCDSerialPortEventHandler fCallback,
									  void *pArg,
									  uint8_t firstInterface,
									  uint8_t numInterface);

extern const USBGenericDescriptor * cdcd_serial_port_parse_interfaces(
	CDCDSerialPort * pCdcd,
	const USBGenericDescriptor * pDescriptors, uint32_t dwLength);

extern uint32_t cdcd_serial_port_request_handler(
	CDCDSerialPort *pCdcd,
	const USBGenericRequest *pRequest);

extern uint32_t cdcd_serial_port_write(
	const CDCDSerialPort *pCdcd,
	void *pData, uint32_t dwSize,
	usbd_xfer_cb_t fCallback, void* pArg);

extern uint32_t cdcd_serial_port_read(
	const CDCDSerialPort *pCdcd,
	void *pData, uint32_t dwSize,
	usbd_xfer_cb_t fCallback, void* pArg);

extern uint16_t cdcd_serial_port_get_serial_state(
	const CDCDSerialPort *pCdcd);

extern void cdcd_serial_port_set_serial_state(
	CDCDSerialPort *pCdcd,
	uint16_t wSerialState);

extern uint8_t cdcd_serial_port_get_control_line_state(
	const CDCDSerialPort * pCdcd);

extern void cdcd_serial_port_get_line_coding(
	const CDCDSerialPort * pCdcd,
	CDCLineCoding * pLineCoding);

/**@}*/
#endif /* #ifndef _CDCDSERIALPORT_H_ */
