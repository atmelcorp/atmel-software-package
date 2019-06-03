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

#ifndef _SAM9X_ADC_INSTANCE_
#define _SAM9X_ADC_INSTANCE_

/* ========== Register definition for ADC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_ADC_CR                      (0xF804C000U) /**< \brief (ADC) Control Register */
  #define REG_ADC_MR                      (0xF804C004U) /**< \brief (ADC) Mode Register */
  #define REG_ADC_SEQR1                   (0xF804C008U) /**< \brief (ADC) Channel Sequence Register 1 */
  #define REG_ADC_SEQR2                   (0xF804C00CU) /**< \brief (ADC) Channel Sequence Register 2 */
  #define REG_ADC_CHER                    (0xF804C010U) /**< \brief (ADC) Channel Enable Register */
  #define REG_ADC_CHDR                    (0xF804C014U) /**< \brief (ADC) Channel Disable Register */
  #define REG_ADC_CHSR                    (0xF804C018U) /**< \brief (ADC) Channel Status Register */
  #define REG_ADC_LCDR                    (0xF804C020U) /**< \brief (ADC) Last Converted Data Register */
  #define REG_ADC_IER                     (0xF804C024U) /**< \brief (ADC) Interrupt Enable Register */
  #define REG_ADC_IDR                     (0xF804C028U) /**< \brief (ADC) Interrupt Disable Register */
  #define REG_ADC_IMR                     (0xF804C02CU) /**< \brief (ADC) Interrupt Mask Register */
  #define REG_ADC_ISR                     (0xF804C030U) /**< \brief (ADC) Interrupt Status Register */
  #define REG_ADC_LCTMR                   (0xF804C034U) /**< \brief (ADC) Last Channel Trigger Mode Register */
  #define REG_ADC_LCCWR                   (0xF804C038U) /**< \brief (ADC) Last Channel Compare Window Register */
  #define REG_ADC_OVER                    (0xF804C03CU) /**< \brief (ADC) Overrun Status Register */
  #define REG_ADC_EMR                     (0xF804C040U) /**< \brief (ADC) Extended Mode Register */
  #define REG_ADC_CWR                     (0xF804C044U) /**< \brief (ADC) Compare Window Register */
  #define REG_ADC_CCR                     (0xF804C04CU) /**< \brief (ADC) Channel Configuration Register */
  #define REG_ADC_CDR                     (0xF804C050U) /**< \brief (ADC) Channel Data Register */
  #define REG_ADC_ACR                     (0xF804C094U) /**< \brief (ADC) Analog Control Register */
  #define REG_ADC_PDR                     (0xF804C0A0U) /**< \brief (ADC) Pseudo-Differential Register */
  #define REG_ADC_TSMR                    (0xF804C0B0U) /**< \brief (ADC) Touchscreen Mode Register */
  #define REG_ADC_XPOSR                   (0xF804C0B4U) /**< \brief (ADC) Touchscreen X Position Register */
  #define REG_ADC_YPOSR                   (0xF804C0B8U) /**< \brief (ADC) Touchscreen Y Position Register */
  #define REG_ADC_PRESSR                  (0xF804C0BCU) /**< \brief (ADC) Touchscreen Pressure Register */
  #define REG_ADC_TRGR                    (0xF804C0C0U) /**< \brief (ADC) Trigger Register */
  #define REG_ADC_CVR                     (0xF804C0D4U) /**< \brief (ADC) Correction Values Register */
  #define REG_ADC_CECR                    (0xF804C0D8U) /**< \brief (ADC) Channel Error Correction Register */
  #define REG_ADC_TSCVR                   (0xF804C0DCU) /**< \brief (ADC) Touchscreen Correction Values Register */
  #define REG_ADC_WPMR                    (0xF804C0E4U) /**< \brief (ADC) Write Protection Mode Register */
  #define REG_ADC_WPSR                    (0xF804C0E8U) /**< \brief (ADC) Write Protection Status Register */
#else
  #define REG_ADC_CR     (*(__O  uint32_t*)0xF804C000U) /**< \brief (ADC) Control Register */
  #define REG_ADC_MR     (*(__IO uint32_t*)0xF804C004U) /**< \brief (ADC) Mode Register */
  #define REG_ADC_SEQR1  (*(__IO uint32_t*)0xF804C008U) /**< \brief (ADC) Channel Sequence Register 1 */
  #define REG_ADC_SEQR2  (*(__IO uint32_t*)0xF804C00CU) /**< \brief (ADC) Channel Sequence Register 2 */
  #define REG_ADC_CHER   (*(__O  uint32_t*)0xF804C010U) /**< \brief (ADC) Channel Enable Register */
  #define REG_ADC_CHDR   (*(__O  uint32_t*)0xF804C014U) /**< \brief (ADC) Channel Disable Register */
  #define REG_ADC_CHSR   (*(__I  uint32_t*)0xF804C018U) /**< \brief (ADC) Channel Status Register */
  #define REG_ADC_LCDR   (*(__I  uint32_t*)0xF804C020U) /**< \brief (ADC) Last Converted Data Register */
  #define REG_ADC_IER    (*(__O  uint32_t*)0xF804C024U) /**< \brief (ADC) Interrupt Enable Register */
  #define REG_ADC_IDR    (*(__O  uint32_t*)0xF804C028U) /**< \brief (ADC) Interrupt Disable Register */
  #define REG_ADC_IMR    (*(__I  uint32_t*)0xF804C02CU) /**< \brief (ADC) Interrupt Mask Register */
  #define REG_ADC_ISR    (*(__I  uint32_t*)0xF804C030U) /**< \brief (ADC) Interrupt Status Register */
  #define REG_ADC_LCTMR  (*(__IO uint32_t*)0xF804C034U) /**< \brief (ADC) Last Channel Trigger Mode Register */
  #define REG_ADC_LCCWR  (*(__IO uint32_t*)0xF804C038U) /**< \brief (ADC) Last Channel Compare Window Register */
  #define REG_ADC_OVER   (*(__I  uint32_t*)0xF804C03CU) /**< \brief (ADC) Overrun Status Register */
  #define REG_ADC_EMR    (*(__IO uint32_t*)0xF804C040U) /**< \brief (ADC) Extended Mode Register */
  #define REG_ADC_CWR    (*(__IO uint32_t*)0xF804C044U) /**< \brief (ADC) Compare Window Register */
  #define REG_ADC_CCR    (*(__IO uint32_t*)0xF804C04CU) /**< \brief (ADC) Channel Configuration Register */
  #define REG_ADC_CDR    (*(__I  uint32_t*)0xF804C050U) /**< \brief (ADC) Channel Data Register */
  #define REG_ADC_ACR    (*(__IO uint32_t*)0xF804C094U) /**< \brief (ADC) Analog Control Register */
  #define REG_ADC_PDR    (*(__IO uint32_t*)0xF804C0A0U) /**< \brief (ADC) Pseudo-Differential Register */
  #define REG_ADC_TSMR   (*(__IO uint32_t*)0xF804C0B0U) /**< \brief (ADC) Touchscreen Mode Register */
  #define REG_ADC_XPOSR  (*(__I  uint32_t*)0xF804C0B4U) /**< \brief (ADC) Touchscreen X Position Register */
  #define REG_ADC_YPOSR  (*(__I  uint32_t*)0xF804C0B8U) /**< \brief (ADC) Touchscreen Y Position Register */
  #define REG_ADC_PRESSR (*(__I  uint32_t*)0xF804C0BCU) /**< \brief (ADC) Touchscreen Pressure Register */
  #define REG_ADC_TRGR   (*(__IO uint32_t*)0xF804C0C0U) /**< \brief (ADC) Trigger Register */
  #define REG_ADC_CVR    (*(__IO uint32_t*)0xF804C0D4U) /**< \brief (ADC) Correction Values Register */
  #define REG_ADC_CECR   (*(__IO uint32_t*)0xF804C0D8U) /**< \brief (ADC) Channel Error Correction Register */
  #define REG_ADC_TSCVR  (*(__IO uint32_t*)0xF804C0DCU) /**< \brief (ADC) Touchscreen Correction Values Register */
  #define REG_ADC_WPMR   (*(__IO uint32_t*)0xF804C0E4U) /**< \brief (ADC) Write Protection Mode Register */
  #define REG_ADC_WPSR   (*(__I  uint32_t*)0xF804C0E8U) /**< \brief (ADC) Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_ADC_INSTANCE_ */
