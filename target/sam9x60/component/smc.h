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

#ifndef _SAM9X_SMC_COMPONENT_
#define _SAM9X_SMC_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Static Memory Controller */
/* ============================================================================= */
/** \addtogroup SAM9X_SMC Static Memory Controller */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief SmcCs_number hardware registers */
typedef struct {
  __IO uint32_t SMC_SETUP; /**< \brief (SmcCs_number Offset: 0x0) SMC Setup Register */
  __IO uint32_t SMC_PULSE; /**< \brief (SmcCs_number Offset: 0x4) SMC Pulse Register */
  __IO uint32_t SMC_CYCLE; /**< \brief (SmcCs_number Offset: 0x8) SMC Cycle Register */
  __IO uint32_t SMC_MODE;  /**< \brief (SmcCs_number Offset: 0xC) SMC Mode Register */
} SmcCs_number;
/** \brief Smc hardware registers */
#define SMCCS_NUMBER_NUMBER 6
typedef struct {
       SmcCs_number SMC_CS[SMCCS_NUMBER_NUMBER];        /**< \brief (Smc Offset: 0x0) CS_number = 0 .. 5 */
  __I  uint32_t     Reserved1[8];
  __IO uint32_t     SMC_OCMS;                           /**< \brief (Smc Offset: 0x80) SMC Off-Chip Memory Scrambling Register */
  __O  uint32_t     SMC_KEY1;                           /**< \brief (Smc Offset: 0x84) SMC Off-Chip Memory Scrambling KEY1 Register */
  __O  uint32_t     SMC_KEY2;                           /**< \brief (Smc Offset: 0x88) SMC Off-Chip Memory Scrambling KEY2 Register */
  __I  uint32_t     Reserved2[1];
  __IO uint32_t     SMC_SRIER;                          /**< \brief (Smc Offset: 0x90) SMC Safety Report Interrupt Enable Register */
  __I  uint32_t     Reserved3[20];
  __IO uint32_t     SMC_WPMR;                           /**< \brief (Smc Offset: 0xE4) SMC Write Protection Mode Register */
  __I  uint32_t     SMC_WPSR;                           /**< \brief (Smc Offset: 0xE8) SMC Write Protection Status Register */
} Smc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- SMC_SETUP : (SMC Offset: N/A) SMC Setup Register -------- */
#define SMC_SETUP_NWE_SETUP_Pos 0
#define SMC_SETUP_NWE_SETUP_Msk (0x3fu << SMC_SETUP_NWE_SETUP_Pos) /**< \brief (SMC_SETUP) NWE Setup Length */
#define SMC_SETUP_NWE_SETUP(value) ((SMC_SETUP_NWE_SETUP_Msk & ((value) << SMC_SETUP_NWE_SETUP_Pos)))
#define SMC_SETUP_NCS_WR_SETUP_Pos 8
#define SMC_SETUP_NCS_WR_SETUP_Msk (0x3fu << SMC_SETUP_NCS_WR_SETUP_Pos) /**< \brief (SMC_SETUP) NCS Setup Length in WRITE Access */
#define SMC_SETUP_NCS_WR_SETUP(value) ((SMC_SETUP_NCS_WR_SETUP_Msk & ((value) << SMC_SETUP_NCS_WR_SETUP_Pos)))
#define SMC_SETUP_NRD_SETUP_Pos 16
#define SMC_SETUP_NRD_SETUP_Msk (0x3fu << SMC_SETUP_NRD_SETUP_Pos) /**< \brief (SMC_SETUP) NRD Setup Length */
#define SMC_SETUP_NRD_SETUP(value) ((SMC_SETUP_NRD_SETUP_Msk & ((value) << SMC_SETUP_NRD_SETUP_Pos)))
#define SMC_SETUP_NCS_RD_SETUP_Pos 24
#define SMC_SETUP_NCS_RD_SETUP_Msk (0x3fu << SMC_SETUP_NCS_RD_SETUP_Pos) /**< \brief (SMC_SETUP) NCS Setup Length in READ Access */
#define SMC_SETUP_NCS_RD_SETUP(value) ((SMC_SETUP_NCS_RD_SETUP_Msk & ((value) << SMC_SETUP_NCS_RD_SETUP_Pos)))
/* -------- SMC_PULSE : (SMC Offset: N/A) SMC Pulse Register -------- */
#define SMC_PULSE_NWE_PULSE_Pos 0
#define SMC_PULSE_NWE_PULSE_Msk (0x7fu << SMC_PULSE_NWE_PULSE_Pos) /**< \brief (SMC_PULSE) NWE Pulse Length */
#define SMC_PULSE_NWE_PULSE(value) ((SMC_PULSE_NWE_PULSE_Msk & ((value) << SMC_PULSE_NWE_PULSE_Pos)))
#define SMC_PULSE_NCS_WR_PULSE_Pos 8
#define SMC_PULSE_NCS_WR_PULSE_Msk (0x7fu << SMC_PULSE_NCS_WR_PULSE_Pos) /**< \brief (SMC_PULSE) NCS Pulse Length in WRITE Access */
#define SMC_PULSE_NCS_WR_PULSE(value) ((SMC_PULSE_NCS_WR_PULSE_Msk & ((value) << SMC_PULSE_NCS_WR_PULSE_Pos)))
#define SMC_PULSE_NRD_PULSE_Pos 16
#define SMC_PULSE_NRD_PULSE_Msk (0x7fu << SMC_PULSE_NRD_PULSE_Pos) /**< \brief (SMC_PULSE) NRD Pulse Length */
#define SMC_PULSE_NRD_PULSE(value) ((SMC_PULSE_NRD_PULSE_Msk & ((value) << SMC_PULSE_NRD_PULSE_Pos)))
#define SMC_PULSE_NCS_RD_PULSE_Pos 24
#define SMC_PULSE_NCS_RD_PULSE_Msk (0x7fu << SMC_PULSE_NCS_RD_PULSE_Pos) /**< \brief (SMC_PULSE) NCS Pulse Length in READ Access */
#define SMC_PULSE_NCS_RD_PULSE(value) ((SMC_PULSE_NCS_RD_PULSE_Msk & ((value) << SMC_PULSE_NCS_RD_PULSE_Pos)))
/* -------- SMC_CYCLE : (SMC Offset: N/A) SMC Cycle Register -------- */
#define SMC_CYCLE_NWE_CYCLE_Pos 0
#define SMC_CYCLE_NWE_CYCLE_Msk (0x1ffu << SMC_CYCLE_NWE_CYCLE_Pos) /**< \brief (SMC_CYCLE) Total Write Cycle Length */
#define SMC_CYCLE_NWE_CYCLE(value) ((SMC_CYCLE_NWE_CYCLE_Msk & ((value) << SMC_CYCLE_NWE_CYCLE_Pos)))
#define SMC_CYCLE_NRD_CYCLE_Pos 16
#define SMC_CYCLE_NRD_CYCLE_Msk (0x1ffu << SMC_CYCLE_NRD_CYCLE_Pos) /**< \brief (SMC_CYCLE) Total Read Cycle Length */
#define SMC_CYCLE_NRD_CYCLE(value) ((SMC_CYCLE_NRD_CYCLE_Msk & ((value) << SMC_CYCLE_NRD_CYCLE_Pos)))
/* -------- SMC_MODE : (SMC Offset: N/A) SMC Mode Register -------- */
#define SMC_MODE_READ_MODE (0x1u << 0) /**< \brief (SMC_MODE) Selection of the Control Signal for Read Operation */
#define   SMC_MODE_READ_MODE_NCS_CTRL (0x0u << 0) /**< \brief (SMC_MODE) Read operation controlled by NCS signal - If TDF cycles are programmed, the external bus is marked busy after the rising edge of NCS. - If TDF optimization is enabled (TDF_MODE = 1), TDF wait states are inserted after the setup of NCS. */
#define   SMC_MODE_READ_MODE_NRD_CTRL (0x1u << 0) /**< \brief (SMC_MODE) Read operation controlled by NRD signal - If TDF cycles are programmed, the external bus is marked busy after the rising edge of NRD. - If TDF optimization is enabled (TDF_MODE = 1), TDF wait states are inserted after the setup of NRD. */
#define SMC_MODE_WRITE_MODE (0x1u << 1) /**< \brief (SMC_MODE) Selection of the Control Signal for Write Operation */
#define   SMC_MODE_WRITE_MODE_NCS_CTRL (0x0u << 1) /**< \brief (SMC_MODE) Write operation controlled by NCS signal-If TDF optimization is enabled (TDF_MODE = 1), TDF wait states will be inserted after the setup of NCS. */
#define   SMC_MODE_WRITE_MODE_NWE_CTRL (0x1u << 1) /**< \brief (SMC_MODE) Write operation controlled by NWE signal-If TDF optimization is enabled (TDF_MODE = 1), TDF wait states will be inserted after the setup of NWE. */
#define SMC_MODE_EXNW_MODE_Pos 4
#define SMC_MODE_EXNW_MODE_Msk (0x3u << SMC_MODE_EXNW_MODE_Pos) /**< \brief (SMC_MODE) NWAIT Mode */
#define SMC_MODE_EXNW_MODE(value) ((SMC_MODE_EXNW_MODE_Msk & ((value) << SMC_MODE_EXNW_MODE_Pos)))
#define   SMC_MODE_EXNW_MODE_DISABLED (0x0u << 4) /**< \brief (SMC_MODE) Disabled Mode-The NWAIT input signal is ignored on the corresponding Chip Select. */
#define   SMC_MODE_EXNW_MODE_FROZEN (0x2u << 4) /**< \brief (SMC_MODE) Frozen Mode-If asserted, the NWAIT signal freezes the current read or write cycle. After deassertion, the read/write cycle is resumed from the point where it was stopped. */
#define   SMC_MODE_EXNW_MODE_READY (0x3u << 4) /**< \brief (SMC_MODE) Ready Mode-The NWAIT signal indicates the availability of the external device at the end of the pulse of the controlling read or write signal, to complete the access. If high, the access normally completes. If low, the access is extended until NWAIT returns high. */
#define SMC_MODE_BAT (0x1u << 8) /**< \brief (SMC_MODE) Byte Access Type */
#define   SMC_MODE_BAT_BYTE_SELECT (0x0u << 8) /**< \brief (SMC_MODE) Byte select access type: - Write operation is controlled using NCS, NWE, NBS0, NBS1, NBS2 and NBS3 - Read operation is controlled using NCS, NRD, NBS0, NBS1, NBS2 and NBS3 */
#define   SMC_MODE_BAT_BYTE_WRITE (0x1u << 8) /**< \brief (SMC_MODE) Byte write access type: - Write operation is controlled using NCS, NWR0, NWR1, NWR2, NWR3 - Read operation is controlled using NCS and NRD */
#define SMC_MODE_DBW_Pos 12
#define SMC_MODE_DBW_Msk (0x3u << SMC_MODE_DBW_Pos) /**< \brief (SMC_MODE) Data Bus Width */
#define SMC_MODE_DBW(value) ((SMC_MODE_DBW_Msk & ((value) << SMC_MODE_DBW_Pos)))
#define   SMC_MODE_DBW_BIT_8 (0x0u << 12) /**< \brief (SMC_MODE) 8-bit bus */
#define   SMC_MODE_DBW_BIT_16 (0x1u << 12) /**< \brief (SMC_MODE) 16-bit bus */
#define   SMC_MODE_DBW_BIT_32 (0x2u << 12) /**< \brief (SMC_MODE) 32-bit bus */
#define SMC_MODE_TDF_CYCLES_Pos 16
#define SMC_MODE_TDF_CYCLES_Msk (0xfu << SMC_MODE_TDF_CYCLES_Pos) /**< \brief (SMC_MODE) Data Float Time */
#define SMC_MODE_TDF_CYCLES(value) ((SMC_MODE_TDF_CYCLES_Msk & ((value) << SMC_MODE_TDF_CYCLES_Pos)))
#define SMC_MODE_TDF_MODE (0x1u << 20) /**< \brief (SMC_MODE) TDF Optimization */
#define SMC_MODE_PMEN (0x1u << 24) /**< \brief (SMC_MODE) Page Mode Enabled */
#define SMC_MODE_PS_Pos 28
#define SMC_MODE_PS_Msk (0x3u << SMC_MODE_PS_Pos) /**< \brief (SMC_MODE) Page Size */
#define SMC_MODE_PS(value) ((SMC_MODE_PS_Msk & ((value) << SMC_MODE_PS_Pos)))
#define   SMC_MODE_PS_BYTE_4 (0x0u << 28) /**< \brief (SMC_MODE) 4-byte page */
#define   SMC_MODE_PS_BYTE_8 (0x1u << 28) /**< \brief (SMC_MODE) 8-byte page */
#define   SMC_MODE_PS_BYTE_16 (0x2u << 28) /**< \brief (SMC_MODE) 16-byte page */
#define   SMC_MODE_PS_BYTE_32 (0x3u << 28) /**< \brief (SMC_MODE) 32-byte page */
/* -------- SMC_OCMS : (SMC Offset: 0x80) SMC Off-Chip Memory Scrambling Register -------- */
#define SMC_OCMS_SMSE (0x1u << 0) /**< \brief (SMC_OCMS) Static Memory Controller Scrambling Enable */
#define SMC_OCMS_TAMPCLR (0x1u << 4) /**< \brief (SMC_OCMS) Tamper Clear Enable */
#define SMC_OCMS_CS0SE (0x1u << 8) /**< \brief (SMC_OCMS) Chip Select (x = 0 to 5) Scrambling Enable */
#define SMC_OCMS_CS1SE (0x1u << 9) /**< \brief (SMC_OCMS) Chip Select (x = 0 to 5) Scrambling Enable */
#define SMC_OCMS_CS2SE (0x1u << 10) /**< \brief (SMC_OCMS) Chip Select (x = 0 to 5) Scrambling Enable */
#define SMC_OCMS_CS3SE (0x1u << 11) /**< \brief (SMC_OCMS) Chip Select (x = 0 to 5) Scrambling Enable */
#define SMC_OCMS_CS4SE (0x1u << 12) /**< \brief (SMC_OCMS) Chip Select (x = 0 to 5) Scrambling Enable */
#define SMC_OCMS_CS5SE (0x1u << 13) /**< \brief (SMC_OCMS) Chip Select (x = 0 to 5) Scrambling Enable */
/* -------- SMC_KEY1 : (SMC Offset: 0x84) SMC Off-Chip Memory Scrambling KEY1 Register -------- */
#define SMC_KEY1_KEY1_Pos 0
#define SMC_KEY1_KEY1_Msk (0xffffffffu << SMC_KEY1_KEY1_Pos) /**< \brief (SMC_KEY1) Off-Chip Memory Scrambling (OCMS) Key Part 1 */
#define SMC_KEY1_KEY1(value) ((SMC_KEY1_KEY1_Msk & ((value) << SMC_KEY1_KEY1_Pos)))
/* -------- SMC_KEY2 : (SMC Offset: 0x88) SMC Off-Chip Memory Scrambling KEY2 Register -------- */
#define SMC_KEY2_KEY2_Pos 0
#define SMC_KEY2_KEY2_Msk (0xffffffffu << SMC_KEY2_KEY2_Pos) /**< \brief (SMC_KEY2) Off-Chip Memory Scrambling (OCMS) Key Part 2 */
#define SMC_KEY2_KEY2(value) ((SMC_KEY2_KEY2_Msk & ((value) << SMC_KEY2_KEY2_Pos)))
/* -------- SMC_SRIER : (SMC Offset: 0x90) SMC Safety Report Interrupt Enable Register -------- */
#define SMC_SRIER_SRIE (0x1u << 0) /**< \brief (SMC_SRIER) Safety Report Interrupt Enable */
/* -------- SMC_WPMR : (SMC Offset: 0xE4) SMC Write Protection Mode Register -------- */
#define SMC_WPMR_WPEN (0x1u << 0) /**< \brief (SMC_WPMR) Write Protection Enable */
#define SMC_WPMR_WPKEY_Pos 8
#define SMC_WPMR_WPKEY_Msk (0xffffffu << SMC_WPMR_WPKEY_Pos) /**< \brief (SMC_WPMR) Write Protection Key */
#define SMC_WPMR_WPKEY(value) ((SMC_WPMR_WPKEY_Msk & ((value) << SMC_WPMR_WPKEY_Pos)))
#define   SMC_WPMR_WPKEY_PASSWD (0x534D43u << 8) /**< \brief (SMC_WPMR) Writing any other value in this field aborts the write operation of bit WPEN. Always reads as 0. */
/* -------- SMC_WPSR : (SMC Offset: 0xE8) SMC Write Protection Status Register -------- */
#define SMC_WPSR_WPVS (0x1u << 0) /**< \brief (SMC_WPSR) Write Protection Violation Status (Cleared on read) */
#define SMC_WPSR_SEQE (0x1u << 2) /**< \brief (SMC_WPSR) Internal Sequencer Error (Cleared on read) */
#define SMC_WPSR_SWE (0x1u << 3) /**< \brief (SMC_WPSR) Software Control Error (Cleared on read) */
#define SMC_WPSR_WPVSRC_Pos 8
#define SMC_WPSR_WPVSRC_Msk (0xffffu << SMC_WPSR_WPVSRC_Pos) /**< \brief (SMC_WPSR) Write Protection Violation Source */
#define SMC_WPSR_SWETYP_Pos 24
#define SMC_WPSR_SWETYP_Msk (0x3u << SMC_WPSR_SWETYP_Pos) /**< \brief (SMC_WPSR) Software Error Type (Cleared on read) */
#define   SMC_WPSR_SWETYP_READ_WO (0x0u << 24) /**< \brief (SMC_WPSR) A write-only register has been read. */
#define   SMC_WPSR_SWETYP_WRITE_RO (0x1u << 24) /**< \brief (SMC_WPSR) A write access has been performed on a read-only register. */
#define   SMC_WPSR_SWETYP_UNDEF_RW (0x2u << 24) /**< \brief (SMC_WPSR) Access to an undefined address. */

/*@}*/


#endif /* _SAM9X_SMC_COMPONENT_ */
