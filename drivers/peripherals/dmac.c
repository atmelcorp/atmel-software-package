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
 * Implementation of DMA controller (DMAC).
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "peripherals/dmac.h"

#include <assert.h>
#include "compiler.h"

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

Dmac *dmac_get_instance(uint32_t index)
{
	assert(index < DMAC_CONTROLLERS);
	if (index == 0)
		return DMAC0;
	else if (index == 1)
		return DMAC1;
	else
		return NULL;
}

uint32_t dmac_get_periph_id(Dmac *dmac)
{
	assert(dmac == DMAC0 || dmac == DMAC1);
	if (dmac == DMAC0)
		return ID_DMAC0;
	else if (dmac == DMAC1)
		return ID_DMAC1;
	else
		return ID_PERIPH_COUNT;
}

uint32_t dmac_get_config(Dmac *dmac)
{
	assert(dmac == DMAC0 || dmac == DMAC1);

	return dmac->DMAC_GCFG;
}

void dmac_enable(Dmac *dmac)
{
	assert(dmac == DMAC0 || dmac == DMAC1);

	dmac->DMAC_EN = DMAC_EN_ENABLE;
}

void dmac_disable(Dmac *dmac)
{
	assert(dmac == DMAC0 || dmac == DMAC1);

	dmac->DMAC_EN = 0 ;
}


void dmac_enable_global_it(Dmac *dmac, uint32_t int_mask)
{
	assert(dmac == DMAC0 || dmac == DMAC1);

	dmac->DMAC_EBCIER |= int_mask;
}

void dmac_disable_global_it(Dmac *dmac, uint32_t int_mask)
{
	assert(dmac == DMAC0 || dmac == DMAC1);

	dmac->DMAC_EBCIDR |= int_mask;
}

uint32_t dmac_get_global_it_mask(Dmac *dmac)
{
	assert(dmac == DMAC0 || dmac == DMAC1);

	return dmac->DMAC_EBCIMR;
}

uint32_t dmac_get_global_isr(Dmac *dmac)
{
	assert(dmac == DMAC0 || dmac == DMAC1);

	return dmac->DMAC_EBCISR;
}

uint32_t dmac_get_masked_global_isr(Dmac *dmac)
{
	assert(dmac == DMAC0 || dmac == DMAC1);

	uint32_t mask = dmac->DMAC_EBCIMR;

	return dmac->DMAC_EBCISR & mask;
}

void dmac_enable_channel(Dmac *dmac, uint8_t channel)
{
	assert(dmac == DMAC0 || dmac == DMAC1);
	assert(channel < DMAC_CHANNELS);

	dmac->DMAC_CHER = DMAC_CHER_ENA0 << channel;
}

void dmac_enable_channels(Dmac *dmac, uint8_t channel_mask)
{
	assert(dmac == DMAC0 || dmac == DMAC1);

	dmac->DMAC_CHER = channel_mask;
}

void dmac_disable_channel(Dmac *dmac, uint8_t channel)
{
	assert(dmac == DMAC0 || dmac == DMAC1);
	assert(channel < DMAC_CHANNELS);

	dmac->DMAC_CHDR = DMAC_CHDR_DIS0 << channel;
}

void dmac_disable_channels(Dmac *dmac, uint8_t channel_mask)
{
	assert(dmac == DMAC0 || dmac == DMAC1);

	dmac->DMAC_CHDR = channel_mask;
}

void dmac_resume_channel(Dmac *dmac, uint8_t channel)
{
	assert(dmac == DMAC0 || dmac == DMAC1);
	assert(channel < DMAC_CHANNELS);
	dmac->DMAC_CHER = DMAC_CHER_KEEP0 << channel;
}

uint32_t dmac_get_channel_status(Dmac *dmac)
{
	assert(dmac == DMAC0 || dmac == DMAC1);

	return dmac->DMAC_CHSR;
}

void dmac_software_single_request(Dmac *dmac, uint8_t channel)
{
	assert(dmac == DMAC0 || dmac == DMAC1);
	assert(channel < DMAC_CHANNELS);

	dmac->DMAC_SREQ |= ((DMAC_SREQ_SSREQ0 | DMAC_SREQ_DSREQ0) << (channel << 1) );
}

void dmac_software_chunk_transfer_request(Dmac *dmac, uint8_t channel)
{
	assert(dmac == DMAC0 || dmac == DMAC1);
	assert(channel < DMAC_CHANNELS);
	dmac->DMAC_CREQ |= ((DMAC_CREQ_SCREQ0 | DMAC_CREQ_DCREQ0) << (channel << 1));
}

void dmac_set_src_addr(Dmac *dmac, uint8_t channel, void *addr)
{
	assert(dmac == DMAC0 || dmac == DMAC1);
	assert(channel < DMAC_CHANNELS);

	dmac->DMAC_CH_NUM[channel].DMAC_SADDR = (uint32_t)addr;
}

void dmac_set_dest_addr(Dmac *dmac, uint8_t channel, void *addr)
{
	assert(dmac == DMAC0 || dmac == DMAC1);
	assert(channel < DMAC_CHANNELS);

	dmac->DMAC_CH_NUM[channel].DMAC_DADDR = (uint32_t)addr;
}

uint32_t dmac_get_channel_src_addr(Dmac *dmac, uint8_t channel)
{
	assert(dmac == DMAC0 || dmac == DMAC1);
	assert(channel < DMAC_CHANNELS);

	return dmac->DMAC_CH_NUM[channel].DMAC_SADDR;
}

uint32_t dmac_get_channel_dest_addr(Dmac *dmac, uint8_t channel)
{
	assert(dmac == DMAC0 || dmac == DMAC1);
	assert(channel < DMAC_CHANNELS);

	return dmac->DMAC_CH_NUM[channel].DMAC_DADDR;
}

void dmac_set_descriptor_addr(Dmac *dmac, uint8_t channel, void *addr,
		uint32_t ndaif)
{
	assert(dmac == DMAC0 || dmac == DMAC1);
	assert(channel < DMAC_CHANNELS);

	dmac->DMAC_CH_NUM[channel].DMAC_DSCR = (((uint32_t)addr) & 0xFFFFFFFC) | ndaif;
}

void dmac_set_control_a(Dmac *dmac, uint8_t channel,
		uint32_t config)
{
	assert(dmac == DMAC0 || dmac == DMAC1);
	assert(channel < DMAC_CHANNELS);
	dmac->DMAC_CH_NUM[channel].DMAC_CTRLA = config;
}

void dmac_set_control_b(Dmac *dmac, uint8_t channel,
		uint32_t config)
{
	assert(dmac == DMAC0 || dmac == DMAC1);
	assert(channel < DMAC_CHANNELS);

	dmac->DMAC_CH_NUM[channel].DMAC_CTRLB = config;
}

void dmac_set_channel_config(Dmac *dmac, uint8_t channel, uint32_t config)
{
	assert(dmac == DMAC0 || dmac == DMAC1);
	assert(channel < DMAC_CHANNELS);

	dmac->DMAC_CH_NUM[channel].DMAC_CFG = config;
}

bool is_dmac_auto_transfer(Dmac *dmac, uint8_t channel)
{
	assert(dmac == DMAC0 || dmac == DMAC1);
	assert(channel < DMAC_CHANNELS);
	return (dmac->DMAC_CH_NUM[channel].DMAC_CTRLB & DMAC_CTRLB_AUTO_ENABLE);
}

void dmac_auto_clear(Dmac *dmac, uint8_t channel)
{
	assert(dmac == DMAC0 || dmac == DMAC1);
	assert(channel < DMAC_CHANNELS);
	dmac->DMAC_CH_NUM[channel].DMAC_CTRLB &= ~DMAC_CTRLB_AUTO;
}

uint32_t dmac_get_channel_config(Dmac *dmac, uint8_t channel)
{
	assert(dmac == DMAC0 || dmac == DMAC1);
	assert(channel < DMAC_CHANNELS);

	return dmac->DMAC_CH_NUM[channel].DMAC_CFG;
}

void dmac_set_src_pip(Dmac *dmac, uint8_t channel, uint32_t pip)
{
	assert(dmac == DMAC0 || dmac == DMAC1);
	assert(channel < DMAC_CHANNELS);

	dmac->DMAC_CH_NUM[channel].DMAC_SPIP = pip;
}

void dmac_set_des_pip(Dmac *dmac, uint8_t channel, uint32_t pip)
{
	assert(dmac == DMAC0 || dmac == DMAC1);
	assert(channel < DMAC_CHANNELS);

	dmac->DMAC_CH_NUM[channel].DMAC_DPIP = pip;
}
