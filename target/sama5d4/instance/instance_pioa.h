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

#ifndef _SAMA5D4_PIOA_INSTANCE_
#define _SAMA5D4_PIOA_INSTANCE_

/* ========== Register definition for PIOA peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_PIOA_PER                      (0xFC06A000U)	/**< \brief (PIOA) PIO Enable Register */
#define REG_PIOA_PDR                      (0xFC06A004U)	/**< \brief (PIOA) PIO Disable Register */
#define REG_PIOA_PSR                      (0xFC06A008U)	/**< \brief (PIOA) PIO Status Register */
#define REG_PIOA_ISLR                     (0xFC06A00CU)	/**< \brief (PIOA) PIO Interrupt Security Level Register */
#define REG_PIOA_OER                      (0xFC06A010U)	/**< \brief (PIOA) Output Enable Register */
#define REG_PIOA_ODR                      (0xFC06A014U)	/**< \brief (PIOA) Output Disable Register */
#define REG_PIOA_OSR                      (0xFC06A018U)	/**< \brief (PIOA) Output Status Register */
#define REG_PIOA_IFER                     (0xFC06A020U)	/**< \brief (PIOA) Glitch Input Filter Enable Register */
#define REG_PIOA_IFDR                     (0xFC06A024U)	/**< \brief (PIOA) Glitch Input Filter Disable Register */
#define REG_PIOA_IFSR                     (0xFC06A028U)	/**< \brief (PIOA) Glitch Input Filter Status Register */
#define REG_PIOA_SODR                     (0xFC06A030U)	/**< \brief (PIOA) Set Output Data Register */
#define REG_PIOA_CODR                     (0xFC06A034U)	/**< \brief (PIOA) Clear Output Data Register */
#define REG_PIOA_ODSR                     (0xFC06A038U)	/**< \brief (PIOA) Output Data Status Register */
#define REG_PIOA_PDSR                     (0xFC06A03CU)	/**< \brief (PIOA) Pin Data Status Register */
#define REG_PIOA_IER                      (0xFC06A040U)	/**< \brief (PIOA) Interrupt Enable Register */
#define REG_PIOA_IDR                      (0xFC06A044U)	/**< \brief (PIOA) Interrupt Disable Register */
#define REG_PIOA_IMR                      (0xFC06A048U)	/**< \brief (PIOA) Interrupt Mask Register */
#define REG_PIOA_ISR                      (0xFC06A04CU)	/**< \brief (PIOA) Interrupt Status Register */
#define REG_PIOA_MDER                     (0xFC06A050U)	/**< \brief (PIOA) Multi-driver Enable Register */
#define REG_PIOA_MDDR                     (0xFC06A054U)	/**< \brief (PIOA) Multi-driver Disable Register */
#define REG_PIOA_MDSR                     (0xFC06A058U)	/**< \brief (PIOA) Multi-driver Status Register */
#define REG_PIOA_PUDR                     (0xFC06A060U)	/**< \brief (PIOA) Pull-up Disable Register */
#define REG_PIOA_PUER                     (0xFC06A064U)	/**< \brief (PIOA) Pull-up Enable Register */
#define REG_PIOA_PUSR                     (0xFC06A068U)	/**< \brief (PIOA) Pad Pull-up Status Register */
#define REG_PIOA_ABCDSR                   (0xFC06A070U)	/**< \brief (PIOA) Peripheral Select Register */
#define REG_PIOA_IFSCDR                   (0xFC06A080U)	/**< \brief (PIOA) Input Filter Slow Clock Disable Register */
#define REG_PIOA_IFSCER                   (0xFC06A084U)	/**< \brief (PIOA) Input Filter Slow Clock Enable Register */
#define REG_PIOA_IFSCSR                   (0xFC06A088U)	/**< \brief (PIOA) Input Filter Slow Clock Status Register */
#define REG_PIOA_SCDR                     (0xFC06A08CU)	/**< \brief (PIOA) Slow Clock Divider Debouncing Register */
#define REG_PIOA_PPDDR                    (0xFC06A090U)	/**< \brief (PIOA) Pad Pull-down Disable Register */
#define REG_PIOA_PPDER                    (0xFC06A094U)	/**< \brief (PIOA) Pad Pull-down Enable Register */
#define REG_PIOA_PPDSR                    (0xFC06A098U)	/**< \brief (PIOA) Pad Pull-down Status Register */
#define REG_PIOA_OWER                     (0xFC06A0A0U)	/**< \brief (PIOA) Output Write Enable */
#define REG_PIOA_OWDR                     (0xFC06A0A4U)	/**< \brief (PIOA) Output Write Disable */
#define REG_PIOA_OWSR                     (0xFC06A0A8U)	/**< \brief (PIOA) Output Write Status Register */
#define REG_PIOA_AIMER                    (0xFC06A0B0U)	/**< \brief (PIOA) Additional Interrupt Modes Enable Register */
#define REG_PIOA_AIMDR                    (0xFC06A0B4U)	/**< \brief (PIOA) Additional Interrupt Modes Disable Register */
#define REG_PIOA_AIMMR                    (0xFC06A0B8U)	/**< \brief (PIOA) Additional Interrupt Modes Mask Register */
#define REG_PIOA_ESR                      (0xFC06A0C0U)	/**< \brief (PIOA) Edge Select Register */
#define REG_PIOA_LSR                      (0xFC06A0C4U)	/**< \brief (PIOA) Level Select Register */
#define REG_PIOA_ELSR                     (0xFC06A0C8U)	/**< \brief (PIOA) Edge/Level Status Register */
#define REG_PIOA_FELLSR                   (0xFC06A0D0U)	/**< \brief (PIOA) Falling Edge/Low-Level Select Register */
#define REG_PIOA_REHLSR                   (0xFC06A0D4U)	/**< \brief (PIOA) Rising Edge/High-Level Select Register */
#define REG_PIOA_FRLHSR                   (0xFC06A0D8U)	/**< \brief (PIOA) Fall/Rise - Low/High Status Register */
#define REG_PIOA_WPMR                     (0xFC06A0E4U)	/**< \brief (PIOA) Write Protection Mode Register */
#define REG_PIOA_WPSR                     (0xFC06A0E8U)	/**< \brief (PIOA) Write Protection Status Register */
#define REG_PIOA_SCHMITT                  (0xFC06A100U)	/**< \brief (PIOA) Schmitt Trigger Register */
#define REG_PIOA_DRIVER1                  (0xFC06A118U)	/**< \brief (PIOA) I/O Drive Register 1 */
#define REG_PIOA_DRIVER2                  (0xFC06A11CU)	/**< \brief (PIOA) I/O Drive Register 2 */
#else
#define REG_PIOA_PER     (*(__O  uint32_t*)0xFC06A000U)	/**< \brief (PIOA) PIO Enable Register */
#define REG_PIOA_PDR     (*(__O  uint32_t*)0xFC06A004U)	/**< \brief (PIOA) PIO Disable Register */
#define REG_PIOA_PSR     (*(__I  uint32_t*)0xFC06A008U)	/**< \brief (PIOA) PIO Status Register */
#define REG_PIOA_ISLR    (*(__IO uint32_t*)0xFC06A00CU)	/**< \brief (PIOA) PIO Interrupt Security Level Register */
#define REG_PIOA_OER     (*(__O  uint32_t*)0xFC06A010U)	/**< \brief (PIOA) Output Enable Register */
#define REG_PIOA_ODR     (*(__O  uint32_t*)0xFC06A014U)	/**< \brief (PIOA) Output Disable Register */
#define REG_PIOA_OSR     (*(__I  uint32_t*)0xFC06A018U)	/**< \brief (PIOA) Output Status Register */
#define REG_PIOA_IFER    (*(__O  uint32_t*)0xFC06A020U)	/**< \brief (PIOA) Glitch Input Filter Enable Register */
#define REG_PIOA_IFDR    (*(__O  uint32_t*)0xFC06A024U)	/**< \brief (PIOA) Glitch Input Filter Disable Register */
#define REG_PIOA_IFSR    (*(__I  uint32_t*)0xFC06A028U)	/**< \brief (PIOA) Glitch Input Filter Status Register */
#define REG_PIOA_SODR    (*(__O  uint32_t*)0xFC06A030U)	/**< \brief (PIOA) Set Output Data Register */
#define REG_PIOA_CODR    (*(__O  uint32_t*)0xFC06A034U)	/**< \brief (PIOA) Clear Output Data Register */
#define REG_PIOA_ODSR    (*(__IO uint32_t*)0xFC06A038U)	/**< \brief (PIOA) Output Data Status Register */
#define REG_PIOA_PDSR    (*(__I  uint32_t*)0xFC06A03CU)	/**< \brief (PIOA) Pin Data Status Register */
#define REG_PIOA_IER     (*(__O  uint32_t*)0xFC06A040U)	/**< \brief (PIOA) Interrupt Enable Register */
#define REG_PIOA_IDR     (*(__O  uint32_t*)0xFC06A044U)	/**< \brief (PIOA) Interrupt Disable Register */
#define REG_PIOA_IMR     (*(__I  uint32_t*)0xFC06A048U)	/**< \brief (PIOA) Interrupt Mask Register */
#define REG_PIOA_ISR     (*(__I  uint32_t*)0xFC06A04CU)	/**< \brief (PIOA) Interrupt Status Register */
#define REG_PIOA_MDER    (*(__O  uint32_t*)0xFC06A050U)	/**< \brief (PIOA) Multi-driver Enable Register */
#define REG_PIOA_MDDR    (*(__O  uint32_t*)0xFC06A054U)	/**< \brief (PIOA) Multi-driver Disable Register */
#define REG_PIOA_MDSR    (*(__I  uint32_t*)0xFC06A058U)	/**< \brief (PIOA) Multi-driver Status Register */
#define REG_PIOA_PUDR    (*(__O  uint32_t*)0xFC06A060U)	/**< \brief (PIOA) Pull-up Disable Register */
#define REG_PIOA_PUER    (*(__O  uint32_t*)0xFC06A064U)	/**< \brief (PIOA) Pull-up Enable Register */
#define REG_PIOA_PUSR    (*(__I  uint32_t*)0xFC06A068U)	/**< \brief (PIOA) Pad Pull-up Status Register */
#define REG_PIOA_ABCDSR  (*(__IO uint32_t*)0xFC06A070U)	/**< \brief (PIOA) Peripheral Select Register */
#define REG_PIOA_IFSCDR  (*(__O  uint32_t*)0xFC06A080U)	/**< \brief (PIOA) Input Filter Slow Clock Disable Register */
#define REG_PIOA_IFSCER  (*(__O  uint32_t*)0xFC06A084U)	/**< \brief (PIOA) Input Filter Slow Clock Enable Register */
#define REG_PIOA_IFSCSR  (*(__I  uint32_t*)0xFC06A088U)	/**< \brief (PIOA) Input Filter Slow Clock Status Register */
#define REG_PIOA_SCDR    (*(__IO uint32_t*)0xFC06A08CU)	/**< \brief (PIOA) Slow Clock Divider Debouncing Register */
#define REG_PIOA_PPDDR   (*(__O  uint32_t*)0xFC06A090U)	/**< \brief (PIOA) Pad Pull-down Disable Register */
#define REG_PIOA_PPDER   (*(__O  uint32_t*)0xFC06A094U)	/**< \brief (PIOA) Pad Pull-down Enable Register */
#define REG_PIOA_PPDSR   (*(__I  uint32_t*)0xFC06A098U)	/**< \brief (PIOA) Pad Pull-down Status Register */
#define REG_PIOA_OWER    (*(__O  uint32_t*)0xFC06A0A0U)	/**< \brief (PIOA) Output Write Enable */
#define REG_PIOA_OWDR    (*(__O  uint32_t*)0xFC06A0A4U)	/**< \brief (PIOA) Output Write Disable */
#define REG_PIOA_OWSR    (*(__I  uint32_t*)0xFC06A0A8U)	/**< \brief (PIOA) Output Write Status Register */
#define REG_PIOA_AIMER   (*(__O  uint32_t*)0xFC06A0B0U)	/**< \brief (PIOA) Additional Interrupt Modes Enable Register */
#define REG_PIOA_AIMDR   (*(__O  uint32_t*)0xFC06A0B4U)	/**< \brief (PIOA) Additional Interrupt Modes Disable Register */
#define REG_PIOA_AIMMR   (*(__I  uint32_t*)0xFC06A0B8U)	/**< \brief (PIOA) Additional Interrupt Modes Mask Register */
#define REG_PIOA_ESR     (*(__O  uint32_t*)0xFC06A0C0U)	/**< \brief (PIOA) Edge Select Register */
#define REG_PIOA_LSR     (*(__O  uint32_t*)0xFC06A0C4U)	/**< \brief (PIOA) Level Select Register */
#define REG_PIOA_ELSR    (*(__I  uint32_t*)0xFC06A0C8U)	/**< \brief (PIOA) Edge/Level Status Register */
#define REG_PIOA_FELLSR  (*(__O  uint32_t*)0xFC06A0D0U)	/**< \brief (PIOA) Falling Edge/Low-Level Select Register */
#define REG_PIOA_REHLSR  (*(__O  uint32_t*)0xFC06A0D4U)	/**< \brief (PIOA) Rising Edge/High-Level Select Register */
#define REG_PIOA_FRLHSR  (*(__I  uint32_t*)0xFC06A0D8U)	/**< \brief (PIOA) Fall/Rise - Low/High Status Register */
#define REG_PIOA_WPMR    (*(__IO uint32_t*)0xFC06A0E4U)	/**< \brief (PIOA) Write Protection Mode Register */
#define REG_PIOA_WPSR    (*(__I  uint32_t*)0xFC06A0E8U)	/**< \brief (PIOA) Write Protection Status Register */
#define REG_PIOA_SCHMITT (*(__IO uint32_t*)0xFC06A100U)	/**< \brief (PIOA) Schmitt Trigger Register */
#define REG_PIOA_DRIVER1 (*(__IO uint32_t*)0xFC06A118U)	/**< \brief (PIOA) I/O Drive Register 1 */
#define REG_PIOA_DRIVER2 (*(__IO uint32_t*)0xFC06A11CU)	/**< \brief (PIOA) I/O Drive Register 2 */
#endif				/* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif				/* _SAMA5D4_PIOA_INSTANCE_ */
