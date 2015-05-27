/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, Atmel Corporation
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

#ifndef _L2CC_H
#define _L2CC_H

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

#define ENABLE          1
#define DISABLE         0

#define OFFSET_BIT      5
#define INDEX_BIT       9
#define TAG_BIT         18

#define DCACHE_CLEAN            0
#define DCACHE_INVAL            1
#define DCACHE_FLUSH            2

#define RESET_EVCOUNTER0        0
#define RESET_EVCOUNTER1        1
#define RESET_BOTH_COUNTER      3

#define FWA_DEFAULT             0
#define FWA_NO_ALLOCATE         1
#define FWA_FORCE_ALLOCATE      2
#define FWA_INTERNALLY_MAPPED   3

/*----------------------------------------------------------------------------
*        Types
*----------------------------------------------------------------------------*/

struct _latency {
	uint8_t SetupLAT;
	uint8_t ReadLAT;
	uint8_t WriteLAT;
} ;

struct _ram_latency_control {
	struct _latency TagRAM;
	struct _latency DataRAM;
} ;

/** L2CC structur */
struct _l2cc_control {
	/** High Priority for SO and Dev Reads Enable */
	uint32_t HPSO_Val;
	/** Store Buffer Device Limitation Enable */
	uint32_t SBDLE_Val;
	/** Shared Attribute Invalidate Enable */
	uint32_t SAIE_Val;
	/** Event Monitor Bus Enable */
	uint32_t EMBEN_Val;
	/** Parity Enable */
	uint32_t PEN_Val;
	/** Shared Attribute Override Enable */
	uint32_t SAOEN_Val;
	/** Force Write Allocate */
	uint32_t FWA_Val;
	/** Cache Replacement Policy */
	uint32_t CRPOL_Val;
	/** Non-Secure Lockdown Enable*/
	uint32_t NSLEN_Val;
	/** Non-Secure Interrupt Access Control */
	uint32_t NSIAC_Val;
	/** Data Prefetch Enable*/
	uint32_t DPEN_Val;
	/** Instruction Prefetch Enable */
	uint32_t IPEN_Val;
	/** Prefetch Offset */
	uint32_t OFFSET_Val;
	/** Not Same ID on Exclusive Sequence Enable */
	uint32_t NSIDEN_Val;
	/** INCR Double Linefill Enable */
	uint32_t IDLEN_Val;
	/** Prefetch Drop Enable*/
	uint32_t PDEN_Val;
	/** Double Linefill on WRAP Read Disable */
	uint32_t DLFWRDIS_Val;
	/** Double linefill Enable */
	uint32_t DLEN_Val;
	/** Standby Mode Enable */
	uint32_t STBYEN_Val;
	/** Dynamic Clock Gating Enable */
	uint32_t DCKGATEN_Val;
	/** Disable Cache Linefill*/
	uint32_t DCL_Val;
	/** Disable Write-back, Force Write-through */
	uint32_t DWB_Val;
} ;
/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

extern uint32_t l2cc_is_enabled(L2cc * pL2cc);
extern void l2cc_enable(L2cc * pL2cc);
extern void l2cc_disable(L2cc * pL2cc);
extern void l2cc_exclusive_cache(L2cc * pL2cc, uint8_t Enable);
extern void l2cc_config_lat_ram(L2cc * pL2cc, struct _ram_latency_control * pLat);
extern void l2cc_config(L2cc * pL2cc, struct _l2cc_control L2cc_Config);
extern void l2cc_data_prefetch_enable(L2cc * pL2cc);
extern void l2cc_inst_prefetch_enable(L2cc * pL2cc);
extern void l2cc_enable_reset_counter(L2cc * pL2cc, uint8_t EvenetCounter);
extern void l2cc_event_config(L2cc * pL2cc, uint8_t EventCounter, uint8_t Source, uint8_t IntGen);
extern uint32_t l2cc_event_counter_value(L2cc * pL2cc, uint8_t EventCounter);
extern void l2cc_enable_it(L2cc * pL2cc, uint16_t ITSource);
extern void l2cc_disable_it(L2cc * pL2cc, uint16_t ITSource);
extern uint16_t l2cc_it_status_raw(L2cc * pL2cc, uint16_t ITSource);
extern uint16_t l2cc_it_status_mask(L2cc * pL2cc, uint16_t ITSource);
extern void l2cc_it_clear(L2cc * pL2cc, uint16_t ITSource);
extern uint8_t l2cc_poll_spniden(L2cc * pL2cc);
extern void l2cc_cache_sync(L2cc * pL2cc);
extern void l2cc_invalidate_way(L2cc * pL2cc, uint8_t way);
extern void l2cc_clean_way(L2cc * pL2cc, uint8_t way);
extern void l2cc_invalidate_pal(L2cc * pL2cc, uint32_t phys_addr);
extern void l2cc_clean_pal(L2cc * pL2cc, uint32_t phys_addr);
extern void l2cc_clean_ix(L2cc * pL2cc, uint32_t phys_addr);
extern void l2cc_clean_index(L2cc * pL2cc, uint32_t phys_addr, uint8_t way);
extern void l2cc_clean_invalidate_index(L2cc * pL2cc, uint32_t phys_addr, uint8_t way);
extern void l2cc_data_lockdown(L2cc * pL2cc, uint8_t way);
extern void l2cc_instruction_lockdown(L2cc * pL2cc, uint8_t way);
extern void l2cc_cache_maintenance(uint8_t Maint_Op);
extern void enable_l2cc(void);

#ifdef __cplusplus
}
#endif
#endif				/* #ifndef _L2CC_ */
