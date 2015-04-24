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

#ifndef _SAMA5D2_QSPI1_INSTANCE_
#define _SAMA5D2_QSPI1_INSTANCE_

/* ========== Register definition for QSPI1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_QSPI1_CR                       (0xF0024000U) /**< \brief (QSPI1) Control Register */
  #define REG_QSPI1_MR                       (0xF0024004U) /**< \brief (QSPI1) Mode Register */
  #define REG_QSPI1_RDR                      (0xF0024008U) /**< \brief (QSPI1) Receive Data Register */
  #define REG_QSPI1_TDR                      (0xF002400CU) /**< \brief (QSPI1) Transmit Data Register */
  #define REG_QSPI1_SR                       (0xF0024010U) /**< \brief (QSPI1) Status Register */
  #define REG_QSPI1_IER                      (0xF0024014U) /**< \brief (QSPI1) Interrupt Enable Register */
  #define REG_QSPI1_IDR                      (0xF0024018U) /**< \brief (QSPI1) Interrupt Disable Register */
  #define REG_QSPI1_IMR                      (0xF002401CU) /**< \brief (QSPI1) Interrupt Mask Register */
  #define REG_QSPI1_SCR                      (0xF0024020U) /**< \brief (QSPI1) Serial Clock Register */
  #define REG_QSPI1_IAR                      (0xF0024030U) /**< \brief (QSPI1) Instruction Address Register */
  #define REG_QSPI1_ICR                      (0xF0024034U) /**< \brief (QSPI1) Instruction Code Register */
  #define REG_QSPI1_IFR                      (0xF0024038U) /**< \brief (QSPI1) Instruction Frame Register */
  #define REG_QSPI1_SMR                      (0xF0024040U) /**< \brief (QSPI1) Scrambling Mode Register */
  #define REG_QSPI1_SKR                      (0xF0024044U) /**< \brief (QSPI1) Scrambling Key Register */
  #define REG_QSPI1_WPMR                     (0xF00240E4U) /**< \brief (QSPI1) Write Protection Mode Register */
  #define REG_QSPI1_WPSR                     (0xF00240E8U) /**< \brief (QSPI1) Write Protection Status Register */
  #define REG_QSPI1_VERSION                  (0xF00240FCU) /**< \brief (QSPI1) Version Register */
#else
  #define REG_QSPI1_CR      (*(__O  uint32_t*)0xF0024000U) /**< \brief (QSPI1) Control Register */
  #define REG_QSPI1_MR      (*(__IO uint32_t*)0xF0024004U) /**< \brief (QSPI1) Mode Register */
  #define REG_QSPI1_RDR     (*(__I  uint32_t*)0xF0024008U) /**< \brief (QSPI1) Receive Data Register */
  #define REG_QSPI1_TDR     (*(__O  uint32_t*)0xF002400CU) /**< \brief (QSPI1) Transmit Data Register */
  #define REG_QSPI1_SR      (*(__I  uint32_t*)0xF0024010U) /**< \brief (QSPI1) Status Register */
  #define REG_QSPI1_IER     (*(__O  uint32_t*)0xF0024014U) /**< \brief (QSPI1) Interrupt Enable Register */
  #define REG_QSPI1_IDR     (*(__O  uint32_t*)0xF0024018U) /**< \brief (QSPI1) Interrupt Disable Register */
  #define REG_QSPI1_IMR     (*(__I  uint32_t*)0xF002401CU) /**< \brief (QSPI1) Interrupt Mask Register */
  #define REG_QSPI1_SCR     (*(__IO uint32_t*)0xF0024020U) /**< \brief (QSPI1) Serial Clock Register */
  #define REG_QSPI1_IAR     (*(__IO uint32_t*)0xF0024030U) /**< \brief (QSPI1) Instruction Address Register */
  #define REG_QSPI1_ICR     (*(__IO uint32_t*)0xF0024034U) /**< \brief (QSPI1) Instruction Code Register */
  #define REG_QSPI1_IFR     (*(__IO uint32_t*)0xF0024038U) /**< \brief (QSPI1) Instruction Frame Register */
  #define REG_QSPI1_SMR     (*(__IO uint32_t*)0xF0024040U) /**< \brief (QSPI1) Scrambling Mode Register */
  #define REG_QSPI1_SKR     (*(__O  uint32_t*)0xF0024044U) /**< \brief (QSPI1) Scrambling Key Register */
  #define REG_QSPI1_WPMR    (*(__IO uint32_t*)0xF00240E4U) /**< \brief (QSPI1) Write Protection Mode Register */
  #define REG_QSPI1_WPSR    (*(__I  uint32_t*)0xF00240E8U) /**< \brief (QSPI1) Write Protection Status Register */
  #define REG_QSPI1_VERSION (*(__I  uint32_t*)0xF00240FCU) /**< \brief (QSPI1) Version Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_QSPI1_INSTANCE_ */
