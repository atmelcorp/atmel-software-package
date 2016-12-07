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
 *  \page lcd LCD Example
 *
 *  \section Purpose
 *
 *  This example demonstrates how to configure the LCD Controller (LCDC)
 *  to use the LCD on the board.
 *
 *  \section Requirements
 *
 *  This package can be used with SAMA5D4x Xplained board.
 *
 *  \section Description
 *
 *  The example configures the LCDC for LCD to display and then draw test
 *  patterns on LCD.
 *
 *  4 layers are displayed:
 *  - Base: The layer at bottom, show test pattern with color blocks.
 *  - OVR1: The layer over base, used as canvas to draw shapes.
 *  - HEO:  The next layer, showed scaled ('F') which flips or rotates once
 *          for a while.
 *
 *  \section Note
 *
 *  \section Usage
 *
 *  -# Build the program and download it inside the evaluation board. Please
 *     refer to the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *     SAM-BA User Guide</a>, the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *     GNU-Based Software Development</a>
 *     application note or to the
 *     <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *     IAR EWARM User Guide</a>,
 *     depending on your chosen solution.
 *  -# On the computer, open and configure a terminal application
 *     (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *    - 115200 bauds
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# Start the application.
 *  -# In the terminal window, the
 *     following text should appear (values depend on the board and chip used):
 *     \code
 *      -- LCD Example xxx --
 *      -- SAMxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 *  -# Test pattern images should be displayed on the LCD.
 *
 *  \section References
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

#include "peripherals/lcdc.h"
#include "peripherals/pmc.h"
#include "gpio/pio.h"

#include "mm/cache.h"
#include "serial/console.h"
#include "led/led.h"

#include "lcd_draw.h"
#include "lcd_font.h"
#include "lcd_color.h"
#include "font.h"
#include "timer.h"
#include "trace.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#define EXAMPLE_LCD_SCALE 1

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

/** Size of base image buffer */
#define SIZE_LCD_BUFFER_BASE (BOARD_LCD_WIDTH * BOARD_LCD_HEIGHT * 4)
/** Size of Overlay 1 buffer */
#define SIZE_LCD_BUFFER_OVR1 (BOARD_LCD_WIDTH * BOARD_LCD_HEIGHT * 4)
/** Size of Overlay 2 buffer */
#define SIZE_LCD_BUFFER_OVR2 (BOARD_LCD_WIDTH * BOARD_LCD_HEIGHT * 4)
/** Size of High End Overlay buffer */
#define SIZE_LCD_BUFFER_HEO  (BOARD_LCD_WIDTH * BOARD_LCD_HEIGHT * 4)

/** Width for OVR1 */
#define OVR1_W      (BOARD_LCD_WIDTH * 5 / 6)
/** Height for OVR1 */
#define OVR1_H      (BOARD_LCD_HEIGHT * 5/ 6)
/** Background color for OVR1 */
#define OVR1_BG      0xFFFFFF
/** OVR1 draw step */
#define OVR1_STEP    15

/** Width for HEO */
#define HEO_W       (BOARD_LCD_WIDTH * 2 / 3)
/** Height for HEO */
#define HEO_H       (BOARD_LCD_HEIGHT * 2 /3)

/** Number of blocks in vertical */
#define N_BLK_VERT    4
/** Number of blocks in horizontal */
#define N_BLK_HOR     6


/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** LCD BASE buffer */
CACHE_ALIGNED_DDR static uint8_t _base_buffer[SIZE_LCD_BUFFER_BASE];

/** Overlay 1 buffer */
CACHE_ALIGNED_DDR static uint8_t _ovr1_buffer[SIZE_LCD_BUFFER_OVR1];

#ifdef CONFIG_HAVE_LCDC_OVR2
/** Overlay 2 buffer */
CACHE_ALIGNED_DDR static uint8_t _ovr2_buffer[SIZE_LCD_BUFFER_OVR2];
#endif

/** High End Overlay buffer */
CACHE_ALIGNED_DDR static uint8_t _heo_buffer[SIZE_LCD_BUFFER_HEO];

/** Test pattern source */
static uint32_t test_colors[N_BLK_HOR*N_BLK_VERT] = {
    COLOR_BLACK,  COLOR_Aqua,  COLOR_BLUE,  COLOR_Fuchsia,  COLOR_GRAY,  COLOR_GREEN,
    COLOR_Lime,  COLOR_Maroon,  COLOR_NAVY,  COLOR_OLIVE, COLOR_ORANGE, COLOR_Purple,
    COLOR_RED, COLOR_SILVER, COLOR_Teal, COLOR_YELLOW, COLOR_YELLOWGREEN, COLOR_MistyRose,
    COLOR_SKYBLUE, COLOR_VIOLET, COLOR_DARKGRAY, COLOR_DARKGREEN, COLOR_BEIGE, COLOR_BROWN,
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
/** OVR1 XY move direction (XY - 00 01 10 11) */
static uint8_t bOvr1Dir = 0x01;

#ifdef CONFIG_HAVE_LCDC_OVR2

/** OVR2 X */
static uint16_t wOvr2X = 0;
/** OVR2 Y */
static uint16_t wOvr2Y = BOARD_LCD_HEIGHT-1;
/** OVR2 W */
static uint16_t wOvr2W = 0;
/** OVR2 H */
static uint16_t wOvr2H = 0;
/** OVR2 XY move direction (XY - 00 01 10 11) */
static uint8_t bOvr2Dir = 0x01;

#endif /* CONFIG_HAVE_LCDC_OVR2 */

/** HEO X and Width */
static uint16_t wHeoX = 0, wHeoW = 0;
/** HEO Y and Height */
static uint16_t wHeoY = BOARD_LCD_HEIGHT-1, wHeoH = 0;
/** HEO XY move direction */
static uint8_t bHeoDir = 0x01;
/** HEO draw mode */
static uint8_t bHeoDraw = 0;
/** HEO image width & height */
static uint16_t wHeoImgW, wHeoImgH;
/** HEO image bpp */
static uint8_t bHeoBpp = 0;

/** Drawing changing step */
static uint8_t  bDrawChange = 0;
/** Drawing size */
static uint8_t  bDrawSize  =  0;
/** Drawing shape */
static uint8_t  bDrawShape =  0;
/** Last drawing w, h */
static uint16_t wLastW, wLastH;


/** Global timestamp in milliseconds since start of application */
volatile uint32_t dwTimeStamp = 0;

#define NB_TAB_COLOR N_BLK_HOR*N_BLK_VERT
uint8_t ncolor = 0;

/*----------------------------------------------------------------------------
 *        Functions
 *----------------------------------------------------------------------------*/

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
 * Turn ON LCD, show base .
 */
static void _LcdOn(void)
{
	test_pattern_24RGB(_base_buffer);
	cache_clean_region(_base_buffer, sizeof(_base_buffer));

	lcdc_on();

	lcdc_set_backlight(bBackLight);
	/* Display base layer */
	lcdc_show_base(_base_buffer, 24, 0);

	/* Show magnified 'F' for rotate test */
	wHeoImgW = 20 * EXAMPLE_LCD_SCALE;
	wHeoImgH = 24 * EXAMPLE_LCD_SCALE;
	wHeoW = wHeoImgW * 3;
	wHeoH = (uint16_t) (wHeoImgH * 5.5);
	bHeoBpp = 24;
	/* Mask out background color */
	lcdc_set_color_keying(LCDC_HEO, 0, COLOR_WHITE, 0xFFFFFF);
	lcdc_create_canvas(LCDC_HEO, _heo_buffer, bHeoBpp, 0, 0,
			   wHeoImgW, wHeoImgH);

	lcd_fill(COLOR_WHITE);
	lcd_draw_filled_rectangle(0, 0, wHeoImgW, 2 * EXAMPLE_LCD_SCALE,
				   COLOR_BLACK);
	lcd_draw_filled_rectangle(0, 2 * EXAMPLE_LCD_SCALE, EXAMPLE_LCD_SCALE,
				   wHeoImgH, COLOR_BLACK);
	lcd_draw_filled_rectangle(2*EXAMPLE_LCD_SCALE,
				   10 * EXAMPLE_LCD_SCALE,
				   13 * EXAMPLE_LCD_SCALE,
				   13 * EXAMPLE_LCD_SCALE, COLOR_BLACK);

	cache_clean_region(_heo_buffer, sizeof(_heo_buffer));
	lcdc_put_image_rotated(LCDC_HEO, _heo_buffer, bHeoBpp, SCR_X(wHeoX),
			      SCR_Y(wHeoY), wHeoW, wHeoH, wHeoImgW,
			      wHeoImgH, 0);
	/* It's over overlay 1 */
	lcdc_set_priority(LCDC_HEO, 1);

#ifdef CONFIG_HAVE_LCDC_OVR2
	/* Test LCD draw */
	wOvr2X = IMG_X(BOARD_LCD_WIDTH/4);
	wOvr2Y = IMG_Y(BOARD_LCD_WIDTH/4);
	wOvr2W = BOARD_LCD_WIDTH/5;
	wOvr2H = BOARD_LCD_HEIGHT/4;
	lcdc_create_canvas(LCDC_OVR2, _ovr2_buffer, 24, SCR_X(wOvr2X),
			   SCR_Y(wOvr2Y), wOvr2W, wOvr2H);
	lcd_fill_white();

	/* Display message font 8x8 */
	lcd_select_font(FONT8x8);
	lcd_draw_string(8, 56, "ATMEL RFO", COLOR_BLACK);
	cache_clean_region(_ovr2_buffer, sizeof(_ovr2_buffer));
#endif /* CONFIG_HAVE_LCDC_OVR2 */

	/* Test LCD draw */
	wOvr1X = IMG_X(0);
	wOvr1Y = IMG_Y(0);
	wOvr1W = BOARD_LCD_WIDTH/2;
	wOvr1H = BOARD_LCD_HEIGHT/2;
	lcdc_create_canvas(LCDC_OVR1, _ovr1_buffer, 24, SCR_X(wOvr1X),
			   SCR_Y(wOvr1Y), wOvr1W, wOvr1H);
	lcd_fill(OVR1_BG);
	cache_clean_region(_ovr1_buffer, sizeof(_ovr1_buffer));

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
	uint8_t x_dir = (0xF0 & *pDir);
	uint8_t y_dir = (0x0F & *pDir);
	if (x_dir == 0x10) {
		if ((*pwX) <= wXMin + bXMov){
			(*pwX)   = wXMin;
			(*pDir) &= ~0x10;
		} else {
			(*pwX) -= bXMov;
		}
	} else if (x_dir == 0) {
		if ((*pwX) >= wXMax - bXMov) {
			(*pwX)   = wXMax;
			(*pDir) |= 0x10;
		} else {
			(*pwX) += bXMov;
		}
	}
	if (y_dir == 0x01) {
		if ((*pwY) <= wYMin + bYMov){
			(*pwY)   =  wYMin;
			(*pDir) &= ~0x01;
		} else {
			(*pwY) -= bYMov;
		}
	} else if (y_dir == 0) {
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

	if (!lcdc_is_layer_on(LCDC_HEO))
		return;

	switch (bHeoDraw){
		/* Origional size */
		case 0:
			bHeoDraw = 1;
			w = wHeoImgW;
			h = wHeoImgH;
			break;
		/* Mirrow (scan direction) */
		case 1:
			bHeoDraw = 2;
			break;
		case 2:
			bHeoDraw = 3;
			h = -h;
			break;
		case 3:
			bHeoDraw = 4;
			h = -h; w = -w;
			break;
		case 4:
			bHeoDraw = 5;
			w = -w;
			break;
		/* Goes Back */
		case 5:
			bHeoDraw = 6;
			w = wHeoImgW;
			h = wHeoImgH;
			break;
		/* Rotate (0?) */
		case 6:
			bHeoDraw = 7;
			break;
		/* Rotate (90?) */
		case 7:
			bHeoDraw = 8;
			w = wHeoH;
			h = wHeoW;
			wHeoH = h;
			wHeoW = w;
			wRotate = 90;
			break;
		/* X mirror & Rotate (90?) */
		case 8:
			bHeoDraw = 9;
			w = (0-wHeoW);
			h = wHeoH;
			wRotate = 90;
			break;
		/* Rotate (180?) */
		case 9:
			bHeoDraw = 10;
			w = wHeoH;
			h = wHeoW;
			wHeoH = h;
			wHeoW = w;
			wRotate = 180;
			break;
		/* Rotate (270?) */
		case 10:
			bHeoDraw = 11;
			w = wHeoH;
			h = wHeoW;
			wHeoH = h;
			wHeoW = w;
			wRotate = 270;
			break;
		/* Y mirror & Rotate (270?) */
		case 11:
			bHeoDraw = 12;
			w = wHeoW;
			h = 0-wHeoH;
			wRotate = 270;
			break;
		/* Rotate (0?) */
		case 12:
			bHeoDraw = 0;
			w = wHeoH;
			h = wHeoW;
			wHeoH = h;
			wHeoW = w;
			break;
	}
	if (SCR_X(wHeoX) + abs(w) > BOARD_LCD_WIDTH){
		wHeoX = IMG_X(BOARD_LCD_WIDTH - abs(w));
	}
	if (SCR_Y(wHeoY) + abs(h) > BOARD_LCD_HEIGHT){
		wHeoY = IMG_Y(BOARD_LCD_HEIGHT - abs(h));
	}

	printf("Show: %u,%u %d, %d %u\n\r", (unsigned)SCR_X(wHeoX),
	       (unsigned)SCR_Y(wHeoY), (int)w, (int)h, (unsigned)wRotate);
	lcdc_put_image_rotated(LCDC_HEO, 0, bHeoBpp, SCR_X(wHeoX), SCR_Y(wHeoY),
			      w, h, wHeoImgW, wHeoImgH, wRotate);

	if (bHeoDraw == 0) {
		printf("\n\r");
		printf("---------------------------------------\n\r");
		printf(" Use 'SPACE' to change the priority HE0\n\r");
	}
}

/**
 * Draw on canvas
 */
static void _draws(void)
{
	uint32_t x, y, w, h;

	x = wOvr1W / 2;
	y = wOvr1H / 2;
	if (!lcdc_is_layer_on(LCDC_OVR1))
		return;

	/* Drawing width, height */
	if (bDrawSize == 0) {
		w = h = 2;
	} else {
		w = wOvr1W / 10 * bDrawSize;
		h = wOvr1H / 10 * bDrawSize;
	}

	/* Draw circles */
	if (bDrawShape){
		/* Remove last shape */
		lcd_draw_circle(x, y, wLastW > wLastH ? wLastH/2 : wLastW/2, OVR1_BG);
		/* Draw new */
		lcd_draw_circle(x, y, w > h ? h/2 : w/2, test_colors[ncolor]);
		ncolor = (ncolor+1)%NB_TAB_COLOR;
	} else {
		/* Remove last shape */
		lcd_draw_rounded_rect(x - wLastW/2, y - wLastH/2, wLastW, wLastH, wLastH/3, OVR1_BG);
		/* Draw new */
		lcd_draw_rounded_rect(x - w/2, y - h/2, w, h, h/3, test_colors[ncolor]);
		ncolor = (ncolor+1)%NB_TAB_COLOR;
	}
	wLastW = w;
	wLastH = h;

	/* Size -- */
	if (bDrawChange) {
		if (bDrawSize == 0) {
			bDrawShape = !bDrawShape;
			bDrawChange = 0;
		} else {
			bDrawSize--;
		}
	}
	/* Size ++ */
	else {
		if (bDrawSize == 8) {
			bDrawChange = 1;
		} else {
			bDrawSize++;
		}
	}

	/* Display message font 10x8 */
	lcd_select_font(FONT10x8);
	lcd_draw_string(1, 1,
			" This example shows the \n"
			"graphic functionnalities\n"
			"       on a SAMA5", COLOR_BLACK);

	cache_clean_region(_ovr1_buffer, sizeof(_ovr1_buffer));
}

/**
 * Move layers.
 */
static void _moves(void)
{
	if (lcdc_is_layer_on(LCDC_OVR1)){
		_move_calc(&wOvr1X, &wOvr1Y, &bOvr1Dir,
				1, 1,
				0, BOARD_LCD_WIDTH - wOvr1W - 1,
				wOvr1H, BOARD_LCD_HEIGHT - 1);
		lcdc_set_position(LCDC_OVR1, SCR_X(wOvr1X), SCR_Y(wOvr1Y));
	}

#ifdef CONFIG_HAVE_LCDC_OVR2
	if (lcdc_is_layer_on(LCDC_OVR2)){
		_move_calc(&wOvr2X, &wOvr2Y, &bOvr2Dir,
				1, 1,
				0, BOARD_LCD_WIDTH - wOvr2W - 1,
				wOvr2H, BOARD_LCD_HEIGHT - 1);
		lcdc_set_position(LCDC_OVR2, SCR_X(wOvr2X), SCR_Y(wOvr2Y));
	}
#endif /* CONFIG_HAVE_LCDC_OVR2 */

	if (lcdc_is_layer_on(LCDC_HEO)){
		_move_calc(&wHeoX, &wHeoY, &bHeoDir,
				2, 3,
				0, BOARD_LCD_WIDTH - wHeoW - 1,
				wHeoH, BOARD_LCD_HEIGHT - 1);
		lcdc_set_position(LCDC_HEO, SCR_X(wHeoX), SCR_Y(wHeoY));
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
			case ' ': /* HEO & OVR1 layout */
				lcdc_set_priority(LCDC_HEO,
						!lcdc_get_priority(LCDC_HEO));
				printf("Change priority HE0 \n\r");
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
extern int main(void)
{
	uint32_t t1, t2;
	uint32_t heoDly = 0;
	uint32_t ovr1Dly = 0;

	/* Output example information */
	console_example_info("LCD Example");

	/* Configure LCD */
	_LcdOn();

	t1 = timer_get_tick();
	printf("ADDR_LCD_BUFFER_HEO is 0x%x, size %u\n\r",
	       (unsigned)_heo_buffer,
	       (unsigned)sizeof(_heo_buffer));
	while(1) {
		_DbgEvents();
		t2 = timer_get_tick();
		/* Move layers */
		if ((t2 - t1) >= 10) {
			t1 = t2;
			_moves();

			/* Change OVR1  */
			if (ovr1Dly >= 500 / 50){
				ovr1Dly = 0;
				_draws();
				led_toggle(LED_BLUE);
			} else {
				ovr1Dly++;
			}

			/* Change HEO display mode */
			if (heoDly >= 4000 / 50) {
				heoDly = 0;
				_rotates();
			} else {
				heoDly++;
			}
		}
	}
}
