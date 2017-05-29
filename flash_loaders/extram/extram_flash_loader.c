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

/** \addtogroup flash_flashloader Embedded Flash Flashloader
 *
 * It describes how to write and debug your own flash loader.
 * Finally, the flash loader framework API functions are described in detail.
 *
 * Related files :\n
 * \ref flashd.c\n
 * \ref flashd.h.\n
 * \ref efc.c\n
 * \ref efc.h.\n
*/
/*@{*/
/*@}*/


/**
 * \file
 *
 * The flash flashloader provides the embedded flash flashloader framework.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "flash_loader.h"
#include "flash_loader_extra.h"
#include "irqflags.h"
#include "irq/irq.h"
#include "peripherals/pmc.h"
#include "serial/console.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/* Debug enable/disable */
#define DEBUG

/*----------------------------------------------------------------------------
 *        Local Varible
 *----------------------------------------------------------------------------*/

static char message[80];

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/* override default board init */
void board_init(void)
{
	board_cfg_lowlevel(true, true, false);
	board_cfg_console(0);
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

	/* stop warning */
	base_of_flash = base_of_flash;
	image_size = image_size;
	link_address = link_address;
	flags = flags;

#ifdef DEBUG
	sprintf(message, "%s", "-I- External ram loader");
	cSpyMessageLog(message);
#endif

	if (!findOption( "--ddram", 0, argc, argv ))
		return RESULT_ERROR;

	board_init();

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
	uint32_t i;
	uint8_t* p1;
	uint8_t* p2;
#ifdef DEBUG
	sprintf(message, "-I- Write arguments: address 0x%08x,  offset 0x%x of 0x%x Bytes", (unsigned int)block_start, offset_into_block,count );
	cSpyMessageLog(message);
#endif


//	memcpy((uint8_t*)((uint32_t)block_start + offset_into_block), buffer, count);
	p1 = (uint8_t*)((uint32_t)block_start + offset_into_block);
	p2 = (uint8_t*)buffer;
	for (i = 0; i < count; i++)
		*p1++ = *p2++;

	//if (FLASHD_Write((unsigned int)block_start + offset_into_block, buffer, count) != 0) {
	sprintf(message, "-I- Write Done!");
	cSpyMessageLog(message);
	return RESULT_OK;
}

/**
 * \brief  Unlock the flash in giving address. (auto erased before program).
 *
 * \param block_start Address of the start of the flash memory block affected by the write operation.
 * \param block_size  The size of the block, in bytes.
 * \return 0 if successful; otherwise returns an error code.
 */
uint32_t FlashErase(void *block_start, uint32_t block_size)
{
#ifdef DEBUG
	sprintf(message, "-I- Erase arguments: address 0x%08x of 0x%x Bytes", (unsigned int)block_start, block_size);
	cSpyMessageLog(message);
#endif
	return RESULT_OK;
}

/**
 * \brief  UThis is an optional function. You can implement it if you need to perform
 * some cleanup after flash loading has finished.
 */
uint32_t FlashSignoff(void)
{
	return RESULT_OK;
}
