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
#include "compiler.h"

#include "peripherals/l2cc.h"

#include <assert.h>
#include <stdbool.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

#define L2CC_OFFSET_BIT 5
#define L2CC_INDEX_BIT  9
#define L2CC_TAG_BIT    18

/*----------------------------------------------------------------------------
 *        Functions
 *----------------------------------------------------------------------------*/

bool l2cc_is_enabled(void)
{
	return (L2CC->L2CC_CR & L2CC_CR_L2CEN) != 0;
}

void l2cc_enable(void)
{
#ifdef SFR_L2CC_HRAMC_SRAM_SEL
	SFR->SFR_L2CC_HRAMC = SFR_L2CC_HRAMC_SRAM_SEL;
#endif
	L2CC->L2CC_CR |= L2CC_CR_L2CEN;
	dsb();
	isb();
}

void l2cc_disable(void)
{
	L2CC->L2CC_CR &= ~L2CC_CR_L2CEN;
	dsb();
	isb();
}

void l2cc_set_exclusive(void)
{
	assert(!l2cc_is_enabled());
	cp15_cache_set_exclusive();
	L2CC->L2CC_ACR |= L2CC_ACR_EXCC;
}

void l2cc_set_non_exclusive(void)
{
	assert(!l2cc_is_enabled());
	cp15_cache_set_non_exclusive();
	L2CC->L2CC_ACR &= ~L2CC_ACR_EXCC;
}

void l2cc_set_tag_ram_latency(const struct _l2cc_ram_latency *latency)
{
	assert(!l2cc_is_enabled());

	L2CC->L2CC_TRCR = L2CC_TRCR_TSETLAT(latency->setup) |
	                  L2CC_TRCR_TRDLAT(latency->read) |
	                  L2CC_TRCR_TWRLAT(latency->write);
};

void l2cc_set_data_ram_latency(const struct _l2cc_ram_latency *latency)
{
	assert(!l2cc_is_enabled());

	L2CC->L2CC_DRCR = L2CC_DRCR_DSETLAT(latency->setup) |
	                  L2CC_DRCR_DRDLAT(latency->read) |
	                  L2CC_DRCR_DWRLAT(latency->write);
}

void l2cc_set_config(const struct _l2cc_config* cfg)
{
	assert(cfg->offset <= 7 ||
	       cfg->offset == 15 ||
	       cfg->offset == 23 ||
	       cfg->offset == 31);
	assert(!l2cc_is_enabled());

	L2CC->L2CC_ACR = (cfg->high_prior_so ? L2CC_ACR_HPSO : 0) |
	                 (cfg->store_buff_dev_limit ? L2CC_ACR_SBDLE : 0) |
	                 (cfg->shared_attr_invalidate ? L2CC_ACR_SAIE : 0) |
	                 (cfg->evt_mon_bus ? L2CC_ACR_EMBEN : 0) |
	                 (cfg->parity ? L2CC_ACR_PEN : 0) |
	                 (cfg->shared_attr_override ? L2CC_ACR_SAOEN : 0) |
	                 L2CC_ACR_FWA(cfg->force_write_alloc) |
	                 (cfg->cache_replacement ? L2CC_ACR_CRPOL : 0) |
	                 (cfg->non_sec_lockdown ? L2CC_ACR_NSLEN : 0) |
	                 (cfg->it_acces_non_sec ? L2CC_ACR_NSIAC : 0) |
	                 (cfg->data_prefetch ? L2CC_ACR_DPEN : 0) |
	                 (cfg->instruct_prefetch ? L2CC_ACR_IPEN : 0);

	L2CC->L2CC_DCR = (cfg->no_cache_linefill ? L2CC_DCR_DCL : 0) |
	                 (cfg->no_write_back ? L2CC_DCR_DWB : 0);

	L2CC->L2CC_PCR = L2CC_PCR_OFFSET(cfg->offset) |
	                 (cfg->exclusive_seq_same_id ? L2CC_PCR_NSIDEN : 0) |
	                 (cfg->incr_double_linefill ? L2CC_PCR_IDLEN : 0) |
	                 (cfg->prefetch_drop ? L2CC_PCR_PDEN : 0) |
	                 (cfg->DLFWRDIS << 27) |
	                 (cfg->data_prefetch ? L2CC_PCR_DATPEN : 0) |
	                 (cfg->instruct_prefetch ? L2CC_PCR_INSPEN : 0) |
	                 (cfg->double_linefill ? L2CC_PCR_DLEN : 0);

	L2CC->L2CC_POWCR = (cfg->standby_mode ? L2CC_POWCR_STBYEN : 0) |
	                   (cfg->dyn_clock_gating ? L2CC_POWCR_DCKGATEN : 0);
}

void l2cc_data_prefetch_enable(void)
{
	L2CC->L2CC_PCR |= L2CC_PCR_DATPEN;
}

void l2cc_inst_prefetch_enable(void)
{
	L2CC->L2CC_PCR |= L2CC_PCR_INSPEN;
}

void l2cc_enable_event_counter(uint8_t event_counter)
{
	assert(event_counter < 2);

	switch (event_counter) {
	case 0:
		L2CC->L2CC_ECR = L2CC_ECR_EVCEN | L2CC_ECR_EVC0RST;
		break;
	case 1:
		L2CC->L2CC_ECR = L2CC_ECR_EVCEN | L2CC_ECR_EVC1RST;
		break;
	default:
		break;
	}
}

void l2cc_event_config(uint8_t event_counter, uint8_t source, uint8_t it)
{
	assert(event_counter < 2);
	assert(!l2cc_is_enabled());

	switch (event_counter) {
	case 0:
		L2CC->L2CC_ECFGR0 = (source & L2CC_ECFGR0_ESRC_Msk) |
		                    (it & L2CC_ECFGR0_EIGEN_Msk);
		break;
	case 1:
		L2CC->L2CC_ECFGR1 = (source & L2CC_ECFGR1_ESRC_Msk) |
		                    (it & L2CC_ECFGR1_EIGEN_Msk);
		break;
	default:
		break;
	}

}

uint32_t l2cc_event_counter_value(uint8_t event_counter)
{
	assert(event_counter < 2);

	switch (event_counter) {
	case 0:
		return L2CC->L2CC_EVR0;
	case 1:
		return L2CC->L2CC_EVR1;
	default:
		return 0;
	}
}

void l2cc_enable_it(uint32_t sources)
{
	L2CC->L2CC_IMR |= sources;
}

void l2cc_disable_it(uint32_t sources)
{
	L2CC->L2CC_IMR &= ~sources;
}

uint32_t l2cc_it_status(uint32_t sources)
{
	return L2CC->L2CC_RISR & sources;
}

uint32_t l2cc_it_status_mask(uint32_t sources)
{
	return L2CC->L2CC_MISR & sources;
}

void l2cc_it_clear(uint32_t sources)
{
	L2CC->L2CC_ICR |= sources;
}

bool l2cc_get_spniden()
{
	return (L2CC->L2CC_DCR & L2CC_DCR_SPNIDEN) != 0;
}

void l2cc_cache_sync()
{
	while (L2CC->L2CC_CSR & L2CC_CSR_C) {}
	L2CC->L2CC_CSR = L2CC_CSR_C;
	while (L2CC->L2CC_CSR & L2CC_CSR_C) {}
}

void l2cc_invalidate_pal(uint32_t phys_addr)
{
	uint32_t tag, index;

	tag = phys_addr >> (L2CC_OFFSET_BIT + L2CC_INDEX_BIT);
	index = (phys_addr >> L2CC_OFFSET_BIT) & ((1 << L2CC_INDEX_BIT) - 1);
	L2CC->L2CC_IPALR = L2CC_IPALR_TAG(tag) | L2CC_IPALR_IDX(index) | L2CC_IPALR_C;
	while (L2CC->L2CC_IPALR & L2CC_IPALR_C) {}
}

void l2cc_clean_pal(uint32_t phys_addr)
{
	uint32_t tag, index;

	tag = phys_addr >> (L2CC_OFFSET_BIT + L2CC_INDEX_BIT);
	index = (phys_addr >> L2CC_OFFSET_BIT) & ((1 << L2CC_INDEX_BIT) - 1);
	L2CC->L2CC_CPALR = L2CC_CPALR_TAG(tag) | L2CC_CPALR_IDX(index) | L2CC_CPALR_C;
	while (L2CC->L2CC_CPALR & L2CC_CPALR_C) {}
}

void l2cc_clean_invalidate_pal(uint32_t phys_addr)
{
	uint32_t tag, index;

	tag = phys_addr >> (L2CC_OFFSET_BIT + L2CC_INDEX_BIT);
	index = (phys_addr >> L2CC_OFFSET_BIT) & ((1 << L2CC_INDEX_BIT) - 1);
	L2CC->L2CC_CIPALR = L2CC_CIPALR_TAG(tag) | L2CC_CIPALR_IDX(index) | L2CC_CIPALR_C;
	while (L2CC->L2CC_CIPALR & L2CC_CIPALR_C) {}
}

void l2cc_invalidate_way(uint8_t way)
{
	L2CC->L2CC_IWR = way;
	while (L2CC->L2CC_IWR & way) {}
}

void l2cc_clean_way(uint8_t way)
{
	L2CC->L2CC_CWR = way;
	while (L2CC->L2CC_CWR & way) {}
}

void l2cc_clean_invalidate_way(uint8_t way)
{
	L2CC->L2CC_CIWR = way;
	while (L2CC->L2CC_CIWR & way) {}
}

void l2cc_clean_index(uint32_t phys_addr, uint8_t way)
{
	uint32_t index;

	index = (phys_addr >> L2CC_OFFSET_BIT) & ((1 << L2CC_INDEX_BIT) - 1);
	L2CC->L2CC_CIR = L2CC_CIR_IDX(index) | L2CC_CIR_WAY(way) | L2CC_CIR_C;
	while (L2CC->L2CC_CIR & L2CC_CIR_C) {}
}

void l2cc_clean_invalidate_index(uint32_t phys_addr, uint8_t way)
{
	uint32_t index;

	index = (phys_addr >> L2CC_OFFSET_BIT) & ((1 << L2CC_INDEX_BIT) - 1);
	L2CC->L2CC_CIIR = L2CC_CIIR_IDX(index) | L2CC_CIIR_WAY(way) | L2CC_CIIR_C;
	while (L2CC->L2CC_CIIR & L2CC_CIIR_C) {}
}

void l2cc_data_lockdown(uint8_t way)
{
	L2CC->L2CC_DLKR = way;
	while (L2CC->L2CC_CSR & L2CC_CSR_C) {}
}

void l2cc_instruction_lockdown(uint8_t way)
{
	L2CC->L2CC_ILKR = way;
	while (L2CC->L2CC_CSR & L2CC_CSR_C) {}
}

void l2cc_clean(void)
{
	if (l2cc_is_enabled()) {
		// forces the address out past level 2
		l2cc_clean_way(0xFF);
		// Ensures completion of the L2 clean
		l2cc_cache_sync();
	}
}

void l2cc_invalidate(void)
{
	if (l2cc_is_enabled()) {
		// forces the address out past level 2
		l2cc_invalidate_way(0xFF);
		// Ensures completion of the L2 inval
		l2cc_cache_sync();
	}
}

void l2cc_clean_invalidate(void)
{
	if (l2cc_is_enabled()) {
		/* forces the address out past level 2 */
		l2cc_clean_invalidate_way(0xFF);
		/* Ensures completion of the L2 inval */
		l2cc_cache_sync();
	}
}

void l2cc_invalidate_region(uint32_t start, uint32_t end)
{
	assert(start < end);
	uint32_t current = start & ~0x1f;
	if (l2cc_is_enabled()) {
		while (current <= end) {
			l2cc_invalidate_pal(current);
			current += 32;
		}
		l2cc_invalidate_pal(end);
	}
}

void l2cc_clean_region(uint32_t start, uint32_t end)
{
	assert(start < end);
	uint32_t current = start & ~0x1f;
	if (l2cc_is_enabled()) {
		while (current <= end) {
			l2cc_clean_pal(current);
			current += 32;
		}
		l2cc_clean_pal(end);
	}
}

void l2cc_configure(const struct _l2cc_config* cfg)
{
	assert(!l2cc_is_enabled());

	l2cc_event_config(0, L2CC_ECFGR0_ESRC_SRC_DRHIT,
	                  L2CC_ECFGR0_EIGEN_INT_DIS);
	l2cc_event_config(1, L2CC_ECFGR0_ESRC_SRC_DWHIT,
	                  L2CC_ECFGR0_EIGEN_INT_DIS);
	l2cc_enable_event_counter(0);
	l2cc_enable_event_counter(1);

	/* Set configuration */
	l2cc_set_config(cfg);

	/* Enable Prefetch */
	l2cc_inst_prefetch_enable();
	l2cc_data_prefetch_enable();

	/* Invalidate whole L2CC */
	l2cc_invalidate_way(0xFF);

	/* Disable all L2CC Interrupt */
	l2cc_disable_it(0x1FF);

	/* Clear all L2CC Interrupt */
	l2cc_it_clear(0xFF);

	/* Set exclusive mode */
	l2cc_set_exclusive();

	/* Enable L2CC */
	l2cc_enable();
}
