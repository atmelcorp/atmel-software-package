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

#ifndef _SAMA5D4_SFC_INSTANCE_
#define _SAMA5D4_SFC_INSTANCE_

/* ========== Register definition for SFC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_SFC_KR                   (0xFC060000U) /**< \brief (SFC) SFC Key Register */
#define REG_SFC_MR                   (0xFC060004U) /**< \brief (SFC) SFC Mode Register */
#define REG_SFC_IER                  (0xFC060010U) /**< \brief (SFC) SFC Interrupt Enable Register */
#define REG_SFC_IDR                  (0xFC060014U) /**< \brief (SFC) SFC Interrupt Disable Register */
#define REG_SFC_IMR                  (0xFC060018U) /**< \brief (SFC) SFC Interrupt Mask Register */
#define REG_SFC_SR                   (0xFC06001CU) /**< \brief (SFC) SFC Status Register */
#define REG_SFC_DR                   (0xFC060020U) /**< \brief (SFC) SFC Data Register */
#else
#define REG_SFC_KR  (*(__O  uint32_t*)0xFC060000U) /**< \brief (SFC) SFC Key Register */
#define REG_SFC_MR  (*(__IO uint32_t*)0xFC060004U) /**< \brief (SFC) SFC Mode Register */
#define REG_SFC_IER (*(__IO uint32_t*)0xFC060010U) /**< \brief (SFC) SFC Interrupt Enable Register */
#define REG_SFC_IDR (*(__IO uint32_t*)0xFC060014U) /**< \brief (SFC) SFC Interrupt Disable Register */
#define REG_SFC_IMR (*(__I  uint32_t*)0xFC060018U) /**< \brief (SFC) SFC Interrupt Mask Register */
#define REG_SFC_SR  (*(__I  uint32_t*)0xFC06001CU) /**< \brief (SFC) SFC Status Register */
#define REG_SFC_DR  (*(__IO uint32_t*)0xFC060020U) /**< \brief (SFC) SFC Data Register */
#endif				/* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif				/* _SAMA5D4_SFC_INSTANCE_ */
