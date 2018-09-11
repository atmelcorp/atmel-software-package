/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2018, Microchip Technology
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

#ifndef SDRAMC_HEADER_
#define SDRAMC_HEADER_

#include <stdbool.h>
#include <stdint.h>

struct _sdramc_desc {
	bool is_lpsdr;

	uint8_t nb_columns;
	uint8_t nb_rows;
	uint8_t nb_banks;
	uint8_t data_bus_width;
	uint8_t cas_latency;
	uint8_t shift_sampling;

	struct {
		uint8_t tmrd;  /**< Load Mode Register Command to Activate or Refresh Command */
		uint8_t twr;   /**< Write Recovery Delay */
		uint8_t trc;   /**< Row Cycle Delay */
		uint8_t trfc;  /**< Row Refresh Cycle */
		uint8_t trp;   /**< Row Precharge Delay */
		uint8_t trcd;  /**< Row to Column Delay */
		uint8_t tras;  /**< Active to Precharge Delay */
		uint8_t txsr;  /**< Exit Self-Refresh to Active Delay */
	} timings;

	uint32_t refresh_window; /* in ms */
	uint32_t refresh_cycles;
};

extern void sdramc_configure(const struct _sdramc_desc *desc);

#endif /* SDRAMC_HEADER_ */
