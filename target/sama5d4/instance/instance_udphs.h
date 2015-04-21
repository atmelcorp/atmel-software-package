/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2015, Atmel Corporation                                        */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Atmel's name may not be used to endorse or promote products derived from     */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR   */
/* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE   */
/* DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,      */
/* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,  */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    */
/* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING         */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/* ---------------------------------------------------------------------------- */

#ifndef _SAMA5D4_UDPHS_INSTANCE_
#define _SAMA5D4_UDPHS_INSTANCE_

/* ========== Register definition for UDPHS peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_UDPHS_CTRL                         (0xFC02C000U) /**< \brief (UDPHS) UDPHS Control Register */
#define REG_UDPHS_FNUM                         (0xFC02C004U) /**< \brief (UDPHS) UDPHS Frame Number Register */
#define REG_UDPHS_IEN                          (0xFC02C010U) /**< \brief (UDPHS) UDPHS Interrupt Enable Register */
#define REG_UDPHS_INTSTA                       (0xFC02C014U) /**< \brief (UDPHS) UDPHS Interrupt Status Register */
#define REG_UDPHS_CLRINT                       (0xFC02C018U) /**< \brief (UDPHS) UDPHS Clear Interrupt Register */
#define REG_UDPHS_EPTRST                       (0xFC02C01CU) /**< \brief (UDPHS) UDPHS Endpoints Reset Register */
#define REG_UDPHS_TST                          (0xFC02C0E0U) /**< \brief (UDPHS) UDPHS Test Register */
#define REG_UDPHS_EPTCFG0                      (0xFC02C100U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 0) */
#define REG_UDPHS_EPTCTLENB0                   (0xFC02C104U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 0) */
#define REG_UDPHS_EPTCTLDIS0                   (0xFC02C108U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 0) */
#define REG_UDPHS_EPTCTL0                      (0xFC02C10CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 0) */
#define REG_UDPHS_EPTSETSTA0                   (0xFC02C114U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 0) */
#define REG_UDPHS_EPTCLRSTA0                   (0xFC02C118U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 0) */
#define REG_UDPHS_EPTSTA0                      (0xFC02C11CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 0) */
#define REG_UDPHS_EPTCFG1                      (0xFC02C120U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 1) */
#define REG_UDPHS_EPTCTLENB1                   (0xFC02C124U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 1) */
#define REG_UDPHS_EPTCTLDIS1                   (0xFC02C128U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 1) */
#define REG_UDPHS_EPTCTL1                      (0xFC02C12CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 1) */
#define REG_UDPHS_EPTSETSTA1                   (0xFC02C134U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 1) */
#define REG_UDPHS_EPTCLRSTA1                   (0xFC02C138U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 1) */
#define REG_UDPHS_EPTSTA1                      (0xFC02C13CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 1) */
#define REG_UDPHS_EPTCFG2                      (0xFC02C140U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 2) */
#define REG_UDPHS_EPTCTLENB2                   (0xFC02C144U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 2) */
#define REG_UDPHS_EPTCTLDIS2                   (0xFC02C148U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 2) */
#define REG_UDPHS_EPTCTL2                      (0xFC02C14CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 2) */
#define REG_UDPHS_EPTSETSTA2                   (0xFC02C154U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 2) */
#define REG_UDPHS_EPTCLRSTA2                   (0xFC02C158U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 2) */
#define REG_UDPHS_EPTSTA2                      (0xFC02C15CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 2) */
#define REG_UDPHS_EPTCFG3                      (0xFC02C160U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 3) */
#define REG_UDPHS_EPTCTLENB3                   (0xFC02C164U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 3) */
#define REG_UDPHS_EPTCTLDIS3                   (0xFC02C168U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 3) */
#define REG_UDPHS_EPTCTL3                      (0xFC02C16CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 3) */
#define REG_UDPHS_EPTSETSTA3                   (0xFC02C174U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 3) */
#define REG_UDPHS_EPTCLRSTA3                   (0xFC02C178U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 3) */
#define REG_UDPHS_EPTSTA3                      (0xFC02C17CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 3) */
#define REG_UDPHS_EPTCFG4                      (0xFC02C180U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 4) */
#define REG_UDPHS_EPTCTLENB4                   (0xFC02C184U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 4) */
#define REG_UDPHS_EPTCTLDIS4                   (0xFC02C188U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 4) */
#define REG_UDPHS_EPTCTL4                      (0xFC02C18CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 4) */
#define REG_UDPHS_EPTSETSTA4                   (0xFC02C194U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 4) */
#define REG_UDPHS_EPTCLRSTA4                   (0xFC02C198U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 4) */
#define REG_UDPHS_EPTSTA4                      (0xFC02C19CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 4) */
#define REG_UDPHS_EPTCFG5                      (0xFC02C1A0U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 5) */
#define REG_UDPHS_EPTCTLENB5                   (0xFC02C1A4U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 5) */
#define REG_UDPHS_EPTCTLDIS5                   (0xFC02C1A8U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 5) */
#define REG_UDPHS_EPTCTL5                      (0xFC02C1ACU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 5) */
#define REG_UDPHS_EPTSETSTA5                   (0xFC02C1B4U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 5) */
#define REG_UDPHS_EPTCLRSTA5                   (0xFC02C1B8U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 5) */
#define REG_UDPHS_EPTSTA5                      (0xFC02C1BCU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 5) */
#define REG_UDPHS_EPTCFG6                      (0xFC02C1C0U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 6) */
#define REG_UDPHS_EPTCTLENB6                   (0xFC02C1C4U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 6) */
#define REG_UDPHS_EPTCTLDIS6                   (0xFC02C1C8U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 6) */
#define REG_UDPHS_EPTCTL6                      (0xFC02C1CCU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 6) */
#define REG_UDPHS_EPTSETSTA6                   (0xFC02C1D4U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 6) */
#define REG_UDPHS_EPTCLRSTA6                   (0xFC02C1D8U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 6) */
#define REG_UDPHS_EPTSTA6                      (0xFC02C1DCU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 6) */
#define REG_UDPHS_EPTCFG7                      (0xFC02C1E0U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 7) */
#define REG_UDPHS_EPTCTLENB7                   (0xFC02C1E4U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 7) */
#define REG_UDPHS_EPTCTLDIS7                   (0xFC02C1E8U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 7) */
#define REG_UDPHS_EPTCTL7                      (0xFC02C1ECU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 7) */
#define REG_UDPHS_EPTSETSTA7                   (0xFC02C1F4U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 7) */
#define REG_UDPHS_EPTCLRSTA7                   (0xFC02C1F8U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 7) */
#define REG_UDPHS_EPTSTA7                      (0xFC02C1FCU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 7) */
#define REG_UDPHS_EPTCFG8                      (0xFC02C200U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 8) */
#define REG_UDPHS_EPTCTLENB8                   (0xFC02C204U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 8) */
#define REG_UDPHS_EPTCTLDIS8                   (0xFC02C208U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 8) */
#define REG_UDPHS_EPTCTL8                      (0xFC02C20CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 8) */
#define REG_UDPHS_EPTSETSTA8                   (0xFC02C214U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 8) */
#define REG_UDPHS_EPTCLRSTA8                   (0xFC02C218U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 8) */
#define REG_UDPHS_EPTSTA8                      (0xFC02C21CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 8) */
#define REG_UDPHS_EPTCFG9                      (0xFC02C220U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 9) */
#define REG_UDPHS_EPTCTLENB9                   (0xFC02C224U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 9) */
#define REG_UDPHS_EPTCTLDIS9                   (0xFC02C228U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 9) */
#define REG_UDPHS_EPTCTL9                      (0xFC02C22CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 9) */
#define REG_UDPHS_EPTSETSTA9                   (0xFC02C234U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 9) */
#define REG_UDPHS_EPTCLRSTA9                   (0xFC02C238U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 9) */
#define REG_UDPHS_EPTSTA9                      (0xFC02C23CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 9) */
#define REG_UDPHS_EPTCFG10                     (0xFC02C240U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 10) */
#define REG_UDPHS_EPTCTLENB10                  (0xFC02C244U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 10) */
#define REG_UDPHS_EPTCTLDIS10                  (0xFC02C248U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 10) */
#define REG_UDPHS_EPTCTL10                     (0xFC02C24CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 10) */
#define REG_UDPHS_EPTSETSTA10                  (0xFC02C254U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 10) */
#define REG_UDPHS_EPTCLRSTA10                  (0xFC02C258U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 10) */
#define REG_UDPHS_EPTSTA10                     (0xFC02C25CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 10) */
#define REG_UDPHS_EPTCFG11                     (0xFC02C260U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 11) */
#define REG_UDPHS_EPTCTLENB11                  (0xFC02C264U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 11) */
#define REG_UDPHS_EPTCTLDIS11                  (0xFC02C268U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 11) */
#define REG_UDPHS_EPTCTL11                     (0xFC02C26CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 11) */
#define REG_UDPHS_EPTSETSTA11                  (0xFC02C274U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 11) */
#define REG_UDPHS_EPTCLRSTA11                  (0xFC02C278U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 11) */
#define REG_UDPHS_EPTSTA11                     (0xFC02C27CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 11) */
#define REG_UDPHS_EPTCFG12                     (0xFC02C280U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 12) */
#define REG_UDPHS_EPTCTLENB12                  (0xFC02C284U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 12) */
#define REG_UDPHS_EPTCTLDIS12                  (0xFC02C288U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 12) */
#define REG_UDPHS_EPTCTL12                     (0xFC02C28CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 12) */
#define REG_UDPHS_EPTSETSTA12                  (0xFC02C294U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 12) */
#define REG_UDPHS_EPTCLRSTA12                  (0xFC02C298U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 12) */
#define REG_UDPHS_EPTSTA12                     (0xFC02C29CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 12) */
#define REG_UDPHS_EPTCFG13                     (0xFC02C2A0U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 13) */
#define REG_UDPHS_EPTCTLENB13                  (0xFC02C2A4U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 13) */
#define REG_UDPHS_EPTCTLDIS13                  (0xFC02C2A8U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 13) */
#define REG_UDPHS_EPTCTL13                     (0xFC02C2ACU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 13) */
#define REG_UDPHS_EPTSETSTA13                  (0xFC02C2B4U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 13) */
#define REG_UDPHS_EPTCLRSTA13                  (0xFC02C2B8U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 13) */
#define REG_UDPHS_EPTSTA13                     (0xFC02C2BCU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 13) */
#define REG_UDPHS_EPTCFG14                     (0xFC02C2C0U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 14) */
#define REG_UDPHS_EPTCTLENB14                  (0xFC02C2C4U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 14) */
#define REG_UDPHS_EPTCTLDIS14                  (0xFC02C2C8U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 14) */
#define REG_UDPHS_EPTCTL14                     (0xFC02C2CCU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 14) */
#define REG_UDPHS_EPTSETSTA14                  (0xFC02C2D4U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 14) */
#define REG_UDPHS_EPTCLRSTA14                  (0xFC02C2D8U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 14) */
#define REG_UDPHS_EPTSTA14                     (0xFC02C2DCU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 14) */
#define REG_UDPHS_EPTCFG15                     (0xFC02C2E0U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 15) */
#define REG_UDPHS_EPTCTLENB15                  (0xFC02C2E4U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 15) */
#define REG_UDPHS_EPTCTLDIS15                  (0xFC02C2E8U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 15) */
#define REG_UDPHS_EPTCTL15                     (0xFC02C2ECU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 15) */
#define REG_UDPHS_EPTSETSTA15                  (0xFC02C2F4U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 15) */
#define REG_UDPHS_EPTCLRSTA15                  (0xFC02C2F8U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 15) */
#define REG_UDPHS_EPTSTA15                     (0xFC02C2FCU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 15) */
#define REG_UDPHS_DMANXTDSC0                   (0xFC02C300U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 0) */
#define REG_UDPHS_DMAADDRESS0                  (0xFC02C304U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 0) */
#define REG_UDPHS_DMACONTROL0                  (0xFC02C308U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 0) */
#define REG_UDPHS_DMASTATUS0                   (0xFC02C30CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 0) */
#define REG_UDPHS_DMANXTDSC1                   (0xFC02C310U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 1) */
#define REG_UDPHS_DMAADDRESS1                  (0xFC02C314U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 1) */
#define REG_UDPHS_DMACONTROL1                  (0xFC02C318U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 1) */
#define REG_UDPHS_DMASTATUS1                   (0xFC02C31CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 1) */
#define REG_UDPHS_DMANXTDSC2                   (0xFC02C320U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 2) */
#define REG_UDPHS_DMAADDRESS2                  (0xFC02C324U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 2) */
#define REG_UDPHS_DMACONTROL2                  (0xFC02C328U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 2) */
#define REG_UDPHS_DMASTATUS2                   (0xFC02C32CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 2) */
#define REG_UDPHS_DMANXTDSC3                   (0xFC02C330U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 3) */
#define REG_UDPHS_DMAADDRESS3                  (0xFC02C334U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 3) */
#define REG_UDPHS_DMACONTROL3                  (0xFC02C338U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 3) */
#define REG_UDPHS_DMASTATUS3                   (0xFC02C33CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 3) */
#define REG_UDPHS_DMANXTDSC4                   (0xFC02C340U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 4) */
#define REG_UDPHS_DMAADDRESS4                  (0xFC02C344U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 4) */
#define REG_UDPHS_DMACONTROL4                  (0xFC02C348U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 4) */
#define REG_UDPHS_DMASTATUS4                   (0xFC02C34CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 4) */
#define REG_UDPHS_DMANXTDSC5                   (0xFC02C350U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 5) */
#define REG_UDPHS_DMAADDRESS5                  (0xFC02C354U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 5) */
#define REG_UDPHS_DMACONTROL5                  (0xFC02C358U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 5) */
#define REG_UDPHS_DMASTATUS5                   (0xFC02C35CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 5) */
#define REG_UDPHS_DMANXTDSC6                   (0xFC02C360U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 6) */
#define REG_UDPHS_DMAADDRESS6                  (0xFC02C364U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 6) */
#define REG_UDPHS_DMACONTROL6                  (0xFC02C368U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 6) */
#define REG_UDPHS_DMASTATUS6                   (0xFC02C36CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 6) */
#else
#define REG_UDPHS_CTRL        (*(__IO uint32_t*)0xFC02C000U) /**< \brief (UDPHS) UDPHS Control Register */
#define REG_UDPHS_FNUM        (*(__I  uint32_t*)0xFC02C004U) /**< \brief (UDPHS) UDPHS Frame Number Register */
#define REG_UDPHS_IEN         (*(__IO uint32_t*)0xFC02C010U) /**< \brief (UDPHS) UDPHS Interrupt Enable Register */
#define REG_UDPHS_INTSTA      (*(__I  uint32_t*)0xFC02C014U) /**< \brief (UDPHS) UDPHS Interrupt Status Register */
#define REG_UDPHS_CLRINT      (*(__O  uint32_t*)0xFC02C018U) /**< \brief (UDPHS) UDPHS Clear Interrupt Register */
#define REG_UDPHS_EPTRST      (*(__O  uint32_t*)0xFC02C01CU) /**< \brief (UDPHS) UDPHS Endpoints Reset Register */
#define REG_UDPHS_TST         (*(__IO uint32_t*)0xFC02C0E0U) /**< \brief (UDPHS) UDPHS Test Register */
#define REG_UDPHS_EPTCFG0     (*(__IO uint32_t*)0xFC02C100U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 0) */
#define REG_UDPHS_EPTCTLENB0  (*(__O  uint32_t*)0xFC02C104U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 0) */
#define REG_UDPHS_EPTCTLDIS0  (*(__O  uint32_t*)0xFC02C108U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 0) */
#define REG_UDPHS_EPTCTL0     (*(__I  uint32_t*)0xFC02C10CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 0) */
#define REG_UDPHS_EPTSETSTA0  (*(__O  uint32_t*)0xFC02C114U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 0) */
#define REG_UDPHS_EPTCLRSTA0  (*(__O  uint32_t*)0xFC02C118U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 0) */
#define REG_UDPHS_EPTSTA0     (*(__I  uint32_t*)0xFC02C11CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 0) */
#define REG_UDPHS_EPTCFG1     (*(__IO uint32_t*)0xFC02C120U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 1) */
#define REG_UDPHS_EPTCTLENB1  (*(__O  uint32_t*)0xFC02C124U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 1) */
#define REG_UDPHS_EPTCTLDIS1  (*(__O  uint32_t*)0xFC02C128U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 1) */
#define REG_UDPHS_EPTCTL1     (*(__I  uint32_t*)0xFC02C12CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 1) */
#define REG_UDPHS_EPTSETSTA1  (*(__O  uint32_t*)0xFC02C134U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 1) */
#define REG_UDPHS_EPTCLRSTA1  (*(__O  uint32_t*)0xFC02C138U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 1) */
#define REG_UDPHS_EPTSTA1     (*(__I  uint32_t*)0xFC02C13CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 1) */
#define REG_UDPHS_EPTCFG2     (*(__IO uint32_t*)0xFC02C140U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 2) */
#define REG_UDPHS_EPTCTLENB2  (*(__O  uint32_t*)0xFC02C144U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 2) */
#define REG_UDPHS_EPTCTLDIS2  (*(__O  uint32_t*)0xFC02C148U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 2) */
#define REG_UDPHS_EPTCTL2     (*(__I  uint32_t*)0xFC02C14CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 2) */
#define REG_UDPHS_EPTSETSTA2  (*(__O  uint32_t*)0xFC02C154U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 2) */
#define REG_UDPHS_EPTCLRSTA2  (*(__O  uint32_t*)0xFC02C158U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 2) */
#define REG_UDPHS_EPTSTA2     (*(__I  uint32_t*)0xFC02C15CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 2) */
#define REG_UDPHS_EPTCFG3     (*(__IO uint32_t*)0xFC02C160U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 3) */
#define REG_UDPHS_EPTCTLENB3  (*(__O  uint32_t*)0xFC02C164U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 3) */
#define REG_UDPHS_EPTCTLDIS3  (*(__O  uint32_t*)0xFC02C168U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 3) */
#define REG_UDPHS_EPTCTL3     (*(__I  uint32_t*)0xFC02C16CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 3) */
#define REG_UDPHS_EPTSETSTA3  (*(__O  uint32_t*)0xFC02C174U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 3) */
#define REG_UDPHS_EPTCLRSTA3  (*(__O  uint32_t*)0xFC02C178U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 3) */
#define REG_UDPHS_EPTSTA3     (*(__I  uint32_t*)0xFC02C17CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 3) */
#define REG_UDPHS_EPTCFG4     (*(__IO uint32_t*)0xFC02C180U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 4) */
#define REG_UDPHS_EPTCTLENB4  (*(__O  uint32_t*)0xFC02C184U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 4) */
#define REG_UDPHS_EPTCTLDIS4  (*(__O  uint32_t*)0xFC02C188U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 4) */
#define REG_UDPHS_EPTCTL4     (*(__I  uint32_t*)0xFC02C18CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 4) */
#define REG_UDPHS_EPTSETSTA4  (*(__O  uint32_t*)0xFC02C194U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 4) */
#define REG_UDPHS_EPTCLRSTA4  (*(__O  uint32_t*)0xFC02C198U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 4) */
#define REG_UDPHS_EPTSTA4     (*(__I  uint32_t*)0xFC02C19CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 4) */
#define REG_UDPHS_EPTCFG5     (*(__IO uint32_t*)0xFC02C1A0U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 5) */
#define REG_UDPHS_EPTCTLENB5  (*(__O  uint32_t*)0xFC02C1A4U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 5) */
#define REG_UDPHS_EPTCTLDIS5  (*(__O  uint32_t*)0xFC02C1A8U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 5) */
#define REG_UDPHS_EPTCTL5     (*(__I  uint32_t*)0xFC02C1ACU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 5) */
#define REG_UDPHS_EPTSETSTA5  (*(__O  uint32_t*)0xFC02C1B4U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 5) */
#define REG_UDPHS_EPTCLRSTA5  (*(__O  uint32_t*)0xFC02C1B8U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 5) */
#define REG_UDPHS_EPTSTA5     (*(__I  uint32_t*)0xFC02C1BCU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 5) */
#define REG_UDPHS_EPTCFG6     (*(__IO uint32_t*)0xFC02C1C0U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 6) */
#define REG_UDPHS_EPTCTLENB6  (*(__O  uint32_t*)0xFC02C1C4U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 6) */
#define REG_UDPHS_EPTCTLDIS6  (*(__O  uint32_t*)0xFC02C1C8U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 6) */
#define REG_UDPHS_EPTCTL6     (*(__I  uint32_t*)0xFC02C1CCU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 6) */
#define REG_UDPHS_EPTSETSTA6  (*(__O  uint32_t*)0xFC02C1D4U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 6) */
#define REG_UDPHS_EPTCLRSTA6  (*(__O  uint32_t*)0xFC02C1D8U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 6) */
#define REG_UDPHS_EPTSTA6     (*(__I  uint32_t*)0xFC02C1DCU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 6) */
#define REG_UDPHS_EPTCFG7     (*(__IO uint32_t*)0xFC02C1E0U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 7) */
#define REG_UDPHS_EPTCTLENB7  (*(__O  uint32_t*)0xFC02C1E4U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 7) */
#define REG_UDPHS_EPTCTLDIS7  (*(__O  uint32_t*)0xFC02C1E8U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 7) */
#define REG_UDPHS_EPTCTL7     (*(__I  uint32_t*)0xFC02C1ECU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 7) */
#define REG_UDPHS_EPTSETSTA7  (*(__O  uint32_t*)0xFC02C1F4U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 7) */
#define REG_UDPHS_EPTCLRSTA7  (*(__O  uint32_t*)0xFC02C1F8U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 7) */
#define REG_UDPHS_EPTSTA7     (*(__I  uint32_t*)0xFC02C1FCU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 7) */
#define REG_UDPHS_EPTCFG8     (*(__IO uint32_t*)0xFC02C200U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 8) */
#define REG_UDPHS_EPTCTLENB8  (*(__O  uint32_t*)0xFC02C204U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 8) */
#define REG_UDPHS_EPTCTLDIS8  (*(__O  uint32_t*)0xFC02C208U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 8) */
#define REG_UDPHS_EPTCTL8     (*(__I  uint32_t*)0xFC02C20CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 8) */
#define REG_UDPHS_EPTSETSTA8  (*(__O  uint32_t*)0xFC02C214U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 8) */
#define REG_UDPHS_EPTCLRSTA8  (*(__O  uint32_t*)0xFC02C218U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 8) */
#define REG_UDPHS_EPTSTA8     (*(__I  uint32_t*)0xFC02C21CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 8) */
#define REG_UDPHS_EPTCFG9     (*(__IO uint32_t*)0xFC02C220U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 9) */
#define REG_UDPHS_EPTCTLENB9  (*(__O  uint32_t*)0xFC02C224U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 9) */
#define REG_UDPHS_EPTCTLDIS9  (*(__O  uint32_t*)0xFC02C228U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 9) */
#define REG_UDPHS_EPTCTL9     (*(__I  uint32_t*)0xFC02C22CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 9) */
#define REG_UDPHS_EPTSETSTA9  (*(__O  uint32_t*)0xFC02C234U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 9) */
#define REG_UDPHS_EPTCLRSTA9  (*(__O  uint32_t*)0xFC02C238U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 9) */
#define REG_UDPHS_EPTSTA9     (*(__I  uint32_t*)0xFC02C23CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 9) */
#define REG_UDPHS_EPTCFG10    (*(__IO uint32_t*)0xFC02C240U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 10) */
#define REG_UDPHS_EPTCTLENB10 (*(__O  uint32_t*)0xFC02C244U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 10) */
#define REG_UDPHS_EPTCTLDIS10 (*(__O  uint32_t*)0xFC02C248U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 10) */
#define REG_UDPHS_EPTCTL10    (*(__I  uint32_t*)0xFC02C24CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 10) */
#define REG_UDPHS_EPTSETSTA10 (*(__O  uint32_t*)0xFC02C254U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 10) */
#define REG_UDPHS_EPTCLRSTA10 (*(__O  uint32_t*)0xFC02C258U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 10) */
#define REG_UDPHS_EPTSTA10    (*(__I  uint32_t*)0xFC02C25CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 10) */
#define REG_UDPHS_EPTCFG11    (*(__IO uint32_t*)0xFC02C260U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 11) */
#define REG_UDPHS_EPTCTLENB11 (*(__O  uint32_t*)0xFC02C264U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 11) */
#define REG_UDPHS_EPTCTLDIS11 (*(__O  uint32_t*)0xFC02C268U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 11) */
#define REG_UDPHS_EPTCTL11    (*(__I  uint32_t*)0xFC02C26CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 11) */
#define REG_UDPHS_EPTSETSTA11 (*(__O  uint32_t*)0xFC02C274U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 11) */
#define REG_UDPHS_EPTCLRSTA11 (*(__O  uint32_t*)0xFC02C278U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 11) */
#define REG_UDPHS_EPTSTA11    (*(__I  uint32_t*)0xFC02C27CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 11) */
#define REG_UDPHS_EPTCFG12    (*(__IO uint32_t*)0xFC02C280U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 12) */
#define REG_UDPHS_EPTCTLENB12 (*(__O  uint32_t*)0xFC02C284U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 12) */
#define REG_UDPHS_EPTCTLDIS12 (*(__O  uint32_t*)0xFC02C288U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 12) */
#define REG_UDPHS_EPTCTL12    (*(__I  uint32_t*)0xFC02C28CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 12) */
#define REG_UDPHS_EPTSETSTA12 (*(__O  uint32_t*)0xFC02C294U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 12) */
#define REG_UDPHS_EPTCLRSTA12 (*(__O  uint32_t*)0xFC02C298U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 12) */
#define REG_UDPHS_EPTSTA12    (*(__I  uint32_t*)0xFC02C29CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 12) */
#define REG_UDPHS_EPTCFG13    (*(__IO uint32_t*)0xFC02C2A0U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 13) */
#define REG_UDPHS_EPTCTLENB13 (*(__O  uint32_t*)0xFC02C2A4U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 13) */
#define REG_UDPHS_EPTCTLDIS13 (*(__O  uint32_t*)0xFC02C2A8U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 13) */
#define REG_UDPHS_EPTCTL13    (*(__I  uint32_t*)0xFC02C2ACU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 13) */
#define REG_UDPHS_EPTSETSTA13 (*(__O  uint32_t*)0xFC02C2B4U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 13) */
#define REG_UDPHS_EPTCLRSTA13 (*(__O  uint32_t*)0xFC02C2B8U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 13) */
#define REG_UDPHS_EPTSTA13    (*(__I  uint32_t*)0xFC02C2BCU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 13) */
#define REG_UDPHS_EPTCFG14    (*(__IO uint32_t*)0xFC02C2C0U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 14) */
#define REG_UDPHS_EPTCTLENB14 (*(__O  uint32_t*)0xFC02C2C4U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 14) */
#define REG_UDPHS_EPTCTLDIS14 (*(__O  uint32_t*)0xFC02C2C8U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 14) */
#define REG_UDPHS_EPTCTL14    (*(__I  uint32_t*)0xFC02C2CCU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 14) */
#define REG_UDPHS_EPTSETSTA14 (*(__O  uint32_t*)0xFC02C2D4U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 14) */
#define REG_UDPHS_EPTCLRSTA14 (*(__O  uint32_t*)0xFC02C2D8U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 14) */
#define REG_UDPHS_EPTSTA14    (*(__I  uint32_t*)0xFC02C2DCU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 14) */
#define REG_UDPHS_EPTCFG15    (*(__IO uint32_t*)0xFC02C2E0U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 15) */
#define REG_UDPHS_EPTCTLENB15 (*(__O  uint32_t*)0xFC02C2E4U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 15) */
#define REG_UDPHS_EPTCTLDIS15 (*(__O  uint32_t*)0xFC02C2E8U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 15) */
#define REG_UDPHS_EPTCTL15    (*(__I  uint32_t*)0xFC02C2ECU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 15) */
#define REG_UDPHS_EPTSETSTA15 (*(__O  uint32_t*)0xFC02C2F4U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 15) */
#define REG_UDPHS_EPTCLRSTA15 (*(__O  uint32_t*)0xFC02C2F8U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 15) */
#define REG_UDPHS_EPTSTA15    (*(__I  uint32_t*)0xFC02C2FCU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 15) */
#define REG_UDPHS_DMANXTDSC0  (*(__IO uint32_t*)0xFC02C300U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 0) */
#define REG_UDPHS_DMAADDRESS0 (*(__IO uint32_t*)0xFC02C304U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 0) */
#define REG_UDPHS_DMACONTROL0 (*(__IO uint32_t*)0xFC02C308U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 0) */
#define REG_UDPHS_DMASTATUS0  (*(__IO uint32_t*)0xFC02C30CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 0) */
#define REG_UDPHS_DMANXTDSC1  (*(__IO uint32_t*)0xFC02C310U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 1) */
#define REG_UDPHS_DMAADDRESS1 (*(__IO uint32_t*)0xFC02C314U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 1) */
#define REG_UDPHS_DMACONTROL1 (*(__IO uint32_t*)0xFC02C318U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 1) */
#define REG_UDPHS_DMASTATUS1  (*(__IO uint32_t*)0xFC02C31CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 1) */
#define REG_UDPHS_DMANXTDSC2  (*(__IO uint32_t*)0xFC02C320U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 2) */
#define REG_UDPHS_DMAADDRESS2 (*(__IO uint32_t*)0xFC02C324U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 2) */
#define REG_UDPHS_DMACONTROL2 (*(__IO uint32_t*)0xFC02C328U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 2) */
#define REG_UDPHS_DMASTATUS2  (*(__IO uint32_t*)0xFC02C32CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 2) */
#define REG_UDPHS_DMANXTDSC3  (*(__IO uint32_t*)0xFC02C330U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 3) */
#define REG_UDPHS_DMAADDRESS3 (*(__IO uint32_t*)0xFC02C334U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 3) */
#define REG_UDPHS_DMACONTROL3 (*(__IO uint32_t*)0xFC02C338U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 3) */
#define REG_UDPHS_DMASTATUS3  (*(__IO uint32_t*)0xFC02C33CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 3) */
#define REG_UDPHS_DMANXTDSC4  (*(__IO uint32_t*)0xFC02C340U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 4) */
#define REG_UDPHS_DMAADDRESS4 (*(__IO uint32_t*)0xFC02C344U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 4) */
#define REG_UDPHS_DMACONTROL4 (*(__IO uint32_t*)0xFC02C348U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 4) */
#define REG_UDPHS_DMASTATUS4  (*(__IO uint32_t*)0xFC02C34CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 4) */
#define REG_UDPHS_DMANXTDSC5  (*(__IO uint32_t*)0xFC02C350U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 5) */
#define REG_UDPHS_DMAADDRESS5 (*(__IO uint32_t*)0xFC02C354U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 5) */
#define REG_UDPHS_DMACONTROL5 (*(__IO uint32_t*)0xFC02C358U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 5) */
#define REG_UDPHS_DMASTATUS5  (*(__IO uint32_t*)0xFC02C35CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 5) */
#define REG_UDPHS_DMANXTDSC6  (*(__IO uint32_t*)0xFC02C360U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 6) */
#define REG_UDPHS_DMAADDRESS6 (*(__IO uint32_t*)0xFC02C364U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 6) */
#define REG_UDPHS_DMACONTROL6 (*(__IO uint32_t*)0xFC02C368U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 6) */
#define REG_UDPHS_DMASTATUS6  (*(__IO uint32_t*)0xFC02C36CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 6) */
#endif				/* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif				/* _SAMA5D4_UDPHS_INSTANCE_ */
