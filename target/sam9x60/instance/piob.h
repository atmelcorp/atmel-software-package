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

#ifndef _SAM9X_PIOB_INSTANCE_
#define _SAM9X_PIOB_INSTANCE_

/* ========== Register definition for PIOB peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_PIOB_PER                      (0xFFFFF600U) /**< \brief (PIOB) PIO Enable Register */
  #define REG_PIOB_PDR                      (0xFFFFF604U) /**< \brief (PIOB) PIO Disable Register */
  #define REG_PIOB_PSR                      (0xFFFFF608U) /**< \brief (PIOB) PIO Status Register */
  #define REG_PIOB_OER                      (0xFFFFF610U) /**< \brief (PIOB) Output Enable Register */
  #define REG_PIOB_ODR                      (0xFFFFF614U) /**< \brief (PIOB) Output Disable Register */
  #define REG_PIOB_OSR                      (0xFFFFF618U) /**< \brief (PIOB) Output Status Register */
  #define REG_PIOB_IFER                     (0xFFFFF620U) /**< \brief (PIOB) Glitch Input Filter Enable Register */
  #define REG_PIOB_IFDR                     (0xFFFFF624U) /**< \brief (PIOB) Glitch Input Filter Disable Register */
  #define REG_PIOB_IFSR                     (0xFFFFF628U) /**< \brief (PIOB) Glitch Input Filter Status Register */
  #define REG_PIOB_SODR                     (0xFFFFF630U) /**< \brief (PIOB) Set Output Data Register */
  #define REG_PIOB_CODR                     (0xFFFFF634U) /**< \brief (PIOB) Clear Output Data Register */
  #define REG_PIOB_ODSR                     (0xFFFFF638U) /**< \brief (PIOB) Output Data Status Register */
  #define REG_PIOB_PDSR                     (0xFFFFF63CU) /**< \brief (PIOB) Pin Data Status Register */
  #define REG_PIOB_IER                      (0xFFFFF640U) /**< \brief (PIOB) Interrupt Enable Register */
  #define REG_PIOB_IDR                      (0xFFFFF644U) /**< \brief (PIOB) Interrupt Disable Register */
  #define REG_PIOB_IMR                      (0xFFFFF648U) /**< \brief (PIOB) Interrupt Mask Register */
  #define REG_PIOB_ISR                      (0xFFFFF64CU) /**< \brief (PIOB) Interrupt Status Register */
  #define REG_PIOB_MDER                     (0xFFFFF650U) /**< \brief (PIOB) Multi-driver Enable Register */
  #define REG_PIOB_MDDR                     (0xFFFFF654U) /**< \brief (PIOB) Multi-driver Disable Register */
  #define REG_PIOB_MDSR                     (0xFFFFF658U) /**< \brief (PIOB) Multi-driver Status Register */
  #define REG_PIOB_PUDR                     (0xFFFFF660U) /**< \brief (PIOB) Pull-Up Disable Register */
  #define REG_PIOB_PUER                     (0xFFFFF664U) /**< \brief (PIOB) Pull-Up Enable Register */
  #define REG_PIOB_PUSR                     (0xFFFFF668U) /**< \brief (PIOB) Pad Pull-Up Status Register */
  #define REG_PIOB_ABCDSR                   (0xFFFFF670U) /**< \brief (PIOB) Peripheral ABCD Select Register */
  #define REG_PIOB_IFSCDR                   (0xFFFFF680U) /**< \brief (PIOB) Input Filter Slow Clock Disable Register */
  #define REG_PIOB_IFSCER                   (0xFFFFF684U) /**< \brief (PIOB) Input Filter Slow Clock Enable Register */
  #define REG_PIOB_IFSCSR                   (0xFFFFF688U) /**< \brief (PIOB) Input Filter Slow Clock Status Register */
  #define REG_PIOB_SCDR                     (0xFFFFF68CU) /**< \brief (PIOB) Slow Clock Divider Debouncing Register */
  #define REG_PIOB_PPDDR                    (0xFFFFF690U) /**< \brief (PIOB) Pad Pull-Down Disable Register */
  #define REG_PIOB_PPDER                    (0xFFFFF694U) /**< \brief (PIOB) Pad Pull-Down Enable Register */
  #define REG_PIOB_PPDSR                    (0xFFFFF698U) /**< \brief (PIOB) Pad Pull-Down Status Register */
  #define REG_PIOB_OWER                     (0xFFFFF6A0U) /**< \brief (PIOB) Output Write Enable */
  #define REG_PIOB_OWDR                     (0xFFFFF6A4U) /**< \brief (PIOB) Output Write Disable */
  #define REG_PIOB_OWSR                     (0xFFFFF6A8U) /**< \brief (PIOB) Output Write Status Register */
  #define REG_PIOB_AIMER                    (0xFFFFF6B0U) /**< \brief (PIOB) Additional Interrupt Modes Enable Register */
  #define REG_PIOB_AIMDR                    (0xFFFFF6B4U) /**< \brief (PIOB) Additional Interrupt Modes Disable Register */
  #define REG_PIOB_AIMMR                    (0xFFFFF6B8U) /**< \brief (PIOB) Additional Interrupt Modes Mask Register */
  #define REG_PIOB_ESR                      (0xFFFFF6C0U) /**< \brief (PIOB) Edge Select Register */
  #define REG_PIOB_LSR                      (0xFFFFF6C4U) /**< \brief (PIOB) Level Select Register */
  #define REG_PIOB_ELSR                     (0xFFFFF6C8U) /**< \brief (PIOB) Edge/Level Status Register */
  #define REG_PIOB_FELLSR                   (0xFFFFF6D0U) /**< \brief (PIOB) Falling Edge/Low-Level Select Register */
  #define REG_PIOB_REHLSR                   (0xFFFFF6D4U) /**< \brief (PIOB) Rising Edge/High-Level Select Register */
  #define REG_PIOB_FRLHSR                   (0xFFFFF6D8U) /**< \brief (PIOB) Fall/Rise - Low/High Status Register */
  #define REG_PIOB_WPMR                     (0xFFFFF6E4U) /**< \brief (PIOB) Write Protection Mode Register */
  #define REG_PIOB_WPSR                     (0xFFFFF6E8U) /**< \brief (PIOB) Write Protection Status Register */
  #define REG_PIOB_SCHMITT                  (0xFFFFF700U) /**< \brief (PIOB) Schmitt Trigger Register */
  #define REG_PIOB_SLEWR                    (0xFFFFF710U) /**< \brief (PIOB) I/O Slewrate Control Register */
  #define REG_PIOB_DRIVER                   (0xFFFFF718U) /**< \brief (PIOB) I/O Drive Register */
#else
  #define REG_PIOB_PER     (*(__O  uint32_t*)0xFFFFF600U) /**< \brief (PIOB) PIO Enable Register */
  #define REG_PIOB_PDR     (*(__O  uint32_t*)0xFFFFF604U) /**< \brief (PIOB) PIO Disable Register */
  #define REG_PIOB_PSR     (*(__I  uint32_t*)0xFFFFF608U) /**< \brief (PIOB) PIO Status Register */
  #define REG_PIOB_OER     (*(__O  uint32_t*)0xFFFFF610U) /**< \brief (PIOB) Output Enable Register */
  #define REG_PIOB_ODR     (*(__O  uint32_t*)0xFFFFF614U) /**< \brief (PIOB) Output Disable Register */
  #define REG_PIOB_OSR     (*(__I  uint32_t*)0xFFFFF618U) /**< \brief (PIOB) Output Status Register */
  #define REG_PIOB_IFER    (*(__O  uint32_t*)0xFFFFF620U) /**< \brief (PIOB) Glitch Input Filter Enable Register */
  #define REG_PIOB_IFDR    (*(__O  uint32_t*)0xFFFFF624U) /**< \brief (PIOB) Glitch Input Filter Disable Register */
  #define REG_PIOB_IFSR    (*(__I  uint32_t*)0xFFFFF628U) /**< \brief (PIOB) Glitch Input Filter Status Register */
  #define REG_PIOB_SODR    (*(__O  uint32_t*)0xFFFFF630U) /**< \brief (PIOB) Set Output Data Register */
  #define REG_PIOB_CODR    (*(__O  uint32_t*)0xFFFFF634U) /**< \brief (PIOB) Clear Output Data Register */
  #define REG_PIOB_ODSR    (*(__IO uint32_t*)0xFFFFF638U) /**< \brief (PIOB) Output Data Status Register */
  #define REG_PIOB_PDSR    (*(__I  uint32_t*)0xFFFFF63CU) /**< \brief (PIOB) Pin Data Status Register */
  #define REG_PIOB_IER     (*(__O  uint32_t*)0xFFFFF640U) /**< \brief (PIOB) Interrupt Enable Register */
  #define REG_PIOB_IDR     (*(__O  uint32_t*)0xFFFFF644U) /**< \brief (PIOB) Interrupt Disable Register */
  #define REG_PIOB_IMR     (*(__I  uint32_t*)0xFFFFF648U) /**< \brief (PIOB) Interrupt Mask Register */
  #define REG_PIOB_ISR     (*(__I  uint32_t*)0xFFFFF64CU) /**< \brief (PIOB) Interrupt Status Register */
  #define REG_PIOB_MDER    (*(__O  uint32_t*)0xFFFFF650U) /**< \brief (PIOB) Multi-driver Enable Register */
  #define REG_PIOB_MDDR    (*(__O  uint32_t*)0xFFFFF654U) /**< \brief (PIOB) Multi-driver Disable Register */
  #define REG_PIOB_MDSR    (*(__I  uint32_t*)0xFFFFF658U) /**< \brief (PIOB) Multi-driver Status Register */
  #define REG_PIOB_PUDR    (*(__O  uint32_t*)0xFFFFF660U) /**< \brief (PIOB) Pull-Up Disable Register */
  #define REG_PIOB_PUER    (*(__O  uint32_t*)0xFFFFF664U) /**< \brief (PIOB) Pull-Up Enable Register */
  #define REG_PIOB_PUSR    (*(__I  uint32_t*)0xFFFFF668U) /**< \brief (PIOB) Pad Pull-Up Status Register */
  #define REG_PIOB_ABCDSR  (*(__IO uint32_t*)0xFFFFF670U) /**< \brief (PIOB) Peripheral ABCD Select Register */
  #define REG_PIOB_IFSCDR  (*(__O  uint32_t*)0xFFFFF680U) /**< \brief (PIOB) Input Filter Slow Clock Disable Register */
  #define REG_PIOB_IFSCER  (*(__O  uint32_t*)0xFFFFF684U) /**< \brief (PIOB) Input Filter Slow Clock Enable Register */
  #define REG_PIOB_IFSCSR  (*(__I  uint32_t*)0xFFFFF688U) /**< \brief (PIOB) Input Filter Slow Clock Status Register */
  #define REG_PIOB_SCDR    (*(__IO uint32_t*)0xFFFFF68CU) /**< \brief (PIOB) Slow Clock Divider Debouncing Register */
  #define REG_PIOB_PPDDR   (*(__O  uint32_t*)0xFFFFF690U) /**< \brief (PIOB) Pad Pull-Down Disable Register */
  #define REG_PIOB_PPDER   (*(__O  uint32_t*)0xFFFFF694U) /**< \brief (PIOB) Pad Pull-Down Enable Register */
  #define REG_PIOB_PPDSR   (*(__I  uint32_t*)0xFFFFF698U) /**< \brief (PIOB) Pad Pull-Down Status Register */
  #define REG_PIOB_OWER    (*(__O  uint32_t*)0xFFFFF6A0U) /**< \brief (PIOB) Output Write Enable */
  #define REG_PIOB_OWDR    (*(__O  uint32_t*)0xFFFFF6A4U) /**< \brief (PIOB) Output Write Disable */
  #define REG_PIOB_OWSR    (*(__I  uint32_t*)0xFFFFF6A8U) /**< \brief (PIOB) Output Write Status Register */
  #define REG_PIOB_AIMER   (*(__O  uint32_t*)0xFFFFF6B0U) /**< \brief (PIOB) Additional Interrupt Modes Enable Register */
  #define REG_PIOB_AIMDR   (*(__O  uint32_t*)0xFFFFF6B4U) /**< \brief (PIOB) Additional Interrupt Modes Disable Register */
  #define REG_PIOB_AIMMR   (*(__I  uint32_t*)0xFFFFF6B8U) /**< \brief (PIOB) Additional Interrupt Modes Mask Register */
  #define REG_PIOB_ESR     (*(__O  uint32_t*)0xFFFFF6C0U) /**< \brief (PIOB) Edge Select Register */
  #define REG_PIOB_LSR     (*(__O  uint32_t*)0xFFFFF6C4U) /**< \brief (PIOB) Level Select Register */
  #define REG_PIOB_ELSR    (*(__I  uint32_t*)0xFFFFF6C8U) /**< \brief (PIOB) Edge/Level Status Register */
  #define REG_PIOB_FELLSR  (*(__O  uint32_t*)0xFFFFF6D0U) /**< \brief (PIOB) Falling Edge/Low-Level Select Register */
  #define REG_PIOB_REHLSR  (*(__O  uint32_t*)0xFFFFF6D4U) /**< \brief (PIOB) Rising Edge/High-Level Select Register */
  #define REG_PIOB_FRLHSR  (*(__I  uint32_t*)0xFFFFF6D8U) /**< \brief (PIOB) Fall/Rise - Low/High Status Register */
  #define REG_PIOB_WPMR    (*(__IO uint32_t*)0xFFFFF6E4U) /**< \brief (PIOB) Write Protection Mode Register */
  #define REG_PIOB_WPSR    (*(__I  uint32_t*)0xFFFFF6E8U) /**< \brief (PIOB) Write Protection Status Register */
  #define REG_PIOB_SCHMITT (*(__IO uint32_t*)0xFFFFF700U) /**< \brief (PIOB) Schmitt Trigger Register */
  #define REG_PIOB_SLEWR   (*(__IO uint32_t*)0xFFFFF710U) /**< \brief (PIOB) I/O Slewrate Control Register */
  #define REG_PIOB_DRIVER  (*(__IO uint32_t*)0xFFFFF718U) /**< \brief (PIOB) I/O Drive Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_PIOB_INSTANCE_ */
