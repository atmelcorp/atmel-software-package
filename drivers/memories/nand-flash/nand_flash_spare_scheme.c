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

/** \file */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "compiler.h"

#include "nand_flash_spare_scheme.h"

#include <assert.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Exported variables
 *----------------------------------------------------------------------------*/

static const uint8_t nand_spare_scheme256_ecc_bytes_pos[] = {
	0, 1, 2
};

static const uint8_t nand_spare_scheme256_extra_bytes_pos[] = {
	3, 4, 6, 7
};

/** Spare area placement scheme for 256 byte pages. */
const struct _nand_spare_scheme nand_spare_scheme256 = {
	.bad_block_marker_position = 5,
	.num_ecc_bytes = ARRAY_SIZE(nand_spare_scheme256_ecc_bytes_pos),
	.ecc_bytes_positions = nand_spare_scheme256_ecc_bytes_pos,
	.num_extra_bytes = ARRAY_SIZE(nand_spare_scheme256_extra_bytes_pos),
	.extra_bytes_positions = nand_spare_scheme256_extra_bytes_pos,
};

static const uint8_t nand_spare_scheme512_ecc_bytes_pos[] = {
	0, 1, 2, 3, 6, 7
};

static const uint8_t nand_spare_scheme512_extra_bytes_pos[] = {
	8, 9, 10, 11, 12, 13, 14, 15
};

/** Spare area placement scheme for 512 byte pages. */
const struct _nand_spare_scheme nand_spare_scheme512 = {
	.bad_block_marker_position = 5,
	.num_ecc_bytes = ARRAY_SIZE(nand_spare_scheme512_ecc_bytes_pos),
	.ecc_bytes_positions = nand_spare_scheme512_ecc_bytes_pos,
	.num_extra_bytes = ARRAY_SIZE(nand_spare_scheme512_extra_bytes_pos),
	.extra_bytes_positions = nand_spare_scheme512_extra_bytes_pos,
};

static const uint8_t nand_spare_scheme2048_ecc_bytes_pos[] = {
	40, 41, 42, 43, 44, 45, 46, 47,
	48, 49, 50, 51, 52, 53, 54, 55,
	56, 57, 58, 59, 60, 61, 62, 63
};

static const uint8_t nand_spare_scheme2048_extra_bytes_pos[] = {
	2,  3,  4,  5,  6,  7,  8,  9,
	10, 11, 12, 13, 14, 15, 16, 17,
	18, 19, 20, 21, 22, 23, 24, 25,
	26, 27, 28, 29, 30, 31, 32, 33,
	34, 35, 36, 37, 38, 39
};

/** Spare area placement scheme for 2048 byte pages. */
const struct _nand_spare_scheme nand_spare_scheme2048 = {
	.bad_block_marker_position = 0,
	.num_ecc_bytes = ARRAY_SIZE(nand_spare_scheme2048_ecc_bytes_pos),
	.ecc_bytes_positions = nand_spare_scheme2048_ecc_bytes_pos,
	.num_extra_bytes = ARRAY_SIZE(nand_spare_scheme2048_extra_bytes_pos),
	.extra_bytes_positions = nand_spare_scheme2048_extra_bytes_pos,
};

static const uint8_t nand_spare_scheme4096_ecc_bytes_pos[] = {
	80,  81,  82,  83,  84,  85,  86,  87,
	88,  89,  90,  91,  92,  93,  94,  95,
	96,  97,  98,  99,  100, 101, 102, 103,
	104, 105, 106, 107, 108, 109, 110, 111,
	112, 113, 114, 115, 116, 117, 118, 119,
	120, 121, 122, 123, 124, 125, 126, 127
};

static const uint8_t nand_spare_scheme4096_extra_bytes_pos[] = {
	2,  3,  4,  5,  6,  7,  8,  9,
	10, 11, 12, 13, 14, 15, 16, 17,
	18, 19, 20, 21, 22, 23, 24, 25,
	26, 27, 28, 29, 30, 31, 32, 33,
	34, 35, 36, 37, 38, 39, 40, 41,
	42, 43, 44, 45, 46, 47, 48, 49,
	50, 51, 52, 53, 54, 55, 56, 57,
	58, 59, 60, 61, 62, 63, 64, 65,
	66, 67, 68, 69, 70, 71, 72, 73,
	74, 75, 76, 77, 78, 79
};

/** Spare area placement scheme for 4096 byte pages. */
const struct _nand_spare_scheme nand_spare_scheme4096 = {
	.bad_block_marker_position = 0,
	.num_ecc_bytes = ARRAY_SIZE(nand_spare_scheme4096_ecc_bytes_pos),
	.ecc_bytes_positions = nand_spare_scheme4096_ecc_bytes_pos,
	.num_extra_bytes = ARRAY_SIZE(nand_spare_scheme4096_extra_bytes_pos),
	.extra_bytes_positions = nand_spare_scheme4096_extra_bytes_pos,
};

static const uint8_t nand_spare_scheme8192_ecc_bytes_pos[] = {
	80,  81,  82,  83,  84,  85,  86,  87,
	88,  89,  90,  91,  92,  93,  94,  95,
	96,  97,  98,  99,  100, 101, 102, 103,
	104, 105, 106, 107, 108, 109, 110, 111,
	112, 113, 114, 115, 116, 117, 118, 119,
	120, 121, 122, 123, 124, 125, 126, 127
};

static const uint8_t nand_spare_scheme8192_extra_bytes_pos[] = {
	2,  3,  4,  5,  6,  7,  8,  9,
	10, 11, 12, 13, 14, 15, 16, 17,
	18, 19, 20, 21, 22, 23, 24, 25,
	26, 27, 28, 29, 30, 31, 32, 33,
	34, 35, 36, 37, 38, 39, 40, 41,
	42, 43, 44, 45, 46, 47, 48, 49,
	50, 51, 52, 53, 54, 55, 56, 57,
	58, 59, 60, 61, 62, 63, 64, 65,
	66, 67, 68, 69, 70, 71, 72, 73,
	74, 75, 76, 77, 78, 79
};

/** Spare area placement scheme for 8192 byte pages. */
const struct _nand_spare_scheme nand_spare_scheme8192 = {
	.bad_block_marker_position = 0,
	.num_ecc_bytes = ARRAY_SIZE(nand_spare_scheme8192_ecc_bytes_pos),
	.ecc_bytes_positions = nand_spare_scheme8192_ecc_bytes_pos,
	.num_extra_bytes = ARRAY_SIZE(nand_spare_scheme8192_extra_bytes_pos),
	.extra_bytes_positions = nand_spare_scheme8192_extra_bytes_pos,
};

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Reads the bad block marker inside a spare area buffer using the provided
 * scheme.
 * \param scheme  Pointer to a _nand_spare_scheme instance.
 * \param spare  Spare area buffer.
 * \param marker  Pointer to the variable to store the bad block marker.
 */
void nand_spare_scheme_read_bad_block_marker(
		const struct _nand_spare_scheme *scheme,
		const uint8_t *spare, uint8_t *marker)
{
	*marker = spare[scheme->bad_block_marker_position];
}

/**
 * \brief Modifies the bad block marker inside a spare area, using the given scheme.
 * \param scheme  Pointer to a _nand_spare_scheme instance.
 * \param spare  Spare area buffer.
 * \param marker  Bad block marker to write.
 */
void nand_spare_scheme_write_bad_block_marker(
		const struct _nand_spare_scheme *scheme,
		uint8_t *spare, uint8_t marker)
{
	spare[scheme->bad_block_marker_position] = marker;
}

/**
 * \brief Reads ECC information from a spare area using the provided scheme.
 * \param scheme  Pointer to a _nand_spare_scheme instance.
 * \param spare  Spare area buffer.
 * \param ecc  ECC buffer.
 */
void nand_spare_scheme_read_ecc(
		const struct _nand_spare_scheme *scheme,
		const uint8_t *spare, uint8_t *ecc)
{
	uint32_t i;
	for (i = 0; i < scheme->num_ecc_bytes; i++) {
		ecc[i] = spare[scheme->ecc_bytes_positions[i]];
	}
}

/**
 * \brief Writes ECC information in a spare area, using a particular scheme.
 * \param scheme  Pointer to a _nand_spare_scheme instance.
 * \param spare  Spare area buffer.
 * \param ecc  ECC buffer.
 */
void nand_spare_scheme_write_ecc(
		const struct _nand_spare_scheme *scheme,
		uint8_t *spare, const uint8_t *ecc)
{
	uint32_t i;
	for (i = 0; i < scheme->num_ecc_bytes; i++) {
		spare[scheme->ecc_bytes_positions[i]] = ecc[i];
	}
}

/**
 * \brief Reads extra bytes of information from a spare area, using the provided
 * scheme.
 * \param scheme  Pointer to a _nand_spare_scheme instance.
 * \param spare  Spare area buffer.
 * \param extra  Extra bytes buffer.
 * \param size  Number of extra bytes to read.
 * \param offset  Index where to read the first extra byte.
 */
void nand_spare_scheme_read_extra( const struct _nand_spare_scheme *scheme,
		const uint8_t *spare, void *extra, uint8_t size,
		uint8_t offset)
{
	uint32_t i;

	assert((size + offset) < scheme->num_extra_bytes);

	for (i = 0; i < size; i++) {
		((uint8_t*)extra)[i] =
			spare[scheme->extra_bytes_positions[offset + i]];
	}
}

/**
 * \brief Write extra bytes of information inside a spare area, using the provided
 * scheme.
 * \param scheme  Pointer to a _nand_spare_scheme instance.
 * \param spare  Spare area buffer.
 * \param extra  Extra bytes to write.
 * \param size  Number of extra bytes to write.
 * \param offset  Index where to write the first extra byte.
*/
void nand_spare_scheme_write_extra( const struct _nand_spare_scheme *scheme,
		uint8_t *spare, const void *extra, uint8_t size,
		uint8_t offset)
{
	uint32_t i;

	assert((size + offset) < scheme->num_extra_bytes);

	for (i = 0; i < size; i++) {
		spare[scheme->extra_bytes_positions[offset + i]] =
			((uint8_t*)extra)[i];
	}
}
