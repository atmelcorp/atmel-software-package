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

#ifndef _SAMA5D2_SSC0_INSTANCE_
#define _SAMA5D2_SSC0_INSTANCE_

/* ========== Register definition for SSC0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_SSC0_CR                       (0xF8004000U) /**< \brief (SSC0) Control Register */
  #define REG_SSC0_CMR                      (0xF8004004U) /**< \brief (SSC0) Clock Mode Register */
  #define REG_SSC0_RCMR                     (0xF8004010U) /**< \brief (SSC0) Receive Clock Mode Register */
  #define REG_SSC0_RFMR                     (0xF8004014U) /**< \brief (SSC0) Receive Frame Mode Register */
  #define REG_SSC0_TCMR                     (0xF8004018U) /**< \brief (SSC0) Transmit Clock Mode Register */
  #define REG_SSC0_TFMR                     (0xF800401CU) /**< \brief (SSC0) Transmit Frame Mode Register */
  #define REG_SSC0_RHR                      (0xF8004020U) /**< \brief (SSC0) Receive Holding Register */
  #define REG_SSC0_THR                      (0xF8004024U) /**< \brief (SSC0) Transmit Holding Register */
  #define REG_SSC0_RSHR                     (0xF8004030U) /**< \brief (SSC0) Receive Sync. Holding Register */
  #define REG_SSC0_TSHR                     (0xF8004034U) /**< \brief (SSC0) Transmit Sync. Holding Register */
  #define REG_SSC0_RC0R                     (0xF8004038U) /**< \brief (SSC0) Receive Compare 0 Register */
  #define REG_SSC0_RC1R                     (0xF800403CU) /**< \brief (SSC0) Receive Compare 1 Register */
  #define REG_SSC0_SR                       (0xF8004040U) /**< \brief (SSC0) Status Register */
  #define REG_SSC0_IER                      (0xF8004044U) /**< \brief (SSC0) Interrupt Enable Register */
  #define REG_SSC0_IDR                      (0xF8004048U) /**< \brief (SSC0) Interrupt Disable Register */
  #define REG_SSC0_IMR                      (0xF800404CU) /**< \brief (SSC0) Interrupt Mask Register */
  #define REG_SSC0_WPMR                     (0xF80040E4U) /**< \brief (SSC0) Write Protection Mode Register */
  #define REG_SSC0_WPSR                     (0xF80040E8U) /**< \brief (SSC0) Write Protection Status Register */
  #define REG_SSC0_VERSION                  (0xF80040FCU) /**< \brief (SSC0) Version Register */
#else
  #define REG_SSC0_CR      (*(__O  uint32_t*)0xF8004000U) /**< \brief (SSC0) Control Register */
  #define REG_SSC0_CMR     (*(__IO uint32_t*)0xF8004004U) /**< \brief (SSC0) Clock Mode Register */
  #define REG_SSC0_RCMR    (*(__IO uint32_t*)0xF8004010U) /**< \brief (SSC0) Receive Clock Mode Register */
  #define REG_SSC0_RFMR    (*(__IO uint32_t*)0xF8004014U) /**< \brief (SSC0) Receive Frame Mode Register */
  #define REG_SSC0_TCMR    (*(__IO uint32_t*)0xF8004018U) /**< \brief (SSC0) Transmit Clock Mode Register */
  #define REG_SSC0_TFMR    (*(__IO uint32_t*)0xF800401CU) /**< \brief (SSC0) Transmit Frame Mode Register */
  #define REG_SSC0_RHR     (*(__I  uint32_t*)0xF8004020U) /**< \brief (SSC0) Receive Holding Register */
  #define REG_SSC0_THR     (*(__O  uint32_t*)0xF8004024U) /**< \brief (SSC0) Transmit Holding Register */
  #define REG_SSC0_RSHR    (*(__I  uint32_t*)0xF8004030U) /**< \brief (SSC0) Receive Sync. Holding Register */
  #define REG_SSC0_TSHR    (*(__IO uint32_t*)0xF8004034U) /**< \brief (SSC0) Transmit Sync. Holding Register */
  #define REG_SSC0_RC0R    (*(__IO uint32_t*)0xF8004038U) /**< \brief (SSC0) Receive Compare 0 Register */
  #define REG_SSC0_RC1R    (*(__IO uint32_t*)0xF800403CU) /**< \brief (SSC0) Receive Compare 1 Register */
  #define REG_SSC0_SR      (*(__I  uint32_t*)0xF8004040U) /**< \brief (SSC0) Status Register */
  #define REG_SSC0_IER     (*(__O  uint32_t*)0xF8004044U) /**< \brief (SSC0) Interrupt Enable Register */
  #define REG_SSC0_IDR     (*(__O  uint32_t*)0xF8004048U) /**< \brief (SSC0) Interrupt Disable Register */
  #define REG_SSC0_IMR     (*(__I  uint32_t*)0xF800404CU) /**< \brief (SSC0) Interrupt Mask Register */
  #define REG_SSC0_WPMR    (*(__IO uint32_t*)0xF80040E4U) /**< \brief (SSC0) Write Protection Mode Register */
  #define REG_SSC0_WPSR    (*(__I  uint32_t*)0xF80040E8U) /**< \brief (SSC0) Write Protection Status Register */
  #define REG_SSC0_VERSION (*(__I  uint32_t*)0xF80040FCU) /**< \brief (SSC0) Version Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_SSC0_INSTANCE_ */
