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

#ifndef _SAM9X_QSPI_INSTANCE_
#define _SAM9X_QSPI_INSTANCE_

/* ========== Register definition for QSPI peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_QSPI_CR                    (0xF0014000U) /**< \brief (QSPI) Control Register */
  #define REG_QSPI_MR                    (0xF0014004U) /**< \brief (QSPI) Mode Register */
  #define REG_QSPI_RDR                   (0xF0014008U) /**< \brief (QSPI) Receive Data Register */
  #define REG_QSPI_TDR                   (0xF001400CU) /**< \brief (QSPI) Transmit Data Register */
  #define REG_QSPI_SR                    (0xF0014010U) /**< \brief (QSPI) Status Register */
  #define REG_QSPI_IER                   (0xF0014014U) /**< \brief (QSPI) Interrupt Enable Register */
  #define REG_QSPI_IDR                   (0xF0014018U) /**< \brief (QSPI) Interrupt Disable Register */
  #define REG_QSPI_IMR                   (0xF001401CU) /**< \brief (QSPI) Interrupt Mask Register */
  #define REG_QSPI_SCR                   (0xF0014020U) /**< \brief (QSPI) Serial Clock Register */
  #define REG_QSPI_IAR                   (0xF0014030U) /**< \brief (QSPI) Instruction Address Register */
  #define REG_QSPI_WICR                  (0xF0014034U) /**< \brief (QSPI) Write Instruction Code Register */
  #define REG_QSPI_IFR                   (0xF0014038U) /**< \brief (QSPI) Instruction Frame Register */
  #define REG_QSPI_RICR                  (0xF001403CU) /**< \brief (QSPI) Read Instruction Code Register */
  #define REG_QSPI_SMR                   (0xF0014040U) /**< \brief (QSPI) Scrambling Mode Register */
  #define REG_QSPI_SKR                   (0xF0014044U) /**< \brief (QSPI) Scrambling Key Register */
  #define REG_QSPI_WPMR                  (0xF00140E4U) /**< \brief (QSPI) Write Protection Mode Register */
  #define REG_QSPI_WPSR                  (0xF00140E8U) /**< \brief (QSPI) Write Protection Status Register */
#else
  #define REG_QSPI_CR   (*(__O  uint32_t*)0xF0014000U) /**< \brief (QSPI) Control Register */
  #define REG_QSPI_MR   (*(__IO uint32_t*)0xF0014004U) /**< \brief (QSPI) Mode Register */
  #define REG_QSPI_RDR  (*(__I  uint32_t*)0xF0014008U) /**< \brief (QSPI) Receive Data Register */
  #define REG_QSPI_TDR  (*(__O  uint32_t*)0xF001400CU) /**< \brief (QSPI) Transmit Data Register */
  #define REG_QSPI_SR   (*(__I  uint32_t*)0xF0014010U) /**< \brief (QSPI) Status Register */
  #define REG_QSPI_IER  (*(__O  uint32_t*)0xF0014014U) /**< \brief (QSPI) Interrupt Enable Register */
  #define REG_QSPI_IDR  (*(__O  uint32_t*)0xF0014018U) /**< \brief (QSPI) Interrupt Disable Register */
  #define REG_QSPI_IMR  (*(__I  uint32_t*)0xF001401CU) /**< \brief (QSPI) Interrupt Mask Register */
  #define REG_QSPI_SCR  (*(__IO uint32_t*)0xF0014020U) /**< \brief (QSPI) Serial Clock Register */
  #define REG_QSPI_IAR  (*(__IO uint32_t*)0xF0014030U) /**< \brief (QSPI) Instruction Address Register */
  #define REG_QSPI_WICR (*(__IO uint32_t*)0xF0014034U) /**< \brief (QSPI) Write Instruction Code Register */
  #define REG_QSPI_IFR  (*(__IO uint32_t*)0xF0014038U) /**< \brief (QSPI) Instruction Frame Register */
  #define REG_QSPI_RICR (*(__IO uint32_t*)0xF001403CU) /**< \brief (QSPI) Read Instruction Code Register */
  #define REG_QSPI_SMR  (*(__IO uint32_t*)0xF0014040U) /**< \brief (QSPI) Scrambling Mode Register */
  #define REG_QSPI_SKR  (*(__O  uint32_t*)0xF0014044U) /**< \brief (QSPI) Scrambling Key Register */
  #define REG_QSPI_WPMR (*(__IO uint32_t*)0xF00140E4U) /**< \brief (QSPI) Write Protection Mode Register */
  #define REG_QSPI_WPSR (*(__I  uint32_t*)0xF00140E8U) /**< \brief (QSPI) Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_QSPI_INSTANCE_ */
