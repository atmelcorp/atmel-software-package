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

#ifndef _SAM9X_PIT64B_COMPONENT_
#define _SAM9X_PIT64B_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Periodic Interval Timer 64-bit */
/* ============================================================================= */
/** \addtogroup SAM9X_PIT64B Periodic Interval Timer 64-bit */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Pit64b hardware registers */
typedef struct {
  __O  uint32_t PIT64B_CR;     /**< \brief (Pit64b Offset: 0x0) Control Register */
  __IO uint32_t PIT64B_MR;     /**< \brief (Pit64b Offset: 0x4) Mode Register */
  __IO uint32_t PIT64B_LSBPR;  /**< \brief (Pit64b Offset: 0x8) LSB Period Register */
  __IO uint32_t PIT64B_MSBPR;  /**< \brief (Pit64b Offset: 0xC) MSB Period Register */
  __O  uint32_t PIT64B_IER;    /**< \brief (Pit64b Offset: 0x10) Interrupt Enable Register */
  __O  uint32_t PIT64B_IDR;    /**< \brief (Pit64b Offset: 0x14) Interrupt Disable Register */
  __I  uint32_t PIT64B_IMR;    /**< \brief (Pit64b Offset: 0x18) Interrupt Mask Register */
  __I  uint32_t PIT64B_ISR;    /**< \brief (Pit64b Offset: 0x1C) Interrupt Status Register */
  __I  uint32_t PIT64B_TLSBR;  /**< \brief (Pit64b Offset: 0x20) Timer LSB Current Value Register */
  __I  uint32_t PIT64B_TMSBR;  /**< \brief (Pit64b Offset: 0x24) Timer MSB Current Value Register */
  __I  uint32_t Reserved1[47];
  __IO uint32_t PIT64B_WPMR;   /**< \brief (Pit64b Offset: 0xE4) Write Protection Mode Register */
  __I  uint32_t PIT64B_WPSR;   /**< \brief (Pit64b Offset: 0xE8) Write Protection Status Register */
} Pit64b;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- PIT64B_CR : (PIT64B Offset: 0x0) Control Register -------- */
#define PIT64B_CR_START (0x1u << 0) /**< \brief (PIT64B_CR) Start Timer */
#define PIT64B_CR_SWRST (0x1u << 8) /**< \brief (PIT64B_CR) Software Reset */
/* -------- PIT64B_MR : (PIT64B Offset: 0x4) Mode Register -------- */
#define PIT64B_MR_CONT (0x1u << 0) /**< \brief (PIT64B_MR) Continuous Mode */
#define PIT64B_MR_SGCLK (0x1u << 3) /**< \brief (PIT64B_MR) Generic Clock Selection Enable */
#define PIT64B_MR_SMOD (0x1u << 4) /**< \brief (PIT64B_MR) Start Mode */
#define PIT64B_MR_PRESCALER_Pos 8
#define PIT64B_MR_PRESCALER_Msk (0xfu << PIT64B_MR_PRESCALER_Pos) /**< \brief (PIT64B_MR) Prescaler Period */
#define PIT64B_MR_PRESCALER(value) ((PIT64B_MR_PRESCALER_Msk & ((value) << PIT64B_MR_PRESCALER_Pos)))
/* -------- PIT64B_LSBPR : (PIT64B Offset: 0x8) LSB Period Register -------- */
#define PIT64B_LSBPR_LSBPERIOD_Pos 0
#define PIT64B_LSBPR_LSBPERIOD_Msk (0xffffffffu << PIT64B_LSBPR_LSBPERIOD_Pos) /**< \brief (PIT64B_LSBPR) 32 LSB of the Timer Period */
#define PIT64B_LSBPR_LSBPERIOD(value) ((PIT64B_LSBPR_LSBPERIOD_Msk & ((value) << PIT64B_LSBPR_LSBPERIOD_Pos)))
/* -------- PIT64B_MSBPR : (PIT64B Offset: 0xC) MSB Period Register -------- */
#define PIT64B_MSBPR_MSBPERIOD_Pos 0
#define PIT64B_MSBPR_MSBPERIOD_Msk (0xffffffffu << PIT64B_MSBPR_MSBPERIOD_Pos) /**< \brief (PIT64B_MSBPR) 32 MSB of the Timer Period */
#define PIT64B_MSBPR_MSBPERIOD(value) ((PIT64B_MSBPR_MSBPERIOD_Msk & ((value) << PIT64B_MSBPR_MSBPERIOD_Pos)))
/* -------- PIT64B_IER : (PIT64B Offset: 0x10) Interrupt Enable Register -------- */
#define PIT64B_IER_PERIOD (0x1u << 0) /**< \brief (PIT64B_IER) Elapsed Timer Period Interrupt Enable */
#define PIT64B_IER_OVRE (0x1u << 1) /**< \brief (PIT64B_IER) Overrun Error Interrupt Enable */
#define PIT64B_IER_SECE (0x1u << 4) /**< \brief (PIT64B_IER) Safety and/or Security Report Interrupt Enable */
/* -------- PIT64B_IDR : (PIT64B Offset: 0x14) Interrupt Disable Register -------- */
#define PIT64B_IDR_PERIOD (0x1u << 0) /**< \brief (PIT64B_IDR) Elapsed Timer Period Interrupt Disable */
#define PIT64B_IDR_OVRE (0x1u << 1) /**< \brief (PIT64B_IDR) Overrun Error Interrupt Disable */
#define PIT64B_IDR_SECE (0x1u << 4) /**< \brief (PIT64B_IDR) Safety and/or Security Report Interrupt Disable */
/* -------- PIT64B_IMR : (PIT64B Offset: 0x18) Interrupt Mask Register -------- */
#define PIT64B_IMR_PERIOD (0x1u << 0) /**< \brief (PIT64B_IMR) Elapsed Timer Period Interrupt Mask */
#define PIT64B_IMR_OVRE (0x1u << 1) /**< \brief (PIT64B_IMR) Overrun Error Interrupt Mask */
#define PIT64B_IMR_SECE (0x1u << 4) /**< \brief (PIT64B_IMR) Safety and/or Security Report Interrupt Mask */
/* -------- PIT64B_ISR : (PIT64B Offset: 0x1C) Interrupt Status Register -------- */
#define PIT64B_ISR_PERIOD (0x1u << 0) /**< \brief (PIT64B_ISR) Elapsed Timer Period Status Flag (cleared on read) */
#define PIT64B_ISR_OVRE (0x1u << 1) /**< \brief (PIT64B_ISR) Overrun Error (cleared on read) */
#define PIT64B_ISR_SECE (0x1u << 4) /**< \brief (PIT64B_ISR) Safety/Security Report (cleared on read) */
/* -------- PIT64B_TLSBR : (PIT64B Offset: 0x20) Timer LSB Current Value Register -------- */
#define PIT64B_TLSBR_LSBTIMER_Pos 0
#define PIT64B_TLSBR_LSBTIMER_Msk (0xffffffffu << PIT64B_TLSBR_LSBTIMER_Pos) /**< \brief (PIT64B_TLSBR) Current 32 LSB of the Timer */
/* -------- PIT64B_TMSBR : (PIT64B Offset: 0x24) Timer MSB Current Value Register -------- */
#define PIT64B_TMSBR_MSBTIMER_Pos 0
#define PIT64B_TMSBR_MSBTIMER_Msk (0xffffffffu << PIT64B_TMSBR_MSBTIMER_Pos) /**< \brief (PIT64B_TMSBR) Current 32 MSB of the Timer */
/* -------- PIT64B_WPMR : (PIT64B Offset: 0xE4) Write Protection Mode Register -------- */
#define PIT64B_WPMR_WPEN (0x1u << 0) /**< \brief (PIT64B_WPMR) Write Protection Enable */
#define PIT64B_WPMR_WPITEN (0x1u << 1) /**< \brief (PIT64B_WPMR) Write Protection Interruption Enable */
#define PIT64B_WPMR_WPCREN (0x1u << 2) /**< \brief (PIT64B_WPMR) Write Protection Control Enable */
#define PIT64B_WPMR_FIRSTE (0x1u << 4) /**< \brief (PIT64B_WPMR) First Error Report Enable */
#define PIT64B_WPMR_WPKEY_Pos 8
#define PIT64B_WPMR_WPKEY_Msk (0xffffffu << PIT64B_WPMR_WPKEY_Pos) /**< \brief (PIT64B_WPMR) Write Protection Key */
#define PIT64B_WPMR_WPKEY(value) ((PIT64B_WPMR_WPKEY_Msk & ((value) << PIT64B_WPMR_WPKEY_Pos)))
#define   PIT64B_WPMR_WPKEY_PASSWD (0x504954u << 8) /**< \brief (PIT64B_WPMR) Writing any other value in this field aborts the write operation of the WPCREN, WPITEN and WPEN bits. Always reads as 0. */
/* -------- PIT64B_WPSR : (PIT64B Offset: 0xE8) Write Protection Status Register -------- */
#define PIT64B_WPSR_WPVS (0x1u << 0) /**< \brief (PIT64B_WPSR) Write Protection Violation Status (cleared on read) */
#define PIT64B_WPSR_CGD (0x1u << 1) /**< \brief (PIT64B_WPSR) Clock Glitch Detected (cleared on read) */
#define PIT64B_WPSR_SEQE (0x1u << 2) /**< \brief (PIT64B_WPSR) Internal Sequencer Error (cleared on read) */
#define PIT64B_WPSR_SWE (0x1u << 3) /**< \brief (PIT64B_WPSR) Software Control Error (cleared on read) */
#define PIT64B_WPSR_WPVSRC_Pos 8
#define PIT64B_WPSR_WPVSRC_Msk (0xffffu << PIT64B_WPSR_WPVSRC_Pos) /**< \brief (PIT64B_WPSR) Write Protection Violation Source */
#define PIT64B_WPSR_SWETYP_Pos 24
#define PIT64B_WPSR_SWETYP_Msk (0x3u << PIT64B_WPSR_SWETYP_Pos) /**< \brief (PIT64B_WPSR) Software Error Type (cleared on read) */
#define   PIT64B_WPSR_SWETYP_READ_WO (0x0u << 24) /**< \brief (PIT64B_WPSR) A write-only register has been read (warning). */
#define   PIT64B_WPSR_SWETYP_WRITE_RO (0x1u << 24) /**< \brief (PIT64B_WPSR) A write access has been performed on a read-only register (Warning). */
#define   PIT64B_WPSR_SWETYP_UNDEF_RW (0x2u << 24) /**< \brief (PIT64B_WPSR) Access to an undefined address (warning). */
#define   PIT64B_WPSR_SWETYP_WEIRD_ACTION (0x3u << 24) /**< \brief (PIT64B_WPSR) A write access is performed into PIT64B_MR, PIT64B_LSBR, PIT64B_MSBR while the PIT64B is running (abnormal). */
#define PIT64B_WPSR_ECLASS (0x1u << 31) /**< \brief (PIT64B_WPSR) Software Error Class (cleared on read) */
#define   PIT64B_WPSR_ECLASS_WARNING (0x0u << 31) /**< \brief (PIT64B_WPSR) An abnormal access that does not affect system functionality. */
#define   PIT64B_WPSR_ECLASS_ERROR (0x1u << 31) /**< \brief (PIT64B_WPSR) A write access is performed into PIT64B_MR, PIT64B_LSBR, PIT64B_MSBR while the PIT64B is running. */

/*@}*/


#endif /* _SAM9X_PIT64B_COMPONENT_ */
