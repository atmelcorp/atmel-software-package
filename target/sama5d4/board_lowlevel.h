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

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
void defaultSpuriousHandler(void);
void defaultFiqHandler(void);
void defaultIrqHandler(void);

/* Cortex-A5 core handlers */
/*
*/

void SYS_IrqHandler(void);
void Spurious_handler(void);

/* Peripherals handlers */
void SAIC0_Handler(void);
void ARM_IrqHandler(void);
void PIT_IrqHandler(void);
void WDT_IrqHandler(void);
void PIOD_IrqHandler(void);
void USART0_IrqHandler(void);
void USART1_IrqHandler(void);
void XDMAC0_IrqHandler(void);
void ICM_IrqHandler(void);
void PKCC_IrqHandler(void);
void SCI_IrqHandler(void);
void AES_IrqHandler(void);
void AESB_IrqHandler(void);
void TDES_IrqHandler(void);
void SHA_IrqHandler(void);
void MPDDRC_IrqHandler(void);
void H32MX_IrqHandler(void);
void H64MX_IrqHandler(void);
void VDEC_IrqHandler(void);
void SECUMOD_IrqHandler(void);
void MSADCC_IrqHandler(void);
void HSMC_IrqHandler(void);
void PIOA_IrqHandler(void);
void PIOB_IrqHandler(void);
void PIOC_IrqHandler(void);
void PIOE_IrqHandler(void);
void UART0_IrqHandler(void);
void UART1_IrqHandler(void);
void USART2_IrqHandler(void);
void USART3_IrqHandler(void);
void USART4_IrqHandler(void);
void TWI0_IrqHandler(void);
void TWI1_IrqHandler(void);
void TWI2_IrqHandler(void);
void HSMCI0_IrqHandler(void);
void HSMCI1_IrqHandler(void);
void SPI0_IrqHandler(void);
void SPI1_IrqHandler(void);
void SPI2_IrqHandler(void);
void TC0_IrqHandler(void);
void TC1_IrqHandler(void);
void TC2_IrqHandler(void);
void PWM_IrqHandler(void);
void ADC_IrqHandler(void);
void DBGU_IrqHandler(void);
void UHPHS_IrqHandler(void);
void UDPHS_IrqHandler(void);
void SSC0_IrqHandler(void);
void SSC1_IrqHandler(void);
void XDMAC1_IrqHandler(void);
void LCDC_IrqHandler(void);
void ISI_IrqHandler(void);
void TRNG_IrqHandler(void);
void GMAC0_IrqHandler(void);
void GMAC1_IrqHandler(void);
void AIC0_IrqHandler(void);
void SFC_IrqHandler(void);
void SECURAM_IrqHandler(void);
void CTB_IrqHandler(void);
void SMD_IrqHandler(void);
void TWI3_IrqHandler(void);
void CATB_IrqHandler(void);
void SFR_IrqHandler(void);
void AIC1_IrqHandler(void);
void SAIC1_IrqHandler(void);
void L2CC_IrqHandler(void);
void LowLevelInit(void);

#endif  /* BOARD_LOWLEVEL_H */
