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

#ifndef _SAM9X_DBGU_COMPONENT_
#define _SAM9X_DBGU_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Debug Unit */
/* ============================================================================= */
/** \addtogroup SAM9X_DBGU Debug Unit */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Dbgu hardware registers */
typedef struct {
  __O  uint32_t DBGU_CR;       /**< \brief (Dbgu Offset: 0x0) Control Register */
  __IO uint32_t DBGU_MR;       /**< \brief (Dbgu Offset: 0x4) Mode Register */
  __O  uint32_t DBGU_IER;      /**< \brief (Dbgu Offset: 0x8) Interrupt Enable Register */
  __O  uint32_t DBGU_IDR;      /**< \brief (Dbgu Offset: 0xC) Interrupt Disable Register */
  __I  uint32_t DBGU_IMR;      /**< \brief (Dbgu Offset: 0x10) Interrupt Mask Register */
  __I  uint32_t DBGU_SR;       /**< \brief (Dbgu Offset: 0x14) Status Register */
  __I  uint32_t DBGU_RHR;      /**< \brief (Dbgu Offset: 0x18) Receive Holding Register */
  __O  uint32_t DBGU_THR;      /**< \brief (Dbgu Offset: 0x1C) Transmit Holding Register */
  __IO uint32_t DBGU_BRGR;     /**< \brief (Dbgu Offset: 0x20) Baud Rate Generator Register */
  __I  uint32_t Reserved1[1];
  __IO uint32_t DBGU_RTOR;     /**< \brief (Dbgu Offset: 0x28) Receiver Timeout Register */
  __I  uint32_t Reserved2[5];
  __I  uint32_t DBGU_CIDR;     /**< \brief (Dbgu Offset: 0x40) Chip ID Register */
  __I  uint32_t DBGU_EXID;     /**< \brief (Dbgu Offset: 0x44) Chip ID Extension Register */
  __IO uint32_t DBGU_FNR;      /**< \brief (Dbgu Offset: 0x48) Force NTRST Register */
  __I  uint32_t Reserved3[38];
  __IO uint32_t DBGU_WPMR;     /**< \brief (Dbgu Offset: 0xE4) Write Protection Mode Register */
} Dbgu;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- DBGU_CR : (DBGU Offset: 0x0) Control Register -------- */
#define DBGU_CR_RSTRX (0x1u << 2) /**< \brief (DBGU_CR) Reset Receiver */
#define DBGU_CR_RSTTX (0x1u << 3) /**< \brief (DBGU_CR) Reset Transmitter */
#define DBGU_CR_RXEN (0x1u << 4) /**< \brief (DBGU_CR) Receiver Enable */
#define DBGU_CR_RXDIS (0x1u << 5) /**< \brief (DBGU_CR) Receiver Disable */
#define DBGU_CR_TXEN (0x1u << 6) /**< \brief (DBGU_CR) Transmitter Enable */
#define DBGU_CR_TXDIS (0x1u << 7) /**< \brief (DBGU_CR) Transmitter Disable */
#define DBGU_CR_RSTSTA (0x1u << 8) /**< \brief (DBGU_CR) Reset Status */
#define DBGU_CR_RETTO (0x1u << 10) /**< \brief (DBGU_CR) Rearm Timeout */
#define DBGU_CR_STTTO (0x1u << 11) /**< \brief (DBGU_CR) Start Timeout */
/* -------- DBGU_MR : (DBGU Offset: 0x4) Mode Register -------- */
#define DBGU_MR_FILTER (0x1u << 4) /**< \brief (DBGU_MR) Receiver Digital Filter */
#define   DBGU_MR_FILTER_DISABLED (0x0u << 4) /**< \brief (DBGU_MR) DBGU does not filter the receive line. */
#define   DBGU_MR_FILTER_ENABLED (0x1u << 4) /**< \brief (DBGU_MR) DBGU filters the receive line using a three-sample filter (16x-bit clock) (2 over 3 majority). */
#define DBGU_MR_PAR_Pos 9
#define DBGU_MR_PAR_Msk (0x7u << DBGU_MR_PAR_Pos) /**< \brief (DBGU_MR) Parity Type */
#define DBGU_MR_PAR(value) ((DBGU_MR_PAR_Msk & ((value) << DBGU_MR_PAR_Pos)))
#define   DBGU_MR_PAR_EVEN (0x0u << 9) /**< \brief (DBGU_MR) Even Parity */
#define   DBGU_MR_PAR_ODD (0x1u << 9) /**< \brief (DBGU_MR) Odd Parity */
#define   DBGU_MR_PAR_SPACE (0x2u << 9) /**< \brief (DBGU_MR) Space: parity forced to 0 */
#define   DBGU_MR_PAR_MARK (0x3u << 9) /**< \brief (DBGU_MR) Mark: parity forced to 1 */
#define   DBGU_MR_PAR_NONE (0x4u << 9) /**< \brief (DBGU_MR) No parity */
#define DBGU_MR_BRSRCCK (0x1u << 12) /**< \brief (DBGU_MR) Baud Rate Source Clock */
#define   DBGU_MR_BRSRCCK_PERIPH_CLK (0x0u << 12) /**< \brief (DBGU_MR) The baud rate is driven by the peripheral clock */
#define   DBGU_MR_BRSRCCK_GCLK (0x1u << 12) /**< \brief (DBGU_MR) The baud rate is driven by a PMC-programmable clock GCLK (see section Power Management Controller (PMC)). */
#define DBGU_MR_CHMODE_Pos 14
#define DBGU_MR_CHMODE_Msk (0x3u << DBGU_MR_CHMODE_Pos) /**< \brief (DBGU_MR) Channel Mode */
#define DBGU_MR_CHMODE(value) ((DBGU_MR_CHMODE_Msk & ((value) << DBGU_MR_CHMODE_Pos)))
#define   DBGU_MR_CHMODE_NORM (0x0u << 14) /**< \brief (DBGU_MR) Normal mode */
#define   DBGU_MR_CHMODE_AUTO (0x1u << 14) /**< \brief (DBGU_MR) Automatic echo */
#define   DBGU_MR_CHMODE_LOCLOOP (0x2u << 14) /**< \brief (DBGU_MR) Local loopback */
#define   DBGU_MR_CHMODE_REMLOOP (0x3u << 14) /**< \brief (DBGU_MR) Remote loopback */
/* -------- DBGU_IER : (DBGU Offset: 0x8) Interrupt Enable Register -------- */
#define DBGU_IER_RXRDY (0x1u << 0) /**< \brief (DBGU_IER) Enable RXRDY Interrupt */
#define DBGU_IER_TXRDY (0x1u << 1) /**< \brief (DBGU_IER) Enable TXRDY Interrupt */
#define DBGU_IER_OVRE (0x1u << 5) /**< \brief (DBGU_IER) Enable Overrun Error Interrupt */
#define DBGU_IER_FRAME (0x1u << 6) /**< \brief (DBGU_IER) Enable Framing Error Interrupt */
#define DBGU_IER_PARE (0x1u << 7) /**< \brief (DBGU_IER) Enable Parity Error Interrupt */
#define DBGU_IER_TIMEOUT (0x1u << 8) /**< \brief (DBGU_IER) Enable Timeout Interrupt */
#define DBGU_IER_TXEMPTY (0x1u << 9) /**< \brief (DBGU_IER) Enable TXEMPTY Interrupt */
#define DBGU_IER_COMMTX (0x1u << 30) /**< \brief (DBGU_IER) Enable COMMTX (from ARM) Interrupt */
#define DBGU_IER_COMMRX (0x1u << 31) /**< \brief (DBGU_IER) Enable COMMRX (from ARM) Interrupt */
/* -------- DBGU_IDR : (DBGU Offset: 0xC) Interrupt Disable Register -------- */
#define DBGU_IDR_RXRDY (0x1u << 0) /**< \brief (DBGU_IDR) Disable RXRDY Interrupt */
#define DBGU_IDR_TXRDY (0x1u << 1) /**< \brief (DBGU_IDR) Disable TXRDY Interrupt */
#define DBGU_IDR_OVRE (0x1u << 5) /**< \brief (DBGU_IDR) Disable Overrun Error Interrupt */
#define DBGU_IDR_FRAME (0x1u << 6) /**< \brief (DBGU_IDR) Disable Framing Error Interrupt */
#define DBGU_IDR_PARE (0x1u << 7) /**< \brief (DBGU_IDR) Disable Parity Error Interrupt */
#define DBGU_IDR_TIMEOUT (0x1u << 8) /**< \brief (DBGU_IDR) Disable Timeout Interrupt */
#define DBGU_IDR_TXEMPTY (0x1u << 9) /**< \brief (DBGU_IDR) Disable TXEMPTY Interrupt */
#define DBGU_IDR_COMMTX (0x1u << 30) /**< \brief (DBGU_IDR) Disable COMMTX (from ARM) Interrupt */
#define DBGU_IDR_COMMRX (0x1u << 31) /**< \brief (DBGU_IDR) Disable COMMRX (from ARM) Interrupt */
/* -------- DBGU_IMR : (DBGU Offset: 0x10) Interrupt Mask Register -------- */
#define DBGU_IMR_RXRDY (0x1u << 0) /**< \brief (DBGU_IMR) Mask RXRDY Interrupt */
#define DBGU_IMR_TXRDY (0x1u << 1) /**< \brief (DBGU_IMR) Disable TXRDY Interrupt */
#define DBGU_IMR_OVRE (0x1u << 5) /**< \brief (DBGU_IMR) Mask Overrun Error Interrupt */
#define DBGU_IMR_FRAME (0x1u << 6) /**< \brief (DBGU_IMR) Mask Framing Error Interrupt */
#define DBGU_IMR_PARE (0x1u << 7) /**< \brief (DBGU_IMR) Mask Parity Error Interrupt */
#define DBGU_IMR_TIMEOUT (0x1u << 8) /**< \brief (DBGU_IMR) Mask Timeout Interrupt */
#define DBGU_IMR_TXEMPTY (0x1u << 9) /**< \brief (DBGU_IMR) Mask TXEMPTY Interrupt */
#define DBGU_IMR_COMMTX (0x1u << 30) /**< \brief (DBGU_IMR) Mask COMMTX (from ARM) Interrupt */
#define DBGU_IMR_COMMRX (0x1u << 31) /**< \brief (DBGU_IMR) Mask COMMRX (from ARM) Interrupt */
/* -------- DBGU_SR : (DBGU Offset: 0x14) Status Register -------- */
#define DBGU_SR_RXRDY (0x1u << 0) /**< \brief (DBGU_SR) Receiver Ready */
#define DBGU_SR_TXRDY (0x1u << 1) /**< \brief (DBGU_SR) Transmitter Ready */
#define DBGU_SR_OVRE (0x1u << 5) /**< \brief (DBGU_SR) Overrun Error */
#define DBGU_SR_FRAME (0x1u << 6) /**< \brief (DBGU_SR) Framing Error */
#define DBGU_SR_PARE (0x1u << 7) /**< \brief (DBGU_SR) Parity Error */
#define DBGU_SR_TIMEOUT (0x1u << 8) /**< \brief (DBGU_SR) Receiver Timeout */
#define DBGU_SR_TXEMPTY (0x1u << 9) /**< \brief (DBGU_SR) Transmitter Empty */
#define DBGU_SR_COMMTX (0x1u << 30) /**< \brief (DBGU_SR) Debug Communication Channel Write Status */
#define DBGU_SR_COMMRX (0x1u << 31) /**< \brief (DBGU_SR) Debug Communication Channel Read Status */
/* -------- DBGU_RHR : (DBGU Offset: 0x18) Receive Holding Register -------- */
#define DBGU_RHR_RXCHR_Pos 0
#define DBGU_RHR_RXCHR_Msk (0xffu << DBGU_RHR_RXCHR_Pos) /**< \brief (DBGU_RHR) Received Character */
/* -------- DBGU_THR : (DBGU Offset: 0x1C) Transmit Holding Register -------- */
#define DBGU_THR_TXCHR_Pos 0
#define DBGU_THR_TXCHR_Msk (0xffu << DBGU_THR_TXCHR_Pos) /**< \brief (DBGU_THR) Character to be Transmitted */
#define DBGU_THR_TXCHR(value) ((DBGU_THR_TXCHR_Msk & ((value) << DBGU_THR_TXCHR_Pos)))
/* -------- DBGU_BRGR : (DBGU Offset: 0x20) Baud Rate Generator Register -------- */
#define DBGU_BRGR_CD_Pos 0
#define DBGU_BRGR_CD_Msk (0xffffu << DBGU_BRGR_CD_Pos) /**< \brief (DBGU_BRGR) Clock Divisor */
#define DBGU_BRGR_CD(value) ((DBGU_BRGR_CD_Msk & ((value) << DBGU_BRGR_CD_Pos)))
/* -------- DBGU_RTOR : (DBGU Offset: 0x28) Receiver Timeout Register -------- */
#define DBGU_RTOR_TO_Pos 0
#define DBGU_RTOR_TO_Msk (0xffu << DBGU_RTOR_TO_Pos) /**< \brief (DBGU_RTOR) Timeout Value */
#define DBGU_RTOR_TO(value) ((DBGU_RTOR_TO_Msk & ((value) << DBGU_RTOR_TO_Pos)))
/* -------- DBGU_CIDR : (DBGU Offset: 0x40) Chip ID Register -------- */
#define DBGU_CIDR_CHID_Pos 0
#define DBGU_CIDR_CHID_Msk (0x7fffffffu << DBGU_CIDR_CHID_Pos) /**< \brief (DBGU_CIDR) Chip ID Value */
#define DBGU_CIDR_VERSION_Pos 0
#define DBGU_CIDR_VERSION_Msk (0x1fu << DBGU_CIDR_VERSION_Pos) /**< \brief (DBGU_CIDR) Version of the Device */
#define DBGU_CIDR_EXT (0x1u << 31) /**< \brief (DBGU_CIDR) Extension Flag */
/* -------- DBGU_EXID : (DBGU Offset: 0x44) Chip ID Extension Register -------- */
#define DBGU_EXID_EXID_Pos 0
#define DBGU_EXID_EXID_Msk (0xffffffffu << DBGU_EXID_EXID_Pos) /**< \brief (DBGU_EXID) Chip ID Extension */
/* -------- DBGU_FNR : (DBGU Offset: 0x48) Force NTRST Register -------- */
#define DBGU_FNR_FNTRST (0x1u << 0) /**< \brief (DBGU_FNR) Force NTRST */
/* -------- DBGU_WPMR : (DBGU Offset: 0xE4) Write Protection Mode Register -------- */
#define DBGU_WPMR_WPEN (0x1u << 0) /**< \brief (DBGU_WPMR) Write Protection Enable */
#define DBGU_WPMR_WPKEY_Pos 8
#define DBGU_WPMR_WPKEY_Msk (0xffffffu << DBGU_WPMR_WPKEY_Pos) /**< \brief (DBGU_WPMR) Write Protection Key */
#define DBGU_WPMR_WPKEY(value) ((DBGU_WPMR_WPKEY_Msk & ((value) << DBGU_WPMR_WPKEY_Pos)))
#define   DBGU_WPMR_WPKEY_PASSWD (0x554152u << 8) /**< \brief (DBGU_WPMR) Writing any other value in this field aborts the write operation. Always reads as 0. */

/*@}*/


#endif /* _SAM9X_DBGU_COMPONENT_ */
