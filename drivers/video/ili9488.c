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
 * Implementation of ILI9488 driver.
 * LCD board Atmel MaxTouch Xplained Pro
 * Interface SPI on EXT1 connector, using board SAMA5D4-XULT
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "board.h"
#include "chip.h"

#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/aic.h"
#include "peripherals/pwmc.h"
#include "peripherals/spi.h"
#include "peripherals/spid.h"

#include "video/ili9488.h"
#include "video/ili9488_reg.h"

#include "lcd_color.h"
#include "widget.h"

#include "timer.h"

#include "trace.h"
#include "compiler.h"


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*----------------------------------------------------------------------------
 *        Defines
 *----------------------------------------------------------------------------*/

#define BOARD_LCD_ILI9488

#define swap(a, b) { int16_t t = a; a = b; b = t; }

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

extern uint32_t dwTimeStamp ;

/** Pio pins to configure. */
static const struct _pin MXTX_Reset[] = MXTX_RESET_PIN;
static const struct _pin MXTX_Pwm[] = MXTX_BACKLIGHT_PIN;
static const struct _pin spi_pins[] = ILI9488_PINS;

/* Pixel cache used to speed up communication */
#define MXTX_DATA_CACHE_SIZE ILI9488_MXTX_WIDTH
static LcdColor_t gLcdPixelCache[MXTX_DATA_CACHE_SIZE];

// LCD parameters
static struct _mxtx_param sMXTX ;

#define pgm_read_byte(addr) (*(const unsigned char *)(addr))

static struct _spi_desc spi_ili9488_desc = {
	.addr           = ILI9488_ADDR,
	.bitrate        = ILI9488_FREQ,
	.attributes     = ILI9488_ATTRS,
	.dlybs          = ILI9488_DLYBS,
	.dlybct         = ILI9488_DLYCT,
	.chip_select    = ILI9488_CS,
	.spi_mode       = ILI9488_SPI_MODE,
	.transfert_mode = SPID_MODE_POLLING,
};

/*----------------------------------------------------------------------------
 *        Local low level functions
 *----------------------------------------------------------------------------*/

static void mxtx_send_cmd ( uint8_t reg );
static void mxtx_write_reg ( uint8_t data );
static void mxtx_write_reg16 ( uint16_t data );
static void mxtx_write_reg24 ( uint32_t data );
//static void mxtx_write_reg32 ( uint32_t data );
static uint8_t mxtx_read_reg ( uint8_t reg );
//static uint16_t mxtx_read_reg16 ( uint8_t reg );
static uint32_t mxtx_read_reg24 ( uint8_t reg );
//static uint32_t mxtx_read_reg32 ( uint8_t reg );
static void mxtx_nop (void);
static void mxtx_write_single ( LcdColor_t data );
static void mxtx_write_ram_buffer( const LcdColor_t *pBuf, uint32_t size );

//=============================================================================
/**
 * \brief Send Command to LCD.
 * \param reg   Command Register address.
 */
static void mxtx_send_cmd ( uint8_t reg )
{
	spi_write(spi_ili9488_desc.addr, spi_ili9488_desc.chip_select, MXTX_CMD(reg));
}

//=============================================================================
/**
 * \brief Write Parameter to LCD Register.
 * \param data  Data to be written.
 */
static void mxtx_write_reg ( uint8_t data )
{
	spi_write(spi_ili9488_desc.addr, spi_ili9488_desc.chip_select, MXTX_PARAM(data));
}

//=============================================================================
/**
 * \brief Write 16 bit Parameter to LCD Register.
 * \param data  Data to be written.
 */
static void mxtx_write_reg16( uint16_t data )
{
	spi_write(spi_ili9488_desc.addr, spi_ili9488_desc.chip_select, MXTX_PARAM(((data>>8) &0xFF)));
	mxtx_write_reg((uint8_t)data);
}

//=============================================================================
/**
 * \brief Write 24 bit Parameter to LCD Register.
 * \param data  Data to be written.
 */
static void mxtx_write_reg24 ( uint32_t data )
{
	spi_write(spi_ili9488_desc.addr, spi_ili9488_desc.chip_select, MXTX_PARAM(((data>>16) & 0xFF)));
	mxtx_write_reg16 ((uint16_t)data);
}

//=============================================================================
/**
 * \brief Write 32 bit Parameter to LCD Register.
 * \param data  Data to be written.
 */
#if 0
static void mxtx_write_reg32 ( uint32_t data )
{
	spi_write(spi_ili9488_desc.addr, spi_ili9488_desc.chip_select, MXTX_PARAM((data>>24) & 0xFF));
	mxtx_write_reg24(data);
}
#endif

//=============================================================================
/**
 * \brief Read data from LCD Register.
 * \param reg   Register address.
 * \return      Readed data.
 */
static uint8_t mxtx_read_reg ( uint8_t reg )
{
	uint16_t value;

	spi_write(spi_ili9488_desc.addr, spi_ili9488_desc.chip_select, MXTX_CMD(reg));
	while(spi_is_finished(spi_ili9488_desc.addr) !=1);
	spi_read(spi_ili9488_desc.addr, spi_ili9488_desc.chip_select);
	spi_write(spi_ili9488_desc.addr, spi_ili9488_desc.chip_select, MXTX_PARAM(0xFF));
	while(spi_is_finished(spi_ili9488_desc.addr) !=1);
	value = spi_read(spi_ili9488_desc.addr, spi_ili9488_desc.chip_select);
	mxtx_send_cmd(ILI9488_CMD_SPI_READ_SETTINGS);
	mxtx_write_reg(0);
	return (uint8_t)value;
}

//=============================================================================
/**
 * \brief Read data from LCD Register.
 * \param reg   Register address.
 * \return      Readed data.
 */
#if 0
static uint16_t mxtx_read_reg16 ( uint8_t reg )
{
	uint16_t value = 0;
	uint8_t SPI_CNT = 0x81;

	mxtx_send_cmd(ILI9488_CMD_SPI_READ_SETTINGS);
	mxtx_write_reg(SPI_CNT);
	value = (mxtx_read_reg(reg) << 8);
	SPI_CNT++;
	mxtx_send_cmd(ILI9488_CMD_SPI_READ_SETTINGS);
	mxtx_write_reg(SPI_CNT);
	value |= mxtx_read_reg(reg);
	mxtx_send_cmd(ILI9488_CMD_SPI_READ_SETTINGS);
	mxtx_write_reg(0);
	return value;
}
#endif
//=============================================================================
/**
 * \brief Read data from LCD Register.
 * \param reg   Register address.
 * \return      Readed data.
 */
static uint32_t mxtx_read_reg24 ( uint8_t reg )
{
	uint32_t value = 0;
	uint8_t SPI_CNT = 0x81;

	//Set LCD count to 0
	mxtx_send_cmd(ILI9488_CMD_SPI_READ_SETTINGS);
	mxtx_write_reg(SPI_CNT);
	// Send Command
	value = (mxtx_read_reg(reg) << 16);
	SPI_CNT++;
	mxtx_send_cmd(ILI9488_CMD_SPI_READ_SETTINGS);
	mxtx_write_reg(SPI_CNT);
	value |= (mxtx_read_reg(reg) << 8);
	SPI_CNT++;
	mxtx_send_cmd(ILI9488_CMD_SPI_READ_SETTINGS);
	mxtx_write_reg(SPI_CNT);
	value |= mxtx_read_reg(reg);
	mxtx_send_cmd(ILI9488_CMD_SPI_READ_SETTINGS);
	mxtx_write_reg(0);
	return value;
}

//=============================================================================
/**
 * \brief Read data from LCD Register.
 * \param reg   Register address.
 * \return      Readed data.
 */
#if 0
static uint32_t mxtx_read_reg32 ( uint8_t reg )
{
	uint32_t value;
	uint8_t SPI_CNT = 0x81;

	mxtx_send_cmd(ILI9488_CMD_SPI_READ_SETTINGS);
	mxtx_write_reg(SPI_CNT);
	value = mxtx_read_reg(reg) ;
	value  <<=  24;
	SPI_CNT++;
	mxtx_send_cmd(ILI9488_CMD_SPI_READ_SETTINGS);
	mxtx_write_reg(SPI_CNT);
	value |= (mxtx_read_reg(reg) << 16);
	SPI_CNT++;
	mxtx_send_cmd(ILI9488_CMD_SPI_READ_SETTINGS);
	mxtx_write_reg(SPI_CNT);
	value |= (mxtx_read_reg(reg) << 8);
	SPI_CNT++;
	mxtx_send_cmd(ILI9488_CMD_SPI_READ_SETTINGS);
	mxtx_write_reg(SPI_CNT);
	value |= mxtx_read_reg(reg);
	mxtx_send_cmd(ILI9488_CMD_SPI_READ_SETTINGS);
	mxtx_write_reg(0);
	return value;
}
#endif
//=============================================================================
static void mxtx_nop (void)
{
	mxtx_send_cmd(ILI9488_CMD_NOP);
}

//=============================================================================
/**
 * \brief Write data to LCD Register.
 * \param reg   Register address.
 * \param data  Data to be written.
 */
static void mxtx_write_single( LcdColor_t data )
{
	mxtx_send_cmd(ILI9488_CMD_MEMORY_WRITE);
	mxtx_write_reg24(data);
}

//=============================================================================
/**
 * \brief Write data to LCD Register.
 * \param reg   Register address.
 * \param data  Data to be written.
 */
static void mxtx_write_ram_buffer ( const LcdColor_t *pBuf, uint32_t size)
{
	uint32_t addr ;
	for ( addr = 0 ; addr < size ; addr++ )
		mxtx_write_reg24(pBuf[addr]);
}

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/


//=============================================================================
static void mxtx_init_interface (void)
{
	uint32_t mode;

	pio_configure(MXTX_Reset, ARRAY_SIZE(MXTX_Reset));
	pio_configure(spi_pins, ARRAY_SIZE(spi_pins));
	pio_configure(MXTX_Pwm, ARRAY_SIZE(MXTX_Pwm));

	/* Enable PWM peripheral clock */
	pmc_enable_peripheral(ID_PWM);

	/* Set clock A and clock B */
	mode = PWM_CLK_PREB(0x0A) | (PWM_CLK_DIVB(2)) | PWM_CLK_PREA(0x0A) | (PWM_CLK_DIVA(128));
	pwmc_configure_clocks(PWM, mode);

	/* Configure PWM channel for backlight  */
	pwmc_disable_channel(PWM, CHANNEL_PWM_LCD);
	mode = PWM_CMR_CPOL | PWM_CMR_CALG | PWM_CMR_CPRE_CLKB;
	pwmc_configure_channel(PWM, CHANNEL_PWM_LCD, mode);
	pwmc_set_period(PWM, CHANNEL_PWM_LCD, 20);
	pwmc_set_duty_cycle(PWM, CHANNEL_PWM_LCD, 10);
	pwmc_enable_channel(PWM, CHANNEL_PWM_LCD);

	spid_configure(&spi_ili9488_desc);

}

//=============================================================================
void mxtx_init_environment(void)
{
	sMXTX.cursor_x = 0;
	sMXTX.cursor_y = 0;
	sMXTX.scr_bgcolor = COLOR_WHITE;
	sMXTX.text_bgcolor = COLOR_WHITE;
	sMXTX.text_color = COLOR_WHITE;
	mxtx_set_font(FONT10x14);
}

//=============================================================================
/**
 * \brief Draw a LcdColor_t on LCD of given color.
 * \param x  X-coordinate of pixel.
 * \param y  Y-coordinate of pixel.
 */
void mxtx_draw_pixel(uint32_t x, uint32_t y)
{
	if( (x >= sMXTX.scr_width) || (y >= sMXTX.scr_height) ) return ;
	/* Set cursor */
	mxtx_set_cursor( x, y );
	/* Prepare to write in GRAM */
	mxtx_write_single( *gLcdPixelCache );
}

//=============================================================================
/**
 * \brief Check Box coordinates. Return upper left and bottom right coordinates.
 * \param pX1      X-coordinate of upper-left corner on LCD.
 * \param pY1      Y-coordinate of upper-left corner on LCD.
 * \param pX2      X-coordinate of lower-right corner on LCD.
 * \param pY2      Y-coordinate of lower-right corner on LCD.
 */
static void mxtx_check_box_coordinates ( struct _point* Coord1, struct _point* Coord2 )
{
	uint32_t dw;

	if ( Coord1->x >= (int32_t)sMXTX.scr_width ) Coord1->x = sMXTX.scr_width-1 ;
	if ( Coord2->x >= (int32_t)sMXTX.scr_width ) Coord2->x = sMXTX.scr_width-1 ;
	if ( Coord1->y >= (int32_t)sMXTX.scr_height) Coord1->y = sMXTX.scr_height-1 ;
	if ( Coord2->y >= (int32_t)sMXTX.scr_height) Coord2->y = sMXTX.scr_height-1 ;
	if (Coord1->x > Coord2->x)
	{
		dw = Coord1->x;
		Coord1->x = Coord2->x;
		Coord2->x = dw;
	}
	if (Coord1->y > Coord2->y)
	{
		dw = Coord1->y;
		Coord1->y = Coord2->y;
		Coord2->y = dw;
	}
}

//=============================================================================
/*
 * \brief Draw a line on LCD, which is not horizontal or vertical.
 * \param x         X-coordinate of line start.
 * \param y         Y-coordinate of line start.
 */

void mxtx_draw_line_bresenham (struct _point* Coord1, struct _point* Coord2)
{
	int dx = abs(Coord2->x - Coord1->x);
	int dy = abs(Coord2->y - Coord1->y);
	int sx = (Coord1->x < Coord2->x) ? 1 : -1;
	int sy = (Coord1->y < Coord2->y) ? 1 : -1;
	int err = dx - dy;
	int e2 ;

	while (1)
	{
		mxtx_draw_pixel(Coord1->x, Coord1->y);

		if ((Coord1->x == Coord2->x) && (Coord1->y == Coord2->y))
			break;
		e2 = 2 * err;
		if (e2 > -dy)
		{ err -= dy; Coord1->x += sx; }
		if (e2 < dx)
		{ err += dx; Coord1->y += sy; }
	}
}

//=============================================================================
void mxtx_draw_fast_vertical_line(struct _point* Coord, uint32_t h)
{
	struct _point Dest =
		{
			.x = Coord->x,
			.y = Coord->y + h-1,
		};
	mxtx_draw_line(Coord, &Dest);
}

//=============================================================================
void mxtx_draw_fast_horizontal_line(struct _point* Coord, uint32_t w)
{
	struct _point Dest =
		{
			.x = Coord->x+w-1,
			.y = Coord->y,
		};
	mxtx_draw_line(Coord, &Dest);
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

struct _mxtx_param* mxtx_get_pnt_struct (void)
{
	return &sMXTX;
}
//=============================================================================

/**
 * \internal
 * \brief Reset the display using the digital control interface
 *
 * Controls the reset pin of the display controller to reset the display.
 */
static void mxtx_reset_display (void)
{
	pio_set(MXTX_Reset);
	timer_wait(10);
	pio_clear(MXTX_Reset);
	timer_wait(10);
	pio_set(MXTX_Reset);
	timer_wait(150);
}

//=============================================================================

#define NB_GAMMA        15
const uint8_t Positive_Gamma_1[NB_GAMMA] = {
	0x00, 0x07, 0x0F, 0x0D, 0x1B, 0x0A, 0x3c, 0x78, 0x4A, 0x07, 0x0E, 0x09, 0x1B, 0x1E, 0x0F
};
const uint8_t Positive_Gamma_2[NB_GAMMA] = {
	0x00, 0x06, 0x06, 0x08, 0x18, 0x0C, 0x41, 0x9B, 0x4F, 0x07, 0x0E, 0x0C, 0x1C, 0x1C, 0x0F
};

const uint8_t Negative_Gamma_1[NB_GAMMA] = {
	0x00, 0x22, 0x24, 0x06, 0x12, 0x07, 0x36, 0x47, 0x47, 0x06, 0x0A, 0x07, 0x30, 0x37, 0x0F
};
const uint8_t Negative_Gamma_2[NB_GAMMA] = {
	0x00, 0x1B, 0x1E, 0x03, 0x0E, 0x04, 0x35, 0x24, 0x49, 0x04, 0x0F, 0x0E, 0x37, 0x3A, 0x0F
};


/**
 * \brief Initialize the LCD controller.
 */
uint8_t mxtx_initialize (void)
{
	uint8_t i;
	uint32_t chipid;

	// Init PIOs, PWM and SPI interface
	mxtx_init_interface();
	// Init structure used with driver
	mxtx_init_environment();
	// Reset display with PIO pin control
	mxtx_reset_display();

	// Check ILI9488 chipid
	chipid = mxtx_read_reg24(ILI9488_CMD_READ_ID4);
	if (chipid != ILI9488_DEVICE_CODE)
	{
		printf("Read ILI9488 chip ID (0x%04x) error, skip initialization.\r\n",
		       (unsigned int)chipid);
		return 1;
	}

//    mxtx_send_cmd(ILI9488_CMD_NORMAL_DISP_MODE_ON);


	// PGAMCTRL - Positive Gamma Control
	mxtx_send_cmd(ILI9488_CMD_POSITIVE_GAMMA_CORRECTION);
	for (i=0; i<NB_GAMMA; i++)
		mxtx_write_reg(Positive_Gamma_1[i]);
	// NGAMCTRL - Negative Gamma Control
	mxtx_send_cmd(ILI9488_CMD_NEGATIVE_GAMMA_CORRECTION);
	for (i=0; i<NB_GAMMA; i++)
		mxtx_write_reg(Negative_Gamma_1[i]);


	// Power Control 1
	mxtx_send_cmd(ILI9488_CMD_POWER_CONTROL_1);
	mxtx_write_reg(0x10);
	mxtx_write_reg(0x10);
	// Power Control 2
	mxtx_send_cmd(ILI9488_CMD_POWER_CONTROL_2);
	mxtx_write_reg(0x43);
	// VCOM Control
	mxtx_send_cmd(ILI9488_CMD_VCOM_CONTROL_1);
	mxtx_write_reg(0x00);
	mxtx_write_reg(0x22);
	mxtx_write_reg(0x80);
	// Memory Access Control
	mxtx_send_cmd(ILI9488_CMD_MEMORY_ACCESS_CONTROL);
	mxtx_write_reg(0x68);
	//Interface Mode Control
	// Set up used SPI lines and RGB interface
	mxtx_send_cmd(ILI9488_CMD_INTERFACE_MODE_CONTROL);
	mxtx_write_reg(0x00);
	//Frame rate 70HZ
	mxtx_send_cmd(ILI9488_CMD_FRAME_RATE_CONTROL_NORMAL);
	mxtx_write_reg(0xB0);
	mxtx_write_reg(0x11);
	// Display Inversion
	mxtx_send_cmd(ILI9488_CMD_DISPLAY_INVERSION_CONTROL);
	mxtx_write_reg(0x02);
	// Entry Set Mode
	mxtx_send_cmd(ILI9488_CMD_ENTRY_MODE_SET);
	mxtx_write_reg(0xC6);
	// Interface Pixel Format
//    mxtx_send_cmd(ILI9488_CMD_INTERFACE_PIXEL_FORMAT);
//    mxtx_write_reg(0x66);// DPI: 18bpp  DBI: 18bpp
	// Set Image Function
	mxtx_send_cmd(ILI9488_CMD_SET_IMAGE_FUNCTION);
	mxtx_write_reg(0x00);
	// Adjustment Control 3
	// fixed settings and DSI packet setup
	mxtx_send_cmd(ILI9488_CMD_ADJUST_CONTROL_3);
	mxtx_write_reg(0xA9);
	mxtx_write_reg(0x51);
	mxtx_write_reg(0x2C);
	mxtx_write_reg(0x82);
	// Set Interface Mode
	mxtx_send_cmd(ILI9488_CMD_DISPLAY_FUNCTION_CONTROL);
	mxtx_write_reg(0x00);// RGB or other interface
	mxtx_write_reg(0x22);
	mxtx_write_reg(0x3B);


	// Set display direction and color mode
	mxtx_set_display_direction(DDD_NORMAL, BGR_MODE);
	// Set display window
	struct _point Point =
		{
			.x = 0,
			.y = 0,
		};
	struct _size Size =
		{
			.w = sMXTX.scr_width,
			.h = sMXTX.scr_height,
		};
	mxtx_set_window(&Point, &Size) ;
	// Set backlight
	mxtx_send_cmd(ILI9488_CMD_WRITE_DISPLAY_BRIGHTNESS);
	mxtx_write_reg(0xF0);
	// Sleep out
	mxtx_sleep_mode(0);

	return 0 ;
}

//=============================================================================

void mxtx_set_cursor (uint16_t x, uint16_t y)
{
	/* Set Horizontal Address Start Position */
	mxtx_send_cmd(ILI9488_CMD_COLUMN_ADDRESS_SET);
	mxtx_write_reg16(x);
	mxtx_write_reg16(ILI9488_MXTX_WIDTH);
	mxtx_nop();
	/* Set Horizontal Address End Position */
	mxtx_send_cmd(ILI9488_CMD_PAGE_ADDRESS_SET);
	mxtx_write_reg16(y);
	mxtx_write_reg16(ILI9488_MXTX_HEIGHT);
	mxtx_nop();
}

//=============================================================================
/**
 * \brief Turn on the LCD.
 */
void mxtx_on ( void )
{
	mxtx_send_cmd(ILI9488_CMD_PIXEL_OFF);
	mxtx_send_cmd(ILI9488_CMD_DISPLAY_ON);
	mxtx_send_cmd(ILI9488_CMD_NORMAL_DISP_MODE_ON);
}

//=============================================================================
/**
 * \brief Turn off the LCD.
 */
void mxtx_off ( void )
{
	mxtx_send_cmd(ILI9488_CMD_DISPLAY_OFF);
	mxtx_send_cmd(ILI9488_CMD_DISPLAY_OFF);
}

//=============================================================================
void mxtx_sleep_mode ( uint8_t is_sleep )
{
	if(is_sleep==1)
	{
		//Sleep In
		mxtx_send_cmd(ILI9488_CMD_DISPLAY_OFF);
		timer_wait(120);
		mxtx_send_cmd(ILI9488_CMD_ENTER_SLEEP_MODE);
		timer_wait(120);
	}
	else
	{
		//Sleep Out
		mxtx_send_cmd(ILI9488_CMD_SLEEP_OUT);
		timer_wait(150);
		mxtx_send_cmd(ILI9488_CMD_DISPLAY_ON);
	}
}

//=============================================================================
/**
 * \brief Convert 24 bit RGB color into 6-6-6 rgb color space.
 * Initialize the LcdColor_t cache with the color pattern.
 * \param x  24-bits RGB color.
 */
void mxtx_set_color ( uint32_t dwRgb24Bits )
{
	uint32_t i ;
	/* Fill the cache with selected color */
	for ( i = 0 ; i < MXTX_DATA_CACHE_SIZE ; ++i )
	{
		gLcdPixelCache[i] = dwRgb24Bits ;
	}
}

//=============================================================================
/**
 * \brief Set a partial display window
 * Initialize a partial window on LCD
 * \param Start Starting address of window.
 * \param End  End address of window.
 * \return 0 for successfull operation.
 */
void mxtx_set_partial_window( uint16_t Start, uint16_t End)
{
	mxtx_send_cmd(ILI9488_CMD_POWER_CONTROL_PARTIAL_5);
	mxtx_write_reg(0x44 ) ;
	mxtx_send_cmd(ILI9488_CMD_PARTIAL_AREA);
	mxtx_write_reg16(Start ) ;
	mxtx_write_reg16(End)  ;
	mxtx_send_cmd(ILI9488_CMD_PARTIAL_MODE_ON);
	timer_wait(10);
}

//=============================================================================
/**
 * \brief Helper function to send the drawing limits (boundaries) to the display
 *
 * This function is used to send the currently set upper-left and lower-right
 * drawing limits to the display, as set through the various limit functions.
 *
 */

void mxtx_set_window ( struct _point* Coord, struct _size* Size )
{
	if ( (Size->w > sMXTX.scr_width) || (Size->h > sMXTX.scr_height) )
	{
		printf("\n\rWindow too large\n\r");
		assert(1);
	}

	if (  ( (int32_t)Size->w < Coord->x) || ( (int32_t)Size->h < Coord->y) )
	{
		printf("\n\rWindow's hight or width is not large enough\n\r");
		assert(1);
	}
	/* Set Horizontal Address Start Position */
	mxtx_send_cmd(ILI9488_CMD_COLUMN_ADDRESS_SET);
	mxtx_write_reg16((uint16_t)Coord->x);
	mxtx_write_reg16((uint16_t)Size->w);
	mxtx_nop();
	/* Set Horizontal Address End Position */
	mxtx_send_cmd(ILI9488_CMD_PAGE_ADDRESS_SET);
	mxtx_write_reg16((uint16_t)Coord->y);
	mxtx_write_reg16((uint16_t)Size->h);
	mxtx_nop();
}

//=============================================================================

// LCD_MODE_08  portrait                x0 = top right          y0 = top right
// LCD_MODE_18  portrait    mirror      x0 = top right          y0 = top right
// LCD_MODE_28  landscape               x0 = top right          y0 = top right
// LCD_MODE_48  portrait                x0 = top left           y0 = top left
// LCD_MODE_68  landscape   mirror      x0 = top left           y0 = top left
// LCD_MODE_88  landscape   mirror      x0 = bottom left        y0 = bottom left
// LCD_MODE_A8  landscape               x0 = bottom right       y0 = bottom right
// LCD_MODE_C8  landscape   mirror      x0 = bottom left        y0 = bottom left
// LCD_MODE_E8  portrait                x0 = bottom left        y0 = bottom left

void mxtx_set_display_direction (enum _mxtx_direction direction, uint8_t BGR_mode)
{
	uint8_t mode = 0;
	switch (direction)
	{
	case DDD_NORMAL:
		mode = 0x00;
		sMXTX.scr_height = MXTX_LCD_HEIGHT;
		sMXTX.scr_width = MXTX_LCD_WIDTH;
		break;
	case DDD_Y_MIRROR:
		mode = 0x20;
		sMXTX.scr_height = MXTX_LCD_WIDTH ;
		sMXTX.scr_width = MXTX_LCD_HEIGHT;
		break;
	case DDD_X_MIRROR:
		mode = 0x40;
		sMXTX.scr_height = MXTX_LCD_HEIGHT;
		sMXTX.scr_width = MXTX_LCD_WIDTH;
		break;
	case DDD_XY_MIRROR:
		mode = 0x60;
		sMXTX.scr_height = MXTX_LCD_WIDTH ;
		sMXTX.scr_width = MXTX_LCD_HEIGHT;
		break;
	case DDD_XY_EXCHANGE:
		mode = 0x80;
		sMXTX.scr_height = MXTX_LCD_HEIGHT;
		sMXTX.scr_width = MXTX_LCD_WIDTH;
		break;
	case DDD_XY_EXCHANGE_Y_MIRROR:
		mode = 0xA0;
		sMXTX.scr_height = MXTX_LCD_WIDTH ;
		sMXTX.scr_width = MXTX_LCD_HEIGHT;
		break;
	case DDD_XY_EXCHANGE_X_MIRROR:
		mode = 0xC0;
		sMXTX.scr_height = MXTX_LCD_HEIGHT;
		sMXTX.scr_width = MXTX_LCD_WIDTH;
		break;
	case DDD_XY_EXCHANGE_XY_MIRROR:
		mode = 0xE0;
		sMXTX.scr_height = MXTX_LCD_WIDTH ;
		sMXTX.scr_width = MXTX_LCD_HEIGHT;
		break;
	}
	mode |= BGR_mode;
	mxtx_send_cmd(ILI9488_CMD_MEMORY_ACCESS_CONTROL);
	mxtx_write_reg(mode);
	struct _point Point =
		{
			.x = 0,
			.y = 0,
		};
	struct _size Size =
		{
			.w = sMXTX.scr_width,
			.h = sMXTX.scr_height,
		};
	mxtx_set_window( &Point, &Size ) ;
}

//=============================================================================
void mxtx_clear_screen (void)
{
	mxtx_set_color(sMXTX.scr_bgcolor);
	struct _point Pt1 =
		{
			.x = 0,
			.y = 0,
		};
	struct _point Pt2 =
		{
			.x = sMXTX.scr_width,
			.y = sMXTX.scr_height,
		};
	mxtx_draw_filled_rectangle(&Pt1, &Pt2);
}

//=============================================================================
void mxtx_set_vertical_scroll_window ( uint16_t dwStartAdd, uint16_t dwHeight )
{
	mxtx_send_cmd(ILI9488_CMD_VERT_SCROLL_DEFINITION);
	mxtx_write_reg16(dwStartAdd-1);
	mxtx_write_reg16(dwStartAdd);
	mxtx_write_reg16((dwStartAdd + dwHeight + 1));
}

//=============================================================================
// TEXTE
//=============================================================================

void mxtx_set_font (uint8_t FontSel)
{
	sMXTX.font_sel = FontSel;
	sMXTX.max_lines = sMXTX.scr_height / sGFont[FontSel].height;
	sMXTX.char_per_line = sMXTX.scr_width / sGFont[FontSel].width;
}

//=============================================================================

void mxtx_draw_char ( struct _point* Coord, uint8_t c, uint32_t color )
{
	uint32_t row, col ;
	uint8_t Ch;
	uint8_t width = sGFont[sMXTX.font_sel].width ;
	uint8_t height = sGFont[sMXTX.font_sel].height;
	uint8_t* pfont = (uint8_t*)sGFont[sMXTX.font_sel].pfont;

	assert( (c >= 0x20) && (c <= 0x7F) ) ;
	mxtx_set_color(color);

	switch (sMXTX.font_sel)
	{
	case FONT10x14:
		for (col=0 ; col < width ; col++ )
		{
			for (row=0 ; row<8 ; row++ )
			{
				Ch = (pfont[((c - 0x20) * 20) + col * 2] >> (7 - row)) & 0x1;
				if (Ch) mxtx_draw_pixel( Coord->x+col, Coord->y+row) ;
			}
			for (row=0; row<6; row++ )
			{
				Ch = (pfont[((c - 0x20) * 20) + col * 2 + 1] >> (7 - row)) & 0x1;
				if (Ch) mxtx_draw_pixel( Coord->x+col, Coord->y+row+8) ;
			}
		}
		break;

	case FONT10x8:
		for (col=0 ; col < width ; col++ )
		{
			Ch = pfont[((c-0x20)*width)+ col];
			if (Ch)
			{
				for (row=0 ; row < height; row++ )
				{
					if ((Ch>>row)&0x1)
					{
						mxtx_draw_pixel( Coord->x+(height-row), Coord->y+col) ;
					}
				}
			}
		}
		break;

	case FONT8x8:
	case FONT6x8:
		for (col=0 ; col < width ; col++ )
		{
			Ch = pfont[((c-0x20)*width)+ col];
			if (Ch)
			{
				for (row=0 ; row < height; row++ )
				{
					if ((Ch>>row)&0x1)
					{
						if (sMXTX.font_sel == FONT8x8)
							mxtx_draw_pixel( Coord->x+row, Coord->y+col) ;
						else
							mxtx_draw_pixel( Coord->x+col, Coord->y+row) ;
					}
				}
			}
		}
		break;
	}
}

//=============================================================================
void mxtx_draw_string(struct _point* Coord, const char* pString, uint32_t color)
{
	uint32_t xorg = Coord->x;
	uint32_t w = sGFont[sMXTX.font_sel].width;

	while (*pString)
	{
		if (*pString == '\n')
		{
			Coord->y += sGFont[sMXTX.font_sel].height + 2;
			Coord->x = xorg;
		}
		else
		{
			mxtx_draw_char (Coord, *pString, color);
			if (*pString==0x20) Coord->x += w/2;
			else Coord->x += w + sGFont[sMXTX.font_sel].char_space;
		}
		pString ++;
	}
}

//=============================================================================
/**
 * \brief Returns the width & height in pixels that a string will occupy on the screen
 * if drawn using lcdd_draw_string.
 *
 * \param pString  String.
 * \param pSize    Pointer for storing the string width and height.
 *
 * \return String width/height in pixels.
 */
void mxtx_get_string_size(const char *pString, struct _size *pSize)
{
	uint32_t width = sGFont[sMXTX.font_sel].width;
	uint32_t height = sGFont[sMXTX.font_sel].height;
	uint8_t space = sGFont[sMXTX.font_sel].char_space;

	while (*pString)
	{
		if (*pString == '\n') pSize->h += height;
		else                  pSize->w += width + space;
		pString ++;
	}
	if (width > 0) width -= 2;

	pSize->w  = width;
	pSize->h = height;
}

//=============================================================================
/**
 * \brief Write several pixels pre-formatted in a bufer to LCD GRAM.
 * \param dwX1      X-coordinate of upper-left corner on LCD.
 * \param dwY1      Y-coordinate of upper-left corner on LCD.
 * \param dwX2      X-coordinate of lower-right corner on LCD.
 * \param dwY2      Y-coordinate of lower-right corner on LCD.
 * \param pBuffer   LcdColor_t buffer area.
 */

#define IRAM_ADDR       (0x00200000u) /**< Internal RAM base address */
#define IRAM_SIZE       (0x20000u)

void mxtx_draw_picture (struct _point* Coord1, struct _point* Coord2, const LcdColor_t *pBuffer )
{
	uint32_t size, blocks;
	LcdColor_t currentColor;

	/* Swap coordinates if necessary */
	mxtx_check_box_coordinates(Coord1, Coord2);
	/* Determine the refresh window area */
	/* Horizontal and Vertical RAM Address Position (R50h, R51h, R52h, R53h) */
	mxtx_set_window(Coord1, (struct _size*)Coord2);
	/* Prepare to write in GRAM */
	mxtx_send_cmd(ILI9488_CMD_MEMORY_WRITE);

	//    size = (dwX2 - dwX1 + 1) * (dwY2 - dwY1 + 1);
	size = (Coord2->x - Coord1->x + 1) * (Coord2->y - Coord1->y + 1);

	/* Check if the buffer is within the SRAM */
	if ((IRAM_ADDR <= (uint32_t)pBuffer) && ((uint32_t)pBuffer < (IRAM_ADDR+IRAM_SIZE)))
	{
		mxtx_write_ram_buffer(pBuffer, size);
	}
	/* If the buffer is not in SRAM, transfer it in SRAM first before transfer */
	else
	{
		/* Use color buffer as a cache */
		currentColor = gLcdPixelCache[0];
		/* Send pixels blocks => one LCD IT / block */
		blocks = size / MXTX_DATA_CACHE_SIZE;
		while (blocks--)
		{
			memcpy(gLcdPixelCache, pBuffer, MXTX_DATA_CACHE_SIZE * sizeof(LcdColor_t));
			mxtx_write_ram_buffer(gLcdPixelCache, MXTX_DATA_CACHE_SIZE);
			pBuffer += MXTX_DATA_CACHE_SIZE;
		}
		/* Send remaining pixels */
		memcpy(gLcdPixelCache, pBuffer, (size % MXTX_DATA_CACHE_SIZE) * sizeof(LcdColor_t));
		mxtx_write_ram_buffer(gLcdPixelCache, size % MXTX_DATA_CACHE_SIZE);

		/* Restore the color cache */
		mxtx_set_color(currentColor);
	}
}


//=============================================================================
/*
 *
 *
 */
void mxtx_draw_bitmap(struct _point* Coord1, struct _size* Size,
		      const uint8_t *bitmap)
{
	uint16_t i, j;
	uint16_t byteWidth = (Size->w + 7) / 8;

	for(j=0; j<Size->h; j++)
	{
		for(i=0; i<Size->w; i++ )
		{
			if( pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7)) )
			{
				mxtx_draw_pixel(Coord1->x+i, Coord1->y+j);
			}
		}
	}
}

/* Draw a 1-bit color bitmap at the specified x, y position from the
 * provided bitmap buffer (must be PROGMEM memory) using color as the
 * foreground color and bg as the background color.
 */
void mxtx_draw_1bit_color_bitmap(struct _point* Coord1, struct _size* Size,
				 const uint8_t *bitmap)
{
	uint16_t i, j;
	uint16_t byteWidth = (Size->w + 7) / 8;

	for(j=0; j<Size->h; j++)
	{
		for(i=0; i<Size->w; i++ )
		{
			if( pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7)) )
			{
				// use foreground color
				mxtx_draw_pixel(Coord1->x+i, Coord1->y+j);
			}
			else
			{
				// use backgroung color
				mxtx_draw_pixel(Coord1->x+i, Coord1->y+j);
			}
		}
	}
}

/*
 * Draw XBitMap Files (*.xbm), exported from GIMP,
 * Usage: Export from GIMP to *.xbm, rename *.xbm to *.c and open in editor.
 * C Array can be directly used with this function
 */
void mxtx_draw_xbm_bitmap(struct _point* Coord1, struct _size* Size, const uint8_t *bitmap)
{
	uint16_t i, j;
	uint16_t byteWidth = (Size->w + 7) / 8;

	for(j=0; j<Size->h; j++)
	{
		for(i=0; i<Size->w; i++ )
		{
			if(pgm_read_byte(bitmap + j * byteWidth + i / 8) & (1 << (i % 8)))
			{
				mxtx_draw_pixel(Coord1->x+i, Coord1->y+j);
			}
		}
	}
}

//=============================================================================
/*
 * \brief Draw a line on LCD, horizontal and vertical line are supported.
 * \param dwX1      X-coordinate of line start.
 * \param dwY1      Y-coordinate of line start.
 * \param dwX2      X-coordinate of line end.
 * \param dwY2      Y-coordinate of line end.
 */
void mxtx_draw_line (struct _point* Coord1, struct _point* Coord2)
{
	/* Optimize horizontal or vertical line drawing */
	if (( Coord1->y == Coord2->y ) || (Coord1->x == Coord2->x))
		mxtx_draw_filled_rectangle(Coord1, Coord2);
	else
		mxtx_draw_line_bresenham(Coord1, Coord2) ;
}

//=============================================================================
/**
 * \brief Draws a circle on LCD, at the given coordinates.
 * \param dwX      X-coordinate of circle center.
 * \param dwY      Y-coordinate of circle center.
 * \param dwR      circle radius.
 */
void mxtx_draw_circle (struct _point* Coord1, uint32_t dwR )
{
	int32_t   d;    /* Decision Variable */
	uint32_t  curX; /* Current X Value */
	uint32_t  curY; /* Current Y Value */
	uint32_t  dwX = Coord1->x;
	uint32_t  dwY = Coord1->y;

	if (dwR == 0) return ;
	d = 3 - (dwR << 1);
	curX = 0;
	curY = dwR;

	while (curX <= curY)
	{
		mxtx_draw_pixel(dwX + curX, dwY + curY);
		mxtx_draw_pixel(dwX + curX, dwY - curY);
		mxtx_draw_pixel(dwX - curX, dwY + curY);
		mxtx_draw_pixel(dwX - curX, dwY - curY);
		mxtx_draw_pixel(dwX + curY, dwY + curX);
		mxtx_draw_pixel(dwX + curY, dwY - curX);
		mxtx_draw_pixel(dwX - curY, dwY + curX);
		mxtx_draw_pixel(dwX - curY, dwY - curX);

		if (d < 0) d += (curX << 2) + 6;
		else
		{
			d += ((curX - curY) << 2) + 10;
			curY--;
		}
		curX++;
	}
}

//=============================================================================
void mxtx_draw_circleHelper(struct _point* Coord1, uint32_t r, uint8_t corner)
{
	int32_t f = 1 - r;
	int32_t ddF_x = 1;
	int32_t ddF_y = -2 * (int32_t)r;
	int32_t x = 0;
	int32_t y = r;
	uint32_t  dwX = Coord1->x;
	uint32_t  dwY = Coord1->y;

	while (x<y)
	{
		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f+= ddF_y;
		}
		x++;
		ddF_x += 2;
		f     += ddF_x;
		if (corner & 0x4)
		{
			mxtx_draw_pixel(dwX + x, dwY + y);
			mxtx_draw_pixel(dwX + y, dwY + x);
		}
		if (corner & 0x2)
		{
			mxtx_draw_pixel(dwX + x, dwY - y);
			mxtx_draw_pixel(dwX + y, dwY - x);
		}
		if (corner & 0x8)
		{
			mxtx_draw_pixel(dwX - y, dwY + x);
			mxtx_draw_pixel(dwX - x, dwY + y);
		}
		if (corner & 0x01)
		{
			mxtx_draw_pixel(dwX - y, dwY - x);
			mxtx_draw_pixel(dwX - x, dwY - y);
		}
	}
}

//=============================================================================
void mxtx_draw_filled_circle(struct _point* Coord1, uint32_t dwRadius)
{
	signed int d ; /* Decision Variable */
	uint32_t dwCurX ; /* Current X Value */
	uint32_t dwCurY ; /* Current Y Value */
	uint32_t dwXmin, dwYmin;

	uint32_t  dwX = Coord1->x;
	uint32_t  dwY = Coord1->y;
	struct _point Pt1, Pt2;

	if (dwRadius == 0) return ;
	d = 3 - (dwRadius << 1) ;
	dwCurX = 0 ;
	dwCurY = dwRadius ;

	while ( dwCurX <= dwCurY )
	{
		dwXmin = (dwCurX > dwX) ? 0 : dwX-dwCurX;
		dwYmin = (dwCurY > dwY) ? 0 : dwY-dwCurY;
		Pt1.x = dwXmin;
		Pt1.y = dwYmin;
		Pt2.x = dwX+dwCurX;
		Pt2.y = dwYmin;
		if( (Pt1.x!=Pt2.x) || (Pt1.y!=Pt2.y))
			mxtx_draw_filled_rectangle(&Pt1, &Pt2); // dwXmin, dwYmin, dwX+dwCurX, dwYmin ) ;
		Pt1.x = dwXmin;
		Pt1.y = dwY+dwCurY;
		Pt2.x = dwX+dwCurX;
		Pt2.y = dwY+dwCurY;
		if( (Pt1.x!=Pt2.x) || (Pt1.y!=Pt2.y))
			mxtx_draw_filled_rectangle(&Pt1, &Pt2); //  dwXmin, dwY+dwCurY, dwX+dwCurX, dwY+dwCurY ) ;
		dwXmin = (dwCurY > dwX) ? 0 : dwX-dwCurY;
		dwYmin = (dwCurX > dwY) ? 0 : dwY-dwCurX;
		Pt1.x = dwXmin;
		Pt1.y = dwYmin;
		Pt2.x = dwX+dwCurY;
		Pt2.y = dwYmin;
		if( (Pt1.x!=Pt2.x) || (Pt1.y!=Pt2.y))
			mxtx_draw_filled_rectangle(&Pt1, &Pt2); // dwXmin, dwYmin, dwX+dwCurY, dwYmin ) ;
		Pt1.x = dwXmin;
		Pt1.y = dwY+dwCurX;
		Pt2.x = dwX+dwCurY;
		Pt2.y = dwY+dwCurX;
		if( (Pt1.x!=Pt2.x) || (Pt1.y!=Pt2.y))
			mxtx_draw_filled_rectangle(&Pt1, &Pt2); // dwXmin, dwY+dwCurX, dwX+dwCurY, dwY+dwCurX ) ;
		if ( d < 0 )
			d += (dwCurX << 2) + 6 ;
		else
		{
			d += ((dwCurX - dwCurY) << 2) + 10;
			dwCurY-- ;
		}
		dwCurX++ ;
	}
}

//=============================================================================
// Used to do circles and roundrects
void mxtx_draw_filled_circle_helper(struct _point* Coord1, uint32_t r, uint8_t corner, uint32_t delta)
{
	int32_t f = 1 - r;
	int32_t ddF_x = 1;
	int32_t ddF_y = -2 * (int32_t)r;
	int32_t x = 0;
	int32_t y = r;
	struct _point Pt1, Pt2;

	while (x<y)
	{
		if (f >= 0)
		{
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		if (corner & 0x1)
		{
			Pt1.x = Coord1->x+x;
			Pt1.y = Coord1->y-y;
			Pt2.x = Coord1->x+x;
			Pt2.y = 2*y+1+delta;
			mxtx_draw_line(&Pt1, &Pt2); //dwX1+x, dwY1-y, dwX1+x, 2*y+1+delta);
			Pt1.y = Coord1->y-x;
			Pt2.y = 2*x+1+delta;
			mxtx_draw_line(&Pt1, &Pt2); //dwX1+x, dwY1-x, dwX1+x, 2*x+1+delta);
		}
		if (corner & 0x2)
		{
			Pt1.x = Coord1->x-x;
			Pt1.y = Coord1->y-y;
			Pt2.x = Coord1->x-x;
			Pt2.y = 2*y+1+delta;
			mxtx_draw_line(&Pt1, &Pt2); //dwX1-x, dwY1-y, dwX1-x, 2*y+1+delta);
			Pt1.x = Coord1->x-y;
			Pt1.y = Coord1->y-x;
			Pt2.x = Coord1->x-y;
			Pt2.y = 2*x+1+delta;
			mxtx_draw_line(&Pt1, &Pt2); //dwX1-y, dwY1-x, dwX1-y, 2*x+1+delta);
		}
	}
}

//=============================================================================
/**
 * \brief Write several pixels with the same color to LCD GRAM.
 * LcdColor_t color is set by the mxtx_set_color() function.
 * This function is optimized using an sram buffer to transfer block instead of
 * individual pixels in order to limit the number of LCD acces.
 * \param dwX1      X-coordinate of upper-left corner on LCD.
 * \param dwY1      Y-coordinate of upper-left corner on LCD.
 * \param dwX2      X-coordinate of lower-right corner on LCD.
 * \param dwY2      Y-coordinate of lower-right corner on LCD.
 */
void mxtx_draw_filled_rectangle(struct _point* Coord1, struct _point* Coord2)
{
	uint32_t size, blocks;

	/* Swap coordinates if necessary */
	mxtx_check_box_coordinates(Coord1, Coord2);
	/* Determine the refresh window area */
	mxtx_set_window(Coord1, (struct _size*)Coord2);
	size = (Coord2->x - Coord1->x + 1) * (Coord2->y - Coord1->y + 1);
	/* Send pixels blocks => one LCD IT / block */
	blocks = size / MXTX_DATA_CACHE_SIZE;
	mxtx_send_cmd(ILI9488_CMD_MEMORY_WRITE);
	while (blocks--)
	{
		mxtx_write_ram_buffer(gLcdPixelCache, MXTX_DATA_CACHE_SIZE);
	}
	/* Send remaining pixels */
	mxtx_write_ram_buffer(gLcdPixelCache, size % MXTX_DATA_CACHE_SIZE);
}

//=============================================================================
void mxtx_draw_rectangle(struct _point* Coord1, struct _point* Coord2)
{
	uint32_t dwX1 = Coord1->x;
	uint32_t dwY1 = Coord1->y;
	uint32_t dwX2 = Coord2->x;
	uint32_t dwY2 = Coord2->y;

	mxtx_check_box_coordinates(Coord1, Coord2);

	struct _point Pt1 =
		{
			.x = dwX1,
			.y = dwY1,
		};
	struct _point Pt2 =
		{
			.x = dwX2,
			.y = dwY1,
		};
	mxtx_draw_filled_rectangle(&Pt1, &Pt2); // dwX1, dwY1, dwX2, dwY1 ) ;
	Pt1.x = dwX1;
	Pt1.y = dwY2;
	Pt2.x = dwX2;
	Pt2.y = dwY2;
	mxtx_draw_filled_rectangle(&Pt1, &Pt2); // dwX1, dwY2, dwX2, dwY2 ) ;
	Pt1.x = dwX1;
	Pt1.y = dwY1;
	Pt2.x = dwX1;
	Pt2.y = dwY2;
	mxtx_draw_filled_rectangle(&Pt1, &Pt2); // dwX1, dwY1, dwX1, dwY2 ) ;
	Pt1.x = dwX2;
	Pt1.y = dwY1;
	Pt2.x = dwX2;
	Pt2.y = dwY2;
	mxtx_draw_filled_rectangle(&Pt1, &Pt2); // dwX2, dwY1, dwX2, dwY2 ) ;
}

//=============================================================================
// Draw a rounded rectangle
void mxtx_draw_rounded_rectangle(struct _point* Coord1, struct _size* Size, uint32_t r)
{
	uint32_t x = Coord1->x;
	uint32_t y = Coord1->y;
	uint32_t w = Size->w;
	uint32_t h = Size->h;
	struct _point Pt1;

	Pt1.x = x+r;
	Pt1.y = y;
	mxtx_draw_fast_horizontal_line(&Pt1, w-2*r); // Top
	Pt1.x = x+r;
	Pt1.y = y+h-1;
	mxtx_draw_fast_horizontal_line(&Pt1, w-2*r); // Bottom
	Pt1.x = x;
	Pt1.y = y+r;
	mxtx_draw_fast_vertical_line(&Pt1, h-2*r); // Left
	Pt1.x = x+w-1;
	Pt1.y = y+r;
	mxtx_draw_fast_vertical_line(&Pt1, h-2*r); // Right
	// draw four corners
	Pt1.x = x+r;
	Pt1.y = y+r;
	mxtx_draw_circleHelper(&Pt1, r, 1);
	Pt1.x = x+w-r-1;
	Pt1.y = y+r;
	mxtx_draw_circleHelper(&Pt1, r, 2);
	Pt1.x = x+w-r-1;
	Pt1.y = y+h-r-1;
	mxtx_draw_circleHelper(&Pt1, r, 4);
	Pt1.x = x+r;
	Pt1.y = y+h-r-1;
	mxtx_draw_circleHelper(&Pt1, r, 8);
}

//=============================================================================
// Draw a triangle
void mxtx_draw_triangle(struct _point* Coord0, struct _point* Coord1, struct _point* Coord2)
{
	mxtx_draw_line(Coord0, Coord1);
	mxtx_draw_line(Coord1, Coord2);
	mxtx_draw_line(Coord0, Coord2);
}

//=============================================================================
// Fill a triangle
void mxtx_draw_filled_triangle(struct _point* Coord0, struct _point* Coord1, struct _point* Coord2)
{
	int16_t a, b, y, last;
	int16_t dx01, dy01, dx02, dy02, dx12, dy12;
	int32_t sa, sb;
	struct _point Pt1;

	// Sort coordinates by Y order (y2 >= y1 >= y0)
	if (Coord0->y > Coord1->y)
	{
		swap(Coord0->y, Coord1->y);
		swap(Coord0->y, Coord1->x);
	}
	if (Coord1->y > Coord2->y)
	{
		swap(Coord2->y, Coord1->y);
		swap(Coord2->x, Coord1->x);
	}
	if (Coord0->y > Coord1->y)
	{
		swap(Coord0->y, Coord1->y);
		swap(Coord0->x, Coord1->x);
	}

	if(Coord0->y == Coord2->y)
	{ // Handle awkward all-on-same-line case as its own thing
		a = b = Coord0->x;
		if( (int16_t)Coord1->x < a)
			a = Coord1->x;
		else if ( (int16_t)Coord1->x > b)
			b = Coord1->x;
		if( (int16_t)Coord2->x < a)
			a = Coord2->x;
		else if( (int16_t)Coord2->x > b)
			b = Coord2->x;
		Pt1.x = a;
		Pt1.y = Coord0->y;
		mxtx_draw_fast_horizontal_line(&Pt1, b-a+1);
		return;
	}

	dx01 = Coord1->x - Coord0->x,
		dy01 = Coord1->y - Coord0->y,
		dx02 = Coord2->x - Coord0->x,
		dy02 = Coord2->y - Coord0->y,
		dx12 = Coord2->x - Coord1->x,
		dy12 = Coord2->y - Coord1->y;
	sa   = 0,
		sb   = 0;

	// For upper part of triangle, find scanline crossings for segments
	// 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
	// is included here (and second loop will be skipped, avoiding a /0
	// error there), otherwise scanline y1 is skipped here and handled
	// in the second loop...which also avoids a /0 error here if y0=y1
	// (flat-topped triangle).
	if(Coord1->y == Coord2->y)
		last = Coord1->y;   // Include y1 scanline
	else
		last = Coord1->y-1; // Skip it

	for(y=Coord0->y; y<=last; y++)
	{
		a   = Coord0->x + sa / dy01;
		b   = Coord0->x + sb / dy02;
		sa += dx01;
		sb += dx02;
		if(a > b) swap(a,b);
		Pt1.x = a;
		Pt1.y = y;
		mxtx_draw_fast_horizontal_line(&Pt1, b-a+1);
	}

	// For lower part of triangle, find scanline crossings for segments
	// 0-2 and 1-2.  This loop is skipped if y1=y2.
	sa = dx12 * (y - Coord1->y);
	sb = dx02 * (y - Coord0->y);
	for(; y <= (int16_t)Coord2->y; y++)
	{
		a   = Coord1->x + sa / dy12;
		b   = Coord0->x + sb / dy02;
		sa += dx12;
		sb += dx02;
		if(a > b) swap(a,b);
		Pt1.x = a;
		Pt1.y = y;
		mxtx_draw_fast_horizontal_line(&Pt1, b-a+1);
	}
}

//=============================================================================
/**
 * \brief Set the backlight of the LCD
 * \param level   Backlight brightness level [1..16], 1 means maximum brightness.
 */
void mxtx_set_backlight (uint8_t level)
{
	/* Ensure valid level */
	level = (level < 1) ? 1 : level;
	//level = (level > 16) ? 16 : level;
	pwmc_set_duty_cycle(PWM, CHANNEL_PWM_LCD, level);
}

//=============================================================================
// DEMO and TEST
//=============================================================================

/** Number of blocks in vertical */
#define N_BLK_VERT    6
/** Number of blocks in horizontal */
#define N_BLK_HOR     6

void mxtx_test_pattern(void)
{
	uint8_t bcl, row, col;
	uint32_t size_x, size_y;
	uint32_t base_color ;

	size_x = sMXTX.scr_width/N_BLK_HOR;
	size_y = sMXTX.scr_height/N_BLK_VERT;
	for (bcl=0 ; bcl<6; bcl++)
	{
		base_color = 0x330000 * bcl ;
		for (row=0 ; row<N_BLK_VERT; row++)
		{
			for (col=0; col<N_BLK_HOR; col++)
			{
				mxtx_set_color(base_color + (0x33*col));
				struct _point Pt1 =
					{
						.x = size_x*col,
						.y = size_y*row,
					};
				struct _point Pt2 =
					{
						.x = (size_x*col)+(size_x-5),
						.y = (size_y*row)+(size_y-5),
					};
				mxtx_draw_filled_rectangle(&Pt1, &Pt2);
			}
			base_color += 0x3300 ;
		}
		timer_wait(1000);
	}
}

//=============================================================================

void test_lcd_ili9488(void)
{
	uint16_t i;

	struct _point Pt1 =
		{
			.x = 0,
			.y = 0,
		};
	struct _point Pt2 =
		{
			.x = 0,
			.y = 0,
		};
	struct _size Size =
		{
			.w = 0,
			.h = 0,
		};

	if (mxtx_initialize()) {
		printf(" --E-- Error init ILI9488 \n\n");
		return;
	}
	mxtx_set_backlight(20);
	mxtx_set_font(FONT10x14);

	(mxtx_get_pnt_struct())->scr_bgcolor = COLOR_WHITE;

	mxtx_clear_screen();
	mxtx_test_pattern();
	mxtx_clear_screen();


	/* Test LCD_DrawFilledCircle */
	mxtx_set_color(COLOR_BLUE);
	Pt1.x = MXTX_LCD_WIDTH*3/4;
	Pt1.y = MXTX_LCD_HEIGHT*3/4;
	mxtx_draw_filled_circle(&Pt1, MXTX_LCD_WIDTH/4);
	Pt1.x = MXTX_LCD_WIDTH/4;
	Pt1.y = MXTX_LCD_HEIGHT/4;
	mxtx_draw_circle(&Pt1, MXTX_LCD_HEIGHT/4);
	mxtx_set_color(COLOR_OLIVE);
	Pt1.x = MXTX_LCD_WIDTH/4;
	Pt1.y = MXTX_LCD_HEIGHT*3/4;
	mxtx_draw_filled_circle(&Pt1, MXTX_LCD_HEIGHT/4);
	mxtx_set_color(COLOR_BLACK);
	Pt1.x = MXTX_LCD_WIDTH*3/4;
	Pt1.y = MXTX_LCD_HEIGHT*3/4;
	mxtx_draw_circle(&Pt1, MXTX_LCD_WIDTH/4);

	/* Test horizontal/vertial LCD_drawLine  */
	mxtx_set_color(COLOR_CYAN);
	Pt1.x = 0;
	Pt1.y = MXTX_LCD_HEIGHT/2;
	Pt2.x = MXTX_LCD_WIDTH-1;
	Pt2.y = MXTX_LCD_HEIGHT/2;
	mxtx_draw_line(&Pt1, &Pt2);
	Pt1.x = MXTX_LCD_WIDTH/2;
	Pt1.y = 0;
	Pt2.x = MXTX_LCD_WIDTH/2;
	Pt2.y = MXTX_LCD_HEIGHT-1;
	mxtx_draw_line(&Pt1, &Pt2);

	/* Test Bresenham LCD_drawLine  */
	Pt1.x = 0;
	Pt1.y = 0;
	Pt2.x = MXTX_LCD_WIDTH-1;
	Pt2.y = MXTX_LCD_HEIGHT-1;
	mxtx_draw_line(&Pt1, &Pt2);
	Pt1.x = 0;
	Pt1.y = MXTX_LCD_HEIGHT-1;
	Pt2.x = MXTX_LCD_WIDTH-1;
	Pt2.y = 0;
	mxtx_draw_line(&Pt1, &Pt2);

	/* Test LCD_DrawRectangle */
	Pt1.x = MXTX_LCD_WIDTH/4;
	Pt1.y = MXTX_LCD_HEIGHT/4;
	Pt2.x = MXTX_LCD_WIDTH*3/4;
	Pt2.y = MXTX_LCD_HEIGHT*3/4;
	mxtx_draw_rectangle(&Pt1, &Pt2);

	Pt1.x = MXTX_LCD_WIDTH*2/3;
	Pt1.y = MXTX_LCD_HEIGHT*2/3;
	Pt2.x = MXTX_LCD_WIDTH/3;
	Pt2.y = MXTX_LCD_HEIGHT/3;
	mxtx_set_color(COLOR_BLACK);
	mxtx_draw_rectangle(&Pt1, &Pt2);

	Pt1.x = MXTX_LCD_WIDTH/3;
	Pt1.y = MXTX_LCD_HEIGHT/3;
	Size.w = MXTX_LCD_WIDTH/3;
	Size.h = MXTX_LCD_HEIGHT/3;
	mxtx_set_color(COLOR_BLUE);
	mxtx_draw_rounded_rectangle(&Pt1, &Size, 20);

	Pt1.x = 50; Pt1.y = 50;
	Size.w = 100; Size.h = 50;
	mxtx_set_color(COLOR_GREEN);
	mxtx_draw_rounded_rectangle (&Pt1, &Size, 10);

	mxtx_set_font(FONT10x14);
	Pt1.x = 170;
	Pt1.y = 20;
	mxtx_draw_string(&Pt1, "ATMEL 2015", COLOR_BLACK);
	mxtx_set_font(FONT10x8);
	Pt1.x = 170;
	Pt1.y = 40;
	mxtx_draw_string(&Pt1, "ATMEL 2015", COLOR_BLACK);
	mxtx_set_font(FONT8x8);
	Pt1.x = 170;
	Pt1.y = 55;
	mxtx_draw_string(&Pt1, "ATMEL 2015", COLOR_BLACK);
	mxtx_set_font(FONT6x8);
	Pt1.x = 170;
	Pt1.y = 70;
	mxtx_draw_string(&Pt1, "ATMEL 2015", COLOR_BLACK);
	mxtx_set_font(FONT10x14);

	mxtx_set_color(COLOR_RED);
	Pt1.x = 10;
	Pt1.y = 10;
	Pt2.x = 100;
	Pt2.y = 150;
	struct _point Pt3 = { .x = 40, .y = 100, };
	mxtx_draw_triangle (&Pt1, &Pt2, &Pt3);
	Pt1.x = 10;
	Pt1.y = 10;
	Pt2.x = 100;
	Pt2.y = 150;
	Pt3.x = 5;
	Pt3.y = 100;
	mxtx_draw_filled_triangle (&Pt1, &Pt2, &Pt3);

	// draws a series of circles on a circle in steps of 30 Ѝ

	mxtx_set_color(COLOR_BLACK);
	struct _point Org = { .x = MXTX_LCD_WIDTH/2, .y = MXTX_LCD_HEIGHT/2, };
	mxtx_draw_circle(&Org, 50); // main cirle

	Pt1 = Org;
	point_on_circle (&Pt1, 50, 0);
	mxtx_draw_filled_circle(&Pt1, 10);
	Pt3 = Pt1;
	do
	{
		for (i=0; i<360; i+=30)
		{
			timer_wait(100);
			Pt2 = Pt1;
			// delete old filled circle

			mxtx_set_color(COLOR_LIGHTGREY);
			mxtx_draw_filled_circle(&Pt2, 10);
			mxtx_set_color(COLOR_WHITE);
			mxtx_draw_filled_circle(&Pt3, 10);
			// draw old circle not filled
			mxtx_set_color(COLOR_BLACK);
			mxtx_draw_circle(&Pt2, 10);
			mxtx_draw_circle(&Pt3, 10);
			Pt3 = Pt2;
			Pt1 = Org;
			point_on_circle (&Pt1, 50, i);
			mxtx_draw_filled_circle(&Pt1, 10);
		}

	} while (1);

}
