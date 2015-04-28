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

/**
 * \if document_A5D4_EK
 * \page sama5d4_board_desc SAMA5D4-EK - Board Description
 * \section Purpose
 *
 * This file is dedicated to describe the SAMA5D4 Evaluation Kit (SAMA5D4-EK) board.
 * \elseif document_A5D4_XULT
 * \page sama5d4_board_desc SAMA5D4-XULT - Board Description
 *
 * \section Purpose
 *
 * This file is dedicated to describe the SAMA5D4 Xplained Ultra (SAMA5D4-XULT) board.
 * \endif
 *
 * \section Contents
 *
 *  - For SAMA5D4-EK information, see \subpage sama5d4_board_info.
 *  - For operating frequency information, see \subpage sama5d4_board_opfreq.
 *  - For using portable PIO definitions, see \subpage sama5d4_board_piodef.
 *  - For on-board memories, see \subpage sama5d4_board_mem.
 *  - Several USB definitions are included here, see \subpage sama5d4_board_usb.
 *  - For External components, see \subpage sama5d4_board_extcomp.
 *  - For Individual chip definition, see \subpage sama5d4_board_chipdef.
 *
 * To get more software details and the full list of parameters related to the
 * board configuration, please have a look at the source file:
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
 *  Definition of \ref sama5d4_board_desc "the board"
 *  characteristics, sama5d4-dependent PIOs and external components interfacing.
 */

#ifndef _BOARD_SAMA5D4_COMMON_HEADER_
#define _BOARD_SAMA5D4_COMMON_HEADER_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "chip.h"

/**
 * Libc porting layers
 */
#if defined   ( __CC_ARM   )	/* Keil uvision 4 */
#include "include/rand.h"
#elif defined ( __ICCARM__ )	/* IAR Ewarm 5.41+ */
#include "include/rand.h"
#elif defined (  __GNUC__  )	/* GCC CS3 2009q3-68/2010q1-188 */
#include "rand.h"
#include "syscalls.h"	  /** RedHat Newlib minimal stub */
#endif

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
 * \if document_A5D4_EK
 * \page sama5d4_board_info "SAMA5D4-EK - Board informations"
 * \elseif document_A5D4_XULT
 * \page sama5d4_board_info "SAMA5D4-XULT - Board informations"
 * \endif
 * This page lists several definition related to the board description.
 *
 * \section Definitions
 * - \ref BOARD_NAME
 */

#if defined(BOARD_SAMA5D4_EK)
/** Name of the board */
#define BOARD_NAME "SAMA5D4-EK"
#elif defined(BOARD_SAMA5D4_XPLAINED)
/** Name of the board */
#define BOARD_NAME "SAMA5D4-XPLAINED"
#endif

/** Family definition (already defined) */
#if !defined sama5d4
#define sama5d4
#endif
/** Core definition */
#define cortexa5

/*----------------------------------------------------------------------------*/
/**
 * \if document_A5D4_EK
 *  \page sama5d4_board_opfreq "SAMA5D4-EK - Operating frequencies"
 * \elseif document_A5D4_XULT
 *  \page sama5d4_board_opfreq "SAMA5D4-XULT - Operating frequencies"
 * \endif
 *  This page lists several definition related to the board operating frequency
 *  (when using the initialization done by board_lowlevel.c).
 *
 *  \section Definitions
 *  - \ref BOARD_MAINOSC
 *  - \ref BOARD_MCK
 */

/** Frequency of the board main oscillator */
#define BOARD_MAINOSC           12000000

/** Master clock frequency (when using board_lowlevel.c) */
#define BOARD_MCK               ((unsigned long)((BOARD_MAINOSC / 3 / 2) * 88 ))

/*----------------------------------------------------------------------------*/
/**
 * \if document_A5D4_EK
 * \page sama5d4_board_piodef "SAMA5D4-EK - PIO definitions"
 * \elseif document_A5D4_XULT
 * \page sama5d4_board_piodef "SAMA5D4-XULT - PIO definitions"
 * \endif
 * This pages lists all the pio definitions contained in board.h. The constants
 * are named using the following convention: PIN_* for a constant which defines
 * a single Pin instance (but may include several PIOs sharing the same
 * controller), and PINS_* for a list of Pin instances.
 *
 * DBGU
 * - \ref PINS_DBGU
 *
 * USART0
 * - \ref PIN_USART0_TXD
 * - \ref PIN_USART0_RXD
 * - \ref PIN_USART0_RTS
 * - \ref PIN_USART0_CTS
 * - \ref PIN_USART0_SCK
 *
 * TWI0
 * - \ref PIN_TWI_TWD0
 * - \ref PIN_TWI_TWCK0
 * - \ref PINS_TWI0
 *
 * SPI0
 * - \ref PIN_SPI0_MISO
 * - \ref PIN_SPI0_MOSI
 * - \ref PIN_SPI0_SPCK
 * - \ref PIN_SPI0_NPCS0
 * - \ref PINS_SPI0
 *
 * SSC
 * - \ref PIN_SSC_TD0   \ref PIN_SSC_TD1
 * - \ref PIN_SSC_TK0   \ref PIN_SSC_TK1
 * - \ref PIN_SSC_TF0   \ref PIN_SSC_TF1
 * - \ref PIN_SSC_RD0   \ref PIN_SSC_RD1
 * - \ref PIN_SSC_RK0   \ref PIN_SSC_RK1
 * - \ref PIN_SSC_RF0   \ref PIN_SSC_RF1
 * - \ref PINS_SSC_CODEC
 *
 * EMAC0
 * - \ref PIN_EMAC0_TXCK
 * - \ref PIN_EMAC0_TX0
 * - \ref PIN_EMAC0_TX1
 * - \ref PIN_EMAC0_TX2
 * - \ref PIN_EMAC0_TX3
 * - \ref PIN_EMAC0_TXEN
 * - \ref PIN_EMAC0_RXER
 * - \ref PIN_EMAC0_RXDV
 * - \ref PIN_EMAC0_RX0
 * - \ref PIN_EMAC0_RX1
 * - \ref PIN_EMAC0_RX2
 * - \ref PIN_EMAC0_RX3
 * - \ref PIN_EMAC0_MDC
 * - \ref PIN_EMAC0_MDIO
 * - \ref PIN_EMAC0_INTR
 * - \ref PINS_EMAC0_MII
 * - \ref PINS_EMAC0_RMII
 * LCD
 * - \ref PINS_LCD
 *
 * ADC
 * - \ref PIN_ADTRG
 *
 * ISI
 * - \ref PIN_ISI_MCK
 * - \ref BOARD_ISI_VSYNC
 * - \ref BOARD_ISI_HSYNC
 * - \ref BOARD_ISI_PCK
 * - \ref BOARD_ISI_PINS_DATA
 * - \ref PINS_ISI
 */

/** List of all DBGU pin definitions. */

/** DBGU Monitor IO pin (detect any DBGU operation). */
#define PIN_DBGU_MON {PIO_PB24A_DRXD, PIOB, ID_PIOB, PIO_INPUT, PIO_IT_RISE_EDGE}
/** DBGU pin definition. */
#define PINS_DBGU   {PIO_PB24A_DRXD | PIO_PB25A_DTXD, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}

/** List of all USART pin definitions. */

/** USART0 TXD pin definition. */
#define PIN_USART0_TXD  {PIO_PD13A_TXD0, PIOD, ID_PIOD, PIO_PERIPH_A, PIO_DEFAULT}
/** USART0 RXD pin definition. */
#define PIN_USART0_RXD  {PIO_PD12A_RXD0, PIOD, ID_PIOD, PIO_PERIPH_A, PIO_DEFAULT}
/** USART0 RTS pin definition. */
#define PIN_USART0_RTS  {PIO_PD11A_RTS0, PIOD, ID_PIOD, PIO_PERIPH_A, PIO_DEFAULT}
/** USART0 CTS pin definition. */
#define PIN_USART0_CTS  {PIO_PD10A_CTS0, PIOD, ID_PIOD, PIO_PERIPH_A, PIO_DEFAULT}
/** USART0 SCK pin definition. */
#define PIN_USART0_SCK  {PIO_PD28A_SCK0, PIOD, ID_PIOD, PIO_PERIPH_A, PIO_DEFAULT}

/** USART1 TXD pin definition. */
#define PIN_USART1_TXD  {PIO_PD17A_TXD1, PIOD, ID_PIOD, PIO_PERIPH_A, PIO_DEFAULT}
/** USART1 RXD pin definition. */
#define PIN_USART1_RXD  {PIO_PD16A_RXD1, PIOD, ID_PIOD, PIO_PERIPH_A, PIO_DEFAULT}
/** USART1 RTS pin definition. */
#define PIN_USART1_RTS  {PIO_PD15A_RTS1, PIOD, ID_PIOD, PIO_PERIPH_A, PIO_DEFAULT}
/** USART1 CTS pin definition. */
#define PIN_USART1_CTS  {PIO_PD14A_CTS1, PIOD, ID_PIOD, PIO_PERIPH_A, PIO_DEFAULT}
/** USART1 SCK pin definition. */
#define PIN_USART1_SCK  {PIO_PD29A_SCK1, PIOD, ID_PIOD, PIO_PERIPH_A, PIO_DEFAULT}

/** USART2 TXD pin definition. */
#define PIN_USART2_TXD  {PIO_PE26B_TXD2, PIOE, ID_PIOE, PIO_PERIPH_B, PIO_DEFAULT}
/** USART2 RXD pin definition. */
#define PIN_USART2_RXD  {PIO_PE25B_RXD2, PIOE, ID_PIOE, PIO_PERIPH_B, PIO_DEFAULT}
/** USART2 RTS pin definition. */
#define PIN_USART2_RTS  {PIO_PE24B_RTS2, PIOE, ID_PIOE, PIO_PERIPH_B, PIO_DEFAULT}
/** USART2 CTS pin definition. */
#define PIN_USART2_CTS  {PIO_PE23B_CTS2, PIOE, ID_PIOE, PIO_PERIPH_B, PIO_DEFAULT}
/** USART2 SCK pin definition. */
#define PIN_USART2_SCK  {PIO_PE20B_SCK2, PIOE, ID_PIOE, PIO_PERIPH_B, PIO_DEFAULT}

/** USART3 TXD pin definition. */
#define PIN_USART3_TXD  {PIO_PE17B_TXD3, PIOE, ID_PIOE, PIO_PERIPH_B, PIO_DEFAULT}
/** USART3 RXD pin definition. */
#define PIN_USART3_RXD  {PIO_PE16B_RXD3, PIOE, ID_PIOE, PIO_PERIPH_B, PIO_DEFAULT}
/** USART3 SCK pin definition. */
#define PIN_USART3_SCK  {PIO_PE15B_SCK3, PIOE, ID_PIOE, PIO_PERIPH_B, PIO_DEFAULT}

/** USART4 TXD pin definition. */
//#define PIN_USART4_TXD  {PIO_PE27B_TXD4, PIOE, ID_PIOE, PIO_PERIPH_B, PIO_DEFAULT}
/** USART4 RXD pin definition. */
//#define PIN_USART4_RXD  {PIO_PE26B_RXD4, PIOE, ID_PIOE, PIO_PERIPH_B, PIO_DEFAULT}
/** USART4 RTS pin definition. */
//#define PIN_USART4_RTS  {PIO_PE28B_RTS4, PIOE, ID_PIOE, PIO_PERIPH_B, PIO_DEFAULT}
/** USART4 CTS pin definition. */
//#define PIN_USART4_CTS  {PIO_PE0C_CTS4, PIOE, ID_PIOE, PIO_PERIPH_C, PIO_DEFAULT}
/** USART4 SCK pin definition. */
//#define PIN_USART4_SCK  {PIO_PE25B_SCK4, PIOE, ID_PIOE, PIO_PERIPH_B, PIO_DEFAULT}

/** PIN used for reset the smartcard */
#define PIN_ISO7816_RSTMC       {1 << 10, PIOD, ID_PIOD, PIO_OUTPUT_0, PIO_DEFAULT}
/** Pins used for connect the smartcard */
#define PINS_ISO7816            PIN_USART1_TXD, PIN_USART1_SCK,PIN_ISO7816_RSTMC

/** List of all TWI pin definitions. */

/** TWI0 data pin */
#define PIN_TWI_TWD0   {PIO_PA30A_TWD0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** TWI0 clock pin */
#define PIN_TWI_TWCK0  {PIO_PA31A_TWCK0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** TWI0 pins */
#define PINS_TWI0      PIN_TWI_TWD0, PIN_TWI_TWCK0

/** TWI1 data pin */
#define PIN_TWI_TWD1   {PIO_PE29C_TWD1, PIOE, ID_PIOE, PIO_PERIPH_C, PIO_DEFAULT}
/** TWI1 clock pin */
#define PIN_TWI_TWCK1  {PIO_PE30C_TWCK1, PIOE, ID_PIOE, PIO_PERIPH_C, PIO_DEFAULT}
/** TWI1 pins */
#define PINS_TWI1      PIN_TWI_TWD1, PIN_TWI_TWCK1

/** TWI2 data pin */
#define PIN_TWI_TWD2   {PIO_PB29A_TWD2, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
/** TWI2 clock pin */
#define PIN_TWI_TWCK2  {PIO_PB30A_TWCK2, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
/** TWI2 pins */
#define PINS_TWI2      PIN_TWI_TWD2, PIN_TWI_TWCK2

/** TWI3 data pin */
#define PIN_TWI_TWD3   {PIO_PC25B_TWD3, PIOC, ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT}
/** TWI3 clock pin */
#define PIN_TWI_TWCK3  {PIO_PC26B_TWCK3, PIOC, ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT}
/** TWI3 pins */
#define PINS_TWI3      PIN_TWI_TWD3, PIN_TWI_TWCK3

/** List of all CAN pin definitions. */
/** CAN0 pin TX */
#define PIN_CAN0_TX     {PIO_PD15C_CANTX0, PIOD, ID_PIOD, PIO_PERIPH_C, PIO_DEFAULT}
/** CAN0 pin RX */
#define PIN_CAN0_RX     {PIO_PD14C_CANRX0, PIOD, ID_PIOD, PIO_PERIPH_C, PIO_DEFAULT}
/** CAN0 pins */
#define PINS_CAN0       PIN_CAN0_TX, PIN_CAN0_RX
/** CAN1 pin TX */
#define PIN_CAN1_TX     {PIO_PB15B_CANTX1, PIOB, ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
/** CAN1 pin RX */
#define PIN_CAN1_RX     {PIO_PB14B_CANRX1, PIOB, ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
/** CAN0 pins */
#define PINS_CAN1       PIN_CAN1_TX, PIN_CAN1_RX

/** List of all SPI pin definitions. */

/** SPI0 MISO pin definition. */
#define PIN_SPI0_MISO     {PIO_PC0A_SPI0_MISO, PIOC, ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}
/** SPI0 MOSI pin definition. */
#define PIN_SPI0_MOSI     {PIO_PC1A_SPI0_MOSI, PIOC, ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}
/** SPI0 SPCK pin definition. */
#define PIN_SPI0_SPCK     {PIO_PC2A_SPI0_SPCK, PIOC, ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}
/** SPI0 chip select pin definition. */
#define PIN_SPI0_NPCS0    {PIO_PC3A_SPI0_NPCS0, PIOC, ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}
/** List of SPI0 pin definitions (MISO, MOSI & SPCK). */
#define PINS_SPI0         PIN_SPI0_MISO, PIN_SPI0_MOSI, PIN_SPI0_SPCK

/** SPI1 MISO pin definition. */
#define PIN_SPI1_MISO     {PIO_PB18A_SPI1_MISO, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
/** SPI1 MOSI pin definition. */
#define PIN_SPI1_MOSI     {PIO_PB19A_SPI1_MOSI, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
/** SPI1 SPCK pin definition. */
#define PIN_SPI1_SPCK     {PIO_PB20A_SPI1_SPCK, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
/** SPI1 chip select pin definition. */
#define PIN_SPI1_NPCS0    {PIO_PB21A_SPI1_NPCS0, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
/** SPI1 chip select pin definition. */
#define PIN_SPI1_NPCS2    {PIO_PB23A_SPI1_NPCS2, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
/** List of SPI1 pin definitions (MISO, MOSI & SPCK). */
#define PINS_SPI1         PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SPCK

/** SPI2 MISO pin definition. */
#define PIN_SPI2_MISO     {PIO_PD11B_SPI2_MISO, PIOD, ID_PIOD, PIO_PERIPH_B, PIO_DEFAULT}
/** SPI2 MOSI pin definition. */
#define PIN_SPI2_MOSI     {PIO_PD13B_SPI2_MOSI, PIOD, ID_PIOD, PIO_PERIPH_B, PIO_DEFAULT}
/** SPI2 SPCK pin definition. */
#define PIN_SPI2_SPCK     {PIO_PD15B_SPI2_SPCK, PIOD, ID_PIOD, PIO_PERIPH_B, PIO_DEFAULT}
/** SPI2 chip select 0 pin definition. */
#define PIN_SPI2_NPCS0    {PIO_PD17B_SPI2_NPCS0, PIOD, ID_PIOD, PIO_PERIPH_B, PIO_DEFAULT}
/** SPI2 chip select 1 pin definition. */
#define PIN_SPI2_NPCS1    {PIO_PB14B_SPI2_NPCS1, PIOB, ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
/** List of SPI1 pin definitions (MISO, MOSI & SPCK). */
#define PINS_SPI2         PIN_SPI2_MISO, PIN_SPI2_MOSI, PIN_SPI2_SPCK

/** List of all SSC pin definitions. */

/** SSC pin Transmitter Data (TD) */
#define PIN_SSC_TD0      {PIO_PB28B_TD0, PIOB, ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
/** SSC pin Transmitter Clock (TK) */
#define PIN_SSC_TK0      {PIO_PB27B_TK0, PIOB, ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
/** SSC pin Transmitter FrameSync (TF) */
#define PIN_SSC_TF0      {PIO_PB31B_TF0, PIOB, ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
/** SSC pin RD */
#define PIN_SSC_RD0      {PIO_PB29B_RD0, PIOB, ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
/** SSC pin RK */
#define PIN_SSC_RK0      {PIO_PB26B_RK0, PIOB, ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
/** SSC pin RF */
#define PIN_SSC_RF0      {PIO_PB30B_RF0, PIOB, ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}

/** SSC pin Transmitter Data (TD) */
#define PIN_SSC_TD1      {0x1 << 21, PIOC, ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT}
/** SSC pin Transmitter Clock (TK) */
#define PIN_SSC_TK1      {0x1 << 19, PIOC, ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT}
/** SSC pin Transmitter FrameSync (TF) */
#define PIN_SSC_TF1      {0x1 << 20, PIOC, ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT}
/** SSC pin RD */
#define PIN_SSC_RD1      {0x1 << 23, PIOC, ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT}
/** SSC pin RK */
#define PIN_SSC_RK1      {0x1 << 24, PIOC, ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT}
/** SSC pin RF */
#define PIN_SSC_RF1      {0x1 << 22, PIOC, ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT}

/** SSC pins definition for codec. */
#define PINS_SSC_CODEC   PIN_SSC_TD0,  PIN_SSC_TK0, PIN_SSC_TF0, PIN_SSC_RD0,  PIN_SSC_RK0, PIN_SSC_RF0

/** LCD pin list. */
#define PINS_LCD_PIOA   {0x3FFEFEFE, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}
/** LCD pin list. */
#define PINS_LCD        PINS_LCD_PIOA
/** ADC ADTRG pin (PD19). */
#define PIN_ADTRG       {PIO_PE31A_ADTRG, PIOE, ID_PIOE, PIO_PERIPH_A, PIO_PULLUP}

/** CONSOLE pin definition, Use only USART */
#define CONSOLE_DRIVER          DRV_DBGU
#define PINS_CONSOLE            {PIN_USART3_TXD,PIN_USART3_RXD}
#define CONSOLE_PER_ADD         USART3
#define CONSOLE_ID              ID_USART3
#define CONSOLE_BAUDRATE        115200


/*----------------------------------------------------------------------------*/
/**
 * \if document_A5D4_EK
 * \page sama5d4_board_usb "SAMA5D4-EK - USB device"
 * \elseif document_A5D4_XULT
 * \page sama5d4_board_usb "SAMA5D4-XULT - USB device"
 * \endif
 *
 * \section Definitions
 * - \ref BOARD_USB_BMATTRIBUTES
 * - \ref CHIP_USB_UDP
 * - \ref CHIP_USB_PULLUP_INTERNAL
 * - \ref CHIP_USB_NUMENDPOINTS
 * - \ref CHIP_USB_ENDPOINTS_MAXPACKETSIZE
 * - \ref CHIP_USB_ENDPOINTS_BANKS
 */

/** USB VBus pin */
#define PIN_USB_VBUS      {PIO_PE31, PIOE, ID_PIOE, PIO_INPUT, PIO_DEFAULT}

/** USB attributes configuration descriptor (bus or self powered, remote wakeup) */
#define BOARD_USB_BMATTRIBUTES   USBConfigurationDescriptor_SELFPOWERED_NORWAKEUP

/*----------------------------------------------------------------------------*/
/**
 * \if document_A5D4_EK
 * \page sama5d4_board_mem "SAMA5D4-EK - Memories"
 * \elseif document_A5D4_XULT
 * \page sama5d4_board_mem "SAMA5D4-XULT - Memories"
 * \endif
 * This page lists definitions related to internal & external on-board memories.
 *
 * \section Sdram
 *
 * - \ref EBI_SDRAM_PINS
 *
 * \section Nandflash
 * - \ref PINS_NANDFLASH
 * - \ref BOARD_NF_IO_PINS
 * - \ref BOARD_NF_CE_PIN
 * - \ref BOARD_NF_RB_PIN
 */

/** Nandflash IO pin definition.*/
#define BOARD_NF_IO_PINS        {0x0007FFE0, PIOC, ID_PIOC, PIO_PERIPH_A, PIO_PULLUP}
/** Nandflash chip enable pin definition. */
#define BOARD_NF_CE_PIN         {0, 0, 0, 0, 0}
/** Nandflash controller peripheral pins definition. */
#define PINS_NANDFLASH          BOARD_NF_IO_PINS

/** Address for transferring command bytes to the nandflash, CLE A22*/
#define BOARD_NF_COMMAND_ADDR   0x80400000
/** Address for transferring address bytes to the nandflash, ALE A21*/
#define BOARD_NF_ADDRESS_ADDR   0x80200000
/** Address for transferring data bytes to the nandflash.*/
#define BOARD_NF_DATA_ADDR      0x80000000

/** Address for transferring command bytes to the norflash. */
#define BOARD_NORFLASH_ADDR     0x10000000
/** Default NOR bus size after power up reset */
#define BOARD_NORFLASH_DFT_BUS_SIZE 16

/** Ddram type MT47H128M8CF */
#define DDRAM_MT47H128M8CF    0
/** Ddram type MT47H128M16RT */
#define DDRAM_MT47H128M16   1

/** PHY address */
#define BOARD_EMAC_PHY_ADDR         1
/** PHY Component */
#define BOARD_EMAC_PHY_COMP_KSZ8051RNL 1
/** Board EMAC power control - ALWAYS ON */
#define BOARD_EMAC_POWER_ALWAYS_ON
/** Board EMAC work mode - RMII/MII ( 1 / 0 ) */
#define BOARD_EMAC_MODE_RMII        1

/** The PIN list of PIO for EMAC */
#define BOARD_EMAC_PINS          {0x3FF, PIOC, ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT},\
                                 {(1<<30),PIOE, ID_PIOE, PIO_INPUT, PIO_PULLUP}

/** The runtime pin configure list for EMAC */
#define BOARD_EMAC_RUN_PINS BOARD_EMAC_PINS

/** PHY address */
#define BOARD_GMAC_PHY_ADDR         0
#define BOARD_GMAC_PHY_COMP_KSZ9021RNL 1
#define BOARD_GMAC_PHY_COMP_KSZ8081RNL 1
#define BOARD_GMAC_POWER_ALWAYS_ON
#define BOARD_GMAC_MODE_RGMII        1

/// The PIN list of PIO for EMAC
#define BOARD_GMAC_PINS0          {0x333C5, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT},\
                                  {(1<<6),PIOE, ID_PIOE, PIO_INPUT,    PIO_PULLUP}
/// The runtime pin configure list for EMAC
#define BOARD_GMAC_RUN_PINS0 BOARD_GMAC_PINS0

/// The PIN list of PIO for EMAC
#define BOARD_GMAC_PINS1          {0xC0FC14, PIOA, ID_PIOA, PIO_PERIPH_B, PIO_DEFAULT},\
                                  {(1<<7),PIOE, ID_PIOE, PIO_INPUT,    PIO_PULLUP}
/// The runtime pin configure list for EMAC
#define BOARD_GMAC_RUN_PINS1 BOARD_GMAC_PINS1

/*----------------------------------------------------------------------------*/
/**
 * \if document_A5D4_EK
 * \page sama5d4_board_extcomp "SAMA5D4-EK - External components"
 * This page lists the definitions related to external on-board components
 * located in the board.h file for \ref sama5d4_board_desc "SAMA5D4-EK".
 * \elseif document_A5D4_XULT
 * \page sama5d4_board_extcomp "SAMA5D4-XULT - External components"
 * This page lists the definitions related to external on-board components
 * located in the board.h file for \ref sama5d4_board_desc "SAMA5D4-XULT".
 * \endif
 *
 * \section board_sdmmc SD/MMC
 * - \ref BOARD_MCI0_PINS
 * - \ref BOARD_MCI0_PIN_CD
 * - \ref BOARD_MCI1_PINS
 * - \ref BOARD_MCI1_PIN_CD
 * - \ref BOARD_NUM_MCI
 *
 * \section board_emac EMAC
 * - \ref BOARD_EMAC_RST_PINS
 * - \ref BOARD_EMAC_PHY_ADDR
 * - \ref BOARD_EMAC_RUN_PINS
 *
 * \section board_lcd LCD Properties
 * - \ref BOARD_LCD_WIDTH
 * - \ref BOARD_LCD_HEIGHT
 * - \ref BOARD_LCD_IFWIDTH
 * - \ref BOARD_LCD_FRAMESIZE
 * - \ref BOARD_LCD_TIMING_VFP
 * - \ref BOARD_LCD_TIMING_VBP
 * - \ref BOARD_LCD_TIMING_VPW
 * - \ref BOARD_LCD_TIMING_HFP
 * - \ref BOARD_LCD_TIMING_HBP
 * - \ref BOARD_LCD_TIMING_HPW
 * - \ref BOARD_LCD_FRAMERATE
 * - \ref BOARD_LCD_PIXELCLOCK
 *
 * \section board_ts Touchscreen ADC Properties
 * - \ref BOARD_TOUCHSCREEN_ADCCLK
 * - \ref BOARD_TOUCHSCREEN_STARTUP
 * - \ref BOARD_TOUCHSCREEN_SHTIM
 * - \ref BOARD_TOUCHSCREEN_DEBOUNCE
 */

/** MCI0 Clock . */
#define BOARD_MCI0_PIN_CK       {PIO_PC4, PIOC, ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT}

/** MCI0 Solt A IO pins definition. (PC4-PC13) */
#define BOARD_MCI0_PINS_SLOTA   {0x3FF0, PIOC, ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT}
//MCI0_CDB PE0, MCI0_DB0, MCI0_DB1,MCI0_DB2, MCI0_DB3

/** MCI0 IO pins definition. */
#define BOARD_MCI0_PINS        BOARD_MCI0_PINS_SLOTA
/** MCI1 IO pins definition. (PE18-PE23) */
#define BOARD_MCI1_PINS        {0xFC0000, PIOE, ID_PIOE, PIO_PERIPH_C, PIO_DEFAULT}

/** Total number of MCI interface */
#define BOARD_NUM_MCI           2

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

/** Pixel clock rate in Hz (HS period * VS period * BOARD_LCD_FRAMERATE). */
#define BOARD_LCD_PIXELCLOCK        ((BOARD_LCD_TIMING_HPW+BOARD_LCD_TIMING_HBP+BOARD_LCD_WIDTH+BOARD_LCD_TIMING_HFP)\
                                    *(BOARD_LCD_TIMING_VPW+BOARD_LCD_TIMING_VBP+BOARD_LCD_HEIGHT+BOARD_LCD_TIMING_VFP)\
                                    *BOARD_LCD_FRAMERATE)

/** Image Sensor Interface vertical sync. */
#define BOARD_ISI_VSYNC     {PIO_PB3C_ISI_VSYNC, PIOB, ID_PIOB, PIO_PERIPH_C, PIO_DEFAULT}
/** Image Sensor Interface horizontal sync. */
#define BOARD_ISI_HSYNC     {PIO_PB4C_ISI_HSYNC, PIOB, ID_PIOB, PIO_PERIPH_C, PIO_DEFAULT}
/** Image Sensor Interface data clock. */
#define BOARD_ISI_PCK       {PIO_PB1C_ISI_PCK, PIOB, ID_PIOB, PIO_PERIPH_C, PIO_DEFAULT}
/** Image Sensor Interface data pins. */
#define BOARD_ISI_PINS_DATA {0x07F80000, PIOC, ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}	//pc19-26
//#define BOARD_ISI_PINS_DATA2 {0x0000000F, PIOC, ID_PIOC, PIO_PERIPH_C, PIO_DEFAULT}

/** Image Sensor Interface reset pin. */
#define PIN_ISI_RST       {1 << 11, PIOB, ID_PIOB, PIO_OUTPUT_1, PIO_DEFAULT}

/** Image Sensor Interface reset_n pin. */
#define PIN_ISI_RSTN      {1 << 5, PIOB, ID_PIOB, PIO_OUTPUT_1, PIO_DEFAULT}

/** Image Sensor Interface pin list. */
#define PINS_ISI          BOARD_ISI_VSYNC, BOARD_ISI_HSYNC, BOARD_ISI_PCK , BOARD_ISI_PINS_DATA

/** Touchscreen ADC clock frequency to use. */
#define BOARD_TOUCHSCREEN_ADCCLK    300000	/* 8MHz max */
/** Touchscreen ADC startup time in µseconds. */
#define BOARD_TOUCHSCREEN_STARTUP   40
/** Touchscreen ADC track and hold time in nanoseconds. */
#define BOARD_TOUCHSCREEN_SHTIM     2000	/* min 1µs at 8MHz */
/** Touchscreen pen debounce time in nanoseconds. */
#define BOARD_TOUCHSCREEN_DEBOUNCE  10000000

/** Analog-to-Digital Converter signal AD0 definition. */
#define PIN_AD0      {PIO_PC27X1_AD0, PIOC, ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}
/** Analog-to-Digital Converter signal AD1 definition. */
#define PIN_AD1      {PIO_PC28X1_AD1, PIOC, ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}
/** Analog-to-Digital Converter signal AD2 definition. */
#define PIN_AD2      {PIO_PC29X1_AD2, PIOC, ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}
/** Analog-to-Digital Converter signal AD3 definition. */
#define PIN_AD3      {PIO_PC30X1_AD3, PIOC, ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}
/** Analog-to-Digital Converter signal AD4 definition. */
#define PIN_AD4      {PIO_PC31X1_AD4, PIOC, ID_PIOC, PIO_PERIPH_A, PIO_DEFAULT}

//#define PINS_TOUCH_SCREEN   PIN_AD0_XP, PIN_AD1_XM, PIN_AD2_YP, PIN_AD3_YM, PIN_AD4_LR

/** HDMI reset pins. */
#define PIN_HDMI_RESET_L  {PIO_PC31, PIOC, ID_PIOC, PIO_OUTPUT_0, PIO_DEFAULT}
#define PIN_HDMI_RESET_H  {PIO_PC31, PIOC, ID_PIOC, PIO_OUTPUT_1, PIO_DEFAULT}

/*----------------------------------------------------------------------------*/
/**
 * \if document_A5D4_EK
 * \page sama5d4_board_chipdef "SAMA5D4-EK - Individual chip definition"
 * This page lists the definitions related to different chip's definition
 * located in the board.h file for \ref sama5d4_board_desc "SAMA5D4-EK".
 * \elseif document_A5D4_XULT
 * \page sama5d4_board_chipdef "SAMA5D4-XULT - Individual chip definition"
 * This page lists the definitions related to different chip's definition
 * located in the board.h file for \ref sama5d4_board_desc "SAMA5D4-XULT".
 * \endif
 *
 * LEDs
 * - \ref PIN_LED_0
 * - \ref PIN_LED_1
 * \if document_A5D4_EK
 * - \ref PIN_LED_2
 * \endif
 * - \ref PINS_LEDS
 *
 * Push buttons
 * - \ref PIN_PUSHBUTTON_1
  * - \ref PINS_PUSHBUTTONS

 *
 * PCK0
 * - \ref PIN_PCK0
 *
 * PCK1
 * - \ref  PIN_PCK1
 */

/** BLUE LED index definition. */
#define LED_BLUE      0
/** RED LED index definition. */
#define LED_RED       1

#if defined(BOARD_SAMA5D4_EK)
/** LED #0 pin definition (LED_BLUE). */
#define PIN_LED_0   {(PIO_PE8), PIOE, ID_PIOE, PIO_OUTPUT_1, PIO_DEFAULT}
/** LED #1 pin definition (LED_RED). */
#define PIN_LED_1   {(PIO_PE9), PIOE, ID_PIOE, PIO_OUTPUT_0, PIO_DEFAULT}
/** LED #2 pin definition (LED_GREEN). */
#define PIN_LED_2   {(PIO_PE28), PIOE, ID_PIOE, PIO_OUTPUT_0, PIO_DEFAULT}

/** List of all LEDs definitions. */
#define PINS_LEDS   PIN_LED_0, PIN_LED_1,PIN_LED_2

/** Push button #1 definition. Attributes = pull-up + debounce + interrupt on rising edge. */
#define PIN_PUSHBUTTON_1    {PIO_PE13, PIOE, ID_PIOE, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE}
#define PIN_PUSHBUTTON_2    {PIO_PE13, PIOE, ID_PIOE, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE}
#elif defined(BOARD_SAMA5D4_XPLAINED)
/** LED #0 pin definition (LED_BLUE). */
#define PIN_LED_0   {(PIO_PE15), PIOE, ID_PIOE, PIO_OUTPUT_1, PIO_DEFAULT}
/** LED #1 pin definition (LED_RED). */
#define PIN_LED_1   {(PIO_PD30), PIOD, ID_PIOD, PIO_OUTPUT_0, PIO_DEFAULT}

/** List of all LEDs definitions. */
#define PINS_LEDS   PIN_LED_0, PIN_LED_1

/** Push button #1 definition. Attributes = pull-up + debounce + interrupt on rising edge. */
#define PIN_PUSHBUTTON_1    {PIO_PE8, PIOE, ID_PIOE, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE}
#define PIN_PUSHBUTTON_2    {PIO_PE8, PIOE, ID_PIOE, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE}
#endif
/** List of all push button definitions. */
#define PINS_PUSHBUTTONS    PIN_PUSHBUTTON_1

/** Push button #1 index. */
#define PUSHBUTTON_BP1   0
/** Push button #2 index. */
#define PUSHBUTTON_BP2   1

/** catb button */
#define PIN_SBUTTON0    {1 << 18, PIOD, ID_PIOD, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_SBUTTON1    {1 << 19, PIOD, ID_PIOD, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_SBUTTON2    {1 << 20, PIOD, ID_PIOD, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_SBUTTON3    {1 << 21, PIOD, ID_PIOD, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_SBUTTON4    {1 << 22, PIOD, ID_PIOD, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_SBUTTON_DIS {1 << 29, PIOD, ID_PIOD, PIO_PERIPH_B, PIO_DEFAULT}

#define PINS_SBUTTON PIN_SBUTTON0, PIN_SBUTTON1, PIN_SBUTTON2, PIN_SBUTTON3, PIN_SBUTTON4, PIN_SBUTTON_DIS

/** PCK0 */
#define PIN_PCK0        {PIO_PB26A_PCK0, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT}
/** PCK1 */
#define PIN_PCK1        {PIO_PD31B_PCK1, PIOD, ID_PIOD, PIO_PERIPH_B, PIO_DEFAULT}
//#define PIN_PCK1        {PIO_PC4C_PCK1, PIOC, ID_PIOC, PIO_PERIPH_C, PIO_DEFAULT}
/** PCK2 */
#define PIN_PCK2        {PIO_PB10B_PCK2, PIOB, ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}

/*----------------------------------------------------------------------------
 *        Headers for board
 *----------------------------------------------------------------------------*/

//#include "include/dbg_util.h"
//#include "include/hamming.h"
//#include "include/math.h"
//#include "include/wav.h"
//#include "include/bmp.h"
/* #include "core/async.h" */
/* #include "core/pio.h" */

#include "board_lowlevel.h"
#include "board_memories.h"

/* #include "bus/dbgu_console.h" */

/* #include "bus/twid.h" */
/* #include "bus/xdma_hardware_interface.h" */
/* #include "bus/xdmad.h" */

/* #include "av/lcdd.h" */
/* #include "av/lcd_draw.h" */
/* #include "av/lcd_font10x14.h" */
/* #include "av/lcd_font.h" */
/* #include "av/lcd_color.h" */
/* #include "av/wm8904.h" */

/* #include "net/gmac.h" */
/* #include "net/gmii.h" */
/* #include "net/gmacd.h" */
/* #include "net/gmacb.h" */

/* #include "io/iso7816_4.h" */
/* #include "io/mcid.h" */
/* #include "io/led.h" */
/* #include "io/ov.h" */
/* #include "io/omnivision.h" */
/* #include "io/ovyuv.h" */
/* #include "io/aptina.h" */
/* #include "io/mtyuv.h" */
/* #include "io/mt.h" */
/* #include "io/tsd.h" */
/* #include "io/tsd.h" */
/* #include "io/tsd_com.h" */

/* #include "time/timetick.h" */
/* #include "time/rtc_calib.h" */

#endif				/* #ifndef _BOARD_SAMA5D4_COMMON_HEADER_ */
