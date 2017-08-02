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

#ifndef NAND_FLASH_COMMANDS_H
#define NAND_FLASH_COMMANDS_H

/*------------------------------------------------------------------------------ */
/*         Headers                                                               */
/*------------------------------------------------------------------------------ */

#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** NANDFLASH commands */

#define NAND_CMD_READ_1             0x00
#define NAND_CMD_READ_2             0x30
#define NAND_CMD_READ_A             0x00
#define NAND_CMD_READ_C             0x50
#define NAND_CMD_COPYBACK_READ_1    0x00
#define NAND_CMD_COPYBACK_READ_2    0x35
#define NAND_CMD_COPYBACK_PROGRAM_1 0x85
#define NAND_CMD_COPYBACK_PROGRAM_2 0x10
#define NAND_CMD_RANDOM_OUT         0x05
#define NAND_CMD_RANDOM_OUT_2       0xE0
#define NAND_CMD_RANDOM_IN          0x85
#define NAND_CMD_READID             0x90
#define NAND_CMD_WRITE_1            0x80
#define NAND_CMD_WRITE_2            0x10
#define NAND_CMD_ERASE_1            0x60
#define NAND_CMD_ERASE_2            0xD0
#define NAND_CMD_STATUS             0x70
#define NAND_CMD_READ_PARAM_PAGE    0xEC
#define NAND_CMD_GET_FEATURES       0xEE
#define NAND_CMD_SET_FEATURES       0xEF
#define NAND_CMD_RESET              0xFF

/** NANDFLASH status bit mask */
#define NAND_STATUS_FAIL  (1 << 0)
#define NAND_STATUS_FAILC (1 << 1)
#define NAND_STATUS_ARDY  (1 << 5)
#define NAND_STATUS_RDY   (1 << 6)

#endif /* NAND_FLASH_COMMANDS_H */
