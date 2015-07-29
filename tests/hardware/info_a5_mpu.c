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

/*------------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

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
	uint8_t	data ;
	char		string[48];
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
	uint32_t	cidr ;
	uint32_t	exid ;
	char		string[16];
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

/*------------------------------------------------------------------------------
 *        Boot config definitions
 *----------------------------------------------------------------------------*/

#define BSCR_ADDR       (0xF8048054u) /**< Boot Sequence Register base address */
#define GPBR_ADDR       (0xF8045400u) /**< General Purpose Backup Register */
#define SECURAM_ADDR    (0xF8044000u) /**< SecuRAM address */
#define SFR_FUSE_ADDR_16  (0xF804C060u) /**< Fuse bit address */

union _boot_bscr {
    struct {
        uint32_t
			gpbrIdx  :  2,
        	gpbrEn   :  1,
        	reserved : 29;
    } bits;
    uint32_t   u32;
} ;


union _boot_config {
	struct {
		uint32_t
			qspi_0:   				2,
			qspi_1:   				2,
			spi_0:					2,
			spi_1:   				2,
			nfc:					2,
			sdmmc_0:				1,
			sdmmc_1:				1,
			uart_console:			4,
			jtag_io_set:			2,
			ext_mem_boot_enable:	1,
			dnu19:					1,
			keys_in_fuse:			1,
			qspi_xip_mode:			1,
			disable_bscr:			1,
			no_pll_init:			1,
			disable_monitor:		1,
			fuse_full_lock:			1,
			prairing_mode:			1,
			cipher_mode:			1,
			// AES customer key has already been written
			customer_key:			1,
			// Activate secure boot mode
			secure_mode:			1,
			sec_dbg:				1,
			jtag_dis:				1;
	} bits;
	uint32_t u32;
};

static const char* _uart_console[16] = {
	"uart_1_ioset_1",
	"uart_0_ioset_1",
	"uart_1_ioset_2",
	"uart_2_ioset_1",
	"uart_2_ioset_2",
	"uart_2_ioset_3",
	"uart_3_ioset_1",
	"uart_3_ioset_2",
	"uart_3_ioset_3",
	"uart_4_ioset_1",
	"disabled",
	"disabled",
	"disabled",
	"disabled",
	"disabled",
};

static const char* _nfc_boot[4] = {
	"nfc_ioset_1",
	"nfc_ioset_2",
	"disabled",
	"disabled",
};

static const char* _spi0_boot[4] = {
	"spi_0_ioset_1",
	"spi_0_ioset_2",
	"disabled",
	"disabled",
};

static const char* _spi1_boot[4] = {
	"spi_1_ioset_1",
	"spi_1_ioset_2",
	"spi_1_ioset_3",
	"disabled",
};

static const char* _qspi0_boot[4] = {
	"qspi_0_ioset_1",
	"qspi_0_ioset_2",
	"qspi_0_ioset_3",
	"disabled",
};
static const char* _qspi1_boot[4] = {
	"qspi_1_ioset_1",
	"qspi_1_ioset_2",
	"qspi_1_ioset_3",
	"disabled",
};

/*------------------------------------------------------------------------------
 *        Local Functions
 *----------------------------------------------------------------------------*/

static char* _board_info_get_arch (uint8_t  arch)
{
	uint8_t index ;

	for (index=0; index!=size_cidr_arch; index++)
	{
		if ( arch == tab_cidr_arch[index].data )
			break;
	}
	return (char*)&tab_cidr_arch[index].string;
}

static char* _board_info_get_cidr_proc (uint32_t cidr, uint32_t exid)
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

/*------------------------------------------------------------------------------
 *        Global Functions
 *----------------------------------------------------------------------------*/

#define CHIP_CIDR_REGISTER (CHIPID->CHIPID_CIDR)
#define CHIP_EXID_REGISTER (CHIPID->CHIPID_EXID)
#define SFR_SER_NUM0_REGISTER (SFR->SFR_SN0)
#define SFR_SER_NUM1_REGISTER (SFR->SFR_SN1)

uint8_t display_info_mpu (void)
{
	uint32_t reg_cidr, reg_exid;
	struct _chipid_cidr cidr;

	reg_cidr = CHIPID->CHIPID_CIDR;
	reg_exid = CHIPID->CHIPID_EXID;
	cidr = *((struct _chipid_cidr *)&CHIP_CIDR_REGISTER);

	printf(" Reg.EXID \t\t\t\t\t: %08X\n\r",
	       (unsigned int)reg_exid);
	printf(" Reg.CIDR\t\t\t\t\t: %08X\n\r",
	       (unsigned int)reg_cidr);
	printf (" VERSION - Version of the Device \t\t: %02x \n\r",
		(unsigned int)cidr.version);
	printf (" EPROC - Embedded ARM processor \t\t:%s \n\r",
		tab_cidr_eproc[cidr.eproc]+2) ;
	printf (" EPROC - Embedded processor on board \t\t: %s \n\r", _board_info_get_cidr_proc(reg_cidr, reg_exid)) ;
	printf (" SRAMSIZE - Size of the embedded SRAM \t\t:%s \n\r", tab_cidr_sramsiz[cidr.sramsiz ]+2) ;
	printf (" ARCH - Set of embedded peripherals \t\t: %s \n\r", _board_info_get_arch(cidr.arch)) ;
	printf (" NVPTYP - Type of embedded non-volatile memory \t:%s \n\r", tab_cidr_nvtyp[cidr.nvptyp]+2) ;
	printf (" NVPSIZ1 - Size of embedded non-volatile memory :%s \n\r", tab_cidr_nvpsiz[cidr.nvpsiz]+2) ;
	printf (" NVPSIZ2 - Size of embedded non-volatile memory :%s \n\r", tab_cidr_nvpsiz[cidr.nvpsiz2]+2) ;

	printf (" SERIAL NUMBER 0- \t\t\t: 0x%08x \n\r", (uint32_t)SFR_SER_NUM0_REGISTER);
	printf (" SERIAL NUMBER 1- \t\t\t: 0x%08x \n\r", (uint32_t)SFR_SER_NUM1_REGISTER);
	return 0;
}

/* Display on console the Boot configuration
 *
 */
void display_boot_register (void)
{
	union _boot_config boot_config;
	union _boot_bscr boot_bscr; // backup register
	uint32_t fuse_bits;

	boot_bscr.u32 = *(uint32_t*)BSCR_ADDR;
	printf (" BSCR Register: 0x%08X \n\r",boot_bscr.u32);
	printf (" GPBR Enable \t\t: %s \n\r", boot_bscr.bits.gpbrEn ? "enable" : "disable" ) ;
	printf (" GPBR Index \t\t: %02d \n\r", boot_bscr.bits.gpbrIdx);

	boot_config.u32 = ((uint32_t*)(GPBR_ADDR))[boot_bscr.bits.gpbrIdx] ;
	printf (" GPBR Register: 0x%08X \n\r",boot_config.u32) ;
	printf (" QSPI0 \t\t\t: %s \n\r", _qspi0_boot[boot_config.bits.qspi_0]) ;
	printf (" QSPI1 \t\t\t: %s \n\r", _qspi1_boot[boot_config.bits.qspi_1]) ;
	printf (" SPI0 \t\t\t: %s \n\r", _spi0_boot[boot_config.bits.spi_0]) ;
	printf (" SPI1 \t\t\t: %s \n\r", _spi1_boot[boot_config.bits.spi_1]) ;
	printf (" NFC \t\t\t: %s \n\r", _nfc_boot[boot_config.bits.nfc]) ;
	printf (" UART Console \t\t: %s \n\r", _uart_console[boot_config.bits.uart_console]) ;
	printf (" JTAG \t\t\t: jtag_ioset_%x \n\r", boot_config.bits.jtag_io_set) ;
	printf (" SDMMC_0 \t\t: %s \n\r", boot_config.bits.sdmmc_0 ? "enable" : "disable" ) ;
	printf (" SDMMC_1 \t\t: %s \n\r", boot_config.bits.sdmmc_1 ? "enable" : "disable" ) ;
	printf (" Ext. memory boot \t: %s \n\r", boot_config.bits.ext_mem_boot_enable ? "ENABLE" : "DISABLE" ) ;
	printf (" Reserved bit 19 \n\r");
	printf (" Keys in Fuse \t\t: %s \n\r", boot_config.bits.keys_in_fuse ? "1" : "0" ) ;
	printf (" QSPI XIP mode \t\t: %s \n\r", boot_config.bits.qspi_xip_mode ? "1" : "0" ) ;
	printf (" Disable BSCR \t\t: %s \n\r", boot_config.bits.disable_bscr ? "1" : "0" ) ;
	printf (" No PLL Init \t\t: %s \n\r", boot_config.bits.no_pll_init ? "1" : "0" ) ;
	printf (" Disable Monitor \t: %s \n\r", boot_config.bits.disable_monitor ? "1" : "0" ) ;
	printf (" Fuse Full Lock \t: %s \n\r", boot_config.bits.fuse_full_lock ? "1" : "0" ) ;
	printf (" Praising Mode \t\t: %s \n\r", boot_config.bits.prairing_mode ? "1" : "0" ) ;
	printf (" Cipher Mode \t\t: %s \n\r", boot_config.bits.cipher_mode ? "1" : "0" ) ;
	printf (" Customer Key \t\t: %s \n\r", boot_config.bits.customer_key ? "1" : "0" ) ;
	printf (" Secure Mode \t\t: %s \n\r", boot_config.bits.secure_mode ? "1" : "0" ) ;
	printf (" Secure DBG \t\t: %s \n\r", boot_config.bits.sec_dbg ? "1" : "0" ) ;
	printf (" JTAG Disable \t\t: %s \n\r", boot_config.bits.jtag_dis ? "1" : "0" ) ;

	fuse_bits = *(uint32_t*)SFR_FUSE_ADDR_16;
	printf (" SFR Fuse Register: 0x%08X \n\r",fuse_bits) ;
}

