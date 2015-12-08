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
 * Implementation of the CDCSetControlLineStateRequest class.
 */

/** \addtogroup usb_cdc
 *@{
 */

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "usb/common/cdc/cdc_requests.h"

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

/**
 *  Notifies if the given request indicates that the DTE signal is present.
 *  \param request Pointer to a USBGenericRequest instance.
 *  \return 1 if the DTE signal is present, otherwise 0.
 */
bool cdc_set_control_line_state_request_is_dte_present(
	const USBGenericRequest *request)
{
	return usb_generic_request_get_value(request) & 0x0001;
}

/**
 *  Notifies if the given request indicates that the device carrier should
 *  be activated.
 *  \param request Pointer to a USBGenericRequest instance.
 *  \return 1 is the device should activate its carrier, 0 otherwise.
 */
bool cdc_set_control_line_state_request_activate_carrier(
	const USBGenericRequest *request)
{
	return usb_generic_request_get_value(request) & 0x0002;
}

/**
 *  Initializes the bitrate, number of stop bits, parity checking and
 *  number of data bits of a CDCLineCoding object.
 *  \param lineCoding Pointer to a CDCLineCoding instance.
 *  \param bitrate Bitrate of the virtual COM connection.
 *  \param stopbits Number of stop bits
 *                  (\ref usb_cdc_stop CDC LineCoding StopBits).
 *  \param parity Parity check type
 *                  (\ref usb_cdc_parity CDC LineCoding ParityChecking).
 *  \param databits Number of data bits.
 */
void cdc_line_coding_initialize(CDCLineCoding *line_coding, uint32_t bitrate,
		uint8_t stopbits, uint8_t parity, uint8_t databits)
{
	line_coding->dwDTERate = bitrate;
	line_coding->bCharFormat = stopbits;
	line_coding->bParityType = parity;
	line_coding->bDataBits = databits;
}

/**@}*/
