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
 * \page isc ISC Example
 *
 * \section Purpose
 *
 * This example demonstrates the ISC (Image Sensor controller) of an SAMA5D2
 * Xplained board.
 *
 * \section Requirements
 *
 * This package can be used with SAMA5D2-EK  with
 * On-board ISC interface and a external CMOS-type image sensor board.
 *
 * \section Description
 * The provided program uses the Image Sensor Controller (ISC) system,
 * it manages incoming data from a parallel CMOS sensor (ov7740) . It
 * support sensor with a data width of 8 bits in YUV format and 10
 * bits raw Bayer format. This example shows how to configure the
 * internal image processor includes color filter array interpolation,
 * gamma correction, 12 bits to 10 bits compression, color space conversion,
 * luminance adjustment. It introduces how to samples data stream to expected
 * data format and transfer with DMA master module.
 *
 * \section Usage
 *  -# Build the program and download it inside the SAMA5D2-EK board.
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
 *     -- ISC Example xxx --
 *      -- SAMxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *    \endcode
 * The user can then choose any of the available options to perform the
 * described action.
 *
 * \section References
 * - lcdc.c
 * - twihs.c
 * - twihsd.c
 * - isc.c
 * - iscd.c
 */

/**
 * \file
 *
 * This file contains all the specific code for the ISC example.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"

#include "trace.h"

#include "mm/cache.h"
#include "serial/console.h"

#include "display/lcdc.h"

#include "video/image_sensor_inf.h"
#include "video/isc.h"
#include "video/iscd.h"

#include <stdbool.h>
#include <stdio.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** DMA memory address for DMA package 8/16 and DMA YC422P */
#define ISC_OUTPUT_BASE_ADDRESS   (DDR_CS_ADDR + 16 * 1024 * 1024)
#define ISC_OUTPUT_BASE_ADDRESS1  (ISC_OUTPUT_BASE_ADDRESS + 0x100000)
#define ISC_OUTPUT_BASE_ADDRESS2  (ISC_OUTPUT_BASE_ADDRESS1 + 0x100000)

/** Supported LCD mode in this example */
#define LCD_MODE_YUV               (LCDC_HEOCFG1_YUVEN | LCDC_HEOCFG1_YUVMODE_16BPP_YCBCR_MODE2)
#define LCD_MODE_YUV422_PLANAR     (LCDC_HEOCFG1_YUVEN | LCDC_HEOCFG1_YUVMODE_16BPP_YCBCR_PLANAR)
#define LCD_MODE_YUV422_SEMIPLANAR (LCDC_HEOCFG1_YUVEN | LCDC_HEOCFG1_YUVMODE_16BPP_YCBCR_SEMIPLANAR)
#define LCD_MODE_YUV420_PLANAR     (LCDC_HEOCFG1_YUVEN | LCDC_HEOCFG1_YUVMODE_12BPP_YCBCR_PLANAR)
#define LCD_MODE_YUV420_SEMIPLANAR (LCDC_HEOCFG1_YUVEN | LCDC_HEOCFG1_YUVMODE_12BPP_YCBCR_SEMIPLANAR)
#define LCD_MODE_RGB565            (LCDC_HEOCFG1_RGBMODE_16BPP_RGB_565)

/** Maximum number of frame buffer */
#define ISC_MAX_NUM_FRAME_BUFFER    1

#define SENSOR_TWI_BUS BOARD_ISC_TWI_BUS

/*----------------------------------------------------------------------------
 *        Local variables/constants
 *----------------------------------------------------------------------------*/

/** Supported sensor profiles */
static struct sensor_profile *sensor;

CACHE_ALIGNED uint32_t buffer_histogram[HIST_ENTRIES];

/** LCD buffer.*/
static uint8_t *heo_buffer = (uint8_t*)ISC_OUTPUT_BASE_ADDRESS;
static uint8_t *heo_buffer1 = (uint8_t*)ISC_OUTPUT_BASE_ADDRESS1;
static uint8_t *heo_buffer2 = (uint8_t*)ISC_OUTPUT_BASE_ADDRESS2;

/* Image size in preview mode */
static uint32_t image_width, image_height;
/* Image output bit width */
static uint8_t sensor_output_bit_width;
/* Sensor mode for YUV or RAW BAYER */
static uint8_t sensor_mode;
/* LCD mode */
static uint32_t lcd_mode;
static bool awb;
static struct _iscd_desc iscd;
/* Color space matrix setting */
static struct _color_space ref_cs = {
	0x42, 0x81, 0x19, 0x10, 0xFDA, 0xFB6, 0x70, 0x80, 0x70, 0xFA2, 0xFEE, 0x80};

static struct _color_correct ref_cc = {
	0, 0, 0, 0x100, 0, 0, 0x100, 0, 0, 0, 0, 0x100};

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Configure LCD controller.
 */
static void configure_lcd(void)
{
	lcdc_enable_layer(LCDC_HEO, 0);
	lcdc_configure_input_mode(LCDC_HEO, lcd_mode);

	if (sensor_mode == YUV_422)
		lcdc_create_canvas(LCDC_HEO, heo_buffer, 16, 0, 0, image_width, image_height);
	else {
		switch (lcd_mode) {
		case LCD_MODE_YUV422_PLANAR:
			lcdc_create_canvas_yuv_planar(LCDC_HEO, heo_buffer, heo_buffer1, heo_buffer2,
			                              16, 0, 0, image_width, image_height);
			break;
		case LCD_MODE_YUV422_SEMIPLANAR:
			lcdc_create_canvas_yuv_semiplanar(LCDC_HEO, heo_buffer, heo_buffer1,
			                                  16, 0, 0, image_width, image_height);
			break;
		case LCD_MODE_YUV420_PLANAR:
			lcdc_create_canvas_yuv_planar(LCDC_HEO, heo_buffer, heo_buffer1, heo_buffer2,
			                              12, 0, 0, image_width, image_height);
		case LCD_MODE_YUV420_SEMIPLANAR:
			lcdc_create_canvas_yuv_semiplanar(LCDC_HEO, heo_buffer, heo_buffer1,
			                                  12, 0, 0, image_width, image_height);
			break;
		case LCD_MODE_RGB565:
			lcdc_create_canvas(LCDC_HEO, heo_buffer, 16, 0, 0, image_width, image_height);
			break;
		}
	}
	lcdc_enable_layer(LCDC_HEO, 1);
}

/**
 * \brief ISC initialization.
 */
static void configure_isc(void)
{
	iscd.cfg.multi_bufs = ISC_MAX_NUM_FRAME_BUFFER;

	switch (lcd_mode) {
	case LCD_MODE_YUV422_PLANAR:
	case LCD_MODE_YUV420_PLANAR:
		iscd.cfg.layout = lcd_mode == LCD_MODE_YUV420_PLANAR ? ISCD_LAYOUT_YC420P : ISCD_LAYOUT_YC422P;
		iscd.pipe.rlp_mode = ISCD_RLP_MODE_YYCC_LIMIT;
		iscd.dma.address0 = (uint32_t)ISC_OUTPUT_BASE_ADDRESS;
		iscd.dma.address1 = (uint32_t)ISC_OUTPUT_BASE_ADDRESS2;
		iscd.dma.address2 = (uint32_t)ISC_OUTPUT_BASE_ADDRESS1;
		break;
	case LCD_MODE_YUV422_SEMIPLANAR:
	case LCD_MODE_YUV420_SEMIPLANAR:
		iscd.cfg.layout = lcd_mode == LCD_MODE_YUV420_SEMIPLANAR ? ISCD_LAYOUT_YC420SP : ISCD_LAYOUT_YC422SP;
		iscd.pipe.rlp_mode = ISCD_RLP_MODE_YYCC_LIMIT;
		iscd.dma.address0 = (uint32_t)ISC_OUTPUT_BASE_ADDRESS;
		iscd.dma.address1 = (uint32_t)ISC_OUTPUT_BASE_ADDRESS1 + 1;
		break;
	case LCD_MODE_RGB565:
		iscd.pipe.rlp_mode = ISCD_RLP_MODE_RGB565;
		iscd.cfg.layout = ISCD_LAYOUT_PACKED16;
		iscd.dma.address0 = (uint32_t)ISC_OUTPUT_BASE_ADDRESS;
		break;
	default:
		iscd.pipe.rlp_mode = ISCD_RLP_MODE_DAT8;
		iscd.cfg.layout = ISCD_LAYOUT_PACKED8;
		iscd.dma.address0 = (uint32_t)ISC_OUTPUT_BASE_ADDRESS;
		break;
	}

	iscd.cfg.input_bits = sensor_output_bit_width;
	iscd.pipe.bayer_pattern = ISCD_BGBG;
	/* For sensor 8-bit output, it is recommand to perform 
		12 bits to 10 bits compression is performed skipping two bits.*/
	iscd.pipe.gamma.gamma_enable = true;
	iscd.pipe.gamma.rg_enable = false;
	iscd.pipe.gamma.gg_enable = false;
	iscd.pipe.gamma.bg_enable = false;
	iscd.pipe.gamma.rg_table = NULL;
	iscd.pipe.gamma.gg_table = NULL;
	iscd.pipe.gamma.bg_table = NULL;
	iscd.pipe.cbc.bright = 0.0;
	iscd.pipe.cbc.contrast = 1.0;
	iscd.pipe.cs = &ref_cs;
	iscd.pipe.color_correction = &ref_cc;
	iscd.cfg.input_format = sensor_mode;
	iscd.pipe.histo_enable = true;
	iscd.pipe.histo_buf = buffer_histogram;
	iscd_pipe_start(&iscd);
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Application entry point for ISC example.
 *
 * \return Unused (ANSI-C compatibility).
 */
extern int main(void)
{
	uint8_t key;

	/* Output example information */
	console_example_info("ISC Example");

	printf("Image Sensor detection:\n\r");
	if ((sensor = sensor_detect(SENSOR_TWI_BUS, true, 0))) {
		if (sensor_setup(SENSOR_TWI_BUS, sensor, VGA, YUV_422) != SENSOR_OK) {
			printf("-E- Sensor setup failed.");
			while (1);
		}
	} else {
		printf("-E- Can't detect supported sensor connected to board\r\n");
		while (1);
	}

restart_sensor:
	printf("------------ %s -------------\n\r", sensor->name);
	printf("- 'Y' Test YUV mode input       -\n\r");
	printf("- 'B' Test RAW BAYER mode input -\n\r");
	printf("---------------------------------\n\r");
	sensor_mode = 0xff;
	while (sensor_mode == 0xff) {
		key = console_get_char();
		switch (key) {
		case 'Y':
		case 'y':
			sensor_mode = YUV_422;
			break;
		case 'B':
		case 'b':
			sensor_mode = RAW_BAYER;
			break;
		}
	}

	if (sensor_setup(SENSOR_TWI_BUS, sensor, QVGA, sensor_mode) != SENSOR_OK)
		trace_fatal("-E- Sensor setup failed.");

	/* Retrieve sensor output format and size */
	sensor_get_output(sensor, QVGA, sensor_mode, &sensor_output_bit_width,
	                  &image_width, &image_height);

	if (sensor_mode == RAW_BAYER) {
		printf("-----------------------------------\n\r");
		printf("- '0' Test RGB565 output \n\r");
		printf("- '1' Test YC422P output \n\r");
		printf("- '2' Test YC422SP output \n\r");
		printf("- '3' Test YC420P output \n\r");
		printf("- '4' Test YC420SP output \n\r");
		printf("-----------------------------------\n\r");
		lcd_mode = 0;
		while (!lcd_mode) {
			key = console_get_char();
			switch (key) {
			case '0':
				lcd_mode = LCD_MODE_RGB565;
				break;
			case '1':
				lcd_mode = LCD_MODE_YUV422_PLANAR;
				break;
			case '2':
				lcd_mode = LCD_MODE_YUV422_SEMIPLANAR;
				break;
			case '3':
				lcd_mode = LCD_MODE_YUV420_PLANAR;
				break;
			case '4':
				lcd_mode = LCD_MODE_YUV420_SEMIPLANAR;
				break;
			}
		}
	} else
		lcd_mode = LCD_MODE_YUV;

	printf("-I- Bit width = %d, Image Width = %d, Image Height=%d \n\r",
			(unsigned int)(sensor_output_bit_width + 8),
			(unsigned int)image_width, (unsigned int)image_height);

	configure_lcd();
	configure_isc();

	printf("-I- Preview start. \n\r");
	printf("-I- press 'S' or 's' to switch ISC mode. \n\r");
	if (sensor_mode == RAW_BAYER)
		printf("-I- press 'A' or 'a' to start auto white balance & AE. \n\r");

	awb = false;
	while (1) {
		if (console_is_rx_ready()) {
			key = console_get_char();
			switch (key) {
			case 'S':
			case 's':
				isc_stop_capture();
				goto restart_sensor;
			case 'A':
			case 'a':
				if (sensor_mode == RAW_BAYER)
					awb = true;
				break;
			}
		}
		if (awb)
			iscd_auto_white_balance_ref_algo(iscd.pipe.histo_buf);
	}

}
