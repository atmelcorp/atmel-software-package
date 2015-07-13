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

#include "video/lcdd.h"
#include "utils/lcd_draw.h"

#include "utils/trace.h"

#include <stdbool.h>
#include <stdio.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/* TWI  */
#define TWI_CLOCK                 (100000)


/** Get double word */
#define _DW(pByte) ((uint32_t)((((uint8_t*)pByte)[0] << 0) \
                              |(((uint8_t*)pByte)[1] << 8) \
                              |(((uint8_t*)pByte)[2] <<16) \
                              |(((uint8_t*)pByte)[3] <<24)))

/** Screen X -> Display X */
#define SCR_X(X)    \
    ((BOARD_LCD_WIDTH>(X))?(X):(BOARD_LCD_WIDTH-1))
/** Screen Y -> Display Y */
#define SCR_Y(Y)    \
    ((BOARD_LCD_HEIGHT>(Y))?(BOARD_LCD_HEIGHT-1-(Y)):(BOARD_LCD_HEIGHT-1))
/** Display X -> Screen X */
#define IMG_X(X)    \
    ((BOARD_LCD_WIDTH>(X))?(X):(BOARD_LCD_WIDTH-1))
/** Display Y -> Screen Y */
#define IMG_Y(Y)    \
    ((BOARD_LCD_HEIGHT>(Y))?(BOARD_LCD_HEIGHT-1-(Y)):(BOARD_LCD_HEIGHT-1))
/** Absolute */
#define abs(x)  (((x) > 0)?(x):(-(x)))

#define LCD_BASE (DDR_CS_ADDR + 16*1024*1024)
/** LCD base image buffer */
#define ADDR_LCD_BUFFER_BASE    (LCD_BASE)
/** Size of base image buffer */
#define SIZE_LCD_BUFFER_BASE    (BOARD_LCD_WIDTH * BOARD_LCD_HEIGHT * 4)
/** LCD Overlay 1 (OVR1) buffer */
#define ADDR_LCD_BUFFER_OVR1    (ADDR_LCD_BUFFER_BASE + SIZE_LCD_BUFFER_BASE)
/** Size of Overlay 1 buffer */
#define SIZE_LCD_BUFFER_OVR1    (BOARD_LCD_WIDTH * BOARD_LCD_HEIGHT * 4)
/** LCD Overlay 2 (OVR2) buffer */
#define ADDR_LCD_BUFFER_OVR2    (ADDR_LCD_BUFFER_OVR1 + SIZE_LCD_BUFFER_OVR1)
/** Size of Overlay 2 buffer */
#define SIZE_LCD_BUFFER_OVR2    (BOARD_LCD_WIDTH * BOARD_LCD_HEIGHT * 4)
/** LCD High End Overlay (HEO) buffer */
#define ADDR_LCD_BUFFER_HEO     (ADDR_LCD_BUFFER_OVR2 + SIZE_LCD_BUFFER_OVR2)
/** Size of High End Overlay buffer */
#define SIZE_LCD_BUFFER_HEO     (BOARD_LCD_WIDTH * BOARD_LCD_HEIGHT * 4)

/** Width for OVR1 */
#define OVR1_W      (BOARD_LCD_WIDTH*5/6)
/** Height for OVR1 */
#define OVR1_H      (BOARD_LCD_HEIGHT*5/6)
/** Background color for OVR1 */
#define OVR1_BG      0xFFFFFF
/** OVR1 draw step */
#define OVR1_STEP    15

/** Width for HEO */
#define HEO_W       (BOARD_LCD_WIDTH*2/3)
/** Height for HEO */
#define HEO_H       (BOARD_LCD_HEIGHT*2/3)

/** Number of blocks in vertical */
#define N_BLK_VERT    4
/** Number of blocks in horizontal */
#define N_BLK_HOR     6

/*
 * No.   Number               R     G    B
 * 01.   dark skin           115    82   68
 * 02.   light skin          194   150  130
 * 03.   blue sky             98   122  157
 * 04.   foliage              87   108   67
 * 05.   blue flower         133   128  177
 * 06.   bluish green        103   189  170
 * 07.   orange              214   126   44
 * 08.   purplish blue        80    91  166
 * 09.   moderate red        193    90   99
 * 10.   purple               94    60  108
 * 11.   yellow green        157   188   64
 * 12.   orange yellow       224   163   46
 * 13.   blue                 56    61  150
 * 14.   green                70   148   73
 * 15.   red                 175    54   60
 * 16.   yellow              231   199   31
 * 17.   magenta             187    86  149
 * 18.   cyan                  8   133  161
 * 19.   white(.05*)         243   243  243
 * 20.   neutral 8 (.23*)    200   200  200
 * 21.   neutral 6.5 (.44*)  160   160  160
 * 22.   neutral 5 (.70*)    122   122  121
 * 23.   neutral 3.5 (.1.05*) 85    85   85
 * 24.   black (1.50*)        52    52   52
 */

#define COLOR_1           0x735244
#define COLOR_2           0xc29682
#define COLOR_3           0x627a9d
#define COLOR_4           0x576c43
#define COLOR_5           0x8580b1
#define COLOR_6           0x67bdaa
#define COLOR_7           0xd67e2c
#define COLOR_8           0x505ba6
#define COLOR_9           0xc15a63
#define COLOR_10          0x5e3c6c
#define COLOR_11          0x9dbc40
#define COLOR_12          0xe0a32e
#define COLOR_13          0x383d96
#define COLOR_14          0x469449
#define COLOR_15          0xaf363c
#define COLOR_16          0xe7c71f
#define COLOR_17          0xbb5695
#define COLOR_18          0x0885a1
#define COLOR_19          0xf3f3f3
#define COLOR_20          0xc8c8c8
#define COLOR_21          0xa0a0a0
#define COLOR_22          0x7a7a7a
#define COLOR_23          0x555555
#define COLOR_24          0x343434

#define COLOR_BLACK          0x000000
#define COLOR_WHITE          0xFFFFFF

#define COLOR_BLUE           0x0000FF
#define COLOR_GREEN          0x00FF00

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** LCD BASE buffer */

static uint8_t *pBaseBuffer = (uint8_t *)ADDR_LCD_BUFFER_BASE;

/** Overlay 1 buffer */

static uint8_t *pOvr1Buffer = (uint8_t*)ADDR_LCD_BUFFER_OVR1;

/** Overlay 2 buffer */

static uint8_t *pOvr2Buffer = (uint8_t*)ADDR_LCD_BUFFER_OVR2;

/** High End Overlay buffer */

static uint8_t *pHeoBuffer = (uint8_t*)ADDR_LCD_BUFFER_HEO;
/** Pins for LCDC */
static const struct _pin pins_lcd[] = PINS_LCD;

/** Test pattern source */
static uint32_t test_colors[N_BLK_HOR*N_BLK_VERT] = {
    COLOR_1,  COLOR_2,  COLOR_3,  COLOR_4,  COLOR_5,  COLOR_6,
    COLOR_7,  COLOR_8,  COLOR_9,  COLOR_10, COLOR_11, COLOR_12,
    COLOR_13, COLOR_14, COLOR_15, COLOR_16, COLOR_17, COLOR_18,
    COLOR_19, COLOR_20, COLOR_21, COLOR_22, COLOR_23, COLOR_24,
};

/** Backlight value */
static uint8_t bBackLight = 0xF0;
/** OVR1 X */
static uint16_t wOvr1X = 0;
/** OVR1 Y */
static uint16_t wOvr1Y = BOARD_LCD_HEIGHT-1;
/** OVR1 W */
static uint16_t wOvr1W = 0;
/** OVR1 H */
static uint16_t wOvr1H = 0;

/** OVR2 X */
static uint16_t wOvr2X = 0;
/** OVR1 Y */
static uint16_t wOvr2Y = BOARD_LCD_HEIGHT-1;
/** OVR1 W */
static uint16_t wOvr2W = 0;
/** OVR1 H */
static uint16_t wOvr2H = 0;

/** HEO X and Width */
static uint16_t wHeoX  = 0, wHeoW = 0;
/** HEO Y and Height */
static uint16_t wHeoY  = BOARD_LCD_HEIGHT-1, wHeoH = 0;

/** Drawing changing step */
static uint8_t  bDrawChange = 0;
/** Drawing size */
static uint8_t  bDrawSize  =  0;
/** Drawing shape */
static uint8_t  bDrawShape =  0;
/** Last drawing w, h */
static uint16_t wLastW, wLastH;

/** OVR1 XY move direction (XY - 00 01 10 11) */
static uint8_t bOvr1Dir = 0x01;
static uint8_t bOvr2Dir = 0x01;
/** HEO XY move direction */
static uint8_t bHeoDir  = 0x01;
/** HEO draw mode */
static uint8_t bHeoDraw = 0;

/** HEO image width & height */
static uint16_t wHeoImgW, wHeoImgH;
/** HEO image bpp */
static uint8_t  bHeoBpp = 0;

/** Global timestamp in milliseconds since start of application */
volatile uint32_t dwTimeStamp = 0;

/**
 *  \brief Handler for PIT interrupt.
 */
static void pit_handler(void)
{
	uint32_t dwStatus;
	/* Read the PIT status register */
	dwStatus = pit_get_status() & PIT_SR_PITS;
	if (dwStatus) {
		/* 1 = The Periodic Interval timer has reached PIV since the last read of PIT_PIVR.
			Read the PIVR to acknowledge interrupt and get number of ticks
			Returns the number of occurrences of periodic intervals since the last read of PIT_PIVR. */
		dwTimeStamp += (pit_get_pivr() >> 20);
	}
}

/**
 * Fill buffer with test pattern
 */
static void test_pattern_24RGB (uint8_t *lcd_base)
{
	uint16_t v_max  = BOARD_LCD_HEIGHT;
	uint16_t h_max  = BOARD_LCD_WIDTH;
	uint16_t v_step = (v_max + N_BLK_VERT - 1) / N_BLK_VERT;
	uint16_t h_step = (h_max + N_BLK_HOR  - 1) / N_BLK_HOR;
	uint16_t v, h;
	uint8_t *pix = (uint8_t *)lcd_base;

	printf("- Test Pattern: %d x %d [%d x %d]\n\r",
			h_max, v_max, h_step, v_step);

	/* WARNING: Code silently assumes 24bit/pixel */
	for (v=0; v<v_max; ++v) {
		uint8_t iy = v / v_step;
		for (h=0; h<h_max; ++h) {
			uint8_t ix = N_BLK_HOR * iy + (h/h_step);
			*pix++ = (test_colors[ix]&0x0000FF) >>  0;
			*pix++ = (test_colors[ix]&0x00FF00) >>  8;
			*pix++ = (test_colors[ix]&0xFF0000) >>  16;
		}
	}
}

/**
 * Initialize PIT for system tick
 */
static void configure_pit(void)
{
	/* Enable PIT controller */
	pmc_enable_peripheral(ID_PIT);

	/* Initialize the PIT to the desired frequency */
	pit_init(1000);

	/* Configure interrupt on PIT */
	aic_enable(ID_PIT);
	aic_set_source_vector(ID_PIT, pit_handler);

	pit_enable_it();

	/* Enable the pit */
	pit_enable();
}

/**
 * Turn ON LCD, show base .
 */
static void _LcdOn(void)
{
	test_pattern_24RGB(pBaseBuffer);
//	cp15_flush_dcache_for_dma ((uint32_t)ADDR_LCD_BUFFER_BASE, ((uint32_t)ADDR_LCD_BUFFER_BASE) + SIZE_LCD_BUFFER_BASE);

	lcdd_on();

	lcdd_set_backlight(bBackLight);
	/* Display base layer */
	lcdd_show_base( pBaseBuffer, 24, 0 );
	/* Show magnified 'F' for rotate test */
	wHeoImgW = 16 * EXAMPLE_LCD_SCALE; wHeoImgH = 24 * EXAMPLE_LCD_SCALE;
	wHeoW = wHeoImgW * 3; wHeoH = (uint16_t) (wHeoImgH * 5.5);
	bHeoBpp = 24;
	/* Mask out background color */
	lcdd_set_color_keying(LCDD_HEO, 0, COLOR_WHITE, 0xFFFFFF);
	lcdd_create_canvas(LCDD_HEO, pHeoBuffer, bHeoBpp, 0, 0, wHeoImgW, wHeoImgH);
	
	lcdd_fill(COLOR_WHITE);
	lcdd_draw_filled_rectangle(  0,  0, wHeoImgW,  2 * EXAMPLE_LCD_SCALE, COLOR_BLACK);
	
	lcdd_draw_filled_rectangle(  0,  2 * EXAMPLE_LCD_SCALE,  
									EXAMPLE_LCD_SCALE, wHeoImgH, COLOR_BLACK);
	lcdd_draw_filled_rectangle(  2 * EXAMPLE_LCD_SCALE, 10 * EXAMPLE_LCD_SCALE, 
								13 * EXAMPLE_LCD_SCALE, 13 * EXAMPLE_LCD_SCALE, COLOR_BLACK);
//	cp15_flush_dcache_for_dma ((uint32_t)ADDR_LCD_BUFFER_HEO, ((uint32_t)ADDR_LCD_BUFFER_HEO) + SIZE_LCD_BUFFER_HEO);
	lcdd_show_bmp_rotated(LCDD_HEO, pHeoBuffer, bHeoBpp,
							SCR_X(wHeoX), SCR_Y(wHeoY),
							wHeoW, wHeoH, wHeoImgW, wHeoImgH,
							0);
	/* It's over overlay 1 */
	lcdd_set_prioty(LCDD_HEO, 1);

	/* Test LCD draw */
	wOvr2X = IMG_X(BOARD_LCD_WIDTH/4); wOvr2Y = IMG_Y(BOARD_LCD_WIDTH/4);
	wOvr2W = BOARD_LCD_WIDTH/5;      wOvr2H = BOARD_LCD_HEIGHT/4;
	lcdd_create_canvas(LCDD_OVR2, pOvr2Buffer, 24,
                      SCR_X(wOvr2X), SCR_Y(wOvr2Y), wOvr2W, wOvr2H);
	lcdd_fill_white();
//	cp15_flush_dcache_for_dma ((uint32_t)ADDR_LCD_BUFFER_OVR2, ((uint32_t)ADDR_LCD_BUFFER_OVR2) + SIZE_LCD_BUFFER_OVR2);
    
    /* Test LCD draw */
	wOvr1X = IMG_X(0); wOvr1Y = IMG_Y(0);
	wOvr1W = BOARD_LCD_WIDTH/2;      wOvr1H = BOARD_LCD_HEIGHT/2;
	lcdd_create_canvas(LCDD_OVR1, pOvr1Buffer, 24,
						SCR_X(wOvr1X), SCR_Y(wOvr1Y), wOvr1W, wOvr1H);
	lcdd_fill( OVR1_BG );
//	cp15_flush_dcache_for_dma ((uint32_t)ADDR_LCD_BUFFER_OVR1, ((uint32_t)ADDR_LCD_BUFFER_OVR1) + SIZE_LCD_BUFFER_OVR1);

	printf("- LCD ON\n\r");
}

/**
 * Calculate X,Y and DIR for move.
 * \param pwX  Pointer to X.
 * \param pwY  Pointer to Y.
 * \param pDir Pointer to DIR.
 */
static void _move_calc(uint16_t *pwX, uint16_t *pwY, uint8_t *pDir,
						uint8_t  bXMov, uint8_t  bYMov,
						uint16_t wXMin, uint16_t wXMax,
						uint16_t wYMin, uint16_t wYMax)
{
	uint8_t bXDir = (0xF0 & *pDir);
	uint8_t bYDir = (0x0F & *pDir);
	if (bXDir == 0x10){
		if ((*pwX) <= wXMin + bXMov){
			(*pwX)   = wXMin;
			(*pDir) &= ~0x10;
		} else {
			(*pwX) -= bXMov;
		}
	} else if (bXDir == 0) {
		if ((*pwX) >= wXMax - bXMov) {
			(*pwX)   = wXMax;
			(*pDir) |= 0x10;
		} else{
			(*pwX) += bXMov;
		}
	}
	if (bYDir == 0x01){
		if ((*pwY) <= wYMin + bYMov){
			(*pwY)   =  wYMin;
			(*pDir) &= ~0x01;
		} else {
			(*pwY) -= bYMov;
		}
	} else if (bYDir == 0){
		if ((*pwY) >= wYMax - bYMov){
			(*pwY)   = wYMax;
			(*pDir) |= 0x01;
		} else {
			(*pwY) += bYMov;
		}
	}
}

/**
 * Rotates on HEO
 */
static void _rotates(void)
{
	int32_t w = wHeoW, h = wHeoH;
	uint16_t wRotate = 0;

	if (!lcdd_is_layer_on(LCDD_HEO)) return;

	switch (bHeoDraw){
	/* Origional size */
	case 0: bHeoDraw = 1; w = wHeoImgW; h = wHeoImgH; break;
	
	/* Mirrow (scan direction) */
	case 1: bHeoDraw = 2; break;
	case 2: bHeoDraw = 3; h = -h; break;
	case 3: bHeoDraw = 4; h = -h; w = -w; break;
	case 4: bHeoDraw = 5; w = -w; break;

	/* Goes Back */
	case 5: bHeoDraw = 6; w = wHeoImgW; h = wHeoImgH; break;

	/* Rotate (0?) */
	case 6: bHeoDraw = 7; break;
	/* Rotate (90?) */
	case 7: bHeoDraw = 8;
		w = wHeoH; h = wHeoW;
		wHeoH = h; wHeoW = w;
		wRotate = 90;
		break;
	/* X mirror & Rotate (90?) */
	case 8: bHeoDraw = 9;
		w = (0-wHeoW); h = wHeoH;
		wRotate = 90;
		break;
	/* Rotate (180?) */
	case 9: bHeoDraw = 10;
		w = wHeoH; h = wHeoW;
		wHeoH = h; wHeoW = w;
		wRotate = 180;
		break;
	/* Rotate (270?) */
	case 10: bHeoDraw = 11;
		w = wHeoH; h = wHeoW;
		wHeoH = h; wHeoW = w;
		wRotate = 270;
		break;
	/* Y mirror & Rotate (270?) */
	case 11: bHeoDraw = 12;
		w = wHeoW; h = 0-wHeoH;
		wRotate = 270;
		break;
	/* Rotate (0?) */
	case 12: bHeoDraw = 0;
		w = wHeoH; h = wHeoW;
		wHeoH = h; wHeoW = w;
		break;
	}
	if (SCR_X(wHeoX) + abs(w) > BOARD_LCD_WIDTH){
		wHeoX = IMG_X(BOARD_LCD_WIDTH - abs(w));
		//printf("- x %d\n\r", wHeoX);
	}
	if (SCR_Y(wHeoY) + abs(h) > BOARD_LCD_HEIGHT){
		wHeoY = IMG_Y(BOARD_LCD_HEIGHT - abs(h));
		//printf("- y %d\n\r", wHeoY);
	}

	printf("Show: %u,%u %d, %d %u\n\r",
			(unsigned int)SCR_X(wHeoX), (unsigned int)SCR_Y(wHeoY), 
			(int)w, (int)h, (unsigned int)wRotate);
	lcdd_show_bmp_rotated(LCDD_HEO,
						0, bHeoBpp,
						SCR_X(wHeoX), SCR_Y(wHeoY),
						w, h, wHeoImgW, wHeoImgH, wRotate);

//	cp15_flush_dcache_for_dma ((uint32_t)ADDR_LCD_BUFFER_HEO, 
								//((uint32_t)ADDR_LCD_BUFFER_HEO) + SIZE_LCD_BUFFER_HEO);
	if (bHeoDraw == 0) printf("\n\r-----------------\n\r");
}

/**
 * Draw on canvas
 */
static void _draws(void)
{
	uint32_t x, y, w, h;

	x = wOvr1W / 2; y = wOvr1H / 2;
	if (!lcdd_is_layer_on(LCDD_OVR1)) return;
	/* Drawing width, height */
	if (bDrawSize == 0) w = h = 2;
	else {
		w = wOvr1W / 10 * bDrawSize;
		h = wOvr1H / 10 * bDrawSize;
	}

	/* Draw circles */
	if (bDrawShape){
		/* Remove last shape */
		lcdd_draw_circle(x, y, wLastW > wLastH ? wLastH/2 : wLastW/2, OVR1_BG);
		/* Draw new */
		lcdd_draw_circle(x, y, w > h ? h/2 : w/2, COLOR_BLUE);
	} else {
	/* Draw rectangles */
		/* Remove last shape */
		lcdd_draw_rectangle(x - wLastW/2, y - wLastH/2, wLastW, wLastH, OVR1_BG);
        /* Draw new */
		lcdd_draw_rectangle(x - w/2, y - h/2, w, h, COLOR_GREEN);
	}
//	cp15_flush_dcache_for_dma ((uint32_t)ADDR_LCD_BUFFER_OVR1, ((uint32_t)ADDR_LCD_BUFFER_OVR1) + SIZE_LCD_BUFFER_OVR1);

	wLastW = w; wLastH = h;

    /* Size -- */
	if (bDrawChange){
		if (bDrawSize == 0){
			bDrawShape = !bDrawShape;
			bDrawChange = 0;
		} else {
			bDrawSize --;
		}
	}
	/* Size ++ */
	else {
		if (bDrawSize == 10){
			bDrawChange = 1;
		} else {
			bDrawSize ++;
		}
	}
}

/**
 * Move layers.
 */
static void _moves(void)
{
	if (lcdd_is_layer_on(LCDD_OVR1)){
		_move_calc(&wOvr1X, &wOvr1Y, &bOvr1Dir,
				1, 1,
				0, BOARD_LCD_WIDTH - wOvr1W - 1,
				wOvr1H, BOARD_LCD_HEIGHT - 1);
		lcdd_set_position(LCDD_OVR1, SCR_X(wOvr1X), SCR_Y(wOvr1Y));
	}

	if (lcdd_is_layer_on(LCDD_OVR2)){
		_move_calc(&wOvr2X, &wOvr2Y, &bOvr2Dir,
				1, 1,
				0, BOARD_LCD_WIDTH - wOvr2W - 1,
				wOvr2H, BOARD_LCD_HEIGHT - 1);
		lcdd_set_position(LCDD_OVR2, SCR_X(wOvr2X), SCR_Y(wOvr2Y));
	}
    
	if (lcdd_is_layer_on(LCDD_HEO)){
		_move_calc(&wHeoX, &wHeoY, &bHeoDir,
				2, 3,
				0, BOARD_LCD_WIDTH - wHeoW - 1,
				wHeoH, BOARD_LCD_HEIGHT - 1);
		lcdd_set_position(LCDD_HEO, SCR_X(wHeoX), SCR_Y(wHeoY));
	}
}

/**
 * Handle DBGU events.
 */
static void _DbgEvents(void)
{
	uint8_t key;
	if (console_is_rx_ready()){
		key = console_get_char();
		switch(key){
		case '`': /* HEO & OVR1 layout */
			lcdd_set_prioty(LCDD_HEO, !lcdd_get_prioty(LCDD_HEO));
		break;
		}
	}
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief LCD Exmple Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
extern int main( void )
{
	uint32_t t1, t2; 
	uint32_t heoDly = 0;
	uint32_t ovr1Dly = 0;
	/* Disable watchdog */
	wdt_disable() ;
    
    /* Initialize console */
	console_configure(CONSOLE_BAUDRATE);

	/* Output example information */
	printf( "-- LCD Example %s --\n\r", SOFTPACK_VERSION ) ;
	printf( "-- %s\n\r", BOARD_NAME ) ;
	printf( "-- Compiled: %s %s --\n\r", __DATE__, __TIME__ ) ;

	board_cfg_ddram();
	
	cp15_disable_mmu();
	cp15_disable_icache();
	cp15_disable_dcache();
    
	configure_pit();
	lcdd_initialize(pins_lcd, ARRAY_SIZE(pins_lcd));
    
	_LcdOn();

	t1 = dwTimeStamp;
	printf("ADDR_LCD_BUFFER_HEO is %x, %x\n\r",
			ADDR_LCD_BUFFER_HEO, ADDR_LCD_BUFFER_HEO+SIZE_LCD_BUFFER_HEO);
	while(1){
		_DbgEvents();
		t2 = dwTimeStamp;
		/* Move layers */
		if ((t2 - t1) >= 50){
			t1 = t2;
			_moves();
			/* Change OVR1 each 0.5s */
			if (ovr1Dly >= 500 / 50){
				ovr1Dly = 0;
				_draws();
			} else ovr1Dly ++;

			/* Change HEO display mode each 2s */
			if (heoDly >= 2000 / 50) {
				heoDly = 0;
				_rotates();
			} else heoDly ++;
		}
	}
}
/** \endcond */
