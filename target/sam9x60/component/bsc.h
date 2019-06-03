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

#ifndef _SAM9X_BSC_COMPONENT_
#define _SAM9X_BSC_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Boot Sequence Controller */
/* ============================================================================= */
/** \addtogroup SAM9X_BSC Boot Sequence Controller */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Bsc hardware registers */
typedef struct {
  __IO uint32_t BSC_CR; /**< \brief (Bsc Offset: 0x0) Boot Sequence Controller Configuration Register */
} Bsc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- BSC_CR : (BSC Offset: 0x0) Boot Sequence Controller Configuration Register -------- */
#define BSC_CR_BOOT_Pos 0
#define BSC_CR_BOOT_Msk (0x7u << BSC_CR_BOOT_Pos) /**< \brief (BSC_CR) Boot Media Sequence */
#define BSC_CR_BOOT(value) ((BSC_CR_BOOT_Msk & ((value) << BSC_CR_BOOT_Pos)))
#define BSC_CR_WPKEY_Pos 16
#define BSC_CR_WPKEY_Msk (0xffffu << BSC_CR_WPKEY_Pos) /**< \brief (BSC_CR) Write Protection Key (Write-only) */
#define BSC_CR_WPKEY(value) ((BSC_CR_WPKEY_Msk & ((value) << BSC_CR_WPKEY_Pos)))
#define   BSC_CR_WPKEY_PASSWD (0x6683u << 16) /**< \brief (BSC_CR) Writing any other value in this field aborts the write operation of the BOOT field. Always reads as 0. */

/*@}*/


#endif /* _SAM9X_BSC_COMPONENT_ */
