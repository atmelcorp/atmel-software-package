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

#ifndef _SAMA5D2_MATRIX_COMPONENT_
#define _SAMA5D2_MATRIX_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR AHB Bus Matrix */
/* ============================================================================= */
/** \addtogroup SAMA5D2_MATRIX AHB Bus Matrix */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief MatrixPr hardware registers */
typedef struct {
	__IO uint32_t MATRIX_PRAS; /**< \brief (MatrixPr Offset: 0x0) Priority Register A for Slave 0 */
	__IO uint32_t MATRIX_PRBS; /**< \brief (MatrixPr Offset: 0x4) Priority Register B for Slave 0 */
} MatrixPr;
/** \brief Matrix hardware registers */
typedef struct {
	__IO uint32_t MATRIX_MCFG[12];  /**< \brief (Matrix Offset: 0x0000) Master Configuration Register */
	__I  uint32_t Reserved1[4];
	__IO uint32_t MATRIX_SCFG[15];  /**< \brief (Matrix Offset: 0x0040) Slave Configuration Register */
	__I  uint32_t Reserved2[1];
	     MatrixPr MATRIX_PR[15];    /**< \brief (Matrix Offset: 0x0080) 0 .. 14 */
	__I  uint32_t Reserved3[22];
	__O  uint32_t MATRIX_MEIER;     /**< \brief (Matrix Offset: 0x0150) Master Error Interrupt Enable Register */
	__O  uint32_t MATRIX_MEIDR;     /**< \brief (Matrix Offset: 0x0154) Master Error Interrupt Disable Register */
	__I  uint32_t MATRIX_MEIMR;     /**< \brief (Matrix Offset: 0x0158) Master Error Interrupt Mask Register */
	__I  uint32_t MATRIX_MESR;      /**< \brief (Matrix Offset: 0x015C) Master Error Status Register */
	__I  uint32_t MATRIX_MEAR[12];  /**< \brief (Matrix Offset: 0x0160) Master 0 Error Address Register */
	__I  uint32_t Reserved4[21];
	__IO uint32_t MATRIX_WPMR;      /**< \brief (Matrix Offset: 0x01E4) Write Protection Mode Register */
	__I  uint32_t MATRIX_WPSR;      /**< \brief (Matrix Offset: 0x01E8) Write Protection Status Register */
	__I  uint32_t Reserved5[5];
	__IO uint32_t MATRIX_SSR[15];   /**< \brief (Matrix Offset: 0x0200) Security Slave x Register */
	__I  uint32_t Reserved6[1];
	__IO uint32_t MATRIX_SASSR[15]; /**< \brief (Matrix Offset: 0x0240) Security Areas Split Slave x Register */
	__I  uint32_t Reserved7[1];
	__IO uint32_t MATRIX_SRTSR[15]; /**< \brief (Matrix Offset: 0x0284) Security Region Top Slave x Register */
	__I  uint32_t Reserved8[1];
	__IO uint32_t MATRIX_SPSELR[3]; /**< \brief (Matrix Offset: 0x02C0) Security Peripheral Select x Register */
} Matrix;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- MATRIX_MCFG[12] : (MATRIX Offset: 0x0000) Master Configuration Register -------- */
#define MATRIX_MCFG_ULBT_Pos 0
#define MATRIX_MCFG_ULBT_Msk (0x7u << MATRIX_MCFG_ULBT_Pos) /**< \brief (MATRIX_MCFG[12]) Undefined Length Burst Type */
#define MATRIX_MCFG_ULBT(value) ((MATRIX_MCFG_ULBT_Msk & ((value) << MATRIX_MCFG_ULBT_Pos)))
#define   MATRIX_MCFG_ULBT_UNLIMITED (0x0u << 0) /**< \brief (MATRIX_MCFG[12]) Unlimited Length Burst-No predicted end of burst is generated, therefore INCR bursts coming from this master can only be broken if the Slave Slot Cycle Limit is reached. If the Slot Cycle Limit is not reached, the burst is normally completed by the master, at the latest, on the next AHB 1 Kbyte address boundary, allowing up to 256-beat word bursts or 128-beat double-word bursts.This value should not be used in the very particular case of a master capable of performing back-to-back undefined length bursts on a single slave, since this could indefinitely freeze the slave arbitration and thus prevent another master from accessing this slave. */
#define   MATRIX_MCFG_ULBT_SINGLE (0x1u << 0) /**< \brief (MATRIX_MCFG[12]) Single Access-The undefined length burst is treated as a succession of single accesses, allowing re-arbitration at each beat of the INCR burst or bursts sequence. */
#define   MATRIX_MCFG_ULBT_4_BEAT (0x2u << 0) /**< \brief (MATRIX_MCFG[12]) 4-beat Burst-The undefined length burst or bursts sequence is split into 4-beat bursts or less, allowing re-arbitration every 4 beats. */
#define   MATRIX_MCFG_ULBT_8_BEAT (0x3u << 0) /**< \brief (MATRIX_MCFG[12]) 8-beat Burst-The undefined length burst or bursts sequence is split into 8-beat bursts or less, allowing re-arbitration every 8 beats. */
#define   MATRIX_MCFG_ULBT_16_BEAT (0x4u << 0) /**< \brief (MATRIX_MCFG[12]) 16-beat Burst-The undefined length burst or bursts sequence is split into 16-beat bursts or less, allowing re-arbitration every 16 beats. */
#define   MATRIX_MCFG_ULBT_32_BEAT (0x5u << 0) /**< \brief (MATRIX_MCFG[12]) 32-beat Burst-The undefined length burst or bursts sequence is split into 32-beat bursts or less, allowing re-arbitration every 32 beats. */
#define   MATRIX_MCFG_ULBT_64_BEAT (0x6u << 0) /**< \brief (MATRIX_MCFG[12]) 64-beat Burst-The undefined length burst or bursts sequence is split into 64-beat bursts or less, allowing re-arbitration every 64 beats. */
#define   MATRIX_MCFG_ULBT_128_BEAT (0x7u << 0) /**< \brief (MATRIX_MCFG[12]) 128-beat Burst-The undefined length burst or bursts sequence is split into 128-beat bursts or less, allowing re-arbitration every 128 beats.Unless duly needed, the ULBT should be left at its default 0 value for power saving. */
/* -------- MATRIX_SCFG[15] : (MATRIX Offset: 0x0040) Slave Configuration Register -------- */
#define MATRIX_SCFG_SLOT_CYCLE_Pos 0
#define MATRIX_SCFG_SLOT_CYCLE_Msk (0x1ffu << MATRIX_SCFG_SLOT_CYCLE_Pos) /**< \brief (MATRIX_SCFG[15]) Maximum Bus Grant Duration for Masters */
#define MATRIX_SCFG_SLOT_CYCLE(value) ((MATRIX_SCFG_SLOT_CYCLE_Msk & ((value) << MATRIX_SCFG_SLOT_CYCLE_Pos)))
#define MATRIX_SCFG_DEFMSTR_TYPE_Pos 16
#define MATRIX_SCFG_DEFMSTR_TYPE_Msk (0x3u << MATRIX_SCFG_DEFMSTR_TYPE_Pos) /**< \brief (MATRIX_SCFG[15]) Default Master Type */
#define MATRIX_SCFG_DEFMSTR_TYPE(value) ((MATRIX_SCFG_DEFMSTR_TYPE_Msk & ((value) << MATRIX_SCFG_DEFMSTR_TYPE_Pos)))
#define   MATRIX_SCFG_DEFMSTR_TYPE_NONE (0x0u << 16) /**< \brief (MATRIX_SCFG[15]) No Default Master-At the end of the current slave access, if no other master request is pending, the slave is disconnected from all masters.This results in a one clock cycle latency for the first access of a burst transfer or for a single access. */
#define   MATRIX_SCFG_DEFMSTR_TYPE_LAST (0x1u << 16) /**< \brief (MATRIX_SCFG[15]) Last Default Master-At the end of the current slave access, if no other master request is pending, the slave stays connected to the last master having accessed it.This results in not having one clock cycle latency when the last master tries to access the slave again. */
#define   MATRIX_SCFG_DEFMSTR_TYPE_FIXED (0x2u << 16) /**< \brief (MATRIX_SCFG[15]) Fixed Default Master-At the end of the current slave access, if no other master request is pending, the slave connects to the fixed master the number that has been written in the FIXED_DEFMSTR field.This results in not having one clock cycle latency when the fixed master tries to access the slave again. */
#define MATRIX_SCFG_FIXED_DEFMSTR_Pos 18
#define MATRIX_SCFG_FIXED_DEFMSTR_Msk (0xfu << MATRIX_SCFG_FIXED_DEFMSTR_Pos) /**< \brief (MATRIX_SCFG[15]) Fixed Default Master */
#define MATRIX_SCFG_FIXED_DEFMSTR(value) ((MATRIX_SCFG_FIXED_DEFMSTR_Msk & ((value) << MATRIX_SCFG_FIXED_DEFMSTR_Pos)))
/* -------- MATRIX_PRAS : (MATRIX Offset: N/A) Priority Register A for Slave 0 -------- */
#define MATRIX_PRAS_M0PR_Pos 0
#define MATRIX_PRAS_M0PR_Msk (0x3u << MATRIX_PRAS_M0PR_Pos) /**< \brief (MATRIX_PRAS) Master 0 Priority */
#define MATRIX_PRAS_M0PR(value) ((MATRIX_PRAS_M0PR_Msk & ((value) << MATRIX_PRAS_M0PR_Pos)))
#define MATRIX_PRAS_M1PR_Pos 4
#define MATRIX_PRAS_M1PR_Msk (0x3u << MATRIX_PRAS_M1PR_Pos) /**< \brief (MATRIX_PRAS) Master 1 Priority */
#define MATRIX_PRAS_M1PR(value) ((MATRIX_PRAS_M1PR_Msk & ((value) << MATRIX_PRAS_M1PR_Pos)))
#define MATRIX_PRAS_M2PR_Pos 8
#define MATRIX_PRAS_M2PR_Msk (0x3u << MATRIX_PRAS_M2PR_Pos) /**< \brief (MATRIX_PRAS) Master 2 Priority */
#define MATRIX_PRAS_M2PR(value) ((MATRIX_PRAS_M2PR_Msk & ((value) << MATRIX_PRAS_M2PR_Pos)))
#define MATRIX_PRAS_M3PR_Pos 12
#define MATRIX_PRAS_M3PR_Msk (0x3u << MATRIX_PRAS_M3PR_Pos) /**< \brief (MATRIX_PRAS) Master 3 Priority */
#define MATRIX_PRAS_M3PR(value) ((MATRIX_PRAS_M3PR_Msk & ((value) << MATRIX_PRAS_M3PR_Pos)))
#define MATRIX_PRAS_M4PR_Pos 16
#define MATRIX_PRAS_M4PR_Msk (0x3u << MATRIX_PRAS_M4PR_Pos) /**< \brief (MATRIX_PRAS) Master 4 Priority */
#define MATRIX_PRAS_M4PR(value) ((MATRIX_PRAS_M4PR_Msk & ((value) << MATRIX_PRAS_M4PR_Pos)))
#define MATRIX_PRAS_M5PR_Pos 20
#define MATRIX_PRAS_M5PR_Msk (0x3u << MATRIX_PRAS_M5PR_Pos) /**< \brief (MATRIX_PRAS) Master 5 Priority */
#define MATRIX_PRAS_M5PR(value) ((MATRIX_PRAS_M5PR_Msk & ((value) << MATRIX_PRAS_M5PR_Pos)))
#define MATRIX_PRAS_M6PR_Pos 24
#define MATRIX_PRAS_M6PR_Msk (0x3u << MATRIX_PRAS_M6PR_Pos) /**< \brief (MATRIX_PRAS) Master 6 Priority */
#define MATRIX_PRAS_M6PR(value) ((MATRIX_PRAS_M6PR_Msk & ((value) << MATRIX_PRAS_M6PR_Pos)))
#define MATRIX_PRAS_M7PR_Pos 28
#define MATRIX_PRAS_M7PR_Msk (0x3u << MATRIX_PRAS_M7PR_Pos) /**< \brief (MATRIX_PRAS) Master 7 Priority */
#define MATRIX_PRAS_M7PR(value) ((MATRIX_PRAS_M7PR_Msk & ((value) << MATRIX_PRAS_M7PR_Pos)))
/* -------- MATRIX_PRBS : (MATRIX Offset: N/A) Priority Register B for Slave 0 -------- */
#define MATRIX_PRBS_M8PR_Pos 0
#define MATRIX_PRBS_M8PR_Msk (0x3u << MATRIX_PRBS_M8PR_Pos) /**< \brief (MATRIX_PRBS) Master 8 Priority */
#define MATRIX_PRBS_M8PR(value) ((MATRIX_PRBS_M8PR_Msk & ((value) << MATRIX_PRBS_M8PR_Pos)))
#define MATRIX_PRBS_M9PR_Pos 4
#define MATRIX_PRBS_M9PR_Msk (0x3u << MATRIX_PRBS_M9PR_Pos) /**< \brief (MATRIX_PRBS) Master 9 Priority */
#define MATRIX_PRBS_M9PR(value) ((MATRIX_PRBS_M9PR_Msk & ((value) << MATRIX_PRBS_M9PR_Pos)))
#define MATRIX_PRBS_M10PR_Pos 8
#define MATRIX_PRBS_M10PR_Msk (0x3u << MATRIX_PRBS_M10PR_Pos) /**< \brief (MATRIX_PRBS) Master 10 Priority */
#define MATRIX_PRBS_M10PR(value) ((MATRIX_PRBS_M10PR_Msk & ((value) << MATRIX_PRBS_M10PR_Pos)))
#define MATRIX_PRBS_M11PR_Pos 12
#define MATRIX_PRBS_M11PR_Msk (0x3u << MATRIX_PRBS_M11PR_Pos) /**< \brief (MATRIX_PRBS) Master 11 Priority */
#define MATRIX_PRBS_M11PR(value) ((MATRIX_PRBS_M11PR_Msk & ((value) << MATRIX_PRBS_M11PR_Pos)))
/* -------- MATRIX_MEIER : (MATRIX Offset: 0x0150) Master Error Interrupt Enable Register -------- */
#define MATRIX_MEIER_MERR0 (0x1u << 0) /**< \brief (MATRIX_MEIER) Master 0 Access Error */
#define MATRIX_MEIER_MERR1 (0x1u << 1) /**< \brief (MATRIX_MEIER) Master 1 Access Error */
#define MATRIX_MEIER_MERR2 (0x1u << 2) /**< \brief (MATRIX_MEIER) Master 2 Access Error */
#define MATRIX_MEIER_MERR3 (0x1u << 3) /**< \brief (MATRIX_MEIER) Master 3 Access Error */
#define MATRIX_MEIER_MERR4 (0x1u << 4) /**< \brief (MATRIX_MEIER) Master 4 Access Error */
#define MATRIX_MEIER_MERR5 (0x1u << 5) /**< \brief (MATRIX_MEIER) Master 5 Access Error */
#define MATRIX_MEIER_MERR6 (0x1u << 6) /**< \brief (MATRIX_MEIER) Master 6 Access Error */
#define MATRIX_MEIER_MERR7 (0x1u << 7) /**< \brief (MATRIX_MEIER) Master 7 Access Error */
#define MATRIX_MEIER_MERR8 (0x1u << 8) /**< \brief (MATRIX_MEIER) Master 8 Access Error */
#define MATRIX_MEIER_MERR9 (0x1u << 9) /**< \brief (MATRIX_MEIER) Master 9 Access Error */
#define MATRIX_MEIER_MERR10 (0x1u << 10) /**< \brief (MATRIX_MEIER) Master 10 Access Error */
#define MATRIX_MEIER_MERR11 (0x1u << 11) /**< \brief (MATRIX_MEIER) Master 11 Access Error */
/* -------- MATRIX_MEIDR : (MATRIX Offset: 0x0154) Master Error Interrupt Disable Register -------- */
#define MATRIX_MEIDR_MERR0 (0x1u << 0) /**< \brief (MATRIX_MEIDR) Master 0 Access Error */
#define MATRIX_MEIDR_MERR1 (0x1u << 1) /**< \brief (MATRIX_MEIDR) Master 1 Access Error */
#define MATRIX_MEIDR_MERR2 (0x1u << 2) /**< \brief (MATRIX_MEIDR) Master 2 Access Error */
#define MATRIX_MEIDR_MERR3 (0x1u << 3) /**< \brief (MATRIX_MEIDR) Master 3 Access Error */
#define MATRIX_MEIDR_MERR4 (0x1u << 4) /**< \brief (MATRIX_MEIDR) Master 4 Access Error */
#define MATRIX_MEIDR_MERR5 (0x1u << 5) /**< \brief (MATRIX_MEIDR) Master 5 Access Error */
#define MATRIX_MEIDR_MERR6 (0x1u << 6) /**< \brief (MATRIX_MEIDR) Master 6 Access Error */
#define MATRIX_MEIDR_MERR7 (0x1u << 7) /**< \brief (MATRIX_MEIDR) Master 7 Access Error */
#define MATRIX_MEIDR_MERR8 (0x1u << 8) /**< \brief (MATRIX_MEIDR) Master 8 Access Error */
#define MATRIX_MEIDR_MERR9 (0x1u << 9) /**< \brief (MATRIX_MEIDR) Master 9 Access Error */
#define MATRIX_MEIDR_MERR10 (0x1u << 10) /**< \brief (MATRIX_MEIDR) Master 10 Access Error */
#define MATRIX_MEIDR_MERR11 (0x1u << 11) /**< \brief (MATRIX_MEIDR) Master 11 Access Error */
/* -------- MATRIX_MEIMR : (MATRIX Offset: 0x0158) Master Error Interrupt Mask Register -------- */
#define MATRIX_MEIMR_MERR0 (0x1u << 0) /**< \brief (MATRIX_MEIMR) Master 0 Access Error */
#define MATRIX_MEIMR_MERR1 (0x1u << 1) /**< \brief (MATRIX_MEIMR) Master 1 Access Error */
#define MATRIX_MEIMR_MERR2 (0x1u << 2) /**< \brief (MATRIX_MEIMR) Master 2 Access Error */
#define MATRIX_MEIMR_MERR3 (0x1u << 3) /**< \brief (MATRIX_MEIMR) Master 3 Access Error */
#define MATRIX_MEIMR_MERR4 (0x1u << 4) /**< \brief (MATRIX_MEIMR) Master 4 Access Error */
#define MATRIX_MEIMR_MERR5 (0x1u << 5) /**< \brief (MATRIX_MEIMR) Master 5 Access Error */
#define MATRIX_MEIMR_MERR6 (0x1u << 6) /**< \brief (MATRIX_MEIMR) Master 6 Access Error */
#define MATRIX_MEIMR_MERR7 (0x1u << 7) /**< \brief (MATRIX_MEIMR) Master 7 Access Error */
#define MATRIX_MEIMR_MERR8 (0x1u << 8) /**< \brief (MATRIX_MEIMR) Master 8 Access Error */
#define MATRIX_MEIMR_MERR9 (0x1u << 9) /**< \brief (MATRIX_MEIMR) Master 9 Access Error */
#define MATRIX_MEIMR_MERR10 (0x1u << 10) /**< \brief (MATRIX_MEIMR) Master 10 Access Error */
#define MATRIX_MEIMR_MERR11 (0x1u << 11) /**< \brief (MATRIX_MEIMR) Master 11 Access Error */
/* -------- MATRIX_MESR : (MATRIX Offset: 0x015C) Master Error Status Register -------- */
#define MATRIX_MESR_MERR0 (0x1u << 0) /**< \brief (MATRIX_MESR) Master 0 Access Error */
#define MATRIX_MESR_MERR1 (0x1u << 1) /**< \brief (MATRIX_MESR) Master 1 Access Error */
#define MATRIX_MESR_MERR2 (0x1u << 2) /**< \brief (MATRIX_MESR) Master 2 Access Error */
#define MATRIX_MESR_MERR3 (0x1u << 3) /**< \brief (MATRIX_MESR) Master 3 Access Error */
#define MATRIX_MESR_MERR4 (0x1u << 4) /**< \brief (MATRIX_MESR) Master 4 Access Error */
#define MATRIX_MESR_MERR5 (0x1u << 5) /**< \brief (MATRIX_MESR) Master 5 Access Error */
#define MATRIX_MESR_MERR6 (0x1u << 6) /**< \brief (MATRIX_MESR) Master 6 Access Error */
#define MATRIX_MESR_MERR7 (0x1u << 7) /**< \brief (MATRIX_MESR) Master 7 Access Error */
#define MATRIX_MESR_MERR8 (0x1u << 8) /**< \brief (MATRIX_MESR) Master 8 Access Error */
#define MATRIX_MESR_MERR9 (0x1u << 9) /**< \brief (MATRIX_MESR) Master 9 Access Error */
#define MATRIX_MESR_MERR10 (0x1u << 10) /**< \brief (MATRIX_MESR) Master 10 Access Error */
#define MATRIX_MESR_MERR11 (0x1u << 11) /**< \brief (MATRIX_MESR) Master 11 Access Error */
/* -------- MATRIX_MEAR[12] : (MATRIX Offset: 0x0160) Master 0 Error Address Register -------- */
#define MATRIX_MEAR_ERRADD_Pos 0
#define MATRIX_MEAR_ERRADD_Msk (0xffffffffu << MATRIX_MEAR_ERRADD_Pos) /**< \brief (MATRIX_MEAR[12]) Master Error Address */
/* -------- MATRIX_WPMR : (MATRIX Offset: 0x01E4) Write Protection Mode Register -------- */
#define MATRIX_WPMR_WPEN (0x1u << 0) /**< \brief (MATRIX_WPMR) Write Protection Enable */
#define MATRIX_WPMR_WPKEY_Pos 8
#define MATRIX_WPMR_WPKEY_Msk (0xffffffu << MATRIX_WPMR_WPKEY_Pos) /**< \brief (MATRIX_WPMR) Write Protection Key (Write-only) */
#define MATRIX_WPMR_WPKEY(value) ((MATRIX_WPMR_WPKEY_Msk & ((value) << MATRIX_WPMR_WPKEY_Pos)))
#define   MATRIX_WPMR_WPKEY_PASSWD (0x4D4154u << 8) /**< \brief (MATRIX_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit.Always reads as 0. */
/* -------- MATRIX_WPSR : (MATRIX Offset: 0x01E8) Write Protection Status Register -------- */
#define MATRIX_WPSR_WPVS (0x1u << 0) /**< \brief (MATRIX_WPSR) Write Protection Violation Status */
#define MATRIX_WPSR_WPVSRC_Pos 8
#define MATRIX_WPSR_WPVSRC_Msk (0xffffu << MATRIX_WPSR_WPVSRC_Pos) /**< \brief (MATRIX_WPSR) Write Protection Violation Source */
/* -------- MATRIX_SSR[15] : (MATRIX Offset: 0x0200) Security Slave 0 Register -------- */
#define MATRIX_SSR_LANSECH0 (0x1u << 0) /**< \brief (MATRIX_SSR[15]) Low Area Non-secured in HSELx Security Region */
#define MATRIX_SSR_LANSECH1 (0x1u << 1) /**< \brief (MATRIX_SSR[15]) Low Area Non-secured in HSELx Security Region */
#define MATRIX_SSR_LANSECH2 (0x1u << 2) /**< \brief (MATRIX_SSR[15]) Low Area Non-secured in HSELx Security Region */
#define MATRIX_SSR_LANSECH3 (0x1u << 3) /**< \brief (MATRIX_SSR[15]) Low Area Non-secured in HSELx Security Region */
#define MATRIX_SSR_LANSECH4 (0x1u << 4) /**< \brief (MATRIX_SSR[15]) Low Area Non-secured in HSELx Security Region */
#define MATRIX_SSR_LANSECH5 (0x1u << 5) /**< \brief (MATRIX_SSR[15]) Low Area Non-secured in HSELx Security Region */
#define MATRIX_SSR_LANSECH6 (0x1u << 6) /**< \brief (MATRIX_SSR[15]) Low Area Non-secured in HSELx Security Region */
#define MATRIX_SSR_LANSECH7 (0x1u << 7) /**< \brief (MATRIX_SSR[15]) Low Area Non-secured in HSELx Security Region */
#define MATRIX_SSR_RDNSECH0 (0x1u << 8) /**< \brief (MATRIX_SSR[15]) Read Non-secured for HSELx Security Region */
#define MATRIX_SSR_RDNSECH1 (0x1u << 9) /**< \brief (MATRIX_SSR[15]) Read Non-secured for HSELx Security Region */
#define MATRIX_SSR_RDNSECH2 (0x1u << 10) /**< \brief (MATRIX_SSR[15]) Read Non-secured for HSELx Security Region */
#define MATRIX_SSR_RDNSECH3 (0x1u << 11) /**< \brief (MATRIX_SSR[15]) Read Non-secured for HSELx Security Region */
#define MATRIX_SSR_RDNSECH4 (0x1u << 12) /**< \brief (MATRIX_SSR[15]) Read Non-secured for HSELx Security Region */
#define MATRIX_SSR_RDNSECH5 (0x1u << 13) /**< \brief (MATRIX_SSR[15]) Read Non-secured for HSELx Security Region */
#define MATRIX_SSR_RDNSECH6 (0x1u << 14) /**< \brief (MATRIX_SSR[15]) Read Non-secured for HSELx Security Region */
#define MATRIX_SSR_RDNSECH7 (0x1u << 15) /**< \brief (MATRIX_SSR[15]) Read Non-secured for HSELx Security Region */
#define MATRIX_SSR_WRNSECH0 (0x1u << 16) /**< \brief (MATRIX_SSR[15]) Write Non-secured for HSELx Security Region */
#define MATRIX_SSR_WRNSECH1 (0x1u << 17) /**< \brief (MATRIX_SSR[15]) Write Non-secured for HSELx Security Region */
#define MATRIX_SSR_WRNSECH2 (0x1u << 18) /**< \brief (MATRIX_SSR[15]) Write Non-secured for HSELx Security Region */
#define MATRIX_SSR_WRNSECH3 (0x1u << 19) /**< \brief (MATRIX_SSR[15]) Write Non-secured for HSELx Security Region */
#define MATRIX_SSR_WRNSECH4 (0x1u << 20) /**< \brief (MATRIX_SSR[15]) Write Non-secured for HSELx Security Region */
#define MATRIX_SSR_WRNSECH5 (0x1u << 21) /**< \brief (MATRIX_SSR[15]) Write Non-secured for HSELx Security Region */
#define MATRIX_SSR_WRNSECH6 (0x1u << 22) /**< \brief (MATRIX_SSR[15]) Write Non-secured for HSELx Security Region */
#define MATRIX_SSR_WRNSECH7 (0x1u << 23) /**< \brief (MATRIX_SSR[15]) Write Non-secured for HSELx Security Region */
/* -------- MATRIX_SASSR[15] : (MATRIX Offset: 0x0240) Security Areas Split Slave 0 Register -------- */
#define MATRIX_SASSR_SASPLIT0_Pos 0
#define MATRIX_SASSR_SASPLIT0_Msk (0xfu << MATRIX_SASSR_SASPLIT0_Pos) /**< \brief (MATRIX_SASSR[15]) Security Areas Split for HSELx Security Region */
#define MATRIX_SASSR_SASPLIT0(value) ((MATRIX_SASSR_SASPLIT0_Msk & ((value) << MATRIX_SASSR_SASPLIT0_Pos)))
#define MATRIX_SASSR_SASPLIT1_Pos 4
#define MATRIX_SASSR_SASPLIT1_Msk (0xfu << MATRIX_SASSR_SASPLIT1_Pos) /**< \brief (MATRIX_SASSR[15]) Security Areas Split for HSELx Security Region */
#define MATRIX_SASSR_SASPLIT1(value) ((MATRIX_SASSR_SASPLIT1_Msk & ((value) << MATRIX_SASSR_SASPLIT1_Pos)))
#define MATRIX_SASSR_SASPLIT2_Pos 8
#define MATRIX_SASSR_SASPLIT2_Msk (0xfu << MATRIX_SASSR_SASPLIT2_Pos) /**< \brief (MATRIX_SASSR[15]) Security Areas Split for HSELx Security Region */
#define MATRIX_SASSR_SASPLIT2(value) ((MATRIX_SASSR_SASPLIT2_Msk & ((value) << MATRIX_SASSR_SASPLIT2_Pos)))
#define MATRIX_SASSR_SASPLIT3_Pos 12
#define MATRIX_SASSR_SASPLIT3_Msk (0xfu << MATRIX_SASSR_SASPLIT3_Pos) /**< \brief (MATRIX_SASSR[15]) Security Areas Split for HSELx Security Region */
#define MATRIX_SASSR_SASPLIT3(value) ((MATRIX_SASSR_SASPLIT3_Msk & ((value) << MATRIX_SASSR_SASPLIT3_Pos)))
#define MATRIX_SASSR_SASPLIT4_Pos 16
#define MATRIX_SASSR_SASPLIT4_Msk (0xfu << MATRIX_SASSR_SASPLIT4_Pos) /**< \brief (MATRIX_SASSR[15]) Security Areas Split for HSELx Security Region */
#define MATRIX_SASSR_SASPLIT4(value) ((MATRIX_SASSR_SASPLIT4_Msk & ((value) << MATRIX_SASSR_SASPLIT4_Pos)))
#define MATRIX_SASSR_SASPLIT5_Pos 20
#define MATRIX_SASSR_SASPLIT5_Msk (0xfu << MATRIX_SASSR_SASPLIT5_Pos) /**< \brief (MATRIX_SASSR[15]) Security Areas Split for HSELx Security Region */
#define MATRIX_SASSR_SASPLIT5(value) ((MATRIX_SASSR_SASPLIT5_Msk & ((value) << MATRIX_SASSR_SASPLIT5_Pos)))
#define MATRIX_SASSR_SASPLIT6_Pos 24
#define MATRIX_SASSR_SASPLIT6_Msk (0xfu << MATRIX_SASSR_SASPLIT6_Pos) /**< \brief (MATRIX_SASSR[15]) Security Areas Split for HSELx Security Region */
#define MATRIX_SASSR_SASPLIT6(value) ((MATRIX_SASSR_SASPLIT6_Msk & ((value) << MATRIX_SASSR_SASPLIT6_Pos)))
#define MATRIX_SASSR_SASPLIT7_Pos 28
#define MATRIX_SASSR_SASPLIT7_Msk (0xfu << MATRIX_SASSR_SASPLIT7_Pos) /**< \brief (MATRIX_SASSR[15]) Security Areas Split for HSELx Security Region */
#define MATRIX_SASSR_SASPLIT7(value) ((MATRIX_SASSR_SASPLIT7_Msk & ((value) << MATRIX_SASSR_SASPLIT7_Pos)))
/* -------- MATRIX_SRTSR[15] : (MATRIX Offset: 0x0284) Security Region Top Slave 1 Register -------- */
#define MATRIX_SRTSR_SRTOP0_Pos 0
#define MATRIX_SRTSR_SRTOP0_Msk (0xfu << MATRIX_SRTSR_SRTOP0_Pos) /**< \brief (MATRIX_SRTSR[15]) HSELx Security Region Top */
#define MATRIX_SRTSR_SRTOP0(value) ((MATRIX_SRTSR_SRTOP0_Msk & ((value) << MATRIX_SRTSR_SRTOP0_Pos)))
#define MATRIX_SRTSR_SRTOP1_Pos 4
#define MATRIX_SRTSR_SRTOP1_Msk (0xfu << MATRIX_SRTSR_SRTOP1_Pos) /**< \brief (MATRIX_SRTSR[15]) HSELx Security Region Top */
#define MATRIX_SRTSR_SRTOP1(value) ((MATRIX_SRTSR_SRTOP1_Msk & ((value) << MATRIX_SRTSR_SRTOP1_Pos)))
#define MATRIX_SRTSR_SRTOP2_Pos 8
#define MATRIX_SRTSR_SRTOP2_Msk (0xfu << MATRIX_SRTSR_SRTOP2_Pos) /**< \brief (MATRIX_SRTSR[15]) HSELx Security Region Top */
#define MATRIX_SRTSR_SRTOP2(value) ((MATRIX_SRTSR_SRTOP2_Msk & ((value) << MATRIX_SRTSR_SRTOP2_Pos)))
#define MATRIX_SRTSR_SRTOP3_Pos 12
#define MATRIX_SRTSR_SRTOP3_Msk (0xfu << MATRIX_SRTSR_SRTOP3_Pos) /**< \brief (MATRIX_SRTSR[15]) HSELx Security Region Top */
#define MATRIX_SRTSR_SRTOP3(value) ((MATRIX_SRTSR_SRTOP3_Msk & ((value) << MATRIX_SRTSR_SRTOP3_Pos)))
#define MATRIX_SRTSR_SRTOP4_Pos 16
#define MATRIX_SRTSR_SRTOP4_Msk (0xfu << MATRIX_SRTSR_SRTOP4_Pos) /**< \brief (MATRIX_SRTSR[15]) HSELx Security Region Top */
#define MATRIX_SRTSR_SRTOP4(value) ((MATRIX_SRTSR_SRTOP4_Msk & ((value) << MATRIX_SRTSR_SRTOP4_Pos)))
#define MATRIX_SRTSR_SRTOP5_Pos 20
#define MATRIX_SRTSR_SRTOP5_Msk (0xfu << MATRIX_SRTSR_SRTOP5_Pos) /**< \brief (MATRIX_SRTSR[15]) HSELx Security Region Top */
#define MATRIX_SRTSR_SRTOP5(value) ((MATRIX_SRTSR_SRTOP5_Msk & ((value) << MATRIX_SRTSR_SRTOP5_Pos)))
#define MATRIX_SRTSR_SRTOP6_Pos 24
#define MATRIX_SRTSR_SRTOP6_Msk (0xfu << MATRIX_SRTSR_SRTOP6_Pos) /**< \brief (MATRIX_SRTSR[15]) HSELx Security Region Top */
#define MATRIX_SRTSR_SRTOP6(value) ((MATRIX_SRTSR_SRTOP6_Msk & ((value) << MATRIX_SRTSR_SRTOP6_Pos)))
#define MATRIX_SRTSR_SRTOP7_Pos 28
#define MATRIX_SRTSR_SRTOP7_Msk (0xfu << MATRIX_SRTSR_SRTOP7_Pos) /**< \brief (MATRIX_SRTSR[15]) HSELx Security Region Top */
#define MATRIX_SRTSR_SRTOP7(value) ((MATRIX_SRTSR_SRTOP7_Msk & ((value) << MATRIX_SRTSR_SRTOP7_Pos)))
/* -------- MATRIX_SPSELR[3] : (MATRIX Offset: 0x02C0) Security Peripheral Select 1 Register -------- */
#define MATRIX_SPSELR_NSECP0 (0x1u << 0) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP1 (0x1u << 1) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP2 (0x1u << 2) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP3 (0x1u << 3) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP4 (0x1u << 4) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP5 (0x1u << 5) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP6 (0x1u << 6) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP7 (0x1u << 7) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP8 (0x1u << 8) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP9 (0x1u << 9) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP10 (0x1u << 10) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP11 (0x1u << 11) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP12 (0x1u << 12) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP13 (0x1u << 13) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP14 (0x1u << 14) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP15 (0x1u << 15) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP16 (0x1u << 16) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP17 (0x1u << 17) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP18 (0x1u << 18) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP19 (0x1u << 19) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP20 (0x1u << 20) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP21 (0x1u << 21) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP22 (0x1u << 22) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP23 (0x1u << 23) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP24 (0x1u << 24) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP25 (0x1u << 25) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP26 (0x1u << 26) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP27 (0x1u << 27) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP28 (0x1u << 28) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP29 (0x1u << 29) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP30 (0x1u << 30) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */
#define MATRIX_SPSELR_NSECP31 (0x1u << 31) /**< \brief (MATRIX_SPSELR[3]) Non-secured Peripheral */

/*@}*/

#endif /* _SAMA5D2_MATRIX_COMPONENT_ */
