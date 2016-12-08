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

/** \addtogroup spi_module Working with SPI
 * \section Purpose
 * The SPI driver provides the interface to configure and use the SPI
 * peripheral.
 *
 * The Serial Peripheral Interface (SPI) circuit is a synchronous serial
 * data link that provides communication with external devices in Master
 * or Slave Mode.
 *
 * \section Usage
 * To use the SPI, the user has to follow these few steps:
 * -# Enable the SPI pins required by the application (see pio.h).
 * -# Configure the SPI using the \ref spi_configure(). This enables the
 *    peripheral clock. The mode register is loaded with the given value.
 * -# Configure all the necessary chip selects with \ref spi_configure_npcs().
 * -# Enable the SPI by calling \ref spi_enable().
 * -# Send/receive data using \ref spi_write() and \ref
 * spi_read(). Note that \ref spi_read()
 *    must be called after \ref spi_write() to retrieve the last value read.
 * -# Disable the SPI by calling \ref spi_disable().
 *
 * For more accurate information, please look at the SPI section of the
 * Datasheet.
 *
 * Related files :\n
 * \ref spi.c\n
 * \ref spi.h\n
*/
/*@{*/
/*@}*/

/**
 * \file
 *
 * Implementation of Serial Peripheral Interface (SPI) controller.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

#include "spi/spi.h"
#include "peripherals/pmc.h"

#include "io.h"
#include "trace.h"

#include <stdint.h>

#include <assert.h>

/*---------------------------------------------------------------------------
*        Macros
*----------------------------------------------------------------------------*/

#define SPI_PCS(npcs)       SPI_MR_PCS((~(1 << npcs) & 0xF))

/*----------------------------------------------------------------------------
 *        local functions
 *----------------------------------------------------------------------------*/

static inline uint32_t _spi_compute_scbr(uint32_t bitrate, uint32_t id)
{
	uint32_t pclk = pmc_get_peripheral_clock(id);
	if (bitrate == 0)
		return 0;
	return SPI_CSR_SCBR(pclk / (bitrate * 1000));
}

static inline uint32_t _spi_compute_dlybs(uint32_t delay, uint32_t id)
{
	uint32_t pclk = pmc_get_peripheral_clock(id);
	uint32_t dlybs = ((pclk / 1000000u) * delay) / 100;
	return SPI_CSR_DLYBS(dlybs);
}

static inline uint32_t _spi_compute_dlybct(uint32_t delay, uint32_t id)
{
	uint32_t pclk = pmc_get_peripheral_clock(id);
	uint32_t dlybct = ((pclk / 32000u) * delay) / 100;
	return SPI_CSR_DLYBCT(dlybct);
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void spi_enable(Spi * spi)
{
	spi->SPI_CR = SPI_CR_SPIEN;
}

void spi_disable(Spi * spi)
{
	spi->SPI_CR = SPI_CR_SPIDIS;
}

void spi_enable_it(Spi * spi, uint32_t dwSources)
{
	spi->SPI_IER = dwSources;
}

void spi_disable_it(Spi * spi, uint32_t dwSources)
{
	spi->SPI_IDR = dwSources;
}

void spi_configure(Spi * spi)
{
	spi->SPI_CR = SPI_CR_SPIDIS;

	spi->SPI_CR = SPI_CR_SWRST;

	spi->SPI_MR = SPI_MR_WDRBT | SPI_MR_MODFDIS;

	spi->SPI_RDR;
}

void spi_mode_master_enable(Spi *spi, bool master)
{
	if (master)
		spi->SPI_MR |= SPI_MR_MSTR;
	else
		spi->SPI_MR = spi->SPI_MR & ~SPI_MR_MSTR;
}

void spi_select_cs(Spi * spi, uint8_t cs)
{
	uint32_t mr = spi->SPI_MR & ~SPI_MR_PCS_Msk;
	spi->SPI_MR = mr | SPI_MR_PCS((1 << cs) - 1);
}

void spi_release_cs(Spi * spi)
{
	spi->SPI_CR = SPI_CR_LASTXFER;
}

void spi_configure_cs(Spi * spi, uint8_t cs, uint32_t bitrate,
		      uint32_t delay_dlybs, uint32_t delay_dlybct,
		      uint32_t spi_mode)
{
	uint32_t csr = 0;
	trace_debug("Spi: configuring chip select %u\r\n", (unsigned int)cs);
	uint32_t id = get_spi_id_from_addr(spi);
	assert(id < ID_PERIPH_COUNT);

	csr |= _spi_compute_scbr(bitrate, id);
	csr |= _spi_compute_dlybs(delay_dlybs, id);
	csr |= _spi_compute_dlybct(delay_dlybct, id);
	csr |= spi_mode & ~(SPI_CSR_SCBR_Msk | SPI_CSR_DLYBS_Msk | SPI_CSR_DLYBCT_Msk);

	spi->SPI_CSR[cs] = csr;
}

void spi_set_cs_bitrate(Spi * spi, uint8_t cs, uint32_t bitrate)
{
	uint32_t csr = spi->SPI_CSR[cs];
	uint32_t id = get_spi_id_from_addr(spi);
	assert(id < ID_PERIPH_COUNT);

	csr &= ~SPI_CSR_SCBR_Msk;
	csr |= _spi_compute_scbr(bitrate, id);

	spi->SPI_CSR[cs] = csr;
}

uint32_t spi_get_status(Spi * spi)
{
	return spi->SPI_SR;
}

uint32_t spi_get_masked_status(Spi *spi)
{
	uint32_t status;
	assert(spi != NULL);
	status = spi->SPI_SR;
	status &= spi->SPI_IMR;
	return status;
}

void spi_write(Spi *spi, uint16_t tx)
{
	while ((spi->SPI_SR & SPI_SR_TDRE) == 0);

	writehw(&spi->SPI_TDR, SPI_TDR_TD(tx));
}

uint16_t spi_read(Spi *spi)
{
	while ((spi->SPI_SR & SPI_SR_RDRF) == 0);

	return (spi->SPI_RDR & SPI_RDR_RD_Msk);
}

uint16_t spi_transfer(Spi *spi, uint16_t tx)
{
	spi_write(spi, tx);

	return spi_read(spi);
}

bool spi_is_tx_finished(Spi * spi)
{
	return ((spi->SPI_SR & SPI_SR_TXEMPTY) != 0);
}

#ifdef CONFIG_HAVE_SPI_FIFO
void spi_fifo_configure(Spi *spi, uint8_t tx_thres, uint8_t rx_thres)
{
	assert(spi != NULL);

	/* Configure FIFO */
	spi->SPI_FMR = SPI_FMR_TXFTHRES(tx_thres) | SPI_FMR_RXFTHRES(rx_thres)
		| SPI_FMR_RXRDYM_ONE_DATA | SPI_FMR_TXRDYM_ONE_DATA;
}

void spi_fifo_enable(Spi *spi)
{
	assert(spi != NULL);

	spi->SPI_CR = SPI_CR_SPIDIS;
	spi->SPI_CR = SPI_CR_FIFOEN | SPI_CR_TXFCLR | SPI_CR_RXFCLR;

	spi->SPI_CR = SPI_CR_SPIEN;
}

void spi_fifo_disable(Spi *spi)
{
	assert(spi != NULL);

	spi->SPI_CR = SPI_CR_SPIDIS;
	spi->SPI_CR = SPI_CR_FIFODIS | SPI_CR_TXFCLR | SPI_CR_RXFCLR;

	spi->SPI_CR = SPI_CR_SPIEN;
}

uint32_t spi_fifo_get_rx_size(Spi *spi)
{
	assert(spi != NULL);

	return (spi->SPI_FLR & SPI_FLR_RXFL_Msk) >> SPI_FLR_RXFL_Pos;
}

uint32_t spi_fifo_get_tx_size(Spi *spi)
{
	assert(spi != NULL);

	return (spi->SPI_FLR & SPI_FLR_TXFL_Msk) >> SPI_FLR_TXFL_Pos;
}

void spi_fifo_flush_rx(Spi *spi)
{
	assert(spi != NULL);
	spi->SPI_CR = SPI_CR_RXFCLR;
}

void spi_fifo_flush_tx(Spi *spi)
{
	assert(spi != NULL);
	spi->SPI_CR = SPI_CR_TXFCLR;
}

#endif /* CONFIG_HAVE_SPI_FIFO */
