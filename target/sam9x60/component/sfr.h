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
  __IO uint32_t SFR_CCFG_EBICSA; /**< \brief (Sfr Offset: 0x4) EBI Chip Select Register */
  __I  uint32_t Reserved2[2];
  __IO uint32_t SFR_OHCIICR;     /**< \brief (Sfr Offset: 0x10) OHCI Interrupt Configuration Register */
  __I  uint32_t SFR_OHCIISR;     /**< \brief (Sfr Offset: 0x14) OHCI Interrupt Status Register */
  __I  uint32_t Reserved3[7];
  __IO uint32_t SFR_UTMIHSTRIM;  /**< \brief (Sfr Offset: 0x34) UTMI High-Speed Trimming Register */
  __IO uint32_t SFR_UTMIFSTRIM;  /**< \brief (Sfr Offset: 0x38) UTMI Full-Speed Trimming Register */
  __IO uint32_t SFR_UTMISWAP;    /**< \brief (Sfr Offset: 0x3C) UTMI DP/DM Pin Swapping Register */
  __I  uint32_t Reserved4[15];
  __IO uint32_t SFR_LS;          /**< \brief (Sfr Offset: 0x7C) Light Sleep Register */
  __I  uint32_t Reserved5[12];
  __IO uint32_t SFR_CAL0;            /**< \brief (Sfr Offset: 0xB0) I/O Calibration 0 Register */
  __IO uint32_t SFR_CAL1;            /**< \brief (Sfr Offset: 0xB4) I/O Calibration 1 Register */
  __I  uint32_t Reserved7[11];
  __IO uint32_t SFR_WPMR;        /**< \brief (Sfr Offset: 0xE4) Write Protection Mode Register */
} Sfr;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- SFR_CCFG_EBICSA : (SFR Offset: 0x4) EBI Chip Select Register -------- */
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
/* -------- SFR_UTMIHSTRIM : (SFR Offset: 0x34) UTMI High-Speed Trimming Register -------- */
#define SFR_UTMIHSTRIM_SLOPE0_Pos 8
#define SFR_UTMIHSTRIM_SLOPE0_Msk (0x7u << SFR_UTMIHSTRIM_SLOPE0_Pos) /**< \brief (SFR_UTMIHSTRIM) UTMI HS PORTx Transceiver Slope Trimming */
#define SFR_UTMIHSTRIM_SLOPE0(value) ((SFR_UTMIHSTRIM_SLOPE0_Msk & ((value) << SFR_UTMIHSTRIM_SLOPE0_Pos)))
#define SFR_UTMIHSTRIM_SLOPE1_Pos 12
#define SFR_UTMIHSTRIM_SLOPE1_Msk (0x7u << SFR_UTMIHSTRIM_SLOPE1_Pos) /**< \brief (SFR_UTMIHSTRIM) UTMI HS PORTx Transceiver Slope Trimming */
#define SFR_UTMIHSTRIM_SLOPE1(value) ((SFR_UTMIHSTRIM_SLOPE1_Msk & ((value) << SFR_UTMIHSTRIM_SLOPE1_Pos)))
#define SFR_UTMIHSTRIM_SLOPE2_Pos 16
#define SFR_UTMIHSTRIM_SLOPE2_Msk (0x7u << SFR_UTMIHSTRIM_SLOPE2_Pos) /**< \brief (SFR_UTMIHSTRIM) UTMI HS PORTx Transceiver Slope Trimming */
#define SFR_UTMIHSTRIM_SLOPE2(value) ((SFR_UTMIHSTRIM_SLOPE2_Msk & ((value) << SFR_UTMIHSTRIM_SLOPE2_Pos)))
/* -------- SFR_UTMIFSTRIM : (SFR Offset: 0x38) UTMI Full-Speed Trimming Register -------- */
#define SFR_UTMIFSTRIM_ZN_Pos 16
#define SFR_UTMIFSTRIM_ZN_Msk (0x7u << SFR_UTMIFSTRIM_ZN_Pos) /**< \brief (SFR_UTMIFSTRIM) FS Transceiver NMOS Impedance Trimming */
#define SFR_UTMIFSTRIM_ZN(value) ((SFR_UTMIFSTRIM_ZN_Msk & ((value) << SFR_UTMIFSTRIM_ZN_Pos)))
#define SFR_UTMIFSTRIM_ZP_Pos 20
#define SFR_UTMIFSTRIM_ZP_Msk (0x7u << SFR_UTMIFSTRIM_ZP_Pos) /**< \brief (SFR_UTMIFSTRIM) FS Transceiver PMOS Impedance Trimming */
#define SFR_UTMIFSTRIM_ZP(value) ((SFR_UTMIFSTRIM_ZP_Msk & ((value) << SFR_UTMIFSTRIM_ZP_Pos)))
#define SFR_UTMIFSTRIM_ZN_CAL_Pos 24
#define SFR_UTMIFSTRIM_ZN_CAL_Msk (0x7u << SFR_UTMIFSTRIM_ZN_CAL_Pos) /**< \brief (SFR_UTMIFSTRIM) FS Transceiver NMOS Impedance Calibration */
#define SFR_UTMIFSTRIM_ZN_CAL(value) ((SFR_UTMIFSTRIM_ZN_CAL_Msk & ((value) << SFR_UTMIFSTRIM_ZN_CAL_Pos)))
#define SFR_UTMIFSTRIM_ZP_CAL_Pos 28
#define SFR_UTMIFSTRIM_ZP_CAL_Msk (0x7u << SFR_UTMIFSTRIM_ZP_CAL_Pos) /**< \brief (SFR_UTMIFSTRIM) FS Transceiver PMOS Impedance Calibration */
#define SFR_UTMIFSTRIM_ZP_CAL(value) ((SFR_UTMIFSTRIM_ZP_CAL_Msk & ((value) << SFR_UTMIFSTRIM_ZP_CAL_Pos)))
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
/* -------- SFR_CAL0 : (SFR Offset: 0xB0) I/O Calibration 0 Register -------- */
#define SFR_CAL0_CALN_P0_Pos 0
#define SFR_CAL0_CALN_P0_Msk (0xfu << SFR_CAL0_CALN_P0_Pos) /**< \brief (SFR_CAL0) Calibration of Low Level Output Impedance of Pads with VDDIOP0 Supply */
#define SFR_CAL0_CALN_P0(value) ((SFR_CAL0_CALN_P0_Msk & ((value) << SFR_CAL0_CALN_P0_Pos)))
#define SFR_CAL0_CALP_P0_Pos 4
#define SFR_CAL0_CALP_P0_Msk (0xfu << SFR_CAL0_CALP_P0_Pos) /**< \brief (SFR_CAL0) Calibration of High Level Output Impedance of Pads with VDDIOP0 Supply */
#define SFR_CAL0_CALP_P0(value) ((SFR_CAL0_CALP_P0_Msk & ((value) << SFR_CAL0_CALP_P0_Pos)))
#define SFR_CAL0_CALN_P1_Pos 8
#define SFR_CAL0_CALN_P1_Msk (0xfu << SFR_CAL0_CALN_P1_Pos) /**< \brief (SFR_CAL0) Calibration of Low Level Output Impedance of Pads with VDDIOP1 Supply */
#define SFR_CAL0_CALN_P1(value) ((SFR_CAL0_CALN_P1_Msk & ((value) << SFR_CAL0_CALN_P1_Pos)))
#define SFR_CAL0_CALP_P1_Pos 12
#define SFR_CAL0_CALP_P1_Msk (0xfu << SFR_CAL0_CALP_P1_Pos) /**< \brief (SFR_CAL0) Calibration of High Level Output Impedance of Pads with VDDIOP1 Supply */
#define SFR_CAL0_CALP_P1(value) ((SFR_CAL0_CALP_P1_Msk & ((value) << SFR_CAL0_CALP_P1_Pos)))
#define SFR_CAL0_CALN_ANA_Pos 16
#define SFR_CAL0_CALN_ANA_Msk (0xfu << SFR_CAL0_CALN_ANA_Pos) /**< \brief (SFR_CAL0) Calibration of Low Level Output Impedance of Pads with VDDANA Supply */
#define SFR_CAL0_CALN_ANA(value) ((SFR_CAL0_CALN_ANA_Msk & ((value) << SFR_CAL0_CALN_ANA_Pos)))
#define SFR_CAL0_CALP_ANA_Pos 20
#define SFR_CAL0_CALP_ANA_Msk (0xfu << SFR_CAL0_CALP_ANA_Pos) /**< \brief (SFR_CAL0) Calibration of High Level Output Impedance of Pads with VDDANA Supply */
#define SFR_CAL0_CALP_ANA(value) ((SFR_CAL0_CALP_ANA_Msk & ((value) << SFR_CAL0_CALP_ANA_Pos)))
#define SFR_CAL0_CALN_QSPI_Pos 24
#define SFR_CAL0_CALN_QSPI_Msk (0xfu << SFR_CAL0_CALN_QSPI_Pos) /**< \brief (SFR_CAL0) Calibration of Low Level Output Impedance of Pads with VDDQSPI Supply */
#define SFR_CAL0_CALN_QSPI(value) ((SFR_CAL0_CALN_QSPI_Msk & ((value) << SFR_CAL0_CALN_QSPI_Pos)))
#define SFR_CAL0_CALP_QSPI_Pos 28
#define SFR_CAL0_CALP_QSPI_Msk (0xfu << SFR_CAL0_CALP_QSPI_Pos) /**< \brief (SFR_CAL0) Calibration of High Level Output Impedance of Pads with VDDQSPI Supply */
#define SFR_CAL0_CALP_QSPI(value) ((SFR_CAL0_CALP_QSPI_Msk & ((value) << SFR_CAL0_CALP_QSPI_Pos)))
/* -------- SFR_CAL1 : (SFR Offset: 0xB4) I/O Calibration 1 Register -------- */
#define SFR_CAL1_CALN_M_Pos 0
#define SFR_CAL1_CALN_M_Msk (0xfu << SFR_CAL1_CALN_M_Pos) /**< \brief (SFR_CAL1) Calibration of Low Level Output Impedance of Pads with VDDIOM Supply */
#define SFR_CAL1_CALN_M(value) ((SFR_CAL1_CALN_M_Msk & ((value) << SFR_CAL1_CALN_M_Pos)))
#define SFR_CAL1_CALP_M_Pos 4
#define SFR_CAL1_CALP_M_Msk (0xfu << SFR_CAL1_CALP_M_Pos) /**< \brief (SFR_CAL1) Calibration of High Level Output Impedance of Pads with VDDIOM Supply */
#define SFR_CAL1_CALP_M(value) ((SFR_CAL1_CALP_M_Msk & ((value) << SFR_CAL1_CALP_M_Pos)))
#define SFR_CAL1_TEST_M (0x1u << 8) /**< \brief (SFR_CAL1) Enable Calibration of Low/High Level Output Impedance of Pads with VDDIOM Supply */
/* -------- SFR_WPMR : (SFR Offset: 0xE4) Write Protection Mode Register -------- */
#define SFR_WPMR_WPEN (0x1u << 0) /**< \brief (SFR_WPMR) Write Protection Enable */
#define SFR_WPMR_WPKEY_Pos 8
#define SFR_WPMR_WPKEY_Msk (0xffffffu << SFR_WPMR_WPKEY_Pos) /**< \brief (SFR_WPMR) Write Protection Key */
#define SFR_WPMR_WPKEY(value) ((SFR_WPMR_WPKEY_Msk & ((value) << SFR_WPMR_WPKEY_Pos)))
#define   SFR_WPMR_WPKEY_PASSWD (0x534652u << 8) /**< \brief (SFR_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit. Always reads as 0. */

/*@}*/


#endif /* _SAM9X_SFR_COMPONENT_ */
