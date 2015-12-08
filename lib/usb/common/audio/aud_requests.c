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
 *
 * This file implements functions for USB AUDIO class requests.
 */

/** \addtogroup usb_audio
 *@{
 */

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "usb/common/audio/aud_requests.h"

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

/**
 * Returns the ID of the unit or terminal targeted by an USB audio request.
 * \param request  Pointer to a USBGenericRequest instance.
 */
uint8_t aud_generic_request_get_entity(const USBGenericRequest *request)
{
	return (usb_generic_request_get_index(request) >> 8) & 0xff;
}

/**
 * Returns the ID of the interface targeted by an USB audio request.
 * \param request  Pointer to a USBGenericRequest instance.
 */
uint8_t aud_generic_request_get_interface(const USBGenericRequest *request)
{
	return usb_generic_request_get_index(request) & 0xff;
}

/**
 *  Returns the control selector value indicating the target of a Feature Unit
 *  request.
 *  \param request  Pointer to a USBGenericRequest instance.
 *  \sa usb_audio_ctrl_sel USB Audio Control selector values
 */
uint8_t aud_feature_unit_request_get_control(const USBGenericRequest *request)
{
	return (usb_generic_request_get_value(request) >> 8) & 0xff;
}

/**
 *  Returns the channel number of a Feature unit which should be altered by the
 *  given request.
 *  \param request  Pointer to a USBGenericRequest instance.
 */
uint8_t aud_feature_unit_request_get_channel(const USBGenericRequest *request)
{
	return usb_generic_request_get_value(request) & 0xff;
}

/**@}*/
