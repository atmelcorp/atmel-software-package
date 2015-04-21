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

#ifndef _SAMA5D4_PIOB_INSTANCE_
#define _SAMA5D4_PIOB_INSTANCE_

/* ========== Register definition for PIOB peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_PIOB_PER                      (0xFC06B000U)	/**< \brief (PIOB) PIO Enable Register */
#define REG_PIOB_PDR                      (0xFC06B004U)	/**< \brief (PIOB) PIO Disable Register */
#define REG_PIOB_PSR                      (0xFC06B008U)	/**< \brief (PIOB) PIO Status Register */
#define REG_PIOB_ISLR                     (0xFC06B00CU)	/**< \brief (PIOB) PIO Interrupt Security Level Register */
#define REG_PIOB_OER                      (0xFC06B010U)	/**< \brief (PIOB) Output Enable Register */
#define REG_PIOB_ODR                      (0xFC06B014U)	/**< \brief (PIOB) Output Disable Register */
#define REG_PIOB_OSR                      (0xFC06B018U)	/**< \brief (PIOB) Output Status Register */
#define REG_PIOB_IFER                     (0xFC06B020U)	/**< \brief (PIOB) Glitch Input Filter Enable Register */
#define REG_PIOB_IFDR                     (0xFC06B024U)	/**< \brief (PIOB) Glitch Input Filter Disable Register */
#define REG_PIOB_IFSR                     (0xFC06B028U)	/**< \brief (PIOB) Glitch Input Filter Status Register */
#define REG_PIOB_SODR                     (0xFC06B030U)	/**< \brief (PIOB) Set Output Data Register */
#define REG_PIOB_CODR                     (0xFC06B034U)	/**< \brief (PIOB) Clear Output Data Register */
#define REG_PIOB_ODSR                     (0xFC06B038U)	/**< \brief (PIOB) Output Data Status Register */
#define REG_PIOB_PDSR                     (0xFC06B03CU)	/**< \brief (PIOB) Pin Data Status Register */
#define REG_PIOB_IER                      (0xFC06B040U)	/**< \brief (PIOB) Interrupt Enable Register */
#define REG_PIOB_IDR                      (0xFC06B044U)	/**< \brief (PIOB) Interrupt Disable Register */
#define REG_PIOB_IMR                      (0xFC06B048U)	/**< \brief (PIOB) Interrupt Mask Register */
#define REG_PIOB_ISR                      (0xFC06B04CU)	/**< \brief (PIOB) Interrupt Status Register */
#define REG_PIOB_MDER                     (0xFC06B050U)	/**< \brief (PIOB) Multi-driver Enable Register */
#define REG_PIOB_MDDR                     (0xFC06B054U)	/**< \brief (PIOB) Multi-driver Disable Register */
#define REG_PIOB_MDSR                     (0xFC06B058U)	/**< \brief (PIOB) Multi-driver Status Register */
#define REG_PIOB_PUDR                     (0xFC06B060U)	/**< \brief (PIOB) Pull-up Disable Register */
#define REG_PIOB_PUER                     (0xFC06B064U)	/**< \brief (PIOB) Pull-up Enable Register */
#define REG_PIOB_PUSR                     (0xFC06B068U)	/**< \brief (PIOB) Pad Pull-up Status Register */
#define REG_PIOB_ABCDSR                   (0xFC06B070U)	/**< \brief (PIOB) Peripheral Select Register */
#define REG_PIOB_IFSCDR                   (0xFC06B080U)	/**< \brief (PIOB) Input Filter Slow Clock Disable Register */
#define REG_PIOB_IFSCER                   (0xFC06B084U)	/**< \brief (PIOB) Input Filter Slow Clock Enable Register */
#define REG_PIOB_IFSCSR                   (0xFC06B088U)	/**< \brief (PIOB) Input Filter Slow Clock Status Register */
#define REG_PIOB_SCDR                     (0xFC06B08CU)	/**< \brief (PIOB) Slow Clock Divider Debouncing Register */
#define REG_PIOB_PPDDR                    (0xFC06B090U)	/**< \brief (PIOB) Pad Pull-down Disable Register */
#define REG_PIOB_PPDER                    (0xFC06B094U)	/**< \brief (PIOB) Pad Pull-down Enable Register */
#define REG_PIOB_PPDSR                    (0xFC06B098U)	/**< \brief (PIOB) Pad Pull-down Status Register */
#define REG_PIOB_OWER                     (0xFC06B0A0U)	/**< \brief (PIOB) Output Write Enable */
#define REG_PIOB_OWDR                     (0xFC06B0A4U)	/**< \brief (PIOB) Output Write Disable */
#define REG_PIOB_OWSR                     (0xFC06B0A8U)	/**< \brief (PIOB) Output Write Status Register */
#define REG_PIOB_AIMER                    (0xFC06B0B0U)	/**< \brief (PIOB) Additional Interrupt Modes Enable Register */
#define REG_PIOB_AIMDR                    (0xFC06B0B4U)	/**< \brief (PIOB) Additional Interrupt Modes Disable Register */
#define REG_PIOB_AIMMR                    (0xFC06B0B8U)	/**< \brief (PIOB) Additional Interrupt Modes Mask Register */
#define REG_PIOB_ESR                      (0xFC06B0C0U)	/**< \brief (PIOB) Edge Select Register */
#define REG_PIOB_LSR                      (0xFC06B0C4U)	/**< \brief (PIOB) Level Select Register */
#define REG_PIOB_ELSR                     (0xFC06B0C8U)	/**< \brief (PIOB) Edge/Level Status Register */
#define REG_PIOB_FELLSR                   (0xFC06B0D0U)	/**< \brief (PIOB) Falling Edge/Low-Level Select Register */
#define REG_PIOB_REHLSR                   (0xFC06B0D4U)	/**< \brief (PIOB) Rising Edge/High-Level Select Register */
#define REG_PIOB_FRLHSR                   (0xFC06B0D8U)	/**< \brief (PIOB) Fall/Rise - Low/High Status Register */
#define REG_PIOB_WPMR                     (0xFC06B0E4U)	/**< \brief (PIOB) Write Protection Mode Register */
#define REG_PIOB_WPSR                     (0xFC06B0E8U)	/**< \brief (PIOB) Write Protection Status Register */
#define REG_PIOB_SCHMITT                  (0xFC06B100U)	/**< \brief (PIOB) Schmitt Trigger Register */
#define REG_PIOB_DRIVER1                  (0xFC06B118U)	/**< \brief (PIOB) I/O Drive Register 1 */
#define REG_PIOB_DRIVER2                  (0xFC06B11CU)	/**< \brief (PIOB) I/O Drive Register 2 */
#else
#define REG_PIOB_PER     (*(__O  uint32_t*)0xFC06B000U)	/**< \brief (PIOB) PIO Enable Register */
#define REG_PIOB_PDR     (*(__O  uint32_t*)0xFC06B004U)	/**< \brief (PIOB) PIO Disable Register */
#define REG_PIOB_PSR     (*(__I  uint32_t*)0xFC06B008U)	/**< \brief (PIOB) PIO Status Register */
#define REG_PIOB_ISLR    (*(__IO uint32_t*)0xFC06B00CU)	/**< \brief (PIOB) PIO Interrupt Security Level Register */
#define REG_PIOB_OER     (*(__O  uint32_t*)0xFC06B010U)	/**< \brief (PIOB) Output Enable Register */
#define REG_PIOB_ODR     (*(__O  uint32_t*)0xFC06B014U)	/**< \brief (PIOB) Output Disable Register */
#define REG_PIOB_OSR     (*(__I  uint32_t*)0xFC06B018U)	/**< \brief (PIOB) Output Status Register */
#define REG_PIOB_IFER    (*(__O  uint32_t*)0xFC06B020U)	/**< \brief (PIOB) Glitch Input Filter Enable Register */
#define REG_PIOB_IFDR    (*(__O  uint32_t*)0xFC06B024U)	/**< \brief (PIOB) Glitch Input Filter Disable Register */
#define REG_PIOB_IFSR    (*(__I  uint32_t*)0xFC06B028U)	/**< \brief (PIOB) Glitch Input Filter Status Register */
#define REG_PIOB_SODR    (*(__O  uint32_t*)0xFC06B030U)	/**< \brief (PIOB) Set Output Data Register */
#define REG_PIOB_CODR    (*(__O  uint32_t*)0xFC06B034U)	/**< \brief (PIOB) Clear Output Data Register */
#define REG_PIOB_ODSR    (*(__IO uint32_t*)0xFC06B038U)	/**< \brief (PIOB) Output Data Status Register */
#define REG_PIOB_PDSR    (*(__I  uint32_t*)0xFC06B03CU)	/**< \brief (PIOB) Pin Data Status Register */
#define REG_PIOB_IER     (*(__O  uint32_t*)0xFC06B040U)	/**< \brief (PIOB) Interrupt Enable Register */
#define REG_PIOB_IDR     (*(__O  uint32_t*)0xFC06B044U)	/**< \brief (PIOB) Interrupt Disable Register */
#define REG_PIOB_IMR     (*(__I  uint32_t*)0xFC06B048U)	/**< \brief (PIOB) Interrupt Mask Register */
#define REG_PIOB_ISR     (*(__I  uint32_t*)0xFC06B04CU)	/**< \brief (PIOB) Interrupt Status Register */
#define REG_PIOB_MDER    (*(__O  uint32_t*)0xFC06B050U)	/**< \brief (PIOB) Multi-driver Enable Register */
#define REG_PIOB_MDDR    (*(__O  uint32_t*)0xFC06B054U)	/**< \brief (PIOB) Multi-driver Disable Register */
#define REG_PIOB_MDSR    (*(__I  uint32_t*)0xFC06B058U)	/**< \brief (PIOB) Multi-driver Status Register */
#define REG_PIOB_PUDR    (*(__O  uint32_t*)0xFC06B060U)	/**< \brief (PIOB) Pull-up Disable Register */
#define REG_PIOB_PUER    (*(__O  uint32_t*)0xFC06B064U)	/**< \brief (PIOB) Pull-up Enable Register */
#define REG_PIOB_PUSR    (*(__I  uint32_t*)0xFC06B068U)	/**< \brief (PIOB) Pad Pull-up Status Register */
#define REG_PIOB_ABCDSR  (*(__IO uint32_t*)0xFC06B070U)	/**< \brief (PIOB) Peripheral Select Register */
#define REG_PIOB_IFSCDR  (*(__O  uint32_t*)0xFC06B080U)	/**< \brief (PIOB) Input Filter Slow Clock Disable Register */
#define REG_PIOB_IFSCER  (*(__O  uint32_t*)0xFC06B084U)	/**< \brief (PIOB) Input Filter Slow Clock Enable Register */
#define REG_PIOB_IFSCSR  (*(__I  uint32_t*)0xFC06B088U)	/**< \brief (PIOB) Input Filter Slow Clock Status Register */
#define REG_PIOB_SCDR    (*(__IO uint32_t*)0xFC06B08CU)	/**< \brief (PIOB) Slow Clock Divider Debouncing Register */
#define REG_PIOB_PPDDR   (*(__O  uint32_t*)0xFC06B090U)	/**< \brief (PIOB) Pad Pull-down Disable Register */
#define REG_PIOB_PPDER   (*(__O  uint32_t*)0xFC06B094U)	/**< \brief (PIOB) Pad Pull-down Enable Register */
#define REG_PIOB_PPDSR   (*(__I  uint32_t*)0xFC06B098U)	/**< \brief (PIOB) Pad Pull-down Status Register */
#define REG_PIOB_OWER    (*(__O  uint32_t*)0xFC06B0A0U)	/**< \brief (PIOB) Output Write Enable */
#define REG_PIOB_OWDR    (*(__O  uint32_t*)0xFC06B0A4U)	/**< \brief (PIOB) Output Write Disable */
#define REG_PIOB_OWSR    (*(__I  uint32_t*)0xFC06B0A8U)	/**< \brief (PIOB) Output Write Status Register */
#define REG_PIOB_AIMER   (*(__O  uint32_t*)0xFC06B0B0U)	/**< \brief (PIOB) Additional Interrupt Modes Enable Register */
#define REG_PIOB_AIMDR   (*(__O  uint32_t*)0xFC06B0B4U)	/**< \brief (PIOB) Additional Interrupt Modes Disable Register */
#define REG_PIOB_AIMMR   (*(__I  uint32_t*)0xFC06B0B8U)	/**< \brief (PIOB) Additional Interrupt Modes Mask Register */
#define REG_PIOB_ESR     (*(__O  uint32_t*)0xFC06B0C0U)	/**< \brief (PIOB) Edge Select Register */
#define REG_PIOB_LSR     (*(__O  uint32_t*)0xFC06B0C4U)	/**< \brief (PIOB) Level Select Register */
#define REG_PIOB_ELSR    (*(__I  uint32_t*)0xFC06B0C8U)	/**< \brief (PIOB) Edge/Level Status Register */
#define REG_PIOB_FELLSR  (*(__O  uint32_t*)0xFC06B0D0U)	/**< \brief (PIOB) Falling Edge/Low-Level Select Register */
#define REG_PIOB_REHLSR  (*(__O  uint32_t*)0xFC06B0D4U)	/**< \brief (PIOB) Rising Edge/High-Level Select Register */
#define REG_PIOB_FRLHSR  (*(__I  uint32_t*)0xFC06B0D8U)	/**< \brief (PIOB) Fall/Rise - Low/High Status Register */
#define REG_PIOB_WPMR    (*(__IO uint32_t*)0xFC06B0E4U)	/**< \brief (PIOB) Write Protection Mode Register */
#define REG_PIOB_WPSR    (*(__I  uint32_t*)0xFC06B0E8U)	/**< \brief (PIOB) Write Protection Status Register */
#define REG_PIOB_SCHMITT (*(__IO uint32_t*)0xFC06B100U)	/**< \brief (PIOB) Schmitt Trigger Register */
#define REG_PIOB_DRIVER1 (*(__IO uint32_t*)0xFC06B118U)	/**< \brief (PIOB) I/O Drive Register 1 */
#define REG_PIOB_DRIVER2 (*(__IO uint32_t*)0xFC06B11CU)	/**< \brief (PIOB) I/O Drive Register 2 */
#endif				/* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif				/* _SAMA5D4_PIOB_INSTANCE_ */
