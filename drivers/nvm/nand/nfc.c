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
  *  \file
  *
  *  Implementation of SMC NFC functions.
  */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "trace.h"
#include "intmath.h"

#include "nvm/nand/nfc.h"
#include "peripherals/pmc.h"

#include <assert.h>

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/* Reading the NFC Command Register (to any address) will give the status of
 * the NFC. */
static uint32_t _nfc_read_status(void)
{
	return *(volatile uint32_t*)(NFC_CMD_ADDR);
}

static void _nfc_write_cmd(uint32_t cmd, uint32_t value)
{
	*(volatile uint32_t*)(NFC_CMD_ADDR + cmd) = value;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void nfc_configure(uint32_t data_size, uint32_t spare_size,
		bool read_spare, bool write_spare)
{
	uint32_t cfg;

	/* cannot read and write spare at the same time */
	assert(!read_spare || !write_spare);

	cfg = NFC_CFG_NFCSPARESIZE(CEIL_INT_DIV(spare_size, 4) - 1) |
	      NFC_CFG_DTOCYC(0xF) |
	      NFC_CFG_DTOMUL_X1048576 |
	      NFC_CFG_RBEDGE;

	if (read_spare)
		cfg |= NFC_CFG_RSPARE;

	if (write_spare)
		cfg |= NFC_CFG_WSPARE;

	switch (data_size) {
	case 512:
		cfg |= NFC_CFG_PAGESIZE_PS512;
		break;
	case 1024:
		cfg |= NFC_CFG_PAGESIZE_PS1024;
		break;
	case 2048:
		cfg |= NFC_CFG_PAGESIZE_PS2048;
		break;
	case 4096:
		cfg |= NFC_CFG_PAGESIZE_PS4096;
		break;
#ifdef NFC_CFG_PAGESIZE_PS8192
	case 8192:
		cfg |= NFC_CFG_PAGESIZE_PS8192;
		break;
#endif
	default:
		trace_fatal("Data size %d unsupported!\r\n",
				(unsigned)data_size);
	}

	NFC->NFC_CFG = cfg;
}

void nfc_enable(void)
{
	NFC->NFC_CTRL |= NFC_CTRL_NFCEN;
}

void nfc_disable(void)
{
	NFC->NFC_CTRL |= NFC_CTRL_NFCDIS;
}

uint32_t nfc_get_status(void)
{
	return NFC->NFC_SR;
}

/**
 * \brief Check if the host controller is busy.
 * \return Returns 1 if the host controller is busy, otherwise returns 0.
 */
static bool nfc_is_host_busy(void)
{
	return (_nfc_read_status() & NFCDATA_STATUS_NFCBUSY) == NFCDATA_STATUS_NFCBUSY;
}

/**
 * \brief Wait for NFC command has done.
 */
void nfc_wait_cmd_done(void)
{
	while ((NFC->NFC_SR & NFC_SR_CMDDONE) != NFC_SR_CMDDONE);
}

/**
 * \brief Wait for NFC Data Transfer Terminated.
 */
void nfc_wait_xfr_done(void)
{
	while ((NFC->NFC_SR & NFC_SR_XFRDONE) != NFC_SR_XFRDONE);
}

/**
 * \brief Wait for NFC Ready/Busy Line 0 Edge Detected.
 */
void nfc_wait_rb_busy(void)
{
	while ((NFC->NFC_SR & NFC_SR_RB_EDGE0) != NFC_SR_RB_EDGE0);
}

/**
 * \brief Uses the HOST NANDFLASH controller to send a command to the NFC.
 * \param cmd  command to send.
 * \param address_cycle address cycle when command access id decoded.
 * \param cycle0 address at first cycle.
 */
void nfc_send_cmd(uint32_t cmd, uint8_t *cycle_bytes)
{
	int cycle_offset = 0;
	uint32_t nfcdata_addr = 0;

	/* Wait until host controller is not busy. */
	while (nfc_is_host_busy());

	/* Send the command */
	switch (cmd & NFCADDR_CMD_ACYCLE_Msk) {
	case NFCADDR_CMD_ACYCLE_FIVE:
		NFC->NFC_ADDR = cycle_bytes[0];
		cycle_offset = 1;
		// fall-through
	case NFCADDR_CMD_ACYCLE_FOUR:
		nfcdata_addr |= NFCDATA_ADDR_ACYCLE4(cycle_bytes[cycle_offset + 3]);
		// fall-through
	case NFCADDR_CMD_ACYCLE_THREE:
		nfcdata_addr |= NFCDATA_ADDR_ACYCLE3(cycle_bytes[cycle_offset + 2]);
		// fall-through
	case NFCADDR_CMD_ACYCLE_TWO:
		nfcdata_addr |= NFCDATA_ADDR_ACYCLE2(cycle_bytes[cycle_offset + 1]);
		// fall-through
	case NFCADDR_CMD_ACYCLE_ONE:
		nfcdata_addr |= NFCDATA_ADDR_ACYCLE1(cycle_bytes[cycle_offset + 0]);
		break;
	case NFCADDR_CMD_ACYCLE_NONE:
		break;
	default:
		assert(0);
		break;
	}
	_nfc_write_cmd(cmd, nfcdata_addr);

	/* Wait for command completion */
	nfc_wait_cmd_done();
}

#ifdef CONFIG_HAVE_SMC_SCRAMBLING

void nfc_sram_scrambling_enable(void)
{
	SMC->SMC_OCMS |= SMC_OCMS_SRSE;
}

void nfc_sram_scrambling_disable(void)
{
	SMC->SMC_OCMS &= ~SMC_OCMS_SRSE;
}

bool nfc_sram_scrambling_is_enabled(void)
{
	return SMC->SMC_OCMS & SMC_OCMS_SRSE;
}

#endif /* CONFIG_HAVE_SMC_SCRAMBLING */
