/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2014, Atmel Corporation                                        */
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

#ifndef _SAM9X_AIC_COMPONENT_
#define _SAM9X_AIC_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Advanced Interrupt Controller */
/* ============================================================================= */
/** \addtogroup SAM9X_AIC Advanced Interrupt Controller */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Aic hardware registers */
typedef struct {
	__IO uint32_t AIC_SMR[32];  /**< \brief (Aic Offset: 0x00) Source Mode Register */
	__IO uint32_t AIC_SVR[32];  /**< \brief (Aic Offset: 0x80) Source Vector Register */
	__I  uint32_t AIC_IVR;      /**< \brief (Aic Offset: 0x100) Interrupt Vector Register */
	__I  uint32_t AIC_FVR;      /**< \brief (Aic Offset: 0x104) FIQ Interrupt Vector Register */
	__I  uint32_t AIC_ISR;      /**< \brief (Aic Offset: 0x108) Interrupt Status Register */
	__I  uint32_t AIC_IPR;      /**< \brief (Aic Offset: 0x10C) Interrupt Pending Register */
	__I  uint32_t AIC_IMR;      /**< \brief (Aic Offset: 0x110) Interrupt Mask Register */
	__I  uint32_t AIC_CISR;     /**< \brief (Aic Offset: 0x114) Core Interrupt Status Register */
	__I  uint32_t Reserved1[2];
	__O  uint32_t AIC_IECR;     /**< \brief (Aic Offset: 0x120) Interrupt Enable Command Register */
	__O  uint32_t AIC_IDCR;     /**< \brief (Aic Offset: 0x124) Interrupt Disable Command Register */
	__O  uint32_t AIC_ICCR;     /**< \brief (Aic Offset: 0x128) Interrupt Clear Command Register */
	__O  uint32_t AIC_ISCR;     /**< \brief (Aic Offset: 0x12C) Interrupt Set Command Register */
	__O  uint32_t AIC_EOICR;    /**< \brief (Aic Offset: 0x130) End of Interrupt Command Register */
	__IO uint32_t AIC_SPU;      /**< \brief (Aic Offset: 0x134) Spurious Interrupt Vector Register */
	__IO uint32_t AIC_DCR;      /**< \brief (Aic Offset: 0x138) Debug Control Register */
	__I  uint32_t Reserved2[1];
	__O  uint32_t AIC_FFER;     /**< \brief (Aic Offset: 0x140) Fast Forcing Enable Register */
	__O  uint32_t AIC_FFDR;     /**< \brief (Aic Offset: 0x144) Fast Forcing Disable Register */
	__I  uint32_t AIC_FFSR;     /**< \brief (Aic Offset: 0x148) Fast Forcing Status Register */
	__I  uint32_t Reserved3[38];
	__IO uint32_t AIC_WPMR;     /**< \brief (Aic Offset: 0x1E4) Write Protection Mode Register */
	__I  uint32_t AIC_WPSR;     /**< \brief (Aic Offset: 0x1E8) Write Protection Status Register */
} Aic;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- AIC_SMR[32] : (AIC Offset: 0x00) Source Mode Register -------- */
#define AIC_SMR_PRIOR_Pos 0
#define AIC_SMR_PRIOR_Msk (0x7u << AIC_SMR_PRIOR_Pos) /**< \brief (AIC_SMR[32]) Priority Level */
#define AIC_SMR_PRIOR(value) ((AIC_SMR_PRIOR_Msk & ((value) << AIC_SMR_PRIOR_Pos)))
#define AIC_SMR_SRCTYPE_Pos 5
#define AIC_SMR_SRCTYPE_Msk (0x3u << AIC_SMR_SRCTYPE_Pos) /**< \brief (AIC_SMR[32]) Interrupt Source Type */
#define AIC_SMR_SRCTYPE(value) ((AIC_SMR_SRCTYPE_Msk & ((value) << AIC_SMR_SRCTYPE_Pos)))
#define   AIC_SMR_SRCTYPE_INT_LEVEL_SENSITIVE (0x0u << 5) /**< \brief (AIC_SMR[32]) High level Sensitive for internal sourceLow level Sensitive for external source */
#define   AIC_SMR_SRCTYPE_INT_EDGE_TRIGGERED (0x1u << 5) /**< \brief (AIC_SMR[32]) Positive edge triggered for internal sourceNegative edge triggered for external source */
#define   AIC_SMR_SRCTYPE_EXT_HIGH_LEVEL (0x2u << 5) /**< \brief (AIC_SMR[32]) High level Sensitive for internal sourceHigh level Sensitive for external source */
#define   AIC_SMR_SRCTYPE_EXT_POSITIVE_EDGE (0x3u << 5) /**< \brief (AIC_SMR[32]) Positive edge triggered for internal sourcePositive edge triggered for external source */
/* -------- AIC_SVR[32] : (AIC Offset: 0x80) Source Vector Register -------- */
#define AIC_SVR_VECTOR_Pos 0
#define AIC_SVR_VECTOR_Msk (0xffffffffu << AIC_SVR_VECTOR_Pos) /**< \brief (AIC_SVR[32]) Source Vector */
#define AIC_SVR_VECTOR(value) ((AIC_SVR_VECTOR_Msk & ((value) << AIC_SVR_VECTOR_Pos)))
/* -------- AIC_IVR : (AIC Offset: 0x100) Interrupt Vector Register -------- */
#define AIC_IVR_IRQV_Pos 0
#define AIC_IVR_IRQV_Msk (0xffffffffu << AIC_IVR_IRQV_Pos) /**< \brief (AIC_IVR) Interrupt Vector Register */
/* -------- AIC_FVR : (AIC Offset: 0x104) FIQ Interrupt Vector Register -------- */
#define AIC_FVR_FIQV_Pos 0
#define AIC_FVR_FIQV_Msk (0xffffffffu << AIC_FVR_FIQV_Pos) /**< \brief (AIC_FVR) FIQ Vector Register */
/* -------- AIC_ISR : (AIC Offset: 0x108) Interrupt Status Register -------- */
#define AIC_ISR_IRQID_Pos 0
#define AIC_ISR_IRQID_Msk (0x1fu << AIC_ISR_IRQID_Pos) /**< \brief (AIC_ISR) Current Interrupt Identifier */
/* -------- AIC_IPR : (AIC Offset: 0x10C) Interrupt Pending Register -------- */
#define AIC_IPR_FIQ (0x1u << 0) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_SYS (0x1u << 1) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID2 (0x1u << 2) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID3 (0x1u << 3) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID4 (0x1u << 4) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID5 (0x1u << 5) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID6 (0x1u << 6) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID7 (0x1u << 7) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID8 (0x1u << 8) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID9 (0x1u << 9) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID10 (0x1u << 10) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID11 (0x1u << 11) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID12 (0x1u << 12) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID13 (0x1u << 13) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID14 (0x1u << 14) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID15 (0x1u << 15) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID16 (0x1u << 16) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID17 (0x1u << 17) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID18 (0x1u << 18) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID19 (0x1u << 19) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID20 (0x1u << 20) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID21 (0x1u << 21) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID22 (0x1u << 22) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID23 (0x1u << 23) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID24 (0x1u << 24) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID25 (0x1u << 25) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID26 (0x1u << 26) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID27 (0x1u << 27) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID28 (0x1u << 28) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID29 (0x1u << 29) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID30 (0x1u << 30) /**< \brief (AIC_IPR) Interrupt Pending */
#define AIC_IPR_PID31 (0x1u << 31) /**< \brief (AIC_IPR) Interrupt Pending */
/* -------- AIC_IMR : (AIC Offset: 0x110) Interrupt Mask Register -------- */
#define AIC_IMR_FIQ (0x1u << 0) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_SYS (0x1u << 1) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID2 (0x1u << 2) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID3 (0x1u << 3) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID4 (0x1u << 4) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID5 (0x1u << 5) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID6 (0x1u << 6) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID7 (0x1u << 7) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID8 (0x1u << 8) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID9 (0x1u << 9) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID10 (0x1u << 10) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID11 (0x1u << 11) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID12 (0x1u << 12) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID13 (0x1u << 13) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID14 (0x1u << 14) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID15 (0x1u << 15) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID16 (0x1u << 16) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID17 (0x1u << 17) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID18 (0x1u << 18) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID19 (0x1u << 19) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID20 (0x1u << 20) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID21 (0x1u << 21) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID22 (0x1u << 22) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID23 (0x1u << 23) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID24 (0x1u << 24) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID25 (0x1u << 25) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID26 (0x1u << 26) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID27 (0x1u << 27) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID28 (0x1u << 28) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID29 (0x1u << 29) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID30 (0x1u << 30) /**< \brief (AIC_IMR) Interrupt Mask */
#define AIC_IMR_PID31 (0x1u << 31) /**< \brief (AIC_IMR) Interrupt Mask */
/* -------- AIC_CISR : (AIC Offset: 0x114) Core Interrupt Status Register -------- */
#define AIC_CISR_NFIQ (0x1u << 0) /**< \brief (AIC_CISR) NFIQ Status */
#define AIC_CISR_NIRQ (0x1u << 1) /**< \brief (AIC_CISR) NIRQ Status */
/* -------- AIC_IECR : (AIC Offset: 0x120) Interrupt Enable Command Register -------- */
#define AIC_IECR_FIQ (0x1u << 0) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_SYS (0x1u << 1) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID2 (0x1u << 2) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID3 (0x1u << 3) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID4 (0x1u << 4) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID5 (0x1u << 5) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID6 (0x1u << 6) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID7 (0x1u << 7) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID8 (0x1u << 8) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID9 (0x1u << 9) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID10 (0x1u << 10) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID11 (0x1u << 11) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID12 (0x1u << 12) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID13 (0x1u << 13) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID14 (0x1u << 14) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID15 (0x1u << 15) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID16 (0x1u << 16) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID17 (0x1u << 17) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID18 (0x1u << 18) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID19 (0x1u << 19) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID20 (0x1u << 20) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID21 (0x1u << 21) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID22 (0x1u << 22) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID23 (0x1u << 23) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID24 (0x1u << 24) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID25 (0x1u << 25) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID26 (0x1u << 26) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID27 (0x1u << 27) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID28 (0x1u << 28) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID29 (0x1u << 29) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID30 (0x1u << 30) /**< \brief (AIC_IECR) Interrupt Enable */
#define AIC_IECR_PID31 (0x1u << 31) /**< \brief (AIC_IECR) Interrupt Enable */
/* -------- AIC_IDCR : (AIC Offset: 0x124) Interrupt Disable Command Register -------- */
#define AIC_IDCR_FIQ (0x1u << 0) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_SYS (0x1u << 1) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID2 (0x1u << 2) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID3 (0x1u << 3) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID4 (0x1u << 4) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID5 (0x1u << 5) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID6 (0x1u << 6) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID7 (0x1u << 7) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID8 (0x1u << 8) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID9 (0x1u << 9) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID10 (0x1u << 10) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID11 (0x1u << 11) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID12 (0x1u << 12) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID13 (0x1u << 13) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID14 (0x1u << 14) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID15 (0x1u << 15) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID16 (0x1u << 16) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID17 (0x1u << 17) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID18 (0x1u << 18) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID19 (0x1u << 19) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID20 (0x1u << 20) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID21 (0x1u << 21) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID22 (0x1u << 22) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID23 (0x1u << 23) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID24 (0x1u << 24) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID25 (0x1u << 25) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID26 (0x1u << 26) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID27 (0x1u << 27) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID28 (0x1u << 28) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID29 (0x1u << 29) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID30 (0x1u << 30) /**< \brief (AIC_IDCR) Interrupt Disable */
#define AIC_IDCR_PID31 (0x1u << 31) /**< \brief (AIC_IDCR) Interrupt Disable */
/* -------- AIC_ICCR : (AIC Offset: 0x128) Interrupt Clear Command Register -------- */
#define AIC_ICCR_FIQ (0x1u << 0) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_SYS (0x1u << 1) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID2 (0x1u << 2) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID3 (0x1u << 3) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID4 (0x1u << 4) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID5 (0x1u << 5) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID6 (0x1u << 6) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID7 (0x1u << 7) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID8 (0x1u << 8) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID9 (0x1u << 9) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID10 (0x1u << 10) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID11 (0x1u << 11) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID12 (0x1u << 12) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID13 (0x1u << 13) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID14 (0x1u << 14) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID15 (0x1u << 15) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID16 (0x1u << 16) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID17 (0x1u << 17) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID18 (0x1u << 18) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID19 (0x1u << 19) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID20 (0x1u << 20) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID21 (0x1u << 21) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID22 (0x1u << 22) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID23 (0x1u << 23) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID24 (0x1u << 24) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID25 (0x1u << 25) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID26 (0x1u << 26) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID27 (0x1u << 27) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID28 (0x1u << 28) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID29 (0x1u << 29) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID30 (0x1u << 30) /**< \brief (AIC_ICCR) Interrupt Clear */
#define AIC_ICCR_PID31 (0x1u << 31) /**< \brief (AIC_ICCR) Interrupt Clear */
/* -------- AIC_ISCR : (AIC Offset: 0x12C) Interrupt Set Command Register -------- */
#define AIC_ISCR_FIQ (0x1u << 0) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_SYS (0x1u << 1) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID2 (0x1u << 2) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID3 (0x1u << 3) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID4 (0x1u << 4) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID5 (0x1u << 5) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID6 (0x1u << 6) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID7 (0x1u << 7) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID8 (0x1u << 8) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID9 (0x1u << 9) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID10 (0x1u << 10) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID11 (0x1u << 11) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID12 (0x1u << 12) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID13 (0x1u << 13) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID14 (0x1u << 14) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID15 (0x1u << 15) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID16 (0x1u << 16) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID17 (0x1u << 17) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID18 (0x1u << 18) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID19 (0x1u << 19) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID20 (0x1u << 20) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID21 (0x1u << 21) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID22 (0x1u << 22) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID23 (0x1u << 23) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID24 (0x1u << 24) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID25 (0x1u << 25) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID26 (0x1u << 26) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID27 (0x1u << 27) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID28 (0x1u << 28) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID29 (0x1u << 29) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID30 (0x1u << 30) /**< \brief (AIC_ISCR) Interrupt Set */
#define AIC_ISCR_PID31 (0x1u << 31) /**< \brief (AIC_ISCR) Interrupt Set */
/* -------- AIC_EOICR : (AIC Offset: 0x130) End of Interrupt Command Register -------- */
#define AIC_EOICR_ENDIT (0x1u << 0) /**< \brief (AIC_EOICR) Interrupt Processing Complete Command */
/* -------- AIC_SPU : (AIC Offset: 0x134) Spurious Interrupt Vector Register -------- */
#define AIC_SPU_SIVR_Pos 0
#define AIC_SPU_SIVR_Msk (0xffffffffu << AIC_SPU_SIVR_Pos) /**< \brief (AIC_SPU) Spurious Interrupt Vector Register */
#define AIC_SPU_SIVR(value) ((AIC_SPU_SIVR_Msk & ((value) << AIC_SPU_SIVR_Pos)))
/* -------- AIC_DCR : (AIC Offset: 0x138) Debug Control Register -------- */
#define AIC_DCR_PROT (0x1u << 0) /**< \brief (AIC_DCR) Protection Mode */
#define AIC_DCR_GMSK (0x1u << 1) /**< \brief (AIC_DCR) General Interrupt Mask */
/* -------- AIC_FFER : (AIC Offset: 0x140) Fast Forcing Enable Register -------- */
#define AIC_FFER_SYS (0x1u << 1) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID2 (0x1u << 2) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID3 (0x1u << 3) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID4 (0x1u << 4) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID5 (0x1u << 5) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID6 (0x1u << 6) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID7 (0x1u << 7) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID8 (0x1u << 8) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID9 (0x1u << 9) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID10 (0x1u << 10) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID11 (0x1u << 11) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID12 (0x1u << 12) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID13 (0x1u << 13) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID14 (0x1u << 14) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID15 (0x1u << 15) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID16 (0x1u << 16) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID17 (0x1u << 17) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID18 (0x1u << 18) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID19 (0x1u << 19) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID20 (0x1u << 20) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID21 (0x1u << 21) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID22 (0x1u << 22) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID23 (0x1u << 23) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID24 (0x1u << 24) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID25 (0x1u << 25) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID26 (0x1u << 26) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID27 (0x1u << 27) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID28 (0x1u << 28) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID29 (0x1u << 29) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID30 (0x1u << 30) /**< \brief (AIC_FFER) Fast Forcing Enable */
#define AIC_FFER_PID31 (0x1u << 31) /**< \brief (AIC_FFER) Fast Forcing Enable */
/* -------- AIC_FFDR : (AIC Offset: 0x144) Fast Forcing Disable Register -------- */
#define AIC_FFDR_SYS (0x1u << 1) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID2 (0x1u << 2) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID3 (0x1u << 3) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID4 (0x1u << 4) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID5 (0x1u << 5) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID6 (0x1u << 6) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID7 (0x1u << 7) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID8 (0x1u << 8) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID9 (0x1u << 9) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID10 (0x1u << 10) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID11 (0x1u << 11) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID12 (0x1u << 12) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID13 (0x1u << 13) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID14 (0x1u << 14) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID15 (0x1u << 15) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID16 (0x1u << 16) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID17 (0x1u << 17) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID18 (0x1u << 18) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID19 (0x1u << 19) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID20 (0x1u << 20) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID21 (0x1u << 21) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID22 (0x1u << 22) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID23 (0x1u << 23) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID24 (0x1u << 24) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID25 (0x1u << 25) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID26 (0x1u << 26) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID27 (0x1u << 27) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID28 (0x1u << 28) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID29 (0x1u << 29) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID30 (0x1u << 30) /**< \brief (AIC_FFDR) Fast Forcing Disable */
#define AIC_FFDR_PID31 (0x1u << 31) /**< \brief (AIC_FFDR) Fast Forcing Disable */
/* -------- AIC_FFSR : (AIC Offset: 0x148) Fast Forcing Status Register -------- */
#define AIC_FFSR_SYS (0x1u << 1) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID2 (0x1u << 2) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID3 (0x1u << 3) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID4 (0x1u << 4) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID5 (0x1u << 5) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID6 (0x1u << 6) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID7 (0x1u << 7) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID8 (0x1u << 8) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID9 (0x1u << 9) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID10 (0x1u << 10) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID11 (0x1u << 11) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID12 (0x1u << 12) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID13 (0x1u << 13) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID14 (0x1u << 14) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID15 (0x1u << 15) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID16 (0x1u << 16) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID17 (0x1u << 17) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID18 (0x1u << 18) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID19 (0x1u << 19) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID20 (0x1u << 20) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID21 (0x1u << 21) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID22 (0x1u << 22) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID23 (0x1u << 23) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID24 (0x1u << 24) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID25 (0x1u << 25) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID26 (0x1u << 26) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID27 (0x1u << 27) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID28 (0x1u << 28) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID29 (0x1u << 29) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID30 (0x1u << 30) /**< \brief (AIC_FFSR) Fast Forcing Status */
#define AIC_FFSR_PID31 (0x1u << 31) /**< \brief (AIC_FFSR) Fast Forcing Status */
/* -------- AIC_WPMR : (AIC Offset: 0x1E4) Write Protection Mode Register -------- */
#define AIC_WPMR_WPEN (0x1u << 0) /**< \brief (AIC_WPMR) Write Protection Enable */
#define AIC_WPMR_WPKEY_Pos 8
#define AIC_WPMR_WPKEY_Msk (0xffffffu << AIC_WPMR_WPKEY_Pos) /**< \brief (AIC_WPMR) Write Protection Key */
#define AIC_WPMR_WPKEY(value) ((AIC_WPMR_WPKEY_Msk & ((value) << AIC_WPMR_WPKEY_Pos)))
#define   AIC_WPMR_WPKEY_PASSWD (0x414943u << 8) /**< \brief (AIC_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit.Always reads as 0. */
/* -------- AIC_WPSR : (AIC Offset: 0x1E8) Write Protection Status Register -------- */
#define AIC_WPSR_WPVS (0x1u << 0) /**< \brief (AIC_WPSR) Write Protection Violation Status */
#define AIC_WPSR_WPVSRC_Pos 8
#define AIC_WPSR_WPVSRC_Msk (0xffffu << AIC_WPSR_WPVSRC_Pos) /**< \brief (AIC_WPSR) Write Protection Violation Source */

/*@}*/

#endif /* _SAM9X_AIC_COMPONENT_ */
