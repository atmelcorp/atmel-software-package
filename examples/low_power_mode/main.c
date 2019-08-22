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

/**
 *  \page low_power_mode Low Power Mode Example
 *
 *  \section Purpose
 *  This example will help new users get familiar with device Low-power modes.
 *
 *  \section Requirements
 *  This package can be used with SAMA5D2-XULT.
 *
 *  - Note
 *  Due to the power consumption results can be affected by IOs setting, the
 *  value in datasheet is measured with most IOs disconnected from external
 *  devices.
 *  For boards with the chip can't disconnected from other devices, user can
 *  change the IOs setting to get lower power consumption. For SAMA5D2-XULT
 *  board, put IOs to the state described in board_restore_pio_reset_state() can
 *  achieve lower power consumption.
 *
 *  \section Description
 *  The demonstration program offers methods to make the device enter low power
 *  mode, users can also change the settings of clock and DDR.
 *  Power consumptions could be measured by ammeters connected between the
 *  jumpers of VDDCORE or VDDBU.
 *
 *  \section Usage
 *  -# Build the program and download it inside the evaluation board. Please
 *     refer to the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *     SAM-BA User Guide</a>, the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *     GNU-Based Software Development</a>
 *     application note or to the
 *     <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *     IAR EWARM User Guide</a>,
 *     depending on your chosen solution.
 *  -# On the computer, open and configure a terminal application
 *     (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *    - 115200 bauds
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# Start the application.
 *  -# In the terminal window, the following text should appear (values depend on
 *     the board and chip used):
 *     \code
 *      -- Low Power mode --
 *      -- SAMxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *      -- Select an option :
 *      -- 0 -> Enter BackUp mode
 *      -- 1 -> Enter Low Power mode
 *      -- A -> Init DDR
 *      -- B -> Write data in DDR
 *      -- C -> Check data in DDR
 *      -- D -> Set DDR self-refresh mode and isolate Pads
 *      -- E -> Reset DDR to normal mode and reconnect Pads
 *     \endcode
 *  -# When setting DDR to self-refresh mode
 *
 *
 *  \section References
 *  - low_power_mode/main.c
 *  - pio.h
 *  - pio_it.h
 */

/** \file
 *
 *  This file contains all the specific code for the getting-started example.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "board.h"
#include "board_console.h"
#include "board_led.h"
#include "board_twi.h"
#include "chip.h"
#include "extram/mpddrc.h"
#include "irq/irq.h"
#include "led/led.h"
#include "serial/console.h"
#include "mm/l2cache.h"
#include "peripherals/shdwc.h"
#include "peripherals/wdt.h"
#include "serial/console.h"

#include "clk-config.h"
#include "event-config.h"
#include "low-power-config.h"

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------
 */

volatile unsigned int MenuChoice;
uint8_t modechoice, test_setting_size, eventchoice, eventchoice_bak;
static char message[100] = { 0 };

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------
 */

/**
 *  \brief Handler for DBGU input.
 *
 */

static void _console_handler(uint8_t c)
{
	MenuChoice = c;
}

static void _restore_console(void)
{
	board_cfg_console(0);

	/* Initializing console interrupts */
	console_set_rx_handler(_console_handler);
	console_enable_rx_interrupt();
}

#ifdef VARIANT_SRAM
/**
 * \brief Test SDRAM access
 * \param base_addr Base address of SDRAM
 * \param size  Size of memory in byte
 * \return 1: OK, 0: Error
 */
static uint32_t _sdram_access(uint32_t base_addr, uint32_t size)
{
	uint32_t i;
	uint32_t ret = 1;
	uint32_t *ptr32 = (uint32_t *) base_addr;

	check_ddr_ready();

	/* Test for DWORD accessing */
	printf(" Test for DWORD accessing...\n\r");
	for (i = 0; i < size / 4 ; i++)
		ptr32[i] = (uint32_t)(i & 0xFFFFFFFF);
	return ret;
}

static uint32_t _sdram_check(uint32_t base_addr, uint32_t size)
{
	uint32_t i;
	uint32_t ret = 1;
	uint32_t *ptr32 = (uint32_t *) base_addr;

	check_ddr_ready();

	/* Test for DWORD accessing */
	printf("Test for DWORD accessing...\n\r");
	for (i = 0; i <  size / 4 ;  i++) {
		if (ptr32[i] != (uint32_t)(i & 0xFFFFFFFF)) {
		printf("-E- Expected:%x, read %x @ %x\n\r",
			(unsigned)(i & 0xFFFFFFFF),
			(unsigned)(ptr32[i]),
			(unsigned)(base_addr + i));
			ret = 0;
		}
	}

	return ret;
}
#endif

/* ---------------------------------------------------------------------------
 * Function Name       : _print_menu
 * Object              :
 * ---------------------------------------------------------------------------
 */
static void _print_menu(void)
{
	printf(" ------------------------------------------\n\r"
	       " Select an option :\n\r"
	       " 0 -> Enter BackUp mode\n\r"
	       " 1 -> Enter Low Power mode\n\r"
#ifdef VARIANT_SRAM
	       " A -> Init DDR\n\r"
	       " B -> Write data in DDR\n\r"
	       " C -> Check data in DDR\n\r"
	       " D -> Set DDR self-refresh mode and isolate Pads\n\r"
	       " E -> Reset DDR to normal mode and reconnect Pads\n\r"
#endif
	       " =>");
}

static void menu_backup(void)
{
	printf("\n\r\n\r");
	printf("  =========== Enter Backup mode ===========\n\r");

	/* config the wakeup */
	shdwc_configure_wakeup();
	/* clear status */
	(void)shdwc_get_status();
	/* enter backup mode */
	shdwc_do_shutdown();

	printf("\n\r ! ! ! ! ! ! ! Enter Backup FAILED ! ! ! ! ! ! ! !");
}

#ifdef CONFIG_RAMCODE
#if defined(__GNUC__)
	extern uint32_t _ramcode_lma, _sramcode, _eramcode;
	extern uint32_t _ramdata_lma, _sramdata, _eramdata;
#elif defined(__ICCARM__)
	#pragma section = ".ramcode_section"
	#pragma section = ".ramcode_section_init"
	#pragma section = ".ramdata_section"
	#pragma section = ".ramdata_section_init"
#endif
static void ramcode_init(void)
{
#if defined(__GNUC__)
	memcpy(&_sramcode, &_ramcode_lma, (uint32_t)&_eramcode - (uint32_t)&_sramcode);
	memcpy(&_sramdata, &_ramdata_lma, (uint32_t)&_eramdata - (uint32_t)&_sramdata);
#elif defined(__ICCARM__)
	memcpy(__section_begin(".ramcode_section"),
	    __section_begin(".ramcode_section_init"),
	    __section_size(".ramcode_section_init"));
	memcpy(__section_begin(".ramdata_section"),
	    __section_begin(".ramdata_section_init"),
	    __section_size(".ramdata_section_init"));
#endif
}
#endif

#ifdef VARIANT_DDRAM
RAMDATA static uint32_t tmp_stack[128];
#if defined(__GNUC__)
	__attribute__((optimize("O0")))
#elif defined(__ICCARM__)
	#pragma optimize=none
#endif
#endif
/**
 *  \brief Run low power mode in sram.
 *  \param mode   select test setting.
 */
RAMCODE static void _low_power_run(uint8_t mode)
{
#ifdef VARIANT_DDRAM
	uint32_t sp = (uint32_t)&tmp_stack[128];
	asm("mov r3, %0" : : "r"(sp));
	asm("mov r0, sp");
	asm("mov sp, r3");
	asm("push {r0}");
	{
#endif /* VARIANT_DDRAM */
		RAMDATA static struct pck_mck_cfg clock_cfg;
		RAMDATA static uint32_t i;
		RAMDATA static uint32_t value;
		value = test_setting[mode].mode;
		i = 0;
		do {
			*(uint8_t *)(((uint32_t)&clock_cfg) + i) =
				*(uint8_t *)(((uint32_t)&test_setting[mode].clock_test_setting) + i);
		} while(++i < sizeof(struct pck_mck_cfg));

		/* get board ext32k bypass state */
#if defined(CKGR_MOR_XT32KFME) && defined(SCKC_CR_OSC32BYP)
		clock_cfg.ext32k_bypass = clock_setting_backup.ext32k_bypass;
#endif

#ifdef VARIANT_DDRAM
		_ddr_active_needed = 1;
		ddr_self_refresh();
#endif /* VARIANT_DDRAM */
		/* config PCK and MCK */
		pmc_set_custom_pck_mck(&clock_cfg);
		processor_ulp(value);
		/* wait for the PMC_SR.MCKRDY bit to be set. */
		while ((PMC->PMC_SR & PMC_SR_MCKRDY) == 0);
#ifdef VARIANT_DDRAM
		if (_ddr_active_needed == 1) {
			pmc_set_custom_pck_mck(&clock_setting_backup);
			check_ddr_ready();
	}
#endif
		/* To capture wakeup time */
		led_toggle(0);
#ifdef VARIANT_SRAM
		/* Restore default PCK and MCK */
		pmc_set_custom_pck_mck(&clock_setting_backup);
#endif
#ifdef VARIANT_DDRAM
		_ddr_active_needed = 0;
	}
	asm("pop {r0}");
	asm("mov sp, r0");
#endif /* VARIANT_DDRAM */
}

/**
 *  \brief Configure low power mode option.
 *  \param modechoice   select test settings.
 *  \param eventchoice   select wake up event.
 */
static void _low_power_configure(uint8_t mode, uint8_t event)
{
#ifdef CONFIG_HAVE_LED
	/* config a led for indicator to capture wake-up time */
	board_cfg_led();
#endif
	if(test_setting[mode].mode == IDLE) {
		wakeup_event(event);
		processor_idle();
	} else {
		low_power_cfg(test_setting[mode].mode);
		wakeup_event(event);
		_low_power_run(mode);
		_restore_console();
		low_power_exit(test_setting[mode].mode);
	}

#ifdef CONFIG_HAVE_LED
	/* config a led for indicator to capture wake-up time */
	board_cfg_led();
#endif
}

/**
 *  \brief Print test menu.
 */
static void _low_power_menu(void)
{
	uint8_t m[32], i = 0, a = 0;
	printf("\n\rLow Power Mode Menu :\n\r");
	printf("\n\r=>Press [0|1|2|... ] to select low power mode \n\r\n\r");
	while(test_setting[i].name != NULL) {
		if (modechoice == i) {
			m[i] = 'X';
		} else {
			m[i] = ' ';
		}
		sprintf(message, "%s %s \n\r", "[%c] %x: ", test_setting[i].name);
		printf(message, m[i], i);
		i++;
	}

	/* save test_setting size*/
	test_setting_size = i;

	i = 0;
	a = 0;
	while(event_menu[i] != NULL) {
		if (test_setting[(int)modechoice].event & (1 << i)) {
			m[a++] = i;
		}
		i++;
	}

	i = 0;
	printf("\n\r=>Press [a|b....] to set wake-up event\n\r\n\r");
	while(i < a) {
		printf("%c: ", (char)(i + 'a'));
		sprintf(message, "%s %s \n\r", "[%c] ", event_menu[m[i]]);		
		if(eventchoice == i) {
			printf(message, 'x');
			eventchoice_bak = 1 << m[i];
		} else {
			printf(message, ' ');
		}
		i++;
	}
	printf("\n\r=>Press 't' to run\n\r");
	printf("\n\r=>Press 'u' to auto-run\n\r");
}

/**
 *  \brief Select test menu.
 */
static void _low_power_main(void){
	/* Display menu */
	_low_power_menu();
	MenuChoice = 0;
	while (1) {
		if (MenuChoice >= '0' && MenuChoice < (test_setting_size + 0x30)){
			modechoice = MenuChoice - '0';
			_low_power_menu();
			MenuChoice = ' ';
		} else if (MenuChoice >= 'a' && MenuChoice <= 'f') {
			eventchoice = MenuChoice - 'a';
			_low_power_menu();
			MenuChoice = ' ';
		} else if (MenuChoice == 't') {
			printf("\n\rWaiting for event to exit the low power mode\n\r");
			while(!console_is_tx_empty());
			_low_power_configure(modechoice, eventchoice_bak);
			printf("Leave low power mode\n\r\n\r");
			break;
		} else if (MenuChoice == 'u') {
			printf("\n\rAuto run all setting items with the selected event:\n\r");
			while(!console_is_tx_empty());
			int i = 0;
			while(test_setting[i].name != NULL) {
				if ((test_setting[i].event & eventchoice_bak) != eventchoice_bak) {
					i++;
					continue;
				} 
				sprintf(message, "%d: %s Please waiting...\n\r", i, test_setting[i].name);
				printf(message);
				while(!console_is_tx_empty());
				_low_power_configure(i++, eventchoice_bak);
				printf("->Passed\n\r");
			}
			printf("Leave low power mode\n\r");
			break;
		}
	}
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------
 */

/* override default board_init */
void board_init(void)
{
#ifdef CONFIG_RAMCODE
	ramcode_init();
#endif

	/* Configure low-level peripherals */
#ifdef VARIANT_DDRAM
	board_cfg_lowlevel(false, false, false);
#else
	board_cfg_lowlevel(true, false, false);
#endif
	/* Configure console */
	board_cfg_console(0);

	/* Configure DMA with interrupt */
	dma_initialize(false);

#ifdef CONFIG_HAVE_I2C_BUS
	/* Configure TWI bus */
	board_cfg_twi_bus();

#if defined(CONFIG_HAVE_PMIC_ACT8865) || \
    defined(CONFIG_HAVE_PMIC_ACT8945A)
	/* Configure PMIC */
	board_cfg_pmic();
#endif
#endif /* CONFIG_HAVE_I2C_BUS */
}

/**
 *  \brief Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Output example information */
	console_example_info("Low Power Mode Example");
	while(!console_is_tx_empty());

#ifdef CONFIG_HAVE_L2CC
	/* set a default state at the beginning to save power */
	/* Enable L2 cache clock gating */
	board_cfg_l2cc();

	/* Disable L2 cache */
	l2cache_disable();
#endif

	/* Set the I/Os to an appropriate state */
	board_restore_pio_reset_state();

	/* Disable the USB transceivers and all peripheral clocks */
	board_save_misc_power();

	/* Get PMC configuration */
	clock_setting_backup = pmc_get_pck_mck_cfg();

	/* Disable all AIC interrupt sources */
	unsigned int i;

	for (i = 0; i < 128; i++)
		irq_disable(i);

	/* Initialize console again */
	_restore_console();

	_print_menu();
	MenuChoice = ' ';
	while (1) {
		switch (MenuChoice) {
		case '0':
			printf("0");
			menu_backup();
			MenuChoice = 0;
			break;
		case '1':
			printf("1");
			_low_power_main();
			MenuChoice = 0;
			break;
#ifdef VARIANT_SRAM
		case 'a':
		case 'A':
			printf("a\n\r\n\r");
			printf("  =========== Init DDR ===========\n\r");

			/* init DDR Memory */
			board_cfg_ddram();
			MenuChoice = 0;
			break;
		case 'b':
		case 'B':
			printf("b\n\r\n\r");
			printf("=========== Write data into DDR ===========\n\r");
			
			_sdram_access(DDR_CS_ADDR, BOARD_DDR_MEMORY_SIZE);
			printf("end of init\n\r");
			MenuChoice = 0;
			break;
		case 'c':
		case 'C':
			printf("c\n\r\n\r");
			printf("=========== Verify data in DDR ===========\n\r");
			if (_sdram_check(DDR_CS_ADDR, BOARD_DDR_MEMORY_SIZE))
			printf("data OK\n\r");
			else
			printf("data KO\n\r");
			MenuChoice = 0;
			break;
		case 'd':
		case 'D':
			printf("d\n\r\n\r");
			printf("=========== Set DDR into self-refresh ===========\n\r");

			ddr_self_refresh();
			MenuChoice = 0;
			break;
		case 'e':
		case 'E':
			printf("e\n\r\n\r");
			printf("=========== Out of DDR Self refresh state  ===========\n\r");

			check_ddr_ready();
			MenuChoice = 0;
			break;
#endif
		default:
			if (MenuChoice == 0) {
				MenuChoice = ' ';
				_print_menu();
			}
			break;
		}
	}
}
