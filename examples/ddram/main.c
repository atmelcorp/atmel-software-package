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

#include "board.h"

#include "rand.h"
#include "trace.h"

#include "cortex-a/mmu.h"
#include "cortex-a/cp15.h"

#include "peripherals/wdt.h"
#include "peripherals/l2cc.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/* size of the random data buffer (in uint32_t)*/
#define BUFFER_SIZE (1024*8)

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static uint32_t random_buffer[BUFFER_SIZE];

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Test DDRAM access
 * \param baseAddr Base address of DDRAM
 * \param size  Size of memory in byte
 * \return 1: OK, 0: Error
 */
static uint32_t _ddram_access(uint32_t baseAddr, uint32_t size)
{
	int i, count;
	uint32_t offset, value;
	uint32_t *ptr = (uint32_t *)baseAddr;
	uint32_t ret = 1;
	int percent, percent_old;

	percent_old = -1;
	for (offset = 0; offset < (size/4); offset += count) {
		count = (size/4) - offset;
		if (count > BUFFER_SIZE)
			count = BUFFER_SIZE;

		memcpy(ptr + offset, random_buffer, count*4);
		l2cc_clean_region((uint32_t)(ptr + offset), (uint32_t)(ptr + offset + count));
		l2cc_invalidate_region((uint32_t)(ptr + offset), (uint32_t)(ptr + offset + count));

		for (i = 0; i < count; i++) {
			value = ptr[offset + i];
			if (value != random_buffer[i]) {
				ret = 0;
			}
		}

		percent =  offset / (size / (4 * 100));
		if (percent != percent_old) {
			percent_old = percent;
			printf("%d%%\r", percent);
		}
	}

	return ret;
}

static void _ddram_test_loop(uint32_t baseAddr, uint32_t size)
{
	int i, passed, failed;

	passed = 0;
	failed = 0;
	while (1) {
		for (i = 0; i < BUFFER_SIZE; i++)
			random_buffer[i] = rand();

		if (_ddram_access(baseAddr, size)) {
			passed++;
			printf("Test Passed (passed=%d, failed=%d)\r\n", passed, failed);
		} else {
			failed++;
			printf("Test Failed (passed=%d, failed=%d)\r\n", passed, failed);
		}
	}
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/**
 *  \brief getting-started Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Disable watchdog */
	wdt_disable();

	/* Configure console */
	board_cfg_console();

	srand(0);

	/* Output example information */
	printf("\n\r-- DDRAM Example " SOFTPACK_VERSION " --\n\r"
	       "-- "BOARD_NAME "\n\r"
	       "-- Compiled: "__DATE__" at " __TIME__ "--\n\r");

#ifndef VARIANT_DDRAM
	trace_info("Configuring External DDRAM \n\r");
	board_cfg_ddram();
#endif

	/* Full test DDRAM  */
	trace_info("Starting memory validation of External DDRAM \n\r");
	trace_info("Buffer: %u bytes at 0x%08x\r\n", BUFFER_SIZE*4,
		   (unsigned int)random_buffer);

	_ddram_test_loop(DDR_CS_ADDR, BOARD_DDR_MEMORY_SIZE);
	return 0;
}
