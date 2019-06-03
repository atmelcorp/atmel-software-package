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

#ifndef _SAM9X_EMAC0_INSTANCE_
#define _SAM9X_EMAC0_INSTANCE_

/* ========== Register definition for EMAC0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_EMAC0_NCR                    (0xF802C000U) /**< \brief (EMAC0) Network Control Register */
  #define REG_EMAC0_NCFGR                  (0xF802C004U) /**< \brief (EMAC0) Network Configuration Register */
  #define REG_EMAC0_NSR                    (0xF802C008U) /**< \brief (EMAC0) Network Status Register */
  #define REG_EMAC0_TSR                    (0xF802C014U) /**< \brief (EMAC0) Transmit Status Register */
  #define REG_EMAC0_RBQP                   (0xF802C018U) /**< \brief (EMAC0) Receive Buffer Queue Pointer Register */
  #define REG_EMAC0_TBQP                   (0xF802C01CU) /**< \brief (EMAC0) Transmit Buffer Queue Pointer Register */
  #define REG_EMAC0_RSR                    (0xF802C020U) /**< \brief (EMAC0) Receive Status Register */
  #define REG_EMAC0_ISR                    (0xF802C024U) /**< \brief (EMAC0) Interrupt Status Register */
  #define REG_EMAC0_IER                    (0xF802C028U) /**< \brief (EMAC0) Interrupt Enable Register */
  #define REG_EMAC0_IDR                    (0xF802C02CU) /**< \brief (EMAC0) Interrupt Disable Register */
  #define REG_EMAC0_IMR                    (0xF802C030U) /**< \brief (EMAC0) Interrupt Mask Register */
  #define REG_EMAC0_MAN                    (0xF802C034U) /**< \brief (EMAC0) PHY Maintenance Register */
  #define REG_EMAC0_PTR                    (0xF802C038U) /**< \brief (EMAC0) Pause Time Register */
  #define REG_EMAC0_PFR                    (0xF802C03CU) /**< \brief (EMAC0) Pause Frames Received Register */
  #define REG_EMAC0_FTO                    (0xF802C040U) /**< \brief (EMAC0) Frames Transmitted OK Register */
  #define REG_EMAC0_SCF                    (0xF802C044U) /**< \brief (EMAC0) Single Collision Frames Register */
  #define REG_EMAC0_MCF                    (0xF802C048U) /**< \brief (EMAC0) Multiple Collision Frames Register */
  #define REG_EMAC0_FRO                    (0xF802C04CU) /**< \brief (EMAC0) Frames Received OK Register */
  #define REG_EMAC0_FCSE                   (0xF802C050U) /**< \brief (EMAC0) Frame Check Sequence Errors Register */
  #define REG_EMAC0_ALE                    (0xF802C054U) /**< \brief (EMAC0) Alignment Errors Register */
  #define REG_EMAC0_DTF                    (0xF802C058U) /**< \brief (EMAC0) Deferred Transmission Frames Register */
  #define REG_EMAC0_LCOL                   (0xF802C05CU) /**< \brief (EMAC0) Late Collisions Register */
  #define REG_EMAC0_ECOL                   (0xF802C060U) /**< \brief (EMAC0) Excessive Collisions Register */
  #define REG_EMAC0_TUND                   (0xF802C064U) /**< \brief (EMAC0) Transmit Underrun Errors Register */
  #define REG_EMAC0_CSE                    (0xF802C068U) /**< \brief (EMAC0) Carrier Sense Errors Register */
  #define REG_EMAC0_RRE                    (0xF802C06CU) /**< \brief (EMAC0) Receive Resource Errors Register */
  #define REG_EMAC0_ROV                    (0xF802C070U) /**< \brief (EMAC0) Receive Overrun Errors Register */
  #define REG_EMAC0_RSE                    (0xF802C074U) /**< \brief (EMAC0) Receive Symbol Errors Register */
  #define REG_EMAC0_ELE                    (0xF802C078U) /**< \brief (EMAC0) Excessive Length Errors Register */
  #define REG_EMAC0_RJA                    (0xF802C07CU) /**< \brief (EMAC0) Receive Jabbers Register */
  #define REG_EMAC0_USF                    (0xF802C080U) /**< \brief (EMAC0) Undersize Frames Register */
  #define REG_EMAC0_STE                    (0xF802C084U) /**< \brief (EMAC0) SQE Test Errors Register */
  #define REG_EMAC0_RLE                    (0xF802C088U) /**< \brief (EMAC0) Received Length Field Mismatch Register */
  #define REG_EMAC0_TPF                    (0xF802C08CU) /**< \brief (EMAC0) Transmitted Pause Frames Register */
  #define REG_EMAC0_HRB                    (0xF802C090U) /**< \brief (EMAC0) Hash Register Bottom [31:0] Register */
  #define REG_EMAC0_HRT                    (0xF802C094U) /**< \brief (EMAC0) Hash Register Top [63:32] Register */
  #define REG_EMAC0_SA1B                   (0xF802C098U) /**< \brief (EMAC0) Specific Address 1 Bottom Register */
  #define REG_EMAC0_SA1T                   (0xF802C09CU) /**< \brief (EMAC0) Specific Address 1 Top Register */
  #define REG_EMAC0_SA2B                   (0xF802C0A0U) /**< \brief (EMAC0) Specific Address 2 Bottom Register */
  #define REG_EMAC0_SA2T                   (0xF802C0A4U) /**< \brief (EMAC0) Specific Address 2 Top Register */
  #define REG_EMAC0_SA3B                   (0xF802C0A8U) /**< \brief (EMAC0) Specific Address 3 Bottom Register */
  #define REG_EMAC0_SA3T                   (0xF802C0ACU) /**< \brief (EMAC0) Specific Address 3 Top Register */
  #define REG_EMAC0_SA4B                   (0xF802C0B0U) /**< \brief (EMAC0) Specific Address 4 Bottom Register */
  #define REG_EMAC0_SA4T                   (0xF802C0B4U) /**< \brief (EMAC0) Specific Address 4 Top Register */
  #define REG_EMAC0_TID                    (0xF802C0B8U) /**< \brief (EMAC0) Type ID Checking Register */
  #define REG_EMAC0_TPQ                    (0xF802C0BCU) /**< \brief (EMAC0) Transmit Pause Quantum Register */
  #define REG_EMAC0_USRIO                  (0xF802C0C0U) /**< \brief (EMAC0) User Input/Output Register */
  #define REG_EMAC0_WOL                    (0xF802C0C4U) /**< \brief (EMAC0) Wake-on-LAN Register */
#else
  #define REG_EMAC0_NCR   (*(__IO uint32_t*)0xF802C000U) /**< \brief (EMAC0) Network Control Register */
  #define REG_EMAC0_NCFGR (*(__IO uint32_t*)0xF802C004U) /**< \brief (EMAC0) Network Configuration Register */
  #define REG_EMAC0_NSR   (*(__I  uint32_t*)0xF802C008U) /**< \brief (EMAC0) Network Status Register */
  #define REG_EMAC0_TSR   (*(__IO uint32_t*)0xF802C014U) /**< \brief (EMAC0) Transmit Status Register */
  #define REG_EMAC0_RBQP  (*(__IO uint32_t*)0xF802C018U) /**< \brief (EMAC0) Receive Buffer Queue Pointer Register */
  #define REG_EMAC0_TBQP  (*(__IO uint32_t*)0xF802C01CU) /**< \brief (EMAC0) Transmit Buffer Queue Pointer Register */
  #define REG_EMAC0_RSR   (*(__IO uint32_t*)0xF802C020U) /**< \brief (EMAC0) Receive Status Register */
  #define REG_EMAC0_ISR   (*(__IO uint32_t*)0xF802C024U) /**< \brief (EMAC0) Interrupt Status Register */
  #define REG_EMAC0_IER   (*(__O  uint32_t*)0xF802C028U) /**< \brief (EMAC0) Interrupt Enable Register */
  #define REG_EMAC0_IDR   (*(__O  uint32_t*)0xF802C02CU) /**< \brief (EMAC0) Interrupt Disable Register */
  #define REG_EMAC0_IMR   (*(__I  uint32_t*)0xF802C030U) /**< \brief (EMAC0) Interrupt Mask Register */
  #define REG_EMAC0_MAN   (*(__IO uint32_t*)0xF802C034U) /**< \brief (EMAC0) PHY Maintenance Register */
  #define REG_EMAC0_PTR   (*(__IO uint32_t*)0xF802C038U) /**< \brief (EMAC0) Pause Time Register */
  #define REG_EMAC0_PFR   (*(__IO uint32_t*)0xF802C03CU) /**< \brief (EMAC0) Pause Frames Received Register */
  #define REG_EMAC0_FTO   (*(__IO uint32_t*)0xF802C040U) /**< \brief (EMAC0) Frames Transmitted OK Register */
  #define REG_EMAC0_SCF   (*(__IO uint32_t*)0xF802C044U) /**< \brief (EMAC0) Single Collision Frames Register */
  #define REG_EMAC0_MCF   (*(__IO uint32_t*)0xF802C048U) /**< \brief (EMAC0) Multiple Collision Frames Register */
  #define REG_EMAC0_FRO   (*(__IO uint32_t*)0xF802C04CU) /**< \brief (EMAC0) Frames Received OK Register */
  #define REG_EMAC0_FCSE  (*(__IO uint32_t*)0xF802C050U) /**< \brief (EMAC0) Frame Check Sequence Errors Register */
  #define REG_EMAC0_ALE   (*(__IO uint32_t*)0xF802C054U) /**< \brief (EMAC0) Alignment Errors Register */
  #define REG_EMAC0_DTF   (*(__IO uint32_t*)0xF802C058U) /**< \brief (EMAC0) Deferred Transmission Frames Register */
  #define REG_EMAC0_LCOL  (*(__IO uint32_t*)0xF802C05CU) /**< \brief (EMAC0) Late Collisions Register */
  #define REG_EMAC0_ECOL  (*(__IO uint32_t*)0xF802C060U) /**< \brief (EMAC0) Excessive Collisions Register */
  #define REG_EMAC0_TUND  (*(__IO uint32_t*)0xF802C064U) /**< \brief (EMAC0) Transmit Underrun Errors Register */
  #define REG_EMAC0_CSE   (*(__IO uint32_t*)0xF802C068U) /**< \brief (EMAC0) Carrier Sense Errors Register */
  #define REG_EMAC0_RRE   (*(__IO uint32_t*)0xF802C06CU) /**< \brief (EMAC0) Receive Resource Errors Register */
  #define REG_EMAC0_ROV   (*(__IO uint32_t*)0xF802C070U) /**< \brief (EMAC0) Receive Overrun Errors Register */
  #define REG_EMAC0_RSE   (*(__IO uint32_t*)0xF802C074U) /**< \brief (EMAC0) Receive Symbol Errors Register */
  #define REG_EMAC0_ELE   (*(__IO uint32_t*)0xF802C078U) /**< \brief (EMAC0) Excessive Length Errors Register */
  #define REG_EMAC0_RJA   (*(__IO uint32_t*)0xF802C07CU) /**< \brief (EMAC0) Receive Jabbers Register */
  #define REG_EMAC0_USF   (*(__IO uint32_t*)0xF802C080U) /**< \brief (EMAC0) Undersize Frames Register */
  #define REG_EMAC0_STE   (*(__IO uint32_t*)0xF802C084U) /**< \brief (EMAC0) SQE Test Errors Register */
  #define REG_EMAC0_RLE   (*(__IO uint32_t*)0xF802C088U) /**< \brief (EMAC0) Received Length Field Mismatch Register */
  #define REG_EMAC0_TPF   (*(__IO uint32_t*)0xF802C08CU) /**< \brief (EMAC0) Transmitted Pause Frames Register */
  #define REG_EMAC0_HRB   (*(__IO uint32_t*)0xF802C090U) /**< \brief (EMAC0) Hash Register Bottom [31:0] Register */
  #define REG_EMAC0_HRT   (*(__IO uint32_t*)0xF802C094U) /**< \brief (EMAC0) Hash Register Top [63:32] Register */
  #define REG_EMAC0_SA1B  (*(__IO uint32_t*)0xF802C098U) /**< \brief (EMAC0) Specific Address 1 Bottom Register */
  #define REG_EMAC0_SA1T  (*(__IO uint32_t*)0xF802C09CU) /**< \brief (EMAC0) Specific Address 1 Top Register */
  #define REG_EMAC0_SA2B  (*(__IO uint32_t*)0xF802C0A0U) /**< \brief (EMAC0) Specific Address 2 Bottom Register */
  #define REG_EMAC0_SA2T  (*(__IO uint32_t*)0xF802C0A4U) /**< \brief (EMAC0) Specific Address 2 Top Register */
  #define REG_EMAC0_SA3B  (*(__IO uint32_t*)0xF802C0A8U) /**< \brief (EMAC0) Specific Address 3 Bottom Register */
  #define REG_EMAC0_SA3T  (*(__IO uint32_t*)0xF802C0ACU) /**< \brief (EMAC0) Specific Address 3 Top Register */
  #define REG_EMAC0_SA4B  (*(__IO uint32_t*)0xF802C0B0U) /**< \brief (EMAC0) Specific Address 4 Bottom Register */
  #define REG_EMAC0_SA4T  (*(__IO uint32_t*)0xF802C0B4U) /**< \brief (EMAC0) Specific Address 4 Top Register */
  #define REG_EMAC0_TID   (*(__IO uint32_t*)0xF802C0B8U) /**< \brief (EMAC0) Type ID Checking Register */
  #define REG_EMAC0_TPQ   (*(__IO uint32_t*)0xF802C0BCU) /**< \brief (EMAC0) Transmit Pause Quantum Register */
  #define REG_EMAC0_USRIO (*(__IO uint32_t*)0xF802C0C0U) /**< \brief (EMAC0) User Input/Output Register */
  #define REG_EMAC0_WOL   (*(__IO uint32_t*)0xF802C0C4U) /**< \brief (EMAC0) Wake-on-LAN Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_EMAC0_INSTANCE_ */
