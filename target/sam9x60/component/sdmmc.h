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

#ifndef _SAM9X_SDMMC_COMPONENT_
#define _SAM9X_SDMMC_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Secure Digital MultiMedia Card Controller */
/* ============================================================================= */
/** \addtogroup SAM9X_SDMMC Secure Digital MultiMedia Card Controller */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Sdmmc hardware registers */
typedef struct {
  __IO uint32_t SDMMC_SSAR;     /**< \brief (Sdmmc Offset: 0x0) SDMA System Address / Argument 2 Register */
  __IO uint16_t SDMMC_BSR;      /**< \brief (Sdmmc Offset: 0x4) Block Size Register */
  __IO uint16_t SDMMC_BCR;      /**< \brief (Sdmmc Offset: 0x6) Block Count Register */
  __IO uint32_t SDMMC_ARG1R;    /**< \brief (Sdmmc Offset: 0x8) Argument 1 Register */
  __IO uint16_t SDMMC_TMR;      /**< \brief (Sdmmc Offset: 0xC) Transfer Mode Register */
  __IO uint16_t SDMMC_CR;       /**< \brief (Sdmmc Offset: 0xE) Command Register */
  __I  uint32_t SDMMC_RR[4];    /**< \brief (Sdmmc Offset: 0x10) Response Register */
  __IO uint32_t SDMMC_BDPR;     /**< \brief (Sdmmc Offset: 0x20) Buffer Data Port Register */
  __I  uint32_t SDMMC_PSR;      /**< \brief (Sdmmc Offset: 0x24) Present State Register */
  __IO uint8_t  SDMMC_HC1R;     /**< \brief (Sdmmc Offset: 0x28) Host Control 1 Register */
  __IO uint8_t  SDMMC_PCR;      /**< \brief (Sdmmc Offset: 0x29) Power Control Register */
  __IO uint8_t  SDMMC_BGCR;     /**< \brief (Sdmmc Offset: 0x2A) Block Gap Control Register */
  __IO uint8_t  SDMMC_WCR;      /**< \brief (Sdmmc Offset: 0x2B) Wakeup Control Register */
  __IO uint16_t SDMMC_CCR;      /**< \brief (Sdmmc Offset: 0x2C) Clock Control Register */
  __IO uint8_t  SDMMC_TCR;      /**< \brief (Sdmmc Offset: 0x2E) Timeout Control Register */
  __IO uint8_t  SDMMC_SRR;      /**< \brief (Sdmmc Offset: 0x2F) Software Reset Register */
  __IO uint16_t SDMMC_NISTR;    /**< \brief (Sdmmc Offset: 0x30) Normal Interrupt Status Register */
  __IO uint16_t SDMMC_EISTR;    /**< \brief (Sdmmc Offset: 0x32) Error Interrupt Status Register */
  __IO uint16_t SDMMC_NISTER;   /**< \brief (Sdmmc Offset: 0x34) Normal Interrupt Status Enable Register */
  __IO uint16_t SDMMC_EISTER;   /**< \brief (Sdmmc Offset: 0x36) Error Interrupt Status Enable Register */
  __IO uint16_t SDMMC_NISIER;   /**< \brief (Sdmmc Offset: 0x38) Normal Interrupt Signal Enable Register */
  __IO uint16_t SDMMC_EISIER;   /**< \brief (Sdmmc Offset: 0x3A) Error Interrupt Signal Enable Register */
  __I  uint16_t SDMMC_ACESR;    /**< \brief (Sdmmc Offset: 0x3C) Auto CMD Error Status Register */
  __IO uint16_t SDMMC_HC2R;     /**< \brief (Sdmmc Offset: 0x3E) Host Control 2 Register */
  __IO uint32_t SDMMC_CA0R;     /**< \brief (Sdmmc Offset: 0x40) Capabilities 0 Register */
  __IO uint32_t SDMMC_CA1R;     /**< \brief (Sdmmc Offset: 0x44) Capabilities 1 Register */
  __IO uint32_t SDMMC_MCCAR;    /**< \brief (Sdmmc Offset: 0x48) Maximum Current Capabilities Register */
  __I  uint32_t Reserved1[1];
  __O  uint16_t SDMMC_FERACES;  /**< \brief (Sdmmc Offset: 0x50) Force Event Register for Auto CMD Error Status */
  __O  uint16_t SDMMC_FEREIS;   /**< \brief (Sdmmc Offset: 0x52) Force Event Register for Error Interrupt Status */
  __I  uint8_t  SDMMC_AESR;     /**< \brief (Sdmmc Offset: 0x54) ADMA Error Status Register */
  __I  uint8_t  Reserved2[3];
  __IO uint32_t SDMMC_ASA0R;    /**< \brief (Sdmmc Offset: 0x58) ADMA System Address Register 0 */
  __I  uint32_t Reserved3[1];
  __IO uint16_t SDMMC_PVR[3];   /**< \brief (Sdmmc Offset: 0x60) Preset Value Register 0 (for initialization) */
  __I  uint8_t  Reserved4[150];
  __I  uint16_t SDMMC_SISR;     /**< \brief (Sdmmc Offset: 0xFC) Slot Interrupt Status Register */
  __I  uint16_t SDMMC_HCVR;     /**< \brief (Sdmmc Offset: 0xFE) Host Controller Version Register */
  __I  uint32_t Reserved5[64];
  __I  uint32_t SDMMC_APSR;     /**< \brief (Sdmmc Offset: 0x200) Additional Present State Register */
  __IO uint8_t  SDMMC_MC1R;     /**< \brief (Sdmmc Offset: 0x204) e.MMC Control 1 Register */
  __O  uint8_t  SDMMC_MC2R;     /**< \brief (Sdmmc Offset: 0x205) e.MMC Control 2 Register */
  __I  uint8_t  Reserved6[2];
  __IO uint32_t SDMMC_ACR;      /**< \brief (Sdmmc Offset: 0x208) AHB Control Register */
  __IO uint32_t SDMMC_CC2R;     /**< \brief (Sdmmc Offset: 0x20C) Clock Control 2 Register */
  __I  uint32_t Reserved7[5];
  __I  uint32_t SDMMC_TUNSR;    /**< \brief (Sdmmc Offset: 0x224) Tuning Status Register */
  __I  uint32_t Reserved8[2];
  __IO uint32_t SDMMC_CACR;     /**< \brief (Sdmmc Offset: 0x230) Capabilities Control Register */
  __IO uint32_t SDMMC_DBGR;     /**< \brief (Sdmmc Offset: 0x234) Debug Register */
} Sdmmc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- SDMMC_SSAR : (SDMMC Offset: 0x0) SDMA System Address / Argument 2 Register -------- */
#define SDMMC_SSAR_ADDR_Pos 0
#define SDMMC_SSAR_ADDR_Msk (0xffffffffu << SDMMC_SSAR_ADDR_Pos) /**< \brief (SDMMC_SSAR) SDMA System Address */
#define SDMMC_SSAR_ADDR(value) ((SDMMC_SSAR_ADDR_Msk & ((value) << SDMMC_SSAR_ADDR_Pos)))
#define SDMMC_SSAR_ARG2_Pos 0
#define SDMMC_SSAR_ARG2_Msk (0xffffffffu << SDMMC_SSAR_ARG2_Pos) /**< \brief (SDMMC_SSAR) Argument 2 */
#define SDMMC_SSAR_ARG2(value) ((SDMMC_SSAR_ARG2_Msk & ((value) << SDMMC_SSAR_ARG2_Pos)))
/* -------- SDMMC_BSR : (SDMMC Offset: 0x4) Block Size Register -------- */
#define SDMMC_BSR_BLKSIZE_Pos 0
#define SDMMC_BSR_BLKSIZE_Msk (0x3ffu << SDMMC_BSR_BLKSIZE_Pos) /**< \brief (SDMMC_BSR) Transfer Block Size */
#define SDMMC_BSR_BLKSIZE(value) ((SDMMC_BSR_BLKSIZE_Msk & ((value) << SDMMC_BSR_BLKSIZE_Pos)))
#define SDMMC_BSR_BOUNDARY_Pos 12
#define SDMMC_BSR_BOUNDARY_Msk (0x7u << SDMMC_BSR_BOUNDARY_Pos) /**< \brief (SDMMC_BSR) SDMA Buffer Boundary */
#define SDMMC_BSR_BOUNDARY(value) ((SDMMC_BSR_BOUNDARY_Msk & ((value) << SDMMC_BSR_BOUNDARY_Pos)))
#define   SDMMC_BSR_BOUNDARY_4K (0x0u << 12) /**< \brief (SDMMC_BSR) 4-Kbyte boundary */
#define   SDMMC_BSR_BOUNDARY_8K (0x1u << 12) /**< \brief (SDMMC_BSR) 8-Kbyte boundary */
#define   SDMMC_BSR_BOUNDARY_16K (0x2u << 12) /**< \brief (SDMMC_BSR) 16-Kbyte boundary */
#define   SDMMC_BSR_BOUNDARY_32K (0x3u << 12) /**< \brief (SDMMC_BSR) 32-Kbyte boundary */
#define   SDMMC_BSR_BOUNDARY_64K (0x4u << 12) /**< \brief (SDMMC_BSR) 64-Kbyte boundary */
#define   SDMMC_BSR_BOUNDARY_128K (0x5u << 12) /**< \brief (SDMMC_BSR) 128-Kbyte boundary */
#define   SDMMC_BSR_BOUNDARY_256k (0x6u << 12) /**< \brief (SDMMC_BSR) 256-Kbyte boundary */
#define   SDMMC_BSR_BOUNDARY_512K (0x7u << 12) /**< \brief (SDMMC_BSR) 512-Kbyte boundary */
/* -------- SDMMC_BCR : (SDMMC Offset: 0x6) Block Count Register -------- */
#define SDMMC_BCR_BLKCNT_Pos 0
#define SDMMC_BCR_BLKCNT_Msk (0xffffu << SDMMC_BCR_BLKCNT_Pos) /**< \brief (SDMMC_BCR) Block Count for Current Transfer */
#define SDMMC_BCR_BLKCNT(value) ((SDMMC_BCR_BLKCNT_Msk & ((value) << SDMMC_BCR_BLKCNT_Pos)))
/* -------- SDMMC_ARG1R : (SDMMC Offset: 0x8) Argument 1 Register -------- */
#define SDMMC_ARG1R_ARG1_Pos 0
#define SDMMC_ARG1R_ARG1_Msk (0xffffffffu << SDMMC_ARG1R_ARG1_Pos) /**< \brief (SDMMC_ARG1R) Argument 1 */
#define SDMMC_ARG1R_ARG1(value) ((SDMMC_ARG1R_ARG1_Msk & ((value) << SDMMC_ARG1R_ARG1_Pos)))
/* -------- SDMMC_TMR : (SDMMC Offset: 0xC) Transfer Mode Register -------- */
#define SDMMC_TMR_DMAEN (0x1u << 0) /**< \brief (SDMMC_TMR) DMA Enable */
#define   SDMMC_TMR_DMAEN_DISABLED (0x0u << 0) /**< \brief (SDMMC_TMR) DMA functionality is disabled. */
#define   SDMMC_TMR_DMAEN_ENABLED (0x1u << 0) /**< \brief (SDMMC_TMR) DMA functionality is enabled. */
#define SDMMC_TMR_BCEN (0x1u << 1) /**< \brief (SDMMC_TMR) Block Count Enable */
#define   SDMMC_TMR_BCEN_DISABLED (0x0u << 1) /**< \brief (SDMMC_TMR) Block count is disabled. */
#define   SDMMC_TMR_BCEN_ENABLED (0x1u << 1) /**< \brief (SDMMC_TMR) Block count is enabled. */
#define SDMMC_TMR_ACMDEN_Pos 2
#define SDMMC_TMR_ACMDEN_Msk (0x3u << SDMMC_TMR_ACMDEN_Pos) /**< \brief (SDMMC_TMR) Auto Command Enable */
#define SDMMC_TMR_ACMDEN(value) ((SDMMC_TMR_ACMDEN_Msk & ((value) << SDMMC_TMR_ACMDEN_Pos)))
#define   SDMMC_TMR_ACMDEN_DIS (0x0u << 2) /**< \brief (SDMMC_TMR) Auto Command Disabled */
#define   SDMMC_TMR_ACMDEN_ACMD12 (0x1u << 2) /**< \brief (SDMMC_TMR) Auto CMD12 Enabled */
#define   SDMMC_TMR_ACMDEN_ACMD23 (0x2u << 2) /**< \brief (SDMMC_TMR) Auto CMD23 Enabled */
#define SDMMC_TMR_DTDSEL (0x1u << 4) /**< \brief (SDMMC_TMR) Data Transfer Direction Selection */
#define   SDMMC_TMR_DTDSEL_WR (0x0u << 4) /**< \brief (SDMMC_TMR) Writes data from the SDMMC to the device. */
#define   SDMMC_TMR_DTDSEL_RD (0x1u << 4) /**< \brief (SDMMC_TMR) Reads data from the device to the SDMMC. */
#define SDMMC_TMR_MSBSEL (0x1u << 5) /**< \brief (SDMMC_TMR) Multi/Single Block Selection */
/* -------- SDMMC_CR : (SDMMC Offset: 0xE) Command Register -------- */
#define SDMMC_CR_RESPTYP_Pos 0
#define SDMMC_CR_RESPTYP_Msk (0x3u << SDMMC_CR_RESPTYP_Pos) /**< \brief (SDMMC_CR) Response Type */
#define SDMMC_CR_RESPTYP(value) ((SDMMC_CR_RESPTYP_Msk & ((value) << SDMMC_CR_RESPTYP_Pos)))
#define   SDMMC_CR_RESPTYP_NORESP (0x0u << 0) /**< \brief (SDMMC_CR) No Response */
#define   SDMMC_CR_RESPTYP_RL136 (0x1u << 0) /**< \brief (SDMMC_CR) Response Length 136 */
#define   SDMMC_CR_RESPTYP_RL48 (0x2u << 0) /**< \brief (SDMMC_CR) Response Length 48 */
#define   SDMMC_CR_RESPTYP_RL48BUSY (0x3u << 0) /**< \brief (SDMMC_CR) Response Length 48 with Busy */
#define SDMMC_CR_CMDCCEN (0x1u << 3) /**< \brief (SDMMC_CR) Command CRC Check Enable */
#define   SDMMC_CR_CMDCCEN_DISABLED (0x0u << 3) /**< \brief (SDMMC_CR) The Command CRC Check is disabled. */
#define   SDMMC_CR_CMDCCEN_ENABLED (0x1u << 3) /**< \brief (SDMMC_CR) The Command CRC Check is enabled. */
#define SDMMC_CR_CMDICEN (0x1u << 4) /**< \brief (SDMMC_CR) Command Index Check Enable */
#define   SDMMC_CR_CMDICEN_DISABLED (0x0u << 4) /**< \brief (SDMMC_CR) The Command Index Check is disabled. */
#define   SDMMC_CR_CMDICEN_ENABLED (0x1u << 4) /**< \brief (SDMMC_CR) The Command Index Check is enabled. */
#define SDMMC_CR_DPSEL (0x1u << 5) /**< \brief (SDMMC_CR) Data Present Select */
#define SDMMC_CR_CMDTYP_Pos 6
#define SDMMC_CR_CMDTYP_Msk (0x3u << SDMMC_CR_CMDTYP_Pos) /**< \brief (SDMMC_CR) Command Type */
#define SDMMC_CR_CMDTYP(value) ((SDMMC_CR_CMDTYP_Msk & ((value) << SDMMC_CR_CMDTYP_Pos)))
#define   SDMMC_CR_CMDTYP_NORMAL (0x0u << 6) /**< \brief (SDMMC_CR) Other commands */
#define   SDMMC_CR_CMDTYP_SUSPEND (0x1u << 6) /**< \brief (SDMMC_CR) CMD52 to write "Bus Suspend" in the Card Common Control Registers (CCCR) (for SDIO only) */
#define   SDMMC_CR_CMDTYP_RESUME (0x2u << 6) /**< \brief (SDMMC_CR) CMD52 to write "Function Select" in the Card Common Control Registers (CCCR) (for SDIO only) */
#define   SDMMC_CR_CMDTYP_ABORT (0x3u << 6) /**< \brief (SDMMC_CR) CMD12, CMD52 to write "I/O Abort" in the Card Common Control Registers (CCCR) (for SDIO only) */
#define SDMMC_CR_CMDIDX_Pos 8
#define SDMMC_CR_CMDIDX_Msk (0x3fu << SDMMC_CR_CMDIDX_Pos) /**< \brief (SDMMC_CR) Command Index */
#define SDMMC_CR_CMDIDX(value) ((SDMMC_CR_CMDIDX_Msk & ((value) << SDMMC_CR_CMDIDX_Pos)))
/* -------- SDMMC_RR[4] : (SDMMC Offset: 0x10) Response Register -------- */
#define SDMMC_RR_CMDRESP_Pos 0
#define SDMMC_RR_CMDRESP_Msk (0xffffffffu << SDMMC_RR_CMDRESP_Pos) /**< \brief (SDMMC_RR[4]) Command Response */
/* -------- SDMMC_BDPR : (SDMMC Offset: 0x20) Buffer Data Port Register -------- */
#define SDMMC_BDPR_BUFDATA_Pos 0
#define SDMMC_BDPR_BUFDATA_Msk (0xffffffffu << SDMMC_BDPR_BUFDATA_Pos) /**< \brief (SDMMC_BDPR) Buffer Data */
#define SDMMC_BDPR_BUFDATA(value) ((SDMMC_BDPR_BUFDATA_Msk & ((value) << SDMMC_BDPR_BUFDATA_Pos)))
/* -------- SDMMC_PSR : (SDMMC Offset: 0x24) Present State Register -------- */
#define SDMMC_PSR_CMDINHC (0x1u << 0) /**< \brief (SDMMC_PSR) Command Inhibit (CMD) */
#define SDMMC_PSR_CMDINHD (0x1u << 1) /**< \brief (SDMMC_PSR) Command Inhibit (DAT) */
#define SDMMC_PSR_DLACT (0x1u << 2) /**< \brief (SDMMC_PSR) DAT Line Active */
#define SDMMC_PSR_WTACT (0x1u << 8) /**< \brief (SDMMC_PSR) Write Transfer Active */
#define SDMMC_PSR_RTACT (0x1u << 9) /**< \brief (SDMMC_PSR) Read Transfer Active */
#define SDMMC_PSR_BUFWREN (0x1u << 10) /**< \brief (SDMMC_PSR) Buffer Write Enable */
#define SDMMC_PSR_BUFRDEN (0x1u << 11) /**< \brief (SDMMC_PSR) Buffer Read Enable */
#define SDMMC_PSR_DATLL_Pos 20
#define SDMMC_PSR_DATLL_Msk (0xfu << SDMMC_PSR_DATLL_Pos) /**< \brief (SDMMC_PSR) DAT[3:0] Line Level */
#define SDMMC_PSR_CMDLL (0x1u << 24) /**< \brief (SDMMC_PSR) CMD Line Level */
/* -------- SDMMC_HC1R : (SDMMC Offset: 0x28) Host Control 1 Register -------- */
#define SDMMC_HC1R_LEDCTRL (0x1u << 0) /**< \brief (SDMMC_HC1R) LED Control */
#define   SDMMC_HC1R_LEDCTRL_OFF (0x0u << 0) /**< \brief (SDMMC_HC1R) LED off. */
#define   SDMMC_HC1R_LEDCTRL_ON (0x1u << 0) /**< \brief (SDMMC_HC1R) LED on. */
#define SDMMC_HC1R_DW (0x1u << 1) /**< \brief (SDMMC_HC1R) Data Width */
#define   SDMMC_HC1R_DW_1_BIT (0x0u << 1) /**< \brief (SDMMC_HC1R) 1-bit mode. */
#define   SDMMC_HC1R_DW_4_BIT (0x1u << 1) /**< \brief (SDMMC_HC1R) 4-bit mode. */
#define SDMMC_HC1R_HSEN (0x1u << 2) /**< \brief (SDMMC_HC1R) High Speed Enable */
#define SDMMC_HC1R_DMASEL_Pos 3
#define SDMMC_HC1R_DMASEL_Msk (0x3u << SDMMC_HC1R_DMASEL_Pos) /**< \brief (SDMMC_HC1R) DMA Select */
#define SDMMC_HC1R_DMASEL(value) ((SDMMC_HC1R_DMASEL_Msk & ((value) << SDMMC_HC1R_DMASEL_Pos)))
#define   SDMMC_HC1R_DMASEL_SDMA (0x0u << 3) /**< \brief (SDMMC_HC1R) SDMA is selected */
#define   SDMMC_HC1R_DMASEL_ADMA32 (0x2u << 3) /**< \brief (SDMMC_HC1R) 32-bit Address ADMA2 is selected */
#define SDMMC_HC1R_EXTDW (0x1u << 5) /**< \brief (SDMMC_HC1R) Extended Data Width */
/* -------- SDMMC_PCR : (SDMMC Offset: 0x29) Power Control Register -------- */
#define SDMMC_PCR_SDBPWR (0x1u << 0) /**< \brief (SDMMC_PCR) SD Bus Power */
/* -------- SDMMC_BGCR : (SDMMC Offset: 0x2A) Block Gap Control Register -------- */
#define SDMMC_BGCR_STPBGR (0x1u << 0) /**< \brief (SDMMC_BGCR) Stop At Block Gap Request */
#define SDMMC_BGCR_CONTR (0x1u << 1) /**< \brief (SDMMC_BGCR) Continue Request */
#define SDMMC_BGCR_RWCTRL (0x1u << 2) /**< \brief (SDMMC_BGCR) Read Wait Control */
#define SDMMC_BGCR_INTBG (0x1u << 3) /**< \brief (SDMMC_BGCR) Interrupt at Block Gap */
#define   SDMMC_BGCR_INTBG_DISABLED (0x0u << 3) /**< \brief (SDMMC_BGCR) Interrupt detection disabled. */
#define   SDMMC_BGCR_INTBG_ENABLED (0x1u << 3) /**< \brief (SDMMC_BGCR) Interrupt detection enabled. */
/* -------- SDMMC_WCR : (SDMMC Offset: 0x2B) Wakeup Control Register -------- */
#define SDMMC_WCR_WKENCINT (0x1u << 0) /**< \brief (SDMMC_WCR) Wakeup Event Enable on Card Interrupt */
#define   SDMMC_WCR_WKENCINT_DISABLED (0x0u << 0) /**< \brief (SDMMC_WCR) Wakeup Event disabled. */
#define   SDMMC_WCR_WKENCINT_ENABLED (0x1u << 0) /**< \brief (SDMMC_WCR) Wakeup Event enabled. */
/* -------- SDMMC_CCR : (SDMMC Offset: 0x2C) Clock Control Register -------- */
#define SDMMC_CCR_INTCLKEN (0x1u << 0) /**< \brief (SDMMC_CCR) Internal Clock Enable */
#define SDMMC_CCR_INTCLKS (0x1u << 1) /**< \brief (SDMMC_CCR) Internal Clock Stable */
#define SDMMC_CCR_SDCLKEN (0x1u << 2) /**< \brief (SDMMC_CCR) SD Clock Enable */
#define SDMMC_CCR_CLKGSEL (0x1u << 5) /**< \brief (SDMMC_CCR) Clock Generator Select */
#define SDMMC_CCR_USDCLKFSEL_Pos 6
#define SDMMC_CCR_USDCLKFSEL_Msk (0x3u << SDMMC_CCR_USDCLKFSEL_Pos) /**< \brief (SDMMC_CCR) Upper Bits of SDCLK Frequency Select */
#define SDMMC_CCR_USDCLKFSEL(value) ((SDMMC_CCR_USDCLKFSEL_Msk & ((value) << SDMMC_CCR_USDCLKFSEL_Pos)))
#define SDMMC_CCR_SDCLKFSEL_Pos 8
#define SDMMC_CCR_SDCLKFSEL_Msk (0xffu << SDMMC_CCR_SDCLKFSEL_Pos) /**< \brief (SDMMC_CCR) SDCLK Frequency Select */
#define SDMMC_CCR_SDCLKFSEL(value) ((SDMMC_CCR_SDCLKFSEL_Msk & ((value) << SDMMC_CCR_SDCLKFSEL_Pos)))
/* -------- SDMMC_TCR : (SDMMC Offset: 0x2E) Timeout Control Register -------- */
#define SDMMC_TCR_DTCVAL_Pos 0
#define SDMMC_TCR_DTCVAL_Msk (0xfu << SDMMC_TCR_DTCVAL_Pos) /**< \brief (SDMMC_TCR) Data Timeout Counter Value */
#define SDMMC_TCR_DTCVAL(value) ((SDMMC_TCR_DTCVAL_Msk & ((value) << SDMMC_TCR_DTCVAL_Pos)))
/* -------- SDMMC_SRR : (SDMMC Offset: 0x2F) Software Reset Register -------- */
#define SDMMC_SRR_SWRSTALL (0x1u << 0) /**< \brief (SDMMC_SRR) Software reset for All */
#define SDMMC_SRR_SWRSTCMD (0x1u << 1) /**< \brief (SDMMC_SRR) Software reset for CMD line */
#define SDMMC_SRR_SWRSTDAT (0x1u << 2) /**< \brief (SDMMC_SRR) Software reset for DAT line */
/* -------- SDMMC_NISTR : (SDMMC Offset: 0x30) Normal Interrupt Status Register -------- */
#define SDMMC_NISTR_CMDC (0x1u << 0) /**< \brief (SDMMC_NISTR) Command Complete */
#define SDMMC_NISTR_TRFC (0x1u << 1) /**< \brief (SDMMC_NISTR) Transfer Complete */
#define SDMMC_NISTR_BLKGE (0x1u << 2) /**< \brief (SDMMC_NISTR) Block Gap Event */
#define SDMMC_NISTR_DMAINT (0x1u << 3) /**< \brief (SDMMC_NISTR) DMA Interrupt */
#define SDMMC_NISTR_BWRRDY (0x1u << 4) /**< \brief (SDMMC_NISTR) Buffer Write Ready */
#define SDMMC_NISTR_BRDRDY (0x1u << 5) /**< \brief (SDMMC_NISTR) Buffer Read Ready */
#define SDMMC_NISTR_CINT (0x1u << 8) /**< \brief (SDMMC_NISTR) Card Interrupt */
#define SDMMC_NISTR_ERRINT (0x1u << 15) /**< \brief (SDMMC_NISTR) Error Interrupt */
#define SDMMC_NISTR_BOOTAR (0x1u << 14) /**< \brief (SDMMC_NISTR) Boot Acknowledge Received */
/* -------- SDMMC_EISTR : (SDMMC Offset: 0x32) Error Interrupt Status Register -------- */
#define SDMMC_EISTR_CMDTEO (0x1u << 0) /**< \brief (SDMMC_EISTR) Command Timeout Error */
#define SDMMC_EISTR_CMDCRC (0x1u << 1) /**< \brief (SDMMC_EISTR) Command CRC Error */
#define SDMMC_EISTR_CMDEND (0x1u << 2) /**< \brief (SDMMC_EISTR) Command End Bit Error */
#define SDMMC_EISTR_CMDIDX (0x1u << 3) /**< \brief (SDMMC_EISTR) Command Index Error */
#define SDMMC_EISTR_DATTEO (0x1u << 4) /**< \brief (SDMMC_EISTR) Data Timeout Error */
#define SDMMC_EISTR_DATCRC (0x1u << 5) /**< \brief (SDMMC_EISTR) Data CRC error */
#define SDMMC_EISTR_DATEND (0x1u << 6) /**< \brief (SDMMC_EISTR) Data End Bit Error */
#define SDMMC_EISTR_CURLIM (0x1u << 7) /**< \brief (SDMMC_EISTR) Current Limit Error */
#define SDMMC_EISTR_ACMD (0x1u << 8) /**< \brief (SDMMC_EISTR) Auto CMD Error */
#define SDMMC_EISTR_ADMA (0x1u << 9) /**< \brief (SDMMC_EISTR) ADMA Error */
#define SDMMC_EISTR_BOOTAE (0x1u << 12) /**< \brief (SDMMC_EISTR) Boot Acknowledge Error */
/* -------- SDMMC_NISTER : (SDMMC Offset: 0x34) Normal Interrupt Status Enable Register -------- */
#define SDMMC_NISTER_CMDC (0x1u << 0) /**< \brief (SDMMC_NISTER) Command Complete Status Enable */
#define   SDMMC_NISTER_CMDC_MASKED (0x0u << 0) /**< \brief (SDMMC_NISTER) The CMDC status flag in SDMMC_NISTR is masked. */
#define   SDMMC_NISTER_CMDC_ENABLED (0x1u << 0) /**< \brief (SDMMC_NISTER) The CMDC status flag in SDMMC_NISTR is enabled. */
#define SDMMC_NISTER_TRFC (0x1u << 1) /**< \brief (SDMMC_NISTER) Transfer Complete Status Enable */
#define   SDMMC_NISTER_TRFC_MASKED (0x0u << 1) /**< \brief (SDMMC_NISTER) The TRFC status flag in SDMMC_NISTR is masked. */
#define   SDMMC_NISTER_TRFC_ENABLED (0x1u << 1) /**< \brief (SDMMC_NISTER) The TRFC status flag in SDMMC_NISTR is enabled. */
#define SDMMC_NISTER_BLKGE (0x1u << 2) /**< \brief (SDMMC_NISTER) Block Gap Event Status Enable */
#define   SDMMC_NISTER_BLKGE_MASKED (0x0u << 2) /**< \brief (SDMMC_NISTER) The BLKGE status flag in SDMMC_NISTR is masked. */
#define   SDMMC_NISTER_BLKGE_ENABLED (0x1u << 2) /**< \brief (SDMMC_NISTER) The BLKGE status flag in SDMMC_NISTR is enabled. */
#define SDMMC_NISTER_DMAINT (0x1u << 3) /**< \brief (SDMMC_NISTER) DMA Interrupt Status Enable */
#define   SDMMC_NISTER_DMAINT_MASKED (0x0u << 3) /**< \brief (SDMMC_NISTER) The DMAINT status flag in SDMMC_NISTR is masked. */
#define   SDMMC_NISTER_DMAINT_ENABLED (0x1u << 3) /**< \brief (SDMMC_NISTER) The DMAINT status flag in SDMMC_NISTR is enabled. */
#define SDMMC_NISTER_BWRRDY (0x1u << 4) /**< \brief (SDMMC_NISTER) Buffer Write Ready Status Enable */
#define   SDMMC_NISTER_BWRRDY_MASKED (0x0u << 4) /**< \brief (SDMMC_NISTER) The BWRRDY status flag in SDMMC_NISTR is masked. */
#define   SDMMC_NISTER_BWRRDY_ENABLED (0x1u << 4) /**< \brief (SDMMC_NISTER) The BWRRDY status flag in SDMMC_NISTR is enabled. */
#define SDMMC_NISTER_BRDRDY (0x1u << 5) /**< \brief (SDMMC_NISTER) Buffer Read Ready Status Enable */
#define   SDMMC_NISTER_BRDRDY_MASKED (0x0u << 5) /**< \brief (SDMMC_NISTER) The BRDRDY status flag in SDMMC_NISTR is masked. */
#define   SDMMC_NISTER_BRDRDY_ENABLED (0x1u << 5) /**< \brief (SDMMC_NISTER) The BRDRDY status flag in SDMMC_NISTR is enabled. */
#define SDMMC_NISTER_CINT (0x1u << 8) /**< \brief (SDMMC_NISTER) Card Interrupt Status Enable */
#define   SDMMC_NISTER_CINT_MASKED (0x0u << 8) /**< \brief (SDMMC_NISTER) The CINT status flag in SDMMC_NISTR is masked. */
#define   SDMMC_NISTER_CINT_ENABLED (0x1u << 8) /**< \brief (SDMMC_NISTER) The CINT status flag in SDMMC_NISTR is enabled. */
#define SDMMC_NISTER_BOOTAR (0x1u << 14) /**< \brief (SDMMC_NISTER) Boot Acknowledge Received Status Enable */
#define   SDMMC_NISTER_BOOTAR_MASKED (0x0u << 14) /**< \brief (SDMMC_NISTER) The BOOTAR status flag in SDMMC_NISTR is masked. */
#define   SDMMC_NISTER_BOOTAR_ENABLED (0x1u << 14) /**< \brief (SDMMC_NISTER) The BOOTAR status flag in SDMMC_NISTR is enabled. */
/* -------- SDMMC_EISTER : (SDMMC Offset: 0x36) Error Interrupt Status Enable Register -------- */
#define SDMMC_EISTER_CMDTEO (0x1u << 0) /**< \brief (SDMMC_EISTER) Command Timeout Error Status Enable */
#define   SDMMC_EISTER_CMDTEO_MASKED (0x0u << 0) /**< \brief (SDMMC_EISTER) The CMDTEO status flag in SDMMC_EISTR is masked. */
#define   SDMMC_EISTER_CMDTEO_ENABLED (0x1u << 0) /**< \brief (SDMMC_EISTER) The CMDTEO status flag in SDMMC_EISTR is enabled. */
#define SDMMC_EISTER_CMDCRC (0x1u << 1) /**< \brief (SDMMC_EISTER) Command CRC Error Status Enable */
#define   SDMMC_EISTER_CMDCRC_MASKED (0x0u << 1) /**< \brief (SDMMC_EISTER) The CMDCRC status flag in SDMMC_EISTR is masked. */
#define   SDMMC_EISTER_CMDCRC_ENABLED (0x1u << 1) /**< \brief (SDMMC_EISTER) The CMDCRC status flag in SDMMC_EISTR is enabled. */
#define SDMMC_EISTER_CMDEND (0x1u << 2) /**< \brief (SDMMC_EISTER) Command End Bit Error Status Enable */
#define   SDMMC_EISTER_CMDEND_MASKED (0x0u << 2) /**< \brief (SDMMC_EISTER) The CMDEND status flag in SDMMC_EISTR is masked. */
#define   SDMMC_EISTER_CMDEND_ENABLED (0x1u << 2) /**< \brief (SDMMC_EISTER) The CMDEND status flag in SDMMC_EISTR is enabled. */
#define SDMMC_EISTER_CMDIDX (0x1u << 3) /**< \brief (SDMMC_EISTER) Command Index Error Status Enable */
#define   SDMMC_EISTER_CMDIDX_MASKED (0x0u << 3) /**< \brief (SDMMC_EISTER) The CMDIDX status flag in SDMMC_EISTR is masked. */
#define   SDMMC_EISTER_CMDIDX_ENABLED (0x1u << 3) /**< \brief (SDMMC_EISTER) The CMDIDX status flag in SDMMC_EISTR is enabled. */
#define SDMMC_EISTER_DATTEO (0x1u << 4) /**< \brief (SDMMC_EISTER) Data Timeout Error Status Enable */
#define   SDMMC_EISTER_DATTEO_MASKED (0x0u << 4) /**< \brief (SDMMC_EISTER) The DATTEO status flag in SDMMC_EISTR is masked. */
#define   SDMMC_EISTER_DATTEO_ENABLED (0x1u << 4) /**< \brief (SDMMC_EISTER) The DATTEO status flag in SDMMC_EISTR is enabled. */
#define SDMMC_EISTER_DATCRC (0x1u << 5) /**< \brief (SDMMC_EISTER) Data CRC Error Status Enable */
#define   SDMMC_EISTER_DATCRC_MASKED (0x0u << 5) /**< \brief (SDMMC_EISTER) The DATCRC status flag in SDMMC_EISTR is masked. */
#define   SDMMC_EISTER_DATCRC_ENABLED (0x1u << 5) /**< \brief (SDMMC_EISTER) The DATCRC status flag in SDMMC_EISTR is enabled. */
#define SDMMC_EISTER_DATEND (0x1u << 6) /**< \brief (SDMMC_EISTER) Data End Bit Error Status Enable */
#define   SDMMC_EISTER_DATEND_MASKED (0x0u << 6) /**< \brief (SDMMC_EISTER) The DATEND status flag in SDMMC_EISTR is masked. */
#define   SDMMC_EISTER_DATEND_ENABLED (0x1u << 6) /**< \brief (SDMMC_EISTER) The DATEND status flag in SDMMC_EISTR is enabled. */
#define SDMMC_EISTER_CURLIM (0x1u << 7) /**< \brief (SDMMC_EISTER) Current Limit Error Status Enable */
#define   SDMMC_EISTER_CURLIM_MASKED (0x0u << 7) /**< \brief (SDMMC_EISTER) The CURLIM status flag in SDMMC_EISTR is masked. */
#define   SDMMC_EISTER_CURLIM_ENABLED (0x1u << 7) /**< \brief (SDMMC_EISTER) The CURLIM status flag in SDMMC_EISTR is enabled. */
#define SDMMC_EISTER_ACMD (0x1u << 8) /**< \brief (SDMMC_EISTER) Auto CMD Error Status Enable */
#define   SDMMC_EISTER_ACMD_MASKED (0x0u << 8) /**< \brief (SDMMC_EISTER) The ACMD status flag in SDMMC_EISTR is masked. */
#define   SDMMC_EISTER_ACMD_ENABLED (0x1u << 8) /**< \brief (SDMMC_EISTER) The ACMD status flag in SDMMC_EISTR is enabled. */
#define SDMMC_EISTER_ADMA (0x1u << 9) /**< \brief (SDMMC_EISTER) ADMA Error Status Enable */
#define   SDMMC_EISTER_ADMA_MASKED (0x0u << 9) /**< \brief (SDMMC_EISTER) The ADMA status flag in SDMMC_EISTR is masked. */
#define   SDMMC_EISTER_ADMA_ENABLED (0x1u << 9) /**< \brief (SDMMC_EISTER) The ADMA status flag in SDMMC_EISTR is enabled. */
#define SDMMC_EISTER_BOOTAE (0x1u << 12) /**< \brief (SDMMC_EISTER) Boot Acknowledge Error Status Enable */
#define   SDMMC_EISTER_BOOTAE_MASKED (0x0u << 12) /**< \brief (SDMMC_EISTER) The BOOTAE status flag in SDMMC_EISTR is masked. */
#define   SDMMC_EISTER_BOOTAE_ENABLED (0x1u << 12) /**< \brief (SDMMC_EISTER) The BOOTAE status flag in SDMMC_EISTR is enabled. */
/* -------- SDMMC_NISIER : (SDMMC Offset: 0x38) Normal Interrupt Signal Enable Register -------- */
#define SDMMC_NISIER_CMDC (0x1u << 0) /**< \brief (SDMMC_NISIER) Command Complete Signal Enable */
#define   SDMMC_NISIER_CMDC_MASKED (0x0u << 0) /**< \brief (SDMMC_NISIER) No interrupt is generated when the CMDC status rises in SDMMC_NISTR. */
#define   SDMMC_NISIER_CMDC_ENABLED (0x1u << 0) /**< \brief (SDMMC_NISIER) An interrupt is generated when the CMDC status rises in SDMMC_NISTR. */
#define SDMMC_NISIER_TRFC (0x1u << 1) /**< \brief (SDMMC_NISIER) Transfer Complete Signal Enable */
#define   SDMMC_NISIER_TRFC_MASKED (0x0u << 1) /**< \brief (SDMMC_NISIER) No interrupt is generated when the TRFC status rises in SDMMC_NISTR. */
#define   SDMMC_NISIER_TRFC_ENABLED (0x1u << 1) /**< \brief (SDMMC_NISIER) An interrupt is generated when the TRFC status rises in SDMMC_NISTR. */
#define SDMMC_NISIER_BLKGE (0x1u << 2) /**< \brief (SDMMC_NISIER) Block Gap Event Signal Enable */
#define   SDMMC_NISIER_BLKGE_MASKED (0x0u << 2) /**< \brief (SDMMC_NISIER) No interrupt is generated when the BLKGE status rises in SDMMC_NISTR. */
#define   SDMMC_NISIER_BLKGE_ENABLED (0x1u << 2) /**< \brief (SDMMC_NISIER) An interrupt is generated when the BLKGE status rises in SDMMC_NISTR. */
#define SDMMC_NISIER_DMAINT (0x1u << 3) /**< \brief (SDMMC_NISIER) DMA Interrupt Signal Enable */
#define   SDMMC_NISIER_DMAINT_MASKED (0x0u << 3) /**< \brief (SDMMC_NISIER) No interrupt is generated when the DMAINT status rises in SDMMC_NISTR. */
#define   SDMMC_NISIER_DMAINT_ENABLED (0x1u << 3) /**< \brief (SDMMC_NISIER) An interrupt is generated when the DMAINT status rises in SDMMC_NISTR. */
#define SDMMC_NISIER_BWRRDY (0x1u << 4) /**< \brief (SDMMC_NISIER) Buffer Write Ready Signal Enable */
#define   SDMMC_NISIER_BWRRDY_MASKED (0x0u << 4) /**< \brief (SDMMC_NISIER) No interrupt is generated when the BWRRDY status rises in SDMMC_NISTR. */
#define   SDMMC_NISIER_BWRRDY_ENABLED (0x1u << 4) /**< \brief (SDMMC_NISIER) An interrupt is generated when the BWRRDY status rises in SDMMC_NISTR. */
#define SDMMC_NISIER_BRDRDY (0x1u << 5) /**< \brief (SDMMC_NISIER) Buffer Read Ready Signal Enable */
#define   SDMMC_NISIER_BRDRDY_MASKED (0x0u << 5) /**< \brief (SDMMC_NISIER) No interrupt is generated when the BRDRDY status rises in SDMMC_NISTR. */
#define   SDMMC_NISIER_BRDRDY_ENABLED (0x1u << 5) /**< \brief (SDMMC_NISIER) An interrupt is generated when the BRDRDY status rises in SDMMC_NISTR. */
#define SDMMC_NISIER_CINT (0x1u << 8) /**< \brief (SDMMC_NISIER) Card Interrupt Signal Enable */
#define   SDMMC_NISIER_CINT_MASKED (0x0u << 8) /**< \brief (SDMMC_NISIER) No interrupt is generated when the CINT status rises in SDMMC_NISTR. */
#define   SDMMC_NISIER_CINT_ENABLED (0x1u << 8) /**< \brief (SDMMC_NISIER) An interrupt is generated when the CINT status rises in SDMMC_NISTR. */
#define SDMMC_NISIER_BOOTAR (0x1u << 14) /**< \brief (SDMMC_NISIER) Boot Acknowledge Received Signal Enable */
#define   SDMMC_NISIER_BOOTAR_MASKED (0x0u << 14) /**< \brief (SDMMC_NISIER) No interrupt is generated when the BOOTAR status rises in SDMMC_NISTR. */
#define   SDMMC_NISIER_BOOTAR_ENABLED (0x1u << 14) /**< \brief (SDMMC_NISIER) An interrupt is generated when the BOOTAR status rises in SDMMC_NISTR. */
/* -------- SDMMC_EISIER : (SDMMC Offset: 0x3A) Error Interrupt Signal Enable Register -------- */
#define SDMMC_EISIER_CMDTEO (0x1u << 0) /**< \brief (SDMMC_EISIER) Command Timeout Error Signal Enable */
#define   SDMMC_EISIER_CMDTEO_MASKED (0x0u << 0) /**< \brief (SDMMC_EISIER) No interrupt is generated when the CMDTEO status rises in SDMMC_EISTR. */
#define   SDMMC_EISIER_CMDTEO_ENABLED (0x1u << 0) /**< \brief (SDMMC_EISIER) An interrupt is generated when the CMDTEO status rises in SDMMC_EISTR. */
#define SDMMC_EISIER_CMDCRC (0x1u << 1) /**< \brief (SDMMC_EISIER) Command CRC Error Signal Enable */
#define   SDMMC_EISIER_CMDCRC_MASKED (0x0u << 1) /**< \brief (SDMMC_EISIER) No interrupt is generated when the CDMCRC status rises in SDMMC_EISTR. */
#define   SDMMC_EISIER_CMDCRC_ENABLED (0x1u << 1) /**< \brief (SDMMC_EISIER) An interrupt is generated when the CMDCRC status rises in SDMMC_EISTR. */
#define SDMMC_EISIER_CMDEND (0x1u << 2) /**< \brief (SDMMC_EISIER) Command End Bit Error Signal Enable */
#define   SDMMC_EISIER_CMDEND_MASKED (0x0u << 2) /**< \brief (SDMMC_EISIER) No interrupt is generated when the CMDEND status rises in SDMMC_EISTR. */
#define   SDMMC_EISIER_CMDEND_ENABLED (0x1u << 2) /**< \brief (SDMMC_EISIER) An interrupt is generated when the CMDEND status rises in SDMMC_EISTR. */
#define SDMMC_EISIER_CMDIDX (0x1u << 3) /**< \brief (SDMMC_EISIER) Command Index Error Signal Enable */
#define   SDMMC_EISIER_CMDIDX_MASKED (0x0u << 3) /**< \brief (SDMMC_EISIER) No interrupt is generated when the CMDIDX status rises in SDMMC_EISTR. */
#define   SDMMC_EISIER_CMDIDX_ENABLED (0x1u << 3) /**< \brief (SDMMC_EISIER) An interrupt is generated when the CMDIDX status rises in SDMMC_EISTR. */
#define SDMMC_EISIER_DATTEO (0x1u << 4) /**< \brief (SDMMC_EISIER) Data Timeout Error Signal Enable */
#define   SDMMC_EISIER_DATTEO_MASKED (0x0u << 4) /**< \brief (SDMMC_EISIER) No interrupt is generated when the DATTEO status rises in SDMMC_EISTR. */
#define   SDMMC_EISIER_DATTEO_ENABLED (0x1u << 4) /**< \brief (SDMMC_EISIER) An interrupt is generated when the DATTEO status rises in SDMMC_EISTR. */
#define SDMMC_EISIER_DATCRC (0x1u << 5) /**< \brief (SDMMC_EISIER) Data CRC Error Signal Enable */
#define   SDMMC_EISIER_DATCRC_MASKED (0x0u << 5) /**< \brief (SDMMC_EISIER) No interrupt is generated when the DATCRC status rises in SDMMC_EISTR. */
#define   SDMMC_EISIER_DATCRC_ENABLED (0x1u << 5) /**< \brief (SDMMC_EISIER) An interrupt is generated when the DATCRC status rises in SDMMC_EISTR. */
#define SDMMC_EISIER_DATEND (0x1u << 6) /**< \brief (SDMMC_EISIER) Data End Bit Error Signal Enable */
#define   SDMMC_EISIER_DATEND_MASKED (0x0u << 6) /**< \brief (SDMMC_EISIER) No interrupt is generated when the DATEND status rises in SDMMC_EISTR. */
#define   SDMMC_EISIER_DATEND_ENABLED (0x1u << 6) /**< \brief (SDMMC_EISIER) An interrupt is generated when the DATEND status rises in SDMMC_EISTR. */
#define SDMMC_EISIER_CURLIM (0x1u << 7) /**< \brief (SDMMC_EISIER) Current Limit Error Signal Enable */
#define   SDMMC_EISIER_CURLIM_MASKED (0x0u << 7) /**< \brief (SDMMC_EISIER) No interrupt is generated when the CURLIM status rises in SDMMC_EISTR. */
#define   SDMMC_EISIER_CURLIM_ENABLED (0x1u << 7) /**< \brief (SDMMC_EISIER) An interrupt is generated when the CURLIM status rises in SDMMC_EISTR. */
#define SDMMC_EISIER_ACMD (0x1u << 8) /**< \brief (SDMMC_EISIER) Auto CMD Error Signal Enable */
#define   SDMMC_EISIER_ACMD_MASKED (0x0u << 8) /**< \brief (SDMMC_EISIER) No interrupt is generated when the ACMD status rises in SDMMC_EISTR. */
#define   SDMMC_EISIER_ACMD_ENABLED (0x1u << 8) /**< \brief (SDMMC_EISIER) An interrupt is generated when the ACMD status rises in SDMMC_EISTR. */
#define SDMMC_EISIER_ADMA (0x1u << 9) /**< \brief (SDMMC_EISIER) ADMA Error Signal Enable */
#define   SDMMC_EISIER_ADMA_MASKED (0x0u << 9) /**< \brief (SDMMC_EISIER) No interrupt is generated when the ADMA status rises in SDMMC_EISTR. */
#define   SDMMC_EISIER_ADMA_ENABLED (0x1u << 9) /**< \brief (SDMMC_EISIER) An interrupt is generated when the ADMA status rises in SDMMC_EISTR. */
#define SDMMC_EISIER_BOOTAE (0x1u << 12) /**< \brief (SDMMC_EISIER) Boot Acknowledge Error Signal Enable */
#define   SDMMC_EISIER_BOOTAE_MASKED (0x0u << 12) /**< \brief (SDMMC_EISIER) No interrupt is generated when the BOOTAE status rises in SDMMC_EISTR. */
#define   SDMMC_EISIER_BOOTAE_ENABLED (0x1u << 12) /**< \brief (SDMMC_EISIER) An interrupt is generated when the BOOTAE status rises in SDMMC_EISTR. */
/* -------- SDMMC_ACESR : (SDMMC Offset: 0x3C) Auto CMD Error Status Register -------- */
#define SDMMC_ACESR_ACMD12NE (0x1u << 0) /**< \brief (SDMMC_ACESR) Auto CMD12 Not Executed */
#define SDMMC_ACESR_ACMDTEO (0x1u << 1) /**< \brief (SDMMC_ACESR) Auto CMD Timeout Error */
#define SDMMC_ACESR_ACMDCRC (0x1u << 2) /**< \brief (SDMMC_ACESR) Auto CMD CRC Error */
#define SDMMC_ACESR_ACMDEND (0x1u << 3) /**< \brief (SDMMC_ACESR) Auto CMD End Bit Error */
#define SDMMC_ACESR_ACMDIDX (0x1u << 4) /**< \brief (SDMMC_ACESR) Auto CMD Index Error */
#define SDMMC_ACESR_CMDNI (0x1u << 7) /**< \brief (SDMMC_ACESR) Command Not Issued by Auto CMD12 Error */
/* -------- SDMMC_HC2R : (SDMMC Offset: 0x3E) Host Control 2 Register -------- */
#define SDMMC_HC2R_ASINTEN (0x1u << 14) /**< \brief (SDMMC_HC2R) Asynchronous Interrupt Enable */
#define SDMMC_HC2R_PVALEN (0x1u << 15) /**< \brief (SDMMC_HC2R) Preset Value Enable */
/* -------- SDMMC_CA0R : (SDMMC Offset: 0x40) Capabilities 0 Register -------- */
#define SDMMC_CA0R_TEOCLKF_Pos 0
#define SDMMC_CA0R_TEOCLKF_Msk (0x3fu << SDMMC_CA0R_TEOCLKF_Pos) /**< \brief (SDMMC_CA0R) Timeout Clock Frequency */
#define SDMMC_CA0R_TEOCLKF(value) ((SDMMC_CA0R_TEOCLKF_Msk & ((value) << SDMMC_CA0R_TEOCLKF_Pos)))
#define SDMMC_CA0R_TEOCLKU (0x1u << 7) /**< \brief (SDMMC_CA0R) Timeout Clock Unit */
#define SDMMC_CA0R_BASECLKF_Pos 8
#define SDMMC_CA0R_BASECLKF_Msk (0xffu << SDMMC_CA0R_BASECLKF_Pos) /**< \brief (SDMMC_CA0R) Base Clock Frequency */
#define SDMMC_CA0R_BASECLKF(value) ((SDMMC_CA0R_BASECLKF_Msk & ((value) << SDMMC_CA0R_BASECLKF_Pos)))
#define SDMMC_CA0R_MAXBLKL_Pos 16
#define SDMMC_CA0R_MAXBLKL_Msk (0x3u << SDMMC_CA0R_MAXBLKL_Pos) /**< \brief (SDMMC_CA0R) Max Block Length */
#define SDMMC_CA0R_MAXBLKL(value) ((SDMMC_CA0R_MAXBLKL_Msk & ((value) << SDMMC_CA0R_MAXBLKL_Pos)))
#define   SDMMC_CA0R_MAXBLKL_512 (0x0u << 16) /**< \brief (SDMMC_CA0R) 512 bytes */
#define   SDMMC_CA0R_MAXBLKL_1024 (0x1u << 16) /**< \brief (SDMMC_CA0R) 1024 bytes */
#define   SDMMC_CA0R_MAXBLKL_2048 (0x2u << 16) /**< \brief (SDMMC_CA0R) 2048 bytes */
#define SDMMC_CA0R_ED8SUP (0x1u << 18) /**< \brief (SDMMC_CA0R) 8-Bit Support for Embedded Device */
#define SDMMC_CA0R_ADMA2SUP (0x1u << 19) /**< \brief (SDMMC_CA0R) ADMA2 Support */
#define SDMMC_CA0R_HSSUP (0x1u << 21) /**< \brief (SDMMC_CA0R) High Speed Support */
#define SDMMC_CA0R_SDMASUP (0x1u << 22) /**< \brief (SDMMC_CA0R) SDMA Support */
#define SDMMC_CA0R_SRSUP (0x1u << 23) /**< \brief (SDMMC_CA0R) Suspend/Resume Support */
#define SDMMC_CA0R_V33VSUP (0x1u << 24) /**< \brief (SDMMC_CA0R) Voltage Support 3.3V */
#define SDMMC_CA0R_V30VSUP (0x1u << 25) /**< \brief (SDMMC_CA0R) Voltage Support 3.0V */
#define SDMMC_CA0R_V18VSUP (0x1u << 26) /**< \brief (SDMMC_CA0R) Voltage Support 1.8V */
#define SDMMC_CA0R_SB64SUP (0x1u << 28) /**< \brief (SDMMC_CA0R) 64-Bit System Bus Support */
#define SDMMC_CA0R_ASINTSUP (0x1u << 29) /**< \brief (SDMMC_CA0R) Asynchronous Interrupt Support */
#define SDMMC_CA0R_SLTYPE_Pos 30
#define SDMMC_CA0R_SLTYPE_Msk (0x3u << SDMMC_CA0R_SLTYPE_Pos) /**< \brief (SDMMC_CA0R) Slot Type */
#define SDMMC_CA0R_SLTYPE(value) ((SDMMC_CA0R_SLTYPE_Msk & ((value) << SDMMC_CA0R_SLTYPE_Pos)))
#define   SDMMC_CA0R_SLTYPE_REMOVABLECARD (0x0u << 30) /**< \brief (SDMMC_CA0R) Removable Card Slot */
#define   SDMMC_CA0R_SLTYPE_EMBEDDED (0x1u << 30) /**< \brief (SDMMC_CA0R) Embedded Slot for One Device */
/* -------- SDMMC_CA1R : (SDMMC Offset: 0x44) Capabilities 1 Register -------- */
#define SDMMC_CA1R_SDR50SUP (0x1u << 0) /**< \brief (SDMMC_CA1R) SDR50 Support */
#define SDMMC_CA1R_SDR104SUP (0x1u << 1) /**< \brief (SDMMC_CA1R) SDR104 Support */
#define SDMMC_CA1R_DDR50SUP (0x1u << 2) /**< \brief (SDMMC_CA1R) DDR50 Support */
#define SDMMC_CA1R_DRVASUP (0x1u << 4) /**< \brief (SDMMC_CA1R) Driver Type A Support */
#define SDMMC_CA1R_DRVCSUP (0x1u << 5) /**< \brief (SDMMC_CA1R) Driver Type C Support */
#define SDMMC_CA1R_DRVDSUP (0x1u << 6) /**< \brief (SDMMC_CA1R) Driver Type D Support */
#define SDMMC_CA1R_CLKMULT_Pos 16
#define SDMMC_CA1R_CLKMULT_Msk (0xffu << SDMMC_CA1R_CLKMULT_Pos) /**< \brief (SDMMC_CA1R) Clock Multiplier */
#define SDMMC_CA1R_CLKMULT(value) ((SDMMC_CA1R_CLKMULT_Msk & ((value) << SDMMC_CA1R_CLKMULT_Pos)))
/* -------- SDMMC_MCCAR : (SDMMC Offset: 0x48) Maximum Current Capabilities Register -------- */
#define SDMMC_MCCAR_MAXCUR33V_Pos 0
#define SDMMC_MCCAR_MAXCUR33V_Msk (0xffu << SDMMC_MCCAR_MAXCUR33V_Pos) /**< \brief (SDMMC_MCCAR) Maximum Current for 3.3V */
#define SDMMC_MCCAR_MAXCUR33V(value) ((SDMMC_MCCAR_MAXCUR33V_Msk & ((value) << SDMMC_MCCAR_MAXCUR33V_Pos)))
#define SDMMC_MCCAR_MAXCUR30V_Pos 8
#define SDMMC_MCCAR_MAXCUR30V_Msk (0xffu << SDMMC_MCCAR_MAXCUR30V_Pos) /**< \brief (SDMMC_MCCAR) Maximum Current for 3.0V */
#define SDMMC_MCCAR_MAXCUR30V(value) ((SDMMC_MCCAR_MAXCUR30V_Msk & ((value) << SDMMC_MCCAR_MAXCUR30V_Pos)))
#define SDMMC_MCCAR_MAXCUR18V_Pos 16
#define SDMMC_MCCAR_MAXCUR18V_Msk (0xffu << SDMMC_MCCAR_MAXCUR18V_Pos) /**< \brief (SDMMC_MCCAR) Maximum Current for 1.8V */
#define SDMMC_MCCAR_MAXCUR18V(value) ((SDMMC_MCCAR_MAXCUR18V_Msk & ((value) << SDMMC_MCCAR_MAXCUR18V_Pos)))
/* -------- SDMMC_FERACES : (SDMMC Offset: 0x50) Force Event Register for Auto CMD Error Status -------- */
#define SDMMC_FERACES_ACMD12NE (0x1u << 0) /**< \brief (SDMMC_FERACES) Force Event for Auto CMD12 Not Executed */
#define SDMMC_FERACES_ACMDTEO (0x1u << 1) /**< \brief (SDMMC_FERACES) Force Event for Auto CMD Timeout Error */
#define SDMMC_FERACES_ACMDCRC (0x1u << 2) /**< \brief (SDMMC_FERACES) Force Event for Auto CMD CRC Error */
#define SDMMC_FERACES_ACMDEND (0x1u << 3) /**< \brief (SDMMC_FERACES) Force Event for Auto CMD End Bit Error */
#define SDMMC_FERACES_ACMDIDX (0x1u << 4) /**< \brief (SDMMC_FERACES) Force Event for Auto CMD Index Error */
#define SDMMC_FERACES_CMDNI (0x1u << 7) /**< \brief (SDMMC_FERACES) Force Event for Command Not Issued by Auto CMD12 Error */
/* -------- SDMMC_FEREIS : (SDMMC Offset: 0x52) Force Event Register for Error Interrupt Status -------- */
#define SDMMC_FEREIS_CMDTEO (0x1u << 0) /**< \brief (SDMMC_FEREIS) Force Event for Command Timeout Error */
#define SDMMC_FEREIS_CMDCRC (0x1u << 1) /**< \brief (SDMMC_FEREIS) Force Event for Command CRC Error */
#define SDMMC_FEREIS_CMDEND (0x1u << 2) /**< \brief (SDMMC_FEREIS) Force Event for Command End Bit Error */
#define SDMMC_FEREIS_CMDIDX (0x1u << 3) /**< \brief (SDMMC_FEREIS) Force Event for Command Index Error */
#define SDMMC_FEREIS_DATTEO (0x1u << 4) /**< \brief (SDMMC_FEREIS) Force Event for Data Timeout error */
#define SDMMC_FEREIS_DATCRC (0x1u << 5) /**< \brief (SDMMC_FEREIS) Force Event for Data CRC error */
#define SDMMC_FEREIS_DATEND (0x1u << 6) /**< \brief (SDMMC_FEREIS) Force Event for Data End Bit Error */
#define SDMMC_FEREIS_CURLIM (0x1u << 7) /**< \brief (SDMMC_FEREIS) Force Event for Current Limit Error */
#define SDMMC_FEREIS_ACMD (0x1u << 8) /**< \brief (SDMMC_FEREIS) Force Event for Auto CMD Error */
#define SDMMC_FEREIS_ADMA (0x1u << 9) /**< \brief (SDMMC_FEREIS) Force Event for ADMA Error */
#define SDMMC_FEREIS_BOOTAE (0x1u << 12) /**< \brief (SDMMC_FEREIS) Force Event for Boot Acknowledge Error */
/* -------- SDMMC_AESR : (SDMMC Offset: 0x54) ADMA Error Status Register -------- */
#define SDMMC_AESR_ERRST_Pos 0
#define SDMMC_AESR_ERRST_Msk (0x3u << SDMMC_AESR_ERRST_Pos) /**< \brief (SDMMC_AESR) ADMA Error State */
#define   SDMMC_AESR_ERRST_STOP (0x0u << 0) /**< \brief (SDMMC_AESR) (Stop DMA) SDMMC_ASAR points to the descriptor following the error descriptor */
#define   SDMMC_AESR_ERRST_FDS (0x1u << 0) /**< \brief (SDMMC_AESR) (Fetch Descriptor) SDMMC_ASAR points to the error descriptor */
#define   SDMMC_AESR_ERRST_TFR (0x3u << 0) /**< \brief (SDMMC_AESR) (Transfer Data) SDMMC_ASAR points to the descriptor following the error descriptor */
#define SDMMC_AESR_LMIS (0x1u << 2) /**< \brief (SDMMC_AESR) ADMA Length Mismatch Error */
/* -------- SDMMC_ASAR0 : (SDMMC Offset: 0x58) ADMA System Address Register 0 -------- */
#define SDMMC_ASA0R_ADMASA_Pos 0
#define SDMMC_ASA0R_ADMASA_Msk (0xffffffffu << SDMMC_ASA0R_ADMASA_Pos) /**< \brief (SDMMC_ASA0R) ADMA System Address */
#define SDMMC_ASA0R_ADMASA(value) ((SDMMC_ASA0R_ADMASA_Msk & ((value) << SDMMC_ASA0R_ADMASA_Pos)))
/* -------- SDMMC_PVR[3] : (SDMMC Offset: 0x60) Preset Value Register 0 (for initialization) -------- */
#define SDMMC_PVR_SDCLKFSEL_Pos 0
#define SDMMC_PVR_SDCLKFSEL_Msk (0x3ffu << SDMMC_PVR_SDCLKFSEL_Pos) /**< \brief (SDMMC_PVR[3]) SDCLK Frequency Select */
#define SDMMC_PVR_SDCLKFSEL(value) ((SDMMC_PVR_SDCLKFSEL_Msk & ((value) << SDMMC_PVR_SDCLKFSEL_Pos)))
#define SDMMC_PVR_CLKGSEL (0x1u << 10) /**< \brief (SDMMC_PVR[3]) Clock Generator Select */
/* -------- SDMMC_SISR : (SDMMC Offset: 0xFC) Slot Interrupt Status Register -------- */
#define SDMMC_SISR_INTSSL_Pos 0
#define SDMMC_SISR_INTSSL_Msk (0x3u << SDMMC_SISR_INTSSL_Pos) /**< \brief (SDMMC_SISR) Interrupt Signal for Each Slot */
/* -------- SDMMC_HCVR : (SDMMC Offset: 0xFE) Host Controller Version Register -------- */
#define SDMMC_HCVR_SVER_Pos 0
#define SDMMC_HCVR_SVER_Msk (0xffu << SDMMC_HCVR_SVER_Pos) /**< \brief (SDMMC_HCVR) Specification Version Number */
#define SDMMC_HCVR_VVER_Pos 8
#define SDMMC_HCVR_VVER_Msk (0xffu << SDMMC_HCVR_VVER_Pos) /**< \brief (SDMMC_HCVR) Vendor Version Number */
/* -------- SDMMC_APSR : (SDMMC Offset: 0x200) Additional Present State Register -------- */
#define SDMMC_APSR_HDATLL_Pos 0
#define SDMMC_APSR_HDATLL_Msk (0xfu << SDMMC_APSR_HDATLL_Pos) /**< \brief (SDMMC_APSR) DAT[7:4] High Line Level */
/* -------- SDMMC_MC1R : (SDMMC Offset: 0x204) e.MMC Control 1 Register -------- */
#define SDMMC_MC1R_CMDTYP_Pos 0
#define SDMMC_MC1R_CMDTYP_Msk (0x3u << SDMMC_MC1R_CMDTYP_Pos) /**< \brief (SDMMC_MC1R) e.MMC Command Type */
#define SDMMC_MC1R_CMDTYP(value) ((SDMMC_MC1R_CMDTYP_Msk & ((value) << SDMMC_MC1R_CMDTYP_Pos)))
#define   SDMMC_MC1R_CMDTYP_NORMAL (0x0u << 0) /**< \brief (SDMMC_MC1R) The command is not an e.MMC specific command. */
#define   SDMMC_MC1R_CMDTYP_WAITIRQ (0x1u << 0) /**< \brief (SDMMC_MC1R) This bit must be set to 1 when the e.MMC is in Interrupt mode (CMD40). See "Interrupt Mode" in the Embedded MultiMedia Card (e.MMC) Electrical Standard 4.51. */
#define   SDMMC_MC1R_CMDTYP_STREAM (0x2u << 0) /**< \brief (SDMMC_MC1R) This bit must be set to 1 in the case of Stream Read(CMD11) or Stream Write (CMD20). Only effective for e.MMC up to revision 4.41. */
#define   SDMMC_MC1R_CMDTYP_BOOT (0x3u << 0) /**< \brief (SDMMC_MC1R) Starts a Boot Operation mode at the next write to SDMMC_CR. Boot data are read directly from e.MMC device. */
#define SDMMC_MC1R_DDR (0x1u << 3) /**< \brief (SDMMC_MC1R) e.MMC HSDDR Mode */
#define SDMMC_MC1R_OPD (0x1u << 4) /**< \brief (SDMMC_MC1R) e.MMC Open Drain Mode */
#define SDMMC_MC1R_BOOTA (0x1u << 5) /**< \brief (SDMMC_MC1R) e.MMC Boot Acknowledge Enable */
/* -------- SDMMC_MC2R : (SDMMC Offset: 0x205) e.MMC Control 2 Register -------- */
#define SDMMC_MC2R_SRESP (0x1u << 0) /**< \brief (SDMMC_MC2R) e.MMC Abort Wait IRQ */
#define SDMMC_MC2R_ABOOT (0x1u << 1) /**< \brief (SDMMC_MC2R) e.MMC Abort Boot */
/* -------- SDMMC_ACR : (SDMMC Offset: 0x208) AHB Control Register -------- */
#define SDMMC_ACR_BMAX_Pos 0
#define SDMMC_ACR_BMAX_Msk (0x3u << SDMMC_ACR_BMAX_Pos) /**< \brief (SDMMC_ACR) AHB Maximum Burst */
#define SDMMC_ACR_BMAX(value) ((SDMMC_ACR_BMAX_Msk & ((value) << SDMMC_ACR_BMAX_Pos)))
#define   SDMMC_ACR_BMAX_INCR16 (0x0u << 0) /**< \brief (SDMMC_ACR) The maximum burst size is INCR16. */
#define   SDMMC_ACR_BMAX_INCR8 (0x1u << 0) /**< \brief (SDMMC_ACR) The maximum burst size is INCR8. */
#define   SDMMC_ACR_BMAX_INCR4 (0x2u << 0) /**< \brief (SDMMC_ACR) The maximum burst size is INCR4. */
#define   SDMMC_ACR_BMAX_SINGLE (0x3u << 0) /**< \brief (SDMMC_ACR) Only SINGLE transfers are performed. */
#define SDMMC_ACR_HNBRDIS (0x1u << 4) /**< \brief (SDMMC_ACR) HNBREQ Disable */
#define SDMMC_ACR_B1KBDIS (0x1u << 5) /**< \brief (SDMMC_ACR) 1kB Boundary Disable */
/* -------- SDMMC_CC2R : (SDMMC Offset: 0x20C) Clock Control 2 Register -------- */
#define SDMMC_CC2R_FSDCLKD (0x1u << 0) /**< \brief (SDMMC_CC2R) Force SDCLK Disabled */
/* -------- SDMMC_TUNSR : (SDMMC Offset: 0x224) Tuning Status Register -------- */
#define SDMMC_TUNSR_DLLPS_Pos 0
#define SDMMC_TUNSR_DLLPS_Msk (0xfu << SDMMC_TUNSR_DLLPS_Pos) /**< \brief (SDMMC_TUNSR) Tuning DLL Phase Status */
#define SDMMC_TUNSR_SMPLES (0x1u << 8) /**< \brief (SDMMC_TUNSR) Tuning Sampling SDCLK Edge Status */
/* -------- SDMMC_CACR : (SDMMC Offset: 0x230) Capabilities Control Register -------- */
#define SDMMC_CACR_CAPWREN (0x1u << 0) /**< \brief (SDMMC_CACR) Capabilities Write Enable */
#define SDMMC_CACR_KEY_Pos 8
#define SDMMC_CACR_KEY_Msk (0xffu << SDMMC_CACR_KEY_Pos) /**< \brief (SDMMC_CACR) Key */
#define SDMMC_CACR_KEY(value) ((SDMMC_CACR_KEY_Msk & ((value) << SDMMC_CACR_KEY_Pos)))
#define   SDMMC_CACR_KEY_KEY (0x46u << 8) /**< \brief (SDMMC_CACR) Writing any other value in this field aborts the write operation of the CAPWREN bit. Always reads as 0. */
/* -------- SDMMC_DBGR : (SDMMC Offset: 0x234) Debug Register -------- */
#define SDMMC_DBGR_NIDBG (0x1u << 0) /**< \brief (SDMMC_DBGR) Nonintrusive Debug */
#define   SDMMC_DBGR_NIDBG_DISABLED (0x0u << 0) /**< \brief (SDMMC_DBGR) Reading the SDMMC_BDPR via debugger increments the dual port RAM read pointer. */
#define   SDMMC_DBGR_NIDBG_ENABLED (0x1u << 0) /**< \brief (SDMMC_DBGR) Reading the SDMMC_BDPR via debugger does not increment the dual port RAM read pointer. */
/* --------  SDMMC Descriptor Table for Advanced DMA 2 as pointed by SDMMC_ASA0R */
#define SDMMC_DMADL_SIZE (2u) /**< \brief Size of a Descriptor Line in the ADMA2 Descriptor Table, in words */
#define SDMMC_DMADL_TRAN_LEN_MIN (1u) /**< \brief Minimum data length per ADMA2 Descriptor Line, in bytes */
#define SDMMC_DMADL_TRAN_LEN_MAX (65536ul) /**< \brief Maximum data length per ADMA2 Descriptor Line, in bytes */
/* --------  SDMMC_DMADL[0] (Descriptor Line Offset: 0x0) ADMA2 Descriptor Line */
#define SDMMC_DMA0DL_ATTR_VALID (0x1u << 0)
#define SDMMC_DMA0DL_ATTR_END (0x1u << 1)
#define SDMMC_DMA0DL_ATTR_INT (0x1u << 2)
#define SDMMC_DMA0DL_ATTR_ACT_Pos 4
#define SDMMC_DMA0DL_ATTR_ACT_Msk (0x3u << SDMMC_DMA0DL_ATTR_ACT_Pos)
#define   SDMMC_DMA0DL_ATTR_ACT_NOP (0x0u << 4)
#define   SDMMC_DMA0DL_ATTR_ACT_TRAN (0x2u << 4)
#define   SDMMC_DMA0DL_ATTR_ACT_LINK (0x3u << 4)
#define SDMMC_DMA0DL_LEN_Pos 16
#define SDMMC_DMA0DL_LEN_Msk (0xFFFFu << SDMMC_DMA0DL_LEN_Pos)
#define   SDMMC_DMA0DL_LEN_MAX (0x0u << 16)
#define SDMMC_DMA0DL_LEN(value) ((SDMMC_DMA0DL_LEN_Msk & ((value) << SDMMC_DMA0DL_LEN_Pos)))
/* --------  SDMMC_DMADL[1] (Descriptor Line Offset: 0x4) ADMA2 Descriptor Line */
#define SDMMC_DMA1DL_ADDR_Pos 0
#define SDMMC_DMA1DL_ADDR_Msk (0xFFFFFFFFu << SDMMC_DMA1DL_ADDR_Pos)
#define SDMMC_DMA1DL_ADDR(value) ((SDMMC_DMA1DL_ADDR_Msk & ((value) << SDMMC_DMA1DL_ADDR_Pos)))

/*@}*/


#endif /* _SAM9X_SDMMC_COMPONENT_ */
