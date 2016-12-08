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
 * Interface for Serial Peripheral Interface (SPI) controller.
 *
 */

#ifndef _SPI_H
#define _SPI_H

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

/*----------------------------------------------------------------------------
 *        Macros
 *----------------------------------------------------------------------------*/

/* Returns 1 if the TDRE bit (ready to transmit data) is set in the given status register value.*/
#define SPI_STATUS_TDRE(status) ((status & SPI_SR_TDRE) == SPI_SR_TDRE)

/* Returns 1 if the RDRF bit (ready to receive data) is set in the given status register value.*/
#define SPI_STATUS_RDRF(status) ((status & SPI_SR_RDRF) == SPI_SR_RDRF)

/* Returns 1 if the TXEMPTY bit is set in the given status register value.*/
#define SPI_STATUS_TXEMPTY(status) ((status & SPI_SR_TXEMPTY) == SPI_SR_TXEMPTY)

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Enables a SPI peripheral.
 *
 * \param spi  Pointer to an Spi instance.
 */
extern void spi_enable(Spi * spi);

/**
 * \brief Disables a SPI peripheral.
 *
 * \param spi  Pointer to an Spi instance.
 */
extern void spi_disable(Spi * spi);

/**
 * \brief Enables one or more interrupt sources of a SPI peripheral.
 *
 * \param spi  Pointer to an Spi instance.
 * \param dwSources Bitwise OR of selected interrupt sources.
 */
extern void spi_enable_it(Spi * spi, uint32_t dwSources);

/**
 * \brief Disables one or more interrupt sources of a SPI peripheral.
 *
 * \param spi  Pointer to an Spi instance.
 * \param dwSources Bitwise OR of selected interrupt sources.
 */
extern void spi_disable_it(Spi * spi, uint32_t dwSources);

/**
 * \brief Configures a SPI peripheral as specified. The configuration
 * can be computed
 * using several macros (see \ref spi_configuration_macros).
 *
 * \param spi  Pointer to an Spi instance.
 */
extern void spi_configure(Spi * spi);

/**
 * \brief Configures a chip select of a SPI peripheral.
 *
 * \param spi Pointer to an Spi instance.
 * \param cs Chip select to configure (0, 1, 2 or 3).
 * \param bitrate
 * \param delay_dlybs
 * \param delay_dlybct
 * \param spi_mode
 */
extern void spi_configure_cs(Spi * spi, uint8_t cs, uint32_t bitrate,
			     uint32_t delay_dlybs, uint32_t delay_dlybct,
			     uint32_t spi_mode);

/**
 * \brief Set SPI to master or slave mode
 *
 * \param spi  Pointer to an Spi instance.
 * \param master  Configure as master if true, configure as slave otherwise.
 */
extern void spi_mode_master_enable(Spi *spi, bool master);

/**
 * \brief Configures the current chip select bitrate
 *
 * \param spi Pointer to an Spi instance.
 * \param cs Chip select to configure (0, 1, 2 or 3).
 * \param bitrate
 */
extern void spi_set_cs_bitrate(Spi * spi, uint8_t cs, uint32_t bitrate);

/**
 * \brief Configures SPI chip select.
 *
 * \param spi  Pointer to an Spi instance.
 * \param cs   Chip select of NPSCx.
 */
extern void spi_select_cs(Spi * spi, uint8_t cs);

/**
 * \brief Configures SPI to release last used CS line.
 *
 * \param spi  Pointer to an Spi instance.
 */
extern void spi_release_cs(Spi * spi);

/**
 * \brief Write one data from SPI peripheral.
 *
 * \param spi Pointer to an Spi instance.
 *
 * \return readed data.
 */
extern void spi_write(Spi *spi, uint16_t tx);

/**
 * \brief Read one data from SPI peripheral.
 *
 * \param spi Pointer to an Spi instance.
 *
 * \return read data.
 */
extern uint16_t spi_read(Spi *spi);

/**
 * \brief Write and Read one data from SPI peripheral.
 *
 * \param spi Pointer to an Spi instance.
 * \param tx  Data to write
 *
 * \return read data.
 */
extern uint16_t spi_transfer(Spi *spi, uint16_t tx);

/**
 * \brief Get the current status register of the given SPI peripheral.
 *
 * \note This resets the internal value of the status register, so further
 * read may yield different values.
 *
 * \param spi   Pointer to a Spi instance.
 * \return  SPI status register.
 */
extern uint32_t spi_get_status(Spi * spi);

/**
 * \brief Returns the current status register of the given SPI peripheral, but
 * masking interrupt sources which are not currently enabled.
 *
 * \note This resets the internal value of the status register, so further
 * read may yield different values.
 *
 * \param spi  Pointer to an Spi instance.
 */
extern uint32_t spi_get_masked_status(Spi *spi);

/**
 * \brief Check if SPI transfer finish.
 *
 * \param spi  Pointer to an Spi instance.
 *
 * \return Returns true if there is no pending write operation on the SPI;
 * otherwise returns false.
 */
extern bool spi_is_tx_finished(Spi * spi);

#ifdef CONFIG_HAVE_SPI_FIFO
/**
 * \brief  Configure FIFO
 * \param spi       Pointer to an Spi instance.
 * \param tx_thres  TX threshold
 * \param rx_thres  RX threshold
 */
extern void spi_fifo_configure(Spi *spi, uint8_t tx_thres, uint8_t rx_thres);

/**
 * \brief  Enable FIFO
 * \param spi  Pointer to an Spi instance.
 */
extern void spi_fifo_enable(Spi *spi);

/**
 * \brief  Disable FIFO
 * \param spi  Pointer to an Spi instance.
 */
extern void spi_fifo_disable(Spi *spi);

/**
 * \brief  Get RX FIFO size
 * \param spi       Pointer to an Spi instance.
 * \return the number of bytes in the FIFO
 */
extern uint32_t spi_fifo_get_rx_size(Spi *spi);

/**
 * \brief  Get TX FIFO size
 * \param spi       Pointer to an Spi instance.
 * \return the number of bytes in the FIFO
 */
extern uint32_t spi_fifo_get_tx_size(Spi *spi);

extern void spi_fifo_flush_rx(Spi *spi);

extern void spi_fifo_flush_tx(Spi *spi);

#endif /* CONFIG_HAVE_SPI_FIFO */

#ifdef __cplusplus
}
#endif
#endif  /* #ifndef _SPI_H */
