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
 *        Header
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "trace.h"

#include "extram/ddram.h"

#include "peripherals/matrix.h"
#include "extram/mpddrc.h"
#include "peripherals/pmc.h"

#include "mm/l1cache.h"

#include <assert.h>
#include <string.h>

/*------------------------------------------------------------------------------
 *        Macro
 *----------------------------------------------------------------------------*/

#ifndef MAX
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#endif

/* Convert nanoseconds to clock cycles for given master clock in MHz */
#define NS2CYCLES(ns, clk) ((((ns) * (clk)) + 999) / 1000)

#define TZQIO_CYCLES(clk) (NS2CYCLES(MPDDRC_TZQIO_DELAY, mck) + 1)

/* For compatibility with older DDR controller IP */
#ifndef MPDDRC_CR_NDQS_DISABLED
#define MPDDRC_CR_NDQS_DISABLED 0
#endif
#ifndef MPDDRC_CR_UNAL_SUPPORTED
#define MPDDRC_CR_UNAL_SUPPORTED 0
#endif

/*------------------------------------------------------------------------------
 *        Exported Functions
 *----------------------------------------------------------------------------*/

#ifdef CONFIG_HAVE_MPDDRC_DDR3

#ifdef CONFIG_HAVE_DDR3_MT41K128M16
static void _init_mt41k128m16(struct _mpddrc_desc* desc)
{
	uint32_t mck = pmc_get_master_clock() / 1000000;

	desc->type = MPDDRC_TYPE_DDR3;

	desc->mode = MPDDRC_MD_MD_DDR3_SDRAM
	           | MPDDRC_MD_DBW_DBW_32_BITS;

#ifdef CONFIG_HAVE_MPDDRC_DATA_PATH
	desc->data_path = MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_SHIFT_TWO_CYCLES;
#endif

	desc->control = MPDDRC_CR_NC_DDR_10_COL_BITS
	              | MPDDRC_CR_NR_14_ROW_BITS
	              | MPDDRC_CR_CAS_DDR_CAS5
	              | MPDDRC_CR_DIS_DLL
	              | MPDDRC_CR_NB_8_BANKS
	              | MPDDRC_CR_DIC_DS_DDR3_RZQ7
	              | MPDDRC_CR_DECOD_INTERLEAVED
	              | MPDDRC_CR_UNAL_SUPPORTED;

#ifdef CONFIG_HAVE_MPDDRC_IO_CALIBRATION
	desc->io_calibr = MPDDRC_IO_CALIBR_RDIV(4)
	                | MPDDRC_IO_CALIBR_TZQIO(TZQIO_CYCLES(mck));
#endif

	/* timings */

	memset(&desc->timings, 0, sizeof(desc->timings));
	desc->timings.tras  = NS2CYCLES(35, mck);          // 35ns
	desc->timings.trcd  = NS2CYCLES(14, mck);          // 13.75ns
	desc->timings.twr   = NS2CYCLES(15, mck);          // 15ns
	desc->timings.trc   = NS2CYCLES(49, mck);          // 48.75ns
	desc->timings.trp   = NS2CYCLES(14, mck);          // 13.75ns
	desc->timings.trrd  = MAX(NS2CYCLES(6, mck), 4);   // max(6ns, 4ck)
	desc->timings.twtr  = MAX(NS2CYCLES(8, mck), 4);   // max(7.5ns, 4ck)
	desc->timings.tmrd  = 4;                           // min 4ck
	desc->timings.trfc  = NS2CYCLES(160, mck);         // 160ns
	desc->timings.txsnr = NS2CYCLES(170, mck);         // tRFC+10ns
	desc->timings.txp   = MAX(NS2CYCLES(14, mck), 10); // max(24ns, 10ck)
	desc->timings.trtp  = MAX(NS2CYCLES(8, mck), 4);   // mac(7.5ns, 4ck)
	desc->timings.tfaw  = NS2CYCLES(40, mck);          // 40ns

	desc->refresh_window = 64;
	desc->refresh_cycles = 8192;
}
#endif /* CONFIG_HAVE_DDR3_MT41K128M16 */

#endif /* CONFIG_HAVE_MPDDRC_DDR3 */

#ifdef CONFIG_HAVE_MPDDRC_LPDDR3

#ifdef CONFIG_HAVE_LPDDR3_EDF8164A3MA
static void _init_edf8164a3ma(struct _mpddrc_desc* desc)
{
	uint32_t mck = pmc_get_master_clock() / 1000000;

	desc->type = MPDDRC_TYPE_LPDDR3;

	desc->mode = MPDDRC_MD_MD_LPDDR3_SDRAM
	           | MPDDRC_MD_DBW_DBW_32_BITS;

#ifdef CONFIG_HAVE_MPDDRC_DATA_PATH
	desc->data_path = MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_SHIFT_TWO_CYCLES;
#endif

	desc->control = MPDDRC_CR_NC_DDR_10_COL_BITS
	              | MPDDRC_CR_NR_14_ROW_BITS
	              | MPDDRC_CR_CAS_DDR_CAS3
	              | MPDDRC_CR_NB_8_BANKS
	              | MPDDRC_CR_DIC_DS_DDR3_RZQ6
	              | MPDDRC_CR_DECOD_SEQUENTIAL
	              | MPDDRC_CR_UNAL_SUPPORTED;

#ifdef CONFIG_HAVE_MPDDRC_IO_CALIBRATION
	desc->io_calibr = MPDDRC_IO_CALIBR_RDIV(4);
#endif

	/* timings */

	memset(&desc->timings, 0, sizeof(desc->timings));
	desc->timings.tras  = NS2CYCLES(42, mck);          // 42ns
	desc->timings.trcd  = MAX(NS2CYCLES(18, mck), 3);  // max(18ns, 3ck)
	desc->timings.twr   = MAX(NS2CYCLES(15, mck), 3);  // max(15ns, 3ck)
	desc->timings.trc   = NS2CYCLES(55, mck);          // 55ns
	desc->timings.trp   = MAX(NS2CYCLES(8, mck), 4);   // max(7.5ns, 4ck)
	desc->timings.trrd  = MAX(NS2CYCLES(10, mck), 2);  // max(10ns, 2ck)
	desc->timings.twtr  = MAX(NS2CYCLES(8, mck), 4);   // max(7.5ns, 4ck)
	desc->timings.tmrd  = MAX(NS2CYCLES(14, mck), 10); // max(14ns, 10ck)
	desc->timings.trfc  = NS2CYCLES(130, mck);         // 130ns
	desc->timings.txsnr = NS2CYCLES(140, mck);         // 140ns
	desc->timings.txp   = MAX(NS2CYCLES(8, mck), 2);   // max(7.5ns, 2ck)
	desc->timings.trtp  = MAX(NS2CYCLES(8, mck), 4);   // max(7.5ns, 4ck)
	desc->timings.tfaw  = MAX(NS2CYCLES(50, mck), 8);  // max(50ns, 8ck)

	desc->refresh_window = 64;
	desc->refresh_cycles = 8192;
}
#endif /* CONFIG_HAVE_LPDDR3_EDF8164A3MA */

#endif /* CONFIG_HAVE_MPDDRC_LPDDR3 */

#ifdef CONFIG_HAVE_MPDDRC_DDR2

#ifdef CONFIG_HAVE_DDR2_W971G16SG
static void _init_w971g16sg(struct _mpddrc_desc* desc)
{
	uint32_t mck = pmc_get_master_clock() / 1000000;

	desc->type = MPDDRC_TYPE_DDR2;

	desc->mode = MPDDRC_MD_MD_DDR2_SDRAM
	           | MPDDRC_MD_DBW_DBW_16_BITS;

#ifdef CONFIG_HAVE_MPDDRC_DATA_PATH
	desc->data_path = MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_SHIFT_ONE_CYCLE;
#endif

	desc->control = MPDDRC_CR_NR_13_ROW_BITS
	              | MPDDRC_CR_NC_DDR_10_COL_BITS
	              | MPDDRC_CR_CAS_DDR_CAS3
	              | MPDDRC_CR_DIC_DS_DDR2_WEAKSTRENGTH
	              | MPDDRC_CR_NB_8_BANKS
	              | MPDDRC_CR_DECOD_INTERLEAVED
	              | MPDDRC_CR_UNAL_SUPPORTED;

#ifdef CONFIG_HAVE_MPDDRC_IO_CALIBRATION
	desc->io_calibr = MPDDRC_IO_CALIBR_RDIV(4)
	                | MPDDRC_IO_CALIBR_TZQIO(TZQIO_CYCLES(mck));
#endif

	/* timings */

	memset(&desc->timings, 0, sizeof(desc->timings));
	desc->timings.tras   = NS2CYCLES(40, mck);  // 40ns
	desc->timings.trcd   = NS2CYCLES(13, mck);  // 12.5ns
	desc->timings.twr    = NS2CYCLES(15, mck);  // 15ns
	desc->timings.trc    = NS2CYCLES(53, mck);  // 52.5ns
	desc->timings.trp    = NS2CYCLES(13, mck);  // 12.5ns
	desc->timings.trrd   = NS2CYCLES(10, mck);  // 10ns
	desc->timings.twtr   = NS2CYCLES(8, mck);   // 7.5ns
	desc->timings.tmrd   = 2;                   // 2ck
	desc->timings.trfc   = NS2CYCLES(128, mck); // 127.5ns
	desc->timings.txsnr  = NS2CYCLES(138, mck); // tRFC+10ns
	desc->timings.txsrd  = 200;                 // 200ck
	desc->timings.txp    = 2;                   // 2ck
	desc->timings.txard  = 2;                   // 2ck
	desc->timings.txards = 8;                   // 8ck
	desc->timings.trpa   = desc->timings.trp + 1; // tRP+1ck
	desc->timings.trtp   = NS2CYCLES(8, mck);   // 7.5ns
	desc->timings.tfaw   = NS2CYCLES(45, mck);  // 45ns

	desc->refresh_window = 64;
	desc->refresh_cycles = 8192;
}
#endif /* CONFIG_HAVE_DDR2_W971G16SG */

#ifdef CONFIG_HAVE_DDR2_W972GG6KB
static void _init_w972gg6kb(struct _mpddrc_desc* desc)
{
	uint32_t mck = pmc_get_master_clock() / 1000000;

	desc->type = MPDDRC_TYPE_DDR2;

	desc->mode = MPDDRC_MD_MD_DDR2_SDRAM
	           | MPDDRC_MD_DBW_DBW_32_BITS;

#ifdef CONFIG_HAVE_MPDDRC_DATA_PATH
	desc->data_path = MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_SHIFT_ONE_CYCLE;
#endif

	desc->control = MPDDRC_CR_NR_14_ROW_BITS
	              | MPDDRC_CR_NC_DDR_10_COL_BITS
	              | MPDDRC_CR_CAS_DDR_CAS3
	              | MPDDRC_CR_NB_8_BANKS
	              | MPDDRC_CR_UNAL_SUPPORTED;

#ifdef CONFIG_HAVE_MPDDRC_IO_CALIBRATION
	desc->io_calibr = MPDDRC_IO_CALIBR_RDIV(4)
	                | MPDDRC_IO_CALIBR_TZQIO(TZQIO_CYCLES(mck))
	                | MPDDRC_IO_CALIBR_EN_CALIB_ENABLE_CALIBRATION;
#endif

	/* timings */

	memset(&desc->timings, 0, sizeof(desc->timings));
	desc->timings.tras   = NS2CYCLES(45, mck);  // 45ns
	desc->timings.trcd   = NS2CYCLES(13, mck);  // 13ns
	desc->timings.twr    = NS2CYCLES(15, mck);  // 15ns
	desc->timings.trc    = NS2CYCLES(58, mck);  // 58ns
	desc->timings.trp    = NS2CYCLES(13, mck);  // 13ns
	desc->timings.trrd   = NS2CYCLES(10, mck);  // 10ns
	desc->timings.twtr   = NS2CYCLES(8, mck);   // 8ns
	desc->timings.tmrd   = 2;                   // 2ck
	desc->timings.trfc   = NS2CYCLES(195, mck); // 195ns
	desc->timings.txsnr  = NS2CYCLES(205, mck); // tRFC+10ns
	desc->timings.txsrd  = 200;                 // 200ck
	desc->timings.txp    = 2;                   // 2ck
	desc->timings.txard  = 2;                   // 2ck
	desc->timings.txards = 8;                   // 8ck
	desc->timings.trpa   = NS2CYCLES(21, mck);  // 21ns
	desc->timings.trtp   = NS2CYCLES(8, mck);   // 8ns
	desc->timings.tfaw   = NS2CYCLES(45, mck);  // 45ns

	desc->refresh_window = 64;
	desc->refresh_cycles = 8192;
}
#endif /* CONFIG_HAVE_DDR2_W972GG6KB */

#ifdef CONFIG_HAVE_DDR2_MT47H128M8
static void _init_mt47h128m8(struct _mpddrc_desc* desc)
{
	uint32_t mck = pmc_get_master_clock() / 1000000;

	desc->type = MPDDRC_TYPE_DDR2;

	desc->mode = MPDDRC_MD_MD_DDR2_SDRAM
	           | MPDDRC_MD_DBW_DBW_32_BITS;

#ifdef CONFIG_HAVE_MPDDRC_DATA_PATH
	desc->data_path = MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_SHIFT_ONE_CYCLE;
#endif

	desc->control = MPDDRC_CR_NR_14_ROW_BITS
	              | MPDDRC_CR_NC_DDR_10_COL_BITS
	              | MPDDRC_CR_CAS_DDR_CAS3
	              | MPDDRC_CR_NB_8_BANKS
	              | MPDDRC_CR_NDQS_DISABLED
	              | MPDDRC_CR_UNAL_SUPPORTED;

#ifdef CONFIG_HAVE_MPDDRC_IO_CALIBRATION
	desc->io_calibr = MPDDRC_IO_CALIBR_RDIV(4)
	                | MPDDRC_IO_CALIBR_TZQIO(TZQIO_CYCLES(mck))
	                | MPDDRC_IO_CALIBR_EN_CALIB_ENABLE_CALIBRATION;
#endif

	/* timings */

	memset(&desc->timings, 0, sizeof(desc->timings));
	desc->timings.tras   = NS2CYCLES(40, mck);  // 40ns
	desc->timings.trcd   = NS2CYCLES(13, mck);  // 12.5ns
	desc->timings.twr    = NS2CYCLES(15, mck);  // 15ns
	desc->timings.trc    = NS2CYCLES(55, mck);  // 55ns
	desc->timings.trp    = NS2CYCLES(13, mck);  // 12.5ns
	desc->timings.trrd   = NS2CYCLES(8, mck);   // 7.5ns
	desc->timings.twtr   = NS2CYCLES(10, mck);  // 10ns
	desc->timings.tmrd   = 2;                   // 2ck
	desc->timings.trfc   = NS2CYCLES(128, mck); // 127.5ns
	desc->timings.txsnr  = NS2CYCLES(138, mck); // tRFC+10ns
	desc->timings.txsrd  = 200;                 // 200ck
	desc->timings.txp    = 2;                   // 2ck
	desc->timings.txard  = 8;                   // 8ck
	desc->timings.txards = 2;                   // 2ck
	desc->timings.trpa   = NS2CYCLES(15, mck);  // 15ns
	desc->timings.trtp   = NS2CYCLES(8, mck);   // 7.5ns
	desc->timings.tfaw   = NS2CYCLES(35, mck);  // 35ns

	desc->refresh_window = 64;
	desc->refresh_cycles = 8192;
}
#endif /* CONFIG_HAVE_DDR2_MT47H128M8 */

#ifdef CONFIG_HAVE_DDR2_MT47H64M16
static void _init_mt47h64m16(struct _mpddrc_desc* desc)
{
	uint32_t mck = pmc_get_master_clock() / 1000000;

	desc->type = MPDDRC_TYPE_DDR2;

	desc->mode = MPDDRC_MD_MD_DDR2_SDRAM
	           | MPDDRC_MD_DBW_DBW_16_BITS;

#ifdef CONFIG_HAVE_MPDDRC_DATA_PATH
	desc->data_path = MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_SHIFT_ONE_CYCLE;
#endif

	desc->control = MPDDRC_CR_NR_13_ROW_BITS
	              | MPDDRC_CR_NC_DDR_10_COL_BITS
	              | MPDDRC_CR_CAS_DDR_CAS3
	              | MPDDRC_CR_NB_8_BANKS
	              | MPDDRC_CR_DECOD_INTERLEAVED
	              | MPDDRC_CR_NDQS_DISABLED
	              | MPDDRC_CR_UNAL_SUPPORTED;

#ifdef CONFIG_HAVE_MPDDRC_IO_CALIBRATION
	desc->io_calibr = MPDDRC_IO_CALIBR_RDIV(4)
	                | MPDDRC_IO_CALIBR_TZQIO(TZQIO_CYCLES(mck))
	                | MPDDRC_IO_CALIBR_EN_CALIB_ENABLE_CALIBRATION;
#endif

	/* timings */

	memset(&desc->timings, 0, sizeof(desc->timings));
	desc->timings.tras   = NS2CYCLES(45, mck);  // 45ns
	desc->timings.trcd   = NS2CYCLES(15, mck);  // 15ns
	desc->timings.twr    = NS2CYCLES(15, mck);  // 15ns
	desc->timings.trc    = NS2CYCLES(55, mck);  // 55ns
	desc->timings.trp    = NS2CYCLES(15, mck);  // 15ns
	desc->timings.trrd   = NS2CYCLES(13, mck);  // 12.5ns
	desc->timings.twtr   = NS2CYCLES(10, mck);  // 10ns
	desc->timings.tmrd   = NS2CYCLES(8, mck);   // 8ns
	desc->timings.trfc   = NS2CYCLES(198, mck); // 198ns
	desc->timings.txsnr  = NS2CYCLES(208, mck); // tRFC+10ns
	desc->timings.txsrd  = 200;                 // 200ck
	desc->timings.txp    = 2;                   // 2ck
	desc->timings.txard  = 8;                   // 8ck
	desc->timings.txards = 2;                   // 2ck
	desc->timings.trpa   = NS2CYCLES(15, mck);  // 15ns
	desc->timings.trtp   = NS2CYCLES(8, mck);   // 8ns
	desc->timings.tfaw   = NS2CYCLES(45, mck);  // 45ns

	desc->refresh_window = 64;
	desc->refresh_cycles = 8192;
}
#endif /* CONFIG_HAVE_DDR2_MT47H64M16 */

#ifdef CONFIG_HAVE_DDR2_MT47H128M16
static void _init_mt47h128m16(struct _mpddrc_desc* desc)
{
	uint32_t mck = pmc_get_master_clock() / 1000000;

	desc->type = MPDDRC_TYPE_DDR2;

	desc->mode = MPDDRC_MD_MD_DDR2_SDRAM
	           | MPDDRC_MD_DBW_DBW_32_BITS;

#ifdef CONFIG_HAVE_MPDDRC_DATA_PATH
	desc->data_path = MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_SHIFT_ONE_CYCLE;
#endif

	desc->control = MPDDRC_CR_NR_14_ROW_BITS
	              | MPDDRC_CR_NC_DDR_10_COL_BITS
	              | MPDDRC_CR_CAS_DDR_CAS3
	              | MPDDRC_CR_NB_8_BANKS
	              | MPDDRC_CR_NDQS_DISABLED
	              | MPDDRC_CR_UNAL_SUPPORTED;

#ifdef CONFIG_HAVE_MPDDRC_IO_CALIBRATION
	desc->io_calibr = MPDDRC_IO_CALIBR_RDIV(4)
	                | MPDDRC_IO_CALIBR_TZQIO(TZQIO_CYCLES(mck))
	                | MPDDRC_IO_CALIBR_EN_CALIB_ENABLE_CALIBRATION;
#endif

	/* timings */

	memset(&desc->timings, 0, sizeof(desc->timings));
	desc->timings.tras   = NS2CYCLES(45, mck);  // 45ns
	desc->timings.trcd   = NS2CYCLES(15, mck);  // 15ns
	desc->timings.twr    = NS2CYCLES(15, mck);  // 15ns
	desc->timings.trc    = NS2CYCLES(55, mck);  // 55ns
	desc->timings.trp    = NS2CYCLES(15, mck);  // 15ns
	desc->timings.trrd   = NS2CYCLES(13, mck);  // 12.5ns
	desc->timings.twtr   = NS2CYCLES(10, mck);  // 10ns
	desc->timings.tmrd   = NS2CYCLES(8, mck);   // 8ns
	desc->timings.trfc   = NS2CYCLES(186, mck); // 186ns
	desc->timings.txsnr  = NS2CYCLES(208, mck); // tRFC+10s
	desc->timings.txsrd  = 202;                 // 202ck
	desc->timings.txp    = 3;                   // 3ck
	desc->timings.txard  = 3;                   // 3ck
	desc->timings.txards = 10;                  // 10ck
	desc->timings.trpa   = NS2CYCLES(15, mck);  // 15ns
	desc->timings.trtp   = NS2CYCLES(8, mck);   // 8ns
	desc->timings.tfaw   = NS2CYCLES(45, mck);  // 45ns

	desc->refresh_window = 64;
	desc->refresh_cycles = 8192;
}
#endif /* CONFIG_HAVE_DDR2_MT47H128M16 */

#endif /* CONFIG_HAVE_MPDDRC_DDR2 */

#ifdef CONFIG_HAVE_MPDDRC_LPDDR2

#ifdef CONFIG_HAVE_LPDDR2_MT42L128M16
static void _init_mt42l128m16(struct _mpddrc_desc* desc)
{
	uint32_t mck = pmc_get_master_clock() / 1000000;

	desc->type = MPDDRC_TYPE_LPDDR2;

	desc->mode = MPDDRC_MD_MD_LPDDR2_SDRAM
	           | MPDDRC_MD_DBW_DBW_32_BITS;

#ifdef CONFIG_HAVE_MPDDRC_DATA_PATH
	desc->data_path = MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_SHIFT_ONE_CYCLE;
#endif

	desc->control = MPDDRC_CR_NR_14_ROW_BITS
	              | MPDDRC_CR_NC_DDR_10_COL_BITS
	              | MPDDRC_CR_CAS_DDR_CAS3
	              | MPDDRC_CR_NB_8_BANKS
	              | MPDDRC_CR_UNAL_SUPPORTED;

#ifdef CONFIG_HAVE_MPDDRC_IO_CALIBRATION
	desc->io_calibr = MPDDRC_IO_CALIBR_RDIV(4);
#endif

	/* timings */

	memset(&desc->timings, 0, sizeof(desc->timings));
	desc->timings.tras   = NS2CYCLES(40, mck);  // 40ns
	desc->timings.trcd   = NS2CYCLES(15, mck);  // 15ns
	desc->timings.twr    = NS2CYCLES(15, mck);  // 15ns
	desc->timings.trc    = NS2CYCLES(60, mck);  // 60ns
	desc->timings.trp    = NS2CYCLES(15, mck);  // 15ns
	desc->timings.trrd   = NS2CYCLES(11, mck);  // 11ns
	desc->timings.twtr   = NS2CYCLES(8, mck);   // 7.5ns
	desc->timings.tmrd   = 2;                   // 2ck
	desc->timings.trfc   = NS2CYCLES(130, mck); // 130ns
	desc->timings.txsnr  = NS2CYCLES(140, mck); // 140ns
	desc->timings.txp    = 2;                   // 2ck
	desc->timings.trtp   = NS2CYCLES(8, mck);   // 8ns
	desc->timings.tfaw   = NS2CYCLES(50, mck);  // 50ns

	desc->refresh_window = 32;
	desc->refresh_cycles = 8192;
}
#endif /* CONFIG_HAVE_LPDDR2_MT42L128M16 */

#endif /* CONFIG_HAVE_MPDDRC_LPDDR2 */

#ifdef CONFIG_HAVE_MPDDRC_SDRAM

#ifdef CONFIG_HAVE_SDRAM_AS4C16M16SA
static void _init_as4c16m16sa(struct _mpddrc_desc* desc)
{
	uint32_t mck = pmc_get_master_clock() / 1000000;

	desc->type = MPDDRC_TYPE_SDRAM;

	desc->mode = MPDDRC_MD_MD_SDRAM;

	desc->control = MPDDRC_CR_NC_SDRAM_9_COL_BITS
	              | MPDDRC_CR_NR_13_ROW_BITS
	              | MPDDRC_CR_CAS_SDRAM_CAS3
	              | MPDDRC_CR_NB_BANK4
	              | MPDDRC_CR_DBW;

	/* timings */

	memset(&desc->timings, 0, sizeof(desc->timings));
	desc->timings.twr   = NS2CYCLES(12, mck) + 2; // tRP+2ck (tDAL)
	desc->timings.trc   = NS2CYCLES(65, mck);     // 65ns
	desc->timings.trfc  = desc->timings.trc;      // same as tRC
	desc->timings.trp   = NS2CYCLES(20, mck);     // 20ns
	desc->timings.trcd  = NS2CYCLES(20, mck);     // 20ns
	desc->timings.tras  = NS2CYCLES(45, mck);     // 45ns
	desc->timings.txsrd = NS2CYCLES(3, mck) + 1;  // 3ns+1ck (tCKA)
	desc->timings.txsnr = desc->timings.txsrd;    // same as tXSRD

	desc->refresh_window = 64;
	desc->refresh_cycles = 8192;
}
#endif /* CONFIG_HAVE_SDRAM_AS4C416M16SA */

#ifdef CONFIG_HAVE_SDRAM_IS42S16100E
static void _init_is42s16100e(struct _mpddrc_desc* desc)
{
	uint32_t mck = pmc_get_master_clock() / 1000000;

	desc->type = MPDDRC_TYPE_SDRAM;

	desc->mode = MPDDRC_MD_MD_SDRAM;

	desc->control = MPDDRC_CR_NC_SDRAM_8_COL_BITS
	              | MPDDRC_CR_NR_11_ROW_BITS
	              | MPDDRC_CR_CAS_SDRAM_CAS3
	              | MPDDRC_CR_NB_BANK2
	              | MPDDRC_CR_DBW;

	/* timings */

	memset(&desc->timings, 0, sizeof(desc->timings));
	desc->timings.twr   = NS2CYCLES(20, mck) + 2; // tRP+2ck (tDAL)
	desc->timings.trc   = NS2CYCLES(63, mck);     // 63ns
	desc->timings.trfc  = desc->timings.trc;      // same as tRC
	desc->timings.trp   = NS2CYCLES(20, mck);     // 20ns
	desc->timings.trcd  = NS2CYCLES(16, mck);     // 16ns
	desc->timings.tras  = NS2CYCLES(42, mck);     // 42ns
	desc->timings.txsrd = NS2CYCLES(3, mck) + 1;  // 3ns+1ck (tCKA)
	desc->timings.txsnr = desc->timings.txsrd;    // same as tXSRD

	desc->refresh_window = 32;
	desc->refresh_cycles = 2048;
}
#endif /* CONFIG_HAVE_SDRAM_IS42S16100E */


#ifdef CONFIG_HAVE_SDRAM_W981216BH
static void _init_w981216bh(struct _mpddrc_desc* desc)
{
	uint32_t mck = pmc_get_master_clock() / 1000000;

	desc->type = MPDDRC_TYPE_SDRAM;

	desc->mode = MPDDRC_MD_MD_SDRAM;

	desc->control = MPDDRC_CR_NC_SDRAM_9_COL_BITS
	              | MPDDRC_CR_NR_12_ROW_BITS
	              | MPDDRC_CR_CAS_SDRAM_CAS3
	              | MPDDRC_CR_NB_BANK4
	              | MPDDRC_CR_DBW;

	/* timings */

	memset(&desc->timings, 0, sizeof(desc->timings));
	desc->timings.twr   = NS2CYCLES(10, mck) + 2; // tRP+2ck (tDAL)
	desc->timings.trc   = NS2CYCLES(65, mck);     // 65ns
	desc->timings.trfc  = desc->timings.trc;      // same as tRC
	desc->timings.trp   = NS2CYCLES(20, mck);     // 20ns
	desc->timings.trcd  = NS2CYCLES(20, mck);     // 20ns
	desc->timings.tras  = NS2CYCLES(45, mck);     // 45ns
	desc->timings.txsrd = NS2CYCLES(3, mck) + 1;  // 3ns+1ck (tCKA)
	desc->timings.txsnr = desc->timings.txsrd;    // same as tXSRD

	desc->refresh_window = 64;
	desc->refresh_cycles = 4096;
}
#endif /* CONFIG_HAVE_SDRAM_W981216BH */


#ifdef CONFIG_HAVE_SDRAM_MT48LC16M16
static void _init_mt48lc16m16(struct _mpddrc_desc* desc)
{
	uint32_t mck = pmc_get_master_clock() / 1000000;

	desc->type = MPDDRC_TYPE_SDRAM;

	desc->mode = MPDDRC_MD_MD_SDR_SDRAM
	           | MPDDRC_MD_DBW_DBW_16_BITS;

	desc->control = MPDDRC_CR_NC_SDR_9_COL_BITS
	              | MPDDRC_CR_NR_13_ROW_BITS
	              | MPDDRC_CR_CAS_SDR_CAS3
	              | MPDDRC_CR_NB_4_BANKS
	              | MPDDRC_CR_DECOD_INTERLEAVED;

	/* timings */

	memset(&desc->timings, 0, sizeof(desc->timings));
	desc->timings.twr   = NS2CYCLES(15, mck) + 2; // tRP+2ck (tDAL)
	desc->timings.trc   = NS2CYCLES(66, mck);     // 66ns
	desc->timings.trfc  = desc->timings.trc;      // same as tRC
	desc->timings.trp   = NS2CYCLES(20, mck);     // 20ns
	desc->timings.trcd  = NS2CYCLES(20, mck);     // 20ns
	desc->timings.tras  = NS2CYCLES(44, mck);     // 44ns
	desc->timings.txsrd = NS2CYCLES(75, mck);     // 75ns
	desc->timings.txsnr = desc->timings.txsrd;    // same as tXSRD
	desc->timings.trrd  = NS2CYCLES(15, mck);     // 15ns
	desc->timings.tmrd =  2;                      // 2 cycles

	desc->refresh_window = 64;
	desc->refresh_cycles = 8192;
}
#endif /* CONFIG_HAVE_SDRAM_MT48LC16M16 */

#endif /* CONFIG_HAVE_MPDDRC_SDRAM */

void ddram_init_descriptor(struct _mpddrc_desc* desc,
			   enum _ddram_devices device)
{
	switch(device) {
#ifdef CONFIG_HAVE_MPDDRC_SDRAM
  #ifdef CONFIG_HAVE_SDRAM_AS4C16M16SA
	case AS4C16M16SA:
		_init_as4c16m16sa(desc);
		break;
  #endif
  #ifdef CONFIG_HAVE_SDRAM_IS42S16100E
	case IS42S16100E:
		_init_is42s16100e(desc);
		break;
  #endif
  #ifdef CONFIG_HAVE_SDRAM_W981216BH
	case W981216BH:
		_init_w981216bh(desc);
		break;
  #endif
  #ifdef CONFIG_HAVE_SDRAM_MT48LC16M16
	case MT48LC16M16:
		_init_mt48lc16m16(desc);
		break;
  #endif
#endif
#ifdef CONFIG_HAVE_MPDDRC_DDR2
  #ifdef CONFIG_HAVE_DDR2_MT47H128M8
	case MT47H128M8:
		_init_mt47h128m8(desc);
		break;
  #endif
  #ifdef CONFIG_HAVE_DDR2_MT47H64M16
	case MT47H64M16:
		_init_mt47h64m16(desc);
		break;
  #endif
  #ifdef CONFIG_HAVE_DDR2_MT47H128M16
	case MT47H128M16:
		_init_mt47h128m16(desc);
		break;
  #endif
  #ifdef CONFIG_HAVE_DDR2_W971G16SG
	case W971G16SG:
		_init_w971g16sg(desc);
		break;
  #endif
  #ifdef CONFIG_HAVE_DDR2_W972GG6KB
	case W972GG6KB:
		_init_w972gg6kb(desc);
		break;
  #endif
#endif
#ifdef CONFIG_HAVE_MPDDRC_LPDDR2
  #ifdef CONFIG_HAVE_LPDDR2_MT42L128M16
	case MT42L128M16:
		_init_mt42l128m16(desc);
		break;
  #endif
#endif
#ifdef CONFIG_HAVE_MPDDRC_DDR3
  #ifdef CONFIG_HAVE_DDR3_MT41K128M16
	case MT41K128M16:
		_init_mt41k128m16(desc);
		break;
  #endif
#endif
#ifdef CONFIG_HAVE_MPDDRC_LPDDR3
  #ifdef CONFIG_HAVE_LPDDR3_EDF8164A3MA
	case EDF8164A3MA:
		_init_edf8164a3ma(desc);
		break;
  #endif
#endif
	default:
		trace_fatal("Unsupported DDRAM type\r\n");
		break;
	}
}

void ddram_configure(struct _mpddrc_desc* desc)
{
	assert(!dcache_is_enabled());
	mpddrc_configure(desc);
}
