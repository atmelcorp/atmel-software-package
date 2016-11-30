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

#ifndef NAND_FLASH_COMMON_H
#define NAND_FLASH_COMMON_H

/** \addtogroup nand_common_def
@{*/

/*------------------------------------------------------------------------------ */
/*         Definitions                                                           */
/*------------------------------------------------------------------------------ */

/* traces are disabled by default */
#undef NAND_DEBUG

#ifdef NAND_DEBUG
#define NAND_TRACE(...) trace_debug_wp(__VA_ARGS__)
#else
#define NAND_TRACE(...)
#endif

/** \addtogroup nand_max_val NandFlash Maximum Supported Values
 * @{
 * Since no memory allocation is available, limits have been set on various
 * characteristics of a NandFlash chip:
 *
 * \section Maximums
 * - NAND_MAXNUM_BLOCKS
 * - NAND_MAX_NUM_PAGES_PER_BLOCK
 * - NandCommon_MAXPAGESIZE
*/

/** Maximum number of blocks in a device */
#define NAND_MAXNUM_BLOCKS               2048

/** Maximum number of pages in one block */
#define NAND_MAX_NUM_PAGES_PER_BLOCK     256

/** Maximum size of the data area of one page, in bytes. */
#define NAND_MAX_PAGE_DATA_SIZE          8192

/** Maximum size of the spare area of one page, in bytes. */
#define NAND_MAX_PAGE_SPARE_SIZE         512

/** Maximum number of ecc bytes stored in the spare for one single page. */
#define NAND_MAX_SPARE_ECC_BYTES         48

/** Maximum number of extra free bytes inside the spare area of a page. */
#define NAND_MAX_SPARE_EXTRA_BYTES       384

#define NAND_MAX_PMECC_BYTE_SIZE         512

/** @}*/

/** \addtogroup nand_ec NandFlash Error Codes
 * @{
 * NandFlash API methods return either 0 (indicating that there was no error),
 * or one of the following error codes:
 *
 * \section Codes
 * - NAND_ERROR_NOMOREBLOCKS
 * - NAND_ERROR_BLOCKNOTMAPPED
 * - NAND_ERROR_OUTOFBOUNDS
 * - NAND_ERROR_MAPPINGNOTFOUND
 * - NAND_ERROR_CANNOTREAD
*/

/** No more blocks can be allocated for a write operation. */
#define NAND_ERROR_NOMOREBLOCKS       1

/** The desired logical block has no current physical mapping. */
#define NAND_ERROR_BLOCKNOTMAPPED     2

/** Access if out-of-bounds. */
#define NAND_ERROR_OUTOFBOUNDS        3

/** There are no block having the desired property. */
#define NAND_ERROR_NOBLOCKFOUND       4

/** The NANDFLASH device has no logical mapping information on it. */
#define NAND_ERROR_MAPPINGNOTFOUND    5

/** A read operation cannot be carried out. */
#define NAND_ERROR_CANNOTREAD         6

/** A write operation cannot be carried out. */
#define NAND_ERROR_CANNOTWRITE        7

/** NandFlash chip model cannot be recognized. */
#define NAND_ERROR_UNKNOWNMODEL       8

/** Page data is corrupted according to ECC */
#define NAND_ERROR_CORRUPTEDDATA      9

/** Block is not in the required status. */
#define NAND_ERROR_WRONGSTATUS        10

/** Device has no logical mapping stored in it */
#define NAND_ERROR_NOMAPPING          11

/** The block being accessed is bad and must be replaced */
#define NAND_ERROR_BADBLOCK           12

/** Failed to perform an erase operation */
#define NAND_ERROR_CANNOTERASE        13

/** A hardware copy-back operation failed. */
#define NAND_ERROR_CANNOTCOPY         14

/** HW ECC Not compatible with the NAND Model */
#define NAND_ERROR_ECC_NOT_COMPATIBLE 15

/** DMA failed. */
#define NAND_ERROR_DMA                16

/** DMA failed. */
#define NAND_ERROR_STATUS             17

/** Invalid argument. */
#define NAND_ERROR_INVALID_ARG        18


/**@}*/
/**@}*/

#endif /* NAND_FLASH_COMMON_H */
