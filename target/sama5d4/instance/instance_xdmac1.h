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

#ifndef _SAMA5D4_XDMAC1_INSTANCE_
#define _SAMA5D4_XDMAC1_INSTANCE_

/* ========== Register definition for XDMAC1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_XDMAC1_GTYPE                      (0xF0004000U) /**< \brief (XDMAC1) Global Type Register */
  #define REG_XDMAC1_GCFG                       (0xF0004004U) /**< \brief (XDMAC1) Global Configuration Register */
  #define REG_XDMAC1_GWAC                       (0xF0004008U) /**< \brief (XDMAC1) Global Weighted Arbiter Configuration Register */
  #define REG_XDMAC1_GIE                        (0xF000400CU) /**< \brief (XDMAC1) Global Interrupt Enable Register */
  #define REG_XDMAC1_GID                        (0xF0004010U) /**< \brief (XDMAC1) Global Interrupt Disable Register */
  #define REG_XDMAC1_GIM                        (0xF0004014U) /**< \brief (XDMAC1) Global Interrupt Mask Register */
  #define REG_XDMAC1_GIS                        (0xF0004018U) /**< \brief (XDMAC1) Global Interrupt Status Register */
  #define REG_XDMAC1_GE                         (0xF000401CU) /**< \brief (XDMAC1) Global Channel Enable Register */
  #define REG_XDMAC1_GD                         (0xF0004020U) /**< \brief (XDMAC1) Global Channel Disable Register */
  #define REG_XDMAC1_GS                         (0xF0004024U) /**< \brief (XDMAC1) Global Channel Status Register */
  #define REG_XDMAC1_GRS                        (0xF0004028U) /**< \brief (XDMAC1) Global Channel Read Suspend Register */
  #define REG_XDMAC1_GWS                        (0xF000402CU) /**< \brief (XDMAC1) Global Channel Write Suspend Register */
  #define REG_XDMAC1_GRWS                       (0xF0004030U) /**< \brief (XDMAC1) Global Channel Read Write Suspend Register */
  #define REG_XDMAC1_GRWR                       (0xF0004034U) /**< \brief (XDMAC1) Global Channel Read Write Resume Register */
  #define REG_XDMAC1_GSWR                       (0xF0004038U) /**< \brief (XDMAC1) Global Channel Software Request Register */
  #define REG_XDMAC1_GSWS                       (0xF000403CU) /**< \brief (XDMAC1) Global Channel Software Request Status Register */
  #define REG_XDMAC1_GSWF                       (0xF0004040U) /**< \brief (XDMAC1) Global Channel Software Flush Request Register */
  #define REG_XDMAC1_CIE0                       (0xF0004050U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 0) */
  #define REG_XDMAC1_CID0                       (0xF0004054U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 0) */
  #define REG_XDMAC1_CIM0                       (0xF0004058U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 0) */
  #define REG_XDMAC1_CIS0                       (0xF000405CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 0) */
  #define REG_XDMAC1_CSA0                       (0xF0004060U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 0) */
  #define REG_XDMAC1_CDA0                       (0xF0004064U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 0) */
  #define REG_XDMAC1_CNDA0                      (0xF0004068U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 0) */
  #define REG_XDMAC1_CNDC0                      (0xF000406CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 0) */
  #define REG_XDMAC1_CUBC0                      (0xF0004070U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 0) */
  #define REG_XDMAC1_CBC0                       (0xF0004074U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 0) */
  #define REG_XDMAC1_CC0                        (0xF0004078U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 0) */
  #define REG_XDMAC1_CDS_MSP0                   (0xF000407CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 0) */
  #define REG_XDMAC1_CSUS0                      (0xF0004080U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 0) */
  #define REG_XDMAC1_CDUS0                      (0xF0004084U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 0) */
  #define REG_XDMAC1_CIE1                       (0xF0004090U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 1) */
  #define REG_XDMAC1_CID1                       (0xF0004094U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 1) */
  #define REG_XDMAC1_CIM1                       (0xF0004098U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 1) */
  #define REG_XDMAC1_CIS1                       (0xF000409CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 1) */
  #define REG_XDMAC1_CSA1                       (0xF00040A0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 1) */
  #define REG_XDMAC1_CDA1                       (0xF00040A4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 1) */
  #define REG_XDMAC1_CNDA1                      (0xF00040A8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 1) */
  #define REG_XDMAC1_CNDC1                      (0xF00040ACU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 1) */
  #define REG_XDMAC1_CUBC1                      (0xF00040B0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 1) */
  #define REG_XDMAC1_CBC1                       (0xF00040B4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 1) */
  #define REG_XDMAC1_CC1                        (0xF00040B8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 1) */
  #define REG_XDMAC1_CDS_MSP1                   (0xF00040BCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 1) */
  #define REG_XDMAC1_CSUS1                      (0xF00040C0U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 1) */
  #define REG_XDMAC1_CDUS1                      (0xF00040C4U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 1) */
  #define REG_XDMAC1_CIE2                       (0xF00040D0U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 2) */
  #define REG_XDMAC1_CID2                       (0xF00040D4U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 2) */
  #define REG_XDMAC1_CIM2                       (0xF00040D8U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 2) */
  #define REG_XDMAC1_CIS2                       (0xF00040DCU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 2) */
  #define REG_XDMAC1_CSA2                       (0xF00040E0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 2) */
  #define REG_XDMAC1_CDA2                       (0xF00040E4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 2) */
  #define REG_XDMAC1_CNDA2                      (0xF00040E8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 2) */
  #define REG_XDMAC1_CNDC2                      (0xF00040ECU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 2) */
  #define REG_XDMAC1_CUBC2                      (0xF00040F0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 2) */
  #define REG_XDMAC1_CBC2                       (0xF00040F4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 2) */
  #define REG_XDMAC1_CC2                        (0xF00040F8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 2) */
  #define REG_XDMAC1_CDS_MSP2                   (0xF00040FCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 2) */
  #define REG_XDMAC1_CSUS2                      (0xF0004100U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 2) */
  #define REG_XDMAC1_CDUS2                      (0xF0004104U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 2) */
  #define REG_XDMAC1_CIE3                       (0xF0004110U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 3) */
  #define REG_XDMAC1_CID3                       (0xF0004114U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 3) */
  #define REG_XDMAC1_CIM3                       (0xF0004118U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 3) */
  #define REG_XDMAC1_CIS3                       (0xF000411CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 3) */
  #define REG_XDMAC1_CSA3                       (0xF0004120U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 3) */
  #define REG_XDMAC1_CDA3                       (0xF0004124U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 3) */
  #define REG_XDMAC1_CNDA3                      (0xF0004128U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 3) */
  #define REG_XDMAC1_CNDC3                      (0xF000412CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 3) */
  #define REG_XDMAC1_CUBC3                      (0xF0004130U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 3) */
  #define REG_XDMAC1_CBC3                       (0xF0004134U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 3) */
  #define REG_XDMAC1_CC3                        (0xF0004138U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 3) */
  #define REG_XDMAC1_CDS_MSP3                   (0xF000413CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 3) */
  #define REG_XDMAC1_CSUS3                      (0xF0004140U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 3) */
  #define REG_XDMAC1_CDUS3                      (0xF0004144U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 3) */
  #define REG_XDMAC1_CIE4                       (0xF0004150U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 4) */
  #define REG_XDMAC1_CID4                       (0xF0004154U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 4) */
  #define REG_XDMAC1_CIM4                       (0xF0004158U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 4) */
  #define REG_XDMAC1_CIS4                       (0xF000415CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 4) */
  #define REG_XDMAC1_CSA4                       (0xF0004160U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 4) */
  #define REG_XDMAC1_CDA4                       (0xF0004164U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 4) */
  #define REG_XDMAC1_CNDA4                      (0xF0004168U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 4) */
  #define REG_XDMAC1_CNDC4                      (0xF000416CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 4) */
  #define REG_XDMAC1_CUBC4                      (0xF0004170U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 4) */
  #define REG_XDMAC1_CBC4                       (0xF0004174U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 4) */
  #define REG_XDMAC1_CC4                        (0xF0004178U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 4) */
  #define REG_XDMAC1_CDS_MSP4                   (0xF000417CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 4) */
  #define REG_XDMAC1_CSUS4                      (0xF0004180U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 4) */
  #define REG_XDMAC1_CDUS4                      (0xF0004184U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 4) */
  #define REG_XDMAC1_CIE5                       (0xF0004190U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 5) */
  #define REG_XDMAC1_CID5                       (0xF0004194U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 5) */
  #define REG_XDMAC1_CIM5                       (0xF0004198U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 5) */
  #define REG_XDMAC1_CIS5                       (0xF000419CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 5) */
  #define REG_XDMAC1_CSA5                       (0xF00041A0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 5) */
  #define REG_XDMAC1_CDA5                       (0xF00041A4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 5) */
  #define REG_XDMAC1_CNDA5                      (0xF00041A8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 5) */
  #define REG_XDMAC1_CNDC5                      (0xF00041ACU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 5) */
  #define REG_XDMAC1_CUBC5                      (0xF00041B0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 5) */
  #define REG_XDMAC1_CBC5                       (0xF00041B4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 5) */
  #define REG_XDMAC1_CC5                        (0xF00041B8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 5) */
  #define REG_XDMAC1_CDS_MSP5                   (0xF00041BCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 5) */
  #define REG_XDMAC1_CSUS5                      (0xF00041C0U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 5) */
  #define REG_XDMAC1_CDUS5                      (0xF00041C4U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 5) */
  #define REG_XDMAC1_CIE6                       (0xF00041D0U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 6) */
  #define REG_XDMAC1_CID6                       (0xF00041D4U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 6) */
  #define REG_XDMAC1_CIM6                       (0xF00041D8U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 6) */
  #define REG_XDMAC1_CIS6                       (0xF00041DCU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 6) */
  #define REG_XDMAC1_CSA6                       (0xF00041E0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 6) */
  #define REG_XDMAC1_CDA6                       (0xF00041E4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 6) */
  #define REG_XDMAC1_CNDA6                      (0xF00041E8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 6) */
  #define REG_XDMAC1_CNDC6                      (0xF00041ECU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 6) */
  #define REG_XDMAC1_CUBC6                      (0xF00041F0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 6) */
  #define REG_XDMAC1_CBC6                       (0xF00041F4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 6) */
  #define REG_XDMAC1_CC6                        (0xF00041F8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 6) */
  #define REG_XDMAC1_CDS_MSP6                   (0xF00041FCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 6) */
  #define REG_XDMAC1_CSUS6                      (0xF0004200U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 6) */
  #define REG_XDMAC1_CDUS6                      (0xF0004204U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 6) */
  #define REG_XDMAC1_CIE7                       (0xF0004210U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 7) */
  #define REG_XDMAC1_CID7                       (0xF0004214U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 7) */
  #define REG_XDMAC1_CIM7                       (0xF0004218U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 7) */
  #define REG_XDMAC1_CIS7                       (0xF000421CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 7) */
  #define REG_XDMAC1_CSA7                       (0xF0004220U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 7) */
  #define REG_XDMAC1_CDA7                       (0xF0004224U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 7) */
  #define REG_XDMAC1_CNDA7                      (0xF0004228U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 7) */
  #define REG_XDMAC1_CNDC7                      (0xF000422CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 7) */
  #define REG_XDMAC1_CUBC7                      (0xF0004230U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 7) */
  #define REG_XDMAC1_CBC7                       (0xF0004234U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 7) */
  #define REG_XDMAC1_CC7                        (0xF0004238U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 7) */
  #define REG_XDMAC1_CDS_MSP7                   (0xF000423CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 7) */
  #define REG_XDMAC1_CSUS7                      (0xF0004240U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 7) */
  #define REG_XDMAC1_CDUS7                      (0xF0004244U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 7) */
  #define REG_XDMAC1_CIE8                       (0xF0004250U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 8) */
  #define REG_XDMAC1_CID8                       (0xF0004254U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 8) */
  #define REG_XDMAC1_CIM8                       (0xF0004258U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 8) */
  #define REG_XDMAC1_CIS8                       (0xF000425CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 8) */
  #define REG_XDMAC1_CSA8                       (0xF0004260U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 8) */
  #define REG_XDMAC1_CDA8                       (0xF0004264U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 8) */
  #define REG_XDMAC1_CNDA8                      (0xF0004268U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 8) */
  #define REG_XDMAC1_CNDC8                      (0xF000426CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 8) */
  #define REG_XDMAC1_CUBC8                      (0xF0004270U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 8) */
  #define REG_XDMAC1_CBC8                       (0xF0004274U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 8) */
  #define REG_XDMAC1_CC8                        (0xF0004278U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 8) */
  #define REG_XDMAC1_CDS_MSP8                   (0xF000427CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 8) */
  #define REG_XDMAC1_CSUS8                      (0xF0004280U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 8) */
  #define REG_XDMAC1_CDUS8                      (0xF0004284U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 8) */
  #define REG_XDMAC1_CIE9                       (0xF0004290U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 9) */
  #define REG_XDMAC1_CID9                       (0xF0004294U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 9) */
  #define REG_XDMAC1_CIM9                       (0xF0004298U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 9) */
  #define REG_XDMAC1_CIS9                       (0xF000429CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 9) */
  #define REG_XDMAC1_CSA9                       (0xF00042A0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 9) */
  #define REG_XDMAC1_CDA9                       (0xF00042A4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 9) */
  #define REG_XDMAC1_CNDA9                      (0xF00042A8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 9) */
  #define REG_XDMAC1_CNDC9                      (0xF00042ACU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 9) */
  #define REG_XDMAC1_CUBC9                      (0xF00042B0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 9) */
  #define REG_XDMAC1_CBC9                       (0xF00042B4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 9) */
  #define REG_XDMAC1_CC9                        (0xF00042B8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 9) */
  #define REG_XDMAC1_CDS_MSP9                   (0xF00042BCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 9) */
  #define REG_XDMAC1_CSUS9                      (0xF00042C0U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 9) */
  #define REG_XDMAC1_CDUS9                      (0xF00042C4U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 9) */
  #define REG_XDMAC1_CIE10                      (0xF00042D0U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 10) */
  #define REG_XDMAC1_CID10                      (0xF00042D4U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 10) */
  #define REG_XDMAC1_CIM10                      (0xF00042D8U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 10) */
  #define REG_XDMAC1_CIS10                      (0xF00042DCU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 10) */
  #define REG_XDMAC1_CSA10                      (0xF00042E0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 10) */
  #define REG_XDMAC1_CDA10                      (0xF00042E4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 10) */
  #define REG_XDMAC1_CNDA10                     (0xF00042E8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 10) */
  #define REG_XDMAC1_CNDC10                     (0xF00042ECU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 10) */
  #define REG_XDMAC1_CUBC10                     (0xF00042F0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 10) */
  #define REG_XDMAC1_CBC10                      (0xF00042F4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 10) */
  #define REG_XDMAC1_CC10                       (0xF00042F8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 10) */
  #define REG_XDMAC1_CDS_MSP10                  (0xF00042FCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 10) */
  #define REG_XDMAC1_CSUS10                     (0xF0004300U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 10) */
  #define REG_XDMAC1_CDUS10                     (0xF0004304U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 10) */
  #define REG_XDMAC1_CIE11                      (0xF0004310U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 11) */
  #define REG_XDMAC1_CID11                      (0xF0004314U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 11) */
  #define REG_XDMAC1_CIM11                      (0xF0004318U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 11) */
  #define REG_XDMAC1_CIS11                      (0xF000431CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 11) */
  #define REG_XDMAC1_CSA11                      (0xF0004320U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 11) */
  #define REG_XDMAC1_CDA11                      (0xF0004324U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 11) */
  #define REG_XDMAC1_CNDA11                     (0xF0004328U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 11) */
  #define REG_XDMAC1_CNDC11                     (0xF000432CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 11) */
  #define REG_XDMAC1_CUBC11                     (0xF0004330U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 11) */
  #define REG_XDMAC1_CBC11                      (0xF0004334U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 11) */
  #define REG_XDMAC1_CC11                       (0xF0004338U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 11) */
  #define REG_XDMAC1_CDS_MSP11                  (0xF000433CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 11) */
  #define REG_XDMAC1_CSUS11                     (0xF0004340U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 11) */
  #define REG_XDMAC1_CDUS11                     (0xF0004344U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 11) */
  #define REG_XDMAC1_CIE12                      (0xF0004350U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 12) */
  #define REG_XDMAC1_CID12                      (0xF0004354U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 12) */
  #define REG_XDMAC1_CIM12                      (0xF0004358U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 12) */
  #define REG_XDMAC1_CIS12                      (0xF000435CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 12) */
  #define REG_XDMAC1_CSA12                      (0xF0004360U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 12) */
  #define REG_XDMAC1_CDA12                      (0xF0004364U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 12) */
  #define REG_XDMAC1_CNDA12                     (0xF0004368U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 12) */
  #define REG_XDMAC1_CNDC12                     (0xF000436CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 12) */
  #define REG_XDMAC1_CUBC12                     (0xF0004370U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 12) */
  #define REG_XDMAC1_CBC12                      (0xF0004374U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 12) */
  #define REG_XDMAC1_CC12                       (0xF0004378U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 12) */
  #define REG_XDMAC1_CDS_MSP12                  (0xF000437CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 12) */
  #define REG_XDMAC1_CSUS12                     (0xF0004380U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 12) */
  #define REG_XDMAC1_CDUS12                     (0xF0004384U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 12) */
  #define REG_XDMAC1_CIE13                      (0xF0004390U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 13) */
  #define REG_XDMAC1_CID13                      (0xF0004394U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 13) */
  #define REG_XDMAC1_CIM13                      (0xF0004398U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 13) */
  #define REG_XDMAC1_CIS13                      (0xF000439CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 13) */
  #define REG_XDMAC1_CSA13                      (0xF00043A0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 13) */
  #define REG_XDMAC1_CDA13                      (0xF00043A4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 13) */
  #define REG_XDMAC1_CNDA13                     (0xF00043A8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 13) */
  #define REG_XDMAC1_CNDC13                     (0xF00043ACU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 13) */
  #define REG_XDMAC1_CUBC13                     (0xF00043B0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 13) */
  #define REG_XDMAC1_CBC13                      (0xF00043B4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 13) */
  #define REG_XDMAC1_CC13                       (0xF00043B8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 13) */
  #define REG_XDMAC1_CDS_MSP13                  (0xF00043BCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 13) */
  #define REG_XDMAC1_CSUS13                     (0xF00043C0U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 13) */
  #define REG_XDMAC1_CDUS13                     (0xF00043C4U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 13) */
  #define REG_XDMAC1_CIE14                      (0xF00043D0U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 14) */
  #define REG_XDMAC1_CID14                      (0xF00043D4U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 14) */
  #define REG_XDMAC1_CIM14                      (0xF00043D8U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 14) */
  #define REG_XDMAC1_CIS14                      (0xF00043DCU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 14) */
  #define REG_XDMAC1_CSA14                      (0xF00043E0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 14) */
  #define REG_XDMAC1_CDA14                      (0xF00043E4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 14) */
  #define REG_XDMAC1_CNDA14                     (0xF00043E8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 14) */
  #define REG_XDMAC1_CNDC14                     (0xF00043ECU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 14) */
  #define REG_XDMAC1_CUBC14                     (0xF00043F0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 14) */
  #define REG_XDMAC1_CBC14                      (0xF00043F4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 14) */
  #define REG_XDMAC1_CC14                       (0xF00043F8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 14) */
  #define REG_XDMAC1_CDS_MSP14                  (0xF00043FCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 14) */
  #define REG_XDMAC1_CSUS14                     (0xF0004400U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 14) */
  #define REG_XDMAC1_CDUS14                     (0xF0004404U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 14) */
  #define REG_XDMAC1_CIE15                      (0xF0004410U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 15) */
  #define REG_XDMAC1_CID15                      (0xF0004414U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 15) */
  #define REG_XDMAC1_CIM15                      (0xF0004418U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 15) */
  #define REG_XDMAC1_CIS15                      (0xF000441CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 15) */
  #define REG_XDMAC1_CSA15                      (0xF0004420U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 15) */
  #define REG_XDMAC1_CDA15                      (0xF0004424U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 15) */
  #define REG_XDMAC1_CNDA15                     (0xF0004428U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 15) */
  #define REG_XDMAC1_CNDC15                     (0xF000442CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 15) */
  #define REG_XDMAC1_CUBC15                     (0xF0004430U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 15) */
  #define REG_XDMAC1_CBC15                      (0xF0004434U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 15) */
  #define REG_XDMAC1_CC15                       (0xF0004438U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 15) */
  #define REG_XDMAC1_CDS_MSP15                  (0xF000443CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 15) */
  #define REG_XDMAC1_CSUS15                     (0xF0004440U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 15) */
  #define REG_XDMAC1_CDUS15                     (0xF0004444U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 15) */
#else
  #define REG_XDMAC1_GTYPE     (*(__IO uint32_t*)0xF0004000U) /**< \brief (XDMAC1) Global Type Register */
  #define REG_XDMAC1_GCFG      (*(__I  uint32_t*)0xF0004004U) /**< \brief (XDMAC1) Global Configuration Register */
  #define REG_XDMAC1_GWAC      (*(__IO uint32_t*)0xF0004008U) /**< \brief (XDMAC1) Global Weighted Arbiter Configuration Register */
  #define REG_XDMAC1_GIE       (*(__O  uint32_t*)0xF000400CU) /**< \brief (XDMAC1) Global Interrupt Enable Register */
  #define REG_XDMAC1_GID       (*(__O  uint32_t*)0xF0004010U) /**< \brief (XDMAC1) Global Interrupt Disable Register */
  #define REG_XDMAC1_GIM       (*(__I  uint32_t*)0xF0004014U) /**< \brief (XDMAC1) Global Interrupt Mask Register */
  #define REG_XDMAC1_GIS       (*(__I  uint32_t*)0xF0004018U) /**< \brief (XDMAC1) Global Interrupt Status Register */
  #define REG_XDMAC1_GE        (*(__O  uint32_t*)0xF000401CU) /**< \brief (XDMAC1) Global Channel Enable Register */
  #define REG_XDMAC1_GD        (*(__O  uint32_t*)0xF0004020U) /**< \brief (XDMAC1) Global Channel Disable Register */
  #define REG_XDMAC1_GS        (*(__I  uint32_t*)0xF0004024U) /**< \brief (XDMAC1) Global Channel Status Register */
  #define REG_XDMAC1_GRS       (*(__IO uint32_t*)0xF0004028U) /**< \brief (XDMAC1) Global Channel Read Suspend Register */
  #define REG_XDMAC1_GWS       (*(__IO uint32_t*)0xF000402CU) /**< \brief (XDMAC1) Global Channel Write Suspend Register */
  #define REG_XDMAC1_GRWS      (*(__O  uint32_t*)0xF0004030U) /**< \brief (XDMAC1) Global Channel Read Write Suspend Register */
  #define REG_XDMAC1_GRWR      (*(__O  uint32_t*)0xF0004034U) /**< \brief (XDMAC1) Global Channel Read Write Resume Register */
  #define REG_XDMAC1_GSWR      (*(__O  uint32_t*)0xF0004038U) /**< \brief (XDMAC1) Global Channel Software Request Register */
  #define REG_XDMAC1_GSWS      (*(__I  uint32_t*)0xF000403CU) /**< \brief (XDMAC1) Global Channel Software Request Status Register */
  #define REG_XDMAC1_GSWF      (*(__O  uint32_t*)0xF0004040U) /**< \brief (XDMAC1) Global Channel Software Flush Request Register */
  #define REG_XDMAC1_CIE0      (*(__O  uint32_t*)0xF0004050U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 0) */
  #define REG_XDMAC1_CID0      (*(__O  uint32_t*)0xF0004054U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 0) */
  #define REG_XDMAC1_CIM0      (*(__O  uint32_t*)0xF0004058U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 0) */
  #define REG_XDMAC1_CIS0      (*(__I  uint32_t*)0xF000405CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 0) */
  #define REG_XDMAC1_CSA0      (*(__IO uint32_t*)0xF0004060U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 0) */
  #define REG_XDMAC1_CDA0      (*(__IO uint32_t*)0xF0004064U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 0) */
  #define REG_XDMAC1_CNDA0     (*(__IO uint32_t*)0xF0004068U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 0) */
  #define REG_XDMAC1_CNDC0     (*(__IO uint32_t*)0xF000406CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 0) */
  #define REG_XDMAC1_CUBC0     (*(__IO uint32_t*)0xF0004070U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 0) */
  #define REG_XDMAC1_CBC0      (*(__IO uint32_t*)0xF0004074U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 0) */
  #define REG_XDMAC1_CC0       (*(__IO uint32_t*)0xF0004078U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 0) */
  #define REG_XDMAC1_CDS_MSP0  (*(__IO uint32_t*)0xF000407CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 0) */
  #define REG_XDMAC1_CSUS0     (*(__IO uint32_t*)0xF0004080U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 0) */
  #define REG_XDMAC1_CDUS0     (*(__IO uint32_t*)0xF0004084U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 0) */
  #define REG_XDMAC1_CIE1      (*(__O  uint32_t*)0xF0004090U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 1) */
  #define REG_XDMAC1_CID1      (*(__O  uint32_t*)0xF0004094U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 1) */
  #define REG_XDMAC1_CIM1      (*(__O  uint32_t*)0xF0004098U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 1) */
  #define REG_XDMAC1_CIS1      (*(__I  uint32_t*)0xF000409CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 1) */
  #define REG_XDMAC1_CSA1      (*(__IO uint32_t*)0xF00040A0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 1) */
  #define REG_XDMAC1_CDA1      (*(__IO uint32_t*)0xF00040A4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 1) */
  #define REG_XDMAC1_CNDA1     (*(__IO uint32_t*)0xF00040A8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 1) */
  #define REG_XDMAC1_CNDC1     (*(__IO uint32_t*)0xF00040ACU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 1) */
  #define REG_XDMAC1_CUBC1     (*(__IO uint32_t*)0xF00040B0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 1) */
  #define REG_XDMAC1_CBC1      (*(__IO uint32_t*)0xF00040B4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 1) */
  #define REG_XDMAC1_CC1       (*(__IO uint32_t*)0xF00040B8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 1) */
  #define REG_XDMAC1_CDS_MSP1  (*(__IO uint32_t*)0xF00040BCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 1) */
  #define REG_XDMAC1_CSUS1     (*(__IO uint32_t*)0xF00040C0U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 1) */
  #define REG_XDMAC1_CDUS1     (*(__IO uint32_t*)0xF00040C4U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 1) */
  #define REG_XDMAC1_CIE2      (*(__O  uint32_t*)0xF00040D0U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 2) */
  #define REG_XDMAC1_CID2      (*(__O  uint32_t*)0xF00040D4U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 2) */
  #define REG_XDMAC1_CIM2      (*(__O  uint32_t*)0xF00040D8U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 2) */
  #define REG_XDMAC1_CIS2      (*(__I  uint32_t*)0xF00040DCU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 2) */
  #define REG_XDMAC1_CSA2      (*(__IO uint32_t*)0xF00040E0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 2) */
  #define REG_XDMAC1_CDA2      (*(__IO uint32_t*)0xF00040E4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 2) */
  #define REG_XDMAC1_CNDA2     (*(__IO uint32_t*)0xF00040E8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 2) */
  #define REG_XDMAC1_CNDC2     (*(__IO uint32_t*)0xF00040ECU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 2) */
  #define REG_XDMAC1_CUBC2     (*(__IO uint32_t*)0xF00040F0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 2) */
  #define REG_XDMAC1_CBC2      (*(__IO uint32_t*)0xF00040F4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 2) */
  #define REG_XDMAC1_CC2       (*(__IO uint32_t*)0xF00040F8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 2) */
  #define REG_XDMAC1_CDS_MSP2  (*(__IO uint32_t*)0xF00040FCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 2) */
  #define REG_XDMAC1_CSUS2     (*(__IO uint32_t*)0xF0004100U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 2) */
  #define REG_XDMAC1_CDUS2     (*(__IO uint32_t*)0xF0004104U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 2) */
  #define REG_XDMAC1_CIE3      (*(__O  uint32_t*)0xF0004110U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 3) */
  #define REG_XDMAC1_CID3      (*(__O  uint32_t*)0xF0004114U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 3) */
  #define REG_XDMAC1_CIM3      (*(__O  uint32_t*)0xF0004118U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 3) */
  #define REG_XDMAC1_CIS3      (*(__I  uint32_t*)0xF000411CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 3) */
  #define REG_XDMAC1_CSA3      (*(__IO uint32_t*)0xF0004120U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 3) */
  #define REG_XDMAC1_CDA3      (*(__IO uint32_t*)0xF0004124U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 3) */
  #define REG_XDMAC1_CNDA3     (*(__IO uint32_t*)0xF0004128U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 3) */
  #define REG_XDMAC1_CNDC3     (*(__IO uint32_t*)0xF000412CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 3) */
  #define REG_XDMAC1_CUBC3     (*(__IO uint32_t*)0xF0004130U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 3) */
  #define REG_XDMAC1_CBC3      (*(__IO uint32_t*)0xF0004134U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 3) */
  #define REG_XDMAC1_CC3       (*(__IO uint32_t*)0xF0004138U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 3) */
  #define REG_XDMAC1_CDS_MSP3  (*(__IO uint32_t*)0xF000413CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 3) */
  #define REG_XDMAC1_CSUS3     (*(__IO uint32_t*)0xF0004140U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 3) */
  #define REG_XDMAC1_CDUS3     (*(__IO uint32_t*)0xF0004144U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 3) */
  #define REG_XDMAC1_CIE4      (*(__O  uint32_t*)0xF0004150U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 4) */
  #define REG_XDMAC1_CID4      (*(__O  uint32_t*)0xF0004154U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 4) */
  #define REG_XDMAC1_CIM4      (*(__O  uint32_t*)0xF0004158U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 4) */
  #define REG_XDMAC1_CIS4      (*(__I  uint32_t*)0xF000415CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 4) */
  #define REG_XDMAC1_CSA4      (*(__IO uint32_t*)0xF0004160U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 4) */
  #define REG_XDMAC1_CDA4      (*(__IO uint32_t*)0xF0004164U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 4) */
  #define REG_XDMAC1_CNDA4     (*(__IO uint32_t*)0xF0004168U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 4) */
  #define REG_XDMAC1_CNDC4     (*(__IO uint32_t*)0xF000416CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 4) */
  #define REG_XDMAC1_CUBC4     (*(__IO uint32_t*)0xF0004170U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 4) */
  #define REG_XDMAC1_CBC4      (*(__IO uint32_t*)0xF0004174U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 4) */
  #define REG_XDMAC1_CC4       (*(__IO uint32_t*)0xF0004178U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 4) */
  #define REG_XDMAC1_CDS_MSP4  (*(__IO uint32_t*)0xF000417CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 4) */
  #define REG_XDMAC1_CSUS4     (*(__IO uint32_t*)0xF0004180U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 4) */
  #define REG_XDMAC1_CDUS4     (*(__IO uint32_t*)0xF0004184U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 4) */
  #define REG_XDMAC1_CIE5      (*(__O  uint32_t*)0xF0004190U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 5) */
  #define REG_XDMAC1_CID5      (*(__O  uint32_t*)0xF0004194U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 5) */
  #define REG_XDMAC1_CIM5      (*(__O  uint32_t*)0xF0004198U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 5) */
  #define REG_XDMAC1_CIS5      (*(__I  uint32_t*)0xF000419CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 5) */
  #define REG_XDMAC1_CSA5      (*(__IO uint32_t*)0xF00041A0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 5) */
  #define REG_XDMAC1_CDA5      (*(__IO uint32_t*)0xF00041A4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 5) */
  #define REG_XDMAC1_CNDA5     (*(__IO uint32_t*)0xF00041A8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 5) */
  #define REG_XDMAC1_CNDC5     (*(__IO uint32_t*)0xF00041ACU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 5) */
  #define REG_XDMAC1_CUBC5     (*(__IO uint32_t*)0xF00041B0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 5) */
  #define REG_XDMAC1_CBC5      (*(__IO uint32_t*)0xF00041B4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 5) */
  #define REG_XDMAC1_CC5       (*(__IO uint32_t*)0xF00041B8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 5) */
  #define REG_XDMAC1_CDS_MSP5  (*(__IO uint32_t*)0xF00041BCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 5) */
  #define REG_XDMAC1_CSUS5     (*(__IO uint32_t*)0xF00041C0U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 5) */
  #define REG_XDMAC1_CDUS5     (*(__IO uint32_t*)0xF00041C4U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 5) */
  #define REG_XDMAC1_CIE6      (*(__O  uint32_t*)0xF00041D0U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 6) */
  #define REG_XDMAC1_CID6      (*(__O  uint32_t*)0xF00041D4U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 6) */
  #define REG_XDMAC1_CIM6      (*(__O  uint32_t*)0xF00041D8U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 6) */
  #define REG_XDMAC1_CIS6      (*(__I  uint32_t*)0xF00041DCU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 6) */
  #define REG_XDMAC1_CSA6      (*(__IO uint32_t*)0xF00041E0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 6) */
  #define REG_XDMAC1_CDA6      (*(__IO uint32_t*)0xF00041E4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 6) */
  #define REG_XDMAC1_CNDA6     (*(__IO uint32_t*)0xF00041E8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 6) */
  #define REG_XDMAC1_CNDC6     (*(__IO uint32_t*)0xF00041ECU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 6) */
  #define REG_XDMAC1_CUBC6     (*(__IO uint32_t*)0xF00041F0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 6) */
  #define REG_XDMAC1_CBC6      (*(__IO uint32_t*)0xF00041F4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 6) */
  #define REG_XDMAC1_CC6       (*(__IO uint32_t*)0xF00041F8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 6) */
  #define REG_XDMAC1_CDS_MSP6  (*(__IO uint32_t*)0xF00041FCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 6) */
  #define REG_XDMAC1_CSUS6     (*(__IO uint32_t*)0xF0004200U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 6) */
  #define REG_XDMAC1_CDUS6     (*(__IO uint32_t*)0xF0004204U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 6) */
  #define REG_XDMAC1_CIE7      (*(__O  uint32_t*)0xF0004210U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 7) */
  #define REG_XDMAC1_CID7      (*(__O  uint32_t*)0xF0004214U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 7) */
  #define REG_XDMAC1_CIM7      (*(__O  uint32_t*)0xF0004218U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 7) */
  #define REG_XDMAC1_CIS7      (*(__I  uint32_t*)0xF000421CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 7) */
  #define REG_XDMAC1_CSA7      (*(__IO uint32_t*)0xF0004220U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 7) */
  #define REG_XDMAC1_CDA7      (*(__IO uint32_t*)0xF0004224U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 7) */
  #define REG_XDMAC1_CNDA7     (*(__IO uint32_t*)0xF0004228U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 7) */
  #define REG_XDMAC1_CNDC7     (*(__IO uint32_t*)0xF000422CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 7) */
  #define REG_XDMAC1_CUBC7     (*(__IO uint32_t*)0xF0004230U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 7) */
  #define REG_XDMAC1_CBC7      (*(__IO uint32_t*)0xF0004234U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 7) */
  #define REG_XDMAC1_CC7       (*(__IO uint32_t*)0xF0004238U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 7) */
  #define REG_XDMAC1_CDS_MSP7  (*(__IO uint32_t*)0xF000423CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 7) */
  #define REG_XDMAC1_CSUS7     (*(__IO uint32_t*)0xF0004240U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 7) */
  #define REG_XDMAC1_CDUS7     (*(__IO uint32_t*)0xF0004244U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 7) */
  #define REG_XDMAC1_CIE8      (*(__O  uint32_t*)0xF0004250U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 8) */
  #define REG_XDMAC1_CID8      (*(__O  uint32_t*)0xF0004254U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 8) */
  #define REG_XDMAC1_CIM8      (*(__O  uint32_t*)0xF0004258U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 8) */
  #define REG_XDMAC1_CIS8      (*(__I  uint32_t*)0xF000425CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 8) */
  #define REG_XDMAC1_CSA8      (*(__IO uint32_t*)0xF0004260U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 8) */
  #define REG_XDMAC1_CDA8      (*(__IO uint32_t*)0xF0004264U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 8) */
  #define REG_XDMAC1_CNDA8     (*(__IO uint32_t*)0xF0004268U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 8) */
  #define REG_XDMAC1_CNDC8     (*(__IO uint32_t*)0xF000426CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 8) */
  #define REG_XDMAC1_CUBC8     (*(__IO uint32_t*)0xF0004270U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 8) */
  #define REG_XDMAC1_CBC8      (*(__IO uint32_t*)0xF0004274U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 8) */
  #define REG_XDMAC1_CC8       (*(__IO uint32_t*)0xF0004278U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 8) */
  #define REG_XDMAC1_CDS_MSP8  (*(__IO uint32_t*)0xF000427CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 8) */
  #define REG_XDMAC1_CSUS8     (*(__IO uint32_t*)0xF0004280U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 8) */
  #define REG_XDMAC1_CDUS8     (*(__IO uint32_t*)0xF0004284U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 8) */
  #define REG_XDMAC1_CIE9      (*(__O  uint32_t*)0xF0004290U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 9) */
  #define REG_XDMAC1_CID9      (*(__O  uint32_t*)0xF0004294U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 9) */
  #define REG_XDMAC1_CIM9      (*(__O  uint32_t*)0xF0004298U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 9) */
  #define REG_XDMAC1_CIS9      (*(__I  uint32_t*)0xF000429CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 9) */
  #define REG_XDMAC1_CSA9      (*(__IO uint32_t*)0xF00042A0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 9) */
  #define REG_XDMAC1_CDA9      (*(__IO uint32_t*)0xF00042A4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 9) */
  #define REG_XDMAC1_CNDA9     (*(__IO uint32_t*)0xF00042A8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 9) */
  #define REG_XDMAC1_CNDC9     (*(__IO uint32_t*)0xF00042ACU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 9) */
  #define REG_XDMAC1_CUBC9     (*(__IO uint32_t*)0xF00042B0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 9) */
  #define REG_XDMAC1_CBC9      (*(__IO uint32_t*)0xF00042B4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 9) */
  #define REG_XDMAC1_CC9       (*(__IO uint32_t*)0xF00042B8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 9) */
  #define REG_XDMAC1_CDS_MSP9  (*(__IO uint32_t*)0xF00042BCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 9) */
  #define REG_XDMAC1_CSUS9     (*(__IO uint32_t*)0xF00042C0U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 9) */
  #define REG_XDMAC1_CDUS9     (*(__IO uint32_t*)0xF00042C4U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 9) */
  #define REG_XDMAC1_CIE10     (*(__O  uint32_t*)0xF00042D0U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 10) */
  #define REG_XDMAC1_CID10     (*(__O  uint32_t*)0xF00042D4U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 10) */
  #define REG_XDMAC1_CIM10     (*(__O  uint32_t*)0xF00042D8U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 10) */
  #define REG_XDMAC1_CIS10     (*(__I  uint32_t*)0xF00042DCU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 10) */
  #define REG_XDMAC1_CSA10     (*(__IO uint32_t*)0xF00042E0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 10) */
  #define REG_XDMAC1_CDA10     (*(__IO uint32_t*)0xF00042E4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 10) */
  #define REG_XDMAC1_CNDA10    (*(__IO uint32_t*)0xF00042E8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 10) */
  #define REG_XDMAC1_CNDC10    (*(__IO uint32_t*)0xF00042ECU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 10) */
  #define REG_XDMAC1_CUBC10    (*(__IO uint32_t*)0xF00042F0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 10) */
  #define REG_XDMAC1_CBC10     (*(__IO uint32_t*)0xF00042F4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 10) */
  #define REG_XDMAC1_CC10      (*(__IO uint32_t*)0xF00042F8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 10) */
  #define REG_XDMAC1_CDS_MSP10 (*(__IO uint32_t*)0xF00042FCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 10) */
  #define REG_XDMAC1_CSUS10    (*(__IO uint32_t*)0xF0004300U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 10) */
  #define REG_XDMAC1_CDUS10    (*(__IO uint32_t*)0xF0004304U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 10) */
  #define REG_XDMAC1_CIE11     (*(__O  uint32_t*)0xF0004310U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 11) */
  #define REG_XDMAC1_CID11     (*(__O  uint32_t*)0xF0004314U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 11) */
  #define REG_XDMAC1_CIM11     (*(__O  uint32_t*)0xF0004318U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 11) */
  #define REG_XDMAC1_CIS11     (*(__I  uint32_t*)0xF000431CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 11) */
  #define REG_XDMAC1_CSA11     (*(__IO uint32_t*)0xF0004320U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 11) */
  #define REG_XDMAC1_CDA11     (*(__IO uint32_t*)0xF0004324U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 11) */
  #define REG_XDMAC1_CNDA11    (*(__IO uint32_t*)0xF0004328U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 11) */
  #define REG_XDMAC1_CNDC11    (*(__IO uint32_t*)0xF000432CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 11) */
  #define REG_XDMAC1_CUBC11    (*(__IO uint32_t*)0xF0004330U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 11) */
  #define REG_XDMAC1_CBC11     (*(__IO uint32_t*)0xF0004334U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 11) */
  #define REG_XDMAC1_CC11      (*(__IO uint32_t*)0xF0004338U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 11) */
  #define REG_XDMAC1_CDS_MSP11 (*(__IO uint32_t*)0xF000433CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 11) */
  #define REG_XDMAC1_CSUS11    (*(__IO uint32_t*)0xF0004340U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 11) */
  #define REG_XDMAC1_CDUS11    (*(__IO uint32_t*)0xF0004344U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 11) */
  #define REG_XDMAC1_CIE12     (*(__O  uint32_t*)0xF0004350U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 12) */
  #define REG_XDMAC1_CID12     (*(__O  uint32_t*)0xF0004354U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 12) */
  #define REG_XDMAC1_CIM12     (*(__O  uint32_t*)0xF0004358U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 12) */
  #define REG_XDMAC1_CIS12     (*(__I  uint32_t*)0xF000435CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 12) */
  #define REG_XDMAC1_CSA12     (*(__IO uint32_t*)0xF0004360U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 12) */
  #define REG_XDMAC1_CDA12     (*(__IO uint32_t*)0xF0004364U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 12) */
  #define REG_XDMAC1_CNDA12    (*(__IO uint32_t*)0xF0004368U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 12) */
  #define REG_XDMAC1_CNDC12    (*(__IO uint32_t*)0xF000436CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 12) */
  #define REG_XDMAC1_CUBC12    (*(__IO uint32_t*)0xF0004370U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 12) */
  #define REG_XDMAC1_CBC12     (*(__IO uint32_t*)0xF0004374U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 12) */
  #define REG_XDMAC1_CC12      (*(__IO uint32_t*)0xF0004378U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 12) */
  #define REG_XDMAC1_CDS_MSP12 (*(__IO uint32_t*)0xF000437CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 12) */
  #define REG_XDMAC1_CSUS12    (*(__IO uint32_t*)0xF0004380U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 12) */
  #define REG_XDMAC1_CDUS12    (*(__IO uint32_t*)0xF0004384U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 12) */
  #define REG_XDMAC1_CIE13     (*(__O  uint32_t*)0xF0004390U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 13) */
  #define REG_XDMAC1_CID13     (*(__O  uint32_t*)0xF0004394U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 13) */
  #define REG_XDMAC1_CIM13     (*(__O  uint32_t*)0xF0004398U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 13) */
  #define REG_XDMAC1_CIS13     (*(__I  uint32_t*)0xF000439CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 13) */
  #define REG_XDMAC1_CSA13     (*(__IO uint32_t*)0xF00043A0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 13) */
  #define REG_XDMAC1_CDA13     (*(__IO uint32_t*)0xF00043A4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 13) */
  #define REG_XDMAC1_CNDA13    (*(__IO uint32_t*)0xF00043A8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 13) */
  #define REG_XDMAC1_CNDC13    (*(__IO uint32_t*)0xF00043ACU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 13) */
  #define REG_XDMAC1_CUBC13    (*(__IO uint32_t*)0xF00043B0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 13) */
  #define REG_XDMAC1_CBC13     (*(__IO uint32_t*)0xF00043B4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 13) */
  #define REG_XDMAC1_CC13      (*(__IO uint32_t*)0xF00043B8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 13) */
  #define REG_XDMAC1_CDS_MSP13 (*(__IO uint32_t*)0xF00043BCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 13) */
  #define REG_XDMAC1_CSUS13    (*(__IO uint32_t*)0xF00043C0U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 13) */
  #define REG_XDMAC1_CDUS13    (*(__IO uint32_t*)0xF00043C4U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 13) */
  #define REG_XDMAC1_CIE14     (*(__O  uint32_t*)0xF00043D0U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 14) */
  #define REG_XDMAC1_CID14     (*(__O  uint32_t*)0xF00043D4U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 14) */
  #define REG_XDMAC1_CIM14     (*(__O  uint32_t*)0xF00043D8U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 14) */
  #define REG_XDMAC1_CIS14     (*(__I  uint32_t*)0xF00043DCU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 14) */
  #define REG_XDMAC1_CSA14     (*(__IO uint32_t*)0xF00043E0U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 14) */
  #define REG_XDMAC1_CDA14     (*(__IO uint32_t*)0xF00043E4U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 14) */
  #define REG_XDMAC1_CNDA14    (*(__IO uint32_t*)0xF00043E8U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 14) */
  #define REG_XDMAC1_CNDC14    (*(__IO uint32_t*)0xF00043ECU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 14) */
  #define REG_XDMAC1_CUBC14    (*(__IO uint32_t*)0xF00043F0U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 14) */
  #define REG_XDMAC1_CBC14     (*(__IO uint32_t*)0xF00043F4U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 14) */
  #define REG_XDMAC1_CC14      (*(__IO uint32_t*)0xF00043F8U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 14) */
  #define REG_XDMAC1_CDS_MSP14 (*(__IO uint32_t*)0xF00043FCU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 14) */
  #define REG_XDMAC1_CSUS14    (*(__IO uint32_t*)0xF0004400U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 14) */
  #define REG_XDMAC1_CDUS14    (*(__IO uint32_t*)0xF0004404U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 14) */
  #define REG_XDMAC1_CIE15     (*(__O  uint32_t*)0xF0004410U) /**< \brief (XDMAC1) Channel Interrupt Enable Register (chid = 15) */
  #define REG_XDMAC1_CID15     (*(__O  uint32_t*)0xF0004414U) /**< \brief (XDMAC1) Channel Interrupt Disable Register (chid = 15) */
  #define REG_XDMAC1_CIM15     (*(__O  uint32_t*)0xF0004418U) /**< \brief (XDMAC1) Channel Interrupt Mask Register (chid = 15) */
  #define REG_XDMAC1_CIS15     (*(__I  uint32_t*)0xF000441CU) /**< \brief (XDMAC1) Channel Interrupt Status Register (chid = 15) */
  #define REG_XDMAC1_CSA15     (*(__IO uint32_t*)0xF0004420U) /**< \brief (XDMAC1) Channel Source Address Register (chid = 15) */
  #define REG_XDMAC1_CDA15     (*(__IO uint32_t*)0xF0004424U) /**< \brief (XDMAC1) Channel Destination Address Register (chid = 15) */
  #define REG_XDMAC1_CNDA15    (*(__IO uint32_t*)0xF0004428U) /**< \brief (XDMAC1) Channel Next Descriptor Address Register (chid = 15) */
  #define REG_XDMAC1_CNDC15    (*(__IO uint32_t*)0xF000442CU) /**< \brief (XDMAC1) Channel Next Descriptor Control Register (chid = 15) */
  #define REG_XDMAC1_CUBC15    (*(__IO uint32_t*)0xF0004430U) /**< \brief (XDMAC1) Channel Microblock Control Register (chid = 15) */
  #define REG_XDMAC1_CBC15     (*(__IO uint32_t*)0xF0004434U) /**< \brief (XDMAC1) Channel Block Control Register (chid = 15) */
  #define REG_XDMAC1_CC15      (*(__IO uint32_t*)0xF0004438U) /**< \brief (XDMAC1) Channel Configuration Register (chid = 15) */
  #define REG_XDMAC1_CDS_MSP15 (*(__IO uint32_t*)0xF000443CU) /**< \brief (XDMAC1) Channel Data Stride Memory Set Pattern (chid = 15) */
  #define REG_XDMAC1_CSUS15    (*(__IO uint32_t*)0xF0004440U) /**< \brief (XDMAC1) Channel Source Microblock Stride (chid = 15) */
  #define REG_XDMAC1_CDUS15    (*(__IO uint32_t*)0xF0004444U) /**< \brief (XDMAC1) Channel Destination Microblock Stride (chid = 15) */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D4_XDMAC1_INSTANCE_ */
