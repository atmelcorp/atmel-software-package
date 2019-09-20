/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2018, Microchip Technology
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

#include "extram/sdram.h"

#include "extram/sdramc.h"
#include "peripherals/pmc.h"

#include "mm/l1cache.h"

#include <assert.h>
#include <string.h>

/*------------------------------------------------------------------------------
 *        Macro
 *----------------------------------------------------------------------------*/

/* Convert nanoseconds to clock cycles for given master clock in MHz */
#define NS2CYCLES(ns, clk) ((((ns) * (clk)) + 999) / 1000)

/*---------------------------------------------------------------------------
 *      Local functions
 *---------------------------------------------------------------------------*/

#ifdef CONFIG_HAVE_SDRAM_MT48LC16M16
static void _init_mt48lc16m16(struct _sdramc_desc *desc)
{
	uint32_t mck = pmc_get_master_clock() / 1000000;

	desc->is_lpsdr = false;
	desc->nb_columns = 9;
	desc->nb_rows = 13;
	desc->nb_banks = 4;
	desc->data_bus_width = 16;
	desc->cas_latency = 3;
	desc->shift_sampling = 3;

	/* timings for 166MHz */

	memset(&desc->timings, 0, sizeof(desc->timings));
	desc->timings.tmrd = 2;                     // 2ck
	desc->timings.twr  = NS2CYCLES(12, mck);    // 12ns
	desc->timings.trc  = NS2CYCLES(60, mck);    // 60ns
	desc->timings.trfc = NS2CYCLES(60, mck);    // 60ns
	desc->timings.trp  = NS2CYCLES(18, mck);    // 18ns
	desc->timings.trcd = NS2CYCLES(18, mck);    // 18ns
	desc->timings.tras = NS2CYCLES(42, mck);    // 42ns
	desc->timings.txsr = NS2CYCLES(67, mck);    // 67ns

	desc->refresh_window = 64;
	desc->refresh_cycles = 8192;
}

static void _init_mt48lc16m16x2(struct _sdramc_desc *desc)
{
	_init_mt48lc16m16(desc);
	desc->data_bus_width = 32; /* 2 x 16-bit chips */
}
#endif /* CONFIG_HAVE_SDRAM_MT48LC16M16 */

#ifdef CONFIG_HAVE_LPSDR_MT48H32M16
static void _init_mt48h32m16(struct _sdramc_desc *desc)
{
	uint32_t mck = pmc_get_master_clock() / 1000000;

	desc->is_lpsdr = true;
	desc->nb_columns = 10;
	desc->nb_rows = 13;
	desc->nb_banks = 4;
	desc->data_bus_width = 16;
	desc->cas_latency = 3;
	desc->shift_sampling = 3;

	/* timings for 166MHz */

	memset(&desc->timings, 0, sizeof(desc->timings));
	desc->timings.tmrd = 2;                     // 2ck
	desc->timings.twr  = NS2CYCLES(15, mck);    // 15ns
	desc->timings.trc  = NS2CYCLES(60, mck);    // 60ns
	desc->timings.trfc = NS2CYCLES(72, mck);    // 72ns
	desc->timings.trp  = NS2CYCLES(18, mck);    // 18ns
	desc->timings.trcd = NS2CYCLES(18, mck);    // 18ns
	desc->timings.tras = NS2CYCLES(42, mck);    // 42ns
	desc->timings.txsr = NS2CYCLES(120, mck);   // 120ns

	desc->refresh_window = 64;
	desc->refresh_cycles = 8192;
}
#endif /* CONFIG_HAVE_LPSDR_MT48H32M16 */

#ifdef CONFIG_HAVE_SDRAM_W9864G6KH
static void _init_w9864g6kh(struct _sdramc_desc *desc)
{
	uint32_t mck = pmc_get_master_clock() / 1000000;

	desc->is_lpsdr = false;
	desc->nb_columns = 8;
	desc->nb_rows = 12;
	desc->nb_banks = 4;
	desc->data_bus_width = 16;
	desc->cas_latency = 3;
	desc->shift_sampling = 3;

	memset(&desc->timings, 0, sizeof(desc->timings));
	desc->timings.tmrd = 2;                     // 2ck
	desc->timings.twr  = 2;                     // min 2ck
	desc->timings.trc  = NS2CYCLES(60, mck);    // 60ns
	desc->timings.trfc = NS2CYCLES(72, mck);    // 72ns
	desc->timings.trp  = NS2CYCLES(18, mck);    // 18ns
	desc->timings.trcd = NS2CYCLES(20, mck);    // 20ns
	desc->timings.tras = NS2CYCLES(45, mck);    // 45ns
	desc->timings.txsr = NS2CYCLES(75, mck);    // 75ns

	desc->refresh_window = 64;
	desc->refresh_cycles = 8192;
}
#endif /* CONFIG_HAVE_SDRAM_W9864G6KH */

/*------------------------------------------------------------------------------
 *        Exported Functions
 *----------------------------------------------------------------------------*/

void sdram_init_descriptor(struct _sdramc_desc *desc,
			   enum _sdram_devices device)
{
	switch (device) {
#ifdef CONFIG_HAVE_SDRAM_MT48LC16M16
	case MT48LC16M16:
		_init_mt48lc16m16(desc);
		break;
	case MT48LC16M16X2:
		_init_mt48lc16m16x2(desc);
		break;
#endif
#ifdef CONFIG_HAVE_LPSDR_MT48H32M16
	case MT48H32M16:
		_init_mt48h32m16(desc);
		break;
#endif
#ifdef CONFIG_HAVE_SDRAM_W9864G6KH
	case W9864G6KH:
		_init_w9864g6kh(desc);
		break;
#endif
	default:
		trace_fatal("Unsupported SDRAM type\r\n");
		break;
	}
}

void sdram_configure(const struct _sdramc_desc *desc)
{
	assert(!dcache_is_enabled());
	sdramc_configure(desc);
}
