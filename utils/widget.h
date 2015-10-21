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

#ifndef _WIDGET_H_
#define _WIDGET_H_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "video/lcdd.h"
#include "lcd_draw.h"
#include "lcd_font.h"
#include "lcd_color.h"
#include "font.h"

#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Define
 *----------------------------------------------------------------------------*/

struct _point {
	int32_t x;
	int32_t y;
	int32_t z;
};

struct _size {
	uint32_t w;
	uint32_t h;
};

struct _circle {
	struct _point org;
	struct _point old;
	uint32_t bg_color;
	uint32_t border_color;
	uint8_t radius;
};

struct _rect {
	struct _point org;
	struct _point dest;
	struct _size size;
	uint32_t bg_color;
	uint32_t border_color;
	uint8_t radius;
};

struct _triangle {
	struct _point pt1;
	struct _point pt2;
	struct _point pt3;
	uint16_t segment;
};

struct _text {
	struct _point org;
	struct _size size;
	uint8_t font_sel;
	uint32_t bg_color;
	uint32_t txt_color;
};

struct _3color {
	uint32_t color1;
	uint32_t color2;
	uint32_t color3;
};

struct _widget_desc {
	uint8_t layer;
	struct _point org;
	struct _point dest;
	struct _size size;
	uint32_t bg_color;
	uint32_t bord_color;
	uint16_t radius;
	struct _text txt;
};

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

extern uint16_t bcd_to_hex (uint16_t x);

extern uint8_t bcd_decimal(uint8_t hex);

extern void point_on_circle (struct _point* org, uint16_t radius,
			     uint16_t angle);

extern void rotate_point (struct _point* org, struct _point* pt,
			  uint16_t angle, uint8_t clockwise);

extern void widget_draw_vector (uint32_t X, uint32_t Y, uint32_t radius,
			uint8_t segment, uint16_t degre, uint32_t color);

#endif /* #ifndef _WIDGET_H_ */
