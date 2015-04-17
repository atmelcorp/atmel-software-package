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

#ifndef _SAMA5D4_TDES_INSTANCE_
#define _SAMA5D4_TDES_INSTANCE_

/* ========== Register definition for TDES peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_TDES_CR                         (0xFC04C000U) /**< \brief (TDES) Control Register */
  #define REG_TDES_MR                         (0xFC04C004U) /**< \brief (TDES) Mode Register */
  #define REG_TDES_IER                        (0xFC04C010U) /**< \brief (TDES) Interrupt Enable Register */
  #define REG_TDES_IDR                        (0xFC04C014U) /**< \brief (TDES) Interrupt Disable Register */
  #define REG_TDES_IMR                        (0xFC04C018U) /**< \brief (TDES) Interrupt Mask Register */
  #define REG_TDES_ISR                        (0xFC04C01CU) /**< \brief (TDES) Interrupt Status Register */
  #define REG_TDES_KEY1WR                     (0xFC04C020U) /**< \brief (TDES) Key 1 Word Register */
  #define REG_TDES_KEY2WR                     (0xFC04C028U) /**< \brief (TDES) Key 2 Word Register */
  #define REG_TDES_KEY3WR                     (0xFC04C030U) /**< \brief (TDES) Key 3 Word Register */
  #define REG_TDES_IDATAR                     (0xFC04C040U) /**< \brief (TDES) Input Data Register */
  #define REG_TDES_ODATAR                     (0xFC04C050U) /**< \brief (TDES) Output Data Register */
  #define REG_TDES_IVR                        (0xFC04C060U) /**< \brief (TDES) Initialization Vector Register */
  #define REG_TDES_XTEA_RNDR                  (0xFC04C070U) /**< \brief (TDES) XTEA Rounds Register */
#else
  #define REG_TDES_CR        (*(__O  uint32_t*)0xFC04C000U) /**< \brief (TDES) Control Register */
  #define REG_TDES_MR        (*(__IO uint32_t*)0xFC04C004U) /**< \brief (TDES) Mode Register */
  #define REG_TDES_IER       (*(__O  uint32_t*)0xFC04C010U) /**< \brief (TDES) Interrupt Enable Register */
  #define REG_TDES_IDR       (*(__O  uint32_t*)0xFC04C014U) /**< \brief (TDES) Interrupt Disable Register */
  #define REG_TDES_IMR       (*(__I  uint32_t*)0xFC04C018U) /**< \brief (TDES) Interrupt Mask Register */
  #define REG_TDES_ISR       (*(__I  uint32_t*)0xFC04C01CU) /**< \brief (TDES) Interrupt Status Register */
  #define REG_TDES_KEY1WR    (*(__O  uint32_t*)0xFC04C020U) /**< \brief (TDES) Key 1 Word Register */
  #define REG_TDES_KEY2WR    (*(__O  uint32_t*)0xFC04C028U) /**< \brief (TDES) Key 2 Word Register */
  #define REG_TDES_KEY3WR    (*(__O  uint32_t*)0xFC04C030U) /**< \brief (TDES) Key 3 Word Register */
  #define REG_TDES_IDATAR    (*(__O  uint32_t*)0xFC04C040U) /**< \brief (TDES) Input Data Register */
  #define REG_TDES_ODATAR    (*(__I  uint32_t*)0xFC04C050U) /**< \brief (TDES) Output Data Register */
  #define REG_TDES_IVR       (*(__O  uint32_t*)0xFC04C060U) /**< \brief (TDES) Initialization Vector Register */
  #define REG_TDES_XTEA_RNDR (*(__IO uint32_t*)0xFC04C070U) /**< \brief (TDES) XTEA Rounds Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D4_TDES_INSTANCE_ */
