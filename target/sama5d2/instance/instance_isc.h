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

#ifndef _SAMA5D2_ISC_INSTANCE_
#define _SAMA5D2_ISC_INSTANCE_

/* ========== Register definition for ISC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_ISC_CTRLEN                        (0xF0008000U) /**< \brief (ISC) Control Enable Register */
  #define REG_ISC_CTRLDIS                       (0xF0008004U) /**< \brief (ISC) Control Disable Register */
  #define REG_ISC_CTRLSR                        (0xF0008008U) /**< \brief (ISC) Control Status Register */
  #define REG_ISC_PFE_CFG0                      (0xF000800CU) /**< \brief (ISC) Parallel Front End Configuration 0 Register */
  #define REG_ISC_PFE_CFG1                      (0xF0008010U) /**< \brief (ISC) Parallel Front End Configuration 1 Register */
  #define REG_ISC_PFE_CFG2                      (0xF0008014U) /**< \brief (ISC) Parallel Front End Configuration 2 Register */
  #define REG_ISC_CLKEN                         (0xF0008018U) /**< \brief (ISC) Clock Enable Register */
  #define REG_ISC_CLKDIS                        (0xF000801CU) /**< \brief (ISC) Clock Disable Register */
  #define REG_ISC_CLKSR                         (0xF0008020U) /**< \brief (ISC) Clock Status Register */
  #define REG_ISC_CLKCFG                        (0xF0008024U) /**< \brief (ISC) Clock Configuration Register */
  #define REG_ISC_INTEN                         (0xF0008028U) /**< \brief (ISC) Interrupt Enable Register */
  #define REG_ISC_INTDIS                        (0xF000802CU) /**< \brief (ISC) Interrupt Disable Register */
  #define REG_ISC_INTMASK                       (0xF0008030U) /**< \brief (ISC) Interrupt Mask Register */
  #define REG_ISC_INTSR                         (0xF0008034U) /**< \brief (ISC) Interrupt Status Register */
  #define REG_ISC_WB_CTRL                       (0xF0008058U) /**< \brief (ISC) White Balance Control Register */
  #define REG_ISC_WB_CFG                        (0xF000805CU) /**< \brief (ISC) White Balance Configuration Register */
  #define REG_ISC_WB_O_RGR                      (0xF0008060U) /**< \brief (ISC) White Balance Offset for R, GR Register */
  #define REG_ISC_WB_O_BGB                      (0xF0008064U) /**< \brief (ISC) White Balance Offset for B, GB Register */
  #define REG_ISC_WB_G_RGR                      (0xF0008068U) /**< \brief (ISC) White Balance Gain for R, GR Register */
  #define REG_ISC_WB_G_BGB                      (0xF000806CU) /**< \brief (ISC) White Balance Gain for B, GB Register */
  #define REG_ISC_CFA_CTRL                      (0xF0008070U) /**< \brief (ISC) Color Filter Array Control Register */
  #define REG_ISC_CFA_CFG                       (0xF0008074U) /**< \brief (ISC) Color Filter Array Configuration Register */
  #define REG_ISC_CC_CTRL                       (0xF0008078U) /**< \brief (ISC) Color Correction Control Register */
  #define REG_ISC_CC_RR_RG                      (0xF000807CU) /**< \brief (ISC) Color Correction RR RG Register */
  #define REG_ISC_CC_RB_OR                      (0xF0008080U) /**< \brief (ISC) Color Correction RB OR Register */
  #define REG_ISC_CC_GR_GG                      (0xF0008084U) /**< \brief (ISC) Color Correction GR GG Register */
  #define REG_ISC_CC_GB_OG                      (0xF0008088U) /**< \brief (ISC) Color Correction GB OG Register */
  #define REG_ISC_CC_BR_BG                      (0xF000808CU) /**< \brief (ISC) Color Correction BR BG Register */
  #define REG_ISC_CC_BB_OB                      (0xF0008090U) /**< \brief (ISC) Color Correction BB OB Register */
  #define REG_ISC_GAM_CTRL                      (0xF0008094U) /**< \brief (ISC) Gamma Correction Control Register */
  #define REG_ISC_GAM_BENTRY                    (0xF0008098U) /**< \brief (ISC) Gamma Correction Blue Entry */
  #define REG_ISC_GAM_GENTRY                    (0xF0008198U) /**< \brief (ISC) Gamma Correction Green Entry */
  #define REG_ISC_GAM_RENTRY                    (0xF0008298U) /**< \brief (ISC) Gamma Correction Red Entry */
  #define REG_ISC_CSC_CTRL                      (0xF0008398U) /**< \brief (ISC) Color Space Conversion Control Register */
  #define REG_ISC_CSC_YR_YG                     (0xF000839CU) /**< \brief (ISC) Color Space Conversion YR, YG Register */
  #define REG_ISC_CSC_YB_OY                     (0xF00083A0U) /**< \brief (ISC) Color Space Conversion YB, OY Register */
  #define REG_ISC_CSC_CBR_CBG                   (0xF00083A4U) /**< \brief (ISC) Color Space Conversion CBR CBG Register */
  #define REG_ISC_CSC_CBB_OCB                   (0xF00083A8U) /**< \brief (ISC) Color Space Conversion CBB OCB Register */
  #define REG_ISC_CSC_CRR_CRG                   (0xF00083ACU) /**< \brief (ISC) Color Space Conversion CRR CRG Register */
  #define REG_ISC_CSC_CRB_OCR                   (0xF00083B0U) /**< \brief (ISC) Color Space Conversion CRB OCR Register */
  #define REG_ISC_CBC_CTRL                      (0xF00083B4U) /**< \brief (ISC) Contrast and Brightness Control Register */
  #define REG_ISC_CBC_CFG                       (0xF00083B8U) /**< \brief (ISC) Contrast and Brightness Configuration Register */
  #define REG_ISC_CBC_BRIGHT                    (0xF00083BCU) /**< \brief (ISC) Contrast and Brightness, Brightness Register */
  #define REG_ISC_CBC_CONTRAST                  (0xF00083C0U) /**< \brief (ISC) Contrast and Brightness, Contrast Register */
  #define REG_ISC_SUB422_CTRL                   (0xF00083C4U) /**< \brief (ISC) Subsampling 4:4:4 to 4:2:2 Control Register */
  #define REG_ISC_SUB422_CFG                    (0xF00083C8U) /**< \brief (ISC) Subsampling 4:4:4 to 4:2:2 Configuration Register */
  #define REG_ISC_SUB420_CTRL                   (0xF00083CCU) /**< \brief (ISC) Subsampling 4:2:2 to 4:2:0 Control Register */
  #define REG_ISC_RLP_CFG                       (0xF00083D0U) /**< \brief (ISC) Rounding, Limiting and Packing Config Register */
  #define REG_ISC_HIS_CTRL                      (0xF00083D4U) /**< \brief (ISC) Histogram Control Register */
  #define REG_ISC_HIS_CFG                       (0xF00083D8U) /**< \brief (ISC) Histogram Configuration Register */
  #define REG_ISC_DCFG                          (0xF00083E0U) /**< \brief (ISC) DMA Configuration Register */
  #define REG_ISC_DCTRL                         (0xF00083E4U) /**< \brief (ISC) DMA Control Register */
  #define REG_ISC_DNDA                          (0xF00083E8U) /**< \brief (ISC) DMA Descriptor Address Register */
  #define REG_ISC_DAD0                          (0xF00083ECU) /**< \brief (ISC) DMA Address 0 Register */
  #define REG_ISC_DST0                          (0xF00083F0U) /**< \brief (ISC) DMA Stride 0 Register */
  #define REG_ISC_DAD1                          (0xF00083F4U) /**< \brief (ISC) DMA Address 1 Register */
  #define REG_ISC_DST1                          (0xF00083F8U) /**< \brief (ISC) DMA Stride 1 Register */
  #define REG_ISC_DAD2                          (0xF00083FCU) /**< \brief (ISC) DMA Address 2 Register */
  #define REG_ISC_DST2                          (0xF0008400U) /**< \brief (ISC) DMA Stride 2 Register */
  #define REG_IPB_VERSION                       (0xF000840CU) /**< \brief (ISC) Version Register */
  #define REG_ISC_HIS_ENTRY                     (0xF0008410U) /**< \brief (ISC) Histogram Entry */
#else
  #define REG_ISC_CTRLEN       (*(__O  uint32_t*)0xF0008000U) /**< \brief (ISC) Control Enable Register */
  #define REG_ISC_CTRLDIS      (*(__O  uint32_t*)0xF0008004U) /**< \brief (ISC) Control Disable Register */
  #define REG_ISC_CTRLSR       (*(__I  uint32_t*)0xF0008008U) /**< \brief (ISC) Control Status Register */
  #define REG_ISC_PFE_CFG0     (*(__IO uint32_t*)0xF000800CU) /**< \brief (ISC) Parallel Front End Configuration 0 Register */
  #define REG_ISC_PFE_CFG1     (*(__IO uint32_t*)0xF0008010U) /**< \brief (ISC) Parallel Front End Configuration 1 Register */
  #define REG_ISC_PFE_CFG2     (*(__IO uint32_t*)0xF0008014U) /**< \brief (ISC) Parallel Front End Configuration 2 Register */
  #define REG_ISC_CLKEN        (*(__O  uint32_t*)0xF0008018U) /**< \brief (ISC) Clock Enable Register */
  #define REG_ISC_CLKDIS       (*(__O  uint32_t*)0xF000801CU) /**< \brief (ISC) Clock Disable Register */
  #define REG_ISC_CLKSR        (*(__I  uint32_t*)0xF0008020U) /**< \brief (ISC) Clock Status Register */
  #define REG_ISC_CLKCFG       (*(__IO uint32_t*)0xF0008024U) /**< \brief (ISC) Clock Configuration Register */
  #define REG_ISC_INTEN        (*(__O  uint32_t*)0xF0008028U) /**< \brief (ISC) Interrupt Enable Register */
  #define REG_ISC_INTDIS       (*(__O  uint32_t*)0xF000802CU) /**< \brief (ISC) Interrupt Disable Register */
  #define REG_ISC_INTMASK      (*(__I  uint32_t*)0xF0008030U) /**< \brief (ISC) Interrupt Mask Register */
  #define REG_ISC_INTSR        (*(__I  uint32_t*)0xF0008034U) /**< \brief (ISC) Interrupt Status Register */
  #define REG_ISC_WB_CTRL      (*(__IO uint32_t*)0xF0008058U) /**< \brief (ISC) White Balance Control Register */
  #define REG_ISC_WB_CFG       (*(__IO uint32_t*)0xF000805CU) /**< \brief (ISC) White Balance Configuration Register */
  #define REG_ISC_WB_O_RGR     (*(__IO uint32_t*)0xF0008060U) /**< \brief (ISC) White Balance Offset for R, GR Register */
  #define REG_ISC_WB_O_BGB     (*(__IO uint32_t*)0xF0008064U) /**< \brief (ISC) White Balance Offset for B, GB Register */
  #define REG_ISC_WB_G_RGR     (*(__IO uint32_t*)0xF0008068U) /**< \brief (ISC) White Balance Gain for R, GR Register */
  #define REG_ISC_WB_G_BGB     (*(__IO uint32_t*)0xF000806CU) /**< \brief (ISC) White Balance Gain for B, GB Register */
  #define REG_ISC_CFA_CTRL     (*(__IO uint32_t*)0xF0008070U) /**< \brief (ISC) Color Filter Array Control Register */
  #define REG_ISC_CFA_CFG      (*(__IO uint32_t*)0xF0008074U) /**< \brief (ISC) Color Filter Array Configuration Register */
  #define REG_ISC_CC_CTRL      (*(__IO uint32_t*)0xF0008078U) /**< \brief (ISC) Color Correction Control Register */
  #define REG_ISC_CC_RR_RG     (*(__IO uint32_t*)0xF000807CU) /**< \brief (ISC) Color Correction RR RG Register */
  #define REG_ISC_CC_RB_OR     (*(__IO uint32_t*)0xF0008080U) /**< \brief (ISC) Color Correction RB OR Register */
  #define REG_ISC_CC_GR_GG     (*(__IO uint32_t*)0xF0008084U) /**< \brief (ISC) Color Correction GR GG Register */
  #define REG_ISC_CC_GB_OG     (*(__IO uint32_t*)0xF0008088U) /**< \brief (ISC) Color Correction GB OG Register */
  #define REG_ISC_CC_BR_BG     (*(__IO uint32_t*)0xF000808CU) /**< \brief (ISC) Color Correction BR BG Register */
  #define REG_ISC_CC_BB_OB     (*(__IO uint32_t*)0xF0008090U) /**< \brief (ISC) Color Correction BB OB Register */
  #define REG_ISC_GAM_CTRL     (*(__IO uint32_t*)0xF0008094U) /**< \brief (ISC) Gamma Correction Control Register */
  #define REG_ISC_GAM_BENTRY   (*(__IO uint32_t*)0xF0008098U) /**< \brief (ISC) Gamma Correction Blue Entry */
  #define REG_ISC_GAM_GENTRY   (*(__IO uint32_t*)0xF0008198U) /**< \brief (ISC) Gamma Correction Green Entry */
  #define REG_ISC_GAM_RENTRY   (*(__IO uint32_t*)0xF0008298U) /**< \brief (ISC) Gamma Correction Red Entry */
  #define REG_ISC_CSC_CTRL     (*(__IO uint32_t*)0xF0008398U) /**< \brief (ISC) Color Space Conversion Control Register */
  #define REG_ISC_CSC_YR_YG    (*(__IO uint32_t*)0xF000839CU) /**< \brief (ISC) Color Space Conversion YR, YG Register */
  #define REG_ISC_CSC_YB_OY    (*(__IO uint32_t*)0xF00083A0U) /**< \brief (ISC) Color Space Conversion YB, OY Register */
  #define REG_ISC_CSC_CBR_CBG  (*(__IO uint32_t*)0xF00083A4U) /**< \brief (ISC) Color Space Conversion CBR CBG Register */
  #define REG_ISC_CSC_CBB_OCB  (*(__IO uint32_t*)0xF00083A8U) /**< \brief (ISC) Color Space Conversion CBB OCB Register */
  #define REG_ISC_CSC_CRR_CRG  (*(__IO uint32_t*)0xF00083ACU) /**< \brief (ISC) Color Space Conversion CRR CRG Register */
  #define REG_ISC_CSC_CRB_OCR  (*(__IO uint32_t*)0xF00083B0U) /**< \brief (ISC) Color Space Conversion CRB OCR Register */
  #define REG_ISC_CBC_CTRL     (*(__IO uint32_t*)0xF00083B4U) /**< \brief (ISC) Contrast and Brightness Control Register */
  #define REG_ISC_CBC_CFG      (*(__IO uint32_t*)0xF00083B8U) /**< \brief (ISC) Contrast and Brightness Configuration Register */
  #define REG_ISC_CBC_BRIGHT   (*(__IO uint32_t*)0xF00083BCU) /**< \brief (ISC) Contrast and Brightness, Brightness Register */
  #define REG_ISC_CBC_CONTRAST (*(__IO uint32_t*)0xF00083C0U) /**< \brief (ISC) Contrast and Brightness, Contrast Register */
  #define REG_ISC_SUB422_CTRL  (*(__IO uint32_t*)0xF00083C4U) /**< \brief (ISC) Subsampling 4:4:4 to 4:2:2 Control Register */
  #define REG_ISC_SUB422_CFG   (*(__IO uint32_t*)0xF00083C8U) /**< \brief (ISC) Subsampling 4:4:4 to 4:2:2 Configuration Register */
  #define REG_ISC_SUB420_CTRL  (*(__IO uint32_t*)0xF00083CCU) /**< \brief (ISC) Subsampling 4:2:2 to 4:2:0 Control Register */
  #define REG_ISC_RLP_CFG      (*(__IO uint32_t*)0xF00083D0U) /**< \brief (ISC) Rounding, Limiting and Packing Config Register */
  #define REG_ISC_HIS_CTRL     (*(__IO uint32_t*)0xF00083D4U) /**< \brief (ISC) Histogram Control Register */
  #define REG_ISC_HIS_CFG      (*(__IO uint32_t*)0xF00083D8U) /**< \brief (ISC) Histogram Configuration Register */
  #define REG_ISC_DCFG         (*(__IO uint32_t*)0xF00083E0U) /**< \brief (ISC) DMA Configuration Register */
  #define REG_ISC_DCTRL        (*(__IO uint32_t*)0xF00083E4U) /**< \brief (ISC) DMA Control Register */
  #define REG_ISC_DNDA         (*(__IO uint32_t*)0xF00083E8U) /**< \brief (ISC) DMA Descriptor Address Register */
  #define REG_ISC_DAD0         (*(__IO uint32_t*)0xF00083ECU) /**< \brief (ISC) DMA Address 0 Register */
  #define REG_ISC_DST0         (*(__IO uint32_t*)0xF00083F0U) /**< \brief (ISC) DMA Stride 0 Register */
  #define REG_ISC_DAD1         (*(__IO uint32_t*)0xF00083F4U) /**< \brief (ISC) DMA Address 1 Register */
  #define REG_ISC_DST1         (*(__IO uint32_t*)0xF00083F8U) /**< \brief (ISC) DMA Stride 1 Register */
  #define REG_ISC_DAD2         (*(__IO uint32_t*)0xF00083FCU) /**< \brief (ISC) DMA Address 2 Register */
  #define REG_ISC_DST2         (*(__IO uint32_t*)0xF0008400U) /**< \brief (ISC) DMA Stride 2 Register */
  #define REG_IPB_VERSION      (*(__I  uint32_t*)0xF000840CU) /**< \brief (ISC) Version Register */
  #define REG_ISC_HIS_ENTRY    (*(__I  uint32_t*)0xF0008410U) /**< \brief (ISC) Histogram Entry */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_ISC_INSTANCE_ */
