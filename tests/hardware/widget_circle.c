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

/* Demo do draw a little circle moving around a main circle
 *
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

#include "utils/widget.h"

#include <stdint.h>

/*----------------------------------------------------------------------------
 *         Global definitions
 *----------------------------------------------------------------------------*/

struct _size {
	uint16_t w;
	uint16_t h;
};

struct circle {
	struct _point org;
	uint32_t bg_color;
	uint32_t border_color;
	uint8_t radius;
};

struct widget_desc {
	uint8_t layer;
	struct _point org;
	struct _point dest;
	struct _size size;
	uint32_t bg_color;
	uint32_t txt_color;
	uint8_t font_sel;
};

struct widget_desc cwdesc;
struct circle mcircle;
struct circle scircle;

static uint16_t last_degre ;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

/*
 * Init graphic environment
 * Layer: layer on LCD
 * X, Y : origin
 * W, H : not used
 */
void init_widget_descriptor (uint8_t layer, uint16_t X, uint16_t Y, uint16_t W, uint16_t H)
{
	cwdesc.layer = layer;
	cwdesc.org.x = X;
	cwdesc.org.y = Y;
	cwdesc.size.w = W;
	cwdesc.size.h = H;
	cwdesc.bg_color = COLOR_WHITE;
	cwdesc.txt_color = COLOR_BLUE;
	cwdesc.font_sel = FONT10x8;
}

/* Main circle
 *
 */
void init_mcircle (uint16_t X, uint16_t Y, uint32_t bg_color, uint32_t border_color, uint8_t radius)
{
	mcircle.org.x = X;
	mcircle.org.y = Y;
	mcircle.bg_color = bg_color;
	mcircle.border_color = border_color;
	mcircle.radius = radius;

	lcdd_draw_filled_circle(X, Y, radius, bg_color);
	lcdd_draw_circle(X, Y, radius, border_color);
}

/* Secondary or animate circle
 *
 */
void init_scircle (uint32_t bg_color, uint32_t border_color, uint8_t radius)
{
	scircle.org.x = mcircle.org.x;
	scircle.org.y = mcircle.org.y - (mcircle.radius-radius);
	scircle.bg_color = bg_color;
	scircle.border_color = border_color;
	scircle.radius = radius;

	lcdd_draw_filled_circle(mcircle.org.x, mcircle.org.y, mcircle.radius-(radius*2), bg_color);
	lcdd_draw_circle(mcircle.org.x, mcircle.org.y, mcircle.radius-(radius*2), border_color);

//	lcdd_draw_filled_circle(scircle.org.x, scircle.org.y, radius, scircle.bg_color);
//	lcdd_draw_circle(scircle.org.x, scircle.org.y, radius, scircle.border_color);

}

/*
 * Draw circle
 *
 */
void circle_moving_around_circle (void)
{
	uint16_t i;
	sLCDDLayer* psLAYR;
	struct _point pt;

	/* save activ layer */
	psLAYR = lcdd_get_canvas();
	/* set layer binary clock */
	lcdd_select_canvas(cwdesc.layer);

	init_widget_descriptor (LCDD_BASE, 0, 0, BOARD_LCD_WIDTH, BOARD_LCD_HEIGHT);
	init_mcircle (200, 150, COLOR_WHITE, COLOR_BLACK, 60);
	init_scircle (COLOR_BLUE, COLOR_WHITE, 10);

	i = 10;
	do {
		lcdd_draw_filled_circle(scircle.org.x, scircle.org.y, scircle.radius, COLOR_WHITE);
		pt = mcircle.org;
		point_on_circle (&pt, mcircle.radius-scircle.radius, i);
		scircle.org = pt;
		lcdd_draw_filled_circle(scircle.org.x, scircle.org.y, scircle.radius, scircle.bg_color);

		lcdd_draw_circle(mcircle.org.x, mcircle.org.y, mcircle.radius, mcircle.border_color);
		lcdd_draw_circle(mcircle.org.x, mcircle.org.y, mcircle.radius+1, mcircle.border_color);

		//lcdd_draw_circle(mcircle.org.x, mcircle.org.y, mcircle.radius-(mcircle.radius*2), mcircle.border_color);
		//lcdd_draw_circle(mcircle.org.x, mcircle.org.y, mcircle.radius-(mcircle.radius*2)-1, mcircle.border_color);

		i = (i+10) %360;

	}while (i!=0);

	lcdd_select_canvas(psLAYR->bLayer);
}

#define TEMP_RANGE_MIN	0
#define TEMP_RANGE_MAX	40
#define STEP			12

static uint8_t old_consigne ;

void display_thermostat_consigne (uint8_t temp_consigne)
{
	uint16_t x, val, temp ;
	uint8_t radius2, radius3 ;
	char Buf[16];

	/* save activ layer */
	sLCDDLayer* psLAYR ;
	psLAYR = lcdd_get_canvas();
	lcdd_select_canvas(cwdesc.layer);

	uint8_t prev_font = lcdd_get_selected_font();
	lcdd_select_font(cwdesc.font_sel);
	uint8_t font = lcdd_get_selected_font();
	uint8_t width = font_param[font].width ;
	uint8_t height = font_param[font].height;
	uint8_t cspace = font_param[font].char_space;

	val =  mcircle.radius / 10;
	radius2 = val * 6;
	radius3 = val * 4;

	temp = 240 / (TEMP_RANGE_MAX - TEMP_RANGE_MIN);
	x = (240 + (old_consigne * temp)) % 360;

	widget_draw_vector (mcircle.org.x, mcircle.org.y, (uint32_t)radius2-3, radius2-radius3-5, x, COLOR_WHITE);

	temp = 240 / (TEMP_RANGE_MAX - TEMP_RANGE_MIN);
	x = (240 + (temp_consigne * temp)) % 360;

	widget_draw_vector (mcircle.org.x, mcircle.org.y, (uint32_t)radius2-3, radius2-radius3-5, x, COLOR_BLUE);

	sprintf(Buf, "  ", temp_consigne);
	lcdd_draw_string (mcircle.org.x-width-cspace, mcircle.org.y, Buf, COLOR_BLUE);
	sprintf(Buf, "%02d", temp_consigne);
	lcdd_draw_string (mcircle.org.x-width-cspace, mcircle.org.y, Buf, COLOR_BLUE);

	old_consigne = temp_consigne;

	lcdd_select_font(prev_font);
	lcdd_select_canvas(psLAYR->bLayer);
}

void widget_thermostat (uint8_t layer, uint16_t w, uint16_t h)
{
    uint16_t degre, step, x ;
	uint8_t val;
	uint8_t radius2, radius3 ;

	/* save activ layer */
	sLCDDLayer* psLAYR ;
	psLAYR = lcdd_get_canvas();

	init_widget_descriptor (layer, 0, 0, w, h);
	lcdd_select_canvas(cwdesc.layer);
	init_mcircle (cwdesc.size.w/2, cwdesc.size.h/2, COLOR_WHITE, COLOR_BLACK, cwdesc.size.h/4);

	val =  mcircle.radius / 10;
	radius2 = val * 6;
	radius3 = val * 4;

    lcdd_draw_filled_circle(mcircle.org.x, mcircle.org.y, mcircle.radius, COLOR_LIGHTGREY);
	lcdd_draw_circle (mcircle.org.x, mcircle.org.y, mcircle.radius, COLOR_BLACK);

	lcdd_draw_filled_circle (mcircle.org.x, mcircle.org.y, mcircle.radius-val, COLOR_BLACK);

    lcdd_draw_filled_circle (mcircle.org.x, mcircle.org.y, radius2, COLOR_ORANGE);
    lcdd_draw_filled_circle (mcircle.org.x, mcircle.org.y, radius3, COLOR_DarkOrange);

    degre = 120;
    step = STEP;
    x = degre/step;
	for (x=360-degre; x<360; x+=step) {
       widget_draw_vector (mcircle.org.x, mcircle.org.y, (uint32_t)radius2-3, radius2-radius3-5, x, COLOR_WHITE);
	}
	for (x=0; x<degre+step; x+=step) {
       widget_draw_vector (mcircle.org.x, mcircle.org.y, (uint32_t)radius2-3, radius2-radius3-5, x, COLOR_WHITE);
	}
	display_thermostat_consigne(20);

	/* restore previous layer */
	lcdd_select_canvas(psLAYR->bLayer);
}

/*
Tous les x millisecondes, faire :
    erreur = consigne - mesure;
    somme_erreurs += erreur;
    variation_erreur = erreur - erreur_précédente;
    commande = Kp * erreur + Ki * somme_erreurs + Kd * variation_erreur;
    erreur_précédente = erreur

	http://www.ferdinandpiette.com/blog/2011/08/implementer-un-pid-sans-faire-de-calculs/
*/
