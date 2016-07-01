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

#include "misc/cache.h"
#include "misc/console.h"
#include "misc/led.h"

#include "peripherals/dma.h"

#include "usb/device/audio/audd_speaker_driver.h"

#include "main_descriptors.h"
#include "../usb_common/main_usb_common.h"
#include "audio/audio_device.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#if defined(CONFIG_BOARD_SAMA5D2_XPLAINED)
	#include "config_sama5d2-xplained.h"
#elif defined(CONFIG_BOARD_SAMA5D4_EK)
	#include "config_sama5d4-ek.h"
#else
#error Unsupported board!
#endif

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

/**  Number of available audio buffers. */
#define BUFFER_NUMBER (128)

/**  Size of one buffer in bytes. */
#define BUFFER_SIZE   AUDDSpeakerDriver_BYTESPERFRAME

/**  Delay (in number of buffers) before starting the DAC transmission
     after data has been received. */
#define DAC_DELAY     (10)


/*----------------------------------------------------------------------------
 *         External variables
 *----------------------------------------------------------------------------*/

/** Descriptor list for USB Audio Speaker Device Driver */
extern const USBDDriverDescriptors audd_speaker_driver_descriptors;

/*----------------------------------------------------------------------------
 *         Internal variables
 *----------------------------------------------------------------------------*/

/**  Data buffers for receiving audio frames from the USB host. */
CACHE_ALIGNED static uint8_t buffers[BUFFER_NUMBER][BUFFER_SIZE];

/**  Number of samples stored in each data buffer. */
static uint32_t buffer_sizes[BUFFER_NUMBER];

/**  Next buffer in which USB data can be stored. */
static volatile uint32_t in_buffer_index = 0;

/**  Next buffer which should be sent to the DAC. */
static volatile uint32_t out_buffer_index = 0;

/**  Number of buffers that can be sent to the DAC. */
static volatile uint32_t num_buffers_to_send = 0;


/** First USB frame flag */
static volatile bool is_first_frame = true;

/** audio playing flag */
static volatile bool is_audio_playing = false;

/** audio playing volume */
static uint8_t play_vol = AUDIO_PLAY_MAX_VOLUME/2;

/*----------------------------------------------------------------------------
 *         Internal functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief DMA TX callback
 */
void audio_play_finish_callback(struct dma_channel *channel, void* p_arg);
void audio_play_finish_callback(struct dma_channel *channel, void* p_arg)
{
	p_arg = p_arg; /* dummy */

	if (num_buffers_to_send == 0) {
		/* End of transmission */
		is_audio_playing = false;
		is_first_frame = true;
		audio_enable(&audio_device, false);
		return;
	}


	/* Load next buffer */
	out_buffer_index = (out_buffer_index + 1) % BUFFER_NUMBER;
	num_buffers_to_send--;
	audio_dma_transfer(&audio_device, buffers[out_buffer_index],
			buffer_sizes[out_buffer_index], audio_play_finish_callback);

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
			audio_enable(&audio_device, true);
			is_audio_playing = true;
			out_buffer_index = (out_buffer_index + 1) % BUFFER_NUMBER;
			num_buffers_to_send--;
			audio_dma_transfer(&audio_device, buffers[out_buffer_index],
					buffer_sizes[out_buffer_index], audio_play_finish_callback);
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

static void console_handler(uint8_t key)
{
	switch (key) {
	case '+':
		if (play_vol < AUDIO_PLAY_MAX_VOLUME) {
			play_vol += 10;
			audio_play_set_volume(&audio_device, play_vol);
		}
		break;
	case '-':
		if (play_vol > 10) {
			play_vol -= 10;
			audio_play_set_volume(&audio_device, play_vol);
		}
		break;

	case 'u':
	case 'U':
		audio_play_mute(&audio_device, false);
		break;

	case 'm':
	case 'M':
		audio_play_mute(&audio_device, true);
		break;

	default:
		break;
	}
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
		if (muted) {
			audio_play_mute(&audio_device, true);
			printf("MuteMaster ");
		} else {
			printf("UnmuteMaster ");
			audio_play_mute(&audio_device, false);
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
		audio_dma_stop(&audio_device);
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

	console_set_rx_handler(console_handler);
	console_enable_rx_interrupt();

	/* Output example information */
	console_example_info("USB Device Audio Speaker Example");

	/* Initialize all USB power (off) */
	usb_power_configure();
		
	/* Configure Audio */
	audio_configure(&audio_device);

	/* Configure audio play volume */
	audio_play_set_volume(&audio_device, play_vol);

	/* USB audio driver initialization */
	audd_speaker_driver_initialize(&audd_speaker_driver_descriptors);

	/* connect if needed */
	usb_vbus_configure();

	printf("=========================================================\n\r");
	printf("Input '+' or '-' to increase or decrease volume\n\r");
	printf("Input 'm' or 'u' to mute or unmute sound\n\r");
	printf("=========================================================\n\r");

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
				//printf("<stop_playing> ");
				audio_on = false;
			}
		} else {
			if (is_audio_playing) {
				//printf("<start_playing> ");
				audio_on = true;
			}
		}
	}
}
