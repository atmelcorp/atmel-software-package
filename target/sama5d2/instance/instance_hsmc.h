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

#ifndef _SAMA5D2_HSMC_INSTANCE_
#define _SAMA5D2_HSMC_INSTANCE_

/* ========== Register definition for HSMC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_HSMC_CFG                         (0xF8014000U) /**< \brief (HSMC) HSMC NFC Configuration Register */
  #define REG_HSMC_CTRL                        (0xF8014004U) /**< \brief (HSMC) HSMC NFC Control Register */
  #define REG_HSMC_SR                          (0xF8014008U) /**< \brief (HSMC) HSMC NFC Status Register */
  #define REG_HSMC_IER                         (0xF801400CU) /**< \brief (HSMC) HSMC NFC Interrupt Enable Register */
  #define REG_HSMC_IDR                         (0xF8014010U) /**< \brief (HSMC) HSMC NFC Interrupt Disable Register */
  #define REG_HSMC_IMR                         (0xF8014014U) /**< \brief (HSMC) HSMC NFC Interrupt Mask Register */
  #define REG_HSMC_ADDR                        (0xF8014018U) /**< \brief (HSMC) HSMC NFC Address Cycle Zero Register */
  #define REG_HSMC_BANK                        (0xF801401CU) /**< \brief (HSMC) HSMC Bank Address Register */
  #define REG_HSMC_PMECCFG                     (0xF8014070U) /**< \brief (HSMC) PMECC Configuration Register */
  #define REG_HSMC_PMECCSAREA                  (0xF8014074U) /**< \brief (HSMC) PMECC Spare Area Size Register */
  #define REG_HSMC_PMECCSADDR                  (0xF8014078U) /**< \brief (HSMC) PMECC Start Address Register */
  #define REG_HSMC_PMECCEADDR                  (0xF801407CU) /**< \brief (HSMC) PMECC End Address Register */
  #define REG_HSMC_PMECCTRL                    (0xF8014084U) /**< \brief (HSMC) PMECC Control Register */
  #define REG_HSMC_PMECCSR                     (0xF8014088U) /**< \brief (HSMC) PMECC Status Register */
  #define REG_HSMC_PMECCIER                    (0xF801408CU) /**< \brief (HSMC) PMECC Interrupt Enable register */
  #define REG_HSMC_PMECCIDR                    (0xF8014090U) /**< \brief (HSMC) PMECC Interrupt Disable Register */
  #define REG_HSMC_PMECCIMR                    (0xF8014094U) /**< \brief (HSMC) PMECC Interrupt Mask Register */
  #define REG_HSMC_PMECCISR                    (0xF8014098U) /**< \brief (HSMC) PMECC Interrupt Status Register */
  #define REG_HSMC_PMECC0_0                    (0xF80140B0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 0) */
  #define REG_HSMC_PMECC1_0                    (0xF80140B4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 0) */
  #define REG_HSMC_PMECC2_0                    (0xF80140B8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 0) */
  #define REG_HSMC_PMECC3_0                    (0xF80140BCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 0) */
  #define REG_HSMC_PMECC4_0                    (0xF80140C0U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 0) */
  #define REG_HSMC_PMECC5_0                    (0xF80140C4U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 0) */
  #define REG_HSMC_PMECC6_0                    (0xF80140C8U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 0) */
  #define REG_HSMC_PMECC7_0                    (0xF80140CCU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 0) */
  #define REG_HSMC_PMECC8_0                    (0xF80140D0U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 0) */
  #define REG_HSMC_PMECC9_0                    (0xF80140D4U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 0) */
  #define REG_HSMC_PMECC10_0                   (0xF80140D8U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 0) */
  #define REG_HSMC_PMECC11_0                   (0xF80140DCU) /**< \brief (HSMC) PMECC Redundancy 11 Register (sec_num = 0) */
  #define REG_HSMC_PMECC12_0                   (0xF80140E0U) /**< \brief (HSMC) PMECC Redundancy 12 Register (sec_num = 0) */
  #define REG_HSMC_PMECC13_0                   (0xF80140E4U) /**< \brief (HSMC) PMECC Redundancy 13 Register (sec_num = 0) */
  #define REG_HSMC_PMECC0_1                    (0xF80140F0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 1) */
  #define REG_HSMC_PMECC1_1                    (0xF80140F4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 1) */
  #define REG_HSMC_PMECC2_1                    (0xF80140F8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 1) */
  #define REG_HSMC_PMECC3_1                    (0xF80140FCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 1) */
  #define REG_HSMC_PMECC4_1                    (0xF8014100U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 1) */
  #define REG_HSMC_PMECC5_1                    (0xF8014104U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 1) */
  #define REG_HSMC_PMECC6_1                    (0xF8014108U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 1) */
  #define REG_HSMC_PMECC7_1                    (0xF801410CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 1) */
  #define REG_HSMC_PMECC8_1                    (0xF8014110U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 1) */
  #define REG_HSMC_PMECC9_1                    (0xF8014114U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 1) */
  #define REG_HSMC_PMECC10_1                   (0xF8014118U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 1) */
  #define REG_HSMC_PMECC11_1                   (0xF801411CU) /**< \brief (HSMC) PMECC Redundancy 11 Register (sec_num = 1) */
  #define REG_HSMC_PMECC12_1                   (0xF8014120U) /**< \brief (HSMC) PMECC Redundancy 12 Register (sec_num = 1) */
  #define REG_HSMC_PMECC13_1                   (0xF8014124U) /**< \brief (HSMC) PMECC Redundancy 13 Register (sec_num = 1) */
  #define REG_HSMC_PMECC0_2                    (0xF8014130U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 2) */
  #define REG_HSMC_PMECC1_2                    (0xF8014134U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 2) */
  #define REG_HSMC_PMECC2_2                    (0xF8014138U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 2) */
  #define REG_HSMC_PMECC3_2                    (0xF801413CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 2) */
  #define REG_HSMC_PMECC4_2                    (0xF8014140U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 2) */
  #define REG_HSMC_PMECC5_2                    (0xF8014144U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 2) */
  #define REG_HSMC_PMECC6_2                    (0xF8014148U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 2) */
  #define REG_HSMC_PMECC7_2                    (0xF801414CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 2) */
  #define REG_HSMC_PMECC8_2                    (0xF8014150U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 2) */
  #define REG_HSMC_PMECC9_2                    (0xF8014154U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 2) */
  #define REG_HSMC_PMECC10_2                   (0xF8014158U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 2) */
  #define REG_HSMC_PMECC11_2                   (0xF801415CU) /**< \brief (HSMC) PMECC Redundancy 11 Register (sec_num = 2) */
  #define REG_HSMC_PMECC12_2                   (0xF8014160U) /**< \brief (HSMC) PMECC Redundancy 12 Register (sec_num = 2) */
  #define REG_HSMC_PMECC13_2                   (0xF8014164U) /**< \brief (HSMC) PMECC Redundancy 13 Register (sec_num = 2) */
  #define REG_HSMC_PMECC0_3                    (0xF8014170U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 3) */
  #define REG_HSMC_PMECC1_3                    (0xF8014174U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 3) */
  #define REG_HSMC_PMECC2_3                    (0xF8014178U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 3) */
  #define REG_HSMC_PMECC3_3                    (0xF801417CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 3) */
  #define REG_HSMC_PMECC4_3                    (0xF8014180U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 3) */
  #define REG_HSMC_PMECC5_3                    (0xF8014184U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 3) */
  #define REG_HSMC_PMECC6_3                    (0xF8014188U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 3) */
  #define REG_HSMC_PMECC7_3                    (0xF801418CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 3) */
  #define REG_HSMC_PMECC8_3                    (0xF8014190U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 3) */
  #define REG_HSMC_PMECC9_3                    (0xF8014194U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 3) */
  #define REG_HSMC_PMECC10_3                   (0xF8014198U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 3) */
  #define REG_HSMC_PMECC11_3                   (0xF801419CU) /**< \brief (HSMC) PMECC Redundancy 11 Register (sec_num = 3) */
  #define REG_HSMC_PMECC12_3                   (0xF80141A0U) /**< \brief (HSMC) PMECC Redundancy 12 Register (sec_num = 3) */
  #define REG_HSMC_PMECC13_3                   (0xF80141A4U) /**< \brief (HSMC) PMECC Redundancy 13 Register (sec_num = 3) */
  #define REG_HSMC_PMECC0_4                    (0xF80141B0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 4) */
  #define REG_HSMC_PMECC1_4                    (0xF80141B4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 4) */
  #define REG_HSMC_PMECC2_4                    (0xF80141B8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 4) */
  #define REG_HSMC_PMECC3_4                    (0xF80141BCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 4) */
  #define REG_HSMC_PMECC4_4                    (0xF80141C0U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 4) */
  #define REG_HSMC_PMECC5_4                    (0xF80141C4U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 4) */
  #define REG_HSMC_PMECC6_4                    (0xF80141C8U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 4) */
  #define REG_HSMC_PMECC7_4                    (0xF80141CCU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 4) */
  #define REG_HSMC_PMECC8_4                    (0xF80141D0U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 4) */
  #define REG_HSMC_PMECC9_4                    (0xF80141D4U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 4) */
  #define REG_HSMC_PMECC10_4                   (0xF80141D8U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 4) */
  #define REG_HSMC_PMECC11_4                   (0xF80141DCU) /**< \brief (HSMC) PMECC Redundancy 11 Register (sec_num = 4) */
  #define REG_HSMC_PMECC12_4                   (0xF80141E0U) /**< \brief (HSMC) PMECC Redundancy 12 Register (sec_num = 4) */
  #define REG_HSMC_PMECC13_4                   (0xF80141E4U) /**< \brief (HSMC) PMECC Redundancy 13 Register (sec_num = 4) */
  #define REG_HSMC_PMECC0_5                    (0xF80141F0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 5) */
  #define REG_HSMC_PMECC1_5                    (0xF80141F4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 5) */
  #define REG_HSMC_PMECC2_5                    (0xF80141F8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 5) */
  #define REG_HSMC_PMECC3_5                    (0xF80141FCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 5) */
  #define REG_HSMC_PMECC4_5                    (0xF8014200U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 5) */
  #define REG_HSMC_PMECC5_5                    (0xF8014204U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 5) */
  #define REG_HSMC_PMECC6_5                    (0xF8014208U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 5) */
  #define REG_HSMC_PMECC7_5                    (0xF801420CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 5) */
  #define REG_HSMC_PMECC8_5                    (0xF8014210U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 5) */
  #define REG_HSMC_PMECC9_5                    (0xF8014214U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 5) */
  #define REG_HSMC_PMECC10_5                   (0xF8014218U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 5) */
  #define REG_HSMC_PMECC11_5                   (0xF801421CU) /**< \brief (HSMC) PMECC Redundancy 11 Register (sec_num = 5) */
  #define REG_HSMC_PMECC12_5                   (0xF8014220U) /**< \brief (HSMC) PMECC Redundancy 12 Register (sec_num = 5) */
  #define REG_HSMC_PMECC13_5                   (0xF8014224U) /**< \brief (HSMC) PMECC Redundancy 13 Register (sec_num = 5) */
  #define REG_HSMC_PMECC0_6                    (0xF8014230U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 6) */
  #define REG_HSMC_PMECC1_6                    (0xF8014234U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 6) */
  #define REG_HSMC_PMECC2_6                    (0xF8014238U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 6) */
  #define REG_HSMC_PMECC3_6                    (0xF801423CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 6) */
  #define REG_HSMC_PMECC4_6                    (0xF8014240U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 6) */
  #define REG_HSMC_PMECC5_6                    (0xF8014244U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 6) */
  #define REG_HSMC_PMECC6_6                    (0xF8014248U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 6) */
  #define REG_HSMC_PMECC7_6                    (0xF801424CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 6) */
  #define REG_HSMC_PMECC8_6                    (0xF8014250U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 6) */
  #define REG_HSMC_PMECC9_6                    (0xF8014254U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 6) */
  #define REG_HSMC_PMECC10_6                   (0xF8014258U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 6) */
  #define REG_HSMC_PMECC11_6                   (0xF801425CU) /**< \brief (HSMC) PMECC Redundancy 11 Register (sec_num = 6) */
  #define REG_HSMC_PMECC12_6                   (0xF8014260U) /**< \brief (HSMC) PMECC Redundancy 12 Register (sec_num = 6) */
  #define REG_HSMC_PMECC13_6                   (0xF8014264U) /**< \brief (HSMC) PMECC Redundancy 13 Register (sec_num = 6) */
  #define REG_HSMC_PMECC0_7                    (0xF8014270U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 7) */
  #define REG_HSMC_PMECC1_7                    (0xF8014274U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 7) */
  #define REG_HSMC_PMECC2_7                    (0xF8014278U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 7) */
  #define REG_HSMC_PMECC3_7                    (0xF801427CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 7) */
  #define REG_HSMC_PMECC4_7                    (0xF8014280U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 7) */
  #define REG_HSMC_PMECC5_7                    (0xF8014284U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 7) */
  #define REG_HSMC_PMECC6_7                    (0xF8014288U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 7) */
  #define REG_HSMC_PMECC7_7                    (0xF801428CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 7) */
  #define REG_HSMC_PMECC8_7                    (0xF8014290U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 7) */
  #define REG_HSMC_PMECC9_7                    (0xF8014294U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 7) */
  #define REG_HSMC_PMECC10_7                   (0xF8014298U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 7) */
  #define REG_HSMC_PMECC11_7                   (0xF801429CU) /**< \brief (HSMC) PMECC Redundancy 11 Register (sec_num = 7) */
  #define REG_HSMC_PMECC12_7                   (0xF80142A0U) /**< \brief (HSMC) PMECC Redundancy 12 Register (sec_num = 7) */
  #define REG_HSMC_PMECC13_7                   (0xF80142A4U) /**< \brief (HSMC) PMECC Redundancy 13 Register (sec_num = 7) */
  #define REG_HSMC_REM0_0                      (0xF80142B0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 0) */
  #define REG_HSMC_REM1_0                      (0xF80142B4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 0) */
  #define REG_HSMC_REM2_0                      (0xF80142B8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 0) */
  #define REG_HSMC_REM3_0                      (0xF80142BCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 0) */
  #define REG_HSMC_REM4_0                      (0xF80142C0U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 0) */
  #define REG_HSMC_REM5_0                      (0xF80142C4U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 0) */
  #define REG_HSMC_REM6_0                      (0xF80142C8U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 0) */
  #define REG_HSMC_REM7_0                      (0xF80142CCU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 0) */
  #define REG_HSMC_REM8_0                      (0xF80142D0U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 0) */
  #define REG_HSMC_REM9_0                      (0xF80142D4U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 0) */
  #define REG_HSMC_REM10_0                     (0xF80142D8U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 0) */
  #define REG_HSMC_REM11_0                     (0xF80142DCU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 0) */
  #define REG_HSMC_REM12_0                     (0xF80142E0U) /**< \brief (HSMC) PMECC Remainder 12 Register (sec_num = 0) */
  #define REG_HSMC_REM13_0                     (0xF80142E4U) /**< \brief (HSMC) PMECC Remainder 13 Register (sec_num = 0) */
  #define REG_HSMC_REM14_0                     (0xF80142E8U) /**< \brief (HSMC) PMECC Remainder 14 Register (sec_num = 0) */
  #define REG_HSMC_REM15_0                     (0xF80142ECU) /**< \brief (HSMC) PMECC Remainder 15 Register (sec_num = 0) */
  #define REG_HSMC_REM0_1                      (0xF80142F0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 1) */
  #define REG_HSMC_REM1_1                      (0xF80142F4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 1) */
  #define REG_HSMC_REM2_1                      (0xF80142F8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 1) */
  #define REG_HSMC_REM3_1                      (0xF80142FCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 1) */
  #define REG_HSMC_REM4_1                      (0xF8014300U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 1) */
  #define REG_HSMC_REM5_1                      (0xF8014304U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 1) */
  #define REG_HSMC_REM6_1                      (0xF8014308U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 1) */
  #define REG_HSMC_REM7_1                      (0xF801430CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 1) */
  #define REG_HSMC_REM8_1                      (0xF8014310U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 1) */
  #define REG_HSMC_REM9_1                      (0xF8014314U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 1) */
  #define REG_HSMC_REM10_1                     (0xF8014318U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 1) */
  #define REG_HSMC_REM11_1                     (0xF801431CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 1) */
  #define REG_HSMC_REM12_1                     (0xF8014320U) /**< \brief (HSMC) PMECC Remainder 12 Register (sec_num = 1) */
  #define REG_HSMC_REM13_1                     (0xF8014324U) /**< \brief (HSMC) PMECC Remainder 13 Register (sec_num = 1) */
  #define REG_HSMC_REM14_1                     (0xF8014328U) /**< \brief (HSMC) PMECC Remainder 14 Register (sec_num = 1) */
  #define REG_HSMC_REM15_1                     (0xF801432CU) /**< \brief (HSMC) PMECC Remainder 15 Register (sec_num = 1) */
  #define REG_HSMC_REM0_2                      (0xF8014330U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 2) */
  #define REG_HSMC_REM1_2                      (0xF8014334U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 2) */
  #define REG_HSMC_REM2_2                      (0xF8014338U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 2) */
  #define REG_HSMC_REM3_2                      (0xF801433CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 2) */
  #define REG_HSMC_REM4_2                      (0xF8014340U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 2) */
  #define REG_HSMC_REM5_2                      (0xF8014344U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 2) */
  #define REG_HSMC_REM6_2                      (0xF8014348U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 2) */
  #define REG_HSMC_REM7_2                      (0xF801434CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 2) */
  #define REG_HSMC_REM8_2                      (0xF8014350U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 2) */
  #define REG_HSMC_REM9_2                      (0xF8014354U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 2) */
  #define REG_HSMC_REM10_2                     (0xF8014358U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 2) */
  #define REG_HSMC_REM11_2                     (0xF801435CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 2) */
  #define REG_HSMC_REM12_2                     (0xF8014360U) /**< \brief (HSMC) PMECC Remainder 12 Register (sec_num = 2) */
  #define REG_HSMC_REM13_2                     (0xF8014364U) /**< \brief (HSMC) PMECC Remainder 13 Register (sec_num = 2) */
  #define REG_HSMC_REM14_2                     (0xF8014368U) /**< \brief (HSMC) PMECC Remainder 14 Register (sec_num = 2) */
  #define REG_HSMC_REM15_2                     (0xF801436CU) /**< \brief (HSMC) PMECC Remainder 15 Register (sec_num = 2) */
  #define REG_HSMC_REM0_3                      (0xF8014370U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 3) */
  #define REG_HSMC_REM1_3                      (0xF8014374U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 3) */
  #define REG_HSMC_REM2_3                      (0xF8014378U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 3) */
  #define REG_HSMC_REM3_3                      (0xF801437CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 3) */
  #define REG_HSMC_REM4_3                      (0xF8014380U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 3) */
  #define REG_HSMC_REM5_3                      (0xF8014384U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 3) */
  #define REG_HSMC_REM6_3                      (0xF8014388U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 3) */
  #define REG_HSMC_REM7_3                      (0xF801438CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 3) */
  #define REG_HSMC_REM8_3                      (0xF8014390U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 3) */
  #define REG_HSMC_REM9_3                      (0xF8014394U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 3) */
  #define REG_HSMC_REM10_3                     (0xF8014398U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 3) */
  #define REG_HSMC_REM11_3                     (0xF801439CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 3) */
  #define REG_HSMC_REM12_3                     (0xF80143A0U) /**< \brief (HSMC) PMECC Remainder 12 Register (sec_num = 3) */
  #define REG_HSMC_REM13_3                     (0xF80143A4U) /**< \brief (HSMC) PMECC Remainder 13 Register (sec_num = 3) */
  #define REG_HSMC_REM14_3                     (0xF80143A8U) /**< \brief (HSMC) PMECC Remainder 14 Register (sec_num = 3) */
  #define REG_HSMC_REM15_3                     (0xF80143ACU) /**< \brief (HSMC) PMECC Remainder 15 Register (sec_num = 3) */
  #define REG_HSMC_REM0_4                      (0xF80143B0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 4) */
  #define REG_HSMC_REM1_4                      (0xF80143B4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 4) */
  #define REG_HSMC_REM2_4                      (0xF80143B8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 4) */
  #define REG_HSMC_REM3_4                      (0xF80143BCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 4) */
  #define REG_HSMC_REM4_4                      (0xF80143C0U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 4) */
  #define REG_HSMC_REM5_4                      (0xF80143C4U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 4) */
  #define REG_HSMC_REM6_4                      (0xF80143C8U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 4) */
  #define REG_HSMC_REM7_4                      (0xF80143CCU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 4) */
  #define REG_HSMC_REM8_4                      (0xF80143D0U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 4) */
  #define REG_HSMC_REM9_4                      (0xF80143D4U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 4) */
  #define REG_HSMC_REM10_4                     (0xF80143D8U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 4) */
  #define REG_HSMC_REM11_4                     (0xF80143DCU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 4) */
  #define REG_HSMC_REM12_4                     (0xF80143E0U) /**< \brief (HSMC) PMECC Remainder 12 Register (sec_num = 4) */
  #define REG_HSMC_REM13_4                     (0xF80143E4U) /**< \brief (HSMC) PMECC Remainder 13 Register (sec_num = 4) */
  #define REG_HSMC_REM14_4                     (0xF80143E8U) /**< \brief (HSMC) PMECC Remainder 14 Register (sec_num = 4) */
  #define REG_HSMC_REM15_4                     (0xF80143ECU) /**< \brief (HSMC) PMECC Remainder 15 Register (sec_num = 4) */
  #define REG_HSMC_REM0_5                      (0xF80143F0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 5) */
  #define REG_HSMC_REM1_5                      (0xF80143F4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 5) */
  #define REG_HSMC_REM2_5                      (0xF80143F8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 5) */
  #define REG_HSMC_REM3_5                      (0xF80143FCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 5) */
  #define REG_HSMC_REM4_5                      (0xF8014400U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 5) */
  #define REG_HSMC_REM5_5                      (0xF8014404U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 5) */
  #define REG_HSMC_REM6_5                      (0xF8014408U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 5) */
  #define REG_HSMC_REM7_5                      (0xF801440CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 5) */
  #define REG_HSMC_REM8_5                      (0xF8014410U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 5) */
  #define REG_HSMC_REM9_5                      (0xF8014414U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 5) */
  #define REG_HSMC_REM10_5                     (0xF8014418U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 5) */
  #define REG_HSMC_REM11_5                     (0xF801441CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 5) */
  #define REG_HSMC_REM12_5                     (0xF8014420U) /**< \brief (HSMC) PMECC Remainder 12 Register (sec_num = 5) */
  #define REG_HSMC_REM13_5                     (0xF8014424U) /**< \brief (HSMC) PMECC Remainder 13 Register (sec_num = 5) */
  #define REG_HSMC_REM14_5                     (0xF8014428U) /**< \brief (HSMC) PMECC Remainder 14 Register (sec_num = 5) */
  #define REG_HSMC_REM15_5                     (0xF801442CU) /**< \brief (HSMC) PMECC Remainder 15 Register (sec_num = 5) */
  #define REG_HSMC_REM0_6                      (0xF8014430U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 6) */
  #define REG_HSMC_REM1_6                      (0xF8014434U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 6) */
  #define REG_HSMC_REM2_6                      (0xF8014438U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 6) */
  #define REG_HSMC_REM3_6                      (0xF801443CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 6) */
  #define REG_HSMC_REM4_6                      (0xF8014440U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 6) */
  #define REG_HSMC_REM5_6                      (0xF8014444U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 6) */
  #define REG_HSMC_REM6_6                      (0xF8014448U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 6) */
  #define REG_HSMC_REM7_6                      (0xF801444CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 6) */
  #define REG_HSMC_REM8_6                      (0xF8014450U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 6) */
  #define REG_HSMC_REM9_6                      (0xF8014454U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 6) */
  #define REG_HSMC_REM10_6                     (0xF8014458U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 6) */
  #define REG_HSMC_REM11_6                     (0xF801445CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 6) */
  #define REG_HSMC_REM12_6                     (0xF8014460U) /**< \brief (HSMC) PMECC Remainder 12 Register (sec_num = 6) */
  #define REG_HSMC_REM13_6                     (0xF8014464U) /**< \brief (HSMC) PMECC Remainder 13 Register (sec_num = 6) */
  #define REG_HSMC_REM14_6                     (0xF8014468U) /**< \brief (HSMC) PMECC Remainder 14 Register (sec_num = 6) */
  #define REG_HSMC_REM15_6                     (0xF801446CU) /**< \brief (HSMC) PMECC Remainder 15 Register (sec_num = 6) */
  #define REG_HSMC_REM0_7                      (0xF8014470U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 7) */
  #define REG_HSMC_REM1_7                      (0xF8014474U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 7) */
  #define REG_HSMC_REM2_7                      (0xF8014478U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 7) */
  #define REG_HSMC_REM3_7                      (0xF801447CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 7) */
  #define REG_HSMC_REM4_7                      (0xF8014480U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 7) */
  #define REG_HSMC_REM5_7                      (0xF8014484U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 7) */
  #define REG_HSMC_REM6_7                      (0xF8014488U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 7) */
  #define REG_HSMC_REM7_7                      (0xF801448CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 7) */
  #define REG_HSMC_REM8_7                      (0xF8014490U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 7) */
  #define REG_HSMC_REM9_7                      (0xF8014494U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 7) */
  #define REG_HSMC_REM10_7                     (0xF8014498U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 7) */
  #define REG_HSMC_REM11_7                     (0xF801449CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 7) */
  #define REG_HSMC_REM12_7                     (0xF80144A0U) /**< \brief (HSMC) PMECC Remainder 12 Register (sec_num = 7) */
  #define REG_HSMC_REM13_7                     (0xF80144A4U) /**< \brief (HSMC) PMECC Remainder 13 Register (sec_num = 7) */
  #define REG_HSMC_REM14_7                     (0xF80144A8U) /**< \brief (HSMC) PMECC Remainder 14 Register (sec_num = 7) */
  #define REG_HSMC_REM15_7                     (0xF80144ACU) /**< \brief (HSMC) PMECC Remainder 15 Register (sec_num = 7) */
  #define REG_HSMC_ELCFG                       (0xF8014500U) /**< \brief (HSMC) PMECC Error Location Configuration Register */
  #define REG_HSMC_ELPRIM                      (0xF8014504U) /**< \brief (HSMC) PMECC Error Location Primitive Register */
  #define REG_HSMC_ELEN                        (0xF8014508U) /**< \brief (HSMC) PMECC Error Location Enable Register */
  #define REG_HSMC_ELDIS                       (0xF801450CU) /**< \brief (HSMC) PMECC Error Location Disable Register */
  #define REG_HSMC_ELSR                        (0xF8014510U) /**< \brief (HSMC) PMECC Error Location Status Register */
  #define REG_HSMC_ELIER                       (0xF8014514U) /**< \brief (HSMC) PMECC Error Location Interrupt Enable register */
  #define REG_HSMC_ELIDR                       (0xF8014518U) /**< \brief (HSMC) PMECC Error Location Interrupt Disable Register */
  #define REG_HSMC_ELIMR                       (0xF801451CU) /**< \brief (HSMC) PMECC Error Location Interrupt Mask Register */
  #define REG_HSMC_ELISR                       (0xF8014520U) /**< \brief (HSMC) PMECC Error Location Interrupt Status Register */
  #define REG_HSMC_SIGMA0                      (0xF8014528U) /**< \brief (HSMC) PMECC Error Location SIGMA 0 Register */
  #define REG_HSMC_SIGMA1                      (0xF801452CU) /**< \brief (HSMC) PMECC Error Location SIGMA 1 Register */
  #define REG_HSMC_SIGMA2                      (0xF8014530U) /**< \brief (HSMC) PMECC Error Location SIGMA 2 Register */
  #define REG_HSMC_SIGMA3                      (0xF8014534U) /**< \brief (HSMC) PMECC Error Location SIGMA 3 Register */
  #define REG_HSMC_SIGMA4                      (0xF8014538U) /**< \brief (HSMC) PMECC Error Location SIGMA 4 Register */
  #define REG_HSMC_SIGMA5                      (0xF801453CU) /**< \brief (HSMC) PMECC Error Location SIGMA 5 Register */
  #define REG_HSMC_SIGMA6                      (0xF8014540U) /**< \brief (HSMC) PMECC Error Location SIGMA 6 Register */
  #define REG_HSMC_SIGMA7                      (0xF8014544U) /**< \brief (HSMC) PMECC Error Location SIGMA 7 Register */
  #define REG_HSMC_SIGMA8                      (0xF8014548U) /**< \brief (HSMC) PMECC Error Location SIGMA 8 Register */
  #define REG_HSMC_SIGMA9                      (0xF801454CU) /**< \brief (HSMC) PMECC Error Location SIGMA 9 Register */
  #define REG_HSMC_SIGMA10                     (0xF8014550U) /**< \brief (HSMC) PMECC Error Location SIGMA 10 Register */
  #define REG_HSMC_SIGMA11                     (0xF8014554U) /**< \brief (HSMC) PMECC Error Location SIGMA 11 Register */
  #define REG_HSMC_SIGMA12                     (0xF8014558U) /**< \brief (HSMC) PMECC Error Location SIGMA 12 Register */
  #define REG_HSMC_SIGMA13                     (0xF801455CU) /**< \brief (HSMC) PMECC Error Location SIGMA 13 Register */
  #define REG_HSMC_SIGMA14                     (0xF8014560U) /**< \brief (HSMC) PMECC Error Location SIGMA 14 Register */
  #define REG_HSMC_SIGMA15                     (0xF8014564U) /**< \brief (HSMC) PMECC Error Location SIGMA 15 Register */
  #define REG_HSMC_SIGMA16                     (0xF8014568U) /**< \brief (HSMC) PMECC Error Location SIGMA 16 Register */
  #define REG_HSMC_SIGMA17                     (0xF801456CU) /**< \brief (HSMC) PMECC Error Location SIGMA 17 Register */
  #define REG_HSMC_SIGMA18                     (0xF8014570U) /**< \brief (HSMC) PMECC Error Location SIGMA 18 Register */
  #define REG_HSMC_SIGMA19                     (0xF8014574U) /**< \brief (HSMC) PMECC Error Location SIGMA 19 Register */
  #define REG_HSMC_SIGMA20                     (0xF8014578U) /**< \brief (HSMC) PMECC Error Location SIGMA 20 Register */
  #define REG_HSMC_SIGMA21                     (0xF801457CU) /**< \brief (HSMC) PMECC Error Location SIGMA 21 Register */
  #define REG_HSMC_SIGMA22                     (0xF8014580U) /**< \brief (HSMC) PMECC Error Location SIGMA 22 Register */
  #define REG_HSMC_SIGMA23                     (0xF8014584U) /**< \brief (HSMC) PMECC Error Location SIGMA 23 Register */
  #define REG_HSMC_SIGMA24                     (0xF8014588U) /**< \brief (HSMC) PMECC Error Location SIGMA 24 Register */
  #define REG_HSMC_SIGMA25                     (0xF801458CU) /**< \brief (HSMC) PMECC Error Location SIGMA 25 Register */
  #define REG_HSMC_SIGMA26                     (0xF8014590U) /**< \brief (HSMC) PMECC Error Location SIGMA 26 Register */
  #define REG_HSMC_SIGMA27                     (0xF8014594U) /**< \brief (HSMC) PMECC Error Location SIGMA 27 Register */
  #define REG_HSMC_SIGMA28                     (0xF8014598U) /**< \brief (HSMC) PMECC Error Location SIGMA 28 Register */
  #define REG_HSMC_SIGMA29                     (0xF801459CU) /**< \brief (HSMC) PMECC Error Location SIGMA 29 Register */
  #define REG_HSMC_SIGMA30                     (0xF80145A0U) /**< \brief (HSMC) PMECC Error Location SIGMA 30 Register */
  #define REG_HSMC_SIGMA31                     (0xF80145A4U) /**< \brief (HSMC) PMECC Error Location SIGMA 31 Register */
  #define REG_HSMC_SIGMA32                     (0xF80145A8U) /**< \brief (HSMC) PMECC Error Location SIGMA 32 Register */
  #define REG_HSMC_ERRLOC0                     (0xF80145ACU) /**< \brief (HSMC) PMECC Error Location 0 Register */
  #define REG_HSMC_ERRLOC1                     (0xF80145B0U) /**< \brief (HSMC) PMECC Error Location 1 Register */
  #define REG_HSMC_ERRLOC2                     (0xF80145B4U) /**< \brief (HSMC) PMECC Error Location 2 Register */
  #define REG_HSMC_ERRLOC3                     (0xF80145B8U) /**< \brief (HSMC) PMECC Error Location 3 Register */
  #define REG_HSMC_ERRLOC4                     (0xF80145BCU) /**< \brief (HSMC) PMECC Error Location 4 Register */
  #define REG_HSMC_ERRLOC5                     (0xF80145C0U) /**< \brief (HSMC) PMECC Error Location 5 Register */
  #define REG_HSMC_ERRLOC6                     (0xF80145C4U) /**< \brief (HSMC) PMECC Error Location 6 Register */
  #define REG_HSMC_ERRLOC7                     (0xF80145C8U) /**< \brief (HSMC) PMECC Error Location 7 Register */
  #define REG_HSMC_ERRLOC8                     (0xF80145CCU) /**< \brief (HSMC) PMECC Error Location 8 Register */
  #define REG_HSMC_ERRLOC9                     (0xF80145D0U) /**< \brief (HSMC) PMECC Error Location 9 Register */
  #define REG_HSMC_ERRLOC10                    (0xF80145D4U) /**< \brief (HSMC) PMECC Error Location 10 Register */
  #define REG_HSMC_ERRLOC11                    (0xF80145D8U) /**< \brief (HSMC) PMECC Error Location 11 Register */
  #define REG_HSMC_ERRLOC12                    (0xF80145DCU) /**< \brief (HSMC) PMECC Error Location 12 Register */
  #define REG_HSMC_ERRLOC13                    (0xF80145E0U) /**< \brief (HSMC) PMECC Error Location 13 Register */
  #define REG_HSMC_ERRLOC14                    (0xF80145E4U) /**< \brief (HSMC) PMECC Error Location 14 Register */
  #define REG_HSMC_ERRLOC15                    (0xF80145E8U) /**< \brief (HSMC) PMECC Error Location 15 Register */
  #define REG_HSMC_ERRLOC16                    (0xF80145ECU) /**< \brief (HSMC) PMECC Error Location 16 Register */
  #define REG_HSMC_ERRLOC17                    (0xF80145F0U) /**< \brief (HSMC) PMECC Error Location 17 Register */
  #define REG_HSMC_ERRLOC18                    (0xF80145F4U) /**< \brief (HSMC) PMECC Error Location 18 Register */
  #define REG_HSMC_ERRLOC19                    (0xF80145F8U) /**< \brief (HSMC) PMECC Error Location 19 Register */
  #define REG_HSMC_ERRLOC20                    (0xF80145FCU) /**< \brief (HSMC) PMECC Error Location 20 Register */
  #define REG_HSMC_ERRLOC21                    (0xF8014600U) /**< \brief (HSMC) PMECC Error Location 21 Register */
  #define REG_HSMC_ERRLOC22                    (0xF8014604U) /**< \brief (HSMC) PMECC Error Location 22 Register */
  #define REG_HSMC_ERRLOC23                    (0xF8014608U) /**< \brief (HSMC) PMECC Error Location 23 Register */
  #define REG_HSMC_ERRLOC24                    (0xF801460CU) /**< \brief (HSMC) PMECC Error Location 24 Register */
  #define REG_HSMC_ERRLOC25                    (0xF8014610U) /**< \brief (HSMC) PMECC Error Location 25 Register */
  #define REG_HSMC_ERRLOC26                    (0xF8014614U) /**< \brief (HSMC) PMECC Error Location 26 Register */
  #define REG_HSMC_ERRLOC27                    (0xF8014618U) /**< \brief (HSMC) PMECC Error Location 27 Register */
  #define REG_HSMC_ERRLOC28                    (0xF801461CU) /**< \brief (HSMC) PMECC Error Location 28 Register */
  #define REG_HSMC_ERRLOC29                    (0xF8014620U) /**< \brief (HSMC) PMECC Error Location 29 Register */
  #define REG_HSMC_ERRLOC30                    (0xF8014624U) /**< \brief (HSMC) PMECC Error Location 30 Register */
  #define REG_HSMC_ERRLOC31                    (0xF8014628U) /**< \brief (HSMC) PMECC Error Location 31 Register */
  #define REG_HSMC_SETUP0                      (0xF8014700U) /**< \brief (HSMC) HSMC Setup Register (CS_number = 0) */
  #define REG_HSMC_PULSE0                      (0xF8014704U) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 0) */
  #define REG_HSMC_CYCLE0                      (0xF8014708U) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 0) */
  #define REG_HSMC_TIMINGS0                    (0xF801470CU) /**< \brief (HSMC) HSMC Timings Register (CS_number = 0) */
  #define REG_HSMC_MODE0                       (0xF8014710U) /**< \brief (HSMC) HSMC Mode Register (CS_number = 0) */
  #define REG_HSMC_SETUP1                      (0xF8014714U) /**< \brief (HSMC) HSMC Setup Register (CS_number = 1) */
  #define REG_HSMC_PULSE1                      (0xF8014718U) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 1) */
  #define REG_HSMC_CYCLE1                      (0xF801471CU) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 1) */
  #define REG_HSMC_TIMINGS1                    (0xF8014720U) /**< \brief (HSMC) HSMC Timings Register (CS_number = 1) */
  #define REG_HSMC_MODE1                       (0xF8014724U) /**< \brief (HSMC) HSMC Mode Register (CS_number = 1) */
  #define REG_HSMC_SETUP2                      (0xF8014728U) /**< \brief (HSMC) HSMC Setup Register (CS_number = 2) */
  #define REG_HSMC_PULSE2                      (0xF801472CU) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 2) */
  #define REG_HSMC_CYCLE2                      (0xF8014730U) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 2) */
  #define REG_HSMC_TIMINGS2                    (0xF8014734U) /**< \brief (HSMC) HSMC Timings Register (CS_number = 2) */
  #define REG_HSMC_MODE2                       (0xF8014738U) /**< \brief (HSMC) HSMC Mode Register (CS_number = 2) */
  #define REG_HSMC_SETUP3                      (0xF801473CU) /**< \brief (HSMC) HSMC Setup Register (CS_number = 3) */
  #define REG_HSMC_PULSE3                      (0xF8014740U) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 3) */
  #define REG_HSMC_CYCLE3                      (0xF8014744U) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 3) */
  #define REG_HSMC_TIMINGS3                    (0xF8014748U) /**< \brief (HSMC) HSMC Timings Register (CS_number = 3) */
  #define REG_HSMC_MODE3                       (0xF801474CU) /**< \brief (HSMC) HSMC Mode Register (CS_number = 3) */
  #define REG_HSMC_OCMS                        (0xF80147A0U) /**< \brief (HSMC) HSMC Off Chip Memory Scrambling Register */
  #define REG_HSMC_KEY1                        (0xF80147A4U) /**< \brief (HSMC) HSMC Off Chip Memory Scrambling KEY1 Register */
  #define REG_HSMC_KEY2                        (0xF80147A8U) /**< \brief (HSMC) HSMC Off Chip Memory Scrambling KEY2 Register */
  #define REG_HSMC_WPMR                        (0xF80147E4U) /**< \brief (HSMC) HSMC Write Protection Mode Register */
  #define REG_HSMC_WPSR                        (0xF80147E8U) /**< \brief (HSMC) HSMC Write Protection Status Register */
  #define REG_HSMC_VERSION                     (0xF80147FCU) /**< \brief (HSMC) HSMC Version Register */
#else
  #define REG_HSMC_CFG        (*(__IO uint32_t*)0xF8014000U) /**< \brief (HSMC) HSMC NFC Configuration Register */
  #define REG_HSMC_CTRL       (*(__O  uint32_t*)0xF8014004U) /**< \brief (HSMC) HSMC NFC Control Register */
  #define REG_HSMC_SR         (*(__I  uint32_t*)0xF8014008U) /**< \brief (HSMC) HSMC NFC Status Register */
  #define REG_HSMC_IER        (*(__O  uint32_t*)0xF801400CU) /**< \brief (HSMC) HSMC NFC Interrupt Enable Register */
  #define REG_HSMC_IDR        (*(__O  uint32_t*)0xF8014010U) /**< \brief (HSMC) HSMC NFC Interrupt Disable Register */
  #define REG_HSMC_IMR        (*(__I  uint32_t*)0xF8014014U) /**< \brief (HSMC) HSMC NFC Interrupt Mask Register */
  #define REG_HSMC_ADDR       (*(__IO uint32_t*)0xF8014018U) /**< \brief (HSMC) HSMC NFC Address Cycle Zero Register */
  #define REG_HSMC_BANK       (*(__IO uint32_t*)0xF801401CU) /**< \brief (HSMC) HSMC Bank Address Register */
  #define REG_HSMC_PMECCFG    (*(__IO uint32_t*)0xF8014070U) /**< \brief (HSMC) PMECC Configuration Register */
  #define REG_HSMC_PMECCSAREA (*(__IO uint32_t*)0xF8014074U) /**< \brief (HSMC) PMECC Spare Area Size Register */
  #define REG_HSMC_PMECCSADDR (*(__IO uint32_t*)0xF8014078U) /**< \brief (HSMC) PMECC Start Address Register */
  #define REG_HSMC_PMECCEADDR (*(__IO uint32_t*)0xF801407CU) /**< \brief (HSMC) PMECC End Address Register */
  #define REG_HSMC_PMECCTRL   (*(__O  uint32_t*)0xF8014084U) /**< \brief (HSMC) PMECC Control Register */
  #define REG_HSMC_PMECCSR    (*(__I  uint32_t*)0xF8014088U) /**< \brief (HSMC) PMECC Status Register */
  #define REG_HSMC_PMECCIER   (*(__O  uint32_t*)0xF801408CU) /**< \brief (HSMC) PMECC Interrupt Enable register */
  #define REG_HSMC_PMECCIDR   (*(__O  uint32_t*)0xF8014090U) /**< \brief (HSMC) PMECC Interrupt Disable Register */
  #define REG_HSMC_PMECCIMR   (*(__I  uint32_t*)0xF8014094U) /**< \brief (HSMC) PMECC Interrupt Mask Register */
  #define REG_HSMC_PMECCISR   (*(__I  uint32_t*)0xF8014098U) /**< \brief (HSMC) PMECC Interrupt Status Register */
  #define REG_HSMC_PMECC0_0   (*(__I  uint32_t*)0xF80140B0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 0) */
  #define REG_HSMC_PMECC1_0   (*(__I  uint32_t*)0xF80140B4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 0) */
  #define REG_HSMC_PMECC2_0   (*(__I  uint32_t*)0xF80140B8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 0) */
  #define REG_HSMC_PMECC3_0   (*(__I  uint32_t*)0xF80140BCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 0) */
  #define REG_HSMC_PMECC4_0   (*(__I  uint32_t*)0xF80140C0U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 0) */
  #define REG_HSMC_PMECC5_0   (*(__I  uint32_t*)0xF80140C4U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 0) */
  #define REG_HSMC_PMECC6_0   (*(__I  uint32_t*)0xF80140C8U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 0) */
  #define REG_HSMC_PMECC7_0   (*(__I  uint32_t*)0xF80140CCU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 0) */
  #define REG_HSMC_PMECC8_0   (*(__I  uint32_t*)0xF80140D0U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 0) */
  #define REG_HSMC_PMECC9_0   (*(__I  uint32_t*)0xF80140D4U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 0) */
  #define REG_HSMC_PMECC10_0  (*(__I  uint32_t*)0xF80140D8U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 0) */
  #define REG_HSMC_PMECC11_0  (*(__I  uint32_t*)0xF80140DCU) /**< \brief (HSMC) PMECC Redundancy 11 Register (sec_num = 0) */
  #define REG_HSMC_PMECC12_0  (*(__I  uint32_t*)0xF80140E0U) /**< \brief (HSMC) PMECC Redundancy 12 Register (sec_num = 0) */
  #define REG_HSMC_PMECC13_0  (*(__I  uint32_t*)0xF80140E4U) /**< \brief (HSMC) PMECC Redundancy 13 Register (sec_num = 0) */
  #define REG_HSMC_PMECC0_1   (*(__I  uint32_t*)0xF80140F0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 1) */
  #define REG_HSMC_PMECC1_1   (*(__I  uint32_t*)0xF80140F4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 1) */
  #define REG_HSMC_PMECC2_1   (*(__I  uint32_t*)0xF80140F8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 1) */
  #define REG_HSMC_PMECC3_1   (*(__I  uint32_t*)0xF80140FCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 1) */
  #define REG_HSMC_PMECC4_1   (*(__I  uint32_t*)0xF8014100U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 1) */
  #define REG_HSMC_PMECC5_1   (*(__I  uint32_t*)0xF8014104U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 1) */
  #define REG_HSMC_PMECC6_1   (*(__I  uint32_t*)0xF8014108U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 1) */
  #define REG_HSMC_PMECC7_1   (*(__I  uint32_t*)0xF801410CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 1) */
  #define REG_HSMC_PMECC8_1   (*(__I  uint32_t*)0xF8014110U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 1) */
  #define REG_HSMC_PMECC9_1   (*(__I  uint32_t*)0xF8014114U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 1) */
  #define REG_HSMC_PMECC10_1  (*(__I  uint32_t*)0xF8014118U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 1) */
  #define REG_HSMC_PMECC11_1  (*(__I  uint32_t*)0xF801411CU) /**< \brief (HSMC) PMECC Redundancy 11 Register (sec_num = 1) */
  #define REG_HSMC_PMECC12_1  (*(__I  uint32_t*)0xF8014120U) /**< \brief (HSMC) PMECC Redundancy 12 Register (sec_num = 1) */
  #define REG_HSMC_PMECC13_1  (*(__I  uint32_t*)0xF8014124U) /**< \brief (HSMC) PMECC Redundancy 13 Register (sec_num = 1) */
  #define REG_HSMC_PMECC0_2   (*(__I  uint32_t*)0xF8014130U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 2) */
  #define REG_HSMC_PMECC1_2   (*(__I  uint32_t*)0xF8014134U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 2) */
  #define REG_HSMC_PMECC2_2   (*(__I  uint32_t*)0xF8014138U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 2) */
  #define REG_HSMC_PMECC3_2   (*(__I  uint32_t*)0xF801413CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 2) */
  #define REG_HSMC_PMECC4_2   (*(__I  uint32_t*)0xF8014140U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 2) */
  #define REG_HSMC_PMECC5_2   (*(__I  uint32_t*)0xF8014144U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 2) */
  #define REG_HSMC_PMECC6_2   (*(__I  uint32_t*)0xF8014148U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 2) */
  #define REG_HSMC_PMECC7_2   (*(__I  uint32_t*)0xF801414CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 2) */
  #define REG_HSMC_PMECC8_2   (*(__I  uint32_t*)0xF8014150U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 2) */
  #define REG_HSMC_PMECC9_2   (*(__I  uint32_t*)0xF8014154U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 2) */
  #define REG_HSMC_PMECC10_2  (*(__I  uint32_t*)0xF8014158U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 2) */
  #define REG_HSMC_PMECC11_2  (*(__I  uint32_t*)0xF801415CU) /**< \brief (HSMC) PMECC Redundancy 11 Register (sec_num = 2) */
  #define REG_HSMC_PMECC12_2  (*(__I  uint32_t*)0xF8014160U) /**< \brief (HSMC) PMECC Redundancy 12 Register (sec_num = 2) */
  #define REG_HSMC_PMECC13_2  (*(__I  uint32_t*)0xF8014164U) /**< \brief (HSMC) PMECC Redundancy 13 Register (sec_num = 2) */
  #define REG_HSMC_PMECC0_3   (*(__I  uint32_t*)0xF8014170U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 3) */
  #define REG_HSMC_PMECC1_3   (*(__I  uint32_t*)0xF8014174U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 3) */
  #define REG_HSMC_PMECC2_3   (*(__I  uint32_t*)0xF8014178U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 3) */
  #define REG_HSMC_PMECC3_3   (*(__I  uint32_t*)0xF801417CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 3) */
  #define REG_HSMC_PMECC4_3   (*(__I  uint32_t*)0xF8014180U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 3) */
  #define REG_HSMC_PMECC5_3   (*(__I  uint32_t*)0xF8014184U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 3) */
  #define REG_HSMC_PMECC6_3   (*(__I  uint32_t*)0xF8014188U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 3) */
  #define REG_HSMC_PMECC7_3   (*(__I  uint32_t*)0xF801418CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 3) */
  #define REG_HSMC_PMECC8_3   (*(__I  uint32_t*)0xF8014190U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 3) */
  #define REG_HSMC_PMECC9_3   (*(__I  uint32_t*)0xF8014194U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 3) */
  #define REG_HSMC_PMECC10_3  (*(__I  uint32_t*)0xF8014198U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 3) */
  #define REG_HSMC_PMECC11_3  (*(__I  uint32_t*)0xF801419CU) /**< \brief (HSMC) PMECC Redundancy 11 Register (sec_num = 3) */
  #define REG_HSMC_PMECC12_3  (*(__I  uint32_t*)0xF80141A0U) /**< \brief (HSMC) PMECC Redundancy 12 Register (sec_num = 3) */
  #define REG_HSMC_PMECC13_3  (*(__I  uint32_t*)0xF80141A4U) /**< \brief (HSMC) PMECC Redundancy 13 Register (sec_num = 3) */
  #define REG_HSMC_PMECC0_4   (*(__I  uint32_t*)0xF80141B0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 4) */
  #define REG_HSMC_PMECC1_4   (*(__I  uint32_t*)0xF80141B4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 4) */
  #define REG_HSMC_PMECC2_4   (*(__I  uint32_t*)0xF80141B8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 4) */
  #define REG_HSMC_PMECC3_4   (*(__I  uint32_t*)0xF80141BCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 4) */
  #define REG_HSMC_PMECC4_4   (*(__I  uint32_t*)0xF80141C0U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 4) */
  #define REG_HSMC_PMECC5_4   (*(__I  uint32_t*)0xF80141C4U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 4) */
  #define REG_HSMC_PMECC6_4   (*(__I  uint32_t*)0xF80141C8U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 4) */
  #define REG_HSMC_PMECC7_4   (*(__I  uint32_t*)0xF80141CCU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 4) */
  #define REG_HSMC_PMECC8_4   (*(__I  uint32_t*)0xF80141D0U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 4) */
  #define REG_HSMC_PMECC9_4   (*(__I  uint32_t*)0xF80141D4U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 4) */
  #define REG_HSMC_PMECC10_4  (*(__I  uint32_t*)0xF80141D8U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 4) */
  #define REG_HSMC_PMECC11_4  (*(__I  uint32_t*)0xF80141DCU) /**< \brief (HSMC) PMECC Redundancy 11 Register (sec_num = 4) */
  #define REG_HSMC_PMECC12_4  (*(__I  uint32_t*)0xF80141E0U) /**< \brief (HSMC) PMECC Redundancy 12 Register (sec_num = 4) */
  #define REG_HSMC_PMECC13_4  (*(__I  uint32_t*)0xF80141E4U) /**< \brief (HSMC) PMECC Redundancy 13 Register (sec_num = 4) */
  #define REG_HSMC_PMECC0_5   (*(__I  uint32_t*)0xF80141F0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 5) */
  #define REG_HSMC_PMECC1_5   (*(__I  uint32_t*)0xF80141F4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 5) */
  #define REG_HSMC_PMECC2_5   (*(__I  uint32_t*)0xF80141F8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 5) */
  #define REG_HSMC_PMECC3_5   (*(__I  uint32_t*)0xF80141FCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 5) */
  #define REG_HSMC_PMECC4_5   (*(__I  uint32_t*)0xF8014200U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 5) */
  #define REG_HSMC_PMECC5_5   (*(__I  uint32_t*)0xF8014204U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 5) */
  #define REG_HSMC_PMECC6_5   (*(__I  uint32_t*)0xF8014208U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 5) */
  #define REG_HSMC_PMECC7_5   (*(__I  uint32_t*)0xF801420CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 5) */
  #define REG_HSMC_PMECC8_5   (*(__I  uint32_t*)0xF8014210U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 5) */
  #define REG_HSMC_PMECC9_5   (*(__I  uint32_t*)0xF8014214U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 5) */
  #define REG_HSMC_PMECC10_5  (*(__I  uint32_t*)0xF8014218U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 5) */
  #define REG_HSMC_PMECC11_5  (*(__I  uint32_t*)0xF801421CU) /**< \brief (HSMC) PMECC Redundancy 11 Register (sec_num = 5) */
  #define REG_HSMC_PMECC12_5  (*(__I  uint32_t*)0xF8014220U) /**< \brief (HSMC) PMECC Redundancy 12 Register (sec_num = 5) */
  #define REG_HSMC_PMECC13_5  (*(__I  uint32_t*)0xF8014224U) /**< \brief (HSMC) PMECC Redundancy 13 Register (sec_num = 5) */
  #define REG_HSMC_PMECC0_6   (*(__I  uint32_t*)0xF8014230U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 6) */
  #define REG_HSMC_PMECC1_6   (*(__I  uint32_t*)0xF8014234U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 6) */
  #define REG_HSMC_PMECC2_6   (*(__I  uint32_t*)0xF8014238U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 6) */
  #define REG_HSMC_PMECC3_6   (*(__I  uint32_t*)0xF801423CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 6) */
  #define REG_HSMC_PMECC4_6   (*(__I  uint32_t*)0xF8014240U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 6) */
  #define REG_HSMC_PMECC5_6   (*(__I  uint32_t*)0xF8014244U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 6) */
  #define REG_HSMC_PMECC6_6   (*(__I  uint32_t*)0xF8014248U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 6) */
  #define REG_HSMC_PMECC7_6   (*(__I  uint32_t*)0xF801424CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 6) */
  #define REG_HSMC_PMECC8_6   (*(__I  uint32_t*)0xF8014250U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 6) */
  #define REG_HSMC_PMECC9_6   (*(__I  uint32_t*)0xF8014254U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 6) */
  #define REG_HSMC_PMECC10_6  (*(__I  uint32_t*)0xF8014258U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 6) */
  #define REG_HSMC_PMECC11_6  (*(__I  uint32_t*)0xF801425CU) /**< \brief (HSMC) PMECC Redundancy 11 Register (sec_num = 6) */
  #define REG_HSMC_PMECC12_6  (*(__I  uint32_t*)0xF8014260U) /**< \brief (HSMC) PMECC Redundancy 12 Register (sec_num = 6) */
  #define REG_HSMC_PMECC13_6  (*(__I  uint32_t*)0xF8014264U) /**< \brief (HSMC) PMECC Redundancy 13 Register (sec_num = 6) */
  #define REG_HSMC_PMECC0_7   (*(__I  uint32_t*)0xF8014270U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 7) */
  #define REG_HSMC_PMECC1_7   (*(__I  uint32_t*)0xF8014274U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 7) */
  #define REG_HSMC_PMECC2_7   (*(__I  uint32_t*)0xF8014278U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 7) */
  #define REG_HSMC_PMECC3_7   (*(__I  uint32_t*)0xF801427CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 7) */
  #define REG_HSMC_PMECC4_7   (*(__I  uint32_t*)0xF8014280U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 7) */
  #define REG_HSMC_PMECC5_7   (*(__I  uint32_t*)0xF8014284U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 7) */
  #define REG_HSMC_PMECC6_7   (*(__I  uint32_t*)0xF8014288U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 7) */
  #define REG_HSMC_PMECC7_7   (*(__I  uint32_t*)0xF801428CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 7) */
  #define REG_HSMC_PMECC8_7   (*(__I  uint32_t*)0xF8014290U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 7) */
  #define REG_HSMC_PMECC9_7   (*(__I  uint32_t*)0xF8014294U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 7) */
  #define REG_HSMC_PMECC10_7  (*(__I  uint32_t*)0xF8014298U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 7) */
  #define REG_HSMC_PMECC11_7  (*(__I  uint32_t*)0xF801429CU) /**< \brief (HSMC) PMECC Redundancy 11 Register (sec_num = 7) */
  #define REG_HSMC_PMECC12_7  (*(__I  uint32_t*)0xF80142A0U) /**< \brief (HSMC) PMECC Redundancy 12 Register (sec_num = 7) */
  #define REG_HSMC_PMECC13_7  (*(__I  uint32_t*)0xF80142A4U) /**< \brief (HSMC) PMECC Redundancy 13 Register (sec_num = 7) */
  #define REG_HSMC_REM0_0     (*(__I  uint32_t*)0xF80142B0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 0) */
  #define REG_HSMC_REM1_0     (*(__I  uint32_t*)0xF80142B4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 0) */
  #define REG_HSMC_REM2_0     (*(__I  uint32_t*)0xF80142B8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 0) */
  #define REG_HSMC_REM3_0     (*(__I  uint32_t*)0xF80142BCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 0) */
  #define REG_HSMC_REM4_0     (*(__I  uint32_t*)0xF80142C0U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 0) */
  #define REG_HSMC_REM5_0     (*(__I  uint32_t*)0xF80142C4U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 0) */
  #define REG_HSMC_REM6_0     (*(__I  uint32_t*)0xF80142C8U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 0) */
  #define REG_HSMC_REM7_0     (*(__I  uint32_t*)0xF80142CCU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 0) */
  #define REG_HSMC_REM8_0     (*(__I  uint32_t*)0xF80142D0U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 0) */
  #define REG_HSMC_REM9_0     (*(__I  uint32_t*)0xF80142D4U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 0) */
  #define REG_HSMC_REM10_0    (*(__I  uint32_t*)0xF80142D8U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 0) */
  #define REG_HSMC_REM11_0    (*(__I  uint32_t*)0xF80142DCU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 0) */
  #define REG_HSMC_REM12_0    (*(__I  uint32_t*)0xF80142E0U) /**< \brief (HSMC) PMECC Remainder 12 Register (sec_num = 0) */
  #define REG_HSMC_REM13_0    (*(__I  uint32_t*)0xF80142E4U) /**< \brief (HSMC) PMECC Remainder 13 Register (sec_num = 0) */
  #define REG_HSMC_REM14_0    (*(__I  uint32_t*)0xF80142E8U) /**< \brief (HSMC) PMECC Remainder 14 Register (sec_num = 0) */
  #define REG_HSMC_REM15_0    (*(__I  uint32_t*)0xF80142ECU) /**< \brief (HSMC) PMECC Remainder 15 Register (sec_num = 0) */
  #define REG_HSMC_REM0_1     (*(__I  uint32_t*)0xF80142F0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 1) */
  #define REG_HSMC_REM1_1     (*(__I  uint32_t*)0xF80142F4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 1) */
  #define REG_HSMC_REM2_1     (*(__I  uint32_t*)0xF80142F8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 1) */
  #define REG_HSMC_REM3_1     (*(__I  uint32_t*)0xF80142FCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 1) */
  #define REG_HSMC_REM4_1     (*(__I  uint32_t*)0xF8014300U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 1) */
  #define REG_HSMC_REM5_1     (*(__I  uint32_t*)0xF8014304U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 1) */
  #define REG_HSMC_REM6_1     (*(__I  uint32_t*)0xF8014308U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 1) */
  #define REG_HSMC_REM7_1     (*(__I  uint32_t*)0xF801430CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 1) */
  #define REG_HSMC_REM8_1     (*(__I  uint32_t*)0xF8014310U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 1) */
  #define REG_HSMC_REM9_1     (*(__I  uint32_t*)0xF8014314U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 1) */
  #define REG_HSMC_REM10_1    (*(__I  uint32_t*)0xF8014318U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 1) */
  #define REG_HSMC_REM11_1    (*(__I  uint32_t*)0xF801431CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 1) */
  #define REG_HSMC_REM12_1    (*(__I  uint32_t*)0xF8014320U) /**< \brief (HSMC) PMECC Remainder 12 Register (sec_num = 1) */
  #define REG_HSMC_REM13_1    (*(__I  uint32_t*)0xF8014324U) /**< \brief (HSMC) PMECC Remainder 13 Register (sec_num = 1) */
  #define REG_HSMC_REM14_1    (*(__I  uint32_t*)0xF8014328U) /**< \brief (HSMC) PMECC Remainder 14 Register (sec_num = 1) */
  #define REG_HSMC_REM15_1    (*(__I  uint32_t*)0xF801432CU) /**< \brief (HSMC) PMECC Remainder 15 Register (sec_num = 1) */
  #define REG_HSMC_REM0_2     (*(__I  uint32_t*)0xF8014330U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 2) */
  #define REG_HSMC_REM1_2     (*(__I  uint32_t*)0xF8014334U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 2) */
  #define REG_HSMC_REM2_2     (*(__I  uint32_t*)0xF8014338U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 2) */
  #define REG_HSMC_REM3_2     (*(__I  uint32_t*)0xF801433CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 2) */
  #define REG_HSMC_REM4_2     (*(__I  uint32_t*)0xF8014340U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 2) */
  #define REG_HSMC_REM5_2     (*(__I  uint32_t*)0xF8014344U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 2) */
  #define REG_HSMC_REM6_2     (*(__I  uint32_t*)0xF8014348U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 2) */
  #define REG_HSMC_REM7_2     (*(__I  uint32_t*)0xF801434CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 2) */
  #define REG_HSMC_REM8_2     (*(__I  uint32_t*)0xF8014350U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 2) */
  #define REG_HSMC_REM9_2     (*(__I  uint32_t*)0xF8014354U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 2) */
  #define REG_HSMC_REM10_2    (*(__I  uint32_t*)0xF8014358U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 2) */
  #define REG_HSMC_REM11_2    (*(__I  uint32_t*)0xF801435CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 2) */
  #define REG_HSMC_REM12_2    (*(__I  uint32_t*)0xF8014360U) /**< \brief (HSMC) PMECC Remainder 12 Register (sec_num = 2) */
  #define REG_HSMC_REM13_2    (*(__I  uint32_t*)0xF8014364U) /**< \brief (HSMC) PMECC Remainder 13 Register (sec_num = 2) */
  #define REG_HSMC_REM14_2    (*(__I  uint32_t*)0xF8014368U) /**< \brief (HSMC) PMECC Remainder 14 Register (sec_num = 2) */
  #define REG_HSMC_REM15_2    (*(__I  uint32_t*)0xF801436CU) /**< \brief (HSMC) PMECC Remainder 15 Register (sec_num = 2) */
  #define REG_HSMC_REM0_3     (*(__I  uint32_t*)0xF8014370U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 3) */
  #define REG_HSMC_REM1_3     (*(__I  uint32_t*)0xF8014374U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 3) */
  #define REG_HSMC_REM2_3     (*(__I  uint32_t*)0xF8014378U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 3) */
  #define REG_HSMC_REM3_3     (*(__I  uint32_t*)0xF801437CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 3) */
  #define REG_HSMC_REM4_3     (*(__I  uint32_t*)0xF8014380U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 3) */
  #define REG_HSMC_REM5_3     (*(__I  uint32_t*)0xF8014384U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 3) */
  #define REG_HSMC_REM6_3     (*(__I  uint32_t*)0xF8014388U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 3) */
  #define REG_HSMC_REM7_3     (*(__I  uint32_t*)0xF801438CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 3) */
  #define REG_HSMC_REM8_3     (*(__I  uint32_t*)0xF8014390U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 3) */
  #define REG_HSMC_REM9_3     (*(__I  uint32_t*)0xF8014394U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 3) */
  #define REG_HSMC_REM10_3    (*(__I  uint32_t*)0xF8014398U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 3) */
  #define REG_HSMC_REM11_3    (*(__I  uint32_t*)0xF801439CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 3) */
  #define REG_HSMC_REM12_3    (*(__I  uint32_t*)0xF80143A0U) /**< \brief (HSMC) PMECC Remainder 12 Register (sec_num = 3) */
  #define REG_HSMC_REM13_3    (*(__I  uint32_t*)0xF80143A4U) /**< \brief (HSMC) PMECC Remainder 13 Register (sec_num = 3) */
  #define REG_HSMC_REM14_3    (*(__I  uint32_t*)0xF80143A8U) /**< \brief (HSMC) PMECC Remainder 14 Register (sec_num = 3) */
  #define REG_HSMC_REM15_3    (*(__I  uint32_t*)0xF80143ACU) /**< \brief (HSMC) PMECC Remainder 15 Register (sec_num = 3) */
  #define REG_HSMC_REM0_4     (*(__I  uint32_t*)0xF80143B0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 4) */
  #define REG_HSMC_REM1_4     (*(__I  uint32_t*)0xF80143B4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 4) */
  #define REG_HSMC_REM2_4     (*(__I  uint32_t*)0xF80143B8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 4) */
  #define REG_HSMC_REM3_4     (*(__I  uint32_t*)0xF80143BCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 4) */
  #define REG_HSMC_REM4_4     (*(__I  uint32_t*)0xF80143C0U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 4) */
  #define REG_HSMC_REM5_4     (*(__I  uint32_t*)0xF80143C4U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 4) */
  #define REG_HSMC_REM6_4     (*(__I  uint32_t*)0xF80143C8U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 4) */
  #define REG_HSMC_REM7_4     (*(__I  uint32_t*)0xF80143CCU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 4) */
  #define REG_HSMC_REM8_4     (*(__I  uint32_t*)0xF80143D0U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 4) */
  #define REG_HSMC_REM9_4     (*(__I  uint32_t*)0xF80143D4U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 4) */
  #define REG_HSMC_REM10_4    (*(__I  uint32_t*)0xF80143D8U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 4) */
  #define REG_HSMC_REM11_4    (*(__I  uint32_t*)0xF80143DCU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 4) */
  #define REG_HSMC_REM12_4    (*(__I  uint32_t*)0xF80143E0U) /**< \brief (HSMC) PMECC Remainder 12 Register (sec_num = 4) */
  #define REG_HSMC_REM13_4    (*(__I  uint32_t*)0xF80143E4U) /**< \brief (HSMC) PMECC Remainder 13 Register (sec_num = 4) */
  #define REG_HSMC_REM14_4    (*(__I  uint32_t*)0xF80143E8U) /**< \brief (HSMC) PMECC Remainder 14 Register (sec_num = 4) */
  #define REG_HSMC_REM15_4    (*(__I  uint32_t*)0xF80143ECU) /**< \brief (HSMC) PMECC Remainder 15 Register (sec_num = 4) */
  #define REG_HSMC_REM0_5     (*(__I  uint32_t*)0xF80143F0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 5) */
  #define REG_HSMC_REM1_5     (*(__I  uint32_t*)0xF80143F4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 5) */
  #define REG_HSMC_REM2_5     (*(__I  uint32_t*)0xF80143F8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 5) */
  #define REG_HSMC_REM3_5     (*(__I  uint32_t*)0xF80143FCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 5) */
  #define REG_HSMC_REM4_5     (*(__I  uint32_t*)0xF8014400U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 5) */
  #define REG_HSMC_REM5_5     (*(__I  uint32_t*)0xF8014404U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 5) */
  #define REG_HSMC_REM6_5     (*(__I  uint32_t*)0xF8014408U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 5) */
  #define REG_HSMC_REM7_5     (*(__I  uint32_t*)0xF801440CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 5) */
  #define REG_HSMC_REM8_5     (*(__I  uint32_t*)0xF8014410U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 5) */
  #define REG_HSMC_REM9_5     (*(__I  uint32_t*)0xF8014414U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 5) */
  #define REG_HSMC_REM10_5    (*(__I  uint32_t*)0xF8014418U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 5) */
  #define REG_HSMC_REM11_5    (*(__I  uint32_t*)0xF801441CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 5) */
  #define REG_HSMC_REM12_5    (*(__I  uint32_t*)0xF8014420U) /**< \brief (HSMC) PMECC Remainder 12 Register (sec_num = 5) */
  #define REG_HSMC_REM13_5    (*(__I  uint32_t*)0xF8014424U) /**< \brief (HSMC) PMECC Remainder 13 Register (sec_num = 5) */
  #define REG_HSMC_REM14_5    (*(__I  uint32_t*)0xF8014428U) /**< \brief (HSMC) PMECC Remainder 14 Register (sec_num = 5) */
  #define REG_HSMC_REM15_5    (*(__I  uint32_t*)0xF801442CU) /**< \brief (HSMC) PMECC Remainder 15 Register (sec_num = 5) */
  #define REG_HSMC_REM0_6     (*(__I  uint32_t*)0xF8014430U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 6) */
  #define REG_HSMC_REM1_6     (*(__I  uint32_t*)0xF8014434U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 6) */
  #define REG_HSMC_REM2_6     (*(__I  uint32_t*)0xF8014438U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 6) */
  #define REG_HSMC_REM3_6     (*(__I  uint32_t*)0xF801443CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 6) */
  #define REG_HSMC_REM4_6     (*(__I  uint32_t*)0xF8014440U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 6) */
  #define REG_HSMC_REM5_6     (*(__I  uint32_t*)0xF8014444U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 6) */
  #define REG_HSMC_REM6_6     (*(__I  uint32_t*)0xF8014448U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 6) */
  #define REG_HSMC_REM7_6     (*(__I  uint32_t*)0xF801444CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 6) */
  #define REG_HSMC_REM8_6     (*(__I  uint32_t*)0xF8014450U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 6) */
  #define REG_HSMC_REM9_6     (*(__I  uint32_t*)0xF8014454U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 6) */
  #define REG_HSMC_REM10_6    (*(__I  uint32_t*)0xF8014458U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 6) */
  #define REG_HSMC_REM11_6    (*(__I  uint32_t*)0xF801445CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 6) */
  #define REG_HSMC_REM12_6    (*(__I  uint32_t*)0xF8014460U) /**< \brief (HSMC) PMECC Remainder 12 Register (sec_num = 6) */
  #define REG_HSMC_REM13_6    (*(__I  uint32_t*)0xF8014464U) /**< \brief (HSMC) PMECC Remainder 13 Register (sec_num = 6) */
  #define REG_HSMC_REM14_6    (*(__I  uint32_t*)0xF8014468U) /**< \brief (HSMC) PMECC Remainder 14 Register (sec_num = 6) */
  #define REG_HSMC_REM15_6    (*(__I  uint32_t*)0xF801446CU) /**< \brief (HSMC) PMECC Remainder 15 Register (sec_num = 6) */
  #define REG_HSMC_REM0_7     (*(__I  uint32_t*)0xF8014470U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 7) */
  #define REG_HSMC_REM1_7     (*(__I  uint32_t*)0xF8014474U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 7) */
  #define REG_HSMC_REM2_7     (*(__I  uint32_t*)0xF8014478U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 7) */
  #define REG_HSMC_REM3_7     (*(__I  uint32_t*)0xF801447CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 7) */
  #define REG_HSMC_REM4_7     (*(__I  uint32_t*)0xF8014480U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 7) */
  #define REG_HSMC_REM5_7     (*(__I  uint32_t*)0xF8014484U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 7) */
  #define REG_HSMC_REM6_7     (*(__I  uint32_t*)0xF8014488U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 7) */
  #define REG_HSMC_REM7_7     (*(__I  uint32_t*)0xF801448CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 7) */
  #define REG_HSMC_REM8_7     (*(__I  uint32_t*)0xF8014490U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 7) */
  #define REG_HSMC_REM9_7     (*(__I  uint32_t*)0xF8014494U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 7) */
  #define REG_HSMC_REM10_7    (*(__I  uint32_t*)0xF8014498U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 7) */
  #define REG_HSMC_REM11_7    (*(__I  uint32_t*)0xF801449CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 7) */
  #define REG_HSMC_REM12_7    (*(__I  uint32_t*)0xF80144A0U) /**< \brief (HSMC) PMECC Remainder 12 Register (sec_num = 7) */
  #define REG_HSMC_REM13_7    (*(__I  uint32_t*)0xF80144A4U) /**< \brief (HSMC) PMECC Remainder 13 Register (sec_num = 7) */
  #define REG_HSMC_REM14_7    (*(__I  uint32_t*)0xF80144A8U) /**< \brief (HSMC) PMECC Remainder 14 Register (sec_num = 7) */
  #define REG_HSMC_REM15_7    (*(__I  uint32_t*)0xF80144ACU) /**< \brief (HSMC) PMECC Remainder 15 Register (sec_num = 7) */
  #define REG_HSMC_ELCFG      (*(__IO uint32_t*)0xF8014500U) /**< \brief (HSMC) PMECC Error Location Configuration Register */
  #define REG_HSMC_ELPRIM     (*(__I  uint32_t*)0xF8014504U) /**< \brief (HSMC) PMECC Error Location Primitive Register */
  #define REG_HSMC_ELEN       (*(__O  uint32_t*)0xF8014508U) /**< \brief (HSMC) PMECC Error Location Enable Register */
  #define REG_HSMC_ELDIS      (*(__O  uint32_t*)0xF801450CU) /**< \brief (HSMC) PMECC Error Location Disable Register */
  #define REG_HSMC_ELSR       (*(__I  uint32_t*)0xF8014510U) /**< \brief (HSMC) PMECC Error Location Status Register */
  #define REG_HSMC_ELIER      (*(__O  uint32_t*)0xF8014514U) /**< \brief (HSMC) PMECC Error Location Interrupt Enable register */
  #define REG_HSMC_ELIDR      (*(__O  uint32_t*)0xF8014518U) /**< \brief (HSMC) PMECC Error Location Interrupt Disable Register */
  #define REG_HSMC_ELIMR      (*(__I  uint32_t*)0xF801451CU) /**< \brief (HSMC) PMECC Error Location Interrupt Mask Register */
  #define REG_HSMC_ELISR      (*(__I  uint32_t*)0xF8014520U) /**< \brief (HSMC) PMECC Error Location Interrupt Status Register */
  #define REG_HSMC_SIGMA0     (*(__IO uint32_t*)0xF8014528U) /**< \brief (HSMC) PMECC Error Location SIGMA 0 Register */
  #define REG_HSMC_SIGMA1     (*(__IO uint32_t*)0xF801452CU) /**< \brief (HSMC) PMECC Error Location SIGMA 1 Register */
  #define REG_HSMC_SIGMA2     (*(__IO uint32_t*)0xF8014530U) /**< \brief (HSMC) PMECC Error Location SIGMA 2 Register */
  #define REG_HSMC_SIGMA3     (*(__IO uint32_t*)0xF8014534U) /**< \brief (HSMC) PMECC Error Location SIGMA 3 Register */
  #define REG_HSMC_SIGMA4     (*(__IO uint32_t*)0xF8014538U) /**< \brief (HSMC) PMECC Error Location SIGMA 4 Register */
  #define REG_HSMC_SIGMA5     (*(__IO uint32_t*)0xF801453CU) /**< \brief (HSMC) PMECC Error Location SIGMA 5 Register */
  #define REG_HSMC_SIGMA6     (*(__IO uint32_t*)0xF8014540U) /**< \brief (HSMC) PMECC Error Location SIGMA 6 Register */
  #define REG_HSMC_SIGMA7     (*(__IO uint32_t*)0xF8014544U) /**< \brief (HSMC) PMECC Error Location SIGMA 7 Register */
  #define REG_HSMC_SIGMA8     (*(__IO uint32_t*)0xF8014548U) /**< \brief (HSMC) PMECC Error Location SIGMA 8 Register */
  #define REG_HSMC_SIGMA9     (*(__IO uint32_t*)0xF801454CU) /**< \brief (HSMC) PMECC Error Location SIGMA 9 Register */
  #define REG_HSMC_SIGMA10    (*(__IO uint32_t*)0xF8014550U) /**< \brief (HSMC) PMECC Error Location SIGMA 10 Register */
  #define REG_HSMC_SIGMA11    (*(__IO uint32_t*)0xF8014554U) /**< \brief (HSMC) PMECC Error Location SIGMA 11 Register */
  #define REG_HSMC_SIGMA12    (*(__IO uint32_t*)0xF8014558U) /**< \brief (HSMC) PMECC Error Location SIGMA 12 Register */
  #define REG_HSMC_SIGMA13    (*(__IO uint32_t*)0xF801455CU) /**< \brief (HSMC) PMECC Error Location SIGMA 13 Register */
  #define REG_HSMC_SIGMA14    (*(__IO uint32_t*)0xF8014560U) /**< \brief (HSMC) PMECC Error Location SIGMA 14 Register */
  #define REG_HSMC_SIGMA15    (*(__IO uint32_t*)0xF8014564U) /**< \brief (HSMC) PMECC Error Location SIGMA 15 Register */
  #define REG_HSMC_SIGMA16    (*(__IO uint32_t*)0xF8014568U) /**< \brief (HSMC) PMECC Error Location SIGMA 16 Register */
  #define REG_HSMC_SIGMA17    (*(__IO uint32_t*)0xF801456CU) /**< \brief (HSMC) PMECC Error Location SIGMA 17 Register */
  #define REG_HSMC_SIGMA18    (*(__IO uint32_t*)0xF8014570U) /**< \brief (HSMC) PMECC Error Location SIGMA 18 Register */
  #define REG_HSMC_SIGMA19    (*(__IO uint32_t*)0xF8014574U) /**< \brief (HSMC) PMECC Error Location SIGMA 19 Register */
  #define REG_HSMC_SIGMA20    (*(__IO uint32_t*)0xF8014578U) /**< \brief (HSMC) PMECC Error Location SIGMA 20 Register */
  #define REG_HSMC_SIGMA21    (*(__IO uint32_t*)0xF801457CU) /**< \brief (HSMC) PMECC Error Location SIGMA 21 Register */
  #define REG_HSMC_SIGMA22    (*(__IO uint32_t*)0xF8014580U) /**< \brief (HSMC) PMECC Error Location SIGMA 22 Register */
  #define REG_HSMC_SIGMA23    (*(__IO uint32_t*)0xF8014584U) /**< \brief (HSMC) PMECC Error Location SIGMA 23 Register */
  #define REG_HSMC_SIGMA24    (*(__IO uint32_t*)0xF8014588U) /**< \brief (HSMC) PMECC Error Location SIGMA 24 Register */
  #define REG_HSMC_SIGMA25    (*(__IO uint32_t*)0xF801458CU) /**< \brief (HSMC) PMECC Error Location SIGMA 25 Register */
  #define REG_HSMC_SIGMA26    (*(__IO uint32_t*)0xF8014590U) /**< \brief (HSMC) PMECC Error Location SIGMA 26 Register */
  #define REG_HSMC_SIGMA27    (*(__IO uint32_t*)0xF8014594U) /**< \brief (HSMC) PMECC Error Location SIGMA 27 Register */
  #define REG_HSMC_SIGMA28    (*(__IO uint32_t*)0xF8014598U) /**< \brief (HSMC) PMECC Error Location SIGMA 28 Register */
  #define REG_HSMC_SIGMA29    (*(__IO uint32_t*)0xF801459CU) /**< \brief (HSMC) PMECC Error Location SIGMA 29 Register */
  #define REG_HSMC_SIGMA30    (*(__IO uint32_t*)0xF80145A0U) /**< \brief (HSMC) PMECC Error Location SIGMA 30 Register */
  #define REG_HSMC_SIGMA31    (*(__IO uint32_t*)0xF80145A4U) /**< \brief (HSMC) PMECC Error Location SIGMA 31 Register */
  #define REG_HSMC_SIGMA32    (*(__IO uint32_t*)0xF80145A8U) /**< \brief (HSMC) PMECC Error Location SIGMA 32 Register */
  #define REG_HSMC_ERRLOC0    (*(__I  uint32_t*)0xF80145ACU) /**< \brief (HSMC) PMECC Error Location 0 Register */
  #define REG_HSMC_ERRLOC1    (*(__I  uint32_t*)0xF80145B0U) /**< \brief (HSMC) PMECC Error Location 1 Register */
  #define REG_HSMC_ERRLOC2    (*(__I  uint32_t*)0xF80145B4U) /**< \brief (HSMC) PMECC Error Location 2 Register */
  #define REG_HSMC_ERRLOC3    (*(__I  uint32_t*)0xF80145B8U) /**< \brief (HSMC) PMECC Error Location 3 Register */
  #define REG_HSMC_ERRLOC4    (*(__I  uint32_t*)0xF80145BCU) /**< \brief (HSMC) PMECC Error Location 4 Register */
  #define REG_HSMC_ERRLOC5    (*(__I  uint32_t*)0xF80145C0U) /**< \brief (HSMC) PMECC Error Location 5 Register */
  #define REG_HSMC_ERRLOC6    (*(__I  uint32_t*)0xF80145C4U) /**< \brief (HSMC) PMECC Error Location 6 Register */
  #define REG_HSMC_ERRLOC7    (*(__I  uint32_t*)0xF80145C8U) /**< \brief (HSMC) PMECC Error Location 7 Register */
  #define REG_HSMC_ERRLOC8    (*(__I  uint32_t*)0xF80145CCU) /**< \brief (HSMC) PMECC Error Location 8 Register */
  #define REG_HSMC_ERRLOC9    (*(__I  uint32_t*)0xF80145D0U) /**< \brief (HSMC) PMECC Error Location 9 Register */
  #define REG_HSMC_ERRLOC10   (*(__I  uint32_t*)0xF80145D4U) /**< \brief (HSMC) PMECC Error Location 10 Register */
  #define REG_HSMC_ERRLOC11   (*(__I  uint32_t*)0xF80145D8U) /**< \brief (HSMC) PMECC Error Location 11 Register */
  #define REG_HSMC_ERRLOC12   (*(__I  uint32_t*)0xF80145DCU) /**< \brief (HSMC) PMECC Error Location 12 Register */
  #define REG_HSMC_ERRLOC13   (*(__I  uint32_t*)0xF80145E0U) /**< \brief (HSMC) PMECC Error Location 13 Register */
  #define REG_HSMC_ERRLOC14   (*(__I  uint32_t*)0xF80145E4U) /**< \brief (HSMC) PMECC Error Location 14 Register */
  #define REG_HSMC_ERRLOC15   (*(__I  uint32_t*)0xF80145E8U) /**< \brief (HSMC) PMECC Error Location 15 Register */
  #define REG_HSMC_ERRLOC16   (*(__I  uint32_t*)0xF80145ECU) /**< \brief (HSMC) PMECC Error Location 16 Register */
  #define REG_HSMC_ERRLOC17   (*(__I  uint32_t*)0xF80145F0U) /**< \brief (HSMC) PMECC Error Location 17 Register */
  #define REG_HSMC_ERRLOC18   (*(__I  uint32_t*)0xF80145F4U) /**< \brief (HSMC) PMECC Error Location 18 Register */
  #define REG_HSMC_ERRLOC19   (*(__I  uint32_t*)0xF80145F8U) /**< \brief (HSMC) PMECC Error Location 19 Register */
  #define REG_HSMC_ERRLOC20   (*(__I  uint32_t*)0xF80145FCU) /**< \brief (HSMC) PMECC Error Location 20 Register */
  #define REG_HSMC_ERRLOC21   (*(__I  uint32_t*)0xF8014600U) /**< \brief (HSMC) PMECC Error Location 21 Register */
  #define REG_HSMC_ERRLOC22   (*(__I  uint32_t*)0xF8014604U) /**< \brief (HSMC) PMECC Error Location 22 Register */
  #define REG_HSMC_ERRLOC23   (*(__I  uint32_t*)0xF8014608U) /**< \brief (HSMC) PMECC Error Location 23 Register */
  #define REG_HSMC_ERRLOC24   (*(__I  uint32_t*)0xF801460CU) /**< \brief (HSMC) PMECC Error Location 24 Register */
  #define REG_HSMC_ERRLOC25   (*(__I  uint32_t*)0xF8014610U) /**< \brief (HSMC) PMECC Error Location 25 Register */
  #define REG_HSMC_ERRLOC26   (*(__I  uint32_t*)0xF8014614U) /**< \brief (HSMC) PMECC Error Location 26 Register */
  #define REG_HSMC_ERRLOC27   (*(__I  uint32_t*)0xF8014618U) /**< \brief (HSMC) PMECC Error Location 27 Register */
  #define REG_HSMC_ERRLOC28   (*(__I  uint32_t*)0xF801461CU) /**< \brief (HSMC) PMECC Error Location 28 Register */
  #define REG_HSMC_ERRLOC29   (*(__I  uint32_t*)0xF8014620U) /**< \brief (HSMC) PMECC Error Location 29 Register */
  #define REG_HSMC_ERRLOC30   (*(__I  uint32_t*)0xF8014624U) /**< \brief (HSMC) PMECC Error Location 30 Register */
  #define REG_HSMC_ERRLOC31   (*(__I  uint32_t*)0xF8014628U) /**< \brief (HSMC) PMECC Error Location 31 Register */
  #define REG_HSMC_SETUP0     (*(__IO uint32_t*)0xF8014700U) /**< \brief (HSMC) HSMC Setup Register (CS_number = 0) */
  #define REG_HSMC_PULSE0     (*(__IO uint32_t*)0xF8014704U) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 0) */
  #define REG_HSMC_CYCLE0     (*(__IO uint32_t*)0xF8014708U) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 0) */
  #define REG_HSMC_TIMINGS0   (*(__IO uint32_t*)0xF801470CU) /**< \brief (HSMC) HSMC Timings Register (CS_number = 0) */
  #define REG_HSMC_MODE0      (*(__IO uint32_t*)0xF8014710U) /**< \brief (HSMC) HSMC Mode Register (CS_number = 0) */
  #define REG_HSMC_SETUP1     (*(__IO uint32_t*)0xF8014714U) /**< \brief (HSMC) HSMC Setup Register (CS_number = 1) */
  #define REG_HSMC_PULSE1     (*(__IO uint32_t*)0xF8014718U) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 1) */
  #define REG_HSMC_CYCLE1     (*(__IO uint32_t*)0xF801471CU) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 1) */
  #define REG_HSMC_TIMINGS1   (*(__IO uint32_t*)0xF8014720U) /**< \brief (HSMC) HSMC Timings Register (CS_number = 1) */
  #define REG_HSMC_MODE1      (*(__IO uint32_t*)0xF8014724U) /**< \brief (HSMC) HSMC Mode Register (CS_number = 1) */
  #define REG_HSMC_SETUP2     (*(__IO uint32_t*)0xF8014728U) /**< \brief (HSMC) HSMC Setup Register (CS_number = 2) */
  #define REG_HSMC_PULSE2     (*(__IO uint32_t*)0xF801472CU) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 2) */
  #define REG_HSMC_CYCLE2     (*(__IO uint32_t*)0xF8014730U) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 2) */
  #define REG_HSMC_TIMINGS2   (*(__IO uint32_t*)0xF8014734U) /**< \brief (HSMC) HSMC Timings Register (CS_number = 2) */
  #define REG_HSMC_MODE2      (*(__IO uint32_t*)0xF8014738U) /**< \brief (HSMC) HSMC Mode Register (CS_number = 2) */
  #define REG_HSMC_SETUP3     (*(__IO uint32_t*)0xF801473CU) /**< \brief (HSMC) HSMC Setup Register (CS_number = 3) */
  #define REG_HSMC_PULSE3     (*(__IO uint32_t*)0xF8014740U) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 3) */
  #define REG_HSMC_CYCLE3     (*(__IO uint32_t*)0xF8014744U) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 3) */
  #define REG_HSMC_TIMINGS3   (*(__IO uint32_t*)0xF8014748U) /**< \brief (HSMC) HSMC Timings Register (CS_number = 3) */
  #define REG_HSMC_MODE3      (*(__IO uint32_t*)0xF801474CU) /**< \brief (HSMC) HSMC Mode Register (CS_number = 3) */
  #define REG_HSMC_OCMS       (*(__IO uint32_t*)0xF80147A0U) /**< \brief (HSMC) HSMC Off Chip Memory Scrambling Register */
  #define REG_HSMC_KEY1       (*(__O  uint32_t*)0xF80147A4U) /**< \brief (HSMC) HSMC Off Chip Memory Scrambling KEY1 Register */
  #define REG_HSMC_KEY2       (*(__O  uint32_t*)0xF80147A8U) /**< \brief (HSMC) HSMC Off Chip Memory Scrambling KEY2 Register */
  #define REG_HSMC_WPMR       (*(__IO uint32_t*)0xF80147E4U) /**< \brief (HSMC) HSMC Write Protection Mode Register */
  #define REG_HSMC_WPSR       (*(__I  uint32_t*)0xF80147E8U) /**< \brief (HSMC) HSMC Write Protection Status Register */
  #define REG_HSMC_VERSION    (*(__I  uint32_t*)0xF80147FCU) /**< \brief (HSMC) HSMC Version Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_HSMC_INSTANCE_ */
