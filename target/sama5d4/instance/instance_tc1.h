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

#ifndef _SAMA5D4_TC1_INSTANCE_
#define _SAMA5D4_TC1_INSTANCE_

/* ========== Register definition for TC1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_TC1_CCR0                   (0xFC020000U) /**< \brief (TC1) Channel Control Register (channel = 0) */
  #define REG_TC1_CMR0                   (0xFC020004U) /**< \brief (TC1) Channel Mode Register (channel = 0) */
  #define REG_TC1_SMMR0                  (0xFC020008U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 0) */
  #define REG_TC1_RAB0                   (0xFC02000CU) /**< \brief (TC1) Register AB (channel = 0) */
  #define REG_TC1_CV0                    (0xFC020010U) /**< \brief (TC1) Counter Value (channel = 0) */
  #define REG_TC1_RA0                    (0xFC020014U) /**< \brief (TC1) Register A (channel = 0) */
  #define REG_TC1_RB0                    (0xFC020018U) /**< \brief (TC1) Register B (channel = 0) */
  #define REG_TC1_RC0                    (0xFC02001CU) /**< \brief (TC1) Register C (channel = 0) */
  #define REG_TC1_SR0                    (0xFC020020U) /**< \brief (TC1) Status Register (channel = 0) */
  #define REG_TC1_IER0                   (0xFC020024U) /**< \brief (TC1) Interrupt Enable Register (channel = 0) */
  #define REG_TC1_IDR0                   (0xFC020028U) /**< \brief (TC1) Interrupt Disable Register (channel = 0) */
  #define REG_TC1_IMR0                   (0xFC02002CU) /**< \brief (TC1) Interrupt Mask Register (channel = 0) */
  #define REG_TC1_EMR0                   (0xFC020030U) /**< \brief (TC1) Extended Mode Register (channel = 0) */
  #define REG_TC1_CCR1                   (0xFC020040U) /**< \brief (TC1) Channel Control Register (channel = 1) */
  #define REG_TC1_CMR1                   (0xFC020044U) /**< \brief (TC1) Channel Mode Register (channel = 1) */
  #define REG_TC1_SMMR1                  (0xFC020048U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 1) */
  #define REG_TC1_RAB1                   (0xFC02004CU) /**< \brief (TC1) Register AB (channel = 1) */
  #define REG_TC1_CV1                    (0xFC020050U) /**< \brief (TC1) Counter Value (channel = 1) */
  #define REG_TC1_RA1                    (0xFC020054U) /**< \brief (TC1) Register A (channel = 1) */
  #define REG_TC1_RB1                    (0xFC020058U) /**< \brief (TC1) Register B (channel = 1) */
  #define REG_TC1_RC1                    (0xFC02005CU) /**< \brief (TC1) Register C (channel = 1) */
  #define REG_TC1_SR1                    (0xFC020060U) /**< \brief (TC1) Status Register (channel = 1) */
  #define REG_TC1_IER1                   (0xFC020064U) /**< \brief (TC1) Interrupt Enable Register (channel = 1) */
  #define REG_TC1_IDR1                   (0xFC020068U) /**< \brief (TC1) Interrupt Disable Register (channel = 1) */
  #define REG_TC1_IMR1                   (0xFC02006CU) /**< \brief (TC1) Interrupt Mask Register (channel = 1) */
  #define REG_TC1_EMR1                   (0xFC020070U) /**< \brief (TC1) Extended Mode Register (channel = 1) */
  #define REG_TC1_CCR2                   (0xFC020080U) /**< \brief (TC1) Channel Control Register (channel = 2) */
  #define REG_TC1_CMR2                   (0xFC020084U) /**< \brief (TC1) Channel Mode Register (channel = 2) */
  #define REG_TC1_SMMR2                  (0xFC020088U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 2) */
  #define REG_TC1_RAB2                   (0xFC02008CU) /**< \brief (TC1) Register AB (channel = 2) */
  #define REG_TC1_CV2                    (0xFC020090U) /**< \brief (TC1) Counter Value (channel = 2) */
  #define REG_TC1_RA2                    (0xFC020094U) /**< \brief (TC1) Register A (channel = 2) */
  #define REG_TC1_RB2                    (0xFC020098U) /**< \brief (TC1) Register B (channel = 2) */
  #define REG_TC1_RC2                    (0xFC02009CU) /**< \brief (TC1) Register C (channel = 2) */
  #define REG_TC1_SR2                    (0xFC0200A0U) /**< \brief (TC1) Status Register (channel = 2) */
  #define REG_TC1_IER2                   (0xFC0200A4U) /**< \brief (TC1) Interrupt Enable Register (channel = 2) */
  #define REG_TC1_IDR2                   (0xFC0200A8U) /**< \brief (TC1) Interrupt Disable Register (channel = 2) */
  #define REG_TC1_IMR2                   (0xFC0200ACU) /**< \brief (TC1) Interrupt Mask Register (channel = 2) */
  #define REG_TC1_EMR2                   (0xFC0200B0U) /**< \brief (TC1) Extended Mode Register (channel = 2) */
  #define REG_TC1_BCR                    (0xFC0200C0U) /**< \brief (TC1) Block Control Register */
  #define REG_TC1_BMR                    (0xFC0200C4U) /**< \brief (TC1) Block Mode Register */
  #define REG_TC1_QIER                   (0xFC0200C8U) /**< \brief (TC1) QDEC Interrupt Enable Register */
  #define REG_TC1_QIDR                   (0xFC0200CCU) /**< \brief (TC1) QDEC Interrupt Disable Register */
  #define REG_TC1_QIMR                   (0xFC0200D0U) /**< \brief (TC1) QDEC Interrupt Mask Register */
  #define REG_TC1_QISR                   (0xFC0200D4U) /**< \brief (TC1) QDEC Interrupt Status Register */
  #define REG_TC1_FMR                    (0xFC0200D8U) /**< \brief (TC1) Fault Mode Register */
  #define REG_TC1_WPMR                   (0xFC0200E4U) /**< \brief (TC1) Write Protection Mode Register */
#else
  #define REG_TC1_CCR0  (*(__O  uint32_t*)0xFC020000U) /**< \brief (TC1) Channel Control Register (channel = 0) */
  #define REG_TC1_CMR0  (*(__IO uint32_t*)0xFC020004U) /**< \brief (TC1) Channel Mode Register (channel = 0) */
  #define REG_TC1_SMMR0 (*(__IO uint32_t*)0xFC020008U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 0) */
  #define REG_TC1_RAB0  (*(__I  uint32_t*)0xFC02000CU) /**< \brief (TC1) Register AB (channel = 0) */
  #define REG_TC1_CV0   (*(__I  uint32_t*)0xFC020010U) /**< \brief (TC1) Counter Value (channel = 0) */
  #define REG_TC1_RA0   (*(__IO uint32_t*)0xFC020014U) /**< \brief (TC1) Register A (channel = 0) */
  #define REG_TC1_RB0   (*(__IO uint32_t*)0xFC020018U) /**< \brief (TC1) Register B (channel = 0) */
  #define REG_TC1_RC0   (*(__IO uint32_t*)0xFC02001CU) /**< \brief (TC1) Register C (channel = 0) */
  #define REG_TC1_SR0   (*(__I  uint32_t*)0xFC020020U) /**< \brief (TC1) Status Register (channel = 0) */
  #define REG_TC1_IER0  (*(__O  uint32_t*)0xFC020024U) /**< \brief (TC1) Interrupt Enable Register (channel = 0) */
  #define REG_TC1_IDR0  (*(__O  uint32_t*)0xFC020028U) /**< \brief (TC1) Interrupt Disable Register (channel = 0) */
  #define REG_TC1_IMR0  (*(__I  uint32_t*)0xFC02002CU) /**< \brief (TC1) Interrupt Mask Register (channel = 0) */
  #define REG_TC1_EMR0  (*(__IO uint32_t*)0xFC020030U) /**< \brief (TC1) Extended Mode Register (channel = 0) */
  #define REG_TC1_CCR1  (*(__O  uint32_t*)0xFC020040U) /**< \brief (TC1) Channel Control Register (channel = 1) */
  #define REG_TC1_CMR1  (*(__IO uint32_t*)0xFC020044U) /**< \brief (TC1) Channel Mode Register (channel = 1) */
  #define REG_TC1_SMMR1 (*(__IO uint32_t*)0xFC020048U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 1) */
  #define REG_TC1_RAB1  (*(__I  uint32_t*)0xFC02004CU) /**< \brief (TC1) Register AB (channel = 1) */
  #define REG_TC1_CV1   (*(__I  uint32_t*)0xFC020050U) /**< \brief (TC1) Counter Value (channel = 1) */
  #define REG_TC1_RA1   (*(__IO uint32_t*)0xFC020054U) /**< \brief (TC1) Register A (channel = 1) */
  #define REG_TC1_RB1   (*(__IO uint32_t*)0xFC020058U) /**< \brief (TC1) Register B (channel = 1) */
  #define REG_TC1_RC1   (*(__IO uint32_t*)0xFC02005CU) /**< \brief (TC1) Register C (channel = 1) */
  #define REG_TC1_SR1   (*(__I  uint32_t*)0xFC020060U) /**< \brief (TC1) Status Register (channel = 1) */
  #define REG_TC1_IER1  (*(__O  uint32_t*)0xFC020064U) /**< \brief (TC1) Interrupt Enable Register (channel = 1) */
  #define REG_TC1_IDR1  (*(__O  uint32_t*)0xFC020068U) /**< \brief (TC1) Interrupt Disable Register (channel = 1) */
  #define REG_TC1_IMR1  (*(__I  uint32_t*)0xFC02006CU) /**< \brief (TC1) Interrupt Mask Register (channel = 1) */
  #define REG_TC1_EMR1  (*(__IO uint32_t*)0xFC020070U) /**< \brief (TC1) Extended Mode Register (channel = 1) */
  #define REG_TC1_CCR2  (*(__O  uint32_t*)0xFC020080U) /**< \brief (TC1) Channel Control Register (channel = 2) */
  #define REG_TC1_CMR2  (*(__IO uint32_t*)0xFC020084U) /**< \brief (TC1) Channel Mode Register (channel = 2) */
  #define REG_TC1_SMMR2 (*(__IO uint32_t*)0xFC020088U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 2) */
  #define REG_TC1_RAB2  (*(__I  uint32_t*)0xFC02008CU) /**< \brief (TC1) Register AB (channel = 2) */
  #define REG_TC1_CV2   (*(__I  uint32_t*)0xFC020090U) /**< \brief (TC1) Counter Value (channel = 2) */
  #define REG_TC1_RA2   (*(__IO uint32_t*)0xFC020094U) /**< \brief (TC1) Register A (channel = 2) */
  #define REG_TC1_RB2   (*(__IO uint32_t*)0xFC020098U) /**< \brief (TC1) Register B (channel = 2) */
  #define REG_TC1_RC2   (*(__IO uint32_t*)0xFC02009CU) /**< \brief (TC1) Register C (channel = 2) */
  #define REG_TC1_SR2   (*(__I  uint32_t*)0xFC0200A0U) /**< \brief (TC1) Status Register (channel = 2) */
  #define REG_TC1_IER2  (*(__O  uint32_t*)0xFC0200A4U) /**< \brief (TC1) Interrupt Enable Register (channel = 2) */
  #define REG_TC1_IDR2  (*(__O  uint32_t*)0xFC0200A8U) /**< \brief (TC1) Interrupt Disable Register (channel = 2) */
  #define REG_TC1_IMR2  (*(__I  uint32_t*)0xFC0200ACU) /**< \brief (TC1) Interrupt Mask Register (channel = 2) */
  #define REG_TC1_EMR2  (*(__IO uint32_t*)0xFC0200B0U) /**< \brief (TC1) Extended Mode Register (channel = 2) */
  #define REG_TC1_BCR   (*(__O  uint32_t*)0xFC0200C0U) /**< \brief (TC1) Block Control Register */
  #define REG_TC1_BMR   (*(__IO uint32_t*)0xFC0200C4U) /**< \brief (TC1) Block Mode Register */
  #define REG_TC1_QIER  (*(__O  uint32_t*)0xFC0200C8U) /**< \brief (TC1) QDEC Interrupt Enable Register */
  #define REG_TC1_QIDR  (*(__O  uint32_t*)0xFC0200CCU) /**< \brief (TC1) QDEC Interrupt Disable Register */
  #define REG_TC1_QIMR  (*(__I  uint32_t*)0xFC0200D0U) /**< \brief (TC1) QDEC Interrupt Mask Register */
  #define REG_TC1_QISR  (*(__I  uint32_t*)0xFC0200D4U) /**< \brief (TC1) QDEC Interrupt Status Register */
  #define REG_TC1_FMR   (*(__IO uint32_t*)0xFC0200D8U) /**< \brief (TC1) Fault Mode Register */
  #define REG_TC1_WPMR  (*(__IO uint32_t*)0xFC0200E4U) /**< \brief (TC1) Write Protection Mode Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D4_TC1_INSTANCE_ */
