/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2016, Atmel Corporation                                        */
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

#ifndef _CORTEXM7_FPU_COMPONENT_
#define _CORTEXM7_FPU_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Cortex-M7 Floating Point Unit */
/* ============================================================================= */
/** \addtogroup Cortex-M7 Floating Point Unit */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct {
	__I  uint32_t Reserved1[1];
	__IO uint32_t FPU_FPCCR;    /**< \brief (Fpu Offset: 0x04) FP Context Control Register */
	__IO uint32_t FPU_FPCAR;    /**< \brief (Fpu Offset: 0x08) FP Context Address Register */
	__IO uint32_t FPU_FPDSCR;   /**< \brief (Fpu Offset: 0x0C) FP Default Status Control Register */
	__I  uint32_t FPU_MVFR0;    /**< \brief (Fpu Offset: 0x10) Media and FP Feature Register 0 */
	__I  uint32_t FPU_MVFR1;    /**< \brief (Fpu Offset: 0x14) Media and FP Feature Register 1 */
	__I  uint32_t FPU_MVFR2;    /**< \brief (Fpu Offset: 0x18) Media and FP Feature Register 2 */
} Fpu;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- FPU_FPCCR : (FPU Offset: 0x04) FP Context Control Register -------- */
#define FPU_FPCCR_LSPACT (0x1u << 0)
#define FPU_FPCCR_USER (0x1u << 1)
#define FPU_FPCCR_THREAD (0x1u << 3)
#define FPU_FPCCR_HFRDY (0x1u << 4)
#define FPU_FPCCR_MMRDY (0x1u << 5)
#define FPU_FPCCR_BFRDY (0x1u << 6)
#define FPU_FPCCR_MONRDY (0x1u << 8)
#define FPU_FPCCR_LSPEN (0x1u << 30)
#define FPU_FPCCR_ASPEN (0x1u << 31)
/* -------- FPU_FPCAR : (FPU Offset: 0x08) FP Context Address Register -------- */
#define FPU_FPCAR_ADDR_Pos 3
#define FPU_FPCAR_ADDR_Msk (0x1fffffffu << 3)
#define FPU_FPCAR_ADDR(value) ((FPU_FPCAR_ADDR_Msk & ((value) << FPU_FPCAR_ADDR_Pos)))
/* -------- FPU_FPDSCR : (FPU Offset: 0x0C) FP Default Status Control Register -------- */
#define FPU_FPDSCR_RMODE_Pos 22
#define FPU_FPDSCR_RMODE_Msk (0x3u << 22)
#define FPU_FPDSCR_RMODE(value) ((FPU_FPDSCR_RMODE_Msk & ((value) << FPU_FPDSCR_RMODE_Pos)))
#define FPU_FPDSCR_FZ (0x1u << 24)
#define FPU_FPDSCR_DN (0x1u << 25)
#define FPU_FPDSCR_AHP (0x1u << 26)

/*@}*/

#endif /* _CORTEXM7_FPU_COMPONENT_ */
