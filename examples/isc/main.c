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
 * The provided program uses the Image Sensor Controller (ISC) system,  it manages 
 * incoming data from a parallel CMOS sensor (ov7740) . It support sensor with a 
 * data width of 8 bits in YUV format and 10 bits raw Bayer format. This example 
 * show how to configure the internal image processor includes color filter array 
 * interpolation, gamma correction, 12 bits to 10 bits compression, and transfer 
 * data stream with DMA 8/16 package.
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
 *     -- ISI Example xxx --
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

#include "peripherals/aic.h"
#include "peripherals/pmc.h"
#include "peripherals/wdt.h"
#include "peripherals/pio.h"
#include "cortex-a/mmu.h"

#include "misc/console.h"
#include "peripherals/twihs.h"
#include "peripherals/twihsd.h"
#include "peripherals/isc.h"


#include "video/lcdd.h"
#include "video/lcd_draw.h"
#include "video/image_sensor_inf.h"

#include "utils/trace.h"

#include <stdbool.h>
#include <stdio.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** Frame buffer base address in preview path */
#define ISC_OUTPUT_BASE_ADDRESS  (DDR_CS_ADDR + 16 * 1024 * 1024)
#define ISC_OUTPUT_BASE_ADDRESS1  (ISC_OUTPUT_BASE_ADDRESS + 0x400000)
#define ISC_OUTPUT_BASE_ADDRESS2  (ISC_OUTPUT_BASE_ADDRESS1 + 0x400000)

#define LCD_MODE_YUV          (LCDC_HEOCFG1_YUVEN | LCDC_HEOCFG1_YUVMODE_16BPP_YCBCR_MODE2)
#define LCD_MODE_RGB565       LCDC_HEOCFG1_RGBMODE_16BPP_RGB_565
#define LCD_MODE_YUV_PLANAR   (LCDC_HEOCFG1_YUVEN |LCDC_HEOCFG1_YUVMODE_16BPP_YCBCR_PLANAR)

/** Maximum number of preview buffer */
#define ISC_MAX_NUM_FRAME_BUFFER    1

/** Maximum image size (YUV)*/
#define ISC_MAX_IMAGE_SIZE            (1600 * 1200 * 2)

/** LCD buffer start address for preview mode (same address for ISI preview buffer) */
#define LCD_PREVIEW_BASE_ADDRESS      ISC_OUTPUT_BASE_ADDRESS

/** TWI clock frequency in Hz. */
#define TWCK                  400000

/** TWI peripheral ID for sensor TWI interface */
#define BOARD_ID_TWI_ISI     ID_TWIHS0

/** TWI base address for sensor TWI interface*/
#define BOARD_BASE_TWI_ISI   TWIHS0

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/
extern const sensorProfile_t ov7740Profile;

/** PIO pins to configured. */
const struct _pin pins_twi[] = PINS_TWI0_IOS4;
const struct _pin pin_rst = PIN_ISC_RST;
const struct _pin pin_pwd = PIN_ISC_PWD;
const struct _pin pins_isc[]= PINS_ISC_IOS3;

/** Descriptor view 0 is used when the pixel or data stream is packed */
#if defined ( __ICCARM__ )	/* IAR Ewarm */
#pragma data_alignment=64
#elif defined (  __GNUC__  ) /* GCC CS3 */
__attribute__ ((aligned(64)))
#endif
static IscDmaDescView0 isc_dam_desc_linklist[ISC_MAX_NUM_FRAME_BUFFER + 1];

/** Descriptor view 2 is used for YCbCr planar pixel stream. */
#if defined ( __ICCARM__ )	/* IAR Ewarm */
#pragma data_alignment=64
#elif defined (  __GNUC__  ) /* GCC CS3 */
__attribute__ ((aligned(64)))
#endif
static IscDmaDescView2 isc_dam_desc_linklist2[ISC_MAX_NUM_FRAME_BUFFER + 1];

/** TWI driver instance.*/
Twihsd twid;

/** LCD buffer.*/
static uint8_t *pHeoBuffer =  (uint8_t*)LCD_PREVIEW_BASE_ADDRESS;
static uint8_t *pHeoBuffer1 =  (uint8_t*)ISC_OUTPUT_BASE_ADDRESS1;
static uint8_t *pHeoBuffer2 =  (uint8_t*)ISC_OUTPUT_BASE_ADDRESS2;

/* Image size in preview mode */
static uint32_t wImageWidth, wImageHeight;

/* Image output bit width */
static sensorOutputBit_t wSensorOutBitWidth;

/* Sensor mode for YUV or RAW BAYER */
static sensorOutputFormat_t sensorMode;

/* LCD mode */
static uint32_t lcdMode;

volatile static uint32_t capture_started = 0;

/* Color space matrix setting */
static sColorSpaceComponents cs = {
0x42, 0x81, 0x19 , 
0x10, 0xFDA, 0xFB6, 
0x70, 0x80, 0x70, 
0xFA2, 0xFEE, 0x80};

/* Gamma table with gamma 1/2.2 */
const uint32_t gGam[64] = {
0x2B0079 ,0x9C0039 ,0xD4002B ,0xFF0024 ,0x122001F,0x141001C,0x15D0019,0x1760018,
0x18E0016,0x1A40015,0x1B80014,0x1CC0013,0x1DE0012,0x1F00011,0x2010010,0x2110010,
0x221000F,0x230000F,0x23F000E,0x24D000E,0x25B000D,0x269000D,0x276000D,0x283000D,
0x28F000C,0x29C000C,0x2A8000C,0x2B4000C,0x2BF000B,0x2CA000B,0x2D6000B,0x2E0000B,
0x2EB000A,0x2F6000A,0x300000A,0x30A000A,0x314000A,0x31E000A,0x328000A,0x3310009,
0x33B0009,0x3440009,0x34D0009,0x3570009,0x3600009,0x3680009,0x3710009,0x37A0009,
0x3820008,0x38B0008,0x3930008,0x39B0008,0x3A40008,0x3AC0008,0x3B40008,0x3BC0008,
0x3C40008,0x3CB0008,0x3D30008,0x3DB0008,0x3E20007,0x3EA0007,0x3F10007,0x3F90007
 };

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
/**
 * \brief ISC interrupt handler. 
 */
static void isc_handler(void )
{
	uint32_t status;
	status = isc_interrupt_status();
	if((status & ISC_INTSR_HD) == ISC_INTSR_HD) {
	}
	if((status & ISC_INTSR_VD) == ISC_INTSR_VD){
		if (!capture_started){
			isc_start_capture();
			capture_started = 1;
		}
	}
	if ((status & ISC_INTSR_DDONE) == ISC_INTSR_DDONE) {
	}
 	if ((status & ISC_INTSR_LDONE) == ISC_INTSR_LDONE) {
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
	pmc_enable_peripheral(BOARD_ID_TWI_ISI);
	/* Configure TWI */
	twihs_configure_master(BOARD_BASE_TWI_ISI, TWCK);
	twihsd_initialize(&twid, BOARD_BASE_TWI_ISI);
	/* Configure TWI interrupts */
}

/**
 * \brief ISI PCK initialization.
 */
static void configure_mck_clock(void)
{
	PMC->PMC_PCR = PMC_PCR_CMD|PMC_PCR_EN |ID_ISC;
	PMC->PMC_SCER|= 1 << 18 ;

	isc_configure_master_clock(6 ,0);
	while((ISC->ISC_CLKSR & ISC_CLKSR_SIP) == ISC_CLKSR_SIP);
	isc_enable_master_clock();

	isc_configure_isp_clock(5 ,0);
	while((ISC->ISC_CLKSR & ISC_CLKSR_SIP) == ISC_CLKSR_SIP);
	isc_enable_isp_clock();
	
}

static void sensor_reset(void)
{
	pio_configure(&pin_rst,1);
	pio_configure(&pin_pwd,1);
	pio_clear(&pin_pwd);
	pio_clear(&pin_rst);
	pio_set(&pin_rst);
}

/**
 * \brief Configure LCD controller.
 */
static void configure_lcd(void) 
{
	lcdd_initialize();
	if( sensorMode == YUV_422) {
		lcdc_configure_inputMode(LCDD_HEO, LCD_MODE_YUV);
		lcdd_create_canvas(LCDD_HEO, 
						pHeoBuffer, 
						16, 
						0,
						0,
						wImageWidth, 
						wImageHeight);
	} else {
		if (lcdMode == LCD_MODE_YUV_PLANAR){
			lcdc_configure_inputMode(LCDD_HEO, LCD_MODE_YUV_PLANAR);
			lcdd_create_canvas_yuv_planar(LCDD_HEO, 
						pHeoBuffer,
						pHeoBuffer1,
						pHeoBuffer2,
						16, 
						0,
						0,
						wImageWidth, 
						wImageHeight);
		}
		if (lcdMode == LCD_MODE_RGB565){
			lcdc_configure_inputMode(LCDD_HEO, LCD_MODE_RGB565);
			lcdd_create_canvas(LCDD_HEO, 
						pHeoBuffer, 
						16, 
						0,
						0,
						wImageWidth, 
						wImageHeight);
		}
	}
	lcdd_enable_layer(LCDD_HEO, 1);
}

/**
 * \brief ISC initialization.
 */
static void configure_isc(void)
{
	uint32_t i;
	/* Configurer the Parallel Front End module performs data re-sampling across 
	clock domain boundary. ISC_PFE_CFG0.BPS shows the number of bits per sample 
	depends on the bit width of sensor output. 
	The PFE module outputs a 12-bit data on the vp_data[11:0] bus */

	isc_pfe_set_video_mode(ISC_PFE_CFG0_MODE_PROGRESSIVE);
	isc_pfe_set_bps(ISC_PFE_CFG0_BPS(wSensorOutBitWidth));
	isc_pfe_set_sync_polarity(0, ISC_PFE_CFG0_VPOL);
	
	/* Set Continuous Acquisition mode */
	isc_pfe_set_continuous_shot();
	
	if( sensorMode == RAW_BAYER) {
		/* In a single-sensor system, each cell on the sensor has a specific 
		color filter and microlens positioned above it. The raw data obtained 
		from the sensor do not have the full R/G/B information at each cell 
		position. Color interpolation is required to retrieve the missing 
		components. */
		isc_cfa_enabled(1);
		isc_cfa_configure( ISC_CFA_CFG_BAYCFG_BGBG, 1);
		
		/* Set up Gamma table with gamma 1/2.2 */
		for (i = 0; i< 64; i++){
			ISC->ISC_GAM_RENTRY[i] = gGam[i];
			ISC->ISC_GAM_GENTRY[i] = gGam[i];
			ISC->ISC_GAM_BENTRY[i] = gGam[i];
		}
		
		isc_gamma_enabled(1, ISC_GAM_CTRL_BENABLE |
							 ISC_GAM_CTRL_GENABLE | 
							 ISC_GAM_CTRL_RENABLE );
		
		if (lcdMode == LCD_MODE_YUV_PLANAR) {
			/* By converting an image from RGB to YCbCr color space, it is possible 
				to separate Y, Cb and Cr information. */
			isc_csc_enabled(1);
			isc_csc_configure(&cs);
			/* The color space conversion output stream is a full-bandwidth YCbCr 
				4:4:4 signal. The chrominance subsampling divides the horizontal 
				chrominance sampling rate by two */
			isc_sub422_enabled(1);
			/* Configure limited YCrcb output format before the DMA master module */
			isc_rlp_configure(ISC_RLP_CFG_MODE_YYCC_LIMITED, 0);
			/* Set DAM for 16-bit YC422P with stream descriptor view 2 for 
				YCbCr planar pixel stream*/
			isc_dma_configure_input_mode(ISC_DCFG_IMODE_YC422P | 
										ISC_DCFG_YMBSIZE_BEATS8 |
										ISC_DCFG_CMBSIZE_BEATS8);
			isc_dma_configure_desc_entry((uint32_t)&isc_dam_desc_linklist2[0]);
			isc_dma_enable( ISC_DCTRL_DVIEW_PLANAR | ISC_DCTRL_DE  );
			ISC->ISC_SUB0[0].ISC_DAD = ISC_OUTPUT_BASE_ADDRESS;
			ISC->ISC_SUB0[1].ISC_DAD = ISC_OUTPUT_BASE_ADDRESS2;
			ISC->ISC_SUB0[2].ISC_DAD = ISC_OUTPUT_BASE_ADDRESS1;
		}
		if (lcdMode == LCD_MODE_RGB565) {
			/* Configure RGB 565 output format before the DMA master module */
			isc_rlp_configure(ISC_RLP_CFG_MODE_RGB565, 0);
			/* Set DAM for 16-bit packaged stream with descriptor view 0 used 
				for the data stream is packed. */
			isc_dma_configure_input_mode(ISC_DCFG_IMODE_PACKED16);
			isc_dma_configure_desc_entry((uint32_t)&isc_dam_desc_linklist[0]);
			isc_dma_enable( ISC_DCTRL_DVIEW_PACKED | ISC_DCTRL_DE  );
			isc_dma_adderss(ISC_OUTPUT_BASE_ADDRESS);
		}
	} 
	if( sensorMode == YUV_422) {
		/* Configure DAT8 output format before the DMA master module */
		isc_rlp_configure(ISC_RLP_CFG_MODE_DAT8, 0);
		/* Set DAM for 8-bit packaged stream with descriptor view 0 used 
				for the data stream is packed*/
		isc_dma_configure_input_mode(ISC_DCFG_IMODE_PACKED8);
		isc_dma_configure_desc_entry((uint32_t)&isc_dam_desc_linklist[0]);
		isc_dma_enable( ISC_DCTRL_DVIEW_PACKED | ISC_DCTRL_DE  );
		isc_dma_adderss(ISC_OUTPUT_BASE_ADDRESS);
	}
	
	isc_update_profile();
	
	aic_set_source_vector(ID_ISC, isc_handler);
	i = isc_interrupt_status();
	isc_enable_interrupt( 0xFFFFFFFF);
	isc_interrupt_status();
	aic_enable(ID_ISC);
}

/**
 * \brief Set up DMA Descriptors.
 */
static void configure_dma_linklist(void)
{
	uint32_t i;
	if (lcdMode == LCD_MODE_YUV_PLANAR){
		for(i = 0; i < ISC_MAX_NUM_FRAME_BUFFER; i++) {
			isc_dam_desc_linklist2[i].isc_dma_ctrl = ISC_DCTRL_DVIEW_PLANAR | ISC_DCTRL_DE ;
			isc_dam_desc_linklist2[i].isc_dma_nda =(uint32_t)&isc_dam_desc_linklist2[i + 1 ];
			isc_dam_desc_linklist2[i].isc_dma_addr0 = (uint32_t)ISC_OUTPUT_BASE_ADDRESS ;
			isc_dam_desc_linklist2[i].isc_dma_stride0 = 0;
			isc_dam_desc_linklist2[i].isc_dma_addr1 = (uint32_t)ISC_OUTPUT_BASE_ADDRESS2 ;
			isc_dam_desc_linklist2[i].isc_dma_stride1 = 0;
			isc_dam_desc_linklist2[i].isc_dma_addr2 = (uint32_t)ISC_OUTPUT_BASE_ADDRESS1 ;
			isc_dam_desc_linklist2[i].isc_dma_stride2 = 0;
		}
		isc_dam_desc_linklist2[i-1].isc_dma_nda = (uint32_t)&isc_dam_desc_linklist2[0];
	} else {
		for(i = 0; i < ISC_MAX_NUM_FRAME_BUFFER; i++) {
			isc_dam_desc_linklist[i].isc_dma_ctrl = ISC_DCTRL_DVIEW_PACKED | ISC_DCTRL_DE ;
			isc_dam_desc_linklist[i].isc_dma_nda =(uint32_t)&isc_dam_desc_linklist[i + 1];
			isc_dam_desc_linklist[i].isc_dma_addr = (uint32_t)ISC_OUTPUT_BASE_ADDRESS ;
			isc_dam_desc_linklist[i].isc_dma_stride = 0;
		}
		isc_dam_desc_linklist[i-1].isc_dma_nda = (uint32_t)&isc_dam_desc_linklist[0];
	}
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
	volatile uint32_t i;
	uint8_t key;
	
	wdt_disable() ;
	
	/* Initialize console */
	console_configure(CONSOLE_BAUDRATE);

	/* Output example information */
	printf( "-- ISC Example %s --\n\r", SOFTPACK_VERSION ) ;
	printf( "-- %s\n\r", BOARD_NAME ) ;
	printf( "-- Compiled: %s %s --\n\r", __DATE__, __TIME__ ) ;

	board_cfg_ddram();

	/* TWI Initialize */
	configure_twi();
	
	/* Configure all ISC pins */
	pio_configure(pins_isc, ARRAY_SIZE(pins_isc));

	/* ISI PCK clock Initialize */
	configure_mck_clock();
	
	/* Reset Sensor board */
	sensor_reset();
	printf("-----------------------------------\n\r");
	printf("- 'Y' Test OV7740 YUV mode input \n\r");
	printf("- 'B' Test OV7740 RAW BAYER mode input \n\r");
	printf("-----------------------------------\n\r");
	for(;;) {
		key = console_get_char();
		if ((key == 'Y') || (key == 'y')) {
			sensorMode = YUV_422;
			break;
		}
		if ((key == 'B') || (key == 'b')) {
			sensorMode = RAW_BAYER;
			break;
		}
	}
	
	if(sensor_setup(&twid, &ov7740Profile, QVGA, sensorMode) 
		!= SENSOR_OK){
		printf("-E- Sensor setup failed \n\r");
		while(1);
	}
	
	/* Retrieve sensor output format and size */
	sensor_get_output(QVGA, sensorMode, &wSensorOutBitWidth, &wImageWidth, &wImageHeight);
	if (sensorMode == RAW_BAYER ){
		printf("-----------------------------------\n\r");
		printf("- 'R' Test RGB565 output \n\r");
		printf("- 'Y' Test YC422P output \n\r");
		printf("-----------------------------------\n\r");
		for(;;) {
			key = console_get_char();
			if ((key == 'R') || (key == 'r')) {
				lcdMode = LCD_MODE_YUV_PLANAR;
				break;
			}
			if ((key == 'Y') || (key == 'y')) {
				lcdMode = LCD_MODE_RGB565;
				break;
			}
		}
	} else {
		lcdMode = LCD_MODE_YUV ;
	}
	
	printf("Bit width = %d, Image Width = %d, Image Height=%d \n\r", 
				(wSensorOutBitWidth + 8 ), wImageWidth, wImageHeight);

	/* Configure LCD */
	configure_lcd(); 
	configure_dma_linklist();
	configure_isc();
	printf("Preview start...\n\r"); 
	while(1);
}

