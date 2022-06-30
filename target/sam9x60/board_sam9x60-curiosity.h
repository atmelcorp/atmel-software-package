/**
 * \page sam9x60_curiosity_board_desc sam9x60-curiosity - Board Description
 *
 * \section Purpose
 *
 * This file is dedicated to describe a sam9x60 curiosity board.
 *
 * \section Contents
 *
 *  - sam9x60-curiosity
 *  - For sam9x60-curiosity information, see \subpage sam9x60_curiosity_board_info.
 *  - For operating frequency information, see \subpage sam9x60_curiosity_opfreq.
 *  - For using portable PIO definitions, see \subpage sam9x60_curiosity_piodef.
 *  - For on-board memories, see \subpage sam9x60_curiosity_mem.
 *  - Several USB definitions are included here, see \subpage sam9x60_curiosity_usb.
 *  - For External components, see \subpage sam9x60_curiosity_extcomp.
 *  - For Individual chip definition, see \subpage sam9x60_curiosity_chipdef.
 *
 * To get more software details and the full list of parameters related to the
 * sam9x60-curiosity board configuration, please have a look at the source file:
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
 *  Definition of sam9x60-curiosity
 *  characteristics, chip-dependent PIOs and external components interfacing.
 */

#ifndef BOARD_SAM9x60_curiosity_H_
#define BOARD_SAM9x60_curiosity_H_

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
 * \page sam9x60_curiosity_board_info "sam9x60-curiosity - Board informations"
 * This page lists several definition related to the board description.
 *
 * \section Definitions
 * - \ref BOARD_NAME
 */

/** Name of the board */
#define BOARD_NAME "sam9x60-curiosity"

/*----------------------------------------------------------------------------*/

/** Frequency of the board main clock oscillator */
#define BOARD_MAIN_CLOCK_EXT_OSC 24000000

/** In SIP DDR2-SDRAM type */
#define BOARD_DDRAM_TYPE         W972GG6KB_16

/** PMC PLLA configuration */
#define BOARD_PMC_PLLA_MUL 49
#define BOARD_PMC_PLLA_DIV 1

/** PMC UPLL configuration */
#define BOARD_PMC_UPLL_MUL 39
#define BOARD_PMC_UPLL_DIV 1

/** In SIP DDR2-SDRAM size in bytes */
#define BOARD_DDR_MEMORY_SIZE    256*1024*1024

/** \def Board System timer */
#define BOARD_TIMER_TC      TC1
#define BOARD_TIMER_CHANNEL 0

/* =================== PIN CONSOLE definition ================== */

#ifndef CONFIG_HAVE_SERIALD_USART
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


#else
/** CONSOLE pin definition: use USART */
#ifndef BOARD_CONSOLE_ADDR
#define BOARD_CONSOLE_ADDR     FLEXUSART2
#endif
#define BOARD_CONSOLE_BAUDRATE 115200
#ifndef BOARD_CONSOLE_TX_PIN
#define BOARD_CONSOLE_TX_PIN   PIN_FLEXCOM2_IO0_IOS1
#endif
#ifndef BOARD_CONSOLE_RX_PIN
#define BOARD_CONSOLE_RX_PIN   PIN_FLEXCOM2_IO1_IOS1
#endif
#endif

/* =================== PIN LED definition ====================== */

/* RGB LED index */
#define LED_RED    0
#define LED_GREEN  1
#define LED_BLUE   2

/** LED #0 pin definition (red). */
#define PIN_LED_0 { PIO_GROUP_D, PIO_PD17, PIO_OUTPUT_1, PIO_DEFAULT }

/** LED #1 pin definition (green). */
#define PIN_LED_1 { PIO_GROUP_D, PIO_PD19, PIO_OUTPUT_1, PIO_DEFAULT }

/** LED #2 pin definition (blue). */
#define PIN_LED_2 { PIO_GROUP_D, PIO_PD21, PIO_OUTPUT_1, PIO_DEFAULT }

/** List of all LEDs definitions. */
#define PINS_LEDS { PIN_LED_0, PIN_LED_1, PIN_LED_2 }

#define NUM_LEDS  3

/* =============== CAN STAND BY PINS definition ================ */

/** CAN STNY PC9 for CAN0 */
#define CAN0_STBY_PC9 { PIO_GROUP_C, PIO_PC9, PIO_OUTPUT_0, PIO_DEFAULT }

/** CAN STNY PB17 for CAN1 */
#define CAN1_STBY_PB17 { PIO_GROUP_B, PIO_PB17, PIO_OUTPUT_0, PIO_DEFAULT }

/* =================== PIN PUSH BUTTON definition ============== */

#define PIN_PUSHBUTTON_1 { PIO_GROUP_D, PIO_PD18, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE }

/** List of all push button definitions. */
#define PINS_PUSHBUTTONS { PIN_PUSHBUTTON_1 }

/** Push button index. */
#define PUSHBUTTON_BP1 0

/* =================== USB device definition =================== */

/** USB-A port VBus detect pin */
#define PIN_USB_VBUS \
	{ PIO_GROUP_C, PIO_PC24, PIO_INPUT, PIO_IT_BOTH_EDGE }

/** USB attributes configuration descriptor (bus or self powered,
 * remote wakeup) */
#define BOARD_USB_BMATTRIBUTES \
	USBConfigurationDescriptor_SELFPOWERED_NORWAKEUP

/* =================== SDMMC device definition ==================== */

/** Card Detect (CD) line of the SD Card slot */
#define BOARD_SDMMC0_PIN_CD \
	{ PIO_GROUP_A, PIO_PA25, PIO_INPUT, PIO_DEFAULT | PIO_DEBOUNCE }

#define BOARD_SDMMC0_PINS { BOARD_SDMMC0_PIN_CD, PIN_SDMMC0_CK, \
                            PIN_SDMMC0_CMD, PINS_SDMMC0_DATA4B }

/* The relatively high capactive load of SD Cards requires strong drivers,
 * that we soften by enabling slew rate control. */
#define BOARD_SDMMC0_PIO_ATTR (PIO_CRTL_SLEWR | PIO_DRVSTR_HI)

#define BOARD_SDMMC0_CAPS0 (SDMMC_CA0R_V33VSUP | \
                            SDMMC_CA0R_SLTYPE_REMOVABLECARD)

/** Card Detect (CD) line of the SD Card slot */
#define BOARD_SDMMC1_PIN_CD \
	{ PIO_GROUP_C, PIO_PC8, PIO_INPUT, PIO_DEFAULT | PIO_DEBOUNCE }

/** Write Protect (WP) line of the SD Card slot */
#define BOARD_SDMMC1_PIN_WP \
	{ PIO_GROUP_A, PIO_PA14, PIO_INPUT, PIO_DEFAULT | PIO_DEBOUNCE }

#define BOARD_SDMMC1_PINS { PIN_SDMMC1_CK, \
                            BOARD_SDMMC1_PIN_CD, BOARD_SDMMC1_PIN_WP, \
                            PIN_SDMMC1_CMD, PINS_SDMMC1_DATA4B }

/* The relatively high capactive load of SD Cards requires strong drivers,
 * that we soften by enabling slew rate control. */
#define BOARD_SDMMC1_PIO_ATTR (PIO_CRTL_SLEWR | PIO_DRVSTR_HI)

#define BOARD_SDMMC1_CAPS0 (SDMMC_CA0R_V33VSUP | \
                            SDMMC_CA0R_SLTYPE_REMOVABLECARD)

/* =================== ETH0 definition =================== */

#define BOARD_ETH0_PINS        PINS_EMAC0_RMII
#define BOARD_ETH0_TYPE        ETH_TYPE_EMAC
#define BOARD_ETH0_ADDR        EMAC0
#define BOARD_ETH0_PHY_ADDR    1
#define BOARD_ETH0_PHY_IF      PHY_IF_EMAC
#define BOARD_ETH0_PHY_IRQ_PIN { PIO_GROUP_B, PIO_PB8, PIO_INPUT, PIO_PULLUP }
#define BOARD_ETH0_MAC_ADDR    {0x3a, 0x1f, 0x34, 0x08, 0x54, 0x53}

/* =================== NANDFLASH device definition =================== */

#define BOARD_NANDFLASH_PINS      PINS_NAND8
#define BOARD_NANDFLASH_BUS_WIDTH 8

/* =================== Display device definition =================== */

/* SAM9X60-Curiosity REV 1,2,3 have an on-board RGB to MIPI DSI Display
 * Interface Bridge and a MIPI-DSI connector.
 * SAM9X60-Curiosity REV 4 has a RGB666 (18-bit data) parallel LCD connector. */

/** PIO pins for LCD */
#define BOARD_LCD_PINS            PINS_LCD_IOS2

/** Display width in pixels. */
#define BOARD_LCD_WIDTH           800
/** Display height in pixels. */
#define BOARD_LCD_HEIGHT          480
/** Frame rate in Hz. */
#define BOARD_LCD_FRAMERATE       40

/** Vertical front porch in number of lines. */
#define BOARD_LCD_TIMING_VFP      22
/** Vertical back porch in number of lines. */
#define BOARD_LCD_TIMING_VBP      21
/** Vertical pulse width in number of lines. */
#define BOARD_LCD_TIMING_VPW      2
/** Horizontal front porch in LCDDOTCLK cycles. */
#define BOARD_LCD_TIMING_HFP      64
/** Horizontal back porch in LCDDOTCLK cycles. */
#define BOARD_LCD_TIMING_HBP      64
/** Horizontal pulse width in LCDDOTCLK cycles. */
#define BOARD_LCD_TIMING_HPW      128

/* ================== CAN bus definition ====================== */

#define BOARD_CAN_BUS0      CAN0
#define BOARD_CAN_BUS0_PINS PINS_CAN0
#define BOARD_CAN_BUS0_FREQ 1000000

#define BOARD_CAN_BUS1      CAN1
#define BOARD_CAN_BUS1_PINS PINS_CAN1
#define BOARD_CAN_BUS1_FREQ 1000000

/* ================== TWI bus definition ====================== */

#define BOARD_TWI_BUS0      FLEXTWI0
#define BOARD_TWI_BUS0_FREQ 400000
#define BOARD_TWI_BUS0_PINS PINS_FLEXCOM0_TWI_IOS1
#define BOARD_TWI_BUS0_MODE BUS_TRANSFER_MODE_DMA

#define BOARD_TWI_BUS1      FLEXTWI6
#define BOARD_TWI_BUS1_FREQ 400000
#define BOARD_TWI_BUS1_PINS PINS_FLEXCOM6_TWI_IOS1
#define BOARD_TWI_BUS1_MODE BUS_TRANSFER_MODE_DMA

/* ================== SPI bus definition ====================== */

#define BOARD_SPI_BUS0       FLEXSPI4
#define BOARD_SPI_BUS0_PINS  PINS_FLEXCOM4_SPI_NPCS0_IOS1
#define BOARD_SPI_BUS0_MODE  BUS_TRANSFER_MODE_DMA

#define BOARD_SPI_BUS1       FLEXSPI5
#define BOARD_SPI_BUS1_PINS  PINS_FLEXCOM5_SPI_NPCS0_IOS1
#define BOARD_SPI_BUS1_MODE  BUS_TRANSFER_MODE_DMA

/* =================== AT24 device definition =================== */

#define BOARD_AT24_TWI_BUS BUS(BUS_TYPE_I2C, 0)
#define BOARD_AT24_ADDR    0x53
#define BOARD_AT24_MODEL   MCP24AA025E48

#endif /* BOARD_SAM9x60_curiosity_H_ */

