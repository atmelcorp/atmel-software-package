/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2019, Atmel Corporation
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

#include <math.h>
#include <string.h>
#include <stdio.h>

#include "chip.h"
#include "compiler.h"
#include "display/lcdc.h"
#include "gpio/pio.h"
#include "mm/cache.h"
#include "peripherals/pmc.h"
#include "trace.h"

/** \addtogroup lcdc_base
 * Implementation of LCD driver, Include LCD initialization,
 * LCD on/off and LCD backlight control.
 */

/**@{*/

/*----------------------------------------------------------------------------
 *        Local types
 *----------------------------------------------------------------------------*/

/** Hardware info about the layers */
struct _layer_info {
	struct _layer_data* data;
	bool                stride_supported;
	volatile uint32_t  *reg_enable;     /**< regs: _ER, _DR, _SR, _IER, _IDR, _IMR, _ISR */
	volatile uint32_t  *reg_blender;    /**< regs: blender */
	volatile uint32_t  *reg_dma_head;   /**< regs: _HEAD, _ADDRESS, _CONTROL, _NEXT */
	volatile uint32_t  *reg_dma_u_head; /**< regs: _HEAD, _ADDRESS, _CONTROL, _NEXT */
	volatile uint32_t  *reg_dma_v_head; /**< regs: _HEAD, _ADDRESS, _CONTROL, _NEXT */
	volatile uint32_t  *reg_cfg;        /**< regs: _CFG0, _CFG1 (RGB mode ...) */
	volatile uint32_t  *reg_win;        /**< regs: X Y register, W H register */
	volatile uint32_t  *reg_stride;     /**< regs: stride */
	volatile uint32_t  *reg_color;      /**< regs: RGB Default, RGB Key, RGB Mask */
	volatile uint32_t  *reg_scale;      /**< regs: scale */
	volatile uint32_t  *reg_clut;       /**< regs: CLUT */
};

/** DMA descriptor for LCDC */
struct _lcdc_dma_desc {
	uint32_t addr;
	uint32_t ctrl;
	uint32_t next;
	uint32_t for_alignment_only;
};

/** Variable layer data */
struct _layer_data {
	struct _lcdc_dma_desc *dma_desc;
	struct _lcdc_dma_desc *dma_u_desc;
	struct _lcdc_dma_desc *dma_v_desc;
	void                  *buffer;
	uint8_t                bpp;
};

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static struct _lcdc_desc lcdc_config;         /**< Current LCD configuration */

static struct _lcdc_layer lcdc_canvas;        /**< Current selected canvas */

CACHE_ALIGNED_DDR
static struct _lcdc_dma_desc base_dma_desc;  /**< DMA desc. for Base Layer */

static struct _layer_data lcdc_base;         /**< Base Layer */

#ifdef CONFIG_HAVE_LCDC_OVR1
CACHE_ALIGNED_DDR
static struct _lcdc_dma_desc ovr1_dma_desc;  /**< DMA desc. for OVR1 Layer */

static struct _layer_data lcdc_ovr1;         /**< OVR1 Layer */
#endif

#ifdef CONFIG_HAVE_LCDC_OVR2
CACHE_ALIGNED_DDR
static struct _lcdc_dma_desc ovr2_dma_desc;  /**< DMA desc. for OVR2 Layer */

static struct _layer_data lcdc_ovr2;         /**< OVR2 Layer */
#endif

CACHE_ALIGNED_DDR
static struct _lcdc_dma_desc heo_dma_desc;   /**< DMA desc. for HEO Layer */

CACHE_ALIGNED_DDR
static struct _lcdc_dma_desc heo_dma_u_desc; /**< DMA desc. for HEO U-UV Layer */

CACHE_ALIGNED_DDR
static struct _lcdc_dma_desc heo_dma_v_desc; /**< DMA desc. for HEO V Layer */

static struct _layer_data lcdc_heo;          /**< HEO Layer */

#ifdef CONFIG_HAVE_LCDC_PP
CACHE_ALIGNED_DDR
static struct _lcdc_dma_desc pp_dma_desc;    /**< DMA desc. for PP Layer */

static struct _layer_data lcdc_pp;           /**< PP Layer */
#endif

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

/** Information about layers, order must match value of LCDC_XXX constants in
 * ldcd.h */
static const struct _layer_info lcdc_layers[] = {
	/* 0: LCDC_CONTROLLER */
	{
		.stride_supported = false,
	},
	/* 1: LCDC_BASE */
	{
		.data = &lcdc_base,
		.stride_supported = false,
		.reg_enable = &LCDC->LCDC_BASECHER,
		.reg_blender = &LCDC->LCDC_BASECFG4,
		.reg_dma_head = &LCDC->LCDC_BASEHEAD,
		.reg_cfg = &LCDC->LCDC_BASECFG0,
		.reg_stride = &LCDC->LCDC_BASECFG2,
		.reg_color = &LCDC->LCDC_BASECFG3,
		.reg_clut = &LCDC->LCDC_BASECLUT[0]
	},
#ifdef CONFIG_HAVE_LCDC_OVR1
	/* 2: LCDC_OVR1 */
	{
		.data = &lcdc_ovr1,
		.stride_supported = true,
		.reg_enable = &LCDC->LCDC_OVR1CHER,
		.reg_blender = &LCDC->LCDC_OVR1CFG9,
		.reg_dma_head = &LCDC->LCDC_OVR1HEAD,
		.reg_cfg = &LCDC->LCDC_OVR1CFG0,
		.reg_win = &LCDC->LCDC_OVR1CFG2,
		.reg_stride = &LCDC->LCDC_OVR1CFG4,
		.reg_color = &LCDC->LCDC_OVR1CFG6,
		.reg_clut = &LCDC->LCDC_OVR1CLUT[0],
	},
#else
	/* 2: N/A */
	{
		.data = NULL,
	},
#endif
	/* 3: LCDC_HEO */
	{
		.data = &lcdc_heo,
		.stride_supported = true,
		.reg_enable = &LCDC->LCDC_HEOCHER,
		.reg_blender = &LCDC->LCDC_HEOCFG12,
		.reg_dma_head = &LCDC->LCDC_HEOHEAD,
		.reg_dma_u_head = &LCDC->LCDC_HEOUHEAD,
		.reg_dma_v_head = &LCDC->LCDC_HEOVHEAD,
		.reg_cfg = &LCDC->LCDC_HEOCFG0,
		.reg_win = &LCDC->LCDC_HEOCFG2,
		.reg_stride = &LCDC->LCDC_HEOCFG5,
		.reg_color = &LCDC->LCDC_HEOCFG9,
		.reg_scale = &LCDC->LCDC_HEOCFG13,
		.reg_clut = &LCDC->LCDC_HEOCLUT[0],
	},
#ifdef CONFIG_HAVE_LCDC_OVR2
	/* 4: LCDC_OVR2 */
	{
		.data = &lcdc_ovr2,
		.stride_supported = true,
		.reg_enable = &LCDC->LCDC_OVR2CHER,
		.reg_blender = &LCDC->LCDC_OVR2CFG9,
		.reg_dma_head = &LCDC->LCDC_OVR2HEAD,
		.reg_cfg = &LCDC->LCDC_OVR2CFG0,
		.reg_win = &LCDC->LCDC_OVR2CFG2,
		.reg_stride = &LCDC->LCDC_OVR2CFG4,
		.reg_color = &LCDC->LCDC_OVR2CFG6,
		.reg_clut = &LCDC->LCDC_OVR2CLUT[0],
	},
#else
	/* 4: N/A */
	{
		.data = NULL,
	},
#endif
#ifdef CONFIG_HAVE_LCDC_PP

	{
		.data = &lcdc_pp,
		.stride_supported = true,
		.reg_enable = &LCDC->LCDC_PPCHER,
		.reg_dma_head = &LCDC->LCDC_PPHEAD,
		.reg_cfg = &LCDC->LCDC_PPCFG0,
		.reg_stride = &LCDC->LCDC_PPCFG2,
	},
#else
	/* 5: N/A */
	{
		.data = NULL,
	},
#endif
};

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * Wait for clock domain synchronization to be complete.
 * While synchronization is in progress, access to registers
 * LCDC_LCDCCFG[0..6], LCDC_LCDEN and LCDC_LCDDIS has no effect.
 */
static void _wait_for_clock_domain_sync(void)
{
	while ((LCDC->LCDC_LCDSR & LCDC_LCDSR_SIPSTS));
}

/**
 * Return bits per pixel from RGB mode settings.
 * (Note the bits is bits occupied in memory, including reserved)
 */
static uint32_t _get_bits_per_pixel(uint32_t mode_reg)
{
	switch (mode_reg) {

	/* RGB modes */

	case LCDC_HEOCFG1_RGBMODE_12BPP_RGB_444:
	case LCDC_HEOCFG1_RGBMODE_16BPP_ARGB_4444:
	case LCDC_HEOCFG1_RGBMODE_16BPP_RGBA_4444:
	case LCDC_HEOCFG1_RGBMODE_16BPP_RGB_565:
	case LCDC_HEOCFG1_RGBMODE_16BPP_TRGB_1555:
		return 2 * 8;

	case LCDC_HEOCFG1_RGBMODE_18BPP_RGB_666_PACKED:
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

	/* CLUT modes */

	case LCDC_HEOCFG1_CLUTMODE_1BPP | LCDC_HEOCFG1_CLUTEN:
		return 1;
	case LCDC_HEOCFG1_CLUTMODE_2BPP | LCDC_HEOCFG1_CLUTEN:
		return 2;
	case LCDC_HEOCFG1_CLUTMODE_4BPP | LCDC_HEOCFG1_CLUTEN:
		return 4;
	case LCDC_HEOCFG1_CLUTMODE_8BPP | LCDC_HEOCFG1_CLUTEN:
		return 8;

#ifdef LCDC_HEOCFG1_YUVEN
	/* YUV modes */

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
#endif /* LCDC_HEOCFG1_YUVEN */
	}
	return 0;
}

/**
 * Enable a LCDC DMA channel
 */
static void _set_dma_desc(void *buffer, struct _lcdc_dma_desc *desc,
		volatile uint32_t *dma_head_reg)
{
	/* Modify descriptor */
	desc->addr = (uint32_t)buffer;
	desc->ctrl = LCDC_BASECTRL_DFETCH;
	desc->next = (uint32_t)desc;
	cache_clean_region(desc, sizeof(struct _lcdc_dma_desc));
	/* Modify registers */
	dma_head_reg[1] = (uint32_t)buffer;
	dma_head_reg[2] = LCDC_BASECTRL_DFETCH;
	dma_head_reg[3] = (uint32_t)desc;
}

/**
 * Disable a LCDC DMA channel
 */
static void _clear_dma_desc(struct _lcdc_dma_desc *desc,
		volatile uint32_t *dma_head_reg)
{
	/* Modify descriptor */
	if (desc) {
		desc->ctrl &= ~LCDC_BASECTRL_DFETCH;
		desc->next = (uint32_t)desc;
		cache_clean_region(desc, sizeof(struct _lcdc_dma_desc));
	}

	/* Modify registers */
	dma_head_reg[2] &= ~LCDC_BASECTRL_DFETCH;
	dma_head_reg[3] = (uint32_t)desc;
}

/**
 * Compute scaling factors
 */
static void _compute_scaling_factors(const struct _layer_info *layer,
		uint16_t* xfactor, uint16_t* yfactor)
{
	uint16_t xmemsize, ymemsize;
	uint16_t xsize, ysize;
#ifdef LCDC_HEOCFG41_XPHIDEF
	uint16_t xfactor_1st, yfactor_1st;
#endif

	xmemsize = (layer->reg_win[2] & LCDC_HEOCFG4_XMEMSIZE_Msk) >> LCDC_HEOCFG4_XMEMSIZE_Pos;
	ymemsize = (layer->reg_win[2] & LCDC_HEOCFG4_YMEMSIZE_Msk) >> LCDC_HEOCFG4_YMEMSIZE_Pos;
	xsize = (layer->reg_win[1] & LCDC_HEOCFG3_XSIZE_Msk) >> LCDC_HEOCFG3_XSIZE_Pos;
	ysize = (layer->reg_win[1] & LCDC_HEOCFG3_YSIZE_Msk) >> LCDC_HEOCFG3_YSIZE_Pos;

#ifdef LCDC_HEOCFG41_XPHIDEF
	/* we assume that XPHIDEF & YPHIDEF are 0 */
	xfactor_1st = (2048 * xmemsize / xsize) + 1;
	yfactor_1st = (2048 * ymemsize / ysize) + 1;

	if ((xfactor_1st * xsize / 2048) > xmemsize)
		*xfactor = xfactor_1st - 1;
	else
		*xfactor = xfactor_1st;

	if ((yfactor_1st * ysize / 2048) > ymemsize)
		*yfactor = yfactor_1st - 1;
	else
		*yfactor = yfactor_1st;
#else
	*xfactor = 1024 * (xmemsize + 1) / (xsize + 1);
	*yfactor = 1024 * (ymemsize + 1) / (ysize + 1);
#endif
}

/**
 * Build 8-bit color palette (actually true color)
 */
static void _build_color_lut8(volatile uint32_t *clut)
{
	uint32_t r, g, b;
	/* 3:3:2 */
	for (r = 0; r < 8; r++) {
		for (g = 0; g < 8; g++) {
			for (b = 0; b < 4; b++) {
				*clut++ = (r << (16 + 5))
					+ (g << (8 + 5))
					+ (b << (0 + 6));
			}
		}
	}
}

/**
 * Build 4-bit color palette (16 color)
 */
static void _build_color_lut4(volatile uint32_t *clut)
{
	uint32_t r, g, b;
	for (r = 0; r < 4; r++) {
		for (g = 0; g < 2; g++) {
			for (b = 0; b < 2; b++) {
				*clut++ = (r << (16 + 6))
					+ (g << (8 + 7))
					+ (b << (0 + 7));
			}
		}
	}
}

/**
 * Build 2-bit color palette (4 gray)
 */
static void _build_color_lut2(volatile uint32_t *clut)
{
	clut[0] = 0x000000;
	clut[1] = 0x505050;
	clut[2] = 0xA0A0A0;
	clut[3] = 0xFFFFFF;
}

/**
 * Build 1-bit color palette (black & white)
 */
static void _build_color_lut1(volatile uint32_t *clut)
{
	clut[0] = 0x000000;
	clut[1] = 0xFFFFFF;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Initializes the LCD controller.
 * Configure SMC to access LCD controller at 64MHz MCK.
 */
void lcdc_configure(const struct _lcdc_desc *desc)
{
	lcdc_config = *desc;

	/* Reset layer information */
	lcdc_base.bpp = 0;
	lcdc_base.buffer = NULL;
	lcdc_base.dma_desc = &base_dma_desc;
#ifdef CONFIG_HAVE_LCDC_OVR1
	lcdc_ovr1.bpp = 0;
	lcdc_ovr1.buffer = NULL;
	lcdc_ovr1.dma_desc = &ovr1_dma_desc;
#endif
#ifdef CONFIG_HAVE_LCDC_OVR2
	lcdc_ovr2.bpp = 0;
	lcdc_ovr2.buffer = NULL;
	lcdc_ovr2.dma_desc = &ovr2_dma_desc;
#endif
	lcdc_heo.bpp = 0;
	lcdc_heo.buffer = NULL;
	lcdc_heo.dma_desc = &heo_dma_desc;
	lcdc_heo.dma_u_desc = &heo_dma_u_desc;
	lcdc_heo.dma_v_desc = &heo_dma_v_desc;
#ifdef CONFIG_HAVE_LCDC_PP
	/* Reset layer information */
	lcdc_pp.bpp = 0;
	lcdc_pp.buffer = NULL;
	lcdc_pp.dma_desc = &pp_dma_desc;
#endif
	/* No canvas selected */
	lcdc_canvas.buffer = NULL;

	/* Disable LCD controller */
	lcdc_off();

	/* Enable peripheral clock */
	pmc_configure_peripheral(ID_LCDC, NULL, true);
	if (pmc_has_system_clock(PMC_SYSTEM_CLOCK_LCD))
		pmc_enable_system_clock(PMC_SYSTEM_CLOCK_LCD);

	/* Timing Engine Configuration */

	/* Disable interrupt */
	LCDC->LCDC_LCDIDR = 0xFFFFFFFF;

	/* Configure channels */

	/* Base */
	LCDC->LCDC_BASECFG0 = LCDC_BASECFG0_DLBO |
	                      LCDC_BASECFG0_BLEN_AHB_INCR16;
	LCDC->LCDC_BASECFG1 = LCDC_BASECFG1_RGBMODE_24BPP_RGB_888_PACKED;

#ifdef CONFIG_HAVE_LCDC_OVR1
	/* Overlay 1, GA 0xFF */
	LCDC->LCDC_OVR1CFG0 = LCDC_OVR1CFG0_DLBO |
	                      LCDC_OVR1CFG0_BLEN_AHB_INCR16 |
	                      LCDC_OVR1CFG0_ROTDIS;
	LCDC->LCDC_OVR1CFG1 = LCDC_OVR1CFG1_RGBMODE_24BPP_RGB_888_PACKED;
	LCDC->LCDC_OVR1CFG9 = LCDC_OVR1CFG9_GA(0xFF) |
	                      LCDC_OVR1CFG9_GAEN;
#endif

#ifdef CONFIG_HAVE_LCDC_OVR2
	/* Overlay 2, GA 0xFF */
	LCDC->LCDC_OVR2CFG0 = LCDC_OVR2CFG0_DLBO |
	                      LCDC_OVR2CFG0_BLEN_AHB_INCR16 |
	                      LCDC_OVR2CFG0_ROTDIS;
	LCDC->LCDC_OVR2CFG1 = LCDC_OVR2CFG1_RGBMODE_24BPP_RGB_888_PACKED;
	LCDC->LCDC_OVR2CFG9 = LCDC_OVR2CFG9_GA(0xFF) |
	                      LCDC_OVR2CFG9_GAEN;
#endif

	/* High End Overlay, GA 0xFF */
	LCDC->LCDC_HEOCFG0 = LCDC_HEOCFG0_DLBO |
	                     LCDC_HEOCFG0_BLEN_AHB_INCR16 |
	                     LCDC_HEOCFG0_ROTDIS;
	LCDC->LCDC_HEOCFG1 = LCDC_HEOCFG1_RGBMODE_24BPP_RGB_888_PACKED;
	LCDC->LCDC_HEOCFG12 = LCDC_HEOCFG12_GA(0xFF) |
	                      LCDC_HEOCFG12_GAEN;

	LCDC->LCDC_HEOCFG14 = LCDC_HEOCFG14_CSCRY(0x94) |
	                      LCDC_HEOCFG14_CSCRU(0xCC) |
	                      LCDC_HEOCFG14_CSCRV(0) |
	                      LCDC_HEOCFG14_CSCYOFF;
	LCDC->LCDC_HEOCFG15 = LCDC_HEOCFG15_CSCGY(0x94) |
	                      LCDC_HEOCFG15_CSCGU(0x387) |
	                      LCDC_HEOCFG15_CSCGV(0x3CD) |
	                      LCDC_HEOCFG15_CSCUOFF;
	LCDC->LCDC_HEOCFG16 = LCDC_HEOCFG16_CSCBY(0x94)|
	                      LCDC_HEOCFG16_CSCBU(0) |
	                      LCDC_HEOCFG16_CSCBV(0x102) |
	                      LCDC_HEOCFG16_CSCVOFF;

	lcdc_on();
}

/**
 * Check if specified layer is working.
 * \param layer Layer ID.
 * \return 1 if layer is on.
 */
uint8_t lcdc_is_layer_on(uint8_t layer_id)
{
	const struct _layer_info *layer = &lcdc_layers[layer_id];

	if (!layer->reg_enable)
		return 0;

	return ((layer->reg_enable[2] & LCDC_BASECHSR_CHSR) > 0);
}

/**
 * Enable(turn on)/Disable(hide) specified layer.
 * \param layer_id Layer ID.
 * \param bEnDis Enable/Disable.
 */
void lcdc_enable_layer(uint8_t layer_id, bool enable)
{
	const struct _layer_info *layer = &lcdc_layers[layer_id];
#ifdef CONFIG_HAVE_LCDC_PP
	if (layer_id == LCDC_PP) {
		if (enable) {
			/* Disable the display by setting LCDC_LCDDIS.SYNCDIS bit */
			LCDC->LCDC_LCDDIS = LCDC_LCDDIS_SYNCDIS;
			/* select the PP layer */
			LCDC->LCDC_LCDCFG5 |= LCDC_LCDCFG5_PP;
			LCDC->LCDC_PPCHER = LCDC_PPCHER_CHEN | LCDC_PPCHER_UPDATEEN;
			while(LCDC->LCDC_PPCHSR & LCDC_PPCHSR_CHSR != LCDC_PPCHSR_CHSR);
			LCDC->LCDC_LCDEN = LCDC_LCDEN_SYNCEN;
		} else {
			LCDC->LCDC_LCDDIS = LCDC_LCDDIS_SYNCDIS;
			LCDC->LCDC_LCDCFG5 = 0;
			LCDC->LCDC_PPCHDR = LCDC_PPCHDR_CHDIS;
			LCDC->LCDC_LCDEN = LCDC_LCDEN_SYNCEN;
		}
	} else
#endif
	{
		if (!layer->reg_enable || !layer->reg_blender)
			return;

		if (enable) {
			layer->reg_enable[0] = LCDC_BASECHER_CHEN | LCDC_BASECHER_UPDATEEN;
			layer->reg_blender[0] |= LCDC_HEOCFG12_DMA | LCDC_HEOCFG12_OVR;
		} else {
			layer->reg_enable[1] = LCDC_BASECHDR_CHDIS;
			layer->reg_blender[0] &= ~(LCDC_HEOCFG12_DMA | LCDC_HEOCFG12_OVR);
		}
	}
}

/**
 * Refresh layer
 * \param layer_id Layer ID.
 */
void lcdc_refresh(uint8_t layer_id)
{
	const struct _layer_info *layer = &lcdc_layers[layer_id];

	if (!layer->reg_enable || !layer->reg_blender)
		return;

	if (layer->reg_enable[2] & LCDC_HEOCHSR_CHSR) {
		layer->reg_blender[0] |= LCDC_HEOCFG12_DMA;
		layer->reg_enable[0] = LCDC_HEOCHER_UPDATEEN;
	}
}

/**
 * Set display window position.
 * \param layer_id Layer ID.
 * \param x X position.
 * \param y Y position.
 */
void lcdc_set_position(uint8_t layer_id, uint32_t x, uint32_t y)
{
	const struct _layer_info *layer = &lcdc_layers[layer_id];
	uint32_t w, h;

	if (!layer->reg_enable || !layer->reg_win)
		return;

	w = (layer->reg_win[1] & LCDC_HEOCFG3_XSIZE_Msk) >> LCDC_HEOCFG3_XSIZE_Pos;
	h = (layer->reg_win[1] & LCDC_HEOCFG3_YSIZE_Msk) >> LCDC_HEOCFG3_YSIZE_Pos;

	if (x + w >= lcdc_config.width)
		x = lcdc_config.width - w;
	if (y + h >= lcdc_config.height)
		y = lcdc_config.height - h;

	layer->reg_win[0] = LCDC_HEOCFG2_XPOS(x) | LCDC_HEOCFG2_YPOS(y);
	if (layer->reg_enable[2] & LCDC_HEOCHSR_CHSR)
		layer->reg_enable[0] = LCDC_HEOCHER_UPDATEEN;
}

/**
 * Set Priority of layer (only for HEO now).
 * \param layer_id Layer ID
 * \param priority Priority value.
 */
void lcdc_set_priority(uint8_t layer_id, uint8_t priority)
{
#ifdef LCDC_HEOCFG12_VIDPRI
	if (layer_id != LCDC_HEO)
		return;

	if (priority)
		LCDC->LCDC_HEOCFG12 |= LCDC_HEOCFG12_VIDPRI;
	else
		LCDC->LCDC_HEOCFG12 &= ~LCDC_HEOCFG12_VIDPRI;
	LCDC->LCDC_HEOCHER = LCDC_HEOCHER_UPDATEEN;
#endif /* LCDC_HEOCFG12_VIDPRI */
}

/**
 * Return Priority of layer (only for HEO now).
 * \param layer_id Layer ID.
 */
uint8_t lcdc_get_priority(uint8_t layer_id)
{
#ifdef LCDC_HEOCFG12_VIDPRI
	if (layer_id != LCDC_HEO)
		return 0;

	return (LCDC->LCDC_HEOCFG12 & LCDC_HEOCFG12_VIDPRI) > 0;
#else
	return 0;
#endif /* LCDC_HEOCFG12_VIDPRI */
}

/**
 * Global & Local Alpha Enable/Disable
 * \param layer_id   Layer ID.
 * \param bEnDisLA Enable/Disable local  alpha.
 * \param bEnDisGA Enable/Disable global alpha.
 */
void lcdc_enable_alpha(uint8_t layer_id, bool enable_local, bool enable_global)
{
	const struct _layer_info *layer = &lcdc_layers[layer_id];
	uint32_t cfg;

	if (!layer->reg_enable || !layer->reg_blender)
		return;

	cfg = layer->reg_blender[0] & ~(LCDC_HEOCFG12_LAEN | LCDC_HEOCFG12_GAEN);
	if (enable_global)
		cfg |= LCDC_HEOCFG12_GAEN;
	if (enable_local)
		cfg |= LCDC_HEOCFG12_LAEN;
	layer->reg_blender[0] = cfg;
	layer->reg_enable[0] = LCDC_HEOCHER_UPDATEEN;
}

/**
 * Set alpha value
 * \param layer_id Layer ID (OVR1 or HEOR).
 * \param bReverse Reverse alpha (alpha -> 1 - alpha).
 * \param bAlpha   Global alpha value.
 */
void lcdc_set_alpha(uint8_t layer_id, bool reverse, uint8_t alpha)
{
	const struct _layer_info *layer = &lcdc_layers[layer_id];
	uint32_t cfg;

	if (!layer->reg_enable || !layer->reg_blender)
		return;

	cfg = layer->reg_blender[0] & ~(LCDC_HEOCFG12_REVALPHA | LCDC_HEOCFG12_GA_Msk);
	if (reverse)
		cfg |= LCDC_HEOCFG12_REVALPHA;
	layer->reg_blender[0] = cfg | LCDC_HEOCFG12_GA(alpha);
	layer->reg_enable[0] = LCDC_HEOCHER_UPDATEEN;
}

/**
 * Get alpha value
 * \param layer_id Layer ID (OVR1 or HEO).
 */
uint8_t lcdc_get_alpha(uint8_t layer_id)
{
	const struct _layer_info *layer = &lcdc_layers[layer_id];

	if (!layer->reg_blender)
		return 0;

	return (layer->reg_blender[0] & LCDC_HEOCFG12_GA_Msk) >> LCDC_HEOCFG12_GA_Pos;
}

/**
 * Enable and Set Color Keying
 * \param layer_id  Layer ID (OVR1 or HEO).
 * \param dest_keying Destination/Source keying.
 * \param color Color to matching.
 * \param mask  Color bit mask.
 */
void lcdc_set_color_keying(uint8_t layer_id, bool dest_keying,
			   uint32_t color, uint32_t mask)
{
	const struct _layer_info *layer = &lcdc_layers[layer_id];

	if (!layer->reg_enable || !layer->reg_blender || !layer->reg_color)
		return;

	/* Dest/Source Keying */
	if (dest_keying)
		layer->reg_blender[0] |= LCDC_HEOCFG12_DSTKEY;
	else
		layer->reg_blender[0] &= ~LCDC_HEOCFG12_DSTKEY;

	/* Activate Color Keying */
	layer->reg_blender[0] |= LCDC_HEOCFG12_CRKEY;

	/* Program Color Keying */
	layer->reg_color[1] = color;
	layer->reg_color[2] = mask;

	/* Update */
	layer->reg_enable[0] = LCDC_HEOCHER_UPDATEEN;
}

/**
 * Disable Color Keying
 * \param layer_id  Layer ID (OVR1 or HEO).
 */
void lcdc_disable_color_keying(uint8_t layer_id)
{
	const struct _layer_info *layer = &lcdc_layers[layer_id];

	if (!layer->reg_enable || !layer->reg_blender || !layer->reg_color)
		return;

	layer->reg_blender[0] &= ~LCDC_HEOCFG12_CRKEY;
	layer->reg_color[2] = 0;

	/* Update */
	layer->reg_enable[0] = LCDC_HEOCHER_UPDATEEN;
}

/**
 * Set Color Lookup Table
 * \param layer_id   Layer ID (OVR1 or HEO).
 * \param pCLUT    Pointer to color lookup table.
 * \param bpp      Bits Per Pixel (1, 2, 4, 8).
 */
void lcdc_set_color_lut(uint8_t layer_id, uint32_t *clut, uint8_t bpp)
{
	const struct _layer_info *layer = &lcdc_layers[layer_id];
	struct _layer_data *data = layer->data;

	if (!layer->reg_clut || !data)
		return;

	data->bpp = bpp;

	/* Customize CLUT */
	if (clut) {
		uint32_t i;
		for (i = 0; i < (1 << bpp); i++)
			layer->reg_clut[i] = clut[i];
	}
	/* Build CLUT */
	else {
		switch (bpp) {
		case 1:
			_build_color_lut1(layer->reg_clut);
			break;
		case 2:
			_build_color_lut2(layer->reg_clut);
			break;
		case 4:
			_build_color_lut4(layer->reg_clut);
			break;
		case 8:
			_build_color_lut8(layer->reg_clut);
			break;
		}
	}
}

/**
 * Display an image on specified layer.
 * (Image scan origion: Left -> Right, Top -> Bottom.)
 * \note w & h should be the rotated result.
 * \note for LCDC_BASE: x, y don't care. w always > 0.
 * \note for LCDC_HEO:imgW & imgH is used.
 * \param layer_id  Layer ID (OVR1 or HEO).
 * \param buffer Pointer to image data.
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
void * lcdc_put_image_rotated(uint8_t layer_id,
			     void *buffer, uint8_t bpp,
			     uint32_t x, uint32_t y,
			     int32_t w, int32_t h,
			     uint32_t img_w, uint32_t img_h, int16_t rotation)
{
	const struct _layer_info *layer = &lcdc_layers[layer_id];
	struct _layer_data *data = layer->data;

	uint8_t bottom_up = (h < 0);
	uint8_t right_left = (w < 0);
	uint32_t padding = 0;
	int32_t src_w, src_h;
	uint32_t bits_per_row, bytes_per_row;
	uint32_t bytes_per_pixel = bpp >> 3;

	void *old_buffer = data->buffer;

	if (!layer->reg_cfg)
		return old_buffer;

	//printf("Show %x @ %d: (%d,%d)+(%d,%d) img %d x %d * %d\n\r", buffer, layer_id, x, y, w, h, img_w, img_h, bpp);

	switch (bpp) {
	/*  RGB 565 */
	case 16:
#ifdef LCDC_HEOCFG1_YUVEN
		if ((layer->reg_cfg[1] & LCDC_HEOCFG1_YUVEN) == LCDC_HEOCFG1_YUVEN) {
			layer->reg_cfg[1] = layer->reg_cfg[1] & (~LCDC_HEOCFG1_YUVMODE_Msk) | LCDC_HEOCFG1_YUVMODE_16BPP_YCBCR_MODE0;
		} else
#endif
		{
			layer->reg_cfg[1] = LCDC_HEOCFG1_RGBMODE_16BPP_RGB_565;
		}
		break;
	/*  RGB  888 packed */
	case 24:
		layer->reg_cfg[1] = LCDC_HEOCFG1_RGBMODE_24BPP_RGB_888_PACKED;
		break;
	/* ARGB 8888 */
	case 32:
		layer->reg_cfg[1] = LCDC_HEOCFG1_RGBMODE_32BPP_ARGB_8888;
		break;
	default:
		return old_buffer;
	}

	/* Windows position & size check */
	if (h < 0)
		h = -h;
	if (w < 0)
		w = -w;
	if (x + w > lcdc_config.width) {
		//printf("! w %d -> %d\n\r", w, lcdc_config.width-x);
		w = lcdc_config.width - x;
	}
	if (y + h > lcdc_config.height) {
		//printf("! h %d -> %d\n\r", h, lcdc_config.height-y);
		h = lcdc_config.height - y;
	}
	if (w == 0)
		w++;
	if (h == 0)
		h++;
	if (img_w == 0)
		img_w++;
	if (img_h == 0)
		img_h++;

	/* Only 0,(-)90,(-)180,(-)270 accepted */
	switch (rotation) {
	case 0:
	case 90:
	case 180:
	case 270:
		break;
	case -90:
	case -180:
	case -270:
		rotation += 360;
		break;
	default:
		return NULL;
	}

	/* Setup display buffer & window */
	if (buffer)
		data->buffer = buffer;
	else
		buffer = data->buffer;

	/* Set display buffer & mode */
	bits_per_row = img_w * bpp;
	bytes_per_row = bits_per_row >> 3;
	if (bits_per_row & 0x7)
		bytes_per_row++;
	if (bytes_per_row & 0x3)
		padding = 4 - (bytes_per_row & 0x3);

	/* No X mirror supported layer, no Right->Left scan */
	if (!layer->stride_supported)
		right_left = 0;

	/* --------- Mirror & then rotate --------- */
	/* Normal direction: Left,Top -> Right,Down */
	if ((!right_left && !bottom_up && rotation == 0)
	    || (right_left && bottom_up && rotation == 180)) {
#ifdef LCDC_HEOCFG1_YUVEN
		if(layer->reg_cfg[1] & LCDC_HEOCFG1_YUVEN) {
			/* No rotation optimization */
			layer->reg_cfg[0] = LCDC_HEOCFG0_BLEN(0x2) | LCDC_HEOCFG0_ROTDIS;
			layer->reg_cfg[1] &= ~LCDC_HEOCFG1_YUV422ROT;
			/* X0 ++ */
			if (layer->stride_supported)
					layer->reg_stride[1] = LCDC_HEOCFG6_PSTRIDE(0);
			/* Y0 ++ */
			layer->reg_stride[0] = LCDC_HEOCFG5_XSTRIDE(0);
			/* Pointer to Left,Top (x0,y0) */
		} else
#endif
		{
			/* No rotation optimization */
			layer->reg_cfg[0] |= LCDC_HEOCFG0_ROTDIS;
			/* X0 ++ */
			if (layer->stride_supported)
				layer->reg_stride[1] = LCDC_HEOCFG6_PSTRIDE(0);
			/* Y0 ++ */
			layer->reg_stride[0] = LCDC_HEOCFG5_XSTRIDE(padding);
			/* Pointer to Left,Top (x0,y0) */
		}
	}
	/* X mirror: Right,Top -> Left,Down */
	else if ((right_left && !bottom_up && rotation == 0)
		 || (!right_left && bottom_up && rotation == 180)) {
#ifdef LCDC_HEOCFG1_YUVEN
		if ((layer->reg_cfg[1] & LCDC_HEOCFG1_YUVEN) == LCDC_HEOCFG1_YUVEN) {
			/* No rotation optimization */
			layer->reg_cfg[0] = LCDC_HEOCFG0_BLEN(0x2) | LCDC_HEOCFG0_ROTDIS;
			layer->reg_cfg[1] &= ~LCDC_HEOCFG1_YUV422ROT;
			/* X0 ++ */
			if (layer->stride_supported)
					layer->reg_stride[1] = LCDC_HEOCFG6_PSTRIDE(0 - 2 * bytes_per_pixel - 4);
			/* Y0 ++ */
			layer->reg_stride[0] = LCDC_HEOCFG5_XSTRIDE(bytes_per_row * 2 - 2 * bytes_per_pixel - 4);
			/* Pointer to Right,Top (x1,y0) */
			buffer = (void *)((uint32_t) buffer + bytes_per_row - 4);
		} else
#endif
		{
			/* No rotation optimization */
			layer->reg_cfg[0] |= LCDC_HEOCFG0_ROTDIS;
			/* X1 -- */
			if (layer->stride_supported)
				layer->reg_stride[1] = LCDC_HEOCFG6_PSTRIDE(0 - 2 * bytes_per_pixel);
			/* Y0 ++ */
			layer->reg_stride[0] = LCDC_HEOCFG5_XSTRIDE(bytes_per_row * 2 + padding - 2 * bytes_per_pixel);
			/* Pointer to Right,Top (x1,y0) */
			buffer = (void *)((uint32_t) buffer + bytes_per_pixel * (img_w - 1));
		}
	}
	/* Y mirror: Left,Down -> Right,Top */
	else if ((!right_left && bottom_up && rotation == 0)
		 || (right_left && !bottom_up && rotation == 180)) {
#ifdef LCDC_HEOCFG1_YUVEN
		if(layer->reg_cfg[1] & LCDC_HEOCFG1_YUVEN) {
			/* No rotation optimization */
			layer->reg_cfg[0] = LCDC_HEOCFG0_BLEN(0x2) | LCDC_HEOCFG0_ROTDIS;
			layer->reg_cfg[1] &= ~LCDC_HEOCFG1_YUV422ROT;
			/* X0 ++ */
			if (layer->stride_supported)
					layer->reg_stride[1] = LCDC_HEOCFG6_PSTRIDE(0);
			/* Y0 ++ */
			layer->reg_stride[0] = LCDC_HEOCFG5_XSTRIDE(0 - bytes_per_row * 2);
			/* Pointer to Right,Top (x1,y0) */
			buffer = (void *)((uint32_t) buffer + bytes_per_row * (img_h - 1));
		} else
#endif
		{
			/* No rotation optimization */
			layer->reg_cfg[0] |= LCDC_HEOCFG0_ROTDIS;
			/* X0 ++ */
			if (layer->stride_supported)
				layer->reg_stride[1] = LCDC_HEOCFG6_PSTRIDE(0);
			/* Y1 -- */
			layer->reg_stride[0] = LCDC_HEOCFG5_XSTRIDE(0 - (bytes_per_row * 2 + padding));
			/* Pointer to Left,Down (x0,y1) */
			buffer = (void *)((uint32_t) buffer + (bytes_per_row + padding) * (img_h - 1));
		}
	}
	/* X,Y mirror: Right,Top -> Left,Down */
	else if ((right_left && bottom_up && rotation == 0)
		 || (!right_left && !bottom_up && rotation == 180)) {
#ifdef LCDC_HEOCFG1_YUVEN
		if(layer->reg_cfg[1] & LCDC_HEOCFG1_YUVEN) {
			/* No rotation optimization */
			layer->reg_cfg[0] = LCDC_HEOCFG0_BLEN(0x2) | LCDC_HEOCFG0_ROTDIS;
			layer->reg_cfg[1] &= ~LCDC_HEOCFG1_YUV422ROT;
			/* X0 ++ */
			if (layer->stride_supported)
				  layer->reg_stride[1] = LCDC_HEOCFG6_PSTRIDE(0);
			/* Y0 ++ */
			layer->reg_stride[0] = LCDC_HEOCFG5_XSTRIDE(0 - bytes_per_row * 2);
			/* Pointer to Right,Top (x1,y0) */
			buffer = (void *)((uint32_t) buffer + bytes_per_row * (img_h-1));
		} else
#endif
		{
			/* No rotation optimization */
			layer->reg_cfg[0] |= LCDC_HEOCFG0_ROTDIS;
			/* X1 -- */
			if (layer->stride_supported)
				layer->reg_stride[1] = LCDC_HEOCFG6_PSTRIDE(0 - 2 * bytes_per_pixel);
			/* Y1 -- */
			layer->reg_stride[0] = LCDC_HEOCFG5_XSTRIDE(0 - (bytes_per_pixel * 2 + padding));
			/* Pointer to Left,Down (x1,y1) */
			buffer = (void *)((uint32_t) buffer + (bytes_per_row + padding) * (img_h - 1) + (bytes_per_pixel) * (img_w - 1));
		}
	}
	/* Rotate  90: Down,Left -> Top,Right (with w,h swap) */
	else if ((!right_left && !bottom_up && rotation == 90)
		 || (right_left && bottom_up && rotation == 270)) {
#ifdef LCDC_HEOCFG1_YUVEN
		if(layer->reg_cfg[1] & LCDC_HEOCFG1_YUVEN) {
			/* No rotation optimization */
			layer->reg_cfg[0] = LCDC_HEOCFG0_BLEN(0x2) | LCDC_HEOCFG0_ROTDIS;
			layer->reg_cfg[1] |= LCDC_HEOCFG1_YUV422ROT;
			/* X0 ++ */
			if (layer->stride_supported)
					layer->reg_stride[1] = LCDC_HEOCFG6_PSTRIDE(0 - bytes_per_row - 4);
			/* Y0 ++ */
			layer->reg_stride[0] = LCDC_HEOCFG5_XSTRIDE(bytes_per_row * (img_h-1));
			/* Pointer to Right,Top (x1,y0) */
			buffer = (void *)((uint32_t) buffer + bytes_per_row * (img_h - 1));
		} else
#endif
		{
			/* No rotation optimization */
			layer->reg_cfg[0] |= LCDC_HEOCFG0_ROTDIS;
			/* Y -- as pixels in row */
			if (layer->stride_supported)
				layer->reg_stride[1] = LCDC_HEOCFG6_PSTRIDE(0 - (bytes_per_pixel + bytes_per_row + padding));
			/* X ++ as rows */
			layer->reg_stride[0] = LCDC_HEOCFG5_XSTRIDE((bytes_per_row + padding) * (img_h - 1));
			/* Pointer to Bottom,Left */
			buffer = (void *)((uint32_t) buffer + (bytes_per_row + padding) * (img_h - 1));
		}
	}
	/* Rotate 270: Top,Right -> Down,Left (with w,h swap) */
	else if ((!right_left && !bottom_up && rotation == 270)
		 || (right_left && bottom_up && rotation == 90)) {
#ifdef LCDC_HEOCFG1_YUVEN
		if(layer->reg_cfg[1] & LCDC_HEOCFG1_YUVEN) {
			/* No rotation optimization */
			layer->reg_cfg[0] = LCDC_HEOCFG0_BLEN(0x2) | LCDC_HEOCFG0_ROTDIS;
			layer->reg_cfg[1] |= LCDC_HEOCFG1_YUV422ROT;
			/* X0 ++ */
			if (layer->stride_supported)
					layer->reg_stride[1] = LCDC_HEOCFG6_PSTRIDE(bytes_per_row - 4);
			/* Y0 ++ */
			layer->reg_stride[0] = LCDC_HEOCFG5_XSTRIDE((bytes_per_row * (1 - img_h) - 4 - 4));
			/* Pointer to Right,Top (x1,y0) */
			buffer = (void *)((uint32_t) buffer + bytes_per_row - 4);
		} else
#endif
		{
			/* No rotation optimization */
			layer->reg_cfg[0] |= LCDC_HEOCFG0_ROTDIS;
			/* Y ++ as pixels in row */
			if (layer->stride_supported)
				layer->reg_stride[1] = LCDC_HEOCFG6_PSTRIDE(bytes_per_row + padding - bytes_per_pixel);
			/* X -- as rows */
			layer->reg_stride[0] = LCDC_HEOCFG5_XSTRIDE(0 - 2 * bytes_per_pixel - (bytes_per_row + padding) * (img_h - 1));
			/* Pointer to top right */
			buffer = (void *)((uint32_t) buffer + bytes_per_pixel * (img_w - 1));
		}
	}
	/* Mirror X then Rotate 90: Down,Right -> Top,Left */
	else if ((right_left && !bottom_up && rotation == 90)
		 || (!right_left && bottom_up && rotation == 270)) {
#ifdef LCDC_HEOCFG1_YUVEN
		if(layer->reg_cfg[1] & LCDC_HEOCFG1_YUVEN) {
			/* No rotation optimization */
			layer->reg_cfg[0] = LCDC_HEOCFG0_BLEN(0x2) | LCDC_HEOCFG0_ROTDIS;
			layer->reg_cfg[1] |= LCDC_HEOCFG1_YUV422ROT;
			/* X0 ++ */
			if (layer->stride_supported)
					layer->reg_stride[1] = LCDC_HEOCFG6_PSTRIDE(0 - bytes_per_row - 4);
			/* Y0 ++ */
			layer->reg_stride[0] = LCDC_HEOCFG5_XSTRIDE(bytes_per_row * (img_h - 1) - 2 * bytes_per_pixel - 4);
			/* Pointer to Right,Top (x1,y0) */
			buffer = (void *)((uint32_t) buffer + bytes_per_row * img_h - 4);
		} else
#endif
		{
			/* No rotation optimization */
			layer->reg_cfg[0] |= LCDC_HEOCFG0_ROTDIS;
			/* Y -- as pixels in row */
			if (layer->stride_supported)
				layer->reg_stride[1] = LCDC_HEOCFG6_PSTRIDE(0 - (bytes_per_pixel + bytes_per_row + padding));
			/* X -- as rows */
			layer->reg_stride[0] = LCDC_HEOCFG5_XSTRIDE(0 - 2 * bytes_per_pixel + (bytes_per_row + padding) * (img_h - 1));
			/* Pointer to down right (x1,y1) */
			buffer = (void *)((uint32_t) buffer + (bytes_per_row + padding) * (img_h - 1) + (bytes_per_pixel) * (img_w - 1));
		}
	}
	/* Mirror Y then Rotate 90: Top,Left -> Down,Right */
	else if ((!right_left && bottom_up && rotation == 90)
		 || (right_left && !bottom_up && rotation == 270)) {
#ifdef LCDC_HEOCFG1_YUVEN
		if(layer->reg_cfg[1] & LCDC_HEOCFG1_YUVEN) {
			/* No rotation optimization */
			layer->reg_cfg[0] = LCDC_HEOCFG0_BLEN(0x2) | LCDC_HEOCFG0_ROTDIS;
			layer->reg_cfg[1] |= LCDC_HEOCFG1_YUV422ROT;
			/* X0 ++ */
			if (layer->stride_supported)
					layer->reg_stride[1] = LCDC_HEOCFG6_PSTRIDE(bytes_per_row - 4);
			/* Y0 ++ */
			layer->reg_stride[0] = LCDC_HEOCFG5_XSTRIDE(0 - (bytes_per_row * (img_h - 1)));
			/* Pointer to Right,Top (x1,y0) */
		} else
#endif
		{
			/* No rotation optimization */
			layer->reg_cfg[0] |= LCDC_HEOCFG0_ROTDIS;
			/* Y ++ as pixels in row */
			if (layer->stride_supported)
				layer->reg_stride[1] = LCDC_HEOCFG6_PSTRIDE(bytes_per_row + padding - bytes_per_pixel);
			/* X ++ as rows */
			layer->reg_stride[0] = LCDC_HEOCFG5_XSTRIDE(0 - (bytes_per_row + padding) * (img_h - 1));
			/* Pointer to top left (x0,y0) */
		}
	}

	/** DMA is running, just add new descriptor to queue */
	if (layer->reg_blender[0] & LCDC_HEOCFG12_DMA) {
		data->dma_desc->addr = (uint32_t)buffer;
		data->dma_desc->ctrl = LCDC_HEOCTRL_DFETCH;
		data->dma_desc->next = (uint32_t)data->dma_desc;
		cache_clean_region(data->dma_desc, sizeof(*(data->dma_desc)));
		layer->reg_dma_head[0] = (uint32_t)data->dma_desc;
		layer->reg_enable[0] = LCDC_HEOCHER_A2QEN;
	} else {
		/* 2. Write the channel descriptor (DSCR) structure in the system memory by
		   writing DSCR.CHXADDR Frame base address, DSCR.CHXCTRL channel control
		   and DSCR.CHXNEXT next descriptor location.
		   3. If more than one descriptor is expected, the DFETCH field of
		   DSCR.CHXCTRL is set to one to enable the descriptor fetch operation.
		   4. Write the DSCR.CHXNEXT register with the address location of the
		   descriptor structure and set DFETCH field of the DSCR.CHXCTRL register
		   to one. */
		_set_dma_desc(buffer, data->dma_desc, layer->reg_dma_head);
	}

	/* Set window & position */
	if (layer->reg_win) {
		layer->reg_win[0] = LCDC_HEOCFG2_XPOS(x) | LCDC_HEOCFG2_YPOS(y);
		layer->reg_win[1] = LCDC_HEOCFG3_XSIZE(w - 1) | LCDC_HEOCFG3_YSIZE(h - 1);
	}

	/* Scaling setup */
	if (layer->reg_win && layer->reg_scale) {
		/* Image size only used in scaling */
		/* Scaling target */
		if (rotation == 90 || rotation == 270) {
			src_w = img_h;
			src_h = img_w;
		} else {
			src_w = img_w;
			src_h = img_h;
		}
		layer->reg_win[2] = LCDC_HEOCFG4_XMEMSIZE(src_w - 1)
			| LCDC_HEOCFG4_YMEMSIZE(src_h - 1);
		/* Scaled */
		if (w != src_w || h != src_h) {
			uint16_t scale_w, scale_h;
			_compute_scaling_factors(layer, &scale_w, &scale_h);
			layer->reg_scale[0] = LCDC_HEOCFG13_YFACTOR(scale_h)
				| LCDC_HEOCFG13_XFACTOR(scale_w)
				| LCDC_HEOCFG13_SCALEN;
		}
		/* Disable scaling */
		else {
			layer->reg_scale[0] = 0;
		}
	}
	/* Enable DMA */
	if (buffer) {
		layer->reg_blender[0] |= LCDC_HEOCFG12_DMA | LCDC_HEOCFG12_OVR;
	}
	/* Enable & Update */
	/* 5. Enable the relevant channel by writing one to the CHEN field of the
	   CHXCHER register. */
	layer->reg_enable[0] = LCDC_HEOCHER_UPDATEEN | LCDC_HEOCHER_CHEN;

	/* 6. An interrupt may be raised if unmasked when the descriptor has been
	   loaded.  */

	return old_buffer;
}

/**
 * Display an image on specified layer.
 * (Image scan: Left -> Right, Top -> Bottom.)
 * \param layer_id  Layer ID (OVR1 or HEO).
 * \param buffer Pointer to image data.
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
void * lcdc_put_image_scaled(uint8_t layer_id, void *buffer, uint8_t bpp,
		uint32_t x, uint32_t y, int32_t w, int32_t h,
		uint32_t img_w, uint32_t img_h)
{
	return lcdc_put_image_rotated(layer_id, buffer, bpp, x, y, w, h, img_w,
			img_h, 0);
}

/**
 * Display an image on specified layer.
 * (Image scan: Left -> Right, Top -> Bottom.)
 * \param layer_id  Layer ID (OVR1 or HEO).
 * \param buffer Pointer to image data.
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
void * lcdc_put_image(uint8_t layer_id, void *buffer, uint8_t bpp,
		uint32_t x, uint32_t y, int32_t w, int32_t h)
{
	return lcdc_put_image_rotated(layer_id, buffer, bpp, x, y, w, h, w,
			h < 0 ? -h : h, 0);
}

/**
 * Start display on base layer
 * \param buffer   Pointer to image data.
 * \param bpp       Bits Per Pixel.
 * \param bBottomUp Scan from bottom to top.
 * \return Pointer to old display image data.
 */
void * lcdc_show_base(void *buffer, uint8_t bpp, bool bottom_up)
{
	return lcdc_put_image(LCDC_BASE, buffer, bpp, 0, 0, lcdc_config.width,
			bottom_up ? -lcdc_config.height : lcdc_config.height);
}

void lcdc_base_auto_loop(void *buffer, uint32_t size, uint32_t slides)
{
	uint32_t i;
	ALIGNED(16) static struct _lcdc_dma_desc dma_desc[40];
	if (ARRAY_SIZE(dma_desc) < slides * 10) {
		trace_warning("The DMA link size is not suitable for showing the loop effects on the base layer!");
		return;
	}
	for (i = 0; i < ARRAY_SIZE(dma_desc); i++) {
		dma_desc[i].addr = (uint32_t)buffer + (i / 10) * (size / slides);
		dma_desc[i].ctrl = LCDC_HEOCTRL_DFETCH;
		dma_desc[i].next = (uint32_t)&dma_desc[i+1];
	}
	dma_desc[i-1].next = (uint32_t)&dma_desc[0];
	cache_clean_region(dma_desc, sizeof(dma_desc));
	lcdc_layers[LCDC_BASE].reg_dma_head[0] = (uint32_t)dma_desc;
	lcdc_layers[LCDC_BASE].reg_enable[0] = LCDC_HEOCHER_A2QEN;
}

/**
 * Stop display on base layer
 */
void lcdc_stop_base(void)
{
	if (!(LCDC->LCDC_BASECHSR & LCDC_BASECHSR_CHSR))
		return;

	/* 1. Clear the DFETCH bit in the DSCR.CHXCTRL field of the DSCR structure
	   will disable the channel at the end of the frame. */
	/* 2. Set the DSCR.CHXNEXT field of the DSCR structure will disable the
	   channel at the end of the frame. */
	_clear_dma_desc(lcdc_base.dma_desc, &LCDC->LCDC_BASEHEAD);

	/* 3. Writing one to the CHDIS field of the CHXCHDR register will disable
	   the channel at the end of the frame. */
	LCDC->LCDC_BASECHDR = LCDC_BASECHDR_CHDIS;

	/* 4. Writing one to the CHRST field of the CHXCHDR register will disable
	   the channel immediately. This may occur in the middle of the image. */

	/* 5. Poll CHSR field in the CHXCHSR register until the channel is
	   successfully disabled. */
	while (LCDC->LCDC_BASECHSR & LCDC_BASECHSR_CHSR);
}

#ifdef CONFIG_HAVE_LCDC_OVR1
/**
 * Start display on overlay 1 layer
 */
void *lcdc_show_ovr1(void *buffer, uint8_t bpp, uint32_t x, uint32_t y,
		int32_t w, int32_t h)
{
	return lcdc_put_image(LCDC_OVR1, buffer, bpp, x, y, w, h);
}

/**
 * Stop display on overlay 1 layer
 */
void lcdc_stop_ovr1(void)
{
	if (!(LCDC->LCDC_OVR1CHSR & LCDC_OVR1CHSR_CHSR))
		return;

	/* 1. Clear the DFETCH bit in the DSCR.CHXCTRL field of the DSCR structure
	   will disable the channel at the end of the frame. */
	/* 2. Set the DSCR.CHXNEXT field of the DSCR structure will disable the
	   channel at the end of the frame. */
	_clear_dma_desc(lcdc_ovr1.dma_desc, &LCDC->LCDC_OVR1HEAD);

	/* 3. Writing one to the CHDIS field of the CHXCHDR register will disable
	   the channel at the end of the frame. */
	LCDC->LCDC_OVR1CHDR = LCDC_OVR1CHDR_CHDIS;

	/* 4. Writing one to the CHRST field of the CHXCHDR register will disable
	   the channel immediately. This may occur in the middle of the image. */

	/* 5. Poll CHSR field in the CHXCHSR register until the channel is
	   successfully disabled. */
	while (LCDC->LCDC_OVR1CHSR & LCDC_OVR1CHSR_CHSR);
}
#endif /* CONFIG_HAVE_LCDC_OVR1 */

/**
 * Start display on High End Overlay layer
 */
void *lcdc_show_heo(void *buffer, uint8_t bpp, uint32_t x, uint32_t y,
		int32_t w, int32_t h, uint32_t img_w, uint32_t img_h)
{
	return lcdc_put_image_rotated(LCDC_HEO, buffer, bpp, x, y, w, h,
			img_w, img_h, 0);
}

/**
 * Stop display on High End Overlay layer
 */
void lcdc_stop_heo(void)
{
	if (!(LCDC->LCDC_HEOCHSR & LCDC_HEOCHSR_CHSR))
		return;

	/* 1. Clear the DFETCH bit in the DSCR.CHXCTRL field of the DSCR structure
	   will disable the channel at the end of the frame. */
	/* 2. Set the DSCR.CHXNEXT field of the DSCR structure will disable the
	   channel at the end of the frame. */
	_clear_dma_desc(lcdc_heo.dma_desc, &LCDC->LCDC_HEOHEAD);
	_clear_dma_desc(lcdc_heo.dma_u_desc, &LCDC->LCDC_HEOUHEAD);
	_clear_dma_desc(lcdc_heo.dma_v_desc, &LCDC->LCDC_HEOVHEAD);

	/* 3. Writing one to the CHDIS field of the CHXCHDR register will disable
	   the channel at the end of the frame. */
	LCDC->LCDC_HEOCHDR = LCDC_HEOCHDR_CHDIS;

	/* 4. Writing one to the CHRST field of the CHXCHDR register will disable
	   the channel immediately. This may occur in the middle of the image. */

	/* 5. Poll CHSR field in the CHXCHSR register until the channel is
	   successfully disabled. */
	while (LCDC->LCDC_HEOCHSR & LCDC_HEOCHSR_CHSR);
}

/**
 * \brief Turn on the LCD.
 */
void lcdc_on(void)
{
	uint32_t cfg0;
	uint32_t pixel_clock = lcdc_config.framerate;
	uint32_t lcd_clock;
	pixel_clock *= lcdc_config.timing_hpw + lcdc_config.timing_hbp +
		lcdc_config.width + lcdc_config.timing_hfp;
	pixel_clock *= lcdc_config.timing_vpw + lcdc_config.timing_vbp +
		lcdc_config.height + lcdc_config.timing_vfp;

	/* Enable peripheral clock and LCD system clock */
	if (pmc_has_system_clock(PMC_SYSTEM_CLOCK_LCD)) {
		pmc_configure_peripheral(ID_LCDC, NULL, true);
		pmc_enable_system_clock(PMC_SYSTEM_CLOCK_LCD);
		lcd_clock = pmc_get_master_clock();
	} else {
#ifdef CONFIG_HAVE_PMC_GENERATED_CLOCKS
		struct _pmc_periph_cfg cfg = {
			.gck = {
				.css = PMC_PCR_GCKCSS_MCK_CLK,
				.div = 2,
			},
		};
		pmc_configure_peripheral(ID_LCDC, &cfg, true);
		lcd_clock = pmc_get_gck_clock(ID_LCDC);
#else
		lcd_clock = pmc_get_master_clock();
#endif
	}
	/* 1. Configure LCD timing parameters, signal polarity and clock period. */
#ifdef LCDC_LCDCFG0_CLKSEL
	cfg0 = LCDC_LCDCFG0_CLKDIV((lcd_clock * 2) / pixel_clock - 2) |
	       LCDC_LCDCFG0_CGDISBASE |
	       LCDC_LCDCFG0_CGDISHEO |
	       LCDC_LCDCFG0_CLKPWMSEL |
	       LCDC_LCDCFG0_CLKSEL;
#else
	cfg0 = LCDC_LCDCFG0_CLKDIV(lcd_clock / pixel_clock - 2) |
	       LCDC_LCDCFG0_CGDISBASE |
	       LCDC_LCDCFG0_CGDISHEO |
	       LCDC_LCDCFG0_CLKPWMSEL;
#endif

#ifdef LCDC_LCDCFG0_CGDISOVR1
	cfg0 |= LCDC_LCDCFG0_CGDISOVR1;
#endif
#ifdef LCDC_LCDCFG0_CGDISOVR2
	cfg0 |= LCDC_LCDCFG0_CGDISOVR2;
#endif
#ifdef LCDC_LCDCFG0_CGDISHCR
	cfg0 |= LCDC_LCDCFG0_CGDISHCR;
#endif
#ifdef LCDC_LCDCFG0_CGDISPP
	cfg0 |= LCDC_LCDCFG0_CGDISPP;
#endif
	_wait_for_clock_domain_sync();
	LCDC->LCDC_LCDCFG0 = cfg0;

	_wait_for_clock_domain_sync();
	LCDC->LCDC_LCDCFG1 = LCDC_LCDCFG1_VSPW(lcdc_config.timing_vpw - 1) |
	                     LCDC_LCDCFG1_HSPW(lcdc_config.timing_hpw - 1);

	_wait_for_clock_domain_sync();
	LCDC->LCDC_LCDCFG2 = LCDC_LCDCFG2_VBPW(lcdc_config.timing_vbp) |
	                     LCDC_LCDCFG2_VFPW(lcdc_config.timing_vfp - 1);

	_wait_for_clock_domain_sync();
	LCDC->LCDC_LCDCFG3 = LCDC_LCDCFG3_HBPW(lcdc_config.timing_hbp - 1) |
	                     LCDC_LCDCFG3_HFPW(lcdc_config.timing_hfp - 1);

	_wait_for_clock_domain_sync();
	LCDC->LCDC_LCDCFG4 = LCDC_LCDCFG4_RPF(lcdc_config.height - 1) |
	                     LCDC_LCDCFG4_PPL(lcdc_config.width - 1);

	_wait_for_clock_domain_sync();
	LCDC->LCDC_LCDCFG5 = LCDC_LCDCFG5_GUARDTIME(30) |
	                     LCDC_LCDCFG5_MODE_OUTPUT_24BPP |
	                     LCDC_LCDCFG5_DISPDLY |
	                     LCDC_LCDCFG5_VSPDLYS |
	                     LCDC_LCDCFG5_VSPOL |
	                     LCDC_LCDCFG5_HSPOL;

	_wait_for_clock_domain_sync();
	LCDC->LCDC_LCDCFG6 = LCDC_LCDCFG6_PWMCVAL(0xF0) |
	                     LCDC_LCDCFG6_PWMPOL |
	                     LCDC_LCDCFG6_PWMPS(5);

	/* 2. Enable the Pixel Clock by writing one to the CLKEN field of the
	   LCDC_LCDEN register. */
	_wait_for_clock_domain_sync();
	LCDC->LCDC_LCDEN = LCDC_LCDEN_CLKEN;

	/* 3. Poll CLKSTS field of the LCDC_LCDSR register to check that the clock
	   is running. */
	while (!(LCDC->LCDC_LCDSR & LCDC_LCDSR_CLKSTS));

	/* 4. Enable Horizontal and Vertical Synchronization by writing one to the
	   SYNCEN field of the LCDC_LCDEN register. */
	_wait_for_clock_domain_sync();
	LCDC->LCDC_LCDEN = LCDC_LCDEN_SYNCEN;

	/* 5. Poll LCDSTS field of the LCDC_LCDSR register to check that the
	   synchronization is up. */
	while (!(LCDC->LCDC_LCDSR & LCDC_LCDSR_LCDSTS));

	/* 6. Enable the display power signal writing one to the DISPEN field of the
	   LCDC_LCDEN register. */
	_wait_for_clock_domain_sync();
	LCDC->LCDC_LCDEN = LCDC_LCDEN_DISPEN;

	/* 7. Poll DISPSTS field of the LCDC_LCDSR register to check that the power
	   signal is activated. */
	while (!(LCDC->LCDC_LCDSR & LCDC_LCDSR_DISPSTS));

	/* 8. Enable backlight */
	_wait_for_clock_domain_sync();
	LCDC->LCDC_LCDEN = LCDC_LCDEN_PWMEN;
}

/**
 * \brief Turn off the LCD.
 */
void lcdc_off(void)
{
	/* 1. Clear the DFETCH bit in the DSCR.CHXCTRL field of the DSCR structure
	   will disable the channel at the end of the frame. */

	/* 2. Set the DSCR.CHXNEXT field of the DSCR structure will disable the
	   channel at the end of the frame. */

	/* Disable all DMA channel descriptors */
	_clear_dma_desc(lcdc_base.dma_desc, &LCDC->LCDC_BASEHEAD);
#ifdef CONFIG_HAVE_LCDC_OVR1
	_clear_dma_desc(lcdc_ovr1.dma_desc, &LCDC->LCDC_OVR1HEAD);
#endif
#ifdef CONFIG_HAVE_LCDC_OVR2
	_clear_dma_desc(lcdc_ovr2.dma_desc, &LCDC->LCDC_OVR2HEAD);
#endif
	_clear_dma_desc(lcdc_heo.dma_desc, &LCDC->LCDC_HEOHEAD);
	_clear_dma_desc(lcdc_heo.dma_u_desc, &LCDC->LCDC_HEOUHEAD);
	_clear_dma_desc(lcdc_heo.dma_v_desc, &LCDC->LCDC_HEOVHEAD);

	/* 3. Writing one to the CHDIS field of the CHXCHDR register will disable
	   the channel at the end of the frame. */

	/* Disable DMA channels */
	LCDC->LCDC_BASECHDR = LCDC_BASECHDR_CHDIS;
#ifdef CONFIG_HAVE_LCDC_OVR1
	LCDC->LCDC_OVR1CHDR = LCDC_OVR1CHDR_CHDIS;
#endif
#ifdef CONFIG_HAVE_LCDC_OVR2
	LCDC->LCDC_OVR2CHDR = LCDC_OVR2CHDR_CHDIS;
#endif
	LCDC->LCDC_HEOCHDR = LCDC_HEOCHDR_CHDIS;
	LCDC->LCDC_BASECFG4 = 0;

	/* 4. Writing one to the CHRST field of the CHXCHDR register will disable
	   the channel immediately. This may occur in the middle of the image. */

	/* 5. Poll CHSR field in the CHXCHSR register until the channel is
	   successfully disabled. */
	while (LCDC->LCDC_BASECHSR & LCDC_BASECHSR_CHSR);
#ifdef CONFIG_HAVE_LCDC_OVR1
	while (LCDC->LCDC_OVR1CHSR & LCDC_OVR1CHSR_CHSR);
#endif
#ifdef CONFIG_HAVE_LCDC_OVR2
	while (LCDC->LCDC_OVR2CHSR & LCDC_OVR1CHSR_CHSR);
#endif
	while (LCDC->LCDC_HEOCHSR & LCDC_HEOCHSR_CHSR);

	/* Timing Engine Power Down Software Operation */

	/* Disable backlight */
	LCDC->LCDC_LCDDIS = LCDC_LCDDIS_PWMDIS;
	while (LCDC->LCDC_LCDSR & LCDC_LCDSR_PWMSTS);

	/* 1. Disable the DISP signal writing DISPDIS field of the LCDC_LCDDIS
	   register. */
	LCDC->LCDC_LCDDIS = LCDC_LCDDIS_DISPDIS;

	/* 2. Poll DISPSTS field of the LCDC_LCDSR register to verify that the DISP
	   is no longer activated. */
	while (LCDC->LCDC_LCDSR & LCDC_LCDSR_DISPSTS);

	/* 3. Disable the hsync and vsync signals by writing one to SYNCDIS field of
	   the LCDC_LCDDIS register. */
	LCDC->LCDC_LCDDIS = LCDC_LCDDIS_SYNCDIS;

	/* 4. Poll LCDSTS field of the LCDC_LCDSR register to check that the
	   synchronization is off. */
	while (LCDC->LCDC_LCDSR & LCDC_LCDSR_LCDSTS);

	/* 5. Disable the Pixel clock by writing one in the CLKDIS field of the
	   LCDC_LCDDIS register. */
	LCDC->LCDC_LCDDIS = LCDC_LCDDIS_CLKDIS;

	/* 6. Poll CLKSTS field of the LCDC_LCDSR register to check that Pixel Clock
	   is disabled. */
	while (LCDC->LCDC_LCDSR & LCDC_LCDSR_CLKSTS);

	/* Disable peripheral clock and ISC system clock */
	pmc_disable_peripheral(ID_LCDC);
	if (pmc_has_system_clock(PMC_SYSTEM_CLOCK_LCD))
		pmc_disable_system_clock(PMC_SYSTEM_CLOCK_LCD);
}

/**
 * \brief Set the backlight of the LCD.
 *
 * \param level   Backlight brightness level [1..255],
 *                255 means maximum brightness.
 */
void lcdc_set_backlight(uint32_t level)
{
	uint32_t cfg = LCDC->LCDC_LCDCFG6 & ~LCDC_LCDCFG6_PWMCVAL_Msk;
	LCDC->LCDC_LCDCFG6 = cfg | LCDC_LCDCFG6_PWMCVAL(level);
}

/**
 * Get canvas layer for LCDC_Draw*
 * \return Layer information pointer.
 */
struct _lcdc_layer *lcdc_get_canvas(void)
{
	return &lcdc_canvas;
}

/**
 * Flush the current canvas layer*
 */
void lcdc_flush_canvas(void)
{
	struct _lcdc_layer *layer;

	layer = lcdc_get_canvas();
	cache_clean_region(layer->buffer, layer->height * layer->width * 4);
}

/**
 * Select an LCD layer as canvas layer.
 * Then all drawing operations will apply to current display buffer
 * of selected layer.
 * \note If there is no display buffer for the layer (not running)
 *       selection fails.
 * \param layer_id Layer ID.
 */
uint8_t lcdc_select_canvas(uint8_t layer_id)
{
	const struct _layer_info *layer = &lcdc_layers[layer_id];

	if (!layer->reg_cfg || !layer->data)
		return 0;

	lcdc_canvas.buffer = (void *)layer->data->buffer;
	if (layer->reg_win) {
		lcdc_canvas.width = (layer->reg_win[1] & LCDC_HEOCFG3_XSIZE_Msk) >> LCDC_HEOCFG3_XSIZE_Pos;
		lcdc_canvas.height = (layer->reg_win[1] & LCDC_HEOCFG3_YSIZE_Msk) >> LCDC_HEOCFG3_YSIZE_Pos;
	} else {
		lcdc_canvas.width = lcdc_config.width;
		lcdc_canvas.height = lcdc_config.height;
	}
	lcdc_canvas.bpp = _get_bits_per_pixel(layer->reg_cfg[1] & LCDC_HEOCFG1_RGBMODE_Msk);
	lcdc_canvas.layer_id = layer_id;

	return 1;
}

/**
 * Create a blank canvas on a display layer for further operations.
 * \param layer_id Layer ID.
 * \param buffer   Pointer to canvas display buffer.
 * \param bpp      Bits Per Pixel.
 * \param x        Canvas X coordinate on base.
 * \param y        Canvas Y coordinate on base.
 * \param w        Canvas width.
 * \param h        Canvas height.
 * \note The content in buffer is destroied.
 */
void * lcdc_create_canvas(uint8_t layer_id, void *buffer, uint8_t bpp,
			  uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	uint32_t max_w = lcdc_config.width;
	uint32_t max_h = lcdc_config.height;
	uint32_t bits_per_row, bytes_per_row;
	void *old_buffer;

	switch (layer_id) {
	case LCDC_BASE:
		x = 0;
		y = 0;
		break;
#ifdef CONFIG_HAVE_LCDC_OVR1
	case LCDC_OVR1:
#endif
#ifdef CONFIG_HAVE_LCDC_OVR2
	case LCDC_OVR2:
#endif
	case LCDC_HEO:
		/* Size check */
		if (x + w > lcdc_config.width || y + h > lcdc_config.height)
			return NULL;
		break;
	}
	if (w == 0)
		w = max_w - x;
	if (h == 0)
		h = max_h - y;

	/* Clear buffer */
	bits_per_row = w * bpp;
	bytes_per_row = (bits_per_row & 0x7) ? (bits_per_row / 8 + 1) : (bits_per_row / 8);
	memset(buffer, 0, bytes_per_row * h);

	old_buffer = lcdc_put_image_rotated(layer_id, buffer, bpp,
			x, y, w, h, w, h, 0);

	lcdc_canvas.layer_id = layer_id;
	lcdc_canvas.bpp = bpp;
	lcdc_canvas.buffer = buffer;
	lcdc_canvas.width = w;
	lcdc_canvas.height = h;

	return old_buffer;
}

/**
 * Create a blank canvas on a display layer for YUV422/420 planar.
 * \param layer_id Layer ID.
 * \param buffer   Pointer to buffer of Y.
 * \param buffer_u Pointer to buffer of U.
 * \param buffer_v Pointer to buffer of V.
 * \param bpp      Bits Per Pixel.
 * \param x        Canvas X coordinate on base.
 * \param y        Canvas Y coordinate on base.
 * \param w        Canvas width.
 * \param h        Canvas height.
 */
void *lcdc_create_canvas_yuv_planar(uint8_t layer_id,
		void *buffer_y, void *buffer_u, void *buffer_v, uint8_t bpp,
		uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	const struct _layer_info *layer = &lcdc_layers[layer_id];

	uint32_t max_w = lcdc_config.width;
	uint32_t max_h = lcdc_config.height;
	uint32_t bits_per_row, bytes_per_row;

	if (!layer->reg_dma_u_head || !layer->reg_dma_v_head)
		return NULL;

	/* Size check */
	if (x + w > lcdc_config.width || y + h > lcdc_config.height)
		return NULL;
	if (w == 0)
		w = max_w - x;
	if (h == 0)
		h = max_h - y;

	/* Clear buffer */
	bits_per_row = w * bpp;
	bytes_per_row = (bits_per_row & 0x7) ? (bits_per_row / 8 + 1) : (bits_per_row / 8);
	memset(buffer_y, 0xFF, bytes_per_row * h);

	/* Setup window */
	if (layer->reg_win) {
		layer->reg_win[0] = LCDC_HEOCFG2_XPOS(x) | LCDC_HEOCFG2_YPOS(y);
		layer->reg_win[1] = LCDC_HEOCFG3_XSIZE(w - 1) | LCDC_HEOCFG3_YSIZE(h - 1);
		layer->reg_win[2] = LCDC_HEOCFG4_XMEMSIZE(w - 1) | LCDC_HEOCFG4_YMEMSIZE(h - 1);
	}

	_set_dma_desc(buffer_y, layer->data->dma_desc, layer->reg_dma_head);
	_set_dma_desc(buffer_u, layer->data->dma_u_desc, layer->reg_dma_u_head);
	_set_dma_desc(buffer_v, layer->data->dma_v_desc, layer->reg_dma_v_head);

	return 0;
}

/**
 * Create a blank canvas on a display layer for YUV422/420 semiplanar.
 * \param layer_id  Layer ID.
 * \param buffer    Pointer to buffer of Y.
 * \param buffer_uv Pointer to buffer of UV.
 * \param bpp       Bits Per Pixel.
 * \param x         Canvas X coordinate on base.
 * \param y         Canvas Y coordinate on base.
 * \param w         Canvas width.
 * \param h         Canvas height.
 */
void *lcdc_create_canvas_yuv_semiplanar(uint8_t layer_id,
		void *buffer_y, void *buffer_uv, uint8_t bpp,
		uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	const struct _layer_info *layer = &lcdc_layers[layer_id];

	uint32_t max_w = lcdc_config.width;
	uint32_t max_h = lcdc_config.height;
	uint32_t bits_per_row, bytes_per_row;

	if (!layer->reg_dma_u_head || !layer->reg_dma_v_head)
		return NULL;

	/* Size check */
	if (x + w > lcdc_config.width || y + h > lcdc_config.height)
		return NULL;
	if (w == 0)
		w = max_w - x;
	if (h == 0)
		h = max_h - y;

	/* Clear buffer */
	bits_per_row = w * bpp;
	bytes_per_row = (bits_per_row & 0x7) ? (bits_per_row / 8 + 1) : (bits_per_row / 8);
	memset(buffer_y, 0xFF, bytes_per_row * h);

	if (layer->reg_win) {
		layer->reg_win[0] = LCDC_HEOCFG2_XPOS(x) | LCDC_HEOCFG2_YPOS(y);
		layer->reg_win[1] = LCDC_HEOCFG3_XSIZE(w - 1) | LCDC_HEOCFG3_YSIZE(h - 1);
		layer->reg_win[2] = LCDC_HEOCFG4_XMEMSIZE(w - 1) | LCDC_HEOCFG4_YMEMSIZE(h - 1);
	}

	_set_dma_desc(buffer_y, layer->data->dma_desc, layer->reg_dma_head);
	_set_dma_desc(buffer_uv, layer->data->dma_u_desc, layer->reg_dma_u_head);

	return 0;
}

#ifdef CONFIG_HAVE_LCDC_PP
/**
 * Connfigure PPC with DMA enabled.
 * \param buffer       Pointer to buffer.
 * \param output_mode  Post Processing output format selection.
 */
void lcdc_configure_pp(void *buffer, uint32_t output_mode)
{
	const struct _layer_info *layer = &lcdc_layers[LCDC_PP];

	_set_dma_desc(buffer, layer->data->dma_desc, layer->reg_dma_head);
	layer->reg_dma_head[0] = (uint32_t)layer->data->dma_desc;
	LCDC->LCDC_PPCFG1 = output_mode;
}
#endif

/**
 * \brief Change RGB Input Mode Selection for given layer.
 * \param layer_id   Layer ID.
 * \param input_mode RGB Input Mode Selection.
 */
void lcdc_configure_input_mode(uint8_t layer_id, uint32_t input_mode)
{
	const struct _layer_info *layer = &lcdc_layers[layer_id];
	layer->reg_cfg[1] = input_mode;
}

uint32_t lcdc_configure_get_mode(uint8_t layer_id)
{
	const struct _layer_info *layer = &lcdc_layers[layer_id];
	return layer->reg_cfg[1];
}

/**@}*/
