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

#ifndef _SAMA5D4_GMAC0_INSTANCE_
#define _SAMA5D4_GMAC0_INSTANCE_

/* ========== Register definition for GMAC0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_GMAC0_NCR                        (0xF8020000U) /**< \brief (GMAC0) Network Control Register */
  #define REG_GMAC0_NCFGR                      (0xF8020004U) /**< \brief (GMAC0) Network Configuration Register */
  #define REG_GMAC0_NSR                        (0xF8020008U) /**< \brief (GMAC0) Network Status Register */
  #define REG_GMAC0_UR                         (0xF802000CU) /**< \brief (GMAC0) User Register */
  #define REG_GMAC0_DCFGR                      (0xF8020010U) /**< \brief (GMAC0) DMA Configuration Register */
  #define REG_GMAC0_TSR                        (0xF8020014U) /**< \brief (GMAC0) Transmit Status Register */
  #define REG_GMAC0_RBQB                       (0xF8020018U) /**< \brief (GMAC0) Receive Buffer Queue Base Address */
  #define REG_GMAC0_TBQB                       (0xF802001CU) /**< \brief (GMAC0) Transmit Buffer Queue Base Address */
  #define REG_GMAC0_RSR                        (0xF8020020U) /**< \brief (GMAC0) Receive Status Register */
  #define REG_GMAC0_ISR                        (0xF8020024U) /**< \brief (GMAC0) Interrupt Status Register */
  #define REG_GMAC0_IER                        (0xF8020028U) /**< \brief (GMAC0) Interrupt Enable Register */
  #define REG_GMAC0_IDR                        (0xF802002CU) /**< \brief (GMAC0) Interrupt Disable Register */
  #define REG_GMAC0_IMR                        (0xF8020030U) /**< \brief (GMAC0) Interrupt Mask Register */
  #define REG_GMAC0_MAN                        (0xF8020034U) /**< \brief (GMAC0) PHY Maintenance Register */
  #define REG_GMAC0_RPQ                        (0xF8020038U) /**< \brief (GMAC0) Received Pause Quantum Register */
  #define REG_GMAC0_TPQ                        (0xF802003CU) /**< \brief (GMAC0) Transmit Pause Quantum Register */
  #define REG_GMAC0_HRB                        (0xF8020080U) /**< \brief (GMAC0) Hash Register Bottom [31:0] */
  #define REG_GMAC0_HRT                        (0xF8020084U) /**< \brief (GMAC0) Hash Register Top [63:32] */
  #define REG_GMAC0_SAB1                       (0xF8020088U) /**< \brief (GMAC0) Specific Address 1 Bottom [31:0] Register */
  #define REG_GMAC0_SAT1                       (0xF802008CU) /**< \brief (GMAC0) Specific Address 1 Top [47:32] Register */
  #define REG_GMAC0_SAB2                       (0xF8020090U) /**< \brief (GMAC0) Specific Address 2 Bottom [31:0] Register */
  #define REG_GMAC0_SAT2                       (0xF8020094U) /**< \brief (GMAC0) Specific Address 2 Top [47:32] Register */
  #define REG_GMAC0_SAB3                       (0xF8020098U) /**< \brief (GMAC0) Specific Address 3 Bottom [31:0] Register */
  #define REG_GMAC0_SAT3                       (0xF802009CU) /**< \brief (GMAC0) Specific Address 3 Top [47:32] Register */
  #define REG_GMAC0_SAB4                       (0xF80200A0U) /**< \brief (GMAC0) Specific Address 4 Bottom [31:0] Register */
  #define REG_GMAC0_SAT4                       (0xF80200A4U) /**< \brief (GMAC0) Specific Address 4 Top [47:32] Register */
  #define REG_GMAC0_TIDM1                      (0xF80200A8U) /**< \brief (GMAC0) Type ID Match 1 Register */
  #define REG_GMAC0_TIDM2                      (0xF80200ACU) /**< \brief (GMAC0) Type ID Match 2 Register */
  #define REG_GMAC0_TIDM3                      (0xF80200B0U) /**< \brief (GMAC0) Type ID Match 3 Register */
  #define REG_GMAC0_TIDM4                      (0xF80200B4U) /**< \brief (GMAC0) Type ID Match 4 Register */
  #define REG_GMAC0_WOL                        (0xF80200B8U) /**< \brief (GMAC0) Wake on LAN Register */
  #define REG_GMAC0_IPGS                       (0xF80200BCU) /**< \brief (GMAC0) IPG Stretch Register */
  #define REG_GMAC0_SVLAN                      (0xF80200C0U) /**< \brief (GMAC0) Stacked VLAN Register */
  #define REG_GMAC0_TPFCP                      (0xF80200C4U) /**< \brief (GMAC0) Transmit PFC Pause Register */
  #define REG_GMAC0_SAMB1                      (0xF80200C8U) /**< \brief (GMAC0) Specific Address 1 Mask Bottom [31:0] Register */
  #define REG_GMAC0_SAMT1                      (0xF80200CCU) /**< \brief (GMAC0) Specific Address 1 Mask Top [47:32] Register */
  #define REG_GMAC0_OTLO                       (0xF8020100U) /**< \brief (GMAC0) Octets Transmitted [31:0] Register */
  #define REG_GMAC0_OTHI                       (0xF8020104U) /**< \brief (GMAC0) Octets Transmitted [47:32] Register */
  #define REG_GMAC0_FT                         (0xF8020108U) /**< \brief (GMAC0) Frames Transmitted Register */
  #define REG_GMAC0_BCFT                       (0xF802010CU) /**< \brief (GMAC0) Broadcast Frames Transmitted Register */
  #define REG_GMAC0_MFT                        (0xF8020110U) /**< \brief (GMAC0) Multicast Frames Transmitted Register */
  #define REG_GMAC0_PFT                        (0xF8020114U) /**< \brief (GMAC0) Pause Frames Transmitted Register */
  #define REG_GMAC0_BFT64                      (0xF8020118U) /**< \brief (GMAC0) 64 Byte Frames Transmitted Register */
  #define REG_GMAC0_TBFT127                    (0xF802011CU) /**< \brief (GMAC0) 65 to 127 Byte Frames Transmitted Register */
  #define REG_GMAC0_TBFT255                    (0xF8020120U) /**< \brief (GMAC0) 128 to 255 Byte Frames Transmitted Register */
  #define REG_GMAC0_TBFT511                    (0xF8020124U) /**< \brief (GMAC0) 256 to 511 Byte Frames Transmitted Register */
  #define REG_GMAC0_TBFT1023                   (0xF8020128U) /**< \brief (GMAC0) 512 to 1023 Byte Frames Transmitted Register */
  #define REG_GMAC0_TBFT1518                   (0xF802012CU) /**< \brief (GMAC0) 1024 to 1518 Byte Frames Transmitted Register */
  #define REG_GMAC0_GTBFT1518                  (0xF8020130U) /**< \brief (GMAC0) Greater Than 1518 Byte Frames Transmitted Register */
  #define REG_GMAC0_TUR                        (0xF8020134U) /**< \brief (GMAC0) Transmit Underruns Register */
  #define REG_GMAC0_SCF                        (0xF8020138U) /**< \brief (GMAC0) Single Collision Frames Register */
  #define REG_GMAC0_MCF                        (0xF802013CU) /**< \brief (GMAC0) Multiple Collision Frames Register */
  #define REG_GMAC0_EC                         (0xF8020140U) /**< \brief (GMAC0) Excessive Collisions Register */
  #define REG_GMAC0_LC                         (0xF8020144U) /**< \brief (GMAC0) Late Collisions Register */
  #define REG_GMAC0_DTF                        (0xF8020148U) /**< \brief (GMAC0) Deferred Transmission Frames Register */
  #define REG_GMAC0_CSE                        (0xF802014CU) /**< \brief (GMAC0) Carrier Sense Errors Register */
  #define REG_GMAC0_ORLO                       (0xF8020150U) /**< \brief (GMAC0) Octets Received [31:0] Received */
  #define REG_GMAC0_ORHI                       (0xF8020154U) /**< \brief (GMAC0) Octets Received [47:32] Received */
  #define REG_GMAC0_FR                         (0xF8020158U) /**< \brief (GMAC0) Frames Received Register */
  #define REG_GMAC0_BCFR                       (0xF802015CU) /**< \brief (GMAC0) Broadcast Frames Received Register */
  #define REG_GMAC0_MFR                        (0xF8020160U) /**< \brief (GMAC0) Multicast Frames Received Register */
  #define REG_GMAC0_PFR                        (0xF8020164U) /**< \brief (GMAC0) Pause Frames Received Register */
  #define REG_GMAC0_BFR64                      (0xF8020168U) /**< \brief (GMAC0) 64 Byte Frames Received Register */
  #define REG_GMAC0_TBFR127                    (0xF802016CU) /**< \brief (GMAC0) 65 to 127 Byte Frames Received Register */
  #define REG_GMAC0_TBFR255                    (0xF8020170U) /**< \brief (GMAC0) 128 to 255 Byte Frames Received Register */
  #define REG_GMAC0_TBFR511                    (0xF8020174U) /**< \brief (GMAC0) 256 to 511Byte Frames Received Register */
  #define REG_GMAC0_TBFR1023                   (0xF8020178U) /**< \brief (GMAC0) 512 to 1023 Byte Frames Received Register */
  #define REG_GMAC0_TBFR1518                   (0xF802017CU) /**< \brief (GMAC0) 1024 to 1518 Byte Frames Received Register */
  #define REG_GMAC0_TMXBFR                     (0xF8020180U) /**< \brief (GMAC0) 1519 to Maximum Byte Frames Received Register */
  #define REG_GMAC0_UFR                        (0xF8020184U) /**< \brief (GMAC0) Undersize Frames Received Register */
  #define REG_GMAC0_OFR                        (0xF8020188U) /**< \brief (GMAC0) Oversize Frames Received Register */
  #define REG_GMAC0_JR                         (0xF802018CU) /**< \brief (GMAC0) Jabbers Received Register */
  #define REG_GMAC0_FCSE                       (0xF8020190U) /**< \brief (GMAC0) Frame Check Sequence Errors Register */
  #define REG_GMAC0_LFFE                       (0xF8020194U) /**< \brief (GMAC0) Length Field Frame Errors Register */
  #define REG_GMAC0_RSE                        (0xF8020198U) /**< \brief (GMAC0) Receive Symbol Errors Register */
  #define REG_GMAC0_AE                         (0xF802019CU) /**< \brief (GMAC0) Alignment Errors Register */
  #define REG_GMAC0_RRE                        (0xF80201A0U) /**< \brief (GMAC0) Receive Resource Errors Register */
  #define REG_GMAC0_ROE                        (0xF80201A4U) /**< \brief (GMAC0) Receive Overrun Register */
  #define REG_GMAC0_IHCE                       (0xF80201A8U) /**< \brief (GMAC0) IP Header Checksum Errors Register */
  #define REG_GMAC0_TCE                        (0xF80201ACU) /**< \brief (GMAC0) TCP Checksum Errors Register */
  #define REG_GMAC0_UCE                        (0xF80201B0U) /**< \brief (GMAC0) UDP Checksum Errors Register */
  #define REG_GMAC0_TSSSL                      (0xF80201C8U) /**< \brief (GMAC0) 1588 Timer Sync Strobe Seconds [31:0] Register */
  #define REG_GMAC0_TSSN                       (0xF80201CCU) /**< \brief (GMAC0) 1588 Timer Sync Strobe Nanoseconds Register */
  #define REG_GMAC0_TSL                        (0xF80201D0U) /**< \brief (GMAC0) 1588 Timer Seconds [31:0] Register */
  #define REG_GMAC0_TN                         (0xF80201D4U) /**< \brief (GMAC0) 1588 Timer Nanoseconds Register */
  #define REG_GMAC0_TA                         (0xF80201D8U) /**< \brief (GMAC0) 1588 Timer Adjust Register */
  #define REG_GMAC0_TI                         (0xF80201DCU) /**< \brief (GMAC0) 1588 Timer Increment Register */
  #define REG_GMAC0_EFTS                       (0xF80201E0U) /**< \brief (GMAC0) PTP Event Frame Transmitted Seconds */
  #define REG_GMAC0_EFTN                       (0xF80201E4U) /**< \brief (GMAC0) PTP Event Frame Transmitted Nanoseconds */
  #define REG_GMAC0_EFRS                       (0xF80201E8U) /**< \brief (GMAC0) PTP Event Frame Received Seconds */
  #define REG_GMAC0_EFRN                       (0xF80201ECU) /**< \brief (GMAC0) PTP Event Frame Received Nanoseconds */
  #define REG_GMAC0_PEFTS                      (0xF80201F0U) /**< \brief (GMAC0) PTP Peer Event Frame Transmitted Seconds */
  #define REG_GMAC0_PEFTN                      (0xF80201F4U) /**< \brief (GMAC0) PTP Peer Event Frame Transmitted Nanoseconds */
  #define REG_GMAC0_PEFRS                      (0xF80201F8U) /**< \brief (GMAC0) PTP Peer Event Frame Received Seconds */
  #define REG_GMAC0_PEFRN                      (0xF80201FCU) /**< \brief (GMAC0) PTP Peer Event Frame Received Nanoseconds */
#else
  #define REG_GMAC0_NCR       (*(__IO uint32_t*)0xF8020000U) /**< \brief (GMAC0) Network Control Register */
  #define REG_GMAC0_NCFGR     (*(__IO uint32_t*)0xF8020004U) /**< \brief (GMAC0) Network Configuration Register */
  #define REG_GMAC0_NSR       (*(__I  uint32_t*)0xF8020008U) /**< \brief (GMAC0) Network Status Register */
  #define REG_GMAC0_UR        (*(__IO uint32_t*)0xF802000CU) /**< \brief (GMAC0) User Register */
  #define REG_GMAC0_DCFGR     (*(__IO uint32_t*)0xF8020010U) /**< \brief (GMAC0) DMA Configuration Register */
  #define REG_GMAC0_TSR       (*(__IO uint32_t*)0xF8020014U) /**< \brief (GMAC0) Transmit Status Register */
  #define REG_GMAC0_RBQB      (*(__IO uint32_t*)0xF8020018U) /**< \brief (GMAC0) Receive Buffer Queue Base Address */
  #define REG_GMAC0_TBQB      (*(__IO uint32_t*)0xF802001CU) /**< \brief (GMAC0) Transmit Buffer Queue Base Address */
  #define REG_GMAC0_RSR       (*(__IO uint32_t*)0xF8020020U) /**< \brief (GMAC0) Receive Status Register */
  #define REG_GMAC0_ISR       (*(__I  uint32_t*)0xF8020024U) /**< \brief (GMAC0) Interrupt Status Register */
  #define REG_GMAC0_IER       (*(__O  uint32_t*)0xF8020028U) /**< \brief (GMAC0) Interrupt Enable Register */
  #define REG_GMAC0_IDR       (*(__O  uint32_t*)0xF802002CU) /**< \brief (GMAC0) Interrupt Disable Register */
  #define REG_GMAC0_IMR       (*(__IO uint32_t*)0xF8020030U) /**< \brief (GMAC0) Interrupt Mask Register */
  #define REG_GMAC0_MAN       (*(__IO uint32_t*)0xF8020034U) /**< \brief (GMAC0) PHY Maintenance Register */
  #define REG_GMAC0_RPQ       (*(__I  uint32_t*)0xF8020038U) /**< \brief (GMAC0) Received Pause Quantum Register */
  #define REG_GMAC0_TPQ       (*(__IO uint32_t*)0xF802003CU) /**< \brief (GMAC0) Transmit Pause Quantum Register */
  #define REG_GMAC0_HRB       (*(__IO uint32_t*)0xF8020080U) /**< \brief (GMAC0) Hash Register Bottom [31:0] */
  #define REG_GMAC0_HRT       (*(__IO uint32_t*)0xF8020084U) /**< \brief (GMAC0) Hash Register Top [63:32] */
  #define REG_GMAC0_SAB1      (*(__IO uint32_t*)0xF8020088U) /**< \brief (GMAC0) Specific Address 1 Bottom [31:0] Register */
  #define REG_GMAC0_SAT1      (*(__IO uint32_t*)0xF802008CU) /**< \brief (GMAC0) Specific Address 1 Top [47:32] Register */
  #define REG_GMAC0_SAB2      (*(__IO uint32_t*)0xF8020090U) /**< \brief (GMAC0) Specific Address 2 Bottom [31:0] Register */
  #define REG_GMAC0_SAT2      (*(__IO uint32_t*)0xF8020094U) /**< \brief (GMAC0) Specific Address 2 Top [47:32] Register */
  #define REG_GMAC0_SAB3      (*(__IO uint32_t*)0xF8020098U) /**< \brief (GMAC0) Specific Address 3 Bottom [31:0] Register */
  #define REG_GMAC0_SAT3      (*(__IO uint32_t*)0xF802009CU) /**< \brief (GMAC0) Specific Address 3 Top [47:32] Register */
  #define REG_GMAC0_SAB4      (*(__IO uint32_t*)0xF80200A0U) /**< \brief (GMAC0) Specific Address 4 Bottom [31:0] Register */
  #define REG_GMAC0_SAT4      (*(__IO uint32_t*)0xF80200A4U) /**< \brief (GMAC0) Specific Address 4 Top [47:32] Register */
  #define REG_GMAC0_TIDM1     (*(__IO uint32_t*)0xF80200A8U) /**< \brief (GMAC0) Type ID Match 1 Register */
  #define REG_GMAC0_TIDM2     (*(__IO uint32_t*)0xF80200ACU) /**< \brief (GMAC0) Type ID Match 2 Register */
  #define REG_GMAC0_TIDM3     (*(__IO uint32_t*)0xF80200B0U) /**< \brief (GMAC0) Type ID Match 3 Register */
  #define REG_GMAC0_TIDM4     (*(__IO uint32_t*)0xF80200B4U) /**< \brief (GMAC0) Type ID Match 4 Register */
  #define REG_GMAC0_WOL       (*(__IO uint32_t*)0xF80200B8U) /**< \brief (GMAC0) Wake on LAN Register */
  #define REG_GMAC0_IPGS      (*(__IO uint32_t*)0xF80200BCU) /**< \brief (GMAC0) IPG Stretch Register */
  #define REG_GMAC0_SVLAN     (*(__IO uint32_t*)0xF80200C0U) /**< \brief (GMAC0) Stacked VLAN Register */
  #define REG_GMAC0_TPFCP     (*(__IO uint32_t*)0xF80200C4U) /**< \brief (GMAC0) Transmit PFC Pause Register */
  #define REG_GMAC0_SAMB1     (*(__IO uint32_t*)0xF80200C8U) /**< \brief (GMAC0) Specific Address 1 Mask Bottom [31:0] Register */
  #define REG_GMAC0_SAMT1     (*(__IO uint32_t*)0xF80200CCU) /**< \brief (GMAC0) Specific Address 1 Mask Top [47:32] Register */
  #define REG_GMAC0_OTLO      (*(__I  uint32_t*)0xF8020100U) /**< \brief (GMAC0) Octets Transmitted [31:0] Register */
  #define REG_GMAC0_OTHI      (*(__I  uint32_t*)0xF8020104U) /**< \brief (GMAC0) Octets Transmitted [47:32] Register */
  #define REG_GMAC0_FT        (*(__I  uint32_t*)0xF8020108U) /**< \brief (GMAC0) Frames Transmitted Register */
  #define REG_GMAC0_BCFT      (*(__I  uint32_t*)0xF802010CU) /**< \brief (GMAC0) Broadcast Frames Transmitted Register */
  #define REG_GMAC0_MFT       (*(__I  uint32_t*)0xF8020110U) /**< \brief (GMAC0) Multicast Frames Transmitted Register */
  #define REG_GMAC0_PFT       (*(__I  uint32_t*)0xF8020114U) /**< \brief (GMAC0) Pause Frames Transmitted Register */
  #define REG_GMAC0_BFT64     (*(__I  uint32_t*)0xF8020118U) /**< \brief (GMAC0) 64 Byte Frames Transmitted Register */
  #define REG_GMAC0_TBFT127   (*(__I  uint32_t*)0xF802011CU) /**< \brief (GMAC0) 65 to 127 Byte Frames Transmitted Register */
  #define REG_GMAC0_TBFT255   (*(__I  uint32_t*)0xF8020120U) /**< \brief (GMAC0) 128 to 255 Byte Frames Transmitted Register */
  #define REG_GMAC0_TBFT511   (*(__I  uint32_t*)0xF8020124U) /**< \brief (GMAC0) 256 to 511 Byte Frames Transmitted Register */
  #define REG_GMAC0_TBFT1023  (*(__I  uint32_t*)0xF8020128U) /**< \brief (GMAC0) 512 to 1023 Byte Frames Transmitted Register */
  #define REG_GMAC0_TBFT1518  (*(__I  uint32_t*)0xF802012CU) /**< \brief (GMAC0) 1024 to 1518 Byte Frames Transmitted Register */
  #define REG_GMAC0_GTBFT1518 (*(__I  uint32_t*)0xF8020130U) /**< \brief (GMAC0) Greater Than 1518 Byte Frames Transmitted Register */
  #define REG_GMAC0_TUR       (*(__I  uint32_t*)0xF8020134U) /**< \brief (GMAC0) Transmit Underruns Register */
  #define REG_GMAC0_SCF       (*(__I  uint32_t*)0xF8020138U) /**< \brief (GMAC0) Single Collision Frames Register */
  #define REG_GMAC0_MCF       (*(__I  uint32_t*)0xF802013CU) /**< \brief (GMAC0) Multiple Collision Frames Register */
  #define REG_GMAC0_EC        (*(__I  uint32_t*)0xF8020140U) /**< \brief (GMAC0) Excessive Collisions Register */
  #define REG_GMAC0_LC        (*(__I  uint32_t*)0xF8020144U) /**< \brief (GMAC0) Late Collisions Register */
  #define REG_GMAC0_DTF       (*(__I  uint32_t*)0xF8020148U) /**< \brief (GMAC0) Deferred Transmission Frames Register */
  #define REG_GMAC0_CSE       (*(__I  uint32_t*)0xF802014CU) /**< \brief (GMAC0) Carrier Sense Errors Register */
  #define REG_GMAC0_ORLO      (*(__I  uint32_t*)0xF8020150U) /**< \brief (GMAC0) Octets Received [31:0] Received */
  #define REG_GMAC0_ORHI      (*(__I  uint32_t*)0xF8020154U) /**< \brief (GMAC0) Octets Received [47:32] Received */
  #define REG_GMAC0_FR        (*(__I  uint32_t*)0xF8020158U) /**< \brief (GMAC0) Frames Received Register */
  #define REG_GMAC0_BCFR      (*(__I  uint32_t*)0xF802015CU) /**< \brief (GMAC0) Broadcast Frames Received Register */
  #define REG_GMAC0_MFR       (*(__I  uint32_t*)0xF8020160U) /**< \brief (GMAC0) Multicast Frames Received Register */
  #define REG_GMAC0_PFR       (*(__I  uint32_t*)0xF8020164U) /**< \brief (GMAC0) Pause Frames Received Register */
  #define REG_GMAC0_BFR64     (*(__I  uint32_t*)0xF8020168U) /**< \brief (GMAC0) 64 Byte Frames Received Register */
  #define REG_GMAC0_TBFR127   (*(__I  uint32_t*)0xF802016CU) /**< \brief (GMAC0) 65 to 127 Byte Frames Received Register */
  #define REG_GMAC0_TBFR255   (*(__I  uint32_t*)0xF8020170U) /**< \brief (GMAC0) 128 to 255 Byte Frames Received Register */
  #define REG_GMAC0_TBFR511   (*(__I  uint32_t*)0xF8020174U) /**< \brief (GMAC0) 256 to 511Byte Frames Received Register */
  #define REG_GMAC0_TBFR1023  (*(__I  uint32_t*)0xF8020178U) /**< \brief (GMAC0) 512 to 1023 Byte Frames Received Register */
  #define REG_GMAC0_TBFR1518  (*(__I  uint32_t*)0xF802017CU) /**< \brief (GMAC0) 1024 to 1518 Byte Frames Received Register */
  #define REG_GMAC0_TMXBFR    (*(__I  uint32_t*)0xF8020180U) /**< \brief (GMAC0) 1519 to Maximum Byte Frames Received Register */
  #define REG_GMAC0_UFR       (*(__I  uint32_t*)0xF8020184U) /**< \brief (GMAC0) Undersize Frames Received Register */
  #define REG_GMAC0_OFR       (*(__I  uint32_t*)0xF8020188U) /**< \brief (GMAC0) Oversize Frames Received Register */
  #define REG_GMAC0_JR        (*(__I  uint32_t*)0xF802018CU) /**< \brief (GMAC0) Jabbers Received Register */
  #define REG_GMAC0_FCSE      (*(__I  uint32_t*)0xF8020190U) /**< \brief (GMAC0) Frame Check Sequence Errors Register */
  #define REG_GMAC0_LFFE      (*(__I  uint32_t*)0xF8020194U) /**< \brief (GMAC0) Length Field Frame Errors Register */
  #define REG_GMAC0_RSE       (*(__I  uint32_t*)0xF8020198U) /**< \brief (GMAC0) Receive Symbol Errors Register */
  #define REG_GMAC0_AE        (*(__I  uint32_t*)0xF802019CU) /**< \brief (GMAC0) Alignment Errors Register */
  #define REG_GMAC0_RRE       (*(__I  uint32_t*)0xF80201A0U) /**< \brief (GMAC0) Receive Resource Errors Register */
  #define REG_GMAC0_ROE       (*(__I  uint32_t*)0xF80201A4U) /**< \brief (GMAC0) Receive Overrun Register */
  #define REG_GMAC0_IHCE      (*(__I  uint32_t*)0xF80201A8U) /**< \brief (GMAC0) IP Header Checksum Errors Register */
  #define REG_GMAC0_TCE       (*(__I  uint32_t*)0xF80201ACU) /**< \brief (GMAC0) TCP Checksum Errors Register */
  #define REG_GMAC0_UCE       (*(__I  uint32_t*)0xF80201B0U) /**< \brief (GMAC0) UDP Checksum Errors Register */
  #define REG_GMAC0_TSSSL     (*(__IO uint32_t*)0xF80201C8U) /**< \brief (GMAC0) 1588 Timer Sync Strobe Seconds [31:0] Register */
  #define REG_GMAC0_TSSN      (*(__IO uint32_t*)0xF80201CCU) /**< \brief (GMAC0) 1588 Timer Sync Strobe Nanoseconds Register */
  #define REG_GMAC0_TSL       (*(__IO uint32_t*)0xF80201D0U) /**< \brief (GMAC0) 1588 Timer Seconds [31:0] Register */
  #define REG_GMAC0_TN        (*(__IO uint32_t*)0xF80201D4U) /**< \brief (GMAC0) 1588 Timer Nanoseconds Register */
  #define REG_GMAC0_TA        (*(__O  uint32_t*)0xF80201D8U) /**< \brief (GMAC0) 1588 Timer Adjust Register */
  #define REG_GMAC0_TI        (*(__IO uint32_t*)0xF80201DCU) /**< \brief (GMAC0) 1588 Timer Increment Register */
  #define REG_GMAC0_EFTS      (*(__I  uint32_t*)0xF80201E0U) /**< \brief (GMAC0) PTP Event Frame Transmitted Seconds */
  #define REG_GMAC0_EFTN      (*(__I  uint32_t*)0xF80201E4U) /**< \brief (GMAC0) PTP Event Frame Transmitted Nanoseconds */
  #define REG_GMAC0_EFRS      (*(__I  uint32_t*)0xF80201E8U) /**< \brief (GMAC0) PTP Event Frame Received Seconds */
  #define REG_GMAC0_EFRN      (*(__I  uint32_t*)0xF80201ECU) /**< \brief (GMAC0) PTP Event Frame Received Nanoseconds */
  #define REG_GMAC0_PEFTS     (*(__I  uint32_t*)0xF80201F0U) /**< \brief (GMAC0) PTP Peer Event Frame Transmitted Seconds */
  #define REG_GMAC0_PEFTN     (*(__I  uint32_t*)0xF80201F4U) /**< \brief (GMAC0) PTP Peer Event Frame Transmitted Nanoseconds */
  #define REG_GMAC0_PEFRS     (*(__I  uint32_t*)0xF80201F8U) /**< \brief (GMAC0) PTP Peer Event Frame Received Seconds */
  #define REG_GMAC0_PEFRN     (*(__I  uint32_t*)0xF80201FCU) /**< \brief (GMAC0) PTP Peer Event Frame Received Nanoseconds */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D4_GMAC0_INSTANCE_ */
