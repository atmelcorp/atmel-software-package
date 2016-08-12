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

/** Frequency of the board slow clock oscillator */
#define BOARD_SLOW_CLOCK_EXT_OSC 32768

/** Frequency of the board main clock oscillator */
#define BOARD_MAIN_CLOCK_EXT_OSC 12000000

/** Definition of DDRAM's type */
#define BOARD_DDRAM_TYPE         MT47H64M16

/** Board DDR memory size in bytes */
#define BOARD_DDR_MEMORY_SIZE    128*1024*1024

/** Board timer tick resolution */
#define BOARD_TIMER_RESOLUTION   1000

/* =================== PIN CONSOLE definition ================== */
 
/** CONSOLE pin definition: use USART3 */
#define BOARD_CONSOLE_PINS     PINS_DBGU
#define BOARD_CONSOLE_ADDR     DBGU
#define BOARD_CONSOLE_BAUDRATE 115200
 
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

/* =================== EMAC0/PHY definition =================== */

#define EMAC0_ADDR        EMAC0
#define EMAC0_PINS        PINS_EMAC0_RMII
#define EMAC0_PHY_ADDR    0
#define EMAC0_PHY_IRQ_PIN { PIO_GROUP_B, PIO_PB8, PIO_INPUT, PIO_PULLUP }

/* =================== EMAC1/PHY definition =================== */

#define EMAC1_ADDR        EMAC1
#define EMAC1_PINS        PINS_EMAC1_RMII
#define EMAC1_PHY_ADDR    0
#define EMAC1_PHY_IRQ_PIN { PIO_GROUP_C, PIO_PC26, PIO_INPUT, PIO_PULLUP }

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

#define BOARD_ISI_TWI_BUS  0
#define BOARD_ISI_PINS     PINS_ISI
#define BOARD_ISI_RST_PIN  { PIO_GROUP_A, PIO_PA7, PIO_OUTPUT_1, PIO_DEFAULT }
#define BOARD_ISI_PWD_PIN  { PIO_GROUP_A, PIO_PA13, PIO_OUTPUT_1, PIO_DEFAULT }

/* ================== TWI bus definition ====================== */

#define BOARD_TWI_BUS0      TWI0
#define BOARD_TWI_BUS0_FREQ 400000
#define BOARD_TWI_BUS0_PINS PINS_TWI0

/* =================== AT24 device definition =================== */

#define BOARD_AT24_TWI_BUS  0
#define BOARD_AT24_DESC     {"AT24C512", 0xFFFF, 16}
#define BOARD_AT24_EEP_ADDR (0x50 | 0x1)

/* =================== AT25 device definition =================== */

#define BOARD_AT25_PINS     PINS_SPI0_NPCS0
#define BOARD_AT25_ADDR     SPI0
#define BOARD_AT25_CS       0
#define BOARD_AT25_ATTRS    (SPI_MR_MODFDIS | SPI_MR_WDRBT | SPI_MR_MSTR)
#define BOARD_AT25_FREQ     40000 /* (value in KHz) */
#define BOARD_AT25_DLYBS    0
#define BOARD_AT25_DLYCT    0
#define BOARD_AT25_SPI_MODE (SPI_CSR_NCPHA | SPI_CSR_BITS_8_BIT)

#endif /* BOARD_SAM9XX5_EK_H_ */
