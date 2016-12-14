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

#ifndef BOARD_SPI_H
#define BOARD_SPI_H

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"

#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

struct _at25;

/*----------------------------------------------------------------------------
 *        Functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Configures SPIx bus for the board
 */
extern void board_cfg_spi_bus(void);

#ifdef BOARD_AT25_BUS
/**
 * \brief Configures the eth<iface> for the board
 */
extern void board_cfg_at25(void);

/**
 * \brief Get the at25 configuration for the board
 */
extern struct _at25* board_get_at25(void);
#endif /* BOARD_AT25_BUS */

#ifdef CONFIG_HAVE_QSPI
/**
 * \brief Configure the QSPI flash if available
 */
extern void board_cfg_qspiflash(void);

/**
 * \brief Get the qspi configuration for the board
 */
extern struct _qspiflash* board_get_qspiflash(void);
#endif /* CONFIG_HAVE_QSPI */

#endif /* BOARD_SPI_H */
