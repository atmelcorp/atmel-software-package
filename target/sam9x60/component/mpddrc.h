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

#ifndef _SAM9X_MPDDRC_COMPONENT_
#define _SAM9X_MPDDRC_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR AHB Multiport DDR-SDRAM Controller */
/* ============================================================================= */
/** \addtogroup SAM9X_MPDDRC AHB Multiport DDR-SDRAM Controller */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Mpddrc hardware registers */
typedef struct {
  __IO uint32_t MPDDRC_MR;            /**< \brief (Mpddrc Offset: 0x0) Mode Register */
  __IO uint32_t MPDDRC_RTR;           /**< \brief (Mpddrc Offset: 0x4) Refresh Timer Register */
  __IO uint32_t MPDDRC_CR;            /**< \brief (Mpddrc Offset: 0x8) Configuration Register */
  __IO uint32_t MPDDRC_TPR0;          /**< \brief (Mpddrc Offset: 0xC) Timing Parameter 0 Register */
  __IO uint32_t MPDDRC_TPR1;          /**< \brief (Mpddrc Offset: 0x10) Timing Parameter 1 Register */
  __IO uint32_t MPDDRC_TPR2;          /**< \brief (Mpddrc Offset: 0x14) Timing Parameter 2 Register */
  __I  uint32_t Reserved1[1];
  __IO uint32_t MPDDRC_LPR;           /**< \brief (Mpddrc Offset: 0x1C) Low-Power Register */
  __IO uint32_t MPDDRC_MD;            /**< \brief (Mpddrc Offset: 0x20) Memory Device Register */
  __I  uint32_t Reserved2[4];
  __IO uint32_t MPDDRC_IO_CALIBR;     /**< \brief (Mpddrc Offset: 0x34) I/O Calibration Register */
  __IO uint32_t MPDDRC_OCMS;          /**< \brief (Mpddrc Offset: 0x38) OCMS Register */
  __O  uint32_t MPDDRC_OCMS_KEY1;     /**< \brief (Mpddrc Offset: 0x3C) OCMS KEY1 Register */
  __O  uint32_t MPDDRC_OCMS_KEY2;     /**< \brief (Mpddrc Offset: 0x40) OCMS KEY2 Register */
  __IO uint32_t MPDDRC_CONF_ARBITER;  /**< \brief (Mpddrc Offset: 0x44) Configuration Arbiter Register */
  __IO uint32_t MPDDRC_TIMEOUT;       /**< \brief (Mpddrc Offset: 0x48) Timeout Register */
  __IO uint32_t MPDDRC_REQ_PORT_0123; /**< \brief (Mpddrc Offset: 0x4C) Request Port 0-1-2-3 Register */
  __I  uint32_t Reserved3[1];
  __I  uint32_t MPDDRC_BDW_PORT_0123; /**< \brief (Mpddrc Offset: 0x54) Current/Maximum Bandwidth Port 0-1-2-3 Register */
  __I  uint32_t Reserved4[1];
  __IO uint32_t MPDDRC_RD_DATA_PATH;  /**< \brief (Mpddrc Offset: 0x5C) Read Data Path Register */
  __IO uint32_t MPDDRC_MCFGR;         /**< \brief (Mpddrc Offset: 0x60) Monitor Configuration Register */
  __IO uint32_t MPDDRC_MADDR0;        /**< \brief (Mpddrc Offset: 0x64) Monitor Address High/Low Port 0 Register */
  __IO uint32_t MPDDRC_MADDR1;        /**< \brief (Mpddrc Offset: 0x68) Monitor Address High/Low Port 1 Register */
  __IO uint32_t MPDDRC_MADDR2;        /**< \brief (Mpddrc Offset: 0x6C) Monitor Address High/Low Port 2 Register */
  __IO uint32_t MPDDRC_MADDR3;        /**< \brief (Mpddrc Offset: 0x70) Monitor Address High/Low Port 3 Register */
  __I  uint32_t Reserved5[4];
  __I  uint32_t MPDDRC_MINFO0;        /**< \brief (Mpddrc Offset: 0x84) Monitor Information Port 0 Register */
  __I  uint32_t MPDDRC_MINFO1;        /**< \brief (Mpddrc Offset: 0x88) Monitor Information Port 1 Register */
  __I  uint32_t MPDDRC_MINFO2;        /**< \brief (Mpddrc Offset: 0x8C) Monitor Information Port 2 Register */
  __I  uint32_t MPDDRC_MINFO3;        /**< \brief (Mpddrc Offset: 0x90) Monitor Information Port 3 Register */
  __I  uint32_t Reserved6[11];
  __O  uint32_t MPDDRC_IER;           /**< \brief (Mpddrc Offset: 0xC0) Interrupt Enable Register */
  __O  uint32_t MPDDRC_IDR;           /**< \brief (Mpddrc Offset: 0xC4) Interrupt Disable Register */
  __I  uint32_t MPDDRC_IMR;           /**< \brief (Mpddrc Offset: 0xC8) Interrupt Mask Register */
  __I  uint32_t MPDDRC_ISR;           /**< \brief (Mpddrc Offset: 0xCC) Interrupt Status Register */
  __IO uint32_t MPDDRC_SAFETY;        /**< \brief (Mpddrc Offset: 0xD0) Safety Register */
  __I  uint32_t Reserved7[4];
  __IO uint32_t MPDDRC_WPMR;          /**< \brief (Mpddrc Offset: 0xE4) Write Protection Mode Register */
  __I  uint32_t MPDDRC_WPSR;          /**< \brief (Mpddrc Offset: 0xE8) Write Protection Status Register */
} Mpddrc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- MPDDRC_MR : (MPDDRC Offset: 0x0) Mode Register -------- */
#define MPDDRC_MR_MODE_Pos 0
#define MPDDRC_MR_MODE_Msk (0x7u << MPDDRC_MR_MODE_Pos) /**< \brief (MPDDRC_MR) MPDDRC Command Mode */
#define MPDDRC_MR_MODE(value) ((MPDDRC_MR_MODE_Msk & ((value) << MPDDRC_MR_MODE_Pos)))
#define   MPDDRC_MR_MODE_NORMAL_CMD (0x0u << 0) /**< \brief (MPDDRC_MR) Normal Mode. Any access to the MPDDRC is decoded normally. To activate this mode, the command must be followed by a write to the DDR-SDRAM. */
#define   MPDDRC_MR_MODE_NOP_CMD (0x1u << 0) /**< \brief (MPDDRC_MR) The MPDDRC issues a NOP command when the DDR-SDRAM device is accessed regardless of the cycle. To activate this mode, the command must be followed by a write to the DDR-SDRAM. */
#define   MPDDRC_MR_MODE_PRCGALL_CMD (0x2u << 0) /**< \brief (MPDDRC_MR) The MPDDRC issues the All Banks Precharge command when the DDR-SDRAM device is accessed regardless of the cycle. To activate this mode, the command must be followed by a write to the SDRAM. */
#define   MPDDRC_MR_MODE_LMR_CMD (0x3u << 0) /**< \brief (MPDDRC_MR) The MPDDRC issues a Load Mode Register command when the DDR-SDRAM device is accessed regardless of the cycle. To activate this mode, the command must be followed by a write to the DDR-SDRAM. */
#define   MPDDRC_MR_MODE_RFSH_CMD (0x4u << 0) /**< \brief (MPDDRC_MR) The MPDDRC issues an Autorefresh command when the DDR-SDRAM device is accessed regardless of the cycle. Previously, an All Banks Precharge command must be issued. To activate this mode, the command must be followed by a write to the DDR-SDRAM. */
#define   MPDDRC_MR_MODE_EXT_LMR_CMD (0x5u << 0) /**< \brief (MPDDRC_MR) The MPDDRC issues an Extended Load Mode Register command when the SDRAM device is accessed regardless of the cycle. To activate this mode, the command must be followed by a write to the DDR-SDRAM. The write in the DDR-SDRAM must be done in the appropriate bank. */
#define   MPDDRC_MR_MODE_DEEP_MD (0x6u << 0) /**< \brief (MPDDRC_MR) Deep Power mode: Access to Deep Powerdown mode */
/* -------- MPDDRC_RTR : (MPDDRC Offset: 0x4) Refresh Timer Register -------- */
#define MPDDRC_RTR_COUNT_Pos 0
#define MPDDRC_RTR_COUNT_Msk (0xfffu << MPDDRC_RTR_COUNT_Pos) /**< \brief (MPDDRC_RTR) MPDDRC Refresh Timer Count */
#define MPDDRC_RTR_COUNT(value) ((MPDDRC_RTR_COUNT_Msk & ((value) << MPDDRC_RTR_COUNT_Pos)))
/* -------- MPDDRC_CR : (MPDDRC Offset: 0x8) Configuration Register -------- */
#define MPDDRC_CR_NC_Pos 0
#define MPDDRC_CR_NC_Msk (0x3u << MPDDRC_CR_NC_Pos) /**< \brief (MPDDRC_CR) Number of Column Bits */
#define MPDDRC_CR_NC(value) ((MPDDRC_CR_NC_Msk & ((value) << MPDDRC_CR_NC_Pos)))
#define   MPDDRC_CR_NC_DDR_9_COL_BITS (0x0u << 0) /**< \brief (MPDDRC_CR) 9 bits to define the column number, up to 512 columns, for DDR2-SDRAM 8 bits to define the column number, up to 256 columns, for LPDDR1-SDRAM */
#define   MPDDRC_CR_NC_DDR_10_COL_BITS (0x1u << 0) /**< \brief (MPDDRC_CR) 10 bits to define the column number, up to 1024 columns, for DDR2-SDRAM 9 bits to define the column number, up to 512 columns, for LPDDR1-SDRAM */
#define   MPDDRC_CR_NC_DDR_11_COL_BITS (0x2u << 0) /**< \brief (MPDDRC_CR) 11 bits to define the column number, up to 2048 columns, for DDR2-SDRAM 10 bits to define the column number, up to 1024 columns, for LPDDR1-SDRAM */
#define   MPDDRC_CR_NC_DDR_12_COL_BITS (0x3u << 0) /**< \brief (MPDDRC_CR) 12 bits to define the column number, up to 4096 columns, for DDR2-SDRAM 11 bits to define the column number, up to 2048 columns, for LPDDR1-SDRAM */
#define MPDDRC_CR_NR_Pos 2
#define MPDDRC_CR_NR_Msk (0x3u << MPDDRC_CR_NR_Pos) /**< \brief (MPDDRC_CR) Number of Row Bits */
#define MPDDRC_CR_NR(value) ((MPDDRC_CR_NR_Msk & ((value) << MPDDRC_CR_NR_Pos)))
#define   MPDDRC_CR_NR_11_ROW_BITS (0x0u << 2) /**< \brief (MPDDRC_CR) 11 bits to define the row number, up to 2048 rows */
#define   MPDDRC_CR_NR_12_ROW_BITS (0x1u << 2) /**< \brief (MPDDRC_CR) 12 bits to define the row number, up to 4096 rows */
#define   MPDDRC_CR_NR_13_ROW_BITS (0x2u << 2) /**< \brief (MPDDRC_CR) 13 bits to define the row number, up to 8192 rows */
#define   MPDDRC_CR_NR_14_ROW_BITS (0x3u << 2) /**< \brief (MPDDRC_CR) 14 bits to define the row number, up to 16384 rows */
#define MPDDRC_CR_CAS_Pos 4
#define MPDDRC_CR_CAS_Msk (0x7u << MPDDRC_CR_CAS_Pos) /**< \brief (MPDDRC_CR) CAS Latency */
#define MPDDRC_CR_CAS(value) ((MPDDRC_CR_CAS_Msk & ((value) << MPDDRC_CR_CAS_Pos)))
#define   MPDDRC_CR_CAS_DDR_CAS2 (0x2u << 4) /**< \brief (MPDDRC_CR) LPDDR1 CAS Latency 2 */
#define   MPDDRC_CR_CAS_DDR_CAS3 (0x3u << 4) /**< \brief (MPDDRC_CR) DDR2/LPDDR1 CAS Latency 3 */
#define MPDDRC_CR_DLL (0x1u << 7) /**< \brief (MPDDRC_CR) Reset DLL */
#define   MPDDRC_CR_DLL_RESET_DISABLED (0x0u << 7) /**< \brief (MPDDRC_CR) Disable DLL reset */
#define   MPDDRC_CR_DLL_RESET_ENABLED (0x1u << 7) /**< \brief (MPDDRC_CR) Enable DLL reset */
#define MPDDRC_CR_DIC_DS (0x1u << 8) /**< \brief (MPDDRC_CR) Output Driver Impedance Control (Drive Strength) */
#define   MPDDRC_CR_DIC_DS_DDR2_NORMALSTRENGTH (0x0u << 8) /**< \brief (MPDDRC_CR) Normal drive strength (DDR2) */
#define   MPDDRC_CR_DIC_DS_DDR2_WEAKSTRENGTH (0x1u << 8) /**< \brief (MPDDRC_CR) Weak drive strength (DDR2) */
#define MPDDRC_CR_DIS_DLL (0x1u << 9) /**< \brief (MPDDRC_CR) Disable DLL */
#define MPDDRC_CR_OCD_Pos 12
#define MPDDRC_CR_OCD_Msk (0x7u << MPDDRC_CR_OCD_Pos) /**< \brief (MPDDRC_CR) Off-chip Driver */
#define MPDDRC_CR_OCD(value) ((MPDDRC_CR_OCD_Msk & ((value) << MPDDRC_CR_OCD_Pos)))
#define   MPDDRC_CR_OCD_DDR2_EXITCALIB (0x0u << 12) /**< \brief (MPDDRC_CR) Exit from OCD Calibration mode and maintain settings */
#define   MPDDRC_CR_OCD_DDR2_DEFAULT_CALIB (0x7u << 12) /**< \brief (MPDDRC_CR) OCD calibration default */
#define MPDDRC_CR_DQMS (0x1u << 16) /**< \brief (MPDDRC_CR) Mask Data is Shared */
#define   MPDDRC_CR_DQMS_NOT_SHARED (0x0u << 16) /**< \brief (MPDDRC_CR) DQM is not shared with another controller */
#define   MPDDRC_CR_DQMS_SHARED (0x1u << 16) /**< \brief (MPDDRC_CR) DQM is shared with another controller */
#define MPDDRC_CR_LC_LPDDR1 (0x1u << 19) /**< \brief (MPDDRC_CR) Low-cost Low-power DDR1 */
#define   MPDDRC_CR_LC_LPDDR1_NOT_2_BANKS (0x0u << 19) /**< \brief (MPDDRC_CR) Any type of memory devices except of low cost, low density Low Power DDR1. */
#define   MPDDRC_CR_LC_LPDDR1_2_BANKS_LPDDR1 (0x1u << 19) /**< \brief (MPDDRC_CR) Low-cost and low-density low-power DDR1. These devices have a density of 32 Mbits and are organized as two internal banks. To use this feature, the user has to define the type of memory and the data bus width (see Section 8.8 "MPDDRC Memory Device Register"). The 16-bit memory device is organized as 2 banks, 9 columns and 11 rows. */
#define MPDDRC_CR_NB (0x1u << 20) /**< \brief (MPDDRC_CR) Number of Banks */
#define   MPDDRC_CR_NB_4_BANKS (0x0u << 20) /**< \brief (MPDDRC_CR) 4-bank memory devices */
#define   MPDDRC_CR_NB_8_BANKS (0x1u << 20) /**< \brief (MPDDRC_CR) 8 banks. Only possible when using DDR2-SDRAM devices. */
#define MPDDRC_CR_NDQS (0x1u << 21) /**< \brief (MPDDRC_CR) Not DQS. */
#define   MPDDRC_CR_NDQS_ENABLED (0x0u << 21) /**< \brief (MPDDRC_CR) 'Not DQS' is enabled. */
#define   MPDDRC_CR_NDQS_DISABLED (0x1u << 21) /**< \brief (MPDDRC_CR) 'Not DQS' is disabled. */
#define MPDDRC_CR_DECOD (0x1u << 22) /**< \brief (MPDDRC_CR) Type of Decoding */
#define   MPDDRC_CR_DECOD_SEQUENTIAL (0x0u << 22) /**< \brief (MPDDRC_CR) Method for address mapping where banks alternate at each last DDR-SDRAM page of the current bank. */
#define   MPDDRC_CR_DECOD_INTERLEAVED (0x1u << 22) /**< \brief (MPDDRC_CR) Method for address mapping where banks alternate at each DDR-SDRAM end of page of the current bank. */
#define MPDDRC_CR_UNAL (0x1u << 23) /**< \brief (MPDDRC_CR) This bit must always be written to 1 */
/* -------- MPDDRC_TPR0 : (MPDDRC Offset: 0xC) Timing Parameter 0 Register -------- */
#define MPDDRC_TPR0_TRAS_Pos 0
#define MPDDRC_TPR0_TRAS_Msk (0xfu << MPDDRC_TPR0_TRAS_Pos) /**< \brief (MPDDRC_TPR0) Active to Precharge Delay */
#define MPDDRC_TPR0_TRAS(value) ((MPDDRC_TPR0_TRAS_Msk & ((value) << MPDDRC_TPR0_TRAS_Pos)))
#define MPDDRC_TPR0_TRCD_Pos 4
#define MPDDRC_TPR0_TRCD_Msk (0xfu << MPDDRC_TPR0_TRCD_Pos) /**< \brief (MPDDRC_TPR0) Row to Column Delay */
#define MPDDRC_TPR0_TRCD(value) ((MPDDRC_TPR0_TRCD_Msk & ((value) << MPDDRC_TPR0_TRCD_Pos)))
#define MPDDRC_TPR0_TWR_Pos 8
#define MPDDRC_TPR0_TWR_Msk (0xfu << MPDDRC_TPR0_TWR_Pos) /**< \brief (MPDDRC_TPR0) Write Recovery Delay */
#define MPDDRC_TPR0_TWR(value) ((MPDDRC_TPR0_TWR_Msk & ((value) << MPDDRC_TPR0_TWR_Pos)))
#define MPDDRC_TPR0_TRC_Pos 12
#define MPDDRC_TPR0_TRC_Msk (0xfu << MPDDRC_TPR0_TRC_Pos) /**< \brief (MPDDRC_TPR0) Row Cycle Delay */
#define MPDDRC_TPR0_TRC(value) ((MPDDRC_TPR0_TRC_Msk & ((value) << MPDDRC_TPR0_TRC_Pos)))
#define MPDDRC_TPR0_TRP_Pos 16
#define MPDDRC_TPR0_TRP_Msk (0xfu << MPDDRC_TPR0_TRP_Pos) /**< \brief (MPDDRC_TPR0) Row Precharge Delay */
#define MPDDRC_TPR0_TRP(value) ((MPDDRC_TPR0_TRP_Msk & ((value) << MPDDRC_TPR0_TRP_Pos)))
#define MPDDRC_TPR0_TRRD_Pos 20
#define MPDDRC_TPR0_TRRD_Msk (0xfu << MPDDRC_TPR0_TRRD_Pos) /**< \brief (MPDDRC_TPR0) Active BankA to Active BankB */
#define MPDDRC_TPR0_TRRD(value) ((MPDDRC_TPR0_TRRD_Msk & ((value) << MPDDRC_TPR0_TRRD_Pos)))
#define MPDDRC_TPR0_TWTR_Pos 24
#define MPDDRC_TPR0_TWTR_Msk (0x7u << MPDDRC_TPR0_TWTR_Pos) /**< \brief (MPDDRC_TPR0) Internal Write to Read Delay */
#define MPDDRC_TPR0_TWTR(value) ((MPDDRC_TPR0_TWTR_Msk & ((value) << MPDDRC_TPR0_TWTR_Pos)))
#define MPDDRC_TPR0_TMRD_Pos 28
#define MPDDRC_TPR0_TMRD_Msk (0xfu << MPDDRC_TPR0_TMRD_Pos) /**< \brief (MPDDRC_TPR0) Load Mode Register Command to Activate or Refresh Command */
#define MPDDRC_TPR0_TMRD(value) ((MPDDRC_TPR0_TMRD_Msk & ((value) << MPDDRC_TPR0_TMRD_Pos)))
/* -------- MPDDRC_TPR1 : (MPDDRC Offset: 0x10) Timing Parameter 1 Register -------- */
#define MPDDRC_TPR1_TRFC_Pos 0
#define MPDDRC_TPR1_TRFC_Msk (0x7fu << MPDDRC_TPR1_TRFC_Pos) /**< \brief (MPDDRC_TPR1) Row Refresh Cycle */
#define MPDDRC_TPR1_TRFC(value) ((MPDDRC_TPR1_TRFC_Msk & ((value) << MPDDRC_TPR1_TRFC_Pos)))
#define MPDDRC_TPR1_TXSNR_Pos 8
#define MPDDRC_TPR1_TXSNR_Msk (0xffu << MPDDRC_TPR1_TXSNR_Pos) /**< \brief (MPDDRC_TPR1) Exit Self-refresh Delay to Non-Read Command */
#define MPDDRC_TPR1_TXSNR(value) ((MPDDRC_TPR1_TXSNR_Msk & ((value) << MPDDRC_TPR1_TXSNR_Pos)))
#define MPDDRC_TPR1_TXSRD_Pos 16
#define MPDDRC_TPR1_TXSRD_Msk (0xffu << MPDDRC_TPR1_TXSRD_Pos) /**< \brief (MPDDRC_TPR1) Exit Self-refresh Delay to Read Command */
#define MPDDRC_TPR1_TXSRD(value) ((MPDDRC_TPR1_TXSRD_Msk & ((value) << MPDDRC_TPR1_TXSRD_Pos)))
#define MPDDRC_TPR1_TXP_Pos 24
#define MPDDRC_TPR1_TXP_Msk (0xfu << MPDDRC_TPR1_TXP_Pos) /**< \brief (MPDDRC_TPR1) Exit Powerdown Delay to First Command */
#define MPDDRC_TPR1_TXP(value) ((MPDDRC_TPR1_TXP_Msk & ((value) << MPDDRC_TPR1_TXP_Pos)))
/* -------- MPDDRC_TPR2 : (MPDDRC Offset: 0x14) Timing Parameter 2 Register -------- */
#define MPDDRC_TPR2_TXARD_Pos 0
#define MPDDRC_TPR2_TXARD_Msk (0xfu << MPDDRC_TPR2_TXARD_Pos) /**< \brief (MPDDRC_TPR2) Exit Active Power Down Delay to Read Command in Mode "Fast Exit" */
#define MPDDRC_TPR2_TXARD(value) ((MPDDRC_TPR2_TXARD_Msk & ((value) << MPDDRC_TPR2_TXARD_Pos)))
#define MPDDRC_TPR2_TXARDS_Pos 4
#define MPDDRC_TPR2_TXARDS_Msk (0xfu << MPDDRC_TPR2_TXARDS_Pos) /**< \brief (MPDDRC_TPR2) Exit Active Power Down Delay to Read Command in Mode "Slow Exit" */
#define MPDDRC_TPR2_TXARDS(value) ((MPDDRC_TPR2_TXARDS_Msk & ((value) << MPDDRC_TPR2_TXARDS_Pos)))
#define MPDDRC_TPR2_TRPA_Pos 8
#define MPDDRC_TPR2_TRPA_Msk (0xfu << MPDDRC_TPR2_TRPA_Pos) /**< \brief (MPDDRC_TPR2) Row Precharge All Delay */
#define MPDDRC_TPR2_TRPA(value) ((MPDDRC_TPR2_TRPA_Msk & ((value) << MPDDRC_TPR2_TRPA_Pos)))
#define MPDDRC_TPR2_TRTP_Pos 12
#define MPDDRC_TPR2_TRTP_Msk (0x7u << MPDDRC_TPR2_TRTP_Pos) /**< \brief (MPDDRC_TPR2) Read to Precharge */
#define MPDDRC_TPR2_TRTP(value) ((MPDDRC_TPR2_TRTP_Msk & ((value) << MPDDRC_TPR2_TRTP_Pos)))
#define MPDDRC_TPR2_TFAW_Pos 16
#define MPDDRC_TPR2_TFAW_Msk (0xfu << MPDDRC_TPR2_TFAW_Pos) /**< \brief (MPDDRC_TPR2) Four Active Windows */
#define MPDDRC_TPR2_TFAW(value) ((MPDDRC_TPR2_TFAW_Msk & ((value) << MPDDRC_TPR2_TFAW_Pos)))
/* -------- MPDDRC_LPR : (MPDDRC Offset: 0x1C) Low-Power Register -------- */
#define MPDDRC_LPR_LPCB_Pos 0
#define MPDDRC_LPR_LPCB_Msk (0x3u << MPDDRC_LPR_LPCB_Pos) /**< \brief (MPDDRC_LPR) Low-power Command Bit */
#define MPDDRC_LPR_LPCB(value) ((MPDDRC_LPR_LPCB_Msk & ((value) << MPDDRC_LPR_LPCB_Pos)))
#define   MPDDRC_LPR_LPCB_NOLOWPOWER (0x0u << 0) /**< \brief (MPDDRC_LPR) Low-power feature is inhibited. No Powerdown, Self-refresh and Deep power modes are issued to the DDR-SDRAM device. */
#define   MPDDRC_LPR_LPCB_SELFREFRESH (0x1u << 0) /**< \brief (MPDDRC_LPR) The MPDDRC issues a self-refresh command to the DDR-SDRAM device, the clock(s) is/are deactivated and the CKE signal is set low. The DDR-SDRAM device leaves the Self-refresh mode when accessed and reenters it after the access. */
#define   MPDDRC_LPR_LPCB_POWERDOWN (0x2u << 0) /**< \brief (MPDDRC_LPR) The MPDDRC issues a Powerdown command to the DDR-SDRAM device after each access, the CKE signal is set low. The DDR-SDRAM device leaves the Powerdown mode when accessed and reenters it after the access. */
#define   MPDDRC_LPR_LPCB_DEEPPOWERDOWN (0x3u << 0) /**< \brief (MPDDRC_LPR) The MPDDRC issues a Deep Powerdown command to the low-power DDR-SDRAM device. */
#define MPDDRC_LPR_CLK_FR (0x1u << 2) /**< \brief (MPDDRC_LPR) Clock Frozen Command Bit */
#define   MPDDRC_LPR_CLK_FR_DISABLED (0x0u << 2) /**< \brief (MPDDRC_LPR) Clock(s) is/are not frozen. */
#define   MPDDRC_LPR_CLK_FR_ENABLED (0x1u << 2) /**< \brief (MPDDRC_LPR) Clock(s) is/are frozen. */
#define MPDDRC_LPR_PASR_Pos 4
#define MPDDRC_LPR_PASR_Msk (0x7u << MPDDRC_LPR_PASR_Pos) /**< \brief (MPDDRC_LPR) Partial Array Self-refresh */
#define MPDDRC_LPR_PASR(value) ((MPDDRC_LPR_PASR_Msk & ((value) << MPDDRC_LPR_PASR_Pos)))
#define MPDDRC_LPR_DS_Pos 8
#define MPDDRC_LPR_DS_Msk (0x7u << MPDDRC_LPR_DS_Pos) /**< \brief (MPDDRC_LPR) Drive Strength */
#define MPDDRC_LPR_DS(value) ((MPDDRC_LPR_DS_Msk & ((value) << MPDDRC_LPR_DS_Pos)))
#define   MPDDRC_LPR_DS_DS_FULL (0x0u << 8) /**< \brief (MPDDRC_LPR) Full drive strength */
#define   MPDDRC_LPR_DS_DS_HALF (0x1u << 8) /**< \brief (MPDDRC_LPR) Half drive strength */
#define   MPDDRC_LPR_DS_DS_QUARTER (0x2u << 8) /**< \brief (MPDDRC_LPR) Quarter drive strength */
#define   MPDDRC_LPR_DS_DS_OCTANT (0x3u << 8) /**< \brief (MPDDRC_LPR) Octant drive strength */
#define MPDDRC_LPR_TIMEOUT_Pos 12
#define MPDDRC_LPR_TIMEOUT_Msk (0x3u << MPDDRC_LPR_TIMEOUT_Pos) /**< \brief (MPDDRC_LPR) Time Between Last Transfer and Low-Power Mode */
#define MPDDRC_LPR_TIMEOUT(value) ((MPDDRC_LPR_TIMEOUT_Msk & ((value) << MPDDRC_LPR_TIMEOUT_Pos)))
#define   MPDDRC_LPR_TIMEOUT_NONE (0x0u << 12) /**< \brief (MPDDRC_LPR) SDRAM Low-power mode is activated immediately after the end of the last transfer. */
#define   MPDDRC_LPR_TIMEOUT_DELAY_64_CLK (0x1u << 12) /**< \brief (MPDDRC_LPR) SDRAM Low-power mode is activated 64 clock cycles after the end of the last transfer. */
#define   MPDDRC_LPR_TIMEOUT_DELAY_128_CLK (0x2u << 12) /**< \brief (MPDDRC_LPR) SDRAM Low-power mode is activated 128 clock cycles after the end of the last transfer. */
#define MPDDRC_LPR_SELFAUTO (0x1u << 14) /**< \brief (MPDDRC_LPR) Self-refresh Exit Autorefresh */
#define MPDDRC_LPR_APDE (0x1u << 16) /**< \brief (MPDDRC_LPR) Active Power Down Exit Time */
#define   MPDDRC_LPR_APDE_DDR2_FAST_EXIT (0x0u << 16) /**< \brief (MPDDRC_LPR) Fast Exit from Power Down. DDR2-SDRAM devices only. */
#define   MPDDRC_LPR_APDE_DDR2_SLOW_EXIT (0x1u << 16) /**< \brief (MPDDRC_LPR) Slow Exit from Power Down. DDR2-SDRAM devices only. */
#define MPDDRC_LPR_UPD_MR_Pos 20
#define MPDDRC_LPR_UPD_MR_Msk (0x3u << MPDDRC_LPR_UPD_MR_Pos) /**< \brief (MPDDRC_LPR) Update Load Mode Register and Extended Mode Register */
#define MPDDRC_LPR_UPD_MR(value) ((MPDDRC_LPR_UPD_MR_Msk & ((value) << MPDDRC_LPR_UPD_MR_Pos)))
#define   MPDDRC_LPR_UPD_MR_NO_UPDATE (0x0u << 20) /**< \brief (MPDDRC_LPR) Update of Load Mode and Extended Mode registers is disabled. */
#define   MPDDRC_LPR_UPD_MR_UPDATE_SHAREDBUS (0x1u << 20) /**< \brief (MPDDRC_LPR) MPDDRC shares an external bus. Automatic update is done during a refresh command and a pending read or write access in the SDRAM device. */
#define   MPDDRC_LPR_UPD_MR_UPDATE_NOSHAREDBUS (0x2u << 20) /**< \brief (MPDDRC_LPR) MPDDRC does not share an external bus. Automatic update is done before entering Self-refresh mode. */
#define MPDDRC_LPR_CHG_FRQ (0x1u << 24) /**< \brief (MPDDRC_LPR) Change Clock Frequency During Self-refresh Mode */
#define MPDDRC_LPR_SELF_DONE (0x1u << 25) /**< \brief (MPDDRC_LPR) Self-refresh is Done (read-only) */
/* -------- MPDDRC_MD : (MPDDRC Offset: 0x20) Memory Device Register -------- */
#define MPDDRC_MD_MD_Pos 0
#define MPDDRC_MD_MD_Msk (0x7u << MPDDRC_MD_MD_Pos) /**< \brief (MPDDRC_MD) Memory Device */
#define MPDDRC_MD_MD(value) ((MPDDRC_MD_MD_Msk & ((value) << MPDDRC_MD_MD_Pos)))
#define   MPDDRC_MD_MD_LPDDR_SDRAM (0x3u << 0) /**< \brief (MPDDRC_MD) Low-power DDR1-SDRAM */
#define   MPDDRC_MD_MD_DDR2_SDRAM (0x6u << 0) /**< \brief (MPDDRC_MD) DDR2-SDRAM */
#define MPDDRC_MD_DBW (0x1u << 4) /**< \brief (MPDDRC_MD) Data Bus Width */
#define   MPDDRC_MD_DBW_DBW_16_BITS (0x1u << 4) /**< \brief (MPDDRC_MD) Data bus width is 16 bits. */
/* -------- MPDDRC_IO_CALIBR : (MPDDRC Offset: 0x34) I/O Calibration Register -------- */
#define MPDDRC_IO_CALIBR_CK_F_RANGE_Pos 0
#define MPDDRC_IO_CALIBR_CK_F_RANGE_Msk (0x7u << MPDDRC_IO_CALIBR_CK_F_RANGE_Pos) /**< \brief (MPDDRC_IO_CALIBR) DDRCK Maximum Clock Frequency Range Indicator */
#define MPDDRC_IO_CALIBR_CK_F_RANGE(value) ((MPDDRC_IO_CALIBR_CK_F_RANGE_Msk & ((value) << MPDDRC_IO_CALIBR_CK_F_RANGE_Pos)))
#define MPDDRC_IO_CALIBR_TZQIO_Pos 8
#define MPDDRC_IO_CALIBR_TZQIO_Msk (0x7fu << MPDDRC_IO_CALIBR_TZQIO_Pos) /**< \brief (MPDDRC_IO_CALIBR) IO Calibration */
#define MPDDRC_IO_CALIBR_TZQIO(value) ((MPDDRC_IO_CALIBR_TZQIO_Msk & ((value) << MPDDRC_IO_CALIBR_TZQIO_Pos)))
#define MPDDRC_IO_CALIBR_CALCODEP_Pos 16
#define MPDDRC_IO_CALIBR_CALCODEP_Msk (0xfu << MPDDRC_IO_CALIBR_CALCODEP_Pos) /**< \brief (MPDDRC_IO_CALIBR) Number of P-type Transistors (read-only) */
#define MPDDRC_IO_CALIBR_CALCODEP(value) ((MPDDRC_IO_CALIBR_CALCODEP_Msk & ((value) << MPDDRC_IO_CALIBR_CALCODEP_Pos)))
#define MPDDRC_IO_CALIBR_CALCODEN_Pos 20
#define MPDDRC_IO_CALIBR_CALCODEN_Msk (0xfu << MPDDRC_IO_CALIBR_CALCODEN_Pos) /**< \brief (MPDDRC_IO_CALIBR) Number of N-type Transistors (read-only) */
#define MPDDRC_IO_CALIBR_CALCODEN(value) ((MPDDRC_IO_CALIBR_CALCODEN_Msk & ((value) << MPDDRC_IO_CALIBR_CALCODEN_Pos)))
/* -------- MPDDRC_OCMS : (MPDDRC Offset: 0x38) OCMS Register -------- */
#define MPDDRC_OCMS_SCR_EN (0x1u << 0) /**< \brief (MPDDRC_OCMS) Scrambling Enable */
#define MPDDRC_OCMS_TAMPCLR (0x1u << 4) /**< \brief (MPDDRC_OCMS) Tamper Clear Enable */
/* -------- MPDDRC_OCMS_KEY1 : (MPDDRC Offset: 0x3C) OCMS KEY1 Register -------- */
#define MPDDRC_OCMS_KEY1_KEY1_Pos 0
#define MPDDRC_OCMS_KEY1_KEY1_Msk (0xffffffffu << MPDDRC_OCMS_KEY1_KEY1_Pos) /**< \brief (MPDDRC_OCMS_KEY1) Off-chip Memory Scrambling (OCMS) Key Part 1 */
#define MPDDRC_OCMS_KEY1_KEY1(value) ((MPDDRC_OCMS_KEY1_KEY1_Msk & ((value) << MPDDRC_OCMS_KEY1_KEY1_Pos)))
/* -------- MPDDRC_OCMS_KEY2 : (MPDDRC Offset: 0x40) OCMS KEY2 Register -------- */
#define MPDDRC_OCMS_KEY2_KEY2_Pos 0
#define MPDDRC_OCMS_KEY2_KEY2_Msk (0xffffffffu << MPDDRC_OCMS_KEY2_KEY2_Pos) /**< \brief (MPDDRC_OCMS_KEY2) Off-chip Memory Scrambling (OCMS) Key Part 2 */
#define MPDDRC_OCMS_KEY2_KEY2(value) ((MPDDRC_OCMS_KEY2_KEY2_Msk & ((value) << MPDDRC_OCMS_KEY2_KEY2_Pos)))
/* -------- MPDDRC_CONF_ARBITER : (MPDDRC Offset: 0x44) Configuration Arbiter Register -------- */
#define MPDDRC_CONF_ARBITER_ARB_Pos 0
#define MPDDRC_CONF_ARBITER_ARB_Msk (0x3u << MPDDRC_CONF_ARBITER_ARB_Pos) /**< \brief (MPDDRC_CONF_ARBITER) Type of Arbitration */
#define MPDDRC_CONF_ARBITER_ARB(value) ((MPDDRC_CONF_ARBITER_ARB_Msk & ((value) << MPDDRC_CONF_ARBITER_ARB_Pos)))
#define   MPDDRC_CONF_ARBITER_ARB_ROUND (0x0u << 0) /**< \brief (MPDDRC_CONF_ARBITER) Round-Robin Policy */
#define   MPDDRC_CONF_ARBITER_ARB_NB_REQUEST (0x1u << 0) /**< \brief (MPDDRC_CONF_ARBITER) Request Policy */
#define   MPDDRC_CONF_ARBITER_ARB_BANDWIDTH (0x2u << 0) /**< \brief (MPDDRC_CONF_ARBITER) Bandwidth Policy */
#define   MPDDRC_CONF_ARBITER_ARB_LQOS (0x3u << 0) /**< \brief (MPDDRC_CONF_ARBITER) Quality of Service Policy */
#define MPDDRC_CONF_ARBITER_BDW_MAX_CUR (0x1u << 3) /**< \brief (MPDDRC_CONF_ARBITER) Bandwidth Max or Current */
#define MPDDRC_CONF_ARBITER_RQ_WD_P0 (0x1u << 8) /**< \brief (MPDDRC_CONF_ARBITER) Request or Word from Port X */
#define MPDDRC_CONF_ARBITER_RQ_WD_P1 (0x1u << 9) /**< \brief (MPDDRC_CONF_ARBITER) Request or Word from Port X */
#define MPDDRC_CONF_ARBITER_RQ_WD_P2 (0x1u << 10) /**< \brief (MPDDRC_CONF_ARBITER) Request or Word from Port X */
#define MPDDRC_CONF_ARBITER_RQ_WD_P3 (0x1u << 11) /**< \brief (MPDDRC_CONF_ARBITER) Request or Word from Port X */
#define MPDDRC_CONF_ARBITER_MA_PR_P0 (0x1u << 16) /**< \brief (MPDDRC_CONF_ARBITER) Master or Software Provide Information */
#define MPDDRC_CONF_ARBITER_MA_PR_P1 (0x1u << 17) /**< \brief (MPDDRC_CONF_ARBITER) Master or Software Provide Information */
#define MPDDRC_CONF_ARBITER_MA_PR_P2 (0x1u << 18) /**< \brief (MPDDRC_CONF_ARBITER) Master or Software Provide Information */
#define MPDDRC_CONF_ARBITER_MA_PR_P3 (0x1u << 19) /**< \brief (MPDDRC_CONF_ARBITER) Master or Software Provide Information */
#define MPDDRC_CONF_ARBITER_BDW_BURST_P0 (0x1u << 24) /**< \brief (MPDDRC_CONF_ARBITER) Bandwidth Arbitration Mode on Port X */
#define MPDDRC_CONF_ARBITER_BDW_BURST_P1 (0x1u << 25) /**< \brief (MPDDRC_CONF_ARBITER) Bandwidth Arbitration Mode on Port X */
#define MPDDRC_CONF_ARBITER_BDW_BURST_P2 (0x1u << 26) /**< \brief (MPDDRC_CONF_ARBITER) Bandwidth Arbitration Mode on Port X */
#define MPDDRC_CONF_ARBITER_BDW_BURST_P3 (0x1u << 27) /**< \brief (MPDDRC_CONF_ARBITER) Bandwidth Arbitration Mode on Port X */
/* -------- MPDDRC_TIMEOUT : (MPDDRC Offset: 0x48) Timeout Register -------- */
#define MPDDRC_TIMEOUT_TIMEOUT_P0_Pos 0
#define MPDDRC_TIMEOUT_TIMEOUT_P0_Msk (0xfu << MPDDRC_TIMEOUT_TIMEOUT_P0_Pos) /**< \brief (MPDDRC_TIMEOUT) Timeout for Ports 0, 1, 2, 3 */
#define MPDDRC_TIMEOUT_TIMEOUT_P0(value) ((MPDDRC_TIMEOUT_TIMEOUT_P0_Msk & ((value) << MPDDRC_TIMEOUT_TIMEOUT_P0_Pos)))
#define MPDDRC_TIMEOUT_TIMEOUT_P1_Pos 4
#define MPDDRC_TIMEOUT_TIMEOUT_P1_Msk (0xfu << MPDDRC_TIMEOUT_TIMEOUT_P1_Pos) /**< \brief (MPDDRC_TIMEOUT) Timeout for Ports 0, 1, 2, 3 */
#define MPDDRC_TIMEOUT_TIMEOUT_P1(value) ((MPDDRC_TIMEOUT_TIMEOUT_P1_Msk & ((value) << MPDDRC_TIMEOUT_TIMEOUT_P1_Pos)))
#define MPDDRC_TIMEOUT_TIMEOUT_P2_Pos 8
#define MPDDRC_TIMEOUT_TIMEOUT_P2_Msk (0xfu << MPDDRC_TIMEOUT_TIMEOUT_P2_Pos) /**< \brief (MPDDRC_TIMEOUT) Timeout for Ports 0, 1, 2, 3 */
#define MPDDRC_TIMEOUT_TIMEOUT_P2(value) ((MPDDRC_TIMEOUT_TIMEOUT_P2_Msk & ((value) << MPDDRC_TIMEOUT_TIMEOUT_P2_Pos)))
#define MPDDRC_TIMEOUT_TIMEOUT_P3_Pos 12
#define MPDDRC_TIMEOUT_TIMEOUT_P3_Msk (0xfu << MPDDRC_TIMEOUT_TIMEOUT_P3_Pos) /**< \brief (MPDDRC_TIMEOUT) Timeout for Ports 0, 1, 2, 3 */
#define MPDDRC_TIMEOUT_TIMEOUT_P3(value) ((MPDDRC_TIMEOUT_TIMEOUT_P3_Msk & ((value) << MPDDRC_TIMEOUT_TIMEOUT_P3_Pos)))
/* -------- MPDDRC_REQ_PORT_0123 : (MPDDRC Offset: 0x4C) Request Port 0-1-2-3 Register -------- */
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P0_Pos 0
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P0_Msk (0xffu << MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P0_Pos) /**< \brief (MPDDRC_REQ_PORT_0123) Number of Requests, Number of Words or Bandwidth Allocation from Port 0-1-2-3 */
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P0(value) ((MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P0_Msk & ((value) << MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P0_Pos)))
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P1_Pos 8
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P1_Msk (0xffu << MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P1_Pos) /**< \brief (MPDDRC_REQ_PORT_0123) Number of Requests, Number of Words or Bandwidth Allocation from Port 0-1-2-3 */
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P1(value) ((MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P1_Msk & ((value) << MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P1_Pos)))
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P2_Pos 16
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P2_Msk (0xffu << MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P2_Pos) /**< \brief (MPDDRC_REQ_PORT_0123) Number of Requests, Number of Words or Bandwidth Allocation from Port 0-1-2-3 */
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P2(value) ((MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P2_Msk & ((value) << MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P2_Pos)))
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P3_Pos 24
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P3_Msk (0xffu << MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P3_Pos) /**< \brief (MPDDRC_REQ_PORT_0123) Number of Requests, Number of Words or Bandwidth Allocation from Port 0-1-2-3 */
#define MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P3(value) ((MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P3_Msk & ((value) << MPDDRC_REQ_PORT_0123_NRQ_NWD_BDW_P3_Pos)))
/* -------- MPDDRC_BDW_PORT_0123 : (MPDDRC Offset: 0x54) Current/Maximum Bandwidth Port 0-1-2-3 Register -------- */
#define MPDDRC_BDW_PORT_0123_BDW_P0_Pos 0
#define MPDDRC_BDW_PORT_0123_BDW_P0_Msk (0x7fu << MPDDRC_BDW_PORT_0123_BDW_P0_Pos) /**< \brief (MPDDRC_BDW_PORT_0123) Current/Maximum Bandwidth from Port 0-1-2-3 */
#define MPDDRC_BDW_PORT_0123_BDW_P1_Pos 8
#define MPDDRC_BDW_PORT_0123_BDW_P1_Msk (0x7fu << MPDDRC_BDW_PORT_0123_BDW_P1_Pos) /**< \brief (MPDDRC_BDW_PORT_0123) Current/Maximum Bandwidth from Port 0-1-2-3 */
#define MPDDRC_BDW_PORT_0123_BDW_P2_Pos 16
#define MPDDRC_BDW_PORT_0123_BDW_P2_Msk (0x7fu << MPDDRC_BDW_PORT_0123_BDW_P2_Pos) /**< \brief (MPDDRC_BDW_PORT_0123) Current/Maximum Bandwidth from Port 0-1-2-3 */
#define MPDDRC_BDW_PORT_0123_BDW_P3_Pos 24
#define MPDDRC_BDW_PORT_0123_BDW_P3_Msk (0x7fu << MPDDRC_BDW_PORT_0123_BDW_P3_Pos) /**< \brief (MPDDRC_BDW_PORT_0123) Current/Maximum Bandwidth from Port 0-1-2-3 */
/* -------- MPDDRC_RD_DATA_PATH : (MPDDRC Offset: 0x5C) Read Data Path Register -------- */
#define MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_Pos 0
#define MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_Msk (0x3u << MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_Pos) /**< \brief (MPDDRC_RD_DATA_PATH) Shift Sampling Point of Data */
#define MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING(value) ((MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_Msk & ((value) << MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_Pos)))
#define   MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_NO_SHIFT (0x0u << 0) /**< \brief (MPDDRC_RD_DATA_PATH) Initial sampling point. */
#define   MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_SHIFT_ONE_CYCLE (0x1u << 0) /**< \brief (MPDDRC_RD_DATA_PATH) Sampling point is shifted by one cycle. */
#define   MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_SHIFT_TWO_CYCLES (0x2u << 0) /**< \brief (MPDDRC_RD_DATA_PATH) Sampling point is shifted by two cycles. */
#define   MPDDRC_RD_DATA_PATH_SHIFT_SAMPLING_SHIFT_THREE_CYCLES (0x3u << 0) /**< \brief (MPDDRC_RD_DATA_PATH) Not applicable for DDR2 and LPDDR1 devices. */
/* -------- MPDDRC_MCFGR : (MPDDRC Offset: 0x60) Monitor Configuration Register -------- */
#define MPDDRC_MCFGR_EN_MONI (0x1u << 0) /**< \brief (MPDDRC_MCFGR) Enable Monitor */
#define MPDDRC_MCFGR_SOFT_RESET (0x1u << 1) /**< \brief (MPDDRC_MCFGR) Soft Reset */
#define MPDDRC_MCFGR_RUN (0x1u << 4) /**< \brief (MPDDRC_MCFGR) Control Monitor */
#define MPDDRC_MCFGR_READ_WRITE_Pos 8
#define MPDDRC_MCFGR_READ_WRITE_Msk (0x3u << MPDDRC_MCFGR_READ_WRITE_Pos) /**< \brief (MPDDRC_MCFGR) Read/Write Access */
#define MPDDRC_MCFGR_READ_WRITE(value) ((MPDDRC_MCFGR_READ_WRITE_Msk & ((value) << MPDDRC_MCFGR_READ_WRITE_Pos)))
#define   MPDDRC_MCFGR_READ_WRITE_TRIG_RD_WR (0x0u << 8) /**< \brief (MPDDRC_MCFGR) Read and Write accesses are triggered. */
#define   MPDDRC_MCFGR_READ_WRITE_TRIG_WR (0x1u << 8) /**< \brief (MPDDRC_MCFGR) Only Write accesses are triggered. */
#define   MPDDRC_MCFGR_READ_WRITE_TRIG_RD (0x2u << 8) /**< \brief (MPDDRC_MCFGR) Only Read accesses are triggered. */
#define MPDDRC_MCFGR_REFR_CALIB (0x1u << 10) /**< \brief (MPDDRC_MCFGR) Refresh Calibration */
#define MPDDRC_MCFGR_INFO_Pos 11
#define MPDDRC_MCFGR_INFO_Msk (0x7u << MPDDRC_MCFGR_INFO_Pos) /**< \brief (MPDDRC_MCFGR) Information Type */
#define MPDDRC_MCFGR_INFO(value) ((MPDDRC_MCFGR_INFO_Msk & ((value) << MPDDRC_MCFGR_INFO_Pos)))
#define   MPDDRC_MCFGR_INFO_MAX_WAIT (0x0u << 11) /**< \brief (MPDDRC_MCFGR) Information concerning the transfer with the longest waiting time */
#define   MPDDRC_MCFGR_INFO_NB_TRANSFERS (0x1u << 11) /**< \brief (MPDDRC_MCFGR) Number of transfers on the port */
#define   MPDDRC_MCFGR_INFO_TOTAL_LATENCY (0x2u << 11) /**< \brief (MPDDRC_MCFGR) Total latency on the port */
#define   MPDDRC_MCFGR_INFO_MAX_WAIT_QOS01 (0x4u << 11) /**< \brief (MPDDRC_MCFGR) Information concerning the transfer with the longest waiting time, depending on QOS values (0 and 1) */
#define   MPDDRC_MCFGR_INFO_MAX_WAIT_QOS23 (0x5u << 11) /**< \brief (MPDDRC_MCFGR) Information concerning the transfer with the longest waiting time, depending on QOS values (2 and 3) */
/* -------- MPDDRC_MADDR0 : (MPDDRC Offset: 0x64) Monitor Address High/Low Port 0 Register -------- */
#define MPDDRC_MADDR0_ADDR_LOW_PORT0_Pos 0
#define MPDDRC_MADDR0_ADDR_LOW_PORT0_Msk (0xffffu << MPDDRC_MADDR0_ADDR_LOW_PORT0_Pos) /**< \brief (MPDDRC_MADDR0) Address Low on Port 0 */
#define MPDDRC_MADDR0_ADDR_LOW_PORT0(value) ((MPDDRC_MADDR0_ADDR_LOW_PORT0_Msk & ((value) << MPDDRC_MADDR0_ADDR_LOW_PORT0_Pos)))
#define MPDDRC_MADDR0_ADDR_HIGH_PORT0_Pos 16
#define MPDDRC_MADDR0_ADDR_HIGH_PORT0_Msk (0xffffu << MPDDRC_MADDR0_ADDR_HIGH_PORT0_Pos) /**< \brief (MPDDRC_MADDR0) Address High on Port 0 */
#define MPDDRC_MADDR0_ADDR_HIGH_PORT0(value) ((MPDDRC_MADDR0_ADDR_HIGH_PORT0_Msk & ((value) << MPDDRC_MADDR0_ADDR_HIGH_PORT0_Pos)))
/* -------- MPDDRC_MADDR1 : (MPDDRC Offset: 0x68) Monitor Address High/Low Port 1 Register -------- */
#define MPDDRC_MADDR1_ADDR_LOW_PORT1_Pos 0
#define MPDDRC_MADDR1_ADDR_LOW_PORT1_Msk (0xffffu << MPDDRC_MADDR1_ADDR_LOW_PORT1_Pos) /**< \brief (MPDDRC_MADDR1) Address Low on Port 1 */
#define MPDDRC_MADDR1_ADDR_LOW_PORT1(value) ((MPDDRC_MADDR1_ADDR_LOW_PORT1_Msk & ((value) << MPDDRC_MADDR1_ADDR_LOW_PORT1_Pos)))
#define MPDDRC_MADDR1_ADDR_HIGH_PORT1_Pos 16
#define MPDDRC_MADDR1_ADDR_HIGH_PORT1_Msk (0xffffu << MPDDRC_MADDR1_ADDR_HIGH_PORT1_Pos) /**< \brief (MPDDRC_MADDR1) Address High on Port 1 */
#define MPDDRC_MADDR1_ADDR_HIGH_PORT1(value) ((MPDDRC_MADDR1_ADDR_HIGH_PORT1_Msk & ((value) << MPDDRC_MADDR1_ADDR_HIGH_PORT1_Pos)))
/* -------- MPDDRC_MADDR2 : (MPDDRC Offset: 0x6C) Monitor Address High/Low Port 2 Register -------- */
#define MPDDRC_MADDR2_ADDR_LOW_PORT2_Pos 0
#define MPDDRC_MADDR2_ADDR_LOW_PORT2_Msk (0xffffu << MPDDRC_MADDR2_ADDR_LOW_PORT2_Pos) /**< \brief (MPDDRC_MADDR2) Address Low on Port 2 */
#define MPDDRC_MADDR2_ADDR_LOW_PORT2(value) ((MPDDRC_MADDR2_ADDR_LOW_PORT2_Msk & ((value) << MPDDRC_MADDR2_ADDR_LOW_PORT2_Pos)))
#define MPDDRC_MADDR2_ADDR_HIGH_PORT2_Pos 16
#define MPDDRC_MADDR2_ADDR_HIGH_PORT2_Msk (0xffffu << MPDDRC_MADDR2_ADDR_HIGH_PORT2_Pos) /**< \brief (MPDDRC_MADDR2) Address High on Port 2 */
#define MPDDRC_MADDR2_ADDR_HIGH_PORT2(value) ((MPDDRC_MADDR2_ADDR_HIGH_PORT2_Msk & ((value) << MPDDRC_MADDR2_ADDR_HIGH_PORT2_Pos)))
/* -------- MPDDRC_MADDR3 : (MPDDRC Offset: 0x70) Monitor Address High/Low Port 3 Register -------- */
#define MPDDRC_MADDR3_ADDR_LOW_PORT3_Pos 0
#define MPDDRC_MADDR3_ADDR_LOW_PORT3_Msk (0xffffu << MPDDRC_MADDR3_ADDR_LOW_PORT3_Pos) /**< \brief (MPDDRC_MADDR3) Address Low on Port 3 */
#define MPDDRC_MADDR3_ADDR_LOW_PORT3(value) ((MPDDRC_MADDR3_ADDR_LOW_PORT3_Msk & ((value) << MPDDRC_MADDR3_ADDR_LOW_PORT3_Pos)))
#define MPDDRC_MADDR3_ADDR_HIGH_PORT3_Pos 16
#define MPDDRC_MADDR3_ADDR_HIGH_PORT3_Msk (0xffffu << MPDDRC_MADDR3_ADDR_HIGH_PORT3_Pos) /**< \brief (MPDDRC_MADDR3) Address High on Port 3 */
#define MPDDRC_MADDR3_ADDR_HIGH_PORT3(value) ((MPDDRC_MADDR3_ADDR_HIGH_PORT3_Msk & ((value) << MPDDRC_MADDR3_ADDR_HIGH_PORT3_Pos)))
/* -------- MPDDRC_MINFO0 : (MPDDRC Offset: 0x84) Monitor Information Port 0 Register -------- */
#define MPDDRC_MINFO0_MAX_PORT0_WAITING_Pos 0
#define MPDDRC_MINFO0_MAX_PORT0_WAITING_Msk (0xffffu << MPDDRC_MINFO0_MAX_PORT0_WAITING_Pos) /**< \brief (MPDDRC_MINFO0) Address High on Port 0 */
#define MPDDRC_MINFO0_BURST_Pos 16
#define MPDDRC_MINFO0_BURST_Msk (0x7u << MPDDRC_MINFO0_BURST_Pos) /**< \brief (MPDDRC_MINFO0) Type of Burst on Port 0 */
#define   MPDDRC_MINFO0_BURST_SINGLE (0x0u << 16) /**< \brief (MPDDRC_MINFO0) Single transfer */
#define   MPDDRC_MINFO0_BURST_INCR (0x1u << 16) /**< \brief (MPDDRC_MINFO0) Incrementing burst of unspecified length */
#define   MPDDRC_MINFO0_BURST_WRAP4 (0x2u << 16) /**< \brief (MPDDRC_MINFO0) 4-beat wrapping burst */
#define   MPDDRC_MINFO0_BURST_INCR4 (0x3u << 16) /**< \brief (MPDDRC_MINFO0) 4-beat incrementing burst */
#define   MPDDRC_MINFO0_BURST_WRAP8 (0x4u << 16) /**< \brief (MPDDRC_MINFO0) 8-beat wrapping burst */
#define   MPDDRC_MINFO0_BURST_INCR8 (0x5u << 16) /**< \brief (MPDDRC_MINFO0) 8-beat incrementing burst */
#define   MPDDRC_MINFO0_BURST_WRAP16 (0x6u << 16) /**< \brief (MPDDRC_MINFO0) 16-beat wrapping burst */
#define   MPDDRC_MINFO0_BURST_INCR16 (0x7u << 16) /**< \brief (MPDDRC_MINFO0) 16-beat incrementing burst */
#define MPDDRC_MINFO0_SIZE_Pos 20
#define MPDDRC_MINFO0_SIZE_Msk (0x7u << MPDDRC_MINFO0_SIZE_Pos) /**< \brief (MPDDRC_MINFO0) Transfer Size on Port 0 */
#define   MPDDRC_MINFO0_SIZE_8BITS (0x0u << 20) /**< \brief (MPDDRC_MINFO0) Byte transfer */
#define   MPDDRC_MINFO0_SIZE_16BITS (0x1u << 20) /**< \brief (MPDDRC_MINFO0) Halfword transfer */
#define   MPDDRC_MINFO0_SIZE_32BITS (0x2u << 20) /**< \brief (MPDDRC_MINFO0) Word transfer */
#define   MPDDRC_MINFO0_SIZE_64BITS (0x3u << 20) /**< \brief (MPDDRC_MINFO0) Dword transfer */
#define MPDDRC_MINFO0_READ_WRITE (0x1u << 24) /**< \brief (MPDDRC_MINFO0) Read or Write Access on Port 0 */
#define MPDDRC_MINFO0_LQOS_Pos 25
#define MPDDRC_MINFO0_LQOS_Msk (0x3u << MPDDRC_MINFO0_LQOS_Pos) /**< \brief (MPDDRC_MINFO0) Value of Quality Of Service on Port 0 */
#define   MPDDRC_MINFO0_LQOS_BACKGROUND (0x0u << 25) /**< \brief (MPDDRC_MINFO0) Background transfers */
#define   MPDDRC_MINFO0_LQOS_BANDWIDTH (0x1u << 25) /**< \brief (MPDDRC_MINFO0) Bandwidth sensitive */
#define   MPDDRC_MINFO0_LQOS_SENSITIVE_LAT (0x2u << 25) /**< \brief (MPDDRC_MINFO0) Latency sensitive */
#define   MPDDRC_MINFO0_LQOS_CRITICAL_LAT (0x3u << 25) /**< \brief (MPDDRC_MINFO0) Latency critical */
#define MPDDRC_MINFO0_P0_NB_TRANSFERS_Pos 0
#define MPDDRC_MINFO0_P0_NB_TRANSFERS_Msk (0xffffffffu << MPDDRC_MINFO0_P0_NB_TRANSFERS_Pos) /**< \brief (MPDDRC_MINFO0) Number of Transfers on Port 0 */
#define MPDDRC_MINFO0_P0_TOTAL_LATENCY_Pos 0
#define MPDDRC_MINFO0_P0_TOTAL_LATENCY_Msk (0xffffffffu << MPDDRC_MINFO0_P0_TOTAL_LATENCY_Pos) /**< \brief (MPDDRC_MINFO0) Total Latency on Port 0 */
#define MPDDRC_MINFO0_P0_TOTAL_LATENCY_QOS0_Pos 0
#define MPDDRC_MINFO0_P0_TOTAL_LATENCY_QOS0_Msk (0xffffu << MPDDRC_MINFO0_P0_TOTAL_LATENCY_QOS0_Pos) /**< \brief (MPDDRC_MINFO0) Total Latency on Port 0 when value of qos is 0 */
#define MPDDRC_MINFO0_P0_TOTAL_LATENCY_QOS1_Pos 16
#define MPDDRC_MINFO0_P0_TOTAL_LATENCY_QOS1_Msk (0xffffu << MPDDRC_MINFO0_P0_TOTAL_LATENCY_QOS1_Pos) /**< \brief (MPDDRC_MINFO0) Total Latency on Port 1 when value of qos is 1 */
#define MPDDRC_MINFO0_P0_TOTAL_LATENCY_QOS2_Pos 0
#define MPDDRC_MINFO0_P0_TOTAL_LATENCY_QOS2_Msk (0xffffu << MPDDRC_MINFO0_P0_TOTAL_LATENCY_QOS2_Pos) /**< \brief (MPDDRC_MINFO0) Total Latency on Port 2 when value of qos is 2 */
#define MPDDRC_MINFO0_P0_TOTAL_LATENCY_QOS3_Pos 16
#define MPDDRC_MINFO0_P0_TOTAL_LATENCY_QOS3_Msk (0xffffu << MPDDRC_MINFO0_P0_TOTAL_LATENCY_QOS3_Pos) /**< \brief (MPDDRC_MINFO0) Total Latency on Port 3 when value of qos is 3 */
/* -------- MPDDRC_MINFO1 : (MPDDRC Offset: 0x88) Monitor Information Port 1 Register -------- */
#define MPDDRC_MINFO1_MAX_PORT1_WAITING_Pos 0
#define MPDDRC_MINFO1_MAX_PORT1_WAITING_Msk (0xffffu << MPDDRC_MINFO1_MAX_PORT1_WAITING_Pos) /**< \brief (MPDDRC_MINFO1) Address High on Port 1 */
#define MPDDRC_MINFO1_BURST_Pos 16
#define MPDDRC_MINFO1_BURST_Msk (0x7u << MPDDRC_MINFO1_BURST_Pos) /**< \brief (MPDDRC_MINFO1) Type of Burst on Port 1 */
#define   MPDDRC_MINFO1_BURST_SINGLE (0x0u << 16) /**< \brief (MPDDRC_MINFO1) Single transfer */
#define   MPDDRC_MINFO1_BURST_INCR (0x1u << 16) /**< \brief (MPDDRC_MINFO1) Incrementing burst of unspecified length */
#define   MPDDRC_MINFO1_BURST_WRAP4 (0x2u << 16) /**< \brief (MPDDRC_MINFO1) 4-beat wrapping burst */
#define   MPDDRC_MINFO1_BURST_INCR4 (0x3u << 16) /**< \brief (MPDDRC_MINFO1) 4-beat incrementing burst */
#define   MPDDRC_MINFO1_BURST_WRAP8 (0x4u << 16) /**< \brief (MPDDRC_MINFO1) 8-beat wrapping burst */
#define   MPDDRC_MINFO1_BURST_INCR8 (0x5u << 16) /**< \brief (MPDDRC_MINFO1) 8-beat incrementing burst */
#define   MPDDRC_MINFO1_BURST_WRAP16 (0x6u << 16) /**< \brief (MPDDRC_MINFO1) 16-beat wrapping burst */
#define   MPDDRC_MINFO1_BURST_INCR16 (0x7u << 16) /**< \brief (MPDDRC_MINFO1) 16-beat incrementing burst */
#define MPDDRC_MINFO1_SIZE_Pos 20
#define MPDDRC_MINFO1_SIZE_Msk (0x7u << MPDDRC_MINFO1_SIZE_Pos) /**< \brief (MPDDRC_MINFO1) Transfer Size on Port 1 */
#define   MPDDRC_MINFO1_SIZE_8BITS (0x0u << 20) /**< \brief (MPDDRC_MINFO1) Byte transfer */
#define   MPDDRC_MINFO1_SIZE_16BITS (0x1u << 20) /**< \brief (MPDDRC_MINFO1) Halfword transfer */
#define   MPDDRC_MINFO1_SIZE_32BITS (0x2u << 20) /**< \brief (MPDDRC_MINFO1) Word transfer */
#define   MPDDRC_MINFO1_SIZE_64BITS (0x3u << 20) /**< \brief (MPDDRC_MINFO1) Dword transfer */
#define MPDDRC_MINFO1_READ_WRITE (0x1u << 24) /**< \brief (MPDDRC_MINFO1) Read or Write Access on Port 1 */
#define MPDDRC_MINFO1_LQOS_Pos 25
#define MPDDRC_MINFO1_LQOS_Msk (0x3u << MPDDRC_MINFO1_LQOS_Pos) /**< \brief (MPDDRC_MINFO1) Value of Quality Of Service on Port 1 */
#define   MPDDRC_MINFO1_LQOS_BACKGROUND (0x0u << 25) /**< \brief (MPDDRC_MINFO1) Background transfers */
#define   MPDDRC_MINFO1_LQOS_BANDWIDTH (0x1u << 25) /**< \brief (MPDDRC_MINFO1) Bandwidth sensitive */
#define   MPDDRC_MINFO1_LQOS_SENSITIVE_LAT (0x2u << 25) /**< \brief (MPDDRC_MINFO1) Latency sensitive */
#define   MPDDRC_MINFO1_LQOS_CRITICAL_LAT (0x3u << 25) /**< \brief (MPDDRC_MINFO1) Latency critical */
#define MPDDRC_MINFO1_P1_NB_TRANSFERS_Pos 0
#define MPDDRC_MINFO1_P1_NB_TRANSFERS_Msk (0xffffffffu << MPDDRC_MINFO1_P1_NB_TRANSFERS_Pos) /**< \brief (MPDDRC_MINFO1) Number of Transfers on Port 1 */
#define MPDDRC_MINFO1_P1_TOTAL_LATENCY_Pos 0
#define MPDDRC_MINFO1_P1_TOTAL_LATENCY_Msk (0xffffffffu << MPDDRC_MINFO1_P1_TOTAL_LATENCY_Pos) /**< \brief (MPDDRC_MINFO1) Total Latency on Port 1 */
#define MPDDRC_MINFO1_P1_TOTAL_LATENCY_QOS0_Pos 0
#define MPDDRC_MINFO1_P1_TOTAL_LATENCY_QOS0_Msk (0xffffu << MPDDRC_MINFO1_P1_TOTAL_LATENCY_QOS0_Pos) /**< \brief (MPDDRC_MINFO1) Total Latency on Port 0 when value of qos is 0 */
#define MPDDRC_MINFO1_P1_TOTAL_LATENCY_QOS1_Pos 16
#define MPDDRC_MINFO1_P1_TOTAL_LATENCY_QOS1_Msk (0xffffu << MPDDRC_MINFO1_P1_TOTAL_LATENCY_QOS1_Pos) /**< \brief (MPDDRC_MINFO1) Total Latency on Port 1 when value of qos is 1 */
#define MPDDRC_MINFO1_P1_TOTAL_LATENCY_QOS2_Pos 0
#define MPDDRC_MINFO1_P1_TOTAL_LATENCY_QOS2_Msk (0xffffu << MPDDRC_MINFO1_P1_TOTAL_LATENCY_QOS2_Pos) /**< \brief (MPDDRC_MINFO1) Total Latency on Port 2 when value of qos is 2 */
#define MPDDRC_MINFO1_P1_TOTAL_LATENCY_QOS3_Pos 16
#define MPDDRC_MINFO1_P1_TOTAL_LATENCY_QOS3_Msk (0xffffu << MPDDRC_MINFO1_P1_TOTAL_LATENCY_QOS3_Pos) /**< \brief (MPDDRC_MINFO1) Total Latency on Port 3 when value of qos is 3 */
/* -------- MPDDRC_MINFO2 : (MPDDRC Offset: 0x8C) Monitor Information Port 2 Register -------- */
#define MPDDRC_MINFO2_MAX_PORT2_WAITING_Pos 0
#define MPDDRC_MINFO2_MAX_PORT2_WAITING_Msk (0xffffu << MPDDRC_MINFO2_MAX_PORT2_WAITING_Pos) /**< \brief (MPDDRC_MINFO2) Address High on Port 2 */
#define MPDDRC_MINFO2_BURST_Pos 16
#define MPDDRC_MINFO2_BURST_Msk (0x7u << MPDDRC_MINFO2_BURST_Pos) /**< \brief (MPDDRC_MINFO2) Type of Burst on Port 2 */
#define   MPDDRC_MINFO2_BURST_SINGLE (0x0u << 16) /**< \brief (MPDDRC_MINFO2) Single transfer */
#define   MPDDRC_MINFO2_BURST_INCR (0x1u << 16) /**< \brief (MPDDRC_MINFO2) Incrementing burst of unspecified length */
#define   MPDDRC_MINFO2_BURST_WRAP4 (0x2u << 16) /**< \brief (MPDDRC_MINFO2) 4-beat wrapping burst */
#define   MPDDRC_MINFO2_BURST_INCR4 (0x3u << 16) /**< \brief (MPDDRC_MINFO2) 4-beat incrementing burst */
#define   MPDDRC_MINFO2_BURST_WRAP8 (0x4u << 16) /**< \brief (MPDDRC_MINFO2) 8-beat wrapping burst */
#define   MPDDRC_MINFO2_BURST_INCR8 (0x5u << 16) /**< \brief (MPDDRC_MINFO2) 8-beat incrementing burst */
#define   MPDDRC_MINFO2_BURST_WRAP16 (0x6u << 16) /**< \brief (MPDDRC_MINFO2) 16-beat wrapping burst */
#define   MPDDRC_MINFO2_BURST_INCR16 (0x7u << 16) /**< \brief (MPDDRC_MINFO2) 16-beat incrementing burst */
#define MPDDRC_MINFO2_SIZE_Pos 20
#define MPDDRC_MINFO2_SIZE_Msk (0x7u << MPDDRC_MINFO2_SIZE_Pos) /**< \brief (MPDDRC_MINFO2) Transfer Size on Port 2 */
#define   MPDDRC_MINFO2_SIZE_8BITS (0x0u << 20) /**< \brief (MPDDRC_MINFO2) Byte transfer */
#define   MPDDRC_MINFO2_SIZE_16BITS (0x1u << 20) /**< \brief (MPDDRC_MINFO2) Halfword transfer */
#define   MPDDRC_MINFO2_SIZE_32BITS (0x2u << 20) /**< \brief (MPDDRC_MINFO2) Word transfer */
#define   MPDDRC_MINFO2_SIZE_64BITS (0x3u << 20) /**< \brief (MPDDRC_MINFO2) Dword transfer */
#define MPDDRC_MINFO2_READ_WRITE (0x1u << 24) /**< \brief (MPDDRC_MINFO2) Read or Write Access on Port 2 */
#define MPDDRC_MINFO2_LQOS_Pos 25
#define MPDDRC_MINFO2_LQOS_Msk (0x3u << MPDDRC_MINFO2_LQOS_Pos) /**< \brief (MPDDRC_MINFO2) Value of Quality Of Service on Port 2 */
#define   MPDDRC_MINFO2_LQOS_BACKGROUND (0x0u << 25) /**< \brief (MPDDRC_MINFO2) Background transfers */
#define   MPDDRC_MINFO2_LQOS_BANDWIDTH (0x1u << 25) /**< \brief (MPDDRC_MINFO2) Bandwidth sensitive */
#define   MPDDRC_MINFO2_LQOS_SENSITIVE_LAT (0x2u << 25) /**< \brief (MPDDRC_MINFO2) Latency sensitive */
#define   MPDDRC_MINFO2_LQOS_CRITICAL_LAT (0x3u << 25) /**< \brief (MPDDRC_MINFO2) Latency critical */
#define MPDDRC_MINFO2_P2_NB_TRANSFERS_Pos 0
#define MPDDRC_MINFO2_P2_NB_TRANSFERS_Msk (0xffffffffu << MPDDRC_MINFO2_P2_NB_TRANSFERS_Pos) /**< \brief (MPDDRC_MINFO2) Number of Transfers on Port 2 */
#define MPDDRC_MINFO2_P2_TOTAL_LATENCY_Pos 0
#define MPDDRC_MINFO2_P2_TOTAL_LATENCY_Msk (0xffffffffu << MPDDRC_MINFO2_P2_TOTAL_LATENCY_Pos) /**< \brief (MPDDRC_MINFO2) Total Latency on Port 2 */
#define MPDDRC_MINFO2_P2_TOTAL_LATENCY_QOS0_Pos 0
#define MPDDRC_MINFO2_P2_TOTAL_LATENCY_QOS0_Msk (0xffffu << MPDDRC_MINFO2_P2_TOTAL_LATENCY_QOS0_Pos) /**< \brief (MPDDRC_MINFO2) Total Latency on Port 0 when value of qos is 0 */
#define MPDDRC_MINFO2_P2_TOTAL_LATENCY_QOS1_Pos 16
#define MPDDRC_MINFO2_P2_TOTAL_LATENCY_QOS1_Msk (0xffffu << MPDDRC_MINFO2_P2_TOTAL_LATENCY_QOS1_Pos) /**< \brief (MPDDRC_MINFO2) Total Latency on Port 1 when value of qos is 1 */
#define MPDDRC_MINFO2_P2_TOTAL_LATENCY_QOS2_Pos 0
#define MPDDRC_MINFO2_P2_TOTAL_LATENCY_QOS2_Msk (0xffffu << MPDDRC_MINFO2_P2_TOTAL_LATENCY_QOS2_Pos) /**< \brief (MPDDRC_MINFO2) Total Latency on Port 2 when value of qos is 2 */
#define MPDDRC_MINFO2_P2_TOTAL_LATENCY_QOS3_Pos 16
#define MPDDRC_MINFO2_P2_TOTAL_LATENCY_QOS3_Msk (0xffffu << MPDDRC_MINFO2_P2_TOTAL_LATENCY_QOS3_Pos) /**< \brief (MPDDRC_MINFO2) Total Latency on Port 3 when value of qos is 3 */
/* -------- MPDDRC_MINFO3 : (MPDDRC Offset: 0x90) Monitor Information Port 3 Register -------- */
#define MPDDRC_MINFO3_MAX_PORT3_WAITING_Pos 0
#define MPDDRC_MINFO3_MAX_PORT3_WAITING_Msk (0xffffu << MPDDRC_MINFO3_MAX_PORT3_WAITING_Pos) /**< \brief (MPDDRC_MINFO3) Address High on Port 3 */
#define MPDDRC_MINFO3_BURST_Pos 16
#define MPDDRC_MINFO3_BURST_Msk (0x7u << MPDDRC_MINFO3_BURST_Pos) /**< \brief (MPDDRC_MINFO3) Type of Burst on Port 3 */
#define   MPDDRC_MINFO3_BURST_SINGLE (0x0u << 16) /**< \brief (MPDDRC_MINFO3) Single transfer */
#define   MPDDRC_MINFO3_BURST_INCR (0x1u << 16) /**< \brief (MPDDRC_MINFO3) Incrementing burst of unspecified length */
#define   MPDDRC_MINFO3_BURST_WRAP4 (0x2u << 16) /**< \brief (MPDDRC_MINFO3) 4-beat wrapping burst */
#define   MPDDRC_MINFO3_BURST_INCR4 (0x3u << 16) /**< \brief (MPDDRC_MINFO3) 4-beat incrementing burst */
#define   MPDDRC_MINFO3_BURST_WRAP8 (0x4u << 16) /**< \brief (MPDDRC_MINFO3) 8-beat wrapping burst */
#define   MPDDRC_MINFO3_BURST_INCR8 (0x5u << 16) /**< \brief (MPDDRC_MINFO3) 8-beat incrementing burst */
#define   MPDDRC_MINFO3_BURST_WRAP16 (0x6u << 16) /**< \brief (MPDDRC_MINFO3) 16-beat wrapping burst */
#define   MPDDRC_MINFO3_BURST_INCR16 (0x7u << 16) /**< \brief (MPDDRC_MINFO3) 16-beat incrementing burst */
#define MPDDRC_MINFO3_SIZE_Pos 20
#define MPDDRC_MINFO3_SIZE_Msk (0x7u << MPDDRC_MINFO3_SIZE_Pos) /**< \brief (MPDDRC_MINFO3) Transfer Size on Port 3 */
#define   MPDDRC_MINFO3_SIZE_8BITS (0x0u << 20) /**< \brief (MPDDRC_MINFO3) Byte transfer */
#define   MPDDRC_MINFO3_SIZE_16BITS (0x1u << 20) /**< \brief (MPDDRC_MINFO3) Halfword transfer */
#define   MPDDRC_MINFO3_SIZE_32BITS (0x2u << 20) /**< \brief (MPDDRC_MINFO3) Word transfer */
#define   MPDDRC_MINFO3_SIZE_64BITS (0x3u << 20) /**< \brief (MPDDRC_MINFO3) Dword transfer */
#define MPDDRC_MINFO3_READ_WRITE (0x1u << 24) /**< \brief (MPDDRC_MINFO3) Read or Write Access on Port 3 */
#define MPDDRC_MINFO3_LQOS_Pos 25
#define MPDDRC_MINFO3_LQOS_Msk (0x3u << MPDDRC_MINFO3_LQOS_Pos) /**< \brief (MPDDRC_MINFO3) Value of Quality Of Service on Port 3 */
#define   MPDDRC_MINFO3_LQOS_BACKGROUND (0x0u << 25) /**< \brief (MPDDRC_MINFO3) Background transfers */
#define   MPDDRC_MINFO3_LQOS_BANDWIDTH (0x1u << 25) /**< \brief (MPDDRC_MINFO3) Bandwidth sensitive */
#define   MPDDRC_MINFO3_LQOS_SENSITIVE_LAT (0x2u << 25) /**< \brief (MPDDRC_MINFO3) Latency sensitive */
#define   MPDDRC_MINFO3_LQOS_CRITICAL_LAT (0x3u << 25) /**< \brief (MPDDRC_MINFO3) Latency critical */
#define MPDDRC_MINFO3_P3_NB_TRANSFERS_Pos 0
#define MPDDRC_MINFO3_P3_NB_TRANSFERS_Msk (0xffffffffu << MPDDRC_MINFO3_P3_NB_TRANSFERS_Pos) /**< \brief (MPDDRC_MINFO3) Number of Transfers on Port 3 */
#define MPDDRC_MINFO3_P3_TOTAL_LATENCY_Pos 0
#define MPDDRC_MINFO3_P3_TOTAL_LATENCY_Msk (0xffffffffu << MPDDRC_MINFO3_P3_TOTAL_LATENCY_Pos) /**< \brief (MPDDRC_MINFO3) Total Latency on Port 3 */
#define MPDDRC_MINFO3_P3_TOTAL_LATENCY_QOS0_Pos 0
#define MPDDRC_MINFO3_P3_TOTAL_LATENCY_QOS0_Msk (0xffffu << MPDDRC_MINFO3_P3_TOTAL_LATENCY_QOS0_Pos) /**< \brief (MPDDRC_MINFO3) Total Latency on Port 0 when value of qos is 0 */
#define MPDDRC_MINFO3_P3_TOTAL_LATENCY_QOS1_Pos 16
#define MPDDRC_MINFO3_P3_TOTAL_LATENCY_QOS1_Msk (0xffffu << MPDDRC_MINFO3_P3_TOTAL_LATENCY_QOS1_Pos) /**< \brief (MPDDRC_MINFO3) Total Latency on Port 1 when value of qos is 1 */
#define MPDDRC_MINFO3_P3_TOTAL_LATENCY_QOS2_Pos 0
#define MPDDRC_MINFO3_P3_TOTAL_LATENCY_QOS2_Msk (0xffffu << MPDDRC_MINFO3_P3_TOTAL_LATENCY_QOS2_Pos) /**< \brief (MPDDRC_MINFO3) Total Latency on Port 2 when value of qos is 2 */
#define MPDDRC_MINFO3_P3_TOTAL_LATENCY_QOS3_Pos 16
#define MPDDRC_MINFO3_P3_TOTAL_LATENCY_QOS3_Msk (0xffffu << MPDDRC_MINFO3_P3_TOTAL_LATENCY_QOS3_Pos) /**< \brief (MPDDRC_MINFO3) Total Latency on Port 3 when value of qos is 3 */
/* -------- MPDDRC_IER : (MPDDRC Offset: 0xC0) Interrupt Enable Register -------- */
#define MPDDRC_IER_SEC (0x1u << 0) /**< \brief (MPDDRC_IER) Security and /or Safety Interrupt Enable */
#define MPDDRC_IER_RD_ERR (0x1u << 1) /**< \brief (MPDDRC_IER) Read Error Interrupt Enable */
/* -------- MPDDRC_IDR : (MPDDRC Offset: 0xC4) Interrupt Disable Register -------- */
#define MPDDRC_IDR_SEC (0x1u << 0) /**< \brief (MPDDRC_IDR) Security and /or Safety Interrupt Disable */
#define MPDDRC_IDR_RD_ERR (0x1u << 1) /**< \brief (MPDDRC_IDR) Read Error Interrupt Disable */
/* -------- MPDDRC_IMR : (MPDDRC Offset: 0xC8) Interrupt Mask Register -------- */
#define MPDDRC_IMR_SEC (0x1u << 0) /**< \brief (MPDDRC_IMR) Security and /or Safety Interrupt Mask */
#define MPDDRC_IMR_RD_ERR (0x1u << 1) /**< \brief (MPDDRC_IMR) Read Error Interrupt Mask */
/* -------- MPDDRC_ISR : (MPDDRC Offset: 0xCC) Interrupt Status Register -------- */
#define MPDDRC_ISR_SEC (0x1u << 0) /**< \brief (MPDDRC_ISR) Security and /or Safety Event */
#define MPDDRC_ISR_RD_ERR (0x1u << 1) /**< \brief (MPDDRC_ISR) Read Error */
/* -------- MPDDRC_SAFETY : (MPDDRC Offset: 0xD0) Safety Register -------- */
#define MPDDRC_SAFETY_ADDRESS_Pos 0
#define MPDDRC_SAFETY_ADDRESS_Msk (0xfffffffu << MPDDRC_SAFETY_ADDRESS_Pos) /**< \brief (MPDDRC_SAFETY) Memory Device Address */
#define MPDDRC_SAFETY_ADDRESS(value) ((MPDDRC_SAFETY_ADDRESS_Msk & ((value) << MPDDRC_SAFETY_ADDRESS_Pos)))
#define MPDDRC_SAFETY_EN (0x1u << 28) /**< \brief (MPDDRC_SAFETY) Enable Periodic Check of Memory Device */
/* -------- MPDDRC_WPMR : (MPDDRC Offset: 0xE4) Write Protection Mode Register -------- */
#define MPDDRC_WPMR_WPEN (0x1u << 0) /**< \brief (MPDDRC_WPMR) Write Protection Enable */
#define MPDDRC_WPMR_WPITEN (0x1u << 1) /**< \brief (MPDDRC_WPMR) Write Protection Interruption Enable */
#define MPDDRC_WPMR_FIRSTE (0x1u << 4) /**< \brief (MPDDRC_WPMR) First Error Report Enable */
#define MPDDRC_WPMR_WPKEY_Pos 8
#define MPDDRC_WPMR_WPKEY_Msk (0xffffffu << MPDDRC_WPMR_WPKEY_Pos) /**< \brief (MPDDRC_WPMR) Write Protection Key */
#define MPDDRC_WPMR_WPKEY(value) ((MPDDRC_WPMR_WPKEY_Msk & ((value) << MPDDRC_WPMR_WPKEY_Pos)))
#define   MPDDRC_WPMR_WPKEY_PASSWD (0x444452u << 8) /**< \brief (MPDDRC_WPMR) Writing any other value in this field aborts the write operation of the WPEN and WPITEN bits. Always reads as 0. */
/* -------- MPDDRC_WPSR : (MPDDRC Offset: 0xE8) Write Protection Status Register -------- */
#define MPDDRC_WPSR_WPVS (0x1u << 0) /**< \brief (MPDDRC_WPSR) Write Protection Enable */
#define MPDDRC_WPSR_CGD (0x1u << 1) /**< \brief (MPDDRC_WPSR) Clock Glitch Detected (cleared on read) */
#define MPDDRC_WPSR_SEQE (0x1u << 2) /**< \brief (MPDDRC_WPSR) Internal Sequencer Error (cleared on read) */
#define MPDDRC_WPSR_SWE (0x1u << 3) /**< \brief (MPDDRC_WPSR) Software Control Error (cleared on read) */
#define MPDDRC_WPSR_WPVSRC_Pos 8
#define MPDDRC_WPSR_WPVSRC_Msk (0xffffu << MPDDRC_WPSR_WPVSRC_Pos) /**< \brief (MPDDRC_WPSR) Write Protection Violation Source */
#define MPDDRC_WPSR_SWETYP_Pos 24
#define MPDDRC_WPSR_SWETYP_Msk (0x3u << MPDDRC_WPSR_SWETYP_Pos) /**< \brief (MPDDRC_WPSR) Software Error Type (cleared on read) */
#define   MPDDRC_WPSR_SWETYP_READ_WO (0x0u << 24) /**< \brief (MPDDRC_WPSR) A write-only register has been read (warning). */
#define   MPDDRC_WPSR_SWETYP_WRITE_RO (0x1u << 24) /**< \brief (MPDDRC_WPSR) MPDDRC is enabled and a write access has been performed on a read-only register (warning). */
#define   MPDDRC_WPSR_SWETYP_UNDEF_RW (0x2u << 24) /**< \brief (MPDDRC_WPSR) Access to an undefined address (warning). */
#define   MPDDRC_WPSR_SWETYP_W_AFTER_INIT (0x3u << 24) /**< \brief (MPDDRC_WPSR) Abnormal use of MPDDRC user interface when memory device is already configured and initialized, i.e., if MPDDRC_RTR.COUNT > 0 (error). */
#define MPDDRC_WPSR_ECLASS (0x1u << 31) /**< \brief (MPDDRC_WPSR) Software Error Class (cleared on read) */
#define   MPDDRC_WPSR_ECLASS_WARNING (0x0u << 31) /**< \brief (MPDDRC_WPSR) An abnormal access that does not affect system functionality is performed. */
#define   MPDDRC_WPSR_ECLASS_ERROR (0x1u << 31) /**< \brief (MPDDRC_WPSR) An access is performed into some registers after memory device initialization sequence. */

/*@}*/


#endif /* _SAM9X_MPDDRC_COMPONENT_ */
