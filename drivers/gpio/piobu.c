/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2017, Atmel Corporation
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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <errno.h>
#include <stdbool.h>

#include "board.h"
#include "gpio/piobu.h"

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

int piobu_configure(const struct _pin* pin_list, int size)
{
	int i, j;

	for (i = 0; i < size; i++) {
		const struct _pin* pin = &pin_list[i];
		uint32_t piobu = 0;

		switch (pin->type) {
		case PIO_INPUT:
			break;
		case PIO_OUTPUT_1:
			piobu |= SECUMOD_PIOBU_PIO_SOD;
			/* fall-through */
		case PIO_OUTPUT_0:
			piobu |= SECUMOD_PIOBU_OUTPUT_ENABLED_OUTPUT;
			break;
		default:
			return -EINVAL;
		}

		switch (pin->attribute) {
		case PIO_DEFAULT:
			break;
		case PIO_PULLUP:
			piobu |= SECUMOD_PIOBU_PULLUP_PULL_UP;
			break;
		case PIO_PULLDOWN:
			piobu |= SECUMOD_PIOBU_PULLUP_PULL_DOWN;
			break;
		default:
			return -EINVAL;
		}

		for (j = 0; j < ARRAY_SIZE(SECUMOD->SECUMOD_PIOBU); j++) {
			if (pin->mask & (1u << j))
				SECUMOD->SECUMOD_PIOBU[j] = piobu;
		}
	}

	return 0;
}

uint32_t piobu_get(const struct _pin* pin)
{
	uint32_t piobu = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(SECUMOD->SECUMOD_PIOBU); i++) {
		if (pin->mask & (1u << i)) {
			if (SECUMOD->SECUMOD_PIOBU[i] & SECUMOD_PIOBU_PIO_PDS)
				piobu |= (1u << i);
		}
	}

	return piobu;
}

void piobu_set(const struct _pin* pin)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(SECUMOD->SECUMOD_PIOBU); i++) {
		if (pin->mask & (1u << i))
			SECUMOD->SECUMOD_PIOBU[i] |= SECUMOD_PIOBU_PIO_SOD;
	}
}

void piobu_clear(const struct _pin* pin)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(SECUMOD->SECUMOD_PIOBU); i++) {
		if (pin->mask & (1u << i))
			SECUMOD->SECUMOD_PIOBU[i] &= ~SECUMOD_PIOBU_PIO_SOD;
	}
}
