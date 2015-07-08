/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

/** \file */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"

#include "video/lcdd.h"
#include "peripherals/pio.h"
#include "peripherals/pmc.h"

#include "cortex-a/cp15.h"

#include <math.h>
#include <string.h>

#ifdef LCDC
/** \addtogroup lcdd_base
 * Implementation of LCD driver, Include LCD initialization,
 * LCD on/off and LCD backlight control.
 */
/**@{*/

/*----------------------------------------------------------------------------
 *        Local types
 *----------------------------------------------------------------------------*/

/** DMA descriptor for LCDC */
typedef struct _LCDCDescriptor {
	uint32_t addr;
	uint32_t ctrl;
	uint32_t next;
} sLCDCDescriptor;

/** CULT information */
typedef struct _CLUTInfo {
	uint8_t bpp;
	uint8_t nbColors;
} sCLUTInfo;

/** LCDC General Layer information */
typedef struct _Layer {
	sLCDCDescriptor dmaD;
	void *pBuffer;
	sCLUTInfo clut;
	uint16_t reserved;
} sLayer;

/** LCDC HEO Layer information */
typedef struct _HeoLayer {
	sLCDCDescriptor dmaD[3];
	void *pBuffer;
	sCLUTInfo clut;
	uint16_t reserved;
} sHeoLayer;

ALIGNED(64) static sLCDCDescriptor dmaHeader;

ALIGNED(64) static sLCDCDescriptor dmaHeaderUv;

ALIGNED(64) static sLCDCDescriptor dmaHeaderV;

/** Current selected canvas information */
static sLCDDLayer lcddCanvas;
/** Base Layer */

ALIGNED(64) static sLayer lcddBase;

ALIGNED(64) static sLayer lcddOvr1;

ALIGNED(64) static sLayer lcddOvr2;

ALIGNED(64) static sHeoLayer lcddHeo;

ALIGNED(64) static sLayer lcddHcc;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * Return a pointer to layer.
 * \param bLayer Layer ID.
 */
static sLayer* pLayer(uint8_t bLayer)
{
	switch (bLayer) {
	case LCDD_BASE:
		return &lcddBase;
	case LCDD_OVR1:
		return &lcddOvr1;
	case LCDD_OVR2:
		return &lcddOvr2;
	case LCDD_HEO:
		return (sLayer *) & lcddHeo;
	case LCDD_CUR:
		return &lcddHcc;
	}
	return NULL;
}

/**
 * Return true if Pixel stride supported.
 * \param bLayer Layer ID.
 */
static uint8_t _is_stride_supported(uint8_t bLayer)
{
	switch (bLayer) {
	case LCDD_OVR1:
	case LCDD_OVR2:
	case LCDD_HEO:
		return 1;
	default:
		return 0;
	}
}

/**
 * Return a pointer to enable register.
 * (Starts following register list: _ER, _DR, _SR, _IER, _IDR, _IMR, _ISR)
 * \param bLayer Layer ID.
 */
static volatile uint32_t *pEnableReg(uint8_t bLayer)
{
	Lcdc *pHw = LCDC;
	switch (bLayer) {
	case LCDD_CONTROLLER:
		return (volatile uint32_t *) &pHw->LCDC_LCDEN;
	case LCDD_BASE:
		return (volatile uint32_t *) &pHw->LCDC_BASECHER;
	case LCDD_OVR1:
		return (volatile uint32_t *) &pHw->LCDC_OVR1CHER;
	case LCDD_OVR2:
		return (volatile uint32_t *) &pHw->LCDC_OVR2CHER;
	case LCDD_HEO:
		return (volatile uint32_t *) &pHw->LCDC_HEOCHER;
	}
	return NULL;
}

/**
 * Return a pointer to blender configuration register.
 * \param bLayer Layer ID.
 */
static volatile uint32_t *pBlenderReg(uint8_t bLayer)
{
	Lcdc *pHw = LCDC;
	switch (bLayer) {
	case LCDD_BASE:
		return (volatile uint32_t *) &pHw->LCDC_BASECFG4;
	case LCDD_OVR1:
		return (volatile uint32_t *) &pHw->LCDC_OVR1CFG9;
	case LCDD_OVR2:
		return (volatile uint32_t *) &pHw->LCDC_OVR2CFG9;
	case LCDD_HEO:
		return (volatile uint32_t *) &pHw->LCDC_HEOCFG12;
	}
	return NULL;
}

/**
 * Return a pointer to DMA head register.
 * (Starts following register list: _HEAD, _ADDRESS, _CONTROL, _NEXT)
 * \param bLayer Layer ID.
 */
static volatile uint32_t *pHeadReg(uint8_t bLayer)
{
	Lcdc *pHw = LCDC;
	switch (bLayer) {
	case LCDD_BASE:
		return (volatile uint32_t *) &pHw->LCDC_BASEHEAD;
	case LCDD_OVR1:
		return (volatile uint32_t *) &pHw->LCDC_OVR1HEAD;
	case LCDD_OVR2:
		return (volatile uint32_t *) &pHw->LCDC_OVR2HEAD;
	case LCDD_HEO:
		return (volatile uint32_t *) &pHw->LCDC_HEOHEAD;
	}
	return NULL;
}

/**
 * Return a pointer to layer configure register.
 * (Including: _CFG0, _CFG1 (RGB mode ...))
 * \param bLayer Layer ID.
 */
static volatile uint32_t *pCfgReg(uint8_t bLayer)
{
	Lcdc *pHw = LCDC;
	switch (bLayer) {
	case LCDD_BASE:
		return (volatile uint32_t *) &pHw->LCDC_BASECFG0;
	case LCDD_OVR1:
		return (volatile uint32_t *) &pHw->LCDC_OVR1CFG0;
	case LCDD_OVR2:
		return (volatile uint32_t *) &pHw->LCDC_OVR2CFG0;
	case LCDD_HEO:
		return (volatile uint32_t *) &pHw->LCDC_HEOCFG0;
	}
	return NULL;
}

/**
 * Return a pointer to Window configure register.
 * (Including: X Y register, W H register)
 * \param bLayer Layer ID.
 */
static volatile uint32_t *pWinReg(uint8_t bLayer)
{
	Lcdc *pHw = LCDC;
	switch (bLayer) {
	case LCDD_OVR1:
		return (volatile uint32_t *) &pHw->LCDC_OVR1CFG2;
	case LCDD_OVR2:
		return (volatile uint32_t *) &pHw->LCDC_OVR2CFG2;
	case LCDD_HEO:
		return (volatile uint32_t *) &pHw->LCDC_HEOCFG2;
	}
	return NULL;
}

/**
 * Return a pointer to striding regiters.
 * \param bLayer Layer ID.
 */
static volatile uint32_t *pStrideReg(uint8_t bLayer)
{
	Lcdc *pHw = LCDC;
	switch (bLayer) {
	case LCDD_BASE:
		return (volatile uint32_t *) &pHw->LCDC_BASECFG2;
	case LCDD_OVR1:
		return (volatile uint32_t *) &pHw->LCDC_OVR1CFG4;
	case LCDD_OVR2:
		return (volatile uint32_t *) &pHw->LCDC_OVR2CFG4;
	case LCDD_HEO:
		return (volatile uint32_t *) &pHw->LCDC_HEOCFG5;
	}
	return NULL;
}

/**
 * Return a pointer to Color configure regiters.
 * (Including: RGB Default, RGB Key, RGB Mask)
 * Note that base layer only has one register (default).
 * \param bLayer Layer ID.
 */
static volatile uint32_t *pColorReg(uint8_t bLayer)
{
	Lcdc *pHw = LCDC;
	switch (bLayer) {
	case LCDD_BASE:
		return (volatile uint32_t *) &pHw->LCDC_BASECFG3;
	case LCDD_OVR1:
		return (volatile uint32_t *) &pHw->LCDC_OVR1CFG6;
	case LCDD_OVR2:
		return (volatile uint32_t *) &pHw->LCDC_OVR2CFG6;
	case LCDD_HEO:
		return (volatile uint32_t *) &pHw->LCDC_HEOCFG9;
	}
	return NULL;
}

/**
 * Return a pointer to scaling register.
 * \param bLayer Layer ID.
 */
static volatile uint32_t *pScaleReg(uint8_t bLayer)
{
	Lcdc *pHw = LCDC;
	switch (bLayer) {
	case LCDD_HEO:
		return (volatile uint32_t *) &pHw->LCDC_HEOCFG13;
	}
	return NULL;
}

/**
 * Return bits per pixel from RGB mode settings.
 * (Note the bits is bits occupied in memory, including reserved)
 */
static uint32_t _get_bits_per_pixel(uint32_t modeReg)
{
	switch (modeReg) {
		/* RGB mode */
	case LCDC_HEOCFG1_RGBMODE_12BPP_RGB_444:
	case LCDC_HEOCFG1_RGBMODE_16BPP_ARGB_4444:
	case LCDC_HEOCFG1_RGBMODE_16BPP_RGBA_4444:
	case LCDC_HEOCFG1_RGBMODE_16BPP_RGB_565:
	case LCDC_HEOCFG1_RGBMODE_16BPP_TRGB_1555:
		return 2 * 8;

	case LCDC_HEOCFG1_RGBMODE_18BPP_RGB_666PACKED:
	case LCDC_HEOCFG1_RGBMODE_19BPP_TRGB_PACKED:
	case LCDC_HEOCFG1_RGBMODE_24BPP_RGB_888_PACKED:
		return 3 * 8;

	case LCDC_HEOCFG1_RGBMODE_18BPP_RGB_666:
	case LCDC_HEOCFG1_RGBMODE_19BPP_TRGB_1666:
	case LCDC_HEOCFG1_RGBMODE_24BPP_RGB_888:
	case LCDC_HEOCFG1_RGBMODE_25BPP_TRGB_1888:
	case LCDC_HEOCFG1_RGBMODE_32BPP_ARGB_8888:
	case LCDC_HEOCFG1_RGBMODE_32BPP_RGBA_8888:
		return 3 * 8;

		/* CLUT mode */

	case LCDC_HEOCFG1_CLUTMODE_CLUT_1BPP | LCDC_HEOCFG1_CLUTEN:
		return 1;
	case LCDC_HEOCFG1_CLUTMODE_CLUT_2BPP | LCDC_HEOCFG1_CLUTEN:
		return 2;
	case LCDC_HEOCFG1_CLUTMODE_CLUT_4BPP | LCDC_HEOCFG1_CLUTEN:
		return 4;
	case LCDC_HEOCFG1_CLUTMODE_CLUT_8BPP | LCDC_HEOCFG1_CLUTEN:
		return 8;

		/* YUV mode */
	case LCDC_HEOCFG1_YUVEN | LCDC_HEOCFG1_YUVMODE_32BPP_AYCBCR:
		return 32;
	case LCDC_HEOCFG1_YUVEN | LCDC_HEOCFG1_YUVMODE_16BPP_YCBCR_MODE0:
	case LCDC_HEOCFG1_YUVEN | LCDC_HEOCFG1_YUVMODE_16BPP_YCBCR_MODE1:
	case LCDC_HEOCFG1_YUVEN | LCDC_HEOCFG1_YUVMODE_16BPP_YCBCR_MODE2:
	case LCDC_HEOCFG1_YUVEN | LCDC_HEOCFG1_YUVMODE_16BPP_YCBCR_MODE3:
	case LCDC_HEOCFG1_YUVEN | LCDC_HEOCFG1_YUVMODE_16BPP_YCBCR_SEMIPLANAR:
	case LCDC_HEOCFG1_YUVEN | LCDC_HEOCFG1_YUVMODE_16BPP_YCBCR_PLANAR:
	case LCDC_HEOCFG1_YUVEN | LCDC_HEOCFG1_YUVMODE_12BPP_YCBCR_SEMIPLANAR:
	case LCDC_HEOCFG1_YUVEN | LCDC_HEOCFG1_YUVMODE_12BPP_YCBCR_PLANAR:
		return 16;
	}
	return 0;
}

/**
 * Enable a LCDC DMA channel
 */
static void _set_dma_desc(void *pBuffer, sLCDCDescriptor * pTD, uint32_t regAddr)
{
	volatile uint32_t *pDmaR = (volatile uint32_t *) regAddr;
	/* Modify descriptor */
	pTD->addr = (uint32_t) pBuffer;
	pTD->ctrl = LCDC_BASECTRL_DFETCH;
	pTD->next = (uint32_t) pTD;
	/* Modify registers */
	pDmaR[1] = (uint32_t) pBuffer;
	pDmaR[2] = LCDC_BASECTRL_DFETCH;
	pDmaR[3] = (uint32_t) pTD;
}

/**
 * Disable a LCDC DMA channel
 */
static void _clear_dma_desc(sLCDCDescriptor * pTD, uint32_t regAddr)
{
	uint32_t *pReg = (uint32_t *) regAddr;
	volatile uint32_t *pRegCtrl = (volatile uint32_t *) &pReg[1];
	volatile uint32_t *pRegNext = (volatile uint32_t *) &pReg[2];

	/* Modify descriptor */
	if (pTD) {
		pTD->ctrl &= ~LCDC_BASECTRL_DFETCH;
		pTD->next = (uint32_t) pTD;
	}
	/* Modify control registers */
	*pRegCtrl &= ~LCDC_BASECTRL_DFETCH;
	*pRegNext = (uint32_t) pTD;
}

/**
 * Return scaling factor
 */
static uint32_t _calc_scale_factor(uint32_t targetW, uint32_t imgW)
{
	uint32_t factor;

	factor = 2048 * (imgW + 1) / (targetW + 1);

	//factor = 1024 * (imgW + 1) / (targetW + 1);
	//if (targetW > imgW * 2)
	//    factor -= 7;
	return factor;
}

/**
 * Return a pointer to Color Palette lookup regiters.
 * \param bLayer Layer ID.
 */
static volatile uint32_t *pCLUTReg(uint8_t bLayer)
{
	Lcdc *pHw = LCDC;
	switch (bLayer) {
	case LCDD_BASE:
		return (volatile uint32_t *) &pHw->LCDC_BASECLUT[0];
	case LCDD_OVR1:
		return (volatile uint32_t *) &pHw->LCDC_OVR1CLUT[0];
	case LCDD_OVR2:
		return (volatile uint32_t *) &pHw->LCDC_OVR2CLUT[0];
	case LCDD_HEO:
		return (volatile uint32_t *) &pHw->LCDC_HEOCLUT[0];
	}
	return NULL;
}

/**
 * Build 8-bit color palette (actually true color)
 */
static void _build_color_lut8(volatile uint32_t * pCLUT)
{
	uint32_t r, g, b;	/* 3:3:2 */
	for (r = 0; r < 8; r++) {
		for (g = 0; g < 8; g++) {
			for (b = 0; b < 4; b++) {
				*pCLUT++ = (r << (16 + 5))
					+ (g << (8 + 5))
					+ (b << (0 + 6));
			}
		}
	}
}

/**
 * Build 4-bit color palette (16 color)
 */
static void _build_color_lut4(volatile uint32_t * pCLUT)
{
	uint32_t r, g, b;
	for (r = 0; r < 4; r++) {
		for (g = 0; g < 2; g++) {
			for (b = 0; b < 2; b++) {
				*pCLUT++ = (r << (16 + 6))
					+ (g << (8 + 7))
					+ (b << (0 + 7));
			}
		}
	}
}

/**
 * Build 2-bit color palette (4 gray)
 */
static void _build_color_lut2(volatile uint32_t * pCLUT)
{
	pCLUT[0] = 0x000000;
	pCLUT[1] = 0x505050;
	pCLUT[2] = 0xA0A0A0;
	pCLUT[3] = 0xFFFFFF;
}

/**
 * Build 1-bit color palette (black & white)
 */
static void _build_color_lut1(volatile uint32_t * pCLUT)
{
	pCLUT[0] = 0x000000;
	pCLUT[1] = 0xFFFFFF;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Initializes the LCD controller.
 * Configure SMC to access LCD controller at 64MHz MCK.
 */
void lcdd_initialize(struct _pin* pins, uint32_t pin_len)
{
	Lcdc *pHw = LCDC;
	Pmc *pPmc = PMC;

	/* Configure PIO */
	pio_configure(pins, pin_len);

	lcdd_off();

	/* Reset CLUT information */
	lcddBase.clut.bpp = 0;
	lcddOvr1.clut.bpp = 0;
	lcddOvr2.clut.bpp = 0;
	lcddHeo.clut.bpp = 0;
	lcddHcc.clut.bpp = 0;

	/* Reset layer information */
	lcddBase.pBuffer = NULL;
	lcddOvr1.pBuffer = NULL;
	lcddOvr2.pBuffer = NULL;
	lcddHeo.pBuffer = NULL;
	lcddHcc.pBuffer = NULL;

	/* No canvas selected */
	lcddCanvas.pBuffer = NULL;

	/* Enable peripheral clock */
	pmc_enable_peripheral(ID_LCDC);
	pPmc->PMC_SCER = (0x1u << 3);

	/* Timing Engine Configuration */

	/* Disable interrupt */
	pHw->LCDC_LCDIDR = 0xFFFFFFFF;

	/* Configure channels */

	/* Base */
	pHw->LCDC_BASECFG0 = LCDC_BASECFG0_DLBO | LCDC_BASECFG0_BLEN_AHB_INCR16;
	pHw->LCDC_BASECFG1 = LCDC_BASECFG1_RGBMODE_24BPP_RGB_888_PACKED;

	/* Overlay 1, GA 0xFF */
	pHw->LCDC_OVR1CFG0 =
		LCDC_OVR1CFG0_DLBO | LCDC_OVR1CFG0_BLEN_AHB_BLEN_INCR16 |
		LCDC_OVR1CFG0_ROTDIS;
	pHw->LCDC_OVR1CFG1 = LCDC_OVR1CFG1_RGBMODE_24BPP_RGB_888_PACKED;
	pHw->LCDC_OVR1CFG9 = LCDC_OVR1CFG9_GA(0xFF) | LCDC_OVR1CFG9_GAEN;

	/* Overlay 2, GA 0xFF */
	pHw->LCDC_OVR2CFG0 = LCDC_OVR2CFG0_DLBO | LCDC_OVR2CFG0_BLEN_AHB_INCR16
		| LCDC_OVR2CFG0_ROTDIS;
	pHw->LCDC_OVR2CFG1 = LCDC_OVR2CFG1_RGBMODE_24BPP_RGB_888_PACKED;
	pHw->LCDC_OVR2CFG9 = LCDC_OVR2CFG9_GA(0xFF) | LCDC_OVR2CFG9_GAEN;

	/* High End Overlay, GA 0xFF */
	pHw->LCDC_HEOCFG0 =
		LCDC_HEOCFG0_DLBO | LCDC_HEOCFG0_BLEN_AHB_BLEN_INCR16 |
		LCDC_HEOCFG0_ROTDIS;
	pHw->LCDC_HEOCFG1 = LCDC_HEOCFG1_RGBMODE_24BPP_RGB_888_PACKED;
	pHw->LCDC_HEOCFG12 = LCDC_HEOCFG12_GA(0xFF) | LCDC_HEOCFG12_GAEN;

	LCDC->LCDC_HEOCFG14 = LCDC_HEOCFG14_CSCRY(0x94)
		| LCDC_HEOCFG14_CSCRU(0xCC) | LCDC_HEOCFG14_CSCRV(0)
		| LCDC_HEOCFG14_CSCYOFF;
	LCDC->LCDC_HEOCFG15 = LCDC_HEOCFG15_CSCGY(0x94)
		| LCDC_HEOCFG15_CSCGU(0x387) | LCDC_HEOCFG15_CSCGV(0x3CD)
		| LCDC_HEOCFG15_CSCUOFF;
	LCDC->LCDC_HEOCFG16 = LCDC_HEOCFG16_CSCBY(0x94)| LCDC_HEOCFG16_CSCBU(0)
		| LCDC_HEOCFG16_CSCBV(0x102) | LCDC_HEOCFG16_CSCVOFF;

	lcdd_on();
}

/**
 * Check if specified layer is working.
 * \param bLayer Layer ID.
 * \return 1 if layer is on.
 */
uint8_t lcdd_is_layer_on(uint8_t bLayer)
{
	volatile uint32_t *pReg = pEnableReg(bLayer);
	if (pReg)
		return ((pReg[2] & LCDC_BASECHSR_CHSR) > 0);
	return 0;
}

/**
 * Enable(turn on)/Disable(hide) specified layer.
 * \param bLayer Layer ID.
 * \param bEnDis Enable/Disable.
 */
void lcdd_enable_layer(uint8_t bLayer, uint8_t bEnDis)
{
	volatile uint32_t *pReg = pEnableReg(bLayer);
	volatile uint32_t *pBlR = pBlenderReg(bLayer);

	if (pReg && bLayer > LCDD_CONTROLLER) {
		if (bEnDis) {
			pReg[0] = LCDC_BASECHER_CHEN | LCDC_BASECHER_UPDATEEN;
			pBlR[0] |= LCDC_HEOCFG12_DMA | LCDC_HEOCFG12_OVR;
		} else {
			pReg[1] = LCDC_BASECHDR_CHDIS;
			pBlR[0] &= ~(LCDC_HEOCFG12_DMA | LCDC_HEOCFG12_OVR);
		}
	}
}

/**
 * Refresh layer
 * \param bLayer Layer ID.
 */
void lcdd_refresh(uint8_t bLayer)
{
	volatile uint32_t *pBlR = pBlenderReg(bLayer);
	volatile uint32_t *pEnR = pEnableReg(bLayer);
	if (pBlR) {
		if (pEnR[2] & LCDC_OVR1CHSR_CHSR) {
			pBlR[0] |= LCDC_HEOCFG12_DMA;
			pEnR[0] = LCDC_OVR1CHER_UPDATEEN;
		}
	}
}

/**
 * Set display window position.
 * \param bLayer Layer ID.
 * \param x X position.
 * \param y Y position.
 */
void lcdd_set_position(uint8_t bLayer, uint32_t x, uint32_t y)
{
	volatile uint32_t *pChReg = pEnableReg(bLayer);
	volatile uint32_t *pXyReg = pWinReg(bLayer);
	uint32_t w, h;

	w = (pXyReg[1] & LCDC_OVR1CFG3_XSIZE_Msk) >> LCDC_OVR1CFG3_XSIZE_Pos;
	h = (pXyReg[1] & LCDC_OVR1CFG3_YSIZE_Msk) >> LCDC_OVR1CFG3_YSIZE_Pos;

	if (x + w >= BOARD_LCD_WIDTH)
		x = BOARD_LCD_WIDTH - w;
	if (y + h >= BOARD_LCD_HEIGHT)
		y = BOARD_LCD_HEIGHT - h;

	if (pXyReg) {
		pXyReg[0] = LCDC_OVR1CFG2_XPOS(x) | LCDC_OVR1CFG2_YPOS(y);
		if (pChReg[2] & LCDC_OVR1CHSR_CHSR)
			pChReg[0] = LCDC_OVR1CHER_UPDATEEN;
	}
}

/**
 * Set Prioty of layer (only for HEO now).
 * \param bLayer Layer ID (HEO).
 * \param bPri   Prority value.
 */
void lcdd_set_prioty(uint8_t bLayer, uint8_t bPri)
{
	Lcdc *pHw = LCDC;
	if (bLayer != LCDD_HEO)
		return;
	if (bPri)
		pHw->LCDC_HEOCFG12 |= LCDC_HEOCFG12_VIDPRI;
	else
		pHw->LCDC_HEOCFG12 &= ~LCDC_HEOCFG12_VIDPRI;
	pHw->LCDC_HEOCHER = LCDC_HEOCHER_UPDATEEN;
}

/**
 * Return Prioty of layer (only for HEO now).
 * \param bLayer Layer ID (HEO).
 */
uint8_t lcdd_get_prioty(uint8_t bLayer)
{
	Lcdc *pHw = LCDC;
	if (bLayer != LCDD_HEO)
		return 0;
	return (pHw->LCDC_HEOCFG12 & LCDC_HEOCFG12_VIDPRI) > 0;
}

/**
 * Global & Local Alpha Enable/Disable
 * \param bLayer   Layer ID.
 * \param bEnDisLA Enable/Disable local  alpha.
 * \param bEnDisGA Enable/Disable global alpha.
 */
void lcdd_enable_alpha(uint8_t bLayer, uint8_t bEnDisLA, uint8_t bEnDisGA)
{
	volatile uint32_t *pEnR = pEnableReg(bLayer);
	volatile uint32_t *pCfgR = pBlenderReg(bLayer);
	uint32_t cfg;
	if (pCfgR) {
		cfg = (*pCfgR) & ~(LCDC_OVR1CFG9_LAEN | LCDC_OVR1CFG9_GAEN);
		if (bEnDisGA)
			cfg |= LCDC_OVR1CFG9_GAEN;
		if (bEnDisLA)
			cfg |= LCDC_OVR1CFG9_LAEN;
		(*pCfgR) = cfg;

		pEnR[0] = LCDC_OVR1CHER_UPDATEEN;
	}
}

/**
 * Set alpha value
 * \param bLayer Layer ID (OVR1, HEO or CUR).
 * \param bReverse Reverse alpha (alpha -> 1 - alpha).
 * \param bAlpha   Global alpha value.
 */
void lcdd_set_alpha(uint8_t bLayer, uint8_t bReverse, uint8_t bAlpha)
{
	volatile uint32_t *pEnR = pEnableReg(bLayer);
	volatile uint32_t *pCfgR = pBlenderReg(bLayer);
	uint32_t cfg;

	if (pCfgR) {
		cfg =
			(*pCfgR) & ~(LCDC_OVR1CFG9_REVALPHA | LCDC_OVR1CFG9_GA_Msk);
		if (bReverse)
			cfg |= LCDC_OVR1CFG9_REVALPHA;
		(*pCfgR) = cfg | LCDC_OVR1CFG9_GA(bAlpha);

		pEnR[0] = LCDC_OVR1CHER_UPDATEEN;
	}
}

/**
 * Get alpha value
 * \param bLayer Layer ID (OVR1, HEO or CUR).
 */
uint8_t lcdd_get_alpha(uint8_t bLayer)
{
	Lcdc *pHw = LCDC;
	volatile uint32_t *pCfg;
	uint32_t bmMask = LCDC_OVR1CFG9_GA_Msk;
	uint32_t bShift = LCDC_OVR1CFG9_GA_Pos;

	switch (bLayer) {
	case LCDD_OVR1:
		pCfg = (volatile uint32_t *) &pHw->LCDC_OVR1CFG9;
		break;
	case LCDD_OVR2:
		pCfg = (volatile uint32_t *) &pHw->LCDC_OVR2CFG9;
		break;
	case LCDD_HEO:
		pCfg = (volatile uint32_t *) &pHw->LCDC_HEOCFG9;
		break;
	default:
		return 0;
	}

	return (((*pCfg) >> bShift) & bmMask);
}

/**
 * Enable and Set Color Keying
 * \param bLayer  Layer ID (OVR1, HEO or CUR).
 * \param bDstSrc Destination/Source keying.
 * \param dwColor Color to matching.
 * \param dwMask  Color bit mask.
 */
void lcdd_set_color_keying(uint8_t bLayer, uint8_t bDstSrc,
			   uint32_t dwColor, uint32_t dwMask)
{
	volatile uint32_t *pEnR = pEnableReg(bLayer);
	volatile uint32_t *pBCfgR = pBlenderReg(bLayer);
	volatile uint32_t *pColorR = pColorReg(bLayer);
	if (pBCfgR == NULL)
		return;
	/* Select the Overlay to Blit */
	/* Dest/Source Keying */
	if (bDstSrc)
		*pBCfgR |= LCDC_HEOCFG12_DSTKEY;
	else
		*pBCfgR &= ~LCDC_HEOCFG12_DSTKEY;
	/* Activate Color Keying */
	*pBCfgR |= LCDC_HEOCFG12_CRKEY;
	/* Program Color Keying */
	pColorR[1] = dwColor;
	pColorR[2] = dwMask;
	/* Update */
	pEnR[0] = LCDC_HEOCHER_UPDATEEN;
}

/**
 * Disable Color Keying
 * \param bLayer  Layer ID (OVR1, HEO or CUR).
 */
void lcdd_disable_color_keying(uint8_t bLayer)
{
	volatile uint32_t *pEnR = pEnableReg(bLayer);
	volatile uint32_t *pBCfgR = pBlenderReg(bLayer);
	volatile uint32_t *pColorR = pColorReg(bLayer);
	if (pBCfgR == NULL)
		return;
	*pBCfgR &= ~LCDC_HEOCFG12_CRKEY;
	pColorR[2] = 0;
	/* Update */
	pEnR[0] = LCDC_HEOCHER_UPDATEEN;
}

/**
 * Set Color Lookup Table
 * \param bLayer   Layer ID (OVR1, HEO or CUR).
 * \param pCLUT    Pointer to color lookup table.
 * \param bpp      Bits Per Pixel (1, 2, 4, 8).
 * \param nbColors Number of colors indexed in table.
 */
void lcdd_set_color_lut(uint8_t bLayer, uint32_t * pCLUT, uint8_t bpp, uint8_t nbColors)
{
	//Lcdc *pHw = LCDC;
	volatile uint32_t *pCLUTR = pCLUTReg(bLayer);
	sCLUTInfo *pInfo = &pLayer(bLayer)->clut;

	if (pInfo == NULL)
		return;

	pInfo->bpp = bpp;
	/* Customize CLUT */
	if (pCLUT) {
		uint32_t i;
		if (nbColors == 0)
			nbColors = 1 << bpp;
		pInfo->nbColors = nbColors;
		for (i = 0; i < nbColors; i++)
			pCLUTR[i] = pCLUT[i];
	}
	/* Build CLUT */
	else {
		pInfo->nbColors = 1 << bpp;
		switch (bpp) {
		case 1:
			_build_color_lut1(pCLUTR);
			break;
		case 2:
			_build_color_lut2(pCLUTR);
			break;
		case 4:
			_build_color_lut4(pCLUTR);
			break;
		case 8:
			_build_color_lut8(pCLUTR);
			break;
		}
	}
}

/**
 * Display an image on specified layer.
 * (Image scan origion: Left -> Right, Top -> Bottom.)
 * \note w & h should be the rotated result.
 * \note for LCDD_BASE: x, y don't care. w always > 0.
 * \note for LCDD_HEO:imgW & imgH is used.
 * \param bLayer  Layer ID (OVR1, HEO or CUR).
 * \param pBuffer Pointer to image data.
 * \param bpp     Bits Per Pixel.
 *                - 16: TRGB 1555
 *                - 24:  RGB  888  packed
 *                - 32: ARGB 8888
 * \param x       X position.
 * \param y       Y position.
 * \param w       Width  (<0 means Right  -> Left data).
 * \param h       Height (<0 means Bottom -> Top data).
 * \param imgW    Source image width.
 * \param imgH    Source image height.
 * \param wRotate Rotation (clockwise, 0, 90, 180, 270 accepted).
 */
void * lcdd_show_bmp_rotated(uint8_t bLayer,
			     void *pBuffer, uint8_t bpp,
			     uint32_t x, uint32_t y,
			     int32_t w, int32_t h,
			     uint32_t imgW, uint32_t imgH, int16_t wRotate)
{

	//Lcdc *pHw = LCDC;
	sLayer *pLD = pLayer(bLayer);
	//sCLUTInfo         *pClut = &pLD->clut;
	sLCDCDescriptor *pTD = &pLD->dmaD;
	volatile uint32_t *pEnR = pEnableReg(bLayer);
	volatile uint32_t *pDmaR = pHeadReg(bLayer);
	volatile uint32_t *pWinR = pWinReg(bLayer);
	volatile uint32_t *pStrR = pStrideReg(bLayer);
	volatile uint32_t *pSclR = pScaleReg(bLayer);
	volatile uint32_t *pBlR = pBlenderReg(bLayer);
	volatile uint32_t *pCfgR = pCfgReg(bLayer);
	uint8_t bPStride = _is_stride_supported(bLayer);

	uint8_t bBottomUp = (h < 0);
	uint8_t bRightLeft = (w < 0);
	uint32_t padding = 0;
	int32_t srcW, srcH;
	uint32_t bitsPRow, bytesPRow;
	uint32_t bytesPPix = bpp >> 3;

	void *pOldBuffer = pLD->pBuffer;

	if (pCfgR == NULL)
		return pOldBuffer;

	//printf("Show %x @ %d: (%d,%d)+(%d,%d) img %d x %d * %d\n\r", pBuffer, bLayer, x, y, w, h, imgW, imgH, bpp);

	switch (bpp) {
	case 16:		/*  RGB 565 */
		if ((pCfgR[1] & LCDC_HEOCFG1_YUVEN) != LCDC_HEOCFG1_YUVEN) {
			pCfgR[1] = LCDC_HEOCFG1_RGBMODE_16BPP_RGB_565;	//LCDC_HEOCFG1_RGBMODE_16BPP_TRGB_1555;
		}
		break;
	case 24:		/*  RGB  888 packed */
		pCfgR[1] = LCDC_HEOCFG1_RGBMODE_24BPP_RGB_888_PACKED;
		break;
	case 32:		/* ARGB 8888 */
		pCfgR[1] = LCDC_HEOCFG1_RGBMODE_32BPP_ARGB_8888;
		break;
	default:
		return pOldBuffer;
	}
	/* Windows position & size check */
	if (h < 0)
		h = -h;
	if (w < 0)
		w = -w;
	if (x + w > BOARD_LCD_WIDTH) {
		//printf("! w %d -> %d\n\r", w, BOARD_LCD_WIDTH-x);
		w = BOARD_LCD_WIDTH - x;
	}
	if (y + h > BOARD_LCD_HEIGHT) {
		//printf("! h %d -> %d\n\r", h, BOARD_LCD_HEIGHT-y);
		h = BOARD_LCD_HEIGHT - y;
	}
	if (w == 0)
		w++;
	if (h == 0)
		h++;
	if (imgW == 0)
		imgW++;
	if (imgH == 0)
		imgH++;

	/* Only 0,(-)90,(-)180,(-)270 accepted */
	switch (wRotate) {
	case 0:
	case 90:
	case 180:
	case 270:
		break;
	case -90:
	case -180:
	case -270:
		wRotate += 360;
		break;
	default:
		return NULL;
	}

	/* Setup display buffer & window */
	if (pBuffer)
		pLD->pBuffer = pBuffer;
	else
		pBuffer = pLD->pBuffer;

	/* Set display buffer & mode */
	bitsPRow = imgW * bpp;
	bytesPRow = bitsPRow >> 3;
	if (bitsPRow & 0x7)
		bytesPRow++;
	if (bytesPRow & 0x3)
		padding = 4 - (bytesPRow & 0x3);

	/* No X mirror supported layer, no Right->Left scan */
	if (!bPStride)
		bRightLeft = 0;

	/* --------- Mirror & then rotate --------- */
	/* Normal direction: Left,Top -> Right,Down */
	if ((!bRightLeft && !bBottomUp && wRotate == 0)
	    || (bRightLeft && bBottomUp && wRotate == 180)) {
		/* No rotation optimization */
		pCfgR[0] |= LCDC_HEOCFG0_ROTDIS;
		/* X0 ++ */
		if (bPStride)
			pStrR[1] = LCDC_HEOCFG6_PSTRIDE(0);
		/* Y0 ++ */
		pStrR[0] = LCDC_HEOCFG5_XSTRIDE(padding);
		/* Pointer to Left,Top (x0,y0) */
	}
	/* X mirror: Right,Top -> Left,Down */
	else if ((bRightLeft && !bBottomUp && wRotate == 0)
		 || (!bRightLeft && bBottomUp && wRotate == 180)) {
		/* No rotation optimization */
		pCfgR[0] |= LCDC_HEOCFG0_ROTDIS;
		/* X1 -- */
		if (bPStride)
			pStrR[1] = LCDC_HEOCFG6_PSTRIDE(0 - 2 * bytesPPix);
		/* Y0 ++ */
		pStrR[0] =
			LCDC_HEOCFG5_XSTRIDE(bytesPRow * 2 + padding -
					     2 * bytesPPix);
		/* Pointer to Right,Top (x1,y0) */
		pBuffer = (void *) ((uint32_t) pBuffer
				    + bytesPPix * (imgW - 1));
	}
	/* Y mirror: Left,Down -> Right,Top */
	else if ((!bRightLeft && bBottomUp && wRotate == 0)
		 || (bRightLeft && !bBottomUp && wRotate == 180)) {
		/* No rotation optimization */
		pCfgR[0] |= LCDC_HEOCFG0_ROTDIS;
		/* X0 ++ */
		if (bPStride)
			pStrR[1] = LCDC_HEOCFG6_PSTRIDE(0);
		/* Y1 -- */
		pStrR[0] = LCDC_HEOCFG5_XSTRIDE(0 - (bytesPRow * 2 + padding));
		/* Pointer to Left,Down (x0,y1) */
		pBuffer = (void *) ((uint32_t) pBuffer
				    + (bytesPRow + padding) * (imgH - 1));
	}
	/* X,Y mirror: Right,Top -> Left,Down */
	else if ((bRightLeft && bBottomUp && wRotate == 0)
		 || (!bRightLeft && !bBottomUp && wRotate == 180)) {
		/* No rotation optimization */
		pCfgR[0] |= LCDC_HEOCFG0_ROTDIS;
		/* X1 -- */
		if (bPStride)
			pStrR[1] = LCDC_HEOCFG6_PSTRIDE(0 - 2 * bytesPPix);
		/* Y1 -- */
		pStrR[0] = LCDC_HEOCFG5_XSTRIDE(0 - (bytesPPix * 2 + padding));
		/* Pointer to Left,Down (x1,y1) */
		pBuffer = (void *) ((uint32_t) pBuffer
				    + (bytesPRow + padding) * (imgH - 1)
				    + (bytesPPix) * (imgW - 1));
	}
	/* Rotate  90: Down,Left -> Top,Right (with w,h swap) */
	else if ((!bRightLeft && !bBottomUp && wRotate == 90)
		 || (bRightLeft && bBottomUp && wRotate == 270)) {
		/* No rotation optimization */
		pCfgR[0] |= LCDC_HEOCFG0_ROTDIS;
		/* Y -- as pixels in row */
		if (bPStride)
			pStrR[1] =
				LCDC_HEOCFG6_PSTRIDE(0 -
						     (bytesPPix + bytesPRow +
						      padding));
		/* X ++ as rows */
		pStrR[0] =
			LCDC_HEOCFG5_XSTRIDE((bytesPRow + padding) * (imgH - 1));
		/* Pointer to Bottom,Left */
		pBuffer = (void *) ((uint32_t) pBuffer
				    + (bytesPRow + padding) * (imgH - 1));
	}
	/* Rotate 270: Top,Right -> Down,Left (with w,h swap) */
	else if ((!bRightLeft && !bBottomUp && wRotate == 270)
		 || (bRightLeft && bBottomUp && wRotate == 90)) {
		/* No rotation optimization */
		pCfgR[0] |= LCDC_HEOCFG0_ROTDIS;
		/* Y ++ as pixels in row */
		if (bPStride)
			pStrR[1] =
				LCDC_HEOCFG6_PSTRIDE(bytesPRow + padding -
						     bytesPPix);
		/* X -- as rows */
		pStrR[0] =
			LCDC_HEOCFG5_XSTRIDE(0 - 2 * bytesPPix -
					     (bytesPRow + padding) * (imgH - 1));
		/* Pointer to top right */
		pBuffer = (void *) ((uint32_t) pBuffer
				    + bytesPPix * (imgW - 1));
	}
	/* Mirror X then Rotate 90: Down,Right -> Top,Left */
	else if ((bRightLeft && !bBottomUp && wRotate == 90)
		 || (!bRightLeft && bBottomUp && wRotate == 270)) {
		/* No rotation optimization */
		pCfgR[0] |= LCDC_HEOCFG0_ROTDIS;
		/* Y -- as pixels in row */
		if (bPStride)
			pStrR[1] =
				LCDC_HEOCFG6_PSTRIDE(0 -
						     (bytesPPix + bytesPRow +
						      padding));
		/* X -- as rows */
		pStrR[0] =
			LCDC_HEOCFG5_XSTRIDE(0 - 2 * bytesPPix +
					     (bytesPRow + padding) * (imgH - 1));
		/* Pointer to down right (x1,y1) */
		pBuffer = (void *) ((uint32_t) pBuffer
				    + (bytesPRow + padding) * (imgH - 1)
				    + (bytesPPix) * (imgW - 1));
	}
	/* Mirror Y then Rotate 90: Top,Left -> Down,Right */
	else if ((!bRightLeft && bBottomUp && wRotate == 90)
		 || (bRightLeft && !bBottomUp && wRotate == 270)) {
		/* No rotation optimization */
		pCfgR[0] |= LCDC_HEOCFG0_ROTDIS;
		/* Y ++ as pixels in row */
		if (bPStride)
			pStrR[1] =
				LCDC_HEOCFG6_PSTRIDE(bytesPRow + padding -
						     bytesPPix);
		/* X ++ as rows */
		pStrR[0] =
			LCDC_HEOCFG5_XSTRIDE(0 -
					     (bytesPRow + padding) * (imgH - 1));
		/* Pointer to top left (x0,y0) */
	}
	/** DMA is running, just add new descriptor to queue */
	if (pBlR[0] & LCDC_HEOCFG12_DMA) {
		pTD->addr = (uint32_t) pBuffer;
		pTD->ctrl = LCDC_HEOCTRL_DFETCH;
		pTD->next = (uint32_t) pTD;
		pDmaR[0] = (uint32_t) pTD;
		pEnR[0] = LCDC_HEOCHER_A2QEN;
	} else {
		/* 2. Write the channel descriptor (DSCR) structure in the system memory by
		   writing DSCR.CHXADDR Frame base address, DSCR.CHXCTRL channel control
		   and DSCR.CHXNEXT next descriptor location.
		   3. If more than one descriptor is expected, the DFETCH field of
		   DSCR.CHXCTRL is set to one to enable the descriptor fetch operation.
		   4. Write the DSCR.CHXNEXT register with the address location of the
		   descriptor structure and set DFETCH field of the DSCR.CHXCTRL register
		   to one. */
		_set_dma_desc(pBuffer, pTD, (uint32_t) pDmaR);
	}
	cp15_flush_dcache_for_dma((uint32_t) pTD,
				  ((uint32_t) pTD) + sizeof (pTD));
	/* Set window & position */
	if (pWinR) {
		pWinR[0] = LCDC_HEOCFG2_XPOS(x) | LCDC_HEOCFG2_YPOS(y);
		pWinR[1] =
			LCDC_HEOCFG3_XSIZE(w - 1) | LCDC_HEOCFG3_YSIZE(h - 1);
	}
	/* Scaling setup */
	if (pSclR) {

		/* Image size only used in scaling */
		/* Scaling target */
		if (wRotate == 90 || wRotate == 270) {
			srcW = imgH;
			srcH = imgW;
		} else {
			srcW = imgW;
			srcH = imgH;
		}
		pWinR[2] =
			LCDC_HEOCFG4_XMEMSIZE(srcW -
					      1) | LCDC_HEOCFG4_YMEMSIZE(srcH - 1);
		/* Scaled */
		if (w != srcW || h != srcH) {
			uint16_t wYf, wXf;
			wXf = _calc_scale_factor(w, srcW);
			wYf = _calc_scale_factor(h, srcH);
			//printf("- Scale(%d,%d)\n\r", wXf, wYf);
			pSclR[0] = LCDC_HEOCFG13_YFACTOR(wYf)
				| LCDC_HEOCFG13_XFACTOR(wXf)
				| LCDC_HEOCFG13_SCALEN;
		}
		/* Disable scaling */
		else {
			pSclR[0] = 0;
		}
	}
	/* Enable DMA */
	if (pBuffer) {
		pBlR[0] |= LCDC_HEOCFG12_DMA | LCDC_HEOCFG12_OVR;
	}
	/* Enable & Update */
	/* 5. Enable the relevant channel by writing one to the CHEN field of the
	   CHXCHER register. */
	pEnR[0] = LCDC_HEOCHER_UPDATEEN | LCDC_HEOCHER_CHEN;

	/* 6. An interrupt may be raised if unmasked when the descriptor has been
	   loaded.  */

	return pOldBuffer;
}

/**
 * Display an image on specified layer.
 * (Image scan: Left -> Right, Top -> Bottom.)
 * \param bLayer  Layer ID (OVR1, HEO or CUR).
 * \param pBuffer Pointer to image data.
 * \param bpp     Bits Per Pixel.
 *                - 16: TRGB 1555
 *                - 24:  RGB  888  packed
 *                - 32: ARGB 8888
 * \param x       X position.
 * \param y       Y position.
 * \param w       Width  (<0 means Right  -> Left data).
 * \param h       Height (<0 means Bottom -> Top data).
 * \param imgW    Source image width.
 * \param imgH    Source image height.
 * \return Pointer to old display image data.
 */
void * lcdd_show_bmp_scaled(uint8_t bLayer,
			    void *pBuffer, uint8_t bpp,
			    uint32_t x, uint32_t y,
			    int32_t w, int32_t h, uint32_t imgW, uint32_t imgH)
{
	return lcdd_show_bmp_rotated(bLayer, pBuffer, bpp,
				     x, y, w, h, imgW, imgH, 0);
}

/**
 * Display an image on specified layer.
 * (Image scan: Left -> Right, Top -> Bottom.)
 * \param bLayer  Layer ID (OVR1, HEO or CUR).
 * \param pBuffer Pointer to image data.
 * \param bpp     Bits Per Pixel.
 *                - 16: TRGB 1555
 *                - 24:  RGB  888  packed
 *                - 32: ARGB 8888
 * \param x       X position.
 * \param y       Y position.
 * \param w       Width
 * \param h       Height (<0 means Bottom -> Top data).
 * \return Pointer to old display image data.
 */
void * lcdd_show_bmp(uint8_t bLayer,
		     void *pBuffer, uint8_t bpp,
		     uint32_t x, uint32_t y, int32_t w, int32_t h)
{
	return lcdd_show_bmp_rotated(bLayer, pBuffer, bpp,
				     x, y, w, h, w, (h < 0) ? (-h) : h, 0);
}

/**
 * Start display on base layer
 * \param pBuffer   Pointer to image data.
 * \param bpp       Bits Per Pixel.
 * \param bBottomUp Scan from bottom to top.
 * \return Pointer to old display image data.
 */
void * lcdd_show_base(void *pBuffer, uint8_t bpp, uint8_t bBottomUp)
{
	return lcdd_show_bmp(LCDD_BASE, pBuffer, bpp,
			     0, 0,
			     BOARD_LCD_WIDTH,
			     bBottomUp ? -BOARD_LCD_HEIGHT : BOARD_LCD_HEIGHT);
}

/**
 * Stop display on base layer
 */
void lcdd_stop_base(void)
{
	Lcdc *pHw = LCDC;

	if (!(pHw->LCDC_BASECHSR & LCDC_BASECHSR_CHSR))
		return;

	/* 1. Clear the DFETCH bit in the DSCR.CHXCTRL field of the DSCR structure
	   will disable the channel at the end of the frame. */
	/* 2. Set the DSCR.CHXNEXT field of the DSCR structure will disable the
	   channel at the end of the frame. */
	_clear_dma_desc(&lcddBase.dmaD, (uint32_t) & pHw->LCDC_BASEADDR);

	/* 3. Writing one to the CHDIS field of the CHXCHDR register will disable
	   the channel at the end of the frame. */
	pHw->LCDC_BASECHDR = LCDC_BASECHDR_CHDIS;

	/* 4. Writing one to the CHRST field of the CHXCHDR register will disable
	   the channel immediately. This may occur in the middle of the image. */

	/* 5. Poll CHSR field in the CHXCHSR register until the channel is
	   successfully disabled. */
	while (pHw->LCDC_BASECHSR & LCDC_BASECHSR_CHSR) ;
}

/**
 * Start display on overlay 1 layer
 */
void * lcdd_show_ovr1(void *pBuffer, uint8_t bpp,
		      uint32_t x, uint32_t y, int32_t w, int32_t h)
{
	return lcdd_show_bmp(LCDD_OVR1, pBuffer, bpp, x, y, w, h);
}

/**
 * Stop display on overlay 1 layer
 */
void lcdd_stop_ovr1(void)
{
	Lcdc *pHw = LCDC;

	if (!(pHw->LCDC_OVR1CHSR & LCDC_OVR1CHSR_CHSR))
		return;

	/* 1. Clear the DFETCH bit in the DSCR.CHXCTRL field of the DSCR structure
	   will disable the channel at the end of the frame. */
	/* 2. Set the DSCR.CHXNEXT field of the DSCR structure will disable the
	   channel at the end of the frame. */
	_clear_dma_desc(&lcddOvr1.dmaD, (uint32_t) & pHw->LCDC_OVR1ADDR);

	/* 3. Writing one to the CHDIS field of the CHXCHDR register will disable
	   the channel at the end of the frame. */
	pHw->LCDC_OVR1CHDR = LCDC_OVR1CHDR_CHDIS;

	/* 4. Writing one to the CHRST field of the CHXCHDR register will disable
	   the channel immediately. This may occur in the middle of the image. */

	/* 5. Poll CHSR field in the CHXCHSR register until the channel is
	   successfully disabled. */
	while (pHw->LCDC_OVR1CHSR & LCDC_OVR1CHSR_CHSR) ;
}

/**
 * Start display on High End Overlay layer
 */
void * lcdd_show_heo(void *pBuffer, uint8_t bpp,
		     uint32_t x, uint32_t y, int32_t w, int32_t h,
		     uint32_t imgW, uint32_t imgH)
{
	return lcdd_show_bmp_rotated(LCDD_HEO,
				     pBuffer, bpp, x, y, w, h, imgW, imgH, 0);
}

/**
 * Stop display on High End Overlay layer
 */
void lcdd_stop_heo(void)
{
	Lcdc *pHw = LCDC;

	if (!(pHw->LCDC_HEOCHSR & LCDC_HEOCHSR_CHSR))
		return;

	/* 1. Clear the DFETCH bit in the DSCR.CHXCTRL field of the DSCR structure
	   will disable the channel at the end of the frame. */
	/* 2. Set the DSCR.CHXNEXT field of the DSCR structure will disable the
	   channel at the end of the frame. */
	_clear_dma_desc(&lcddHeo.dmaD[0], (uint32_t) & pHw->LCDC_HEOADDR);
	_clear_dma_desc(&lcddHeo.dmaD[1], (uint32_t) & pHw->LCDC_HEOUADDR);
	_clear_dma_desc(&lcddHeo.dmaD[2], (uint32_t) & pHw->LCDC_HEOVADDR);

	/* 3. Writing one to the CHDIS field of the CHXCHDR register will disable
	   the channel at the end of the frame. */
	pHw->LCDC_HEOCHDR = LCDC_HEOCHDR_CHDIS;

	/* 4. Writing one to the CHRST field of the CHXCHDR register will disable
	   the channel immediately. This may occur in the middle of the image. */

	/* 5. Poll CHSR field in the CHXCHSR register until the channel is
	   successfully disabled. */
	while (pHw->LCDC_HEOCHSR & LCDC_HEOCHSR_CHSR) ;
}

/**
 * Start display on Hardware Cursor layer
 * (Default transparent color is set to #000000, black)
 */
void * lcdd_show_hcr(void *pBuffer, uint8_t bpp,
		     uint32_t x, uint32_t y, int32_t w, int32_t h)
{
	return 0;
}

/**
 * Stop display on Hardware Cursor layer
 */
void lcdd_stop_hcr(void)
{

}

/**
 * \brief Turn on the LCD.
 */
void lcdd_on(void)
{
	Pmc *pPmc = PMC;
	Lcdc *pHw = LCDC;

	/* Enable peripheral clock */
	pmc_enable_peripheral(ID_LCDC);
	pPmc->PMC_SCER = (0x1u << 3);

	/* 1. Configure LCD timing parameters, signal polarity and clock period. */
	pHw->LCDC_LCDCFG0 =
		LCDC_LCDCFG0_CLKDIV((pmc_get_master_clock() * 2) / BOARD_LCD_PIXELCLOCK - 2)
		| LCDC_LCDCFG0_CGDISHEO | LCDC_LCDCFG0_CGDISOVR1 |
		LCDC_LCDCFG0_CGDISOVR2 | LCDC_LCDCFG0_CGDISBASE |
		LCDC_LCDCFG0_CLKPWMSEL | LCDC_LCDCFG0_CLKSEL;
	//|LCDC_LCDCFG0_CLKPOL;

	pHw->LCDC_LCDCFG1 = LCDC_LCDCFG1_VSPW(BOARD_LCD_TIMING_VPW - 1)
		| LCDC_LCDCFG1_HSPW(BOARD_LCD_TIMING_HPW - 1);

	pHw->LCDC_LCDCFG2 = LCDC_LCDCFG2_VBPW(BOARD_LCD_TIMING_VBP)
		| LCDC_LCDCFG2_VFPW(BOARD_LCD_TIMING_VFP - 1);

	pHw->LCDC_LCDCFG3 = LCDC_LCDCFG3_HBPW(BOARD_LCD_TIMING_HBP - 1)
		| LCDC_LCDCFG3_HFPW(BOARD_LCD_TIMING_HFP - 1);

	pHw->LCDC_LCDCFG4 = LCDC_LCDCFG4_RPF(BOARD_LCD_HEIGHT - 1)
		| LCDC_LCDCFG4_PPL(BOARD_LCD_WIDTH - 1);

	pHw->LCDC_LCDCFG5 = LCDC_LCDCFG5_GUARDTIME(30)
		| LCDC_LCDCFG5_MODE_OUTPUT_24BPP
		| LCDC_LCDCFG5_DISPDLY
		| LCDC_LCDCFG5_VSPDLYS | LCDC_LCDCFG5_VSPOL | LCDC_LCDCFG5_HSPOL;

	pHw->LCDC_LCDCFG6 = LCDC_LCDCFG6_PWMCVAL(0xF0)
		| LCDC_LCDCFG6_PWMPOL | LCDC_LCDCFG6_PWMPS(6);

	/* 2. Enable the Pixel Clock by writing one to the CLKEN field of the
	   LCDC_LCDEN register. */
	pHw->LCDC_LCDEN = LCDC_LCDEN_CLKEN;
	/* 3. Poll CLKSTS field of the LCDC_LCDSR register to check that the clock
	   is running. */
	while (!(pHw->LCDC_LCDSR & LCDC_LCDSR_CLKSTS)) ;

	/* 4. Enable Horizontal and Vertical Synchronization by writing one to the
	   SYNCEN field of the LCDC_LCDEN register. */
	pHw->LCDC_LCDEN = LCDC_LCDEN_SYNCEN;
	/* 5. Poll LCDSTS field of the LCDC_LCDSR register to check that the
	   synchronization is up. */
	while (!(pHw->LCDC_LCDSR & LCDC_LCDSR_LCDSTS)) ;

	/* 6. Enable the display power signal writing one to the DISPEN field of the
	   LCDC_LCDEN register. */
	pHw->LCDC_LCDEN = LCDC_LCDEN_DISPEN;
	/* 7. Poll DISPSTS field of the LCDC_LCDSR register to check that the power
	   signal is activated. */
	while (!(pHw->LCDC_LCDSR & LCDC_LCDSR_DISPSTS)) ;
	/* 8. Enable backlight */
	pHw->LCDC_LCDEN = LCDC_LCDEN_PWMEN;
}

/**
 * \brief Turn off the LCD.
 */
void lcdd_off(void)
{
	Lcdc *pHw = LCDC;
	Pmc *pPmc = PMC;

	/* 1. Clear the DFETCH bit in the DSCR.CHXCTRL field of the DSCR structure
	   will disable the channel at the end of the frame. */

	/* 2. Set the DSCR.CHXNEXT field of the DSCR structure will disable the
	   channel at the end of the frame. */

	/* Disable all DMA channel descriptors */
	_clear_dma_desc(&lcddBase.dmaD, (uint32_t) & pHw->LCDC_BASEADDR);
	_clear_dma_desc(&lcddOvr1.dmaD, (uint32_t) & pHw->LCDC_OVR1ADDR);
	_clear_dma_desc(&lcddOvr2.dmaD, (uint32_t) & pHw->LCDC_OVR2ADDR);
	_clear_dma_desc(&lcddHeo.dmaD[0], (uint32_t) & pHw->LCDC_HEOADDR);
	_clear_dma_desc(&lcddHeo.dmaD[1], (uint32_t) & pHw->LCDC_HEOUADDR);
	_clear_dma_desc(&lcddHeo.dmaD[2], (uint32_t) & pHw->LCDC_HEOVADDR);

	/* 3. Writing one to the CHDIS field of the CHXCHDR register will disable
	   the channel at the end of the frame. */

	/* Disable DMA channels */
	pHw->LCDC_BASECHDR = LCDC_BASECHDR_CHDIS;
	pHw->LCDC_OVR1CHDR = LCDC_OVR1CHDR_CHDIS;
	pHw->LCDC_HEOCHDR = LCDC_HEOCHDR_CHDIS;
	pHw->LCDC_BASECFG4 = 0;

	/* 4. Writing one to the CHRST field of the CHXCHDR register will disable
	   the channel immediately. This may occur in the middle of the image. */

	/* 5. Poll CHSR field in the CHXCHSR register until the channel is
	   successfully disabled. */
	while (pHw->LCDC_BASECHSR & LCDC_BASECHSR_CHSR) ;
	while (pHw->LCDC_OVR1CHSR & LCDC_OVR1CHSR_CHSR) ;
	while (pHw->LCDC_HEOCHSR & LCDC_HEOCHSR_CHSR) ;

	/* Timing Engine Power Down Software Operation */

	/* Disable backlight */
	pHw->LCDC_LCDDIS = LCDC_LCDDIS_PWMDIS;
	while (pHw->LCDC_LCDSR & LCDC_LCDSR_PWMSTS) ;

	/* 1. Disable the DISP signal writing DISPDIS field of the LCDC_LCDDIS
	   register. */
	pHw->LCDC_LCDDIS = LCDC_LCDDIS_DISPDIS;
	/* 2. Poll DISPSTS field of the LCDC_LCDSR register to verify that the DISP
	   is no longer activated. */
	while (pHw->LCDC_LCDSR & LCDC_LCDSR_DISPSTS) ;

	/* 3. Disable the hsync and vsync signals by writing one to SYNCDIS field of
	   the LCDC_LCDDIS register. */
	pHw->LCDC_LCDDIS = LCDC_LCDDIS_SYNCDIS;
	/* 4. Poll LCDSTS field of the LCDC_LCDSR register to check that the
	   synchronization is off. */
	while (pHw->LCDC_LCDSR & LCDC_LCDSR_LCDSTS) ;

	/* 5. Disable the Pixel clock by writing one in the CLKDIS field of the
	   LCDC_LCDDIS register. */
	pHw->LCDC_LCDDIS = LCDC_LCDDIS_CLKDIS;
	/* 6. Poll CLKSTS field of the LCDC_LCDSR register to check that Pixel Clock
	   is disabled. */
	while (pHw->LCDC_LCDSR & LCDC_LCDSR_CLKSTS) ;

	/* Disable peripheral clock */
	pmc_disable_peripheral(ID_LCDC);
	/* LCD Clock Disable */
	pPmc->PMC_SCDR = (0x1u << 3);

}

/**
 * \brief Set the backlight of the LCD.
 *
 * \param level   Backlight brightness level [1..255],
 *                255 means maximum brightness.
 */
void lcdd_set_backlight(uint32_t level)
{
	Lcdc *pHw = LCDC;
	uint32_t cfg = pHw->LCDC_LCDCFG6 & ~LCDC_LCDCFG6_PWMCVAL_Msk;

	pHw->LCDC_LCDCFG6 = cfg | LCDC_LCDCFG6_PWMCVAL(level);
}

/**
 * Get canvas layer for LCDD_Draw*
 * \return Layer information pointer.
 */
sLCDDLayer * lcdd_get_canvas(void)
{
	return &lcddCanvas;
}

/**
 * Flush the current canvas layer*
 */
void lcdd_flush_canvas(void)
{
	sLCDDLayer *pCurrentLayer;
	uint32_t base, height, width;
	pCurrentLayer = lcdd_get_canvas();
	base = (uint32_t) pCurrentLayer->pBuffer;
	height = pCurrentLayer->wImgH;
	width = pCurrentLayer->wImgW;
	cp15_flush_dcache_for_dma((uint32_t) base,
				  ((uint32_t) base) + height * width * 4);
}

/**
 * Select an LCD layer as canvas layer.
 * Then all drawing operations will apply to current display buffer
 * of selected layer.
 * \note If there is no display buffer for the layer (not running)
 *       selection fails.
 * \param bLayer    Layer ID.
 */
uint8_t lcdd_select_canvas(uint8_t bLayer)
{
	sLayer *pLD = pLayer(bLayer);
	volatile uint32_t *pXyR = pWinReg(bLayer);
	volatile uint32_t *pCfR = pCfgReg(bLayer);

	if (pLD == NULL)
		return 0;

	lcddCanvas.pBuffer = (void *) pLD->pBuffer;
	if (pXyR) {
		lcddCanvas.wImgW =
			(pXyR[1] & LCDC_HEOCFG3_XSIZE_Msk) >>
			LCDC_HEOCFG3_XSIZE_Pos;
		lcddCanvas.wImgH =
			(pXyR[1] & LCDC_HEOCFG3_YSIZE_Msk) >>
			LCDC_HEOCFG3_YSIZE_Pos;
	} else {
		lcddCanvas.wImgW = BOARD_LCD_WIDTH;
		lcddCanvas.wImgH = BOARD_LCD_HEIGHT;
	}
	lcddCanvas.bMode =
		_get_bits_per_pixel(pCfR[1] & LCDC_HEOCFG1_RGBMODE_Msk);
	lcddCanvas.bLayer = bLayer;

	return 1;
}

/**
 * Create a blank canvas on a display layer for further operations.
 * \param bLayer    Layer ID.
 * \param pBuffer   Pointer to canvas display buffer.
 * \param bBPP      Bits Per Pixel.
 * \param wX        Canvas X coordinate on base.
 * \param wY        Canvas Y coordinate on base.
 * \param wW        Canvas width.
 * \param wH        Canvas height.
 * \note The content in buffer is destroied.
 */
void * lcdd_create_canvas(uint8_t bLayer,
			  void *pBuffer, uint8_t bBPP,
			  uint16_t wX, uint16_t wY, uint16_t wW, uint16_t wH)
{
	void *pOldBuffer;
	uint32_t maxW = BOARD_LCD_WIDTH;
	uint32_t maxH = BOARD_LCD_HEIGHT;

	uint32_t bitsPR, bytesPR;

	switch (bLayer) {
	case LCDD_BASE:
		wX = 0;
		wY = 0;
		break;
	case LCDD_OVR1:
	case LCDD_OVR2:
	case LCDD_HEO:
		/* Size check */
		if (wX + wW > BOARD_LCD_WIDTH || wY + wH > BOARD_LCD_HEIGHT)
			return NULL;
		break;
	case LCDD_CUR:
		/* Size check */
		if (wX + wW > BOARD_LCD_WIDTH || wY + wH > BOARD_LCD_HEIGHT
		    || wW > 128 || wH > 128)
			return NULL;
		maxW = maxH = 128;
		break;
	}
	if (wW == 0)
		wW = maxW - wX;
	if (wH == 0)
		wH = maxH - wY;

	bitsPR = wW * bBPP;
	bytesPR = (bitsPR & 0x7) ? (bitsPR / 8 + 1) : (bitsPR / 8);
	memset(pBuffer, 0xFF, bytesPR * wH);
	pOldBuffer = lcdd_show_bmp_rotated(bLayer, pBuffer, bBPP,
					   wX, wY, wW, wH, wW, wH, 0);

	lcddCanvas.bLayer = bLayer;
	lcddCanvas.bMode = bBPP;
	lcddCanvas.pBuffer = pBuffer;
	lcddCanvas.wImgW = wW;
	lcddCanvas.wImgH = wH;

	return pOldBuffer;
}

/**
 * Create a blank canvas on a display layer for further operations.
 * \param bLayer    Layer ID.
 * \param pBuffer   Pointer to canvas display buffer.
 * \param bBPP      Bits Per Pixel.
 * \param wX        Canvas X coordinate on base.
 * \param wY        Canvas Y coordinate on base.
 * \param wW        Canvas width.
 * \param wH        Canvas height.
 * \note The content in buffer is destroyed.
 */
void * lcdd_create_canvas_yuv_planar(uint8_t bLayer,
				     void *pBuffer, void *pBufferUV,
				     void *pBufferV, uint8_t bBPP,
				     uint16_t wX, uint16_t wY, uint16_t wW,
				     uint16_t wH)
{
	volatile uint32_t *pDmaR;
	sLCDCDescriptor *pTD;

	volatile uint32_t *pWinR = pWinReg(bLayer);

	uint32_t maxW = BOARD_LCD_WIDTH;
	uint32_t maxH = BOARD_LCD_HEIGHT;

	uint32_t bitsPR, bytesPR;

	switch (bLayer) {
	case LCDD_BASE:
	case LCDD_OVR1:
	case LCDD_OVR2:
	case LCDD_CUR:
		return 0;
	case LCDD_HEO:
		/* Size check */
		if (wX + wW > BOARD_LCD_WIDTH || wY + wH > BOARD_LCD_HEIGHT)
			return NULL;
		break;
	}
	if (wW == 0)
		wW = maxW - wX;
	if (wH == 0)
		wH = maxH - wY;

	bitsPR = wW * bBPP;
	bytesPR = (bitsPR & 0x7) ? (bitsPR / 8 + 1) : (bitsPR / 8);
	memset(pBuffer, 0xFF, bytesPR * wH);

	if (pWinR) {
		pWinR[0] = LCDC_HEOCFG2_XPOS(wX) | LCDC_HEOCFG2_YPOS(wY);
		pWinR[1] =
			LCDC_HEOCFG3_XSIZE(wW - 1) | LCDC_HEOCFG3_YSIZE(wH - 1);
		pWinR[2] =
			LCDC_HEOCFG4_XMEMSIZE(wW - 1) | LCDC_HEOCFG4_YMEMSIZE(wH - 1);
	}


	pTD = &dmaHeader;
	pDmaR = (volatile uint32_t *)&LCDC->LCDC_HEOHEAD;
	/* Modify descriptor */
	pTD->addr = (uint32_t) pBuffer;
	pTD->ctrl = LCDC_BASECTRL_DFETCH;
	pTD->next = (uint32_t) pTD;
	/* Modify registers */
	pDmaR[0] = (uint32_t) pTD;
	pDmaR[1] = (uint32_t) pBuffer;
	pDmaR[2] = LCDC_BASECTRL_DFETCH;
	pDmaR[3] = (uint32_t) pTD;

	pTD= &dmaHeaderUv;
	pDmaR = (volatile uint32_t *)&LCDC->LCDC_HEOUHEAD;
	/* Modify descriptor */
	pTD->addr = (uint32_t) pBufferUV;
	pTD->ctrl = LCDC_BASECTRL_DFETCH;
	pTD->next = (uint32_t) pTD;
	/* Modify registers */
	pDmaR[0] = (uint32_t) pTD;
	pDmaR[1] = (uint32_t) pBufferUV;
	pDmaR[2] = LCDC_BASECTRL_DFETCH;
	pDmaR[3] = (uint32_t) pTD;

	pTD = &dmaHeaderV;
	pDmaR = (volatile uint32_t *)&LCDC->LCDC_HEOVHEAD;
	/* Modify descriptor */
	pTD->addr = (uint32_t) pBufferV;
	pTD->ctrl = LCDC_BASECTRL_DFETCH;
	pTD->next = (uint32_t) pTD;
	/* Modify registers */
	pDmaR[0] = (uint32_t) pTD;
	pDmaR[1] = (uint32_t) pBufferV;
	pDmaR[2] = LCDC_BASECTRL_DFETCH;
	pDmaR[3] = (uint32_t) pTD;
	return 0;
}

/**
 * \brief Change RGB Input Mode Selection for giving layer.
 * \param bLayer    Layer ID.
 * \param inputMode   RGB Input Mode Selection.
 */
void lcdc_configure_inputMode(uint8_t bLayer, uint32_t inputMode)
{
	volatile uint32_t *pCfgR = pCfgReg(bLayer);
	pCfgR[1] = inputMode;
}

/**@}*/
#endif /* ifdef LCDC */
