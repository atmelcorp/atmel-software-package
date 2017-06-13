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
#include "mm/cache.h"
#include "usb/common/uvc/usb_video.h"
#include "usb/common/uvc/uvc_descriptors.h"
#include "usb/device/usbd_driver.h"
#include "usb/device/usbd.h"
#include "usb/device/usbd_hal.h"
#include "usb/device/uvc/uvc_function.h"
#include "timer.h"
#include <string.h>

/** Probe & Commit Controls */

static const struct _USBVideoProbeCommitData vidd_probe_data_init =
{
	0, /* bmHint: All parameters fixed: sent by host */
	0x01,   /* bFormatIndex: Format #1 */
	0x01,   /* bFrameIndex: Frame #1 */
	FRAME_INTERVALC(30), /* dwFrameInterval: in 100ns */
	0, /* wKeyFrameRate: not used */
	0, /* wPFrameRate: not used */
	10000, /* wCompQuality: highest */
	0, /* wCompWindowSize: ?K */
	100, /* wDelay: Internal VS latency in ms */
	FRAME_BUFFER_SIZEC(320, 240), /* dwMaxVideoFrameSize: in bytes */
	FRAME_PACKET_SIZE_HS, /* dwMaxPayloadTransferSize: in bytes */
	0, /* dwClockFrequency */
	3, /* bmFramingInfo */
	0, /* bPreferedVersion */
	0, /* bMinVersion */
	0 /* bMaxVersion */
};

/*-----------------------------------------------------------------------------
 *         Internal variables
 *-----------------------------------------------------------------------------*/

CACHE_ALIGNED static struct _USBVideoProbeCommitData vidd_probe_data;

/** Frame size: Width, Height */
static uint32_t frm_width = 320, frm_height = 240;

/** Xfr Maximum packet size */
static uint32_t frm_max_pkt_size = FRAME_PACKET_SIZE_HS * (ISO_HIGH_BW_MODE + 1);

/** Buffer for USB requests data */
CACHE_ALIGNED static uint8_t control_buffer[64];

CACHE_ALIGNED static uint8_t stream_header[32];

static struct _uvc_driver *uvc_driver;

static volatile uint32_t frame_buffer_addr;

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
	USBVideoProbeData *pProbe = (USBVideoProbeData *)control_buffer;

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

	memcpy(&vidd_probe_data, &vidd_probe_data_init, sizeof(vidd_probe_data));
	vidd_update_high_bw_max_packetsize();
	vidd_probe_data.bFormatIndex = pProbe->bFormatIndex;
	vidd_probe_data.bFrameIndex = pProbe->bFrameIndex;
	vidd_probe_data.wCompQuality = 0;
	vidd_probe_data.wDelay = 0;
	vidd_probe_data.dwMaxVideoFrameSize = FRAME_BUFFER_SIZEC(frm_width, frm_height);
	uvc_driver->frm_format = pProbe->bFrameIndex;
	usbd_write(0, NULL, 0, NULL, NULL);
}

/**
 * Handle SetCUR request for USB Video Device.
 */
void uvc_function_set_cur(const USBGenericRequest *request)
{
	uint8_t b_cs = USBVideoRequest_GetControlSelector(request);
	uint32_t len;

	trace_debug_wp("SetCUR(%d) ", request->wLength);
	if (request->wIndex == VIDCAMD_StreamInterfaceNum) {
		trace_debug_wp("VS ");
		switch(b_cs) {
		case VS_PROBE_CONTROL:
			trace_debug_wp("PROBE ");
			len = sizeof(USBVideoProbeData);
			if (request->wLength < len)
				len = request->wLength;
			usbd_read(0, control_buffer, len,
					vidd_status_stage, NULL);
			break;
		case VS_COMMIT_CONTROL:
			trace_debug_wp("COMMIT ");
			len = sizeof(USBVideoProbeData);
			if (request->wLength < len)
				len = request->wLength;
			usbd_read(0, control_buffer, len,
					vidd_status_stage, NULL);
			break;
		default:
			usbd_stall(0);
		}
	} else if (request->wIndex == VIDCAMD_ControlInterfaceNum) {
		trace_debug_wp("VC ");
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

	trace_debug_wp("GetCUR(%d) ", request->wLength);
	if (request->wIndex == VIDCAMD_StreamInterfaceNum) {
		trace_debug_wp("VS ");
		switch(b_cs) {
		case VS_PROBE_CONTROL:
			trace_debug_wp("PROBE ");
			len = sizeof(USBVideoProbeData);
			if (request->wLength < len) len = request->wLength;
			usbd_write(0, &vidd_probe_data, len,
					NULL, NULL);
			break;
		case VS_COMMIT_CONTROL: /* Returns current state of VS I/F */
			trace_debug_wp("COMMIT ");
			usbd_write(0, &(uvc_driver->alternate_interfaces[VIDCAMD_StreamInterfaceNum]), 1,
					NULL, NULL);
			break;
		default:
			usbd_stall(0);
		}
	} else if (request->wIndex == VIDCAMD_ControlInterfaceNum) {
		trace_debug_wp("VC ");
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
	trace_debug_wp("GetDEF(%x,%x,%d)\n\r", request->wIndex, request->wValue, request->wLength);
	usbd_stall(0);
}

/**
 * Handle GetINFO request for USB Video Device.
 */
void uvc_function_get_info(const USBGenericRequest *request)
{
	trace_debug_wp("GetINFO(%x,%x,%d)\n\r", request->wIndex, request->wValue, request->wLength);
	usbd_stall(0);
}

/**
 * Handle GetMIN request for USB Video Device.
 */
void uvc_function_get_min(const USBGenericRequest *request)
{
	trace_debug_wp("GetMin(%x,%x,%d)\n\r", request->wIndex, request->wValue, request->wLength);
	uvc_function_get_cur(request);
}

/**
 * Handle GetMAX request for USB Video Device.
 */
void uvc_function_get_max(const USBGenericRequest *request)
{
	trace_debug_wp("GetMax(%x,%x,%d)\n\r", request->wIndex, request->wValue, request->wLength);
	uvc_function_get_cur(request);
}

/**
 * Handle GetRES request for USB Video Device.
 */
void uvc_function_get_res(const USBGenericRequest *request)
{
	trace_debug_wp("GetRES(%x,%x,%d) ", request->wIndex, request->wValue, request->wLength);
	usbd_stall(0);
}

/**
 * Callback that invoked when USB packet is sent.
 */
void uvc_function_payload_sent(void *arg, uint8_t state,
		uint32_t transferred, uint32_t remaining)
{
	uint32_t dma_transfer_size;
	uint32_t frame_size = FRAME_BUFFER_SIZEC(frm_width, frm_height);
	uint8_t *uncompressed_stream = (uint8_t*)(uvc_driver->buf_start_addr +
									frame_buffer_addr * FRAME_BUFFER_SIZEC(frm_width, frm_height));
	USBVideoPayloadHeader *header = (USBVideoPayloadHeader*)stream_header;
	uint32_t max_pkt_size = usbd_is_high_speed() ? frm_max_pkt_size : FRAME_PACKET_SIZE_FS;
	if (remaining){

		return;
	}
	dma_transfer_size = frame_size - uvc_driver->frm_offset;
	header->bHeaderLength = FRAME_PAYLOAD_HDR_SIZE;
	header->bmHeaderInfo.B = 0;
	if (dma_transfer_size > max_pkt_size - header->bHeaderLength)
		dma_transfer_size = max_pkt_size - header->bHeaderLength;
	uncompressed_stream = &uncompressed_stream[uvc_driver->frm_offset];
	uvc_driver->frm_offset += dma_transfer_size;
	header->bmHeaderInfo.bm.FID = (uvc_driver->frm_count & 1);
	if (uvc_driver->frm_offset >= frame_size) {
		uvc_driver->frm_count++;
		uvc_driver->frm_offset = 0;
		header->bmHeaderInfo.bm.EoF = 1;
		frame_buffer_addr = uvc_driver ->stream_frm_index;
		frame_buffer_addr = (frame_buffer_addr == 0) ?
							(uvc_driver->multi_buffers - 1): (frame_buffer_addr -1);
		if (uvc_driver->is_frame_xfring)
			uvc_driver->is_frame_xfring = 0;
	} else {
		header->bmHeaderInfo.bm.EoF = 0;
	}
	header->bmHeaderInfo.bm.EOH =  1;
	usleep(500);
	usbd_hal_write_with_header(VIDCAMD_IsoInEndpointNum, header,
		header->bHeaderLength, uncompressed_stream, dma_transfer_size);
}

void uvc_function_initialize(struct _uvc_driver* uvc_drv)
{
	uvc_driver = uvc_drv;
	usbd_hal_set_transfer_callback(VIDCAMD_IsoInEndpointNum, uvc_function_payload_sent, NULL);
}

uint8_t uvc_function_is_video_on(void)
{
	return uvc_driver->is_video_on;
}

uint8_t uvc_function_get_frame_format(void)
{
	return (uint8_t)uvc_driver->frm_format;
}

void uvc_function_update_frame_idx(uint32_t idx)
{
	uvc_driver->stream_frm_index = idx;
}

/**@}*/

