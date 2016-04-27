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

/** \file */

/** \addtogroup hsmci_module Working with HSMCI
 *  \ingroup mcid_module
 *
 * \section Purpose
 *
 * The HSMCIC driver is a C wrapper to the User Interface of the HSMCI
 * peripheral.
 *
 * \section Usage
 *
 * -# hsmci_enable(), hsmci_disable(): Enable/Disable HSMCI interface.
 * -# hsmci_reset(): Reset HSMCI interface.
 * -# hsmci_select(): HSMCI slot and buswidth selection
 *                    (\ref Hsmci::HSMCI_SDCR).
 * -# hsmci_cfg_mode(): Configure the  MCI CLKDIV in the _MR register
 *                      (\ref Hsmci::HSMCI_MR).
 * -# hsmci_enable_it(), hsmci_disable_it(), hsmci_get_it_mask(),
 *    hsmci_get_status(): HSMCI Interrupt control (\ref Hsmci::HSMCI_IER,
 *                        \ref Hsmci::HSMCI_IDR, \ref Hsmci::HSMCI_IMR,
 *                        \ref Hsmci::HSMCI_SR).
 * -# hsmci_cfg_xfer(): Setup block length and count for MCI transfer
 *                      (\ref Hsmci::HSMCI_BLKR).
 * -# hsmci_send_cmd(): Send SD/MMC command with argument
 *                     (\ref Hsmci::HSMCI_ARGR, \ref Hsmci::HSMCI_CMDR).
 * -# hsmci_get_response(): Get SD/MMC response after command finished
 *                         (\ref Hsmci::HSMCI_RSPR).
 * -# hsmci_cfg_dma(): Configure MCI DMA transfer
 *                     (\ref Hsmci::HSMCI_DMA).
 * -# hsmci_configure(): Configure the HSMCI interface (\ref Hsmci::HSMCI_CFG).
 * -# hsmci_hs_enable(), hsmci_is_hs_enabled(): High Speed control.
 *
 * For more accurate information, please look at the HSMCI section of the
 * Datasheet.
 *
 * \sa \ref mcid_module
 *
 * Related files:\n
 * \ref hsmcic.h\n
 * \ref hsmcic.c.\n
 */

#ifndef _HSMCIC_PERIPH_H_
#define _HSMCIC_PERIPH_H_
/** \addtogroup hsmci_module
 * @{
 */

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/
/** \addtogroup hsmci_functions HSMCI Functions
 *      @{
 */

/**
 * \brief Enable Multi-Media Interface
 * \param regs		Pointer to an Hsmci instance
 */
extern void hsmci_enable(Hsmci * regs);

/**
 * \brief Disable Multi-Media Interface
 * \param regs		Pointer to an Hsmci instance
 */
extern void hsmci_disable(Hsmci * regs);

/**
 * \brief Reset and disable Multi-Media Interface
 * \param regs		Pointer to an Hsmci instance
 * \param backup	Restore the previous value of selected registers,
 *			notably MR, SDCR, DTOR, CSTOR, DMA and CFG.
 */
extern void hsmci_reset(Hsmci * regs, bool backup);

/**
 * \brief Select slot
 * \param regs		Pointer to an Hsmci instance
 * \param bSlot		Slot ID (0~3 for A~D)
 * \param bBusWidth	Bus width: 1, 4 or 8 bits
 */
extern void hsmci_select(Hsmci * regs, uint8_t bSlot, uint8_t bBusWidth);

/**
 * \brief Set slot
 * \param regs		Pointer to an Hsmci instance
 * \param bSlot		Slot ID (0~3 for A~D)
 */
extern void hsmci_set_slot(Hsmci * regs, uint8_t bSlot);

/**
 * \brief Set bus width of MCI
 * \param regs		Pointer to an Hsmci instance
 * \param bBusWidth	Bus width: 1, 4 or 8 bits
 */
extern void hsmci_set_bus_width(Hsmci * regs, uint8_t bBusWidth);

/**
 * \brief Get current bus width
 * \param regs		Pointer to an Hsmci instance
 * \return bus width: 1, 4 or 8 bits.
 */
extern uint8_t hsmci_get_bus_width(const Hsmci * regs);

/**
 * \brief Configures a MCI peripheral as specified
 * \param regs		Pointer to an Hsmci instance
 * \param dwMode	Value of the Mode Register
 */
extern void hsmci_cfg_mode(Hsmci * regs, uint32_t dwMode);

/**
 * \brief Get Mode Register
 * \param regs		Pointer to an Hsmci instance
 * \return the contents of the Mode Register.
 */
extern uint32_t hsmci_get_mode(const Hsmci * regs);

/**
 * \brief Enable/Disable R/W proof
 * \param regs		Pointer to an Hsmci instance
 * \param rd_proof	Read proof enable/disable
 * \param wr_proof	Write proof enable/disable
 */
extern void hsmci_proof_enable(Hsmci * regs, bool rd_proof,
                               bool wr_proof);

/**
 * \brief Select the data pattern appended to written data
 * \param regs		Pointer to an Hsmci instance
 * \param bPadv		Padding value 0xFF/0x00
 */
extern void hsmci_set_pad_pattern(Hsmci * regs, uint8_t bPadv);

/**
 * \brief Force byte transfer enable/disable
 * \param regs		Pointer to an Hsmci instance
 * \param xfer_bytes	FBYTE enable/disable
 */
extern void hsmci_xfer_bytes(Hsmci * regs, bool xfer_bytes);

/**
 * \brief Check if Force Byte mode enabled
 * \param regs		Pointer to an Hsmci instance
 * \return true if FBYTE is enabled.
 */
extern bool hsmci_is_xfer_in_bytes(const Hsmci * regs);

/**
 * \brief Set Clock Divider & Power save divider for MCI
 * \param regs		Pointer to an Hsmci instance.
 * \param bClkDiv	Clock Divider value (0 ~ 255)
 * \param bPwsDiv	Power Saving Divider (1 ~ 7)
 */
extern void hsmci_set_clock(Hsmci * regs, uint32_t bClkDiv, uint8_t bPwsDiv);

/**
 * \brief Enables one or more interrupt sources of MCI peripheral
 * \param regs		Pointer to an Hsmci instance
 * \param dwSources	Bitwise OR of selected interrupt sources
 */
extern void hsmci_enable_it(Hsmci * regs, uint32_t dwSources);

/**
 * \brief Disable one or more interrupt sources of MCI peripheral
 * \param regs		Pointer to an Hsmci instance
 * \param dwSources	Bitwise OR of selected interrupt sources
 */
extern void hsmci_disable_it(Hsmci * regs, uint32_t dwSources);

/**
 * \brief Get the interrupt mask register
 * \param regs		Pointer to an Hsmci instance
 * \return the contents of the interrupt mask register.
 */
extern uint32_t hsmci_get_it_mask(const Hsmci * regs);

/**
 * \brief Set block len & count for transfer
 * \param regs		Pointer to an Hsmci instance
 * \param wBlkLen	Block size
 * \param wCnt		Block (byte) count
 */
extern void hsmci_cfg_xfer(Hsmci * regs, uint16_t wBlkLen,
                           uint16_t wCnt);

/**
 * \brief Set block length
 * \param regs		Pointer to an Hsmci instance
 * \param wBlkSize	Block size
 * \note Count is reset to 0.
 */
extern void hsmci_set_block_len(Hsmci * regs, uint16_t wBlkSize);

/**
 * \brief Set block (byte) count
 * \param regs		Pointer to an Hsmci instance
 * \param wBlkCnt	Block (byte) count
 */
extern void hsmci_set_block_count(Hsmci * regs, uint16_t wBlkCnt);

/**
 * \brief Configure the Completion Signal Timeout
 * \param regs		Pointer to an Hsmci instance
 * \param dwConfigure	Completion Signal Timeout configure
 */
extern void hsmci_cfg_compl_timeout(Hsmci * regs, uint32_t dwConfigure);

/**
 * \brief Configure the Data Timeout
 * \param regs		Pointer to an Hsmci instance
 * \param dwConfigure	Data Timeout configure
 */
extern void hsmci_cfg_data_timeout(Hsmci * regs, uint32_t dwConfigure);

/**
 * \brief Send command
 * \param regs		Pointer to an Hsmci instance
 * \param dwCmd		Command register value
 * \param dwArg		Argument register value
 */
extern void hsmci_send_cmd(Hsmci * regs, uint32_t dwCmd, uint32_t dwArg);

/**
 * \brief Get the Response Register
 * \param regs		Pointer to an Hsmci instance
 * \return the contents of the Response Register.
 */
extern uint32_t hsmci_get_response(const Hsmci * regs);

/**
 * \brief Get the receive data register
 * \param regs		Pointer to an Hsmci instance
 * \return the contents of the receive data register.
 */
extern uint32_t hsmci_read(const Hsmci * regs);

/**
 * \brief Read from FIFO
 * \param regs		Pointer to an Hsmci instance
 * \param pdwData	Pointer to data buffer
 * \param dwSize	Size of data buffer (in DWord)
 */
extern void hsmci_read_fifo(const Hsmci * regs, uint8_t * pdwData,
                            uint32_t dwSize);

/**
 * \brief Sends data through MCI peripheral
 * \param regs		Pointer to an Hsmci instance
 * \param dwData	Data to transmit
 */
extern void hsmci_write(Hsmci * regs, uint32_t dwData);

/**
 * \brief Write to FIFO
 * \param regs		Pointer to an Hsmci instance
 * \param pdwData	Pointer to data buffer
 * \param dwSize	Size of data buffer (In DWord)
 */
extern void hsmci_write_fifo(Hsmci * regs, const uint8_t * pdwData,
                             uint32_t dwSize);

/**
 * \brief Get the status register
 * \param regs		Pointer to an Hsmci instance
 * \return the contents of the status register.
 */
extern uint32_t hsmci_get_status(const Hsmci * regs);

/**
 * \brief Configure the HSMCI DMA
 * \param regs		Pointer to an Hsmci instance
 * \param dwConfigure	Configure value
 */
extern void hsmci_cfg_dma(Hsmci * regs, uint32_t dwConfigure);

/**
 * \brief Enable the HSMCI DMA
 * \param regs		Pointer to an Hsmci instance
 * \param use_dma	Enable/disable DMA
 */
extern void hsmci_enable_dma(Hsmci * regs, bool use_dma);

/**
 * \brief Configure the HSMCI
 * \param regs		Pointer to an Hsmci instance
 * \param dwConfigure	Configure value
 */
extern void hsmci_configure(Hsmci * regs, uint32_t dwConfigure);

/**
 * \brief Enable/Disable High-Speed mode for MCI
 * \param regs		Pointer to an Hsmci instance
 * \param high_spd	Enable/disable high-speed mode
 */
extern void hsmci_enable_hs(Hsmci * regs, bool high_spd);

/**
 * \brief Check if high-speed mode is enabled on MCI
 * \param regs		Pointer to an Hsmci instance
 * \return true if high-speed mode is enabled
 */
extern bool hsmci_is_hs_enabled(const Hsmci * regs);

/**
 * \brief Configure the Write Protection Mode
 * \param regs		Pointer to an Hsmci instance
 * \param dwConfigure	WP mode configure value
 */
extern void hsmci_cfg_wp(Hsmci * regs, uint32_t dwConfigure);

/**
 * \brief Get the write protect status register
 * \param regs		Pointer to an Hsmci instance
 * \return the contents of the write protect status register.
 */
extern uint32_t hsmci_get_wp_status(const Hsmci * regs);

/**      @} */

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* #ifndef _HSMCIC_PERIPH_H_ */
