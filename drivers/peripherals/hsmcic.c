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

/** \file
 *
 * Implementation of High Speed MultiMedia Card Interface (HSMCI) controller.
 */

/*---------------------------------------------------------------------------
 *         Headers
 *---------------------------------------------------------------------------*/

#include "chip.h"
#include "peripherals/hsmcic.h"

/*---------------------------------------------------------------------------
 *         Exported functions
 *---------------------------------------------------------------------------*/

void hsmci_enable(Hsmci * regs)
{
	regs->HSMCI_CR = HSMCI_CR_MCIEN;
}

void hsmci_disable(Hsmci * regs)
{
	regs->HSMCI_CR = HSMCI_CR_MCIDIS;
}

void hsmci_reset(Hsmci * regs, bool backup)
{
	if (backup) {
		uint32_t mr = regs->HSMCI_MR;
		uint32_t dtor = regs->HSMCI_DTOR;
		uint32_t sdcr = regs->HSMCI_SDCR;
		uint32_t cstor = regs->HSMCI_CSTOR;
		uint32_t dma = regs->HSMCI_DMA;
		uint32_t cfg = regs->HSMCI_CFG;

		regs->HSMCI_CR = HSMCI_CR_SWRST;

		regs->HSMCI_MR = mr;
		regs->HSMCI_DTOR = dtor;
		regs->HSMCI_SDCR = sdcr;
		regs->HSMCI_CSTOR = cstor;
		regs->HSMCI_DMA = dma;
		regs->HSMCI_CFG = cfg;
	} else {
		regs->HSMCI_CR = HSMCI_CR_SWRST;
	}
}

void hsmci_select(Hsmci * regs, uint8_t bSlot, uint8_t bBusWidth)
{
	uint32_t dwSdcr;
	dwSdcr = HSMCI_SDCR_SDCSEL_Msk & bSlot;
	switch (bBusWidth) {
	case 1:
		regs->HSMCI_SDCR = dwSdcr | HSMCI_SDCR_SDCBUS_1;
		break;
	case 4:
		regs->HSMCI_SDCR = dwSdcr | HSMCI_SDCR_SDCBUS_4;
		break;
	case 8:
		regs->HSMCI_SDCR = dwSdcr | HSMCI_SDCR_SDCBUS_8;
		break;
	}
}

void hsmci_set_slot(Hsmci * regs, uint8_t bSlot)
{
	uint32_t dwSdcr = regs->HSMCI_SDCR & ~HSMCI_SDCR_SDCSEL_Msk;
	regs->HSMCI_SDCR = dwSdcr | (HSMCI_SDCR_SDCSEL_Msk & bSlot);
}

void hsmci_set_bus_width(Hsmci * regs, uint8_t bBusWidth)
{
	uint32_t dwSdcr = regs->HSMCI_SDCR & ~HSMCI_SDCR_SDCBUS_Msk;
	switch (bBusWidth) {
	case 1:
		regs->HSMCI_SDCR = dwSdcr | HSMCI_SDCR_SDCBUS_1;
		break;
	case 4:
		regs->HSMCI_SDCR = dwSdcr | HSMCI_SDCR_SDCBUS_4;
		break;
	case 8:
		regs->HSMCI_SDCR = dwSdcr | HSMCI_SDCR_SDCBUS_8;
		break;
	}
}

uint8_t hsmci_get_bus_width(const Hsmci * regs)
{
	switch (regs->HSMCI_SDCR & HSMCI_SDCR_SDCBUS_Msk) {
	case HSMCI_SDCR_SDCBUS_1:
		return 1;
	case HSMCI_SDCR_SDCBUS_4:
		return 4;
	case HSMCI_SDCR_SDCBUS_8:
		return 8;
	}
	return 0;
}

void hsmci_cfg_mode(Hsmci * regs, uint32_t dwMode)
{
	regs->HSMCI_MR = dwMode;
}

uint32_t hsmci_get_mode(const Hsmci * regs)
{
	return regs->HSMCI_MR;
}

void hsmci_proof_enable(Hsmci * regs, bool rd_proof, bool wr_proof)
{
	uint32_t mr = regs->HSMCI_MR;
	regs->HSMCI_MR = (mr & ~HSMCI_MR_WRPROOF & ~HSMCI_MR_RDPROOF)
		| (rd_proof ? HSMCI_MR_RDPROOF : 0)
		| (wr_proof ? HSMCI_MR_WRPROOF : 0);
}

void hsmci_set_pad_pattern(Hsmci * regs, uint8_t bPadv)
{
	if (bPadv) {
		regs->HSMCI_MR |= HSMCI_MR_PADV;
	} else {
		regs->HSMCI_MR &= ~HSMCI_MR_PADV;
	}
}

void hsmci_xfer_bytes(Hsmci * regs, bool xfer_bytes)
{
	if (xfer_bytes) {
		regs->HSMCI_MR |= HSMCI_MR_FBYTE;
	} else {
		regs->HSMCI_MR &= ~HSMCI_MR_FBYTE;
	}
}

bool hsmci_is_xfer_in_bytes(const Hsmci * regs)
{
	return regs->HSMCI_MR & HSMCI_MR_FBYTE ? true : false;
}

void hsmci_set_clock(Hsmci * regs, uint32_t bClkDiv, uint8_t bPwsDiv)
{
	uint32_t mr = regs->HSMCI_MR;
	uint32_t clkdiv, clkodd;
	clkdiv = bClkDiv - 2;
	clkodd = (bClkDiv & 1) ? HSMCI_MR_CLKODD : 0;
	clkdiv = clkdiv >> 1;

	regs->HSMCI_MR = (mr & ~HSMCI_MR_CLKDIV_Msk & ~HSMCI_MR_PWSDIV_Msk)
		| HSMCI_MR_CLKDIV(clkdiv) | HSMCI_MR_PWSDIV(bPwsDiv) | clkodd;
}

void hsmci_enable_it(Hsmci * regs, uint32_t dwSources)
{
	regs->HSMCI_IER = dwSources;
}

void hsmci_disable_it(Hsmci * regs, uint32_t dwSources)
{
	regs->HSMCI_IDR = dwSources;
}

uint32_t hsmci_get_it_mask(const Hsmci * regs)
{
	return regs->HSMCI_IMR;
}

void hsmci_cfg_xfer(Hsmci * regs, uint16_t wBlkLen, uint16_t wCnt)
{
	regs->HSMCI_BLKR = (wBlkLen << 16) | wCnt;
}

void hsmci_set_block_len(Hsmci * regs, uint16_t wBlkSize)
{
	regs->HSMCI_BLKR = wBlkSize << 16;
}

void hsmci_set_block_count(Hsmci * regs, uint16_t wBlkCnt)
{
	regs->HSMCI_BLKR |= wBlkCnt;
}

void hsmci_cfg_compl_timeout(Hsmci * regs, uint32_t dwConfigure)
{
	regs->HSMCI_CSTOR = dwConfigure;
}

void hsmci_cfg_data_timeout(Hsmci * regs, uint32_t dwConfigure)
{
	regs->HSMCI_DTOR = dwConfigure;
}

void hsmci_send_cmd(Hsmci * regs, uint32_t dwCmd, uint32_t dwArg)
{
	regs->HSMCI_ARGR = dwArg;
	regs->HSMCI_CMDR = dwCmd;
}

uint32_t hsmci_get_response(const Hsmci * regs)
{
	return regs->HSMCI_RSPR[0];
}

uint32_t hsmci_read(const Hsmci * regs)
{
	return regs->HSMCI_RDR;
}

void hsmci_read_fifo(const Hsmci * regs, uint8_t * pdwData, uint32_t dwSize)
{
	const volatile uint32_t *pFIFO = (volatile uint32_t *)regs->HSMCI_FIFO;
	register uint32_t c4, c1;

	if (dwSize == 0)
		return;

	c4 = dwSize >> 2;
	c1 = dwSize & 0x3;

	for (; c4; c4--) {
		*pdwData++ = *pFIFO++;
		*pdwData++ = *pFIFO++;
		*pdwData++ = *pFIFO++;
		*pdwData++ = *pFIFO++;
	}
	for (; c1; c1--) {
		*pdwData++ = *pFIFO++;
	}
}

void hsmci_write(Hsmci * regs, uint32_t dwData)
{
	regs->HSMCI_TDR = dwData;
}

void hsmci_write_fifo(Hsmci * regs, const uint8_t * pdwData, uint32_t dwSize)
{
	volatile uint32_t *pFIFO = (volatile uint32_t *)regs->HSMCI_FIFO;
	register uint32_t c4, c1;

	if (dwSize == 0)
		return;

	c4 = dwSize >> 2;
	c1 = dwSize & 0x3;

	for (; c4; c4--) {
		*pFIFO++ = *pdwData++;
		*pFIFO++ = *pdwData++;
		*pFIFO++ = *pdwData++;
		*pFIFO++ = *pdwData++;
	}
	for (; c1; c1--) {
		*pFIFO++ = *pdwData++;
	}
}

uint32_t hsmci_get_status(const Hsmci * regs)
{
	return regs->HSMCI_SR;
}

void hsmci_cfg_dma(Hsmci * regs, uint32_t dwConfigure)
{
	regs->HSMCI_DMA = dwConfigure;
}

void hsmci_enable_dma(Hsmci * regs, bool use_dma)
{
	if (use_dma) {
		regs->HSMCI_DMA |= HSMCI_DMA_DMAEN;
	} else {
		regs->HSMCI_DMA &= ~HSMCI_DMA_DMAEN;
	}
}

void hsmci_configure(Hsmci * regs, uint32_t dwConfigure)
{
	regs->HSMCI_CFG = dwConfigure;
}

void hsmci_enable_hs(Hsmci * regs, bool high_spd)
{
	if (high_spd) {
		regs->HSMCI_CFG |= HSMCI_CFG_HSMODE;
	} else {
		regs->HSMCI_CFG &= ~HSMCI_CFG_HSMODE;
	}
}

bool hsmci_is_hs_enabled(const Hsmci * regs)
{
	return regs->HSMCI_CFG & HSMCI_CFG_HSMODE ? true : false;
}

void hsmci_cfg_wp(Hsmci * regs, uint32_t dwConfigure)
{
	regs->HSMCI_WPMR = dwConfigure;
}

uint32_t hsmci_get_wp_status(const Hsmci * regs)
{
	return regs->HSMCI_WPSR;
}
