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

#ifndef _SAM9X_PIOA_INSTANCE_
#define _SAM9X_PIOA_INSTANCE_

/* ========== Register definition for PIOA peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_PIOA_PER                      (0xFFFFF400U) /**< \brief (PIOA) PIO Enable Register */
  #define REG_PIOA_PDR                      (0xFFFFF404U) /**< \brief (PIOA) PIO Disable Register */
  #define REG_PIOA_PSR                      (0xFFFFF408U) /**< \brief (PIOA) PIO Status Register */
  #define REG_PIOA_OER                      (0xFFFFF410U) /**< \brief (PIOA) Output Enable Register */
  #define REG_PIOA_ODR                      (0xFFFFF414U) /**< \brief (PIOA) Output Disable Register */
  #define REG_PIOA_OSR                      (0xFFFFF418U) /**< \brief (PIOA) Output Status Register */
  #define REG_PIOA_IFER                     (0xFFFFF420U) /**< \brief (PIOA) Glitch Input Filter Enable Register */
  #define REG_PIOA_IFDR                     (0xFFFFF424U) /**< \brief (PIOA) Glitch Input Filter Disable Register */
  #define REG_PIOA_IFSR                     (0xFFFFF428U) /**< \brief (PIOA) Glitch Input Filter Status Register */
  #define REG_PIOA_SODR                     (0xFFFFF430U) /**< \brief (PIOA) Set Output Data Register */
  #define REG_PIOA_CODR                     (0xFFFFF434U) /**< \brief (PIOA) Clear Output Data Register */
  #define REG_PIOA_ODSR                     (0xFFFFF438U) /**< \brief (PIOA) Output Data Status Register */
  #define REG_PIOA_PDSR                     (0xFFFFF43CU) /**< \brief (PIOA) Pin Data Status Register */
  #define REG_PIOA_IER                      (0xFFFFF440U) /**< \brief (PIOA) Interrupt Enable Register */
  #define REG_PIOA_IDR                      (0xFFFFF444U) /**< \brief (PIOA) Interrupt Disable Register */
  #define REG_PIOA_IMR                      (0xFFFFF448U) /**< \brief (PIOA) Interrupt Mask Register */
  #define REG_PIOA_ISR                      (0xFFFFF44CU) /**< \brief (PIOA) Interrupt Status Register */
  #define REG_PIOA_MDER                     (0xFFFFF450U) /**< \brief (PIOA) Multi-driver Enable Register */
  #define REG_PIOA_MDDR                     (0xFFFFF454U) /**< \brief (PIOA) Multi-driver Disable Register */
  #define REG_PIOA_MDSR                     (0xFFFFF458U) /**< \brief (PIOA) Multi-driver Status Register */
  #define REG_PIOA_PUDR                     (0xFFFFF460U) /**< \brief (PIOA) Pull-Up Disable Register */
  #define REG_PIOA_PUER                     (0xFFFFF464U) /**< \brief (PIOA) Pull-Up Enable Register */
  #define REG_PIOA_PUSR                     (0xFFFFF468U) /**< \brief (PIOA) Pad Pull-Up Status Register */
  #define REG_PIOA_ABCDSR                   (0xFFFFF470U) /**< \brief (PIOA) Peripheral ABCD Select Register */
  #define REG_PIOA_IFSCDR                   (0xFFFFF480U) /**< \brief (PIOA) Input Filter Slow Clock Disable Register */
  #define REG_PIOA_IFSCER                   (0xFFFFF484U) /**< \brief (PIOA) Input Filter Slow Clock Enable Register */
  #define REG_PIOA_IFSCSR                   (0xFFFFF488U) /**< \brief (PIOA) Input Filter Slow Clock Status Register */
  #define REG_PIOA_SCDR                     (0xFFFFF48CU) /**< \brief (PIOA) Slow Clock Divider Debouncing Register */
  #define REG_PIOA_PPDDR                    (0xFFFFF490U) /**< \brief (PIOA) Pad Pull-Down Disable Register */
  #define REG_PIOA_PPDER                    (0xFFFFF494U) /**< \brief (PIOA) Pad Pull-Down Enable Register */
  #define REG_PIOA_PPDSR                    (0xFFFFF498U) /**< \brief (PIOA) Pad Pull-Down Status Register */
  #define REG_PIOA_OWER                     (0xFFFFF4A0U) /**< \brief (PIOA) Output Write Enable */
  #define REG_PIOA_OWDR                     (0xFFFFF4A4U) /**< \brief (PIOA) Output Write Disable */
  #define REG_PIOA_OWSR                     (0xFFFFF4A8U) /**< \brief (PIOA) Output Write Status Register */
  #define REG_PIOA_AIMER                    (0xFFFFF4B0U) /**< \brief (PIOA) Additional Interrupt Modes Enable Register */
  #define REG_PIOA_AIMDR                    (0xFFFFF4B4U) /**< \brief (PIOA) Additional Interrupt Modes Disable Register */
  #define REG_PIOA_AIMMR                    (0xFFFFF4B8U) /**< \brief (PIOA) Additional Interrupt Modes Mask Register */
  #define REG_PIOA_ESR                      (0xFFFFF4C0U) /**< \brief (PIOA) Edge Select Register */
  #define REG_PIOA_LSR                      (0xFFFFF4C4U) /**< \brief (PIOA) Level Select Register */
  #define REG_PIOA_ELSR                     (0xFFFFF4C8U) /**< \brief (PIOA) Edge/Level Status Register */
  #define REG_PIOA_FELLSR                   (0xFFFFF4D0U) /**< \brief (PIOA) Falling Edge/Low-Level Select Register */
  #define REG_PIOA_REHLSR                   (0xFFFFF4D4U) /**< \brief (PIOA) Rising Edge/High-Level Select Register */
  #define REG_PIOA_FRLHSR                   (0xFFFFF4D8U) /**< \brief (PIOA) Fall/Rise - Low/High Status Register */
  #define REG_PIOA_WPMR                     (0xFFFFF4E4U) /**< \brief (PIOA) Write Protection Mode Register */
  #define REG_PIOA_WPSR                     (0xFFFFF4E8U) /**< \brief (PIOA) Write Protection Status Register */
  #define REG_PIOA_SCHMITT                  (0xFFFFF500U) /**< \brief (PIOA) Schmitt Trigger Register */
  #define REG_PIOA_SLEWR                    (0xFFFFF510U) /**< \brief (PIOA) I/O Slewrate Control Register */
  #define REG_PIOA_DRIVER                   (0xFFFFF518U) /**< \brief (PIOA) I/O Drive Register */
#else
  #define REG_PIOA_PER     (*(__O  uint32_t*)0xFFFFF400U) /**< \brief (PIOA) PIO Enable Register */
  #define REG_PIOA_PDR     (*(__O  uint32_t*)0xFFFFF404U) /**< \brief (PIOA) PIO Disable Register */
  #define REG_PIOA_PSR     (*(__I  uint32_t*)0xFFFFF408U) /**< \brief (PIOA) PIO Status Register */
  #define REG_PIOA_OER     (*(__O  uint32_t*)0xFFFFF410U) /**< \brief (PIOA) Output Enable Register */
  #define REG_PIOA_ODR     (*(__O  uint32_t*)0xFFFFF414U) /**< \brief (PIOA) Output Disable Register */
  #define REG_PIOA_OSR     (*(__I  uint32_t*)0xFFFFF418U) /**< \brief (PIOA) Output Status Register */
  #define REG_PIOA_IFER    (*(__O  uint32_t*)0xFFFFF420U) /**< \brief (PIOA) Glitch Input Filter Enable Register */
  #define REG_PIOA_IFDR    (*(__O  uint32_t*)0xFFFFF424U) /**< \brief (PIOA) Glitch Input Filter Disable Register */
  #define REG_PIOA_IFSR    (*(__I  uint32_t*)0xFFFFF428U) /**< \brief (PIOA) Glitch Input Filter Status Register */
  #define REG_PIOA_SODR    (*(__O  uint32_t*)0xFFFFF430U) /**< \brief (PIOA) Set Output Data Register */
  #define REG_PIOA_CODR    (*(__O  uint32_t*)0xFFFFF434U) /**< \brief (PIOA) Clear Output Data Register */
  #define REG_PIOA_ODSR    (*(__IO uint32_t*)0xFFFFF438U) /**< \brief (PIOA) Output Data Status Register */
  #define REG_PIOA_PDSR    (*(__I  uint32_t*)0xFFFFF43CU) /**< \brief (PIOA) Pin Data Status Register */
  #define REG_PIOA_IER     (*(__O  uint32_t*)0xFFFFF440U) /**< \brief (PIOA) Interrupt Enable Register */
  #define REG_PIOA_IDR     (*(__O  uint32_t*)0xFFFFF444U) /**< \brief (PIOA) Interrupt Disable Register */
  #define REG_PIOA_IMR     (*(__I  uint32_t*)0xFFFFF448U) /**< \brief (PIOA) Interrupt Mask Register */
  #define REG_PIOA_ISR     (*(__I  uint32_t*)0xFFFFF44CU) /**< \brief (PIOA) Interrupt Status Register */
  #define REG_PIOA_MDER    (*(__O  uint32_t*)0xFFFFF450U) /**< \brief (PIOA) Multi-driver Enable Register */
  #define REG_PIOA_MDDR    (*(__O  uint32_t*)0xFFFFF454U) /**< \brief (PIOA) Multi-driver Disable Register */
  #define REG_PIOA_MDSR    (*(__I  uint32_t*)0xFFFFF458U) /**< \brief (PIOA) Multi-driver Status Register */
  #define REG_PIOA_PUDR    (*(__O  uint32_t*)0xFFFFF460U) /**< \brief (PIOA) Pull-Up Disable Register */
  #define REG_PIOA_PUER    (*(__O  uint32_t*)0xFFFFF464U) /**< \brief (PIOA) Pull-Up Enable Register */
  #define REG_PIOA_PUSR    (*(__I  uint32_t*)0xFFFFF468U) /**< \brief (PIOA) Pad Pull-Up Status Register */
  #define REG_PIOA_ABCDSR  (*(__IO uint32_t*)0xFFFFF470U) /**< \brief (PIOA) Peripheral ABCD Select Register */
  #define REG_PIOA_IFSCDR  (*(__O  uint32_t*)0xFFFFF480U) /**< \brief (PIOA) Input Filter Slow Clock Disable Register */
  #define REG_PIOA_IFSCER  (*(__O  uint32_t*)0xFFFFF484U) /**< \brief (PIOA) Input Filter Slow Clock Enable Register */
  #define REG_PIOA_IFSCSR  (*(__I  uint32_t*)0xFFFFF488U) /**< \brief (PIOA) Input Filter Slow Clock Status Register */
  #define REG_PIOA_SCDR    (*(__IO uint32_t*)0xFFFFF48CU) /**< \brief (PIOA) Slow Clock Divider Debouncing Register */
  #define REG_PIOA_PPDDR   (*(__O  uint32_t*)0xFFFFF490U) /**< \brief (PIOA) Pad Pull-Down Disable Register */
  #define REG_PIOA_PPDER   (*(__O  uint32_t*)0xFFFFF494U) /**< \brief (PIOA) Pad Pull-Down Enable Register */
  #define REG_PIOA_PPDSR   (*(__I  uint32_t*)0xFFFFF498U) /**< \brief (PIOA) Pad Pull-Down Status Register */
  #define REG_PIOA_OWER    (*(__O  uint32_t*)0xFFFFF4A0U) /**< \brief (PIOA) Output Write Enable */
  #define REG_PIOA_OWDR    (*(__O  uint32_t*)0xFFFFF4A4U) /**< \brief (PIOA) Output Write Disable */
  #define REG_PIOA_OWSR    (*(__I  uint32_t*)0xFFFFF4A8U) /**< \brief (PIOA) Output Write Status Register */
  #define REG_PIOA_AIMER   (*(__O  uint32_t*)0xFFFFF4B0U) /**< \brief (PIOA) Additional Interrupt Modes Enable Register */
  #define REG_PIOA_AIMDR   (*(__O  uint32_t*)0xFFFFF4B4U) /**< \brief (PIOA) Additional Interrupt Modes Disable Register */
  #define REG_PIOA_AIMMR   (*(__I  uint32_t*)0xFFFFF4B8U) /**< \brief (PIOA) Additional Interrupt Modes Mask Register */
  #define REG_PIOA_ESR     (*(__O  uint32_t*)0xFFFFF4C0U) /**< \brief (PIOA) Edge Select Register */
  #define REG_PIOA_LSR     (*(__O  uint32_t*)0xFFFFF4C4U) /**< \brief (PIOA) Level Select Register */
  #define REG_PIOA_ELSR    (*(__I  uint32_t*)0xFFFFF4C8U) /**< \brief (PIOA) Edge/Level Status Register */
  #define REG_PIOA_FELLSR  (*(__O  uint32_t*)0xFFFFF4D0U) /**< \brief (PIOA) Falling Edge/Low-Level Select Register */
  #define REG_PIOA_REHLSR  (*(__O  uint32_t*)0xFFFFF4D4U) /**< \brief (PIOA) Rising Edge/High-Level Select Register */
  #define REG_PIOA_FRLHSR  (*(__I  uint32_t*)0xFFFFF4D8U) /**< \brief (PIOA) Fall/Rise - Low/High Status Register */
  #define REG_PIOA_WPMR    (*(__IO uint32_t*)0xFFFFF4E4U) /**< \brief (PIOA) Write Protection Mode Register */
  #define REG_PIOA_WPSR    (*(__I  uint32_t*)0xFFFFF4E8U) /**< \brief (PIOA) Write Protection Status Register */
  #define REG_PIOA_SCHMITT (*(__IO uint32_t*)0xFFFFF500U) /**< \brief (PIOA) Schmitt Trigger Register */
  #define REG_PIOA_SLEWR   (*(__IO uint32_t*)0xFFFFF510U) /**< \brief (PIOA) I/O Slewrate Control Register */
  #define REG_PIOA_DRIVER  (*(__IO uint32_t*)0xFFFFF518U) /**< \brief (PIOA) I/O Drive Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_PIOA_INSTANCE_ */
