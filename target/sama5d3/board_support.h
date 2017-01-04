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

/**
 * \file
 *
 * Interface for memories configuration on board.
 *
 */

#ifndef BOARD_SUPPORT_H
#define BOARD_SUPPORT_H

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/* \brief Return a string containing the board name
 * \return the board name
 */
extern const char* get_board_name(void);

/**
 * \brief Configure the board master clock using PMC
 */
extern void board_cfg_clocks(void);

/**
 * \brief Performs the low-level initialization of the chip.
 *
 * This includes watchdog, master clock, AIC, DDRAM and MMU.
 */
extern void board_cfg_lowlevel(bool clocks, bool ddram, bool mmu);

/**
 * \brief Configure the system timer
 */
extern void board_cfg_timer(void);

/**
 * \brief Configure the board console if any
 * \param baudrate Requested baudrate, or board default if 0
 */
extern void board_cfg_console(uint32_t baudrate);

/**
 * \brief Restore all IOs to default state after power-on reset.
 */
extern void board_restore_pio_reset_state(void);

/**
 * \brief Save power by disabling most peripherals
 */
extern void board_save_misc_power(void);

/**
 * \brief Setup MMU for the board
 */
extern void board_cfg_mmu(void);

/**
 * \brief Configures L2CC for the board
 */
extern void board_cfg_l2cc(void);

/**
 * \brief Configure the MATRIX for DDR
 */
extern void board_cfg_matrix_for_ddr(void);

/**
 * \brief Configure the MATRIX for NAND
 */
extern void board_cfg_matrix_for_nand(void);

/**
 * \brief Configures DDR (calls board_cfg_matrix_for_ddr)
 */
extern void board_cfg_ddram(void);

/**
 * \brief Configures the EBI for nandflash access (calls
 * board_cfg_matrix_for_nand)
 */
extern void board_cfg_nand_flash(void);

/**
 * \brief Configures the EBI for norflash access.
 */
extern void board_cfg_nor_flash(void);

/**
 * \brief Configures the PMIC
 */
extern void board_cfg_pmic(void);

/**
 * \brief Configures the board.
 */
extern void board_init(void);

/**
 * \brief Configure a SD/MMC slot of the board
 * \param hsmci_id  HSMCI peripheral ID (ID_HSMCIx).
 * \note The application shall have enabled the clocks assigned to this HSMCI
 * peripheral.
 * \return true if successful, false if the specified peripheral could not be
 * initialized.
 */
extern bool board_cfg_sdmmc(uint32_t hsmci_id);

/**
 * \brief Detect whether or not a card is inserted into the specified SD/MMC
 * slot of the board
 * \param hsmci_id  HSMCI peripheral ID (ID_HSMCIx).
 * \return true if a card is inserted, false if no card is inserted.
 * \note board_cfg_sdmmc() must have been called prior to using this function.
 */
extern bool board_is_sdmmc_inserted(uint32_t hsmci_id);

/**
 * \brief Power ON/OFF the SD/MMC device connected to the specified slot
 * \param hsmci_id  HSMCI peripheral ID (ID_HSMCIx).
 * \param on  true to power the device ON, false to power it OFF.
 * \return true if successful, false if the specified peripheral could not be
 * controlled.
 * \note board_cfg_sdmmc() must have been called prior to using this function.
 * When powering the device OFF it may still be powered upon return of this
 * function by a residual charge in the capacitors.
*/
extern bool board_power_sdmmc_device(uint32_t hsmci_id, bool on);

#endif /* #ifndef BOARD_SUPPORT_H */
