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
 *  USB Audio Device Streaming interface with controls.
 *  (3 channels (including master) supported).
 */

/** \addtogroup usbd_audio_speakerphone
 *@{
 *  Implement speakerphone function that combine 1 AC interface, 1 AS interface
 *  for speaker and 1 AS interface for microphone.
 */

#ifndef _AUDD_STREAM_H_
#define _AUDD_STREAM_H_

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include <stdint.h>

#include "usb/device/usbd.h"
#include "usb/device/usbd_driver.h"

/*------------------------------------------------------------------------------
 *         Defines
 *------------------------------------------------------------------------------*/

/** \addtopage usbd_audio_ec Audio Device Event codes
 *      @{
 */
/** Mute status changed */
#define AUDD_EC_MuteChanged         1
/** Volume status changed */
#define AUDD_EC_VolumeChanged       2
/**     @}*/

/*------------------------------------------------------------------------------
 *         Types
 *------------------------------------------------------------------------------*/

/** Callback function for Audio Stream Event */
typedef void (*AUDDStreamEventCallback)(uint32_t ec,
										uint8_t  channel,
										void* pArg);

/**
 * Struct of USB Audio Stream Interface.
 * Support 1 control interface, with I & O stream.
 * Unit ID 0xFF is reserved for not implemented.
 */
typedef struct _AUDDStream {
	/** AudioControl Interface number */
	uint8_t     bAcInterface;
	/** AudioControl Feature Unit ID for IN */
	uint8_t     bFeatureUnitOut;
	/** AudioControl Feature Unit ID for OUT */
	uint8_t     bFeatureUnitIn;
	/** AudioStreaming Interface number */
	uint8_t     bAsInterface;
	/** Streaming OUT endpoint address */
	uint8_t     bEndpointOut;
	/** Streaming IN  endpoint address */
	uint8_t     bEndpointIn;
	/** Number of channels (<=8) */
	uint8_t     bNumChannels;
	/** Mute control bits  (8b) */
	uint8_t     bmMute;
	/** Volume control data */
	uint16_t   *pwVolumes;

	/** Audio Streaming Events Callback */
	AUDDStreamEventCallback fCallback;
	/** Callback arguments */
	void* pArg;
} AUDDStream;

/*------------------------------------------------------------------------------
 *         Functions
 *------------------------------------------------------------------------------*/

extern void audd_stream_initialize(
	AUDDStream * pAuds,
	uint8_t numChannels,
	uint16_t wChannelVolumes [ ],
	AUDDStreamEventCallback fCallback,
	void * pArg);

extern uint32_t audd_stream_change_mute(
	AUDDStream * pAuds,
	uint8_t bChannel,
	uint8_t bMute);

extern uint32_t audd_stream_set_volume(
	AUDDStream * pAuds,
	uint8_t bChannel,
	uint16_t wVolume);

extern uint32_t audd_stream_is_request_accepted(
	AUDDStream *pAuds,
	const USBGenericRequest *pReq);

extern uint32_t audd_stream_read(
	AUDDStream * pAuds,
	void * pData, uint32_t dwSize,
	usbd_xfer_cb_t fCallback,void * pArg);

extern uint32_t audd_stream_setup_write(
	AUDDStream * pAuds,
	void * pListInit, uint16_t listSize,
	uint16_t delaySize,
	usbd_xfer_cb_t callback,void * argument);

extern uint32_t audd_stream_write(
	AUDDStream * pAuds,
	void * pBuffer,uint16_t wLength);

extern uint32_t audd_stream_close(AUDDStream * pStream);

#endif /* _AUDD_STREAM_H_ */

