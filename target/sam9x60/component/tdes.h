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

#ifndef _SAM9X_TDES_COMPONENT_
#define _SAM9X_TDES_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Triple Data Encryption Standard */
/* ============================================================================= */
/** \addtogroup SAM9X_TDES Triple Data Encryption Standard */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Tdes hardware registers */
typedef struct {
  __O  uint32_t TDES_CR;        /**< \brief (Tdes Offset: 0x0) Control Register */
  __IO uint32_t TDES_MR;        /**< \brief (Tdes Offset: 0x4) Mode Register */
  __I  uint32_t Reserved1[2];
  __O  uint32_t TDES_IER;       /**< \brief (Tdes Offset: 0x10) Interrupt Enable Register */
  __O  uint32_t TDES_IDR;       /**< \brief (Tdes Offset: 0x14) Interrupt Disable Register */
  __I  uint32_t TDES_IMR;       /**< \brief (Tdes Offset: 0x18) Interrupt Mask Register */
  __I  uint32_t TDES_ISR;       /**< \brief (Tdes Offset: 0x1C) Interrupt Status Register */
  __O  uint32_t TDES_KEY1WR[2]; /**< \brief (Tdes Offset: 0x20) Key 1 Word Register */
  __O  uint32_t TDES_KEY2WR[2]; /**< \brief (Tdes Offset: 0x28) Key 2 Word Register */
  __O  uint32_t TDES_KEY3WR[2]; /**< \brief (Tdes Offset: 0x30) Key 3 Word Register */
  __I  uint32_t Reserved2[2];
  __O  uint32_t TDES_IDATAR[2]; /**< \brief (Tdes Offset: 0x40) Input Data Register */
  __I  uint32_t Reserved3[2];
  __I  uint32_t TDES_ODATAR[2]; /**< \brief (Tdes Offset: 0x50) Output Data Register */
  __I  uint32_t Reserved4[2];
  __O  uint32_t TDES_IVR[2];    /**< \brief (Tdes Offset: 0x60) Initialization Vector Register */
  __I  uint32_t Reserved5[2];
  __IO uint32_t TDES_XTEA_RNDR; /**< \brief (Tdes Offset: 0x70) XTEA Rounds Register */
  __I  uint32_t Reserved6[28];
  __IO uint32_t TDES_WPMR;      /**< \brief (Tdes Offset: 0xE4) Write Protection Mode Register */
  __I  uint32_t TDES_WPSR;      /**< \brief (Tdes Offset: 0xE8) Write Protection Status Register */
} Tdes;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- TDES_CR : (TDES Offset: 0x0) Control Register -------- */
#define TDES_CR_START (0x1u << 0) /**< \brief (TDES_CR) Start Processing */
#define TDES_CR_SWRST (0x1u << 8) /**< \brief (TDES_CR) Software Reset */
#define TDES_CR_LOADSEED (0x1u << 16) /**< \brief (TDES_CR) Loadseed */
#define TDES_CR_UNLOCK (0x1u << 24) /**< \brief (TDES_CR) Unlock Processing */
/* -------- TDES_MR : (TDES Offset: 0x4) Mode Register -------- */
#define TDES_MR_CIPHER (0x1u << 0) /**< \brief (TDES_MR) Processing Mode */
#define   TDES_MR_CIPHER_DECRYPT (0x0u << 0) /**< \brief (TDES_MR) Decrypts data. */
#define   TDES_MR_CIPHER_ENCRYPT (0x1u << 0) /**< \brief (TDES_MR) Encrypts data. */
#define TDES_MR_TDESMOD_Pos 1
#define TDES_MR_TDESMOD_Msk (0x3u << TDES_MR_TDESMOD_Pos) /**< \brief (TDES_MR) ALGORITHM Mode */
#define TDES_MR_TDESMOD(value) ((TDES_MR_TDESMOD_Msk & ((value) << TDES_MR_TDESMOD_Pos)))
#define   TDES_MR_TDESMOD_SINGLE_DES (0x0u << 1) /**< \brief (TDES_MR) Single DES processing using TDES_KEY1WRy. */
#define   TDES_MR_TDESMOD_TRIPLE_DES (0x1u << 1) /**< \brief (TDES_MR) Triple DES processing using TDES_KEY1WRy, TDES_KEY2WRy and TDES_KEY3WRy. */
#define   TDES_MR_TDESMOD_XTEA (0x2u << 1) /**< \brief (TDES_MR) XTEA processing using TDES_KEY1WRy and TDES_KEY2WRy. */
#define TDES_MR_KEYMOD (0x1u << 4) /**< \brief (TDES_MR) Key Mode */
#define TDES_MR_PKWO (0x1u << 6) /**< \brief (TDES_MR) Private Key Write Once */
#define TDES_MR_PKRS (0x1u << 7) /**< \brief (TDES_MR) Private Key Internal Register Select */
#define TDES_MR_SMOD_Pos 8
#define TDES_MR_SMOD_Msk (0x3u << TDES_MR_SMOD_Pos) /**< \brief (TDES_MR) Start Mode */
#define TDES_MR_SMOD(value) ((TDES_MR_SMOD_Msk & ((value) << TDES_MR_SMOD_Pos)))
#define   TDES_MR_SMOD_MANUAL_START (0x0u << 8) /**< \brief (TDES_MR) Manual Mode */
#define   TDES_MR_SMOD_AUTO_START (0x1u << 8) /**< \brief (TDES_MR) Auto Mode */
#define   TDES_MR_SMOD_IDATAR0_START (0x2u << 8) /**< \brief (TDES_MR) TDES_IDATAR0 accesses only Auto mode */
#define TDES_MR_OPMOD_Pos 12
#define TDES_MR_OPMOD_Msk (0x3u << TDES_MR_OPMOD_Pos) /**< \brief (TDES_MR) Operating Mode */
#define TDES_MR_OPMOD(value) ((TDES_MR_OPMOD_Msk & ((value) << TDES_MR_OPMOD_Pos)))
#define   TDES_MR_OPMOD_ECB (0x0u << 12) /**< \brief (TDES_MR) Electronic Code Book mode */
#define   TDES_MR_OPMOD_CBC (0x1u << 12) /**< \brief (TDES_MR) Cipher Block Chaining mode */
#define   TDES_MR_OPMOD_OFB (0x2u << 12) /**< \brief (TDES_MR) Output Feedback mode */
#define   TDES_MR_OPMOD_CFB (0x3u << 12) /**< \brief (TDES_MR) Cipher Feedback mode */
#define TDES_MR_LOD (0x1u << 15) /**< \brief (TDES_MR) Last Output Data Mode */
#define TDES_MR_CFBS_Pos 16
#define TDES_MR_CFBS_Msk (0x3u << TDES_MR_CFBS_Pos) /**< \brief (TDES_MR) Cipher Feedback Data Size */
#define TDES_MR_CFBS(value) ((TDES_MR_CFBS_Msk & ((value) << TDES_MR_CFBS_Pos)))
#define   TDES_MR_CFBS_SIZE_64BIT (0x0u << 16) /**< \brief (TDES_MR) 64-bit */
#define   TDES_MR_CFBS_SIZE_32BIT (0x1u << 16) /**< \brief (TDES_MR) 32-bit */
#define   TDES_MR_CFBS_SIZE_16BIT (0x2u << 16) /**< \brief (TDES_MR) 16-bit */
#define   TDES_MR_CFBS_SIZE_8BIT (0x3u << 16) /**< \brief (TDES_MR) 8-bit */
#define TDES_MR_CKEY_Pos 20
#define TDES_MR_CKEY_Msk (0xfu << TDES_MR_CKEY_Pos) /**< \brief (TDES_MR) Countermeasure Key */
#define TDES_MR_CKEY(value) ((TDES_MR_CKEY_Msk & ((value) << TDES_MR_CKEY_Pos)))
#define TDES_MR_CMTYP1 (0x1u << 24) /**< \brief (TDES_MR) Countermeasure Type 1 */
#define   TDES_MR_CMTYP1_NO_PAUSE (0x0u << 24) /**< \brief (TDES_MR) Countermeasure type 1 is disabled. */
#define   TDES_MR_CMTYP1_PAUSE (0x1u << 24) /**< \brief (TDES_MR) Countermeasure type 1 is enabled. */
#define TDES_MR_CMTYP2 (0x1u << 25) /**< \brief (TDES_MR) Countermeasure Type 2 */
#define   TDES_MR_CMTYP2_NO_DUMMY (0x0u << 25) /**< \brief (TDES_MR) Countermeasure type 2 is disabled. */
#define   TDES_MR_CMTYP2_DUMMY (0x1u << 25) /**< \brief (TDES_MR) Countermeasure type 2 is enabled. */
#define TDES_MR_CMTYP3 (0x1u << 26) /**< \brief (TDES_MR) Countermeasure Type 3 */
#define   TDES_MR_CMTYP3_NO_RESTART (0x0u << 26) /**< \brief (TDES_MR) Countermeasure type 3 is disabled. */
#define   TDES_MR_CMTYP3_RESTART (0x1u << 26) /**< \brief (TDES_MR) Countermeasure type 3 is enabled. */
#define TDES_MR_CMTYP4 (0x1u << 27) /**< \brief (TDES_MR) Countermeasure Type 4 */
#define   TDES_MR_CMTYP4_NO_IDLECURRENT (0x0u << 27) /**< \brief (TDES_MR) Countermeasure type 4 is disabled. */
#define   TDES_MR_CMTYP4_IDLECURRENT (0x1u << 27) /**< \brief (TDES_MR) Countermeasure type 4 is enabled. */
#define TDES_MR_CMTYP5 (0x1u << 28) /**< \brief (TDES_MR) Countermeasure Type 5 */
#define   TDES_MR_CMTYP5_NO_ADDACCESS (0x0u << 28) /**< \brief (TDES_MR) Countermeasure type 5 is disabled. */
#define   TDES_MR_CMTYP5_ADDACCESS (0x1u << 28) /**< \brief (TDES_MR) Countermeasure type 5 is enabled. */
#define TDES_MR_CMTYP6 (0x1u << 29) /**< \brief (TDES_MR) Countermeasure Type 6 */
#define   TDES_MR_CMTYP6_NO_UNIFORM (0x0u << 29) /**< \brief (TDES_MR) Countermeasure type 6 is disabled. */
#define   TDES_MR_CMTYP6_UNIFORM (0x1u << 29) /**< \brief (TDES_MR) Countermeasure type 6 is enabled. */
#define TDES_MR_CMTYP7 (0x1u << 30) /**< \brief (TDES_MR) Countermeasure Type 7 */
#define   TDES_MR_CMTYP7_NO_STARTDELAY (0x0u << 30) /**< \brief (TDES_MR) Countermeasure type 7 is disabled. */
#define   TDES_MR_CMTYP7_STARTDELAY (0x1u << 30) /**< \brief (TDES_MR) Countermeasure type 7 is enabled. */
#define TDES_MR_TAMPCLR (0x1u << 31) /**< \brief (TDES_MR) Tamper Pin Clear Key Enable */
/* -------- TDES_IER : (TDES Offset: 0x10) Interrupt Enable Register -------- */
#define TDES_IER_DATRDY (0x1u << 0) /**< \brief (TDES_IER) Data Ready Interrupt Enable */
#define TDES_IER_URAD (0x1u << 8) /**< \brief (TDES_IER) Unspecified Register Access Detection Interrupt Enable */
#define TDES_IER_SECE (0x1u << 16) /**< \brief (TDES_IER) Security and/or Safety Event Interrupt Enable */
/* -------- TDES_IDR : (TDES Offset: 0x14) Interrupt Disable Register -------- */
#define TDES_IDR_DATRDY (0x1u << 0) /**< \brief (TDES_IDR) Data Ready Interrupt Disable */
#define TDES_IDR_URAD (0x1u << 8) /**< \brief (TDES_IDR) Unspecified Register Access Detection Interrupt Disable */
#define TDES_IDR_SECE (0x1u << 16) /**< \brief (TDES_IDR) Security and/or Safety Event Interrupt Disable */
/* -------- TDES_IMR : (TDES Offset: 0x18) Interrupt Mask Register -------- */
#define TDES_IMR_DATRDY (0x1u << 0) /**< \brief (TDES_IMR) Data Ready Interrupt Mask */
#define TDES_IMR_URAD (0x1u << 8) /**< \brief (TDES_IMR) Unspecified Register Access Detection Interrupt Mask */
#define TDES_IMR_SECE (0x1u << 16) /**< \brief (TDES_IMR) Security and/or Safety Event Interrupt Mask */
/* -------- TDES_ISR : (TDES Offset: 0x1C) Interrupt Status Register -------- */
#define TDES_ISR_DATRDY (0x1u << 0) /**< \brief (TDES_ISR) Data Ready (cleared by setting TDES_CR.START or TDES_CR.SWRST, or by reading TDES_ODATARx) */
#define TDES_ISR_URAD (0x1u << 8) /**< \brief (TDES_ISR) Unspecified Register Access Detection Status (cleared by setting TDES_CR.SWRST) */
#define TDES_ISR_URAT_Pos 12
#define TDES_ISR_URAT_Msk (0x3u << TDES_ISR_URAT_Pos) /**< \brief (TDES_ISR) Unspecified Register Access (cleared by setting TDES_CR.SWRST) */
#define   TDES_ISR_URAT_IDR_WR_PROCESSING (0x0u << 12) /**< \brief (TDES_ISR) TDES_IDATAR written during data processing when SMOD = 0x2 mode. */
#define   TDES_ISR_URAT_ODR_RD_PROCESSING (0x1u << 12) /**< \brief (TDES_ISR) TDES_ODATAR read during data processing. */
#define   TDES_ISR_URAT_MR_WR_PROCESSING (0x2u << 12) /**< \brief (TDES_ISR) TDES_MR written during data processing. */
#define   TDES_ISR_URAT_WOR_RD_ACCESS (0x3u << 12) /**< \brief (TDES_ISR) Write-only register read access. */
#define TDES_ISR_SECE (0x1u << 16) /**< \brief (TDES_ISR) Security and/or Safety Event Interrupt Mask */
/* -------- TDES_KEY1WR[2] : (TDES Offset: 0x20) Key 1 Word Register -------- */
#define TDES_KEY1WR_KEY1W_Pos 0
#define TDES_KEY1WR_KEY1W_Msk (0xffffffffu << TDES_KEY1WR_KEY1W_Pos) /**< \brief (TDES_KEY1WR[2]) Key 1 Word */
#define TDES_KEY1WR_KEY1W(value) ((TDES_KEY1WR_KEY1W_Msk & ((value) << TDES_KEY1WR_KEY1W_Pos)))
/* -------- TDES_KEY2WR[2] : (TDES Offset: 0x28) Key 2 Word Register -------- */
#define TDES_KEY2WR_KEY2W_Pos 0
#define TDES_KEY2WR_KEY2W_Msk (0xffffffffu << TDES_KEY2WR_KEY2W_Pos) /**< \brief (TDES_KEY2WR[2]) Key 2 Word */
#define TDES_KEY2WR_KEY2W(value) ((TDES_KEY2WR_KEY2W_Msk & ((value) << TDES_KEY2WR_KEY2W_Pos)))
/* -------- TDES_KEY3WR[2] : (TDES Offset: 0x30) Key 3 Word Register -------- */
#define TDES_KEY3WR_KEY3W_Pos 0
#define TDES_KEY3WR_KEY3W_Msk (0xffffffffu << TDES_KEY3WR_KEY3W_Pos) /**< \brief (TDES_KEY3WR[2]) Key 3 Word */
#define TDES_KEY3WR_KEY3W(value) ((TDES_KEY3WR_KEY3W_Msk & ((value) << TDES_KEY3WR_KEY3W_Pos)))
/* -------- TDES_IDATAR[2] : (TDES Offset: 0x40) Input Data Register -------- */
#define TDES_IDATAR_IDATA_Pos 0
#define TDES_IDATAR_IDATA_Msk (0xffffffffu << TDES_IDATAR_IDATA_Pos) /**< \brief (TDES_IDATAR[2]) Input Data */
#define TDES_IDATAR_IDATA(value) ((TDES_IDATAR_IDATA_Msk & ((value) << TDES_IDATAR_IDATA_Pos)))
/* -------- TDES_ODATAR[2] : (TDES Offset: 0x50) Output Data Register -------- */
#define TDES_ODATAR_ODATA_Pos 0
#define TDES_ODATAR_ODATA_Msk (0xffffffffu << TDES_ODATAR_ODATA_Pos) /**< \brief (TDES_ODATAR[2]) Output Data */
/* -------- TDES_IVR[2] : (TDES Offset: 0x60) Initialization Vector Register -------- */
#define TDES_IVR_IV_Pos 0
#define TDES_IVR_IV_Msk (0xffffffffu << TDES_IVR_IV_Pos) /**< \brief (TDES_IVR[2]) Initialization Vector */
#define TDES_IVR_IV(value) ((TDES_IVR_IV_Msk & ((value) << TDES_IVR_IV_Pos)))
/* -------- TDES_XTEA_RNDR : (TDES Offset: 0x70) XTEA Rounds Register -------- */
#define TDES_XTEA_RNDR_XTEA_RNDS_Pos 0
#define TDES_XTEA_RNDR_XTEA_RNDS_Msk (0x3fu << TDES_XTEA_RNDR_XTEA_RNDS_Pos) /**< \brief (TDES_XTEA_RNDR) Number of Rounds */
#define TDES_XTEA_RNDR_XTEA_RNDS(value) ((TDES_XTEA_RNDR_XTEA_RNDS_Msk & ((value) << TDES_XTEA_RNDR_XTEA_RNDS_Pos)))
/* -------- TDES_WPMR : (TDES Offset: 0xE4) Write Protection Mode Register -------- */
#define TDES_WPMR_WPEN (0x1u << 0) /**< \brief (TDES_WPMR) Write Protection Enable */
#define TDES_WPMR_WPITEN (0x1u << 1) /**< \brief (TDES_WPMR) Write Protection Interrupt Enable */
#define TDES_WPMR_WPCREN (0x1u << 2) /**< \brief (TDES_WPMR) Write Protection Control Enable */
#define TDES_WPMR_FIRSTE (0x1u << 4) /**< \brief (TDES_WPMR) First Error Report Enable */
#define TDES_WPMR_ACTION_Pos 5
#define TDES_WPMR_ACTION_Msk (0x7u << TDES_WPMR_ACTION_Pos) /**< \brief (TDES_WPMR) Action on Abnormal Event Detection */
#define TDES_WPMR_ACTION(value) ((TDES_WPMR_ACTION_Msk & ((value) << TDES_WPMR_ACTION_Pos)))
#define   TDES_WPMR_ACTION_REPORT_ONLY (0x0u << 5) /**< \brief (TDES_WPMR) No action (stop or clear key) is performed when one of PKRPVS, WPVS, CGD, SEQE, or SWE flags are set. */
#define   TDES_WPMR_ACTION_LOCK_PKRPVS_WPVS_SWE (0x1u << 5) /**< \brief (TDES_WPMR) If a processing is in progress when the TDES_WPSR.PKRPVS/WPVS/SWE event detection occurs, the current processing is ended normally but no other processing is started while a TDES_CR.UNLOCK command is issued. */
#define   TDES_WPMR_ACTION_LOCK_CGD_SEQE (0x2u << 5) /**< \brief (TDES_WPMR) If a processing is in progress when the TDES_WPSR.CGD/SEQE event detection occurs, the current processing is ended normally but no other processing is started while a TDES_CR.UNLOCK command is issued. */
#define   TDES_WPMR_ACTION_LOCK_ANY_EV (0x3u << 5) /**< \brief (TDES_WPMR) If a processing is in progress when the TDES_WPSR.PKRPVS/WPVS/CGD/SEQE/SWE events detection occurs, the current processing is ended normally but no other processing is started while a TDES_CR.UNLOCK command is issued. */
#define   TDES_WPMR_ACTION_CLEAR_PKRPVS_WPVS_SWE (0x4u << 5) /**< \brief (TDES_WPMR) If a processing is in progress when the TDES_WPSR.PKRPVS/WPVS/SWE events detection occurs, the current processing is ended normally but no other processing is started while a TDES_CR.UNLOCK command is issued. Moreover, TDES_KEYxWRy are immediately cleared. */
#define   TDES_WPMR_ACTION_CLEAR_CGD_SEQE (0x5u << 5) /**< \brief (TDES_WPMR) If a processing is in progress when the TDES_WPSR.CGD/SEQE events detection occurs, the current processing is ended normally but no other processing is started while a TDES_CR.UNLOCK command is issued. Moreover, TDES_KEYxWRy are immediately cleared. */
#define   TDES_WPMR_ACTION_CLEAR_ANY_EV (0x6u << 5) /**< \brief (TDES_WPMR) If a processing is in progress when the TDES_WPSR.PKRPVS/WPVS/CGD/SEQE/SWE events detection occurs, the current processing is ended normally but no other processing is started while a TDES_CR.UNLOCK command is issued. Moreover, TDES_KEYxWRy are immediately cleared. */
#define TDES_WPMR_WPKEY_Pos 8
#define TDES_WPMR_WPKEY_Msk (0xffffffu << TDES_WPMR_WPKEY_Pos) /**< \brief (TDES_WPMR) Write Protection Key */
#define TDES_WPMR_WPKEY(value) ((TDES_WPMR_WPKEY_Msk & ((value) << TDES_WPMR_WPKEY_Pos)))
#define   TDES_WPMR_WPKEY_PASSWD (0x444553u << 8) /**< \brief (TDES_WPMR) Writing any other value in this field aborts the write operation of bits WPEN, WPITEN and WPCREN. Always reads as 0. */
/* -------- TDES_WPSR : (TDES Offset: 0xE8) Write Protection Status Register -------- */
#define TDES_WPSR_WPVS (0x1u << 0) /**< \brief (TDES_WPSR) Write Protection Violation Status (cleared on read) */
#define TDES_WPSR_CGD (0x1u << 1) /**< \brief (TDES_WPSR) Clock Glitch Detected (cleared on read) */
#define TDES_WPSR_SEQE (0x1u << 2) /**< \brief (TDES_WPSR) Internal Sequencer Error (cleared on read) */
#define TDES_WPSR_SWE (0x1u << 3) /**< \brief (TDES_WPSR) Software Control Error (cleared on read) */
#define TDES_WPSR_PKRPVS (0x1u << 4) /**< \brief (TDES_WPSR) Private Key Register Protection Violation Status (cleared on read) */
#define TDES_WPSR_WPVSRC_Pos 8
#define TDES_WPSR_WPVSRC_Msk (0xffffu << TDES_WPSR_WPVSRC_Pos) /**< \brief (TDES_WPSR) Write Protection Violation Source (cleared on read) */
#define TDES_WPSR_SWETYP_Pos 24
#define TDES_WPSR_SWETYP_Msk (0xfu << TDES_WPSR_SWETYP_Pos) /**< \brief (TDES_WPSR) Software Error Type (cleared on read) */
#define   TDES_WPSR_SWETYP_READ_WO (0x0u << 24) /**< \brief (TDES_WPSR) A write-only register has been read (Warning). */
#define   TDES_WPSR_SWETYP_WRITE_RO (0x1u << 24) /**< \brief (TDES_WPSR) TDES is enabled and a write access has been performed on a read-only register (Warning). */
#define   TDES_WPSR_SWETYP_UNDEF_RW (0x2u << 24) /**< \brief (TDES_WPSR) Access to an undefined address (Warning). */
#define   TDES_WPSR_SWETYP_CTRL_START (0x3u << 24) /**< \brief (TDES_WPSR) Abnormal use of TDES_CR.START command when DMA access is configured. */
#define   TDES_WPSR_SWETYP_WEIRD_ACTION (0x4u << 24) /**< \brief (TDES_WPSR) A key write, init value write, output data read, Mode register write, private key bus access or XTEA round register has been performed while a current processing is in progress (abnormal). */
#define   TDES_WPSR_SWETYP_INCOMPLETE_KEY (0x5u << 24) /**< \brief (TDES_WPSR) A tentative of start is required while the keys are not fully loaded into TDES_KEYxWRy. */
#define TDES_WPSR_ECLASS (0x1u << 31) /**< \brief (TDES_WPSR) Software Error Class (cleared on read) */
#define   TDES_WPSR_ECLASS_WARNING (0x0u << 31) /**< \brief (TDES_WPSR) An abnormal access that does not affect system functionality. */
#define   TDES_WPSR_ECLASS_ERROR (0x1u << 31) /**< \brief (TDES_WPSR) An access is performed into key, input data, control registers while the TDES is performing an encryption/decryption or a start is request by software or DMA while the key is not fully configured. */

/*@}*/


#endif /* _SAM9X_TDES_COMPONENT_ */
