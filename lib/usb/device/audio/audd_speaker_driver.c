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
 * \addtogroup usbd_audio_speaker
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "trace.h"

#include "usb/common/audio/aud_requests.h"
#include "usb/device/audio/audd_speaker_driver.h"
#include "usb/device/audio/audd_speaker_phone.h"
#include "usb/device/usbd_driver.h"
#include "usb/device/usbd.h"

/*----------------------------------------------------------------------------
 *         Internal types
 *----------------------------------------------------------------------------*/

/**
 * \brief Audio speaker driver struct.
 */
typedef struct _AUDDSpeakerDriver {
	/** Speaker & Phone function */
	AUDDSpeakerPhone fun;

	/** Stream instance for speaker */
	AUDDStream speaker;

	/** Array for storing the current setting of each interface */
	uint8_t b_alt_interfaces[AUDDSpeakerDriver_NUMINTERFACES];
} AUDDSpeakerDriver;

/*----------------------------------------------------------------------------
 *         Internal variables
 *----------------------------------------------------------------------------*/

/** Global USB audio speaker driver instance. */
static AUDDSpeakerDriver audd_speaker_driver;

/*----------------------------------------------------------------------------
 *         Dummy callbacks
 *----------------------------------------------------------------------------*/

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
static void audd_speaker_event_callback(uint32_t ec, uint8_t channel,
		AUDDStream *arg)
{
	if (ec == AUDD_EC_MuteChanged) {
		LIBUSB_TRACE("AUDD_EC_MuteChanged ");
		audd_speaker_driver_mute_changed(channel, arg->bmMute);
	}
	else if (ec == AUDD_EC_VolumeChanged) {
		/* Not supported now */
		LIBUSB_TRACE("AUDD_EC_VolumeChanged ");
	}
}

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

/**
 * Initializes an USB audio speaker device driver, as well as the underlying
 * USB controller.
 */
void audd_speaker_driver_initialize(const USBDDriverDescriptors *descriptors)
{
	AUDDSpeakerDriver *p_audd = &audd_speaker_driver;
	AUDDSpeakerPhone *p_audf  = &p_audd->fun;
	AUDDStream *p_auds = &p_audd->speaker;

	audd_speaker_phone_initializeStream(
		p_auds, AUDDSpeakerDriver_NUMCHANNELS, 0,
		(AUDDStreamEventCallback)audd_speaker_event_callback, p_auds);

	audd_speaker_phone_initialize(p_audf, p_auds, 0);

	/* Initialize the USB driver */
	usbd_driver_initialize(descriptors, p_audd->b_alt_interfaces, sizeof(p_audd->b_alt_interfaces));
	usbd_init();
}

/**
 * Invoked whenever the active configuration of device is changed by the
 * host.
 * \param cfgnum Configuration number.
 */
void audd_speaker_driver_configuration_change_handler(uint8_t cfgnum)
{
	AUDDSpeakerDriver *p_audd = &audd_speaker_driver;
	AUDDSpeakerPhone *p_audf = &p_audd->fun;
	const USBDDriverDescriptors *p_descriptors = usbd_driver_get_descriptors();
	USBConfigurationDescriptor *p_desc;

	if (cfgnum > 0) {

		/* Parse endpoints for data & notification */
		if (usbd_is_high_speed() && p_descriptors->pHsConfiguration)
			p_desc = (USBConfigurationDescriptor*)p_descriptors->pHsConfiguration;
		else
			p_desc = (USBConfigurationDescriptor*)p_descriptors->pFsConfiguration;

		audd_speaker_phone_parse_interfaces(p_audf,
				(USBGenericDescriptor*)p_desc,
				p_desc->wTotalLength);
	}
}

/**
 * Invoked whenever the active setting of an interface is changed by the
 * host. Changes the status of the third LED accordingly.
 * \param interface Interface number.
 * \param setting Newly active setting.
 */
void audd_speaker_driver_interface_setting_changed_handler(uint8_t interface,
		uint8_t setting)
{
	AUDDSpeakerDriver *p_speakerd = &audd_speaker_driver;
	AUDDSpeakerPhone  *p_audf     = &p_speakerd->fun;

	if (setting == 0) {
		audd_speaker_phone_close_stream(p_audf, interface);
	}

	if (NULL != (void*)audd_speaker_driver_stream_setting_changed)
		audd_speaker_driver_stream_setting_changed(setting);
}

/**
 * Handles audio-specific USB requests sent by the host, and forwards
 * standard ones to the USB device driver.
 * \param request Pointer to a USBGenericRequest instance.
 */
void audd_speaker_driver_request_handler(const USBGenericRequest *request)
{
	AUDDSpeakerDriver *p_audd = &audd_speaker_driver;
	AUDDSpeakerPhone *p_audf  = &p_audd->fun;

	LIBUSB_TRACE("NewReq ");

	/* Handle Audio Class requests */
	if (audd_speaker_phone_request_handler(p_audf, request) == USBRC_SUCCESS) {
		return;
	}

	/* Handle STD requests */
	if (usb_generic_request_get_type(request) == USBGenericRequest_STANDARD) {

		usbd_driver_request_handler(request);
	}
	/* Unsupported request */
	else {

		trace_warning("audd_speaker_driver_request_handler: Unsupported request (%d,%x)\n\r",
		  usb_generic_request_get_type(request),
		  usb_generic_request_get_request(request));
		usbd_stall(0);
	}
}

/**
 * Reads incoming audio data sent by the USB host into the provided
 * buffer. When the transfer is complete, an optional callback function is
 * invoked.
 * \param buffer Pointer to the data storage buffer.
 * \param length Size of the buffer in bytes.
 * \param callback Optional callback function.
 * \param argument Optional argument to the callback function.
 * \return USBD_STATUS_SUCCESS if the transfer is started successfully;
 *         otherwise an error code.
 */
uint8_t audd_speaker_driver_read(void *buffer, uint32_t length,
		usbd_xfer_cb_t callback, void *argument)
{
	AUDDSpeakerDriver *p_audd = &audd_speaker_driver;
	AUDDSpeakerPhone *p_audf  = &p_audd->fun;
	return usbd_read(p_audf->pSpeaker->bEndpointOut,
			buffer, length, callback, argument);
}

/**@}*/
