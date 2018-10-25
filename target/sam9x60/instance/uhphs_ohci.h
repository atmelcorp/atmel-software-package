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

#ifndef _SAM9X_UHPHS_OHCI_INSTANCE_
#define _SAM9X_UHPHS_OHCI_INSTANCE_

/* ========== Register definition for UHPHS_OHCI peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_UHPHS_OHCI_HcRevision                          (0x00600000U) /**< \brief (UHPHS_OHCI) OHCI Revision Number Register */
  #define REG_UHPHS_OHCI_HcControl                           (0x00600004U) /**< \brief (UHPHS_OHCI) HC Operating Mode Register */
  #define REG_UHPHS_OHCI_HcCommandStatus                     (0x00600008U) /**< \brief (UHPHS_OHCI) HC Command and Status Register */
  #define REG_UHPHS_OHCI_HcInterruptStatus                   (0x0060000CU) /**< \brief (UHPHS_OHCI) HC Interrupt and Status Register */
  #define REG_UHPHS_OHCI_HcInterruptEnable                   (0x00600010U) /**< \brief (UHPHS_OHCI) HC Interrupt Enable Register */
  #define REG_UHPHS_OHCI_HcInterruptDisable                  (0x00600014U) /**< \brief (UHPHS_OHCI) HC Interrupt Disable Register */
  #define REG_UHPHS_OHCI_HcHCCA                              (0x00600018U) /**< \brief (UHPHS_OHCI) HC HCCA Address Register */
  #define REG_UHPHS_OHCI_HcPeriodCurrentED                   (0x0060001CU) /**< \brief (UHPHS_OHCI) HC Current Periodic Register */
  #define REG_UHPHS_OHCI_HcControlHeadED                     (0x00600020U) /**< \brief (UHPHS_OHCI) HC Head Control Register */
  #define REG_UHPHS_OHCI_HcControlCurrentED                  (0x00600024U) /**< \brief (UHPHS_OHCI) HC Current Control Register */
  #define REG_UHPHS_OHCI_HcBulkHeadED                        (0x00600028U) /**< \brief (UHPHS_OHCI) HC Head Bulk Register */
  #define REG_UHPHS_OHCI_HcBulkCurrentED                     (0x0060002CU) /**< \brief (UHPHS_OHCI) HC Current Bulk Register */
  #define REG_UHPHS_OHCI_HcDoneHead                          (0x00600030U) /**< \brief (UHPHS_OHCI) HC Head Done Register */
  #define REG_UHPHS_OHCI_HcFmInterval                        (0x00600034U) /**< \brief (UHPHS_OHCI) HC Frame Interval Register */
  #define REG_UHPHS_OHCI_HcFmRemaining                       (0x00600038U) /**< \brief (UHPHS_OHCI) HC Frame Remaining Register */
  #define REG_UHPHS_OHCI_HcFmNumber                          (0x0060003CU) /**< \brief (UHPHS_OHCI) HC Frame Number Register */
  #define REG_UHPHS_OHCI_HcPeriodicStart                     (0x00600040U) /**< \brief (UHPHS_OHCI) HC Periodic Start Register */
  #define REG_UHPHS_OHCI_HcLSThreshold                       (0x00600044U) /**< \brief (UHPHS_OHCI) HC Low-Speed Threshold Register */
  #define REG_UHPHS_OHCI_HcRhDescriptorA                     (0x00600048U) /**< \brief (UHPHS_OHCI) HC Root Hub A Register */
  #define REG_UHPHS_OHCI_HcRhDescriptorB                     (0x0060004CU) /**< \brief (UHPHS_OHCI) HC Root Hub B Register */
  #define REG_UHPHS_OHCI_HcRhStatus                          (0x00600050U) /**< \brief (UHPHS_OHCI) HC Root Hub Status Register */
  #define REG_UHPHS_OHCI_HcRhPortStatus                      (0x00600054U) /**< \brief (UHPHS_OHCI) HC Port Status and Control Register (ndp = 0) */
#else
  #define REG_UHPHS_OHCI_HcRevision         (*(__I  uint32_t*)0x00600000U) /**< \brief (UHPHS_OHCI) OHCI Revision Number Register */
  #define REG_UHPHS_OHCI_HcControl          (*(__IO uint32_t*)0x00600004U) /**< \brief (UHPHS_OHCI) HC Operating Mode Register */
  #define REG_UHPHS_OHCI_HcCommandStatus    (*(__IO uint32_t*)0x00600008U) /**< \brief (UHPHS_OHCI) HC Command and Status Register */
  #define REG_UHPHS_OHCI_HcInterruptStatus  (*(__IO uint32_t*)0x0060000CU) /**< \brief (UHPHS_OHCI) HC Interrupt and Status Register */
  #define REG_UHPHS_OHCI_HcInterruptEnable  (*(__IO uint32_t*)0x00600010U) /**< \brief (UHPHS_OHCI) HC Interrupt Enable Register */
  #define REG_UHPHS_OHCI_HcInterruptDisable (*(__IO uint32_t*)0x00600014U) /**< \brief (UHPHS_OHCI) HC Interrupt Disable Register */
  #define REG_UHPHS_OHCI_HcHCCA             (*(__IO uint32_t*)0x00600018U) /**< \brief (UHPHS_OHCI) HC HCCA Address Register */
  #define REG_UHPHS_OHCI_HcPeriodCurrentED  (*(__IO uint32_t*)0x0060001CU) /**< \brief (UHPHS_OHCI) HC Current Periodic Register */
  #define REG_UHPHS_OHCI_HcControlHeadED    (*(__IO uint32_t*)0x00600020U) /**< \brief (UHPHS_OHCI) HC Head Control Register */
  #define REG_UHPHS_OHCI_HcControlCurrentED (*(__IO uint32_t*)0x00600024U) /**< \brief (UHPHS_OHCI) HC Current Control Register */
  #define REG_UHPHS_OHCI_HcBulkHeadED       (*(__IO uint32_t*)0x00600028U) /**< \brief (UHPHS_OHCI) HC Head Bulk Register */
  #define REG_UHPHS_OHCI_HcBulkCurrentED    (*(__IO uint32_t*)0x0060002CU) /**< \brief (UHPHS_OHCI) HC Current Bulk Register */
  #define REG_UHPHS_OHCI_HcDoneHead         (*(__IO uint32_t*)0x00600030U) /**< \brief (UHPHS_OHCI) HC Head Done Register */
  #define REG_UHPHS_OHCI_HcFmInterval       (*(__IO uint32_t*)0x00600034U) /**< \brief (UHPHS_OHCI) HC Frame Interval Register */
  #define REG_UHPHS_OHCI_HcFmRemaining      (*(__IO uint32_t*)0x00600038U) /**< \brief (UHPHS_OHCI) HC Frame Remaining Register */
  #define REG_UHPHS_OHCI_HcFmNumber         (*(__IO uint32_t*)0x0060003CU) /**< \brief (UHPHS_OHCI) HC Frame Number Register */
  #define REG_UHPHS_OHCI_HcPeriodicStart    (*(__IO uint32_t*)0x00600040U) /**< \brief (UHPHS_OHCI) HC Periodic Start Register */
  #define REG_UHPHS_OHCI_HcLSThreshold      (*(__IO uint32_t*)0x00600044U) /**< \brief (UHPHS_OHCI) HC Low-Speed Threshold Register */
  #define REG_UHPHS_OHCI_HcRhDescriptorA    (*(__IO uint32_t*)0x00600048U) /**< \brief (UHPHS_OHCI) HC Root Hub A Register */
  #define REG_UHPHS_OHCI_HcRhDescriptorB    (*(__IO uint32_t*)0x0060004CU) /**< \brief (UHPHS_OHCI) HC Root Hub B Register */
  #define REG_UHPHS_OHCI_HcRhStatus         (*(__IO uint32_t*)0x00600050U) /**< \brief (UHPHS_OHCI) HC Root Hub Status Register */
  #define REG_UHPHS_OHCI_HcRhPortStatus     (*(__IO uint32_t*)0x00600054U) /**< \brief (UHPHS_OHCI) HC Port Status and Control Register (ndp = 0) */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_UHPHS_OHCI_INSTANCE_ */
