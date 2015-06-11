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

#include "peripherals/spi.h"
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

static inline uint32_t _spi_compute_scbr(uint32_t bitrate, uint32_t periph_id)
{
	assert(bitrate>0);
	return SPI_CSR_SCBR(
		pmc_get_peripheral_clock(periph_id) / (bitrate*1000));
}

static inline uint32_t _spi_compute_dlybs(uint32_t delay, uint32_t periph_id)
{
	uint32_t dlybs =
		pmc_get_peripheral_clock(periph_id) / (delay * 1000000000u);
	dlybs = dlybs > 0 ? dlybs : 1;
	return SPI_CSR_DLYBS(dlybs);
}

static inline uint32_t _spi_compute_dlybct(uint32_t delay, uint32_t periph_id)
{
	uint32_t dlybct =
		pmc_get_peripheral_clock(periph_id) / (delay * 31250000u);
	dlybct = dlybct > 0 ? dlybct : 1;
	return SPI_CSR_DLYBCT(dlybct);
}

static inline uint32_t _spi_is_master(Spi* spi)
{
	return (spi->SPI_MR & SPI_MR_MSTR);
}

static inline uint32_t _spi_is_variable_ps(Spi* spi)
{
	return (spi->SPI_MR & SPI_MR_PS);
}

static void _spi_write_dummy(Spi* spi)
{
	if (_spi_is_master(spi)) {
		spi->SPI_TDR = 0xFF;
	}
}

static inline void _spi_consume_read(Spi* spi)
{
	if (_spi_is_master(spi)) {
		while(!(spi->SPI_SR & SPI_SR_RDRF));
		(void)spi->SPI_RDR;
	}
}

#ifdef CONFIG_HAVE_SPI_FIFO
static void _spi_fifo_clear(Spi* spi, uint32_t fifos)
{
	spi->SPI_CR = fifos & (SPI_CR_RXFCLR | SPI_CR_TXFCLR);
}

static inline void _clear_fifo_control_flags(uint32_t* control_reg)
{
	*control_reg |= SPI_CR_TXFCLR | SPI_CR_RXFCLR | SPI_CR_FIFODIS;
}
#else
#define _clear_fifo_control_flags(dummy) do {} while(0)
#endif

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Enables a SPI peripheral.
 *
 * \param spi  Pointer to an Spi instance.
 */
void spi_enable(Spi * spi)
{
	spi->SPI_CR = SPI_CR_SPIEN;
}

/**
 * \brief Disables a SPI peripheral.
 *
 * \param spi  Pointer to an Spi instance.
 */
void spi_disable(Spi * spi)
{
	spi->SPI_CR = SPI_CR_SPIDIS;
}

/**
 * \brief Enables one or more interrupt sources of a SPI peripheral.
 *
 * \param spi  Pointer to an Spi instance.
 * \param dwSources Bitwise OR of selected interrupt sources.
 */
void spi_enable_it(Spi * spi, uint32_t dwSources)
{
	spi->SPI_IER = dwSources;
}

/**
 * \brief Disables one or more interrupt sources of a SPI peripheral.
 *
 * \param spi  Pointer to an Spi instance.
 * \param dwSources Bitwise OR of selected interrupt sources.
 */
void spi_disable_it(Spi * spi, uint32_t dwSources)
{
	spi->SPI_IDR = dwSources;
}

/**
 * \brief Configures a SPI peripheral as specified. The configuration
 * can be computed
 * using several macros (see \ref spi_configuration_macros).
 *
 * \param spi  Pointer to an Spi instance.
 * \param dwConfiguration  Value of the SPI configuration register.
 */
void spi_configure(Spi * spi, uint32_t configuration)
{
	uint32_t spi_id = get_spi_id_from_addr(spi);
	assert(spi_id != ID_PERIPH_COUNT);
	/* Enable device */
	pmc_enable_peripheral(spi_id);
	uint32_t control_reg = SPI_CR_SPIDIS;
	/* Add clear FIFO flags if present */
	_clear_fifo_control_flags(&control_reg);
	/* Apply */
	spi->SPI_CR = control_reg;

	/* Execute a software reset of the SPI twice */
	spi->SPI_CR = SPI_CR_SWRST;
	spi->SPI_CR = SPI_CR_SWRST;
	spi->SPI_MR = configuration;
}

/**
 * \brief Configures SPI chip select.
 *
 * \param spi  Pointer to an Spi instance.
 * \param cS  Chip select of NPSCx.
 */
void spi_chip_select(Spi * spi, uint8_t cS)
{
	spi->SPI_MR |= SPI_MR_PCS_Msk;
	spi->SPI_MR &= ~(SPI_MR_PCS(cS));
}

/**
 * \brief Configures SPI Mode Register.
 *
 * \param spi  Pointer to an Spi instance.
 * \param dwConfiguration  Value of the SPI mode register.
 */
void spi_set_mode(Spi * spi, uint32_t dwConfiguration)
{
	spi->SPI_MR = dwConfiguration;
}

/**
 * \brief Configures SPI to release last used CS line.
 *
 * \param spi  Pointer to an Spi instance.
 */
void spi_release_cs(Spi * spi)
{
	spi->SPI_CR = SPI_CR_LASTXFER;
}

/**
 * \brief Configures a chip select of a SPI peripheral.
 *
 * \param spi Pointer to an Spi instance.
 * \param cs Chip select to configure (0, 1, 2 or 3).
 * \param bitrate
 * \param delay_dlybs
 * \param delay_dlybct
 * \param spi_mode
 * \param release_on_last
 */
void spi_configure_cs(Spi * spi, uint32_t cs, uint32_t bitrate,
		      uint32_t delay_dlybs, uint32_t delay_dlybct,
		      uint32_t spi_mode, uint32_t release_on_last)
{
	uint32_t id = get_spi_id_from_addr(spi);
	assert(id < ID_PERIPH_COUNT);

	bitrate = _spi_compute_scbr(bitrate, id);
	delay_dlybs = _spi_compute_dlybs(delay_dlybs, id);
	delay_dlybct = _spi_compute_dlybct(delay_dlybct, id);
	release_on_last = release_on_last ? SPI_CSR_CSAAT : 0;

	spi->SPI_CSR[cs] = bitrate | delay_dlybs | delay_dlybct
		| release_on_last | spi_mode;
}

/**
 * \brief Configures a chip select active mode of a SPI peripheral.
 *
 * \param spi   Pointer to an Spi instance.
 * \param cs  Chip select to configure (0, 1, 2 or 3).
 * \param release_on_last CS controlled by last transfer.
 *                       spi_release_cs() is used to deactive CS.
 */
void spi_configure_cs_mode(Spi * spi, uint32_t cs, uint32_t release_on_last)
{
	if (!release_on_last) {
		spi->SPI_CSR[cs] |= SPI_CSR_CSAAT;
	} else {
		spi->SPI_CSR[cs] &= ~SPI_CSR_CSAAT;
	}
}

/**
 * \brief Get the current status register of the given SPI peripheral.
 * \note This resets the internal value of the status register, so further
 * read may yield different values.
 * \param spi   Pointer to a Spi instance.
 * \return  SPI status register.
 */
uint32_t spi_get_status(Spi * spi)
{
	return spi->SPI_SR;
}

/**
 * \brief Reads data from SPI peripheral while sending dummy data.
 *
 * \param spi Pointer to an Spi instance.
 *
 * \return readed data.
 */
uint32_t spi_read(Spi * spi)
{
	_spi_write_dummy(spi);
	while ((spi->SPI_SR & SPI_SR_RDRF) == 0) ;
	uint8_t value;
	readb(&spi->SPI_RDR, &value);
	return value;
}

/**
 * \brief Sends data through a SPI peripheral consuming reads.
 *
 * \details If the SPI is configured to use a fixed peripheral select,
 * the npcs value is meaningless. Otherwise, it identifies the
 * component which shall be addressed.
 *
 * \param spi   Pointer to an Spi instance.
 * \param cs  Chip select of the component to address (0, 1, 2 or 3).
 * \param data  Word of data to send.
 */
void spi_write(Spi * spi, uint32_t cs, uint16_t data)
{
	/* Send data */
	while ((spi->SPI_SR & SPI_SR_TXEMPTY) == 0);
	if (_spi_is_variable_ps(spi)) {
		spi->SPI_TDR = data | SPI_PCS(cs);
	} else {
		writehw(&spi->SPI_TDR, data);
	}
	/* Consume write to not corrupt FIFO if present (dummy
	 * function if CONFIG_HAV_SPI_FIFO not defined) */
	_spi_consume_read(spi);
}

/**
 * \brief Sends last data through a SPI peripheral.
 *
 * \details If the SPI is configured to use a fixed peripheral select,
 * the npcs value is meaningless. Otherwise, it identifies the
 * component which shall be addressed.
 *
 * \param spi   Pointer to an Spi instance.
 * \param dwNpcs  Chip select of the component to address (0, 1, 2 or 3).
 * \param wData  Word of data to send.
 */
void spi_write_last(Spi * spi, uint32_t cs, uint16_t data)
{
	/* Send data */
	while ((spi->SPI_SR & SPI_SR_TXEMPTY) == 0) ;
	spi->SPI_TDR = data | SPI_PCS(cs) | SPI_TDR_LASTXFER;
	/* Consume write to not corrupt FIFO if present (dummy
	 * function if CONFIG_HAV_SPI_FIFO not defined) */
	_spi_consume_read(spi);
}

/**
 * \brief Check if SPI transfer finish.
 *
 * \param spi  Pointer to an Spi instance.
 *
 * \return Returns 1 if there is no pending write operation on the SPI; otherwise
 * returns 0.
 */
uint32_t spi_is_finished(Spi * spi)
{
	return ((spi->SPI_SR & SPI_SR_TXEMPTY) != 0);
}

#ifdef CONFIG_HAVE_SPI_FIFO

static void _spi_fifo_set_rx_threshold(Spi* spi, uint8_t rx_thres)
{
	spi->SPI_FMR &= ~SPI_FMR_RXFTHRES_Msk;
	spi->SPI_FMR |= SPI_FMR_RXFTHRES(rx_thres);
}

static uint32_t _spi_write_stream(Spi *spi, uint32_t chip_select,
			  const void *stream, uint32_t len)
{
	const uint8_t* buffer = stream;
	uint32_t left = len;

	uint8_t is_ps = _spi_is_variable_ps(spi);
	uint32_t max_size = is_ps ? sizeof(uint8_t) : sizeof(uint16_t);

	while (left > 0) {
		if ((spi->SPI_SR & SPI_SR_TDRE) == 0) continue;

		/* Get FIFO free size (int octet) and clamp it */
		uint32_t buf_size = SPI_FIFO_DEPTH - spi_fifo_tx_size(spi);
		buf_size = buf_size > left ? left : buf_size;

		/* Fill the FIFO as must as possible */
		while (buf_size >= max_size) {
			if (is_ps)
				spi->SPI_TDR = *(uint8_t*)buffer | SPI_PCS(chip_select)
					| (left == len ? SPI_TDR_LASTXFER : 0);
			else {
				uint32_t value =
					*(uint8_t*)buffer |
					*(uint8_t*)(buffer+1) << 16;
				spi->SPI_TDR = value;
			}
			buffer += max_size;
			left -= max_size;
			buf_size -= max_size;
		}
		if (buf_size >= sizeof(uint8_t)) {
			spi->SPI_TDR = *(uint8_t*)buffer | (is_ps ? SPI_PCS(chip_select) : 0);
			buffer += sizeof(uint8_t);
			left -= sizeof(uint8_t);
		}
	}
	return len - left;
}

void spi_fifo_configure(Spi* spi, uint8_t tx_thres,
			uint8_t rx_thres,
			uint32_t ready_modes)
{
	/* Disable SPI and activate FIFO */
	spi->SPI_CR = SPI_CR_SPIDIS | SPI_CR_FIFOEN;

	/* Configure FIFO */
	spi->SPI_FMR = SPI_FMR_TXFTHRES(tx_thres) | SPI_FMR_RXFTHRES(rx_thres)
		| ready_modes;

	/* Reenable SPI */
	spi->SPI_CR = SPI_CR_SPIEN;
}

void spi_fifo_disable(Spi* spi)
{
}

uint32_t spi_fifo_rx_size(Spi *spi)
{
	return (spi->SPI_FLR & SPI_FLR_RXFL_Msk) >> SPI_FLR_RXFL_Pos;
}

uint32_t spi_fifo_tx_size(Spi *spi)
{
	return (spi->SPI_FLR & SPI_FLR_TXFL_Msk) >> SPI_FLR_TXFL_Pos;
}

uint32_t spi_read_stream(Spi *spi, uint32_t chip_select,
			 void *stream, uint32_t len)
{
	uint8_t* buffer = stream;
	uint32_t left = len;

	uint8_t is_master = _spi_is_master(spi);
	uint32_t max_size = is_master ? sizeof(uint8_t) : sizeof(uint32_t);

	/* flush status */
	(void)spi->SPI_SR;

	while (left > 0) {
		uint32_t lenwrite = left > SPI_FIFO_DEPTH ?
			SPI_FIFO_DEPTH : left;

		_spi_fifo_set_rx_threshold(spi, lenwrite);
		_spi_write_stream(spi, chip_select,
				 stream, lenwrite);

		while (spi->SPI_SR & SPI_SR_RXFTHF);
		/* flush status */
		(void)spi->SPI_SR;

		/* Get FIFO size (in octets) and clamp it */
		uint32_t buf_size = spi_fifo_rx_size(spi);
		buf_size = buf_size > left ? left : buf_size;

		/* Fill the buffer as must as possible with four data reads */
		while (buf_size >= max_size) {
			if (is_master) {
				readb(&spi->SPI_RDR, (uint8_t*)buffer);
			} else {
				*(uint32_t*)buffer = spi->SPI_RDR;
			}
			buffer += max_size;
			left -= max_size;
			buf_size -= max_size;
		}
		/* Add tail data if stream is not 4 octet aligned */
		if (buf_size >= sizeof(uint16_t)) {
			/* two data read */
			uint16_t value = 0;
			readhw(&spi->SPI_RDR, &value);
			*(uint8_t*)buffer = value & 0x00FFu;
			left -= sizeof(uint16_t);
			buffer += sizeof(uint16_t);
			buf_size -= sizeof(uint16_t);
		}
		if (buf_size >= sizeof(uint8_t)) {
			/* two data read */
			readb(&spi->SPI_RDR, (uint8_t*)buffer);
			left -= sizeof(uint8_t);
			buffer += sizeof(uint8_t);
		}
	}
	return len - left;
}

uint32_t spi_write_stream(Spi *spi, uint32_t chip_select,
			  const void *stream, uint32_t len)
{
	uint32_t consumed = _spi_write_stream(spi, chip_select, stream, len);
	_spi_fifo_clear(spi, SPI_CR_RXFCLR);
	return consumed;
}

#endif
