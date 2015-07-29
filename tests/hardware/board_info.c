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

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include "board.h"
#include "chip.h"

#include "cortex-a/cp15.h"
#include "board_memories.h"

#include "peripherals/wdt.h"
#include "peripherals/pmc.h"
#include "peripherals/aic.h"
#include "peripherals/pio.h"

#include "power/act8945a.h"

#include "peripherals/twi.h"
#include "peripherals/twid.h"
#include "memories/at24.h"
#include "test_at24mac402.h"

#include "board_info.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

extern struct _act8945a act8945a;

struct _stResult
{
	uint8_t	result ;
	char	string[48];
} ;

/*------------------------------------------------------------------------------
 *        Functions
 *----------------------------------------------------------------------------*/

static void _display_driver_info (const char* str1,
				  const char* str2,
				  const char* str3)
{
	printf(" Device   : %s\n\r", str1);
	printf(" Interface: %s\n\r", str2);
	printf(" Comment  : %s\n\r", str3);
}

uint8_t check_hw_on_board (void)
{
	uint32_t size, board_pll, board_mck, proc_clk;
	uint8_t i, index, status, sum;
	struct _stResult sresult[16];

	index = 0;

	/* Output information */
	printf("-- Hardware test %s --\n\r", SOFTPACK_VERSION);
	printf("\n\r ======================================== \n\r");
	printf("-- Board name: %s -- \n\r",BOARD_NAME);
	printf("-- Compiled: %s %s -- \n\r", __DATE__, __TIME__);
	printf("\n\r");

	printf("--CONSOLE\n\r");
	printf(" UART1, Bdr=57600\n\r");
	sresult[index].result = 0;
	strcpy (sresult[index++].string, "CONSOLE\t\t");

	//printf("\n\r");
	printf("--MPU\n\r");
	sresult[index].result = display_info_mpu();
	strcpy (sresult[index++].string, "MPU\t\t");

	//printf("\n\r");
	printf(" -MPU FREQ\n\r");
	board_mck = pmc_get_master_clock();
	board_pll = pmc_get_plla_clock();
	proc_clk = pmc_get_processor_clock();
	printf(" Osc      : %dMHz \n\r", (int)BOARD_MAIN_CLOCK_EXT_OSC/1000000);
	printf(" Plla clk : %dMHz\n\r", (int)board_mck/1000000);
	printf(" Proc clk : %dMHz\n\r", (int)proc_clk/1000000);
	printf(" Check PCK: %03dMHz\n\r", (int)board_pll/1000000);

	//printf("\n\r");
	printf(" -BOOT MODE\n\r");
	display_boot_register();

#ifdef ACT8945A
	//printf("\n\r");
	printf("--PMIC \n\r");
	_display_driver_info(PMIC_DEVICE, PMIC_INTERFACE, PMIC_COMMENT);
	act8945a_display_voltage_settings(&act8945a);
	sresult[index].result = 0;
	strcpy (sresult[index++].string, "PMIC\t\t");
#endif

#ifdef AT24MAC402
	//printf("\n\r");
	printf("--EEP \n\r");
	_display_driver_info (EEP_DEVICE, EEP_INTERFACE, EEP_COMMENT);
	sresult[index].result = test_at24mac402();
	strcpy (sresult[index++].string, "EEP\t\t");
#endif

#ifdef NAND_FLASH
	uint8_t Index = 0;
	sPPDSD* OnfiPPDSD = GetPntPPDSD();

	//printf("\n\r");
	printf("--NAND FLASH \n\r");
	GetInfoNandFlash();
	OnfiPPDSD->ONFI_MIB.DeviceManufacturer[8]= 0;
	OnfiPPDSD->ONFI_MIB.DeviceModel[18]=0;
	printf (" DeviceManufacturer       : %s \n\r", &OnfiPPDSD->ONFI_MIB.DeviceManufacturer[0] ) ;
	printf (" JedecManufacturer        : 0x%02X \n\r", &OnfiPPDSD->ONFI_MIB.JedecManufacturer[0] ) ;
	printf (" DeviceModel              : %s \n\r", &OnfiPPDSD->ONFI_MIB.DeviceModel[0] ) ;
	printf (" NumberOfDataBytesPerPage : %d Bytes \n\r", (int)Tab8To32(&OnfiPPDSD->ONFI_MOB.NumberOfDataBytesPerPage[0])/2) ;
	if(OnfiPPDSD->ONFI_MOB.NumberOfSpareBytesPerPage[0]==0xE0)
		printf (" NumberOfSpareBytesPerPage: 64 Bytes \n\r") ;
	else
		printf (" NumberOfSpareBytesPerPage: 32 Words \n\r") ;
	printf (" NumberOfPagesPerBlock    : %d Pages \n\r", OnfiPPDSD->ONFI_MOB.NumberOfPagesPerBlock[0]) ;
	printf (" NumOfBlocksPerLogicalUnit: %d Blocks \n\r", (int)Tab8To32(&OnfiPPDSD->ONFI_MOB.NumberOfBlocksPerLogicalUnit[0]) ) ;
	printf (" NumberOfLogicalUnits     : %d Unit \n\r", OnfiPPDSD->ONFI_MOB.NumberOfLogicalUnits[0] ) ;

	sresult[index].result = 0;
	strcpy (sresult[index++].string, "NAND FLASH\t");
#endif

#ifdef EMMC
	//printf("\n\r");
	printf("--eMMC\n\r");
	_display_driver_info (EMMC_DEVICE, EMMC_INTERFACE, EMMC_COMMENT);
	sresult[index].result = 0;
	strcpy (sresult[index++].string, "EMMC\t\t");
#endif

#ifdef SDRAM_DDR2
	//printf("\n\r");
	printf("--SDRAM DDR2\n\r");
	_display_driver_info (DDR2_DEVICE, DDR2_INTERFACE, DDR2_COMMENT);
	printf(" Add Start/End : 0x%08x - 0x%08x  \n\r", ADDR_DDR2_START, ADDR_DDR2_END) ;
	Result = BOARD_DDRAM_SIZE/1024/1024;
	printf(" Total Size    : %dMb .. %dGB \n\r", (int)Result, (int)Result/128);

	sresult[index].result = 0;
	strcpy (sresult[index++].string, "SDRAM DDR2\t");
#endif

#ifdef SDRAM_DDR3
	//printf("\n\r");
	printf("--SDRAM DDR3\n\r");
	_display_driver_info (DDR3_DEVICE, DDR3_INTERFACE, DDR3_COMMENT);
	printf(" Add Start/End : 0x%08x - 0x%08x  \n\r", ADDR_DDR3_START, ADDR_DDR3_END) ;
	size = BOARD_DDRAM_SIZE/1024/1024;
	printf(" Total Size    : %dMb .. %dGB \n\r", (int)size, (int)size/128);

	#ifndef VARIANT_DDRAM
		board_cfg_ddram();
		cp15_disable_mmu();
		cp15_disable_icache();
		cp15_disable_dcache();
	#endif

	sresult[index].result = test_ddr_sdram (ADDR_DDR3_START, ADDR_DDR3_END, (uint64_t)(ADDR_DDR3_END-ADDR_DDR3_START)/512);
	strcpy (sresult[index++].string, "SDRAM DDR3\t");
#endif

#ifdef SPI_FLASH
	//printf("\n\r");
	printf("--SPI FLASH\n\r");
	_display_driver_info (SPIF_DEVICE, SPIF_INTERFACE, SPIF_COMMENT);
	sresult[index].result = test_spi_flash();
	strcpy (sresult[index++].string, "SPI FLASH\t");
#endif

#ifdef QSPI_FLASH
	//printf("\n\r");
	printf("--QSPI FLASH\n\r");
	_display_driver_info (QSPIF_DEVICE, QSPIF_INTERFACE, QSPIF_COMMENT);
	sresult[index].result = test_qspi_flash();
	strcpy (sresult[index++].string, "QSPI FLASH\t");
#endif

#ifdef SDCARD
	//printf("\n\r");
	printf("--SDCARD\n\r");
	_display_driver_info (SDCARD_DEVICE, SDCARD_INTERFACE, SDCARD_COMMENT);
	sresult[index].result = 0;
	strcpy (sresult[index++].string, "SDCARD\t\t");
#endif

#ifdef GETH
	//printf("\n\r");
	printf("--GETH\n\r");
	_display_driver_info (GETH_DEVICE, GETH_INTERFACE, GETH_COMMENT);
	sresult[index].result = 0;
	strcpy (sresult[index++].string, "GETH\t\t");
#endif

#ifdef LCD
	//printf("\n\r");
	printf("--LCD\n\r");
	_display_driver_info (LCD_DEVICE, LCD_INTERFACE, LCD_COMMENT);
	sresult[index].result = test_lcd();
	strcpy (sresult[index++].string, "LCD\t\t");
#endif

	printf("\n\r ------------- RESULTS ------------------- \n\r");
	sum = 0;
	for (i=0 ; i!=index; i++) {
		printf("%s : %s \n\r", sresult[i].string, sresult[i].result ? "Failed": "ok");
		sum += sresult[i].result;
	}
	printf("\n\r");
	return sum;

}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// End of file
