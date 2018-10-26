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

#include "interface.h"
#include "flash_loader.h"
#include "flash_loader_extra.h"
#include "board_spi.h"
#include "board_console.h"
#include "dma/dma.h"
#include "gpio/pio.h"
#include "nvm/spi-nor/spi-nor.h"
#include "pin_config.h"
#include "peripherals/matrix.h"
#include "peripherals/pmc.h"
#include "spi/qspi.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local Varible
 *----------------------------------------------------------------------------*/
 
static struct spi_flash_cfg _flash_cfg = {
	.type = SPI_FLASH_TYPE_QSPI,
	.mode = SPI_FLASH_MODE0,
};

static struct spi_flash flash;

static uint32_t base_address;

static uint32_t instance;
#if defined (CONFIG_SOC_SAMA5D2)
static uint32_t ioset;
#endif
static uint32_t freq;
static uint32_t image_size;
static uint32_t erase_support;
static uint32_t size_written;
static uint32_t erase_support;

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

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
 * \param size The size of the whole image that is to be written in bytes.
 * \param link_address The original link address of the first byte of the image.
 * \param flags Contains optional flags.
 * \param  argc Number of arguments.
 * \param  An array of argument string pointers.
 * \return 0 if successful; otherwise returns an error code.
 */
uint32_t FlashInit(void *base_of_flash,
				   uint32_t size,
				   uint32_t link_address,
				   uint32_t flags,
				   int argc,
				   char const *argv[])

{
	const char *arg;
	Qspi* addr;

	base_address = (uint32_t)base_of_flash;
	image_size = size;
	
	link_address = link_address;
	flags = flags;

	board_init();
	matrix_remap_ram();

	/* Disable all PIO interrupts */
	pio_reset_all_it();

	trace_info_wp("\n\rQSPI flash loader, filesize 0x%x\n\r", image_size);
	arg = findOption("--instance", 1, argc, argv);
	instance = strtoul(arg, 0, 0);

	arg = findOption("--freq", 1, argc, argv);
	freq = strtoul(arg, 0, 0);

#if defined (CONFIG_SOC_SAMA5D2)
	arg = findOption("--ioset", 1,argc, argv);
	ioset = strtoul(arg, 0, 0);

	uint32_t max_freq = pmc_get_peripheral_clock(ID_QSPI0);
	if (freq == 0 || (freq * 1000000) > max_freq) {
		trace_error_wp("Invalid configuration: frequency must be " \
				"between 1 and %uHz (requested %uHz)\r\n",
				(unsigned)max_freq, (unsigned)freq * 1000000);
		return RESULT_ERROR;
	}
#endif

#if defined (CONFIG_SOC_SAMA5D2)
	if (!qspi_pio_configure(instance, ioset, &addr))
		return RESULT_ERROR;

	trace_warning_wp("Initializing QSPI%u IOSet%u at %uHz\r\n",
			(unsigned)instance, (unsigned)ioset,
			(unsigned)freq);
#elif defined (CONFIG_SOC_SAM9X60)
	if (!qspi_pio_configure(instance, &addr))
		return RESULT_ERROR;

	trace_warning_wp("Initializing QSPI%u at %uMHz\r\n",
			(unsigned)instance, (unsigned)freq);
#endif

	/* initialize the QSPI */
	_flash_cfg.qspi.addr = addr;
	_flash_cfg.baudrate = freq * 1000000;

	if (spi_nor_configure(&flash, &_flash_cfg) < 0) {
		trace_warning_wp("Error while detecting QSPI flash chip\r\n");
		return RESULT_ERROR;
	}

	uint32_t page_size = flash.page_size;
	uint32_t mem_size = flash.size;

	trace_warning_wp("Found Device %s\r\n", flash.name);
	trace_warning_wp("Size: %u bytes\r\n", (unsigned)mem_size);
	trace_warning_wp("Page Size: %u bytes\r\n", (unsigned)page_size);

	erase_support = spi_flash_get_uniform_erase_map(&flash);

	trace_warning_wp("QSPI Flash configured %d.\n\r",erase_support);
	size_written = 0;
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
	void* qspi_mem_addr = get_qspi_mem_from_addr(flash.priv.qspi.addr);

	trace_info_wp("Write arguments: address 0x%08x,  offset 0x%x of 0x%x Bytes\n\r",
		(uint32_t)block_start, offset_into_block, count);

	/* perform the write operation */
	if (spi_nor_write(&flash, (uint32_t)block_start + offset_into_block 
		- base_address, buffer, count) < 0) {
		trace_error("Write error\r\n");
		return RESULT_ERROR;
	}
	
	size_written+= count;
	if (size_written >= image_size) {
		trace_warning_wp("Enter to XIP mode!\n\r");
		/* Start continuous read mode to enter in XIP mode*/
		if (qspi_xip(&flash, qspi_mem_addr) < 0) {
			trace_error("Read the code from QSPI Flash failed!\n\r");
			return RESULT_ERROR;
		}
	}
	trace_warning_wp("Write Done!\n\r");
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
	uint32_t offset = (uint32_t)block_start;

	trace_info_wp("Erase arguments: offset 0x%08x,  size 0x%x Bytes %x\n\r",
		offset, block_size, erase_support);

	if ((erase_support & (block_size / flash.page_size)) == 0) {
		trace_error("Memory does not support requested erase size "
				"%u bytes\r\n", (unsigned)block_size);
		return RESULT_ERROR;
	}
	
	if (offset & (block_size - 1)) {
		trace_error("Unaligned erase offset: 0x%08x (erase size "
				"%u bytes)\r\n", (unsigned)offset,
				(unsigned)block_size);
		return RESULT_ERROR;
	}

	if (spi_nor_erase(&flash, offset, block_size) < 0) {
		trace_error("Erase failed at offset 0x%lx\r\n", offset);
		return RESULT_ERROR;
	}

	trace_info_wp("Erased %u bytes at 0x%08x\r\n",
			(unsigned)block_size, (unsigned)offset);
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
