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

#ifndef _SAM9X_LCDC_INSTANCE_
#define _SAM9X_LCDC_INSTANCE_

/* ========== Register definition for LCDC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_LCDC_LCDCFG0                   (0xF8038000U) /**< \brief (LCDC) LCD Controller Configuration Register 0 */
  #define REG_LCDC_LCDCFG1                   (0xF8038004U) /**< \brief (LCDC) LCD Controller Configuration Register 1 */
  #define REG_LCDC_LCDCFG2                   (0xF8038008U) /**< \brief (LCDC) LCD Controller Configuration Register 2 */
  #define REG_LCDC_LCDCFG3                   (0xF803800CU) /**< \brief (LCDC) LCD Controller Configuration Register 3 */
  #define REG_LCDC_LCDCFG4                   (0xF8038010U) /**< \brief (LCDC) LCD Controller Configuration Register 4 */
  #define REG_LCDC_LCDCFG5                   (0xF8038014U) /**< \brief (LCDC) LCD Controller Configuration Register 5 */
  #define REG_LCDC_LCDCFG6                   (0xF8038018U) /**< \brief (LCDC) LCD Controller Configuration Register 6 */
  #define REG_LCDC_LCDCFG7                   (0xF803801CU) /**< \brief (LCDC) LCD Controller Configuration Register 7 */
  #define REG_LCDC_LCDEN                     (0xF8038020U) /**< \brief (LCDC) LCD Controller Enable Register */
  #define REG_LCDC_LCDDIS                    (0xF8038024U) /**< \brief (LCDC) LCD Controller Disable Register */
  #define REG_LCDC_LCDSR                     (0xF8038028U) /**< \brief (LCDC) LCD Controller Status Register */
  #define REG_LCDC_LCDIER                    (0xF803802CU) /**< \brief (LCDC) LCD Controller Interrupt Enable Register */
  #define REG_LCDC_LCDIDR                    (0xF8038030U) /**< \brief (LCDC) LCD Controller Interrupt Disable Register */
  #define REG_LCDC_LCDIMR                    (0xF8038034U) /**< \brief (LCDC) LCD Controller Interrupt Mask Register */
  #define REG_LCDC_LCDISR                    (0xF8038038U) /**< \brief (LCDC) LCD Controller Interrupt Status Register */
  #define REG_LCDC_ATTR                      (0xF803803CU) /**< \brief (LCDC) LCD Controller Attribute Register */
  #define REG_LCDC_QOSCFG                    (0xF8038040U) /**< \brief (LCDC) LCD Controller QoS Configuration Register */
  #define REG_LCDC_QOS1M                     (0xF8038044U) /**< \brief (LCDC) LCD Controller QoS 1 Metrics Register */
  #define REG_LCDC_QOS2M                     (0xF8038048U) /**< \brief (LCDC) LCD Controller QoS 2 Metrics Register */
  #define REG_LCDC_QOS3M                     (0xF803804CU) /**< \brief (LCDC) LCD Controller QoS 3 Metrics Register */
  #define REG_LCDC_QOSMIN                    (0xF8038050U) /**< \brief (LCDC) LCD Controller QoS Min FIFO Level Register */
  #define REG_LCDC_BASECHER                  (0xF8038060U) /**< \brief (LCDC) Base Layer Channel Enable Register */
  #define REG_LCDC_BASECHDR                  (0xF8038064U) /**< \brief (LCDC) Base Layer Channel Disable Register */
  #define REG_LCDC_BASECHSR                  (0xF8038068U) /**< \brief (LCDC) Base Layer Channel Status Register */
  #define REG_LCDC_BASEIER                   (0xF803806CU) /**< \brief (LCDC) Base Layer Interrupt Enable Register */
  #define REG_LCDC_BASEIDR                   (0xF8038070U) /**< \brief (LCDC) Base Layer Interrupt Disabled Register */
  #define REG_LCDC_BASEIMR                   (0xF8038074U) /**< \brief (LCDC) Base Layer Interrupt Mask Register */
  #define REG_LCDC_BASEISR                   (0xF8038078U) /**< \brief (LCDC) Base Layer Interrupt Status Register */
  #define REG_LCDC_BASEHEAD                  (0xF803807CU) /**< \brief (LCDC) Base DMA Head Register */
  #define REG_LCDC_BASEADDR                  (0xF8038080U) /**< \brief (LCDC) Base DMA Address Register */
  #define REG_LCDC_BASECTRL                  (0xF8038084U) /**< \brief (LCDC) Base DMA Control Register */
  #define REG_LCDC_BASENEXT                  (0xF8038088U) /**< \brief (LCDC) Base DMA Next Register */
  #define REG_LCDC_BASECFG0                  (0xF803808CU) /**< \brief (LCDC) Base Layer Configuration Register 0 */
  #define REG_LCDC_BASECFG1                  (0xF8038090U) /**< \brief (LCDC) Base Layer Configuration Register 1 */
  #define REG_LCDC_BASECFG2                  (0xF8038094U) /**< \brief (LCDC) Base Layer Configuration Register 2 */
  #define REG_LCDC_BASECFG3                  (0xF8038098U) /**< \brief (LCDC) Base Layer Configuration Register 3 */
  #define REG_LCDC_BASECFG4                  (0xF803809CU) /**< \brief (LCDC) Base Layer Configuration Register 4 */
  #define REG_LCDC_BASECFG5                  (0xF80380A0U) /**< \brief (LCDC) Base Layer Configuration Register 5 */
  #define REG_LCDC_BASECFG6                  (0xF80380A4U) /**< \brief (LCDC) Base Layer Configuration Register 6 */
  #define REG_LCDC_OVR1CHER                  (0xF8038160U) /**< \brief (LCDC) Overlay 1 Channel Enable Register */
  #define REG_LCDC_OVR1CHDR                  (0xF8038164U) /**< \brief (LCDC) Overlay 1 Channel Disable Register */
  #define REG_LCDC_OVR1CHSR                  (0xF8038168U) /**< \brief (LCDC) Overlay 1 Channel Status Register */
  #define REG_LCDC_OVR1IER                   (0xF803816CU) /**< \brief (LCDC) Overlay 1 Interrupt Enable Register */
  #define REG_LCDC_OVR1IDR                   (0xF8038170U) /**< \brief (LCDC) Overlay 1 Interrupt Disable Register */
  #define REG_LCDC_OVR1IMR                   (0xF8038174U) /**< \brief (LCDC) Overlay 1 Interrupt Mask Register */
  #define REG_LCDC_OVR1ISR                   (0xF8038178U) /**< \brief (LCDC) Overlay 1 Interrupt Status Register */
  #define REG_LCDC_OVR1HEAD                  (0xF803817CU) /**< \brief (LCDC) Overlay 1 DMA Head Register */
  #define REG_LCDC_OVR1ADDR                  (0xF8038180U) /**< \brief (LCDC) Overlay 1 DMA Address Register */
  #define REG_LCDC_OVR1CTRL                  (0xF8038184U) /**< \brief (LCDC) Overlay 1 DMA Control Register */
  #define REG_LCDC_OVR1NEXT                  (0xF8038188U) /**< \brief (LCDC) Overlay 1 DMA Next Register */
  #define REG_LCDC_OVR1CFG0                  (0xF803818CU) /**< \brief (LCDC) Overlay 1 Configuration Register 0 */
  #define REG_LCDC_OVR1CFG1                  (0xF8038190U) /**< \brief (LCDC) Overlay 1 Configuration Register 1 */
  #define REG_LCDC_OVR1CFG2                  (0xF8038194U) /**< \brief (LCDC) Overlay 1 Configuration Register 2 */
  #define REG_LCDC_OVR1CFG3                  (0xF8038198U) /**< \brief (LCDC) Overlay 1 Configuration Register 3 */
  #define REG_LCDC_OVR1CFG4                  (0xF803819CU) /**< \brief (LCDC) Overlay 1 Configuration Register 4 */
  #define REG_LCDC_OVR1CFG5                  (0xF80381A0U) /**< \brief (LCDC) Overlay 1 Configuration Register 5 */
  #define REG_LCDC_OVR1CFG6                  (0xF80381A4U) /**< \brief (LCDC) Overlay 1 Configuration Register 6 */
  #define REG_LCDC_OVR1CFG7                  (0xF80381A8U) /**< \brief (LCDC) Overlay 1 Configuration Register 7 */
  #define REG_LCDC_OVR1CFG8                  (0xF80381ACU) /**< \brief (LCDC) Overlay 1 Configuration Register 8 */
  #define REG_LCDC_OVR1CFG9                  (0xF80381B0U) /**< \brief (LCDC) Overlay 1 Configuration Register 9 */
  #define REG_LCDC_OVR2CHER                  (0xF8038260U) /**< \brief (LCDC) Overlay 2 Channel Enable Register */
  #define REG_LCDC_OVR2CHDR                  (0xF8038264U) /**< \brief (LCDC) Overlay 2 Channel Disable Register */
  #define REG_LCDC_OVR2CHSR                  (0xF8038268U) /**< \brief (LCDC) Overlay 2 Channel Status Register */
  #define REG_LCDC_OVR2IER                   (0xF803826CU) /**< \brief (LCDC) Overlay 2 Interrupt Enable Register */
  #define REG_LCDC_OVR2IDR                   (0xF8038270U) /**< \brief (LCDC) Overlay 2 Interrupt Disable Register */
  #define REG_LCDC_OVR2IMR                   (0xF8038274U) /**< \brief (LCDC) Overlay 2 Interrupt Mask Register */
  #define REG_LCDC_OVR2ISR                   (0xF8038278U) /**< \brief (LCDC) Overlay 2 Interrupt Status Register */
  #define REG_LCDC_OVR2HEAD                  (0xF803827CU) /**< \brief (LCDC) Overlay 2 DMA Head Register */
  #define REG_LCDC_OVR2ADDR                  (0xF8038280U) /**< \brief (LCDC) Overlay 2 DMA Address Register */
  #define REG_LCDC_OVR2CTRL                  (0xF8038284U) /**< \brief (LCDC) Overlay 2 DMA Control Register */
  #define REG_LCDC_OVR2NEXT                  (0xF8038288U) /**< \brief (LCDC) Overlay 2 DMA Next Register */
  #define REG_LCDC_OVR2CFG0                  (0xF803828CU) /**< \brief (LCDC) Overlay 2 Configuration Register 0 */
  #define REG_LCDC_OVR2CFG1                  (0xF8038290U) /**< \brief (LCDC) Overlay 2 Configuration Register 1 */
  #define REG_LCDC_OVR2CFG2                  (0xF8038294U) /**< \brief (LCDC) Overlay 2 Configuration Register 2 */
  #define REG_LCDC_OVR2CFG3                  (0xF8038298U) /**< \brief (LCDC) Overlay 2 Configuration Register 3 */
  #define REG_LCDC_OVR2CFG4                  (0xF803829CU) /**< \brief (LCDC) Overlay 2 Configuration Register 4 */
  #define REG_LCDC_OVR2CFG5                  (0xF80382A0U) /**< \brief (LCDC) Overlay 2 Configuration Register 5 */
  #define REG_LCDC_OVR2CFG6                  (0xF80382A4U) /**< \brief (LCDC) Overlay 2 Configuration Register 6 */
  #define REG_LCDC_OVR2CFG7                  (0xF80382A8U) /**< \brief (LCDC) Overlay 2 Configuration Register 7 */
  #define REG_LCDC_OVR2CFG8                  (0xF80382ACU) /**< \brief (LCDC) Overlay 2 Configuration Register 8 */
  #define REG_LCDC_OVR2CFG9                  (0xF80382B0U) /**< \brief (LCDC) Overlay 2 Configuration Register 9 */
  #define REG_LCDC_HEOCHER                   (0xF8038360U) /**< \brief (LCDC) High-End Overlay Channel Enable Register */
  #define REG_LCDC_HEOCHDR                   (0xF8038364U) /**< \brief (LCDC) High-End Overlay Channel Disable Register */
  #define REG_LCDC_HEOCHSR                   (0xF8038368U) /**< \brief (LCDC) High-End Overlay Channel Status Register */
  #define REG_LCDC_HEOIER                    (0xF803836CU) /**< \brief (LCDC) High-End Overlay Interrupt Enable Register */
  #define REG_LCDC_HEOIDR                    (0xF8038370U) /**< \brief (LCDC) High-End Overlay Interrupt Disable Register */
  #define REG_LCDC_HEOIMR                    (0xF8038374U) /**< \brief (LCDC) High-End Overlay Interrupt Mask Register */
  #define REG_LCDC_HEOISR                    (0xF8038378U) /**< \brief (LCDC) High-End Overlay Interrupt Status Register */
  #define REG_LCDC_HEOHEAD                   (0xF803837CU) /**< \brief (LCDC) High-End Overlay DMA Head Register */
  #define REG_LCDC_HEOADDR                   (0xF8038380U) /**< \brief (LCDC) High-End Overlay DMA Address Register */
  #define REG_LCDC_HEOCTRL                   (0xF8038384U) /**< \brief (LCDC) High-End Overlay DMA Control Register */
  #define REG_LCDC_HEONEXT                   (0xF8038388U) /**< \brief (LCDC) High-End Overlay DMA Next Register */
  #define REG_LCDC_HEOUHEAD                  (0xF803838CU) /**< \brief (LCDC) High-End Overlay U-UV DMA Head Register */
  #define REG_LCDC_HEOUADDR                  (0xF8038390U) /**< \brief (LCDC) High-End Overlay U-UV DMA Address Register */
  #define REG_LCDC_HEOUCTRL                  (0xF8038394U) /**< \brief (LCDC) High-End Overlay U-UV DMA Control Register */
  #define REG_LCDC_HEOUNEXT                  (0xF8038398U) /**< \brief (LCDC) High-End Overlay U-UV DMA Next Register */
  #define REG_LCDC_HEOVHEAD                  (0xF803839CU) /**< \brief (LCDC) High-End Overlay V DMA Head Register */
  #define REG_LCDC_HEOVADDR                  (0xF80383A0U) /**< \brief (LCDC) High-End Overlay V DMA Address Register */
  #define REG_LCDC_HEOVCTRL                  (0xF80383A4U) /**< \brief (LCDC) High-End Overlay V DMA Control Register */
  #define REG_LCDC_HEOVNEXT                  (0xF80383A8U) /**< \brief (LCDC) High-End Overlay V DMA Next Register */
  #define REG_LCDC_HEOCFG0                   (0xF80383ACU) /**< \brief (LCDC) High-End Overlay Configuration Register 0 */
  #define REG_LCDC_HEOCFG1                   (0xF80383B0U) /**< \brief (LCDC) High-End Overlay Configuration Register 1 */
  #define REG_LCDC_HEOCFG2                   (0xF80383B4U) /**< \brief (LCDC) High-End Overlay Configuration Register 2 */
  #define REG_LCDC_HEOCFG3                   (0xF80383B8U) /**< \brief (LCDC) High-End Overlay Configuration Register 3 */
  #define REG_LCDC_HEOCFG4                   (0xF80383BCU) /**< \brief (LCDC) High-End Overlay Configuration Register 4 */
  #define REG_LCDC_HEOCFG5                   (0xF80383C0U) /**< \brief (LCDC) High-End Overlay Configuration Register 5 */
  #define REG_LCDC_HEOCFG6                   (0xF80383C4U) /**< \brief (LCDC) High-End Overlay Configuration Register 6 */
  #define REG_LCDC_HEOCFG7                   (0xF80383C8U) /**< \brief (LCDC) High-End Overlay Configuration Register 7 */
  #define REG_LCDC_HEOCFG8                   (0xF80383CCU) /**< \brief (LCDC) High-End Overlay Configuration Register 8 */
  #define REG_LCDC_HEOCFG9                   (0xF80383D0U) /**< \brief (LCDC) High-End Overlay Configuration Register 9 */
  #define REG_LCDC_HEOCFG10                  (0xF80383D4U) /**< \brief (LCDC) High-End Overlay Configuration Register 10 */
  #define REG_LCDC_HEOCFG11                  (0xF80383D8U) /**< \brief (LCDC) High-End Overlay Configuration Register 11 */
  #define REG_LCDC_HEOCFG12                  (0xF80383DCU) /**< \brief (LCDC) High-End Overlay Configuration Register 12 */
  #define REG_LCDC_HEOCFG13                  (0xF80383E0U) /**< \brief (LCDC) High-End Overlay Configuration Register 13 */
  #define REG_LCDC_HEOCFG14                  (0xF80383E4U) /**< \brief (LCDC) High-End Overlay Configuration Register 14 */
  #define REG_LCDC_HEOCFG15                  (0xF80383E8U) /**< \brief (LCDC) High-End Overlay Configuration Register 15 */
  #define REG_LCDC_HEOCFG16                  (0xF80383ECU) /**< \brief (LCDC) High-End Overlay Configuration Register 16 */
  #define REG_LCDC_HEOCFG17                  (0xF80383F0U) /**< \brief (LCDC) High-End Overlay Configuration Register 17 */
  #define REG_LCDC_HEOCFG18                  (0xF80383F4U) /**< \brief (LCDC) High-End Overlay Configuration Register 18 */
  #define REG_LCDC_HEOCFG19                  (0xF80383F8U) /**< \brief (LCDC) High-End Overlay Configuration Register 19 */
  #define REG_LCDC_HEOCFG20                  (0xF80383FCU) /**< \brief (LCDC) High-End Overlay Configuration Register 20 */
  #define REG_LCDC_HEOCFG21                  (0xF8038400U) /**< \brief (LCDC) High-End Overlay Configuration Register 21 */
  #define REG_LCDC_HEOCFG22                  (0xF8038404U) /**< \brief (LCDC) High-End Overlay Configuration Register 22 */
  #define REG_LCDC_HEOCFG23                  (0xF8038408U) /**< \brief (LCDC) High-End Overlay Configuration Register 23 */
  #define REG_LCDC_HEOCFG24                  (0xF803840CU) /**< \brief (LCDC) High-End Overlay Configuration Register 24 */
  #define REG_LCDC_HEOCFG25                  (0xF8038410U) /**< \brief (LCDC) High-End Overlay Configuration Register 25 */
  #define REG_LCDC_HEOCFG26                  (0xF8038414U) /**< \brief (LCDC) High-End Overlay Configuration Register 26 */
  #define REG_LCDC_HEOCFG27                  (0xF8038418U) /**< \brief (LCDC) High-End Overlay Configuration Register 27 */
  #define REG_LCDC_HEOCFG28                  (0xF803841CU) /**< \brief (LCDC) High-End Overlay Configuration Register 28 */
  #define REG_LCDC_HEOCFG29                  (0xF8038420U) /**< \brief (LCDC) High-End Overlay Configuration Register 29 */
  #define REG_LCDC_HEOCFG30                  (0xF8038424U) /**< \brief (LCDC) High-End Overlay Configuration Register 30 */
  #define REG_LCDC_HEOCFG31                  (0xF8038428U) /**< \brief (LCDC) High-End Overlay Configuration Register 31 */
  #define REG_LCDC_HEOCFG32                  (0xF803842CU) /**< \brief (LCDC) High-End Overlay Configuration Register 32 */
  #define REG_LCDC_HEOCFG33                  (0xF8038430U) /**< \brief (LCDC) High-End Overlay Configuration Register 33 */
  #define REG_LCDC_HEOCFG34                  (0xF8038434U) /**< \brief (LCDC) High-End Overlay Configuration Register 34 */
  #define REG_LCDC_HEOCFG35                  (0xF8038438U) /**< \brief (LCDC) High-End Overlay Configuration Register 35 */
  #define REG_LCDC_HEOCFG36                  (0xF803843CU) /**< \brief (LCDC) High-End Overlay Configuration Register 36 */
  #define REG_LCDC_HEOCFG37                  (0xF8038440U) /**< \brief (LCDC) High-End Overlay Configuration Register 37 */
  #define REG_LCDC_HEOCFG38                  (0xF8038444U) /**< \brief (LCDC) High-End Overlay Configuration Register 38 */
  #define REG_LCDC_HEOCFG39                  (0xF8038448U) /**< \brief (LCDC) High-End Overlay Configuration Register 39 */
  #define REG_LCDC_HEOCFG40                  (0xF803844CU) /**< \brief (LCDC) High-End Overlay Configuration Register 40 */
  #define REG_LCDC_HEOCFG41                  (0xF8038450U) /**< \brief (LCDC) High-End Overlay Configuration Register 41 */
  #define REG_LCDC_BASECLUT                  (0xF8038600U) /**< \brief (LCDC) Base CLUT Register */
  #define REG_LCDC_OVR1CLUT                  (0xF8038A00U) /**< \brief (LCDC) Overlay 1 CLUT Register */
  #define REG_LCDC_OVR2CLUT                  (0xF8038E00U) /**< \brief (LCDC) Overlay 2 CLUT Register */
  #define REG_LCDC_HEOCLUT                   (0xF8039200U) /**< \brief (LCDC) High-End Overlay CLUT Register */
#else
  #define REG_LCDC_LCDCFG0  (*(__IO uint32_t*)0xF8038000U) /**< \brief (LCDC) LCD Controller Configuration Register 0 */
  #define REG_LCDC_LCDCFG1  (*(__IO uint32_t*)0xF8038004U) /**< \brief (LCDC) LCD Controller Configuration Register 1 */
  #define REG_LCDC_LCDCFG2  (*(__IO uint32_t*)0xF8038008U) /**< \brief (LCDC) LCD Controller Configuration Register 2 */
  #define REG_LCDC_LCDCFG3  (*(__IO uint32_t*)0xF803800CU) /**< \brief (LCDC) LCD Controller Configuration Register 3 */
  #define REG_LCDC_LCDCFG4  (*(__IO uint32_t*)0xF8038010U) /**< \brief (LCDC) LCD Controller Configuration Register 4 */
  #define REG_LCDC_LCDCFG5  (*(__IO uint32_t*)0xF8038014U) /**< \brief (LCDC) LCD Controller Configuration Register 5 */
  #define REG_LCDC_LCDCFG6  (*(__IO uint32_t*)0xF8038018U) /**< \brief (LCDC) LCD Controller Configuration Register 6 */
  #define REG_LCDC_LCDCFG7  (*(__IO uint32_t*)0xF803801CU) /**< \brief (LCDC) LCD Controller Configuration Register 7 */
  #define REG_LCDC_LCDEN    (*(__O  uint32_t*)0xF8038020U) /**< \brief (LCDC) LCD Controller Enable Register */
  #define REG_LCDC_LCDDIS   (*(__O  uint32_t*)0xF8038024U) /**< \brief (LCDC) LCD Controller Disable Register */
  #define REG_LCDC_LCDSR    (*(__I  uint32_t*)0xF8038028U) /**< \brief (LCDC) LCD Controller Status Register */
  #define REG_LCDC_LCDIER   (*(__O  uint32_t*)0xF803802CU) /**< \brief (LCDC) LCD Controller Interrupt Enable Register */
  #define REG_LCDC_LCDIDR   (*(__O  uint32_t*)0xF8038030U) /**< \brief (LCDC) LCD Controller Interrupt Disable Register */
  #define REG_LCDC_LCDIMR   (*(__I  uint32_t*)0xF8038034U) /**< \brief (LCDC) LCD Controller Interrupt Mask Register */
  #define REG_LCDC_LCDISR   (*(__I  uint32_t*)0xF8038038U) /**< \brief (LCDC) LCD Controller Interrupt Status Register */
  #define REG_LCDC_ATTR     (*(__O  uint32_t*)0xF803803CU) /**< \brief (LCDC) LCD Controller Attribute Register */
  #define REG_LCDC_QOSCFG   (*(__IO uint32_t*)0xF8038040U) /**< \brief (LCDC) LCD Controller QoS Configuration Register */
  #define REG_LCDC_QOS1M    (*(__I  uint32_t*)0xF8038044U) /**< \brief (LCDC) LCD Controller QoS 1 Metrics Register */
  #define REG_LCDC_QOS2M    (*(__I  uint32_t*)0xF8038048U) /**< \brief (LCDC) LCD Controller QoS 2 Metrics Register */
  #define REG_LCDC_QOS3M    (*(__I  uint32_t*)0xF803804CU) /**< \brief (LCDC) LCD Controller QoS 3 Metrics Register */
  #define REG_LCDC_QOSMIN   (*(__I  uint32_t*)0xF8038050U) /**< \brief (LCDC) LCD Controller QoS Min FIFO Level Register */
  #define REG_LCDC_BASECHER (*(__O  uint32_t*)0xF8038060U) /**< \brief (LCDC) Base Layer Channel Enable Register */
  #define REG_LCDC_BASECHDR (*(__O  uint32_t*)0xF8038064U) /**< \brief (LCDC) Base Layer Channel Disable Register */
  #define REG_LCDC_BASECHSR (*(__I  uint32_t*)0xF8038068U) /**< \brief (LCDC) Base Layer Channel Status Register */
  #define REG_LCDC_BASEIER  (*(__O  uint32_t*)0xF803806CU) /**< \brief (LCDC) Base Layer Interrupt Enable Register */
  #define REG_LCDC_BASEIDR  (*(__O  uint32_t*)0xF8038070U) /**< \brief (LCDC) Base Layer Interrupt Disabled Register */
  #define REG_LCDC_BASEIMR  (*(__I  uint32_t*)0xF8038074U) /**< \brief (LCDC) Base Layer Interrupt Mask Register */
  #define REG_LCDC_BASEISR  (*(__I  uint32_t*)0xF8038078U) /**< \brief (LCDC) Base Layer Interrupt Status Register */
  #define REG_LCDC_BASEHEAD (*(__IO uint32_t*)0xF803807CU) /**< \brief (LCDC) Base DMA Head Register */
  #define REG_LCDC_BASEADDR (*(__IO uint32_t*)0xF8038080U) /**< \brief (LCDC) Base DMA Address Register */
  #define REG_LCDC_BASECTRL (*(__IO uint32_t*)0xF8038084U) /**< \brief (LCDC) Base DMA Control Register */
  #define REG_LCDC_BASENEXT (*(__IO uint32_t*)0xF8038088U) /**< \brief (LCDC) Base DMA Next Register */
  #define REG_LCDC_BASECFG0 (*(__IO uint32_t*)0xF803808CU) /**< \brief (LCDC) Base Layer Configuration Register 0 */
  #define REG_LCDC_BASECFG1 (*(__IO uint32_t*)0xF8038090U) /**< \brief (LCDC) Base Layer Configuration Register 1 */
  #define REG_LCDC_BASECFG2 (*(__IO uint32_t*)0xF8038094U) /**< \brief (LCDC) Base Layer Configuration Register 2 */
  #define REG_LCDC_BASECFG3 (*(__IO uint32_t*)0xF8038098U) /**< \brief (LCDC) Base Layer Configuration Register 3 */
  #define REG_LCDC_BASECFG4 (*(__IO uint32_t*)0xF803809CU) /**< \brief (LCDC) Base Layer Configuration Register 4 */
  #define REG_LCDC_BASECFG5 (*(__IO uint32_t*)0xF80380A0U) /**< \brief (LCDC) Base Layer Configuration Register 5 */
  #define REG_LCDC_BASECFG6 (*(__IO uint32_t*)0xF80380A4U) /**< \brief (LCDC) Base Layer Configuration Register 6 */
  #define REG_LCDC_OVR1CHER (*(__O  uint32_t*)0xF8038160U) /**< \brief (LCDC) Overlay 1 Channel Enable Register */
  #define REG_LCDC_OVR1CHDR (*(__O  uint32_t*)0xF8038164U) /**< \brief (LCDC) Overlay 1 Channel Disable Register */
  #define REG_LCDC_OVR1CHSR (*(__I  uint32_t*)0xF8038168U) /**< \brief (LCDC) Overlay 1 Channel Status Register */
  #define REG_LCDC_OVR1IER  (*(__O  uint32_t*)0xF803816CU) /**< \brief (LCDC) Overlay 1 Interrupt Enable Register */
  #define REG_LCDC_OVR1IDR  (*(__O  uint32_t*)0xF8038170U) /**< \brief (LCDC) Overlay 1 Interrupt Disable Register */
  #define REG_LCDC_OVR1IMR  (*(__I  uint32_t*)0xF8038174U) /**< \brief (LCDC) Overlay 1 Interrupt Mask Register */
  #define REG_LCDC_OVR1ISR  (*(__I  uint32_t*)0xF8038178U) /**< \brief (LCDC) Overlay 1 Interrupt Status Register */
  #define REG_LCDC_OVR1HEAD (*(__IO uint32_t*)0xF803817CU) /**< \brief (LCDC) Overlay 1 DMA Head Register */
  #define REG_LCDC_OVR1ADDR (*(__IO uint32_t*)0xF8038180U) /**< \brief (LCDC) Overlay 1 DMA Address Register */
  #define REG_LCDC_OVR1CTRL (*(__IO uint32_t*)0xF8038184U) /**< \brief (LCDC) Overlay 1 DMA Control Register */
  #define REG_LCDC_OVR1NEXT (*(__IO uint32_t*)0xF8038188U) /**< \brief (LCDC) Overlay 1 DMA Next Register */
  #define REG_LCDC_OVR1CFG0 (*(__IO uint32_t*)0xF803818CU) /**< \brief (LCDC) Overlay 1 Configuration Register 0 */
  #define REG_LCDC_OVR1CFG1 (*(__IO uint32_t*)0xF8038190U) /**< \brief (LCDC) Overlay 1 Configuration Register 1 */
  #define REG_LCDC_OVR1CFG2 (*(__IO uint32_t*)0xF8038194U) /**< \brief (LCDC) Overlay 1 Configuration Register 2 */
  #define REG_LCDC_OVR1CFG3 (*(__IO uint32_t*)0xF8038198U) /**< \brief (LCDC) Overlay 1 Configuration Register 3 */
  #define REG_LCDC_OVR1CFG4 (*(__IO uint32_t*)0xF803819CU) /**< \brief (LCDC) Overlay 1 Configuration Register 4 */
  #define REG_LCDC_OVR1CFG5 (*(__IO uint32_t*)0xF80381A0U) /**< \brief (LCDC) Overlay 1 Configuration Register 5 */
  #define REG_LCDC_OVR1CFG6 (*(__IO uint32_t*)0xF80381A4U) /**< \brief (LCDC) Overlay 1 Configuration Register 6 */
  #define REG_LCDC_OVR1CFG7 (*(__IO uint32_t*)0xF80381A8U) /**< \brief (LCDC) Overlay 1 Configuration Register 7 */
  #define REG_LCDC_OVR1CFG8 (*(__IO uint32_t*)0xF80381ACU) /**< \brief (LCDC) Overlay 1 Configuration Register 8 */
  #define REG_LCDC_OVR1CFG9 (*(__IO uint32_t*)0xF80381B0U) /**< \brief (LCDC) Overlay 1 Configuration Register 9 */
  #define REG_LCDC_OVR2CHER (*(__O  uint32_t*)0xF8038260U) /**< \brief (LCDC) Overlay 2 Channel Enable Register */
  #define REG_LCDC_OVR2CHDR (*(__O  uint32_t*)0xF8038264U) /**< \brief (LCDC) Overlay 2 Channel Disable Register */
  #define REG_LCDC_OVR2CHSR (*(__I  uint32_t*)0xF8038268U) /**< \brief (LCDC) Overlay 2 Channel Status Register */
  #define REG_LCDC_OVR2IER  (*(__O  uint32_t*)0xF803826CU) /**< \brief (LCDC) Overlay 2 Interrupt Enable Register */
  #define REG_LCDC_OVR2IDR  (*(__O  uint32_t*)0xF8038270U) /**< \brief (LCDC) Overlay 2 Interrupt Disable Register */
  #define REG_LCDC_OVR2IMR  (*(__I  uint32_t*)0xF8038274U) /**< \brief (LCDC) Overlay 2 Interrupt Mask Register */
  #define REG_LCDC_OVR2ISR  (*(__I  uint32_t*)0xF8038278U) /**< \brief (LCDC) Overlay 2 Interrupt Status Register */
  #define REG_LCDC_OVR2HEAD (*(__IO uint32_t*)0xF803827CU) /**< \brief (LCDC) Overlay 2 DMA Head Register */
  #define REG_LCDC_OVR2ADDR (*(__IO uint32_t*)0xF8038280U) /**< \brief (LCDC) Overlay 2 DMA Address Register */
  #define REG_LCDC_OVR2CTRL (*(__IO uint32_t*)0xF8038284U) /**< \brief (LCDC) Overlay 2 DMA Control Register */
  #define REG_LCDC_OVR2NEXT (*(__IO uint32_t*)0xF8038288U) /**< \brief (LCDC) Overlay 2 DMA Next Register */
  #define REG_LCDC_OVR2CFG0 (*(__IO uint32_t*)0xF803828CU) /**< \brief (LCDC) Overlay 2 Configuration Register 0 */
  #define REG_LCDC_OVR2CFG1 (*(__IO uint32_t*)0xF8038290U) /**< \brief (LCDC) Overlay 2 Configuration Register 1 */
  #define REG_LCDC_OVR2CFG2 (*(__IO uint32_t*)0xF8038294U) /**< \brief (LCDC) Overlay 2 Configuration Register 2 */
  #define REG_LCDC_OVR2CFG3 (*(__IO uint32_t*)0xF8038298U) /**< \brief (LCDC) Overlay 2 Configuration Register 3 */
  #define REG_LCDC_OVR2CFG4 (*(__IO uint32_t*)0xF803829CU) /**< \brief (LCDC) Overlay 2 Configuration Register 4 */
  #define REG_LCDC_OVR2CFG5 (*(__IO uint32_t*)0xF80382A0U) /**< \brief (LCDC) Overlay 2 Configuration Register 5 */
  #define REG_LCDC_OVR2CFG6 (*(__IO uint32_t*)0xF80382A4U) /**< \brief (LCDC) Overlay 2 Configuration Register 6 */
  #define REG_LCDC_OVR2CFG7 (*(__IO uint32_t*)0xF80382A8U) /**< \brief (LCDC) Overlay 2 Configuration Register 7 */
  #define REG_LCDC_OVR2CFG8 (*(__IO uint32_t*)0xF80382ACU) /**< \brief (LCDC) Overlay 2 Configuration Register 8 */
  #define REG_LCDC_OVR2CFG9 (*(__IO uint32_t*)0xF80382B0U) /**< \brief (LCDC) Overlay 2 Configuration Register 9 */
  #define REG_LCDC_HEOCHER  (*(__O  uint32_t*)0xF8038360U) /**< \brief (LCDC) High-End Overlay Channel Enable Register */
  #define REG_LCDC_HEOCHDR  (*(__O  uint32_t*)0xF8038364U) /**< \brief (LCDC) High-End Overlay Channel Disable Register */
  #define REG_LCDC_HEOCHSR  (*(__I  uint32_t*)0xF8038368U) /**< \brief (LCDC) High-End Overlay Channel Status Register */
  #define REG_LCDC_HEOIER   (*(__O  uint32_t*)0xF803836CU) /**< \brief (LCDC) High-End Overlay Interrupt Enable Register */
  #define REG_LCDC_HEOIDR   (*(__O  uint32_t*)0xF8038370U) /**< \brief (LCDC) High-End Overlay Interrupt Disable Register */
  #define REG_LCDC_HEOIMR   (*(__I  uint32_t*)0xF8038374U) /**< \brief (LCDC) High-End Overlay Interrupt Mask Register */
  #define REG_LCDC_HEOISR   (*(__I  uint32_t*)0xF8038378U) /**< \brief (LCDC) High-End Overlay Interrupt Status Register */
  #define REG_LCDC_HEOHEAD  (*(__IO uint32_t*)0xF803837CU) /**< \brief (LCDC) High-End Overlay DMA Head Register */
  #define REG_LCDC_HEOADDR  (*(__IO uint32_t*)0xF8038380U) /**< \brief (LCDC) High-End Overlay DMA Address Register */
  #define REG_LCDC_HEOCTRL  (*(__IO uint32_t*)0xF8038384U) /**< \brief (LCDC) High-End Overlay DMA Control Register */
  #define REG_LCDC_HEONEXT  (*(__IO uint32_t*)0xF8038388U) /**< \brief (LCDC) High-End Overlay DMA Next Register */
  #define REG_LCDC_HEOUHEAD (*(__IO uint32_t*)0xF803838CU) /**< \brief (LCDC) High-End Overlay U-UV DMA Head Register */
  #define REG_LCDC_HEOUADDR (*(__IO uint32_t*)0xF8038390U) /**< \brief (LCDC) High-End Overlay U-UV DMA Address Register */
  #define REG_LCDC_HEOUCTRL (*(__IO uint32_t*)0xF8038394U) /**< \brief (LCDC) High-End Overlay U-UV DMA Control Register */
  #define REG_LCDC_HEOUNEXT (*(__IO uint32_t*)0xF8038398U) /**< \brief (LCDC) High-End Overlay U-UV DMA Next Register */
  #define REG_LCDC_HEOVHEAD (*(__IO uint32_t*)0xF803839CU) /**< \brief (LCDC) High-End Overlay V DMA Head Register */
  #define REG_LCDC_HEOVADDR (*(__IO uint32_t*)0xF80383A0U) /**< \brief (LCDC) High-End Overlay V DMA Address Register */
  #define REG_LCDC_HEOVCTRL (*(__IO uint32_t*)0xF80383A4U) /**< \brief (LCDC) High-End Overlay V DMA Control Register */
  #define REG_LCDC_HEOVNEXT (*(__IO uint32_t*)0xF80383A8U) /**< \brief (LCDC) High-End Overlay V DMA Next Register */
  #define REG_LCDC_HEOCFG0  (*(__IO uint32_t*)0xF80383ACU) /**< \brief (LCDC) High-End Overlay Configuration Register 0 */
  #define REG_LCDC_HEOCFG1  (*(__IO uint32_t*)0xF80383B0U) /**< \brief (LCDC) High-End Overlay Configuration Register 1 */
  #define REG_LCDC_HEOCFG2  (*(__IO uint32_t*)0xF80383B4U) /**< \brief (LCDC) High-End Overlay Configuration Register 2 */
  #define REG_LCDC_HEOCFG3  (*(__IO uint32_t*)0xF80383B8U) /**< \brief (LCDC) High-End Overlay Configuration Register 3 */
  #define REG_LCDC_HEOCFG4  (*(__IO uint32_t*)0xF80383BCU) /**< \brief (LCDC) High-End Overlay Configuration Register 4 */
  #define REG_LCDC_HEOCFG5  (*(__IO uint32_t*)0xF80383C0U) /**< \brief (LCDC) High-End Overlay Configuration Register 5 */
  #define REG_LCDC_HEOCFG6  (*(__IO uint32_t*)0xF80383C4U) /**< \brief (LCDC) High-End Overlay Configuration Register 6 */
  #define REG_LCDC_HEOCFG7  (*(__IO uint32_t*)0xF80383C8U) /**< \brief (LCDC) High-End Overlay Configuration Register 7 */
  #define REG_LCDC_HEOCFG8  (*(__IO uint32_t*)0xF80383CCU) /**< \brief (LCDC) High-End Overlay Configuration Register 8 */
  #define REG_LCDC_HEOCFG9  (*(__IO uint32_t*)0xF80383D0U) /**< \brief (LCDC) High-End Overlay Configuration Register 9 */
  #define REG_LCDC_HEOCFG10 (*(__IO uint32_t*)0xF80383D4U) /**< \brief (LCDC) High-End Overlay Configuration Register 10 */
  #define REG_LCDC_HEOCFG11 (*(__IO uint32_t*)0xF80383D8U) /**< \brief (LCDC) High-End Overlay Configuration Register 11 */
  #define REG_LCDC_HEOCFG12 (*(__IO uint32_t*)0xF80383DCU) /**< \brief (LCDC) High-End Overlay Configuration Register 12 */
  #define REG_LCDC_HEOCFG13 (*(__IO uint32_t*)0xF80383E0U) /**< \brief (LCDC) High-End Overlay Configuration Register 13 */
  #define REG_LCDC_HEOCFG14 (*(__IO uint32_t*)0xF80383E4U) /**< \brief (LCDC) High-End Overlay Configuration Register 14 */
  #define REG_LCDC_HEOCFG15 (*(__IO uint32_t*)0xF80383E8U) /**< \brief (LCDC) High-End Overlay Configuration Register 15 */
  #define REG_LCDC_HEOCFG16 (*(__IO uint32_t*)0xF80383ECU) /**< \brief (LCDC) High-End Overlay Configuration Register 16 */
  #define REG_LCDC_HEOCFG17 (*(__IO uint32_t*)0xF80383F0U) /**< \brief (LCDC) High-End Overlay Configuration Register 17 */
  #define REG_LCDC_HEOCFG18 (*(__IO uint32_t*)0xF80383F4U) /**< \brief (LCDC) High-End Overlay Configuration Register 18 */
  #define REG_LCDC_HEOCFG19 (*(__IO uint32_t*)0xF80383F8U) /**< \brief (LCDC) High-End Overlay Configuration Register 19 */
  #define REG_LCDC_HEOCFG20 (*(__IO uint32_t*)0xF80383FCU) /**< \brief (LCDC) High-End Overlay Configuration Register 20 */
  #define REG_LCDC_HEOCFG21 (*(__IO uint32_t*)0xF8038400U) /**< \brief (LCDC) High-End Overlay Configuration Register 21 */
  #define REG_LCDC_HEOCFG22 (*(__IO uint32_t*)0xF8038404U) /**< \brief (LCDC) High-End Overlay Configuration Register 22 */
  #define REG_LCDC_HEOCFG23 (*(__IO uint32_t*)0xF8038408U) /**< \brief (LCDC) High-End Overlay Configuration Register 23 */
  #define REG_LCDC_HEOCFG24 (*(__IO uint32_t*)0xF803840CU) /**< \brief (LCDC) High-End Overlay Configuration Register 24 */
  #define REG_LCDC_HEOCFG25 (*(__IO uint32_t*)0xF8038410U) /**< \brief (LCDC) High-End Overlay Configuration Register 25 */
  #define REG_LCDC_HEOCFG26 (*(__IO uint32_t*)0xF8038414U) /**< \brief (LCDC) High-End Overlay Configuration Register 26 */
  #define REG_LCDC_HEOCFG27 (*(__IO uint32_t*)0xF8038418U) /**< \brief (LCDC) High-End Overlay Configuration Register 27 */
  #define REG_LCDC_HEOCFG28 (*(__IO uint32_t*)0xF803841CU) /**< \brief (LCDC) High-End Overlay Configuration Register 28 */
  #define REG_LCDC_HEOCFG29 (*(__IO uint32_t*)0xF8038420U) /**< \brief (LCDC) High-End Overlay Configuration Register 29 */
  #define REG_LCDC_HEOCFG30 (*(__IO uint32_t*)0xF8038424U) /**< \brief (LCDC) High-End Overlay Configuration Register 30 */
  #define REG_LCDC_HEOCFG31 (*(__IO uint32_t*)0xF8038428U) /**< \brief (LCDC) High-End Overlay Configuration Register 31 */
  #define REG_LCDC_HEOCFG32 (*(__IO uint32_t*)0xF803842CU) /**< \brief (LCDC) High-End Overlay Configuration Register 32 */
  #define REG_LCDC_HEOCFG33 (*(__IO uint32_t*)0xF8038430U) /**< \brief (LCDC) High-End Overlay Configuration Register 33 */
  #define REG_LCDC_HEOCFG34 (*(__IO uint32_t*)0xF8038434U) /**< \brief (LCDC) High-End Overlay Configuration Register 34 */
  #define REG_LCDC_HEOCFG35 (*(__IO uint32_t*)0xF8038438U) /**< \brief (LCDC) High-End Overlay Configuration Register 35 */
  #define REG_LCDC_HEOCFG36 (*(__IO uint32_t*)0xF803843CU) /**< \brief (LCDC) High-End Overlay Configuration Register 36 */
  #define REG_LCDC_HEOCFG37 (*(__IO uint32_t*)0xF8038440U) /**< \brief (LCDC) High-End Overlay Configuration Register 37 */
  #define REG_LCDC_HEOCFG38 (*(__IO uint32_t*)0xF8038444U) /**< \brief (LCDC) High-End Overlay Configuration Register 38 */
  #define REG_LCDC_HEOCFG39 (*(__IO uint32_t*)0xF8038448U) /**< \brief (LCDC) High-End Overlay Configuration Register 39 */
  #define REG_LCDC_HEOCFG40 (*(__IO uint32_t*)0xF803844CU) /**< \brief (LCDC) High-End Overlay Configuration Register 40 */
  #define REG_LCDC_HEOCFG41 (*(__IO uint32_t*)0xF8038450U) /**< \brief (LCDC) High-End Overlay Configuration Register 41 */
  #define REG_LCDC_BASECLUT (*(__IO uint32_t*)0xF8038600U) /**< \brief (LCDC) Base CLUT Register */
  #define REG_LCDC_OVR1CLUT (*(__IO uint32_t*)0xF8038A00U) /**< \brief (LCDC) Overlay 1 CLUT Register */
  #define REG_LCDC_OVR2CLUT (*(__IO uint32_t*)0xF8038E00U) /**< \brief (LCDC) Overlay 2 CLUT Register */
  #define REG_LCDC_HEOCLUT  (*(__IO uint32_t*)0xF8039200U) /**< \brief (LCDC) High-End Overlay CLUT Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_LCDC_INSTANCE_ */
