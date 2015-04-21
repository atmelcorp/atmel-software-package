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

#ifndef _SAMA5D4_MATRIX1_INSTANCE_
#define _SAMA5D4_MATRIX1_INSTANCE_

/* ========== Register definition for MATRIX1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_MATRIX1_MCFG                    (0xFC054000U) /**< \brief (MATRIX1) Master Configuration Register */
#define REG_MATRIX1_SCFG                    (0xFC054040U) /**< \brief (MATRIX1) Slave Configuration Register */
#define REG_MATRIX1_PRAS0                   (0xFC054080U) /**< \brief (MATRIX1) Priority Register A for Slave 0 */
#define REG_MATRIX1_PRBS0                   (0xFC054084U) /**< \brief (MATRIX1) Priority Register B for Slave 0 */
#define REG_MATRIX1_PRAS1                   (0xFC054088U) /**< \brief (MATRIX1) Priority Register A for Slave 1 */
#define REG_MATRIX1_PRBS1                   (0xFC05408CU) /**< \brief (MATRIX1) Priority Register B for Slave 1 */
#define REG_MATRIX1_PRAS2                   (0xFC054090U) /**< \brief (MATRIX1) Priority Register A for Slave 2 */
#define REG_MATRIX1_PRBS2                   (0xFC054094U) /**< \brief (MATRIX1) Priority Register B for Slave 2 */
#define REG_MATRIX1_PRAS3                   (0xFC054098U) /**< \brief (MATRIX1) Priority Register A for Slave 3 */
#define REG_MATRIX1_PRBS3                   (0xFC05409CU) /**< \brief (MATRIX1) Priority Register B for Slave 3 */
#define REG_MATRIX1_PRAS4                   (0xFC0540A0U) /**< \brief (MATRIX1) Priority Register A for Slave 4 */
#define REG_MATRIX1_PRBS4                   (0xFC0540A4U) /**< \brief (MATRIX1) Priority Register B for Slave 4 */
#define REG_MATRIX1_PRAS5                   (0xFC0540A8U) /**< \brief (MATRIX1) Priority Register A for Slave 5 */
#define REG_MATRIX1_PRBS5                   (0xFC0540ACU) /**< \brief (MATRIX1) Priority Register B for Slave 5 */
#define REG_MATRIX1_PRAS6                   (0xFC0540B0U) /**< \brief (MATRIX1) Priority Register A for Slave 6 */
#define REG_MATRIX1_PRBS6                   (0xFC0540B4U) /**< \brief (MATRIX1) Priority Register B for Slave 6 */
#define REG_MATRIX1_PRAS7                   (0xFC0540B8U) /**< \brief (MATRIX1) Priority Register A for Slave 7 */
#define REG_MATRIX1_PRBS7                   (0xFC0540BCU) /**< \brief (MATRIX1) Priority Register B for Slave 7 */
#define REG_MATRIX1_PRAS8                   (0xFC0540C0U) /**< \brief (MATRIX1) Priority Register A for Slave 8 */
#define REG_MATRIX1_PRBS8                   (0xFC0540C4U) /**< \brief (MATRIX1) Priority Register B for Slave 8 */
#define REG_MATRIX1_PRAS9                   (0xFC0540C8U) /**< \brief (MATRIX1) Priority Register A for Slave 9 */
#define REG_MATRIX1_PRBS9                   (0xFC0540CCU) /**< \brief (MATRIX1) Priority Register B for Slave 9 */
#define REG_MATRIX1_PRAS10                  (0xFC0540D0U) /**< \brief (MATRIX1) Priority Register A for Slave 10 */
#define REG_MATRIX1_PRBS10                  (0xFC0540D4U) /**< \brief (MATRIX1) Priority Register B for Slave 10 */
#define REG_MATRIX1_PRAS11                  (0xFC0540D8U) /**< \brief (MATRIX1) Priority Register A for Slave 11 */
#define REG_MATRIX1_PRBS11                  (0xFC0540DCU) /**< \brief (MATRIX1) Priority Register B for Slave 11 */
#define REG_MATRIX1_PRAS12                  (0xFC0540E0U) /**< \brief (MATRIX1) Priority Register A for Slave 12 */
#define REG_MATRIX1_PRBS12                  (0xFC0540E4U) /**< \brief (MATRIX1) Priority Register B for Slave 12 */
#define REG_MATRIX1_MEIER                   (0xFC054150U) /**< \brief (MATRIX1) Master Error Interrupt Enable Register */
#define REG_MATRIX1_MEIDR                   (0xFC054154U) /**< \brief (MATRIX1) Master Error Interrupt Disable Register */
#define REG_MATRIX1_MEIMR                   (0xFC054158U) /**< \brief (MATRIX1) Master Error Interrupt Mask Register */
#define REG_MATRIX1_MESR                    (0xFC05415CU) /**< \brief (MATRIX1) Master Error Status Register */
#define REG_MATRIX1_MEAR                    (0xFC054160U) /**< \brief (MATRIX1) Master 0 Error Address Register */
#define REG_MATRIX1_WPMR                    (0xFC0541E4U) /**< \brief (MATRIX1) Write Protection Mode Register */
#define REG_MATRIX1_WPSR                    (0xFC0541E8U) /**< \brief (MATRIX1) Write Protection Status Register */
#define REG_MATRIX1_SSR                     (0xFC054200U) /**< \brief (MATRIX1) Security Slave 0 Register */
#define REG_MATRIX1_SASSR                   (0xFC054240U) /**< \brief (MATRIX1) Security Areas Split Slave 0 Register */
#define REG_MATRIX1_SRTSR                   (0xFC054280U) /**< \brief (MATRIX1) Security Region Top Slave 1 Register */
#define REG_MATRIX1_SPSELR                  (0xFC0542C0U) /**< \brief (MATRIX1) Security Peripheral Select 1 Register */
#else
#define REG_MATRIX1_MCFG   (*(__IO uint32_t*)0xFC054000U) /**< \brief (MATRIX1) Master Configuration Register */
#define REG_MATRIX1_SCFG   (*(__IO uint32_t*)0xFC054040U) /**< \brief (MATRIX1) Slave Configuration Register */
#define REG_MATRIX1_PRAS0  (*(__IO uint32_t*)0xFC054080U) /**< \brief (MATRIX1) Priority Register A for Slave 0 */
#define REG_MATRIX1_PRBS0  (*(__IO uint32_t*)0xFC054084U) /**< \brief (MATRIX1) Priority Register B for Slave 0 */
#define REG_MATRIX1_PRAS1  (*(__IO uint32_t*)0xFC054088U) /**< \brief (MATRIX1) Priority Register A for Slave 1 */
#define REG_MATRIX1_PRBS1  (*(__IO uint32_t*)0xFC05408CU) /**< \brief (MATRIX1) Priority Register B for Slave 1 */
#define REG_MATRIX1_PRAS2  (*(__IO uint32_t*)0xFC054090U) /**< \brief (MATRIX1) Priority Register A for Slave 2 */
#define REG_MATRIX1_PRBS2  (*(__IO uint32_t*)0xFC054094U) /**< \brief (MATRIX1) Priority Register B for Slave 2 */
#define REG_MATRIX1_PRAS3  (*(__IO uint32_t*)0xFC054098U) /**< \brief (MATRIX1) Priority Register A for Slave 3 */
#define REG_MATRIX1_PRBS3  (*(__IO uint32_t*)0xFC05409CU) /**< \brief (MATRIX1) Priority Register B for Slave 3 */
#define REG_MATRIX1_PRAS4  (*(__IO uint32_t*)0xFC0540A0U) /**< \brief (MATRIX1) Priority Register A for Slave 4 */
#define REG_MATRIX1_PRBS4  (*(__IO uint32_t*)0xFC0540A4U) /**< \brief (MATRIX1) Priority Register B for Slave 4 */
#define REG_MATRIX1_PRAS5  (*(__IO uint32_t*)0xFC0540A8U) /**< \brief (MATRIX1) Priority Register A for Slave 5 */
#define REG_MATRIX1_PRBS5  (*(__IO uint32_t*)0xFC0540ACU) /**< \brief (MATRIX1) Priority Register B for Slave 5 */
#define REG_MATRIX1_PRAS6  (*(__IO uint32_t*)0xFC0540B0U) /**< \brief (MATRIX1) Priority Register A for Slave 6 */
#define REG_MATRIX1_PRBS6  (*(__IO uint32_t*)0xFC0540B4U) /**< \brief (MATRIX1) Priority Register B for Slave 6 */
#define REG_MATRIX1_PRAS7  (*(__IO uint32_t*)0xFC0540B8U) /**< \brief (MATRIX1) Priority Register A for Slave 7 */
#define REG_MATRIX1_PRBS7  (*(__IO uint32_t*)0xFC0540BCU) /**< \brief (MATRIX1) Priority Register B for Slave 7 */
#define REG_MATRIX1_PRAS8  (*(__IO uint32_t*)0xFC0540C0U) /**< \brief (MATRIX1) Priority Register A for Slave 8 */
#define REG_MATRIX1_PRBS8  (*(__IO uint32_t*)0xFC0540C4U) /**< \brief (MATRIX1) Priority Register B for Slave 8 */
#define REG_MATRIX1_PRAS9  (*(__IO uint32_t*)0xFC0540C8U) /**< \brief (MATRIX1) Priority Register A for Slave 9 */
#define REG_MATRIX1_PRBS9  (*(__IO uint32_t*)0xFC0540CCU) /**< \brief (MATRIX1) Priority Register B for Slave 9 */
#define REG_MATRIX1_PRAS10 (*(__IO uint32_t*)0xFC0540D0U) /**< \brief (MATRIX1) Priority Register A for Slave 10 */
#define REG_MATRIX1_PRBS10 (*(__IO uint32_t*)0xFC0540D4U) /**< \brief (MATRIX1) Priority Register B for Slave 10 */
#define REG_MATRIX1_PRAS11 (*(__IO uint32_t*)0xFC0540D8U) /**< \brief (MATRIX1) Priority Register A for Slave 11 */
#define REG_MATRIX1_PRBS11 (*(__IO uint32_t*)0xFC0540DCU) /**< \brief (MATRIX1) Priority Register B for Slave 11 */
#define REG_MATRIX1_PRAS12 (*(__IO uint32_t*)0xFC0540E0U) /**< \brief (MATRIX1) Priority Register A for Slave 12 */
#define REG_MATRIX1_PRBS12 (*(__IO uint32_t*)0xFC0540E4U) /**< \brief (MATRIX1) Priority Register B for Slave 12 */
#define REG_MATRIX1_MEIER  (*(__O  uint32_t*)0xFC054150U) /**< \brief (MATRIX1) Master Error Interrupt Enable Register */
#define REG_MATRIX1_MEIDR  (*(__O  uint32_t*)0xFC054154U) /**< \brief (MATRIX1) Master Error Interrupt Disable Register */
#define REG_MATRIX1_MEIMR  (*(__I  uint32_t*)0xFC054158U) /**< \brief (MATRIX1) Master Error Interrupt Mask Register */
#define REG_MATRIX1_MESR   (*(__I  uint32_t*)0xFC05415CU) /**< \brief (MATRIX1) Master Error Status Register */
#define REG_MATRIX1_MEAR   (*(__I  uint32_t*)0xFC054160U) /**< \brief (MATRIX1) Master 0 Error Address Register */
#define REG_MATRIX1_WPMR   (*(__IO uint32_t*)0xFC0541E4U) /**< \brief (MATRIX1) Write Protection Mode Register */
#define REG_MATRIX1_WPSR   (*(__I  uint32_t*)0xFC0541E8U) /**< \brief (MATRIX1) Write Protection Status Register */
#define REG_MATRIX1_SSR    (*(__IO uint32_t*)0xFC054200U) /**< \brief (MATRIX1) Security Slave 0 Register */
#define REG_MATRIX1_SASSR  (*(__IO uint32_t*)0xFC054240U) /**< \brief (MATRIX1) Security Areas Split Slave 0 Register */
#define REG_MATRIX1_SRTSR  (*(__IO uint32_t*)0xFC054280U) /**< \brief (MATRIX1) Security Region Top Slave 1 Register */
#define REG_MATRIX1_SPSELR (*(__IO uint32_t*)0xFC0542C0U) /**< \brief (MATRIX1) Security Peripheral Select 1 Register */
#endif				/* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif				/* _SAMA5D4_MATRIX1_INSTANCE_ */
