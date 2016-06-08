/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
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

/**
 * \file
 *
 * Interface for cache maintenance.
 *
 * Several macros are provided to place variables in specific section depending
 * on their caching/alignment requirements.
 *
 * NOT_CACHED_DDR will place the variable in the ".region_ddr_nocache" section.
 * This section in located in DDRAM and its MMU attributes makr it as
 * non-cacheable.
 *
 * CACHE_ALIGNED_DDR (resp. CACHE_ALIGNED_SRAM) will place the variable in the
 * ".region_ddr_cache_aligned" section (resp. ".region_ddr_cache_aligned"
 * section) and align the variable start address on a cache line.  Since these
 * sections will contain only cache aligned variables, we can be certain that
 * flushing/invalidating any variable in these regions will not
 * flush/invalidate more than expected.
 */

#ifndef CACHE_H_
#define CACHE_H_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "compiler.h"

#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** Place variable in DDRAM not-cached section
 * Note: this section is *not* initialized at all */
#define NOT_CACHED_DDR \
	SECTION(".region_ddr_nocache")

/** Place variable in default cache-aligned section
 * Note: this section is *not* initialized at all */
#define CACHE_ALIGNED \
	ALIGNED(L1_CACHE_BYTES) \
	SECTION(".region_cache_aligned")

/** Place constant in default cache-aligned section
 * Note: this section is initialized but may be placed in a read-only memory */
#define CACHE_ALIGNED_CONST \
	ALIGNED(L1_CACHE_BYTES) \
	SECTION(".region_cache_aligned_const")

/** Place variable in DRAM cache-aligned section
 * Note: this section is *not* initialized at all */
#ifdef VARIANT_DDRAM
#define CACHE_ALIGNED_DDR \
	CACHE_ALIGNED
#else
#define CACHE_ALIGNED_DDR \
	ALIGNED(L1_CACHE_BYTES) \
	SECTION(".region_ddr_cache_aligned")
#endif

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief Invalidate cache lines corresponding to a memory region
 *
 *  \param start Beginning of the memory region
 *  \param length Length of the memory region
 */
extern void cache_invalidate_region(void *start, uint32_t length);

/**
 *  \brief Clean cache lines corresponding to a memory region
 *
 *  \param start Beginning of the memory region
 *  \param length Length of the memory region
 */
extern void cache_clean_region(const void *start, uint32_t length);

#endif /* #ifndef CACHE_H_ */
