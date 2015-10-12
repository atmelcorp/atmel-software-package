/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
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

#ifndef BOARD_INFO_H
  #define BOARD_INFO_H

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include "board.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------

#define ACT8945A
#define AT24MAC402
// #define ONE-WIRE
// #define NAND_FLASH
//#define EMMC
// #define SDRAM_DDR2
#define SDRAM_DDR3
//#define	EEPROM
#define SPI_FLASH
//#define QSPI_FLASH
//#define SDCARD
#define LCD
#define GETH

//------------------------------------------------------------------------------

#ifdef ACT8945A
	#define PMIC_DEVICE     "ACT8945A"
	#define PMIC_INTERFACE  "FLEXCOM4 TWI, IOS3"
	#define PMIC_COMMENT    "Advanced PMU for Atmel"
#endif


//------------------------------------------------------------------------------

#ifdef AT24MAC402
	#include "memories/at24.h"

	#define EEP_DEVICE      "AT24MAC402"
	#define EEP_INTERFACE   "TWI1, IOS2"
	#define EEP_COMMENT     "Serial number + Mac addr"
#endif


//------------------------------------------------------------------------------

#ifdef  EMMC
	#define EMMC_DEVICE		"MTFC4GLDEA-DM WT "
	#define EMMC_INTERFACE	"SDHC0 8bits data"
	#define	EMMC_COMMENT 	"4Gb"
#endif

//------------------------------------------------------------------------------

#ifdef SDRAM_DDR2
	#define DDR2_DEVICE		" "
	#define DDR2_INTERFACE	" "
	#DEFINE	DDR2_COMMENT 	" "

	#define BOARD_DDRAM_SIZE            (256*1024*1024)  // 256 MB
	#define OFFSET_MEMORY               0x00000000
	#define ADDR_DDR2_START             DDR_CS_ADDR + OFFSET_MEMORY
	#define ADDR_DDR2_END               ADDR_DDR2_START + BOARD_DDRAM_SIZE
	#define ADDR_FLASH_BUFFER_DATA      (ADDR_DDR2_START + BOARD_DDRAM_SIZE - 0x00A00000)

#endif

//------------------------------------------------------------------------------

#ifdef SDRAM_DDR3

	#define DDR3_DEVICE		"MT41K128M16JT-125:K"
	#define DDR3_INTERFACE	"Multi port controller"
	#define	DDR3_COMMENT 	"Mode DLL OFF"

	#define BOARD_DDRAM_SIZE            (256*1024*1024)  // 256 MB
 	#define OFFSET_MEMORY               0x04000000
	#define ADDR_DDR3_START				DDR_CS_ADDR	+ OFFSET_MEMORY
	#define ADDR_DDR3_END				DDR_CS_ADDR + BOARD_DDRAM_SIZE

#endif

//------------------------------------------------------------------------------

#ifdef SPI_FLASH
	#define SPIF_DEVICE		"AT25DF321A"
	#define SPIF_INTERFACE	"SPI0, IOS1, NPCS0"
	#define	SPIF_COMMENT 	"32Mb/4MB"
#endif

//------------------------------------------------------------------------------

#ifdef QSPI_FLASH
	#define QSPIF_DEVICE	"N25Q128A13ESE40F"
	#define QSPIF_INTERFACE	"QSPI0, I0S3 "
	#define	QSPIF_COMMENT 	"Optionnal"
#endif

//------------------------------------------------------------------------------

#ifdef SDCARD
	#define SDCARD_DEVICE		"SDHC1"
	#define SDCARD_INTERFACE	"8 bits data "
	#define	SDCARD_COMMENT 	"standard "
#endif

//------------------------------------------------------------------------------

#ifdef GETH
	#define GETH_DEVICE		"KSZ8081RNB "
	#define GETH_INTERFACE	"RMII "
	#define	GETH_COMMENT 	"10/100MHz "
#endif

//------------------------------------------------------------------------------

#ifdef LCD
	#define LCD_DEVICE		"TM4301/TM7000"
	#define LCD_INTERFACE	"18 bits data"
	#define	LCD_COMMENT 	"RGB 6-6-6"
#endif

//------------------------------------------------------------------------------

uint8_t check_hw_on_board(void);

#endif //#ifndef BOARD_INFO_H
