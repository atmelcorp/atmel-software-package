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
 *  (3 channels supported).
 */

/** \addtogroup usbd_audio_speakerphone
 *@{
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "trace.h"

#include "usb/common/audio/aud_descriptors.h"
#include "usb/common/audio/aud_requests.h"
#include "usb/common/usb_descriptors.h"
#include "usb/common/usb_requests.h"
#include "usb/device/audio/audd_speaker_phone.h"
#include "usb/device/usbd_hal.h"

/*------------------------------------------------------------------------------
 *         Types
 *------------------------------------------------------------------------------*/

/** Parse data extention for descriptor parsing  */
typedef struct _AUDDParseData {
	/** Pointer to AUDDSpeakerPhone instance */
	AUDDSpeakerPhone * p_audf;

	/** Pointer to found interface descriptor */
	USBInterfaceDescriptor * p_if_desc;
} AUDDParseData;

/** Transfer callback extention */
typedef struct _AUDDXfrExt {
	/** Pointer to AUDDStream instance */
	AUDDStream *stream;

	/** Buffer for USB device to get data from host */
	uint16_t    usb_buffer;

	/** Additional information: Entity */
	uint8_t     entity;

	/** Additional information: Channel */
	uint8_t     channel;
} AUDDXfrExt;

/*------------------------------------------------------------------------------
 *         Internal Variable
 *------------------------------------------------------------------------------*/

/** Transfer data extension */
static AUDDXfrExt audd_xfr_data;

/*------------------------------------------------------------------------------
 *         Internal Functions
 *------------------------------------------------------------------------------*/

/**
 * Parse descriptors: Interface, ISO IN/OUT, Feature Unit IDs.
 * \param desc Pointer to descriptor list.
 * \param p_arg  Argument, pointer to AUDDParseData instance.
 */
static uint32_t audd_speaker_phone_parse(USBGenericDescriptor *desc,
		AUDDParseData *p_arg)
{
	AUDDStream *p_speaker = p_arg->p_audf->pSpeaker;
	AUDDStream *p_mic     = p_arg->p_audf->pMicrophone;
	USBEndpointDescriptor* pEp = (USBEndpointDescriptor*)desc;
	uint8_t bSpeakerDone = 0, bMicDone = 0;

	/* Validate descriptor */
	if (desc->bLength == 0)
		return USBRC_PARAM_ERR;

	/* Log current interface */
	if (desc->bDescriptorType == USBGenericDescriptor_INTERFACE) {
		USBInterfaceDescriptor* p_if = (USBInterfaceDescriptor*)desc;
		/* AudioControl interface */
		if (p_if->bInterfaceClass == AUDControlInterfaceDescriptor_CLASS
			&& p_if->bInterfaceSubClass == AUDControlInterfaceDescriptor_SUBCLASS) {
			p_arg->p_if_desc = p_if;
			if (p_speaker)
				p_speaker->bAcInterface = p_if->bInterfaceNumber;
			if (p_mic)
				p_mic->bAcInterface = p_if->bInterfaceNumber;
		}
		/* AudioStreaming interface with endpoint */
		else if (p_if->bInterfaceClass == AUDStreamingInterfaceDescriptor_CLASS
			&& p_if->bInterfaceSubClass == AUDStreamingInterfaceDescriptor_SUBCLASS) {
			p_arg->p_if_desc = p_if;
		}
		/* Not Audio interface, force end */
		else if (p_arg->p_if_desc) {
			return USBRC_PARTIAL_DONE;
		}
	}

	if (p_arg->p_if_desc) {
		/* Find Control Interface */
		/* Find Entities */
		/* Find Streaming Interface & Endpoints */
		if (desc->bDescriptorType == USBGenericDescriptor_ENDPOINT
			&& (pEp->bmAttributes & 0x3) == USBEndpointDescriptor_ISOCHRONOUS) {
			if (pEp->bEndpointAddress & 0x80 && p_mic) {
				p_mic->bEndpointIn = pEp->bEndpointAddress & 0x7F;
				p_mic->bAsInterface = p_arg->p_if_desc->bInterfaceNumber;
				/* Fixed FU */
				p_mic->bFeatureUnitIn = AUDD_ID_MicrophoneFU;
			}
			else if (p_speaker) {
				p_speaker->bEndpointOut = pEp->bEndpointAddress;
				p_speaker->bAsInterface = p_arg->p_if_desc->bInterfaceNumber;
				/* Fixed FU */
				p_speaker->bFeatureUnitOut = AUDD_ID_SpeakerFU;
			}
		}
	}

	if (p_speaker) {
		if (p_speaker->bAcInterface != 0xFF &&
				p_speaker->bAsInterface != 0xFF &&
				p_speaker->bFeatureUnitOut != 0xFF &&
				p_speaker->bEndpointOut != 0) {
			bSpeakerDone = 1;
		}
	} else {
		bSpeakerDone = 1;
	}

	if (p_mic) {
		if (p_mic->bAcInterface != 0xFF &&
				p_mic->bAsInterface != 0xFF &&
				p_mic->bFeatureUnitIn != 0xFF &&
				p_mic->bEndpointIn != 0) {
			bMicDone = 1;
		}
	} else {
		bMicDone = 1;
	}

	if (bSpeakerDone && bMicDone)
		return USBRC_FINISHED;

	return USBRC_SUCCESS;
}

/**
 * Callback triggered after the new mute status of a channel has been read.
 * Changes the mute status of the given channel accordingly.
 * \param p_data Pointer to AUDDXfrExt (transfer extension data).
 */
static void audd_mute_received(void *arg, uint8_t status,
		uint32_t transferred, uint32_t remaining)
{
	AUDDXfrExt *data = (AUDDXfrExt*)arg;

	audd_stream_change_mute(data->stream, data->channel,
			(uint8_t)data->usb_buffer);
	usbd_write(0, NULL, 0, NULL, NULL);
}

/**
 * Callback triggered after the new volume status of a channel has been read.
 * Changes the volume status of the given channel accordingly.
 * \param p_data Pointer to AUDDXfrExt (transfer extension data).
 */
static void audd_volume_received(void *arg, uint8_t status,
		uint32_t transferred, uint32_t remaining)
{
	AUDDXfrExt *data = (AUDDXfrExt*)arg;

	audd_stream_set_volume(data->stream, data->channel,
			data->usb_buffer);
	usbd_write(0, NULL, 0, NULL, NULL);
}

/**
 * Get Target AUDDStream for control
 * \param p_audf         Pointer to AUDDSpeakerPhone instance.
 * \param bAcInterface  Interface number
 * \param entity       Entity ID
 * \param bChannel      Channel number
 * \return Pointer to AUDDStream instance
 */
static AUDDStream *audd_get_ctl_stream(AUDDSpeakerPhone *p_audf,
		uint8_t b_ac_interface, uint8_t entity, uint8_t channel)
{
	AUDDStream *p_auds = 0;

	if (entity == p_audf->pSpeaker->bFeatureUnitOut ||
			entity == p_audf->pSpeaker->bFeatureUnitIn)
		p_auds = p_audf->pSpeaker;
	else if (entity == p_audf->pMicrophone->bFeatureUnitIn ||
			entity == p_audf->pMicrophone->bFeatureUnitOut)
		p_auds = p_audf->pMicrophone;

	if (p_auds && p_auds->bAcInterface == b_ac_interface &&
			p_auds->bNumChannels >= channel) {
		return p_auds;
	}

	return 0;
}

/**
 * Handle the SET_CUR request.
 * \param p_audf Pointer to AUDDSpeakerPhone instance.
 * \param pReq  Pointer to USBGenericRequest instance.
 */
static void audd_set_cur(AUDDSpeakerPhone *p_audf,
		const USBGenericRequest* pReq)
{
	uint8_t intf = aud_generic_request_get_interface(pReq);
	uint8_t entity = aud_generic_request_get_entity(pReq);
	uint8_t length = usb_generic_request_get_length(pReq);
	uint8_t channel = aud_feature_unit_request_get_channel(pReq);
	uint8_t b_ctrl = aud_feature_unit_request_get_control(pReq);
	AUDDStream *p_auds = audd_get_ctl_stream(p_audf, intf, entity, channel);
	usbd_xfer_cb_t callback = NULL;

	LIBUSB_TRACE("sCUR(E%d, CtlS%d, Ch%d, L%d) ",
			entity, b_ctrl, channel, length);

	/* Set Mute to AC, 1 byte */
	if (b_ctrl == AUDFeatureUnitRequest_MUTE &&
			length == 1 && p_auds) {
		callback = audd_mute_received;
	}
	else if (b_ctrl == AUDFeatureUnitRequest_VOLUME &&
			length == 2 && p_auds && p_auds->pwVolumes) {
		callback = audd_volume_received;
	}

	if (callback) {
		audd_xfr_data.stream = p_auds;
		audd_xfr_data.entity = entity;
		audd_xfr_data.channel = channel;
		usbd_read(0, &audd_xfr_data.usb_buffer, length,
				  callback, &audd_xfr_data);
	} else {
		usbd_stall(0);
	}
}

/**
 * Handle the GET_CUR request.
 * \param p_audf Pointer to AUDDSpeakerPhone instance.
 * \param request  Pointer to USBGenericRequest instance.
 */
static void audd_get_cur(AUDDSpeakerPhone *p_audf, const USBGenericRequest *request)
{
	uint8_t intf     = aud_generic_request_get_interface(request);
	uint8_t entity = aud_generic_request_get_entity(request);
	uint8_t length = usb_generic_request_get_length(request);
	uint8_t channel     = aud_feature_unit_request_get_channel(request);
	uint8_t b_ctrl   = aud_feature_unit_request_get_control(request);
	AUDDStream *p_auds = audd_get_ctl_stream(p_audf, intf, entity, channel);
	bool ok = false;

	LIBUSB_TRACE("gCUR(E%d, CtlS%d, Ch%d, L%d) ",
			entity, b_ctrl, channel, length);

	/* Get Mute 1 byte */
	if (b_ctrl == AUDFeatureUnitRequest_MUTE &&
			length == 1 && p_auds) {
		audd_xfr_data.usb_buffer = (p_auds->bmMute & (1 << channel)) > 0;
		ok = true;
	}
	else if (b_ctrl == AUDFeatureUnitRequest_VOLUME &&
			length == 2 && p_auds && p_auds->pwVolumes) {
		audd_xfr_data.usb_buffer = p_auds->pwVolumes[channel];
		ok = true;
	}

	if (ok) {
		usbd_write(0, &audd_xfr_data.usb_buffer, length,
				NULL, NULL);
	} else {
		usbd_stall(0);
	}
}

/*------------------------------------------------------------------------------
 *         Exported Functions
 *------------------------------------------------------------------------------*/

/**
 * Initialize AUDDStream instance.
 * Note the number of channels excludes the master control, so
 * actual volume array size should be (1 + numChannels).
 * \param p_auds Pointer to AUDDStream instance.
 * \param num_channels     Number of channels in the stream (<31).
 * \param channel_volumes Data array for channel volume values.
 * \param callback Callback function for stream events.
 * \param callback_arg      Pointer to event handler arguments.
 */
void audd_stream_initialize(AUDDStream *p_auds,
		uint8_t num_channels, uint16_t channel_volumes[],
		AUDDStreamEventCallback callback, void *callback_arg)
{
	p_auds->bAcInterface    = 0xFF;
	p_auds->bFeatureUnitOut = 0xFF;
	p_auds->bFeatureUnitIn  = 0xFF;
	p_auds->bAsInterface    = 0xFF;
	p_auds->bEndpointOut    = 0;
	p_auds->bEndpointIn     = 0;

	p_auds->bNumChannels   = num_channels;
	p_auds->bmMute         = 0;
	p_auds->pwVolumes      = channel_volumes;

	p_auds->fCallback = callback;
	p_auds->pArg      = callback_arg;
}

/**
 * Check if the request is accepted.
 * \param p_auds Pointer to AUDDStream instance.
 * \param request  Pointer to a USBGenericRequest instance.
 * \return 1 if accepted.
 */
uint32_t audd_stream_is_request_accepted(AUDDStream *p_auds,
	const USBGenericRequest *request)
{
	uint8_t intf = aud_generic_request_get_interface(request);
	uint8_t entity = aud_generic_request_get_entity(request);
	uint8_t ch = aud_feature_unit_request_get_channel(request);

	if (intf != p_auds->bAcInterface)
		return 0;

	if (ch > p_auds->bNumChannels)
		return 0;

	if (entity != p_auds->bFeatureUnitIn &&
			entity != p_auds->bFeatureUnitOut)
		return 0;

	return 1;
}

/**
 * Change Stream Mute status.
 * \param p_auds     Pointer to AUDDStream instance.
 * \param channel  Channel number.
 * \param bm_mute     1 to mute, 0 to unmute.
 */
uint32_t audd_stream_change_mute(AUDDStream *p_auds,
		uint8_t channel, uint8_t b_mute)
{
	uint32_t bm_mute = (b_mute << channel);

	if (p_auds->bNumChannels < channel)
		return USBRC_PARAM_ERR;

	p_auds->bmMute =  bm_mute;

	if (p_auds->fCallback)
		p_auds->fCallback(AUDD_EC_MuteChanged,
				channel, p_auds->pArg);

	return USBRC_SUCCESS;
}

/**
 * Set Stream Volume status.
 * \param p_auds     Pointer to AUDDStream instance.
 * \param channel  Channel number.
 * \param w_volume   New volume value.
 */
uint32_t audd_stream_set_volume(AUDDStream *p_auds,
		uint8_t channel, uint16_t w_volume)
{
	if (p_auds->pwVolumes == 0)
		return USBRC_PARAM_ERR;

	if (channel > p_auds->bNumChannels)
		return USBRC_PARAM_ERR;

	p_auds->pwVolumes[channel] = w_volume;

	if (p_auds->fCallback) {
		p_auds->fCallback(AUDD_EC_VolumeChanged,
				channel, p_auds->pArg);
	}

	return USBRC_SUCCESS;
}

/**
 * Receives data from the host through the audio function (as speaker).
 * This function behaves like usbd_read.
 * \param p_auds        Pointer to AUDDStream instance.
 * \param p_data  Pointer to the data buffer to put received data.
 * \param dwSize Size of the data buffer in bytes.
 * \param fCallback Optional callback function to invoke when the transfer
 *                  finishes.
 * \param p_arg      Optional argument to the callback function.
 * \return USBD_STATUS_SUCCESS if the read operation has been started normally;
 *         otherwise, the corresponding error code.
 */
uint32_t audd_stream_read( AUDDStream *p_auds, void * p_data, uint32_t dw_size,
		usbd_xfer_cb_t fCallback, void *p_arg)
{
	if (p_auds->bEndpointOut == 0)
		return USBRC_PARAM_ERR;

	return usbd_read(p_auds->bEndpointOut, p_data, dw_size,
					 fCallback, p_arg);
}

/**
 * Initialize Frame List for sending audio data.
 * \param p_auds     Pointer to AUDDStream instance.
 * \param p_list Pointer to the allocated list for audio write.
 * \param list_size  Circular list size.
 * \param delay_size Start transfer after delay_size frames filled in.
 * \param callback  Optional callback function for transfer.
 * \param argument  Optional callback argument.
 * \return USBD_STATUS_SUCCESS if setup successfully; otherwise an error code.
 */
uint32_t audd_stream_setup_write(AUDDStream *p_auds,
		void *p_list, uint16_t list_size, uint16_t delay_size,
		usbd_xfer_cb_t callback, void *argument)
{
	uint32_t error;

	if (p_auds->bEndpointIn == 0)
		return USBRC_STATE_ERR;

	error = usbd_hal_setup_multi_transfer(p_auds->bEndpointIn,
			p_list, list_size, delay_size);
	if (error)
		return error;

	error = usbd_hal_set_transfer_callback(p_auds->bEndpointIn,
			callback, argument);
	return error;
}


/**
 *  Add frame buffer to audio sending list.
 *  \param p_auds   Pointer to AUDDStream instance.
 *  \param buffer Pointer to data frame to send.
 *  \param length Frame size in bytes.
 *  \return USBD_STATUS_SUCCESS if the transfer is started successfully;
 *          otherwise an error code.
 */
uint32_t audd_stream_write(AUDDStream *p_auds, void* buffer, uint16_t length)
{
	if (p_auds->bEndpointIn == 0)
		return USBRC_STATE_ERR;

	return usbd_hal_write(p_auds->bEndpointIn, buffer, length);
}

/**
 * Close the stream. All pending transfers are canceled.
 * \param stream Pointer to AUDDStream instance.
 */
uint32_t audd_stream_close(AUDDStream *stream)
{
	uint32_t bm_eps = 0;

	/* Close output stream */
	if (stream->bEndpointIn) {
		bm_eps |= 1 << stream->bEndpointIn;
	}

	/* Close input stream */
	if (stream->bEndpointOut) {
		bm_eps |= 1 << stream->bEndpointOut;
	}

	usbd_hal_reset_endpoints(bm_eps, USBRC_CANCELED, 1);

	return USBRC_SUCCESS;
}

/*
 *          Audio Speakerphone functions
 */

/**
 * Initialize AUDDStream instance.
 * Note the number of channels excludes the master control, so
 * actual volume array size should be (1 + numChannels).
 * \param p_auds Pointer to AUDDStream instance.
 * \param numChannels Number of channels in the stream (excluding master,<31).
 * \param channel_volumes Data array for channel volume values,
 *                        must include master (1 + numChannels).
 * \param fCallback callback function for stream control events.
 * \param p_arg      Pointer to event handler arguments.
 */
void audd_speaker_phone_initializeStream(AUDDStream *p_auds,
		uint8_t numChannels, uint16_t channel_volumes[],
		AUDDStreamEventCallback callback, void *p_arg)
{
	p_auds->bAcInterface    = 0xFF;
	p_auds->bFeatureUnitOut = 0xFF;
	p_auds->bFeatureUnitIn  = 0xFF;
	p_auds->bAsInterface    = 0xFF;
	p_auds->bEndpointOut    = 0;
	p_auds->bEndpointIn     = 0;

	p_auds->bNumChannels   = numChannels;
	p_auds->bmMute         = 0;
	p_auds->pwVolumes      = channel_volumes;

	p_auds->fCallback = callback;
	p_auds->pArg      = p_arg;
}

/**
 * Initialize AUDDSpeakerPhone instance.
 * \param p_audf       Pointer to AUDDSpeakerPhone instance.
 * \param pUsbd       Pointer to USBDDriver instance.
 * \param pSpeaker    Pointer to speaker streaming interface.
 * \param pMicrophone Pointer to microphone streaming interface.
 */
void audd_speaker_phone_initialize(AUDDSpeakerPhone *p_audf, AUDDStream *p_speaker,
		AUDDStream *p_microphone)
{
	p_audf->pSpeaker    = p_speaker;
	p_audf->pMicrophone = p_microphone;
}

/**
 * Parse USB Audio streaming information for AUDDStream instance.
 * \param p_audf        Pointer to AUDDSpeakerPhone instance.
 * \param p_descriptors Pointer to descriptor list.
 * \param length     Descriptor list size in bytes.
 */
const USBGenericDescriptor *audd_speaker_phone_parse_interfaces(AUDDSpeakerPhone *p_audf,
		USBGenericDescriptor *p_descriptors, uint32_t length)
{
	AUDDParseData data;

	data.p_audf = p_audf;
	data.p_if_desc = 0;

	return usb_generic_descriptor_parse(p_descriptors, length,
			(USBDescriptorParseFunction)audd_speaker_phone_parse,
			&data);
}

/**
 * Close the stream. All pending transfers are canceled.
 * \param p_audf        Pointer to AUDDSpeakerPhone instance.
 * \param b_interface   Stream interface number
 */
uint32_t audd_speaker_phone_close_stream(AUDDSpeakerPhone *p_audf,
		uint32_t b_interface)
{
	if (p_audf->pSpeaker->bAsInterface == b_interface) {
//        usbd_hal_reset_endpoints(1 << p_audf->pSpeaker->bEndpointOut,
//                          USBRC_CANCELED, 1);
	}
	else if (p_audf->pMicrophone->bAsInterface == b_interface) {
//        usbd_hal_reset_endpoints(1 << p_audf->pMicrophone->bEndpointIn,
//                          USBRC_CANCELED, 1);
	}

	return USBRC_SUCCESS;
}

/**
 *  Handles audio-specific USB requests sent by the host
 *  \param p_audf    Pointer to AUDDSpeakerPhone instance.
 *  \param request Pointer to a USBGenericRequest instance.
 *  \return USBRC_PARAM_ERR if not handled.
 */
uint32_t audd_speaker_phone_request_handler(AUDDSpeakerPhone *p_audf,
		const USBGenericRequest* request)
{
	if (usb_generic_request_get_type(request) != USBGenericRequest_CLASS)
		return USBRC_PARAM_ERR;

	LIBUSB_TRACE("Aud ");

	switch (usb_generic_request_get_request(request)) {
	case AUDGenericRequest_SETCUR:
		audd_set_cur(p_audf, request);
		break;
	case AUDGenericRequest_GETCUR:
		audd_get_cur(p_audf, request);
		break;

	default:
		return USBRC_PARAM_ERR;
	}

	return USBRC_SUCCESS;
}

/**
 * Receives data from the host through the audio function (as speaker).
 * This function behaves like usbd_read.
 * \param p_audf        Pointer to AUDDSpeakerPhone instance.
 * \param p_data  Pointer to the data buffer to put received data.
 * \param size Size of the data buffer in bytes.
 * \param callback Optional callback function to invoke when the transfer
 *                  finishes.
 * \param p_arg      Optional argument to the callback function.
 * \return USBD_STATUS_SUCCESS if the read operation has been started normally;
 *         otherwise, the corresponding error code.
 */
uint32_t audd_speaker_phone_read(AUDDSpeakerPhone *p_audf,
		void *p_data, uint32_t size,
		usbd_xfer_cb_t callback, void *p_arg)
{
	if (p_audf->pSpeaker == 0)
		return USBRC_PARAM_ERR;

	if (p_audf->pSpeaker->bEndpointOut == 0)
		return USBRC_PARAM_ERR;

	return usbd_read(p_audf->pSpeaker->bEndpointOut, p_data, size,
			callback, p_arg);
}

/**
 * Initialize Frame List for sending audio data.
 * \param p_audf     Pointer to AUDDSpeakerPhone instance.
 * \param p_list_init Pointer to the allocated list for audio write.
 * \param list_size  Circular list size.
 * \param delay_size Start transfer after delay_size frames filled in.
 * \param callback  Optional callback function for transfer.
 * \param argument  Optional callback argument.
 * \return USBD_STATUS_SUCCESS if setup successfully; otherwise an error code.
 */
uint32_t audd_speaker_phone_setup_write(AUDDSpeakerPhone *p_audf,
		void *p_list, uint16_t list_size, uint16_t delay_size,
		usbd_xfer_cb_t callback, void *argument)
{
	uint32_t error;

	if (p_audf->pMicrophone == 0)
		return USBRC_PARAM_ERR;

	if (p_audf->pMicrophone->bEndpointIn == 0)
		return USBRC_STATE_ERR;

	error = usbd_hal_setup_multi_transfer(p_audf->pMicrophone->bEndpointIn,
			p_list, list_size, delay_size);
	if (error)
		return error;

	error = usbd_hal_set_transfer_callback( p_audf->pMicrophone->bEndpointIn,
			callback, argument);
	return error;
}


/**
 *  Add frame buffer to audio sending list.
 *  \param p_audf   Pointer to AUDDSpeakerPhone instance.
 *  \param buffer Pointer to data frame to send.
 *  \param length Frame size in bytes.
 *  \return USBD_STATUS_SUCCESS if the transfer is started successfully;
 *          otherwise an error code.
 */
uint32_t audd_speaker_phone_write(AUDDSpeakerPhone *p_audf,
		void* buffer, uint16_t length)
{
	if (p_audf->pSpeaker == 0)
		return USBRC_PARAM_ERR;

	if (p_audf->pSpeaker->bEndpointIn == 0)
		return USBRC_STATE_ERR;

	return usbd_hal_write(p_audf->pSpeaker->bEndpointIn,
			buffer, length);
}

/**@}*/

