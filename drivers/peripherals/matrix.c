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

#include "misc/cache.h"

#include <assert.h>

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

uint8_t matrix_is_peripheral_secured(Matrix* mtx, uint32_t periph_id)
{
#ifdef CONFIG_HAVE_SECURE_MATRIX
	if (mtx->MATRIX_SPSELR[periph_id / 32] & (1 << (periph_id % 32))) {
		return 0;
	} else
#endif
	{
		return 1;
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
#ifdef CONFIG_SOC_SAMA5D3
	MATRIX->MATRIX_MRCR = MATRIX_MRCR_RCB0;
#endif
	AXIMX->AXIMX_REMAP = 0;
	for (i = 200; i--; ) {}
	cp15_icache_invalidate();

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
#ifdef CONFIG_SOC_SAMA5D3
	MATRIX->MATRIX_MRCR = MATRIX_MRCR_RCB0;
#endif
	AXIMX->AXIMX_REMAP = AXIMX_REMAP_REMAP0;
	for (i = 200; i--; ) {}
	cp15_icache_invalidate();

	/* If caching is enabled, clean the SRAM region and invalidate remap
	 * area */
	cache_clean_region((void*)IRAM_ADDR, IRAM_SIZE);
	cache_invalidate_region((void*)0, IRAM_SIZE);
}
