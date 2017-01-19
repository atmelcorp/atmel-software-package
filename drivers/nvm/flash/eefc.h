/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2017, Atmel Corporation
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

#ifndef EEFC_H
#define EEFC_H

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Enables the flash ready interrupt source on the EEFC peripheral.
 *
 * \param efc  Pointer to a Eefc instance
 */
extern void eefc_enable_frdy_it(Eefc* eefc);

/**
 * \brief Disables the flash ready interrupt source on the EEFC peripheral.
 *
 * \param efc  Pointer to a Efc instance
 */
extern void eefc_disable_frdy_it(Eefc* eefc);

/**
 * \brief Set read/write wait state on the EEFC peripheral.
 *
 * \param efc  Pointer to a Efc instance
 * \param cycles  the number of wait states in cycle.
 */
extern void eefc_set_flash_wait_states(Eefc* eefc, uint8_t cycles);

/**
 * \brief Read Unique Identifier from the EEFC peripheral.
 *
 * \param efc  Pointer to a Efc instance
 * \param uid  Pointer to a 16-byte buffer that will be updated with the unique ID.
 */
extern int eefc_read_unique_id(Eefc* eefc, uint8_t* uid);

/**
 * \brief Performs the given command and wait until its completion (or an error).
 *
 * \param eefc  Pointer to a Efc instance
 * \param cmd  Command to perform.
 * \param arg  Optional command argument.
 *
 * \return 0 if successful, otherwise returns an error code.
 */
extern int eefc_perform_command(Eefc* eefc, uint32_t command, uint32_t arg);

/**
 * \brief Returns the current status of the EEFC.
 *
 * \note Keep in mind that this function clears the value of some status bits
 * (LOCKE, PROGE).
 *
 * \param efc  Pointer to a Efc instance
 */
extern uint32_t eefc_get_status(Eefc* eefc);

/**
 * \brief Returns the result of the last executed command.
 *
 * \param efc  Pointer to a Efc instance
 */
extern uint32_t eefc_get_result(Eefc* eefc);

#endif /* EEFC_H */

