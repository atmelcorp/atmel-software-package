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

#ifndef _SAMA5D2_MATRIX0_INSTANCE_
#define _SAMA5D2_MATRIX0_INSTANCE_

/* ========== Register definition for MATRIX0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_MATRIX0_MCFG0                    (0xF0018000U) /**< \brief (MATRIX0) Master Configuration Register 0 */
  #define REG_MATRIX0_MCFG1                    (0xF0018004U) /**< \brief (MATRIX0) Master Configuration Register 1 */
  #define REG_MATRIX0_MCFG2                    (0xF0018008U) /**< \brief (MATRIX0) Master Configuration Register 2 */
  #define REG_MATRIX0_MCFG3                    (0xF001800CU) /**< \brief (MATRIX0) Master Configuration Register 3 */
  #define REG_MATRIX0_MCFG4                    (0xF0018010U) /**< \brief (MATRIX0) Master Configuration Register 4 */
  #define REG_MATRIX0_MCFG5                    (0xF0018014U) /**< \brief (MATRIX0) Master Configuration Register 5 */
  #define REG_MATRIX0_MCFG6                    (0xF0018018U) /**< \brief (MATRIX0) Master Configuration Register 6 */
  #define REG_MATRIX0_MCFG7                    (0xF001801CU) /**< \brief (MATRIX0) Master Configuration Register 7 */
  #define REG_MATRIX0_MCFG8                    (0xF0018020U) /**< \brief (MATRIX0) Master Configuration Register 8 */
  #define REG_MATRIX0_MCFG9                    (0xF0018024U) /**< \brief (MATRIX0) Master Configuration Register 9 */
  #define REG_MATRIX0_MCFG10                   (0xF0018028U) /**< \brief (MATRIX0) Master Configuration Register 10 */
  #define REG_MATRIX0_MCFG11                   (0xF001802CU) /**< \brief (MATRIX0) Master Configuration Register 11 */
  #define REG_MATRIX0_SCFG0                    (0xF0018040U) /**< \brief (MATRIX0) Slave Configuration Register 0 */
  #define REG_MATRIX0_SCFG1                    (0xF0018044U) /**< \brief (MATRIX0) Slave Configuration Register 1 */
  #define REG_MATRIX0_SCFG2                    (0xF0018048U) /**< \brief (MATRIX0) Slave Configuration Register 2 */
  #define REG_MATRIX0_SCFG3                    (0xF001804CU) /**< \brief (MATRIX0) Slave Configuration Register 3 */
  #define REG_MATRIX0_SCFG4                    (0xF0018050U) /**< \brief (MATRIX0) Slave Configuration Register 4 */
  #define REG_MATRIX0_SCFG5                    (0xF0018054U) /**< \brief (MATRIX0) Slave Configuration Register 5 */
  #define REG_MATRIX0_SCFG6                    (0xF0018058U) /**< \brief (MATRIX0) Slave Configuration Register 6 */
  #define REG_MATRIX0_SCFG7                    (0xF001805CU) /**< \brief (MATRIX0) Slave Configuration Register 7 */
  #define REG_MATRIX0_SCFG8                    (0xF0018060U) /**< \brief (MATRIX0) Slave Configuration Register 8 */
  #define REG_MATRIX0_SCFG9                    (0xF0018064U) /**< \brief (MATRIX0) Slave Configuration Register 9 */
  #define REG_MATRIX0_SCFG10                   (0xF0018068U) /**< \brief (MATRIX0) Slave Configuration Register 10 */
  #define REG_MATRIX0_SCFG11                   (0xF001806CU) /**< \brief (MATRIX0) Slave Configuration Register 11 */
  #define REG_MATRIX0_SCFG12                   (0xF0018070U) /**< \brief (MATRIX0) Slave Configuration Register 12 */
  #define REG_MATRIX0_SCFG13                   (0xF0018074U) /**< \brief (MATRIX0) Slave Configuration Register 13 */
  #define REG_MATRIX0_SCFG14                   (0xF0018078U) /**< \brief (MATRIX0) Slave Configuration Register 14 */
  #define REG_MATRIX0_PRAS0                    (0xF0018080U) /**< \brief (MATRIX0) Priority Register A for Slave 0 */
  #define REG_MATRIX0_PRBS0                    (0xF0018084U) /**< \brief (MATRIX0) Priority Register B for Slave 0 */
  #define REG_MATRIX0_PRAS1                    (0xF0018088U) /**< \brief (MATRIX0) Priority Register A for Slave 1 */
  #define REG_MATRIX0_PRBS1                    (0xF001808CU) /**< \brief (MATRIX0) Priority Register B for Slave 1 */
  #define REG_MATRIX0_PRAS2                    (0xF0018090U) /**< \brief (MATRIX0) Priority Register A for Slave 2 */
  #define REG_MATRIX0_PRBS2                    (0xF0018094U) /**< \brief (MATRIX0) Priority Register B for Slave 2 */
  #define REG_MATRIX0_PRAS3                    (0xF0018098U) /**< \brief (MATRIX0) Priority Register A for Slave 3 */
  #define REG_MATRIX0_PRBS3                    (0xF001809CU) /**< \brief (MATRIX0) Priority Register B for Slave 3 */
  #define REG_MATRIX0_PRAS4                    (0xF00180A0U) /**< \brief (MATRIX0) Priority Register A for Slave 4 */
  #define REG_MATRIX0_PRBS4                    (0xF00180A4U) /**< \brief (MATRIX0) Priority Register B for Slave 4 */
  #define REG_MATRIX0_PRAS5                    (0xF00180A8U) /**< \brief (MATRIX0) Priority Register A for Slave 5 */
  #define REG_MATRIX0_PRBS5                    (0xF00180ACU) /**< \brief (MATRIX0) Priority Register B for Slave 5 */
  #define REG_MATRIX0_PRAS6                    (0xF00180B0U) /**< \brief (MATRIX0) Priority Register A for Slave 6 */
  #define REG_MATRIX0_PRBS6                    (0xF00180B4U) /**< \brief (MATRIX0) Priority Register B for Slave 6 */
  #define REG_MATRIX0_PRAS7                    (0xF00180B8U) /**< \brief (MATRIX0) Priority Register A for Slave 7 */
  #define REG_MATRIX0_PRBS7                    (0xF00180BCU) /**< \brief (MATRIX0) Priority Register B for Slave 7 */
  #define REG_MATRIX0_PRAS8                    (0xF00180C0U) /**< \brief (MATRIX0) Priority Register A for Slave 8 */
  #define REG_MATRIX0_PRBS8                    (0xF00180C4U) /**< \brief (MATRIX0) Priority Register B for Slave 8 */
  #define REG_MATRIX0_PRAS9                    (0xF00180C8U) /**< \brief (MATRIX0) Priority Register A for Slave 9 */
  #define REG_MATRIX0_PRBS9                    (0xF00180CCU) /**< \brief (MATRIX0) Priority Register B for Slave 9 */
  #define REG_MATRIX0_PRAS10                   (0xF00180D0U) /**< \brief (MATRIX0) Priority Register A for Slave 10 */
  #define REG_MATRIX0_PRBS10                   (0xF00180D4U) /**< \brief (MATRIX0) Priority Register B for Slave 10 */
  #define REG_MATRIX0_PRAS11                   (0xF00180D8U) /**< \brief (MATRIX0) Priority Register A for Slave 11 */
  #define REG_MATRIX0_PRBS11                   (0xF00180DCU) /**< \brief (MATRIX0) Priority Register B for Slave 11 */
  #define REG_MATRIX0_PRAS12                   (0xF00180E0U) /**< \brief (MATRIX0) Priority Register A for Slave 12 */
  #define REG_MATRIX0_PRBS12                   (0xF00180E4U) /**< \brief (MATRIX0) Priority Register B for Slave 12 */
  #define REG_MATRIX0_PRAS13                   (0xF00180E8U) /**< \brief (MATRIX0) Priority Register A for Slave 13 */
  #define REG_MATRIX0_PRBS13                   (0xF00180ECU) /**< \brief (MATRIX0) Priority Register B for Slave 13 */
  #define REG_MATRIX0_PRAS14                   (0xF00180F0U) /**< \brief (MATRIX0) Priority Register A for Slave 14 */
  #define REG_MATRIX0_PRBS14                   (0xF00180F4U) /**< \brief (MATRIX0) Priority Register B for Slave 14 */
  #define REG_MATRIX0_MEIER                    (0xF0018150U) /**< \brief (MATRIX0) Master Error Interrupt Enable Register */
  #define REG_MATRIX0_MEIDR                    (0xF0018154U) /**< \brief (MATRIX0) Master Error Interrupt Disable Register */
  #define REG_MATRIX0_MEIMR                    (0xF0018158U) /**< \brief (MATRIX0) Master Error Interrupt Mask Register */
  #define REG_MATRIX0_MESR                     (0xF001815CU) /**< \brief (MATRIX0) Master Error Status Register */
  #define REG_MATRIX0_MEAR0                    (0xF0018160U) /**< \brief (MATRIX0) Master 0 Error Address Register */
  #define REG_MATRIX0_MEAR1                    (0xF0018164U) /**< \brief (MATRIX0) Master 1 Error Address Register */
  #define REG_MATRIX0_MEAR2                    (0xF0018168U) /**< \brief (MATRIX0) Master 2 Error Address Register */
  #define REG_MATRIX0_MEAR3                    (0xF001816CU) /**< \brief (MATRIX0) Master 3 Error Address Register */
  #define REG_MATRIX0_MEAR4                    (0xF0018170U) /**< \brief (MATRIX0) Master 4 Error Address Register */
  #define REG_MATRIX0_MEAR5                    (0xF0018174U) /**< \brief (MATRIX0) Master 5 Error Address Register */
  #define REG_MATRIX0_MEAR6                    (0xF0018178U) /**< \brief (MATRIX0) Master 6 Error Address Register */
  #define REG_MATRIX0_MEAR7                    (0xF001817CU) /**< \brief (MATRIX0) Master 7 Error Address Register */
  #define REG_MATRIX0_MEAR8                    (0xF0018180U) /**< \brief (MATRIX0) Master 8 Error Address Register */
  #define REG_MATRIX0_MEAR9                    (0xF0018184U) /**< \brief (MATRIX0) Master 9 Error Address Register */
  #define REG_MATRIX0_MEAR10                   (0xF0018188U) /**< \brief (MATRIX0) Master 10 Error Address Register */
  #define REG_MATRIX0_MEAR11                   (0xF001818CU) /**< \brief (MATRIX0) Master 11 Error Address Register */
  #define REG_MATRIX0_WPMR                     (0xF00181E4U) /**< \brief (MATRIX0) Write Protection Mode Register */
  #define REG_MATRIX0_WPSR                     (0xF00181E8U) /**< \brief (MATRIX0) Write Protection Status Register */
  #define REG_MATRIX0_VERSION                  (0xF00181FCU) /**< \brief (MATRIX0) Version Register */
  #define REG_MATRIX0_SSR0                     (0xF0018200U) /**< \brief (MATRIX0) Security Slave 0 Register */
  #define REG_MATRIX0_SSR1                     (0xF0018204U) /**< \brief (MATRIX0) Security Slave 1 Register */
  #define REG_MATRIX0_SSR2                     (0xF0018208U) /**< \brief (MATRIX0) Security Slave 2 Register */
  #define REG_MATRIX0_SSR3                     (0xF001820CU) /**< \brief (MATRIX0) Security Slave 3 Register */
  #define REG_MATRIX0_SSR4                     (0xF0018210U) /**< \brief (MATRIX0) Security Slave 4 Register */
  #define REG_MATRIX0_SSR5                     (0xF0018214U) /**< \brief (MATRIX0) Security Slave 5 Register */
  #define REG_MATRIX0_SSR6                     (0xF0018218U) /**< \brief (MATRIX0) Security Slave 6 Register */
  #define REG_MATRIX0_SSR7                     (0xF001821CU) /**< \brief (MATRIX0) Security Slave 7 Register */
  #define REG_MATRIX0_SSR8                     (0xF0018220U) /**< \brief (MATRIX0) Security Slave 8 Register */
  #define REG_MATRIX0_SSR9                     (0xF0018224U) /**< \brief (MATRIX0) Security Slave 9 Register */
  #define REG_MATRIX0_SSR10                    (0xF0018228U) /**< \brief (MATRIX0) Security Slave 10 Register */
  #define REG_MATRIX0_SSR11                    (0xF001822CU) /**< \brief (MATRIX0) Security Slave 11 Register */
  #define REG_MATRIX0_SSR12                    (0xF0018230U) /**< \brief (MATRIX0) Security Slave 12 Register */
  #define REG_MATRIX0_SSR13                    (0xF0018234U) /**< \brief (MATRIX0) Security Slave 13 Register */
  #define REG_MATRIX0_SSR14                    (0xF0018238U) /**< \brief (MATRIX0) Security Slave 14 Register */
  #define REG_MATRIX0_SASSR0                   (0xF0018240U) /**< \brief (MATRIX0) Security Areas Split Slave 0 Register */
  #define REG_MATRIX0_SASSR1                   (0xF0018244U) /**< \brief (MATRIX0) Security Areas Split Slave 1 Register */
  #define REG_MATRIX0_SASSR2                   (0xF0018248U) /**< \brief (MATRIX0) Security Areas Split Slave 2 Register */
  #define REG_MATRIX0_SASSR3                   (0xF001824CU) /**< \brief (MATRIX0) Security Areas Split Slave 3 Register */
  #define REG_MATRIX0_SASSR4                   (0xF0018250U) /**< \brief (MATRIX0) Security Areas Split Slave 4 Register */
  #define REG_MATRIX0_SASSR5                   (0xF0018254U) /**< \brief (MATRIX0) Security Areas Split Slave 5 Register */
  #define REG_MATRIX0_SASSR6                   (0xF0018258U) /**< \brief (MATRIX0) Security Areas Split Slave 6 Register */
  #define REG_MATRIX0_SASSR7                   (0xF001825CU) /**< \brief (MATRIX0) Security Areas Split Slave 7 Register */
  #define REG_MATRIX0_SASSR8                   (0xF0018260U) /**< \brief (MATRIX0) Security Areas Split Slave 8 Register */
  #define REG_MATRIX0_SASSR9                   (0xF0018264U) /**< \brief (MATRIX0) Security Areas Split Slave 9 Register */
  #define REG_MATRIX0_SASSR10                  (0xF0018268U) /**< \brief (MATRIX0) Security Areas Split Slave 10 Register */
  #define REG_MATRIX0_SASSR11                  (0xF001826CU) /**< \brief (MATRIX0) Security Areas Split Slave 11 Register */
  #define REG_MATRIX0_SASSR12                  (0xF0018270U) /**< \brief (MATRIX0) Security Areas Split Slave 12 Register */
  #define REG_MATRIX0_SASSR13                  (0xF0018274U) /**< \brief (MATRIX0) Security Areas Split Slave 13 Register */
  #define REG_MATRIX0_SASSR14                  (0xF0018278U) /**< \brief (MATRIX0) Security Areas Split Slave 14 Register */
  #define REG_MATRIX0_SRTSR1                   (0xF0018284U) /**< \brief (MATRIX0) Security Region Top Slave 1 Register */
  #define REG_MATRIX0_SRTSR2                   (0xF0018288U) /**< \brief (MATRIX0) Security Region Top Slave 2 Register */
  #define REG_MATRIX0_SRTSR3                   (0xF001828CU) /**< \brief (MATRIX0) Security Region Top Slave 3 Register */
  #define REG_MATRIX0_SRTSR4                   (0xF0018290U) /**< \brief (MATRIX0) Security Region Top Slave 4 Register */
  #define REG_MATRIX0_SRTSR5                   (0xF0018294U) /**< \brief (MATRIX0) Security Region Top Slave 5 Register */
  #define REG_MATRIX0_SRTSR6                   (0xF0018298U) /**< \brief (MATRIX0) Security Region Top Slave 6 Register */
  #define REG_MATRIX0_SRTSR7                   (0xF001829CU) /**< \brief (MATRIX0) Security Region Top Slave 7 Register */
  #define REG_MATRIX0_SRTSR8                   (0xF00182A0U) /**< \brief (MATRIX0) Security Region Top Slave 8 Register */
  #define REG_MATRIX0_SRTSR9                   (0xF00182A4U) /**< \brief (MATRIX0) Security Region Top Slave 9 Register */
  #define REG_MATRIX0_SRTSR10                  (0xF00182A8U) /**< \brief (MATRIX0) Security Region Top Slave 10 Register */
  #define REG_MATRIX0_SRTSR11                  (0xF00182ACU) /**< \brief (MATRIX0) Security Region Top Slave 11 Register */
  #define REG_MATRIX0_SRTSR12                  (0xF00182B0U) /**< \brief (MATRIX0) Security Region Top Slave 12 Register */
  #define REG_MATRIX0_SRTSR13                  (0xF00182B4U) /**< \brief (MATRIX0) Security Region Top Slave 13 Register */
  #define REG_MATRIX0_SRTSR14                  (0xF00182B8U) /**< \brief (MATRIX0) Security Region Top Slave 14 Register */
  #define REG_MATRIX0_SPSELR                   (0xF00182C0U) /**< \brief (MATRIX0) Security Peripheral Select 1 Register */
#else
  #define REG_MATRIX0_MCFG0   (*(__IO uint32_t*)0xF0018000U) /**< \brief (MATRIX0) Master Configuration Register 0 */
  #define REG_MATRIX0_MCFG1   (*(__IO uint32_t*)0xF0018004U) /**< \brief (MATRIX0) Master Configuration Register 1 */
  #define REG_MATRIX0_MCFG2   (*(__IO uint32_t*)0xF0018008U) /**< \brief (MATRIX0) Master Configuration Register 2 */
  #define REG_MATRIX0_MCFG3   (*(__IO uint32_t*)0xF001800CU) /**< \brief (MATRIX0) Master Configuration Register 3 */
  #define REG_MATRIX0_MCFG4   (*(__IO uint32_t*)0xF0018010U) /**< \brief (MATRIX0) Master Configuration Register 4 */
  #define REG_MATRIX0_MCFG5   (*(__IO uint32_t*)0xF0018014U) /**< \brief (MATRIX0) Master Configuration Register 5 */
  #define REG_MATRIX0_MCFG6   (*(__IO uint32_t*)0xF0018018U) /**< \brief (MATRIX0) Master Configuration Register 6 */
  #define REG_MATRIX0_MCFG7   (*(__IO uint32_t*)0xF001801CU) /**< \brief (MATRIX0) Master Configuration Register 7 */
  #define REG_MATRIX0_MCFG8   (*(__IO uint32_t*)0xF0018020U) /**< \brief (MATRIX0) Master Configuration Register 8 */
  #define REG_MATRIX0_MCFG9   (*(__IO uint32_t*)0xF0018024U) /**< \brief (MATRIX0) Master Configuration Register 9 */
  #define REG_MATRIX0_MCFG10  (*(__IO uint32_t*)0xF0018028U) /**< \brief (MATRIX0) Master Configuration Register 10 */
  #define REG_MATRIX0_MCFG11  (*(__IO uint32_t*)0xF001802CU) /**< \brief (MATRIX0) Master Configuration Register 11 */
  #define REG_MATRIX0_SCFG0   (*(__IO uint32_t*)0xF0018040U) /**< \brief (MATRIX0) Slave Configuration Register 0 */
  #define REG_MATRIX0_SCFG1   (*(__IO uint32_t*)0xF0018044U) /**< \brief (MATRIX0) Slave Configuration Register 1 */
  #define REG_MATRIX0_SCFG2   (*(__IO uint32_t*)0xF0018048U) /**< \brief (MATRIX0) Slave Configuration Register 2 */
  #define REG_MATRIX0_SCFG3   (*(__IO uint32_t*)0xF001804CU) /**< \brief (MATRIX0) Slave Configuration Register 3 */
  #define REG_MATRIX0_SCFG4   (*(__IO uint32_t*)0xF0018050U) /**< \brief (MATRIX0) Slave Configuration Register 4 */
  #define REG_MATRIX0_SCFG5   (*(__IO uint32_t*)0xF0018054U) /**< \brief (MATRIX0) Slave Configuration Register 5 */
  #define REG_MATRIX0_SCFG6   (*(__IO uint32_t*)0xF0018058U) /**< \brief (MATRIX0) Slave Configuration Register 6 */
  #define REG_MATRIX0_SCFG7   (*(__IO uint32_t*)0xF001805CU) /**< \brief (MATRIX0) Slave Configuration Register 7 */
  #define REG_MATRIX0_SCFG8   (*(__IO uint32_t*)0xF0018060U) /**< \brief (MATRIX0) Slave Configuration Register 8 */
  #define REG_MATRIX0_SCFG9   (*(__IO uint32_t*)0xF0018064U) /**< \brief (MATRIX0) Slave Configuration Register 9 */
  #define REG_MATRIX0_SCFG10  (*(__IO uint32_t*)0xF0018068U) /**< \brief (MATRIX0) Slave Configuration Register 10 */
  #define REG_MATRIX0_SCFG11  (*(__IO uint32_t*)0xF001806CU) /**< \brief (MATRIX0) Slave Configuration Register 11 */
  #define REG_MATRIX0_SCFG12  (*(__IO uint32_t*)0xF0018070U) /**< \brief (MATRIX0) Slave Configuration Register 12 */
  #define REG_MATRIX0_SCFG13  (*(__IO uint32_t*)0xF0018074U) /**< \brief (MATRIX0) Slave Configuration Register 13 */
  #define REG_MATRIX0_SCFG14  (*(__IO uint32_t*)0xF0018078U) /**< \brief (MATRIX0) Slave Configuration Register 14 */
  #define REG_MATRIX0_PRAS0   (*(__IO uint32_t*)0xF0018080U) /**< \brief (MATRIX0) Priority Register A for Slave 0 */
  #define REG_MATRIX0_PRBS0   (*(__IO uint32_t*)0xF0018084U) /**< \brief (MATRIX0) Priority Register B for Slave 0 */
  #define REG_MATRIX0_PRAS1   (*(__IO uint32_t*)0xF0018088U) /**< \brief (MATRIX0) Priority Register A for Slave 1 */
  #define REG_MATRIX0_PRBS1   (*(__IO uint32_t*)0xF001808CU) /**< \brief (MATRIX0) Priority Register B for Slave 1 */
  #define REG_MATRIX0_PRAS2   (*(__IO uint32_t*)0xF0018090U) /**< \brief (MATRIX0) Priority Register A for Slave 2 */
  #define REG_MATRIX0_PRBS2   (*(__IO uint32_t*)0xF0018094U) /**< \brief (MATRIX0) Priority Register B for Slave 2 */
  #define REG_MATRIX0_PRAS3   (*(__IO uint32_t*)0xF0018098U) /**< \brief (MATRIX0) Priority Register A for Slave 3 */
  #define REG_MATRIX0_PRBS3   (*(__IO uint32_t*)0xF001809CU) /**< \brief (MATRIX0) Priority Register B for Slave 3 */
  #define REG_MATRIX0_PRAS4   (*(__IO uint32_t*)0xF00180A0U) /**< \brief (MATRIX0) Priority Register A for Slave 4 */
  #define REG_MATRIX0_PRBS4   (*(__IO uint32_t*)0xF00180A4U) /**< \brief (MATRIX0) Priority Register B for Slave 4 */
  #define REG_MATRIX0_PRAS5   (*(__IO uint32_t*)0xF00180A8U) /**< \brief (MATRIX0) Priority Register A for Slave 5 */
  #define REG_MATRIX0_PRBS5   (*(__IO uint32_t*)0xF00180ACU) /**< \brief (MATRIX0) Priority Register B for Slave 5 */
  #define REG_MATRIX0_PRAS6   (*(__IO uint32_t*)0xF00180B0U) /**< \brief (MATRIX0) Priority Register A for Slave 6 */
  #define REG_MATRIX0_PRBS6   (*(__IO uint32_t*)0xF00180B4U) /**< \brief (MATRIX0) Priority Register B for Slave 6 */
  #define REG_MATRIX0_PRAS7   (*(__IO uint32_t*)0xF00180B8U) /**< \brief (MATRIX0) Priority Register A for Slave 7 */
  #define REG_MATRIX0_PRBS7   (*(__IO uint32_t*)0xF00180BCU) /**< \brief (MATRIX0) Priority Register B for Slave 7 */
  #define REG_MATRIX0_PRAS8   (*(__IO uint32_t*)0xF00180C0U) /**< \brief (MATRIX0) Priority Register A for Slave 8 */
  #define REG_MATRIX0_PRBS8   (*(__IO uint32_t*)0xF00180C4U) /**< \brief (MATRIX0) Priority Register B for Slave 8 */
  #define REG_MATRIX0_PRAS9   (*(__IO uint32_t*)0xF00180C8U) /**< \brief (MATRIX0) Priority Register A for Slave 9 */
  #define REG_MATRIX0_PRBS9   (*(__IO uint32_t*)0xF00180CCU) /**< \brief (MATRIX0) Priority Register B for Slave 9 */
  #define REG_MATRIX0_PRAS10  (*(__IO uint32_t*)0xF00180D0U) /**< \brief (MATRIX0) Priority Register A for Slave 10 */
  #define REG_MATRIX0_PRBS10  (*(__IO uint32_t*)0xF00180D4U) /**< \brief (MATRIX0) Priority Register B for Slave 10 */
  #define REG_MATRIX0_PRAS11  (*(__IO uint32_t*)0xF00180D8U) /**< \brief (MATRIX0) Priority Register A for Slave 11 */
  #define REG_MATRIX0_PRBS11  (*(__IO uint32_t*)0xF00180DCU) /**< \brief (MATRIX0) Priority Register B for Slave 11 */
  #define REG_MATRIX0_PRAS12  (*(__IO uint32_t*)0xF00180E0U) /**< \brief (MATRIX0) Priority Register A for Slave 12 */
  #define REG_MATRIX0_PRBS12  (*(__IO uint32_t*)0xF00180E4U) /**< \brief (MATRIX0) Priority Register B for Slave 12 */
  #define REG_MATRIX0_PRAS13  (*(__IO uint32_t*)0xF00180E8U) /**< \brief (MATRIX0) Priority Register A for Slave 13 */
  #define REG_MATRIX0_PRBS13  (*(__IO uint32_t*)0xF00180ECU) /**< \brief (MATRIX0) Priority Register B for Slave 13 */
  #define REG_MATRIX0_PRAS14  (*(__IO uint32_t*)0xF00180F0U) /**< \brief (MATRIX0) Priority Register A for Slave 14 */
  #define REG_MATRIX0_PRBS14  (*(__IO uint32_t*)0xF00180F4U) /**< \brief (MATRIX0) Priority Register B for Slave 14 */
  #define REG_MATRIX0_MEIER   (*(__O  uint32_t*)0xF0018150U) /**< \brief (MATRIX0) Master Error Interrupt Enable Register */
  #define REG_MATRIX0_MEIDR   (*(__O  uint32_t*)0xF0018154U) /**< \brief (MATRIX0) Master Error Interrupt Disable Register */
  #define REG_MATRIX0_MEIMR   (*(__I  uint32_t*)0xF0018158U) /**< \brief (MATRIX0) Master Error Interrupt Mask Register */
  #define REG_MATRIX0_MESR    (*(__I  uint32_t*)0xF001815CU) /**< \brief (MATRIX0) Master Error Status Register */
  #define REG_MATRIX0_MEAR0   (*(__I  uint32_t*)0xF0018160U) /**< \brief (MATRIX0) Master 0 Error Address Register */
  #define REG_MATRIX0_MEAR1   (*(__I  uint32_t*)0xF0018164U) /**< \brief (MATRIX0) Master 1 Error Address Register */
  #define REG_MATRIX0_MEAR2   (*(__I  uint32_t*)0xF0018168U) /**< \brief (MATRIX0) Master 2 Error Address Register */
  #define REG_MATRIX0_MEAR3   (*(__I  uint32_t*)0xF001816CU) /**< \brief (MATRIX0) Master 3 Error Address Register */
  #define REG_MATRIX0_MEAR4   (*(__I  uint32_t*)0xF0018170U) /**< \brief (MATRIX0) Master 4 Error Address Register */
  #define REG_MATRIX0_MEAR5   (*(__I  uint32_t*)0xF0018174U) /**< \brief (MATRIX0) Master 5 Error Address Register */
  #define REG_MATRIX0_MEAR6   (*(__I  uint32_t*)0xF0018178U) /**< \brief (MATRIX0) Master 6 Error Address Register */
  #define REG_MATRIX0_MEAR7   (*(__I  uint32_t*)0xF001817CU) /**< \brief (MATRIX0) Master 7 Error Address Register */
  #define REG_MATRIX0_MEAR8   (*(__I  uint32_t*)0xF0018180U) /**< \brief (MATRIX0) Master 8 Error Address Register */
  #define REG_MATRIX0_MEAR9   (*(__I  uint32_t*)0xF0018184U) /**< \brief (MATRIX0) Master 9 Error Address Register */
  #define REG_MATRIX0_MEAR10  (*(__I  uint32_t*)0xF0018188U) /**< \brief (MATRIX0) Master 10 Error Address Register */
  #define REG_MATRIX0_MEAR11  (*(__I  uint32_t*)0xF001818CU) /**< \brief (MATRIX0) Master 11 Error Address Register */
  #define REG_MATRIX0_WPMR    (*(__IO uint32_t*)0xF00181E4U) /**< \brief (MATRIX0) Write Protection Mode Register */
  #define REG_MATRIX0_WPSR    (*(__I  uint32_t*)0xF00181E8U) /**< \brief (MATRIX0) Write Protection Status Register */
  #define REG_MATRIX0_VERSION (*(__I  uint32_t*)0xF00181FCU) /**< \brief (MATRIX0) Version Register */
  #define REG_MATRIX0_SSR0    (*(__IO uint32_t*)0xF0018200U) /**< \brief (MATRIX0) Security Slave 0 Register */
  #define REG_MATRIX0_SSR1    (*(__IO uint32_t*)0xF0018204U) /**< \brief (MATRIX0) Security Slave 1 Register */
  #define REG_MATRIX0_SSR2    (*(__IO uint32_t*)0xF0018208U) /**< \brief (MATRIX0) Security Slave 2 Register */
  #define REG_MATRIX0_SSR3    (*(__IO uint32_t*)0xF001820CU) /**< \brief (MATRIX0) Security Slave 3 Register */
  #define REG_MATRIX0_SSR4    (*(__IO uint32_t*)0xF0018210U) /**< \brief (MATRIX0) Security Slave 4 Register */
  #define REG_MATRIX0_SSR5    (*(__IO uint32_t*)0xF0018214U) /**< \brief (MATRIX0) Security Slave 5 Register */
  #define REG_MATRIX0_SSR6    (*(__IO uint32_t*)0xF0018218U) /**< \brief (MATRIX0) Security Slave 6 Register */
  #define REG_MATRIX0_SSR7    (*(__IO uint32_t*)0xF001821CU) /**< \brief (MATRIX0) Security Slave 7 Register */
  #define REG_MATRIX0_SSR8    (*(__IO uint32_t*)0xF0018220U) /**< \brief (MATRIX0) Security Slave 8 Register */
  #define REG_MATRIX0_SSR9    (*(__IO uint32_t*)0xF0018224U) /**< \brief (MATRIX0) Security Slave 9 Register */
  #define REG_MATRIX0_SSR10   (*(__IO uint32_t*)0xF0018228U) /**< \brief (MATRIX0) Security Slave 10 Register */
  #define REG_MATRIX0_SSR11   (*(__IO uint32_t*)0xF001822CU) /**< \brief (MATRIX0) Security Slave 11 Register */
  #define REG_MATRIX0_SSR12   (*(__IO uint32_t*)0xF0018230U) /**< \brief (MATRIX0) Security Slave 12 Register */
  #define REG_MATRIX0_SSR13   (*(__IO uint32_t*)0xF0018234U) /**< \brief (MATRIX0) Security Slave 13 Register */
  #define REG_MATRIX0_SSR14   (*(__IO uint32_t*)0xF0018238U) /**< \brief (MATRIX0) Security Slave 14 Register */
  #define REG_MATRIX0_SASSR0  (*(__IO uint32_t*)0xF0018240U) /**< \brief (MATRIX0) Security Areas Split Slave 0 Register */
  #define REG_MATRIX0_SASSR1  (*(__IO uint32_t*)0xF0018244U) /**< \brief (MATRIX0) Security Areas Split Slave 1 Register */
  #define REG_MATRIX0_SASSR2  (*(__IO uint32_t*)0xF0018248U) /**< \brief (MATRIX0) Security Areas Split Slave 2 Register */
  #define REG_MATRIX0_SASSR3  (*(__IO uint32_t*)0xF001824CU) /**< \brief (MATRIX0) Security Areas Split Slave 3 Register */
  #define REG_MATRIX0_SASSR4  (*(__IO uint32_t*)0xF0018250U) /**< \brief (MATRIX0) Security Areas Split Slave 4 Register */
  #define REG_MATRIX0_SASSR5  (*(__IO uint32_t*)0xF0018254U) /**< \brief (MATRIX0) Security Areas Split Slave 5 Register */
  #define REG_MATRIX0_SASSR6  (*(__IO uint32_t*)0xF0018258U) /**< \brief (MATRIX0) Security Areas Split Slave 6 Register */
  #define REG_MATRIX0_SASSR7  (*(__IO uint32_t*)0xF001825CU) /**< \brief (MATRIX0) Security Areas Split Slave 7 Register */
  #define REG_MATRIX0_SASSR8  (*(__IO uint32_t*)0xF0018260U) /**< \brief (MATRIX0) Security Areas Split Slave 8 Register */
  #define REG_MATRIX0_SASSR9  (*(__IO uint32_t*)0xF0018264U) /**< \brief (MATRIX0) Security Areas Split Slave 9 Register */
  #define REG_MATRIX0_SASSR10 (*(__IO uint32_t*)0xF0018268U) /**< \brief (MATRIX0) Security Areas Split Slave 10 Register */
  #define REG_MATRIX0_SASSR11 (*(__IO uint32_t*)0xF001826CU) /**< \brief (MATRIX0) Security Areas Split Slave 11 Register */
  #define REG_MATRIX0_SASSR12 (*(__IO uint32_t*)0xF0018270U) /**< \brief (MATRIX0) Security Areas Split Slave 12 Register */
  #define REG_MATRIX0_SASSR13 (*(__IO uint32_t*)0xF0018274U) /**< \brief (MATRIX0) Security Areas Split Slave 13 Register */
  #define REG_MATRIX0_SASSR14 (*(__IO uint32_t*)0xF0018278U) /**< \brief (MATRIX0) Security Areas Split Slave 14 Register */
  #define REG_MATRIX0_SRTSR1  (*(__IO uint32_t*)0xF0018284U) /**< \brief (MATRIX0) Security Region Top Slave 1 Register */
  #define REG_MATRIX0_SRTSR2  (*(__IO uint32_t*)0xF0018288U) /**< \brief (MATRIX0) Security Region Top Slave 2 Register */
  #define REG_MATRIX0_SRTSR3  (*(__IO uint32_t*)0xF001828CU) /**< \brief (MATRIX0) Security Region Top Slave 3 Register */
  #define REG_MATRIX0_SRTSR4  (*(__IO uint32_t*)0xF0018290U) /**< \brief (MATRIX0) Security Region Top Slave 4 Register */
  #define REG_MATRIX0_SRTSR5  (*(__IO uint32_t*)0xF0018294U) /**< \brief (MATRIX0) Security Region Top Slave 5 Register */
  #define REG_MATRIX0_SRTSR6  (*(__IO uint32_t*)0xF0018298U) /**< \brief (MATRIX0) Security Region Top Slave 6 Register */
  #define REG_MATRIX0_SRTSR7  (*(__IO uint32_t*)0xF001829CU) /**< \brief (MATRIX0) Security Region Top Slave 7 Register */
  #define REG_MATRIX0_SRTSR8  (*(__IO uint32_t*)0xF00182A0U) /**< \brief (MATRIX0) Security Region Top Slave 8 Register */
  #define REG_MATRIX0_SRTSR9  (*(__IO uint32_t*)0xF00182A4U) /**< \brief (MATRIX0) Security Region Top Slave 9 Register */
  #define REG_MATRIX0_SRTSR10 (*(__IO uint32_t*)0xF00182A8U) /**< \brief (MATRIX0) Security Region Top Slave 10 Register */
  #define REG_MATRIX0_SRTSR11 (*(__IO uint32_t*)0xF00182ACU) /**< \brief (MATRIX0) Security Region Top Slave 11 Register */
  #define REG_MATRIX0_SRTSR12 (*(__IO uint32_t*)0xF00182B0U) /**< \brief (MATRIX0) Security Region Top Slave 12 Register */
  #define REG_MATRIX0_SRTSR13 (*(__IO uint32_t*)0xF00182B4U) /**< \brief (MATRIX0) Security Region Top Slave 13 Register */
  #define REG_MATRIX0_SRTSR14 (*(__IO uint32_t*)0xF00182B8U) /**< \brief (MATRIX0) Security Region Top Slave 14 Register */
  #define REG_MATRIX0_SPSELR  (*(__IO uint32_t*)0xF00182C0U) /**< \brief (MATRIX0) Security Peripheral Select 1 Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_MATRIX0_INSTANCE_ */
