/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015-2016, Atmel Corporation
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
 * \page secumod Security Module Example
 *
 * \section Purpose
 *
 * This basic example shows how to use the \ref secumod_module "Security Module (SECUMOD)"
 * available on the Atmel SAMA5D2 and SAMA5D4 microcontrollers. The SECUMOD
 * provides features to protect against attacks on the chip, recording and
 * timestamping of tamper events.
 *
 * \section Requirements
 *
 * This example can be run on all SAMA5D2 and SAMA5D4 boards.
 *
 * PIOBU pins 0, 1, 3, and 7 are used to monitor the intrusion events:
 * - PIOBU0, PIOBU1 work as a pair in dynamic mode,
 * - PIOBU3 and PIOBU7 work in static mode.
 *
 * Please change the following connections to switch between non-intrusion status
 * and intrusion status.
 * \if document_A5D2_XULT
 *   - shorten PIOBU0, PIOBU1 with a jumper (J12 pin 1, 2)      <--- non-intrusion status
 *   - PIOBU3 (J12 pin 5) connects to GND     <--- intrusion status
 *   - PIOBU7 (J12 pin 8) connects to VCC3.3 <--- intrusion status
 * \endif
 * \section Description
 *
 * Upon startup, the program displays the menu.
 *  - Press '0'/'3'/'7'/'j' to Enable/Disable Protection Monitoring on PIOBU0/1/3/7 and JTAG.\n
 * By default PIOBU0/1 and JTAG protection is disabled;
 *  - Press 'O' to Enable/Disable Protection Monitoring on TST.\n
 *  - Press 'k' to Enable/Disable Protection Monitoring on MCKM.\n
 *  - press 'w' or 'r' to operate the internal RAM;
 *  - press 'a'/'b'/'c' to change access rights of the internal RAM;
 *  - press 'p' to perform internal RAM erasing;
 *  - press 's' to change the scrambling key\n User can read/write the internal RAM
 * by 'r'/'w' to watch how the key effects the content in the RAM;
 *  - press 'm' to switch to backup mode;
 *  - press 'h' to display the menu.
 *
 * Note: The tamper information shown on console might cause misunderstanding once there
 * are many tamper events occur in a short while (the tamper information under printing is
 * updated in SECUMOD interrupt service routine), however the total tamper time is accurate.
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board. Please
 *    refer to the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/xxx.pdf">
 *    SAM-BA User Guide</a>, the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/xxx.pdf">
 *    GNU-Based Software Development</a> application note or to the
 *    <a href="http://www.iar.com/website1/1.0.1.0/78/1/">
 *    IAR EWARM User and reference guides</a>, depending on your chosen solution.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *    \code
 *     -- SECUMOD Example xxx --
 *     -- xxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *
 *
 *    ============== SECUMOD (Security Module) Menu =================
 *
 *    |-----------------------------------------------------------|
 *    |           Protection Configuration                        |
 *    |                                                           |
 *    | Press [0|3|7|j] to Enable/Disable Protection Monitoring   |
 *    |                                                           |
 *    |  0: PIOBU0 and 1 (Dynamic)  [Disabled]                    |
 *    |  3: PIOBU3 (Static)         [Enabled ]                    |
 *    |  7: PIOBU7 (Static)         [Enabled ]                    |
 *    |  j: JTAG Pins               [Disabled]                    |
 *    |  O: TST Pins                [Disabled]                    |
 *    |                                                           |
 *    |-----------------------------------------------------------|
 *    |  q: Tamper Interrupt        [Enabled ]                    |
 *    |  y: SECURAM Auto Erase      [Enabled ]                    |
 *    |-----------------------------------------------------------|
 *    |           SECURAM Access Rights Settings                  |
 *    |                                                           |
 *    | Press [a|b|c] to change access rights for regions below   |
 *    |                                                           |
 *    |  a: Lower area       [ ] None  [ ] W  [ ] R  [X] RW       |
 *    |  b: Higher area      [ ] None  [ ] W  [ ] R  [X] RW       |
 *    |  c: Reg. Bank area   [ ] None  [ ] W  [ ] R  [X] RW       |
 *    |                                                           |
 *    |-----------------------------------------------------------|
 *    |-----------------------------------------------------------|
 *    |               Commands                                    |
 *    |                                                           |
 *    |  w: Write pattern into SECURAM                            |
 *    |  r: Read pattern from SECURAM                             |
 *    |  p: Launch software protection (SECURAM erasing process)  |
 *    |  s: Change Scrambling Key                                 |
 *    |                                                           |
 *    |  m: Switch to Backup Mode                                 |
 *    |                                                           |
 *    |  i: Display the tamper/SECURAM events                     |
 *    |  h: Display this menu                                     |
 *    |                                                           |
 *    |-----------------------------------------------------------|
 *
 *    \endcode
 * -# Press one of the keys listed in the menu to perform the corresponding action.
 *
 * \section References
 * - examples/secumod/main.c
 * - drivers/security/secumod.c
 * - drivers/security/secumod.h
 */

/**
 * \file
 *
 * This file contains all the specific code for the secumod example.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "board_console.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"

#include "irq/irq.h"
#include "gpio/pio.h"
#include "peripherals/pit.h"
#include "peripherals/pmc.h"
#include "peripherals/rtc.h"
#include "security/secumod.h"
#include "peripherals/shdwc.h"

#include "serial/console.h"

#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** Flag for invalid tamper counter */
#define TAMPER_COUNTER_INVALID (0xFFFFFFFF)

/*----------------------------------------------------------------------------
 *        Local types
 *----------------------------------------------------------------------------*/

/** Options for switch on/off some detections in this example  */
struct _option
{
	bool tst;
	bool jtag;
	bool pair0;
	bool piobu3;
	bool pair2;
	bool piobu7;
};

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

/** Tamper source definition */
static const char *tamper_source_info[] = {
	"",
	"",
	"Test pin Monitor",
	"JTAG pins Monitor",
};

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/* Tamper interrupt enable/disable option */
static bool int_opt = false;
static bool erase_opt = false;
#ifdef CONFIG_SOC_SAMA5D2
static unsigned int bureg0_value, bsc_cr_value;
#endif

/** Initial access rights of the RAM regions */
static uint8_t access_rights_lower = 3;
static uint8_t access_rights_higher = 3;
static uint8_t access_rights_bureg = 3;

/** Initial on/off status of the detections */
static struct _option options = {
	.piobu3 = true,
	.piobu7 = true,
};

/* PIOBU pin attribute */
static struct _secumod_piobu piobus[] = {
	{
		.pinIndex = 0, /* PIOBU0 */
		.afv = 5,
		.rfv = 5,
		.mode = 1,
		.outputLevel = 0,
		.pullUpState = 0,
		.scheduled  = 0,
		.inputDefaultLevel = 0,
		.dynamic = 1,
		.filter3_5 = 0,
	},
	{
		.pinIndex = 1, /* PIOBU1 */
		.afv = 5,
		.rfv = 5,
		.mode = 0,
		.outputLevel = 0,
		.pullUpState = 0,
		.scheduled = 0,
		.inputDefaultLevel = 0,
		.dynamic = 1,
		.filter3_5 = 0,
	},
	{
		.pinIndex = 3, /* PIOBU3 */
		.afv = 6,
		.rfv = 6,
		.mode = 0,
		.outputLevel = 0,
		.pullUpState = 1,
		.scheduled = 0,
		.inputDefaultLevel = 1,
		.dynamic = 0,
		.filter3_5 = 0,
	},
	{
		.pinIndex = 4, /* PIOBU4 */
		.afv = 5,
		.rfv = 5,
		.mode = 1,
		.outputLevel = 0,
		.pullUpState = 0,
		.scheduled  = 0,
		.inputDefaultLevel = 0,
		.dynamic = 1,
		.filter3_5 = 0,
	},
	{
		.pinIndex = 5, /* PIOBU5 */
		.afv = 5,
		.rfv = 5,
		.mode = 0,
		.outputLevel = 0,
		.pullUpState = 0,
		.scheduled = 0,
		.inputDefaultLevel = 0,
		.dynamic = 1,
		.filter3_5 = 0,
	},
	{
		.pinIndex = 7, /* PIOBU7 */
		.afv = 8,
		.rfv = 8,
		.mode = 0,
		.outputLevel = 0,
		.pullUpState = 2,
		.scheduled = 0,
		.inputDefaultLevel = 0,
		.dynamic = 0,
		.filter3_5 = 0,
	},
};

/* flags used for callback routines */
static uint32_t tamper_occurred = 0;
static uint32_t violation_occurred = 0;
static uint32_t memory_erased = 0;

/* PLLA EXT12M/24M RC32K MULA=59 DIV2ON=1 PRES=1 DIV=2 */
struct pck_mck_cfg clock_setting = {
		.pck_input = PMC_MCKR_CSS_PLLA_CLK,
		.ext12m = true,
		.ext32k = false,
		.plla = {
#if BOARD_MAIN_CLOCK_EXT_OSC == 12000000
			.mul = 58,
#elif BOARD_MAIN_CLOCK_EXT_OSC == 24000000
			.mul = 25,
#endif
			.div = 1,
			.count = 0x3f,
		},
		.pck_pres = PMC_MCKR_PRES_CLOCK,
		.mck_div = PMC_MCKR_MDIV_PCK_DIV2,
		.plla_div2 = true,
		.h32mx_div2 = true,
};

/*----------------------------------------------------------------------------
 *        Call back routines for ISR
 *----------------------------------------------------------------------------*/
 /**
 * \brief Tamper callback
 */
static void _tamper_callback(void)
{
	/* The tamper information is stored in structure secumod, it will be
	 * destroyed in interrupt service routine once the next tamper event
	 * occurs */
	tamper_occurred++;
}


/**
 * \brief Access violation callback
 */
static void _access_violation_callback(uint8_t region, uint32_t status)
{
	violation_occurred = (status << 8 ) | region;
}


/**
 * \brief Memory erased callback
 */
static void _memory_erased_callback(void)
{
	uint32_t status;
	memory_erased++;
	status = secumod_get_system_status();
	status &= ~SECUMOD_SYSR_ERASE_DONE;
	secumod_set_system_status(status);
}


/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Dump buffer to DBGU
 *
 */
static void _dump_buffer(uint8_t *buffer, uint32_t size)
{
	uint32_t i = 0;
	uint32_t offset = (uint32_t)buffer - (uint32_t)SECURAM->BUSRAM_LOWER;
	do {
		if (i == 16 * 4) {
			printf("\n\r ...");
			i = size - 16 * 4;
		}

		if ((i % 16) == 0) {
			printf("\n\r %04x: ", (unsigned)(offset + i));
		}

		printf(" %02x", buffer[i++]);
	} while (i < size);
}

/**
 * \brief Display current time.
 */
static void _display_current_time( void )
{
	struct _time time;
	struct _date date;

	rtc_get_time(&time);
	printf("\r\n%02d:%02d:%02d", time.hour, time.min, time.sec);

	rtc_get_date(&date);
	printf("\r\n%04d:%02d:%02d", date.year, date.month, date.day);
}

/**
 * \brief Display source of tamper events.
 */
static void _show_tamper_source(uint32_t tamper_src)
{
	uint32_t index;

	printf("\n\r Tamper source: ");
	for (index = 0; index < ARRAY_SIZE(tamper_source_info); index++) {
		if (tamper_src & (1 << index ))
			printf("   %s", tamper_source_info[index]);
	}
	for ( ; index < 32; index++) {
		if (tamper_src & (1 << index))
			printf("   PIOBU%u Intrusion Detector",
					(unsigned)(index - 16));
	}
}

/**
 * \brief Display time, date and source of tamper events.
 */
static void _show_tamper_detail(uint8_t index)
{
	struct _tamper_info *tamper_info = secumod_get_tamper_info();
	struct _tamper_detail *detail = &tamper_info->details[index];

	/* Display time & data of tamper events */
	printf("%02d:%02d:%02d ", detail->time.hour, detail->time.min,
			detail->time.sec);
	printf("%02d/%02d/%04d ", detail->date.month, detail->date.day,
			detail->date.year);

	if (rtc_is_tamper_occur_in_backup_mode(index))
		printf(" (in backup mode)");

	_show_tamper_source(detail->source);
}

/**
 * \brief Show tamper information when there's tamper event since last check.
 */
static void _show_tamper_info(struct _tamper_info *tamper_info)
{
	uint32_t tamper_cnt = tamper_info->tampers;

	printf(" \n\r ====== tamper information of the last check ======");

	if (tamper_info->jtag_sel_ca5) {
		printf(" \n\r JTAGSEL, CA5 TAP response or CA5 debug ACK detected.");
		tamper_info->jtag_sel_ca5 = 0;
	}

	if (tamper_info->jtag_tck_tms) {
		printf(" \n\r JTAG TCK/TMS activity detected.");
		tamper_info->jtag_tck_tms = 0;
	}

	if (tamper_cnt) {
		if (tamper_cnt == 1) {
			printf(" \n\r 1 tamper event occurred since last check.");
			printf(" \n\r Tamper event occurs at: ");
			_show_tamper_detail(0);
		} else if (tamper_cnt == 2) {
			printf(" \n\r 2 tamper events occurred since last check.");
			printf(" \n\r The 1st tamper event occurred at: ");
			_show_tamper_detail(0);
			printf(" \n\r The 2nd tamper event occurred at: ");
			_show_tamper_detail(1);
		} else {
			if (tamper_cnt >= 15) {
				printf(" \n\r More than 15 tamper events occurred since last check.");
			} else {
				printf(" \n\r %u tamper events occurred since last check.",
						(unsigned)tamper_cnt);
			}
			printf(" \n\r The 1st tamper event occurred at: ");
			_show_tamper_detail(0);
			printf(" \n\r The last tamper event occurred at: ");
			_show_tamper_detail(1);
		}
	}
	printf(" \n\r Total: %u tamper events occurred.\n\r",
			(unsigned)tamper_info->total_tampers);
}

/**
 * \brief Show tamper alarm information when tamper interrupt and auto erase
 * are disabled since last check.
 */
static void _show_alarm_status(void)
{
	uint32_t status = secumod_get_status();

	if (status & SECUMOD_SR_JTAG)
		printf("\r\n jtag\r\n");

	if (status & SECUMOD_SR_DET0)
		printf("\r\n piobu0\r\n");
	if (status & SECUMOD_SR_DET1)
		printf("\r\n piobu1\r\n");
	if (status & SECUMOD_SR_DET2)
		printf("\r\n piobu2\r\n");
	if (status & SECUMOD_SR_DET3)
		printf("\r\n piobu3\r\n");
	if (status & SECUMOD_SR_DET4)
		printf("\r\n piobu4\r\n");
	if (status & SECUMOD_SR_DET5)
		printf("\r\n piobu5\r\n");
	if (status & SECUMOD_SR_DET6)
		printf("\r\n piobu6\r\n");
	if (status & SECUMOD_SR_DET7)
		printf("\r\n piobu7\r\n");

	secumod_clear_status(status);
}


/**
 * \brief Show Access violation informations
 */
static void _show_access_violation(uint8_t region, uint32_t status)
{
	switch(status) {
	case SECUMOD_RAMACCSR_W_VIOLATION:
		printf("\n\r SECURAM Region [%d kbytes - %d kbytes] write access violation occurred.",
				region, region + 1);
		break;
	case SECUMOD_RAMACCSR_R_VIOLATION:
		printf("\n\r SECURAM Region [%d kbytes - %d kbytes] read access violation occurred.",
				region, region + 1);
		break;
	case SECUMOD_RAMACCSR_RW_VIOLATION:
		printf("\n\r SECURAM Region [%d kbytes - %d kbytes] read and write access violation occurred.",
				region, region + 1);
		break;
	default:
		break;
	}
}

/**
 * \brief Change new scrambling key.
 * Get new scrambling key from console and change it.
 */
static void _change_scrambling_key(void)
{
	uint32_t old_key = secumod_get_scrambling_key();
	uint32_t new_key;

	printf("\r\n-I- Current Scrambling Key is: %08x", (unsigned)old_key);
	printf("\n\rEnter new Scrambling Key (hexadecimal):");

	if (console_get_hexa_32(&new_key) != 1) {
		printf("\r\n-W- Invalid input, Scrambling Key not modified.");
	} else {
		printf("\r\n-I- Change Scrambling Key: %08x -> %08x",
				(unsigned)old_key, (unsigned)new_key);
		secumod_set_scrambling_key(new_key);
	}
	printf("\r\n");
}

/**
 * \brief Enter Backup Mode.
 * Main Power Supplies off, VDDBU powered by a battery.
 */
static void _enter_backup_mode(void)
{
	volatile uint32_t delay = 500;

#ifdef CONFIG_SOC_SAMA5D2
	/* Retrieve BUREG/BSC_CR values in case they are erased by auto erase */
	SECURAM->BUREG[0] = bureg0_value;
	BSC->BSC_CR = bsc_cr_value;

	printf("backup: bcr_cr register = 0x%08x\r\n",
			(unsigned)BSC->BSC_CR);
	printf("backup: bureg0 register = 0x%08x\r\n",
			(unsigned)SECURAM->BUREG[0]);
#endif

	printf("backup mode protection register  0x%08x\n\r",
			(unsigned)secumod_get_backup_mode_protections());
	printf("backup mode wakeup register  0x%08x\n\r",
			(unsigned)secumod_get_wakeup_protections());
	printf("system status register: 0x%08x\r\n",
			(unsigned)secumod_get_system_status());
	printf("Enter in Backup Mode\n\r");
	printf(" - Press WAKE UP button to wakeup\n\r");

	/* Delay for a while */
	while (delay--);

#ifdef CONFIG_SOC_SAMA5D2
	/* Enable Secure Module input as wake-up source, and set its input type
	 * as rising edge */
	shdwc_set_wakeup_input(SHDW_WUIR_WKUPEN0_ENABLE | SHDW_WUIR_WKUPEN1_ENABLE,
	                       SHDW_WUIR_WKUPT0_LOW     | SHDW_WUIR_WKUPT1_HIGH);

	/* set debouncer period for wakeup inputs of PIOBUx */
	shdwc_set_wakeup_debounce(SHDW_MR_WKUPDBC_512_SLCK);
#endif

	/* enter backup */
	shdwc_do_shutdown();

	while (1);
}

/**
 * \brief Display main menu.
 */
static void _display_menu(void)
{
	const char* enDis[] = { "Disabled", "Enabled " };
	const char* strAccess[] = {
		"[X] None  [ ] W  [ ] R  [ ] RW",
		"[ ] None  [X] W  [ ] R  [ ] RW",
		"[ ] None  [ ] W  [X] R  [ ] RW",
		"[ ] None  [ ] W  [ ] R  [X] RW",
	};

	printf("\n\r============= SECUMOD (Security Module) Menu =============\n\r");
	printf("\n\r");
	printf("|-----------------------------------------------------------|\n\r");
	printf("|                 Protection Configuration                  |\n\r");
	printf("|                                                           |\n\r");
	printf("| Press [0|3|7|j] to Enable/Disable Protection Monitoring   |\n\r");
	printf("|                                                           |\n\r");
	printf("|  0: PIOBU0 and 1 (Dynamic)  [%s]                    |\n\r", enDis[options.pair0]);
	printf("|  3: PIOBU3 (Static)         [%s]                    |\n\r", enDis[options.piobu3]);
	printf("|  2: PIOBU4 and 5 (Dynamic)  [%s]                    |\n\r", enDis[options.pair2]);
	printf("|  7: PIOBU7 (Static)         [%s]                    |\n\r", enDis[options.piobu7]);
	printf("|  j: JTAG Pins               [%s]                    |\n\r", enDis[options.jtag]);
	printf("|  O: TST Pins                [%s]                    |\n\r", enDis[options.tst]);
	printf("|-----------------------------------------------------------|\n\r");
	printf("|  q: Tamper Interrupt        [%s]                    |\n\r", enDis[int_opt]);
	printf("|  y: SECURAM Auto Erase      [%s]                    |\n\r", enDis[erase_opt]);
	printf("|-----------------------------------------------------------|\n\r");
	printf("|              SECURAM Access Rights Settings               |\n\r");
	printf("|                                                           |\n\r");
	printf("| Press [a|b|c] to change access rights for regions below   |\n\r");
	printf("|                                                           |\n\r");
	printf("|  a: Lower area      %s        |\n\r", strAccess[access_rights_lower]);
	printf("|  b: Higher area     %s        |\n\r", strAccess[access_rights_higher]);
	printf("|  c: Reg Bank area   %s        |\n\r", strAccess[access_rights_bureg]);
	printf("|                                                           |\n\r");
	printf("|-----------------------------------------------------------|\n\r");
	printf("|-----------------------------------------------------------|\n\r");
	printf("|                         Commands                          |\n\r");
	printf("|                                                           |\n\r");
	printf("|  w: Write pattern into SECURAM                            |\n\r");
	printf("|  r: Read pattern from SECURAM                             |\n\r");
	printf("|  p: Launch software protection (SECURAM erasing process)  |\n\r");
	printf("|  s: Change Scrambling Key                                 |\n\r");
	printf("|                                                           |\n\r");
	printf("|  m: Switch to Backup Mode                                 |\n\r");
	printf("|                                                           |\n\r");
	printf("|  i: Display the tamper/SECURAM events                     |\n\r");
	printf("|  h: Display this menu                                     |\n\r");
	printf("|                                                           |\n\r");
	printf("|-----------------------------------------------------------|\n\r");

}

/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Application entry point for SECUMOD example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t  key ;
	uint32_t protections;
	uint32_t interrupts;

	/* enable tamper interrupt and auto erase */
	erase_opt = true;
	int_opt = true;

	/* reconfigure PCK, MCK */
	pmc_set_custom_pck_mck(&clock_setting);
	board_cfg_console(0);

	/* Output example information */
	console_example_info("SECUMOD Example");

	/*Print the chip module information*/
	printf("-- CHIP Module: %s --\n\r", get_chip_name());
	printf("-- PCK = %d MHz, MCK = %d MHz--\n\r",
			(unsigned)(pmc_get_processor_clock() / 1000000),
			(unsigned)(pmc_get_master_clock() / 1000000));

#ifdef CONFIG_SOC_SAMA5D2
	/* store the gpbr value in case it is erased by tamper event */
	bsc_cr_value = BSC->BSC_CR;
	bureg0_value = SECURAM->BUREG[0];
	printf("main: bsc_cr = 0x%08x\r\n", bsc_cr_value);
	printf("main: bureg0 = 0x%08x\r\n", bureg0_value);
#endif

	/* Initialize PIT for clean SECUMOD alarm status */
	if (PMC->PMC_MCKR & PMC_MCKR_H32MXDIV_H32MXDIV2) {
		pit_init(pmc_get_master_clock()/2 / 1000000);
	} else {
		pit_init(pmc_get_master_clock() / 1000000);
	}

	secumod_initialize();
	secumod_set_access_callback(_access_violation_callback);
	secumod_set_erased_callback(_memory_erased_callback);
	secumod_set_tamper_callback(_tamper_callback);
	secumod_switch_to_normal_mode();

	/* Configure PIOBUs */
	secumod_piobu_config(piobus, ARRAY_SIZE(piobus));

	/* Prepare protections and enabling interrupts for further configuration */
	protections = 0x00000000;
	interrupts = 0x00000000;

	if (options.pair0) {
		protections |= (SECUMOD_NMPR_DET0 | SECUMOD_NMPR_DET1);
		interrupts |= (SECUMOD_NIEPR_DET0 | SECUMOD_NIEPR_DET1);
	}

	if (options.piobu3) {
		protections |= SECUMOD_NMPR_DET3;
		interrupts |= SECUMOD_NIEPR_DET3;
	}

	if (options.pair2) {
		protections |= (SECUMOD_NMPR_DET4 | SECUMOD_NMPR_DET5);
		interrupts |= (SECUMOD_NIEPR_DET4 | SECUMOD_NIEPR_DET5);
	}

	if (options.piobu7) {
		protections |= SECUMOD_NMPR_DET7;
		interrupts |= SECUMOD_NIEPR_DET7;
	}

	if (options.jtag) {
		protections |= SECUMOD_NMPR_JTAG;
		interrupts |= SECUMOD_NIEPR_JTAG;
	}

	if (options.tst) {
		protections |= SECUMOD_NMPR_TST;
		interrupts |= SECUMOD_NIEPR_TST;
	}

	/* disable all protections before enabling them */
	secumod_set_normal_mode_protections(0x000000);
	secumod_set_backup_mode_protections(0x000000);

	printf("\n\rprotection settings: [%08x]\n\r",
			(unsigned)protections);

	if (erase_opt){
		/* Set protections in normal mode */
		secumod_set_normal_mode_protections(protections);
		/* Set protections in backup mode */
		secumod_set_backup_mode_protections(protections);
	}

	/* disable interrupt configuration before enabling them */
	secumod_disable_it(SECUMOD_NIDPR_ALL);

	/* interrupt configuration */
	if (int_opt)
		secumod_enable_it(interrupts);

	/* Display menu */
	_display_menu();
	while(1) {
		key = console_get_char();

		if (key == 'I' || key == 'i') {
			if (memory_erased) {
				printf("\n\r SECURAM erased %u times",
						(unsigned)memory_erased);
				memory_erased = 0;
				printf(" \n\r ");
				_display_current_time();
				printf(" SECURAM: lower and register bank areas have been erased.\n\r");
			} else {
				printf("\n\r -I- no SECURAM events happened.\n\r");
			}

			if (violation_occurred) {
				_show_access_violation(violation_occurred & 0xFF,
						violation_occurred >> 8);
				violation_occurred = 0;
			} else {
				printf("\n\r -I- no access violations happened.\n\r");
			}

			if (tamper_occurred) {
				printf("\n\r SECUMOD interrupt occurs %u times",
						(unsigned)tamper_occurred);
				tamper_occurred = 0;
				_show_tamper_info(secumod_get_tamper_info());
			} else {
				printf("\n\r -I- Neither tamper interrupt nor securam erase happened. Print Alarm status since last time check\n\r");
				_show_alarm_status();
			}

			continue;
		} else if (key == '0') {
			options.pair0 = !options.pair0;
			if (options.pair0) {
				protections |= (SECUMOD_NMPR_DET0 | SECUMOD_NMPR_DET1);
				if(int_opt)
					secumod_enable_it(SECUMOD_NIEPR_DET0 | SECUMOD_NIEPR_DET1);
			} else {
				protections &= ~(SECUMOD_NMPR_DET0 | SECUMOD_NMPR_DET1);
				secumod_disable_it(SECUMOD_NIDPR_DET0 | SECUMOD_NIDPR_DET1);
			}
		} else if (key == '3') {
			options.piobu3 = !options.piobu3;
			if (options.piobu3) {
				protections |= SECUMOD_NMPR_DET3;
				if(int_opt)
					secumod_enable_it(SECUMOD_NIEPR_DET3);
			} else {
				protections &= ~SECUMOD_NMPR_DET3;
				secumod_disable_it(SECUMOD_NIDPR_DET3);
			}
		} else if (key == '2') {
			options.pair2 = !options.pair2;
			if (options.pair2) {
				protections |= (SECUMOD_NMPR_DET4 | SECUMOD_NMPR_DET5);
				if(int_opt)
					secumod_enable_it(SECUMOD_NIEPR_DET4 | SECUMOD_NIEPR_DET5);
			} else {
				protections &= ~(SECUMOD_NMPR_DET4 | SECUMOD_NMPR_DET5);
				secumod_disable_it(SECUMOD_NIDPR_DET4 | SECUMOD_NIDPR_DET5);
			}
		} else if (key == '7') {
			options.piobu7 = !options.piobu7;
			if (options.piobu7) {
				protections |= SECUMOD_NMPR_DET7;
				if(int_opt)
					secumod_enable_it(SECUMOD_NIEPR_DET7);
			} else {
				protections &= ~SECUMOD_NMPR_DET7;
				secumod_disable_it(SECUMOD_NIDPR_DET7);
			}
		} else if (key == 'J' || key == 'j') {
			options.jtag = !options.jtag;
			if (options.jtag) {
				protections |= SECUMOD_NMPR_JTAG;
				if(int_opt)
					secumod_enable_it(SECUMOD_NIEPR_JTAG);
			} else {
				protections &= ~SECUMOD_NMPR_JTAG;
				secumod_disable_it(SECUMOD_NIDPR_JTAG);
			}
		} else if (key == 'O' || key == 'o') {
			options.tst = !options.tst;
			if (options.tst) {
				protections |= SECUMOD_NMPR_TST;
				if(int_opt)
					secumod_enable_it(SECUMOD_NIEPR_TST);
			} else {
				protections &= ~SECUMOD_NMPR_TST;
				secumod_disable_it(SECUMOD_NIDPR_TST);
			}
		} else if (key == 'Q' || key == 'q'){
			int_opt = !int_opt;
			if(int_opt){
				/*enable the corresponding tamper interrupt*/
				secumod_enable_it(protections);
			}
			else {
				secumod_disable_it(SECUMOD_NIDPR_ALL);
			}

		}else if (key == 'Y' || key == 'y'){
			erase_opt = !erase_opt;
			if(!erase_opt){
			/* disable securam auto erase by the corresponding tamper  */
			secumod_set_normal_mode_protections(~SECUMOD_NMPR_ALL);
			secumod_set_backup_mode_protections(~SECUMOD_NMPR_ALL);
			}
		}
		else if (key == 'R' || key == 'r') {
			/* Wait SECURAM ready */
			while (SECUMOD_RAMRDY_READY != (SECUMOD->SECUMOD_RAMRDY & SECUMOD_RAMRDY_READY));

			/* NOTE: Read SECURAM with access rights check using secumod_read_internal_memory() */
			printf("\r\n-I- SECURAM dump:");

			printf("\r\n-- Lower area (%d bytes)", sizeof(SECURAM->BUSRAM_LOWER));
			_dump_buffer((uint8_t *)SECURAM->BUSRAM_LOWER, sizeof(SECURAM->BUSRAM_LOWER));
			printf("\r\n");

			printf("\r\n-- Higher area (%d bytes)", sizeof(SECURAM->BUSRAM_HIGHER));
			_dump_buffer((uint8_t *)SECURAM->BUSRAM_HIGHER, sizeof(SECURAM->BUSRAM_HIGHER));
			printf("\r\n");

			printf("\r\n-- Register Bank area (%d bits)", 8 * sizeof(SECURAM->BUREG));
			_dump_buffer((uint8_t *)SECURAM->BUREG, sizeof(SECURAM->BUREG));

			printf("\n\r");

			continue;
		} else if (key == 'W' || key == 'w') {

			/* Wait SECURAM ready */
			while (SECUMOD_RAMRDY_READY != (SECUMOD->SECUMOD_RAMRDY & SECUMOD_RAMRDY_READY));

			/* NOTE: Write SECURAM with access rights check using secumod_write_internal_memory() */
			printf("\r\n-I- Fill SECURAM:");

			printf("\r\n-I- -- Lower area with 0x04 (%d bytes)", sizeof(SECURAM->BUSRAM_LOWER));
			memset((uint8_t *)SECURAM->BUSRAM_LOWER, 0x04, sizeof(SECURAM->BUSRAM_LOWER));

			printf("\r\n-I- -- Higher area with 0x01 (%d bytes)", sizeof(SECURAM->BUSRAM_HIGHER));
			memset((uint8_t *)SECURAM->BUSRAM_HIGHER, 0x01, sizeof(SECURAM->BUSRAM_HIGHER));

			printf("\r\n-I- -- Register Bank area with 0xff (%d bits)", 8 * sizeof(SECURAM->BUREG));
			memset((uint8_t *)SECURAM->BUREG, 0xff, sizeof(SECURAM->BUREG));

			printf("\r\n");

			continue;
		} else if (key == 'A' || key == 'a') {
			access_rights_lower = (access_rights_lower + 1) & 0x3;
			secumod_set_ram_access_rights(0, access_rights_lower);
		} else if (key == 'B' || key == 'b') {
			access_rights_higher = (access_rights_higher + 1) & 0x3;
			secumod_set_ram_access_rights(4, access_rights_higher);
		} else if (key == 'C' || key == 'c') {
			access_rights_bureg = (access_rights_bureg + 1) & 0x3;
			secumod_set_ram_access_rights(5, access_rights_bureg);
		} else if (key == 'P' || key == 'p') {
			secumod_software_protection();
			printf("\r\n -I- SECURAM erased.\r\n");
			continue;
		} else if (key == 'S' || key == 's') {
			_change_scrambling_key();
			continue;
		} else if (key == 'M' || key == 'm') {
			/* Set protections in backup mode */
			/*enable vddbuh wake up */
			secumod_set_wakeup_protections(0x800);
			secumod_set_backup_mode_protections(0x0);
			secumod_switch_to_backup_mode();
			_enter_backup_mode();
			printf( " WOKEN UP from Backup Mode.\n\r");
		} else if (key == 'D' || key == 'd') {
			irq_disable(ID_SECUMOD);
			printf( "\r\n SECUMOD interrupt disabled.\n\r");
			continue;
		} else if (key == 'E' || key == 'e') {
			irq_enable(ID_SECUMOD);
			printf( "\r\n SECUMOD interrupt enabled.\n\r");
			continue;
		} else if (key == 'H' || key == 'h') {
		} else {
			continue;
		}
		secumod_switch_to_normal_mode();
		if(erase_opt){
			secumod_set_normal_mode_protections(protections);
			secumod_set_backup_mode_protections(protections);
		}
		_display_menu();
	}
}
