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

#ifndef _SAM9X_SHA_INSTANCE_
#define _SAM9X_SHA_INSTANCE_

/* ========== Register definition for SHA peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_SHA_CR                       (0xF002C000U) /**< \brief (SHA) Control Register */
  #define REG_SHA_MR                       (0xF002C004U) /**< \brief (SHA) Mode Register */
  #define REG_SHA_IER                      (0xF002C010U) /**< \brief (SHA) Interrupt Enable Register */
  #define REG_SHA_IDR                      (0xF002C014U) /**< \brief (SHA) Interrupt Disable Register */
  #define REG_SHA_IMR                      (0xF002C018U) /**< \brief (SHA) Interrupt Mask Register */
  #define REG_SHA_ISR                      (0xF002C01CU) /**< \brief (SHA) Interrupt Status Register */
  #define REG_SHA_MSR                      (0xF002C020U) /**< \brief (SHA) Message Size Register */
  #define REG_SHA_BCR                      (0xF002C030U) /**< \brief (SHA) Bytes Count Register */
  #define REG_SHA_IDATAR                   (0xF002C040U) /**< \brief (SHA) Input Data 0 Register */
  #define REG_SHA_IODATAR                  (0xF002C080U) /**< \brief (SHA) Input/Output Data 0 Register */
  #define REG_SHA_WPMR                     (0xF002C0E4U) /**< \brief (SHA) Write Protection Mode Register */
  #define REG_SHA_WPSR                     (0xF002C0E8U) /**< \brief (SHA) Write Protection Status Register */
#else
  #define REG_SHA_CR      (*(__O  uint32_t*)0xF002C000U) /**< \brief (SHA) Control Register */
  #define REG_SHA_MR      (*(__IO uint32_t*)0xF002C004U) /**< \brief (SHA) Mode Register */
  #define REG_SHA_IER     (*(__O  uint32_t*)0xF002C010U) /**< \brief (SHA) Interrupt Enable Register */
  #define REG_SHA_IDR     (*(__O  uint32_t*)0xF002C014U) /**< \brief (SHA) Interrupt Disable Register */
  #define REG_SHA_IMR     (*(__I  uint32_t*)0xF002C018U) /**< \brief (SHA) Interrupt Mask Register */
  #define REG_SHA_ISR     (*(__I  uint32_t*)0xF002C01CU) /**< \brief (SHA) Interrupt Status Register */
  #define REG_SHA_MSR     (*(__IO uint32_t*)0xF002C020U) /**< \brief (SHA) Message Size Register */
  #define REG_SHA_BCR     (*(__IO uint32_t*)0xF002C030U) /**< \brief (SHA) Bytes Count Register */
  #define REG_SHA_IDATAR  (*(__O  uint32_t*)0xF002C040U) /**< \brief (SHA) Input Data 0 Register */
  #define REG_SHA_IODATAR (*(__IO uint32_t*)0xF002C080U) /**< \brief (SHA) Input/Output Data 0 Register */
  #define REG_SHA_WPMR    (*(__IO uint32_t*)0xF002C0E4U) /**< \brief (SHA) Write Protection Mode Register */
  #define REG_SHA_WPSR    (*(__I  uint32_t*)0xF002C0E8U) /**< \brief (SHA) Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_SHA_INSTANCE_ */
