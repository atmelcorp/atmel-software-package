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

#ifndef _SAMA5D2_QSPI0_INSTANCE_
#define _SAMA5D2_QSPI0_INSTANCE_

/* ========== Register definition for QSPI0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_QSPI0_CR                       (0xF0020000U) /**< \brief (QSPI0) Control Register */
  #define REG_QSPI0_MR                       (0xF0020004U) /**< \brief (QSPI0) Mode Register */
  #define REG_QSPI0_RDR                      (0xF0020008U) /**< \brief (QSPI0) Receive Data Register */
  #define REG_QSPI0_TDR                      (0xF002000CU) /**< \brief (QSPI0) Transmit Data Register */
  #define REG_QSPI0_SR                       (0xF0020010U) /**< \brief (QSPI0) Status Register */
  #define REG_QSPI0_IER                      (0xF0020014U) /**< \brief (QSPI0) Interrupt Enable Register */
  #define REG_QSPI0_IDR                      (0xF0020018U) /**< \brief (QSPI0) Interrupt Disable Register */
  #define REG_QSPI0_IMR                      (0xF002001CU) /**< \brief (QSPI0) Interrupt Mask Register */
  #define REG_QSPI0_SCR                      (0xF0020020U) /**< \brief (QSPI0) Serial Clock Register */
  #define REG_QSPI0_IAR                      (0xF0020030U) /**< \brief (QSPI0) Instruction Address Register */
  #define REG_QSPI0_ICR                      (0xF0020034U) /**< \brief (QSPI0) Instruction Code Register */
  #define REG_QSPI0_IFR                      (0xF0020038U) /**< \brief (QSPI0) Instruction Frame Register */
  #define REG_QSPI0_SMR                      (0xF0020040U) /**< \brief (QSPI0) Scrambling Mode Register */
  #define REG_QSPI0_SKR                      (0xF0020044U) /**< \brief (QSPI0) Scrambling Key Register */
  #define REG_QSPI0_WPMR                     (0xF00200E4U) /**< \brief (QSPI0) Write Protection Mode Register */
  #define REG_QSPI0_WPSR                     (0xF00200E8U) /**< \brief (QSPI0) Write Protection Status Register */
  #define REG_QSPI0_VERSION                  (0xF00200FCU) /**< \brief (QSPI0) Version Register */
#else
  #define REG_QSPI0_CR      (*(__O  uint32_t*)0xF0020000U) /**< \brief (QSPI0) Control Register */
  #define REG_QSPI0_MR      (*(__IO uint32_t*)0xF0020004U) /**< \brief (QSPI0) Mode Register */
  #define REG_QSPI0_RDR     (*(__I  uint32_t*)0xF0020008U) /**< \brief (QSPI0) Receive Data Register */
  #define REG_QSPI0_TDR     (*(__O  uint32_t*)0xF002000CU) /**< \brief (QSPI0) Transmit Data Register */
  #define REG_QSPI0_SR      (*(__I  uint32_t*)0xF0020010U) /**< \brief (QSPI0) Status Register */
  #define REG_QSPI0_IER     (*(__O  uint32_t*)0xF0020014U) /**< \brief (QSPI0) Interrupt Enable Register */
  #define REG_QSPI0_IDR     (*(__O  uint32_t*)0xF0020018U) /**< \brief (QSPI0) Interrupt Disable Register */
  #define REG_QSPI0_IMR     (*(__I  uint32_t*)0xF002001CU) /**< \brief (QSPI0) Interrupt Mask Register */
  #define REG_QSPI0_SCR     (*(__IO uint32_t*)0xF0020020U) /**< \brief (QSPI0) Serial Clock Register */
  #define REG_QSPI0_IAR     (*(__IO uint32_t*)0xF0020030U) /**< \brief (QSPI0) Instruction Address Register */
  #define REG_QSPI0_ICR     (*(__IO uint32_t*)0xF0020034U) /**< \brief (QSPI0) Instruction Code Register */
  #define REG_QSPI0_IFR     (*(__IO uint32_t*)0xF0020038U) /**< \brief (QSPI0) Instruction Frame Register */
  #define REG_QSPI0_SMR     (*(__IO uint32_t*)0xF0020040U) /**< \brief (QSPI0) Scrambling Mode Register */
  #define REG_QSPI0_SKR     (*(__O  uint32_t*)0xF0020044U) /**< \brief (QSPI0) Scrambling Key Register */
  #define REG_QSPI0_WPMR    (*(__IO uint32_t*)0xF00200E4U) /**< \brief (QSPI0) Write Protection Mode Register */
  #define REG_QSPI0_WPSR    (*(__I  uint32_t*)0xF00200E8U) /**< \brief (QSPI0) Write Protection Status Register */
  #define REG_QSPI0_VERSION (*(__I  uint32_t*)0xF00200FCU) /**< \brief (QSPI0) Version Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_QSPI0_INSTANCE_ */
