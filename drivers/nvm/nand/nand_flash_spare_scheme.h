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
 * \page spare_nand_page _nand_spare_scheme
 *
 * \section Purpose
 *
 * _nand_spare_scheme layer is used to do NANDFLASH device's spare area operations. It is called by
 * upper layer drivers, such as \ref skip_nand_page layer.
 *
 * \section Usage
 *
 * -# nand_spare_scheme_write_bad_block_marker() is used to mark a bad-block marker inside a spare
 *     area.
 * -# nand_spare_scheme_read_bad_block_marker() is used to readout the marker.
 * -# nand_spare_scheme_read_ecc() is used to read out ecc from spare area using the provided
 *      spare scheme.
 * -# nand_spare_scheme_write_ecc() is used to write ecc to spare area using the provided
 *      spare scheme.
 * -# nand_spare_scheme_read_extra() is used to read extra bytes from spare area using the provided
 *      spare scheme.
 * -# nand_spare_scheme_write_extra() is used to write extra bytes to spare area using the provided
 *      spare scheme.
 */

#ifndef NAND_FLASH_SPARE_SCHEME_H
#define NAND_FLASH_SPARE_SCHEME_H

/*------------------------------------------------------------------------------ */
/*         Headers                                                               */
/*------------------------------------------------------------------------------ */

#include <stdint.h>

#include "nand_flash_common.h"

/*------------------------------------------------------------------------------ */
/*         Types                                                                 */
/*------------------------------------------------------------------------------ */

struct _nand_spare_scheme {
	uint8_t bad_block_marker_position;
	uint8_t num_ecc_bytes;
	const uint8_t *ecc_bytes_positions;
	uint8_t num_extra_bytes;
	const uint8_t *extra_bytes_positions;
};

/*------------------------------------------------------------------------------ */
/*         Exported variables                                                    */
/*------------------------------------------------------------------------------ */

extern const struct _nand_spare_scheme nand_spare_scheme256;
extern const struct _nand_spare_scheme nand_spare_scheme512;
extern const struct _nand_spare_scheme nand_spare_scheme2048;
extern const struct _nand_spare_scheme nand_spare_scheme4096;
extern const struct _nand_spare_scheme nand_spare_scheme8192;

/*------------------------------------------------------------------------------ */
/*         Exported functions                                                    */
/*------------------------------------------------------------------------------ */

extern void nand_spare_scheme_read_bad_block_marker(
		const struct _nand_spare_scheme *scheme,
		const uint8_t *spare,
		uint8_t *marker);

extern void nand_spare_scheme_write_bad_block_marker(
		const struct _nand_spare_scheme *scheme,
		uint8_t *spare,
		uint8_t marker);

extern void nand_spare_scheme_read_ecc(
		const struct _nand_spare_scheme *scheme,
		const uint8_t *spare,
		uint8_t *ecc);

extern void nand_spare_scheme_write_ecc(
		const struct _nand_spare_scheme *scheme,
		uint8_t *spare,
		const uint8_t *ecc);

extern void nand_spare_scheme_read_extra(
		const struct _nand_spare_scheme *scheme,
		const uint8_t *spare,
		void *extra,
		uint8_t size,
		uint8_t offset);

extern void nand_spare_scheme_write_extra(
		const struct _nand_spare_scheme *scheme,
		uint8_t *spare,
		const void *extra,
		uint8_t size,
		uint8_t offset);

#endif /* NAND_FLASH_SPARE_SCHEME_H */
