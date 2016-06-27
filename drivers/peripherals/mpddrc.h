/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
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

#ifndef MPDDRC_HEADER_
#define MPDDRC_HEADER_

#include <stdint.h>
#include <peripherals/mpddrc.h>

enum _ram_type {
#ifdef CONFIG_HAVE_MPDDRC_DDR2
	MPDDRC_TYPE_DDR2,
#endif
#ifdef CONFIG_HAVE_MPDDRC_LPDDR2
	MPDDRC_TYPE_LPDDR2,
#endif
#ifdef CONFIG_HAVE_MPDDRC_DDR3
	MPDDRC_TYPE_DDR3,
#endif
#ifdef CONFIG_HAVE_MPDDRC_LPDDR3
	MPDDRC_TYPE_LPDDR3,
#endif
};

struct _mpddrc_desc {
	enum _ram_type type;
#ifdef CONFIG_HAVE_MPDDRC_IO_CALIBRATION
	uint32_t io_calibr;
#endif
#ifdef CONFIG_HAVE_MPDDRC_DATA_PATH
	uint32_t data_path;
#endif
	uint32_t mode;
	uint32_t control;
	uint32_t bank;
	uint32_t tpr0;
	uint32_t tpr1;
	uint32_t tpr2;
};

extern void mpddrc_configure(struct _mpddrc_desc* desc, uint32_t tc_id, uint32_t tc_ch);

/**
 * \brief Issue a Low-Power Command to the DDR-SDRAM device.
 *
 * \param cmd the Low-Power Command to send (one of the MPDDRC_LPR_LPCB_*
 * constants)
 */
extern void mpddrc_issue_low_power_command(uint32_t cmd);

#endif
