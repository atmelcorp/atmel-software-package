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

#ifndef _SAMA5D4_MATRIX0_INSTANCE_
#define _SAMA5D4_MATRIX0_INSTANCE_

/* ========== Register definition for MATRIX0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_MATRIX0_MCFG                    (0xF001C000U) /**< \brief (MATRIX0) Master Configuration Register */
#define REG_MATRIX0_SCFG                    (0xF001C040U) /**< \brief (MATRIX0) Slave Configuration Register */
#define REG_MATRIX0_PRAS0                   (0xF001C080U) /**< \brief (MATRIX0) Priority Register A for Slave 0 */
#define REG_MATRIX0_PRBS0                   (0xF001C084U) /**< \brief (MATRIX0) Priority Register B for Slave 0 */
#define REG_MATRIX0_PRAS1                   (0xF001C088U) /**< \brief (MATRIX0) Priority Register A for Slave 1 */
#define REG_MATRIX0_PRBS1                   (0xF001C08CU) /**< \brief (MATRIX0) Priority Register B for Slave 1 */
#define REG_MATRIX0_PRAS2                   (0xF001C090U) /**< \brief (MATRIX0) Priority Register A for Slave 2 */
#define REG_MATRIX0_PRBS2                   (0xF001C094U) /**< \brief (MATRIX0) Priority Register B for Slave 2 */
#define REG_MATRIX0_PRAS3                   (0xF001C098U) /**< \brief (MATRIX0) Priority Register A for Slave 3 */
#define REG_MATRIX0_PRBS3                   (0xF001C09CU) /**< \brief (MATRIX0) Priority Register B for Slave 3 */
#define REG_MATRIX0_PRAS4                   (0xF001C0A0U) /**< \brief (MATRIX0) Priority Register A for Slave 4 */
#define REG_MATRIX0_PRBS4                   (0xF001C0A4U) /**< \brief (MATRIX0) Priority Register B for Slave 4 */
#define REG_MATRIX0_PRAS5                   (0xF001C0A8U) /**< \brief (MATRIX0) Priority Register A for Slave 5 */
#define REG_MATRIX0_PRBS5                   (0xF001C0ACU) /**< \brief (MATRIX0) Priority Register B for Slave 5 */
#define REG_MATRIX0_PRAS6                   (0xF001C0B0U) /**< \brief (MATRIX0) Priority Register A for Slave 6 */
#define REG_MATRIX0_PRBS6                   (0xF001C0B4U) /**< \brief (MATRIX0) Priority Register B for Slave 6 */
#define REG_MATRIX0_PRAS7                   (0xF001C0B8U) /**< \brief (MATRIX0) Priority Register A for Slave 7 */
#define REG_MATRIX0_PRBS7                   (0xF001C0BCU) /**< \brief (MATRIX0) Priority Register B for Slave 7 */
#define REG_MATRIX0_PRAS8                   (0xF001C0C0U) /**< \brief (MATRIX0) Priority Register A for Slave 8 */
#define REG_MATRIX0_PRBS8                   (0xF001C0C4U) /**< \brief (MATRIX0) Priority Register B for Slave 8 */
#define REG_MATRIX0_PRAS9                   (0xF001C0C8U) /**< \brief (MATRIX0) Priority Register A for Slave 9 */
#define REG_MATRIX0_PRBS9                   (0xF001C0CCU) /**< \brief (MATRIX0) Priority Register B for Slave 9 */
#define REG_MATRIX0_PRAS10                  (0xF001C0D0U) /**< \brief (MATRIX0) Priority Register A for Slave 10 */
#define REG_MATRIX0_PRBS10                  (0xF001C0D4U) /**< \brief (MATRIX0) Priority Register B for Slave 10 */
#define REG_MATRIX0_PRAS11                  (0xF001C0D8U) /**< \brief (MATRIX0) Priority Register A for Slave 11 */
#define REG_MATRIX0_PRBS11                  (0xF001C0DCU) /**< \brief (MATRIX0) Priority Register B for Slave 11 */
#define REG_MATRIX0_PRAS12                  (0xF001C0E0U) /**< \brief (MATRIX0) Priority Register A for Slave 12 */
#define REG_MATRIX0_PRBS12                  (0xF001C0E4U) /**< \brief (MATRIX0) Priority Register B for Slave 12 */
#define REG_MATRIX0_MEIER                   (0xF001C150U) /**< \brief (MATRIX0) Master Error Interrupt Enable Register */
#define REG_MATRIX0_MEIDR                   (0xF001C154U) /**< \brief (MATRIX0) Master Error Interrupt Disable Register */
#define REG_MATRIX0_MEIMR                   (0xF001C158U) /**< \brief (MATRIX0) Master Error Interrupt Mask Register */
#define REG_MATRIX0_MESR                    (0xF001C15CU) /**< \brief (MATRIX0) Master Error Status Register */
#define REG_MATRIX0_MEAR                    (0xF001C160U) /**< \brief (MATRIX0) Master 0 Error Address Register */
#define REG_MATRIX0_WPMR                    (0xF001C1E4U) /**< \brief (MATRIX0) Write Protection Mode Register */
#define REG_MATRIX0_WPSR                    (0xF001C1E8U) /**< \brief (MATRIX0) Write Protection Status Register */
#define REG_MATRIX0_SSR                     (0xF001C200U) /**< \brief (MATRIX0) Security Slave 0 Register */
#define REG_MATRIX0_SASSR                   (0xF001C240U) /**< \brief (MATRIX0) Security Areas Split Slave 0 Register */
#define REG_MATRIX0_SRTSR                   (0xF001C280U) /**< \brief (MATRIX0) Security Region Top Slave 1 Register */
#define REG_MATRIX0_SPSELR                  (0xF001C2C0U) /**< \brief (MATRIX0) Security Peripheral Select 1 Register */
#else
#define REG_MATRIX0_MCFG   (*(__IO uint32_t*)0xF001C000U) /**< \brief (MATRIX0) Master Configuration Register */
#define REG_MATRIX0_SCFG   (*(__IO uint32_t*)0xF001C040U) /**< \brief (MATRIX0) Slave Configuration Register */
#define REG_MATRIX0_PRAS0  (*(__IO uint32_t*)0xF001C080U) /**< \brief (MATRIX0) Priority Register A for Slave 0 */
#define REG_MATRIX0_PRBS0  (*(__IO uint32_t*)0xF001C084U) /**< \brief (MATRIX0) Priority Register B for Slave 0 */
#define REG_MATRIX0_PRAS1  (*(__IO uint32_t*)0xF001C088U) /**< \brief (MATRIX0) Priority Register A for Slave 1 */
#define REG_MATRIX0_PRBS1  (*(__IO uint32_t*)0xF001C08CU) /**< \brief (MATRIX0) Priority Register B for Slave 1 */
#define REG_MATRIX0_PRAS2  (*(__IO uint32_t*)0xF001C090U) /**< \brief (MATRIX0) Priority Register A for Slave 2 */
#define REG_MATRIX0_PRBS2  (*(__IO uint32_t*)0xF001C094U) /**< \brief (MATRIX0) Priority Register B for Slave 2 */
#define REG_MATRIX0_PRAS3  (*(__IO uint32_t*)0xF001C098U) /**< \brief (MATRIX0) Priority Register A for Slave 3 */
#define REG_MATRIX0_PRBS3  (*(__IO uint32_t*)0xF001C09CU) /**< \brief (MATRIX0) Priority Register B for Slave 3 */
#define REG_MATRIX0_PRAS4  (*(__IO uint32_t*)0xF001C0A0U) /**< \brief (MATRIX0) Priority Register A for Slave 4 */
#define REG_MATRIX0_PRBS4  (*(__IO uint32_t*)0xF001C0A4U) /**< \brief (MATRIX0) Priority Register B for Slave 4 */
#define REG_MATRIX0_PRAS5  (*(__IO uint32_t*)0xF001C0A8U) /**< \brief (MATRIX0) Priority Register A for Slave 5 */
#define REG_MATRIX0_PRBS5  (*(__IO uint32_t*)0xF001C0ACU) /**< \brief (MATRIX0) Priority Register B for Slave 5 */
#define REG_MATRIX0_PRAS6  (*(__IO uint32_t*)0xF001C0B0U) /**< \brief (MATRIX0) Priority Register A for Slave 6 */
#define REG_MATRIX0_PRBS6  (*(__IO uint32_t*)0xF001C0B4U) /**< \brief (MATRIX0) Priority Register B for Slave 6 */
#define REG_MATRIX0_PRAS7  (*(__IO uint32_t*)0xF001C0B8U) /**< \brief (MATRIX0) Priority Register A for Slave 7 */
#define REG_MATRIX0_PRBS7  (*(__IO uint32_t*)0xF001C0BCU) /**< \brief (MATRIX0) Priority Register B for Slave 7 */
#define REG_MATRIX0_PRAS8  (*(__IO uint32_t*)0xF001C0C0U) /**< \brief (MATRIX0) Priority Register A for Slave 8 */
#define REG_MATRIX0_PRBS8  (*(__IO uint32_t*)0xF001C0C4U) /**< \brief (MATRIX0) Priority Register B for Slave 8 */
#define REG_MATRIX0_PRAS9  (*(__IO uint32_t*)0xF001C0C8U) /**< \brief (MATRIX0) Priority Register A for Slave 9 */
#define REG_MATRIX0_PRBS9  (*(__IO uint32_t*)0xF001C0CCU) /**< \brief (MATRIX0) Priority Register B for Slave 9 */
#define REG_MATRIX0_PRAS10 (*(__IO uint32_t*)0xF001C0D0U) /**< \brief (MATRIX0) Priority Register A for Slave 10 */
#define REG_MATRIX0_PRBS10 (*(__IO uint32_t*)0xF001C0D4U) /**< \brief (MATRIX0) Priority Register B for Slave 10 */
#define REG_MATRIX0_PRAS11 (*(__IO uint32_t*)0xF001C0D8U) /**< \brief (MATRIX0) Priority Register A for Slave 11 */
#define REG_MATRIX0_PRBS11 (*(__IO uint32_t*)0xF001C0DCU) /**< \brief (MATRIX0) Priority Register B for Slave 11 */
#define REG_MATRIX0_PRAS12 (*(__IO uint32_t*)0xF001C0E0U) /**< \brief (MATRIX0) Priority Register A for Slave 12 */
#define REG_MATRIX0_PRBS12 (*(__IO uint32_t*)0xF001C0E4U) /**< \brief (MATRIX0) Priority Register B for Slave 12 */
#define REG_MATRIX0_MEIER  (*(__O  uint32_t*)0xF001C150U) /**< \brief (MATRIX0) Master Error Interrupt Enable Register */
#define REG_MATRIX0_MEIDR  (*(__O  uint32_t*)0xF001C154U) /**< \brief (MATRIX0) Master Error Interrupt Disable Register */
#define REG_MATRIX0_MEIMR  (*(__I  uint32_t*)0xF001C158U) /**< \brief (MATRIX0) Master Error Interrupt Mask Register */
#define REG_MATRIX0_MESR   (*(__I  uint32_t*)0xF001C15CU) /**< \brief (MATRIX0) Master Error Status Register */
#define REG_MATRIX0_MEAR   (*(__I  uint32_t*)0xF001C160U) /**< \brief (MATRIX0) Master 0 Error Address Register */
#define REG_MATRIX0_WPMR   (*(__IO uint32_t*)0xF001C1E4U) /**< \brief (MATRIX0) Write Protection Mode Register */
#define REG_MATRIX0_WPSR   (*(__I  uint32_t*)0xF001C1E8U) /**< \brief (MATRIX0) Write Protection Status Register */
#define REG_MATRIX0_SSR    (*(__IO uint32_t*)0xF001C200U) /**< \brief (MATRIX0) Security Slave 0 Register */
#define REG_MATRIX0_SASSR  (*(__IO uint32_t*)0xF001C240U) /**< \brief (MATRIX0) Security Areas Split Slave 0 Register */
#define REG_MATRIX0_SRTSR  (*(__IO uint32_t*)0xF001C280U) /**< \brief (MATRIX0) Security Region Top Slave 1 Register */
#define REG_MATRIX0_SPSELR (*(__IO uint32_t*)0xF001C2C0U) /**< \brief (MATRIX0) Security Peripheral Select 1 Register */
#endif				/* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif				/* _SAMA5D4_MATRIX0_INSTANCE_ */
