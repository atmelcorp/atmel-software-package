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

/** \addtogroup qspi_flash_loader Embedded QSPI Flashloader
 *
 * It describes how to write and debug your own flash loader.
 * Finally, the flash loader framework API functions are described in detail.
 *
 * Related files :\n
 * \ref qspi_flash.c\n
*/
/*@{*/
/*@}*/


/**
 * \file
 *
 * The QSPI flashloader provides the embedded QSPI flashloader framework.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <board.h>
#include <chip.h>
#include "trace.h"

#include "gpio/pio.h"
#include "nvm/spi-nor/qspiflash.h"

#include "interface.h"
#include "flash_loader.h"
#include "flash_loader_extra.h"

#include "pin_defs.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/
/* Software version */
#define VERSION "1.0"

/*----------------------------------------------------------------------------
 *        Local Varible
 *----------------------------------------------------------------------------*/
static int8_t SectorErased[0x200000 / (64* 1024)];
static uint32_t sizeTobeWritten;
static uint32_t sizeWritten;

/** QSPI serial flash instance. */
static struct _qspiflash flash;

static uint32_t base_address;

uint32_t instance;
uint32_t ioset;
uint32_t freq;

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static bool configure_instance_pio(uint32_t instance, uint32_t ioset, Qspi** addr)
{
	int i;
	for (i = 0; i < num_qspiflash_pin_defs; i++) {
		const struct qspiflash_pin_definition* def =
			&qspiflash_pin_defs[i];
		if (def->instance == instance && def->ioset == ioset) {
			*addr = def->addr;
			pio_configure(def->pins, def->num_pins);
			return true;
		}
	}

	trace_error_wp("Invalid configuration: QSPI%u IOSet%u\r\n",
		(unsigned)instance, (unsigned)ioset);
	return false;
}

/* override default board init */
void board_init(void)
{
	board_cfg_lowlevel(true, true, false);
	board_cfg_console(0);
	/* DMA Driver init */
	dma_initialize(true);
}

/*----------------------------------------------------------------------------
 *        Export functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Initializes the flash driver.
 *
 * \param base_of_flash  base address of flash memory.
 * \param image_size The size of the whole image that is to be written in bytes.
 * \param link_address The original link address of the first byte of the image.
 * \param flags Contains optional flags.
 * \param  argc Number of arguments.
 * \param  An array of argument string pointers.
 * \return 0 if successful; otherwise returns an error code.
 */
uint32_t FlashInit(void *base_of_flash,
				   uint32_t image_size,
				   uint32_t link_address,
				   uint32_t flags,
				   int argc,
				   char const *argv[])

{
	uint32_t i;
	const char *arg;
	Qspi* addr;

	base_address = (uint32_t)base_of_flash;
	sizeTobeWritten = image_size;
	/* stop warning */
	link_address = link_address;
	flags = flags;
	
	board_init();
	matrix_remap_ram();

	for (i = 0; i < (0x200000 / (64*1024)); i++)
		SectorErased[i] = 0;

	/* Disable all PIO interrupts */
	pio_reset_all_it();

	printf("\n\r-I- QSPI flash loader, filesize 0x%x\n\r", sizeTobeWritten);
	arg = findOption("--instance", 1, argc, argv);
	instance = strtoul(arg, 0, 0);

	arg = findOption("--ioset", 1,argc, argv);
	ioset = strtoul(arg, 0, 0);

	arg = findOption("--freq", 1, argc, argv);
	freq = strtoul(arg, 0, 0);

	uint32_t max_freq = pmc_get_peripheral_clock(ID_QSPI0);
	if (freq == 0 || (freq * 1000000) > max_freq) {
		trace_error_wp("Invalid configuration: frequency must be " \
				"between 1 and %uHz (requested %uHz)\r\n",
				(unsigned)max_freq, (unsigned)freq * 1000000);
		return RESULT_ERROR;
	}

	if (!configure_instance_pio(instance, ioset, &addr))
		return RESULT_ERROR;

	trace_debug("Initialize QSPI drivers...\n\r");
	qspi_initialize(addr);
	trace_debug("QSPI drivers initialized.\n\r");

	(void)qspi_set_baudrate(addr, freq * 1000000);

	trace_debug("Configure QSPI Flash...\n\r");
	int rc = qspiflash_configure(&flash, addr);
	if (rc < 0) {
		trace_debug("Configure QSPI Flash failed!\n\r");
		return rc;
	}
	if (!flash.desc->jedec_id) {
		trace_debug("Device Unknown\r\n");
		return RESULT_ERROR;
	}
	trace_debug("QSPI Flash configured.\n\r");

	sizeWritten = 0;
	return RESULT_OK;
}

/**
 * \brief Writes a data buffer in the internal flash.
 *
 * \param block_start  address of the start of the flash memory block affected by the write operation.
 * \param offset_into_block  How far into the current block that this write operation shall start.
 * \param count  Size of data buffer in bytes.
 * \param buffer Points to the buffer containing the bytes to write.
 * \return 0 if successful; otherwise returns an error code.
 */

uint32_t FlashWrite(void *block_start, uint32_t offset_into_block, uint32_t count, char const *buffer)
{
  	printf("-I- Write arguments: address 0x%08x,  offset 0x%x of 0x%x Bytes\n\r",
		(uint32_t)block_start, offset_into_block, count);
	if (qspiflash_write(&flash, (uint32_t)block_start + offset_into_block - base_address, buffer, count) < 0)
	{
	// Write data
		printf("-E- Failed to write!\n\r");
		return RESULT_ERROR;
	}

	sizeWritten+= count;
	if (sizeWritten >= sizeTobeWritten) {
		printf("-I- Enter to XIP mode!\n\r");
		/* Start continuous read mode to enter in XIP mode*/
		if (qspiflash_read(&flash, 0, NULL, 0) < 0) {
			trace_debug("Read the code from QSPI Flash failed!\n\r");
			return RESULT_ERROR;
		}
	}
	printf("-I- Write Done!\n\r");
	return RESULT_OK;
}

/**
 * \brief  erase the flash in giving address. (auto erased before program).
 *
 * \param block_start Address of the start of the flash memory block affected by the write operation.
 * \param block_size  The size of the block, in bytes.
 * \return 0 if successful; otherwise returns an error code.
 */
uint32_t FlashErase(void *block_start, uint32_t block_size)
{
	uint32_t id;
	uint32_t startAddr;

	printf("-I- Erase arguments: address 0x%08x of 0x%x Bytes\n\r",
		(uint32_t)block_start, block_size);

	id = ((uint32_t)block_start - base_address) / block_size;
	if (SectorErased[id] == 0) {
		startAddr = id * block_size;
		qspiflash_erase_block(&flash, startAddr, block_size);
		printf("-I- Erase Done!\n\r");
		SectorErased[id] = 1;
	}

	return RESULT_OK;
}


/**
 * \brief  UThis is an optional function. You can implement it if you need to perform
 * some cleanup after flash loading has finished.
 */
uint32_t FlashSignoff()
{
	return RESULT_OK;
}
