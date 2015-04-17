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

#ifndef _SAMA5D4_PIOD_INSTANCE_
#define _SAMA5D4_PIOD_INSTANCE_

/* ========== Register definition for PIOD peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_PIOD_PER                      (0xFC068000U) /**< \brief (PIOD) PIO Enable Register */
  #define REG_PIOD_PDR                      (0xFC068004U) /**< \brief (PIOD) PIO Disable Register */
  #define REG_PIOD_PSR                      (0xFC068008U) /**< \brief (PIOD) PIO Status Register */
  #define REG_PIOD_ISLR                     (0xFC06800CU) /**< \brief (PIOD) PIO Interrupt Security Level Register */
  #define REG_PIOD_OER                      (0xFC068010U) /**< \brief (PIOD) Output Enable Register */
  #define REG_PIOD_ODR                      (0xFC068014U) /**< \brief (PIOD) Output Disable Register */
  #define REG_PIOD_OSR                      (0xFC068018U) /**< \brief (PIOD) Output Status Register */
  #define REG_PIOD_IFER                     (0xFC068020U) /**< \brief (PIOD) Glitch Input Filter Enable Register */
  #define REG_PIOD_IFDR                     (0xFC068024U) /**< \brief (PIOD) Glitch Input Filter Disable Register */
  #define REG_PIOD_IFSR                     (0xFC068028U) /**< \brief (PIOD) Glitch Input Filter Status Register */
  #define REG_PIOD_SODR                     (0xFC068030U) /**< \brief (PIOD) Set Output Data Register */
  #define REG_PIOD_CODR                     (0xFC068034U) /**< \brief (PIOD) Clear Output Data Register */
  #define REG_PIOD_ODSR                     (0xFC068038U) /**< \brief (PIOD) Output Data Status Register */
  #define REG_PIOD_PDSR                     (0xFC06803CU) /**< \brief (PIOD) Pin Data Status Register */
  #define REG_PIOD_IER                      (0xFC068040U) /**< \brief (PIOD) Interrupt Enable Register */
  #define REG_PIOD_IDR                      (0xFC068044U) /**< \brief (PIOD) Interrupt Disable Register */
  #define REG_PIOD_IMR                      (0xFC068048U) /**< \brief (PIOD) Interrupt Mask Register */
  #define REG_PIOD_ISR                      (0xFC06804CU) /**< \brief (PIOD) Interrupt Status Register */
  #define REG_PIOD_MDER                     (0xFC068050U) /**< \brief (PIOD) Multi-driver Enable Register */
  #define REG_PIOD_MDDR                     (0xFC068054U) /**< \brief (PIOD) Multi-driver Disable Register */
  #define REG_PIOD_MDSR                     (0xFC068058U) /**< \brief (PIOD) Multi-driver Status Register */
  #define REG_PIOD_PUDR                     (0xFC068060U) /**< \brief (PIOD) Pull-up Disable Register */
  #define REG_PIOD_PUER                     (0xFC068064U) /**< \brief (PIOD) Pull-up Enable Register */
  #define REG_PIOD_PUSR                     (0xFC068068U) /**< \brief (PIOD) Pad Pull-up Status Register */
  #define REG_PIOD_ABCDSR                   (0xFC068070U) /**< \brief (PIOD) Peripheral Select Register */
  #define REG_PIOD_IFSCDR                   (0xFC068080U) /**< \brief (PIOD) Input Filter Slow Clock Disable Register */
  #define REG_PIOD_IFSCER                   (0xFC068084U) /**< \brief (PIOD) Input Filter Slow Clock Enable Register */
  #define REG_PIOD_IFSCSR                   (0xFC068088U) /**< \brief (PIOD) Input Filter Slow Clock Status Register */
  #define REG_PIOD_SCDR                     (0xFC06808CU) /**< \brief (PIOD) Slow Clock Divider Debouncing Register */
  #define REG_PIOD_PPDDR                    (0xFC068090U) /**< \brief (PIOD) Pad Pull-down Disable Register */
  #define REG_PIOD_PPDER                    (0xFC068094U) /**< \brief (PIOD) Pad Pull-down Enable Register */
  #define REG_PIOD_PPDSR                    (0xFC068098U) /**< \brief (PIOD) Pad Pull-down Status Register */
  #define REG_PIOD_OWER                     (0xFC0680A0U) /**< \brief (PIOD) Output Write Enable */
  #define REG_PIOD_OWDR                     (0xFC0680A4U) /**< \brief (PIOD) Output Write Disable */
  #define REG_PIOD_OWSR                     (0xFC0680A8U) /**< \brief (PIOD) Output Write Status Register */
  #define REG_PIOD_AIMER                    (0xFC0680B0U) /**< \brief (PIOD) Additional Interrupt Modes Enable Register */
  #define REG_PIOD_AIMDR                    (0xFC0680B4U) /**< \brief (PIOD) Additional Interrupt Modes Disable Register */
  #define REG_PIOD_AIMMR                    (0xFC0680B8U) /**< \brief (PIOD) Additional Interrupt Modes Mask Register */
  #define REG_PIOD_ESR                      (0xFC0680C0U) /**< \brief (PIOD) Edge Select Register */
  #define REG_PIOD_LSR                      (0xFC0680C4U) /**< \brief (PIOD) Level Select Register */
  #define REG_PIOD_ELSR                     (0xFC0680C8U) /**< \brief (PIOD) Edge/Level Status Register */
  #define REG_PIOD_FELLSR                   (0xFC0680D0U) /**< \brief (PIOD) Falling Edge/Low-Level Select Register */
  #define REG_PIOD_REHLSR                   (0xFC0680D4U) /**< \brief (PIOD) Rising Edge/High-Level Select Register */
  #define REG_PIOD_FRLHSR                   (0xFC0680D8U) /**< \brief (PIOD) Fall/Rise - Low/High Status Register */
  #define REG_PIOD_WPMR                     (0xFC0680E4U) /**< \brief (PIOD) Write Protection Mode Register */
  #define REG_PIOD_WPSR                     (0xFC0680E8U) /**< \brief (PIOD) Write Protection Status Register */
  #define REG_PIOD_SCHMITT                  (0xFC068100U) /**< \brief (PIOD) Schmitt Trigger Register */
  #define REG_PIOD_DRIVER1                  (0xFC068118U) /**< \brief (PIOD) I/O Drive Register 1 */
  #define REG_PIOD_DRIVER2                  (0xFC06811CU) /**< \brief (PIOD) I/O Drive Register 2 */
#else
  #define REG_PIOD_PER     (*(__O  uint32_t*)0xFC068000U) /**< \brief (PIOD) PIO Enable Register */
  #define REG_PIOD_PDR     (*(__O  uint32_t*)0xFC068004U) /**< \brief (PIOD) PIO Disable Register */
  #define REG_PIOD_PSR     (*(__I  uint32_t*)0xFC068008U) /**< \brief (PIOD) PIO Status Register */
  #define REG_PIOD_ISLR    (*(__IO uint32_t*)0xFC06800CU) /**< \brief (PIOD) PIO Interrupt Security Level Register */
  #define REG_PIOD_OER     (*(__O  uint32_t*)0xFC068010U) /**< \brief (PIOD) Output Enable Register */
  #define REG_PIOD_ODR     (*(__O  uint32_t*)0xFC068014U) /**< \brief (PIOD) Output Disable Register */
  #define REG_PIOD_OSR     (*(__I  uint32_t*)0xFC068018U) /**< \brief (PIOD) Output Status Register */
  #define REG_PIOD_IFER    (*(__O  uint32_t*)0xFC068020U) /**< \brief (PIOD) Glitch Input Filter Enable Register */
  #define REG_PIOD_IFDR    (*(__O  uint32_t*)0xFC068024U) /**< \brief (PIOD) Glitch Input Filter Disable Register */
  #define REG_PIOD_IFSR    (*(__I  uint32_t*)0xFC068028U) /**< \brief (PIOD) Glitch Input Filter Status Register */
  #define REG_PIOD_SODR    (*(__O  uint32_t*)0xFC068030U) /**< \brief (PIOD) Set Output Data Register */
  #define REG_PIOD_CODR    (*(__O  uint32_t*)0xFC068034U) /**< \brief (PIOD) Clear Output Data Register */
  #define REG_PIOD_ODSR    (*(__IO uint32_t*)0xFC068038U) /**< \brief (PIOD) Output Data Status Register */
  #define REG_PIOD_PDSR    (*(__I  uint32_t*)0xFC06803CU) /**< \brief (PIOD) Pin Data Status Register */
  #define REG_PIOD_IER     (*(__O  uint32_t*)0xFC068040U) /**< \brief (PIOD) Interrupt Enable Register */
  #define REG_PIOD_IDR     (*(__O  uint32_t*)0xFC068044U) /**< \brief (PIOD) Interrupt Disable Register */
  #define REG_PIOD_IMR     (*(__I  uint32_t*)0xFC068048U) /**< \brief (PIOD) Interrupt Mask Register */
  #define REG_PIOD_ISR     (*(__I  uint32_t*)0xFC06804CU) /**< \brief (PIOD) Interrupt Status Register */
  #define REG_PIOD_MDER    (*(__O  uint32_t*)0xFC068050U) /**< \brief (PIOD) Multi-driver Enable Register */
  #define REG_PIOD_MDDR    (*(__O  uint32_t*)0xFC068054U) /**< \brief (PIOD) Multi-driver Disable Register */
  #define REG_PIOD_MDSR    (*(__I  uint32_t*)0xFC068058U) /**< \brief (PIOD) Multi-driver Status Register */
  #define REG_PIOD_PUDR    (*(__O  uint32_t*)0xFC068060U) /**< \brief (PIOD) Pull-up Disable Register */
  #define REG_PIOD_PUER    (*(__O  uint32_t*)0xFC068064U) /**< \brief (PIOD) Pull-up Enable Register */
  #define REG_PIOD_PUSR    (*(__I  uint32_t*)0xFC068068U) /**< \brief (PIOD) Pad Pull-up Status Register */
  #define REG_PIOD_ABCDSR  (*(__IO uint32_t*)0xFC068070U) /**< \brief (PIOD) Peripheral Select Register */
  #define REG_PIOD_IFSCDR  (*(__O  uint32_t*)0xFC068080U) /**< \brief (PIOD) Input Filter Slow Clock Disable Register */
  #define REG_PIOD_IFSCER  (*(__O  uint32_t*)0xFC068084U) /**< \brief (PIOD) Input Filter Slow Clock Enable Register */
  #define REG_PIOD_IFSCSR  (*(__I  uint32_t*)0xFC068088U) /**< \brief (PIOD) Input Filter Slow Clock Status Register */
  #define REG_PIOD_SCDR    (*(__IO uint32_t*)0xFC06808CU) /**< \brief (PIOD) Slow Clock Divider Debouncing Register */
  #define REG_PIOD_PPDDR   (*(__O  uint32_t*)0xFC068090U) /**< \brief (PIOD) Pad Pull-down Disable Register */
  #define REG_PIOD_PPDER   (*(__O  uint32_t*)0xFC068094U) /**< \brief (PIOD) Pad Pull-down Enable Register */
  #define REG_PIOD_PPDSR   (*(__I  uint32_t*)0xFC068098U) /**< \brief (PIOD) Pad Pull-down Status Register */
  #define REG_PIOD_OWER    (*(__O  uint32_t*)0xFC0680A0U) /**< \brief (PIOD) Output Write Enable */
  #define REG_PIOD_OWDR    (*(__O  uint32_t*)0xFC0680A4U) /**< \brief (PIOD) Output Write Disable */
  #define REG_PIOD_OWSR    (*(__I  uint32_t*)0xFC0680A8U) /**< \brief (PIOD) Output Write Status Register */
  #define REG_PIOD_AIMER   (*(__O  uint32_t*)0xFC0680B0U) /**< \brief (PIOD) Additional Interrupt Modes Enable Register */
  #define REG_PIOD_AIMDR   (*(__O  uint32_t*)0xFC0680B4U) /**< \brief (PIOD) Additional Interrupt Modes Disable Register */
  #define REG_PIOD_AIMMR   (*(__I  uint32_t*)0xFC0680B8U) /**< \brief (PIOD) Additional Interrupt Modes Mask Register */
  #define REG_PIOD_ESR     (*(__O  uint32_t*)0xFC0680C0U) /**< \brief (PIOD) Edge Select Register */
  #define REG_PIOD_LSR     (*(__O  uint32_t*)0xFC0680C4U) /**< \brief (PIOD) Level Select Register */
  #define REG_PIOD_ELSR    (*(__I  uint32_t*)0xFC0680C8U) /**< \brief (PIOD) Edge/Level Status Register */
  #define REG_PIOD_FELLSR  (*(__O  uint32_t*)0xFC0680D0U) /**< \brief (PIOD) Falling Edge/Low-Level Select Register */
  #define REG_PIOD_REHLSR  (*(__O  uint32_t*)0xFC0680D4U) /**< \brief (PIOD) Rising Edge/High-Level Select Register */
  #define REG_PIOD_FRLHSR  (*(__I  uint32_t*)0xFC0680D8U) /**< \brief (PIOD) Fall/Rise - Low/High Status Register */
  #define REG_PIOD_WPMR    (*(__IO uint32_t*)0xFC0680E4U) /**< \brief (PIOD) Write Protection Mode Register */
  #define REG_PIOD_WPSR    (*(__I  uint32_t*)0xFC0680E8U) /**< \brief (PIOD) Write Protection Status Register */
  #define REG_PIOD_SCHMITT (*(__IO uint32_t*)0xFC068100U) /**< \brief (PIOD) Schmitt Trigger Register */
  #define REG_PIOD_DRIVER1 (*(__IO uint32_t*)0xFC068118U) /**< \brief (PIOD) I/O Drive Register 1 */
  #define REG_PIOD_DRIVER2 (*(__IO uint32_t*)0xFC06811CU) /**< \brief (PIOD) I/O Drive Register 2 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D4_PIOD_INSTANCE_ */
