/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, Atmel Corporation
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

#ifndef _BOARD_SAMA5D4_EK_H
#define _BOARD_SAMA5D4_EK_H

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

#include "board_lowlevel.h"
#include "board_memories.h"

/*----------------------------------------------------------------------------
 *        HW BOARD Definitions
 *----------------------------------------------------------------------------*/

/**
 * \page sama5d4-ek_board_info "sama5d4-ek - Board Informations"
 * This page lists several definition related to the board description.
 *
 * \section Definitions
 * - \ref BOARD_NAME
 */

/** Name of the board */
#define BOARD_NAME "sama5d4-xult"

/*----------------------------------------------------------------------------*/
/**
 *  \page sama5d4_ek_opfreq "sama5d4-ek - Operating Frequencies"
 *  This page lists several definition related to the board operating frequency
 *  (when using the initialization done by board_lowlevel.c).
 */

/** Frequency of the board slow clock oscillator */
#define BOARD_SLOW_CLOCK_EXT_OSC 32768

/** Frequency of the board main clock oscillator */
#define BOARD_MAIN_CLOCK_EXT_OSC 12000000

/** /def Definition of DDRAM's type */
#define BOARD_DDRAM_TYPE         MT47H128M16

/** \def Board DDR memory size in bytes */
#define BOARD_DDR_MEMORY_SIZE    512*1024*1024

/** \def Board PIT tick resolution */
#define BOARD_TIMER_RESOLUTION    1000

/* =================== PIN CONSOLE definition ================== */

/** CONSOLE pin definition, Use only USART */
#define CONSOLE_DRIVER          DRV_DBGU
#define PINS_CONSOLE            {PIN_USART3_TXD,PIN_USART3_RXD}
#define CONSOLE_PER_ADD         USART3
#define CONSOLE_ID              ID_USART3
#define CONSOLE_BAUDRATE        115200

/* =================== PIN LED definition ====================== */

/* RGB LED index */
#define LED_BLUE  0
#define LED_RED   1

/** LED #0 pin definition (Blue). */
#define PIN_LED_0 { PIO_GROUP_E, PIO_PE15, PIO_OUTPUT_1, PIO_DEFAULT }

/** LED #1 pin definition (Red). */
#define PIN_LED_1 { PIO_GROUP_D, PIO_PD30, PIO_OUTPUT_0, PIO_DEFAULT }

/** List of all LEDs definitions. */
#define PINS_LEDS { PIN_LED_0, PIN_LED_1 }

/* =================== PIN PUSH BUTTON definition ============== */

#define PIO_CFG_PB  (PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE)
#define PIN_PUSHBUTTON_1 { PIO_GROUP_E, PIO_PE8, PIO_INPUT, PIO_CFG_PB }

/** List of all push button definitions. */
#define PINS_PUSHBUTTONS { PIN_PUSHBUTTON_1 }

/** Push button index. */
#define PUSHBUTTON_BP1 0

/* =================== AT25 device definition =================== */

#define AT25_PINS     PINS_SPI0_NPCS0
#define AT25_ADDR     SPI0
#define AT25_CS       0
#define AT25_ATTRS    (SPI_MR_MODFDIS | SPI_MR_WDRBT | SPI_MR_MSTR)
#define AT25_FREQ     40000 /* (value in KHz) */
#define AT25_LOW_FREQ 20000 /* (value in KHz) */
#define AT25_DLYBS    0
#define AT25_DLYCT    0
#define AT25_SPI_MODE (SPI_CSR_NCPHA | SPI_CSR_BITS_8_BIT)

/* =================== GMAC/PHY definition =================== */

#define GMAC0_ADDR        GMAC0
#define GMAC0_PINS        PINS_GMAC0_RMII
#define GMAC0_PHY_ADDR    0
#define GMAC0_PHY_IRQ_PIN { PIO_GROUP_E, PIO_PE1, PIO_INPUT, PIO_PULLUP }
#define GMAC0_PHY_RETRIES PHY_DEFAULT_RETRIES

/* =================== Display device definition =================== */

/** Display width in pixels. */
#define BOARD_LCD_WIDTH 800

/** Display height in pixels. */
#define BOARD_LCD_HEIGHT 480

/** Display interface width in bits. */
#define BOARD_LCD_IFWIDTH           24
/** Frame size in words (height * width * bpp / 32) */
#define BOARD_LCD_FRAMESIZE         (BOARD_LCD_WIDTH * BOARD_LCD_HEIGHT * BOARD_LCD_IFWIDTH / 32)

/** Vertical front porch in number of lines. */
#define BOARD_LCD_TIMING_VFP        22
/** Vertical back porch in number of lines. */
#define BOARD_LCD_TIMING_VBP        21
/** Vertical pulse width in number of lines. */
#define BOARD_LCD_TIMING_VPW        2
/** Horizontal front porch in LCDDOTCLK cycles. */
#define BOARD_LCD_TIMING_HFP        64
/** Horizontal back porch in LCDDOTCLK cycles. */
#define BOARD_LCD_TIMING_HBP        64
/** Horizontal pulse width in LCDDOTCLK cycles. */
#define BOARD_LCD_TIMING_HPW        128

/** Frame rate in Hz. */
#define BOARD_LCD_FRAMERATE         40

#define EXAMPLE_LCD_SCALE   1

/** Pixel clock rate in Hz (HS period * VS period * BOARD_LCD_FRAMERATE). */
#define BOARD_LCD_PIXELCLOCK \
	((BOARD_LCD_TIMING_HPW+BOARD_LCD_TIMING_HBP                     \
	  +BOARD_LCD_WIDTH+BOARD_LCD_TIMING_HFP)                        \
	 *(BOARD_LCD_TIMING_VPW+BOARD_LCD_TIMING_VBP+                   \
	   BOARD_LCD_HEIGHT+BOARD_LCD_TIMING_VFP)                       \
	 *BOARD_LCD_FRAMERATE)

#endif /* _BOARD_SAMA5D4_EK_H */
