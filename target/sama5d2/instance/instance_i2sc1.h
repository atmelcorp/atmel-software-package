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

#ifndef _SAMA5D2_I2SC1_INSTANCE_
#define _SAMA5D2_I2SC1_INSTANCE_

/* ========== Register definition for I2SC1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_I2SC1_CR                       (0xFC04C000U) /**< \brief (I2SC1) Control Register */
  #define REG_I2SC1_MR                       (0xFC04C004U) /**< \brief (I2SC1) Mode Register */
  #define REG_I2SC1_SR                       (0xFC04C008U) /**< \brief (I2SC1) Status Register */
  #define REG_I2SC1_SCR                      (0xFC04C00CU) /**< \brief (I2SC1) Status Clear Register */
  #define REG_I2SC1_SSR                      (0xFC04C010U) /**< \brief (I2SC1) Status Set Register */
  #define REG_I2SC1_IER                      (0xFC04C014U) /**< \brief (I2SC1) Interrupt Enable Register */
  #define REG_I2SC1_IDR                      (0xFC04C018U) /**< \brief (I2SC1) Interrupt Disable Register */
  #define REG_I2SC1_IMR                      (0xFC04C01CU) /**< \brief (I2SC1) Interrupt Mask Register */
  #define REG_I2SC1_RHR                      (0xFC04C020U) /**< \brief (I2SC1) Receiver Holding Register */
  #define REG_I2SC1_THR                      (0xFC04C024U) /**< \brief (I2SC1) Transmitter Holding Register */
  #define REG_I2SC1_VERSION                  (0xFC04C028U) /**< \brief (I2SC1) Version Register */
#else
  #define REG_I2SC1_CR      (*(__O  uint32_t*)0xFC04C000U) /**< \brief (I2SC1) Control Register */
  #define REG_I2SC1_MR      (*(__IO uint32_t*)0xFC04C004U) /**< \brief (I2SC1) Mode Register */
  #define REG_I2SC1_SR      (*(__I  uint32_t*)0xFC04C008U) /**< \brief (I2SC1) Status Register */
  #define REG_I2SC1_SCR     (*(__O  uint32_t*)0xFC04C00CU) /**< \brief (I2SC1) Status Clear Register */
  #define REG_I2SC1_SSR     (*(__O  uint32_t*)0xFC04C010U) /**< \brief (I2SC1) Status Set Register */
  #define REG_I2SC1_IER     (*(__O  uint32_t*)0xFC04C014U) /**< \brief (I2SC1) Interrupt Enable Register */
  #define REG_I2SC1_IDR     (*(__O  uint32_t*)0xFC04C018U) /**< \brief (I2SC1) Interrupt Disable Register */
  #define REG_I2SC1_IMR     (*(__I  uint32_t*)0xFC04C01CU) /**< \brief (I2SC1) Interrupt Mask Register */
  #define REG_I2SC1_RHR     (*(__I  uint32_t*)0xFC04C020U) /**< \brief (I2SC1) Receiver Holding Register */
  #define REG_I2SC1_THR     (*(__O  uint32_t*)0xFC04C024U) /**< \brief (I2SC1) Transmitter Holding Register */
  #define REG_I2SC1_VERSION (*(__I  uint32_t*)0xFC04C028U) /**< \brief (I2SC1) Version Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_I2SC1_INSTANCE_ */
