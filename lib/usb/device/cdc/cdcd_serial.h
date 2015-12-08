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
 * Single CDC Serial Port Function for USB device & composite driver.
 */

#ifndef CDCDSERIAL_H
#define CDCDSERIAL_H

/** \addtogroup usbd_cdc
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include <stdint.h>

#include "usb/common/usb_requests.h"
#include "usb/device/cdc/cdcd_serial_port.h"
#include "usb/device/usbd_driver.h"

/*------------------------------------------------------------------------------
 *         Definitions
 *------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *         Types
 *------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *      Exported functions
 *------------------------------------------------------------------------------*/

extern void cdcd_serial_initialize(uint8_t bInterfaceNb);

extern uint32_t cdcd_serial_request_handler(
		const USBGenericRequest *request);

extern void cdcd_serial_configure_function(
		USBGenericDescriptor *descriptors, uint16_t length);

extern uint32_t cdcd_serial_write(void *data, uint32_t size,
		usbd_xfer_cb_t callback, void *callback_arg);

extern uint32_t cdcd_serial_read(void *data, uint32_t size,
		usbd_xfer_cb_t callback, void *callback_arg);

extern void cdcd_serial_get_line_coding(CDCLineCoding *line_coding);

extern uint8_t cdcd_serial_get_control_line_state(void);

extern uint16_t cdcd_serial_get_serial_state(void);

extern void cdcd_serial_set_serial_state(uint16_t serial_state);

extern uint8_t cdcd_serial_line_coding_is_to_change(CDCLineCoding *line_coding);

extern void cdcd_serial_control_line_state_changed(uint8_t dtr, uint8_t rts);

extern uint8_t cdcd_serial_driver_line_coding_is_to_change(CDCLineCoding *line_coding);

extern void cdcd_serial_driver_control_line_state_changed(uint8_t dtr, uint8_t rts);

/**@}*/

#endif /*#ifndef CDCSERIAL_H*/

