/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2016, Atmel Corporation                                        */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Atmel's name may not be used to endorse or promote products derived from     */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR   */
/* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE   */
/* DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,      */
/* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,  */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    */
/* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING         */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/* ---------------------------------------------------------------------------- */
/*                                                                              */

#ifndef _CHIP_PINS_H_
#define _CHIP_PINS_H_

/*----------------------------------------------------------------------------
 *       PIOs Define
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

/**
 * This pages lists all the pio definitions contained in chip.h.
 * The constants are named using the following convention: PIN_* for a constant
 * which defines a single Pin instance (but may include several PIOs sharing the
 * same controller), and PINS_* for a list of Pin instances.
 */

/* ========== Pio PIN definition for DBGU peripheral ========== */

/** DBGU TXD pin definition. */
#define PIN_DBGU_TXD { PIO_GROUP_A, PIO_PA10A_DTXD, PIO_PERIPH_A, PIO_DEFAULT }

/** DBGU RXD pin definition. */
#define PIN_DBGU_RXD { PIO_GROUP_A, PIO_PA9A_DRXD, PIO_PERIPH_A, PIO_DEFAULT }

/** DBGU pin definition. */
#define PINS_DBGU {\
	PIN_DBGU_TXD,\
	PIN_DBGU_RXD,\
}

/* ========== Pio PIN definition for PMC peripheral (PCK) ========== */

#define PIN_PCK0 { PIO_GROUP_B, PIO_PB10B_PCK0, PIO_PERIPH_B, PIO_DEFAULT }

#define PIN_PCK0_ALT { PIO_GROUP_C, PIO_PC15C_PCK0, PIO_PERIPH_C, PIO_DEFAULT }

#define PIN_PCK1 { PIO_GROUP_B, PIO_PB9B_PCK1, PIO_PERIPH_B, PIO_DEFAULT }

#define PIN_PCK1_ALT { PIO_GROUP_C, PIO_PC31C_PCK1, PIO_PERIPH_C, PIO_DEFAULT }

/* ========== Pio PIN definition for UART0 peripheral ========== */

/** UART0 TXD pin definition. */
#define PIN_UART0_TXD { PIO_GROUP_C, PIO_PC8C_UTXD0, PIO_PERIPH_C, PIO_DEFAULT }

/** UART0 RXD pin definition. */
#define PIN_UART0_RXD { PIO_GROUP_C, PIO_PC9C_URXD0, PIO_PERIPH_C, PIO_DEFAULT }

/** UART0 pins definition. */
#define PINS_UART0 {\
	PIN_UART0_TXD,\
	PIN_UART0_RXD,\
}

/* ========== Pio PIN definition for UART1 peripheral ========== */

/** UART1 TXD pin definition. */
#define PIN_UART1_TXD { PIO_GROUP_C, PIO_PC16C_UTXD1, PIO_PERIPH_C, PIO_DEFAULT }

/** UART1 RXD pin definition. */
#define PIN_UART1_RXD { PIO_GROUP_C, PIO_PC17C_URXD1, PIO_PERIPH_C, PIO_DEFAULT }

/** UART1 pins definition. */
#define PINS_UART1 {\
	PIN_UART1_TXD,\
	PIN_UART1_RXD,\
}

/* ========== Pio PIN definition for USART0 peripheral ========== */

/** USART0 TXD pin definition. */
#define PIN_USART0_TXD { PIO_GROUP_A, PIO_PA0A_TXD0, PIO_PERIPH_A, PIO_DEFAULT }

/** USART0 RXD pin definition. */
#define PIN_USART0_RXD { PIO_GROUP_A, PIO_PA1A_RXD0, PIO_PERIPH_A, PIO_DEFAULT }

/** USART0 RTS pin definition. */
#define PIN_USART0_RTS { PIO_GROUP_A, PIO_PA2A_RTS0, PIO_PERIPH_A, PIO_DEFAULT }

/** USART0 CTS pin definition. */
#define PIN_USART0_CTS { PIO_GROUP_A, PIO_PA3A_CTS0, PIO_PERIPH_A, PIO_DEFAULT }

/** USART0 SCK pin definition. */
#define PIN_USART0_SCK { PIO_GROUP_A, PIO_PA4A_SCK0, PIO_PERIPH_A, PIO_DEFAULT }

/** USART0 pins definition (default) */
#define PINS_USART0 \
	{ PIN_USART0_TXD, PIN_USART0_RXD }

/** USART0 pins definition (with handshake) */
#define PINS_USART0_HS \
	{ PIN_USART0_TXD, PIN_USART0_RXD, PIN_USART0_RTS, PIN_USART0_CTS }

/** USART0 pins definition (synchronous) */
#define PINS_USART0_SYNC \
	{ PIN_USART0_TXD, PIN_USART0_RXD, PIN_USART0_SCK }

/** USART0 pins definition (synchronous with handshake) */
#define PINS_USART0_SYNC_HS \
	{ PIN_USART0_TXD, PIN_USART0_RXD, PIN_USART0_RTS, PIN_USART0_CTS, PIN_USART0_SCK }

/** USART0 pins definition (ISO7816) */
#define PINS_USART0_ISO7816 \
	{ PIN_USART0_TXD, PIN_USART0_SCK }

/** USART0 pins definition (RS485) */
#define PINS_USART0_RS485 \
	{ PIN_USART0_TXD, PIN_USART0_RXD, PIN_USART0_RTS }

/* ========== Pio PIN definition for USART1 peripheral ========== */

/** USART1 TXD pin definition. */
#define PIN_USART1_TXD { PIO_GROUP_A, PIO_PA5A_TXD1, PIO_PERIPH_A, PIO_DEFAULT }

/** USART1 RXD pin definition. */
#define PIN_USART1_RXD { PIO_GROUP_A, PIO_PA6A_RXD1, PIO_PERIPH_A, PIO_DEFAULT }

/** USART1 RTS pin definition. */
#define PIN_USART1_RTS { PIO_GROUP_C, PIO_PC27C_RTS1, PIO_PERIPH_C, PIO_DEFAULT }

/** USART1 CTS pin definition. */
#define PIN_USART1_CTS { PIO_GROUP_C, PIO_PC28C_CTS1, PIO_PERIPH_C, PIO_DEFAULT }

/** USART1 SCK pin definition. */
#define PIN_USART1_SCK { PIO_GROUP_C, PIO_PC29C_SCK1, PIO_PERIPH_C, PIO_DEFAULT }

/** USART1 pins definition (default) */
#define PINS_USART1 \
	{ PIN_USART1_TXD, PIN_USART1_RXD }

/** USART1 pins definition (with handshake) */
#define PINS_USART1_HS \
	{ PIN_USART1_TXD, PIN_USART1_RXD, PIN_USART1_RTS, PIN_USART1_CTS }

/** USART1 pins definition (synchronous) */
#define PINS_USART1_SYNC \
	{ PIN_USART1_TXD, PIN_USART1_RXD, PIN_USART1_SCK }

/** USART1 pins definition (synchronous with handshake) */
#define PINS_USART1_SYNC_HS \
	{ PIN_USART1_TXD, PIN_USART1_RXD, PIN_USART1_RTS, PIN_USART1_CTS, PIN_USART1_SCK }

/** USART1 pins definition (ISO7816) */
#define PINS_USART1_ISO7816 \
	{ PIN_USART1_TXD, PIN_USART1_SCK }

/** USART1 pins definition (RS485) */
#define PINS_USART1_RS485 \
	{ PIN_USART1_TXD, PIN_USART1_RXD, PIN_USART1_RTS }

/* ========== Pio PIN definition for USART2 peripheral ========== */

/** USART2 TXD pin definition. */
#define PIN_USART2_TXD { PIO_GROUP_A, PIO_PA7A_TXD2, PIO_PERIPH_A, PIO_DEFAULT }

/** USART2 RXD pin definition. */
#define PIN_USART2_RXD { PIO_GROUP_A, PIO_PA8A_RXD2, PIO_PERIPH_A, PIO_DEFAULT }

/** USART2 RTS pin definition. */
#define PIN_USART2_RTS { PIO_GROUP_B, PIO_PB0B_RTS2, PIO_PERIPH_B, PIO_DEFAULT }

/** USART2 CTS pin definition. */
#define PIN_USART2_CTS { PIO_GROUP_B, PIO_PB1B_CTS2, PIO_PERIPH_B, PIO_DEFAULT }

/** USART2 SCK pin definition. */
#define PIN_USART2_SCK { PIO_GROUP_B, PIO_PB2B_SCK2, PIO_PERIPH_B, PIO_DEFAULT }

/** USART2 pins definition (default) */
#define PINS_USART2 \
	{ PIN_USART2_TXD, PIN_USART2_RXD }

/** USART2 pins definition (with handshake) */
#define PINS_USART2_HS \
	{ PIN_USART2_TXD, PIN_USART2_RXD, PIN_USART2_RTS, PIN_USART2_CTS }

/** USART2 pins definition (synchronous) */
#define PINS_USART2_SYNC \
	{ PIN_USART2_TXD, PIN_USART2_RXD, PIN_USART2_SCK }

/** USART2 pins definition (synchronous with handshake) */
#define PINS_USART2_SYNC_HS \
	{ PIN_USART2_TXD, PIN_USART2_RXD, PIN_USART2_RTS, PIN_USART2_CTS, PIN_USART2_SCK }

/** USART2 pins definition (ISO7816) */
#define PINS_USART2_ISO7816 \
	{ PIN_USART2_TXD, PIN_USART2_SCK }

/** USART2 pins definition (RS485) */
#define PINS_USART2_RS485 \
	{ PIN_USART2_TXD, PIN_USART2_RXD, PIN_USART2_RTS }

/* ========== Pio PIN definition for USART3 peripheral ========== */

/** USART3 TXD pin definition. */
#define PIN_USART3_TXD { PIO_GROUP_C, PIO_PC22B_TXD3, PIO_PERIPH_B, PIO_DEFAULT }

/** USART3 RXD pin definition. */
#define PIN_USART3_RXD { PIO_GROUP_C, PIO_PC23B_RXD3, PIO_PERIPH_B, PIO_DEFAULT }

/** USART3 RTS pin definition. */
#define PIN_USART3_RTS { PIO_GROUP_C, PIO_PC24B_RTS3, PIO_PERIPH_B, PIO_DEFAULT }

/** USART3 CTS pin definition. */
#define PIN_USART3_CTS { PIO_GROUP_C, PIO_PC25B_CTS3, PIO_PERIPH_B, PIO_DEFAULT }

/** USART3 SCK pin definition. */
#define PIN_USART3_SCK { PIO_GROUP_C, PIO_PC26B_SCK3, PIO_PERIPH_B, PIO_DEFAULT }

/** USART3 pins definition (default) */
#define PINS_USART3 \
	{ PIN_USART3_TXD, PIN_USART3_RXD }

/** USART3 pins definition (with handshake) */
#define PINS_USART3_HS \
	{ PIN_USART3_TXD, PIN_USART3_RXD, PIN_USART3_RTS, PIN_USART3_CTS }

/** USART3 pins definition (synchronous) */
#define PINS_USART3_SYNC \
	{ PIN_USART3_TXD, PIN_USART3_RXD, PIN_USART3_SCK }

/** USART3 pins definition (synchronous with handshake) */
#define PINS_USART3_SYNC_HS \
	{ PIN_USART3_TXD, PIN_USART3_RXD, PIN_USART3_RTS, PIN_USART3_CTS, PIN_USART3_SCK }

/** USART3 pins definition (ISO7816) */
#define PINS_USART3_ISO7816 \
	{ PIN_USART3_TXD, PIN_USART3_SCK }

/** USART3 pins definition (RS485) */
#define PINS_USART3_RS485 \
	{ PIN_USART3_TXD, PIN_USART3_RXD, PIN_USART3_RTS }

/* ========== Pio PIN definition for TWI0 peripheral ========== */

/** TWI0 data pin */
#define PIN_TWI0_TWD { PIO_GROUP_A, PIO_PA30A_TWD0, PIO_PERIPH_A, PIO_DEFAULT }

/** TWI0 clock pin */
#define PIN_TWI0_TWCK { PIO_GROUP_A, PIO_PA31A_TWCK0, PIO_PERIPH_A, PIO_DEFAULT }

/** TWI0 pins */
#define PINS_TWI0 { PIN_TWI0_TWD, PIN_TWI0_TWCK }

/* ========== Pio PIN definition for TWI1 peripheral ========== */

/** TWI1 data pin */
#define PIN_TWI1_TWD { PIO_GROUP_C, PIO_PC0C_TWD1, PIO_PERIPH_C, PIO_DEFAULT }

/** TWI1 clock pin */
#define PIN_TWI1_TWCK { PIO_GROUP_C, PIO_PC1C_TWCK1, PIO_PERIPH_C, PIO_DEFAULT }

/** TWI1 pins */
#define PINS_TWI1 { PIN_TWI1_TWD, PIN_TWI1_TWCK }

/* ========== Pio PIN definition for TWI2 peripheral ========== */

/** TWI2 data pin */
#define PIN_TWI2_TWD { PIO_GROUP_B, PIO_PB4B_TWD2, PIO_PERIPH_B, PIO_DEFAULT }

/** TWI2 clock pin */
#define PIN_TWI2_TWCK { PIO_GROUP_B, PIO_PB5B_TWCK2, PIO_PERIPH_B, PIO_DEFAULT }

/** TWI2 pins */
#define PINS_TWI2 { PIN_TWI2_TWD, PIN_TWI2_TWCK }

/* ========== Pio PIN definition for CLASSD peripheral ========== */

#define PIN_CLASSD_L0_IOS1 \
	{ PIO_GROUP_A, PIO_PA24C_CLASSD_L0, PIO_PERIPH_C, PIO_DEFAULT }

#define PIN_CLASSD_L1_IOS1 \
	{ PIO_GROUP_A, PIO_PA25C_CLASSD_L1, PIO_PERIPH_C, PIO_DEFAULT }

#define PIN_CLASSD_L2_IOS1 \
	{ PIO_GROUP_A, PIO_PA26C_CLASSD_L2, PIO_PERIPH_C, PIO_DEFAULT }

#define PIN_CLASSD_L3_IOS1 \
	{ PIO_GROUP_A, PIO_PA27C_CLASSD_L3, PIO_PERIPH_C, PIO_DEFAULT }

#define PINS_CLASSD_IOS1 {\
	PIN_CLASSD0_L0_IOS1, PIN_CLASSD0_L1_IOS1, \
	PIN_CLASSD0_L2_IOS1, PIN_CLASSD0_L3_IOS1, \
};

/* ========== Pio PIN definition for CAN0 peripheral ========== */

/** CAN0 pin TX */
#define PIN_CAN0_TX     { PIO_GROUP_A, PIO_PA10B_CANTX0, PIO_PERIPH_B, PIO_DEFAULT }

/** CAN0 pin RX */
#define PIN_CAN0_RX     { PIO_GROUP_A, PIO_PA9B_CANRX0, PIO_PERIPH_B, PIO_DEFAULT }

/** CAN0 pins */
#define PINS_CAN0       { PIN_CAN0_TX, PIN_CAN0_RX }

/* ========== Pio PIN definition for CAN1 peripheral ========== */

/** CAN1 pin TX */
#define PIN_CAN1_TX     { PIO_GROUP_A, PIO_PA5B_CANTX1, PIO_PERIPH_B, PIO_DEFAULT }

/** CAN1 pin RX */
#define PIN_CAN1_RX     { PIO_GROUP_A, PIO_PA6B_CANRX1, PIO_PERIPH_B, PIO_DEFAULT }

/** CAN0 pins */
#define PINS_CAN1       { PIN_CAN1_TX, PIN_CAN1_RX }

/* ========== Pio PIN definition for SPI0 peripheral ========== */

/** SPI0 MISO pin definition. */
#define PIN_SPI0_MISO { PIO_GROUP_A, PIO_PA11A_SPI0_MISO, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI0 MOSI pin definition. */
#define PIN_SPI0_MOSI { PIO_GROUP_A, PIO_PA12A_SPI0_MOSI, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI0 SPCK pin definition. */
#define PIN_SPI0_SPCK { PIO_GROUP_A, PIO_PA13A_SPI0_SPCK, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI0 chip select 0 pin definition. */
#define PIN_SPI0_NPCS0 { PIO_GROUP_A, PIO_PA14A_SPI0_NPCS0, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI0 chip select 1 pin definition. */
#define PIN_SPI0_NPCS1 { PIO_GROUP_A, PIO_PA7B_SPI0_NPCS1, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI0 chip select 2 pin definition. */
#define PIN_SPI0_NPCS2 { PIO_GROUP_A, PIO_PA1B_SPI0_NPCS2, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI0 chip select 3 pin definition. */
#define PIN_SPI0_NPCS3 { PIO_GROUP_A, PIO_PB3B_SPI0_NPCS3, PIO_PERIPH_B, PIO_DEFAULT }

/** List of SPI0 pin definitions (MISO, MOSI & SPCK). */
#define PINS_SPI0 { PIN_SPI0_MISO, PIN_SPI0_MOSI, PIN_SPI0_SPCK }

/** List of SPI0 pin definitions (MISO, MOSI, SPCK & NPCS0). */
#define PINS_SPI0_NPCS0 { PIN_SPI0_MISO, PIN_SPI0_MOSI, PIN_SPI0_SPCK, PIN_SPI0_NPCS0 }

/** List of SPI0 pin definitions (MISO, MOSI, SPCK & NPCS1). */
#define PINS_SPI0_NPCS1 { PIN_SPI0_MISO, PIN_SPI0_MOSI, PIN_SPI0_SPCK, PIN_SPI0_NPCS1 }

/** List of SPI0 pin definitions (MISO, MOSI, SPCK & NPCS2). */
#define PINS_SPI0_NPCS2 { PIN_SPI0_MISO, PIN_SPI0_MOSI, PIN_SPI0_SPCK, PIN_SPI0_NPCS2 }

/** List of SPI0 pin definitions (MISO, MOSI, SPCK & NPCS3). */
#define PINS_SPI0_NPCS3 { PIN_SPI0_MISO, PIN_SPI0_MOSI, PIN_SPI0_SPCK, PIN_SPI0_NPCS3 }

/* ========== Pio PIN definition for SPI1 peripheral ========== */

/** SPI1 MISO pin definition. */
#define PIN_SPI1_MISO { PIO_GROUP_A, PIO_PA21B_SPI1_MISO, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI1 MOSI pin definition. */
#define PIN_SPI1_MOSI { PIO_GROUP_A, PIO_PA22B_SPI1_MOSI, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI1 SPCK pin definition. */
#define PIN_SPI1_SPCK { PIO_GROUP_A, PIO_PA23B_SPI1_SPCK, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI1 chip select 0 pin definition. */
#define PIN_SPI1_NPCS0 { PIO_GROUP_A, PIO_PA8B_SPI1_NPCS0, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI1 chip select 1 pin definition. */
#define PIN_SPI1_NPCS1 { PIO_GROUP_A, PIO_PA0B_SPI1_NPCS1, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI1 chip select 2 pin definition. */
#define PIN_SPI1_NPCS2 { PIO_GROUP_A, PIO_PA31B_SPI1_NPCS2, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI1 chip select 3 pin definition. */
#define PIN_SPI1_NPCS3 { PIO_GROUP_A, PIO_PA30B_SPI1_NPCS3, PIO_PERIPH_B, PIO_DEFAULT }

/** List of SPI1 pin definitions (MISO, MOSI & SPCK). */
#define PINS_SPI1 { PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SPCK }

/** List of SPI1 pin definitions (MISO, MOSI, SPCK & NPCS0). */
#define PINS_SPI1_NPCS0 { PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SPCK, PIN_SPI1_NPCS0 }

/** List of SPI1 pin definitions (MISO, MOSI, SPCK & NPCS1). */
#define PINS_SPI1_NPCS1 { PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SPCK, PIN_SPI1_NPCS1 }

/** List of SPI1 pin definitions (MISO, MOSI, SPCK & NPCS2). */
#define PINS_SPI1_NPCS2 { PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SPCK, PIN_SPI1_NPCS2 }

/** List of SPI1 pin definitions (MISO, MOSI, SPCK & NPCS2). */
#define PINS_SPI1_NPCS3 { PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SPCK, PIN_SPI1_NPCS3 }

/* ========== Pio PIN definition for SSC peripheral ========== */

#define SSC0_TX (PIO_PA24B_TK | PIO_PA25B_TF | PIO_PA26B_TD)

#define SSC0_RX (PIO_PA27B_RD | PIO_PA28B_RK | PIO_PA29B_RF)

#define PINS_SSC0 {\
	{ PIO_GROUP_A, SSC0_TX | SSC0_RX, PIO_PERIPH_B, PIO_DEFAULT },\
}

/* ========== Pio PIN definition for LCDC peripheral ========== */

/* LCD 24 bits */
#define PINS_LCD { { PIO_GROUP_C, 0x7DFFFFFF, PIO_PERIPH_A, PIO_DEFAULT } }

/* ========== Pio PIN definition for ISI peripheral ========== */

/** Image Sensor Interface master clock. */
#define PIN_ISI_MCK { PIO_GROUP_C, PIO_PC15B_ISI_MCK, PIO_PERIPH_B, PIO_DEFAULT }

/** Image Sensor Interface vertical sync. */
#define PIN_ISI_VSYNC { PIO_GROUP_C, PIO_PC13B_ISI_VSYNC, PIO_PERIPH_B, PIO_DEFAULT }

/** Image Sensor Interface horizontal sync. */
#define PIN_ISI_HSYNC { PIO_GROUP_C, PIO_PC14B_ISI_HSYNC, PIO_PERIPH_B, PIO_DEFAULT }

/** Image Sensor Interface pixel clock. */
#define PIN_ISI_PCK { PIO_GROUP_C, PIO_PC12B_ISI_PCK, PIO_PERIPH_B, PIO_DEFAULT }

/** Image Sensor Interface data pins. */
#define PINS_ISI_DATA { PIO_GROUP_C, 0x00000FFF, PIO_PERIPH_B, PIO_DEFAULT } // pc0-11

/** Image Sensor Interface pin list. */
#define PINS_ISI { PIN_ISI_MCK, PIN_ISI_VSYNC, PIN_ISI_HSYNC, PIN_ISI_PCK, PINS_ISI_DATA }

/* ========== Pio PIN definition for ADC peripheral ========== */

/** ADC ADTRG pin (PD19). */
#define PIN_ADTRG { PIO_GROUP_B, PIO_PB18B_ADTRG, PIO_PERIPH_B, PIO_PULLUP }

/* ========== Pio PIN definition for EMAC peripheral ========== */

/** EMAC0 pin list (MII) */
#define PINS_EMAC0_MII  { { PIO_GROUP_B, 0x0003FFFF, PIO_PERIPH_A, PIO_DEFAULT } }

/** EMAC0 pin list (RMII) */
#define PINS_EMAC0_RMII  { { PIO_GROUP_B, 0x000006FF, PIO_PERIPH_A, PIO_DEFAULT } }

/** EMAC1 pin list (RMII) */
#define PINS_EMAC1_RMII  { { PIO_GROUP_C, 0xF83D0000, PIO_PERIPH_B, PIO_DEFAULT } }

/* ========== Pio PIN definition for NAND peripheral ========== */

/* 8-bit NAND: D16-D23, NAND{WE,CS,ALE,CLE,OE,RDY} */
#define PINS_NAND8 { { PIO_GROUP_D, 0x00003FFF, PIO_PERIPH_A, PIO_DEFAULT } }

/* 8-bit NAND: D16-D31, NAND{WE,CS,ALE,CLE,OE,RDY} */
#define PINS_NAND16 { { PIO_GROUP_D, 0x03FFFFF, PIO_PERIPH_A, PIO_DEFAULT } }

/* ========== Pio PIN definition for SDMMC0 peripheral ========== */

/** SDMMC0 pin Card Command (CMD) */
#define PIN_SDMMC0_CMD { PIO_GROUP_A, 0x00010000, PIO_PERIPH_A, PIO_PULLUP }

/** SDMMC0 pin Card Clock (CK) */
#define PIN_SDMMC0_CK { PIO_GROUP_A, 0x00020000, PIO_PERIPH_A, PIO_DEFAULT }

/** SDMMC0 pin 1-bit Data (DA0) */
#define PINS_SDMMC0_DATA1B { PIO_GROUP_A, 0x00008000, PIO_PERIPH_A, PIO_PULLUP }

/** SDMMC0 pin 4-bit Data (DA0-3) */
#define PINS_SDMMC0_DATA4B { PIO_GROUP_A, 0x001C8000, PIO_PERIPH_A, PIO_PULLUP }

/* ========== Pio PIN definition for SDMMC1 peripheral ========== */

/** SDMMC1 pin Card Command (CMD) */
#define PIN_SDMMC1_CMD { PIO_GROUP_A, 0x00001000, PIO_PERIPH_B, PIO_PULLUP }

/** SDMMC1 pin Card Clock (CK) */
#define PIN_SDMMC1_CK { PIO_GROUP_A, 0x00002000, PIO_PERIPH_B, PIO_DEFAULT }

/** SDMMC1 pin 1-bit Data (DA0) */
#define PINS_SDMMC1_DATA1B { PIO_GROUP_A, 0x00000800, PIO_PERIPH_B, PIO_PULLUP }

/** SDMMC1 pin 4-bit Data (DA0-3) */
#define PINS_SDMMC1_DATA4B { PIO_GROUP_A, 0x0000081C, PIO_PERIPH_B, PIO_PULLUP }

/* ========== Pio PIN definition for QSPI peripheral ========== */

/* QSPI */
#define PINS_QSPI {\
	{ PIO_GROUP_B, 0x01F80000, PIO_PERIPH_A, PIO_DEFAULT},\
}

/* ========== Pio PIN definition for TC0 peripheral ========== */

#define PIN_TC0_TCLK0 { PIO_GROUP_A, PIO_PA24A_TCLK0, PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_TC0_TCLK1 { PIO_GROUP_A, PIO_PA25A_TCLK1, PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_TC0_TCLK2 { PIO_GROUP_A, PIO_PA26A_TCLK2, PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_TC0_TIOA0 { PIO_GROUP_A, PIO_PA21A_TIOA0, PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_TC0_TIOA1 { PIO_GROUP_A, PIO_PA22A_TIOA1, PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_TC0_TIOA2 { PIO_GROUP_A, PIO_PA23A_TIOA2, PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_TC0_TIOB0 { PIO_GROUP_A, PIO_PA27A_TIOB0, PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_TC0_TIOB1 { PIO_GROUP_A, PIO_PA28A_TIOB1, PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_TC0_TIOB2 { PIO_GROUP_A, PIO_PA29A_TIOB2, PIO_PERIPH_A, PIO_DEFAULT }

/* ========== Pio PIN definition for TC1 peripheral ========== */

#define PIN_TC1_TCLK3 { PIO_GROUP_C, PIO_PC4C_TCLK3,  PIO_PERIPH_C, PIO_DEFAULT }
#define PIN_TC1_TCLK4 { PIO_GROUP_C, PIO_PC7C_TCLK4,  PIO_PERIPH_C, PIO_DEFAULT }
#define PIN_TC1_TCLK5 { PIO_GROUP_C, PIO_PC14C_TCLK5, PIO_PERIPH_C, PIO_DEFAULT }
#define PIN_TC1_TIOA3 { PIO_GROUP_C, PIO_PC2C_TIOA3,  PIO_PERIPH_C, PIO_DEFAULT }
#define PIN_TC1_TIOA4 { PIO_GROUP_C, PIO_PC5C_TIOA4,  PIO_PERIPH_C, PIO_DEFAULT }
#define PIN_TC1_TIOA5 { PIO_GROUP_C, PIO_PC12C_TIOA5, PIO_PERIPH_C, PIO_DEFAULT }
#define PIN_TC1_TIOB3 { PIO_GROUP_C, PIO_PC3C_TIOB3,  PIO_PERIPH_C, PIO_DEFAULT }
#define PIN_TC1_TIOB4 { PIO_GROUP_C, PIO_PC6C_TIOB4,  PIO_PERIPH_C, PIO_DEFAULT }
#define PIN_TC1_TIOB5 { PIO_GROUP_C, PIO_PC13C_TIOB5, PIO_PERIPH_C, PIO_DEFAULT }

/* ============================================================ */


/* ========== Pio PIN definition for FLEXCOM0 peripheral ========== */
/* FLEXCOM0 IO0 (USART: TXD, SPI: MOSI, TWI: TWD) */
#define PIN_FLEXCOM0_IO0_IOS1 { PIO_GROUP_A, PIO_PA0A_FLEXCOM0_IO0, PIO_PERIPH_A, PIO_DEFAULT }
/* FLEXCOM0 IO1 (USART: RXD, SPI: MISO, TWI: TWCK) */
#define PIN_FLEXCOM0_IO1_IOS1 { PIO_GROUP_A, PIO_PA1A_FLEXCOM0_IO1, PIO_PERIPH_A, PIO_DEFAULT }
/* FLEXCOM0 IO2 (USART: SCK, SPI: SPCK) */
#define PIN_FLEXCOM0_IO2_IOS1 { PIO_GROUP_A, PIO_PA4A_FLEXCOM0_IO2, PIO_PERIPH_A, PIO_DEFAULT }
/* FLEXCOM0 IO3 (USART: CTS, SPI: NPCS0) */
#define PIN_FLEXCOM0_IO3_IOS1 { PIO_GROUP_A, PIO_PA3A_FLEXCOM0_IO3, PIO_PERIPH_A, PIO_DEFAULT }
/* FLEXCOM0 IO4 (USART: RTS, SPI: NPCS1) */
#define PIN_FLEXCOM0_IO4_IOS1 { PIO_GROUP_A, PIO_PA2A_FLEXCOM0_IO4, PIO_PERIPH_A, PIO_DEFAULT }
/* FLEXCOM0 IO7 (USART: LONCOL) */
#define PIN_FLEXCOM0_IO7_IOS1 { PIO_GROUP_B, PIO_PB6B_FLEXCOM0_IO7, PIO_PERIPH_B, PIO_DEFAULT }

/* ========== Pio PIN definition for FLEXCOM1 peripheral ========== */
/* FLEXCOM1 IO0 (USART: TXD, SPI: MOSI, TWI: TWD) */
#define PIN_FLEXCOM1_IO0_IOS1 { PIO_GROUP_A, PIO_PA5A_FLEXCOM1_IO0, PIO_PERIPH_A, PIO_DEFAULT }
/* FLEXCOM1 IO1 (USART: RXD, SPI: MISO, TWI: TWCK) */
#define PIN_FLEXCOM1_IO1_IOS1 { PIO_GROUP_A, PIO_PA6A_FLEXCOM1_IO1, PIO_PERIPH_A, PIO_DEFAULT }
/* FLEXCOM1 IO2 (USART: SCK, SPI: SPCK) */
#define PIN_FLEXCOM1_IO2_IOS1 { PIO_GROUP_C, PIO_PC29C_FLEXCOM1_IO2, PIO_PERIPH_C, PIO_DEFAULT }
/* FLEXCOM1 IO3 (USART: CTS, SPI: NPCS0) */
#define PIN_FLEXCOM1_IO3_IOS1 { PIO_GROUP_C, PIO_PC28C_FLEXCOM1_IO3, PIO_PERIPH_C, PIO_DEFAULT }
/* FLEXCOM1 IO4 (USART: RTS, SPI: NPCS1) */
#define PIN_FLEXCOM1_IO4_IOS1 { PIO_GROUP_C, PIO_PC27C_FLEXCOM1_IO4, PIO_PERIPH_C, PIO_DEFAULT }
/* FLEXCOM1 IO7 (USART: LONCOL) */
#define PIN_FLEXCOM1_IO7_IOS1 { PIO_GROUP_C, PIO_PC17B_FLEXCOM1_IO7, PIO_PERIPH_B, PIO_DEFAULT }

/* ========== Pio PIN definition for FLEXCOM2 peripheral ========== */
/* FLEXCOM2 IO0 (USART: TXD, SPI: MOSI, TWI: TWD) */
#define PIN_FLEXCOM2_IO0_IOS1 { PIO_GROUP_A, PIO_PA7A_FLEXCOM2_IO0, PIO_PERIPH_A, PIO_DEFAULT }
/* FLEXCOM2 IO1 (USART: RXD, SPI: MISO, TWI: TWCK) */
#define PIN_FLEXCOM2_IO1_IOS1 { PIO_GROUP_A, PIO_PA8A_FLEXCOM2_IO1, PIO_PERIPH_A, PIO_DEFAULT }
/* FLEXCOM2 IO2 (USART: SCK, SPI: SPCK) */
#define PIN_FLEXCOM2_IO2_IOS1 { PIO_GROUP_B, PIO_PB2B_FLEXCOM2_IO2, PIO_PERIPH_B, PIO_DEFAULT }
/* FLEXCOM2 IO3 (USART: CTS, SPI: NPCS0) */
#define PIN_FLEXCOM2_IO3_IOS1 { PIO_GROUP_B, PIO_PB1B_FLEXCOM2_IO3, PIO_PERIPH_B, PIO_DEFAULT }
/* FLEXCOM2 IO4 (USART: RTS, SPI: NPCS1) */
#define PIN_FLEXCOM2_IO4_IOS1 { PIO_GROUP_B, PIO_PB0B_FLEXCOM2_IO4, PIO_PERIPH_B, PIO_DEFAULT }
/* FLEXCOM2 IO7 (USART: LONCOL) */
#define PIN_FLEXCOM2_IO7_IOS1 { PIO_GROUP_A, PIO_PA29C_FLEXCOM2_IO7, PIO_PERIPH_C, PIO_DEFAULT }

/* ========== Pio PIN definition for FLEXCOM3 peripheral ========== */
/* FLEXCOM3 IO0 (USART: TXD, SPI: MOSI, TWI: TWD) */
#define PIN_FLEXCOM3_IO0_IOS1 { PIO_GROUP_C, PIO_PC22B_FLEXCOM3_IO0, PIO_PERIPH_B, PIO_DEFAULT }
/* FLEXCOM3 IO1 (USART: RXD, SPI: MISO, TWI: TWCK) */
#define PIN_FLEXCOM3_IO1_IOS1 { PIO_GROUP_C, PIO_PC23B_FLEXCOM3_IO1, PIO_PERIPH_B, PIO_DEFAULT }
/* FLEXCOM3 IO2 (USART: SCK, SPI: SPCK) */
#define PIN_FLEXCOM3_IO2_IOS1 { PIO_GROUP_C, PIO_PC26B_FLEXCOM3_IO2, PIO_PERIPH_B, PIO_DEFAULT }
/* FLEXCOM3 IO3 (USART: CTS, SPI: NPCS0) */
#define PIN_FLEXCOM3_IO3_IOS1 { PIO_GROUP_C, PIO_PC25B_FLEXCOM3_IO3, PIO_PERIPH_B, PIO_DEFAULT }
/* FLEXCOM3 IO4 (USART: RTS, SPI: NPCS1) */
#define PIN_FLEXCOM3_IO4_IOS1 { PIO_GROUP_C, PIO_PC24B_FLEXCOM3_IO4, PIO_PERIPH_B, PIO_DEFAULT }
/* FLEXCOM3 IO7 (USART: LONCOL) */
#define PIN_FLEXCOM3_IO7_IOS1 { PIO_GROUP_C, PIO_PC30C_FLEXCOM3_IO7, PIO_PERIPH_C, PIO_DEFAULT }

/* ========== Pio PIN definition for FLEXCOM4 peripheral ========== */
/* FLEXCOM4 IO0 (USART: TXD, SPI: MOSI, TWI: TWD) */
#define PIN_FLEXCOM4_IO0_IOS1 { PIO_GROUP_A, PIO_PA12A_FLEXCOM4_IO0, PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_FLEXCOM4_IO0_IOS2 { PIO_GROUP_A, PIO_PA12A_FLEXCOM4_IO0, PIO_PERIPH_A, PIO_DEFAULT }
/* FLEXCOM4 IO1 (USART: RXD, SPI: MISO, TWI: TWCK) */
#define PIN_FLEXCOM4_IO1_IOS1 { PIO_GROUP_A, PIO_PA11A_FLEXCOM4_IO1, PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_FLEXCOM4_IO1_IOS2 { PIO_GROUP_A, PIO_PA11A_FLEXCOM4_IO1, PIO_PERIPH_A, PIO_DEFAULT }
/* FLEXCOM4 IO2 (USART: SCK, SPI: SPCK) */
#define PIN_FLEXCOM4_IO2_IOS1 { PIO_GROUP_A, PIO_PA13A_FLEXCOM4_IO2, PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_FLEXCOM4_IO2_IOS2 { PIO_GROUP_A, PIO_PA13A_FLEXCOM4_IO2, PIO_PERIPH_A, PIO_DEFAULT }
/* FLEXCOM4 IO3 (USART: CTS, SPI: NPCS0) */
#define PIN_FLEXCOM4_IO3_IOS1 { PIO_GROUP_A, PIO_PA14A_FLEXCOM4_IO3, PIO_PERIPH_A, PIO_DEFAULT }
#define PIN_FLEXCOM4_IO3_IOS2 { PIO_GROUP_A, PIO_PA14A_FLEXCOM4_IO3, PIO_PERIPH_A, PIO_DEFAULT }
/* FLEXCOM4 IO4 (USART: RTS, SPI: NPCS1) */
#define PIN_FLEXCOM4_IO4_IOS1 { PIO_GROUP_A, PIO_PA7B_FLEXCOM4_IO4, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_FLEXCOM4_IO4_IOS2 { PIO_GROUP_A, PIO_PA0C_FLEXCOM4_IO4, PIO_PERIPH_C, PIO_DEFAULT }
/* FLEXCOM4 IO5 (SPI: NPCS2) */
#define PIN_FLEXCOM4_IO5_IOS1 { PIO_GROUP_A, PIO_PA1B_FLEXCOM4_IO5, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_FLEXCOM4_IO5_IOS2 { PIO_GROUP_A, PIO_PA8C_FLEXCOM4_IO5, PIO_PERIPH_C, PIO_DEFAULT }
/* FLEXCOM4 IO6 (SPI: NPCS3) */
#define PIN_FLEXCOM4_IO6_IOS1 { PIO_GROUP_B, PIO_PB3B_FLEXCOM4_IO6, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_FLEXCOM4_IO6_IOS2 { PIO_GROUP_B, PIO_PB3B_FLEXCOM4_IO6, PIO_PERIPH_B, PIO_DEFAULT }

/* ========== Pio PIN definition for FLEXCOM5 peripheral ========== */
/* FLEXCOM5 IO0 (USART: TXD, SPI: MOSI, TWI: TWD) */
#define PIN_FLEXCOM5_IO0_IOS1 { PIO_GROUP_A, PIO_PA22B_FLEXCOM5_IO0, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_FLEXCOM5_IO0_IOS2 { PIO_GROUP_A, PIO_PA22B_FLEXCOM5_IO0, PIO_PERIPH_B, PIO_DEFAULT }
/* FLEXCOM5 IO1 (USART: RXD, SPI: MISO, TWI: TWCK) */
#define PIN_FLEXCOM5_IO1_IOS1 { PIO_GROUP_A, PIO_PA21B_FLEXCOM5_IO1, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_FLEXCOM5_IO1_IOS2 { PIO_GROUP_A, PIO_PA21B_FLEXCOM5_IO1, PIO_PERIPH_B, PIO_DEFAULT }
/* FLEXCOM5 IO2 (USART: SCK, SPI: SPCK) */
#define PIN_FLEXCOM5_IO2_IOS1 { PIO_GROUP_A, PIO_PA23B_FLEXCOM5_IO2, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_FLEXCOM5_IO2_IOS2 { PIO_GROUP_A, PIO_PA23B_FLEXCOM5_IO2, PIO_PERIPH_B, PIO_DEFAULT }
/* FLEXCOM5 IO3 (USART: CTS, SPI: NPCS0) */
#define PIN_FLEXCOM5_IO3_IOS1 { PIO_GROUP_A, PIO_PA8B_FLEXCOM5_IO3, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_FLEXCOM5_IO3_IOS2 { PIO_GROUP_A, PIO_PA8B_FLEXCOM5_IO3, PIO_PERIPH_B, PIO_DEFAULT }
/* FLEXCOM5 IO4 (USART: RTS, SPI: NPCS1) */
#define PIN_FLEXCOM5_IO4_IOS1 { PIO_GROUP_A, PIO_PA0B_FLEXCOM5_IO4, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_FLEXCOM5_IO4_IOS2 { PIO_GROUP_A, PIO_PA7C_FLEXCOM5_IO4, PIO_PERIPH_C, PIO_DEFAULT }
/* FLEXCOM5 IO5 (SPI: NPCS2) */
#define PIN_FLEXCOM5_IO5_IOS1 { PIO_GROUP_A, PIO_PA31B_FLEXCOM5_IO5, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_FLEXCOM5_IO5_IOS2 { PIO_GROUP_A, PIO_PA31B_FLEXCOM5_IO5, PIO_PERIPH_B, PIO_DEFAULT }
/* FLEXCOM5 IO6 (SPI: NPCS3) */
#define PIN_FLEXCOM5_IO6_IOS1 { PIO_GROUP_A, PIO_PA30B_FLEXCOM5_IO6, PIO_PERIPH_B, PIO_DEFAULT }
#define PIN_FLEXCOM5_IO6_IOS2 { PIO_GROUP_A, PIO_PA30B_FLEXCOM5_IO6, PIO_PERIPH_B, PIO_DEFAULT }

/* ========== Pio PIN definition for FLEXCOM6 peripheral ========== */
/* FLEXCOM6 IO0 (USART: TXD, TWI: TWD) */
#define PIN_FLEXCOM6_IO0_IOS1 { PIO_GROUP_A, PIO_PA30A_FLEXCOM6_IO0, PIO_PERIPH_A, PIO_DEFAULT }
/* FLEXCOM6 IO1 (USART: RXD, TWI: TWCK) */
#define PIN_FLEXCOM6_IO1_IOS1 { PIO_GROUP_A, PIO_PA31A_FLEXCOM6_IO1, PIO_PERIPH_A, PIO_DEFAULT }

/* ========== Pio PIN definition for FLEXCOM7 peripheral ========== */
/* FLEXCOM7 IO0 (USART: TXD, TWI: TWD) */
#define PIN_FLEXCOM7_IO0_IOS1 { PIO_GROUP_C, PIO_PC0C_FLEXCOM7_IO0, PIO_PERIPH_C, PIO_DEFAULT }
/* FLEXCOM7 IO1 (USART: RXD, TWI: TWCK) */
#define PIN_FLEXCOM7_IO1_IOS1 { PIO_GROUP_C, PIO_PC1C_FLEXCOM7_IO1, PIO_PERIPH_C, PIO_DEFAULT }

/* ========== Pio PIN definition for FLEXCOM8 peripheral ========== */
/* FLEXCOM8 IO0 (USART: TXD, TWI: TWD) */
#define PIN_FLEXCOM8_IO0_IOS1 { PIO_GROUP_B, PIO_PB4B_FLEXCOM8_IO0, PIO_PERIPH_B, PIO_DEFAULT }
/* FLEXCOM8 IO1 (USART: RXD, TWI: TWCK) */
#define PIN_FLEXCOM8_IO1_IOS1 { PIO_GROUP_B, PIO_PB5B_FLEXCOM8_IO1, PIO_PERIPH_B, PIO_DEFAULT }

/* ========== Pio PIN definition for FLEXCOM9 peripheral ========== */
/* FLEXCOM9 IO0 (USART: TXD, TWI: TWD) */
#define PIN_FLEXCOM9_IO0_IOS1 { PIO_GROUP_C, PIO_PC8C_FLEXCOM9_IO0, PIO_PERIPH_C, PIO_DEFAULT }
/* FLEXCOM9 IO1 (USART: RXD, TWI: TWCK) */
#define PIN_FLEXCOM9_IO1_IOS1 { PIO_GROUP_C, PIO_PC9C_FLEXCOM9_IO1, PIO_PERIPH_C, PIO_DEFAULT }

/* ========== Pio PIN definition for FLEXCOM10 peripheral ========== */
/* FLEXCOM10 IO0 (USART: TXD, TWI: TWD) */
#define PIN_FLEXCOM10_IO0_IOS1 { PIO_GROUP_C, PIO_PC16C_FLEXCOM10_IO0, PIO_PERIPH_C, PIO_DEFAULT }
/* FLEXCOM10 IO1 (USART: RXD, TWI: TWCK) */
#define PIN_FLEXCOM10_IO1_IOS1 { PIO_GROUP_C, PIO_PC17C_FLEXCOM10_IO1, PIO_PERIPH_C, PIO_DEFAULT }

/* ========== Pio PIN definition for FLEXCOM11 peripheral ========== */
/* FLEXCOM11 IO0 (USART: TXD, TWI: TWD) */
#define PIN_FLEXCOM11_IO0_IOS1 { PIO_GROUP_B, PIO_PB19C_FLEXCOM11_IO0, PIO_PERIPH_C, PIO_DEFAULT }
/* FLEXCOM11 IO1 (USART: RXD, TWI: TWCK) */
#define PIN_FLEXCOM11_IO1_IOS1 { PIO_GROUP_B, PIO_PB20C_FLEXCOM11_IO1, PIO_PERIPH_C, PIO_DEFAULT }

/* ========== Pio PIN definition for FLEXCOM12 peripheral ========== */
/* FLEXCOM12 IO0 (USART: TXD, TWI: TWD) */
#define PIN_FLEXCOM12_IO0_IOS1 { PIO_GROUP_B, PIO_PB21C_FLEXCOM12_IO0, PIO_PERIPH_C, PIO_DEFAULT }
/* FLEXCOM12 IO1 (USART: RXD, TWI: TWCK) */
#define PIN_FLEXCOM12_IO1_IOS1 { PIO_GROUP_B, PIO_PB22C_FLEXCOM12_IO1, PIO_PERIPH_C, PIO_DEFAULT }

//=============================================================================
/* Include generic flexcom pin definitions (must be included last) */
#include "chip_pins_flexcom.h"

#endif /* _CHIP_PINS_H_ */
