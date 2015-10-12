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

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include "board.h"
#include "chip.h"

#include "cortex-a/cp15.h"
#include "board_memories.h"

#include "peripherals/wdt.h"
#include "peripherals/pmc.h"
#include "peripherals/aic.h"
#include "peripherals/pio.h"

#include "power/act8945a.h"

#include "peripherals/twi.h"
#include "peripherals/twid.h"
#include "memories/at24.h"
#include "test_at24mac402.h"

#include "board_info.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

extern struct _act8945a act8945a;

struct _stResult
{
	uint8_t	result ;
	char	string[48];
} ;

/* VBUS pin */
static const struct _pin vbus_pin[] = PIN_USB_VBUS;
static const struct _pin en5v_usbb_pin[] = PIN_USB_POWER_ENB;


/*------------------------------------------------------------------------------
 *        External Functions used for tests
 *----------------------------------------------------------------------------*/

extern uint8_t display_info_mpu (void);
extern void display_boot_register (void);
extern uint8_t test_at24mac402 (void);
extern uint8_t test_ddr_sdram(uint32_t* addr_start, uint32_t* addr_end, uint64_t nBytes);
extern uint8_t test_spi_flash (void);
extern uint8_t test_qspi_flash (void);
extern uint8_t test_lcd (void);
extern uint8_t test_geth (uint8_t bypass_exchange);

/*------------------------------------------------------------------------------
 *        Functions
 *----------------------------------------------------------------------------*/

/**
 *  Interrupt handler VBUS pin.
 */
static void vbus_change_handler(uint32_t mask, uint32_t status, void* user_arg)
{
	uint8_t state = pio_get(&vbus_pin[0]);
	(void)user_arg;
	printf("\n\r--I-- Switching power mode USB:%1x %s\n\r", state, (state)?"connected" : "disconnected");
}

/**
 *  Configure pin VBus change state
 */
static void configure_pin_vbus_state(void)
{
	/* Configure Pio and interrupt (both edge)*/
	pio_configure(&vbus_pin[0], 1);
	pio_set_debounce_filter(&vbus_pin[0], 10);
	pio_configure_it(&vbus_pin[0]);
	pio_add_handler_to_group(vbus_pin[0].group, vbus_pin[0].mask,
		vbus_change_handler, NULL);
	pio_enable_it(&vbus_pin[0]);

}

static uint8_t get_vbus_pin_state (void)
{
	return pio_get(&vbus_pin[0]);
}


static void _display_driver_info (const char* str1,
				  const char* str2,
				  const char* str3)
{
	printf(" Device   : %s\n\r", str1);
	printf(" Interface: %s\n\r", str2);
	printf(" Comment  : %s\n\r", str3);
}

uint8_t check_hw_on_board (void)
{
	uint32_t size, board_pll, board_mck, proc_clk;
	uint8_t i, index, sum;
	struct _stResult sresult[16];

	index = 0;

	/* Output information */
	printf("\n\r");
	printf("  ======================================\n\r");
	printf("-- Hardware test %s --\n\r", SOFTPACK_VERSION);
	printf("-- Board name: %s -- \n\r",BOARD_NAME);
	printf("-- Compiled: %s %s -- \n\r", __DATE__, __TIME__);
	printf("-- Using SDRAM DDR3L \n\r");
	printf("  ======================================\n\r");

	printf("--CONSOLE\n\r");
	printf(" UART1, Bdr=57600\n\r");
	sresult[index].result = 0;
	strcpy (sresult[index++].string, "CONSOLE\t\t");

	//printf("\n\r");
	printf("--MPU\n\r");
	sresult[index].result = display_info_mpu();
	strcpy (sresult[index++].string, "MPU\t\t");

	//printf("\n\r");
	printf(" -MPU FREQ\n\r");
	board_mck = pmc_get_master_clock();
	board_pll = pmc_get_plla_clock();
	proc_clk = pmc_get_processor_clock();
	printf(" Osc      : %dMHz \n\r", (int)BOARD_MAIN_CLOCK_EXT_OSC/1000000);
	printf(" Plla clk : %dMHz\n\r", (int)board_mck/1000000);
	printf(" Proc clk : %dMHz\n\r", (int)proc_clk/1000000);
	printf(" Check PCK: %03dMHz\n\r", (int)board_pll/1000000);

	//printf("\n\r");
	printf(" -BOOT MODE\n\r");
	display_boot_register();

	/* Configure VBUS pin */
	printf("--VBUS Pin\n\r");
	configure_pin_vbus_state();
	/* Configure ENABLE 5V USB pin output to 0*/
	pio_configure(en5v_usbb_pin, ARRAY_SIZE(en5v_usbb_pin));
	pio_clear(en5v_usbb_pin);

#ifdef ACT8945A
	//printf("\n\r");
	printf("--PMIC \n\r");
	_display_driver_info(PMIC_DEVICE, PMIC_INTERFACE, PMIC_COMMENT);
	if (act8945a.sys0) {
		act8945a_display_voltage_settings(&act8945a);
		sresult[index].result = 0;
	}
	else {
		printf("--E-- ByPass display config\n\r");
		sresult[index].result = 1;
	}
	strcpy (sresult[index++].string, "PMIC\t\t");

#endif

#ifdef AT24MAC402
	//printf("\n\r");
	printf("--EEP \n\r");
	_display_driver_info (EEP_DEVICE, EEP_INTERFACE, EEP_COMMENT);
	sresult[index].result = test_at24mac402();
	strcpy (sresult[index++].string, "EEP\t\t");
#endif

#ifdef EMMC
	//printf("\n\r");
	printf("--eMMC\n\r");
	_display_driver_info (EMMC_DEVICE, EMMC_INTERFACE, EMMC_COMMENT);
	sresult[index].result = 0;
	strcpy (sresult[index++].string, "EMMC\t\t");
#endif

#ifdef SDRAM_DDR2
	//printf("\n\r");
	printf("--SDRAM DDR2\n\r");
	_display_driver_info (DDR2_DEVICE, DDR2_INTERFACE, DDR2_COMMENT);
	printf(" Add Start/End : 0x%08x - 0x%08x  \n\r", ADDR_DDR2_START, ADDR_DDR2_END) ;
	Result = BOARD_DDRAM_SIZE/1024/1024;
	printf(" Total Size    : %dMb .. %dGB \n\r", (int)Result, (int)Result/128);
	sresult[index].result = 0;
	strcpy (sresult[index++].string, "SDRAM DDR2\t");
#endif

#ifdef SDRAM_DDR3
	//printf("\n\r");
	printf("--SDRAM DDR3\n\r");
	_display_driver_info (DDR3_DEVICE, DDR3_INTERFACE, DDR3_COMMENT);
	size = BOARD_DDRAM_SIZE/1024/1024;
	printf(" Total Size    : %dMb .. %dGB \n\r", (int)size, (int)size/128);
	sresult[index].result = test_ddr_sdram ((uint32_t*)ADDR_DDR3_START,
											(uint32_t*)ADDR_DDR3_END,
											(uint64_t)(ADDR_DDR3_END-ADDR_DDR3_START)/512);
	strcpy (sresult[index++].string, "SDRAM DDR3\t");

/*
	#ifndef VARIANT_DDRAM
		board_cfg_ddram();
		cp15_disable_mmu();
		cp15_disable_icache();
		cp15_disable_dcache();
	#endif
*/
#endif

#ifdef SPI_FLASH
	//printf("\n\r");
	printf("--SPI FLASH\n\r");
	_display_driver_info (SPIF_DEVICE, SPIF_INTERFACE, SPIF_COMMENT);
	sresult[index].result = test_spi_flash();
	if(sresult[index].result) printf(" -E- Check jumper JP9 Boot Disable\n\r");
	strcpy (sresult[index++].string, "SPI FLASH\t");
#endif

#ifdef QSPI_FLASH
	//printf("\n\r");
	printf("--QSPI FLASH\n\r");
	_display_driver_info (QSPIF_DEVICE, QSPIF_INTERFACE, QSPIF_COMMENT);
	sresult[index].result = test_qspi_flash();
	if(sresult[index].result) printf(" -E- Check jumper JP9 Boot Disable\n\r");
	strcpy (sresult[index++].string, "QSPI FLASH\t");
#endif

#ifdef SDCARD
	//printf("\n\r");
	printf("--SDCARD\n\r");
	_display_driver_info (SDCARD_DEVICE, SDCARD_INTERFACE, SDCARD_COMMENT);
	sresult[index].result = 0;
	strcpy (sresult[index++].string, "SDCARD\t\t");
#endif

#ifdef LCD
	//printf("\n\r");
	printf("--LCD\n\r");
	_display_driver_info (LCD_DEVICE, LCD_INTERFACE, LCD_COMMENT);
	sresult[index].result = test_lcd();
	strcpy (sresult[index++].string, "LCD\t\t");
#endif

#ifdef GETH
	//printf("\n\r");
	printf("--GETH\n\r");
	_display_driver_info (GETH_DEVICE, GETH_INTERFACE, GETH_COMMENT);
	sresult[index].result = test_geth(1);
	strcpy (sresult[index++].string, "GETH\t\t");
#endif


	printf("\n\r ------------- RESULTS ------------------- \n\r");
	sum = 0;
	for (i=0 ; i!=index; i++) {
		printf("%s : %s \n\r", sresult[i].string, sresult[i].result ? "Failed": "ok");
		sum += sresult[i].result;
	}
	printf("\n\r");
	if(!sum) {
		/* Test result OK, program board info */
		printf("--BOARD INFO UPDATE\n\r");
 		update_at24mac402();
	}

	act8945a_dump_registers(&act8945a);
	act8945a_display_apch_registers(&act8945a);
	act8945a_display_system_registers(&act8945a);

	return sum;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// End of file
