/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
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
 */
#include "common.h"
#include "hardware.h"
#include "pmc.h"
#include "usart.h"
#include "debug.h"
#include "ddramc.h"
#include "spi.h"
#include "gpio.h"
#include "timer.h"
#include "watchdog.h"
#include "string.h"

#include "arch/at91_pmc.h"
#include "arch/at91_rstc.h"
#include "arch/sama5_smc.h"
#include "arch/at91_pio.h"
#include "arch/at91_ddrsdrc.h"
#include "sama5d2_xplained.h"
#include "l2cc.h"
#include "act8865.h"
#include "twi.h"

static void at91_dbgu_hw_init(void)
{
	const struct pio_desc dbgu_pins[] = {
		{"URXD1", AT91C_PIN_PD(2), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"UTXD1", AT91C_PIN_PD(3), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	pio_configure(dbgu_pins);
	pmc_sam9x5_enable_periph_clk(AT91C_ID_UART1);
}

static void initialize_dbgu(void)
{
	unsigned int baudrate = 57600;

	at91_dbgu_hw_init();
	usart_init(BAUDRATE(MASTER_CLOCK, baudrate));
}

#ifdef CONFIG_DDR3
static void ddramc_reg_config(struct ddramc_register *ddramc_config)
{
	ddramc_config->mdr = (AT91C_DDRC2_DBW_32_BITS
				| AT91C_DDRC2_MD_DDR3_SDRAM);

	ddramc_config->cr = (AT91C_DDRC2_NC_DDR10_SDR9
				| AT91C_DDRC2_NR_14
				| AT91C_DDRC2_CAS_5
				| AT91C_DDRC2_DLL_RESET_DISABLED
				| AT91C_DDRC2_WEAK_STRENGTH_RZQ7 /*REVIST*/
				| AT91C_DDRC2_DIS_DLL_DISABLED
				| AT91C_DDRC2_NB_BANKS_8
				| AT91C_DDRC2_DECOD_INTERLEAVED	/*REVIST*/
				| AT91C_DDRC2_UNAL_SUPPORTED); /*REVIST*/

	ddramc_config->rtr = 0x410;

	/* Assume timings for 7.5ns min clock period */
	ddramc_config->t0pr = (AT91C_DDRC2_TRAS_(6)
			| AT91C_DDRC2_TRCD_(3)
			| AT91C_DDRC2_TWR_(3)
			| AT91C_DDRC2_TRC_(10)
			| AT91C_DDRC2_TRP_(3)
			| AT91C_DDRC2_TRRD_(4)
			| AT91C_DDRC2_TWTR_(4)
			| AT91C_DDRC2_TMRD_(4));

	ddramc_config->t1pr = (AT91C_DDRC2_TRFC_(27)
			| AT91C_DDRC2_TXSNR_(24)
			| AT91C_DDRC2_TXSRD_(24)
			| AT91C_DDRC2_TXP_(3));

	ddramc_config->t2pr = (AT91C_DDRC2_TXARD_(2)
			| AT91C_DDRC2_TXARDS_(7)
			| AT91C_DDRC2_TRPA_(4)
			| AT91C_DDRC2_TRTP_(4)
			| AT91C_DDRC2_TFAW_(7));

	ddramc_config->tim_calr = AT91C_DDRC2_ZQCS(64);
}

static void ddramc_init(void)
{
	struct ddramc_register ddramc_reg;
	unsigned int reg;

	ddramc_reg_config(&ddramc_reg);

	pmc_sam9x5_enable_periph_clk(AT91C_ID_MPDDRC);
	pmc_enable_system_clock(AT91C_PMC_DDR);

	writel(AT91C_MPDDRC_RD_DATA_PATH_THREE_CYCLES,
			(AT91C_BASE_MPDDRC + MPDDRC_RD_DATA_PATH));

	reg = readl(AT91C_BASE_MPDDRC + MPDDRC_IO_CALIBR);
	reg &= ~AT91C_MPDDRC_TZQIO;
	reg |= AT91C_MPDDRC_TZQIO_(80);
	reg |= AT91C_MPDDRC_EN_CALIB;
	writel(reg, (AT91C_BASE_MPDDRC + MPDDRC_IO_CALIBR));

	ddr3_sdram_initialize(AT91C_BASE_MPDDRC, AT91C_BASE_DDRCS, &ddramc_reg);

	ddramc_print_config_regs(AT91C_BASE_MPDDRC);
}
#endif

static void SiI9022_hw_reset(void)
{
	pio_set_gpio_output(CONFIG_SYS_HDMI_RESET_PIN, 1);
	pio_set_gpio_output(CONFIG_SYS_HDMI_RESET_PIN, 0);
	udelay(500);
	pio_set_gpio_output(CONFIG_SYS_HDMI_RESET_PIN, 1);
}

#ifdef CONFIG_HW_INIT
void hw_init(void)
{
	/* Disable watchdog */
	at91_disable_wdt();

	/* Switch PCK/MCK on Main Clock output */
	pmc_cfg_mck(BOARD_PRESCALER_MAIN_CLOCK);

	/* Configure PLLA */
	pmc_cfg_plla(PLLA_SETTINGS);

	/* Initialize PLLA charge pump */
	pmc_init_pll(0);

	/* Switch MCK on PLLA output */
	pmc_cfg_mck(BOARD_PRESCALER_PLLA);

	/* Enable External Reset */
	writel(AT91C_RSTC_KEY_UNLOCK | AT91C_RSTC_URSTEN,
					AT91C_BASE_RSTC + RSTC_RMR);

	/* initialize the dbgu */
	initialize_dbgu();

	/* Init timer */
	timer_init();

#ifdef CONFIG_DDR3
	/* Initialize MPDDR Controller */
	ddramc_init();
#endif
	/* Reset HDMI SiI9022 */
	SiI9022_hw_reset();

	/* Prepare L2 cache setup */
	l2cache_prepare();
}
#endif /* #ifdef CONFIG_HW_INIT */

#ifdef CONFIG_DATAFLASH
void at91_spi0_hw_init(void)
{
	const struct pio_desc spi0_pins[] = {
		{"SPI0_SPCK",	AT91C_PIN_PA(14), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SPI0_MOSI",	AT91C_PIN_PA(15), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SPI0_MISO",	AT91C_PIN_PA(16), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SPI0_NPCS",	CONFIG_SYS_SPI_PCS, 1, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	pio_configure(spi0_pins);

	pmc_sam9x5_enable_periph_clk(AT91C_ID_SPI0);
}
#endif

#ifdef CONFIG_SDCARD
static void sdcard_set_of_name_board(char *of_name)
{
	strcpy(of_name, "sama5d4ek.dtb");
}

void at91_mci0_hw_init(void)
{
	const struct pio_desc mci_pins[] = {
		{"MCI1_CK", AT91C_PIN_PA(22), 0, PIO_DEFAULT, PIO_PERIPH_E},
		{"MCI1_CDA", AT91C_PIN_PA(28), 0, PIO_DEFAULT, PIO_PERIPH_E},

		{"MCI1_DA0", AT91C_PIN_PA(18), 0, PIO_DEFAULT, PIO_PERIPH_E},
		{"MCI1_DA1", AT91C_PIN_PE(19), 0, PIO_DEFAULT, PIO_PERIPH_E},
		{"MCI1_DA2", AT91C_PIN_PE(20), 0, PIO_DEFAULT, PIO_PERIPH_E},
		{"MCI1_DA3", AT91C_PIN_PE(21), 0, PIO_DEFAULT, PIO_PERIPH_E},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	pio_configure(mci_pins);
	pmc_sam9x5_enable_periph_clk(AT91C_ID_SDMMC0_TIMER);

	sdcard_set_of_name = &sdcard_set_of_name_board;
}
#endif

#ifdef CONFIG_NANDFLASH
void nandflash_hw_init(void)
{
	const struct pio_desc nand_pins[] = {
		{"NANDOE",	CONFIG_SYS_NAND_OE_PIN,
					0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDWE",	CONFIG_SYS_NAND_WE_PIN,
					0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDALE",	CONFIG_SYS_NAND_ALE_PIN,
					0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDCLE",	CONFIG_SYS_NAND_CLE_PIN,
					0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDCS",	CONFIG_SYS_NAND_ENABLE_PIN,
					1, PIO_DEFAULT, PIO_OUTPUT},
		{"D0",	AT91C_PIN_PC(5), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D1",	AT91C_PIN_PC(6), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D2",	AT91C_PIN_PC(7), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D3",	AT91C_PIN_PC(8), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D4",	AT91C_PIN_PC(9), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D5",	AT91C_PIN_PC(10), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D6",	AT91C_PIN_PC(11), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D7",	AT91C_PIN_PC(12), 0, PIO_PULLUP, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	pio_configure(nand_pins);

	pmc_sam9x5_enable_periph_clk(AT91C_ID_HSMC);

	writel((AT91C_EBICFG_DRIVE0_HIGH
		| AT91C_EBICFG_PULL0_NONE
		| AT91C_EBICFG_DRIVE1_HIGH
		| AT91C_EBICFG_PULL1_NONE), SFR_EBICFG + AT91C_BASE_SFR);

	writel(AT91C_SMC_SETUP_NWE(1)
		| AT91C_SMC_SETUP_NCS_WR(1)
		| AT91C_SMC_SETUP_NRD(1)
		| AT91C_SMC_SETUP_NCS_RD(1),
		(ATMEL_BASE_SMC + SMC_SETUP3));

	writel(AT91C_SMC_PULSE_NWE(2)
		| AT91C_SMC_PULSE_NCS_WR(3)
		| AT91C_SMC_PULSE_NRD(2)
		| AT91C_SMC_PULSE_NCS_RD(3),
		(ATMEL_BASE_SMC + SMC_PULSE3));

	writel(AT91C_SMC_CYCLE_NWE(5)
		| AT91C_SMC_CYCLE_NRD(5),
		(ATMEL_BASE_SMC + SMC_CYCLE3));

	writel(AT91C_SMC_TIMINGS_TCLR(2)
		| AT91C_SMC_TIMINGS_TADL(7)
		| AT91C_SMC_TIMINGS_TAR(2)
		| AT91C_SMC_TIMINGS_TRR(3)
		| AT91C_SMC_TIMINGS_TWB(7)
		| AT91C_SMC_TIMINGS_RBNSEL(2)
		| AT91C_SMC_TIMINGS_NFSEL,
		(ATMEL_BASE_SMC + SMC_TIMINGS3));

	writel(AT91C_SMC_MODE_READMODE_NRD_CTRL
		| AT91C_SMC_MODE_WRITEMODE_NWE_CTRL
		| AT91C_SMC_MODE_DBW_8
		| AT91C_SMC_MODE_TDF_CYCLES(1),
		(ATMEL_BASE_SMC + SMC_MODE3));
}
#endif