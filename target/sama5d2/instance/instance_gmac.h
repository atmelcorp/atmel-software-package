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

#ifndef _SAMA5D2_GMAC_INSTANCE_
#define _SAMA5D2_GMAC_INSTANCE_

/* ========== Register definition for GMAC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_GMAC_NCR                        (0xF8008000U) /**< \brief (GMAC) Network Control Register */
  #define REG_GMAC_NCFGR                      (0xF8008004U) /**< \brief (GMAC) Network Configuration Register */
  #define REG_GMAC_NSR                        (0xF8008008U) /**< \brief (GMAC) Network Status Register */
  #define REG_GMAC_UR                         (0xF800800CU) /**< \brief (GMAC) User Register */
  #define REG_GMAC_DCFGR                      (0xF8008010U) /**< \brief (GMAC) DMA Configuration Register */
  #define REG_GMAC_TSR                        (0xF8008014U) /**< \brief (GMAC) Transmit Status Register */
  #define REG_GMAC_RBQB                       (0xF8008018U) /**< \brief (GMAC) Receive Buffer Queue Base Address Register */
  #define REG_GMAC_TBQB                       (0xF800801CU) /**< \brief (GMAC) Transmit Buffer Queue Base Address Register */
  #define REG_GMAC_RSR                        (0xF8008020U) /**< \brief (GMAC) Receive Status Register */
  #define REG_GMAC_ISR                        (0xF8008024U) /**< \brief (GMAC) Interrupt Status Register */
  #define REG_GMAC_IER                        (0xF8008028U) /**< \brief (GMAC) Interrupt Enable Register */
  #define REG_GMAC_IDR                        (0xF800802CU) /**< \brief (GMAC) Interrupt Disable Register */
  #define REG_GMAC_IMR                        (0xF8008030U) /**< \brief (GMAC) Interrupt Mask Register */
  #define REG_GMAC_MAN                        (0xF8008034U) /**< \brief (GMAC) PHY Maintenance Register */
  #define REG_GMAC_RPQ                        (0xF8008038U) /**< \brief (GMAC) Received Pause Quantum Register */
  #define REG_GMAC_TPQ                        (0xF800803CU) /**< \brief (GMAC) Transmit Pause Quantum Register */
  #define REG_GMAC_TPSF                       (0xF8008040U) /**< \brief (GMAC) TX Partial Store and Forward Register */
  #define REG_GMAC_RPSF                       (0xF8008044U) /**< \brief (GMAC) RX Partial Store and Forward Register */
  #define REG_GMAC_RJFML                      (0xF8008048U) /**< \brief (GMAC) RX Jumbo Frame Max Length Register */
  #define REG_GMAC_HRB                        (0xF8008080U) /**< \brief (GMAC) Hash Register Bottom */
  #define REG_GMAC_HRT                        (0xF8008084U) /**< \brief (GMAC) Hash Register Top */
  #define REG_GMAC_SAB1                       (0xF8008088U) /**< \brief (GMAC) Specific Address 1 Bottom Register */
  #define REG_GMAC_SAT1                       (0xF800808CU) /**< \brief (GMAC) Specific Address 1 Top Register */
  #define REG_GMAC_SAB2                       (0xF8008090U) /**< \brief (GMAC) Specific Address 2 Bottom Register */
  #define REG_GMAC_SAT2                       (0xF8008094U) /**< \brief (GMAC) Specific Address 2 Top Register */
  #define REG_GMAC_SAB3                       (0xF8008098U) /**< \brief (GMAC) Specific Address 3 Bottom Register */
  #define REG_GMAC_SAT3                       (0xF800809CU) /**< \brief (GMAC) Specific Address 3 Top Register */
  #define REG_GMAC_SAB4                       (0xF80080A0U) /**< \brief (GMAC) Specific Address 4 Bottom Register */
  #define REG_GMAC_SAT4                       (0xF80080A4U) /**< \brief (GMAC) Specific Address 4 Top Register */
  #define REG_GMAC_TIDM1                      (0xF80080A8U) /**< \brief (GMAC) Type ID Match 1 Register */
  #define REG_GMAC_TIDM2                      (0xF80080ACU) /**< \brief (GMAC) Type ID Match 2 Register */
  #define REG_GMAC_TIDM3                      (0xF80080B0U) /**< \brief (GMAC) Type ID Match 3 Register */
  #define REG_GMAC_TIDM4                      (0xF80080B4U) /**< \brief (GMAC) Type ID Match 4 Register */
  #define REG_GMAC_WOL                        (0xF80080B8U) /**< \brief (GMAC) Wake on LAN Register */
  #define REG_GMAC_IPGS                       (0xF80080BCU) /**< \brief (GMAC) IPG Stretch Register */
  #define REG_GMAC_SVLAN                      (0xF80080C0U) /**< \brief (GMAC) Stacked VLAN Register */
  #define REG_GMAC_TPFCP                      (0xF80080C4U) /**< \brief (GMAC) Transmit PFC Pause Register */
  #define REG_GMAC_SAMB1                      (0xF80080C8U) /**< \brief (GMAC) Specific Address 1 Mask Bottom Register */
  #define REG_GMAC_SAMT1                      (0xF80080CCU) /**< \brief (GMAC) Specific Address 1 Mask Top Register */
  #define REG_GMAC_NSC                        (0xF80080DCU) /**< \brief (GMAC) 1588 Timer Nanosecond Comparison Register */
  #define REG_GMAC_SCL                        (0xF80080E0U) /**< \brief (GMAC) 1588 Timer Second Comparison Low Register */
  #define REG_GMAC_SCH                        (0xF80080E4U) /**< \brief (GMAC) 1588 Timer Second Comparison High Register */
  #define REG_GMAC_EFTSH                      (0xF80080E8U) /**< \brief (GMAC) PTP Event Frame Transmitted Seconds High Register */
  #define REG_GMAC_EFRSH                      (0xF80080ECU) /**< \brief (GMAC) PTP Event Frame Received Seconds High Register */
  #define REG_GMAC_PEFTSH                     (0xF80080F0U) /**< \brief (GMAC) PTP Peer Event Frame Transmitted Seconds High Register */
  #define REG_GMAC_PEFRSH                     (0xF80080F4U) /**< \brief (GMAC) PTP Peer Event Frame Received Seconds High Register */
  #define REG_GMAC_MID                        (0xF80080FCU) /**< \brief (GMAC) Module ID Register */
  #define REG_GMAC_OTLO                       (0xF8008100U) /**< \brief (GMAC) Octets Transmitted Low Register */
  #define REG_GMAC_OTHI                       (0xF8008104U) /**< \brief (GMAC) Octets Transmitted High Register */
  #define REG_GMAC_FT                         (0xF8008108U) /**< \brief (GMAC) Frames Transmitted Register */
  #define REG_GMAC_BCFT                       (0xF800810CU) /**< \brief (GMAC) Broadcast Frames Transmitted Register */
  #define REG_GMAC_MFT                        (0xF8008110U) /**< \brief (GMAC) Multicast Frames Transmitted Register */
  #define REG_GMAC_PFT                        (0xF8008114U) /**< \brief (GMAC) Pause Frames Transmitted Register */
  #define REG_GMAC_BFT64                      (0xF8008118U) /**< \brief (GMAC) 64 Byte Frames Transmitted Register */
  #define REG_GMAC_TBFT127                    (0xF800811CU) /**< \brief (GMAC) 65 to 127 Byte Frames Transmitted Register */
  #define REG_GMAC_TBFT255                    (0xF8008120U) /**< \brief (GMAC) 128 to 255 Byte Frames Transmitted Register */
  #define REG_GMAC_TBFT511                    (0xF8008124U) /**< \brief (GMAC) 256 to 511 Byte Frames Transmitted Register */
  #define REG_GMAC_TBFT1023                   (0xF8008128U) /**< \brief (GMAC) 512 to 1023 Byte Frames Transmitted Register */
  #define REG_GMAC_TBFT1518                   (0xF800812CU) /**< \brief (GMAC) 1024 to 1518 Byte Frames Transmitted Register */
  #define REG_GMAC_GTBFT1518                  (0xF8008130U) /**< \brief (GMAC) Greater Than 1518 Byte Frames Transmitted Register */
  #define REG_GMAC_TUR                        (0xF8008134U) /**< \brief (GMAC) Transmit Underruns Register */
  #define REG_GMAC_SCF                        (0xF8008138U) /**< \brief (GMAC) Single Collision Frames Register */
  #define REG_GMAC_MCF                        (0xF800813CU) /**< \brief (GMAC) Multiple Collision Frames Register */
  #define REG_GMAC_EC                         (0xF8008140U) /**< \brief (GMAC) Excessive Collisions Register */
  #define REG_GMAC_LC                         (0xF8008144U) /**< \brief (GMAC) Late Collisions Register */
  #define REG_GMAC_DTF                        (0xF8008148U) /**< \brief (GMAC) Deferred Transmission Frames Register */
  #define REG_GMAC_CSE                        (0xF800814CU) /**< \brief (GMAC) Carrier Sense Errors Register */
  #define REG_GMAC_ORLO                       (0xF8008150U) /**< \brief (GMAC) Octets Received Low Received Register */
  #define REG_GMAC_ORHI                       (0xF8008154U) /**< \brief (GMAC) Octets Received High Received Register */
  #define REG_GMAC_FR                         (0xF8008158U) /**< \brief (GMAC) Frames Received Register */
  #define REG_GMAC_BCFR                       (0xF800815CU) /**< \brief (GMAC) Broadcast Frames Received Register */
  #define REG_GMAC_MFR                        (0xF8008160U) /**< \brief (GMAC) Multicast Frames Received Register */
  #define REG_GMAC_PFR                        (0xF8008164U) /**< \brief (GMAC) Pause Frames Received Register */
  #define REG_GMAC_BFR64                      (0xF8008168U) /**< \brief (GMAC) 64 Byte Frames Received Register */
  #define REG_GMAC_TBFR127                    (0xF800816CU) /**< \brief (GMAC) 65 to 127 Byte Frames Received Register */
  #define REG_GMAC_TBFR255                    (0xF8008170U) /**< \brief (GMAC) 128 to 255 Byte Frames Received Register */
  #define REG_GMAC_TBFR511                    (0xF8008174U) /**< \brief (GMAC) 256 to 511 Byte Frames Received Register */
  #define REG_GMAC_TBFR1023                   (0xF8008178U) /**< \brief (GMAC) 512 to 1023 Byte Frames Received Register */
  #define REG_GMAC_TBFR1518                   (0xF800817CU) /**< \brief (GMAC) 1024 to 1518 Byte Frames Received Register */
  #define REG_GMAC_TMXBFR                     (0xF8008180U) /**< \brief (GMAC) 1519 to Maximum Byte Frames Received Register */
  #define REG_GMAC_UFR                        (0xF8008184U) /**< \brief (GMAC) Undersize Frames Received Register */
  #define REG_GMAC_OFR                        (0xF8008188U) /**< \brief (GMAC) Oversize Frames Received Register */
  #define REG_GMAC_JR                         (0xF800818CU) /**< \brief (GMAC) Jabbers Received Register */
  #define REG_GMAC_FCSE                       (0xF8008190U) /**< \brief (GMAC) Frame Check Sequence Errors Register */
  #define REG_GMAC_LFFE                       (0xF8008194U) /**< \brief (GMAC) Length Field Frame Errors Register */
  #define REG_GMAC_RSE                        (0xF8008198U) /**< \brief (GMAC) Receive Symbol Errors Register */
  #define REG_GMAC_AE                         (0xF800819CU) /**< \brief (GMAC) Alignment Errors Register */
  #define REG_GMAC_RRE                        (0xF80081A0U) /**< \brief (GMAC) Receive Resource Errors Register */
  #define REG_GMAC_ROE                        (0xF80081A4U) /**< \brief (GMAC) Receive Overrun Register */
  #define REG_GMAC_IHCE                       (0xF80081A8U) /**< \brief (GMAC) IP Header Checksum Errors Register */
  #define REG_GMAC_TCE                        (0xF80081ACU) /**< \brief (GMAC) TCP Checksum Errors Register */
  #define REG_GMAC_UCE                        (0xF80081B0U) /**< \brief (GMAC) UDP Checksum Errors Register */
  #define REG_GMAC_TISUBN                     (0xF80081BCU) /**< \brief (GMAC) 1588 Timer Increment Sub-nanoseconds Register */
  #define REG_GMAC_TSH                        (0xF80081C0U) /**< \brief (GMAC) 1588 Timer Seconds High Register */
  #define REG_GMAC_TSL                        (0xF80081D0U) /**< \brief (GMAC) 1588 Timer Seconds Low Register */
  #define REG_GMAC_TN                         (0xF80081D4U) /**< \brief (GMAC) 1588 Timer Nanoseconds Register */
  #define REG_GMAC_TA                         (0xF80081D8U) /**< \brief (GMAC) 1588 Timer Adjust Register */
  #define REG_GMAC_TI                         (0xF80081DCU) /**< \brief (GMAC) 1588 Timer Increment Register */
  #define REG_GMAC_EFTSL                      (0xF80081E0U) /**< \brief (GMAC) PTP Event Frame Transmitted Seconds Low Register */
  #define REG_GMAC_EFTN                       (0xF80081E4U) /**< \brief (GMAC) PTP Event Frame Transmitted Nanoseconds Register */
  #define REG_GMAC_EFRSL                      (0xF80081E8U) /**< \brief (GMAC) PTP Event Frame Received Seconds Low Register */
  #define REG_GMAC_EFRN                       (0xF80081ECU) /**< \brief (GMAC) PTP Event Frame Received Nanoseconds Register */
  #define REG_GMAC_PEFTSL                     (0xF80081F0U) /**< \brief (GMAC) PTP Peer Event Frame Transmitted Seconds Low Register */
  #define REG_GMAC_PEFTN                      (0xF80081F4U) /**< \brief (GMAC) PTP Peer Event Frame Transmitted Nanoseconds Register */
  #define REG_GMAC_PEFRSL                     (0xF80081F8U) /**< \brief (GMAC) PTP Peer Event Frame Received Seconds Low Register */
  #define REG_GMAC_PEFRN                      (0xF80081FCU) /**< \brief (GMAC) PTP Peer Event Frame Received Nanoseconds Register */
  #define REG_GMAC_ISRPQ                      (0xF8008400U) /**< \brief (GMAC) Interrupt Status Register Priority Queue (index = 1) */
  #define REG_GMAC_TBQBAPQ                    (0xF8008440U) /**< \brief (GMAC) Transmit Buffer Queue Base Address Register Priority Queue (index = 1) */
  #define REG_GMAC_RBQBAPQ                    (0xF8008480U) /**< \brief (GMAC) Receive Buffer Queue Base Address Register Priority Queue (index = 1) */
  #define REG_GMAC_RBSRPQ                     (0xF80084A0U) /**< \brief (GMAC) Receive Buffer Size Register Priority Queue (index = 1) */
  #define REG_GMAC_CBSCR                      (0xF80084BCU) /**< \brief (GMAC) Credit-Based Shaping Control Register */
  #define REG_GMAC_CBSISQA                    (0xF80084C0U) /**< \brief (GMAC) Credit-Based Shaping IdleSlope Register for Queue A */
  #define REG_GMAC_CBSISQB                    (0xF80084C4U) /**< \brief (GMAC) Credit-Based Shaping IdleSlope Register for Queue B */
  #define REG_GMAC_ST1RPQ                     (0xF8008500U) /**< \brief (GMAC) Screening Type 1 Register Priority Queue (index = 0) */
  #define REG_GMAC_ST2RPQ                     (0xF8008540U) /**< \brief (GMAC) Screening Type 2 Register Priority Queue (index = 0) */
  #define REG_GMAC_IERPQ                      (0xF8008600U) /**< \brief (GMAC) Interrupt Enable Register Priority Queue (index = 1) */
  #define REG_GMAC_IDRPQ                      (0xF8008620U) /**< \brief (GMAC) Interrupt Disable Register Priority Queue (index = 1) */
  #define REG_GMAC_IMRPQ                      (0xF8008640U) /**< \brief (GMAC) Interrupt Mask Register Priority Queue (index = 1) */
  #define REG_GMAC_ST2ER                      (0xF80086E0U) /**< \brief (GMAC) Screening Type 2 Ethertype Register (index = 0) */
  #define REG_GMAC_ST2CW00                    (0xF8008700U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 0) */
  #define REG_GMAC_ST2CW10                    (0xF8008704U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 0) */
  #define REG_GMAC_ST2CW01                    (0xF8008708U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 1) */
  #define REG_GMAC_ST2CW11                    (0xF800870CU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 1) */
  #define REG_GMAC_ST2CW02                    (0xF8008710U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 2) */
  #define REG_GMAC_ST2CW12                    (0xF8008714U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 2) */
  #define REG_GMAC_ST2CW03                    (0xF8008718U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 3) */
  #define REG_GMAC_ST2CW13                    (0xF800871CU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 3) */
  #define REG_GMAC_ST2CW04                    (0xF8008720U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 4) */
  #define REG_GMAC_ST2CW14                    (0xF8008724U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 4) */
  #define REG_GMAC_ST2CW05                    (0xF8008728U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 5) */
  #define REG_GMAC_ST2CW15                    (0xF800872CU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 5) */
  #define REG_GMAC_ST2CW06                    (0xF8008730U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 6) */
  #define REG_GMAC_ST2CW16                    (0xF8008734U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 6) */
  #define REG_GMAC_ST2CW07                    (0xF8008738U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 7) */
  #define REG_GMAC_ST2CW17                    (0xF800873CU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 7) */
  #define REG_GMAC_ST2CW08                    (0xF8008740U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 8) */
  #define REG_GMAC_ST2CW18                    (0xF8008744U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 8) */
  #define REG_GMAC_ST2CW09                    (0xF8008748U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 9) */
  #define REG_GMAC_ST2CW19                    (0xF800874CU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 9) */
  #define REG_GMAC_ST2CW010                   (0xF8008750U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 10) */
  #define REG_GMAC_ST2CW110                   (0xF8008754U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 10) */
  #define REG_GMAC_ST2CW011                   (0xF8008758U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 11) */
  #define REG_GMAC_ST2CW111                   (0xF800875CU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 11) */
  #define REG_GMAC_ST2CW012                   (0xF8008760U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 12) */
  #define REG_GMAC_ST2CW112                   (0xF8008764U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 12) */
  #define REG_GMAC_ST2CW013                   (0xF8008768U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 13) */
  #define REG_GMAC_ST2CW113                   (0xF800876CU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 13) */
  #define REG_GMAC_ST2CW014                   (0xF8008770U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 14) */
  #define REG_GMAC_ST2CW114                   (0xF8008774U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 14) */
  #define REG_GMAC_ST2CW015                   (0xF8008778U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 15) */
  #define REG_GMAC_ST2CW115                   (0xF800877CU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 15) */
  #define REG_GMAC_ST2CW016                   (0xF8008780U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 16) */
  #define REG_GMAC_ST2CW116                   (0xF8008784U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 16) */
  #define REG_GMAC_ST2CW017                   (0xF8008788U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 17) */
  #define REG_GMAC_ST2CW117                   (0xF800878CU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 17) */
  #define REG_GMAC_ST2CW018                   (0xF8008790U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 18) */
  #define REG_GMAC_ST2CW118                   (0xF8008794U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 18) */
  #define REG_GMAC_ST2CW019                   (0xF8008798U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 19) */
  #define REG_GMAC_ST2CW119                   (0xF800879CU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 19) */
  #define REG_GMAC_ST2CW020                   (0xF80087A0U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 20) */
  #define REG_GMAC_ST2CW120                   (0xF80087A4U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 20) */
  #define REG_GMAC_ST2CW021                   (0xF80087A8U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 21) */
  #define REG_GMAC_ST2CW121                   (0xF80087ACU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 21) */
  #define REG_GMAC_ST2CW022                   (0xF80087B0U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 22) */
  #define REG_GMAC_ST2CW122                   (0xF80087B4U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 22) */
  #define REG_GMAC_ST2CW023                   (0xF80087B8U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 23) */
  #define REG_GMAC_ST2CW123                   (0xF80087BCU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 23) */
#else
  #define REG_GMAC_NCR       (*(__IO uint32_t*)0xF8008000U) /**< \brief (GMAC) Network Control Register */
  #define REG_GMAC_NCFGR     (*(__IO uint32_t*)0xF8008004U) /**< \brief (GMAC) Network Configuration Register */
  #define REG_GMAC_NSR       (*(__I  uint32_t*)0xF8008008U) /**< \brief (GMAC) Network Status Register */
  #define REG_GMAC_UR        (*(__IO uint32_t*)0xF800800CU) /**< \brief (GMAC) User Register */
  #define REG_GMAC_DCFGR     (*(__IO uint32_t*)0xF8008010U) /**< \brief (GMAC) DMA Configuration Register */
  #define REG_GMAC_TSR       (*(__IO uint32_t*)0xF8008014U) /**< \brief (GMAC) Transmit Status Register */
  #define REG_GMAC_RBQB      (*(__IO uint32_t*)0xF8008018U) /**< \brief (GMAC) Receive Buffer Queue Base Address Register */
  #define REG_GMAC_TBQB      (*(__IO uint32_t*)0xF800801CU) /**< \brief (GMAC) Transmit Buffer Queue Base Address Register */
  #define REG_GMAC_RSR       (*(__IO uint32_t*)0xF8008020U) /**< \brief (GMAC) Receive Status Register */
  #define REG_GMAC_ISR       (*(__I  uint32_t*)0xF8008024U) /**< \brief (GMAC) Interrupt Status Register */
  #define REG_GMAC_IER       (*(__O  uint32_t*)0xF8008028U) /**< \brief (GMAC) Interrupt Enable Register */
  #define REG_GMAC_IDR       (*(__O  uint32_t*)0xF800802CU) /**< \brief (GMAC) Interrupt Disable Register */
  #define REG_GMAC_IMR       (*(__IO uint32_t*)0xF8008030U) /**< \brief (GMAC) Interrupt Mask Register */
  #define REG_GMAC_MAN       (*(__IO uint32_t*)0xF8008034U) /**< \brief (GMAC) PHY Maintenance Register */
  #define REG_GMAC_RPQ       (*(__I  uint32_t*)0xF8008038U) /**< \brief (GMAC) Received Pause Quantum Register */
  #define REG_GMAC_TPQ       (*(__IO uint32_t*)0xF800803CU) /**< \brief (GMAC) Transmit Pause Quantum Register */
  #define REG_GMAC_TPSF      (*(__IO uint32_t*)0xF8008040U) /**< \brief (GMAC) TX Partial Store and Forward Register */
  #define REG_GMAC_RPSF      (*(__IO uint32_t*)0xF8008044U) /**< \brief (GMAC) RX Partial Store and Forward Register */
  #define REG_GMAC_RJFML     (*(__IO uint32_t*)0xF8008048U) /**< \brief (GMAC) RX Jumbo Frame Max Length Register */
  #define REG_GMAC_HRB       (*(__IO uint32_t*)0xF8008080U) /**< \brief (GMAC) Hash Register Bottom */
  #define REG_GMAC_HRT       (*(__IO uint32_t*)0xF8008084U) /**< \brief (GMAC) Hash Register Top */
  #define REG_GMAC_SAB1      (*(__IO uint32_t*)0xF8008088U) /**< \brief (GMAC) Specific Address 1 Bottom Register */
  #define REG_GMAC_SAT1      (*(__IO uint32_t*)0xF800808CU) /**< \brief (GMAC) Specific Address 1 Top Register */
  #define REG_GMAC_SAB2      (*(__IO uint32_t*)0xF8008090U) /**< \brief (GMAC) Specific Address 2 Bottom Register */
  #define REG_GMAC_SAT2      (*(__IO uint32_t*)0xF8008094U) /**< \brief (GMAC) Specific Address 2 Top Register */
  #define REG_GMAC_SAB3      (*(__IO uint32_t*)0xF8008098U) /**< \brief (GMAC) Specific Address 3 Bottom Register */
  #define REG_GMAC_SAT3      (*(__IO uint32_t*)0xF800809CU) /**< \brief (GMAC) Specific Address 3 Top Register */
  #define REG_GMAC_SAB4      (*(__IO uint32_t*)0xF80080A0U) /**< \brief (GMAC) Specific Address 4 Bottom Register */
  #define REG_GMAC_SAT4      (*(__IO uint32_t*)0xF80080A4U) /**< \brief (GMAC) Specific Address 4 Top Register */
  #define REG_GMAC_TIDM1     (*(__IO uint32_t*)0xF80080A8U) /**< \brief (GMAC) Type ID Match 1 Register */
  #define REG_GMAC_TIDM2     (*(__IO uint32_t*)0xF80080ACU) /**< \brief (GMAC) Type ID Match 2 Register */
  #define REG_GMAC_TIDM3     (*(__IO uint32_t*)0xF80080B0U) /**< \brief (GMAC) Type ID Match 3 Register */
  #define REG_GMAC_TIDM4     (*(__IO uint32_t*)0xF80080B4U) /**< \brief (GMAC) Type ID Match 4 Register */
  #define REG_GMAC_WOL       (*(__IO uint32_t*)0xF80080B8U) /**< \brief (GMAC) Wake on LAN Register */
  #define REG_GMAC_IPGS      (*(__IO uint32_t*)0xF80080BCU) /**< \brief (GMAC) IPG Stretch Register */
  #define REG_GMAC_SVLAN     (*(__IO uint32_t*)0xF80080C0U) /**< \brief (GMAC) Stacked VLAN Register */
  #define REG_GMAC_TPFCP     (*(__IO uint32_t*)0xF80080C4U) /**< \brief (GMAC) Transmit PFC Pause Register */
  #define REG_GMAC_SAMB1     (*(__IO uint32_t*)0xF80080C8U) /**< \brief (GMAC) Specific Address 1 Mask Bottom Register */
  #define REG_GMAC_SAMT1     (*(__IO uint32_t*)0xF80080CCU) /**< \brief (GMAC) Specific Address 1 Mask Top Register */
  #define REG_GMAC_NSC       (*(__IO uint32_t*)0xF80080DCU) /**< \brief (GMAC) 1588 Timer Nanosecond Comparison Register */
  #define REG_GMAC_SCL       (*(__IO uint32_t*)0xF80080E0U) /**< \brief (GMAC) 1588 Timer Second Comparison Low Register */
  #define REG_GMAC_SCH       (*(__IO uint32_t*)0xF80080E4U) /**< \brief (GMAC) 1588 Timer Second Comparison High Register */
  #define REG_GMAC_EFTSH     (*(__I  uint32_t*)0xF80080E8U) /**< \brief (GMAC) PTP Event Frame Transmitted Seconds High Register */
  #define REG_GMAC_EFRSH     (*(__I  uint32_t*)0xF80080ECU) /**< \brief (GMAC) PTP Event Frame Received Seconds High Register */
  #define REG_GMAC_PEFTSH    (*(__I  uint32_t*)0xF80080F0U) /**< \brief (GMAC) PTP Peer Event Frame Transmitted Seconds High Register */
  #define REG_GMAC_PEFRSH    (*(__I  uint32_t*)0xF80080F4U) /**< \brief (GMAC) PTP Peer Event Frame Received Seconds High Register */
  #define REG_GMAC_MID       (*(__I  uint32_t*)0xF80080FCU) /**< \brief (GMAC) Module ID Register */
  #define REG_GMAC_OTLO      (*(__I  uint32_t*)0xF8008100U) /**< \brief (GMAC) Octets Transmitted Low Register */
  #define REG_GMAC_OTHI      (*(__I  uint32_t*)0xF8008104U) /**< \brief (GMAC) Octets Transmitted High Register */
  #define REG_GMAC_FT        (*(__I  uint32_t*)0xF8008108U) /**< \brief (GMAC) Frames Transmitted Register */
  #define REG_GMAC_BCFT      (*(__I  uint32_t*)0xF800810CU) /**< \brief (GMAC) Broadcast Frames Transmitted Register */
  #define REG_GMAC_MFT       (*(__I  uint32_t*)0xF8008110U) /**< \brief (GMAC) Multicast Frames Transmitted Register */
  #define REG_GMAC_PFT       (*(__I  uint32_t*)0xF8008114U) /**< \brief (GMAC) Pause Frames Transmitted Register */
  #define REG_GMAC_BFT64     (*(__I  uint32_t*)0xF8008118U) /**< \brief (GMAC) 64 Byte Frames Transmitted Register */
  #define REG_GMAC_TBFT127   (*(__I  uint32_t*)0xF800811CU) /**< \brief (GMAC) 65 to 127 Byte Frames Transmitted Register */
  #define REG_GMAC_TBFT255   (*(__I  uint32_t*)0xF8008120U) /**< \brief (GMAC) 128 to 255 Byte Frames Transmitted Register */
  #define REG_GMAC_TBFT511   (*(__I  uint32_t*)0xF8008124U) /**< \brief (GMAC) 256 to 511 Byte Frames Transmitted Register */
  #define REG_GMAC_TBFT1023  (*(__I  uint32_t*)0xF8008128U) /**< \brief (GMAC) 512 to 1023 Byte Frames Transmitted Register */
  #define REG_GMAC_TBFT1518  (*(__I  uint32_t*)0xF800812CU) /**< \brief (GMAC) 1024 to 1518 Byte Frames Transmitted Register */
  #define REG_GMAC_GTBFT1518 (*(__I  uint32_t*)0xF8008130U) /**< \brief (GMAC) Greater Than 1518 Byte Frames Transmitted Register */
  #define REG_GMAC_TUR       (*(__I  uint32_t*)0xF8008134U) /**< \brief (GMAC) Transmit Underruns Register */
  #define REG_GMAC_SCF       (*(__I  uint32_t*)0xF8008138U) /**< \brief (GMAC) Single Collision Frames Register */
  #define REG_GMAC_MCF       (*(__I  uint32_t*)0xF800813CU) /**< \brief (GMAC) Multiple Collision Frames Register */
  #define REG_GMAC_EC        (*(__I  uint32_t*)0xF8008140U) /**< \brief (GMAC) Excessive Collisions Register */
  #define REG_GMAC_LC        (*(__I  uint32_t*)0xF8008144U) /**< \brief (GMAC) Late Collisions Register */
  #define REG_GMAC_DTF       (*(__I  uint32_t*)0xF8008148U) /**< \brief (GMAC) Deferred Transmission Frames Register */
  #define REG_GMAC_CSE       (*(__I  uint32_t*)0xF800814CU) /**< \brief (GMAC) Carrier Sense Errors Register */
  #define REG_GMAC_ORLO      (*(__I  uint32_t*)0xF8008150U) /**< \brief (GMAC) Octets Received Low Received Register */
  #define REG_GMAC_ORHI      (*(__I  uint32_t*)0xF8008154U) /**< \brief (GMAC) Octets Received High Received Register */
  #define REG_GMAC_FR        (*(__I  uint32_t*)0xF8008158U) /**< \brief (GMAC) Frames Received Register */
  #define REG_GMAC_BCFR      (*(__I  uint32_t*)0xF800815CU) /**< \brief (GMAC) Broadcast Frames Received Register */
  #define REG_GMAC_MFR       (*(__I  uint32_t*)0xF8008160U) /**< \brief (GMAC) Multicast Frames Received Register */
  #define REG_GMAC_PFR       (*(__I  uint32_t*)0xF8008164U) /**< \brief (GMAC) Pause Frames Received Register */
  #define REG_GMAC_BFR64     (*(__I  uint32_t*)0xF8008168U) /**< \brief (GMAC) 64 Byte Frames Received Register */
  #define REG_GMAC_TBFR127   (*(__I  uint32_t*)0xF800816CU) /**< \brief (GMAC) 65 to 127 Byte Frames Received Register */
  #define REG_GMAC_TBFR255   (*(__I  uint32_t*)0xF8008170U) /**< \brief (GMAC) 128 to 255 Byte Frames Received Register */
  #define REG_GMAC_TBFR511   (*(__I  uint32_t*)0xF8008174U) /**< \brief (GMAC) 256 to 511 Byte Frames Received Register */
  #define REG_GMAC_TBFR1023  (*(__I  uint32_t*)0xF8008178U) /**< \brief (GMAC) 512 to 1023 Byte Frames Received Register */
  #define REG_GMAC_TBFR1518  (*(__I  uint32_t*)0xF800817CU) /**< \brief (GMAC) 1024 to 1518 Byte Frames Received Register */
  #define REG_GMAC_TMXBFR    (*(__I  uint32_t*)0xF8008180U) /**< \brief (GMAC) 1519 to Maximum Byte Frames Received Register */
  #define REG_GMAC_UFR       (*(__I  uint32_t*)0xF8008184U) /**< \brief (GMAC) Undersize Frames Received Register */
  #define REG_GMAC_OFR       (*(__I  uint32_t*)0xF8008188U) /**< \brief (GMAC) Oversize Frames Received Register */
  #define REG_GMAC_JR        (*(__I  uint32_t*)0xF800818CU) /**< \brief (GMAC) Jabbers Received Register */
  #define REG_GMAC_FCSE      (*(__I  uint32_t*)0xF8008190U) /**< \brief (GMAC) Frame Check Sequence Errors Register */
  #define REG_GMAC_LFFE      (*(__I  uint32_t*)0xF8008194U) /**< \brief (GMAC) Length Field Frame Errors Register */
  #define REG_GMAC_RSE       (*(__I  uint32_t*)0xF8008198U) /**< \brief (GMAC) Receive Symbol Errors Register */
  #define REG_GMAC_AE        (*(__I  uint32_t*)0xF800819CU) /**< \brief (GMAC) Alignment Errors Register */
  #define REG_GMAC_RRE       (*(__I  uint32_t*)0xF80081A0U) /**< \brief (GMAC) Receive Resource Errors Register */
  #define REG_GMAC_ROE       (*(__I  uint32_t*)0xF80081A4U) /**< \brief (GMAC) Receive Overrun Register */
  #define REG_GMAC_IHCE      (*(__I  uint32_t*)0xF80081A8U) /**< \brief (GMAC) IP Header Checksum Errors Register */
  #define REG_GMAC_TCE       (*(__I  uint32_t*)0xF80081ACU) /**< \brief (GMAC) TCP Checksum Errors Register */
  #define REG_GMAC_UCE       (*(__I  uint32_t*)0xF80081B0U) /**< \brief (GMAC) UDP Checksum Errors Register */
  #define REG_GMAC_TISUBN    (*(__IO uint32_t*)0xF80081BCU) /**< \brief (GMAC) 1588 Timer Increment Sub-nanoseconds Register */
  #define REG_GMAC_TSH       (*(__IO uint32_t*)0xF80081C0U) /**< \brief (GMAC) 1588 Timer Seconds High Register */
  #define REG_GMAC_TSL       (*(__IO uint32_t*)0xF80081D0U) /**< \brief (GMAC) 1588 Timer Seconds Low Register */
  #define REG_GMAC_TN        (*(__IO uint32_t*)0xF80081D4U) /**< \brief (GMAC) 1588 Timer Nanoseconds Register */
  #define REG_GMAC_TA        (*(__O  uint32_t*)0xF80081D8U) /**< \brief (GMAC) 1588 Timer Adjust Register */
  #define REG_GMAC_TI        (*(__IO uint32_t*)0xF80081DCU) /**< \brief (GMAC) 1588 Timer Increment Register */
  #define REG_GMAC_EFTSL     (*(__I  uint32_t*)0xF80081E0U) /**< \brief (GMAC) PTP Event Frame Transmitted Seconds Low Register */
  #define REG_GMAC_EFTN      (*(__I  uint32_t*)0xF80081E4U) /**< \brief (GMAC) PTP Event Frame Transmitted Nanoseconds Register */
  #define REG_GMAC_EFRSL     (*(__I  uint32_t*)0xF80081E8U) /**< \brief (GMAC) PTP Event Frame Received Seconds Low Register */
  #define REG_GMAC_EFRN      (*(__I  uint32_t*)0xF80081ECU) /**< \brief (GMAC) PTP Event Frame Received Nanoseconds Register */
  #define REG_GMAC_PEFTSL    (*(__I  uint32_t*)0xF80081F0U) /**< \brief (GMAC) PTP Peer Event Frame Transmitted Seconds Low Register */
  #define REG_GMAC_PEFTN     (*(__I  uint32_t*)0xF80081F4U) /**< \brief (GMAC) PTP Peer Event Frame Transmitted Nanoseconds Register */
  #define REG_GMAC_PEFRSL    (*(__I  uint32_t*)0xF80081F8U) /**< \brief (GMAC) PTP Peer Event Frame Received Seconds Low Register */
  #define REG_GMAC_PEFRN     (*(__I  uint32_t*)0xF80081FCU) /**< \brief (GMAC) PTP Peer Event Frame Received Nanoseconds Register */
  #define REG_GMAC_ISRPQ     (*(__I  uint32_t*)0xF8008400U) /**< \brief (GMAC) Interrupt Status Register Priority Queue (index = 1) */
  #define REG_GMAC_TBQBAPQ   (*(__IO uint32_t*)0xF8008440U) /**< \brief (GMAC) Transmit Buffer Queue Base Address Register Priority Queue (index = 1) */
  #define REG_GMAC_RBQBAPQ   (*(__IO uint32_t*)0xF8008480U) /**< \brief (GMAC) Receive Buffer Queue Base Address Register Priority Queue (index = 1) */
  #define REG_GMAC_RBSRPQ    (*(__IO uint32_t*)0xF80084A0U) /**< \brief (GMAC) Receive Buffer Size Register Priority Queue (index = 1) */
  #define REG_GMAC_CBSCR     (*(__IO uint32_t*)0xF80084BCU) /**< \brief (GMAC) Credit-Based Shaping Control Register */
  #define REG_GMAC_CBSISQA   (*(__IO uint32_t*)0xF80084C0U) /**< \brief (GMAC) Credit-Based Shaping IdleSlope Register for Queue A */
  #define REG_GMAC_CBSISQB   (*(__IO uint32_t*)0xF80084C4U) /**< \brief (GMAC) Credit-Based Shaping IdleSlope Register for Queue B */
  #define REG_GMAC_ST1RPQ    (*(__IO uint32_t*)0xF8008500U) /**< \brief (GMAC) Screening Type 1 Register Priority Queue (index = 0) */
  #define REG_GMAC_ST2RPQ    (*(__IO uint32_t*)0xF8008540U) /**< \brief (GMAC) Screening Type 2 Register Priority Queue (index = 0) */
  #define REG_GMAC_IERPQ     (*(__O  uint32_t*)0xF8008600U) /**< \brief (GMAC) Interrupt Enable Register Priority Queue (index = 1) */
  #define REG_GMAC_IDRPQ     (*(__O  uint32_t*)0xF8008620U) /**< \brief (GMAC) Interrupt Disable Register Priority Queue (index = 1) */
  #define REG_GMAC_IMRPQ     (*(__IO uint32_t*)0xF8008640U) /**< \brief (GMAC) Interrupt Mask Register Priority Queue (index = 1) */
  #define REG_GMAC_ST2ER     (*(__IO uint32_t*)0xF80086E0U) /**< \brief (GMAC) Screening Type 2 Ethertype Register (index = 0) */
  #define REG_GMAC_ST2CW00   (*(__IO uint32_t*)0xF8008700U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 0) */
  #define REG_GMAC_ST2CW10   (*(__IO uint32_t*)0xF8008704U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 0) */
  #define REG_GMAC_ST2CW01   (*(__IO uint32_t*)0xF8008708U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 1) */
  #define REG_GMAC_ST2CW11   (*(__IO uint32_t*)0xF800870CU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 1) */
  #define REG_GMAC_ST2CW02   (*(__IO uint32_t*)0xF8008710U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 2) */
  #define REG_GMAC_ST2CW12   (*(__IO uint32_t*)0xF8008714U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 2) */
  #define REG_GMAC_ST2CW03   (*(__IO uint32_t*)0xF8008718U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 3) */
  #define REG_GMAC_ST2CW13   (*(__IO uint32_t*)0xF800871CU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 3) */
  #define REG_GMAC_ST2CW04   (*(__IO uint32_t*)0xF8008720U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 4) */
  #define REG_GMAC_ST2CW14   (*(__IO uint32_t*)0xF8008724U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 4) */
  #define REG_GMAC_ST2CW05   (*(__IO uint32_t*)0xF8008728U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 5) */
  #define REG_GMAC_ST2CW15   (*(__IO uint32_t*)0xF800872CU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 5) */
  #define REG_GMAC_ST2CW06   (*(__IO uint32_t*)0xF8008730U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 6) */
  #define REG_GMAC_ST2CW16   (*(__IO uint32_t*)0xF8008734U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 6) */
  #define REG_GMAC_ST2CW07   (*(__IO uint32_t*)0xF8008738U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 7) */
  #define REG_GMAC_ST2CW17   (*(__IO uint32_t*)0xF800873CU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 7) */
  #define REG_GMAC_ST2CW08   (*(__IO uint32_t*)0xF8008740U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 8) */
  #define REG_GMAC_ST2CW18   (*(__IO uint32_t*)0xF8008744U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 8) */
  #define REG_GMAC_ST2CW09   (*(__IO uint32_t*)0xF8008748U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 9) */
  #define REG_GMAC_ST2CW19   (*(__IO uint32_t*)0xF800874CU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 9) */
  #define REG_GMAC_ST2CW010  (*(__IO uint32_t*)0xF8008750U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 10) */
  #define REG_GMAC_ST2CW110  (*(__IO uint32_t*)0xF8008754U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 10) */
  #define REG_GMAC_ST2CW011  (*(__IO uint32_t*)0xF8008758U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 11) */
  #define REG_GMAC_ST2CW111  (*(__IO uint32_t*)0xF800875CU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 11) */
  #define REG_GMAC_ST2CW012  (*(__IO uint32_t*)0xF8008760U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 12) */
  #define REG_GMAC_ST2CW112  (*(__IO uint32_t*)0xF8008764U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 12) */
  #define REG_GMAC_ST2CW013  (*(__IO uint32_t*)0xF8008768U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 13) */
  #define REG_GMAC_ST2CW113  (*(__IO uint32_t*)0xF800876CU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 13) */
  #define REG_GMAC_ST2CW014  (*(__IO uint32_t*)0xF8008770U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 14) */
  #define REG_GMAC_ST2CW114  (*(__IO uint32_t*)0xF8008774U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 14) */
  #define REG_GMAC_ST2CW015  (*(__IO uint32_t*)0xF8008778U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 15) */
  #define REG_GMAC_ST2CW115  (*(__IO uint32_t*)0xF800877CU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 15) */
  #define REG_GMAC_ST2CW016  (*(__IO uint32_t*)0xF8008780U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 16) */
  #define REG_GMAC_ST2CW116  (*(__IO uint32_t*)0xF8008784U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 16) */
  #define REG_GMAC_ST2CW017  (*(__IO uint32_t*)0xF8008788U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 17) */
  #define REG_GMAC_ST2CW117  (*(__IO uint32_t*)0xF800878CU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 17) */
  #define REG_GMAC_ST2CW018  (*(__IO uint32_t*)0xF8008790U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 18) */
  #define REG_GMAC_ST2CW118  (*(__IO uint32_t*)0xF8008794U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 18) */
  #define REG_GMAC_ST2CW019  (*(__IO uint32_t*)0xF8008798U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 19) */
  #define REG_GMAC_ST2CW119  (*(__IO uint32_t*)0xF800879CU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 19) */
  #define REG_GMAC_ST2CW020  (*(__IO uint32_t*)0xF80087A0U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 20) */
  #define REG_GMAC_ST2CW120  (*(__IO uint32_t*)0xF80087A4U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 20) */
  #define REG_GMAC_ST2CW021  (*(__IO uint32_t*)0xF80087A8U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 21) */
  #define REG_GMAC_ST2CW121  (*(__IO uint32_t*)0xF80087ACU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 21) */
  #define REG_GMAC_ST2CW022  (*(__IO uint32_t*)0xF80087B0U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 22) */
  #define REG_GMAC_ST2CW122  (*(__IO uint32_t*)0xF80087B4U) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 22) */
  #define REG_GMAC_ST2CW023  (*(__IO uint32_t*)0xF80087B8U) /**< \brief (GMAC) Screening Type 2 Compare Word 0 Register (index = 23) */
  #define REG_GMAC_ST2CW123  (*(__IO uint32_t*)0xF80087BCU) /**< \brief (GMAC) Screening Type 2 Compare Word 1 Register (index = 23) */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_GMAC_INSTANCE_ */
