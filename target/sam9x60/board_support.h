/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2018, Atmel Corporation
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

#ifndef BOARD_SUPPORT_H
#define BOARD_SUPPORT_H

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Functions
 *----------------------------------------------------------------------------*/

/* \brief Return a string containing the board name
 * \return the board name
 */
extern const char* get_board_name(void);

/**
 *\brief Configure the board master clock using PMC base on selected preset
 */
extern void board_cfg_clocks_for_preset(uint32_t preset);

/**
 * \brief Configure the board master clock using PMC
 */
extern void board_cfg_clocks(void);

/**
 * \brief Performs the low-level initialization of the chip.
 *
 * This includes watchdog, master clock, AIC, timer, DDRAM and MMU.
 */
extern void board_cfg_lowlevel(bool clocks, bool ddram, bool mmu);

/**
 * \brief 
 */
extern void board_restore_pio_reset_state(void);

/*
 * \brief Save power by disabling most peripherals
 */
extern void board_save_misc_power(void);

/**
 * \brief Setup MMU for the board
 */
extern void board_cfg_mmu(void);

/**
 * \brief Configure the MATRIX for DDR
 */
extern void board_cfg_matrix_for_ddr(void);

/**
 * \brief Configure the MATRIX for SDRAM
 */
extern void board_cfg_matrix_for_sdr(void);

/**
 * \brief Configure the MATRIX for NAND
 */
extern void board_cfg_matrix_for_nand(void);

/**
 * \brief Configure the MATRIX for NAND
 */
extern void board_cfg_matrix_for_nand_ex(bool nfd0_on_d16);

/**
 * \brief Configures DDR for the board (calls board_cfg_matrix_for_ddr)
 */
extern void board_cfg_ddram(void);

#ifdef CONFIG_HAVE_NAND_FLASH
/**
 * \brief Configures SMC for the board NAND flash (calls
 * board_cfg_matrix_for_nand).
 */
extern void board_cfg_nand_flash(void);
#endif /* CONFIG_HAVE_NAND_FLASH */

/**
 * \brief Configures a SD/MMC/e.MMC slot of the board
 * \param sdmmc_id  SDMMC peripheral ID (ID_SDMMCx).
 * \note The application shall have enabled the clocks assigned to this SDMMC
 * peripheral.
 * \return true if successful, false if the specified peripheral could not be
 * initialized.
 */
extern bool board_cfg_sdmmc(uint32_t sdmmc_id);

/**
 * \brief Detect whether or not a card is inserted into the specified SD/MMC
 * slot of the board
 * \param sdmmc_id  SDMMC peripheral ID (ID_SDMMCx).
 * \return true if a card is inserted, false if no card is inserted.
 * \note board_cfg_sdmmc() must have been called prior to using this function.
 */
extern bool board_get_sdmmc_card_detect_status(uint32_t sdmmc_id);

/**
 * \brief Configures the board.
 */
extern void board_init(void);

#endif  /* BOARD_SUPPORT_H */

