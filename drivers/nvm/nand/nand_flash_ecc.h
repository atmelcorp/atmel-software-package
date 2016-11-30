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
 * \page ecc_nand_page ECC NANDFLASH
 *
 * \section Purpose
 *
 * EccNandFlash layer is called by SkipBlockNandFlash driver, it will call the bl driver (RawNandFlash)
 * to do write/read operations, and do ECC check to the write/read result, it then will feedback the
 * ECC check result to the upper SkipBlockNandFlash layer driver.
 *
 * \section Usage
 *
 * -# nand_ecc_initialize() is used to initializes an EccNandFlash instance.
 * -# nand_ecc_write_page() is used to write a NANDFLASH page with ECC result, the function
 *      will calculate ECC for the data that is going to be written, and write data and spare(with
 *      calculated ECC) to NANDFLASH device.
 * -# nand_ecc_read_page() is used to read a NANDFLASH page with ECC check, the function
 *      will read out data and spare first, then it calculates ECC with data and then compare with
 *      the readout ECC, and feedback the ECC check result to PMECC driver.
*/

#ifndef NAND_FLASH_ECC_H
#define NAND_FLASH_ECC_H

/*---------------------------------------------------------------------- */
/*         Headers                                                       */
/*---------------------------------------------------------------------- */

#include <stdint.h>

#include "nand_flash_raw.h"

/*---------------------------------------------------------------------- */
/*         Exported functions                                            */
/*---------------------------------------------------------------------- */

extern uint8_t nand_ecc_read_page(const struct _nand_flash *nand,
		uint16_t block, uint16_t page,
		void *data, void *spare);

extern uint8_t nand_ecc_write_page(const struct _nand_flash *nand,
		uint16_t block, uint16_t page,
		void *data, void *spare);

#endif /* NAND_FLASH_ECC_H */
