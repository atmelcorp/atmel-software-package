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

#include "memories/ddram.h"

#include "peripherals/matrix.h"
#include "peripherals/mpddrc.h"

#include "cortex-a/mmu.h"
#include "cortex-a/cp15.h"

#ifdef CONFIG_HAVE_DDR3
static void _init_mt41k128m16(struct _mpddrc_desc* desc)
{
	desc->type = MPDDRC_TYPE_DDR3;

	desc->io_calibr = MPDDRC_IO_CALIBR_RDIV_RZQ_60;

	desc->mode = MPDDRC_MD_MD_DDR3_SDRAM;

	desc->data_path = MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_SHIFT_TWO_CYCLES;

	desc->control = MPDDRC_CR_NC_10_COL_BITS
		| MPDDRC_CR_NR_14_ROW_BITS
		| MPDDRC_CR_CAS_DDR_CAS5
		| MPDDRC_CR_DIS_DLL
		| MPDDRC_CR_NB_8_BANKS
		| MPDDRC_CR_DECOD_INTERLEAVED
		| MPDDRC_CR_UNAL_SUPPORTED;

	/* timings */
	desc->tpr0 = MPDDRC_TPR0_TRAS(6)
		| MPDDRC_TPR0_TRCD(3)
		| MPDDRC_TPR0_TWR(4) // 4 in mode DLL off
		| MPDDRC_TPR0_TRC(9)
		| MPDDRC_TPR0_TRP(3)
		| MPDDRC_TPR0_TRRD(4) // min 4 tCK
		| MPDDRC_TPR0_TWTR(4) // min 4 tCK
		| MPDDRC_TPR0_TMRD(4);

	desc->tpr1 = MPDDRC_TPR1_TRFC(27)
		| MPDDRC_TPR1_TXSNR(29)
		| MPDDRC_TPR1_TXSRD(0)
		| MPDDRC_TPR1_TXP(15);

	desc->tpr2 = MPDDRC_TPR2_TXARD(0)
		| MPDDRC_TPR2_TXARDS(0)
		| MPDDRC_TPR2_TRPA(0)
		| MPDDRC_TPR2_TRTP(4)
		| MPDDRC_TPR2_TFAW(7);

	desc->bank = 8192;
}
#endif

static void _init_mt47h128m8cf(struct _mpddrc_desc* desc)
{
	desc->type = MPDDRC_TYPE_DDR2;
	/* DBW = 0 (32 bits bus wide);
	 * Memory Device = 6 = DDR2-SDRAM = 0x00000006 */
	desc->mode = MPDDRC_MD_MD_DDR2_SDRAM | MPDDRC_MD_DBW_DBW_32_BITS;

	desc->data_path = MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_SHIFT_ONE_CYCLE;

	desc->control = MPDDRC_CR_NR_14_ROW_BITS |
		MPDDRC_CR_NC_10_COL_BITS |
		MPDDRC_CR_CAS_DDR_CAS3 |
		MPDDRC_CR_DLL_RESET_DISABLED |
		MPDDRC_CR_DQMS_NOT_SHARED |
		MPDDRC_CR_ENRDM_OFF |
		MPDDRC_CR_NB_8_BANKS |
		MPDDRC_CR_NDQS_DISABLED |
		MPDDRC_CR_UNAL_SUPPORTED | MPDDRC_CR_OCD_DDR2_EXITCALIB;

	desc->io_calibr = MPDDRC_IO_CALIBR_CALCODEP(7)
		| MPDDRC_IO_CALIBR_CALCODEN(8)
		| MPDDRC_IO_CALIBR_RDIV_RZQ_60
		| MPDDRC_IO_CALIBR_TZQIO(5)
		| MPDDRC_IO_CALIBR_EN_CALIB_ENABLE_CALIBRATION;

	/* timings */
	desc->tpr0 = MPDDRC_TPR0_TRAS(8)	//  40 ns
		| MPDDRC_TPR0_TRCD(3)	//  12.5 ns
		| MPDDRC_TPR0_TWR(3)	//  15 ns
		| MPDDRC_TPR0_TRC(10)	//  55 ns
		| MPDDRC_TPR0_TRP(3)	//
		| MPDDRC_TPR0_TRRD(2)	//  8 ns
		| MPDDRC_TPR0_TWTR(2)	//  2 clock cycle
		| MPDDRC_TPR0_TMRD(2);	//  2 clock cycles
	desc->tpr1 = MPDDRC_TPR1_TRFC(23)
		| MPDDRC_TPR1_TXSNR(25)
		| MPDDRC_TPR1_TXSRD(200)
		| MPDDRC_TPR1_TXP(2);
	desc->tpr2 = MPDDRC_TPR2_TXARD(8)
		| MPDDRC_TPR2_TXARDS(2)
		| MPDDRC_TPR2_TRPA(3)
		| MPDDRC_TPR2_TRTP(2)
		| MPDDRC_TPR2_TFAW(7);

	desc->bank = 8192;
}

static void _init_mt47h128m16(struct _mpddrc_desc* desc)
{
	desc->type = MPDDRC_TYPE_DDR2;
	/* DBW = 0 (32 bits bus wide);
	 * Memory Device = 6 = DDR2-SDRAM = 0x00000006 */
	desc->mode = MPDDRC_MD_MD_DDR2_SDRAM | MPDDRC_MD_DBW_DBW_32_BITS;

	desc->data_path = MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_SHIFT_ONE_CYCLE;

	desc->io_calibr = MPDDRC_IO_CALIBR_CALCODEP(7)
		| MPDDRC_IO_CALIBR_CALCODEN(8)
		| MPDDRC_IO_CALIBR_RDIV_RZQ_60
		| MPDDRC_IO_CALIBR_TZQIO(5)
		| MPDDRC_IO_CALIBR_EN_CALIB_ENABLE_CALIBRATION;

	desc->control = MPDDRC_CR_NR_14_ROW_BITS |
		MPDDRC_CR_NC_10_COL_BITS |
		MPDDRC_CR_CAS_DDR_CAS3 |
		MPDDRC_CR_DLL_RESET_DISABLED |
		MPDDRC_CR_DQMS_NOT_SHARED |
		MPDDRC_CR_ENRDM_OFF |
		MPDDRC_CR_NB_8_BANKS |
		MPDDRC_CR_NDQS_DISABLED |
		MPDDRC_CR_UNAL_SUPPORTED | MPDDRC_CR_OCD_DDR2_EXITCALIB;

	/* timings */
	desc->tpr0 = MPDDRC_TPR0_TRAS(8)        //  40 ns
		| MPDDRC_TPR0_TRCD(3)           //  12.5 ns
		| MPDDRC_TPR0_TWR(3)            //  15 ns
		| MPDDRC_TPR0_TRC(10)           //  55 ns
		| MPDDRC_TPR0_TRP(3)            //  12.5 ns
		| MPDDRC_TPR0_TRRD(3)           //  8 ns
		| MPDDRC_TPR0_TWTR(2)           //  2 clock cycle
		| MPDDRC_TPR0_TMRD(2);          //  2 clock cycles
	desc->tpr1 = MPDDRC_TPR1_TRFC(23)
		| MPDDRC_TPR1_TXSNR(25)
		| MPDDRC_TPR1_TXSRD(200)
		| MPDDRC_TPR1_TXP(2);
	desc->tpr2 = MPDDRC_TPR2_TXARD(8)
		| MPDDRC_TPR2_TXARDS(2)
		| MPDDRC_TPR2_TRPA(3)
		| MPDDRC_TPR2_TRTP(2)
		| MPDDRC_TPR2_TFAW(8);

	desc->bank = 8192;
}

void ddram_init_descriptor(struct _mpddrc_desc* desc,
			   enum _ddram_devices device)
{
	switch(device) {
#ifdef CONFIG_HAVE_DDR3
	case MT41K128M16:
		_init_mt41k128m16(desc);
		break;
#endif
	case MT47H128M8CF:
		_init_mt47h128m8cf(desc);
		break;
	case MT47H128M16:
		_init_mt47h128m16(desc);
		break;
	default:
		break;
	}
}

void ddram_configure(struct _mpddrc_desc* desc)
{
	mpddrc_configure(desc);

	mmu_initialize();
	cp15_icache_invalidate();
	cp15_dcache_invalidate();
	cp15_enable_icache();
	cp15_enable_dcache();
	cp15_enable_mmu();
}
