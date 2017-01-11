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
*  Definitions and function prototype for SMC module
*/

#ifndef SMC_H_
#define SMC_H_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Sets SMC timing for NAND FLASH.
 * \param bus_width  bus width 8/16.
 */
extern void smc_nand_configure(uint8_t bus_width);

/**
 * \brief Sets SMC timing for NOR FLASH.
 * \param cs  chip select.
 * \param bus_width  bus width 8/16.
 */
extern void smc_nor_configure(uint8_t cs, uint8_t bus_width);

/**
 * \brief Set SMC scrambling key.
 * \param key1
 * \param key2
 */
extern void smc_scrambling_set_key(uint32_t key1, uint32_t key2);

/**
 * \brief Enables SMC scrambling
 */
extern void smc_scrambling_enable(void);

/**
 * \brief Disables SMC scrambling
 */
extern void smc_scrambling_disable(void);

/**
 * \brief Check if SMC scrambling is enabled
 * \return true if SMC scrambling enabled, false otherwise
 */
extern bool smc_scrambling_is_enabled(void);

#endif /* SMC_H_ */
