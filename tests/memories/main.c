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
 *  \page sdram SDRAM example
 *
 *  \section Purpose
 *
 *  The SDRAM example will help new users get familiar with Atmel's
 *  samv7 family of micro-controllers. This basic application shows Shows how
 *  to initialize and perform read and write a SDRAM memory.
 *
 *  \section Requirements
 *
 *  This package can be used with SAM V71 Xplained Ultra board.
 *
 *  \section Description
 *
 *  \section Usage
 *
 *  -# Build the program and download it inside the SAM V71 Xplained Ultra board.
 *     Please refer to the Getting Started with SAM V71 Microcontrollers.pdf
 *  -# On the computer, open and configure a terminal application
 *     (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *    - 115200 baud rates
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# Start the application.
 *  -#In the terminal window, the
 *     following text should appear (values depend on the board and chip used):
 *     \code
 *      -- SDRAM Example xxx --
 *      -- xxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 *
 *  \section References
 *  - sdram/main.c
 *  - trace.h
 */

/** \file
 *
 *  This file contains all the specific code for the SDRAM example.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "board_memories.h"

#include "rand.h"
#include "peripherals/wdt.h"

#include "cortex-a/mmu.h"
#include "cortex-a/cp15.h"

#include "trace.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/* configure the SDRAM IO pins to use HIGH drive */
#undef SDRAM_HIGH_DRIVE

/* use memory barriers between write and read/compare */
#undef USE_BARRIERS

/* use memory barrier + cache clean/invalidate between write and read/compare */
#undef USE_CACHE_CLEAN_INV

/* read and compare written data */
#define READ_COMPARE

/* increase SRAM read margins */
#undef ADJUST_READ_MARGINS

/* size of the random data buffer */
#define BUFFER_SIZE (1024*8)

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static uint32_t random_buffer[BUFFER_SIZE];

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Test SDRAM access
 * \param baseAddr Base address of SDRAM
 * \param size  Size of memory in byte
 * \return 1: OK, 0: Error
 */
static uint32_t _sdram_access(uint32_t baseAddr, uint32_t size)
{
	int i, count;
	uint32_t offset, value;
	uint32_t *ptr = (uint32_t *)baseAddr;
	uint32_t ret = 1;

	for (offset = 0; offset < (size/4); offset += count) {
		count = (size/4) - offset;
		if (count > BUFFER_SIZE)
			count = BUFFER_SIZE;

		memcpy(ptr + offset, random_buffer, count*4);

		for (i = 0; i < count; i++) {
			value = ptr[offset + i];
			if (value != random_buffer[i]) {
				ret = 0;
			}
		}
	}

	return ret;
}

static void _sram_loop_test(uint32_t baseAddr, uint32_t size)
{
	int i;

	srand(0);
	while (1) {
		for (i = 0; i < BUFFER_SIZE; i++)
			random_buffer[i] = rand();
		if (_sdram_access(baseAddr, size)) {
			printf("_");
		}
		else {
			printf("F");
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

	board_cfg_ddram();

	/* Output example information */
	printf("\n\r-- SDRAM Example " SOFTPACK_VERSION " --\n\r"
	       "-- "BOARD_NAME "\n\r"
	       "-- Compiled: "__DATE__" at " __TIME__ "--\n\r");

	trace_info("Configuring External SDRAM \n\r");

	/* Full test SDRAM  */
	trace_info("Starting memory validation of External SDRAM \n\r");
	trace_info("Buffer: %u bytes at 0x%08x\r\n", BUFFER_SIZE*4,
		   (unsigned int)random_buffer);

	_sram_loop_test(DDR_CS_ADDR, 1024*1024*64);
	printf("goto sleep, good night\r\n");
	while(1);
}
