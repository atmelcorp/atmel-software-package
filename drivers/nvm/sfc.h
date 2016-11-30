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

/**
 * \file
 *
 * Interface for Secure Fuse Controller (SFC).
 *
 */

#ifndef SFC_H_
#define SFC_H_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

enum {
	SFC_ERR_LCHECK = 1, /* Live Integrity Checking Error */
	SFC_ERR_APLE   = 2, /* Atmel Programming Lock Error */
	SFC_ERR_ACE    = 4, /* Atmel Check Error */
};

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Get the current error status of the SFC (clear on read)
 * \return the current errors (bitfield of SFC_ERR_x constants)
 */
extern uint32_t sfc_get_errors(void);

/**
 * \brief Read the value of a fuse data register
 * This function can be called without calling sfc_enable beforehand.
 * \param index the index of the fuse data register to read
 * \return the value of the fuse data register at requested index
 */
extern uint32_t sfc_read(uint32_t index);

/**
 * \brief Enable the peripheral clock of the SFC
 */
extern void sfc_enable(void);

/**
 * \brief Disable the peripheral clock of the SFC
 */
extern void sfc_disable(void);

/**
 * \brief Write the value of a fuse data register
 * The SFC peripheral clock must be enabled beforehand by calling sfc_enable.
 * The SFC only writes the 1 bits.
 * \param index the index of the fuse data register to write
 * \return true on success, false otherwise
 */
extern bool sfc_write(uint32_t index, uint32_t data);

/**
 * \brief Mask some data registers
 * Once masking is enabled, some data registers will read 0 until the chip is reset.
 * The masked registers are 20 to 23 for SAMA5D2x and 0 to 7 for SAMA5D4x.
 */
extern void sfc_mask_data_registers(void);

/**
 * \brief Check if some data registers are masked
 * \return true if some registers are masked, false otherwise
 */
extern bool sfc_are_data_registers_masked(void);

#ifdef __cplusplus
}
#endif

#endif /* SFC_H_ */
