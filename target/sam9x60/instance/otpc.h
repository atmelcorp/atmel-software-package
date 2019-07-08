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

#ifndef _SAM9X_OTPC_INSTANCE_
#define _SAM9X_OTPC_INSTANCE_

/* ========== Register definition for OTPC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_OTPC_CR                     (0xEFF00000U) /**< \brief (OTPC) Control Register */
  #define REG_OTPC_MR                     (0xEFF00004U) /**< \brief (OTPC) Mode Register */
  #define REG_OTPC_AR                     (0xEFF00008U) /**< \brief (OTPC) Address Register */
  #define REG_OTPC_SR                     (0xEFF0000CU) /**< \brief (OTPC) Status Register */
  #define REG_OTPC_IER                    (0xEFF00010U) /**< \brief (OTPC) Interrupt Enable Register */
  #define REG_OTPC_IDR                    (0xEFF00014U) /**< \brief (OTPC) Interrupt Disable Register */
  #define REG_OTPC_IMR                    (0xEFF00018U) /**< \brief (OTPC) Interrupt Mask Register */
  #define REG_OTPC_ISR                    (0xEFF0001CU) /**< \brief (OTPC) Interrupt Status Register */
  #define REG_OTPC_HR                     (0xEFF00020U) /**< \brief (OTPC) Header Register */
  #define REG_OTPC_DR                     (0xEFF00024U) /**< \brief (OTPC) Data Register */
  #define REG_OTPC_BAR                    (0xEFF00030U) /**< \brief (OTPC) Boot Addresses Register */
  #define REG_OTPC_CAR                    (0xEFF00034U) /**< \brief (OTPC) Custom Address Register */
  #define REG_OTPC_UHC0R                  (0xEFF00050U) /**< \brief (OTPC) User Hardware Configuration 0 Register */
  #define REG_OTPC_UHC1R                  (0xEFF00054U) /**< \brief (OTPC) User Hardware Configuration 1 Register */
  #define REG_OTPC_UID0R                  (0xEFF00060U) /**< \brief (OTPC) Product UID 0 Register */
  #define REG_OTPC_UID1R                  (0xEFF00064U) /**< \brief (OTPC) Product UID 1 Register */
  #define REG_OTPC_UID2R                  (0xEFF00068U) /**< \brief (OTPC) Product UID 2 Register */
  #define REG_OTPC_UID3R                  (0xEFF0006CU) /**< \brief (OTPC) Product UID 3 Register */
  #define REG_OTPC_WPMR                   (0xEFF000E4U) /**< \brief (OTPC) Write Protection Mode Register */
  #define REG_OTPC_WPSR                   (0xEFF000E8U) /**< \brief (OTPC) Write Protection Status Register */
#else
  #define REG_OTPC_CR    (*(__O  uint32_t*)0xEFF00000U) /**< \brief (OTPC) Control Register */
  #define REG_OTPC_MR    (*(__IO uint32_t*)0xEFF00004U) /**< \brief (OTPC) Mode Register */
  #define REG_OTPC_AR    (*(__IO uint32_t*)0xEFF00008U) /**< \brief (OTPC) Address Register */
  #define REG_OTPC_SR    (*(__I  uint32_t*)0xEFF0000CU) /**< \brief (OTPC) Status Register */
  #define REG_OTPC_IER   (*(__O  uint32_t*)0xEFF00010U) /**< \brief (OTPC) Interrupt Enable Register */
  #define REG_OTPC_IDR   (*(__O  uint32_t*)0xEFF00014U) /**< \brief (OTPC) Interrupt Disable Register */
  #define REG_OTPC_IMR   (*(__I  uint32_t*)0xEFF00018U) /**< \brief (OTPC) Interrupt Mask Register */
  #define REG_OTPC_ISR   (*(__I  uint32_t*)0xEFF0001CU) /**< \brief (OTPC) Interrupt Status Register */
  #define REG_OTPC_HR    (*(__IO uint32_t*)0xEFF00020U) /**< \brief (OTPC) Header Register */
  #define REG_OTPC_DR    (*(__IO uint32_t*)0xEFF00024U) /**< \brief (OTPC) Data Register */
  #define REG_OTPC_BAR   (*(__I  uint32_t*)0xEFF00030U) /**< \brief (OTPC) Boot Addresses Register */
  #define REG_OTPC_CAR   (*(__I  uint32_t*)0xEFF00034U) /**< \brief (OTPC) Custom Address Register */
  #define REG_OTPC_UHC0R (*(__I  uint32_t*)0xEFF00050U) /**< \brief (OTPC) User Hardware Configuration 0 Register */
  #define REG_OTPC_UHC1R (*(__I  uint32_t*)0xEFF00054U) /**< \brief (OTPC) User Hardware Configuration 1 Register */
  #define REG_OTPC_UID0R (*(__I  uint32_t*)0xEFF00060U) /**< \brief (OTPC) Product UID 0 Register */
  #define REG_OTPC_UID1R (*(__I  uint32_t*)0xEFF00064U) /**< \brief (OTPC) Product UID 1 Register */
  #define REG_OTPC_UID2R (*(__I  uint32_t*)0xEFF00068U) /**< \brief (OTPC) Product UID 2 Register */
  #define REG_OTPC_UID3R (*(__I  uint32_t*)0xEFF0006CU) /**< \brief (OTPC) Product UID 3 Register */
  #define REG_OTPC_WPMR  (*(__IO uint32_t*)0xEFF000E4U) /**< \brief (OTPC) Write Protection Mode Register */
  #define REG_OTPC_WPSR  (*(__I  uint32_t*)0xEFF000E8U) /**< \brief (OTPC) Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_OTPC_INSTANCE_ */
