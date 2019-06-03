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

#ifndef _SAM9X_UDPHS_INSTANCE_
#define _SAM9X_UDPHS_INSTANCE_

/* ========== Register definition for UDPHS peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_UDPHS_CTRL                         (0xF803C000U) /**< \brief (UDPHS) UDPHS Control Register */
  #define REG_UDPHS_FNUM                         (0xF803C004U) /**< \brief (UDPHS) UDPHS Frame Number Register */
  #define REG_UDPHS_IEN                          (0xF803C010U) /**< \brief (UDPHS) UDPHS Interrupt Enable Register */
  #define REG_UDPHS_INTSTA                       (0xF803C014U) /**< \brief (UDPHS) UDPHS Interrupt Status Register */
  #define REG_UDPHS_CLRINT                       (0xF803C018U) /**< \brief (UDPHS) UDPHS Clear Interrupt Register */
  #define REG_UDPHS_EPTRST                       (0xF803C01CU) /**< \brief (UDPHS) UDPHS Endpoints Reset Register */
  #define REG_UDPHS_TSTSOFCNT                    (0xF803C0D0U) /**< \brief (UDPHS) UDPHS Test SOF Counter Register */
  #define REG_UDPHS_TSTCNTA                      (0xF803C0D4U) /**< \brief (UDPHS) UDPHS Test A Counter Register */
  #define REG_UDPHS_TSTCNTB                      (0xF803C0D8U) /**< \brief (UDPHS) UDPHS Test B Counter Register */
  #define REG_UDPHS_TSTMODEREG                   (0xF803C0DCU) /**< \brief (UDPHS) UDPHS Test Mode Register */
  #define REG_UDPHS_TST                          (0xF803C0E0U) /**< \brief (UDPHS) UDPHS Test Register */
  #define REG_UDPHS_EPTCFG0                      (0xF803C100U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 0) */
  #define REG_UDPHS_EPTCTLENB0                   (0xF803C104U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 0) */
  #define REG_UDPHS_EPTCTLDIS0                   (0xF803C108U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 0) */
  #define REG_UDPHS_EPTCTL0                      (0xF803C10CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 0) */
  #define REG_UDPHS_EPTSETSTA0                   (0xF803C114U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 0) */
  #define REG_UDPHS_EPTCLRSTA0                   (0xF803C118U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 0) */
  #define REG_UDPHS_EPTSTA0                      (0xF803C11CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 0) */
  #define REG_UDPHS_EPTCFG1                      (0xF803C120U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 1) */
  #define REG_UDPHS_EPTCTLENB1                   (0xF803C124U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 1) */
  #define REG_UDPHS_EPTCTLDIS1                   (0xF803C128U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 1) */
  #define REG_UDPHS_EPTCTL1                      (0xF803C12CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 1) */
  #define REG_UDPHS_EPTSETSTA1                   (0xF803C134U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 1) */
  #define REG_UDPHS_EPTCLRSTA1                   (0xF803C138U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 1) */
  #define REG_UDPHS_EPTSTA1                      (0xF803C13CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 1) */
  #define REG_UDPHS_EPTCFG2                      (0xF803C140U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 2) */
  #define REG_UDPHS_EPTCTLENB2                   (0xF803C144U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 2) */
  #define REG_UDPHS_EPTCTLDIS2                   (0xF803C148U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 2) */
  #define REG_UDPHS_EPTCTL2                      (0xF803C14CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 2) */
  #define REG_UDPHS_EPTSETSTA2                   (0xF803C154U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 2) */
  #define REG_UDPHS_EPTCLRSTA2                   (0xF803C158U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 2) */
  #define REG_UDPHS_EPTSTA2                      (0xF803C15CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 2) */
  #define REG_UDPHS_EPTCFG3                      (0xF803C160U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 3) */
  #define REG_UDPHS_EPTCTLENB3                   (0xF803C164U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 3) */
  #define REG_UDPHS_EPTCTLDIS3                   (0xF803C168U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 3) */
  #define REG_UDPHS_EPTCTL3                      (0xF803C16CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 3) */
  #define REG_UDPHS_EPTSETSTA3                   (0xF803C174U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 3) */
  #define REG_UDPHS_EPTCLRSTA3                   (0xF803C178U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 3) */
  #define REG_UDPHS_EPTSTA3                      (0xF803C17CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 3) */
  #define REG_UDPHS_EPTCFG4                      (0xF803C180U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 4) */
  #define REG_UDPHS_EPTCTLENB4                   (0xF803C184U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 4) */
  #define REG_UDPHS_EPTCTLDIS4                   (0xF803C188U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 4) */
  #define REG_UDPHS_EPTCTL4                      (0xF803C18CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 4) */
  #define REG_UDPHS_EPTSETSTA4                   (0xF803C194U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 4) */
  #define REG_UDPHS_EPTCLRSTA4                   (0xF803C198U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 4) */
  #define REG_UDPHS_EPTSTA4                      (0xF803C19CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 4) */
  #define REG_UDPHS_EPTCFG5                      (0xF803C1A0U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 5) */
  #define REG_UDPHS_EPTCTLENB5                   (0xF803C1A4U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 5) */
  #define REG_UDPHS_EPTCTLDIS5                   (0xF803C1A8U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 5) */
  #define REG_UDPHS_EPTCTL5                      (0xF803C1ACU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 5) */
  #define REG_UDPHS_EPTSETSTA5                   (0xF803C1B4U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 5) */
  #define REG_UDPHS_EPTCLRSTA5                   (0xF803C1B8U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 5) */
  #define REG_UDPHS_EPTSTA5                      (0xF803C1BCU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 5) */
  #define REG_UDPHS_EPTCFG6                      (0xF803C1C0U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 6) */
  #define REG_UDPHS_EPTCTLENB6                   (0xF803C1C4U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 6) */
  #define REG_UDPHS_EPTCTLDIS6                   (0xF803C1C8U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 6) */
  #define REG_UDPHS_EPTCTL6                      (0xF803C1CCU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 6) */
  #define REG_UDPHS_EPTSETSTA6                   (0xF803C1D4U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 6) */
  #define REG_UDPHS_EPTCLRSTA6                   (0xF803C1D8U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 6) */
  #define REG_UDPHS_EPTSTA6                      (0xF803C1DCU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 6) */
  #define REG_UDPHS_DMANXTDSC0                   (0xF803C300U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 0) */
  #define REG_UDPHS_DMAADDRESS0                  (0xF803C304U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 0) */
  #define REG_UDPHS_DMACONTROL0                  (0xF803C308U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 0) */
  #define REG_UDPHS_DMASTATUS0                   (0xF803C30CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 0) */
  #define REG_UDPHS_DMANXTDSC1                   (0xF803C310U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 1) */
  #define REG_UDPHS_DMAADDRESS1                  (0xF803C314U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 1) */
  #define REG_UDPHS_DMACONTROL1                  (0xF803C318U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 1) */
  #define REG_UDPHS_DMASTATUS1                   (0xF803C31CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 1) */
  #define REG_UDPHS_DMANXTDSC2                   (0xF803C320U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 2) */
  #define REG_UDPHS_DMAADDRESS2                  (0xF803C324U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 2) */
  #define REG_UDPHS_DMACONTROL2                  (0xF803C328U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 2) */
  #define REG_UDPHS_DMASTATUS2                   (0xF803C32CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 2) */
  #define REG_UDPHS_DMANXTDSC3                   (0xF803C330U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 3) */
  #define REG_UDPHS_DMAADDRESS3                  (0xF803C334U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 3) */
  #define REG_UDPHS_DMACONTROL3                  (0xF803C338U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 3) */
  #define REG_UDPHS_DMASTATUS3                   (0xF803C33CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 3) */
  #define REG_UDPHS_DMANXTDSC4                   (0xF803C340U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 4) */
  #define REG_UDPHS_DMAADDRESS4                  (0xF803C344U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 4) */
  #define REG_UDPHS_DMACONTROL4                  (0xF803C348U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 4) */
  #define REG_UDPHS_DMASTATUS4                   (0xF803C34CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 4) */
  #define REG_UDPHS_DMANXTDSC5                   (0xF803C350U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 5) */
  #define REG_UDPHS_DMAADDRESS5                  (0xF803C354U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 5) */
  #define REG_UDPHS_DMACONTROL5                  (0xF803C358U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 5) */
  #define REG_UDPHS_DMASTATUS5                   (0xF803C35CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 5) */
  #define REG_UDPHS_DMANXTDSC6                   (0xF803C360U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 6) */
  #define REG_UDPHS_DMAADDRESS6                  (0xF803C364U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 6) */
  #define REG_UDPHS_DMACONTROL6                  (0xF803C368U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 6) */
  #define REG_UDPHS_DMASTATUS6                   (0xF803C36CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 6) */
#else
  #define REG_UDPHS_CTRL        (*(__IO uint32_t*)0xF803C000U) /**< \brief (UDPHS) UDPHS Control Register */
  #define REG_UDPHS_FNUM        (*(__I  uint32_t*)0xF803C004U) /**< \brief (UDPHS) UDPHS Frame Number Register */
  #define REG_UDPHS_IEN         (*(__IO uint32_t*)0xF803C010U) /**< \brief (UDPHS) UDPHS Interrupt Enable Register */
  #define REG_UDPHS_INTSTA      (*(__I  uint32_t*)0xF803C014U) /**< \brief (UDPHS) UDPHS Interrupt Status Register */
  #define REG_UDPHS_CLRINT      (*(__O  uint32_t*)0xF803C018U) /**< \brief (UDPHS) UDPHS Clear Interrupt Register */
  #define REG_UDPHS_EPTRST      (*(__O  uint32_t*)0xF803C01CU) /**< \brief (UDPHS) UDPHS Endpoints Reset Register */
  #define REG_UDPHS_TSTSOFCNT   (*(__IO uint32_t*)0xF803C0D0U) /**< \brief (UDPHS) UDPHS Test SOF Counter Register */
  #define REG_UDPHS_TSTCNTA     (*(__IO uint32_t*)0xF803C0D4U) /**< \brief (UDPHS) UDPHS Test A Counter Register */
  #define REG_UDPHS_TSTCNTB     (*(__IO uint32_t*)0xF803C0D8U) /**< \brief (UDPHS) UDPHS Test B Counter Register */
  #define REG_UDPHS_TSTMODEREG  (*(__IO uint32_t*)0xF803C0DCU) /**< \brief (UDPHS) UDPHS Test Mode Register */
  #define REG_UDPHS_TST         (*(__IO uint32_t*)0xF803C0E0U) /**< \brief (UDPHS) UDPHS Test Register */
  #define REG_UDPHS_EPTCFG0     (*(__IO uint32_t*)0xF803C100U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 0) */
  #define REG_UDPHS_EPTCTLENB0  (*(__O  uint32_t*)0xF803C104U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 0) */
  #define REG_UDPHS_EPTCTLDIS0  (*(__O  uint32_t*)0xF803C108U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 0) */
  #define REG_UDPHS_EPTCTL0     (*(__I  uint32_t*)0xF803C10CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 0) */
  #define REG_UDPHS_EPTSETSTA0  (*(__O  uint32_t*)0xF803C114U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 0) */
  #define REG_UDPHS_EPTCLRSTA0  (*(__O  uint32_t*)0xF803C118U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 0) */
  #define REG_UDPHS_EPTSTA0     (*(__I  uint32_t*)0xF803C11CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 0) */
  #define REG_UDPHS_EPTCFG1     (*(__IO uint32_t*)0xF803C120U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 1) */
  #define REG_UDPHS_EPTCTLENB1  (*(__O  uint32_t*)0xF803C124U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 1) */
  #define REG_UDPHS_EPTCTLDIS1  (*(__O  uint32_t*)0xF803C128U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 1) */
  #define REG_UDPHS_EPTCTL1     (*(__I  uint32_t*)0xF803C12CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 1) */
  #define REG_UDPHS_EPTSETSTA1  (*(__O  uint32_t*)0xF803C134U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 1) */
  #define REG_UDPHS_EPTCLRSTA1  (*(__O  uint32_t*)0xF803C138U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 1) */
  #define REG_UDPHS_EPTSTA1     (*(__I  uint32_t*)0xF803C13CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 1) */
  #define REG_UDPHS_EPTCFG2     (*(__IO uint32_t*)0xF803C140U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 2) */
  #define REG_UDPHS_EPTCTLENB2  (*(__O  uint32_t*)0xF803C144U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 2) */
  #define REG_UDPHS_EPTCTLDIS2  (*(__O  uint32_t*)0xF803C148U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 2) */
  #define REG_UDPHS_EPTCTL2     (*(__I  uint32_t*)0xF803C14CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 2) */
  #define REG_UDPHS_EPTSETSTA2  (*(__O  uint32_t*)0xF803C154U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 2) */
  #define REG_UDPHS_EPTCLRSTA2  (*(__O  uint32_t*)0xF803C158U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 2) */
  #define REG_UDPHS_EPTSTA2     (*(__I  uint32_t*)0xF803C15CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 2) */
  #define REG_UDPHS_EPTCFG3     (*(__IO uint32_t*)0xF803C160U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 3) */
  #define REG_UDPHS_EPTCTLENB3  (*(__O  uint32_t*)0xF803C164U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 3) */
  #define REG_UDPHS_EPTCTLDIS3  (*(__O  uint32_t*)0xF803C168U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 3) */
  #define REG_UDPHS_EPTCTL3     (*(__I  uint32_t*)0xF803C16CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 3) */
  #define REG_UDPHS_EPTSETSTA3  (*(__O  uint32_t*)0xF803C174U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 3) */
  #define REG_UDPHS_EPTCLRSTA3  (*(__O  uint32_t*)0xF803C178U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 3) */
  #define REG_UDPHS_EPTSTA3     (*(__I  uint32_t*)0xF803C17CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 3) */
  #define REG_UDPHS_EPTCFG4     (*(__IO uint32_t*)0xF803C180U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 4) */
  #define REG_UDPHS_EPTCTLENB4  (*(__O  uint32_t*)0xF803C184U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 4) */
  #define REG_UDPHS_EPTCTLDIS4  (*(__O  uint32_t*)0xF803C188U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 4) */
  #define REG_UDPHS_EPTCTL4     (*(__I  uint32_t*)0xF803C18CU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 4) */
  #define REG_UDPHS_EPTSETSTA4  (*(__O  uint32_t*)0xF803C194U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 4) */
  #define REG_UDPHS_EPTCLRSTA4  (*(__O  uint32_t*)0xF803C198U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 4) */
  #define REG_UDPHS_EPTSTA4     (*(__I  uint32_t*)0xF803C19CU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 4) */
  #define REG_UDPHS_EPTCFG5     (*(__IO uint32_t*)0xF803C1A0U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 5) */
  #define REG_UDPHS_EPTCTLENB5  (*(__O  uint32_t*)0xF803C1A4U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 5) */
  #define REG_UDPHS_EPTCTLDIS5  (*(__O  uint32_t*)0xF803C1A8U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 5) */
  #define REG_UDPHS_EPTCTL5     (*(__I  uint32_t*)0xF803C1ACU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 5) */
  #define REG_UDPHS_EPTSETSTA5  (*(__O  uint32_t*)0xF803C1B4U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 5) */
  #define REG_UDPHS_EPTCLRSTA5  (*(__O  uint32_t*)0xF803C1B8U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 5) */
  #define REG_UDPHS_EPTSTA5     (*(__I  uint32_t*)0xF803C1BCU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 5) */
  #define REG_UDPHS_EPTCFG6     (*(__IO uint32_t*)0xF803C1C0U) /**< \brief (UDPHS) UDPHS Endpoint Configuration Register (endpoint = 6) */
  #define REG_UDPHS_EPTCTLENB6  (*(__O  uint32_t*)0xF803C1C4U) /**< \brief (UDPHS) UDPHS Endpoint Control Enable Register (endpoint = 6) */
  #define REG_UDPHS_EPTCTLDIS6  (*(__O  uint32_t*)0xF803C1C8U) /**< \brief (UDPHS) UDPHS Endpoint Control Disable Register (endpoint = 6) */
  #define REG_UDPHS_EPTCTL6     (*(__I  uint32_t*)0xF803C1CCU) /**< \brief (UDPHS) UDPHS Endpoint Control Register (endpoint = 6) */
  #define REG_UDPHS_EPTSETSTA6  (*(__O  uint32_t*)0xF803C1D4U) /**< \brief (UDPHS) UDPHS Endpoint Set Status Register (endpoint = 6) */
  #define REG_UDPHS_EPTCLRSTA6  (*(__O  uint32_t*)0xF803C1D8U) /**< \brief (UDPHS) UDPHS Endpoint Clear Status Register (endpoint = 6) */
  #define REG_UDPHS_EPTSTA6     (*(__I  uint32_t*)0xF803C1DCU) /**< \brief (UDPHS) UDPHS Endpoint Status Register (endpoint = 6) */
  #define REG_UDPHS_DMANXTDSC0  (*(__IO uint32_t*)0xF803C300U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 0) */
  #define REG_UDPHS_DMAADDRESS0 (*(__IO uint32_t*)0xF803C304U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 0) */
  #define REG_UDPHS_DMACONTROL0 (*(__IO uint32_t*)0xF803C308U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 0) */
  #define REG_UDPHS_DMASTATUS0  (*(__IO uint32_t*)0xF803C30CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 0) */
  #define REG_UDPHS_DMANXTDSC1  (*(__IO uint32_t*)0xF803C310U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 1) */
  #define REG_UDPHS_DMAADDRESS1 (*(__IO uint32_t*)0xF803C314U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 1) */
  #define REG_UDPHS_DMACONTROL1 (*(__IO uint32_t*)0xF803C318U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 1) */
  #define REG_UDPHS_DMASTATUS1  (*(__IO uint32_t*)0xF803C31CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 1) */
  #define REG_UDPHS_DMANXTDSC2  (*(__IO uint32_t*)0xF803C320U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 2) */
  #define REG_UDPHS_DMAADDRESS2 (*(__IO uint32_t*)0xF803C324U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 2) */
  #define REG_UDPHS_DMACONTROL2 (*(__IO uint32_t*)0xF803C328U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 2) */
  #define REG_UDPHS_DMASTATUS2  (*(__IO uint32_t*)0xF803C32CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 2) */
  #define REG_UDPHS_DMANXTDSC3  (*(__IO uint32_t*)0xF803C330U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 3) */
  #define REG_UDPHS_DMAADDRESS3 (*(__IO uint32_t*)0xF803C334U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 3) */
  #define REG_UDPHS_DMACONTROL3 (*(__IO uint32_t*)0xF803C338U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 3) */
  #define REG_UDPHS_DMASTATUS3  (*(__IO uint32_t*)0xF803C33CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 3) */
  #define REG_UDPHS_DMANXTDSC4  (*(__IO uint32_t*)0xF803C340U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 4) */
  #define REG_UDPHS_DMAADDRESS4 (*(__IO uint32_t*)0xF803C344U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 4) */
  #define REG_UDPHS_DMACONTROL4 (*(__IO uint32_t*)0xF803C348U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 4) */
  #define REG_UDPHS_DMASTATUS4  (*(__IO uint32_t*)0xF803C34CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 4) */
  #define REG_UDPHS_DMANXTDSC5  (*(__IO uint32_t*)0xF803C350U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 5) */
  #define REG_UDPHS_DMAADDRESS5 (*(__IO uint32_t*)0xF803C354U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 5) */
  #define REG_UDPHS_DMACONTROL5 (*(__IO uint32_t*)0xF803C358U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 5) */
  #define REG_UDPHS_DMASTATUS5  (*(__IO uint32_t*)0xF803C35CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 5) */
  #define REG_UDPHS_DMANXTDSC6  (*(__IO uint32_t*)0xF803C360U) /**< \brief (UDPHS) UDPHS DMA Next Descriptor Address Register (channel = 6) */
  #define REG_UDPHS_DMAADDRESS6 (*(__IO uint32_t*)0xF803C364U) /**< \brief (UDPHS) UDPHS DMA Channel Address Register (channel = 6) */
  #define REG_UDPHS_DMACONTROL6 (*(__IO uint32_t*)0xF803C368U) /**< \brief (UDPHS) UDPHS DMA Channel Control Register (channel = 6) */
  #define REG_UDPHS_DMASTATUS6  (*(__IO uint32_t*)0xF803C36CU) /**< \brief (UDPHS) UDPHS DMA Channel Status Register (channel = 6) */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_UDPHS_INSTANCE_ */
