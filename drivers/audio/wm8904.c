/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
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
 *
 * Implementation of wm8904 driver.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "trace.h"
#include "audio/wm8904.h"
#include "i2c/twi-bus.h"
#include "i2c/twid.h"
#include "peripherals/pmc.h"

#include "timer.h"

#include <stdio.h>

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

/** Reset register */
#define WM8904_REG_RESET                           0x00

/** Bias control 0 register */
#define WM8904_REG_BIAS_CTRL0                      0x04

/** VMID control 0 register */
#define WM8904_REG_VMID_CTRL0                      0x05

/** MIC Bias control 0 register */
#define WM8904_REG_MICBIAS_CTRL0                   0x06

/** Bias control 1 register */
#define WM8904_REG_BIAS_CTRL1                      0x07

/** Power management control 0 register */
#define WM8904_REG_POWER_MANG0                     0x0c
/** Power management control 2 register */
#define WM8904_REG_POWER_MANG2                     0x0e
/** Power management control 3 register */
#define WM8904_REG_POWER_MANG3                     0x0f
/** Power management control 6 register */
#define WM8904_REG_POWER_MANG6                     0x12

/** Clock rate0 register */
#define WM8904_REG_CLOCK_RATE0                     0x14
/** Clock rate1 register */
#define WM8904_REG_CLOCK_RATE1                     0x15
/** Clock rate2 register */
#define WM8904_REG_CLOCK_RATE2                     0x16

/** Audio interface0 register */
#define WM8904_REG_AUD_INF0                        0x18

/** Audio interface1 register */
#define WM8904_REG_AUD_INF1                        0x19
/** Audio interface2 register */
#define WM8904_REG_AUD_INF2                        0x1a
/** Audio interface3 register */
#define WM8904_REG_AUD_INF3                        0x1b

/** ADC digital 0 register */
#define WM8904_REG_ADC_DIG0                        0x20
/** ADC digital 1 register */
#define WM8904_REG_ADC_DIG1                        0x21

/** Analogue left input 0 register */
#define WM8904_REG_ANALOGUE_LIN0                   0x2c
/** Analogue right input 0 register */
#define WM8904_REG_ANALOGUE_RIN0                   0x2d

/** Analogue left input 1 register */
#define WM8904_REG_ANALOGUE_LIN1                   0x2e
/** Analogue right input 1 register */
#define WM8904_REG_ANALOGUE_RIN1                   0x2f

/** Analogue left output 1 register */
#define WM8904_REG_ANALOGUE_LOUT1                  0x39
/** Analogue right output 1 register */
#define WM8904_REG_ANALOGUE_ROUT1                  0x3a

/** Analogue left output 2 register */
#define WM8904_REG_ANALOGUE_LOUT2                  0x3b
/** Analogue right output 2 register */
#define WM8904_REG_ANALOGUE_ROUT2                  0x3c

/** Analogue output 12 ZC register */
#define WM8904_REG_ANALOGUE_OUT12ZC                0x3d

/** DC servo 0 register */
#define WM8904_REG_DC_SERVO0                       0x43

/** Analogue HP 0 register */
#define WM8904_REG_ANALOGUE_HP0                    0x5a

/** Charge pump 0 register */
#define WM8904_REG_CHARGE_PUMP0                    0x62

/** Class W 0 register */
#define WM8904_REG_CLASS0                          0x68

/** FLL control 1 register */
#define WM8904_REG_FLL_CRTL1                       0x74
/** FLL control 2 register */
#define WM8904_REG_FLL_CRTL2                       0x75
/** FLL control 3 register */
#define WM8904_REG_FLL_CRTL3                       0x76
/** FLL control 4 register */
#define WM8904_REG_FLL_CRTL4                       0x77
/** FLL control 5 register */
#define WM8904_REG_FLL_CRTL5                       0x78

#define WM8904_HPOUT_MUTE            (1 << 8)  /* Bit 8:  Headphone output mute */
#define WM8904_HPOUT_VU              (1 << 7)  /* Bit 7:  Headphone output volume update */
#define WM8904_HPOUTZC               (1 << 6)  /* Bit 6:  Headphone output zero cross enable */
#define WM8904_HPOUT_MAX_VOLUME      (63)      /* Headphone output max volume */

/*----------------------------------------------------------------------------
 *        Type
 *----------------------------------------------------------------------------*/

struct _wm8904_para {
	uint8_t  address;
	uint16_t value;
	uint8_t  delay;
};

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

static const struct _wm8904_para wm8904_access_slow[] = {
	{ 0x00, 0x0000, 0 },   /** R0   - SW Reset and ID */
	{ 0x04, 0x001a, 0 },   /** R4   - Bias Control 0 */
	{ 0x05, 0x0047, 5 },   /** R5   - VMID Control 0 */
	{ 0x05, 0x0043, 0 },   /** R5   - VMID Control 0 */
	{ 0x04, 0x000b, 0 },   /** R4   - Bias Control 0 */
	{ 0x0c, 0x0003, 0 },   /** R12  - Power Management 0 CC */
	{ 0x0e, 0x0003, 0 },   /** R14  - Power Management 2 */
	{ 0x12, 0x000c, 0 },   /** R18  - Power Management 6 */
	{ 0x21, 0x0000, 0 },   /** R33  - DAC Digital 1 */
	{ 0x3d, 0x0000, 0 },   /** R61  - Analogue OUT12 ZC */
	{ 0x62, 0x0001, 0 },   /** R98  - Charge Pump 0 */
	{ 0x68, 0x0005, 0 },   /** R104 - Class W 0 */
	/* FLL setting,32.768KHZ MCLK input,12.288M output. */
	{ 0x74, 0x0000, 0 },   /** R116 - FLL Control 1 */
	{ 0x75, 0x0704, 0 },   /** R117 - FLL Control 2 */
	{ 0x76, 0x8000, 0 },   /** R118 - FLL Control 3 */
	{ 0x77, 0x1760, 0 },   /** R119 - FLL Control 4 */
	{ 0x74, 0x0005, 5 },   /** R116 - FLL Control 1 */
	{ 0x15, 0x0c05, 0 },   /** R21  - Clock Rates 1 */
	{ 0x14, 0x845e, 0 },   /** R20  - Clock Rates 0 */
	{ 0x16, 0x4006, 0 },   /** R22  - Clock Rates 2 */
	/* wm8904 IIS master BCLK=12.288MHz/8=1.536MHz LRCK=1.536MHz/32=48KHz */
	{ 0x19, 0x0042, 0 },   /** R25  - Audio Interface 1 */
	{ 0x1a, 0x00e8, 0 },   /** R26  - Audio Interface 2 */
	{ 0x1b, 0x0820, 0 },   /** R27  - Audio Interface 3 */
	{ 0x0c, 0x0003, 0 },   /** R12  - Power Management 0 */
	{ 0x12, 0x000f, 5 },   /** R18  - Power Management 6 */
	{ 0x2c, 0x0010, 0 },   /** R44  - Analogue Left Input 0 */
	{ 0x2d, 0x0010, 0 },   /** R45  - Analogue Right Input 0 */
	{ 0x2e, 0x0004, 0 },   /** R46  - Analogue Left Input 1 */
	{ 0x2f, 0x0004, 0 },   /** R47  - Analogue Right Input 1 */
	{ 0x5a, 0x0011, 0 },   /** R90  - Analogue HP 0 */
	{ 0x5a, 0x0033, 0 },   /** R90  - Analogue HP 0 */
	{ 0x43, 0x000f, 0 },   /** R67  - DC Servo 0 */
	{ 0x44, 0x00f0, 100 }, /** R68  - DC Servo 1 */
	{ 0x5a, 0x0077, 0 },   /** R90  - Analogue HP 0 */
	{ 0x5a, 0x00ff, 0 },   /** R90  - Analogue HP 0 */
	{ 0x39, 0x00b9, 0 },   /** R57  - Analogue OUT1 Left */
	{ 0x3a, 0x00b9, 100 }, /** R58  - Analogue OUT1 Right */
};

static const struct _wm8904_para wm8904_access_main[] = {
	{ 0x04, 0x0018, 0 }, /** R2   - Bias Control 0 */
	{ 0x05, 0x0043, 0 }, /** R5   - VMID Control 0 */
	{ 0x0c, 0x0003, 0 }, /** R12  - Power Management 0 */
	{ 0x0e, 0x0003, 0 }, /** R14  - Power Management 2 */
	{ 0x12, 0x000f, 0 }, /** R18  - Power Management 6 */
	{ 0x14, 0x845e, 0 }, /** R20  - Clock Rates 0 */
	{ 0x16, 0x0006, 0 }, /** R22  - Clock Rates 2 */
	{ 0x19, 0x404a, 0 }, /** R25  - Audio Interface 1 */
	{ 0x1b, 0x0840, 0 }, /** R27  - Audio Interface 3 */
	{ 0x21, 0x0000, 0 }, /** R33  - DAC Digital 1 */
	{ 0x2c, 0x0005, 0 }, /** R44  - Analogue Left Input 0 */
	{ 0x2d, 0x0005, 0 }, /** R45  - Analogue Right Input 0 */
	{ 0x2e, 0x0000, 0 }, /** R46  - Analogue Left Input 1 */
	{ 0x2f, 0x0000, 0 }, /** R47  - Analogue Right Input 1 */
	{ 0x3a, 0x00ad, 0 }, /** R58  - Analogue OUT1 Right */
	{ 0x43, 0x0003, 0 }, /** R67  - DC Servo 0 */
	{ 0x5a, 0x00ff, 0 }, /** R90  - Analogue HP 0 */
	{ 0x62, 0x0001, 0 }, /** R98  - Charge Pump 0 */
	{ 0x68, 0x0005, 0 }, /** R104 - Class W 0 */
	{ 0x74, 0x0004, 0 }, /** R116 - FLL Control 1 */
	{ 0x75, 0x0704, 0 }, /** R117 - FLL Control 2 */
	{ 0x76, 0x8000, 0 }, /** R118 - FLL Control 3 */
	{ 0x77, 0x1760, 0 }, /** R119 - FLL Control 4 */
};

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Read data from WM8904 Register.
 *
 * \param wm8904   Descriptor of WM8904
 * \param reg_addr Register address to read.
 * \return value in the given register.
 */
static uint16_t wm8904_read(struct _wm8904_desc *wm8904, uint8_t reg_addr)
{
	int status;
	uint8_t temp_data[2] = { 0, 0 };
	struct _buffer buf[2] = {
		{
			.data = &reg_addr,
			.size = 1,
			.attr = TWID_BUF_ATTR_START | TWID_BUF_ATTR_WRITE | TWID_BUF_ATTR_STOP,
		},
		{
			.data = temp_data,
			.size = 2,
			.attr = TWID_BUF_ATTR_START | TWID_BUF_ATTR_READ | TWID_BUF_ATTR_STOP,
		},
	};

	while (twi_bus_transaction_pending(wm8904->twi.bus));
	twi_bus_start_transaction(wm8904->twi.bus);

	status = twi_bus_transfer(wm8904->twi.bus, wm8904->twi.addr, buf, 2, NULL);
	if (status < 0) {
		twi_bus_stop_transaction(wm8904->twi.bus);
		return status;
	}

	twi_bus_wait_transfer(wm8904->twi.bus);
	twi_bus_stop_transaction(wm8904->twi.bus);

	return (temp_data[0] << 8) | temp_data[1];
}

/**
 * \brief  Write data to WM8904 Register.
 * \param wm8904   Descriptor of WM8904
 * \param reg_addr Register address to read.
 * \param data    Data to write
 */
static void wm8904_write(struct _wm8904_desc *wm8904, uint8_t reg_addr, uint16_t data)
{
	int status;
	uint8_t tmp_data[2] = { 0, 0 };
	struct _buffer buf[2] = {
		{
			.data = &reg_addr,
			.size = 1,
			.attr = TWID_BUF_ATTR_START | TWID_BUF_ATTR_WRITE,
		},
		{
			.data = tmp_data,
			.size = 2,
			.attr = TWID_BUF_ATTR_WRITE | TWID_BUF_ATTR_STOP,
		},
	};

	tmp_data[0] = (data & 0xff00) >> 8;
	tmp_data[1] = data & 0xff;

	while (twi_bus_transaction_pending(wm8904->twi.bus));
	twi_bus_start_transaction(wm8904->twi.bus);

	status = twi_bus_transfer(wm8904->twi.bus, wm8904->twi.addr, buf, 2, NULL);
	if (status < 0) {
		twi_bus_stop_transaction(wm8904->twi.bus);
		return;
	}

	twi_bus_wait_transfer(wm8904->twi.bus);
	twi_bus_stop_transaction(wm8904->twi.bus);
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void wm8904_configure(struct _wm8904_desc *wm8904)
{
	const struct _wm8904_para *params;
	uint8_t i, count;

	/* configure codec master clock */
	pmc_disable_pck(wm8904->mclk_pck);
	pmc_configure_pck(wm8904->mclk_pck, wm8904->mclk_pck_src, 0);
	pmc_enable_pck(wm8904->mclk_pck);
	pio_configure(&wm8904->mclk_pin, 1);

	/* check that WM8904 is present */
	if (!wm8904_detect(wm8904))
		trace_fatal("wm8904: device not detected!\r\n");

	wm8904_reset(wm8904);

	switch (wm8904->mclk_pck_src) {
	case PMC_PCK_CSS_SLOW_CLK:
		params = wm8904_access_slow;
		count = ARRAY_SIZE(wm8904_access_slow);
		break;

	case PMC_PCK_CSS_MAIN_CLK:
		params = wm8904_access_main;
		count = ARRAY_SIZE(wm8904_access_main);
		break;

	default:
		trace_fatal("wm8904: PCK not supported!\r\n");
	}

	for (i = 0; i < count; i++) {
		wm8904_write(wm8904, params[i].address, params[i].value);
		if (params[i].delay > 0)
			msleep(params[i].delay);
	}

	if ((wm8904->input_path & (WM8904_INPUT_PATH_IN1L | WM8904_INPUT_PATH_IN2L)) == (WM8904_INPUT_PATH_IN1L | WM8904_INPUT_PATH_IN2L))
		trace_fatal("wm8904: invalid left input path\r\n");

	if (wm8904->input_path & WM8904_INPUT_PATH_IN1L) {
		/* IN1L */
		wm8904_write(wm8904, WM8904_REG_ANALOGUE_LIN1, 0x0000);
	} else {
		/* IN2L */
		wm8904_write(wm8904, WM8904_REG_ANALOGUE_LIN1, 0x0010);
	}

	if ((wm8904->input_path & (WM8904_INPUT_PATH_IN1R | WM8904_INPUT_PATH_IN2R)) == (WM8904_INPUT_PATH_IN1R | WM8904_INPUT_PATH_IN2R))
		trace_fatal("wm8904: invalid right input path\r\n");

	if (wm8904->input_path & WM8904_INPUT_PATH_IN1R) {
		/* IN1R*/
		wm8904_write(wm8904, WM8904_REG_ANALOGUE_RIN1, 0x0000);
	} else {
		/* IN2R*/
		wm8904_write(wm8904, WM8904_REG_ANALOGUE_RIN1, 0x0010);
	}
}

void wm8904_in2r_in1l(struct _wm8904_desc *wm8904)
{
	/** R44  - Analogue Left Input 0 */
	wm8904_write(wm8904, 0x2C, 0x0008);

	/** R45  - Analogue Right Input 0 */
	wm8904_write(wm8904, 0x2D, 0x0005);

	/** R46  - Analogue Left Input 1 */
	wm8904_write(wm8904, 0x2E, 0x0000);

	/** R47  - Analogue Right Input 1 */
	wm8904_write(wm8904, 0x2F, 0x0010);
}

void wm8904_set_left_volume(struct _wm8904_desc *wm8904, uint8_t vol)
{
	if (vol > WM8904_HPOUT_MAX_VOLUME)
		return;
	/** R57 (0x39) - Analogue OUT1 Left */
	wm8904_write(wm8904, 0x39, WM8904_HPOUT_VU | WM8904_HPOUTZC | vol);
}

void wm8904_set_right_volume(struct _wm8904_desc *wm8904, uint8_t vol)
{
	if (vol > WM8904_HPOUT_MAX_VOLUME)
		return;
	/** R58 (0x3a) Analogue OUT1 Right */
	wm8904_write(wm8904, 0x3a, WM8904_HPOUT_VU | WM8904_HPOUTZC | vol);
}

void wm8904_volume_mute(struct _wm8904_desc *wm8904, bool left, bool right)
{
	uint16_t left_val = wm8904_read(wm8904, 0x39);
	uint16_t right_val = wm8904_read(wm8904, 0x3a);

	if (left) {
		/** R57 (0x39) - Analogue OUT1 Left Mute */
		wm8904_write(wm8904, 0x39, WM8904_HPOUT_MUTE | WM8904_HPOUT_VU | left_val);
	} else {
		left_val &= ~WM8904_HPOUT_MUTE;
		/** R57 (0x39) - Analogue OUT1 Left Unmute */
		wm8904_write(wm8904, 0x39, WM8904_HPOUT_VU | left_val);
	}

	if (right) {
		/** R58 (0x3a) Analogue OUT1 Right Mute */
		wm8904_write(wm8904, 0x3a, WM8904_HPOUT_MUTE | WM8904_HPOUT_VU | right_val);
	} else {
		right_val &= ~WM8904_HPOUT_MUTE;
		/** R58 (0x3a) Analogue OUT1 Right Unmute */
		wm8904_write(wm8904, 0x3a, WM8904_HPOUT_VU | right_val);
	}
}

bool wm8904_detect(struct _wm8904_desc *wm8904)
{
	/* Check that WM8904 is there */
	wm8904_write(wm8904, 22, 0);
	return (wm8904_read(wm8904, 0) == 0x8904);
}

void wm8904_reset(struct _wm8904_desc *wm8904)
{
	wm8904_write(wm8904, WM8904_REG_RESET, 0xFFFF);
	msleep(10);
	/* Wait until codec is ready */
	while (wm8904_read(wm8904, 0) != 0x8904);
}

void wm8904_sync(struct _wm8904_desc *wm8904, int32_t adjust)
{
	if (adjust > 0) {
		/* Fractional multiply for FLL_K, Fref = 0x8000 (1/2) */
		wm8904_write(wm8904, WM8904_REG_FLL_CRTL3, 0xFF00);
	} else if (adjust < 0) {
		/* Fractional multiply for FLL_K, Fref = 0x8000 (1/2) */
		wm8904_write(wm8904, WM8904_REG_FLL_CRTL3, 0x5000);
	} else {
		/* Default: 32K -> 48K*256, FLL: 32768*187.5/16/8 */
		/* FLL_FRATIO=4 (/16), FLL_OUTDIV= 7 (/8) */
		/* Fractional multiply for FLL_K, Fref = 0x8000 (1/2) */
		wm8904_write(wm8904, WM8904_REG_FLL_CRTL3, 0x8000 + 0x3000);
	}
}
