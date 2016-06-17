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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "compiler.h"

#include "arm_cp15.h"

#include <assert.h>
#include <stdbool.h>

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

uint32_t cp15_read_control(void)
{
	uint32_t control;
	asm("mrc p15, 0, %0, c1, c0, 0" : "=r"(control));
	return control;
}

void cp15_write_control(uint32_t value)
{
	asm("mcr p15, 0, %0, c1, c0, 0" :: "r"(value));
}

bool cp15_mmu_is_enabled(void)
{
	return (cp15_read_control() & CP15_M_BIT) != 0;
}

void cp15_mmu_enable(void)
{
	uint32_t control;

	control = cp15_read_control();
	if ((control & CP15_M_BIT) == 0)
		cp15_write_control(control | CP15_M_BIT);
}

void cp15_mmu_disable(void)
{
	uint32_t control;

	control = cp15_read_control();
	if (control & CP15_M_BIT) {
		cp15_dcache_clean();
		control &= ~(CP15_M_BIT | CP15_C_BIT);
		cp15_write_control(control);
		cp15_dcache_invalidate();
	}
}

void cp15_write_domain_access_control(uint32_t value)
{
	/* write DACR */
	asm("mcr p15, 0, %0, c3, c0, 0" :: "r"(value));
}

void cp15_write_ttb(uint32_t value)
{
	/* write TTBR */
	asm("mcr p15, 0, %0, c2, c0, 0" :: "r"(value));
}

void cp15_cache_set_exclusive(void)
{
	uint32_t actlr;
	asm("mrc p15, 0, %0, c1, c0, 1" : "=r"(actlr));
	actlr |= 0x80;
	asm("mcr p15, 0, %0, c1, c0, 1" :: "r"(actlr));
}

void cp15_cache_set_non_exclusive(void)
{
	uint32_t actlr;
	asm("mrc p15, 0, %0, c1, c0, 1" : "=r"(actlr));
	actlr &= ~0x80;
	asm("mcr p15, 0, %0, c1, c0, 1" :: "r"(actlr));
}

void cp15_icache_invalidate(void)
{
	/* ICIALLU - Invalidate I-cache */
	asm("mcr p15, 0, %0, c7, c5, 0" :: "r"(0));
	isb();
}

bool cp15_icache_is_enabled(void)
{
	return (cp15_read_control() & CP15_I_BIT) != 0;
}

void cp15_icache_enable(void)
{
	uint32_t control = cp15_read_control();
	if ((control & CP15_I_BIT) == 0) {
		cp15_icache_invalidate();
		cp15_write_control(control | CP15_I_BIT);
	}
}

void cp15_icache_disable(void)
{
	uint32_t control = cp15_read_control();
	if (control & CP15_I_BIT) {
		cp15_write_control(control & ~CP15_I_BIT);
		cp15_icache_invalidate();
	}
}

bool cp15_dcache_is_enabled(void)
{
	return (cp15_read_control() & (CP15_C_BIT | CP15_M_BIT)) ==
		(CP15_C_BIT | CP15_M_BIT);
}

void cp15_dcache_enable(void)
{
	uint32_t control = cp15_read_control();
	if (control & CP15_M_BIT) {
		if ((control & CP15_C_BIT) == 0) {
			cp15_dcache_invalidate();
			cp15_write_control(control | CP15_C_BIT);
		}
	}
}

void cp15_dcache_disable(void)
{
	uint32_t control = cp15_read_control();
	if (control & CP15_C_BIT) {
		cp15_dcache_clean();
		cp15_write_control(control & ~CP15_C_BIT);
		cp15_dcache_invalidate();
	}
}

void cp15_dcache_clean(void)
{
	uint32_t set, way;

	for (way = 0; way < L1_CACHE_WAYS; way++) {
		for (set = 0; set < L1_CACHE_SETS; set++) {
			uint32_t setway = (set << 5) | (way << L1_CACHE_WAY_OFFSET);
			/* DCCSW */
			asm("mcr p15, 0, %0, c7, c10, 2" :: "r"(setway));
		}
	}

	dsb();
}

void cp15_dcache_invalidate(void)
{
	uint32_t set, way;

	for (way = 0; way < L1_CACHE_WAYS; way++) {
		for (set = 0; set < L1_CACHE_SETS; set++) {
			uint32_t setway = (set << 5) | (way << L1_CACHE_WAY_OFFSET);
			/* DCISW */
			asm("mcr p15, 0, %0, c7, c6, 2" :: "r"(setway));
		}
	}

	dsb();
}

void cp15_dcache_clean_invalidate(void)
{
	uint32_t set, way;

	for (way = 0; way < L1_CACHE_WAYS; way++) {
		for (set = 0; set < L1_CACHE_SETS; set++) {
			uint32_t setway = (set << 5) | (way << L1_CACHE_WAY_OFFSET);
			/* DCCISW */
			asm("mcr p15, 0, %0, c7, c14, 2" :: "r"(setway));
		}
	}

	dsb();
}

void cp15_dcache_invalidate_region(uint32_t start, uint32_t end)
{
	uint32_t mva;

	assert(start < end);

	for (mva = start & ~L1_CACHE_BYTES; mva < end; mva += L1_CACHE_BYTES) {
		/* DCIMVAC */
		asm("mcr p15, 0, %0, c7, c6, 1" :: "r"(mva));
	}

	dsb();
}

void cp15_dcache_clean_region(uint32_t start, uint32_t end)
{
	uint32_t mva;

	assert(start < end);

	for (mva = start & ~L1_CACHE_BYTES; mva < end; mva += L1_CACHE_BYTES) {
		/* DCCMVAC */
		asm("mcr p15, 0, %0, c7, c10, 1" :: "r"(mva));
	}

	dsb();
}

void cp15_dcache_clean_invalidate_region(uint32_t start, uint32_t end)
{
	uint32_t mva;

	assert(start < end);

	for (mva = start & ~L1_CACHE_BYTES; mva < end; mva += L1_CACHE_BYTES) {
		/* DCCIMVAC */
		asm("mcr p15, 0, %0, c7, c14, 1" :: "r"(mva));
	}

	dsb();
}
