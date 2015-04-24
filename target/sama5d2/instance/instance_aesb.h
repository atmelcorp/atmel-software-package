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

#ifndef _SAMA5D2_AESB_INSTANCE_
#define _SAMA5D2_AESB_INSTANCE_

/* ========== Register definition for AESB peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_AESB_CR                       (0xF001C000U) /**< \brief (AESB) Control Register */
  #define REG_AESB_MR                       (0xF001C004U) /**< \brief (AESB) Mode Register */
  #define REG_AESB_IER                      (0xF001C010U) /**< \brief (AESB) Interrupt Enable Register */
  #define REG_AESB_IDR                      (0xF001C014U) /**< \brief (AESB) Interrupt Disable Register */
  #define REG_AESB_IMR                      (0xF001C018U) /**< \brief (AESB) Interrupt Mask Register */
  #define REG_AESB_ISR                      (0xF001C01CU) /**< \brief (AESB) Interrupt Status Register */
  #define REG_AESB_KEYWR                    (0xF001C020U) /**< \brief (AESB) Key Word Register */
  #define REG_AESB_IDATAR                   (0xF001C040U) /**< \brief (AESB) Input Data Register */
  #define REG_AESB_ODATAR                   (0xF001C050U) /**< \brief (AESB) Output Data Register */
  #define REG_AESB_IVR                      (0xF001C060U) /**< \brief (AESB) Initialization Vector Register */
  #define REG_AESB_VERSION                  (0xF001C0FCU) /**< \brief (AESB) Version Register */
#else
  #define REG_AESB_CR      (*(__O  uint32_t*)0xF001C000U) /**< \brief (AESB) Control Register */
  #define REG_AESB_MR      (*(__IO uint32_t*)0xF001C004U) /**< \brief (AESB) Mode Register */
  #define REG_AESB_IER     (*(__O  uint32_t*)0xF001C010U) /**< \brief (AESB) Interrupt Enable Register */
  #define REG_AESB_IDR     (*(__O  uint32_t*)0xF001C014U) /**< \brief (AESB) Interrupt Disable Register */
  #define REG_AESB_IMR     (*(__I  uint32_t*)0xF001C018U) /**< \brief (AESB) Interrupt Mask Register */
  #define REG_AESB_ISR     (*(__I  uint32_t*)0xF001C01CU) /**< \brief (AESB) Interrupt Status Register */
  #define REG_AESB_KEYWR   (*(__O  uint32_t*)0xF001C020U) /**< \brief (AESB) Key Word Register */
  #define REG_AESB_IDATAR  (*(__O  uint32_t*)0xF001C040U) /**< \brief (AESB) Input Data Register */
  #define REG_AESB_ODATAR  (*(__I  uint32_t*)0xF001C050U) /**< \brief (AESB) Output Data Register */
  #define REG_AESB_IVR     (*(__O  uint32_t*)0xF001C060U) /**< \brief (AESB) Initialization Vector Register */
  #define REG_AESB_VERSION (*(__I  uint32_t*)0xF001C0FCU) /**< \brief (AESB) Version Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_AESB_INSTANCE_ */
