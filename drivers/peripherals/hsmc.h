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
*  Definitions and function prototype for smc module
*/

#ifndef _HSMC_
#define _HSMC_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

#include <stdbool.h>
#include <stdint.h>

/*----------------------------------------------------------------------------
 *         Macros
 *----------------------------------------------------------------------------*/

#define hsmc_nfc_enable()              {HSMC->HSMC_CTRL |= HSMC_CTRL_NFCEN;}
#define hsmc_nfc_disable()             {HSMC->HSMC_CTRL |= HSMC_CTRL_NFCDIS;}
#define hsmc_nfc_get_status()          {HSMC->HSMC_SR;}

#define hsmc_nfc_enable_spare_read()   {HSMC->HSMC_CFG |= HSMC_CFG_RSPARE;}
#define hsmc_nfc_disable_spare_read()  {HSMC->HSMC_CFG &= (~HSMC_CFG_RSPARE);}
#define hsmc_nfc_enable_spare_write()  {HSMC->HSMC_CFG |= HSMC_CFG_WSPARE;}
#define hsmc_nfc_disable_spare_write() {HSMC->HSMC_CFG &= (~HSMC_CFG_WSPARE);}

#define hsmc_pmecc_reset()             {HSMC->HSMC_PMECCTRL = HSMC_PMECCTRL_RST; }
#define hsmc_pmecc_or_reset()          {HSMC->HSMC_PMECCTRL |= HSMC_PMECCTRL_RST; }
#define hsmc_pmecc_data_phase()        {HSMC->HSMC_PMECCTRL |= HSMC_PMECCTRL_DATA; }
#define hsmc_pmecc_enable_write()      {HSMC->HSMC_PMECCFG |= HSMC_PMECCFG_NANDWR;}
#define hsmc_pmecc_enable_read()       {HSMC->HSMC_PMECCFG &= (~HSMC_PMECCFG_NANDWR);}
 
#define hsmc_pmecc_error_status()      (HSMC->HSMC_PMECCISR )
#define hsmc_pmecc_enable()            {HSMC->HSMC_PMECCTRL = HSMC_PMECCTRL_ENABLE;}
#define hsmc_pmecc_disable()           {HSMC->HSMC_PMECCTRL = HSMC_PMECCTRL_DISABLE;}
#define hsmc_pmecc_auto_enable()       {HSMC->HSMC_PMECCFG |= HSMC_PMECCFG_AUTO;}
#define hsmc_pmecc_auto_disable()      {HSMC->HSMC_PMECCFG &= (~HSMC_PMECCFG_AUTO);}
#define hsmc_pmecc_auto_apare_en()     ((HSMC->HSMC_PMECCFG & HSMC_PMECCFG_SPAREEN) == HSMC_PMECCFG_SPAREEN) 
#define hsmc_pmecc(i)                  (HSMC->SMC_PMECC[i])

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

#define HSMC_SR_RB_EDGE0     (0x1u << 24)

/* -------- NFCADDR_CMD : NFC Address Command -------- */

#define NFCADDR_CMD_CMD1_Pos 2
#define NFCADDR_CMD_CMD1_Msk (0xFFu << NFCADDR_CMD_CMD1_Pos) /**< \brief (NFCADDR_CMD) Command Register Value for Cycle 1 */
#define NFCADDR_CMD_CMD1(value) ((NFCADDR_CMD_CMD1_Msk & ((value) << NFCADDR_CMD_CMD1_Pos)))
#define NFCADDR_CMD_CMD2_Pos 10
#define NFCADDR_CMD_CMD2_Msk (0xFFu << NFCADDR_CMD_CMD2_Pos) /**< \brief (NFCADDR_CMD) Command Register Value for Cycle 2 */
#define NFCADDR_CMD_CMD2(value) ((NFCADDR_CMD_CMD2_Msk & ((value) << NFCADDR_CMD_CMD2_Pos)))
#define NFCADDR_CMD_VCMD2 (0x1u << 18) /**< (NFCADDR_CMD) Valid Cycle 2 Command */
#define NFCADDR_CMD_ACYCLE_Pos 19
#define NFCADDR_CMD_ACYCLE_Msk (0x7u << NFCADDR_CMD_ACYCLE_Pos) /**< \brief (NFCADDR_CMD) Number of Address cycles required for the current command */
#define NFCADDR_CMD_ACYCLE(value) ((NFCADDR_CMD_ACYCLE_Msk & ((value) << NFCADDR_CMD_ACYCLE_Pos)))
#define   NFCADDR_CMD_ACYCLE_NONE (0x0u << 19) /**< \brief (NFCADDR_CMD) No address cycle */
#define   NFCADDR_CMD_ACYCLE_ONE (0x1u << 19) /**< \brief (NFCADDR_CMD) One address cycle */
#define   NFCADDR_CMD_ACYCLE_TWO (0x2u << 19) /**< \brief (NFCADDR_CMD) Two address cycles */
#define   NFCADDR_CMD_ACYCLE_THREE (0x3u << 19) /**< \brief (NFCADDR_CMD) Three address cycles */
#define   NFCADDR_CMD_ACYCLE_FOUR (0x4u << 19) /**< \brief (NFCADDR_CMD) Four address cycles */
#define   NFCADDR_CMD_ACYCLE_FIVE (0x5u << 19) /**< \brief (NFCADDR_CMD) Five address cycles */
#define NFCADDR_CMD_CSID_Pos 22
#define NFCADDR_CMD_CSID_Msk (0x7u << NFCADDR_CMD_CSID_Pos) /**< \brief (NFCADDR_CMD) Chip Select Identifier */
#define NFCADDR_CMD_CSID(value) ((NFCADDR_CMD_CSID_Msk & ((value) << NFCADDR_CMD_CSID_Pos)))
#define   NFCADDR_CMD_CSID_0 (0x0u << 22) /**< \brief (NFCADDR_CMD) CS0 */
#define   NFCADDR_CMD_CSID_1 (0x1u << 22) /**< \brief (NFCADDR_CMD) CS1 */
#define   NFCADDR_CMD_CSID_2 (0x2u << 22) /**< \brief (NFCADDR_CMD) CS2 */
#define   NFCADDR_CMD_CSID_3 (0x3u << 22) /**< \brief (NFCADDR_CMD) CS3 */
#define   NFCADDR_CMD_CSID_4 (0x4u << 22) /**< \brief (NFCADDR_CMD) CS4 */
#define   NFCADDR_CMD_CSID_5 (0x5u << 22) /**< \brief (NFCADDR_CMD) CS5 */
#define   NFCADDR_CMD_CSID_6 (0x6u << 22) /**< \brief (NFCADDR_CMD) CS6 */
#define   NFCADDR_CMD_CSID_7 (0x7u << 22) /**< \brief (NFCADDR_CMD) CS7 */
#define NFCADDR_CMD_DATAEN (0x1u << 25) /**< \brief (NFCADDR_CMD) NFC Data Enable */
#define NFCADDR_CMD_NFCWR (0x1u << 26) /**< \brief (NFCADDR_CMD) NFC Write Enable */

/* -------- NFCDATA_ADDR : NFC Data Address -------- */

#define NFCDATA_ADDR_ACYCLE1_Pos 0
#define NFCDATA_ADDR_ACYCLE1_Msk (0xffu << NFCDATA_ADDR_ACYCLE1_Pos) /**< \brief (NFCDATA_ADDR) NAND Flash Array Address Cycle 1 */
#define NFCDATA_ADDR_ACYCLE1(value) ((NFCDATA_ADDR_ACYCLE1_Msk & ((value) << NFCDATA_ADDR_ACYCLE1_Pos)))
#define NFCDATA_ADDR_ACYCLE2_Pos 8
#define NFCDATA_ADDR_ACYCLE2_Msk (0xffu << NFCDATA_ADDR_ACYCLE2_Pos) /**< \brief (NFCDATA_ADDR) NAND Flash Array Address Cycle 2 */
#define NFCDATA_ADDR_ACYCLE2(value) ((NFCDATA_ADDR_ACYCLE2_Msk & ((value) << NFCDATA_ADDR_ACYCLE2_Pos)))
#define NFCDATA_ADDR_ACYCLE3_Pos 16
#define NFCDATA_ADDR_ACYCLE3_Msk (0xffu << NFCDATA_ADDR_ACYCLE3_Pos) /**< \brief (NFCDATA_ADDR) NAND Flash Array Address Cycle 3 */
#define NFCDATA_ADDR_ACYCLE3(value) ((NFCDATA_ADDR_ACYCLE3_Msk & ((value) << NFCDATA_ADDR_ACYCLE3_Pos)))
#define NFCDATA_ADDR_ACYCLE4_Pos 24
#define NFCDATA_ADDR_ACYCLE4_Msk (0xffu << NFCDATA_ADDR_ACYCLE4_Pos) /**< \brief (NFCDATA_ADDR) NAND Flash Array Address Cycle 4 */
#define NFCDATA_ADDR_ACYCLE4(value) ((NFCDATA_ADDR_ACYCLE4_Msk & ((value) << NFCDATA_ADDR_ACYCLE4_Pos)))

/* -------- NFCDATA_STATUS : NFC Data Status -------- */

#define NFCDATA_STATUS_CMD1_Pos 2
#define NFCDATA_STATUS_CMD1_Msk (0xFFu << NFCDATA_STATUS_CMD1_Pos) /**< \brief (NFCDATA_STATUS) Command Register Value for Cycle 1 */
#define NFCDATA_STATUS_CMD1(value) ((NFCDATA_STATUS_CMD1_Msk & ((value) << NFCDATA_STATUS_CMD1_Pos)))
#define NFCDATA_STATUS_CMD2_Pos 10
#define NFCDATA_STATUS_CMD2_Msk (0xFFu << NFCDATA_STATUS_CMD2_Pos) /**< \brief (NFCDATA_STATUS) Command Register Value for Cycle 2 */
#define NFCDATA_STATUS_CMD2(value) ((NFCDATA_STATUS_CMD2_Msk & ((value) << NFCDATA_STATUS_CMD2_Pos)))
#define NFCDATA_STATUS_VCMD2 (0x1u << 18) /**< (NFCDATA_STATUS) Valid Cycle 2 Command */
#define NFCDATA_STATUS_ACYCLE_Pos 19
#define NFCDATA_STATUS_ACYCLE_Msk (0x7u << NFCDATA_STATUS_ACYCLE_Pos) /**< \brief (NFCDATA_STATUS) Number of Address cycles required for the current command */
#define NFCDATA_STATUS_ACYCLE(value) ((NFCDATA_STATUS_ACYCLE_Msk & ((value) << NFCDATA_STATUS_ACYCLE_Pos)))
#define   NFCDATA_STATUS_ACYCLE_NONE (0x0u << 19) /**< \brief (NFCDATA_STATUS) No address cycle */
#define   NFCDATA_STATUS_ACYCLE_ONE (0x1u << 19) /**< \brief (NFCDATA_STATUS) One address cycle */
#define   NFCDATA_STATUS_ACYCLE_TWO (0x2u << 19) /**< \brief (NFCDATA_STATUS) Two address cycles */
#define   NFCDATA_STATUS_ACYCLE_THREE (0x3u << 19) /**< \brief (NFCDATA_STATUS) Three address cycles */
#define   NFCDATA_STATUS_ACYCLE_FOUR (0x4u << 19) /**< \brief (NFCDATA_STATUS) Four address cycles */
#define   NFCDATA_STATUS_ACYCLE_FIVE (0x5u << 19) /**< \brief (NFCDATA_STATUS) Five address cycles */
#define NFCDATA_STATUS_CSID_Pos 22
#define NFCDATA_STATUS_CSID_Msk (0x7u << NFCDATA_STATUS_CSID_Pos) /**< \brief (NFCDATA_STATUS) Chip Select Identifier */
#define NFCDATA_STATUS_CSID(value) ((NFCDATA_STATUS_CSID_Msk & ((value) << NFCDATA_STATUS_CSID_Pos)))
#define   NFCDATA_STATUS_CSID_0 (0x0u << 22) /**< \brief (NFCDATA_STATUS) CS0 */
#define   NFCDATA_STATUS_CSID_1 (0x1u << 22) /**< \brief (NFCDATA_STATUS) CS1 */
#define   NFCDATA_STATUS_CSID_2 (0x2u << 22) /**< \brief (NFCDATA_STATUS) CS2 */
#define   NFCDATA_STATUS_CSID_3 (0x3u << 22) /**< \brief (NFCDATA_STATUS) CS3 */
#define   NFCDATA_STATUS_CSID_4 (0x4u << 22) /**< \brief (NFCDATA_STATUS) CS4 */
#define   NFCDATA_STATUS_CSID_5 (0x5u << 22) /**< \brief (NFCDATA_STATUS) CS5 */
#define   NFCDATA_STATUS_CSID_6 (0x6u << 22) /**< \brief (NFCDATA_STATUS) CS6 */
#define   NFCDATA_STATUS_CSID_7 (0x7u << 22) /**< \brief (NFCDATA_STATUS) CS7 */
#define NFCDATA_STATUS_DATAEN (0x1u << 25) /**< \brief (NFCDATA_STATUS) NFC Data Enable */
#define NFCDATA_STATUS_NFCWR (0x1u << 26) /**< \brief (NFCDATA_STATUS) NFC Write Enable */
#define NFCDATA_STATUS_NFCBUSY (0x1u << 27) /**< \brief (NFCDATA_STATUS) NFC Busy Status Flag */

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

extern void hsmc_nand_configure(uint8_t bus_width);

extern void hsmc_nor_configure(uint8_t cs, uint8_t bus_width);

extern void hsmc_nfc_configure(uint32_t data_size, uint32_t spare_size,
		bool read_spare, bool write_spare);

extern void hsmc_nfc_reset(void);

extern bool hsmc_nfc_is_spare_read_enabled(void);

extern bool hsmc_nfc_is_spare_write_enabled(void);

extern bool hsmc_nfc_is_nfc_busy(void);

extern void hsmc_wait_rb(void);

extern void hsmc_nfc_send_cmd(uint32_t cmd, uint8_t *cycle_bytes);

extern void hsmc_nfc_wait_cmd_done(void);

extern void hsmc_nfc_wait_xfr_done(void);

extern void hsmc_nfc_wait_rb_busy(void);

extern void hsmc_nfc_wait_hamming_ready(void);

extern void hsmc_pmecc_wait_ready(void);

#endif /* _HSMC_ */
