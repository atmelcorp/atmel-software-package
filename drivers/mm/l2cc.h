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

/**
 * \file
 *
 * Interface for Level 2 cache (L2CC) controller.
 *
 */

/** \addtogroup l2cc_module L2 Cache Operations
 * \ingroup cache_module
 * \section Usage
 * - Enable or disable L2CC with L2CC_Enable() or L2CC_Disable().
 * - Check if L2CC is enabled with L2CC_IsEnabled().
 * - Enable or disable L2CC interrupt with L2CC_EnableIT() or L2CC_DisableIT().
 * - Enable data or instruction prefetch with L2CC_DataPrefetchEnable() or L2CC_InstPrefetchEnable().
 *
 * Related files:\n
 * \ref l2cc.h\n
 * \ref l2cc.c\n
 */

#ifndef L2CC_H_
#define L2CC_H_

#ifdef CONFIG_HAVE_L2CC

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "chip.h"

#include <assert.h>

/*----------------------------------------------------------------------------
 *        Define
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#define L2CC_FWA_DEFAULT            0
#define L2CC_FWA_NO_ALLOCATE        1
#define L2CC_FWA_FORCE_ALLOCATE     2
#define L2CC_FWA_INTERNALLY_MAPPED  3

/*----------------------------------------------------------------------------
*        Types
*----------------------------------------------------------------------------*/

struct _l2cc_ram_latency {
	uint8_t setup;
	uint8_t read;
	uint8_t write;
};

/** L2CC structure */
struct _l2cc_config {
	/** High Priority for SO and Dev Reads Enable */
	uint32_t high_prior_so:    1,
	/** Store Buffer Device Limitation Enable */
		store_buff_dev_limit:    1,
	/** Shared Attribute Invalidate Enable */
		shared_attr_invalidate:     1,
	/** Event Monitor Bus Enable */
		evt_mon_bus:    1,
	/** Parity Enable */
		parity:      1,
	/** Shared Attribute Override Enable */
		shared_attr_override:    1,
	/** Force Write Allocate */
		force_write_alloc:      2,
	/** Cache Replacement Policy */
		cache_replacement:    1,
	/** Non-Secure Lockdown Enable*/
		non_sec_lockdown:    1,
	/** Non-Secure Interrupt Access Control */
		it_acces_non_sec:    1,
	/** Data Prefetch Enable*/
		data_prefetch:     1,
	/** Instruction Prefetch Enable */
		instruct_prefetch:     1,
	/** Prefetch Offset */
		offset:   5,
	/** Not Same ID on Exclusive Sequence Enable */
		exclusive_seq_same_id:   1,
	/** INCR Double Linefill Enable */
		incr_double_linefill:    1,
	/** Prefetch Drop Enable*/
		prefetch_drop:     1,
	/** Double Linefill on WRAP Read Disable */
		DLFWRDIS: 1,
	/** Double linefill Enable */
		double_linefill:     1,
	/** Standby Mode Enable */
		standby_mode:   1,
	/** Dynamic Clock Gating Enable */
		dyn_clock_gating: 1,
	/** Disable Cache Linefill*/
		no_cache_linefill:      1,
	/** Disable Write-back, Force Write-through */
		no_write_back:      1;
};
/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Check if Level 2 cache is enable.
 */
extern bool l2cc_is_enabled(void);

/**
 * \brief Enable Level 2 cache.
 */
extern void l2cc_enable(void);

/**
 * \brief Disable Level 2 cache.
 */
extern void l2cc_disable(void);

/**
 * \brief Configures Level 2 cache as exclusive cache.
 */
extern void l2cc_set_exclusive(void);

/**
 * \brief Configures Level 2 cache as non-exclusive cache.
 */
extern void l2cc_set_non_exclusive(void);

/**
 * \brief Configures Level 2 cache Tag RAM Latency
 * \param latency  Structure containing Tag RAM latency
 */
extern void l2cc_set_tag_ram_latency(const struct _l2cc_ram_latency *latency);

/**
 * \brief Configures Level 2 cache Data RAM Latency
 * \param latency  Structure containing Data RAM latency
 */
extern void l2cc_set_data_ram_latency(const struct _l2cc_ram_latency *latency);

/**
 * \brief Configures Level 2 cache.
 * \param cfg  Configuration values to put in Auxiliary, prefetch,
 * debug and powercontrol registers.
 */
extern void l2cc_set_config(const struct _l2cc_config* cfg);

/**
 * \brief Enables Data prefetch on L2
 */
extern void l2cc_data_prefetch_enable(void);

/**
 * \brief Enables instruction prefetch on L2
 */
extern void l2cc_inst_prefetch_enable(void);

/**
 * \brief Enables instruction prefetch on L2
 * \param event_counter Counter of the events.
 */
extern void l2cc_enable_event_counter(uint8_t event_counter);

/**
 * \brief Configures Event of Level 2 cache.
 * \param event_counter  Eventcounter 1 or 0
 * \param source  Event Genration source
 * \param it  Event Counter Interrupt Generation condition
 */
extern void l2cc_event_config(uint8_t event_counter, uint8_t source,
			      uint8_t it);

/**
 * \brief Reads Event Counter value.
 * \param event_counter  choose Eventcounter 1 or 0
 */
extern uint32_t l2cc_event_counter_value(uint8_t event_counter);

/**
 * \brief Enable interrupts
 * \param sources  Interrupt source
 */
extern void l2cc_enable_it(uint32_t sources);

/**
 * \brief Disable interrupts
 * \param sources  Interrupt source
 */
extern void l2cc_disable_it(uint32_t sources);

/**
 * \brief Enabled interrupt's status
 * \param sources  Interrupt source
 */
extern uint32_t l2cc_it_status(uint32_t sources);

/**
 * \brief Status of masked interrupts
 * \param sources  Interrupt source
 */
extern uint32_t l2cc_it_status_mask(uint32_t sources);

/**
 * \brief Clear interrupts
 * \param sources  Interrupt source
 */
extern void l2cc_it_clear(uint32_t sources);

/**
 * \brief Get SPNIDEN signal value
 */
extern bool l2cc_get_spniden(void);

/**
 * \brief Synchronizes the L2 cache
 */
extern void l2cc_cache_sync(void);

/**
 * \brief Invalidate cache by way
 * \param way  way number
 */
extern void l2cc_invalidate_way(uint8_t way);

/**
 * \brief Clean cache by way
 * \param way  way number
 */
extern void l2cc_clean_way(uint8_t way);

/**
 * \brief Clean & Invalidate cache by way
 * \param way  way number
 */
extern void l2cc_clean_invalidate_way(uint8_t way);

/**
 * \brief Invalidate cache by Physical Address
 * \param phys_addr  Physical Address
 */
extern void l2cc_invalidate_pal(uint32_t phys_addr);

/**
 * \brief Clean cache by Physical Address
 * \param phys_addr  Physical Address
 */
extern void l2cc_clean_pal(uint32_t phys_addr);

/**
 * \brief Clean & invalidate index cache by Physical Address
 * \param phys_addr  Physical Address
 */
extern void l2cc_clean_invalidate_pal(uint32_t phys_addr);

/**
 * \brief Clean cache by Index
 * \param phys_addr  Physical addresse
 * \param way  way number
 */
extern void l2cc_clean_index(uint32_t phys_addr, uint8_t way);

/**
 * \brief Clean Invalidate cache by index
 * \param phys_addr  Physical address
 * \param way  way number
 */
extern void l2cc_clean_invalidate_index(uint32_t phys_addr, uint8_t way);

/**
 * \brief cache Data lockdown
 * \param way  way number
 */
extern void l2cc_data_lockdown(uint8_t way);

/**
 * \brief cache instruction lockdown
 * \param way  way number
 */
extern void l2cc_instruction_lockdown(uint8_t way);

/**
 *  \brief Clean L2 DCache
 */
extern void l2cc_clean(void);

/**
 *  \brief Invalidate L2 DCache
 */
extern void l2cc_invalidate(void);

/**
 *  \brief Clean & Invalidate L2 DCache
 */
extern void l2cc_clean_invalidate(void);

/**
 *  \brief Invalidate cache lines corresponding to a memory region
 *
 *  \param start Beginning of the memory region
 *  \param end End of the memory region
 */
extern void l2cc_invalidate_region(uint32_t start, uint32_t end);

/**
 *  \brief Clean cache lines corresponding to a memory region
 *
 *  \param start Beginning of the memory region
 *  \param end End of the memory region
 */
extern void l2cc_clean_region(uint32_t start, uint32_t end);

/**
 *  \brief configure and enable L2 cache controller (L2CC)
 *
 *  \param cfg configuration to apply: \sa #_l2cc_config
 */
extern void l2cc_configure(const struct _l2cc_config* cfg);

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_HAVE_L2CC */

#endif /* L2CC_H_ */
