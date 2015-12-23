/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2015, Atmel Corporation                                        */
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

/** List of all DBGU pin definitions. */

/** DBGU Monitor IO pin (detect any DBGU operation). */
#define PIN_DBGU_MON { PIO_GROUP_B, PIO_PB24A_DRXD, PIO_INPUT, PIO_IT_RISE_EDGE }

/** DBGU pin definition. */
#define PINS_DBGU {\
	{ PIO_GROUP_B, PIO_PB24A_DRXD | PIO_PB25A_DTXD, PIO_PERIPH_A, PIO_DEFAULT },\
}

/** List of all USART pin definitions. */

/** USART0 TXD pin definition. */
#define PIN_USART0_TXD { PIO_GROUP_D, PIO_PD13A_TXD0, PIO_PERIPH_A, PIO_DEFAULT }

/** USART0 RXD pin definition. */
#define PIN_USART0_RXD { PIO_GROUP_D, PIO_PD12A_RXD0, PIO_PERIPH_A, PIO_DEFAULT }

/** USART0 RTS pin definition. */
#define PIN_USART0_RTS { PIO_GROUP_D, PIO_PD11A_RTS0, PIO_PERIPH_A, PIO_DEFAULT }

/** USART0 CTS pin definition. */
#define PIN_USART0_CTS { PIO_GROUP_D, PIO_PD10A_CTS0, PIO_PERIPH_A, PIO_DEFAULT }

/** USART0 SCK pin definition. */
#define PIN_USART0_SCK { PIO_GROUP_D, PIO_PD28A_SCK0, PIO_PERIPH_A, PIO_DEFAULT }

/** USART1 TXD pin definition. */
#define PIN_USART1_TXD { PIO_GROUP_D, PIO_PD17A_TXD1, PIO_PERIPH_A, PIO_DEFAULT }

/** USART1 RXD pin definition. */
#define PIN_USART1_RXD { PIO_GROUP_D, PIO_PD16A_RXD1, PIO_PERIPH_A, PIO_DEFAULT }

/** USART1 RTS pin definition. */
#define PIN_USART1_RTS { PIO_GROUP_D, PIO_PD15A_RTS1, PIO_PERIPH_A, PIO_DEFAULT }

/** USART1 CTS pin definition. */
#define PIN_USART1_CTS { PIO_GROUP_D, PIO_PD14A_CTS1, PIO_PERIPH_A, PIO_DEFAULT }

/** USART1 SCK pin definition. */
#define PIN_USART1_SCK { PIO_GROUP_D, PIO_PD29A_SCK1, PIO_PERIPH_A, PIO_DEFAULT }

/** USART2 TXD pin definition. */
#define PIN_USART2_TXD { PIO_GROUP_E, PIO_PE26B_TXD2, PIO_PERIPH_B, PIO_DEFAULT }

/** USART2 RXD pin definition. */
#define PIN_USART2_RXD { PIO_GROUP_E, PIO_PE25B_RXD2, PIO_PERIPH_B, PIO_DEFAULT }

/** USART2 RTS pin definition. */
#define PIN_USART2_RTS { PIO_GROUP_E, PIO_PE24B_RTS2, PIO_PERIPH_B, PIO_DEFAULT }

/** USART2 CTS pin definition. */
#define PIN_USART2_CTS { PIO_GROUP_E, PIO_PE23B_CTS2, PIO_PERIPH_B, PIO_DEFAULT }

/** USART2 SCK pin definition. */
#define PIN_USART2_SCK { PIO_GROUP_E, PIO_PE20B_SCK2, PIO_PERIPH_B, PIO_DEFAULT }

/** USART3 TXD pin definition. */
#define PIN_USART3_TXD { PIO_GROUP_E, PIO_PE17B_TXD3, PIO_PERIPH_B, PIO_DEFAULT }

/** USART3 RXD pin definition. */
#define PIN_USART3_RXD { PIO_GROUP_E, PIO_PE16B_RXD3, PIO_PERIPH_B, PIO_DEFAULT }

/** USART3 SCK pin definition. */
#define PIN_USART3_SCK { PIO_GROUP_E, PIO_PE15B_SCK3, PIO_PERIPH_B, PIO_DEFAULT }

/** USART4 TXD pin definition. */
//#define PIN_USART4_TXD { PIO_GROUP_E, PIO_PE27B_TXD4, PIO_PERIPH_B, PIO_DEFAULT }

/** USART4 RXD pin definition. */
//#define PIN_USART4_RXD { PIO_GROUP_E, PIO_PE26B_RXD4, PIO_PERIPH_B, PIO_DEFAULT }

/** USART4 RTS pin definition. */
//#define PIN_USART4_RTS { PIO_GROUP_E, PIO_PE28B_RTS4, PIO_PERIPH_B, PIO_DEFAULT }

/** USART4 CTS pin definition. */
//#define PIN_USART4_CTS { PIO_GROUP_E, PIO_PE0C_CTS4, PIO_PERIPH_C, PIO_DEFAULT }

/** USART4 SCK pin definition. */
//#define PIN_USART4_SCK { PIO_GROUP_E, PIO_PE25B_SCK4, PIO_PERIPH_B, PIO_DEFAULT }

/** PIN used for reset the smartcard */
#define PIN_ISO7816_RSTMC { PIO_GROUP_D, PIO_PD10, PIO_OUTPUT_0, PIO_DEFAULT }

/** Pins used for connect the smartcard */
#define PINS_ISO7816 { PIN_USART1_TXD, PIN_USART1_SCK, PIN_ISO7816_RSTMC }

/** List of all TWI pin definitions. */

/** TWI0 data pin */
#define PIN_TWI_TWD0 { PIO_GROUP_A, PIO_PA30A_TWD0, PIO_PERIPH_A, PIO_DEFAULT }

/** TWI0 clock pin */
#define PIN_TWI_TWCK0 { PIO_GROUP_A, PIO_PA31A_TWCK0, PIO_PERIPH_A, PIO_DEFAULT }

/** TWI0 pins */
#define PINS_TWI0 { PIN_TWI_TWD0, PIN_TWI_TWCK0 }

/** TWI1 data pin */
#define PIN_TWI_TWD1 { PIO_GROUP_E, PIO_PE29C_TWD1, PIO_PERIPH_C, PIO_DEFAULT }

/** TWI1 clock pin */
#define PIN_TWI_TWCK1 { PIO_GROUP_E, PIO_PE30C_TWCK1, PIO_PERIPH_C, PIO_DEFAULT }

/** TWI1 pins */
#define PINS_TWI1 { PIN_TWI_TWD1, PIN_TWI_TWCK1 }

/** TWI2 data pin */
#define PIN_TWI_TWD2 { PIO_GROUP_B, PIO_PB29A_TWD2, PIO_PERIPH_A, PIO_DEFAULT }

/** TWI2 clock pin */
#define PIN_TWI_TWCK2 { PIO_GROUP_B, PIO_PB30A_TWCK2, PIO_PERIPH_A, PIO_DEFAULT }

/** TWI2 pins */
#define PINS_TWI2 { PIN_TWI_TWD2, PIN_TWI_TWCK2 }

/** TWI3 data pin */
#define PIN_TWI_TWD3 { PIO_GROUP_C, PIO_PC25B_TWD3, PIO_PERIPH_B, PIO_DEFAULT }

/** TWI3 clock pin */
#define PIN_TWI_TWCK3 { PIO_GROUP_C, PIO_PC26B_TWCK3, PIO_PERIPH_B, PIO_DEFAULT }

/** TWI3 pins */
#define PINS_TWI3 { PIN_TWI_TWD3, PIN_TWI_TWCK3 }

/** List of all SPI pin definitions. */

/** SPI0 MISO pin definition. */
#define PIN_SPI0_MISO { PIO_GROUP_C, PIO_PC0A_SPI0_MISO, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI0 MOSI pin definition. */
#define PIN_SPI0_MOSI { PIO_GROUP_C, PIO_PC1A_SPI0_MOSI, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI0 SPCK pin definition. */
#define PIN_SPI0_SPCK { PIO_GROUP_C, PIO_PC2A_SPI0_SPCK, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI0 chip select 0 pin definition. */
#define PIN_SPI0_NPCS0 { PIO_GROUP_C, PIO_PC3A_SPI0_NPCS0, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI0 chip select 1 pin definition. */
#define PIN_SPI0_NPCS1 { PIO_GROUP_C, PIO_PC4A_SPI0_NPCS1, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI0 chip select 1 pin definition (alternate). */
#define PIN_SPI0_NPCS1_ALT { PIO_GROUP_C, PIO_PC27B_SPI0_NPCS1, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI0 chip select 2 pin definition. */
#define PIN_SPI0_NPCS2 { PIO_GROUP_C, PIO_PC28B_SPI0_NPCS2, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI0 chip select 2 pin definition (alternate). */
#define PIN_SPI0_NPCS2_ALT { PIO_GROUP_D, PIO_PD31A_SPI0_NPCS2, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI0 chip select 3 pin definition. */
#define PIN_SPI0_NPCS3 { PIO_GROUP_C, PIO_PC29B_SPI0_NPCS3, PIO_PERIPH_C, PIO_DEFAULT }

/** List of SPI0 pin definitions (MISO, MOSI & SPCK). */
#define PINS_SPI0 { PIN_SPI0_MISO, PIN_SPI0_MOSI, PIN_SPI0_SPCK }

/** List of SPI0 pin definitions (MISO, MOSI, SPCK & NPCS0). */
#define PINS_SPI0_NPCS0 { PIN_SPI0_MISO, PIN_SPI0_MOSI, PIN_SPI0_SPCK, PIN_SPI0_NPCS0 }

/** List of SPI0 pin definitions (MISO, MOSI, SPCK & NPCS1). */
#define PINS_SPI0_NPCS1 { PIN_SPI0_MISO, PIN_SPI0_MOSI, PIN_SPI0_SPCK, PIN_SPI0_NPCS1 }

/** List of SPI0 pin definitions (MISO, MOSI, SPCK & NPCS1 alternate). */
#define PINS_SPI0_NPCS1_ALT { PIN_SPI0_MISO, PIN_SPI0_MOSI, PIN_SPI0_SPCK, PIN_SPI0_NPCS1_ALT }

/** List of SPI0 pin definitions (MISO, MOSI, SPCK & NPCS2). */
#define PINS_SPI0_NPCS2 { PIN_SPI0_MISO, PIN_SPI0_MOSI, PIN_SPI0_SPCK, PIN_SPI0_NPCS2 }

/** List of SPI0 pin definitions (MISO, MOSI, SPCK & NPCS2 alternate). */
#define PINS_SPI0_NPCS2_ALT { PIN_SPI0_MISO, PIN_SPI0_MOSI, PIN_SPI0_SPCK, PIN_SPI0_NPCS2_ALT }

/** List of SPI0 pin definitions (MISO, MOSI, SPCK & NPCS3). */
#define PINS_SPI0_NPCS3 { PIN_SPI0_MISO, PIN_SPI0_MOSI, PIN_SPI0_SPCK, PIN_SPI0_NPCS3 }

/** SPI1 MISO pin definition. */
#define PIN_SPI1_MISO { PIO_GROUP_B, PIO_PB18A_SPI1_MISO, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI1 MOSI pin definition. */
#define PIN_SPI1_MOSI { PIO_GROUP_B, PIO_PB19A_SPI1_MOSI, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI1 SPCK pin definition. */
#define PIN_SPI1_SPCK { PIO_GROUP_B, PIO_PB20A_SPI1_SPCK, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI1 chip select 0 pin definition. */
#define PIN_SPI1_NPCS0 { PIO_GROUP_B, PIO_PB21A_SPI1_NPCS0, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI1 chip select 1 pin definition. */
#define PIN_SPI1_NPCS1 { PIO_GROUP_A, PIO_PA26C_SPI1_NPCS1, PIO_PERIPH_C, PIO_DEFAULT }

/** SPI1 chip select 1 pin definition (alternate). */
#define PIN_SPI1_NPCS1_ALT { PIO_GROUP_B, PIO_PB22A_SPI1_NPCS1, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI1 chip select 2 pin definition. */
#define PIN_SPI1_NPCS2 { PIO_GROUP_A, PIO_PA27C_SPI1_NPCS2, PIO_PERIPH_C, PIO_DEFAULT }

/** SPI1 chip select 2 pin definition (alternate). */
#define PIN_SPI1_NPCS2_ALT { PIO_GROUP_B, PIO_PB23A_SPI1_NPCS2, PIO_PERIPH_A, PIO_DEFAULT }

/** SPI1 chip select 3 pin definition. */
#define PIN_SPI1_NPCS3 { PIO_GROUP_A, PIO_PA28C_SPI1_NPCS3, PIO_PERIPH_C, PIO_DEFAULT }

/** SPI1 chip select 3 pin definition (alternate). */
#define PIN_SPI1_NPCS3_ALT { PIO_GROUP_B, PIO_PB27A_SPI1_NPCS3, PIO_PERIPH_A, PIO_DEFAULT }

/** List of SPI1 pin definitions (MISO, MOSI & SPCK). */
#define PINS_SPI1 { PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SPCK }

/** List of SPI1 pin definitions (MISO, MOSI, SPCK & NPCS0). */
#define PINS_SPI1_NPCS0 { PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SPCK, PIN_SPI1_NPCS0 }

/** List of SPI1 pin definitions (MISO, MOSI, SPCK & NPCS1). */
#define PINS_SPI1_NPCS1 { PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SPCK, PIN_SPI1_NPCS1 }

/** List of SPI1 pin definitions (MISO, MOSI, SPCK & NPCS1 alternate). */
#define PINS_SPI1_NPCS1_ALT { PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SPCK, PIN_SPI1_NPCS1_ALT }

/** List of SPI1 pin definitions (MISO, MOSI, SPCK & NPCS2). */
#define PINS_SPI1_NPCS2 { PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SPCK, PIN_SPI1_NPCS2 }

/** List of SPI1 pin definitions (MISO, MOSI, SPCK & NPCS2 alternate). */
#define PINS_SPI1_NPCS2_ALT { PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SPCK, PIN_SPI1_NPCS2_ALT }

/** List of SPI1 pin definitions (MISO, MOSI, SPCK & NPCS2). */
#define PINS_SPI1_NPCS3 { PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SPCK, PIN_SPI1_NPCS3 }

/** List of SPI1 pin definitions (MISO, MOSI, SPCK & NPCS2 alternate). */
#define PINS_SPI1_NPCS3_ALT { PIN_SPI1_MISO, PIN_SPI1_MOSI, PIN_SPI1_SPCK, PIN_SPI1_NPCS3_ALT }

/** SPI2 MISO pin definition. */
#define PIN_SPI2_MISO { PIO_GROUP_D, PIO_PD11B_SPI2_MISO, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI2 MOSI pin definition. */
#define PIN_SPI2_MOSI { PIO_GROUP_D, PIO_PD13B_SPI2_MOSI, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI2 SPCK pin definition. */
#define PIN_SPI2_SPCK { PIO_GROUP_D, PIO_PD15B_SPI2_SPCK, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI2 chip select 0 pin definition. */
#define PIN_SPI2_NPCS0 { PIO_GROUP_D, PIO_PD17B_SPI2_NPCS0, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI2 chip select 1 pin definition. */
#define PIN_SPI2_NPCS1 { PIO_GROUP_B, PIO_PB14B_SPI2_NPCS1, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI2 chip select 2 pin definition. */
#define PIN_SPI2_NPCS2 { PIO_GROUP_B, PIO_PB15B_SPI2_NPCS2, PIO_PERIPH_B, PIO_DEFAULT }

/** SPI2 chip select 3 pin definition. */
#define PIN_SPI2_NPCS3 { PIO_GROUP_B, PIO_PB28A_SPI2_NPCS3, PIO_PERIPH_A, PIO_DEFAULT }

/** List of SPI2 pin definitions (MISO, MOSI & SPCK). */
#define PINS_SPI2 { PIN_SPI2_MISO, PIN_SPI2_MOSI, PIN_SPI2_SPCK }

/** List of SPI2 pin definitions (MISO, MOSI, SPCK & NPCS0). */
#define PINS_SPI2_NPCS0 { PIN_SPI2_MISO, PIN_SPI2_MOSI, PIN_SPI2_SPCK, PIN_SPI2_NPCS0 }

/** List of SPI2 pin definitions (MISO, MOSI, SPCK & NPCS1). */
#define PINS_SPI2_NPCS1 { PIN_SPI2_MISO, PIN_SPI2_MOSI, PIN_SPI2_SPCK, PIN_SPI2_NPCS1 }

/** List of SPI2 pin definitions (MISO, MOSI, SPCK & NPCS2). */
#define PINS_SPI2_NPCS2 { PIN_SPI2_MISO, PIN_SPI2_MOSI, PIN_SPI2_SPCK, PIN_SPI2_NPCS2 }

/** List of SPI2 pin definitions (MISO, MOSI, SPCK & NPCS3). */
#define PINS_SPI2_NPCS3 { PIN_SPI2_MISO, PIN_SPI2_MOSI, PIN_SPI2_SPCK, PIN_SPI2_NPCS3 }

/** List of all SSC pin definitions. */

/** SSC pin Transmitter Data (TD) */
#define PIN_SSC_TD0 { PIO_GROUP_B, PIO_PB28B_TD0, PIO_PERIPH_B, PIO_DEFAULT }

/** SSC pin Transmitter Clock (TK) */
#define PIN_SSC_TK0 { PIO_GROUP_B, PIO_PB27B_TK0, PIO_PERIPH_B, PIO_DEFAULT }

/** SSC pin Transmitter FrameSync (TF) */
#define PIN_SSC_TF0 { PIO_GROUP_B, PIO_PB31B_TF0, PIO_PERIPH_B, PIO_DEFAULT }

/** SSC pin RD */
#define PIN_SSC_RD0 { PIO_GROUP_B, PIO_PB29B_RD0, PIO_PERIPH_B, PIO_DEFAULT }

/** SSC pin RK */
#define PIN_SSC_RK0 { PIO_GROUP_B, PIO_PB26B_RK0, PIO_PERIPH_B, PIO_DEFAULT }

/** SSC pin RF */
#define PIN_SSC_RF0 { PIO_GROUP_B, PIO_PB30B_RF0, PIO_PERIPH_B, PIO_DEFAULT }

/** SSC pin Transmitter Data (TD) */
#define PIN_SSC_TD1 { PIO_GROUP_C, PIO_PC21, PIO_PERIPH_B, PIO_DEFAULT }

/** SSC pin Transmitter Clock (TK) */
#define PIN_SSC_TK1 { PIO_GROUP_C, PIO_PC19, PIO_PERIPH_B, PIO_DEFAULT }

/** SSC pin Transmitter FrameSync (TF) */
#define PIN_SSC_TF1 { PIO_GROUP_C, PIO_PC20, PIO_PERIPH_B, PIO_DEFAULT }

/** SSC pin RD */
#define PIN_SSC_RD1 { PIO_GROUP_C, PIO_PC23, PIO_PERIPH_B, PIO_DEFAULT }

/** SSC pin RK */
#define PIN_SSC_RK1 { PIO_GROUP_C, PIO_PC24, PIO_PERIPH_B, PIO_DEFAULT }

/** SSC pin RF */
#define PIN_SSC_RF1 { PIO_GROUP_C, PIO_PC22, PIO_PERIPH_B, PIO_DEFAULT }

/** SSC pins definition for codec. */
#define PINS_SSC_CODEC { PIN_SSC_TD0,  PIN_SSC_TK0, PIN_SSC_TF0, PIN_SSC_RD0,  PIN_SSC_RK0, PIN_SSC_RF0 }

/** LCD pin list. */
#define PINS_LCD_PIOA { { PIO_GROUP_A, 0x3FFEFEFE, PIO_PERIPH_A, PIO_DEFAULT } }

/** LCD pin list. */
#define PINS_LCD PINS_LCD_PIOA

/** ADC ADTRG pin (PD19). */
#define PIN_ADTRG { PIO_GROUP_E, PIO_PE31A_ADTRG, PIO_PERIPH_A, PIO_PULLUP }

/** GMAC0 MII pin list */
#define PINS_GMAC0_MII  { { PIO_GROUP_B, 0x3FFFF, PIO_PERIPH_A, PIO_DEFAULT } }

/** GMAC0 RMII pin list */
#define PINS_GMAC0_RMII { { PIO_GROUP_B, 0x333C5, PIO_PERIPH_A, PIO_DEFAULT } }

/** GMAC1 MII pin list */
#define PINS_GMAC1_MII  { { PIO_GROUP_A, 0xFCFE7C, PIO_PERIPH_B, PIO_DEFAULT } }

/** GMAC1 RMII pin list */
#define PINS_GMAC1_RMII { { PIO_GROUP_A, 0xC0FC14, PIO_PERIPH_B, PIO_DEFAULT } }

/* 8-bit NAND: D0-D7, NAND{WE,CS,ALE,CLE,OE,RDY} */
#define PINS_NAND8 { { PIO_GROUP_C, 0x0007FFE0, PIO_PERIPH_A, PIO_DEFAULT } }

/* 16-bit NAND: D0-D15, NAND{WE,CS,ALE,CLE,OE,RDY} */
#define PINS_NAND16 {\
	{ PIO_GROUP_B, 0x03FC0000, PIO_PERIPH_B, PIO_DEFAULT },\
	{ PIO_GROUP_C, 0x0007FFE0, PIO_PERIPH_A, PIO_DEFAULT },\
}

//=============================================================================

#endif /* _CHIP_PINS_H_ */
