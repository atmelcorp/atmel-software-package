/* ---------------------------------------------------------------------------- */
/*                Microchip Microcontroller Software Support                    */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) %copyright_year%, Microchip Technology Inc.                    */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Microchip's name may not be used to endorse or promote products derived from */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY MICROCHIP "AS IS" AND ANY EXPRESS  */
/* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES */
/* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT    */
/* ARE DISCLAIMED. IN NO EVENT SHALL MICROCHIP BE LIABLE FOR ANY DIRECT,        */
/* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES           */
/* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; */
/* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND  */
/* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT   */
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF     */
/* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.            */
/* ---------------------------------------------------------------------------- */

#ifndef _SAM9X_SSC_INSTANCE_
#define _SAM9X_SSC_INSTANCE_

/* ========== Register definition for SSC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_SSC_CR                    (0xF0010000U) /**< \brief (SSC) Control Register */
  #define REG_SSC_CMR                   (0xF0010004U) /**< \brief (SSC) Clock Mode Register */
  #define REG_SSC_RCMR                  (0xF0010010U) /**< \brief (SSC) Receive Clock Mode Register */
  #define REG_SSC_RFMR                  (0xF0010014U) /**< \brief (SSC) Receive Frame Mode Register */
  #define REG_SSC_TCMR                  (0xF0010018U) /**< \brief (SSC) Transmit Clock Mode Register */
  #define REG_SSC_TFMR                  (0xF001001CU) /**< \brief (SSC) Transmit Frame Mode Register */
  #define REG_SSC_RHR                   (0xF0010020U) /**< \brief (SSC) Receive Holding Register */
  #define REG_SSC_THR                   (0xF0010024U) /**< \brief (SSC) Transmit Holding Register */
  #define REG_SSC_RSHR                  (0xF0010030U) /**< \brief (SSC) Receive Sync. Holding Register */
  #define REG_SSC_TSHR                  (0xF0010034U) /**< \brief (SSC) Transmit Sync. Holding Register */
  #define REG_SSC_RC0R                  (0xF0010038U) /**< \brief (SSC) Receive Compare 0 Register */
  #define REG_SSC_RC1R                  (0xF001003CU) /**< \brief (SSC) Receive Compare 1 Register */
  #define REG_SSC_SR                    (0xF0010040U) /**< \brief (SSC) Status Register */
  #define REG_SSC_IER                   (0xF0010044U) /**< \brief (SSC) Interrupt Enable Register */
  #define REG_SSC_IDR                   (0xF0010048U) /**< \brief (SSC) Interrupt Disable Register */
  #define REG_SSC_IMR                   (0xF001004CU) /**< \brief (SSC) Interrupt Mask Register */
  #define REG_SSC_WPMR                  (0xF00100E4U) /**< \brief (SSC) Write Protection Mode Register */
  #define REG_SSC_WPSR                  (0xF00100E8U) /**< \brief (SSC) Write Protection Status Register */
#else
  #define REG_SSC_CR   (*(__O  uint32_t*)0xF0010000U) /**< \brief (SSC) Control Register */
  #define REG_SSC_CMR  (*(__IO uint32_t*)0xF0010004U) /**< \brief (SSC) Clock Mode Register */
  #define REG_SSC_RCMR (*(__IO uint32_t*)0xF0010010U) /**< \brief (SSC) Receive Clock Mode Register */
  #define REG_SSC_RFMR (*(__IO uint32_t*)0xF0010014U) /**< \brief (SSC) Receive Frame Mode Register */
  #define REG_SSC_TCMR (*(__IO uint32_t*)0xF0010018U) /**< \brief (SSC) Transmit Clock Mode Register */
  #define REG_SSC_TFMR (*(__IO uint32_t*)0xF001001CU) /**< \brief (SSC) Transmit Frame Mode Register */
  #define REG_SSC_RHR  (*(__I  uint32_t*)0xF0010020U) /**< \brief (SSC) Receive Holding Register */
  #define REG_SSC_THR  (*(__O  uint32_t*)0xF0010024U) /**< \brief (SSC) Transmit Holding Register */
  #define REG_SSC_RSHR (*(__I  uint32_t*)0xF0010030U) /**< \brief (SSC) Receive Sync. Holding Register */
  #define REG_SSC_TSHR (*(__IO uint32_t*)0xF0010034U) /**< \brief (SSC) Transmit Sync. Holding Register */
  #define REG_SSC_RC0R (*(__IO uint32_t*)0xF0010038U) /**< \brief (SSC) Receive Compare 0 Register */
  #define REG_SSC_RC1R (*(__IO uint32_t*)0xF001003CU) /**< \brief (SSC) Receive Compare 1 Register */
  #define REG_SSC_SR   (*(__I  uint32_t*)0xF0010040U) /**< \brief (SSC) Status Register */
  #define REG_SSC_IER  (*(__O  uint32_t*)0xF0010044U) /**< \brief (SSC) Interrupt Enable Register */
  #define REG_SSC_IDR  (*(__O  uint32_t*)0xF0010048U) /**< \brief (SSC) Interrupt Disable Register */
  #define REG_SSC_IMR  (*(__I  uint32_t*)0xF001004CU) /**< \brief (SSC) Interrupt Mask Register */
  #define REG_SSC_WPMR (*(__IO uint32_t*)0xF00100E4U) /**< \brief (SSC) Write Protection Mode Register */
  #define REG_SSC_WPSR (*(__I  uint32_t*)0xF00100E8U) /**< \brief (SSC) Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_SSC_INSTANCE_ */
