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

#include "chip.h"

#include "peripherals/matrix.h"

#include "mm/cache.h"
#include "mm/l1cache.h"

#include <assert.h>

#if defined(CONFIG_SOC_SAMA5D2) || defined(CONFIG_SOC_SAMA5D4)
void matrix_configure_master(Matrix* mtx, uint8_t id, uint32_t val)
{
	mtx->MATRIX_MCFG[id] = val;
}

void matrix_configure_slave(Matrix* mtx, uint8_t id, uint32_t val)
{
	mtx->MATRIX_SCFG[id] = val;
}

void matrix_master_priority_for_slave(Matrix* mtx,
	uint8_t s_id, uint8_t m_id, uint8_t priority)
{
	if (m_id <= 7) {
		m_id <<= 2;
		mtx->MATRIX_PR[s_id].MATRIX_PRAS = (mtx->MATRIX_PR[s_id].MATRIX_PRAS &
			(~(MATRIX_PRAS_M0PR_Msk << m_id))) | (priority << m_id);
	} else {
		assert(m_id < 16);
		m_id = (m_id - 8) << 2;
		mtx->MATRIX_PR[s_id].MATRIX_PRBS = (mtx->MATRIX_PR[s_id].MATRIX_PRBS &
			(~(MATRIX_PRAS_M0PR_Msk << m_id))) | (priority << m_id);
	}
}
#endif

void matrix_configure_slave_sec(Matrix* mtx, uint8_t slave_id,
				uint8_t sel_mask, uint8_t read_mask,
				uint8_t write_mask)
{
#ifdef CONFIG_HAVE_SECURE_MATRIX
	mtx->MATRIX_SSR[slave_id] = sel_mask | (read_mask << 8) |
		(write_mask << 16);
#endif
}

void matrix_set_slave_split_addr(Matrix* mtx, uint8_t slave_id,
				 uint8_t area_size, uint8_t mask)
{
#ifdef CONFIG_HAVE_SECURE_MATRIX
	uint8_t i = mask, j = 0;
	uint32_t value = 0;
	for (i = 1; (i <= mask) && (j < 32); i <<= 1, j += 4) {
		if (i & mask)
			value |= area_size << j;
	}
	mtx->MATRIX_SASSR[slave_id] = value;
#endif
}

void matrix_set_slave_region_size(Matrix* mtx, uint8_t slave_id,
				  uint8_t area_size, uint8_t mask)
{
#ifdef CONFIG_HAVE_SECURE_MATRIX
	assert(slave_id != 0);
	uint8_t i = mask, j = 0;
	uint32_t value = 0;
	for (i = 1; (i <= mask) && (j < 32 ); i <<= 1, j += 4) {
		if (i & mask)
			value |= area_size << j;
	}
	mtx->MATRIX_SRTSR[slave_id] = value;
#endif
}

bool matrix_is_peripheral_secured(Matrix* mtx, uint32_t periph_id)
{
#ifdef CONFIG_HAVE_SECURE_MATRIX
	if (mtx->MATRIX_SPSELR[periph_id / 32] & (1 << (periph_id % 32))) {
		return false;
	} else
#endif
	{
		return true;
	}
}

void matrix_remove_write_protection(Matrix* mtx)
{
	mtx->MATRIX_WPMR = MATRIX_WPMR_WPKEY_PASSWD;
}

/**
 * \brief Changes the mapping of the chip so that the remap area mirrors the
 * internal ROM or the EBI CS0.
 */
void matrix_remap_rom(void)
{
	volatile int i;
#if defined(CONFIG_SOC_SAM9XX5) || defined(CONFIG_SOC_SAM9X60)
	MATRIX->MATRIX_MRCR = 0;
#elif defined(CONFIG_SOC_SAMA5D3)
	MATRIX->MATRIX_MRCR = 0;
	AXIMX->AXIMX_REMAP = 0;
#elif defined(CONFIG_SOC_SAMA5D2) || defined(CONFIG_SOC_SAMA5D4)
	AXIMX->AXIMX_REMAP = 0;
#endif
	for (i = 200; i--; ) {}
	icache_invalidate();

	/* If caching is enabled, invalidate the remap area */
	cache_invalidate_region((void*)0, IRAM_SIZE);
}

/**
 * \brief Changes the mapping of the chip so that the remap area mirrors the
 * internal RAM.
 */

void matrix_remap_ram(void)
{
	volatile int i;
#if defined(CONFIG_SOC_SAM9XX5) || defined(CONFIG_SOC_SAM9X60)
	MATRIX->MATRIX_MRCR = MATRIX_MRCR_RCB0 | MATRIX_MRCR_RCB1;
#elif defined(CONFIG_SOC_SAMA5D3)
	MATRIX->MATRIX_MRCR = MATRIX_MRCR_RCB0;
	AXIMX->AXIMX_REMAP = AXIMX_REMAP_REMAP0;
#elif defined(CONFIG_SOC_SAMA5D2) || defined(CONFIG_SOC_SAMA5D4)
	AXIMX->AXIMX_REMAP = AXIMX_REMAP_REMAP0;
#endif
	for (i = 200; i--; ) {}
	icache_invalidate();

	/* If caching is enabled, clean the SRAM region and invalidate remap
	 * area */
	cache_clean_region((void*)IRAM_ADDR, IRAM_SIZE);
	cache_invalidate_region((void*)0, IRAM_SIZE);
}

#if defined(CONFIG_SOC_SAMA5D2) || defined(CONFIG_SOC_SAMA5D4)
void matrix_set_default_config(void)
{
	uint32_t m_id;
	uint32_t s_id;

	/* Disable write protection */
	matrix_remove_write_protection(MATRIX0);

	for (m_id = 0; m_id < H64MX_MASTER_COUNT; m_id++)
		matrix_configure_master(MATRIX0, m_id, MATRIX_MCFG_ULBT_16_BEAT);

	for (s_id = 0; s_id < H64MX_SLAVE_COUNT; s_id++) {
		matrix_configure_slave(MATRIX0, s_id, MATRIX_SCFG_FIXED_DEFMSTR(0) |
			MATRIX_SCFG_DEFMSTR_TYPE_NONE | MATRIX_SCFG_SLOT_CYCLE_Msk);
		for (m_id = 0; m_id < H64MX_MASTER_COUNT; m_id++)
			matrix_master_priority_for_slave(MATRIX0, s_id, m_id, 0);
		matrix_configure_slave_sec(MATRIX0, s_id, 0xFF, 0xFF, 0xFF);
	}

	/* Disable write protection */
	matrix_remove_write_protection(MATRIX1);

	for (m_id = 0; m_id <= H32MX_MASTER_COUNT; m_id++)
		matrix_configure_master(MATRIX1, m_id, MATRIX_MCFG_ULBT_16_BEAT);

	for (s_id = 0; s_id <= H32MX_SLAVE_COUNT; s_id++) {
		matrix_configure_slave(MATRIX1, s_id, MATRIX_SCFG_FIXED_DEFMSTR(0) |
			MATRIX_SCFG_DEFMSTR_TYPE_NONE | MATRIX_SCFG_SLOT_CYCLE_Msk);
		for (m_id = 0; m_id <= H32MX_MASTER_COUNT; m_id++)
			matrix_master_priority_for_slave(MATRIX1, s_id, m_id, 0);
		matrix_configure_slave_sec(MATRIX1, s_id, 0xFF, 0xFF, 0xFF);
	}
}
#endif

