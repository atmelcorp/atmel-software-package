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
#include "peripherals/bus.h"

#include "board_support.h"

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
#define BOARD_NAME "sama5d4-ek"

/*----------------------------------------------------------------------------*/
/**
 *  \page sama5d4_ek_opfreq "sama5d4-ek - Operating Frequencies"
 *  This page lists several definition related to the board operating frequency
 *  (when using the initialization done by board_lowlevel.c).
 */

/** Frequency of the board main clock oscillator */
#define BOARD_MAIN_CLOCK_EXT_OSC 12000000

/** /def Definition of DDRAM's type */
#define BOARD_DDRAM_TYPE         MT47H128M8

/** \def Board DDR memory size in bytes */
#define BOARD_DDR_MEMORY_SIZE    512*1024*1024

/** \def Board System timer */
#define BOARD_TIMER_TC      TC1
#define BOARD_TIMER_CHANNEL 0

/* =================== PIN CONSOLE definition ================== */

/** CONSOLE pin definition: use USART3 */
/* Note that since this is the ROM-code default console, these definitions
 * could be omitted */
#define BOARD_CONSOLE_ADDR     USART3
#define BOARD_CONSOLE_BAUDRATE 115200
#define BOARD_CONSOLE_TX_PIN   PIN_USART3_TXD
#define BOARD_CONSOLE_RX_PIN   PIN_USART3_RXD

/* =================== PIN LED definition ====================== */

/* RGB LED index */
#define LED_BLUE  0
#define LED_RED   1
#define LED_GREEN 2

/** LED #0 pin definition (Blue). */
#define PIN_LED_0 { PIO_GROUP_E, PIO_PE8, PIO_OUTPUT_1, PIO_DEFAULT }

/** LED #1 pin definition (Red). */
#define PIN_LED_1 { PIO_GROUP_E, PIO_PE9, PIO_OUTPUT_0, PIO_DEFAULT }

/** LED #2 pin definition (Green). */
#define PIN_LED_2 { PIO_GROUP_E, PIO_PE28, PIO_OUTPUT_0, PIO_DEFAULT }

/** List of all LEDs definitions. */
#define PINS_LEDS { PIN_LED_0, PIN_LED_1, PIN_LED_2 }

#define NUM_LEDS  3

/* =================== PIN PUSH BUTTON definition ============== */

#define PIO_CFG_PB  (PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE)
#define PIN_PUSHBUTTON_1 { PIO_GROUP_E, PIO_PE13, PIO_INPUT, PIO_CFG_PB }

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
	{ PIO_GROUP_D, PIO_PD9, PIO_INPUT, PIO_PULLUP }

/** USB Power Enable A:MicroAB:Active low */
#define PIN_USB_POWER_ENA \
	{ PIO_GROUP_E, PIO_PE10, PIO_OUTPUT_1, PIO_DEFAULT }

/** USB Power Enable B:A:Active low  */
#define PIN_USB_POWER_ENB \
	{ PIO_GROUP_E, PIO_PE11, PIO_OUTPUT_1, PIO_DEFAULT }

/** USB Power Enable C:A:Active low  */
#define PIN_USB_POWER_ENC \
	{ PIO_GROUP_E, PIO_PE12, PIO_OUTPUT_1, PIO_DEFAULT }

/** USB attributes configuration descriptor (bus or self powered,
 * remote wakeup) */
#define BOARD_USB_BMATTRIBUTES \
	USBConfigurationDescriptor_SELFPOWERED_NORWAKEUP

/* =================== HSMCI device definition ==================== */

/** HSMCI0 Card detect pin definition */
#define BOARD_HSMCI0_PIN_CD \
	{ PIO_GROUP_E, PIO_PE5, PIO_INPUT, PIO_DEFAULT }

/** HSMCI0: the 4 most-significant data bits miss on-board pull-up resistors,
 *  enable the on-chip pull-up resistors. */
#define PINS_HSMCI0_DATA8B_A_MSB \
	{ PIO_GROUP_C, PIO_PC10B_MCI0_DA4 | PIO_PC11B_MCI0_DA5 \
	  | PIO_PC12B_MCI0_DA6 | PIO_PC13B_MCI0_DA7, PIO_PERIPH_B, PIO_PULLUP }

/** HSMCI0 device interface pin set definition */
#define BOARD_HSMCI0_DEV_PINS \
	{ PIN_HSMCI0_CMD_A, PIN_HSMCI0_CK, PINS_HSMCI0_DATA4B_A, PINS_HSMCI0_DATA8B_A_MSB }

/** HSMCI0 pin set definition */
#define BOARD_HSMCI0_PINS \
	{ PIN_HSMCI0_CMD_A, PIN_HSMCI0_CK, PINS_HSMCI0_DATA4B_A, PINS_HSMCI0_DATA8B_A_MSB, \
	  BOARD_HSMCI0_PIN_CD }

/** HSMCI0 slot definition */
#define BOARD_HSMCI0_SLOT 0

/** HSMCI1 power control definition */
#define BOARD_HSMCI1_PIN_POWER \
	{ PIO_GROUP_E, PIO_PE15, PIO_OUTPUT_0, PIO_DEFAULT }

/** HSMCI1 Card detect pin definition */
#define BOARD_HSMCI1_PIN_CD \
	{ PIO_GROUP_E, PIO_PE6, PIO_INPUT, PIO_DEFAULT }

/** HSMCI1 device interface pin set definition */
#define BOARD_HSMCI1_DEV_PINS \
	{ PIN_HSMCI1_CMD_A, PIN_HSMCI1_CK, PINS_HSMCI1_DATA4B_A }

/** HSMCI1 pin set definition */
#define BOARD_HSMCI1_PINS \
	{ PIN_HSMCI1_CMD_A, PIN_HSMCI1_CK, PINS_HSMCI1_DATA4B_A, \
	  BOARD_HSMCI1_PIN_CD, BOARD_HSMCI1_PIN_POWER }

/** HSMCI1 slot definition */
#define BOARD_HSMCI1_SLOT 0

/* ================== TWI bus definition ====================== */

#define BOARD_TWI_BUS0      TWI0
#define BOARD_TWI_BUS0_FREQ 400000
#define BOARD_TWI_BUS0_PINS PINS_TWI0
#define BOARD_TWI_BUS0_MODE BUS_TRANSFER_MODE_DMA

/* ================== SPI bus definition ====================== */

#define BOARD_SPI_BUS0       SPI0
#define BOARD_SPI_BUS0_PINS  PINS_SPI0_NPCS0
#define BOARD_SPI_BUS0_MODE  BUS_TRANSFER_MODE_DMA

#define BOARD_SPI_BUS1       SPI1
#define BOARD_SPI_BUS1_PINS  PINS_SPI1_NPCS0
#define BOARD_SPI_BUS1_MODE  BUS_TRANSFER_MODE_DMA

/* =================== AT25 device definition =================== */

#define BOARD_AT25_BUS         BUS(BUS_TYPE_SPI, 0)
#define BOARD_AT25_CHIP_SELECT 0
#define BOARD_AT25_BITRATE     40000
#define BOARD_AT25_DLYBS       0
#define BOARD_AT25_DLYBCT      0
#define BOARD_AT25_SPI_MODE    SPID_MODE_0

/* =================== ETH definition =================== */

#define BOARD_ETH0_PINS        PINS_GMAC0_RMII
#define BOARD_ETH0_TYPE        ETH_TYPE_GMAC
#define BOARD_ETH0_ADDR        GMAC0
#define BOARD_ETH0_PHY_ADDR    1
#define BOARD_ETH0_PHY_IF      PHY_IF_GMAC
#define BOARD_ETH0_PHY_IRQ_PIN { PIO_GROUP_E, PIO_PE1, PIO_INPUT, PIO_PULLUP }
#define BOARD_ETH0_MAC_ADDR    {0x3a, 0x1f, 0x34, 0x08, 0x27, 0x27}

#define BOARD_ETH1_PINS        PINS_GMAC1_RMII
#define BOARD_ETH1_TYPE        ETH_TYPE_GMAC
#define BOARD_ETH1_ADDR        GMAC1
#define BOARD_ETH1_PHY_ADDR    2
#define BOARD_ETH1_PHY_IF      PHY_IF_GMAC
#define BOARD_ETH1_PHY_IRQ_PIN { PIO_GROUP_E, PIO_PE2, PIO_INPUT, PIO_PULLUP }
#define BOARD_ETH1_MAC_ADDR    {0x3a, 0x1f, 0x34, 0x08, 0x54, 0x54}

/* =================== NANDFLASH device definition =================== */

#define BOARD_NANDFLASH_PINS      PINS_NAND8
#define BOARD_NANDFLASH_BUS_WIDTH 8

/* =================== Display device definition =================== */

/** PIO pins for LCD */
#define BOARD_LCD_PINS              PINS_LCD

/** Display width in pixels. */
#define BOARD_LCD_WIDTH             800
/** Display height in pixels. */
#define BOARD_LCD_HEIGHT            480
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

/* =================== ISI device definition =================== */

#define BOARD_ISI_TWI_BUS     BUS(BUS_TYPE_I2C, 0)
#define BOARD_ISI_PINS        PINS_ISI_8BIT
#define BOARD_ISI_RST_PIN     { PIO_GROUP_B, PIO_PB11, PIO_OUTPUT_1, PIO_DEFAULT }
#define BOARD_ISI_PWD_PIN     { PIO_GROUP_B, PIO_PB5, PIO_OUTPUT_1, PIO_DEFAULT }
#define BOARD_ISI_MCK_PCK     1
#define BOARD_ISI_MCK_PCK_SRC PMC_PCK_CSS_MCK
#define BOARD_ISI_MCK_PCK_DIV 3
#define BOARD_ISI_MCK_PIN     PIN_PCK1

/* ================== ACT8865 PMIC definition ====================== */

#define BOARD_ACT8865_TWI_BUS  BUS(BUS_TYPE_I2C, 0)
#define BOARD_ACT8865_TWI_ADDR 0x5b
#define BOARD_ACT8865_PIN_IRQ  { PIO_GROUP_E, PIO_PE0, PIO_INPUT, PIO_PULLUP | PIO_IT_FALL_EDGE }

/* ================== SSC definition ====================== */

#define BOARD_SSC0_PINS PINS_SSC0

/* ================== WM8904 definition ====================== */

#define BOARD_WM8904_TWI_BUS      BUS(BUS_TYPE_I2C, 0)
#define BOARD_WM8904_SLAVE_ADDR   0x1a
#define BOARD_WM8904_INPUT_PATH   (WM8904_INPUT_PATH_IN1L | WM8904_INPUT_PATH_IN1R)
#define BOARD_WM8904_MCLK_PCK     2
#define BOARD_WM8904_MCLK_PCK_SRC PMC_PCK_CSS_SLOW_CLK
#define BOARD_WM8904_MCLK_PIN     PIN_PCK2_ALT1

#endif /* _BOARD_SAMA5D4_EK_H */
