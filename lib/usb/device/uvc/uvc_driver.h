/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
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


#ifndef UVCDRIVER_H
#define UVCDRIVER_H

/** \addtogroup usbd_composite_hidmsd
 *@{
 */

/*---------------------------------------------------------------------------
 *         Headers
 *---------------------------------------------------------------------------*/

#include "compiler.h"

#include "usb/common/usb_requests.h"
#include "usb/common/uvc/uvc_descriptors.h"
#include "usb/device/usbd_driver.h"
#include "usb/device/usbd.h"

/*-----------------------------------------------------------------------------
 *         Internal Types
 *-----------------------------------------------------------------------------*/

/**
 * \brief USB Video class driver struct.
 */
struct _uvc_driver {
	volatile uint8_t is_video_on;
	volatile uint8_t is_frame_xfring; //=0 default
	uint32_t frm_format;
	uint32_t frm_count;
	uint32_t frm_offset;
	uint32_t stream_frm_index;
	uint32_t buf_start_addr;
	uint8_t  multi_buffers;
	/** Array for storing the current setting of each interface */
	uint8_t alternate_interfaces[4];
};

/*---------------------------------------------------------------------------
 *         Exported functions
 *---------------------------------------------------------------------------*/

extern void uvc_driver_initialize(const USBDDriverDescriptors *descriptors,
		uint32_t buff_addr, uint8_t multi_buffers);

extern void uvc_driver_configuration_changed_handler(uint8_t cfgnum);

extern void uvc_driver_request_handler(const USBGenericRequest *request);

extern void uvc_driver_remote_wakeup(void);

extern void uvc_driver_interface_setting_changed_handler(uint8_t interface,
		uint8_t setting);

/**@}*/
#endif //#ifndef UVCDRIVER_H


