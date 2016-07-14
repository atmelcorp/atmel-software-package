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
#include "peripherals/twid.h"
#include "peripherals/pmc.h"

#include "timer.h"

#include <stdio.h>

/*----------------------------------------------------------------------------
 *        Type
 *----------------------------------------------------------------------------*/
typedef struct {
	uint16_t value;
	uint8_t address;
} wm8904_para;

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Read data from WM8904 Register.
 *
 * \param twid   Pointer to twi driver structure
 * \param device  Twi slave address.
 * \param reg_addr Register address to read.
 * \return value in the given register.
 */
uint16_t wm8904_read(struct _twi_desc * twid, uint32_t device, uint32_t reg_addr)
{
	uint16_t bits_data_register;
	uint8_t temp_data[2] = { 0, 0 };
	struct _buffer in = {
		.data = temp_data,
		.size = 2,
	};

	twid->slave_addr = device;
	twid->iaddr = reg_addr;
	twid->isize = 1;

	twid_transfer(twid, &in, NULL, NULL, NULL);
	while (twid_is_busy(twid));

	bits_data_register = (temp_data[0] << 8) | temp_data[1];
	return bits_data_register;
}

/**
 * \brief  Write data to WM8904 Register.
 *
 * \param twid   Pointer to twi driver structure
 * \param device  Twi slave address.
 * \param reg_addr Register address to read.
 * \param data    Data to write
 */
void wm8904_write(struct _twi_desc * twid, uint32_t device, 
						uint32_t reg_addr, uint16_t data)
{
	uint8_t tmp_data[2] = { 0, 0 };
	struct _buffer out = {
		.data = tmp_data,
		.size = 2,
	};

	twid->slave_addr = device;
	twid->iaddr = reg_addr;
	twid->isize = 1;

	tmp_data[0] = (data & 0xff00) >> 8;
	tmp_data[1] = data & 0xff;
	twid_transfer(twid, NULL, &out, NULL, NULL);
	while (twid_is_busy(twid));
}


static wm8904_para wm8904_access_slow[] = {
	{0x0000, 0},    /** R0   - SW Reset and ID */
	{0x001A, 4},    /** R4   - Bias Control 0 */
	{0x0047, 5},    /** R5   - VMID Control 0 *//*insert_delay_ms 5 */

	{0x0043, 5},    /** R5   - VMID Control 0 */
	{0x000B, 4},    /** R4   - Bias Control 0 */

	{0x0003, 0x0C},    /** R12  - Power Management 0 CC */

	{0x0003, 0x0E},    /** R14  - Power Management 2 */
	{0x000C, 0x12},    /** R18  - Power Management 6 */
	{0x0000, 0x21},    /** R33  - DAC Digital 1 */
	{0x0000, 0x3D},    /** R61  - Analogue OUT12 ZC */
	{0x0001, 0x62},    /** R98  - Charge Pump 0 */
	{0x0005, 0x68},    /** R104 - Class W 0 */

	/* FLL setting,32.768KHZ MCLK input,12.288M output. */
	{0x0000, 0x74},    /** R116 - FLL Control 1 */
	{0x0704, 0x75},    /** R117 - FLL Control 2 */
	{0x8000, 0x76},    /** R118 - FLL Control 3 */
	{0x1760, 0x77},    /** R119 - FLL Control 4 */
	{0x0005, 0x74},    /** R116 - FLL Control 1 *//*insert_delay_ms 5 */

	{0x0C05, 0x15},    /** R21  - Clock Rates 1 */
	{0x845E, 0x14},    /** R20  - Clock Rates 0 */
	{0x4006, 0x16},    /** R22  - Clock Rates 2 */

	/* wm8904 IIS master BCLK=12.288MHz/8=1.536MHz LRCK=1.536MHz/32=48KHz */
	{0x0042, 0x19},    /** R25  - Audio Interface 1 */
	{0x00E8, 0x1A},    /** R26  - Audio Interface 2 */
	{0x0820, 0x1B},    /** R27  - Audio Interface 3 */

	{0x0003, 0x0C},    /** R12  - Power Management 0 */
	{0x000F, 0x12},    /** R18  - Power Management 6 *//*insert_delay_ms 5 */

	{0x0010, 0x2C},    /** R44  - Analogue Left Input 0 */
	{0x0010, 0x2D},    /** R45  - Analogue Right Input 0 */
	{0x0004, 0x2E},    /** R46  - Analogue Left Input 1 */
	{0x0004, 0x2F},    /** R47  - Analogue Right Input 1 */

	{0x0011, 0x5A},    /** R90  - Analogue HP 0 */
	{0x0033, 0x5A},    /** R90  - Analogue HP 0 */

	{0x000F, 0x43},    /** R67  - DC Servo 0 */
	{0x00F0, 0x44},    /** R68  - DC Servo 1 *//*insert_delay_ms 100 */

	{0x0077, 0x5A},    /** R90  - Analogue HP 0 */
	{0x00FF, 0x5A},    /** R90  - Analogue HP 0 */
	{0x00B9, 0x39},    /** R57  - Analogue OUT1 Left */
	{0x00B9, 0x3A},    /** R58  - Analogue OUT1 Right */

};

static wm8904_para wm8904_access_main[] = {
	{0x0019, 4},     /** R4   - Bias Control 0 */
	{0x0043, 5},     /** R5   - VMID Control 0 */
	{0x0003, 12},    /** R12  - Power Management 0 */
	{0x0003, 14},    /** R14  - Power Management 2 */
	{0x000F, 18},    /** R18  - Power Management 6 */
	{0x845E, 20},    /** R20  - Clock Rates 0 */
	{0x0006, 22},    /** R22  - Clock Rates 2 */
	{0x404A, 25},    /** R25  - Audio Interface 1 */
	{0x0840, 27},    /** R27  - Audio Interface 3 */
	{0x0000, 33},    /** R33  - DAC Digital 1 */
	{0x0005, 44},    /** R44  - Analogue Left Input 0 */
	{0x0005, 45},    /** R45  - Analogue Right Input 0 */
	{0x0000, 46},    /** R46  - Analogue Left Input 1 */
	{0x0000, 47},    /** R47  - Analogue Right Input 1 */
	{0x00AD, 58},    /** R58  - Analogue OUT1 Right */
	{0x0003, 67},    /** R67  - DC Servo 0 */
	{0x00FF, 90},    /** R90  - Analogue HP 0 */
	{0x0001, 98},    /** R98  - Charge Pump 0 */
	{0x0005, 104},   /** R104 - Class W 0 */
	{0x0004, 116},   /** R116 - FLL Control 1 */
	{0x0704, 117},   /** R117 - FLL Control 2 */
	{0x8000, 118},   /** R118 - FLL Control 3 */
	{0x1760, 119},   /** R119 - FLL Control 4 */
	{0x55AA, 255}    /** end */
};

uint8_t wm8904_init(struct _twi_desc* twid, uint32_t device, uint32_t PCK, uint8_t input_path)
{
	uint8_t count;
	uint16_t data = 0;

	/* write Reg@0x0 to reset) */
	wm8904_write(twid, device, 0, 0xFFFF);

	for (data = 0; data < 1000; data++) ;
	/* wait ready */
	while (data != 0x8904)
		data = wm8904_read(twid, device, 0);

	if (PMC_MCKR_CSS_SLOW_CLK == PCK) {
		for (count = 0; count < ARRAY_SIZE(wm8904_access_slow); count++) {
					wm8904_write(twid, device, wm8904_access_slow[count].address,
							wm8904_access_slow[count].value);
			if (((wm8904_access_slow[count].address == 0x05) && 
				(wm8904_access_slow[count].value == 0x0047)) ||
				((wm8904_access_slow[count].address == 0x74) && 
				(wm8904_access_slow[count].value == 0x0005)) ||
				((wm8904_access_slow[count].address == 0x12) && 
				(wm8904_access_slow[count].value == 0x000F))) {
				timer_wait(5);
			}
			if (((wm8904_access_slow[count].address == 0x44) && 
					(wm8904_access_slow[count].value == 0x00F0)) ||
					((wm8904_access_slow[count].address == 0x3A) && 
					(wm8904_access_slow[count].value == 0x00B9))) {
				timer_wait(100);
			}
		}
		if (input_path & WM8904_INPUT_PATH_IN2L) {
			/* IN2L */
			wm8904_write(twid, device, WM8904_REG_ANALOGUE_LIN1, 0x0010);
		}
		if (input_path & WM8904_INPUT_PATH_IN2R) {
			/* IN2R*/
			wm8904_write(twid, device, WM8904_REG_ANALOGUE_RIN1, 0x0010);
		}
	} else if (PMC_MCKR_CSS_MAIN_CLK == PCK) {
		for (count = 0; count < ARRAY_SIZE(wm8904_access_main); count++)
			wm8904_write(twid, device,
			 		wm8904_access_main[count].address,
					wm8904_access_main[count].value);
	} else {
		trace_error("wm8904: PCK not supported! \n\r");
		while (1) ;
	}

	return 0;
}

void wm8904_in2r_in1l(struct _twi_desc* twid, uint32_t device)
{
	/** R44  - Analogue Left Input 0 */
	wm8904_write(twid, device, 0x2C, 0x0008);

	/** R45  - Analogue Right Input 0 */
	wm8904_write(twid, device, 0x2D, 0x0005);

	/** R46  - Analogue Left Input 1 */
	wm8904_write(twid, device, 0x2E, 0x0000);

	/** R47  - Analogue Right Input 1 */
	wm8904_write(twid, device, 0x2F, 0x0010);
}

void wm8904_set_left_volume(struct _twi_desc* twid, uint32_t device, uint8_t vol)
{
	if(vol > WM8904_HPOUT_MAX_VOLUME)
		return;
	/** R57 (0x39) - Analogue OUT1 Left */
	wm8904_write(twid, device, 0x39, WM8904_HPOUT_VU | WM8904_HPOUTZC | vol);
}

void wm8904_set_right_volume(struct _twi_desc* twid, uint32_t device, uint8_t vol)
{
	if(vol > WM8904_HPOUT_MAX_VOLUME)
		return;
	/** R58 (0x3a) Analogue OUT1 Right */
	wm8904_write(twid, device, 0x3a, WM8904_HPOUT_VU | WM8904_HPOUTZC | vol);
}

void wm8904_volume_mute(struct _twi_desc* twid, uint32_t device, bool left, bool right)
{
	uint16_t left_val = wm8904_read(twid, device, 0x39);
	uint16_t right_val = wm8904_read(twid, device, 0x3a);

	if(left) {
		/** R57 (0x39) - Analogue OUT1 Left Mute */
		wm8904_write(twid, device, 0x39, WM8904_HPOUT_MUTE | WM8904_HPOUT_VU | left_val);
	} else {
		left_val &= ~WM8904_HPOUT_MUTE;
		/** R57 (0x39) - Analogue OUT1 Left Unmute */
		wm8904_write(twid, device, 0x39, WM8904_HPOUT_VU |  left_val);
	}

	if(right) {
		/** R58 (0x3a) Analogue OUT1 Right Mute */
		wm8904_write(twid, device, 0x3a, WM8904_HPOUT_MUTE | WM8904_HPOUT_VU | right_val);
	} else {
		right_val &= ~WM8904_HPOUT_MUTE;
		/** R58 (0x3a) Analogue OUT1 Right Unmute */
		wm8904_write(twid, device, 0x3a, WM8904_HPOUT_VU | right_val);
	}

}

