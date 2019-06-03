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

#ifndef _SAM9X_PIOD_INSTANCE_
#define _SAM9X_PIOD_INSTANCE_

/* ========== Register definition for PIOD peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_PIOD_PER                      (0xFFFFFA00U) /**< \brief (PIOD) PIO Enable Register */
  #define REG_PIOD_PDR                      (0xFFFFFA04U) /**< \brief (PIOD) PIO Disable Register */
  #define REG_PIOD_PSR                      (0xFFFFFA08U) /**< \brief (PIOD) PIO Status Register */
  #define REG_PIOD_OER                      (0xFFFFFA10U) /**< \brief (PIOD) Output Enable Register */
  #define REG_PIOD_ODR                      (0xFFFFFA14U) /**< \brief (PIOD) Output Disable Register */
  #define REG_PIOD_OSR                      (0xFFFFFA18U) /**< \brief (PIOD) Output Status Register */
  #define REG_PIOD_IFER                     (0xFFFFFA20U) /**< \brief (PIOD) Glitch Input Filter Enable Register */
  #define REG_PIOD_IFDR                     (0xFFFFFA24U) /**< \brief (PIOD) Glitch Input Filter Disable Register */
  #define REG_PIOD_IFSR                     (0xFFFFFA28U) /**< \brief (PIOD) Glitch Input Filter Status Register */
  #define REG_PIOD_SODR                     (0xFFFFFA30U) /**< \brief (PIOD) Set Output Data Register */
  #define REG_PIOD_CODR                     (0xFFFFFA34U) /**< \brief (PIOD) Clear Output Data Register */
  #define REG_PIOD_ODSR                     (0xFFFFFA38U) /**< \brief (PIOD) Output Data Status Register */
  #define REG_PIOD_PDSR                     (0xFFFFFA3CU) /**< \brief (PIOD) Pin Data Status Register */
  #define REG_PIOD_IER                      (0xFFFFFA40U) /**< \brief (PIOD) Interrupt Enable Register */
  #define REG_PIOD_IDR                      (0xFFFFFA44U) /**< \brief (PIOD) Interrupt Disable Register */
  #define REG_PIOD_IMR                      (0xFFFFFA48U) /**< \brief (PIOD) Interrupt Mask Register */
  #define REG_PIOD_ISR                      (0xFFFFFA4CU) /**< \brief (PIOD) Interrupt Status Register */
  #define REG_PIOD_MDER                     (0xFFFFFA50U) /**< \brief (PIOD) Multi-driver Enable Register */
  #define REG_PIOD_MDDR                     (0xFFFFFA54U) /**< \brief (PIOD) Multi-driver Disable Register */
  #define REG_PIOD_MDSR                     (0xFFFFFA58U) /**< \brief (PIOD) Multi-driver Status Register */
  #define REG_PIOD_PUDR                     (0xFFFFFA60U) /**< \brief (PIOD) Pull-Up Disable Register */
  #define REG_PIOD_PUER                     (0xFFFFFA64U) /**< \brief (PIOD) Pull-Up Enable Register */
  #define REG_PIOD_PUSR                     (0xFFFFFA68U) /**< \brief (PIOD) Pad Pull-Up Status Register */
  #define REG_PIOD_ABCDSR                   (0xFFFFFA70U) /**< \brief (PIOD) Peripheral ABCD Select Register */
  #define REG_PIOD_IFSCDR                   (0xFFFFFA80U) /**< \brief (PIOD) Input Filter Slow Clock Disable Register */
  #define REG_PIOD_IFSCER                   (0xFFFFFA84U) /**< \brief (PIOD) Input Filter Slow Clock Enable Register */
  #define REG_PIOD_IFSCSR                   (0xFFFFFA88U) /**< \brief (PIOD) Input Filter Slow Clock Status Register */
  #define REG_PIOD_SCDR                     (0xFFFFFA8CU) /**< \brief (PIOD) Slow Clock Divider Debouncing Register */
  #define REG_PIOD_PPDDR                    (0xFFFFFA90U) /**< \brief (PIOD) Pad Pull-Down Disable Register */
  #define REG_PIOD_PPDER                    (0xFFFFFA94U) /**< \brief (PIOD) Pad Pull-Down Enable Register */
  #define REG_PIOD_PPDSR                    (0xFFFFFA98U) /**< \brief (PIOD) Pad Pull-Down Status Register */
  #define REG_PIOD_OWER                     (0xFFFFFAA0U) /**< \brief (PIOD) Output Write Enable */
  #define REG_PIOD_OWDR                     (0xFFFFFAA4U) /**< \brief (PIOD) Output Write Disable */
  #define REG_PIOD_OWSR                     (0xFFFFFAA8U) /**< \brief (PIOD) Output Write Status Register */
  #define REG_PIOD_AIMER                    (0xFFFFFAB0U) /**< \brief (PIOD) Additional Interrupt Modes Enable Register */
  #define REG_PIOD_AIMDR                    (0xFFFFFAB4U) /**< \brief (PIOD) Additional Interrupt Modes Disable Register */
  #define REG_PIOD_AIMMR                    (0xFFFFFAB8U) /**< \brief (PIOD) Additional Interrupt Modes Mask Register */
  #define REG_PIOD_ESR                      (0xFFFFFAC0U) /**< \brief (PIOD) Edge Select Register */
  #define REG_PIOD_LSR                      (0xFFFFFAC4U) /**< \brief (PIOD) Level Select Register */
  #define REG_PIOD_ELSR                     (0xFFFFFAC8U) /**< \brief (PIOD) Edge/Level Status Register */
  #define REG_PIOD_FELLSR                   (0xFFFFFAD0U) /**< \brief (PIOD) Falling Edge/Low-Level Select Register */
  #define REG_PIOD_REHLSR                   (0xFFFFFAD4U) /**< \brief (PIOD) Rising Edge/High-Level Select Register */
  #define REG_PIOD_FRLHSR                   (0xFFFFFAD8U) /**< \brief (PIOD) Fall/Rise - Low/High Status Register */
  #define REG_PIOD_WPMR                     (0xFFFFFAE4U) /**< \brief (PIOD) Write Protection Mode Register */
  #define REG_PIOD_WPSR                     (0xFFFFFAE8U) /**< \brief (PIOD) Write Protection Status Register */
  #define REG_PIOD_SCHMITT                  (0xFFFFFB00U) /**< \brief (PIOD) Schmitt Trigger Register */
  #define REG_PIOD_SLEWR                    (0xFFFFFB10U) /**< \brief (PIOD) I/O Slewrate Control Register */
  #define REG_PIOD_DRIVER                   (0xFFFFFB18U) /**< \brief (PIOD) I/O Drive Register */
#else
  #define REG_PIOD_PER     (*(__O  uint32_t*)0xFFFFFA00U) /**< \brief (PIOD) PIO Enable Register */
  #define REG_PIOD_PDR     (*(__O  uint32_t*)0xFFFFFA04U) /**< \brief (PIOD) PIO Disable Register */
  #define REG_PIOD_PSR     (*(__I  uint32_t*)0xFFFFFA08U) /**< \brief (PIOD) PIO Status Register */
  #define REG_PIOD_OER     (*(__O  uint32_t*)0xFFFFFA10U) /**< \brief (PIOD) Output Enable Register */
  #define REG_PIOD_ODR     (*(__O  uint32_t*)0xFFFFFA14U) /**< \brief (PIOD) Output Disable Register */
  #define REG_PIOD_OSR     (*(__I  uint32_t*)0xFFFFFA18U) /**< \brief (PIOD) Output Status Register */
  #define REG_PIOD_IFER    (*(__O  uint32_t*)0xFFFFFA20U) /**< \brief (PIOD) Glitch Input Filter Enable Register */
  #define REG_PIOD_IFDR    (*(__O  uint32_t*)0xFFFFFA24U) /**< \brief (PIOD) Glitch Input Filter Disable Register */
  #define REG_PIOD_IFSR    (*(__I  uint32_t*)0xFFFFFA28U) /**< \brief (PIOD) Glitch Input Filter Status Register */
  #define REG_PIOD_SODR    (*(__O  uint32_t*)0xFFFFFA30U) /**< \brief (PIOD) Set Output Data Register */
  #define REG_PIOD_CODR    (*(__O  uint32_t*)0xFFFFFA34U) /**< \brief (PIOD) Clear Output Data Register */
  #define REG_PIOD_ODSR    (*(__IO uint32_t*)0xFFFFFA38U) /**< \brief (PIOD) Output Data Status Register */
  #define REG_PIOD_PDSR    (*(__I  uint32_t*)0xFFFFFA3CU) /**< \brief (PIOD) Pin Data Status Register */
  #define REG_PIOD_IER     (*(__O  uint32_t*)0xFFFFFA40U) /**< \brief (PIOD) Interrupt Enable Register */
  #define REG_PIOD_IDR     (*(__O  uint32_t*)0xFFFFFA44U) /**< \brief (PIOD) Interrupt Disable Register */
  #define REG_PIOD_IMR     (*(__I  uint32_t*)0xFFFFFA48U) /**< \brief (PIOD) Interrupt Mask Register */
  #define REG_PIOD_ISR     (*(__I  uint32_t*)0xFFFFFA4CU) /**< \brief (PIOD) Interrupt Status Register */
  #define REG_PIOD_MDER    (*(__O  uint32_t*)0xFFFFFA50U) /**< \brief (PIOD) Multi-driver Enable Register */
  #define REG_PIOD_MDDR    (*(__O  uint32_t*)0xFFFFFA54U) /**< \brief (PIOD) Multi-driver Disable Register */
  #define REG_PIOD_MDSR    (*(__I  uint32_t*)0xFFFFFA58U) /**< \brief (PIOD) Multi-driver Status Register */
  #define REG_PIOD_PUDR    (*(__O  uint32_t*)0xFFFFFA60U) /**< \brief (PIOD) Pull-Up Disable Register */
  #define REG_PIOD_PUER    (*(__O  uint32_t*)0xFFFFFA64U) /**< \brief (PIOD) Pull-Up Enable Register */
  #define REG_PIOD_PUSR    (*(__I  uint32_t*)0xFFFFFA68U) /**< \brief (PIOD) Pad Pull-Up Status Register */
  #define REG_PIOD_ABCDSR  (*(__IO uint32_t*)0xFFFFFA70U) /**< \brief (PIOD) Peripheral ABCD Select Register */
  #define REG_PIOD_IFSCDR  (*(__O  uint32_t*)0xFFFFFA80U) /**< \brief (PIOD) Input Filter Slow Clock Disable Register */
  #define REG_PIOD_IFSCER  (*(__O  uint32_t*)0xFFFFFA84U) /**< \brief (PIOD) Input Filter Slow Clock Enable Register */
  #define REG_PIOD_IFSCSR  (*(__I  uint32_t*)0xFFFFFA88U) /**< \brief (PIOD) Input Filter Slow Clock Status Register */
  #define REG_PIOD_SCDR    (*(__IO uint32_t*)0xFFFFFA8CU) /**< \brief (PIOD) Slow Clock Divider Debouncing Register */
  #define REG_PIOD_PPDDR   (*(__O  uint32_t*)0xFFFFFA90U) /**< \brief (PIOD) Pad Pull-Down Disable Register */
  #define REG_PIOD_PPDER   (*(__O  uint32_t*)0xFFFFFA94U) /**< \brief (PIOD) Pad Pull-Down Enable Register */
  #define REG_PIOD_PPDSR   (*(__I  uint32_t*)0xFFFFFA98U) /**< \brief (PIOD) Pad Pull-Down Status Register */
  #define REG_PIOD_OWER    (*(__O  uint32_t*)0xFFFFFAA0U) /**< \brief (PIOD) Output Write Enable */
  #define REG_PIOD_OWDR    (*(__O  uint32_t*)0xFFFFFAA4U) /**< \brief (PIOD) Output Write Disable */
  #define REG_PIOD_OWSR    (*(__I  uint32_t*)0xFFFFFAA8U) /**< \brief (PIOD) Output Write Status Register */
  #define REG_PIOD_AIMER   (*(__O  uint32_t*)0xFFFFFAB0U) /**< \brief (PIOD) Additional Interrupt Modes Enable Register */
  #define REG_PIOD_AIMDR   (*(__O  uint32_t*)0xFFFFFAB4U) /**< \brief (PIOD) Additional Interrupt Modes Disable Register */
  #define REG_PIOD_AIMMR   (*(__I  uint32_t*)0xFFFFFAB8U) /**< \brief (PIOD) Additional Interrupt Modes Mask Register */
  #define REG_PIOD_ESR     (*(__O  uint32_t*)0xFFFFFAC0U) /**< \brief (PIOD) Edge Select Register */
  #define REG_PIOD_LSR     (*(__O  uint32_t*)0xFFFFFAC4U) /**< \brief (PIOD) Level Select Register */
  #define REG_PIOD_ELSR    (*(__I  uint32_t*)0xFFFFFAC8U) /**< \brief (PIOD) Edge/Level Status Register */
  #define REG_PIOD_FELLSR  (*(__O  uint32_t*)0xFFFFFAD0U) /**< \brief (PIOD) Falling Edge/Low-Level Select Register */
  #define REG_PIOD_REHLSR  (*(__O  uint32_t*)0xFFFFFAD4U) /**< \brief (PIOD) Rising Edge/High-Level Select Register */
  #define REG_PIOD_FRLHSR  (*(__I  uint32_t*)0xFFFFFAD8U) /**< \brief (PIOD) Fall/Rise - Low/High Status Register */
  #define REG_PIOD_WPMR    (*(__IO uint32_t*)0xFFFFFAE4U) /**< \brief (PIOD) Write Protection Mode Register */
  #define REG_PIOD_WPSR    (*(__I  uint32_t*)0xFFFFFAE8U) /**< \brief (PIOD) Write Protection Status Register */
  #define REG_PIOD_SCHMITT (*(__IO uint32_t*)0xFFFFFB00U) /**< \brief (PIOD) Schmitt Trigger Register */
  #define REG_PIOD_SLEWR   (*(__IO uint32_t*)0xFFFFFB10U) /**< \brief (PIOD) I/O Slewrate Control Register */
  #define REG_PIOD_DRIVER  (*(__IO uint32_t*)0xFFFFFB18U) /**< \brief (PIOD) I/O Drive Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_PIOD_INSTANCE_ */
