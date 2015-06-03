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

/** \file */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "peripherals/l2cc.h"
#include "cortex-a/cp15.h"
#include "trace.h"

#include <assert.h>

/*----------------------------------------------------------------------------
 *        Functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Check if Level 2 cache is enable.
 * \param pL2cc Pointer to the L2CC peripheral.
 */
uint32_t l2cc_is_enabled(L2cc * pL2cc)
{
	return ((pL2cc->L2CC_CR) & L2CC_CR_L2CEN);
}

/**
 * \brief Enable Level 2 cache.
 * \param pL2cc Pointer to the L2CC peripheral.
 */
void l2cc_enable(L2cc * pL2cc)
{
	pL2cc->L2CC_CR |= L2CC_CR_L2CEN;
	trace_info("L2 cache is enabled");
}

/**
 * \brief Disable Level 2 cache.
 * \param pL2cc Pointer to the L2CC peripheral.
 */
void l2cc_disable(L2cc * pL2cc)
{
	pL2cc->L2CC_CR &= (!L2CC_CR_L2CEN);
	trace_info("L2 cache is Disabled");
}

/**
 * \brief Configures Level 2 cache as exclusive cache.
 * \param pL2cc Pointer to the L2CC peripheral.
 * \param Enable Enable/disable exclusive cache.
 */
void l2cc_exclusive_cache(L2cc * pL2cc, uint8_t Enable)
{
	uint32_t Aux_Cfg;
	if (l2cc_is_enabled(pL2cc)) {
		pL2cc->L2CC_CR = DISABLE;
	}
	Aux_Cfg = pL2cc->L2CC_ACR;
	if (Enable) {
		cp15_exclusive_cache();
		Aux_Cfg |= L2CC_ACR_EXCC;
		trace_info("L2 Exclusive mode Enabled\n\r");
	} else {
		cp15_non_exclusive_cache();
		Aux_Cfg &= ~L2CC_ACR_EXCC;
		trace_info("L2 Exclusive mode Disabled\n\r");
	}
	pL2cc->L2CC_ACR |= Aux_Cfg;
}

/**
 * \brief Configures Level 2 cache RAM Latency (Tag and Data).
 * \param pL2cc Pointer to the L2CC peripheral.
 * \param pLat  Structure containing RAM Tag and Data latencies
 */
void l2cc_config_lat_ram(L2cc * pL2cc, struct _ram_latency_control * pLat)
{
	if (l2cc_is_enabled(pL2cc)) {
		pL2cc->L2CC_CR = DISABLE;
	}

	pL2cc->L2CC_TRCR =
	    (L2CC_TRCR_TSETLAT(pLat->TagRAM.SetupLAT) |
		 		L2CC_TRCR_TRDLAT(pLat->TagRAM.ReadLAT) |
			 	L2CC_TRCR_TWRLAT(pLat->TagRAM.WriteLAT));
	pL2cc->L2CC_DRCR =
	    (L2CC_DRCR_DSETLAT(pLat->DataRAM.SetupLAT) |
		 		L2CC_DRCR_DRDLAT(pLat->DataRAM.ReadLAT) |
				L2CC_DRCR_DWRLAT(pLat->DataRAM.WriteLAT));
}

/**
 * \brief Configures Level 2 cache.
 * \param pL2cc Pointer to the L2CC peripheral.
 * \param L2cc_Config  Configuration values to put in Auxiliary, prefetch, debug and powercontrol registers
 */
void l2cc_config(L2cc * pL2cc, struct _l2cc_control L2cc_Config)
{
	uint32_t AuxiliaryControl, DebugControl, PrefetchControl, PowerControl;

	if (L2cc_Config.OFFSET_Val > 31) {
		assert(0);
	}
	if ((L2cc_Config.OFFSET_Val > 7) && (L2cc_Config.OFFSET_Val < 15)) {
		assert(0);
	}
	if ((L2cc_Config.OFFSET_Val > 15) && (L2cc_Config.OFFSET_Val < 23)) {
		assert(0);
	}
	if ((L2cc_Config.OFFSET_Val > 23) && (L2cc_Config.OFFSET_Val < 31)) {
		assert(0);
	}
//  if( ((L2cc_Config.IDLEN_Val==1) || (L2cc_Config.DLFWRDIS_Val==0)) && L2cc_Config.DLEN_Val==0)
//  {
//    trace_error(" DLEN is not enabled for Double Line fill");
//    assert(0);
//  }

	if (l2cc_is_enabled(pL2cc)) {
		pL2cc->L2CC_CR = DISABLE;
	}

	AuxiliaryControl = ((L2cc_Config.HPSO_Val << 10) |
			    (L2cc_Config.SBDLE_Val << 11) |
			    (L2cc_Config.SAIE_Val << 13) |
			    (L2cc_Config.EMBEN_Val << 20) |
			    (L2cc_Config.PEN_Val << 21) |
			    (L2cc_Config.SAOEN_Val << 22) |
			    (L2CC_ACR_FWA(L2cc_Config.FWA_Val)) |
			    (L2cc_Config.CRPOL_Val << 25) |
			    (L2cc_Config.NSLEN_Val << 26) |
			    (L2cc_Config.NSIAC_Val << 27) |
			    (L2cc_Config.DPEN_Val << 28) |
			    (L2cc_Config.IPEN_Val << 29));

	DebugControl = ((L2cc_Config.DCL_Val << 0) |
			(L2cc_Config.DWB_Val << 1));

	PrefetchControl = ((L2cc_Config.OFFSET_Val << 0) |
			   (L2cc_Config.NSIDEN_Val << 21) |
			   (L2cc_Config.IDLEN_Val << 23) |
			   (L2cc_Config.PDEN_Val << 24) |
			   (L2cc_Config.DLFWRDIS_Val << 27) |
			   (L2cc_Config.DPEN_Val << 28) |
			   (L2cc_Config.IPEN_Val << 29) |
			   (L2cc_Config.DLEN_Val << 30));

	PowerControl = ((L2cc_Config.DCL_Val << 0) |
			(L2cc_Config.DWB_Val << 1));

	pL2cc->L2CC_ACR = AuxiliaryControl;
	pL2cc->L2CC_DCR = DebugControl;
	pL2cc->L2CC_PCR = PrefetchControl;
	pL2cc->L2CC_POWCR = PowerControl;
}

/**
 * \brief Enables Data prefetch on L2
 * \param pL2cc Pointer to the L2CC peripheral.
 */
void l2cc_data_prefetch_enable(L2cc * pL2cc)
{
	pL2cc->L2CC_PCR |= L2CC_PCR_DATPEN;
}

/**
 * \brief Enables instruction prefetch on L2
 * \param pL2cc Pointer to the L2CC peripheral.
 */
void l2cc_inst_prefetch_enable(L2cc * pL2cc)
{
	pL2cc->L2CC_PCR |= L2CC_PCR_INSPEN;
}

/**
 * \brief Enables instruction prefetch on L2
 * \param pL2cc Pointer to the L2CC peripheral.
 * \param EventCounter Counter of the events.
 */
void l2cc_enable_reset_counter(L2cc * pL2cc, uint8_t EventCounter)
{
	assert((EventCounter > 3) ? 0 : 1);
	pL2cc->L2CC_ECR = (L2CC_ECR_EVCEN | (EventCounter << 1));
}

/**
 * \brief Configures Event of Level 2 cache.
 * \param pL2cc Pointer to the L2CC peripheral.
 * \param EventCounter  Eventcounter 1 or 0
 * \param Source  Event Genration source
 * \param IntGen  Event Counter Interrupt Generation condition
 */
void l2cc_event_config(L2cc * pL2cc, uint8_t EventCounter, uint8_t Source, uint8_t IntGen)
{
	if (l2cc_is_enabled(pL2cc)) {
		pL2cc->L2CC_CR = DISABLE;
	}
	assert((EventCounter > 1) ? 0 : 1);
	if (!EventCounter) {
		pL2cc->L2CC_ECFGR0 = (Source | IntGen);
	} else {
		pL2cc->L2CC_ECFGR1 = (Source | IntGen);
	}

}

/**
 * \brief Reads Eventcounter value.
 * \param pL2cc Pointer to the L2CC peripheral.
 * \param EventCounter  choose Eventcounter 1 or 0
 */
uint32_t l2cc_event_counter_value(L2cc * pL2cc, uint8_t EventCounter)
{
	assert((EventCounter > 1) ? 0 : 1);
	if (!EventCounter) {
		return pL2cc->L2CC_EVR0;
	} else {
		return pL2cc->L2CC_EVR1;
	}
}

/**
 * \brief Enable interrupts
 * \param pL2cc Pointer to the L2CC peripheral.
 * \param ITSource  Interrupt source
 */
void l2cc_enable_it(L2cc * pL2cc, uint16_t ITSource)
{
	pL2cc->L2CC_IMR |= ITSource;
}

/**
 * \brief Disable interrupts
 * \param pL2cc Pointer to the L2CC peripheral.
 * \param ITSource  Interrupt source
 */
void l2cc_disable_it(L2cc * pL2cc, uint16_t ITSource)
{
	pL2cc->L2CC_IMR &= (!ITSource);
}

/**
 * \brief Enabled interrupt's raw status
 * \param pL2cc Pointer to the L2CC peripheral.
 * \param ITSource  Interrupt source
 */
unsigned short l2cc_it_status_raw(L2cc * pL2cc, uint16_t ITSource)
{
	return ((pL2cc->L2CC_RISR) & ITSource) ? 1 : 0;
}

/**
 * \brief Status of masked interrupts
 * \param pL2cc Pointer to the L2CC peripheral.
 * \param ITSource  Interrupt source
 */
uint16_t l2cc_it_status_mask(L2cc * pL2cc, uint16_t ITSource)
{
	return ((pL2cc->L2CC_MISR) & ITSource) ? 1 : 0;
}

/**
 * \brief Clear interrupts
 * \param pL2cc Pointer to the L2CC peripheral.
 * \param ITSource  Interrupt source
 */
void l2cc_it_clear(L2cc * pL2cc, uint16_t ITSource)
{
	pL2cc->L2CC_ICR |= ITSource;
}

/**
 * \brief Poll SPNIDEN signal
 * \param pL2cc Pointer to the L2CC peripheral.
 */
uint8_t l2cc_poll_spniden(L2cc * pL2cc)
{
	return ((pL2cc->L2CC_DCR & L2CC_DCR_SPNIDEN) >> 2);
}

/**
 * \brief Synchronizes the L2 cache
 * \param pL2cc Pointer to the L2CC peripheral.
 */
void l2cc_cache_sync(L2cc * pL2cc)
{
	while ((pL2cc->L2CC_CSR) & L2CC_CSR_C) ;
	pL2cc->L2CC_CSR = L2CC_CSR_C;
	while ((pL2cc->L2CC_CSR) & L2CC_CSR_C) ;
}

/**
 * \brief Invalidate cache by Physical addersse
 * \param pL2cc Pointer to the L2CC peripheral.
 * \param phys_addr  Physical addresse
 */
void l2cc_invalidate_pal(L2cc * pL2cc, uint32_t phys_addr)
{
	static uint32_t Tag;
	static uint16_t Index;
	Tag = (phys_addr >> (OFFSET_BIT + INDEX_BIT));
	Index = (phys_addr >> OFFSET_BIT) & ((1 << INDEX_BIT) - 1);
	pL2cc->L2CC_IPALR = (L2CC_IPALR_TAG(Tag) | L2CC_IPALR_IDX(Index) | L2CC_IPALR_C);
	while ((pL2cc->L2CC_IPALR) & L2CC_IPALR_C) ;
}

/**
 * \brief Clean cache by Physical addersse
 * \param pL2cc Pointer to the L2CC peripheral.
 * \param phys_addr  Physical addresse
 */
void l2cc_clean_pal(L2cc * pL2cc, uint32_t phys_addr)
{
	static uint32_t Tag;
	static uint16_t Index;

	Tag = (phys_addr >> (OFFSET_BIT + INDEX_BIT));
	Index = (phys_addr >> OFFSET_BIT) & ((1 << INDEX_BIT) - 1);
	pL2cc->L2CC_CPALR =
	    (L2CC_CPALR_TAG(Tag) | L2CC_CPALR_IDX(Index) | L2CC_CPALR_C);
	while ((pL2cc->L2CC_CPALR) & L2CC_CPALR_C) ;
}

/**
 * \brief Clean index cache by Physical addersse
 * \param pL2cc Pointer to the L2CC peripheral.
 * \param phys_addr  Physical addresse
 */
void l2cc_clean_ix(L2cc * pL2cc, uint32_t phys_addr)
{
	static uint32_t Tag;
	static uint16_t Index;

	Tag = (phys_addr >> (OFFSET_BIT + INDEX_BIT));
	Index = (phys_addr >> OFFSET_BIT) & ((1 << INDEX_BIT) - 1);
	pL2cc->L2CC_CIPALR =
	    (L2CC_CIPALR_TAG(Tag) | L2CC_CIPALR_IDX(Index) | L2CC_CIPALR_C);
	while ((pL2cc->L2CC_CIPALR) & L2CC_CIPALR_C) ;
}

/**
 * \brief Invalidate cache by way
 * \param pL2cc Pointer to the L2CC peripheral.
 * \param way  way number
 */
void l2cc_invalidate_way(L2cc * pL2cc, uint8_t way)
{
	pL2cc->L2CC_IWR = way;
	while (pL2cc->L2CC_IWR) ;
	while (pL2cc->L2CC_CSR) ;
}

/**
 * \brief Clean cache by way
 * \param pL2cc Pointer to the L2CC peripheral.
 * \param way  way number
 */
void l2cc_clean_way(L2cc * pL2cc, uint8_t way)
{
	pL2cc->L2CC_CWR = way;
	while (pL2cc->L2CC_CWR) ;
	while (pL2cc->L2CC_CSR) ;
}

/**
 * \brief Clean Invalidate cache by way
 * \param pL2cc Pointer to the L2CC peripheral.
 * \param way  way number
 */
static void l2cc_clean_invalidate_way(L2cc * pL2cc, uint8_t way)
{
	pL2cc->L2CC_CIWR = way;
	while (pL2cc->L2CC_CSR) ;
}

/**
 * \brief Clean cache by Index
 * \param pL2cc Pointer to the L2CC peripheral.
 * \param phys_addr  Physical addresse
 * \param way  way number
 */
void l2cc_clean_index(L2cc * pL2cc, uint32_t phys_addr, uint8_t way)
{
	static uint16_t Index;

	Index = (phys_addr >> OFFSET_BIT) & ((1 << INDEX_BIT) - 1);
	pL2cc->L2CC_CIR =
	    (L2CC_CIR_IDX(Index) | L2CC_CIR_WAY(way) | L2CC_CIR_C);
	while ((pL2cc->L2CC_CIR) & L2CC_CIR_C) ;
}

/**
 * \brief Clean Invalidate cache by index
 * \param pL2cc Pointer to the L2CC peripheral.
 * \param phys_addr  Physical address
 * \param way  way number
 */
void l2cc_clean_invalidate_index(L2cc * pL2cc, uint32_t phys_addr, uint8_t way)
{
	static uint16_t Index;

	Index = (phys_addr >> OFFSET_BIT) & ((1 << INDEX_BIT) - 1);
	pL2cc->L2CC_CIIR =
	    (L2CC_CIIR_IDX(Index) | L2CC_CIIR_WAY(Index) | L2CC_CIIR_C);
	while ((pL2cc->L2CC_CIIR) & L2CC_CIIR_C) ;
}

/**
 * \brief cache Data lockdown
 * \param pL2cc Pointer to the L2CC peripheral.
 * \param way  way number
 */
void l2cc_data_lockdown(L2cc * pL2cc, uint8_t way)
{
	pL2cc->L2CC_DLKR = way;
	while (pL2cc->L2CC_CSR) ;
}

/**
 * \brief cache instruction lockdown
 * \param pL2cc Pointer to the L2CC peripheral.
 * \param way  way number
 */
void l2cc_instruction_lockdown(L2cc * pL2cc, uint8_t way)
{
	pL2cc->L2CC_ILKR = way;
	while (pL2cc->L2CC_CSR) ;
}

static void l2cc_clean(void)
{
	cp15_cache_clean(CP15_DCache);	// Clean of L1; This is broadcast within the cluster
	l2cc_clean_way(L2CC, 0xFF);	// forces the address out past level 2
	l2cc_cache_sync(L2CC);	// Ensures completion of the L2 clean
}

static void l2cc_invalidate(void)
{
	l2cc_invalidate_way(L2CC, 0xFF);	// forces the address out past level 2
	l2cc_cache_sync(L2CC);	// Ensures completion of the L2 inval
	cp15_cache_invalidate(CP15_DCache);	// Inval of L1; This is broadcast within the cluster
}

static void l2cc_clean_invalidate(void)
{
	cp15_cache_clean(CP15_DCache);	// Clean of L1; This is broadcast within the cluster
	l2cc_clean_invalidate_way(L2CC, 0xFF);	// forces the address out past level 2
	l2cc_cache_sync(L2CC);	// Ensures completion of the L2 inval
	cp15_cache_invalidate(CP15_DCache);	// Inval of L1; This is broadcast within the cluster
}

/**
 *  \brief L2 DCache maintenance (clean/invalidate/flush)
 */
void l2cc_cache_maintenance(uint8_t Maint_Op)
{
	switch (Maint_Op) {
		case DCACHE_CLEAN:
			l2cc_clean();
			break;
		case DCACHE_INVAL:
			l2cc_invalidate();
			break;
		case DCACHE_FLUSH:
			l2cc_clean_invalidate();
			break;
	}
}

/**
 *  \brief Enable level two cache controller (L2CC)
 */
void enable_l2cc(void)
{
	struct _l2cc_control L2Config;

	/*****1. configure L2CC ************/
	L2Config.IPEN_Val = ENABLE;	// Instruction prefetch enable
	L2Config.DPEN_Val = ENABLE;	// Data prefetch enable
	L2Config.DLEN_Val = ENABLE;
	L2Config.IDLEN_Val = ENABLE;

	// Disable Write back (enables write through, Use this setting if DDR2 mem is not write-back)
	//L2Config.DWB_Val = ENABLE;

	L2Config.FWA_Val = FWA_NO_ALLOCATE;
	L2Config.OFFSET_Val = 31;
	L2Config.PDEN_Val = ENABLE;
	L2Config.STBYEN_Val = ENABLE;
	L2Config.DCKGATEN_Val = ENABLE;

	l2cc_event_config(L2CC, 0, L2CC_ECFGR0_ESRC_SRC_DRHIT, L2CC_ECFGR0_EIGEN_INT_DIS);
	l2cc_event_config(L2CC, 1, L2CC_ECFGR0_ESRC_SRC_DWHIT, L2CC_ECFGR0_EIGEN_INT_DIS);
	l2cc_enable_reset_counter(L2CC, RESET_BOTH_COUNTER);
	l2cc_config(L2CC, L2Config);
	/* Enable Prefetch */
	l2cc_inst_prefetch_enable(L2CC);
	l2cc_data_prefetch_enable(L2CC);
	/*2. Invalidate whole L2CC     ********** */
	l2cc_invalidate_way(L2CC, 0xFF);
	/*3. Disable all L2CC Interrupt ********** */
	l2cc_disable_it(L2CC, 0x1FF);
	/*4. Clear all L2CC Interrupt ********** */
	l2cc_it_clear(L2CC, 0);
	l2cc_exclusive_cache(L2CC, ENABLE);
	l2cc_enable(L2CC);
}
