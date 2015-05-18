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
 * \file
 *
 * Provides the low-level initialization function that called on chip startup.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "board.h"
#include "resources/compiler_defines.h"
#include "core/pmc.h"
#include "core/pio.h"
#include "core/cpsr.h"
#include <stdio.h>

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** Array of dividers to compute max supported peripheral frequence for SAMA5D2
 *  chips.
 */
const uint32_t peripherals_min_clock_dividers[] = {
	2,/* ID_SAIC_FIQ */
	2,/* ID_PMC */
	2,/* ID_ARM_PMU */
	2,/* ID_PIT */
	2,/* ID_WDT */
	2,/* ID_GMAC */
	1,/* ID_XDMAC0 */
	1,/* ID_XDMAC1 */
	2,/* ID_ICM */
	2,/* ID_AES */
	1,/* ID_AESB */
	2,/* ID_TDES */
	2,/* ID_SHA */
	2,/* ID_MPDDRC */
	2,/* ID_MATRIX1 */
	1,/* ID_MATRIX0 */
	0,
	2,/* ID_HSMC */
	2,/* ID_PIOA */
	2,/* ID_FLEXCOM0 */
	2,/* ID_FLEXCOM1 */
	2,/* ID_FLEXCOM2 */
	2,/* ID_FLEXCOM3 */
	2,/* ID_FLEXCOM4 */
	2,/* ID_UART0 */
	2,/* ID_UART1 */
	2,/* ID_UART2 */
	2,/* ID_UART3 */
	2,/* ID_UART4 */
	2,/* ID_TWIHS0 */
	2,/* ID_TWIHS1 */
	1,/* ID_SDHC0 */
	1,/* ID_SDHC1 */
	2,/* ID_SPI0 */
	2,/* ID_SPI1 */
	2,/* ID_TC0 */
	2,/* ID_TC1 */
	0,
	2,/* ID_PWM */
	0,
	2,/* ID_ADC */
	2,/* ID_UHPHS */
	2,/* ID_UDPHS */
	2,/* ID_SSC0 */
	2,/* ID_SSC1 */
	1,/* ID_LCDC */
	2,/* ID_ISC */
	2,/* ID_TRNG */
	2,/* ID_PDMIC */
	2,/* ID_AIC_IRQ */
	2,/* ID_SFC */
	2,/* ID_SECURAM */
	2,/* ID_QSPI0 */
	2,/* ID_QSPI1 */
	2,/* ID_I2SC0 */
	2,/* ID_I2SC1 */
	0,
	0,
	0,
	2,/* ID_CLASSD */
	2,/* ID_SFR */
	2,/* ID_SAIC */
	2,/* ID_AIC */
	2,/* ID_L2CC */
	2,/* ID_CAN0_INT1 */
	2,/* ID_CAN1_INT1 */
	2,/* ID_GMAC_Q1 */
	2,/* ID_GMAC_Q2 */
	2,/* ID_PIOB */
	2,/* ID_PIOC */
	2,/* ID_PIOD */
	2,/* ID_SDHC0_TIMER */
	0,
	2,/* ID_RSTC */
	2,/* ID_RTC */
	2,/* ID_ACC */
	2,/* ID_RXLP */
	0,
	2,/* ID_CHIPID */
};
static const char* abort_status[][2]=
{
	// IFSR status        ,       DFSR status
	{"Unknown(reserved status)",                          "Unknown(reserved status)"                      },//0
	{"Unknown(reserved status)",                          "Alignment Fault"                               },//1
	{"Debug Event",                                       "Debug Event"                                   },//2
	{"Access flag - section",                             "Access flag - section"                         },//3
	{"Unknown(reserved status)",                          "Instruction cache maintenance"                 },//4
	{"Translation fault - section",                       "Translation fault - section"                   },//5
	{"Access flag - Page",                                "Access flag - Page"                            },//6
	{"Translation fault -Page",                           "Translation fault -Page"                       },//7
	{"Synchronous external abort",                        "Synchronous external abort, nontranslation"    },//8
	{"Domain fault - Section",                            "Domain fault - Section"                        },//9
	{"Unknown(reserved status)",                          "Unknown(reserved status)"                      },//10
	{"Domain fault - Page",                               "Domain fault - Page"                           },//11
	{"Synchronous external abort - L1 Translation",       "Synchronous external abort - L1 Translation"   },//12
	{"Permission fault - Section",                        "Permission fault - Section"                    },//13
	{"Synchronous external abort - L2 Translation",       "Synchronous external abort - L2 Translation"   },//14
	{"Permission fault - Page",                           "Permission fault - Page"                       },//15
	{"Unknown(reserved status)",                          "Unknown(reserved status)"                      },//16
	{"Unknown(reserved status)",                          "Unknown(reserved status)"                      },//17
	{"Unknown(reserved status)",                          "Unknown(reserved status)"                      },//18
	{"Unknown(reserved status)",                          "Unknown(reserved status)"                      },//19
	{"Unknown(reserved status)",                          "Unknown(reserved status)"                      },//20
	{"Unknown(reserved status)",                          "Unknown(reserved status)"                      },//21
	{"Unknown(reserved status)",                          "Asynchronous external abort"}
};

/*----------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------*/

extern WEAK void low_level_init(void);

void default_spurious_handler(void);
void abort_c_handler(void);
void prefetch_c_handler(void);
void undefined_c_Handler(void);
void dummy_handler(void);
void non_secure_it_init(void);
void secure_it_init(void);

/*----------------------------------------------------------------------------
 *        Functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Performs the low-level initialization of the chip.
 * It also enable a low level on the pin NRST triggers a user reset.
 */
extern WEAK void low_level_init(void)
{
	volatile uint32_t * pAicFuse = (volatile uint32_t *) REG_SFR_AICREDIR;

	non_secure_it_init();
	if(!(*pAicFuse)) {
		secure_it_init();
	}

	/* clock configure */
	if ((uint32_t)low_level_init < DDR_CS_ADDR) /* Code not in external mem */ {
		pmc_select_external_osc();
		pmc_switch_mck_to_main();
		pmc_set_plla( CKGR_PLLAR_ONE |
			      CKGR_PLLAR_PLLACOUNT(0x3F) |
			      CKGR_PLLAR_OUTA(0x0) |
			      CKGR_PLLAR_MULA(87) |
			      1,
			      PMC_PLLICPR_IPLL_PLLA(0x0));
		pmc_set_mck_plla_div(PMC_MCKR_PLLADIV2);
		pmc_set_mck_prescaler(PMC_MCKR_PRES_CLOCK);
		pmc_set_mck_divider(PMC_MCKR_MDIV_PCK_DIV3);
		pmc_switch_mck_to_pll();
	}
	/* Remap */
	board_remap_ram();
}

/**
 * \brief Default spurious interrupt handler.
 * Infinite loop.
 */
void default_spurious_handler(void)
{
	while (1);
}

/**
 * \brief Abort c handler.
 * Infinite loop.
 */
void abort_c_handler(void)
{
	uint32_t v1,v2, dfsr;
	v1= 0;
	v2= 0;
	asm("mrc   p15, 0, %0, c5, c0, 0" : : "r"(v1));
	asm("mrc   p15, 0, %0, c6, c0, 0" : : "r"(v2));

	dfsr = ((v1 >> 4) & 0x0F);
	printf("\n\r######################################################################\n\r");
	printf("Data Abort occured in %x domain\n\r", (uint32_t)dfsr);
	dfsr = (((v1 & 0x400) >> 6) | (v1 & 0x0F));
	printf("Data abort fault reason is: %s\n\r", (char*)abort_status[dfsr][1]);
	printf("Data fault occured at Address = 0x%08x\n\n\r",(uint32_t)v2);
	printf("-[Info]-Data fault status register value = 0x%x\n\r",(uint32_t)v1);
	while(1);
}

/**
 * \brief Prefetch c handler.
 * Infinite loop.
 */
void prefetch_c_handler(void)
{
	uint32_t v1,v2, ifsr;
	v1= 0;
	v2= 0;

	asm("mrc   p15, 0, %0, c5, c0, 1" : : "r"(v1));
	asm("mrc   p15, 0, %0, c6, c0, 2" : : "r"(v2));

	ifsr = (((v1 & 0x400) >> 6) | (v1 & 0x0F));
	printf("\n\r######################################################################\n\r");
	printf("Instruction prefetch abort reason is: %s\n\r", (char*)abort_status[ifsr][0]);
	printf("Instruction prefetch Fault occured at Address = 0x%08x\n\n\r",(uint32_t)v2);
	printf("-[INFO]- Prefetch Fault status register value by = 0x%x\n\r",(uint32_t)v1);
	while(1);
}

/**
 * \brief Undefined c handler.
 * Infinite loop.
 */
void undefined_c_Handler(void)
{
	printf("Undefined abort \n\r");
	while(1);
}

/**
 * \brief dummy default handler.
 */
void dummy_handler(void)
{
	while(1) ;
}

#pragma weak PIT_Handler=dummy_handler              /**<  3 SAMA5D2x Periodic Interval Timer Interrupt (PIT) */
#pragma weak WDT_Handler=dummy_handler              /**<  4 SAMA5D2x Watchdog timer Interrupt (WDT) */
#pragma weak GMAC_Handler=dummy_handler             /**<  5 SAMA5D2x Ethernet MAC (GMAC) */
#pragma weak XDMAC0_Handler=dummy_handler           /**<  6 SAMA5D2x DMA Controller 0 (XDMAC0) */
#pragma weak XDMAC1_Handler=dummy_handler           /**<  7 SAMA5D2x DMA Controller 1 (XDMAC1) */
#pragma weak ICM_Handler=dummy_handler              /**<  8 SAMA5D2x Integritry Check Monitor (ICM) */
#pragma weak AES_Handler=dummy_handler              /**<  9 SAMA5D2x Advanced Enion Standard (AES) */
#pragma weak AESB_Handler=dummy_handler             /**< 10 SAMA5D2x AES bridge (AESB) */
#pragma weak TDES_Handler=dummy_handler             /**< 11 SAMA5D2x Triple Data Enion Standard (TDES) */
#pragma weak SHA_Handler=dummy_handler              /**< 12 SAMA5D2x SHA Signature (SHA) */
#pragma weak MPDDRC_Handler=dummy_handler           /**< 13 SAMA5D2x MPDDR controller (MPDDRC) */
#pragma weak MATRIX1_Handler=dummy_handler          /**< 14 SAMA5D2x H32MX, 32-bit AHB Matrix (MATRIX1) */
#pragma weak MATRIX0_Handler=dummy_handler          /**< 15 SAMA5D2x H64MX, 64-bit AHB Matrix (MATRIX0) */
#pragma weak HSMC_Handler=dummy_handler             /**< 17 SAMA5D2x Multi-bit ECC Interrupt (HSMC) */
#pragma weak PIOA_Handler=dummy_handler             /**< 18 SAMA5D2x Parallel I/O Controller (PIOA) */
#pragma weak FLEXCOM0_Handler=dummy_handler         /**< 19 SAMA5D2x FLEXCOM 0 (FLEXCOM0) */
#pragma weak FLEXCOM1_Handler=dummy_handler         /**< 20 SAMA5D2x FLEXCOM 1 (FLEXCOM1) */
#pragma weak FLEXCOM2_Handler=dummy_handler         /**< 21 SAMA5D2x FLEXCOM 2 (FLEXCOM2) */
#pragma weak FLEXCOM3_Handler=dummy_handler         /**< 22 SAMA5D2x FLEXCOM 3 (FLEXCOM3) */
#pragma weak FLEXCOM4_Handler=dummy_handler         /**< 23 SAMA5D2x FLEXCOM 4 (FLEXCOM4) */
#pragma weak UART0_Handler=dummy_handler            /**< 24 SAMA5D2x UART 0 (UART0) */
#pragma weak UART1_Handler=dummy_handler            /**< 25 SAMA5D2x UART 1 (UART1) */
#pragma weak UART2_Handler=dummy_handler            /**< 26 SAMA5D2x UART 2 (UART2) */
#pragma weak UART3_Handler=dummy_handler            /**< 27 SAMA5D2x UART 3 (UART3) */
#pragma weak UART4_Handler=dummy_handler            /**< 28 SAMA5D2x UART 4 (UART4) */
#pragma weak TWIHS0_Handler=dummy_handler           /**< 29 SAMA5D2x Two-Wire Interface 0 (TWIHS0) */
#pragma weak TWIHS1_Handler=dummy_handler           /**< 30 SAMA5D2x Two-Wire Interface 1 (TWIHS1) */
#pragma weak SPI0_Handler=dummy_handler             /**< 33 SAMA5D2x Serial Peripheral Interface 0 (SPI0) */
#pragma weak SPI1_Handler=dummy_handler             /**< 34 SAMA5D2x Serial Peripheral Interface 1 (SPI1) */
#pragma weak TC0_Handler=dummy_handler              /**< 35 SAMA5D2x Timer Counter 0 (ch. 0, 1, 2) (TC0) */
#pragma weak TC1_Handler=dummy_handler              /**< 36 SAMA5D2x Timer Counter 1 (ch. 3, 4, 5) (TC1) */
#pragma weak PWM_Handler=dummy_handler              /**< 38 SAMA5D2x Pulse Width Modulation Controller0 (ch. 0, 1, 2, 3) (PWM) */
#pragma weak ADC_Handler=dummy_handler              /**< 40 SAMA5D2x Touch Screen ADC Controller (ADC) */
#pragma weak UHPHS_Handler=dummy_handler            /**< 41 SAMA5D2x USB Host High Speed (UHPHS) */
#pragma weak UDPHS_Handler=dummy_handler            /**< 42 SAMA5D2x USB Device High Speed (UDPHS) */
#pragma weak SSC0_Handler=dummy_handler             /**< 43 SAMA5D2x Synchronous Serial Controller 0 (SSC0) */
#pragma weak SSC1_Handler=dummy_handler             /**< 44 SAMA5D2x Synchronous Serial Controller 1 (SSC1) */
#pragma weak LCDC_Handler=dummy_handler             /**< 45 SAMA5D2x LCD Controller (LCDC) */
#pragma weak TRNG_Handler=dummy_handler             /**< 47 SAMA5D2x True Random Number Generator (TRNG) */
#pragma weak PDMIC_Handler=dummy_handler            /**< 48 SAMA5D2x Pulse Density Modulation Interface Controller (PDMIC) */
#pragma weak SFC_Handler=dummy_handler              /**< 50 SAMA5D2x Fuse Controller (SFC) */
#pragma weak QSPI0_Handler=dummy_handler            /**< 52 SAMA5D2x QSPI 0 (QSPI0) */
#pragma weak QSPI1_Handler=dummy_handler            /**< 53 SAMA5D2x QSPI 1 (QSPI1) */
#pragma weak I2SC0_Handler=dummy_handler            /**< 54 SAMA5D2x Inter-IC Sound Controller 0 (I2SC0) */
#pragma weak I2SC1_Handler=dummy_handler            /**< 55 SAMA5D2x Inter-IC Sound Controller 1 (I2SC1) */
#pragma weak CLASSD_Handler=dummy_handler           /**< 59 SAMA5D2x Audio Class D amplifier (CLASSD) */
#pragma weak SFR_Handler=dummy_handler              /**< 60 SAMA5D2x Special Function Register  (SFR) */
#pragma weak SAIC_Handler=dummy_handler             /**< 61 SAMA5D2x Secured Advanced Interrupt Controller  (SAIC) */
#pragma weak AIC_Handler=dummy_handler              /**< 62 SAMA5D2x Advanced Interrupt Controller  (AIC) */
#pragma weak L2CC_Handler=dummy_handler             /**< 63 SAMA5D2x L2 Cache Controller (L2CC) */
#pragma weak PIOB_Handler=dummy_handler             /**< 68 SAMA5D2x  (PIOB) */
#pragma weak PIOC_Handler=dummy_handler             /**< 69 SAMA5D2x  (PIOC) */
#pragma weak PIOD_Handler=dummy_handler             /**< 70 SAMA5D2x  (PIOD) */
#pragma weak ACC_Handler=dummy_handler              /**< 75 SAMA5D2x Analog Comparator (ACC) */
#pragma weak RXLP_Handler=dummy_handler             /**< 76 SAMA5D2x Uart Low Power (RXLP) */
#pragma weak CHIPID_Handler=dummy_handler           /**< 78 SAMA5D2x Chip ID (CHIPID) */

#pragma weak Spurious_handler=dummy_handler


/**
 * \brief Non-secure Interupt Init.
 */
void non_secure_it_init(void)
{
	/* Disable IRQ and FIQ at core level */
	v_arm_set_cpsr_bits(CPSR_MASK_IRQ|CPSR_MASK_FIQ);
	uint32_t i;

	/* Disable all interrupts */
	for (i = 1; i < ID_PERIPH_COUNT; i++){
		AIC->AIC_SSR = i;
		AIC->AIC_IDCR = AIC_IDCR_INTD;
	}
	/* Clear All pending interrupts flags */
	for (i = 0; i < ID_PERIPH_COUNT; i++){
		AIC->AIC_SSR  = i;
		AIC->AIC_ICCR = AIC_ICCR_INTCLR;
	}
	/* /\* Perform 8 IT acknoledge (write any value in EOICR) *\/ */
	for (i = 0; i < 8; i++){
		AIC->AIC_EOICR = 0;
	}

	/* Assign handler addesses */
	AIC->AIC_SSR =  3; AIC->AIC_SVR = (uint32_t) PIT_Handler;              /**<  3 SAMA5D2x Periodic Interval Timer Interrupt (PIT) */
	AIC->AIC_SSR =  4; AIC->AIC_SVR = (uint32_t) WDT_Handler;              /**<  4 SAMA5D2x Watchdog timer Interrupt (WDT) */
	AIC->AIC_SSR =  5; AIC->AIC_SVR = (uint32_t) GMAC_Handler;             /**<  5 SAMA5D2x Ethernet MAC (GMAC) */
	AIC->AIC_SSR =  6; AIC->AIC_SVR = (uint32_t) XDMAC0_Handler;           /**<  6 SAMA5D2x DMA Controller 0 (XDMAC0) */
	AIC->AIC_SSR =  7; AIC->AIC_SVR = (uint32_t) XDMAC1_Handler;           /**<  7 SAMA5D2x DMA Controller 1 (XDMAC1) */
	AIC->AIC_SSR =  8; AIC->AIC_SVR = (uint32_t) ICM_Handler;              /**<  8 SAMA5D2x Integritry Check Monitor (ICM) */
	AIC->AIC_SSR =  9; AIC->AIC_SVR = (uint32_t) AES_Handler;              /**<  9 SAMA5D2x Advanced Enion Standard (AES) */
	AIC->AIC_SSR = 10; AIC->AIC_SVR = (uint32_t) AESB_Handler;             /**< 10 SAMA5D2x AES bridge (AESB) */
	AIC->AIC_SSR = 11; AIC->AIC_SVR = (uint32_t) TDES_Handler;             /**< 11 SAMA5D2x Triple Data Enion Standard (TDES) */
	AIC->AIC_SSR = 12; AIC->AIC_SVR = (uint32_t) SHA_Handler;              /**< 12 SAMA5D2x SHA Signature (SHA) */
	AIC->AIC_SSR = 13; AIC->AIC_SVR = (uint32_t) MPDDRC_Handler;           /**< 13 SAMA5D2x MPDDR controller (MPDDRC) */
	AIC->AIC_SSR = 14; AIC->AIC_SVR = (uint32_t) MATRIX1_Handler;          /**< 14 SAMA5D2x H32MX, 32-bit AHB Matrix (MATRIX1) */
	AIC->AIC_SSR = 15; AIC->AIC_SVR = (uint32_t) MATRIX0_Handler;          /**< 15 SAMA5D2x H64MX, 64-bit AHB Matrix (MATRIX0) */
	AIC->AIC_SSR = 17; AIC->AIC_SVR = (uint32_t) HSMC_Handler;             /**< 17 SAMA5D2x Multi-bit ECC Interrupt (HSMC) */
	AIC->AIC_SSR = 18; AIC->AIC_SVR = (uint32_t) PIOA_Handler;             /**< 18 SAMA5D2x Parallel I/O Controller (PIOA) */
	AIC->AIC_SSR = 19; AIC->AIC_SVR = (uint32_t) FLEXCOM0_Handler;         /**< 19 SAMA5D2x FLEXCOM 0 (FLEXCOM0) */
	AIC->AIC_SSR = 20; AIC->AIC_SVR = (uint32_t) FLEXCOM1_Handler;         /**< 20 SAMA5D2x FLEXCOM 1 (FLEXCOM1) */
	AIC->AIC_SSR = 21; AIC->AIC_SVR = (uint32_t) FLEXCOM2_Handler;         /**< 21 SAMA5D2x FLEXCOM 2 (FLEXCOM2) */
	AIC->AIC_SSR = 22; AIC->AIC_SVR = (uint32_t) FLEXCOM3_Handler;         /**< 22 SAMA5D2x FLEXCOM 3 (FLEXCOM3) */
	AIC->AIC_SSR = 23; AIC->AIC_SVR = (uint32_t) FLEXCOM4_Handler;         /**< 23 SAMA5D2x FLEXCOM 4 (FLEXCOM4) */
	AIC->AIC_SSR = 24; AIC->AIC_SVR = (uint32_t) UART0_Handler;            /**< 24 SAMA5D2x UART 0 (UART0) */
	AIC->AIC_SSR = 25; AIC->AIC_SVR = (uint32_t) UART1_Handler;            /**< 25 SAMA5D2x UART 1 (UART1) */
	AIC->AIC_SSR = 26; AIC->AIC_SVR = (uint32_t) UART2_Handler;            /**< 26 SAMA5D2x UART 2 (UART2) */
	AIC->AIC_SSR = 27; AIC->AIC_SVR = (uint32_t) UART3_Handler;            /**< 27 SAMA5D2x UART 3 (UART3) */
	AIC->AIC_SSR = 28; AIC->AIC_SVR = (uint32_t) UART4_Handler;            /**< 28 SAMA5D2x UART 4 (UART4) */
	AIC->AIC_SSR = 29; AIC->AIC_SVR = (uint32_t) TWIHS0_Handler;           /**< 29 SAMA5D2x Two-Wire Interface 0 (TWIHS0) */
	AIC->AIC_SSR = 30; AIC->AIC_SVR = (uint32_t) TWIHS1_Handler;           /**< 30 SAMA5D2x Two-Wire Interface 1 (TWIHS1) */
	AIC->AIC_SSR = 33; AIC->AIC_SVR = (uint32_t) SPI0_Handler;             /**< 33 SAMA5D2x Serial Peripheral Interface 0 (SPI0) */
	AIC->AIC_SSR = 34; AIC->AIC_SVR = (uint32_t) SPI1_Handler;             /**< 34 SAMA5D2x Serial Peripheral Interface 1 (SPI1) */
	AIC->AIC_SSR = 35; AIC->AIC_SVR = (uint32_t) TC0_Handler;              /**< 35 SAMA5D2x Timer Counter 0 (ch. 0, 1, 2) (TC0) */
	AIC->AIC_SSR = 36; AIC->AIC_SVR = (uint32_t) TC1_Handler;              /**< 36 SAMA5D2x Timer Counter 1 (ch. 3, 4, 5) (TC1) */
	AIC->AIC_SSR = 38; AIC->AIC_SVR = (uint32_t) PWM_Handler;              /**< 38 SAMA5D2x Pulse Width Modulation Controller0 (ch. 0, 1, 2, 3) (PWM) */
	AIC->AIC_SSR = 40; AIC->AIC_SVR = (uint32_t) ADC_Handler;              /**< 40 SAMA5D2x Touch Screen ADC Controller (ADC) */
	AIC->AIC_SSR = 41; AIC->AIC_SVR = (uint32_t) UHPHS_Handler;            /**< 41 SAMA5D2x USB Host High Speed (UHPHS) */
	AIC->AIC_SSR = 42; AIC->AIC_SVR = (uint32_t) UDPHS_Handler;            /**< 42 SAMA5D2x USB Device High Speed (UDPHS) */
	AIC->AIC_SSR = 43; AIC->AIC_SVR = (uint32_t) SSC0_Handler;             /**< 43 SAMA5D2x Synchronous Serial Controller 0 (SSC0) */
	AIC->AIC_SSR = 44; AIC->AIC_SVR = (uint32_t) SSC1_Handler;             /**< 44 SAMA5D2x Synchronous Serial Controller 1 (SSC1) */
	AIC->AIC_SSR = 45; AIC->AIC_SVR = (uint32_t) LCDC_Handler;             /**< 45 SAMA5D2x LCD Controller (LCDC) */
	AIC->AIC_SSR = 47; AIC->AIC_SVR = (uint32_t) TRNG_Handler;             /**< 47 SAMA5D2x True Random Number Generator (TRNG) */
	AIC->AIC_SSR = 48; AIC->AIC_SVR = (uint32_t) PDMIC_Handler;            /**< 48 SAMA5D2x Pulse Density Modulation Interface Controller (PDMIC) */
	AIC->AIC_SSR = 50; AIC->AIC_SVR = (uint32_t) SFC_Handler;              /**< 50 SAMA5D2x Fuse Controller (SFC) */
	AIC->AIC_SSR = 52; AIC->AIC_SVR = (uint32_t) QSPI0_Handler;            /**< 52 SAMA5D2x QSPI 0 (QSPI0) */
	AIC->AIC_SSR = 53; AIC->AIC_SVR = (uint32_t) QSPI1_Handler;            /**< 53 SAMA5D2x QSPI 1 (QSPI1) */
	AIC->AIC_SSR = 54; AIC->AIC_SVR = (uint32_t) I2SC0_Handler;            /**< 54 SAMA5D2x Inter-IC Sound Controller 0 (I2SC0) */
	AIC->AIC_SSR = 55; AIC->AIC_SVR = (uint32_t) I2SC1_Handler;            /**< 55 SAMA5D2x Inter-IC Sound Controller 1 (I2SC1) */
	AIC->AIC_SSR = 59; AIC->AIC_SVR = (uint32_t) CLASSD_Handler;           /**< 59 SAMA5D2x Audio Class D amplifier (CLASSD) */
	AIC->AIC_SSR = 60; AIC->AIC_SVR = (uint32_t) SFR_Handler;              /**< 60 SAMA5D2x Special Function Register  (SFR) */
	AIC->AIC_SSR = 61; AIC->AIC_SVR = (uint32_t) SAIC_Handler;             /**< 61 SAMA5D2x Secured Advanced Interrupt Controller  (SAIC) */
	AIC->AIC_SSR = 62; AIC->AIC_SVR = (uint32_t) AIC_Handler;              /**< 62 SAMA5D2x Advanced Interrupt Controller  (AIC) */
	AIC->AIC_SSR = 63; AIC->AIC_SVR = (uint32_t) L2CC_Handler;             /**< 63 SAMA5D2x L2 Cache Controller (L2CC) */
	AIC->AIC_SSR = 68; AIC->AIC_SVR = (uint32_t) PIOB_Handler;             /**< 68 SAMA5D2x  (PIOB) */
	AIC->AIC_SSR = 69; AIC->AIC_SVR = (uint32_t) PIOC_Handler;             /**< 69 SAMA5D2x  (PIOC) */
	AIC->AIC_SSR = 70; AIC->AIC_SVR = (uint32_t) PIOD_Handler;             /**< 70 SAMA5D2x  (PIOD) */
	AIC->AIC_SSR = 75; AIC->AIC_SVR = (uint32_t) ACC_Handler;              /**< 75 SAMA5D2x Analog Comparator (ACC) */
	AIC->AIC_SSR = 76; AIC->AIC_SVR = (uint32_t) RXLP_Handler;             /**< 76 SAMA5D2x Uart Low Power (RXLP) */
	AIC->AIC_SSR = 78; AIC->AIC_SVR = (uint32_t) CHIPID_Handler;           /**< 78 SAMA5D2x Chip ID (CHIPID) */

	AIC->AIC_SPU = (uint32_t)Spurious_handler;

	/* Enable IRQ and FIQ at core level */
	v_arm_clr_cpsr_bits(CPSR_MASK_IRQ|CPSR_MASK_FIQ);
}

/**
 * \brief Secure interrupt init.
 */
void secure_it_init(void)
{
	uint32_t i;

	/* Assign handler addesses */
	SAIC->AIC_SSR =  3; SAIC->AIC_SVR = (uint32_t) PIT_Handler;              /**<  3 SAMA5D2x Periodic Interval Timer Interrupt (PIT) */
	SAIC->AIC_SSR =  4; SAIC->AIC_SVR = (uint32_t) WDT_Handler;              /**<  4 SAMA5D2x Watchdog timer Interrupt (WDT) */
	SAIC->AIC_SSR =  5; SAIC->AIC_SVR = (uint32_t) GMAC_Handler;             /**<  5 SAMA5D2x Ethernet MAC (GMAC) */
	SAIC->AIC_SSR =  6; SAIC->AIC_SVR = (uint32_t) XDMAC0_Handler;           /**<  6 SAMA5D2x DMA Controller 0 (XDMAC0) */
	SAIC->AIC_SSR =  7; SAIC->AIC_SVR = (uint32_t) XDMAC1_Handler;           /**<  7 SAMA5D2x DMA Controller 1 (XDMAC1) */
	SAIC->AIC_SSR =  8; SAIC->AIC_SVR = (uint32_t) ICM_Handler;              /**<  8 SAMA5D2x Integritry Check Monitor (ICM) */
	SAIC->AIC_SSR =  9; SAIC->AIC_SVR = (uint32_t) AES_Handler;              /**<  9 SAMA5D2x Advanced Enion Standard (AES) */
	SAIC->AIC_SSR = 10; SAIC->AIC_SVR = (uint32_t) AESB_Handler;             /**< 10 SAMA5D2x AES bridge (AESB) */
	SAIC->AIC_SSR = 11; SAIC->AIC_SVR = (uint32_t) TDES_Handler;             /**< 11 SAMA5D2x Triple Data Enion Standard (TDES) */
	SAIC->AIC_SSR = 12; SAIC->AIC_SVR = (uint32_t) SHA_Handler;              /**< 12 SAMA5D2x SHA Signature (SHA) */
	SAIC->AIC_SSR = 13; SAIC->AIC_SVR = (uint32_t) MPDDRC_Handler;           /**< 13 SAMA5D2x MPDDR controller (MPDDRC) */
	SAIC->AIC_SSR = 14; SAIC->AIC_SVR = (uint32_t) MATRIX1_Handler;          /**< 14 SAMA5D2x H32MX, 32-bit AHB Matrix (MATRIX1) */
	SAIC->AIC_SSR = 15; SAIC->AIC_SVR = (uint32_t) MATRIX0_Handler;          /**< 15 SAMA5D2x H64MX, 64-bit AHB Matrix (MATRIX0) */
	SAIC->AIC_SSR = 17; SAIC->AIC_SVR = (uint32_t) HSMC_Handler;             /**< 17 SAMA5D2x Multi-bit ECC Interrupt (HSMC) */
	SAIC->AIC_SSR = 18; SAIC->AIC_SVR = (uint32_t) PIOA_Handler;             /**< 18 SAMA5D2x Parallel I/O Controller (PIOA) */
	SAIC->AIC_SSR = 19; SAIC->AIC_SVR = (uint32_t) FLEXCOM0_Handler;         /**< 19 SAMA5D2x FLEXCOM 0 (FLEXCOM0) */
	SAIC->AIC_SSR = 20; SAIC->AIC_SVR = (uint32_t) FLEXCOM1_Handler;         /**< 20 SAMA5D2x FLEXCOM 1 (FLEXCOM1) */
	SAIC->AIC_SSR = 21; SAIC->AIC_SVR = (uint32_t) FLEXCOM2_Handler;         /**< 21 SAMA5D2x FLEXCOM 2 (FLEXCOM2) */
	SAIC->AIC_SSR = 22; SAIC->AIC_SVR = (uint32_t) FLEXCOM3_Handler;         /**< 22 SAMA5D2x FLEXCOM 3 (FLEXCOM3) */
	SAIC->AIC_SSR = 23; SAIC->AIC_SVR = (uint32_t) FLEXCOM4_Handler;         /**< 23 SAMA5D2x FLEXCOM 4 (FLEXCOM4) */
	SAIC->AIC_SSR = 24; SAIC->AIC_SVR = (uint32_t) UART0_Handler;            /**< 24 SAMA5D2x UART 0 (UART0) */
	SAIC->AIC_SSR = 25; SAIC->AIC_SVR = (uint32_t) UART1_Handler;            /**< 25 SAMA5D2x UART 1 (UART1) */
	SAIC->AIC_SSR = 26; SAIC->AIC_SVR = (uint32_t) UART2_Handler;            /**< 26 SAMA5D2x UART 2 (UART2) */
	SAIC->AIC_SSR = 27; SAIC->AIC_SVR = (uint32_t) UART3_Handler;            /**< 27 SAMA5D2x UART 3 (UART3) */
	SAIC->AIC_SSR = 28; SAIC->AIC_SVR = (uint32_t) UART4_Handler;            /**< 28 SAMA5D2x UART 4 (UART4) */
	SAIC->AIC_SSR = 29; SAIC->AIC_SVR = (uint32_t) TWIHS0_Handler;           /**< 29 SAMA5D2x Two-Wire Interface 0 (TWIHS0) */
	SAIC->AIC_SSR = 30; SAIC->AIC_SVR = (uint32_t) TWIHS1_Handler;           /**< 30 SAMA5D2x Two-Wire Interface 1 (TWIHS1) */
	SAIC->AIC_SSR = 33; SAIC->AIC_SVR = (uint32_t) SPI0_Handler;             /**< 33 SAMA5D2x Serial Peripheral Interface 0 (SPI0) */
	SAIC->AIC_SSR = 34; SAIC->AIC_SVR = (uint32_t) SPI1_Handler;             /**< 34 SAMA5D2x Serial Peripheral Interface 1 (SPI1) */
	SAIC->AIC_SSR = 35; SAIC->AIC_SVR = (uint32_t) TC0_Handler;              /**< 35 SAMA5D2x Timer Counter 0 (ch. 0, 1, 2) (TC0) */
	SAIC->AIC_SSR = 36; SAIC->AIC_SVR = (uint32_t) TC1_Handler;              /**< 36 SAMA5D2x Timer Counter 1 (ch. 3, 4, 5) (TC1) */
	SAIC->AIC_SSR = 38; SAIC->AIC_SVR = (uint32_t) PWM_Handler;              /**< 38 SAMA5D2x Pulse Width Modulation Controller0 (ch. 0, 1, 2, 3) (PWM) */
	SAIC->AIC_SSR = 40; SAIC->AIC_SVR = (uint32_t) ADC_Handler;              /**< 40 SAMA5D2x Touch Screen ADC Controller (ADC) */
	SAIC->AIC_SSR = 41; SAIC->AIC_SVR = (uint32_t) UHPHS_Handler;            /**< 41 SAMA5D2x USB Host High Speed (UHPHS) */
	SAIC->AIC_SSR = 42; SAIC->AIC_SVR = (uint32_t) UDPHS_Handler;            /**< 42 SAMA5D2x USB Device High Speed (UDPHS) */
	SAIC->AIC_SSR = 43; SAIC->AIC_SVR = (uint32_t) SSC0_Handler;             /**< 43 SAMA5D2x Synchronous Serial Controller 0 (SSC0) */
	SAIC->AIC_SSR = 44; SAIC->AIC_SVR = (uint32_t) SSC1_Handler;             /**< 44 SAMA5D2x Synchronous Serial Controller 1 (SSC1) */
	SAIC->AIC_SSR = 45; SAIC->AIC_SVR = (uint32_t) LCDC_Handler;             /**< 45 SAMA5D2x LCD Controller (LCDC) */
	SAIC->AIC_SSR = 47; SAIC->AIC_SVR = (uint32_t) TRNG_Handler;             /**< 47 SAMA5D2x True Random Number Generator (TRNG) */
	SAIC->AIC_SSR = 48; SAIC->AIC_SVR = (uint32_t) PDMIC_Handler;            /**< 48 SAMA5D2x Pulse Density Modulation Interface Controller (PDMIC) */
	SAIC->AIC_SSR = 50; SAIC->AIC_SVR = (uint32_t) SFC_Handler;              /**< 50 SAMA5D2x Fuse Controller (SFC) */
	SAIC->AIC_SSR = 52; SAIC->AIC_SVR = (uint32_t) QSPI0_Handler;            /**< 52 SAMA5D2x QSPI 0 (QSPI0) */
	SAIC->AIC_SSR = 53; SAIC->AIC_SVR = (uint32_t) QSPI1_Handler;            /**< 53 SAMA5D2x QSPI 1 (QSPI1) */
	SAIC->AIC_SSR = 54; SAIC->AIC_SVR = (uint32_t) I2SC0_Handler;            /**< 54 SAMA5D2x Inter-IC Sound Controller 0 (I2SC0) */
	SAIC->AIC_SSR = 55; SAIC->AIC_SVR = (uint32_t) I2SC1_Handler;            /**< 55 SAMA5D2x Inter-IC Sound Controller 1 (I2SC1) */
	SAIC->AIC_SSR = 59; SAIC->AIC_SVR = (uint32_t) CLASSD_Handler;           /**< 59 SAMA5D2x Audio Class D amplifier (CLASSD) */
	SAIC->AIC_SSR = 60; SAIC->AIC_SVR = (uint32_t) SFR_Handler;              /**< 60 SAMA5D2x Special Function Register  (SFR) */
	SAIC->AIC_SSR = 61; SAIC->AIC_SVR = (uint32_t) SAIC_Handler;             /**< 61 SAMA5D2x Secured Advanced Interrupt Controller  (SAIC) */
	SAIC->AIC_SSR = 62; SAIC->AIC_SVR = (uint32_t) AIC_Handler;              /**< 62 SAMA5D2x Advanced Interrupt Controller  (AIC) */
	SAIC->AIC_SSR = 63; SAIC->AIC_SVR = (uint32_t) L2CC_Handler;             /**< 63 SAMA5D2x L2 Cache Controller (L2CC) */
	SAIC->AIC_SSR = 68; SAIC->AIC_SVR = (uint32_t) PIOB_Handler;             /**< 68 SAMA5D2x  (PIOB) */
	SAIC->AIC_SSR = 69; SAIC->AIC_SVR = (uint32_t) PIOC_Handler;             /**< 69 SAMA5D2x  (PIOC) */
	SAIC->AIC_SSR = 70; SAIC->AIC_SVR = (uint32_t) PIOD_Handler;             /**< 70 SAMA5D2x  (PIOD) */
	SAIC->AIC_SSR = 75; SAIC->AIC_SVR = (uint32_t) ACC_Handler;              /**< 75 SAMA5D2x Analog Comparator (ACC) */
	SAIC->AIC_SSR = 76; SAIC->AIC_SVR = (uint32_t) RXLP_Handler;             /**< 76 SAMA5D2x Uart Low Power (RXLP) */
	SAIC->AIC_SSR = 78; SAIC->AIC_SVR = (uint32_t) CHIPID_Handler;           /**< 78 SAMA5D2x Chip ID (CHIPID) */

	SAIC->AIC_SPU = (uint32_t) Spurious_handler;

	/* Disable all interrupts */
	for (i = 1; i < ID_PERIPH_COUNT; i++){
		SAIC->AIC_SSR = i;
		SAIC->AIC_IDCR = AIC_IDCR_INTD;
	}
	/* Clear All pending interrupts flags */
	for (i = 0; i < ID_PERIPH_COUNT; i++){
		SAIC->AIC_SSR = i;
		SAIC->AIC_ICCR = AIC_ICCR_INTCLR;
	}
	/* Perform 8 IT acknoledge (write any value in EOICR) (VPy) */
	for (i = 0; i < 8; i++){
		SAIC->AIC_EOICR = 0;
	}
	/* Enable IRQ and FIQ at core level */
	v_arm_clr_cpsr_bits(CPSR_MASK_IRQ|CPSR_MASK_FIQ);
}
