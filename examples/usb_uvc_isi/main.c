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
/**
 * \page usb_video USB Video Example
 *
 * \section Purpose
 *
 * The USB Video Example will help you to get familiar with the
 * USB Device Port(UDP) and ISI interface on SAMA5D4 microcontrollers.
 *
 * \section Requirements
 *
 * - On-board ISI interface.
 * - External sensor, in the example, Omnivision OV2643/OV5640/OV7740/OV7670/OV9740
 * sensor could be used.
 * When an EK running this program connected to a host (PC for example), with
 * USB cable, the EK appears as a video camera for the host.
 *
 * \note
 * For the limitation of external memory size, this example only support for
 * VGA/QVGA format.
 *
 * \section Usage
 *
 -# Build the program and download it inside the SAMA5D4 EK board.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 baud rates
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *     \code
 *     -- USB UVC ISI Example xxx --
 *     -- SAMxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 * -# When connecting USB cable to windows, the
 *    new "xxx USB Device" appears in the
 *    hardware %device list.
 * -# Once the device is connected and configured on windows XP,
 *    "USB Video Device" will appear in "My Computer", you can double click
 *    it to preview with default resolution - QVGA.
 * -# Other video camera programs can also be used to monitor the capture
 *    output. The demo is tested on windows XP through "AmCap.exe".
 *
 * \section References
 * - usb_uvc_isi/main.c
 */

/**
 * \file
 *
 * This file contains all the specific code for the
 * usb_uvc_isi
 *
 * \section Contents
 *
 * The code can be roughly broken down as follows:
 *    - Configuration functions
 *       - Configure TWI
 *       - Configure pins for OV sensor
 *       - Configure ISI controller
 *    - The main function, which implements the program behaviour
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"
#include "rand.h"

#include "misc/console.h"
#include "timer.h"

#include "peripherals/aic.h"
#include "peripherals/isi.h"
#include "misc/cache.h"
#include "peripherals/pio.h"
#include "peripherals/pit.h"
#include "peripherals/pmc.h"
#include "peripherals/twid.h"

#include "video/image_sensor_inf.h"

#include "usb/common/uvc/usb_video.h"
#include "usb/common/uvc/uvc_descriptors.h"
#include "usb/device/usbd_driver.h"
#include "usb/device/usbd.h"
#include "usb/device/usbd_hal.h"
#include "usb/device/uvc/uvc_driver.h"
#include "usb/device/uvc/uvc_function.h"

#include "../usb_common/main_usb_common.h"

#include <string.h>
#include <stdbool.h>
#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** TWI clock frequency in Hz. */
#define TWCK 400000

#define NUM_FRAME_BUFFER     4

/*----------------------------------------------------------------------------
 *          External variables
 *----------------------------------------------------------------------------*/

extern const USBDDriverDescriptors usbdDriverDescriptors;

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** PIO pins to configured for ISI */
const struct _pin pins_twi[] = BOARD_ISI_TWI_PINS;

CACHE_ALIGNED static struct _isi_dma_desc dma_desc[NUM_FRAME_BUFFER];

/** TWI driver instance.*/
static struct _twi_desc twid = {
	.addr = BOARD_ISI_TWI_ADDR,
	.freq = TWCK,
	.transfert_mode = TWID_MODE_POLLING
};

static uint8_t sensor_idx;

/* Image output bit width */
static sensor_output_bit_t sensor_output_bit_width;

/* Image resolution */
static sensor_output_resolution_t image_resolution = QVGA;

/* Image size in preview mode */
static uint32_t image_width, image_height;

static uint8_t frame_format;

static volatile uint32_t frame_idx = 0;

/** Supported sensor profiles */
static const sensor_profile_t *sensor_profiles[6] = {
	&ov2640_profile,
	&ov2643_profile,
	&ov5640_profile,
	&ov7670_profile,
	&ov7740_profile,
	&ov9740_profile
};

/** Video buffers */
CACHE_ALIGNED_DDR
static uint8_t stream_buffers[FRAME_BUFFER_SIZEC(640, 480) * NUM_FRAME_BUFFER];

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief ISi interrupt handler.
 */
static void isi_handler(void)
{
	uint32_t status = isi_get_status();

	if ((status & ISI_SR_PXFR_DONE) == ISI_SR_PXFR_DONE) {
		frame_idx = (frame_idx == (NUM_FRAME_BUFFER - 1)) ? 0 : (frame_idx + 1);
		uvc_function_update_frame_idx(frame_idx);
	}
}

/**
 * \brief TWI initialization.
 */
static void configure_twi(void)
{
	/* Configure TWI pins. */
	pio_configure(pins_twi, ARRAY_SIZE(pins_twi));
	/* Enable TWI peripheral clock */
	pmc_enable_peripheral(get_twi_id_from_addr(BOARD_ISI_TWI_ADDR));
	/* Configure TWI */
	twid_configure(&twid);
}

/**
 * \brief Set up DMA Descriptors.
 */
static void configure_dma_linklist(void)
{
	uint8_t i;

	for(i = 0; i < NUM_FRAME_BUFFER; i++) {
		dma_desc[i].address = (uint32_t)stream_buffers + i * FRAME_BUFFER_SIZEC(image_width, image_height);
		dma_desc[i].control = ISI_DMA_P_CTRL_P_FETCH | ISI_DMA_P_CTRL_P_WB;
		dma_desc[i].next = (uint32_t)&dma_desc[i + 1];
	}
	dma_desc[i - 1].next = (uint32_t)&dma_desc[0];
	cache_clean_region(&dma_desc, sizeof(dma_desc));
}

/**
 * \brief ISI initialization.
 */
static void configure_isi(void)
{
	/* Reset ISI peripheral */
	isi_reset();
	/* Set the windows blank */
	isi_set_blank(0, 0);
	/* Set vertical and horizontal Size of the Image Sensor for preview path*/
	isi_set_sensor_size(image_width, image_height);
	/* Set preview size to fit LCD size*/
	isi_set_preview_size(image_width, image_height );
	/* calculate scaler factor automatically. */
	isi_calc_scaler_factor();
	/*  Set data stream in YUV/RGB format.*/
	isi_set_input_stream(1);
	isi_rgb_pixel_mapping(ISI_CFG2_RGB_CFG_MODE3);
	isi_ycrcb_format(ISI_CFG2_YCC_SWAP_MODE3);
	/* Configure DMA for preview path. */
	isi_set_dma_preview_path((uint32_t)&dma_desc,
			ISI_DMA_P_CTRL_P_FETCH, (uint32_t)stream_buffers);
	isi_reset();
	isi_disable_interrupt(-1);
	aic_set_source_vector(ID_ISI, isi_handler);
	isi_enable_interrupt(ISI_IER_PXFR_DONE);
}

static void start_preview(void)
{
	sensor_output_format_t sensor_mode = YUV_422;

	/* Re-configure sensor with giving resolution */
	if (sensor_setup(&twid, sensor_profiles[sensor_idx], image_resolution, sensor_mode) != SENSOR_OK) {
		printf("-E- Sensor setup failed.");
		while (1);
	}
	/* Retrieve sensor output format and size */
	sensor_get_output(image_resolution, sensor_mode, &sensor_output_bit_width,
			&image_width, &image_height);

	printf("-I- Bit width = %d, Image Width = %d, Image Height=%d \n\r",
			(unsigned)(sensor_output_bit_width + 8),
			(unsigned)image_width, (unsigned)image_height);

	/* Set up Frame Buffer Descriptors(FBD) for preview path. */
	configure_dma_linklist();
	configure_isi();
	isi_enable();
	isi_dma_codec_channel_enabled(0);
	isi_dma_preview_channel_enabled(1);
	aic_enable(ID_ISI);
}

/**
 *  Invoked whenever a SETUP request is received from the host. Forwards the
 *  request to the standard handler.
 */
void usbd_callbacks_request_received(const USBGenericRequest *request)
{
	uvc_driver_request_handler(request);
}

/**
 * Invoked whenever the active setting of an interface is changed by the
 * host. Reset streaming interface.
 * \param interface Interface number.
 * \param setting Newly active setting.
 */
void usbd_driver_callbacks_interface_setting_changed( uint8_t interface, uint8_t setting )
{
	uvc_driver_interface_setting_changed_handler(interface, setting);
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Application entry point for ISI USB video example.
 *
 * \return Unused (ANSI-C compatibility).
 */
extern int main( void )
{
	int i;
	uint8_t key;
	bool is_usb_vid_on = false;

	/* Output example information */
	console_example_info("USB UVC ISI Example");

	/* TWI Initialize */
	configure_twi();

	printf("Image Sensor Selection:\n\r");
	for (i = 0; i < ARRAY_SIZE(sensor_profiles); i++)
		printf("- '%d' %s\n\r", i + 1, sensor_profiles[i]->name);
	for(;;) {
		printf("Press [1..%d] to select sensor\n\r",
			ARRAY_SIZE(sensor_profiles));
		key = console_get_char();
		if ((key >= '1') && (key <= ('1' + ARRAY_SIZE(sensor_profiles)))) {
			sensor_idx = key - '1';
			break;
		}
	}

	usb_power_configure();

	uvc_driver_initialize(&usbdDriverDescriptors, (uint32_t)stream_buffers, NUM_FRAME_BUFFER);

	/* connect if needed */
	usb_vbus_configure();

	while (1) {
		if (usbd_get_state() < USBD_STATE_CONFIGURED) {
			continue;
		}

		if (is_usb_vid_on) {
			if (!uvc_function_is_video_on()) {
				is_usb_vid_on = false;
				isi_disable_interrupt(ISI_IDR_PXFR_DONE);
				isi_dma_preview_channel_enabled(0);
				isi_disable();
				frame_idx = 0;
				printf("CapE\r\n");
				printf("vidE\r\n");
			}
		} else {
			if (uvc_function_is_video_on()) {
				is_usb_vid_on = true;
				frame_format = uvc_function_get_frame_format();
				if (frame_format == 1) {
					image_resolution = QVGA;
				}
				else if (frame_format == 2) {
					image_resolution = VGA;
				} else {
					printf ("-I- Only support VGA and QVGA format\r\n");
					image_resolution = QVGA;
				}
					/* clear video buffer */
				memset(stream_buffers, 0, sizeof(stream_buffers));
				cache_clean_region(stream_buffers, sizeof(stream_buffers));
				start_preview();
				uvc_function_payload_sent(NULL, USBD_STATUS_SUCCESS, 0, 0);
				printf("vidS\r\n");
			}
		}
	}
}
