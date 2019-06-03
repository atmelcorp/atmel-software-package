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

#ifndef _SAM9X_TC1_INSTANCE_
#define _SAM9X_TC1_INSTANCE_

/* ========== Register definition for TC1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_TC1_CCR0                   (0xF800C000U) /**< \brief (TC1) Channel Control Register (channel = 0) */
  #define REG_TC1_CMR0                   (0xF800C004U) /**< \brief (TC1) Channel Mode Register (channel = 0) */
  #define REG_TC1_SMMR0                  (0xF800C008U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 0) */
  #define REG_TC1_RAB0                   (0xF800C00CU) /**< \brief (TC1) Register AB (channel = 0) */
  #define REG_TC1_CV0                    (0xF800C010U) /**< \brief (TC1) Counter Value (channel = 0) */
  #define REG_TC1_RA0                    (0xF800C014U) /**< \brief (TC1) Register A (channel = 0) */
  #define REG_TC1_RB0                    (0xF800C018U) /**< \brief (TC1) Register B (channel = 0) */
  #define REG_TC1_RC0                    (0xF800C01CU) /**< \brief (TC1) Register C (channel = 0) */
  #define REG_TC1_SR0                    (0xF800C020U) /**< \brief (TC1) Interrupt Status Register (channel = 0) */
  #define REG_TC1_IER0                   (0xF800C024U) /**< \brief (TC1) Interrupt Enable Register (channel = 0) */
  #define REG_TC1_IDR0                   (0xF800C028U) /**< \brief (TC1) Interrupt Disable Register (channel = 0) */
  #define REG_TC1_IMR0                   (0xF800C02CU) /**< \brief (TC1) Interrupt Mask Register (channel = 0) */
  #define REG_TC1_EMR0                   (0xF800C030U) /**< \brief (TC1) Extended Mode Register (channel = 0) */
  #define REG_TC1_CSR0                   (0xF800C034U) /**< \brief (TC1) Channel Status Register (channel = 0) */
  #define REG_TC1_SSR0                   (0xF800C038U) /**< \brief (TC1) Safety Status Register (channel = 0) */
  #define REG_TC1_CCR1                   (0xF800C040U) /**< \brief (TC1) Channel Control Register (channel = 1) */
  #define REG_TC1_CMR1                   (0xF800C044U) /**< \brief (TC1) Channel Mode Register (channel = 1) */
  #define REG_TC1_SMMR1                  (0xF800C048U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 1) */
  #define REG_TC1_RAB1                   (0xF800C04CU) /**< \brief (TC1) Register AB (channel = 1) */
  #define REG_TC1_CV1                    (0xF800C050U) /**< \brief (TC1) Counter Value (channel = 1) */
  #define REG_TC1_RA1                    (0xF800C054U) /**< \brief (TC1) Register A (channel = 1) */
  #define REG_TC1_RB1                    (0xF800C058U) /**< \brief (TC1) Register B (channel = 1) */
  #define REG_TC1_RC1                    (0xF800C05CU) /**< \brief (TC1) Register C (channel = 1) */
  #define REG_TC1_SR1                    (0xF800C060U) /**< \brief (TC1) Interrupt Status Register (channel = 1) */
  #define REG_TC1_IER1                   (0xF800C064U) /**< \brief (TC1) Interrupt Enable Register (channel = 1) */
  #define REG_TC1_IDR1                   (0xF800C068U) /**< \brief (TC1) Interrupt Disable Register (channel = 1) */
  #define REG_TC1_IMR1                   (0xF800C06CU) /**< \brief (TC1) Interrupt Mask Register (channel = 1) */
  #define REG_TC1_EMR1                   (0xF800C070U) /**< \brief (TC1) Extended Mode Register (channel = 1) */
  #define REG_TC1_CSR1                   (0xF800C074U) /**< \brief (TC1) Channel Status Register (channel = 1) */
  #define REG_TC1_SSR1                   (0xF800C078U) /**< \brief (TC1) Safety Status Register (channel = 1) */
  #define REG_TC1_CCR2                   (0xF800C080U) /**< \brief (TC1) Channel Control Register (channel = 2) */
  #define REG_TC1_CMR2                   (0xF800C084U) /**< \brief (TC1) Channel Mode Register (channel = 2) */
  #define REG_TC1_SMMR2                  (0xF800C088U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 2) */
  #define REG_TC1_RAB2                   (0xF800C08CU) /**< \brief (TC1) Register AB (channel = 2) */
  #define REG_TC1_CV2                    (0xF800C090U) /**< \brief (TC1) Counter Value (channel = 2) */
  #define REG_TC1_RA2                    (0xF800C094U) /**< \brief (TC1) Register A (channel = 2) */
  #define REG_TC1_RB2                    (0xF800C098U) /**< \brief (TC1) Register B (channel = 2) */
  #define REG_TC1_RC2                    (0xF800C09CU) /**< \brief (TC1) Register C (channel = 2) */
  #define REG_TC1_SR2                    (0xF800C0A0U) /**< \brief (TC1) Interrupt Status Register (channel = 2) */
  #define REG_TC1_IER2                   (0xF800C0A4U) /**< \brief (TC1) Interrupt Enable Register (channel = 2) */
  #define REG_TC1_IDR2                   (0xF800C0A8U) /**< \brief (TC1) Interrupt Disable Register (channel = 2) */
  #define REG_TC1_IMR2                   (0xF800C0ACU) /**< \brief (TC1) Interrupt Mask Register (channel = 2) */
  #define REG_TC1_EMR2                   (0xF800C0B0U) /**< \brief (TC1) Extended Mode Register (channel = 2) */
  #define REG_TC1_CSR2                   (0xF800C0B4U) /**< \brief (TC1) Channel Status Register (channel = 2) */
  #define REG_TC1_SSR2                   (0xF800C0B8U) /**< \brief (TC1) Safety Status Register (channel = 2) */
  #define REG_TC1_BCR                    (0xF800C0C0U) /**< \brief (TC1) Block Control Register */
  #define REG_TC1_BMR                    (0xF800C0C4U) /**< \brief (TC1) Block Mode Register */
  #define REG_TC1_QIER                   (0xF800C0C8U) /**< \brief (TC1) QDEC Interrupt Enable Register */
  #define REG_TC1_QIDR                   (0xF800C0CCU) /**< \brief (TC1) QDEC Interrupt Disable Register */
  #define REG_TC1_QIMR                   (0xF800C0D0U) /**< \brief (TC1) QDEC Interrupt Mask Register */
  #define REG_TC1_QISR                   (0xF800C0D4U) /**< \brief (TC1) QDEC Interrupt Status Register */
  #define REG_TC1_FMR                    (0xF800C0D8U) /**< \brief (TC1) Fault Mode Register */
  #define REG_TC1_QSR                    (0xF800C0DCU) /**< \brief (TC1) QDEC Status Register */
  #define REG_TC1_WPMR                   (0xF800C0E4U) /**< \brief (TC1) Write Protection Mode Register */
#else
  #define REG_TC1_CCR0  (*(__O  uint32_t*)0xF800C000U) /**< \brief (TC1) Channel Control Register (channel = 0) */
  #define REG_TC1_CMR0  (*(__IO uint32_t*)0xF800C004U) /**< \brief (TC1) Channel Mode Register (channel = 0) */
  #define REG_TC1_SMMR0 (*(__IO uint32_t*)0xF800C008U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 0) */
  #define REG_TC1_RAB0  (*(__I  uint32_t*)0xF800C00CU) /**< \brief (TC1) Register AB (channel = 0) */
  #define REG_TC1_CV0   (*(__I  uint32_t*)0xF800C010U) /**< \brief (TC1) Counter Value (channel = 0) */
  #define REG_TC1_RA0   (*(__IO uint32_t*)0xF800C014U) /**< \brief (TC1) Register A (channel = 0) */
  #define REG_TC1_RB0   (*(__IO uint32_t*)0xF800C018U) /**< \brief (TC1) Register B (channel = 0) */
  #define REG_TC1_RC0   (*(__IO uint32_t*)0xF800C01CU) /**< \brief (TC1) Register C (channel = 0) */
  #define REG_TC1_SR0   (*(__I  uint32_t*)0xF800C020U) /**< \brief (TC1) Interrupt Status Register (channel = 0) */
  #define REG_TC1_IER0  (*(__O  uint32_t*)0xF800C024U) /**< \brief (TC1) Interrupt Enable Register (channel = 0) */
  #define REG_TC1_IDR0  (*(__O  uint32_t*)0xF800C028U) /**< \brief (TC1) Interrupt Disable Register (channel = 0) */
  #define REG_TC1_IMR0  (*(__I  uint32_t*)0xF800C02CU) /**< \brief (TC1) Interrupt Mask Register (channel = 0) */
  #define REG_TC1_EMR0  (*(__IO uint32_t*)0xF800C030U) /**< \brief (TC1) Extended Mode Register (channel = 0) */
  #define REG_TC1_CSR0  (*(__I  uint32_t*)0xF800C034U) /**< \brief (TC1) Channel Status Register (channel = 0) */
  #define REG_TC1_SSR0  (*(__I  uint32_t*)0xF800C038U) /**< \brief (TC1) Safety Status Register (channel = 0) */
  #define REG_TC1_CCR1  (*(__O  uint32_t*)0xF800C040U) /**< \brief (TC1) Channel Control Register (channel = 1) */
  #define REG_TC1_CMR1  (*(__IO uint32_t*)0xF800C044U) /**< \brief (TC1) Channel Mode Register (channel = 1) */
  #define REG_TC1_SMMR1 (*(__IO uint32_t*)0xF800C048U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 1) */
  #define REG_TC1_RAB1  (*(__I  uint32_t*)0xF800C04CU) /**< \brief (TC1) Register AB (channel = 1) */
  #define REG_TC1_CV1   (*(__I  uint32_t*)0xF800C050U) /**< \brief (TC1) Counter Value (channel = 1) */
  #define REG_TC1_RA1   (*(__IO uint32_t*)0xF800C054U) /**< \brief (TC1) Register A (channel = 1) */
  #define REG_TC1_RB1   (*(__IO uint32_t*)0xF800C058U) /**< \brief (TC1) Register B (channel = 1) */
  #define REG_TC1_RC1   (*(__IO uint32_t*)0xF800C05CU) /**< \brief (TC1) Register C (channel = 1) */
  #define REG_TC1_SR1   (*(__I  uint32_t*)0xF800C060U) /**< \brief (TC1) Interrupt Status Register (channel = 1) */
  #define REG_TC1_IER1  (*(__O  uint32_t*)0xF800C064U) /**< \brief (TC1) Interrupt Enable Register (channel = 1) */
  #define REG_TC1_IDR1  (*(__O  uint32_t*)0xF800C068U) /**< \brief (TC1) Interrupt Disable Register (channel = 1) */
  #define REG_TC1_IMR1  (*(__I  uint32_t*)0xF800C06CU) /**< \brief (TC1) Interrupt Mask Register (channel = 1) */
  #define REG_TC1_EMR1  (*(__IO uint32_t*)0xF800C070U) /**< \brief (TC1) Extended Mode Register (channel = 1) */
  #define REG_TC1_CSR1  (*(__I  uint32_t*)0xF800C074U) /**< \brief (TC1) Channel Status Register (channel = 1) */
  #define REG_TC1_SSR1  (*(__I  uint32_t*)0xF800C078U) /**< \brief (TC1) Safety Status Register (channel = 1) */
  #define REG_TC1_CCR2  (*(__O  uint32_t*)0xF800C080U) /**< \brief (TC1) Channel Control Register (channel = 2) */
  #define REG_TC1_CMR2  (*(__IO uint32_t*)0xF800C084U) /**< \brief (TC1) Channel Mode Register (channel = 2) */
  #define REG_TC1_SMMR2 (*(__IO uint32_t*)0xF800C088U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 2) */
  #define REG_TC1_RAB2  (*(__I  uint32_t*)0xF800C08CU) /**< \brief (TC1) Register AB (channel = 2) */
  #define REG_TC1_CV2   (*(__I  uint32_t*)0xF800C090U) /**< \brief (TC1) Counter Value (channel = 2) */
  #define REG_TC1_RA2   (*(__IO uint32_t*)0xF800C094U) /**< \brief (TC1) Register A (channel = 2) */
  #define REG_TC1_RB2   (*(__IO uint32_t*)0xF800C098U) /**< \brief (TC1) Register B (channel = 2) */
  #define REG_TC1_RC2   (*(__IO uint32_t*)0xF800C09CU) /**< \brief (TC1) Register C (channel = 2) */
  #define REG_TC1_SR2   (*(__I  uint32_t*)0xF800C0A0U) /**< \brief (TC1) Interrupt Status Register (channel = 2) */
  #define REG_TC1_IER2  (*(__O  uint32_t*)0xF800C0A4U) /**< \brief (TC1) Interrupt Enable Register (channel = 2) */
  #define REG_TC1_IDR2  (*(__O  uint32_t*)0xF800C0A8U) /**< \brief (TC1) Interrupt Disable Register (channel = 2) */
  #define REG_TC1_IMR2  (*(__I  uint32_t*)0xF800C0ACU) /**< \brief (TC1) Interrupt Mask Register (channel = 2) */
  #define REG_TC1_EMR2  (*(__IO uint32_t*)0xF800C0B0U) /**< \brief (TC1) Extended Mode Register (channel = 2) */
  #define REG_TC1_CSR2  (*(__I  uint32_t*)0xF800C0B4U) /**< \brief (TC1) Channel Status Register (channel = 2) */
  #define REG_TC1_SSR2  (*(__I  uint32_t*)0xF800C0B8U) /**< \brief (TC1) Safety Status Register (channel = 2) */
  #define REG_TC1_BCR   (*(__O  uint32_t*)0xF800C0C0U) /**< \brief (TC1) Block Control Register */
  #define REG_TC1_BMR   (*(__IO uint32_t*)0xF800C0C4U) /**< \brief (TC1) Block Mode Register */
  #define REG_TC1_QIER  (*(__O  uint32_t*)0xF800C0C8U) /**< \brief (TC1) QDEC Interrupt Enable Register */
  #define REG_TC1_QIDR  (*(__O  uint32_t*)0xF800C0CCU) /**< \brief (TC1) QDEC Interrupt Disable Register */
  #define REG_TC1_QIMR  (*(__I  uint32_t*)0xF800C0D0U) /**< \brief (TC1) QDEC Interrupt Mask Register */
  #define REG_TC1_QISR  (*(__I  uint32_t*)0xF800C0D4U) /**< \brief (TC1) QDEC Interrupt Status Register */
  #define REG_TC1_FMR   (*(__IO uint32_t*)0xF800C0D8U) /**< \brief (TC1) Fault Mode Register */
  #define REG_TC1_QSR   (*(__I  uint32_t*)0xF800C0DCU) /**< \brief (TC1) QDEC Status Register */
  #define REG_TC1_WPMR  (*(__IO uint32_t*)0xF800C0E4U) /**< \brief (TC1) Write Protection Mode Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_TC1_INSTANCE_ */
