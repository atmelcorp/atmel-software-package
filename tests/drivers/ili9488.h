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

/**
 * \file
 *
 * Interface of ILI9488 driver.
 *
 */

#ifndef _ILI9488_H_
#define _ILI9488_H_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"

#include "font.h" 
   
#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/* ILI9488 ID code */
#define ILI9488_DEVICE_CODE    0x2810
   
#define ILI9488_MXTX_WIDTH       320
#define ILI9488_MXTX_HEIGHT      480
   
/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

typedef uint32_t LcdColor_t ;

/*----------------------------------------------------------------------------
 *        
 *----------------------------------------------------------------------------*/

/** LCD index register address */
#define MXTX_CMD(x) (uint16_t)(x & 0x00FF)
/** LCD status register address */
#define MXTX_PARAM(x) (uint16_t)(x | 0x100)

#define BGR_MODE 0x08   // bit D3 Memory acces control (36h)
#define RGB_MODE 0x00

/*----------------------------------------------------------------------------
 *        
 *----------------------------------------------------------------------------*/

// Define display data direction command (DDD)   
typedef enum 
{
  DDD_NORMAL = 0,
  DDD_Y_MIRROR,
  DDD_X_MIRROR,
  DDD_XY_MIRROR,
  DDD_XY_EXCHANGE,
  DDD_XY_EXCHANGE_Y_MIRROR,
  DDD_XY_EXCHANGE_X_MIRROR,
  DDD_XY_EXCHANGE_XY_MIRROR,
} MXTX_DIRECTION_enum;   
   
typedef struct _point
{
  int32_t x;
  int32_t y;
  int32_t z;    
}sPoint, *psPoint;   

typedef struct _size
{
  uint32_t w;
  uint32_t h;
}sSize, *psSize;   


typedef struct _MXTX_param
{
  // CURSOR  
  uint32_t  cursor_x; 
  uint32_t  cursor_y ;
  // SCREEN
  uint32_t  scr_width;
  uint32_t  scr_height;
  uint32_t  scr_bgcolor;
  uint32_t  text_color;
  uint32_t  text_bgcolor;
  // FONT
  uint8_t   font_sel;
  uint8_t   max_lines;
  uint8_t   char_per_line;
  G_FONT    sgFont;
}MXTX_param, *pMXTX_param;


/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
   
extern MXTX_param* mxtx_get_pnt_struct (void);   
extern uint8_t mxtx_initialize (void);   
extern void mxtx_on ( void );   
extern void mxtx_off ( void );  
extern void mxtx_sleep_mode ( uint8_t is_sleep );

extern void mxtx_set_cursor (uint16_t x, uint16_t y);   
extern void mxtx_set_color ( uint32_t dwRgb24Bits );   
extern void mxtx_set_partial_window ( uint16_t Start, uint16_t End);   
extern void mxtx_set_window ( struct _point* Coord1, struct _size* Size );   
extern void mxtx_set_display_direction (MXTX_DIRECTION_enum direction, uint8_t BGR_mode);
extern void mxtx_clear_screen (void);
extern void mxtx_set_vertical_scroll_window ( uint16_t dwStartAdd, uint16_t dwHeight );   

extern void mxtx_set_font (uint8_t FontSize);
extern void mxtx_draw_char ( struct _point* Coord1, uint8_t c, uint32_t color );   
extern void mxtx_draw_string ( struct _point* Coord1, char* pString, uint32_t color ); 
extern void mxtx_get_string_size ( const char *pString, struct _size *pSize );

extern void mxtx_draw_picture( struct _point* Coord1, struct _point* Coord2, const LcdColor_t *pBuffer );   
extern void mxtx_draw_line ( struct _point* Coord1, struct _point* Coord2 );
extern void mxtx_draw_circle( struct _point* Coord1, uint32_t dwR );   
extern void mxtx_draw_circle_helper (struct _point* Coord1, uint32_t r, uint8_t corner);    
extern void mxtx_draw_filled_circle ( struct _point* Coord1, uint32_t dwRadius);   
extern void mxtx_fill_circle_helper (struct _point* Coord1, uint32_t r, uint8_t corner, uint32_t delta);    
extern void mxtx_draw_filled_rectangle (struct _point* Coord1, struct _point* Coord2);   
extern void mxtx_draw_rectangle (struct _point* Coord1, struct _point* Coord2);   
extern void mxtx_draw_rounded_rectangle (struct _point* Org, struct _size* Size, uint32_t r);   

extern void mxtx_draw_triangle (struct _point* Coord0, struct _point* Coord1, struct _point* Coord2 ); 
extern void mxtx_draw_filled_triangle ( struct _point* Coord0, struct _point* Coord1, struct _point* Coord2 );

extern void mxtx_set_backlight (uint8_t level);   


extern void mxtx_test_pattern (void);

#endif /* #ifndef ILI9488_H_ */
