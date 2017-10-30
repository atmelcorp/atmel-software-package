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
/** \cond usb_hid_aud
 *  \page usb_hid_aud USB HID(Keyboard)+Audio(Speaker) Example
 *
 *  \section Purpose
 *
 *  The HID Audio Composite Example will help you to get familiar with the
 *  USB Device Port(UDP) and CLASSD on samA5 microcontrollers. Also
 *  it can help you to be familiar with the USB Framework that is used for
 *  rapid development of USB-compliant class drivers such as USB Composite
 *  HID and Audio classes.
 *
 *  \section Requirements
 *
 *  This package can be used with SAMA5D2x evaluation kits that have both
 *  UDP and CLASSD.
 *
 *  \section win_drv_update Windows Driver Update
 *
 * The composite device is generally supported by Microsoft windows, but some
 * patches are needed for muti-interface functions such as CDC & Audio. The
 * example composite devices are tested under windows XP (SP3). For CDC
 * serial port, additional windows driver file (CompositeCDCSerial.inf) can
 * be found at
 * libraries\\usb\\device\\composite\\drv\\CompositeCDCSerial.inf.
 *
 * The following is alternate update to fix the composite device support
 * on windows XP:
 *
 * \subsection install_win_sp3 Install Windows Service Pack 3 (SP3)
 *
 * All the fixes for USB generic driver are included in window XP service pack
 * 3. It can be found at
 * http://technet.microsoft.com/zh-cn/windows/bb794714(en-us).aspx .
 *
 * \subsection install_win_hotfix Install Windows Hot Fixes
 *
 * Two hot fixes are necessary for window to recognize the composite device
 * correctly:
 *
 * -# http://support.microsoft.com/kb/814560
 * -# http://support.microsoft.com/kb/918365
 *
 *  \section Description
 *
 * The demo simulates a USB device that integrates HID Keyboard and Audio
 * Desktop Speaker function.
 *
 * When an EK running this program connected to a host (PC for example), with
 * USB cable, host will notice the attachment of a USB device (USB Composite
 * Device) with a USB Humen Interface Device and a USB Audio Device.
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
 *  -- USB HID + Audio Device Example xxx --
 *  -- SAMxxxxx-xx
 *  -- Compiled: xxx xx xxxx xx:xx:xx --
 *  \endcode
 *  -# When connecting USB cable to windows, the LED blinks, and the host
 *     reports a new USB device attachment (if it's the first time you connect
 *     an %audio speaker demo board to your host). You can find new
 *     "USB Composite Device" and "USB Audio Device" appear in the hardware
 *     device list.
 *  -# You can play sound in host side through the USB Audio Device, and it
 *     can be heard from the earphone connected to the EK.
 *
 *  \section References
 *  - usb_hid_aud/main.c
 *  - pio: Pin configurations and peripheral configure.
*  - classd: CLASSD interface driver
 *  - usb: USB Framework, HID, Audio function driver and UDP interface driver
 *      - \ref usbd_framework
 *         - \ref usbd_api
 *      - \ref usbd_composite "composite"
 *         - \ref usbd_composite_drv
 *      - \ref usbd_aud "audio"
 *         - \ref usbd_audio_rec_drv
 *  - projects: more detailed information for HID(Keyboard) and Audio(Speaker)
 *      - \ref usb_core
 *      - \ref usb_audio_speaker, \ref usb_audio_headphone
 *
 */

/**
 *  \file
 *
 *  This file contains all the specific code for the
 *  usb_iad_hid_aud example.
 */

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "audio/audio_device.h"
#include "board.h"
#include "chip.h"
#include "chip_pins.h"
#include "gpio/pio.h"
#include "led/led.h"
#include "main_descriptors.h"
#include "mm/cache.h"
#include "serial/console.h"
#include "trace.h"
#include "../usb_common/main_usb_common.h"
#include "usb/device/audio/audd_function.h"
#include "usb/device/composite/hid_audd_driver.h"
#include "usb/device/hid/hidd_keyboard.h"

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

/*- HID */
/** Number of keys used in the example. */
#define NUM_KEYS       (3)

/** Num lock LED index. */
#define LED_NUMLOCK    LED_RED

/*- Audio */
/**  Number of available audio buffers. */
#define BUFFERS (32)

/**  Size of one buffer in bytes. */
#define BUFFER_SIZE ROUND_UP_MULT(AUDDSpeakerDriver_BYTESPERFRAME, L1_CACHE_BYTES)

/**  Delay in ms for starting the DAC transmission
     after a frame has been received. */
#define BUFFER_THRESHOLD (8)

/*----------------------------------------------------------------------------
 *         External variables
 *----------------------------------------------------------------------------*/

/** Descriptor list for USB Audio Speaker Device Driver */
extern const USBDDriverDescriptors hid_audd_driver_descriptors;

/*----------------------------------------------------------------------------
 *         Internal variables
 *----------------------------------------------------------------------------*/

/*- HID */

#ifdef PIN_PUSHBUTTON_1
/** Push button pin to configure for the applicatino. */
static struct _pin pin_push_button = PIN_PUSHBUTTON_1;
#endif


/** Array of key codes produced by each button. */
static uint8_t key_codes[NUM_KEYS] = {
	HIDKeypad_T,
	HIDKeypad_U,
	HIDKeypad_NUMLOCK,
};

/** Current status (pressed or not) for each key. */
static bool key_status[NUM_KEYS];

/*- Audio */
/**  Data buffers for receiving audio frames from the USB host. */
CACHE_ALIGNED_DDR static uint8_t _buffer[BUFFERS][ROUND_UP_MULT(BUFFER_SIZE, L1_CACHE_BYTES)];

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
	.threshold = 8,
	.circ = {
		.rx = 0,
		.tx = 0,
		.count = 0,
	},
	.volume =  AUDIO_PLAY_MAX_VOLUME / 2,
	.playing = false,
};

/*----------------------------------------------------------------------------
 *         Internal functions
 *----------------------------------------------------------------------------*/
/**
 *  \brief Audio TX callback
 */
static int _audio_transfer_callback(void* arg1, void* arg2)
{
	struct _audio_desc* desc = (struct _audio_desc*)arg1;
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
 * Monitor keyboard buttons & Update key status in HID driver
 */
static void hidd_keyboard_process_keys(void)
{
	uint32_t i;
	uint8_t pressed_keys[NUM_KEYS];
	uint8_t pressed_keys_size = 0;
	uint8_t released_keys[NUM_KEYS];
	uint8_t released_keys_size = 0;

	/* Monitor buttons */
	if (console_is_rx_ready()) {
		uint8_t key = console_get_char();
		switch(key) {
			case '1':
			case '2':
				i = key - '1' + 1;
				key_status[i] = ! key_status[i];
				if (key_status[i]) {
					/* Key press simulation */
					trace_info("Key %u pressed\n\r", (unsigned)i);
					pressed_keys[pressed_keys_size] = key_codes[i];
					pressed_keys_size ++;
					hidd_keyboard_remote_wakeup();
				} else {
					/* Key release simulation */
					trace_info("Key %u released\n\r", (unsigned)i);
					released_keys[released_keys_size] = key_codes[i];
					released_keys_size++;
				}
				break;
			default:
				console_put_char(key);
		}
	}

#ifdef PIN_PUSHBUTTON_1
	/* Check if button state has changed */
	bool is_button_pressed = !pio_get(&pin_push_button);
	if (is_button_pressed != key_status[0]) {
		/* Update button state */
		key_status[0] = !key_status[0];
		if (!is_button_pressed) {
			/* Key has been pressed */
			trace_info("BP has been pressed\n\r");
			pressed_keys[pressed_keys_size] = key_codes[0];
			pressed_keys_size++;
			hidd_keyboard_remote_wakeup();

		} else {
			/* Key has been released */
			trace_info("BP has been released\n\r");
			released_keys[released_keys_size] = key_codes[0];
			released_keys_size++;
		}
	}
#endif

	/* Update key status in the HID driver if necessary */
	if (pressed_keys_size != 0 || released_keys_size != 0) {
		uint8_t status;
		do {
			status = hidd_keyboard_change_keys(pressed_keys,
									pressed_keys_size,
									released_keys,
									released_keys_size);
			} while (status != USBD_STATUS_SUCCESS);
	}
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
				audio_enable(&audio_device, true);
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
	audd_function_read(_buffer[_audio_ctx.circ.rx],
				 AUDDSpeakerDriver_BYTESPERFRAME,
				 _usb_frame_recv_callback, desc);
}

/*----------------------------------------------------------------------------
 *         Callbacks re-implementation
 *----------------------------------------------------------------------------*/

/*-------------------------------------------
 *      USB Device Driver callbacks
 *-------------------------------------------*/

/**
 * Invoked when the configuration of the device changes. Parse used endpoints.
 * \param cfgnum New configuration number.
 */
void usbd_driver_callbacks_configuration_changed(unsigned char cfgnum)
{
	hid_audd_driver_configuration_changed_handler(cfgnum);
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
	hid_audd_driver_interface_setting_changed_handler(interface, setting);
}

/**
 *  Invoked whenever a SETUP request is received from the host. Forwards the
 *  request to the standard handler.
 */
void usbd_callbacks_request_received(const USBGenericRequest *request)
{
	hid_audd_driver_request_handler(request);
}

/*-------------------------------------------
 *      USB Function driver callbacks
 *-------------------------------------------*/

/**
 *  Invoked when an audio channel get muted or unmuted. Mutes/unmutes the
 *  channel at the DAC level.
 *  \param mic      Microphone/Speaker stream changed.
 *  \param channel  Channel number that changed.
 *  \param muted    Indicates the new mute status of the channel.
 */
void audd_function_mute_changed(uint8_t mic, uint8_t channel, uint8_t muted)
{
	if (mic)
		return;

	/* Speaker Master channel */
	if (channel == AUDD_CH_Master) {
		if (muted) {
			audio_mute(&audio_device, true);
			trace_info("MuteMaster ");
		} else {
			trace_info("UnmuteMaster ");
			audio_mute(&audio_device, false);
		}
	}
}

/**
 *  Invoked when an audio streaming interface setting changed. Actually control
 *  streaming rate.
 *  \param mic         1 to indicate microphone mute changed.
 *  \param new_setting  New stream (interface) setting.
 */
void audd_function_stream_setting_changed(uint8_t mic, uint8_t new_setting)
{
	mic = mic; /* dummy */
	if (new_setting) {
		audio_stop(&audio_device);
		_audio_ctx.circ.count = 0;
		_audio_ctx.circ.rx = 0;
		_audio_ctx.circ.tx = 0;
	}
}

/**
 * Invoked when the status of the keyboard LEDs changes. Turns the num. lock
 * LED on or off.
 * \param num_lock_status Indicates the current status of the num. lock key.
 * \param caps_lock_status Indicates the current status of the caps lock key.
 * \param scroll_lock_status Indicates the current status of the scroll lock key
 */
void hidd_keyboard_callbacks_leds_changed(
	uint8_t num_lock_status,
	uint8_t caps_lock_status,
	uint8_t scroll_lock_status)
{

	caps_lock_status = caps_lock_status; /* dummy */
	scroll_lock_status = scroll_lock_status; /* dummy */
	/* Num. lock */
	if (num_lock_status)
		led_set(LED_NUMLOCK);
	else
		led_clear(LED_NUMLOCK);
}

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief usb_iad_hid_aud Application entry point.
 *
 *  Starts the driver and waits for an audio input stream to forward to the DAC.
 */
int main(void)
{
	bool usb_conn = false;

	/* Output example information */
	console_example_info("USB HID + Audio Device Example");

	/* Initialize all USB power (off) */
	usb_power_configure();

	/* ----- HID Function Initialize */
	printf( "-- : DBG key 1 2 used as buttons\n\r" );
	printf( "-- : 1st press to push, 2nd press to release\n\r" );

#ifdef PIN_PUSHBUTTON_1
	/* Initialize key statuses and configure push buttons */
	pio_configure(&pin_push_button, 1);
#endif
	memset(key_status, 0, sizeof(key_status));

	/* Configure Audio */
	audio_configure(&audio_device);

	/* USB audio driver initialization */
	hid_audd_driver_initialize(&hid_audd_driver_descriptors);

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
			audd_function_read(_buffer[_audio_ctx.circ.rx],
					AUDDSpeakerDriver_BYTESPERFRAME,
					_usb_frame_recv_callback, &audio_device);

			usb_conn = true;
		}

		hidd_keyboard_process_keys();
	}
}
/** \endcond */
