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

enum _ram_type {
#ifdef CONFIG_HAVE_MPDDRC_SDRAM
	MPDDRC_TYPE_SDRAM,
#endif
#ifdef CONFIG_HAVE_MPDDRC_LPDDR
	MPDDRC_TYPE_LPDDR,
#endif
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

	struct {
		uint8_t tmrd;   /**< Load Mode Register Command to Activate or Refresh Command */
		uint8_t twtr;   /**< Internal Write to Read Delay */
		uint8_t trrd;   /**< Active BankA to Active BankB */
		uint8_t trp;    /**< Row Precharge Delay */
		uint8_t trc;    /**< Row Cycle Delay */
		uint8_t twr;    /**< Write Recovery Delay */
		uint8_t trcd;   /**< Row to Column Delay */
		uint8_t tras;   /**< Active to Precharge Delay */
		uint8_t txp;    /**< Exit Powerdown Delay to First Command */
		uint8_t txsrd;  /**< Exit Self-refresh Delay to Read Command */
		uint8_t txsnr;  /**< Exit Self-refresh Delay to Non-Read Command */
		uint8_t trfc;   /**< Row Cycle Delay */
		uint8_t tfaw;   /**< Four Active Windows */
		uint8_t trtp;   /**< Read to Precharge */
		uint8_t trpa;   /**< Row Precharge All Delay */
		uint8_t txards; /**< Exit Active Powerdown Delay to Read Command in Mode "Slow Exit" */
		uint8_t txard;  /**< Exit Active Powerdown Delay to Read Command in Mode "Fast Exit" */
	} timings;

	uint32_t refresh_window; /* in ms */
	uint32_t refresh_cycles;
};

RAMDATA extern struct pck_mck_cfg clock_setting_backup;
#ifdef CONFIG_RAMCODE
RAMDATA extern volatile int _ddr_active_needed;
#endif

extern void mpddrc_configure(struct _mpddrc_desc* desc);

/**
 * \brief Issue a Low-Power Command to the DDR-SDRAM device.
 *
 * \param cmd the Low-Power Command to send (one of the MPDDRC_LPR_LPCB_*
 * constants)
 */
extern void mpddrc_issue_low_power_command(uint32_t cmd);

void ddr_self_refresh(void);

void check_ddr_ready(void);

#ifdef CONFIG_RAMCODE
void ddram_active(void);
#endif
#endif
