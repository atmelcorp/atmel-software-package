/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
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
 * Implementation of Secure Fuse Controller (SFC).
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "compiler.h"

#include "peripherals/sfc.h"
#include "peripherals/pmc.h"

#include <assert.h>

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

uint32_t sfc_get_errors(void)
{
	uint32_t status = SFC->SFC_SR;
	uint32_t err = 0;

#ifdef SFC_SR_LCHECK
	if (status & SFC_SR_LCHECK)
		err |= SFC_ERR_LCHECK;
#endif

	if (status & SFC_SR_APLE)
		err |= SFC_ERR_APLE;

	if (status & SFC_SR_ACE)
		err |= SFC_ERR_ACE;

	return err;
}

uint32_t sfc_read(uint32_t index)
{
	assert(index < ARRAY_SIZE(SFC->SFC_DR));
	return SFC->SFC_DR[index];
}

void sfc_enable(void)
{
	pmc_enable_peripheral(ID_SFC);
}

void sfc_disable(void)
{
	pmc_disable_peripheral(ID_SFC);
}

bool sfc_write(uint32_t index, uint32_t data)
{
	uint32_t status;

	assert(index < ARRAY_SIZE(SFC->SFC_DR));

	/* write key */
	SFC->SFC_KR = SFC_KR_KEY(0xFB);

	/* write data to be fused */
	SFC->SFC_DR[index] = data;

	/* wait for completion */
	do {
		status = SFC->SFC_SR;
	} while ((status & SFC_SR_PGMC) == 0);

	/* check for failure */
	return (status & SFC_SR_PGMF) == 0;
}

void sfc_mask_data_registers(void)
{
	SFC->SFC_MR |= SFC_MR_MSK;
}

bool sfc_are_data_registers_masked(void)
{
	return (SFC->SFC_MR & SFC_MR_MSK) != 0;
}
