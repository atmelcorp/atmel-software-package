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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "audio/wm8904.h"
#include "audio/wm8904_regs.h"
#include "i2c/twid.h"
#include "peripherals/bus.h"
#include "peripherals/pmc.h"
#include "timer.h"
#include "trace.h"

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
	{ WM8904_REG_RESET, 0x0000, 0 },   /** R0   - SW Reset and ID */
	{ WM8904_REG_BIAS_CTRL0, 0x001a, 0 },   /** R4   - Bias Control 0 */
	{ WM8904_REG_VMID_CTRL0, 0x0047, 5 },   /** R5   - VMID Control 0 */
	{ WM8904_REG_VMID_CTRL0, 0x0043, 0 },   /** R5   - VMID Control 0 */
	{ WM8904_REG_BIAS_CTRL0, 0x000b, 0 },   /** R4   - Bias Control 0 */
	{ WM8904_REG_POWER_MANG0, 0x0003, 0 },   /** R12  - Power Management 0 CC */
	{ WM8904_REG_POWER_MANG2, 0x0003, 0 },   /** R14  - Power Management 2 */
	{ WM8904_REG_POWER_MANG6, 0x000c, 0 },   /** R18  - Power Management 6 */
	{ WM8904_REG_ADC_DIG1, 0x0000, 0 },   /** R33  - DAC Digital 1 */
	{ WM8904_REG_ANALOGUE_OUT12ZC, 0x0000, 0 },   /** R61  - Analogue OUT12 ZC */
	{ WM8904_REG_CHARGE_PUMP0, 0x0001, 0 },   /** R98  - Charge Pump 0 */
	{ WM8904_REG_CLASS0, 0x0005, 0 },   /** R104 - Class W 0 */
	/* FLL setting,32.768KHZ MCLK input,12.288M output. */
	{ WM8904_REG_FLL_CRTL1, 0x0000, 0 },   /** R116 - FLL Control 1 */
	{ WM8904_REG_FLL_CRTL2, 0x0704, 0 },   /** R117 - FLL Control 2 */
	{ WM8904_REG_FLL_CRTL3, 0x8000, 0 },   /** R118 - FLL Control 3 */
	{ WM8904_REG_FLL_CRTL4, 0x1760, 0 },   /** R119 - FLL Control 4 */
	{ WM8904_REG_FLL_CRTL1, 0x0005, 5 },   /** R116 - FLL Control 1 */
	{ WM8904_REG_CLOCK_RATE1, 0x0c05, 0 },   /** R21  - Clock Rates 1 */
	{ WM8904_REG_CLOCK_RATE0, 0x845e, 0 },   /** R20  - Clock Rates 0 */
	{ WM8904_REG_CLOCK_RATE2, 0x4006, 0 },   /** R22  - Clock Rates 2 */
	/* wm8904 IIS master BCLK=12.288MHz/8=1.536MHz LRCK=1.536MHz/32=48KHz */
	{ WM8904_REG_AUD_INF1, 0x0042, 0 },   /** R25  - Audio Interface 1 */
	{ WM8904_REG_AUD_INF2, 0x00e8, 0 },   /** R26  - Audio Interface 2 */
	{ WM8904_REG_AUD_INF3, 0x0820, 0 },   /** R27  - Audio Interface 3 */
	{ WM8904_REG_POWER_MANG0, 0x0003, 0 },   /** R12  - Power Management 0 */
	{ WM8904_REG_POWER_MANG6, 0x000f, 5 },   /** R18  - Power Management 6 */
	{ WM8904_REG_ANALOGUE_LIN0, 0x0010, 0 },   /** R44  - Analogue Left Input 0 */
	{ WM8904_REG_ANALOGUE_RIN0, 0x0010, 0 },   /** R45  - Analogue Right Input 0 */
	{ WM8904_REG_ANALOGUE_LIN1, 0x0004, 0 },   /** R46  - Analogue Left Input 1 */
	{ WM8904_REG_ANALOGUE_RIN1, 0x0004, 0 },   /** R47  - Analogue Right Input 1 */
	{ WM8904_REG_ANALOGUE_HP0, 0x0011, 0 },   /** R90  - Analogue HP 0 */
	{ WM8904_REG_ANALOGUE_HP0, 0x0033, 0 },   /** R90  - Analogue HP 0 */
	{ WM8904_REG_DC_SERVO0, 0x000f, 0 },   /** R67  - DC Servo 0 */
	{ WM8904_REG_DC_SERVO1, 0x00f0, 100 }, /** R68  - DC Servo 1 */
	{ WM8904_REG_ANALOGUE_HP0, 0x0077, 0 },   /** R90  - Analogue HP 0 */
	{ WM8904_REG_ANALOGUE_HP0, 0x00ff, 0 },   /** R90  - Analogue HP 0 */
	{ WM8904_REG_ANALOGUE_LOUT1, 0x00b9, 0 },   /** R57  - Analogue OUT1 Left */
	{ WM8904_REG_ANALOGUE_ROUT1, 0x00b9, 100 }, /** R58  - Analogue OUT1 Right */
};

static const struct _wm8904_para wm8904_access_main[] = {
	{ WM8904_REG_BIAS_CTRL0, 0x0018, 0 }, /** R2   - Bias Control 0 */
	{ WM8904_REG_VMID_CTRL0, 0x0043, 0 }, /** R5   - VMID Control 0 */
	{ WM8904_REG_POWER_MANG0, 0x0003, 0 }, /** R12  - Power Management 0 */
	{ WM8904_REG_POWER_MANG2, 0x0003, 0 }, /** R14  - Power Management 2 */
	{ WM8904_REG_POWER_MANG6, 0x000f, 0 }, /** R18  - Power Management 6 */
	{ WM8904_REG_CLOCK_RATE0, 0x845e, 0 }, /** R20  - Clock Rates 0 */
	{ WM8904_REG_CLOCK_RATE2, 0x0006, 0 }, /** R22  - Clock Rates 2 */
	{ WM8904_REG_AUD_INF1, 0x404a, 0 }, /** R25  - Audio Interface 1 */
	{ WM8904_REG_AUD_INF3, 0x0840, 0 }, /** R27  - Audio Interface 3 */
	{ WM8904_REG_ADC_DIG1, 0x0000, 0 }, /** R33  - DAC Digital 1 */
	{ WM8904_REG_ANALOGUE_LIN0, 0x0005, 0 }, /** R44  - Analogue Left Input 0 */
	{ WM8904_REG_ANALOGUE_RIN0, 0x0005, 0 }, /** R45  - Analogue Right Input 0 */
	{ WM8904_REG_ANALOGUE_LIN1, 0x0000, 0 }, /** R46  - Analogue Left Input 1 */
	{ WM8904_REG_ANALOGUE_RIN1, 0x0000, 0 }, /** R47  - Analogue Right Input 1 */
	{ WM8904_REG_ANALOGUE_ROUT1, 0x00ad, 0 }, /** R58  - Analogue OUT1 Right */
	{ WM8904_REG_DC_SERVO0, 0x0003, 0 }, /** R67  - DC Servo 0 */
	{ WM8904_REG_ANALOGUE_HP0, 0x00ff, 0 }, /** R90  - Analogue HP 0 */
	{ WM8904_REG_CHARGE_PUMP0, 0x0001, 0 }, /** R98  - Charge Pump 0 */
	{ WM8904_REG_CLASS0, 0x0005, 0 }, /** R104 - Class W 0 */
	{ WM8904_REG_FLL_CRTL1, 0x0004, 0 }, /** R116 - FLL Control 1 */
	{ WM8904_REG_FLL_CRTL2, 0x0704, 0 }, /** R117 - FLL Control 2 */
	{ WM8904_REG_FLL_CRTL3, 0x8000, 0 }, /** R118 - FLL Control 3 */
	{ WM8904_REG_FLL_CRTL4, 0x1760, 0 }, /** R119 - FLL Control 4 */
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
static int wm8904_read(struct _wm8904_desc *wm8904, uint8_t reg_addr)
{
	int err;
	uint8_t temp_data[2] = { 0, 0 };
	struct _buffer buf[2] = {
		{
			.data = &reg_addr,
			.size = 1,
			.attr = BUS_I2C_BUF_ATTR_START | BUS_BUF_ATTR_TX | BUS_I2C_BUF_ATTR_STOP,
		},
		{
			.data = temp_data,
			.size = 2,
			.attr = BUS_I2C_BUF_ATTR_START | BUS_BUF_ATTR_RX | BUS_I2C_BUF_ATTR_STOP,
		},
	};

	bus_start_transaction(wm8904->twi.bus);
	err = bus_transfer(wm8904->twi.bus, wm8904->twi.addr, buf, 2, NULL);
	bus_stop_transaction(wm8904->twi.bus);

	if (err < 0)
		return err;

	return (temp_data[0] << 8) | temp_data[1];
}

/**
 * \brief  Write data to WM8904 Register.
 * \param wm8904   Descriptor of WM8904
 * \param reg_addr Register address to read.
 * \param data    Data to write
 */
static int wm8904_write(struct _wm8904_desc *wm8904, uint8_t reg_addr, uint16_t data)
{
	int err;
	uint8_t tmp_data[2] = { 0, 0 };
	struct _buffer buf[2] = {
		{
			.data = &reg_addr,
			.size = 1,
			.attr = BUS_I2C_BUF_ATTR_START | BUS_BUF_ATTR_TX,
		},
		{
			.data = tmp_data,
			.size = 2,
			.attr = BUS_BUF_ATTR_TX | BUS_I2C_BUF_ATTR_STOP,
		},
	};

	tmp_data[0] = (data & 0xff00) >> 8;
	tmp_data[1] = data & 0xff;

	bus_start_transaction(wm8904->twi.bus);
	err = bus_transfer(wm8904->twi.bus, wm8904->twi.addr, buf, 2, NULL);
	bus_stop_transaction(wm8904->twi.bus);

	return err;
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
		wm8904_write(wm8904, WM8904_REG_ANALOGUE_LIN1, WM8904_L_IP_SEL_P_IN1L);
	} else {
		/* IN2L */
		wm8904_write(wm8904, WM8904_REG_ANALOGUE_LIN1, WM8904_L_IP_SEL_P_IN2L);
	}

	if ((wm8904->input_path & (WM8904_INPUT_PATH_IN1R | WM8904_INPUT_PATH_IN2R)) == (WM8904_INPUT_PATH_IN1R | WM8904_INPUT_PATH_IN2R))
		trace_fatal("wm8904: invalid right input path\r\n");

	if (wm8904->input_path & WM8904_INPUT_PATH_IN1R) {
		/* IN1R*/
		wm8904_write(wm8904, WM8904_REG_ANALOGUE_RIN1, WM8904_R_IP_SEL_P_IN1R);
	} else {
		/* IN2R*/
		wm8904_write(wm8904, WM8904_REG_ANALOGUE_RIN1, WM8904_R_IP_SEL_P_IN2R);
	}
}


void wm8904_set_left_volume(struct _wm8904_desc *wm8904, uint8_t vol)
{
	if (vol > WM8904_HPOUT_MAX_VOLUME)
		return;
	/** R57 (0x39) - Analogue OUT1 Left */
	wm8904_write(wm8904, WM8904_REG_ANALOGUE_LOUT1, WM8904_HPOUT_VU | WM8904_HPOUTZC | vol);
}

void wm8904_set_right_volume(struct _wm8904_desc *wm8904, uint8_t vol)
{
	if (vol > WM8904_HPOUT_MAX_VOLUME)
		return;
	/** R58 (0x3a) Analogue OUT1 Right */
	wm8904_write(wm8904, WM8904_REG_ANALOGUE_ROUT1, WM8904_HPOUT_VU | WM8904_HPOUTZC | vol);
}

void wm8904_volume_mute(struct _wm8904_desc *wm8904, bool left, bool right)
{
	uint16_t left_val = wm8904_read(wm8904, WM8904_REG_ANALOGUE_LOUT1);
	uint16_t right_val = wm8904_read(wm8904, WM8904_REG_ANALOGUE_ROUT1);

	if (left) {
		/** R57 (0x39) - Analogue OUT1 Left Mute */
		wm8904_write(wm8904, WM8904_REG_ANALOGUE_LOUT1, WM8904_HPOUT_MUTE | WM8904_HPOUT_VU | left_val);
	} else {
		left_val &= ~WM8904_HPOUT_MUTE;
		/** R57 (0x39) - Analogue OUT1 Left Unmute */
		wm8904_write(wm8904, WM8904_REG_ANALOGUE_LOUT1, WM8904_HPOUT_VU | left_val);
	}

	if (right) {
		/** R58 (0x3a) Analogue OUT1 Right Mute */
		wm8904_write(wm8904, WM8904_REG_ANALOGUE_ROUT1, WM8904_HPOUT_MUTE | WM8904_HPOUT_VU | right_val);
	} else {
		right_val &= ~WM8904_HPOUT_MUTE;
		/** R58 (0x3a) Analogue OUT1 Right Unmute */
		wm8904_write(wm8904, WM8904_REG_ANALOGUE_ROUT1, WM8904_HPOUT_VU | right_val);
	}
}

bool wm8904_detect(struct _wm8904_desc *wm8904)
{
	/* Wait for pck out clock is ready */
	msleep(10);
	/* Check that WM8904 is there */
	wm8904_write(wm8904, WM8904_REG_RESET, 0);
	msleep(10);
	return (wm8904_read(wm8904, 0) == WM8904_DEVICE_ID);
}

void wm8904_reset(struct _wm8904_desc *wm8904)
{
	/* Writing to this register resets all registers to their default state. */
	wm8904_write(wm8904, WM8904_REG_RESET, 0xFFFF);
	msleep(10);
	/* Wait until codec is ready */
	while (wm8904_read(wm8904, 0) != WM8904_DEVICE_ID);
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
