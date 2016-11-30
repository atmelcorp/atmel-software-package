/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation
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
 * \page raw_nand_page RawNandflash
 *
 * \section Purpose
 *
 * RawNandflash is a bl NANDFLASH driver, it directly interacts with hardware's register to
 * operate NANDFLASH interface, and it is called by upper layer drivers, such as EccNandFlash
 *
 * \section Usage
 *
 * -# nand_raw_initialize() is used to initializes a RawNandFlash instance based on the given
 *      model and physical interface. If no model is provided, then the function tries to auto-detect
 *      it.
 * -# nand_raw_reset() is used to reset a NANDFLASH device.
 * -# nand_raw_read_id() is used to read a NANDFLASH's id.
 * -# nand_raw_erase_block() is used to erase a certain NANDFLASH device's block.
 * -# nand_raw_read_page() and nand_raw_write_page is used to do read/write operation.
 * -# nand_raw_copy_page() is used to issue copy-page command to NANDFLASH device.
 * -# nand_raw_copy_block() calls nand_raw_copy_page to do a NANDFLASH block copy.
*/


#ifndef NAND_FLASH_RAW_H
#define NAND_FLASH_RAW_H

/*------------------------------------------------------------------------------ */
/*         Headers                                                               */
/*------------------------------------------------------------------------------ */

#include <stdint.h>

#include "gpio/pio.h"

#include "nand_flash.h"

/*------------------------------------------------------------------------------ */
/*         Exported functions                                                    */
/*------------------------------------------------------------------------------ */

extern uint8_t nand_raw_initialize(struct _nand_flash *nand,
		const struct _nand_flash_model *model);

extern void nand_raw_reset(const struct _nand_flash *nand);

extern uint32_t nand_raw_read_id(const struct _nand_flash *nand);

extern uint8_t nand_raw_erase_block(const struct _nand_flash *nand,
		uint16_t block);

extern uint8_t nand_raw_read_page(const struct _nand_flash *nand,
		uint16_t block, uint16_t page,
		void *data, void *spare);

extern uint8_t nand_raw_write_page(const struct _nand_flash *nand,
		uint16_t block, uint16_t page,
		void *data, void *spare);

extern uint8_t nand_raw_copy_page(const struct _nand_flash *nand,
		uint16_t source_block, uint16_t source_page,
		uint16_t dest_block, uint16_t dest_page);

extern uint8_t nand_raw_copy_block(const struct _nand_flash *nand,
		uint16_t source_block, uint16_t dest_block);

#endif /* NAND_FLASH_RAW_H */
