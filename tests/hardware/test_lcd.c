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

#include "video/lcdd.h"
#include "lcd_draw.h"
#include "lcd_font.h"
#include "lcd_color.h"
#include "font.h"

#include "peripherals/twi.h"
#include "peripherals/twid.h"

#include "video/qt1070.h"

#include "peripherals/rtc.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hardware/icone_clim.h"

//#include "hardware/newlogoMF02.h"
#include "hardware/monkey_480-272.h"


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

/** Width for OVR1 */
#define OVR1_W      (BOARD_LCD_WIDTH*5/6)
/** Height for OVR1 */
#define OVR1_H      (BOARD_LCD_HEIGHT*5/6)

#define BASE_COLOR_BG	COLOR_WHITE
#define OVR1_COLOR_BG   COLOR_WhiteSmoke
#define OVR2_COLOR_BG	COLOR_SNOW
#define HEO_COLOR_BG	COLOR_WHITE

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
    COLOR_BLACK,  COLOR_Aqua,  COLOR_BLUE,  COLOR_Fuchsia,  COLOR_GRAY,  COLOR_GREEN,
    COLOR_Lime,  COLOR_Maroon,  COLOR_NAVY,  COLOR_OLIVE, COLOR_ORANGE, COLOR_Purple,
    COLOR_RED, COLOR_SILVER, COLOR_Teal, COLOR_YELLOW, COLOR_YELLOWGREEN, COLOR_MistyRose,
    COLOR_SKYBLUE, COLOR_VIOLET, COLOR_DARKGRAY, COLOR_DARKGREEN, COLOR_BEIGE, COLOR_BROWN,
};

/** Backlight value */
static uint8_t bBackLight = 0xF0;

static uint16_t wOvr1X = 0;
static uint16_t wOvr1Y = BOARD_LCD_HEIGHT-1;
static uint16_t wOvr1W = 0;
static uint16_t wOvr1H = 0;

static uint16_t wOvr2X = 0;
static uint16_t wOvr2Y = 0;
static uint16_t wOvr2W = 0;
static uint16_t wOvr2H = 0;

static uint16_t wHeoX = 0;
static uint16_t wHeoY = 0;
static uint16_t wHeoW = 0;
static uint16_t wHeoH = 0;

#define NB_TAB_COLOR N_BLK_HOR*N_BLK_VERT
uint8_t ncolor = 0;

uint8_t qt1070_key = 0;

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
	.transfert_mode = TWID_MODE_FIFO
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

/**
 * Turn ON LCD, show base .
 */
static void _LcdOn(void)
{
	void *pBuffer = NULL;

	lcdd_on();
	lcdd_set_backlight(bBackLight);
	pBuffer = lcdd_create_canvas(LCDD_BASE, pBaseBuffer, 24, 0, 0, BOARD_LCD_WIDTH, BOARD_LCD_HEIGHT);
	test_pattern_24RGB(pBaseBuffer);
	//timer_wait(1000);

	/* OVR1 */
	wOvr1X = IMG_X(30);
	wOvr1Y = IMG_Y(135);
	wOvr1W = BOARD_LCD_WIDTH/2;
	wOvr1H = BOARD_LCD_HEIGHT/2;
	pBuffer = lcdd_create_canvas(LCDD_OVR1, pOvr1Buffer, 24, SCR_X(wOvr1X), SCR_Y(wOvr1Y), wOvr1W, wOvr1H);
	lcdd_set_color_keying(LCDD_OVR1, 0, OVR1_COLOR_BG, 0xFFFFFF);
	lcdd_fill(OVR1_COLOR_BG);

	/* OVR2 */
	wOvr2X = IMG_X(BOARD_LCD_WIDTH/2);
	wOvr2Y = IMG_Y(0);
	wOvr2W = BOARD_LCD_WIDTH/2;
	wOvr2H = BOARD_LCD_HEIGHT;
	pBuffer = lcdd_create_canvas(LCDD_OVR2, pOvr2Buffer, 24, SCR_X(wOvr2X), SCR_Y(wOvr2Y), wOvr2W, wOvr2H);
	lcdd_set_color_keying(LCDD_OVR2, 0, OVR2_COLOR_BG, 0xFFFFFF);
	lcdd_fill(OVR2_COLOR_BG);

	/* HE0 */
	wHeoX = 10;
	wHeoY = BOARD_LCD_HEIGHT-35;
	wHeoW = 270;
	wHeoH = 30;
	pBuffer = lcdd_create_canvas(LCDD_HEO, pHeoBuffer, 24, wHeoX, wHeoY, wHeoW, wHeoH);
	lcdd_set_color_keying(LCDD_HEO, 0, HEO_COLOR_BG, 0xFFFFFF);
	lcdd_fill(HEO_COLOR_BG);
	lcdd_fill_rounded_rect (0, 0, wHeoW, wHeoH, 12, COLOR_BLUE);
	lcdd_draw_rounded_rect (0, 0, wHeoW, wHeoH, 12, COLOR_BLACK);
	lcdd_draw_string(5, 8, " Powered by ATMEL-RF0 ", COLOR_WHITE);

	lcdd_select_canvas(LCDD_BASE);
	lcdd_fill(BASE_COLOR_BG);

	//lcdd_draw_image(0, 0, &rawMonkeyData[HEADER_SIZE], 480, 272);
	//circle_moving_around_circle();

	widget_thermostat(LCDD_OVR2, wOvr2W, wOvr2H);
}

void display_icone (void)
{
	lcdd_draw_image(10, 10, &icone_clim[54], 50, 50);
}

#define HMS_POS_X BOARD_LCD_WIDTH-120
#define HMS_POS_Y 15

void display_hms(struct _time* mtu)
{
	char buf[16] = {0};
	uint32_t x = HMS_POS_X, y = HMS_POS_Y;

	sLCDDLayer* psLAYR = lcdd_get_canvas();
	lcdd_select_canvas(LCDD_BASE);

	uint8_t prev_font = lcdd_get_selected_font();
	lcdd_select_font(FONT10x8);
	uint8_t font = lcdd_get_selected_font();
	uint8_t width = font_param[font].width ;
	uint8_t height = font_param[font].height;
	uint8_t cspace = font_param[font].char_space;

	lcdd_draw_filled_rectangle(x, y, x+(9*(width+cspace)), y+height+1, BASE_COLOR_BG);
	sprintf(buf, "%02dh%02dm%02ds", mtu->hour, mtu->min, mtu->sec);
	lcdd_draw_string(x, y, buf, COLOR_BLACK);

	lcdd_select_font(prev_font);
	lcdd_select_canvas(psLAYR->bLayer);
}

uint8_t test_lcd (void)
{
	uint8_t status = 0;

	/* Check if find QT1070 on LCD PDA4300 */
	/* configure twi QT1070 */
	pio_configure(qt1070_pins, ARRAY_SIZE(qt1070_pins));
	/* configure handler twi QT1070 */
	qt1070_configure(&qt1070_drv, &qt1070_twid);
	if (qt1070_drv.chip_id == 0x2E) {
		printf("-I- QT1070 detected \n\r");
		printf("-I- Chip ID : 0x%2X \n\r", qt1070_drv.chip_id );
		printf("-I- Firm.V. : 0x%2X \n\r", qt1070_drv.firmware_version );
		printf("-I- LCD TM4301 \n\r");
		/* configure irq qt1070 */
		configure_pin_qt1070();

		/* Configure LCD */
		lcdd_initialize(pins_lcd, ARRAY_SIZE(pins_lcd));
		_LcdOn();
	}
	return status;
}

uint8_t state_base = 1;
uint8_t state_ovr1 = 1;
uint8_t state_ovr2 = 1;
uint8_t state_heo = 1;

void lcd_app_qtouch (void)
{
	switch (qt1070_key) {
		case 0x01:
			state_base = (~state_base)&0x01;
			lcdd_enable_layer(LCDD_BASE, state_base);
			break;
		case 0x02:
			state_ovr1 = (~state_ovr1)&0x01;
			lcdd_enable_layer(LCDD_OVR1, state_ovr1);
			break;
		case 0x04:
			state_ovr2 = (~state_ovr2)&0x01;
			lcdd_enable_layer(LCDD_OVR2, state_ovr2);
			break;
		case 0x08:
			state_heo = (~state_heo)&0x01;
			lcdd_enable_layer(LCDD_HEO, state_heo);
			break;
		default:
			break;
	}
	qt1070_key = 0x00;
}
