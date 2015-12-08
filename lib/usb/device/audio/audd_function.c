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

/** \addtogroup usbd_aud_fun
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "trace.h"

#include "usb/common/audio/aud_requests.h"
#include "usb/device/audio/audd_function.h"
#include "usb/device/audio/audd_speaker_phone.h"
#include "usb/device/usbd_driver.h"
#include "usb/device/usbd.h"

/*----------------------------------------------------------------------------
 *         Internal types
 *----------------------------------------------------------------------------*/

/**
 * \brief Audio speaker driver struct.
 */
typedef struct _AUDDFunction {
	/** Speaker & Phone function */
	AUDDSpeakerPhone drv;
	/** Stream instance for speaker */
	AUDDStream  speaker;
	/** Stream instance for microphone */
	AUDDStream  mic;
} AUDDFunction;

/*----------------------------------------------------------------------------
 *         Internal variables
 *----------------------------------------------------------------------------*/

/** Global USB audio function driver instance. */
static AUDDFunction audd_function;

/*----------------------------------------------------------------------------
 *         Internal functions
 *----------------------------------------------------------------------------*/

/**
 * Callback triggerred after the mute or volume status of the channel has been
 * changed.
 * \param ec        Event code.
 * \param channel   Channel number.
 * \param p_arg      Pointer to AUDDStream instance.
 */
static void audd_function_event_callback(uint32_t ec, uint8_t channel,
		AUDDStream *p_arg)
{
	AUDDFunction *p_audf = &audd_function;
	uint8_t mic = ((uint32_t)p_arg == (uint32_t)(&p_audf->mic));
	if (ec == AUDD_EC_MuteChanged) {
		if (NULL != (void *)audd_function_mute_changed)
			audd_function_mute_changed(mic, channel, p_arg->bmMute);
	}
	else if (ec == AUDD_EC_VolumeChanged) {
		/* Not supported now */
	}
}

/*---------------------------------------------------------------------------
 *         Exported functions
 *---------------------------------------------------------------------------*/

/**
 * Initializes an USB audio speaker device driver, as well as the underlying
 * USB controller.
 */
void audd_function_initialize(uint8_t b_interface)
{
	AUDDFunction *p_audf = &audd_function;
	AUDDSpeakerPhone *p_drv = &p_audf->drv;
	AUDDStream *p_spk = &p_audf->speaker;
	AUDDStream *pMic = &p_audf->mic;

	b_interface = b_interface;

	/* 0: Speaker */
	audd_speaker_phone_initializeStream(
		p_spk, AUDDFunction_MaxNumSpeakerChannels, 0,
		(AUDDStreamEventCallback)audd_function_event_callback,
		(void*)p_spk);
	/* 1: Mic */
	audd_speaker_phone_initializeStream(
		pMic, AUDDFunction_MaxNumMicrophoneChannels, 0,
		(AUDDStreamEventCallback)audd_function_event_callback,
		(void*)pMic);
	/* Audio Driver initialize */
	audd_speaker_phone_initialize(p_drv, p_spk, pMic);

}

/**
 * Configure function with expected descriptors and start functionality.
 * Usually invoked when device is configured.
 * \p_descriptors Pointer to the descriptors for function configure.
 * \wLength      Length of descriptors in number of bytes.
 */
void audd_function_configure(USBGenericDescriptor *p_descriptors,
		uint16_t wLength)
{
	AUDDFunction *p_audf = &audd_function;
	AUDDSpeakerPhone *p_drv = &p_audf->drv;
	audd_speaker_phone_parse_interfaces(p_drv, p_descriptors, wLength);
}

/**
 * Invoked whenever the active setting of an interface is changed by the
 * host. Changes the status of the third LED accordingly.
 * \param interface Interface number.
 * \param setting Newly active setting.
 */
void audd_function_interface_setting_changed_handler(uint8_t interface,
		uint8_t setting)
{
	AUDDFunction *p_audf = &audd_function;
	AUDDSpeakerPhone *p_drv = &p_audf->drv;
	if (setting == 0) audd_speaker_phone_close_stream(p_drv, interface);
	if (NULL != (void *)audd_function_stream_setting_changed) {
		uint8_t mic = (interface == p_drv->pMicrophone->bAsInterface);
		audd_function_stream_setting_changed(mic, setting);
	}
}

/**
 * Handles AUDIO-specific USB requests sent by the host
 * \param request Pointer to a USBGenericRequest instance.
 * \return USBRC_SUCCESS if request is handled.
 */
uint32_t audd_function_request_handler(
	const USBGenericRequest *request)
{
	AUDDFunction *p_audf = &audd_function;
	AUDDSpeakerPhone *p_drv = &p_audf->drv;
	return audd_speaker_phone_request_handler(p_drv, request);
}

/**
 * Reads incoming audio data sent by the USB host into the provided buffer.
 * When the transfer is complete, an optional callback function is invoked.
 * \param buffer Pointer to the data storage buffer.
 * \param length Size of the buffer in bytes.
 * \param callback Optional callback function.
 * \param argument Optional argument to the callback function.
 * \return <USBD_STATUS_SUCCESS> if the transfer is started successfully;
 *         otherwise an error code.
 */
uint8_t audd_function_read(void *buffer, uint32_t length,
		usbd_xfer_cb_t callback, void *argument)
{
	AUDDFunction *p_audf = &audd_function;
	AUDDSpeakerPhone *p_drv = &p_audf->drv;
	return audd_speaker_phone_read(p_drv, buffer, length, callback, argument);
}

/**
 * Initialize Frame List for sending audio data.
 *
 * \param pListInit Pointer to the allocated list for audio write.
 * \param listSize  Circular list size.
 * \param delaySize Start transfer after delaySize frames filled in.
 * \param callback  Optional callback function for transfer.
 * \param argument  Optional callback argument.
 * \return USBD_STATUS_SUCCESS if setup successfully; otherwise an error code.
 */
uint8_t audd_function_setup_write(void * pListInit, uint16_t listSize,
		uint16_t delaySize, usbd_xfer_cb_t callback, void * argument)
{
	AUDDFunction *p_audf = &audd_function;
	AUDDSpeakerPhone *p_drv = &p_audf->drv;
	return audd_speaker_phone_setup_write(p_drv, pListInit, listSize,
			delaySize, callback, argument);
}

/**
 *  Add frame buffer to audio sending list.
 *  \buffer Pointer to data frame to send.
 *  \length Frame size in bytes.
 *  \return USBD_STATUS_SUCCESS if the transfer is started successfully;
 *          otherwise an error code.
 */
uint8_t audd_function_write(void* buffer, uint16_t length)
{
	AUDDFunction *p_audf = &audd_function;
	AUDDSpeakerPhone *p_drv = &p_audf->drv;
	return audd_speaker_phone_write(p_drv, buffer, length);
}

/**@}*/

