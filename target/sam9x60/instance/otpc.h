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

#ifndef _SAM9X_OTPC_INSTANCE_
#define _SAM9X_OTPC_INSTANCE_

/* ========== Register definition for OTPC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_OTPC_CR                       (0xEFF00000U) /**< \brief (OTPC) Control Register */
  #define REG_OTPC_MR                       (0xEFF00004U) /**< \brief (OTPC) Mode Register */
  #define REG_OTPC_AR                       (0xEFF00008U) /**< \brief (OTPC) Address Register */
  #define REG_OTPC_SR                       (0xEFF0000CU) /**< \brief (OTPC) Status Register */
  #define REG_OTPC_IER                      (0xEFF00010U) /**< \brief (OTPC) Interrupt Enable Register */
  #define REG_OTPC_IDR                      (0xEFF00014U) /**< \brief (OTPC) Interrupt Disable Register */
  #define REG_OTPC_IMR                      (0xEFF00018U) /**< \brief (OTPC) Interrupt Mask Register */
  #define REG_OTPC_ISR                      (0xEFF0001CU) /**< \brief (OTPC) Interrupt Status Register */
  #define REG_OTPC_HR                       (0xEFF00020U) /**< \brief (OTPC) Header Register */
  #define REG_OTPC_DR                       (0xEFF00024U) /**< \brief (OTPC) Data Register */
  #define REG_OTPC_BAR                      (0xEFF00030U) /**< \brief (OTPC) Boot Addresses Register */
  #define REG_OTPC_CAR                      (0xEFF00034U) /**< \brief (OTPC) Custom Address Register */
  #define REG_OTPC_UHC0R                    (0xEFF00050U) /**< \brief (OTPC) User Hardware Configuration 0 Register */
  #define REG_OTPC_UHC1R                    (0xEFF00054U) /**< \brief (OTPC) User Hardware Configuration 1 Register */
  #define REG_OTPC_UID0R                    (0xEFF00060U) /**< \brief (OTPC) Product UID Register */
  #define REG_OTPC_UID1R                    (0xEFF00064U) /**< \brief (OTPC) Product UID Register */
  #define REG_OTPC_UID2R                    (0xEFF00068U) /**< \brief (OTPC) Product UID Register */
  #define REG_OTPC_UID3R                    (0xEFF0006CU) /**< \brief (OTPC) Product UID Register */
  #define REG_OTPC_HCSR                     (0xEFF00070U) /**< \brief (OTPC) Hardware Configuration Selection Register */
  #define REG_OTPC_HCDR                     (0xEFF00074U) /**< \brief (OTPC) Hardware Configuration Data Register */
  #define REG_OTPC_HS0R                     (0xEFF00080U) /**< \brief (OTPC) Hardware Security Register */
  #define REG_OTPC_HS1R                     (0xEFF00084U) /**< \brief (OTPC) Hardware Security Register */
  #define REG_OTPC_OMR                      (0xEFF00090U) /**< \brief (OTPC) OTP Mode Register */
  #define REG_OTPC_ODC0R                    (0xEFF000A0U) /**< \brief (OTPC) OTP DAP Configuration Register */
  #define REG_OTPC_ODC1R                    (0xEFF000A4U) /**< \brief (OTPC) OTP DAP Configuration Register */
  #define REG_OTPC_ODC2R                    (0xEFF000A8U) /**< \brief (OTPC) OTP DAP Configuration Register */
  #define REG_OTPC_ODC3R                    (0xEFF000ACU) /**< \brief (OTPC) OTP DAP Configuration Register */
  #define REG_OTPC_OPC0R                    (0xEFF000B0U) /**< \brief (OTPC) OTP PMC Configuration Register */
  #define REG_OTPC_OPC1R                    (0xEFF000B4U) /**< \brief (OTPC) OTP PMC Configuration Register */
  #define REG_OTPC_OPC2R                    (0xEFF000B8U) /**< \brief (OTPC) OTP PMC Configuration Register */
  #define REG_OTPC_OPC3R                    (0xEFF000BCU) /**< \brief (OTPC) OTP PMC Configuration Register */
  #define REG_OTPC_WPMR                     (0xEFF000E4U) /**< \brief (OTPC) Write Protection Mode Register */
  #define REG_OTPC_WPSR                     (0xEFF000E8U) /**< \brief (OTPC) Write Protection Status Register */
  #define REG_OTPC_VERSION                  (0xEFF000FCU) /**< \brief (OTPC) Version Register */
  #define REG_OTPC_RCR                      (0xEFF00100U) /**< \brief (OTPC) ROM Control Register */
  #define REG_OTPC_RMR                      (0xEFF00104U) /**< \brief (OTPC) ROM Mode Register */
  #define REG_OTPC_RAR                      (0xEFF00110U) /**< \brief (OTPC) ROM Address Register */
  #define REG_OTPC_RDR                      (0xEFF00114U) /**< \brief (OTPC) ROM Data Register */
  #define REG_OTPC_PCR                      (0xEFF00200U) /**< \brief (OTPC) Patch Control Register */
  #define REG_OTPC_PMR                      (0xEFF00204U) /**< \brief (OTPC) Patch Mode Register */
  #define REG_OTPC_PSR                      (0xEFF00208U) /**< \brief (OTPC) Patch Software Register */
  #define REG_OTPC_PAR                      (0xEFF00210U) /**< \brief (OTPC) Patch Address Register */
  #define REG_OTPC_PDR                      (0xEFF00214U) /**< \brief (OTPC) Patch Data Register */
  #define REG_OTPC_ACR                      (0xEFF00300U) /**< \brief (OTPC) A Control Register */
  #define REG_OTPC_AMR                      (0xEFF00304U) /**< \brief (OTPC) A Mode Register */
  #define REG_OTPC_AAR                      (0xEFF00308U) /**< \brief (OTPC) A Address Register */
  #define REG_OTPC_AHR                      (0xEFF00310U) /**< \brief (OTPC) A Header Register */
  #define REG_OTPC_ADR                      (0xEFF00314U) /**< \brief (OTPC) A Data Register */
#else
  #define REG_OTPC_CR      (*(__O  uint32_t*)0xEFF00000U) /**< \brief (OTPC) Control Register */
  #define REG_OTPC_MR      (*(__IO uint32_t*)0xEFF00004U) /**< \brief (OTPC) Mode Register */
  #define REG_OTPC_AR      (*(__IO uint32_t*)0xEFF00008U) /**< \brief (OTPC) Address Register */
  #define REG_OTPC_SR      (*(__I  uint32_t*)0xEFF0000CU) /**< \brief (OTPC) Status Register */
  #define REG_OTPC_IER     (*(__O  uint32_t*)0xEFF00010U) /**< \brief (OTPC) Interrupt Enable Register */
  #define REG_OTPC_IDR     (*(__O  uint32_t*)0xEFF00014U) /**< \brief (OTPC) Interrupt Disable Register */
  #define REG_OTPC_IMR     (*(__I  uint32_t*)0xEFF00018U) /**< \brief (OTPC) Interrupt Mask Register */
  #define REG_OTPC_ISR     (*(__I  uint32_t*)0xEFF0001CU) /**< \brief (OTPC) Interrupt Status Register */
  #define REG_OTPC_HR      (*(__IO uint32_t*)0xEFF00020U) /**< \brief (OTPC) Header Register */
  #define REG_OTPC_DR      (*(__IO uint32_t*)0xEFF00024U) /**< \brief (OTPC) Data Register */
  #define REG_OTPC_BAR     (*(__I  uint32_t*)0xEFF00030U) /**< \brief (OTPC) Boot Addresses Register */
  #define REG_OTPC_CAR     (*(__I  uint32_t*)0xEFF00034U) /**< \brief (OTPC) Custom Address Register */
  #define REG_OTPC_UHC0R   (*(__I  uint32_t*)0xEFF00050U) /**< \brief (OTPC) User Hardware Configuration 0 Register */
  #define REG_OTPC_UHC1R   (*(__I  uint32_t*)0xEFF00054U) /**< \brief (OTPC) User Hardware Configuration 1 Register */
  #define REG_OTPC_UID0R   (*(__I  uint32_t*)0xEFF00060U) /**< \brief (OTPC) Product UID Register */
  #define REG_OTPC_UID1R   (*(__I  uint32_t*)0xEFF00064U) /**< \brief (OTPC) Product UID Register */
  #define REG_OTPC_UID2R   (*(__I  uint32_t*)0xEFF00068U) /**< \brief (OTPC) Product UID Register */
  #define REG_OTPC_UID3R   (*(__I  uint32_t*)0xEFF0006CU) /**< \brief (OTPC) Product UID Register */
  #define REG_OTPC_HCSR    (*(__IO uint32_t*)0xEFF00070U) /**< \brief (OTPC) Hardware Configuration Selection Register */
  #define REG_OTPC_HCDR    (*(__I  uint32_t*)0xEFF00074U) /**< \brief (OTPC) Hardware Configuration Data Register */
  #define REG_OTPC_HS0R    (*(__I  uint32_t*)0xEFF00080U) /**< \brief (OTPC) Hardware Security Register */
  #define REG_OTPC_HS1R    (*(__I  uint32_t*)0xEFF00084U) /**< \brief (OTPC) Hardware Security Register */
  #define REG_OTPC_OMR     (*(__IO uint32_t*)0xEFF00090U) /**< \brief (OTPC) OTP Mode Register */
  #define REG_OTPC_ODC0R   (*(__IO uint32_t*)0xEFF000A0U) /**< \brief (OTPC) OTP DAP Configuration Register */
  #define REG_OTPC_ODC1R   (*(__IO uint32_t*)0xEFF000A4U) /**< \brief (OTPC) OTP DAP Configuration Register */
  #define REG_OTPC_ODC2R   (*(__IO uint32_t*)0xEFF000A8U) /**< \brief (OTPC) OTP DAP Configuration Register */
  #define REG_OTPC_ODC3R   (*(__IO uint32_t*)0xEFF000ACU) /**< \brief (OTPC) OTP DAP Configuration Register */
  #define REG_OTPC_OPC0R   (*(__IO uint32_t*)0xEFF000B0U) /**< \brief (OTPC) OTP PMC Configuration Register */
  #define REG_OTPC_OPC1R   (*(__IO uint32_t*)0xEFF000B4U) /**< \brief (OTPC) OTP PMC Configuration Register */
  #define REG_OTPC_OPC2R   (*(__IO uint32_t*)0xEFF000B8U) /**< \brief (OTPC) OTP PMC Configuration Register */
  #define REG_OTPC_OPC3R   (*(__IO uint32_t*)0xEFF000BCU) /**< \brief (OTPC) OTP PMC Configuration Register */
  #define REG_OTPC_WPMR    (*(__IO uint32_t*)0xEFF000E4U) /**< \brief (OTPC) Write Protection Mode Register */
  #define REG_OTPC_WPSR    (*(__I  uint32_t*)0xEFF000E8U) /**< \brief (OTPC) Write Protection Status Register */
  #define REG_OTPC_VERSION (*(__I  uint32_t*)0xEFF000FCU) /**< \brief (OTPC) Version Register */
  #define REG_OTPC_RCR     (*(__O  uint32_t*)0xEFF00100U) /**< \brief (OTPC) ROM Control Register */
  #define REG_OTPC_RMR     (*(__IO uint32_t*)0xEFF00104U) /**< \brief (OTPC) ROM Mode Register */
  #define REG_OTPC_RAR     (*(__IO uint32_t*)0xEFF00110U) /**< \brief (OTPC) ROM Address Register */
  #define REG_OTPC_RDR     (*(__IO uint32_t*)0xEFF00114U) /**< \brief (OTPC) ROM Data Register */
  #define REG_OTPC_PCR     (*(__O  uint32_t*)0xEFF00200U) /**< \brief (OTPC) Patch Control Register */
  #define REG_OTPC_PMR     (*(__IO uint32_t*)0xEFF00204U) /**< \brief (OTPC) Patch Mode Register */
  #define REG_OTPC_PSR     (*(__IO uint32_t*)0xEFF00208U) /**< \brief (OTPC) Patch Software Register */
  #define REG_OTPC_PAR     (*(__IO uint32_t*)0xEFF00210U) /**< \brief (OTPC) Patch Address Register */
  #define REG_OTPC_PDR     (*(__IO uint32_t*)0xEFF00214U) /**< \brief (OTPC) Patch Data Register */
  #define REG_OTPC_ACR     (*(__O  uint32_t*)0xEFF00300U) /**< \brief (OTPC) A Control Register */
  #define REG_OTPC_AMR     (*(__IO uint32_t*)0xEFF00304U) /**< \brief (OTPC) A Mode Register */
  #define REG_OTPC_AAR     (*(__IO uint32_t*)0xEFF00308U) /**< \brief (OTPC) A Address Register */
  #define REG_OTPC_AHR     (*(__IO uint32_t*)0xEFF00310U) /**< \brief (OTPC) A Header Register */
  #define REG_OTPC_ADR     (*(__IO uint32_t*)0xEFF00314U) /**< \brief (OTPC) A Data Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_OTPC_INSTANCE_ */
