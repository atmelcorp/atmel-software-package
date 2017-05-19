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

#ifndef MCP3208_H_
#define MCP3208_H_

#include "peripherals/bus.h"
#include "spi/spid.h"

enum _mcp3208_model {
	MCP3208_MODEL_3204,
	MCP3208_MODEL_3208,
};

enum _mcp3208_mode {
	MCP3208_MODE_DIFFERENTIAL,
	MCP3208_MODE_SINGLE_ENDED,
};

struct _mcp3208_channel {
	uint8_t channel;
	enum _mcp3208_mode mode;
};

struct _mcp3208_desc {
	struct _bus_dev_cfg cfg;
	enum _mcp3208_model model;
	const struct _mcp3208_channel* channels;
	int num_channels;
	uint16_t vref;
};

int mcp3208_configure(struct _mcp3208_desc *desc);

int mcp3208_read(struct _mcp3208_desc *desc, int channel, uint16_t* value);

int mcp3208_convert_to_mv(struct _mcp3208_desc *desc, uint16_t raw, uint16_t* mv);

#endif /* ! MCP3208_H_ */
