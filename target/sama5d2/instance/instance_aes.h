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

#ifndef _SAMA5D2_AES_INSTANCE_
#define _SAMA5D2_AES_INSTANCE_

/* ========== Register definition for AES peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_AES_CR                       (0xF002C000U) /**< \brief (AES) Control Register */
  #define REG_AES_MR                       (0xF002C004U) /**< \brief (AES) Mode Register */
  #define REG_AES_IER                      (0xF002C010U) /**< \brief (AES) Interrupt Enable Register */
  #define REG_AES_IDR                      (0xF002C014U) /**< \brief (AES) Interrupt Disable Register */
  #define REG_AES_IMR                      (0xF002C018U) /**< \brief (AES) Interrupt Mask Register */
  #define REG_AES_ISR                      (0xF002C01CU) /**< \brief (AES) Interrupt Status Register */
  #define REG_AES_KEYWR                    (0xF002C020U) /**< \brief (AES) Key Word Register */
  #define REG_AES_IDATAR                   (0xF002C040U) /**< \brief (AES) Input Data Register */
  #define REG_AES_ODATAR                   (0xF002C050U) /**< \brief (AES) Output Data Register */
  #define REG_AES_IVR                      (0xF002C060U) /**< \brief (AES) Initialization Vector Register */
  #define REG_AES_AADLENR                  (0xF002C070U) /**< \brief (AES) Additional Authenticated Data Length Register */
  #define REG_AES_CLENR                    (0xF002C074U) /**< \brief (AES) Plaintext/Ciphertext Length Register */
  #define REG_AES_GHASHR                   (0xF002C078U) /**< \brief (AES) GCM Intermediate Hash Word Register */
  #define REG_AES_TAGR                     (0xF002C088U) /**< \brief (AES) GCM Authentication Tag Word Register */
  #define REG_AES_CTRR                     (0xF002C098U) /**< \brief (AES) GCM Encryption Counter Value Register */
  #define REG_AES_GCMHR                    (0xF002C09CU) /**< \brief (AES) GCM H Word Register */
  #define REG_AES_EMR                      (0xF002C0B0U) /**< \brief (AES) Extended Mode Register */
  #define REG_AES_BCNT                     (0xF002C0B4U) /**< \brief (AES) Byte Counter Register */
  #define REG_AES_TWR                      (0xF002C0C0U) /**< \brief (AES) Tweak Word Register */
  #define REG_AES_ALPHAR                   (0xF002C0D0U) /**< \brief (AES) Alpha Word Register */
  #define REG_AES_VERSION                  (0xF002C0FCU) /**< \brief (AES) Version Register */
#else
  #define REG_AES_CR      (*(__O  uint32_t*)0xF002C000U) /**< \brief (AES) Control Register */
  #define REG_AES_MR      (*(__IO uint32_t*)0xF002C004U) /**< \brief (AES) Mode Register */
  #define REG_AES_IER     (*(__O  uint32_t*)0xF002C010U) /**< \brief (AES) Interrupt Enable Register */
  #define REG_AES_IDR     (*(__O  uint32_t*)0xF002C014U) /**< \brief (AES) Interrupt Disable Register */
  #define REG_AES_IMR     (*(__I  uint32_t*)0xF002C018U) /**< \brief (AES) Interrupt Mask Register */
  #define REG_AES_ISR     (*(__I  uint32_t*)0xF002C01CU) /**< \brief (AES) Interrupt Status Register */
  #define REG_AES_KEYWR   (*(__O  uint32_t*)0xF002C020U) /**< \brief (AES) Key Word Register */
  #define REG_AES_IDATAR  (*(__O  uint32_t*)0xF002C040U) /**< \brief (AES) Input Data Register */
  #define REG_AES_ODATAR  (*(__I  uint32_t*)0xF002C050U) /**< \brief (AES) Output Data Register */
  #define REG_AES_IVR     (*(__O  uint32_t*)0xF002C060U) /**< \brief (AES) Initialization Vector Register */
  #define REG_AES_AADLENR (*(__IO uint32_t*)0xF002C070U) /**< \brief (AES) Additional Authenticated Data Length Register */
  #define REG_AES_CLENR   (*(__IO uint32_t*)0xF002C074U) /**< \brief (AES) Plaintext/Ciphertext Length Register */
  #define REG_AES_GHASHR  (*(__IO uint32_t*)0xF002C078U) /**< \brief (AES) GCM Intermediate Hash Word Register */
  #define REG_AES_TAGR    (*(__I  uint32_t*)0xF002C088U) /**< \brief (AES) GCM Authentication Tag Word Register */
  #define REG_AES_CTRR    (*(__I  uint32_t*)0xF002C098U) /**< \brief (AES) GCM Encryption Counter Value Register */
  #define REG_AES_GCMHR   (*(__IO uint32_t*)0xF002C09CU) /**< \brief (AES) GCM H Word Register */
  #define REG_AES_EMR     (*(__IO uint32_t*)0xF002C0B0U) /**< \brief (AES) Extended Mode Register */
  #define REG_AES_BCNT    (*(__IO uint32_t*)0xF002C0B4U) /**< \brief (AES) Byte Counter Register */
  #define REG_AES_TWR     (*(__IO uint32_t*)0xF002C0C0U) /**< \brief (AES) Tweak Word Register */
  #define REG_AES_ALPHAR  (*(__O  uint32_t*)0xF002C0D0U) /**< \brief (AES) Alpha Word Register */
  #define REG_AES_VERSION (*(__I  uint32_t*)0xF002C0FCU) /**< \brief (AES) Version Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_AES_INSTANCE_ */
