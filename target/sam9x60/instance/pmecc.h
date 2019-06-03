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

#ifndef _SAM9X_PMECC_INSTANCE_
#define _SAM9X_PMECC_INSTANCE_

/* ========== Register definition for PMECC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_PMECC_CFG                      (0xFFFFE000U) /**< \brief (PMECC) PMECC Configuration Register */
  #define REG_PMECC_SAREA                    (0xFFFFE004U) /**< \brief (PMECC) PMECC Spare Area Size Register */
  #define REG_PMECC_SADDR                    (0xFFFFE008U) /**< \brief (PMECC) PMECC Start Address Register */
  #define REG_PMECC_EADDR                    (0xFFFFE00CU) /**< \brief (PMECC) PMECC End Address Register */
  #define REG_PMECC_CLK                      (0xFFFFE010U) /**< \brief (PMECC) PMECC Clock Control Register */
  #define REG_PMECC_CTRL                     (0xFFFFE014U) /**< \brief (PMECC) PMECC Control Register */
  #define REG_PMECC_SR                       (0xFFFFE018U) /**< \brief (PMECC) PMECC Status Register */
  #define REG_PMECC_IER                      (0xFFFFE01CU) /**< \brief (PMECC) PMECC Interrupt Enable register */
  #define REG_PMECC_IDR                      (0xFFFFE020U) /**< \brief (PMECC) PMECC Interrupt Disable Register */
  #define REG_PMECC_IMR                      (0xFFFFE024U) /**< \brief (PMECC) PMECC Interrupt Mask Register */
  #define REG_PMECC_ISR                      (0xFFFFE028U) /**< \brief (PMECC) PMECC Interrupt Status Register */
  #define REG_PMECC_ECC0_0                   (0xFFFFE040U) /**< \brief (PMECC) PMECC ECC 0 Register (sec_num = 0) */
  #define REG_PMECC_ECC1_0                   (0xFFFFE044U) /**< \brief (PMECC) PMECC ECC 1 Register (sec_num = 0) */
  #define REG_PMECC_ECC2_0                   (0xFFFFE048U) /**< \brief (PMECC) PMECC ECC 2 Register (sec_num = 0) */
  #define REG_PMECC_ECC3_0                   (0xFFFFE04CU) /**< \brief (PMECC) PMECC ECC 3 Register (sec_num = 0) */
  #define REG_PMECC_ECC4_0                   (0xFFFFE050U) /**< \brief (PMECC) PMECC ECC 4 Register (sec_num = 0) */
  #define REG_PMECC_ECC5_0                   (0xFFFFE054U) /**< \brief (PMECC) PMECC ECC 5 Register (sec_num = 0) */
  #define REG_PMECC_ECC6_0                   (0xFFFFE058U) /**< \brief (PMECC) PMECC ECC 6 Register (sec_num = 0) */
  #define REG_PMECC_ECC7_0                   (0xFFFFE05CU) /**< \brief (PMECC) PMECC ECC 7 Register (sec_num = 0) */
  #define REG_PMECC_ECC8_0                   (0xFFFFE060U) /**< \brief (PMECC) PMECC ECC 8 Register (sec_num = 0) */
  #define REG_PMECC_ECC9_0                   (0xFFFFE064U) /**< \brief (PMECC) PMECC ECC 9 Register (sec_num = 0) */
  #define REG_PMECC_ECC10_0                  (0xFFFFE068U) /**< \brief (PMECC) PMECC ECC 10 Register (sec_num = 0) */
  #define REG_PMECC_ECC0_1                   (0xFFFFE080U) /**< \brief (PMECC) PMECC ECC 0 Register (sec_num = 1) */
  #define REG_PMECC_ECC1_1                   (0xFFFFE084U) /**< \brief (PMECC) PMECC ECC 1 Register (sec_num = 1) */
  #define REG_PMECC_ECC2_1                   (0xFFFFE088U) /**< \brief (PMECC) PMECC ECC 2 Register (sec_num = 1) */
  #define REG_PMECC_ECC3_1                   (0xFFFFE08CU) /**< \brief (PMECC) PMECC ECC 3 Register (sec_num = 1) */
  #define REG_PMECC_ECC4_1                   (0xFFFFE090U) /**< \brief (PMECC) PMECC ECC 4 Register (sec_num = 1) */
  #define REG_PMECC_ECC5_1                   (0xFFFFE094U) /**< \brief (PMECC) PMECC ECC 5 Register (sec_num = 1) */
  #define REG_PMECC_ECC6_1                   (0xFFFFE098U) /**< \brief (PMECC) PMECC ECC 6 Register (sec_num = 1) */
  #define REG_PMECC_ECC7_1                   (0xFFFFE09CU) /**< \brief (PMECC) PMECC ECC 7 Register (sec_num = 1) */
  #define REG_PMECC_ECC8_1                   (0xFFFFE0A0U) /**< \brief (PMECC) PMECC ECC 8 Register (sec_num = 1) */
  #define REG_PMECC_ECC9_1                   (0xFFFFE0A4U) /**< \brief (PMECC) PMECC ECC 9 Register (sec_num = 1) */
  #define REG_PMECC_ECC10_1                  (0xFFFFE0A8U) /**< \brief (PMECC) PMECC ECC 10 Register (sec_num = 1) */
  #define REG_PMECC_ECC0_2                   (0xFFFFE0C0U) /**< \brief (PMECC) PMECC ECC 0 Register (sec_num = 2) */
  #define REG_PMECC_ECC1_2                   (0xFFFFE0C4U) /**< \brief (PMECC) PMECC ECC 1 Register (sec_num = 2) */
  #define REG_PMECC_ECC2_2                   (0xFFFFE0C8U) /**< \brief (PMECC) PMECC ECC 2 Register (sec_num = 2) */
  #define REG_PMECC_ECC3_2                   (0xFFFFE0CCU) /**< \brief (PMECC) PMECC ECC 3 Register (sec_num = 2) */
  #define REG_PMECC_ECC4_2                   (0xFFFFE0D0U) /**< \brief (PMECC) PMECC ECC 4 Register (sec_num = 2) */
  #define REG_PMECC_ECC5_2                   (0xFFFFE0D4U) /**< \brief (PMECC) PMECC ECC 5 Register (sec_num = 2) */
  #define REG_PMECC_ECC6_2                   (0xFFFFE0D8U) /**< \brief (PMECC) PMECC ECC 6 Register (sec_num = 2) */
  #define REG_PMECC_ECC7_2                   (0xFFFFE0DCU) /**< \brief (PMECC) PMECC ECC 7 Register (sec_num = 2) */
  #define REG_PMECC_ECC8_2                   (0xFFFFE0E0U) /**< \brief (PMECC) PMECC ECC 8 Register (sec_num = 2) */
  #define REG_PMECC_ECC9_2                   (0xFFFFE0E4U) /**< \brief (PMECC) PMECC ECC 9 Register (sec_num = 2) */
  #define REG_PMECC_ECC10_2                  (0xFFFFE0E8U) /**< \brief (PMECC) PMECC ECC 10 Register (sec_num = 2) */
  #define REG_PMECC_ECC0_3                   (0xFFFFE100U) /**< \brief (PMECC) PMECC ECC 0 Register (sec_num = 3) */
  #define REG_PMECC_ECC1_3                   (0xFFFFE104U) /**< \brief (PMECC) PMECC ECC 1 Register (sec_num = 3) */
  #define REG_PMECC_ECC2_3                   (0xFFFFE108U) /**< \brief (PMECC) PMECC ECC 2 Register (sec_num = 3) */
  #define REG_PMECC_ECC3_3                   (0xFFFFE10CU) /**< \brief (PMECC) PMECC ECC 3 Register (sec_num = 3) */
  #define REG_PMECC_ECC4_3                   (0xFFFFE110U) /**< \brief (PMECC) PMECC ECC 4 Register (sec_num = 3) */
  #define REG_PMECC_ECC5_3                   (0xFFFFE114U) /**< \brief (PMECC) PMECC ECC 5 Register (sec_num = 3) */
  #define REG_PMECC_ECC6_3                   (0xFFFFE118U) /**< \brief (PMECC) PMECC ECC 6 Register (sec_num = 3) */
  #define REG_PMECC_ECC7_3                   (0xFFFFE11CU) /**< \brief (PMECC) PMECC ECC 7 Register (sec_num = 3) */
  #define REG_PMECC_ECC8_3                   (0xFFFFE120U) /**< \brief (PMECC) PMECC ECC 8 Register (sec_num = 3) */
  #define REG_PMECC_ECC9_3                   (0xFFFFE124U) /**< \brief (PMECC) PMECC ECC 9 Register (sec_num = 3) */
  #define REG_PMECC_ECC10_3                  (0xFFFFE128U) /**< \brief (PMECC) PMECC ECC 10 Register (sec_num = 3) */
  #define REG_PMECC_ECC0_4                   (0xFFFFE140U) /**< \brief (PMECC) PMECC ECC 0 Register (sec_num = 4) */
  #define REG_PMECC_ECC1_4                   (0xFFFFE144U) /**< \brief (PMECC) PMECC ECC 1 Register (sec_num = 4) */
  #define REG_PMECC_ECC2_4                   (0xFFFFE148U) /**< \brief (PMECC) PMECC ECC 2 Register (sec_num = 4) */
  #define REG_PMECC_ECC3_4                   (0xFFFFE14CU) /**< \brief (PMECC) PMECC ECC 3 Register (sec_num = 4) */
  #define REG_PMECC_ECC4_4                   (0xFFFFE150U) /**< \brief (PMECC) PMECC ECC 4 Register (sec_num = 4) */
  #define REG_PMECC_ECC5_4                   (0xFFFFE154U) /**< \brief (PMECC) PMECC ECC 5 Register (sec_num = 4) */
  #define REG_PMECC_ECC6_4                   (0xFFFFE158U) /**< \brief (PMECC) PMECC ECC 6 Register (sec_num = 4) */
  #define REG_PMECC_ECC7_4                   (0xFFFFE15CU) /**< \brief (PMECC) PMECC ECC 7 Register (sec_num = 4) */
  #define REG_PMECC_ECC8_4                   (0xFFFFE160U) /**< \brief (PMECC) PMECC ECC 8 Register (sec_num = 4) */
  #define REG_PMECC_ECC9_4                   (0xFFFFE164U) /**< \brief (PMECC) PMECC ECC 9 Register (sec_num = 4) */
  #define REG_PMECC_ECC10_4                  (0xFFFFE168U) /**< \brief (PMECC) PMECC ECC 10 Register (sec_num = 4) */
  #define REG_PMECC_ECC0_5                   (0xFFFFE180U) /**< \brief (PMECC) PMECC ECC 0 Register (sec_num = 5) */
  #define REG_PMECC_ECC1_5                   (0xFFFFE184U) /**< \brief (PMECC) PMECC ECC 1 Register (sec_num = 5) */
  #define REG_PMECC_ECC2_5                   (0xFFFFE188U) /**< \brief (PMECC) PMECC ECC 2 Register (sec_num = 5) */
  #define REG_PMECC_ECC3_5                   (0xFFFFE18CU) /**< \brief (PMECC) PMECC ECC 3 Register (sec_num = 5) */
  #define REG_PMECC_ECC4_5                   (0xFFFFE190U) /**< \brief (PMECC) PMECC ECC 4 Register (sec_num = 5) */
  #define REG_PMECC_ECC5_5                   (0xFFFFE194U) /**< \brief (PMECC) PMECC ECC 5 Register (sec_num = 5) */
  #define REG_PMECC_ECC6_5                   (0xFFFFE198U) /**< \brief (PMECC) PMECC ECC 6 Register (sec_num = 5) */
  #define REG_PMECC_ECC7_5                   (0xFFFFE19CU) /**< \brief (PMECC) PMECC ECC 7 Register (sec_num = 5) */
  #define REG_PMECC_ECC8_5                   (0xFFFFE1A0U) /**< \brief (PMECC) PMECC ECC 8 Register (sec_num = 5) */
  #define REG_PMECC_ECC9_5                   (0xFFFFE1A4U) /**< \brief (PMECC) PMECC ECC 9 Register (sec_num = 5) */
  #define REG_PMECC_ECC10_5                  (0xFFFFE1A8U) /**< \brief (PMECC) PMECC ECC 10 Register (sec_num = 5) */
  #define REG_PMECC_ECC0_6                   (0xFFFFE1C0U) /**< \brief (PMECC) PMECC ECC 0 Register (sec_num = 6) */
  #define REG_PMECC_ECC1_6                   (0xFFFFE1C4U) /**< \brief (PMECC) PMECC ECC 1 Register (sec_num = 6) */
  #define REG_PMECC_ECC2_6                   (0xFFFFE1C8U) /**< \brief (PMECC) PMECC ECC 2 Register (sec_num = 6) */
  #define REG_PMECC_ECC3_6                   (0xFFFFE1CCU) /**< \brief (PMECC) PMECC ECC 3 Register (sec_num = 6) */
  #define REG_PMECC_ECC4_6                   (0xFFFFE1D0U) /**< \brief (PMECC) PMECC ECC 4 Register (sec_num = 6) */
  #define REG_PMECC_ECC5_6                   (0xFFFFE1D4U) /**< \brief (PMECC) PMECC ECC 5 Register (sec_num = 6) */
  #define REG_PMECC_ECC6_6                   (0xFFFFE1D8U) /**< \brief (PMECC) PMECC ECC 6 Register (sec_num = 6) */
  #define REG_PMECC_ECC7_6                   (0xFFFFE1DCU) /**< \brief (PMECC) PMECC ECC 7 Register (sec_num = 6) */
  #define REG_PMECC_ECC8_6                   (0xFFFFE1E0U) /**< \brief (PMECC) PMECC ECC 8 Register (sec_num = 6) */
  #define REG_PMECC_ECC9_6                   (0xFFFFE1E4U) /**< \brief (PMECC) PMECC ECC 9 Register (sec_num = 6) */
  #define REG_PMECC_ECC10_6                  (0xFFFFE1E8U) /**< \brief (PMECC) PMECC ECC 10 Register (sec_num = 6) */
  #define REG_PMECC_ECC0_7                   (0xFFFFE200U) /**< \brief (PMECC) PMECC ECC 0 Register (sec_num = 7) */
  #define REG_PMECC_ECC1_7                   (0xFFFFE204U) /**< \brief (PMECC) PMECC ECC 1 Register (sec_num = 7) */
  #define REG_PMECC_ECC2_7                   (0xFFFFE208U) /**< \brief (PMECC) PMECC ECC 2 Register (sec_num = 7) */
  #define REG_PMECC_ECC3_7                   (0xFFFFE20CU) /**< \brief (PMECC) PMECC ECC 3 Register (sec_num = 7) */
  #define REG_PMECC_ECC4_7                   (0xFFFFE210U) /**< \brief (PMECC) PMECC ECC 4 Register (sec_num = 7) */
  #define REG_PMECC_ECC5_7                   (0xFFFFE214U) /**< \brief (PMECC) PMECC ECC 5 Register (sec_num = 7) */
  #define REG_PMECC_ECC6_7                   (0xFFFFE218U) /**< \brief (PMECC) PMECC ECC 6 Register (sec_num = 7) */
  #define REG_PMECC_ECC7_7                   (0xFFFFE21CU) /**< \brief (PMECC) PMECC ECC 7 Register (sec_num = 7) */
  #define REG_PMECC_ECC8_7                   (0xFFFFE220U) /**< \brief (PMECC) PMECC ECC 8 Register (sec_num = 7) */
  #define REG_PMECC_ECC9_7                   (0xFFFFE224U) /**< \brief (PMECC) PMECC ECC 9 Register (sec_num = 7) */
  #define REG_PMECC_ECC10_7                  (0xFFFFE228U) /**< \brief (PMECC) PMECC ECC 10 Register (sec_num = 7) */
  #define REG_PMECC_REM0_0                   (0xFFFFE240U) /**< \brief (PMECC) PMECC REM 0 Register (sec_num = 0) */
  #define REG_PMECC_REM1_0                   (0xFFFFE244U) /**< \brief (PMECC) PMECC REM 1 Register (sec_num = 0) */
  #define REG_PMECC_REM2_0                   (0xFFFFE248U) /**< \brief (PMECC) PMECC REM 2 Register (sec_num = 0) */
  #define REG_PMECC_REM3_0                   (0xFFFFE24CU) /**< \brief (PMECC) PMECC REM 3 Register (sec_num = 0) */
  #define REG_PMECC_REM4_0                   (0xFFFFE250U) /**< \brief (PMECC) PMECC REM 4 Register (sec_num = 0) */
  #define REG_PMECC_REM5_0                   (0xFFFFE254U) /**< \brief (PMECC) PMECC REM 5 Register (sec_num = 0) */
  #define REG_PMECC_REM6_0                   (0xFFFFE258U) /**< \brief (PMECC) PMECC REM 6 Register (sec_num = 0) */
  #define REG_PMECC_REM7_0                   (0xFFFFE25CU) /**< \brief (PMECC) PMECC REM 7 Register (sec_num = 0) */
  #define REG_PMECC_REM8_0                   (0xFFFFE260U) /**< \brief (PMECC) PMECC REM 8 Register (sec_num = 0) */
  #define REG_PMECC_REM9_0                   (0xFFFFE264U) /**< \brief (PMECC) PMECC REM 9 Register (sec_num = 0) */
  #define REG_PMECC_REM10_0                  (0xFFFFE268U) /**< \brief (PMECC) PMECC REM 10 Register (sec_num = 0) */
  #define REG_PMECC_REM11_0                  (0xFFFFE26CU) /**< \brief (PMECC) PMECC REM 11 Register (sec_num = 0) */
  #define REG_PMECC_REM0_1                   (0xFFFFE280U) /**< \brief (PMECC) PMECC REM 0 Register (sec_num = 1) */
  #define REG_PMECC_REM1_1                   (0xFFFFE284U) /**< \brief (PMECC) PMECC REM 1 Register (sec_num = 1) */
  #define REG_PMECC_REM2_1                   (0xFFFFE288U) /**< \brief (PMECC) PMECC REM 2 Register (sec_num = 1) */
  #define REG_PMECC_REM3_1                   (0xFFFFE28CU) /**< \brief (PMECC) PMECC REM 3 Register (sec_num = 1) */
  #define REG_PMECC_REM4_1                   (0xFFFFE290U) /**< \brief (PMECC) PMECC REM 4 Register (sec_num = 1) */
  #define REG_PMECC_REM5_1                   (0xFFFFE294U) /**< \brief (PMECC) PMECC REM 5 Register (sec_num = 1) */
  #define REG_PMECC_REM6_1                   (0xFFFFE298U) /**< \brief (PMECC) PMECC REM 6 Register (sec_num = 1) */
  #define REG_PMECC_REM7_1                   (0xFFFFE29CU) /**< \brief (PMECC) PMECC REM 7 Register (sec_num = 1) */
  #define REG_PMECC_REM8_1                   (0xFFFFE2A0U) /**< \brief (PMECC) PMECC REM 8 Register (sec_num = 1) */
  #define REG_PMECC_REM9_1                   (0xFFFFE2A4U) /**< \brief (PMECC) PMECC REM 9 Register (sec_num = 1) */
  #define REG_PMECC_REM10_1                  (0xFFFFE2A8U) /**< \brief (PMECC) PMECC REM 10 Register (sec_num = 1) */
  #define REG_PMECC_REM11_1                  (0xFFFFE2ACU) /**< \brief (PMECC) PMECC REM 11 Register (sec_num = 1) */
  #define REG_PMECC_REM0_2                   (0xFFFFE2C0U) /**< \brief (PMECC) PMECC REM 0 Register (sec_num = 2) */
  #define REG_PMECC_REM1_2                   (0xFFFFE2C4U) /**< \brief (PMECC) PMECC REM 1 Register (sec_num = 2) */
  #define REG_PMECC_REM2_2                   (0xFFFFE2C8U) /**< \brief (PMECC) PMECC REM 2 Register (sec_num = 2) */
  #define REG_PMECC_REM3_2                   (0xFFFFE2CCU) /**< \brief (PMECC) PMECC REM 3 Register (sec_num = 2) */
  #define REG_PMECC_REM4_2                   (0xFFFFE2D0U) /**< \brief (PMECC) PMECC REM 4 Register (sec_num = 2) */
  #define REG_PMECC_REM5_2                   (0xFFFFE2D4U) /**< \brief (PMECC) PMECC REM 5 Register (sec_num = 2) */
  #define REG_PMECC_REM6_2                   (0xFFFFE2D8U) /**< \brief (PMECC) PMECC REM 6 Register (sec_num = 2) */
  #define REG_PMECC_REM7_2                   (0xFFFFE2DCU) /**< \brief (PMECC) PMECC REM 7 Register (sec_num = 2) */
  #define REG_PMECC_REM8_2                   (0xFFFFE2E0U) /**< \brief (PMECC) PMECC REM 8 Register (sec_num = 2) */
  #define REG_PMECC_REM9_2                   (0xFFFFE2E4U) /**< \brief (PMECC) PMECC REM 9 Register (sec_num = 2) */
  #define REG_PMECC_REM10_2                  (0xFFFFE2E8U) /**< \brief (PMECC) PMECC REM 10 Register (sec_num = 2) */
  #define REG_PMECC_REM11_2                  (0xFFFFE2ECU) /**< \brief (PMECC) PMECC REM 11 Register (sec_num = 2) */
  #define REG_PMECC_REM0_3                   (0xFFFFE300U) /**< \brief (PMECC) PMECC REM 0 Register (sec_num = 3) */
  #define REG_PMECC_REM1_3                   (0xFFFFE304U) /**< \brief (PMECC) PMECC REM 1 Register (sec_num = 3) */
  #define REG_PMECC_REM2_3                   (0xFFFFE308U) /**< \brief (PMECC) PMECC REM 2 Register (sec_num = 3) */
  #define REG_PMECC_REM3_3                   (0xFFFFE30CU) /**< \brief (PMECC) PMECC REM 3 Register (sec_num = 3) */
  #define REG_PMECC_REM4_3                   (0xFFFFE310U) /**< \brief (PMECC) PMECC REM 4 Register (sec_num = 3) */
  #define REG_PMECC_REM5_3                   (0xFFFFE314U) /**< \brief (PMECC) PMECC REM 5 Register (sec_num = 3) */
  #define REG_PMECC_REM6_3                   (0xFFFFE318U) /**< \brief (PMECC) PMECC REM 6 Register (sec_num = 3) */
  #define REG_PMECC_REM7_3                   (0xFFFFE31CU) /**< \brief (PMECC) PMECC REM 7 Register (sec_num = 3) */
  #define REG_PMECC_REM8_3                   (0xFFFFE320U) /**< \brief (PMECC) PMECC REM 8 Register (sec_num = 3) */
  #define REG_PMECC_REM9_3                   (0xFFFFE324U) /**< \brief (PMECC) PMECC REM 9 Register (sec_num = 3) */
  #define REG_PMECC_REM10_3                  (0xFFFFE328U) /**< \brief (PMECC) PMECC REM 10 Register (sec_num = 3) */
  #define REG_PMECC_REM11_3                  (0xFFFFE32CU) /**< \brief (PMECC) PMECC REM 11 Register (sec_num = 3) */
  #define REG_PMECC_REM0_4                   (0xFFFFE340U) /**< \brief (PMECC) PMECC REM 0 Register (sec_num = 4) */
  #define REG_PMECC_REM1_4                   (0xFFFFE344U) /**< \brief (PMECC) PMECC REM 1 Register (sec_num = 4) */
  #define REG_PMECC_REM2_4                   (0xFFFFE348U) /**< \brief (PMECC) PMECC REM 2 Register (sec_num = 4) */
  #define REG_PMECC_REM3_4                   (0xFFFFE34CU) /**< \brief (PMECC) PMECC REM 3 Register (sec_num = 4) */
  #define REG_PMECC_REM4_4                   (0xFFFFE350U) /**< \brief (PMECC) PMECC REM 4 Register (sec_num = 4) */
  #define REG_PMECC_REM5_4                   (0xFFFFE354U) /**< \brief (PMECC) PMECC REM 5 Register (sec_num = 4) */
  #define REG_PMECC_REM6_4                   (0xFFFFE358U) /**< \brief (PMECC) PMECC REM 6 Register (sec_num = 4) */
  #define REG_PMECC_REM7_4                   (0xFFFFE35CU) /**< \brief (PMECC) PMECC REM 7 Register (sec_num = 4) */
  #define REG_PMECC_REM8_4                   (0xFFFFE360U) /**< \brief (PMECC) PMECC REM 8 Register (sec_num = 4) */
  #define REG_PMECC_REM9_4                   (0xFFFFE364U) /**< \brief (PMECC) PMECC REM 9 Register (sec_num = 4) */
  #define REG_PMECC_REM10_4                  (0xFFFFE368U) /**< \brief (PMECC) PMECC REM 10 Register (sec_num = 4) */
  #define REG_PMECC_REM11_4                  (0xFFFFE36CU) /**< \brief (PMECC) PMECC REM 11 Register (sec_num = 4) */
  #define REG_PMECC_REM0_5                   (0xFFFFE380U) /**< \brief (PMECC) PMECC REM 0 Register (sec_num = 5) */
  #define REG_PMECC_REM1_5                   (0xFFFFE384U) /**< \brief (PMECC) PMECC REM 1 Register (sec_num = 5) */
  #define REG_PMECC_REM2_5                   (0xFFFFE388U) /**< \brief (PMECC) PMECC REM 2 Register (sec_num = 5) */
  #define REG_PMECC_REM3_5                   (0xFFFFE38CU) /**< \brief (PMECC) PMECC REM 3 Register (sec_num = 5) */
  #define REG_PMECC_REM4_5                   (0xFFFFE390U) /**< \brief (PMECC) PMECC REM 4 Register (sec_num = 5) */
  #define REG_PMECC_REM5_5                   (0xFFFFE394U) /**< \brief (PMECC) PMECC REM 5 Register (sec_num = 5) */
  #define REG_PMECC_REM6_5                   (0xFFFFE398U) /**< \brief (PMECC) PMECC REM 6 Register (sec_num = 5) */
  #define REG_PMECC_REM7_5                   (0xFFFFE39CU) /**< \brief (PMECC) PMECC REM 7 Register (sec_num = 5) */
  #define REG_PMECC_REM8_5                   (0xFFFFE3A0U) /**< \brief (PMECC) PMECC REM 8 Register (sec_num = 5) */
  #define REG_PMECC_REM9_5                   (0xFFFFE3A4U) /**< \brief (PMECC) PMECC REM 9 Register (sec_num = 5) */
  #define REG_PMECC_REM10_5                  (0xFFFFE3A8U) /**< \brief (PMECC) PMECC REM 10 Register (sec_num = 5) */
  #define REG_PMECC_REM11_5                  (0xFFFFE3ACU) /**< \brief (PMECC) PMECC REM 11 Register (sec_num = 5) */
  #define REG_PMECC_REM0_6                   (0xFFFFE3C0U) /**< \brief (PMECC) PMECC REM 0 Register (sec_num = 6) */
  #define REG_PMECC_REM1_6                   (0xFFFFE3C4U) /**< \brief (PMECC) PMECC REM 1 Register (sec_num = 6) */
  #define REG_PMECC_REM2_6                   (0xFFFFE3C8U) /**< \brief (PMECC) PMECC REM 2 Register (sec_num = 6) */
  #define REG_PMECC_REM3_6                   (0xFFFFE3CCU) /**< \brief (PMECC) PMECC REM 3 Register (sec_num = 6) */
  #define REG_PMECC_REM4_6                   (0xFFFFE3D0U) /**< \brief (PMECC) PMECC REM 4 Register (sec_num = 6) */
  #define REG_PMECC_REM5_6                   (0xFFFFE3D4U) /**< \brief (PMECC) PMECC REM 5 Register (sec_num = 6) */
  #define REG_PMECC_REM6_6                   (0xFFFFE3D8U) /**< \brief (PMECC) PMECC REM 6 Register (sec_num = 6) */
  #define REG_PMECC_REM7_6                   (0xFFFFE3DCU) /**< \brief (PMECC) PMECC REM 7 Register (sec_num = 6) */
  #define REG_PMECC_REM8_6                   (0xFFFFE3E0U) /**< \brief (PMECC) PMECC REM 8 Register (sec_num = 6) */
  #define REG_PMECC_REM9_6                   (0xFFFFE3E4U) /**< \brief (PMECC) PMECC REM 9 Register (sec_num = 6) */
  #define REG_PMECC_REM10_6                  (0xFFFFE3E8U) /**< \brief (PMECC) PMECC REM 10 Register (sec_num = 6) */
  #define REG_PMECC_REM11_6                  (0xFFFFE3ECU) /**< \brief (PMECC) PMECC REM 11 Register (sec_num = 6) */
  #define REG_PMECC_REM0_7                   (0xFFFFE400U) /**< \brief (PMECC) PMECC REM 0 Register (sec_num = 7) */
  #define REG_PMECC_REM1_7                   (0xFFFFE404U) /**< \brief (PMECC) PMECC REM 1 Register (sec_num = 7) */
  #define REG_PMECC_REM2_7                   (0xFFFFE408U) /**< \brief (PMECC) PMECC REM 2 Register (sec_num = 7) */
  #define REG_PMECC_REM3_7                   (0xFFFFE40CU) /**< \brief (PMECC) PMECC REM 3 Register (sec_num = 7) */
  #define REG_PMECC_REM4_7                   (0xFFFFE410U) /**< \brief (PMECC) PMECC REM 4 Register (sec_num = 7) */
  #define REG_PMECC_REM5_7                   (0xFFFFE414U) /**< \brief (PMECC) PMECC REM 5 Register (sec_num = 7) */
  #define REG_PMECC_REM6_7                   (0xFFFFE418U) /**< \brief (PMECC) PMECC REM 6 Register (sec_num = 7) */
  #define REG_PMECC_REM7_7                   (0xFFFFE41CU) /**< \brief (PMECC) PMECC REM 7 Register (sec_num = 7) */
  #define REG_PMECC_REM8_7                   (0xFFFFE420U) /**< \brief (PMECC) PMECC REM 8 Register (sec_num = 7) */
  #define REG_PMECC_REM9_7                   (0xFFFFE424U) /**< \brief (PMECC) PMECC REM 9 Register (sec_num = 7) */
  #define REG_PMECC_REM10_7                  (0xFFFFE428U) /**< \brief (PMECC) PMECC REM 10 Register (sec_num = 7) */
  #define REG_PMECC_REM11_7                  (0xFFFFE42CU) /**< \brief (PMECC) PMECC REM 11 Register (sec_num = 7) */
#else
  #define REG_PMECC_CFG     (*(__IO uint32_t*)0xFFFFE000U) /**< \brief (PMECC) PMECC Configuration Register */
  #define REG_PMECC_SAREA   (*(__IO uint32_t*)0xFFFFE004U) /**< \brief (PMECC) PMECC Spare Area Size Register */
  #define REG_PMECC_SADDR   (*(__IO uint32_t*)0xFFFFE008U) /**< \brief (PMECC) PMECC Start Address Register */
  #define REG_PMECC_EADDR   (*(__IO uint32_t*)0xFFFFE00CU) /**< \brief (PMECC) PMECC End Address Register */
  #define REG_PMECC_CLK     (*(__IO uint32_t*)0xFFFFE010U) /**< \brief (PMECC) PMECC Clock Control Register */
  #define REG_PMECC_CTRL    (*(__O  uint32_t*)0xFFFFE014U) /**< \brief (PMECC) PMECC Control Register */
  #define REG_PMECC_SR      (*(__I  uint32_t*)0xFFFFE018U) /**< \brief (PMECC) PMECC Status Register */
  #define REG_PMECC_IER     (*(__O  uint32_t*)0xFFFFE01CU) /**< \brief (PMECC) PMECC Interrupt Enable register */
  #define REG_PMECC_IDR     (*(__O  uint32_t*)0xFFFFE020U) /**< \brief (PMECC) PMECC Interrupt Disable Register */
  #define REG_PMECC_IMR     (*(__I  uint32_t*)0xFFFFE024U) /**< \brief (PMECC) PMECC Interrupt Mask Register */
  #define REG_PMECC_ISR     (*(__I  uint32_t*)0xFFFFE028U) /**< \brief (PMECC) PMECC Interrupt Status Register */
  #define REG_PMECC_ECC0_0  (*(__I  uint32_t*)0xFFFFE040U) /**< \brief (PMECC) PMECC ECC 0 Register (sec_num = 0) */
  #define REG_PMECC_ECC1_0  (*(__I  uint32_t*)0xFFFFE044U) /**< \brief (PMECC) PMECC ECC 1 Register (sec_num = 0) */
  #define REG_PMECC_ECC2_0  (*(__I  uint32_t*)0xFFFFE048U) /**< \brief (PMECC) PMECC ECC 2 Register (sec_num = 0) */
  #define REG_PMECC_ECC3_0  (*(__I  uint32_t*)0xFFFFE04CU) /**< \brief (PMECC) PMECC ECC 3 Register (sec_num = 0) */
  #define REG_PMECC_ECC4_0  (*(__I  uint32_t*)0xFFFFE050U) /**< \brief (PMECC) PMECC ECC 4 Register (sec_num = 0) */
  #define REG_PMECC_ECC5_0  (*(__I  uint32_t*)0xFFFFE054U) /**< \brief (PMECC) PMECC ECC 5 Register (sec_num = 0) */
  #define REG_PMECC_ECC6_0  (*(__I  uint32_t*)0xFFFFE058U) /**< \brief (PMECC) PMECC ECC 6 Register (sec_num = 0) */
  #define REG_PMECC_ECC7_0  (*(__I  uint32_t*)0xFFFFE05CU) /**< \brief (PMECC) PMECC ECC 7 Register (sec_num = 0) */
  #define REG_PMECC_ECC8_0  (*(__I  uint32_t*)0xFFFFE060U) /**< \brief (PMECC) PMECC ECC 8 Register (sec_num = 0) */
  #define REG_PMECC_ECC9_0  (*(__I  uint32_t*)0xFFFFE064U) /**< \brief (PMECC) PMECC ECC 9 Register (sec_num = 0) */
  #define REG_PMECC_ECC10_0 (*(__I  uint32_t*)0xFFFFE068U) /**< \brief (PMECC) PMECC ECC 10 Register (sec_num = 0) */
  #define REG_PMECC_ECC0_1  (*(__I  uint32_t*)0xFFFFE080U) /**< \brief (PMECC) PMECC ECC 0 Register (sec_num = 1) */
  #define REG_PMECC_ECC1_1  (*(__I  uint32_t*)0xFFFFE084U) /**< \brief (PMECC) PMECC ECC 1 Register (sec_num = 1) */
  #define REG_PMECC_ECC2_1  (*(__I  uint32_t*)0xFFFFE088U) /**< \brief (PMECC) PMECC ECC 2 Register (sec_num = 1) */
  #define REG_PMECC_ECC3_1  (*(__I  uint32_t*)0xFFFFE08CU) /**< \brief (PMECC) PMECC ECC 3 Register (sec_num = 1) */
  #define REG_PMECC_ECC4_1  (*(__I  uint32_t*)0xFFFFE090U) /**< \brief (PMECC) PMECC ECC 4 Register (sec_num = 1) */
  #define REG_PMECC_ECC5_1  (*(__I  uint32_t*)0xFFFFE094U) /**< \brief (PMECC) PMECC ECC 5 Register (sec_num = 1) */
  #define REG_PMECC_ECC6_1  (*(__I  uint32_t*)0xFFFFE098U) /**< \brief (PMECC) PMECC ECC 6 Register (sec_num = 1) */
  #define REG_PMECC_ECC7_1  (*(__I  uint32_t*)0xFFFFE09CU) /**< \brief (PMECC) PMECC ECC 7 Register (sec_num = 1) */
  #define REG_PMECC_ECC8_1  (*(__I  uint32_t*)0xFFFFE0A0U) /**< \brief (PMECC) PMECC ECC 8 Register (sec_num = 1) */
  #define REG_PMECC_ECC9_1  (*(__I  uint32_t*)0xFFFFE0A4U) /**< \brief (PMECC) PMECC ECC 9 Register (sec_num = 1) */
  #define REG_PMECC_ECC10_1 (*(__I  uint32_t*)0xFFFFE0A8U) /**< \brief (PMECC) PMECC ECC 10 Register (sec_num = 1) */
  #define REG_PMECC_ECC0_2  (*(__I  uint32_t*)0xFFFFE0C0U) /**< \brief (PMECC) PMECC ECC 0 Register (sec_num = 2) */
  #define REG_PMECC_ECC1_2  (*(__I  uint32_t*)0xFFFFE0C4U) /**< \brief (PMECC) PMECC ECC 1 Register (sec_num = 2) */
  #define REG_PMECC_ECC2_2  (*(__I  uint32_t*)0xFFFFE0C8U) /**< \brief (PMECC) PMECC ECC 2 Register (sec_num = 2) */
  #define REG_PMECC_ECC3_2  (*(__I  uint32_t*)0xFFFFE0CCU) /**< \brief (PMECC) PMECC ECC 3 Register (sec_num = 2) */
  #define REG_PMECC_ECC4_2  (*(__I  uint32_t*)0xFFFFE0D0U) /**< \brief (PMECC) PMECC ECC 4 Register (sec_num = 2) */
  #define REG_PMECC_ECC5_2  (*(__I  uint32_t*)0xFFFFE0D4U) /**< \brief (PMECC) PMECC ECC 5 Register (sec_num = 2) */
  #define REG_PMECC_ECC6_2  (*(__I  uint32_t*)0xFFFFE0D8U) /**< \brief (PMECC) PMECC ECC 6 Register (sec_num = 2) */
  #define REG_PMECC_ECC7_2  (*(__I  uint32_t*)0xFFFFE0DCU) /**< \brief (PMECC) PMECC ECC 7 Register (sec_num = 2) */
  #define REG_PMECC_ECC8_2  (*(__I  uint32_t*)0xFFFFE0E0U) /**< \brief (PMECC) PMECC ECC 8 Register (sec_num = 2) */
  #define REG_PMECC_ECC9_2  (*(__I  uint32_t*)0xFFFFE0E4U) /**< \brief (PMECC) PMECC ECC 9 Register (sec_num = 2) */
  #define REG_PMECC_ECC10_2 (*(__I  uint32_t*)0xFFFFE0E8U) /**< \brief (PMECC) PMECC ECC 10 Register (sec_num = 2) */
  #define REG_PMECC_ECC0_3  (*(__I  uint32_t*)0xFFFFE100U) /**< \brief (PMECC) PMECC ECC 0 Register (sec_num = 3) */
  #define REG_PMECC_ECC1_3  (*(__I  uint32_t*)0xFFFFE104U) /**< \brief (PMECC) PMECC ECC 1 Register (sec_num = 3) */
  #define REG_PMECC_ECC2_3  (*(__I  uint32_t*)0xFFFFE108U) /**< \brief (PMECC) PMECC ECC 2 Register (sec_num = 3) */
  #define REG_PMECC_ECC3_3  (*(__I  uint32_t*)0xFFFFE10CU) /**< \brief (PMECC) PMECC ECC 3 Register (sec_num = 3) */
  #define REG_PMECC_ECC4_3  (*(__I  uint32_t*)0xFFFFE110U) /**< \brief (PMECC) PMECC ECC 4 Register (sec_num = 3) */
  #define REG_PMECC_ECC5_3  (*(__I  uint32_t*)0xFFFFE114U) /**< \brief (PMECC) PMECC ECC 5 Register (sec_num = 3) */
  #define REG_PMECC_ECC6_3  (*(__I  uint32_t*)0xFFFFE118U) /**< \brief (PMECC) PMECC ECC 6 Register (sec_num = 3) */
  #define REG_PMECC_ECC7_3  (*(__I  uint32_t*)0xFFFFE11CU) /**< \brief (PMECC) PMECC ECC 7 Register (sec_num = 3) */
  #define REG_PMECC_ECC8_3  (*(__I  uint32_t*)0xFFFFE120U) /**< \brief (PMECC) PMECC ECC 8 Register (sec_num = 3) */
  #define REG_PMECC_ECC9_3  (*(__I  uint32_t*)0xFFFFE124U) /**< \brief (PMECC) PMECC ECC 9 Register (sec_num = 3) */
  #define REG_PMECC_ECC10_3 (*(__I  uint32_t*)0xFFFFE128U) /**< \brief (PMECC) PMECC ECC 10 Register (sec_num = 3) */
  #define REG_PMECC_ECC0_4  (*(__I  uint32_t*)0xFFFFE140U) /**< \brief (PMECC) PMECC ECC 0 Register (sec_num = 4) */
  #define REG_PMECC_ECC1_4  (*(__I  uint32_t*)0xFFFFE144U) /**< \brief (PMECC) PMECC ECC 1 Register (sec_num = 4) */
  #define REG_PMECC_ECC2_4  (*(__I  uint32_t*)0xFFFFE148U) /**< \brief (PMECC) PMECC ECC 2 Register (sec_num = 4) */
  #define REG_PMECC_ECC3_4  (*(__I  uint32_t*)0xFFFFE14CU) /**< \brief (PMECC) PMECC ECC 3 Register (sec_num = 4) */
  #define REG_PMECC_ECC4_4  (*(__I  uint32_t*)0xFFFFE150U) /**< \brief (PMECC) PMECC ECC 4 Register (sec_num = 4) */
  #define REG_PMECC_ECC5_4  (*(__I  uint32_t*)0xFFFFE154U) /**< \brief (PMECC) PMECC ECC 5 Register (sec_num = 4) */
  #define REG_PMECC_ECC6_4  (*(__I  uint32_t*)0xFFFFE158U) /**< \brief (PMECC) PMECC ECC 6 Register (sec_num = 4) */
  #define REG_PMECC_ECC7_4  (*(__I  uint32_t*)0xFFFFE15CU) /**< \brief (PMECC) PMECC ECC 7 Register (sec_num = 4) */
  #define REG_PMECC_ECC8_4  (*(__I  uint32_t*)0xFFFFE160U) /**< \brief (PMECC) PMECC ECC 8 Register (sec_num = 4) */
  #define REG_PMECC_ECC9_4  (*(__I  uint32_t*)0xFFFFE164U) /**< \brief (PMECC) PMECC ECC 9 Register (sec_num = 4) */
  #define REG_PMECC_ECC10_4 (*(__I  uint32_t*)0xFFFFE168U) /**< \brief (PMECC) PMECC ECC 10 Register (sec_num = 4) */
  #define REG_PMECC_ECC0_5  (*(__I  uint32_t*)0xFFFFE180U) /**< \brief (PMECC) PMECC ECC 0 Register (sec_num = 5) */
  #define REG_PMECC_ECC1_5  (*(__I  uint32_t*)0xFFFFE184U) /**< \brief (PMECC) PMECC ECC 1 Register (sec_num = 5) */
  #define REG_PMECC_ECC2_5  (*(__I  uint32_t*)0xFFFFE188U) /**< \brief (PMECC) PMECC ECC 2 Register (sec_num = 5) */
  #define REG_PMECC_ECC3_5  (*(__I  uint32_t*)0xFFFFE18CU) /**< \brief (PMECC) PMECC ECC 3 Register (sec_num = 5) */
  #define REG_PMECC_ECC4_5  (*(__I  uint32_t*)0xFFFFE190U) /**< \brief (PMECC) PMECC ECC 4 Register (sec_num = 5) */
  #define REG_PMECC_ECC5_5  (*(__I  uint32_t*)0xFFFFE194U) /**< \brief (PMECC) PMECC ECC 5 Register (sec_num = 5) */
  #define REG_PMECC_ECC6_5  (*(__I  uint32_t*)0xFFFFE198U) /**< \brief (PMECC) PMECC ECC 6 Register (sec_num = 5) */
  #define REG_PMECC_ECC7_5  (*(__I  uint32_t*)0xFFFFE19CU) /**< \brief (PMECC) PMECC ECC 7 Register (sec_num = 5) */
  #define REG_PMECC_ECC8_5  (*(__I  uint32_t*)0xFFFFE1A0U) /**< \brief (PMECC) PMECC ECC 8 Register (sec_num = 5) */
  #define REG_PMECC_ECC9_5  (*(__I  uint32_t*)0xFFFFE1A4U) /**< \brief (PMECC) PMECC ECC 9 Register (sec_num = 5) */
  #define REG_PMECC_ECC10_5 (*(__I  uint32_t*)0xFFFFE1A8U) /**< \brief (PMECC) PMECC ECC 10 Register (sec_num = 5) */
  #define REG_PMECC_ECC0_6  (*(__I  uint32_t*)0xFFFFE1C0U) /**< \brief (PMECC) PMECC ECC 0 Register (sec_num = 6) */
  #define REG_PMECC_ECC1_6  (*(__I  uint32_t*)0xFFFFE1C4U) /**< \brief (PMECC) PMECC ECC 1 Register (sec_num = 6) */
  #define REG_PMECC_ECC2_6  (*(__I  uint32_t*)0xFFFFE1C8U) /**< \brief (PMECC) PMECC ECC 2 Register (sec_num = 6) */
  #define REG_PMECC_ECC3_6  (*(__I  uint32_t*)0xFFFFE1CCU) /**< \brief (PMECC) PMECC ECC 3 Register (sec_num = 6) */
  #define REG_PMECC_ECC4_6  (*(__I  uint32_t*)0xFFFFE1D0U) /**< \brief (PMECC) PMECC ECC 4 Register (sec_num = 6) */
  #define REG_PMECC_ECC5_6  (*(__I  uint32_t*)0xFFFFE1D4U) /**< \brief (PMECC) PMECC ECC 5 Register (sec_num = 6) */
  #define REG_PMECC_ECC6_6  (*(__I  uint32_t*)0xFFFFE1D8U) /**< \brief (PMECC) PMECC ECC 6 Register (sec_num = 6) */
  #define REG_PMECC_ECC7_6  (*(__I  uint32_t*)0xFFFFE1DCU) /**< \brief (PMECC) PMECC ECC 7 Register (sec_num = 6) */
  #define REG_PMECC_ECC8_6  (*(__I  uint32_t*)0xFFFFE1E0U) /**< \brief (PMECC) PMECC ECC 8 Register (sec_num = 6) */
  #define REG_PMECC_ECC9_6  (*(__I  uint32_t*)0xFFFFE1E4U) /**< \brief (PMECC) PMECC ECC 9 Register (sec_num = 6) */
  #define REG_PMECC_ECC10_6 (*(__I  uint32_t*)0xFFFFE1E8U) /**< \brief (PMECC) PMECC ECC 10 Register (sec_num = 6) */
  #define REG_PMECC_ECC0_7  (*(__I  uint32_t*)0xFFFFE200U) /**< \brief (PMECC) PMECC ECC 0 Register (sec_num = 7) */
  #define REG_PMECC_ECC1_7  (*(__I  uint32_t*)0xFFFFE204U) /**< \brief (PMECC) PMECC ECC 1 Register (sec_num = 7) */
  #define REG_PMECC_ECC2_7  (*(__I  uint32_t*)0xFFFFE208U) /**< \brief (PMECC) PMECC ECC 2 Register (sec_num = 7) */
  #define REG_PMECC_ECC3_7  (*(__I  uint32_t*)0xFFFFE20CU) /**< \brief (PMECC) PMECC ECC 3 Register (sec_num = 7) */
  #define REG_PMECC_ECC4_7  (*(__I  uint32_t*)0xFFFFE210U) /**< \brief (PMECC) PMECC ECC 4 Register (sec_num = 7) */
  #define REG_PMECC_ECC5_7  (*(__I  uint32_t*)0xFFFFE214U) /**< \brief (PMECC) PMECC ECC 5 Register (sec_num = 7) */
  #define REG_PMECC_ECC6_7  (*(__I  uint32_t*)0xFFFFE218U) /**< \brief (PMECC) PMECC ECC 6 Register (sec_num = 7) */
  #define REG_PMECC_ECC7_7  (*(__I  uint32_t*)0xFFFFE21CU) /**< \brief (PMECC) PMECC ECC 7 Register (sec_num = 7) */
  #define REG_PMECC_ECC8_7  (*(__I  uint32_t*)0xFFFFE220U) /**< \brief (PMECC) PMECC ECC 8 Register (sec_num = 7) */
  #define REG_PMECC_ECC9_7  (*(__I  uint32_t*)0xFFFFE224U) /**< \brief (PMECC) PMECC ECC 9 Register (sec_num = 7) */
  #define REG_PMECC_ECC10_7 (*(__I  uint32_t*)0xFFFFE228U) /**< \brief (PMECC) PMECC ECC 10 Register (sec_num = 7) */
  #define REG_PMECC_REM0_0  (*(__I  uint32_t*)0xFFFFE240U) /**< \brief (PMECC) PMECC REM 0 Register (sec_num = 0) */
  #define REG_PMECC_REM1_0  (*(__I  uint32_t*)0xFFFFE244U) /**< \brief (PMECC) PMECC REM 1 Register (sec_num = 0) */
  #define REG_PMECC_REM2_0  (*(__I  uint32_t*)0xFFFFE248U) /**< \brief (PMECC) PMECC REM 2 Register (sec_num = 0) */
  #define REG_PMECC_REM3_0  (*(__I  uint32_t*)0xFFFFE24CU) /**< \brief (PMECC) PMECC REM 3 Register (sec_num = 0) */
  #define REG_PMECC_REM4_0  (*(__I  uint32_t*)0xFFFFE250U) /**< \brief (PMECC) PMECC REM 4 Register (sec_num = 0) */
  #define REG_PMECC_REM5_0  (*(__I  uint32_t*)0xFFFFE254U) /**< \brief (PMECC) PMECC REM 5 Register (sec_num = 0) */
  #define REG_PMECC_REM6_0  (*(__I  uint32_t*)0xFFFFE258U) /**< \brief (PMECC) PMECC REM 6 Register (sec_num = 0) */
  #define REG_PMECC_REM7_0  (*(__I  uint32_t*)0xFFFFE25CU) /**< \brief (PMECC) PMECC REM 7 Register (sec_num = 0) */
  #define REG_PMECC_REM8_0  (*(__I  uint32_t*)0xFFFFE260U) /**< \brief (PMECC) PMECC REM 8 Register (sec_num = 0) */
  #define REG_PMECC_REM9_0  (*(__I  uint32_t*)0xFFFFE264U) /**< \brief (PMECC) PMECC REM 9 Register (sec_num = 0) */
  #define REG_PMECC_REM10_0 (*(__I  uint32_t*)0xFFFFE268U) /**< \brief (PMECC) PMECC REM 10 Register (sec_num = 0) */
  #define REG_PMECC_REM11_0 (*(__I  uint32_t*)0xFFFFE26CU) /**< \brief (PMECC) PMECC REM 11 Register (sec_num = 0) */
  #define REG_PMECC_REM0_1  (*(__I  uint32_t*)0xFFFFE280U) /**< \brief (PMECC) PMECC REM 0 Register (sec_num = 1) */
  #define REG_PMECC_REM1_1  (*(__I  uint32_t*)0xFFFFE284U) /**< \brief (PMECC) PMECC REM 1 Register (sec_num = 1) */
  #define REG_PMECC_REM2_1  (*(__I  uint32_t*)0xFFFFE288U) /**< \brief (PMECC) PMECC REM 2 Register (sec_num = 1) */
  #define REG_PMECC_REM3_1  (*(__I  uint32_t*)0xFFFFE28CU) /**< \brief (PMECC) PMECC REM 3 Register (sec_num = 1) */
  #define REG_PMECC_REM4_1  (*(__I  uint32_t*)0xFFFFE290U) /**< \brief (PMECC) PMECC REM 4 Register (sec_num = 1) */
  #define REG_PMECC_REM5_1  (*(__I  uint32_t*)0xFFFFE294U) /**< \brief (PMECC) PMECC REM 5 Register (sec_num = 1) */
  #define REG_PMECC_REM6_1  (*(__I  uint32_t*)0xFFFFE298U) /**< \brief (PMECC) PMECC REM 6 Register (sec_num = 1) */
  #define REG_PMECC_REM7_1  (*(__I  uint32_t*)0xFFFFE29CU) /**< \brief (PMECC) PMECC REM 7 Register (sec_num = 1) */
  #define REG_PMECC_REM8_1  (*(__I  uint32_t*)0xFFFFE2A0U) /**< \brief (PMECC) PMECC REM 8 Register (sec_num = 1) */
  #define REG_PMECC_REM9_1  (*(__I  uint32_t*)0xFFFFE2A4U) /**< \brief (PMECC) PMECC REM 9 Register (sec_num = 1) */
  #define REG_PMECC_REM10_1 (*(__I  uint32_t*)0xFFFFE2A8U) /**< \brief (PMECC) PMECC REM 10 Register (sec_num = 1) */
  #define REG_PMECC_REM11_1 (*(__I  uint32_t*)0xFFFFE2ACU) /**< \brief (PMECC) PMECC REM 11 Register (sec_num = 1) */
  #define REG_PMECC_REM0_2  (*(__I  uint32_t*)0xFFFFE2C0U) /**< \brief (PMECC) PMECC REM 0 Register (sec_num = 2) */
  #define REG_PMECC_REM1_2  (*(__I  uint32_t*)0xFFFFE2C4U) /**< \brief (PMECC) PMECC REM 1 Register (sec_num = 2) */
  #define REG_PMECC_REM2_2  (*(__I  uint32_t*)0xFFFFE2C8U) /**< \brief (PMECC) PMECC REM 2 Register (sec_num = 2) */
  #define REG_PMECC_REM3_2  (*(__I  uint32_t*)0xFFFFE2CCU) /**< \brief (PMECC) PMECC REM 3 Register (sec_num = 2) */
  #define REG_PMECC_REM4_2  (*(__I  uint32_t*)0xFFFFE2D0U) /**< \brief (PMECC) PMECC REM 4 Register (sec_num = 2) */
  #define REG_PMECC_REM5_2  (*(__I  uint32_t*)0xFFFFE2D4U) /**< \brief (PMECC) PMECC REM 5 Register (sec_num = 2) */
  #define REG_PMECC_REM6_2  (*(__I  uint32_t*)0xFFFFE2D8U) /**< \brief (PMECC) PMECC REM 6 Register (sec_num = 2) */
  #define REG_PMECC_REM7_2  (*(__I  uint32_t*)0xFFFFE2DCU) /**< \brief (PMECC) PMECC REM 7 Register (sec_num = 2) */
  #define REG_PMECC_REM8_2  (*(__I  uint32_t*)0xFFFFE2E0U) /**< \brief (PMECC) PMECC REM 8 Register (sec_num = 2) */
  #define REG_PMECC_REM9_2  (*(__I  uint32_t*)0xFFFFE2E4U) /**< \brief (PMECC) PMECC REM 9 Register (sec_num = 2) */
  #define REG_PMECC_REM10_2 (*(__I  uint32_t*)0xFFFFE2E8U) /**< \brief (PMECC) PMECC REM 10 Register (sec_num = 2) */
  #define REG_PMECC_REM11_2 (*(__I  uint32_t*)0xFFFFE2ECU) /**< \brief (PMECC) PMECC REM 11 Register (sec_num = 2) */
  #define REG_PMECC_REM0_3  (*(__I  uint32_t*)0xFFFFE300U) /**< \brief (PMECC) PMECC REM 0 Register (sec_num = 3) */
  #define REG_PMECC_REM1_3  (*(__I  uint32_t*)0xFFFFE304U) /**< \brief (PMECC) PMECC REM 1 Register (sec_num = 3) */
  #define REG_PMECC_REM2_3  (*(__I  uint32_t*)0xFFFFE308U) /**< \brief (PMECC) PMECC REM 2 Register (sec_num = 3) */
  #define REG_PMECC_REM3_3  (*(__I  uint32_t*)0xFFFFE30CU) /**< \brief (PMECC) PMECC REM 3 Register (sec_num = 3) */
  #define REG_PMECC_REM4_3  (*(__I  uint32_t*)0xFFFFE310U) /**< \brief (PMECC) PMECC REM 4 Register (sec_num = 3) */
  #define REG_PMECC_REM5_3  (*(__I  uint32_t*)0xFFFFE314U) /**< \brief (PMECC) PMECC REM 5 Register (sec_num = 3) */
  #define REG_PMECC_REM6_3  (*(__I  uint32_t*)0xFFFFE318U) /**< \brief (PMECC) PMECC REM 6 Register (sec_num = 3) */
  #define REG_PMECC_REM7_3  (*(__I  uint32_t*)0xFFFFE31CU) /**< \brief (PMECC) PMECC REM 7 Register (sec_num = 3) */
  #define REG_PMECC_REM8_3  (*(__I  uint32_t*)0xFFFFE320U) /**< \brief (PMECC) PMECC REM 8 Register (sec_num = 3) */
  #define REG_PMECC_REM9_3  (*(__I  uint32_t*)0xFFFFE324U) /**< \brief (PMECC) PMECC REM 9 Register (sec_num = 3) */
  #define REG_PMECC_REM10_3 (*(__I  uint32_t*)0xFFFFE328U) /**< \brief (PMECC) PMECC REM 10 Register (sec_num = 3) */
  #define REG_PMECC_REM11_3 (*(__I  uint32_t*)0xFFFFE32CU) /**< \brief (PMECC) PMECC REM 11 Register (sec_num = 3) */
  #define REG_PMECC_REM0_4  (*(__I  uint32_t*)0xFFFFE340U) /**< \brief (PMECC) PMECC REM 0 Register (sec_num = 4) */
  #define REG_PMECC_REM1_4  (*(__I  uint32_t*)0xFFFFE344U) /**< \brief (PMECC) PMECC REM 1 Register (sec_num = 4) */
  #define REG_PMECC_REM2_4  (*(__I  uint32_t*)0xFFFFE348U) /**< \brief (PMECC) PMECC REM 2 Register (sec_num = 4) */
  #define REG_PMECC_REM3_4  (*(__I  uint32_t*)0xFFFFE34CU) /**< \brief (PMECC) PMECC REM 3 Register (sec_num = 4) */
  #define REG_PMECC_REM4_4  (*(__I  uint32_t*)0xFFFFE350U) /**< \brief (PMECC) PMECC REM 4 Register (sec_num = 4) */
  #define REG_PMECC_REM5_4  (*(__I  uint32_t*)0xFFFFE354U) /**< \brief (PMECC) PMECC REM 5 Register (sec_num = 4) */
  #define REG_PMECC_REM6_4  (*(__I  uint32_t*)0xFFFFE358U) /**< \brief (PMECC) PMECC REM 6 Register (sec_num = 4) */
  #define REG_PMECC_REM7_4  (*(__I  uint32_t*)0xFFFFE35CU) /**< \brief (PMECC) PMECC REM 7 Register (sec_num = 4) */
  #define REG_PMECC_REM8_4  (*(__I  uint32_t*)0xFFFFE360U) /**< \brief (PMECC) PMECC REM 8 Register (sec_num = 4) */
  #define REG_PMECC_REM9_4  (*(__I  uint32_t*)0xFFFFE364U) /**< \brief (PMECC) PMECC REM 9 Register (sec_num = 4) */
  #define REG_PMECC_REM10_4 (*(__I  uint32_t*)0xFFFFE368U) /**< \brief (PMECC) PMECC REM 10 Register (sec_num = 4) */
  #define REG_PMECC_REM11_4 (*(__I  uint32_t*)0xFFFFE36CU) /**< \brief (PMECC) PMECC REM 11 Register (sec_num = 4) */
  #define REG_PMECC_REM0_5  (*(__I  uint32_t*)0xFFFFE380U) /**< \brief (PMECC) PMECC REM 0 Register (sec_num = 5) */
  #define REG_PMECC_REM1_5  (*(__I  uint32_t*)0xFFFFE384U) /**< \brief (PMECC) PMECC REM 1 Register (sec_num = 5) */
  #define REG_PMECC_REM2_5  (*(__I  uint32_t*)0xFFFFE388U) /**< \brief (PMECC) PMECC REM 2 Register (sec_num = 5) */
  #define REG_PMECC_REM3_5  (*(__I  uint32_t*)0xFFFFE38CU) /**< \brief (PMECC) PMECC REM 3 Register (sec_num = 5) */
  #define REG_PMECC_REM4_5  (*(__I  uint32_t*)0xFFFFE390U) /**< \brief (PMECC) PMECC REM 4 Register (sec_num = 5) */
  #define REG_PMECC_REM5_5  (*(__I  uint32_t*)0xFFFFE394U) /**< \brief (PMECC) PMECC REM 5 Register (sec_num = 5) */
  #define REG_PMECC_REM6_5  (*(__I  uint32_t*)0xFFFFE398U) /**< \brief (PMECC) PMECC REM 6 Register (sec_num = 5) */
  #define REG_PMECC_REM7_5  (*(__I  uint32_t*)0xFFFFE39CU) /**< \brief (PMECC) PMECC REM 7 Register (sec_num = 5) */
  #define REG_PMECC_REM8_5  (*(__I  uint32_t*)0xFFFFE3A0U) /**< \brief (PMECC) PMECC REM 8 Register (sec_num = 5) */
  #define REG_PMECC_REM9_5  (*(__I  uint32_t*)0xFFFFE3A4U) /**< \brief (PMECC) PMECC REM 9 Register (sec_num = 5) */
  #define REG_PMECC_REM10_5 (*(__I  uint32_t*)0xFFFFE3A8U) /**< \brief (PMECC) PMECC REM 10 Register (sec_num = 5) */
  #define REG_PMECC_REM11_5 (*(__I  uint32_t*)0xFFFFE3ACU) /**< \brief (PMECC) PMECC REM 11 Register (sec_num = 5) */
  #define REG_PMECC_REM0_6  (*(__I  uint32_t*)0xFFFFE3C0U) /**< \brief (PMECC) PMECC REM 0 Register (sec_num = 6) */
  #define REG_PMECC_REM1_6  (*(__I  uint32_t*)0xFFFFE3C4U) /**< \brief (PMECC) PMECC REM 1 Register (sec_num = 6) */
  #define REG_PMECC_REM2_6  (*(__I  uint32_t*)0xFFFFE3C8U) /**< \brief (PMECC) PMECC REM 2 Register (sec_num = 6) */
  #define REG_PMECC_REM3_6  (*(__I  uint32_t*)0xFFFFE3CCU) /**< \brief (PMECC) PMECC REM 3 Register (sec_num = 6) */
  #define REG_PMECC_REM4_6  (*(__I  uint32_t*)0xFFFFE3D0U) /**< \brief (PMECC) PMECC REM 4 Register (sec_num = 6) */
  #define REG_PMECC_REM5_6  (*(__I  uint32_t*)0xFFFFE3D4U) /**< \brief (PMECC) PMECC REM 5 Register (sec_num = 6) */
  #define REG_PMECC_REM6_6  (*(__I  uint32_t*)0xFFFFE3D8U) /**< \brief (PMECC) PMECC REM 6 Register (sec_num = 6) */
  #define REG_PMECC_REM7_6  (*(__I  uint32_t*)0xFFFFE3DCU) /**< \brief (PMECC) PMECC REM 7 Register (sec_num = 6) */
  #define REG_PMECC_REM8_6  (*(__I  uint32_t*)0xFFFFE3E0U) /**< \brief (PMECC) PMECC REM 8 Register (sec_num = 6) */
  #define REG_PMECC_REM9_6  (*(__I  uint32_t*)0xFFFFE3E4U) /**< \brief (PMECC) PMECC REM 9 Register (sec_num = 6) */
  #define REG_PMECC_REM10_6 (*(__I  uint32_t*)0xFFFFE3E8U) /**< \brief (PMECC) PMECC REM 10 Register (sec_num = 6) */
  #define REG_PMECC_REM11_6 (*(__I  uint32_t*)0xFFFFE3ECU) /**< \brief (PMECC) PMECC REM 11 Register (sec_num = 6) */
  #define REG_PMECC_REM0_7  (*(__I  uint32_t*)0xFFFFE400U) /**< \brief (PMECC) PMECC REM 0 Register (sec_num = 7) */
  #define REG_PMECC_REM1_7  (*(__I  uint32_t*)0xFFFFE404U) /**< \brief (PMECC) PMECC REM 1 Register (sec_num = 7) */
  #define REG_PMECC_REM2_7  (*(__I  uint32_t*)0xFFFFE408U) /**< \brief (PMECC) PMECC REM 2 Register (sec_num = 7) */
  #define REG_PMECC_REM3_7  (*(__I  uint32_t*)0xFFFFE40CU) /**< \brief (PMECC) PMECC REM 3 Register (sec_num = 7) */
  #define REG_PMECC_REM4_7  (*(__I  uint32_t*)0xFFFFE410U) /**< \brief (PMECC) PMECC REM 4 Register (sec_num = 7) */
  #define REG_PMECC_REM5_7  (*(__I  uint32_t*)0xFFFFE414U) /**< \brief (PMECC) PMECC REM 5 Register (sec_num = 7) */
  #define REG_PMECC_REM6_7  (*(__I  uint32_t*)0xFFFFE418U) /**< \brief (PMECC) PMECC REM 6 Register (sec_num = 7) */
  #define REG_PMECC_REM7_7  (*(__I  uint32_t*)0xFFFFE41CU) /**< \brief (PMECC) PMECC REM 7 Register (sec_num = 7) */
  #define REG_PMECC_REM8_7  (*(__I  uint32_t*)0xFFFFE420U) /**< \brief (PMECC) PMECC REM 8 Register (sec_num = 7) */
  #define REG_PMECC_REM9_7  (*(__I  uint32_t*)0xFFFFE424U) /**< \brief (PMECC) PMECC REM 9 Register (sec_num = 7) */
  #define REG_PMECC_REM10_7 (*(__I  uint32_t*)0xFFFFE428U) /**< \brief (PMECC) PMECC REM 10 Register (sec_num = 7) */
  #define REG_PMECC_REM11_7 (*(__I  uint32_t*)0xFFFFE42CU) /**< \brief (PMECC) PMECC REM 11 Register (sec_num = 7) */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_PMECC_INSTANCE_ */
