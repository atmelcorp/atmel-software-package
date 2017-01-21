/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015-2016, Atmel Corporation
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

/*
 * L1 Cache functions implementation for ARMv5-TE and ARMv7-A
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "barriers.h"

#include "arm/cp15.h"

#include "mm/l1cache.h"

#include <assert.h>

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

void icache_invalidate(void)
{
	cp15_icache_invalidate();
	isb();
}

bool icache_is_enabled(void)
{
	return (cp15_read_sctlr() & CP15_SCTLR_I) != 0;
}

void icache_enable(void)
{
	uint32_t sctlr = cp15_read_sctlr();
	if ((sctlr & CP15_SCTLR_I) == 0) {
		icache_invalidate();
		cp15_write_sctlr(sctlr | CP15_SCTLR_I);
	}
}

void icache_disable(void)
{
	uint32_t sctlr = cp15_read_sctlr();
	if (sctlr & CP15_SCTLR_I) {
		cp15_write_sctlr(sctlr & ~CP15_SCTLR_I);
		icache_invalidate();
	}
}

bool dcache_is_enabled(void)
{
	return (cp15_read_sctlr() & (CP15_SCTLR_C | CP15_SCTLR_M)) ==
		(CP15_SCTLR_C | CP15_SCTLR_M);
}

void dcache_enable(void)
{
	uint32_t sctlr = cp15_read_sctlr();
	if ((sctlr & CP15_SCTLR_C) == 0) {
		assert(sctlr & CP15_SCTLR_M);
		dcache_invalidate();
		cp15_write_sctlr(sctlr | CP15_SCTLR_C);
	}
}

void dcache_disable(void)
{
	uint32_t sctlr = cp15_read_sctlr();
	if (sctlr & CP15_SCTLR_C) {
		dcache_clean();
		cp15_write_sctlr(sctlr & ~CP15_SCTLR_C);
		dcache_invalidate();
	}
}

void dcache_invalidate(void)
{
	uint32_t set, way;

	for (way = 0; way < L1_CACHE_WAYS; way++)
		for (set = 0; set < L1_CACHE_SETS; set++)
			cp15_dcache_invalidate_setway(L1_CACHE_SETWAY(set, way));

	dsb();
}

void dcache_clean(void)
{
	uint32_t set, way;

	for (way = 0; way < L1_CACHE_WAYS; way++)
		for (set = 0; set < L1_CACHE_SETS; set++)
			cp15_dcache_clean_setway(L1_CACHE_SETWAY(set, way));

	dsb();
}

void dcache_clean_invalidate(void)
{
	uint32_t set, way;

	for (way = 0; way < L1_CACHE_WAYS; way++)
		for (set = 0; set < L1_CACHE_SETS; set++)
			cp15_dcache_clean_invalidate_setway(L1_CACHE_SETWAY(set, way));

	dsb();
}

void dcache_invalidate_region(uint32_t start, uint32_t end)
{
	uint32_t mva;

	assert(start < end);

	for (mva = start & ~(L1_CACHE_BYTES - 1); mva < end; mva += L1_CACHE_BYTES)
		cp15_dcache_invalidate_mva(mva);

	dsb();
}

void dcache_clean_region(uint32_t start, uint32_t end)
{
	uint32_t mva;

	assert(start < end);

	for (mva = start & ~(L1_CACHE_BYTES - 1); mva < end; mva += L1_CACHE_BYTES)
		cp15_dcache_clean_mva(mva);

	dsb();
}

void dcache_clean_invalidate_region(uint32_t start, uint32_t end)
{
	uint32_t mva;

	assert(start < end);

	for (mva = start & ~(L1_CACHE_BYTES - 1); mva < end; mva += L1_CACHE_BYTES)
		cp15_dcache_clean_invalidate_mva(mva);

	dsb();
}

void dcache_set_exclusive(void)
{
	uint32_t actlr = cp15_read_actlr();
	actlr |= CP15_ACTLR_EXCL;
	cp15_write_actlr(actlr);
}

void dcache_set_non_exclusive(void)
{
	uint32_t actlr = cp15_read_actlr();
	actlr &= ~CP15_ACTLR_EXCL;
	cp15_write_actlr(actlr);
}
