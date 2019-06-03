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

#ifndef _SAM9X_PIT64B_INSTANCE_
#define _SAM9X_PIT64B_INSTANCE_

/* ========== Register definition for PIT64B peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_PIT64B_CR                     (0xF0028000U) /**< \brief (PIT64B) Control Register */
  #define REG_PIT64B_MR                     (0xF0028004U) /**< \brief (PIT64B) Mode Register */
  #define REG_PIT64B_LSBPR                  (0xF0028008U) /**< \brief (PIT64B) LSB Period Register */
  #define REG_PIT64B_MSBPR                  (0xF002800CU) /**< \brief (PIT64B) MSB Period Register */
  #define REG_PIT64B_IER                    (0xF0028010U) /**< \brief (PIT64B) Interrupt Enable Register */
  #define REG_PIT64B_IDR                    (0xF0028014U) /**< \brief (PIT64B) Interrupt Disable Register */
  #define REG_PIT64B_IMR                    (0xF0028018U) /**< \brief (PIT64B) Interrupt Mask Register */
  #define REG_PIT64B_ISR                    (0xF002801CU) /**< \brief (PIT64B) Interrupt Status Register */
  #define REG_PIT64B_TLSBR                  (0xF0028020U) /**< \brief (PIT64B) Timer LSB Current Value Register */
  #define REG_PIT64B_TMSBR                  (0xF0028024U) /**< \brief (PIT64B) Timer MSB Current Value Register */
  #define REG_PIT64B_WPMR                   (0xF00280E4U) /**< \brief (PIT64B) Write Protection Mode Register */
  #define REG_PIT64B_WPSR                   (0xF00280E8U) /**< \brief (PIT64B) Write Protection Status Register */
#else
  #define REG_PIT64B_CR    (*(__O  uint32_t*)0xF0028000U) /**< \brief (PIT64B) Control Register */
  #define REG_PIT64B_MR    (*(__IO uint32_t*)0xF0028004U) /**< \brief (PIT64B) Mode Register */
  #define REG_PIT64B_LSBPR (*(__IO uint32_t*)0xF0028008U) /**< \brief (PIT64B) LSB Period Register */
  #define REG_PIT64B_MSBPR (*(__IO uint32_t*)0xF002800CU) /**< \brief (PIT64B) MSB Period Register */
  #define REG_PIT64B_IER   (*(__O  uint32_t*)0xF0028010U) /**< \brief (PIT64B) Interrupt Enable Register */
  #define REG_PIT64B_IDR   (*(__O  uint32_t*)0xF0028014U) /**< \brief (PIT64B) Interrupt Disable Register */
  #define REG_PIT64B_IMR   (*(__I  uint32_t*)0xF0028018U) /**< \brief (PIT64B) Interrupt Mask Register */
  #define REG_PIT64B_ISR   (*(__I  uint32_t*)0xF002801CU) /**< \brief (PIT64B) Interrupt Status Register */
  #define REG_PIT64B_TLSBR (*(__I  uint32_t*)0xF0028020U) /**< \brief (PIT64B) Timer LSB Current Value Register */
  #define REG_PIT64B_TMSBR (*(__I  uint32_t*)0xF0028024U) /**< \brief (PIT64B) Timer MSB Current Value Register */
  #define REG_PIT64B_WPMR  (*(__IO uint32_t*)0xF00280E4U) /**< \brief (PIT64B) Write Protection Mode Register */
  #define REG_PIT64B_WPSR  (*(__I  uint32_t*)0xF00280E8U) /**< \brief (PIT64B) Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_PIT64B_INSTANCE_ */
