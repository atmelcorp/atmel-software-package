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

#ifndef _SAMA5D4_SMD_COMPONENT_
#define _SAMA5D4_SMD_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Software Modem Device */
/* ============================================================================= */
/** \addtogroup SAMA5D4_SMD Software Modem Device */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Smd hardware registers */
typedef struct {
	__I uint32_t Reserved1[3];
	__IO uint32_t SMD_DRIVE;    /**< \brief (Smd Offset: 0x0C) SMD Drive register */
} Smd;
#endif				/* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- SMD_DRIVE : (SMD Offset: 0x0C) SMD Drive register -------- */
#define SMD_DRIVE_MIE (0x1u << 0) /**< \brief (SMD_DRIVE) MADCVS Interrupt Enable */
#define SMD_DRIVE_DC_PWRCLKPN (0x1u << 1) /**< \brief (SMD_DRIVE) Direct Control of PWRCLKP, PWRCLKN Pins Enable */
#define SMD_DRIVE_PWRCLKP_PV2 (0x1u << 2) /**< \brief (SMD_DRIVE) PWRCLKP Pin Value */
#define SMD_DRIVE_PWRCLKP_PV (0x1u << 3) /**< \brief (SMD_DRIVE) PWRCLKP Pin Value */
#define SMD_DRIVE_PWRCLKN_PCS2_Pos 4
#define SMD_DRIVE_PWRCLKN_PCS2_Msk (0x3u << SMD_DRIVE_PWRCLKN_PCS2_Pos)	/**< \brief (SMD_DRIVE) PWRCLKN Pin Control Select */
#define SMD_DRIVE_PWRCLKN_PCS2(value) ((SMD_DRIVE_PWRCLKN_PCS2_Msk & ((value) << SMD_DRIVE_PWRCLKN_PCS2_Pos)))
#define SMD_DRIVE_PWRCLKP_PCS_Pos 6
#define SMD_DRIVE_PWRCLKP_PCS_Msk (0x3u << SMD_DRIVE_PWRCLKP_PCS_Pos) /**< \brief (SMD_DRIVE) PWRCLKP Pin Control Select */
#define SMD_DRIVE_PWRCLKP_PCS(value) ((SMD_DRIVE_PWRCLKP_PCS_Msk & ((value) << SMD_DRIVE_PWRCLKP_PCS_Pos)))

/*@}*/

#endif				/* _SAMA5D4_SMD_COMPONENT_ */
