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

#ifndef FLASHD_H
#define FLASHD_H

#include "chip.h"

/*----------------------------------------------------------------------------
 *        Type definitions
 *----------------------------------------------------------------------------*/

struct _flash {
	Eefc* eefc;
	uint32_t total_size;
	uint32_t page_size;
	uint32_t erase_size;
	uint32_t lock_count;
	uint32_t gpnvm_count;
};

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Initializes the flash driver.
 * \param flash pointer to the flash driver structure
 * \param eefc pointer to the flash peripheral to configure
 */
extern int flashd_initialize(struct _flash* flash, Eefc* eefc);

/**
 * \brief Read the 16-byte unique ID.
 * \param flash pointer to the flash driver structure
 * \param id pointer to a 16-byte buffer that will be updated with the unique ID.
 * \returns 0 on success; otherwise returns a negative error code.
 */
extern int flashd_read_unique_id(struct _flash* flash, uint8_t* uid);

/**
 * \brief Read the value of a GPNVM bit.
 * \param flash pointer to the flash driver structure
 * \param gpnvm GPNVM bit index.
 * \param value pointer to a boolean that will be updated with the GPNVM bit value.
 * \returns 0 on success; otherwise returns a negative error code.
 */
extern int flashd_get_gpnvm(struct _flash* flash, uint8_t gpnvm, bool* value);

/**
 * \brief Read the value of several consecutive GPNVM bits.
 * \param flash pointer to the flash driver structure
 * \param gpnvm_start GPNVM start bit index (inclusive)
 * \param gpnvm_end GPNVM end bit index (inclusive)
 * \param value pointer to a word whose lower bits will be updated with the
 *        GPNVM bit values (gpnvm_start into bit0, gpnvm_start+1 into bit1,
 *        etc.)
 * \returns 0 on success; otherwise returns a negative error code.
 */
extern int flashd_get_gpnvm_bits(struct _flash* flash, uint8_t gpnvm_start, uint8_t gpnvm_end, uint32_t* value);

/**
 * \brief Set the value of a GPNVM bit.
 * \param flash pointer to the flash driver structure
 * \param gpnvm GPNVM bit index.
 * \param value GPNVM bit value.
 * \returns 0 on success; otherwise returns a negative error code.
 */
extern int flashd_set_gpnvm(struct _flash* flash, uint8_t gpnvm, bool value);

/**
 * \brief Set the value of several consecutive GPNVM bits.
 * \param flash pointer to the flash driver structure
 * \param gpnvm_start GPNVM start bit index (inclusive)
 * \param gpnvm_end GPNVM end bit index (inclusive)
 * \param value word whose lower bits represent the GPNVM bit values to set
 *        (bit0=gpnvm_start, bit1=gpnvm_start+1, etc.)
 * \returns 0 on success; otherwise returns a negative error code.
 */
extern int flashd_set_gpnvm_bits(struct _flash* flash, uint8_t gpnvm_start, uint8_t gpnvm_end, uint32_t value);

/**
 * \brief Erase the whole flash
 * \param flash pointer to the flash driver structure
 * \returns 0 on success; otherwise returns a negative error code.
 */
extern int flashd_erase(struct _flash* flash);

/**
 * \brief Erase a single flash block
 * \param flash pointer to the flash driver structure
 * \param addr offset into the flash of the block to erase
 * \param length number of bytes to erase (block size)
 * \returns 0 on success; otherwise returns a negative error code.
 */
extern int flashd_erase_block(struct _flash* flash, uint32_t addr, uint32_t length);

/**
 * \brief Read data from the flash
 * \param flash pointer to the flash driver structure
 * \param addr start offset into the flash for the read operation
 * \param length number of bytes to read
 * \returns 0 on success; otherwise returns a negative error code.
 * \note The flash can also be read directly at address IFLASH_ADDR.
 */
extern int flashd_read(struct _flash* flash, uint32_t addr, uint8_t* data, uint32_t length);

/**
 * \brief Write data from the flash
 * \param flash pointer to the flash driver structure
 * \param addr start offset into the flash for the write operation
 * \param data pointer to the data to write into the flash
 * \param length number of bytes to write
 * \returns 0 on success; otherwise returns a negative error code.
 */
extern int flashd_write(struct _flash* flash, uint32_t addr, const uint8_t* data, uint32_t length);

#endif /* FLASHD_H */
