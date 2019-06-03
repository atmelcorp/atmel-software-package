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

#ifndef _SAM9X_SFR_COMPONENT_
#define _SAM9X_SFR_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Special Function Registers */
/* ============================================================================= */
/** \addtogroup SAM9X_SFR Special Function Registers */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Sfr hardware registers */
typedef struct {
  __I  uint32_t Reserved1[1];
  __IO uint32_t SFR_CCFG_EBICSA; /**< \brief (Sfr Offset: 0x04) EBI Chip Select Register */
  __I  uint32_t Reserved2[2];
  __IO uint32_t SFR_OHCIICR;     /**< \brief (Sfr Offset: 0x10) OHCI Interrupt Configuration Register */
  __I  uint32_t SFR_OHCIISR;     /**< \brief (Sfr Offset: 0x14) OHCI Interrupt Status Register */
  __I  uint32_t Reserved3[9];
  __IO uint32_t SFR_UTMISWAP;    /**< \brief (Sfr Offset: 0x3C) UTMI DP/DM Pin Swapping Register */
  __I  uint32_t Reserved4[15];
  __IO uint32_t SFR_LS;          /**< \brief (Sfr Offset: 0x7C) Light Sleep Register */
  __I  uint32_t Reserved5[25];
  __IO uint32_t SFR_WPMR;        /**< \brief (Sfr Offset: 0xE4) Write Protection Mode Register */
} Sfr;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- SFR_CCFG_EBICSA : (SFR Offset: 0x04) EBI Chip Select Register -------- */
#define SFR_CCFG_EBICSA_EBI_CS1A (0x1u << 1) /**< \brief (SFR_CCFG_EBICSA) EBI Chip Select 1 Assignment */
#define SFR_CCFG_EBICSA_EBI_CS3A (0x1u << 3) /**< \brief (SFR_CCFG_EBICSA) EBI Chip Select 3 Assignment */
#define SFR_CCFG_EBICSA_EBI_CS4A (0x1u << 4) /**< \brief (SFR_CCFG_EBICSA) EBI Chip Select 4 Assignment */
#define SFR_CCFG_EBICSA_EBI_CS5A (0x1u << 5) /**< \brief (SFR_CCFG_EBICSA) EBI Chip Select 5 Assignment */
#define SFR_CCFG_EBICSA_EBI_DBPUC (0x1u << 8) /**< \brief (SFR_CCFG_EBICSA) EBI Data Bus Pullup Configuration */
#define SFR_CCFG_EBICSA_EBI_DBPDC (0x1u << 9) /**< \brief (SFR_CCFG_EBICSA) EBI Data Bus Pulldown Configuration */
#define SFR_CCFG_EBICSA_EBI_DRIVE (0x1u << 16) /**< \brief (SFR_CCFG_EBICSA) EBI I/O Drive Configuration */
#define SFR_CCFG_EBICSA_DQIEN_F (0x1u << 20) /**< \brief (SFR_CCFG_EBICSA) Force Analog Input Comparator Configuration */
#define SFR_CCFG_EBICSA_NFD0_ON_D16 (0x1u << 24) /**< \brief (SFR_CCFG_EBICSA) NAND Flash Databus Selection */
#define SFR_CCFG_EBICSA_DDR_MP_EN (0x1u << 25) /**< \brief (SFR_CCFG_EBICSA) DDR Multi-port Enable */
/* -------- SFR_OHCIICR : (SFR Offset: 0x10) OHCI Interrupt Configuration Register -------- */
#define SFR_OHCIICR_RES0 (0x1u << 0) /**< \brief (SFR_OHCIICR) USB PORTx Reset */
#define SFR_OHCIICR_RES1 (0x1u << 1) /**< \brief (SFR_OHCIICR) USB PORTx Reset */
#define SFR_OHCIICR_RES2 (0x1u << 2) /**< \brief (SFR_OHCIICR) USB PORTx Reset */
#define SFR_OHCIICR_ARIE (0x1u << 4) /**< \brief (SFR_OHCIICR) OHCI Asynchronous Resume Interrupt Enable */
#define SFR_OHCIICR_APPSTART (0x1u << 5) /**< \brief (SFR_OHCIICR) Reserved */
#define SFR_OHCIICR_SUSP0 (0x1u << 8) /**< \brief (SFR_OHCIICR) USB PORTx */
#define SFR_OHCIICR_SUSP1 (0x1u << 9) /**< \brief (SFR_OHCIICR) USB PORTx */
#define SFR_OHCIICR_SUSP2 (0x1u << 10) /**< \brief (SFR_OHCIICR) USB PORTx */
#define SFR_OHCIICR_UDPPUDIS (0x1u << 23) /**< \brief (SFR_OHCIICR) Reserved */
/* -------- SFR_OHCIISR : (SFR Offset: 0x14) OHCI Interrupt Status Register -------- */
#define SFR_OHCIISR_RIS0 (0x1u << 0) /**< \brief (SFR_OHCIISR) OHCI Resume Interrupt Status Port 0 */
#define SFR_OHCIISR_RIS1 (0x1u << 1) /**< \brief (SFR_OHCIISR) OHCI Resume Interrupt Status Port 1 */
#define SFR_OHCIISR_RIS2 (0x1u << 2) /**< \brief (SFR_OHCIISR) OHCI Resume Interrupt Status Port 2 */
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
/* -------- SFR_LS : (SFR Offset: 0x7C) Light Sleep Register -------- */
#define SFR_LS_LS0 (0x1u << 0) /**< \brief (SFR_LS) Light Sleep Value (GFX2D) */
#define SFR_LS_LS1 (0x1u << 1) /**< \brief (SFR_LS) Light Sleep Value (HLCDC5) */
#define SFR_LS_LS2 (0x1u << 2) /**< \brief (SFR_LS) Light Sleep Value (SDMMC) */
#define SFR_LS_LS3 (0x1u << 3) /**< \brief (SFR_LS) Light Sleep Value (HUSB) */
#define SFR_LS_LS4 (0x1u << 4) /**< \brief (SFR_LS) Light Sleep Value (HXDMA) */
#define SFR_LS_LS5 (0x1u << 5) /**< \brief (SFR_LS) Light Sleep Value (EHCI/OHCI) */
#define SFR_LS_LS6 (0x1u << 6) /**< \brief (SFR_LS) Light Sleep Value (SRAM0) */
#define SFR_LS_LS7 (0x1u << 7) /**< \brief (SFR_LS) Light Sleep Value (SRAM1 (OTPC)) */
#define SFR_LS_LS8 (0x1u << 8) /**< \brief (SFR_LS) Light Sleep Value (ROM + OTPC) */
#define SFR_LS_LS9 (0x1u << 9) /**< \brief (SFR_LS) Light Sleep Value (ARM926) */
#define SFR_LS_MEM_POWER_GATING_ULP1_EN (0x1u << 16) /**< \brief (SFR_LS) Light Sleep Value for ULP1 Power-Gated Memories */
/* -------- SFR_WPMR : (SFR Offset: 0xE4) Write Protection Mode Register -------- */
#define SFR_WPMR_WPEN (0x1u << 0) /**< \brief (SFR_WPMR) Write Protection Enable */
#define SFR_WPMR_WPKEY_Pos 8
#define SFR_WPMR_WPKEY_Msk (0xffffffu << SFR_WPMR_WPKEY_Pos) /**< \brief (SFR_WPMR) Write Protection Key */
#define SFR_WPMR_WPKEY(value) ((SFR_WPMR_WPKEY_Msk & ((value) << SFR_WPMR_WPKEY_Pos)))
#define   SFR_WPMR_WPKEY_PASSWD (0x534652u << 8) /**< \brief (SFR_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit. Always reads as 0. */

/*@}*/


#endif /* _SAM9X_SFR_COMPONENT_ */
