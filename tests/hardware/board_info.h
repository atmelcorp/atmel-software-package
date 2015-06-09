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

#define NOERROR 0
#define ERROR   1

#define CKGR_PLLAR_DIVA_Msk (0xffu << CKGR_PLLAR_DIVA_Pos) /**< \brief (CKGR_PLLAR) Divider A */
#define CKGR_PLLAR_DIVA_Pos 0

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------

#define AT24MAC402
// #define ONE-WIRE
// #define NAND_FLASH
//#define EMMC
// #define SDRAM_DDR2
#define SDRAM_DDR3
#define	EEPROM
#define SPI_FLASH
//#define QSPI_FLASH
//#define SDCARD
//#define GETH
//#define LCD

//------------------------------------------------------------------------------

#ifdef AT24MAC402
	#include "memories/24mac402.h"

	#define EEP_DEVICE		"AT24MAC402"
	#define EEP_INTERFACE	"TWI1, IOS2"
	#define	EEP_COMMENT 	"Serial number + Mac addr"
#endif

//------------------------------------------------------------------------------

#ifdef NAND_FLASH

#include "libnandflash/include/SkipBlockNandFlash.h"
#include "libnandflash/include/RawNandFlash.h"
#include "libnandflash/include/NandSpareScheme.h"
#include "libnandflash/include/NandFlashModelList.h"
#include "libnandflash/include/NandFlashModel.h"
#include "libnandflash/include/NandCommon.h"
#include "libnandflash/include/EccNandFlash.h"
#include "libnandflash/include/NandFlashOnfi.h"

	#define NAND_FLASH_DEVICE		" "
	#define NAND_FLASH_INTERFACE	" "
	#DEFINE	NAND_FLASH_COMMENT 	" "

typedef struct RevisionInfoFeaturesBolck
{
  char    ParamPageSignature[4-0] ;
  uint8_t RevisionNumber[6-4] ;
  uint8_t FeaturesSpported[8-6] ;
  uint8_t OptionalCommandsSupported[10-8] ;
  uint8_t Reserved0[12-10];
  uint8_t ExtendedParameterPageLength[14-12];
  uint8_t  NumberOfParameterPages[15-14] ;
  uint8_t Reserved1[32-15] ;
} sRIFB, *psRIFB ;

typedef struct ManufacturerInfoBlock
{
  char    DeviceManufacturer[44-32] ;
  char    DeviceModel[64-44] ;
  uint8_t JedecManufacturer[65-64] ;
  uint8_t DateCode[67-65] ;
  uint8_t Reserved[80-67] ;
} sMIB, *psMIB ;

typedef struct MemoryOrgBlock
{
  uint8_t NumberOfDataBytesPerPage[84-80] ;
  uint8_t NumberOfSpareBytesPerPage[86-84] ;
  uint8_t NumberOfDataBytesPerPartialPage[90-86] ;
  uint8_t NumberOfSpareBytesPerPartialPage[92-90] ;
  uint8_t NumberOfPagesPerBlock[96-92] ;
  uint8_t NumberOfBlocksPerLogicalUnit[100-96] ; //LUN)
  uint8_t NumberOfLogicalUnits[101-100] ; // (LUNs)
  uint8_t NumberOfAddressCycles[102-101] ;
  uint8_t NumberOfBitsperCell[103-102] ;
  uint8_t BadBlocksMaxPerLUN[105-103] ;
  uint8_t BlockEndurance[107-105] ;
  uint8_t GuaranteedValidBlocksAtBeginningOfTarget[108-107] ;
  uint8_t BlockEnduranceForGuaranteedValidBlocks[110-108] ;
  uint8_t NumberOfProgramsPerPage[111-110] ;
  uint8_t PartialProgrammingAttributes[112-111] ;
  uint8_t NumberOfBitsECCCorrectability[113-112] ;
  uint8_t NumberOfInterleavedAddressBits[114-113] ;
  uint8_t InterleavedOperationAttributes[115-114] ;
  uint8_t Reserved[128-115] ;
} sMOB, *psMOB ;

typedef struct ElectricalParametersBlock
{
  uint8_t IOPinCapacitance[129-128] ;
  uint8_t AsynchronousTimingModeSupport[131-129] ;
  uint8_t AsynchronousProgramCacheTimingModeSupport[133-131] ;
  uint8_t MaximumPageProgramTime[135-133] ;
  uint8_t MaximumBlockEraseTime[137-135] ;
  uint8_t MaximumPageReadTime[139-137] ;
  uint8_t MinimumChangeColumnSetupTime[141-139] ;
  uint8_t SourceSynchronousTimingModeSupport[143-141] ;
  uint8_t SourceSynchronousFeatures[144-143] ;
  uint8_t ClkIputPinCapacitance[146-144] ;
  uint8_t IoPinCapacitance[148-146] ;
  uint8_t InputPinCapacitanceTyp[150-148] ;
  uint8_t InputPinCapacitanceMax[151-150] ;
  uint8_t DriverStrengthSupport[152-150] ;
  uint8_t MaximumInterleavedPageReadTime[154-152] ;
  uint8_t ProgramPageRegisterClearEnhancement[156-154] ;
  uint8_t Reserved[164-156] ;
} sEPB, *psEPB;

typedef struct VendorBlock
{
  uint8_t VendorSpecificRevisionNumber[166-164] ;
  uint8_t VendorSpecific[254-166] ;
  uint8_t IntegrityCrc[256-254] ;
} sVB, *psVB ;

typedef struct RedundantParameterPages
{
  uint8_t ValueBytes0[512-256] ;
  uint8_t ValueBytes1[768-256] ;
  uint8_t AdditionalRedundantParameterPages[897-768];
} sRPP, *psRPP ;

typedef struct ParameterPageDataStructureDefinition
{
  sRIFB ONFI_RIFB ;
  sMIB  ONFI_MIB ;
  sMOB  ONFI_MOB ;
  sEPB  ONFI_EPB ;
  sVB   ONFI_VB ;
  sRPP  ONFI_RPP ;
} sPPDSD, *psPPDSD ;

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
 	#define OFFSET_MEMORY               0x00000000
	#define ADDR_DDR3_START				DDR_CS_ADDR	+ OFFSET_MEMORY
	#define ADDR_DDR3_END				ADDR_DDR3_START + BOARD_DDRAM_SIZE

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
	#define	QSPIF_COMMENT 	" "
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

#endif //#ifndef BOARD_INFO_H
