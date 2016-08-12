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

#ifndef _BOARD_SAMA5D4_XPLAINED_H
#define _BOARD_SAMA5D4_XPLAINED_H

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

#include "board_support.h"

/*----------------------------------------------------------------------------
 *        HW BOARD Definitions
 *----------------------------------------------------------------------------*/

/**
 * \page sama5d4-xplained_board_info "sama5d4-xplained - Board Informations"
 * This page lists several definition related to the board description.
 *
 * \section Definitions
 * - \ref BOARD_NAME
 */

/** Name of the board */
#define BOARD_NAME "sama5d4-xult"

/*----------------------------------------------------------------------------*/

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

/** CONSOLE pin definition: use USART3 */
/* Note that since this is the ROM-code default console, these definitions
 * could be omitted */
#define BOARD_CONSOLE_PINS     { PIN_USART3_TXD, PIN_USART3_RXD }
#define BOARD_CONSOLE_ADDR     USART3
#define BOARD_CONSOLE_BAUDRATE 115200

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

#define NUM_LEDS 2

/* =================== PIN PUSH BUTTON definition ============== */

#define PIO_CFG_PB  (PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE)
#define PIN_PUSHBUTTON_1 { PIO_GROUP_E, PIO_PE8, PIO_INPUT, PIO_CFG_PB }

/** List of all push button definitions. */
#define PINS_PUSHBUTTONS { PIN_PUSHBUTTON_1 }

/** Push button index. */
#define PUSHBUTTON_BP1 0

/* =================== USB device definition =================== */

/** USB VBus pin */
#define PIN_USB_VBUS \
	{ PIO_GROUP_E, PIO_PE31, PIO_INPUT, PIO_DEFAULT }

/** USB OverCurrent detection*/
#define PIN_USB_OVCUR \
	{ PIO_GROUP_E, PIO_PE0, PIO_INPUT, PIO_PULLUP }

/** USB Power Enable B:A:Active High  */
#define PIN_USB_POWER_ENB \
	{ PIO_GROUP_E, PIO_PE11, PIO_OUTPUT_0, PIO_DEFAULT }

/** USB Power Enable C:A:Active High  */
#define PIN_USB_POWER_ENC \
	{ PIO_GROUP_E, PIO_PE14, PIO_OUTPUT_0, PIO_DEFAULT }

/** USB attributes configuration descriptor (bus or self powered,
 * remote wakeup) */
#define BOARD_USB_BMATTRIBUTES \
	USBConfigurationDescriptor_SELFPOWERED_NORWAKEUP

/* =================== HSMCI device definition ==================== */

/** HSMCI0 power control: none, always powered on */

/** HSMCI0 card detect pin definition */
#define BOARD_HSMCI0_PIN_CD \
	{ PIO_GROUP_E, PIO_PE2, PIO_INPUT, PIO_DEFAULT }

/** HSMCI0 device interface pin set definition */
#define BOARD_HSMCI0_DEV_PINS \
	{ PIN_HSMCI0_CDA, PIN_HSMCI0_CK, PINS_HSMCI0_DA0_3 }

/** HSMCI0 pin set definition */
#define BOARD_HSMCI0_PINS \
	{ PIN_HSMCI0_CDA, PIN_HSMCI0_CK, PINS_HSMCI0_DA0_3, \
	  BOARD_HSMCI0_PIN_CD }

/** HSMCI0 slot definition */
#define BOARD_HSMCI0_SLOT HSMCI_SDCR_SDCSEL_SLOTA

/** HSMCI1 power control definition */
#define BOARD_HSMCI1_PIN_POWER \
	{ PIO_GROUP_E, PIO_PE4, PIO_OUTPUT_0, PIO_DEFAULT }

/** HSMCI1 card detect pin definition */
#define BOARD_HSMCI1_PIN_CD \
	{ PIO_GROUP_E, PIO_PE3, PIO_INPUT, PIO_DEFAULT }

/** HSMCI1 device interface pin set definition */
#define BOARD_HSMCI1_DEV_PINS \
	{ PIN_HSMCI1_CDA, PIN_HSMCI1_CK, PINS_HSMCI1_DA }

/** HSMCI1 pin set definition */
#define BOARD_HSMCI1_PINS \
	{ BOARD_HSMCI1_PIN_POWER, PIN_HSMCI1_CDA, \
	  PIN_HSMCI1_CK, PINS_HSMCI1_DA, BOARD_HSMCI1_PIN_CD }

/* ================== TWI bus definition ====================== */

#define BOARD_TWI_BUS0      TWI3
#define BOARD_TWI_BUS0_FREQ 400000
#define BOARD_TWI_BUS0_PINS PINS_TWI3

#define BOARD_TWI_BUS1      TWI0
#define BOARD_TWI_BUS1_FREQ 400000
#define BOARD_TWI_BUS1_PINS PINS_TWI0

/* =================== AT24 device definition =================== */

#define BOARD_AT24_TWI_BUS        1
#define BOARD_AT24_DESC           {"AT24MAC402", 0xFF, 16}
#define BOARD_AT24_EEP_ADDR       (0x50 | 0x4)
#define BOARD_AT24_SN_ADDR        (0x58 | 0x4)
#define BOARD_AT24_SN_OFFSET      0x80        // 0x80-0x8F
#define BOARD_AT24_EUI48_OFFSET   0x9A        // 0x9A-0x9F

/* =================== AT25 device definition =================== */

#define BOARD_AT25_PINS     PINS_SPI0_NPCS0
#define BOARD_AT25_ADDR     SPI0
#define BOARD_AT25_CS       0
#define BOARD_AT25_ATTRS    (SPI_MR_MODFDIS | SPI_MR_WDRBT | SPI_MR_MSTR)
#define BOARD_AT25_FREQ     40000 /* (value in KHz) */
#define BOARD_AT25_DLYBS    0
#define BOARD_AT25_DLYCT    0
#define BOARD_AT25_SPI_MODE (SPI_CSR_NCPHA | SPI_CSR_BITS_8_BIT)

/* =================== GMAC/PHY definition =================== */

#define GMAC0_ADDR        GMAC0
#define GMAC0_PINS        PINS_GMAC0_RMII
#define GMAC0_PHY_ADDR    0
#define GMAC0_PHY_IRQ_PIN { PIO_GROUP_E, PIO_PE1, PIO_INPUT, PIO_PULLUP }
#define GMAC0_PHY_RETRIES PHY_DEFAULT_RETRIES

/* =================== NANDFLASH device definition =================== */

#define BOARD_NANDFLASH_PINS      PINS_NAND8
#define BOARD_NANDFLASH_BUS_WIDTH 8

/* =================== Display device definition =================== */

/** PIO pins for LCD */
#define BOARD_LCD_PINS              PINS_LCD

/** Display width in pixels. */
#define BOARD_LCD_WIDTH             480
/** Display height in pixels. */
#define BOARD_LCD_HEIGHT            272
/** Frame rate in Hz. */
#define BOARD_LCD_FRAMERATE         40

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

/* ================== ACT8865 PMIC definition ====================== */

#define BOARD_ACT8865_TWI_BUS  0
#define BOARD_ACT8865_TWI_ADDR 0x5b
#define BOARD_ACT8865_PIN_IRQ  { PIO_GROUP_E, PIO_PE25, PIO_INPUT, PIO_PULLUP | PIO_IT_FALL_EDGE }

#endif /* _BOARD_SAMA5D4_XPLAINED_H */
