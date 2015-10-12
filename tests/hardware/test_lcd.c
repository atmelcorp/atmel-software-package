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

/*------------------------------------------------------------------------------
 *        Header
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"

#include "peripherals/pio.h"
#include "peripherals/twi.h"
#include "peripherals/twid.h"
#include "peripherals/rtc.h"
#include "peripherals/l2cc.h"

#include "test_lcd.h"
#include "video/qt1070.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

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

/** Number of blocks in vertical */
#define N_BLK_VERT    4
/** Number of blocks in horizontal */
#define N_BLK_HOR     6

#define HEADER_SIZE	54

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** LCD BASE buffer */

SECTION(".region_ddr") static uint8_t _base_buffer[SIZE_LCD_BUFFER_BASE];

/** Overlay 1 buffer */

SECTION(".region_ddr") static uint8_t _ovr1_buffer[SIZE_LCD_BUFFER_OVR1];

/** Overlay 2 buffer */

SECTION(".region_ddr") static uint8_t _ovr2_buffer[SIZE_LCD_BUFFER_OVR2];

/** High End Overlay buffer */

SECTION(".region_ddr") static uint8_t _heo_buffer[SIZE_LCD_BUFFER_HEO];

/** Pins for LCDC */
static const struct _pin pins_lcd[] = PINS_LCD;

/** Test pattern source */
static uint32_t test_colors[N_BLK_HOR*N_BLK_VERT] = {
    COLOR_BLACK,  COLOR_Aqua,  COLOR_BLUE,  COLOR_Fuchsia,  COLOR_GRAY,  COLOR_GREEN,
    COLOR_Lime,  COLOR_Maroon,  COLOR_NAVY,  COLOR_OLIVE, COLOR_ORANGE, COLOR_Purple,
    COLOR_RED, COLOR_SILVER, COLOR_Teal, COLOR_YELLOW, COLOR_YELLOWGREEN, COLOR_MistyRose,
    COLOR_SKYBLUE, COLOR_VIOLET, COLOR_DARKGRAY, COLOR_DARKGREEN, COLOR_BEIGE, COLOR_BROWN,
};

/** Backlight value */
static uint8_t bBackLight = 0xF0;

#define NB_TAB_COLOR N_BLK_HOR*N_BLK_VERT
uint8_t ncolor = 0;

uint8_t qt1070_key = 0;

/** Layer descriptor */

static struct _lcdd_layer_desc base_desc = {
	.state = 1,
	.layer = LCDD_BASE,
	.pbuffer = _base_buffer,
	.bit_per_pixel = 24,
	.org.x = 0,
	.org.y = 0,
	.dest.x = 0,
	.dest.y = 0,
	.size.w = BOARD_LCD_WIDTH,
	.size.h = BOARD_LCD_HEIGHT,
	.bg_color = COLOR_WHITE,
	.brd_color = COLOR_BLACK,
	.txt_color = COLOR_BLACK,
};

static struct _lcdd_layer_desc ovr1_desc = {
	.state = 1,
	.layer = LCDD_OVR1,
	.pbuffer = _ovr1_buffer,
	.bit_per_pixel = 24,
	.org.x = SCR_X(IMG_X(0)),
	.org.y = SCR_Y(IMG_Y(0)),
	.dest.x = 0,
	.dest.y = 0,
	.size.w = BOARD_LCD_WIDTH/2,
	.size.h = BOARD_LCD_HEIGHT,
	.bg_color = COLOR_WhiteSmoke,
	.brd_color = COLOR_BLACK,
	.txt_color = COLOR_BLACK,
};

static struct _lcdd_layer_desc ovr2_desc = {
	.state = 1,
	.layer = LCDD_OVR2,
	.pbuffer =  _ovr2_buffer,
	.bit_per_pixel = 24,
	.org.x = SCR_X(IMG_X(BOARD_LCD_WIDTH/2)),
	.org.y = SCR_Y(IMG_Y(0)),
	.dest.x = 0,
	.dest.y = 0,
	.size.w = BOARD_LCD_WIDTH/2,
	.size.h = BOARD_LCD_HEIGHT,
	.bg_color = COLOR_SNOW,
	.brd_color = COLOR_BLACK,
	.txt_color = COLOR_BLACK,
};

static struct _lcdd_layer_desc heo_desc = {
	.state = 1,
	.layer = LCDD_HEO,
	.pbuffer = _heo_buffer,
	.bit_per_pixel = 24,
	.org.x = 10,
	.org.y = BOARD_LCD_HEIGHT-30,
	.dest.x = 0,
	.dest.y = 0,
	.size.w = BOARD_LCD_WIDTH-(10*2),
	.size.h = 30,
	.bg_color = COLOR_WHITE,
	.brd_color = COLOR_BLACK,
	.txt_color = COLOR_BLACK,
};

/** Widget descriptor */

/*------------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------*/

static const struct _pin qt1070_pins[] = QT1070_PINS;
static const struct _pin qt1070_irq[] = PIN_QT1070_IRQ;

struct _qt1070 qt1070_drv = {
	.desc = QT1070_DESC
};

struct _twi_desc qt1070_twid = {
	.addr = QT1070_ADDR,
	.freq = QT1070_FREQ,
	.transfert_mode = TWID_MODE_POLLING
};

/*------------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------*/

/**
 *  Interrupt handler QT1070 pin.
 */
static void qt1070_irq_handler(uint32_t mask, uint32_t status, void* user_arg)
{
	uint8_t detect_status;
	detect_status = qt1070_get_detection_status(&qt1070_drv);
	if ( detect_status & 0x01) {
		qt1070_key = qt1070_get_key_status(&qt1070_drv);
	}
	else  {
		detect_status = qt1070_get_key_status(&qt1070_drv);
	}
}

/**
 *  Configure pin irq QT1070
*/
void configure_pin_qt1070(void)
{
	/* Configure Pio and interrupt */
	pio_configure(&qt1070_irq[0], 1);
	pio_configure_it(&qt1070_irq[0]);
	pio_add_handler_to_group(qt1070_irq[0].group, qt1070_irq[0].mask, qt1070_irq_handler, NULL);
	pio_enable_it(&qt1070_irq[0]);
}

/*------------------------------------------------------------------------------
 *
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

struct _lcdd_layer_desc* get_layer_desc (uint8_t layer)
{
	switch (layer) {
		case LCDD_BASE: return &base_desc; break;
		case LCDD_OVR1: return &ovr1_desc; break;
		case LCDD_OVR2: return &ovr2_desc; break;
		case LCDD_HEO: return &heo_desc; break;
	}
	return NULL;
}

void* create_canvas (struct _lcdd_layer_desc* ld)
{
	return lcdd_create_canvas(ld->layer, ld->pbuffer, ld->bit_per_pixel,
							  ld->org.x, ld->org.y, ld->size.w, ld->size.h);
}

/**
 * Turn ON LCD, show base .
 */
static void _LcdOn(void)
{
	void *pBuffer = NULL;

	test_pattern_24RGB (base_desc.pbuffer);
	l2cc_clean_region((uint32_t)_base_buffer, (uint32_t)_base_buffer + sizeof(_base_buffer));

	/* OVR1 */
	pBuffer = create_canvas(&ovr1_desc);
	lcdd_set_color_keying(ovr1_desc.layer, 0, ovr1_desc.bg_color, 0xFFFFFF);
	lcdd_fill(ovr1_desc.bg_color);

	/* OVR2 */
	pBuffer = create_canvas(&ovr2_desc);
	lcdd_set_color_keying(ovr2_desc.layer, 0, ovr2_desc.bg_color, 0xFFFFFF);
	lcdd_fill(ovr2_desc.bg_color);

	/* HE0 */
	pBuffer = create_canvas(&heo_desc);
	lcdd_set_color_keying(heo_desc.layer, 0, heo_desc.bg_color, 0xFFFFFF);
	lcdd_fill(heo_desc.bg_color);
	lcdd_set_alpha(heo_desc.layer, 1, 128);
	lcdd_set_priority(heo_desc.layer, 0);

	lcdd_on();
	lcdd_set_backlight(bBackLight);
	lcdd_show_base(_base_buffer, 24, 0);

	/* BASE */
	lcdd_select_canvas(LCDD_BASE);
	//lcdd_fill(base_desc.bg_color);

}

/**
 * Display a string on layer.
 */
void display_widget_string_on_layer (uint8_t layer, struct _text* txt, char* str)
{
	uint8_t radius, save_font;
	uint16_t offset;
	sLCDDLayer* psLAYR ;

	/* save activ layer */
	psLAYR = lcdd_get_canvas();
	lcdd_select_canvas(layer);
	/* save activ font */
	save_font = lcdd_get_selected_font();
	lcdd_select_font ((_FONT_enum)txt->font_sel);

	if(txt->size.w == 0 || txt->size.h == 0) {
		lcdd_get_string_size(str, &txt->size.w, &txt->size.h);
	}
	radius = txt->size.h/4*3;
	offset = 8;
	lcdd_fill_rounded_rect (txt->org.x, txt->org.y, txt->size.w, txt->size.h+offset, radius, txt->bg_color);
	lcdd_draw_rounded_rect (txt->org.x, txt->org.y, txt->size.w, txt->size.h+offset, radius, COLOR_BLACK);
	lcdd_draw_string(txt->org.x, txt->org.y+(offset/2), str, txt->txt_color);

	/* restore previous font */
	lcdd_select_font((_FONT_enum)save_font);
	/* restore activ layer */
	lcdd_select_canvas(psLAYR->bLayer);
}

/**
 * Init layer and test LCD.
 */
uint8_t test_lcd (void)
{
	uint8_t status = 0;

	/* Check if find QT1070 on LCD PDA4300 */
	printf("-I- Check QTouch interface \n\r");
	/* configure twi QT1070 */
	pio_configure(qt1070_pins, ARRAY_SIZE(qt1070_pins));
	/* configure handler twi QT1070 */
	qt1070_configure(&qt1070_drv, &qt1070_twid);
	if (qt1070_drv.chip_id != 0x2E) {
		printf("-E- QT1070 not detected \n\r");
		status = 1;
	}
	else {
		printf("-I- QT1070 detected \n\r");
		printf("-I- Chip ID : 0x%2X \n\r", qt1070_drv.chip_id );
		printf("-I- Firm.V. : 0x%2X \n\r", qt1070_drv.firmware_version );
		printf("-I- LCD TM4301 \n\r");
		/* configure irq qt1070 */
		configure_pin_qt1070();

		/* Configure LCD 4.3" */
		lcdd_initialize(pins_lcd, ARRAY_SIZE(pins_lcd));
		_LcdOn();

		/* Display powered by ..*/
		struct _text txt = {
			.org.x = 10,	// relative on layer HEO
			.org.y = 5,		// relative on layer HEO
			.size.w = 0,
			.size.h = 0,
			.font_sel = FONT10x14,
			.bg_color = COLOR_BLUE,
			.txt_color = COLOR_WHITE
		};
		display_widget_string_on_layer(LCDD_HEO, &txt, " Powered by ATMEL-RFO ");
	}
	return status;
}
/**
 * Check Qtouch and Enable, disable layer.
 */
void lcd_app_qtouch (void)
{
	switch (qt1070_key) {
		case 0x01:
			//base_desc.state = (~base_desc.state)&0x01;
			//lcdd_enable_layer(LCDD_BASE, base_desc.state);
			lcdd_select_canvas(LCDD_BASE);
			lcdd_fill(base_desc.bg_color);

			break;
		case 0x02:
			ovr1_desc.state = (~ovr1_desc.state)&0x01;
			lcdd_enable_layer(LCDD_OVR1, ovr1_desc.state);
			break;
		case 0x04:
			ovr2_desc.state = (~ovr1_desc.state)&0x01;
			lcdd_enable_layer(LCDD_OVR2, ovr2_desc.state);
			break;
		case 0x08:
			heo_desc.state = (~heo_desc.state)&0x01;
			lcdd_enable_layer(LCDD_HEO, heo_desc.state);
			break;
		default:
			break;
	}
	qt1070_key = 0x00;
}
