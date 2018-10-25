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

#ifndef _SAM9X_WDT_INSTANCE_
#define _SAM9X_WDT_INSTANCE_

/* ========== Register definition for WDT peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_WDT_CR                   (0xFFFFFF80U) /**< \brief (WDT) Control Register */
  #define REG_WDT_MR                   (0xFFFFFF84U) /**< \brief (WDT) Mode Register */
  #define REG_WDT_VR                   (0xFFFFFF88U) /**< \brief (WDT) Value Register */
  #define REG_WDT_WLR                  (0xFFFFFF8CU) /**< \brief (WDT) Window Level Register */
  #define REG_WDT_ILR                  (0xFFFFFF90U) /**< \brief (WDT) Interrupt Level Register */
  #define REG_WDT_IER                  (0xFFFFFF94U) /**< \brief (WDT) Interrupt Enable Register */
  #define REG_WDT_IDR                  (0xFFFFFF98U) /**< \brief (WDT) Interrupt Disable Register */
  #define REG_WDT_ISR                  (0xFFFFFF9CU) /**< \brief (WDT) Interrupt Status Register */
  #define REG_WDT_IMR                  (0xFFFFFFA0U) /**< \brief (WDT) Interrupt Mask Register */
#else
  #define REG_WDT_CR  (*(__O  uint32_t*)0xFFFFFF80U) /**< \brief (WDT) Control Register */
  #define REG_WDT_MR  (*(__IO uint32_t*)0xFFFFFF84U) /**< \brief (WDT) Mode Register */
  #define REG_WDT_VR  (*(__I  uint32_t*)0xFFFFFF88U) /**< \brief (WDT) Value Register */
  #define REG_WDT_WLR (*(__IO uint32_t*)0xFFFFFF8CU) /**< \brief (WDT) Window Level Register */
  #define REG_WDT_ILR (*(__IO uint32_t*)0xFFFFFF90U) /**< \brief (WDT) Interrupt Level Register */
  #define REG_WDT_IER (*(__O  uint32_t*)0xFFFFFF94U) /**< \brief (WDT) Interrupt Enable Register */
  #define REG_WDT_IDR (*(__O  uint32_t*)0xFFFFFF98U) /**< \brief (WDT) Interrupt Disable Register */
  #define REG_WDT_ISR (*(__I  uint32_t*)0xFFFFFF9CU) /**< \brief (WDT) Interrupt Status Register */
  #define REG_WDT_IMR (*(__I  uint32_t*)0xFFFFFFA0U) /**< \brief (WDT) Interrupt Mask Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_WDT_INSTANCE_ */
