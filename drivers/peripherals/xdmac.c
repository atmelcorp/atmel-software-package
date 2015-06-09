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
 * Implementation of xDMA controller (XDMAC).
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "peripherals/xdmac.h"

#include <stdint.h>
#include <assert.h>

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

uint32_t xdmac_get_type(Xdmac *xdmac)
{
	assert(xdmac);
	return xdmac->XDMAC_GTYPE;
}

uint32_t xdmac_get_config(Xdmac *xdmac)
{
	assert(xdmac);
	return xdmac->XDMAC_GCFG;
}

uint32_t xdmac_get_arbiter(Xdmac *xdmac)
{
	assert(xdmac);
	return xdmac->XDMAC_GWAC;
}

void xdmac_enable_global_it(Xdmac *xdmac, uint32_t dwInteruptMask)
{
	assert(xdmac);
	xdmac->XDMAC_GIE = dwInteruptMask;
}

void xdmac_disable_global_it(Xdmac *xdmac, uint32_t dwInteruptMask)
{
	assert(xdmac);
	xdmac->XDMAC_GID = dwInteruptMask;
}

uint32_t xdmaC_get_global_it_mask(Xdmac *xdmac)
{
	assert(xdmac);
	return xdmac->XDMAC_GIM;
}

uint32_t xdmac_get_global_isr(Xdmac *xdmac)
{
	assert(xdmac);
	return xdmac->XDMAC_GIS;
}

uint32_t xdmac_get_masked_global_isr(Xdmac *xdmac)
{
	assert(xdmac);
	return xdmac->XDMAC_GIS & xdmac->XDMAC_GIM;
}

void xdmac_enable_channel(Xdmac *xdmac, uint8_t channel)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	xdmac->XDMAC_GE |= XDMAC_GE_EN0 << channel;
}

void xdmac_enable_channels(Xdmac *xdmac, uint8_t bmChannels)
{
	assert(xdmac);
	xdmac->XDMAC_GE = bmChannels;
}

void xdmac_disable_channel(Xdmac *xdmac, uint8_t channel)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	xdmac->XDMAC_GD |= XDMAC_GD_DI0 << channel;
}

void xdmac_disable_channels(Xdmac *xdmac, uint8_t bmChannels)
{
	assert(xdmac);
	xdmac->XDMAC_GD = bmChannels;
}

uint32_t xdmac_get_global_channel_status(Xdmac *xdmac)
{
	assert(xdmac);
	return xdmac->XDMAC_GS;
}

void xdmac_suspend_read_channel(Xdmac *xdmac, uint8_t channel)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	xdmac->XDMAC_GRS |= XDMAC_GRS_RS0 << channel;
}

void xdmac_suspend_write_channel(Xdmac *xdmac, uint8_t channel)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	xdmac->XDMAC_GWS |= XDMAC_GWS_WS0 << channel;
}

void xdmac_suspend_read_write_channel(Xdmac *xdmac, uint8_t channel)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	xdmac->XDMAC_GRWS |= XDMAC_GRWS_RWS0 << channel;
}

void xdmac_resume_read_write_channel(Xdmac *xdmac, uint8_t channel)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	xdmac->XDMAC_GRWR |= XDMAC_GRWR_RWR0 << channel;
}

void xdmac_software_transfer_request(Xdmac *xdmac, uint8_t channel)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	xdmac->XDMAC_GSWR |= (XDMAC_GSWR_SWREQ0 << channel);
}

uint32_t xdmac_get_software_transfer_status(Xdmac *xdmac)
{
	assert(xdmac);
	return xdmac->XDMAC_GSWS;
}

void xdmac_software_flush_request(Xdmac *xdmac, uint8_t channel)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	xdmac->XDMAC_GSWF |= XDMAC_GSWF_SWF0 << channel;
}

void xdmac_enable_channel_it(Xdmac *xdmac, uint8_t channel, uint32_t dwInteruptMask)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	xdmac->XDMAC_CHID[channel].XDMAC_CIE = dwInteruptMask;
}

void xdmac_disable_channel_it(Xdmac *xdmac, uint8_t channel, uint32_t dwInteruptMask)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	xdmac->XDMAC_CHID[channel].XDMAC_CID = dwInteruptMask;
}

uint32_t xdmac_get_channel_it_mask(Xdmac *xdmac, uint8_t channel)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	return xdmac->XDMAC_CHID[channel].XDMAC_CIM;
}

uint32_t xdmac_get_channel_isr(Xdmac *xdmac, uint8_t channel)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	return xdmac->XDMAC_CHID[channel].XDMAC_CIS;
}

uint32_t xdmac_get_masked_channel_isr(Xdmac *xdmac, uint8_t channel)
{
	uint32_t status;
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	status = xdmac->XDMAC_CHID[channel].XDMAC_CIS;
	status &= xdmac->XDMAC_CHID[channel].XDMAC_CIM;
	return status;
}

void xdmac_set_src_addr(Xdmac *xdmac, uint8_t channel, uint32_t addr)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	xdmac->XDMAC_CHID[channel].XDMAC_CSA = addr;
}

void xdmac_set_dest_addr(Xdmac *xdmac, uint8_t channel, uint32_t addr)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	xdmac->XDMAC_CHID[channel].XDMAC_CDA = addr;
}

void xdmac_set_descriptor_addr(Xdmac *xdmac, uint8_t channel, uint32_t addr,
			uint32_t ndaif)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	xdmac->XDMAC_CHID[channel].XDMAC_CNDA = (addr & 0xFFFFFFFC) | ndaif;
}

void xdmac_set_descriptor_control(Xdmac *xdmac, uint8_t channel, uint32_t config)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	xdmac->XDMAC_CHID[channel].XDMAC_CNDC = config;
}

void xdmac_set_microblock_control(Xdmac *xdmac, uint8_t channel, uint32_t ublen)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	xdmac->XDMAC_CHID[channel].XDMAC_CUBC = ublen;
}

void xdmac_set_block_control(Xdmac *xdmac, uint8_t channel, uint32_t blen)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	xdmac->XDMAC_CHID[channel].XDMAC_CBC = blen;
}

void xdmac_set_channel_config(Xdmac *xdmac, uint8_t channel, uint32_t config)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	xdmac->XDMAC_CHID[channel].XDMAC_CC = config;
}

uint32_t xdmac_get_channel_config(Xdmac *xdmac, uint8_t channel)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	return xdmac->XDMAC_CHID[channel].XDMAC_CC;
}

void xdmac_set_data_stride_mem_pattern(Xdmac *xdmac, uint8_t channel,
			       uint32_t dds_msp)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	xdmac->XDMAC_CHID[channel].XDMAC_CDS_MSP = dds_msp;
}

void xdmac_set_src_microblock_stride(Xdmac *xdmac, uint8_t channel, uint32_t subs)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	xdmac->XDMAC_CHID[channel].XDMAC_CSUS = subs;
}

void xdmac_set_dest_microblock_stride(Xdmac *xdmac, uint8_t channel,
				     uint32_t dubs)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	xdmac->XDMAC_CHID[channel].XDMAC_CDUS = dubs;
}

uint32_t xdmac_get_channel_dest_addr(Xdmac *xdmac, uint8_t channel)
{
	assert(xdmac);
	assert(channel < XDMAC_CHANNEL_NUM);
	return xdmac->XDMAC_CHID[channel].XDMAC_CDA;
}
