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

#ifndef _SAM9X_SMC_INSTANCE_
#define _SAM9X_SMC_INSTANCE_

/* ========== Register definition for SMC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_SMC_SETUP0                  (0xFFFFEA00U) /**< \brief (SMC) SMC Setup Register (CS_number = 0) */
  #define REG_SMC_PULSE0                  (0xFFFFEA04U) /**< \brief (SMC) SMC Pulse Register (CS_number = 0) */
  #define REG_SMC_CYCLE0                  (0xFFFFEA08U) /**< \brief (SMC) SMC Cycle Register (CS_number = 0) */
  #define REG_SMC_MODE0                   (0xFFFFEA0CU) /**< \brief (SMC) SMC Mode Register (CS_number = 0) */
  #define REG_SMC_SETUP1                  (0xFFFFEA10U) /**< \brief (SMC) SMC Setup Register (CS_number = 1) */
  #define REG_SMC_PULSE1                  (0xFFFFEA14U) /**< \brief (SMC) SMC Pulse Register (CS_number = 1) */
  #define REG_SMC_CYCLE1                  (0xFFFFEA18U) /**< \brief (SMC) SMC Cycle Register (CS_number = 1) */
  #define REG_SMC_MODE1                   (0xFFFFEA1CU) /**< \brief (SMC) SMC Mode Register (CS_number = 1) */
  #define REG_SMC_SETUP2                  (0xFFFFEA20U) /**< \brief (SMC) SMC Setup Register (CS_number = 2) */
  #define REG_SMC_PULSE2                  (0xFFFFEA24U) /**< \brief (SMC) SMC Pulse Register (CS_number = 2) */
  #define REG_SMC_CYCLE2                  (0xFFFFEA28U) /**< \brief (SMC) SMC Cycle Register (CS_number = 2) */
  #define REG_SMC_MODE2                   (0xFFFFEA2CU) /**< \brief (SMC) SMC Mode Register (CS_number = 2) */
  #define REG_SMC_SETUP3                  (0xFFFFEA30U) /**< \brief (SMC) SMC Setup Register (CS_number = 3) */
  #define REG_SMC_PULSE3                  (0xFFFFEA34U) /**< \brief (SMC) SMC Pulse Register (CS_number = 3) */
  #define REG_SMC_CYCLE3                  (0xFFFFEA38U) /**< \brief (SMC) SMC Cycle Register (CS_number = 3) */
  #define REG_SMC_MODE3                   (0xFFFFEA3CU) /**< \brief (SMC) SMC Mode Register (CS_number = 3) */
  #define REG_SMC_SETUP4                  (0xFFFFEA40U) /**< \brief (SMC) SMC Setup Register (CS_number = 4) */
  #define REG_SMC_PULSE4                  (0xFFFFEA44U) /**< \brief (SMC) SMC Pulse Register (CS_number = 4) */
  #define REG_SMC_CYCLE4                  (0xFFFFEA48U) /**< \brief (SMC) SMC Cycle Register (CS_number = 4) */
  #define REG_SMC_MODE4                   (0xFFFFEA4CU) /**< \brief (SMC) SMC Mode Register (CS_number = 4) */
  #define REG_SMC_SETUP5                  (0xFFFFEA50U) /**< \brief (SMC) SMC Setup Register (CS_number = 5) */
  #define REG_SMC_PULSE5                  (0xFFFFEA54U) /**< \brief (SMC) SMC Pulse Register (CS_number = 5) */
  #define REG_SMC_CYCLE5                  (0xFFFFEA58U) /**< \brief (SMC) SMC Cycle Register (CS_number = 5) */
  #define REG_SMC_MODE5                   (0xFFFFEA5CU) /**< \brief (SMC) SMC Mode Register (CS_number = 5) */
  #define REG_SMC_OCMS                    (0xFFFFEA80U) /**< \brief (SMC) SMC Off-Chip Memory Scrambling Register */
  #define REG_SMC_KEY1                    (0xFFFFEA84U) /**< \brief (SMC) SMC Off-Chip Memory Scrambling KEY1 Register */
  #define REG_SMC_KEY2                    (0xFFFFEA88U) /**< \brief (SMC) SMC Off-Chip Memory Scrambling KEY2 Register */
  #define REG_SMC_SRIER                   (0xFFFFEA90U) /**< \brief (SMC) SMC Safety Report Interrupt Enable Register */
  #define REG_SMC_WPMR                    (0xFFFFEAE4U) /**< \brief (SMC) SMC Write Protection Mode Register */
  #define REG_SMC_WPSR                    (0xFFFFEAE8U) /**< \brief (SMC) SMC Write Protection Status Register */
#else
  #define REG_SMC_SETUP0 (*(__IO uint32_t*)0xFFFFEA00U) /**< \brief (SMC) SMC Setup Register (CS_number = 0) */
  #define REG_SMC_PULSE0 (*(__IO uint32_t*)0xFFFFEA04U) /**< \brief (SMC) SMC Pulse Register (CS_number = 0) */
  #define REG_SMC_CYCLE0 (*(__IO uint32_t*)0xFFFFEA08U) /**< \brief (SMC) SMC Cycle Register (CS_number = 0) */
  #define REG_SMC_MODE0  (*(__IO uint32_t*)0xFFFFEA0CU) /**< \brief (SMC) SMC Mode Register (CS_number = 0) */
  #define REG_SMC_SETUP1 (*(__IO uint32_t*)0xFFFFEA10U) /**< \brief (SMC) SMC Setup Register (CS_number = 1) */
  #define REG_SMC_PULSE1 (*(__IO uint32_t*)0xFFFFEA14U) /**< \brief (SMC) SMC Pulse Register (CS_number = 1) */
  #define REG_SMC_CYCLE1 (*(__IO uint32_t*)0xFFFFEA18U) /**< \brief (SMC) SMC Cycle Register (CS_number = 1) */
  #define REG_SMC_MODE1  (*(__IO uint32_t*)0xFFFFEA1CU) /**< \brief (SMC) SMC Mode Register (CS_number = 1) */
  #define REG_SMC_SETUP2 (*(__IO uint32_t*)0xFFFFEA20U) /**< \brief (SMC) SMC Setup Register (CS_number = 2) */
  #define REG_SMC_PULSE2 (*(__IO uint32_t*)0xFFFFEA24U) /**< \brief (SMC) SMC Pulse Register (CS_number = 2) */
  #define REG_SMC_CYCLE2 (*(__IO uint32_t*)0xFFFFEA28U) /**< \brief (SMC) SMC Cycle Register (CS_number = 2) */
  #define REG_SMC_MODE2  (*(__IO uint32_t*)0xFFFFEA2CU) /**< \brief (SMC) SMC Mode Register (CS_number = 2) */
  #define REG_SMC_SETUP3 (*(__IO uint32_t*)0xFFFFEA30U) /**< \brief (SMC) SMC Setup Register (CS_number = 3) */
  #define REG_SMC_PULSE3 (*(__IO uint32_t*)0xFFFFEA34U) /**< \brief (SMC) SMC Pulse Register (CS_number = 3) */
  #define REG_SMC_CYCLE3 (*(__IO uint32_t*)0xFFFFEA38U) /**< \brief (SMC) SMC Cycle Register (CS_number = 3) */
  #define REG_SMC_MODE3  (*(__IO uint32_t*)0xFFFFEA3CU) /**< \brief (SMC) SMC Mode Register (CS_number = 3) */
  #define REG_SMC_SETUP4 (*(__IO uint32_t*)0xFFFFEA40U) /**< \brief (SMC) SMC Setup Register (CS_number = 4) */
  #define REG_SMC_PULSE4 (*(__IO uint32_t*)0xFFFFEA44U) /**< \brief (SMC) SMC Pulse Register (CS_number = 4) */
  #define REG_SMC_CYCLE4 (*(__IO uint32_t*)0xFFFFEA48U) /**< \brief (SMC) SMC Cycle Register (CS_number = 4) */
  #define REG_SMC_MODE4  (*(__IO uint32_t*)0xFFFFEA4CU) /**< \brief (SMC) SMC Mode Register (CS_number = 4) */
  #define REG_SMC_SETUP5 (*(__IO uint32_t*)0xFFFFEA50U) /**< \brief (SMC) SMC Setup Register (CS_number = 5) */
  #define REG_SMC_PULSE5 (*(__IO uint32_t*)0xFFFFEA54U) /**< \brief (SMC) SMC Pulse Register (CS_number = 5) */
  #define REG_SMC_CYCLE5 (*(__IO uint32_t*)0xFFFFEA58U) /**< \brief (SMC) SMC Cycle Register (CS_number = 5) */
  #define REG_SMC_MODE5  (*(__IO uint32_t*)0xFFFFEA5CU) /**< \brief (SMC) SMC Mode Register (CS_number = 5) */
  #define REG_SMC_OCMS   (*(__IO uint32_t*)0xFFFFEA80U) /**< \brief (SMC) SMC Off-Chip Memory Scrambling Register */
  #define REG_SMC_KEY1   (*(__O  uint32_t*)0xFFFFEA84U) /**< \brief (SMC) SMC Off-Chip Memory Scrambling KEY1 Register */
  #define REG_SMC_KEY2   (*(__O  uint32_t*)0xFFFFEA88U) /**< \brief (SMC) SMC Off-Chip Memory Scrambling KEY2 Register */
  #define REG_SMC_SRIER  (*(__IO uint32_t*)0xFFFFEA90U) /**< \brief (SMC) SMC Safety Report Interrupt Enable Register */
  #define REG_SMC_WPMR   (*(__IO uint32_t*)0xFFFFEAE4U) /**< \brief (SMC) SMC Write Protection Mode Register */
  #define REG_SMC_WPSR   (*(__I  uint32_t*)0xFFFFEAE8U) /**< \brief (SMC) SMC Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_SMC_INSTANCE_ */
