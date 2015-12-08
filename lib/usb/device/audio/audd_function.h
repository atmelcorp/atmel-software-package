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
/** \file */
#ifndef AUDDFUNCTION_H
#define AUDDFUNCTION_H
/** \addtogroup usbd_aud_fun
 *@{
 */

/*-----------------------------------------------------------------------------
 *         Headers
 *---------------------------------------------------------------------------*/

#include "usb/common/usb_requests.h"
#include "usb/device/audio/audd_speaker_phone.h"
#include "usb/device/usbd_driver.h"
#include "usb/device/usbd.h"

/*-----------------------------------------------------------------------------
 *         Definitions
 *---------------------------------------------------------------------------*/

/** \addtogroup audd_fun_desc USBD Audio Function definitions
 *      @{
 */
/** ID for Speaker */
#define AUDDFunction_Speaker                    0
/** ID for Microphone */
#define AUDDFunction_Microhpone                 1
/** Max number of interfaces that supported by the function (AC + 2*AS) */
#define AUDDFunction_MaxNumInterfaces           3
/** Max number of channels supported by speaker stream (including master) */
#define AUDDFunction_MaxNumSpeakerChannels      3
/** Max number of channels supported by microphone stream (including master) */
#define AUDDFunction_MaxNumMicrophoneChannels   3

/** Endpoint polling interval 2^(x-1) * 125us */
#define AUDDFunction_HS_INTERVAL                0x04
/** Endpoint polling interval 2^(x-1) * ms */
#define AUDDFunction_FS_INTERVAL                0x01

/** Playback input terminal ID */
#define AUDDFunction_INPUTTERMINAL              AUDD_ID_SpeakerIT
/** Playback output terminal ID */
#define AUDDFunction_OUTPUTTERMINAL             AUDD_ID_SpeakerOT
/** Playback feature unit ID */
#define AUDDFunction_FEATUREUNIT                AUDD_ID_SpeakerFU
/** Record input terminal ID */
#define AUDDFunction_INPUTTERMINAL_REC          AUDD_ID_MicrophoneIT
/** Record output terminal ID */
#define AUDDFunction_OUTPUTTERMINAL_REC         AUDD_ID_MicrophoneOT
/** Record feature unit ID */
#define AUDDFunction_FEATUREUNIT_REC            AUDD_ID_MicrophoneFU

/**     @}*/

/*-----------------------------------------------------------------------------
 *         Exported functions
 *---------------------------------------------------------------------------*/

extern void audd_function_initialize(uint8_t bInterface);
extern void audd_function_configure(
	USBGenericDescriptor * pDescriptors, uint16_t wLength);
extern void audd_function_interface_setting_changed_handler(
	uint8_t interface,uint8_t setting);
extern uint32_t audd_function_request_handler(const USBGenericRequest * request);
extern uint8_t audd_function_read(
	void * buffer, uint32_t length,
	usbd_xfer_cb_t callback, void * argument);
extern uint8_t audd_function_setup_write(
	void * pListInit, uint16_t listSize, uint16_t delaySize,
	usbd_xfer_cb_t callback,void * argument);
extern uint8_t audd_function_write(void * buffer, uint16_t length);

extern void audd_function_mute_changed(
	uint8_t idMic, uint8_t ch, uint8_t mute);
extern void audd_function_stream_setting_changed(
	uint8_t idMic, uint8_t setting);

/**@}*/
#endif // #define AUDDFUNCTIONDRIVER_H

