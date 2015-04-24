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

#ifndef _SAMA5D2_MATRIX1_INSTANCE_
#define _SAMA5D2_MATRIX1_INSTANCE_

/* ========== Register definition for MATRIX1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_MATRIX1_MCFG0                    (0xFC03C000U) /**< \brief (MATRIX1) Master Configuration Register 0 */
  #define REG_MATRIX1_MCFG1                    (0xFC03C004U) /**< \brief (MATRIX1) Master Configuration Register 1 */
  #define REG_MATRIX1_MCFG2                    (0xFC03C008U) /**< \brief (MATRIX1) Master Configuration Register 2 */
  #define REG_MATRIX1_MCFG3                    (0xFC03C00CU) /**< \brief (MATRIX1) Master Configuration Register 3 */
  #define REG_MATRIX1_MCFG4                    (0xFC03C010U) /**< \brief (MATRIX1) Master Configuration Register 4 */
  #define REG_MATRIX1_MCFG5                    (0xFC03C014U) /**< \brief (MATRIX1) Master Configuration Register 5 */
  #define REG_MATRIX1_MCFG6                    (0xFC03C018U) /**< \brief (MATRIX1) Master Configuration Register 6 */
  #define REG_MATRIX1_MCFG7                    (0xFC03C01CU) /**< \brief (MATRIX1) Master Configuration Register 7 */
  #define REG_MATRIX1_MCFG8                    (0xFC03C020U) /**< \brief (MATRIX1) Master Configuration Register 8 */
  #define REG_MATRIX1_MCFG9                    (0xFC03C024U) /**< \brief (MATRIX1) Master Configuration Register 9 */
  #define REG_MATRIX1_MCFG10                   (0xFC03C028U) /**< \brief (MATRIX1) Master Configuration Register 10 */
  #define REG_MATRIX1_MCFG11                   (0xFC03C02CU) /**< \brief (MATRIX1) Master Configuration Register 11 */
  #define REG_MATRIX1_SCFG0                    (0xFC03C040U) /**< \brief (MATRIX1) Slave Configuration Register 0 */
  #define REG_MATRIX1_SCFG1                    (0xFC03C044U) /**< \brief (MATRIX1) Slave Configuration Register 1 */
  #define REG_MATRIX1_SCFG2                    (0xFC03C048U) /**< \brief (MATRIX1) Slave Configuration Register 2 */
  #define REG_MATRIX1_SCFG3                    (0xFC03C04CU) /**< \brief (MATRIX1) Slave Configuration Register 3 */
  #define REG_MATRIX1_SCFG4                    (0xFC03C050U) /**< \brief (MATRIX1) Slave Configuration Register 4 */
  #define REG_MATRIX1_SCFG5                    (0xFC03C054U) /**< \brief (MATRIX1) Slave Configuration Register 5 */
  #define REG_MATRIX1_SCFG6                    (0xFC03C058U) /**< \brief (MATRIX1) Slave Configuration Register 6 */
  #define REG_MATRIX1_SCFG7                    (0xFC03C05CU) /**< \brief (MATRIX1) Slave Configuration Register 7 */
  #define REG_MATRIX1_SCFG8                    (0xFC03C060U) /**< \brief (MATRIX1) Slave Configuration Register 8 */
  #define REG_MATRIX1_SCFG9                    (0xFC03C064U) /**< \brief (MATRIX1) Slave Configuration Register 9 */
  #define REG_MATRIX1_SCFG10                   (0xFC03C068U) /**< \brief (MATRIX1) Slave Configuration Register 10 */
  #define REG_MATRIX1_SCFG11                   (0xFC03C06CU) /**< \brief (MATRIX1) Slave Configuration Register 11 */
  #define REG_MATRIX1_SCFG12                   (0xFC03C070U) /**< \brief (MATRIX1) Slave Configuration Register 12 */
  #define REG_MATRIX1_SCFG13                   (0xFC03C074U) /**< \brief (MATRIX1) Slave Configuration Register 13 */
  #define REG_MATRIX1_SCFG14                   (0xFC03C078U) /**< \brief (MATRIX1) Slave Configuration Register 14 */
  #define REG_MATRIX1_PRAS0                    (0xFC03C080U) /**< \brief (MATRIX1) Priority Register A for Slave 0 */
  #define REG_MATRIX1_PRBS0                    (0xFC03C084U) /**< \brief (MATRIX1) Priority Register B for Slave 0 */
  #define REG_MATRIX1_PRAS1                    (0xFC03C088U) /**< \brief (MATRIX1) Priority Register A for Slave 1 */
  #define REG_MATRIX1_PRBS1                    (0xFC03C08CU) /**< \brief (MATRIX1) Priority Register B for Slave 1 */
  #define REG_MATRIX1_PRAS2                    (0xFC03C090U) /**< \brief (MATRIX1) Priority Register A for Slave 2 */
  #define REG_MATRIX1_PRBS2                    (0xFC03C094U) /**< \brief (MATRIX1) Priority Register B for Slave 2 */
  #define REG_MATRIX1_PRAS3                    (0xFC03C098U) /**< \brief (MATRIX1) Priority Register A for Slave 3 */
  #define REG_MATRIX1_PRBS3                    (0xFC03C09CU) /**< \brief (MATRIX1) Priority Register B for Slave 3 */
  #define REG_MATRIX1_PRAS4                    (0xFC03C0A0U) /**< \brief (MATRIX1) Priority Register A for Slave 4 */
  #define REG_MATRIX1_PRBS4                    (0xFC03C0A4U) /**< \brief (MATRIX1) Priority Register B for Slave 4 */
  #define REG_MATRIX1_PRAS5                    (0xFC03C0A8U) /**< \brief (MATRIX1) Priority Register A for Slave 5 */
  #define REG_MATRIX1_PRBS5                    (0xFC03C0ACU) /**< \brief (MATRIX1) Priority Register B for Slave 5 */
  #define REG_MATRIX1_PRAS6                    (0xFC03C0B0U) /**< \brief (MATRIX1) Priority Register A for Slave 6 */
  #define REG_MATRIX1_PRBS6                    (0xFC03C0B4U) /**< \brief (MATRIX1) Priority Register B for Slave 6 */
  #define REG_MATRIX1_PRAS7                    (0xFC03C0B8U) /**< \brief (MATRIX1) Priority Register A for Slave 7 */
  #define REG_MATRIX1_PRBS7                    (0xFC03C0BCU) /**< \brief (MATRIX1) Priority Register B for Slave 7 */
  #define REG_MATRIX1_PRAS8                    (0xFC03C0C0U) /**< \brief (MATRIX1) Priority Register A for Slave 8 */
  #define REG_MATRIX1_PRBS8                    (0xFC03C0C4U) /**< \brief (MATRIX1) Priority Register B for Slave 8 */
  #define REG_MATRIX1_PRAS9                    (0xFC03C0C8U) /**< \brief (MATRIX1) Priority Register A for Slave 9 */
  #define REG_MATRIX1_PRBS9                    (0xFC03C0CCU) /**< \brief (MATRIX1) Priority Register B for Slave 9 */
  #define REG_MATRIX1_PRAS10                   (0xFC03C0D0U) /**< \brief (MATRIX1) Priority Register A for Slave 10 */
  #define REG_MATRIX1_PRBS10                   (0xFC03C0D4U) /**< \brief (MATRIX1) Priority Register B for Slave 10 */
  #define REG_MATRIX1_PRAS11                   (0xFC03C0D8U) /**< \brief (MATRIX1) Priority Register A for Slave 11 */
  #define REG_MATRIX1_PRBS11                   (0xFC03C0DCU) /**< \brief (MATRIX1) Priority Register B for Slave 11 */
  #define REG_MATRIX1_PRAS12                   (0xFC03C0E0U) /**< \brief (MATRIX1) Priority Register A for Slave 12 */
  #define REG_MATRIX1_PRBS12                   (0xFC03C0E4U) /**< \brief (MATRIX1) Priority Register B for Slave 12 */
  #define REG_MATRIX1_PRAS13                   (0xFC03C0E8U) /**< \brief (MATRIX1) Priority Register A for Slave 13 */
  #define REG_MATRIX1_PRBS13                   (0xFC03C0ECU) /**< \brief (MATRIX1) Priority Register B for Slave 13 */
  #define REG_MATRIX1_PRAS14                   (0xFC03C0F0U) /**< \brief (MATRIX1) Priority Register A for Slave 14 */
  #define REG_MATRIX1_PRBS14                   (0xFC03C0F4U) /**< \brief (MATRIX1) Priority Register B for Slave 14 */
  #define REG_MATRIX1_MEIER                    (0xFC03C150U) /**< \brief (MATRIX1) Master Error Interrupt Enable Register */
  #define REG_MATRIX1_MEIDR                    (0xFC03C154U) /**< \brief (MATRIX1) Master Error Interrupt Disable Register */
  #define REG_MATRIX1_MEIMR                    (0xFC03C158U) /**< \brief (MATRIX1) Master Error Interrupt Mask Register */
  #define REG_MATRIX1_MESR                     (0xFC03C15CU) /**< \brief (MATRIX1) Master Error Status Register */
  #define REG_MATRIX1_MEAR0                    (0xFC03C160U) /**< \brief (MATRIX1) Master 0 Error Address Register */
  #define REG_MATRIX1_MEAR1                    (0xFC03C164U) /**< \brief (MATRIX1) Master 1 Error Address Register */
  #define REG_MATRIX1_MEAR2                    (0xFC03C168U) /**< \brief (MATRIX1) Master 2 Error Address Register */
  #define REG_MATRIX1_MEAR3                    (0xFC03C16CU) /**< \brief (MATRIX1) Master 3 Error Address Register */
  #define REG_MATRIX1_MEAR4                    (0xFC03C170U) /**< \brief (MATRIX1) Master 4 Error Address Register */
  #define REG_MATRIX1_MEAR5                    (0xFC03C174U) /**< \brief (MATRIX1) Master 5 Error Address Register */
  #define REG_MATRIX1_MEAR6                    (0xFC03C178U) /**< \brief (MATRIX1) Master 6 Error Address Register */
  #define REG_MATRIX1_MEAR7                    (0xFC03C17CU) /**< \brief (MATRIX1) Master 7 Error Address Register */
  #define REG_MATRIX1_MEAR8                    (0xFC03C180U) /**< \brief (MATRIX1) Master 8 Error Address Register */
  #define REG_MATRIX1_MEAR9                    (0xFC03C184U) /**< \brief (MATRIX1) Master 9 Error Address Register */
  #define REG_MATRIX1_MEAR10                   (0xFC03C188U) /**< \brief (MATRIX1) Master 10 Error Address Register */
  #define REG_MATRIX1_MEAR11                   (0xFC03C18CU) /**< \brief (MATRIX1) Master 11 Error Address Register */
  #define REG_MATRIX1_WPMR                     (0xFC03C1E4U) /**< \brief (MATRIX1) Write Protection Mode Register */
  #define REG_MATRIX1_WPSR                     (0xFC03C1E8U) /**< \brief (MATRIX1) Write Protection Status Register */
  #define REG_MATRIX1_VERSION                  (0xFC03C1FCU) /**< \brief (MATRIX1) Version Register */
  #define REG_MATRIX1_SSR0                     (0xFC03C200U) /**< \brief (MATRIX1) Security Slave 0 Register */
  #define REG_MATRIX1_SSR1                     (0xFC03C204U) /**< \brief (MATRIX1) Security Slave 1 Register */
  #define REG_MATRIX1_SSR2                     (0xFC03C208U) /**< \brief (MATRIX1) Security Slave 2 Register */
  #define REG_MATRIX1_SSR3                     (0xFC03C20CU) /**< \brief (MATRIX1) Security Slave 3 Register */
  #define REG_MATRIX1_SSR4                     (0xFC03C210U) /**< \brief (MATRIX1) Security Slave 4 Register */
  #define REG_MATRIX1_SSR5                     (0xFC03C214U) /**< \brief (MATRIX1) Security Slave 5 Register */
  #define REG_MATRIX1_SSR6                     (0xFC03C218U) /**< \brief (MATRIX1) Security Slave 6 Register */
  #define REG_MATRIX1_SSR7                     (0xFC03C21CU) /**< \brief (MATRIX1) Security Slave 7 Register */
  #define REG_MATRIX1_SSR8                     (0xFC03C220U) /**< \brief (MATRIX1) Security Slave 8 Register */
  #define REG_MATRIX1_SSR9                     (0xFC03C224U) /**< \brief (MATRIX1) Security Slave 9 Register */
  #define REG_MATRIX1_SSR10                    (0xFC03C228U) /**< \brief (MATRIX1) Security Slave 10 Register */
  #define REG_MATRIX1_SSR11                    (0xFC03C22CU) /**< \brief (MATRIX1) Security Slave 11 Register */
  #define REG_MATRIX1_SSR12                    (0xFC03C230U) /**< \brief (MATRIX1) Security Slave 12 Register */
  #define REG_MATRIX1_SSR13                    (0xFC03C234U) /**< \brief (MATRIX1) Security Slave 13 Register */
  #define REG_MATRIX1_SSR14                    (0xFC03C238U) /**< \brief (MATRIX1) Security Slave 14 Register */
  #define REG_MATRIX1_SASSR0                   (0xFC03C240U) /**< \brief (MATRIX1) Security Areas Split Slave 0 Register */
  #define REG_MATRIX1_SASSR1                   (0xFC03C244U) /**< \brief (MATRIX1) Security Areas Split Slave 1 Register */
  #define REG_MATRIX1_SASSR2                   (0xFC03C248U) /**< \brief (MATRIX1) Security Areas Split Slave 2 Register */
  #define REG_MATRIX1_SASSR3                   (0xFC03C24CU) /**< \brief (MATRIX1) Security Areas Split Slave 3 Register */
  #define REG_MATRIX1_SASSR4                   (0xFC03C250U) /**< \brief (MATRIX1) Security Areas Split Slave 4 Register */
  #define REG_MATRIX1_SASSR5                   (0xFC03C254U) /**< \brief (MATRIX1) Security Areas Split Slave 5 Register */
  #define REG_MATRIX1_SASSR6                   (0xFC03C258U) /**< \brief (MATRIX1) Security Areas Split Slave 6 Register */
  #define REG_MATRIX1_SASSR7                   (0xFC03C25CU) /**< \brief (MATRIX1) Security Areas Split Slave 7 Register */
  #define REG_MATRIX1_SASSR8                   (0xFC03C260U) /**< \brief (MATRIX1) Security Areas Split Slave 8 Register */
  #define REG_MATRIX1_SASSR9                   (0xFC03C264U) /**< \brief (MATRIX1) Security Areas Split Slave 9 Register */
  #define REG_MATRIX1_SASSR10                  (0xFC03C268U) /**< \brief (MATRIX1) Security Areas Split Slave 10 Register */
  #define REG_MATRIX1_SASSR11                  (0xFC03C26CU) /**< \brief (MATRIX1) Security Areas Split Slave 11 Register */
  #define REG_MATRIX1_SASSR12                  (0xFC03C270U) /**< \brief (MATRIX1) Security Areas Split Slave 12 Register */
  #define REG_MATRIX1_SASSR13                  (0xFC03C274U) /**< \brief (MATRIX1) Security Areas Split Slave 13 Register */
  #define REG_MATRIX1_SASSR14                  (0xFC03C278U) /**< \brief (MATRIX1) Security Areas Split Slave 14 Register */
  #define REG_MATRIX1_SRTSR1                   (0xFC03C284U) /**< \brief (MATRIX1) Security Region Top Slave 1 Register */
  #define REG_MATRIX1_SRTSR2                   (0xFC03C288U) /**< \brief (MATRIX1) Security Region Top Slave 2 Register */
  #define REG_MATRIX1_SRTSR3                   (0xFC03C28CU) /**< \brief (MATRIX1) Security Region Top Slave 3 Register */
  #define REG_MATRIX1_SRTSR4                   (0xFC03C290U) /**< \brief (MATRIX1) Security Region Top Slave 4 Register */
  #define REG_MATRIX1_SRTSR5                   (0xFC03C294U) /**< \brief (MATRIX1) Security Region Top Slave 5 Register */
  #define REG_MATRIX1_SRTSR6                   (0xFC03C298U) /**< \brief (MATRIX1) Security Region Top Slave 6 Register */
  #define REG_MATRIX1_SRTSR7                   (0xFC03C29CU) /**< \brief (MATRIX1) Security Region Top Slave 7 Register */
  #define REG_MATRIX1_SRTSR8                   (0xFC03C2A0U) /**< \brief (MATRIX1) Security Region Top Slave 8 Register */
  #define REG_MATRIX1_SRTSR9                   (0xFC03C2A4U) /**< \brief (MATRIX1) Security Region Top Slave 9 Register */
  #define REG_MATRIX1_SRTSR10                  (0xFC03C2A8U) /**< \brief (MATRIX1) Security Region Top Slave 10 Register */
  #define REG_MATRIX1_SRTSR11                  (0xFC03C2ACU) /**< \brief (MATRIX1) Security Region Top Slave 11 Register */
  #define REG_MATRIX1_SRTSR12                  (0xFC03C2B0U) /**< \brief (MATRIX1) Security Region Top Slave 12 Register */
  #define REG_MATRIX1_SRTSR13                  (0xFC03C2B4U) /**< \brief (MATRIX1) Security Region Top Slave 13 Register */
  #define REG_MATRIX1_SRTSR14                  (0xFC03C2B8U) /**< \brief (MATRIX1) Security Region Top Slave 14 Register */
  #define REG_MATRIX1_SPSELR                   (0xFC03C2C0U) /**< \brief (MATRIX1) Security Peripheral Select 1 Register */
#else
  #define REG_MATRIX1_MCFG0   (*(__IO uint32_t*)0xFC03C000U) /**< \brief (MATRIX1) Master Configuration Register 0 */
  #define REG_MATRIX1_MCFG1   (*(__IO uint32_t*)0xFC03C004U) /**< \brief (MATRIX1) Master Configuration Register 1 */
  #define REG_MATRIX1_MCFG2   (*(__IO uint32_t*)0xFC03C008U) /**< \brief (MATRIX1) Master Configuration Register 2 */
  #define REG_MATRIX1_MCFG3   (*(__IO uint32_t*)0xFC03C00CU) /**< \brief (MATRIX1) Master Configuration Register 3 */
  #define REG_MATRIX1_MCFG4   (*(__IO uint32_t*)0xFC03C010U) /**< \brief (MATRIX1) Master Configuration Register 4 */
  #define REG_MATRIX1_MCFG5   (*(__IO uint32_t*)0xFC03C014U) /**< \brief (MATRIX1) Master Configuration Register 5 */
  #define REG_MATRIX1_MCFG6   (*(__IO uint32_t*)0xFC03C018U) /**< \brief (MATRIX1) Master Configuration Register 6 */
  #define REG_MATRIX1_MCFG7   (*(__IO uint32_t*)0xFC03C01CU) /**< \brief (MATRIX1) Master Configuration Register 7 */
  #define REG_MATRIX1_MCFG8   (*(__IO uint32_t*)0xFC03C020U) /**< \brief (MATRIX1) Master Configuration Register 8 */
  #define REG_MATRIX1_MCFG9   (*(__IO uint32_t*)0xFC03C024U) /**< \brief (MATRIX1) Master Configuration Register 9 */
  #define REG_MATRIX1_MCFG10  (*(__IO uint32_t*)0xFC03C028U) /**< \brief (MATRIX1) Master Configuration Register 10 */
  #define REG_MATRIX1_MCFG11  (*(__IO uint32_t*)0xFC03C02CU) /**< \brief (MATRIX1) Master Configuration Register 11 */
  #define REG_MATRIX1_SCFG0   (*(__IO uint32_t*)0xFC03C040U) /**< \brief (MATRIX1) Slave Configuration Register 0 */
  #define REG_MATRIX1_SCFG1   (*(__IO uint32_t*)0xFC03C044U) /**< \brief (MATRIX1) Slave Configuration Register 1 */
  #define REG_MATRIX1_SCFG2   (*(__IO uint32_t*)0xFC03C048U) /**< \brief (MATRIX1) Slave Configuration Register 2 */
  #define REG_MATRIX1_SCFG3   (*(__IO uint32_t*)0xFC03C04CU) /**< \brief (MATRIX1) Slave Configuration Register 3 */
  #define REG_MATRIX1_SCFG4   (*(__IO uint32_t*)0xFC03C050U) /**< \brief (MATRIX1) Slave Configuration Register 4 */
  #define REG_MATRIX1_SCFG5   (*(__IO uint32_t*)0xFC03C054U) /**< \brief (MATRIX1) Slave Configuration Register 5 */
  #define REG_MATRIX1_SCFG6   (*(__IO uint32_t*)0xFC03C058U) /**< \brief (MATRIX1) Slave Configuration Register 6 */
  #define REG_MATRIX1_SCFG7   (*(__IO uint32_t*)0xFC03C05CU) /**< \brief (MATRIX1) Slave Configuration Register 7 */
  #define REG_MATRIX1_SCFG8   (*(__IO uint32_t*)0xFC03C060U) /**< \brief (MATRIX1) Slave Configuration Register 8 */
  #define REG_MATRIX1_SCFG9   (*(__IO uint32_t*)0xFC03C064U) /**< \brief (MATRIX1) Slave Configuration Register 9 */
  #define REG_MATRIX1_SCFG10  (*(__IO uint32_t*)0xFC03C068U) /**< \brief (MATRIX1) Slave Configuration Register 10 */
  #define REG_MATRIX1_SCFG11  (*(__IO uint32_t*)0xFC03C06CU) /**< \brief (MATRIX1) Slave Configuration Register 11 */
  #define REG_MATRIX1_SCFG12  (*(__IO uint32_t*)0xFC03C070U) /**< \brief (MATRIX1) Slave Configuration Register 12 */
  #define REG_MATRIX1_SCFG13  (*(__IO uint32_t*)0xFC03C074U) /**< \brief (MATRIX1) Slave Configuration Register 13 */
  #define REG_MATRIX1_SCFG14  (*(__IO uint32_t*)0xFC03C078U) /**< \brief (MATRIX1) Slave Configuration Register 14 */
  #define REG_MATRIX1_PRAS0   (*(__IO uint32_t*)0xFC03C080U) /**< \brief (MATRIX1) Priority Register A for Slave 0 */
  #define REG_MATRIX1_PRBS0   (*(__IO uint32_t*)0xFC03C084U) /**< \brief (MATRIX1) Priority Register B for Slave 0 */
  #define REG_MATRIX1_PRAS1   (*(__IO uint32_t*)0xFC03C088U) /**< \brief (MATRIX1) Priority Register A for Slave 1 */
  #define REG_MATRIX1_PRBS1   (*(__IO uint32_t*)0xFC03C08CU) /**< \brief (MATRIX1) Priority Register B for Slave 1 */
  #define REG_MATRIX1_PRAS2   (*(__IO uint32_t*)0xFC03C090U) /**< \brief (MATRIX1) Priority Register A for Slave 2 */
  #define REG_MATRIX1_PRBS2   (*(__IO uint32_t*)0xFC03C094U) /**< \brief (MATRIX1) Priority Register B for Slave 2 */
  #define REG_MATRIX1_PRAS3   (*(__IO uint32_t*)0xFC03C098U) /**< \brief (MATRIX1) Priority Register A for Slave 3 */
  #define REG_MATRIX1_PRBS3   (*(__IO uint32_t*)0xFC03C09CU) /**< \brief (MATRIX1) Priority Register B for Slave 3 */
  #define REG_MATRIX1_PRAS4   (*(__IO uint32_t*)0xFC03C0A0U) /**< \brief (MATRIX1) Priority Register A for Slave 4 */
  #define REG_MATRIX1_PRBS4   (*(__IO uint32_t*)0xFC03C0A4U) /**< \brief (MATRIX1) Priority Register B for Slave 4 */
  #define REG_MATRIX1_PRAS5   (*(__IO uint32_t*)0xFC03C0A8U) /**< \brief (MATRIX1) Priority Register A for Slave 5 */
  #define REG_MATRIX1_PRBS5   (*(__IO uint32_t*)0xFC03C0ACU) /**< \brief (MATRIX1) Priority Register B for Slave 5 */
  #define REG_MATRIX1_PRAS6   (*(__IO uint32_t*)0xFC03C0B0U) /**< \brief (MATRIX1) Priority Register A for Slave 6 */
  #define REG_MATRIX1_PRBS6   (*(__IO uint32_t*)0xFC03C0B4U) /**< \brief (MATRIX1) Priority Register B for Slave 6 */
  #define REG_MATRIX1_PRAS7   (*(__IO uint32_t*)0xFC03C0B8U) /**< \brief (MATRIX1) Priority Register A for Slave 7 */
  #define REG_MATRIX1_PRBS7   (*(__IO uint32_t*)0xFC03C0BCU) /**< \brief (MATRIX1) Priority Register B for Slave 7 */
  #define REG_MATRIX1_PRAS8   (*(__IO uint32_t*)0xFC03C0C0U) /**< \brief (MATRIX1) Priority Register A for Slave 8 */
  #define REG_MATRIX1_PRBS8   (*(__IO uint32_t*)0xFC03C0C4U) /**< \brief (MATRIX1) Priority Register B for Slave 8 */
  #define REG_MATRIX1_PRAS9   (*(__IO uint32_t*)0xFC03C0C8U) /**< \brief (MATRIX1) Priority Register A for Slave 9 */
  #define REG_MATRIX1_PRBS9   (*(__IO uint32_t*)0xFC03C0CCU) /**< \brief (MATRIX1) Priority Register B for Slave 9 */
  #define REG_MATRIX1_PRAS10  (*(__IO uint32_t*)0xFC03C0D0U) /**< \brief (MATRIX1) Priority Register A for Slave 10 */
  #define REG_MATRIX1_PRBS10  (*(__IO uint32_t*)0xFC03C0D4U) /**< \brief (MATRIX1) Priority Register B for Slave 10 */
  #define REG_MATRIX1_PRAS11  (*(__IO uint32_t*)0xFC03C0D8U) /**< \brief (MATRIX1) Priority Register A for Slave 11 */
  #define REG_MATRIX1_PRBS11  (*(__IO uint32_t*)0xFC03C0DCU) /**< \brief (MATRIX1) Priority Register B for Slave 11 */
  #define REG_MATRIX1_PRAS12  (*(__IO uint32_t*)0xFC03C0E0U) /**< \brief (MATRIX1) Priority Register A for Slave 12 */
  #define REG_MATRIX1_PRBS12  (*(__IO uint32_t*)0xFC03C0E4U) /**< \brief (MATRIX1) Priority Register B for Slave 12 */
  #define REG_MATRIX1_PRAS13  (*(__IO uint32_t*)0xFC03C0E8U) /**< \brief (MATRIX1) Priority Register A for Slave 13 */
  #define REG_MATRIX1_PRBS13  (*(__IO uint32_t*)0xFC03C0ECU) /**< \brief (MATRIX1) Priority Register B for Slave 13 */
  #define REG_MATRIX1_PRAS14  (*(__IO uint32_t*)0xFC03C0F0U) /**< \brief (MATRIX1) Priority Register A for Slave 14 */
  #define REG_MATRIX1_PRBS14  (*(__IO uint32_t*)0xFC03C0F4U) /**< \brief (MATRIX1) Priority Register B for Slave 14 */
  #define REG_MATRIX1_MEIER   (*(__O  uint32_t*)0xFC03C150U) /**< \brief (MATRIX1) Master Error Interrupt Enable Register */
  #define REG_MATRIX1_MEIDR   (*(__O  uint32_t*)0xFC03C154U) /**< \brief (MATRIX1) Master Error Interrupt Disable Register */
  #define REG_MATRIX1_MEIMR   (*(__I  uint32_t*)0xFC03C158U) /**< \brief (MATRIX1) Master Error Interrupt Mask Register */
  #define REG_MATRIX1_MESR    (*(__I  uint32_t*)0xFC03C15CU) /**< \brief (MATRIX1) Master Error Status Register */
  #define REG_MATRIX1_MEAR0   (*(__I  uint32_t*)0xFC03C160U) /**< \brief (MATRIX1) Master 0 Error Address Register */
  #define REG_MATRIX1_MEAR1   (*(__I  uint32_t*)0xFC03C164U) /**< \brief (MATRIX1) Master 1 Error Address Register */
  #define REG_MATRIX1_MEAR2   (*(__I  uint32_t*)0xFC03C168U) /**< \brief (MATRIX1) Master 2 Error Address Register */
  #define REG_MATRIX1_MEAR3   (*(__I  uint32_t*)0xFC03C16CU) /**< \brief (MATRIX1) Master 3 Error Address Register */
  #define REG_MATRIX1_MEAR4   (*(__I  uint32_t*)0xFC03C170U) /**< \brief (MATRIX1) Master 4 Error Address Register */
  #define REG_MATRIX1_MEAR5   (*(__I  uint32_t*)0xFC03C174U) /**< \brief (MATRIX1) Master 5 Error Address Register */
  #define REG_MATRIX1_MEAR6   (*(__I  uint32_t*)0xFC03C178U) /**< \brief (MATRIX1) Master 6 Error Address Register */
  #define REG_MATRIX1_MEAR7   (*(__I  uint32_t*)0xFC03C17CU) /**< \brief (MATRIX1) Master 7 Error Address Register */
  #define REG_MATRIX1_MEAR8   (*(__I  uint32_t*)0xFC03C180U) /**< \brief (MATRIX1) Master 8 Error Address Register */
  #define REG_MATRIX1_MEAR9   (*(__I  uint32_t*)0xFC03C184U) /**< \brief (MATRIX1) Master 9 Error Address Register */
  #define REG_MATRIX1_MEAR10  (*(__I  uint32_t*)0xFC03C188U) /**< \brief (MATRIX1) Master 10 Error Address Register */
  #define REG_MATRIX1_MEAR11  (*(__I  uint32_t*)0xFC03C18CU) /**< \brief (MATRIX1) Master 11 Error Address Register */
  #define REG_MATRIX1_WPMR    (*(__IO uint32_t*)0xFC03C1E4U) /**< \brief (MATRIX1) Write Protection Mode Register */
  #define REG_MATRIX1_WPSR    (*(__I  uint32_t*)0xFC03C1E8U) /**< \brief (MATRIX1) Write Protection Status Register */
  #define REG_MATRIX1_VERSION (*(__I  uint32_t*)0xFC03C1FCU) /**< \brief (MATRIX1) Version Register */
  #define REG_MATRIX1_SSR0    (*(__IO uint32_t*)0xFC03C200U) /**< \brief (MATRIX1) Security Slave 0 Register */
  #define REG_MATRIX1_SSR1    (*(__IO uint32_t*)0xFC03C204U) /**< \brief (MATRIX1) Security Slave 1 Register */
  #define REG_MATRIX1_SSR2    (*(__IO uint32_t*)0xFC03C208U) /**< \brief (MATRIX1) Security Slave 2 Register */
  #define REG_MATRIX1_SSR3    (*(__IO uint32_t*)0xFC03C20CU) /**< \brief (MATRIX1) Security Slave 3 Register */
  #define REG_MATRIX1_SSR4    (*(__IO uint32_t*)0xFC03C210U) /**< \brief (MATRIX1) Security Slave 4 Register */
  #define REG_MATRIX1_SSR5    (*(__IO uint32_t*)0xFC03C214U) /**< \brief (MATRIX1) Security Slave 5 Register */
  #define REG_MATRIX1_SSR6    (*(__IO uint32_t*)0xFC03C218U) /**< \brief (MATRIX1) Security Slave 6 Register */
  #define REG_MATRIX1_SSR7    (*(__IO uint32_t*)0xFC03C21CU) /**< \brief (MATRIX1) Security Slave 7 Register */
  #define REG_MATRIX1_SSR8    (*(__IO uint32_t*)0xFC03C220U) /**< \brief (MATRIX1) Security Slave 8 Register */
  #define REG_MATRIX1_SSR9    (*(__IO uint32_t*)0xFC03C224U) /**< \brief (MATRIX1) Security Slave 9 Register */
  #define REG_MATRIX1_SSR10   (*(__IO uint32_t*)0xFC03C228U) /**< \brief (MATRIX1) Security Slave 10 Register */
  #define REG_MATRIX1_SSR11   (*(__IO uint32_t*)0xFC03C22CU) /**< \brief (MATRIX1) Security Slave 11 Register */
  #define REG_MATRIX1_SSR12   (*(__IO uint32_t*)0xFC03C230U) /**< \brief (MATRIX1) Security Slave 12 Register */
  #define REG_MATRIX1_SSR13   (*(__IO uint32_t*)0xFC03C234U) /**< \brief (MATRIX1) Security Slave 13 Register */
  #define REG_MATRIX1_SSR14   (*(__IO uint32_t*)0xFC03C238U) /**< \brief (MATRIX1) Security Slave 14 Register */
  #define REG_MATRIX1_SASSR0  (*(__IO uint32_t*)0xFC03C240U) /**< \brief (MATRIX1) Security Areas Split Slave 0 Register */
  #define REG_MATRIX1_SASSR1  (*(__IO uint32_t*)0xFC03C244U) /**< \brief (MATRIX1) Security Areas Split Slave 1 Register */
  #define REG_MATRIX1_SASSR2  (*(__IO uint32_t*)0xFC03C248U) /**< \brief (MATRIX1) Security Areas Split Slave 2 Register */
  #define REG_MATRIX1_SASSR3  (*(__IO uint32_t*)0xFC03C24CU) /**< \brief (MATRIX1) Security Areas Split Slave 3 Register */
  #define REG_MATRIX1_SASSR4  (*(__IO uint32_t*)0xFC03C250U) /**< \brief (MATRIX1) Security Areas Split Slave 4 Register */
  #define REG_MATRIX1_SASSR5  (*(__IO uint32_t*)0xFC03C254U) /**< \brief (MATRIX1) Security Areas Split Slave 5 Register */
  #define REG_MATRIX1_SASSR6  (*(__IO uint32_t*)0xFC03C258U) /**< \brief (MATRIX1) Security Areas Split Slave 6 Register */
  #define REG_MATRIX1_SASSR7  (*(__IO uint32_t*)0xFC03C25CU) /**< \brief (MATRIX1) Security Areas Split Slave 7 Register */
  #define REG_MATRIX1_SASSR8  (*(__IO uint32_t*)0xFC03C260U) /**< \brief (MATRIX1) Security Areas Split Slave 8 Register */
  #define REG_MATRIX1_SASSR9  (*(__IO uint32_t*)0xFC03C264U) /**< \brief (MATRIX1) Security Areas Split Slave 9 Register */
  #define REG_MATRIX1_SASSR10 (*(__IO uint32_t*)0xFC03C268U) /**< \brief (MATRIX1) Security Areas Split Slave 10 Register */
  #define REG_MATRIX1_SASSR11 (*(__IO uint32_t*)0xFC03C26CU) /**< \brief (MATRIX1) Security Areas Split Slave 11 Register */
  #define REG_MATRIX1_SASSR12 (*(__IO uint32_t*)0xFC03C270U) /**< \brief (MATRIX1) Security Areas Split Slave 12 Register */
  #define REG_MATRIX1_SASSR13 (*(__IO uint32_t*)0xFC03C274U) /**< \brief (MATRIX1) Security Areas Split Slave 13 Register */
  #define REG_MATRIX1_SASSR14 (*(__IO uint32_t*)0xFC03C278U) /**< \brief (MATRIX1) Security Areas Split Slave 14 Register */
  #define REG_MATRIX1_SRTSR1  (*(__IO uint32_t*)0xFC03C284U) /**< \brief (MATRIX1) Security Region Top Slave 1 Register */
  #define REG_MATRIX1_SRTSR2  (*(__IO uint32_t*)0xFC03C288U) /**< \brief (MATRIX1) Security Region Top Slave 2 Register */
  #define REG_MATRIX1_SRTSR3  (*(__IO uint32_t*)0xFC03C28CU) /**< \brief (MATRIX1) Security Region Top Slave 3 Register */
  #define REG_MATRIX1_SRTSR4  (*(__IO uint32_t*)0xFC03C290U) /**< \brief (MATRIX1) Security Region Top Slave 4 Register */
  #define REG_MATRIX1_SRTSR5  (*(__IO uint32_t*)0xFC03C294U) /**< \brief (MATRIX1) Security Region Top Slave 5 Register */
  #define REG_MATRIX1_SRTSR6  (*(__IO uint32_t*)0xFC03C298U) /**< \brief (MATRIX1) Security Region Top Slave 6 Register */
  #define REG_MATRIX1_SRTSR7  (*(__IO uint32_t*)0xFC03C29CU) /**< \brief (MATRIX1) Security Region Top Slave 7 Register */
  #define REG_MATRIX1_SRTSR8  (*(__IO uint32_t*)0xFC03C2A0U) /**< \brief (MATRIX1) Security Region Top Slave 8 Register */
  #define REG_MATRIX1_SRTSR9  (*(__IO uint32_t*)0xFC03C2A4U) /**< \brief (MATRIX1) Security Region Top Slave 9 Register */
  #define REG_MATRIX1_SRTSR10 (*(__IO uint32_t*)0xFC03C2A8U) /**< \brief (MATRIX1) Security Region Top Slave 10 Register */
  #define REG_MATRIX1_SRTSR11 (*(__IO uint32_t*)0xFC03C2ACU) /**< \brief (MATRIX1) Security Region Top Slave 11 Register */
  #define REG_MATRIX1_SRTSR12 (*(__IO uint32_t*)0xFC03C2B0U) /**< \brief (MATRIX1) Security Region Top Slave 12 Register */
  #define REG_MATRIX1_SRTSR13 (*(__IO uint32_t*)0xFC03C2B4U) /**< \brief (MATRIX1) Security Region Top Slave 13 Register */
  #define REG_MATRIX1_SRTSR14 (*(__IO uint32_t*)0xFC03C2B8U) /**< \brief (MATRIX1) Security Region Top Slave 14 Register */
  #define REG_MATRIX1_SPSELR  (*(__IO uint32_t*)0xFC03C2C0U) /**< \brief (MATRIX1) Security Peripheral Select 1 Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_MATRIX1_INSTANCE_ */
