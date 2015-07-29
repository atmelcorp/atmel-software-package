/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
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

/* Demo do draw a binary clock on LCD screen
 ** format
 *  . h h m m s s
 *  8 O O O O O O
 *  4 O O O O O O
 *  2 O O O O O O
 *  1 O O O O O O
 *
 * Time is 24h format
 */
/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/


#include "board.h"
#include "chip.h"

#include "video/lcdd.h"
#include "lcd_draw.h"
#include "lcd_font.h"
#include "lcd_color.h"
#include "font.h"

#include "peripherals/rtc.h"

#include <stdint.h>

/*----------------------------------------------------------------------------
 *         Global definitions
 *----------------------------------------------------------------------------*/

#define SIZE_CIRCLE_HB  7
#define NB_CIRCLE		8

const uint8_t Of7Y[NB_CIRCLE] = { 0x06, 0x04, 0x02, 0x00, 0x06, 0x04, 0x02, 0x00} ;

const uint8_t Of7X[3][NB_CIRCLE] =  {
  /*
  { 0x0F, 0x0F, 0x0F, 0x0F, 0x0C, 0x0C, 0x0C, 0x0C }, // Sec
  { 0x09, 0x09, 0x09, 0x09, 0x06, 0x06, 0x06, 0x06},  // Min
  { 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00},  // Hour
  */
  { 0x0A, 0x0A, 0x0A, 0x0A, 0x08, 0x08, 0x08, 0x08 }, // Sec
  { 0x06, 0x06, 0x06, 0x06, 0x04, 0x04, 0x04, 0x04},  // Min
  { 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00},  // Hour
} ;


struct _point {
	uint16_t x;
	uint16_t y;
} ;

struct _size {
	uint16_t w;
	uint16_t h;
};

struct hms_color {
	uint32_t h_color;
	uint32_t m_color;
	uint32_t s_color;
};

struct windows_desc {
	uint8_t layer;
	struct _point org;
	struct _point dest;
	struct _size size;
	uint32_t bg_color;
	uint32_t txt_color;
	uint16_t radius;
};

struct windows_desc wdesc;
struct hms_color tcolor;

struct _time prev_time = {0xFF, 0xFF, 0xFF};

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

uint16_t bcd_to_hex (uint16_t x)
{
  uint16_t val ;
  val = (x / 10) << 4;
  val = val | (x % 10);
  return val;
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

/*
 * Init graphic environment used by binary clock
 * Layer: layer on LCD
 * X, Y : origin
 * W, H : not used
 */
void init_binary_clock (uint8_t layer, uint16_t X, uint16_t Y, uint16_t W, uint16_t H)
{
	wdesc.layer = layer;
	wdesc.org.x = X;
	wdesc.org.y = Y;
	wdesc.size.w = W;
	wdesc.size.h = H;
	wdesc.bg_color = COLOR_WHITE;
	wdesc.txt_color = COLOR_BLACK;
	wdesc.radius = SIZE_CIRCLE_HB;

   	tcolor.h_color = COLOR_BLUE;
   	tcolor.m_color = COLOR_DARKRED;
   	tcolor.s_color = COLOR_DeepSkyBlue;
}
/*
 * Draw circle according to hms value
 *
 */
void draw_binary_clock (struct _time * pTime)
{
	uint8_t i, tx;
	uint16_t radius = wdesc.radius;
	uint32_t of7x, of7y, color;
	sLCDDLayer* psLAYR;

	/* save activ layer */
	psLAYR = lcdd_get_canvas();
	/* set layer binary clock */
	lcdd_select_canvas(wdesc.layer);
	/* update second */
    if (prev_time.sec != pTime->sec) {
		prev_time.sec = pTime->sec;
		tx = bcd_to_hex(pTime->sec);
		for (i=0; i<NB_CIRCLE; i++) {
		  color = (tx>>i)&0x1 ? tcolor.s_color : COLOR_LIGHTGREY;
		  of7x = radius*Of7X[0][i];
		  of7y = radius*Of7Y[i];
		  lcdd_draw_filled_circle (wdesc.org.x+of7x, wdesc.org.y+of7y, radius, color);
		  lcdd_draw_circle (wdesc.org.x+of7x,  wdesc.org.y+of7y, radius, COLOR_BLACK);
		}
	}
	/* update minute */
	if (prev_time.min != pTime->min) {
		prev_time.min = pTime->min;
		tx = bcd_to_hex(pTime->min);
		for (i=0; i<NB_CIRCLE; i++) {
			color = (tx>>i)&0x1 ? tcolor.m_color : COLOR_LIGHTGREY;
			of7x = radius*Of7X[1][i];
			of7y = radius*Of7Y[i];
			lcdd_draw_filled_circle (wdesc.org.x+of7x, wdesc.org.y+of7y, radius, color);
			lcdd_draw_circle (wdesc.org.x+of7x,  wdesc.org.y+of7y, radius, COLOR_BLACK);
		}
	}
	/* update hour */
	if (prev_time.hour != pTime->hour) {
		prev_time.hour = pTime->hour;
		tx = bcd_to_hex(pTime->hour);
		for (i=0; i<NB_CIRCLE; i++) {
			color = (tx>>i)&0x1 ? tcolor.h_color : COLOR_LIGHTGREY;
			of7x = radius*Of7X[2][i];
			of7y = radius*Of7Y[i];
			lcdd_draw_filled_circle (wdesc.org.x+of7x, wdesc.org.y+of7y, radius, color);
			lcdd_draw_circle (wdesc.org.x+of7x,  wdesc.org.y+of7y, radius, COLOR_BLACK);
		}
	}
	if (pTime->hour>12) {
		lcdd_draw_filled_circle (wdesc.org.x, wdesc.org.y, radius, COLOR_BLACK);
		lcdd_draw_circle (wdesc.org.x,  wdesc.org.y, radius, COLOR_BLACK);
	}
	lcdd_select_canvas(psLAYR->bLayer);
}



