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

#ifndef _SAM9X_OTPC_COMPONENT_
#define _SAM9X_OTPC_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR OTP Memory Controller */
/* ============================================================================= */
/** \addtogroup SAM9X_OTPC OTP Memory Controller */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Otpc hardware registers */
typedef struct {
  __O  uint32_t OTPC_CR;       /**< \brief (Otpc Offset: 0x0) Control Register */
  __IO uint32_t OTPC_MR;       /**< \brief (Otpc Offset: 0x4) Mode Register */
  __IO uint32_t OTPC_AR;       /**< \brief (Otpc Offset: 0x8) Address Register */
  __I  uint32_t OTPC_SR;       /**< \brief (Otpc Offset: 0xC) Status Register */
  __O  uint32_t OTPC_IER;      /**< \brief (Otpc Offset: 0x10) Interrupt Enable Register */
  __O  uint32_t OTPC_IDR;      /**< \brief (Otpc Offset: 0x14) Interrupt Disable Register */
  __I  uint32_t OTPC_IMR;      /**< \brief (Otpc Offset: 0x18) Interrupt Mask Register */
  __I  uint32_t OTPC_ISR;      /**< \brief (Otpc Offset: 0x1C) Interrupt Status Register */
  __IO uint32_t OTPC_HR;       /**< \brief (Otpc Offset: 0x20) Header Register */
  __IO uint32_t OTPC_DR;       /**< \brief (Otpc Offset: 0x24) Data Register */
  __I  uint32_t Reserved1[2];
  __I  uint32_t OTPC_BAR;      /**< \brief (Otpc Offset: 0x30) Boot Addresses Register */
  __I  uint32_t OTPC_CAR;      /**< \brief (Otpc Offset: 0x34) Custom Address Register */
  __I  uint32_t Reserved2[6];
  __I  uint32_t OTPC_UHC0R;    /**< \brief (Otpc Offset: 0x50) User Hardware Configuration 0 Register */
  __I  uint32_t OTPC_UHC1R;    /**< \brief (Otpc Offset: 0x54) User Hardware Configuration 1 Register */
  __I  uint32_t Reserved3[2];
  __I  uint32_t OTPC_UIDxR[4]; /**< \brief (Otpc Offset: 0x60) Product UID x Register */
  __I  uint32_t Reserved4[29];
  __IO uint32_t OTPC_WPMR;     /**< \brief (Otpc Offset: 0xE4) Write Protection Mode Register */
  __I  uint32_t OTPC_WPSR;     /**< \brief (Otpc Offset: 0xE8) Write Protection Status Register */
} Otpc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- OTPC_CR : (OTPC Offset: 0x0) Control Register -------- */
#define OTPC_CR_PGM (0x1u << 0) /**< \brief (OTPC_CR) Program Packet */
#define OTPC_CR_CKSGEN (0x1u << 1) /**< \brief (OTPC_CR) Generate Checksum */
#define OTPC_CR_INVLD (0x1u << 2) /**< \brief (OTPC_CR) Invalidate Packet */
#define OTPC_CR_HIDE (0x1u << 4) /**< \brief (OTPC_CR) Hide Packet */
#define OTPC_CR_READ (0x1u << 6) /**< \brief (OTPC_CR) Read Packet */
#define OTPC_CR_FLUSH (0x1u << 7) /**< \brief (OTPC_CR) Flush Temporary Registers */
#define OTPC_CR_KBSTART (0x1u << 8) /**< \brief (OTPC_CR) Key Bus Transfer Start */
#define OTPC_CR_KBSTOP (0x1u << 9) /**< \brief (OTPC_CR) Key Bus Transfer Stop */
#define OTPC_CR_REFRESH (0x1u << 15) /**< \brief (OTPC_CR) Refresh the Area */
#define OTPC_CR_KEY_Pos 16
#define OTPC_CR_KEY_Msk (0xffffu << OTPC_CR_KEY_Pos) /**< \brief (OTPC_CR) Programming Key */
#define OTPC_CR_KEY(value) ((OTPC_CR_KEY_Msk & ((value) << OTPC_CR_KEY_Pos)))
/* -------- OTPC_MR : (OTPC Offset: 0x4) Mode Register -------- */
#define OTPC_MR_UHCRRDIS (0x1u << 0) /**< \brief (OTPC_MR) User Hardware Configuration Register Read Disable */
#define OTPC_MR_NPCKT (0x1u << 4) /**< \brief (OTPC_MR) New Packet */
#define OTPC_MR_EMUL (0x1u << 7) /**< \brief (OTPC_MR) Emulation Enable */
#define OTPC_MR_RDDIS (0x1u << 8) /**< \brief (OTPC_MR) Read Disable */
#define OTPC_MR_WRDIS (0x1u << 9) /**< \brief (OTPC_MR) Write Disable */
#define OTPC_MR_KBDST (0x1u << 12) /**< \brief (OTPC_MR) Key Bus Destination */
#define   OTPC_MR_KBDST_TDES (0x0u << 12) /**< \brief (OTPC_MR) The TDES is the destination of the key transfer. */
#define   OTPC_MR_KBDST_AES (0x1u << 12) /**< \brief (OTPC_MR) The AES is the destination of the key transfer. */
#define OTPC_MR_LOCK (0x1u << 15) /**< \brief (OTPC_MR) Lock Register */
#define OTPC_MR_ADDR_Pos 16
#define OTPC_MR_ADDR_Msk (0xffffu << OTPC_MR_ADDR_Pos) /**< \brief (OTPC_MR) Address */
#define OTPC_MR_ADDR(value) ((OTPC_MR_ADDR_Msk & ((value) << OTPC_MR_ADDR_Pos)))
/* -------- OTPC_AR : (OTPC Offset: 0x8) Address Register -------- */
#define OTPC_AR_DADDR_Pos 0
#define OTPC_AR_DADDR_Msk (0xffu << OTPC_AR_DADDR_Pos) /**< \brief (OTPC_AR) Data Address */
#define OTPC_AR_DADDR(value) ((OTPC_AR_DADDR_Msk & ((value) << OTPC_AR_DADDR_Pos)))
#define OTPC_AR_INCRT (0x1u << 16) /**< \brief (OTPC_AR) Increment Type */
#define   OTPC_AR_INCRT_AFTER_READ (0x0u << 16) /**< \brief (OTPC_AR) Increment DADDR after a read of OTPC_DR. */
#define   OTPC_AR_INCRT_AFTER_WRITE (0x1u << 16) /**< \brief (OTPC_AR) Increment DADDR after a write of OTPC_DR. */
/* -------- OTPC_SR : (OTPC Offset: 0xC) Status Register -------- */
#define OTPC_SR_PGM (0x1u << 0) /**< \brief (OTPC_SR) Programming On-Going */
#define OTPC_SR_LOCK (0x1u << 1) /**< \brief (OTPC_SR) Lock On-Going */
#define OTPC_SR_INVLD (0x1u << 2) /**< \brief (OTPC_SR) Invalidation On-Going */
#define OTPC_SR_EMUL (0x1u << 3) /**< \brief (OTPC_SR) Emulation Enabled */
#define OTPC_SR_MKBB (0x1u << 4) /**< \brief (OTPC_SR) Master Key Bus Busy */
#define OTPC_SR_SKBB (0x1u << 5) /**< \brief (OTPC_SR) Slave Key Bus Busy */
#define OTPC_SR_READ (0x1u << 6) /**< \brief (OTPC_SR) Read On-Going */
#define OTPC_SR_FLUSH (0x1u << 7) /**< \brief (OTPC_SR) Flush On-Going */
#define OTPC_SR_HIDE (0x1u << 8) /**< \brief (OTPC_SR) Hiding On-Going */
#define OTPC_SR_ONEF (0x1u << 9) /**< \brief (OTPC_SR) One Found */
#define OTPC_SR_UNLOCK (0x1u << 11) /**< \brief (OTPC_SR) OTP Registers Unlocked */
/* -------- OTPC_IER : (OTPC Offset: 0x10) Interrupt Enable Register -------- */
#define OTPC_IER_EOP (0x1u << 0) /**< \brief (OTPC_IER) End Of Programming Interrupt Enable */
#define OTPC_IER_EOL (0x1u << 1) /**< \brief (OTPC_IER) End Of Locking Interrupt Enable */
#define OTPC_IER_EOI (0x1u << 2) /**< \brief (OTPC_IER) End Of Invalidation Interrupt Enable */
#define OTPC_IER_EOKT (0x1u << 3) /**< \brief (OTPC_IER) End Of Key Transfer Interrupt Enable */
#define OTPC_IER_PGERR (0x1u << 4) /**< \brief (OTPC_IER) Programming Error Interrupt Enable */
#define OTPC_IER_LKERR (0x1u << 5) /**< \brief (OTPC_IER) Locking Error Interrupt Enable */
#define OTPC_IER_IVERR (0x1u << 6) /**< \brief (OTPC_IER) Invalidation Error Interrupt Enable */
#define OTPC_IER_WERR (0x1u << 7) /**< \brief (OTPC_IER) Write Error Interrupt Enable */
#define OTPC_IER_EOR (0x1u << 8) /**< \brief (OTPC_IER) End Of Read Interrupt Enable */
#define OTPC_IER_EOF (0x1u << 9) /**< \brief (OTPC_IER) End Of Flush Interrupt Enable */
#define OTPC_IER_EOH (0x1u << 10) /**< \brief (OTPC_IER) End Of Hide Interrupt Enable */
#define OTPC_IER_EORF (0x1u << 11) /**< \brief (OTPC_IER) End Of Refresh Interrupt Enable */
#define OTPC_IER_CKERR (0x1u << 12) /**< \brief (OTPC_IER) Checksum Check Error Interrupt Enable */
#define OTPC_IER_COERR (0x1u << 13) /**< \brief (OTPC_IER) Corruption Error Interrupt Enable */
#define OTPC_IER_HDERR (0x1u << 14) /**< \brief (OTPC_IER) Hide Error Interrupt Enable */
#define OTPC_IER_KBERR (0x1u << 16) /**< \brief (OTPC_IER) Key Bus Error Interrupt Enable */
#define OTPC_IER_SECE (0x1u << 28) /**< \brief (OTPC_IER) Security and/or Safety Event Interrupt Enable */
/* -------- OTPC_IDR : (OTPC Offset: 0x14) Interrupt Disable Register -------- */
#define OTPC_IDR_EOP (0x1u << 0) /**< \brief (OTPC_IDR) End Of Programming Interrupt Disable */
#define OTPC_IDR_EOL (0x1u << 1) /**< \brief (OTPC_IDR) End Of Locking Interrupt Disable */
#define OTPC_IDR_EOI (0x1u << 2) /**< \brief (OTPC_IDR) End Of Invalidation Interrupt Disable */
#define OTPC_IDR_EOKT (0x1u << 3) /**< \brief (OTPC_IDR) End Of Key Transfer Interrupt Disable */
#define OTPC_IDR_PGERR (0x1u << 4) /**< \brief (OTPC_IDR) Programming Error Interrupt Disable */
#define OTPC_IDR_LKERR (0x1u << 5) /**< \brief (OTPC_IDR) Locking Error Interrupt Disable */
#define OTPC_IDR_IVERR (0x1u << 6) /**< \brief (OTPC_IDR) Invalidation Error Interrupt Disable */
#define OTPC_IDR_WERR (0x1u << 7) /**< \brief (OTPC_IDR) Write Error Interrupt Disable */
#define OTPC_IDR_EOR (0x1u << 8) /**< \brief (OTPC_IDR) End Of Read Interrupt Disable */
#define OTPC_IDR_EOF (0x1u << 9) /**< \brief (OTPC_IDR) End Of Flush Interrupt Disable */
#define OTPC_IDR_EOH (0x1u << 10) /**< \brief (OTPC_IDR) End Of Hide Interrupt Disable */
#define OTPC_IDR_EORF (0x1u << 11) /**< \brief (OTPC_IDR) End Of Refresh Interrupt Disable */
#define OTPC_IDR_CKERR (0x1u << 12) /**< \brief (OTPC_IDR) Checksum Check Error Interrupt Disable */
#define OTPC_IDR_COERR (0x1u << 13) /**< \brief (OTPC_IDR) Corruption Error Interrupt Disable */
#define OTPC_IDR_HDERR (0x1u << 14) /**< \brief (OTPC_IDR) Hide Error Interrupt Disable */
#define OTPC_IDR_KBERR (0x1u << 16) /**< \brief (OTPC_IDR) Key Bus Error Interrupt Disable */
#define OTPC_IDR_SECE (0x1u << 28) /**< \brief (OTPC_IDR) Security and/or Safety Event Interrupt Disable */
/* -------- OTPC_IMR : (OTPC Offset: 0x18) Interrupt Mask Register -------- */
#define OTPC_IMR_EOP (0x1u << 0) /**< \brief (OTPC_IMR) End Of Programming Interrupt Mask */
#define OTPC_IMR_EOL (0x1u << 1) /**< \brief (OTPC_IMR) End Of Locking Interrupt Mask */
#define OTPC_IMR_EOI (0x1u << 2) /**< \brief (OTPC_IMR) End Of Invalidation Interrupt Mask */
#define OTPC_IMR_EOKT (0x1u << 3) /**< \brief (OTPC_IMR) End Of Key Transfer Interrupt Mask */
#define OTPC_IMR_PGERR (0x1u << 4) /**< \brief (OTPC_IMR) Programming Error Interrupt Mask */
#define OTPC_IMR_LKERR (0x1u << 5) /**< \brief (OTPC_IMR) Locking Error Interrupt Mask */
#define OTPC_IMR_IVERR (0x1u << 6) /**< \brief (OTPC_IMR) Invalidation Error Interrupt Mask */
#define OTPC_IMR_WERR (0x1u << 7) /**< \brief (OTPC_IMR) Write Error Interrupt Mask */
#define OTPC_IMR_EOR (0x1u << 8) /**< \brief (OTPC_IMR) End Of Read Interrupt Mask */
#define OTPC_IMR_EOF (0x1u << 9) /**< \brief (OTPC_IMR) End Of Flush Interrupt Mask */
#define OTPC_IMR_EOH (0x1u << 10) /**< \brief (OTPC_IMR) End Of Hide Interrupt Mask */
#define OTPC_IMR_EORF (0x1u << 11) /**< \brief (OTPC_IMR) End Of Refresh Interrupt Mask */
#define OTPC_IMR_CKERR (0x1u << 12) /**< \brief (OTPC_IMR) Checksum Check Error Interrupt Mask */
#define OTPC_IMR_COERR (0x1u << 13) /**< \brief (OTPC_IMR) Corruption Error Interrupt Mask */
#define OTPC_IMR_HDERR (0x1u << 14) /**< \brief (OTPC_IMR) Hide Error Interrupt Mask */
#define OTPC_IMR_KBERR (0x1u << 16) /**< \brief (OTPC_IMR) Key Bus Error Interrupt Mask */
#define OTPC_IMR_SECE (0x1u << 28) /**< \brief (OTPC_IMR) Security and/or Safety Event Interrupt Mask */
/* -------- OTPC_ISR : (OTPC Offset: 0x1C) Interrupt Status Register -------- */
#define OTPC_ISR_EOP (0x1u << 0) /**< \brief (OTPC_ISR) End Of Programming (cleared on read) */
#define OTPC_ISR_EOL (0x1u << 1) /**< \brief (OTPC_ISR) End Of Locking (cleared on read) */
#define OTPC_ISR_EOI (0x1u << 2) /**< \brief (OTPC_ISR) End Of Invalidation (cleared on read) */
#define OTPC_ISR_EOKT (0x1u << 3) /**< \brief (OTPC_ISR) End Of Key Transfer (cleared on read) */
#define OTPC_ISR_PGERR (0x1u << 4) /**< \brief (OTPC_ISR) Programming Error (cleared on read) */
#define OTPC_ISR_LKERR (0x1u << 5) /**< \brief (OTPC_ISR) Locking Error (cleared on read) */
#define OTPC_ISR_IVERR (0x1u << 6) /**< \brief (OTPC_ISR) Invalidation Error (cleared on read) */
#define OTPC_ISR_WERR (0x1u << 7) /**< \brief (OTPC_ISR) Write Error (cleared on read) */
#define OTPC_ISR_EOR (0x1u << 8) /**< \brief (OTPC_ISR) End Of Read (cleared on read) */
#define OTPC_ISR_EOF (0x1u << 9) /**< \brief (OTPC_ISR) End Of Flush (cleared on read) */
#define OTPC_ISR_EOH (0x1u << 10) /**< \brief (OTPC_ISR) End Of Hide (cleared on read) */
#define OTPC_ISR_EORF (0x1u << 11) /**< \brief (OTPC_ISR) End Of Refresh (cleared on read) */
#define OTPC_ISR_CKERR (0x1u << 12) /**< \brief (OTPC_ISR) Checksum Check Error (cleared on read) */
#define OTPC_ISR_COERR (0x1u << 13) /**< \brief (OTPC_ISR) Corruption Error (cleared on read) */
#define OTPC_ISR_HDERR (0x1u << 14) /**< \brief (OTPC_ISR) Hide Error (cleared on read) */
#define OTPC_ISR_KBERR (0x1u << 16) /**< \brief (OTPC_ISR) Key Bus Error (cleared on read) */
#define OTPC_ISR_SECE (0x1u << 28) /**< \brief (OTPC_ISR) Security and/or Safety Event (cleared on read) */
/* -------- OTPC_HR : (OTPC Offset: 0x20) Header Register -------- */
#define OTPC_HR_PACKET_Pos 0
#define OTPC_HR_PACKET_Msk (0x7u << OTPC_HR_PACKET_Pos) /**< \brief (OTPC_HR) Packet Type */
#define OTPC_HR_PACKET(value) ((OTPC_HR_PACKET_Msk & ((value) << OTPC_HR_PACKET_Pos)))
#define   OTPC_HR_PACKET_REGULAR (0x1u << 0) /**< \brief (OTPC_HR) Regular packet accessible through the User Interface */
#define   OTPC_HR_PACKET_KEY (0x2u << 0) /**< \brief (OTPC_HR) Key packet accessible only through the Key Buses */
#define   OTPC_HR_PACKET_BOOT_CONFIGURATION (0x3u << 0) /**< \brief (OTPC_HR) Boot Configuration packet */
#define   OTPC_HR_PACKET_SECURE_BOOT_CONFIGURATION (0x4u << 0) /**< \brief (OTPC_HR) Secure Boot Configuration packet */
#define   OTPC_HR_PACKET_HARDWARE_CONFIGURATION (0x5u << 0) /**< \brief (OTPC_HR) Hardware Configuration packet */
#define   OTPC_HR_PACKET_CUSTOM (0x6u << 0) /**< \brief (OTPC_HR) Custom packet */
#define OTPC_HR_LOCK (0x1u << 3) /**< \brief (OTPC_HR) Lock Status */
#define OTPC_HR_INVLD_Pos 4
#define OTPC_HR_INVLD_Msk (0x3u << OTPC_HR_INVLD_Pos) /**< \brief (OTPC_HR) Invalid Status */
#define OTPC_HR_INVLD(value) ((OTPC_HR_INVLD_Msk & ((value) << OTPC_HR_INVLD_Pos)))
#define OTPC_HR_ONE (0x1u << 7) /**< \brief (OTPC_HR) One */
#define OTPC_HR_SIZE_Pos 8
#define OTPC_HR_SIZE_Msk (0xffu << OTPC_HR_SIZE_Pos) /**< \brief (OTPC_HR) Packet Size */
#define OTPC_HR_SIZE(value) ((OTPC_HR_SIZE_Msk & ((value) << OTPC_HR_SIZE_Pos)))
#define OTPC_HR_CHECKSUM_Pos 16
#define OTPC_HR_CHECKSUM_Msk (0xffffu << OTPC_HR_CHECKSUM_Pos) /**< \brief (OTPC_HR) Packet Checksum */
#define OTPC_HR_CHECKSUM(value) ((OTPC_HR_CHECKSUM_Msk & ((value) << OTPC_HR_CHECKSUM_Pos)))
/* -------- OTPC_DR : (OTPC Offset: 0x24) Data Register -------- */
#define OTPC_DR_DATA_Pos 0
#define OTPC_DR_DATA_Msk (0xffffffffu << OTPC_DR_DATA_Pos) /**< \brief (OTPC_DR) Packet Data */
#define OTPC_DR_DATA(value) ((OTPC_DR_DATA_Msk & ((value) << OTPC_DR_DATA_Pos)))
/* -------- OTPC_BAR : (OTPC Offset: 0x30) Boot Addresses Register -------- */
#define OTPC_BAR_BCADDR_Pos 0
#define OTPC_BAR_BCADDR_Msk (0xffffu << OTPC_BAR_BCADDR_Pos) /**< \brief (OTPC_BAR) Boot Configuration Address */
#define OTPC_BAR_SBCADDR_Pos 16
#define OTPC_BAR_SBCADDR_Msk (0xffffu << OTPC_BAR_SBCADDR_Pos) /**< \brief (OTPC_BAR) Secure Boot Configuration Address */
/* -------- OTPC_CAR : (OTPC Offset: 0x34) Custom Address Register -------- */
#define OTPC_CAR_CADDR_Pos 0
#define OTPC_CAR_CADDR_Msk (0xffffu << OTPC_CAR_CADDR_Pos) /**< \brief (OTPC_CAR) Custom Address */
/* -------- OTPC_UHC0R : (OTPC Offset: 0x50) User Hardware Configuration 0 Register -------- */
#define OTPC_UHC0R_JTAGDIS_Pos 0
#define OTPC_UHC0R_JTAGDIS_Msk (0xffu << OTPC_UHC0R_JTAGDIS_Pos) /**< \brief (OTPC_UHC0R) JTAG Disable */
/* -------- OTPC_UHC1R : (OTPC Offset: 0x54) User Hardware Configuration 1 Register -------- */
#define OTPC_UHC1R_URDDIS (0x1u << 0) /**< \brief (OTPC_UHC1R) User Read Disable */
#define OTPC_UHC1R_UPGDIS (0x1u << 1) /**< \brief (OTPC_UHC1R) User programming Disable */
#define OTPC_UHC1R_UHCINVDIS (0x1u << 2) /**< \brief (OTPC_UHC1R) User Hardware Configuration Packet Invalidation Disable */
#define OTPC_UHC1R_UHCLKDIS (0x1u << 3) /**< \brief (OTPC_UHC1R) User Hardware Configuration Packet Lock Disable */
#define OTPC_UHC1R_UHCPGDIS (0x1u << 4) /**< \brief (OTPC_UHC1R) User Hardware Configuration Packet Program Disable */
#define OTPC_UHC1R_BCINVDIS (0x1u << 5) /**< \brief (OTPC_UHC1R) Boot Configuration Packet Invalidation Disable */
#define OTPC_UHC1R_BCLKDIS (0x1u << 6) /**< \brief (OTPC_UHC1R) Boot Configuration Packet Lock Disable */
#define OTPC_UHC1R_BCPGDIS (0x1u << 7) /**< \brief (OTPC_UHC1R) Boot Configuration Packet Program Disable */
#define OTPC_UHC1R_SBCINVDIS (0x1u << 8) /**< \brief (OTPC_UHC1R) Secure Boot Configuration Packet Invalidation Disable */
#define OTPC_UHC1R_SBCLKDIS (0x1u << 9) /**< \brief (OTPC_UHC1R) Secure Boot Configuration Packet Lock Disable */
#define OTPC_UHC1R_SBCPGDIS (0x1u << 10) /**< \brief (OTPC_UHC1R) Secure Boot Configuration Packet Program Disable */
#define OTPC_UHC1R_CINVDIS (0x1u << 14) /**< \brief (OTPC_UHC1R) Custom Packet Invalidation Disable */
#define OTPC_UHC1R_CLKDIS (0x1u << 15) /**< \brief (OTPC_UHC1R) Custom Packet Lock Disable */
#define OTPC_UHC1R_CPGDIS (0x1u << 16) /**< \brief (OTPC_UHC1R) Custom Packet Program Disable */
#define OTPC_UHC1R_URFDIS (0x1u << 17) /**< \brief (OTPC_UHC1R) User Refresh Disable */
/* -------- OTPC_UID0R : (OTPC Offset: 0x60) Product UID 0 Register -------- */
#define OTPC_UID0R_UID_Pos 0
#define OTPC_UID0R_UID_Msk (0xffffffffu << OTPC_UID0R_UID_Pos) /**< \brief (OTPC_UID0R) Unique Product ID */
/* -------- OTPC_UID1R : (OTPC Offset: 0x64) Product UID 1 Register -------- */
#define OTPC_UID1R_UID_Pos 0
#define OTPC_UID1R_UID_Msk (0xffffffffu << OTPC_UID1R_UID_Pos) /**< \brief (OTPC_UID1R) Unique Product ID */
/* -------- OTPC_UID2R : (OTPC Offset: 0x68) Product UID 2 Register -------- */
#define OTPC_UID2R_UID_Pos 0
#define OTPC_UID2R_UID_Msk (0xffffffffu << OTPC_UID2R_UID_Pos) /**< \brief (OTPC_UID2R) Unique Product ID */
/* -------- OTPC_UID3R : (OTPC Offset: 0x6C) Product UID 3 Register -------- */
#define OTPC_UID3R_UID_Pos 0
#define OTPC_UID3R_UID_Msk (0xffffffffu << OTPC_UID3R_UID_Pos) /**< \brief (OTPC_UID3R) Unique Product ID */
/* -------- OTPC_WPMR : (OTPC Offset: 0xE4) Write Protection Mode Register -------- */
#define OTPC_WPMR_WPCFEN (0x1u << 0) /**< \brief (OTPC_WPMR) Write Protection Configuration Enable */
#define OTPC_WPMR_WPITEN (0x1u << 1) /**< \brief (OTPC_WPMR) Write Protection Interrupt Enable */
#define OTPC_WPMR_WPCTEN (0x1u << 2) /**< \brief (OTPC_WPMR) Write Protection Control Enable */
#define OTPC_WPMR_FIRSTE (0x1u << 4) /**< \brief (OTPC_WPMR) First Error Report Enable */
#define OTPC_WPMR_WPKEY_Pos 8
#define OTPC_WPMR_WPKEY_Msk (0xffffffu << OTPC_WPMR_WPKEY_Pos) /**< \brief (OTPC_WPMR) Write Protection Key */
#define OTPC_WPMR_WPKEY(value) ((OTPC_WPMR_WPKEY_Msk & ((value) << OTPC_WPMR_WPKEY_Pos)))
#define   OTPC_WPMR_WPKEY_PASSWD (0x4F5450u << 8) /**< \brief (OTPC_WPMR) Writing any other value in this field aborts the write operation. Always reads as 0. */
/* -------- OTPC_WPSR : (OTPC Offset: 0xE8) Write Protection Status Register -------- */
#define OTPC_WPSR_WPVS (0x1u << 0) /**< \brief (OTPC_WPSR) Write Protection Violation Status (cleared on read) */
#define OTPC_WPSR_CGD (0x1u << 1) /**< \brief (OTPC_WPSR) Clock Glitch Detected (cleared on read) */
#define OTPC_WPSR_SEQE (0x1u << 2) /**< \brief (OTPC_WPSR) Internal Sequencer Error (cleared on read) */
#define OTPC_WPSR_SWE (0x1u << 3) /**< \brief (OTPC_WPSR) Software Control Error (cleared on read) */
#define OTPC_WPSR_WPVSRC_Pos 8
#define OTPC_WPSR_WPVSRC_Msk (0xffffu << OTPC_WPSR_WPVSRC_Pos) /**< \brief (OTPC_WPSR) Write Protection Violation Source */
#define OTPC_WPSR_SWETYP_Pos 24
#define OTPC_WPSR_SWETYP_Msk (0xfu << OTPC_WPSR_SWETYP_Pos) /**< \brief (OTPC_WPSR) Software Error Type */
#define   OTPC_WPSR_SWETYP_READ_WO (0x0u << 24) /**< \brief (OTPC_WPSR) A write-only register has been read (warning). */
#define   OTPC_WPSR_SWETYP_WRITE_RO (0x1u << 24) /**< \brief (OTPC_WPSR) A write access has been performed on a read-only register (warning). */
#define   OTPC_WPSR_SWETYP_CONF_CHG (0x2u << 24) /**< \brief (OTPC_WPSR) A change has been made into the configuration (error). */
#define   OTPC_WPSR_SWETYP_KEY_ERROR (0x3u << 24) /**< \brief (OTPC_WPSR) A write has been computed in OTPC_CR or OTPC_WPMR register with a wrong value in the related KEY field (error). */
#define OTPC_WPSR_ECLASS (0x1u << 31) /**< \brief (OTPC_WPSR) Software Error Class */
#define   OTPC_WPSR_ECLASS_WARNING (0x0u << 31) /**< \brief (OTPC_WPSR) An abnormal access that does not have any impact. */
#define   OTPC_WPSR_ECLASS_ERROR (0x1u << 31) /**< \brief (OTPC_WPSR) An abnormal access that may have an impact. */

/*@}*/


#endif /* _SAM9X_OTPC_COMPONENT_ */
