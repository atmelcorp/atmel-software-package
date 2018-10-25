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
  __O  uint32_t OTPC_CR;        /**< \brief (Otpc Offset: 0x00) Control Register */
  __IO uint32_t OTPC_MR;        /**< \brief (Otpc Offset: 0x04) Mode Register */
  __IO uint32_t OTPC_AR;        /**< \brief (Otpc Offset: 0x08) Address Register */
  __I  uint32_t OTPC_SR;        /**< \brief (Otpc Offset: 0x0C) Status Register */
  __O  uint32_t OTPC_IER;       /**< \brief (Otpc Offset: 0x10) Interrupt Enable Register */
  __O  uint32_t OTPC_IDR;       /**< \brief (Otpc Offset: 0x14) Interrupt Disable Register */
  __I  uint32_t OTPC_IMR;       /**< \brief (Otpc Offset: 0x18) Interrupt Mask Register */
  __I  uint32_t OTPC_ISR;       /**< \brief (Otpc Offset: 0x1C) Interrupt Status Register */
  __IO uint32_t OTPC_HR;        /**< \brief (Otpc Offset: 0x20) Header Register */
  __IO uint32_t OTPC_DR;        /**< \brief (Otpc Offset: 0x24) Data Register */
  __I  uint32_t Reserved1[2];
  __I  uint32_t OTPC_BAR;       /**< \brief (Otpc Offset: 0x30) Boot Addresses Register */
  __I  uint32_t OTPC_CAR;       /**< \brief (Otpc Offset: 0x34) Custom Address Register */
  __I  uint32_t Reserved2[6];
  __I  uint32_t OTPC_UHC0R;     /**< \brief (Otpc Offset: 0x50) User Hardware Configuration 0 Register */
  __I  uint32_t OTPC_UHC1R;     /**< \brief (Otpc Offset: 0x54) User Hardware Configuration 1 Register */
  __I  uint32_t Reserved3[2];
  __I  uint32_t OTPC_UIDxR[4];  /**< \brief (Otpc Offset: 0x60) Product UID Register */
  __IO uint32_t OTPC_HCSR;      /**< \brief (Otpc Offset: 0x70) Hardware Configuration Selection Register */
  __I  uint32_t OTPC_HCDR;      /**< \brief (Otpc Offset: 0x74) Hardware Configuration Data Register */
  __I  uint32_t Reserved4[2];
  __I  uint32_t OTPC_HSxR[2];   /**< \brief (Otpc Offset: 0x80) Hardware Security Register */
  __I  uint32_t Reserved5[2];
  __IO uint32_t OTPC_OMR;       /**< \brief (Otpc Offset: 0x90) OTP Mode Register */
  __I  uint32_t Reserved6[3];
  __IO uint32_t OTPC_ODCxR[4];  /**< \brief (Otpc Offset: 0xA0) OTP DAP Configuration Register */
  __IO uint32_t OTPC_OPCxR[4];  /**< \brief (Otpc Offset: 0xB0) OTP PMC Configuration Register */
  __I  uint32_t Reserved7[9];
  __IO uint32_t OTPC_WPMR;      /**< \brief (Otpc Offset: 0xE4) Write Protection Mode Register */
  __I  uint32_t OTPC_WPSR;      /**< \brief (Otpc Offset: 0xE8) Write Protection Status Register */
  __I  uint32_t Reserved8[4];
  __I  uint32_t OTPC_VERSION;   /**< \brief (Otpc Offset: 0xFC) Version Register */
  __O  uint32_t OTPC_RCR;       /**< \brief (Otpc Offset: 0x100) ROM Control Register */
  __IO uint32_t OTPC_RMR;       /**< \brief (Otpc Offset: 0x104) ROM Mode Register */
  __I  uint32_t Reserved9[2];
  __IO uint32_t OTPC_RAR;       /**< \brief (Otpc Offset: 0x110) ROM Address Register */
  __IO uint32_t OTPC_RDR;       /**< \brief (Otpc Offset: 0x114) ROM Data Register */
  __I  uint32_t Reserved10[58];
  __O  uint32_t OTPC_PCR;       /**< \brief (Otpc Offset: 0x200) Patch Control Register */
  __IO uint32_t OTPC_PMR;       /**< \brief (Otpc Offset: 0x204) Patch Mode Register */
  __IO uint32_t OTPC_PSR;       /**< \brief (Otpc Offset: 0x208) Patch Software Register */
  __I  uint32_t Reserved11[1];
  __IO uint32_t OTPC_PAR;       /**< \brief (Otpc Offset: 0x210) Patch Address Register */
  __IO uint32_t OTPC_PDR;       /**< \brief (Otpc Offset: 0x214) Patch Data Register */
  __I  uint32_t Reserved12[58];
  __O  uint32_t OTPC_ACR;       /**< \brief (Otpc Offset: 0x300) A Control Register */
  __IO uint32_t OTPC_AMR;       /**< \brief (Otpc Offset: 0x304) A Mode Register */
  __IO uint32_t OTPC_AAR;       /**< \brief (Otpc Offset: 0x308) A Address Register */
  __I  uint32_t Reserved13[1];
  __IO uint32_t OTPC_AHR;       /**< \brief (Otpc Offset: 0x310) A Header Register */
  __IO uint32_t OTPC_ADR;       /**< \brief (Otpc Offset: 0x314) A Data Register */
} Otpc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- OTPC_CR : (OTPC Offset: 0x00) Control Register -------- */
#define OTPC_CR_PGM (0x1u << 0) /**< \brief (OTPC_CR) Program Packet */
#define OTPC_CR_CKSGEN (0x1u << 1) /**< \brief (OTPC_CR) Generate Checksum */
#define OTPC_CR_INVLD (0x1u << 2) /**< \brief (OTPC_CR) Invalidate Packet */
#define OTPC_CR_HIDE (0x1u << 4) /**< \brief (OTPC_CR) Hide Packet */
#define OTPC_CR_READ (0x1u << 6) /**< \brief (OTPC_CR) Read Area */
#define OTPC_CR_FLUSH (0x1u << 7) /**< \brief (OTPC_CR) Flush Temporary Registers */
#define OTPC_CR_KBSTART (0x1u << 8) /**< \brief (OTPC_CR) Key Bus Transfer Start */
#define OTPC_CR_KBSTOP (0x1u << 9) /**< \brief (OTPC_CR) Key Bus Transfer Stop */
#define OTPC_CR_REFRESH (0x1u << 15) /**< \brief (OTPC_CR) Refresh the Area */
#define OTPC_CR_KEY_Pos 16
#define OTPC_CR_KEY_Msk (0xffffu << OTPC_CR_KEY_Pos) /**< \brief (OTPC_CR) Programming Key */
#define OTPC_CR_KEY(value) ((OTPC_CR_KEY_Msk & ((value) << OTPC_CR_KEY_Pos)))
/* -------- OTPC_MR : (OTPC Offset: 0x04) Mode Register -------- */
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
/* -------- OTPC_AR : (OTPC Offset: 0x08) Address Register -------- */
#define OTPC_AR_DADDR_Pos 0
#define OTPC_AR_DADDR_Msk (0xffu << OTPC_AR_DADDR_Pos) /**< \brief (OTPC_AR) Data Address */
#define OTPC_AR_DADDR(value) ((OTPC_AR_DADDR_Msk & ((value) << OTPC_AR_DADDR_Pos)))
#define OTPC_AR_INCRT (0x1u << 16) /**< \brief (OTPC_AR) Increment Type */
#define   OTPC_AR_INCRT_AFTER_READ (0x0u << 16) /**< \brief (OTPC_AR) Increment DADDR after a read of OTPC_DR. */
#define   OTPC_AR_INCRT_AFTER_WRITE (0x1u << 16) /**< \brief (OTPC_AR) Increment DADDR after a write of OTPC_DR. */
/* -------- OTPC_SR : (OTPC Offset: 0x0C) Status Register -------- */
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
#define OTPC_SR_AHIDE (0x1u << 12) /**< \brief (OTPC_SR) Hiding On-Going */
#define OTPC_SR_RPGM (0x1u << 16) /**< \brief (OTPC_SR) ROM Programming On-Going */
#define OTPC_SR_PPGM (0x1u << 20) /**< \brief (OTPC_SR) Patch Programming On-Going */
#define OTPC_SR_PEMUL (0x1u << 21) /**< \brief (OTPC_SR) Patch Emulation Enabled */
#define OTPC_SR_PREAD (0x1u << 22) /**< \brief (OTPC_SR) Patch Read On-Going */
#define OTPC_SR_PREFRESH (0x1u << 23) /**< \brief (OTPC_SR) Patch Refresh On-Going */
#define OTPC_SR_APGM (0x1u << 24) /**< \brief (OTPC_SR) Engineering Programming On-Going */
#define OTPC_SR_ALOCK (0x1u << 25) /**< \brief (OTPC_SR) Engineering Lock On-Going */
#define OTPC_SR_AINVLD (0x1u << 26) /**< \brief (OTPC_SR) Engineering Invalidation On-Going */
#define OTPC_SR_AEMUL (0x1u << 27) /**< \brief (OTPC_SR) Engineering Emulation Enabled */
#define OTPC_SR_AMKBB (0x1u << 28) /**< \brief (OTPC_SR) Engineering Master Key Bus Busy */
#define OTPC_SR_ASKBB (0x1u << 29) /**< \brief (OTPC_SR) Engineering Slave Key Bus Busy */
#define OTPC_SR_AREAD (0x1u << 30) /**< \brief (OTPC_SR) Engineering Read On-Going */
#define OTPC_SR_AFLUSH (0x1u << 31) /**< \brief (OTPC_SR) Engineering Flush On-Going */
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
/* -------- OTPC_UID0R : (OTPC Offset: 0x60) Product UID Register -------- */
#define OTPC_UID0R_UID_Pos 0
#define OTPC_UID0R_UID_Msk (0xffffffffu << OTPC_UID0R_UID_Pos) /**< \brief (OTPC_UID0R) Unique Product ID */
/* -------- OTPC_UID1R : (OTPC Offset: 0x64) Product UID Register -------- */
#define OTPC_UID1R_UID_Pos 0
#define OTPC_UID1R_UID_Msk (0xffffffffu << OTPC_UID1R_UID_Pos) /**< \brief (OTPC_UID1R) Unique Product ID */
/* -------- OTPC_UID2R : (OTPC Offset: 0x68) Product UID Register -------- */
#define OTPC_UID2R_UID_Pos 0
#define OTPC_UID2R_UID_Msk (0xffffffffu << OTPC_UID2R_UID_Pos) /**< \brief (OTPC_UID2R) Unique Product ID */
/* -------- OTPC_UID3R : (OTPC Offset: 0x6C) Product UID Register -------- */
#define OTPC_UID3R_UID_Pos 0
#define OTPC_UID3R_UID_Msk (0xffffffffu << OTPC_UID3R_UID_Pos) /**< \brief (OTPC_UID3R) Unique Product ID */
/* -------- OTPC_HCSR : (OTPC Offset: 0x70) Hardware Configuration Selection Register -------- */
#define OTPC_HCSR_HCSEL_Pos 0
#define OTPC_HCSR_HCSEL_Msk (0xfu << OTPC_HCSR_HCSEL_Pos) /**< \brief (OTPC_HCSR) Hardware Configuration Selection */
#define OTPC_HCSR_HCSEL(value) ((OTPC_HCSR_HCSEL_Msk & ((value) << OTPC_HCSR_HCSEL_Pos)))
/* -------- OTPC_HCDR : (OTPC Offset: 0x74) Hardware Configuration Data Register -------- */
#define OTPC_HCDR_HCFG_Pos 0
#define OTPC_HCDR_HCFG_Msk (0xffffffffu << OTPC_HCDR_HCFG_Pos) /**< \brief (OTPC_HCDR) Hardware Configuration Value */
/* -------- OTPC_HS0R : (OTPC Offset: 0x80) Hardware Security Register -------- */
#define OTPC_HS0R_SCFG_Pos 0
#define OTPC_HS0R_SCFG_Msk (0xffffffffu << OTPC_HS0R_SCFG_Pos) /**< \brief (OTPC_HS0R) Security Configuration Value */
/* -------- OTPC_HS1R : (OTPC Offset: 0x84) Hardware Security Register -------- */
#define OTPC_HS1R_SCFG_Pos 0
#define OTPC_HS1R_SCFG_Msk (0xffffffffu << OTPC_HS1R_SCFG_Pos) /**< \brief (OTPC_HS1R) Security Configuration Value */
/* -------- OTPC_OMR : (OTPC Offset: 0x90) OTP Mode Register -------- */
#define OTPC_OMR_CHGRQ (0x1u << 0) /**< \brief (OTPC_OMR) Change Request */
#define OTPC_OMR_KEY_Pos 16
#define OTPC_OMR_KEY_Msk (0xffffu << OTPC_OMR_KEY_Pos) /**< \brief (OTPC_OMR) Key */
#define OTPC_OMR_KEY(value) ((OTPC_OMR_KEY_Msk & ((value) << OTPC_OMR_KEY_Pos)))
/* -------- OTPC_ODC0R : (OTPC Offset: 0xA0) OTP DAP Configuration Register -------- */
#define OTPC_ODC0R_DAPCFG_Pos 0
#define OTPC_ODC0R_DAPCFG_Msk (0xffffffffu << OTPC_ODC0R_DAPCFG_Pos) /**< \brief (OTPC_ODC0R) DAP Configuration */
#define OTPC_ODC0R_DAPCFG(value) ((OTPC_ODC0R_DAPCFG_Msk & ((value) << OTPC_ODC0R_DAPCFG_Pos)))
/* -------- OTPC_ODC1R : (OTPC Offset: 0xA4) OTP DAP Configuration Register -------- */
#define OTPC_ODC1R_DAPCFG_Pos 0
#define OTPC_ODC1R_DAPCFG_Msk (0xffffffffu << OTPC_ODC1R_DAPCFG_Pos) /**< \brief (OTPC_ODC1R) DAP Configuration */
#define OTPC_ODC1R_DAPCFG(value) ((OTPC_ODC1R_DAPCFG_Msk & ((value) << OTPC_ODC1R_DAPCFG_Pos)))
/* -------- OTPC_ODC2R : (OTPC Offset: 0xA8) OTP DAP Configuration Register -------- */
#define OTPC_ODC2R_DAPCFG_Pos 0
#define OTPC_ODC2R_DAPCFG_Msk (0xffffffffu << OTPC_ODC2R_DAPCFG_Pos) /**< \brief (OTPC_ODC2R) DAP Configuration */
#define OTPC_ODC2R_DAPCFG(value) ((OTPC_ODC2R_DAPCFG_Msk & ((value) << OTPC_ODC2R_DAPCFG_Pos)))
/* -------- OTPC_ODC3R : (OTPC Offset: 0xAC) OTP DAP Configuration Register -------- */
#define OTPC_ODC3R_DAPCFG_Pos 0
#define OTPC_ODC3R_DAPCFG_Msk (0xffffffffu << OTPC_ODC3R_DAPCFG_Pos) /**< \brief (OTPC_ODC3R) DAP Configuration */
#define OTPC_ODC3R_DAPCFG(value) ((OTPC_ODC3R_DAPCFG_Msk & ((value) << OTPC_ODC3R_DAPCFG_Pos)))
/* -------- OTPC_OPC0R : (OTPC Offset: 0xB0) OTP PMC Configuration Register -------- */
#define OTPC_OPC0R_PMCCFG_Pos 0
#define OTPC_OPC0R_PMCCFG_Msk (0xffffffffu << OTPC_OPC0R_PMCCFG_Pos) /**< \brief (OTPC_OPC0R) PMC Configuration */
#define OTPC_OPC0R_PMCCFG(value) ((OTPC_OPC0R_PMCCFG_Msk & ((value) << OTPC_OPC0R_PMCCFG_Pos)))
/* -------- OTPC_OPC1R : (OTPC Offset: 0xB4) OTP PMC Configuration Register -------- */
#define OTPC_OPC1R_PMCCFG_Pos 0
#define OTPC_OPC1R_PMCCFG_Msk (0xffffffffu << OTPC_OPC1R_PMCCFG_Pos) /**< \brief (OTPC_OPC1R) PMC Configuration */
#define OTPC_OPC1R_PMCCFG(value) ((OTPC_OPC1R_PMCCFG_Msk & ((value) << OTPC_OPC1R_PMCCFG_Pos)))
/* -------- OTPC_OPC2R : (OTPC Offset: 0xB8) OTP PMC Configuration Register -------- */
#define OTPC_OPC2R_PMCCFG_Pos 0
#define OTPC_OPC2R_PMCCFG_Msk (0xffffffffu << OTPC_OPC2R_PMCCFG_Pos) /**< \brief (OTPC_OPC2R) PMC Configuration */
#define OTPC_OPC2R_PMCCFG(value) ((OTPC_OPC2R_PMCCFG_Msk & ((value) << OTPC_OPC2R_PMCCFG_Pos)))
/* -------- OTPC_OPC3R : (OTPC Offset: 0xBC) OTP PMC Configuration Register -------- */
#define OTPC_OPC3R_PMCCFG_Pos 0
#define OTPC_OPC3R_PMCCFG_Msk (0xffffffffu << OTPC_OPC3R_PMCCFG_Pos) /**< \brief (OTPC_OPC3R) PMC Configuration */
#define OTPC_OPC3R_PMCCFG(value) ((OTPC_OPC3R_PMCCFG_Msk & ((value) << OTPC_OPC3R_PMCCFG_Pos)))
/* -------- OTPC_WPMR : (OTPC Offset: 0xE4) Write Protection Mode Register -------- */
#define OTPC_WPMR_WPCFEN (0x1u << 0) /**< \brief (OTPC_WPMR) Write Protection Configuration Enable */
#define OTPC_WPMR_WPITEN (0x1u << 1) /**< \brief (OTPC_WPMR) Write Protection Interrupt Enable */
#define OTPC_WPMR_WPCTEN (0x1u << 2) /**< \brief (OTPC_WPMR) Write Protection Control Enable */
#define OTPC_WPMR_FIRSTE (0x1u << 4) /**< \brief (OTPC_WPMR) First Error Report Enable */
#define OTPC_WPMR_WPKEY_Pos 8
#define OTPC_WPMR_WPKEY_Msk (0xffffffu << OTPC_WPMR_WPKEY_Pos) /**< \brief (OTPC_WPMR) Write Protection Key */
#define OTPC_WPMR_WPKEY(value) ((OTPC_WPMR_WPKEY_Msk & ((value) << OTPC_WPMR_WPKEY_Pos)))
#define   OTPC_WPMR_WPKEY_PASSWD (0x4F5450u << 8) /**< \brief (OTPC_WPMR) Writing any other value in this field aborts the write operation.Always reads as 0. */
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
#define   OTPC_WPSR_SWETYP_KEY_ERROR (0x3u << 24) /**< \brief (OTPC_WPSR) A write has been computed in OTPC_CR, OTPC_ACR, OTPC_RCR, OTPC_PCR, OTPC_OMR or OTPC_WPMR register with a wrong value in the related KEY field (error). */
#define OTPC_WPSR_ECLASS (0x1u << 31) /**< \brief (OTPC_WPSR) Software Error Class */
#define   OTPC_WPSR_ECLASS_WARNING (0x0u << 31) /**< \brief (OTPC_WPSR) An abnormal access that does not have any impact. */
#define   OTPC_WPSR_ECLASS_ERROR (0x1u << 31) /**< \brief (OTPC_WPSR) An abnormal access that may have an impact. */
/* -------- OTPC_VERSION : (OTPC Offset: 0xFC) Version Register -------- */
#define OTPC_VERSION_VERSION_Pos 0
#define OTPC_VERSION_VERSION_Msk (0xfffu << OTPC_VERSION_VERSION_Pos) /**< \brief (OTPC_VERSION) Hardware Module Version */
#define OTPC_VERSION_MFN_Pos 16
#define OTPC_VERSION_MFN_Msk (0x7u << OTPC_VERSION_MFN_Pos) /**< \brief (OTPC_VERSION) Metal Fix Number */
/* -------- OTPC_RCR : (OTPC Offset: 0x100) ROM Control Register -------- */
#define OTPC_RCR_PGM (0x1u << 0) /**< \brief (OTPC_RCR) Program */
#define OTPC_RCR_KEY_Pos 16
#define OTPC_RCR_KEY_Msk (0xffffu << OTPC_RCR_KEY_Pos) /**< \brief (OTPC_RCR) Programming Key */
#define OTPC_RCR_KEY(value) ((OTPC_RCR_KEY_Msk & ((value) << OTPC_RCR_KEY_Pos)))
/* -------- OTPC_RMR : (OTPC Offset: 0x104) ROM Mode Register -------- */
#define OTPC_RMR_FWEN (0x1u << 0) /**< \brief (OTPC_RMR) Firewall Enable */
#define OTPC_RMR_RDDIS (0x1u << 8) /**< \brief (OTPC_RMR) Read Disable */
#define OTPC_RMR_WRDIS (0x1u << 9) /**< \brief (OTPC_RMR) Write Disable */
#define OTPC_RMR_LOCK (0x1u << 15) /**< \brief (OTPC_RMR) Lock Register */
#define OTPC_RMR_PGMODE_Pos 16
#define OTPC_RMR_PGMODE_Msk (0x3u << OTPC_RMR_PGMODE_Pos) /**< \brief (OTPC_RMR) Programming Mode */
#define OTPC_RMR_PGMODE(value) ((OTPC_RMR_PGMODE_Msk & ((value) << OTPC_RMR_PGMODE_Pos)))
#define   OTPC_RMR_PGMODE_ROM_NO_PGM (0x0u << 16) /**< \brief (OTPC_RMR) ROM Code programming is disabled */
#define   OTPC_RMR_PGMODE_ROM_SBUS_PGM (0x1u << 16) /**< \brief (OTPC_RMR) ROM Code programming through System Bus Slave Interface */
#define   OTPC_RMR_PGMODE_ROM_UI_ADDR_CONST_PGM (0x2u << 16) /**< \brief (OTPC_RMR) ROM Code programming through User Interface */
#define   OTPC_RMR_PGMODE_ROM_UI_ADDR_INCR_PGM (0x3u << 16) /**< \brief (OTPC_RMR) ROM Code programming through User Interface with OTPC_RAR incremented after each programming. */
/* -------- OTPC_RAR : (OTPC Offset: 0x110) ROM Address Register -------- */
#define OTPC_RAR_RADDR_Pos 2
#define OTPC_RAR_RADDR_Msk (0x3fffffffu << OTPC_RAR_RADDR_Pos) /**< \brief (OTPC_RAR) ROM Address */
#define OTPC_RAR_RADDR(value) ((OTPC_RAR_RADDR_Msk & ((value) << OTPC_RAR_RADDR_Pos)))
/* -------- OTPC_RDR : (OTPC Offset: 0x114) ROM Data Register -------- */
#define OTPC_RDR_RDATA_Pos 0
#define OTPC_RDR_RDATA_Msk (0xffffffffu << OTPC_RDR_RDATA_Pos) /**< \brief (OTPC_RDR) ROM Data */
#define OTPC_RDR_RDATA(value) ((OTPC_RDR_RDATA_Msk & ((value) << OTPC_RDR_RDATA_Pos)))
/* -------- OTPC_PCR : (OTPC Offset: 0x200) Patch Control Register -------- */
#define OTPC_PCR_PGM (0x1u << 0) /**< \brief (OTPC_PCR) Program */
#define OTPC_PCR_READ (0x1u << 6) /**< \brief (OTPC_PCR) Read Patch */
#define OTPC_PCR_REFRESH (0x1u << 7) /**< \brief (OTPC_PCR) Refresh Patches */
#define OTPC_PCR_KEY_Pos 16
#define OTPC_PCR_KEY_Msk (0xffffu << OTPC_PCR_KEY_Pos) /**< \brief (OTPC_PCR) Programming Key */
#define OTPC_PCR_KEY(value) ((OTPC_PCR_KEY_Msk & ((value) << OTPC_PCR_KEY_Pos)))
/* -------- OTPC_PMR : (OTPC Offset: 0x204) Patch Mode Register -------- */
#define OTPC_PMR_EMUL (0x1u << 7) /**< \brief (OTPC_PMR) Emulation Mode */
#define OTPC_PMR_RDDIS (0x1u << 8) /**< \brief (OTPC_PMR) Read Disable */
#define OTPC_PMR_WRDIS (0x1u << 9) /**< \brief (OTPC_PMR) Write Disable */
#define OTPC_PMR_LOCK (0x1u << 15) /**< \brief (OTPC_PMR) Lock Register */
#define OTPC_PMR_PID_Pos 16
#define OTPC_PMR_PID_Msk (0xfu << OTPC_PMR_PID_Pos) /**< \brief (OTPC_PMR) Patch ID */
#define OTPC_PMR_PID(value) ((OTPC_PMR_PID_Msk & ((value) << OTPC_PMR_PID_Pos)))
/* -------- OTPC_PSR : (OTPC Offset: 0x208) Patch Software Register -------- */
#define OTPC_PSR_SOFT_Pos 0
#define OTPC_PSR_SOFT_Msk (0xffffffffu << OTPC_PSR_SOFT_Pos) /**< \brief (OTPC_PSR) Software Value */
#define OTPC_PSR_SOFT(value) ((OTPC_PSR_SOFT_Msk & ((value) << OTPC_PSR_SOFT_Pos)))
/* -------- OTPC_PAR : (OTPC Offset: 0x210) Patch Address Register -------- */
#define OTPC_PAR_VALID0_Pos 0
#define OTPC_PAR_VALID0_Msk (0x3u << OTPC_PAR_VALID0_Pos) /**< \brief (OTPC_PAR) Patch Validity */
#define OTPC_PAR_VALID0(value) ((OTPC_PAR_VALID0_Msk & ((value) << OTPC_PAR_VALID0_Pos)))
#define OTPC_PAR_PADDR_Pos 2
#define OTPC_PAR_PADDR_Msk (0x3ffffffu << OTPC_PAR_PADDR_Pos) /**< \brief (OTPC_PAR) Patch Address */
#define OTPC_PAR_PADDR(value) ((OTPC_PAR_PADDR_Msk & ((value) << OTPC_PAR_PADDR_Pos)))
#define OTPC_PAR_VALID1_Pos 28
#define OTPC_PAR_VALID1_Msk (0xfu << OTPC_PAR_VALID1_Pos) /**< \brief (OTPC_PAR) Patch Validity */
#define OTPC_PAR_VALID1(value) ((OTPC_PAR_VALID1_Msk & ((value) << OTPC_PAR_VALID1_Pos)))
/* -------- OTPC_PDR : (OTPC Offset: 0x214) Patch Data Register -------- */
#define OTPC_PDR_PDATA_Pos 0
#define OTPC_PDR_PDATA_Msk (0xffffffffu << OTPC_PDR_PDATA_Pos) /**< \brief (OTPC_PDR) Patch Data */
#define OTPC_PDR_PDATA(value) ((OTPC_PDR_PDATA_Msk & ((value) << OTPC_PDR_PDATA_Pos)))
/* -------- OTPC_ACR : (OTPC Offset: 0x300) A Control Register -------- */
#define OTPC_ACR_PGM (0x1u << 0) /**< \brief (OTPC_ACR) Program Packet */
#define OTPC_ACR_CKSGEN (0x1u << 1) /**< \brief (OTPC_ACR) Generate Checksum */
#define OTPC_ACR_INVLD (0x1u << 2) /**< \brief (OTPC_ACR) Invalidate Packet */
#define OTPC_ACR_HIDE (0x1u << 4) /**< \brief (OTPC_ACR) Hide Packet */
#define OTPC_ACR_READ (0x1u << 6) /**< \brief (OTPC_ACR) Read Area */
#define OTPC_ACR_FLUSH (0x1u << 7) /**< \brief (OTPC_ACR) Flush Temporary Registers */
#define OTPC_ACR_KBSTART (0x1u << 8) /**< \brief (OTPC_ACR) Key Bus Transfer Start */
#define OTPC_ACR_KBSTOP (0x1u << 9) /**< \brief (OTPC_ACR) Key Bus Transfer Stop */
#define OTPC_ACR_REFRESH (0x1u << 15) /**< \brief (OTPC_ACR) Refresh the Area */
#define OTPC_ACR_KEY_Pos 16
#define OTPC_ACR_KEY_Msk (0xffffu << OTPC_ACR_KEY_Pos) /**< \brief (OTPC_ACR) Programming Key */
#define OTPC_ACR_KEY(value) ((OTPC_ACR_KEY_Msk & ((value) << OTPC_ACR_KEY_Pos)))
/* -------- OTPC_AMR : (OTPC Offset: 0x304) A Mode Register -------- */
#define OTPC_AMR_UIDRDDIS (0x1u << 0) /**< \brief (OTPC_AMR) UID Register Read Disable */
#define OTPC_AMR_HCGRDDIS (0x1u << 1) /**< \brief (OTPC_AMR) Hardware Configuration Register Read Disable */
#define OTPC_AMR_SCGRDDIS (0x1u << 2) /**< \brief (OTPC_AMR) Security Configuration Register Read Disable */
#define OTPC_AMR_NPCKT (0x1u << 4) /**< \brief (OTPC_AMR) New Packet */
#define OTPC_AMR_EMUL (0x1u << 7) /**< \brief (OTPC_AMR) Emulation Mode */
#define OTPC_AMR_RDDIS (0x1u << 8) /**< \brief (OTPC_AMR) Read Disable */
#define OTPC_AMR_WRDIS (0x1u << 9) /**< \brief (OTPC_AMR) Write Disable */
#define OTPC_AMR_KBDST (0x1u << 12) /**< \brief (OTPC_AMR) Key Bus Destination */
#define   OTPC_AMR_KBDST_TDES (0x0u << 12) /**< \brief (OTPC_AMR) The TDES is the destination of the key transfer. */
#define   OTPC_AMR_KBDST_AES (0x1u << 12) /**< \brief (OTPC_AMR) The AES is the destination of the key transfer. */
#define OTPC_AMR_LOCK (0x1u << 15) /**< \brief (OTPC_AMR) Lock Register */
#define OTPC_AMR_AADDR_Pos 16
#define OTPC_AMR_AADDR_Msk (0xffffu << OTPC_AMR_AADDR_Pos) /**< \brief (OTPC_AMR) Address */
#define OTPC_AMR_AADDR(value) ((OTPC_AMR_AADDR_Msk & ((value) << OTPC_AMR_AADDR_Pos)))
/* -------- OTPC_AAR : (OTPC Offset: 0x308) A Address Register -------- */
#define OTPC_AAR_DADDR_Pos 0
#define OTPC_AAR_DADDR_Msk (0xffu << OTPC_AAR_DADDR_Pos) /**< \brief (OTPC_AAR) Data Address */
#define OTPC_AAR_DADDR(value) ((OTPC_AAR_DADDR_Msk & ((value) << OTPC_AAR_DADDR_Pos)))
#define OTPC_AAR_INCRT (0x1u << 16) /**< \brief (OTPC_AAR) Increment Type */
#define   OTPC_AAR_INCRT_AFTER_READ (0x0u << 16) /**< \brief (OTPC_AAR) Increment DADDR after a read of OTPC_ADR. */
#define   OTPC_AAR_INCRT_AFTER_WRITE (0x1u << 16) /**< \brief (OTPC_AAR) Increment DADDR after a write of OTPC_ADR. */
/* -------- OTPC_AHR : (OTPC Offset: 0x310) A Header Register -------- */
#define OTPC_AHR_PACKET_Pos 0
#define OTPC_AHR_PACKET_Msk (0x7u << OTPC_AHR_PACKET_Pos) /**< \brief (OTPC_AHR) Packet Type */
#define OTPC_AHR_PACKET(value) ((OTPC_AHR_PACKET_Msk & ((value) << OTPC_AHR_PACKET_Pos)))
#define   OTPC_AHR_PACKET_REGULAR (0x1u << 0) /**< \brief (OTPC_AHR) Regular packet accessible through the User Interface. */
#define   OTPC_AHR_PACKET_KEY (0x2u << 0) /**< \brief (OTPC_AHR) Key packet accessible only through the Key buses. */
#define   OTPC_AHR_PACKET_PRODUCT_UID (0x4u << 0) /**< \brief (OTPC_AHR) Product UID packet. */
#define   OTPC_AHR_PACKET_HARDWARE_CONFIGURATION (0x5u << 0) /**< \brief (OTPC_AHR) Hardware Configuration packet. */
#define   OTPC_AHR_PACKET_SECURITY_CONFIGURATION (0x6u << 0) /**< \brief (OTPC_AHR) Security Configuration packet. */
#define OTPC_AHR_LOCK (0x1u << 3) /**< \brief (OTPC_AHR) Lock Status */
#define OTPC_AHR_INVLD_Pos 4
#define OTPC_AHR_INVLD_Msk (0x3u << OTPC_AHR_INVLD_Pos) /**< \brief (OTPC_AHR) Invalid Status */
#define OTPC_AHR_INVLD(value) ((OTPC_AHR_INVLD_Msk & ((value) << OTPC_AHR_INVLD_Pos)))
#define OTPC_AHR_ONE (0x1u << 7) /**< \brief (OTPC_AHR) One */
#define OTPC_AHR_SIZE_Pos 8
#define OTPC_AHR_SIZE_Msk (0xffu << OTPC_AHR_SIZE_Pos) /**< \brief (OTPC_AHR) Packet Size */
#define OTPC_AHR_SIZE(value) ((OTPC_AHR_SIZE_Msk & ((value) << OTPC_AHR_SIZE_Pos)))
#define OTPC_AHR_CHECKSUM_Pos 16
#define OTPC_AHR_CHECKSUM_Msk (0xffffu << OTPC_AHR_CHECKSUM_Pos) /**< \brief (OTPC_AHR) Packet Checksum */
#define OTPC_AHR_CHECKSUM(value) ((OTPC_AHR_CHECKSUM_Msk & ((value) << OTPC_AHR_CHECKSUM_Pos)))
/* -------- OTPC_ADR : (OTPC Offset: 0x314) A Data Register -------- */
#define OTPC_ADR_ADATA_Pos 0
#define OTPC_ADR_ADATA_Msk (0xffffffffu << OTPC_ADR_ADATA_Pos) /**< \brief (OTPC_ADR) Engineering Packet Data */
#define OTPC_ADR_ADATA(value) ((OTPC_ADR_ADATA_Msk & ((value) << OTPC_ADR_ADATA_Pos)))

/*@}*/


#endif /* _SAM9X_OTPC_COMPONENT_ */
