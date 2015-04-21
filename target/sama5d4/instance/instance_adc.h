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

#ifndef _SAMA5D4_ADC_INSTANCE_
#define _SAMA5D4_ADC_INSTANCE_

/* ========== Register definition for ADC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_ADC_CR                      (0xFC034000U) /**< \brief (ADC) Control Register */
  #define REG_ADC_MR                      (0xFC034004U) /**< \brief (ADC) Mode Register */
  #define REG_ADC_SEQR1                   (0xFC034008U) /**< \brief (ADC) Channel Sequence Register 1 */
  #define REG_ADC_CHER                    (0xFC034010U) /**< \brief (ADC) Channel Enable Register */
  #define REG_ADC_CHDR                    (0xFC034014U) /**< \brief (ADC) Channel Disable Register */
  #define REG_ADC_CHSR                    (0xFC034018U) /**< \brief (ADC) Channel Status Register */
  #define REG_ADC_LCDR                    (0xFC034020U) /**< \brief (ADC) Last Converted Data Register */
  #define REG_ADC_IER                     (0xFC034024U) /**< \brief (ADC) Interrupt Enable Register */
  #define REG_ADC_IDR                     (0xFC034028U) /**< \brief (ADC) Interrupt Disable Register */
  #define REG_ADC_IMR                     (0xFC03402CU) /**< \brief (ADC) Interrupt Mask Register */
  #define REG_ADC_ISR                     (0xFC034030U) /**< \brief (ADC) Interrupt Status Register */
  #define REG_ADC_OVER                    (0xFC03403CU) /**< \brief (ADC) Overrun Status Register */
  #define REG_ADC_EMR                     (0xFC034040U) /**< \brief (ADC) Extended Mode Register */
  #define REG_ADC_CWR                     (0xFC034044U) /**< \brief (ADC) Compare Window Register */
  #define REG_ADC_CDR                     (0xFC034050U) /**< \brief (ADC) Channel Data Register */
  #define REG_ADC_ACR                     (0xFC034094U) /**< \brief (ADC) Analog Control Register */
  #define REG_ADC_TSMR                    (0xFC0340B0U) /**< \brief (ADC) Touchscreen Mode Register */
  #define REG_ADC_XPOSR                   (0xFC0340B4U) /**< \brief (ADC) Touchscreen X Position Register */
  #define REG_ADC_YPOSR                   (0xFC0340B8U) /**< \brief (ADC) Touchscreen Y Position Register */
  #define REG_ADC_PRESSR                  (0xFC0340BCU) /**< \brief (ADC) Touchscreen Pressure Register */
  #define REG_ADC_TRGR                    (0xFC0340C0U) /**< \brief (ADC) Trigger Register */
  #define REG_ADC_WPMR                    (0xFC0340E4U) /**< \brief (ADC) Write Protection Mode Register */
  #define REG_ADC_WPSR                    (0xFC0340E8U) /**< \brief (ADC) Write Protection Status Register */
#else
  #define REG_ADC_CR     (*(__O  uint32_t*)0xFC034000U) /**< \brief (ADC) Control Register */
  #define REG_ADC_MR     (*(__IO uint32_t*)0xFC034004U) /**< \brief (ADC) Mode Register */
  #define REG_ADC_SEQR1  (*(__IO uint32_t*)0xFC034008U) /**< \brief (ADC) Channel Sequence Register 1 */
  #define REG_ADC_CHER   (*(__O  uint32_t*)0xFC034010U) /**< \brief (ADC) Channel Enable Register */
  #define REG_ADC_CHDR   (*(__O  uint32_t*)0xFC034014U) /**< \brief (ADC) Channel Disable Register */
  #define REG_ADC_CHSR   (*(__I  uint32_t*)0xFC034018U) /**< \brief (ADC) Channel Status Register */
  #define REG_ADC_LCDR   (*(__I  uint32_t*)0xFC034020U) /**< \brief (ADC) Last Converted Data Register */
  #define REG_ADC_IER    (*(__O  uint32_t*)0xFC034024U) /**< \brief (ADC) Interrupt Enable Register */
  #define REG_ADC_IDR    (*(__O  uint32_t*)0xFC034028U) /**< \brief (ADC) Interrupt Disable Register */
  #define REG_ADC_IMR    (*(__I  uint32_t*)0xFC03402CU) /**< \brief (ADC) Interrupt Mask Register */
  #define REG_ADC_ISR    (*(__I  uint32_t*)0xFC034030U) /**< \brief (ADC) Interrupt Status Register */
  #define REG_ADC_OVER   (*(__I  uint32_t*)0xFC03403CU) /**< \brief (ADC) Overrun Status Register */
  #define REG_ADC_EMR    (*(__IO uint32_t*)0xFC034040U) /**< \brief (ADC) Extended Mode Register */
  #define REG_ADC_CWR    (*(__IO uint32_t*)0xFC034044U) /**< \brief (ADC) Compare Window Register */
  #define REG_ADC_CDR    (*(__I  uint32_t*)0xFC034050U) /**< \brief (ADC) Channel Data Register */
  #define REG_ADC_ACR    (*(__IO uint32_t*)0xFC034094U) /**< \brief (ADC) Analog Control Register */
  #define REG_ADC_TSMR   (*(__IO uint32_t*)0xFC0340B0U) /**< \brief (ADC) Touchscreen Mode Register */
  #define REG_ADC_XPOSR  (*(__I  uint32_t*)0xFC0340B4U) /**< \brief (ADC) Touchscreen X Position Register */
  #define REG_ADC_YPOSR  (*(__I  uint32_t*)0xFC0340B8U) /**< \brief (ADC) Touchscreen Y Position Register */
  #define REG_ADC_PRESSR (*(__I  uint32_t*)0xFC0340BCU) /**< \brief (ADC) Touchscreen Pressure Register */
  #define REG_ADC_TRGR   (*(__IO uint32_t*)0xFC0340C0U) /**< \brief (ADC) Trigger Register */
  #define REG_ADC_WPMR   (*(__IO uint32_t*)0xFC0340E4U) /**< \brief (ADC) Write Protection Mode Register */
  #define REG_ADC_WPSR   (*(__I  uint32_t*)0xFC0340E8U) /**< \brief (ADC) Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D4_ADC_INSTANCE_ */
