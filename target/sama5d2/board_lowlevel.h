/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation
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
 * Interface for the low-level initialization function.
 *
 */

#ifndef BOARD_LOWLEVEL_H
#define BOARD_LOWLEVEL_H

#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

uint32_t v_arm_read_control(void);
void v_arm_write_control(uint32_t ctl);

void defaultSpuriousHandler(void);
void defaultFiqHandler(void);
void defaultIrqHandler(void);

/* Cortex-A5 core handlers */
/*
*/

void SYS_IrqHandler(void);
void Spurious_handler(void);

/* Peripherals handlers */
void SAIC_Handler(void);
void ARM_Handler(void);
void PIT_Handler(void);
void WDT_Handler(void);
void PIOD_Handler(void);
void USART0_Handler(void);
void USART1_Handler(void);
void XDMAC0_Handler(void);
void ICM_Handler(void);
void PKCC_Handler(void);
void SCI_Handler(void);
void AES_Handler(void);
void AESB_Handler(void);
void TDES_Handler(void);
void SHA_Handler(void);
void MPDDRC_Handler(void);
void H32MX_Handler(void);
void H64MX_Handler(void);
void VDEC_Handler(void);
void SECUMOD_Handler(void);
void MSADCC_Handler(void);
void HSMC_Handler(void);
void PIOA_Handler(void);
void PIOB_Handler(void);
void PIOC_Handler(void);
void PIOE_Handler(void);
void UART0_Handler(void);
void UART1_Handler(void);
void UART2_Handler(void);
void UART3_Handler(void);
void UART4_Handler(void);
void USART2_Handler(void);
void USART3_Handler(void);
void USART4_Handler(void);
void TWI0_Handler(void);
void TWI1_Handler(void);
void TWI2_Handler(void);
void HSMCI0_Handler(void);
void HSMCI1_Handler(void);
void SPI0_Handler(void);
void SPI1_Handler(void);
void SPI2_Handler(void);
void TC0_Handler(void);
void TC1_Handler(void);
void TC2_Handler(void);
void PWM_Handler(void);
void ADC_Handler(void);
void DBGU_Handler(void);
void UHPHS_Handler(void);
void UDPHS_Handler(void);
void SSC0_Handler(void);
void SSC1_Handler(void);
void XDMAC1_Handler(void);
void LCDC_Handler(void);
void ISI_Handler(void);
void TRNG_Handler(void);
void GMAC_Handler(void);
void AIC_Handler(void);
void SFC_Handler(void);
void SECURAM_Handler(void);
void CTB_Handler(void);
void SMD_Handler(void);
void TWI3_Handler(void);
void CATB_Handler(void);
void SFR_Handler(void);
void SAIC1_Handler(void);
void L2CC_Handler(void);
void MATRIX1_Handler(void);
void MATRIX0_Handler(void);
void FLEXCOM0_Handler(void);
void FLEXCOM1_Handler(void);
void FLEXCOM2_Handler(void);
void FLEXCOM3_Handler(void);
void FLEXCOM4_Handler(void);
void TWIHS0_Handler(void);
void TWIHS1_Handler(void);
void QSPI0_Handler(void);
void QSPI1_Handler(void);
void PDMIC_Handler(void);
void I2SC0_Handler(void);
void I2SC1_Handler(void);
void CLASSD_Handler(void);
void ACC_Handler(void);
void RXLP_Handler(void);
void CHIPID_Handler(void);

void low_level_init(void);

#endif  /* BOARD_LOWLEVEL_H */
