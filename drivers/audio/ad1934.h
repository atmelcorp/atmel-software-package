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

#ifndef AD1934_H_
#define AD1934_H_

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

#include "peripherals/bus.h"

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

enum _ad1934_dac_channel {
	AD1934_DAC_L1_CHANNEL,
	AD1934_DAC_R1_CHANNEL,
	AD1934_DAC_L2_CHANNEL,
	AD1934_DAC_R2_CHANNEL,
	AD1934_DAC_L3_CHANNEL,
	AD1934_DAC_R3_CHANNEL,
	AD1934_DAC_L4_CHANNEL,
	AD1934_DAC_R4_CHANNEL,
};

struct _ad1934_desc {
	uint8_t bus; /* SPI bus */
	const struct _bus_dev_cfg* dev; /* SPI device configuration */
};

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief AD1934 chip initialize.
 *
 * \param ad1934   Pointer to ad1934_desc structure
 */
extern void ad1934_configure(struct _ad1934_desc* ad1934);


/**
 * \brief  Mute or unmute the master volume of ad1934.
 *
 * \param ad1934   Pointer to ad1934_desc structure
 * \param reg_addr Register address to read.
 * \param data    Data to write
 */
extern void ad1934_master_volume_mute(struct _ad1934_desc* ad1934, bool mute);

/**
 * \brief  Set the slot number of tdm.
 *
 * \param ad1934   Pointer to ad1934_desc structure
 * \param slots    number channel of sound data
 * \return true if successful; otherwise return false.
 */
extern bool ad1934_set_tdm_slot(struct _ad1934_desc* ad1934, int slots);

/**
 * \brief  Set the word width of sound data.
 *
 * \param ad1934  Pointer to ad1934_desc structure
 * \param word_len  word width of sound data
 * \return true if successful; otherwise return false.
 */
extern bool ad1934_set_word_width(struct _ad1934_desc* ad1934, uint8_t word_len);

/**
 * \brief  Set the volume of specify channel.
 *
 * \param ad1934  Pointer to ad1934_desc structure
 * \param channel  the number channel need to change volume
 * \param volume  the volume value of specify channel
 * \return true if successful; otherwise return false.
 */
extern void ad1934_set_channel_volume(struct _ad1934_desc* ad1934, enum _ad1934_dac_channel channel, uint8_t volume);

/**
 * \brief  Set the sample rate of sound data.
 *
 * \param ad1934  Pointer to ad1934_desc structure
 * \param sample_rate  sample rate of sound data
 * \return true if successful; otherwise return false.
 */
extern bool ad1934_set_sample_rate(struct _ad1934_desc* ad1934, uint32_t sample_rate);
#endif /* AD1934_H_ */
