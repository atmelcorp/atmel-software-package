/**
 * \page sam9xx5_ek_board_desc sam9xx5-ek - Board Description
 *
 * \section Purpose
 *
 * This file is dedicated to describe a ek sam9xx5 board.
 *
 * \section Contents
 *
 *  - sam9xx5-ek
 *  - For sam9xx5-ek information, see \subpage sam9xx5_ek_board_info.
 *  - For operating frequency information, see \subpage sam9xx5_ek_opfreq.
 *  - For using portable PIO definitions, see \subpage sam9xx5_ek_piodef.
 *  - For on-board memories, see \subpage sam9xx5_ek_mem.
 *  - Several USB definitions are included here, see \subpage sam9xx5_ek_usb.
 *  - For External components, see \subpage sam9xx5_ek_extcomp.
 *  - For Individual chip definition, see \subpage sam9xx5_ek_chipdef.
 *
 * To get more software details and the full list of parameters related to the
 * sam9xx5-ek board configuration, please have a look at the source file:
 * \ref board.h\n
 *
 * \section Usage
 *
 *  - The code for booting the board is provided by board_cstartup_xxx.c and
 *    board_lowlevel.c.
 *  - For using board PIOs, board characteristics (clock, etc.) and external
 *    components, see board.h.
 *  - For manipulating memories, see board_memories.h.
 *
 * This file can be used as a template and modified to fit a custom board, with
 * specific PIOs usage or memory connections.
 */

/**
 *  \file board.h
 *
 *  Definition of sam9xx5-ek
 *  characteristics, sama5d4-dependant PIOs and external components interfacing.
 */

#ifndef BOARD_SAM9XX5_EK_H_
#define BOARD_SAM9XX5_EK_H_

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
 * \page sam9xx5_ek_board_info "sam9xx5-ek - Board informations"
 * This page lists several definition related to the board description.
 *
 * \section Definitions
 * - \ref BOARD_NAME
 */

/** Name of the board */
#if defined(CONFIG_BOARD_SAM9G15_EK)
  #define BOARD_NAME "sam9g15-ek"
#elif defined(CONFIG_BOARD_SAM9G25_EK)
  #define BOARD_NAME "sam9g25-ek"
#elif defined(CONFIG_BOARD_SAM9G35_EK)
  #define BOARD_NAME "sam9g35-ek"
#elif defined(CONFIG_BOARD_SAM9X25_EK)
  #define BOARD_NAME "sam9x25-ek"
#elif defined(CONFIG_BOARD_SAM9X35_EK)
  #define BOARD_NAME "sam9x35-ek"
#endif

/*----------------------------------------------------------------------------*/

/** Frequency of the board main clock oscillator */
#define BOARD_MAIN_CLOCK_EXT_OSC 12000000

/** Definition of DDRAM's type */
#define BOARD_DDRAM_TYPE         MT47H64M16

/** Board DDR memory size in bytes */
#define BOARD_DDR_MEMORY_SIZE    128*1024*1024

/** \def Board System timer */
#define BOARD_TIMER_TC      TC1
#define BOARD_TIMER_CHANNEL 0

/* =================== PIN CONSOLE definition ================== */

/** CONSOLE pin definition: use DBGU */
#ifndef BOARD_CONSOLE_ADDR
#define BOARD_CONSOLE_ADDR     DBGU
#endif
#define BOARD_CONSOLE_BAUDRATE 115200
#ifndef BOARD_CONSOLE_TX_PIN
#define BOARD_CONSOLE_TX_PIN   PIN_DBGU_TXD
#endif
#ifndef BOARD_CONSOLE_RX_PIN
#define BOARD_CONSOLE_RX_PIN   PIN_DBGU_RXD
#endif

/* =================== PIN LED definition ====================== */

/* RGB LED index */
#define LED_BLUE   0
#define LED_RED    1

/** LED #0 pin definition (Blue). */
#define PIN_LED_0 { PIO_GROUP_B, PIO_PB18, PIO_OUTPUT_1, PIO_DEFAULT }

/** LED #1 pin definition (Red). */
#define PIN_LED_1 { PIO_GROUP_D, PIO_PD21, PIO_OUTPUT_0, PIO_DEFAULT }

/** List of all LEDs definitions. */
#define PINS_LEDS { PIN_LED_0, PIN_LED_1 }

#define NUM_LEDS  2

/* =================== USB device definition =================== */

/** USB VBus pin */
#define PIN_USB_VBUS \
	{ PIO_GROUP_B, PIO_PB16, PIO_INPUT, PIO_DEFAULT }

/** USB OverCurrent detection*/
#define PIN_USB_OVCUR \
	{ PIO_GROUP_B, PIO_PB17, PIO_INPUT, PIO_PULLUP }

/** USB Power Enable A:MicroAB:Active Low  */
#define PIN_USB_POWER_ENA \
	{ PIO_GROUP_D, PIO_PD18, PIO_OUTPUT_1, PIO_DEFAULT }

/** USB Power Enable B:A:Active Low  */
#define PIN_USB_POWER_ENB \
	{ PIO_GROUP_D, PIO_PD19, PIO_OUTPUT_1, PIO_DEFAULT }

/** USB Power Enable C:A:Active Low  */
#define PIN_USB_POWER_ENC \
	{ PIO_GROUP_D, PIO_PD20, PIO_OUTPUT_1, PIO_DEFAULT }

/** USB attributes configuration descriptor (bus or self powered,
 * remote wakeup) */
#define BOARD_USB_BMATTRIBUTES \
	USBConfigurationDescriptor_SELFPOWERED_NORWAKEUP

/* =================== HSMCI device definition ==================== */

/** HSMCI0 Card detect pin definition */
#define BOARD_HSMCI0_PIN_CD \
	{ PIO_GROUP_D, PIO_PD15, PIO_INPUT, PIO_DEFAULT }

/** HSMCI0 device interface pin set definition */
#define BOARD_HSMCI0_DEV_PINS \
	{ PIN_HSMCI0_CMD_A, PIN_HSMCI0_CK, PINS_HSMCI0_DATA4B_A }

/** HSMCI0 pin set definition */
#define BOARD_HSMCI0_PINS \
	{ PIN_HSMCI0_CMD_A, PIN_HSMCI0_CK, PINS_HSMCI0_DATA4B_A, \
	  BOARD_HSMCI0_PIN_CD }

/** HSMCI0 slot definition */
#define BOARD_HSMCI0_SLOT 0

/** HSMCI1 Card detect pin definition */
#define BOARD_HSMCI1_PIN_CD \
	{ PIO_GROUP_D, PIO_PD14, PIO_INPUT, PIO_DEFAULT }

/** HSMCI1 device interface pin set definition */
#define BOARD_HSMCI1_DEV_PINS \
	{ PIN_HSMCI1_CMD_A, PIN_HSMCI1_CK, PINS_HSMCI1_DATA4B_A }

/** HSMCI1 pin set definition */
#define BOARD_HSMCI1_PINS \
	{ PIN_HSMCI1_CMD_A, PIN_HSMCI1_CK, PINS_HSMCI1_DATA4B_A, \
	  BOARD_HSMCI1_PIN_CD }

/** HSMCI1 slot definition */
#define BOARD_HSMCI1_SLOT 0

/* =================== ETH0 definition =================== */

#define BOARD_ETH0_PINS        PINS_EMAC0_RMII
#define BOARD_ETH0_TYPE        ETH_TYPE_EMAC
#define BOARD_ETH0_ADDR        EMAC0
#define BOARD_ETH0_PHY_ADDR    0
#define BOARD_ETH0_PHY_IF      PHY_IF_EMAC
#define BOARD_ETH0_PHY_IRQ_PIN { PIO_GROUP_B, PIO_PB8, PIO_INPUT, PIO_PULLUP }

#define BOARD_ETH1_PINS        PINS_EMAC1_RMII
#define BOARD_ETH1_TYPE        ETH_TYPE_EMAC
#define BOARD_ETH1_ADDR        EMAC1
#define BOARD_ETH1_PHY_ADDR    0
#define BOARD_ETH1_PHY_IF      PHY_IF_GMAC
#define BOARD_ETH1_PHY_IRQ_PIN { PIO_GROUP_C, PIO_PC26, PIO_INPUT, PIO_PULLUP }
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

/* ================== SSC definition ====================== */

#define BOARD_SSC0_PINS PINS_SSC0

/* =================== ISI device definition =================== */

#define BOARD_ISI_TWI_BUS     BUS(BUS_TYPE_I2C, 0)
#define BOARD_ISI_PINS        PINS_ISI
#define BOARD_ISI_RST_PIN     { PIO_GROUP_A, PIO_PA7, PIO_OUTPUT_1, PIO_DEFAULT }
#define BOARD_ISI_PWD_PIN     { PIO_GROUP_A, PIO_PA13, PIO_OUTPUT_1, PIO_DEFAULT }
#define BOARD_ISI_MCK_PCK     0
#define BOARD_ISI_MCK_PCK_SRC PMC_PCK_CSS_PLLA_CLK
#define BOARD_ISI_MCK_PCK_DIV 4
#define BOARD_ISI_MCK_PIN     PIN_PCK0_ALT

/* ================== CAN bus definition ====================== */

#define BOARD_CAN_BUS0      CAN0
#define BOARD_CAN_BUS0_PINS PINS_CAN0
#define BOARD_CAN_BUS0_FREQ 1000000

#define BOARD_CAN_BUS1      CAN1
#define BOARD_CAN_BUS1_PINS PINS_CAN1
#define BOARD_CAN_BUS1_FREQ 1000000

/* ================== TWI bus definition ====================== */

#define BOARD_TWI_BUS0      TWI0
#define BOARD_TWI_BUS0_FREQ 400000
#define BOARD_TWI_BUS0_PINS PINS_TWI0
#define BOARD_TWI_BUS0_MODE BUS_TRANSFER_MODE_DMA

/* ================== SPI bus definition ====================== */

#define BOARD_SPI_BUS0       SPI0
#define BOARD_SPI_BUS0_PINS  PINS_SPI0_NPCS0
#define BOARD_SPI_BUS0_MODE  BUS_TRANSFER_MODE_DMA

/* =================== AT24 device definition =================== */

#define BOARD_AT24_TWI_BUS BUS(BUS_TYPE_I2C, 0)
#define BOARD_AT24_ADDR    0x51
#define BOARD_AT24_MODEL   AT24C512

/* =================== AT25 device definition =================== */

#define BOARD_AT25_BUS         BUS(BUS_TYPE_SPI, 0)
#define BOARD_AT25_CHIP_SELECT 0
#define BOARD_AT25_BITRATE     40000
#define BOARD_AT25_DLYBS       0
#define BOARD_AT25_DLYBCT      0
#define BOARD_AT25_SPI_MODE    SPID_MODE_0

/* ================== WM8731 definition ====================== */

#define BOARD_WM8731_TWI_BUS      BUS(BUS_TYPE_I2C, 0)
#define BOARD_WM8731_SLAVE_ADDR   0x1a
#define BOARD_WM8731_MCLK_PCK     0
#define BOARD_WM8731_MCLK_PCK_SRC PMC_PCK_CSS_MAIN_CLK
#define BOARD_WM8731_MCLK_PIN     PIN_PCK0

#endif /* BOARD_SAM9XX5_EK_H_ */
