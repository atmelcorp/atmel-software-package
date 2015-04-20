/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation
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

/**
 * \file
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "aptina.h"

#define VAL_SET(x, mask, rshift, lshift)  \
        ((((x) >> rshift) & mask) << lshift)

/*
 * DSP registers
 * register offset for BANK_SEL == BANK_SEL_DSP
 */
#define   R_BYPASS    0x05 /* Bypass DSP */
#define   R_BYPASS_DSP_BYPAS    0x01 /* Bypass DSP, sensor out directly */
#define   R_BYPASS_USE_DSP      0x00 /* Use the internal DSP */
#define   QS          0x44 /* Quantization Scale Factor */
#define   CTRLI       0x50
#define   CTRLI_LP_DP           0x80
#define   CTRLI_ROUND           0x40
#define   CTRLI_V_DIV_SET(x)    VAL_SET(x, 0x3, 0, 3)
#define   CTRLI_H_DIV_SET(x)    VAL_SET(x, 0x3, 0, 0)
#define   HSIZE       0x51 /* H_SIZE[7:0] (real/4) */
#define   HSIZE_SET(x)          VAL_SET(x, 0xFF, 2, 0)
#define   VSIZE       0x52 /* V_SIZE[7:0] (real/4) */
#define   VSIZE_SET(x)          VAL_SET(x, 0xFF, 2, 0)
#define   XOFFL       0x53 /* OFFSET_X[7:0] */
#define   XOFFL_SET(x)          VAL_SET(x, 0xFF, 0, 0)
#define   YOFFL       0x54 /* OFFSET_Y[7:0] */
#define   YOFFL_SET(x)          VAL_SET(x, 0xFF, 0, 0)
#define   VHYX        0x55 /* Offset and size completion */
#define   VHYX_VSIZE_SET(x)     VAL_SET(x, 0x1, (8+2), 7)
#define   VHYX_HSIZE_SET(x)     VAL_SET(x, 0x1, (8+2), 3)
#define   VHYX_YOFF_SET(x)      VAL_SET(x, 0x3, 8, 4)
#define   VHYX_XOFF_SET(x)      VAL_SET(x, 0x3, 8, 0)
#define   DPRP        0x56
#define   TEST        0x57 /* Horizontal size completion */
#define   TEST_HSIZE_SET(x)     VAL_SET(x, 0x1, (9+2), 7)
#define   ZMOW        0x5A /* Zoom: Out Width  OUTW[7:0] (real/4) */
#define   ZMOW_OUTW_SET(x)      VAL_SET(x, 0xFF, 2, 0)
#define   ZMOH        0x5B /* Zoom: Out Height OUTH[7:0] (real/4) */
#define   ZMOH_OUTH_SET(x)      VAL_SET(x, 0xFF, 2, 0)
#define   ZMHH        0x5C /* Zoom: Speed and H&W completion */
#define   ZMHH_ZSPEED_SET(x)    VAL_SET(x, 0x0F, 0, 4)
#define   ZMHH_OUTH_SET(x)      VAL_SET(x, 0x1, (8+2), 2)
#define   ZMHH_OUTW_SET(x)      VAL_SET(x, 0x3, (8+2), 0)
#define   BPADDR      0x7C /* SDE Indirect Register Access: Address */
#define   BPDATA      0x7D /* SDE Indirect Register Access: Data */
#define   CTRL2       0x86 /* DSP Module enable 2 */
#define   CTRL2_DCW_EN          0x20
#define   CTRL2_SDE_EN          0x10
#define   CTRL2_UV_ADJ_EN       0x08
#define   CTRL2_UV_AVG_EN       0x04
#define   CTRL2_CMX_EN          0x01
#define   CTRL3       0x87 /* DSP Module enable 3 */
#define   CTRL3_BPC_EN          0x80
#define   CTRL3_WPC_EN          0x40
#define   SIZEL       0x8C /* Image Size Completion */
#define   SIZEL_HSIZE8_11_SET(x) VAL_SET(x, 0x1, 11, 6)
#define   SIZEL_HSIZE8_SET(x)    VAL_SET(x, 0x7, 0, 3)
#define   SIZEL_VSIZE8_SET(x)    VAL_SET(x, 0x7, 0, 0)
#define   HSIZE8      0xC0 /* Image Horizontal Size HSIZE[10:3] */
#define   HSIZE8_SET(x)         VAL_SET(x, 0xFF, 3, 0)
#define   VSIZE8      0xC1 /* Image Vertical Size VSIZE[10:3] */
#define   VSIZE8_SET(x)         VAL_SET(x, 0xFF, 3, 0)
#define   CTRL0       0xC2 /* DSP Module enable 0 */
#define   CTRL0_AEC_EN       0x80
#define   CTRL0_AEC_SEL      0x40
#define   CTRL0_STAT_SEL     0x20
#define   CTRL0_VFIRST       0x10
#define   CTRL0_YUV422       0x08
#define   CTRL0_YUV_EN       0x04
#define   CTRL0_RGB_EN       0x02
#define   CTRL0_RAW_EN       0x01
#define   CTRL1       0xC3 /* DSP Module enable 1 */
#define   CTRL1_CIP          0x80
#define   CTRL1_DMY          0x40
#define   CTRL1_RAW_GMA      0x20
#define   CTRL1_DG           0x10
#define   CTRL1_AWB          0x08
#define   CTRL1_AWB_GAIN     0x04
#define   CTRL1_LENC         0x02
#define   CTRL1_PRE          0x01
#define   R_DVP_SP    0xD3 /* DVP output speed control */
#define   R_DVP_SP_AUTO_MODE 0x80
#define   R_DVP_SP_DVP_MASK  0x3F /* DVP PCLK = sysclk (48)/[6:0] (YUV0);
                   *          = sysclk (48)/(2*[6:0]) (RAW);*/
#define   IMAGE_MODE  0xDA /* Image Output Format Select */
#define   IMAGE_MODE_Y8_DVP_EN   0x40
#define   IMAGE_MODE_JPEG_EN     0x10
#define   IMAGE_MODE_YUV422      0x00
#define   IMAGE_MODE_RAW10       0x04 /* (DVP) */
#define   IMAGE_MODE_RGB565      0x08
#define   IMAGE_MODE_HREF_VSYNC  0x02 /* HREF timing select in DVP JPEG output
                       * mode (0 for HREF is same as sensor) */
#define   IMAGE_MODE_LBYTE_FIRST 0x01 /* Byte swap enable for DVP
                       *    1: Low byte first UYVY (C2[4] =0)
                       *        VYUY (C2[4] =1)
                       *    0: High byte first YUYV (C2[4]=0)
                       *        YVYU (C2[4] = 1) */
#define   RESET       0xE0 /* Reset */
#define   RESET_MICROC       0x40
#define   RESET_SCCB         0x20
#define   RESET_JPEG         0x10
#define   RESET_DVP          0x04
#define   RESET_IPU          0x02
#define   RESET_CIF          0x01
#define   REGED       0xED /* Register ED */
#define   REGED_CLK_OUT_DIS  0x10
#define   MS_SP       0xF0 /* SCCB Master Speed */
#define   SS_ID       0xF7 /* SCCB Slave ID */
#define   SS_CTRL     0xF8 /* SCCB Slave Control */
#define   SS_CTRL_ADD_AUTO_INC  0x20
#define   SS_CTRL_EN            0x08
#define   SS_CTRL_DELAY_CLK     0x04
#define   SS_CTRL_ACC_EN        0x02
#define   SS_CTRL_SEN_PASS_THR  0x01
#define   MC_BIST     0xF9 /* Microcontroller misc register */
#define   MC_BIST_RESET           0x80 /* Microcontroller Reset */
#define   MC_BIST_BOOT_ROM_SEL    0x40
#define   MC_BIST_12KB_SEL        0x20
#define   MC_BIST_12KB_MASK       0x30
#define   MC_BIST_512KB_SEL       0x08
#define   MC_BIST_512KB_MASK      0x0C
#define   MC_BIST_BUSY_BIT_R      0x02
#define   MC_BIST_MC_RES_ONE_SH_W 0x02
#define   MC_BIST_LAUNCH          0x01
#define   BANK_SEL    0xFF /* Register Bank Select */
#define   BANK_SEL_DSP     0x00
#define   BANK_SEL_SENS    0x01

/*
 * Sensor registers
 * register offset for BANK_SEL == BANK_SEL_SENS
 */
#define   GAIN        0x00 /* AGC - Gain control gain setting */
#define   COM1        0x03 /* Common control 1 */
#define   COM1_1_DUMMY_FR          0x40
#define   COM1_3_DUMMY_FR          0x80
#define   COM1_7_DUMMY_FR          0xC0
#define   COM1_VWIN_LSB_UXGA       0x0F
#define   COM1_VWIN_LSB_SVGA       0x0A
#define   COM1_VWIN_LSB_CIF        0x06
#define   REG04       0x04 /* Register 04 */
#define   REG04_DEF             0x20 /* Always set */
#define   REG04_HFLIP_IMG       0x80 /* Horizontal mirror image ON/OFF */
#define   REG04_VFLIP_IMG       0x40 /* Vertical flip image ON/OFF */
#define   REG04_VREF_EN         0x10
#define   REG04_HREF_EN         0x08
#define   REG04_AEC_SET(x)      VAL_SET(x, 0x3, 0, 0)
#define   REG08       0x08 /* Frame Exposure One-pin Control Pre-charge Row Num */
#define   COM2        0x09 /* Common control 2 */
#define   COM2_SOFT_SLEEP_MODE  0x10 /* Soft sleep mode */
/* Output drive capability */
#define   COM2_OCAP_Nx_SET(N)   (((N) - 1) & 0x03) /* N = [1x .. 4x] */
#define   PID         0x0A /* Product ID Number MSB */
#define   VER         0x0B /* Product ID Number LSB */
#define   COM3        0x0C /* Common control 3 */
#define   COM3_BAND_50H        0x04 /* 0 For Banding at 60H */
#define   COM3_BAND_AUTO       0x02 /* Auto Banding */
#define   COM3_SING_FR_SNAPSH  0x01 /* 0 For enable live video output after the
                     * snapshot sequence*/
#define   AEC         0x10 /* AEC[9:2] Exposure Value */
#define   CLKRC       0x11 /* Internal clock */
#define   CLKRC_EN             0x80
#define   CLKRC_DIV_SET(x)     (((x) - 1) & 0x1F) /* CLK = XVCLK/(x) */
#define   COM7        0x12 /* Common control 7 */
#define   COM7_SRST            0x80 /* Initiates system reset. All registers are
                     * set to factory default values after which
                     * the chip resumes normal operation */
#define   COM7_RES_UXGA        0x00 /* Resolution selectors for UXGA */
#define   COM7_RES_SVGA        0x40 /* SVGA */
#define   COM7_RES_CIF         0x20 /* CIF */
#define   COM7_ZOOM_EN         0x04 /* Enable Zoom mode */
#define   COM7_COLOR_BAR_TEST  0x02 /* Enable Color Bar Test Pattern */
#define   COM8        0x13 /* Common control 8 */
#define   COM8_DEF             0xC0 /* Banding filter ON/OFF */
#define   COM8_BNDF_EN         0x20 /* Banding filter ON/OFF */
#define   COM8_AGC_EN          0x04 /* AGC Auto/Manual control selection */
#define   COM8_AEC_EN          0x01 /* Auto/Manual Exposure control */
#define   COM9        0x14 /* Common control 9
              * Automatic gain ceiling - maximum AGC value [7:5]*/
#define   COM9_AGC_GAIN_2x     0x00 /* 000 :   2x */
#define   COM9_AGC_GAIN_4x     0x20 /* 001 :   4x */
#define   COM9_AGC_GAIN_8x     0x40 /* 010 :   8x */
#define   COM9_AGC_GAIN_16x    0x60 /* 011 :  16x */
#define   COM9_AGC_GAIN_32x    0x80 /* 100 :  32x */
#define   COM9_AGC_GAIN_64x    0xA0 /* 101 :  64x */
#define   COM9_AGC_GAIN_128x   0xC0 /* 110 : 128x */
#define   COM10       0x15 /* Common control 10 */
#define   COM10_PCLK_HREF      0x20 /* PCLK output qualified by HREF */
#define   COM10_PCLK_RISE      0x10 /* Data is updated at the rising edge of
                     * PCLK (user can latch data at the next
                     * falling edge of PCLK).
                     * 0 otherwise. */
#define   COM10_HREF_INV       0x08 /* Invert HREF polarity:
                     * HREF negative for valid data*/
#define   COM10_VSINC_INV      0x02 /* Invert VSYNC polarity */
#define   HSTART      0x17 /* Horizontal Window start MSB 8 bit */
#define   HEND        0x18 /* Horizontal Window end MSB 8 bit */
#define   VSTART      0x19 /* Vertical Window start MSB 8 bit */
#define   VEND        0x1A /* Vertical Window end MSB 8 bit */
#define   MIDH        0x1C /* Manufacturer ID byte - high */
#define   MIDL        0x1D /* Manufacturer ID byte - low  */
#define   AEW         0x24 /* AGC/AEC - Stable operating region (upper limit) */
#define   AEB         0x25 /* AGC/AEC - Stable operating region (lower limit) */
#define   VV          0x26 /* AGC/AEC Fast mode operating region */
#define   VV_HIGH_TH_SET(x)      VAL_SET(x, 0xF, 0, 4)
#define   VV_LOW_TH_SET(x)       VAL_SET(x, 0xF, 0, 0)
#define   REG2A       0x2A /* Dummy pixel insert MSB */
#define   FRARL       0x2B /* Dummy pixel insert LSB */
#define   ADDVFL      0x2D /* LSB of insert dummy lines in Vertical direction */
#define   ADDVFH      0x2E /* MSB of insert dummy lines in Vertical direction */
#define   YAVG        0x2F /* Y/G Channel Average value */
#define   REG32       0x32 /* Common Control 32 */
#define   REG32_PCLK_DIV_2    0x80 /* PCLK freq divided by 2 */
#define   REG32_PCLK_DIV_4    0xC0 /* PCLK freq divided by 4 */
#define   ARCOM2      0x34 /* Zoom: Horizontal start point */
#define   REG45       0x45 /* Register 45 */
#define   FLL         0x46 /* Frame Length Adjustment LSBs */
#define   FLH         0x47 /* Frame Length Adjustment MSBs */
#define   COM19       0x48 /* Zoom: Vertical start point */
#define   ZOOMS       0x49 /* Zoom: Vertical start point */
#define   COM22       0x4B /* Flash light control */
#define   COM25       0x4E /* For Banding operations */
#define   BD50        0x4F /* 50Hz Banding AEC 8 LSBs */
#define   BD60        0x50 /* 60Hz Banding AEC 8 LSBs */
#define   REG5D       0x5D /* AVGsel[7:0],   16-zone average weight option */
#define   REG5E       0x5E /* AVGsel[15:8],  16-zone average weight option */
#define   REG5F       0x5F /* AVGsel[23:16], 16-zone average weight option */
#define   REG60       0x60 /* AVGsel[31:24], 16-zone average weight option */
#define   HISTO_LOW   0x61 /* Histogram Algorithm Low Level */
#define   HISTO_HIGH  0x62 /* Histogram Algorithm High Level */

/*
 * ID
 */
#define   MANUFACTURER_ID    0x7FA2
#define   PID_OV2640    0x2642
#define   VERSION(pid, ver) ((pid << 8) | (ver & 0xFF))

#define   ENDMARKER { 0xff, 0xff }


#define   PER_SIZE_REG_SEQ(x, y, v_div, h_div, pclk_div)    \
           {CTRLI, CTRLI_LP_DP | CTRLI_V_DIV_SET(0) |    \
            CTRLI_H_DIV_SET(2)},        \
           {ZMOW, ZMOW_OUTW_SET(640) },            \
           {ZMOH, ZMOH_OUTH_SET(480) },            \
           {ZMHH, ZMHH_OUTW_SET(640) | ZMHH_OUTH_SET(480) },    \
           {R_DVP_SP, 2 },                \
           {RESET, 0x00}


/* Supported resolutions */
enum ov2640_width {
	W_QCIF    = 176,
	W_QVGA    = 320,
	W_CIF     = 352,
	W_VGA     = 640,
	W_SVGA    = 800,
	W_XGA     = 1024,
	W_SXGA    = 1280,
	W_UXGA    = 1600,
};

enum ov2640_height {
	H_QCIF    = 144,
	H_QVGA    = 240,
	H_CIF    = 288,
	H_VGA    = 480,
	H_SVGA    = 600,
	H_XGA    = 768,
	H_SXGA    = 1024,
	H_UXGA    = 1200,
};

/*------------------------------------------------------------------------------
 *         Local Variables
 *------------------------------------------------------------------------------*/

const struct mt_reg mt9v022_yuv_vga[]= {
	{0x01, 0x00, 0x01},    // COL_WINDOW_START_CONTEXTA_REG
	{0x02, 0x00, 0x04},    // ROW_WINDOW_START_CONTEXTA_REG
	{0x03, 0x01, 0xE0},    // ROW_WINDOW_SIZE_CONTEXTA_REG
	{0x04, 0x02, 0xF0},    // COL_WINDOW_SIZE_CONTEXTA_REG
	{0x05, 0x00, 0x5E},    // HORZ_BLANK_CONTEXTA_REG
	{0x06, 0x00, 0x2D},    // VERT_BLANK_CONTEXTA_REG
	{0x07, 0x01, 0x88},    // CONTROL_MODE_REG
	{0x08, 0x01, 0x90},    // COARSE_SHUTTER_WIDTH_1_CONTEXTA
	{0x09, 0x01, 0xBD},    // COARSE_SHUTTER_WIDTH_2_CONTEXTA
	{0x0A, 0x01, 0x64},    // SHUTTER_WIDTH_CONTROL_CONTEXTA
	{0x0B, 0x01, 0xC2},    // COARSE_SHUTTER_WIDTH_TOTAL_CONTEXTA
	{0x0C, 0x00, 0x00},    // RESET_REG
	{0x0D, 0x03, 0x00},    // READ_MODE_REG
	{0x0E, 0x00, 0x00},    // READ_MODE2_REG
	{0x0F, 0x00, 0x11},    // PIXEL_OPERATION_MODE 0x0100
	{0x10, 0x00, 0x40},    // RESERVED_CORE_10
	{0x11, 0x80, 0x42},    // RESERVED_CORE_11
	{0x12, 0x00, 0x22},    // RESERVED_CORE_12
	{0x13, 0x2D, 0x32},    // RESERVED_CORE_13
	{0x14, 0x0E, 0x02},    // RESERVED_CORE_14
	{0x15, 0x7F, 0x32},    // RESERVED_CORE_15
	{0x16, 0x28, 0x02},    // RESERVED_CORE_16
	{0x17, 0x3E, 0x38},    // RESERVED_CORE_17
	{0x18, 0x3E, 0x38},    // RESERVED_CORE_18
	{0x19, 0x28, 0x02},    // RESERVED_CORE_19
	{0x1A, 0x04, 0x28},    // RESERVED_CORE_1A
	{0x1B, 0x00, 0x00},    // LED_OUT_CONTROL
	{0x1C, 0x03, 0x02},    // DATA_COMPRESSION
	{0x1D, 0x00, 0x00},    // RESERVED_CORE_1D
	{0x1E, 0x00, 0x00},    // RESERVED_CORE_1E
	{0x1F, 0x00, 0x00},    // RESERVED_CORE_1F
	{0x20, 0x01, 0xD1},    // RESERVED_CORE_20
	{0x21, 0x00, 0x20},    // RESERVED_CORE_21
	{0x22, 0x00, 0x20},    // RESERVED_CORE_22
	{0x23, 0x00, 0x10},    // RESERVED_CORE_23
	{0x24, 0x00, 0x10},    // RESERVED_CORE_24
	{0x25, 0x00, 0x20},    // RESERVED_CORE_25
	{0x26, 0x00, 0x10},    // RESERVED_CORE_26
	{0x27, 0x00, 0x10},    // RESERVED_CORE_27
	{0x28, 0x00, 0x10},    // RESERVED_CORE_28
	{0x29, 0x00, 0x10},    // RESERVED_CORE_29
	{0x2A, 0x00, 0x20},    // RESERVED_CORE_2A
	{0x2B, 0x00, 0x03},    // RESERVED_CORE_2B
	{0x2C, 0x00, 0x04},    // VREF_ADC_CONTROL  //0~7
	{0x2D, 0x00, 0x04},    // RESERVED_CORE_2D
	{0x2E, 0x00, 0x07},    // RESERVED_CORE_2E
	{0x2F, 0x00, 0x04},    // RESERVED_CORE_2F
	{0x30, 0x00, 0x03},    // RESERVED_CORE_30
	{0x31, 0x00, 0x1F},    // V1_CONTROL_CONTEXTA
	{0x32, 0x00, 0x1A},    // V2_CONTROL_CONTEXTA
	{0x33, 0x00, 0x12},    // V3_CONTROL_CONTEXTA
	{0x34, 0x00, 0x03},    // V4_CONTROL_CONTEXTA
	{0x35, 0x00, 0x20},    // GLOBAL_GAIN_CONTEXTA_REG
	{0x36, 0x00, 0x10},    // GLOBAL_GAIN_CONTEXTB_REG
	{0x37, 0x00, 0x00},    // RESERVED_CORE_37
	{0x38, 0x00, 0x00},    // RESERVED_CORE_38
	{0x39, 0x00, 0x25},    // V1_CONTROL_CONTEXTB//none
	{0x3A, 0x00, 0x20},    // V2_CONTROL_CONTEXTB//none
	{0x3B, 0x00, 0x03},    // V3_CONTROL_CONTEXTB//none
	{0x3C, 0x00, 0x03},    // V4_CONTROL_CONTEXTB//none
	{0x46, 0x23, 0x1D},    // DARK_AVG_THRESHOLDS
	{0x47, 0x80, 0x80},    // CALIB_CONTROL_REG
	{0x4C, 0x00, 0x02},    // STEP_SIZE_AVG_MODE
	{0x39, 0x00, 0x25},    // V1_CONTROL_CONTEXTB//none
	{0x3A, 0x00, 0x20},    // V2_CONTROL_CONTEXTB//none
	{0x3B, 0x00, 0x03},    // V3_CONTROL_CONTEXTB//none
	{0x3C, 0x00, 0x03},    // V4_CONTROL_CONTEXTB//none
	{0x46, 0x23, 0x1D},    // DARK_AVG_THRESHOLDS
	{0x47, 0x80, 0x80},    // CALIB_CONTROL_REG
	{0x4C, 0x00, 0x02},    // STEP_SIZE_AVG_MODE
	{0x39, 0x00, 0x25},    // V1_CONTROL_CONTEXTB//none
	{0x3A, 0x00, 0x20},    // V2_CONTROL_CONTEXTB//none
	{0x3B, 0x00, 0x03},    // V3_CONTROL_CONTEXTB//none
	{0x3C, 0x00, 0x03},    // V4_CONTROL_CONTEXTB//none
	{0x46, 0x23, 0x1D},    // DARK_AVG_THRESHOLDS
	{0x47, 0x80, 0x80},    // CALIB_CONTROL_REG
	{0x4C, 0x00, 0x02},    // STEP_SIZE_AVG_MODE
	{0x60, 0x00, 0x00},    // RESERVED_CORE_60
	{0x61, 0x00, 0x00},    // RESERVED_CORE_61
	{0x62, 0x00, 0x00},    // RESERVED_CORE_62
	{0x63, 0x00, 0x00},    // RESERVED_CORE_63
	{0x64, 0x00, 0x00},    // RESERVED_CORE_64
	{0x65, 0x00, 0x00},    // RESERVED_CORE_65
	{0x66, 0x00, 0x00},    // RESERVED_CORE_66
	{0x67, 0x00, 0x00},    // RESERVED_CORE_67
	{0x6C, 0x00, 0x00},    // RESERVED_CORE_6C
	{0x70, 0x00, 0x04},    // ROW_NOISE_CONTROL
	{0x71, 0x00, 0x00},    // NOISE_CONSTANT
	{0x72, 0x00, 0x2A},    // PIXCLK_CONTROL
	{0x73, 0x02, 0xF7},    //
	{0x74, 0x00, 0x00},    //
	{0x7F, 0x00, 0x00},    // TEST_DATA
	{0x80, 0x00, 0xF4},    // TILE_X0_Y0
	{0x81, 0x00, 0xF4},    // TILE_X1_Y0
	{0x82, 0x00, 0xF4},    // TILE_X2_Y0
	{0x83, 0x00, 0xF4},    // TILE_X3_Y0
	{0x84, 0x00, 0xF4},    // TILE_X4_Y0
	{0x85, 0x00, 0xF4},    // TILE_X0_Y1
	{0x86, 0x00, 0xF4},    // TILE_X1_Y1
	{0x87, 0x00, 0xF4},    // TILE_X2_Y1
	{0x88, 0x00, 0xF4},    // TILE_X3_Y1
	{0x89, 0x00, 0xF4},    // TILE_X4_Y1
	{0x8A, 0x00, 0xF4},    // TILE_X0_Y2
	{0x8B, 0x00, 0xF4},    // TILE_X1_Y2
	{0x8C, 0x00, 0xF4},    // TILE_X2_Y2
	{0x8D, 0x00, 0xF4},    // TILE_X3_Y2
	{0x8E, 0x00, 0xF4},    // TILE_X4_Y2
	{0x8F, 0x00, 0xF4},    // TILE_X0_Y3
	{0x90, 0x00, 0xF4},    // TILE_X1_Y3
	{0x91, 0x00, 0xF4},    // TILE_X2_Y3
	{0x92, 0x00, 0xF4},    // TILE_X3_Y3
	{0x93, 0x00, 0xF4},    // TILE_X4_Y3
	{0x94, 0x00, 0xF4},    // TILE_X0_Y4
	{0x95, 0x00, 0xF4},    // TILE_X1_Y4
	{0x96, 0x00, 0xF4},    // TILE_X2_Y4
	{0x97, 0x00, 0xF4},    // TILE_X3_Y4
	{0x98, 0x00, 0xF4},    // TILE_X4_Y4
	{0x99, 0x00, 0x00},    // X0_SLASH5
	{0x9A, 0x00, 0x96},    // X1_SLASH5
	{0x9B, 0x01, 0x2C},    // X2_SLASH5
	{0x9C, 0x01, 0xC2},    // X3_SLASH5
	{0x9D, 0x02, 0x58},    // X4_SLASH5
	{0x9E, 0x02, 0xF0},    // X5_SLASH5
	{0x9F, 0x00, 0x00},    // Y0_SLASH5
	{0xA0, 0x00, 0x60},    // Y1_SLASH5
	{0xA1, 0x00, 0xC0},    // Y2_SLASH5
	{0xA2, 0x01, 0x20},    // Y3_SLASH5
	{0xA3, 0x01, 0x80},    // Y4_SLASH5
	{0xA4, 0x01, 0xE0},    // Y5_SLASH5
	{0xA5, 0x00, 0x3A},    // DESIRED_BIN
	{0xA6, 0x00, 0x02},    // EXP_SKIP_FRM_H
	{0xA8, 0x00, 0x00},    // EXP_LPF
	{0xA9, 0x00, 0x02},    // GAIN_SKIP_FRM
	{0xAA, 0x00, 0x00},    // GAIN_LPF_H
	{0xAB, 0x00, 0x40},    // MAX_GAIN
	{0xAC, 0x00, 0x01},    // MIN_COARSE_EXPOSURE
	{0xAD, 0x01, 0xE0},    // MAX_COARSE_EXPOSURE
	{0xAE, 0x00, 0x14},    // BIN_DIFF_THRESHOLD
	{0xAF, 0x00, 0x03},    // AUTO_BLOCK_CONTROL
	{0xB0, 0xAB, 0xE0},    // PIXEL_COUNT
	{0xB1, 0x00, 0x02},    // LVDS_MASTER_CONTROL
	{0xB2, 0x00, 0x10},    // LVDS_SHFT_CLK_CONTROL
	{0xB3, 0x00, 0x10},    // LVDS_DATA_CONTROL
	{0xB4, 0x00, 0x00},    // LVDS_DATA_STREAM_LATENCY
	{0xB5, 0x00, 0x00},    // LVDS_INTERNAL_SYNC
	{0xB6, 0x00, 0x00},    // LVDS_USE_10BIT_PIXELS
	{0xB7, 0x00, 0x00},    // STEREO_ERROR_CONTROL
	{0xBD, 0x01, 0xE0},    // Max Shutter 控制(自動AEC時使用) 1~0x7FF
	{0xBF, 0x00, 0x16},    // INTERLACE_FIELD_VBLANK
	{0xC0, 0x00, 0x0A},    // IMAGE_CAPTURE_NUM
	{0xC2, 0x08, 0x40},    // ANALOG_CONTROLS
	{0xC3, 0x00, 0x00},    // RESERVED_CORE_C3  0x007F
	{0xC4, 0x44, 0x16},    // RESERVED_CORE_C4
	{0xC5, 0x44, 0x21},    // RESERVED_CORE_C5
	{0xF1, 0x00, 0x00},    // RESERVED_CORE_ F1
	{0xFE, 0xBE, 0xEF},    // RESERVED_CORE_FE
	{0xFF, 0xFF, 0xFF},    //END use
};

