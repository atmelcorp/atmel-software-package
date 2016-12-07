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

#ifndef L1CACHE_H_
#define L1CACHE_H_

/*
 * Functions related to L1 cache maintenance (I-Cache and D-Cache).
 *
 * Actual implementation is located in arch/ since L1 is part of the CPU core.
 */

#ifdef CONFIG_HAVE_L1CACHE

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

/**
 * \brief Invalidate all instruction cache.
 */
extern void icache_invalidate(void);

/**
 * \brief Check if instruction cache is enabled.
 */
extern bool icache_is_enabled(void);

/**
 * \brief Enable instruction cache.
 */
extern void icache_enable(void);

/**
 * \brief Disable instruction cache.
 */
extern void icache_disable(void);

/**
 * \brief Check if data cache is enabled.
 */
extern bool dcache_is_enabled(void);

/**
 * \brief Enable data cache.
 */
extern void dcache_enable(void);

/**
 * \brief Disable the data cache.
 */
extern void dcache_disable(void);

/**
 * \brief Clean the data cache.
 */
extern void dcache_clean(void);

/**
 * \brief Invalidate the data cache.
 */
extern void dcache_invalidate(void);

/**
 * \brief Clean & Invalidate the data cache.
 */
extern void dcache_clean_invalidate(void);

/**
 * \brief Invalidate the data cache within the specified region
 * \param start virtual start address of region
 * \param end virtual end address of region
 */
extern void dcache_invalidate_region(uint32_t start, uint32_t end);

/**
 * \brief Clean the data cache within the specified region.
 * \param start virtual start address of region
 * \param end virtual end address of region
 */
extern void dcache_clean_region(uint32_t start, uint32_t end);

/**
 * \brief Clean and invalidate the data cache within the specified region.
 * \param start virtual start address of region
 * \param end virtual end address of region
 */
extern void dcache_clean_invalidate_region(uint32_t start, uint32_t end);

/**
 * \brief Enable exclusive caching for the L1 cache.
 *
 * The L2 cache must also be configured in exclusive mode.
 */
extern void dcache_set_exclusive(void);

/**
 * \brief Allow data to reside in the L1 and L2 caches at the same time.
 */
extern void dcache_set_non_exclusive(void);

#endif /* CONFIG_HAVE_L1CACHE */

#endif /* L1CACHE_H_ */
