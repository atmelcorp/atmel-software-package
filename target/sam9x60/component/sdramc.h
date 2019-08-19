/* ---------------------------------------------------------------------------- */
/*                Microchip Microcontroller Software Support                    */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) %copyright_year%, Microchip Technology Inc.                    */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Microchip's name may not be used to endorse or promote products derived from */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY MICROCHIP "AS IS" AND ANY EXPRESS  */
/* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES */
/* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT    */
/* ARE DISCLAIMED. IN NO EVENT SHALL MICROCHIP BE LIABLE FOR ANY DIRECT,        */
/* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES           */
/* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; */
/* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND  */
/* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT   */
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF     */
/* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.            */
/* ---------------------------------------------------------------------------- */

#ifndef _SAM9X_SDRAMC_COMPONENT_
#define _SAM9X_SDRAMC_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR SDRAM Controller */
/* ============================================================================= */
/** \addtogroup SAM9X_SDRAMC SDRAM Controller */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Sdramc hardware registers */
typedef struct {
  __IO uint32_t SDRAMC_MR;        /**< \brief (Sdramc Offset: 0x0) Mode Register */
  __IO uint32_t SDRAMC_TR;        /**< \brief (Sdramc Offset: 0x4) Refresh Timer Register */
  __IO uint32_t SDRAMC_CR;        /**< \brief (Sdramc Offset: 0x8) Configuration Register */
  __IO uint32_t SDRAMC_HSR;       /**< \brief (Sdramc Offset: 0xC) High-Speed Register */
  __IO uint32_t SDRAMC_LPR;       /**< \brief (Sdramc Offset: 0x10) Low-Power Register */
  __O  uint32_t SDRAMC_IER;       /**< \brief (Sdramc Offset: 0x14) Interrupt Enable Register */
  __O  uint32_t SDRAMC_IDR;       /**< \brief (Sdramc Offset: 0x18) Interrupt Disable Register */
  __I  uint32_t SDRAMC_IMR;       /**< \brief (Sdramc Offset: 0x1C) Interrupt Mask Register */
  __I  uint32_t SDRAMC_ISR;       /**< \brief (Sdramc Offset: 0x20) Interrupt Status Register */
  __IO uint32_t SDRAMC_MDR;       /**< \brief (Sdramc Offset: 0x24) Memory Device Register */
  __IO uint32_t SDRAMC_CFR1;      /**< \brief (Sdramc Offset: 0x28) Configuration Register 1 */
  __IO uint32_t SDRAMC_OCMS;      /**< \brief (Sdramc Offset: 0x2C) OCMS Register */
  __O  uint32_t SDRAMC_OCMS_KEY1; /**< \brief (Sdramc Offset: 0x30) OCMS KEY1 Register */
  __O  uint32_t SDRAMC_OCMS_KEY2; /**< \brief (Sdramc Offset: 0x34) OCMS KEY2 Register */
  __I  uint32_t Reserved1[1];
  __IO uint32_t SDRAMC_WPMR;      /**< \brief (Sdramc Offset: 0x3C) Write Protection Mode Register */
  __I  uint32_t SDRAMC_WPSR;      /**< \brief (Sdramc Offset: 0x40) Write Protection Status Register */
} Sdramc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- SDRAMC_MR : (SDRAMC Offset: 0x0) Mode Register -------- */
#define SDRAMC_MR_MODE_Pos 0
#define SDRAMC_MR_MODE_Msk (0x7u << SDRAMC_MR_MODE_Pos) /**< \brief (SDRAMC_MR) SDRAMC Command Mode */
#define SDRAMC_MR_MODE(value) ((SDRAMC_MR_MODE_Msk & ((value) << SDRAMC_MR_MODE_Pos)))
#define   SDRAMC_MR_MODE_NORMAL (0x0u << 0) /**< \brief (SDRAMC_MR) Normal mode. Any access to the SDRAM is decoded normally. To activate this mode, the command must be followed by a write to the SDRAM. */
#define   SDRAMC_MR_MODE_NOP (0x1u << 0) /**< \brief (SDRAMC_MR) The SDRAMC issues a NOP command when the SDRAM device is accessed regardless of the cycle. To activate this mode, the command must be followed by a write to the SDRAM. */
#define   SDRAMC_MR_MODE_ALLBANKS_PRECHARGE (0x2u << 0) /**< \brief (SDRAMC_MR) The SDRAMC issues an "All Banks Precharge" command when the SDRAM device is accessed regardless of the cycle. To activate this mode, the command must be followed by a write to the SDRAM. */
#define   SDRAMC_MR_MODE_LOAD_MODEREG (0x3u << 0) /**< \brief (SDRAMC_MR) The SDRAMC issues a "Load Mode Register" command when the SDRAM device is accessed regardless of the cycle. To activate this mode, the command must be followed by a write to the SDRAM. */
#define   SDRAMC_MR_MODE_AUTO_REFRESH (0x4u << 0) /**< \brief (SDRAMC_MR) The SDRAMC issues an "Autorefresh" Command when the SDRAM device is accessed regardless of the cycle. Previously, an "All Banks Precharge" command must be issued. To activate this mode, the command must be followed by a write to the SDRAM. */
#define   SDRAMC_MR_MODE_EXT_LOAD_MODEREG (0x5u << 0) /**< \brief (SDRAMC_MR) The SDRAMC issues an "Extended Load Mode Register" command when the SDRAM device is accessed regardless of the cycle. To activate this mode, the "Extended Load Mode Register" command must be followed by a write to the SDRAM. The write in the SDRAM must be done in the appropriate bank; most low-power SDRAM devices use the bank 1. */
#define   SDRAMC_MR_MODE_DEEP_POWERDOWN (0x6u << 0) /**< \brief (SDRAMC_MR) Deep Powerdown mode. Enters Deep Powerdown mode. */
/* -------- SDRAMC_TR : (SDRAMC Offset: 0x4) Refresh Timer Register -------- */
#define SDRAMC_TR_COUNT_Pos 0
#define SDRAMC_TR_COUNT_Msk (0xfffu << SDRAMC_TR_COUNT_Pos) /**< \brief (SDRAMC_TR) SDRAMC Refresh Timer Count */
#define SDRAMC_TR_COUNT(value) ((SDRAMC_TR_COUNT_Msk & ((value) << SDRAMC_TR_COUNT_Pos)))
/* -------- SDRAMC_CR : (SDRAMC Offset: 0x8) Configuration Register -------- */
#define SDRAMC_CR_NC_Pos 0
#define SDRAMC_CR_NC_Msk (0x3u << SDRAMC_CR_NC_Pos) /**< \brief (SDRAMC_CR) Number of Column Bits */
#define SDRAMC_CR_NC(value) ((SDRAMC_CR_NC_Msk & ((value) << SDRAMC_CR_NC_Pos)))
#define   SDRAMC_CR_NC_COL8 (0x0u << 0) /**< \brief (SDRAMC_CR) 8 bits to define the column number, up to 256 columns */
#define   SDRAMC_CR_NC_COL9 (0x1u << 0) /**< \brief (SDRAMC_CR) 9 bits to define the column number, up to 512 columns */
#define   SDRAMC_CR_NC_COL10 (0x2u << 0) /**< \brief (SDRAMC_CR) 10 bits to define the column number, up to 1024 columns */
#define   SDRAMC_CR_NC_COL11 (0x3u << 0) /**< \brief (SDRAMC_CR) 11 bits to define the column number, up to 2048 columns */
#define SDRAMC_CR_NR_Pos 2
#define SDRAMC_CR_NR_Msk (0x3u << SDRAMC_CR_NR_Pos) /**< \brief (SDRAMC_CR) Number of Row Bits */
#define SDRAMC_CR_NR(value) ((SDRAMC_CR_NR_Msk & ((value) << SDRAMC_CR_NR_Pos)))
#define   SDRAMC_CR_NR_ROW11 (0x0u << 2) /**< \brief (SDRAMC_CR) 11 bits to define the row number, up to 2048 rows */
#define   SDRAMC_CR_NR_ROW12 (0x1u << 2) /**< \brief (SDRAMC_CR) 12 bits to define the row number, up to 4096 rows */
#define   SDRAMC_CR_NR_ROW13 (0x2u << 2) /**< \brief (SDRAMC_CR) 13 bits to define the row number, up to 8192 rows */
#define SDRAMC_CR_NB (0x1u << 4) /**< \brief (SDRAMC_CR) Number of Banks */
#define   SDRAMC_CR_NB_BANK2 (0x0u << 4) /**< \brief (SDRAMC_CR) 2 banks */
#define   SDRAMC_CR_NB_BANK4 (0x1u << 4) /**< \brief (SDRAMC_CR) 4 banks */
#define SDRAMC_CR_CAS_Pos 5
#define SDRAMC_CR_CAS_Msk (0x3u << SDRAMC_CR_CAS_Pos) /**< \brief (SDRAMC_CR) CAS Latency */
#define SDRAMC_CR_CAS(value) ((SDRAMC_CR_CAS_Msk & ((value) << SDRAMC_CR_CAS_Pos)))
#define   SDRAMC_CR_CAS_LATENCY2 (0x2u << 5) /**< \brief (SDRAMC_CR) 2-cycle latency */
#define   SDRAMC_CR_CAS_LATENCY3 (0x3u << 5) /**< \brief (SDRAMC_CR) 3-cycle latency */
#define SDRAMC_CR_DBW (0x1u << 7) /**< \brief (SDRAMC_CR) Data Bus Width */
#define SDRAMC_CR_TWR_Pos 8
#define SDRAMC_CR_TWR_Msk (0xfu << SDRAMC_CR_TWR_Pos) /**< \brief (SDRAMC_CR) Write Recovery Delay */
#define SDRAMC_CR_TWR(value) ((SDRAMC_CR_TWR_Msk & ((value) << SDRAMC_CR_TWR_Pos)))
#define SDRAMC_CR_TRC_TRFC_Pos 12
#define SDRAMC_CR_TRC_TRFC_Msk (0xfu << SDRAMC_CR_TRC_TRFC_Pos) /**< \brief (SDRAMC_CR) Row Cycle Delay and Row Refresh Cycle */
#define SDRAMC_CR_TRC_TRFC(value) ((SDRAMC_CR_TRC_TRFC_Msk & ((value) << SDRAMC_CR_TRC_TRFC_Pos)))
#define SDRAMC_CR_TRP_Pos 16
#define SDRAMC_CR_TRP_Msk (0xfu << SDRAMC_CR_TRP_Pos) /**< \brief (SDRAMC_CR) Row Precharge Delay */
#define SDRAMC_CR_TRP(value) ((SDRAMC_CR_TRP_Msk & ((value) << SDRAMC_CR_TRP_Pos)))
#define SDRAMC_CR_TRCD_Pos 20
#define SDRAMC_CR_TRCD_Msk (0xfu << SDRAMC_CR_TRCD_Pos) /**< \brief (SDRAMC_CR) Row to Column Delay */
#define SDRAMC_CR_TRCD(value) ((SDRAMC_CR_TRCD_Msk & ((value) << SDRAMC_CR_TRCD_Pos)))
#define SDRAMC_CR_TRAS_Pos 24
#define SDRAMC_CR_TRAS_Msk (0xfu << SDRAMC_CR_TRAS_Pos) /**< \brief (SDRAMC_CR) Active to Precharge Delay */
#define SDRAMC_CR_TRAS(value) ((SDRAMC_CR_TRAS_Msk & ((value) << SDRAMC_CR_TRAS_Pos)))
#define SDRAMC_CR_TXSR_Pos 28
#define SDRAMC_CR_TXSR_Msk (0xfu << SDRAMC_CR_TXSR_Pos) /**< \brief (SDRAMC_CR) Exit Self-Refresh to Active Delay */
#define SDRAMC_CR_TXSR(value) ((SDRAMC_CR_TXSR_Msk & ((value) << SDRAMC_CR_TXSR_Pos)))
/* -------- SDRAMC_HSR : (SDRAMC Offset: 0xC) High-Speed Register -------- */
#define SDRAMC_HSR_DA (0x1u << 0) /**< \brief (SDRAMC_HSR) Decode Cycle Enable */
/* -------- SDRAMC_LPR : (SDRAMC Offset: 0x10) Low-Power Register -------- */
#define SDRAMC_LPR_LPCB_Pos 0
#define SDRAMC_LPR_LPCB_Msk (0x3u << SDRAMC_LPR_LPCB_Pos) /**< \brief (SDRAMC_LPR) Low-power Configuration Bits */
#define SDRAMC_LPR_LPCB(value) ((SDRAMC_LPR_LPCB_Msk & ((value) << SDRAMC_LPR_LPCB_Pos)))
#define   SDRAMC_LPR_LPCB_DISABLED (0x0u << 0) /**< \brief (SDRAMC_LPR) The low-power feature is inhibited: no Powerdown, Self-refresh or Deep Powerdown command is issued to the SDRAM device. */
#define   SDRAMC_LPR_LPCB_SELF_REFRESH (0x1u << 0) /**< \brief (SDRAMC_LPR) The SDRAMC issues a Self-refresh command to the SDRAM device, the SDCK clock is deactivated and the SDCKE signal is set low. The SDRAM device leaves the Self-refresh mode when accessed and enters it after the access. */
#define   SDRAMC_LPR_LPCB_POWER_DOWN (0x2u << 0) /**< \brief (SDRAMC_LPR) The SDRAMC issues a Powerdown Command to the SDRAM device after each access, the SDCKE signal is set to low. The SDRAM device leaves the Powerdown mode when accessed and enters it after the access. */
#define   SDRAMC_LPR_LPCB_DEEP_POWER_DOWN (0x3u << 0) /**< \brief (SDRAMC_LPR) The SDRAMC issues a Deep Powerdown command to the SDRAM device. This mode is unique to low-power SDRAM. */
#define SDRAMC_LPR_PASR_Pos 4
#define SDRAMC_LPR_PASR_Msk (0x7u << SDRAMC_LPR_PASR_Pos) /**< \brief (SDRAMC_LPR) Partial Array Self-refresh (only for low-power SDRAM) */
#define SDRAMC_LPR_PASR(value) ((SDRAMC_LPR_PASR_Msk & ((value) << SDRAMC_LPR_PASR_Pos)))
#define SDRAMC_LPR_TCSR_Pos 8
#define SDRAMC_LPR_TCSR_Msk (0x3u << SDRAMC_LPR_TCSR_Pos) /**< \brief (SDRAMC_LPR) Temperature Compensated Self-Refresh (only for low-power SDRAM) */
#define SDRAMC_LPR_TCSR(value) ((SDRAMC_LPR_TCSR_Msk & ((value) << SDRAMC_LPR_TCSR_Pos)))
#define SDRAMC_LPR_DS_Pos 10
#define SDRAMC_LPR_DS_Msk (0x3u << SDRAMC_LPR_DS_Pos) /**< \brief (SDRAMC_LPR) Drive Strength (only for low-power SDRAM) */
#define SDRAMC_LPR_DS(value) ((SDRAMC_LPR_DS_Msk & ((value) << SDRAMC_LPR_DS_Pos)))
#define SDRAMC_LPR_TIMEOUT_Pos 12
#define SDRAMC_LPR_TIMEOUT_Msk (0x3u << SDRAMC_LPR_TIMEOUT_Pos) /**< \brief (SDRAMC_LPR) Time to Define When Low-power Mode Is Enabled */
#define SDRAMC_LPR_TIMEOUT(value) ((SDRAMC_LPR_TIMEOUT_Msk & ((value) << SDRAMC_LPR_TIMEOUT_Pos)))
#define   SDRAMC_LPR_TIMEOUT_LP_LAST_XFER (0x0u << 12) /**< \brief (SDRAMC_LPR) The SDRAMC activates the SDRAM Low-power mode immediately after the end of the last transfer. */
#define   SDRAMC_LPR_TIMEOUT_LP_LAST_XFER_64 (0x1u << 12) /**< \brief (SDRAMC_LPR) The SDRAMC activates the SDRAM Low-power mode 64 clock cycles after the end of the last transfer. */
#define   SDRAMC_LPR_TIMEOUT_LP_LAST_XFER_128 (0x2u << 12) /**< \brief (SDRAMC_LPR) The SDRAMC activates the SDRAM Low-power mode 128 clock cycles after the end of the last transfer. */
#define SDRAMC_LPR_SELFAUTO (0x1u << 14) /**< \brief (SDRAMC_LPR) Self-refresh Exit Autorefresh */
#define SDRAMC_LPR_SELFDONE (0x1u << 16) /**< \brief (SDRAMC_LPR) Self-refresh Done (read-only) */
/* -------- SDRAMC_IER : (SDRAMC Offset: 0x14) Interrupt Enable Register -------- */
#define SDRAMC_IER_RES (0x1u << 0) /**< \brief (SDRAMC_IER) Refresh Error Interrupt Enable */
#define SDRAMC_IER_SECE (0x1u << 1) /**< \brief (SDRAMC_IER) Security and/or Safety Event Interrupt Enable */
/* -------- SDRAMC_IDR : (SDRAMC Offset: 0x18) Interrupt Disable Register -------- */
#define SDRAMC_IDR_RES (0x1u << 0) /**< \brief (SDRAMC_IDR) Refresh Error Interrupt Disable */
#define SDRAMC_IDR_SECE (0x1u << 1) /**< \brief (SDRAMC_IDR) Security and/or Safety Event Interrupt Disable */
/* -------- SDRAMC_IMR : (SDRAMC Offset: 0x1C) Interrupt Mask Register -------- */
#define SDRAMC_IMR_RES (0x1u << 0) /**< \brief (SDRAMC_IMR) Refresh Error Interrupt Mask */
#define SDRAMC_IMR_SECE (0x1u << 1) /**< \brief (SDRAMC_IMR) Security and/or Safety Event Interrupt Mask */
/* -------- SDRAMC_ISR : (SDRAMC Offset: 0x20) Interrupt Status Register -------- */
#define SDRAMC_ISR_RES (0x1u << 0) /**< \brief (SDRAMC_ISR) Refresh Error Status (cleared on read) */
#define SDRAMC_ISR_SECE (0x1u << 1) /**< \brief (SDRAMC_ISR) Security and/or Safety Event (cleared on read) */
/* -------- SDRAMC_MDR : (SDRAMC Offset: 0x24) Memory Device Register -------- */
#define SDRAMC_MDR_MD_Pos 0
#define SDRAMC_MDR_MD_Msk (0x3u << SDRAMC_MDR_MD_Pos) /**< \brief (SDRAMC_MDR) Memory Device Type */
#define SDRAMC_MDR_MD(value) ((SDRAMC_MDR_MD_Msk & ((value) << SDRAMC_MDR_MD_Pos)))
#define   SDRAMC_MDR_MD_SDRAM (0x0u << 0) /**< \brief (SDRAMC_MDR) SDRAM */
#define   SDRAMC_MDR_MD_LPSDRAM (0x1u << 0) /**< \brief (SDRAMC_MDR) Low-power SDRAM */
#define SDRAMC_MDR_SHIFT_SAMPLING_Pos 4
#define SDRAMC_MDR_SHIFT_SAMPLING_Msk (0x3u << SDRAMC_MDR_SHIFT_SAMPLING_Pos) /**< \brief (SDRAMC_MDR) Shift Sampling Point of Data */
#define SDRAMC_MDR_SHIFT_SAMPLING(value) ((SDRAMC_MDR_SHIFT_SAMPLING_Msk & ((value) << SDRAMC_MDR_SHIFT_SAMPLING_Pos)))
#define   SDRAMC_MDR_SHIFT_SAMPLING_SHIFT_ONE_CYCLE (0x1u << 4) /**< \brief (SDRAMC_MDR) Sampling point is shifted by one cycle. */
#define   SDRAMC_MDR_SHIFT_SAMPLING_SHIFT_TWO_CYCLES (0x2u << 4) /**< \brief (SDRAMC_MDR) Sampling point is shifted by two cycles. */
#define   SDRAMC_MDR_SHIFT_SAMPLING_SHIFT_THREE_CYCLES (0x3u << 4) /**< \brief (SDRAMC_MDR) Sampling point is shifted by three cycles. */
/* -------- SDRAMC_CFR1 : (SDRAMC Offset: 0x28) Configuration Register 1 -------- */
#define SDRAMC_CFR1_TMRD_Pos 0
#define SDRAMC_CFR1_TMRD_Msk (0xfu << SDRAMC_CFR1_TMRD_Pos) /**< \brief (SDRAMC_CFR1) Load Mode Register Command to Active or Refresh Command */
#define SDRAMC_CFR1_TMRD(value) ((SDRAMC_CFR1_TMRD_Msk & ((value) << SDRAMC_CFR1_TMRD_Pos)))
#define SDRAMC_CFR1_UNAL (0x1u << 8) /**< \brief (SDRAMC_CFR1) This bit must be always written to 1 */
#define SDRAMC_CFR1_ADD_DATA_MUX (0x1u << 10) /**< \brief (SDRAMC_CFR1) Multiplexed Address and Data */
#define   SDRAMC_CFR1_ADD_DATA_MUX_UNSUPPORTED (0x0u << 10) /**< \brief (SDRAMC_CFR1) Data and address are not multiplexed */
#define   SDRAMC_CFR1_ADD_DATA_MUX_SUPPORTED (0x1u << 10) /**< \brief (SDRAMC_CFR1) Data and address are multiplexed */
#define SDRAMC_CFR1_CMD_MUX (0x1u << 11) /**< \brief (SDRAMC_CFR1) Commands are Multiplexed with Address and Data */
#define   SDRAMC_CFR1_CMD_MUX_UNSUPPORTED (0x0u << 11) /**< \brief (SDRAMC_CFR1) Commands are not multiplexed with address and data. */
#define   SDRAMC_CFR1_CMD_MUX_SUPPORTED (0x1u << 11) /**< \brief (SDRAMC_CFR1) Commands are multiplexed with address and data. */
/* -------- SDRAMC_OCMS : (SDRAMC Offset: 0x2C) OCMS Register -------- */
#define SDRAMC_OCMS_SDR_SE (0x1u << 0) /**< \brief (SDRAMC_OCMS) SDRAM Memory Controller Scrambling Enable */
#define SDRAMC_OCMS_TAMPCLR (0x1u << 4) /**< \brief (SDRAMC_OCMS) Tamper Clear Enable */
/* -------- SDRAMC_OCMS_KEY1 : (SDRAMC Offset: 0x30) OCMS KEY1 Register -------- */
#define SDRAMC_OCMS_KEY1_KEY1_Pos 0
#define SDRAMC_OCMS_KEY1_KEY1_Msk (0xffffffffu << SDRAMC_OCMS_KEY1_KEY1_Pos) /**< \brief (SDRAMC_OCMS_KEY1) Off-chip Memory Scrambling (OCMS) Key Part 1 */
#define SDRAMC_OCMS_KEY1_KEY1(value) ((SDRAMC_OCMS_KEY1_KEY1_Msk & ((value) << SDRAMC_OCMS_KEY1_KEY1_Pos)))
/* -------- SDRAMC_OCMS_KEY2 : (SDRAMC Offset: 0x34) OCMS KEY2 Register -------- */
#define SDRAMC_OCMS_KEY2_KEY2_Pos 0
#define SDRAMC_OCMS_KEY2_KEY2_Msk (0xffffffffu << SDRAMC_OCMS_KEY2_KEY2_Pos) /**< \brief (SDRAMC_OCMS_KEY2) Off-chip Memory Scrambling (OCMS) Key Part 2 */
#define SDRAMC_OCMS_KEY2_KEY2(value) ((SDRAMC_OCMS_KEY2_KEY2_Msk & ((value) << SDRAMC_OCMS_KEY2_KEY2_Pos)))
/* -------- SDRAMC_WPMR : (SDRAMC Offset: 0x3C) Write Protection Mode Register -------- */
#define SDRAMC_WPMR_WPEN (0x1u << 0) /**< \brief (SDRAMC_WPMR) Write Protection Enable */
#define SDRAMC_WPMR_WPITEN (0x1u << 1) /**< \brief (SDRAMC_WPMR) Write Protection Interrupt Enable */
#define SDRAMC_WPMR_WPKEY_Pos 8
#define SDRAMC_WPMR_WPKEY_Msk (0xffffffu << SDRAMC_WPMR_WPKEY_Pos) /**< \brief (SDRAMC_WPMR) Write Protection Key */
#define SDRAMC_WPMR_WPKEY(value) ((SDRAMC_WPMR_WPKEY_Msk & ((value) << SDRAMC_WPMR_WPKEY_Pos)))
#define   SDRAMC_WPMR_WPKEY_PASSWD (0x534452u << 8) /**< \brief (SDRAMC_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit. Always reads as 0. */
/* -------- SDRAMC_WPSR : (SDRAMC Offset: 0x40) Write Protection Status Register -------- */
#define SDRAMC_WPSR_WPEN (0x1u << 0) /**< \brief (SDRAMC_WPSR) Write Protection Violation Status (cleared on read) */
#define SDRAMC_WPSR_CGD (0x1u << 1) /**< \brief (SDRAMC_WPSR) Clock Glitch Detected (cleared on read) */
#define SDRAMC_WPSR_SEQE (0x1u << 2) /**< \brief (SDRAMC_WPSR) Internal Sequencer Error (cleared on read) */
#define SDRAMC_WPSR_SWE (0x1u << 3) /**< \brief (SDRAMC_WPSR) Software Control Error (cleared on read) */
#define SDRAMC_WPSR_WPVSRC_Pos 8
#define SDRAMC_WPSR_WPVSRC_Msk (0xffu << SDRAMC_WPSR_WPVSRC_Pos) /**< \brief (SDRAMC_WPSR) Write Protection Violation Source */
#define SDRAMC_WPSR_SWETYP_Pos 24
#define SDRAMC_WPSR_SWETYP_Msk (0x7u << SDRAMC_WPSR_SWETYP_Pos) /**< \brief (SDRAMC_WPSR) Software Error Type (cleared on read) */
#define   SDRAMC_WPSR_SWETYP_READ_WO (0x0u << 24) /**< \brief (SDRAMC_WPSR) A write-only register has been read (Warning). */
#define   SDRAMC_WPSR_SWETYP_WRITE_RO (0x1u << 24) /**< \brief (SDRAMC_WPSR) A write access has been performed on a read-only register (Warning). */
#define   SDRAMC_WPSR_SWETYP_UNDEF_RW (0x2u << 24) /**< \brief (SDRAMC_WPSR) Access to an undefined address (Warning). */
#define   SDRAMC_WPSR_SWETYP_W_AFTER_INIT (0x3u << 24) /**< \brief (SDRAMC_WPSR) Write access performed into some configuration registers after memory device initialization, i.e. if SDRAMC_TR.COUNT > 0 (Error). */
#define SDRAMC_WPSR_ECLASS (0x1u << 31) /**< \brief (SDRAMC_WPSR) Software Error Class (cleared on read) */
#define   SDRAMC_WPSR_ECLASS_WARNING (0x0u << 31) /**< \brief (SDRAMC_WPSR) An abnormal access is performed but it does not affect system functionality. */
#define   SDRAMC_WPSR_ECLASS_ERROR (0x1u << 31) /**< \brief (SDRAMC_WPSR) An access is performed into some registers after memory device initialization sequence. */

/*@}*/


#endif /* _SAM9X_SDRAMC_COMPONENT_ */
