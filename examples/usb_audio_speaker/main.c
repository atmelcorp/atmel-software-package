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
/** \cond usb_audio_speaker
 *  \page usb_audio_speaker USB Audio Speaker Example
 *
 *  \section Purpose
 *
 *  The USB Audio Speaker Example will help you to get familiar with the
 *  USB Device Port(UDP) and CLASSD on SAMA5D2 microcontrollers. Also
 *  it can help you to be familiar with the USB Framework that is used for
 *  rapid development of USB-compliant class drivers such as USB Audio Device
 *  class.
 *
 *  \section Requirements
 *
 *  This package can be used with SAMA5D2-EK and SAMA5D2-XPLAINED that have
 *  both UDP and CLASSD.
 *
 *  \section Description
 *
 *  The demo simulates an USB Desktop Speaker.
 *
 *  When an EK running this program connected to a host (PC for example), with
 *  USB cable, the EK appears as a desktop speaker for the host. Then the host
 *  can play sound through host software. The audio stream from the host is
 *  then sent to the EK, and eventually sent to audio DAC connected to the
 *  amplifier. At the same time, the audio stream received is also sent
 *  back to host from EK for recording.
 *
 *  \section Usage
 *
 *  -# Build the program and download it inside the evaluation board. Please
 *     refer to the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6421.pdf">
 *     SAM-BA User Guide</a>, the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *     GNU-Based Software Development</a> application note or to the
 *     <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *     IAR EWARM User Guide</a>, depending on your chosen solution.
 *  -# On the computer, open and configure a terminal application
 *     (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *    - 115200 bauds
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# Start the application.
 *  -# In the terminal window, the following text should appear:
 *  \code
 *  -- USB Device Audio Speaker Example xxx --
 *  -- SAMxxxxx-xx
 *  -- Compiled: xxx xx xxxx xx:xx:xx --
 *  \endcode
 *  -# When connecting USB cable to windowss, the host
 *     reports a new USB device attachment (if it's the first time you connect
 *     an audio speaker demo board to your host). You can find new
 *     "USB Composite Device" and "USB Audio Device" appear in the hardware
 *     device list.
 *  -# You can play sound in host side through the USB Audio Device, and it
 *     can be heard from the speaker connected to the EK.
 *
 *  \section References
 *  - usb_audio_speaker/main.c
 *  - classd: CLASSD interface driver
 *  - usb: USB Framework, Audio Device Class driver and UDP interface driver
 *      - \ref usbd_framework
 *      - \ref usbd_api
 *      - \ref usbd_audio_speaker
 */

/**
 *  \file
 *
 *  This file contains all the specific code for the
 *  usb_audio_speaker example.
 */

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"

#include "misc/console.h"
#include "misc/led.h"

#include "peripherals/classd.h"
#include "misc/cache.h"
#include "peripherals/pio.h"
#include "peripherals/pit.h"
#include "peripherals/pmc.h"
#include "peripherals/wdt.h"
#include "peripherals/xdmad.h"

#include "usb/device/audio/audd_speaker_driver.h"

#include "main_descriptors.h"
#include "../usb_common/main_usb_common.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

/**  Number of available audio buffers. */
#define BUFFER_NUMBER (128)

/**  Size of one buffer in bytes. */
#define BUFFER_SIZE   ROUND_UP_MULT(AUDDSpeakerDriver_BYTESPERFRAME + \
		AUDDSpeakerDriver_BYTESPERSUBFRAME, L1_CACHE_BYTES)

/**  Delay (in number of buffers) before starting the DAC transmission
     after data has been received. */
#define DAC_DELAY     (2)

/*----------------------------------------------------------------------------
 *         External variables
 *----------------------------------------------------------------------------*/

/** Descriptor list for USB Audio Speaker Device Driver */
extern const USBDDriverDescriptors audd_speaker_driver_descriptors;

/*----------------------------------------------------------------------------
 *         Internal variables
 *----------------------------------------------------------------------------*/

/** ClassD pin instance */
static const struct _pin classd_pins[] = BOARD_CLASSD_PINS;

/**  Data buffers for receiving audio frames from the USB host. */
ALIGNED(L1_CACHE_BYTES)
static uint8_t buffers[BUFFER_NUMBER][BUFFER_SIZE];

/**  Number of samples stored in each data buffer. */
static uint32_t buffer_sizes[BUFFER_NUMBER];

/**  Next buffer in which USB data can be stored. */
static volatile uint32_t in_buffer_index = 0;

/**  Next buffer which should be sent to the DAC. */
static volatile uint32_t out_buffer_index = 0;

/**  Number of buffers that can be sent to the DAC. */
static volatile uint32_t num_buffers_to_send = 0;

/** DMA channel for TX */
static struct _xdmad_channel *classd_dma_tx_channel = NULL;

/** First USB frame flag */
static volatile bool is_first_frame = true;

/** Class D audio playing flag */
static volatile bool is_audio_playing = false;

/*----------------------------------------------------------------------------
 *         Internal functions
 *----------------------------------------------------------------------------*/

/**
 * Configure the CLASSD for audio output.
 */
static void _configure_classd(void)
{
	/* Configure Class D */
	struct _classd_desc classd_desc = {
		.sample_rate = AUDDSpeakerDriver_SAMPLERATE,
		.mode = BOARD_CLASSD_MODE,
		.non_ovr = CLASSD_NONOVR_10NS,
		.swap_channels = false,
		.mono = BOARD_CLASSD_MONO,
		.mono_mode = BOARD_CLASSD_MONO_MODE,
		.left_enable = true,
		.right_enable = true,
	};
	classd_configure(&classd_desc);
	classd_set_left_attenuation(30);
	classd_set_right_attenuation(30);
	classd_volume_unmute(true, true);
	classd_enable_channels(true, true);

	/* DMA Driver initialize */
	xdmad_initialize(false);

	/* Allocate DMA TX channels for CLASSD */
	classd_dma_tx_channel = xdmad_allocate_channel(XDMAD_PERIPH_MEMORY, ID_CLASSD);
	if (!classd_dma_tx_channel) {
		printf("xDMA channel allocation error\n\r");
	} else {
		xdmad_prepare_channel(classd_dma_tx_channel);
	}
}

/**
 * Enable/Disable audio channels
 */
static void audio_play_enable(bool enable)
{
	if (enable) {
		classd_enable_channels(true, true);
	} else {
		classd_disable_channels(true, true);
	}
}

/**
 * Mute/Unmute audio channels
 */
static void audio_play_mute(bool mute)
{
	if (mute) {
		classd_volume_mute(true, true);
	} else {
		classd_volume_unmute(true, true);
	}
}

/* forward declaration */
static void _classd_tx_callback(struct _xdmad_channel *channel, void* p_arg);

/**
 *  \brief Start sending next buffer to Class D using DMA.
 */
static void _classd_dma_start_transfer(void)
{
	void *buffer;
	uint16_t wsize;
	struct _xdmad_cfg xdmad_cfg;

	is_audio_playing = true;

	buffer = buffers[out_buffer_index];
	wsize = buffer_sizes[out_buffer_index];

	out_buffer_index = (out_buffer_index + 1) % BUFFER_NUMBER;
	num_buffers_to_send--;

	cache_clean_region(buffer, wsize);

	xdmad_cfg.ublock_size = wsize / AUDDSpeakerDriver_BYTESPERSUBFRAME;
	xdmad_cfg.src_addr = (uint32_t*)buffer;
	xdmad_cfg.dest_addr = (uint32_t*)&CLASSD->CLASSD_THR;
	xdmad_cfg.cfg.uint32_value = XDMAC_CC_TYPE_PER_TRAN |
		XDMAC_CC_MBSIZE_SINGLE |
		XDMAC_CC_DSYNC_MEM2PER |
		XDMAC_CC_CSIZE_CHK_1 |
		XDMAC_CC_DWIDTH_WORD |
		XDMAC_CC_SIF_AHB_IF0 |
		XDMAC_CC_DIF_AHB_IF1 |
		XDMAC_CC_SAM_INCREMENTED_AM |
		XDMAC_CC_DAM_FIXED_AM;
	xdmad_cfg.block_size = 0;
	xdmad_set_callback(classd_dma_tx_channel, _classd_tx_callback, 0);
	xdmad_configure_transfer(classd_dma_tx_channel, &xdmad_cfg, 0, 0);
	xdmad_start_transfer(classd_dma_tx_channel);
}

/**
 *  \brief DMA TX callback
 */
static void _classd_tx_callback(struct _xdmad_channel *channel, void* p_arg)
{
	p_arg = p_arg; /* dummy */

	if (!xdmad_is_transfer_done(channel))
		return;

	if (num_buffers_to_send == 0) {
		/* End of transmission */
		is_audio_playing = false;
		is_first_frame = true;
		audio_play_enable(false);
		return;
	}

	/* Load next buffer */
	_classd_dma_start_transfer();
}

/*----------------------------------------------------------------------------
 *         Internal functions
 *----------------------------------------------------------------------------*/

/**
 *  Invoked when a frame has been received.
 */
static void frame_received(void* arg, uint8_t status, uint32_t transferred, uint32_t remaining)
{
	/* unused */
	(void)arg;
	(void)remaining;

	if (status == USBD_STATUS_SUCCESS) {
		assert(transferred <= BUFFER_SIZE);
		buffer_sizes[in_buffer_index] = transferred;
		in_buffer_index = (in_buffer_index + 1) % BUFFER_NUMBER;
		num_buffers_to_send++;

		/* Start DAC transmission if necessary */
		if (is_first_frame && num_buffers_to_send > DAC_DELAY) {
			is_first_frame = false;
			audio_play_enable(true);
			_classd_dma_start_transfer();
		}
	} else if (status == USBD_STATUS_ABORTED) {
		/* Error , ABORT, add NULL buffer */
		buffer_sizes[in_buffer_index] = 0;
	} else {
		/* Packet is discarded */
	}

	/* Receive next packet */
	audd_speaker_driver_read(buffers[in_buffer_index],
			AUDDSpeakerDriver_BYTESPERFRAME,
			frame_received, 0);
}

/*----------------------------------------------------------------------------
 *         Callbacks re-implementation
 *----------------------------------------------------------------------------*/

/**
 * Invoked when the configuration of the device changes. Parse used endpoints.
 * \param cfgnum New configuration number.
 */
void usbd_driver_callbacks_configuration_changed(unsigned char cfgnum)
{
	audd_speaker_driver_configuration_change_handler(cfgnum);
}

/**
 * Invoked whenever the active setting of an interface is changed by the
 * host. Reset streaming interface.
 * \param interface Interface number.
 * \param setting Newly active setting.
 */
void usbd_driver_callbacks_interface_setting_changed(unsigned char interface,
		unsigned char setting)
{
	audd_speaker_driver_interface_setting_changed_handler(interface, setting);
}

/**
 *  Invoked whenever a SETUP request is received from the host. Forwards the
 *  request to the standard handler.
 */
void usbd_callbacks_request_received(const USBGenericRequest *request)
{
	audd_speaker_driver_request_handler(request);
}

/**
 *  Invoked when an audio channel get muted or unmuted. Mutes/unmutes the
 *  channel at the DAC level.
 *  \param channel  Channel number that changed.
 *  \param muted    Indicates the new mute status of the channel.
 */
void audd_speaker_driver_mute_changed(uint8_t channel, uint8_t muted)
{
	/* Speaker Master channel */
	if (channel == AUDDSpeakerDriver_MASTERCHANNEL){
		if (muted){
			audio_play_mute(true);
			printf("MuteMaster ");
		} else {
			printf("UnmuteMaster ");
			audio_play_mute(false);
		}
	}
}

/**
 *  Invoked when an audio streaming interface setting changed. Actually control
 *  streaming rate.
 *  \param newSetting  New stream (interface) setting.
 */
void audd_speaker_driver_stream_setting_changed(uint8_t new_setting)
{
	if (new_setting) {
		if (classd_dma_tx_channel)
			xdmad_stop_transfer(classd_dma_tx_channel);
		num_buffers_to_send = 0;
	}
}

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief usb_audio_speaker Application entry point.
 *
 *  Starts the driver and waits for an audio input stream to forward to the DAC.
 */
int main(void)
{
	bool usb_conn = false;
	bool audio_on = false;

	/* Disable watchdog */
	wdt_disable();

	/* Configure console */
	board_cfg_console(0);

	/* Output example information */
	printf("-- USB Device Audio Speaker Example %s --\n\r", SOFTPACK_VERSION);
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	/* configure PIO muxing for ClassD */
	pio_configure(classd_pins, ARRAY_SIZE(classd_pins));

	/* Initialize all USB power (off) */
	usb_power_configure();

	/* Configure Audio */
	_configure_classd();

	/* USB audio driver initialization */
	audd_speaker_driver_initialize(&audd_speaker_driver_descriptors);

	/* connect if needed */
	usb_vbus_configure();

	/* Infinite loop */
	while (1) {
		if (usbd_get_state() < USBD_STATE_CONFIGURED) {
			usb_conn = false;
			continue;
		} else if (!usb_conn) {
			trace_info("USB connected\r\n");

			/* Start Reading the incoming audio stream */
			audd_speaker_driver_read(buffers[in_buffer_index],
					AUDDSpeakerDriver_BYTESPERFRAME,
					frame_received, 0);

			usb_conn = true;
		}

		if (audio_on) {
			if (!is_audio_playing) {
				printf("<stop_playing> ");
				audio_on = false;
			}
		} else {
			if (is_audio_playing) {
				printf("<start_playing> ");
				audio_on = true;
			}
		}
	}
}
