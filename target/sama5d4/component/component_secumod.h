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

#ifndef _SAMA5D4_SECUMOD_COMPONENT_
#define _SAMA5D4_SECUMOD_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Security Module */
/* ============================================================================= */
/** \addtogroup SAMA5D4_SECUMOD Security Module */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Secumod internal memory */
typedef struct {
	__IO uint32_t BUSRAM_LOWER[1536]; /**< \brief (Securam Offset: 0x0000) Lower 6KB auto-erased */
	__IO uint32_t BUSRAM_HIGHER[512]; /**< \brief (Securam Offset: 0x1800) Higher 2KB not auto-erased */
	__IO uint32_t BUREG[16];          /**< \brief (Securam Offset: 0x2000) BUREG 512 bits auto-erased */
} Securam;

/** \brief Secumod hardware registers */
typedef struct {
	__O  uint32_t SECUMOD_CR;       /**< \brief (Secumod Offset: 0x0000) Control Register */
	__IO uint32_t SECUMOD_SYSR;     /**< \brief (Secumod Offset: 0x0004) System Status Register */
	__I  uint32_t SECUMOD_SR;       /**< \brief (Secumod Offset: 0x0008) Status Register */
	__I  uint32_t SECUMOD_ASR;      /**< \brief (Secumod Offset: 0x000C) Auxiliary Status Register */
	__O  uint32_t SECUMOD_SCR;      /**< \brief (Secumod Offset: 0x0010) Status Clear Register */
	__I  uint32_t SECUMOD_RAMRDY;   /**< \brief (Secumod Offset: 0x0014) RAM Access Ready Register */
	__IO uint32_t SECUMOD_PIOBU[8]; /**< \brief (Secumod Offset: 0x0018) PIO Backup Register */
	__I  uint32_t Reserved1[12];
	__IO uint32_t SECUMOD_JTAGCR;   /**< \brief (Secumod Offset: 0x0068) JTAG Protection Control Register */
	__IO uint32_t SECUMOD_DYSTUNE;  /**< \brief (Secumod Offset: 0x006C) Dynamic Signatures Tuning Register */
	__IO uint32_t SECUMOD_SCRKEY;   /**< \brief (Secumod Offset: 0x0070) Scrambling Key Register */
	__IO uint32_t SECUMOD_RAMACC;   /**< \brief (Secumod Offset: 0x0074) RAM Access Rights Register */
	__IO uint32_t SECUMOD_RAMACCSR; /**< \brief (Secumod Offset: 0x0078) RAM Access Rights Status Register */
	__IO uint32_t SECUMOD_BMPR;     /**< \brief (Secumod Offset: 0x007C) Backup Mode Protection Register */
	__IO uint32_t SECUMOD_NMPR;     /**< \brief (Secumod Offset: 0x0080) Normal Mode Protection Register */
	__O  uint32_t SECUMOD_NIEPR;    /**< \brief (Secumod Offset: 0x0084) Normal Interrupt Enable Protection Register */
	__O  uint32_t SECUMOD_NIDPR;    /**< \brief (Secumod Offset: 0x0088) Normal Interrupt Disable Protection Register */
	__I  uint32_t SECUMOD_NIMPR;    /**< \brief (Secumod Offset: 0x008C) Normal Interrupt Mask Protection Register */
	__IO uint32_t SECUMOD_WKPR;     /**< \brief (Secumod Offset: 0x0090) Wake Up Protection Register */
} Secumod;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- SECUMOD_CR : (SECUMOD Offset: 0x0000) Control Register -------- */
#define SECUMOD_CR_BACKUP (0x1u << 0) /**< \brief (SECUMOD_CR) Backup Mode */
#define SECUMOD_CR_NORMAL (0x1u << 1) /**< \brief (SECUMOD_CR) Normal Mode */
#define SECUMOD_CR_SWPROT (0x1u << 2) /**< \brief (SECUMOD_CR) Software Protection */
#define SECUMOD_CR_NIMP_EN_Pos 3
#define SECUMOD_CR_NIMP_EN_Msk (0x3u << SECUMOD_CR_NIMP_EN_Pos) /**< \brief (SECUMOD_CR) Non-Imprinting Enable */
#define SECUMOD_CR_NIMP_EN(value) ((SECUMOD_CR_NIMP_EN_Msk & ((value) << SECUMOD_CR_NIMP_EN_Pos)))
#define SECUMOD_CR_NIMP_EN_DISABLE (0x2u << 3) /**< \brief (SECUMOD_CR) Non-imprinting mechanism is disabled (default) */
#define SECUMOD_CR_NIMP_EN_ENABLE  (0x1u << 3) /**< \brief (SECUMOD_CR) Non-imprinting mechanism is authorized to start when the required conditions are met */
#define SECUMOD_CR_AUTOBKP_Pos 5
#define SECUMOD_CR_AUTOBKP_Msk (0x3u << SECUMOD_CR_AUTOBKP_Pos) /**< \brief (SECUMOD_CR) Automatic Normal to Backup Mode Switching */
#define SECUMOD_CR_AUTOBKP(value) ((SECUMOD_CR_AUTOBKP_Msk & ((value) << SECUMOD_CR_AUTOBKP_Pos)))
#define SECUMOD_CR_AUTOBKP_SW_SWITCH   (0x2u << 3) /**< \brief (SECUMOD_CR) When in Normal mode, software must switch to Backup mode before powering down the core */
#define SECUMOD_CR_AUTOBKP_AUTO_SWITCH (0x1u << 3) /**< \brief (SECUMOD_CR) When in Normal mode, the power down of the core supply will automatically switch the mode to Backup mode, simultaneously with core to backup isolation barrier activation. (default) */
#define SECUMOD_CR_SCRAMB_Pos 9
#define SECUMOD_CR_SCRAMB_Msk (0x3u << SECUMOD_CR_SCRAMB_Pos) /**< \brief (SECUMOD_CR) Memory Scrambling Enable */
#define SECUMOD_CR_SCRAMB(value) ((SECUMOD_CR_SCRAMB_Msk & ((value) << SECUMOD_CR_SCRAMB_Pos)))
#define SECUMOD_CR_SCRAMB_DISABLE (0x2u << 3) /**< \brief (SECUMOD_CR) Memories are not scrambled */
#define SECUMOD_CR_SCRAMB_ENABLE  (0x1u << 3) /**< \brief (SECUMOD_CR) Memories are scrambled (default) */
#define SECUMOD_CR_KEY_Pos 16
#define SECUMOD_CR_KEY_Msk (0xffffu << SECUMOD_CR_KEY_Pos) /**< \brief (SECUMOD_CR) Password */
#define SECUMOD_CR_KEY(value) ((SECUMOD_CR_KEY_Msk & ((value) << SECUMOD_CR_KEY_Pos)))
#define   SECUMOD_CR_KEY_TOGGLE (SECUMOD_CR_KEY(0x89CAu))
/* -------- SECUMOD_SYSR : (SECUMOD Offset: 0x0004) System Status Register -------- */
#define SECUMOD_SYSR_ERASE_DONE (0x1u << 0) /**< \brief (SECUMOD_SYSR) Erasable Memories State (RW) */
#define SECUMOD_SYSR_ERASE_ON (0x1u << 1) /**< \brief (SECUMOD_SYSR) Erase Process Ongoing (RO) */
#define SECUMOD_SYSR_BACKUP (0x1u << 2) /**< \brief (SECUMOD_SYSR) Backup Mode (RO) */
#define SECUMOD_SYSR_SWKUP (0x1u << 3) /**< \brief (SECUMOD_SYSR) SWKUP State (RO) */
#define SECUMOD_SYSR_NIMP_EN (0x1u << 5) /**< \brief (SECUMOD_SYSR) Non-Imprinting Enabled (RO) */
#define SECUMOD_SYSR_AUTOBKP (0x1u << 6) /**< \brief (SECUMOD_SYSR) Automatic Backup Mode Enabled (RO) */
#define SECUMOD_SYSR_SCRAMB (0x1u << 7) /**< \brief (SECUMOD_SYSR) Scrambling Enabled (RO) */
/* -------- SECUMOD_SR : (SECUMOD Offset: 0x0008) Status Register -------- */
#define SECUMOD_SR_TST (0x1u << 2) /**< \brief (SECUMOD_SR) Test Pin Monitor */
#define SECUMOD_SR_JTAG (0x1u << 3) /**< \brief (SECUMOD_SR) JTAG Pins Monitor */
#define SECUMOD_SR_DET0 (0x1u << 16) /**< \brief (SECUMOD_SR) PIOBU Intrusion Detector */
#define SECUMOD_SR_DET1 (0x1u << 17) /**< \brief (SECUMOD_SR) PIOBU Intrusion Detector */
#define SECUMOD_SR_DET2 (0x1u << 18) /**< \brief (SECUMOD_SR) PIOBU Intrusion Detector */
#define SECUMOD_SR_DET3 (0x1u << 19) /**< \brief (SECUMOD_SR) PIOBU Intrusion Detector */
#define SECUMOD_SR_DET4 (0x1u << 20) /**< \brief (SECUMOD_SR) PIOBU Intrusion Detector */
#define SECUMOD_SR_DET5 (0x1u << 21) /**< \brief (SECUMOD_SR) PIOBU Intrusion Detector */
#define SECUMOD_SR_DET6 (0x1u << 22) /**< \brief (SECUMOD_SR) PIOBU Intrusion Detector */
#define SECUMOD_SR_DET7 (0x1u << 23) /**< \brief (SECUMOD_SR) PIOBU Intrusion Detector */
/* -------- SECUMOD_ASR : (SECUMOD Offset: 0x000C) Auxiliary Status Register -------- */
#define SECUMOD_ASR_JTAG (0x1u << 4) /**< \brief (SECUMOD_ASR) JTAGSEL, CA5 tap response or CA5 debug acknowledge is the cause of JTAG flag in SECUMOD_SR. */
#define SECUMOD_ASR_TCK (0x1u << 5) /**< \brief (SECUMOD_ASR) TCK/TMS activity detected is the cause of JTAG flag in SECUMOD_SR. */
/* -------- SECUMOD_SCR : (SECUMOD Offset: 0x0010) Status Clear Register -------- */
#define SECUMOD_SCR_TST (0x1u << 2) /**< \brief (SECUMOD_SCR) Test Pin Monitor */
#define SECUMOD_SCR_JTAG (0x1u << 3) /**< \brief (SECUMOD_SCR) JTAG Pins Monitor */
#define SECUMOD_SCR_DET0 (0x1u << 16) /**< \brief (SECUMOD_SCR) PIOBU Intrusion Detector */
#define SECUMOD_SCR_DET1 (0x1u << 17) /**< \brief (SECUMOD_SCR) PIOBU Intrusion Detector */
#define SECUMOD_SCR_DET2 (0x1u << 18) /**< \brief (SECUMOD_SCR) PIOBU Intrusion Detector */
#define SECUMOD_SCR_DET3 (0x1u << 19) /**< \brief (SECUMOD_SCR) PIOBU Intrusion Detector */
#define SECUMOD_SCR_DET4 (0x1u << 20) /**< \brief (SECUMOD_SCR) PIOBU Intrusion Detector */
#define SECUMOD_SCR_DET5 (0x1u << 21) /**< \brief (SECUMOD_SCR) PIOBU Intrusion Detector */
#define SECUMOD_SCR_DET6 (0x1u << 22) /**< \brief (SECUMOD_SCR) PIOBU Intrusion Detector */
#define SECUMOD_SCR_DET7 (0x1u << 23) /**< \brief (SECUMOD_SCR) PIOBU Intrusion Detector */
/* -------- SECUMOD_RAMRDY : (SECUMOD Offset: 0x0014) RAM Access Ready Register -------- */
#define SECUMOD_RAMRDY_READY (0x1u << 0) /**< \brief (SECUMOD_RAMRDY) Ready for system access flag */
/* -------- SECUMOD_PIOBU[8] : (SECUMOD Offset: 0x0018) PIO Backup Register -------- */
#define SECUMOD_PIOBU_AFV_Pos 0
#define SECUMOD_PIOBU_AFV_Msk (0xfu << SECUMOD_PIOBU_AFV_Pos) /**< \brief (SECUMOD_PIOBU[8]) PIOBU Alarm Filter Value */
#define SECUMOD_PIOBU_AFV_0   (0x0u << 0) /**< \brief (SECUMOD_PIOBU) Maximun Counter Value is 0 */
#define SECUMOD_PIOBU_AFV_2   (0x1u << 0) /**< \brief (SECUMOD_PIOBU) Maximun Counter Value is 2 */
#define SECUMOD_PIOBU_AFV_4   (0x2u << 0) /**< \brief (SECUMOD_PIOBU) Maximun Counter Value is 4 */
#define SECUMOD_PIOBU_AFV_8   (0x3u << 0) /**< \brief (SECUMOD_PIOBU) Maximun Counter Value is 8 */
#define SECUMOD_PIOBU_AFV_16  (0x4u << 0) /**< \brief (SECUMOD_PIOBU) Maximun Counter Value is 16 */
#define SECUMOD_PIOBU_AFV_32  (0x5u << 0) /**< \brief (SECUMOD_PIOBU) Maximun Counter Value is 32 */
#define SECUMOD_PIOBU_AFV_64  (0x6u << 0) /**< \brief (SECUMOD_PIOBU) Maximun Counter Value is 64 */
#define SECUMOD_PIOBU_AFV_128 (0x7u << 0) /**< \brief (SECUMOD_PIOBU) Maximun Counter Value is 128 */
#define SECUMOD_PIOBU_AFV_256 (0x8u << 0) /**< \brief (SECUMOD_PIOBU) Maximun Counter Value is 256 */
#define SECUMOD_PIOBU_AFV_512 (0x9u << 0) /**< \brief (SECUMOD_PIOBU) Maximun Counter Value is 512 */
#define SECUMOD_PIOBU_AFV_512 (0x9u << 0) /**< \brief (SECUMOD_PIOBU) Maximun Counter Value is 512 */
#define SECUMOD_PIOBU_AFV(value) ((SECUMOD_PIOBU_AFV_Msk & ((value) << SECUMOD_PIOBU_AFV_Pos)))
#define SECUMOD_PIOBU_RFV_Pos 4
#define SECUMOD_PIOBU_RFV_Msk (0xFu << SECUMOD_PIOBU_RFV_Pos) /**< \brief (SECUMOD_PIOBU) PIOBU Reset Filter Value */
#define SECUMOD_PIOBU_RFV_0   (0x0u << 4) /**< \brief (SECUMOD_PIOBU) Maximun Counter Value is 0 */
#define SECUMOD_PIOBU_RFV_2   (0x1u << 4) /**< \brief (SECUMOD_PIOBU) Maximun Counter Value is 2 */
#define SECUMOD_PIOBU_RFV_4   (0x2u << 4) /**< \brief (SECUMOD_PIOBU) Maximun Counter Value is 4 */
#define SECUMOD_PIOBU_RFV_8   (0x3u << 4) /**< \brief (SECUMOD_PIOBU) Maximun Counter Value is 8 */
#define SECUMOD_PIOBU_RFV_16  (0x4u << 4) /**< \brief (SECUMOD_PIOBU) Maximun Counter Value is 16 */
#define SECUMOD_PIOBU_RFV_32  (0x5u << 4) /**< \brief (SECUMOD_PIOBU) Maximun Counter Value is 32 */
#define SECUMOD_PIOBU_RFV_64  (0x6u << 4) /**< \brief (SECUMOD_PIOBU) Maximun Counter Value is 64 */
#define SECUMOD_PIOBU_RFV_128 (0x7u << 4) /**< \brief (SECUMOD_PIOBU) Maximun Counter Value is 128 */
#define SECUMOD_PIOBU_RFV_256 (0x8u << 4) /**< \brief (SECUMOD_PIOBU) Maximun Counter Value is 256 */
#define SECUMOD_PIOBU_RFV_512 (0x9u << 4) /**< \brief (SECUMOD_PIOBU) Maximun Counter Value is 512 */
#define SECUMOD_PIOBU_RFV_512 (0x9u << 4) /**< \brief (SECUMOD_PIOBU) Maximun Counter Value is 512 */
#define SECUMOD_PIOBU_RFV(value) ((SECUMOD_PIOBU_RFV_Msk & ((value) << SECUMOD_PIOBU_RFV_Pos)))
#define SECUMOD_PIOBU_OUTPUT (0x1u << 8) /**< \brief (SECUMOD_PIOBU[8]) Configure I/O Line in Input/Output */
#define SECUMOD_PIOBU_OUTPUT_PURE_INPUT     (0x0u << 8) /**< \brief (SECUMOD_PIOBU) The I/O is a pure input */
#define SECUMOD_PIOBU_OUTPUT_ENABLED_OUTPUT (0x1u << 8) /**< \brief (SECUMOD_PIOBU) The I/O is enabled in output */
#define SECUMOD_PIOBU_PIO_SOD (0x1u << 9) /**< \brief (SECUMOD_PIOBU[8]) Set/Clear the I/O Line when configured in Output Mode (OUTPUT =1) */
#define SECUMOD_PIOBU_PIO_PDS (0x1u << 10) /**< \brief (SECUMOD_PIOBU[8]) Level on the Pin in Input Mode (OUTPUT = 0) (Read-only) */
#define SECUMOD_PIOBU_PULLUP_Pos 12
#define SECUMOD_PIOBU_PULLUP_Msk (0x3u << SECUMOD_PIOBU_PULLUP_Pos) /**< \brief (SECUMOD_PIOBU[8]) Programmable Pull-up State */
#define SECUMOD_PIOBU_PULLUP(value) ((SECUMOD_PIOBU_PULLUP_Msk & ((value) << SECUMOD_PIOBU_PULLUP_Pos)))
#define SECUMOD_PIOBU_PULLUP_NONE      (0x0u << 12) /**< \brief (SECUMOD_PIOBU) No pull-up/pull-down connected */
#define SECUMOD_PIOBU_PULLUP_PULL_UP   (0x1u << 12) /**< \brief (SECUMOD_PIOBU) Pull-up connected */
#define SECUMOD_PIOBU_PULLUP_PULL_DOWN (0x2u << 12) /**< \brief (SECUMOD_PIOBU) Pull-down connected */
#define SECUMOD_PIOBU_SCHEDULE (0x1u << 14) /**< \brief (SECUMOD_PIOBU[8]) Pull-up/Down Scheduled */
#define SECUMOD_PIOBU_SWITCH (0x1u << 15) /**< \brief (SECUMOD_PIOBU[8]) Switch State for Intrusion Detection */
#define SECUMOD_PIOBU_DYNSTAT (0x1u << 20) /**< \brief (SECUMOD_PIOBU[8]) Switch for Static or Dynamic Detection Intrusion */
#define SECUMOD_PIOBU_FILTER3_5 (0x1u << 21) /**< \brief (SECUMOD_PIOBU[8]) Filter for Dynamic Signatures Input */
/* -------- SECUMOD_JTAGCR : (SECUMOD Offset: 0x0068) JTAG Protection Control Register -------- */
#define SECUMOD_JTAGCR_FNTRST (0x1u << 0) /**< \brief (SECUMOD_JTAGCR) Force NTRST */
#define SECUMOD_JTAGCR_CA5_DEBUG_MODE_Pos 1
#define SECUMOD_JTAGCR_CA5_DEBUG_MODE_Msk (0x7u << SECUMOD_JTAGCR_CA5_DEBUG_MODE_Pos) /**< \brief (SECUMOD_JTAGCR) Cortex-A5 Invasive/Non-Invasive Secure/Non-Secure Debug Permissions */
#define SECUMOD_JTAGCR_CA5_DEBUG_MODE(value) ((SECUMOD_JTAGCR_CA5_DEBUG_MODE_Msk & ((value) << SECUMOD_JTAGCR_CA5_DEBUG_MODE_Pos)))
#define SECUMOD_JTAGCR_CA5_DEBUG_MODE_NO_DEBUG    (0x0u << 1) /**< \brief (SECUMOD_JTAGCR) No debug */
#define SECUMOD_JTAGCR_CA5_DEBUG_MODE_NINS        (0x1u << 1) /**< \brief (SECUMOD_JTAGCR) Non-Invasive Non-Secure */
#define SECUMOD_JTAGCR_CA5_DEBUG_MODE_FULL_NS     (0x2u << 1) /**< \brief (SECUMOD_JTAGCR) Full Non-Secure (Invasive and Non-Invasive) */
#define SECUMOD_JTAGCR_CA5_DEBUG_MODE_FULL_NS_NIS (0x3u << 1) /**< \brief (SECUMOD_JTAGCR) Full Non-Secure + Non-Invasive Secure */
#define SECUMOD_JTAGCR_CA5_DEBUG_MODE_FULL_DEBUG  (0x4u << 1) /**< \brief (SECUMOD_JTAGCR) Full debug allowed */
#define SECUMOD_JTAGCR_CA5_DEBUG_MON (0x1u << 4) /**< \brief (SECUMOD_JTAGCR) Cortex-A5 Debug Acknowledge (DBGACK) Monitoring */
/* -------- SECUMOD_DYSTUNE : (SECUMOD Offset: 0x006C) Dynamic Signatures Tuning Register -------- */
#define SECUMOD_DYSTUNE_RX_ERROR_THRESHOLD_Pos 0
#define SECUMOD_DYSTUNE_RX_ERROR_THRESHOLD_Msk (0x7fu << SECUMOD_DYSTUNE_RX_ERROR_THRESHOLD_Pos) /**< \brief (SECUMOD_DYSTUNE) Error Detection Threshold */
#define SECUMOD_DYSTUNE_RX_ERROR_THRESHOLD(value) ((SECUMOD_DYSTUNE_RX_ERROR_THRESHOLD_Msk & ((value) << SECUMOD_DYSTUNE_RX_ERROR_THRESHOLD_Pos)))
#define SECUMOD_DYSTUNE_NOPA (0x1u << 7) /**< \brief (SECUMOD_DYSTUNE) No Periodic Alarm */
#define SECUMOD_DYSTUNE_RX_OK_CORREL_NUMBER_Pos 8
#define SECUMOD_DYSTUNE_RX_OK_CORREL_NUMBER_Msk (0xffu << SECUMOD_DYSTUNE_RX_OK_CORREL_NUMBER_Pos) /**< \brief (SECUMOD_DYSTUNE) Error Counter Reset Threshold */
#define SECUMOD_DYSTUNE_RX_OK_CORREL_NUMBER(value) ((SECUMOD_DYSTUNE_RX_OK_CORREL_NUMBER_Msk & ((value) << SECUMOD_DYSTUNE_RX_OK_CORREL_NUMBER_Pos)))
#define SECUMOD_DYSTUNE_PERIOD_Pos 16
#define SECUMOD_DYSTUNE_PERIOD_Msk (0xffffu << SECUMOD_DYSTUNE_PERIOD_Pos) /**< \brief (SECUMOD_DYSTUNE) Signature Clock Period */
#define SECUMOD_DYSTUNE_PERIOD(value) ((SECUMOD_DYSTUNE_PERIOD_Msk & ((value) << SECUMOD_DYSTUNE_PERIOD_Pos)))
/* -------- SECUMOD_SCRKEY : (SECUMOD Offset: 0x0070) Scrambling Key Register -------- */
#define SECUMOD_SCRKEY_SCRKEY_Pos 0
#define SECUMOD_SCRKEY_SCRKEY_Msk (0xffffffffu << SECUMOD_SCRKEY_SCRKEY_Pos) /**< \brief (SECUMOD_SCRKEY) Scrambling Key Value */
#define SECUMOD_SCRKEY_SCRKEY(value) ((SECUMOD_SCRKEY_SCRKEY_Msk & ((value) << SECUMOD_SCRKEY_SCRKEY_Pos)))
/* -------- SECUMOD_RAMACC : (SECUMOD Offset: 0x0074) RAM Access Rights Register -------- */
#define SECUMOD_RAMACC_RW0_Pos 0
#define SECUMOD_RAMACC_RW0_Msk (0x3u << SECUMOD_RAMACC_RW0_Pos) /**< \brief (SECUMOD_RAMACC) Access right for RAM region [0; 1 Kbyte] */
#define SECUMOD_RAMACC_RW0(value) ((SECUMOD_RAMACC_RW0_Msk & ((value) << SECUMOD_RAMACC_RW0_Pos)))
#define SECUMOD_RAMACC_RW1_Pos 2
#define SECUMOD_RAMACC_RW1_Msk (0x3u << SECUMOD_RAMACC_RW1_Pos) /**< \brief (SECUMOD_RAMACC) Access right for RAM region [1 Kbyte; 2 Kbytes] */
#define SECUMOD_RAMACC_RW1(value) ((SECUMOD_RAMACC_RW1_Msk & ((value) << SECUMOD_RAMACC_RW1_Pos)))
#define SECUMOD_RAMACC_RW2_Pos 4
#define SECUMOD_RAMACC_RW2_Msk (0x3u << SECUMOD_RAMACC_RW2_Pos) /**< \brief (SECUMOD_RAMACC) Access right for RAM region [2 Kbytes; 3 Kbytes] */
#define SECUMOD_RAMACC_RW2(value) ((SECUMOD_RAMACC_RW2_Msk & ((value) << SECUMOD_RAMACC_RW2_Pos)))
#define SECUMOD_RAMACC_RW3_Pos 6
#define SECUMOD_RAMACC_RW3_Msk (0x3u << SECUMOD_RAMACC_RW3_Pos) /**< \brief (SECUMOD_RAMACC) Access right for RAM region [3 Kbytes; 4 Kbytes] */
#define SECUMOD_RAMACC_RW3(value) ((SECUMOD_RAMACC_RW3_Msk & ((value) << SECUMOD_RAMACC_RW3_Pos)))
#define SECUMOD_RAMACC_RW4_Pos 8
#define SECUMOD_RAMACC_RW4_Msk (0x3u << SECUMOD_RAMACC_RW4_Pos) /**< \brief (SECUMOD_RAMACC) Access right for RAM region [4 Kbytes; 5 Kbytes] */
#define SECUMOD_RAMACC_RW4(value) ((SECUMOD_RAMACC_RW4_Msk & ((value) << SECUMOD_RAMACC_RW4_Pos)))
#define SECUMOD_RAMACC_RW5_Pos 10
#define SECUMOD_RAMACC_RW5_Msk (0x3u << SECUMOD_RAMACC_RW5_Pos) /**< \brief (SECUMOD_RAMACC) Access right for RAM region [5 Kbytes; 6 Kbytes] */
#define SECUMOD_RAMACC_RW5(value) ((SECUMOD_RAMACC_RW5_Msk & ((value) << SECUMOD_RAMACC_RW5_Pos)))
#define SECUMOD_RAMACC_RW6_Pos 12
#define SECUMOD_RAMACC_RW6_Msk (0x3u << SECUMOD_RAMACC_RW6_Pos) /**< \brief (SECUMOD_RAMACC) Access right for RAM region [6 Kbytes; 7 Kbytes] (SECURAM_2KB) */
#define SECUMOD_RAMACC_RW6(value) ((SECUMOD_RAMACC_RW6_Msk & ((value) << SECUMOD_RAMACC_RW6_Pos)))
#define SECUMOD_RAMACC_RW7_Pos 14
#define SECUMOD_RAMACC_RW7_Msk (0x3u << SECUMOD_RAMACC_RW7_Pos) /**< \brief (SECUMOD_RAMACC) Access right for RAM region [7 Kbytes; 8 Kbytes] (SECURAM_2KB) */
#define SECUMOD_RAMACC_RW7(value) ((SECUMOD_RAMACC_RW7_Msk & ((value) << SECUMOD_RAMACC_RW7_Pos)))
#define SECUMOD_RAMACC_RW8_Pos 16
#define SECUMOD_RAMACC_RW8_Msk (0x3u << SECUMOD_RAMACC_RW8_Pos) /**< \brief (SECUMOD_RAMACC) Access right for RAM region [8 Kbytes; 9 Kbytes] (register bank SECURAM_512b) */
#define SECUMOD_RAMACC_RW8(value) ((SECUMOD_RAMACC_RW8_Msk & ((value) << SECUMOD_RAMACC_RW8_Pos)))
#define SECUMOD_RAMACC_RWx_Pos(x)          ( 2 * (x) )
#define SECUMOD_RAMACC_RWx_Msk(x)          ( 0x3u << ( 2 * (x) ) ) /**< \brief (SECUMOD_RAMACC) Access right for RAM region */
#define SECUMOD_RAMACC_RWx_NO_ACCESS(x)    ( 0x0u << ( 2 * (x) ) ) /**< \brief (SECUMOD_RAMACC) No access allowed */
#define SECUMOD_RAMACC_RWx_WR_ACCESS(x)    ( 0x1u << ( 2 * (x) ) ) /**< \brief (SECUMOD_RAMACC) Only write access allowed */
#define SECUMOD_RAMACC_RWx_RD_ACCESS(x)    ( 0x2u << ( 2 * (x) ) ) /**< \brief (SECUMOD_RAMACC) Only read access allowed */
#define SECUMOD_RAMACC_RWx_RD_WR_ACCESS(x) ( 0x3u << ( 2 * (x) ) ) /**< \brief (SECUMOD_RAMACC) Read and write access allowed */
/* -------- SECUMOD_RAMACCSR : (SECUMOD Offset: 0x0078) RAM Access Rights Status Register -------- */
#define SECUMOD_RAMACCSR_RW0_Pos 0
#define SECUMOD_RAMACCSR_RW0_Msk (0x3u << SECUMOD_RAMACCSR_RW0_Pos) /**< \brief (SECUMOD_RAMACCSR) Access right status for RAM region [0; 1 Kbyte] */
#define SECUMOD_RAMACCSR_RW0(value) ((SECUMOD_RAMACCSR_RW0_Msk & ((value) << SECUMOD_RAMACCSR_RW0_Pos)))
#define SECUMOD_RAMACCSR_RW1_Pos 2
#define SECUMOD_RAMACCSR_RW1_Msk (0x3u << SECUMOD_RAMACCSR_RW1_Pos) /**< \brief (SECUMOD_RAMACCSR) Access right status for RAM region [1 Kbytes; 2 Kbytes] */
#define SECUMOD_RAMACCSR_RW1(value) ((SECUMOD_RAMACCSR_RW1_Msk & ((value) << SECUMOD_RAMACCSR_RW1_Pos)))
#define SECUMOD_RAMACCSR_RW2_Pos 4
#define SECUMOD_RAMACCSR_RW2_Msk (0x3u << SECUMOD_RAMACCSR_RW2_Pos) /**< \brief (SECUMOD_RAMACCSR) Access right status for RAM region [2 Kbytes; 3 Kbytes] */
#define SECUMOD_RAMACCSR_RW2(value) ((SECUMOD_RAMACCSR_RW2_Msk & ((value) << SECUMOD_RAMACCSR_RW2_Pos)))
#define SECUMOD_RAMACCSR_RW3_Pos 6
#define SECUMOD_RAMACCSR_RW3_Msk (0x3u << SECUMOD_RAMACCSR_RW3_Pos) /**< \brief (SECUMOD_RAMACCSR) Access right status for RAM region [3 Kbytes; 4 Kbytes] */
#define SECUMOD_RAMACCSR_RW3(value) ((SECUMOD_RAMACCSR_RW3_Msk & ((value) << SECUMOD_RAMACCSR_RW3_Pos)))
#define SECUMOD_RAMACCSR_RW4_Pos 8
#define SECUMOD_RAMACCSR_RW4_Msk (0x3u << SECUMOD_RAMACCSR_RW4_Pos) /**< \brief (SECUMOD_RAMACCSR) Access right status for RAM region [4 Kbytes; 5 Kbytes] */
#define SECUMOD_RAMACCSR_RW4(value) ((SECUMOD_RAMACCSR_RW4_Msk & ((value) << SECUMOD_RAMACCSR_RW4_Pos)))
#define SECUMOD_RAMACCSR_RW5_Pos 10
#define SECUMOD_RAMACCSR_RW5_Msk (0x3u << SECUMOD_RAMACCSR_RW5_Pos) /**< \brief (SECUMOD_RAMACCSR) Access right status for RAM region [5 Kbytes; 6 Kbytes] */
#define SECUMOD_RAMACCSR_RW5(value) ((SECUMOD_RAMACCSR_RW5_Msk & ((value) << SECUMOD_RAMACCSR_RW5_Pos)))
#define SECUMOD_RAMACCSR_RW6_Pos 10
#define SECUMOD_RAMACCSR_RW6_Msk (0x3u << SECUMOD_RAMACCSR_RW6_Pos) /**< \brief (SECUMOD_RAMACCSR) Access right status for RAM region [6 Kbytes; 7 Kbytes] (SECURAM_2KB) */
#define SECUMOD_RAMACCSR_RW6(value) ((SECUMOD_RAMACCSR_RW6_Msk & ((value) << SECUMOD_RAMACCSR_RW6_Pos)))
#define SECUMOD_RAMACCSR_RW7_Pos 10
#define SECUMOD_RAMACCSR_RW7_Msk (0x3u << SECUMOD_RAMACCSR_RW7_Pos) /**< \brief (SECUMOD_RAMACCSR) Access right status for RAM region [7 Kbytes; 8 Kbytes] (SECURAM_2KB) */
#define SECUMOD_RAMACCSR_RW7(value) ((SECUMOD_RAMACCSR_RW7_Msk & ((value) << SECUMOD_RAMACCSR_RW7_Pos)))
#define SECUMOD_RAMACCSR_RW8_Pos 10
#define SECUMOD_RAMACCSR_RW8_Msk (0x3u << SECUMOD_RAMACCSR_RW8_Pos) /**< \brief (SECUMOD_RAMACCSR) Access right status for RAM region [8 Kbytes; 9 Kbytes] (register bank SECURAM_512b) */
#define SECUMOD_RAMACCSR_RW8(value) ((SECUMOD_RAMACCSR_RW8_Msk & ((value) << SECUMOD_RAMACCSR_RW8_Pos)))
#define SECUMOD_RAMACCSR_RWx_Pos(x)          ( 2 * (x) )
#define SECUMOD_RAMACCSR_NO_VIOLATION        ( 0x0u ) /**< \brief (SECUMOD_RAMACCSR) No access violation occurred */
#define SECUMOD_RAMACCSR_W_VIOLATION         ( 0x1u ) /**< \brief (SECUMOD_RAMACCSR) Only write access violation occurred */
#define SECUMOD_RAMACCSR_R_VIOLATION         ( 0x2u ) /**< \brief (SECUMOD_RAMACCSR) Only read access violation occurred */
#define SECUMOD_RAMACCSR_RW_VIOLATION        ( 0x3u ) /**< \brief (SECUMOD_RAMACCSR) Read and write access violation occurred */
/* -------- SECUMOD_BMPR : (SECUMOD Offset: 0x007C) Backup Mode Protection Register -------- */
#define SECUMOD_BMPR_ALL  (0x00FF0004u)
#define SECUMOD_BMPR_TST (0x1u << 2) /**< \brief (SECUMOD_BMPR) Test Pin Protection */
#define SECUMOD_BMPR_DET0 (0x1u << 16) /**< \brief (SECUMOD_BMPR) PIOBU Intrusion Detector Protection */
#define SECUMOD_BMPR_DET1 (0x1u << 17) /**< \brief (SECUMOD_BMPR) PIOBU Intrusion Detector Protection */
#define SECUMOD_BMPR_DET2 (0x1u << 18) /**< \brief (SECUMOD_BMPR) PIOBU Intrusion Detector Protection */
#define SECUMOD_BMPR_DET3 (0x1u << 19) /**< \brief (SECUMOD_BMPR) PIOBU Intrusion Detector Protection */
#define SECUMOD_BMPR_DET4 (0x1u << 20) /**< \brief (SECUMOD_BMPR) PIOBU Intrusion Detector Protection */
#define SECUMOD_BMPR_DET5 (0x1u << 21) /**< \brief (SECUMOD_BMPR) PIOBU Intrusion Detector Protection */
#define SECUMOD_BMPR_DET6 (0x1u << 22) /**< \brief (SECUMOD_BMPR) PIOBU Intrusion Detector Protection */
#define SECUMOD_BMPR_DET7 (0x1u << 23) /**< \brief (SECUMOD_BMPR) PIOBU Intrusion Detector Protection */
/* -------- SECUMOD_NMPR : (SECUMOD Offset: 0x0080) Normal Mode Protection Register -------- */
#define SECUMOD_NMPR_ALL  (0x00FF000Cu)
#define SECUMOD_NMPR_TST (0x1u << 2) /**< \brief (SECUMOD_NMPR) Test Pin Protection */
#define SECUMOD_NMPR_JTAG (0x1u << 3) /**< \brief (SECUMOD_NMPR) JTAG Pins Protection */
#define SECUMOD_NMPR_DET0 (0x1u << 16) /**< \brief (SECUMOD_NMPR) PIOBU Intrusion Detector Protection */
#define SECUMOD_NMPR_DET1 (0x1u << 17) /**< \brief (SECUMOD_NMPR) PIOBU Intrusion Detector Protection */
#define SECUMOD_NMPR_DET2 (0x1u << 18) /**< \brief (SECUMOD_NMPR) PIOBU Intrusion Detector Protection */
#define SECUMOD_NMPR_DET3 (0x1u << 19) /**< \brief (SECUMOD_NMPR) PIOBU Intrusion Detector Protection */
#define SECUMOD_NMPR_DET4 (0x1u << 20) /**< \brief (SECUMOD_NMPR) PIOBU Intrusion Detector Protection */
#define SECUMOD_NMPR_DET5 (0x1u << 21) /**< \brief (SECUMOD_NMPR) PIOBU Intrusion Detector Protection */
#define SECUMOD_NMPR_DET6 (0x1u << 22) /**< \brief (SECUMOD_NMPR) PIOBU Intrusion Detector Protection */
#define SECUMOD_NMPR_DET7 (0x1u << 23) /**< \brief (SECUMOD_NMPR) PIOBU Intrusion Detector Protection */
/* -------- SECUMOD_NIEPR : (SECUMOD Offset: 0x0084) Normal Interrupt Enable Protection Register -------- */
#define SECUMOD_NIEPR_ALL  (0x00FF000Cu)
#define SECUMOD_NIEPR_TST (0x1u << 2) /**< \brief (SECUMOD_NIEPR) Test Pin Protection Interrupt Enable */
#define SECUMOD_NIEPR_JTAG (0x1u << 3) /**< \brief (SECUMOD_NIEPR) JTAG Pins Protection Interrupt Enable */
#define SECUMOD_NIEPR_DET0 (0x1u << 16) /**< \brief (SECUMOD_NIEPR) PIOBU Intrusion Detector Protection Interrupt Enable */
#define SECUMOD_NIEPR_DET1 (0x1u << 17) /**< \brief (SECUMOD_NIEPR) PIOBU Intrusion Detector Protection Interrupt Enable */
#define SECUMOD_NIEPR_DET2 (0x1u << 18) /**< \brief (SECUMOD_NIEPR) PIOBU Intrusion Detector Protection Interrupt Enable */
#define SECUMOD_NIEPR_DET3 (0x1u << 19) /**< \brief (SECUMOD_NIEPR) PIOBU Intrusion Detector Protection Interrupt Enable */
#define SECUMOD_NIEPR_DET4 (0x1u << 20) /**< \brief (SECUMOD_NIEPR) PIOBU Intrusion Detector Protection Interrupt Enable */
#define SECUMOD_NIEPR_DET5 (0x1u << 21) /**< \brief (SECUMOD_NIEPR) PIOBU Intrusion Detector Protection Interrupt Enable */
#define SECUMOD_NIEPR_DET6 (0x1u << 22) /**< \brief (SECUMOD_NIEPR) PIOBU Intrusion Detector Protection Interrupt Enable */
#define SECUMOD_NIEPR_DET7 (0x1u << 23) /**< \brief (SECUMOD_NIEPR) PIOBU Intrusion Detector Protection Interrupt Enable */
/* -------- SECUMOD_NIDPR : (SECUMOD Offset: 0x0088) Normal Interrupt Disable Protection Register -------- */
#define SECUMOD_NIDPR_ALL  (0x00FF000Cu)
#define SECUMOD_NIDPR_TST (0x1u << 2) /**< \brief (SECUMOD_NIDPR) Test Pin Protection Interrupt Disable */
#define SECUMOD_NIDPR_JTAG (0x1u << 3) /**< \brief (SECUMOD_NIDPR) JTAG Pins Protection Interrupt Disable */
#define SECUMOD_NIDPR_DET0 (0x1u << 16) /**< \brief (SECUMOD_NIDPR) PIOBU Intrusion Detector Protection Interrupt Disable */
#define SECUMOD_NIDPR_DET1 (0x1u << 17) /**< \brief (SECUMOD_NIDPR) PIOBU Intrusion Detector Protection Interrupt Disable */
#define SECUMOD_NIDPR_DET2 (0x1u << 18) /**< \brief (SECUMOD_NIDPR) PIOBU Intrusion Detector Protection Interrupt Disable */
#define SECUMOD_NIDPR_DET3 (0x1u << 19) /**< \brief (SECUMOD_NIDPR) PIOBU Intrusion Detector Protection Interrupt Disable */
#define SECUMOD_NIDPR_DET4 (0x1u << 20) /**< \brief (SECUMOD_NIDPR) PIOBU Intrusion Detector Protection Interrupt Disable */
#define SECUMOD_NIDPR_DET5 (0x1u << 21) /**< \brief (SECUMOD_NIDPR) PIOBU Intrusion Detector Protection Interrupt Disable */
#define SECUMOD_NIDPR_DET6 (0x1u << 22) /**< \brief (SECUMOD_NIDPR) PIOBU Intrusion Detector Protection Interrupt Disable */
#define SECUMOD_NIDPR_DET7 (0x1u << 23) /**< \brief (SECUMOD_NIDPR) PIOBU Intrusion Detector Protection Interrupt Disable */
/* -------- SECUMOD_NIMPR : (SECUMOD Offset: 0x008C) Normal Interrupt Mask Protection Register -------- */
#define SECUMOD_NIMPR_ALL  (0x00FF000Cu)
#define SECUMOD_NIMPR_TST (0x1u << 2) /**< \brief (SECUMOD_NIMPR) Test Pin Protection Interrupt Mask */
#define SECUMOD_NIMPR_JTAG (0x1u << 3) /**< \brief (SECUMOD_NIMPR) JTAG Pins Protection Interrupt Mask */
#define SECUMOD_NIMPR_DET0 (0x1u << 16) /**< \brief (SECUMOD_NIMPR) PIOBU Intrusion Detector Protection Interrupt Mask */
#define SECUMOD_NIMPR_DET1 (0x1u << 17) /**< \brief (SECUMOD_NIMPR) PIOBU Intrusion Detector Protection Interrupt Mask */
#define SECUMOD_NIMPR_DET2 (0x1u << 18) /**< \brief (SECUMOD_NIMPR) PIOBU Intrusion Detector Protection Interrupt Mask */
#define SECUMOD_NIMPR_DET3 (0x1u << 19) /**< \brief (SECUMOD_NIMPR) PIOBU Intrusion Detector Protection Interrupt Mask */
#define SECUMOD_NIMPR_DET4 (0x1u << 20) /**< \brief (SECUMOD_NIMPR) PIOBU Intrusion Detector Protection Interrupt Mask */
#define SECUMOD_NIMPR_DET5 (0x1u << 21) /**< \brief (SECUMOD_NIMPR) PIOBU Intrusion Detector Protection Interrupt Mask */
#define SECUMOD_NIMPR_DET6 (0x1u << 22) /**< \brief (SECUMOD_NIMPR) PIOBU Intrusion Detector Protection Interrupt Mask */
#define SECUMOD_NIMPR_DET7 (0x1u << 23) /**< \brief (SECUMOD_NIMPR) PIOBU Intrusion Detector Protection Interrupt Mask */
/* -------- SECUMOD_WKPR : (SECUMOD Offset: 0x0090) Wake Up Protection Register -------- */
#define SECUMOD_WKPR_ALL (0x00FF0004u)
#define SECUMOD_WKPR_TST (0x1u << 2) /**< \brief (SECUMOD_WKPR) Test Pin Protection */
#define SECUMOD_WKPR_DET0 (0x1u << 16) /**< \brief (SECUMOD_WKPR) PIOBU Intrusion Detector Protection */
#define SECUMOD_WKPR_DET1 (0x1u << 17) /**< \brief (SECUMOD_WKPR) PIOBU Intrusion Detector Protection */
#define SECUMOD_WKPR_DET2 (0x1u << 18) /**< \brief (SECUMOD_WKPR) PIOBU Intrusion Detector Protection */
#define SECUMOD_WKPR_DET3 (0x1u << 19) /**< \brief (SECUMOD_WKPR) PIOBU Intrusion Detector Protection */
#define SECUMOD_WKPR_DET4 (0x1u << 20) /**< \brief (SECUMOD_WKPR) PIOBU Intrusion Detector Protection */
#define SECUMOD_WKPR_DET5 (0x1u << 21) /**< \brief (SECUMOD_WKPR) PIOBU Intrusion Detector Protection */
#define SECUMOD_WKPR_DET6 (0x1u << 22) /**< \brief (SECUMOD_WKPR) PIOBU Intrusion Detector Protection */
#define SECUMOD_WKPR_DET7 (0x1u << 23) /**< \brief (SECUMOD_WKPR) PIOBU Intrusion Detector Protection */

/*@}*/

#endif /* _SAMA5D4_SECUMOD_COMPONENT_ */
