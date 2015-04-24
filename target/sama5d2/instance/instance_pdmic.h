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

#ifndef _SAMA5D2_PDMIC_INSTANCE_
#define _SAMA5D2_PDMIC_INSTANCE_

/* ========== Register definition for PDMIC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_PDMIC_CR                       (0xF8018000U) /**< \brief (PDMIC) Control Register */
  #define REG_PDMIC_MR                       (0xF8018004U) /**< \brief (PDMIC) Mode Register */
  #define REG_PDMIC_CDR                      (0xF8018014U) /**< \brief (PDMIC) Converted Data Register */
  #define REG_PDMIC_IER                      (0xF8018018U) /**< \brief (PDMIC) Interrupt Enable Register */
  #define REG_PDMIC_IDR                      (0xF801801CU) /**< \brief (PDMIC) Interrupt Disable Register */
  #define REG_PDMIC_IMR                      (0xF8018020U) /**< \brief (PDMIC) Interrupt Mask Register */
  #define REG_PDMIC_ISR                      (0xF8018024U) /**< \brief (PDMIC) Interrupt Status Register */
  #define REG_PDMIC_DSPR0                    (0xF8018058U) /**< \brief (PDMIC) DSP Configuration Register 0 */
  #define REG_PDMIC_DSPR1                    (0xF801805CU) /**< \brief (PDMIC) DSP Configuration Register 1 */
  #define REG_PDMIC_WPMR                     (0xF80180E4U) /**< \brief (PDMIC) Write Protection Mode Register */
  #define REG_PDMIC_WPSR                     (0xF80180E8U) /**< \brief (PDMIC) Write Protection Status Register */
  #define REG_PDMIC_VERSION                  (0xF80180FCU) /**< \brief (PDMIC) Version Register */
#else
  #define REG_PDMIC_CR      (*(__IO uint32_t*)0xF8018000U) /**< \brief (PDMIC) Control Register */
  #define REG_PDMIC_MR      (*(__IO uint32_t*)0xF8018004U) /**< \brief (PDMIC) Mode Register */
  #define REG_PDMIC_CDR     (*(__I  uint32_t*)0xF8018014U) /**< \brief (PDMIC) Converted Data Register */
  #define REG_PDMIC_IER     (*(__O  uint32_t*)0xF8018018U) /**< \brief (PDMIC) Interrupt Enable Register */
  #define REG_PDMIC_IDR     (*(__O  uint32_t*)0xF801801CU) /**< \brief (PDMIC) Interrupt Disable Register */
  #define REG_PDMIC_IMR     (*(__I  uint32_t*)0xF8018020U) /**< \brief (PDMIC) Interrupt Mask Register */
  #define REG_PDMIC_ISR     (*(__I  uint32_t*)0xF8018024U) /**< \brief (PDMIC) Interrupt Status Register */
  #define REG_PDMIC_DSPR0   (*(__IO uint32_t*)0xF8018058U) /**< \brief (PDMIC) DSP Configuration Register 0 */
  #define REG_PDMIC_DSPR1   (*(__IO uint32_t*)0xF801805CU) /**< \brief (PDMIC) DSP Configuration Register 1 */
  #define REG_PDMIC_WPMR    (*(__IO uint32_t*)0xF80180E4U) /**< \brief (PDMIC) Write Protection Mode Register */
  #define REG_PDMIC_WPSR    (*(__I  uint32_t*)0xF80180E8U) /**< \brief (PDMIC) Write Protection Status Register */
  #define REG_PDMIC_VERSION (*(__I  uint32_t*)0xF80180FCU) /**< \brief (PDMIC) Version Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_PDMIC_INSTANCE_ */
