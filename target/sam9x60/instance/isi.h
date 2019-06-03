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

#ifndef _SAM9X_ISI_INSTANCE_
#define _SAM9X_ISI_INSTANCE_

/* ========== Register definition for ISI peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_ISI_CFG1                        (0xF8048000U) /**< \brief (ISI) ISI Configuration 1 Register */
  #define REG_ISI_CFG2                        (0xF8048004U) /**< \brief (ISI) ISI Configuration 2 Register */
  #define REG_ISI_PSIZE                       (0xF8048008U) /**< \brief (ISI) ISI Preview Size Register */
  #define REG_ISI_PDECF                       (0xF804800CU) /**< \brief (ISI) ISI Preview Decimation Factor Register */
  #define REG_ISI_Y2R_SET0                    (0xF8048010U) /**< \brief (ISI) ISI Color Space Conversion YCrCb To RGB Set 0 Register */
  #define REG_ISI_Y2R_SET1                    (0xF8048014U) /**< \brief (ISI) ISI Color Space Conversion YCrCb To RGB Set 1 Register */
  #define REG_ISI_R2Y_SET0                    (0xF8048018U) /**< \brief (ISI) ISI Color Space Conversion RGB To YCrCb Set 0 Register */
  #define REG_ISI_R2Y_SET1                    (0xF804801CU) /**< \brief (ISI) ISI Color Space Conversion RGB To YCrCb Set 1 Register */
  #define REG_ISI_R2Y_SET2                    (0xF8048020U) /**< \brief (ISI) ISI Color Space Conversion RGB To YCrCb Set 2 Register */
  #define REG_ISI_CR                          (0xF8048024U) /**< \brief (ISI) ISI Control Register */
  #define REG_ISI_SR                          (0xF8048028U) /**< \brief (ISI) ISI Status Register */
  #define REG_ISI_IER                         (0xF804802CU) /**< \brief (ISI) ISI Interrupt Enable Register */
  #define REG_ISI_IDR                         (0xF8048030U) /**< \brief (ISI) ISI Interrupt Disable Register */
  #define REG_ISI_IMR                         (0xF8048034U) /**< \brief (ISI) ISI Interrupt Mask Register */
  #define REG_ISI_DMA_CHER                    (0xF8048038U) /**< \brief (ISI) DMA Channel Enable Register */
  #define REG_ISI_DMA_CHDR                    (0xF804803CU) /**< \brief (ISI) DMA Channel Disable Register */
  #define REG_ISI_DMA_CHSR                    (0xF8048040U) /**< \brief (ISI) DMA Channel Status Register */
  #define REG_ISI_DMA_P_ADDR                  (0xF8048044U) /**< \brief (ISI) DMA Preview Base Address Register */
  #define REG_ISI_DMA_P_CTRL                  (0xF8048048U) /**< \brief (ISI) DMA Preview Control Register */
  #define REG_ISI_DMA_P_DSCR                  (0xF804804CU) /**< \brief (ISI) DMA Preview Descriptor Address Register */
  #define REG_ISI_DMA_C_ADDR                  (0xF8048050U) /**< \brief (ISI) DMA Codec Base Address Register */
  #define REG_ISI_DMA_C_CTRL                  (0xF8048054U) /**< \brief (ISI) DMA Codec Control Register */
  #define REG_ISI_DMA_C_DSCR                  (0xF8048058U) /**< \brief (ISI) DMA Codec Descriptor Address Register */
  #define REG_ISI_WPMR                        (0xF80480E4U) /**< \brief (ISI) Write Protection Mode Register */
  #define REG_ISI_WPSR                        (0xF80480E8U) /**< \brief (ISI) Write Protection Status Register */
#else
  #define REG_ISI_CFG1       (*(__IO uint32_t*)0xF8048000U) /**< \brief (ISI) ISI Configuration 1 Register */
  #define REG_ISI_CFG2       (*(__IO uint32_t*)0xF8048004U) /**< \brief (ISI) ISI Configuration 2 Register */
  #define REG_ISI_PSIZE      (*(__IO uint32_t*)0xF8048008U) /**< \brief (ISI) ISI Preview Size Register */
  #define REG_ISI_PDECF      (*(__IO uint32_t*)0xF804800CU) /**< \brief (ISI) ISI Preview Decimation Factor Register */
  #define REG_ISI_Y2R_SET0   (*(__IO uint32_t*)0xF8048010U) /**< \brief (ISI) ISI Color Space Conversion YCrCb To RGB Set 0 Register */
  #define REG_ISI_Y2R_SET1   (*(__IO uint32_t*)0xF8048014U) /**< \brief (ISI) ISI Color Space Conversion YCrCb To RGB Set 1 Register */
  #define REG_ISI_R2Y_SET0   (*(__IO uint32_t*)0xF8048018U) /**< \brief (ISI) ISI Color Space Conversion RGB To YCrCb Set 0 Register */
  #define REG_ISI_R2Y_SET1   (*(__IO uint32_t*)0xF804801CU) /**< \brief (ISI) ISI Color Space Conversion RGB To YCrCb Set 1 Register */
  #define REG_ISI_R2Y_SET2   (*(__IO uint32_t*)0xF8048020U) /**< \brief (ISI) ISI Color Space Conversion RGB To YCrCb Set 2 Register */
  #define REG_ISI_CR         (*(__O  uint32_t*)0xF8048024U) /**< \brief (ISI) ISI Control Register */
  #define REG_ISI_SR         (*(__I  uint32_t*)0xF8048028U) /**< \brief (ISI) ISI Status Register */
  #define REG_ISI_IER        (*(__O  uint32_t*)0xF804802CU) /**< \brief (ISI) ISI Interrupt Enable Register */
  #define REG_ISI_IDR        (*(__O  uint32_t*)0xF8048030U) /**< \brief (ISI) ISI Interrupt Disable Register */
  #define REG_ISI_IMR        (*(__I  uint32_t*)0xF8048034U) /**< \brief (ISI) ISI Interrupt Mask Register */
  #define REG_ISI_DMA_CHER   (*(__O  uint32_t*)0xF8048038U) /**< \brief (ISI) DMA Channel Enable Register */
  #define REG_ISI_DMA_CHDR   (*(__O  uint32_t*)0xF804803CU) /**< \brief (ISI) DMA Channel Disable Register */
  #define REG_ISI_DMA_CHSR   (*(__I  uint32_t*)0xF8048040U) /**< \brief (ISI) DMA Channel Status Register */
  #define REG_ISI_DMA_P_ADDR (*(__IO uint32_t*)0xF8048044U) /**< \brief (ISI) DMA Preview Base Address Register */
  #define REG_ISI_DMA_P_CTRL (*(__IO uint32_t*)0xF8048048U) /**< \brief (ISI) DMA Preview Control Register */
  #define REG_ISI_DMA_P_DSCR (*(__IO uint32_t*)0xF804804CU) /**< \brief (ISI) DMA Preview Descriptor Address Register */
  #define REG_ISI_DMA_C_ADDR (*(__IO uint32_t*)0xF8048050U) /**< \brief (ISI) DMA Codec Base Address Register */
  #define REG_ISI_DMA_C_CTRL (*(__IO uint32_t*)0xF8048054U) /**< \brief (ISI) DMA Codec Control Register */
  #define REG_ISI_DMA_C_DSCR (*(__IO uint32_t*)0xF8048058U) /**< \brief (ISI) DMA Codec Descriptor Address Register */
  #define REG_ISI_WPMR       (*(__IO uint32_t*)0xF80480E4U) /**< \brief (ISI) Write Protection Mode Register */
  #define REG_ISI_WPSR       (*(__I  uint32_t*)0xF80480E8U) /**< \brief (ISI) Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_ISI_INSTANCE_ */
