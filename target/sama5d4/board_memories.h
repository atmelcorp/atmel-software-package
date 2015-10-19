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
 * \file
 *
 * Interface for memories configuration on board.
 *
 */

#ifndef BOARD_MEMORIES_H
#define BOARD_MEMORIES_H

#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Setup TLB for the board
 */
extern void board_setup_tlb(uint32_t *tlb);

/**
 * \brief Configures L2CC for the board
 */
extern void board_cfg_l2cc(void);

/**
 * \brief Initialize Vdd EBI drive
 * \param VddMemSel 0: 1.8V 1: 3.3V
 */
extern void board_cfg_vdd_mem_sel(uint8_t VddMemSel);

/**
 * \brief Configures DDR
 */
extern void board_cfg_ddram(void);

/**
 * \brief Configures the EBI for Sdram (LPSDR Micron MT48H8M16) access.
 */
extern void board_cfg_sdram(void);

/**
 * \brief Configures the EBI for NandFlash access at 133Mhz.
 */
extern void board_cfg_nand_flash(uint8_t busWidth);

/**
 * \brief Configure SMC, NCS0 is assigned to a norflash.
 */
extern void board_cfg_nor_flash(uint8_t busWidth);

#endif /* #ifndef BOARD_MEMORIES_H */
