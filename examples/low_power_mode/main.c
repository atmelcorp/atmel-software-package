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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------
 */

#include "board.h"
#include "chip.h"

#include "peripherals/aic.h"
#include "peripherals/rtc.h"
#include "peripherals/pmc.h"
#include "peripherals/twid.h"
#include "peripherals/wdt.h"
#include "peripherals/pio.h"
#include "peripherals/l2cc.h"
#include "peripherals/shdwc.h"
#include "peripherals/sfrbu.h"
#include "cortex-a/mmu.h"

#include "misc/led.h"
#include "power/act8945a.h"

#include "misc/console.h"

#include <stdbool.h>
#include <stdio.h>

#include "peripherals/tc.h"
#include "peripherals/pit.h"

#include "trace.h"
#include "compiler.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------
 */

struct pck_mck_cfg clock_test_setting[] = {
	/* PLL A = 996, PCK = 498, MCK = 166 MHz */
	/* PLLA RC12M RC32K MULA=83 DIV2ON=1 PRES=0 MDIV=3 */
	{
		.pck_input = PMC_MCKR_CSS_PLLA_CLK,
		.ext12m = false,
		.ext32k = false,
		.plla_mul = 82,
		.plla_div = 1,
		.plla_div2 = true,
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_PCK_DIV3,
		.h32mxdiv2 = true,
	},
	/* PCK = MCK = 12MHz */
	/* MAIN RC12M RC32K MULA=0 DIV2ON=0 PRES=0 MDIV=0 */
	{
		.pck_input = PMC_MCKR_CSS_MAIN_CLK,
		.ext12m = false,
		.ext32k = false,
		.plla_mul = 0,
		.plla_div = 1,
		.plla_div2 = false,
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
		.h32mxdiv2 = false,
	},
	/* PCK = MCK = 750 kHz */
	/* MAIN RC12M RC32K MULA=0 DIV2ON=0 PRES=16 MDIV=0 */
	{
		.pck_input = PMC_MCKR_CSS_MAIN_CLK,
		.ext12m = false,
		.ext32k = false,
		.plla_mul = 0,
		.plla_div = 1,
		.plla_div2 = false,
		.pck_pres = PMC_MCKR_PRES_CLOCK_DIV16,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
		.h32mxdiv2 = false,
	},
	/* PCK = MCK = 187.5 kHz */
	/* MAIN RC12M RC32K MULA=0 DIV2ON=0 PRES=64 MDIV=0 */
	{
		.pck_input = PMC_MCKR_CSS_MAIN_CLK,
		.ext12m = false,
		.ext32k = false,
		.plla_mul = 0,
		.plla_div = 1,
		.plla_div2 = false,
		.pck_pres = PMC_MCKR_PRES_CLOCK_DIV64,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
		.h32mxdiv2 = false,
	},
	/* PCK = MCK = 32 kHz */
	/* slow clock RC12M RC32K MULA=0 DIV2ON=0 PRES=0 MDIV=0 */
	{
		.pck_input = PMC_MCKR_CSS_SLOW_CLK,
		.ext12m = false,
		.ext32k = false,
		.plla_mul = 0,
		.plla_div = 1,
		.plla_div2 = false,
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
		.h32mxdiv2 = false,
	},
	/* PCK = MCK = 512 Hz */
	/* slow clock RC12M RC32K MULA=0 DIV2ON=0 PRES=64 MDIV=0 */
	{
		.pck_input = PMC_MCKR_CSS_SLOW_CLK,
		.ext12m = false,
		.ext32k = false,
		.plla_mul = 0,
		.plla_div = 1,
		.plla_div2 = false,
		.pck_pres = PMC_MCKR_PRES_CLOCK_DIV64,
		.mck_div = PMC_MCKR_MDIV_EQ_PCK,
		.h32mxdiv2 = false,
	},
	/* PLL A = 792, PCK = 396, MCK = 132MHz */
	/* MAIN RC12M EXT32K MULA=66 DIV2ON=1 PRES=0 MDIV=3 */
	{
		.pck_input = PMC_MCKR_CSS_PLLA_CLK,
		.ext12m = true,
		.ext32k = true,
		.plla_mul = 65,
		.plla_div = 1,
		.plla_div2 = true,
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_PCK_DIV3,
		.h32mxdiv2 = false,
	},
};

#define MENU_NB_OPTIONS 9
#define MENU_STRING_LENGTH 200
char menu_choice_msg[MENU_NB_OPTIONS][MENU_STRING_LENGTH] = {
/* "====================MAXLENGTH==================== */
	" 0 -> Select clock setting\n\r",
	" 1 -> Enter BackUp mode\n\r",
	" 2 -> Enter Ultra Low Power mode 0\n\r",
	" 3 -> Enter Ultra Low Power mode 1\n\r",
	" 4 -> Enter Idle mode\n\r",
	" A -> Init DDR\n\r",
	" B -> write data in DDR\n\r",
	" C -> check data in DDR\n\r",
	" D -> set DDR self-refresh and isolate Pads\n\r"};
/* "====================MAXLENGTH==================== */

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------
 */

unsigned char use_clock_setting = 0;

#ifdef CONFIG_HAVE_PMIC_ACT8945A
struct _pin act8945a_pins[] = ACT8945A_PINS;
struct _twi_desc act8945a_twid = {
	.addr = ACT8945A_ADDR,
	.freq = ACT8945A_FREQ,
	.transfert_mode = TWID_MODE_POLLING
};
struct _act8945a act8945a = {
	.desc = {
		.pin_chglev = ACT8945A_PIN_CHGLEV,
		.pin_irq = ACT8945A_PIN_IRQ,
		.pin_lbo = ACT8945A_PIN_LBO
	}
};
#endif

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
static void _pio_handler(uint32_t mask, uint32_t status, void *user_arg)
{
	int i = 0;

	/* unused */
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

static void _console_handler(void)
{
	if (!console_is_rx_ready())
		return;
	MenuChoice = console_get_char();
}

static void _restore_console(void)
{
	console_configure(CONSOLE_BAUDRATE);

	/* Initializing console interrupts */
	aic_set_source_vector(CONSOLE_ID, _console_handler);
	aic_enable(CONSOLE_ID);
	console_enable_interrupts(US_IER_RXRDY);
}

/**
 *  \brief Configure the Pushbuttons
 *
 *  Configure the PIO as inputs and generate corresponding interrupt when
 *  pressed or released.
 */
static void _configure_buttons(void)
{
	int i = 0;

	for (i = 0; i < ARRAY_SIZE(button_pins); ++i) {
		/* Configure pios as inputs. */
		pio_configure(&button_pins[i], 1);

		/* Adjust pio debounce filter parameters, uses 10 Hz filter. */
		pio_set_debounce_filter(&button_pins[i], 10);

		/* Initialize pios interrupt with its handlers, see */
		/* PIO definition in board.h. */
		pio_configure_it(&button_pins[i]);
		pio_add_handler_to_group(button_pins[i].group,
			button_pins[i].mask, _pio_handler, NULL);
		/* Enable PIO line interrupts. */
		pio_enable_it(button_pins);
	}
}

static void _check_ddr_ready(void)
{
	if (sfrbu_is_ddr_backup_enabled()) {
		/* Enable the DDR Controller clock signal at PMC level */
		pmc_enable_peripheral(ID_MPDDRC);
		/* Enable ddrclk */
		pmc_enable_system_clock(PMC_SYSTEM_CLOCK_DDR);

		sfrbu_disable_ddr_backup();
	}
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
	int i;

	printf(" ------------------------------------------\n\r");
	printf("\n\r");
	printf(" Select an option :\n\r");

	for (i = 0; i < MENU_NB_OPTIONS; ++i)
		printf(menu_choice_msg[i]);

	printf(" =>");
}

static void menu_pck_mck(void)
{
	printf("\n\r\n\r");
	printf("Will use clock setting for test: ");
	use_clock_setting++;
	if (use_clock_setting >= ARRAY_SIZE(clock_test_setting))
		use_clock_setting = 0;
	switch (use_clock_setting) {
	case 0:
		printf("PCK = 498, MCK = 166MHz\n\r");
		break;
	case 1:
		printf("PCK = MCK = Crystal 12MHz\n\r");
		break;
	case 2:
		printf("PCK = MCK = Crystal 12MHz/16 = 750k Hz\n\r");
		break;
	case 3:
		printf("PCK = MCK = Crystal 12MHz/64 = 187.5k Hz\n\r");
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
		printf("PCK = 396, MCK = 132MHz\n\r");
		break;
	}
}

/**
 * \brief Interrupt handler for the RTC. Refreshes the display.
 */
static void _sysc_handler(void)
{
	uint32_t dwStatus = RTC->RTC_SR;

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
	rtc_set_hour_mode(0);
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
	aic_set_source_vector(ID_SYSC, _sysc_handler);
	aic_enable(ID_SYSC);
	new_time.hour = 0;
	new_time.min = 0;
	new_time.sec = wakup_in_seconds;
	rtc_set_time_alarm(&new_time);
}

static void menu_backup(void)
{
	printf("\n\r\n\r");
	printf("  =========== Enter Backup mode ===========\n\r");

	/* SHDW_WUIR_WKUPT0_LOW for new board */
	/* SHDW_WUIR_WKUPT0_HIGH for old version */
	shdwc_set_wakeup_input(SHDW_WUIR_WKUPEN0_ENABLE, SHDW_WUIR_WKUPT0_LOW);
	shdwc_configure_wakeup_mode(0);
	/* enter backup mode */
	shdwc_do_shutdown();

	printf("\n\r ! ! ! ! ! ! ! Enter Backup FAILED ! ! ! ! ! ! ! !");
}

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
	pmc_enable_peripheral(ID_AIC);

	/* config a led for indicator to capture wake-up time*/
	led_configure(0);

	/* config PCK and MCK */
	pmc_set_custom_pck_mck(&clock_test_setting[use_clock_setting]);
	/* enter IDLE mode */
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_PCK);
	asm("wfi");

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

	/* config a led for indicator to capture wake-up time*/
	led_configure(0);

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
	PIOA->PIO_PIO_[1].S_PIO_CODR = PIO_PB6;

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

	/* config a led for indicator to capture wake-up time*/
	printf("Configure led for wakeup indicator.\n\r");
	led_configure(0);

	printf("=========== Enter Idle mode ===========\n\r");
	/* config PCK and MCK */
	pmc_set_custom_pck_mck(&clock_test_setting[use_clock_setting]);
	/* enter IDLE mode */
	pmc_disable_system_clock(PMC_SYSTEM_CLOCK_PCK);
	asm("wfi");

	/* Restore default PCK and MCK */
	pmc_set_custom_pck_mck(&clock_test_setting[0]);
	printf("| | | | | | Leave Idle mode | | | | | |\n\r");
}

static void menu_init_ddr(void)
{
	printf("\n\r\n\r");
	printf("  =========== Init DDR ===========\n\r");

	/* init DDR Memory */
	board_cfg_ddram();
	/* During ddr init, PIT inturrupt is enabled. Disable it here*/
	aic_disable(ID_PIT);
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

	if (!sfrbu_is_ddr_backup_enabled()) {
		/* Wait DDR into self-refresh mode*/
		while (!((MPDDRC->MPDDRC_LPR) & MPDDRC_LPR_SELF_DONE));

		/* Disable the DDR Controller clock signal at PMC level*/
		pmc_disable_peripheral(ID_MPDDRC);
		/* Disable ddrclk */
		pmc_disable_system_clock(PMC_SYSTEM_CLOCK_DDR);

		sfrbu_enable_ddr_backup();
	}
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------
 */

/**
 *  \brief Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Disable watchdog */
	wdt_disable();

	/* Disable all PIO interrupts */
	pio_reset_all_it();

	/* Initialize console */
	console_configure(CONSOLE_BAUDRATE);

	/* Output example information */
	printf("-- Low Power mode --\n\r");
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

#ifdef CONFIG_HAVE_PMIC_ACT8945A
	pio_configure(act8945a_pins, ARRAY_SIZE(act8945a_pins));
	if (act8945a_configure(&act8945a, &act8945a_twid)) {
		act8945a_set_regulator_voltage(&act8945a, 6, 2500);
		act8945a_enable_regulator(&act8945a, 6, true);
	} else {
		printf("--E-- Error initializing ACT8945A PMIC\n\r");
	}
#endif

	/* set a default state at the beginning to save power */
	/* Enable L2 cache clock gating */
	board_cfg_l2cc();

	/* Disable L2 cache */
	l2cc_disable();

	/* Set the I/Os to an appropriate state */
	board_restore_pio_reset_state();

	/* Disable the USB transceivers and all peripheral clocks */
	board_save_misc_power();

	/* Disable all AIC interrupt sources */
	unsigned int i;

	for (i = 0; i < 128; i++)
		aic_disable(i);

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
		default:
			break;
		}
	}
}
