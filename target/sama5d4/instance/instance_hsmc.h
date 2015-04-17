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

#ifndef _SAMA5D4_HSMC_INSTANCE_
#define _SAMA5D4_HSMC_INSTANCE_

/* ========== Register definition for HSMC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_HSMC_CFG                         (0xFC05C000U) /**< \brief (HSMC) HSMC NFC Configuration Register */
  #define REG_HSMC_CTRL                        (0xFC05C004U) /**< \brief (HSMC) HSMC NFC Control Register */
  #define REG_HSMC_SR                          (0xFC05C008U) /**< \brief (HSMC) HSMC NFC Status Register */
  #define REG_HSMC_IER                         (0xFC05C00CU) /**< \brief (HSMC) HSMC NFC Interrupt Enable Register */
  #define REG_HSMC_IDR                         (0xFC05C010U) /**< \brief (HSMC) HSMC NFC Interrupt Disable Register */
  #define REG_HSMC_IMR                         (0xFC05C014U) /**< \brief (HSMC) HSMC NFC Interrupt Mask Register */
  #define REG_HSMC_ADDR                        (0xFC05C018U) /**< \brief (HSMC) HSMC NFC Address Cycle Zero Register */
  #define REG_HSMC_BANK                        (0xFC05C01CU) /**< \brief (HSMC) HSMC Bank Address Register */
  #define REG_HSMC_PMECCFG                     (0xFC05C070U) /**< \brief (HSMC) PMECC Configuration Register */
  #define REG_HSMC_PMECCSAREA                  (0xFC05C074U) /**< \brief (HSMC) PMECC Spare Area Size Register */
  #define REG_HSMC_PMECCSADDR                  (0xFC05C078U) /**< \brief (HSMC) PMECC Start Address Register */
  #define REG_HSMC_PMECCEADDR                  (0xFC05C07CU) /**< \brief (HSMC) PMECC End Address Register */
  #define REG_HSMC_PMECCTRL                    (0xFC05C084U) /**< \brief (HSMC) PMECC Control Register */
  #define REG_HSMC_PMECCSR                     (0xFC05C088U) /**< \brief (HSMC) PMECC Status Register */
  #define REG_HSMC_PMECCIER                    (0xFC05C08CU) /**< \brief (HSMC) PMECC Interrupt Enable register */
  #define REG_HSMC_PMECCIDR                    (0xFC05C090U) /**< \brief (HSMC) PMECC Interrupt Disable Register */
  #define REG_HSMC_PMECCIMR                    (0xFC05C094U) /**< \brief (HSMC) PMECC Interrupt Mask Register */
  #define REG_HSMC_PMECCISR                    (0xFC05C098U) /**< \brief (HSMC) PMECC Interrupt Status Register */
  #define REG_HSMC_PMECC0_0                    (0xFC05C0B0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 0) */
  #define REG_HSMC_PMECC1_0                    (0xFC05C0B4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 0) */
  #define REG_HSMC_PMECC2_0                    (0xFC05C0B8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 0) */
  #define REG_HSMC_PMECC3_0                    (0xFC05C0BCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 0) */
  #define REG_HSMC_PMECC4_0                    (0xFC05C0C0U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 0) */
  #define REG_HSMC_PMECC5_0                    (0xFC05C0C4U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 0) */
  #define REG_HSMC_PMECC6_0                    (0xFC05C0C8U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 0) */
  #define REG_HSMC_PMECC7_0                    (0xFC05C0CCU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 0) */
  #define REG_HSMC_PMECC8_0                    (0xFC05C0D0U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 0) */
  #define REG_HSMC_PMECC9_0                    (0xFC05C0D4U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 0) */
  #define REG_HSMC_PMECC10_0                   (0xFC05C0D8U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 0) */
  #define REG_HSMC_PMECC0_1                    (0xFC05C0F0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 1) */
  #define REG_HSMC_PMECC1_1                    (0xFC05C0F4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 1) */
  #define REG_HSMC_PMECC2_1                    (0xFC05C0F8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 1) */
  #define REG_HSMC_PMECC3_1                    (0xFC05C0FCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 1) */
  #define REG_HSMC_PMECC4_1                    (0xFC05C100U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 1) */
  #define REG_HSMC_PMECC5_1                    (0xFC05C104U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 1) */
  #define REG_HSMC_PMECC6_1                    (0xFC05C108U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 1) */
  #define REG_HSMC_PMECC7_1                    (0xFC05C10CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 1) */
  #define REG_HSMC_PMECC8_1                    (0xFC05C110U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 1) */
  #define REG_HSMC_PMECC9_1                    (0xFC05C114U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 1) */
  #define REG_HSMC_PMECC10_1                   (0xFC05C118U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 1) */
  #define REG_HSMC_PMECC0_2                    (0xFC05C130U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 2) */
  #define REG_HSMC_PMECC1_2                    (0xFC05C134U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 2) */
  #define REG_HSMC_PMECC2_2                    (0xFC05C138U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 2) */
  #define REG_HSMC_PMECC3_2                    (0xFC05C13CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 2) */
  #define REG_HSMC_PMECC4_2                    (0xFC05C140U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 2) */
  #define REG_HSMC_PMECC5_2                    (0xFC05C144U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 2) */
  #define REG_HSMC_PMECC6_2                    (0xFC05C148U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 2) */
  #define REG_HSMC_PMECC7_2                    (0xFC05C14CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 2) */
  #define REG_HSMC_PMECC8_2                    (0xFC05C150U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 2) */
  #define REG_HSMC_PMECC9_2                    (0xFC05C154U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 2) */
  #define REG_HSMC_PMECC10_2                   (0xFC05C158U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 2) */
  #define REG_HSMC_PMECC0_3                    (0xFC05C170U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 3) */
  #define REG_HSMC_PMECC1_3                    (0xFC05C174U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 3) */
  #define REG_HSMC_PMECC2_3                    (0xFC05C178U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 3) */
  #define REG_HSMC_PMECC3_3                    (0xFC05C17CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 3) */
  #define REG_HSMC_PMECC4_3                    (0xFC05C180U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 3) */
  #define REG_HSMC_PMECC5_3                    (0xFC05C184U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 3) */
  #define REG_HSMC_PMECC6_3                    (0xFC05C188U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 3) */
  #define REG_HSMC_PMECC7_3                    (0xFC05C18CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 3) */
  #define REG_HSMC_PMECC8_3                    (0xFC05C190U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 3) */
  #define REG_HSMC_PMECC9_3                    (0xFC05C194U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 3) */
  #define REG_HSMC_PMECC10_3                   (0xFC05C198U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 3) */
  #define REG_HSMC_PMECC0_4                    (0xFC05C1B0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 4) */
  #define REG_HSMC_PMECC1_4                    (0xFC05C1B4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 4) */
  #define REG_HSMC_PMECC2_4                    (0xFC05C1B8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 4) */
  #define REG_HSMC_PMECC3_4                    (0xFC05C1BCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 4) */
  #define REG_HSMC_PMECC4_4                    (0xFC05C1C0U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 4) */
  #define REG_HSMC_PMECC5_4                    (0xFC05C1C4U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 4) */
  #define REG_HSMC_PMECC6_4                    (0xFC05C1C8U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 4) */
  #define REG_HSMC_PMECC7_4                    (0xFC05C1CCU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 4) */
  #define REG_HSMC_PMECC8_4                    (0xFC05C1D0U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 4) */
  #define REG_HSMC_PMECC9_4                    (0xFC05C1D4U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 4) */
  #define REG_HSMC_PMECC10_4                   (0xFC05C1D8U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 4) */
  #define REG_HSMC_PMECC0_5                    (0xFC05C1F0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 5) */
  #define REG_HSMC_PMECC1_5                    (0xFC05C1F4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 5) */
  #define REG_HSMC_PMECC2_5                    (0xFC05C1F8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 5) */
  #define REG_HSMC_PMECC3_5                    (0xFC05C1FCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 5) */
  #define REG_HSMC_PMECC4_5                    (0xFC05C200U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 5) */
  #define REG_HSMC_PMECC5_5                    (0xFC05C204U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 5) */
  #define REG_HSMC_PMECC6_5                    (0xFC05C208U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 5) */
  #define REG_HSMC_PMECC7_5                    (0xFC05C20CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 5) */
  #define REG_HSMC_PMECC8_5                    (0xFC05C210U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 5) */
  #define REG_HSMC_PMECC9_5                    (0xFC05C214U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 5) */
  #define REG_HSMC_PMECC10_5                   (0xFC05C218U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 5) */
  #define REG_HSMC_PMECC0_6                    (0xFC05C230U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 6) */
  #define REG_HSMC_PMECC1_6                    (0xFC05C234U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 6) */
  #define REG_HSMC_PMECC2_6                    (0xFC05C238U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 6) */
  #define REG_HSMC_PMECC3_6                    (0xFC05C23CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 6) */
  #define REG_HSMC_PMECC4_6                    (0xFC05C240U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 6) */
  #define REG_HSMC_PMECC5_6                    (0xFC05C244U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 6) */
  #define REG_HSMC_PMECC6_6                    (0xFC05C248U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 6) */
  #define REG_HSMC_PMECC7_6                    (0xFC05C24CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 6) */
  #define REG_HSMC_PMECC8_6                    (0xFC05C250U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 6) */
  #define REG_HSMC_PMECC9_6                    (0xFC05C254U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 6) */
  #define REG_HSMC_PMECC10_6                   (0xFC05C258U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 6) */
  #define REG_HSMC_PMECC0_7                    (0xFC05C270U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 7) */
  #define REG_HSMC_PMECC1_7                    (0xFC05C274U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 7) */
  #define REG_HSMC_PMECC2_7                    (0xFC05C278U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 7) */
  #define REG_HSMC_PMECC3_7                    (0xFC05C27CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 7) */
  #define REG_HSMC_PMECC4_7                    (0xFC05C280U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 7) */
  #define REG_HSMC_PMECC5_7                    (0xFC05C284U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 7) */
  #define REG_HSMC_PMECC6_7                    (0xFC05C288U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 7) */
  #define REG_HSMC_PMECC7_7                    (0xFC05C28CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 7) */
  #define REG_HSMC_PMECC8_7                    (0xFC05C290U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 7) */
  #define REG_HSMC_PMECC9_7                    (0xFC05C294U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 7) */
  #define REG_HSMC_PMECC10_7                   (0xFC05C298U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 7) */
  #define REG_HSMC_REM0_0                      (0xFC05C2B0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 0) */
  #define REG_HSMC_REM1_0                      (0xFC05C2B4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 0) */
  #define REG_HSMC_REM2_0                      (0xFC05C2B8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 0) */
  #define REG_HSMC_REM3_0                      (0xFC05C2BCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 0) */
  #define REG_HSMC_REM4_0                      (0xFC05C2C0U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 0) */
  #define REG_HSMC_REM5_0                      (0xFC05C2C4U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 0) */
  #define REG_HSMC_REM6_0                      (0xFC05C2C8U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 0) */
  #define REG_HSMC_REM7_0                      (0xFC05C2CCU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 0) */
  #define REG_HSMC_REM8_0                      (0xFC05C2D0U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 0) */
  #define REG_HSMC_REM9_0                      (0xFC05C2D4U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 0) */
  #define REG_HSMC_REM10_0                     (0xFC05C2D8U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 0) */
  #define REG_HSMC_REM11_0                     (0xFC05C2DCU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 0) */
  #define REG_HSMC_REM0_1                      (0xFC05C2F0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 1) */
  #define REG_HSMC_REM1_1                      (0xFC05C2F4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 1) */
  #define REG_HSMC_REM2_1                      (0xFC05C2F8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 1) */
  #define REG_HSMC_REM3_1                      (0xFC05C2FCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 1) */
  #define REG_HSMC_REM4_1                      (0xFC05C300U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 1) */
  #define REG_HSMC_REM5_1                      (0xFC05C304U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 1) */
  #define REG_HSMC_REM6_1                      (0xFC05C308U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 1) */
  #define REG_HSMC_REM7_1                      (0xFC05C30CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 1) */
  #define REG_HSMC_REM8_1                      (0xFC05C310U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 1) */
  #define REG_HSMC_REM9_1                      (0xFC05C314U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 1) */
  #define REG_HSMC_REM10_1                     (0xFC05C318U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 1) */
  #define REG_HSMC_REM11_1                     (0xFC05C31CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 1) */
  #define REG_HSMC_REM0_2                      (0xFC05C330U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 2) */
  #define REG_HSMC_REM1_2                      (0xFC05C334U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 2) */
  #define REG_HSMC_REM2_2                      (0xFC05C338U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 2) */
  #define REG_HSMC_REM3_2                      (0xFC05C33CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 2) */
  #define REG_HSMC_REM4_2                      (0xFC05C340U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 2) */
  #define REG_HSMC_REM5_2                      (0xFC05C344U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 2) */
  #define REG_HSMC_REM6_2                      (0xFC05C348U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 2) */
  #define REG_HSMC_REM7_2                      (0xFC05C34CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 2) */
  #define REG_HSMC_REM8_2                      (0xFC05C350U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 2) */
  #define REG_HSMC_REM9_2                      (0xFC05C354U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 2) */
  #define REG_HSMC_REM10_2                     (0xFC05C358U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 2) */
  #define REG_HSMC_REM11_2                     (0xFC05C35CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 2) */
  #define REG_HSMC_REM0_3                      (0xFC05C370U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 3) */
  #define REG_HSMC_REM1_3                      (0xFC05C374U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 3) */
  #define REG_HSMC_REM2_3                      (0xFC05C378U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 3) */
  #define REG_HSMC_REM3_3                      (0xFC05C37CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 3) */
  #define REG_HSMC_REM4_3                      (0xFC05C380U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 3) */
  #define REG_HSMC_REM5_3                      (0xFC05C384U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 3) */
  #define REG_HSMC_REM6_3                      (0xFC05C388U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 3) */
  #define REG_HSMC_REM7_3                      (0xFC05C38CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 3) */
  #define REG_HSMC_REM8_3                      (0xFC05C390U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 3) */
  #define REG_HSMC_REM9_3                      (0xFC05C394U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 3) */
  #define REG_HSMC_REM10_3                     (0xFC05C398U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 3) */
  #define REG_HSMC_REM11_3                     (0xFC05C39CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 3) */
  #define REG_HSMC_REM0_4                      (0xFC05C3B0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 4) */
  #define REG_HSMC_REM1_4                      (0xFC05C3B4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 4) */
  #define REG_HSMC_REM2_4                      (0xFC05C3B8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 4) */
  #define REG_HSMC_REM3_4                      (0xFC05C3BCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 4) */
  #define REG_HSMC_REM4_4                      (0xFC05C3C0U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 4) */
  #define REG_HSMC_REM5_4                      (0xFC05C3C4U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 4) */
  #define REG_HSMC_REM6_4                      (0xFC05C3C8U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 4) */
  #define REG_HSMC_REM7_4                      (0xFC05C3CCU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 4) */
  #define REG_HSMC_REM8_4                      (0xFC05C3D0U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 4) */
  #define REG_HSMC_REM9_4                      (0xFC05C3D4U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 4) */
  #define REG_HSMC_REM10_4                     (0xFC05C3D8U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 4) */
  #define REG_HSMC_REM11_4                     (0xFC05C3DCU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 4) */
  #define REG_HSMC_REM0_5                      (0xFC05C3F0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 5) */
  #define REG_HSMC_REM1_5                      (0xFC05C3F4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 5) */
  #define REG_HSMC_REM2_5                      (0xFC05C3F8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 5) */
  #define REG_HSMC_REM3_5                      (0xFC05C3FCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 5) */
  #define REG_HSMC_REM4_5                      (0xFC05C400U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 5) */
  #define REG_HSMC_REM5_5                      (0xFC05C404U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 5) */
  #define REG_HSMC_REM6_5                      (0xFC05C408U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 5) */
  #define REG_HSMC_REM7_5                      (0xFC05C40CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 5) */
  #define REG_HSMC_REM8_5                      (0xFC05C410U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 5) */
  #define REG_HSMC_REM9_5                      (0xFC05C414U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 5) */
  #define REG_HSMC_REM10_5                     (0xFC05C418U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 5) */
  #define REG_HSMC_REM11_5                     (0xFC05C41CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 5) */
  #define REG_HSMC_REM0_6                      (0xFC05C430U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 6) */
  #define REG_HSMC_REM1_6                      (0xFC05C434U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 6) */
  #define REG_HSMC_REM2_6                      (0xFC05C438U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 6) */
  #define REG_HSMC_REM3_6                      (0xFC05C43CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 6) */
  #define REG_HSMC_REM4_6                      (0xFC05C440U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 6) */
  #define REG_HSMC_REM5_6                      (0xFC05C444U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 6) */
  #define REG_HSMC_REM6_6                      (0xFC05C448U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 6) */
  #define REG_HSMC_REM7_6                      (0xFC05C44CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 6) */
  #define REG_HSMC_REM8_6                      (0xFC05C450U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 6) */
  #define REG_HSMC_REM9_6                      (0xFC05C454U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 6) */
  #define REG_HSMC_REM10_6                     (0xFC05C458U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 6) */
  #define REG_HSMC_REM11_6                     (0xFC05C45CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 6) */
  #define REG_HSMC_REM0_7                      (0xFC05C470U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 7) */
  #define REG_HSMC_REM1_7                      (0xFC05C474U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 7) */
  #define REG_HSMC_REM2_7                      (0xFC05C478U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 7) */
  #define REG_HSMC_REM3_7                      (0xFC05C47CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 7) */
  #define REG_HSMC_REM4_7                      (0xFC05C480U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 7) */
  #define REG_HSMC_REM5_7                      (0xFC05C484U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 7) */
  #define REG_HSMC_REM6_7                      (0xFC05C488U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 7) */
  #define REG_HSMC_REM7_7                      (0xFC05C48CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 7) */
  #define REG_HSMC_REM8_7                      (0xFC05C490U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 7) */
  #define REG_HSMC_REM9_7                      (0xFC05C494U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 7) */
  #define REG_HSMC_REM10_7                     (0xFC05C498U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 7) */
  #define REG_HSMC_REM11_7                     (0xFC05C49CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 7) */
  #define REG_HSMC_ELCFG                       (0xFC05C500U) /**< \brief (HSMC) PMECC Error Location Configuration Register */
  #define REG_HSMC_ELPRIM                      (0xFC05C504U) /**< \brief (HSMC) PMECC Error Location Primitive Register */
  #define REG_HSMC_ELEN                        (0xFC05C508U) /**< \brief (HSMC) PMECC Error Location Enable Register */
  #define REG_HSMC_ELDIS                       (0xFC05C50CU) /**< \brief (HSMC) PMECC Error Location Disable Register */
  #define REG_HSMC_ELSR                        (0xFC05C510U) /**< \brief (HSMC) PMECC Error Location Status Register */
  #define REG_HSMC_ELIER                       (0xFC05C514U) /**< \brief (HSMC) PMECC Error Location Interrupt Enable register */
  #define REG_HSMC_ELIDR                       (0xFC05C518U) /**< \brief (HSMC) PMECC Error Location Interrupt Disable Register */
  #define REG_HSMC_ELIMR                       (0xFC05C51CU) /**< \brief (HSMC) PMECC Error Location Interrupt Mask Register */
  #define REG_HSMC_ELISR                       (0xFC05C520U) /**< \brief (HSMC) PMECC Error Location Interrupt Status Register */
  #define REG_HSMC_SIGMA0                      (0xFC05C528U) /**< \brief (HSMC) PMECC Error Location SIGMA 0 Register */
  #define REG_HSMC_SIGMA1                      (0xFC05C52CU) /**< \brief (HSMC) PMECC Error Location SIGMA 1 Register */
  #define REG_HSMC_SIGMA2                      (0xFC05C530U) /**< \brief (HSMC) PMECC Error Location SIGMA 2 Register */
  #define REG_HSMC_SIGMA3                      (0xFC05C534U) /**< \brief (HSMC) PMECC Error Location SIGMA 3 Register */
  #define REG_HSMC_SIGMA4                      (0xFC05C538U) /**< \brief (HSMC) PMECC Error Location SIGMA 4 Register */
  #define REG_HSMC_SIGMA5                      (0xFC05C53CU) /**< \brief (HSMC) PMECC Error Location SIGMA 5 Register */
  #define REG_HSMC_SIGMA6                      (0xFC05C540U) /**< \brief (HSMC) PMECC Error Location SIGMA 6 Register */
  #define REG_HSMC_SIGMA7                      (0xFC05C544U) /**< \brief (HSMC) PMECC Error Location SIGMA 7 Register */
  #define REG_HSMC_SIGMA8                      (0xFC05C548U) /**< \brief (HSMC) PMECC Error Location SIGMA 8 Register */
  #define REG_HSMC_SIGMA9                      (0xFC05C54CU) /**< \brief (HSMC) PMECC Error Location SIGMA 9 Register */
  #define REG_HSMC_SIGMA10                     (0xFC05C550U) /**< \brief (HSMC) PMECC Error Location SIGMA 10 Register */
  #define REG_HSMC_SIGMA11                     (0xFC05C554U) /**< \brief (HSMC) PMECC Error Location SIGMA 11 Register */
  #define REG_HSMC_SIGMA12                     (0xFC05C558U) /**< \brief (HSMC) PMECC Error Location SIGMA 12 Register */
  #define REG_HSMC_SIGMA13                     (0xFC05C55CU) /**< \brief (HSMC) PMECC Error Location SIGMA 13 Register */
  #define REG_HSMC_SIGMA14                     (0xFC05C560U) /**< \brief (HSMC) PMECC Error Location SIGMA 14 Register */
  #define REG_HSMC_SIGMA15                     (0xFC05C564U) /**< \brief (HSMC) PMECC Error Location SIGMA 15 Register */
  #define REG_HSMC_SIGMA16                     (0xFC05C568U) /**< \brief (HSMC) PMECC Error Location SIGMA 16 Register */
  #define REG_HSMC_SIGMA17                     (0xFC05C56CU) /**< \brief (HSMC) PMECC Error Location SIGMA 17 Register */
  #define REG_HSMC_SIGMA18                     (0xFC05C570U) /**< \brief (HSMC) PMECC Error Location SIGMA 18 Register */
  #define REG_HSMC_SIGMA19                     (0xFC05C574U) /**< \brief (HSMC) PMECC Error Location SIGMA 19 Register */
  #define REG_HSMC_SIGMA20                     (0xFC05C578U) /**< \brief (HSMC) PMECC Error Location SIGMA 20 Register */
  #define REG_HSMC_SIGMA21                     (0xFC05C57CU) /**< \brief (HSMC) PMECC Error Location SIGMA 21 Register */
  #define REG_HSMC_SIGMA22                     (0xFC05C580U) /**< \brief (HSMC) PMECC Error Location SIGMA 22 Register */
  #define REG_HSMC_SIGMA23                     (0xFC05C584U) /**< \brief (HSMC) PMECC Error Location SIGMA 23 Register */
  #define REG_HSMC_SIGMA24                     (0xFC05C588U) /**< \brief (HSMC) PMECC Error Location SIGMA 24 Register */
  #define REG_HSMC_ERRLOC                      (0xFC05C58CU) /**< \brief (HSMC) PMECC Error Location 0 Register */
  #define REG_HSMC_SETUP0                      (0xFC05C600U) /**< \brief (HSMC) HSMC Setup Register (CS_number = 0) */
  #define REG_HSMC_PULSE0                      (0xFC05C604U) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 0) */
  #define REG_HSMC_CYCLE0                      (0xFC05C608U) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 0) */
  #define REG_HSMC_TIMINGS0                    (0xFC05C60CU) /**< \brief (HSMC) HSMC Timings Register (CS_number = 0) */
  #define REG_HSMC_MODE0                       (0xFC05C610U) /**< \brief (HSMC) HSMC Mode Register (CS_number = 0) */
  #define REG_HSMC_SETUP1                      (0xFC05C614U) /**< \brief (HSMC) HSMC Setup Register (CS_number = 1) */
  #define REG_HSMC_PULSE1                      (0xFC05C618U) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 1) */
  #define REG_HSMC_CYCLE1                      (0xFC05C61CU) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 1) */
  #define REG_HSMC_TIMINGS1                    (0xFC05C620U) /**< \brief (HSMC) HSMC Timings Register (CS_number = 1) */
  #define REG_HSMC_MODE1                       (0xFC05C624U) /**< \brief (HSMC) HSMC Mode Register (CS_number = 1) */
  #define REG_HSMC_SETUP2                      (0xFC05C628U) /**< \brief (HSMC) HSMC Setup Register (CS_number = 2) */
  #define REG_HSMC_PULSE2                      (0xFC05C62CU) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 2) */
  #define REG_HSMC_CYCLE2                      (0xFC05C630U) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 2) */
  #define REG_HSMC_TIMINGS2                    (0xFC05C634U) /**< \brief (HSMC) HSMC Timings Register (CS_number = 2) */
  #define REG_HSMC_MODE2                       (0xFC05C638U) /**< \brief (HSMC) HSMC Mode Register (CS_number = 2) */
  #define REG_HSMC_SETUP3                      (0xFC05C63CU) /**< \brief (HSMC) HSMC Setup Register (CS_number = 3) */
  #define REG_HSMC_PULSE3                      (0xFC05C640U) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 3) */
  #define REG_HSMC_CYCLE3                      (0xFC05C644U) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 3) */
  #define REG_HSMC_TIMINGS3                    (0xFC05C648U) /**< \brief (HSMC) HSMC Timings Register (CS_number = 3) */
  #define REG_HSMC_MODE3                       (0xFC05C64CU) /**< \brief (HSMC) HSMC Mode Register (CS_number = 3) */
  #define REG_HSMC_OCMS                        (0xFC05C6A0U) /**< \brief (HSMC) HSMC Off Chip Memory Scrambling Register */
  #define REG_HSMC_KEY1                        (0xFC05C6A4U) /**< \brief (HSMC) HSMC Off Chip Memory Scrambling KEY1 Register */
  #define REG_HSMC_KEY2                        (0xFC05C6A8U) /**< \brief (HSMC) HSMC Off Chip Memory Scrambling KEY2 Register */
  #define REG_HSMC_WPMR                        (0xFC05C6E4U) /**< \brief (HSMC) HSMC Write Protection Mode Register */
  #define REG_HSMC_WPSR                        (0xFC05C6E8U) /**< \brief (HSMC) HSMC Write Protection Status Register */
#else
  #define REG_HSMC_CFG        (*(__IO uint32_t*)0xFC05C000U) /**< \brief (HSMC) HSMC NFC Configuration Register */
  #define REG_HSMC_CTRL       (*(__O  uint32_t*)0xFC05C004U) /**< \brief (HSMC) HSMC NFC Control Register */
  #define REG_HSMC_SR         (*(__I  uint32_t*)0xFC05C008U) /**< \brief (HSMC) HSMC NFC Status Register */
  #define REG_HSMC_IER        (*(__O  uint32_t*)0xFC05C00CU) /**< \brief (HSMC) HSMC NFC Interrupt Enable Register */
  #define REG_HSMC_IDR        (*(__O  uint32_t*)0xFC05C010U) /**< \brief (HSMC) HSMC NFC Interrupt Disable Register */
  #define REG_HSMC_IMR        (*(__I  uint32_t*)0xFC05C014U) /**< \brief (HSMC) HSMC NFC Interrupt Mask Register */
  #define REG_HSMC_ADDR       (*(__IO uint32_t*)0xFC05C018U) /**< \brief (HSMC) HSMC NFC Address Cycle Zero Register */
  #define REG_HSMC_BANK       (*(__IO uint32_t*)0xFC05C01CU) /**< \brief (HSMC) HSMC Bank Address Register */
  #define REG_HSMC_PMECCFG    (*(__IO uint32_t*)0xFC05C070U) /**< \brief (HSMC) PMECC Configuration Register */
  #define REG_HSMC_PMECCSAREA (*(__IO uint32_t*)0xFC05C074U) /**< \brief (HSMC) PMECC Spare Area Size Register */
  #define REG_HSMC_PMECCSADDR (*(__IO uint32_t*)0xFC05C078U) /**< \brief (HSMC) PMECC Start Address Register */
  #define REG_HSMC_PMECCEADDR (*(__IO uint32_t*)0xFC05C07CU) /**< \brief (HSMC) PMECC End Address Register */
  #define REG_HSMC_PMECCTRL   (*(__O  uint32_t*)0xFC05C084U) /**< \brief (HSMC) PMECC Control Register */
  #define REG_HSMC_PMECCSR    (*(__I  uint32_t*)0xFC05C088U) /**< \brief (HSMC) PMECC Status Register */
  #define REG_HSMC_PMECCIER   (*(__O  uint32_t*)0xFC05C08CU) /**< \brief (HSMC) PMECC Interrupt Enable register */
  #define REG_HSMC_PMECCIDR   (*(__O  uint32_t*)0xFC05C090U) /**< \brief (HSMC) PMECC Interrupt Disable Register */
  #define REG_HSMC_PMECCIMR   (*(__I  uint32_t*)0xFC05C094U) /**< \brief (HSMC) PMECC Interrupt Mask Register */
  #define REG_HSMC_PMECCISR   (*(__I  uint32_t*)0xFC05C098U) /**< \brief (HSMC) PMECC Interrupt Status Register */
  #define REG_HSMC_PMECC0_0   (*(__I  uint32_t*)0xFC05C0B0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 0) */
  #define REG_HSMC_PMECC1_0   (*(__I  uint32_t*)0xFC05C0B4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 0) */
  #define REG_HSMC_PMECC2_0   (*(__I  uint32_t*)0xFC05C0B8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 0) */
  #define REG_HSMC_PMECC3_0   (*(__I  uint32_t*)0xFC05C0BCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 0) */
  #define REG_HSMC_PMECC4_0   (*(__I  uint32_t*)0xFC05C0C0U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 0) */
  #define REG_HSMC_PMECC5_0   (*(__I  uint32_t*)0xFC05C0C4U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 0) */
  #define REG_HSMC_PMECC6_0   (*(__I  uint32_t*)0xFC05C0C8U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 0) */
  #define REG_HSMC_PMECC7_0   (*(__I  uint32_t*)0xFC05C0CCU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 0) */
  #define REG_HSMC_PMECC8_0   (*(__I  uint32_t*)0xFC05C0D0U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 0) */
  #define REG_HSMC_PMECC9_0   (*(__I  uint32_t*)0xFC05C0D4U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 0) */
  #define REG_HSMC_PMECC10_0  (*(__I  uint32_t*)0xFC05C0D8U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 0) */
  #define REG_HSMC_PMECC0_1   (*(__I  uint32_t*)0xFC05C0F0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 1) */
  #define REG_HSMC_PMECC1_1   (*(__I  uint32_t*)0xFC05C0F4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 1) */
  #define REG_HSMC_PMECC2_1   (*(__I  uint32_t*)0xFC05C0F8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 1) */
  #define REG_HSMC_PMECC3_1   (*(__I  uint32_t*)0xFC05C0FCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 1) */
  #define REG_HSMC_PMECC4_1   (*(__I  uint32_t*)0xFC05C100U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 1) */
  #define REG_HSMC_PMECC5_1   (*(__I  uint32_t*)0xFC05C104U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 1) */
  #define REG_HSMC_PMECC6_1   (*(__I  uint32_t*)0xFC05C108U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 1) */
  #define REG_HSMC_PMECC7_1   (*(__I  uint32_t*)0xFC05C10CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 1) */
  #define REG_HSMC_PMECC8_1   (*(__I  uint32_t*)0xFC05C110U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 1) */
  #define REG_HSMC_PMECC9_1   (*(__I  uint32_t*)0xFC05C114U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 1) */
  #define REG_HSMC_PMECC10_1  (*(__I  uint32_t*)0xFC05C118U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 1) */
  #define REG_HSMC_PMECC0_2   (*(__I  uint32_t*)0xFC05C130U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 2) */
  #define REG_HSMC_PMECC1_2   (*(__I  uint32_t*)0xFC05C134U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 2) */
  #define REG_HSMC_PMECC2_2   (*(__I  uint32_t*)0xFC05C138U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 2) */
  #define REG_HSMC_PMECC3_2   (*(__I  uint32_t*)0xFC05C13CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 2) */
  #define REG_HSMC_PMECC4_2   (*(__I  uint32_t*)0xFC05C140U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 2) */
  #define REG_HSMC_PMECC5_2   (*(__I  uint32_t*)0xFC05C144U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 2) */
  #define REG_HSMC_PMECC6_2   (*(__I  uint32_t*)0xFC05C148U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 2) */
  #define REG_HSMC_PMECC7_2   (*(__I  uint32_t*)0xFC05C14CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 2) */
  #define REG_HSMC_PMECC8_2   (*(__I  uint32_t*)0xFC05C150U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 2) */
  #define REG_HSMC_PMECC9_2   (*(__I  uint32_t*)0xFC05C154U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 2) */
  #define REG_HSMC_PMECC10_2  (*(__I  uint32_t*)0xFC05C158U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 2) */
  #define REG_HSMC_PMECC0_3   (*(__I  uint32_t*)0xFC05C170U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 3) */
  #define REG_HSMC_PMECC1_3   (*(__I  uint32_t*)0xFC05C174U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 3) */
  #define REG_HSMC_PMECC2_3   (*(__I  uint32_t*)0xFC05C178U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 3) */
  #define REG_HSMC_PMECC3_3   (*(__I  uint32_t*)0xFC05C17CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 3) */
  #define REG_HSMC_PMECC4_3   (*(__I  uint32_t*)0xFC05C180U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 3) */
  #define REG_HSMC_PMECC5_3   (*(__I  uint32_t*)0xFC05C184U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 3) */
  #define REG_HSMC_PMECC6_3   (*(__I  uint32_t*)0xFC05C188U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 3) */
  #define REG_HSMC_PMECC7_3   (*(__I  uint32_t*)0xFC05C18CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 3) */
  #define REG_HSMC_PMECC8_3   (*(__I  uint32_t*)0xFC05C190U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 3) */
  #define REG_HSMC_PMECC9_3   (*(__I  uint32_t*)0xFC05C194U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 3) */
  #define REG_HSMC_PMECC10_3  (*(__I  uint32_t*)0xFC05C198U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 3) */
  #define REG_HSMC_PMECC0_4   (*(__I  uint32_t*)0xFC05C1B0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 4) */
  #define REG_HSMC_PMECC1_4   (*(__I  uint32_t*)0xFC05C1B4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 4) */
  #define REG_HSMC_PMECC2_4   (*(__I  uint32_t*)0xFC05C1B8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 4) */
  #define REG_HSMC_PMECC3_4   (*(__I  uint32_t*)0xFC05C1BCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 4) */
  #define REG_HSMC_PMECC4_4   (*(__I  uint32_t*)0xFC05C1C0U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 4) */
  #define REG_HSMC_PMECC5_4   (*(__I  uint32_t*)0xFC05C1C4U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 4) */
  #define REG_HSMC_PMECC6_4   (*(__I  uint32_t*)0xFC05C1C8U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 4) */
  #define REG_HSMC_PMECC7_4   (*(__I  uint32_t*)0xFC05C1CCU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 4) */
  #define REG_HSMC_PMECC8_4   (*(__I  uint32_t*)0xFC05C1D0U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 4) */
  #define REG_HSMC_PMECC9_4   (*(__I  uint32_t*)0xFC05C1D4U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 4) */
  #define REG_HSMC_PMECC10_4  (*(__I  uint32_t*)0xFC05C1D8U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 4) */
  #define REG_HSMC_PMECC0_5   (*(__I  uint32_t*)0xFC05C1F0U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 5) */
  #define REG_HSMC_PMECC1_5   (*(__I  uint32_t*)0xFC05C1F4U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 5) */
  #define REG_HSMC_PMECC2_5   (*(__I  uint32_t*)0xFC05C1F8U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 5) */
  #define REG_HSMC_PMECC3_5   (*(__I  uint32_t*)0xFC05C1FCU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 5) */
  #define REG_HSMC_PMECC4_5   (*(__I  uint32_t*)0xFC05C200U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 5) */
  #define REG_HSMC_PMECC5_5   (*(__I  uint32_t*)0xFC05C204U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 5) */
  #define REG_HSMC_PMECC6_5   (*(__I  uint32_t*)0xFC05C208U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 5) */
  #define REG_HSMC_PMECC7_5   (*(__I  uint32_t*)0xFC05C20CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 5) */
  #define REG_HSMC_PMECC8_5   (*(__I  uint32_t*)0xFC05C210U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 5) */
  #define REG_HSMC_PMECC9_5   (*(__I  uint32_t*)0xFC05C214U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 5) */
  #define REG_HSMC_PMECC10_5  (*(__I  uint32_t*)0xFC05C218U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 5) */
  #define REG_HSMC_PMECC0_6   (*(__I  uint32_t*)0xFC05C230U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 6) */
  #define REG_HSMC_PMECC1_6   (*(__I  uint32_t*)0xFC05C234U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 6) */
  #define REG_HSMC_PMECC2_6   (*(__I  uint32_t*)0xFC05C238U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 6) */
  #define REG_HSMC_PMECC3_6   (*(__I  uint32_t*)0xFC05C23CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 6) */
  #define REG_HSMC_PMECC4_6   (*(__I  uint32_t*)0xFC05C240U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 6) */
  #define REG_HSMC_PMECC5_6   (*(__I  uint32_t*)0xFC05C244U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 6) */
  #define REG_HSMC_PMECC6_6   (*(__I  uint32_t*)0xFC05C248U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 6) */
  #define REG_HSMC_PMECC7_6   (*(__I  uint32_t*)0xFC05C24CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 6) */
  #define REG_HSMC_PMECC8_6   (*(__I  uint32_t*)0xFC05C250U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 6) */
  #define REG_HSMC_PMECC9_6   (*(__I  uint32_t*)0xFC05C254U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 6) */
  #define REG_HSMC_PMECC10_6  (*(__I  uint32_t*)0xFC05C258U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 6) */
  #define REG_HSMC_PMECC0_7   (*(__I  uint32_t*)0xFC05C270U) /**< \brief (HSMC) PMECC Redundancy 0 Register (sec_num = 7) */
  #define REG_HSMC_PMECC1_7   (*(__I  uint32_t*)0xFC05C274U) /**< \brief (HSMC) PMECC Redundancy 1 Register (sec_num = 7) */
  #define REG_HSMC_PMECC2_7   (*(__I  uint32_t*)0xFC05C278U) /**< \brief (HSMC) PMECC Redundancy 2 Register (sec_num = 7) */
  #define REG_HSMC_PMECC3_7   (*(__I  uint32_t*)0xFC05C27CU) /**< \brief (HSMC) PMECC Redundancy 3 Register (sec_num = 7) */
  #define REG_HSMC_PMECC4_7   (*(__I  uint32_t*)0xFC05C280U) /**< \brief (HSMC) PMECC Redundancy 4 Register (sec_num = 7) */
  #define REG_HSMC_PMECC5_7   (*(__I  uint32_t*)0xFC05C284U) /**< \brief (HSMC) PMECC Redundancy 5 Register (sec_num = 7) */
  #define REG_HSMC_PMECC6_7   (*(__I  uint32_t*)0xFC05C288U) /**< \brief (HSMC) PMECC Redundancy 6 Register (sec_num = 7) */
  #define REG_HSMC_PMECC7_7   (*(__I  uint32_t*)0xFC05C28CU) /**< \brief (HSMC) PMECC Redundancy 7 Register (sec_num = 7) */
  #define REG_HSMC_PMECC8_7   (*(__I  uint32_t*)0xFC05C290U) /**< \brief (HSMC) PMECC Redundancy 8 Register (sec_num = 7) */
  #define REG_HSMC_PMECC9_7   (*(__I  uint32_t*)0xFC05C294U) /**< \brief (HSMC) PMECC Redundancy 9 Register (sec_num = 7) */
  #define REG_HSMC_PMECC10_7  (*(__I  uint32_t*)0xFC05C298U) /**< \brief (HSMC) PMECC Redundancy 10 Register (sec_num = 7) */
  #define REG_HSMC_REM0_0     (*(__I  uint32_t*)0xFC05C2B0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 0) */
  #define REG_HSMC_REM1_0     (*(__I  uint32_t*)0xFC05C2B4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 0) */
  #define REG_HSMC_REM2_0     (*(__I  uint32_t*)0xFC05C2B8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 0) */
  #define REG_HSMC_REM3_0     (*(__I  uint32_t*)0xFC05C2BCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 0) */
  #define REG_HSMC_REM4_0     (*(__I  uint32_t*)0xFC05C2C0U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 0) */
  #define REG_HSMC_REM5_0     (*(__I  uint32_t*)0xFC05C2C4U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 0) */
  #define REG_HSMC_REM6_0     (*(__I  uint32_t*)0xFC05C2C8U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 0) */
  #define REG_HSMC_REM7_0     (*(__I  uint32_t*)0xFC05C2CCU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 0) */
  #define REG_HSMC_REM8_0     (*(__I  uint32_t*)0xFC05C2D0U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 0) */
  #define REG_HSMC_REM9_0     (*(__I  uint32_t*)0xFC05C2D4U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 0) */
  #define REG_HSMC_REM10_0    (*(__I  uint32_t*)0xFC05C2D8U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 0) */
  #define REG_HSMC_REM11_0    (*(__I  uint32_t*)0xFC05C2DCU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 0) */
  #define REG_HSMC_REM0_1     (*(__I  uint32_t*)0xFC05C2F0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 1) */
  #define REG_HSMC_REM1_1     (*(__I  uint32_t*)0xFC05C2F4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 1) */
  #define REG_HSMC_REM2_1     (*(__I  uint32_t*)0xFC05C2F8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 1) */
  #define REG_HSMC_REM3_1     (*(__I  uint32_t*)0xFC05C2FCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 1) */
  #define REG_HSMC_REM4_1     (*(__I  uint32_t*)0xFC05C300U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 1) */
  #define REG_HSMC_REM5_1     (*(__I  uint32_t*)0xFC05C304U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 1) */
  #define REG_HSMC_REM6_1     (*(__I  uint32_t*)0xFC05C308U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 1) */
  #define REG_HSMC_REM7_1     (*(__I  uint32_t*)0xFC05C30CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 1) */
  #define REG_HSMC_REM8_1     (*(__I  uint32_t*)0xFC05C310U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 1) */
  #define REG_HSMC_REM9_1     (*(__I  uint32_t*)0xFC05C314U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 1) */
  #define REG_HSMC_REM10_1    (*(__I  uint32_t*)0xFC05C318U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 1) */
  #define REG_HSMC_REM11_1    (*(__I  uint32_t*)0xFC05C31CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 1) */
  #define REG_HSMC_REM0_2     (*(__I  uint32_t*)0xFC05C330U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 2) */
  #define REG_HSMC_REM1_2     (*(__I  uint32_t*)0xFC05C334U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 2) */
  #define REG_HSMC_REM2_2     (*(__I  uint32_t*)0xFC05C338U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 2) */
  #define REG_HSMC_REM3_2     (*(__I  uint32_t*)0xFC05C33CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 2) */
  #define REG_HSMC_REM4_2     (*(__I  uint32_t*)0xFC05C340U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 2) */
  #define REG_HSMC_REM5_2     (*(__I  uint32_t*)0xFC05C344U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 2) */
  #define REG_HSMC_REM6_2     (*(__I  uint32_t*)0xFC05C348U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 2) */
  #define REG_HSMC_REM7_2     (*(__I  uint32_t*)0xFC05C34CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 2) */
  #define REG_HSMC_REM8_2     (*(__I  uint32_t*)0xFC05C350U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 2) */
  #define REG_HSMC_REM9_2     (*(__I  uint32_t*)0xFC05C354U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 2) */
  #define REG_HSMC_REM10_2    (*(__I  uint32_t*)0xFC05C358U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 2) */
  #define REG_HSMC_REM11_2    (*(__I  uint32_t*)0xFC05C35CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 2) */
  #define REG_HSMC_REM0_3     (*(__I  uint32_t*)0xFC05C370U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 3) */
  #define REG_HSMC_REM1_3     (*(__I  uint32_t*)0xFC05C374U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 3) */
  #define REG_HSMC_REM2_3     (*(__I  uint32_t*)0xFC05C378U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 3) */
  #define REG_HSMC_REM3_3     (*(__I  uint32_t*)0xFC05C37CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 3) */
  #define REG_HSMC_REM4_3     (*(__I  uint32_t*)0xFC05C380U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 3) */
  #define REG_HSMC_REM5_3     (*(__I  uint32_t*)0xFC05C384U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 3) */
  #define REG_HSMC_REM6_3     (*(__I  uint32_t*)0xFC05C388U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 3) */
  #define REG_HSMC_REM7_3     (*(__I  uint32_t*)0xFC05C38CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 3) */
  #define REG_HSMC_REM8_3     (*(__I  uint32_t*)0xFC05C390U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 3) */
  #define REG_HSMC_REM9_3     (*(__I  uint32_t*)0xFC05C394U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 3) */
  #define REG_HSMC_REM10_3    (*(__I  uint32_t*)0xFC05C398U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 3) */
  #define REG_HSMC_REM11_3    (*(__I  uint32_t*)0xFC05C39CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 3) */
  #define REG_HSMC_REM0_4     (*(__I  uint32_t*)0xFC05C3B0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 4) */
  #define REG_HSMC_REM1_4     (*(__I  uint32_t*)0xFC05C3B4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 4) */
  #define REG_HSMC_REM2_4     (*(__I  uint32_t*)0xFC05C3B8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 4) */
  #define REG_HSMC_REM3_4     (*(__I  uint32_t*)0xFC05C3BCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 4) */
  #define REG_HSMC_REM4_4     (*(__I  uint32_t*)0xFC05C3C0U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 4) */
  #define REG_HSMC_REM5_4     (*(__I  uint32_t*)0xFC05C3C4U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 4) */
  #define REG_HSMC_REM6_4     (*(__I  uint32_t*)0xFC05C3C8U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 4) */
  #define REG_HSMC_REM7_4     (*(__I  uint32_t*)0xFC05C3CCU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 4) */
  #define REG_HSMC_REM8_4     (*(__I  uint32_t*)0xFC05C3D0U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 4) */
  #define REG_HSMC_REM9_4     (*(__I  uint32_t*)0xFC05C3D4U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 4) */
  #define REG_HSMC_REM10_4    (*(__I  uint32_t*)0xFC05C3D8U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 4) */
  #define REG_HSMC_REM11_4    (*(__I  uint32_t*)0xFC05C3DCU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 4) */
  #define REG_HSMC_REM0_5     (*(__I  uint32_t*)0xFC05C3F0U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 5) */
  #define REG_HSMC_REM1_5     (*(__I  uint32_t*)0xFC05C3F4U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 5) */
  #define REG_HSMC_REM2_5     (*(__I  uint32_t*)0xFC05C3F8U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 5) */
  #define REG_HSMC_REM3_5     (*(__I  uint32_t*)0xFC05C3FCU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 5) */
  #define REG_HSMC_REM4_5     (*(__I  uint32_t*)0xFC05C400U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 5) */
  #define REG_HSMC_REM5_5     (*(__I  uint32_t*)0xFC05C404U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 5) */
  #define REG_HSMC_REM6_5     (*(__I  uint32_t*)0xFC05C408U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 5) */
  #define REG_HSMC_REM7_5     (*(__I  uint32_t*)0xFC05C40CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 5) */
  #define REG_HSMC_REM8_5     (*(__I  uint32_t*)0xFC05C410U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 5) */
  #define REG_HSMC_REM9_5     (*(__I  uint32_t*)0xFC05C414U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 5) */
  #define REG_HSMC_REM10_5    (*(__I  uint32_t*)0xFC05C418U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 5) */
  #define REG_HSMC_REM11_5    (*(__I  uint32_t*)0xFC05C41CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 5) */
  #define REG_HSMC_REM0_6     (*(__I  uint32_t*)0xFC05C430U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 6) */
  #define REG_HSMC_REM1_6     (*(__I  uint32_t*)0xFC05C434U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 6) */
  #define REG_HSMC_REM2_6     (*(__I  uint32_t*)0xFC05C438U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 6) */
  #define REG_HSMC_REM3_6     (*(__I  uint32_t*)0xFC05C43CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 6) */
  #define REG_HSMC_REM4_6     (*(__I  uint32_t*)0xFC05C440U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 6) */
  #define REG_HSMC_REM5_6     (*(__I  uint32_t*)0xFC05C444U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 6) */
  #define REG_HSMC_REM6_6     (*(__I  uint32_t*)0xFC05C448U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 6) */
  #define REG_HSMC_REM7_6     (*(__I  uint32_t*)0xFC05C44CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 6) */
  #define REG_HSMC_REM8_6     (*(__I  uint32_t*)0xFC05C450U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 6) */
  #define REG_HSMC_REM9_6     (*(__I  uint32_t*)0xFC05C454U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 6) */
  #define REG_HSMC_REM10_6    (*(__I  uint32_t*)0xFC05C458U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 6) */
  #define REG_HSMC_REM11_6    (*(__I  uint32_t*)0xFC05C45CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 6) */
  #define REG_HSMC_REM0_7     (*(__I  uint32_t*)0xFC05C470U) /**< \brief (HSMC) PMECC Remainder 0 Register (sec_num = 7) */
  #define REG_HSMC_REM1_7     (*(__I  uint32_t*)0xFC05C474U) /**< \brief (HSMC) PMECC Remainder 1 Register (sec_num = 7) */
  #define REG_HSMC_REM2_7     (*(__I  uint32_t*)0xFC05C478U) /**< \brief (HSMC) PMECC Remainder 2 Register (sec_num = 7) */
  #define REG_HSMC_REM3_7     (*(__I  uint32_t*)0xFC05C47CU) /**< \brief (HSMC) PMECC Remainder 3 Register (sec_num = 7) */
  #define REG_HSMC_REM4_7     (*(__I  uint32_t*)0xFC05C480U) /**< \brief (HSMC) PMECC Remainder 4 Register (sec_num = 7) */
  #define REG_HSMC_REM5_7     (*(__I  uint32_t*)0xFC05C484U) /**< \brief (HSMC) PMECC Remainder 5 Register (sec_num = 7) */
  #define REG_HSMC_REM6_7     (*(__I  uint32_t*)0xFC05C488U) /**< \brief (HSMC) PMECC Remainder 6 Register (sec_num = 7) */
  #define REG_HSMC_REM7_7     (*(__I  uint32_t*)0xFC05C48CU) /**< \brief (HSMC) PMECC Remainder 7 Register (sec_num = 7) */
  #define REG_HSMC_REM8_7     (*(__I  uint32_t*)0xFC05C490U) /**< \brief (HSMC) PMECC Remainder 8 Register (sec_num = 7) */
  #define REG_HSMC_REM9_7     (*(__I  uint32_t*)0xFC05C494U) /**< \brief (HSMC) PMECC Remainder 9 Register (sec_num = 7) */
  #define REG_HSMC_REM10_7    (*(__I  uint32_t*)0xFC05C498U) /**< \brief (HSMC) PMECC Remainder 10 Register (sec_num = 7) */
  #define REG_HSMC_REM11_7    (*(__I  uint32_t*)0xFC05C49CU) /**< \brief (HSMC) PMECC Remainder 11 Register (sec_num = 7) */
  #define REG_HSMC_ELCFG      (*(__IO uint32_t*)0xFC05C500U) /**< \brief (HSMC) PMECC Error Location Configuration Register */
  #define REG_HSMC_ELPRIM     (*(__I  uint32_t*)0xFC05C504U) /**< \brief (HSMC) PMECC Error Location Primitive Register */
  #define REG_HSMC_ELEN       (*(__O  uint32_t*)0xFC05C508U) /**< \brief (HSMC) PMECC Error Location Enable Register */
  #define REG_HSMC_ELDIS      (*(__O  uint32_t*)0xFC05C50CU) /**< \brief (HSMC) PMECC Error Location Disable Register */
  #define REG_HSMC_ELSR       (*(__I  uint32_t*)0xFC05C510U) /**< \brief (HSMC) PMECC Error Location Status Register */
  #define REG_HSMC_ELIER      (*(__O  uint32_t*)0xFC05C514U) /**< \brief (HSMC) PMECC Error Location Interrupt Enable register */
  #define REG_HSMC_ELIDR      (*(__O  uint32_t*)0xFC05C518U) /**< \brief (HSMC) PMECC Error Location Interrupt Disable Register */
  #define REG_HSMC_ELIMR      (*(__I  uint32_t*)0xFC05C51CU) /**< \brief (HSMC) PMECC Error Location Interrupt Mask Register */
  #define REG_HSMC_ELISR      (*(__I  uint32_t*)0xFC05C520U) /**< \brief (HSMC) PMECC Error Location Interrupt Status Register */
  #define REG_HSMC_SIGMA0     (*(__IO uint32_t*)0xFC05C528U) /**< \brief (HSMC) PMECC Error Location SIGMA 0 Register */
  #define REG_HSMC_SIGMA1     (*(__IO uint32_t*)0xFC05C52CU) /**< \brief (HSMC) PMECC Error Location SIGMA 1 Register */
  #define REG_HSMC_SIGMA2     (*(__IO uint32_t*)0xFC05C530U) /**< \brief (HSMC) PMECC Error Location SIGMA 2 Register */
  #define REG_HSMC_SIGMA3     (*(__IO uint32_t*)0xFC05C534U) /**< \brief (HSMC) PMECC Error Location SIGMA 3 Register */
  #define REG_HSMC_SIGMA4     (*(__IO uint32_t*)0xFC05C538U) /**< \brief (HSMC) PMECC Error Location SIGMA 4 Register */
  #define REG_HSMC_SIGMA5     (*(__IO uint32_t*)0xFC05C53CU) /**< \brief (HSMC) PMECC Error Location SIGMA 5 Register */
  #define REG_HSMC_SIGMA6     (*(__IO uint32_t*)0xFC05C540U) /**< \brief (HSMC) PMECC Error Location SIGMA 6 Register */
  #define REG_HSMC_SIGMA7     (*(__IO uint32_t*)0xFC05C544U) /**< \brief (HSMC) PMECC Error Location SIGMA 7 Register */
  #define REG_HSMC_SIGMA8     (*(__IO uint32_t*)0xFC05C548U) /**< \brief (HSMC) PMECC Error Location SIGMA 8 Register */
  #define REG_HSMC_SIGMA9     (*(__IO uint32_t*)0xFC05C54CU) /**< \brief (HSMC) PMECC Error Location SIGMA 9 Register */
  #define REG_HSMC_SIGMA10    (*(__IO uint32_t*)0xFC05C550U) /**< \brief (HSMC) PMECC Error Location SIGMA 10 Register */
  #define REG_HSMC_SIGMA11    (*(__IO uint32_t*)0xFC05C554U) /**< \brief (HSMC) PMECC Error Location SIGMA 11 Register */
  #define REG_HSMC_SIGMA12    (*(__IO uint32_t*)0xFC05C558U) /**< \brief (HSMC) PMECC Error Location SIGMA 12 Register */
  #define REG_HSMC_SIGMA13    (*(__IO uint32_t*)0xFC05C55CU) /**< \brief (HSMC) PMECC Error Location SIGMA 13 Register */
  #define REG_HSMC_SIGMA14    (*(__IO uint32_t*)0xFC05C560U) /**< \brief (HSMC) PMECC Error Location SIGMA 14 Register */
  #define REG_HSMC_SIGMA15    (*(__IO uint32_t*)0xFC05C564U) /**< \brief (HSMC) PMECC Error Location SIGMA 15 Register */
  #define REG_HSMC_SIGMA16    (*(__IO uint32_t*)0xFC05C568U) /**< \brief (HSMC) PMECC Error Location SIGMA 16 Register */
  #define REG_HSMC_SIGMA17    (*(__IO uint32_t*)0xFC05C56CU) /**< \brief (HSMC) PMECC Error Location SIGMA 17 Register */
  #define REG_HSMC_SIGMA18    (*(__IO uint32_t*)0xFC05C570U) /**< \brief (HSMC) PMECC Error Location SIGMA 18 Register */
  #define REG_HSMC_SIGMA19    (*(__IO uint32_t*)0xFC05C574U) /**< \brief (HSMC) PMECC Error Location SIGMA 19 Register */
  #define REG_HSMC_SIGMA20    (*(__IO uint32_t*)0xFC05C578U) /**< \brief (HSMC) PMECC Error Location SIGMA 20 Register */
  #define REG_HSMC_SIGMA21    (*(__IO uint32_t*)0xFC05C57CU) /**< \brief (HSMC) PMECC Error Location SIGMA 21 Register */
  #define REG_HSMC_SIGMA22    (*(__IO uint32_t*)0xFC05C580U) /**< \brief (HSMC) PMECC Error Location SIGMA 22 Register */
  #define REG_HSMC_SIGMA23    (*(__IO uint32_t*)0xFC05C584U) /**< \brief (HSMC) PMECC Error Location SIGMA 23 Register */
  #define REG_HSMC_SIGMA24    (*(__IO uint32_t*)0xFC05C588U) /**< \brief (HSMC) PMECC Error Location SIGMA 24 Register */
  #define REG_HSMC_ERRLOC     (*(__I  uint32_t*)0xFC05C58CU) /**< \brief (HSMC) PMECC Error Location 0 Register */
  #define REG_HSMC_SETUP0     (*(__IO uint32_t*)0xFC05C600U) /**< \brief (HSMC) HSMC Setup Register (CS_number = 0) */
  #define REG_HSMC_PULSE0     (*(__IO uint32_t*)0xFC05C604U) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 0) */
  #define REG_HSMC_CYCLE0     (*(__IO uint32_t*)0xFC05C608U) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 0) */
  #define REG_HSMC_TIMINGS0   (*(__IO uint32_t*)0xFC05C60CU) /**< \brief (HSMC) HSMC Timings Register (CS_number = 0) */
  #define REG_HSMC_MODE0      (*(__IO uint32_t*)0xFC05C610U) /**< \brief (HSMC) HSMC Mode Register (CS_number = 0) */
  #define REG_HSMC_SETUP1     (*(__IO uint32_t*)0xFC05C614U) /**< \brief (HSMC) HSMC Setup Register (CS_number = 1) */
  #define REG_HSMC_PULSE1     (*(__IO uint32_t*)0xFC05C618U) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 1) */
  #define REG_HSMC_CYCLE1     (*(__IO uint32_t*)0xFC05C61CU) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 1) */
  #define REG_HSMC_TIMINGS1   (*(__IO uint32_t*)0xFC05C620U) /**< \brief (HSMC) HSMC Timings Register (CS_number = 1) */
  #define REG_HSMC_MODE1      (*(__IO uint32_t*)0xFC05C624U) /**< \brief (HSMC) HSMC Mode Register (CS_number = 1) */
  #define REG_HSMC_SETUP2     (*(__IO uint32_t*)0xFC05C628U) /**< \brief (HSMC) HSMC Setup Register (CS_number = 2) */
  #define REG_HSMC_PULSE2     (*(__IO uint32_t*)0xFC05C62CU) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 2) */
  #define REG_HSMC_CYCLE2     (*(__IO uint32_t*)0xFC05C630U) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 2) */
  #define REG_HSMC_TIMINGS2   (*(__IO uint32_t*)0xFC05C634U) /**< \brief (HSMC) HSMC Timings Register (CS_number = 2) */
  #define REG_HSMC_MODE2      (*(__IO uint32_t*)0xFC05C638U) /**< \brief (HSMC) HSMC Mode Register (CS_number = 2) */
  #define REG_HSMC_SETUP3     (*(__IO uint32_t*)0xFC05C63CU) /**< \brief (HSMC) HSMC Setup Register (CS_number = 3) */
  #define REG_HSMC_PULSE3     (*(__IO uint32_t*)0xFC05C640U) /**< \brief (HSMC) HSMC Pulse Register (CS_number = 3) */
  #define REG_HSMC_CYCLE3     (*(__IO uint32_t*)0xFC05C644U) /**< \brief (HSMC) HSMC Cycle Register (CS_number = 3) */
  #define REG_HSMC_TIMINGS3   (*(__IO uint32_t*)0xFC05C648U) /**< \brief (HSMC) HSMC Timings Register (CS_number = 3) */
  #define REG_HSMC_MODE3      (*(__IO uint32_t*)0xFC05C64CU) /**< \brief (HSMC) HSMC Mode Register (CS_number = 3) */
  #define REG_HSMC_OCMS       (*(__IO uint32_t*)0xFC05C6A0U) /**< \brief (HSMC) HSMC Off Chip Memory Scrambling Register */
  #define REG_HSMC_KEY1       (*(__O  uint32_t*)0xFC05C6A4U) /**< \brief (HSMC) HSMC Off Chip Memory Scrambling KEY1 Register */
  #define REG_HSMC_KEY2       (*(__O  uint32_t*)0xFC05C6A8U) /**< \brief (HSMC) HSMC Off Chip Memory Scrambling KEY2 Register */
  #define REG_HSMC_WPMR       (*(__IO uint32_t*)0xFC05C6E4U) /**< \brief (HSMC) HSMC Write Protection Mode Register */
  #define REG_HSMC_WPSR       (*(__I  uint32_t*)0xFC05C6E8U) /**< \brief (HSMC) HSMC Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D4_HSMC_INSTANCE_ */
