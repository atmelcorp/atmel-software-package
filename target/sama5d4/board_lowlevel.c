/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, Atmel Corporation
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
 * \file
 *
 * Provides the low-level initialization function that called on chip startup.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "resources/compiler_defines.h"
#include "core/pmc.h"
#include "core/cpsr.h"
#include "core/aic.h"

#include <stdio.h>

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** Array of dividers to compute max supported peripheral frequency for SAMA5D4
 *  chips.
 */
const uint32_t peripherals_min_clock_dividers[] = {
	0, /* There is no ID 0 */
	0, /* ID_SYS */
	2, /* ID_ARM */
	2, /* ID_PIT */
	2, /* ID_WDT */
	2, /* ID_PIOD */
	2, /* ID_USART0 */
	2, /* ID_USART1 */
	1, /* ID_XDMAC0 */
	2, /* ID_ICM */
	0,
	0,
	2, /* ID_AES */
	0, /* ID_AESB */
	2, /* ID_TDES */
	2, /* ID_SHA */
	1, /* ID_MPDDRC */
	0, /* ID_MATRIX1 */
	0, /* ID_MATRIX0 */
	0, /* ID_VDEC */
	0,
	0, /* ID_MSADCC */
	2, /* ID_HSMC */
	2, /* ID_PIOA */
	2, /* ID_PIOB */
	2, /* ID_PIOC */
	2, /* ID_PIOE */
	2, /* ID_UART0    */
	2, /* ID_UART1    */
	2, /* ID_USART2   */
	2, /* ID_USART3   */
	2, /* ID_USART4   */
	2, /* ID_TWI0 */
	2, /* ID_TWI1 */
	2, /* ID_TWI2     */
	2, /* ID_HSMCI0   */
	2, /* ID_HSMCI1   */
	2, /* ID_SPI0     */
	2, /* ID_SPI1     */
	2, /* ID_SPI2     */
	2, /* ID_TC0      */
	2, /* ID_TC1      */
	2, /* ID_TC2      */
	2, /* ID_PWM      */
	2, /* ID_ADC      */
	2, /* ID_DBGU */
	2, /* ID_UHPHS    */
	2, /* ID_UDPHS    */
	2, /* ID_SSC0     */
	2, /* ID_SSC1     */
	1, /* ID_XDMAC1   */
	1, /* ID_LCDC     */
	1, /* ID_ISI      */
	2, /* ID_TRNG     */
	2, /* ID_GMAC0    */
	2, /* ID_GMAC1    */
	2, /* ID_IRQ      */
	2, /* ID_SFC      */
	0,
	0,
	0,
	0, /* ID_SMD      */
	2, /* ID_TWI3     */
	0, /* ID_SFR      */
	0, /* ID_AIC      */
	0, /* ID_SAIC     */
	0  /* ID_L2CC     */
};

/* IFSR status */
static const char* _prefetch_abort_status[32] = {
	NULL,
	NULL,
	"debug event",
	"access flag fault, section",
	NULL,
	"translation fault, section",
	"access flag fault, page",
	"translation fault, page",
	"synchronous external abort",
	"domain fault, section",
	NULL,
	"domain fault, page",
	"L1 translation, synchronous external abort",
	"permission fault, section",
	"L2 translation, synchronous external abort",
	"permission fault, page",
};

/* DFSR status */
static const char* _data_abort_status[32] = {
	NULL,
	"alignment fault",
	"debug event",
	"access flag fault, section",
	"instruction cache maintenance fault",
	"translation fault, section",
	"access flag fault, page",
	"translation fault, page",
	"synchronous external abort, nontranslation",
	"domain fault, section",
	NULL,
	"domain fault, page",
	"1st level translation, synchronous external abort",
	"permission fault, section",
	"2nd level translation, synchronous external abort",
	"permission fault, page",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	"asynchronous external abort"
};

/*----------------------------------------------------------------------------
 *        Functions Prototypes
 *----------------------------------------------------------------------------*/

void Default_DataAbort_IrqHandler(void);
void Default_PrefetchAbort_IrqHandler(void);
void Default_UndefInstr_IrqHandler(void);

#pragma weak UndefInstr_IrqHandler=Default_UndefInstr_IrqHandler
#pragma weak PrefetchAbort_IrqHandler=Default_PrefetchAbort_IrqHandler
#pragma weak DataAbort_IrqHandler=Default_DataAbort_IrqHandler

/*----------------------------------------------------------------------------
 *        Functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Performs the low-level initialization of the chip.
 * It also enable a low level on the pin NRST triggers a user reset.
 */
void low_level_init(void)
{
	/* Setup default interrupt handlers */
	aic_initialize();

	/* Configure clocking if code is not in external mem */
	if ((uint32_t)low_level_init < DDR_CS_ADDR)
	{
		pmc_select_external_osc();
		pmc_switch_mck_to_main();
		pmc_set_plla(CKGR_PLLAR_ONE |
			     CKGR_PLLAR_PLLACOUNT(0x3F) |
			     CKGR_PLLAR_OUTA(0x0) |
			     CKGR_PLLAR_MULA(87) |
			     1, PMC_PLLICPR_IPLL_PLLA(0x0));
		pmc_set_mck_plla_div(PMC_MCKR_PLLADIV2);
		pmc_set_mck_prescaler(PMC_MCKR_PRES_CLOCK);
		pmc_set_mck_divider(PMC_MCKR_MDIV_PCK_DIV3);
		pmc_switch_mck_to_pll();
	}

	/* Remap */
	board_remap_ram();
}

/**
 * \brief Default handler for "Data Abort" exception
 */
void Default_DataAbort_IrqHandler(void)
{
	uint32_t v1, v2, dfsr;

	asm("mrc p15, 0, %0, c5, c0, 0" : "=r"(v1));
	asm("mrc p15, 0, %0, c6, c0, 0" : "=r"(v2));

	printf("\n\r####################\n\r");
	dfsr = ((v1 >> 4) & 0x0F);
	printf("Data Fault occured in %x domain\n\r", (unsigned int)dfsr);
	dfsr = (((v1 & 0x400) >> 6) | (v1 & 0x0F));
	if (_data_abort_status[dfsr])
		printf("Data Fault reason is: %s\n\r", _data_abort_status[dfsr]);
	else
		printf("Data Fault reason is unknown\n\r");
	printf("Data Fault occured at address: 0x%08x\n\n\r", (unsigned int)v2);
	printf("Data Fault status register value: 0x%x\n\r", (unsigned int)v1);
	printf("\n\r####################\n\r");

	while(1);
}

/**
 * \brief Default handler for "Prefetch Abort" exception
 */
void Default_PrefetchAbort_IrqHandler(void)
{
	uint32_t v1, v2, ifsr;

	asm("mrc p15, 0, %0, c5, c0, 1" : "=r"(v1));
	asm("mrc p15, 0, %0, c6, c0, 2" : "=r"(v2));

	printf("\n\r####################\n\r");
	ifsr = (((v1 & 0x400) >> 6) | (v1 & 0x0F));
	if (_prefetch_abort_status[ifsr])
		printf("Prefetch Fault reason is: %s\n\r", _prefetch_abort_status[ifsr]);
	else
		printf("Prefetch Fault reason is unknown\n\r");
	printf("prefetch Fault occured at address: 0x%08x\n\n\r", (unsigned int)v2);
	printf("Prefetch Fault status register value: 0x%x\n\r", (unsigned int)v1);
	printf("\n\r####################\n\r");

	while(1);
}

/**
 * \brief Default handler for "Undefined Instruction" exception
 */
void Default_UndefInstr_IrqHandler(void)
{
	printf("\n\r####################\n\r");
	printf("Undefined Instruction\n\r");
	printf("\n\r####################\n\r");

	while(1);
}
