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
 * Collection of methods for using the USB device controller on AT91
 * Microcontrollers.
 *
 * \section Usage
 *
 * Please refer to the corresponding application note.
 * - \ref usbd_framework AT91 USB device framework
 * - \ref usbd_api USBD API
 *
 */

#ifndef USBD_H
#define USBD_H

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "compiler.h"

#include "usb/common/usb_descriptors.h"
#include "usb/common/usb_requests.h"
#include "usb/device/usb_lib_types.h"

/*------------------------------------------------------------------------------
 *      Definitions
 *------------------------------------------------------------------------------*/

/** \addtogroup usbd_interface
 *@{*/

/**
 * \addtogroup usbd_rc USB device API return codes
 *  @{
 * This section lists the return codes for the USB device driver API
 * - \ref USBD_STATUS_SUCCESS
 * - \ref USBD_STATUS_LOCKED
 * - \ref USBD_STATUS_ABORTED
 * - \ref USBD_STATUS_RESET
 */

/** Indicates the operation was successful. */
#define USBD_STATUS_SUCCESS             USBRC_SUCCESS
/** Endpoint/device is already busy. */
#define USBD_STATUS_LOCKED              USBRC_BUSY
/** Operation has been aborted (error or stall). */
#define USBD_STATUS_ABORTED             USBRC_ABORTED
/** Operation has been cancelled (by user). */
#define USBD_STATUS_CANCELED            USBRC_CANCELED
/** Operation has been aborted because the device init/reset/un-configure. */
#define USBD_STATUS_RESET               USBRC_RESET
/** Part of operation successfully done. */
#define USBD_STATUS_PARTIAL_DONE        USBRC_PARTIAL_DONE
/** Operation failed because parameter error */
#define USBD_STATUS_INVALID_PARAMETER   USBRC_PARAM_ERR
/** Operation failed because in unexpected state */
#define USBD_STATUS_WRONG_STATE         USBRC_STATE_ERR
/** Operation failed because SW not supported */
#define USBD_STATUS_SW_NOT_SUPPORTED    USBRC_SW_NOT_SUPPORTED
/** Operation failed because HW not supported */
#define USBD_STATUS_HW_NOT_SUPPORTED    USBRC_HW_NOT_SUPPORTED
/** @}*/

/** \addtogroup usbd_states USB device states
 *  @{
 * This section lists the device states of the USB device driver.
 * - \ref USBD_STATE_SUSPENDED
 * - \ref USBD_STATE_ATTACHED
 * - \ref USBD_STATE_POWERED
 * - \ref USBD_STATE_DEFAULT
 * - \ref USBD_STATE_ADDRESS
 * - \ref USBD_STATE_CONFIGURED
 */

/** The device is currently suspended. */
#define USBD_STATE_SUSPENDED            0
/** USB cable is plugged into the device. */
#define USBD_STATE_ATTACHED             1
/** Host is providing +5V through the USB cable. */
#define USBD_STATE_POWERED              2
/** Device has been reset. */
#define USBD_STATE_DEFAULT              3
/** The device has been given an address on the bus. */
#define USBD_STATE_ADDRESS              4
/** A valid configuration has been selected. */
#define USBD_STATE_CONFIGURED           5
/**  @}*/

/*----------------------------------------------------------------------------
 *         Types
 *----------------------------------------------------------------------------*/

/**
 * Callback used by transfer functions (usbd_read & usbd_write) to notify
 * that a transaction is complete. For MBL transfers, transferred and remaining
 * arguments are not set.
 */
typedef void (*usbd_xfer_cb_t)(void *arg, uint8_t status, uint32_t transferred, uint32_t remaining);

/**@}*/

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

extern void usbd_force_full_speed(void);

extern void usbd_init(void);

extern void usbd_connect(void);

extern void usbd_disconnect(void);

extern uint8_t usbd_write(uint8_t endpoint, const void *data, uint32_t length,
		usbd_xfer_cb_t callback, void *callback_arg);

extern uint16_t usbd_get_data_size(uint8_t endpoint);

extern uint8_t usbd_read(uint8_t endpoint, void *data, uint32_t length,
		usbd_xfer_cb_t callback, void *callback_arg);

extern uint8_t usbd_stall(uint8_t endpoint);

extern void usbd_halt(uint8_t endpoint);

extern void usbd_unhalt(uint8_t endpoint);

extern bool usbd_is_halted(uint8_t endpoint);

extern void usbd_configure_endpoint(const USBEndpointDescriptor *descriptor);

extern void usbd_remote_wakeup(void);

extern void usbd_set_address(uint8_t address);

extern void usbd_set_configuration(uint8_t cfgnum);

extern uint8_t usbd_get_state(void);

extern bool usbd_is_high_speed(void);

extern void usbd_test(uint8_t index);

extern void usbd_suspend_handler(void);
extern void usbd_resume_handler(void);
extern void usbd_reset_handler(void);
extern void usbd_request_handler(uint8_t endpoint,
		const USBGenericRequest *request);

extern void usbd_callbacks_initialized(void);
extern void usbd_callbacks_reset(void);
extern void usbd_callbacks_suspended(void);
extern void usbd_callbacks_resumed(void);
extern void usbd_callbacks_request_received(const USBGenericRequest *request);

#endif /*#ifndef USBD_H*/

