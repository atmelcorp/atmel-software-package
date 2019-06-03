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

#ifndef _SAM9X_PWM_INSTANCE_
#define _SAM9X_PWM_INSTANCE_

/* ========== Register definition for PWM peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_PWM_MR                     (0xF8034000U) /**< \brief (PWM) PWM Mode Register */
  #define REG_PWM_ENA                    (0xF8034004U) /**< \brief (PWM) PWM Enable Register */
  #define REG_PWM_DIS                    (0xF8034008U) /**< \brief (PWM) PWM Disable Register */
  #define REG_PWM_SR                     (0xF803400CU) /**< \brief (PWM) PWM Status Register */
  #define REG_PWM_IER                    (0xF8034010U) /**< \brief (PWM) PWM Interrupt Enable Register */
  #define REG_PWM_IDR                    (0xF8034014U) /**< \brief (PWM) PWM Interrupt Disable Register */
  #define REG_PWM_IMR                    (0xF8034018U) /**< \brief (PWM) PWM Interrupt Mask Register */
  #define REG_PWM_ISR                    (0xF803401CU) /**< \brief (PWM) PWM Interrupt Status Register */
  #define REG_PWM_CMR0                   (0xF8034200U) /**< \brief (PWM) PWM Channel Mode Register (ch_num = 0) */
  #define REG_PWM_CDTY0                  (0xF8034204U) /**< \brief (PWM) PWM Channel Duty Cycle Register (ch_num = 0) */
  #define REG_PWM_CPRD0                  (0xF8034208U) /**< \brief (PWM) PWM Channel Period Register (ch_num = 0) */
  #define REG_PWM_CCNT0                  (0xF803420CU) /**< \brief (PWM) PWM Channel Counter Register (ch_num = 0) */
  #define REG_PWM_CUPD0                  (0xF8034210U) /**< \brief (PWM) PWM Channel Update Register (ch_num = 0) */
  #define REG_PWM_CMR1                   (0xF8034220U) /**< \brief (PWM) PWM Channel Mode Register (ch_num = 1) */
  #define REG_PWM_CDTY1                  (0xF8034224U) /**< \brief (PWM) PWM Channel Duty Cycle Register (ch_num = 1) */
  #define REG_PWM_CPRD1                  (0xF8034228U) /**< \brief (PWM) PWM Channel Period Register (ch_num = 1) */
  #define REG_PWM_CCNT1                  (0xF803422CU) /**< \brief (PWM) PWM Channel Counter Register (ch_num = 1) */
  #define REG_PWM_CUPD1                  (0xF8034230U) /**< \brief (PWM) PWM Channel Update Register (ch_num = 1) */
  #define REG_PWM_CMR2                   (0xF8034240U) /**< \brief (PWM) PWM Channel Mode Register (ch_num = 2) */
  #define REG_PWM_CDTY2                  (0xF8034244U) /**< \brief (PWM) PWM Channel Duty Cycle Register (ch_num = 2) */
  #define REG_PWM_CPRD2                  (0xF8034248U) /**< \brief (PWM) PWM Channel Period Register (ch_num = 2) */
  #define REG_PWM_CCNT2                  (0xF803424CU) /**< \brief (PWM) PWM Channel Counter Register (ch_num = 2) */
  #define REG_PWM_CUPD2                  (0xF8034250U) /**< \brief (PWM) PWM Channel Update Register (ch_num = 2) */
  #define REG_PWM_CMR3                   (0xF8034260U) /**< \brief (PWM) PWM Channel Mode Register (ch_num = 3) */
  #define REG_PWM_CDTY3                  (0xF8034264U) /**< \brief (PWM) PWM Channel Duty Cycle Register (ch_num = 3) */
  #define REG_PWM_CPRD3                  (0xF8034268U) /**< \brief (PWM) PWM Channel Period Register (ch_num = 3) */
  #define REG_PWM_CCNT3                  (0xF803426CU) /**< \brief (PWM) PWM Channel Counter Register (ch_num = 3) */
  #define REG_PWM_CUPD3                  (0xF8034270U) /**< \brief (PWM) PWM Channel Update Register (ch_num = 3) */
#else
  #define REG_PWM_MR    (*(__IO uint32_t*)0xF8034000U) /**< \brief (PWM) PWM Mode Register */
  #define REG_PWM_ENA   (*(__O  uint32_t*)0xF8034004U) /**< \brief (PWM) PWM Enable Register */
  #define REG_PWM_DIS   (*(__O  uint32_t*)0xF8034008U) /**< \brief (PWM) PWM Disable Register */
  #define REG_PWM_SR    (*(__I  uint32_t*)0xF803400CU) /**< \brief (PWM) PWM Status Register */
  #define REG_PWM_IER   (*(__O  uint32_t*)0xF8034010U) /**< \brief (PWM) PWM Interrupt Enable Register */
  #define REG_PWM_IDR   (*(__O  uint32_t*)0xF8034014U) /**< \brief (PWM) PWM Interrupt Disable Register */
  #define REG_PWM_IMR   (*(__I  uint32_t*)0xF8034018U) /**< \brief (PWM) PWM Interrupt Mask Register */
  #define REG_PWM_ISR   (*(__I  uint32_t*)0xF803401CU) /**< \brief (PWM) PWM Interrupt Status Register */
  #define REG_PWM_CMR0  (*(__IO uint32_t*)0xF8034200U) /**< \brief (PWM) PWM Channel Mode Register (ch_num = 0) */
  #define REG_PWM_CDTY0 (*(__IO uint32_t*)0xF8034204U) /**< \brief (PWM) PWM Channel Duty Cycle Register (ch_num = 0) */
  #define REG_PWM_CPRD0 (*(__IO uint32_t*)0xF8034208U) /**< \brief (PWM) PWM Channel Period Register (ch_num = 0) */
  #define REG_PWM_CCNT0 (*(__I  uint32_t*)0xF803420CU) /**< \brief (PWM) PWM Channel Counter Register (ch_num = 0) */
  #define REG_PWM_CUPD0 (*(__O  uint32_t*)0xF8034210U) /**< \brief (PWM) PWM Channel Update Register (ch_num = 0) */
  #define REG_PWM_CMR1  (*(__IO uint32_t*)0xF8034220U) /**< \brief (PWM) PWM Channel Mode Register (ch_num = 1) */
  #define REG_PWM_CDTY1 (*(__IO uint32_t*)0xF8034224U) /**< \brief (PWM) PWM Channel Duty Cycle Register (ch_num = 1) */
  #define REG_PWM_CPRD1 (*(__IO uint32_t*)0xF8034228U) /**< \brief (PWM) PWM Channel Period Register (ch_num = 1) */
  #define REG_PWM_CCNT1 (*(__I  uint32_t*)0xF803422CU) /**< \brief (PWM) PWM Channel Counter Register (ch_num = 1) */
  #define REG_PWM_CUPD1 (*(__O  uint32_t*)0xF8034230U) /**< \brief (PWM) PWM Channel Update Register (ch_num = 1) */
  #define REG_PWM_CMR2  (*(__IO uint32_t*)0xF8034240U) /**< \brief (PWM) PWM Channel Mode Register (ch_num = 2) */
  #define REG_PWM_CDTY2 (*(__IO uint32_t*)0xF8034244U) /**< \brief (PWM) PWM Channel Duty Cycle Register (ch_num = 2) */
  #define REG_PWM_CPRD2 (*(__IO uint32_t*)0xF8034248U) /**< \brief (PWM) PWM Channel Period Register (ch_num = 2) */
  #define REG_PWM_CCNT2 (*(__I  uint32_t*)0xF803424CU) /**< \brief (PWM) PWM Channel Counter Register (ch_num = 2) */
  #define REG_PWM_CUPD2 (*(__O  uint32_t*)0xF8034250U) /**< \brief (PWM) PWM Channel Update Register (ch_num = 2) */
  #define REG_PWM_CMR3  (*(__IO uint32_t*)0xF8034260U) /**< \brief (PWM) PWM Channel Mode Register (ch_num = 3) */
  #define REG_PWM_CDTY3 (*(__IO uint32_t*)0xF8034264U) /**< \brief (PWM) PWM Channel Duty Cycle Register (ch_num = 3) */
  #define REG_PWM_CPRD3 (*(__IO uint32_t*)0xF8034268U) /**< \brief (PWM) PWM Channel Period Register (ch_num = 3) */
  #define REG_PWM_CCNT3 (*(__I  uint32_t*)0xF803426CU) /**< \brief (PWM) PWM Channel Counter Register (ch_num = 3) */
  #define REG_PWM_CUPD3 (*(__O  uint32_t*)0xF8034270U) /**< \brief (PWM) PWM Channel Update Register (ch_num = 3) */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_PWM_INSTANCE_ */
