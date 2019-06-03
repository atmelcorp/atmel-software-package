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

#ifndef _SAM9X_CAN1_INSTANCE_
#define _SAM9X_CAN1_INSTANCE_

/* ========== Register definition for CAN1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_CAN1_MR                       (0xF8004000U) /**< \brief (CAN1) Mode Register */
  #define REG_CAN1_IER                      (0xF8004004U) /**< \brief (CAN1) Interrupt Enable Register */
  #define REG_CAN1_IDR                      (0xF8004008U) /**< \brief (CAN1) Interrupt Disable Register */
  #define REG_CAN1_IMR                      (0xF800400CU) /**< \brief (CAN1) Interrupt Mask Register */
  #define REG_CAN1_SR                       (0xF8004010U) /**< \brief (CAN1) Status Register */
  #define REG_CAN1_BR                       (0xF8004014U) /**< \brief (CAN1) Baudrate Register */
  #define REG_CAN1_TIM                      (0xF8004018U) /**< \brief (CAN1) Timer Register */
  #define REG_CAN1_TIMESTP                  (0xF800401CU) /**< \brief (CAN1) Timestamp Register */
  #define REG_CAN1_ECR                      (0xF8004020U) /**< \brief (CAN1) Error Counter Register */
  #define REG_CAN1_TCR                      (0xF8004024U) /**< \brief (CAN1) Transfer Command Register */
  #define REG_CAN1_ACR                      (0xF8004028U) /**< \brief (CAN1) Abort Command Register */
  #define REG_CAN1_WPMR                     (0xF80040E4U) /**< \brief (CAN1) Write Protection Mode Register */
  #define REG_CAN1_WPSR                     (0xF80040E8U) /**< \brief (CAN1) Write Protection Status Register */
  #define REG_CAN1_MMR0                     (0xF8004200U) /**< \brief (CAN1) Mailbox Mode Register (MB = 0) */
  #define REG_CAN1_MAM0                     (0xF8004204U) /**< \brief (CAN1) Mailbox Acceptance Mask Register (MB = 0) */
  #define REG_CAN1_MID0                     (0xF8004208U) /**< \brief (CAN1) Mailbox ID Register (MB = 0) */
  #define REG_CAN1_MFID0                    (0xF800420CU) /**< \brief (CAN1) Mailbox Family ID Register (MB = 0) */
  #define REG_CAN1_MSR0                     (0xF8004210U) /**< \brief (CAN1) Mailbox Status Register (MB = 0) */
  #define REG_CAN1_MDL0                     (0xF8004214U) /**< \brief (CAN1) Mailbox Data Low Register (MB = 0) */
  #define REG_CAN1_MDH0                     (0xF8004218U) /**< \brief (CAN1) Mailbox Data High Register (MB = 0) */
  #define REG_CAN1_MCR0                     (0xF800421CU) /**< \brief (CAN1) Mailbox Control Register (MB = 0) */
  #define REG_CAN1_MMR1                     (0xF8004220U) /**< \brief (CAN1) Mailbox Mode Register (MB = 1) */
  #define REG_CAN1_MAM1                     (0xF8004224U) /**< \brief (CAN1) Mailbox Acceptance Mask Register (MB = 1) */
  #define REG_CAN1_MID1                     (0xF8004228U) /**< \brief (CAN1) Mailbox ID Register (MB = 1) */
  #define REG_CAN1_MFID1                    (0xF800422CU) /**< \brief (CAN1) Mailbox Family ID Register (MB = 1) */
  #define REG_CAN1_MSR1                     (0xF8004230U) /**< \brief (CAN1) Mailbox Status Register (MB = 1) */
  #define REG_CAN1_MDL1                     (0xF8004234U) /**< \brief (CAN1) Mailbox Data Low Register (MB = 1) */
  #define REG_CAN1_MDH1                     (0xF8004238U) /**< \brief (CAN1) Mailbox Data High Register (MB = 1) */
  #define REG_CAN1_MCR1                     (0xF800423CU) /**< \brief (CAN1) Mailbox Control Register (MB = 1) */
  #define REG_CAN1_MMR2                     (0xF8004240U) /**< \brief (CAN1) Mailbox Mode Register (MB = 2) */
  #define REG_CAN1_MAM2                     (0xF8004244U) /**< \brief (CAN1) Mailbox Acceptance Mask Register (MB = 2) */
  #define REG_CAN1_MID2                     (0xF8004248U) /**< \brief (CAN1) Mailbox ID Register (MB = 2) */
  #define REG_CAN1_MFID2                    (0xF800424CU) /**< \brief (CAN1) Mailbox Family ID Register (MB = 2) */
  #define REG_CAN1_MSR2                     (0xF8004250U) /**< \brief (CAN1) Mailbox Status Register (MB = 2) */
  #define REG_CAN1_MDL2                     (0xF8004254U) /**< \brief (CAN1) Mailbox Data Low Register (MB = 2) */
  #define REG_CAN1_MDH2                     (0xF8004258U) /**< \brief (CAN1) Mailbox Data High Register (MB = 2) */
  #define REG_CAN1_MCR2                     (0xF800425CU) /**< \brief (CAN1) Mailbox Control Register (MB = 2) */
  #define REG_CAN1_MMR3                     (0xF8004260U) /**< \brief (CAN1) Mailbox Mode Register (MB = 3) */
  #define REG_CAN1_MAM3                     (0xF8004264U) /**< \brief (CAN1) Mailbox Acceptance Mask Register (MB = 3) */
  #define REG_CAN1_MID3                     (0xF8004268U) /**< \brief (CAN1) Mailbox ID Register (MB = 3) */
  #define REG_CAN1_MFID3                    (0xF800426CU) /**< \brief (CAN1) Mailbox Family ID Register (MB = 3) */
  #define REG_CAN1_MSR3                     (0xF8004270U) /**< \brief (CAN1) Mailbox Status Register (MB = 3) */
  #define REG_CAN1_MDL3                     (0xF8004274U) /**< \brief (CAN1) Mailbox Data Low Register (MB = 3) */
  #define REG_CAN1_MDH3                     (0xF8004278U) /**< \brief (CAN1) Mailbox Data High Register (MB = 3) */
  #define REG_CAN1_MCR3                     (0xF800427CU) /**< \brief (CAN1) Mailbox Control Register (MB = 3) */
  #define REG_CAN1_MMR4                     (0xF8004280U) /**< \brief (CAN1) Mailbox Mode Register (MB = 4) */
  #define REG_CAN1_MAM4                     (0xF8004284U) /**< \brief (CAN1) Mailbox Acceptance Mask Register (MB = 4) */
  #define REG_CAN1_MID4                     (0xF8004288U) /**< \brief (CAN1) Mailbox ID Register (MB = 4) */
  #define REG_CAN1_MFID4                    (0xF800428CU) /**< \brief (CAN1) Mailbox Family ID Register (MB = 4) */
  #define REG_CAN1_MSR4                     (0xF8004290U) /**< \brief (CAN1) Mailbox Status Register (MB = 4) */
  #define REG_CAN1_MDL4                     (0xF8004294U) /**< \brief (CAN1) Mailbox Data Low Register (MB = 4) */
  #define REG_CAN1_MDH4                     (0xF8004298U) /**< \brief (CAN1) Mailbox Data High Register (MB = 4) */
  #define REG_CAN1_MCR4                     (0xF800429CU) /**< \brief (CAN1) Mailbox Control Register (MB = 4) */
  #define REG_CAN1_MMR5                     (0xF80042A0U) /**< \brief (CAN1) Mailbox Mode Register (MB = 5) */
  #define REG_CAN1_MAM5                     (0xF80042A4U) /**< \brief (CAN1) Mailbox Acceptance Mask Register (MB = 5) */
  #define REG_CAN1_MID5                     (0xF80042A8U) /**< \brief (CAN1) Mailbox ID Register (MB = 5) */
  #define REG_CAN1_MFID5                    (0xF80042ACU) /**< \brief (CAN1) Mailbox Family ID Register (MB = 5) */
  #define REG_CAN1_MSR5                     (0xF80042B0U) /**< \brief (CAN1) Mailbox Status Register (MB = 5) */
  #define REG_CAN1_MDL5                     (0xF80042B4U) /**< \brief (CAN1) Mailbox Data Low Register (MB = 5) */
  #define REG_CAN1_MDH5                     (0xF80042B8U) /**< \brief (CAN1) Mailbox Data High Register (MB = 5) */
  #define REG_CAN1_MCR5                     (0xF80042BCU) /**< \brief (CAN1) Mailbox Control Register (MB = 5) */
  #define REG_CAN1_MMR6                     (0xF80042C0U) /**< \brief (CAN1) Mailbox Mode Register (MB = 6) */
  #define REG_CAN1_MAM6                     (0xF80042C4U) /**< \brief (CAN1) Mailbox Acceptance Mask Register (MB = 6) */
  #define REG_CAN1_MID6                     (0xF80042C8U) /**< \brief (CAN1) Mailbox ID Register (MB = 6) */
  #define REG_CAN1_MFID6                    (0xF80042CCU) /**< \brief (CAN1) Mailbox Family ID Register (MB = 6) */
  #define REG_CAN1_MSR6                     (0xF80042D0U) /**< \brief (CAN1) Mailbox Status Register (MB = 6) */
  #define REG_CAN1_MDL6                     (0xF80042D4U) /**< \brief (CAN1) Mailbox Data Low Register (MB = 6) */
  #define REG_CAN1_MDH6                     (0xF80042D8U) /**< \brief (CAN1) Mailbox Data High Register (MB = 6) */
  #define REG_CAN1_MCR6                     (0xF80042DCU) /**< \brief (CAN1) Mailbox Control Register (MB = 6) */
  #define REG_CAN1_MMR7                     (0xF80042E0U) /**< \brief (CAN1) Mailbox Mode Register (MB = 7) */
  #define REG_CAN1_MAM7                     (0xF80042E4U) /**< \brief (CAN1) Mailbox Acceptance Mask Register (MB = 7) */
  #define REG_CAN1_MID7                     (0xF80042E8U) /**< \brief (CAN1) Mailbox ID Register (MB = 7) */
  #define REG_CAN1_MFID7                    (0xF80042ECU) /**< \brief (CAN1) Mailbox Family ID Register (MB = 7) */
  #define REG_CAN1_MSR7                     (0xF80042F0U) /**< \brief (CAN1) Mailbox Status Register (MB = 7) */
  #define REG_CAN1_MDL7                     (0xF80042F4U) /**< \brief (CAN1) Mailbox Data Low Register (MB = 7) */
  #define REG_CAN1_MDH7                     (0xF80042F8U) /**< \brief (CAN1) Mailbox Data High Register (MB = 7) */
  #define REG_CAN1_MCR7                     (0xF80042FCU) /**< \brief (CAN1) Mailbox Control Register (MB = 7) */
#else
  #define REG_CAN1_MR      (*(__IO uint32_t*)0xF8004000U) /**< \brief (CAN1) Mode Register */
  #define REG_CAN1_IER     (*(__O  uint32_t*)0xF8004004U) /**< \brief (CAN1) Interrupt Enable Register */
  #define REG_CAN1_IDR     (*(__O  uint32_t*)0xF8004008U) /**< \brief (CAN1) Interrupt Disable Register */
  #define REG_CAN1_IMR     (*(__I  uint32_t*)0xF800400CU) /**< \brief (CAN1) Interrupt Mask Register */
  #define REG_CAN1_SR      (*(__I  uint32_t*)0xF8004010U) /**< \brief (CAN1) Status Register */
  #define REG_CAN1_BR      (*(__IO uint32_t*)0xF8004014U) /**< \brief (CAN1) Baudrate Register */
  #define REG_CAN1_TIM     (*(__I  uint32_t*)0xF8004018U) /**< \brief (CAN1) Timer Register */
  #define REG_CAN1_TIMESTP (*(__I  uint32_t*)0xF800401CU) /**< \brief (CAN1) Timestamp Register */
  #define REG_CAN1_ECR     (*(__I  uint32_t*)0xF8004020U) /**< \brief (CAN1) Error Counter Register */
  #define REG_CAN1_TCR     (*(__O  uint32_t*)0xF8004024U) /**< \brief (CAN1) Transfer Command Register */
  #define REG_CAN1_ACR     (*(__O  uint32_t*)0xF8004028U) /**< \brief (CAN1) Abort Command Register */
  #define REG_CAN1_WPMR    (*(__IO uint32_t*)0xF80040E4U) /**< \brief (CAN1) Write Protection Mode Register */
  #define REG_CAN1_WPSR    (*(__I  uint32_t*)0xF80040E8U) /**< \brief (CAN1) Write Protection Status Register */
  #define REG_CAN1_MMR0    (*(__IO uint32_t*)0xF8004200U) /**< \brief (CAN1) Mailbox Mode Register (MB = 0) */
  #define REG_CAN1_MAM0    (*(__IO uint32_t*)0xF8004204U) /**< \brief (CAN1) Mailbox Acceptance Mask Register (MB = 0) */
  #define REG_CAN1_MID0    (*(__IO uint32_t*)0xF8004208U) /**< \brief (CAN1) Mailbox ID Register (MB = 0) */
  #define REG_CAN1_MFID0   (*(__I  uint32_t*)0xF800420CU) /**< \brief (CAN1) Mailbox Family ID Register (MB = 0) */
  #define REG_CAN1_MSR0    (*(__I  uint32_t*)0xF8004210U) /**< \brief (CAN1) Mailbox Status Register (MB = 0) */
  #define REG_CAN1_MDL0    (*(__IO uint32_t*)0xF8004214U) /**< \brief (CAN1) Mailbox Data Low Register (MB = 0) */
  #define REG_CAN1_MDH0    (*(__IO uint32_t*)0xF8004218U) /**< \brief (CAN1) Mailbox Data High Register (MB = 0) */
  #define REG_CAN1_MCR0    (*(__O  uint32_t*)0xF800421CU) /**< \brief (CAN1) Mailbox Control Register (MB = 0) */
  #define REG_CAN1_MMR1    (*(__IO uint32_t*)0xF8004220U) /**< \brief (CAN1) Mailbox Mode Register (MB = 1) */
  #define REG_CAN1_MAM1    (*(__IO uint32_t*)0xF8004224U) /**< \brief (CAN1) Mailbox Acceptance Mask Register (MB = 1) */
  #define REG_CAN1_MID1    (*(__IO uint32_t*)0xF8004228U) /**< \brief (CAN1) Mailbox ID Register (MB = 1) */
  #define REG_CAN1_MFID1   (*(__I  uint32_t*)0xF800422CU) /**< \brief (CAN1) Mailbox Family ID Register (MB = 1) */
  #define REG_CAN1_MSR1    (*(__I  uint32_t*)0xF8004230U) /**< \brief (CAN1) Mailbox Status Register (MB = 1) */
  #define REG_CAN1_MDL1    (*(__IO uint32_t*)0xF8004234U) /**< \brief (CAN1) Mailbox Data Low Register (MB = 1) */
  #define REG_CAN1_MDH1    (*(__IO uint32_t*)0xF8004238U) /**< \brief (CAN1) Mailbox Data High Register (MB = 1) */
  #define REG_CAN1_MCR1    (*(__O  uint32_t*)0xF800423CU) /**< \brief (CAN1) Mailbox Control Register (MB = 1) */
  #define REG_CAN1_MMR2    (*(__IO uint32_t*)0xF8004240U) /**< \brief (CAN1) Mailbox Mode Register (MB = 2) */
  #define REG_CAN1_MAM2    (*(__IO uint32_t*)0xF8004244U) /**< \brief (CAN1) Mailbox Acceptance Mask Register (MB = 2) */
  #define REG_CAN1_MID2    (*(__IO uint32_t*)0xF8004248U) /**< \brief (CAN1) Mailbox ID Register (MB = 2) */
  #define REG_CAN1_MFID2   (*(__I  uint32_t*)0xF800424CU) /**< \brief (CAN1) Mailbox Family ID Register (MB = 2) */
  #define REG_CAN1_MSR2    (*(__I  uint32_t*)0xF8004250U) /**< \brief (CAN1) Mailbox Status Register (MB = 2) */
  #define REG_CAN1_MDL2    (*(__IO uint32_t*)0xF8004254U) /**< \brief (CAN1) Mailbox Data Low Register (MB = 2) */
  #define REG_CAN1_MDH2    (*(__IO uint32_t*)0xF8004258U) /**< \brief (CAN1) Mailbox Data High Register (MB = 2) */
  #define REG_CAN1_MCR2    (*(__O  uint32_t*)0xF800425CU) /**< \brief (CAN1) Mailbox Control Register (MB = 2) */
  #define REG_CAN1_MMR3    (*(__IO uint32_t*)0xF8004260U) /**< \brief (CAN1) Mailbox Mode Register (MB = 3) */
  #define REG_CAN1_MAM3    (*(__IO uint32_t*)0xF8004264U) /**< \brief (CAN1) Mailbox Acceptance Mask Register (MB = 3) */
  #define REG_CAN1_MID3    (*(__IO uint32_t*)0xF8004268U) /**< \brief (CAN1) Mailbox ID Register (MB = 3) */
  #define REG_CAN1_MFID3   (*(__I  uint32_t*)0xF800426CU) /**< \brief (CAN1) Mailbox Family ID Register (MB = 3) */
  #define REG_CAN1_MSR3    (*(__I  uint32_t*)0xF8004270U) /**< \brief (CAN1) Mailbox Status Register (MB = 3) */
  #define REG_CAN1_MDL3    (*(__IO uint32_t*)0xF8004274U) /**< \brief (CAN1) Mailbox Data Low Register (MB = 3) */
  #define REG_CAN1_MDH3    (*(__IO uint32_t*)0xF8004278U) /**< \brief (CAN1) Mailbox Data High Register (MB = 3) */
  #define REG_CAN1_MCR3    (*(__O  uint32_t*)0xF800427CU) /**< \brief (CAN1) Mailbox Control Register (MB = 3) */
  #define REG_CAN1_MMR4    (*(__IO uint32_t*)0xF8004280U) /**< \brief (CAN1) Mailbox Mode Register (MB = 4) */
  #define REG_CAN1_MAM4    (*(__IO uint32_t*)0xF8004284U) /**< \brief (CAN1) Mailbox Acceptance Mask Register (MB = 4) */
  #define REG_CAN1_MID4    (*(__IO uint32_t*)0xF8004288U) /**< \brief (CAN1) Mailbox ID Register (MB = 4) */
  #define REG_CAN1_MFID4   (*(__I  uint32_t*)0xF800428CU) /**< \brief (CAN1) Mailbox Family ID Register (MB = 4) */
  #define REG_CAN1_MSR4    (*(__I  uint32_t*)0xF8004290U) /**< \brief (CAN1) Mailbox Status Register (MB = 4) */
  #define REG_CAN1_MDL4    (*(__IO uint32_t*)0xF8004294U) /**< \brief (CAN1) Mailbox Data Low Register (MB = 4) */
  #define REG_CAN1_MDH4    (*(__IO uint32_t*)0xF8004298U) /**< \brief (CAN1) Mailbox Data High Register (MB = 4) */
  #define REG_CAN1_MCR4    (*(__O  uint32_t*)0xF800429CU) /**< \brief (CAN1) Mailbox Control Register (MB = 4) */
  #define REG_CAN1_MMR5    (*(__IO uint32_t*)0xF80042A0U) /**< \brief (CAN1) Mailbox Mode Register (MB = 5) */
  #define REG_CAN1_MAM5    (*(__IO uint32_t*)0xF80042A4U) /**< \brief (CAN1) Mailbox Acceptance Mask Register (MB = 5) */
  #define REG_CAN1_MID5    (*(__IO uint32_t*)0xF80042A8U) /**< \brief (CAN1) Mailbox ID Register (MB = 5) */
  #define REG_CAN1_MFID5   (*(__I  uint32_t*)0xF80042ACU) /**< \brief (CAN1) Mailbox Family ID Register (MB = 5) */
  #define REG_CAN1_MSR5    (*(__I  uint32_t*)0xF80042B0U) /**< \brief (CAN1) Mailbox Status Register (MB = 5) */
  #define REG_CAN1_MDL5    (*(__IO uint32_t*)0xF80042B4U) /**< \brief (CAN1) Mailbox Data Low Register (MB = 5) */
  #define REG_CAN1_MDH5    (*(__IO uint32_t*)0xF80042B8U) /**< \brief (CAN1) Mailbox Data High Register (MB = 5) */
  #define REG_CAN1_MCR5    (*(__O  uint32_t*)0xF80042BCU) /**< \brief (CAN1) Mailbox Control Register (MB = 5) */
  #define REG_CAN1_MMR6    (*(__IO uint32_t*)0xF80042C0U) /**< \brief (CAN1) Mailbox Mode Register (MB = 6) */
  #define REG_CAN1_MAM6    (*(__IO uint32_t*)0xF80042C4U) /**< \brief (CAN1) Mailbox Acceptance Mask Register (MB = 6) */
  #define REG_CAN1_MID6    (*(__IO uint32_t*)0xF80042C8U) /**< \brief (CAN1) Mailbox ID Register (MB = 6) */
  #define REG_CAN1_MFID6   (*(__I  uint32_t*)0xF80042CCU) /**< \brief (CAN1) Mailbox Family ID Register (MB = 6) */
  #define REG_CAN1_MSR6    (*(__I  uint32_t*)0xF80042D0U) /**< \brief (CAN1) Mailbox Status Register (MB = 6) */
  #define REG_CAN1_MDL6    (*(__IO uint32_t*)0xF80042D4U) /**< \brief (CAN1) Mailbox Data Low Register (MB = 6) */
  #define REG_CAN1_MDH6    (*(__IO uint32_t*)0xF80042D8U) /**< \brief (CAN1) Mailbox Data High Register (MB = 6) */
  #define REG_CAN1_MCR6    (*(__O  uint32_t*)0xF80042DCU) /**< \brief (CAN1) Mailbox Control Register (MB = 6) */
  #define REG_CAN1_MMR7    (*(__IO uint32_t*)0xF80042E0U) /**< \brief (CAN1) Mailbox Mode Register (MB = 7) */
  #define REG_CAN1_MAM7    (*(__IO uint32_t*)0xF80042E4U) /**< \brief (CAN1) Mailbox Acceptance Mask Register (MB = 7) */
  #define REG_CAN1_MID7    (*(__IO uint32_t*)0xF80042E8U) /**< \brief (CAN1) Mailbox ID Register (MB = 7) */
  #define REG_CAN1_MFID7   (*(__I  uint32_t*)0xF80042ECU) /**< \brief (CAN1) Mailbox Family ID Register (MB = 7) */
  #define REG_CAN1_MSR7    (*(__I  uint32_t*)0xF80042F0U) /**< \brief (CAN1) Mailbox Status Register (MB = 7) */
  #define REG_CAN1_MDL7    (*(__IO uint32_t*)0xF80042F4U) /**< \brief (CAN1) Mailbox Data Low Register (MB = 7) */
  #define REG_CAN1_MDH7    (*(__IO uint32_t*)0xF80042F8U) /**< \brief (CAN1) Mailbox Data High Register (MB = 7) */
  #define REG_CAN1_MCR7    (*(__O  uint32_t*)0xF80042FCU) /**< \brief (CAN1) Mailbox Control Register (MB = 7) */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_CAN1_INSTANCE_ */
