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

#ifndef _SAM9X_CLASSD_INSTANCE_
#define _SAM9X_CLASSD_INSTANCE_

/* ========== Register definition for CLASSD peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_CLASSD_CR                      (0xF003C000U) /**< \brief (CLASSD) Control Register */
  #define REG_CLASSD_MR                      (0xF003C004U) /**< \brief (CLASSD) Mode Register */
  #define REG_CLASSD_INTPMR                  (0xF003C008U) /**< \brief (CLASSD) Interpolator Mode Register */
  #define REG_CLASSD_INTSR                   (0xF003C00CU) /**< \brief (CLASSD) Interpolator Status Register */
  #define REG_CLASSD_THR                     (0xF003C010U) /**< \brief (CLASSD) Transmit Holding Register */
  #define REG_CLASSD_IER                     (0xF003C014U) /**< \brief (CLASSD) Interrupt Enable Register */
  #define REG_CLASSD_IDR                     (0xF003C018U) /**< \brief (CLASSD) Interrupt Disable Register */
  #define REG_CLASSD_IMR                     (0xF003C01CU) /**< \brief (CLASSD) Interrupt Mask Register */
  #define REG_CLASSD_ISR                     (0xF003C020U) /**< \brief (CLASSD) Interrupt Status Register */
  #define REG_CLASSD_WPMR                    (0xF003C0E4U) /**< \brief (CLASSD) Write Protection Mode Register */
#else
  #define REG_CLASSD_CR     (*(__O  uint32_t*)0xF003C000U) /**< \brief (CLASSD) Control Register */
  #define REG_CLASSD_MR     (*(__IO uint32_t*)0xF003C004U) /**< \brief (CLASSD) Mode Register */
  #define REG_CLASSD_INTPMR (*(__IO uint32_t*)0xF003C008U) /**< \brief (CLASSD) Interpolator Mode Register */
  #define REG_CLASSD_INTSR  (*(__I  uint32_t*)0xF003C00CU) /**< \brief (CLASSD) Interpolator Status Register */
  #define REG_CLASSD_THR    (*(__IO uint32_t*)0xF003C010U) /**< \brief (CLASSD) Transmit Holding Register */
  #define REG_CLASSD_IER    (*(__O  uint32_t*)0xF003C014U) /**< \brief (CLASSD) Interrupt Enable Register */
  #define REG_CLASSD_IDR    (*(__O  uint32_t*)0xF003C018U) /**< \brief (CLASSD) Interrupt Disable Register */
  #define REG_CLASSD_IMR    (*(__IO uint32_t*)0xF003C01CU) /**< \brief (CLASSD) Interrupt Mask Register */
  #define REG_CLASSD_ISR    (*(__I  uint32_t*)0xF003C020U) /**< \brief (CLASSD) Interrupt Status Register */
  #define REG_CLASSD_WPMR   (*(__IO uint32_t*)0xF003C0E4U) /**< \brief (CLASSD) Write Protection Mode Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_CLASSD_INSTANCE_ */
