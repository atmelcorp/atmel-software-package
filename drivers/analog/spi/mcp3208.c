/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2017, Atmel Corporation
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

#include <errno.h>
#include <stdio.h>

#include "peripherals/bus.h"
#include "spi/spid.h"
#include "analog/spi/mcp3208.h"

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

int mcp3208_configure(struct _mcp3208_desc *desc)
{
	int i;
	int max_chan;

	/* Configure chip select */
	bus_configure_slave(desc->cfg.bus, &desc->cfg);

	/* Check model */
	switch (desc->model) {
	case MCP3208_MODEL_3204:
		max_chan = 4;
		break;
	case MCP3208_MODEL_3208:
		max_chan = 8;
		break;
	default:
		return -EINVAL;
	}

	/* Check channel numbers */
	for (i = 0; i < desc->num_channels; i++)
		if (desc->channels[i].channel > max_chan)
			return -EINVAL;

	return 0;
}


int mcp3208_read(struct _mcp3208_desc *desc, int channel, uint16_t* raw)
{
	volatile uint8_t hdr[] = { 0x04, 0x00, 0x00 };
	struct _buffer buf[] = {
		{
			.data = (uint8_t*)hdr,
			.size = 3,
			.attr = BUS_BUF_ATTR_TX | BUS_BUF_ATTR_RX | BUS_SPI_BUF_ATTR_RELEASE_CS,
		},
	};

	if (!raw)
		return -EINVAL;

	if (channel > desc->num_channels)
		return -EINVAL;

	switch (desc->channels[channel].mode) {
	case MCP3208_MODE_SINGLE_ENDED:
		hdr[0] |= 0x02;
		break;
	case MCP3208_MODE_DIFFERENTIAL:
		break;
	default:
		return -EINVAL;
	}

	if (desc->channels[channel].channel > 3)
		hdr[0] |= 0x01;
	hdr[1] = (desc->channels[channel].channel & 0x03) << 6;

	bus_start_transaction(desc->cfg.bus);
	bus_transfer(desc->cfg.bus, desc->cfg.spi_dev.chip_select, buf, 1, NULL);
	bus_stop_transaction(desc->cfg.bus);

	*raw = (((uint16_t)(hdr[1] & 0x0F)) << 8) | hdr[2];

	return 0;
}

int mcp3208_convert_to_mv(struct _mcp3208_desc *desc, uint16_t raw, uint16_t* mv)
{
	if (!mv)
		return -EINVAL;

	*mv = (uint16_t)(((uint32_t)raw * desc->vref) / 4096);
	return 0;
}
