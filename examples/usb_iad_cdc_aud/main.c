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

#include "board.h"
#include "chip.h"
#include "chip_pins.h"
#include "trace.h"
#include "compiler.h"

#include "cortex-a/mmu.h"
#include "cortex-a/cp15.h"
#include "misc/console.h"
#include "misc/led.h"

#include "peripherals/classd.h"
#include "peripherals/l2cc.h"
#include "peripherals/pio.h"
#include "peripherals/pit.h"
#include "peripherals/pmc.h"
#include "peripherals/wdt.h"
#include "peripherals/xdmad.h"

#include "cdc_audd_driver.h"
#include "cdcd_serial.h"
#include "audd_function.h"

#include "usbd_hal.h"
#include "usb_descriptors.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

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
#define BUFFER_NUMBER       (100)
/**  Size of one buffer in bytes. */
#define BUFFER_SIZE         (AUDDevice_BYTESPERFRAME)

/**  Buffer adjust level */
#define BUFFER_DELAY        (2)

/*
 * Delay in ms for starting the DAC transmission
 * after a frame has been received.
 */
#define DAC_DELAY           BUFFER_DELAY

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
static uint8_t buffers[BUFFER_NUMBER][BUFFER_SIZE];
/**  Number of samples stored in each data buffer. */
static uint32_t buffer_sizes[BUFFER_NUMBER];
/**  Next buffer in which USB data can be stored. */
static uint32_t in_buffer_index = 0;
/**  Next buffer which should be sent to the DAC. */
static uint32_t out_buffer_index = 0;
/**  Number of buffers that can be sent to the DAC. */
static volatile uint32_t num_buffers_to_send = 0;

/**  Current state of the USB OUT transmission. */
static volatile uint8_t  is_play_active = 0;
/**  Current state of the DAC transmission. */
static volatile uint8_t  is_dac_active = 0;

static volatile uint32_t is_first_frame = 1;
/**  Number of buffers to wait for before the DAC starts to transmit data. */
static volatile uint8_t  dac_delay;

/** DMA channel for TX */
static struct _xdmad_channel* classd_dma_tx_channel;


/*----------------------------------------------------------------------------
 *         VBus monitoring (optional)
 *----------------------------------------------------------------------------*/

/**  VBus pin instance. */
static const struct _pin pin_vbus = PIN_USB_VBUS;

static const struct _pin classd_pins[] = BOARD_CLASSD_PINS;

/**
 *  Handles interrupts coming from PIO controllers.
 */
static void pio_handler(uint32_t mask, uint32_t status, void* user_arg)
{
	if (status & pin_vbus.mask) {
		printf("vbus conn\n\r");
		usbd_connect();
	} else {
		printf("vbus discon\n\r");
		usbd_disconnect();
	}
}


/**
 *  Configures the VBus pin to trigger an interrupt when the level on that pin
 *  changes.
 */
static void vbus_configure( void )
{
	trace_info("vbus configuration\n\r");

	/* Configure PIO */
	pio_configure(&pin_vbus, 1);
	/* Initialize pios interrupt with its handlers */
	pio_configure_it(&pin_vbus);
	pio_add_handler_to_group(pin_vbus.group,
							pin_vbus.mask, pio_handler, NULL);
	/* Enable PIO line interrupts. */
	pio_enable_it(&pin_vbus);
	/* Check current level on VBus */
	if (pio_get(&pin_vbus)) {
		/* if VBUS present, force the connect */
		printf("conn\n\r");
		usbd_connect();
	} else {
		usbd_disconnect();
	}
}

/*----------------------------------------------------------------------------
 *         USB Power Control
 *----------------------------------------------------------------------------*/

#ifdef PIN_USB_POWER_ENA
/** Power Enable A (MicroAB Socket) pin instance. */
static const struct _pin pin_pon_a = PIN_USB_POWER_ENA;
#endif
#ifdef PIN_USB_POWER_ENB
/** Power Enable B (A Socket) pin instance. */
static const struct _pin pin_pon_b = PIN_USB_POWER_ENB;
#endif
#ifdef PIN_USB_OVCUR
/** Power Enable C (A Socket) pin instance. */
static const struct _pin pin_pon_c = PIN_USB_OVCUR;
#endif
/**
 * Configures the Power Enable pin to disable self power.
 */
static void usb_power_configure( void )
{
#ifdef PIN_USB_POWER_ENA
	pio_configure(&pin_pon_a, 1);
#endif
#ifdef PIN_USB_POWER_ENB
	pio_configure(&pin_pon_b, 1);
#endif
#ifdef PIN_USB_OVCUR
	pio_configure(&pin_pon_c, 1);
#endif
}

/*----------------------------------------------------------------------------
 *         Internal functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief Start DMA sending/waiting data.
 */
static void _classd_start_dma(void)
{
	uint32_t *buffer;
	uint32_t wsize;
	static struct _xdmad_cfg xdmad_cfg;

	if (num_buffers_to_send == 0)
		return;

	buffer = (uint32_t*)(buffers[out_buffer_index]);
	wsize = buffer_sizes[out_buffer_index];
	out_buffer_index = (out_buffer_index + 1) % BUFFER_NUMBER;
	num_buffers_to_send--;

	if (wsize)
		l2cc_clean_region((uint32_t)buffer, (uint32_t)((uint32_t*)buffer + (wsize/2)));

	xdmad_cfg.ublock_size = (wsize/2);
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
	xdmad_configure_transfer(classd_dma_tx_channel, &xdmad_cfg, 0, 0);
	xdmad_start_transfer(classd_dma_tx_channel);
}

/**
 *  \brief DMA TX callback
 */
static void _classd_tx_callback(struct _xdmad_channel *channel, void *p_arg)
{
	if (!xdmad_is_transfer_done(channel))
		return;

	p_arg = p_arg; /*dummy */

	if (num_buffers_to_send == 0) {
		/* End of transmission */
		is_dac_active = 0;
		return;
	}

	/* Load next buffer */
	_classd_start_dma();
}

/**
 * \brief DMA driver configuration
 */
static void _configure_dma( void )
{
	/* XDMAC initialize */
	xdmad_initialize(false);

	/* Allocate DMA channels for CLASSD */
	classd_dma_tx_channel = xdmad_allocate_channel(XDMAD_PERIPH_MEMORY, ID_CLASSD);
	if (!classd_dma_tx_channel) {
		printf("xDMA channel allocation error\n\r");
	} else {
		xdmad_set_callback(classd_dma_tx_channel, _classd_tx_callback, 0);
		xdmad_prepare_channel(classd_dma_tx_channel);
	}
}


/**
 * Enable/Disable audio speaker channels
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
 * Configure the TC0 and DACC, ADC for audio playback/record.
 * \param sample_rate Audio sample rate.
 */
static void _configure_audio(uint32_t sample_rate)
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
	classd_set_left_attenuation(35);
	classd_set_right_attenuation(35);
	classd_volume_unmute(true, true);
	audio_play_enable(false);
}

/**
 *  Invoked when a frame has been received.
 */
static void frame_received(void *arg, uint8_t status,
		uint32_t transferred, uint32_t remaining)
{
	if (status == USBD_STATUS_SUCCESS) {
		/* Update input status data */
		buffer_sizes[in_buffer_index] = transferred /
			AUDDevice_BYTESPERSAMPLE;
		in_buffer_index = (in_buffer_index + 1) % BUFFER_NUMBER;
		num_buffers_to_send++;

		/* Start DAC transmission if necessary */
		if (!is_dac_active) {
			dac_delay = DAC_DELAY;
			is_dac_active = 1;
		} else if (dac_delay > 0) {
			/* Wait until a few buffers have been received */
			dac_delay--;
		} else if (is_first_frame) {
			/* Start sending buffers */
			is_first_frame = 0;
			audio_play_enable(true);
			_classd_start_dma();
		}
	} else if (status == USBD_STATUS_ABORTED) {
		/* Error , ABORT, add NULL buffer */
		buffer_sizes[in_buffer_index] = 0;
	} else {
		/* Packet is discarded */
	}

	/* Receive next packet */
	audd_function_read(buffers[in_buffer_index], AUDDevice_BYTESPERFRAME,
			frame_received, 0);
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
			audio_play_enable(false);
			trace_warning("MuteMaster ");
		} else {
			trace_info("UnmuteMaster ");
			audio_play_enable(true);
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
			xdmad_stop_transfer(classd_dma_tx_channel);
			num_buffers_to_send = 0;
		} else {
			led_clear(LED_BLUE);
		}
		is_play_active = (new_setting > 0);
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

	volatile uint8_t usb_conn = 0;
	volatile uint8_t audio_on = 0;
	volatile uint8_t serial_on = 0;

	uint32_t num = 0;
	int32_t  num_diff = 0, prev_diff = 0;
	int8_t   clock_adjust = 0;

	/* Disable watchdog */
	wdt_disable( );

#ifndef VARIANT_DDRAM
	mmu_initialize();
	cp15_enable_mmu();
	cp15_enable_dcache();
	cp15_enable_icache();
#endif

	printf("-- USB CDC + Audio Device Example %s --\n\r", SOFTPACK_VERSION);
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	/* If they are present, configure Vbus & Wake-up pins */
	pio_reset_all_it();

	/* configure PIO muxing for ClassD */
	pio_configure(classd_pins, ARRAY_SIZE(classd_pins));

	/* If there is on board power, switch it off */
	usb_power_configure();

	/* Audio STREAM LED */
	led_configure(LED_BLUE);

	/* Configure Audio */
	_configure_audio(AUDDevice_SAMPLERATE);
	/* Configure DMA */
	_configure_dma();

	/* USB audio driver initialization */
	cdc_audd_driver_initialize(&cdc_audd_driver_descriptors);

	/* connect if needed */
	vbus_configure();

	/* Infinite loop */
	while (1) {
		if (usbd_get_state() < USBD_STATE_CONFIGURED) {
			usb_conn = 0;
			continue;
		}
		if (audio_on) {
			if(is_dac_active == 0) {
				audio_play_enable(false);
				is_first_frame = 1;
				audio_on = 0;
				printf("<stop_playing> ");
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
			usb_conn = 1;

			/* Try to Start Reading the incoming audio stream */
			audd_function_read(buffers[in_buffer_index], AUDDevice_BYTESPERFRAME,
					frame_received, 0);
		}

		if (!serial_on && is_serial_port_on) {
			printf("-I- SerialPort ON\n\r");
			/* Start receiving data on the USB */
			cdcd_serial_read(usb_serial_buffer0, DATAPACKETSIZE,
					cdc_data_received, NULL);
			serial_on = 1;
		} else if (serial_on && !is_serial_port_on) {
			printf("-I- SeriaoPort OFF\n\r");
			serial_on = 0;
		}
	}
}
/** \endcond */
