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

#include "board.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"

#include "audio/ad1934.h"
#include "peripherals/pmc.h"
#include "gpio/pio.h"
#include "spi/spid.h"
#include "peripherals/bus.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

#define AD1934_PLL_CLK_CTRL0    0x00
#define AD1934_PLL_CLK_CTRL1    0x01
#define AD1934_DAC_CTRL0        0x02
#define AD1934_DAC_CTRL1        0x03
#define AD1934_DAC_CTRL2        0x04
#define AD1934_DAC_CHNL_MUTE    0x05
#define AD1934_DAC_L1_VOL       0x06
#define AD1934_DAC_R1_VOL       0x07
#define AD1934_DAC_L2_VOL       0x08
#define AD1934_DAC_R2_VOL       0x09
#define AD1934_DAC_L3_VOL       0x0a
#define AD1934_DAC_R3_VOL       0x0b
#define AD1934_DAC_L4_VOL       0x0c
#define AD1934_DAC_R4_VOL       0x0d
#define AD1934_ADC_CTRL0        0x0f
#define AD1934_ADC_CTRL1        0x10

/* This is the chip address 4 shifted left one bit plus the Read bit set to read */
#define AD1934_GLOBAL_ADDRESS_READ 0x09

/* This is the chip address 4 shifted left one bit plus the Write bit set to write */
#define AD1934_GLOBAL_ADDRESS_WRITE 0x08

#define AD1934_PLL_NORMAL_OPERATION 0x00
#define AD1934_PLL_POWERDOWN        0x01

#define AD1934_PLL_INPUT_MASK   0x6
#define AD1934_PLL_INPUT_256    (0 << 1)
#define AD1934_PLL_INPUT_384    (1 << 1)
#define AD1934_PLL_INPUT_512    (2 << 1)
#define AD1934_PLL_INPUT_768    (3 << 1)

#define AD1934_PLL_MCLKO_OFF    (3 << 3)
#define AD1934_PLL_INPUT_MCLK   (0 << 5)

#define AD1934_PLL_DAC_ACTIVE   (1 << 7)

#define AD1934_DAC_POWERDOWN            0x01
#define AD1934_DAC_SERFMT_MASK          0xC0
#define AD1934_DAC_SERFMT_STEREO        (0 << 6)
#define AD1934_DAC_SERFMT_TDM           (1 << 6)

#define AD1934_CTRL1_BCLK_ACTIVE_EDGE_NORMAL (0 << 0)
#define AD1934_CTRL1_LRCLK_LEFT_LOW          (0 << 3)
#define AD1934_CTRL1_LRCLK_MODE_MASTER       (1 << 4)
#define AD1934_CTRL1_BCLK_MODE_MASTER        (1 << 5)
#define AD1934_CTRL1_BCLK_SOURCE_INTERNAL    (1 << 6)
#define AD1934_CTRL1_BCLK_POLARITY_NORMAL    (0 << 7)

#define AD1934_DAC_CTRL0_SAMPLE_RATE_SHFT    (1)
#define AD1934_DAC_CTRL0_SAMPLE_RATE_MASK    (3 << AD1934_DAC_CTRL0_SAMPLE_RATE_SHFT)

#define AD1934_DAC_WORD_LEN_SHFT         3
#define AD1934_DAC_WORD_LEN_MASK        (3 << AD1934_DAC_WORD_LEN_SHFT)
#define AD1934_DAC_MASTER_MUTE  1

#define AD1934_DACL1_MUTE       0
#define AD1934_DACR1_MUTE       1
#define AD1934_DACL2_MUTE       2
#define AD1934_DACR2_MUTE       3
#define AD1934_DACL3_MUTE       4
#define AD1934_DACR3_MUTE       5
#define AD1934_DACL4_MUTE       6
#define AD1934_DACR4_MUTE       7

#define AD1934_DAC_CHAN_SHFT    1
#define AD1934_DAC_CHAN_MASK    (3 << AD1934_DAC_CHAN_SHFT)
#define AD1934_DAC_LCR_MASTER   (1 << 4)
#define AD1934_DAC_BCLK_MASTER  (1 << 5)
#define AD1934_DAC_LEFT_HIGH    (1 << 3)
#define AD1934_DAC_BCLK_INV     (1 << 7)
#define AD1934_DAC_FMT_MASK     (AD1934_DAC_LCR_MASTER | \
         AD1934_DAC_BCLK_MASTER | AD1934_DAC_LEFT_HIGH | AD1934_DAC_BCLK_INV)

#define AD1934_2_CHANNELS   0
#define AD1934_4_CHANNELS   1
#define AD1934_8_CHANNELS   2
#define AD1934_16_CHANNELS  3

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Read data from AD1934 Register.
 *
 * \param spid   Pointer to spi driver structure
 * \param reg_addr Register address to read.
 * \return value in the given register.
 */
static uint8_t ad1934_read_reg(struct _ad1934_desc* ad1934, uint8_t reg_addr)
{
	uint8_t spi_in_message[1], spi_out_message[2];

	/* Global Address[23:17] R/W[16] Register Address[15:8] Data[7:0] */
	spi_out_message[0] = AD1934_GLOBAL_ADDRESS_READ;
	spi_out_message[1] = reg_addr;

	struct _buffer buf[2] = {
		{
			.data = spi_out_message,
			.size = sizeof(spi_out_message),
			.attr = BUS_BUF_ATTR_TX,
		},
		{
			.data = spi_in_message,
			.size = sizeof(spi_in_message),
			.attr = BUS_BUF_ATTR_RX | BUS_SPI_BUF_ATTR_RELEASE_CS,
		},
	};

	bus_start_transaction(ad1934->bus);
	bus_transfer(ad1934->bus, ad1934->dev->spi_dev.chip_select, buf, 2, NULL);
	bus_stop_transaction(ad1934->bus);

	return spi_in_message[0];
}

/**
 * \brief  Write data to AD1934 Register.
 *
 * \param spid   Pointer to spi driver structure
 * \param reg_addr Register address to read.
 * \param data    Data to write
 */
static void ad1934_write_reg(struct _ad1934_desc* ad1934, uint8_t reg_addr, uint8_t data)
{
	uint8_t spi_out_message[3];

	/* Global Address[23:17] R/W[16] Register Address[15:8] Data[7:0] */
	spi_out_message[0] = AD1934_GLOBAL_ADDRESS_WRITE;
	spi_out_message[1] = reg_addr;
	spi_out_message[2] = data;

	struct _buffer out = {
		.data = spi_out_message,
		.size = 3,
		.attr = BUS_BUF_ATTR_TX | BUS_SPI_BUF_ATTR_RELEASE_CS,
	};

	bus_start_transaction(ad1934->bus);
	bus_transfer(ad1934->bus, ad1934->dev->spi_dev.chip_select, &out, 1, NULL);
	bus_stop_transaction(ad1934->bus);

	return;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void ad1934_configure(struct _ad1934_desc* ad1934)
{
	/* Configure spi chip select */
	bus_configure_slave(ad1934->dev->bus, ad1934->dev);

	/* unmute all dac channels */
	ad1934_write_reg(ad1934, AD1934_DAC_CHNL_MUTE, 0x0);

	/* mclk=12.288Mhz fs=48Khz, 256*fs mode */
	ad1934_write_reg(ad1934, AD1934_PLL_CLK_CTRL0,
		AD1934_PLL_NORMAL_OPERATION | AD1934_PLL_INPUT_256 | AD1934_PLL_MCLKO_OFF |
		AD1934_PLL_INPUT_MCLK | AD1934_PLL_DAC_ACTIVE);

	/* Serial format in tdm mode, fs=48K, SDATA=1*/
	ad1934_write_reg(ad1934, AD1934_DAC_CTRL0, AD1934_DAC_SERFMT_TDM);

	/* LRCLK polarity left low, BCLK source internally generated, master mode */
	ad1934_write_reg(ad1934, AD1934_DAC_CTRL1,
		AD1934_CTRL1_BCLK_ACTIVE_EDGE_NORMAL | AD1934_CTRL1_LRCLK_LEFT_LOW |
		AD1934_CTRL1_LRCLK_MODE_MASTER | AD1934_CTRL1_BCLK_MODE_MASTER |
		AD1934_CTRL1_BCLK_SOURCE_INTERNAL | AD1934_CTRL1_BCLK_POLARITY_NORMAL);
}


void ad1934_master_volume_mute(struct _ad1934_desc* ad1934, bool mute)
{
	uint8_t val = ad1934_read_reg(ad1934, AD1934_DAC_CTRL2);
	if (mute)
		ad1934_write_reg(ad1934, AD1934_DAC_CTRL2, val | AD1934_DAC_MASTER_MUTE);
	else
		ad1934_write_reg(ad1934, AD1934_DAC_CTRL2, val & ~AD1934_DAC_MASTER_MUTE);
}


bool ad1934_set_tdm_slot(struct _ad1934_desc* ad1934, int slots)
{
	uint32_t channels;
	uint8_t val;

	switch (slots) {
	case 2:
		channels = AD1934_2_CHANNELS;
		break;
	case 4:
		channels = AD1934_4_CHANNELS;
		break;
	case 8:
		channels = AD1934_8_CHANNELS;
		break;
	case 16:
		channels = AD1934_16_CHANNELS;
		break;
	default:
		return false;
	}

	val = ad1934_read_reg(ad1934, AD1934_DAC_CTRL1);
	ad1934_write_reg(ad1934, AD1934_DAC_CTRL1,
			(val & ~AD1934_DAC_CHAN_MASK) | (channels << AD1934_DAC_CHAN_SHFT));

	return true;
}


bool ad1934_set_sample_rate(struct _ad1934_desc* ad1934, uint32_t sample_rate)
{
	uint8_t val, fs;
	switch (sample_rate) {
	case 32000:
	case 44100:
	case 48000:
		fs = 0x0;
		break;
	case 64000:
	case 88200:
	case 96000:
		fs = 0x1;
		break;
	case 128000:
	case 176400:
	case 192000:
		fs = 0x10;
		break;
	default:
		return false;
	}

	val = ad1934_read_reg(ad1934, AD1934_DAC_CTRL0);
	ad1934_write_reg(ad1934, AD1934_DAC_CTRL0,
			(val & ~AD1934_DAC_CTRL0_SAMPLE_RATE_MASK)
				| (fs << AD1934_DAC_CTRL0_SAMPLE_RATE_SHFT));
	return true;
}


bool ad1934_set_word_width(struct _ad1934_desc* ad1934, uint8_t word_len)
{
	uint8_t val;

	 /* bit size */
	switch (word_len) {
	case 16:
		word_len = 3;
		break;
	case 20:
		word_len = 1;
		break;
	case 24:
	case 32:
		word_len = 0;
		break;
	default:
		return false;
	}

	val = ad1934_read_reg(ad1934, AD1934_DAC_CTRL2);
	ad1934_write_reg(ad1934, AD1934_DAC_CTRL2,
			(val & ~AD1934_DAC_WORD_LEN_MASK) | (word_len << AD1934_DAC_WORD_LEN_SHFT));

	return true;
}


void ad1934_set_channel_volume(struct _ad1934_desc* ad1934, enum _ad1934_dac_channel channel, uint8_t volume)
{
	uint8_t chan_reg;

	switch (channel) {
	case AD1934_DAC_L1_CHANNEL:
		chan_reg = AD1934_DAC_L1_VOL;
		break;
	case AD1934_DAC_R1_CHANNEL:
		chan_reg = AD1934_DAC_R1_VOL;
		break;
	case AD1934_DAC_L2_CHANNEL:
		chan_reg = AD1934_DAC_L2_VOL;
		break;
	case AD1934_DAC_R2_CHANNEL:
		chan_reg = AD1934_DAC_R2_VOL;
		break;
	case AD1934_DAC_L3_CHANNEL:
		chan_reg = AD1934_DAC_L3_VOL;
		break;
	case AD1934_DAC_R3_CHANNEL:
		chan_reg = AD1934_DAC_R3_VOL;
		break;
	case AD1934_DAC_L4_CHANNEL:
		chan_reg = AD1934_DAC_L4_VOL;
		break;
	case AD1934_DAC_R4_CHANNEL:
		chan_reg = AD1934_DAC_R4_VOL;
		break;
	default:
		return;
	}

	/* 0 -> No attenuation, 1 to 254 -> -3/8 db per step, 255->Full attenuation */
	ad1934_write_reg(ad1934, chan_reg, volume);
}
