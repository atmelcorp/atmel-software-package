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

#ifndef _SAM9X_XDMAC_INSTANCE_
#define _SAM9X_XDMAC_INSTANCE_

/* ========== Register definition for XDMAC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_XDMAC_GTYPE                      (0xF0008000U) /**< \brief (XDMAC) Global Type Register */
  #define REG_XDMAC_GCFG                       (0xF0008004U) /**< \brief (XDMAC) Global Configuration Register */
  #define REG_XDMAC_GWAC                       (0xF0008008U) /**< \brief (XDMAC) Global Weighted Arbiter Configuration Register */
  #define REG_XDMAC_GIE                        (0xF000800CU) /**< \brief (XDMAC) Global Interrupt Enable Register */
  #define REG_XDMAC_GID                        (0xF0008010U) /**< \brief (XDMAC) Global Interrupt Disable Register */
  #define REG_XDMAC_GIM                        (0xF0008014U) /**< \brief (XDMAC) Global Interrupt Mask Register */
  #define REG_XDMAC_GIS                        (0xF0008018U) /**< \brief (XDMAC) Global Interrupt Status Register */
  #define REG_XDMAC_GE                         (0xF000801CU) /**< \brief (XDMAC) Global Channel Enable Register */
  #define REG_XDMAC_GD                         (0xF0008020U) /**< \brief (XDMAC) Global Channel Disable Register */
  #define REG_XDMAC_GS                         (0xF0008024U) /**< \brief (XDMAC) Global Channel Status Register */
  #define REG_XDMAC_GRS                        (0xF0008028U) /**< \brief (XDMAC) Global Channel Read Suspend Register */
  #define REG_XDMAC_GWS                        (0xF000802CU) /**< \brief (XDMAC) Global Channel Write Suspend Register */
  #define REG_XDMAC_GRWS                       (0xF0008030U) /**< \brief (XDMAC) Global Channel Read Write Suspend Register */
  #define REG_XDMAC_GRWR                       (0xF0008034U) /**< \brief (XDMAC) Global Channel Read Write Resume Register */
  #define REG_XDMAC_GSWR                       (0xF0008038U) /**< \brief (XDMAC) Global Channel Software Request Register */
  #define REG_XDMAC_GSWS                       (0xF000803CU) /**< \brief (XDMAC) Global Channel Software Request Status Register */
  #define REG_XDMAC_GSWF                       (0xF0008040U) /**< \brief (XDMAC) Global Channel Software Flush Request Register */
  #define REG_XDMAC_CIE0                       (0xF0008050U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 0) */
  #define REG_XDMAC_CID0                       (0xF0008054U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 0) */
  #define REG_XDMAC_CIM0                       (0xF0008058U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 0) */
  #define REG_XDMAC_CIS0                       (0xF000805CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 0) */
  #define REG_XDMAC_CSA0                       (0xF0008060U) /**< \brief (XDMAC) Channel Source Address Register (chid = 0) */
  #define REG_XDMAC_CDA0                       (0xF0008064U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 0) */
  #define REG_XDMAC_CNDA0                      (0xF0008068U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 0) */
  #define REG_XDMAC_CNDC0                      (0xF000806CU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 0) */
  #define REG_XDMAC_CUBC0                      (0xF0008070U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 0) */
  #define REG_XDMAC_CBC0                       (0xF0008074U) /**< \brief (XDMAC) Channel Block Control Register (chid = 0) */
  #define REG_XDMAC_CC0                        (0xF0008078U) /**< \brief (XDMAC) Channel Configuration Register (chid = 0) */
  #define REG_XDMAC_CDS_MSP0                   (0xF000807CU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 0) */
  #define REG_XDMAC_CSUS0                      (0xF0008080U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 0) */
  #define REG_XDMAC_CDUS0                      (0xF0008084U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 0) */
  #define REG_XDMAC_CIE1                       (0xF0008090U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 1) */
  #define REG_XDMAC_CID1                       (0xF0008094U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 1) */
  #define REG_XDMAC_CIM1                       (0xF0008098U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 1) */
  #define REG_XDMAC_CIS1                       (0xF000809CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 1) */
  #define REG_XDMAC_CSA1                       (0xF00080A0U) /**< \brief (XDMAC) Channel Source Address Register (chid = 1) */
  #define REG_XDMAC_CDA1                       (0xF00080A4U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 1) */
  #define REG_XDMAC_CNDA1                      (0xF00080A8U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 1) */
  #define REG_XDMAC_CNDC1                      (0xF00080ACU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 1) */
  #define REG_XDMAC_CUBC1                      (0xF00080B0U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 1) */
  #define REG_XDMAC_CBC1                       (0xF00080B4U) /**< \brief (XDMAC) Channel Block Control Register (chid = 1) */
  #define REG_XDMAC_CC1                        (0xF00080B8U) /**< \brief (XDMAC) Channel Configuration Register (chid = 1) */
  #define REG_XDMAC_CDS_MSP1                   (0xF00080BCU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 1) */
  #define REG_XDMAC_CSUS1                      (0xF00080C0U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 1) */
  #define REG_XDMAC_CDUS1                      (0xF00080C4U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 1) */
  #define REG_XDMAC_CIE2                       (0xF00080D0U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 2) */
  #define REG_XDMAC_CID2                       (0xF00080D4U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 2) */
  #define REG_XDMAC_CIM2                       (0xF00080D8U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 2) */
  #define REG_XDMAC_CIS2                       (0xF00080DCU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 2) */
  #define REG_XDMAC_CSA2                       (0xF00080E0U) /**< \brief (XDMAC) Channel Source Address Register (chid = 2) */
  #define REG_XDMAC_CDA2                       (0xF00080E4U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 2) */
  #define REG_XDMAC_CNDA2                      (0xF00080E8U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 2) */
  #define REG_XDMAC_CNDC2                      (0xF00080ECU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 2) */
  #define REG_XDMAC_CUBC2                      (0xF00080F0U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 2) */
  #define REG_XDMAC_CBC2                       (0xF00080F4U) /**< \brief (XDMAC) Channel Block Control Register (chid = 2) */
  #define REG_XDMAC_CC2                        (0xF00080F8U) /**< \brief (XDMAC) Channel Configuration Register (chid = 2) */
  #define REG_XDMAC_CDS_MSP2                   (0xF00080FCU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 2) */
  #define REG_XDMAC_CSUS2                      (0xF0008100U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 2) */
  #define REG_XDMAC_CDUS2                      (0xF0008104U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 2) */
  #define REG_XDMAC_CIE3                       (0xF0008110U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 3) */
  #define REG_XDMAC_CID3                       (0xF0008114U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 3) */
  #define REG_XDMAC_CIM3                       (0xF0008118U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 3) */
  #define REG_XDMAC_CIS3                       (0xF000811CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 3) */
  #define REG_XDMAC_CSA3                       (0xF0008120U) /**< \brief (XDMAC) Channel Source Address Register (chid = 3) */
  #define REG_XDMAC_CDA3                       (0xF0008124U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 3) */
  #define REG_XDMAC_CNDA3                      (0xF0008128U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 3) */
  #define REG_XDMAC_CNDC3                      (0xF000812CU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 3) */
  #define REG_XDMAC_CUBC3                      (0xF0008130U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 3) */
  #define REG_XDMAC_CBC3                       (0xF0008134U) /**< \brief (XDMAC) Channel Block Control Register (chid = 3) */
  #define REG_XDMAC_CC3                        (0xF0008138U) /**< \brief (XDMAC) Channel Configuration Register (chid = 3) */
  #define REG_XDMAC_CDS_MSP3                   (0xF000813CU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 3) */
  #define REG_XDMAC_CSUS3                      (0xF0008140U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 3) */
  #define REG_XDMAC_CDUS3                      (0xF0008144U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 3) */
  #define REG_XDMAC_CIE4                       (0xF0008150U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 4) */
  #define REG_XDMAC_CID4                       (0xF0008154U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 4) */
  #define REG_XDMAC_CIM4                       (0xF0008158U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 4) */
  #define REG_XDMAC_CIS4                       (0xF000815CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 4) */
  #define REG_XDMAC_CSA4                       (0xF0008160U) /**< \brief (XDMAC) Channel Source Address Register (chid = 4) */
  #define REG_XDMAC_CDA4                       (0xF0008164U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 4) */
  #define REG_XDMAC_CNDA4                      (0xF0008168U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 4) */
  #define REG_XDMAC_CNDC4                      (0xF000816CU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 4) */
  #define REG_XDMAC_CUBC4                      (0xF0008170U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 4) */
  #define REG_XDMAC_CBC4                       (0xF0008174U) /**< \brief (XDMAC) Channel Block Control Register (chid = 4) */
  #define REG_XDMAC_CC4                        (0xF0008178U) /**< \brief (XDMAC) Channel Configuration Register (chid = 4) */
  #define REG_XDMAC_CDS_MSP4                   (0xF000817CU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 4) */
  #define REG_XDMAC_CSUS4                      (0xF0008180U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 4) */
  #define REG_XDMAC_CDUS4                      (0xF0008184U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 4) */
  #define REG_XDMAC_CIE5                       (0xF0008190U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 5) */
  #define REG_XDMAC_CID5                       (0xF0008194U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 5) */
  #define REG_XDMAC_CIM5                       (0xF0008198U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 5) */
  #define REG_XDMAC_CIS5                       (0xF000819CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 5) */
  #define REG_XDMAC_CSA5                       (0xF00081A0U) /**< \brief (XDMAC) Channel Source Address Register (chid = 5) */
  #define REG_XDMAC_CDA5                       (0xF00081A4U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 5) */
  #define REG_XDMAC_CNDA5                      (0xF00081A8U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 5) */
  #define REG_XDMAC_CNDC5                      (0xF00081ACU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 5) */
  #define REG_XDMAC_CUBC5                      (0xF00081B0U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 5) */
  #define REG_XDMAC_CBC5                       (0xF00081B4U) /**< \brief (XDMAC) Channel Block Control Register (chid = 5) */
  #define REG_XDMAC_CC5                        (0xF00081B8U) /**< \brief (XDMAC) Channel Configuration Register (chid = 5) */
  #define REG_XDMAC_CDS_MSP5                   (0xF00081BCU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 5) */
  #define REG_XDMAC_CSUS5                      (0xF00081C0U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 5) */
  #define REG_XDMAC_CDUS5                      (0xF00081C4U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 5) */
  #define REG_XDMAC_CIE6                       (0xF00081D0U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 6) */
  #define REG_XDMAC_CID6                       (0xF00081D4U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 6) */
  #define REG_XDMAC_CIM6                       (0xF00081D8U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 6) */
  #define REG_XDMAC_CIS6                       (0xF00081DCU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 6) */
  #define REG_XDMAC_CSA6                       (0xF00081E0U) /**< \brief (XDMAC) Channel Source Address Register (chid = 6) */
  #define REG_XDMAC_CDA6                       (0xF00081E4U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 6) */
  #define REG_XDMAC_CNDA6                      (0xF00081E8U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 6) */
  #define REG_XDMAC_CNDC6                      (0xF00081ECU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 6) */
  #define REG_XDMAC_CUBC6                      (0xF00081F0U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 6) */
  #define REG_XDMAC_CBC6                       (0xF00081F4U) /**< \brief (XDMAC) Channel Block Control Register (chid = 6) */
  #define REG_XDMAC_CC6                        (0xF00081F8U) /**< \brief (XDMAC) Channel Configuration Register (chid = 6) */
  #define REG_XDMAC_CDS_MSP6                   (0xF00081FCU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 6) */
  #define REG_XDMAC_CSUS6                      (0xF0008200U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 6) */
  #define REG_XDMAC_CDUS6                      (0xF0008204U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 6) */
  #define REG_XDMAC_CIE7                       (0xF0008210U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 7) */
  #define REG_XDMAC_CID7                       (0xF0008214U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 7) */
  #define REG_XDMAC_CIM7                       (0xF0008218U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 7) */
  #define REG_XDMAC_CIS7                       (0xF000821CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 7) */
  #define REG_XDMAC_CSA7                       (0xF0008220U) /**< \brief (XDMAC) Channel Source Address Register (chid = 7) */
  #define REG_XDMAC_CDA7                       (0xF0008224U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 7) */
  #define REG_XDMAC_CNDA7                      (0xF0008228U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 7) */
  #define REG_XDMAC_CNDC7                      (0xF000822CU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 7) */
  #define REG_XDMAC_CUBC7                      (0xF0008230U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 7) */
  #define REG_XDMAC_CBC7                       (0xF0008234U) /**< \brief (XDMAC) Channel Block Control Register (chid = 7) */
  #define REG_XDMAC_CC7                        (0xF0008238U) /**< \brief (XDMAC) Channel Configuration Register (chid = 7) */
  #define REG_XDMAC_CDS_MSP7                   (0xF000823CU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 7) */
  #define REG_XDMAC_CSUS7                      (0xF0008240U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 7) */
  #define REG_XDMAC_CDUS7                      (0xF0008244U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 7) */
  #define REG_XDMAC_CIE8                       (0xF0008250U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 8) */
  #define REG_XDMAC_CID8                       (0xF0008254U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 8) */
  #define REG_XDMAC_CIM8                       (0xF0008258U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 8) */
  #define REG_XDMAC_CIS8                       (0xF000825CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 8) */
  #define REG_XDMAC_CSA8                       (0xF0008260U) /**< \brief (XDMAC) Channel Source Address Register (chid = 8) */
  #define REG_XDMAC_CDA8                       (0xF0008264U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 8) */
  #define REG_XDMAC_CNDA8                      (0xF0008268U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 8) */
  #define REG_XDMAC_CNDC8                      (0xF000826CU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 8) */
  #define REG_XDMAC_CUBC8                      (0xF0008270U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 8) */
  #define REG_XDMAC_CBC8                       (0xF0008274U) /**< \brief (XDMAC) Channel Block Control Register (chid = 8) */
  #define REG_XDMAC_CC8                        (0xF0008278U) /**< \brief (XDMAC) Channel Configuration Register (chid = 8) */
  #define REG_XDMAC_CDS_MSP8                   (0xF000827CU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 8) */
  #define REG_XDMAC_CSUS8                      (0xF0008280U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 8) */
  #define REG_XDMAC_CDUS8                      (0xF0008284U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 8) */
  #define REG_XDMAC_CIE9                       (0xF0008290U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 9) */
  #define REG_XDMAC_CID9                       (0xF0008294U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 9) */
  #define REG_XDMAC_CIM9                       (0xF0008298U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 9) */
  #define REG_XDMAC_CIS9                       (0xF000829CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 9) */
  #define REG_XDMAC_CSA9                       (0xF00082A0U) /**< \brief (XDMAC) Channel Source Address Register (chid = 9) */
  #define REG_XDMAC_CDA9                       (0xF00082A4U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 9) */
  #define REG_XDMAC_CNDA9                      (0xF00082A8U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 9) */
  #define REG_XDMAC_CNDC9                      (0xF00082ACU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 9) */
  #define REG_XDMAC_CUBC9                      (0xF00082B0U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 9) */
  #define REG_XDMAC_CBC9                       (0xF00082B4U) /**< \brief (XDMAC) Channel Block Control Register (chid = 9) */
  #define REG_XDMAC_CC9                        (0xF00082B8U) /**< \brief (XDMAC) Channel Configuration Register (chid = 9) */
  #define REG_XDMAC_CDS_MSP9                   (0xF00082BCU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 9) */
  #define REG_XDMAC_CSUS9                      (0xF00082C0U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 9) */
  #define REG_XDMAC_CDUS9                      (0xF00082C4U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 9) */
  #define REG_XDMAC_CIE10                      (0xF00082D0U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 10) */
  #define REG_XDMAC_CID10                      (0xF00082D4U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 10) */
  #define REG_XDMAC_CIM10                      (0xF00082D8U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 10) */
  #define REG_XDMAC_CIS10                      (0xF00082DCU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 10) */
  #define REG_XDMAC_CSA10                      (0xF00082E0U) /**< \brief (XDMAC) Channel Source Address Register (chid = 10) */
  #define REG_XDMAC_CDA10                      (0xF00082E4U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 10) */
  #define REG_XDMAC_CNDA10                     (0xF00082E8U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 10) */
  #define REG_XDMAC_CNDC10                     (0xF00082ECU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 10) */
  #define REG_XDMAC_CUBC10                     (0xF00082F0U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 10) */
  #define REG_XDMAC_CBC10                      (0xF00082F4U) /**< \brief (XDMAC) Channel Block Control Register (chid = 10) */
  #define REG_XDMAC_CC10                       (0xF00082F8U) /**< \brief (XDMAC) Channel Configuration Register (chid = 10) */
  #define REG_XDMAC_CDS_MSP10                  (0xF00082FCU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 10) */
  #define REG_XDMAC_CSUS10                     (0xF0008300U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 10) */
  #define REG_XDMAC_CDUS10                     (0xF0008304U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 10) */
  #define REG_XDMAC_CIE11                      (0xF0008310U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 11) */
  #define REG_XDMAC_CID11                      (0xF0008314U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 11) */
  #define REG_XDMAC_CIM11                      (0xF0008318U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 11) */
  #define REG_XDMAC_CIS11                      (0xF000831CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 11) */
  #define REG_XDMAC_CSA11                      (0xF0008320U) /**< \brief (XDMAC) Channel Source Address Register (chid = 11) */
  #define REG_XDMAC_CDA11                      (0xF0008324U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 11) */
  #define REG_XDMAC_CNDA11                     (0xF0008328U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 11) */
  #define REG_XDMAC_CNDC11                     (0xF000832CU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 11) */
  #define REG_XDMAC_CUBC11                     (0xF0008330U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 11) */
  #define REG_XDMAC_CBC11                      (0xF0008334U) /**< \brief (XDMAC) Channel Block Control Register (chid = 11) */
  #define REG_XDMAC_CC11                       (0xF0008338U) /**< \brief (XDMAC) Channel Configuration Register (chid = 11) */
  #define REG_XDMAC_CDS_MSP11                  (0xF000833CU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 11) */
  #define REG_XDMAC_CSUS11                     (0xF0008340U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 11) */
  #define REG_XDMAC_CDUS11                     (0xF0008344U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 11) */
  #define REG_XDMAC_CIE12                      (0xF0008350U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 12) */
  #define REG_XDMAC_CID12                      (0xF0008354U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 12) */
  #define REG_XDMAC_CIM12                      (0xF0008358U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 12) */
  #define REG_XDMAC_CIS12                      (0xF000835CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 12) */
  #define REG_XDMAC_CSA12                      (0xF0008360U) /**< \brief (XDMAC) Channel Source Address Register (chid = 12) */
  #define REG_XDMAC_CDA12                      (0xF0008364U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 12) */
  #define REG_XDMAC_CNDA12                     (0xF0008368U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 12) */
  #define REG_XDMAC_CNDC12                     (0xF000836CU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 12) */
  #define REG_XDMAC_CUBC12                     (0xF0008370U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 12) */
  #define REG_XDMAC_CBC12                      (0xF0008374U) /**< \brief (XDMAC) Channel Block Control Register (chid = 12) */
  #define REG_XDMAC_CC12                       (0xF0008378U) /**< \brief (XDMAC) Channel Configuration Register (chid = 12) */
  #define REG_XDMAC_CDS_MSP12                  (0xF000837CU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 12) */
  #define REG_XDMAC_CSUS12                     (0xF0008380U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 12) */
  #define REG_XDMAC_CDUS12                     (0xF0008384U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 12) */
  #define REG_XDMAC_CIE13                      (0xF0008390U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 13) */
  #define REG_XDMAC_CID13                      (0xF0008394U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 13) */
  #define REG_XDMAC_CIM13                      (0xF0008398U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 13) */
  #define REG_XDMAC_CIS13                      (0xF000839CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 13) */
  #define REG_XDMAC_CSA13                      (0xF00083A0U) /**< \brief (XDMAC) Channel Source Address Register (chid = 13) */
  #define REG_XDMAC_CDA13                      (0xF00083A4U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 13) */
  #define REG_XDMAC_CNDA13                     (0xF00083A8U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 13) */
  #define REG_XDMAC_CNDC13                     (0xF00083ACU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 13) */
  #define REG_XDMAC_CUBC13                     (0xF00083B0U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 13) */
  #define REG_XDMAC_CBC13                      (0xF00083B4U) /**< \brief (XDMAC) Channel Block Control Register (chid = 13) */
  #define REG_XDMAC_CC13                       (0xF00083B8U) /**< \brief (XDMAC) Channel Configuration Register (chid = 13) */
  #define REG_XDMAC_CDS_MSP13                  (0xF00083BCU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 13) */
  #define REG_XDMAC_CSUS13                     (0xF00083C0U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 13) */
  #define REG_XDMAC_CDUS13                     (0xF00083C4U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 13) */
  #define REG_XDMAC_CIE14                      (0xF00083D0U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 14) */
  #define REG_XDMAC_CID14                      (0xF00083D4U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 14) */
  #define REG_XDMAC_CIM14                      (0xF00083D8U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 14) */
  #define REG_XDMAC_CIS14                      (0xF00083DCU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 14) */
  #define REG_XDMAC_CSA14                      (0xF00083E0U) /**< \brief (XDMAC) Channel Source Address Register (chid = 14) */
  #define REG_XDMAC_CDA14                      (0xF00083E4U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 14) */
  #define REG_XDMAC_CNDA14                     (0xF00083E8U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 14) */
  #define REG_XDMAC_CNDC14                     (0xF00083ECU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 14) */
  #define REG_XDMAC_CUBC14                     (0xF00083F0U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 14) */
  #define REG_XDMAC_CBC14                      (0xF00083F4U) /**< \brief (XDMAC) Channel Block Control Register (chid = 14) */
  #define REG_XDMAC_CC14                       (0xF00083F8U) /**< \brief (XDMAC) Channel Configuration Register (chid = 14) */
  #define REG_XDMAC_CDS_MSP14                  (0xF00083FCU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 14) */
  #define REG_XDMAC_CSUS14                     (0xF0008400U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 14) */
  #define REG_XDMAC_CDUS14                     (0xF0008404U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 14) */
  #define REG_XDMAC_CIE15                      (0xF0008410U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 15) */
  #define REG_XDMAC_CID15                      (0xF0008414U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 15) */
  #define REG_XDMAC_CIM15                      (0xF0008418U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 15) */
  #define REG_XDMAC_CIS15                      (0xF000841CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 15) */
  #define REG_XDMAC_CSA15                      (0xF0008420U) /**< \brief (XDMAC) Channel Source Address Register (chid = 15) */
  #define REG_XDMAC_CDA15                      (0xF0008424U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 15) */
  #define REG_XDMAC_CNDA15                     (0xF0008428U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 15) */
  #define REG_XDMAC_CNDC15                     (0xF000842CU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 15) */
  #define REG_XDMAC_CUBC15                     (0xF0008430U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 15) */
  #define REG_XDMAC_CBC15                      (0xF0008434U) /**< \brief (XDMAC) Channel Block Control Register (chid = 15) */
  #define REG_XDMAC_CC15                       (0xF0008438U) /**< \brief (XDMAC) Channel Configuration Register (chid = 15) */
  #define REG_XDMAC_CDS_MSP15                  (0xF000843CU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 15) */
  #define REG_XDMAC_CSUS15                     (0xF0008440U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 15) */
  #define REG_XDMAC_CDUS15                     (0xF0008444U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 15) */
#else
  #define REG_XDMAC_GTYPE     (*(__I  uint32_t*)0xF0008000U) /**< \brief (XDMAC) Global Type Register */
  #define REG_XDMAC_GCFG      (*(__IO uint32_t*)0xF0008004U) /**< \brief (XDMAC) Global Configuration Register */
  #define REG_XDMAC_GWAC      (*(__IO uint32_t*)0xF0008008U) /**< \brief (XDMAC) Global Weighted Arbiter Configuration Register */
  #define REG_XDMAC_GIE       (*(__O  uint32_t*)0xF000800CU) /**< \brief (XDMAC) Global Interrupt Enable Register */
  #define REG_XDMAC_GID       (*(__O  uint32_t*)0xF0008010U) /**< \brief (XDMAC) Global Interrupt Disable Register */
  #define REG_XDMAC_GIM       (*(__I  uint32_t*)0xF0008014U) /**< \brief (XDMAC) Global Interrupt Mask Register */
  #define REG_XDMAC_GIS       (*(__I  uint32_t*)0xF0008018U) /**< \brief (XDMAC) Global Interrupt Status Register */
  #define REG_XDMAC_GE        (*(__O  uint32_t*)0xF000801CU) /**< \brief (XDMAC) Global Channel Enable Register */
  #define REG_XDMAC_GD        (*(__O  uint32_t*)0xF0008020U) /**< \brief (XDMAC) Global Channel Disable Register */
  #define REG_XDMAC_GS        (*(__I  uint32_t*)0xF0008024U) /**< \brief (XDMAC) Global Channel Status Register */
  #define REG_XDMAC_GRS       (*(__IO uint32_t*)0xF0008028U) /**< \brief (XDMAC) Global Channel Read Suspend Register */
  #define REG_XDMAC_GWS       (*(__IO uint32_t*)0xF000802CU) /**< \brief (XDMAC) Global Channel Write Suspend Register */
  #define REG_XDMAC_GRWS      (*(__O  uint32_t*)0xF0008030U) /**< \brief (XDMAC) Global Channel Read Write Suspend Register */
  #define REG_XDMAC_GRWR      (*(__O  uint32_t*)0xF0008034U) /**< \brief (XDMAC) Global Channel Read Write Resume Register */
  #define REG_XDMAC_GSWR      (*(__O  uint32_t*)0xF0008038U) /**< \brief (XDMAC) Global Channel Software Request Register */
  #define REG_XDMAC_GSWS      (*(__I  uint32_t*)0xF000803CU) /**< \brief (XDMAC) Global Channel Software Request Status Register */
  #define REG_XDMAC_GSWF      (*(__O  uint32_t*)0xF0008040U) /**< \brief (XDMAC) Global Channel Software Flush Request Register */
  #define REG_XDMAC_CIE0      (*(__O  uint32_t*)0xF0008050U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 0) */
  #define REG_XDMAC_CID0      (*(__O  uint32_t*)0xF0008054U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 0) */
  #define REG_XDMAC_CIM0      (*(__I  uint32_t*)0xF0008058U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 0) */
  #define REG_XDMAC_CIS0      (*(__I  uint32_t*)0xF000805CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 0) */
  #define REG_XDMAC_CSA0      (*(__IO uint32_t*)0xF0008060U) /**< \brief (XDMAC) Channel Source Address Register (chid = 0) */
  #define REG_XDMAC_CDA0      (*(__IO uint32_t*)0xF0008064U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 0) */
  #define REG_XDMAC_CNDA0     (*(__IO uint32_t*)0xF0008068U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 0) */
  #define REG_XDMAC_CNDC0     (*(__IO uint32_t*)0xF000806CU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 0) */
  #define REG_XDMAC_CUBC0     (*(__IO uint32_t*)0xF0008070U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 0) */
  #define REG_XDMAC_CBC0      (*(__IO uint32_t*)0xF0008074U) /**< \brief (XDMAC) Channel Block Control Register (chid = 0) */
  #define REG_XDMAC_CC0       (*(__IO uint32_t*)0xF0008078U) /**< \brief (XDMAC) Channel Configuration Register (chid = 0) */
  #define REG_XDMAC_CDS_MSP0  (*(__IO uint32_t*)0xF000807CU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 0) */
  #define REG_XDMAC_CSUS0     (*(__IO uint32_t*)0xF0008080U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 0) */
  #define REG_XDMAC_CDUS0     (*(__IO uint32_t*)0xF0008084U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 0) */
  #define REG_XDMAC_CIE1      (*(__O  uint32_t*)0xF0008090U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 1) */
  #define REG_XDMAC_CID1      (*(__O  uint32_t*)0xF0008094U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 1) */
  #define REG_XDMAC_CIM1      (*(__I  uint32_t*)0xF0008098U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 1) */
  #define REG_XDMAC_CIS1      (*(__I  uint32_t*)0xF000809CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 1) */
  #define REG_XDMAC_CSA1      (*(__IO uint32_t*)0xF00080A0U) /**< \brief (XDMAC) Channel Source Address Register (chid = 1) */
  #define REG_XDMAC_CDA1      (*(__IO uint32_t*)0xF00080A4U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 1) */
  #define REG_XDMAC_CNDA1     (*(__IO uint32_t*)0xF00080A8U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 1) */
  #define REG_XDMAC_CNDC1     (*(__IO uint32_t*)0xF00080ACU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 1) */
  #define REG_XDMAC_CUBC1     (*(__IO uint32_t*)0xF00080B0U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 1) */
  #define REG_XDMAC_CBC1      (*(__IO uint32_t*)0xF00080B4U) /**< \brief (XDMAC) Channel Block Control Register (chid = 1) */
  #define REG_XDMAC_CC1       (*(__IO uint32_t*)0xF00080B8U) /**< \brief (XDMAC) Channel Configuration Register (chid = 1) */
  #define REG_XDMAC_CDS_MSP1  (*(__IO uint32_t*)0xF00080BCU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 1) */
  #define REG_XDMAC_CSUS1     (*(__IO uint32_t*)0xF00080C0U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 1) */
  #define REG_XDMAC_CDUS1     (*(__IO uint32_t*)0xF00080C4U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 1) */
  #define REG_XDMAC_CIE2      (*(__O  uint32_t*)0xF00080D0U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 2) */
  #define REG_XDMAC_CID2      (*(__O  uint32_t*)0xF00080D4U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 2) */
  #define REG_XDMAC_CIM2      (*(__I  uint32_t*)0xF00080D8U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 2) */
  #define REG_XDMAC_CIS2      (*(__I  uint32_t*)0xF00080DCU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 2) */
  #define REG_XDMAC_CSA2      (*(__IO uint32_t*)0xF00080E0U) /**< \brief (XDMAC) Channel Source Address Register (chid = 2) */
  #define REG_XDMAC_CDA2      (*(__IO uint32_t*)0xF00080E4U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 2) */
  #define REG_XDMAC_CNDA2     (*(__IO uint32_t*)0xF00080E8U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 2) */
  #define REG_XDMAC_CNDC2     (*(__IO uint32_t*)0xF00080ECU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 2) */
  #define REG_XDMAC_CUBC2     (*(__IO uint32_t*)0xF00080F0U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 2) */
  #define REG_XDMAC_CBC2      (*(__IO uint32_t*)0xF00080F4U) /**< \brief (XDMAC) Channel Block Control Register (chid = 2) */
  #define REG_XDMAC_CC2       (*(__IO uint32_t*)0xF00080F8U) /**< \brief (XDMAC) Channel Configuration Register (chid = 2) */
  #define REG_XDMAC_CDS_MSP2  (*(__IO uint32_t*)0xF00080FCU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 2) */
  #define REG_XDMAC_CSUS2     (*(__IO uint32_t*)0xF0008100U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 2) */
  #define REG_XDMAC_CDUS2     (*(__IO uint32_t*)0xF0008104U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 2) */
  #define REG_XDMAC_CIE3      (*(__O  uint32_t*)0xF0008110U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 3) */
  #define REG_XDMAC_CID3      (*(__O  uint32_t*)0xF0008114U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 3) */
  #define REG_XDMAC_CIM3      (*(__I  uint32_t*)0xF0008118U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 3) */
  #define REG_XDMAC_CIS3      (*(__I  uint32_t*)0xF000811CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 3) */
  #define REG_XDMAC_CSA3      (*(__IO uint32_t*)0xF0008120U) /**< \brief (XDMAC) Channel Source Address Register (chid = 3) */
  #define REG_XDMAC_CDA3      (*(__IO uint32_t*)0xF0008124U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 3) */
  #define REG_XDMAC_CNDA3     (*(__IO uint32_t*)0xF0008128U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 3) */
  #define REG_XDMAC_CNDC3     (*(__IO uint32_t*)0xF000812CU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 3) */
  #define REG_XDMAC_CUBC3     (*(__IO uint32_t*)0xF0008130U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 3) */
  #define REG_XDMAC_CBC3      (*(__IO uint32_t*)0xF0008134U) /**< \brief (XDMAC) Channel Block Control Register (chid = 3) */
  #define REG_XDMAC_CC3       (*(__IO uint32_t*)0xF0008138U) /**< \brief (XDMAC) Channel Configuration Register (chid = 3) */
  #define REG_XDMAC_CDS_MSP3  (*(__IO uint32_t*)0xF000813CU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 3) */
  #define REG_XDMAC_CSUS3     (*(__IO uint32_t*)0xF0008140U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 3) */
  #define REG_XDMAC_CDUS3     (*(__IO uint32_t*)0xF0008144U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 3) */
  #define REG_XDMAC_CIE4      (*(__O  uint32_t*)0xF0008150U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 4) */
  #define REG_XDMAC_CID4      (*(__O  uint32_t*)0xF0008154U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 4) */
  #define REG_XDMAC_CIM4      (*(__I  uint32_t*)0xF0008158U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 4) */
  #define REG_XDMAC_CIS4      (*(__I  uint32_t*)0xF000815CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 4) */
  #define REG_XDMAC_CSA4      (*(__IO uint32_t*)0xF0008160U) /**< \brief (XDMAC) Channel Source Address Register (chid = 4) */
  #define REG_XDMAC_CDA4      (*(__IO uint32_t*)0xF0008164U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 4) */
  #define REG_XDMAC_CNDA4     (*(__IO uint32_t*)0xF0008168U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 4) */
  #define REG_XDMAC_CNDC4     (*(__IO uint32_t*)0xF000816CU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 4) */
  #define REG_XDMAC_CUBC4     (*(__IO uint32_t*)0xF0008170U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 4) */
  #define REG_XDMAC_CBC4      (*(__IO uint32_t*)0xF0008174U) /**< \brief (XDMAC) Channel Block Control Register (chid = 4) */
  #define REG_XDMAC_CC4       (*(__IO uint32_t*)0xF0008178U) /**< \brief (XDMAC) Channel Configuration Register (chid = 4) */
  #define REG_XDMAC_CDS_MSP4  (*(__IO uint32_t*)0xF000817CU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 4) */
  #define REG_XDMAC_CSUS4     (*(__IO uint32_t*)0xF0008180U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 4) */
  #define REG_XDMAC_CDUS4     (*(__IO uint32_t*)0xF0008184U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 4) */
  #define REG_XDMAC_CIE5      (*(__O  uint32_t*)0xF0008190U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 5) */
  #define REG_XDMAC_CID5      (*(__O  uint32_t*)0xF0008194U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 5) */
  #define REG_XDMAC_CIM5      (*(__I  uint32_t*)0xF0008198U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 5) */
  #define REG_XDMAC_CIS5      (*(__I  uint32_t*)0xF000819CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 5) */
  #define REG_XDMAC_CSA5      (*(__IO uint32_t*)0xF00081A0U) /**< \brief (XDMAC) Channel Source Address Register (chid = 5) */
  #define REG_XDMAC_CDA5      (*(__IO uint32_t*)0xF00081A4U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 5) */
  #define REG_XDMAC_CNDA5     (*(__IO uint32_t*)0xF00081A8U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 5) */
  #define REG_XDMAC_CNDC5     (*(__IO uint32_t*)0xF00081ACU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 5) */
  #define REG_XDMAC_CUBC5     (*(__IO uint32_t*)0xF00081B0U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 5) */
  #define REG_XDMAC_CBC5      (*(__IO uint32_t*)0xF00081B4U) /**< \brief (XDMAC) Channel Block Control Register (chid = 5) */
  #define REG_XDMAC_CC5       (*(__IO uint32_t*)0xF00081B8U) /**< \brief (XDMAC) Channel Configuration Register (chid = 5) */
  #define REG_XDMAC_CDS_MSP5  (*(__IO uint32_t*)0xF00081BCU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 5) */
  #define REG_XDMAC_CSUS5     (*(__IO uint32_t*)0xF00081C0U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 5) */
  #define REG_XDMAC_CDUS5     (*(__IO uint32_t*)0xF00081C4U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 5) */
  #define REG_XDMAC_CIE6      (*(__O  uint32_t*)0xF00081D0U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 6) */
  #define REG_XDMAC_CID6      (*(__O  uint32_t*)0xF00081D4U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 6) */
  #define REG_XDMAC_CIM6      (*(__I  uint32_t*)0xF00081D8U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 6) */
  #define REG_XDMAC_CIS6      (*(__I  uint32_t*)0xF00081DCU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 6) */
  #define REG_XDMAC_CSA6      (*(__IO uint32_t*)0xF00081E0U) /**< \brief (XDMAC) Channel Source Address Register (chid = 6) */
  #define REG_XDMAC_CDA6      (*(__IO uint32_t*)0xF00081E4U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 6) */
  #define REG_XDMAC_CNDA6     (*(__IO uint32_t*)0xF00081E8U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 6) */
  #define REG_XDMAC_CNDC6     (*(__IO uint32_t*)0xF00081ECU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 6) */
  #define REG_XDMAC_CUBC6     (*(__IO uint32_t*)0xF00081F0U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 6) */
  #define REG_XDMAC_CBC6      (*(__IO uint32_t*)0xF00081F4U) /**< \brief (XDMAC) Channel Block Control Register (chid = 6) */
  #define REG_XDMAC_CC6       (*(__IO uint32_t*)0xF00081F8U) /**< \brief (XDMAC) Channel Configuration Register (chid = 6) */
  #define REG_XDMAC_CDS_MSP6  (*(__IO uint32_t*)0xF00081FCU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 6) */
  #define REG_XDMAC_CSUS6     (*(__IO uint32_t*)0xF0008200U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 6) */
  #define REG_XDMAC_CDUS6     (*(__IO uint32_t*)0xF0008204U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 6) */
  #define REG_XDMAC_CIE7      (*(__O  uint32_t*)0xF0008210U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 7) */
  #define REG_XDMAC_CID7      (*(__O  uint32_t*)0xF0008214U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 7) */
  #define REG_XDMAC_CIM7      (*(__I  uint32_t*)0xF0008218U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 7) */
  #define REG_XDMAC_CIS7      (*(__I  uint32_t*)0xF000821CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 7) */
  #define REG_XDMAC_CSA7      (*(__IO uint32_t*)0xF0008220U) /**< \brief (XDMAC) Channel Source Address Register (chid = 7) */
  #define REG_XDMAC_CDA7      (*(__IO uint32_t*)0xF0008224U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 7) */
  #define REG_XDMAC_CNDA7     (*(__IO uint32_t*)0xF0008228U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 7) */
  #define REG_XDMAC_CNDC7     (*(__IO uint32_t*)0xF000822CU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 7) */
  #define REG_XDMAC_CUBC7     (*(__IO uint32_t*)0xF0008230U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 7) */
  #define REG_XDMAC_CBC7      (*(__IO uint32_t*)0xF0008234U) /**< \brief (XDMAC) Channel Block Control Register (chid = 7) */
  #define REG_XDMAC_CC7       (*(__IO uint32_t*)0xF0008238U) /**< \brief (XDMAC) Channel Configuration Register (chid = 7) */
  #define REG_XDMAC_CDS_MSP7  (*(__IO uint32_t*)0xF000823CU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 7) */
  #define REG_XDMAC_CSUS7     (*(__IO uint32_t*)0xF0008240U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 7) */
  #define REG_XDMAC_CDUS7     (*(__IO uint32_t*)0xF0008244U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 7) */
  #define REG_XDMAC_CIE8      (*(__O  uint32_t*)0xF0008250U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 8) */
  #define REG_XDMAC_CID8      (*(__O  uint32_t*)0xF0008254U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 8) */
  #define REG_XDMAC_CIM8      (*(__I  uint32_t*)0xF0008258U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 8) */
  #define REG_XDMAC_CIS8      (*(__I  uint32_t*)0xF000825CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 8) */
  #define REG_XDMAC_CSA8      (*(__IO uint32_t*)0xF0008260U) /**< \brief (XDMAC) Channel Source Address Register (chid = 8) */
  #define REG_XDMAC_CDA8      (*(__IO uint32_t*)0xF0008264U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 8) */
  #define REG_XDMAC_CNDA8     (*(__IO uint32_t*)0xF0008268U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 8) */
  #define REG_XDMAC_CNDC8     (*(__IO uint32_t*)0xF000826CU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 8) */
  #define REG_XDMAC_CUBC8     (*(__IO uint32_t*)0xF0008270U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 8) */
  #define REG_XDMAC_CBC8      (*(__IO uint32_t*)0xF0008274U) /**< \brief (XDMAC) Channel Block Control Register (chid = 8) */
  #define REG_XDMAC_CC8       (*(__IO uint32_t*)0xF0008278U) /**< \brief (XDMAC) Channel Configuration Register (chid = 8) */
  #define REG_XDMAC_CDS_MSP8  (*(__IO uint32_t*)0xF000827CU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 8) */
  #define REG_XDMAC_CSUS8     (*(__IO uint32_t*)0xF0008280U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 8) */
  #define REG_XDMAC_CDUS8     (*(__IO uint32_t*)0xF0008284U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 8) */
  #define REG_XDMAC_CIE9      (*(__O  uint32_t*)0xF0008290U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 9) */
  #define REG_XDMAC_CID9      (*(__O  uint32_t*)0xF0008294U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 9) */
  #define REG_XDMAC_CIM9      (*(__I  uint32_t*)0xF0008298U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 9) */
  #define REG_XDMAC_CIS9      (*(__I  uint32_t*)0xF000829CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 9) */
  #define REG_XDMAC_CSA9      (*(__IO uint32_t*)0xF00082A0U) /**< \brief (XDMAC) Channel Source Address Register (chid = 9) */
  #define REG_XDMAC_CDA9      (*(__IO uint32_t*)0xF00082A4U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 9) */
  #define REG_XDMAC_CNDA9     (*(__IO uint32_t*)0xF00082A8U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 9) */
  #define REG_XDMAC_CNDC9     (*(__IO uint32_t*)0xF00082ACU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 9) */
  #define REG_XDMAC_CUBC9     (*(__IO uint32_t*)0xF00082B0U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 9) */
  #define REG_XDMAC_CBC9      (*(__IO uint32_t*)0xF00082B4U) /**< \brief (XDMAC) Channel Block Control Register (chid = 9) */
  #define REG_XDMAC_CC9       (*(__IO uint32_t*)0xF00082B8U) /**< \brief (XDMAC) Channel Configuration Register (chid = 9) */
  #define REG_XDMAC_CDS_MSP9  (*(__IO uint32_t*)0xF00082BCU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 9) */
  #define REG_XDMAC_CSUS9     (*(__IO uint32_t*)0xF00082C0U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 9) */
  #define REG_XDMAC_CDUS9     (*(__IO uint32_t*)0xF00082C4U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 9) */
  #define REG_XDMAC_CIE10     (*(__O  uint32_t*)0xF00082D0U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 10) */
  #define REG_XDMAC_CID10     (*(__O  uint32_t*)0xF00082D4U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 10) */
  #define REG_XDMAC_CIM10     (*(__I  uint32_t*)0xF00082D8U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 10) */
  #define REG_XDMAC_CIS10     (*(__I  uint32_t*)0xF00082DCU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 10) */
  #define REG_XDMAC_CSA10     (*(__IO uint32_t*)0xF00082E0U) /**< \brief (XDMAC) Channel Source Address Register (chid = 10) */
  #define REG_XDMAC_CDA10     (*(__IO uint32_t*)0xF00082E4U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 10) */
  #define REG_XDMAC_CNDA10    (*(__IO uint32_t*)0xF00082E8U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 10) */
  #define REG_XDMAC_CNDC10    (*(__IO uint32_t*)0xF00082ECU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 10) */
  #define REG_XDMAC_CUBC10    (*(__IO uint32_t*)0xF00082F0U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 10) */
  #define REG_XDMAC_CBC10     (*(__IO uint32_t*)0xF00082F4U) /**< \brief (XDMAC) Channel Block Control Register (chid = 10) */
  #define REG_XDMAC_CC10      (*(__IO uint32_t*)0xF00082F8U) /**< \brief (XDMAC) Channel Configuration Register (chid = 10) */
  #define REG_XDMAC_CDS_MSP10 (*(__IO uint32_t*)0xF00082FCU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 10) */
  #define REG_XDMAC_CSUS10    (*(__IO uint32_t*)0xF0008300U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 10) */
  #define REG_XDMAC_CDUS10    (*(__IO uint32_t*)0xF0008304U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 10) */
  #define REG_XDMAC_CIE11     (*(__O  uint32_t*)0xF0008310U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 11) */
  #define REG_XDMAC_CID11     (*(__O  uint32_t*)0xF0008314U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 11) */
  #define REG_XDMAC_CIM11     (*(__I  uint32_t*)0xF0008318U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 11) */
  #define REG_XDMAC_CIS11     (*(__I  uint32_t*)0xF000831CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 11) */
  #define REG_XDMAC_CSA11     (*(__IO uint32_t*)0xF0008320U) /**< \brief (XDMAC) Channel Source Address Register (chid = 11) */
  #define REG_XDMAC_CDA11     (*(__IO uint32_t*)0xF0008324U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 11) */
  #define REG_XDMAC_CNDA11    (*(__IO uint32_t*)0xF0008328U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 11) */
  #define REG_XDMAC_CNDC11    (*(__IO uint32_t*)0xF000832CU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 11) */
  #define REG_XDMAC_CUBC11    (*(__IO uint32_t*)0xF0008330U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 11) */
  #define REG_XDMAC_CBC11     (*(__IO uint32_t*)0xF0008334U) /**< \brief (XDMAC) Channel Block Control Register (chid = 11) */
  #define REG_XDMAC_CC11      (*(__IO uint32_t*)0xF0008338U) /**< \brief (XDMAC) Channel Configuration Register (chid = 11) */
  #define REG_XDMAC_CDS_MSP11 (*(__IO uint32_t*)0xF000833CU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 11) */
  #define REG_XDMAC_CSUS11    (*(__IO uint32_t*)0xF0008340U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 11) */
  #define REG_XDMAC_CDUS11    (*(__IO uint32_t*)0xF0008344U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 11) */
  #define REG_XDMAC_CIE12     (*(__O  uint32_t*)0xF0008350U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 12) */
  #define REG_XDMAC_CID12     (*(__O  uint32_t*)0xF0008354U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 12) */
  #define REG_XDMAC_CIM12     (*(__I  uint32_t*)0xF0008358U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 12) */
  #define REG_XDMAC_CIS12     (*(__I  uint32_t*)0xF000835CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 12) */
  #define REG_XDMAC_CSA12     (*(__IO uint32_t*)0xF0008360U) /**< \brief (XDMAC) Channel Source Address Register (chid = 12) */
  #define REG_XDMAC_CDA12     (*(__IO uint32_t*)0xF0008364U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 12) */
  #define REG_XDMAC_CNDA12    (*(__IO uint32_t*)0xF0008368U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 12) */
  #define REG_XDMAC_CNDC12    (*(__IO uint32_t*)0xF000836CU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 12) */
  #define REG_XDMAC_CUBC12    (*(__IO uint32_t*)0xF0008370U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 12) */
  #define REG_XDMAC_CBC12     (*(__IO uint32_t*)0xF0008374U) /**< \brief (XDMAC) Channel Block Control Register (chid = 12) */
  #define REG_XDMAC_CC12      (*(__IO uint32_t*)0xF0008378U) /**< \brief (XDMAC) Channel Configuration Register (chid = 12) */
  #define REG_XDMAC_CDS_MSP12 (*(__IO uint32_t*)0xF000837CU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 12) */
  #define REG_XDMAC_CSUS12    (*(__IO uint32_t*)0xF0008380U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 12) */
  #define REG_XDMAC_CDUS12    (*(__IO uint32_t*)0xF0008384U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 12) */
  #define REG_XDMAC_CIE13     (*(__O  uint32_t*)0xF0008390U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 13) */
  #define REG_XDMAC_CID13     (*(__O  uint32_t*)0xF0008394U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 13) */
  #define REG_XDMAC_CIM13     (*(__I  uint32_t*)0xF0008398U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 13) */
  #define REG_XDMAC_CIS13     (*(__I  uint32_t*)0xF000839CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 13) */
  #define REG_XDMAC_CSA13     (*(__IO uint32_t*)0xF00083A0U) /**< \brief (XDMAC) Channel Source Address Register (chid = 13) */
  #define REG_XDMAC_CDA13     (*(__IO uint32_t*)0xF00083A4U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 13) */
  #define REG_XDMAC_CNDA13    (*(__IO uint32_t*)0xF00083A8U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 13) */
  #define REG_XDMAC_CNDC13    (*(__IO uint32_t*)0xF00083ACU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 13) */
  #define REG_XDMAC_CUBC13    (*(__IO uint32_t*)0xF00083B0U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 13) */
  #define REG_XDMAC_CBC13     (*(__IO uint32_t*)0xF00083B4U) /**< \brief (XDMAC) Channel Block Control Register (chid = 13) */
  #define REG_XDMAC_CC13      (*(__IO uint32_t*)0xF00083B8U) /**< \brief (XDMAC) Channel Configuration Register (chid = 13) */
  #define REG_XDMAC_CDS_MSP13 (*(__IO uint32_t*)0xF00083BCU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 13) */
  #define REG_XDMAC_CSUS13    (*(__IO uint32_t*)0xF00083C0U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 13) */
  #define REG_XDMAC_CDUS13    (*(__IO uint32_t*)0xF00083C4U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 13) */
  #define REG_XDMAC_CIE14     (*(__O  uint32_t*)0xF00083D0U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 14) */
  #define REG_XDMAC_CID14     (*(__O  uint32_t*)0xF00083D4U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 14) */
  #define REG_XDMAC_CIM14     (*(__I  uint32_t*)0xF00083D8U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 14) */
  #define REG_XDMAC_CIS14     (*(__I  uint32_t*)0xF00083DCU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 14) */
  #define REG_XDMAC_CSA14     (*(__IO uint32_t*)0xF00083E0U) /**< \brief (XDMAC) Channel Source Address Register (chid = 14) */
  #define REG_XDMAC_CDA14     (*(__IO uint32_t*)0xF00083E4U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 14) */
  #define REG_XDMAC_CNDA14    (*(__IO uint32_t*)0xF00083E8U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 14) */
  #define REG_XDMAC_CNDC14    (*(__IO uint32_t*)0xF00083ECU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 14) */
  #define REG_XDMAC_CUBC14    (*(__IO uint32_t*)0xF00083F0U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 14) */
  #define REG_XDMAC_CBC14     (*(__IO uint32_t*)0xF00083F4U) /**< \brief (XDMAC) Channel Block Control Register (chid = 14) */
  #define REG_XDMAC_CC14      (*(__IO uint32_t*)0xF00083F8U) /**< \brief (XDMAC) Channel Configuration Register (chid = 14) */
  #define REG_XDMAC_CDS_MSP14 (*(__IO uint32_t*)0xF00083FCU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 14) */
  #define REG_XDMAC_CSUS14    (*(__IO uint32_t*)0xF0008400U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 14) */
  #define REG_XDMAC_CDUS14    (*(__IO uint32_t*)0xF0008404U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 14) */
  #define REG_XDMAC_CIE15     (*(__O  uint32_t*)0xF0008410U) /**< \brief (XDMAC) Channel Interrupt Enable Register (chid = 15) */
  #define REG_XDMAC_CID15     (*(__O  uint32_t*)0xF0008414U) /**< \brief (XDMAC) Channel Interrupt Disable Register (chid = 15) */
  #define REG_XDMAC_CIM15     (*(__I  uint32_t*)0xF0008418U) /**< \brief (XDMAC) Channel Interrupt Mask Register (chid = 15) */
  #define REG_XDMAC_CIS15     (*(__I  uint32_t*)0xF000841CU) /**< \brief (XDMAC) Channel Interrupt Status Register (chid = 15) */
  #define REG_XDMAC_CSA15     (*(__IO uint32_t*)0xF0008420U) /**< \brief (XDMAC) Channel Source Address Register (chid = 15) */
  #define REG_XDMAC_CDA15     (*(__IO uint32_t*)0xF0008424U) /**< \brief (XDMAC) Channel Destination Address Register (chid = 15) */
  #define REG_XDMAC_CNDA15    (*(__IO uint32_t*)0xF0008428U) /**< \brief (XDMAC) Channel Next Descriptor Address Register (chid = 15) */
  #define REG_XDMAC_CNDC15    (*(__IO uint32_t*)0xF000842CU) /**< \brief (XDMAC) Channel Next Descriptor Control Register (chid = 15) */
  #define REG_XDMAC_CUBC15    (*(__IO uint32_t*)0xF0008430U) /**< \brief (XDMAC) Channel Microblock Control Register (chid = 15) */
  #define REG_XDMAC_CBC15     (*(__IO uint32_t*)0xF0008434U) /**< \brief (XDMAC) Channel Block Control Register (chid = 15) */
  #define REG_XDMAC_CC15      (*(__IO uint32_t*)0xF0008438U) /**< \brief (XDMAC) Channel Configuration Register (chid = 15) */
  #define REG_XDMAC_CDS_MSP15 (*(__IO uint32_t*)0xF000843CU) /**< \brief (XDMAC) Channel Data Stride Memory Set Pattern (chid = 15) */
  #define REG_XDMAC_CSUS15    (*(__IO uint32_t*)0xF0008440U) /**< \brief (XDMAC) Channel Source Microblock Stride (chid = 15) */
  #define REG_XDMAC_CDUS15    (*(__IO uint32_t*)0xF0008444U) /**< \brief (XDMAC) Channel Destination Microblock Stride (chid = 15) */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_XDMAC_INSTANCE_ */
