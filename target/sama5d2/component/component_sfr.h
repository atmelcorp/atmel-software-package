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

#ifndef _SAMA5D2_SFR_COMPONENT_
#define _SAMA5D2_SFR_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Special Function Registers */
/* ============================================================================= */
/** \addtogroup SAMA5D2_SFR Special Function Registers */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Sfr hardware registers */
typedef struct {
  __IO uint32_t SFR_EMA;        /**< \brief (Sfr Offset: 0x00) Memory Margin Adjustment Register */
  __IO uint32_t SFR_DDRCFG;     /**< \brief (Sfr Offset: 0x04) DDR Configuration Register */
  __I  uint32_t Reserved1[2];
  __IO uint32_t SFR_OHCIICR;    /**< \brief (Sfr Offset: 0x10) OHCI Interrupt Configuration Register */
  __I  uint32_t SFR_OHCIISR;    /**< \brief (Sfr Offset: 0x14) OHCI Interrupt Status Register */
  __I  uint32_t Reserved2[1];
  __IO uint32_t SFR_CORTEX;     /**< \brief (Sfr Offset: 0x1C) Cortex Configuration Register */
  __IO uint32_t SFR_AHB;        /**< \brief (Sfr Offset: 0x20) AHB Configuration Register */
  __IO uint32_t SFR_BRIDGE;     /**< \brief (Sfr Offset: 0x24) Bridge Configuration Register */
  __IO uint32_t SFR_SECURE;     /**< \brief (Sfr Offset: 0x28) Security Configuration Register */
  __I  uint32_t Reserved3[1];
  __IO uint32_t SFR_UTMICKTRIM; /**< \brief (Sfr Offset: 0x30) UTMI Clock Trimming Register */
  __IO uint32_t SFR_UTMIHSTRIM; /**< \brief (Sfr Offset: 0x34) UTMI High Speed Trimming Register */
  __IO uint32_t SFR_UTMIFSTRIM; /**< \brief (Sfr Offset: 0x38) UTMI Full Speed Trimming Register */
  __IO uint32_t SFR_UTMISWAP;   /**< \brief (Sfr Offset: 0x3C) UTMI DP/DM Pin Swapping Register */
  __IO uint32_t SFR_EBICFG;     /**< \brief (Sfr Offset: 0x40) EBI Configuration Register */
  __IO uint32_t SFR_ANACFG;     /**< \brief (Sfr Offset: 0x44) Analog Configuration Register */
  __IO uint32_t SFR_CAN;        /**< \brief (Sfr Offset: 0x48) CAN memories address based Register */
  __I  uint32_t SFR_SN0;        /**< \brief (Sfr Offset: 0x4C) Serial Number 0 Register */
  __I  uint32_t SFR_SN1;        /**< \brief (Sfr Offset: 0x50) Seriel Number 1 Register */
  __IO uint32_t SFR_AICREDIR;   /**< \brief (Sfr Offset: 0x54) AIC interrupt Redirection Register */
  __IO uint32_t SFR_L2CC_HRAMC; /**< \brief (Sfr Offset: 0x58) L2CC_HRAMC1 */
  __IO uint32_t SFR_RM0;        /**< \brief (Sfr Offset: 0x5C) ReadMargin0 Register */
  __IO uint32_t SFR_RM1;        /**< \brief (Sfr Offset: 0x60) ReadMargin1 Register */
  __IO uint32_t SFR_RM2;        /**< \brief (Sfr Offset: 0x64) ReadMargin2 Register */
  __IO uint32_t SFR_RM3;        /**< \brief (Sfr Offset: 0x68) ReadMargin3 Register */
  __IO uint32_t SFR_RM4;        /**< \brief (Sfr Offset: 0x6C) ReadMargin4 Register */
  __IO uint32_t SFR_RM5;        /**< \brief (Sfr Offset: 0x70) ReadMargin5 Register */
  __IO uint32_t SFR_RM6;        /**< \brief (Sfr Offset: 0x74) ReadMargin6 Register */
  __IO uint32_t SFR_RM7;        /**< \brief (Sfr Offset: 0x78) ReadMargin7 Register */
  __I  uint32_t Reserved4[5];
  __IO uint32_t SFR_I2SCLKSEL;  /**< \brief (Sfr Offset: 0x90) I2S Register */
} Sfr;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- SFR_EMA : (SFR Offset: 0x00) Memory Margin Adjustment Register -------- */
#define SFR_EMA_RD_RAM_F_Pos 0
#define SFR_EMA_RD_RAM_F_Msk (0x3u << SFR_EMA_RD_RAM_F_Pos) /**< \brief (SFR_EMA) Value of Single Port RAM (FAST option) READ Margin Adjustment */
#define SFR_EMA_RD_RAM_F(value) ((SFR_EMA_RD_RAM_F_Msk & ((value) << SFR_EMA_RD_RAM_F_Pos)))
#define SFR_EMA_WR_RAM_F_Pos 4
#define SFR_EMA_WR_RAM_F_Msk (0x7u << SFR_EMA_WR_RAM_F_Pos) /**< \brief (SFR_EMA) Value of Single Port RAM (FAST option) WRITE Margin Adjustment */
#define SFR_EMA_WR_RAM_F(value) ((SFR_EMA_WR_RAM_F_Msk & ((value) << SFR_EMA_WR_RAM_F_Pos)))
#define SFR_EMA_RD_RAM_S_Pos 8
#define SFR_EMA_RD_RAM_S_Msk (0x3u << SFR_EMA_RD_RAM_S_Pos) /**< \brief (SFR_EMA) Value of Single Port RAM (SMALL option) READ Margin Adjustment */
#define SFR_EMA_RD_RAM_S(value) ((SFR_EMA_RD_RAM_S_Msk & ((value) << SFR_EMA_RD_RAM_S_Pos)))
#define SFR_EMA_WR_RAM_S_Pos 12
#define SFR_EMA_WR_RAM_S_Msk (0x7u << SFR_EMA_WR_RAM_S_Pos) /**< \brief (SFR_EMA) Value of Single Port RAM (SMALL option) WRITE Margin Adjustment */
#define SFR_EMA_WR_RAM_S(value) ((SFR_EMA_WR_RAM_S_Msk & ((value) << SFR_EMA_WR_RAM_S_Pos)))
#define SFR_EMA_ARM_TURBO (0x1u << 16) /**< \brief (SFR_EMA) Turbo Mode for High Speed Operation */
#define SFR_EMA_ARM_TSEL_Pos 17
#define SFR_EMA_ARM_TSEL_Msk (0x3u << SFR_EMA_ARM_TSEL_Pos) /**< \brief (SFR_EMA) Timing Selection Input */
#define SFR_EMA_ARM_TSEL(value) ((SFR_EMA_ARM_TSEL_Msk & ((value) << SFR_EMA_ARM_TSEL_Pos)))
#define SFR_EMA_ARM_RTSEL (0x1u << 19) /**< \brief (SFR_EMA) Read Timing Select For Testing */
/* -------- SFR_DDRCFG : (SFR Offset: 0x04) DDR Configuration Register -------- */
#define SFR_DDRCFG_CLKDELAY (0x1u << 8) /**< \brief (SFR_DDRCFG) DDR Clocks Delay */
#define   SFR_DDRCFG_CLKDELAY_HARD (0x0u << 8) /**< \brief (SFR_DDRCFG) DDR clocks delay controlled by hardware. */
#define   SFR_DDRCFG_CLKDELAY_SOFT (0x1u << 8) /**< \brief (SFR_DDRCFG) DDR clocks delay controlled by software. */
#define SFR_DDRCFG_FDQIEN (0x1u << 16) /**< \brief (SFR_DDRCFG) Force DDR_DQ Input Buffer Always On */
#define SFR_DDRCFG_FDQSIEN (0x1u << 17) /**< \brief (SFR_DDRCFG) Force DDR_DQS Input Buffer Always On */
/* -------- SFR_OHCIICR : (SFR Offset: 0x10) OHCI Interrupt Configuration Register -------- */
#define SFR_OHCIICR_RES0 (0x1u << 0) /**< \brief (SFR_OHCIICR) USB PORTx RESET */
#define SFR_OHCIICR_RES1 (0x1u << 1) /**< \brief (SFR_OHCIICR) USB PORTx RESET */
#define SFR_OHCIICR_RES2 (0x1u << 2) /**< \brief (SFR_OHCIICR) USB PORTx RESET */
#define SFR_OHCIICR_ARIE (0x1u << 4) /**< \brief (SFR_OHCIICR) OHCI Asynchronous Resume Interrupt Enable */
#define SFR_OHCIICR_APPSTART (0x1u << 5) /**< \brief (SFR_OHCIICR) Reserved */
#define SFR_OHCIICR_SUSPEND_A (0x1u << 8) /**< \brief (SFR_OHCIICR) USB PORT A */
#define SFR_OHCIICR_SUSPEND_B (0x1u << 9) /**< \brief (SFR_OHCIICR)  */
#define SFR_OHCIICR_SUSPEND_C (0x1u << 10) /**< \brief (SFR_OHCIICR) USB PORT C */
#define SFR_OHCIICR_UDPPUDIS (0x1u << 23) /**< \brief (SFR_OHCIICR) USB DEVICE PULL-UP DISABLE */
#define SFR_OHCIICR_HSICSEL (0x1u << 27) /**< \brief (SFR_OHCIICR) USB HSIC SELECT */
/* -------- SFR_OHCIISR : (SFR Offset: 0x14) OHCI Interrupt Status Register -------- */
#define SFR_OHCIISR_RIS0 (0x1u << 0) /**< \brief (SFR_OHCIISR) OHCI Resume Interrupt Status Port 0 */
#define SFR_OHCIISR_RIS1 (0x1u << 1) /**< \brief (SFR_OHCIISR) OHCI Resume Interrupt Status Port 1 */
#define SFR_OHCIISR_RIS2 (0x1u << 2) /**< \brief (SFR_OHCIISR) OHCI Resume Interrupt Status Port 2 */
/* -------- SFR_CORTEX : (SFR Offset: 0x1C) Cortex Configuration Register -------- */
#define SFR_CORTEX_WFE (0x1u << 0) /**< \brief (SFR_CORTEX) Wait for Event Trigger */
/* -------- SFR_AHB : (SFR Offset: 0x20) AHB Configuration Register -------- */
#define SFR_AHB_PFETCH9 (0x1u << 9) /**< \brief (SFR_AHB) AHB MASTERx 9 Converter Prefetch */
#define   SFR_AHB_PFETCH9_INCR4 (0x0u << 9) /**< \brief (SFR_AHB) INCR undefined burst converted to burst of 4 beats. */
#define   SFR_AHB_PFETCH9_INCR8 (0x1u << 9) /**< \brief (SFR_AHB) INCR undefined burst converted to burst of 8 beats. */
#define SFR_AHB_PFETCH12 (0x1u << 12) /**< \brief (SFR_AHB) AHB MASTERx 12 Converter Prefetch */
#define   SFR_AHB_PFETCH12_INCR4 (0x0u << 12) /**< \brief (SFR_AHB) INCR undefined burst converted to burst of 4 beats. */
#define   SFR_AHB_PFETCH12_INCR8 (0x1u << 12) /**< \brief (SFR_AHB) INCR undefined burst converted to burst of 8 beats. */
#define SFR_AHB_DLBOPT9 (0x1u << 25) /**< \brief (SFR_AHB) AHB MASTERx 9 Converter Define Length Burst Optimization */
#define SFR_AHB_DLBOPT12 (0x1u << 28) /**< \brief (SFR_AHB) AHB MASTERx 12 Converter Define Length Burst Optimization */
/* -------- SFR_BRIDGE : (SFR Offset: 0x24) Bridge Configuration Register -------- */
#define SFR_BRIDGE_AXI2AHBSEL (0x1u << 8) /**< \brief (SFR_BRIDGE) AXI to AHB Bridge for DDR Controller Selection */
#define   SFR_BRIDGE_AXI2AHBSEL_SINGLE (0x0u << 8) /**< \brief (SFR_BRIDGE) Uses single port bridge. */
#define   SFR_BRIDGE_AXI2AHBSEL_DUAL (0x1u << 8) /**< \brief (SFR_BRIDGE) Uses dual port bridge. */
#define SFR_BRIDGE_CA5QWR (0x1u << 12) /**< \brief (SFR_BRIDGE) AXI to AHB 2Ports Bridge for DDR Controller Quick Write Response */
#define SFR_BRIDGE_CA5RESP (0x1u << 13) /**< \brief (SFR_BRIDGE) AXI to AHB 2Ports Bridge for DDR Controller ARREADY ASAP */
/* -------- SFR_SECURE : (SFR Offset: 0x28) Security Configuration Register -------- */
#define SFR_SECURE_ROM (0x1u << 0) /**< \brief (SFR_SECURE) Disable Access to ROM Code */
#define SFR_SECURE_FUSE (0x1u << 8) /**< \brief (SFR_SECURE) Disable Access to Fuse Controller */
/* -------- SFR_UTMICKTRIM : (SFR Offset: 0x30) UTMI Clock Trimming Register -------- */
#define SFR_UTMICKTRIM_FREQ_Pos 0
#define SFR_UTMICKTRIM_FREQ_Msk (0x3u << SFR_UTMICKTRIM_FREQ_Pos) /**< \brief (SFR_UTMICKTRIM) UTMI Reference Clock Frequency */
#define   SFR_UTMICKTRIM_FREQ_12 (0x0u << 0) /**< \brief (SFR_UTMICKTRIM) 12 MHz reference clock */
#define   SFR_UTMICKTRIM_FREQ_16 (0x1u << 0) /**< \brief (SFR_UTMICKTRIM) 16 MHz reference clock */
#define   SFR_UTMICKTRIM_FREQ_24 (0x2u << 0) /**< \brief (SFR_UTMICKTRIM) 24 MHz reference clock */
#define   SFR_UTMICKTRIM_FREQ_48 (0x3u << 0) /**< \brief (SFR_UTMICKTRIM) 48 MHz reference clock */
#define SFR_UTMICKTRIM_VBG_Pos 16
#define SFR_UTMICKTRIM_VBG_Msk (0xfu << SFR_UTMICKTRIM_VBG_Pos) /**< \brief (SFR_UTMICKTRIM) UTMI Band Gap Voltage Trimming */
#define SFR_UTMICKTRIM_VBG(value) ((SFR_UTMICKTRIM_VBG_Msk & ((value) << SFR_UTMICKTRIM_VBG_Pos)))
/* -------- SFR_UTMIHSTRIM : (SFR Offset: 0x34) UTMI High Speed Trimming Register -------- */
#define SFR_UTMIHSTRIM_SQUELCH_Pos 0
#define SFR_UTMIHSTRIM_SQUELCH_Msk (0x7u << SFR_UTMIHSTRIM_SQUELCH_Pos) /**< \brief (SFR_UTMIHSTRIM) UTMI HS SQUELCH Voltage Trimming */
#define SFR_UTMIHSTRIM_SQUELCH(value) ((SFR_UTMIHSTRIM_SQUELCH_Msk & ((value) << SFR_UTMIHSTRIM_SQUELCH_Pos)))
#define SFR_UTMIHSTRIM_DISC_Pos 4
#define SFR_UTMIHSTRIM_DISC_Msk (0x7u << SFR_UTMIHSTRIM_DISC_Pos) /**< \brief (SFR_UTMIHSTRIM) UTMI Disconnect Voltage Trimming */
#define SFR_UTMIHSTRIM_DISC(value) ((SFR_UTMIHSTRIM_DISC_Msk & ((value) << SFR_UTMIHSTRIM_DISC_Pos)))
#define SFR_UTMIHSTRIM_SLOPE0_Pos 8
#define SFR_UTMIHSTRIM_SLOPE0_Msk (0x7u << SFR_UTMIHSTRIM_SLOPE0_Pos) /**< \brief (SFR_UTMIHSTRIM) UTMI HS PORTx Transceiver Slope Trimming */
#define SFR_UTMIHSTRIM_SLOPE0(value) ((SFR_UTMIHSTRIM_SLOPE0_Msk & ((value) << SFR_UTMIHSTRIM_SLOPE0_Pos)))
#define SFR_UTMIHSTRIM_SLOPE1_Pos 12
#define SFR_UTMIHSTRIM_SLOPE1_Msk (0x7u << SFR_UTMIHSTRIM_SLOPE1_Pos) /**< \brief (SFR_UTMIHSTRIM) UTMI HS PORTx Transceiver Slope Trimming */
#define SFR_UTMIHSTRIM_SLOPE1(value) ((SFR_UTMIHSTRIM_SLOPE1_Msk & ((value) << SFR_UTMIHSTRIM_SLOPE1_Pos)))
#define SFR_UTMIHSTRIM_SLOPE2_Pos 16
#define SFR_UTMIHSTRIM_SLOPE2_Msk (0x7u << SFR_UTMIHSTRIM_SLOPE2_Pos) /**< \brief (SFR_UTMIHSTRIM) UTMI HS PORTx Transceiver Slope Trimming */
#define SFR_UTMIHSTRIM_SLOPE2(value) ((SFR_UTMIHSTRIM_SLOPE2_Msk & ((value) << SFR_UTMIHSTRIM_SLOPE2_Pos)))
/* -------- SFR_UTMIFSTRIM : (SFR Offset: 0x38) UTMI Full Speed Trimming Register -------- */
#define SFR_UTMIFSTRIM_RISE_Pos 0
#define SFR_UTMIFSTRIM_RISE_Msk (0x7u << SFR_UTMIFSTRIM_RISE_Pos) /**< \brief (SFR_UTMIFSTRIM) FS Transceiver Output Rising Slope Trimming */
#define SFR_UTMIFSTRIM_RISE(value) ((SFR_UTMIFSTRIM_RISE_Msk & ((value) << SFR_UTMIFSTRIM_RISE_Pos)))
#define SFR_UTMIFSTRIM_FALL_Pos 4
#define SFR_UTMIFSTRIM_FALL_Msk (0x7u << SFR_UTMIFSTRIM_FALL_Pos) /**< \brief (SFR_UTMIFSTRIM) FS Transceiver Output Falling Slope Trimming */
#define SFR_UTMIFSTRIM_FALL(value) ((SFR_UTMIFSTRIM_FALL_Msk & ((value) << SFR_UTMIFSTRIM_FALL_Pos)))
#define SFR_UTMIFSTRIM_XCVR_Pos 8
#define SFR_UTMIFSTRIM_XCVR_Msk (0x3u << SFR_UTMIFSTRIM_XCVR_Pos) /**< \brief (SFR_UTMIFSTRIM) FS Transceiver Crossover Voltage Trimming */
#define SFR_UTMIFSTRIM_XCVR(value) ((SFR_UTMIFSTRIM_XCVR_Msk & ((value) << SFR_UTMIFSTRIM_XCVR_Pos)))
#define SFR_UTMIFSTRIM_ZN_Pos 16
#define SFR_UTMIFSTRIM_ZN_Msk (0x7u << SFR_UTMIFSTRIM_ZN_Pos) /**< \brief (SFR_UTMIFSTRIM) FS Transceiver NMOS Impedance Trimming */
#define SFR_UTMIFSTRIM_ZN(value) ((SFR_UTMIFSTRIM_ZN_Msk & ((value) << SFR_UTMIFSTRIM_ZN_Pos)))
#define SFR_UTMIFSTRIM_ZP_Pos 20
#define SFR_UTMIFSTRIM_ZP_Msk (0x7u << SFR_UTMIFSTRIM_ZP_Pos) /**< \brief (SFR_UTMIFSTRIM) FS Transceiver PMOS Impedance Trimming */
#define SFR_UTMIFSTRIM_ZP(value) ((SFR_UTMIFSTRIM_ZP_Msk & ((value) << SFR_UTMIFSTRIM_ZP_Pos)))
/* -------- SFR_UTMISWAP : (SFR Offset: 0x3C) UTMI DP/DM Pin Swapping Register -------- */
#define SFR_UTMISWAP_PORT0 (0x1u << 0) /**< \brief (SFR_UTMISWAP) PORT 0 DP/DM Pin Swapping */
#define   SFR_UTMISWAP_PORT0_NORMAL (0x0u << 0) /**< \brief (SFR_UTMISWAP) DP/DM normal pinout. */
#define   SFR_UTMISWAP_PORT0_SWAPPED (0x1u << 0) /**< \brief (SFR_UTMISWAP) DP/DM swapped pinout. */
#define SFR_UTMISWAP_PORT1 (0x1u << 1) /**< \brief (SFR_UTMISWAP) PORT 1 DP/DM Pin Swapping */
#define   SFR_UTMISWAP_PORT1_NORMAL (0x0u << 1) /**< \brief (SFR_UTMISWAP) DP/DM normal pinout. */
#define   SFR_UTMISWAP_PORT1_SWAPPED (0x1u << 1) /**< \brief (SFR_UTMISWAP) DP/DM swapped pinout. */
#define SFR_UTMISWAP_PORT2 (0x1u << 2) /**< \brief (SFR_UTMISWAP) PORT 2 DP/DM Pin Swapping */
#define   SFR_UTMISWAP_PORT2_NORMAL (0x0u << 2) /**< \brief (SFR_UTMISWAP) DP/DM normal pinout. */
#define   SFR_UTMISWAP_PORT2_SWAPPED (0x1u << 2) /**< \brief (SFR_UTMISWAP) DP/DM swapped pinout. */
/* -------- SFR_EBICFG : (SFR Offset: 0x40) EBI Configuration Register -------- */
#define SFR_EBICFG_BMS (0x1u << 16) /**< \brief (SFR_EBICFG) BMS Sampled Value (Read Only) */
#define   SFR_EBICFG_BMS_ROM (0x0u << 16) /**< \brief (SFR_EBICFG) Boot on ROM. */
#define   SFR_EBICFG_BMS_EBI (0x1u << 16) /**< \brief (SFR_EBICFG) Boot on EBI. */
/* -------- SFR_ANACFG : (SFR Offset: 0x44) Analog Configuration Register -------- */
#define SFR_ANACFG_SM_DDR_EN (0x1u << 0) /**< \brief (SFR_ANACFG) DDR Supply Monitor Enable */
/* -------- SFR_CAN : (SFR Offset: 0x48) CAN memories address based Register -------- */
#define SFR_CAN_EXT_MEM_CAN0_ADDR_Pos 0
#define SFR_CAN_EXT_MEM_CAN0_ADDR_Msk (0xffffu << SFR_CAN_EXT_MEM_CAN0_ADDR_Pos) /**< \brief (SFR_CAN)  */
#define SFR_CAN_EXT_MEM_CAN0_ADDR(value) ((SFR_CAN_EXT_MEM_CAN0_ADDR_Msk & ((value) << SFR_CAN_EXT_MEM_CAN0_ADDR_Pos)))
#define SFR_CAN_EXT_MEM_CAN1_ADDR_Pos 16
#define SFR_CAN_EXT_MEM_CAN1_ADDR_Msk (0xffffu << SFR_CAN_EXT_MEM_CAN1_ADDR_Pos) /**< \brief (SFR_CAN)  */
#define SFR_CAN_EXT_MEM_CAN1_ADDR(value) ((SFR_CAN_EXT_MEM_CAN1_ADDR_Msk & ((value) << SFR_CAN_EXT_MEM_CAN1_ADDR_Pos)))
/* -------- SFR_SN0 : (SFR Offset: 0x4C) Serial Number 0 Register -------- */
#define SFR_SN0_SN0_Pos 0
#define SFR_SN0_SN0_Msk (0xffffffffu << SFR_SN0_SN0_Pos) /**< \brief (SFR_SN0) Serial Number 0 */
/* -------- SFR_SN1 : (SFR Offset: 0x50) Seriel Number 1 Register -------- */
#define SFR_SN1_SN1_Pos 0
#define SFR_SN1_SN1_Msk (0xffffffffu << SFR_SN1_SN1_Pos) /**< \brief (SFR_SN1) Serial Number 1 */
/* -------- SFR_AICREDIR : (SFR Offset: 0x54) AIC interrupt Redirection Register -------- */
#define SFR_AICREDIR_NSAIC (0x1u << 0) /**< \brief (SFR_AICREDIR) Interrupt redirection to Non-Secure AIC */
#define SFR_AICREDIR_AICREDIRKEY_Pos 1
#define SFR_AICREDIR_AICREDIRKEY_Msk (0x7fffffffu << SFR_AICREDIR_AICREDIRKEY_Pos) /**< \brief (SFR_AICREDIR) Unlock Key */
#define SFR_AICREDIR_AICREDIRKEY(value) ((SFR_AICREDIR_AICREDIRKEY_Msk & ((value) << SFR_AICREDIR_AICREDIRKEY_Pos)))
/* -------- SFR_L2CC_HRAMC : (SFR Offset: 0x58) L2CC_HRAMC1 -------- */
#define SFR_L2CC_HRAMC_SRAM_SEL (0x1u << 0) /**< \brief (SFR_L2CC_HRAMC)  */
/* -------- SFR_RM0 : (SFR Offset: 0x5C) ReadMargin0 Register -------- */
#define SFR_RM0_RM0_Pos 0
#define SFR_RM0_RM0_Msk (0xfu << SFR_RM0_RM0_Pos) /**< \brief (SFR_RM0) READMARGIN value: i_ahb_sram - 128K - sadslspkb1p16384x32m16b2w1cp0d0t0 */
#define SFR_RM0_RM0(value) ((SFR_RM0_RM0_Msk & ((value) << SFR_RM0_RM0_Pos)))
#define SFR_RM0_RME0 (0x1u << 4) /**< \brief (SFR_RM0) READMARGIN Enable: */
#define SFR_RM0_RM1_Pos 5
#define SFR_RM0_RM1_Msk (0xfu << SFR_RM0_RM1_Pos) /**< \brief (SFR_RM0) READMARGIN value: i_rom8192x64_sys - 64Kb system ROM - ulp1mrom8192x64cm16 */
#define SFR_RM0_RM1(value) ((SFR_RM0_RM1_Msk & ((value) << SFR_RM0_RM1_Pos)))
#define SFR_RM0_RME1 (0x1u << 9) /**< \brief (SFR_RM0) READMARGIN Enable: */
#define SFR_RM0_RM2_Pos 10
#define SFR_RM0_RM2_Msk (0xfu << SFR_RM0_RM2_Pos) /**< \brief (SFR_RM0) READMARGIN value: 0 i_rom12288x64_ecc - 96Kb system ROM - ulp1mrom12288x64cm16 */
#define SFR_RM0_RM2(value) ((SFR_RM0_RM2_Msk & ((value) << SFR_RM0_RM2_Pos)))
#define SFR_RM0_RME2 (0x1u << 14) /**< \brief (SFR_RM0) READMARGIN Enable: */
#define SFR_RM0_RM3_Pos 15
#define SFR_RM0_RM3_Msk (0xfu << SFR_RM0_RM3_Pos) /**< \brief (SFR_RM0) READMARGIN value: i_non_erase_securam - 1Kb RAM - sadslspkb1p128x72m4b1w1cp0d0t0 */
#define SFR_RM0_RM3(value) ((SFR_RM0_RM3_Msk & ((value) << SFR_RM0_RM3_Pos)))
#define SFR_RM0_RME3 (0x1u << 19) /**< \brief (SFR_RM0) READMARGIN Enable: */
#define SFR_RM0_RM4_Pos 20
#define SFR_RM0_RM4_Msk (0xfu << SFR_RM0_RM4_Pos) /**< \brief (SFR_RM0) READMARGIN value: i_erased_securam - 4Kb RAM - sadslspkb1p512x72m4b1w1cp0d0t0 */
#define SFR_RM0_RM4(value) ((SFR_RM0_RM4_Msk & ((value) << SFR_RM0_RM4_Pos)))
#define SFR_RM0_RME4 (0x1u << 24) /**< \brief (SFR_RM0) READMARGIN Enable: */
#define SFR_RM0_RM5_Pos 25
#define SFR_RM0_RM5_Msk (0xfu << SFR_RM0_RM5_Pos) /**< \brief (SFR_RM0) i_daram_bist - UHPHS - adrlspkb1p512x64cm4sw1 */
#define SFR_RM0_RM5(value) ((SFR_RM0_RM5_Msk & ((value) << SFR_RM0_RM5_Pos)))
#define SFR_RM0_RME5 (0x1u << 29) /**< \brief (SFR_RM0) READMARGIN Enable: */
/* -------- SFR_RM1 : (SFR Offset: 0x60) ReadMargin1 Register -------- */
#define SFR_RM1_RM6_Pos 0
#define SFR_RM1_RM6_Msk (0xfu << SFR_RM1_RM6_Pos) /**< \brief (SFR_RM1) READMARGIN value:  i_descram_bist - UHPHS - adrlspkb1p68x32cm2sw1 */
#define SFR_RM1_RM6(value) ((SFR_RM1_RM6_Msk & ((value) << SFR_RM1_RM6_Pos)))
#define SFR_RM1_RME6 (0x1u << 4) /**< \brief (SFR_RM1) READMARGIN Enable: */
#define SFR_RM1_RM7_Pos 5
#define SFR_RM1_RM7_Msk (0xfu << SFR_RM1_RM7_Pos) /**< \brief (SFR_RM1) READMARGIN value: i_sram0 ,i_sram1 - HSMC5 - sadslspkb1p1152x32m8b1w1cp0d0t0 */
#define SFR_RM1_RM7(value) ((SFR_RM1_RM7_Msk & ((value) << SFR_RM1_RM7_Pos)))
#define SFR_RM1_RME7 (0x1u << 9) /**< \brief (SFR_RM1) READMARGIN Enable: */
#define SFR_RM1_RM8_Pos 10
#define SFR_RM1_RM8_Msk (0xfu << SFR_RM1_RM8_Pos) /**< \brief (SFR_RM1) READMARGIN value: i_lcd_heo_cue0_sram,i_lcd_heo_cue1_sram - HLCD5 - */
#define SFR_RM1_RM8(value) ((SFR_RM1_RM8_Msk & ((value) << SFR_RM1_RM8_Pos)))
#define SFR_RM1_RME8 (0x1u << 14) /**< \brief (SFR_RM1) READMARGIN Enable: */
#define SFR_RM1_RM9_Pos 15
#define SFR_RM1_RM9_Msk (0xfu << SFR_RM1_RM9_Pos) /**< \brief (SFR_RM1) READMARGIN value: i_lcd_heo_scaler0/1/2_sram -  sadslspkb1p1024x16m4b1w1cp0d0t0 - HLCDC5 */
#define SFR_RM1_RM9(value) ((SFR_RM1_RM9_Msk & ((value) << SFR_RM1_RM9_Pos)))
#define SFR_RM1_RME9 (0x1u << 19) /**< \brief (SFR_RM1) READMARGIN Enable: */
#define SFR_RM1_RM10_Pos 20
#define SFR_RM1_RM10_Msk (0xfu << SFR_RM1_RM10_Pos) /**< \brief (SFR_RM1) READMARGIN value: i_lcd_heo_sram,i_lcd_base_sram,i_lcd_ovr1_sram,i_lcd_ovr2_sram - HLCD5 - asdrlspkb2p16x64cm1sw1 */
#define SFR_RM1_RM10(value) ((SFR_RM1_RM10_Msk & ((value) << SFR_RM1_RM10_Pos)))
#define SFR_RM1_RME10 (0x1u << 24) /**< \brief (SFR_RM1) READMARGIN Enable: */
#define SFR_RM1_RM11_Pos 25
#define SFR_RM1_RM11_Msk (0xfu << SFR_RM1_RM11_Pos) /**< \brief (SFR_RM1) READMARGIN value: i_hxisi_cfa_sram 115 - CFA SPRAM - sadslspkb1p2624x12m16b1w1cp0d0t0 */
#define SFR_RM1_RM11(value) ((SFR_RM1_RM11_Msk & ((value) << SFR_RM1_RM11_Pos)))
#define SFR_RM1_RME11 (0x1u << 29) /**< \brief (SFR_RM1) READMARGIN Enable: */
/* -------- SFR_RM2 : (SFR Offset: 0x64) ReadMargin2 Register -------- */
#define SFR_RM2_RM12_Pos 0
#define SFR_RM2_RM12_Msk (0xfu << SFR_RM2_RM12_Pos) /**< \brief (SFR_RM2) READMARGIN value: i_hxisi_sub420_sram - SUB420 - sadslspkb1p1312x20m8b1w1cp0d0t0 */
#define SFR_RM2_RM12(value) ((SFR_RM2_RM12_Msk & ((value) << SFR_RM2_RM12_Pos)))
#define SFR_RM2_RME12 (0x1u << 4) /**< \brief (SFR_RM2) READMARGIN Enable: */
#define SFR_RM2_RM13_Pos 5
#define SFR_RM2_RM13_Msk (0xfu << SFR_RM2_RM13_Pos) /**< \brief (SFR_RM2) READMARGIN value: u_data_ram_lsb0/1,  u_data_ram_msb0/1 - Data L2 Cache RAMS - sram4kx6 */
#define SFR_RM2_RM13(value) ((SFR_RM2_RM13_Msk & ((value) << SFR_RM2_RM13_Pos)))
#define SFR_RM2_RME13 (0x1u << 9) /**< \brief (SFR_RM2) READMARGIN Enable: */
#define SFR_RM2_RM14_Pos 10
#define SFR_RM2_RM14_Msk (0x1fu << SFR_RM2_RM14_Pos) /**< \brief (SFR_RM2) READMARGIN value: u_tag_ram0-7 - Tag L2 Cache RAMs - sram512x21 */
#define SFR_RM2_RM14(value) ((SFR_RM2_RM14_Msk & ((value) << SFR_RM2_RM14_Pos)))
#define SFR_RM2_RM15_Pos 15
#define SFR_RM2_RM15_Msk (0xfu << SFR_RM2_RM15_Pos) /**< \brief (SFR_RM2) READMARGIN value:  u_ddata_bank0-3 - Data Cache TLB RAMs - hsspsram_2048x32 */
#define SFR_RM2_RM15(value) ((SFR_RM2_RM15_Msk & ((value) << SFR_RM2_RM15_Pos)))
#define SFR_RM2_RME15 (0x1u << 19) /**< \brief (SFR_RM2) READMARGIN Enable: */
#define SFR_RM2_RM16_Pos 20
#define SFR_RM2_RM16_Msk (0xfu << SFR_RM2_RM16_Pos) /**< \brief (SFR_RM2) READMARGIN value: u_idata_bank0-1  u_idata_bank0-1 - Instruction Cache TLB RAMs -hsspsram_2048x72 */
#define SFR_RM2_RM16(value) ((SFR_RM2_RM16_Msk & ((value) << SFR_RM2_RM16_Pos)))
#define SFR_RM2_RME16 (0x1u << 24) /**< \brief (SFR_RM2) READMARGIN Enable: */
#define SFR_RM2_RM17_Pos 25
#define SFR_RM2_RM17_Msk (0xfu << SFR_RM2_RM17_Pos) /**< \brief (SFR_RM2) READMARGIN value:  u_ddirty_ram - Data Cache Dirty bits RAM - hs1prf_256x12 */
#define SFR_RM2_RM17(value) ((SFR_RM2_RM17_Msk & ((value) << SFR_RM2_RM17_Pos)))
#define SFR_RM2_RME17 (0x1u << 29) /**< \brief (SFR_RM2) READMARGIN Enable: */
/* -------- SFR_RM3 : (SFR Offset: 0x68) ReadMargin3 Register -------- */
#define SFR_RM3_RM18_Pos 0
#define SFR_RM3_RM18_Msk (0xfu << SFR_RM3_RM18_Pos) /**< \brief (SFR_RM3) READMARGIN value:  u_itag_ram0/1_up,  u_itag_ram0/1_down - Instruction Cache Data RAMs - hs1prf_256x24 */
#define SFR_RM3_RM18(value) ((SFR_RM3_RM18_Msk & ((value) << SFR_RM3_RM18_Pos)))
#define SFR_RM3_RME18 (0x1u << 4) /**< \brief (SFR_RM3) READMARGIN Enable: */
#define SFR_RM3_RM19_Pos 5
#define SFR_RM3_RM19_Msk (0xfu << SFR_RM3_RM19_Pos) /**< \brief (SFR_RM3) RM31: READMARGIN valuie:  u_dtag_bank0-3 - Data Cache Tag RAMs - hs1prf_256x26 */
#define SFR_RM3_RM19(value) ((SFR_RM3_RM19_Msk & ((value) << SFR_RM3_RM19_Pos)))
#define SFR_RM3_RME19 (0x1u << 9) /**< \brief (SFR_RM3) READMARGIN Enable: */
#define SFR_RM3_RM20_Pos 10
#define SFR_RM3_RM20_Msk (0xfu << SFR_RM3_RM20_Pos) /**< \brief (SFR_RM3) u_tlb_bank0-1 - Cache TLB RAMs - hs1prf_64x63 */
#define SFR_RM3_RM20(value) ((SFR_RM3_RM20_Msk & ((value) << SFR_RM3_RM20_Pos)))
#define SFR_RM3_RME20 (0x1u << 14) /**< \brief (SFR_RM3) READMARGIN Enable: */
#define SFR_RM3_RM21_Pos 15
#define SFR_RM3_RM21_Msk (0xfu << SFR_RM3_RM21_Pos) /**< \brief (SFR_RM3) READMARGIN value: U_PICORAM - AVR16 CODE/DATA RAM - ptc_sadslspkb1p4096x32m8b1w1cp0d0t0 */
#define SFR_RM3_RM21(value) ((SFR_RM3_RM21_Msk & ((value) << SFR_RM3_RM21_Pos)))
#define SFR_RM3_RME21 (0x1u << 19) /**< \brief (SFR_RM3) READMARGIN Enable: */
#define SFR_RM3_RM22_Pos 20
#define SFR_RM3_RM22_Msk (0xfu << SFR_RM3_RM22_Pos) /**< \brief (SFR_RM3) READMARGIN value: U_MAILBOX - MAILBOX RAM - ptc_sadslspkb1p1024x32m4b1w1cp0d0t0 */
#define SFR_RM3_RM22(value) ((SFR_RM3_RM22_Msk & ((value) << SFR_RM3_RM22_Pos)))
#define SFR_RM3_RME22 (0x1u << 24) /**< \brief (SFR_RM3) READMARGIN Enable: */
/* -------- SFR_RM4 : (SFR Offset: 0x6C) ReadMargin4 Register -------- */
#define SFR_RM4_RMA_DP0_Pos 0
#define SFR_RM4_RMA_DP0_Msk (0xfu << SFR_RM4_RMA_DP0_Pos) /**< \brief (SFR_RM4) READMARGIN value: i_hsdhc0/i_hsdhc1 - HSDHC0/HSDHC0 buffer - sadslspkb2p128x64m4b1w1cp0d00 */
#define SFR_RM4_RMA_DP0(value) ((SFR_RM4_RMA_DP0_Msk & ((value) << SFR_RM4_RMA_DP0_Pos)))
#define SFR_RM4_RMB_DP0_Pos 4
#define SFR_RM4_RMB_DP0_Msk (0xfu << SFR_RM4_RMB_DP0_Pos) /**< \brief (SFR_RM4) READMARGIN value: i_hsdhc0/i_hsdhc1 - HSDHC0/HSDHC0 buffer - sadslspkb2p128x64m4b1w1cp0d00 */
#define SFR_RM4_RMB_DP0(value) ((SFR_RM4_RMB_DP0_Msk & ((value) << SFR_RM4_RMB_DP0_Pos)))
#define SFR_RM4_RME_DP0 (0x1u << 8) /**< \brief (SFR_RM4) READMARGIN Enable: */
/* -------- SFR_RM5 : (SFR Offset: 0x70) ReadMargin5 Register -------- */
#define SFR_RM5_RMA_DP1_Pos 0
#define SFR_RM5_RMA_DP1_Msk (0xfu << SFR_RM5_RMA_DP1_Pos) /**< \brief (SFR_RM5) READMARGIN value: i_dpram2kx32  - UDPHS / GMACTX DPRAM  - sadslspkb2p2048x32m8b1w1cp0d0t0 */
#define SFR_RM5_RMA_DP1(value) ((SFR_RM5_RMA_DP1_Msk & ((value) << SFR_RM5_RMA_DP1_Pos)))
#define SFR_RM5_RMB_DP1_Pos 4
#define SFR_RM5_RMB_DP1_Msk (0xfu << SFR_RM5_RMB_DP1_Pos) /**< \brief (SFR_RM5) READMARGIN value: i_dpram2kx32  - UDPHS / GMACTX DPRAM  - sadslspkb2p2048x32m8b1w1cp0d0t0 */
#define SFR_RM5_RMB_DP1(value) ((SFR_RM5_RMB_DP1_Msk & ((value) << SFR_RM5_RMB_DP1_Pos)))
#define SFR_RM5_RME_DP1 (0x1u << 8) /**< \brief (SFR_RM5) READMARGIN Enable: */
#define SFR_RM5_RMA_DP2_Pos 9
#define SFR_RM5_RMA_DP2_Msk (0xfu << SFR_RM5_RMA_DP2_Pos) /**< \brief (SFR_RM5) READMARGIN value: i_txdpram - GMAC RX DPRAM - sadslspkb2p1024x32m8b1w1cp0d0t0 */
#define SFR_RM5_RMA_DP2(value) ((SFR_RM5_RMA_DP2_Msk & ((value) << SFR_RM5_RMA_DP2_Pos)))
#define SFR_RM5_RMB_DP2_Pos 13
#define SFR_RM5_RMB_DP2_Msk (0x7u << SFR_RM5_RMB_DP2_Pos) /**< \brief (SFR_RM5) READMARGIN value: i_txdpram - GMAC RX DPRAM - sadslspkb2p1024x32m8b1w1cp0d0t0 */
#define SFR_RM5_RMB_DP2(value) ((SFR_RM5_RMB_DP2_Msk & ((value) << SFR_RM5_RMB_DP2_Pos)))
#define SFR_RM5_RME_DP2 (0x1u << 17) /**< \brief (SFR_RM5) READMARGIN Enable: */
#define SFR_RM5_RMA_DP3_Pos 18
#define SFR_RM5_RMA_DP3_Msk (0xfu << SFR_RM5_RMA_DP3_Pos) /**< \brief (SFR_RM5) READMARGIN value: i_dpram528x64 - HXDMA0/HXDMA1 - sadslspkb2p528x64m4b1w1cp0d0t0 */
#define SFR_RM5_RMA_DP3(value) ((SFR_RM5_RMA_DP3_Msk & ((value) << SFR_RM5_RMA_DP3_Pos)))
#define SFR_RM5_RMB_DP3_Pos 22
#define SFR_RM5_RMB_DP3_Msk (0xfu << SFR_RM5_RMB_DP3_Pos) /**< \brief (SFR_RM5) READMARGIN value: i_dpram528x64 - HXDMA0/HXDMA1 - sadslspkb2p528x64m4b1w1cp0d0t0 */
#define SFR_RM5_RMB_DP3(value) ((SFR_RM5_RMB_DP3_Msk & ((value) << SFR_RM5_RMB_DP3_Pos)))
#define SFR_RM5_RME_DP3 (0x1u << 26) /**< \brief (SFR_RM5) READMARGIN Enable: */
/* -------- SFR_RM6 : (SFR Offset: 0x74) ReadMargin6 Register -------- */
#define SFR_RM6_RMB_DP4_Pos 0
#define SFR_RM6_RMB_DP4_Msk (0xfu << SFR_RM6_RMB_DP4_Pos) /**< \brief (SFR_RM6) READMARGIN value: i_lcd_base_rf2p,i_lcd_ovr1_rf2p,i_lcd_ovr1_rf2p, i_lcd_heo_rf2p, i_lcd_heop1_rf2p , i_lcd_heop2_rf2p - HLCD5 - asdrlspkb2p32x67cm1sw1 */
#define SFR_RM6_RMB_DP4(value) ((SFR_RM6_RMB_DP4_Msk & ((value) << SFR_RM6_RMB_DP4_Pos)))
#define SFR_RM6_RME_DP4 (0x1u << 8) /**< \brief (SFR_RM6) READMARGIN Enable: */
#define SFR_RM6_RMB_DP5_Pos 9
#define SFR_RM6_RMB_DP5_Msk (0xfu << SFR_RM6_RMB_DP5_Pos) /**< \brief (SFR_RM6) READMARGIN value:  i_lcd_output_fifo - HCLCD5 - asdrlspkb2p1024x24cm4sw1 */
#define SFR_RM6_RMB_DP5(value) ((SFR_RM6_RMB_DP5_Msk & ((value) << SFR_RM6_RMB_DP5_Pos)))
#define SFR_RM6_RME_DP5 (0x1u << 17) /**< \brief (SFR_RM6) READMARGIN Enable: */
#define SFR_RM6_RMB_DP6_Pos 18
#define SFR_RM6_RMB_DP6_Msk (0xfu << SFR_RM6_RMB_DP6_Pos) /**< \brief (SFR_RM6) READMARGIN value: i_lcd_pp_fifo - HLCD5 - asdrlspkb2p16x64cm1w1 */
#define SFR_RM6_RMB_DP6(value) ((SFR_RM6_RMB_DP6_Msk & ((value) << SFR_RM6_RMB_DP6_Pos)))
#define SFR_RM6_RME_DP6 (0x1u << 26) /**< \brief (SFR_RM6) READMARGIN Enable: */
/* -------- SFR_RM7 : (SFR Offset: 0x78) ReadMargin7 Register -------- */
#define SFR_RM7_RMB_DP9_Pos 0
#define SFR_RM7_RMB_DP9_Msk (0xfu << SFR_RM7_RMB_DP9_Pos) /**< \brief (SFR_RM7) i_hxisi_his_rf2p - HIS DPRAM - asdrlspkb2p512x20cm4sw1 */
#define SFR_RM7_RMB_DP9(value) ((SFR_RM7_RMB_DP9_Msk & ((value) << SFR_RM7_RMB_DP9_Pos)))
#define SFR_RM7_RME_DP9 (0x1u << 8) /**< \brief (SFR_RM7) READMARGIN Enable: */
#define SFR_RM7_RMB_DP10_Pos 9
#define SFR_RM7_RMB_DP10_Msk (0xfu << SFR_RM7_RMB_DP10_Pos) /**< \brief (SFR_RM7) READMARGIN value: i_hxisi_cfa_sram - sadslspkb1p2624x12m16b1w1cp0d0t0  - CFA(color Filter Array) Single Port RAM */
#define SFR_RM7_RMB_DP10(value) ((SFR_RM7_RMB_DP10_Msk & ((value) << SFR_RM7_RMB_DP10_Pos)))
#define SFR_RM7_RME_DP10 (0x1u << 17) /**< \brief (SFR_RM7) READMARGIN Enable: */
#define SFR_RM7_RMB_DP11_Pos 18
#define SFR_RM7_RMB_DP11_Msk (0xfu << SFR_RM7_RMB_DP11_Pos) /**< \brief (SFR_RM7) READMARGIN value: i_hxisi_mif_rf2p - MIF (Master InterFace) Dual Port register files - asdrlspkb2p34x64cm1sw1 */
#define SFR_RM7_RMB_DP11(value) ((SFR_RM7_RMB_DP11_Msk & ((value) << SFR_RM7_RMB_DP11_Pos)))
#define SFR_RM7_RME_DP11 (0x1u << 26) /**< \brief (SFR_RM7) READMARGIN Enable: */
/* -------- SFR_I2SCLKSEL : (SFR Offset: 0x90) I2S Register -------- */
#define SFR_I2SCLKSEL_CLKSEL0 (0x1u << 0) /**< \brief (SFR_I2SCLKSEL)  */
#define SFR_I2SCLKSEL_CLKSEL1 (0x1u << 1) /**< \brief (SFR_I2SCLKSEL)  */

/*@}*/

#endif /* _SAMA5D2_SFR_COMPONENT_ */
