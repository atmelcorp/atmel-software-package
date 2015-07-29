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


/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "widget.h"
#include "video/lcdd.h"
#include "lcd_draw.h"
#include "lcd_color.h"

#include <stdlib.h>

/*----------------------------------------------------------------------------
 *        Local constante
 *----------------------------------------------------------------------------*/

#define NBDEGRE 90+1
#define ISIN    1
#define ICOS    2

// angle degre Sinus, Cosinus
const double SinCos[NBDEGRE][3] =
{
	{0,	0.000,	1.000},
	{1,	0.017,	1.000},
	{2,	0.035,	1.000},
	{3,	0.052,	0.999},
	{4,	0.070,	0.999},
	{5,	0.087,	0.998},
	{6,	0.105,	0.995},
	{7,	0.122,	0.993},
	{8,	0.139,	0.990},
	{9,	0.156,	0.988},
	{10,	0.174,	0.985},
	{11,	0.191,	0.982},
	{12,	0.208,	0.978},
	{13,	0.225,	0.974},
	{14,	0.242,	0.970},
	{15,	0.259,	0.966},
	{16,	0.276,	0.961},
	{17,	0.292,	0.956},
	{18,	0.309,	0.951},
	{19,	0.326,	0.946},
	{20,	0.342,	0.940},
	{21,	0.358,	0.934},
	{22,	0.375,	0.927},
	{23,	0.391,	0.921},
	{24,	0.407,	0.914},
	{25,	0.423,	0.906},
	{26,	0.438,	0.899},
	{27,	0.454,	0.891},
	{28,	0.469,	0.883},
	{29,	0.485,	0.875},
	{30,	0.500,	0.866},
	{31,	0.515,	0.857},
	{32,	0.530,	0.848},
	{33,	0.545,	0.839},
	{34,	0.559,	0.829},
	{35,	0.574,	0.819},
	{36,	0.588,	0.809},
	{37,	0.602,	0.799},
	{38,	0.616,	0.788},
	{39,	0.629,	0.777},
	{40,	0.643,	0.766},
	{41,	0.656,	0.755},
	{42,	0.669,	0.743},
	{43,	0.682,	0.731},
	{44,	0.695,	0.719},
	{45,	0.707,	0.707},
	{46,	0.719,	0.695},
	{47,	0.731,	0.682},
	{48,	0.743,	0.669},
	{49,	0.755,	0.656},
	{50,	0.766,	0.643},
	{51,	0.777,	0.629},
	{52,	0.788,	0.616},
	{53,	0.799,	0.602},
	{54,	0.809,	0.588},
	{55,	0.819,	0.574},
	{56,	0.829,	0.559},
	{57,	0.839,	0.545},
	{58,	0.848,	0.530},
	{59,	0.857,	0.515},
	{60,	0.866,	0.500},
	{61,	0.875,	0.485},
	{62,	0.883,	0.469},
	{63,	0.891,	0.454},
	{64,	0.899,	0.438},
	{65,	0.906,	0.423},
	{66,	0.914,	0.407},
	{67,	0.921,	0.391},
	{68,	0.927,	0.375},
	{69,	0.934,	0.358},
	{70,	0.940,	0.342},
	{71,	0.946,	0.326},
	{72,	0.951,	0.309},
	{73,	0.956,	0.292},
	{74,	0.961,	0.276},
	{75,	0.966,	0.259},
	{76,	0.970,	0.242},
	{77,	0.974,	0.225},
	{78,	0.978,	0.208},
	{79,	0.982,	0.191},
	{80,	0.985,	0.174},
	{81,	0.988,	0.156},
	{82,	0.990,	0.139},
	{83,	0.993,	0.122},
	{84,	0.995,	0.105},
	{85,	0.998,	0.087},
	{86,	0.999,	0.070},
	{87,	0.999,	0.052},
	{88,	1.000,	0.035},
	{89,	1.000,	0.017},
	{90,	1.000,	0.000},
};

const int8_t SinCosSel[4][2] =
{
	{ISIN, ICOS},
	{ICOS, ISIN},
	{ISIN, ICOS},
	{ICOS, ISIN},
};

const int8_t SinCosMul[4][2] =
{
	{1, 1},
	{1, -1},
	{-1, -1},
	{-1, 1},
};

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Return the coordinates of a point on a circle.
 * \param org       x and y coordinate (org)
 * \param radius    raduis of the point on circle
 * \param angle     value of the angle (0-360 degre)
 *
 * \output  struct point updated with coord of the point.
 */

void point_on_circle (struct _point* org, uint16_t radius, uint16_t angle)
{
	uint8_t sector, angle90, v1, v2;
	float s, c;

	if (!angle) sector = 0;
	else sector = (abs)(angle/91);

	if (!sector) angle90 = angle;
	else angle90 = angle % ((sector*90)+1); ;

	v1 = SinCosSel[sector][0];
	v2 = SinCosSel[sector][1];

	s = SinCos[angle90][v1] * SinCosMul[sector][0];
	c = SinCos[angle90][v2] * SinCosMul[sector][1];

	org->x += radius * s ;
	org->y -= radius * c;
}


/**
 * \brief Return the coordinates of a point on a circle.
 * \param org       x and y coordinate (org)
 * \param pt        x and y coordinate (dest)
 * \param angle     increment of the angle (degre)
 * \param clockwise 0= clockwise, 1 = counterclockwise
 *
 * \output  struct point pt updated with coord of the point.
 */
void rotate_point (struct _point* org, struct _point* pt, uint16_t angle, uint8_t clockwise)
{
	float new_x, new_y, s, c;
	uint8_t sector, angle90, v1, v2;

	if (!angle) sector = 0;
	else sector = (abs)(angle/91);

	if (!sector) angle90 = angle;
	else angle90 = angle % ((sector*90)+1);

	v1 = SinCosSel[sector][0];
	v2 = SinCosSel[sector][1];

	s = SinCos[angle90][v1] * SinCosMul[sector][0];
	c = SinCos[angle90][v2] * SinCosMul[sector][1];

	// translate point back to origin
	pt->x -= org->x;
	pt->y -= org->y;
	// rotate point
	if (!clockwise)
	{
		new_x = pt->x * c + pt->y * s;
		new_y = -pt->x * s + pt->y * c;
	}
	else
	{
		new_x = pt->x * c - pt->y * s;
		new_y = pt->x * s + pt->y * c;
	}
	// translate point back:
	pt->x = (int32_t)(new_x + org->x);
	pt->y = (int32_t)(new_y + org->y) ;
}



void compute_vector_position (uint32_t* pX, uint32_t* pY, uint32_t radius, uint16_t degre)
{
  uint16_t  dx1, dy1;
  uint8_t   quadrant = degre/90;
  uint8_t   i = degre%90;

  switch (quadrant)
  {
    case 0:
      dx1 =  (uint16_t)(radius * SinCos[i][ISIN]);
      dy1 =  (uint16_t)(radius * SinCos[i][ICOS]);
      *pX += dx1;
      *pY -= dy1;
      break;
    case 1:
      dx1 =  (uint16_t)(radius * SinCos[i][ICOS]);
      dy1 =  (uint16_t)(radius * SinCos[i][ISIN]);
      *pX += dx1;
      *pY += dy1;
      break;
    case 2:
      dx1 =  (uint16_t)(radius * SinCos[i][ISIN]);
      dy1 =  (uint16_t)(radius * SinCos[i][ICOS]);
      *pX -= dx1;
      *pY += dy1;
      break;
    case 3:
      dx1 =  (uint16_t)(radius * SinCos[i][ICOS]);
      dy1 =  (uint16_t)(radius * SinCos[i][ISIN]);
      *pX -= dx1;
      *pY -= dy1;
      break;
    default: break;
  }
}

// Draws a part of a vector in a circle
// X = org X
// Y = org Y
// radius = size of the radius
// segment = part size of the radius
// degre = angle of the radius
// color = color of the radius

void widget_draw_vector (uint32_t X, uint32_t Y, uint32_t radius, uint8_t segment, uint16_t degre, uint32_t color)
{
  uint32_t  dx0, dy0;
  uint32_t  dx1, dy1;
  uint32_t color1;

  if (color==COLOR_WHITE) { color1 = COLOR_LIGHTGREY; }
  else { color1 = color; }

	dx0 = X; dy0 = Y;
	dx1 = X; dy1 = Y;

	compute_vector_position (&dx0, &dy0, radius-segment, degre);
	compute_vector_position (&dx1, &dy1, radius, degre);
	lcdd_draw_line(dx0+1, dy0, dx1+1, dy1, color1);
	lcdd_draw_line(dx0-1, dy0, dx1-1, dy1, color1);
	lcdd_draw_line(dx0, dy0, dx1, dy1, color);
}