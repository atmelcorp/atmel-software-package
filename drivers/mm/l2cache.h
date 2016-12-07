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

#ifndef L2CACHE_H_
#define L2CACHE_H_

/*
 * Functions related to L2 cache maintenance
 */

#ifdef CONFIG_HAVE_L2CACHE

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

/**
 * \brief Check if L2 cache is enabled.
 */
extern bool l2cache_is_enabled(void);

/**
 * \brief Enable L2 cache.
 */
extern void l2cache_enable(void);

/**
 * \brief Disable the L2 cache.
 */
extern void l2cache_disable(void);

/**
 * \brief Clean the L2 cache.
 */
extern void l2cache_clean(void);

/**
 * \brief Invalidate the L2 cache.
 */
extern void l2cache_invalidate(void);

/**
 * \brief Clean & Invalidate the L2 cache.
 */
extern void l2cache_clean_invalidate(void);

/**
 * \brief Invalidate the L2 cache within the specified region
 * \param start virtual start address of region
 * \param end virtual end address of region
 */
extern void l2cache_invalidate_region(uint32_t start, uint32_t end);

/**
 * \brief Clean the L2 cache within the specified region.
 * \param start virtual start address of region
 * \param end virtual end address of region
 */
extern void l2cache_clean_region(uint32_t start, uint32_t end);

/**
 * \brief Clean and invalidate the L2 cache within the specified region.
 * \param start virtual start address of region
 * \param end virtual end address of region
 */
extern void l2cache_clean_invalidate_region(uint32_t start, uint32_t end);

/**
 * \brief Enable exclusive caching for the L2 cache.
 *
 * The L1 cache must also be configured in exclusive mode.
 */
extern void l2cache_set_exclusive(void);

/**
 * \brief Allow data to reside in the L1 and L2 caches at the same time.
 */
extern void l2cache_set_non_exclusive(void);

#endif /* CONFIG_HAVE_L2CACHE */

#endif /* L2CACHE_H_ */
