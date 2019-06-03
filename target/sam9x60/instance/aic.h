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

#ifndef _SAM9X_AIC_INSTANCE_
#define _SAM9X_AIC_INSTANCE_

/* ========== Register definition for AIC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_AIC_SSR                     (0xFFFFF100U) /**< \brief (AIC) Source Select Register */
  #define REG_AIC_SMR                     (0xFFFFF104U) /**< \brief (AIC) Source Mode Register */
  #define REG_AIC_SVR                     (0xFFFFF108U) /**< \brief (AIC) Source Vector Register */
  #define REG_AIC_IVR                     (0xFFFFF110U) /**< \brief (AIC) Interrupt Vector Register */
  #define REG_AIC_FVR                     (0xFFFFF114U) /**< \brief (AIC) FIQ Vector Register */
  #define REG_AIC_ISR                     (0xFFFFF118U) /**< \brief (AIC) Interrupt Status Register */
  #define REG_AIC_IPR0                    (0xFFFFF120U) /**< \brief (AIC) Interrupt Pending Register 0 */
  #define REG_AIC_IPR1                    (0xFFFFF124U) /**< \brief (AIC) Interrupt Pending Register 1 */
  #define REG_AIC_IPR2                    (0xFFFFF128U) /**< \brief (AIC) Interrupt Pending Register 2 */
  #define REG_AIC_IPR3                    (0xFFFFF12CU) /**< \brief (AIC) Interrupt Pending Register 3 */
  #define REG_AIC_IMR                     (0xFFFFF130U) /**< \brief (AIC) Interrupt Mask Register */
  #define REG_AIC_CISR                    (0xFFFFF134U) /**< \brief (AIC) Core Interrupt Status Register */
  #define REG_AIC_EOICR                   (0xFFFFF138U) /**< \brief (AIC) End of Interrupt Command Register */
  #define REG_AIC_SPU                     (0xFFFFF13CU) /**< \brief (AIC) Spurious Interrupt Vector Register */
  #define REG_AIC_IECR                    (0xFFFFF140U) /**< \brief (AIC) Interrupt Enable Command Register */
  #define REG_AIC_IDCR                    (0xFFFFF144U) /**< \brief (AIC) Interrupt Disable Command Register */
  #define REG_AIC_ICCR                    (0xFFFFF148U) /**< \brief (AIC) Interrupt Clear Command Register */
  #define REG_AIC_ISCR                    (0xFFFFF14CU) /**< \brief (AIC) Interrupt Set Command Register */
  #define REG_AIC_FFER                    (0xFFFFF150U) /**< \brief (AIC) Fast Forcing Enable Register */
  #define REG_AIC_FFDR                    (0xFFFFF154U) /**< \brief (AIC) Fast Forcing Disable Register */
  #define REG_AIC_FFSR                    (0xFFFFF158U) /**< \brief (AIC) Fast Forcing Status Register */
  #define REG_AIC_SVRRER                  (0xFFFFF160U) /**< \brief (AIC) SVR Return Enable Register */
  #define REG_AIC_SVRRDR                  (0xFFFFF164U) /**< \brief (AIC) SVR Return Disable Register */
  #define REG_AIC_SVRRSR                  (0xFFFFF168U) /**< \brief (AIC) SVR Return Status Register */
  #define REG_AIC_DCR                     (0xFFFFF16CU) /**< \brief (AIC) Debug Control Register */
  #define REG_AIC_WPMR                    (0xFFFFF1E4U) /**< \brief (AIC) Write Protection Mode Register */
  #define REG_AIC_WPSR                    (0xFFFFF1E8U) /**< \brief (AIC) Write Protection Status Register */
#else
  #define REG_AIC_SSR    (*(__IO uint32_t*)0xFFFFF100U) /**< \brief (AIC) Source Select Register */
  #define REG_AIC_SMR    (*(__IO uint32_t*)0xFFFFF104U) /**< \brief (AIC) Source Mode Register */
  #define REG_AIC_SVR    (*(__IO uint32_t*)0xFFFFF108U) /**< \brief (AIC) Source Vector Register */
  #define REG_AIC_IVR    (*(__I  uint32_t*)0xFFFFF110U) /**< \brief (AIC) Interrupt Vector Register */
  #define REG_AIC_FVR    (*(__I  uint32_t*)0xFFFFF114U) /**< \brief (AIC) FIQ Vector Register */
  #define REG_AIC_ISR    (*(__I  uint32_t*)0xFFFFF118U) /**< \brief (AIC) Interrupt Status Register */
  #define REG_AIC_IPR0   (*(__I  uint32_t*)0xFFFFF120U) /**< \brief (AIC) Interrupt Pending Register 0 */
  #define REG_AIC_IPR1   (*(__I  uint32_t*)0xFFFFF124U) /**< \brief (AIC) Interrupt Pending Register 1 */
  #define REG_AIC_IPR2   (*(__I  uint32_t*)0xFFFFF128U) /**< \brief (AIC) Interrupt Pending Register 2 */
  #define REG_AIC_IPR3   (*(__I  uint32_t*)0xFFFFF12CU) /**< \brief (AIC) Interrupt Pending Register 3 */
  #define REG_AIC_IMR    (*(__I  uint32_t*)0xFFFFF130U) /**< \brief (AIC) Interrupt Mask Register */
  #define REG_AIC_CISR   (*(__I  uint32_t*)0xFFFFF134U) /**< \brief (AIC) Core Interrupt Status Register */
  #define REG_AIC_EOICR  (*(__O  uint32_t*)0xFFFFF138U) /**< \brief (AIC) End of Interrupt Command Register */
  #define REG_AIC_SPU    (*(__IO uint32_t*)0xFFFFF13CU) /**< \brief (AIC) Spurious Interrupt Vector Register */
  #define REG_AIC_IECR   (*(__O  uint32_t*)0xFFFFF140U) /**< \brief (AIC) Interrupt Enable Command Register */
  #define REG_AIC_IDCR   (*(__O  uint32_t*)0xFFFFF144U) /**< \brief (AIC) Interrupt Disable Command Register */
  #define REG_AIC_ICCR   (*(__O  uint32_t*)0xFFFFF148U) /**< \brief (AIC) Interrupt Clear Command Register */
  #define REG_AIC_ISCR   (*(__O  uint32_t*)0xFFFFF14CU) /**< \brief (AIC) Interrupt Set Command Register */
  #define REG_AIC_FFER   (*(__O  uint32_t*)0xFFFFF150U) /**< \brief (AIC) Fast Forcing Enable Register */
  #define REG_AIC_FFDR   (*(__O  uint32_t*)0xFFFFF154U) /**< \brief (AIC) Fast Forcing Disable Register */
  #define REG_AIC_FFSR   (*(__I  uint32_t*)0xFFFFF158U) /**< \brief (AIC) Fast Forcing Status Register */
  #define REG_AIC_SVRRER (*(__O  uint32_t*)0xFFFFF160U) /**< \brief (AIC) SVR Return Enable Register */
  #define REG_AIC_SVRRDR (*(__O  uint32_t*)0xFFFFF164U) /**< \brief (AIC) SVR Return Disable Register */
  #define REG_AIC_SVRRSR (*(__I  uint32_t*)0xFFFFF168U) /**< \brief (AIC) SVR Return Status Register */
  #define REG_AIC_DCR    (*(__IO uint32_t*)0xFFFFF16CU) /**< \brief (AIC) Debug Control Register */
  #define REG_AIC_WPMR   (*(__IO uint32_t*)0xFFFFF1E4U) /**< \brief (AIC) Write Protection Mode Register */
  #define REG_AIC_WPSR   (*(__I  uint32_t*)0xFFFFF1E8U) /**< \brief (AIC) Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_AIC_INSTANCE_ */
