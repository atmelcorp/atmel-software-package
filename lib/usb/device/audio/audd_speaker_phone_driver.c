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
 * \addtogroup usbd_audio_speakerphone
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "trace.h"

#include "usb/common/audio/aud_requests.h"
#include "usb/device/audio/audd_speaker_phone_driver.h"
#include "usb/device/usbd_hal.h"

/*------------------------------------------------------------------------------
 *         Internal types
 *------------------------------------------------------------------------------*/

/**
 * Structs of USB Audio Stream Function Interface.
 */
typedef struct _AUDDStream {

	/* -- USB Interface settings -- */
	/** Audio Control Interface Number */
	uint8_t  b_ac_interface;
	/** Audio Streaming Interface Number */
	uint8_t  b_as_interface;
	/** Audio Streaming endpoint address */
	uint8_t  b_ep_num;
	/** Audio Control Unit ID */
	uint8_t  b_unit_id;

	/* -- Channel settings -- */
	/** Number of channels (including master 0, max 32) */
	uint16_t  b_num_channels;
	/** Mute Controls bitmap */
	uint16_t  bm_mute_controls;
	/** Volume Controls (Master,L,R..) array */
	uint16_t *p_volumes;
} AUDDStream;

/**
 * \brief Audio SpeakerPhone driver internal state.
 */
typedef struct _AUDDSpeakerPhoneDriver {

	/** Intermediate storage variable for the mute status of a stream */
	uint8_t    muted;
	/** Array for storing the current setting of each interface. */
	uint8_t    interfaces[AUDDSpeakerPhoneDriverDescriptors_NUMINTERFACES];
	/** Audio Speaker interface */
	AUDDStream speaker;
	/** Audio Microphone interface */
	AUDDStream mic;
} AUDDSpeakerPhoneDriver;

/*------------------------------------------------------------------------------
 *         Internal variables
 *------------------------------------------------------------------------------*/

/** Global USB audio SpeakerPhone driver instance. */
static AUDDSpeakerPhoneDriver audd_speaker_phone_driver;

/*------------------------------------------------------------------------------
 *         Internal functions
 *------------------------------------------------------------------------------*/

/**
 * Parse descriptors: Interrupt IN, Bulk EP IN/OUT.
 * \param desc Pointer to descriptor.
 * \param arg  Argument, pointer to AUDDSpeakerPhoneDriver instance.
 */
static uint32_t audd_speaker_phone_parse(USBGenericDescriptor* desc,
		AUDDSpeakerPhoneDriver* arg)
{
	/* Not a valid descriptor */
	if (desc->bLength == 0) {
		return USBD_STATUS_INVALID_PARAMETER;
	}
	/* Parse endpoint descriptor */
	if (desc->bDescriptorType == USBGenericDescriptor_ENDPOINT) {
		USBEndpointDescriptor *pEP = (USBEndpointDescriptor*)desc;
		if (pEP->bmAttributes == USBEndpointDescriptor_ISOCHRONOUS) {
			if (pEP->bEndpointAddress & 0x80)
				arg->mic.b_ep_num = pEP->bEndpointAddress & 0x7F;
			else
				arg->speaker.b_ep_num = pEP->bEndpointAddress;
		}
	}
	return 0;
}

/**
 * Callback triggered after the new mute status of a channel has been read
 * by AUDDSpeakerPhoneDriver_SetFeatureCurrentValue. Changes the mute status
 * of the given channel accordingly.
 * \param arg Number of the channel whose mute status has changed.
 */
static void audd_speaker_phone_mute_received(void *arg, uint8_t status,
		uint32_t transferred, uint32_t remaining)
{
	uint32_t channel = (uint32_t)arg;

	/* unused */
	(void)status;
	(void)transferred;
	(void)remaining;

	AUDDSpeakerPhoneDriver *p_audd = &audd_speaker_phone_driver;
	AUDDStream *p_auds;

	if ((uint8_t)(channel >> 8) ==
		AUDDSpeakerPhoneDriverDescriptors_OUTPUTTERMINAL_REC) {
		p_auds = &p_audd->mic;
	}
	else {
		p_auds = &p_audd->speaker;
	}

	if (p_audd->muted != p_auds->bm_mute_controls) {
		p_auds->bm_mute_controls = p_audd->muted;
		audd_speaker_phone_driver_mute_changed(0, channel, p_audd->muted);
	}
	usbd_write(0, 0, 0, 0, 0);
}

/**
 * Handle the SET_CUR request.
 * \param pReq Pointer to USBGenericRequest instance.
 */
static void audd_speaker_phone_set_cur(const USBGenericRequest* pReq)
{
	AUDDSpeakerPhoneDriver *p_audd = &audd_speaker_phone_driver;
	uint8_t b_if     = aud_generic_request_get_interface(pReq);
	uint8_t b_entity = aud_generic_request_get_entity(pReq);
	uint8_t b_length = usb_generic_request_get_length(pReq);
	uint8_t b_ch     = aud_feature_unit_request_get_channel(pReq);
	uint8_t b_ctrl   = aud_feature_unit_request_get_control(pReq);
	uint8_t b_set = 0;
	AUDDStream *p_auds = 0;

	LIBUSB_TRACE("sCUR(E%d, CtlS%d, Ch%d, L%d) ",
			b_entity, b_ctrl, b_ch, b_length);

	/* Only AC.FeatureUnit accepted */
	if (b_ctrl == AUDFeatureUnitRequest_MUTE
		&& b_length == 1) {

		if (b_entity == p_audd->speaker.b_unit_id)
			p_auds = &p_audd->speaker;
		else if (b_entity == p_audd->mic.b_unit_id)
			p_auds = &p_audd->mic;

		if (p_auds != 0
			&& b_if == p_auds->b_ac_interface
			&& b_ch <= p_auds->b_num_channels) {
			b_set = 1;
		}
	}

	if (b_set) {
		uint32_t argument = b_ch | (b_entity << 8);
		usbd_read(0, &p_audd->muted, sizeof(uint8_t),
				audd_speaker_phone_mute_received,
				(void*)argument);
	}
	else {

		usbd_stall(0);
	}

}

/**
 * Handle the GET_CUR request.
 * \param pReq Pointer to USBGenericRequest instance.
 */
static void audd_speaker_phone_get_cur(const USBGenericRequest *pReq)
{
	AUDDSpeakerPhoneDriver *p_audd = &audd_speaker_phone_driver;
	uint8_t b_if     = aud_generic_request_get_interface(pReq);
	uint8_t b_entity = aud_generic_request_get_entity(pReq);
	uint8_t b_length = usb_generic_request_get_length(pReq);
	uint8_t b_ch     = aud_feature_unit_request_get_channel(pReq);
	uint8_t b_ctrl   = aud_feature_unit_request_get_control(pReq);
	uint8_t b_get = 0;
	AUDDStream *p_auds = 0;

	LIBUSB_TRACE("gCUR(E%d, CtlS%d, Ch%d, L%d) ",
			b_entity, b_ctrl, b_ch, b_length);

	/* Only AC.FeatureUnit accepted */
	if (b_ctrl == AUDFeatureUnitRequest_MUTE
		&& b_length == 1) {

		if (b_entity == p_audd->speaker.b_unit_id)
			p_auds = &p_audd->speaker;
		else if (b_entity == p_audd->mic.b_unit_id)
			p_auds = &p_audd->mic;

		if (p_auds != 0
			&& b_if == p_auds->b_ac_interface
			&& b_ch <= p_auds->b_num_channels) {
			b_get = 1;
		}
	}

	if (b_get) {

		p_audd->muted = p_auds->bm_mute_controls;
		usbd_write(0, &p_audd->muted, sizeof(uint8_t), 0, 0);
	}
	else {

		usbd_stall(0);
	}
}

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

/**
 * Initializes an USB audio SpeakerPhone device driver, as well as the underlying
 * USB controller.
 */
void audd_speaker_phone_driver_initialize(const USBDDriverDescriptors *pDescriptors)
{
	AUDDSpeakerPhoneDriver *p_audd = &audd_speaker_phone_driver;

	/* Initialize SpeakerPhone channels */
	p_audd->speaker.b_num_channels = 3;
	p_audd->speaker.bm_mute_controls = 0;
	p_audd->speaker.p_volumes = 0;

	p_audd->mic.b_num_channels = 1;
	p_audd->mic.bm_mute_controls = 0;
	p_audd->mic.p_volumes = 0;

	p_audd->mic.b_ac_interface = AUDDSpeakerPhoneDriverDescriptors_CONTROL;
	p_audd->mic.b_as_interface = AUDDSpeakerPhoneDriverDescriptors_STREAMINGIN;
	p_audd->mic.b_ep_num = 0;
	p_audd->mic.b_unit_id = AUDDSpeakerPhoneDriverDescriptors_FEATUREUNIT_REC;

	p_audd->speaker.b_ac_interface = AUDDSpeakerPhoneDriverDescriptors_CONTROL;
	p_audd->speaker.b_as_interface = AUDDSpeakerPhoneDriverDescriptors_STREAMING;
	p_audd->speaker.b_ep_num = 0;
	p_audd->speaker.b_unit_id = AUDDSpeakerPhoneDriverDescriptors_FEATUREUNIT;

	/* Initialize the USB driver */
	usbd_driver_initialize(pDescriptors, p_audd->interfaces, sizeof(p_audd->interfaces));
	usbd_init();

}

/**
 * Invoked whenever the active configuration of device is changed by the
 * host.
 * \param cfgnum Configuration number.
 */
void audd_speaker_phone_driver_configuration_change_handler(uint8_t cfgnum)
{
	AUDDSpeakerPhoneDriver *p_audd = &audd_speaker_phone_driver;
	const USBDDriverDescriptors *pDescriptors = usbd_driver_get_descriptors();
	USBConfigurationDescriptor *pDesc;

	if (cfgnum > 0) {

		/* Parse endpoints for data & notification */
		if (usbd_is_high_speed() && pDescriptors->pHsConfiguration)
			pDesc = (USBConfigurationDescriptor*)pDescriptors->pHsConfiguration;
		else
			pDesc = (USBConfigurationDescriptor*)pDescriptors->pFsConfiguration;

		usb_generic_descriptor_parse((USBGenericDescriptor*)pDesc,
				pDesc->wTotalLength,
				(USBDescriptorParseFunction)audd_speaker_phone_parse,
				p_audd);
	}
}

/**
 * Invoked whenever the active setting of an interface is changed by the
 * host. Changes the status of the third LED accordingly.
 * \param interface Interface number.
 * \param setting Newly active setting.
 */
void audd_speaker_phone_driver_interface_setting_changed_handler(uint8_t interface,
		uint8_t setting)
{
	AUDDSpeakerPhoneDriver *p_audd = &audd_speaker_phone_driver;

	if (interface == p_audd->speaker.b_as_interface) {
		/* reset ISO OUT ep */
		if (setting == 0 && p_audd->speaker.b_ep_num) {
			usbd_hal_reset_endpoints(1 << p_audd->speaker.b_ep_num,
					USBD_STATUS_CANCELED, 1);
		}
		audd_speaker_phone_driver_stream_setting_changed(0, setting);
	}
	if (interface == p_audd->mic.b_as_interface) {
		/* reset ISO IN ep */
		if (setting == 0 && p_audd->mic.b_ep_num) {
			usbd_hal_reset_endpoints(1 << p_audd->mic.b_ep_num,
					USBD_STATUS_CANCELED, 1);
		}
		audd_speaker_phone_driver_stream_setting_changed(1, setting);
	}
}


/**
 *  Handles audio-specific USB requests sent by the host, and forwards
 *  standard ones to the USB device driver.
 *  \param request Pointer to a USBGenericRequest instance.
 */
void audd_speaker_phone_driver_request_handler(const USBGenericRequest *request)
{
	LIBUSB_TRACE("NewReq ");

	/* Check if this is a class request */
	if (usb_generic_request_get_type(request) == USBGenericRequest_CLASS) {

		/* Check if the request is supported */
		switch (usb_generic_request_get_request(request)) {

			case AUDGenericRequest_SETCUR:

				audd_speaker_phone_set_cur(request);
				break;

			case AUDGenericRequest_GETCUR:

				audd_speaker_phone_get_cur(request);
				break;

			default:

				trace_warning("audd_speaker_phone_driver_request_handler: Unsupported request (%d)\n\r",
						  usb_generic_request_get_request(request));
				usbd_stall(0);
		}
	}
	/* Check if this is a standard request */
	else if (usb_generic_request_get_type(request) == USBGenericRequest_STANDARD) {

		/* Forward request to the standard handler */
		usbd_driver_request_handler(request);
	}
	/* Unsupported request type */
	else {

		trace_warning("audd_speaker_phone_driver_request_handler: Unsupported request type (%d)\n\r",
				  usb_generic_request_get_type(request));
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
uint8_t audd_speaker_phone_driver_read(void *buffer, uint32_t length,
		usbd_xfer_cb_t callback, void *argument)
{
	AUDDSpeakerPhoneDriver *p_audd = &audd_speaker_phone_driver;

	if (p_audd->speaker.b_ep_num == 0)
		return USBRC_STATE_ERR;

	return usbd_read(p_audd->speaker.b_ep_num, buffer, length,
			callback, argument);
}

/**
 * Initialize Frame List for sending audio data.
 *
 * \param p_list Pointer to the allocated list for audio write.
 * \param listSize  Circular list size.
 * \param delaySize Start transfer after delaySize frames filled in.
 * \param callback  Optional callback function for transfer.
 * \param argument  Optional callback argument.
 * \return USBD_STATUS_SUCCESS if setup successfully; otherwise an error code.
 */
uint8_t audd_speaker_phone_driver_setup_write(void * p_list, uint16_t listSize,
		uint16_t delaySize, usbd_xfer_cb_t callback, void *argument)
{
	AUDDSpeakerPhoneDriver *p_audd = &audd_speaker_phone_driver;
	uint8_t error;

	if (p_audd->mic.b_ep_num == 0)
		return USBRC_STATE_ERR;

	error = usbd_hal_setup_multi_transfer(p_audd->mic.b_ep_num,
			p_list, listSize, delaySize);
	if (error)
		return error;

	error = usbd_hal_set_transfer_callback(p_audd->mic.b_ep_num,
			callback, argument);
	return error;
}

/**
 *  Add frame buffer to audio sending list.
 *  \buffer Pointer to data frame to send.
 *  \length Frame size in bytes.
 *  \return USBD_STATUS_SUCCESS if the transfer is started successfully;
 *          otherwise an error code.
 */
uint8_t audd_speaker_phone_driver_write(void* buffer, uint16_t length)
{
	AUDDSpeakerPhoneDriver *p_audd = &audd_speaker_phone_driver;

	if (p_audd->mic.b_ep_num == 0)
		return USBRC_STATE_ERR;

	return usbd_hal_write(p_audd->mic.b_ep_num, buffer, length);
}

/**@}*/
