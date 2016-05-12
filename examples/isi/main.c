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
 * - twi.c
 * - twid.c
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

#include "peripherals/aic.h"
#include "peripherals/pmc.h"
#include "peripherals/wdt.h"
#include "peripherals/pio.h"
#include "misc/cache.h"

#include "misc/console.h"
#include "peripherals/twi.h"
#include "peripherals/twid.h"
#include "peripherals/isi.h"

#include "video/lcdd.h"
#include "video/image_sensor_inf.h"

#include "trace.h"
#include "timer.h"

#include <stdbool.h>
#include <stdio.h>


/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** Frame buffer base address in preview path */
#define ISI_PREVIEW_PATH_BASE_ADDRESS  (DDR_CS_ADDR + 16* 1024 * 1024)

/** Maximum number of preview buffer */
#define ISI_MAX_NUM_PREVIVEW_BUFFER    2

/** Maximum image size (YUV)*/
#define ISI_MAX_IMAGE_SIZE            (1600 * 1200 * 2)

/** LCD buffer start address for preview mode (same address for ISI preview buffer) */
#define LCD_PREVIEW_BASE_ADDRESS      ISI_PREVIEW_PATH_BASE_ADDRESS

/** Frame buffer base address in codec path */
#define ISI_CODEC_PATH_BASE_ADDRESS   (ISI_PREVIEW_PATH_BASE_ADDRESS + ISI_MAX_IMAGE_SIZE * ISI_MAX_NUM_PREVIVEW_BUFFER)

/** LCD buffer start address for captured image (same address for ISI codec buffer) */
#define LCD_CAPTURED_BASE_ADDRESS      ISI_CODEC_PATH_BASE_ADDRESS

#define ISI_DMA_DESC_PREV_ADDR        (ISI_CODEC_PATH_BASE_ADDRESS + ISI_MAX_IMAGE_SIZE)
#define ISI_DMA_DESC_CODEC_ADDR       (ISI_DMA_DESC_PREV_ADDR + 0x1000)

/** TWI clock frequency in Hz. */
#define TWCK                400000

/** LCDD_OVR1 layer use for preview frame display in RGB output */
#define LCD_PREVIEW_LAYER  LCDD_OVR1

/** LCDD_HEO layer use for display captured image in YUV output */
#define LCD_CAPTURE_LAYER  LCDD_HEO

/*----------------------------------------------------------------------------
 *        Local variables/constants
 *----------------------------------------------------------------------------*/

static const struct _lcdd_desc lcd_desc = {
	.width = BOARD_LCD_WIDTH,
	.height = BOARD_LCD_HEIGHT,
	.framerate = BOARD_LCD_FRAMERATE,
	.timing_vfp = BOARD_LCD_TIMING_VFP,
	.timing_vbp = BOARD_LCD_TIMING_VBP,
	.timing_vpw = BOARD_LCD_TIMING_VPW,
	.timing_hfp = BOARD_LCD_TIMING_HFP,
	.timing_hbp = BOARD_LCD_TIMING_HBP,
	.timing_hpw = BOARD_LCD_TIMING_HPW,
};

/** Supported sensor profiles */
static const sensor_profile_t *sensor_profiles[6] = {
	&ov2640_profile,
	&ov2643_profile,
	&ov5640_profile,
	&ov7670_profile,
	&ov7740_profile,
	&ov9740_profile
};

/** PIO pins to configured. */
const struct _pin pins_twi[] = BOARD_ISI_TWI_PINS;
const struct _pin pin_rst = BOARD_ISI_RST_PIN;
const struct _pin pin_pwd = BOARD_ISI_PWD_PIN;
const struct _pin pins_isi[]= BOARD_ISI_PINS;

/** Pins for LCDC */
static const struct _pin pins_lcd[] = BOARD_LCD_PINS;

/** ISI frame buffer descriptor */
ALIGNED(8) isi_frame_buffer_desc_t preview_path_fb_desc[ISI_MAX_NUM_PREVIVEW_BUFFER];

ALIGNED(8) isi_frame_buffer_desc_t codec_path_fb_desc[ISI_MAX_NUM_PREVIVEW_BUFFER];

/** TWI driver instance.*/
static struct _twi_desc twid = {
	.addr = BOARD_ISI_TWI_ADDR,
	.freq = TWCK,
	.transfert_mode = TWID_MODE_POLLING
};

/** LCD buffer.*/
static uint8_t *pOvr1Buffer = (uint8_t*)LCD_PREVIEW_BASE_ADDRESS;
static uint8_t *pHeoBuffer =  (uint8_t*)LCD_CAPTURED_BASE_ADDRESS;

/* Image size in preview mode */
static uint32_t image_width, image_height;

/* Image output format */
static sensor_output_format_t image_format;

/* Image output bit width */
static sensor_output_bit_t sensor_bit_width;

static isi_yuv2rgb_t y2r = {0x95, 0xFF, 0x68, 0x32, 1, 1, 1, 0xCC,};
/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

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
 * \brief ISI MCK initialization.
 */
static void configure_isi_clock(void)
{
	/* Configure PMC programmable clock(PCK0) */
	pmc_configure_pck1(PMC_PCK_CSS_MCK_CLK, 3);
	pmc_enable_pck1();
}


/**
 * \brief Hardware reset sensor.
 */
static void sensor_reset(void)
{
	pio_configure(&pin_rst,1);
	pio_configure(&pin_pwd,1);
	pio_clear(&pin_pwd);
	pio_clear(&pin_rst);
	pio_set(&pin_rst);
	timer_wait(10);
}

/**
 * \brief Set up Frame Buffer Descriptors(FBD) for preview path.
 */
static void configure_frame_buffer(void)
{
	uint32_t i;
	for(i = 0; i < ISI_MAX_NUM_PREVIVEW_BUFFER; i++) {
		preview_path_fb_desc[i].address = (uint32_t)ISI_PREVIEW_PATH_BASE_ADDRESS ;
		preview_path_fb_desc[i].control = ISI_DMA_P_CTRL_P_FETCH | ISI_DMA_P_CTRL_P_WB;
		preview_path_fb_desc[i].next    = (uint32_t)&preview_path_fb_desc[i + 1];
	}
	/* Wrapping to first FBD */
	preview_path_fb_desc[i-1].next = (uint32_t)&preview_path_fb_desc[0];

	for(i = 0; i < ISI_MAX_NUM_PREVIVEW_BUFFER; i++) {
		codec_path_fb_desc[i].address = (uint32_t)ISI_CODEC_PATH_BASE_ADDRESS;
		codec_path_fb_desc[i].control = ISI_DMA_C_CTRL_C_FETCH | ISI_DMA_C_CTRL_C_WB;
		codec_path_fb_desc[i].next    = (uint32_t)&codec_path_fb_desc[ i + 1];
	}
	/* Wrapping to first FBD */
	codec_path_fb_desc[i-1].next = (uint32_t)&codec_path_fb_desc[0];
	cache_clean_region(preview_path_fb_desc, sizeof(preview_path_fb_desc));
	cache_clean_region(codec_path_fb_desc, sizeof(codec_path_fb_desc));
}

/**
 * \brief Configure LCD controller.
 */
static void configure_lcd(void)
{
	pio_configure(pins_lcd, ARRAY_SIZE(pins_lcd));
	lcdd_configure(&lcd_desc);

	lcdd_configure_input_mode(LCD_PREVIEW_LAYER, LCDC_BASECFG1_RGBMODE_16BPP_RGB_565);
	lcdd_configure_input_mode(LCD_CAPTURE_LAYER, LCDC_HEOCFG1_YUVEN |
							LCDC_HEOCFG1_YUVMODE_16BPP_YCBCR_MODE3);
	printf("- LCD display on\n\r");
}

/**
 * \brief ISI initialization.
 */
static void configure_isi(void)
{
	/* Enable ISI peripheral clock */
	pmc_enable_peripheral(ID_ISI);

	/* Set up Frame Buffer Descriptors(FBD) for preview path. */
	configure_frame_buffer();
	/* Reset ISI peripheral */
	isi_reset();
	/* Set the windows blank */
	isi_set_blank(0, 0);
	/* Set vertical and horizontal Size of the Image Sensor for preview path*/
	isi_set_sensor_size(image_width, image_height);
	/* Set preview size to fit LCD size*/
	isi_set_preview_size(BOARD_LCD_WIDTH, BOARD_LCD_HEIGHT );
	/* calculate scaler factor automatically. */
	isi_calc_scaler_factor();
	/*  Set data stream in YUV/RGB format.*/
	isi_set_input_stream(0);
	/* Defines YCrCb swap format.*/
	isi_ycrcb_format(ISI_CFG2_YCC_SWAP_MODE2);
	/* Set Matrix color space for YUV to RBG convert */
	isi_set_matrix_yuv2rgb(&y2r);

	/* Configure DMA for preview path. */
	isi_set_dma_preview_path((uint32_t)&preview_path_fb_desc[0],
							ISI_DMA_P_CTRL_P_FETCH,
							(uint32_t)ISI_PREVIEW_PATH_BASE_ADDRESS);

	/* Configure DMA for preview path. */
	isi_set_dma_codec_path((uint32_t)&codec_path_fb_desc[0],
							ISI_DMA_C_CTRL_C_FETCH,
							(uint32_t)ISI_CODEC_PATH_BASE_ADDRESS);

	lcdd_create_canvas(LCD_PREVIEW_LAYER,
						pOvr1Buffer,
						16,
						(BOARD_LCD_WIDTH -image_width)/2,
						(BOARD_LCD_HEIGHT -image_height)/2,
						image_width,
						image_height);
	lcdd_create_canvas(LCD_CAPTURE_LAYER,
						pHeoBuffer,
						16,
						(BOARD_LCD_WIDTH -image_width)/2,
						(BOARD_LCD_HEIGHT -image_height)/2,
						image_width,
						image_height);
	isi_reset();
	isi_disable_interrupt(0xFFFFFFFF);
	isi_enable();
	isi_dma_codec_channel_enabled(1);
	isi_dma_preview_channel_enabled(1);
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
	int i;
	uint8_t key;
	volatile uint32_t delay;

	wdt_disable();

	/* Initialize console */
	board_cfg_console(0);

	/* Output example information */
	printf( "-- ISI Example %s --\n\r", SOFTPACK_VERSION ) ;
	printf( "-- %s\n\r", BOARD_NAME ) ;
	printf( "-- Compiled: %s %s --\n\r", __DATE__, __TIME__ ) ;

	/* Configure LCD */
	configure_lcd();

	/* TWI Initialize */
	configure_twi();

	/* Configure ISI pins. */
	pio_configure(pins_isi, ARRAY_SIZE(pins_isi));

	/* ISI PCK clock Initialize */
	configure_isi_clock();
	sensor_reset();

	printf("Image Sensor Selection:\n\r");
	for (i = 0; i < ARRAY_SIZE(sensor_profiles); i++)
		printf("- '%d' %s\n\r", i + 1, sensor_profiles[i]->name);
	for(;;) {
		printf("Press [1..%d] to select supported sensor\n\r",
			ARRAY_SIZE(sensor_profiles));
		key = console_get_char();
		if ((key >= '1') && (key <= ('1' + ARRAY_SIZE(sensor_profiles)))) {
			if (sensor_setup(&twid, sensor_profiles[key - '1'], VGA, YUV_422) != SENSOR_OK){
				printf("-E- Sensor setup failed.");
				while (1);
			} else {
				break;
			}
		}
	}

	/* Retrieve sensor output format and size */
	sensor_get_output(VGA, YUV_422, &sensor_bit_width, &image_width, &image_height);
	image_format = (sensor_output_format_t)YUV_INPUT;
	printf("Image attributes : <%x, %u, %u>\n\r", image_format,
			(unsigned)image_width, (unsigned)image_height);
	printf("preview in RGB 565 mode\n\r");

	/* ISI Initialize */
	configure_isi();

	printf("-I- \n\r");
	printf("-I- Press 'C' to capture image, press 'P' back to preview mode \n\r");
	for(;;) {
		key = console_get_char();
		switch(key){
		case 'c': case 'C':
			printf("Capture image from CODEC path in YUV mode\n\r");
			lcdd_enable_layer(LCD_PREVIEW_LAYER, 0);
			isi_dma_preview_channel_enabled(0);
			isi_dma_codec_channel_enabled(1);
			for (delay = 0; delay < 0xffff; delay++);
			isi_codec_request();
			isi_codec_wait_dma_completed();
			printf("-I- Capture done \r\n");
			for (delay = 0; delay < 0x5ffff; delay++);
			lcdd_put_image_rotated(LCD_CAPTURE_LAYER,
								NULL,
								16,
								(BOARD_LCD_WIDTH - image_width)/2,
								(BOARD_LCD_HEIGHT-  image_height)/2,
								image_width,
								image_height,
								image_width,
								image_height,
								0);
			lcdd_enable_layer(LCD_CAPTURE_LAYER, 1);
			break;
		case 'p': case 'P':
			printf("preivew in RGB 565 mode\n\r");
			isi_dma_codec_channel_enabled(0);
			isi_dma_preview_channel_enabled(1);
			lcdd_enable_layer(LCD_CAPTURE_LAYER, 0);
			lcdd_enable_layer(LCD_PREVIEW_LAYER, 1);
			break;
		}
	}
}
