/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
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

#ifndef _BOARD_SAMA5D3_EK_H
#define _BOARD_SAMA5D3_EK_H

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
 * \page sama5d3-ek_board_info "sama5d3-ek - Board Informations"
 * This page lists several definition related to the board description.
 *
 * \section Definitions
 * - \ref BOARD_NAME
 */

/** Name of the board */
#define BOARD_NAME "sama5d3-ek" /* for mainboard revision D or later */

/*----------------------------------------------------------------------------*/

/** Frequency of the board main clock oscillator */
#define BOARD_MAIN_CLOCK_EXT_OSC 12000000

/** /def Definition of DDRAM's type */
#define BOARD_DDRAM_TYPE         MT47H128M16

/** \def Board DDR memory size in bytes */
#define BOARD_DDR_MEMORY_SIZE    512*1024*1024

/** \def Board System timer */
#define BOARD_TIMER_TC      TC1
#define BOARD_TIMER_CHANNEL 0

/* =================== PIN CONSOLE definition ================== */

/** CONSOLE pin definition: use DBGU */
#define BOARD_CONSOLE_ADDR     DBGU
#define BOARD_CONSOLE_BAUDRATE 115200
#define BOARD_CONSOLE_TX_PIN   PIN_DBGU_TXD
#define BOARD_CONSOLE_RX_PIN   PIN_DBGU_RXD

/* =================== PIN LED definition ====================== */

/* RGB LED index */
#define LED_BLUE   0
#define LED_RED    1

/** LED #0 pin definition (Blue). */
#define PIN_LED_0 { PIO_GROUP_E, PIO_PE25, PIO_OUTPUT_1, PIO_DEFAULT }

/** LED #1 pin definition (Red). */
#define PIN_LED_1 { PIO_GROUP_E, PIO_PE24, PIO_OUTPUT_0, PIO_DEFAULT }

/** List of all LEDs definitions. */
#define PINS_LEDS { PIN_LED_0, PIN_LED_1 }

#define NUM_LEDS  2

/* =================== PIN PUSH BUTTON definition ============== */

#define PIO_CFG_PB  (PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE)
#define PIN_PUSHBUTTON_1 { PIO_GROUP_E, PIO_PE27, PIO_INPUT, PIO_CFG_PB }

/** List of all push button definitions. */
#define PINS_PUSHBUTTONS { PIN_PUSHBUTTON_1 }

/** Push button index. */
#define PUSHBUTTON_PB1 0

/* =================== USB device definition =================== */

/** USB VBus pin */
#define PIN_USB_VBUS \
	{ PIO_GROUP_D, PIO_PD29, PIO_INPUT, PIO_DEFAULT }

/** USB OverCurrent detection*/
#define PIN_USB_OVCUR \
	{ PIO_GROUP_D, PIO_PD28, PIO_INPUT, PIO_PULLUP }

/** USB Power Enable A:MicroAB:Active Low  */
#define PIN_USB_POWER_ENA \
	{ PIO_GROUP_D, PIO_PD25, PIO_OUTPUT_1, PIO_DEFAULT }

/** USB Power Enable B:A:Active Low  */
#define PIN_USB_POWER_ENB \
	{ PIO_GROUP_D, PIO_PD26, PIO_OUTPUT_1, PIO_DEFAULT }

/** USB Power Enable C:A:Active Low  */
#define PIN_USB_POWER_ENC \
	{ PIO_GROUP_D, PIO_PD27, PIO_OUTPUT_1, PIO_DEFAULT }

/** USB attributes configuration descriptor (bus or self powered,
 * remote wakeup) */
#define BOARD_USB_BMATTRIBUTES \
	USBConfigurationDescriptor_SELFPOWERED_NORWAKEUP

/* =================== HSMCI device definition ==================== */

/** HSMCI1 power control definition */
#define BOARD_HSMCI0_PIN_POWER \
	{ PIO_GROUP_B, PIO_PB10, PIO_OUTPUT_0, PIO_DEFAULT }

/** HSMCI0 Card detect pin definition */
#define BOARD_HSMCI0_PIN_CD \
	{ PIO_GROUP_D, PIO_PD17, PIO_INPUT, PIO_PULLUP }

/** HSMCI0 device interface pin set definition */
#define BOARD_HSMCI0_DEV_PINS \
	{ PIN_HSMCI0_CMD_A, PIN_HSMCI0_CK, PINS_HSMCI0_DATA8B_A }

/** HSMCI0 pin set definition */
#define BOARD_HSMCI0_PINS \
	{ PIN_HSMCI0_CMD_A, PIN_HSMCI0_CK, PINS_HSMCI0_DATA8B_A, \
	  BOARD_HSMCI0_PIN_CD, BOARD_HSMCI0_PIN_POWER }

/** HSMCI0 slot definition */
#define BOARD_HSMCI0_SLOT 0

/** HSMCI1 power control definition */
#define BOARD_HSMCI1_PIN_POWER \
	{ PIO_GROUP_B, PIO_PB12, PIO_OUTPUT_0, PIO_DEFAULT }

/** HSMCI1 Card detect pin definition */
#define BOARD_HSMCI1_PIN_CD \
	{ PIO_GROUP_D, PIO_PD18, PIO_INPUT, PIO_DEFAULT }

/** HSMCI1 device interface pin set definition */
#define BOARD_HSMCI1_DEV_PINS \
	{ PIN_HSMCI1_CMD_A, PIN_HSMCI1_CK, PINS_HSMCI1_DATA4B_A }

/** HSMCI1 pin set definition */
#define BOARD_HSMCI1_PINS \
	{ PIN_HSMCI1_CMD_A, PIN_HSMCI1_CK, PINS_HSMCI1_DATA4B_A, \
	  BOARD_HSMCI1_PIN_CD, BOARD_HSMCI1_PIN_POWER }

/** HSMCI1 slot definition */
#define BOARD_HSMCI1_SLOT 0

/* =================== ETH definition =================== */

#define BOARD_ETH0_PINS        PINS_GMAC0_RGMII
#define BOARD_ETH0_TYPE        ETH_TYPE_GMAC
#define BOARD_ETH0_ADDR        GMAC0
#define BOARD_ETH0_PHY_ADDR    7
#define BOARD_ETH0_PHY_IF      PHY_IF_GMAC
#define BOARD_ETH0_PHY_IRQ_PIN { PIO_GROUP_B, PIO_PB25, PIO_INPUT, PIO_PULLUP }
#define BOARD_ETH0_MAC_ADDR    {0x3a, 0x1f, 0x34, 0x08, 0x27, 0x27}

#define BOARD_ETH1_PINS        PINS_EMAC0
#define BOARD_ETH1_TYPE        ETH_TYPE_EMAC
#define BOARD_ETH1_ADDR        EMAC0
#define BOARD_ETH1_PHY_ADDR    1
#define BOARD_ETH1_PHY_IF      PHY_IF_EMAC
#define BOARD_ETH1_PHY_IRQ_PIN { PIO_GROUP_E, PIO_PE30, PIO_INPUT, PIO_PULLUP }
#define BOARD_ETH1_MAC_ADDR    {0x3a, 0x1f, 0x34, 0x08, 0x54, 0x54}

/* =================== NANDFLASH device definition =================== */

#define BOARD_NANDFLASH_PINS      PINS_NAND8
#define BOARD_NANDFLASH_BUS_WIDTH 8

/* =================== Display device definition =================== */

/** PIO pins for LCD */
#define BOARD_LCD_PINS              PINS_LCD_ALT

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

/* ================== TWI bus definition ====================== */

#define BOARD_TWI_BUS0      TWI1
#define BOARD_TWI_BUS0_FREQ 300000
#define BOARD_TWI_BUS0_PINS PINS_TWI1
#define BOARD_TWI_BUS0_MODE BUS_TRANSFER_MODE_DMA

/* ================== SPI bus definition ====================== */

#define BOARD_SPI_BUS0       SPI0
#define BOARD_SPI_BUS0_PINS  PINS_SPI0_NPCS0
#define BOARD_SPI_BUS0_MODE  BUS_TRANSFER_MODE_DMA

/* =================== ISI device definition =================== */

#define BOARD_ISI_TWI_BUS     BUS(BUS_TYPE_I2C, 0)
#define BOARD_ISI_PINS        PINS_ISI_8BIT
#define BOARD_ISI_RST_PIN     { PIO_GROUP_E, PIO_PE24, PIO_OUTPUT_1, PIO_DEFAULT }
#define BOARD_ISI_PWD_PIN     { PIO_GROUP_E, PIO_PE29, PIO_OUTPUT_1, PIO_DEFAULT }
#define BOARD_ISI_MCK_PCK     1
#define BOARD_ISI_MCK_PCK_SRC PMC_PCK_CSS_MCK
#define BOARD_ISI_MCK_PCK_DIV 3
#define BOARD_ISI_MCK_PIN     PIN_PCK1

/* ================== CAN bus definition ====================== */

#define BOARD_CAN_BUS0      CAN0
#define BOARD_CAN_BUS0_PINS PINS_CAN0
#define BOARD_CAN_BUS0_FREQ 1000000

#define BOARD_CAN_BUS1      CAN1
#define BOARD_CAN_BUS1_PINS PINS_CAN1
#define BOARD_CAN_BUS1_FREQ 1000000

/* =================== AT25 device definition =================== */

#define BOARD_AT25_BUS         BUS(BUS_TYPE_SPI, 0)
#define BOARD_AT25_CHIP_SELECT 0
#define BOARD_AT25_BITRATE     40000
#define BOARD_AT25_DLYBS       0
#define BOARD_AT25_DLYBCT      0
#define BOARD_AT25_SPI_MODE    SPID_MODE_0

/* ================== SSC definition ====================== */

#define BOARD_SSC0_PINS PINS_SSC0

/* ================== WM8904 definition ====================== */

#define BOARD_WM8904_TWI_BUS      BUS(BUS_TYPE_I2C, 0)
#define BOARD_WM8904_SLAVE_ADDR   0x1a
#define BOARD_WM8904_INPUT_PATH   (WM8904_INPUT_PATH_IN2L | WM8904_INPUT_PATH_IN2R)
#define BOARD_WM8904_MCLK_PCK     0
#define BOARD_WM8904_MCLK_PCK_SRC PMC_PCK_CSS_SLOW_CLK
#define BOARD_WM8904_MCLK_PIN     PIN_PCK0

#endif /* _BOARD_SAMA5D3_EK_H */
