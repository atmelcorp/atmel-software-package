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

#ifndef _SAMA5D2_ICM_INSTANCE_
#define _SAMA5D2_ICM_INSTANCE_

/* ========== Register definition for ICM peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_ICM_CFG                       (0xF8040000U) /**< \brief (ICM) Configuration Register */
  #define REG_ICM_CTRL                      (0xF8040004U) /**< \brief (ICM) Control Register */
  #define REG_ICM_SR                        (0xF8040008U) /**< \brief (ICM) Status Register */
  #define REG_ICM_IER                       (0xF8040010U) /**< \brief (ICM) Interrupt Enable Register */
  #define REG_ICM_IDR                       (0xF8040014U) /**< \brief (ICM) Interrupt Disable Register */
  #define REG_ICM_IMR                       (0xF8040018U) /**< \brief (ICM) Interrupt Mask Register */
  #define REG_ICM_ISR                       (0xF804001CU) /**< \brief (ICM) Interrupt Status Register */
  #define REG_ICM_UASR                      (0xF8040020U) /**< \brief (ICM) Undefined Access Status Register */
  #define REG_ICM_DSCR                      (0xF8040030U) /**< \brief (ICM) Region Descriptor Area Start Address Register */
  #define REG_ICM_HASH                      (0xF8040034U) /**< \brief (ICM) Region Hash Area Start Address Register */
  #define REG_ICM_UIHVAL                    (0xF8040038U) /**< \brief (ICM) User Initial Hash Value 0 Register */
  #define REG_ICM_ADDRSIZE                  (0xF80400ECU) /**< \brief (ICM) Address Size Register */
  #define REG_ICM_IPNAME                    (0xF80400F0U) /**< \brief (ICM) IP Name 1 Register */
  #define REG_ICM_FEATURES                  (0xF80400F8U) /**< \brief (ICM) Feature Register */
  #define REG_ICM_VERSION                   (0xF80400FCU) /**< \brief (ICM) Version Register */
#else
  #define REG_ICM_CFG      (*(__IO uint32_t*)0xF8040000U) /**< \brief (ICM) Configuration Register */
  #define REG_ICM_CTRL     (*(__O  uint32_t*)0xF8040004U) /**< \brief (ICM) Control Register */
  #define REG_ICM_SR       (*(__O  uint32_t*)0xF8040008U) /**< \brief (ICM) Status Register */
  #define REG_ICM_IER      (*(__O  uint32_t*)0xF8040010U) /**< \brief (ICM) Interrupt Enable Register */
  #define REG_ICM_IDR      (*(__O  uint32_t*)0xF8040014U) /**< \brief (ICM) Interrupt Disable Register */
  #define REG_ICM_IMR      (*(__I  uint32_t*)0xF8040018U) /**< \brief (ICM) Interrupt Mask Register */
  #define REG_ICM_ISR      (*(__I  uint32_t*)0xF804001CU) /**< \brief (ICM) Interrupt Status Register */
  #define REG_ICM_UASR     (*(__I  uint32_t*)0xF8040020U) /**< \brief (ICM) Undefined Access Status Register */
  #define REG_ICM_DSCR     (*(__IO uint32_t*)0xF8040030U) /**< \brief (ICM) Region Descriptor Area Start Address Register */
  #define REG_ICM_HASH     (*(__IO uint32_t*)0xF8040034U) /**< \brief (ICM) Region Hash Area Start Address Register */
  #define REG_ICM_UIHVAL   (*(__O  uint32_t*)0xF8040038U) /**< \brief (ICM) User Initial Hash Value 0 Register */
  #define REG_ICM_ADDRSIZE (*(__I  uint32_t*)0xF80400ECU) /**< \brief (ICM) Address Size Register */
  #define REG_ICM_IPNAME   (*(__I  uint32_t*)0xF80400F0U) /**< \brief (ICM) IP Name 1 Register */
  #define REG_ICM_FEATURES (*(__I  uint32_t*)0xF80400F8U) /**< \brief (ICM) Feature Register */
  #define REG_ICM_VERSION  (*(__I  uint32_t*)0xF80400FCU) /**< \brief (ICM) Version Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_ICM_INSTANCE_ */
