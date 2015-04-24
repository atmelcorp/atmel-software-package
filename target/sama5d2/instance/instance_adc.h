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

#ifndef _SAMA5D2_ADC_INSTANCE_
#define _SAMA5D2_ADC_INSTANCE_

/* ========== Register definition for ADC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_ADC_CR                       (0xFC030000U) /**< \brief (ADC) Control Register */
  #define REG_ADC_MR                       (0xFC030004U) /**< \brief (ADC) Mode Register */
  #define REG_ADC_SEQR1                    (0xFC030008U) /**< \brief (ADC) Channel Sequence Register 1 */
  #define REG_ADC_SEQR2                    (0xFC03000CU) /**< \brief (ADC) Channel Sequence Register 2 */
  #define REG_ADC_CHER                     (0xFC030010U) /**< \brief (ADC) Channel Enable Register */
  #define REG_ADC_CHDR                     (0xFC030014U) /**< \brief (ADC) Channel Disable Register */
  #define REG_ADC_CHSR                     (0xFC030018U) /**< \brief (ADC) Channel Status Register */
  #define REG_ADC_LCDR                     (0xFC030020U) /**< \brief (ADC) Last Converted Data Register */
  #define REG_ADC_IER                      (0xFC030024U) /**< \brief (ADC) Interrupt Enable Register */
  #define REG_ADC_IDR                      (0xFC030028U) /**< \brief (ADC) Interrupt Disable Register */
  #define REG_ADC_IMR                      (0xFC03002CU) /**< \brief (ADC) Interrupt Mask Register */
  #define REG_ADC_ISR                      (0xFC030030U) /**< \brief (ADC) Interrupt Status Register */
  #define REG_ADC_LCTMR                    (0xFC030034U) /**< \brief (ADC) Last Channel Trigger Mode Register */
  #define REG_ADC_LCCWR                    (0xFC030038U) /**< \brief (ADC) Last Channel Compare Window Register */
  #define REG_ADC_OVER                     (0xFC03003CU) /**< \brief (ADC) Overrun Status Register */
  #define REG_ADC_EMR                      (0xFC030040U) /**< \brief (ADC) Extended Mode Register */
  #define REG_ADC_CWR                      (0xFC030044U) /**< \brief (ADC) Compare Window Register */
  #define REG_ADC_CGR                      (0xFC030048U) /**< \brief (ADC) Channel Gain Register */
  #define REG_ADC_COR                      (0xFC03004CU) /**< \brief (ADC) Channel Offset Register */
  #define REG_ADC_CDR0                     (0xFC030050U) /**< \brief (ADC) Channel Data Register 0 */
  #define REG_ADC_CDR1                     (0xFC030054U) /**< \brief (ADC) Channel Data Register 1 */
  #define REG_ADC_CDR2                     (0xFC030058U) /**< \brief (ADC) Channel Data Register 2 */
  #define REG_ADC_CDR3                     (0xFC03005CU) /**< \brief (ADC) Channel Data Register 3 */
  #define REG_ADC_CDR4                     (0xFC030060U) /**< \brief (ADC) Channel Data Register 4 */
  #define REG_ADC_CDR5                     (0xFC030064U) /**< \brief (ADC) Channel Data Register 5 */
  #define REG_ADC_CDR6                     (0xFC030068U) /**< \brief (ADC) Channel Data Register 6 */
  #define REG_ADC_CDR7                     (0xFC03006CU) /**< \brief (ADC) Channel Data Register 7 */
  #define REG_ADC_CDR8                     (0xFC030070U) /**< \brief (ADC) Channel Data Register 8 */
  #define REG_ADC_CDR9                     (0xFC030074U) /**< \brief (ADC) Channel Data Register 9 */
  #define REG_ADC_CDR10                    (0xFC030078U) /**< \brief (ADC) Channel Data Register 10 */
  #define REG_ADC_CDR11                    (0xFC03007CU) /**< \brief (ADC) Channel Data Register 11 */
  #define REG_ADC_CDR12                    (0xFC030080U) /**< \brief (ADC) Channel Data Register 12 */
  #define REG_ADC_CDR13                    (0xFC030084U) /**< \brief (ADC) Channel Data Register 13 */
  #define REG_ADC_CDR14                    (0xFC030088U) /**< \brief (ADC) Channel Data Register 14 */
  #define REG_ADC_CDR15                    (0xFC03008CU) /**< \brief (ADC) Channel Data Register 15 */
  #define REG_ADC_CDR16                    (0xFC030090U) /**< \brief (ADC) Channel Data Register 16 */
  #define REG_ADC_ACR                      (0xFC030094U) /**< \brief (ADC) Analog Control Register */
  #define REG_ADC_TSMR                     (0xFC0300B0U) /**< \brief (ADC) Touchscreen Mode Register */
  #define REG_ADC_XPOSR                    (0xFC0300B4U) /**< \brief (ADC) Touchscreen X Position Register */
  #define REG_ADC_YPOSR                    (0xFC0300B8U) /**< \brief (ADC) Touchscreen Y Position Register */
  #define REG_ADC_PRESSR                   (0xFC0300BCU) /**< \brief (ADC) Touchscreen Pressure Register */
  #define REG_ADC_TRGR                     (0xFC0300C0U) /**< \brief (ADC) Trigger Register */
  #define REG_ADC_COSR                     (0xFC0300D0U) /**< \brief (ADC) Correction Select Register */
  #define REG_ADC_CVR                      (0xFC0300D4U) /**< \brief (ADC) Correction Values Register */
  #define REG_ADC_CECR                     (0xFC0300D8U) /**< \brief (ADC) Channel Error Correction Register */
  #define REG_ADC_WPMR                     (0xFC0300E4U) /**< \brief (ADC) Write Protection Mode Register */
  #define REG_ADC_WPSR                     (0xFC0300E8U) /**< \brief (ADC) Write Protection Status Register */
  #define REG_ADC_VERSION                  (0xFC0300FCU) /**< \brief (ADC) Version Register */
#else
  #define REG_ADC_CR      (*(__O  uint32_t*)0xFC030000U) /**< \brief (ADC) Control Register */
  #define REG_ADC_MR      (*(__IO uint32_t*)0xFC030004U) /**< \brief (ADC) Mode Register */
  #define REG_ADC_SEQR1   (*(__IO uint32_t*)0xFC030008U) /**< \brief (ADC) Channel Sequence Register 1 */
  #define REG_ADC_SEQR2   (*(__IO uint32_t*)0xFC03000CU) /**< \brief (ADC) Channel Sequence Register 2 */
  #define REG_ADC_CHER    (*(__O  uint32_t*)0xFC030010U) /**< \brief (ADC) Channel Enable Register */
  #define REG_ADC_CHDR    (*(__O  uint32_t*)0xFC030014U) /**< \brief (ADC) Channel Disable Register */
  #define REG_ADC_CHSR    (*(__I  uint32_t*)0xFC030018U) /**< \brief (ADC) Channel Status Register */
  #define REG_ADC_LCDR    (*(__I  uint32_t*)0xFC030020U) /**< \brief (ADC) Last Converted Data Register */
  #define REG_ADC_IER     (*(__O  uint32_t*)0xFC030024U) /**< \brief (ADC) Interrupt Enable Register */
  #define REG_ADC_IDR     (*(__O  uint32_t*)0xFC030028U) /**< \brief (ADC) Interrupt Disable Register */
  #define REG_ADC_IMR     (*(__I  uint32_t*)0xFC03002CU) /**< \brief (ADC) Interrupt Mask Register */
  #define REG_ADC_ISR     (*(__I  uint32_t*)0xFC030030U) /**< \brief (ADC) Interrupt Status Register */
  #define REG_ADC_LCTMR   (*(__IO uint32_t*)0xFC030034U) /**< \brief (ADC) Last Channel Trigger Mode Register */
  #define REG_ADC_LCCWR   (*(__IO uint32_t*)0xFC030038U) /**< \brief (ADC) Last Channel Compare Window Register */
  #define REG_ADC_OVER    (*(__I  uint32_t*)0xFC03003CU) /**< \brief (ADC) Overrun Status Register */
  #define REG_ADC_EMR     (*(__IO uint32_t*)0xFC030040U) /**< \brief (ADC) Extended Mode Register */
  #define REG_ADC_CWR     (*(__IO uint32_t*)0xFC030044U) /**< \brief (ADC) Compare Window Register */
  #define REG_ADC_CGR     (*(__IO uint32_t*)0xFC030048U) /**< \brief (ADC) Channel Gain Register */
  #define REG_ADC_COR     (*(__IO uint32_t*)0xFC03004CU) /**< \brief (ADC) Channel Offset Register */
  #define REG_ADC_CDR0    (*(__I  uint32_t*)0xFC030050U) /**< \brief (ADC) Channel Data Register 0 */
  #define REG_ADC_CDR1    (*(__I  uint32_t*)0xFC030054U) /**< \brief (ADC) Channel Data Register 1 */
  #define REG_ADC_CDR2    (*(__I  uint32_t*)0xFC030058U) /**< \brief (ADC) Channel Data Register 2 */
  #define REG_ADC_CDR3    (*(__I  uint32_t*)0xFC03005CU) /**< \brief (ADC) Channel Data Register 3 */
  #define REG_ADC_CDR4    (*(__I  uint32_t*)0xFC030060U) /**< \brief (ADC) Channel Data Register 4 */
  #define REG_ADC_CDR5    (*(__I  uint32_t*)0xFC030064U) /**< \brief (ADC) Channel Data Register 5 */
  #define REG_ADC_CDR6    (*(__I  uint32_t*)0xFC030068U) /**< \brief (ADC) Channel Data Register 6 */
  #define REG_ADC_CDR7    (*(__I  uint32_t*)0xFC03006CU) /**< \brief (ADC) Channel Data Register 7 */
  #define REG_ADC_CDR8    (*(__I  uint32_t*)0xFC030070U) /**< \brief (ADC) Channel Data Register 8 */
  #define REG_ADC_CDR9    (*(__I  uint32_t*)0xFC030074U) /**< \brief (ADC) Channel Data Register 9 */
  #define REG_ADC_CDR10   (*(__I  uint32_t*)0xFC030078U) /**< \brief (ADC) Channel Data Register 10 */
  #define REG_ADC_CDR11   (*(__I  uint32_t*)0xFC03007CU) /**< \brief (ADC) Channel Data Register 11 */
  #define REG_ADC_CDR12   (*(__I  uint32_t*)0xFC030080U) /**< \brief (ADC) Channel Data Register 12 */
  #define REG_ADC_CDR13   (*(__I  uint32_t*)0xFC030084U) /**< \brief (ADC) Channel Data Register 13 */
  #define REG_ADC_CDR14   (*(__I  uint32_t*)0xFC030088U) /**< \brief (ADC) Channel Data Register 14 */
  #define REG_ADC_CDR15   (*(__I  uint32_t*)0xFC03008CU) /**< \brief (ADC) Channel Data Register 15 */
  #define REG_ADC_CDR16   (*(__I  uint32_t*)0xFC030090U) /**< \brief (ADC) Channel Data Register 16 */
  #define REG_ADC_ACR     (*(__IO uint32_t*)0xFC030094U) /**< \brief (ADC) Analog Control Register */
  #define REG_ADC_TSMR    (*(__IO uint32_t*)0xFC0300B0U) /**< \brief (ADC) Touchscreen Mode Register */
  #define REG_ADC_XPOSR   (*(__I  uint32_t*)0xFC0300B4U) /**< \brief (ADC) Touchscreen X Position Register */
  #define REG_ADC_YPOSR   (*(__I  uint32_t*)0xFC0300B8U) /**< \brief (ADC) Touchscreen Y Position Register */
  #define REG_ADC_PRESSR  (*(__I  uint32_t*)0xFC0300BCU) /**< \brief (ADC) Touchscreen Pressure Register */
  #define REG_ADC_TRGR    (*(__IO uint32_t*)0xFC0300C0U) /**< \brief (ADC) Trigger Register */
  #define REG_ADC_COSR    (*(__IO uint32_t*)0xFC0300D0U) /**< \brief (ADC) Correction Select Register */
  #define REG_ADC_CVR     (*(__IO uint32_t*)0xFC0300D4U) /**< \brief (ADC) Correction Values Register */
  #define REG_ADC_CECR    (*(__IO uint32_t*)0xFC0300D8U) /**< \brief (ADC) Channel Error Correction Register */
  #define REG_ADC_WPMR    (*(__IO uint32_t*)0xFC0300E4U) /**< \brief (ADC) Write Protection Mode Register */
  #define REG_ADC_WPSR    (*(__I  uint32_t*)0xFC0300E8U) /**< \brief (ADC) Write Protection Status Register */
  #define REG_ADC_VERSION (*(__I  uint32_t*)0xFC0300FCU) /**< \brief (ADC) Version Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_ADC_INSTANCE_ */
