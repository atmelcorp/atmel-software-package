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

#ifndef _SAM9X_MATRIX_INSTANCE_
#define _SAM9X_MATRIX_INSTANCE_

/* ========== Register definition for MATRIX peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_MATRIX_MCFG                    (0xFFFFDE00U) /**< \brief (MATRIX) Master Configuration Register */
  #define REG_MATRIX_SCFG                    (0xFFFFDE40U) /**< \brief (MATRIX) Slave Configuration Register */
  #define REG_MATRIX_PRAS0                   (0xFFFFDE80U) /**< \brief (MATRIX) Priority Register A for Slave 0 */
  #define REG_MATRIX_PRBS0                   (0xFFFFDE84U) /**< \brief (MATRIX) Priority Register B for Slave 0 */
  #define REG_MATRIX_PRAS1                   (0xFFFFDE88U) /**< \brief (MATRIX) Priority Register A for Slave 1 */
  #define REG_MATRIX_PRBS1                   (0xFFFFDE8CU) /**< \brief (MATRIX) Priority Register B for Slave 1 */
  #define REG_MATRIX_PRAS2                   (0xFFFFDE90U) /**< \brief (MATRIX) Priority Register A for Slave 2 */
  #define REG_MATRIX_PRBS2                   (0xFFFFDE94U) /**< \brief (MATRIX) Priority Register B for Slave 2 */
  #define REG_MATRIX_PRAS3                   (0xFFFFDE98U) /**< \brief (MATRIX) Priority Register A for Slave 3 */
  #define REG_MATRIX_PRBS3                   (0xFFFFDE9CU) /**< \brief (MATRIX) Priority Register B for Slave 3 */
  #define REG_MATRIX_PRAS4                   (0xFFFFDEA0U) /**< \brief (MATRIX) Priority Register A for Slave 4 */
  #define REG_MATRIX_PRBS4                   (0xFFFFDEA4U) /**< \brief (MATRIX) Priority Register B for Slave 4 */
  #define REG_MATRIX_PRAS5                   (0xFFFFDEA8U) /**< \brief (MATRIX) Priority Register A for Slave 5 */
  #define REG_MATRIX_PRBS5                   (0xFFFFDEACU) /**< \brief (MATRIX) Priority Register B for Slave 5 */
  #define REG_MATRIX_PRAS6                   (0xFFFFDEB0U) /**< \brief (MATRIX) Priority Register A for Slave 6 */
  #define REG_MATRIX_PRBS6                   (0xFFFFDEB4U) /**< \brief (MATRIX) Priority Register B for Slave 6 */
  #define REG_MATRIX_PRAS7                   (0xFFFFDEB8U) /**< \brief (MATRIX) Priority Register A for Slave 7 */
  #define REG_MATRIX_PRBS7                   (0xFFFFDEBCU) /**< \brief (MATRIX) Priority Register B for Slave 7 */
  #define REG_MATRIX_PRAS8                   (0xFFFFDEC0U) /**< \brief (MATRIX) Priority Register A for Slave 8 */
  #define REG_MATRIX_PRBS8                   (0xFFFFDEC4U) /**< \brief (MATRIX) Priority Register B for Slave 8 */
  #define REG_MATRIX_PRAS9                   (0xFFFFDEC8U) /**< \brief (MATRIX) Priority Register A for Slave 9 */
  #define REG_MATRIX_PRBS9                   (0xFFFFDECCU) /**< \brief (MATRIX) Priority Register B for Slave 9 */
  #define REG_MATRIX_PRAS10                  (0xFFFFDED0U) /**< \brief (MATRIX) Priority Register A for Slave 10 */
  #define REG_MATRIX_PRBS10                  (0xFFFFDED4U) /**< \brief (MATRIX) Priority Register B for Slave 10 */
  #define REG_MATRIX_PRAS11                  (0xFFFFDED8U) /**< \brief (MATRIX) Priority Register A for Slave 11 */
  #define REG_MATRIX_PRBS11                  (0xFFFFDEDCU) /**< \brief (MATRIX) Priority Register B for Slave 11 */
  #define REG_MATRIX_PRAS12                  (0xFFFFDEE0U) /**< \brief (MATRIX) Priority Register A for Slave 12 */
  #define REG_MATRIX_PRBS12                  (0xFFFFDEE4U) /**< \brief (MATRIX) Priority Register B for Slave 12 */
  #define REG_MATRIX_MRCR                    (0xFFFFDF00U) /**< \brief (MATRIX) Master Remap Control Register */
  #define REG_MATRIX_MEIER                   (0xFFFFDF50U) /**< \brief (MATRIX) Master Error Interrupt Enable Register */
  #define REG_MATRIX_MEIDR                   (0xFFFFDF54U) /**< \brief (MATRIX) Master Error Interrupt Disable Register */
  #define REG_MATRIX_MEIMR                   (0xFFFFDF58U) /**< \brief (MATRIX) Master Error Interrupt Mask Register */
  #define REG_MATRIX_MESR                    (0xFFFFDF5CU) /**< \brief (MATRIX) Master Error Status Register */
  #define REG_MATRIX_MEAR                    (0xFFFFDF60U) /**< \brief (MATRIX) Master 0 Error Address Register */
  #define REG_MATRIX_WPMR                    (0xFFFFDFE4U) /**< \brief (MATRIX) Write Protect Mode Register */
  #define REG_MATRIX_WPSR                    (0xFFFFDFE8U) /**< \brief (MATRIX) Write Protect Status Register */
#else
  #define REG_MATRIX_MCFG   (*(__IO uint32_t*)0xFFFFDE00U) /**< \brief (MATRIX) Master Configuration Register */
  #define REG_MATRIX_SCFG   (*(__IO uint32_t*)0xFFFFDE40U) /**< \brief (MATRIX) Slave Configuration Register */
  #define REG_MATRIX_PRAS0  (*(__IO uint32_t*)0xFFFFDE80U) /**< \brief (MATRIX) Priority Register A for Slave 0 */
  #define REG_MATRIX_PRBS0  (*(__IO uint32_t*)0xFFFFDE84U) /**< \brief (MATRIX) Priority Register B for Slave 0 */
  #define REG_MATRIX_PRAS1  (*(__IO uint32_t*)0xFFFFDE88U) /**< \brief (MATRIX) Priority Register A for Slave 1 */
  #define REG_MATRIX_PRBS1  (*(__IO uint32_t*)0xFFFFDE8CU) /**< \brief (MATRIX) Priority Register B for Slave 1 */
  #define REG_MATRIX_PRAS2  (*(__IO uint32_t*)0xFFFFDE90U) /**< \brief (MATRIX) Priority Register A for Slave 2 */
  #define REG_MATRIX_PRBS2  (*(__IO uint32_t*)0xFFFFDE94U) /**< \brief (MATRIX) Priority Register B for Slave 2 */
  #define REG_MATRIX_PRAS3  (*(__IO uint32_t*)0xFFFFDE98U) /**< \brief (MATRIX) Priority Register A for Slave 3 */
  #define REG_MATRIX_PRBS3  (*(__IO uint32_t*)0xFFFFDE9CU) /**< \brief (MATRIX) Priority Register B for Slave 3 */
  #define REG_MATRIX_PRAS4  (*(__IO uint32_t*)0xFFFFDEA0U) /**< \brief (MATRIX) Priority Register A for Slave 4 */
  #define REG_MATRIX_PRBS4  (*(__IO uint32_t*)0xFFFFDEA4U) /**< \brief (MATRIX) Priority Register B for Slave 4 */
  #define REG_MATRIX_PRAS5  (*(__IO uint32_t*)0xFFFFDEA8U) /**< \brief (MATRIX) Priority Register A for Slave 5 */
  #define REG_MATRIX_PRBS5  (*(__IO uint32_t*)0xFFFFDEACU) /**< \brief (MATRIX) Priority Register B for Slave 5 */
  #define REG_MATRIX_PRAS6  (*(__IO uint32_t*)0xFFFFDEB0U) /**< \brief (MATRIX) Priority Register A for Slave 6 */
  #define REG_MATRIX_PRBS6  (*(__IO uint32_t*)0xFFFFDEB4U) /**< \brief (MATRIX) Priority Register B for Slave 6 */
  #define REG_MATRIX_PRAS7  (*(__IO uint32_t*)0xFFFFDEB8U) /**< \brief (MATRIX) Priority Register A for Slave 7 */
  #define REG_MATRIX_PRBS7  (*(__IO uint32_t*)0xFFFFDEBCU) /**< \brief (MATRIX) Priority Register B for Slave 7 */
  #define REG_MATRIX_PRAS8  (*(__IO uint32_t*)0xFFFFDEC0U) /**< \brief (MATRIX) Priority Register A for Slave 8 */
  #define REG_MATRIX_PRBS8  (*(__IO uint32_t*)0xFFFFDEC4U) /**< \brief (MATRIX) Priority Register B for Slave 8 */
  #define REG_MATRIX_PRAS9  (*(__IO uint32_t*)0xFFFFDEC8U) /**< \brief (MATRIX) Priority Register A for Slave 9 */
  #define REG_MATRIX_PRBS9  (*(__IO uint32_t*)0xFFFFDECCU) /**< \brief (MATRIX) Priority Register B for Slave 9 */
  #define REG_MATRIX_PRAS10 (*(__IO uint32_t*)0xFFFFDED0U) /**< \brief (MATRIX) Priority Register A for Slave 10 */
  #define REG_MATRIX_PRBS10 (*(__IO uint32_t*)0xFFFFDED4U) /**< \brief (MATRIX) Priority Register B for Slave 10 */
  #define REG_MATRIX_PRAS11 (*(__IO uint32_t*)0xFFFFDED8U) /**< \brief (MATRIX) Priority Register A for Slave 11 */
  #define REG_MATRIX_PRBS11 (*(__IO uint32_t*)0xFFFFDEDCU) /**< \brief (MATRIX) Priority Register B for Slave 11 */
  #define REG_MATRIX_PRAS12 (*(__IO uint32_t*)0xFFFFDEE0U) /**< \brief (MATRIX) Priority Register A for Slave 12 */
  #define REG_MATRIX_PRBS12 (*(__IO uint32_t*)0xFFFFDEE4U) /**< \brief (MATRIX) Priority Register B for Slave 12 */
  #define REG_MATRIX_MRCR   (*(__IO uint32_t*)0xFFFFDF00U) /**< \brief (MATRIX) Master Remap Control Register */
  #define REG_MATRIX_MEIER  (*(__O  uint32_t*)0xFFFFDF50U) /**< \brief (MATRIX) Master Error Interrupt Enable Register */
  #define REG_MATRIX_MEIDR  (*(__O  uint32_t*)0xFFFFDF54U) /**< \brief (MATRIX) Master Error Interrupt Disable Register */
  #define REG_MATRIX_MEIMR  (*(__I  uint32_t*)0xFFFFDF58U) /**< \brief (MATRIX) Master Error Interrupt Mask Register */
  #define REG_MATRIX_MESR   (*(__I  uint32_t*)0xFFFFDF5CU) /**< \brief (MATRIX) Master Error Status Register */
  #define REG_MATRIX_MEAR   (*(__I  uint32_t*)0xFFFFDF60U) /**< \brief (MATRIX) Master 0 Error Address Register */
  #define REG_MATRIX_WPMR   (*(__IO uint32_t*)0xFFFFDFE4U) /**< \brief (MATRIX) Write Protect Mode Register */
  #define REG_MATRIX_WPSR   (*(__I  uint32_t*)0xFFFFDFE8U) /**< \brief (MATRIX) Write Protect Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_MATRIX_INSTANCE_ */
