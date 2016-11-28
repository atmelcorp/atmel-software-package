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

/*------------------------------------------------------------------------------ */
/*         Headers                                                               */
/*------------------------------------------------------------------------------ */

#include "compiler.h"
#include "barriers.h"

#include "arm/cp15.h"
#include "arm/mmu_cp15.h"

#include "mm/l1cache.h"
#include "mm/mmu.h"

#include <assert.h>

/*------------------------------------------------------------------------------ */
/*         Exported functions                                                    */
/*------------------------------------------------------------------------------ */

void mmu_configure(void *tlb)
{
	assert(!mmu_is_enabled());

	/* Translation Table Base Register 0 */
	cp15_write_ttbr0((unsigned int)tlb);

	/* Domain Access Register */
	/* only domain 15: access are not checked */
	cp15_write_dacr(0xC0000000);

	dsb();
	isb();
}

bool mmu_is_enabled(void)
{
	return (cp15_read_sctlr() & CP15_SCTLR_M) != 0;
}

void mmu_enable(void)
{
	uint32_t control;

	control = cp15_read_sctlr();
	if ((control & CP15_SCTLR_M) == 0)
		cp15_write_sctlr(control | CP15_SCTLR_M);
}

void mmu_disable(void)
{
	uint32_t control;

	control = cp15_read_sctlr();
	if (control & CP15_SCTLR_M) {
		dcache_clean();
		control &= ~(CP15_SCTLR_M | CP15_SCTLR_C);
		cp15_write_sctlr(control);
		dcache_invalidate();
	}
}
