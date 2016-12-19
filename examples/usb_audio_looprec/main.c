/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, Atmel Corporation
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
/** \cond usb_audio_looprec
 *  \page usb_audio_looprec USB Audio Loopback-Recorder Example
 *
 *  \section Purpose
 *
 *  The USB Audio Loopback-Recorder Example will help you to get
 *  familiar with the USB Device Port(UDP) and DACC on SAMv7 micro-controllers.
 *  Also it can help you to be familiar with the USB Framework that is used for
 *  rapid development of USB-compliant class drivers such as USB Audio Device
 *  class.
 *
 *  \section Requirements
 *
 *  This package can be used with SAMv71 Xplained board that have both
 *  UDP.
 *
 *  \section Description
 *
 *  The demo simulates an USB Desktop Speaker with Microphone which actually
 *  does not "speak out" but loop back the sound as microphone input.
 *
 *  When an Xplained board running this program connected to a host (PC for
 *  example), with USB cable, the Xplained board appears as a desktop speaker
 *  for the host. Then the host can play sound through host software. The audio
 *  stream from the host is then sent to the Xplained board. At the same time,
 *  the audio stream received is also sent back to host from Xplained board for
 *  recording.
 *
 *  \section Usage
 *
 *  -# Build the program and download it inside the SAM V71 Xplained Ultra board.
 *     Please refer to the Getting Started with SAM V71 Microcontrollers.pdf
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
 *  -- USB Device Audio LoopREC Example xxx --
 *  -- SAMxxxxx-xx
 *  -- Compiled: xxx xx xxxx xx:xx:xx --
 *  \endcode
 *  -# When connecting USB cable to windows, the host reports a new USB device
 * attachment (if it's the first time you connect an audio speaker demo board to
 * your host).
 * You can find new "USB Composite Device" and "USB Audio Device" appear in the
 * hardware device list.
 *  -# You can play sound in host side through the USB Audio Device.
 *     When playing sound, you can also record through the USB Audio Device on
 *     the host.
 *
 *  \section References
 *  - usb_audio_looprec/main.c
 *  - ssc: SSC interface driver
 *  - usb: USB Framework, Audio Device Class driver and UDP interface driver
 *      - \ref usbd_framework
 *         - \ref usbd_api
 *      - \ref usbd_audio_rec_drv
 *
 */

/**
 *  \file
 *
 *  This file contains all the specific code for the
 *  usb_audio_looprec example.
 */

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "board.h"
#include "chip.h"
#include "gpio/pio.h"
#include "led/led.h"
#include "main_descriptors.h"
#include "mm/cache.h"
#include "serial/console.h"
#include "trace.h"
#include "../usb_common/main_usb_common.h"
#include "usb/device/audio/audd_speaker_phone_driver.h"

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

/**  Number of available audio buffers. */
#define BUFFERS (8)

/**  Size of one buffer in bytes. */
#define BUFFER_SIZE ROUND_UP_MULT(AUDDSpeakerPhoneDriver_BYTESPERFRAME, L1_CACHE_BYTES)

/*----------------------------------------------------------------------------
 *         External variables
 *----------------------------------------------------------------------------*/

/** Descriptor list for USB Audio SpeakerPhone Driver */
extern const USBDDriverDescriptors audd_speaker_phone_driver_descriptors;

/*----------------------------------------------------------------------------
 *         Internal variables
 *----------------------------------------------------------------------------*/

/**  Data buffers for receiving audio frames from the USB host. */
CACHE_ALIGNED static uint8_t buffers[BUFFERS][BUFFER_SIZE];

/**  Next buffer in which USB data can be stored. */
static volatile uint32_t in_buffer_index = 0;

/**  Current state of the playback stream interface. */
static volatile bool is_play_active = false;

/**  Current state of the record stream interface. */
static volatile bool is_rec_active = false;


/*----------------------------------------------------------------------------
 *         Internal functions
 *----------------------------------------------------------------------------*/

/**
 *  Invoked when a frame has been received.
 */
static void _usb_frame_rcv_callback(void *arg, uint8_t status, uint32_t transferred, uint32_t remaining)
{
	if (status == USBD_STATUS_SUCCESS) {
		/* Loopback! add this buffer to write list */
		if (is_rec_active) {
			audd_speaker_phone_driver_write(buffers[in_buffer_index],
					transferred);
		}

		/* Update input status data */
		in_buffer_index = (in_buffer_index + 1) % BUFFERS;

	} else if (status == USBD_STATUS_ABORTED) {
		/* Error , ABORT, add NULL buffer */
		in_buffer_index = (in_buffer_index + 1) % BUFFERS;
	} else {
		/* Packet is discarded */
	}

	/* Receive next packet */
	audd_speaker_phone_driver_read(buffers[in_buffer_index],
			AUDDSpeakerPhoneDriver_BYTESPERFRAME,
			_usb_frame_rcv_callback, NULL); // No optional argument
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
	audd_speaker_phone_driver_configuration_change_handler(cfgnum);
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
	audd_speaker_phone_driver_interface_setting_changed_handler(interface, setting);
}

/**
 *  Invoked whenever a SETUP request is received from the host. Forwards the
 *  request to the standard handler.
 */
void usbd_callbacks_request_received(const USBGenericRequest *request)
{
	audd_speaker_phone_driver_request_handler(request);
}

/**
 *  Invoked when an audio channel get muted or unmuted. Mutes/unmutes the
 *  channel at the DAC level.
 *  \param mic      Microphone/Speaker stream changed.
 *  \param channel  Channel number that changed.
 *  \param muted    Indicates the new mute status of the channel.
 */
void audd_speaker_phone_driver_mute_changed(uint8_t mic,
		uint8_t channel, uint8_t muted)
{
	/* Speaker Master channel */
	if (!mic && channel == AUDDSpeakerPhoneDriver_MASTERCHANNEL) {
		if (muted)
			trace_info("MuteMaster ");
		else
			trace_info("UnmuteMaster ");
	}
}

/**
 *  Invoked when an audio streaming interface setting changed.
 *  Audio stream is automatically reset.
 *  Actually control streaming rate.
 *  \param mic         Microphone/Speaker stream changed.
 *  \param newSetting  New stream (interface) setting.
 */
void audd_speaker_phone_driver_stream_setting_changed(uint8_t mic,
		uint8_t new_setting)
{
	/* Speaker stream */
	if (!mic)
		is_play_active = (new_setting > 0);
	else
		is_rec_active = (new_setting > 0);
}

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief usb_audio_looprec Application entry point.
 *
 *  Starts the driver and waits for an audio input stream to forward to the DAC.
 */
int main(void)
{
	bool play_on = false, rec_on = false;

	/* Output example information */
	console_example_info("USB Device Audio LoopREC Example");

	/* Initialize all USB power (off) */
	usb_power_configure();

	/* USB audio driver initialization */
	audd_speaker_phone_driver_initialize(&audd_speaker_phone_driver_descriptors);

	/* connect if needed */
	usb_vbus_configure();

	/* Infinite loop */
	while (1) {
		if (usbd_get_state() < USBD_STATE_CONFIGURED)
			continue;

		if (play_on) {
			if (is_play_active == 0) {
				printf("plyE ");
				play_on = false;
			}
		}
		else if (is_play_active) {
			/* Try to Start Reading the incoming audio stream */
			audd_speaker_phone_driver_read(buffers[in_buffer_index],
					AUDDSpeakerPhoneDriver_BYTESPERFRAME,
					_usb_frame_rcv_callback, NULL);
			printf("plyS ");
			play_on = true;
		}

		if (rec_on) {
			if (is_rec_active == 0) {
				printf("recE ");
				rec_on = false;
			}
		} else if (is_rec_active) {
			printf("recS ");
			rec_on = true;
		}
	}
}
/** \endcond */
