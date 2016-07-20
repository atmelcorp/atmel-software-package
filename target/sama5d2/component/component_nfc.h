/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2015, Atmel Corporation                                        */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Atmel's name may not be used to endorse or promote products derived from     */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR   */
/* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE   */
/* DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,      */
/* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,  */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    */
/* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING         */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/* ---------------------------------------------------------------------------- */

#ifndef _SAMA5D2_NFC_COMPONENT_
#define _SAMA5D2_NFC_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Static Memory Controller (NFC) */
/* ============================================================================= */
/** \addtogroup SAMA5D2_NFC Static Memory Controller (NFC) */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Nfc hardware registers */
typedef struct {
	__IO uint32_t NFC_CFG;  /**< \brief (Nfc Offset: 0x00) SMC NFC Configuration Register */
	__O  uint32_t NFC_CTRL; /**< \brief (Nfc Offset: 0x04) SMC NFC Control Register */
	__I  uint32_t NFC_SR;   /**< \brief (Nfc Offset: 0x08) SMC NFC Status Register */
	__O  uint32_t NFC_IER;  /**< \brief (Nfc Offset: 0x0C) SMC NFC Interrupt Enable Register */
	__O  uint32_t NFC_IDR;  /**< \brief (Nfc Offset: 0x10) SMC NFC Interrupt Disable Register */
	__I  uint32_t NFC_IMR;  /**< \brief (Nfc Offset: 0x14) SMC NFC Interrupt Mask Register */
	__IO uint32_t NFC_ADDR; /**< \brief (Nfc Offset: 0x18) SMC NFC Address Cycle Zero Register */
	__IO uint32_t NFC_BANK; /**< \brief (Nfc Offset: 0x1C) SMC NFC Bank Address Register */
} Nfc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- NFC_CFG : (NFC Offset: 0x00) SMC NFC Configuration Register -------- */
#define NFC_CFG_PAGESIZE_Pos 0
#define NFC_CFG_PAGESIZE_Msk (0x7u << NFC_CFG_PAGESIZE_Pos) /**< \brief (NFC_CFG) Page Size of the NAND Flash Device */
#define NFC_CFG_PAGESIZE(value) ((NFC_CFG_PAGESIZE_Msk & ((value) << NFC_CFG_PAGESIZE_Pos)))
#define   NFC_CFG_PAGESIZE_PS512 (0x0u << 0) /**< \brief (NFC_CFG) Main area 512 bytes */
#define   NFC_CFG_PAGESIZE_PS1024 (0x1u << 0) /**< \brief (NFC_CFG) Main area 1024 bytes */
#define   NFC_CFG_PAGESIZE_PS2048 (0x2u << 0) /**< \brief (NFC_CFG) Main area 2048 bytes */
#define   NFC_CFG_PAGESIZE_PS4096 (0x3u << 0) /**< \brief (NFC_CFG) Main area 4096 bytes */
#define   NFC_CFG_PAGESIZE_PS8192 (0x4u << 0) /**< \brief (NFC_CFG) Main area 8192 bytes */
#define NFC_CFG_WSPARE (0x1u << 8) /**< \brief (NFC_CFG) Write Spare Area */
#define NFC_CFG_RSPARE (0x1u << 9) /**< \brief (NFC_CFG) Read Spare Area */
#define NFC_CFG_EDGECTRL (0x1u << 12) /**< \brief (NFC_CFG) Rising/Falling Edge Detection Control */
#define NFC_CFG_RBEDGE (0x1u << 13) /**< \brief (NFC_CFG) Ready/Busy Signal Edge Detection */
#define NFC_CFG_DTOCYC_Pos 16
#define NFC_CFG_DTOCYC_Msk (0xfu << NFC_CFG_DTOCYC_Pos) /**< \brief (NFC_CFG) Data Timeout Cycle Number */
#define NFC_CFG_DTOCYC(value) ((NFC_CFG_DTOCYC_Msk & ((value) << NFC_CFG_DTOCYC_Pos)))
#define NFC_CFG_DTOMUL_Pos 20
#define NFC_CFG_DTOMUL_Msk (0x7u << NFC_CFG_DTOMUL_Pos) /**< \brief (NFC_CFG) Data Timeout Multiplier */
#define NFC_CFG_DTOMUL(value) ((NFC_CFG_DTOMUL_Msk & ((value) << NFC_CFG_DTOMUL_Pos)))
#define   NFC_CFG_DTOMUL_X1 (0x0u << 20) /**< \brief (NFC_CFG) DTOCYC */
#define   NFC_CFG_DTOMUL_X16 (0x1u << 20) /**< \brief (NFC_CFG) DTOCYC x 16 */
#define   NFC_CFG_DTOMUL_X128 (0x2u << 20) /**< \brief (NFC_CFG) DTOCYC x 128 */
#define   NFC_CFG_DTOMUL_X256 (0x3u << 20) /**< \brief (NFC_CFG) DTOCYC x 256 */
#define   NFC_CFG_DTOMUL_X1024 (0x4u << 20) /**< \brief (NFC_CFG) DTOCYC x 1024 */
#define   NFC_CFG_DTOMUL_X4096 (0x5u << 20) /**< \brief (NFC_CFG) DTOCYC x 4096 */
#define   NFC_CFG_DTOMUL_X65536 (0x6u << 20) /**< \brief (NFC_CFG) DTOCYC x 65536 */
#define   NFC_CFG_DTOMUL_X1048576 (0x7u << 20) /**< \brief (NFC_CFG) DTOCYC x 1048576 */
#define NFC_CFG_NFCSPARESIZE_Pos 24
#define NFC_CFG_NFCSPARESIZE_Msk (0x7fu << NFC_CFG_NFCSPARESIZE_Pos) /**< \brief (NFC_CFG) NAND Flash Spare Area Size Retrieved by the Host Controller */
#define NFC_CFG_NFCSPARESIZE(value) ((NFC_CFG_NFCSPARESIZE_Msk & ((value) << NFC_CFG_NFCSPARESIZE_Pos)))
/* -------- NFC_CTRL : (NFC Offset: 0x04) SMC NFC Control Register -------- */
#define NFC_CTRL_NFCEN (0x1u << 0) /**< \brief (NFC_CTRL) NAND Flash Controller Enable */
#define NFC_CTRL_NFCDIS (0x1u << 1) /**< \brief (NFC_CTRL) NAND Flash Controller Disable */
/* -------- NFC_SR : (NFC Offset: 0x08) SMC NFC Status Register -------- */
#define NFC_SR_SMCSTS (0x1u << 0) /**< \brief (NFC_SR) NAND Flash Controller Status (this field cannot be reset) */
#define NFC_SR_RB_RISE (0x1u << 4) /**< \brief (NFC_SR) Selected Ready Busy Rising Edge Detected */
#define NFC_SR_RB_FALL (0x1u << 5) /**< \brief (NFC_SR) Selected Ready Busy Falling Edge Detected */
#define NFC_SR_NFCBUSY (0x1u << 8) /**< \brief (NFC_SR) NFC Busy (this field cannot be reset) */
#define NFC_SR_NFCWR (0x1u << 11) /**< \brief (NFC_SR) NFC Write/Read Operation (this field cannot be reset) */
#define NFC_SR_NFCSID_Pos 12
#define NFC_SR_NFCSID_Msk (0x7u << NFC_SR_NFCSID_Pos) /**< \brief (NFC_SR) NFC Chip Select ID (this field cannot be reset) */
#define NFC_SR_XFRDONE (0x1u << 16) /**< \brief (NFC_SR) NFC Data Transfer Terminated */
#define NFC_SR_CMDDONE (0x1u << 17) /**< \brief (NFC_SR) Command Done */
#define NFC_SR_DTOE (0x1u << 20) /**< \brief (NFC_SR) Data Timeout Error */
#define NFC_SR_UNDEF (0x1u << 21) /**< \brief (NFC_SR) Undefined Area Error */
#define NFC_SR_AWB (0x1u << 22) /**< \brief (NFC_SR) Accessing While Busy */
#define NFC_SR_NFCASE (0x1u << 23) /**< \brief (NFC_SR) NFC Access Size Error */
#define NFC_SR_RB_EDGE0 (0x1u << 24) /**< \brief (NFC_SR) Ready/Busy Line 0 Edge Detected */
/* -------- NFC_IER : (NFC Offset: 0x0C) SMC NFC Interrupt Enable Register -------- */
#define NFC_IER_RB_RISE (0x1u << 4) /**< \brief (NFC_IER) Ready Busy Rising Edge Detection Interrupt Enable */
#define NFC_IER_RB_FALL (0x1u << 5) /**< \brief (NFC_IER) Ready Busy Falling Edge Detection Interrupt Enable */
#define NFC_IER_XFRDONE (0x1u << 16) /**< \brief (NFC_IER) Transfer Done Interrupt Enable */
#define NFC_IER_CMDDONE (0x1u << 17) /**< \brief (NFC_IER) Command Done Interrupt Enable */
#define NFC_IER_DTOE (0x1u << 20) /**< \brief (NFC_IER) Data Timeout Error Interrupt Enable */
#define NFC_IER_UNDEF (0x1u << 21) /**< \brief (NFC_IER) Undefined Area Access Interrupt Enable */
#define NFC_IER_AWB (0x1u << 22) /**< \brief (NFC_IER) Accessing While Busy Interrupt Enable */
#define NFC_IER_NFCASE (0x1u << 23) /**< \brief (NFC_IER) NFC Access Size Error Interrupt Enable */
#define NFC_IER_RB_EDGE0 (0x1u << 24) /**< \brief (NFC_IER) Ready/Busy Line 0 Interrupt Enable */
/* -------- NFC_IDR : (NFC Offset: 0x10) SMC NFC Interrupt Disable Register -------- */
#define NFC_IDR_RB_RISE (0x1u << 4) /**< \brief (NFC_IDR) Ready Busy Rising Edge Detection Interrupt Disable */
#define NFC_IDR_RB_FALL (0x1u << 5) /**< \brief (NFC_IDR) Ready Busy Falling Edge Detection Interrupt Disable */
#define NFC_IDR_XFRDONE (0x1u << 16) /**< \brief (NFC_IDR) Transfer Done Interrupt Disable */
#define NFC_IDR_CMDDONE (0x1u << 17) /**< \brief (NFC_IDR) Command Done Interrupt Disable */
#define NFC_IDR_DTOE (0x1u << 20) /**< \brief (NFC_IDR) Data Timeout Error Interrupt Disable */
#define NFC_IDR_UNDEF (0x1u << 21) /**< \brief (NFC_IDR) Undefined Area Access Interrupt Disable */
#define NFC_IDR_AWB (0x1u << 22) /**< \brief (NFC_IDR) Accessing While Busy Interrupt Disable */
#define NFC_IDR_NFCASE (0x1u << 23) /**< \brief (NFC_IDR) NFC Access Size Error Interrupt Disable */
#define NFC_IDR_RB_EDGE0 (0x1u << 24) /**< \brief (NFC_IDR) Ready/Busy Line 0 Interrupt Disable */
/* -------- NFC_IMR : (NFC Offset: 0x14) SMC NFC Interrupt Mask Register -------- */
#define NFC_IMR_RB_RISE (0x1u << 4) /**< \brief (NFC_IMR) Ready Busy Rising Edge Detection Interrupt Mask */
#define NFC_IMR_RB_FALL (0x1u << 5) /**< \brief (NFC_IMR) Ready Busy Falling Edge Detection Interrupt Mask */
#define NFC_IMR_XFRDONE (0x1u << 16) /**< \brief (NFC_IMR) Transfer Done Interrupt Mask */
#define NFC_IMR_CMDDONE (0x1u << 17) /**< \brief (NFC_IMR) Command Done Interrupt Mask */
#define NFC_IMR_DTOE (0x1u << 20) /**< \brief (NFC_IMR) Data Timeout Error Interrupt Mask */
#define NFC_IMR_UNDEF (0x1u << 21) /**< \brief (NFC_IMR) Undefined Area Access Interrupt Mask5 */
#define NFC_IMR_AWB (0x1u << 22) /**< \brief (NFC_IMR) Accessing While Busy Interrupt Mask */
#define NFC_IMR_NFCASE (0x1u << 23) /**< \brief (NFC_IMR) NFC Access Size Error Interrupt Mask */
#define NFC_IMR_RB_EDGE0 (0x1u << 24) /**< \brief (NFC_IMR) Ready/Busy Line 0 Interrupt Mask */
/* -------- NFC_ADDR : (NFC Offset: 0x18) SMC NFC Address Cycle Zero Register -------- */
#define NFC_ADDR_ADDR_CYCLE0_Pos 0
#define NFC_ADDR_ADDR_CYCLE0_Msk (0xffu << NFC_ADDR_ADDR_CYCLE0_Pos) /**< \brief (NFC_ADDR) NAND Flash Array Address Cycle 0 */
#define NFC_ADDR_ADDR_CYCLE0(value) ((NFC_ADDR_ADDR_CYCLE0_Msk & ((value) << NFC_ADDR_ADDR_CYCLE0_Pos)))
/* -------- NFC_BANK : (NFC Offset: 0x1C) SMC Bank Address Register -------- */
#define NFC_BANK_BANK (0x1u << 0) /**< \brief (NFC_BANK) Bank Identifier */
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

/*@}*/

#endif /* _SAMA5D2_NFC_COMPONENT_ */
