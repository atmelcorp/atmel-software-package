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
*  \file
*
*  Definitions and function prototype for SMC NFC module
*/

#ifndef NFC_H_
#define NFC_H_

#ifdef CONFIG_HAVE_NFC

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

#include <stdbool.h>
#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

extern void nfc_configure(uint32_t data_size, uint32_t spare_size,
		bool read_spare, bool write_spare);

extern void nfc_enable(void);

extern void nfc_disable(void);

extern uint32_t nfc_get_status(void);

extern void nfc_send_cmd(uint32_t cmd, uint8_t *cycle_bytes);

extern void nfc_wait_cmd_done(void);

extern void nfc_wait_xfr_done(void);

extern void nfc_wait_rb_busy(void);

#ifdef CONFIG_HAVE_SMC_SCRAMBLING

/**
 * \brief Enables scrambling of NFC SRAM
 */
extern void nfc_sram_scrambling_enable(void);

/**
 * \brief Disables scrambling of NFC SRAM
 */
extern void nfc_sram_scrambling_disable(void);

/**
 * \brief Check if scrambling for NAND FLASH is enabled.
 * \return true if NFC SRAM scrambling is enabled, false otherwise
 */
extern bool nfc_sram_scrambling_is_enabled(void);

#endif /* CONFIG_HAVE_SMC_SCRAMBLING */

#endif /* CONFIG_HAVE_NFC */

#endif /* NFC_H_ */
