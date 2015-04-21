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

#ifndef _SAMA5D4_XDMAC0_INSTANCE_
#define _SAMA5D4_XDMAC0_INSTANCE_

/* ========== Register definition for XDMAC0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_XDMAC0_GTYPE                      (0xF0014000U) /**< \brief (XDMAC0) Global Type Register */
  #define REG_XDMAC0_GCFG                       (0xF0014004U) /**< \brief (XDMAC0) Global Configuration Register */
  #define REG_XDMAC0_GWAC                       (0xF0014008U) /**< \brief (XDMAC0) Global Weighted Arbiter Configuration Register */
  #define REG_XDMAC0_GIE                        (0xF001400CU) /**< \brief (XDMAC0) Global Interrupt Enable Register */
  #define REG_XDMAC0_GID                        (0xF0014010U) /**< \brief (XDMAC0) Global Interrupt Disable Register */
  #define REG_XDMAC0_GIM                        (0xF0014014U) /**< \brief (XDMAC0) Global Interrupt Mask Register */
  #define REG_XDMAC0_GIS                        (0xF0014018U) /**< \brief (XDMAC0) Global Interrupt Status Register */
  #define REG_XDMAC0_GE                         (0xF001401CU) /**< \brief (XDMAC0) Global Channel Enable Register */
  #define REG_XDMAC0_GD                         (0xF0014020U) /**< \brief (XDMAC0) Global Channel Disable Register */
  #define REG_XDMAC0_GS                         (0xF0014024U) /**< \brief (XDMAC0) Global Channel Status Register */
  #define REG_XDMAC0_GRS                        (0xF0014028U) /**< \brief (XDMAC0) Global Channel Read Suspend Register */
  #define REG_XDMAC0_GWS                        (0xF001402CU) /**< \brief (XDMAC0) Global Channel Write Suspend Register */
  #define REG_XDMAC0_GRWS                       (0xF0014030U) /**< \brief (XDMAC0) Global Channel Read Write Suspend Register */
  #define REG_XDMAC0_GRWR                       (0xF0014034U) /**< \brief (XDMAC0) Global Channel Read Write Resume Register */
  #define REG_XDMAC0_GSWR                       (0xF0014038U) /**< \brief (XDMAC0) Global Channel Software Request Register */
  #define REG_XDMAC0_GSWS                       (0xF001403CU) /**< \brief (XDMAC0) Global Channel Software Request Status Register */
  #define REG_XDMAC0_GSWF                       (0xF0014040U) /**< \brief (XDMAC0) Global Channel Software Flush Request Register */
  #define REG_XDMAC0_CIE0                       (0xF0014050U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 0) */
  #define REG_XDMAC0_CID0                       (0xF0014054U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 0) */
  #define REG_XDMAC0_CIM0                       (0xF0014058U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 0) */
  #define REG_XDMAC0_CIS0                       (0xF001405CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 0) */
  #define REG_XDMAC0_CSA0                       (0xF0014060U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 0) */
  #define REG_XDMAC0_CDA0                       (0xF0014064U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 0) */
  #define REG_XDMAC0_CNDA0                      (0xF0014068U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 0) */
  #define REG_XDMAC0_CNDC0                      (0xF001406CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 0) */
  #define REG_XDMAC0_CUBC0                      (0xF0014070U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 0) */
  #define REG_XDMAC0_CBC0                       (0xF0014074U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 0) */
  #define REG_XDMAC0_CC0                        (0xF0014078U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 0) */
  #define REG_XDMAC0_CDS_MSP0                   (0xF001407CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 0) */
  #define REG_XDMAC0_CSUS0                      (0xF0014080U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 0) */
  #define REG_XDMAC0_CDUS0                      (0xF0014084U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 0) */
  #define REG_XDMAC0_CIE1                       (0xF0014090U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 1) */
  #define REG_XDMAC0_CID1                       (0xF0014094U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 1) */
  #define REG_XDMAC0_CIM1                       (0xF0014098U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 1) */
  #define REG_XDMAC0_CIS1                       (0xF001409CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 1) */
  #define REG_XDMAC0_CSA1                       (0xF00140A0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 1) */
  #define REG_XDMAC0_CDA1                       (0xF00140A4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 1) */
  #define REG_XDMAC0_CNDA1                      (0xF00140A8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 1) */
  #define REG_XDMAC0_CNDC1                      (0xF00140ACU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 1) */
  #define REG_XDMAC0_CUBC1                      (0xF00140B0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 1) */
  #define REG_XDMAC0_CBC1                       (0xF00140B4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 1) */
  #define REG_XDMAC0_CC1                        (0xF00140B8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 1) */
  #define REG_XDMAC0_CDS_MSP1                   (0xF00140BCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 1) */
  #define REG_XDMAC0_CSUS1                      (0xF00140C0U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 1) */
  #define REG_XDMAC0_CDUS1                      (0xF00140C4U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 1) */
  #define REG_XDMAC0_CIE2                       (0xF00140D0U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 2) */
  #define REG_XDMAC0_CID2                       (0xF00140D4U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 2) */
  #define REG_XDMAC0_CIM2                       (0xF00140D8U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 2) */
  #define REG_XDMAC0_CIS2                       (0xF00140DCU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 2) */
  #define REG_XDMAC0_CSA2                       (0xF00140E0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 2) */
  #define REG_XDMAC0_CDA2                       (0xF00140E4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 2) */
  #define REG_XDMAC0_CNDA2                      (0xF00140E8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 2) */
  #define REG_XDMAC0_CNDC2                      (0xF00140ECU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 2) */
  #define REG_XDMAC0_CUBC2                      (0xF00140F0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 2) */
  #define REG_XDMAC0_CBC2                       (0xF00140F4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 2) */
  #define REG_XDMAC0_CC2                        (0xF00140F8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 2) */
  #define REG_XDMAC0_CDS_MSP2                   (0xF00140FCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 2) */
  #define REG_XDMAC0_CSUS2                      (0xF0014100U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 2) */
  #define REG_XDMAC0_CDUS2                      (0xF0014104U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 2) */
  #define REG_XDMAC0_CIE3                       (0xF0014110U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 3) */
  #define REG_XDMAC0_CID3                       (0xF0014114U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 3) */
  #define REG_XDMAC0_CIM3                       (0xF0014118U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 3) */
  #define REG_XDMAC0_CIS3                       (0xF001411CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 3) */
  #define REG_XDMAC0_CSA3                       (0xF0014120U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 3) */
  #define REG_XDMAC0_CDA3                       (0xF0014124U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 3) */
  #define REG_XDMAC0_CNDA3                      (0xF0014128U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 3) */
  #define REG_XDMAC0_CNDC3                      (0xF001412CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 3) */
  #define REG_XDMAC0_CUBC3                      (0xF0014130U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 3) */
  #define REG_XDMAC0_CBC3                       (0xF0014134U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 3) */
  #define REG_XDMAC0_CC3                        (0xF0014138U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 3) */
  #define REG_XDMAC0_CDS_MSP3                   (0xF001413CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 3) */
  #define REG_XDMAC0_CSUS3                      (0xF0014140U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 3) */
  #define REG_XDMAC0_CDUS3                      (0xF0014144U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 3) */
  #define REG_XDMAC0_CIE4                       (0xF0014150U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 4) */
  #define REG_XDMAC0_CID4                       (0xF0014154U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 4) */
  #define REG_XDMAC0_CIM4                       (0xF0014158U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 4) */
  #define REG_XDMAC0_CIS4                       (0xF001415CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 4) */
  #define REG_XDMAC0_CSA4                       (0xF0014160U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 4) */
  #define REG_XDMAC0_CDA4                       (0xF0014164U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 4) */
  #define REG_XDMAC0_CNDA4                      (0xF0014168U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 4) */
  #define REG_XDMAC0_CNDC4                      (0xF001416CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 4) */
  #define REG_XDMAC0_CUBC4                      (0xF0014170U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 4) */
  #define REG_XDMAC0_CBC4                       (0xF0014174U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 4) */
  #define REG_XDMAC0_CC4                        (0xF0014178U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 4) */
  #define REG_XDMAC0_CDS_MSP4                   (0xF001417CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 4) */
  #define REG_XDMAC0_CSUS4                      (0xF0014180U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 4) */
  #define REG_XDMAC0_CDUS4                      (0xF0014184U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 4) */
  #define REG_XDMAC0_CIE5                       (0xF0014190U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 5) */
  #define REG_XDMAC0_CID5                       (0xF0014194U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 5) */
  #define REG_XDMAC0_CIM5                       (0xF0014198U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 5) */
  #define REG_XDMAC0_CIS5                       (0xF001419CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 5) */
  #define REG_XDMAC0_CSA5                       (0xF00141A0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 5) */
  #define REG_XDMAC0_CDA5                       (0xF00141A4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 5) */
  #define REG_XDMAC0_CNDA5                      (0xF00141A8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 5) */
  #define REG_XDMAC0_CNDC5                      (0xF00141ACU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 5) */
  #define REG_XDMAC0_CUBC5                      (0xF00141B0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 5) */
  #define REG_XDMAC0_CBC5                       (0xF00141B4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 5) */
  #define REG_XDMAC0_CC5                        (0xF00141B8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 5) */
  #define REG_XDMAC0_CDS_MSP5                   (0xF00141BCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 5) */
  #define REG_XDMAC0_CSUS5                      (0xF00141C0U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 5) */
  #define REG_XDMAC0_CDUS5                      (0xF00141C4U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 5) */
  #define REG_XDMAC0_CIE6                       (0xF00141D0U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 6) */
  #define REG_XDMAC0_CID6                       (0xF00141D4U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 6) */
  #define REG_XDMAC0_CIM6                       (0xF00141D8U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 6) */
  #define REG_XDMAC0_CIS6                       (0xF00141DCU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 6) */
  #define REG_XDMAC0_CSA6                       (0xF00141E0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 6) */
  #define REG_XDMAC0_CDA6                       (0xF00141E4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 6) */
  #define REG_XDMAC0_CNDA6                      (0xF00141E8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 6) */
  #define REG_XDMAC0_CNDC6                      (0xF00141ECU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 6) */
  #define REG_XDMAC0_CUBC6                      (0xF00141F0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 6) */
  #define REG_XDMAC0_CBC6                       (0xF00141F4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 6) */
  #define REG_XDMAC0_CC6                        (0xF00141F8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 6) */
  #define REG_XDMAC0_CDS_MSP6                   (0xF00141FCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 6) */
  #define REG_XDMAC0_CSUS6                      (0xF0014200U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 6) */
  #define REG_XDMAC0_CDUS6                      (0xF0014204U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 6) */
  #define REG_XDMAC0_CIE7                       (0xF0014210U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 7) */
  #define REG_XDMAC0_CID7                       (0xF0014214U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 7) */
  #define REG_XDMAC0_CIM7                       (0xF0014218U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 7) */
  #define REG_XDMAC0_CIS7                       (0xF001421CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 7) */
  #define REG_XDMAC0_CSA7                       (0xF0014220U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 7) */
  #define REG_XDMAC0_CDA7                       (0xF0014224U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 7) */
  #define REG_XDMAC0_CNDA7                      (0xF0014228U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 7) */
  #define REG_XDMAC0_CNDC7                      (0xF001422CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 7) */
  #define REG_XDMAC0_CUBC7                      (0xF0014230U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 7) */
  #define REG_XDMAC0_CBC7                       (0xF0014234U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 7) */
  #define REG_XDMAC0_CC7                        (0xF0014238U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 7) */
  #define REG_XDMAC0_CDS_MSP7                   (0xF001423CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 7) */
  #define REG_XDMAC0_CSUS7                      (0xF0014240U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 7) */
  #define REG_XDMAC0_CDUS7                      (0xF0014244U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 7) */
  #define REG_XDMAC0_CIE8                       (0xF0014250U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 8) */
  #define REG_XDMAC0_CID8                       (0xF0014254U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 8) */
  #define REG_XDMAC0_CIM8                       (0xF0014258U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 8) */
  #define REG_XDMAC0_CIS8                       (0xF001425CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 8) */
  #define REG_XDMAC0_CSA8                       (0xF0014260U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 8) */
  #define REG_XDMAC0_CDA8                       (0xF0014264U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 8) */
  #define REG_XDMAC0_CNDA8                      (0xF0014268U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 8) */
  #define REG_XDMAC0_CNDC8                      (0xF001426CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 8) */
  #define REG_XDMAC0_CUBC8                      (0xF0014270U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 8) */
  #define REG_XDMAC0_CBC8                       (0xF0014274U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 8) */
  #define REG_XDMAC0_CC8                        (0xF0014278U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 8) */
  #define REG_XDMAC0_CDS_MSP8                   (0xF001427CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 8) */
  #define REG_XDMAC0_CSUS8                      (0xF0014280U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 8) */
  #define REG_XDMAC0_CDUS8                      (0xF0014284U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 8) */
  #define REG_XDMAC0_CIE9                       (0xF0014290U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 9) */
  #define REG_XDMAC0_CID9                       (0xF0014294U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 9) */
  #define REG_XDMAC0_CIM9                       (0xF0014298U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 9) */
  #define REG_XDMAC0_CIS9                       (0xF001429CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 9) */
  #define REG_XDMAC0_CSA9                       (0xF00142A0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 9) */
  #define REG_XDMAC0_CDA9                       (0xF00142A4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 9) */
  #define REG_XDMAC0_CNDA9                      (0xF00142A8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 9) */
  #define REG_XDMAC0_CNDC9                      (0xF00142ACU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 9) */
  #define REG_XDMAC0_CUBC9                      (0xF00142B0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 9) */
  #define REG_XDMAC0_CBC9                       (0xF00142B4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 9) */
  #define REG_XDMAC0_CC9                        (0xF00142B8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 9) */
  #define REG_XDMAC0_CDS_MSP9                   (0xF00142BCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 9) */
  #define REG_XDMAC0_CSUS9                      (0xF00142C0U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 9) */
  #define REG_XDMAC0_CDUS9                      (0xF00142C4U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 9) */
  #define REG_XDMAC0_CIE10                      (0xF00142D0U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 10) */
  #define REG_XDMAC0_CID10                      (0xF00142D4U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 10) */
  #define REG_XDMAC0_CIM10                      (0xF00142D8U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 10) */
  #define REG_XDMAC0_CIS10                      (0xF00142DCU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 10) */
  #define REG_XDMAC0_CSA10                      (0xF00142E0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 10) */
  #define REG_XDMAC0_CDA10                      (0xF00142E4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 10) */
  #define REG_XDMAC0_CNDA10                     (0xF00142E8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 10) */
  #define REG_XDMAC0_CNDC10                     (0xF00142ECU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 10) */
  #define REG_XDMAC0_CUBC10                     (0xF00142F0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 10) */
  #define REG_XDMAC0_CBC10                      (0xF00142F4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 10) */
  #define REG_XDMAC0_CC10                       (0xF00142F8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 10) */
  #define REG_XDMAC0_CDS_MSP10                  (0xF00142FCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 10) */
  #define REG_XDMAC0_CSUS10                     (0xF0014300U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 10) */
  #define REG_XDMAC0_CDUS10                     (0xF0014304U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 10) */
  #define REG_XDMAC0_CIE11                      (0xF0014310U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 11) */
  #define REG_XDMAC0_CID11                      (0xF0014314U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 11) */
  #define REG_XDMAC0_CIM11                      (0xF0014318U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 11) */
  #define REG_XDMAC0_CIS11                      (0xF001431CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 11) */
  #define REG_XDMAC0_CSA11                      (0xF0014320U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 11) */
  #define REG_XDMAC0_CDA11                      (0xF0014324U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 11) */
  #define REG_XDMAC0_CNDA11                     (0xF0014328U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 11) */
  #define REG_XDMAC0_CNDC11                     (0xF001432CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 11) */
  #define REG_XDMAC0_CUBC11                     (0xF0014330U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 11) */
  #define REG_XDMAC0_CBC11                      (0xF0014334U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 11) */
  #define REG_XDMAC0_CC11                       (0xF0014338U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 11) */
  #define REG_XDMAC0_CDS_MSP11                  (0xF001433CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 11) */
  #define REG_XDMAC0_CSUS11                     (0xF0014340U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 11) */
  #define REG_XDMAC0_CDUS11                     (0xF0014344U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 11) */
  #define REG_XDMAC0_CIE12                      (0xF0014350U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 12) */
  #define REG_XDMAC0_CID12                      (0xF0014354U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 12) */
  #define REG_XDMAC0_CIM12                      (0xF0014358U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 12) */
  #define REG_XDMAC0_CIS12                      (0xF001435CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 12) */
  #define REG_XDMAC0_CSA12                      (0xF0014360U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 12) */
  #define REG_XDMAC0_CDA12                      (0xF0014364U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 12) */
  #define REG_XDMAC0_CNDA12                     (0xF0014368U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 12) */
  #define REG_XDMAC0_CNDC12                     (0xF001436CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 12) */
  #define REG_XDMAC0_CUBC12                     (0xF0014370U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 12) */
  #define REG_XDMAC0_CBC12                      (0xF0014374U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 12) */
  #define REG_XDMAC0_CC12                       (0xF0014378U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 12) */
  #define REG_XDMAC0_CDS_MSP12                  (0xF001437CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 12) */
  #define REG_XDMAC0_CSUS12                     (0xF0014380U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 12) */
  #define REG_XDMAC0_CDUS12                     (0xF0014384U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 12) */
  #define REG_XDMAC0_CIE13                      (0xF0014390U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 13) */
  #define REG_XDMAC0_CID13                      (0xF0014394U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 13) */
  #define REG_XDMAC0_CIM13                      (0xF0014398U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 13) */
  #define REG_XDMAC0_CIS13                      (0xF001439CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 13) */
  #define REG_XDMAC0_CSA13                      (0xF00143A0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 13) */
  #define REG_XDMAC0_CDA13                      (0xF00143A4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 13) */
  #define REG_XDMAC0_CNDA13                     (0xF00143A8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 13) */
  #define REG_XDMAC0_CNDC13                     (0xF00143ACU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 13) */
  #define REG_XDMAC0_CUBC13                     (0xF00143B0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 13) */
  #define REG_XDMAC0_CBC13                      (0xF00143B4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 13) */
  #define REG_XDMAC0_CC13                       (0xF00143B8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 13) */
  #define REG_XDMAC0_CDS_MSP13                  (0xF00143BCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 13) */
  #define REG_XDMAC0_CSUS13                     (0xF00143C0U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 13) */
  #define REG_XDMAC0_CDUS13                     (0xF00143C4U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 13) */
  #define REG_XDMAC0_CIE14                      (0xF00143D0U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 14) */
  #define REG_XDMAC0_CID14                      (0xF00143D4U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 14) */
  #define REG_XDMAC0_CIM14                      (0xF00143D8U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 14) */
  #define REG_XDMAC0_CIS14                      (0xF00143DCU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 14) */
  #define REG_XDMAC0_CSA14                      (0xF00143E0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 14) */
  #define REG_XDMAC0_CDA14                      (0xF00143E4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 14) */
  #define REG_XDMAC0_CNDA14                     (0xF00143E8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 14) */
  #define REG_XDMAC0_CNDC14                     (0xF00143ECU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 14) */
  #define REG_XDMAC0_CUBC14                     (0xF00143F0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 14) */
  #define REG_XDMAC0_CBC14                      (0xF00143F4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 14) */
  #define REG_XDMAC0_CC14                       (0xF00143F8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 14) */
  #define REG_XDMAC0_CDS_MSP14                  (0xF00143FCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 14) */
  #define REG_XDMAC0_CSUS14                     (0xF0014400U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 14) */
  #define REG_XDMAC0_CDUS14                     (0xF0014404U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 14) */
  #define REG_XDMAC0_CIE15                      (0xF0014410U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 15) */
  #define REG_XDMAC0_CID15                      (0xF0014414U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 15) */
  #define REG_XDMAC0_CIM15                      (0xF0014418U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 15) */
  #define REG_XDMAC0_CIS15                      (0xF001441CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 15) */
  #define REG_XDMAC0_CSA15                      (0xF0014420U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 15) */
  #define REG_XDMAC0_CDA15                      (0xF0014424U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 15) */
  #define REG_XDMAC0_CNDA15                     (0xF0014428U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 15) */
  #define REG_XDMAC0_CNDC15                     (0xF001442CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 15) */
  #define REG_XDMAC0_CUBC15                     (0xF0014430U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 15) */
  #define REG_XDMAC0_CBC15                      (0xF0014434U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 15) */
  #define REG_XDMAC0_CC15                       (0xF0014438U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 15) */
  #define REG_XDMAC0_CDS_MSP15                  (0xF001443CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 15) */
  #define REG_XDMAC0_CSUS15                     (0xF0014440U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 15) */
  #define REG_XDMAC0_CDUS15                     (0xF0014444U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 15) */
#else
  #define REG_XDMAC0_GTYPE     (*(__IO uint32_t*)0xF0014000U) /**< \brief (XDMAC0) Global Type Register */
  #define REG_XDMAC0_GCFG      (*(__I  uint32_t*)0xF0014004U) /**< \brief (XDMAC0) Global Configuration Register */
  #define REG_XDMAC0_GWAC      (*(__IO uint32_t*)0xF0014008U) /**< \brief (XDMAC0) Global Weighted Arbiter Configuration Register */
  #define REG_XDMAC0_GIE       (*(__O  uint32_t*)0xF001400CU) /**< \brief (XDMAC0) Global Interrupt Enable Register */
  #define REG_XDMAC0_GID       (*(__O  uint32_t*)0xF0014010U) /**< \brief (XDMAC0) Global Interrupt Disable Register */
  #define REG_XDMAC0_GIM       (*(__I  uint32_t*)0xF0014014U) /**< \brief (XDMAC0) Global Interrupt Mask Register */
  #define REG_XDMAC0_GIS       (*(__I  uint32_t*)0xF0014018U) /**< \brief (XDMAC0) Global Interrupt Status Register */
  #define REG_XDMAC0_GE        (*(__O  uint32_t*)0xF001401CU) /**< \brief (XDMAC0) Global Channel Enable Register */
  #define REG_XDMAC0_GD        (*(__O  uint32_t*)0xF0014020U) /**< \brief (XDMAC0) Global Channel Disable Register */
  #define REG_XDMAC0_GS        (*(__I  uint32_t*)0xF0014024U) /**< \brief (XDMAC0) Global Channel Status Register */
  #define REG_XDMAC0_GRS       (*(__IO uint32_t*)0xF0014028U) /**< \brief (XDMAC0) Global Channel Read Suspend Register */
  #define REG_XDMAC0_GWS       (*(__IO uint32_t*)0xF001402CU) /**< \brief (XDMAC0) Global Channel Write Suspend Register */
  #define REG_XDMAC0_GRWS      (*(__O  uint32_t*)0xF0014030U) /**< \brief (XDMAC0) Global Channel Read Write Suspend Register */
  #define REG_XDMAC0_GRWR      (*(__O  uint32_t*)0xF0014034U) /**< \brief (XDMAC0) Global Channel Read Write Resume Register */
  #define REG_XDMAC0_GSWR      (*(__O  uint32_t*)0xF0014038U) /**< \brief (XDMAC0) Global Channel Software Request Register */
  #define REG_XDMAC0_GSWS      (*(__I  uint32_t*)0xF001403CU) /**< \brief (XDMAC0) Global Channel Software Request Status Register */
  #define REG_XDMAC0_GSWF      (*(__O  uint32_t*)0xF0014040U) /**< \brief (XDMAC0) Global Channel Software Flush Request Register */
  #define REG_XDMAC0_CIE0      (*(__O  uint32_t*)0xF0014050U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 0) */
  #define REG_XDMAC0_CID0      (*(__O  uint32_t*)0xF0014054U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 0) */
  #define REG_XDMAC0_CIM0      (*(__O  uint32_t*)0xF0014058U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 0) */
  #define REG_XDMAC0_CIS0      (*(__I  uint32_t*)0xF001405CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 0) */
  #define REG_XDMAC0_CSA0      (*(__IO uint32_t*)0xF0014060U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 0) */
  #define REG_XDMAC0_CDA0      (*(__IO uint32_t*)0xF0014064U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 0) */
  #define REG_XDMAC0_CNDA0     (*(__IO uint32_t*)0xF0014068U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 0) */
  #define REG_XDMAC0_CNDC0     (*(__IO uint32_t*)0xF001406CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 0) */
  #define REG_XDMAC0_CUBC0     (*(__IO uint32_t*)0xF0014070U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 0) */
  #define REG_XDMAC0_CBC0      (*(__IO uint32_t*)0xF0014074U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 0) */
  #define REG_XDMAC0_CC0       (*(__IO uint32_t*)0xF0014078U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 0) */
  #define REG_XDMAC0_CDS_MSP0  (*(__IO uint32_t*)0xF001407CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 0) */
  #define REG_XDMAC0_CSUS0     (*(__IO uint32_t*)0xF0014080U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 0) */
  #define REG_XDMAC0_CDUS0     (*(__IO uint32_t*)0xF0014084U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 0) */
  #define REG_XDMAC0_CIE1      (*(__O  uint32_t*)0xF0014090U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 1) */
  #define REG_XDMAC0_CID1      (*(__O  uint32_t*)0xF0014094U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 1) */
  #define REG_XDMAC0_CIM1      (*(__O  uint32_t*)0xF0014098U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 1) */
  #define REG_XDMAC0_CIS1      (*(__I  uint32_t*)0xF001409CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 1) */
  #define REG_XDMAC0_CSA1      (*(__IO uint32_t*)0xF00140A0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 1) */
  #define REG_XDMAC0_CDA1      (*(__IO uint32_t*)0xF00140A4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 1) */
  #define REG_XDMAC0_CNDA1     (*(__IO uint32_t*)0xF00140A8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 1) */
  #define REG_XDMAC0_CNDC1     (*(__IO uint32_t*)0xF00140ACU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 1) */
  #define REG_XDMAC0_CUBC1     (*(__IO uint32_t*)0xF00140B0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 1) */
  #define REG_XDMAC0_CBC1      (*(__IO uint32_t*)0xF00140B4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 1) */
  #define REG_XDMAC0_CC1       (*(__IO uint32_t*)0xF00140B8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 1) */
  #define REG_XDMAC0_CDS_MSP1  (*(__IO uint32_t*)0xF00140BCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 1) */
  #define REG_XDMAC0_CSUS1     (*(__IO uint32_t*)0xF00140C0U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 1) */
  #define REG_XDMAC0_CDUS1     (*(__IO uint32_t*)0xF00140C4U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 1) */
  #define REG_XDMAC0_CIE2      (*(__O  uint32_t*)0xF00140D0U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 2) */
  #define REG_XDMAC0_CID2      (*(__O  uint32_t*)0xF00140D4U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 2) */
  #define REG_XDMAC0_CIM2      (*(__O  uint32_t*)0xF00140D8U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 2) */
  #define REG_XDMAC0_CIS2      (*(__I  uint32_t*)0xF00140DCU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 2) */
  #define REG_XDMAC0_CSA2      (*(__IO uint32_t*)0xF00140E0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 2) */
  #define REG_XDMAC0_CDA2      (*(__IO uint32_t*)0xF00140E4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 2) */
  #define REG_XDMAC0_CNDA2     (*(__IO uint32_t*)0xF00140E8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 2) */
  #define REG_XDMAC0_CNDC2     (*(__IO uint32_t*)0xF00140ECU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 2) */
  #define REG_XDMAC0_CUBC2     (*(__IO uint32_t*)0xF00140F0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 2) */
  #define REG_XDMAC0_CBC2      (*(__IO uint32_t*)0xF00140F4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 2) */
  #define REG_XDMAC0_CC2       (*(__IO uint32_t*)0xF00140F8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 2) */
  #define REG_XDMAC0_CDS_MSP2  (*(__IO uint32_t*)0xF00140FCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 2) */
  #define REG_XDMAC0_CSUS2     (*(__IO uint32_t*)0xF0014100U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 2) */
  #define REG_XDMAC0_CDUS2     (*(__IO uint32_t*)0xF0014104U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 2) */
  #define REG_XDMAC0_CIE3      (*(__O  uint32_t*)0xF0014110U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 3) */
  #define REG_XDMAC0_CID3      (*(__O  uint32_t*)0xF0014114U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 3) */
  #define REG_XDMAC0_CIM3      (*(__O  uint32_t*)0xF0014118U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 3) */
  #define REG_XDMAC0_CIS3      (*(__I  uint32_t*)0xF001411CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 3) */
  #define REG_XDMAC0_CSA3      (*(__IO uint32_t*)0xF0014120U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 3) */
  #define REG_XDMAC0_CDA3      (*(__IO uint32_t*)0xF0014124U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 3) */
  #define REG_XDMAC0_CNDA3     (*(__IO uint32_t*)0xF0014128U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 3) */
  #define REG_XDMAC0_CNDC3     (*(__IO uint32_t*)0xF001412CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 3) */
  #define REG_XDMAC0_CUBC3     (*(__IO uint32_t*)0xF0014130U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 3) */
  #define REG_XDMAC0_CBC3      (*(__IO uint32_t*)0xF0014134U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 3) */
  #define REG_XDMAC0_CC3       (*(__IO uint32_t*)0xF0014138U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 3) */
  #define REG_XDMAC0_CDS_MSP3  (*(__IO uint32_t*)0xF001413CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 3) */
  #define REG_XDMAC0_CSUS3     (*(__IO uint32_t*)0xF0014140U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 3) */
  #define REG_XDMAC0_CDUS3     (*(__IO uint32_t*)0xF0014144U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 3) */
  #define REG_XDMAC0_CIE4      (*(__O  uint32_t*)0xF0014150U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 4) */
  #define REG_XDMAC0_CID4      (*(__O  uint32_t*)0xF0014154U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 4) */
  #define REG_XDMAC0_CIM4      (*(__O  uint32_t*)0xF0014158U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 4) */
  #define REG_XDMAC0_CIS4      (*(__I  uint32_t*)0xF001415CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 4) */
  #define REG_XDMAC0_CSA4      (*(__IO uint32_t*)0xF0014160U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 4) */
  #define REG_XDMAC0_CDA4      (*(__IO uint32_t*)0xF0014164U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 4) */
  #define REG_XDMAC0_CNDA4     (*(__IO uint32_t*)0xF0014168U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 4) */
  #define REG_XDMAC0_CNDC4     (*(__IO uint32_t*)0xF001416CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 4) */
  #define REG_XDMAC0_CUBC4     (*(__IO uint32_t*)0xF0014170U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 4) */
  #define REG_XDMAC0_CBC4      (*(__IO uint32_t*)0xF0014174U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 4) */
  #define REG_XDMAC0_CC4       (*(__IO uint32_t*)0xF0014178U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 4) */
  #define REG_XDMAC0_CDS_MSP4  (*(__IO uint32_t*)0xF001417CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 4) */
  #define REG_XDMAC0_CSUS4     (*(__IO uint32_t*)0xF0014180U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 4) */
  #define REG_XDMAC0_CDUS4     (*(__IO uint32_t*)0xF0014184U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 4) */
  #define REG_XDMAC0_CIE5      (*(__O  uint32_t*)0xF0014190U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 5) */
  #define REG_XDMAC0_CID5      (*(__O  uint32_t*)0xF0014194U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 5) */
  #define REG_XDMAC0_CIM5      (*(__O  uint32_t*)0xF0014198U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 5) */
  #define REG_XDMAC0_CIS5      (*(__I  uint32_t*)0xF001419CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 5) */
  #define REG_XDMAC0_CSA5      (*(__IO uint32_t*)0xF00141A0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 5) */
  #define REG_XDMAC0_CDA5      (*(__IO uint32_t*)0xF00141A4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 5) */
  #define REG_XDMAC0_CNDA5     (*(__IO uint32_t*)0xF00141A8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 5) */
  #define REG_XDMAC0_CNDC5     (*(__IO uint32_t*)0xF00141ACU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 5) */
  #define REG_XDMAC0_CUBC5     (*(__IO uint32_t*)0xF00141B0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 5) */
  #define REG_XDMAC0_CBC5      (*(__IO uint32_t*)0xF00141B4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 5) */
  #define REG_XDMAC0_CC5       (*(__IO uint32_t*)0xF00141B8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 5) */
  #define REG_XDMAC0_CDS_MSP5  (*(__IO uint32_t*)0xF00141BCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 5) */
  #define REG_XDMAC0_CSUS5     (*(__IO uint32_t*)0xF00141C0U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 5) */
  #define REG_XDMAC0_CDUS5     (*(__IO uint32_t*)0xF00141C4U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 5) */
  #define REG_XDMAC0_CIE6      (*(__O  uint32_t*)0xF00141D0U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 6) */
  #define REG_XDMAC0_CID6      (*(__O  uint32_t*)0xF00141D4U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 6) */
  #define REG_XDMAC0_CIM6      (*(__O  uint32_t*)0xF00141D8U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 6) */
  #define REG_XDMAC0_CIS6      (*(__I  uint32_t*)0xF00141DCU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 6) */
  #define REG_XDMAC0_CSA6      (*(__IO uint32_t*)0xF00141E0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 6) */
  #define REG_XDMAC0_CDA6      (*(__IO uint32_t*)0xF00141E4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 6) */
  #define REG_XDMAC0_CNDA6     (*(__IO uint32_t*)0xF00141E8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 6) */
  #define REG_XDMAC0_CNDC6     (*(__IO uint32_t*)0xF00141ECU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 6) */
  #define REG_XDMAC0_CUBC6     (*(__IO uint32_t*)0xF00141F0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 6) */
  #define REG_XDMAC0_CBC6      (*(__IO uint32_t*)0xF00141F4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 6) */
  #define REG_XDMAC0_CC6       (*(__IO uint32_t*)0xF00141F8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 6) */
  #define REG_XDMAC0_CDS_MSP6  (*(__IO uint32_t*)0xF00141FCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 6) */
  #define REG_XDMAC0_CSUS6     (*(__IO uint32_t*)0xF0014200U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 6) */
  #define REG_XDMAC0_CDUS6     (*(__IO uint32_t*)0xF0014204U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 6) */
  #define REG_XDMAC0_CIE7      (*(__O  uint32_t*)0xF0014210U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 7) */
  #define REG_XDMAC0_CID7      (*(__O  uint32_t*)0xF0014214U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 7) */
  #define REG_XDMAC0_CIM7      (*(__O  uint32_t*)0xF0014218U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 7) */
  #define REG_XDMAC0_CIS7      (*(__I  uint32_t*)0xF001421CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 7) */
  #define REG_XDMAC0_CSA7      (*(__IO uint32_t*)0xF0014220U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 7) */
  #define REG_XDMAC0_CDA7      (*(__IO uint32_t*)0xF0014224U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 7) */
  #define REG_XDMAC0_CNDA7     (*(__IO uint32_t*)0xF0014228U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 7) */
  #define REG_XDMAC0_CNDC7     (*(__IO uint32_t*)0xF001422CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 7) */
  #define REG_XDMAC0_CUBC7     (*(__IO uint32_t*)0xF0014230U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 7) */
  #define REG_XDMAC0_CBC7      (*(__IO uint32_t*)0xF0014234U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 7) */
  #define REG_XDMAC0_CC7       (*(__IO uint32_t*)0xF0014238U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 7) */
  #define REG_XDMAC0_CDS_MSP7  (*(__IO uint32_t*)0xF001423CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 7) */
  #define REG_XDMAC0_CSUS7     (*(__IO uint32_t*)0xF0014240U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 7) */
  #define REG_XDMAC0_CDUS7     (*(__IO uint32_t*)0xF0014244U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 7) */
  #define REG_XDMAC0_CIE8      (*(__O  uint32_t*)0xF0014250U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 8) */
  #define REG_XDMAC0_CID8      (*(__O  uint32_t*)0xF0014254U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 8) */
  #define REG_XDMAC0_CIM8      (*(__O  uint32_t*)0xF0014258U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 8) */
  #define REG_XDMAC0_CIS8      (*(__I  uint32_t*)0xF001425CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 8) */
  #define REG_XDMAC0_CSA8      (*(__IO uint32_t*)0xF0014260U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 8) */
  #define REG_XDMAC0_CDA8      (*(__IO uint32_t*)0xF0014264U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 8) */
  #define REG_XDMAC0_CNDA8     (*(__IO uint32_t*)0xF0014268U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 8) */
  #define REG_XDMAC0_CNDC8     (*(__IO uint32_t*)0xF001426CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 8) */
  #define REG_XDMAC0_CUBC8     (*(__IO uint32_t*)0xF0014270U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 8) */
  #define REG_XDMAC0_CBC8      (*(__IO uint32_t*)0xF0014274U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 8) */
  #define REG_XDMAC0_CC8       (*(__IO uint32_t*)0xF0014278U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 8) */
  #define REG_XDMAC0_CDS_MSP8  (*(__IO uint32_t*)0xF001427CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 8) */
  #define REG_XDMAC0_CSUS8     (*(__IO uint32_t*)0xF0014280U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 8) */
  #define REG_XDMAC0_CDUS8     (*(__IO uint32_t*)0xF0014284U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 8) */
  #define REG_XDMAC0_CIE9      (*(__O  uint32_t*)0xF0014290U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 9) */
  #define REG_XDMAC0_CID9      (*(__O  uint32_t*)0xF0014294U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 9) */
  #define REG_XDMAC0_CIM9      (*(__O  uint32_t*)0xF0014298U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 9) */
  #define REG_XDMAC0_CIS9      (*(__I  uint32_t*)0xF001429CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 9) */
  #define REG_XDMAC0_CSA9      (*(__IO uint32_t*)0xF00142A0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 9) */
  #define REG_XDMAC0_CDA9      (*(__IO uint32_t*)0xF00142A4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 9) */
  #define REG_XDMAC0_CNDA9     (*(__IO uint32_t*)0xF00142A8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 9) */
  #define REG_XDMAC0_CNDC9     (*(__IO uint32_t*)0xF00142ACU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 9) */
  #define REG_XDMAC0_CUBC9     (*(__IO uint32_t*)0xF00142B0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 9) */
  #define REG_XDMAC0_CBC9      (*(__IO uint32_t*)0xF00142B4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 9) */
  #define REG_XDMAC0_CC9       (*(__IO uint32_t*)0xF00142B8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 9) */
  #define REG_XDMAC0_CDS_MSP9  (*(__IO uint32_t*)0xF00142BCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 9) */
  #define REG_XDMAC0_CSUS9     (*(__IO uint32_t*)0xF00142C0U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 9) */
  #define REG_XDMAC0_CDUS9     (*(__IO uint32_t*)0xF00142C4U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 9) */
  #define REG_XDMAC0_CIE10     (*(__O  uint32_t*)0xF00142D0U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 10) */
  #define REG_XDMAC0_CID10     (*(__O  uint32_t*)0xF00142D4U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 10) */
  #define REG_XDMAC0_CIM10     (*(__O  uint32_t*)0xF00142D8U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 10) */
  #define REG_XDMAC0_CIS10     (*(__I  uint32_t*)0xF00142DCU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 10) */
  #define REG_XDMAC0_CSA10     (*(__IO uint32_t*)0xF00142E0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 10) */
  #define REG_XDMAC0_CDA10     (*(__IO uint32_t*)0xF00142E4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 10) */
  #define REG_XDMAC0_CNDA10    (*(__IO uint32_t*)0xF00142E8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 10) */
  #define REG_XDMAC0_CNDC10    (*(__IO uint32_t*)0xF00142ECU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 10) */
  #define REG_XDMAC0_CUBC10    (*(__IO uint32_t*)0xF00142F0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 10) */
  #define REG_XDMAC0_CBC10     (*(__IO uint32_t*)0xF00142F4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 10) */
  #define REG_XDMAC0_CC10      (*(__IO uint32_t*)0xF00142F8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 10) */
  #define REG_XDMAC0_CDS_MSP10 (*(__IO uint32_t*)0xF00142FCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 10) */
  #define REG_XDMAC0_CSUS10    (*(__IO uint32_t*)0xF0014300U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 10) */
  #define REG_XDMAC0_CDUS10    (*(__IO uint32_t*)0xF0014304U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 10) */
  #define REG_XDMAC0_CIE11     (*(__O  uint32_t*)0xF0014310U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 11) */
  #define REG_XDMAC0_CID11     (*(__O  uint32_t*)0xF0014314U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 11) */
  #define REG_XDMAC0_CIM11     (*(__O  uint32_t*)0xF0014318U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 11) */
  #define REG_XDMAC0_CIS11     (*(__I  uint32_t*)0xF001431CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 11) */
  #define REG_XDMAC0_CSA11     (*(__IO uint32_t*)0xF0014320U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 11) */
  #define REG_XDMAC0_CDA11     (*(__IO uint32_t*)0xF0014324U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 11) */
  #define REG_XDMAC0_CNDA11    (*(__IO uint32_t*)0xF0014328U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 11) */
  #define REG_XDMAC0_CNDC11    (*(__IO uint32_t*)0xF001432CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 11) */
  #define REG_XDMAC0_CUBC11    (*(__IO uint32_t*)0xF0014330U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 11) */
  #define REG_XDMAC0_CBC11     (*(__IO uint32_t*)0xF0014334U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 11) */
  #define REG_XDMAC0_CC11      (*(__IO uint32_t*)0xF0014338U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 11) */
  #define REG_XDMAC0_CDS_MSP11 (*(__IO uint32_t*)0xF001433CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 11) */
  #define REG_XDMAC0_CSUS11    (*(__IO uint32_t*)0xF0014340U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 11) */
  #define REG_XDMAC0_CDUS11    (*(__IO uint32_t*)0xF0014344U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 11) */
  #define REG_XDMAC0_CIE12     (*(__O  uint32_t*)0xF0014350U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 12) */
  #define REG_XDMAC0_CID12     (*(__O  uint32_t*)0xF0014354U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 12) */
  #define REG_XDMAC0_CIM12     (*(__O  uint32_t*)0xF0014358U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 12) */
  #define REG_XDMAC0_CIS12     (*(__I  uint32_t*)0xF001435CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 12) */
  #define REG_XDMAC0_CSA12     (*(__IO uint32_t*)0xF0014360U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 12) */
  #define REG_XDMAC0_CDA12     (*(__IO uint32_t*)0xF0014364U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 12) */
  #define REG_XDMAC0_CNDA12    (*(__IO uint32_t*)0xF0014368U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 12) */
  #define REG_XDMAC0_CNDC12    (*(__IO uint32_t*)0xF001436CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 12) */
  #define REG_XDMAC0_CUBC12    (*(__IO uint32_t*)0xF0014370U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 12) */
  #define REG_XDMAC0_CBC12     (*(__IO uint32_t*)0xF0014374U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 12) */
  #define REG_XDMAC0_CC12      (*(__IO uint32_t*)0xF0014378U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 12) */
  #define REG_XDMAC0_CDS_MSP12 (*(__IO uint32_t*)0xF001437CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 12) */
  #define REG_XDMAC0_CSUS12    (*(__IO uint32_t*)0xF0014380U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 12) */
  #define REG_XDMAC0_CDUS12    (*(__IO uint32_t*)0xF0014384U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 12) */
  #define REG_XDMAC0_CIE13     (*(__O  uint32_t*)0xF0014390U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 13) */
  #define REG_XDMAC0_CID13     (*(__O  uint32_t*)0xF0014394U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 13) */
  #define REG_XDMAC0_CIM13     (*(__O  uint32_t*)0xF0014398U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 13) */
  #define REG_XDMAC0_CIS13     (*(__I  uint32_t*)0xF001439CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 13) */
  #define REG_XDMAC0_CSA13     (*(__IO uint32_t*)0xF00143A0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 13) */
  #define REG_XDMAC0_CDA13     (*(__IO uint32_t*)0xF00143A4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 13) */
  #define REG_XDMAC0_CNDA13    (*(__IO uint32_t*)0xF00143A8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 13) */
  #define REG_XDMAC0_CNDC13    (*(__IO uint32_t*)0xF00143ACU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 13) */
  #define REG_XDMAC0_CUBC13    (*(__IO uint32_t*)0xF00143B0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 13) */
  #define REG_XDMAC0_CBC13     (*(__IO uint32_t*)0xF00143B4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 13) */
  #define REG_XDMAC0_CC13      (*(__IO uint32_t*)0xF00143B8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 13) */
  #define REG_XDMAC0_CDS_MSP13 (*(__IO uint32_t*)0xF00143BCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 13) */
  #define REG_XDMAC0_CSUS13    (*(__IO uint32_t*)0xF00143C0U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 13) */
  #define REG_XDMAC0_CDUS13    (*(__IO uint32_t*)0xF00143C4U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 13) */
  #define REG_XDMAC0_CIE14     (*(__O  uint32_t*)0xF00143D0U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 14) */
  #define REG_XDMAC0_CID14     (*(__O  uint32_t*)0xF00143D4U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 14) */
  #define REG_XDMAC0_CIM14     (*(__O  uint32_t*)0xF00143D8U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 14) */
  #define REG_XDMAC0_CIS14     (*(__I  uint32_t*)0xF00143DCU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 14) */
  #define REG_XDMAC0_CSA14     (*(__IO uint32_t*)0xF00143E0U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 14) */
  #define REG_XDMAC0_CDA14     (*(__IO uint32_t*)0xF00143E4U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 14) */
  #define REG_XDMAC0_CNDA14    (*(__IO uint32_t*)0xF00143E8U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 14) */
  #define REG_XDMAC0_CNDC14    (*(__IO uint32_t*)0xF00143ECU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 14) */
  #define REG_XDMAC0_CUBC14    (*(__IO uint32_t*)0xF00143F0U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 14) */
  #define REG_XDMAC0_CBC14     (*(__IO uint32_t*)0xF00143F4U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 14) */
  #define REG_XDMAC0_CC14      (*(__IO uint32_t*)0xF00143F8U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 14) */
  #define REG_XDMAC0_CDS_MSP14 (*(__IO uint32_t*)0xF00143FCU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 14) */
  #define REG_XDMAC0_CSUS14    (*(__IO uint32_t*)0xF0014400U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 14) */
  #define REG_XDMAC0_CDUS14    (*(__IO uint32_t*)0xF0014404U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 14) */
  #define REG_XDMAC0_CIE15     (*(__O  uint32_t*)0xF0014410U) /**< \brief (XDMAC0) Channel Interrupt Enable Register (chid = 15) */
  #define REG_XDMAC0_CID15     (*(__O  uint32_t*)0xF0014414U) /**< \brief (XDMAC0) Channel Interrupt Disable Register (chid = 15) */
  #define REG_XDMAC0_CIM15     (*(__O  uint32_t*)0xF0014418U) /**< \brief (XDMAC0) Channel Interrupt Mask Register (chid = 15) */
  #define REG_XDMAC0_CIS15     (*(__I  uint32_t*)0xF001441CU) /**< \brief (XDMAC0) Channel Interrupt Status Register (chid = 15) */
  #define REG_XDMAC0_CSA15     (*(__IO uint32_t*)0xF0014420U) /**< \brief (XDMAC0) Channel Source Address Register (chid = 15) */
  #define REG_XDMAC0_CDA15     (*(__IO uint32_t*)0xF0014424U) /**< \brief (XDMAC0) Channel Destination Address Register (chid = 15) */
  #define REG_XDMAC0_CNDA15    (*(__IO uint32_t*)0xF0014428U) /**< \brief (XDMAC0) Channel Next Descriptor Address Register (chid = 15) */
  #define REG_XDMAC0_CNDC15    (*(__IO uint32_t*)0xF001442CU) /**< \brief (XDMAC0) Channel Next Descriptor Control Register (chid = 15) */
  #define REG_XDMAC0_CUBC15    (*(__IO uint32_t*)0xF0014430U) /**< \brief (XDMAC0) Channel Microblock Control Register (chid = 15) */
  #define REG_XDMAC0_CBC15     (*(__IO uint32_t*)0xF0014434U) /**< \brief (XDMAC0) Channel Block Control Register (chid = 15) */
  #define REG_XDMAC0_CC15      (*(__IO uint32_t*)0xF0014438U) /**< \brief (XDMAC0) Channel Configuration Register (chid = 15) */
  #define REG_XDMAC0_CDS_MSP15 (*(__IO uint32_t*)0xF001443CU) /**< \brief (XDMAC0) Channel Data Stride Memory Set Pattern (chid = 15) */
  #define REG_XDMAC0_CSUS15    (*(__IO uint32_t*)0xF0014440U) /**< \brief (XDMAC0) Channel Source Microblock Stride (chid = 15) */
  #define REG_XDMAC0_CDUS15    (*(__IO uint32_t*)0xF0014444U) /**< \brief (XDMAC0) Channel Destination Microblock Stride (chid = 15) */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D4_XDMAC0_INSTANCE_ */
