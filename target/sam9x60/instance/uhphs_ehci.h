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

#ifndef _SAM9X_UHPHS_EHCI_INSTANCE_
#define _SAM9X_UHPHS_EHCI_INSTANCE_

/* ========== Register definition for UHPHS_EHCI peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_UHPHS_EHCI_HCCAPBASE                         (0x00700000U) /**< \brief (UHPHS_EHCI) UHPHS Host Controller Capability Register */
  #define REG_UHPHS_EHCI_HCSPARAMS                         (0x00700004U) /**< \brief (UHPHS_EHCI) UHPHS Host Controller Structural Parameters Register */
  #define REG_UHPHS_EHCI_HCCPARAMS                         (0x00700008U) /**< \brief (UHPHS_EHCI) UHPHS Host Controller Capability Parameters Register */
  #define REG_UHPHS_EHCI_USBCMD                            (0x00700010U) /**< \brief (UHPHS_EHCI) UHPHS USB Command Register */
  #define REG_UHPHS_EHCI_USBSTS                            (0x00700014U) /**< \brief (UHPHS_EHCI) UHPHS USB Status Register */
  #define REG_UHPHS_EHCI_USBINTR                           (0x00700018U) /**< \brief (UHPHS_EHCI) UHPHS USB Interrupt Enable Register */
  #define REG_UHPHS_EHCI_FRINDEX                           (0x0070001CU) /**< \brief (UHPHS_EHCI) UHPHS USB Frame Index Register */
  #define REG_UHPHS_EHCI_CTRLDSSEGMENT                     (0x00700020U) /**< \brief (UHPHS_EHCI) UHPHS Control Data Structure Segment Register */
  #define REG_UHPHS_EHCI_PERIODICLISTBASE                  (0x00700024U) /**< \brief (UHPHS_EHCI) UHPHS Periodic Frame List Base Address Register */
  #define REG_UHPHS_EHCI_ASYNCLISTADDR                     (0x00700028U) /**< \brief (UHPHS_EHCI) UHPHS Asynchronous List Address Register */
  #define REG_UHPHS_EHCI_CONFIGFLAG                        (0x00700050U) /**< \brief (UHPHS_EHCI) UHPHS Configured Flag Register */
  #define REG_UHPHS_EHCI_PORTSC                            (0x00700054U) /**< \brief (UHPHS_EHCI) UHPHS Port Status and Control Register (port = 0) */
  #define REG_UHPHS_EHCI_INSNREG06                         (0x007000A8U) /**< \brief (UHPHS_EHCI) EHCI Specific Registers 06 */
  #define REG_UHPHS_EHCI_INSNREG07                         (0x007000ACU) /**< \brief (UHPHS_EHCI) EHCI Specific Registers 07 */
#else
  #define REG_UHPHS_EHCI_HCCAPBASE        (*(__I  uint32_t*)0x00700000U) /**< \brief (UHPHS_EHCI) UHPHS Host Controller Capability Register */
  #define REG_UHPHS_EHCI_HCSPARAMS        (*(__I  uint32_t*)0x00700004U) /**< \brief (UHPHS_EHCI) UHPHS Host Controller Structural Parameters Register */
  #define REG_UHPHS_EHCI_HCCPARAMS        (*(__I  uint32_t*)0x00700008U) /**< \brief (UHPHS_EHCI) UHPHS Host Controller Capability Parameters Register */
  #define REG_UHPHS_EHCI_USBCMD           (*(__IO uint32_t*)0x00700010U) /**< \brief (UHPHS_EHCI) UHPHS USB Command Register */
  #define REG_UHPHS_EHCI_USBSTS           (*(__IO uint32_t*)0x00700014U) /**< \brief (UHPHS_EHCI) UHPHS USB Status Register */
  #define REG_UHPHS_EHCI_USBINTR          (*(__IO uint32_t*)0x00700018U) /**< \brief (UHPHS_EHCI) UHPHS USB Interrupt Enable Register */
  #define REG_UHPHS_EHCI_FRINDEX          (*(__IO uint32_t*)0x0070001CU) /**< \brief (UHPHS_EHCI) UHPHS USB Frame Index Register */
  #define REG_UHPHS_EHCI_CTRLDSSEGMENT    (*(__IO uint32_t*)0x00700020U) /**< \brief (UHPHS_EHCI) UHPHS Control Data Structure Segment Register */
  #define REG_UHPHS_EHCI_PERIODICLISTBASE (*(__IO uint32_t*)0x00700024U) /**< \brief (UHPHS_EHCI) UHPHS Periodic Frame List Base Address Register */
  #define REG_UHPHS_EHCI_ASYNCLISTADDR    (*(__IO uint32_t*)0x00700028U) /**< \brief (UHPHS_EHCI) UHPHS Asynchronous List Address Register */
  #define REG_UHPHS_EHCI_CONFIGFLAG       (*(__IO uint32_t*)0x00700050U) /**< \brief (UHPHS_EHCI) UHPHS Configured Flag Register */
  #define REG_UHPHS_EHCI_PORTSC           (*(__IO uint32_t*)0x00700054U) /**< \brief (UHPHS_EHCI) UHPHS Port Status and Control Register (port = 0) */
  #define REG_UHPHS_EHCI_INSNREG06        (*(__IO uint32_t*)0x007000A8U) /**< \brief (UHPHS_EHCI) EHCI Specific Registers 06 */
  #define REG_UHPHS_EHCI_INSNREG07        (*(__IO uint32_t*)0x007000ACU) /**< \brief (UHPHS_EHCI) EHCI Specific Registers 07 */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_UHPHS_EHCI_INSTANCE_ */
