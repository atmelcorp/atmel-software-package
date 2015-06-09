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

#include "peripherals/pmc.h"
#include "peripherals/twid.h"
#include "power/act8945A.h"

#include "memories/at25dfx.h"

#include "board_info.h"

//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------

typedef char string_t16[16];
typedef char string_t32[32];

const string_t16 tab_cidr_eproc[] =
{
  "00 SAM x7    ",
  "01 ARM946ES  ",
  "02 ARM7TDMI  ",
  "03 Cortex-M3 ",
  "04 ARM920T   ",
  "05 ARM926EJS ",
  "06 Cortex-A5 ",
  "07 Cortex-M4 "
};
#define size_cidr_eproc  sizeof(tab_cidr_eproc)/ sizeof(string_t16)

const string_t16 tab_cidr_nvpsiz[] =
{
  "00 None        ",
  "01 8K bytes    ",
  "02 16K bytes   ",
  "03 32K bytes   ",
  "04 Reserved    ",
  "05 64K bytes   ",
  "06 Reserved    ",
  "07 128K bytes  ",
  "08 160K bytes  ",
  "09 256K bytes  ",
  "10 512K bytes  ",
  "11 Reserved    ",
  "12 1024K bytes ",
  "13 Reserved    ",
  "14 2048K bytes ",
  "15 Reserved    "
};
#define size_cidr_nvpsiz  sizeof(tab_cidr_nvpsiz)/ sizeof(string_t16)

const string_t16 tab_cidr_sramsiz[] =
{
  "00 48K bytes   ",
  "01 192K bytes  ",
  "02 384K bytes  ",
  "03 6K bytes    ",
  "04 24K bytes   ",
  "05 4K bytes    ",
  "06 80K bytes   ",
  "07 160K bytes  ",
  "08 8K bytes    ",
  "09 16K bytes   ",
  "10 32K bytes   ",
  "11 64K bytes   ",
  "12 128K bytes  ",
  "13 256K bytes  ",
  "14 96K bytes   ",
  "15 512K bytes  "
};
#define size_cidr_sramsiz  sizeof(tab_cidr_sramsiz)/ sizeof(string_t16)

typedef struct
{
  uint8_t 	data ;
  char  	string[48];
} stDesc , pstDesc ;

const stDesc tab_cidr_arch[] =
{
  {0x00, "Unknow "},
  {0x19, "AT91SAM9xx Series"},
  {0x29, "AT91SAM9XExx Series"},
  {0x34, "AT91x34 Series"},
  {0x37, "CAP7 Series"},
  {0x39, "CAP9 Series"},
  {0x3B, "CAP11 Series"},
  {0x40, "AT91x40 Series"},
  {0x42, "AT91x42 Series"},
  {0x55, "AT91x55 Series"},
  {0x60, "AT91SAM7Axx Series"},
  {0x61, "AT91SAM7AQxx Series"},
  {0x63, "AT91x63 Series"},
  {0x70, "AT91SAM7Sxx Series"},
  {0x71, "AT91SAM7XCxx Series"},
  {0x72, "AT91SAM7SExx Series"},
  {0x73, "AT91SAM7Lxx Series"},
  {0x75, "AT91SAM7Xxx Series"},
  {0x76, "AT91SAM7SLxx Series"},
  {0x80, "ATSAM3UxC Series (100-pin version)"},
  {0x81, "ATSAM3UxE Series (144-pin version)"},
  {0x83, "ATSAM3AxC Series (100-pin version)"},
  {0x84, "ATSAM3XxC Series (100-pin version)"},
  {0x85, "ATSAM3XxE Series (144-pin version)"},
  {0x86, "ATSAM3XxG Series (208/217-pin version)"},
  {0x88, "ATSAM3SxA Series (48-pin version)"},
  {0x89, "ATSAM3SxB Series (64-pin version)"},
  {0x8A, "ATSAM3SxC Series (100-pin version)"},
  {0x92, "AT91x92 Series"},
  {0x93, "ATSAM3NxA Series (48-pin version)"},
  {0x94, "ATSAM3NxB Series (64-pin version)"},
  {0x95, "ATSAM3NxC Series (100-pin version)"},
  {0x98, "ATSAM3SDxA Series (48-pin version)"},
  {0x99, "ATSAM3SDxB Series (64-pin version)"},
  {0x9A, "ATSAM3SDxC Series (100-pin version)"},
  {0xA5, "Cortex-A5 Series"},
  {0xF0, "AT75Cxx Series"},
  {0xFF, "Error: Not Found !!!!!!"},
};
#define size_cidr_arch  sizeof(tab_cidr_arch)/ sizeof(stDesc)

const string_t32 tab_cidr_nvtyp[] =
{
  "00 ROM",
  "01 ROMless or on-chip Flash",
  "02 Embedded Flash Memory",
  "03 ROM and Embedded Flash Memory",
  "04 SRAM emulating ROM"
};
#define size_cidr_nvtyp  sizeof(tab_cidr_nvtyp)/ sizeof(string_t32)

struct _chipid_cidr
{
	uint32_t
    version : 5,
    eproc : 3,
    nvpsiz : 4,
    nvpsiz2 : 4,
	sramsiz : 4,
	arch : 8,
	nvptyp : 3 ,
    ext : 1;
} ;

typedef struct
{
  uint32_t 	cidr ;
  uint32_t 	exid ;
  char  	string[16];
} stProc , *pstProc ;

const stProc tab_cidr_proc[] =
{
  {0x00041000, 0x00000000, "SAMA5D33 "},
  {0x00414300, 0x00000000, "SAMA5D33 "},
  {0x00041001, 0x00000000, "SAMA5D34 "},
  {0x00414301, 0x00000000, "SAMA5D34 "},
  {0x00580000, 0x00000000, "SAMA5D35 "},
  {0x00584300, 0x00000000, "SAMA5D35 "},
  {0x00440000, 0x00000000, "SAMA5D31 "},
  {0x00444300, 0x00000000, "SAMA5D31 "},
  {0x00004301, 0x00000000, "SAMA5D36 "},

  {0x00000000, 0x00000000, "SAMA5D4x "},
  {0x8A5C0760, 0x00000000, "SAMA5D4x "},
  {0x8A5C07C0, 0x00000000, "SAMA5D4x "},

  {0x8a5c08c0, 0x0000005A, "SAMA5D21-CU "},
  {0x8a5c08c0, 0x00000059, "SAMA5D22-CU "},
  {0x8a5c08c0, 0x00000069, "SAMA5D22-CN "},
  {0x8a5c08c0, 0x00000058, "SAMA5D23-CU "},
  {0x8a5c08c0, 0x00000004, "SAMA5D24-CX "},
  {0x8a5c08c0, 0x00000014, "SAMA5D24-CU "},
  {0x8a5c08c0, 0x00000012, "SAMA5D26-CU "},
  {0x8a5c08c0, 0x00000011, "SAMA5D27-CU "},
  {0x8a5c08c0, 0x00000021, "SAMA5D27-CN "},
  {0x8a5c08c0, 0x00000010, "SAMA5D28-CU "},
  {0x8a5c08c0, 0x00000020, "SAMA5D28-CN "},
} ;
#define NB_ELEMENT_PROC  sizeof(tab_cidr_proc)/ sizeof(stProc)

//------------------------------------------------------------------------------
//         Local function
//------------------------------------------------------------------------------

char* _board_info_get_arch (uint8_t  arch)
{
  uint8_t index ;

  for (index=0; index!=size_cidr_arch; index++)
  {
    if ( arch == tab_cidr_arch[index].data )
      break;
  }
  return (char*)&tab_cidr_arch[index].string;
}

char* _board_info_get_cidr_proc (uint32_t cidr, uint32_t exid)
{
  uint8_t index ;

  for (index=0; index!=NB_ELEMENT_PROC; index++)
  {
	  if ( cidr == tab_cidr_proc[index].cidr ) {
		  if ( exid == tab_cidr_proc[index].exid ) {
      		break;
		  }
	  }
  }
  return (char*)&tab_cidr_proc[index].string;
}

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

#define CHIP_CIDR_REGISTER (CHIPID->CHIPID_CIDR)
#define CHIP_EXID_REGISTER (CHIPID->CHIPID_EXID)
#define SFR_SER_NUM0_REGISTER (SFR->SFR_SN0)
#define SFR_SER_NUM1_REGISTER (SFR->SFR_SN1)

uint8_t EditInfoMpu (void)
{
  uint32_t reg_cidr, reg_exid;
  struct _chipid_cidr cidr;

	reg_cidr = REG_CHIPID_CIDR;
  	reg_exid = REG_CHIPID_EXID;
	cidr = *((struct _chipid_cidr *)&CHIP_CIDR_REGISTER);

    printf(" Reg.EXID \t\t\t\t\t: %08X\n\r", reg_exid);
    printf(" Reg.CIDR\t\t\t\t\t: %08X\n\r", reg_cidr);
    printf ( " VERSION - Version of the Device \t\t: %02x \n\r", cidr.version) ;
	printf ( " EPROC - Embedded ARM processor \t\t:%s \n\r", tab_cidr_eproc[cidr.eproc]+2) ;
	printf ( " EPROC - Embedded processor on board \t\t: %s \n\r", _board_info_get_cidr_proc(reg_cidr, reg_exid)) ;
	printf ( " SRAMSIZE - Size of the embedded SRAM \t\t:%s \n\r", tab_cidr_sramsiz[cidr.sramsiz ]+2) ;
	printf ( " ARCH - Set of embedded peripherals \t\t: %s \n\r", _board_info_get_arch(cidr.arch)) ;
	printf ( " NVPTYP - Type of embedded non-volatile memory \t:%s \n\r", tab_cidr_nvtyp[cidr.nvptyp]+2) ;
	printf ( " NVPSIZ1 - Size of embedded non-volatile memory :%s \n\r", tab_cidr_nvpsiz[cidr.nvpsiz]+2) ;
	printf ( " NVPSIZ2 - Size of embedded non-volatile memory :%s \n\r", tab_cidr_nvpsiz[cidr.nvpsiz2]+2) ;

	printf ( " SERIAL NUMBER 0- : 0x%08x \n\r", SFR_SER_NUM0_REGISTER) ;
	printf ( " SERIAL NUMBER 1- : 0x%08x \n\r", SFR_SER_NUM1_REGISTER) ;
    //printf("\n\r");
	return 0;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------

struct _stResult
{
  uint8_t 	result ;
  char  	string[48];
} ;

#define BOARD_MAIN_CLOCK_EXT_OSC_MHZ BOARD_MAIN_CLOCK_EXT_OSC/1000000

void check_hw_on_board (void)
{
	uint32_t MulA, PllaDiv2, Result, board_mck;
	uint8_t i, index, status, sum;
	struct _stResult sresult[16];

	index = 0;

	/* Output information */
	printf("-- Hardware test %s --\n\r", SOFTPACK_VERSION);
    printf("\n\r ======================================== \n\r");
    printf("-- Board name: %s -- \n\r",BOARD_NAME);
    printf("-- Compiled: %s %s -- \n\r", __DATE__, __TIME__);

    //printf("\n\r");
    printf("--CONSOLE\n\r");
	printf(" UART1, Bdr=57600\n\r");
	sresult[index].result = 0;
	strcpy (sresult[index++].string, "CONSOLE\t\t");

    //printf("\n\r");
    printf("**MPU\n\r");
    sresult[index].result = EditInfoMpu();
	strcpy (sresult[index++].string, "MPU\t\t");

	//printf("\n\r");
    printf("--FREQ\n\r");
    MulA = (CKGR_PLLAR_MULA_Msk & PMC->CKGR_PLLAR) >> CKGR_PLLAR_MULA_Pos;
	MulA ++;
    PllaDiv2 = (PMC->PMC_MCKR & PMC_MCKR_PLLADIV2 ? 2 : 1);
	board_mck = pmc_get_master_clock();
    printf(" Osc:%dMHz \n\r Main OSC : %dMHz\n\r", BOARD_MAIN_CLOCK_EXT_OSC_MHZ, (int)board_mck/1000000);
    printf(" Check PCK: %03dMHz\n\r", (int)MulA*BOARD_MAIN_CLOCK_EXT_OSC_MHZ/PllaDiv2);


#ifdef CONFIG_HAVE_PMIC_ACT8945A
	//printf("\n\r");
    printf("--PMIC \n\r");
	_ACT8945A_display_voltage_setting();
	sresult[index].result = 0;
	strcpy (sresult[index++].string, "PMIC\t\t");
#endif

#ifdef AT24MAC402
	//printf("\n\r");
    printf("--EEP \n\r");
	printf(" Device   : %s\n\r", EEP_DEVICE);
    printf(" Interface: %s\n\r", EEP_INTERFACE);
    printf(" Comment  : %s\n\r", EEP_COMMENT);
	status = at24mac402_begin();
	sresult[index].result = status;
	strcpy (sresult[index++].string, "EEP\t\t");
	if(status==TWI_SUCCES) {
		at24mac402_display_register();
	}
#endif


#ifdef NAND_FLASH
	uint8_t Index = 0;
	sPPDSD* OnfiPPDSD = GetPntPPDSD();

    //printf("\n\r");
    printf("--NAND FLASH \n\r);
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
	printf(" Device   : %s\n\r", EMMC_DEVICE);
    printf(" Interface: %s\n\r", EMMC_INTERFACE);
    printf(" Comment  : %s\n\r", EMMC_COMMENT);

	sresult[index].result = 0;
	strcpy (sresult[index++].string, "EMMC\t\t");
#endif

#ifdef SDRAM_DDR2
    //printf("\n\r");
    printf("--SDRAM DDR2\n\r");
	printf(" Device   : %s\n\r", DDR2_DEVICE);
    printf(" Interface: %s\n\r", DDR2_INTERFACE);
    printf(" Comment  : %s\n\r", DDR2_COMMENT);
    printf(" Add Start/End : 0x%08x - 0x%08x  \n\r", ADDR_DDR2_START, ADDR_DDR2_END) ;
    Result = BOARD_DDRAM_SIZE/1024/1024;
    printf(" Total Size    : %dMb .. %dGB \n\r", (int)Result, (int)Result/128);

	sresult[index].result = 0;
	strcpy (sresult[index++].string, "SDRAM DDR2\t");
#endif

#ifdef SDRAM_DDR3
    //printf("\n\r");
    printf("--SDRAM DDR3\n\r");
	printf(" Device   : %s\n\r", DDR3_DEVICE);
    printf(" Interface: %s\n\r", DDR3_INTERFACE);
    printf(" Comment  : %s\n\r", DDR3_COMMENT);
    printf(" Add Start/End : 0x%08x - 0x%08x  \n\r", ADDR_DDR3_START, ADDR_DDR3_END) ;
    Result = BOARD_DDRAM_SIZE/1024/1024;
    printf(" Total Size    : %dMb .. %dGB \n\r", (int)Result, (int)Result/128);

	sresult[index].result = 0;
	strcpy (sresult[index++].string, "SDRAM DDR3\t");
#endif

#ifdef SPI_FLASH
    //printf("\n\r");
    printf("--SPI FLASH\n\r");
	printf(" Device   : %s\n\r", SPIF_DEVICE);
    printf(" Interface: %s\n\r", SPIF_INTERFACE);
    printf(" Comment  : %s\n\r", SPIF_COMMENT);

	at25dfx_open();
	status = at25dfx_unlock_sectors();
	if (!status) {
		at25dfx_get_status();
		at25dfx_print_device_info();
	}
	sresult[index].result = status ? 1 : 0;
	strcpy (sresult[index++].string, "SPI FLASH\t");
#endif

#ifdef QSPI_FLASH
    //printf("\n\r");
    printf("--QSPI FLASH\n\r");
	printf(" Device   : %s\n\r", QSPIF_DEVICE);
    printf(" Interface: %s\n\r", QSPIF_INTERFACE);
    printf(" Comment  : %s\n\r", QSPIF_COMMENT);

	sresult[index].result = 0;
	strcpy (sresult[index++].string, "QSPI FLASH\t");
#endif

#ifdef SDCARD
    //printf("\n\r");
    printf("--SDCARD\n\r");
	printf(" Device   : %s\n\r", SDCARD_DEVICE);
    printf(" Interface: %s\n\r", SDCARD_INTERFACE);
    printf(" Comment  : %s\n\r", SDCARD_COMMENT);

	sresult[index].result = 0;
	strcpy (sresult[index++].string, "SDCARD\t\t");
#endif

#ifdef GETH
    //printf("\n\r");
    printf("--GETH\n\r");
	printf(" Device   : %s\n\r", GETH_DEVICE);
    printf(" Interface: %s\n\r", GETH_INTERFACE);
    printf(" Comment  : %s\n\r", GETH_COMMENT);

	sresult[index].result = 0;
	strcpy (sresult[index++].string, "GETH\t\t");
#endif

#ifdef LCD
    //printf("\n\r");
    printf("--LCD\n\r");
	printf(" Device   : %s\n\r", LCD_DEVICE);
    printf(" Interface: %s\n\r", LCD_INTERFACE);
    printf(" Comment  : %s\n\r", LCD_COMMENT);

	sresult[index].result = 1;
	strcpy (sresult[index++].string, "LCD\t\t");
#endif

    printf("\n\r ------------- RESULTS ------------------- \n\r");
	sum = 0;
	for (i=0 ; i!=index; i++) {
		printf("%s : %s \n\r", sresult[i].string, sresult[i].result ? "FAILED": "OK");
		sum += sresult[i].result;
	}
    printf("\n\r");

}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// End of file
