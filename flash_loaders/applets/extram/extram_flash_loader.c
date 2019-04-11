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

#include <board.h>
#include "board_console.h"
#include "extram/ddram.h"
#include "flash_loader.h"
#include "flash_loader_extra.h"
#include "gpio/pio.h"
#include "interface.h"
#include "irqflags.h"
#include "irq/irq.h"
#include "peripherals/pmc.h"
#include "trace.h"

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
	board_cfg_lowlevel(true, false, false);
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
	enum _ddram_devices device;
	struct _mpddrc_desc desc;
	const char *arg;
	uint32_t preset;

	/* stop warning */
	base_of_flash = base_of_flash;
	image_size = image_size;
	link_address = link_address;
	flags = flags;

#ifdef DEBUG
	sprintf(message, "%s", "-I- External ram loader");
	cSpyMessageLog(message);
#endif

	arg = findOption("--preset", 1, argc, argv);
	preset = strtoul(arg, 0, 0);

	board_init();

	switch (preset) {
#ifdef CONFIG_HAVE_DDR2_MT47H128M8
	case 0:
		trace_warning_wp("Preset 0 (4 x MT47H128M8)\r\n");
		device = MT47H128M8;
		break;
#endif
#ifdef CONFIG_HAVE_DDR2_MT47H64M16
	case 1:
		trace_warning_wp("Preset 1 (MT47H64M16)\r\n");
		device = MT47H64M16;
		break;
#endif
#ifdef CONFIG_HAVE_DDR2_MT47H128M16
	case 2:
		trace_warning_wp("Preset 2 (2 x MT47H128M16)\r\n");
		device = MT47H128M16;
		break;
#endif
#ifdef CONFIG_HAVE_LPDDR2_MT42L128M16
	case 3:
		trace_warning_wp("Preset 3 (2 x MT42L128M16)\r\n");
		device = MT42L128M16;
		break;
#endif
#ifdef CONFIG_HAVE_DDR3_MT41K128M16
	case 4:
		trace_warning_wp("Preset 4 (2 x MT41K128M16)\r\n");
		device = MT41K128M16;
		break;
	case 12:
		trace_warning_wp("Preset 12 (1 x MT41K128M16)\r\n");
		device = MT41K128M16_16;
		break;
#endif
#ifdef CONFIG_HAVE_LPDDR3_EDF8164A3MA
	case 5:
		trace_warning_wp("Preset 5 (EDF8164A3MA)\r\n");
		device = EDF8164A3MA;
		break;
#endif
#ifdef CONFIG_HAVE_SDRAM_IS42S16100E
	case 6:
		trace_warning_wp("Preset 6 (IS42S16100E)\r\n");

		sprintf(message, "%s", "Preset 6 (IS42S16100E)\r\n");
	cSpyMessageLog(message);

		device = IS42S16100E;
		break;
#endif
#ifdef CONFIG_HAVE_SDRAM_W981216BH
	case 7:
		trace_warning_wp("Preset 7 (W981216BH)\r\n");
		device = W981216BH;
		break;
#endif
#ifdef CONFIG_HAVE_DDR2_W971GG6SB
	case 8:
		trace_warning_wp("Preset 8 (W971GG6SB)\r\n");
		device = W971GG6SB;
		break;
#endif
#ifdef CONFIG_HAVE_DDR2_W972GG6KB
	case 9:
		trace_warning_wp("Preset 9 (W972GG6KB)\r\n");
		device = W972GG6KB;
		break;
	case 11:
		trace_warning_wp("Preset 11 (W972GG6KB_16)\r\n");
		device = W972GG6KB_16;
		break;
#endif

#ifdef CONFIG_HAVE_DDR2_W9712G6KB
	case 15:
		trace_warning_wp("Preset 15 (W9712G6KB)\r\n");
		device = W9712G6KB;
		break;
#endif
#ifdef CONFIG_HAVE_DDR2_W9751G6KB
	case 16:
		trace_warning_wp("Preset 16 (W9751G6KB)\r\n");
		device = W9751G6KB;
		break;
#endif

#ifdef CONFIG_HAVE_SDRAM_AS4C16M16SA
	case 10:
		printf("Preset 10 (AS4C16M16SA)\r\n");
		device = AS4C16M16SA;
		break;
#endif
#ifdef CONFIG_HAVE_LPDDR2_AD220032D
	case 13:
		trace_warning_wp("Preset 13 (AD220032D)\r\n");
		device = AD220032D;
		break;
#endif
#ifdef CONFIG_HAVE_LPDDR2_AD210032D
	case 14:
		trace_warning_wp("Preset 14 (AD210032D)\r\n");
		device = AD210032D;
		break;
#endif
	default:
		trace_warning_wp("Unsupported DRAM preset (%u).\r\n",
				(unsigned)preset);
		return false;
	}
#ifdef BOARD_DDRAM_PINS
	const struct _pin ddram_pins[] = BOARD_DDRAM_PINS;
	pio_configure(ddram_pins, ARRAY_SIZE(ddram_pins));
#endif
	board_cfg_matrix_for_ddr();
	ddram_init_descriptor(&desc, device);
	ddram_configure(&desc);
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

	p1 = (uint8_t*)((uint32_t)block_start + offset_into_block);
	p2 = (uint8_t*)buffer;
	for (i = 0; i < count; i++)
		*p1++ = *p2++;

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
