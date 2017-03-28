/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016-2017, Atmel Corporation
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

#include "applet.h"
#include "bootconfig.h"
#include "chip.h"
#include "nvm/flash/flashd.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#define BOOTCFG_SECURITY  0
#define BOOTCFG_BOOTMODE  1
#define BOOTCFG_TCM       2

/*----------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

static struct _flash flash;

/*----------------------------------------------------------------------------
 *         Public functions
 *----------------------------------------------------------------------------*/

int bootcfg_initialize(void)
{
	return flashd_initialize(&flash, EEFC);
}

int bootcfg_print(uint32_t index, uint32_t value)
{
	switch (index) {
	case BOOTCFG_SECURITY:
		trace_warning_wp("Security Bit: ");
		switch (value) {
		case 0:
			trace_warning_wp("Disabled");
			break;
		case 1:
			trace_warning_wp("Enabled");
			break;
		default:
			trace_warning_wp("Invalid value!");
			break;
		}
		trace_warning_wp("\r\n");
		break;
	case BOOTCFG_BOOTMODE:
		trace_warning_wp("Boot Mode: ");
		switch (value) {
		case 0:
			trace_warning_wp("ROM (SAM-BA monitor)");
			break;
		case 1:
			trace_warning_wp("Flash");
			break;
		default:
			trace_warning_wp("Invalid value!");
			break;
		}
		trace_warning_wp("\r\n");
		break;
	case BOOTCFG_TCM:
		trace_warning_wp("TCM Configuration: ");
		switch (value) {
		case 0:
			trace_warning_wp("0 Kbytes DTCM + 0 Kbytes ITCM");
			break;
		case 1:
			trace_warning_wp("32 Kbytes DTCM + 32 Kbytes ITCM");
			break;
		case 2:
			trace_warning_wp("64 Kbytes DTCM + 64 Kbytes ITCM");
			break;
		case 3:
			trace_warning_wp("128 Kbytes DTCM + 128 Kbytes ITCM");
			break;
		default:
			trace_warning_wp("Invalid value!");
			break;
		}
		trace_warning_wp("\r\n");
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

int bootcfg_read(uint32_t index, uint32_t* value)
{
	switch (index) {
	case BOOTCFG_SECURITY:
		return flashd_get_gpnvm_bits(&flash, 0, 0, value);
	case BOOTCFG_BOOTMODE:
		return flashd_get_gpnvm_bits(&flash, 1, 1, value);
	case BOOTCFG_TCM:
		return flashd_get_gpnvm_bits(&flash, 7, 8, value);
	default:
		return -EINVAL;
	}

	return 0;
}

int bootcfg_write(uint32_t index, uint32_t value)
{
	switch (index) {
	case BOOTCFG_SECURITY:
		/* setting security bit to 0 is not possible */
		switch (value) {
		case 1:
			return flashd_set_gpnvm_bits(&flash, 0, 0, value);
		default:
			return -EINVAL;
		}
		break;
	case BOOTCFG_BOOTMODE:
		switch (value) {
		case 0:
		case 1:
			return flashd_set_gpnvm_bits(&flash, 1, 1, value);
		default:
			return -EINVAL;
		}
		break;
	case BOOTCFG_TCM:
		if (value <= 3)
			return flashd_set_gpnvm_bits(&flash, 7, 8, value);
		else
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
