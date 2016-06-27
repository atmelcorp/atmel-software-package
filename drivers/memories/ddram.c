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

#include "memories/ddram.h"

#include "peripherals/matrix.h"
#include "peripherals/mpddrc.h"
#include "peripherals/pmc.h"

/*------------------------------------------------------------------------------
 *        Macro
 *----------------------------------------------------------------------------*/

#ifndef MAX
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#endif

/* Convert nanoseconds to clock cycles for given master clock in MHz */
#define NS2CYCLES(ns, clk) ((((ns) * (clk)) + 999) / 1000)

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

	desc->mode = MPDDRC_MD_MD_DDR3_SDRAM;

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
	                | MPDDRC_IO_CALIBR_TZQIO(100);
#endif

	/* timings */

	desc->tpr0 = MPDDRC_TPR0_TRAS(NS2CYCLES(35, mck)) // 35ns
	           | MPDDRC_TPR0_TRCD(NS2CYCLES(14, mck)) // 13.75ns
	           | MPDDRC_TPR0_TWR(NS2CYCLES(15, mck))  // 15ns
	           | MPDDRC_TPR0_TRC(NS2CYCLES(49, mck))  // 48.75ns
	           | MPDDRC_TPR0_TRP(NS2CYCLES(14, mck))  // 13.75ns
	           | MPDDRC_TPR0_TRRD(4)                  // greater of 4CK or 6ns
	           | MPDDRC_TPR0_TWTR(4)                  // greater of 4CK or 7.5ns
	           | MPDDRC_TPR0_TMRD(4);                 // min = 4CK

	desc->tpr1 = MPDDRC_TPR1_TRFC(NS2CYCLES(160, mck))  // 160ns
	           | MPDDRC_TPR1_TXSNR(NS2CYCLES(170, mck)) // tRFC+10ns
	           | MPDDRC_TPR1_TXSRD(0)
	           | MPDDRC_TPR1_TXP(10);                   // greater of 10CK or or 24ns

	desc->tpr2 = MPDDRC_TPR2_TXARD(0)
	           | MPDDRC_TPR2_TXARDS(0)
	           | MPDDRC_TPR2_TRPA(0)
	           | MPDDRC_TPR2_TRTP(4)                   // greater of 4CK or 7.5ns
	           | MPDDRC_TPR2_TFAW(NS2CYCLES(40, mck)); // 40ns

	desc->bank = 8192;
}
#endif /* CONFIG_HAVE_DDR3_MT41K128M16 */

#endif /* CONFIG_HAVE_MPDDRC_DDR3 */

#ifdef CONFIG_HAVE_MPDDRC_LPDDR3

#ifdef CONFIG_HAVE_LPDDR3_EDF8164A3MA
static void _init_edf8164a3ma(struct _mpddrc_desc* desc)
{
	uint32_t mck = pmc_get_master_clock() / 1000000;

	desc->type = MPDDRC_TYPE_LPDDR3;

	desc->mode = MPDDRC_MD_MD_LPDDR3_SDRAM;

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

	desc->tpr0 = MPDDRC_TPR0_TRAS(NS2CYCLES(42, mck))           // 42ns
	           | MPDDRC_TPR0_TRCD(MAX(NS2CYCLES(18, mck), 3))   // max(18ns | 3ck)
	           | MPDDRC_TPR0_TWR(MAX(NS2CYCLES(15, mck), 3))    // max(15ns | 3ck)
	           | MPDDRC_TPR0_TRC(NS2CYCLES(55, mck))            // 55ns
	           | MPDDRC_TPR0_TRP(MAX(NS2CYCLES(8, mck), 4))     // max(7.5ns, 4ck)
	           | MPDDRC_TPR0_TRRD(MAX(NS2CYCLES(10, mck), 2))   // max(10ns, 2ck)
	           | MPDDRC_TPR0_TWTR(MAX(NS2CYCLES(8, mck), 4))    // max(7.5ns, 4ck)
	           | MPDDRC_TPR0_TMRD(MAX(NS2CYCLES(14, mck), 10)); // max(14ns, 10ck)

	desc->tpr1 = MPDDRC_TPR1_TRFC(NS2CYCLES(130, mck))       // 130ns
	           | MPDDRC_TPR1_TXSNR(NS2CYCLES(140, mck))      // 140ns
	           | MPDDRC_TPR1_TXSRD(NS2CYCLES(140, mck))      // max(tRFCab + 10ns, 2ck)
	           | MPDDRC_TPR1_TXP(MAX(NS2CYCLES(8, mck), 2)); // max(7.5ns, 2ck)

	desc->tpr2 = MPDDRC_TPR2_TXARD(0)
	           | MPDDRC_TPR2_TXARDS(0)
	           | MPDDRC_TPR2_TRPA(0)
	           | MPDDRC_TPR2_TRTP(MAX(NS2CYCLES(8, mck), 4))   // max(7.5ns, 4ck)
	           | MPDDRC_TPR2_TFAW(MAX(NS2CYCLES(50, mck), 8)); // max(50ns, 8ck)

	desc->bank = 8192;
}
#endif /* CONFIG_HAVE_LPDDR3_EDF8164A3MA */

#endif /* CONFIG_HAVE_MPDDRC_LPDDR3 */

#ifdef CONFIG_HAVE_MPDDRC_DDR2

#ifdef CONFIG_HAVE_DDR2_MT47H128M8CF
static void _init_mt47h128m8cf(struct _mpddrc_desc* desc)
{
	uint32_t mck = pmc_get_master_clock() / 1000000;

	desc->type = MPDDRC_TYPE_DDR2;

	/* DBW = 0 (32 bits bus wide);
	 * Memory Device = 6 = DDR2-SDRAM = 0x00000006 */
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
	desc->io_calibr = MPDDRC_IO_CALIBR_CALCODEP(7)
	                | MPDDRC_IO_CALIBR_CALCODEN(8)
	                | MPDDRC_IO_CALIBR_RDIV(4)
	                | MPDDRC_IO_CALIBR_TZQIO(5)
	                | MPDDRC_IO_CALIBR_EN_CALIB_ENABLE_CALIBRATION;
#endif

	/* timings */

	desc->tpr0 = MPDDRC_TPR0_TRAS(NS2CYCLES(40, mck)) // 40ns
	           | MPDDRC_TPR0_TRCD(NS2CYCLES(13, mck)) // 12.5ns
	           | MPDDRC_TPR0_TWR(NS2CYCLES(15, mck))  // 15ns
	           | MPDDRC_TPR0_TRC(NS2CYCLES(55, mck))  // 55ns
	           | MPDDRC_TPR0_TRP(NS2CYCLES(13, mck))  // 12.5ns
	           | MPDDRC_TPR0_TRRD(NS2CYCLES(8, mck))  // 7.5ns
	           | MPDDRC_TPR0_TWTR(NS2CYCLES(10, mck)) // 10ns
	           | MPDDRC_TPR0_TMRD(2);                 // 2 clock cycles

	desc->tpr1 = MPDDRC_TPR1_TRFC(NS2CYCLES(128, mck))  // 127.5ns
	           | MPDDRC_TPR1_TXSNR(NS2CYCLES(138, mck)) // (tRFC)+10 = 128.5ns
	           | MPDDRC_TPR1_TXSRD(200)                 // 200ck
	           | MPDDRC_TPR1_TXP(2);                    // 2ck

	desc->tpr2 = MPDDRC_TPR2_TXARD(8)                  // 8ck
	           | MPDDRC_TPR2_TXARDS(2)                 // 2ck
	           | MPDDRC_TPR2_TRPA(NS2CYCLES(15, mck))  // 15ns
	           | MPDDRC_TPR2_TRTP(NS2CYCLES(8, mck))   // 7.5ns
	           | MPDDRC_TPR2_TFAW(NS2CYCLES(35, mck)); // 35ns

	desc->bank = 8192;
}
#endif /* CONFIG_HAVE_DDR2_MT47H128M8CF */

#ifdef CONFIG_HAVE_DDR2_MT47H64M16
static void _init_mt47h64m16(struct _mpddrc_desc* desc)
{
	uint32_t mck = pmc_get_master_clock() / 1000000;

	desc->type = MPDDRC_TYPE_DDR2;

	/* DBW = 0 (32 bits bus wide);
	 * Memory Device = 6 = DDR2-SDRAM = 0x00000006 */
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
	desc->io_calibr = MPDDRC_IO_CALIBR_CALCODEP(7)
	                | MPDDRC_IO_CALIBR_CALCODEN(8)
	                | MPDDRC_IO_CALIBR_RDIV(4)
	                | MPDDRC_IO_CALIBR_TZQIO(5)
	                | MPDDRC_IO_CALIBR_EN_CALIB_ENABLE_CALIBRATION;
#endif

	/* timings */
	desc->tpr0 = MPDDRC_TPR0_TRAS(NS2CYCLES(45, mck)) // 45ns
	           | MPDDRC_TPR0_TRCD(NS2CYCLES(15, mck)) // 15ns
	           | MPDDRC_TPR0_TWR(NS2CYCLES(15, mck))  // 15ns
	           | MPDDRC_TPR0_TRC(NS2CYCLES(55, mck))  // 55ns
	           | MPDDRC_TPR0_TRP(NS2CYCLES(15, mck))  // 15ns
	           | MPDDRC_TPR0_TRRD(NS2CYCLES(13, mck)) // 12.5ns
	           | MPDDRC_TPR0_TWTR(NS2CYCLES(10, mck)) // 10ns
	           | MPDDRC_TPR0_TMRD(NS2CYCLES(8, mck)); // 8ns

	desc->tpr1 = MPDDRC_TPR1_TRFC(NS2CYCLES(198, mck))  // 198ns
	           | MPDDRC_TPR1_TXSNR(NS2CYCLES(208, mck)) // (tRFC)+10 = 208ns
	           | MPDDRC_TPR1_TXSRD(200)                 // 200ck
	           | MPDDRC_TPR1_TXP(2);                    // 2ck

	desc->tpr2 = MPDDRC_TPR2_TXARD(8)                  // 8ck
	           | MPDDRC_TPR2_TXARDS(2)                 // 2ck
	           | MPDDRC_TPR2_TRPA(NS2CYCLES(15, mck))  // 15ns
	           | MPDDRC_TPR2_TRTP(NS2CYCLES(8, mck))   // 8ns
	           | MPDDRC_TPR2_TFAW(NS2CYCLES(45, mck)); // 45ns

	desc->bank = 8192;
}
#endif /* CONFIG_HAVE_DDR2_MT47H64M16 */

#ifdef CONFIG_HAVE_DDR2_MT47H128M16
static void _init_mt47h128m16(struct _mpddrc_desc* desc)
{
	uint32_t mck = pmc_get_master_clock() / 1000000;

	desc->type = MPDDRC_TYPE_DDR2;

	/* DBW = 0 (32 bits bus wide);
	 * Memory Device = 6 = DDR2-SDRAM = 0x00000006 */
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
	desc->io_calibr = MPDDRC_IO_CALIBR_CALCODEP(7)
	                | MPDDRC_IO_CALIBR_CALCODEN(8)
	                | MPDDRC_IO_CALIBR_RDIV(4)
	                | MPDDRC_IO_CALIBR_TZQIO(5)
	                | MPDDRC_IO_CALIBR_EN_CALIB_ENABLE_CALIBRATION;
#endif

	/* timings */

	desc->tpr0 = MPDDRC_TPR0_TRAS(NS2CYCLES(45, mck)) // 45ns
	           | MPDDRC_TPR0_TRCD(NS2CYCLES(15, mck)) // 15ns
	           | MPDDRC_TPR0_TWR(NS2CYCLES(15, mck))  // 15ns
	           | MPDDRC_TPR0_TRC(NS2CYCLES(55, mck))  // 55ns
	           | MPDDRC_TPR0_TRP(NS2CYCLES(15, mck))  // 15ns
	           | MPDDRC_TPR0_TRRD(NS2CYCLES(13, mck)) // 12.5ns
	           | MPDDRC_TPR0_TWTR(NS2CYCLES(10, mck)) // 10ns
	           | MPDDRC_TPR0_TMRD(NS2CYCLES(8, mck)); // 8ns

	desc->tpr1 = MPDDRC_TPR1_TRFC(NS2CYCLES(198, mck))  // 198ns
	           | MPDDRC_TPR1_TXSNR(NS2CYCLES(208, mck)) // (tRFC)+10 = 208ns
	           | MPDDRC_TPR1_TXSRD(200)                 // 200ck
	           | MPDDRC_TPR1_TXP(2);                    // 2ck

	desc->tpr2 = MPDDRC_TPR2_TXARD(8)                  // 8ck
	           | MPDDRC_TPR2_TXARDS(2)                 // 2ck
	           | MPDDRC_TPR2_TRPA(NS2CYCLES(15, mck))  // 15ns
	           | MPDDRC_TPR2_TRTP(NS2CYCLES(8, mck))   // 8ns
	           | MPDDRC_TPR2_TFAW(NS2CYCLES(45, mck)); // 45ns

	desc->bank = 8192;
}
#endif /* CONFIG_HAVE_DDR2_MT47H128M16 */

#endif /* CONFIG_HAVE_MPDDRC_DDR2 */

#ifdef CONFIG_HAVE_MPDDRC_LPDDR2

#ifdef CONFIG_HAVE_LPDDR2_MT42L128M16
static void _init_mt42l128m16(struct _mpddrc_desc* desc)
{
	uint32_t mck = pmc_get_master_clock() / 1000000;

	desc->type = MPDDRC_TYPE_LPDDR2;

	/* DBW = 0 (32 bits bus wide);
	 * Memory Device = 7 = LPDDR2-SDRAM = 0x00000007 */
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

	desc->tpr0 = MPDDRC_TPR0_TRAS(NS2CYCLES(40, mck)) // 40ns
	           | MPDDRC_TPR0_TRCD(NS2CYCLES(15, mck)) // 15ns
	           | MPDDRC_TPR0_TWR(NS2CYCLES(15, mck))  // 15ns
	           | MPDDRC_TPR0_TRC(NS2CYCLES(60, mck))  // 60ns
	           | MPDDRC_TPR0_TRP(NS2CYCLES(15, mck))  // 15ns
	           | MPDDRC_TPR0_TRRD(NS2CYCLES(11, mck)) // 11ns
	           | MPDDRC_TPR0_TWTR(NS2CYCLES(8, mck))  // 7.5ns
	           | MPDDRC_TPR0_TMRD(2);                 // 2 clock cycles

	desc->tpr1 = MPDDRC_TPR1_TRFC(NS2CYCLES(130, mck))  // 130ns
	           | MPDDRC_TPR1_TXSNR(NS2CYCLES(140, mck)) // 140ns
	           | MPDDRC_TPR1_TXSRD(200)                 // 200ck
	           | MPDDRC_TPR1_TXP(2);                    // 2ck

	desc->tpr2 = MPDDRC_TPR2_TXARD(2)                  // 2ck
	           | MPDDRC_TPR2_TXARDS(2)                 // 2ck
	           | MPDDRC_TPR2_TRPA(NS2CYCLES(18, mck))  // 18ns
	           | MPDDRC_TPR2_TRTP(NS2CYCLES(8, mck))   // 8ns
	           | MPDDRC_TPR2_TFAW(NS2CYCLES(50, mck)); // 50ns

	desc->bank = 8192;
}
#endif /* CONFIG_HAVE_LPDDR2_MT42L128M16 */

#endif /* CONFIG_HAVE_MPDDRC_LPDDR2 */

void ddram_init_descriptor(struct _mpddrc_desc* desc,
			   enum _ddram_devices device)
{
	switch(device) {
#ifdef CONFIG_HAVE_MPDDRC_DDR2
  #ifdef CONFIG_HAVE_DDR2_MT47H128M8CF
	case MT47H128M8CF:
		_init_mt47h128m8cf(desc);
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

void ddram_configure(struct _mpddrc_desc* desc, uint32_t tc_id, uint32_t tc_ch)
{
	bool mmu = cp15_mmu_is_enabled();
	bool dcache = cp15_dcache_is_enabled();

	if (mmu)
		cp15_mmu_disable();

	mpddrc_configure(desc, tc_id, tc_ch);

	if (mmu) {
		cp15_mmu_enable();
		if (dcache)
			cp15_dcache_enable();
	}
}
