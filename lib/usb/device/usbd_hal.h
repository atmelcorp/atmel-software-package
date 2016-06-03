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

#ifndef USBD_HAL_H
#define USBD_HAL_H

/**
 *  \file
 *
 *  This file defines functions for USB Device Hardware Access Level.
 */

/** \addtogroup usbd_hal
 *@{*/

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>

#include "usb/common/usb_descriptors.h"
#include "usb/common/usb_requests.h"
#include "usb/device/usbd.h"

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

/**
 * \brief Buffer struct used for multi-buffer-listed transfer.
 *
 * The driver can process 255 bytes of buffers or buffer list window.
 */
struct _usbd_transfer_buffer {
	uint8_t *buffer;      /**< Pointer to frame buffer */
	uint16_t size;        /**< Size of the frame (up to 64K-1) */
	uint16_t transferred; /**< Bytes transferred */
	uint16_t buffered;    /**< Bytes in FIFO */
	uint16_t remaining;   /**< Bytes remaining */
};

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

extern void usbd_hal_init(void);

extern void usbd_hal_connect(void);

extern void usbd_hal_disconnect(void);

extern void usbd_hal_remote_wakeup(void);

extern void usbd_hal_set_configuration(uint8_t cfgnum);

extern void usbd_hal_set_address(uint8_t address);

extern void usbd_hal_force_full_speed(void);

extern bool usbd_hal_is_high_speed(void);

extern void usbd_hal_suspend(void);

extern void usbd_hal_activate(void);

extern void usbd_hal_reset_endpoints(uint32_t endpoints, uint8_t status,
		bool keep_cfg);

extern uint8_t usbd_hal_configure(const USBEndpointDescriptor *descriptor);

extern uint8_t usbd_hal_set_transfer_callback(uint8_t endpoint,
		usbd_xfer_cb_t callback, void *callback_arg);

extern uint8_t usbd_hal_setup_multi_transfer(uint8_t endpoint,
		struct _usbd_transfer_buffer *list, uint16_t list_size,
		uint16_t start_offset);

extern uint8_t usbd_hal_write(uint8_t endpoint,
		const void *data, uint32_t length);

extern uint8_t usbd_hal_write_with_header(uint8_t endpoint,
		const void *header, uint32_t header_length,
		const void *data, uint32_t data_length);

extern uint16_t usbd_hal_get_data_size(uint8_t endpoint);

extern uint8_t usbd_hal_read(uint8_t endpoint,
		void *data, uint32_t length);

extern uint8_t usbd_hal_stall(uint8_t endpoint);

extern bool usbd_hal_halt(uint8_t endpoint);

extern void usbd_hal_unhalt(uint8_t endpoint);

extern bool usbd_hal_is_halted(uint8_t endpoint);

extern void usbd_hal_test(uint8_t index);

/**@}*/

#endif // #define USBD_HAL_H
