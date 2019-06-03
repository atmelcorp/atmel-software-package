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

#ifndef _SAM9X_CAN0_INSTANCE_
#define _SAM9X_CAN0_INSTANCE_

/* ========== Register definition for CAN0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_CAN0_MR                       (0xF8000000U) /**< \brief (CAN0) Mode Register */
  #define REG_CAN0_IER                      (0xF8000004U) /**< \brief (CAN0) Interrupt Enable Register */
  #define REG_CAN0_IDR                      (0xF8000008U) /**< \brief (CAN0) Interrupt Disable Register */
  #define REG_CAN0_IMR                      (0xF800000CU) /**< \brief (CAN0) Interrupt Mask Register */
  #define REG_CAN0_SR                       (0xF8000010U) /**< \brief (CAN0) Status Register */
  #define REG_CAN0_BR                       (0xF8000014U) /**< \brief (CAN0) Baudrate Register */
  #define REG_CAN0_TIM                      (0xF8000018U) /**< \brief (CAN0) Timer Register */
  #define REG_CAN0_TIMESTP                  (0xF800001CU) /**< \brief (CAN0) Timestamp Register */
  #define REG_CAN0_ECR                      (0xF8000020U) /**< \brief (CAN0) Error Counter Register */
  #define REG_CAN0_TCR                      (0xF8000024U) /**< \brief (CAN0) Transfer Command Register */
  #define REG_CAN0_ACR                      (0xF8000028U) /**< \brief (CAN0) Abort Command Register */
  #define REG_CAN0_WPMR                     (0xF80000E4U) /**< \brief (CAN0) Write Protection Mode Register */
  #define REG_CAN0_WPSR                     (0xF80000E8U) /**< \brief (CAN0) Write Protection Status Register */
  #define REG_CAN0_MMR0                     (0xF8000200U) /**< \brief (CAN0) Mailbox Mode Register (MB = 0) */
  #define REG_CAN0_MAM0                     (0xF8000204U) /**< \brief (CAN0) Mailbox Acceptance Mask Register (MB = 0) */
  #define REG_CAN0_MID0                     (0xF8000208U) /**< \brief (CAN0) Mailbox ID Register (MB = 0) */
  #define REG_CAN0_MFID0                    (0xF800020CU) /**< \brief (CAN0) Mailbox Family ID Register (MB = 0) */
  #define REG_CAN0_MSR0                     (0xF8000210U) /**< \brief (CAN0) Mailbox Status Register (MB = 0) */
  #define REG_CAN0_MDL0                     (0xF8000214U) /**< \brief (CAN0) Mailbox Data Low Register (MB = 0) */
  #define REG_CAN0_MDH0                     (0xF8000218U) /**< \brief (CAN0) Mailbox Data High Register (MB = 0) */
  #define REG_CAN0_MCR0                     (0xF800021CU) /**< \brief (CAN0) Mailbox Control Register (MB = 0) */
  #define REG_CAN0_MMR1                     (0xF8000220U) /**< \brief (CAN0) Mailbox Mode Register (MB = 1) */
  #define REG_CAN0_MAM1                     (0xF8000224U) /**< \brief (CAN0) Mailbox Acceptance Mask Register (MB = 1) */
  #define REG_CAN0_MID1                     (0xF8000228U) /**< \brief (CAN0) Mailbox ID Register (MB = 1) */
  #define REG_CAN0_MFID1                    (0xF800022CU) /**< \brief (CAN0) Mailbox Family ID Register (MB = 1) */
  #define REG_CAN0_MSR1                     (0xF8000230U) /**< \brief (CAN0) Mailbox Status Register (MB = 1) */
  #define REG_CAN0_MDL1                     (0xF8000234U) /**< \brief (CAN0) Mailbox Data Low Register (MB = 1) */
  #define REG_CAN0_MDH1                     (0xF8000238U) /**< \brief (CAN0) Mailbox Data High Register (MB = 1) */
  #define REG_CAN0_MCR1                     (0xF800023CU) /**< \brief (CAN0) Mailbox Control Register (MB = 1) */
  #define REG_CAN0_MMR2                     (0xF8000240U) /**< \brief (CAN0) Mailbox Mode Register (MB = 2) */
  #define REG_CAN0_MAM2                     (0xF8000244U) /**< \brief (CAN0) Mailbox Acceptance Mask Register (MB = 2) */
  #define REG_CAN0_MID2                     (0xF8000248U) /**< \brief (CAN0) Mailbox ID Register (MB = 2) */
  #define REG_CAN0_MFID2                    (0xF800024CU) /**< \brief (CAN0) Mailbox Family ID Register (MB = 2) */
  #define REG_CAN0_MSR2                     (0xF8000250U) /**< \brief (CAN0) Mailbox Status Register (MB = 2) */
  #define REG_CAN0_MDL2                     (0xF8000254U) /**< \brief (CAN0) Mailbox Data Low Register (MB = 2) */
  #define REG_CAN0_MDH2                     (0xF8000258U) /**< \brief (CAN0) Mailbox Data High Register (MB = 2) */
  #define REG_CAN0_MCR2                     (0xF800025CU) /**< \brief (CAN0) Mailbox Control Register (MB = 2) */
  #define REG_CAN0_MMR3                     (0xF8000260U) /**< \brief (CAN0) Mailbox Mode Register (MB = 3) */
  #define REG_CAN0_MAM3                     (0xF8000264U) /**< \brief (CAN0) Mailbox Acceptance Mask Register (MB = 3) */
  #define REG_CAN0_MID3                     (0xF8000268U) /**< \brief (CAN0) Mailbox ID Register (MB = 3) */
  #define REG_CAN0_MFID3                    (0xF800026CU) /**< \brief (CAN0) Mailbox Family ID Register (MB = 3) */
  #define REG_CAN0_MSR3                     (0xF8000270U) /**< \brief (CAN0) Mailbox Status Register (MB = 3) */
  #define REG_CAN0_MDL3                     (0xF8000274U) /**< \brief (CAN0) Mailbox Data Low Register (MB = 3) */
  #define REG_CAN0_MDH3                     (0xF8000278U) /**< \brief (CAN0) Mailbox Data High Register (MB = 3) */
  #define REG_CAN0_MCR3                     (0xF800027CU) /**< \brief (CAN0) Mailbox Control Register (MB = 3) */
  #define REG_CAN0_MMR4                     (0xF8000280U) /**< \brief (CAN0) Mailbox Mode Register (MB = 4) */
  #define REG_CAN0_MAM4                     (0xF8000284U) /**< \brief (CAN0) Mailbox Acceptance Mask Register (MB = 4) */
  #define REG_CAN0_MID4                     (0xF8000288U) /**< \brief (CAN0) Mailbox ID Register (MB = 4) */
  #define REG_CAN0_MFID4                    (0xF800028CU) /**< \brief (CAN0) Mailbox Family ID Register (MB = 4) */
  #define REG_CAN0_MSR4                     (0xF8000290U) /**< \brief (CAN0) Mailbox Status Register (MB = 4) */
  #define REG_CAN0_MDL4                     (0xF8000294U) /**< \brief (CAN0) Mailbox Data Low Register (MB = 4) */
  #define REG_CAN0_MDH4                     (0xF8000298U) /**< \brief (CAN0) Mailbox Data High Register (MB = 4) */
  #define REG_CAN0_MCR4                     (0xF800029CU) /**< \brief (CAN0) Mailbox Control Register (MB = 4) */
  #define REG_CAN0_MMR5                     (0xF80002A0U) /**< \brief (CAN0) Mailbox Mode Register (MB = 5) */
  #define REG_CAN0_MAM5                     (0xF80002A4U) /**< \brief (CAN0) Mailbox Acceptance Mask Register (MB = 5) */
  #define REG_CAN0_MID5                     (0xF80002A8U) /**< \brief (CAN0) Mailbox ID Register (MB = 5) */
  #define REG_CAN0_MFID5                    (0xF80002ACU) /**< \brief (CAN0) Mailbox Family ID Register (MB = 5) */
  #define REG_CAN0_MSR5                     (0xF80002B0U) /**< \brief (CAN0) Mailbox Status Register (MB = 5) */
  #define REG_CAN0_MDL5                     (0xF80002B4U) /**< \brief (CAN0) Mailbox Data Low Register (MB = 5) */
  #define REG_CAN0_MDH5                     (0xF80002B8U) /**< \brief (CAN0) Mailbox Data High Register (MB = 5) */
  #define REG_CAN0_MCR5                     (0xF80002BCU) /**< \brief (CAN0) Mailbox Control Register (MB = 5) */
  #define REG_CAN0_MMR6                     (0xF80002C0U) /**< \brief (CAN0) Mailbox Mode Register (MB = 6) */
  #define REG_CAN0_MAM6                     (0xF80002C4U) /**< \brief (CAN0) Mailbox Acceptance Mask Register (MB = 6) */
  #define REG_CAN0_MID6                     (0xF80002C8U) /**< \brief (CAN0) Mailbox ID Register (MB = 6) */
  #define REG_CAN0_MFID6                    (0xF80002CCU) /**< \brief (CAN0) Mailbox Family ID Register (MB = 6) */
  #define REG_CAN0_MSR6                     (0xF80002D0U) /**< \brief (CAN0) Mailbox Status Register (MB = 6) */
  #define REG_CAN0_MDL6                     (0xF80002D4U) /**< \brief (CAN0) Mailbox Data Low Register (MB = 6) */
  #define REG_CAN0_MDH6                     (0xF80002D8U) /**< \brief (CAN0) Mailbox Data High Register (MB = 6) */
  #define REG_CAN0_MCR6                     (0xF80002DCU) /**< \brief (CAN0) Mailbox Control Register (MB = 6) */
  #define REG_CAN0_MMR7                     (0xF80002E0U) /**< \brief (CAN0) Mailbox Mode Register (MB = 7) */
  #define REG_CAN0_MAM7                     (0xF80002E4U) /**< \brief (CAN0) Mailbox Acceptance Mask Register (MB = 7) */
  #define REG_CAN0_MID7                     (0xF80002E8U) /**< \brief (CAN0) Mailbox ID Register (MB = 7) */
  #define REG_CAN0_MFID7                    (0xF80002ECU) /**< \brief (CAN0) Mailbox Family ID Register (MB = 7) */
  #define REG_CAN0_MSR7                     (0xF80002F0U) /**< \brief (CAN0) Mailbox Status Register (MB = 7) */
  #define REG_CAN0_MDL7                     (0xF80002F4U) /**< \brief (CAN0) Mailbox Data Low Register (MB = 7) */
  #define REG_CAN0_MDH7                     (0xF80002F8U) /**< \brief (CAN0) Mailbox Data High Register (MB = 7) */
  #define REG_CAN0_MCR7                     (0xF80002FCU) /**< \brief (CAN0) Mailbox Control Register (MB = 7) */
#else
  #define REG_CAN0_MR      (*(__IO uint32_t*)0xF8000000U) /**< \brief (CAN0) Mode Register */
  #define REG_CAN0_IER     (*(__O  uint32_t*)0xF8000004U) /**< \brief (CAN0) Interrupt Enable Register */
  #define REG_CAN0_IDR     (*(__O  uint32_t*)0xF8000008U) /**< \brief (CAN0) Interrupt Disable Register */
  #define REG_CAN0_IMR     (*(__I  uint32_t*)0xF800000CU) /**< \brief (CAN0) Interrupt Mask Register */
  #define REG_CAN0_SR      (*(__I  uint32_t*)0xF8000010U) /**< \brief (CAN0) Status Register */
  #define REG_CAN0_BR      (*(__IO uint32_t*)0xF8000014U) /**< \brief (CAN0) Baudrate Register */
  #define REG_CAN0_TIM     (*(__I  uint32_t*)0xF8000018U) /**< \brief (CAN0) Timer Register */
  #define REG_CAN0_TIMESTP (*(__I  uint32_t*)0xF800001CU) /**< \brief (CAN0) Timestamp Register */
  #define REG_CAN0_ECR     (*(__I  uint32_t*)0xF8000020U) /**< \brief (CAN0) Error Counter Register */
  #define REG_CAN0_TCR     (*(__O  uint32_t*)0xF8000024U) /**< \brief (CAN0) Transfer Command Register */
  #define REG_CAN0_ACR     (*(__O  uint32_t*)0xF8000028U) /**< \brief (CAN0) Abort Command Register */
  #define REG_CAN0_WPMR    (*(__IO uint32_t*)0xF80000E4U) /**< \brief (CAN0) Write Protection Mode Register */
  #define REG_CAN0_WPSR    (*(__I  uint32_t*)0xF80000E8U) /**< \brief (CAN0) Write Protection Status Register */
  #define REG_CAN0_MMR0    (*(__IO uint32_t*)0xF8000200U) /**< \brief (CAN0) Mailbox Mode Register (MB = 0) */
  #define REG_CAN0_MAM0    (*(__IO uint32_t*)0xF8000204U) /**< \brief (CAN0) Mailbox Acceptance Mask Register (MB = 0) */
  #define REG_CAN0_MID0    (*(__IO uint32_t*)0xF8000208U) /**< \brief (CAN0) Mailbox ID Register (MB = 0) */
  #define REG_CAN0_MFID0   (*(__I  uint32_t*)0xF800020CU) /**< \brief (CAN0) Mailbox Family ID Register (MB = 0) */
  #define REG_CAN0_MSR0    (*(__I  uint32_t*)0xF8000210U) /**< \brief (CAN0) Mailbox Status Register (MB = 0) */
  #define REG_CAN0_MDL0    (*(__IO uint32_t*)0xF8000214U) /**< \brief (CAN0) Mailbox Data Low Register (MB = 0) */
  #define REG_CAN0_MDH0    (*(__IO uint32_t*)0xF8000218U) /**< \brief (CAN0) Mailbox Data High Register (MB = 0) */
  #define REG_CAN0_MCR0    (*(__O  uint32_t*)0xF800021CU) /**< \brief (CAN0) Mailbox Control Register (MB = 0) */
  #define REG_CAN0_MMR1    (*(__IO uint32_t*)0xF8000220U) /**< \brief (CAN0) Mailbox Mode Register (MB = 1) */
  #define REG_CAN0_MAM1    (*(__IO uint32_t*)0xF8000224U) /**< \brief (CAN0) Mailbox Acceptance Mask Register (MB = 1) */
  #define REG_CAN0_MID1    (*(__IO uint32_t*)0xF8000228U) /**< \brief (CAN0) Mailbox ID Register (MB = 1) */
  #define REG_CAN0_MFID1   (*(__I  uint32_t*)0xF800022CU) /**< \brief (CAN0) Mailbox Family ID Register (MB = 1) */
  #define REG_CAN0_MSR1    (*(__I  uint32_t*)0xF8000230U) /**< \brief (CAN0) Mailbox Status Register (MB = 1) */
  #define REG_CAN0_MDL1    (*(__IO uint32_t*)0xF8000234U) /**< \brief (CAN0) Mailbox Data Low Register (MB = 1) */
  #define REG_CAN0_MDH1    (*(__IO uint32_t*)0xF8000238U) /**< \brief (CAN0) Mailbox Data High Register (MB = 1) */
  #define REG_CAN0_MCR1    (*(__O  uint32_t*)0xF800023CU) /**< \brief (CAN0) Mailbox Control Register (MB = 1) */
  #define REG_CAN0_MMR2    (*(__IO uint32_t*)0xF8000240U) /**< \brief (CAN0) Mailbox Mode Register (MB = 2) */
  #define REG_CAN0_MAM2    (*(__IO uint32_t*)0xF8000244U) /**< \brief (CAN0) Mailbox Acceptance Mask Register (MB = 2) */
  #define REG_CAN0_MID2    (*(__IO uint32_t*)0xF8000248U) /**< \brief (CAN0) Mailbox ID Register (MB = 2) */
  #define REG_CAN0_MFID2   (*(__I  uint32_t*)0xF800024CU) /**< \brief (CAN0) Mailbox Family ID Register (MB = 2) */
  #define REG_CAN0_MSR2    (*(__I  uint32_t*)0xF8000250U) /**< \brief (CAN0) Mailbox Status Register (MB = 2) */
  #define REG_CAN0_MDL2    (*(__IO uint32_t*)0xF8000254U) /**< \brief (CAN0) Mailbox Data Low Register (MB = 2) */
  #define REG_CAN0_MDH2    (*(__IO uint32_t*)0xF8000258U) /**< \brief (CAN0) Mailbox Data High Register (MB = 2) */
  #define REG_CAN0_MCR2    (*(__O  uint32_t*)0xF800025CU) /**< \brief (CAN0) Mailbox Control Register (MB = 2) */
  #define REG_CAN0_MMR3    (*(__IO uint32_t*)0xF8000260U) /**< \brief (CAN0) Mailbox Mode Register (MB = 3) */
  #define REG_CAN0_MAM3    (*(__IO uint32_t*)0xF8000264U) /**< \brief (CAN0) Mailbox Acceptance Mask Register (MB = 3) */
  #define REG_CAN0_MID3    (*(__IO uint32_t*)0xF8000268U) /**< \brief (CAN0) Mailbox ID Register (MB = 3) */
  #define REG_CAN0_MFID3   (*(__I  uint32_t*)0xF800026CU) /**< \brief (CAN0) Mailbox Family ID Register (MB = 3) */
  #define REG_CAN0_MSR3    (*(__I  uint32_t*)0xF8000270U) /**< \brief (CAN0) Mailbox Status Register (MB = 3) */
  #define REG_CAN0_MDL3    (*(__IO uint32_t*)0xF8000274U) /**< \brief (CAN0) Mailbox Data Low Register (MB = 3) */
  #define REG_CAN0_MDH3    (*(__IO uint32_t*)0xF8000278U) /**< \brief (CAN0) Mailbox Data High Register (MB = 3) */
  #define REG_CAN0_MCR3    (*(__O  uint32_t*)0xF800027CU) /**< \brief (CAN0) Mailbox Control Register (MB = 3) */
  #define REG_CAN0_MMR4    (*(__IO uint32_t*)0xF8000280U) /**< \brief (CAN0) Mailbox Mode Register (MB = 4) */
  #define REG_CAN0_MAM4    (*(__IO uint32_t*)0xF8000284U) /**< \brief (CAN0) Mailbox Acceptance Mask Register (MB = 4) */
  #define REG_CAN0_MID4    (*(__IO uint32_t*)0xF8000288U) /**< \brief (CAN0) Mailbox ID Register (MB = 4) */
  #define REG_CAN0_MFID4   (*(__I  uint32_t*)0xF800028CU) /**< \brief (CAN0) Mailbox Family ID Register (MB = 4) */
  #define REG_CAN0_MSR4    (*(__I  uint32_t*)0xF8000290U) /**< \brief (CAN0) Mailbox Status Register (MB = 4) */
  #define REG_CAN0_MDL4    (*(__IO uint32_t*)0xF8000294U) /**< \brief (CAN0) Mailbox Data Low Register (MB = 4) */
  #define REG_CAN0_MDH4    (*(__IO uint32_t*)0xF8000298U) /**< \brief (CAN0) Mailbox Data High Register (MB = 4) */
  #define REG_CAN0_MCR4    (*(__O  uint32_t*)0xF800029CU) /**< \brief (CAN0) Mailbox Control Register (MB = 4) */
  #define REG_CAN0_MMR5    (*(__IO uint32_t*)0xF80002A0U) /**< \brief (CAN0) Mailbox Mode Register (MB = 5) */
  #define REG_CAN0_MAM5    (*(__IO uint32_t*)0xF80002A4U) /**< \brief (CAN0) Mailbox Acceptance Mask Register (MB = 5) */
  #define REG_CAN0_MID5    (*(__IO uint32_t*)0xF80002A8U) /**< \brief (CAN0) Mailbox ID Register (MB = 5) */
  #define REG_CAN0_MFID5   (*(__I  uint32_t*)0xF80002ACU) /**< \brief (CAN0) Mailbox Family ID Register (MB = 5) */
  #define REG_CAN0_MSR5    (*(__I  uint32_t*)0xF80002B0U) /**< \brief (CAN0) Mailbox Status Register (MB = 5) */
  #define REG_CAN0_MDL5    (*(__IO uint32_t*)0xF80002B4U) /**< \brief (CAN0) Mailbox Data Low Register (MB = 5) */
  #define REG_CAN0_MDH5    (*(__IO uint32_t*)0xF80002B8U) /**< \brief (CAN0) Mailbox Data High Register (MB = 5) */
  #define REG_CAN0_MCR5    (*(__O  uint32_t*)0xF80002BCU) /**< \brief (CAN0) Mailbox Control Register (MB = 5) */
  #define REG_CAN0_MMR6    (*(__IO uint32_t*)0xF80002C0U) /**< \brief (CAN0) Mailbox Mode Register (MB = 6) */
  #define REG_CAN0_MAM6    (*(__IO uint32_t*)0xF80002C4U) /**< \brief (CAN0) Mailbox Acceptance Mask Register (MB = 6) */
  #define REG_CAN0_MID6    (*(__IO uint32_t*)0xF80002C8U) /**< \brief (CAN0) Mailbox ID Register (MB = 6) */
  #define REG_CAN0_MFID6   (*(__I  uint32_t*)0xF80002CCU) /**< \brief (CAN0) Mailbox Family ID Register (MB = 6) */
  #define REG_CAN0_MSR6    (*(__I  uint32_t*)0xF80002D0U) /**< \brief (CAN0) Mailbox Status Register (MB = 6) */
  #define REG_CAN0_MDL6    (*(__IO uint32_t*)0xF80002D4U) /**< \brief (CAN0) Mailbox Data Low Register (MB = 6) */
  #define REG_CAN0_MDH6    (*(__IO uint32_t*)0xF80002D8U) /**< \brief (CAN0) Mailbox Data High Register (MB = 6) */
  #define REG_CAN0_MCR6    (*(__O  uint32_t*)0xF80002DCU) /**< \brief (CAN0) Mailbox Control Register (MB = 6) */
  #define REG_CAN0_MMR7    (*(__IO uint32_t*)0xF80002E0U) /**< \brief (CAN0) Mailbox Mode Register (MB = 7) */
  #define REG_CAN0_MAM7    (*(__IO uint32_t*)0xF80002E4U) /**< \brief (CAN0) Mailbox Acceptance Mask Register (MB = 7) */
  #define REG_CAN0_MID7    (*(__IO uint32_t*)0xF80002E8U) /**< \brief (CAN0) Mailbox ID Register (MB = 7) */
  #define REG_CAN0_MFID7   (*(__I  uint32_t*)0xF80002ECU) /**< \brief (CAN0) Mailbox Family ID Register (MB = 7) */
  #define REG_CAN0_MSR7    (*(__I  uint32_t*)0xF80002F0U) /**< \brief (CAN0) Mailbox Status Register (MB = 7) */
  #define REG_CAN0_MDL7    (*(__IO uint32_t*)0xF80002F4U) /**< \brief (CAN0) Mailbox Data Low Register (MB = 7) */
  #define REG_CAN0_MDH7    (*(__IO uint32_t*)0xF80002F8U) /**< \brief (CAN0) Mailbox Data High Register (MB = 7) */
  #define REG_CAN0_MCR7    (*(__O  uint32_t*)0xF80002FCU) /**< \brief (CAN0) Mailbox Control Register (MB = 7) */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_CAN0_INSTANCE_ */
