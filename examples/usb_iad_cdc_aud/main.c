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
/** \cond usb_iad_cdc_aud
 *  \page usb_iad_cdc_aud USB CDC(Serial)+Audio(Speaker) Example
 *
 *  \section Purpose
 *
 *  The Example will help you to get familiar with the USB Framework that is
 *  used for rapid development of USB-compliant class drivers such as USB
 *  Composite device that integrates a CDC Virtual Serial Port Function and
 *  an Audio Speaker Function.
 *
 *  \section Requirements
 *
 *  This package can be used with SAMA5D2-EK that have UDP
 *  and CLASSD.
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
 * When an EK running this program connected to a host (PC for example), with
 * USB cable, host will notice the attachment of a USB %device (USB Composite
 * Device) with a USB Virtual COM port(AT91 USB to Serial Converter)
 * and a USB Audio Device.
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
 *  -- USB CDC + Audio Device Example xxx --
 *  -- SAMxxxxx-xx
 *  -- Compiled: xxx xx xxxx xx:xx:xx --
 *  \endcode
 *  -# When connecting USB cable to windows, the LED blinks, and the host
 *     reports a new USB %device attachment (if it's the first time you connect
 *     an %audio speaker demo board to your host). You can find new
 *     "USB Composite Device" and "USB Audio Device" appear in the hardware
 *     %device list.
 *  -# You can play sound in host side through the USB Audio Device, and it
 *     can be heard from the earphone connected to the EK.
 *
 *  \section References
 *  - usb_iad_cdc_aud/main.c
 *  - pio: Pin configurations and peripheral configure.
 *  - dacc: DACC interface driver
 *  - adc: ADC interface driver
 *  - usb: USB Framework, CDC, Audio function driver and UDP interface driver
 *      - \ref usbd_framework
 *         - \ref usbd_api
 *      - \ref usbd_composite "composite"
 *         - \ref usbd_composite_drv
 *      - \ref usbd_cdc "cdc-serial"
 *         - \ref usbd_cdc_serial_drv
 *      - \ref usbd_aud "audio"
 *         - \ref usbd_audio_rec_drv
 *  - projects: more detailed information for CDC(Serial) and Audio(Speaker)
 *      - \ref usb_core
 *      - \ref usb_cdc_serial
 *      - \ref usb_audio_speaker, \ref usb_audio_headphone
 */

/**
 *  \file
 *
 *  This file contains all the specific code for the
 *  usb_iad_cdc_aud example.
 */

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include "audio/audio_device.h"
#include "board.h"
#include "chip.h"
#include "chip_pins.h"
#include "led/led.h"
#include "main_descriptors.h"
#include "mm/cache.h"
#include "serial/console.h"
#include "trace.h"
#include "../usb_common/main_usb_common.h"
#include "usb/device/audio/audd_function.h"
#include "usb/device/cdc/cdcd_serial.h"
#include "usb/device/composite/cdc_audd_driver.h"
#include "usb/device/usbd_hal.h"

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

/*- CDC */
/** Size in bytes of the packet used for reading data from USB */
#define DATAPACKETSIZE \
	 CHIP_USB_ENDPOINT_MAXPACKETSIZE(CDCD_Descriptors_DATAIN0)

/** Size in bytes of the buffer used for reading data from the USB & USART */
#define DATABUFFERSIZE (514)

/*- Audio */
/**  Number of available audio buffers. */
#define BUFFERS (32)

/**  Size of one buffer in bytes. */
#define BUFFER_SIZE ROUND_UP_MULT(AUDDevice_BYTESPERFRAME, L1_CACHE_BYTES)

/**  Delay (in number of buffers) before starting the DAC transmission
     after data has been received. */
#define BUFFER_THRESHOLD (8)

/*----------------------------------------------------------------------------
 *         External variables
 *----------------------------------------------------------------------------*/

/** Descriptor list for USB Audio SpeakerPhone Driver */
extern const USBDDriverDescriptors cdc_audd_driver_descriptors;

/*----------------------------------------------------------------------------
 *         Internal variables
 *----------------------------------------------------------------------------*/

/*- CDC */
/** Buffer for storing incoming USB data. */
static uint8_t usb_serial_buffer0[DATABUFFERSIZE];
/** Serial port openned */
static volatile uint8_t is_serial_port_on = 0;

/*- Audio */
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
 *  Invoked when a frame has been received.
 */
static void _usb_frame_recv_callback(void *arg, uint8_t status, uint32_t transferred, uint32_t remaining)
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
	audd_function_read(_buffer[_audio_ctx.circ.rx],
			   AUDDevice_BYTESPERFRAME,
			   _usb_frame_recv_callback, desc);
}

/**
 * Callback invoked when data has been received on the USB.
 */
static void cdc_data_received(void *arg, uint8_t status,
		uint32_t received, uint32_t remaining)
{
	/* Check that data has been received successfully */
	if (status == USBD_STATUS_SUCCESS) {
		/* Echo back */
		cdcd_serial_write(usb_serial_buffer0, received, 0, 0);
		/* Receive next */
		cdcd_serial_read(usb_serial_buffer0, DATAPACKETSIZE,
				cdc_data_received, NULL);
	} else {
		trace_warning( "cdc_data_received: Transfer error\n\r");
	}
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
void usbd_driver_callbacks_configuration_changed(uint8_t cfgnum)
{
	cdc_audd_driver_configuration_changed_handler(cfgnum);
}

/**
 * Invoked whenever the active setting of an interface is changed by the
 * host. Reset streaming interface.
 * \param interface Interface number.
 * \param setting Newly active setting.
 */
void usbd_driver_callbacks_interface_setting_changed(uint8_t interface,
		uint8_t setting)
{
	cdc_audd_driver_interface_setting_changed_handler(interface, setting);
}

/**
 *  Invoked whenever a SETUP request is received from the host. Forwards the
 *  request to the standard handler.
 */
void usbd_callbacks_request_received(const USBGenericRequest *request)
{
	cdc_audd_driver_request_handler(request);
}

/*-------------------------------------------
 *      USB Function driver callbacks
 *-------------------------------------------*/

/**
 * Invoked when the CDC ControlLineState is changed
 * \param DTR   New DTR value.
 * \param RTS   New RTS value.
 */
void cdcd_serial_control_line_state_changed(uint8_t DTR, uint8_t RTS)
{
	is_serial_port_on = DTR;
	RTS = RTS; /* dummy */
}

/**
 *  Invoked when an audio channel get muted or unmuted. Mutes/unmutes the
 *  channel at the DAC level.
 *  \param mic      Microphone/Speaker stream changed.
 *  \param channel  Channel number that changed.
 *  \param muted    Indicates the new mute status of the channel.
 */
void audd_function_mute_changed(uint8_t mic, uint8_t channel,
		uint8_t muted)
{
	if (mic) return;

	/* Speaker Master channel */
	if (channel == AUDD_CH_Master) {
		if (muted) {
			audio_mute(&audio_device, true);
			trace_warning("MuteMaster ");
		} else {
			trace_info("UnmuteMaster ");
			audio_mute(&audio_device, false);
		}
	}
}

/**
 *  Invoked when an audio streaming interface setting changed.
 *  Audio stream is automatically reseted.
 *  Actually control streaming rate.
 *  \param mic         Microphone/Speaker stream changed.
 *  \param new_setting  New stream (interface) setting.
 */
void audd_function_stream_setting_changed(uint8_t mic, uint8_t new_setting)
{
	/* Speaker stream */
	if (!mic) {
		if (new_setting) {
			led_set(LED_BLUE);
			audio_stop(&audio_device);
			_audio_ctx.circ.count = 0;
		} else {
			led_clear(LED_BLUE);
		}
	}
}

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief usb_iad_cdc_aud Application entry point.
 *
 *  Starts the driver and
 *  - waits for an audio input stream to forward to the DAC.
 *  - waits for a cdc serial input to forward to cdc output (echo).
 */
int main(void)
{
	bool usb_conn = false;
	volatile uint8_t serial_on = 0;

	/* Output example information */
	console_example_info("USB CDC + Audio Device Example");

	/* If there is on board power, switch it off */
	usb_power_configure();

	/* Configure Audio */
	audio_configure(&audio_device);

	/* USB audio driver initialization */
	cdc_audd_driver_initialize(&cdc_audd_driver_descriptors);

	/* connect if needed */
	usb_vbus_configure();

	/* Infinite loop */
	while (1) {
		if (usbd_get_state() < USBD_STATE_CONFIGURED) {
			usb_conn = false;
			continue;
		}

		if (!serial_on && is_serial_port_on) {
			printf("-I- SerialPort ON\n\r");
			/* Start receiving data on the USB */
			cdcd_serial_read(usb_serial_buffer0, DATAPACKETSIZE,
					cdc_data_received, NULL);
			serial_on = 1;
		} else if (serial_on && !is_serial_port_on) {
			printf("-I- SerialPort OFF\n\r");
			serial_on = 0;
		}
		if (!usb_conn) {
			trace_info("USB connected\r\n");

			/* Try to Start Reading the incoming audio stream */
			audd_function_read(_buffer[_audio_ctx.circ.rx],
					   AUDDevice_BYTESPERFRAME,
					   _usb_frame_recv_callback, &audio_device);
			usb_conn = true;
		}
	}
}
/** \endcond */
