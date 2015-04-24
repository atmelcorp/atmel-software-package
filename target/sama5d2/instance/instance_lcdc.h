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

#ifndef _SAMA5D2_LCDC_INSTANCE_
#define _SAMA5D2_LCDC_INSTANCE_

/* ========== Register definition for LCDC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_LCDC_LCDCFG0                   (0xF0000000U) /**< \brief (LCDC) LCD Controller Configuration Register 0 */
  #define REG_LCDC_LCDCFG1                   (0xF0000004U) /**< \brief (LCDC) LCD Controller Configuration Register 1 */
  #define REG_LCDC_LCDCFG2                   (0xF0000008U) /**< \brief (LCDC) LCD Controller Configuration Register 2 */
  #define REG_LCDC_LCDCFG3                   (0xF000000CU) /**< \brief (LCDC) LCD Controller Configuration Register 3 */
  #define REG_LCDC_LCDCFG4                   (0xF0000010U) /**< \brief (LCDC) LCD Controller Configuration Register 4 */
  #define REG_LCDC_LCDCFG5                   (0xF0000014U) /**< \brief (LCDC) LCD Controller Configuration Register 5 */
  #define REG_LCDC_LCDCFG6                   (0xF0000018U) /**< \brief (LCDC) LCD Controller Configuration Register 6 */
  #define REG_LCDC_LCDEN                     (0xF0000020U) /**< \brief (LCDC) LCD Controller Enable Register */
  #define REG_LCDC_LCDDIS                    (0xF0000024U) /**< \brief (LCDC) LCD Controller Disable Register */
  #define REG_LCDC_LCDSR                     (0xF0000028U) /**< \brief (LCDC) LCD Controller Status Register */
  #define REG_LCDC_LCDIER                    (0xF000002CU) /**< \brief (LCDC) LCD Controller Interrupt Enable Register */
  #define REG_LCDC_LCDIDR                    (0xF0000030U) /**< \brief (LCDC) LCD Controller Interrupt Disable Register */
  #define REG_LCDC_LCDIMR                    (0xF0000034U) /**< \brief (LCDC) LCD Controller Interrupt Mask Register */
  #define REG_LCDC_LCDISR                    (0xF0000038U) /**< \brief (LCDC) LCD Controller Interrupt Status Register */
  #define REG_LCDC_ATTR                      (0xF000003CU) /**< \brief (LCDC) LCD Controller Attribute Register */
  #define REG_LCDC_BASECHER                  (0xF0000040U) /**< \brief (LCDC) Base Layer Channel Enable Register */
  #define REG_LCDC_BASECHDR                  (0xF0000044U) /**< \brief (LCDC) Base Layer Channel Disable Register */
  #define REG_LCDC_BASECHSR                  (0xF0000048U) /**< \brief (LCDC) Base Layer Channel Status Register */
  #define REG_LCDC_BASEIER                   (0xF000004CU) /**< \brief (LCDC) Base Layer Interrupt Enable Register */
  #define REG_LCDC_BASEIDR                   (0xF0000050U) /**< \brief (LCDC) Base Layer Interrupt Disabled Register */
  #define REG_LCDC_BASEIMR                   (0xF0000054U) /**< \brief (LCDC) Base Layer Interrupt Mask Register */
  #define REG_LCDC_BASEISR                   (0xF0000058U) /**< \brief (LCDC) Base Layer Interrupt Status Register */
  #define REG_LCDC_BASEHEAD                  (0xF000005CU) /**< \brief (LCDC) Base DMA Head Register */
  #define REG_LCDC_BASEADDR                  (0xF0000060U) /**< \brief (LCDC) Base DMA Address Register */
  #define REG_LCDC_BASECTRL                  (0xF0000064U) /**< \brief (LCDC) Base DMA Control Register */
  #define REG_LCDC_BASENEXT                  (0xF0000068U) /**< \brief (LCDC) Base DMA Next Register */
  #define REG_LCDC_BASECFG0                  (0xF000006CU) /**< \brief (LCDC) Base Layer Configuration Register 0 */
  #define REG_LCDC_BASECFG1                  (0xF0000070U) /**< \brief (LCDC) Base Layer Configuration Register 1 */
  #define REG_LCDC_BASECFG2                  (0xF0000074U) /**< \brief (LCDC) Base Layer Configuration Register 2 */
  #define REG_LCDC_BASECFG3                  (0xF0000078U) /**< \brief (LCDC) Base Layer Configuration Register 3 */
  #define REG_LCDC_BASECFG4                  (0xF000007CU) /**< \brief (LCDC) Base Layer Configuration Register 4 */
  #define REG_LCDC_BASECFG5                  (0xF0000080U) /**< \brief (LCDC) Base Layer Configuration Register 5 */
  #define REG_LCDC_BASECFG6                  (0xF0000084U) /**< \brief (LCDC) Base Layer Configuration Register 6 */
  #define REG_LCDC_OVR1CHER                  (0xF0000140U) /**< \brief (LCDC) Overlay 1 Channel Enable Register */
  #define REG_LCDC_OVR1CHDR                  (0xF0000144U) /**< \brief (LCDC) Overlay 1 Channel Disable Register */
  #define REG_LCDC_OVR1CHSR                  (0xF0000148U) /**< \brief (LCDC) Overlay 1 Channel Status Register */
  #define REG_LCDC_OVR1IER                   (0xF000014CU) /**< \brief (LCDC) Overlay 1 Interrupt Enable Register */
  #define REG_LCDC_OVR1IDR                   (0xF0000150U) /**< \brief (LCDC) Overlay 1 Interrupt Disable Register */
  #define REG_LCDC_OVR1IMR                   (0xF0000154U) /**< \brief (LCDC) Overlay 1 Interrupt Mask Register */
  #define REG_LCDC_OVR1ISR                   (0xF0000158U) /**< \brief (LCDC) Overlay 1 Interrupt Status Register */
  #define REG_LCDC_OVR1HEAD                  (0xF000015CU) /**< \brief (LCDC) Overlay 1 DMA Head Register */
  #define REG_LCDC_OVR1ADDR                  (0xF0000160U) /**< \brief (LCDC) Overlay 1 DMA Address Register */
  #define REG_LCDC_OVR1CTRL                  (0xF0000164U) /**< \brief (LCDC) Overlay 1 DMA Control Register */
  #define REG_LCDC_OVR1NEXT                  (0xF0000168U) /**< \brief (LCDC) Overlay 1 DMA Next Register */
  #define REG_LCDC_OVR1CFG0                  (0xF000016CU) /**< \brief (LCDC) Overlay 1 Configuration Register 0 */
  #define REG_LCDC_OVR1CFG1                  (0xF0000170U) /**< \brief (LCDC) Overlay 1 Configuration Register 1 */
  #define REG_LCDC_OVR1CFG2                  (0xF0000174U) /**< \brief (LCDC) Overlay 1 Configuration Register 2 */
  #define REG_LCDC_OVR1CFG3                  (0xF0000178U) /**< \brief (LCDC) Overlay 1 Configuration Register 3 */
  #define REG_LCDC_OVR1CFG4                  (0xF000017CU) /**< \brief (LCDC) Overlay 1 Configuration Register 4 */
  #define REG_LCDC_OVR1CFG5                  (0xF0000180U) /**< \brief (LCDC) Overlay 1 Configuration Register 5 */
  #define REG_LCDC_OVR1CFG6                  (0xF0000184U) /**< \brief (LCDC) Overlay 1 Configuration Register 6 */
  #define REG_LCDC_OVR1CFG7                  (0xF0000188U) /**< \brief (LCDC) Overlay 1 Configuration Register 7 */
  #define REG_LCDC_OVR1CFG8                  (0xF000018CU) /**< \brief (LCDC) Overlay 1 Configuration Register 8 */
  #define REG_LCDC_OVR1CFG9                  (0xF0000190U) /**< \brief (LCDC) Overlay 1 Configuration Register 9 */
  #define REG_LCDC_OVR2CHER                  (0xF0000240U) /**< \brief (LCDC) Overlay 2 Channel Enable Register */
  #define REG_LCDC_OVR2CHDR                  (0xF0000244U) /**< \brief (LCDC) Overlay 2 Channel Disable Register */
  #define REG_LCDC_OVR2CHSR                  (0xF0000248U) /**< \brief (LCDC) Overlay 2 Channel Status Register */
  #define REG_LCDC_OVR2IER                   (0xF000024CU) /**< \brief (LCDC) Overlay 2 Interrupt Enable Register */
  #define REG_LCDC_OVR2IDR                   (0xF0000250U) /**< \brief (LCDC) Overlay 2 Interrupt Disable Register */
  #define REG_LCDC_OVR2IMR                   (0xF0000254U) /**< \brief (LCDC) Overlay 2 Interrupt Mask Register */
  #define REG_LCDC_OVR2ISR                   (0xF0000258U) /**< \brief (LCDC) Overlay 2 Interrupt Status Register */
  #define REG_LCDC_OVR2HEAD                  (0xF000025CU) /**< \brief (LCDC) Overlay 2 DMA Head Register */
  #define REG_LCDC_OVR2ADDR                  (0xF0000260U) /**< \brief (LCDC) Overlay 2 DMA Address Register */
  #define REG_LCDC_OVR2CTRL                  (0xF0000264U) /**< \brief (LCDC) Overlay 2 DMA Control Register */
  #define REG_LCDC_OVR2NEXT                  (0xF0000268U) /**< \brief (LCDC) Overlay 2 DMA Next Register */
  #define REG_LCDC_OVR2CFG0                  (0xF000026CU) /**< \brief (LCDC) Overlay 2 Configuration Register 0 */
  #define REG_LCDC_OVR2CFG1                  (0xF0000270U) /**< \brief (LCDC) Overlay 2 Configuration Register 1 */
  #define REG_LCDC_OVR2CFG2                  (0xF0000274U) /**< \brief (LCDC) Overlay 2 Configuration Register 2 */
  #define REG_LCDC_OVR2CFG3                  (0xF0000278U) /**< \brief (LCDC) Overlay 2 Configuration Register 3 */
  #define REG_LCDC_OVR2CFG4                  (0xF000027CU) /**< \brief (LCDC) Overlay 2 Configuration Register 4 */
  #define REG_LCDC_OVR2CFG5                  (0xF0000280U) /**< \brief (LCDC) Overlay 2 Configuration Register 5 */
  #define REG_LCDC_OVR2CFG6                  (0xF0000284U) /**< \brief (LCDC) Overlay 2 Configuration Register 6 */
  #define REG_LCDC_OVR2CFG7                  (0xF0000288U) /**< \brief (LCDC) Overlay 2 Configuration Register 7 */
  #define REG_LCDC_OVR2CFG8                  (0xF000028CU) /**< \brief (LCDC) Overlay 2 Configuration Register 8 */
  #define REG_LCDC_OVR2CFG9                  (0xF0000290U) /**< \brief (LCDC) Overlay 2 Configuration Register 8 */
  #define REG_LCDC_HEOCHER                   (0xF0000340U) /**< \brief (LCDC) High End Overlay Channel Enable Register */
  #define REG_LCDC_HEOCHDR                   (0xF0000344U) /**< \brief (LCDC) High End Overlay Channel Disable Register */
  #define REG_LCDC_HEOCHSR                   (0xF0000348U) /**< \brief (LCDC) High End Overlay Channel Status Register */
  #define REG_LCDC_HEOIER                    (0xF000034CU) /**< \brief (LCDC) High End Overlay Interrupt Enable Register */
  #define REG_LCDC_HEOIDR                    (0xF0000350U) /**< \brief (LCDC) High End Overlay Interrupt Disable Register */
  #define REG_LCDC_HEOIMR                    (0xF0000354U) /**< \brief (LCDC) High End Overlay Interrupt Mask Register */
  #define REG_LCDC_HEOISR                    (0xF0000358U) /**< \brief (LCDC) High End Overlay Interrupt Status Register */
  #define REG_LCDC_HEOHEAD                   (0xF000035CU) /**< \brief (LCDC) High End Overlay DMA Head Register */
  #define REG_LCDC_HEOADDR                   (0xF0000360U) /**< \brief (LCDC) High End Overlay DMA Address Register */
  #define REG_LCDC_HEOCTRL                   (0xF0000364U) /**< \brief (LCDC) High End Overlay DMA Control Register */
  #define REG_LCDC_HEONEXT                   (0xF0000368U) /**< \brief (LCDC) High End Overlay DMA Next Register */
  #define REG_LCDC_HEOUHEAD                  (0xF000036CU) /**< \brief (LCDC) High End Overlay U-UV DMA Head Register */
  #define REG_LCDC_HEOUADDR                  (0xF0000370U) /**< \brief (LCDC) High End Overlay U-UV DMA Address Register */
  #define REG_LCDC_HEOUCTRL                  (0xF0000374U) /**< \brief (LCDC) High End Overlay U-UV DMA Control Register */
  #define REG_LCDC_HEOUNEXT                  (0xF0000378U) /**< \brief (LCDC) High End Overlay U-UV DMA Next Register */
  #define REG_LCDC_HEOVHEAD                  (0xF000037CU) /**< \brief (LCDC) High End Overlay V DMA Head Register */
  #define REG_LCDC_HEOVADDR                  (0xF0000380U) /**< \brief (LCDC) High End Overlay V DMA Address Register */
  #define REG_LCDC_HEOVCTRL                  (0xF0000384U) /**< \brief (LCDC) High End Overlay V DMA Control Register */
  #define REG_LCDC_HEOVNEXT                  (0xF0000388U) /**< \brief (LCDC) High End Overlay V DMA Next Register */
  #define REG_LCDC_HEOCFG0                   (0xF000038CU) /**< \brief (LCDC) High End Overlay Configuration Register 0 */
  #define REG_LCDC_HEOCFG1                   (0xF0000390U) /**< \brief (LCDC) High End Overlay Configuration Register 1 */
  #define REG_LCDC_HEOCFG2                   (0xF0000394U) /**< \brief (LCDC) High End Overlay Configuration Register 2 */
  #define REG_LCDC_HEOCFG3                   (0xF0000398U) /**< \brief (LCDC) High End Overlay Configuration Register 3 */
  #define REG_LCDC_HEOCFG4                   (0xF000039CU) /**< \brief (LCDC) High End Overlay Configuration Register 4 */
  #define REG_LCDC_HEOCFG5                   (0xF00003A0U) /**< \brief (LCDC) High End Overlay Configuration Register 5 */
  #define REG_LCDC_HEOCFG6                   (0xF00003A4U) /**< \brief (LCDC) High End Overlay Configuration Register 6 */
  #define REG_LCDC_HEOCFG7                   (0xF00003A8U) /**< \brief (LCDC) High End Overlay Configuration Register 7 */
  #define REG_LCDC_HEOCFG8                   (0xF00003ACU) /**< \brief (LCDC) High End Overlay Configuration Register 8 */
  #define REG_LCDC_HEOCFG9                   (0xF00003B0U) /**< \brief (LCDC) High End Overlay Configuration Register 9 */
  #define REG_LCDC_HEOCFG10                  (0xF00003B4U) /**< \brief (LCDC) High End Overlay Configuration Register 10 */
  #define REG_LCDC_HEOCFG11                  (0xF00003B8U) /**< \brief (LCDC) High End Overlay Configuration Register 11 */
  #define REG_LCDC_HEOCFG12                  (0xF00003BCU) /**< \brief (LCDC) High End Overlay Configuration Register 12 */
  #define REG_LCDC_HEOCFG13                  (0xF00003C0U) /**< \brief (LCDC) High End Overlay Configuration Register 13 */
  #define REG_LCDC_HEOCFG14                  (0xF00003C4U) /**< \brief (LCDC) High End Overlay Configuration Register 14 */
  #define REG_LCDC_HEOCFG15                  (0xF00003C8U) /**< \brief (LCDC) High End Overlay Configuration Register 15 */
  #define REG_LCDC_HEOCFG16                  (0xF00003CCU) /**< \brief (LCDC) High End Overlay Configuration Register 16 */
  #define REG_LCDC_HEOCFG17                  (0xF00003D0U) /**< \brief (LCDC) High End Overlay Configuration Register 17 */
  #define REG_LCDC_HEOCFG18                  (0xF00003D4U) /**< \brief (LCDC) High End Overlay Configuration Register 18 */
  #define REG_LCDC_HEOCFG19                  (0xF00003D8U) /**< \brief (LCDC) High End Overlay Configuration Register 19 */
  #define REG_LCDC_HEOCFG20                  (0xF00003DCU) /**< \brief (LCDC) High End Overlay Configuration Register 20 */
  #define REG_LCDC_HEOCFG21                  (0xF00003E0U) /**< \brief (LCDC) High End Overlay Configuration Register 21 */
  #define REG_LCDC_HEOCFG22                  (0xF00003E4U) /**< \brief (LCDC) High End Overlay Configuration Register 22 */
  #define REG_LCDC_HEOCFG23                  (0xF00003E8U) /**< \brief (LCDC) High End Overlay Configuration Register 23 */
  #define REG_LCDC_HEOCFG24                  (0xF00003ECU) /**< \brief (LCDC) High End Overlay Configuration Register 24 */
  #define REG_LCDC_HEOCFG25                  (0xF00003F0U) /**< \brief (LCDC) High End Overlay Configuration Register 25 */
  #define REG_LCDC_HEOCFG26                  (0xF00003F4U) /**< \brief (LCDC) High End Overlay Configuration Register 26 */
  #define REG_LCDC_HEOCFG27                  (0xF00003F8U) /**< \brief (LCDC) High End Overlay Configuration Register 27 */
  #define REG_LCDC_HEOCFG28                  (0xF00003FCU) /**< \brief (LCDC) High End Overlay Configuration Register 28 */
  #define REG_LCDC_HEOCFG29                  (0xF0000400U) /**< \brief (LCDC) High End Overlay Configuration Register 29 */
  #define REG_LCDC_HEOCFG30                  (0xF0000404U) /**< \brief (LCDC) High End Overlay Configuration Register 30 */
  #define REG_LCDC_HEOCFG31                  (0xF0000408U) /**< \brief (LCDC) High End Overlay Configuration Register 31 */
  #define REG_LCDC_HEOCFG32                  (0xF000040CU) /**< \brief (LCDC) High End Overlay Configuration Register 32 */
  #define REG_LCDC_HEOCFG33                  (0xF0000410U) /**< \brief (LCDC) High End Overlay Configuration Register 33 */
  #define REG_LCDC_HEOCFG34                  (0xF0000414U) /**< \brief (LCDC) High End Overlay Configuration Register 34 */
  #define REG_LCDC_HEOCFG35                  (0xF0000418U) /**< \brief (LCDC) High End Overlay Configuration Register 35 */
  #define REG_LCDC_HEOCFG36                  (0xF000041CU) /**< \brief (LCDC) High End Overlay Configuration Register 36 */
  #define REG_LCDC_HEOCFG37                  (0xF0000420U) /**< \brief (LCDC) High End Overlay Configuration Register 37 */
  #define REG_LCDC_HEOCFG38                  (0xF0000424U) /**< \brief (LCDC) High End Overlay Configuration Register 38 */
  #define REG_LCDC_HEOCFG39                  (0xF0000428U) /**< \brief (LCDC) High End Overlay Configuration Register 39 */
  #define REG_LCDC_HEOCFG40                  (0xF000042CU) /**< \brief (LCDC) High End Overlay Configuration Register 40 */
  #define REG_LCDC_HEOCFG41                  (0xF0000430U) /**< \brief (LCDC) High End Overlay Configuration Register 41 */
  #define REG_LCDC_PPCHER                    (0xF0000540U) /**< \brief (LCDC) Post Processing Channel Enable Register */
  #define REG_LCDC_PPCHDR                    (0xF0000544U) /**< \brief (LCDC) Post Processing Channel Disable Register */
  #define REG_LCDC_PPCHSR                    (0xF0000548U) /**< \brief (LCDC) Post Processing Channel Status Register */
  #define REG_LCDC_PPIER                     (0xF000054CU) /**< \brief (LCDC) Post Processing Interrupt Enable Register */
  #define REG_LCDC_PPIDR                     (0xF0000550U) /**< \brief (LCDC) Post Processing Interrupt Disable Register */
  #define REG_LCDC_PPIMR                     (0xF0000554U) /**< \brief (LCDC) Post Processing Interrupt Mask Register */
  #define REG_LCDC_PPISR                     (0xF0000558U) /**< \brief (LCDC) Post Processing Interrupt Status Register */
  #define REG_LCDC_PPHEAD                    (0xF000055CU) /**< \brief (LCDC) Post Processing Head Register */
  #define REG_LCDC_PPADDR                    (0xF0000560U) /**< \brief (LCDC) Post Processing Address Register */
  #define REG_LCDC_PPCTRL                    (0xF0000564U) /**< \brief (LCDC) Post Processing Control Register */
  #define REG_LCDC_PPNEXT                    (0xF0000568U) /**< \brief (LCDC) Post Processing Next Register */
  #define REG_LCDC_PPCFG0                    (0xF000056CU) /**< \brief (LCDC) Post Processing Configuration Register 0 */
  #define REG_LCDC_PPCFG1                    (0xF0000570U) /**< \brief (LCDC) Post Processing Configuration Register 1 */
  #define REG_LCDC_PPCFG2                    (0xF0000574U) /**< \brief (LCDC) Post Processing Configuration Register 2 */
  #define REG_LCDC_PPCFG3                    (0xF0000578U) /**< \brief (LCDC) Post Processing Configuration Register 3 */
  #define REG_LCDC_PPCFG4                    (0xF000057CU) /**< \brief (LCDC) Post Processing Configuration Register 4 */
  #define REG_LCDC_PPCFG5                    (0xF0000580U) /**< \brief (LCDC) Post Processing Configuration Register 5 */
  #define REG_LCDC_BASECLUT                  (0xF0000600U) /**< \brief (LCDC) Base CLUT Register */
  #define REG_LCDC_OVR1CLUT                  (0xF0000A00U) /**< \brief (LCDC) Overlay 1 CLUT Register */
  #define REG_LCDC_OVR2CLUT                  (0xF0000E00U) /**< \brief (LCDC) Overlay 2 CLUT Register */
  #define REG_LCDC_HEOCLUT                   (0xF0001200U) /**< \brief (LCDC) High End Overlay CLUT Register */
  #define REG_LCDC_ADDRSIZE                  (0xF0001FECU) /**< \brief (LCDC) Address Size Register */
  #define REG_LCDC_IPNAME                    (0xF0001FF0U) /**< \brief (LCDC) IP Name1 Register */
  #define REG_LCDC_FEATURES                  (0xF0001FF8U) /**< \brief (LCDC) Features Register */
  #define REG_LCDC_VERSION                   (0xF0001FFCU) /**< \brief (LCDC) Version Register */
#else
  #define REG_LCDC_LCDCFG0  (*(__IO uint32_t*)0xF0000000U) /**< \brief (LCDC) LCD Controller Configuration Register 0 */
  #define REG_LCDC_LCDCFG1  (*(__IO uint32_t*)0xF0000004U) /**< \brief (LCDC) LCD Controller Configuration Register 1 */
  #define REG_LCDC_LCDCFG2  (*(__IO uint32_t*)0xF0000008U) /**< \brief (LCDC) LCD Controller Configuration Register 2 */
  #define REG_LCDC_LCDCFG3  (*(__IO uint32_t*)0xF000000CU) /**< \brief (LCDC) LCD Controller Configuration Register 3 */
  #define REG_LCDC_LCDCFG4  (*(__IO uint32_t*)0xF0000010U) /**< \brief (LCDC) LCD Controller Configuration Register 4 */
  #define REG_LCDC_LCDCFG5  (*(__IO uint32_t*)0xF0000014U) /**< \brief (LCDC) LCD Controller Configuration Register 5 */
  #define REG_LCDC_LCDCFG6  (*(__IO uint32_t*)0xF0000018U) /**< \brief (LCDC) LCD Controller Configuration Register 6 */
  #define REG_LCDC_LCDEN    (*(__O  uint32_t*)0xF0000020U) /**< \brief (LCDC) LCD Controller Enable Register */
  #define REG_LCDC_LCDDIS   (*(__O  uint32_t*)0xF0000024U) /**< \brief (LCDC) LCD Controller Disable Register */
  #define REG_LCDC_LCDSR    (*(__I  uint32_t*)0xF0000028U) /**< \brief (LCDC) LCD Controller Status Register */
  #define REG_LCDC_LCDIER   (*(__O  uint32_t*)0xF000002CU) /**< \brief (LCDC) LCD Controller Interrupt Enable Register */
  #define REG_LCDC_LCDIDR   (*(__O  uint32_t*)0xF0000030U) /**< \brief (LCDC) LCD Controller Interrupt Disable Register */
  #define REG_LCDC_LCDIMR   (*(__I  uint32_t*)0xF0000034U) /**< \brief (LCDC) LCD Controller Interrupt Mask Register */
  #define REG_LCDC_LCDISR   (*(__I  uint32_t*)0xF0000038U) /**< \brief (LCDC) LCD Controller Interrupt Status Register */
  #define REG_LCDC_ATTR     (*(__O  uint32_t*)0xF000003CU) /**< \brief (LCDC) LCD Controller Attribute Register */
  #define REG_LCDC_BASECHER (*(__O  uint32_t*)0xF0000040U) /**< \brief (LCDC) Base Layer Channel Enable Register */
  #define REG_LCDC_BASECHDR (*(__O  uint32_t*)0xF0000044U) /**< \brief (LCDC) Base Layer Channel Disable Register */
  #define REG_LCDC_BASECHSR (*(__I  uint32_t*)0xF0000048U) /**< \brief (LCDC) Base Layer Channel Status Register */
  #define REG_LCDC_BASEIER  (*(__O  uint32_t*)0xF000004CU) /**< \brief (LCDC) Base Layer Interrupt Enable Register */
  #define REG_LCDC_BASEIDR  (*(__O  uint32_t*)0xF0000050U) /**< \brief (LCDC) Base Layer Interrupt Disabled Register */
  #define REG_LCDC_BASEIMR  (*(__I  uint32_t*)0xF0000054U) /**< \brief (LCDC) Base Layer Interrupt Mask Register */
  #define REG_LCDC_BASEISR  (*(__I  uint32_t*)0xF0000058U) /**< \brief (LCDC) Base Layer Interrupt Status Register */
  #define REG_LCDC_BASEHEAD (*(__IO uint32_t*)0xF000005CU) /**< \brief (LCDC) Base DMA Head Register */
  #define REG_LCDC_BASEADDR (*(__IO uint32_t*)0xF0000060U) /**< \brief (LCDC) Base DMA Address Register */
  #define REG_LCDC_BASECTRL (*(__IO uint32_t*)0xF0000064U) /**< \brief (LCDC) Base DMA Control Register */
  #define REG_LCDC_BASENEXT (*(__IO uint32_t*)0xF0000068U) /**< \brief (LCDC) Base DMA Next Register */
  #define REG_LCDC_BASECFG0 (*(__IO uint32_t*)0xF000006CU) /**< \brief (LCDC) Base Layer Configuration Register 0 */
  #define REG_LCDC_BASECFG1 (*(__IO uint32_t*)0xF0000070U) /**< \brief (LCDC) Base Layer Configuration Register 1 */
  #define REG_LCDC_BASECFG2 (*(__IO uint32_t*)0xF0000074U) /**< \brief (LCDC) Base Layer Configuration Register 2 */
  #define REG_LCDC_BASECFG3 (*(__IO uint32_t*)0xF0000078U) /**< \brief (LCDC) Base Layer Configuration Register 3 */
  #define REG_LCDC_BASECFG4 (*(__IO uint32_t*)0xF000007CU) /**< \brief (LCDC) Base Layer Configuration Register 4 */
  #define REG_LCDC_BASECFG5 (*(__IO uint32_t*)0xF0000080U) /**< \brief (LCDC) Base Layer Configuration Register 5 */
  #define REG_LCDC_BASECFG6 (*(__IO uint32_t*)0xF0000084U) /**< \brief (LCDC) Base Layer Configuration Register 6 */
  #define REG_LCDC_OVR1CHER (*(__O  uint32_t*)0xF0000140U) /**< \brief (LCDC) Overlay 1 Channel Enable Register */
  #define REG_LCDC_OVR1CHDR (*(__O  uint32_t*)0xF0000144U) /**< \brief (LCDC) Overlay 1 Channel Disable Register */
  #define REG_LCDC_OVR1CHSR (*(__I  uint32_t*)0xF0000148U) /**< \brief (LCDC) Overlay 1 Channel Status Register */
  #define REG_LCDC_OVR1IER  (*(__O  uint32_t*)0xF000014CU) /**< \brief (LCDC) Overlay 1 Interrupt Enable Register */
  #define REG_LCDC_OVR1IDR  (*(__O  uint32_t*)0xF0000150U) /**< \brief (LCDC) Overlay 1 Interrupt Disable Register */
  #define REG_LCDC_OVR1IMR  (*(__I  uint32_t*)0xF0000154U) /**< \brief (LCDC) Overlay 1 Interrupt Mask Register */
  #define REG_LCDC_OVR1ISR  (*(__I  uint32_t*)0xF0000158U) /**< \brief (LCDC) Overlay 1 Interrupt Status Register */
  #define REG_LCDC_OVR1HEAD (*(__IO uint32_t*)0xF000015CU) /**< \brief (LCDC) Overlay 1 DMA Head Register */
  #define REG_LCDC_OVR1ADDR (*(__IO uint32_t*)0xF0000160U) /**< \brief (LCDC) Overlay 1 DMA Address Register */
  #define REG_LCDC_OVR1CTRL (*(__IO uint32_t*)0xF0000164U) /**< \brief (LCDC) Overlay 1 DMA Control Register */
  #define REG_LCDC_OVR1NEXT (*(__IO uint32_t*)0xF0000168U) /**< \brief (LCDC) Overlay 1 DMA Next Register */
  #define REG_LCDC_OVR1CFG0 (*(__IO uint32_t*)0xF000016CU) /**< \brief (LCDC) Overlay 1 Configuration Register 0 */
  #define REG_LCDC_OVR1CFG1 (*(__IO uint32_t*)0xF0000170U) /**< \brief (LCDC) Overlay 1 Configuration Register 1 */
  #define REG_LCDC_OVR1CFG2 (*(__IO uint32_t*)0xF0000174U) /**< \brief (LCDC) Overlay 1 Configuration Register 2 */
  #define REG_LCDC_OVR1CFG3 (*(__IO uint32_t*)0xF0000178U) /**< \brief (LCDC) Overlay 1 Configuration Register 3 */
  #define REG_LCDC_OVR1CFG4 (*(__IO uint32_t*)0xF000017CU) /**< \brief (LCDC) Overlay 1 Configuration Register 4 */
  #define REG_LCDC_OVR1CFG5 (*(__IO uint32_t*)0xF0000180U) /**< \brief (LCDC) Overlay 1 Configuration Register 5 */
  #define REG_LCDC_OVR1CFG6 (*(__IO uint32_t*)0xF0000184U) /**< \brief (LCDC) Overlay 1 Configuration Register 6 */
  #define REG_LCDC_OVR1CFG7 (*(__IO uint32_t*)0xF0000188U) /**< \brief (LCDC) Overlay 1 Configuration Register 7 */
  #define REG_LCDC_OVR1CFG8 (*(__IO uint32_t*)0xF000018CU) /**< \brief (LCDC) Overlay 1 Configuration Register 8 */
  #define REG_LCDC_OVR1CFG9 (*(__IO uint32_t*)0xF0000190U) /**< \brief (LCDC) Overlay 1 Configuration Register 9 */
  #define REG_LCDC_OVR2CHER (*(__O  uint32_t*)0xF0000240U) /**< \brief (LCDC) Overlay 2 Channel Enable Register */
  #define REG_LCDC_OVR2CHDR (*(__O  uint32_t*)0xF0000244U) /**< \brief (LCDC) Overlay 2 Channel Disable Register */
  #define REG_LCDC_OVR2CHSR (*(__I  uint32_t*)0xF0000248U) /**< \brief (LCDC) Overlay 2 Channel Status Register */
  #define REG_LCDC_OVR2IER  (*(__O  uint32_t*)0xF000024CU) /**< \brief (LCDC) Overlay 2 Interrupt Enable Register */
  #define REG_LCDC_OVR2IDR  (*(__O  uint32_t*)0xF0000250U) /**< \brief (LCDC) Overlay 2 Interrupt Disable Register */
  #define REG_LCDC_OVR2IMR  (*(__I  uint32_t*)0xF0000254U) /**< \brief (LCDC) Overlay 2 Interrupt Mask Register */
  #define REG_LCDC_OVR2ISR  (*(__I  uint32_t*)0xF0000258U) /**< \brief (LCDC) Overlay 2 Interrupt Status Register */
  #define REG_LCDC_OVR2HEAD (*(__IO uint32_t*)0xF000025CU) /**< \brief (LCDC) Overlay 2 DMA Head Register */
  #define REG_LCDC_OVR2ADDR (*(__IO uint32_t*)0xF0000260U) /**< \brief (LCDC) Overlay 2 DMA Address Register */
  #define REG_LCDC_OVR2CTRL (*(__IO uint32_t*)0xF0000264U) /**< \brief (LCDC) Overlay 2 DMA Control Register */
  #define REG_LCDC_OVR2NEXT (*(__IO uint32_t*)0xF0000268U) /**< \brief (LCDC) Overlay 2 DMA Next Register */
  #define REG_LCDC_OVR2CFG0 (*(__IO uint32_t*)0xF000026CU) /**< \brief (LCDC) Overlay 2 Configuration Register 0 */
  #define REG_LCDC_OVR2CFG1 (*(__IO uint32_t*)0xF0000270U) /**< \brief (LCDC) Overlay 2 Configuration Register 1 */
  #define REG_LCDC_OVR2CFG2 (*(__IO uint32_t*)0xF0000274U) /**< \brief (LCDC) Overlay 2 Configuration Register 2 */
  #define REG_LCDC_OVR2CFG3 (*(__IO uint32_t*)0xF0000278U) /**< \brief (LCDC) Overlay 2 Configuration Register 3 */
  #define REG_LCDC_OVR2CFG4 (*(__IO uint32_t*)0xF000027CU) /**< \brief (LCDC) Overlay 2 Configuration Register 4 */
  #define REG_LCDC_OVR2CFG5 (*(__IO uint32_t*)0xF0000280U) /**< \brief (LCDC) Overlay 2 Configuration Register 5 */
  #define REG_LCDC_OVR2CFG6 (*(__IO uint32_t*)0xF0000284U) /**< \brief (LCDC) Overlay 2 Configuration Register 6 */
  #define REG_LCDC_OVR2CFG7 (*(__IO uint32_t*)0xF0000288U) /**< \brief (LCDC) Overlay 2 Configuration Register 7 */
  #define REG_LCDC_OVR2CFG8 (*(__IO uint32_t*)0xF000028CU) /**< \brief (LCDC) Overlay 2 Configuration Register 8 */
  #define REG_LCDC_OVR2CFG9 (*(__IO uint32_t*)0xF0000290U) /**< \brief (LCDC) Overlay 2 Configuration Register 8 */
  #define REG_LCDC_HEOCHER  (*(__O  uint32_t*)0xF0000340U) /**< \brief (LCDC) High End Overlay Channel Enable Register */
  #define REG_LCDC_HEOCHDR  (*(__O  uint32_t*)0xF0000344U) /**< \brief (LCDC) High End Overlay Channel Disable Register */
  #define REG_LCDC_HEOCHSR  (*(__I  uint32_t*)0xF0000348U) /**< \brief (LCDC) High End Overlay Channel Status Register */
  #define REG_LCDC_HEOIER   (*(__O  uint32_t*)0xF000034CU) /**< \brief (LCDC) High End Overlay Interrupt Enable Register */
  #define REG_LCDC_HEOIDR   (*(__O  uint32_t*)0xF0000350U) /**< \brief (LCDC) High End Overlay Interrupt Disable Register */
  #define REG_LCDC_HEOIMR   (*(__I  uint32_t*)0xF0000354U) /**< \brief (LCDC) High End Overlay Interrupt Mask Register */
  #define REG_LCDC_HEOISR   (*(__I  uint32_t*)0xF0000358U) /**< \brief (LCDC) High End Overlay Interrupt Status Register */
  #define REG_LCDC_HEOHEAD  (*(__IO uint32_t*)0xF000035CU) /**< \brief (LCDC) High End Overlay DMA Head Register */
  #define REG_LCDC_HEOADDR  (*(__IO uint32_t*)0xF0000360U) /**< \brief (LCDC) High End Overlay DMA Address Register */
  #define REG_LCDC_HEOCTRL  (*(__IO uint32_t*)0xF0000364U) /**< \brief (LCDC) High End Overlay DMA Control Register */
  #define REG_LCDC_HEONEXT  (*(__IO uint32_t*)0xF0000368U) /**< \brief (LCDC) High End Overlay DMA Next Register */
  #define REG_LCDC_HEOUHEAD (*(__IO uint32_t*)0xF000036CU) /**< \brief (LCDC) High End Overlay U-UV DMA Head Register */
  #define REG_LCDC_HEOUADDR (*(__IO uint32_t*)0xF0000370U) /**< \brief (LCDC) High End Overlay U-UV DMA Address Register */
  #define REG_LCDC_HEOUCTRL (*(__IO uint32_t*)0xF0000374U) /**< \brief (LCDC) High End Overlay U-UV DMA Control Register */
  #define REG_LCDC_HEOUNEXT (*(__IO uint32_t*)0xF0000378U) /**< \brief (LCDC) High End Overlay U-UV DMA Next Register */
  #define REG_LCDC_HEOVHEAD (*(__IO uint32_t*)0xF000037CU) /**< \brief (LCDC) High End Overlay V DMA Head Register */
  #define REG_LCDC_HEOVADDR (*(__IO uint32_t*)0xF0000380U) /**< \brief (LCDC) High End Overlay V DMA Address Register */
  #define REG_LCDC_HEOVCTRL (*(__IO uint32_t*)0xF0000384U) /**< \brief (LCDC) High End Overlay V DMA Control Register */
  #define REG_LCDC_HEOVNEXT (*(__IO uint32_t*)0xF0000388U) /**< \brief (LCDC) High End Overlay V DMA Next Register */
  #define REG_LCDC_HEOCFG0  (*(__IO uint32_t*)0xF000038CU) /**< \brief (LCDC) High End Overlay Configuration Register 0 */
  #define REG_LCDC_HEOCFG1  (*(__IO uint32_t*)0xF0000390U) /**< \brief (LCDC) High End Overlay Configuration Register 1 */
  #define REG_LCDC_HEOCFG2  (*(__IO uint32_t*)0xF0000394U) /**< \brief (LCDC) High End Overlay Configuration Register 2 */
  #define REG_LCDC_HEOCFG3  (*(__IO uint32_t*)0xF0000398U) /**< \brief (LCDC) High End Overlay Configuration Register 3 */
  #define REG_LCDC_HEOCFG4  (*(__IO uint32_t*)0xF000039CU) /**< \brief (LCDC) High End Overlay Configuration Register 4 */
  #define REG_LCDC_HEOCFG5  (*(__IO uint32_t*)0xF00003A0U) /**< \brief (LCDC) High End Overlay Configuration Register 5 */
  #define REG_LCDC_HEOCFG6  (*(__IO uint32_t*)0xF00003A4U) /**< \brief (LCDC) High End Overlay Configuration Register 6 */
  #define REG_LCDC_HEOCFG7  (*(__IO uint32_t*)0xF00003A8U) /**< \brief (LCDC) High End Overlay Configuration Register 7 */
  #define REG_LCDC_HEOCFG8  (*(__IO uint32_t*)0xF00003ACU) /**< \brief (LCDC) High End Overlay Configuration Register 8 */
  #define REG_LCDC_HEOCFG9  (*(__IO uint32_t*)0xF00003B0U) /**< \brief (LCDC) High End Overlay Configuration Register 9 */
  #define REG_LCDC_HEOCFG10 (*(__IO uint32_t*)0xF00003B4U) /**< \brief (LCDC) High End Overlay Configuration Register 10 */
  #define REG_LCDC_HEOCFG11 (*(__IO uint32_t*)0xF00003B8U) /**< \brief (LCDC) High End Overlay Configuration Register 11 */
  #define REG_LCDC_HEOCFG12 (*(__IO uint32_t*)0xF00003BCU) /**< \brief (LCDC) High End Overlay Configuration Register 12 */
  #define REG_LCDC_HEOCFG13 (*(__IO uint32_t*)0xF00003C0U) /**< \brief (LCDC) High End Overlay Configuration Register 13 */
  #define REG_LCDC_HEOCFG14 (*(__IO uint32_t*)0xF00003C4U) /**< \brief (LCDC) High End Overlay Configuration Register 14 */
  #define REG_LCDC_HEOCFG15 (*(__IO uint32_t*)0xF00003C8U) /**< \brief (LCDC) High End Overlay Configuration Register 15 */
  #define REG_LCDC_HEOCFG16 (*(__IO uint32_t*)0xF00003CCU) /**< \brief (LCDC) High End Overlay Configuration Register 16 */
  #define REG_LCDC_HEOCFG17 (*(__IO uint32_t*)0xF00003D0U) /**< \brief (LCDC) High End Overlay Configuration Register 17 */
  #define REG_LCDC_HEOCFG18 (*(__IO uint32_t*)0xF00003D4U) /**< \brief (LCDC) High End Overlay Configuration Register 18 */
  #define REG_LCDC_HEOCFG19 (*(__IO uint32_t*)0xF00003D8U) /**< \brief (LCDC) High End Overlay Configuration Register 19 */
  #define REG_LCDC_HEOCFG20 (*(__IO uint32_t*)0xF00003DCU) /**< \brief (LCDC) High End Overlay Configuration Register 20 */
  #define REG_LCDC_HEOCFG21 (*(__IO uint32_t*)0xF00003E0U) /**< \brief (LCDC) High End Overlay Configuration Register 21 */
  #define REG_LCDC_HEOCFG22 (*(__IO uint32_t*)0xF00003E4U) /**< \brief (LCDC) High End Overlay Configuration Register 22 */
  #define REG_LCDC_HEOCFG23 (*(__IO uint32_t*)0xF00003E8U) /**< \brief (LCDC) High End Overlay Configuration Register 23 */
  #define REG_LCDC_HEOCFG24 (*(__IO uint32_t*)0xF00003ECU) /**< \brief (LCDC) High End Overlay Configuration Register 24 */
  #define REG_LCDC_HEOCFG25 (*(__IO uint32_t*)0xF00003F0U) /**< \brief (LCDC) High End Overlay Configuration Register 25 */
  #define REG_LCDC_HEOCFG26 (*(__IO uint32_t*)0xF00003F4U) /**< \brief (LCDC) High End Overlay Configuration Register 26 */
  #define REG_LCDC_HEOCFG27 (*(__IO uint32_t*)0xF00003F8U) /**< \brief (LCDC) High End Overlay Configuration Register 27 */
  #define REG_LCDC_HEOCFG28 (*(__IO uint32_t*)0xF00003FCU) /**< \brief (LCDC) High End Overlay Configuration Register 28 */
  #define REG_LCDC_HEOCFG29 (*(__IO uint32_t*)0xF0000400U) /**< \brief (LCDC) High End Overlay Configuration Register 29 */
  #define REG_LCDC_HEOCFG30 (*(__IO uint32_t*)0xF0000404U) /**< \brief (LCDC) High End Overlay Configuration Register 30 */
  #define REG_LCDC_HEOCFG31 (*(__IO uint32_t*)0xF0000408U) /**< \brief (LCDC) High End Overlay Configuration Register 31 */
  #define REG_LCDC_HEOCFG32 (*(__IO uint32_t*)0xF000040CU) /**< \brief (LCDC) High End Overlay Configuration Register 32 */
  #define REG_LCDC_HEOCFG33 (*(__IO uint32_t*)0xF0000410U) /**< \brief (LCDC) High End Overlay Configuration Register 33 */
  #define REG_LCDC_HEOCFG34 (*(__IO uint32_t*)0xF0000414U) /**< \brief (LCDC) High End Overlay Configuration Register 34 */
  #define REG_LCDC_HEOCFG35 (*(__IO uint32_t*)0xF0000418U) /**< \brief (LCDC) High End Overlay Configuration Register 35 */
  #define REG_LCDC_HEOCFG36 (*(__IO uint32_t*)0xF000041CU) /**< \brief (LCDC) High End Overlay Configuration Register 36 */
  #define REG_LCDC_HEOCFG37 (*(__IO uint32_t*)0xF0000420U) /**< \brief (LCDC) High End Overlay Configuration Register 37 */
  #define REG_LCDC_HEOCFG38 (*(__IO uint32_t*)0xF0000424U) /**< \brief (LCDC) High End Overlay Configuration Register 38 */
  #define REG_LCDC_HEOCFG39 (*(__IO uint32_t*)0xF0000428U) /**< \brief (LCDC) High End Overlay Configuration Register 39 */
  #define REG_LCDC_HEOCFG40 (*(__IO uint32_t*)0xF000042CU) /**< \brief (LCDC) High End Overlay Configuration Register 40 */
  #define REG_LCDC_HEOCFG41 (*(__IO uint32_t*)0xF0000430U) /**< \brief (LCDC) High End Overlay Configuration Register 41 */
  #define REG_LCDC_PPCHER   (*(__O  uint32_t*)0xF0000540U) /**< \brief (LCDC) Post Processing Channel Enable Register */
  #define REG_LCDC_PPCHDR   (*(__O  uint32_t*)0xF0000544U) /**< \brief (LCDC) Post Processing Channel Disable Register */
  #define REG_LCDC_PPCHSR   (*(__I  uint32_t*)0xF0000548U) /**< \brief (LCDC) Post Processing Channel Status Register */
  #define REG_LCDC_PPIER    (*(__O  uint32_t*)0xF000054CU) /**< \brief (LCDC) Post Processing Interrupt Enable Register */
  #define REG_LCDC_PPIDR    (*(__O  uint32_t*)0xF0000550U) /**< \brief (LCDC) Post Processing Interrupt Disable Register */
  #define REG_LCDC_PPIMR    (*(__I  uint32_t*)0xF0000554U) /**< \brief (LCDC) Post Processing Interrupt Mask Register */
  #define REG_LCDC_PPISR    (*(__I  uint32_t*)0xF0000558U) /**< \brief (LCDC) Post Processing Interrupt Status Register */
  #define REG_LCDC_PPHEAD   (*(__IO uint32_t*)0xF000055CU) /**< \brief (LCDC) Post Processing Head Register */
  #define REG_LCDC_PPADDR   (*(__IO uint32_t*)0xF0000560U) /**< \brief (LCDC) Post Processing Address Register */
  #define REG_LCDC_PPCTRL   (*(__IO uint32_t*)0xF0000564U) /**< \brief (LCDC) Post Processing Control Register */
  #define REG_LCDC_PPNEXT   (*(__IO uint32_t*)0xF0000568U) /**< \brief (LCDC) Post Processing Next Register */
  #define REG_LCDC_PPCFG0   (*(__IO uint32_t*)0xF000056CU) /**< \brief (LCDC) Post Processing Configuration Register 0 */
  #define REG_LCDC_PPCFG1   (*(__IO uint32_t*)0xF0000570U) /**< \brief (LCDC) Post Processing Configuration Register 1 */
  #define REG_LCDC_PPCFG2   (*(__IO uint32_t*)0xF0000574U) /**< \brief (LCDC) Post Processing Configuration Register 2 */
  #define REG_LCDC_PPCFG3   (*(__IO uint32_t*)0xF0000578U) /**< \brief (LCDC) Post Processing Configuration Register 3 */
  #define REG_LCDC_PPCFG4   (*(__IO uint32_t*)0xF000057CU) /**< \brief (LCDC) Post Processing Configuration Register 4 */
  #define REG_LCDC_PPCFG5   (*(__IO uint32_t*)0xF0000580U) /**< \brief (LCDC) Post Processing Configuration Register 5 */
  #define REG_LCDC_BASECLUT (*(__IO uint32_t*)0xF0000600U) /**< \brief (LCDC) Base CLUT Register */
  #define REG_LCDC_OVR1CLUT (*(__IO uint32_t*)0xF0000A00U) /**< \brief (LCDC) Overlay 1 CLUT Register */
  #define REG_LCDC_OVR2CLUT (*(__IO uint32_t*)0xF0000E00U) /**< \brief (LCDC) Overlay 2 CLUT Register */
  #define REG_LCDC_HEOCLUT  (*(__IO uint32_t*)0xF0001200U) /**< \brief (LCDC) High End Overlay CLUT Register */
  #define REG_LCDC_ADDRSIZE (*(__I  uint32_t*)0xF0001FECU) /**< \brief (LCDC) Address Size Register */
  #define REG_LCDC_IPNAME   (*(__I  uint32_t*)0xF0001FF0U) /**< \brief (LCDC) IP Name1 Register */
  #define REG_LCDC_FEATURES (*(__I  uint32_t*)0xF0001FF8U) /**< \brief (LCDC) Features Register */
  #define REG_LCDC_VERSION  (*(__I  uint32_t*)0xF0001FFCU) /**< \brief (LCDC) Version Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_LCDC_INSTANCE_ */
