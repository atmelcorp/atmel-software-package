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

#ifndef _SAMA5D4_GMAC1_INSTANCE_
#define _SAMA5D4_GMAC1_INSTANCE_

/* ========== Register definition for GMAC1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_GMAC1_NCR                        (0xFC028000U) /**< \brief (GMAC1) Network Control Register */
  #define REG_GMAC1_NCFGR                      (0xFC028004U) /**< \brief (GMAC1) Network Configuration Register */
  #define REG_GMAC1_NSR                        (0xFC028008U) /**< \brief (GMAC1) Network Status Register */
  #define REG_GMAC1_UR                         (0xFC02800CU) /**< \brief (GMAC1) User Register */
  #define REG_GMAC1_DCFGR                      (0xFC028010U) /**< \brief (GMAC1) DMA Configuration Register */
  #define REG_GMAC1_TSR                        (0xFC028014U) /**< \brief (GMAC1) Transmit Status Register */
  #define REG_GMAC1_RBQB                       (0xFC028018U) /**< \brief (GMAC1) Receive Buffer Queue Base Address */
  #define REG_GMAC1_TBQB                       (0xFC02801CU) /**< \brief (GMAC1) Transmit Buffer Queue Base Address */
  #define REG_GMAC1_RSR                        (0xFC028020U) /**< \brief (GMAC1) Receive Status Register */
  #define REG_GMAC1_ISR                        (0xFC028024U) /**< \brief (GMAC1) Interrupt Status Register */
  #define REG_GMAC1_IER                        (0xFC028028U) /**< \brief (GMAC1) Interrupt Enable Register */
  #define REG_GMAC1_IDR                        (0xFC02802CU) /**< \brief (GMAC1) Interrupt Disable Register */
  #define REG_GMAC1_IMR                        (0xFC028030U) /**< \brief (GMAC1) Interrupt Mask Register */
  #define REG_GMAC1_MAN                        (0xFC028034U) /**< \brief (GMAC1) PHY Maintenance Register */
  #define REG_GMAC1_RPQ                        (0xFC028038U) /**< \brief (GMAC1) Received Pause Quantum Register */
  #define REG_GMAC1_TPQ                        (0xFC02803CU) /**< \brief (GMAC1) Transmit Pause Quantum Register */
  #define REG_GMAC1_HRB                        (0xFC028080U) /**< \brief (GMAC1) Hash Register Bottom [31:0] */
  #define REG_GMAC1_HRT                        (0xFC028084U) /**< \brief (GMAC1) Hash Register Top [63:32] */
  #define REG_GMAC1_SAB1                       (0xFC028088U) /**< \brief (GMAC1) Specific Address 1 Bottom [31:0] Register */
  #define REG_GMAC1_SAT1                       (0xFC02808CU) /**< \brief (GMAC1) Specific Address 1 Top [47:32] Register */
  #define REG_GMAC1_SAB2                       (0xFC028090U) /**< \brief (GMAC1) Specific Address 2 Bottom [31:0] Register */
  #define REG_GMAC1_SAT2                       (0xFC028094U) /**< \brief (GMAC1) Specific Address 2 Top [47:32] Register */
  #define REG_GMAC1_SAB3                       (0xFC028098U) /**< \brief (GMAC1) Specific Address 3 Bottom [31:0] Register */
  #define REG_GMAC1_SAT3                       (0xFC02809CU) /**< \brief (GMAC1) Specific Address 3 Top [47:32] Register */
  #define REG_GMAC1_SAB4                       (0xFC0280A0U) /**< \brief (GMAC1) Specific Address 4 Bottom [31:0] Register */
  #define REG_GMAC1_SAT4                       (0xFC0280A4U) /**< \brief (GMAC1) Specific Address 4 Top [47:32] Register */
  #define REG_GMAC1_TIDM1                      (0xFC0280A8U) /**< \brief (GMAC1) Type ID Match 1 Register */
  #define REG_GMAC1_TIDM2                      (0xFC0280ACU) /**< \brief (GMAC1) Type ID Match 2 Register */
  #define REG_GMAC1_TIDM3                      (0xFC0280B0U) /**< \brief (GMAC1) Type ID Match 3 Register */
  #define REG_GMAC1_TIDM4                      (0xFC0280B4U) /**< \brief (GMAC1) Type ID Match 4 Register */
  #define REG_GMAC1_WOL                        (0xFC0280B8U) /**< \brief (GMAC1) Wake on LAN Register */
  #define REG_GMAC1_IPGS                       (0xFC0280BCU) /**< \brief (GMAC1) IPG Stretch Register */
  #define REG_GMAC1_SVLAN                      (0xFC0280C0U) /**< \brief (GMAC1) Stacked VLAN Register */
  #define REG_GMAC1_TPFCP                      (0xFC0280C4U) /**< \brief (GMAC1) Transmit PFC Pause Register */
  #define REG_GMAC1_SAMB1                      (0xFC0280C8U) /**< \brief (GMAC1) Specific Address 1 Mask Bottom [31:0] Register */
  #define REG_GMAC1_SAMT1                      (0xFC0280CCU) /**< \brief (GMAC1) Specific Address 1 Mask Top [47:32] Register */
  #define REG_GMAC1_OTLO                       (0xFC028100U) /**< \brief (GMAC1) Octets Transmitted [31:0] Register */
  #define REG_GMAC1_OTHI                       (0xFC028104U) /**< \brief (GMAC1) Octets Transmitted [47:32] Register */
  #define REG_GMAC1_FT                         (0xFC028108U) /**< \brief (GMAC1) Frames Transmitted Register */
  #define REG_GMAC1_BCFT                       (0xFC02810CU) /**< \brief (GMAC1) Broadcast Frames Transmitted Register */
  #define REG_GMAC1_MFT                        (0xFC028110U) /**< \brief (GMAC1) Multicast Frames Transmitted Register */
  #define REG_GMAC1_PFT                        (0xFC028114U) /**< \brief (GMAC1) Pause Frames Transmitted Register */
  #define REG_GMAC1_BFT64                      (0xFC028118U) /**< \brief (GMAC1) 64 Byte Frames Transmitted Register */
  #define REG_GMAC1_TBFT127                    (0xFC02811CU) /**< \brief (GMAC1) 65 to 127 Byte Frames Transmitted Register */
  #define REG_GMAC1_TBFT255                    (0xFC028120U) /**< \brief (GMAC1) 128 to 255 Byte Frames Transmitted Register */
  #define REG_GMAC1_TBFT511                    (0xFC028124U) /**< \brief (GMAC1) 256 to 511 Byte Frames Transmitted Register */
  #define REG_GMAC1_TBFT1023                   (0xFC028128U) /**< \brief (GMAC1) 512 to 1023 Byte Frames Transmitted Register */
  #define REG_GMAC1_TBFT1518                   (0xFC02812CU) /**< \brief (GMAC1) 1024 to 1518 Byte Frames Transmitted Register */
  #define REG_GMAC1_GTBFT1518                  (0xFC028130U) /**< \brief (GMAC1) Greater Than 1518 Byte Frames Transmitted Register */
  #define REG_GMAC1_TUR                        (0xFC028134U) /**< \brief (GMAC1) Transmit Underruns Register */
  #define REG_GMAC1_SCF                        (0xFC028138U) /**< \brief (GMAC1) Single Collision Frames Register */
  #define REG_GMAC1_MCF                        (0xFC02813CU) /**< \brief (GMAC1) Multiple Collision Frames Register */
  #define REG_GMAC1_EC                         (0xFC028140U) /**< \brief (GMAC1) Excessive Collisions Register */
  #define REG_GMAC1_LC                         (0xFC028144U) /**< \brief (GMAC1) Late Collisions Register */
  #define REG_GMAC1_DTF                        (0xFC028148U) /**< \brief (GMAC1) Deferred Transmission Frames Register */
  #define REG_GMAC1_CSE                        (0xFC02814CU) /**< \brief (GMAC1) Carrier Sense Errors Register */
  #define REG_GMAC1_ORLO                       (0xFC028150U) /**< \brief (GMAC1) Octets Received [31:0] Received */
  #define REG_GMAC1_ORHI                       (0xFC028154U) /**< \brief (GMAC1) Octets Received [47:32] Received */
  #define REG_GMAC1_FR                         (0xFC028158U) /**< \brief (GMAC1) Frames Received Register */
  #define REG_GMAC1_BCFR                       (0xFC02815CU) /**< \brief (GMAC1) Broadcast Frames Received Register */
  #define REG_GMAC1_MFR                        (0xFC028160U) /**< \brief (GMAC1) Multicast Frames Received Register */
  #define REG_GMAC1_PFR                        (0xFC028164U) /**< \brief (GMAC1) Pause Frames Received Register */
  #define REG_GMAC1_BFR64                      (0xFC028168U) /**< \brief (GMAC1) 64 Byte Frames Received Register */
  #define REG_GMAC1_TBFR127                    (0xFC02816CU) /**< \brief (GMAC1) 65 to 127 Byte Frames Received Register */
  #define REG_GMAC1_TBFR255                    (0xFC028170U) /**< \brief (GMAC1) 128 to 255 Byte Frames Received Register */
  #define REG_GMAC1_TBFR511                    (0xFC028174U) /**< \brief (GMAC1) 256 to 511Byte Frames Received Register */
  #define REG_GMAC1_TBFR1023                   (0xFC028178U) /**< \brief (GMAC1) 512 to 1023 Byte Frames Received Register */
  #define REG_GMAC1_TBFR1518                   (0xFC02817CU) /**< \brief (GMAC1) 1024 to 1518 Byte Frames Received Register */
  #define REG_GMAC1_TMXBFR                     (0xFC028180U) /**< \brief (GMAC1) 1519 to Maximum Byte Frames Received Register */
  #define REG_GMAC1_UFR                        (0xFC028184U) /**< \brief (GMAC1) Undersize Frames Received Register */
  #define REG_GMAC1_OFR                        (0xFC028188U) /**< \brief (GMAC1) Oversize Frames Received Register */
  #define REG_GMAC1_JR                         (0xFC02818CU) /**< \brief (GMAC1) Jabbers Received Register */
  #define REG_GMAC1_FCSE                       (0xFC028190U) /**< \brief (GMAC1) Frame Check Sequence Errors Register */
  #define REG_GMAC1_LFFE                       (0xFC028194U) /**< \brief (GMAC1) Length Field Frame Errors Register */
  #define REG_GMAC1_RSE                        (0xFC028198U) /**< \brief (GMAC1) Receive Symbol Errors Register */
  #define REG_GMAC1_AE                         (0xFC02819CU) /**< \brief (GMAC1) Alignment Errors Register */
  #define REG_GMAC1_RRE                        (0xFC0281A0U) /**< \brief (GMAC1) Receive Resource Errors Register */
  #define REG_GMAC1_ROE                        (0xFC0281A4U) /**< \brief (GMAC1) Receive Overrun Register */
  #define REG_GMAC1_IHCE                       (0xFC0281A8U) /**< \brief (GMAC1) IP Header Checksum Errors Register */
  #define REG_GMAC1_TCE                        (0xFC0281ACU) /**< \brief (GMAC1) TCP Checksum Errors Register */
  #define REG_GMAC1_UCE                        (0xFC0281B0U) /**< \brief (GMAC1) UDP Checksum Errors Register */
  #define REG_GMAC1_TSSSL                      (0xFC0281C8U) /**< \brief (GMAC1) 1588 Timer Sync Strobe Seconds [31:0] Register */
  #define REG_GMAC1_TSSN                       (0xFC0281CCU) /**< \brief (GMAC1) 1588 Timer Sync Strobe Nanoseconds Register */
  #define REG_GMAC1_TSL                        (0xFC0281D0U) /**< \brief (GMAC1) 1588 Timer Seconds [31:0] Register */
  #define REG_GMAC1_TN                         (0xFC0281D4U) /**< \brief (GMAC1) 1588 Timer Nanoseconds Register */
  #define REG_GMAC1_TA                         (0xFC0281D8U) /**< \brief (GMAC1) 1588 Timer Adjust Register */
  #define REG_GMAC1_TI                         (0xFC0281DCU) /**< \brief (GMAC1) 1588 Timer Increment Register */
  #define REG_GMAC1_EFTS                       (0xFC0281E0U) /**< \brief (GMAC1) PTP Event Frame Transmitted Seconds */
  #define REG_GMAC1_EFTN                       (0xFC0281E4U) /**< \brief (GMAC1) PTP Event Frame Transmitted Nanoseconds */
  #define REG_GMAC1_EFRS                       (0xFC0281E8U) /**< \brief (GMAC1) PTP Event Frame Received Seconds */
  #define REG_GMAC1_EFRN                       (0xFC0281ECU) /**< \brief (GMAC1) PTP Event Frame Received Nanoseconds */
  #define REG_GMAC1_PEFTS                      (0xFC0281F0U) /**< \brief (GMAC1) PTP Peer Event Frame Transmitted Seconds */
  #define REG_GMAC1_PEFTN                      (0xFC0281F4U) /**< \brief (GMAC1) PTP Peer Event Frame Transmitted Nanoseconds */
  #define REG_GMAC1_PEFRS                      (0xFC0281F8U) /**< \brief (GMAC1) PTP Peer Event Frame Received Seconds */
  #define REG_GMAC1_PEFRN                      (0xFC0281FCU) /**< \brief (GMAC1) PTP Peer Event Frame Received Nanoseconds */
#else
  #define REG_GMAC1_NCR       (*(__IO uint32_t*)0xFC028000U) /**< \brief (GMAC1) Network Control Register */
  #define REG_GMAC1_NCFGR     (*(__IO uint32_t*)0xFC028004U) /**< \brief (GMAC1) Network Configuration Register */
  #define REG_GMAC1_NSR       (*(__I  uint32_t*)0xFC028008U) /**< \brief (GMAC1) Network Status Register */
  #define REG_GMAC1_UR        (*(__IO uint32_t*)0xFC02800CU) /**< \brief (GMAC1) User Register */
  #define REG_GMAC1_DCFGR     (*(__IO uint32_t*)0xFC028010U) /**< \brief (GMAC1) DMA Configuration Register */
  #define REG_GMAC1_TSR       (*(__IO uint32_t*)0xFC028014U) /**< \brief (GMAC1) Transmit Status Register */
  #define REG_GMAC1_RBQB      (*(__IO uint32_t*)0xFC028018U) /**< \brief (GMAC1) Receive Buffer Queue Base Address */
  #define REG_GMAC1_TBQB      (*(__IO uint32_t*)0xFC02801CU) /**< \brief (GMAC1) Transmit Buffer Queue Base Address */
  #define REG_GMAC1_RSR       (*(__IO uint32_t*)0xFC028020U) /**< \brief (GMAC1) Receive Status Register */
  #define REG_GMAC1_ISR       (*(__I  uint32_t*)0xFC028024U) /**< \brief (GMAC1) Interrupt Status Register */
  #define REG_GMAC1_IER       (*(__O  uint32_t*)0xFC028028U) /**< \brief (GMAC1) Interrupt Enable Register */
  #define REG_GMAC1_IDR       (*(__O  uint32_t*)0xFC02802CU) /**< \brief (GMAC1) Interrupt Disable Register */
  #define REG_GMAC1_IMR       (*(__IO uint32_t*)0xFC028030U) /**< \brief (GMAC1) Interrupt Mask Register */
  #define REG_GMAC1_MAN       (*(__IO uint32_t*)0xFC028034U) /**< \brief (GMAC1) PHY Maintenance Register */
  #define REG_GMAC1_RPQ       (*(__I  uint32_t*)0xFC028038U) /**< \brief (GMAC1) Received Pause Quantum Register */
  #define REG_GMAC1_TPQ       (*(__IO uint32_t*)0xFC02803CU) /**< \brief (GMAC1) Transmit Pause Quantum Register */
  #define REG_GMAC1_HRB       (*(__IO uint32_t*)0xFC028080U) /**< \brief (GMAC1) Hash Register Bottom [31:0] */
  #define REG_GMAC1_HRT       (*(__IO uint32_t*)0xFC028084U) /**< \brief (GMAC1) Hash Register Top [63:32] */
  #define REG_GMAC1_SAB1      (*(__IO uint32_t*)0xFC028088U) /**< \brief (GMAC1) Specific Address 1 Bottom [31:0] Register */
  #define REG_GMAC1_SAT1      (*(__IO uint32_t*)0xFC02808CU) /**< \brief (GMAC1) Specific Address 1 Top [47:32] Register */
  #define REG_GMAC1_SAB2      (*(__IO uint32_t*)0xFC028090U) /**< \brief (GMAC1) Specific Address 2 Bottom [31:0] Register */
  #define REG_GMAC1_SAT2      (*(__IO uint32_t*)0xFC028094U) /**< \brief (GMAC1) Specific Address 2 Top [47:32] Register */
  #define REG_GMAC1_SAB3      (*(__IO uint32_t*)0xFC028098U) /**< \brief (GMAC1) Specific Address 3 Bottom [31:0] Register */
  #define REG_GMAC1_SAT3      (*(__IO uint32_t*)0xFC02809CU) /**< \brief (GMAC1) Specific Address 3 Top [47:32] Register */
  #define REG_GMAC1_SAB4      (*(__IO uint32_t*)0xFC0280A0U) /**< \brief (GMAC1) Specific Address 4 Bottom [31:0] Register */
  #define REG_GMAC1_SAT4      (*(__IO uint32_t*)0xFC0280A4U) /**< \brief (GMAC1) Specific Address 4 Top [47:32] Register */
  #define REG_GMAC1_TIDM1     (*(__IO uint32_t*)0xFC0280A8U) /**< \brief (GMAC1) Type ID Match 1 Register */
  #define REG_GMAC1_TIDM2     (*(__IO uint32_t*)0xFC0280ACU) /**< \brief (GMAC1) Type ID Match 2 Register */
  #define REG_GMAC1_TIDM3     (*(__IO uint32_t*)0xFC0280B0U) /**< \brief (GMAC1) Type ID Match 3 Register */
  #define REG_GMAC1_TIDM4     (*(__IO uint32_t*)0xFC0280B4U) /**< \brief (GMAC1) Type ID Match 4 Register */
  #define REG_GMAC1_WOL       (*(__IO uint32_t*)0xFC0280B8U) /**< \brief (GMAC1) Wake on LAN Register */
  #define REG_GMAC1_IPGS      (*(__IO uint32_t*)0xFC0280BCU) /**< \brief (GMAC1) IPG Stretch Register */
  #define REG_GMAC1_SVLAN     (*(__IO uint32_t*)0xFC0280C0U) /**< \brief (GMAC1) Stacked VLAN Register */
  #define REG_GMAC1_TPFCP     (*(__IO uint32_t*)0xFC0280C4U) /**< \brief (GMAC1) Transmit PFC Pause Register */
  #define REG_GMAC1_SAMB1     (*(__IO uint32_t*)0xFC0280C8U) /**< \brief (GMAC1) Specific Address 1 Mask Bottom [31:0] Register */
  #define REG_GMAC1_SAMT1     (*(__IO uint32_t*)0xFC0280CCU) /**< \brief (GMAC1) Specific Address 1 Mask Top [47:32] Register */
  #define REG_GMAC1_OTLO      (*(__I  uint32_t*)0xFC028100U) /**< \brief (GMAC1) Octets Transmitted [31:0] Register */
  #define REG_GMAC1_OTHI      (*(__I  uint32_t*)0xFC028104U) /**< \brief (GMAC1) Octets Transmitted [47:32] Register */
  #define REG_GMAC1_FT        (*(__I  uint32_t*)0xFC028108U) /**< \brief (GMAC1) Frames Transmitted Register */
  #define REG_GMAC1_BCFT      (*(__I  uint32_t*)0xFC02810CU) /**< \brief (GMAC1) Broadcast Frames Transmitted Register */
  #define REG_GMAC1_MFT       (*(__I  uint32_t*)0xFC028110U) /**< \brief (GMAC1) Multicast Frames Transmitted Register */
  #define REG_GMAC1_PFT       (*(__I  uint32_t*)0xFC028114U) /**< \brief (GMAC1) Pause Frames Transmitted Register */
  #define REG_GMAC1_BFT64     (*(__I  uint32_t*)0xFC028118U) /**< \brief (GMAC1) 64 Byte Frames Transmitted Register */
  #define REG_GMAC1_TBFT127   (*(__I  uint32_t*)0xFC02811CU) /**< \brief (GMAC1) 65 to 127 Byte Frames Transmitted Register */
  #define REG_GMAC1_TBFT255   (*(__I  uint32_t*)0xFC028120U) /**< \brief (GMAC1) 128 to 255 Byte Frames Transmitted Register */
  #define REG_GMAC1_TBFT511   (*(__I  uint32_t*)0xFC028124U) /**< \brief (GMAC1) 256 to 511 Byte Frames Transmitted Register */
  #define REG_GMAC1_TBFT1023  (*(__I  uint32_t*)0xFC028128U) /**< \brief (GMAC1) 512 to 1023 Byte Frames Transmitted Register */
  #define REG_GMAC1_TBFT1518  (*(__I  uint32_t*)0xFC02812CU) /**< \brief (GMAC1) 1024 to 1518 Byte Frames Transmitted Register */
  #define REG_GMAC1_GTBFT1518 (*(__I  uint32_t*)0xFC028130U) /**< \brief (GMAC1) Greater Than 1518 Byte Frames Transmitted Register */
  #define REG_GMAC1_TUR       (*(__I  uint32_t*)0xFC028134U) /**< \brief (GMAC1) Transmit Underruns Register */
  #define REG_GMAC1_SCF       (*(__I  uint32_t*)0xFC028138U) /**< \brief (GMAC1) Single Collision Frames Register */
  #define REG_GMAC1_MCF       (*(__I  uint32_t*)0xFC02813CU) /**< \brief (GMAC1) Multiple Collision Frames Register */
  #define REG_GMAC1_EC        (*(__I  uint32_t*)0xFC028140U) /**< \brief (GMAC1) Excessive Collisions Register */
  #define REG_GMAC1_LC        (*(__I  uint32_t*)0xFC028144U) /**< \brief (GMAC1) Late Collisions Register */
  #define REG_GMAC1_DTF       (*(__I  uint32_t*)0xFC028148U) /**< \brief (GMAC1) Deferred Transmission Frames Register */
  #define REG_GMAC1_CSE       (*(__I  uint32_t*)0xFC02814CU) /**< \brief (GMAC1) Carrier Sense Errors Register */
  #define REG_GMAC1_ORLO      (*(__I  uint32_t*)0xFC028150U) /**< \brief (GMAC1) Octets Received [31:0] Received */
  #define REG_GMAC1_ORHI      (*(__I  uint32_t*)0xFC028154U) /**< \brief (GMAC1) Octets Received [47:32] Received */
  #define REG_GMAC1_FR        (*(__I  uint32_t*)0xFC028158U) /**< \brief (GMAC1) Frames Received Register */
  #define REG_GMAC1_BCFR      (*(__I  uint32_t*)0xFC02815CU) /**< \brief (GMAC1) Broadcast Frames Received Register */
  #define REG_GMAC1_MFR       (*(__I  uint32_t*)0xFC028160U) /**< \brief (GMAC1) Multicast Frames Received Register */
  #define REG_GMAC1_PFR       (*(__I  uint32_t*)0xFC028164U) /**< \brief (GMAC1) Pause Frames Received Register */
  #define REG_GMAC1_BFR64     (*(__I  uint32_t*)0xFC028168U) /**< \brief (GMAC1) 64 Byte Frames Received Register */
  #define REG_GMAC1_TBFR127   (*(__I  uint32_t*)0xFC02816CU) /**< \brief (GMAC1) 65 to 127 Byte Frames Received Register */
  #define REG_GMAC1_TBFR255   (*(__I  uint32_t*)0xFC028170U) /**< \brief (GMAC1) 128 to 255 Byte Frames Received Register */
  #define REG_GMAC1_TBFR511   (*(__I  uint32_t*)0xFC028174U) /**< \brief (GMAC1) 256 to 511Byte Frames Received Register */
  #define REG_GMAC1_TBFR1023  (*(__I  uint32_t*)0xFC028178U) /**< \brief (GMAC1) 512 to 1023 Byte Frames Received Register */
  #define REG_GMAC1_TBFR1518  (*(__I  uint32_t*)0xFC02817CU) /**< \brief (GMAC1) 1024 to 1518 Byte Frames Received Register */
  #define REG_GMAC1_TMXBFR    (*(__I  uint32_t*)0xFC028180U) /**< \brief (GMAC1) 1519 to Maximum Byte Frames Received Register */
  #define REG_GMAC1_UFR       (*(__I  uint32_t*)0xFC028184U) /**< \brief (GMAC1) Undersize Frames Received Register */
  #define REG_GMAC1_OFR       (*(__I  uint32_t*)0xFC028188U) /**< \brief (GMAC1) Oversize Frames Received Register */
  #define REG_GMAC1_JR        (*(__I  uint32_t*)0xFC02818CU) /**< \brief (GMAC1) Jabbers Received Register */
  #define REG_GMAC1_FCSE      (*(__I  uint32_t*)0xFC028190U) /**< \brief (GMAC1) Frame Check Sequence Errors Register */
  #define REG_GMAC1_LFFE      (*(__I  uint32_t*)0xFC028194U) /**< \brief (GMAC1) Length Field Frame Errors Register */
  #define REG_GMAC1_RSE       (*(__I  uint32_t*)0xFC028198U) /**< \brief (GMAC1) Receive Symbol Errors Register */
  #define REG_GMAC1_AE        (*(__I  uint32_t*)0xFC02819CU) /**< \brief (GMAC1) Alignment Errors Register */
  #define REG_GMAC1_RRE       (*(__I  uint32_t*)0xFC0281A0U) /**< \brief (GMAC1) Receive Resource Errors Register */
  #define REG_GMAC1_ROE       (*(__I  uint32_t*)0xFC0281A4U) /**< \brief (GMAC1) Receive Overrun Register */
  #define REG_GMAC1_IHCE      (*(__I  uint32_t*)0xFC0281A8U) /**< \brief (GMAC1) IP Header Checksum Errors Register */
  #define REG_GMAC1_TCE       (*(__I  uint32_t*)0xFC0281ACU) /**< \brief (GMAC1) TCP Checksum Errors Register */
  #define REG_GMAC1_UCE       (*(__I  uint32_t*)0xFC0281B0U) /**< \brief (GMAC1) UDP Checksum Errors Register */
  #define REG_GMAC1_TSSSL     (*(__IO uint32_t*)0xFC0281C8U) /**< \brief (GMAC1) 1588 Timer Sync Strobe Seconds [31:0] Register */
  #define REG_GMAC1_TSSN      (*(__IO uint32_t*)0xFC0281CCU) /**< \brief (GMAC1) 1588 Timer Sync Strobe Nanoseconds Register */
  #define REG_GMAC1_TSL       (*(__IO uint32_t*)0xFC0281D0U) /**< \brief (GMAC1) 1588 Timer Seconds [31:0] Register */
  #define REG_GMAC1_TN        (*(__IO uint32_t*)0xFC0281D4U) /**< \brief (GMAC1) 1588 Timer Nanoseconds Register */
  #define REG_GMAC1_TA        (*(__O  uint32_t*)0xFC0281D8U) /**< \brief (GMAC1) 1588 Timer Adjust Register */
  #define REG_GMAC1_TI        (*(__IO uint32_t*)0xFC0281DCU) /**< \brief (GMAC1) 1588 Timer Increment Register */
  #define REG_GMAC1_EFTS      (*(__I  uint32_t*)0xFC0281E0U) /**< \brief (GMAC1) PTP Event Frame Transmitted Seconds */
  #define REG_GMAC1_EFTN      (*(__I  uint32_t*)0xFC0281E4U) /**< \brief (GMAC1) PTP Event Frame Transmitted Nanoseconds */
  #define REG_GMAC1_EFRS      (*(__I  uint32_t*)0xFC0281E8U) /**< \brief (GMAC1) PTP Event Frame Received Seconds */
  #define REG_GMAC1_EFRN      (*(__I  uint32_t*)0xFC0281ECU) /**< \brief (GMAC1) PTP Event Frame Received Nanoseconds */
  #define REG_GMAC1_PEFTS     (*(__I  uint32_t*)0xFC0281F0U) /**< \brief (GMAC1) PTP Peer Event Frame Transmitted Seconds */
  #define REG_GMAC1_PEFTN     (*(__I  uint32_t*)0xFC0281F4U) /**< \brief (GMAC1) PTP Peer Event Frame Transmitted Nanoseconds */
  #define REG_GMAC1_PEFRS     (*(__I  uint32_t*)0xFC0281F8U) /**< \brief (GMAC1) PTP Peer Event Frame Received Seconds */
  #define REG_GMAC1_PEFRN     (*(__I  uint32_t*)0xFC0281FCU) /**< \brief (GMAC1) PTP Peer Event Frame Received Nanoseconds */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D4_GMAC1_INSTANCE_ */
