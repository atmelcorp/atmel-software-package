/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/


#include "barriers.h"
#include "chip.h"
#include "timer.h"
#include "trace.h"
#ifdef CONFIG_HAVE_QSPI_DMA
#include "dma/dma.h"
#include "mm/cache.h"
#endif
#include "peripherals/pmc.h"
#include "spi/qspi.h"
#include <stdint.h>
#include <string.h>

#ifdef CONFIG_HAVE_QSPI_DMA
static struct dma_channel *dma_ch = NULL;
static struct dma_xfer_cfg dma_cfg = {
	.upd_sa_per_data = 1,
	.upd_da_per_data = 1,
	.data_width = DMA_DATA_WIDTH_BYTE,
	.chunk_size = DMA_CHUNK_SIZE_1,
	.blk_size = 0,
};
#endif

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static void qspi_memcpy(uint8_t *dst, const uint8_t *src, int count, bool use_dma)
{
	uint32_t rc;
#ifdef CONFIG_HAVE_QSPI_DMA
	if (use_dma) {
		dma_ch = dma_allocate_channel(DMA_PERIPH_MEMORY, DMA_PERIPH_MEMORY);
		if (!dma_ch)
			trace_fatal("Couldn't allocate XDMA channel\n\r");
		dma_cfg.da = (void *)dst;
		dma_cfg.sa = (void *)src;
		dma_cfg.len = count;
		dma_configure_transfer(dma_ch, &dma_cfg);
		rc = dma_start_transfer(dma_ch);
		if (rc != DMA_OK)
			trace_fatal("Couldn't start xDMA transfer\n\r");
		while (!dma_is_transfer_done(dma_ch))
			dma_poll();
		dma_stop_transfer(dma_ch);
		dma_free_channel(dma_ch);
		dma_ch = NULL;
		dsb();
	} else
#endif
	while (count--) {
		*dst++ = *src++;
		dsb();
	}
}

/*----------------------------------------------------------------------------
 *        Public functions
 *----------------------------------------------------------------------------*/

void qspi_initialize(Qspi *qspi)
{
	pmc_configure_peripheral(get_qspi_id_from_addr(qspi), NULL, true);

	/* Disable write protection */
	qspi->QSPI_WPMR = QSPI_WPMR_WPKEY_PASSWD;

	/* Reset */
	qspi->QSPI_CR = QSPI_CR_SWRST;

	/* Configure */
	qspi->QSPI_MR = QSPI_MR_SMM_MEMORY;
	qspi->QSPI_SCR = 0;

	/* Enable */
	qspi->QSPI_CR = QSPI_CR_QSPIEN;
}

uint32_t qspi_set_baudrate(Qspi *qspi, uint32_t baudrate)
{
	uint32_t mck, scr, scbr;

	if (!baudrate)
		return 0;

	/* Serial Clock Baudrate */
	mck = pmc_get_peripheral_clock(get_qspi_id_from_addr(qspi));
	scbr = (mck + baudrate - 1) / baudrate;
	if (scbr > 0)
		scbr--;

	/* Update the Serial Clock Register */
	scr = qspi->QSPI_SCR;
	scr &= ~QSPI_SCR_SCBR_Msk;
	scr |= QSPI_SCR_SCBR(scbr);
	qspi->QSPI_SCR = scr;

	return mck / (scbr + 1);
}

bool qspi_perform_command(Qspi *qspi, const struct _qspi_cmd *cmd)
{
	uint32_t iar, icr, ifr;
	uint32_t offset;
	uint8_t *ptr;
	bool use_dma = false;

	iar = 0;
	icr = 0;
	ifr = (cmd->ifr_width & QSPI_IFR_WIDTH_Msk) | (cmd->ifr_type & QSPI_IFR_TFRTYP_Msk);

	/* Compute address parameters */
	switch (cmd->enable.address) {
	case 4:
		ifr |= QSPI_IFR_ADDRL_32_BIT;
		/* fallback to the 24-bit address case */
	case 3:
		iar = (cmd->enable.data) ? 0 : QSPI_IAR_ADDR(cmd->address);
		ifr |= QSPI_IFR_ADDREN;
		offset = cmd->address;
		break;
	case 0:
		offset = 0;
		break;
	default:
		return false;
	}

	/* Compute instruction parameters */
	if (cmd->enable.instruction) {
		icr |= QSPI_ICR_INST(cmd->instruction);
		ifr |= QSPI_IFR_INSTEN;
	}

	/* Compute option parameters */
	if (cmd->enable.mode && cmd->num_mode_cycles) {
		uint32_t mode_cycle_bits, mode_bits;

		icr |= QSPI_ICR_OPT(cmd->mode);
		ifr |= QSPI_IFR_OPTEN;

		switch (ifr & QSPI_IFR_WIDTH_Msk) {
		case QSPI_IFR_WIDTH_SINGLE_BIT_SPI:
		case QSPI_IFR_WIDTH_DUAL_OUTPUT:
		case QSPI_IFR_WIDTH_QUAD_OUTPUT:
			mode_cycle_bits = 1;
			break;
		case QSPI_IFR_WIDTH_DUAL_IO:
		case QSPI_IFR_WIDTH_DUAL_CMD:
			mode_cycle_bits = 2;
			break;
		case QSPI_IFR_WIDTH_QUAD_IO:
		case QSPI_IFR_WIDTH_QUAD_CMD:
			mode_cycle_bits = 4;
			break;
		default:
			return false;
		}

		mode_bits = cmd->num_mode_cycles * mode_cycle_bits;
		switch (mode_bits) {
		case 1:
			ifr |= QSPI_IFR_OPTL_OPTION_1BIT;
			break;

		case 2:
			ifr |= QSPI_IFR_OPTL_OPTION_2BIT;
			break;

		case 4:
			ifr |= QSPI_IFR_OPTL_OPTION_4BIT;
			break;

		case 8:
			ifr |= QSPI_IFR_OPTL_OPTION_8BIT;
			break;

		default:
			return false;
		}
	}

	/* Set number of dummy cycles */
	if (cmd->enable.dummy)
		ifr |= QSPI_IFR_NBDUM(cmd->num_dummy_cycles);
	else
		ifr |= QSPI_IFR_NBDUM(0);

	/* Set data enable */
	if (cmd->enable.data) {
		ifr |= QSPI_IFR_DATAEN;

		/* Special case for Continous Read Mode */
		if (!cmd->tx_buffer && !cmd->rx_buffer)
			ifr |= QSPI_IFR_CRM_ENABLED;
	}

	/* Set QSPI Instruction Frame registers */
	qspi->QSPI_IAR = iar;
	qspi->QSPI_ICR = icr;
	qspi->QSPI_IFR = ifr;

	/* Skip to the final steps if there is no data */
	if (!cmd->enable.data)
		goto no_data;

	/* Dummy read of QSPI_IFR to synchronize APB and AHB accesses */
	(void)qspi->QSPI_IFR;

#ifdef CONFIG_HAVE_QSPI_DMA
	if (((QSPI_IFR_TFRTYP_TRSFR_WRITE_MEMORY == cmd->ifr_type) &&
		 IS_CACHE_ALIGNED(cmd->tx_buffer) &&
		 IS_CACHE_ALIGNED(cmd->buffer_len)) ||
		((QSPI_IFR_TFRTYP_TRSFR_READ_MEMORY == cmd->ifr_type) &&
		 IS_CACHE_ALIGNED(cmd->rx_buffer) &&
		 IS_CACHE_ALIGNED(cmd->buffer_len)))
		use_dma = true;
#endif

	/* Send/Receive data */
	if (cmd->tx_buffer) {
		/* Write data */
#ifdef CONFIG_HAVE_AESB
		if(cmd->use_aesb)
			ptr = (uint8_t*)get_qspi_aesb_mem_from_addr(qspi);
		else
#endif
			ptr = (uint8_t*)get_qspi_mem_from_addr(qspi);

#ifdef CONFIG_HAVE_QSPI_DMA
		if (use_dma)
			cache_clean_region(cmd->tx_buffer, cmd->buffer_len);
#endif
		qspi_memcpy(ptr + offset, cmd->tx_buffer, cmd->buffer_len, use_dma);
	} else if (cmd->rx_buffer) {
		/* Read data */
#ifdef CONFIG_HAVE_AESB
		if (cmd->use_aesb)
			ptr = (uint8_t*)get_qspi_aesb_mem_from_addr(qspi);
		else
#endif
			ptr = (uint8_t*)get_qspi_mem_from_addr(qspi);

		qspi_memcpy(cmd->rx_buffer, ptr + offset, cmd->buffer_len, use_dma);
#ifdef CONFIG_HAVE_QSPI_DMA
		if (use_dma)
			cache_invalidate_region(cmd->rx_buffer, cmd->buffer_len);
#endif
	} else {
		/* Stop here for continuous read */
		return true;
	}

no_data:
	/* Release the chip-select */
	qspi->QSPI_CR = QSPI_CR_LASTXFER;

	/* Wait for INSTRuction End */
	struct _timeout timeout;
	timer_start_timeout(&timeout, cmd->timeout);
	while (!(qspi->QSPI_SR & QSPI_SR_INSTRE)) {
		if (timer_timeout_reached(&timeout)) {
			trace_debug("qspi_perform_command timeout reached\r\n");
			return false;
		}
	}

	return true;
}
