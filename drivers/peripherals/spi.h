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

/*------------------------------------------------------------------------------ */

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
 * \param dwConfiguration  Value of the SPI configuration register.
 */
extern void spi_configure(Spi * spi, uint32_t configuration);

/**
 * \brief Configures SPI chip select.
 *
 * \param spi  Pointer to an Spi instance.
 * \param cs  Chip select of NPSCx.
 */
extern void spi_chip_select(Spi * spi, uint8_t cs);

/**
 * \brief Configures SPI to release last used CS line.
 *
 * \param spi  Pointer to an Spi instance.
 */
extern void spi_release_cs(Spi * spi);

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
extern void spi_configure_cs(Spi * spi, uint32_t cs, uint32_t bitrate,
			     uint32_t delay_dlybs, uint32_t delay_dlybct,
			     uint32_t spi_mode);

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
 * \brief Check if SPI transfer finish.
 *
 * \param spi  Pointer to an Spi instance.
 *
 * \return Returns true if there is no pending write operation on the SPI;
 * otherwise returns false.
 */

extern bool spi_is_tx_finished(Spi * spi);

#ifdef __cplusplus
}
#endif
#endif  /* #ifndef _SPI_H */
