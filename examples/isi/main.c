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
#include "cortex-a/mmu.h"

#include "misc/console.h"
#include "peripherals/twi.h"
#include "peripherals/twid.h"
#include "peripherals/isi.h"

#include "video/lcdd.h"
#include "video/image_sensor_inf.h"

#include "utils/trace.h"

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

#define ISI_DMA_DESC_PREV_ADDR             (ISI_CODEC_PATH_BASE_ADDRESS + ISI_MAX_IMAGE_SIZE)
#define ISI_DMA_DESC_CODEC_ADDR            (ISI_DMA_DESC_PREV_ADDR + 0x1000)

/** TWI clock frequency in Hz. */
#define TWCK                400000

/** TWI Pins definition */
#define BOARD_PINS_TWI_ISI PINS_TWI0

/** TWI peripheral ID for sensor TWI interface */
#define BOARD_ID_TWI_ISI   ID_TWI0

/** TWI base address for sensor TWI interface*/
#define BOARD_BASE_TWI_ISI TWI0

/** LCDD_OVR1 layer use for preview frame display in RGB output */
#define LCD_PREVIEW_LAYER  LCDD_OVR1

/** LCDD_HEO layer use for display captured image in YUV output */
#define LCD_CAPTURE_LAYER  LCDD_HEO

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/
extern const sensorProfile_t ov2640Profile;
extern const sensorProfile_t ov2643Profile;
extern const sensorProfile_t ov5640Profile;
extern const sensorProfile_t ov7740Profile;
extern const sensorProfile_t ov9740Profile;

/** Supported sensor profiles */ 
static const sensorProfile_t *sensorsProfile[5] = {&ov2640Profile, 
                                                  &ov2643Profile,
                                                  &ov5640Profile,
                                                  &ov7740Profile,
                                                  &ov9740Profile
};

/** Pio pins to configure. */
static const struct _pin pins_twi[] = BOARD_PINS_TWI_ISI;
static const struct _pin pin_rstn = PIN_ISI_RSTN;
static const struct _pin pins_isi[]= {PINS_ISI};
static const struct _pin pin_mck = PIN_ISI_MCK;
/** Pins for LCDC */
static const struct _pin pins_lcd[] = PINS_LCD;

/** ISI frame buffer descriptor */
#if defined ( __ICCARM__ ) /* IAR Ewarm */
#pragma data_alignment=64
#elif defined (  __GNUC__  ) /* GCC CS3 */
__attribute__((aligned(8)))
#endif
isi_frame_buffer_desc_t preview_path_fb_desc[ISI_MAX_NUM_PREVIVEW_BUFFER];

#if defined ( __ICCARM__ ) /* IAR Ewarm */
#pragma data_alignment=64
#elif defined (  __GNUC__  ) /* GCC CS3 */
__attribute__((aligned(8)))
#endif
isi_frame_buffer_desc_t codec_path_fb_desc[ISI_MAX_NUM_PREVIVEW_BUFFER];


/** TWI driver instance.*/
struct _twid twid;

/** LCD buffer.*/
static uint8_t *pOvr1Buffer = (uint8_t*)LCD_PREVIEW_BASE_ADDRESS;
static uint8_t *pHeoBuffer =  (uint8_t*)LCD_CAPTURED_BASE_ADDRESS;

/* Image size in preview mode */
static uint32_t wImageWidth, wImageHeight;

/* Image output format */
static sensorOutputFormat_t wImageFormat;

/* Image output bit width */
static sensorOutputBit_t wSensorOutBitWidth;

static isi_yuv2rgc_t y2r = {0x95, 0xFF, 0x68, 0x32, 1, 1, 1, 0xCC,};
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
	pmc_enable_peripheral(BOARD_ID_TWI_ISI);
	/* Configure TWI */
	twi_configure_master(BOARD_BASE_TWI_ISI, TWCK);
	twid_initialize(&twid, BOARD_BASE_TWI_ISI);
}

/**
 * \brief ISI MCK initialization.
 */
static void configure_isi_clock(void)
{
	/* Configure ISI pins. */
	pio_configure(pins_isi, ARRAY_SIZE(pins_isi));
	/* Configure RSTN pin. */
	pio_configure(&pin_rstn, 1);
	/* Configure PCK as peripheral */
	pio_configure(&pin_mck, 1);
	/* Configure PMC programmable clock(PCK0) */
	pmc_configure_pck1(PMC_PCK_CSS_MCK_CLK, 3);
	pmc_enable_pck1();
	/* ISI PWD OFF*/
	pio_clear(&pin_rstn);

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
}

/**
 * \brief Configure LCD controller.
 */
static void configure_lcd(void) 
{
	lcdd_initialize(pins_lcd, ARRAY_SIZE(pins_lcd));
    
	lcdc_configure_inputMode(LCD_PREVIEW_LAYER, LCDC_BASECFG1_RGBMODE_16BPP_RGB_565);
	lcdc_configure_inputMode(LCD_CAPTURE_LAYER, LCDC_HEOCFG1_YUVEN |
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
	isi_set_sensor_size(wImageWidth, wImageHeight);
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
						(BOARD_LCD_WIDTH -wImageWidth)/2,
						(BOARD_LCD_HEIGHT -wImageHeight)/2,
						wImageWidth, 
						wImageHeight);
	lcdd_create_canvas(LCD_CAPTURE_LAYER, 
						pHeoBuffer, 
						16, 
						(BOARD_LCD_WIDTH -wImageWidth)/2,
						(BOARD_LCD_HEIGHT -wImageHeight)/2,
						wImageWidth, 
						wImageHeight);
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
	uint8_t key;
	volatile uint32_t delay;
	
	wdt_disable() ;
    
	/* Output example information */
	printf( "-- ISI Example %s --\n\r", SOFTPACK_VERSION ) ;
	printf( "-- %s\n\r", BOARD_NAME ) ;
	printf( "-- Compiled: %s %s --\n\r", __DATE__, __TIME__ ) ;

	/* Initialize console */
	console_configure(CONSOLE_BAUDRATE);
	/* Configure LCD */
	configure_lcd();

	/* TWI Initialize */
	configure_twi();

	/* ISI PCK clock Initialize */
	configure_isi_clock();

	printf("Press [0|1|2|3|4][5] to select supported sensor \n\r");
	printf("- '0' omnivision 2640 \n\r");
	printf("- '1' omnivision 2643 \n\r");
	printf("- '2' omnivision 5640 \n\r");
	printf("- '3' omnivision 7740 \n\r");
	printf("- '4' omnivision 9740 \n\r");
	for(;;) {
		key = console_get_char();
		if ((key >= '0') && (key <='5')) {
			if (sensor_setup(&twid, sensorsProfile[key- '0'], VGA, YUV_422) != SENSOR_OK){
				printf("-E- Sensor setup failed.");
				while (1);
			} else {
				break;
			}
		}
	}
	/* Retrieve sensor output format and size */
	sensor_get_output(VGA, YUV_422, &wSensorOutBitWidth, &wImageWidth, &wImageHeight);
	wImageFormat = (sensorOutputFormat_t)YUV_INPUT;
	printf("Image attributes : <%x, %d, %d> \n\r", wImageFormat, wImageWidth,wImageHeight);
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
			lcdd_show_bmp_rotated(LCD_CAPTURE_LAYER, 
								NULL, 
								16, 
								(BOARD_LCD_WIDTH - wImageWidth)/2, 
								(BOARD_LCD_HEIGHT-  wImageHeight)/2, 
								wImageWidth, 
								wImageHeight,
								wImageWidth,
								wImageHeight,
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
