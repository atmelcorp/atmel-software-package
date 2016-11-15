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

#ifndef _CORTEXM7_SCNSCB_COMPONENT_
#define _CORTEXM7_SCNSCB_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Cortex-M7 System control Register not in SCB */
/* ============================================================================= */
/** \addtogroup Cortex-M7 System control Register not in SCB */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct {
	__I  uint32_t Reserved1[1];
	__I  uint32_t SCNSCB_ICTR;  /**< \brief (Scnscb Offset: 0x004) Interrupt Controller Type Register */
	__I  uint32_t SCNSCB_ACTLR; /**< \brief (Scnscb Offset: 0x008) Auxiliary Control Register */
} Scnscb;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- SCNSCB_ICTR : (SCNSCB Offset: 0x004) Interrupt Controller Type Register -------- */
#define SCNSCB_ICTR_INTLINESNUM_Pos 0
#define SCNSCB_ICTR_INTLINESNUM_Msk (0xfu << 0)
/* -------- SCNSCB_ACTLR : (SCNSCB Offset: 0x008) Auxiliary Control Register -------- */
#define SCNSCB_ACTLR_DISMCYCINT (0x1u << 0)
#define SCNSCB_ACTLR_DISFOLD (0x1u << 2)
#define SCNSCB_ACTLR_FPEXCODIS (0x1u << 10)
#define SCNSCB_ACTLR_DISRAMODE (0x1u << 11)
#define SCNSCB_ACTLR_DISITMATBFLUSH (0x1u << 12)

/*@}*/

#endif /* _CM7_SCNSCB_COMPONENT_ */
