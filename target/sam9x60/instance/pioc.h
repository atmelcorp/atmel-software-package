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

#ifndef _SAM9X_PIOC_INSTANCE_
#define _SAM9X_PIOC_INSTANCE_

/* ========== Register definition for PIOC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_PIOC_PER                      (0xFFFFF800U) /**< \brief (PIOC) PIO Enable Register */
  #define REG_PIOC_PDR                      (0xFFFFF804U) /**< \brief (PIOC) PIO Disable Register */
  #define REG_PIOC_PSR                      (0xFFFFF808U) /**< \brief (PIOC) PIO Status Register */
  #define REG_PIOC_OER                      (0xFFFFF810U) /**< \brief (PIOC) Output Enable Register */
  #define REG_PIOC_ODR                      (0xFFFFF814U) /**< \brief (PIOC) Output Disable Register */
  #define REG_PIOC_OSR                      (0xFFFFF818U) /**< \brief (PIOC) Output Status Register */
  #define REG_PIOC_IFER                     (0xFFFFF820U) /**< \brief (PIOC) Glitch Input Filter Enable Register */
  #define REG_PIOC_IFDR                     (0xFFFFF824U) /**< \brief (PIOC) Glitch Input Filter Disable Register */
  #define REG_PIOC_IFSR                     (0xFFFFF828U) /**< \brief (PIOC) Glitch Input Filter Status Register */
  #define REG_PIOC_SODR                     (0xFFFFF830U) /**< \brief (PIOC) Set Output Data Register */
  #define REG_PIOC_CODR                     (0xFFFFF834U) /**< \brief (PIOC) Clear Output Data Register */
  #define REG_PIOC_ODSR                     (0xFFFFF838U) /**< \brief (PIOC) Output Data Status Register */
  #define REG_PIOC_PDSR                     (0xFFFFF83CU) /**< \brief (PIOC) Pin Data Status Register */
  #define REG_PIOC_IER                      (0xFFFFF840U) /**< \brief (PIOC) Interrupt Enable Register */
  #define REG_PIOC_IDR                      (0xFFFFF844U) /**< \brief (PIOC) Interrupt Disable Register */
  #define REG_PIOC_IMR                      (0xFFFFF848U) /**< \brief (PIOC) Interrupt Mask Register */
  #define REG_PIOC_ISR                      (0xFFFFF84CU) /**< \brief (PIOC) Interrupt Status Register */
  #define REG_PIOC_MDER                     (0xFFFFF850U) /**< \brief (PIOC) Multi-driver Enable Register */
  #define REG_PIOC_MDDR                     (0xFFFFF854U) /**< \brief (PIOC) Multi-driver Disable Register */
  #define REG_PIOC_MDSR                     (0xFFFFF858U) /**< \brief (PIOC) Multi-driver Status Register */
  #define REG_PIOC_PUDR                     (0xFFFFF860U) /**< \brief (PIOC) Pull-Up Disable Register */
  #define REG_PIOC_PUER                     (0xFFFFF864U) /**< \brief (PIOC) Pull-Up Enable Register */
  #define REG_PIOC_PUSR                     (0xFFFFF868U) /**< \brief (PIOC) Pad Pull-Up Status Register */
  #define REG_PIOC_ABCDSR                   (0xFFFFF870U) /**< \brief (PIOC) Peripheral ABCD Select Register */
  #define REG_PIOC_IFSCDR                   (0xFFFFF880U) /**< \brief (PIOC) Input Filter Slow Clock Disable Register */
  #define REG_PIOC_IFSCER                   (0xFFFFF884U) /**< \brief (PIOC) Input Filter Slow Clock Enable Register */
  #define REG_PIOC_IFSCSR                   (0xFFFFF888U) /**< \brief (PIOC) Input Filter Slow Clock Status Register */
  #define REG_PIOC_SCDR                     (0xFFFFF88CU) /**< \brief (PIOC) Slow Clock Divider Debouncing Register */
  #define REG_PIOC_PPDDR                    (0xFFFFF890U) /**< \brief (PIOC) Pad Pull-Down Disable Register */
  #define REG_PIOC_PPDER                    (0xFFFFF894U) /**< \brief (PIOC) Pad Pull-Down Enable Register */
  #define REG_PIOC_PPDSR                    (0xFFFFF898U) /**< \brief (PIOC) Pad Pull-Down Status Register */
  #define REG_PIOC_OWER                     (0xFFFFF8A0U) /**< \brief (PIOC) Output Write Enable */
  #define REG_PIOC_OWDR                     (0xFFFFF8A4U) /**< \brief (PIOC) Output Write Disable */
  #define REG_PIOC_OWSR                     (0xFFFFF8A8U) /**< \brief (PIOC) Output Write Status Register */
  #define REG_PIOC_AIMER                    (0xFFFFF8B0U) /**< \brief (PIOC) Additional Interrupt Modes Enable Register */
  #define REG_PIOC_AIMDR                    (0xFFFFF8B4U) /**< \brief (PIOC) Additional Interrupt Modes Disable Register */
  #define REG_PIOC_AIMMR                    (0xFFFFF8B8U) /**< \brief (PIOC) Additional Interrupt Modes Mask Register */
  #define REG_PIOC_ESR                      (0xFFFFF8C0U) /**< \brief (PIOC) Edge Select Register */
  #define REG_PIOC_LSR                      (0xFFFFF8C4U) /**< \brief (PIOC) Level Select Register */
  #define REG_PIOC_ELSR                     (0xFFFFF8C8U) /**< \brief (PIOC) Edge/Level Status Register */
  #define REG_PIOC_FELLSR                   (0xFFFFF8D0U) /**< \brief (PIOC) Falling Edge/Low-Level Select Register */
  #define REG_PIOC_REHLSR                   (0xFFFFF8D4U) /**< \brief (PIOC) Rising Edge/High-Level Select Register */
  #define REG_PIOC_FRLHSR                   (0xFFFFF8D8U) /**< \brief (PIOC) Fall/Rise - Low/High Status Register */
  #define REG_PIOC_WPMR                     (0xFFFFF8E4U) /**< \brief (PIOC) Write Protection Mode Register */
  #define REG_PIOC_WPSR                     (0xFFFFF8E8U) /**< \brief (PIOC) Write Protection Status Register */
  #define REG_PIOC_SCHMITT                  (0xFFFFF900U) /**< \brief (PIOC) Schmitt Trigger Register */
  #define REG_PIOC_SLEWR                    (0xFFFFF910U) /**< \brief (PIOC) I/O Slewrate Control Register */
  #define REG_PIOC_DRIVER                   (0xFFFFF918U) /**< \brief (PIOC) I/O Drive Register */
#else
  #define REG_PIOC_PER     (*(__O  uint32_t*)0xFFFFF800U) /**< \brief (PIOC) PIO Enable Register */
  #define REG_PIOC_PDR     (*(__O  uint32_t*)0xFFFFF804U) /**< \brief (PIOC) PIO Disable Register */
  #define REG_PIOC_PSR     (*(__I  uint32_t*)0xFFFFF808U) /**< \brief (PIOC) PIO Status Register */
  #define REG_PIOC_OER     (*(__O  uint32_t*)0xFFFFF810U) /**< \brief (PIOC) Output Enable Register */
  #define REG_PIOC_ODR     (*(__O  uint32_t*)0xFFFFF814U) /**< \brief (PIOC) Output Disable Register */
  #define REG_PIOC_OSR     (*(__I  uint32_t*)0xFFFFF818U) /**< \brief (PIOC) Output Status Register */
  #define REG_PIOC_IFER    (*(__O  uint32_t*)0xFFFFF820U) /**< \brief (PIOC) Glitch Input Filter Enable Register */
  #define REG_PIOC_IFDR    (*(__O  uint32_t*)0xFFFFF824U) /**< \brief (PIOC) Glitch Input Filter Disable Register */
  #define REG_PIOC_IFSR    (*(__I  uint32_t*)0xFFFFF828U) /**< \brief (PIOC) Glitch Input Filter Status Register */
  #define REG_PIOC_SODR    (*(__O  uint32_t*)0xFFFFF830U) /**< \brief (PIOC) Set Output Data Register */
  #define REG_PIOC_CODR    (*(__O  uint32_t*)0xFFFFF834U) /**< \brief (PIOC) Clear Output Data Register */
  #define REG_PIOC_ODSR    (*(__IO uint32_t*)0xFFFFF838U) /**< \brief (PIOC) Output Data Status Register */
  #define REG_PIOC_PDSR    (*(__I  uint32_t*)0xFFFFF83CU) /**< \brief (PIOC) Pin Data Status Register */
  #define REG_PIOC_IER     (*(__O  uint32_t*)0xFFFFF840U) /**< \brief (PIOC) Interrupt Enable Register */
  #define REG_PIOC_IDR     (*(__O  uint32_t*)0xFFFFF844U) /**< \brief (PIOC) Interrupt Disable Register */
  #define REG_PIOC_IMR     (*(__I  uint32_t*)0xFFFFF848U) /**< \brief (PIOC) Interrupt Mask Register */
  #define REG_PIOC_ISR     (*(__I  uint32_t*)0xFFFFF84CU) /**< \brief (PIOC) Interrupt Status Register */
  #define REG_PIOC_MDER    (*(__O  uint32_t*)0xFFFFF850U) /**< \brief (PIOC) Multi-driver Enable Register */
  #define REG_PIOC_MDDR    (*(__O  uint32_t*)0xFFFFF854U) /**< \brief (PIOC) Multi-driver Disable Register */
  #define REG_PIOC_MDSR    (*(__I  uint32_t*)0xFFFFF858U) /**< \brief (PIOC) Multi-driver Status Register */
  #define REG_PIOC_PUDR    (*(__O  uint32_t*)0xFFFFF860U) /**< \brief (PIOC) Pull-Up Disable Register */
  #define REG_PIOC_PUER    (*(__O  uint32_t*)0xFFFFF864U) /**< \brief (PIOC) Pull-Up Enable Register */
  #define REG_PIOC_PUSR    (*(__I  uint32_t*)0xFFFFF868U) /**< \brief (PIOC) Pad Pull-Up Status Register */
  #define REG_PIOC_ABCDSR  (*(__IO uint32_t*)0xFFFFF870U) /**< \brief (PIOC) Peripheral ABCD Select Register */
  #define REG_PIOC_IFSCDR  (*(__O  uint32_t*)0xFFFFF880U) /**< \brief (PIOC) Input Filter Slow Clock Disable Register */
  #define REG_PIOC_IFSCER  (*(__O  uint32_t*)0xFFFFF884U) /**< \brief (PIOC) Input Filter Slow Clock Enable Register */
  #define REG_PIOC_IFSCSR  (*(__I  uint32_t*)0xFFFFF888U) /**< \brief (PIOC) Input Filter Slow Clock Status Register */
  #define REG_PIOC_SCDR    (*(__IO uint32_t*)0xFFFFF88CU) /**< \brief (PIOC) Slow Clock Divider Debouncing Register */
  #define REG_PIOC_PPDDR   (*(__O  uint32_t*)0xFFFFF890U) /**< \brief (PIOC) Pad Pull-Down Disable Register */
  #define REG_PIOC_PPDER   (*(__O  uint32_t*)0xFFFFF894U) /**< \brief (PIOC) Pad Pull-Down Enable Register */
  #define REG_PIOC_PPDSR   (*(__I  uint32_t*)0xFFFFF898U) /**< \brief (PIOC) Pad Pull-Down Status Register */
  #define REG_PIOC_OWER    (*(__O  uint32_t*)0xFFFFF8A0U) /**< \brief (PIOC) Output Write Enable */
  #define REG_PIOC_OWDR    (*(__O  uint32_t*)0xFFFFF8A4U) /**< \brief (PIOC) Output Write Disable */
  #define REG_PIOC_OWSR    (*(__I  uint32_t*)0xFFFFF8A8U) /**< \brief (PIOC) Output Write Status Register */
  #define REG_PIOC_AIMER   (*(__O  uint32_t*)0xFFFFF8B0U) /**< \brief (PIOC) Additional Interrupt Modes Enable Register */
  #define REG_PIOC_AIMDR   (*(__O  uint32_t*)0xFFFFF8B4U) /**< \brief (PIOC) Additional Interrupt Modes Disable Register */
  #define REG_PIOC_AIMMR   (*(__I  uint32_t*)0xFFFFF8B8U) /**< \brief (PIOC) Additional Interrupt Modes Mask Register */
  #define REG_PIOC_ESR     (*(__O  uint32_t*)0xFFFFF8C0U) /**< \brief (PIOC) Edge Select Register */
  #define REG_PIOC_LSR     (*(__O  uint32_t*)0xFFFFF8C4U) /**< \brief (PIOC) Level Select Register */
  #define REG_PIOC_ELSR    (*(__I  uint32_t*)0xFFFFF8C8U) /**< \brief (PIOC) Edge/Level Status Register */
  #define REG_PIOC_FELLSR  (*(__O  uint32_t*)0xFFFFF8D0U) /**< \brief (PIOC) Falling Edge/Low-Level Select Register */
  #define REG_PIOC_REHLSR  (*(__O  uint32_t*)0xFFFFF8D4U) /**< \brief (PIOC) Rising Edge/High-Level Select Register */
  #define REG_PIOC_FRLHSR  (*(__I  uint32_t*)0xFFFFF8D8U) /**< \brief (PIOC) Fall/Rise - Low/High Status Register */
  #define REG_PIOC_WPMR    (*(__IO uint32_t*)0xFFFFF8E4U) /**< \brief (PIOC) Write Protection Mode Register */
  #define REG_PIOC_WPSR    (*(__I  uint32_t*)0xFFFFF8E8U) /**< \brief (PIOC) Write Protection Status Register */
  #define REG_PIOC_SCHMITT (*(__IO uint32_t*)0xFFFFF900U) /**< \brief (PIOC) Schmitt Trigger Register */
  #define REG_PIOC_SLEWR   (*(__IO uint32_t*)0xFFFFF910U) /**< \brief (PIOC) I/O Slewrate Control Register */
  #define REG_PIOC_DRIVER  (*(__IO uint32_t*)0xFFFFF918U) /**< \brief (PIOC) I/O Drive Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_PIOC_INSTANCE_ */
