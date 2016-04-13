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

#include "board.h"
#include "chip.h"
#include "chip_pins.h"
#include "trace.h"
#include "compiler.h"

#include "misc/console.h"
#include "misc/led.h"

#include "peripherals/classd.h"
#include "peripherals/l2cc.h"
#include "peripherals/pio.h"
#include "peripherals/pit.h"
#include "peripherals/pmc.h"
#include "peripherals/wdt.h"
#include "peripherals/xdmad.h"

#include "usb/device/audio/audd_function.h"
#include "usb/device/composite/hid_audd_driver.h"
#include "usb/device/hid/hidd_keyboard.h"

#include "main_descriptors.h"
#include "../usb_common/main_usb_common.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

#define NO_PUSHBUTTON

/*- HID */
/** Number of keys used in the example. */
#define NUM_KEYS                    (2)

/** Number of non-modifiers keys. */
#define NUM_NORMAL_KEYS             (1)

/** Number of modifier keys. */
#define NUM_MODIFIER_KEYS           (NUM_KEYS - NUM_NORMAL_KEYS)

/** Num lock LED index. */
#define LED_NUMLOCK                 LED_RED

/*- Audio */
/**  Number of available audio buffers. */
#define BUFFER_NUMBER       (100)
/**  Size of one buffer in bytes. */
#define BUFFER_SIZE     (AUDDSpeakerDriver_BYTESPERFRAME)

/**  Delay in ms for starting the DAC transmission
     after a frame has been received. */
#define DAC_DELAY           (2)

/*----------------------------------------------------------------------------
 *         External variables
 *----------------------------------------------------------------------------*/

/** Descriptor list for USB Audio Speaker Device Driver */
extern const USBDDriverDescriptors hid_audd_driver_descriptors;

/*----------------------------------------------------------------------------
 *         Internal variables
 *----------------------------------------------------------------------------*/

/*- HID */

#ifdef NO_PUSHBUTTON
#else
/** List of pins_push_buttons to configure for the applicatino. */
static struct _pin pins_push_buttons[] = {PINS_PUSHBUTTONS};
#endif

static const struct _pin classd_pins[] = BOARD_CLASSD_PINS;

/** Array of key codes produced by each button. */
static uint8_t key_codes[NUM_KEYS] = {
	HIDKeypad_A,
	HIDKeypad_NUMLOCK,
};

/** Current status (pressed or not) for each key. */
static uint8_t key_status[NUM_KEYS];

/*- Audio */
ALIGNED(L1_CACHE_BYTES)
/**  Data buffers for receiving audio frames from the USB host. */
static uint8_t buffers[BUFFER_NUMBER][BUFFER_SIZE];
/**  Number of samples stored in each data buffer. */
static uint32_t buffer_sizes[BUFFER_NUMBER];
/**  Next buffer in which USB data can be stored. */
static volatile uint32_t in_buffer_index = 0;
/**  Next buffer which should be sent to the DAC. */
static volatile uint32_t out_buffer_index = 0;
/**  Number of buffers that can be sent to the DAC. */
static volatile uint32_t num_buffers_to_send = 0;
/**  Current state of the DAC transmission. */
static volatile uint32_t is_dac_active = 0;
static volatile uint32_t is_first_frame = 1;
/**  Number of buffers to wait for before the DAC starts to transmit data. */
static volatile uint32_t dac_delay;

/** DMA channel for TX */
static struct _xdmad_channel*  classd_dma_tx_channel;

/*----------------------------------------------------------------------------
 *         Internal functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief Start DMA sending/waiting data.
 */
static void _classd_dma_tx(void* buffer, uint16_t wsize)
{
	static struct _xdmad_cfg xdmad_cfg;

	l2cc_clean_region((uint32_t)buffer, (uint32_t)((uint32_t*)buffer + (wsize/2)));

	xdmad_cfg.ublock_size = wsize/2;
	xdmad_cfg.src_addr = (uint32_t*)buffer;
	xdmad_cfg.dest_addr = (uint32_t*)&CLASSD->CLASSD_THR;
	xdmad_cfg.cfg.uint32_value = XDMAC_CC_TYPE_PER_TRAN
				| XDMAC_CC_MBSIZE_SINGLE
				| XDMAC_CC_DSYNC_MEM2PER
				| XDMAC_CC_CSIZE_CHK_1
				| XDMAC_CC_DWIDTH_WORD
				| XDMAC_CC_SIF_AHB_IF0
				| XDMAC_CC_DIF_AHB_IF1
				| XDMAC_CC_SAM_INCREMENTED_AM
				| XDMAC_CC_DAM_FIXED_AM;
	xdmad_cfg.block_size = 0;
	xdmad_configure_transfer(classd_dma_tx_channel, &xdmad_cfg, 0, 0);
	xdmad_start_transfer(classd_dma_tx_channel);
}

/**
 *  \brief DMA TX callback
 */
static void _classd_tx_callback(struct _xdmad_channel *channel, void* p_arg)
{
	if (!xdmad_is_transfer_done(channel))
		return;

	p_arg = p_arg; /*dummy */

	if (num_buffers_to_send == 0)
	{
		/* End of transmission */
		is_dac_active = 0;
		return;
	}

	/* Load next buffer */
	_classd_dma_tx(buffers[out_buffer_index], buffer_sizes[out_buffer_index]);
	out_buffer_index = (out_buffer_index + 1) % BUFFER_NUMBER;
	num_buffers_to_send --;
}

/**
 * \brief DMA driver configuration
 */
static void _configure_classd_dma(void)
{
	/* Driver initialize */
	xdmad_initialize(false);

	/* Allocate DMA channels for CLASSD */
	classd_dma_tx_channel = xdmad_allocate_channel( XDMAD_PERIPH_MEMORY, ID_CLASSD );
	if (!classd_dma_tx_channel) {
		printf("XDMA channel allocation error\n\r");
	} else {
		xdmad_set_callback(classd_dma_tx_channel, _classd_tx_callback, 0);
		xdmad_prepare_channel( classd_dma_tx_channel );
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
 * Configure the CLASSD for audio output.
 * \param sampleRate Audio sample rate.
 */
static void _configure_audio_play( uint32_t sample_rate )
{
	struct _classd_desc classd_desc = {
		.sample_rate = sample_rate,
		.mode = BOARD_CLASSD_MODE,
		.non_ovr = CLASSD_NONOVR_10NS,
		.swap_channels = false,
		.mono = BOARD_CLASSD_MONO,
		.mono_mode = BOARD_CLASSD_MONO_MODE,
		.left_enable = true,
		.right_enable = true,
	};

	classd_configure(&classd_desc);
	classd_volume_unmute(true, true);
	classd_set_left_attenuation(35);
	classd_set_right_attenuation(35);
	audio_play_enable(false);
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
#ifdef NO_PUSHBUTTON
	if (console_is_rx_ready()) {
		uint8_t key = console_get_char();
		switch(key) {
			case '1':
			case '2':
				i = key - '1';
				if (key_status[i]) {
					/* Key press simulation */
					trace_info("Key %u pressed\n\r", (unsigned int)i);
					key_status[i] = 0;
					pressed_keys[pressed_keys_size] = key_codes[i];
					pressed_keys_size ++;
					hidd_keyboard_remote_wakeup();
				} else {
					/* Key release simulation */
					trace_info("Key %u released\n\r", (unsigned int)i);
					key_status[i] = 1;
					released_keys[released_keys_size] = key_codes[i];
					released_keys_size++;
				}
					break;
			default: console_put_char(key);
		}
	}
#else
	for (i = 0; i < ARRAY_SIZE(pins_push_buttons); i++) {
		/* Check if button state has changed */
		uint8_t is_button_pressed = pio_get(&(pins_push_buttons[i]));
		if (is_button_pressed != key_status[i]) {
			/* Update button state */
			if (!is_button_pressed) {
				/* Key has been pressed */
				trace_info("Key %u has been pressed\n\r", i);
				key_status[i] = 0;
				pressed_keys[pressed_keys_size] = key_codes[i];
				pressed_keys_size++;
				hidd_keyboard_remote_wakeup();

			} else {

				/* Key has been released */
				trace_info("Key %u has been released\n\r", i);
				key_status[i] = 1;
				released_keys[released_keys_size] = key_codes[i];
				released_keys_size++;
			}
		}
	}
#endif

	/* Update key status in the HID driver if necessary */
	if ((pressed_keys_size != 0) || (released_keys_size != 0)) {
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
static void frame_received(void *arg, uint8_t status,
		uint32_t transferred, uint32_t remaining)
{
	if (status == USBD_STATUS_SUCCESS) {
		buffer_sizes[in_buffer_index] = transferred / AUDDSpeakerDriver_BYTESPERSAMPLE;
		in_buffer_index = (in_buffer_index + 1) % BUFFER_NUMBER;
		num_buffers_to_send++;

		/* Start DAc transmission if necessary */
		if (!is_dac_active) {
			dac_delay = DAC_DELAY;
			is_dac_active = 1;
		}
		/* Wait until a few buffers have been received */
		else if (dac_delay > 0) {
			dac_delay--;
		} else if (is_first_frame) {
			/* Start sending buffers */
			is_first_frame = 0;
			audio_play_enable(true);
			_classd_dma_tx( buffers[out_buffer_index], buffer_sizes[out_buffer_index]);
			out_buffer_index = (out_buffer_index + 1) % BUFFER_NUMBER;
			num_buffers_to_send--;
		}
	}
	else if (status == USBD_STATUS_ABORTED) {
		/* Error , ABORT, add NULL buffer */
		buffer_sizes[in_buffer_index] = 0;
	} else {
		/* Packet is discarded */
	}

	/* Receive next packet */
	audd_function_read(buffers[in_buffer_index],
			AUDDSpeakerDriver_BYTESPERFRAME,
			frame_received, NULL);
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
			audio_play_enable(false);
			trace_info("MuteMaster ");
		} else {
			trace_info("UnmuteMaster ");
			audio_play_enable(true);
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
		xdmad_stop_transfer(classd_dma_tx_channel);
		num_buffers_to_send = 0;
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
	if (num_lock_status) {
		led_set(LED_NUMLOCK);
	}
		else {
		led_clear(LED_NUMLOCK);
	}
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
	volatile uint8_t usb_conn = 0;
	volatile uint8_t audio_on = 0;
	uint32_t num = 0;
	int32_t  num_diff = 0, prev_diff = 0;
	int8_t   clock_adjust = 0;

	/* Disable watchdog */
	wdt_disable();

	/* Configure console */
	board_cfg_console();

	printf("-- USB HID + Audio Device Example %s --\n\r", SOFTPACK_VERSION);
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	/* configure PIO muxing for ClassD */
	pio_configure(classd_pins, ARRAY_SIZE(classd_pins));

	/* Initialize all USB power (off) */
	usb_power_configure();

	/* ----- HID Function Initialize */
#ifdef NO_PUSHBUTTON
	printf( "-- : DBG key 1 2 used as buttons\n\r" );
	printf( "-- : 1st press to push, 2nd press to release\n\r" );
#else
	/* Initialize key statuses and configure push buttons */
	pio_configure(pins_push_buttons,  ARRAY_SIZE(pins_push_buttons));
#endif
	memset(key_status, 1, NUM_KEYS);

	/* Numlock LED */
	led_configure(LED_NUMLOCK);

	/* Configure Audio */
	_configure_audio_play( AUDDSpeakerDriver_SAMPLERATE);

	/* Configure DMA */
	_configure_classd_dma();

	/* USB audio driver initialization */
	hid_audd_driver_initialize(&hid_audd_driver_descriptors);

	/* connect if needed */
	usb_vbus_configure();

	/* Infinite loop */
	while (1) {
		if (usbd_get_state() < USBD_STATE_CONFIGURED) {
			usb_conn = 0;
			continue;
		}

		if (audio_on) {
			if (is_dac_active == 0) {
				audio_play_enable(false);
				printf("<end_playing> ");
				is_first_frame = 1;
				audio_on = 0;
			} else {
					if (num != num_buffers_to_send) {
						num = num_buffers_to_send;
					}

					num_diff = num_buffers_to_send - DAC_DELAY;
					if (prev_diff != num_diff) {
						prev_diff = num_diff;
						if (num_diff > 0 && clock_adjust != 1) {
							/* USB too fast or CLASSD too slow: faster clock */
							clock_adjust = 1;
						}
						if (num_diff < 0 && clock_adjust != -1) {
							/* USB too slow or CLASSD too fast: slower clock */
							clock_adjust = -1;
						}
						if (num_diff == 0 && clock_adjust != 0) {
							clock_adjust = 0;
						}
					}
				}
		} else if (is_dac_active) {
			printf("<start_playing> ");
			audio_on = 1;
		}

		if (usb_conn == 0) {
			/* Start Reading the incoming audio stream */
			audd_function_read(buffers[in_buffer_index],
					AUDDSpeakerDriver_BYTESPERFRAME,
					frame_received, NULL);
			usb_conn = 1;
		}

		hidd_keyboard_process_keys();
	}
}
/** \endcond */
