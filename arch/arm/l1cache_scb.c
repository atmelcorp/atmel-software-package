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
 * L1 Cache functions implementation for ARMv7-M
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "barriers.h"

#include "mm/l1cache.h"

#include <assert.h>

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

void icache_invalidate(void)
{
	dsb();
	isb();
	SCB->SCB_ICIALLU = 0;
	dsb();
	isb();
}

bool icache_is_enabled(void)
{
	return (SCB->SCB_CCR & SCB_CCR_IC) != 0;
}

void icache_enable(void)
{
	if (!icache_is_enabled()) {
		icache_invalidate();
		SCB->SCB_CCR |= SCB_CCR_IC;
		dsb();
		isb();
	}
}

void icache_disable(void)
{
	if (icache_is_enabled()) {
		dsb();
		isb();
		SCB->SCB_CCR &= ~SCB_CCR_IC;
		icache_invalidate();
	}
}

bool dcache_is_enabled(void)
{
	return (SCB->SCB_CCR & SCB_CCR_DC) != 0;
}

void dcache_enable(void)
{
	if (!dcache_is_enabled()) {
		dcache_invalidate();
		SCB->SCB_CCR |= SCB_CCR_DC;
		dsb();
		isb();
	}
}

void dcache_disable(void)
{
	if (dcache_is_enabled()) {
		dsb();
		SCB->SCB_CCR &= ~SCB_CCR_DC;
		dcache_clean_invalidate();
	}
}

void dcache_invalidate(void)
{
	uint32_t set, way;

	for (way = 0; way < L1_CACHE_WAYS; way++)
		for (set = 0; set < L1_CACHE_SETS; set++)
			SCB->SCB_DCISW = L1_CACHE_SETWAY(set, way);

	dsb();
	isb();
}

void dcache_clean(void)
{
	uint32_t set, way;

	for (way = 0; way < L1_CACHE_WAYS; way++)
		for (set = 0; set < L1_CACHE_SETS; set++)
			SCB->SCB_DCCSW = L1_CACHE_SETWAY(set, way);

	dsb();
	isb();
}

void dcache_clean_invalidate(void)
{
	uint32_t set, way;

	for (way = 0; way < L1_CACHE_WAYS; way++)
		for (set = 0; set < L1_CACHE_SETS; set++)
			SCB->SCB_DCCISW = L1_CACHE_SETWAY(set, way);

	dsb();
	isb();
}

void dcache_invalidate_region(uint32_t start, uint32_t end)
{
	uint32_t mva;

	assert(start < end);

	for (mva = start & ~(L1_CACHE_BYTES - 1); mva < end; mva += L1_CACHE_BYTES)
		SCB->SCB_DCIMVAC = mva;

	dsb();
	isb();
}

void dcache_clean_region(uint32_t start, uint32_t end)
{
	uint32_t mva;

	assert(start < end);

	for (mva = start & ~(L1_CACHE_BYTES - 1); mva < end; mva += L1_CACHE_BYTES)
		SCB->SCB_DCCMVAC = mva;

	dsb();
	isb();
}

void dcache_clean_invalidate_region(uint32_t start, uint32_t end)
{
	uint32_t mva;

	assert(start < end);

	for (mva = start & ~(L1_CACHE_BYTES - 1); mva < end; mva += L1_CACHE_BYTES)
		SCB->SCB_DCCIMVAC = mva;

	dsb();
	isb();
}

void dcache_set_exclusive(void)
{
	/* Not implemented */
}

void dcache_set_non_exclusive(void)
{
	/* Not implemented */
}
