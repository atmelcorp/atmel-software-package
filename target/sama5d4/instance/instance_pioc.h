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

#ifndef _SAMA5D4_PIOC_INSTANCE_
#define _SAMA5D4_PIOC_INSTANCE_

/* ========== Register definition for PIOC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_PIOC_PER                      (0xFC06C000U) /**< \brief (PIOC) PIO Enable Register */
  #define REG_PIOC_PDR                      (0xFC06C004U) /**< \brief (PIOC) PIO Disable Register */
  #define REG_PIOC_PSR                      (0xFC06C008U) /**< \brief (PIOC) PIO Status Register */
  #define REG_PIOC_ISLR                     (0xFC06C00CU) /**< \brief (PIOC) PIO Interrupt Security Level Register */
  #define REG_PIOC_OER                      (0xFC06C010U) /**< \brief (PIOC) Output Enable Register */
  #define REG_PIOC_ODR                      (0xFC06C014U) /**< \brief (PIOC) Output Disable Register */
  #define REG_PIOC_OSR                      (0xFC06C018U) /**< \brief (PIOC) Output Status Register */
  #define REG_PIOC_IFER                     (0xFC06C020U) /**< \brief (PIOC) Glitch Input Filter Enable Register */
  #define REG_PIOC_IFDR                     (0xFC06C024U) /**< \brief (PIOC) Glitch Input Filter Disable Register */
  #define REG_PIOC_IFSR                     (0xFC06C028U) /**< \brief (PIOC) Glitch Input Filter Status Register */
  #define REG_PIOC_SODR                     (0xFC06C030U) /**< \brief (PIOC) Set Output Data Register */
  #define REG_PIOC_CODR                     (0xFC06C034U) /**< \brief (PIOC) Clear Output Data Register */
  #define REG_PIOC_ODSR                     (0xFC06C038U) /**< \brief (PIOC) Output Data Status Register */
  #define REG_PIOC_PDSR                     (0xFC06C03CU) /**< \brief (PIOC) Pin Data Status Register */
  #define REG_PIOC_IER                      (0xFC06C040U) /**< \brief (PIOC) Interrupt Enable Register */
  #define REG_PIOC_IDR                      (0xFC06C044U) /**< \brief (PIOC) Interrupt Disable Register */
  #define REG_PIOC_IMR                      (0xFC06C048U) /**< \brief (PIOC) Interrupt Mask Register */
  #define REG_PIOC_ISR                      (0xFC06C04CU) /**< \brief (PIOC) Interrupt Status Register */
  #define REG_PIOC_MDER                     (0xFC06C050U) /**< \brief (PIOC) Multi-driver Enable Register */
  #define REG_PIOC_MDDR                     (0xFC06C054U) /**< \brief (PIOC) Multi-driver Disable Register */
  #define REG_PIOC_MDSR                     (0xFC06C058U) /**< \brief (PIOC) Multi-driver Status Register */
  #define REG_PIOC_PUDR                     (0xFC06C060U) /**< \brief (PIOC) Pull-up Disable Register */
  #define REG_PIOC_PUER                     (0xFC06C064U) /**< \brief (PIOC) Pull-up Enable Register */
  #define REG_PIOC_PUSR                     (0xFC06C068U) /**< \brief (PIOC) Pad Pull-up Status Register */
  #define REG_PIOC_ABCDSR                   (0xFC06C070U) /**< \brief (PIOC) Peripheral Select Register */
  #define REG_PIOC_IFSCDR                   (0xFC06C080U) /**< \brief (PIOC) Input Filter Slow Clock Disable Register */
  #define REG_PIOC_IFSCER                   (0xFC06C084U) /**< \brief (PIOC) Input Filter Slow Clock Enable Register */
  #define REG_PIOC_IFSCSR                   (0xFC06C088U) /**< \brief (PIOC) Input Filter Slow Clock Status Register */
  #define REG_PIOC_SCDR                     (0xFC06C08CU) /**< \brief (PIOC) Slow Clock Divider Debouncing Register */
  #define REG_PIOC_PPDDR                    (0xFC06C090U) /**< \brief (PIOC) Pad Pull-down Disable Register */
  #define REG_PIOC_PPDER                    (0xFC06C094U) /**< \brief (PIOC) Pad Pull-down Enable Register */
  #define REG_PIOC_PPDSR                    (0xFC06C098U) /**< \brief (PIOC) Pad Pull-down Status Register */
  #define REG_PIOC_OWER                     (0xFC06C0A0U) /**< \brief (PIOC) Output Write Enable */
  #define REG_PIOC_OWDR                     (0xFC06C0A4U) /**< \brief (PIOC) Output Write Disable */
  #define REG_PIOC_OWSR                     (0xFC06C0A8U) /**< \brief (PIOC) Output Write Status Register */
  #define REG_PIOC_AIMER                    (0xFC06C0B0U) /**< \brief (PIOC) Additional Interrupt Modes Enable Register */
  #define REG_PIOC_AIMDR                    (0xFC06C0B4U) /**< \brief (PIOC) Additional Interrupt Modes Disable Register */
  #define REG_PIOC_AIMMR                    (0xFC06C0B8U) /**< \brief (PIOC) Additional Interrupt Modes Mask Register */
  #define REG_PIOC_ESR                      (0xFC06C0C0U) /**< \brief (PIOC) Edge Select Register */
  #define REG_PIOC_LSR                      (0xFC06C0C4U) /**< \brief (PIOC) Level Select Register */
  #define REG_PIOC_ELSR                     (0xFC06C0C8U) /**< \brief (PIOC) Edge/Level Status Register */
  #define REG_PIOC_FELLSR                   (0xFC06C0D0U) /**< \brief (PIOC) Falling Edge/Low-Level Select Register */
  #define REG_PIOC_REHLSR                   (0xFC06C0D4U) /**< \brief (PIOC) Rising Edge/High-Level Select Register */
  #define REG_PIOC_FRLHSR                   (0xFC06C0D8U) /**< \brief (PIOC) Fall/Rise - Low/High Status Register */
  #define REG_PIOC_WPMR                     (0xFC06C0E4U) /**< \brief (PIOC) Write Protection Mode Register */
  #define REG_PIOC_WPSR                     (0xFC06C0E8U) /**< \brief (PIOC) Write Protection Status Register */
  #define REG_PIOC_SCHMITT                  (0xFC06C100U) /**< \brief (PIOC) Schmitt Trigger Register */
  #define REG_PIOC_DRIVER1                  (0xFC06C118U) /**< \brief (PIOC) I/O Drive Register 1 */
  #define REG_PIOC_DRIVER2                  (0xFC06C11CU) /**< \brief (PIOC) I/O Drive Register 2 */
#else
  #define REG_PIOC_PER     (*(__O  uint32_t*)0xFC06C000U) /**< \brief (PIOC) PIO Enable Register */
  #define REG_PIOC_PDR     (*(__O  uint32_t*)0xFC06C004U) /**< \brief (PIOC) PIO Disable Register */
  #define REG_PIOC_PSR     (*(__I  uint32_t*)0xFC06C008U) /**< \brief (PIOC) PIO Status Register */
  #define REG_PIOC_ISLR    (*(__IO uint32_t*)0xFC06C00CU) /**< \brief (PIOC) PIO Interrupt Security Level Register */
  #define REG_PIOC_OER     (*(__O  uint32_t*)0xFC06C010U) /**< \brief (PIOC) Output Enable Register */
  #define REG_PIOC_ODR     (*(__O  uint32_t*)0xFC06C014U) /**< \brief (PIOC) Output Disable Register */
  #define REG_PIOC_OSR     (*(__I  uint32_t*)0xFC06C018U) /**< \brief (PIOC) Output Status Register */
  #define REG_PIOC_IFER    (*(__O  uint32_t*)0xFC06C020U) /**< \brief (PIOC) Glitch Input Filter Enable Register */
  #define REG_PIOC_IFDR    (*(__O  uint32_t*)0xFC06C024U) /**< \brief (PIOC) Glitch Input Filter Disable Register */
  #define REG_PIOC_IFSR    (*(__I  uint32_t*)0xFC06C028U) /**< \brief (PIOC) Glitch Input Filter Status Register */
  #define REG_PIOC_SODR    (*(__O  uint32_t*)0xFC06C030U) /**< \brief (PIOC) Set Output Data Register */
  #define REG_PIOC_CODR    (*(__O  uint32_t*)0xFC06C034U) /**< \brief (PIOC) Clear Output Data Register */
  #define REG_PIOC_ODSR    (*(__IO uint32_t*)0xFC06C038U) /**< \brief (PIOC) Output Data Status Register */
  #define REG_PIOC_PDSR    (*(__I  uint32_t*)0xFC06C03CU) /**< \brief (PIOC) Pin Data Status Register */
  #define REG_PIOC_IER     (*(__O  uint32_t*)0xFC06C040U) /**< \brief (PIOC) Interrupt Enable Register */
  #define REG_PIOC_IDR     (*(__O  uint32_t*)0xFC06C044U) /**< \brief (PIOC) Interrupt Disable Register */
  #define REG_PIOC_IMR     (*(__I  uint32_t*)0xFC06C048U) /**< \brief (PIOC) Interrupt Mask Register */
  #define REG_PIOC_ISR     (*(__I  uint32_t*)0xFC06C04CU) /**< \brief (PIOC) Interrupt Status Register */
  #define REG_PIOC_MDER    (*(__O  uint32_t*)0xFC06C050U) /**< \brief (PIOC) Multi-driver Enable Register */
  #define REG_PIOC_MDDR    (*(__O  uint32_t*)0xFC06C054U) /**< \brief (PIOC) Multi-driver Disable Register */
  #define REG_PIOC_MDSR    (*(__I  uint32_t*)0xFC06C058U) /**< \brief (PIOC) Multi-driver Status Register */
  #define REG_PIOC_PUDR    (*(__O  uint32_t*)0xFC06C060U) /**< \brief (PIOC) Pull-up Disable Register */
  #define REG_PIOC_PUER    (*(__O  uint32_t*)0xFC06C064U) /**< \brief (PIOC) Pull-up Enable Register */
  #define REG_PIOC_PUSR    (*(__I  uint32_t*)0xFC06C068U) /**< \brief (PIOC) Pad Pull-up Status Register */
  #define REG_PIOC_ABCDSR  (*(__IO uint32_t*)0xFC06C070U) /**< \brief (PIOC) Peripheral Select Register */
  #define REG_PIOC_IFSCDR  (*(__O  uint32_t*)0xFC06C080U) /**< \brief (PIOC) Input Filter Slow Clock Disable Register */
  #define REG_PIOC_IFSCER  (*(__O  uint32_t*)0xFC06C084U) /**< \brief (PIOC) Input Filter Slow Clock Enable Register */
  #define REG_PIOC_IFSCSR  (*(__I  uint32_t*)0xFC06C088U) /**< \brief (PIOC) Input Filter Slow Clock Status Register */
  #define REG_PIOC_SCDR    (*(__IO uint32_t*)0xFC06C08CU) /**< \brief (PIOC) Slow Clock Divider Debouncing Register */
  #define REG_PIOC_PPDDR   (*(__O  uint32_t*)0xFC06C090U) /**< \brief (PIOC) Pad Pull-down Disable Register */
  #define REG_PIOC_PPDER   (*(__O  uint32_t*)0xFC06C094U) /**< \brief (PIOC) Pad Pull-down Enable Register */
  #define REG_PIOC_PPDSR   (*(__I  uint32_t*)0xFC06C098U) /**< \brief (PIOC) Pad Pull-down Status Register */
  #define REG_PIOC_OWER    (*(__O  uint32_t*)0xFC06C0A0U) /**< \brief (PIOC) Output Write Enable */
  #define REG_PIOC_OWDR    (*(__O  uint32_t*)0xFC06C0A4U) /**< \brief (PIOC) Output Write Disable */
  #define REG_PIOC_OWSR    (*(__I  uint32_t*)0xFC06C0A8U) /**< \brief (PIOC) Output Write Status Register */
  #define REG_PIOC_AIMER   (*(__O  uint32_t*)0xFC06C0B0U) /**< \brief (PIOC) Additional Interrupt Modes Enable Register */
  #define REG_PIOC_AIMDR   (*(__O  uint32_t*)0xFC06C0B4U) /**< \brief (PIOC) Additional Interrupt Modes Disable Register */
  #define REG_PIOC_AIMMR   (*(__I  uint32_t*)0xFC06C0B8U) /**< \brief (PIOC) Additional Interrupt Modes Mask Register */
  #define REG_PIOC_ESR     (*(__O  uint32_t*)0xFC06C0C0U) /**< \brief (PIOC) Edge Select Register */
  #define REG_PIOC_LSR     (*(__O  uint32_t*)0xFC06C0C4U) /**< \brief (PIOC) Level Select Register */
  #define REG_PIOC_ELSR    (*(__I  uint32_t*)0xFC06C0C8U) /**< \brief (PIOC) Edge/Level Status Register */
  #define REG_PIOC_FELLSR  (*(__O  uint32_t*)0xFC06C0D0U) /**< \brief (PIOC) Falling Edge/Low-Level Select Register */
  #define REG_PIOC_REHLSR  (*(__O  uint32_t*)0xFC06C0D4U) /**< \brief (PIOC) Rising Edge/High-Level Select Register */
  #define REG_PIOC_FRLHSR  (*(__I  uint32_t*)0xFC06C0D8U) /**< \brief (PIOC) Fall/Rise - Low/High Status Register */
  #define REG_PIOC_WPMR    (*(__IO uint32_t*)0xFC06C0E4U) /**< \brief (PIOC) Write Protection Mode Register */
  #define REG_PIOC_WPSR    (*(__I  uint32_t*)0xFC06C0E8U) /**< \brief (PIOC) Write Protection Status Register */
  #define REG_PIOC_SCHMITT (*(__IO uint32_t*)0xFC06C100U) /**< \brief (PIOC) Schmitt Trigger Register */
  #define REG_PIOC_DRIVER1 (*(__IO uint32_t*)0xFC06C118U) /**< \brief (PIOC) I/O Drive Register 1 */
  #define REG_PIOC_DRIVER2 (*(__IO uint32_t*)0xFC06C11CU) /**< \brief (PIOC) I/O Drive Register 2 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D4_PIOC_INSTANCE_ */
