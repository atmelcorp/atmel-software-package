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

#include "display/lcdc.h"
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

#ifdef CONFIG_HAVE_LCDC_OVR1
/** Overlay 1 buffer */
CACHE_ALIGNED_DDR static uint8_t _ovr1_buffer[SIZE_LCD_BUFFER_OVR1];
#endif

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

#ifdef CONFIG_HAVE_LCDC_OVR1

/** OVR1 X */
static uint16_t ovr1_x = 0;
/** OVR1 Y */
static uint16_t ovr1_y = BOARD_LCD_HEIGHT - 1;
/** OVR1 W */
static uint16_t orv1_w = 0;
/** OVR1 H */
static uint16_t ovr1_h = 0;
/** OVR1 XY move direction (XY - 00 01 10 11) */
static uint8_t ovr1_dir = 0x01;

/** Drawing changing step */
static uint8_t  draw_changed = 0;
/** Drawing size */
static uint8_t  draw_size  =  0;
/** Drawing shape */
static uint8_t  draw_shape =  0;
/** Last drawing w, h */
static uint16_t last_w, last_h;

#endif /* CONFIG_HAVE_LCDC_OVR1 */

#ifdef CONFIG_HAVE_LCDC_OVR2

/** OVR2 X */
static uint16_t ovr2_x = 0;
/** OVR2 Y */
static uint16_t ovr2_y = BOARD_LCD_HEIGHT-1;
/** OVR2 W */
static uint16_t ovr2_w = 0;
/** OVR2 H */
static uint16_t ovr2_h = 0;
/** OVR2 XY move direction (XY - 00 01 10 11) */
static uint8_t ovr2_dir = 0x01;

#endif /* CONFIG_HAVE_LCDC_OVR2 */

/** HEO X and Width */
static uint16_t heo_x = 0, heo_w = 0;
/** HEO Y and Height */
static uint16_t heo_y = BOARD_LCD_HEIGHT-1, heo_h = 0;
/** HEO XY move direction */
static uint8_t heo_dir = 0x01;
/** HEO draw mode */
static uint8_t heo_draw = 0;
/** HEO image width & height */
static uint16_t heo_img_w, heo_img_h;
/** HEO image bpp */
static uint8_t heo_bpp = 0;

/** Global timestamp in milliseconds since start of application */
volatile uint32_t time_stamp = 0;

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

	printf("- Test Pattern: %d x %d [%d x %d]\r\n",
			h_max, v_max, h_step, v_step);

	/* WARNING: Code silently assumes 24bit/pixel */
	for (v = 0; v < v_max; ++v) {
		uint8_t iy = v / v_step;
		for (h = 0; h < h_max; ++h) {
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
	heo_img_w = 20 * EXAMPLE_LCD_SCALE;
	heo_img_h = 24 * EXAMPLE_LCD_SCALE;
	heo_w = heo_img_w * 3;
	heo_h = (uint16_t) (heo_img_h * 5.5);
	heo_bpp = 24;
	/* Mask out background color */
	lcdc_set_color_keying(LCDC_HEO, 0, COLOR_WHITE, 0xFFFFFF);
	lcdc_create_canvas(LCDC_HEO, _heo_buffer, heo_bpp, 0, 0,
			   heo_img_w, heo_img_h);

	lcd_fill(COLOR_WHITE);
	lcd_draw_filled_rectangle(0, 0, heo_img_w, 2 * EXAMPLE_LCD_SCALE,
				   COLOR_BLACK);
	lcd_draw_filled_rectangle(0, 2 * EXAMPLE_LCD_SCALE, EXAMPLE_LCD_SCALE,
				   heo_img_h, COLOR_BLACK);
	lcd_draw_filled_rectangle(2*EXAMPLE_LCD_SCALE,
				   10 * EXAMPLE_LCD_SCALE,
				   13 * EXAMPLE_LCD_SCALE,
				   13 * EXAMPLE_LCD_SCALE, COLOR_BLACK);

	cache_clean_region(_heo_buffer, sizeof(_heo_buffer));
	lcdc_put_image_rotated(LCDC_HEO, _heo_buffer, heo_bpp, SCR_X(heo_x),
			      SCR_Y(heo_y), heo_w, heo_h, heo_img_w,
			      heo_img_h, 0);
	/* It's over overlay 1 */
	lcdc_set_priority(LCDC_HEO, 1);

#ifdef CONFIG_HAVE_LCDC_OVR2
	/* Test LCD draw */
	ovr2_x = IMG_X(BOARD_LCD_WIDTH / 4);
	ovr2_y = IMG_Y(BOARD_LCD_WIDTH / 4);
	ovr2_w = BOARD_LCD_WIDTH / 5;
	ovr2_h = BOARD_LCD_HEIGHT / 4;
	lcdc_create_canvas(LCDC_OVR2, _ovr2_buffer, 24, SCR_X(ovr2_x),
			   SCR_Y(ovr2_y), ovr2_w, ovr2_h);
	lcd_fill_white();

	/* Display message font 8x8 */
	lcd_select_font(FONT8x8);
	lcd_draw_string(8, 56, "ATMEL RFO", COLOR_BLACK);
	cache_clean_region(_ovr2_buffer, sizeof(_ovr2_buffer));
#endif /* CONFIG_HAVE_LCDC_OVR2 */

#ifdef CONFIG_HAVE_LCDC_OVR1
	/* Test LCD draw */
	ovr1_x = IMG_X(0);
	ovr1_y = IMG_Y(0);
	orv1_w = BOARD_LCD_WIDTH / 2;
	ovr1_h = BOARD_LCD_HEIGHT / 2;
	lcdc_create_canvas(LCDC_OVR1, _ovr1_buffer, 24, SCR_X(ovr1_x),
			   SCR_Y(ovr1_y), orv1_w, ovr1_h);
	lcd_fill(OVR1_BG);
	cache_clean_region(_ovr1_buffer, sizeof(_ovr1_buffer));
#endif /* CONFIG_HAVE_LCDC_OVR1 */

	printf("- LCD ON\r\n");
}

/**
 * Calculate X,Y and DIR for move.
 * \param wx  Pointer to X.
 * \param wy  Pointer to Y.
 * \param dir Pointer to DIR.
 */
static void _move_calc(uint16_t *wx, uint16_t *wy, uint8_t *dir,
	uint8_t  x_mov, uint8_t  y_mov,
	uint16_t x_min, uint16_t x_max,
	uint16_t y_min, uint16_t y_max)
{
	uint8_t x_dir = (0xF0 & *dir);
	uint8_t y_dir = (0x0F & *dir);
	if (x_dir == 0x10) {
		if ((*wx) <= x_min + x_mov){
			(*wx)   = x_min;
			(*dir) &= ~0x10;
		} else {
			(*wx) -= x_mov;
		}
	} else if (x_dir == 0) {
		if ((*wx) >= x_max - x_mov) {
			(*wx)   = x_max;
			(*dir) |= 0x10;
		} else {
			(*wx) += x_mov;
		}
	}
	if (y_dir == 0x01) {
		if ((*wy) <= y_min + y_mov){
			(*wy)   =  y_min;
			(*dir) &= ~0x01;
		} else {
			(*wy) -= y_mov;
		}
	} else if (y_dir == 0) {
		if ((*wy) >= y_max - y_mov){
			(*wy)   = y_max;
			(*dir) |= 0x01;
		} else {
			(*wy) += y_mov;
		}
	}
}

/**
 * Rotates on HEO
 */
static void _rotates(void)
{
	int32_t w = heo_w, h = heo_h;
	uint16_t rotate = 0;

	if (!lcdc_is_layer_on(LCDC_HEO))
		return;

	switch (heo_draw){
		/* Origional size */
		case 0:
			heo_draw = 1;
			w = heo_img_w;
			h = heo_img_h;
			break;
		/* Mirrow (scan direction) */
		case 1:
			heo_draw = 2;
			break;
		case 2:
			heo_draw = 3;
			h = -h;
			break;
		case 3:
			heo_draw = 4;
			h = -h; w = -w;
			break;
		case 4:
			heo_draw = 5;
			w = -w;
			break;
		/* Goes Back */
		case 5:
			heo_draw = 6;
			w = heo_img_w;
			h = heo_img_h;
			break;
		/* Rotate (0?) */
		case 6:
			heo_draw = 7;
			break;
		/* Rotate (90?) */
		case 7:
			heo_draw = 8;
			w = heo_h;
			h = heo_w;
			heo_h = h;
			heo_w = w;
			rotate = 90;
			break;
		/* X mirror & Rotate (90?) */
		case 8:
			heo_draw = 9;
			w = (0-heo_w);
			h = heo_h;
			rotate = 90;
			break;
		/* Rotate (180?) */
		case 9:
			heo_draw = 10;
			w = heo_h;
			h = heo_w;
			heo_h = h;
			heo_w = w;
			rotate = 180;
			break;
		/* Rotate (270?) */
		case 10:
			heo_draw = 11;
			w = heo_h;
			h = heo_w;
			heo_h = h;
			heo_w = w;
			rotate = 270;
			break;
		/* Y mirror & Rotate (270?) */
		case 11:
			heo_draw = 12;
			w = heo_w;
			h = 0-heo_h;
			rotate = 270;
			break;
		/* Rotate (0?) */
		case 12:
			heo_draw = 0;
			w = heo_h;
			h = heo_w;
			heo_h = h;
			heo_w = w;
			break;
	}
	if (SCR_X(heo_x) + abs(w) > BOARD_LCD_WIDTH){
		heo_x = IMG_X(BOARD_LCD_WIDTH - abs(w));
	}
	if (SCR_Y(heo_y) + abs(h) > BOARD_LCD_HEIGHT){
		heo_y = IMG_Y(BOARD_LCD_HEIGHT - abs(h));
	}

	printf("Show: %u,%u %d, %d %u\r\n", (unsigned)SCR_X(heo_x),
	       (unsigned)SCR_Y(heo_y), (int)w, (int)h, (unsigned)rotate);
	lcdc_put_image_rotated(LCDC_HEO, 0, heo_bpp, SCR_X(heo_x), SCR_Y(heo_y),
			      w, h, heo_img_w, heo_img_h, rotate);

	if (heo_draw == 0) {
		printf("\r\n");
		printf("------------------------------------\r\n");
		printf(" Use 'SPACE' to change HEO priority\r\n");
		printf("------------------------------------\r\n");
	}
}

#ifdef CONFIG_HAVE_LCDC_OVR1

/**
 * Draw on canvas
 */
static void _draws(void)
{
	uint32_t x, y, w, h;

	x = orv1_w / 2;
	y = ovr1_h / 2;
	if (!lcdc_is_layer_on(LCDC_OVR1))
		return;

	/* Drawing width, height */
	if (draw_size == 0) {
		w = h = 2;
	} else {
		w = orv1_w / 10 * draw_size;
		h = ovr1_h / 10 * draw_size;
	}

	/* Draw circles */
	if (draw_shape){
		/* Remove last shape */
		lcd_draw_circle(x, y, last_w > last_h ? last_h/2 : last_w/2, OVR1_BG);
		/* Draw new */
		lcd_draw_circle(x, y, w > h ? h/2 : w/2, test_colors[ncolor]);
		ncolor = (ncolor+1)%NB_TAB_COLOR;
	} else {
		/* Remove last shape */
		lcd_draw_rounded_rect(x - last_w/2, y - last_h/2, last_w, last_h, last_h/3, OVR1_BG);
		/* Draw new */
		lcd_draw_rounded_rect(x - w/2, y - h/2, w, h, h/3, test_colors[ncolor]);
		ncolor = (ncolor + 1) % NB_TAB_COLOR;
	}
	last_w = w;
	last_h = h;

	/* Size -- */
	if (draw_changed) {
		if (draw_size == 0) {
			draw_shape = !draw_shape;
			draw_changed = 0;
		} else {
			draw_size--;
		}
	}
	/* Size ++ */
	else {
		if (draw_size == 8) {
			draw_changed = 1;
		} else {
			draw_size++;
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

#endif /* CONFIG_HAVE_LCDC_OVR1 */

/**
 * Move layers.
 */
static void _moves(void)
{
#ifdef CONFIG_HAVE_LCDC_OVR1
	if (lcdc_is_layer_on(LCDC_OVR1)){
		_move_calc(&ovr1_x, &ovr1_y, &ovr1_dir,
				1, 1,
				0, BOARD_LCD_WIDTH - orv1_w - 1,
				ovr1_h, BOARD_LCD_HEIGHT - 1);
		lcdc_set_position(LCDC_OVR1, SCR_X(ovr1_x), SCR_Y(ovr1_y));
	}
#endif /* CONFIG_HAVE_LCDC_OVR1 */

#ifdef CONFIG_HAVE_LCDC_OVR2
	if (lcdc_is_layer_on(LCDC_OVR2)){
		_move_calc(&ovr2_x, &ovr2_y, &ovr2_dir,
				1, 1,
				0, BOARD_LCD_WIDTH - ovr2_w - 1,
				ovr2_h, BOARD_LCD_HEIGHT - 1);
		lcdc_set_position(LCDC_OVR2, SCR_X(ovr2_x), SCR_Y(ovr2_y));
	}
#endif /* CONFIG_HAVE_LCDC_OVR2 */

	if (lcdc_is_layer_on(LCDC_HEO)){
		_move_calc(&heo_x, &heo_y, &heo_dir,
				2, 3,
				0, BOARD_LCD_WIDTH - heo_w - 1,
				heo_h, BOARD_LCD_HEIGHT - 1);
		lcdc_set_position(LCDC_HEO, SCR_X(heo_x), SCR_Y(heo_y));
	}
}

/**
 * Handle DBGU events.
 */
static void dbg_events(void)
{
	uint8_t key;
	if (console_is_rx_ready()){
		key = console_get_char();
		switch(key){
			case ' ': /* HEO & OVR1 layout */
				lcdc_set_priority(LCDC_HEO,
						!lcdc_get_priority(LCDC_HEO));
				printf("Changed HEO priority\r\n");
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
	uint32_t heo_delay = 0;
#ifdef CONFIG_HAVE_LCDC_OVR1
	uint32_t ovr1_delay = 0;
#endif

	/* Output example information */
	console_example_info("LCD Example");

	/* Configure LCD */
	_LcdOn();

	t1 = timer_get_tick();
	printf("ADDR_LCD_BUFFER_HEO is 0x%x, size %u\r\n",
	       (unsigned)_heo_buffer,
	       (unsigned)sizeof(_heo_buffer));
	while(1) {
		dbg_events();
		t2 = timer_get_tick();
		/* Move layers */
		if ((t2 - t1) >= 10) {
			t1 = t2;
			_moves();
#ifdef CONFIG_HAVE_LCDC_OVR1
			/* Change OVR1  */
			if (ovr1_delay >= 500 / 50){
				ovr1_delay = 0;
				_draws();
				led_toggle(0);
			} else {
				ovr1_delay++;
			}
#endif
			/* Change HEO display mode */
			if (heo_delay >= 4000 / 50) {
				heo_delay = 0;
				_rotates();
			} else {
				heo_delay++;
			}
		}
	}
}
