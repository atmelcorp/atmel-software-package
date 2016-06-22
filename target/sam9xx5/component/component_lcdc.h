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

#ifndef _SAM9X_LCDC_COMPONENT_
#define _SAM9X_LCDC_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR LCD Controller */
/* ============================================================================= */
/** \addtogroup SAM9X_LCDC LCD Controller */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Lcdc hardware registers */
typedef struct {
	__IO uint32_t LCDC_LCDCFG0;       /**< \brief (Lcdc Offset: 0x00000000) LCD Controller Configuration Register 0 */
	__IO uint32_t LCDC_LCDCFG1;       /**< \brief (Lcdc Offset: 0x00000004) LCD Controller Configuration Register 1 */
	__IO uint32_t LCDC_LCDCFG2;       /**< \brief (Lcdc Offset: 0x00000008) LCD Controller Configuration Register 2 */
	__IO uint32_t LCDC_LCDCFG3;       /**< \brief (Lcdc Offset: 0x0000000C) LCD Controller Configuration Register 3 */
	__IO uint32_t LCDC_LCDCFG4;       /**< \brief (Lcdc Offset: 0x00000010) LCD Controller Configuration Register 4 */
	__IO uint32_t LCDC_LCDCFG5;       /**< \brief (Lcdc Offset: 0x00000014) LCD Controller Configuration Register 5 */
	__IO uint32_t LCDC_LCDCFG6;       /**< \brief (Lcdc Offset: 0x00000018) LCD Controller Configuration Register 6 */
	__I  uint32_t Reserved1[1];
	__O  uint32_t LCDC_LCDEN;         /**< \brief (Lcdc Offset: 0x00000020) LCD Controller Enable Register */
	__O  uint32_t LCDC_LCDDIS;        /**< \brief (Lcdc Offset: 0x00000024) LCD Controller Disable Register */
	__I  uint32_t LCDC_LCDSR;         /**< \brief (Lcdc Offset: 0x00000028) LCD Controller Status Register */
	__O  uint32_t LCDC_LCDIER;        /**< \brief (Lcdc Offset: 0x0000002C) LCD Controller Interrupt Enable Register */
	__O  uint32_t LCDC_LCDIDR;        /**< \brief (Lcdc Offset: 0x00000030) LCD Controller Interrupt Disable Register */
	__I  uint32_t LCDC_LCDIMR;        /**< \brief (Lcdc Offset: 0x00000034) LCD Controller Interrupt Mask Register */
	__I  uint32_t LCDC_LCDISR;        /**< \brief (Lcdc Offset: 0x00000038) LCD Controller Interrupt Status Register */
	__I  uint32_t Reserved2[1];
	__O  uint32_t LCDC_BASECHER;      /**< \brief (Lcdc Offset: 0x00000040) Base Layer Channel Enable Register */
	__O  uint32_t LCDC_BASECHDR;      /**< \brief (Lcdc Offset: 0x00000044) Base Layer Channel Disable Register */
	__I  uint32_t LCDC_BASECHSR;      /**< \brief (Lcdc Offset: 0x00000048) Base Layer Channel Status Register */
	__O  uint32_t LCDC_BASEIER;       /**< \brief (Lcdc Offset: 0x0000004C) Base Layer Interrupt Enable Register */
	__O  uint32_t LCDC_BASEIDR;       /**< \brief (Lcdc Offset: 0x00000050) Base Layer Interrupt Disabled Register */
	__I  uint32_t LCDC_BASEIMR;       /**< \brief (Lcdc Offset: 0x00000054) Base Layer Interrupt Mask Register */
	__I  uint32_t LCDC_BASEISR;       /**< \brief (Lcdc Offset: 0x00000058) Base Layer Interrupt Status Register */
	__IO uint32_t LCDC_BASEHEAD;      /**< \brief (Lcdc Offset: 0x0000005C) Base Layer DMA Head Register */
	__IO uint32_t LCDC_BASEADDR;      /**< \brief (Lcdc Offset: 0x00000060) Base Layer DMA Address Register */
	__IO uint32_t LCDC_BASECTRL;      /**< \brief (Lcdc Offset: 0x00000064) Base Layer DMA Control Register */
	__IO uint32_t LCDC_BASENEXT;      /**< \brief (Lcdc Offset: 0x00000068) Base Layer DMA Next Register */
	__IO uint32_t LCDC_BASECFG0;      /**< \brief (Lcdc Offset: 0x0000006C) Base Layer Configuration Register 0 */
	__IO uint32_t LCDC_BASECFG1;      /**< \brief (Lcdc Offset: 0x00000070) Base Layer Configuration Register 1 */
	__IO uint32_t LCDC_BASECFG2;      /**< \brief (Lcdc Offset: 0x00000074) Base Layer Configuration Register 2 */
	__IO uint32_t LCDC_BASECFG3;      /**< \brief (Lcdc Offset: 0x00000078) Base Layer Configuration Register 3 */
	__IO uint32_t LCDC_BASECFG4;      /**< \brief (Lcdc Offset: 0x0000007C) Base Layer Configuration Register 4 */
	__I  uint32_t Reserved3[32];
	__O  uint32_t LCDC_OVR1CHER;      /**< \brief (Lcdc Offset: 0x00000100) Overlay 1 Channel Enable Register */
	__O  uint32_t LCDC_OVR1CHDR;      /**< \brief (Lcdc Offset: 0x00000104) Overlay 1 Channel Disable Register */
	__I  uint32_t LCDC_OVR1CHSR;      /**< \brief (Lcdc Offset: 0x00000108) Overlay 1 Channel Status Register */
	__O  uint32_t LCDC_OVR1IER;       /**< \brief (Lcdc Offset: 0x0000010C) Overlay 1 Interrupt Enable Register */
	__O  uint32_t LCDC_OVR1IDR;       /**< \brief (Lcdc Offset: 0x00000110) Overlay 1 Interrupt Disable Register */
	__I  uint32_t LCDC_OVR1IMR;       /**< \brief (Lcdc Offset: 0x00000114) Overlay 1 Interrupt Mask Register */
	__I  uint32_t LCDC_OVR1ISR;       /**< \brief (Lcdc Offset: 0x00000118) Overlay 1 Interrupt Status Register */
	__IO uint32_t LCDC_OVR1HEAD;      /**< \brief (Lcdc Offset: 0x0000011C) Overlay 1 DMA Head Register */
	__IO uint32_t LCDC_OVR1ADDR;      /**< \brief (Lcdc Offset: 0x00000120) Overlay 1 DMA Address Register */
	__IO uint32_t LCDC_OVR1CTRL;      /**< \brief (Lcdc Offset: 0x00000124) Overlay1 DMA Control Register */
	__IO uint32_t LCDC_OVR1NEXT;      /**< \brief (Lcdc Offset: 0x00000128) Overlay1 DMA Next Register */
	__IO uint32_t LCDC_OVR1CFG0;      /**< \brief (Lcdc Offset: 0x0000012C) Overlay 1 Configuration Register 0 */
	__IO uint32_t LCDC_OVR1CFG1;      /**< \brief (Lcdc Offset: 0x00000130) Overlay 1 Configuration Register 1 */
	__IO uint32_t LCDC_OVR1CFG2;      /**< \brief (Lcdc Offset: 0x00000134) Overlay 1 Configuration Register 2 */
	__IO uint32_t LCDC_OVR1CFG3;      /**< \brief (Lcdc Offset: 0x00000138) Overlay 1 Configuration Register 3 */
	__IO uint32_t LCDC_OVR1CFG4;      /**< \brief (Lcdc Offset: 0x0000013C) Overlay 1 Configuration Register 4 */
	__IO uint32_t LCDC_OVR1CFG5;      /**< \brief (Lcdc Offset: 0x00000140) Overlay 1 Configuration Register 5 */
	__IO uint32_t LCDC_OVR1CFG6;      /**< \brief (Lcdc Offset: 0x00000144) Overlay 1 Configuration Register 6 */
	__IO uint32_t LCDC_OVR1CFG7;      /**< \brief (Lcdc Offset: 0x00000148) Overlay 1 Configuration Register 7 */
	__IO uint32_t LCDC_OVR1CFG8;      /**< \brief (Lcdc Offset: 0x0000014C) Overlay 1 Configuration Register 8 */
	__IO uint32_t LCDC_OVR1CFG9;      /**< \brief (Lcdc Offset: 0x00000150) Overlay 1 Configuration Register 9 */
	__I  uint32_t Reserved4[75];
	__O  uint32_t LCDC_HEOCHER;       /**< \brief (Lcdc Offset: 0x00000280) High End Overlay Channel Enable Register */
	__O  uint32_t LCDC_HEOCHDR;       /**< \brief (Lcdc Offset: 0x00000284) High End Overlay Channel Disable Register */
	__I  uint32_t LCDC_HEOCHSR;       /**< \brief (Lcdc Offset: 0x00000288) High End Overlay Channel Status Register */
	__O  uint32_t LCDC_HEOIER;        /**< \brief (Lcdc Offset: 0x0000028C) High End Overlay Interrupt Enable Register */
	__O  uint32_t LCDC_HEOIDR;        /**< \brief (Lcdc Offset: 0x00000290) High End Overlay Interrupt Disable Register */
	__I  uint32_t LCDC_HEOIMR;        /**< \brief (Lcdc Offset: 0x00000294) High End Overlay Interrupt Mask Register */
	__I  uint32_t LCDC_HEOISR;        /**< \brief (Lcdc Offset: 0x00000298) High End Overlay Interrupt Status Register */
	__IO uint32_t LCDC_HEOHEAD;       /**< \brief (Lcdc Offset: 0x0000029C) High End Overlay DMA Head Register */
	__IO uint32_t LCDC_HEOADDR;       /**< \brief (Lcdc Offset: 0x000002A0) High End Overlay DMA Address Register */
	__IO uint32_t LCDC_HEOCTRL;       /**< \brief (Lcdc Offset: 0x000002A4) High End Overlay DMA Control Register */
	__IO uint32_t LCDC_HEONEXT;       /**< \brief (Lcdc Offset: 0x000002A8) High End Overlay DMA Next Register */
	__IO uint32_t LCDC_HEOUHEAD;      /**< \brief (Lcdc Offset: 0x000002AC) High End Overlay U-UV DMA Head Register */
	__IO uint32_t LCDC_HEOUADDR;      /**< \brief (Lcdc Offset: 0x000002B0) High End Overlay U-UV DMA Address Register */
	__IO uint32_t LCDC_HEOUCTRL;      /**< \brief (Lcdc Offset: 0x000002B4) High End Overlay U-UV DMA Control Register */
	__IO uint32_t LCDC_HEOUNEXT;      /**< \brief (Lcdc Offset: 0x000002B8) High End Overlay U-UV DMA Next Register */
	__IO uint32_t LCDC_HEOVHEAD;      /**< \brief (Lcdc Offset: 0x000002BC) High End Overlay V DMA Head Register */
	__IO uint32_t LCDC_HEOVADDR;      /**< \brief (Lcdc Offset: 0x000002C0) High End Overlay V DMA Address Register */
	__IO uint32_t LCDC_HEOVCTRL;      /**< \brief (Lcdc Offset: 0x000002C4) High End Overlay V DMA Control Register */
	__IO uint32_t LCDC_HEOVNEXT;      /**< \brief (Lcdc Offset: 0x000002C8) High End Overlay V DMA Next Register */
	__IO uint32_t LCDC_HEOCFG0;       /**< \brief (Lcdc Offset: 0x000002CC) High End Overlay Configuration Register 0 */
	__IO uint32_t LCDC_HEOCFG1;       /**< \brief (Lcdc Offset: 0x000002D0) High End Overlay Configuration Register 1 */
	__IO uint32_t LCDC_HEOCFG2;       /**< \brief (Lcdc Offset: 0x000002D4) High End Overlay Configuration Register 2 */
	__IO uint32_t LCDC_HEOCFG3;       /**< \brief (Lcdc Offset: 0x000002D8) High End Overlay Configuration Register 3 */
	__IO uint32_t LCDC_HEOCFG4;       /**< \brief (Lcdc Offset: 0x000002DC) High End Overlay Configuration Register 4 */
	__IO uint32_t LCDC_HEOCFG5;       /**< \brief (Lcdc Offset: 0x000002E0) High End Overlay Configuration Register 5 */
	__IO uint32_t LCDC_HEOCFG6;       /**< \brief (Lcdc Offset: 0x000002E4) High End Overlay Configuration Register 6 */
	__IO uint32_t LCDC_HEOCFG7;       /**< \brief (Lcdc Offset: 0x000002E8) High End Overlay Configuration Register 7 */
	__IO uint32_t LCDC_HEOCFG8;       /**< \brief (Lcdc Offset: 0x000002EC) High End Overlay Configuration Register 8 */
	__IO uint32_t LCDC_HEOCFG9;       /**< \brief (Lcdc Offset: 0x000002F0) High End Overlay Configuration Register 9 */
	__IO uint32_t LCDC_HEOCFG10;      /**< \brief (Lcdc Offset: 0x000002F4) High End Overlay Configuration Register 10 */
	__IO uint32_t LCDC_HEOCFG11;      /**< \brief (Lcdc Offset: 0x000002F8) High End Overlay Configuration Register 11 */
	__IO uint32_t LCDC_HEOCFG12;      /**< \brief (Lcdc Offset: 0x000002FC) High End Overlay Configuration Register 12 */
	__IO uint32_t LCDC_HEOCFG13;      /**< \brief (Lcdc Offset: 0x00000300) High End Overlay Configuration Register 13 */
	__IO uint32_t LCDC_HEOCFG14;      /**< \brief (Lcdc Offset: 0x00000304) High End Overlay Configuration Register 14 */
	__IO uint32_t LCDC_HEOCFG15;      /**< \brief (Lcdc Offset: 0x00000308) High End Overlay Configuration Register 15 */
	__IO uint32_t LCDC_HEOCFG16;      /**< \brief (Lcdc Offset: 0x0000030C) High End Overlay Configuration Register 16 */
	__I  uint32_t Reserved5[12];
	__O  uint32_t LCDC_HCRCHER;       /**< \brief (Lcdc Offset: 0x00000340) Hardware Cursor Channel Enable Register */
	__O  uint32_t LCDC_HCRCHDR;       /**< \brief (Lcdc Offset: 0x00000344) Hardware Cursor Channel Disable Register */
	__I  uint32_t LCDC_HCRCHSR;       /**< \brief (Lcdc Offset: 0x00000348) Hardware Cursor Channel Status Register */
	__O  uint32_t LCDC_HCRIER;        /**< \brief (Lcdc Offset: 0x0000034C) Hardware Cursor Interrupt Enable Register */
	__O  uint32_t LCDC_HCRIDR;        /**< \brief (Lcdc Offset: 0x00000350) Hardware Cursor Interrupt Disable Register */
	__I  uint32_t LCDC_HCRIMR;        /**< \brief (Lcdc Offset: 0x00000354) Hardware Cursor Interrupt Mask Register */
	__I  uint32_t LCDC_HCRISR;        /**< \brief (Lcdc Offset: 0x00000358) Hardware Cursor Interrupt Status Register */
	__IO uint32_t LCDC_HCRHEAD;       /**< \brief (Lcdc Offset: 0x0000035C) Hardware Cursor DMA Head Register */
	__IO uint32_t LCDC_HCRADDR;       /**< \brief (Lcdc Offset: 0x00000360) Hardware cursor DMA Address Register */
	__IO uint32_t LCDC_HCRCTRL;       /**< \brief (Lcdc Offset: 0x00000364) Hardware Cursor DMA Control Register */
	__IO uint32_t LCDC_HCRNEXT;       /**< \brief (Lcdc Offset: 0x00000368) Hardware Cursor DMA NExt Register */
	__IO uint32_t LCDC_HCRCFG0;       /**< \brief (Lcdc Offset: 0x0000036C) Hardware Cursor Configuration 0 Register */
	__IO uint32_t LCDC_HCRCFG1;       /**< \brief (Lcdc Offset: 0x00000370) Hardware Cursor Configuration 1 Register */
	__IO uint32_t LCDC_HCRCFG2;       /**< \brief (Lcdc Offset: 0x00000374) Hardware Cursor Configuration 2 Register */
	__IO uint32_t LCDC_HCRCFG3;       /**< \brief (Lcdc Offset: 0x00000378) Hardware Cursor Configuration 3 Register */
	__IO uint32_t LCDC_HCRCFG4;       /**< \brief (Lcdc Offset: 0x0000037C) Hardware Cursor Configuration 4 Register */
	__I  uint32_t Reserved6[1];
	__IO uint32_t LCDC_HCRCFG6;       /**< \brief (Lcdc Offset: 0x00000384) Hardware Cursor Configuration 6 Register */
	__IO uint32_t LCDC_HCRCFG7;       /**< \brief (Lcdc Offset: 0x00000388) Hardware Cursor Configuration 7 Register */
	__IO uint32_t LCDC_HCRCFG8;       /**< \brief (Lcdc Offset: 0x0000038C) Hardware Cursor Configuration 8 Register */
	__IO uint32_t LCDC_HCRCFG9;       /**< \brief (Lcdc Offset: 0x00000390) Hardware Cursor Configuration 9 Register */
	__I  uint32_t Reserved7[27];
	__IO uint32_t LCDC_BASECLUT[256]; /**< \brief (Lcdc Offset: 0x00000400) Base CLUT Register */
	__IO uint32_t LCDC_OVR1CLUT[256]; /**< \brief (Lcdc Offset: 0x00000800) Overlay 1 CLUT Register */
	__I  uint32_t Reserved8[256];
	__IO uint32_t LCDC_HEOCLUT[256];  /**< \brief (Lcdc Offset: 0x00001000) High End Overlay CLUT Register */
	__IO uint32_t LCDC_HCRCLUT[256];  /**< \brief (Lcdc Offset: 0x00001400) Hardware Cursor CLUT Register */
} Lcdc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- LCDC_LCDCFG0 : (LCDC Offset: 0x00000000) LCD Controller Configuration Register 0 -------- */
#define LCDC_LCDCFG0_CLKPOL (0x1u << 0) /**< \brief (LCDC_LCDCFG0) LCD Controller Clock Polarity */
#define LCDC_LCDCFG0_CLKSEL (0x1u << 2) /**< \brief (LCDC_LCDCFG0) LCD Controller Clock Source Selection */
#define LCDC_LCDCFG0_CLKPWMSEL (0x1u << 3) /**< \brief (LCDC_LCDCFG0) LCD Controller PWM Clock Source Selection */
#define LCDC_LCDCFG0_CGDISBASE (0x1u << 8) /**< \brief (LCDC_LCDCFG0) Clock Gating Disable Control for the Base Layer */
#define LCDC_LCDCFG0_CGDISOVR1 (0x1u << 9) /**< \brief (LCDC_LCDCFG0) Clock Gating Disable Control for the Overlay 1 Layer */
#define LCDC_LCDCFG0_CGDISHEO (0x1u << 11) /**< \brief (LCDC_LCDCFG0) Clock Gating Disable Control for the High End Overlay */
#define LCDC_LCDCFG0_CGDISHCR (0x1u << 12) /**< \brief (LCDC_LCDCFG0) Clock Gating Disable Control for the Hardware Cursor Layer */
#define LCDC_LCDCFG0_CLKDIV_Pos 16
#define LCDC_LCDCFG0_CLKDIV_Msk (0xffu << LCDC_LCDCFG0_CLKDIV_Pos) /**< \brief (LCDC_LCDCFG0) LCD Controller Clock Divider */
#define LCDC_LCDCFG0_CLKDIV(value) ((LCDC_LCDCFG0_CLKDIV_Msk & ((value) << LCDC_LCDCFG0_CLKDIV_Pos)))
/* -------- LCDC_LCDCFG1 : (LCDC Offset: 0x00000004) LCD Controller Configuration Register 1 -------- */
#define LCDC_LCDCFG1_HSPW_Pos 0
#define LCDC_LCDCFG1_HSPW_Msk (0x3fu << LCDC_LCDCFG1_HSPW_Pos) /**< \brief (LCDC_LCDCFG1) Horizontal Synchronization Pulse Width */
#define LCDC_LCDCFG1_HSPW(value) ((LCDC_LCDCFG1_HSPW_Msk & ((value) << LCDC_LCDCFG1_HSPW_Pos)))
#define LCDC_LCDCFG1_VSPW_Pos 16
#define LCDC_LCDCFG1_VSPW_Msk (0x3fu << LCDC_LCDCFG1_VSPW_Pos) /**< \brief (LCDC_LCDCFG1) Vertical Synchronization Pulse Width */
#define LCDC_LCDCFG1_VSPW(value) ((LCDC_LCDCFG1_VSPW_Msk & ((value) << LCDC_LCDCFG1_VSPW_Pos)))
/* -------- LCDC_LCDCFG2 : (LCDC Offset: 0x00000008) LCD Controller Configuration Register 2 -------- */
#define LCDC_LCDCFG2_VFPW_Pos 0
#define LCDC_LCDCFG2_VFPW_Msk (0x3fu << LCDC_LCDCFG2_VFPW_Pos) /**< \brief (LCDC_LCDCFG2) Vertical Front Porch Width */
#define LCDC_LCDCFG2_VFPW(value) ((LCDC_LCDCFG2_VFPW_Msk & ((value) << LCDC_LCDCFG2_VFPW_Pos)))
#define LCDC_LCDCFG2_VBPW_Pos 16
#define LCDC_LCDCFG2_VBPW_Msk (0x3fu << LCDC_LCDCFG2_VBPW_Pos) /**< \brief (LCDC_LCDCFG2) Vertical Back Porch Width */
#define LCDC_LCDCFG2_VBPW(value) ((LCDC_LCDCFG2_VBPW_Msk & ((value) << LCDC_LCDCFG2_VBPW_Pos)))
/* -------- LCDC_LCDCFG3 : (LCDC Offset: 0x0000000C) LCD Controller Configuration Register 3 -------- */
#define LCDC_LCDCFG3_HFPW_Pos 0
#define LCDC_LCDCFG3_HFPW_Msk (0xffu << LCDC_LCDCFG3_HFPW_Pos) /**< \brief (LCDC_LCDCFG3) Horizontal Front Porch Width */
#define LCDC_LCDCFG3_HFPW(value) ((LCDC_LCDCFG3_HFPW_Msk & ((value) << LCDC_LCDCFG3_HFPW_Pos)))
#define LCDC_LCDCFG3_HBPW_Pos 16
#define LCDC_LCDCFG3_HBPW_Msk (0xffu << LCDC_LCDCFG3_HBPW_Pos) /**< \brief (LCDC_LCDCFG3) Horizontal Back Porch Width */
#define LCDC_LCDCFG3_HBPW(value) ((LCDC_LCDCFG3_HBPW_Msk & ((value) << LCDC_LCDCFG3_HBPW_Pos)))
/* -------- LCDC_LCDCFG4 : (LCDC Offset: 0x00000010) LCD Controller Configuration Register 4 -------- */
#define LCDC_LCDCFG4_PPL_Pos 0
#define LCDC_LCDCFG4_PPL_Msk (0x7ffu << LCDC_LCDCFG4_PPL_Pos) /**< \brief (LCDC_LCDCFG4) Number of Pixels Per Line */
#define LCDC_LCDCFG4_PPL(value) ((LCDC_LCDCFG4_PPL_Msk & ((value) << LCDC_LCDCFG4_PPL_Pos)))
#define LCDC_LCDCFG4_RPF_Pos 16
#define LCDC_LCDCFG4_RPF_Msk (0x7ffu << LCDC_LCDCFG4_RPF_Pos) /**< \brief (LCDC_LCDCFG4) Number of Active Rows Per Frame */
#define LCDC_LCDCFG4_RPF(value) ((LCDC_LCDCFG4_RPF_Msk & ((value) << LCDC_LCDCFG4_RPF_Pos)))
/* -------- LCDC_LCDCFG5 : (LCDC Offset: 0x00000014) LCD Controller Configuration Register 5 -------- */
#define LCDC_LCDCFG5_HSPOL (0x1u << 0) /**< \brief (LCDC_LCDCFG5) Horizontal Synchronization Pulse Polarity */
#define LCDC_LCDCFG5_VSPOL (0x1u << 1) /**< \brief (LCDC_LCDCFG5) Vertical Synchronization Pulse Polarity */
#define LCDC_LCDCFG5_VSPDLYS (0x1u << 2) /**< \brief (LCDC_LCDCFG5) Vertical Synchronization Pulse Start */
#define LCDC_LCDCFG5_VSPDLYE (0x1u << 3) /**< \brief (LCDC_LCDCFG5) Vertical Synchronization Pulse End */
#define LCDC_LCDCFG5_DISPPOL (0x1u << 4) /**< \brief (LCDC_LCDCFG5) Display Signal Polarity */
#define LCDC_LCDCFG5_DITHER (0x1u << 6) /**< \brief (LCDC_LCDCFG5) LCD Controller Dithering */
#define LCDC_LCDCFG5_DISPDLY (0x1u << 7) /**< \brief (LCDC_LCDCFG5) LCD Controller Display Power Signal Synchronization */
#define LCDC_LCDCFG5_MODE_Pos 8
#define LCDC_LCDCFG5_MODE_Msk (0x3u << LCDC_LCDCFG5_MODE_Pos) /**< \brief (LCDC_LCDCFG5) LCD Controller Output Mode */
#define LCDC_LCDCFG5_MODE(value) ((LCDC_LCDCFG5_MODE_Msk & ((value) << LCDC_LCDCFG5_MODE_Pos)))
#define   LCDC_LCDCFG5_MODE_OUTPUT_12BPP (0x0u << 8) /**< \brief (LCDC_LCDCFG5) LCD Output mode is set to 12 bits per pixel */
#define   LCDC_LCDCFG5_MODE_OUTPUT_16BPP (0x1u << 8) /**< \brief (LCDC_LCDCFG5) LCD Output mode is set to 16 bits per pixel */
#define   LCDC_LCDCFG5_MODE_OUTPUT_18BPP (0x2u << 8) /**< \brief (LCDC_LCDCFG5) LCD Output mode is set to 18 bits per pixel */
#define   LCDC_LCDCFG5_MODE_OUTPUT_24BPP (0x3u << 8) /**< \brief (LCDC_LCDCFG5) LCD Output mode is set to 24 bits per pixel */
#define LCDC_LCDCFG5_VSPSU (0x1u << 12) /**< \brief (LCDC_LCDCFG5) LCD Controller Vertical Synchronization Pulse Setup Configuration */
#define LCDC_LCDCFG5_VSPHO (0x1u << 13) /**< \brief (LCDC_LCDCFG5) LCD Controller Vertical Synchronization Pulse Hold Configuration */
#define LCDC_LCDCFG5_GUARDTIME_Pos 16
#define LCDC_LCDCFG5_GUARDTIME_Msk (0x1fu << LCDC_LCDCFG5_GUARDTIME_Pos) /**< \brief (LCDC_LCDCFG5) LCD DISPLAY Guard Time */
#define LCDC_LCDCFG5_GUARDTIME(value) ((LCDC_LCDCFG5_GUARDTIME_Msk & ((value) << LCDC_LCDCFG5_GUARDTIME_Pos)))
/* -------- LCDC_LCDCFG6 : (LCDC Offset: 0x00000018) LCD Controller Configuration Register 6 -------- */
#define LCDC_LCDCFG6_PWMPS_Pos 0
#define LCDC_LCDCFG6_PWMPS_Msk (0x7u << LCDC_LCDCFG6_PWMPS_Pos) /**< \brief (LCDC_LCDCFG6) PWM Clock Prescaler */
#define LCDC_LCDCFG6_PWMPS(value) ((LCDC_LCDCFG6_PWMPS_Msk & ((value) << LCDC_LCDCFG6_PWMPS_Pos)))
#define   LCDC_LCDCFG6_PWMPS_DIV_1 (0x0u << 0) /**< \brief (LCDC_LCDCFG6) The counter advances at a rate of fCOUNTER = fPWM_SELECTED_CLOCK */
#define   LCDC_LCDCFG6_PWMPS_DIV_2 (0x1u << 0) /**< \brief (LCDC_LCDCFG6) The counter advances at a rate of fCOUNTER = fPWM_SELECTED_CLOCK/2 */
#define   LCDC_LCDCFG6_PWMPS_DIV_4 (0x2u << 0) /**< \brief (LCDC_LCDCFG6) The counter advances at a rate of fCOUNTER = fPWM_SELECTED_CLOCK/4 */
#define   LCDC_LCDCFG6_PWMPS_DIV_8 (0x3u << 0) /**< \brief (LCDC_LCDCFG6) The counter advances at a rate of fCOUNTER = fPWM_SELECTED_CLOCK/8 */
#define   LCDC_LCDCFG6_PWMPS_DIV_16 (0x4u << 0) /**< \brief (LCDC_LCDCFG6) The counter advances at a rate of fCOUNTER = fPWM_SELECTED_CLOCK/16 */
#define   LCDC_LCDCFG6_PWMPS_DIV_32 (0x5u << 0) /**< \brief (LCDC_LCDCFG6) The counter advances at a of rate fCOUNTER = fPWM_SELECTED_CLOCK/32 */
#define   LCDC_LCDCFG6_PWMPS_DIV_64 (0x6u << 0) /**< \brief (LCDC_LCDCFG6) The counter advances at a of rate fCOUNTER = fPWM_SELECTED_CLOCK/64 */
#define LCDC_LCDCFG6_PWMPOL (0x1u << 4) /**< \brief (LCDC_LCDCFG6) LCD Controller PWM Signal Polarity */
#define LCDC_LCDCFG6_PWMCVAL_Pos 8
#define LCDC_LCDCFG6_PWMCVAL_Msk (0xffu << LCDC_LCDCFG6_PWMCVAL_Pos) /**< \brief (LCDC_LCDCFG6) LCD Controller PWM Compare Value */
#define LCDC_LCDCFG6_PWMCVAL(value) ((LCDC_LCDCFG6_PWMCVAL_Msk & ((value) << LCDC_LCDCFG6_PWMCVAL_Pos)))
/* -------- LCDC_LCDEN : (LCDC Offset: 0x00000020) LCD Controller Enable Register -------- */
#define LCDC_LCDEN_CLKEN (0x1u << 0) /**< \brief (LCDC_LCDEN) LCD Controller Pixel Clock Enable */
#define LCDC_LCDEN_SYNCEN (0x1u << 1) /**< \brief (LCDC_LCDEN) LCD Controller Horizontal and Vertical Synchronization Enable */
#define LCDC_LCDEN_DISPEN (0x1u << 2) /**< \brief (LCDC_LCDEN) LCD Controller DISP Signal Enable */
#define LCDC_LCDEN_PWMEN (0x1u << 3) /**< \brief (LCDC_LCDEN) LCD Controller Pulse Width Modulation Enable */
/* -------- LCDC_LCDDIS : (LCDC Offset: 0x00000024) LCD Controller Disable Register -------- */
#define LCDC_LCDDIS_CLKDIS (0x1u << 0) /**< \brief (LCDC_LCDDIS) LCD Controller Pixel Clock Disable */
#define LCDC_LCDDIS_SYNCDIS (0x1u << 1) /**< \brief (LCDC_LCDDIS) LCD Controller Horizontal and Vertical Synchronization Disable */
#define LCDC_LCDDIS_DISPDIS (0x1u << 2) /**< \brief (LCDC_LCDDIS) LCD Controller DISP Signal Disable */
#define LCDC_LCDDIS_PWMDIS (0x1u << 3) /**< \brief (LCDC_LCDDIS) LCD Controller Pulse Width Modulation Disable */
#define LCDC_LCDDIS_CLKRST (0x1u << 8) /**< \brief (LCDC_LCDDIS) LCD Controller Clock Reset */
#define LCDC_LCDDIS_SYNCRST (0x1u << 9) /**< \brief (LCDC_LCDDIS) LCD Controller Horizontal and Vertical Synchronization Reset */
#define LCDC_LCDDIS_DISPRST (0x1u << 10) /**< \brief (LCDC_LCDDIS) LCD Controller DISP Signal Reset */
#define LCDC_LCDDIS_PWMRST (0x1u << 11) /**< \brief (LCDC_LCDDIS) LCD Controller PWM Reset */
/* -------- LCDC_LCDSR : (LCDC Offset: 0x00000028) LCD Controller Status Register -------- */
#define LCDC_LCDSR_CLKSTS (0x1u << 0) /**< \brief (LCDC_LCDSR) Clock Status */
#define LCDC_LCDSR_LCDSTS (0x1u << 1) /**< \brief (LCDC_LCDSR) LCD Controller Synchronization status */
#define LCDC_LCDSR_DISPSTS (0x1u << 2) /**< \brief (LCDC_LCDSR) LCD Controller DISP Signal Status */
#define LCDC_LCDSR_PWMSTS (0x1u << 3) /**< \brief (LCDC_LCDSR) LCD Controller PWM Signal Status */
#define LCDC_LCDSR_SIPSTS (0x1u << 4) /**< \brief (LCDC_LCDSR) Synchronization In Progress */
/* -------- LCDC_LCDIER : (LCDC Offset: 0x0000002C) LCD Controller Interrupt Enable Register -------- */
#define LCDC_LCDIER_SOFIE (0x1u << 0) /**< \brief (LCDC_LCDIER) Start of Frame Interrupt Enable Register */
#define LCDC_LCDIER_DISIE (0x1u << 1) /**< \brief (LCDC_LCDIER) LCD Disable Interrupt Enable Register */
#define LCDC_LCDIER_DISPIE (0x1u << 2) /**< \brief (LCDC_LCDIER) Power UP/Down Sequence Terminated Interrupt Enable Register */
#define LCDC_LCDIER_FIFOERRIE (0x1u << 4) /**< \brief (LCDC_LCDIER) Output FIFO Error Interrupt Enable Register */
#define LCDC_LCDIER_BASEIE (0x1u << 8) /**< \brief (LCDC_LCDIER) Base Layer Interrupt Enable Register */
#define LCDC_LCDIER_OVR1IE (0x1u << 9) /**< \brief (LCDC_LCDIER) Overlay 1 Interrupt Enable Register */
#define LCDC_LCDIER_HEOIE (0x1u << 10) /**< \brief (LCDC_LCDIER) High End Overlay Interrupt Enable Register */
#define LCDC_LCDIER_HCRIE (0x1u << 11) /**< \brief (LCDC_LCDIER) Hardware Cursor Interrupt Enable Register */
/* -------- LCDC_LCDIDR : (LCDC Offset: 0x00000030) LCD Controller Interrupt Disable Register -------- */
#define LCDC_LCDIDR_SOFID (0x1u << 0) /**< \brief (LCDC_LCDIDR) Start of Frame Interrupt Disable Register */
#define LCDC_LCDIDR_DISID (0x1u << 1) /**< \brief (LCDC_LCDIDR) LCD Disable Interrupt Disable Register */
#define LCDC_LCDIDR_DISPID (0x1u << 2) /**< \brief (LCDC_LCDIDR) Power UP/Down Sequence Terminated Interrupt Disable Register */
#define LCDC_LCDIDR_FIFOERRID (0x1u << 4) /**< \brief (LCDC_LCDIDR) Output FIFO Error Interrupt Disable Register */
#define LCDC_LCDIDR_BASEID (0x1u << 8) /**< \brief (LCDC_LCDIDR) Base Layer Interrupt Disable Register */
#define LCDC_LCDIDR_OVR1ID (0x1u << 9) /**< \brief (LCDC_LCDIDR) Overlay 1 Interrupt Disable Register */
#define LCDC_LCDIDR_HEOID (0x1u << 10) /**< \brief (LCDC_LCDIDR) High End Overlay Interrupt Disable Register */
#define LCDC_LCDIDR_HCRID (0x1u << 11) /**< \brief (LCDC_LCDIDR) Hardware Cursor Interrupt Disable Register */
/* -------- LCDC_LCDIMR : (LCDC Offset: 0x00000034) LCD Controller Interrupt Mask Register -------- */
#define LCDC_LCDIMR_SOFIM (0x1u << 0) /**< \brief (LCDC_LCDIMR) Start of Frame Interrupt Mask Register */
#define LCDC_LCDIMR_DISIM (0x1u << 1) /**< \brief (LCDC_LCDIMR) LCD Disable Interrupt Mask Register */
#define LCDC_LCDIMR_DISPIM (0x1u << 2) /**< \brief (LCDC_LCDIMR) Power UP/Down Sequence Terminated Interrupt Mask Register */
#define LCDC_LCDIMR_FIFOERRIM (0x1u << 4) /**< \brief (LCDC_LCDIMR) Output FIFO Error Interrupt Mask Register */
#define LCDC_LCDIMR_BASEIM (0x1u << 8) /**< \brief (LCDC_LCDIMR) Base Layer Interrupt Mask Register */
#define LCDC_LCDIMR_OVR1IM (0x1u << 9) /**< \brief (LCDC_LCDIMR) Overlay 1 Interrupt Mask Register */
#define LCDC_LCDIMR_HEOIM (0x1u << 10) /**< \brief (LCDC_LCDIMR) High End Overlay Interrupt Mask Register */
#define LCDC_LCDIMR_HCRIM (0x1u << 11) /**< \brief (LCDC_LCDIMR) Hardware Cursor Interrupt Mask Register */
/* -------- LCDC_LCDISR : (LCDC Offset: 0x00000038) LCD Controller Interrupt Status Register -------- */
#define LCDC_LCDISR_SOF (0x1u << 0) /**< \brief (LCDC_LCDISR) Start of Frame Interrupt Status Register */
#define LCDC_LCDISR_DIS (0x1u << 1) /**< \brief (LCDC_LCDISR) LCD Disable Interrupt Status Register */
#define LCDC_LCDISR_DISP (0x1u << 2) /**< \brief (LCDC_LCDISR) Power-up/Power-down Sequence Terminated Interrupt Status Register */
#define LCDC_LCDISR_FIFOERR (0x1u << 4) /**< \brief (LCDC_LCDISR) Output FIFO Error */
#define LCDC_LCDISR_BASE (0x1u << 8) /**< \brief (LCDC_LCDISR) Base Layer Raw Interrupt Status Register */
#define LCDC_LCDISR_OVR1 (0x1u << 9) /**< \brief (LCDC_LCDISR) Overlay 1 Raw Interrupt Status Register */
#define LCDC_LCDISR_HEO (0x1u << 10) /**< \brief (LCDC_LCDISR) High End Overlay Raw Interrupt Status Register */
#define LCDC_LCDISR_HCR (0x1u << 11) /**< \brief (LCDC_LCDISR) Hardware Cursor Raw Interrupt Status Register */
/* -------- LCDC_BASECHER : (LCDC Offset: 0x00000040) Base Layer Channel Enable Register -------- */
#define LCDC_BASECHER_CHEN (0x1u << 0) /**< \brief (LCDC_BASECHER) Channel Enable Register */
#define LCDC_BASECHER_UPDATEEN (0x1u << 1) /**< \brief (LCDC_BASECHER) Update Overlay Attributes Enable Register */
#define LCDC_BASECHER_A2QEN (0x1u << 2) /**< \brief (LCDC_BASECHER) Add To Queue Enable Register */
/* -------- LCDC_BASECHDR : (LCDC Offset: 0x00000044) Base Layer Channel Disable Register -------- */
#define LCDC_BASECHDR_CHDIS (0x1u << 0) /**< \brief (LCDC_BASECHDR) Channel Disable Register */
#define LCDC_BASECHDR_CHRST (0x1u << 8) /**< \brief (LCDC_BASECHDR) Channel Reset Register */
/* -------- LCDC_BASECHSR : (LCDC Offset: 0x00000048) Base Layer Channel Status Register -------- */
#define LCDC_BASECHSR_CHSR (0x1u << 0) /**< \brief (LCDC_BASECHSR) Channel Status Register */
#define LCDC_BASECHSR_UPDATESR (0x1u << 1) /**< \brief (LCDC_BASECHSR) Update Overlay Attributes In Progress Status Register */
#define LCDC_BASECHSR_A2QSR (0x1u << 2) /**< \brief (LCDC_BASECHSR) Add To Queue Status Register */
/* -------- LCDC_BASEIER : (LCDC Offset: 0x0000004C) Base Layer Interrupt Enable Register -------- */
#define LCDC_BASEIER_DMA (0x1u << 2) /**< \brief (LCDC_BASEIER) End of DMA Transfer Interrupt Enable Register */
#define LCDC_BASEIER_DSCR (0x1u << 3) /**< \brief (LCDC_BASEIER) Descriptor Loaded Interrupt Enable Register */
#define LCDC_BASEIER_ADD (0x1u << 4) /**< \brief (LCDC_BASEIER) Head Descriptor Loaded Interrupt Enable Register */
#define LCDC_BASEIER_DONE (0x1u << 5) /**< \brief (LCDC_BASEIER) End of List Interrupt Enable Register */
#define LCDC_BASEIER_OVR (0x1u << 6) /**< \brief (LCDC_BASEIER) Overflow Interrupt Enable Register */
/* -------- LCDC_BASEIDR : (LCDC Offset: 0x00000050) Base Layer Interrupt Disabled Register -------- */
#define LCDC_BASEIDR_DMA (0x1u << 2) /**< \brief (LCDC_BASEIDR) End of DMA Transfer Interrupt Disable Register */
#define LCDC_BASEIDR_DSCR (0x1u << 3) /**< \brief (LCDC_BASEIDR) Descriptor Loaded Interrupt Disable Register */
#define LCDC_BASEIDR_ADD (0x1u << 4) /**< \brief (LCDC_BASEIDR) Head Descriptor Loaded Interrupt Disable Register */
#define LCDC_BASEIDR_DONE (0x1u << 5) /**< \brief (LCDC_BASEIDR) End of List Interrupt Disable Register */
#define LCDC_BASEIDR_OVR (0x1u << 6) /**< \brief (LCDC_BASEIDR) Overflow Interrupt Disable Register */
/* -------- LCDC_BASEIMR : (LCDC Offset: 0x00000054) Base Layer Interrupt Mask Register -------- */
#define LCDC_BASEIMR_DMA (0x1u << 2) /**< \brief (LCDC_BASEIMR) End of DMA Transfer Interrupt Mask Register */
#define LCDC_BASEIMR_DSCR (0x1u << 3) /**< \brief (LCDC_BASEIMR) Descriptor Loaded Interrupt Mask Register */
#define LCDC_BASEIMR_ADD (0x1u << 4) /**< \brief (LCDC_BASEIMR) Head Descriptor Loaded Interrupt Mask Register */
#define LCDC_BASEIMR_DONE (0x1u << 5) /**< \brief (LCDC_BASEIMR) End of List Interrupt Mask Register */
#define LCDC_BASEIMR_OVR (0x1u << 6) /**< \brief (LCDC_BASEIMR) Overflow Interrupt Mask Register */
/* -------- LCDC_BASEISR : (LCDC Offset: 0x00000058) Base Layer Interrupt Status Register -------- */
#define LCDC_BASEISR_DMA (0x1u << 2) /**< \brief (LCDC_BASEISR) End of DMA Transfer */
#define LCDC_BASEISR_DSCR (0x1u << 3) /**< \brief (LCDC_BASEISR) DMA Descriptor Loaded */
#define LCDC_BASEISR_ADD (0x1u << 4) /**< \brief (LCDC_BASEISR) Head Descriptor Loaded */
#define LCDC_BASEISR_DONE (0x1u << 5) /**< \brief (LCDC_BASEISR) End of List Detected */
#define LCDC_BASEISR_OVR (0x1u << 6) /**< \brief (LCDC_BASEISR) Overflow Detected */
/* -------- LCDC_BASEHEAD : (LCDC Offset: 0x0000005C) Base Layer DMA Head Register -------- */
#define LCDC_BASEHEAD_HEAD_Pos 2
#define LCDC_BASEHEAD_HEAD_Msk (0x3fffffffu << LCDC_BASEHEAD_HEAD_Pos) /**< \brief (LCDC_BASEHEAD) DMA Head Pointer */
#define LCDC_BASEHEAD_HEAD(value) ((LCDC_BASEHEAD_HEAD_Msk & ((value) << LCDC_BASEHEAD_HEAD_Pos)))
/* -------- LCDC_BASEADDR : (LCDC Offset: 0x00000060) Base Layer DMA Address Register -------- */
#define LCDC_BASEADDR_ADDR_Pos 0
#define LCDC_BASEADDR_ADDR_Msk (0xffffffffu << LCDC_BASEADDR_ADDR_Pos) /**< \brief (LCDC_BASEADDR) DMA Transfer Start Address */
#define LCDC_BASEADDR_ADDR(value) ((LCDC_BASEADDR_ADDR_Msk & ((value) << LCDC_BASEADDR_ADDR_Pos)))
/* -------- LCDC_BASECTRL : (LCDC Offset: 0x00000064) Base Layer DMA Control Register -------- */
#define LCDC_BASECTRL_DFETCH (0x1u << 0) /**< \brief (LCDC_BASECTRL) Transfer Descriptor Fetch Enable */
#define LCDC_BASECTRL_LFETCH (0x1u << 1) /**< \brief (LCDC_BASECTRL) Lookup Table Fetch Enable */
#define LCDC_BASECTRL_DMAIEN (0x1u << 2) /**< \brief (LCDC_BASECTRL) End of DMA Transfer Interrupt Enable */
#define LCDC_BASECTRL_DSCRIEN (0x1u << 3) /**< \brief (LCDC_BASECTRL) Descriptor Loaded Interrupt Enable */
#define LCDC_BASECTRL_ADDIEN (0x1u << 4) /**< \brief (LCDC_BASECTRL) Add Head Descriptor to Queue Interrupt Enable */
#define LCDC_BASECTRL_DONEIEN (0x1u << 5) /**< \brief (LCDC_BASECTRL) End of List Interrupt Enable */
/* -------- LCDC_BASENEXT : (LCDC Offset: 0x00000068) Base Layer DMA Next Register -------- */
#define LCDC_BASENEXT_NEXT_Pos 0
#define LCDC_BASENEXT_NEXT_Msk (0xffffffffu << LCDC_BASENEXT_NEXT_Pos) /**< \brief (LCDC_BASENEXT) DMA Descriptor Next Address */
#define LCDC_BASENEXT_NEXT(value) ((LCDC_BASENEXT_NEXT_Msk & ((value) << LCDC_BASENEXT_NEXT_Pos)))
/* -------- LCDC_BASECFG0 : (LCDC Offset: 0x0000006C) Base Layer Configuration Register 0 -------- */
#define LCDC_BASECFG0_BLEN_Pos 4
#define LCDC_BASECFG0_BLEN_Msk (0x3u << LCDC_BASECFG0_BLEN_Pos) /**< \brief (LCDC_BASECFG0) AHB Burst Length */
#define LCDC_BASECFG0_BLEN(value) ((LCDC_BASECFG0_BLEN_Msk & ((value) << LCDC_BASECFG0_BLEN_Pos)))
#define   LCDC_BASECFG0_BLEN_AHB_SINGLE (0x0u << 4) /**< \brief (LCDC_BASECFG0) AHB Access is started as soon as there is enough space in the FIFO to store one data. SINGLE, INCR, INCR4, INCR8 and INCR16 bursts are used. INCR is used for a burst of 2 and 3 beats. */
#define   LCDC_BASECFG0_BLEN_AHB_INCR4 (0x1u << 4) /**< \brief (LCDC_BASECFG0) AHB Access is started as soon as there is enough space in the FIFO to store a total amount of 4 data. An AHB INCR4 Burst is used. SINGLE, INCR and INCR4 bursts are used. INCR is used for a burst of 2 and 3 beats. */
#define   LCDC_BASECFG0_BLEN_AHB_INCR8 (0x2u << 4) /**< \brief (LCDC_BASECFG0) AHB Access is started as soon as there is enough space in the FIFO to store a total amount of 8 data. An AHB INCR8 Burst is used. SINGLE, INCR, INCR4 and INCR8 bursts are used. INCR is used for a burst of 2 and 3 beats. */
#define   LCDC_BASECFG0_BLEN_AHB_INCR16 (0x3u << 4) /**< \brief (LCDC_BASECFG0) AHB Access is started as soon as there is enough space in the FIFO to store a total amount of 16 data. An AHB INCR16 Burst is used. SINGLE, INCR, INCR4, INCR8 and INCR16 bursts are used. INCR is used for a burst of 2 and 3 beats. */
#define LCDC_BASECFG0_DLBO (0x1u << 8) /**< \brief (LCDC_BASECFG0) Defined Length Burst Only For Channel Bus Transaction */
/* -------- LCDC_BASECFG1 : (LCDC Offset: 0x00000070) Base Layer Configuration Register 1 -------- */
#define LCDC_BASECFG1_CLUTEN (0x1u << 0) /**< \brief (LCDC_BASECFG1) Color Lookup Table Enable */
#define LCDC_BASECFG1_RGBMODE_Pos 4
#define LCDC_BASECFG1_RGBMODE_Msk (0xfu << LCDC_BASECFG1_RGBMODE_Pos) /**< \brief (LCDC_BASECFG1) RGB Mode Input Selection */
#define LCDC_BASECFG1_RGBMODE(value) ((LCDC_BASECFG1_RGBMODE_Msk & ((value) << LCDC_BASECFG1_RGBMODE_Pos)))
#define   LCDC_BASECFG1_RGBMODE_12BPP_RGB_444 (0x0u << 4) /**< \brief (LCDC_BASECFG1) 12 bpp RGB 444 */
#define   LCDC_BASECFG1_RGBMODE_16BPP_ARGB_4444 (0x1u << 4) /**< \brief (LCDC_BASECFG1) 16 bpp ARGB 4444 */
#define   LCDC_BASECFG1_RGBMODE_16BPP_RGBA_4444 (0x2u << 4) /**< \brief (LCDC_BASECFG1) 16 bpp RGBA 4444 */
#define   LCDC_BASECFG1_RGBMODE_16BPP_RGB_565 (0x3u << 4) /**< \brief (LCDC_BASECFG1) 16 bpp RGB 565 */
#define   LCDC_BASECFG1_RGBMODE_16BPP_TRGB_1555 (0x4u << 4) /**< \brief (LCDC_BASECFG1) 16 bpp TRGB 1555 */
#define   LCDC_BASECFG1_RGBMODE_18BPP_RGB_666 (0x5u << 4) /**< \brief (LCDC_BASECFG1) 18 bpp RGB 666 */
#define   LCDC_BASECFG1_RGBMODE_18BPP_RGB_666_PACKED (0x6u << 4) /**< \brief (LCDC_BASECFG1) 18 bpp RGB 666 PACKED */
#define   LCDC_BASECFG1_RGBMODE_19BPP_TRGB_1666 (0x7u << 4) /**< \brief (LCDC_BASECFG1) 19 bpp TRGB 1666 */
#define   LCDC_BASECFG1_RGBMODE_19BPP_TRGB_PACKED (0x8u << 4) /**< \brief (LCDC_BASECFG1) 19 bpp TRGB 1666 PACKED */
#define   LCDC_BASECFG1_RGBMODE_24BPP_RGB_888 (0x9u << 4) /**< \brief (LCDC_BASECFG1) 24 bpp RGB 888 */
#define   LCDC_BASECFG1_RGBMODE_24BPP_RGB_888_PACKED (0xAu << 4) /**< \brief (LCDC_BASECFG1) 24 bpp RGB 888 PACKED */
#define   LCDC_BASECFG1_RGBMODE_25BPP_TRGB_1888 (0xBu << 4) /**< \brief (LCDC_BASECFG1) 25 bpp TRGB 1888 */
#define   LCDC_BASECFG1_RGBMODE_32BPP_ARGB_8888 (0xCu << 4) /**< \brief (LCDC_BASECFG1) 32 bpp ARGB 8888 */
#define   LCDC_BASECFG1_RGBMODE_32BPP_RGBA_8888 (0xDu << 4) /**< \brief (LCDC_BASECFG1) 32 bpp RGBA 8888 */
#define LCDC_BASECFG1_CLUTMODE_Pos 8
#define LCDC_BASECFG1_CLUTMODE_Msk (0x3u << LCDC_BASECFG1_CLUTMODE_Pos) /**< \brief (LCDC_BASECFG1) Color Lookup Table Mode Input Selection */
#define LCDC_BASECFG1_CLUTMODE(value) ((LCDC_BASECFG1_CLUTMODE_Msk & ((value) << LCDC_BASECFG1_CLUTMODE_Pos)))
#define   LCDC_BASECFG1_CLUTMODE_1BPP (0x0u << 8) /**< \brief (LCDC_BASECFG1) Color lookup table mode set to 1 bit per pixel */
#define   LCDC_BASECFG1_CLUTMODE_2BPP (0x1u << 8) /**< \brief (LCDC_BASECFG1) Color lookup table mode set to 2 bits per pixel */
#define   LCDC_BASECFG1_CLUTMODE_4BPP (0x2u << 8) /**< \brief (LCDC_BASECFG1) Color lookup table mode set to 4 bits per pixel */
#define   LCDC_BASECFG1_CLUTMODE_8BPP (0x3u << 8) /**< \brief (LCDC_BASECFG1) Color lookup table mode set to 8 bits per pixel */
/* -------- LCDC_BASECFG2 : (LCDC Offset: 0x00000074) Base Layer Configuration Register 2 -------- */
#define LCDC_BASECFG2_XSTRIDE_Pos 0
#define LCDC_BASECFG2_XSTRIDE_Msk (0xffffffffu << LCDC_BASECFG2_XSTRIDE_Pos) /**< \brief (LCDC_BASECFG2) Horizontal Stride */
#define LCDC_BASECFG2_XSTRIDE(value) ((LCDC_BASECFG2_XSTRIDE_Msk & ((value) << LCDC_BASECFG2_XSTRIDE_Pos)))
/* -------- LCDC_BASECFG3 : (LCDC Offset: 0x00000078) Base Layer Configuration Register 3 -------- */
#define LCDC_BASECFG3_BDEF_Pos 0
#define LCDC_BASECFG3_BDEF_Msk (0xffu << LCDC_BASECFG3_BDEF_Pos) /**< \brief (LCDC_BASECFG3) Blue Default */
#define LCDC_BASECFG3_BDEF(value) ((LCDC_BASECFG3_BDEF_Msk & ((value) << LCDC_BASECFG3_BDEF_Pos)))
#define LCDC_BASECFG3_GDEF_Pos 8
#define LCDC_BASECFG3_GDEF_Msk (0xffu << LCDC_BASECFG3_GDEF_Pos) /**< \brief (LCDC_BASECFG3) Green Default */
#define LCDC_BASECFG3_GDEF(value) ((LCDC_BASECFG3_GDEF_Msk & ((value) << LCDC_BASECFG3_GDEF_Pos)))
#define LCDC_BASECFG3_RDEF_Pos 16
#define LCDC_BASECFG3_RDEF_Msk (0xffu << LCDC_BASECFG3_RDEF_Pos) /**< \brief (LCDC_BASECFG3) Red Default */
#define LCDC_BASECFG3_RDEF(value) ((LCDC_BASECFG3_RDEF_Msk & ((value) << LCDC_BASECFG3_RDEF_Pos)))
/* -------- LCDC_BASECFG4 : (LCDC Offset: 0x0000007C) Base Layer Configuration Register 4 -------- */
#define LCDC_BASECFG4_DMA (0x1u << 8) /**< \brief (LCDC_BASECFG4) Use DMA Data Path */
#define LCDC_BASECFG4_REP (0x1u << 9) /**< \brief (LCDC_BASECFG4) Use Replication logic to expand RGB color to 24 bits */
/* -------- LCDC_OVR1CHER : (LCDC Offset: 0x00000100) Overlay 1 Channel Enable Register -------- */
#define LCDC_OVR1CHER_CHEN (0x1u << 0) /**< \brief (LCDC_OVR1CHER) Channel Enable Register */
#define LCDC_OVR1CHER_UPDATEEN (0x1u << 1) /**< \brief (LCDC_OVR1CHER) Update Overlay Attributes Enable Register */
#define LCDC_OVR1CHER_A2QEN (0x1u << 2) /**< \brief (LCDC_OVR1CHER) Add To Queue Enable Register */
/* -------- LCDC_OVR1CHDR : (LCDC Offset: 0x00000104) Overlay 1 Channel Disable Register -------- */
#define LCDC_OVR1CHDR_CHDIS (0x1u << 0) /**< \brief (LCDC_OVR1CHDR) Channel Disable Register */
#define LCDC_OVR1CHDR_CHRST (0x1u << 8) /**< \brief (LCDC_OVR1CHDR) Channel Reset Register */
/* -------- LCDC_OVR1CHSR : (LCDC Offset: 0x00000108) Overlay 1 Channel Status Register -------- */
#define LCDC_OVR1CHSR_CHSR (0x1u << 0) /**< \brief (LCDC_OVR1CHSR) Channel Status Register */
#define LCDC_OVR1CHSR_UPDATESR (0x1u << 1) /**< \brief (LCDC_OVR1CHSR) Update Overlay Attributes In Progress Status Register */
#define LCDC_OVR1CHSR_A2QSR (0x1u << 2) /**< \brief (LCDC_OVR1CHSR) Add To Queue Status Register */
/* -------- LCDC_OVR1IER : (LCDC Offset: 0x0000010C) Overlay 1 Interrupt Enable Register -------- */
#define LCDC_OVR1IER_DMA (0x1u << 2) /**< \brief (LCDC_OVR1IER) End of DMA Transfer Interrupt Enable Register */
#define LCDC_OVR1IER_DSCR (0x1u << 3) /**< \brief (LCDC_OVR1IER) Descriptor Loaded Interrupt Enable Register */
#define LCDC_OVR1IER_ADD (0x1u << 4) /**< \brief (LCDC_OVR1IER) Head Descriptor Loaded Interrupt Enable Register */
#define LCDC_OVR1IER_DONE (0x1u << 5) /**< \brief (LCDC_OVR1IER) End of List Interrupt Enable Register */
#define LCDC_OVR1IER_OVR (0x1u << 6) /**< \brief (LCDC_OVR1IER) Overflow Interrupt Enable Register */
/* -------- LCDC_OVR1IDR : (LCDC Offset: 0x00000110) Overlay 1 Interrupt Disable Register -------- */
#define LCDC_OVR1IDR_DMA (0x1u << 2) /**< \brief (LCDC_OVR1IDR) End of DMA Transfer Interrupt Disable Register */
#define LCDC_OVR1IDR_DSCR (0x1u << 3) /**< \brief (LCDC_OVR1IDR) Descriptor Loaded Interrupt Disable Register */
#define LCDC_OVR1IDR_ADD (0x1u << 4) /**< \brief (LCDC_OVR1IDR) Head Descriptor Loaded Interrupt Disable Register */
#define LCDC_OVR1IDR_DONE (0x1u << 5) /**< \brief (LCDC_OVR1IDR) End of List Interrupt Disable Register */
#define LCDC_OVR1IDR_OVR (0x1u << 6) /**< \brief (LCDC_OVR1IDR) Overflow Interrupt Disable Register */
/* -------- LCDC_OVR1IMR : (LCDC Offset: 0x00000114) Overlay 1 Interrupt Mask Register -------- */
#define LCDC_OVR1IMR_DMA (0x1u << 2) /**< \brief (LCDC_OVR1IMR) End of DMA Transfer Interrupt Mask Register */
#define LCDC_OVR1IMR_DSCR (0x1u << 3) /**< \brief (LCDC_OVR1IMR) Descriptor Loaded Interrupt Mask Register */
#define LCDC_OVR1IMR_ADD (0x1u << 4) /**< \brief (LCDC_OVR1IMR) Head Descriptor Loaded Interrupt Mask Register */
#define LCDC_OVR1IMR_DONE (0x1u << 5) /**< \brief (LCDC_OVR1IMR) End of List Interrupt Mask Register */
#define LCDC_OVR1IMR_OVR (0x1u << 6) /**< \brief (LCDC_OVR1IMR) Overflow Interrupt Mask Register */
/* -------- LCDC_OVR1ISR : (LCDC Offset: 0x00000118) Overlay 1 Interrupt Status Register -------- */
#define LCDC_OVR1ISR_DMA (0x1u << 2) /**< \brief (LCDC_OVR1ISR) End of DMA Transfer */
#define LCDC_OVR1ISR_DSCR (0x1u << 3) /**< \brief (LCDC_OVR1ISR) DMA Descriptor Loaded */
#define LCDC_OVR1ISR_ADD (0x1u << 4) /**< \brief (LCDC_OVR1ISR) Head Descriptor Loaded */
#define LCDC_OVR1ISR_DONE (0x1u << 5) /**< \brief (LCDC_OVR1ISR) End of List Detected */
#define LCDC_OVR1ISR_OVR (0x1u << 6) /**< \brief (LCDC_OVR1ISR) Overflow Detected */
/* -------- LCDC_OVR1HEAD : (LCDC Offset: 0x0000011C) Overlay 1 DMA Head Register -------- */
#define LCDC_OVR1HEAD_HEAD_Pos 2
#define LCDC_OVR1HEAD_HEAD_Msk (0x3fffffffu << LCDC_OVR1HEAD_HEAD_Pos) /**< \brief (LCDC_OVR1HEAD) DMA Head Pointer */
#define LCDC_OVR1HEAD_HEAD(value) ((LCDC_OVR1HEAD_HEAD_Msk & ((value) << LCDC_OVR1HEAD_HEAD_Pos)))
/* -------- LCDC_OVR1ADDR : (LCDC Offset: 0x00000120) Overlay 1 DMA Address Register -------- */
#define LCDC_OVR1ADDR_ADDR_Pos 0
#define LCDC_OVR1ADDR_ADDR_Msk (0xffffffffu << LCDC_OVR1ADDR_ADDR_Pos) /**< \brief (LCDC_OVR1ADDR) DMA Transfer Overlay 1 Address */
#define LCDC_OVR1ADDR_ADDR(value) ((LCDC_OVR1ADDR_ADDR_Msk & ((value) << LCDC_OVR1ADDR_ADDR_Pos)))
/* -------- LCDC_OVR1CTRL : (LCDC Offset: 0x00000124) Overlay 1 DMA Control Register -------- */
#define LCDC_OVR1CTRL_DFETCH (0x1u << 0) /**< \brief (LCDC_OVR1CTRL) Transfer Descriptor Fetch Enable */
#define LCDC_OVR1CTRL_LFETCH (0x1u << 1) /**< \brief (LCDC_OVR1CTRL) Lookup Table Fetch Enable */
#define LCDC_OVR1CTRL_DMAIEN (0x1u << 2) /**< \brief (LCDC_OVR1CTRL) End of DMA Transfer Interrupt Enable */
#define LCDC_OVR1CTRL_DSCRIEN (0x1u << 3) /**< \brief (LCDC_OVR1CTRL) Descriptor Loaded Interrupt Enable */
#define LCDC_OVR1CTRL_ADDIEN (0x1u << 4) /**< \brief (LCDC_OVR1CTRL) Add Head Descriptor to Queue Interrupt Enable */
#define LCDC_OVR1CTRL_DONEIEN (0x1u << 5) /**< \brief (LCDC_OVR1CTRL) End of List Interrupt Enable */
/* -------- LCDC_OVR1NEXT : (LCDC Offset: 0x00000128) Overlay 1 DMA Next Register -------- */
#define LCDC_OVR1NEXT_NEXT_Pos 0
#define LCDC_OVR1NEXT_NEXT_Msk (0xffffffffu << LCDC_OVR1NEXT_NEXT_Pos) /**< \brief (LCDC_OVR1NEXT) DMA Descriptor Next Address */
#define LCDC_OVR1NEXT_NEXT(value) ((LCDC_OVR1NEXT_NEXT_Msk & ((value) << LCDC_OVR1NEXT_NEXT_Pos)))
/* -------- LCDC_OVR1CFG0 : (LCDC Offset: 0x0000012C) Overlay 1 Configuration Register 0 -------- */
#define LCDC_OVR1CFG0_BLEN_Pos 4
#define LCDC_OVR1CFG0_BLEN_Msk (0x3u << LCDC_OVR1CFG0_BLEN_Pos) /**< \brief (LCDC_OVR1CFG0) AHB Burst Length */
#define LCDC_OVR1CFG0_BLEN(value) ((LCDC_OVR1CFG0_BLEN_Msk & ((value) << LCDC_OVR1CFG0_BLEN_Pos)))
#define   LCDC_OVR1CFG0_BLEN_AHB_SINGLE (0x0u << 4) /**< \brief (LCDC_OVR1CFG0) AHB Access is started as soon as there is enough space in the FIFO to store one data. SINGLE, INCR, INCR4, INCR8 and INCR16 bursts are used. INCR is used for a burst of 2 and 3 beats. */
#define   LCDC_OVR1CFG0_BLEN_AHB_INCR4 (0x1u << 4) /**< \brief (LCDC_OVR1CFG0) AHB Access is started as soon as there is enough space in the FIFO to store a total amount of 4 data. An AHB INCR4 Burst is used. SINGLE, INCR and INCR4 bursts are used. INCR is used for a burst of 2 and 3 beats. */
#define   LCDC_OVR1CFG0_BLEN_AHB_INCR8 (0x2u << 4) /**< \brief (LCDC_OVR1CFG0) AHB Access is started as soon as there is enough space in the FIFO to store a total amount of 8 data. An AHB INCR8 Burst is used. SINGLE, INCR, INCR4 and INCR8 bursts are used. INCR is used for a burst of 2 and 3 beats. */
#define   LCDC_OVR1CFG0_BLEN_AHB_INCR16 (0x3u << 4) /**< \brief (LCDC_OVR1CFG0) AHB Access is started as soon as there is enough space in the FIFO to store a total amount of 16 data. An AHB INCR16 Burst is used. SINGLE, INCR, INCR4, INCR8 and INCR16 bursts are used. INCR is used for a burst of 2 and 3 beats. */
#define LCDC_OVR1CFG0_DLBO (0x1u << 8) /**< \brief (LCDC_OVR1CFG0) Defined Length Burst Only for Channel Bus Transaction. */
#define LCDC_OVR1CFG0_ROTDIS (0x1u << 12) /**< \brief (LCDC_OVR1CFG0) Hardware Rotation Optimization Disable */
#define LCDC_OVR1CFG0_LOCKDIS (0x1u << 13) /**< \brief (LCDC_OVR1CFG0) Hardware Rotation Lock Disable */
/* -------- LCDC_OVR1CFG1 : (LCDC Offset: 0x00000130) Overlay 1 Configuration Register 1 -------- */
#define LCDC_OVR1CFG1_CLUTEN (0x1u << 0) /**< \brief (LCDC_OVR1CFG1) Color Lookup Table Mode Enable */
#define LCDC_OVR1CFG1_RGBMODE_Pos 4
#define LCDC_OVR1CFG1_RGBMODE_Msk (0xfu << LCDC_OVR1CFG1_RGBMODE_Pos) /**< \brief (LCDC_OVR1CFG1) RGB Mode Input Selection */
#define LCDC_OVR1CFG1_RGBMODE(value) ((LCDC_OVR1CFG1_RGBMODE_Msk & ((value) << LCDC_OVR1CFG1_RGBMODE_Pos)))
#define   LCDC_OVR1CFG1_RGBMODE_12BPP_RGB_444 (0x0u << 4) /**< \brief (LCDC_OVR1CFG1) 12 bpp RGB 444 */
#define   LCDC_OVR1CFG1_RGBMODE_16BPP_ARGB_4444 (0x1u << 4) /**< \brief (LCDC_OVR1CFG1) 16 bpp ARGB 4444 */
#define   LCDC_OVR1CFG1_RGBMODE_16BPP_RGBA_4444 (0x2u << 4) /**< \brief (LCDC_OVR1CFG1) 16 bpp RGBA 4444 */
#define   LCDC_OVR1CFG1_RGBMODE_16BPP_RGB_565 (0x3u << 4) /**< \brief (LCDC_OVR1CFG1) 16 bpp RGB 565 */
#define   LCDC_OVR1CFG1_RGBMODE_16BPP_TRGB_1555 (0x4u << 4) /**< \brief (LCDC_OVR1CFG1) 16 bpp TRGB 1555 */
#define   LCDC_OVR1CFG1_RGBMODE_18BPP_RGB_666 (0x5u << 4) /**< \brief (LCDC_OVR1CFG1) 18 bpp RGB 666 */
#define   LCDC_OVR1CFG1_RGBMODE_18BPP_RGB_666_PACKED (0x6u << 4) /**< \brief (LCDC_OVR1CFG1) 18 bpp RGB 666 PACKED */
#define   LCDC_OVR1CFG1_RGBMODE_19BPP_TRGB_1666 (0x7u << 4) /**< \brief (LCDC_OVR1CFG1) 19 bpp TRGB 1666 */
#define   LCDC_OVR1CFG1_RGBMODE_19BPP_TRGB_PACKED (0x8u << 4) /**< \brief (LCDC_OVR1CFG1) 19 bpp TRGB 1666 PACKED */
#define   LCDC_OVR1CFG1_RGBMODE_24BPP_RGB_888 (0x9u << 4) /**< \brief (LCDC_OVR1CFG1) 24 bpp RGB 888 */
#define   LCDC_OVR1CFG1_RGBMODE_24BPP_RGB_888_PACKED (0xAu << 4) /**< \brief (LCDC_OVR1CFG1) 24 bpp RGB 888 PACKED */
#define   LCDC_OVR1CFG1_RGBMODE_25BPP_TRGB_1888 (0xBu << 4) /**< \brief (LCDC_OVR1CFG1) 25 bpp TRGB 1888 */
#define   LCDC_OVR1CFG1_RGBMODE_32BPP_ARGB_8888 (0xCu << 4) /**< \brief (LCDC_OVR1CFG1) 32 bpp ARGB 8888 */
#define   LCDC_OVR1CFG1_RGBMODE_32BPP_RGBA_8888 (0xDu << 4) /**< \brief (LCDC_OVR1CFG1) 32 bpp RGBA 8888 */
#define LCDC_OVR1CFG1_CLUTMODE_Pos 8
#define LCDC_OVR1CFG1_CLUTMODE_Msk (0x3u << LCDC_OVR1CFG1_CLUTMODE_Pos) /**< \brief (LCDC_OVR1CFG1) Color Lookup Table Mode Input Selection */
#define LCDC_OVR1CFG1_CLUTMODE(value) ((LCDC_OVR1CFG1_CLUTMODE_Msk & ((value) << LCDC_OVR1CFG1_CLUTMODE_Pos)))
#define   LCDC_OVR1CFG1_CLUTMODE_1BPP (0x0u << 8) /**< \brief (LCDC_OVR1CFG1) Color lookup table mode set to 1 bit per pixel */
#define   LCDC_OVR1CFG1_CLUTMODE_2BPP (0x1u << 8) /**< \brief (LCDC_OVR1CFG1) Color lookup table mode set to 2 bits per pixel */
#define   LCDC_OVR1CFG1_CLUTMODE_4BPP (0x2u << 8) /**< \brief (LCDC_OVR1CFG1) Color lookup table mode set to 4 bits per pixel */
#define   LCDC_OVR1CFG1_CLUTMODE_8BPP (0x3u << 8) /**< \brief (LCDC_OVR1CFG1) Color lookup table mode set to 8 bits per pixel */
/* -------- LCDC_OVR1CFG2 : (LCDC Offset: 0x00000134) Overlay 1 Configuration Register 2 -------- */
#define LCDC_OVR1CFG2_XPOS_Pos 0
#define LCDC_OVR1CFG2_XPOS_Msk (0x7ffu << LCDC_OVR1CFG2_XPOS_Pos) /**< \brief (LCDC_OVR1CFG2) Horizontal Window Position */
#define LCDC_OVR1CFG2_XPOS(value) ((LCDC_OVR1CFG2_XPOS_Msk & ((value) << LCDC_OVR1CFG2_XPOS_Pos)))
#define LCDC_OVR1CFG2_YPOS_Pos 16
#define LCDC_OVR1CFG2_YPOS_Msk (0x7ffu << LCDC_OVR1CFG2_YPOS_Pos) /**< \brief (LCDC_OVR1CFG2) Vertical Window Position */
#define LCDC_OVR1CFG2_YPOS(value) ((LCDC_OVR1CFG2_YPOS_Msk & ((value) << LCDC_OVR1CFG2_YPOS_Pos)))
/* -------- LCDC_OVR1CFG3 : (LCDC Offset: 0x00000138) Overlay 1 Configuration Register 3 -------- */
#define LCDC_OVR1CFG3_XSIZE_Pos 0
#define LCDC_OVR1CFG3_XSIZE_Msk (0x7ffu << LCDC_OVR1CFG3_XSIZE_Pos) /**< \brief (LCDC_OVR1CFG3) Horizontal Window Size */
#define LCDC_OVR1CFG3_XSIZE(value) ((LCDC_OVR1CFG3_XSIZE_Msk & ((value) << LCDC_OVR1CFG3_XSIZE_Pos)))
#define LCDC_OVR1CFG3_YSIZE_Pos 16
#define LCDC_OVR1CFG3_YSIZE_Msk (0x7ffu << LCDC_OVR1CFG3_YSIZE_Pos) /**< \brief (LCDC_OVR1CFG3) Vertical Window Size */
#define LCDC_OVR1CFG3_YSIZE(value) ((LCDC_OVR1CFG3_YSIZE_Msk & ((value) << LCDC_OVR1CFG3_YSIZE_Pos)))
/* -------- LCDC_OVR1CFG4 : (LCDC Offset: 0x0000013C) Overlay 1 Configuration Register 4 -------- */
#define LCDC_OVR1CFG4_XSTRIDE_Pos 0
#define LCDC_OVR1CFG4_XSTRIDE_Msk (0xffffffffu << LCDC_OVR1CFG4_XSTRIDE_Pos) /**< \brief (LCDC_OVR1CFG4) Horizontal Stride */
#define LCDC_OVR1CFG4_XSTRIDE(value) ((LCDC_OVR1CFG4_XSTRIDE_Msk & ((value) << LCDC_OVR1CFG4_XSTRIDE_Pos)))
/* -------- LCDC_OVR1CFG5 : (LCDC Offset: 0x00000140) Overlay 1 Configuration Register 5 -------- */
#define LCDC_OVR1CFG5_PSTRIDE_Pos 0
#define LCDC_OVR1CFG5_PSTRIDE_Msk (0xffffffffu << LCDC_OVR1CFG5_PSTRIDE_Pos) /**< \brief (LCDC_OVR1CFG5) Pixel Stride */
#define LCDC_OVR1CFG5_PSTRIDE(value) ((LCDC_OVR1CFG5_PSTRIDE_Msk & ((value) << LCDC_OVR1CFG5_PSTRIDE_Pos)))
/* -------- LCDC_OVR1CFG6 : (LCDC Offset: 0x00000144) Overlay 1 Configuration Register 6 -------- */
#define LCDC_OVR1CFG6_BDEF_Pos 0
#define LCDC_OVR1CFG6_BDEF_Msk (0xffu << LCDC_OVR1CFG6_BDEF_Pos) /**< \brief (LCDC_OVR1CFG6) Blue Default */
#define LCDC_OVR1CFG6_BDEF(value) ((LCDC_OVR1CFG6_BDEF_Msk & ((value) << LCDC_OVR1CFG6_BDEF_Pos)))
#define LCDC_OVR1CFG6_GDEF_Pos 8
#define LCDC_OVR1CFG6_GDEF_Msk (0xffu << LCDC_OVR1CFG6_GDEF_Pos) /**< \brief (LCDC_OVR1CFG6) Green Default */
#define LCDC_OVR1CFG6_GDEF(value) ((LCDC_OVR1CFG6_GDEF_Msk & ((value) << LCDC_OVR1CFG6_GDEF_Pos)))
#define LCDC_OVR1CFG6_RDEF_Pos 16
#define LCDC_OVR1CFG6_RDEF_Msk (0xffu << LCDC_OVR1CFG6_RDEF_Pos) /**< \brief (LCDC_OVR1CFG6) Red Default */
#define LCDC_OVR1CFG6_RDEF(value) ((LCDC_OVR1CFG6_RDEF_Msk & ((value) << LCDC_OVR1CFG6_RDEF_Pos)))
/* -------- LCDC_OVR1CFG7 : (LCDC Offset: 0x00000148) Overlay 1 Configuration Register 7 -------- */
#define LCDC_OVR1CFG7_BKEY_Pos 0
#define LCDC_OVR1CFG7_BKEY_Msk (0xffu << LCDC_OVR1CFG7_BKEY_Pos) /**< \brief (LCDC_OVR1CFG7) Blue Color Component Chroma Key */
#define LCDC_OVR1CFG7_BKEY(value) ((LCDC_OVR1CFG7_BKEY_Msk & ((value) << LCDC_OVR1CFG7_BKEY_Pos)))
#define LCDC_OVR1CFG7_GKEY_Pos 8
#define LCDC_OVR1CFG7_GKEY_Msk (0xffu << LCDC_OVR1CFG7_GKEY_Pos) /**< \brief (LCDC_OVR1CFG7) Green Color Component Chroma Key */
#define LCDC_OVR1CFG7_GKEY(value) ((LCDC_OVR1CFG7_GKEY_Msk & ((value) << LCDC_OVR1CFG7_GKEY_Pos)))
#define LCDC_OVR1CFG7_RKEY_Pos 16
#define LCDC_OVR1CFG7_RKEY_Msk (0xffu << LCDC_OVR1CFG7_RKEY_Pos) /**< \brief (LCDC_OVR1CFG7) Red Color Component Chroma Key */
#define LCDC_OVR1CFG7_RKEY(value) ((LCDC_OVR1CFG7_RKEY_Msk & ((value) << LCDC_OVR1CFG7_RKEY_Pos)))
/* -------- LCDC_OVR1CFG8 : (LCDC Offset: 0x0000014C) Overlay 1 Configuration Register 8 -------- */
#define LCDC_OVR1CFG8_BMASK_Pos 0
#define LCDC_OVR1CFG8_BMASK_Msk (0xffu << LCDC_OVR1CFG8_BMASK_Pos) /**< \brief (LCDC_OVR1CFG8) Blue Color Component Chroma Key Mask */
#define LCDC_OVR1CFG8_BMASK(value) ((LCDC_OVR1CFG8_BMASK_Msk & ((value) << LCDC_OVR1CFG8_BMASK_Pos)))
#define LCDC_OVR1CFG8_GMASK_Pos 8
#define LCDC_OVR1CFG8_GMASK_Msk (0xffu << LCDC_OVR1CFG8_GMASK_Pos) /**< \brief (LCDC_OVR1CFG8) Green Color Component Chroma Key Mask */
#define LCDC_OVR1CFG8_GMASK(value) ((LCDC_OVR1CFG8_GMASK_Msk & ((value) << LCDC_OVR1CFG8_GMASK_Pos)))
#define LCDC_OVR1CFG8_RMASK_Pos 16
#define LCDC_OVR1CFG8_RMASK_Msk (0xffu << LCDC_OVR1CFG8_RMASK_Pos) /**< \brief (LCDC_OVR1CFG8) Red Color Component Chroma Key Mask */
#define LCDC_OVR1CFG8_RMASK(value) ((LCDC_OVR1CFG8_RMASK_Msk & ((value) << LCDC_OVR1CFG8_RMASK_Pos)))
/* -------- LCDC_OVR1CFG9 : (LCDC Offset: 0x00000150) Overlay 1 Configuration Register 9 -------- */
#define LCDC_OVR1CFG9_CRKEY (0x1u << 0) /**< \brief (LCDC_OVR1CFG9) Blender Chroma Key Enable */
#define LCDC_OVR1CFG9_INV (0x1u << 1) /**< \brief (LCDC_OVR1CFG9) Blender Inverted Blender Output Enable */
#define LCDC_OVR1CFG9_ITER2BL (0x1u << 2) /**< \brief (LCDC_OVR1CFG9) Blender Iterated Color Enable */
#define LCDC_OVR1CFG9_ITER (0x1u << 3) /**< \brief (LCDC_OVR1CFG9) Blender Use Iterated Color */
#define LCDC_OVR1CFG9_REVALPHA (0x1u << 4) /**< \brief (LCDC_OVR1CFG9) Blender Reverse Alpha */
#define LCDC_OVR1CFG9_GAEN (0x1u << 5) /**< \brief (LCDC_OVR1CFG9) Blender Global Alpha Enable */
#define LCDC_OVR1CFG9_LAEN (0x1u << 6) /**< \brief (LCDC_OVR1CFG9) Blender Local Alpha Enable */
#define LCDC_OVR1CFG9_OVR (0x1u << 7) /**< \brief (LCDC_OVR1CFG9) Blender Overlay Layer Enable */
#define LCDC_OVR1CFG9_DMA (0x1u << 8) /**< \brief (LCDC_OVR1CFG9) Blender DMA Layer Enable */
#define LCDC_OVR1CFG9_REP (0x1u << 9) /**< \brief (LCDC_OVR1CFG9) Use Replication logic to expand RGB color to 24 bits */
#define LCDC_OVR1CFG9_DSTKEY (0x1u << 10) /**< \brief (LCDC_OVR1CFG9) Destination Chroma Keying */
#define LCDC_OVR1CFG9_GA_Pos 16
#define LCDC_OVR1CFG9_GA_Msk (0xffu << LCDC_OVR1CFG9_GA_Pos) /**< \brief (LCDC_OVR1CFG9) Blender Global Alpha */
#define LCDC_OVR1CFG9_GA(value) ((LCDC_OVR1CFG9_GA_Msk & ((value) << LCDC_OVR1CFG9_GA_Pos)))
/* -------- LCDC_HEOCHER : (LCDC Offset: 0x00000280) High End Overlay Channel Enable Register -------- */
#define LCDC_HEOCHER_CHEN (0x1u << 0) /**< \brief (LCDC_HEOCHER) Channel Enable Register */
#define LCDC_HEOCHER_UPDATEEN (0x1u << 1) /**< \brief (LCDC_HEOCHER) Update Overlay Attributes Enable Register */
#define LCDC_HEOCHER_A2QEN (0x1u << 2) /**< \brief (LCDC_HEOCHER) Add To Queue Enable Register */
/* -------- LCDC_HEOCHDR : (LCDC Offset: 0x00000284) High End Overlay Channel Disable Register -------- */
#define LCDC_HEOCHDR_CHDIS (0x1u << 0) /**< \brief (LCDC_HEOCHDR) Channel Disable Register */
#define LCDC_HEOCHDR_CHRST (0x1u << 8) /**< \brief (LCDC_HEOCHDR) Channel Reset Register */
/* -------- LCDC_HEOCHSR : (LCDC Offset: 0x00000288) High End Overlay Channel Status Register -------- */
#define LCDC_HEOCHSR_CHSR (0x1u << 0) /**< \brief (LCDC_HEOCHSR) Channel Status Register */
#define LCDC_HEOCHSR_UPDATESR (0x1u << 1) /**< \brief (LCDC_HEOCHSR) Update Overlay Attributes In Progress Status Register */
#define LCDC_HEOCHSR_A2QSR (0x1u << 2) /**< \brief (LCDC_HEOCHSR) Add To Queue Status Register */
/* -------- LCDC_HEOIER : (LCDC Offset: 0x0000028C) High End Overlay Interrupt Enable Register -------- */
#define LCDC_HEOIER_DMA (0x1u << 2) /**< \brief (LCDC_HEOIER) End of DMA Transfer Interrupt Enable Register */
#define LCDC_HEOIER_DSCR (0x1u << 3) /**< \brief (LCDC_HEOIER) Descriptor Loaded Interrupt Enable Register */
#define LCDC_HEOIER_ADD (0x1u << 4) /**< \brief (LCDC_HEOIER) Head Descriptor Loaded Interrupt Enable Register */
#define LCDC_HEOIER_DONE (0x1u << 5) /**< \brief (LCDC_HEOIER) End of List Interrupt Enable Register */
#define LCDC_HEOIER_OVR (0x1u << 6) /**< \brief (LCDC_HEOIER) Overflow Interrupt Enable Register */
#define LCDC_HEOIER_UDMA (0x1u << 10) /**< \brief (LCDC_HEOIER) End of DMA Transfer for U or UV Chrominance Interrupt Enable Register */
#define LCDC_HEOIER_UDSCR (0x1u << 11) /**< \brief (LCDC_HEOIER) Descriptor Loaded for U or UV Chrominance Interrupt Enable Register */
#define LCDC_HEOIER_UADD (0x1u << 12) /**< \brief (LCDC_HEOIER) Head Descriptor Loaded for U or UV Chrominance Interrupt Enable Register */
#define LCDC_HEOIER_UDONE (0x1u << 13) /**< \brief (LCDC_HEOIER) End of List for U or UV Chrominance Interrupt Enable Register */
#define LCDC_HEOIER_UOVR (0x1u << 14) /**< \brief (LCDC_HEOIER) Overflow for U or UV Chrominance Interrupt Enable Register */
#define LCDC_HEOIER_VDMA (0x1u << 18) /**< \brief (LCDC_HEOIER) End of DMA for V Chrominance Transfer Interrupt Enable Register */
#define LCDC_HEOIER_VDSCR (0x1u << 19) /**< \brief (LCDC_HEOIER) Descriptor Loaded for V Chrominance Interrupt Enable Register */
#define LCDC_HEOIER_VADD (0x1u << 20) /**< \brief (LCDC_HEOIER) Head Descriptor Loaded for V Chrominance Interrupt Enable Register */
#define LCDC_HEOIER_VDONE (0x1u << 21) /**< \brief (LCDC_HEOIER) End of List for V Chrominance Interrupt Enable Register */
#define LCDC_HEOIER_VOVR (0x1u << 22) /**< \brief (LCDC_HEOIER) Overflow for V Chrominance Interrupt Enable Register */
/* -------- LCDC_HEOIDR : (LCDC Offset: 0x00000290) High End Overlay Interrupt Disable Register -------- */
#define LCDC_HEOIDR_DMA (0x1u << 2) /**< \brief (LCDC_HEOIDR) End of DMA Transfer Interrupt Disable Register */
#define LCDC_HEOIDR_DSCR (0x1u << 3) /**< \brief (LCDC_HEOIDR) Descriptor Loaded Interrupt Disable Register */
#define LCDC_HEOIDR_ADD (0x1u << 4) /**< \brief (LCDC_HEOIDR) Head Descriptor Loaded Interrupt Disable Register */
#define LCDC_HEOIDR_DONE (0x1u << 5) /**< \brief (LCDC_HEOIDR) End of List Interrupt Disable Register */
#define LCDC_HEOIDR_OVR (0x1u << 6) /**< \brief (LCDC_HEOIDR) Overflow Interrupt Disable Register */
#define LCDC_HEOIDR_UDMA (0x1u << 10) /**< \brief (LCDC_HEOIDR) End of DMA Transfer for U or UV Chrominance Component Interrupt Disable Register */
#define LCDC_HEOIDR_UDSCR (0x1u << 11) /**< \brief (LCDC_HEOIDR) Descriptor Loaded for U or UV Chrominance Component Interrupt Disable Register */
#define LCDC_HEOIDR_UADD (0x1u << 12) /**< \brief (LCDC_HEOIDR) Head Descriptor Loaded for U or UV Chrominance Component Interrupt Disable Register */
#define LCDC_HEOIDR_UDONE (0x1u << 13) /**< \brief (LCDC_HEOIDR) End of List Interrupt for U or UV Chrominance Component Disable Register */
#define LCDC_HEOIDR_UOVR (0x1u << 14) /**< \brief (LCDC_HEOIDR) Overflow Interrupt for U or UV Chrominance Component Disable Register */
#define LCDC_HEOIDR_VDMA (0x1u << 18) /**< \brief (LCDC_HEOIDR) End of DMA Transfer for V Chrominance Component Interrupt Disable Register */
#define LCDC_HEOIDR_VDSCR (0x1u << 19) /**< \brief (LCDC_HEOIDR) Descriptor Loaded for V Chrominance Component Interrupt Disable Register */
#define LCDC_HEOIDR_VADD (0x1u << 20) /**< \brief (LCDC_HEOIDR) Head Descriptor Loaded for V Chrominance Component Interrupt Disable Register */
#define LCDC_HEOIDR_VDONE (0x1u << 21) /**< \brief (LCDC_HEOIDR) End of List for V Chrominance Component Interrupt Disable Register */
#define LCDC_HEOIDR_VOVR (0x1u << 22) /**< \brief (LCDC_HEOIDR) Overflow for V Chrominance Component Interrupt Disable Register */
/* -------- LCDC_HEOIMR : (LCDC Offset: 0x00000294) High End Overlay Interrupt Mask Register -------- */
#define LCDC_HEOIMR_DMA (0x1u << 2) /**< \brief (LCDC_HEOIMR) End of DMA Transfer Interrupt Mask Register */
#define LCDC_HEOIMR_DSCR (0x1u << 3) /**< \brief (LCDC_HEOIMR) Descriptor Loaded Interrupt Mask Register */
#define LCDC_HEOIMR_ADD (0x1u << 4) /**< \brief (LCDC_HEOIMR) Head Descriptor Loaded Interrupt Mask Register */
#define LCDC_HEOIMR_DONE (0x1u << 5) /**< \brief (LCDC_HEOIMR) End of List Interrupt Mask Register */
#define LCDC_HEOIMR_OVR (0x1u << 6) /**< \brief (LCDC_HEOIMR) Overflow Interrupt Mask Register */
#define LCDC_HEOIMR_UDMA (0x1u << 10) /**< \brief (LCDC_HEOIMR) End of DMA Transfer for U or UV Chrominance Component Interrupt Mask Register */
#define LCDC_HEOIMR_UDSCR (0x1u << 11) /**< \brief (LCDC_HEOIMR) Descriptor Loaded for U or UV Chrominance Component Interrupt Mask Register */
#define LCDC_HEOIMR_UADD (0x1u << 12) /**< \brief (LCDC_HEOIMR) Head Descriptor Loaded for U or UV Chrominance Component Mask Register */
#define LCDC_HEOIMR_UDONE (0x1u << 13) /**< \brief (LCDC_HEOIMR) End of List for U or UV Chrominance Component Mask Register */
#define LCDC_HEOIMR_UOVR (0x1u << 14) /**< \brief (LCDC_HEOIMR) Overflow for U Chrominance Interrupt Mask Register */
#define LCDC_HEOIMR_VDMA (0x1u << 18) /**< \brief (LCDC_HEOIMR) End of DMA Transfer for V Chrominance Component Interrupt Mask Register */
#define LCDC_HEOIMR_VDSCR (0x1u << 19) /**< \brief (LCDC_HEOIMR) Descriptor Loaded for V Chrominance Component Interrupt Mask Register */
#define LCDC_HEOIMR_VADD (0x1u << 20) /**< \brief (LCDC_HEOIMR) Head Descriptor Loaded for V Chrominance Component Mask Register */
#define LCDC_HEOIMR_VDONE (0x1u << 21) /**< \brief (LCDC_HEOIMR) End of List for V Chrominance Component Mask Register */
#define LCDC_HEOIMR_VOVR (0x1u << 22) /**< \brief (LCDC_HEOIMR) Overflow for V Chrominance Interrupt Mask Register */
/* -------- LCDC_HEOISR : (LCDC Offset: 0x00000298) High End Overlay Interrupt Status Register -------- */
#define LCDC_HEOISR_DMA (0x1u << 2) /**< \brief (LCDC_HEOISR) End of DMA Transfer */
#define LCDC_HEOISR_DSCR (0x1u << 3) /**< \brief (LCDC_HEOISR) DMA Descriptor Loaded */
#define LCDC_HEOISR_ADD (0x1u << 4) /**< \brief (LCDC_HEOISR) Head Descriptor Loaded */
#define LCDC_HEOISR_DONE (0x1u << 5) /**< \brief (LCDC_HEOISR) End of List Detected */
#define LCDC_HEOISR_OVR (0x1u << 6) /**< \brief (LCDC_HEOISR) Overflow Detected */
#define LCDC_HEOISR_UDMA (0x1u << 10) /**< \brief (LCDC_HEOISR) End of DMA Transfer for U Component */
#define LCDC_HEOISR_UDSCR (0x1u << 11) /**< \brief (LCDC_HEOISR) DMA Descriptor Loaded for U Component */
#define LCDC_HEOISR_UADD (0x1u << 12) /**< \brief (LCDC_HEOISR) Head Descriptor Loaded for U Component */
#define LCDC_HEOISR_UDONE (0x1u << 13) /**< \brief (LCDC_HEOISR) End of List Detected for U Component */
#define LCDC_HEOISR_UOVR (0x1u << 14) /**< \brief (LCDC_HEOISR) Overflow Detected for U Component */
#define LCDC_HEOISR_VDMA (0x1u << 18) /**< \brief (LCDC_HEOISR) End of DMA Transfer for V Component */
#define LCDC_HEOISR_VDSCR (0x1u << 19) /**< \brief (LCDC_HEOISR) DMA Descriptor Loaded for V Component */
#define LCDC_HEOISR_VADD (0x1u << 20) /**< \brief (LCDC_HEOISR) Head Descriptor Loaded for V Component */
#define LCDC_HEOISR_VDONE (0x1u << 21) /**< \brief (LCDC_HEOISR) End of List Detected for V Component */
#define LCDC_HEOISR_VOVR (0x1u << 22) /**< \brief (LCDC_HEOISR) Overflow Detected for V Component */
/* -------- LCDC_HEOHEAD : (LCDC Offset: 0x0000029C) High End Overlay DMA Head Register -------- */
#define LCDC_HEOHEAD_HEAD_Pos 2
#define LCDC_HEOHEAD_HEAD_Msk (0x3fffffffu << LCDC_HEOHEAD_HEAD_Pos) /**< \brief (LCDC_HEOHEAD) DMA Head Pointer */
#define LCDC_HEOHEAD_HEAD(value) ((LCDC_HEOHEAD_HEAD_Msk & ((value) << LCDC_HEOHEAD_HEAD_Pos)))
/* -------- LCDC_HEOADDR : (LCDC Offset: 0x000002A0) High End Overlay DMA Address Register -------- */
#define LCDC_HEOADDR_ADDR_Pos 0
#define LCDC_HEOADDR_ADDR_Msk (0xffffffffu << LCDC_HEOADDR_ADDR_Pos) /**< \brief (LCDC_HEOADDR) DMA Transfer start Address */
#define LCDC_HEOADDR_ADDR(value) ((LCDC_HEOADDR_ADDR_Msk & ((value) << LCDC_HEOADDR_ADDR_Pos)))
/* -------- LCDC_HEOCTRL : (LCDC Offset: 0x000002A4) High End Overlay DMA Control Register -------- */
#define LCDC_HEOCTRL_DFETCH (0x1u << 0) /**< \brief (LCDC_HEOCTRL) Transfer Descriptor Fetch Enable */
#define LCDC_HEOCTRL_LFETCH (0x1u << 1) /**< \brief (LCDC_HEOCTRL) Lookup Table Fetch Enable */
#define LCDC_HEOCTRL_DMAIEN (0x1u << 2) /**< \brief (LCDC_HEOCTRL) End of DMA Transfer Interrupt Enable */
#define LCDC_HEOCTRL_DSCRIEN (0x1u << 3) /**< \brief (LCDC_HEOCTRL) Descriptor Loaded Interrupt Enable */
#define LCDC_HEOCTRL_ADDIEN (0x1u << 4) /**< \brief (LCDC_HEOCTRL) Add Head Descriptor to Queue Interrupt Enable */
#define LCDC_HEOCTRL_DONEIEN (0x1u << 5) /**< \brief (LCDC_HEOCTRL) End of List Interrupt Enable */
/* -------- LCDC_HEONEXT : (LCDC Offset: 0x000002A8) High End Overlay DMA Next Register -------- */
#define LCDC_HEONEXT_NEXT_Pos 0
#define LCDC_HEONEXT_NEXT_Msk (0xffffffffu << LCDC_HEONEXT_NEXT_Pos) /**< \brief (LCDC_HEONEXT) DMA Descriptor Next Address */
#define LCDC_HEONEXT_NEXT(value) ((LCDC_HEONEXT_NEXT_Msk & ((value) << LCDC_HEONEXT_NEXT_Pos)))
/* -------- LCDC_HEOUHEAD : (LCDC Offset: 0x000002AC) High End Overlay U-UV DMA Head Register -------- */
#define LCDC_HEOUHEAD_UHEAD_Pos 0
#define LCDC_HEOUHEAD_UHEAD_Msk (0xffffffffu << LCDC_HEOUHEAD_UHEAD_Pos) /**< \brief (LCDC_HEOUHEAD) DMA Head Pointer */
#define LCDC_HEOUHEAD_UHEAD(value) ((LCDC_HEOUHEAD_UHEAD_Msk & ((value) << LCDC_HEOUHEAD_UHEAD_Pos)))
/* -------- LCDC_HEOUADDR : (LCDC Offset: 0x000002B0) High End Overlay U-UV DMA Address Register -------- */
#define LCDC_HEOUADDR_UADDR_Pos 0
#define LCDC_HEOUADDR_UADDR_Msk (0xffffffffu << LCDC_HEOUADDR_UADDR_Pos) /**< \brief (LCDC_HEOUADDR) DMA Transfer Start Address for U or UV Chrominance */
#define LCDC_HEOUADDR_UADDR(value) ((LCDC_HEOUADDR_UADDR_Msk & ((value) << LCDC_HEOUADDR_UADDR_Pos)))
/* -------- LCDC_HEOUCTRL : (LCDC Offset: 0x000002B4) High End Overlay U-UV DMA Control Register -------- */
#define LCDC_HEOUCTRL_UDFETCH (0x1u << 0) /**< \brief (LCDC_HEOUCTRL) Transfer Descriptor Fetch Enable */
#define LCDC_HEOUCTRL_UDMAIEN (0x1u << 2) /**< \brief (LCDC_HEOUCTRL) End of DMA Transfer Interrupt Enable */
#define LCDC_HEOUCTRL_UDSCRIEN (0x1u << 3) /**< \brief (LCDC_HEOUCTRL) Descriptor Loaded Interrupt Enable */
#define LCDC_HEOUCTRL_UADDIEN (0x1u << 4) /**< \brief (LCDC_HEOUCTRL) Add Head Descriptor to Queue Interrupt Enable */
#define LCDC_HEOUCTRL_UDONEIEN (0x1u << 5) /**< \brief (LCDC_HEOUCTRL) End of List Interrupt Enable */
/* -------- LCDC_HEOUNEXT : (LCDC Offset: 0x000002B8) High End Overlay U-UV DMA Next Register -------- */
#define LCDC_HEOUNEXT_UNEXT_Pos 0
#define LCDC_HEOUNEXT_UNEXT_Msk (0xffffffffu << LCDC_HEOUNEXT_UNEXT_Pos) /**< \brief (LCDC_HEOUNEXT) DMA Descriptor Next Address */
#define LCDC_HEOUNEXT_UNEXT(value) ((LCDC_HEOUNEXT_UNEXT_Msk & ((value) << LCDC_HEOUNEXT_UNEXT_Pos)))
/* -------- LCDC_HEOVHEAD : (LCDC Offset: 0x000002BC) High End Overlay V DMA Head Register -------- */
#define LCDC_HEOVHEAD_VHEAD_Pos 0
#define LCDC_HEOVHEAD_VHEAD_Msk (0xffffffffu << LCDC_HEOVHEAD_VHEAD_Pos) /**< \brief (LCDC_HEOVHEAD) DMA Head Pointer */
#define LCDC_HEOVHEAD_VHEAD(value) ((LCDC_HEOVHEAD_VHEAD_Msk & ((value) << LCDC_HEOVHEAD_VHEAD_Pos)))
/* -------- LCDC_HEOVADDR : (LCDC Offset: 0x000002C0) High End Overlay V DMA Address Register -------- */
#define LCDC_HEOVADDR_VADDR_Pos 0
#define LCDC_HEOVADDR_VADDR_Msk (0xffffffffu << LCDC_HEOVADDR_VADDR_Pos) /**< \brief (LCDC_HEOVADDR) DMA Transfer Start Address for V Chrominance */
#define LCDC_HEOVADDR_VADDR(value) ((LCDC_HEOVADDR_VADDR_Msk & ((value) << LCDC_HEOVADDR_VADDR_Pos)))
/* -------- LCDC_HEOVCTRL : (LCDC Offset: 0x000002C4) High End Overlay V DMA Control Register -------- */
#define LCDC_HEOVCTRL_VDFETCH (0x1u << 0) /**< \brief (LCDC_HEOVCTRL) Transfer Descriptor Fetch Enable */
#define LCDC_HEOVCTRL_VDMAIEN (0x1u << 2) /**< \brief (LCDC_HEOVCTRL) End of DMA Transfer Interrupt Enable */
#define LCDC_HEOVCTRL_VDSCRIEN (0x1u << 3) /**< \brief (LCDC_HEOVCTRL) Descriptor Loaded Interrupt Enable */
#define LCDC_HEOVCTRL_VADDIEN (0x1u << 4) /**< \brief (LCDC_HEOVCTRL) Add Head Descriptor to Queue Interrupt Enable */
#define LCDC_HEOVCTRL_VDONEIEN (0x1u << 5) /**< \brief (LCDC_HEOVCTRL) End of List Interrupt Enable */
/* -------- LCDC_HEOVNEXT : (LCDC Offset: 0x000002C8) High End Overlay V DMA Next Register -------- */
#define LCDC_HEOVNEXT_VNEXT_Pos 0
#define LCDC_HEOVNEXT_VNEXT_Msk (0xffffffffu << LCDC_HEOVNEXT_VNEXT_Pos) /**< \brief (LCDC_HEOVNEXT) DMA Descriptor Next Address */
#define LCDC_HEOVNEXT_VNEXT(value) ((LCDC_HEOVNEXT_VNEXT_Msk & ((value) << LCDC_HEOVNEXT_VNEXT_Pos)))
/* -------- LCDC_HEOCFG0 : (LCDC Offset: 0x000002CC) High End Overlay Configuration Register 0 -------- */
#define LCDC_HEOCFG0_BLEN_Pos 4
#define LCDC_HEOCFG0_BLEN_Msk (0x3u << LCDC_HEOCFG0_BLEN_Pos) /**< \brief (LCDC_HEOCFG0) AHB Burst Length */
#define LCDC_HEOCFG0_BLEN(value) ((LCDC_HEOCFG0_BLEN_Msk & ((value) << LCDC_HEOCFG0_BLEN_Pos)))
#define   LCDC_HEOCFG0_BLEN_AHB_SINGLE (0x0u << 4) /**< \brief (LCDC_HEOCFG0) AHB Access is started as soon as there is enough space in the FIFO to store one data. SINGLE, INCR, INCR4, INCR8 and INCR16 bursts are used. INCR is used for a burst of 2 and 3 beats. */
#define   LCDC_HEOCFG0_BLEN_AHB_INCR4 (0x1u << 4) /**< \brief (LCDC_HEOCFG0) AHB Access is started as soon as there is enough space in the FIFO to store a total amount of 4 data. An AHB INCR4 Burst is used. SINGLE, INCR and INCR4 bursts are used. INCR is used for a burst of 2 and 3 beats. */
#define   LCDC_HEOCFG0_BLEN_AHB_INCR8 (0x2u << 4) /**< \brief (LCDC_HEOCFG0) AHB Access is started as soon as there is enough space in the FIFO to store a total amount of 8 data. An AHB INCR8 Burst is used. SINGLE, INCR, INCR4 and INCR8 bursts are used. INCR is used for a burst of 2 and 3 beats. */
#define   LCDC_HEOCFG0_BLEN_AHB_INCR16 (0x3u << 4) /**< \brief (LCDC_HEOCFG0) AHB Access is started as soon as there is enough space in the FIFO to store a total amount of 16 data. An AHB INCR16 Burst is used. SINGLE, INCR, INCR4, INCR8 and INCR16 bursts are used. INCR is used for a burst of 2 and 3 beats. */
#define LCDC_HEOCFG0_BLENUV_Pos 6
#define LCDC_HEOCFG0_BLENUV_Msk (0x3u << LCDC_HEOCFG0_BLENUV_Pos) /**< \brief (LCDC_HEOCFG0) AHB Burst Length for U-V channel */
#define LCDC_HEOCFG0_BLENUV(value) ((LCDC_HEOCFG0_BLENUV_Msk & ((value) << LCDC_HEOCFG0_BLENUV_Pos)))
#define   LCDC_HEOCFG0_BLENUV_AHB_SINGLE (0x0u << 6) /**< \brief (LCDC_HEOCFG0) AHB Access is started as soon as there is enough space in the FIFO to store one data. SINGLE, INCR, INCR4, INCR8 and INCR16 bursts are used. INCR is used for a burst of 2 and 3 beats. */
#define   LCDC_HEOCFG0_BLENUV_AHB_INCR4 (0x1u << 6) /**< \brief (LCDC_HEOCFG0) AHB Access is started as soon as there is enough space in the FIFO to store a total amount of 4 data. An AHB INCR4 Burst is used. SINGLE, INCR and INCR4 bursts are used. INCR is used for a burst of 2 and 3 beats. */
#define   LCDC_HEOCFG0_BLENUV_AHB_INCR8 (0x2u << 6) /**< \brief (LCDC_HEOCFG0) AHB Access is started as soon as there is enough space in the FIFO to store a total amount of 8 data. An AHB INCR8 Burst is used. SINGLE, INCR, INCR4 and INCR8 bursts are used. INCR is used for a burst of 2 and 3 beats. */
#define   LCDC_HEOCFG0_BLENUV_AHB_INCR16 (0x3u << 6) /**< \brief (LCDC_HEOCFG0) AHB Access is started as soon as there is enough space in the FIFO to store a total amount of 16 data. An AHB INCR16 Burst is used. SINGLE, INCR, INCR4, INCR8 and INCR16 bursts are used. INCR is used for a burst of 2 and 3 beats. */
#define LCDC_HEOCFG0_DLBO (0x1u << 8) /**< \brief (LCDC_HEOCFG0) Defined Length Burst Only For Channel Bus Transaction. */
#define LCDC_HEOCFG0_ROTDIS (0x1u << 12) /**< \brief (LCDC_HEOCFG0) Hardware Rotation Optimization Disable */
#define LCDC_HEOCFG0_LOCKDIS (0x1u << 13) /**< \brief (LCDC_HEOCFG0) Hardware Rotation Lock Disable */
/* -------- LCDC_HEOCFG1 : (LCDC Offset: 0x000002D0) High End Overlay Configuration Register 1 -------- */
#define LCDC_HEOCFG1_CLUTEN (0x1u << 0) /**< \brief (LCDC_HEOCFG1) Color Lookup Table Mode Enable */
#define LCDC_HEOCFG1_YUVEN (0x1u << 1) /**< \brief (LCDC_HEOCFG1) YUV Color Space Enable */
#define LCDC_HEOCFG1_RGBMODE_Pos 4
#define LCDC_HEOCFG1_RGBMODE_Msk (0xfu << LCDC_HEOCFG1_RGBMODE_Pos) /**< \brief (LCDC_HEOCFG1) RGB input mode selection */
#define LCDC_HEOCFG1_RGBMODE(value) ((LCDC_HEOCFG1_RGBMODE_Msk & ((value) << LCDC_HEOCFG1_RGBMODE_Pos)))
#define   LCDC_HEOCFG1_RGBMODE_12BPP_RGB_444 (0x0u << 4) /**< \brief (LCDC_HEOCFG1) 12 bpp RGB 444 */
#define   LCDC_HEOCFG1_RGBMODE_16BPP_ARGB_4444 (0x1u << 4) /**< \brief (LCDC_HEOCFG1) 16 bpp ARGB 4444 */
#define   LCDC_HEOCFG1_RGBMODE_16BPP_RGBA_4444 (0x2u << 4) /**< \brief (LCDC_HEOCFG1) 16 bpp RGBA 4444 */
#define   LCDC_HEOCFG1_RGBMODE_16BPP_RGB_565 (0x3u << 4) /**< \brief (LCDC_HEOCFG1) 16 bpp RGB 565 */
#define   LCDC_HEOCFG1_RGBMODE_16BPP_TRGB_1555 (0x4u << 4) /**< \brief (LCDC_HEOCFG1) 16 bpp TRGB 1555 */
#define   LCDC_HEOCFG1_RGBMODE_18BPP_RGB_666 (0x5u << 4) /**< \brief (LCDC_HEOCFG1) 18 bpp RGB 666 */
#define   LCDC_HEOCFG1_RGBMODE_18BPP_RGB_666_PACKED (0x6u << 4) /**< \brief (LCDC_HEOCFG1) 18 bpp RGB 666 PACKED */
#define   LCDC_HEOCFG1_RGBMODE_19BPP_TRGB_1666 (0x7u << 4) /**< \brief (LCDC_HEOCFG1) 19 bpp TRGB 1666 */
#define   LCDC_HEOCFG1_RGBMODE_19BPP_TRGB_PACKED (0x8u << 4) /**< \brief (LCDC_HEOCFG1) 19 bpp TRGB 1666 PACKED */
#define   LCDC_HEOCFG1_RGBMODE_24BPP_RGB_888 (0x9u << 4) /**< \brief (LCDC_HEOCFG1) 24 bpp RGB 888 */
#define   LCDC_HEOCFG1_RGBMODE_24BPP_RGB_888_PACKED (0xAu << 4) /**< \brief (LCDC_HEOCFG1) 24 bpp RGB 888 PACKED */
#define   LCDC_HEOCFG1_RGBMODE_25BPP_TRGB_1888 (0xBu << 4) /**< \brief (LCDC_HEOCFG1) 25 bpp TRGB 1888 */
#define   LCDC_HEOCFG1_RGBMODE_32BPP_ARGB_8888 (0xCu << 4) /**< \brief (LCDC_HEOCFG1) 32 bpp ARGB 8888 */
#define   LCDC_HEOCFG1_RGBMODE_32BPP_RGBA_8888 (0xDu << 4) /**< \brief (LCDC_HEOCFG1) 32 bpp RGBA 8888 */
#define LCDC_HEOCFG1_CLUTMODE_Pos 8
#define LCDC_HEOCFG1_CLUTMODE_Msk (0x3u << LCDC_HEOCFG1_CLUTMODE_Pos) /**< \brief (LCDC_HEOCFG1) Color Lookup Table Mode Input Selection */
#define LCDC_HEOCFG1_CLUTMODE(value) ((LCDC_HEOCFG1_CLUTMODE_Msk & ((value) << LCDC_HEOCFG1_CLUTMODE_Pos)))
#define   LCDC_HEOCFG1_CLUTMODE_1BPP (0x0u << 8) /**< \brief (LCDC_HEOCFG1) Color lookup table mode set to 1 bit per pixel */
#define   LCDC_HEOCFG1_CLUTMODE_2BPP (0x1u << 8) /**< \brief (LCDC_HEOCFG1) Color lookup table mode set to 2 bits per pixel */
#define   LCDC_HEOCFG1_CLUTMODE_4BPP (0x2u << 8) /**< \brief (LCDC_HEOCFG1) Color lookup table mode set to 4 bits per pixel */
#define   LCDC_HEOCFG1_CLUTMODE_8BPP (0x3u << 8) /**< \brief (LCDC_HEOCFG1) Color lookup table mode set to 8 bits per pixel */
#define LCDC_HEOCFG1_YUVMODE_Pos 12
#define LCDC_HEOCFG1_YUVMODE_Msk (0xfu << LCDC_HEOCFG1_YUVMODE_Pos) /**< \brief (LCDC_HEOCFG1) YUV Mode Input Selection */
#define LCDC_HEOCFG1_YUVMODE(value) ((LCDC_HEOCFG1_YUVMODE_Msk & ((value) << LCDC_HEOCFG1_YUVMODE_Pos)))
#define   LCDC_HEOCFG1_YUVMODE_32BPP_AYCBCR (0x0u << 12) /**< \brief (LCDC_HEOCFG1) 32 bpp AYCbCr 444 */
#define   LCDC_HEOCFG1_YUVMODE_16BPP_YCBCR_MODE0 (0x1u << 12) /**< \brief (LCDC_HEOCFG1) 16 bpp Cr(n)Y(n+1)Cb(n)Y(n) 422 */
#define   LCDC_HEOCFG1_YUVMODE_16BPP_YCBCR_MODE1 (0x2u << 12) /**< \brief (LCDC_HEOCFG1) 16 bpp Y(n+1)Cr(n)Y(n)Cb(n) 422 */
#define   LCDC_HEOCFG1_YUVMODE_16BPP_YCBCR_MODE2 (0x3u << 12) /**< \brief (LCDC_HEOCFG1) 16 bpp Cb(n)Y(+1)Cr(n)Y(n) 422 */
#define   LCDC_HEOCFG1_YUVMODE_16BPP_YCBCR_MODE3 (0x4u << 12) /**< \brief (LCDC_HEOCFG1) 16 bpp Y(n+1)Cb(n)Y(n)Cr(n) 422 */
#define   LCDC_HEOCFG1_YUVMODE_16BPP_YCBCR_SEMIPLANAR (0x5u << 12) /**< \brief (LCDC_HEOCFG1) 16 bpp Semiplanar 422 YCbCr */
#define   LCDC_HEOCFG1_YUVMODE_16BPP_YCBCR_PLANAR (0x6u << 12) /**< \brief (LCDC_HEOCFG1) 16 bpp Planar 422 YCbCr */
#define   LCDC_HEOCFG1_YUVMODE_12BPP_YCBCR_SEMIPLANAR (0x7u << 12) /**< \brief (LCDC_HEOCFG1) 12 bpp Semiplanar 420 YCbCr */
#define   LCDC_HEOCFG1_YUVMODE_12BPP_YCBCR_PLANAR (0x8u << 12) /**< \brief (LCDC_HEOCFG1) 12 bpp Planar 420 YCbCr */
#define LCDC_HEOCFG1_YUV422ROT (0x1u << 16) /**< \brief (LCDC_HEOCFG1) YUV 4:2:2 Rotation */
#define LCDC_HEOCFG1_YUV422SWP (0x1u << 17) /**< \brief (LCDC_HEOCFG1) YUV 4:2:2 Swap */
/* -------- LCDC_HEOCFG2 : (LCDC Offset: 0x000002D4) High End Overlay Configuration Register 2 -------- */
#define LCDC_HEOCFG2_XPOS_Pos 0
#define LCDC_HEOCFG2_XPOS_Msk (0x7ffu << LCDC_HEOCFG2_XPOS_Pos) /**< \brief (LCDC_HEOCFG2) Horizontal Window Position */
#define LCDC_HEOCFG2_XPOS(value) ((LCDC_HEOCFG2_XPOS_Msk & ((value) << LCDC_HEOCFG2_XPOS_Pos)))
#define LCDC_HEOCFG2_YPOS_Pos 16
#define LCDC_HEOCFG2_YPOS_Msk (0x7ffu << LCDC_HEOCFG2_YPOS_Pos) /**< \brief (LCDC_HEOCFG2) Vertical Window Position */
#define LCDC_HEOCFG2_YPOS(value) ((LCDC_HEOCFG2_YPOS_Msk & ((value) << LCDC_HEOCFG2_YPOS_Pos)))
/* -------- LCDC_HEOCFG3 : (LCDC Offset: 0x000002D8) High End Overlay Configuration Register 3 -------- */
#define LCDC_HEOCFG3_XSIZE_Pos 0
#define LCDC_HEOCFG3_XSIZE_Msk (0x7ffu << LCDC_HEOCFG3_XSIZE_Pos) /**< \brief (LCDC_HEOCFG3) Horizontal Window Size */
#define LCDC_HEOCFG3_XSIZE(value) ((LCDC_HEOCFG3_XSIZE_Msk & ((value) << LCDC_HEOCFG3_XSIZE_Pos)))
#define LCDC_HEOCFG3_YSIZE_Pos 16
#define LCDC_HEOCFG3_YSIZE_Msk (0x7ffu << LCDC_HEOCFG3_YSIZE_Pos) /**< \brief (LCDC_HEOCFG3) Vertical Window Size */
#define LCDC_HEOCFG3_YSIZE(value) ((LCDC_HEOCFG3_YSIZE_Msk & ((value) << LCDC_HEOCFG3_YSIZE_Pos)))
/* -------- LCDC_HEOCFG4 : (LCDC Offset: 0x000002DC) High End Overlay Configuration Register 4 -------- */
#define LCDC_HEOCFG4_XMEMSIZE_Pos 0
#define LCDC_HEOCFG4_XMEMSIZE_Msk (0x7ffu << LCDC_HEOCFG4_XMEMSIZE_Pos) /**< \brief (LCDC_HEOCFG4) Horizontal image Size in Memory */
#define LCDC_HEOCFG4_XMEMSIZE(value) ((LCDC_HEOCFG4_XMEMSIZE_Msk & ((value) << LCDC_HEOCFG4_XMEMSIZE_Pos)))
#define LCDC_HEOCFG4_YMEMSIZE_Pos 16
#define LCDC_HEOCFG4_YMEMSIZE_Msk (0x7ffu << LCDC_HEOCFG4_YMEMSIZE_Pos) /**< \brief (LCDC_HEOCFG4) Vertical image Size in Memory */
#define LCDC_HEOCFG4_YMEMSIZE(value) ((LCDC_HEOCFG4_YMEMSIZE_Msk & ((value) << LCDC_HEOCFG4_YMEMSIZE_Pos)))
/* -------- LCDC_HEOCFG5 : (LCDC Offset: 0x000002E0) High End Overlay Configuration Register 5 -------- */
#define LCDC_HEOCFG5_XSTRIDE_Pos 0
#define LCDC_HEOCFG5_XSTRIDE_Msk (0xffffffffu << LCDC_HEOCFG5_XSTRIDE_Pos) /**< \brief (LCDC_HEOCFG5) Horizontal Stride */
#define LCDC_HEOCFG5_XSTRIDE(value) ((LCDC_HEOCFG5_XSTRIDE_Msk & ((value) << LCDC_HEOCFG5_XSTRIDE_Pos)))
/* -------- LCDC_HEOCFG6 : (LCDC Offset: 0x000002E4) High End Overlay Configuration Register 6 -------- */
#define LCDC_HEOCFG6_PSTRIDE_Pos 0
#define LCDC_HEOCFG6_PSTRIDE_Msk (0xffffffffu << LCDC_HEOCFG6_PSTRIDE_Pos) /**< \brief (LCDC_HEOCFG6) Pixel Stride */
#define LCDC_HEOCFG6_PSTRIDE(value) ((LCDC_HEOCFG6_PSTRIDE_Msk & ((value) << LCDC_HEOCFG6_PSTRIDE_Pos)))
/* -------- LCDC_HEOCFG7 : (LCDC Offset: 0x000002E8) High End Overlay Configuration Register 7 -------- */
#define LCDC_HEOCFG7_UVXSTRIDE_Pos 0
#define LCDC_HEOCFG7_UVXSTRIDE_Msk (0xffffffffu << LCDC_HEOCFG7_UVXSTRIDE_Pos) /**< \brief (LCDC_HEOCFG7) UV Horizontal Stride */
#define LCDC_HEOCFG7_UVXSTRIDE(value) ((LCDC_HEOCFG7_UVXSTRIDE_Msk & ((value) << LCDC_HEOCFG7_UVXSTRIDE_Pos)))
/* -------- LCDC_HEOCFG8 : (LCDC Offset: 0x000002EC) High End Overlay Configuration Register 8 -------- */
#define LCDC_HEOCFG8_UVPSTRIDE_Pos 0
#define LCDC_HEOCFG8_UVPSTRIDE_Msk (0xffffffffu << LCDC_HEOCFG8_UVPSTRIDE_Pos) /**< \brief (LCDC_HEOCFG8) UV Pixel Stride */
#define LCDC_HEOCFG8_UVPSTRIDE(value) ((LCDC_HEOCFG8_UVPSTRIDE_Msk & ((value) << LCDC_HEOCFG8_UVPSTRIDE_Pos)))
/* -------- LCDC_HEOCFG9 : (LCDC Offset: 0x000002F0) High End Overlay Configuration Register 9 -------- */
#define LCDC_HEOCFG9_BDEF_Pos 0
#define LCDC_HEOCFG9_BDEF_Msk (0xffu << LCDC_HEOCFG9_BDEF_Pos) /**< \brief (LCDC_HEOCFG9) Blue Default */
#define LCDC_HEOCFG9_BDEF(value) ((LCDC_HEOCFG9_BDEF_Msk & ((value) << LCDC_HEOCFG9_BDEF_Pos)))
#define LCDC_HEOCFG9_GDEF_Pos 8
#define LCDC_HEOCFG9_GDEF_Msk (0xffu << LCDC_HEOCFG9_GDEF_Pos) /**< \brief (LCDC_HEOCFG9) Green Default */
#define LCDC_HEOCFG9_GDEF(value) ((LCDC_HEOCFG9_GDEF_Msk & ((value) << LCDC_HEOCFG9_GDEF_Pos)))
#define LCDC_HEOCFG9_RDEF_Pos 16
#define LCDC_HEOCFG9_RDEF_Msk (0xffu << LCDC_HEOCFG9_RDEF_Pos) /**< \brief (LCDC_HEOCFG9) Red Default */
#define LCDC_HEOCFG9_RDEF(value) ((LCDC_HEOCFG9_RDEF_Msk & ((value) << LCDC_HEOCFG9_RDEF_Pos)))
/* -------- LCDC_HEOCFG10 : (LCDC Offset: 0x000002F4) High End Overlay Configuration Register 10 -------- */
#define LCDC_HEOCFG10_BKEY_Pos 0
#define LCDC_HEOCFG10_BKEY_Msk (0xffu << LCDC_HEOCFG10_BKEY_Pos) /**< \brief (LCDC_HEOCFG10) Blue Color Component Chroma Key */
#define LCDC_HEOCFG10_BKEY(value) ((LCDC_HEOCFG10_BKEY_Msk & ((value) << LCDC_HEOCFG10_BKEY_Pos)))
#define LCDC_HEOCFG10_GKEY_Pos 8
#define LCDC_HEOCFG10_GKEY_Msk (0xffu << LCDC_HEOCFG10_GKEY_Pos) /**< \brief (LCDC_HEOCFG10) Green Color Component Chroma Key */
#define LCDC_HEOCFG10_GKEY(value) ((LCDC_HEOCFG10_GKEY_Msk & ((value) << LCDC_HEOCFG10_GKEY_Pos)))
#define LCDC_HEOCFG10_RKEY_Pos 16
#define LCDC_HEOCFG10_RKEY_Msk (0xffu << LCDC_HEOCFG10_RKEY_Pos) /**< \brief (LCDC_HEOCFG10) Red Color Component Chroma Key */
#define LCDC_HEOCFG10_RKEY(value) ((LCDC_HEOCFG10_RKEY_Msk & ((value) << LCDC_HEOCFG10_RKEY_Pos)))
/* -------- LCDC_HEOCFG11 : (LCDC Offset: 0x000002F8) High End Overlay Configuration Register 11 -------- */
#define LCDC_HEOCFG11_BMASK_Pos 0
#define LCDC_HEOCFG11_BMASK_Msk (0xffu << LCDC_HEOCFG11_BMASK_Pos) /**< \brief (LCDC_HEOCFG11) Blue Color Component Chroma Key Mask */
#define LCDC_HEOCFG11_BMASK(value) ((LCDC_HEOCFG11_BMASK_Msk & ((value) << LCDC_HEOCFG11_BMASK_Pos)))
#define LCDC_HEOCFG11_GMASK_Pos 8
#define LCDC_HEOCFG11_GMASK_Msk (0xffu << LCDC_HEOCFG11_GMASK_Pos) /**< \brief (LCDC_HEOCFG11) Green Color Component Chroma Key Mask */
#define LCDC_HEOCFG11_GMASK(value) ((LCDC_HEOCFG11_GMASK_Msk & ((value) << LCDC_HEOCFG11_GMASK_Pos)))
#define LCDC_HEOCFG11_RMASK_Pos 16
#define LCDC_HEOCFG11_RMASK_Msk (0xffu << LCDC_HEOCFG11_RMASK_Pos) /**< \brief (LCDC_HEOCFG11) Red Color Component Chroma Key Mask */
#define LCDC_HEOCFG11_RMASK(value) ((LCDC_HEOCFG11_RMASK_Msk & ((value) << LCDC_HEOCFG11_RMASK_Pos)))
/* -------- LCDC_HEOCFG12 : (LCDC Offset: 0x000002FC) High End Overlay Configuration Register 12 -------- */
#define LCDC_HEOCFG12_CRKEY (0x1u << 0) /**< \brief (LCDC_HEOCFG12) Blender Chroma Key Enable */
#define LCDC_HEOCFG12_INV (0x1u << 1) /**< \brief (LCDC_HEOCFG12) Blender Inverted Blender Output Enable */
#define LCDC_HEOCFG12_ITER2BL (0x1u << 2) /**< \brief (LCDC_HEOCFG12) Blender Iterated Color Enable */
#define LCDC_HEOCFG12_ITER (0x1u << 3) /**< \brief (LCDC_HEOCFG12) Blender Use Iterated Color */
#define LCDC_HEOCFG12_REVALPHA (0x1u << 4) /**< \brief (LCDC_HEOCFG12) Blender Reverse Alpha */
#define LCDC_HEOCFG12_GAEN (0x1u << 5) /**< \brief (LCDC_HEOCFG12) Blender Global Alpha Enable */
#define LCDC_HEOCFG12_LAEN (0x1u << 6) /**< \brief (LCDC_HEOCFG12) Blender Local Alpha Enable */
#define LCDC_HEOCFG12_OVR (0x1u << 7) /**< \brief (LCDC_HEOCFG12) Blender Overlay Layer Enable */
#define LCDC_HEOCFG12_DMA (0x1u << 8) /**< \brief (LCDC_HEOCFG12) Blender DMA Layer Enable */
#define LCDC_HEOCFG12_REP (0x1u << 9) /**< \brief (LCDC_HEOCFG12) Use Replication logic to expand RGB color to 24 bits */
#define LCDC_HEOCFG12_DSTKEY (0x1u << 10) /**< \brief (LCDC_HEOCFG12) Destination Chroma Keying */
#define LCDC_HEOCFG12_VIDPRI (0x1u << 12) /**< \brief (LCDC_HEOCFG12) Video Priority */
#define LCDC_HEOCFG12_GA_Pos 16
#define LCDC_HEOCFG12_GA_Msk (0xffu << LCDC_HEOCFG12_GA_Pos) /**< \brief (LCDC_HEOCFG12) Blender Global Alpha */
#define LCDC_HEOCFG12_GA(value) ((LCDC_HEOCFG12_GA_Msk & ((value) << LCDC_HEOCFG12_GA_Pos)))
/* -------- LCDC_HEOCFG13 : (LCDC Offset: 0x00000300) High End Overlay Configuration Register 13 -------- */
#define LCDC_HEOCFG13_XFACTOR_Pos 0
#define LCDC_HEOCFG13_XFACTOR_Msk (0x1fffu << LCDC_HEOCFG13_XFACTOR_Pos) /**< \brief (LCDC_HEOCFG13) Horizontal Scaling Factor */
#define LCDC_HEOCFG13_XFACTOR(value) ((LCDC_HEOCFG13_XFACTOR_Msk & ((value) << LCDC_HEOCFG13_XFACTOR_Pos)))
#define LCDC_HEOCFG13_YFACTOR_Pos 16
#define LCDC_HEOCFG13_YFACTOR_Msk (0x1fffu << LCDC_HEOCFG13_YFACTOR_Pos) /**< \brief (LCDC_HEOCFG13) Vertical Scaling Factor */
#define LCDC_HEOCFG13_YFACTOR(value) ((LCDC_HEOCFG13_YFACTOR_Msk & ((value) << LCDC_HEOCFG13_YFACTOR_Pos)))
#define LCDC_HEOCFG13_SCALEN (0x1u << 31) /**< \brief (LCDC_HEOCFG13) Hardware Scaler Enable */
/* -------- LCDC_HEOCFG14 : (LCDC Offset: 0x00000304) High End Overlay Configuration Register 14 -------- */
#define LCDC_HEOCFG14_CSCRY_Pos 0
#define LCDC_HEOCFG14_CSCRY_Msk (0x3ffu << LCDC_HEOCFG14_CSCRY_Pos) /**< \brief (LCDC_HEOCFG14) Color Space Conversion Y coefficient for Red Component 1:2:7 format */
#define LCDC_HEOCFG14_CSCRY(value) ((LCDC_HEOCFG14_CSCRY_Msk & ((value) << LCDC_HEOCFG14_CSCRY_Pos)))
#define LCDC_HEOCFG14_CSCRU_Pos 10
#define LCDC_HEOCFG14_CSCRU_Msk (0x3ffu << LCDC_HEOCFG14_CSCRU_Pos) /**< \brief (LCDC_HEOCFG14) Color Space Conversion U coefficient for Red Component 1:2:7 format */
#define LCDC_HEOCFG14_CSCRU(value) ((LCDC_HEOCFG14_CSCRU_Msk & ((value) << LCDC_HEOCFG14_CSCRU_Pos)))
#define LCDC_HEOCFG14_CSCRV_Pos 20
#define LCDC_HEOCFG14_CSCRV_Msk (0x3ffu << LCDC_HEOCFG14_CSCRV_Pos) /**< \brief (LCDC_HEOCFG14) Color Space Conversion V coefficient for Red Component 1:2:7 format */
#define LCDC_HEOCFG14_CSCRV(value) ((LCDC_HEOCFG14_CSCRV_Msk & ((value) << LCDC_HEOCFG14_CSCRV_Pos)))
#define LCDC_HEOCFG14_CSCYOFF (0x1u << 30) /**< \brief (LCDC_HEOCFG14) Color Space Conversion Offset */
/* -------- LCDC_HEOCFG15 : (LCDC Offset: 0x00000308) High End Overlay Configuration Register 15 -------- */
#define LCDC_HEOCFG15_CSCGY_Pos 0
#define LCDC_HEOCFG15_CSCGY_Msk (0x3ffu << LCDC_HEOCFG15_CSCGY_Pos) /**< \brief (LCDC_HEOCFG15) Color Space Conversion Y coefficient for Green Component 1:2:7 format */
#define LCDC_HEOCFG15_CSCGY(value) ((LCDC_HEOCFG15_CSCGY_Msk & ((value) << LCDC_HEOCFG15_CSCGY_Pos)))
#define LCDC_HEOCFG15_CSCGU_Pos 10
#define LCDC_HEOCFG15_CSCGU_Msk (0x3ffu << LCDC_HEOCFG15_CSCGU_Pos) /**< \brief (LCDC_HEOCFG15) Color Space Conversion U coefficient for Green Component 1:2:7 format */
#define LCDC_HEOCFG15_CSCGU(value) ((LCDC_HEOCFG15_CSCGU_Msk & ((value) << LCDC_HEOCFG15_CSCGU_Pos)))
#define LCDC_HEOCFG15_CSCGV_Pos 20
#define LCDC_HEOCFG15_CSCGV_Msk (0x3ffu << LCDC_HEOCFG15_CSCGV_Pos) /**< \brief (LCDC_HEOCFG15) Color Space Conversion V coefficient for Green Component 1:2:7 format */
#define LCDC_HEOCFG15_CSCGV(value) ((LCDC_HEOCFG15_CSCGV_Msk & ((value) << LCDC_HEOCFG15_CSCGV_Pos)))
#define LCDC_HEOCFG15_CSCUOFF (0x1u << 30) /**< \brief (LCDC_HEOCFG15) Color Space Conversion Offset */
/* -------- LCDC_HEOCFG16 : (LCDC Offset: 0x0000030C) High End Overlay Configuration Register 16 -------- */
#define LCDC_HEOCFG16_CSCBY_Pos 0
#define LCDC_HEOCFG16_CSCBY_Msk (0x3ffu << LCDC_HEOCFG16_CSCBY_Pos) /**< \brief (LCDC_HEOCFG16) Color Space Conversion Y coefficient for Blue Component 1:2:7 format */
#define LCDC_HEOCFG16_CSCBY(value) ((LCDC_HEOCFG16_CSCBY_Msk & ((value) << LCDC_HEOCFG16_CSCBY_Pos)))
#define LCDC_HEOCFG16_CSCBU_Pos 10
#define LCDC_HEOCFG16_CSCBU_Msk (0x3ffu << LCDC_HEOCFG16_CSCBU_Pos) /**< \brief (LCDC_HEOCFG16) Color Space Conversion U coefficient for Blue Component 1:2:7 format */
#define LCDC_HEOCFG16_CSCBU(value) ((LCDC_HEOCFG16_CSCBU_Msk & ((value) << LCDC_HEOCFG16_CSCBU_Pos)))
#define LCDC_HEOCFG16_CSCBV_Pos 20
#define LCDC_HEOCFG16_CSCBV_Msk (0x3ffu << LCDC_HEOCFG16_CSCBV_Pos) /**< \brief (LCDC_HEOCFG16) Color Space Conversion V coefficient for Blue Component 1:2:7 format */
#define LCDC_HEOCFG16_CSCBV(value) ((LCDC_HEOCFG16_CSCBV_Msk & ((value) << LCDC_HEOCFG16_CSCBV_Pos)))
#define LCDC_HEOCFG16_CSCVOFF (0x1u << 30) /**< \brief (LCDC_HEOCFG16) Color Space Conversion Offset */
/* -------- LCDC_HCRCHER : (LCDC Offset: 0x00000340) Hardware Cursor Channel Enable Register -------- */
#define LCDC_HCRCHER_CHEN (0x1u << 0) /**< \brief (LCDC_HCRCHER) Channel Enable Register */
#define LCDC_HCRCHER_UPDATEEN (0x1u << 1) /**< \brief (LCDC_HCRCHER) Update Overlay Attributes Enable Register */
#define LCDC_HCRCHER_A2QEN (0x1u << 2) /**< \brief (LCDC_HCRCHER) Add Head Pointer Enable Register */
/* -------- LCDC_HCRCHDR : (LCDC Offset: 0x00000344) Hardware Cursor Channel Disable Register -------- */
#define LCDC_HCRCHDR_CHDIS (0x1u << 0) /**< \brief (LCDC_HCRCHDR) Channel Disable Register */
#define LCDC_HCRCHDR_CHRST (0x1u << 8) /**< \brief (LCDC_HCRCHDR) Channel Reset Register */
/* -------- LCDC_HCRCHSR : (LCDC Offset: 0x00000348) Hardware Cursor Channel Status Register -------- */
#define LCDC_HCRCHSR_CHSR (0x1u << 0) /**< \brief (LCDC_HCRCHSR) Channel Status Register */
#define LCDC_HCRCHSR_UPDATESR (0x1u << 1) /**< \brief (LCDC_HCRCHSR) Update Overlay Attributes In Progress */
#define LCDC_HCRCHSR_A2QSR (0x1u << 2) /**< \brief (LCDC_HCRCHSR) Add To Queue Pending Register */
/* -------- LCDC_HCRIER : (LCDC Offset: 0x0000034C) Hardware Cursor Interrupt Enable Register -------- */
#define LCDC_HCRIER_DMA (0x1u << 2) /**< \brief (LCDC_HCRIER) End of DMA Transfer Interrupt Enable Register */
#define LCDC_HCRIER_DSCR (0x1u << 3) /**< \brief (LCDC_HCRIER) Descriptor Loaded Interrupt Enable Register */
#define LCDC_HCRIER_ADD (0x1u << 4) /**< \brief (LCDC_HCRIER) Head Descriptor Loaded Interrupt Enable Register */
#define LCDC_HCRIER_DONE (0x1u << 5) /**< \brief (LCDC_HCRIER) End of List Interrupt Enable Register */
#define LCDC_HCRIER_OVR (0x1u << 6) /**< \brief (LCDC_HCRIER) Overflow Interrupt Enable Register */
/* -------- LCDC_HCRIDR : (LCDC Offset: 0x00000350) Hardware Cursor Interrupt Disable Register -------- */
#define LCDC_HCRIDR_DMA (0x1u << 2) /**< \brief (LCDC_HCRIDR) End of DMA Transfer Interrupt Disable Register */
#define LCDC_HCRIDR_DSCR (0x1u << 3) /**< \brief (LCDC_HCRIDR) Descriptor Loaded Interrupt Disable Register */
#define LCDC_HCRIDR_ADD (0x1u << 4) /**< \brief (LCDC_HCRIDR) Head Descriptor Loaded Interrupt Disable Register */
#define LCDC_HCRIDR_DONE (0x1u << 5) /**< \brief (LCDC_HCRIDR) End of List Interrupt Disable Register */
#define LCDC_HCRIDR_OVR (0x1u << 6) /**< \brief (LCDC_HCRIDR) Overflow Interrupt Disable Register */
/* -------- LCDC_HCRIMR : (LCDC Offset: 0x00000354) Hardware Cursor Interrupt Mask Register -------- */
#define LCDC_HCRIMR_DMA (0x1u << 2) /**< \brief (LCDC_HCRIMR) End of DMA Transfer Interrupt Mask Register */
#define LCDC_HCRIMR_DSCR (0x1u << 3) /**< \brief (LCDC_HCRIMR) Descriptor Loaded Interrupt Mask Register */
#define LCDC_HCRIMR_ADD (0x1u << 4) /**< \brief (LCDC_HCRIMR) Head Descriptor Loaded Interrupt Mask Register */
#define LCDC_HCRIMR_DONE (0x1u << 5) /**< \brief (LCDC_HCRIMR) End of List Interrupt Mask Register */
#define LCDC_HCRIMR_OVR (0x1u << 6) /**< \brief (LCDC_HCRIMR) Overflow Interrupt Mask Register */
/* -------- LCDC_HCRISR : (LCDC Offset: 0x00000358) Hardware Cursor Interrupt Status Register -------- */
#define LCDC_HCRISR_DMA (0x1u << 2) /**< \brief (LCDC_HCRISR) End of DMA Transfer */
#define LCDC_HCRISR_DSCR (0x1u << 3) /**< \brief (LCDC_HCRISR) DMA Descriptor Loaded */
#define LCDC_HCRISR_ADD (0x1u << 4) /**< \brief (LCDC_HCRISR) Head Descriptor Loaded */
#define LCDC_HCRISR_DONE (0x1u << 5) /**< \brief (LCDC_HCRISR) End of List Detected */
#define LCDC_HCRISR_OVR (0x1u << 6) /**< \brief (LCDC_HCRISR) Overflow Detected */
/* -------- LCDC_HCRHEAD : (LCDC Offset: 0x0000035C) Hardware Cursor DMA Head Register -------- */
#define LCDC_HCRHEAD_HEAD_Pos 2
#define LCDC_HCRHEAD_HEAD_Msk (0x3fffffffu << LCDC_HCRHEAD_HEAD_Pos) /**< \brief (LCDC_HCRHEAD) DMA Head Pointer */
#define LCDC_HCRHEAD_HEAD(value) ((LCDC_HCRHEAD_HEAD_Msk & ((value) << LCDC_HCRHEAD_HEAD_Pos)))
/* -------- LCDC_HCRADDR : (LCDC Offset: 0x00000360) Hardware cursor DMA Address Register -------- */
#define LCDC_HCRADDR_ADDR_Pos 0
#define LCDC_HCRADDR_ADDR_Msk (0xffffffffu << LCDC_HCRADDR_ADDR_Pos) /**< \brief (LCDC_HCRADDR) DMA Transfer start address */
#define LCDC_HCRADDR_ADDR(value) ((LCDC_HCRADDR_ADDR_Msk & ((value) << LCDC_HCRADDR_ADDR_Pos)))
/* -------- LCDC_HCRCTRL : (LCDC Offset: 0x00000364) Hardware Cursor DMA Control Register -------- */
#define LCDC_HCRCTRL_DFETCH (0x1u << 0) /**< \brief (LCDC_HCRCTRL) Transfer Descriptor Fetch Enable */
#define LCDC_HCRCTRL_LFETCH (0x1u << 1) /**< \brief (LCDC_HCRCTRL) Lookup Table Fetch Enable */
#define LCDC_HCRCTRL_DMAIEN (0x1u << 2) /**< \brief (LCDC_HCRCTRL) End of DMA Transfer Interrupt Enable */
#define LCDC_HCRCTRL_DSCRIEN (0x1u << 3) /**< \brief (LCDC_HCRCTRL) Descriptor Loaded Interrupt Enable */
#define LCDC_HCRCTRL_ADDIEN (0x1u << 4) /**< \brief (LCDC_HCRCTRL) Add Head Descriptor to Queue Interrupt Enable */
#define LCDC_HCRCTRL_DONEIEN (0x1u << 5) /**< \brief (LCDC_HCRCTRL) End of List Interrupt Enable */
/* -------- LCDC_HCRNEXT : (LCDC Offset: 0x00000368) Hardware Cursor DMA NExt Register -------- */
#define LCDC_HCRNEXT_NEXT_Pos 0
#define LCDC_HCRNEXT_NEXT_Msk (0xffffffffu << LCDC_HCRNEXT_NEXT_Pos) /**< \brief (LCDC_HCRNEXT) DMA Descriptor Next Address */
#define LCDC_HCRNEXT_NEXT(value) ((LCDC_HCRNEXT_NEXT_Msk & ((value) << LCDC_HCRNEXT_NEXT_Pos)))
/* -------- LCDC_HCRCFG0 : (LCDC Offset: 0x0000036C) Hardware Cursor Configuration 0 Register -------- */
#define LCDC_HCRCFG0_BLEN_Pos 4
#define LCDC_HCRCFG0_BLEN_Msk (0x3u << LCDC_HCRCFG0_BLEN_Pos) /**< \brief (LCDC_HCRCFG0) AHB Burst Length */
#define   LCDC_HCRCFG0_BLEN_AHB_SINGLE (0x0u << 4) /**< \brief (LCDC_HCRCFG0) AHB Access is started as soon as there is enough space in the FIFO to store one data. SINGLE, INCR, INCR4, INCR8 and INCR16 bursts are used. INCR is used for a burst of 2 and 3 beats. */
#define   LCDC_HCRCFG0_BLEN_AHB_INCR4 (0x1u << 4) /**< \brief (LCDC_HCRCFG0) AHB Access is started as soon as there is enough space in the FIFO to store a total amount of 4 data. An AHB INCR4 Burst is used. SINGLE, INCR and INCR4 bursts are used. INCR is used for a burst of 2 and 3 beats. */
#define   LCDC_HCRCFG0_BLEN_AHB_INCR8 (0x2u << 4) /**< \brief (LCDC_HCRCFG0) AHB Access is started as soon as there is enough space in the FIFO to store a total amount of 8 data. An AHB INCR8 Burst is used. SINGLE, INCR, INCR4 and INCR8 bursts are used. INCR is used for a burst of 2 and 3 beats. */
#define   LCDC_HCRCFG0_BLEN_AHB_INCR16 (0x3u << 4) /**< \brief (LCDC_HCRCFG0) AHB Access is started as soon as there is enough space in the FIFO to store a total amount of 16 data. An AHB INCR16 Burst is used. SINGLE, INCR, INCR4, INCR8 and INCR16 bursts are used. INCR is used for a burst of 2 and 3 beats. */
#define LCDC_HCRCFG0_DLBO (0x1u << 8) /**< \brief (LCDC_HCRCFG0) Defined Length Burst Only for Channel Bus Transaction. */
/* -------- LCDC_HCRCFG1 : (LCDC Offset: 0x00000370) Hardware Cursor Configuration 1 Register -------- */
#define LCDC_HCRCFG1_CLUTEN (0x1u << 0) /**< \brief (LCDC_HCRCFG1) Color Lookup Table Enable */
#define LCDC_HCRCFG1_RGBMODE_Pos 4
#define LCDC_HCRCFG1_RGBMODE_Msk (0xfu << LCDC_HCRCFG1_RGBMODE_Pos) /**< \brief (LCDC_HCRCFG1) RGB input mode selection */
#define   LCDC_HCRCFG1_RGBMODE_12BPP_RGB_444 (0x0u << 4) /**< \brief (LCDC_HCRCFG1) 12 bpp RGB 444 */
#define   LCDC_HCRCFG1_RGBMODE_16BPP_ARGB_4444 (0x1u << 4) /**< \brief (LCDC_HCRCFG1) 16 bpp ARGB 4444 */
#define   LCDC_HCRCFG1_RGBMODE_16BPP_RGBA_4444 (0x2u << 4) /**< \brief (LCDC_HCRCFG1) 16 bpp RGBA 4444 */
#define   LCDC_HCRCFG1_RGBMODE_16BPP_RGB_565 (0x3u << 4) /**< \brief (LCDC_HCRCFG1) 16 bpp RGB 565 */
#define   LCDC_HCRCFG1_RGBMODE_16BPP_TRGB_1555 (0x4u << 4) /**< \brief (LCDC_HCRCFG1) 16 bpp TRGB 1555 */
#define   LCDC_HCRCFG1_RGBMODE_18BPP_RGB_666 (0x5u << 4) /**< \brief (LCDC_HCRCFG1) 18 bpp RGB 666 */
#define   LCDC_HCRCFG1_RGBMODE_18BPP_RGB_666_PACKED (0x6u << 4) /**< \brief (LCDC_HCRCFG1) 18 bpp RGB 666 PACKED */
#define   LCDC_HCRCFG1_RGBMODE_19BPP_TRGB_1666 (0x7u << 4) /**< \brief (LCDC_HCRCFG1) 19 bpp TRGB 1666 */
#define   LCDC_HCRCFG1_RGBMODE_19BPP_TRGB_PACKED (0x8u << 4) /**< \brief (LCDC_HCRCFG1) 19 bpp TRGB 1666 PACKED */
#define   LCDC_HCRCFG1_RGBMODE_24BPP_RGB_888 (0x9u << 4) /**< \brief (LCDC_HCRCFG1) 24 bpp RGB 888 */
#define   LCDC_HCRCFG1_RGBMODE_24BPP_RGB_888_PACKED (0xAu << 4) /**< \brief (LCDC_HCRCFG1) 24 bpp RGB 888 PACKED */
#define   LCDC_HCRCFG1_RGBMODE_25BPP_TRGB_1888 (0xBu << 4) /**< \brief (LCDC_HCRCFG1) 25 bpp TRGB 1888 */
#define   LCDC_HCRCFG1_RGBMODE_32BPP_ARGB_8888 (0xCu << 4) /**< \brief (LCDC_HCRCFG1) 32 bpp ARGB 8888 */
#define   LCDC_HCRCFG1_RGBMODE_32BPP_RGBA_8888 (0xDu << 4) /**< \brief (LCDC_HCRCFG1) 32 bpp RGBA 8888 */
#define LCDC_HCRCFG1_CLUTMODE_Pos 8
#define LCDC_HCRCFG1_CLUTMODE_Msk (0x3u << LCDC_HCRCFG1_CLUTMODE_Pos) /**< \brief (LCDC_HCRCFG1) Color Lookup table input mode selection */
#define   LCDC_HCRCFG1_CLUTMODE_1BPP (0x0u << 8) /**< \brief (LCDC_HCRCFG1) color lookup table mode set to 1 bit per pixel */
#define   LCDC_HCRCFG1_CLUTMODE_2BPP (0x1u << 8) /**< \brief (LCDC_HCRCFG1) color lookup table mode set to 2 bits per pixel */
#define   LCDC_HCRCFG1_CLUTMODE_4BPP (0x2u << 8) /**< \brief (LCDC_HCRCFG1) color lookup table mode set to 4 bits per pixel */
#define   LCDC_HCRCFG1_CLUTMODE_8BPP (0x3u << 8) /**< \brief (LCDC_HCRCFG1) color lookup table mode set to 8 bits per pixel */
/* -------- LCDC_HCRCFG2 : (LCDC Offset: 0x00000374) Hardware Cursor Configuration 2 Register -------- */
#define LCDC_HCRCFG2_XPOS_Pos 0
#define LCDC_HCRCFG2_XPOS_Msk (0x7ffu << LCDC_HCRCFG2_XPOS_Pos) /**< \brief (LCDC_HCRCFG2) Horizontal Window Position */
#define LCDC_HCRCFG2_XPOS(value) ((LCDC_HCRCFG2_XPOS_Msk & ((value) << LCDC_HCRCFG2_XPOS_Pos)))
#define LCDC_HCRCFG2_YPOS_Pos 16
#define LCDC_HCRCFG2_YPOS_Msk (0x7ffu << LCDC_HCRCFG2_YPOS_Pos) /**< \brief (LCDC_HCRCFG2) Vertical Window Position */
#define LCDC_HCRCFG2_YPOS(value) ((LCDC_HCRCFG2_YPOS_Msk & ((value) << LCDC_HCRCFG2_YPOS_Pos)))
/* -------- LCDC_HCRCFG3 : (LCDC Offset: 0x00000378) Hardware Cursor Configuration 3 Register -------- */
#define LCDC_HCRCFG3_XSIZE_Pos 0
#define LCDC_HCRCFG3_XSIZE_Msk (0x7fu << LCDC_HCRCFG3_XSIZE_Pos) /**< \brief (LCDC_HCRCFG3) Horizontal Window Size */
#define LCDC_HCRCFG3_XSIZE(value) ((LCDC_HCRCFG3_XSIZE_Msk & ((value) << LCDC_HCRCFG3_XSIZE_Pos)))
#define LCDC_HCRCFG3_YSIZE_Pos 16
#define LCDC_HCRCFG3_YSIZE_Msk (0x7fu << LCDC_HCRCFG3_YSIZE_Pos) /**< \brief (LCDC_HCRCFG3) Vertical Window Size */
#define LCDC_HCRCFG3_YSIZE(value) ((LCDC_HCRCFG3_YSIZE_Msk & ((value) << LCDC_HCRCFG3_YSIZE_Pos)))
/* -------- LCDC_HCRCFG4 : (LCDC Offset: 0x0000037C) Hardware Cursor Configuration 4 Register -------- */
#define LCDC_HCRCFG4_XSTRIDE_Pos 0
#define LCDC_HCRCFG4_XSTRIDE_Msk (0xffffffffu << LCDC_HCRCFG4_XSTRIDE_Pos) /**< \brief (LCDC_HCRCFG4) Horizontal Stride */
#define LCDC_HCRCFG4_XSTRIDE(value) ((LCDC_HCRCFG4_XSTRIDE_Msk & ((value) << LCDC_HCRCFG4_XSTRIDE_Pos)))
/* -------- LCDC_HCRCFG6 : (LCDC Offset: 0x00000384) Hardware Cursor Configuration 6 Register -------- */
#define LCDC_HCRCFG6_BDEF_Pos 0
#define LCDC_HCRCFG6_BDEF_Msk (0xffu << LCDC_HCRCFG6_BDEF_Pos) /**< \brief (LCDC_HCRCFG6) Blue Default */
#define LCDC_HCRCFG6_BDEF(value) ((LCDC_HCRCFG6_BDEF_Msk & ((value) << LCDC_HCRCFG6_BDEF_Pos)))
#define LCDC_HCRCFG6_GDEF_Pos 8
#define LCDC_HCRCFG6_GDEF_Msk (0xffu << LCDC_HCRCFG6_GDEF_Pos) /**< \brief (LCDC_HCRCFG6) Green Default */
#define LCDC_HCRCFG6_GDEF(value) ((LCDC_HCRCFG6_GDEF_Msk & ((value) << LCDC_HCRCFG6_GDEF_Pos)))
#define LCDC_HCRCFG6_RDEF_Pos 16
#define LCDC_HCRCFG6_RDEF_Msk (0xffu << LCDC_HCRCFG6_RDEF_Pos) /**< \brief (LCDC_HCRCFG6) Red Default */
#define LCDC_HCRCFG6_RDEF(value) ((LCDC_HCRCFG6_RDEF_Msk & ((value) << LCDC_HCRCFG6_RDEF_Pos)))
/* -------- LCDC_HCRCFG7 : (LCDC Offset: 0x00000388) Hardware Cursor Configuration 7 Register -------- */
#define LCDC_HCRCFG7_BKEY_Pos 0
#define LCDC_HCRCFG7_BKEY_Msk (0xffu << LCDC_HCRCFG7_BKEY_Pos) /**< \brief (LCDC_HCRCFG7) Blue Color Component Chroma Key */
#define LCDC_HCRCFG7_BKEY(value) ((LCDC_HCRCFG7_BKEY_Msk & ((value) << LCDC_HCRCFG7_BKEY_Pos)))
#define LCDC_HCRCFG7_GKEY_Pos 8
#define LCDC_HCRCFG7_GKEY_Msk (0xffu << LCDC_HCRCFG7_GKEY_Pos) /**< \brief (LCDC_HCRCFG7) Green Color Component Chroma Key */
#define LCDC_HCRCFG7_GKEY(value) ((LCDC_HCRCFG7_GKEY_Msk & ((value) << LCDC_HCRCFG7_GKEY_Pos)))
#define LCDC_HCRCFG7_RKEY_Pos 16
#define LCDC_HCRCFG7_RKEY_Msk (0xffu << LCDC_HCRCFG7_RKEY_Pos) /**< \brief (LCDC_HCRCFG7) Red Color Component Chroma Key */
#define LCDC_HCRCFG7_RKEY(value) ((LCDC_HCRCFG7_RKEY_Msk & ((value) << LCDC_HCRCFG7_RKEY_Pos)))
/* -------- LCDC_HCRCFG8 : (LCDC Offset: 0x0000038C) Hardware Cursor Configuration 8 Register -------- */
#define LCDC_HCRCFG8_BMASK_Pos 0
#define LCDC_HCRCFG8_BMASK_Msk (0xffu << LCDC_HCRCFG8_BMASK_Pos) /**< \brief (LCDC_HCRCFG8) Blue Color Component Chroma Key Mask */
#define LCDC_HCRCFG8_BMASK(value) ((LCDC_HCRCFG8_BMASK_Msk & ((value) << LCDC_HCRCFG8_BMASK_Pos)))
#define LCDC_HCRCFG8_GMASK_Pos 8
#define LCDC_HCRCFG8_GMASK_Msk (0xffu << LCDC_HCRCFG8_GMASK_Pos) /**< \brief (LCDC_HCRCFG8) Green Color Component Chroma Key Mask */
#define LCDC_HCRCFG8_GMASK(value) ((LCDC_HCRCFG8_GMASK_Msk & ((value) << LCDC_HCRCFG8_GMASK_Pos)))
#define LCDC_HCRCFG8_RMASK_Pos 16
#define LCDC_HCRCFG8_RMASK_Msk (0xffu << LCDC_HCRCFG8_RMASK_Pos) /**< \brief (LCDC_HCRCFG8) Red Color Component Chroma Key Mask */
#define LCDC_HCRCFG8_RMASK(value) ((LCDC_HCRCFG8_RMASK_Msk & ((value) << LCDC_HCRCFG8_RMASK_Pos)))
/* -------- LCDC_HCRCFG9 : (LCDC Offset: 0x00000390) Hardware Cursor Configuration 9 Register -------- */
#define LCDC_HCRCFG9_CRKEY (0x1u << 0) /**< \brief (LCDC_HCRCFG9) Blender Chroma Key Enable */
#define LCDC_HCRCFG9_INV (0x1u << 1) /**< \brief (LCDC_HCRCFG9) Blender Inverted Blender Output Enable */
#define LCDC_HCRCFG9_ITER2BL (0x1u << 2) /**< \brief (LCDC_HCRCFG9) Blender Iterated Color Enable */
#define LCDC_HCRCFG9_ITER (0x1u << 3) /**< \brief (LCDC_HCRCFG9) Blender Use Iterated Color */
#define LCDC_HCRCFG9_REVALPHA (0x1u << 4) /**< \brief (LCDC_HCRCFG9) Blender Reverse Alpha */
#define LCDC_HCRCFG9_GAEN (0x1u << 5) /**< \brief (LCDC_HCRCFG9) Blender Global Alpha Enable */
#define LCDC_HCRCFG9_LAEN (0x1u << 6) /**< \brief (LCDC_HCRCFG9) Blender Local Alpha Enable */
#define LCDC_HCRCFG9_OVR (0x1u << 7) /**< \brief (LCDC_HCRCFG9) Blender Overlay Layer Enable */
#define LCDC_HCRCFG9_DMA (0x1u << 8) /**< \brief (LCDC_HCRCFG9) Blender DMA Layer Enable */
#define LCDC_HCRCFG9_REP (0x1u << 9) /**< \brief (LCDC_HCRCFG9) Use Replication logic to expand RGB color to 24 bits */
#define LCDC_HCRCFG9_DSTKEY (0x1u << 10) /**< \brief (LCDC_HCRCFG9) Destination Chroma Keying */
#define LCDC_HCRCFG9_GA_Pos 16
#define LCDC_HCRCFG9_GA_Msk (0xffu << LCDC_HCRCFG9_GA_Pos) /**< \brief (LCDC_HCRCFG9) Blender Global Alpha */
#define LCDC_HCRCFG9_GA(value) ((LCDC_HCRCFG9_GA_Msk & ((value) << LCDC_HCRCFG9_GA_Pos)))
/* -------- LCDC_BASECLUT[256] : (LCDC Offset: 0x00000400) Base CLUT Register -------- */
#define LCDC_BASECLUT_BCLUT_Pos 0
#define LCDC_BASECLUT_BCLUT_Msk (0xffu << LCDC_BASECLUT_BCLUT_Pos) /**< \brief (LCDC_BASECLUT[256]) Blue Color entry */
#define LCDC_BASECLUT_BCLUT(value) ((LCDC_BASECLUT_BCLUT_Msk & ((value) << LCDC_BASECLUT_BCLUT_Pos)))
#define LCDC_BASECLUT_GCLUT_Pos 8
#define LCDC_BASECLUT_GCLUT_Msk (0xffu << LCDC_BASECLUT_GCLUT_Pos) /**< \brief (LCDC_BASECLUT[256]) Green Color entry */
#define LCDC_BASECLUT_GCLUT(value) ((LCDC_BASECLUT_GCLUT_Msk & ((value) << LCDC_BASECLUT_GCLUT_Pos)))
#define LCDC_BASECLUT_RCLUT_Pos 16
#define LCDC_BASECLUT_RCLUT_Msk (0xffu << LCDC_BASECLUT_RCLUT_Pos) /**< \brief (LCDC_BASECLUT[256]) Red Color entry */
#define LCDC_BASECLUT_RCLUT(value) ((LCDC_BASECLUT_RCLUT_Msk & ((value) << LCDC_BASECLUT_RCLUT_Pos)))
/* -------- LCDC_OVR1CLUT[256] : (LCDC Offset: 0x00000800) Overlay 1 CLUT Register -------- */
#define LCDC_OVR1CLUT_BCLUT_Pos 0
#define LCDC_OVR1CLUT_BCLUT_Msk (0xffu << LCDC_OVR1CLUT_BCLUT_Pos) /**< \brief (LCDC_OVR1CLUT[256]) Blue Color entry */
#define LCDC_OVR1CLUT_BCLUT(value) ((LCDC_OVR1CLUT_BCLUT_Msk & ((value) << LCDC_OVR1CLUT_BCLUT_Pos)))
#define LCDC_OVR1CLUT_GCLUT_Pos 8
#define LCDC_OVR1CLUT_GCLUT_Msk (0xffu << LCDC_OVR1CLUT_GCLUT_Pos) /**< \brief (LCDC_OVR1CLUT[256]) Green Color entry */
#define LCDC_OVR1CLUT_GCLUT(value) ((LCDC_OVR1CLUT_GCLUT_Msk & ((value) << LCDC_OVR1CLUT_GCLUT_Pos)))
#define LCDC_OVR1CLUT_RCLUT_Pos 16
#define LCDC_OVR1CLUT_RCLUT_Msk (0xffu << LCDC_OVR1CLUT_RCLUT_Pos) /**< \brief (LCDC_OVR1CLUT[256]) Red Color entry */
#define LCDC_OVR1CLUT_RCLUT(value) ((LCDC_OVR1CLUT_RCLUT_Msk & ((value) << LCDC_OVR1CLUT_RCLUT_Pos)))
#define LCDC_OVR1CLUT_ACLUT_Pos 24
#define LCDC_OVR1CLUT_ACLUT_Msk (0xffu << LCDC_OVR1CLUT_ACLUT_Pos) /**< \brief (LCDC_OVR1CLUT[256]) Alpha Color entry */
#define LCDC_OVR1CLUT_ACLUT(value) ((LCDC_OVR1CLUT_ACLUT_Msk & ((value) << LCDC_OVR1CLUT_ACLUT_Pos)))
/* -------- LCDC_HEOCLUT[256] : (LCDC Offset: 0x00001000) High End Overlay CLUT Register -------- */
#define LCDC_HEOCLUT_BCLUT_Pos 0
#define LCDC_HEOCLUT_BCLUT_Msk (0xffu << LCDC_HEOCLUT_BCLUT_Pos) /**< \brief (LCDC_HEOCLUT[256]) Blue Color entry */
#define LCDC_HEOCLUT_BCLUT(value) ((LCDC_HEOCLUT_BCLUT_Msk & ((value) << LCDC_HEOCLUT_BCLUT_Pos)))
#define LCDC_HEOCLUT_GCLUT_Pos 8
#define LCDC_HEOCLUT_GCLUT_Msk (0xffu << LCDC_HEOCLUT_GCLUT_Pos) /**< \brief (LCDC_HEOCLUT[256]) Green Color entry */
#define LCDC_HEOCLUT_GCLUT(value) ((LCDC_HEOCLUT_GCLUT_Msk & ((value) << LCDC_HEOCLUT_GCLUT_Pos)))
#define LCDC_HEOCLUT_RCLUT_Pos 16
#define LCDC_HEOCLUT_RCLUT_Msk (0xffu << LCDC_HEOCLUT_RCLUT_Pos) /**< \brief (LCDC_HEOCLUT[256]) Red Color entry */
#define LCDC_HEOCLUT_RCLUT(value) ((LCDC_HEOCLUT_RCLUT_Msk & ((value) << LCDC_HEOCLUT_RCLUT_Pos)))
#define LCDC_HEOCLUT_ACLUT_Pos 24
#define LCDC_HEOCLUT_ACLUT_Msk (0xffu << LCDC_HEOCLUT_ACLUT_Pos) /**< \brief (LCDC_HEOCLUT[256]) Alpha Color entry */
#define LCDC_HEOCLUT_ACLUT(value) ((LCDC_HEOCLUT_ACLUT_Msk & ((value) << LCDC_HEOCLUT_ACLUT_Pos)))
/* -------- LCDC_HCRCLUT[256] : (LCDC Offset: 0x00001400) Hardware Cursor CLUT Register -------- */
#define LCDC_HCRCLUT_BCLUT_Pos 0
#define LCDC_HCRCLUT_BCLUT_Msk (0xffu << LCDC_HCRCLUT_BCLUT_Pos) /**< \brief (LCDC_HCRCLUT[256]) Blue Color entry */
#define LCDC_HCRCLUT_BCLUT(value) ((LCDC_HCRCLUT_BCLUT_Msk & ((value) << LCDC_HCRCLUT_BCLUT_Pos)))
#define LCDC_HCRCLUT_GCLUT_Pos 8
#define LCDC_HCRCLUT_GCLUT_Msk (0xffu << LCDC_HCRCLUT_GCLUT_Pos) /**< \brief (LCDC_HCRCLUT[256]) Green Color entry */
#define LCDC_HCRCLUT_GCLUT(value) ((LCDC_HCRCLUT_GCLUT_Msk & ((value) << LCDC_HCRCLUT_GCLUT_Pos)))
#define LCDC_HCRCLUT_RCLUT_Pos 16
#define LCDC_HCRCLUT_RCLUT_Msk (0xffu << LCDC_HCRCLUT_RCLUT_Pos) /**< \brief (LCDC_HCRCLUT[256]) Red Color entry */
#define LCDC_HCRCLUT_RCLUT(value) ((LCDC_HCRCLUT_RCLUT_Msk & ((value) << LCDC_HCRCLUT_RCLUT_Pos)))
#define LCDC_HCRCLUT_ACLUT_Pos 24
#define LCDC_HCRCLUT_ACLUT_Msk (0xffu << LCDC_HCRCLUT_ACLUT_Pos) /**< \brief (LCDC_HCRCLUT[256]) Alpha Color entry */
#define LCDC_HCRCLUT_ACLUT(value) ((LCDC_HCRCLUT_ACLUT_Msk & ((value) << LCDC_HCRCLUT_ACLUT_Pos)))

/*@}*/


#endif /* _SAM9X_LCDC_COMPONENT_ */
