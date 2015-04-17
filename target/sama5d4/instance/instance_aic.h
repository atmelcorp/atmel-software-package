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

#ifndef _SAMA5D4_AIC_INSTANCE_
#define _SAMA5D4_AIC_INSTANCE_

/* ========== Register definition for AIC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_AIC_SSR                    (0xFC06E000U) /**< \brief (AIC) Source Select Register */
  #define REG_AIC_SMR                    (0xFC06E004U) /**< \brief (AIC) Source Mode Register */
  #define REG_AIC_SVR                    (0xFC06E008U) /**< \brief (AIC) Source Vector Register */
  #define REG_AIC_IVR                    (0xFC06E010U) /**< \brief (AIC) Interrupt Vector Register */
  #define REG_AIC_FVR                    (0xFC06E014U) /**< \brief (AIC) FIQ Vector Register */
  #define REG_AIC_ISR                    (0xFC06E018U) /**< \brief (AIC) Interrupt Status Register */
  #define REG_AIC_IPR0                   (0xFC06E020U) /**< \brief (AIC) Interrupt Pending Register 0 */
  #define REG_AIC_IPR1                   (0xFC06E024U) /**< \brief (AIC) Interrupt Pending Register 1 */
  #define REG_AIC_IPR2                   (0xFC06E028U) /**< \brief (AIC) Interrupt Pending Register 2 */
  #define REG_AIC_IPR3                   (0xFC06E02CU) /**< \brief (AIC) Interrupt Pending Register 3 */
  #define REG_AIC_IMR                    (0xFC06E030U) /**< \brief (AIC) Interrupt Mask Register */
  #define REG_AIC_CISR                   (0xFC06E034U) /**< \brief (AIC) Core Interrupt Status Register */
  #define REG_AIC_EOICR                  (0xFC06E038U) /**< \brief (AIC) End of Interrupt Command Register */
  #define REG_AIC_SPU                    (0xFC06E03CU) /**< \brief (AIC) Spurious Interrupt Vector Register */
  #define REG_AIC_IECR                   (0xFC06E040U) /**< \brief (AIC) Interrupt Enable Command Register */
  #define REG_AIC_IDCR                   (0xFC06E044U) /**< \brief (AIC) Interrupt Disable Command Register */
  #define REG_AIC_ICCR                   (0xFC06E048U) /**< \brief (AIC) Interrupt Clear Command Register */
  #define REG_AIC_ISCR                   (0xFC06E04CU) /**< \brief (AIC) Interrupt Set Command Register */
  #define REG_AIC_DCR                    (0xFC06E06CU) /**< \brief (AIC) Debug Control Register */
  #define REG_AIC_WPMR                   (0xFC06E0E4U) /**< \brief (AIC) Write Protection Mode Register */
  #define REG_AIC_WPSR                   (0xFC06E0E8U) /**< \brief (AIC) Write Protection Status Register */
#else
  #define REG_AIC_SSR   (*(__IO uint32_t*)0xFC06E000U) /**< \brief (AIC) Source Select Register */
  #define REG_AIC_SMR   (*(__IO uint32_t*)0xFC06E004U) /**< \brief (AIC) Source Mode Register */
  #define REG_AIC_SVR   (*(__IO uint32_t*)0xFC06E008U) /**< \brief (AIC) Source Vector Register */
  #define REG_AIC_IVR   (*(__I  uint32_t*)0xFC06E010U) /**< \brief (AIC) Interrupt Vector Register */
  #define REG_AIC_FVR   (*(__I  uint32_t*)0xFC06E014U) /**< \brief (AIC) FIQ Vector Register */
  #define REG_AIC_ISR   (*(__I  uint32_t*)0xFC06E018U) /**< \brief (AIC) Interrupt Status Register */
  #define REG_AIC_IPR0  (*(__I  uint32_t*)0xFC06E020U) /**< \brief (AIC) Interrupt Pending Register 0 */
  #define REG_AIC_IPR1  (*(__I  uint32_t*)0xFC06E024U) /**< \brief (AIC) Interrupt Pending Register 1 */
  #define REG_AIC_IPR2  (*(__I  uint32_t*)0xFC06E028U) /**< \brief (AIC) Interrupt Pending Register 2 */
  #define REG_AIC_IPR3  (*(__I  uint32_t*)0xFC06E02CU) /**< \brief (AIC) Interrupt Pending Register 3 */
  #define REG_AIC_IMR   (*(__I  uint32_t*)0xFC06E030U) /**< \brief (AIC) Interrupt Mask Register */
  #define REG_AIC_CISR  (*(__I  uint32_t*)0xFC06E034U) /**< \brief (AIC) Core Interrupt Status Register */
  #define REG_AIC_EOICR (*(__O  uint32_t*)0xFC06E038U) /**< \brief (AIC) End of Interrupt Command Register */
  #define REG_AIC_SPU   (*(__IO uint32_t*)0xFC06E03CU) /**< \brief (AIC) Spurious Interrupt Vector Register */
  #define REG_AIC_IECR  (*(__O  uint32_t*)0xFC06E040U) /**< \brief (AIC) Interrupt Enable Command Register */
  #define REG_AIC_IDCR  (*(__O  uint32_t*)0xFC06E044U) /**< \brief (AIC) Interrupt Disable Command Register */
  #define REG_AIC_ICCR  (*(__O  uint32_t*)0xFC06E048U) /**< \brief (AIC) Interrupt Clear Command Register */
  #define REG_AIC_ISCR  (*(__O  uint32_t*)0xFC06E04CU) /**< \brief (AIC) Interrupt Set Command Register */
  #define REG_AIC_DCR   (*(__IO uint32_t*)0xFC06E06CU) /**< \brief (AIC) Debug Control Register */
  #define REG_AIC_WPMR  (*(__IO uint32_t*)0xFC06E0E4U) /**< \brief (AIC) Write Protection Mode Register */
  #define REG_AIC_WPSR  (*(__I  uint32_t*)0xFC06E0E8U) /**< \brief (AIC) Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D4_AIC_INSTANCE_ */
