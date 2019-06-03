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

#ifndef _SAM9X_EMAC1_INSTANCE_
#define _SAM9X_EMAC1_INSTANCE_

/* ========== Register definition for EMAC1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_EMAC1_NCR                    (0xF8030000U) /**< \brief (EMAC1) Network Control Register */
  #define REG_EMAC1_NCFGR                  (0xF8030004U) /**< \brief (EMAC1) Network Configuration Register */
  #define REG_EMAC1_NSR                    (0xF8030008U) /**< \brief (EMAC1) Network Status Register */
  #define REG_EMAC1_TSR                    (0xF8030014U) /**< \brief (EMAC1) Transmit Status Register */
  #define REG_EMAC1_RBQP                   (0xF8030018U) /**< \brief (EMAC1) Receive Buffer Queue Pointer Register */
  #define REG_EMAC1_TBQP                   (0xF803001CU) /**< \brief (EMAC1) Transmit Buffer Queue Pointer Register */
  #define REG_EMAC1_RSR                    (0xF8030020U) /**< \brief (EMAC1) Receive Status Register */
  #define REG_EMAC1_ISR                    (0xF8030024U) /**< \brief (EMAC1) Interrupt Status Register */
  #define REG_EMAC1_IER                    (0xF8030028U) /**< \brief (EMAC1) Interrupt Enable Register */
  #define REG_EMAC1_IDR                    (0xF803002CU) /**< \brief (EMAC1) Interrupt Disable Register */
  #define REG_EMAC1_IMR                    (0xF8030030U) /**< \brief (EMAC1) Interrupt Mask Register */
  #define REG_EMAC1_MAN                    (0xF8030034U) /**< \brief (EMAC1) PHY Maintenance Register */
  #define REG_EMAC1_PTR                    (0xF8030038U) /**< \brief (EMAC1) Pause Time Register */
  #define REG_EMAC1_PFR                    (0xF803003CU) /**< \brief (EMAC1) Pause Frames Received Register */
  #define REG_EMAC1_FTO                    (0xF8030040U) /**< \brief (EMAC1) Frames Transmitted OK Register */
  #define REG_EMAC1_SCF                    (0xF8030044U) /**< \brief (EMAC1) Single Collision Frames Register */
  #define REG_EMAC1_MCF                    (0xF8030048U) /**< \brief (EMAC1) Multiple Collision Frames Register */
  #define REG_EMAC1_FRO                    (0xF803004CU) /**< \brief (EMAC1) Frames Received OK Register */
  #define REG_EMAC1_FCSE                   (0xF8030050U) /**< \brief (EMAC1) Frame Check Sequence Errors Register */
  #define REG_EMAC1_ALE                    (0xF8030054U) /**< \brief (EMAC1) Alignment Errors Register */
  #define REG_EMAC1_DTF                    (0xF8030058U) /**< \brief (EMAC1) Deferred Transmission Frames Register */
  #define REG_EMAC1_LCOL                   (0xF803005CU) /**< \brief (EMAC1) Late Collisions Register */
  #define REG_EMAC1_ECOL                   (0xF8030060U) /**< \brief (EMAC1) Excessive Collisions Register */
  #define REG_EMAC1_TUND                   (0xF8030064U) /**< \brief (EMAC1) Transmit Underrun Errors Register */
  #define REG_EMAC1_CSE                    (0xF8030068U) /**< \brief (EMAC1) Carrier Sense Errors Register */
  #define REG_EMAC1_RRE                    (0xF803006CU) /**< \brief (EMAC1) Receive Resource Errors Register */
  #define REG_EMAC1_ROV                    (0xF8030070U) /**< \brief (EMAC1) Receive Overrun Errors Register */
  #define REG_EMAC1_RSE                    (0xF8030074U) /**< \brief (EMAC1) Receive Symbol Errors Register */
  #define REG_EMAC1_ELE                    (0xF8030078U) /**< \brief (EMAC1) Excessive Length Errors Register */
  #define REG_EMAC1_RJA                    (0xF803007CU) /**< \brief (EMAC1) Receive Jabbers Register */
  #define REG_EMAC1_USF                    (0xF8030080U) /**< \brief (EMAC1) Undersize Frames Register */
  #define REG_EMAC1_STE                    (0xF8030084U) /**< \brief (EMAC1) SQE Test Errors Register */
  #define REG_EMAC1_RLE                    (0xF8030088U) /**< \brief (EMAC1) Received Length Field Mismatch Register */
  #define REG_EMAC1_TPF                    (0xF803008CU) /**< \brief (EMAC1) Transmitted Pause Frames Register */
  #define REG_EMAC1_HRB                    (0xF8030090U) /**< \brief (EMAC1) Hash Register Bottom [31:0] Register */
  #define REG_EMAC1_HRT                    (0xF8030094U) /**< \brief (EMAC1) Hash Register Top [63:32] Register */
  #define REG_EMAC1_SA1B                   (0xF8030098U) /**< \brief (EMAC1) Specific Address 1 Bottom Register */
  #define REG_EMAC1_SA1T                   (0xF803009CU) /**< \brief (EMAC1) Specific Address 1 Top Register */
  #define REG_EMAC1_SA2B                   (0xF80300A0U) /**< \brief (EMAC1) Specific Address 2 Bottom Register */
  #define REG_EMAC1_SA2T                   (0xF80300A4U) /**< \brief (EMAC1) Specific Address 2 Top Register */
  #define REG_EMAC1_SA3B                   (0xF80300A8U) /**< \brief (EMAC1) Specific Address 3 Bottom Register */
  #define REG_EMAC1_SA3T                   (0xF80300ACU) /**< \brief (EMAC1) Specific Address 3 Top Register */
  #define REG_EMAC1_SA4B                   (0xF80300B0U) /**< \brief (EMAC1) Specific Address 4 Bottom Register */
  #define REG_EMAC1_SA4T                   (0xF80300B4U) /**< \brief (EMAC1) Specific Address 4 Top Register */
  #define REG_EMAC1_TID                    (0xF80300B8U) /**< \brief (EMAC1) Type ID Checking Register */
  #define REG_EMAC1_TPQ                    (0xF80300BCU) /**< \brief (EMAC1) Transmit Pause Quantum Register */
  #define REG_EMAC1_USRIO                  (0xF80300C0U) /**< \brief (EMAC1) User Input/Output Register */
  #define REG_EMAC1_WOL                    (0xF80300C4U) /**< \brief (EMAC1) Wake-on-LAN Register */
#else
  #define REG_EMAC1_NCR   (*(__IO uint32_t*)0xF8030000U) /**< \brief (EMAC1) Network Control Register */
  #define REG_EMAC1_NCFGR (*(__IO uint32_t*)0xF8030004U) /**< \brief (EMAC1) Network Configuration Register */
  #define REG_EMAC1_NSR   (*(__I  uint32_t*)0xF8030008U) /**< \brief (EMAC1) Network Status Register */
  #define REG_EMAC1_TSR   (*(__IO uint32_t*)0xF8030014U) /**< \brief (EMAC1) Transmit Status Register */
  #define REG_EMAC1_RBQP  (*(__IO uint32_t*)0xF8030018U) /**< \brief (EMAC1) Receive Buffer Queue Pointer Register */
  #define REG_EMAC1_TBQP  (*(__IO uint32_t*)0xF803001CU) /**< \brief (EMAC1) Transmit Buffer Queue Pointer Register */
  #define REG_EMAC1_RSR   (*(__IO uint32_t*)0xF8030020U) /**< \brief (EMAC1) Receive Status Register */
  #define REG_EMAC1_ISR   (*(__IO uint32_t*)0xF8030024U) /**< \brief (EMAC1) Interrupt Status Register */
  #define REG_EMAC1_IER   (*(__O  uint32_t*)0xF8030028U) /**< \brief (EMAC1) Interrupt Enable Register */
  #define REG_EMAC1_IDR   (*(__O  uint32_t*)0xF803002CU) /**< \brief (EMAC1) Interrupt Disable Register */
  #define REG_EMAC1_IMR   (*(__I  uint32_t*)0xF8030030U) /**< \brief (EMAC1) Interrupt Mask Register */
  #define REG_EMAC1_MAN   (*(__IO uint32_t*)0xF8030034U) /**< \brief (EMAC1) PHY Maintenance Register */
  #define REG_EMAC1_PTR   (*(__IO uint32_t*)0xF8030038U) /**< \brief (EMAC1) Pause Time Register */
  #define REG_EMAC1_PFR   (*(__IO uint32_t*)0xF803003CU) /**< \brief (EMAC1) Pause Frames Received Register */
  #define REG_EMAC1_FTO   (*(__IO uint32_t*)0xF8030040U) /**< \brief (EMAC1) Frames Transmitted OK Register */
  #define REG_EMAC1_SCF   (*(__IO uint32_t*)0xF8030044U) /**< \brief (EMAC1) Single Collision Frames Register */
  #define REG_EMAC1_MCF   (*(__IO uint32_t*)0xF8030048U) /**< \brief (EMAC1) Multiple Collision Frames Register */
  #define REG_EMAC1_FRO   (*(__IO uint32_t*)0xF803004CU) /**< \brief (EMAC1) Frames Received OK Register */
  #define REG_EMAC1_FCSE  (*(__IO uint32_t*)0xF8030050U) /**< \brief (EMAC1) Frame Check Sequence Errors Register */
  #define REG_EMAC1_ALE   (*(__IO uint32_t*)0xF8030054U) /**< \brief (EMAC1) Alignment Errors Register */
  #define REG_EMAC1_DTF   (*(__IO uint32_t*)0xF8030058U) /**< \brief (EMAC1) Deferred Transmission Frames Register */
  #define REG_EMAC1_LCOL  (*(__IO uint32_t*)0xF803005CU) /**< \brief (EMAC1) Late Collisions Register */
  #define REG_EMAC1_ECOL  (*(__IO uint32_t*)0xF8030060U) /**< \brief (EMAC1) Excessive Collisions Register */
  #define REG_EMAC1_TUND  (*(__IO uint32_t*)0xF8030064U) /**< \brief (EMAC1) Transmit Underrun Errors Register */
  #define REG_EMAC1_CSE   (*(__IO uint32_t*)0xF8030068U) /**< \brief (EMAC1) Carrier Sense Errors Register */
  #define REG_EMAC1_RRE   (*(__IO uint32_t*)0xF803006CU) /**< \brief (EMAC1) Receive Resource Errors Register */
  #define REG_EMAC1_ROV   (*(__IO uint32_t*)0xF8030070U) /**< \brief (EMAC1) Receive Overrun Errors Register */
  #define REG_EMAC1_RSE   (*(__IO uint32_t*)0xF8030074U) /**< \brief (EMAC1) Receive Symbol Errors Register */
  #define REG_EMAC1_ELE   (*(__IO uint32_t*)0xF8030078U) /**< \brief (EMAC1) Excessive Length Errors Register */
  #define REG_EMAC1_RJA   (*(__IO uint32_t*)0xF803007CU) /**< \brief (EMAC1) Receive Jabbers Register */
  #define REG_EMAC1_USF   (*(__IO uint32_t*)0xF8030080U) /**< \brief (EMAC1) Undersize Frames Register */
  #define REG_EMAC1_STE   (*(__IO uint32_t*)0xF8030084U) /**< \brief (EMAC1) SQE Test Errors Register */
  #define REG_EMAC1_RLE   (*(__IO uint32_t*)0xF8030088U) /**< \brief (EMAC1) Received Length Field Mismatch Register */
  #define REG_EMAC1_TPF   (*(__IO uint32_t*)0xF803008CU) /**< \brief (EMAC1) Transmitted Pause Frames Register */
  #define REG_EMAC1_HRB   (*(__IO uint32_t*)0xF8030090U) /**< \brief (EMAC1) Hash Register Bottom [31:0] Register */
  #define REG_EMAC1_HRT   (*(__IO uint32_t*)0xF8030094U) /**< \brief (EMAC1) Hash Register Top [63:32] Register */
  #define REG_EMAC1_SA1B  (*(__IO uint32_t*)0xF8030098U) /**< \brief (EMAC1) Specific Address 1 Bottom Register */
  #define REG_EMAC1_SA1T  (*(__IO uint32_t*)0xF803009CU) /**< \brief (EMAC1) Specific Address 1 Top Register */
  #define REG_EMAC1_SA2B  (*(__IO uint32_t*)0xF80300A0U) /**< \brief (EMAC1) Specific Address 2 Bottom Register */
  #define REG_EMAC1_SA2T  (*(__IO uint32_t*)0xF80300A4U) /**< \brief (EMAC1) Specific Address 2 Top Register */
  #define REG_EMAC1_SA3B  (*(__IO uint32_t*)0xF80300A8U) /**< \brief (EMAC1) Specific Address 3 Bottom Register */
  #define REG_EMAC1_SA3T  (*(__IO uint32_t*)0xF80300ACU) /**< \brief (EMAC1) Specific Address 3 Top Register */
  #define REG_EMAC1_SA4B  (*(__IO uint32_t*)0xF80300B0U) /**< \brief (EMAC1) Specific Address 4 Bottom Register */
  #define REG_EMAC1_SA4T  (*(__IO uint32_t*)0xF80300B4U) /**< \brief (EMAC1) Specific Address 4 Top Register */
  #define REG_EMAC1_TID   (*(__IO uint32_t*)0xF80300B8U) /**< \brief (EMAC1) Type ID Checking Register */
  #define REG_EMAC1_TPQ   (*(__IO uint32_t*)0xF80300BCU) /**< \brief (EMAC1) Transmit Pause Quantum Register */
  #define REG_EMAC1_USRIO (*(__IO uint32_t*)0xF80300C0U) /**< \brief (EMAC1) User Input/Output Register */
  #define REG_EMAC1_WOL   (*(__IO uint32_t*)0xF80300C4U) /**< \brief (EMAC1) Wake-on-LAN Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_EMAC1_INSTANCE_ */
