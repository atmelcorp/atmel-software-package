/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2017, Atmel Corporation
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
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "nvm/spi-nor/spi-nor.h"

/*----------------------------------------------------------------------------
 *        Macros
 *----------------------------------------------------------------------------*/

#define ID5(_jedec_id, _ext_id)			\
	.id = {					\
		((_jedec_id) >> 16) & 0xff,	\
		((_jedec_id) >>  8) & 0xff,	\
		((_jedec_id) >>  0) & 0xff,	\
		((_ext_id) >> 8) & 0xff,	\
		((_ext_id) >> 0) & 0xff,	\
	},					\
	.id_len = ((_ext_id) ? 5 : 3)

#define SST25(_name, _jedec_id, _n_sectors)	\
	.name = _name,				\
	ID5(_jedec_id, 0),			\
	.sector_size = 65536U,			\
	.n_sectors = (_n_sectors),		\
	.page_size = 256,			\
	.flags = SNOR_SECT_4K | SNOR_NO_4BAIS | SNOR_SKIP_SFDP

#define SST26(_name, _jedec_id, _n_sectors)	\
	.name = _name,				\
	ID5(_jedec_id, 0),			\
	.sector_size = 4096U,			\
	.n_sectors = (_n_sectors),		\
	.page_size = 256,			\
	.flags = SNOR_SECT_4K_ONLY | SNOR_SST_ULBPR | SNOR_SKIP_SFDP

#define N25Q(_name, _jedec_id, _n_sectors)	\
	.name = _name,				\
	ID5(_jedec_id, 0),			\
	.sector_size = 65536U,			\
	.n_sectors = (_n_sectors),		\
	.page_size = 256,			\
	.flags = SNOR_HAS_FSR | SNOR_SECT_4K | SNOR_NO_4BAIS

#define AT25(_name, _jedec_id, _n_sectors)	\
	.name = _name,				\
	ID5(_jedec_id, 0),			\
	.sector_size = 65536U,			\
	.n_sectors = (_n_sectors),		\
	.page_size = 256,			\
	.flags = SNOR_SECT_4K | SNOR_NO_4BAIS | SNOR_SKIP_SFDP | SNOR_SECT_32K

#define M25P(_name, _jedec_id, _n_sectors, _s_sector)	\
	.name = _name,					\
	ID5(_jedec_id, 0),				\
	.sector_size = (_s_sector),			\
	.n_sectors = (_n_sectors),			\
	.page_size = 256,				\
	.flags = SNOR_NO_4BAIS | SNOR_SKIP_SFDP

#define W25(_name, _jedec_id, _n_sectors)	\
	.name = _name,				\
	ID5(_jedec_id, 0),			\
	.sector_size = 65536U,			\
	.n_sectors = (_n_sectors),		\
	.page_size = 256,			\
	.flags = SNOR_SECT_4K | SNOR_NO_4BAIS | SNOR_SKIP_SFDP

#define MX25(_name, _jedec_id, _n_sectors)	\
	.name = _name,				\
	ID5(_jedec_id, 0),			\
	.sector_size = 65536U,			\
	.n_sectors = (_n_sectors),		\
	.page_size = 256,			\
	.flags = SNOR_SECT_4K | SNOR_NO_4BAIS

#define MX25L(_name, _jedec_id, _n_sectors)	\
	.name = _name,				\
	ID5(_jedec_id, 0),			\
	.sector_size = 65536U,			\
	.n_sectors = (_n_sectors),		\
	.page_size = 256,			\
	.flags = SNOR_SECT_4K

#define MX66L(_name, _jedec_id, _n_sectors)	\
	.name = _name,				\
	ID5(_jedec_id, 0),			\
	.sector_size = 65536U,			\
	.n_sectors = (_n_sectors),		\
	.page_size = 256,			\
	.flags = SNOR_SECT_4K

#define S25FL(_name, _jedec_id, _n_sectors, _s_sector, _flags)	\
	.name = _name,					\
	ID5(_jedec_id, 0),				\
	.sector_size = (_s_sector),			\
	.n_sectors = (_n_sectors),			\
	.page_size = 256,				\
	.flags = (_flags)

/*----------------------------------------------------------------------------
 *        Exported Variables
 *----------------------------------------------------------------------------*/

const struct spi_nor_info spi_nor_ids[] = {
	/* Atmel */
	{ AT25("at25df021",   0x1f4300,    4), },
	{ AT25("at25df041a",  0x1f4401,    8), },
	{ AT25("at25df018a",  0x1f4501,   16), },
	{ AT25("at25df0161a", 0x1f4601,   32), },
	{ AT25("at25df0161",  0x1f4602,   32), },
	{ AT25("at25df321",   0x1f4700,   64), },
	{ AT25("at25df321a",  0x1f4701,   64), },
	{ AT25("at25df321",   0x1f4700,   64), },
	{ AT25("at25df321a",  0x1f4701,   64), },
	{ AT25("at25df641",   0x1f4b00,  128), },
	{ AT25("at25df512b",  0x1f6500,    1), },
	{ AT25("at25df512b",  0x1f6501,    1), },

	/* Micron */
	{ M25P("m25p05",     0x202010,    2, 32768U), },
	{ M25P("m25p10",     0x202011,    4, 32768U), },
	{ M25P("m25p20",     0x202012,    4, 65536U), },
	{ M25P("m25p40",     0x202013,    8, 65536U), },
	{ M25P("m25p80",     0x202014,   16, 65536U), },
	{ M25P("m25p16",     0x202015,   32, 65536U), },
	{ M25P("m25p32",     0x202016,   64, 65536U), },
	{ M25P("m25p64",     0x202017,  128, 65536U), },
	{ N25Q("n25q032ax1", 0x20bb16,   64), },
	{ N25Q("n25q032ax3", 0x20ba16,   64), },
	{ N25Q("n25q064ax1", 0x20bb17,  128), },
	{ N25Q("n25q064ax3", 0x20ba17,  128), },
	{ N25Q("n25q128ax1", 0x20bb18,  256), },
	{ N25Q("n25q128ax3", 0x20ba18,  256), },
	{ N25Q("n25q256ax1", 0x20bb19,  512), },
	{ N25Q("n25q256ax3", 0x20ba19,  512), },
	{ N25Q("n25q512ax1", 0x20bb20, 1024), },
	{ N25Q("n25q512ax3", 0x20ba20, 1024), },
	{ N25Q("n25q00ax1",  0x20bb21, 2048), },
	{ N25Q("n25q00ax3",  0x20ba21, 2048), },

	/* Winbond */
	{ W25("w25x10",  0xef3011,   1), },
	{ W25("w25x20",  0xef3012,   2), },
	{ W25("w25x40",  0xef3013,   4), },
	{ W25("w25x80",  0xef3014,   8), },
	{ W25("w25q128", 0xef4018,  64), },
	{ W25("w25q256", 0xef4019, 128), },

	/* Macronix */
	{ MX25("mx25l512",     0xc22010,    1), },
	{ MX25("mx25l4005",    0xc22013,    8), },
	{ MX25("mx25l8005",    0xc22014,   16), },
	{ MX25("mx25l3205",    0xc22016,   64), },
	{ MX25("mx25l6405",    0xc22017,  128), },
	{ MX25L("mx25l12835f", 0xc22018,  256), },
	{ MX25L("mx25l25673f", 0xc22019,  512), },
	{ MX25L("mx25l51245f", 0xc2201a, 1024), },
	{ MX66L("mx66l1g45g",  0xc2201b, 2048), },

	/* SST */
	{ SST25("sst25vf032",  0xbf254a,   64), },
	{ SST25("sst25vf064",  0xbf254b,  128), },
	{ SST25("sst25vf040b", 0xbf254d,    4), },
	{ SST25("sst25vf080b", 0xbf254e,    8), },
	{ SST26("sst26vf016b", 0xbf2641,  512), },
	{ SST26("sst26vf032b", 0xbf2642, 1024), },
	{ SST26("sst26vf064b", 0xbf2643, 2048), },
	{ SST26("sst26wf040b", 0xbf2654,  128), },
	{ SST26("sst26wf080b", 0xbf2658,  256), },

	/* Spansion */
	{ S25FL("s25fl032p", 0x010215,  128, 65536U, SNOR_SECT_4K), },
	{ S25FL("s25fl032p", 0x010216,  256, 65536U, SNOR_SECT_4K), },
	{ S25FL("s25fl116k", 0x014215,   32, 65536U, SNOR_SECT_4K), },
	{ S25FL("s25fl132k", 0x014216,   64, 65536U, SNOR_SECT_4K), },
	{ S25FL("s25fl164k", 0x014217,  128, 65536U, SNOR_SECT_4K), },
	{ S25FL("s25fl128s", 0x012018,  256, 65536U, SNOR_SECT_4K), },
	{ S25FL("s25fl256s", 0x010219,  512, 65536U, SNOR_SECT_4K), },
	{ S25FL("s25fl512s", 0x010220, 1024, 262144U, 0), },

	{ 0 }	/* Sentinel */
};
