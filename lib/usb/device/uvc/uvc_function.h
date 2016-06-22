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

/** \file
 *  USB Video Class function driver definitions.
 */

#ifndef UVCFUNCTION_H
#define UVCFUNCTION_H

/** \addtogroup usbd_uvc
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include <stdint.h>
#include "usb/device/uvc/uvc_driver.h"

/*------------------------------------------------------------------------------
 *      Global functions
 *------------------------------------------------------------------------------*/

extern void uvc_function_initialize(struct _uvc_driver* uvc_driver);
extern void uvc_function_payload_sent(void *arg, uint8_t state, uint32_t transferred, uint32_t remaining);
extern void uvc_function_get_res(const USBGenericRequest *request);
extern void uvc_function_get_max(const USBGenericRequest *request);
extern void uvc_function_get_min(const USBGenericRequest *request);
extern void uvc_function_get_info(const USBGenericRequest *request);
extern void uvc_function_get_def(const USBGenericRequest *request);
extern void uvc_function_get_cur(const USBGenericRequest *request);
extern void uvc_function_set_cur(const USBGenericRequest *request);
extern uint8_t uvc_function_is_video_on(void);
extern uint8_t uvc_function_get_frame_format(void);
extern void uvc_function_update_frame_idx(uint32_t idx);
/**@}*/

#endif /* UVCDRIVER_H */
