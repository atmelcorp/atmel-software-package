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

/*------------------------------------------------------------------------------
 *      Includes
 *------------------------------------------------------------------------------*/
#include "chip.h"

#include "trace.h"
#include "misc/cache.h"
#include "usb/common/uvc/usb_video.h"
#include "usb/common/uvc/uvc_descriptors.h"
#include "usb/device/usbd_driver.h"
#include "usb/device/usbd.h"
#include "usb/device/usbd_hal.h"
#include "usb/device/uvc/uvc_function.h"

#include <string.h>

/** Probe & Commit Controls */

static const struct _USBVideoProbeCommitData vidd_probe_data_init =
{
	0, /* bmHint: All parameters fixed: sent by host */
	0x01,   /* bFormatIndex: Format #1 */
	0x01,   /* bFrameIndex: Frame #1 */
	FRAME_INTERVALC(4), /* dwFrameInterval: in 100ns */
	0, /* wKeyFrameRate: not used */
	0, /* wPFrameRate: not used */
	10000, /* wCompQuality: highest */
	0, /* wCompWindowSize: ?K */
	100, /* wDelay: Internal VS latency in ms */
	FRAME_BUFFER_SIZEC(800, 600), /* dwMaxVideoFrameSize: in bytes */
	FRAME_PACKET_SIZE_FS, /* dwMaxPayloadTransferSize: in bytes */
	0, /* dwClockFrequency */
	3, /* bmFramingInfo */
	0, /* bPreferedVersion */
	0, /* bMinVersion */
	0 /* bMaxVersion */
};

CACHE_ALIGNED static struct _USBVideoProbeCommitData vidd_probe_data;

/*-----------------------------------------------------------------------------
 *         Internal variables
 *-----------------------------------------------------------------------------*/

/** Frame size: Width, Height */
static uint32_t frm_width = 320, frm_height = 240;

/** Xfr Maximum packet size */
static uint32_t frm_max_pkt_size = FRAME_PACKET_SIZE_HS * (ISO_HIGH_BW_MODE + 1);

static volatile uint32_t delay;

/** Buffer for USB requests data */
CACHE_ALIGNED static uint8_t p_control_buffer[64];

CACHE_ALIGNED static uint8_t p_header_buffer[FRAME_PACKET_SIZE_HS * (ISO_HIGH_BW_MODE + 1)];

static struct _uvc_driver *uvc_driver;

/*-----------------------------------------------------------------------------
 *      Exported functions
 *-----------------------------------------------------------------------------*/

/*------------ USB Video Device Functions ------------*/

/**
 * Max packet size calculation for High bandwidth transfer\n
 * - Mode 1: last packet is <epSize+1> ~ <epSize*2> bytes\n
 * - Mode 2: last packet is <epSize*2+1> ~ <epSize*3> bytes
 */
static void vidd_update_high_bw_max_packetsize(void)
{
#if (ISO_HIGH_BW_MODE == 1 || ISO_HIGH_BW_MODE == 2)
	uint32_t frm_size = frm_width * frm_height * 2 + FRAME_PAYLOAD_HDR_SIZE;
	uint32_t pkt_size = FRAME_PACKET_SIZE_HS * (ISO_HIGH_BW_MODE + 1);
	uint32_t nb_last = frm_size % pkt_size;

	while(1) {
		nb_last = frm_size % pkt_size;
		if (nb_last == 0 || nb_last > (FRAME_PACKET_SIZE_HS * ISO_HIGH_BW_MODE))
			break;
		pkt_size--;
	}
	frm_max_pkt_size = pkt_size;
#else
	frm_max_pkt_size = FRAME_PACKET_SIZE_HS; // EP size
#endif
}

/**
 * Send USB control status.
 */
static void vidd_status_stage(void *arg, uint8_t status,
		uint32_t transferred, uint32_t remaining)
{
	USBVideoProbeData *pProbe = (USBVideoProbeData *)p_control_buffer;

	memcpy(&vidd_probe_data, &vidd_probe_data_init, sizeof(vidd_probe_data));
	vidd_probe_data.bFormatIndex = pProbe->bFormatIndex;
	vidd_probe_data.bFrameIndex = pProbe->bFrameIndex;
	if (pProbe->dwFrameInterval > FRAME_INTERVALC(30))
		vidd_probe_data.dwFrameInterval = FRAME_INTERVALC(30);
	else
		vidd_probe_data.dwFrameInterval = pProbe->dwFrameInterval;

	uvc_driver->frm_format = pProbe->bFrameIndex;
	switch (pProbe->bFrameIndex) {
	case 1:
		frm_width = VIDCAMD_FW_1;
		frm_height = VIDCAMD_FH_1;
		break;
	case 2:
		frm_width = VIDCAMD_FW_2;
		frm_height = VIDCAMD_FH_2;
		break;
	case 3:
		frm_width = VIDCAMD_FW_3;
		frm_height = VIDCAMD_FH_3;
		break;
	}

	vidd_update_high_bw_max_packetsize();
	usbd_write(0, NULL, 0, NULL, NULL);
}

/**
 * Handle SetCUR request for USB Video Device.
 */
void uvc_function_set_cur(const USBGenericRequest *request)
{
	uint8_t b_cs = USBVideoRequest_GetControlSelector(request);
	uint32_t len;

	trace_info_wp("SetCUR(%d) ", request->wLength);
	if (request->wIndex == VIDCAMD_StreamInterfaceNum) {
		trace_info_wp("VS ");
		switch(b_cs) {
		case VS_PROBE_CONTROL:
			trace_info_wp("PROBE ");
			len = sizeof(USBVideoProbeData);
			if (request->wLength < len)
				len = request->wLength;
			usbd_read(0, p_control_buffer, len,
					vidd_status_stage, NULL);
			break;
		case VS_COMMIT_CONTROL:
			trace_info_wp("COMMIT ");
			len = sizeof(USBVideoProbeData);
			if (request->wLength < len)
				len = request->wLength;
			usbd_read(0, p_control_buffer, len,
					vidd_status_stage, NULL);
			break;
		default:
			usbd_stall(0);
		}
	} else if (request->wIndex == VIDCAMD_ControlInterfaceNum) {
		trace_info_wp("VC ");
	}
	else {
		usbd_stall(0);
	}
}

/**
 * Handle GetCUR request for USB Video Device.
 */
void uvc_function_get_cur(const USBGenericRequest *request)
{
	uint8_t b_cs = USBVideoRequest_GetControlSelector(request);
	uint32_t len;

	trace_info_wp("GetCUR(%d) ", request->wLength);
	if (request->wIndex == VIDCAMD_StreamInterfaceNum) {
		trace_info_wp("VS ");
		switch(b_cs) {
		case VS_PROBE_CONTROL:
			trace_info_wp("PROBE ");
			len = sizeof(USBVideoProbeData);
			if (request->wLength < len) len = request->wLength;
			usbd_write(0, &vidd_probe_data, len,
					NULL, NULL);
			break;
		case VS_COMMIT_CONTROL: /* Returns current state of VS I/F */
			trace_info_wp("COMMIT ");
			usbd_write(0, &(uvc_driver->alternate_interfaces[VIDCAMD_StreamInterfaceNum]), 1,
					NULL, NULL);
			break;
		default:
			usbd_stall(0);
		}
	} else if (request->wIndex == VIDCAMD_ControlInterfaceNum) {
		trace_info_wp("VC ");
	}
	else {
		usbd_stall(0);
	}
}

/**
 * Handle GetDEF request for USB Video Device.
 */
void uvc_function_get_def(const USBGenericRequest *request)
{
	printf("GetDEF(%x,%x,%d)\n\r", request->wIndex, request->wValue, request->wLength);
	usbd_stall(0);
}

/**
 * Handle GetINFO request for USB Video Device.
 */
void uvc_function_get_info(const USBGenericRequest *request)
{
	printf("GetINFO(%x,%x,%d)\n\r", request->wIndex, request->wValue, request->wLength);
	usbd_stall(0);
}

/**
 * Handle GetMIN request for USB Video Device.
 */
void uvc_function_get_min(const USBGenericRequest *request)
{
	printf("GetMin(%x,%x,%d)\n\r", request->wIndex, request->wValue, request->wLength);
	uvc_function_get_cur(request);
}

/**
 * Handle GetMAX request for USB Video Device.
 */
void uvc_function_get_max(const USBGenericRequest *request)
{
	printf("GetMax(%x,%x,%d)\n\r", request->wIndex, request->wValue, request->wLength);
	uvc_function_get_cur(request);
}

/**
 * Handle GetRES request for USB Video Device.
 */
void uvc_function_get_res(const USBGenericRequest *request)
{
	printf("GetRES(%x,%x,%d) ", request->wIndex, request->wValue, request->wLength);
	usbd_stall(0);
}

/**
 * Callback that invoked when USB packet is sent.
 */
void uvc_function_payload_sent(void *arg, uint8_t state,
		uint32_t transferred, uint32_t remaining)
{
	uint32_t pktSize;
	uint8_t *px = p_header_buffer;
	uint32_t frmSize = FRAME_BUFFER_SIZEC(frm_width, frm_height);
	uint8_t *p_video = (uint8_t*)uvc_driver->buf;
	USBVideoPayloadHeader *p_hdr = (USBVideoPayloadHeader*)px;
	uint32_t max_pkt_size = usbd_is_high_speed() ? frm_max_pkt_size : FRAME_PACKET_SIZE_FS;

	if (remaining)
		return;
	pktSize = frmSize - uvc_driver->frm_index;
	p_hdr->bHeaderLength = FRAME_PAYLOAD_HDR_SIZE;
	p_hdr->bmHeaderInfo.B = 0;
	if (pktSize > max_pkt_size - p_hdr->bHeaderLength)
		pktSize = max_pkt_size - p_hdr->bHeaderLength;
	p_video = &p_video[uvc_driver->frm_index];
	uvc_driver->frm_index += pktSize;
	p_hdr->bmHeaderInfo.bm.FID = (uvc_driver->frm_count & 1);
	if (uvc_driver->frm_index >= frmSize) {
		uvc_driver->frm_count ++;
		uvc_driver->frm_index = 0;
		p_hdr->bmHeaderInfo.bm.EoF = 1;

		if (uvc_driver->is_frame_xfring) {
			uvc_driver->is_frame_xfring = 0;
		}
	} else {
		p_hdr->bmHeaderInfo.bm.EoF = 0;

		if (uvc_driver->is_frame_xfring == 0) {
			uvc_driver->is_frame_xfring = 1;
			for (delay = 0; delay < 2000; delay++);
		}
	}
	p_hdr->bmHeaderInfo.bm.EOH =  1;

	usbd_hal_set_transfer_callback(VIDCAMD_IsoInEndpointNum,
			uvc_function_payload_sent, NULL);
	usbd_hal_write_with_header(VIDCAMD_IsoInEndpointNum,
			p_hdr, p_hdr->bHeaderLength, p_video, pktSize);
}

void uvc_function_initialize(struct _uvc_driver* uvc_drv)
{
	uvc_driver = uvc_drv;
}

uint8_t uvc_function_is_video_on(void)
{
	return uvc_driver->is_video_on;
}

uint8_t uvc_function_get_frame_format(void)
{
	return (uint8_t)uvc_driver->frm_format;
}

/**@}*/

