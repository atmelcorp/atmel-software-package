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

#ifndef _SAMA5D4_DBGU_INSTANCE_
#define _SAMA5D4_DBGU_INSTANCE_

/* ========== Register definition for DBGU peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_DBGU_CR                    (0xFC069000U) /**< \brief (DBGU) Control Register */
  #define REG_DBGU_MR                    (0xFC069004U) /**< \brief (DBGU) Mode Register */
  #define REG_DBGU_IER                   (0xFC069008U) /**< \brief (DBGU) Interrupt Enable Register */
  #define REG_DBGU_IDR                   (0xFC06900CU) /**< \brief (DBGU) Interrupt Disable Register */
  #define REG_DBGU_IMR                   (0xFC069010U) /**< \brief (DBGU) Interrupt Mask Register */
  #define REG_DBGU_SR                    (0xFC069014U) /**< \brief (DBGU) Status Register */
  #define REG_DBGU_RHR                   (0xFC069018U) /**< \brief (DBGU) Receive Holding Register */
  #define REG_DBGU_THR                   (0xFC06901CU) /**< \brief (DBGU) Transmit Holding Register */
  #define REG_DBGU_BRGR                  (0xFC069020U) /**< \brief (DBGU) Baud Rate Generator Register */
  #define REG_DBGU_CIDR                  (0xFC069040U) /**< \brief (DBGU) Chip ID Register */
  #define REG_DBGU_EXID                  (0xFC069044U) /**< \brief (DBGU) Chip ID Extension Register */
  #define REG_DBGU_FNR                   (0xFC069048U) /**< \brief (DBGU) Force NTRST Register */
#else
  #define REG_DBGU_CR   (*(__O  uint32_t*)0xFC069000U) /**< \brief (DBGU) Control Register */
  #define REG_DBGU_MR   (*(__IO uint32_t*)0xFC069004U) /**< \brief (DBGU) Mode Register */
  #define REG_DBGU_IER  (*(__O  uint32_t*)0xFC069008U) /**< \brief (DBGU) Interrupt Enable Register */
  #define REG_DBGU_IDR  (*(__O  uint32_t*)0xFC06900CU) /**< \brief (DBGU) Interrupt Disable Register */
  #define REG_DBGU_IMR  (*(__I  uint32_t*)0xFC069010U) /**< \brief (DBGU) Interrupt Mask Register */
  #define REG_DBGU_SR   (*(__I  uint32_t*)0xFC069014U) /**< \brief (DBGU) Status Register */
  #define REG_DBGU_RHR  (*(__I  uint32_t*)0xFC069018U) /**< \brief (DBGU) Receive Holding Register */
  #define REG_DBGU_THR  (*(__O  uint32_t*)0xFC06901CU) /**< \brief (DBGU) Transmit Holding Register */
  #define REG_DBGU_BRGR (*(__IO uint32_t*)0xFC069020U) /**< \brief (DBGU) Baud Rate Generator Register */
  #define REG_DBGU_CIDR (*(__I  uint32_t*)0xFC069040U) /**< \brief (DBGU) Chip ID Register */
  #define REG_DBGU_EXID (*(__I  uint32_t*)0xFC069044U) /**< \brief (DBGU) Chip ID Extension Register */
  #define REG_DBGU_FNR  (*(__IO uint32_t*)0xFC069048U) /**< \brief (DBGU) Force NTRST Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D4_DBGU_INSTANCE_ */
