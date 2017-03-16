/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, Atmel Corporation
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
 *  \page ddram DDRAM example
 *
 *  \section Purpose
 *
 *  The DDRAM example will help new users get familiar with Atmel's
 *  SAMA5 family of micro-controllers. This basic application shows Shows how
 *  to initialize and perform read and write a DDRAM memory.
 *
 */

/** \file
 *
 *  This file contains all the specific code for the DDRAM example.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "board.h"
#include "board_console.h"
#include "mm/l1cache.h"
#include "rand.h"
#include "serial/console.h"
#include "timer.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/* size of the random data buffer (in bytes) */
#define BUFFER_SIZE (4096)

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static uint8_t random_buffer[BUFFER_SIZE];

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Test DDRAM access
 * \param baseAddr Base address of DDRAM
 * \param size  Size of memory in bytes
 * \return 1: OK, 0: Error
 */
static bool _ddram_access(uint32_t baseAddr, uint32_t size)
{
	uint32_t offset, count;
	uint8_t *ptr = (uint8_t*)baseAddr;
	int percent, percent_old;

	percent_old = -1;
	for (offset = 0; offset < size; offset += count) {
		count = BUFFER_SIZE;
		if (count > (size - offset))
			count = size - offset;

		memcpy(ptr + offset, random_buffer, count);

		if (memcmp(ptr + offset, random_buffer, count)) {
			printf("Error in range 0x%x-0x%x\r\n", (unsigned)(ptr + offset),
					(unsigned)(ptr + offset + count));
			return false;
		}

		percent =  offset / (size / 100);
		if (percent != percent_old) {
			percent_old = percent;
			printf("%d%%\r", percent);
		}
	}

	return true;
}

static void _ddram_test_loop(uint32_t baseAddr, uint32_t size)
{
	int i, passed, failed;
	uint64_t start, end;
	bool ok;

	passed = 0;
	failed = 0;
	while (1) {
		for (i = 0; i < BUFFER_SIZE/4; i++)
			((uint32_t*)random_buffer)[i] = rand();

		start = timer_get_tick();
		ok = _ddram_access(baseAddr, size);
		end = timer_get_tick();

		if (ok) {
			passed++;
			printf("Test Passed (passed=%d, failed=%d) (%ums)\r\n",
					passed, failed, (unsigned)(end - start));
		} else {
			failed++;
			printf("Test Failed (passed=%d, failed=%d) (%ums)\r\n",
					passed, failed, (unsigned)(end - start));
		}
	}
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void board_init(void)
{
	/* Configure misc low-level stuff */
	board_cfg_lowlevel(true, true, false);
	icache_enable();

	/* Configure console */
	board_cfg_console(0);
}

/**
 *  \brief getting-started Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	srand(0);

	/* Output example information */
	console_example_info("DDRAM Example");

	/* Full test DDRAM  */
	trace_info("Starting memory validation of External DDRAM (%u MB)\n\r",
	           (unsigned)(BOARD_DDR_MEMORY_SIZE/(1024*1024)));
	trace_info("Buffer: %u bytes at 0x%08x\r\n", BUFFER_SIZE,
	           (unsigned)random_buffer);

	_ddram_test_loop(DDR_CS_ADDR, BOARD_DDR_MEMORY_SIZE);
	return 0;
}
