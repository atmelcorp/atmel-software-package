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

#ifndef _SAMA5D4_SAIC_INSTANCE_
#define _SAMA5D4_SAIC_INSTANCE_

/* ========== Register definition for SAIC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_SAIC_SSR                    (0xFC068400U) /**< \brief (SAIC) Source Select Register */
#define REG_SAIC_SMR                    (0xFC068404U) /**< \brief (SAIC) Source Mode Register */
#define REG_SAIC_SVR                    (0xFC068408U) /**< \brief (SAIC) Source Vector Register */
#define REG_SAIC_IVR                    (0xFC068410U) /**< \brief (SAIC) Interrupt Vector Register */
#define REG_SAIC_FVR                    (0xFC068414U) /**< \brief (SAIC) FIQ Vector Register */
#define REG_SAIC_ISR                    (0xFC068418U) /**< \brief (SAIC) Interrupt Status Register */
#define REG_SAIC_IPR0                   (0xFC068420U) /**< \brief (SAIC) Interrupt Pending Register 0 */
#define REG_SAIC_IPR1                   (0xFC068424U) /**< \brief (SAIC) Interrupt Pending Register 1 */
#define REG_SAIC_IPR2                   (0xFC068428U) /**< \brief (SAIC) Interrupt Pending Register 2 */
#define REG_SAIC_IPR3                   (0xFC06842CU) /**< \brief (SAIC) Interrupt Pending Register 3 */
#define REG_SAIC_IMR                    (0xFC068430U) /**< \brief (SAIC) Interrupt Mask Register */
#define REG_SAIC_CISR                   (0xFC068434U) /**< \brief (SAIC) Core Interrupt Status Register */
#define REG_SAIC_EOICR                  (0xFC068438U) /**< \brief (SAIC) End of Interrupt Command Register */
#define REG_SAIC_SPU                    (0xFC06843CU) /**< \brief (SAIC) Spurious Interrupt Vector Register */
#define REG_SAIC_IECR                   (0xFC068440U) /**< \brief (SAIC) Interrupt Enable Command Register */
#define REG_SAIC_IDCR                   (0xFC068444U) /**< \brief (SAIC) Interrupt Disable Command Register */
#define REG_SAIC_ICCR                   (0xFC068448U) /**< \brief (SAIC) Interrupt Clear Command Register */
#define REG_SAIC_ISCR                   (0xFC06844CU) /**< \brief (SAIC) Interrupt Set Command Register */
#define REG_SAIC_DCR                    (0xFC06846CU) /**< \brief (SAIC) Debug Control Register */
#define REG_SAIC_WPMR                   (0xFC0684E4U) /**< \brief (SAIC) Write Protection Mode Register */
#define REG_SAIC_WPSR                   (0xFC0684E8U) /**< \brief (SAIC) Write Protection Status Register */
#else
#define REG_SAIC_SSR   (*(__IO uint32_t*)0xFC068400U) /**< \brief (SAIC) Source Select Register */
#define REG_SAIC_SMR   (*(__IO uint32_t*)0xFC068404U) /**< \brief (SAIC) Source Mode Register */
#define REG_SAIC_SVR   (*(__IO uint32_t*)0xFC068408U) /**< \brief (SAIC) Source Vector Register */
#define REG_SAIC_IVR   (*(__I  uint32_t*)0xFC068410U) /**< \brief (SAIC) Interrupt Vector Register */
#define REG_SAIC_FVR   (*(__I  uint32_t*)0xFC068414U) /**< \brief (SAIC) FIQ Vector Register */
#define REG_SAIC_ISR   (*(__I  uint32_t*)0xFC068418U) /**< \brief (SAIC) Interrupt Status Register */
#define REG_SAIC_IPR0  (*(__I  uint32_t*)0xFC068420U) /**< \brief (SAIC) Interrupt Pending Register 0 */
#define REG_SAIC_IPR1  (*(__I  uint32_t*)0xFC068424U) /**< \brief (SAIC) Interrupt Pending Register 1 */
#define REG_SAIC_IPR2  (*(__I  uint32_t*)0xFC068428U) /**< \brief (SAIC) Interrupt Pending Register 2 */
#define REG_SAIC_IPR3  (*(__I  uint32_t*)0xFC06842CU) /**< \brief (SAIC) Interrupt Pending Register 3 */
#define REG_SAIC_IMR   (*(__I  uint32_t*)0xFC068430U) /**< \brief (SAIC) Interrupt Mask Register */
#define REG_SAIC_CISR  (*(__I  uint32_t*)0xFC068434U) /**< \brief (SAIC) Core Interrupt Status Register */
#define REG_SAIC_EOICR (*(__O  uint32_t*)0xFC068438U) /**< \brief (SAIC) End of Interrupt Command Register */
#define REG_SAIC_SPU   (*(__IO uint32_t*)0xFC06843CU) /**< \brief (SAIC) Spurious Interrupt Vector Register */
#define REG_SAIC_IECR  (*(__O  uint32_t*)0xFC068440U) /**< \brief (SAIC) Interrupt Enable Command Register */
#define REG_SAIC_IDCR  (*(__O  uint32_t*)0xFC068444U) /**< \brief (SAIC) Interrupt Disable Command Register */
#define REG_SAIC_ICCR  (*(__O  uint32_t*)0xFC068448U) /**< \brief (SAIC) Interrupt Clear Command Register */
#define REG_SAIC_ISCR  (*(__O  uint32_t*)0xFC06844CU) /**< \brief (SAIC) Interrupt Set Command Register */
#define REG_SAIC_DCR   (*(__IO uint32_t*)0xFC06846CU) /**< \brief (SAIC) Debug Control Register */
#define REG_SAIC_WPMR  (*(__IO uint32_t*)0xFC0684E4U) /**< \brief (SAIC) Write Protection Mode Register */
#define REG_SAIC_WPSR  (*(__I  uint32_t*)0xFC0684E8U) /**< \brief (SAIC) Write Protection Status Register */
#endif				/* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif				/* _SAMA5D4_SAIC_INSTANCE_ */
