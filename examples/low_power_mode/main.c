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
 *  \section Description
 *  The demonstration program offers methods to make the device enter low power
 *  mode, users can also change the settings of clock and DDR.
 *  Power consumptions could be measured by ammeters connected between the
 *  jumpers of VDDCORE or VDDBU.
 *
 *  \section Note
 *  Due to the power consumption results can be affected by IOs setting, the
 *  value in datasheet is measured with most IOs disconnected from external
 *  devices.
 *  For boards with the chip can't disconnected from other devices, user can
 *  change the IOs setting to get lower power consumption. For SAMA5D2-XULT
 *  board, put IOs to the state described in board_restore_pio_reset_state() can
 *  achieve lower power consumption.
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
 *      -- 0 -> Select clock setting
 *      -- 1 -> Enter BackUp mode
 *      -- 2 -> Enter Ultra Low Power mode 0
 *      -- 3 -> Enter Ultra Low Power mode 1
 *      -- 4 -> Enter Idle mode
 *      -- A -> Init DDR
 *      -- B -> Write data in DDR
 *      -- C -> Check data in DDR
 *      -- D -> Set DDR self-refresh mode and isolate Pads
 *      -- E -> Reset DDR to normal mode and reconnect Pads
 *     \endcode
 *  -# When setting DDR to self-refresh mode
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

#include "board.h"
#include "board_console.h"
#include "board_led.h"
#include "board_twi.h"
#include "chip.h"
#include "cpuidle.h"
#include "dma/dma.h"
#include "extram/mpddrc.h"
#include "gpio/pio.h"
#include "irq/irq.h"
#include "led/led.h"
#include "led/led.h"
#include "serial/console.h"
#include "mm/l2cache.h"
#include "peripherals/bus.h"
#include "peripherals/pit.h"
#include "peripherals/pmc.h"
#include "peripherals/rtc.h"
#ifdef CONFIG_HAVE_SFRBU
#include "peripherals/sfrbu.h"
#endif
#include "peripherals/shdwc.h"
#include "peripherals/tc.h"
#include "peripherals/wdt.h"
#include "serial/console.h"
#include "timer.h"
#include "trace.h"

#include "clk-config.h"

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------
 */

unsigned char use_clock_setting = 0;

#ifdef PINS_PUSHBUTTONS
/* Pushbutton \#1 pin instance. */
static const struct _pin button_pins[] = PINS_PUSHBUTTONS;
#endif

volatile unsigned int MenuChoice;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------
 */

/**
 *  \brief Handler for Buttons rising edge interrupt.
 *
 *  Handle process led1 status change.
 */
static void _pio_handler(uint32_t group, uint32_t status, void *user_arg)
{
	int i = 0;

	/* unused */
	(void)group;
	(void)user_arg;

	for (i = 0; i < ARRAY_SIZE(button_pins); ++i) {
		#if 0
		if (status & button_pins[i].mask)
			process_button_evt(i);
		#endif
	}
}

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

/**
 *  \brief Configure the Pushbuttons
 *
 *  Configure the PIO as inputs and generate corresponding interrupt when
 *  pressed or released.
 */
static void _configure_buttons(void)
{
	int i;

	/* Adjust pio debounce filter parameters, uses 10 Hz filter. */
	pio_set_debounce_filter(10);

	for (i = 0; i < ARRAY_SIZE(button_pins); ++i) {
		/* Configure pios as inputs. */
		pio_configure(&button_pins[i], 1);

		/* Initialize pios interrupt with its handlers, see */
		/* PIO definition in board.h. */
		pio_add_handler_to_group(button_pins[i].group,
			button_pins[i].mask, _pio_handler, NULL);
		/* Enable PIO line interrupts. */
		pio_enable_it(button_pins);
	}
}

static void _check_ddr_ready(void)
{
#ifdef CONFIG_HAVE_SFRBU
	if (sfrbu_is_ddr_backup_enabled()) {
		/* Enable the DDR Controller clock signal at PMC level */
		pmc_configure_peripheral(ID_MPDDRC, NULL, true);
		/* Enable ddrclk */
		pmc_enable_system_clock(PMC_SYSTEM_CLOCK_DDR);
		/* Disable DDR Backup mode */
		sfrbu_disable_ddr_backup();
	}
#else
	mpddrc_issue_low_power_command(MPDDRC_LPR_LPCB_DISABLED);
#endif
}

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

	_check_ddr_ready();

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

	_check_ddr_ready();

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

/* ---------------------------------------------------------------------------
 * Function Name       : _print_menu
 * Object              :
 * ---------------------------------------------------------------------------
 */
static void _print_menu(void)
{
	printf(" ------------------------------------------\n\r"
	       " Select an option :\n\r"
	       " 0 -> Select clock setting\n\r"
	       " 1 -> Enter BackUp mode\n\r"
#ifdef CONFIG_SOC_SAMA5D2
	       " 2 -> Enter Ultra Low Power mode 0\n\r"
	       " 3 -> Enter Ultra Low Power mode 1\n\r"
#elif defined(CONFIG_SOC_SAMA5D3) || defined(CONFIG_SOC_SAMA5D4)
	       " 2 -> Enter Ultra Low Power mode\n\r"
#endif
	       " 4 -> Enter Idle mode\n\r"
	       " A -> Init DDR\n\r"
	       " B -> Write data in DDR\n\r"
	       " C -> Check data in DDR\n\r"
	       " D -> Set DDR self-refresh mode and isolate Pads\n\r"
	       " E -> Reset DDR to normal mode and reconnect Pads\n\r"
	       " =>");
}

static void menu_pck_mck(void)
{
	printf("\n\r\n\r");
	printf("Will use clock setting for test: ");
	use_clock_setting++;
	if (use_clock_setting >= ARRAY_SIZE(clock_test_setting))
		use_clock_setting = 0;
	switch (use_clock_setting) {
	case 0: {
		uint32_t pck = BOARD_MAIN_CLOCK_EXT_OSC / 1000000 *
						(clock_test_setting[0].plla.mul + 1);
#ifdef CONFIG_HAVE_PMC_PLLADIV2
		if (clock_test_setting[0].plla_div2)
			pck /= 2;
#endif
		printf("PCK = %dMHz, MCK = %dMHz\n\r", pck,
			pck / ((clock_test_setting[0].mck_div >> PMC_MCKR_MDIV_Pos) + 1));
		break;
	}
	case 1:
		printf("PCK = MCK = Crystal %dMHz\n\r",
			BOARD_MAIN_CLOCK_EXT_OSC / 1000000);
		break;
	case 2:
		printf("PCK = MCK = Crystal %dMHz/16 = %dk Hz\n\r",
			BOARD_MAIN_CLOCK_EXT_OSC / 1000000,
			BOARD_MAIN_CLOCK_EXT_OSC / 16000);
		break;
	case 3:
		printf("PCK = MCK = Crystal %dMHz/64 = %d.%dk Hz\n\r",
			BOARD_MAIN_CLOCK_EXT_OSC / 1000000,
			BOARD_MAIN_CLOCK_EXT_OSC / 1000 / 64,
			(BOARD_MAIN_CLOCK_EXT_OSC / 100 / 64) % 10);
		break;
	case 4:
		printf("PCK = MCK = Crystal 32k Hz\n\r");
		break;
	case 5:
		printf("PCK = MCK = Crystal 32k/64 = 512 Hz\n\r");
		break;
	case 6:
		printf("PCK = MCK = RC 12MHz\n\r");
		break;
	case 7:
		printf("PCK = %dMHz, MCK = %dMHz\n\r",
			BOARD_MAIN_CLOCK_EXT_OSC / 1000000 * 66 / 2,
			BOARD_MAIN_CLOCK_EXT_OSC / 1000000 * 66 / 2 / 3);
		break;
	}
}

#if defined(CONFIG_SOC_SAMA5D2) ||\
    defined(CONFIG_SOC_SAMA5D3) ||\
    defined(CONFIG_SOC_SAMA5D4)

/**
 * \brief Interrupt handler for the RTC. Refreshes the display.
 */
static void _rtc_handler(uint32_t source, void* user_arg)
{
	uint32_t dwStatus = RTC->RTC_SR;

	assert(source == ID_RTC);

	/* Second increment interrupt */
	if ((dwStatus & RTC_SR_SEC) == RTC_SR_SEC) {
		/* Disable RTC interrupt */
		rtc_disable_it(RTC_IDR_SECDIS);

		RTC->RTC_SCCR = RTC_SCCR_SECCLR;
	}
	/* Time or date alarm */
	else {
		if ((dwStatus & RTC_SR_ALARM) == RTC_SR_ALARM) {
			/* Disable RTC interrupt */
			rtc_disable_it(RTC_IDR_ALRDIS);
			RTC->RTC_SCCR = RTC_SCCR_ALRCLR;
		}
	}
}

static void _start_rtc_timer_for_wakeup(unsigned int wakup_in_seconds)
{
	struct _time new_time;

	rtc_disable_it(RTC_IER_SECEN | RTC_IER_ALREN);

	/* Default RTC configuration */
	/* 24-hour mode */
	rtc_set_hour_mode(RTC_HOUR_MODE_24);
	struct _time empty_time = {0, 0, 0};

	if (rtc_set_time_alarm(&empty_time))
		printf("\r\n Disable time alarm fail!");

	struct _date empty_date = {0, 0, 0};

	if (rtc_set_date_alarm(&empty_date))
		printf("\r\n Disable date alarm fail!");

	new_time.hour = 0;
	new_time.min = 0;
	new_time.sec = 0;
	rtc_set_time(&new_time);

	/* Configure RTC interrupts */
	rtc_enable_it(RTC_IER_ALREN);
	irq_add_handler(ID_RTC, _rtc_handler, NULL);
	irq_enable(ID_RTC);
	new_time.hour = 0;
	new_time.min = 0;
	new_time.sec = wakup_in_seconds;
	rtc_set_time_alarm(&new_time);
}

#endif /* CONFIG_SOC_SAMA5D2 || CONFIG_SOC_SAMA5D3 || CONFIG_SOC_SAMA5D4 */

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

#if defined(CONFIG_SOC_SAMA5D2)
static void menu_ulp0(void)
{
	unsigned int  read_reg[4];

	printf("\n\r\n\r");
	printf("  =========== Enter Ultra Low Power mode 0 ===========\n\r");

	/* Back up IOs and USB transceivers */
	read_reg[0] = PMC->PMC_PCSR0;
	read_reg[1] = PMC->PMC_PCSR1;
	read_reg[2] = PMC->PMC_SCSR;
	read_reg[3] = PMC->CKGR_UCKR;

	/* Set the I/Os to an appropriate state */
	board_restore_pio_reset_state();

	/* Disable the USB transceivers and all peripheral clocks */
	board_save_misc_power();

	/* Set the interrupts to wake up the system. */
	_configure_buttons();

#ifdef CONFIG_HAVE_LED
	/* config a led for indicator to capture wake-up time */
	board_cfg_led();
#endif

	/* config PCK and MCK */
	pmc_set_custom_pck_mck(&clock_test_setting[use_clock_setting]);

	/* enter IDLE mode */
	cpu_idle();

	/* Restore default PCK and MCK */
	pmc_set_custom_pck_mck(&clock_test_setting[0]);
	_restore_console();

	/* Restore IOs and USB transceivers */
	PMC->PMC_PCER0 = read_reg[0];
	PMC->PMC_PCER1 = read_reg[1];
	PMC->PMC_SCER  = read_reg[2];
	PMC->CKGR_UCKR = read_reg[3];

	printf("  | | | | | | Leave Ultra Low Power mode | | | | | |\n\r");
}

static void menu_ulp1(void)
{
	unsigned int  read_reg[4];

	printf("\n\r\n\r");
	printf("  =========== Enter Ultra Low Power mode 1 ===========\n\r");
	printf("  =========== USE WKUP0 button to wake up  ===========\n\r");
	printf("  === Auto wakeup from RTC alarm after 30 second =====\n\r");

	/* Back up IOs and USB transceivers */
	read_reg[0] = PMC->PMC_PCSR0;
	read_reg[1] = PMC->PMC_PCSR1;
	read_reg[2] = PMC->PMC_SCSR;
	read_reg[3] = PMC->CKGR_UCKR;

	/* Set the I/Os to an appropriate state */
	board_restore_pio_reset_state();

	/* Disable the USB transceivers and all peripheral clocks */
	board_save_misc_power();

#ifdef CONFIG_HAVE_LED
	/* config a led for indicator to capture wake-up time */
	board_cfg_led();
#endif

	/* ultra low power mode 1, RC12 is selected for Main Clock */
	/* Disable the PLLs and the main oscillator */
	pmc_set_custom_pck_mck(&clock_test_setting[6]);

	/* set RTC alarm for wake up */
	_start_rtc_timer_for_wakeup(30);

	/* config wake up sources and active polarity */
	pmc_set_fast_startup_polarity(0, PMC_FSPR_FSTP0);
	pmc_set_fast_startup_mode(PMC_FSMR_FSTT0 | PMC_FSMR_FSTT2 |
		PMC_FSMR_RTCAL | PMC_FSMR_LPM);

	/* enter ULP1 */
	asm("WFE");
	asm("WFE");

	/* wait for the PMC_SR.MCKRDY bit to be set. */
	while ((PMC->PMC_SR & PMC_SR_MCKRDY) == 0);

	/* To capture wakeup time, we need to write the register */
	/* directly instead of calling C function */
	/* led_set(0); pio_clear(&pinsLeds[led]);*/
	PIOA->PIO_IO[1].PIO_CODR = PIO_PB6;

	/* Restore default PCK and MCK */
	pmc_set_custom_pck_mck(&clock_test_setting[0]);
	_restore_console();

	/* Restore IOs and USB transceivers */
	PMC->PMC_PCER0 = read_reg[0];
	PMC->PMC_PCER1 = read_reg[1];
	PMC->PMC_SCER  = read_reg[2];
	PMC->CKGR_UCKR = read_reg[3];

	printf("  | | | | | | Leave Ultra Low Power mode | | | | | |\n\r");
}
#elif defined(CONFIG_SOC_SAMA5D3) || defined(CONFIG_SOC_SAMA5D4)
static void menu_ulp(void)
{
	unsigned int  read_reg[4];

	printf("\n\r\n\r");
	printf("  =========== Enter Ultra Low Power mode  ============\n\r");
	printf("  === Auto wakeup from RTC alarm after 30 second =====\n\r");

	/* Back up IOs and USB transceivers */
	read_reg[0] = PMC->PMC_PCSR0;
	read_reg[1] = PMC->PMC_PCSR1;
	read_reg[2] = PMC->PMC_SCSR;
	read_reg[3] = PMC->CKGR_UCKR;

	/* Set the I/Os to an appropriate state */
	board_restore_pio_reset_state();

	/* Disable the USB transceivers and all peripheral clocks */
	board_save_misc_power();

	/* config a led for indicator to capture wake-up time */
	board_cfg_led();

	/* ultra low power mode 1, RC12 is selected for Main Clock */
	/* Disable the PLLs and the main oscillator */
	pmc_set_custom_pck_mck(&clock_test_setting[6]);

	/* set RTC alarm for wake up */
	_start_rtc_timer_for_wakeup(30);

	/* enter ULP */
	cpu_idle();

	/* wait for the PMC_SR.MCKRDY bit to be set. */
	while ((PMC->PMC_SR & PMC_SR_MCKRDY) == 0);

	/* To capture wakeup time, we need to write the register */
	/* directly instead of calling C function */
	led_toggle(0);

	/* Restore default PCK and MCK */
	pmc_set_custom_pck_mck(&clock_test_setting[0]);
	_restore_console();

	/* Restore IOs and USB transceivers */
	PMC->PMC_PCER0 = read_reg[0];
	PMC->PMC_PCER1 = read_reg[1];
	PMC->PMC_SCER  = read_reg[2];
	PMC->CKGR_UCKR = read_reg[3];

	printf("  | | | | | | Leave Ultra Low Power mode | | | | | |\n\r");
}
#endif /* defined(CONFIG_SOC_SAMA5D3) || defined(CONFIG_SOC_SAMA5D4) */

static void menu_idle(void)
{
	/* In this mode, only the core clock is stopped. The peripheral clocks,
	 * including the DDR controller clock, can be enabled. The current
	 * consumption in this mode is application-dependent.
	 */

	/* config a button to wakeup*/
	printf("\n\r\n\r");
	printf("Configure button with debouncing.\n\r");
	_configure_buttons();

#ifdef CONFIG_HAVE_LED
	/* config a led for indicator to capture wake-up time */
	printf("Configure led for wakeup indicator.\n\r");
	board_cfg_led();
#endif

	printf("=========== Enter Idle mode ===========\n\r");
	/* config PCK and MCK */
	pmc_set_custom_pck_mck(&clock_test_setting[use_clock_setting]);
	cpu_idle();

	/* Restore default PCK and MCK */
	pmc_set_custom_pck_mck(&clock_test_setting[0]);
	printf("| | | | | | Leave Idle mode | | | | | |\n\r");
}

static void menu_init_ddr(void)
{
#ifndef VARIANT_DDRAM
	printf("\n\r\n\r");
	printf("  =========== Init DDR ===========\n\r");

	/* init DDR Memory */
	board_cfg_ddram();
#else
	printf("\n\r\n\r");
	printf("DDRAM already initialized\n\r");
#endif
}

static void menu_write_ddr(void)
{
	printf("\n\r\n\r");
	printf("=========== Write data into DDR ===========\n\r");

	_sdram_access(DDR_CS_ADDR, BOARD_DDR_MEMORY_SIZE);
	printf("end of init\n\r");
}

static void menu_check_ddr(void)
{
	printf("\n\r\n\r");
	printf("=========== Verify data in DDR ===========\n\r");

	if (_sdram_check(DDR_CS_ADDR, BOARD_DDR_MEMORY_SIZE))
	printf("data OK\n\r");
	else
	printf("data KO\n\r");
}

static void menu_self_refresh(void)
{
	printf("\n\r\n\r");
	printf("=========== Set DDR into self-refresh ===========\n\r");

#ifdef CONFIG_HAVE_SFRBU
	if (!sfrbu_is_ddr_backup_enabled()) {
		/* Wait DDR into self-refresh mode*/
		while (!((MPDDRC->MPDDRC_LPR) & MPDDRC_LPR_SELF_DONE));

		/* Disable the DDR Controller clock signal at PMC level*/
		pmc_disable_peripheral(ID_MPDDRC);
		/* Disable ddrclk */
		pmc_disable_system_clock(PMC_SYSTEM_CLOCK_DDR);

		sfrbu_enable_ddr_backup();
	}
#else
	mpddrc_issue_low_power_command(MPDDRC_LPR_LPCB_SELFREFRESH);
#endif
}

static void menu_out_of_self_refresh(void)
{
	printf("\n\r\n\r");
	printf("=========== Out of DDR Self refresh state  ===========\n\r");

	_check_ddr_ready();
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------
 */

/* override default board_init */
void board_init(void)
{
	/* Configure system clocks */
	pmc_set_custom_pck_mck(&clock_test_setting[0]);

	/* Configure low-level peripherals */
	board_cfg_lowlevel(false, false, false);

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

	/* Disable all AIC interrupt sources */
	unsigned int i;

	for (i = 0; i < 128; i++)
		irq_disable(i);

	/* Initialize console again */
	_restore_console();

	_print_menu();
	MenuChoice = 0;
	while (1) {
		switch (MenuChoice) {
		case '0':
			printf("0");
			menu_pck_mck();
			MenuChoice = 0;
			_print_menu();
			break;
		case '1':
			printf("1");
			menu_backup();
			MenuChoice = 0;
			_print_menu();
			break;
#if defined(CONFIG_SOC_SAMA5D2)
		case '2':
			printf("2");
			menu_ulp0();
			MenuChoice = 0;
			_print_menu();
			break;
		case '3':
			printf("3");
			menu_ulp1();
			MenuChoice = 0;
			_print_menu();
			break;
#elif defined(CONFIG_SOC_SAMA5D3) || defined(CONFIG_SAMA5D4)
		case '2':
			printf("2");
			menu_ulp();
			MenuChoice = 0;
			_print_menu();
			break;
#endif
		case '4':
			printf("4");
			menu_idle();
			MenuChoice = 0;
			_print_menu();
			break;
		case 'a':
		case 'A':
			printf("a");
			menu_init_ddr();
			MenuChoice = 0;
			_print_menu();
			break;
		case 'b':
		case 'B':
			printf("b");
			menu_write_ddr();
			MenuChoice = 0;
			_print_menu();
			break;
		case 'c':
		case 'C':
			printf("c");
			menu_check_ddr();
			MenuChoice = 0;
			_print_menu();
			break;
		case 'd':
		case 'D':
			printf("d");
			menu_self_refresh();
			MenuChoice = 0;
			_print_menu();
			break;
		case 'e':
		case 'E':
			printf("e");
			menu_out_of_self_refresh();
			MenuChoice = 0;
			_print_menu();
			break;
		default:
			break;
		}
	}
}
