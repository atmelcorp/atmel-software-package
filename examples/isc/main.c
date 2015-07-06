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

/** Maximum number of preview buffer */
#define ISC_MAX_NUM_FRAME_BUFFER    4

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

/** LCDD_OVR1 layer use for preview frame display in RGB output */
#define LCD_PREVIEW_LAYER  LCDD_OVR1

/** LCDD_HEO layer use for display captured image in YUV output */
#define LCD_CAPTURE_LAYER  LCDD_HEO

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/
extern const sensorProfile_t ov7740Profile;

/** Pio pins to configure. */
const struct _pin pins_twi[] = PINS_TWI0_IOS4;
const struct _pin pin_rst = PIN_ISC_RST;
const struct _pin pin_pwd = PIN_ISC_PWD;
const struct _pin pins_isc[]= PINS_ISC_IOS3;

/** Video driver instance */

IscDmaDescView0  isc_dam_desc_linklist[ISC_MAX_NUM_FRAME_BUFFER + 1];


/** TWI driver instance.*/
Twihsd twid;

/** LCD buffer.*/
static uint8_t *pHeoBuffer =  (uint8_t*)LCD_PREVIEW_BASE_ADDRESS;

/* Image size in preview mode */
static uint32_t wImageWidth, wImageHeight;

/* Image output bit width */
static sensorOutputBit_t wSensorOutBitWidth;

/* Test mode for YUV for RAW BAYER */
static uint8_t testMode;

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
 * \brief TWI interrupt handler. Forwards the interrupt to the TWI driver handler.
 */
static void twi_handler(void )
{
	twihsd_handler( &twid );
}

/**
 * \brief ISC interrupt handler. 
 */
static void isc_handler(void )
{
	uint32_t status;
	status = isc_interrupt_status();
	if ((status & ISC_INTSR_DDONE) == ISC_INTSR_DDONE) {
		isc_start_capture();
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
	aic_set_source_vector(BOARD_ID_TWI_ISI, twi_handler);
	aic_enable(BOARD_ID_TWI_ISI);
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
	if( testMode == 0) {
		lcdc_configure_inputMode(LCD_CAPTURE_LAYER, 
								LCDC_HEOCFG1_YUVEN |LCDC_HEOCFG1_YUVMODE_16BPP_YCBCR_MODE2);
	} else {
		lcdc_configure_inputMode(LCD_CAPTURE_LAYER, LCDC_HEOCFG1_RGBMODE_16BPP_RGB_565);
	}
	lcdd_create_canvas(LCD_CAPTURE_LAYER, 
						pHeoBuffer, 
						16, 
						0,
						0,
						wImageWidth, 
						wImageHeight);
	
	lcdd_enable_layer(LCD_CAPTURE_LAYER, 1);
	printf("- LCD display on\n\r");
}

/**
 * \brief ISC initialization.
 */
static void configure_isc(void)
{
	isc_pfe_set_video_mode(ISC_PFE_CFG0_MODE_PROGRESSIVE);
	isc_pfe_set_bps(ISC_PFE_CFG0_BPS(wSensorOutBitWidth));
	isc_pfe_set_sync_polarity(0, ISC_PFE_CFG0_VPOL);
	isc_pfe_set_continuous_shot();
	
	if( testMode == 1) {
		isc_cfa_enabled(1);
		isc_cfa_configure(3, 1);
		isc_gamma_enabled(1, 0xE);
		isc_rlp_configure(ISC_RLP_CFG_MODE_RGB565, 0);
		isc_dma_configure_input_mode(ISC_DCFG_IMODE_PACKED16);
	} else {
		//isc_gamma_enabled(1, 0x0);
		isc_rlp_configure(ISC_RLP_CFG_MODE_DAT8, 0);
		isc_dma_configure_input_mode(ISC_DCFG_IMODE_PACKED8);
	}
	isc_update_profile();
	
	isc_enable_interrupt( 0xFFFFFFFF);
	aic_set_source_vector(ID_ISC, isc_handler);
	aic_enable(ID_ISC);

	isc_dma_configure_desc_entry((uint32_t)&isc_dam_desc_linklist[0]);
	isc_dma_enable( ISC_DCTRL_DVIEW_PACKED | ISC_DCTRL_DE  );
	isc_dma_adderss(ISC_OUTPUT_BASE_ADDRESS);
	isc_start_capture();
	
}

/**
 * \brief Set up Frame Buffer Descriptors(FBD) for preview path.
 */
static void configure_dma_linklist(void)
{
	 uint32_t i;
	for(i = 0; i < ISC_MAX_NUM_FRAME_BUFFER; i++) {
		
		isc_dam_desc_linklist[i].isc_dma_ctrl = ISC_DCTRL_DVIEW_PACKED | ISC_DCTRL_DE ;
		isc_dam_desc_linklist[i].isc_dma_nda =(uint32_t)&isc_dam_desc_linklist[i + 1];
		isc_dam_desc_linklist[i].isc_dma_addr = (uint32_t)ISC_OUTPUT_BASE_ADDRESS ;
		isc_dam_desc_linklist[i].isc_dma_stride = 0;
	}
	/* Wrapping to first view of descriptor */
	isc_dam_desc_linklist[i-1].isc_dma_nda = (uint32_t)&isc_dam_desc_linklist[0];
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
	uint8_t i;
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
	printf("- 'Y' Test 7740 for YUV mode \n\r");
	printf("- 'B' Test 7740 for RAW BAYER mode \n\r");
	printf("-----------------------------------\n\r");
	
	for(;;) {
		key = console_get_char();
		if ((key == 'Y') || (key == 'y')) {
			testMode = 0;
			break;
		}
		if ((key == 'B') || (key == 'b')) {
			testMode = 1;
			break;
		}
	}
	
	if(sensor_setup(&twid, &ov7740Profile, QVGA, ((testMode == 0)? YUV_422: RAW_BAYER)) 
		!= SENSOR_OK){
		printf("-E- Sensor setup failed \n\r");
		while(1);
	}
	
	/* Retrieve sensor output format and size */
	sensor_get_output(QVGA, ((testMode == 0)? YUV_422: RAW_BAYER), &wSensorOutBitWidth, 
					&wImageWidth, &wImageHeight);
	
	/* Set up Gamma table */
	for (i = 0; i< 64; i++){
		ISC->ISC_GAM_RENTRY[i] = gGam[i];
		ISC->ISC_GAM_GENTRY[i] = gGam[i];
		ISC->ISC_GAM_BENTRY[i] = gGam[i];
	}
	printf("Bit width = %d, Image Width = %d, Image Height=%d \n\r", 
				(wSensorOutBitWidth +8), wImageWidth, wImageHeight);

	/* Configure LCD */
	configure_lcd(); 
	configure_dma_linklist();
	configure_isc();
	printf("preview start...\n\r");
	while(1);

}

