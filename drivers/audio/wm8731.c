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
 * Implementation of wm8731 driver.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "trace.h"
#include "audio/wm8731.h"
#include "peripherals/bus.h"
#include "i2c/twid.h"
#include "peripherals/pmc.h"

#include "timer.h"

#include <stdio.h>

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

/** Reset register*/
#define WM8731_REG_RESET                           0x1E

/** Left Line in register*/
#define WM8731_REG_LEFT_lINEIN                     0x0
/** Left line input volume control*/
#define WM8731_LINVOL_BITS                         (0x1f << 0)
/** Left line input mute to ADC*/
#define WM8731_LINMUTE_BIT                         (0x1 << 7)
/** Left to right channel line input volume and mute data load control*/
#define WM8731_LRINBOTH_BIT                        (0x0 << 8)

/** Right Line in register*/
#define WM8731_REG_RIGHT_lINEIN                     0x1
/** Right line input volume control*/
#define WM8731_RINVOL_BITS                         (0x1f << 0)
/** Right line input mute to ADC*/
#define WM8731_RINMUTE_BIT                         (0x1 << 7)
/** Right to right channel line input volume and mute data load control*/
#define WM8731_RLINBOTH_BIT                        (0x0 << 8)

/** Left Headphone out register*/
#define WM8731_REG_LEFT_HPOUT                      0x2
/** Left chnnel headphone output volume control*/
#define WM8731_LHPVOL_BITS                         (0x7f << 0)
/** Left chnnel headphone output volume base */
#define WM8731_LHPVOL_BASE                         (0x30 << 0)
/** Left channel zero cross detect enable*/
#define WM8731_LZCEN_BIT                           (0x1 << 7)
/** Left to right channel headphone volume, mute and zero cross data load control*/
#define WM8731_LRHPBOTH_BIT                        (0x1 << 8)

/** Right Headphone out register*/
#define WM8731_REG_RIGHT_HPOUT                      0x3
/** Right chnnel headphone output volume control*/
#define WM8731_RHPVOL_BITS                         (0x7f << 0)
/** Right chnnel headphone output volume base */
#define WM8731_RHPVOL_BASE                         (0x30 << 0)
/** Right channel zero cross detect enable*/
#define WM8731_RZCEN_BIT                           (0x1 << 7)
/** Right to right channel headphone volume, mute and zero cross data load control*/
#define WM8731_RLHPBOTH_BIT                        (0x1 << 8)

/** Analogue audio path control register*/
#define WM8731_REG_ANALOGUE_PATH_CTRL              0x4

/** Digital audio path control register*/
#define WM8731_REG_DIGITAL_PATH_CTRL               0x5
/* DAC soft mute control */
#define WM8731_DAC_SOFT_MUTE                        (0x1 << 3)
#define WM8731_DAC_SOFT_UNMUTE                      (0x0 << 3)

/** Power down control register*/
#define WM8731_REG_PWDOWN_CTRL                     0x6
/** LineIn power down*/
#define WM8731_LINEINPD_BIT                        (0x1 << 0)
#define WM8731_ENABLE_LINEINPD                     (0x1 << 0)
#define WM8731_DISABLE_LINEINPD                    (0x0 << 0)
/** Mic power down*/
#define WM8731_MICPD_BIT                           (0x1 << 1)
#define WM8731_ENABLE_MICPD                        (0x1 << 1)
#define WM8731_DISABLE_MICPD                       (0x0 << 1)
/** ADC power down*/
#define WM8731_ADCPD_BIT                           (0x1 << 2)
#define WM8731_ENABLE_ADCPD                        (0x1 << 2)
#define WM8731_DISABLE_ADCPD                       (0x0 << 2)
/** DAC power down*/
#define WM8731_DACPD_BIT                           (0x1 << 3)
#define WM8731_ENABLE_DACPD                        (0x1 << 3)
#define WM8731_DISABLE_DACPD                       (0x0 << 3)
/** OUT power down*/
#define WM8731_OUTPD_BIT                           (0x1 << 4)
#define WM8731_ENABLE_OUTPD                        (0x1 << 4)
#define WM8731_DISABLE_OUTPD                       (0x0 << 4)
/** OSC power down*/
#define WM8731_OSCBIT                              (0x1 << 5)
#define WM8731_ENABLE_OSCPD                        (0x1 << 5)
#define WM8731_DISABLE_OSCPD                       (0x0 << 5)
/** CLKOUT powerdown*/
#define WM8731_CLKOUTPD_BIT                        (0x1 << 6)
#define WM8731_ENABLE_CLKOUTPD                     (0x1 << 6)
#define WM8731_DISABLE_CLKOUTPD                    (0x0 << 6)
/** Power off device*/
#define WM8731_POWEROFF_BIT                        (0x1 << 7)
#define WM8731_DEV_POWER_OFF                       (0x1 << 7)
#define WM8731_DEV_POWER_ON                        (0x0 << 7)

/** Interface format register*/
#define WM8731_REG_DA_INTERFACE_FORMAT             0x7
/** Format*/
#define WM8731_FORMAT_BITS                         (0x3 << 0)
#define WM8731_FORMAT_MSB_LEFT_JUSTIFIED           (0x0 << 0)
#define WM8731_FORMAT_MSB_RIGHT_JUSTIFIED          (0x1 << 0)
#define WM8731_FORMAT_I2S                          (0x2 << 0)
#define WM8731_FORMAT_DSP                          (0x3 << 0)
/** Input audio data bit length select*/
#define WM8731_IWL_BITS                            (0x3 << 2)
#define WM8731_IWL_16_BIT                          (0x0 << 2)
#define WM8731_IWL_20_BIT                          (0x1 << 2)
#define WM8731_IWL_24_BIT                          (0x2 << 2)
#define WM8731_IWL_32_BIT                          (0x3 << 2)
/** DACLRC phase control*/
#define WM8731_IRP_BITS                            (0x1 << 4)
/** DAC Left right clock swap*/
#define WM8731_LRSWAP_BIT                          (0x1 << 5)
/** Master slave mode control*/
#define WM8731_MS_BIT                              (0x1 << 6)
#define WM8731_ENABLE_MASTER_MODE                  (0x1 << 6)
#define WM8731_ENABLE_SLAVE_MODE                   (0x0 << 6)
/** Bit clock invert*/
#define WM8731_BCLKINV_BIT                         (0x1 << 7)

/** Sampling control*/
#define WM8731_REG_SAMPLECTRL                      0x8
/** Mode select, usb mode, normal mode*/
#define WM8731_USBNORMAL_BIT                       (0x1 << 0)
#define WM8731_NORMAL_MODE                         (0x1 << 0)
#define WM8731_USB_MODE                            (0x1 << 1)
/** Base over-sampling rate*/
#define WM8731_BOSR_BIT                            (0x1 << 1)
#define WM8731_USB_250FS                           (0x0 << 1)
#define WM8731_USB_272FS                           (0x1 << 1)
#define WM8731_NORMAL_256FS                        (0x0 << 1)
#define WM8731_NORMAL_128_192_384_FS               (0x1 << 1)
/** Sample rate control*/
#define WM8731_SR_BITS                             (0xf << 2)
#define WM8731_CLKIDIV2_BIT                        (0x1 << 6)
#define WM8731_CLKODIV2_BIT                        (0x1 << 7)

/** Active control register*/
#define WM8731_REG_ACTIVE_CTRL                     0x9
/** Activate interface*/
#define WM8731_ACTIVE_BIT                          (0x1 << 0)
#define WM8731_ACTIVE_INTERFACE_ACTIVE             (0x1 << 1)
#define WM8731_ACTIVE_INTERFACE_INACTIVE           (0x0 << 1)

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief  Write data to WM8731 Register.
 * \param wm8731   Descriptor of WM8731
 * \param reg_addr Register address to read.
 * \param data    Data to write
 */
static void wm8731_write(struct _wm8731_desc *wm8731, uint8_t reg_addr, uint16_t data)
{
	uint16_t tmp = ((reg_addr & 0x7f) << 9) | (data & 0x1ff);
	uint8_t tmp_data[2] = {(tmp & 0xff00) >> 8, tmp & 0xff};

	struct _buffer buf[2] = {
		{
			.data = &tmp_data[0],
			.size = 1,
			.attr = BUS_I2C_BUF_ATTR_START | BUS_BUF_ATTR_TX,
		},
		{
			.data = &tmp_data[1],
			.size = 1,
			.attr = BUS_BUF_ATTR_TX | BUS_I2C_BUF_ATTR_STOP,
		},
	};

	bus_start_transaction(wm8731->twi.bus);
	bus_transfer(wm8731->twi.bus, wm8731->twi.addr, buf, 2, NULL);
	bus_stop_transaction(wm8731->twi.bus);
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void wm8731_configure(struct _wm8731_desc *wm8731)
{
	/* configure codec master clock */
	pmc_disable_pck(wm8731->mclk_pck);
	pmc_configure_pck(wm8731->mclk_pck, wm8731->mclk_pck_src, 0);
	pmc_enable_pck(wm8731->mclk_pck);
	pio_configure(&wm8731->mclk_pin, 1);

	/* Reset (R15: write 0x0 to reset) */
	wm8731_write(wm8731, WM8731_REG_RESET, 0);

	/* Left  Linein */
	wm8731_write(wm8731, WM8731_REG_LEFT_lINEIN, 0x1A);
	/* Right Linein */
	wm8731_write(wm8731, WM8731_REG_RIGHT_lINEIN, 0x1A);

	/* Left  Headphone Out (R2: default 0x79) */
	wm8731_write(wm8731, WM8731_REG_LEFT_HPOUT, 0x60);
	/* Right Headphone Out (R3: default 0x79) */
	wm8731_write(wm8731, WM8731_REG_RIGHT_HPOUT, 0x60);

	/* Analogue Audio Path Control (R4: default 0x0A ) */
	wm8731_write(wm8731, WM8731_REG_ANALOGUE_PATH_CTRL, 0x12);

	/* Digital Audio Path Control  (R5: default 0x08 ) */
	wm8731_write(wm8731, WM8731_REG_DIGITAL_PATH_CTRL, 0);

	/* Digital audio interface format (R7: default 0x0A) */
	wm8731_write(wm8731, WM8731_REG_DA_INTERFACE_FORMAT, WM8731_FORMAT_I2S | WM8731_MS_BIT);

	/* Sampling Control (R8: default 0x00) */
	wm8731_write(wm8731, WM8731_REG_SAMPLECTRL, WM8731_USBNORMAL_BIT | WM8731_CLKIDIV2_BIT);

	/* Power Down Control (R6: default 0x9F) */
	wm8731_write(wm8731, WM8731_REG_PWDOWN_CTRL, 0x0);

	/* Active control (R9: default 0x00 )*/
	wm8731_write(wm8731, WM8731_REG_ACTIVE_CTRL, 0x01);

}

void wm8731_set_left_volume(struct _wm8731_desc *wm8731, uint8_t vol)
{
	uint16_t reg_value;
	vol &= WM8731_LHPVOL_BITS;
	vol = (vol * 80 / 63 + WM8731_LHPVOL_BASE) > WM8731_LHPVOL_BITS
		  ? WM8731_LHPVOL_BITS : (vol * 80 / 63 + WM8731_LHPVOL_BASE);
	reg_value = WM8731_LRHPBOTH_BIT | WM8731_LZCEN_BIT | vol;
	wm8731_write(wm8731, WM8731_REG_LEFT_HPOUT, reg_value);
}

void wm8731_set_right_volume(struct _wm8731_desc *wm8731, uint8_t vol)
{
	uint16_t reg_value;
	vol &= WM8731_RHPVOL_BITS;
	vol = (vol * 80 / 63 + WM8731_RHPVOL_BASE) > WM8731_RHPVOL_BITS
		  ? WM8731_RHPVOL_BITS : (vol * 80 / 63 + WM8731_RHPVOL_BASE);
	reg_value = WM8731_RZCEN_BIT | WM8731_RLHPBOTH_BIT | vol ;
	wm8731_write(wm8731, WM8731_REG_RIGHT_HPOUT, reg_value);
}

void wm8731_volume_mute(struct _wm8731_desc *wm8731, bool mute)
{
	if (mute) {
		wm8731_write(wm8731, WM8731_REG_DIGITAL_PATH_CTRL, WM8731_DAC_SOFT_MUTE);
	} else {
		wm8731_write(wm8731, WM8731_REG_DIGITAL_PATH_CTRL, WM8731_DAC_SOFT_UNMUTE);
	}
}

void wm8731_reset(struct _wm8731_desc *wm8731)
{
	wm8731_write(wm8731, WM8731_REG_RESET, 0);
	msleep(10);
}
