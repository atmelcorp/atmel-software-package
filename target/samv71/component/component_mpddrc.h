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

#ifndef _SAMV71_MPDDRC_COMPONENT_
#define _SAMV71_MPDDRC_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR SDRAM Controller */
/* ============================================================================= */
/** \addtogroup SAMV71_MPDDRC SDRAM Controller */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Mpddrc hardware registers */
typedef struct {
	__IO uint32_t MPDDRC_MR;             /**< \brief (Mpddrc Offset: 0x00) MPDDRC Mode Register */
	__IO uint32_t MPDDRC_RTR;            /**< \brief (Mpddrc Offset: 0x04) MPDDRC Refresh Timer Register */
	__IO uint32_t MPDDRC_CR;             /**< \brief (Mpddrc Offset: 0x08) MPDDRC Configuration Register */
	__I  uint32_t Reserved1[1];
	__IO uint32_t MPDDRC_LPR;            /**< \brief (Mpddrc Offset: 0x10) MPDDRC Low-power Register */
	__O  uint32_t MPDDRC_IER;            /**< \brief (Mpddrc Offset: 0x14) MPDDRC Interrupt Enable Register */
	__O  uint32_t MPDDRC_IDR;            /**< \brief (Mpddrc Offset: 0x18) MPDDRC Interrupt Disable Register */
	__I  uint32_t MPDDRC_IMR;            /**< \brief (Mpddrc Offset: 0x1C) MPDDRC Interrupt Mask Register */
	__I  uint32_t MPDDRC_ISR;            /**< \brief (Mpddrc Offset: 0x20) MPDDRC Interrupt Status Register */
	__IO uint32_t MPDDRC_MD;             /**< \brief (Mpddrc Offset: 0x24) MPDDRC Memory Device Register */
	__IO uint32_t MPDDRC_CFR1;           /**< \brief (Mpddrc Offset: 0x28) MPDDRC Configuration Register 1 */
	__IO uint32_t MPDDRC_OCMS;           /**< \brief (Mpddrc Offset: 0x2C) MPDDRC OCMS Register */
	__O  uint32_t MPDDRC_OCMS_KEY1;      /**< \brief (Mpddrc Offset: 0x30) MPDDRC OCMS KEY1 Register */
	__O  uint32_t MPDDRC_OCMS_KEY2;      /**< \brief (Mpddrc Offset: 0x34) MPDDRC OCMS KEY2 Register */
} Mpddrc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- MPDDRC_MR : (MPDDRC Offset: 0x00) MPDDRC Mode Register -------- */
#define MPDDRC_MR_MODE_Pos 0
#define MPDDRC_MR_MODE_Msk (0x7u << MPDDRC_MR_MODE_Pos) /**< \brief (MPDDRC_MR) MPDDRC Command Mode */
#define MPDDRC_MR_MODE(value) ((MPDDRC_MR_MODE_Msk & ((value) << MPDDRC_MR_MODE_Pos)))
#define   MPDDRC_MR_MODE_NORMAL_CMD (0x0u << 0) /**< \brief (MPDDRC_MR) Normal Mode. Any access to the MPDDRC is decoded normally. To activate this mode, the command must be followed by a write to the DDR-SDRAM. */
#define   MPDDRC_MR_MODE_NOP_CMD (0x1u << 0) /**< \brief (MPDDRC_MR) The MPDDRC issues a NOP command when the DDR-SDRAM device is accessed regardless of the cycle. To activate this mode, the command must be followed by a write to the DDR-SDRAM. */
#define   MPDDRC_MR_MODE_PRCGALL_CMD (0x2u << 0) /**< \brief (MPDDRC_MR) The MPDDRC issues the All Banks Precharge command when the DDR-SDRAM device is accessed regardless of the cycle. To activate this mode, the command must be followed by a write to the SDRAM. */
#define   MPDDRC_MR_MODE_LMR_CMD (0x3u << 0) /**< \brief (MPDDRC_MR) The MPDDRC issues a Load Mode Register command when the DDR-SDRAM device is accessed regardless of the cycle. To activate this mode, the command must be followed by a write to the DDR-SDRAM. */
#define   MPDDRC_MR_MODE_RFSH_CMD (0x4u << 0) /**< \brief (MPDDRC_MR) The MPDDRC issues an Auto-Refresh command when the DDR-SDRAM device is accessed regardless of the cycle. Previously, an All Banks Precharge command must be issued. To activate this mode, the command must be followed by a write to the DDR-SDRAM. */
#define   MPDDRC_MR_MODE_EXT_LMR_CMD (0x5u << 0) /**< \brief (MPDDRC_MR) The MPDDRC issues an Extended Load Mode Register command when the SDRAM device is accessed regardless of the cycle. To activate this mode, the command must be followed by a write to the DDR-SDRAM. The write in the DDR-SDRAM must be done in the appropriate bank. */
#define   MPDDRC_MR_MODE_DEEP_CMD (0x6u << 0) /**< \brief (MPDDRC_MR) Deep power mode: Access to deep power-down mode */
/* -------- MPDDRC_RTR : (MPDDRC Offset: 0x04) MPDDRC Refresh Timer Register -------- */
#define MPDDRC_RTR_COUNT_Pos 0
#define MPDDRC_RTR_COUNT_Msk (0xfffu << MPDDRC_RTR_COUNT_Pos) /**< \brief (MPDDRC_RTR) MPDDRC Refresh Timer Count */
#define MPDDRC_RTR_COUNT(value) ((MPDDRC_RTR_COUNT_Msk & ((value) << MPDDRC_RTR_COUNT_Pos)))
/* -------- MPDDRC_CR : (MPDDRC Offset: 0x08) MPDDRC Configuration Register -------- */
#define MPDDRC_CR_NC_Pos 0
#define MPDDRC_CR_NC_Msk (0x3u << MPDDRC_CR_NC_Pos) /**< \brief (MPDDRC_CR) Number of Column Bits */
#define MPDDRC_CR_NC(value) ((MPDDRC_CR_NC_Msk & ((value) << MPDDRC_CR_NC_Pos)))
#define   MPDDRC_CR_NC_SDRAM_8_COL_BITS (0x0u << 0) /**< \brief (MPDDRC_CR) 8 bits for SDRAM */
#define   MPDDRC_CR_NC_SDRAM_9_COL_BITS (0x1u << 0) /**< \brief (MPDDRC_CR) 9 bits for SDRAM */
#define   MPDDRC_CR_NC_SDRAM_10_COL_BITS (0x2u << 0) /**< \brief (MPDDRC_CR) 10 bits for SDRAM */
#define   MPDDRC_CR_NC_SDRAM_11_COL_BITS (0x3u << 0) /**< \brief (MPDDRC_CR) 11 bits for SDRAM */
#define MPDDRC_CR_NR_Pos 2
#define MPDDRC_CR_NR_Msk (0x3u << MPDDRC_CR_NR_Pos) /**< \brief (MPDDRC_CR) Number of Row Bits */
#define MPDDRC_CR_NR(value) ((MPDDRC_CR_NR_Msk & ((value) << MPDDRC_CR_NR_Pos)))
#define   MPDDRC_CR_NR_11_ROW_BITS (0x0u << 2) /**< \brief (MPDDRC_CR) 11 bits to define the row number, up to 2048 rows */
#define   MPDDRC_CR_NR_12_ROW_BITS (0x1u << 2) /**< \brief (MPDDRC_CR) 12 bits to define the row number, up to 4096 rows */
#define   MPDDRC_CR_NR_13_ROW_BITS (0x2u << 2) /**< \brief (MPDDRC_CR) 13 bits to define the row number, up to 8192 rows */
#define MPDDRC_CR_NB (0x1u << 4) /**< \brief (MPDDRC_CR) Number of Banks */
#define   MPDDRC_CR_NB_BANK2 (0x0u << 4) /**< \brief (MPDDRC_CR) 2 banks */
#define   MPDDRC_CR_NB_BANK4 (0x1u << 4) /**< \brief (MPDDRC_CR) 4 banks */
#define MPDDRC_CR_CAS_Pos 5
#define MPDDRC_CR_CAS_Msk (0x3u << MPDDRC_CR_CAS_Pos) /**< \brief (MPDDRC_CR) CAS Latency */
#define MPDDRC_CR_CAS(value) ((MPDDRC_CR_CAS_Msk & ((value) << MPDDRC_CR_CAS_Pos)))
#define   MPDDRC_CR_CAS_SDRAM_CAS1 (0x0u << 5) /**< \brief (MPDDRC_CR) CAS Latency 1 */
#define   MPDDRC_CR_CAS_SDRAM_CAS2 (0x1u << 5) /**< \brief (MPDDRC_CR) CAS Latency 2 */
#define   MPDDRC_CR_CAS_SDRAM_CAS3 (0x2u << 5) /**< \brief (MPDDRC_CR) CAS Latency 3 */
#define MPDDRC_CR_DBW (0x1u << 7) /**< \brief (MPDDRC_CR) Data Bus Width */
#define MPDDRC_CR_TWR_Pos 8
#define MPDDRC_CR_TWR_Msk (0xfu << MPDDRC_CR_TWR_Pos) /**< \brief (MPDDRC_CR) Write Recovery Delay */
#define MPDDRC_CR_TWR(value) ((MPDDRC_CR_TWR_Msk & ((value) << MPDDRC_CR_TWR_Pos)))
#define MPDDRC_CR_TRC_TRFC_Pos 12
#define MPDDRC_CR_TRC_TRFC_Msk (0xfu << MPDDRC_CR_TRC_TRFC_Pos) /**< \brief (MPDDRC_CR) Row Cycle Delay and Row Refresh Cycle */
#define MPDDRC_CR_TRC_TRFC(value) ((MPDDRC_CR_TRC_TRFC_Msk & ((value) << MPDDRC_CR_TRC_TRFC_Pos)))
#define MPDDRC_CR_TRP_Pos 16
#define MPDDRC_CR_TRP_Msk (0xfu << MPDDRC_CR_TRP_Pos) /**< \brief (MPDDRC_CR) Row Precharge Delay */
#define MPDDRC_CR_TRP(value) ((MPDDRC_CR_TRP_Msk & ((value) << MPDDRC_CR_TRP_Pos)))
#define MPDDRC_CR_TRCD_Pos 20
#define MPDDRC_CR_TRCD_Msk (0xfu << MPDDRC_CR_TRCD_Pos) /**< \brief (MPDDRC_CR) Row to Column Delay */
#define MPDDRC_CR_TRCD(value) ((MPDDRC_CR_TRCD_Msk & ((value) << MPDDRC_CR_TRCD_Pos)))
#define MPDDRC_CR_TRAS_Pos 24
#define MPDDRC_CR_TRAS_Msk (0xfu << MPDDRC_CR_TRAS_Pos) /**< \brief (MPDDRC_CR) Active to Precharge Delay */
#define MPDDRC_CR_TRAS(value) ((MPDDRC_CR_TRAS_Msk & ((value) << MPDDRC_CR_TRAS_Pos)))
#define MPDDRC_CR_TXSR_Pos 28
#define MPDDRC_CR_TXSR_Msk (0xfu << MPDDRC_CR_TXSR_Pos) /**< \brief (MPDDRC_CR) Exit Self Refresh to Active Delay */
#define MPDDRC_CR_TXSR(value) ((MPDDRC_CR_TXSR_Msk & ((value) << MPDDRC_CR_TXSR_Pos)))
/* -------- MPDDRC_LPR : (MPDDRC Offset: 0x10) MPDDRC Low-power Register -------- */
#define MPDDRC_LPR_LPCB_Pos 0
#define MPDDRC_LPR_LPCB_Msk (0x3u << MPDDRC_LPR_LPCB_Pos) /**< \brief (MPDDRC_LPR) Low-power Configuration Bits */
#define MPDDRC_LPR_LPCB(value) ((MPDDRC_LPR_LPCB_Msk & ((value) << MPDDRC_LPR_LPCB_Pos)))
#define   MPDDRC_LPR_LPCB_DISABLED (0x0u << 0) /**< \brief (MPDDRC_LPR) Low-power feature is inhibited. No power-down, self-refresh and deep-power modes are issued to the DDR-SDRAM device. */
#define   MPDDRC_LPR_LPCB_SELFREFRESH (0x1u << 0) /**< \brief (MPDDRC_LPR) The MPDDRC issues a self-refresh command to the DDR-SDRAM device, the clock(s) is/are deactivated and the CKE signal is set low. The DDR-SDRAM device leaves the self-refresh mode when accessed and reenters it after the access. */
#define   MPDDRC_LPR_LPCB_POWERDOWN (0x2u << 0) /**< \brief (MPDDRC_LPR) The MPDDRC issues a Power-down command to the DDR-SDRAM device after each access, the CKE signal is set low. The DDR-SDRAM device leaves the power-down mode when accessed and reenters it after the access. */
#define   MPDDRC_LPR_LPCB_DEEPPOWERDOWN (0x3u << 0) /**< \brief (MPDDRC_LPR) The MPDDRC issues a Deep Power-down command to the low-power DDR-SDRAM device. */
#define MPDDRC_LPR_PASR_Pos 4
#define MPDDRC_LPR_PASR_Msk (0x7u << MPDDRC_LPR_PASR_Pos) /**< \brief (MPDDRC_LPR) Partial Array Self-refresh */
#define MPDDRC_LPR_PASR(value) ((MPDDRC_LPR_PASR_Msk & ((value) << MPDDRC_LPR_PASR_Pos)))
#define MPDDRC_LPR_TCSR_Pos 8
#define MPDDRC_LPR_TCSR_Msk (0x3u << MPDDRC_LPR_TCSR_Pos) /**< \brief (MPDDRC_LPR) Temperature Compensated Self-Refresh (only for low-power SDRAM) */
#define MPDDRC_LPR_TCSR(value) ((MPDDRC_LPR_TCSR_Msk & ((value) << MPDDRC_LPR_TCSR_Pos)))
#define MPDDRC_LPR_DS_Pos 10
#define MPDDRC_LPR_DS_Msk (0x3u << MPDDRC_LPR_DS_Pos) /**< \brief (MPDDRC_LPR) Drive Strength */
#define MPDDRC_LPR_DS(value) ((MPDDRC_LPR_DS_Msk & ((value) << MPDDRC_LPR_DS_Pos)))
#define MPDDRC_LPR_TIMEOUT_Pos 12
#define MPDDRC_LPR_TIMEOUT_Msk (0x3u << MPDDRC_LPR_TIMEOUT_Pos) /**< \brief (MPDDRC_LPR) Time Between Last Transfer and Low-Power Mode */
#define MPDDRC_LPR_TIMEOUT(value) ((MPDDRC_LPR_TIMEOUT_Msk & ((value) << MPDDRC_LPR_TIMEOUT_Pos)))
#define   MPDDRC_LPR_TIMEOUT_NONE (0x0u << 12) /**< \brief (MPDDRC_LPR) SDRAM low-power mode is activated immediately after the end of the last transfer. */
#define   MPDDRC_LPR_TIMEOUT_DELAY_64_CLK (0x1u << 12) /**< \brief (MPDDRC_LPR) SDRAM low-power mode is activated 64 clock cycles after the end of the last transfer. */
#define   MPDDRC_LPR_TIMEOUT_DELAY_128_CLK (0x2u << 12) /**< \brief (MPDDRC_LPR) SDRAM low-power mode is activated 128 clock cycles after the end of the last transfer. */
/* -------- MPDDRC_IER : (MPDDRC Offset: 0x14) MPDDRC Interrupt Enable Register -------- */
#define MPDDRC_IER_RES (0x1u << 0) /**< \brief (MPDDRC_IER) Refresh Error Status */
/* -------- MPDDRC_IDR : (MPDDRC Offset: 0x18) MPDDRC Interrupt Disable Register -------- */
#define MPDDRC_IDR_RES (0x1u << 0) /**< \brief (MPDDRC_IDR) Refresh Error Status */
/* -------- MPDDRC_IMR : (MPDDRC Offset: 0x1C) MPDDRC Interrupt Mask Register -------- */
#define MPDDRC_IMR_RES (0x1u << 0) /**< \brief (MPDDRC_IMR) Refresh Error Status */
/* -------- MPDDRC_ISR : (MPDDRC Offset: 0x20) MPDDRC Interrupt Status Register -------- */
#define MPDDRC_ISR_RES (0x1u << 0) /**< \brief (MPDDRC_ISR) Refresh Error Status (cleared on read) */
/* -------- MPDDRC_MD : (MPDDRC Offset: 0x24) MPDDRC Memory Device Register -------- */
#define MPDDRC_MD_MD_Pos 0
#define MPDDRC_MD_MD_Msk (0x3u << MPDDRC_MD_MD_Pos) /**< \brief (MPDDRC_MDR) Memory Device Type */
#define MPDDRC_MD_MD(value) ((MPDDRC_MD_MD_Msk & ((value) << MPDDRC_MD_MD_Pos)))
#define   MPDDRC_MD_MD_SDRAM (0x0u << 0) /**< \brief (MPDDRC_MDR) SDRAM */
#define   MPDDRC_MD_MD_LPSDRAM (0x1u << 0) /**< \brief (MPDDRC_MDR) Low-power SDRAM */
/* -------- MPDDRC_CFR1 : (MPDDRC Offset: 0x28) MPDDRC Configuration Register 1 -------- */
#define MPDDRC_CFR1_TMRD_Pos 0
#define MPDDRC_CFR1_TMRD_Msk (0xfu << MPDDRC_CFR1_TMRD_Pos) /**< \brief (MPDDRC_CFR1) Load Mode Register Command to Active or Refresh Command */
#define MPDDRC_CFR1_TMRD(value) ((MPDDRC_CFR1_TMRD_Msk & ((value) << MPDDRC_CFR1_TMRD_Pos)))
#define MPDDRC_CFR1_UNAL (0x1u << 8) /**< \brief (MPDDRC_CFR1) Support Unaligned Access */
#define   MPDDRC_CFR1_UNAL_UNSUPPORTED (0x0u << 8) /**< \brief (MPDDRC_CFR1) Unaligned access is not supported. */
#define   MPDDRC_CFR1_UNAL_SUPPORTED (0x1u << 8) /**< \brief (MPDDRC_CFR1) Unaligned access is supported. */
/* -------- MPDDRC_OCMS : (MPDDRC Offset: 0x2C) MPDDRC OCMS Register -------- */
#define MPDDRC_OCMS_SCR_EN (0x1u << 0) /**< \brief (MPDDRC_OCMS) Scrambling Enable */
/* -------- MPDDRC_OCMS_KEY1 : (MPDDRC Offset: 0x30) MPDDRC OCMS KEY1 Register -------- */
#define MPDDRC_OCMS_KEY1_KEY1_Pos 0
#define MPDDRC_OCMS_KEY1_KEY1_Msk (0xffffffffu << MPDDRC_OCMS_KEY1_KEY1_Pos) /**< \brief (MPDDRC_OCMS_KEY1) Off-chip Memory Scrambling (OCMS) Key Part 1 */
#define MPDDRC_OCMS_KEY1_KEY1(value) ((MPDDRC_OCMS_KEY1_KEY1_Msk & ((value) << MPDDRC_OCMS_KEY1_KEY1_Pos)))
/* -------- MPDDRC_OCMS_KEY2 : (MPDDRC Offset: 0x34) MPDDRC OCMS KEY2 Register -------- */
#define MPDDRC_OCMS_KEY2_KEY2_Pos 0
#define MPDDRC_OCMS_KEY2_KEY2_Msk (0xffffffffu << MPDDRC_OCMS_KEY2_KEY2_Pos) /**< \brief (MPDDRC_OCMS_KEY2) Off-chip Memory Scrambling (OCMS) Key Part 2 */
#define MPDDRC_OCMS_KEY2_KEY2(value) ((MPDDRC_OCMS_KEY2_KEY2_Msk & ((value) << MPDDRC_OCMS_KEY2_KEY2_Pos)))

/*@}*/

#endif /* _SAMV71_MPDDRC_COMPONENT_ */
