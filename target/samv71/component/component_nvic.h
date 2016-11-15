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

#ifndef _CORTEXM7_NVIC_COMPONENT_
#define _CORTEXM7_NVIC_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Cortex-M7 Nested Vectored Interrupt Controller */
/* ============================================================================= */
/** \addtogroup Cortex-M7 Nested Vectored Interrupt Controller */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct {
	__IO uint32_t NVIC_ISER[8];                  /**< \brief (Nvic Offset: 0x000) Interrupt Set-Enable Register */
	__I  uint32_t Reserved1[24];
	__IO uint32_t NVIC_ICER[8];                  /**< \brief (Nvic Offset: 0x080) Interrupt Clear-Enable Register */
	__I  uint32_t Reserved2[24];
	__IO uint32_t NVIC_ISPR[8];                  /**< \brief (Nvic Offset: 0x100) Interrupt Set-Pending Register */
	__I  uint32_t Reserved3[24];
	__IO uint32_t NVIC_ICPR[8];                  /**< \brief (Nvic Offset: 0x180) Interrupt Clear-Pending Register */
	__I  uint32_t Reserved4[24];
	__I  uint32_t NVIC_IABR[8];                  /**< \brief (Nvic Offset: 0x200) Interrupt Active Bit Register */
	__I  uint32_t Reserved5[56];
	__IO uint32_t NVIC_IPR[60];                  /**< \brief (Nvic Offset: 0x300) Interrupt Priority Register */
	__I  uint32_t Reserved6[644];
	__O  uint32_t NVIC_STIR;                     /**< \brief (Nvic Offset: 0xE00) Software Triggered Interrupt Register */
} Nvic;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- NVIC_ICTR : (NVIC Offset: 0x004) Interrupt Controller Type Register -------- */
#define NVIC_ICTR_INTLINESNUM_Pos 0
#define NVIC_ICTR_INTLINESNUM_Msk (0xfu << 0)
/* -------- NVIC_STIR : (NVIC Offset: 0xE00) Software Triggered Interrupt Register -------- */
#define NVIC_STIR_INTID_Pos 0
#define NVIC_STIR_INTID_Msk (0x1ffu << 0)
#define NVIC_STIR_INTID(value) ((NVIC_STIR_INTID_Msk & ((value) << NVIC_STIR_INTID_Pos)))

/*@}*/

#endif /* _CM7_NVIC_COMPONENT_ */
