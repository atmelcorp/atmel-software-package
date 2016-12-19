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
 * \page isi ISI Example
 *
 * \section Purpose
 *
 * This example demonstrates the ISI (Image Sensor Interface) of an SAM V71
 * Xplained Ultra.
 *
 * \section Requirements
 *
 * This package can be used with SAMA5D4-EK  with
 * On-board ISI interface and a external CMOS-type image sensor board.
 *
 * \section Description
 * The provided program uses the Image Sensor Interface to connects a CMOS-type
 * image sensor to the processor and displays in VGA format.
 *
 *  \section Note
 *
 *  Some pins conflict between LCD pins and JTAG pins, this example can not run
 * in debugger mode.
 *
 * \section Usage
 *  -# Build the program and download it inside the SAMA5D4-EK board.
 *  Please refer to the Getting Started with SAM V71 Microcontrollers.pdf
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *    \code
 *     -- ISI Example xxx --
 *      -- SAMxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *    \endcode
 * The user can then choose any of the available options to perform the
 * described action.
 *
 * \section References
 * - lcdc.c
 * - isi.c
 */

/**
 * \file
 *
 * This file contains all the specific code for the ISI example.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"
#include "compiler.h"
#include "trace.h"

#include "serial/console.h"

#include "display/lcdc.h"

#include "video/image_sensor_inf.h"
#include "video/isi.h"
#include "video/isid.h"

#include <stdbool.h>
#include <stdio.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** Frame buffer base address in preview path */
#define ISI_PREVIEW_PATH_BASE_ADDRESS (DDR_CS_ADDR + 16 * 1024 * 1024)

/** Maximum number of preview buffer */
#define ISI_MAX_NUM_PREVIEW_BUFFER      1

/** Maximum image size (YUV)*/
#define ISI_MAX_IMAGE_SIZE (1600 * 1200 * 2)

/** LCD buffer start address for preview mode (same address for ISI preview buffer) */
#define LCD_PREVIEW_BASE_ADDRESS ISI_PREVIEW_PATH_BASE_ADDRESS

/** Frame buffer base address in codec path */
#define ISI_CODEC_PATH_BASE_ADDRESS (ISI_PREVIEW_PATH_BASE_ADDRESS +\
			ISI_MAX_IMAGE_SIZE * ISI_MAX_NUM_PREVIEW_BUFFER)

/** LCD buffer start address for captured image (same address for ISI codec buffer) */
#define LCD_CAPTURED_BASE_ADDRESS ISI_CODEC_PATH_BASE_ADDRESS

/** LCDC_OVR1 layer use for preview frame display in RGB output */
#define LCD_PREVIEW_LAYER LCDC_OVR1

/** LCDC_HEO layer use for display captured image in YUV output */
#define LCD_CAPTURE_LAYER LCDC_HEO

#define SENSOR_TWI_BUS BOARD_ISI_TWI_BUS

/*----------------------------------------------------------------------------
 *        Local variables/constants
 *----------------------------------------------------------------------------*/

/** Sensor profile */
static struct sensor_profile *sensor;

/* ISI frame buffer descriptors */

/** LCD buffer.*/
static uint8_t *ovr_buffer = (uint8_t*)LCD_PREVIEW_BASE_ADDRESS;
static uint8_t *heo_buffer = (uint8_t*)LCD_CAPTURED_BASE_ADDRESS;

/* Image size in preview mode */
static uint32_t image_width, image_height;

/* Image output bit width */
static uint8_t sensor_bit_width;

static struct _isi_yuv2rgb ref_matrix = { 0x95, 0xFF, 0x68, 0x32, 1, 1, 1, 0xCC };

static struct _isid_desc isid;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Configure LCD controller.
 */
static void configure_lcd(void)
{
	lcdc_configure_input_mode(LCD_PREVIEW_LAYER, LCDC_BASECFG1_RGBMODE_16BPP_RGB_565);
	lcdc_configure_input_mode(LCD_CAPTURE_LAYER, LCDC_HEOCFG1_YUVEN |
							LCDC_HEOCFG1_YUVMODE_16BPP_YCBCR_MODE3);
	lcdc_create_canvas(LCD_PREVIEW_LAYER, ovr_buffer, 16,
						(BOARD_LCD_WIDTH - image_width) / 2,
						(BOARD_LCD_HEIGHT - image_height) / 2,
						image_width, image_height);
	lcdc_create_canvas(LCD_CAPTURE_LAYER, heo_buffer, 16,
						(BOARD_LCD_WIDTH - image_width) / 2,
						(BOARD_LCD_HEIGHT - image_height) / 2,
						image_width, image_height);
}

/**
 * \brief ISI initialization.
 */
static void configure_isi(void)
{
	isid.cfg.input_format = YUV_422;
	isid.cfg.multi_bufs = ISI_MAX_NUM_PREVIEW_BUFFER;
	isid.cfg.width = image_width;
	isid.cfg.height = image_height;
	isid.cfg.capture_rate = 0;

	isid.pipe.pipe = ISID_PIPE_PREVIEW;
	isid.pipe.px = BOARD_LCD_WIDTH;
	isid.pipe.py = BOARD_LCD_HEIGHT;
	isid.pipe.yuv = ISID_Y_CB_Y_CR;
	isid.pipe.yuv2rgb_matrix = &ref_matrix;
	isid.pipe.rgb2yuv_matrix = NULL;
	isid.dma.address_p = LCD_PREVIEW_BASE_ADDRESS;
	isid.dma.address_c = LCD_CAPTURED_BASE_ADDRESS;

	isid_pipe_start(&isid);
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Application entry point for ISI example.
 *
 * \return Unused (ANSI-C compatibility).
 */
extern int main( void )
{
	uint8_t key;
	volatile uint32_t delay;

	/* Output example information */
	console_example_info("ISI Example");

	printf("Image sensor detection:\n\r");
	if ((sensor = sensor_detect(SENSOR_TWI_BUS, true, 0))) {
		if (sensor_setup(SENSOR_TWI_BUS, sensor, VGA, YUV_422) != SENSOR_OK){
			printf("-E- Sensor setup failed.");
			while (1);
		}
	} else {
		printf("-E- Can't detect supported sensor connected to board\r\n");
		while (1);
	}

	/* Retrieve sensor output format and size */
	sensor_get_output(sensor, VGA, YUV_422, &sensor_bit_width,
					&image_width, &image_height);

	printf("Image attributes : <%x, %u, %u>\n\r", YUV_INPUT,
			(unsigned)image_width, (unsigned)image_height);
	printf("preview in RGB 565 mode\n\r");

	/* Configure LCD */
	configure_lcd();

	/* ISI Initialize */
	configure_isi();

	printf("-I- \n\r");
	printf("-I- Press 'C' to capture image, press 'P' back to preview mode \n\r");
	for(;;) {
		key = console_get_char();
		switch(key){
		case 'c': case 'C':
			printf("Capture image from CODEC path in YUV mode\n\r");
			lcdc_enable_layer(LCD_PREVIEW_LAYER, 0);
			isid.pipe.pipe = ISID_PIPE_CODEC;
			isid_pipe_start(&isid);
			for (delay = 0; delay < 0xffff; delay++);
			isi_codec_request();
			isi_codec_wait_dma_completed();
			printf("-I- Capture done \r\n");
			for (delay = 0; delay < 0x5ffff; delay++);
			lcdc_put_image_rotated(LCD_CAPTURE_LAYER, NULL, 16,
								(BOARD_LCD_WIDTH - image_width)/2,
								(BOARD_LCD_HEIGHT- image_height)/2,
								image_width, image_height,
								image_width, image_height,
								0);
			lcdc_enable_layer(LCD_CAPTURE_LAYER, 1);
			break;
		case 'p': case 'P':
			printf("preivew in RGB 565 mode\n\r");
			isid.pipe.pipe = ISID_PIPE_PREVIEW;
			isid_pipe_start(&isid);
			lcdc_enable_layer(LCD_CAPTURE_LAYER, 0);
			lcdc_enable_layer(LCD_PREVIEW_LAYER, 1);
			break;
		}
	}
}
