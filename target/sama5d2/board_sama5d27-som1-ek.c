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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "board.h"
#include "board_audio.h"
#include "board_can.h"
#include "board_console.h"
#include "board_eth.h"
#include "board_isc.h"
#include "board_lcd.h"
#include "board_led.h"
#include "board_spi.h"
#include "board_twi.h"
#include "compiler.h"

#include "dma/dma.h"
#include "board_support.h"

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

WEAK void board_init(void)
{
#ifdef VARIANT_DDRAM
	bool ddram = false;
#else
	bool ddram = true;
#endif

#ifdef VARIANT_SRAM
	bool clocks = true;
#else
	bool clocks = false;
#endif

	/* Configure misc low-level stuff */
	board_cfg_lowlevel(clocks, ddram, true);

	/* Configure console */
	board_cfg_console(0);

	/* DMA Driver init */
	dma_initialize(false);

#ifdef CONFIG_HAVE_SPI_BUS
	/* Configure SPI bus */
	board_cfg_spi_bus();
#endif

#ifdef CONFIG_HAVE_SPI_NOR
	/* Configure SPI NOR flash memory */
	board_cfg_spi_flash();
#endif

#ifdef CONFIG_HAVE_I2C_BUS
	/* Configure TWI bus */
	board_cfg_twi_bus();

#ifdef CONFIG_HAVE_TWI_AT24
	board_cfg_at24();
#endif
#endif

#ifdef CONFIG_HAVE_LED
	/* Configure LEDs */
	board_cfg_led();
#endif

#ifdef CONFIG_HAVE_ETH
	board_cfg_net(0, NULL, true);
#endif

#ifdef CONFIG_HAVE_LCDC
	/* Configure LCD controller/display */
	board_cfg_lcd();
#endif

#ifdef CONFIG_HAVE_ISC
	/* Configure camera interface */
	board_cfg_isc();
#endif

#ifdef CONFIG_HAVE_CAN_BUS
	/* Configure MCAN bus */
	board_cfg_can_bus();
#endif
}
