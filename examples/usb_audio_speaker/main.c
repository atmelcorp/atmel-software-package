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

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "audio/audio_device.h"
#include "board.h"
#include "chip.h"
#include "compiler.h"
#include "dma/dma.h"
#include "led/led.h"
#include "main_descriptors.h"
#include "mm/cache.h"
#include "serial/console.h"
#include "trace.h"
#include "../usb_common/main_usb_common.h"
#include "usb/device/audio/audd_speaker_driver.h"

#if defined(CONFIG_BOARD_SAMA5D2_XPLAINED)
	#include "config_sama5d2-xplained.h"
#elif defined(CONFIG_BOARD_SAMA5D3_EK)
	#include "config_sama5d3-ek.h"
#elif defined(CONFIG_BOARD_SAMA5D4_EK)
	#include "config_sama5d4-ek.h"
#elif defined(CONFIG_BOARD_SAM9G15_EK)
	#include "config_sam9xx5-ek.h"
#elif defined(CONFIG_BOARD_SAM9G25_EK)
	#include "config_sam9xx5-ek.h"
#elif defined(CONFIG_BOARD_SAM9G35_EK)
	#include "config_sam9xx5-ek.h"
#elif defined(CONFIG_BOARD_SAM9X25_EK)
	#include "config_sam9xx5-ek.h"
#elif defined(CONFIG_BOARD_SAM9X35_EK)
	#include "config_sam9xx5-ek.h"
#elif defined(CONFIG_BOARD_SAMV71_XPLAINED)
	#include "config_samv71-xplained.h"
#else
#error Unsupported board!
#endif

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

/**  Number of available audio buffers. */
#define BUFFERS (32)

/**  Size of one buffer in bytes. */
#define BUFFER_SIZE ROUND_UP_MULT(AUDDSpeakerDriver_BYTESPERFRAME, L1_CACHE_BYTES)

/**  Delay (in number of buffers) before starting the DAC transmission
     after data has been received. */
#define BUFFER_THRESHOLD (8)

/*----------------------------------------------------------------------------
 *         External variables
 *----------------------------------------------------------------------------*/

/** Descriptor list for USB Audio Speaker Device Driver */
extern const USBDDriverDescriptors audd_speaker_driver_descriptors;

/*----------------------------------------------------------------------------
 *         Internal variables
 *----------------------------------------------------------------------------*/

/**  Data buffers for receiving audio frames from the USB host. */
CACHE_ALIGNED static uint8_t _buffer[BUFFERS][BUFFER_SIZE];

/**  Number of samples stored in each data buffer. */
static uint32_t _samples[BUFFERS];

/**  Audio context */
static struct _audio_ctx {
	uint32_t* samples;
	uint32_t threshold;
	struct {
		uint16_t rx;
		uint16_t tx;
		uint32_t count;
	} circ;
	uint8_t volume;
	bool playing;
} _audio_ctx = {
	.samples = _samples,
	.threshold = BUFFER_THRESHOLD,
	.circ = {
		.rx = 0,
		.tx = 0,
		.count = 0,
	},
	.volume =  (AUDIO_PLAY_MAX_VOLUME * 80) / 100,
	.playing = false,
};

#ifdef PINS_PUSHBUTTONS
/** Pushbutton \#1 pin instance. */
static const struct _pin button_pins[] = PINS_PUSHBUTTONS;
#endif

/*----------------------------------------------------------------------------
 *         Internal functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief Audio TX callback
 */
static int _audio_transfer_callback(void* arg, void* arg2)
{
	struct _audio_desc* desc = (struct _audio_desc*)arg;
	struct _callback _cb;

	if (_audio_ctx.circ.count > 0) {
		_audio_ctx.circ.tx = (_audio_ctx.circ.tx + 1) % BUFFERS;
		_audio_ctx.circ.count--;
		/* Load next buffer */
		callback_set(&_cb, _audio_transfer_callback, desc);
		audio_transfer(desc,
			       _buffer[_audio_ctx.circ.tx],
			       _audio_ctx.samples[_audio_ctx.circ.tx],
			       &_cb);
	} else {
		_audio_ctx.playing = false;
		audio_enable(desc, false);
	}

	return 0;
}

/**
 *  Invoked when a frame has been received.
 */
static void _usb_frame_recv_callback(void* arg, uint8_t status, uint32_t transferred, uint32_t remaining)
{
	struct _audio_desc* desc = (struct _audio_desc*)arg;

	if (status == USBD_STATUS_SUCCESS) {
		if (_audio_ctx.circ.count >= (BUFFERS - 1)) {
			_audio_ctx.circ.tx = (_audio_ctx.circ.tx + 1) % BUFFERS;
			_audio_ctx.circ.count--;
		}

		_audio_ctx.samples[_audio_ctx.circ.rx] = transferred;
		_audio_ctx.circ.rx = (_audio_ctx.circ.rx + 1) % BUFFERS;
		_audio_ctx.circ.count++;

		if (_audio_ctx.circ.count >= _audio_ctx.threshold) {
			if (!_audio_ctx.playing) {
				audio_enable(desc, true);
				_audio_ctx.playing = true;
			}
			if (audio_transfer_is_done(&audio_device)) {
				struct _callback _cb;

				/* Start DAC transmission if necessary */
				callback_set(&_cb, _audio_transfer_callback, desc);
				audio_transfer(desc,
					       _buffer[_audio_ctx.circ.tx],
					       _audio_ctx.samples[_audio_ctx.circ.tx],
					       &_cb);
				_audio_ctx.circ.tx = (_audio_ctx.circ.tx + 1) % BUFFERS;
				_audio_ctx.circ.count--;
			}
		}
	} else if (status == USBD_STATUS_ABORTED) {
		/* Error , ABORT, add NULL buffer */
		_audio_ctx.samples[_audio_ctx.circ.rx] = 0;
	} else {
		/* Packet is discarded */
	}

	/* Receive next packet */
	audd_speaker_driver_read(_buffer[_audio_ctx.circ.rx],
				 AUDDSpeakerDriver_BYTESPERFRAME,
				 _usb_frame_recv_callback, desc);
}

static void console_handler(uint8_t key)
{
	switch (key) {
	case '0':
		_audio_ctx.volume = 0;
		audio_set_volume(&audio_device, _audio_ctx.volume);
		break;
	case '1':
		_audio_ctx.volume = AUDIO_PLAY_MAX_VOLUME;
		audio_set_volume(&audio_device, _audio_ctx.volume);
		break;
	case '+':
		if (_audio_ctx.volume < AUDIO_PLAY_MAX_VOLUME) {
			_audio_ctx.volume += 10;
			audio_set_volume(&audio_device, _audio_ctx.volume);
		}
		break;
	case '-':
		if (_audio_ctx.volume > 10) {
			_audio_ctx.volume -= 10;
			audio_set_volume(&audio_device, _audio_ctx.volume);
		}
		break;

	case 'u':
	case 'U':
		audio_mute(&audio_device, false);
		break;

	case 'm':
	case 'M':
		audio_mute(&audio_device, true);
		break;

	default:
		break;
	}
}

#ifdef PINS_PUSHBUTTONS

/**
 *  \brief Handler for Buttons rising edge interrupt.
 *
 *  Handle process led1 status change.
 */
static void pio_handler(uint32_t group, uint32_t status, void* user_arg)
{
	if (group == button_pins[0].group && (status & button_pins[0].mask)) {
		if (_audio_ctx.volume < AUDIO_PLAY_MAX_VOLUME)
			_audio_ctx.volume += 10;
		else
			_audio_ctx.volume = 0;
		audio_set_volume(&audio_device, _audio_ctx.volume);
	}
}

/**
 *  \brief Configure the Pushbuttons
 *
 *  Configure the PIO as inputs and generate corresponding interrupt when
 *  pressed or released.
 */
static void configure_buttons(void)
{
	/* Adjust debounce filter parameters, use 10 Hz filter */
	pio_set_debounce_filter(10);

	/* Configure PIO */
	pio_configure(&button_pins[0], 1);

	/* Initialize interrupt with its handlers */
	pio_add_handler_to_group(button_pins[0].group, button_pins[0].mask, pio_handler, NULL);

	/* Enable interrupts */
	pio_enable_it(button_pins);
}

#endif /* PINS_PUSHBUTTONS */

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
			audio_mute(&audio_device, true);
			printf("MuteMaster\r\n");
		} else {
			printf("UnmuteMaster\r\n");
			audio_mute(&audio_device, false);
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
		audio_stop(&audio_device);
		_audio_ctx.circ.count = 0;
		_audio_ctx.circ.tx = 0;
		_audio_ctx.circ.rx = 0;
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

	int32_t jitter = 0, _jitter_curr;
	int8_t clock_adjust = 0;

	console_set_rx_handler(console_handler);
	console_enable_rx_interrupt();

	/* Output example information */
	console_example_info("USB Device Audio Speaker Example");

	/* Initialize all USB power (off) */
	usb_power_configure();

	/* Configure Audio */
	audio_configure(&audio_device);

	/* Configure audio play volume */
	audio_set_volume(&audio_device, _audio_ctx.volume);

#ifdef PINS_PUSHBUTTONS
	configure_buttons();
#endif

	/* USB audio driver initialization */
	audd_speaker_driver_initialize(&audd_speaker_driver_descriptors);

	/* connect if needed */
	usb_vbus_configure();

	printf("=========================================================\n\r");
	printf("Input '+' or '-' to increase or decrease volume\n\r");
	printf("Input '0' or '1' to set volume to min / max\n\r");
	printf("Input 'm' or 'u' to mute or unmute sound\n\r");
	printf("=========================================================\n\r");

	/* Infinite loop */
	while (1) {
		if (usbd_get_state() < USBD_STATE_CONFIGURED) {
			usb_conn = false;
			continue;
		}

		_jitter_curr = (_audio_ctx.circ.count - _audio_ctx.threshold);

		if (jitter != _jitter_curr) {
			jitter = _jitter_curr;
			if (jitter > 0 && clock_adjust != 1) {
				/* USB too fast or SSC too slow: faster clock */
				clock_adjust = 1;
				audio_sync_adjust(&audio_device, clock_adjust);
			}
			if (jitter < 0 && clock_adjust != -1) {
				/* USB too slow or SSC too fast: slower clock */
				clock_adjust = -1;
				audio_sync_adjust(&audio_device, clock_adjust);
			}
		}

		if (!usb_conn) {
			trace_info("USB connected\r\n");
			/* Start Reading the incoming audio stream */
			audd_speaker_driver_read(_buffer[_audio_ctx.circ.rx],
					AUDDSpeakerDriver_BYTESPERFRAME,
					_usb_frame_recv_callback, &audio_device);

			usb_conn = true;
		}
	}
}
