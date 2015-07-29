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

/*------------------------------------------------------------------------------
 *        Header
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"

#include "peripherals/aic.h"
#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/qspi.h"
#include "peripherals/trng.h"
#include "peripherals/wdt.h"

#include "memories/qspiflash.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static struct _pin pins_qspi[] = QSPIFLASH_PINS;


/*------------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------*/

void display_qspi_info (struct _qspiflash *pflash)
{
	printf ("\t- Name             : %s \n\r", pflash->desc.name);
	printf ("\t- Jedec ID         : 0x%4X \n\r", pflash->desc.jedec_id);
	printf ("\t- Num Block        : %d \n\r", pflash->desc.num_blocks);
	printf ("\t- Block Size       : %d \n\r", pflash->desc.block_size);
	printf ("\t- Page Size        : %d \n\r", pflash->desc.page_size);
	printf ("\t- Num Mode Cycles  : %d \n\r", pflash->desc.num_mode_cycles);
	printf ("\t- Num Dummy Cycles : %d \n\r", pflash->desc.num_dummy_cycles);
	printf ("\t- Normal Read Mode : %d \n\r", pflash->desc.normal_read_mode);
	printf ("\t- Continu.Read Mode: %d \n\r", pflash->desc.continuous_read_mode);
	printf ("\t- Features         : %d \n\r", pflash->desc.features);
}


uint8_t test_qspi_flash (void)
{
	uint8_t status = 0;

	pio_configure(pins_qspi, ARRAY_SIZE(pins_qspi));
	qspi_initialize(QSPIFLASH_ADDR);
	qspi_set_baudrate(QSPIFLASH_ADDR, QSPIFLASH_BAUDRATE);

	struct _qspiflash flash;
	/* return 1 of found */
	status = qspiflash_configure(&flash, QSPIFLASH_ADDR);
	if(status) {
		display_qspi_info(&flash);
		return 0;
	}
	return 1;
}
