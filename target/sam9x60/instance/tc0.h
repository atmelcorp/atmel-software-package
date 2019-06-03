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

#ifndef _SAM9X_TC0_INSTANCE_
#define _SAM9X_TC0_INSTANCE_

/* ========== Register definition for TC0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_TC0_CCR0                   (0xF8008000U) /**< \brief (TC0) Channel Control Register (channel = 0) */
  #define REG_TC0_CMR0                   (0xF8008004U) /**< \brief (TC0) Channel Mode Register (channel = 0) */
  #define REG_TC0_SMMR0                  (0xF8008008U) /**< \brief (TC0) Stepper Motor Mode Register (channel = 0) */
  #define REG_TC0_RAB0                   (0xF800800CU) /**< \brief (TC0) Register AB (channel = 0) */
  #define REG_TC0_CV0                    (0xF8008010U) /**< \brief (TC0) Counter Value (channel = 0) */
  #define REG_TC0_RA0                    (0xF8008014U) /**< \brief (TC0) Register A (channel = 0) */
  #define REG_TC0_RB0                    (0xF8008018U) /**< \brief (TC0) Register B (channel = 0) */
  #define REG_TC0_RC0                    (0xF800801CU) /**< \brief (TC0) Register C (channel = 0) */
  #define REG_TC0_SR0                    (0xF8008020U) /**< \brief (TC0) Interrupt Status Register (channel = 0) */
  #define REG_TC0_IER0                   (0xF8008024U) /**< \brief (TC0) Interrupt Enable Register (channel = 0) */
  #define REG_TC0_IDR0                   (0xF8008028U) /**< \brief (TC0) Interrupt Disable Register (channel = 0) */
  #define REG_TC0_IMR0                   (0xF800802CU) /**< \brief (TC0) Interrupt Mask Register (channel = 0) */
  #define REG_TC0_EMR0                   (0xF8008030U) /**< \brief (TC0) Extended Mode Register (channel = 0) */
  #define REG_TC0_CSR0                   (0xF8008034U) /**< \brief (TC0) Channel Status Register (channel = 0) */
  #define REG_TC0_SSR0                   (0xF8008038U) /**< \brief (TC0) Safety Status Register (channel = 0) */
  #define REG_TC0_CCR1                   (0xF8008040U) /**< \brief (TC0) Channel Control Register (channel = 1) */
  #define REG_TC0_CMR1                   (0xF8008044U) /**< \brief (TC0) Channel Mode Register (channel = 1) */
  #define REG_TC0_SMMR1                  (0xF8008048U) /**< \brief (TC0) Stepper Motor Mode Register (channel = 1) */
  #define REG_TC0_RAB1                   (0xF800804CU) /**< \brief (TC0) Register AB (channel = 1) */
  #define REG_TC0_CV1                    (0xF8008050U) /**< \brief (TC0) Counter Value (channel = 1) */
  #define REG_TC0_RA1                    (0xF8008054U) /**< \brief (TC0) Register A (channel = 1) */
  #define REG_TC0_RB1                    (0xF8008058U) /**< \brief (TC0) Register B (channel = 1) */
  #define REG_TC0_RC1                    (0xF800805CU) /**< \brief (TC0) Register C (channel = 1) */
  #define REG_TC0_SR1                    (0xF8008060U) /**< \brief (TC0) Interrupt Status Register (channel = 1) */
  #define REG_TC0_IER1                   (0xF8008064U) /**< \brief (TC0) Interrupt Enable Register (channel = 1) */
  #define REG_TC0_IDR1                   (0xF8008068U) /**< \brief (TC0) Interrupt Disable Register (channel = 1) */
  #define REG_TC0_IMR1                   (0xF800806CU) /**< \brief (TC0) Interrupt Mask Register (channel = 1) */
  #define REG_TC0_EMR1                   (0xF8008070U) /**< \brief (TC0) Extended Mode Register (channel = 1) */
  #define REG_TC0_CSR1                   (0xF8008074U) /**< \brief (TC0) Channel Status Register (channel = 1) */
  #define REG_TC0_SSR1                   (0xF8008078U) /**< \brief (TC0) Safety Status Register (channel = 1) */
  #define REG_TC0_CCR2                   (0xF8008080U) /**< \brief (TC0) Channel Control Register (channel = 2) */
  #define REG_TC0_CMR2                   (0xF8008084U) /**< \brief (TC0) Channel Mode Register (channel = 2) */
  #define REG_TC0_SMMR2                  (0xF8008088U) /**< \brief (TC0) Stepper Motor Mode Register (channel = 2) */
  #define REG_TC0_RAB2                   (0xF800808CU) /**< \brief (TC0) Register AB (channel = 2) */
  #define REG_TC0_CV2                    (0xF8008090U) /**< \brief (TC0) Counter Value (channel = 2) */
  #define REG_TC0_RA2                    (0xF8008094U) /**< \brief (TC0) Register A (channel = 2) */
  #define REG_TC0_RB2                    (0xF8008098U) /**< \brief (TC0) Register B (channel = 2) */
  #define REG_TC0_RC2                    (0xF800809CU) /**< \brief (TC0) Register C (channel = 2) */
  #define REG_TC0_SR2                    (0xF80080A0U) /**< \brief (TC0) Interrupt Status Register (channel = 2) */
  #define REG_TC0_IER2                   (0xF80080A4U) /**< \brief (TC0) Interrupt Enable Register (channel = 2) */
  #define REG_TC0_IDR2                   (0xF80080A8U) /**< \brief (TC0) Interrupt Disable Register (channel = 2) */
  #define REG_TC0_IMR2                   (0xF80080ACU) /**< \brief (TC0) Interrupt Mask Register (channel = 2) */
  #define REG_TC0_EMR2                   (0xF80080B0U) /**< \brief (TC0) Extended Mode Register (channel = 2) */
  #define REG_TC0_CSR2                   (0xF80080B4U) /**< \brief (TC0) Channel Status Register (channel = 2) */
  #define REG_TC0_SSR2                   (0xF80080B8U) /**< \brief (TC0) Safety Status Register (channel = 2) */
  #define REG_TC0_BCR                    (0xF80080C0U) /**< \brief (TC0) Block Control Register */
  #define REG_TC0_BMR                    (0xF80080C4U) /**< \brief (TC0) Block Mode Register */
  #define REG_TC0_QIER                   (0xF80080C8U) /**< \brief (TC0) QDEC Interrupt Enable Register */
  #define REG_TC0_QIDR                   (0xF80080CCU) /**< \brief (TC0) QDEC Interrupt Disable Register */
  #define REG_TC0_QIMR                   (0xF80080D0U) /**< \brief (TC0) QDEC Interrupt Mask Register */
  #define REG_TC0_QISR                   (0xF80080D4U) /**< \brief (TC0) QDEC Interrupt Status Register */
  #define REG_TC0_FMR                    (0xF80080D8U) /**< \brief (TC0) Fault Mode Register */
  #define REG_TC0_QSR                    (0xF80080DCU) /**< \brief (TC0) QDEC Status Register */
  #define REG_TC0_WPMR                   (0xF80080E4U) /**< \brief (TC0) Write Protection Mode Register */
#else
  #define REG_TC0_CCR0  (*(__O  uint32_t*)0xF8008000U) /**< \brief (TC0) Channel Control Register (channel = 0) */
  #define REG_TC0_CMR0  (*(__IO uint32_t*)0xF8008004U) /**< \brief (TC0) Channel Mode Register (channel = 0) */
  #define REG_TC0_SMMR0 (*(__IO uint32_t*)0xF8008008U) /**< \brief (TC0) Stepper Motor Mode Register (channel = 0) */
  #define REG_TC0_RAB0  (*(__I  uint32_t*)0xF800800CU) /**< \brief (TC0) Register AB (channel = 0) */
  #define REG_TC0_CV0   (*(__I  uint32_t*)0xF8008010U) /**< \brief (TC0) Counter Value (channel = 0) */
  #define REG_TC0_RA0   (*(__IO uint32_t*)0xF8008014U) /**< \brief (TC0) Register A (channel = 0) */
  #define REG_TC0_RB0   (*(__IO uint32_t*)0xF8008018U) /**< \brief (TC0) Register B (channel = 0) */
  #define REG_TC0_RC0   (*(__IO uint32_t*)0xF800801CU) /**< \brief (TC0) Register C (channel = 0) */
  #define REG_TC0_SR0   (*(__I  uint32_t*)0xF8008020U) /**< \brief (TC0) Interrupt Status Register (channel = 0) */
  #define REG_TC0_IER0  (*(__O  uint32_t*)0xF8008024U) /**< \brief (TC0) Interrupt Enable Register (channel = 0) */
  #define REG_TC0_IDR0  (*(__O  uint32_t*)0xF8008028U) /**< \brief (TC0) Interrupt Disable Register (channel = 0) */
  #define REG_TC0_IMR0  (*(__I  uint32_t*)0xF800802CU) /**< \brief (TC0) Interrupt Mask Register (channel = 0) */
  #define REG_TC0_EMR0  (*(__IO uint32_t*)0xF8008030U) /**< \brief (TC0) Extended Mode Register (channel = 0) */
  #define REG_TC0_CSR0  (*(__I  uint32_t*)0xF8008034U) /**< \brief (TC0) Channel Status Register (channel = 0) */
  #define REG_TC0_SSR0  (*(__I  uint32_t*)0xF8008038U) /**< \brief (TC0) Safety Status Register (channel = 0) */
  #define REG_TC0_CCR1  (*(__O  uint32_t*)0xF8008040U) /**< \brief (TC0) Channel Control Register (channel = 1) */
  #define REG_TC0_CMR1  (*(__IO uint32_t*)0xF8008044U) /**< \brief (TC0) Channel Mode Register (channel = 1) */
  #define REG_TC0_SMMR1 (*(__IO uint32_t*)0xF8008048U) /**< \brief (TC0) Stepper Motor Mode Register (channel = 1) */
  #define REG_TC0_RAB1  (*(__I  uint32_t*)0xF800804CU) /**< \brief (TC0) Register AB (channel = 1) */
  #define REG_TC0_CV1   (*(__I  uint32_t*)0xF8008050U) /**< \brief (TC0) Counter Value (channel = 1) */
  #define REG_TC0_RA1   (*(__IO uint32_t*)0xF8008054U) /**< \brief (TC0) Register A (channel = 1) */
  #define REG_TC0_RB1   (*(__IO uint32_t*)0xF8008058U) /**< \brief (TC0) Register B (channel = 1) */
  #define REG_TC0_RC1   (*(__IO uint32_t*)0xF800805CU) /**< \brief (TC0) Register C (channel = 1) */
  #define REG_TC0_SR1   (*(__I  uint32_t*)0xF8008060U) /**< \brief (TC0) Interrupt Status Register (channel = 1) */
  #define REG_TC0_IER1  (*(__O  uint32_t*)0xF8008064U) /**< \brief (TC0) Interrupt Enable Register (channel = 1) */
  #define REG_TC0_IDR1  (*(__O  uint32_t*)0xF8008068U) /**< \brief (TC0) Interrupt Disable Register (channel = 1) */
  #define REG_TC0_IMR1  (*(__I  uint32_t*)0xF800806CU) /**< \brief (TC0) Interrupt Mask Register (channel = 1) */
  #define REG_TC0_EMR1  (*(__IO uint32_t*)0xF8008070U) /**< \brief (TC0) Extended Mode Register (channel = 1) */
  #define REG_TC0_CSR1  (*(__I  uint32_t*)0xF8008074U) /**< \brief (TC0) Channel Status Register (channel = 1) */
  #define REG_TC0_SSR1  (*(__I  uint32_t*)0xF8008078U) /**< \brief (TC0) Safety Status Register (channel = 1) */
  #define REG_TC0_CCR2  (*(__O  uint32_t*)0xF8008080U) /**< \brief (TC0) Channel Control Register (channel = 2) */
  #define REG_TC0_CMR2  (*(__IO uint32_t*)0xF8008084U) /**< \brief (TC0) Channel Mode Register (channel = 2) */
  #define REG_TC0_SMMR2 (*(__IO uint32_t*)0xF8008088U) /**< \brief (TC0) Stepper Motor Mode Register (channel = 2) */
  #define REG_TC0_RAB2  (*(__I  uint32_t*)0xF800808CU) /**< \brief (TC0) Register AB (channel = 2) */
  #define REG_TC0_CV2   (*(__I  uint32_t*)0xF8008090U) /**< \brief (TC0) Counter Value (channel = 2) */
  #define REG_TC0_RA2   (*(__IO uint32_t*)0xF8008094U) /**< \brief (TC0) Register A (channel = 2) */
  #define REG_TC0_RB2   (*(__IO uint32_t*)0xF8008098U) /**< \brief (TC0) Register B (channel = 2) */
  #define REG_TC0_RC2   (*(__IO uint32_t*)0xF800809CU) /**< \brief (TC0) Register C (channel = 2) */
  #define REG_TC0_SR2   (*(__I  uint32_t*)0xF80080A0U) /**< \brief (TC0) Interrupt Status Register (channel = 2) */
  #define REG_TC0_IER2  (*(__O  uint32_t*)0xF80080A4U) /**< \brief (TC0) Interrupt Enable Register (channel = 2) */
  #define REG_TC0_IDR2  (*(__O  uint32_t*)0xF80080A8U) /**< \brief (TC0) Interrupt Disable Register (channel = 2) */
  #define REG_TC0_IMR2  (*(__I  uint32_t*)0xF80080ACU) /**< \brief (TC0) Interrupt Mask Register (channel = 2) */
  #define REG_TC0_EMR2  (*(__IO uint32_t*)0xF80080B0U) /**< \brief (TC0) Extended Mode Register (channel = 2) */
  #define REG_TC0_CSR2  (*(__I  uint32_t*)0xF80080B4U) /**< \brief (TC0) Channel Status Register (channel = 2) */
  #define REG_TC0_SSR2  (*(__I  uint32_t*)0xF80080B8U) /**< \brief (TC0) Safety Status Register (channel = 2) */
  #define REG_TC0_BCR   (*(__O  uint32_t*)0xF80080C0U) /**< \brief (TC0) Block Control Register */
  #define REG_TC0_BMR   (*(__IO uint32_t*)0xF80080C4U) /**< \brief (TC0) Block Mode Register */
  #define REG_TC0_QIER  (*(__O  uint32_t*)0xF80080C8U) /**< \brief (TC0) QDEC Interrupt Enable Register */
  #define REG_TC0_QIDR  (*(__O  uint32_t*)0xF80080CCU) /**< \brief (TC0) QDEC Interrupt Disable Register */
  #define REG_TC0_QIMR  (*(__I  uint32_t*)0xF80080D0U) /**< \brief (TC0) QDEC Interrupt Mask Register */
  #define REG_TC0_QISR  (*(__I  uint32_t*)0xF80080D4U) /**< \brief (TC0) QDEC Interrupt Status Register */
  #define REG_TC0_FMR   (*(__IO uint32_t*)0xF80080D8U) /**< \brief (TC0) Fault Mode Register */
  #define REG_TC0_QSR   (*(__I  uint32_t*)0xF80080DCU) /**< \brief (TC0) QDEC Status Register */
  #define REG_TC0_WPMR  (*(__IO uint32_t*)0xF80080E4U) /**< \brief (TC0) Write Protection Mode Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_TC0_INSTANCE_ */
