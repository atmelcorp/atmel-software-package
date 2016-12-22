/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2015, Atmel Corporation                                        */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Atmel's name may not be used to endorse or promote products derived from     */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR   */
/* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE   */
/* DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,      */
/* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,  */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    */
/* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING         */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/* ---------------------------------------------------------------------------- */

#ifndef _SAMA5D43_PIO_
#define _SAMA5D43_PIO_

#define PIO_PA0              (1u << 0)	/**< \brief Pin Controlled by PA0 */
#define PIO_PA1              (1u << 1)	/**< \brief Pin Controlled by PA1 */
#define PIO_PA2              (1u << 2)	/**< \brief Pin Controlled by PA2 */
#define PIO_PA3              (1u << 3)	/**< \brief Pin Controlled by PA3 */
#define PIO_PA4              (1u << 4)	/**< \brief Pin Controlled by PA4 */
#define PIO_PA5              (1u << 5)	/**< \brief Pin Controlled by PA5 */
#define PIO_PA6              (1u << 6)	/**< \brief Pin Controlled by PA6 */
#define PIO_PA7              (1u << 7)	/**< \brief Pin Controlled by PA7 */
#define PIO_PA8              (1u << 8)	/**< \brief Pin Controlled by PA8 */
#define PIO_PA9              (1u << 9)	/**< \brief Pin Controlled by PA9 */
#define PIO_PA10             (1u << 10)	/**< \brief Pin Controlled by PA10 */
#define PIO_PA11             (1u << 11)	/**< \brief Pin Controlled by PA11 */
#define PIO_PA12             (1u << 12)	/**< \brief Pin Controlled by PA12 */
#define PIO_PA13             (1u << 13)	/**< \brief Pin Controlled by PA13 */
#define PIO_PA14             (1u << 14)	/**< \brief Pin Controlled by PA14 */
#define PIO_PA15             (1u << 15)	/**< \brief Pin Controlled by PA15 */
#define PIO_PA16             (1u << 16)	/**< \brief Pin Controlled by PA16 */
#define PIO_PA17             (1u << 17)	/**< \brief Pin Controlled by PA17 */
#define PIO_PA18             (1u << 18)	/**< \brief Pin Controlled by PA18 */
#define PIO_PA19             (1u << 19)	/**< \brief Pin Controlled by PA19 */
#define PIO_PA20             (1u << 20)	/**< \brief Pin Controlled by PA20 */
#define PIO_PA21             (1u << 21)	/**< \brief Pin Controlled by PA21 */
#define PIO_PA22             (1u << 22)	/**< \brief Pin Controlled by PA22 */
#define PIO_PA23             (1u << 23)	/**< \brief Pin Controlled by PA23 */
#define PIO_PA24             (1u << 24)	/**< \brief Pin Controlled by PA24 */
#define PIO_PA25             (1u << 25)	/**< \brief Pin Controlled by PA25 */
#define PIO_PA26             (1u << 26)	/**< \brief Pin Controlled by PA26 */
#define PIO_PA27             (1u << 27)	/**< \brief Pin Controlled by PA27 */
#define PIO_PA28             (1u << 28)	/**< \brief Pin Controlled by PA28 */
#define PIO_PA29             (1u << 29)	/**< \brief Pin Controlled by PA29 */
#define PIO_PA30             (1u << 30)	/**< \brief Pin Controlled by PA30 */
#define PIO_PA31             (1u << 31)	/**< \brief Pin Controlled by PA31 */
#define PIO_PB0              (1u << 0)	/**< \brief Pin Controlled by PB0 */
#define PIO_PB1              (1u << 1)	/**< \brief Pin Controlled by PB1 */
#define PIO_PB2              (1u << 2)	/**< \brief Pin Controlled by PB2 */
#define PIO_PB3              (1u << 3)	/**< \brief Pin Controlled by PB3 */
#define PIO_PB4              (1u << 4)	/**< \brief Pin Controlled by PB4 */
#define PIO_PB5              (1u << 5)	/**< \brief Pin Controlled by PB5 */
#define PIO_PB6              (1u << 6)	/**< \brief Pin Controlled by PB6 */
#define PIO_PB7              (1u << 7)	/**< \brief Pin Controlled by PB7 */
#define PIO_PB8              (1u << 8)	/**< \brief Pin Controlled by PB8 */
#define PIO_PB9              (1u << 9)	/**< \brief Pin Controlled by PB9 */
#define PIO_PB10             (1u << 10)	/**< \brief Pin Controlled by PB10 */
#define PIO_PB11             (1u << 11)	/**< \brief Pin Controlled by PB11 */
#define PIO_PB12             (1u << 12)	/**< \brief Pin Controlled by PB12 */
#define PIO_PB13             (1u << 13)	/**< \brief Pin Controlled by PB13 */
#define PIO_PB14             (1u << 14)	/**< \brief Pin Controlled by PB14 */
#define PIO_PB15             (1u << 15)	/**< \brief Pin Controlled by PB15 */
#define PIO_PB16             (1u << 16)	/**< \brief Pin Controlled by PB16 */
#define PIO_PB17             (1u << 17)	/**< \brief Pin Controlled by PB17 */
#define PIO_PB18             (1u << 18)	/**< \brief Pin Controlled by PB18 */
#define PIO_PB19             (1u << 19)	/**< \brief Pin Controlled by PB19 */
#define PIO_PB20             (1u << 20)	/**< \brief Pin Controlled by PB20 */
#define PIO_PB21             (1u << 21)	/**< \brief Pin Controlled by PB21 */
#define PIO_PB22             (1u << 22)	/**< \brief Pin Controlled by PB22 */
#define PIO_PB23             (1u << 23)	/**< \brief Pin Controlled by PB23 */
#define PIO_PB24             (1u << 24)	/**< \brief Pin Controlled by PB24 */
#define PIO_PB25             (1u << 25)	/**< \brief Pin Controlled by PB25 */
#define PIO_PB26             (1u << 26)	/**< \brief Pin Controlled by PB26 */
#define PIO_PB27             (1u << 27)	/**< \brief Pin Controlled by PB27 */
#define PIO_PB28             (1u << 28)	/**< \brief Pin Controlled by PB28 */
#define PIO_PB29             (1u << 29)	/**< \brief Pin Controlled by PB29 */
#define PIO_PB30             (1u << 30)	/**< \brief Pin Controlled by PB30 */
#define PIO_PB31             (1u << 31)	/**< \brief Pin Controlled by PB31 */
#define PIO_PC0              (1u << 0)	/**< \brief Pin Controlled by PC0 */
#define PIO_PC1              (1u << 1)	/**< \brief Pin Controlled by PC1 */
#define PIO_PC2              (1u << 2)	/**< \brief Pin Controlled by PC2 */
#define PIO_PC3              (1u << 3)	/**< \brief Pin Controlled by PC3 */
#define PIO_PC4              (1u << 4)	/**< \brief Pin Controlled by PC4 */
#define PIO_PC5              (1u << 5)	/**< \brief Pin Controlled by PC5 */
#define PIO_PC6              (1u << 6)	/**< \brief Pin Controlled by PC6 */
#define PIO_PC7              (1u << 7)	/**< \brief Pin Controlled by PC7 */
#define PIO_PC8              (1u << 8)	/**< \brief Pin Controlled by PC8 */
#define PIO_PC9              (1u << 9)	/**< \brief Pin Controlled by PC9 */
#define PIO_PC10             (1u << 10)	/**< \brief Pin Controlled by PC10 */
#define PIO_PC11             (1u << 11)	/**< \brief Pin Controlled by PC11 */
#define PIO_PC12             (1u << 12)	/**< \brief Pin Controlled by PC12 */
#define PIO_PC13             (1u << 13)	/**< \brief Pin Controlled by PC13 */
#define PIO_PC14             (1u << 14)	/**< \brief Pin Controlled by PC14 */
#define PIO_PC15             (1u << 15)	/**< \brief Pin Controlled by PC15 */
#define PIO_PC16             (1u << 16)	/**< \brief Pin Controlled by PC16 */
#define PIO_PC17             (1u << 17)	/**< \brief Pin Controlled by PC17 */
#define PIO_PC18             (1u << 18)	/**< \brief Pin Controlled by PC18 */
#define PIO_PC27             (1u << 27)	/**< \brief Pin Controlled by PC27 */
#define PIO_PC28             (1u << 28)	/**< \brief Pin Controlled by PC28 */
#define PIO_PC29             (1u << 29)	/**< \brief Pin Controlled by PC29 */
#define PIO_PC30             (1u << 30)	/**< \brief Pin Controlled by PC30 */
#define PIO_PC31             (1u << 31)	/**< \brief Pin Controlled by PC31 */
#define PIO_PD0              (1u << 0)	/**< \brief Pin Controlled by PD0 */
#define PIO_PD1              (1u << 1)	/**< \brief Pin Controlled by PD1 */
#define PIO_PD2              (1u << 2)	/**< \brief Pin Controlled by PD2 */
#define PIO_PD3              (1u << 3)	/**< \brief Pin Controlled by PD3 */
#define PIO_PD4              (1u << 4)	/**< \brief Pin Controlled by PD4 */
#define PIO_PD5              (1u << 5)	/**< \brief Pin Controlled by PD5 */
#define PIO_PD6              (1u << 6)	/**< \brief Pin Controlled by PD6 */
#define PIO_PD7              (1u << 7)	/**< \brief Pin Controlled by PD7 */
#define PIO_PD8              (1u << 8)	/**< \brief Pin Controlled by PD8 */
#define PIO_PD9              (1u << 9)	/**< \brief Pin Controlled by PD9 */
#define PIO_PD10             (1u << 10)	/**< \brief Pin Controlled by PD10 */
#define PIO_PD11             (1u << 11)	/**< \brief Pin Controlled by PD11 */
#define PIO_PD12             (1u << 12)	/**< \brief Pin Controlled by PD12 */
#define PIO_PD13             (1u << 13)	/**< \brief Pin Controlled by PD13 */
#define PIO_PD14             (1u << 14)	/**< \brief Pin Controlled by PD14 */
#define PIO_PD15             (1u << 15)	/**< \brief Pin Controlled by PD15 */
#define PIO_PD16             (1u << 16)	/**< \brief Pin Controlled by PD16 */
#define PIO_PD17             (1u << 17)	/**< \brief Pin Controlled by PD17 */
#define PIO_PD18             (1u << 18)	/**< \brief Pin Controlled by PD18 */
#define PIO_PD19             (1u << 19)	/**< \brief Pin Controlled by PD19 */
#define PIO_PD20             (1u << 20)	/**< \brief Pin Controlled by PD20 */
#define PIO_PD21             (1u << 21)	/**< \brief Pin Controlled by PD21 */
#define PIO_PD22             (1u << 22)	/**< \brief Pin Controlled by PD22 */
#define PIO_PD23             (1u << 23)	/**< \brief Pin Controlled by PD23 */
#define PIO_PD24             (1u << 24)	/**< \brief Pin Controlled by PD24 */
#define PIO_PD25             (1u << 25)	/**< \brief Pin Controlled by PD25 */
#define PIO_PD26             (1u << 26)	/**< \brief Pin Controlled by PD26 */
#define PIO_PD27             (1u << 27)	/**< \brief Pin Controlled by PD27 */
#define PIO_PD28             (1u << 28)	/**< \brief Pin Controlled by PD28 */
#define PIO_PD29             (1u << 29)	/**< \brief Pin Controlled by PD29 */
#define PIO_PD30             (1u << 30)	/**< \brief Pin Controlled by PD30 */
#define PIO_PD31             (1u << 31)	/**< \brief Pin Controlled by PD31 */
#define PIO_PE0              (1u << 0)	/**< \brief Pin Controlled by PE0 */
#define PIO_PE1              (1u << 1)	/**< \brief Pin Controlled by PE1 */
#define PIO_PE2              (1u << 2)	/**< \brief Pin Controlled by PE2 */
#define PIO_PE3              (1u << 3)	/**< \brief Pin Controlled by PE3 */
#define PIO_PE4              (1u << 4)	/**< \brief Pin Controlled by PE4 */
#define PIO_PE5              (1u << 5)	/**< \brief Pin Controlled by PE5 */
#define PIO_PE6              (1u << 6)	/**< \brief Pin Controlled by PE6 */
#define PIO_PE7              (1u << 7)	/**< \brief Pin Controlled by PE7 */
#define PIO_PE8              (1u << 8)	/**< \brief Pin Controlled by PE8 */
#define PIO_PE9              (1u << 9)	/**< \brief Pin Controlled by PE9 */
#define PIO_PE10             (1u << 10)	/**< \brief Pin Controlled by PE10 */
#define PIO_PE11             (1u << 11)	/**< \brief Pin Controlled by PE11 */
#define PIO_PE12             (1u << 12)	/**< \brief Pin Controlled by PE12 */
#define PIO_PE13             (1u << 13)	/**< \brief Pin Controlled by PE13 */
#define PIO_PE14             (1u << 14)	/**< \brief Pin Controlled by PE14 */
#define PIO_PE15             (1u << 15)	/**< \brief Pin Controlled by PE15 */
#define PIO_PE16             (1u << 16)	/**< \brief Pin Controlled by PE16 */
#define PIO_PE17             (1u << 17)	/**< \brief Pin Controlled by PE17 */
#define PIO_PE24             (1u << 24)	/**< \brief Pin Controlled by PE24 */
#define PIO_PE25             (1u << 25)	/**< \brief Pin Controlled by PE25 */
#define PIO_PE26             (1u << 26)	/**< \brief Pin Controlled by PE26 */
#define PIO_PE27             (1u << 27)	/**< \brief Pin Controlled by PE27 */
#define PIO_PE28             (1u << 28)	/**< \brief Pin Controlled by PE28 */
#define PIO_PE29             (1u << 29)	/**< \brief Pin Controlled by PE29 */
#define PIO_PE30             (1u << 30)	/**< \brief Pin Controlled by PE30 */
#define PIO_PE31             (1u << 31)	/**< \brief Pin Controlled by PE31 */
/* ========== Pio definition for ADC peripheral ========== */
#define PIO_PC27X1_AD0       (1u << 27)	/**< \brief Adc signal: AD0 */
#define PIO_PC28X1_AD1       (1u << 28)	/**< \brief Adc signal: AD1 */
#define PIO_PC29X1_AD2       (1u << 29)	/**< \brief Adc signal: AD2 */
#define PIO_PC30X1_AD3       (1u << 30)	/**< \brief Adc signal: AD3 */
#define PIO_PC31X1_AD4       (1u << 31)	/**< \brief Adc signal: AD4 */
#define PIO_PE31A_ADTRG      (1u << 31)	/**< \brief Adc signal: ADTRG */
/* ========== Pio definition for AIC peripheral ========== */
#define PIO_PD9A_FIQ         (1u << 9)	/**< \brief Aic signal: FIQ */
#define PIO_PE25C_IRQ        (1u << 25)	/**< \brief Aic signal: IRQ */
/* ========== Pio definition for ARM peripheral ========== */
#define PIO_PA16C_NTRST      (1u << 16)	/**< \brief Arm signal: NTRST */
#define PIO_PA8C_TCK         (1u << 8)	/**< \brief Arm signal: TCK */
#define PIO_PB24C_TDI        (1u << 24)	/**< \brief Arm signal: TDI */
#define PIO_PB25C_TDO        (1u << 25)	/**< \brief Arm signal: TDO */
#define PIO_PA0C_TMS         (1u << 0)	/**< \brief Arm signal: TMS */
/* ========== Pio definition for DBGU peripheral ========== */
#define PIO_PB24A_DRXD       (1u << 24)	/**< \brief Dbgu signal: DRXD */
#define PIO_PB25A_DTXD       (1u << 25)	/**< \brief Dbgu signal: DTXD */
/* ========== Pio definition for EBI peripheral ========== */
#define PIO_PE0A_A0          (1u << 0)	/**< \brief Ebi signal: A0/NBS0 */
#define PIO_PE0A_NBS0        (1u << 0)	/**< \brief Ebi signal: A0/NBS0 */
#define PIO_PE1A_A1          (1u << 1)	/**< \brief Ebi signal: A1 */
#define PIO_PE10A_A10        (1u << 10)	/**< \brief Ebi signal: A10 */
#define PIO_PE11A_A11        (1u << 11)	/**< \brief Ebi signal: A11 */
#define PIO_PE12A_A12        (1u << 12)	/**< \brief Ebi signal: A12 */
#define PIO_PE13A_A13        (1u << 13)	/**< \brief Ebi signal: A13 */
#define PIO_PE14A_A14        (1u << 14)	/**< \brief Ebi signal: A14 */
#define PIO_PE15A_A15        (1u << 15)	/**< \brief Ebi signal: A15 */
#define PIO_PE16A_A16        (1u << 16)	/**< \brief Ebi signal: A16 */
#define PIO_PE17A_A17        (1u << 17)	/**< \brief Ebi signal: A17 */
#define PIO_PE18A_A18        (1u << 18)	/**< \brief Ebi signal: A18 */
#define PIO_PE26C_A18        (1u << 26)	/**< \brief Ebi signal: A18 */
#define PIO_PE19A_A19        (1u << 19)	/**< \brief Ebi signal: A19 */
#define PIO_PE28C_A19        (1u << 28)	/**< \brief Ebi signal: A19 */
#define PIO_PE2A_A2          (1u << 2)	/**< \brief Ebi signal: A2 */
#define PIO_PE20A_A20        (1u << 20)	/**< \brief Ebi signal: A20 */
#define PIO_PC17A_A21        (1u << 17)	/**< \brief Ebi signal: A21/NANDALE */
#define PIO_PC17A_NANDALE    (1u << 17)	/**< \brief Ebi signal: A21/NANDALE */
#define PIO_PC18A_A22        (1u << 18)	/**< \brief Ebi signal: A22/NANDCLE */
#define PIO_PC18A_NANDCLE    (1u << 18)	/**< \brief Ebi signal: A22/NANDCLE */
#define PIO_PE21A_A23        (1u << 21)	/**< \brief Ebi signal: A23 */
#define PIO_PE22A_A24        (1u << 22)	/**< \brief Ebi signal: A24 */
#define PIO_PE23A_A25        (1u << 23)	/**< \brief Ebi signal: A25 */
#define PIO_PE3A_A3          (1u << 3)	/**< \brief Ebi signal: A3 */
#define PIO_PE4A_A4          (1u << 4)	/**< \brief Ebi signal: A4 */
#define PIO_PE5A_A5          (1u << 5)	/**< \brief Ebi signal: A5 */
#define PIO_PE6A_A6          (1u << 6)	/**< \brief Ebi signal: A6 */
#define PIO_PE7A_A7          (1u << 7)	/**< \brief Ebi signal: A7 */
#define PIO_PE8A_A8          (1u << 8)	/**< \brief Ebi signal: A8 */
#define PIO_PE9A_A9          (1u << 9)	/**< \brief Ebi signal: A9 */
#define PIO_PC5A_D0          (1u << 5)	/**< \brief Ebi signal: D0 */
#define PIO_PC6A_D1          (1u << 6)	/**< \brief Ebi signal: D1 */
#define PIO_PB20B_D10        (1u << 20)	/**< \brief Ebi signal: D10 */
#define PIO_PB21B_D11        (1u << 21)	/**< \brief Ebi signal: D11 */
#define PIO_PB22B_D12        (1u << 22)	/**< \brief Ebi signal: D12 */
#define PIO_PB23B_D13        (1u << 23)	/**< \brief Ebi signal: D13 */
#define PIO_PB24B_D14        (1u << 24)	/**< \brief Ebi signal: D14 */
#define PIO_PB25B_D15        (1u << 25)	/**< \brief Ebi signal: D15 */
#define PIO_PC7A_D2          (1u << 7)	/**< \brief Ebi signal: D2 */
#define PIO_PC8A_D3          (1u << 8)	/**< \brief Ebi signal: D3 */
#define PIO_PC9A_D4          (1u << 9)	/**< \brief Ebi signal: D4 */
#define PIO_PC10A_D5         (1u << 10)	/**< \brief Ebi signal: D5 */
#define PIO_PC11A_D6         (1u << 11)	/**< \brief Ebi signal: D6 */
#define PIO_PC12A_D7         (1u << 12)	/**< \brief Ebi signal: D7 */
#define PIO_PB18B_D8         (1u << 18)	/**< \brief Ebi signal: D8 */
#define PIO_PB19B_D9         (1u << 19)	/**< \brief Ebi signal: D9 */
#define PIO_PC16A_NANDRDY    (1u << 16)	/**< \brief Ebi signal: NANDRDY */
#define PIO_PE24A_NCS0       (1u << 24)	/**< \brief Ebi signal: NCS0 */
#define PIO_PE25A_NCS1       (1u << 25)	/**< \brief Ebi signal: NCS1 */
#define PIO_PE26A_NCS2       (1u << 26)	/**< \brief Ebi signal: NCS2 */
#define PIO_PC15A_NCS3       (1u << 15)	/**< \brief Ebi signal: NCS3 */
#define PIO_PC13A_NRD        (1u << 13)	/**< \brief Ebi signal: NRD/NANDOE */
#define PIO_PC13A_NANDOE     (1u << 13)	/**< \brief Ebi signal: NRD/NANDOE */
#define PIO_PE28A_NWAIT      (1u << 28)	/**< \brief Ebi signal: NWAIT */
#define PIO_PC14A_NWE        (1u << 14)	/**< \brief Ebi signal: NWE/NANDWE */
#define PIO_PC14A_NANDWE     (1u << 14)	/**< \brief Ebi signal: NWE/NANDWE */
#define PIO_PE27A_NWR1       (1u << 27)	/**< \brief Ebi signal: NWR1/NBS1 */
#define PIO_PE27A_NBS1       (1u << 27)	/**< \brief Ebi signal: NWR1/NBS1 */
/* ========== Pio definition for GMAC0 peripheral ========== */
#define PIO_PB5A_G0_COL      (1u << 5)	/**< \brief Gmac0 signal: G0_COL */
#define PIO_PB4A_G0_CRS      (1u << 4)	/**< \brief Gmac0 signal: G0_CRS */
#define PIO_PB16A_G0_MDC     (1u << 16)	/**< \brief Gmac0 signal: G0_MDC */
#define PIO_PB17A_G0_MDIO    (1u << 17)	/**< \brief Gmac0 signal: G0_MDIO */
#define PIO_PB8A_G0_RX0      (1u << 8)	/**< \brief Gmac0 signal: G0_RX0 */
#define PIO_PB9A_G0_RX1      (1u << 9)	/**< \brief Gmac0 signal: G0_RX1 */
#define PIO_PB10A_G0_RX2     (1u << 10)	/**< \brief Gmac0 signal: G0_RX2 */
#define PIO_PB11A_G0_RX3     (1u << 11)	/**< \brief Gmac0 signal: G0_RX3 */
#define PIO_PB1A_G0_RXCK     (1u << 1)	/**< \brief Gmac0 signal: G0_RXCK */
#define PIO_PB6A_G0_RXDV     (1u << 6)	/**< \brief Gmac0 signal: G0_RXDV */
#define PIO_PB7A_G0_RXER     (1u << 7)	/**< \brief Gmac0 signal: G0_RXER */
#define PIO_PB12A_G0_TX0     (1u << 12)	/**< \brief Gmac0 signal: G0_TX0 */
#define PIO_PB13A_G0_TX1     (1u << 13)	/**< \brief Gmac0 signal: G0_TX1 */
#define PIO_PB14A_G0_TX2     (1u << 14)	/**< \brief Gmac0 signal: G0_TX2 */
#define PIO_PB15A_G0_TX3     (1u << 15)	/**< \brief Gmac0 signal: G0_TX3 */
#define PIO_PB0A_G0_TXCK     (1u << 0)	/**< \brief Gmac0 signal: G0_TXCK */
#define PIO_PB2A_G0_TXEN     (1u << 2)	/**< \brief Gmac0 signal: G0_TXEN */
#define PIO_PB3A_G0_TXER     (1u << 3)	/**< \brief Gmac0 signal: G0_TXER */
/* ========== Pio definition for GMAC1 peripheral ========== */
#define PIO_PA9B_G1_COL      (1u << 9)	/**< \brief Gmac1 signal: G1_COL */
#define PIO_PA6B_G1_CRS      (1u << 6)	/**< \brief Gmac1 signal: G1_CRS */
#define PIO_PA22B_G1_MDC     (1u << 22)	/**< \brief Gmac1 signal: G1_MDC */
#define PIO_PA23B_G1_MDIO    (1u << 23)	/**< \brief Gmac1 signal: G1_MDIO */
#define PIO_PA12B_G1_RX0     (1u << 12)	/**< \brief Gmac1 signal: G1_RX0 */
#define PIO_PA13B_G1_RX1     (1u << 13)	/**< \brief Gmac1 signal: G1_RX1 */
#define PIO_PA18B_G1_RX2     (1u << 18)	/**< \brief Gmac1 signal: G1_RX2 */
#define PIO_PA19B_G1_RX3     (1u << 19)	/**< \brief Gmac1 signal: G1_RX3 */
#define PIO_PA3B_G1_RXCK     (1u << 3)	/**< \brief Gmac1 signal: G1_RXCK */
#define PIO_PA10B_G1_RXDV    (1u << 10)	/**< \brief Gmac1 signal: G1_RXDV */
#define PIO_PA11B_G1_RXER    (1u << 11)	/**< \brief Gmac1 signal: G1_RXER */
#define PIO_PA14B_G1_TX0     (1u << 14)	/**< \brief Gmac1 signal: G1_TX0 */
#define PIO_PA15B_G1_TX1     (1u << 15)	/**< \brief Gmac1 signal: G1_TX1 */
#define PIO_PA20B_G1_TX2     (1u << 20)	/**< \brief Gmac1 signal: G1_TX2 */
#define PIO_PA21B_G1_TX3     (1u << 21)	/**< \brief Gmac1 signal: G1_TX3 */
#define PIO_PA2B_G1_TXCK     (1u << 2)	/**< \brief Gmac1 signal: G1_TXCK */
#define PIO_PA4B_G1_TXEN     (1u << 4)	/**< \brief Gmac1 signal: G1_TXEN */
#define PIO_PA5B_G1_TXER     (1u << 5)	/**< \brief Gmac1 signal: G1_TXER */
/* ========== Pio definition for HSMCI0 peripheral ========== */
#define PIO_PC5B_MCI0_CDA    (1u << 5)	/**< \brief Hsmci0 signal: MCI0_CDA */
#define PIO_PE0B_MCI0_CDB    (1u << 0)	/**< \brief Hsmci0 signal: MCI0_CDB */
#define PIO_PC4B_MCI0_CK     (1u << 4)	/**< \brief Hsmci0 signal: MCI0_CK */
#define PIO_PC6B_MCI0_DA0    (1u << 6)	/**< \brief Hsmci0 signal: MCI0_DA0 */
#define PIO_PC7B_MCI0_DA1    (1u << 7)	/**< \brief Hsmci0 signal: MCI0_DA1 */
#define PIO_PC8B_MCI0_DA2    (1u << 8)	/**< \brief Hsmci0 signal: MCI0_DA2 */
#define PIO_PC9B_MCI0_DA3    (1u << 9)	/**< \brief Hsmci0 signal: MCI0_DA3 */
#define PIO_PC10B_MCI0_DA4   (1u << 10)	/**< \brief Hsmci0 signal: MCI0_DA4 */
#define PIO_PC11B_MCI0_DA5   (1u << 11)	/**< \brief Hsmci0 signal: MCI0_DA5 */
#define PIO_PC12B_MCI0_DA6   (1u << 12)	/**< \brief Hsmci0 signal: MCI0_DA6 */
#define PIO_PC13B_MCI0_DA7   (1u << 13)	/**< \brief Hsmci0 signal: MCI0_DA7 */
#define PIO_PE1B_MCI0_DB0    (1u << 1)	/**< \brief Hsmci0 signal: MCI0_DB0 */
#define PIO_PE2B_MCI0_DB1    (1u << 2)	/**< \brief Hsmci0 signal: MCI0_DB1 */
#define PIO_PE3B_MCI0_DB2    (1u << 3)	/**< \brief Hsmci0 signal: MCI0_DB2 */
#define PIO_PE4B_MCI0_DB3    (1u << 4)	/**< \brief Hsmci0 signal: MCI0_DB3 */
/* ========== Pio definition for HSMCI1 peripheral ========== */
#define PIO_PE19C_MCI1_CDA   (1u << 19)	/**< \brief Hsmci1 signal: MCI1_CDA */
#define PIO_PE18C_MCI1_CK    (1u << 18)	/**< \brief Hsmci1 signal: MCI1_CK */
#define PIO_PE20C_MCI1_DA0   (1u << 20)	/**< \brief Hsmci1 signal: MCI1_DA0 */
#define PIO_PE21C_MCI1_DA1   (1u << 21)	/**< \brief Hsmci1 signal: MCI1_DA1 */
#define PIO_PE22C_MCI1_DA2   (1u << 22)	/**< \brief Hsmci1 signal: MCI1_DA2 */
#define PIO_PE23C_MCI1_DA3   (1u << 23)	/**< \brief Hsmci1 signal: MCI1_DA3 */
/* ========== Pio definition for ISI peripheral ========== */
#define PIO_PC19A_ISI_D0     (1u << 19)	/**< \brief Isi signal: ISI_D0 */
#define PIO_PC20A_ISI_D1     (1u << 20)	/**< \brief Isi signal: ISI_D1 */
#define PIO_PC2C_ISI_D10     (1u << 2)	/**< \brief Isi signal: ISI_D10 */
#define PIO_PC3C_ISI_D11     (1u << 3)	/**< \brief Isi signal: ISI_D11 */
#define PIO_PC21A_ISI_D2     (1u << 21)	/**< \brief Isi signal: ISI_D2 */
#define PIO_PC22A_ISI_D3     (1u << 22)	/**< \brief Isi signal: ISI_D3 */
#define PIO_PC23A_ISI_D4     (1u << 23)	/**< \brief Isi signal: ISI_D4 */
#define PIO_PC24A_ISI_D5     (1u << 24)	/**< \brief Isi signal: ISI_D5 */
#define PIO_PC25A_ISI_D6     (1u << 25)	/**< \brief Isi signal: ISI_D6 */
#define PIO_PC26A_ISI_D7     (1u << 26)	/**< \brief Isi signal: ISI_D7 */
#define PIO_PC0C_ISI_D8      (1u << 0)	/**< \brief Isi signal: ISI_D8 */
#define PIO_PC1C_ISI_D9      (1u << 1)	/**< \brief Isi signal: ISI_D9 */
#define PIO_PB4C_ISI_HSYNC   (1u << 4)	/**< \brief Isi signal: ISI_HSYNC */
#define PIO_PB1C_ISI_PCK     (1u << 1)	/**< \brief Isi signal: ISI_PCK */
#define PIO_PB3C_ISI_VSYNC   (1u << 3)	/**< \brief Isi signal: ISI_VSYNC */
/* ========== Pio definition for LCDC peripheral ========== */
#define PIO_PA0A_LCDDAT0     (1u << 0)	/**< \brief Lcdc signal: LCDDAT0 */
#define PIO_PA1A_LCDDAT1     (1u << 1)	/**< \brief Lcdc signal: LCDDAT1 */
#define PIO_PA10A_LCDDAT10   (1u << 10)	/**< \brief Lcdc signal: LCDDAT10 */
#define PIO_PA11A_LCDDAT11   (1u << 11)	/**< \brief Lcdc signal: LCDDAT11 */
#define PIO_PA12A_LCDDAT12   (1u << 12)	/**< \brief Lcdc signal: LCDDAT12 */
#define PIO_PA13A_LCDDAT13   (1u << 13)	/**< \brief Lcdc signal: LCDDAT13 */
#define PIO_PA14A_LCDDAT14   (1u << 14)	/**< \brief Lcdc signal: LCDDAT14 */
#define PIO_PA15A_LCDDAT15   (1u << 15)	/**< \brief Lcdc signal: LCDDAT15 */
#define PIO_PA16A_LCDDAT16   (1u << 16)	/**< \brief Lcdc signal: LCDDAT16 */
#define PIO_PA17A_LCDDAT17   (1u << 17)	/**< \brief Lcdc signal: LCDDAT17 */
#define PIO_PA18A_LCDDAT18   (1u << 18)	/**< \brief Lcdc signal: LCDDAT18 */
#define PIO_PA19A_LCDDAT19   (1u << 19)	/**< \brief Lcdc signal: LCDDAT19 */
#define PIO_PA2A_LCDDAT2     (1u << 2)	/**< \brief Lcdc signal: LCDDAT2 */
#define PIO_PA20A_LCDDAT20   (1u << 20)	/**< \brief Lcdc signal: LCDDAT20 */
#define PIO_PA21A_LCDDAT21   (1u << 21)	/**< \brief Lcdc signal: LCDDAT21 */
#define PIO_PA22A_LCDDAT22   (1u << 22)	/**< \brief Lcdc signal: LCDDAT22 */
#define PIO_PA23A_LCDDAT23   (1u << 23)	/**< \brief Lcdc signal: LCDDAT23 */
#define PIO_PA3A_LCDDAT3     (1u << 3)	/**< \brief Lcdc signal: LCDDAT3 */
#define PIO_PA4A_LCDDAT4     (1u << 4)	/**< \brief Lcdc signal: LCDDAT4 */
#define PIO_PA5A_LCDDAT5     (1u << 5)	/**< \brief Lcdc signal: LCDDAT5 */
#define PIO_PA6A_LCDDAT6     (1u << 6)	/**< \brief Lcdc signal: LCDDAT6 */
#define PIO_PA7A_LCDDAT7     (1u << 7)	/**< \brief Lcdc signal: LCDDAT7 */
#define PIO_PA8A_LCDDAT8     (1u << 8)	/**< \brief Lcdc signal: LCDDAT8 */
#define PIO_PA9A_LCDDAT9     (1u << 9)	/**< \brief Lcdc signal: LCDDAT9 */
#define PIO_PA29A_LCDDEN     (1u << 29)	/**< \brief Lcdc signal: LCDDEN */
#define PIO_PA25A_LCDDISP    (1u << 25)	/**< \brief Lcdc signal: LCDDISP */
#define PIO_PA27A_LCDHSYNC   (1u << 27)	/**< \brief Lcdc signal: LCDHSYNC */
#define PIO_PA28A_LCDPCK     (1u << 28)	/**< \brief Lcdc signal: LCDPCK */
#define PIO_PA24A_LCDPWM     (1u << 24)	/**< \brief Lcdc signal: LCDPWM */
#define PIO_PA26A_LCDVSYNC   (1u << 26)	/**< \brief Lcdc signal: LCDVSYNC */
/* ========== Pio definition for PMC peripheral ========== */
#define PIO_PA24B_PCK0       (1u << 24)	/**< \brief Pmc signal: PCK0 */
#define PIO_PB26A_PCK0       (1u << 26)	/**< \brief Pmc signal: PCK0 */
#define PIO_PD8A_PCK0        (1u << 8)	/**< \brief Pmc signal: PCK0 */
#define PIO_PC4C_PCK1        (1u << 4)	/**< \brief Pmc signal: PCK1 */
#define PIO_PC24C_PCK1       (1u << 24)	/**< \brief Pmc signal: PCK1 */
#define PIO_PD31B_PCK1       (1u << 31)	/**< \brief Pmc signal: PCK1 */
#define PIO_PB5C_PCK2        (1u << 5)	/**< \brief Pmc signal: PCK2 */
#define PIO_PB10B_PCK2       (1u << 10)	/**< \brief Pmc signal: PCK2 */
/* ========== Pio definition for PWM0 peripheral ========== */
#define PIO_PC29C_PWM0_FI0   (1u << 29)	/**< \brief Pwm signal: PWM0_FI0 */
#define PIO_PE7C_PWM0_FI1    (1u << 7)	/**< \brief Pwm signal: PWM0_FI1 */
#define PIO_PA26B_PWM0_H0    (1u << 26)	/**< \brief Pwm signal: PWM0_H0 */
#define PIO_PB14C_PWM0_H0    (1u << 14)	/**< \brief Pwm signal: PWM0_H0 */
#define PIO_PB26C_PWM0_H0    (1u << 26)	/**< \brief Pwm signal: PWM0_H0 */
#define PIO_PC30C_PWM0_H0    (1u << 30)	/**< \brief Pwm signal: PWM0_H0 */
#define PIO_PA28B_PWM0_H1    (1u << 28)	/**< \brief Pwm signal: PWM0_H1 */
#define PIO_PB11C_PWM0_H1    (1u << 11)	/**< \brief Pwm signal: PWM0_H1 */
#define PIO_PB28C_PWM0_H1    (1u << 28)	/**< \brief Pwm signal: PWM0_H1 */
#define PIO_PC31C_PWM0_H1    (1u << 31)	/**< \brief Pwm signal: PWM0_H1 */
#define PIO_PC0B_PWM0_H2     (1u << 0)	/**< \brief Pwm signal: PWM0_H2 */
#define PIO_PE12C_PWM0_H2    (1u << 12)	/**< \brief Pwm signal: PWM0_H2 */
#define PIO_PC2B_PWM0_H3     (1u << 2)	/**< \brief Pwm signal: PWM0_H3 */
#define PIO_PE14C_PWM0_H3    (1u << 14)	/**< \brief Pwm signal: PWM0_H3 */
#define PIO_PA27B_PWM0_L0    (1u << 27)	/**< \brief Pwm signal: PWM0_L0 */
#define PIO_PB15C_PWM0_L0    (1u << 15)	/**< \brief Pwm signal: PWM0_L0 */
#define PIO_PB27C_PWM0_L0    (1u << 27)	/**< \brief Pwm signal: PWM0_L0 */
#define PIO_PC27C_PWM0_L0    (1u << 27)	/**< \brief Pwm signal: PWM0_L0 */
#define PIO_PA29B_PWM0_L1    (1u << 29)	/**< \brief Pwm signal: PWM0_L1 */
#define PIO_PB10C_PWM0_L1    (1u << 10)	/**< \brief Pwm signal: PWM0_L1 */
#define PIO_PB29C_PWM0_L1    (1u << 29)	/**< \brief Pwm signal: PWM0_L1 */
#define PIO_PC28C_PWM0_L1    (1u << 28)	/**< \brief Pwm signal: PWM0_L1 */
#define PIO_PC1B_PWM0_L2     (1u << 1)	/**< \brief Pwm signal: PWM0_L2 */
#define PIO_PE13C_PWM0_L2    (1u << 13)	/**< \brief Pwm signal: PWM0_L2 */
#define PIO_PC3B_PWM0_L3     (1u << 3)	/**< \brief Pwm signal: PWM0_L3 */
#define PIO_PE8C_PWM0_L3     (1u << 8)	/**< \brief Pwm signal: PWM0_L3 */
/* ========== Pio definition for SMD peripheral ========== */
#define PIO_PE30A_DIBN       (1u << 30)	/**< \brief Smd signal: DIBN */
#define PIO_PE29A_DIBP       (1u << 29)	/**< \brief Smd signal: DIBP */
/* ========== Pio definition for SPI0 peripheral ========== */
#define PIO_PC0A_SPI0_MISO   (1u << 0)	/**< \brief Spi0 signal: SPI0_MISO */
#define PIO_PC1A_SPI0_MOSI   (1u << 1)	/**< \brief Spi0 signal: SPI0_MOSI */
#define PIO_PC3A_SPI0_NPCS0  (1u << 3)	/**< \brief Spi0 signal: SPI0_NPCS0 */
#define PIO_PC4A_SPI0_NPCS1  (1u << 4)	/**< \brief Spi0 signal: SPI0_NPCS1 */
#define PIO_PC27B_SPI0_NPCS1 (1u << 27)	/**< \brief Spi0 signal: SPI0_NPCS1 */
#define PIO_PC28B_SPI0_NPCS2 (1u << 28)	/**< \brief Spi0 signal: SPI0_NPCS2 */
#define PIO_PD31A_SPI0_NPCS2 (1u << 31)	/**< \brief Spi0 signal: SPI0_NPCS2 */
#define PIO_PC29B_SPI0_NPCS3 (1u << 29)	/**< \brief Spi0 signal: SPI0_NPCS3 */
#define PIO_PC2A_SPI0_SPCK   (1u << 2)	/**< \brief Spi0 signal: SPI0_SPCK */
/* ========== Pio definition for SPI1 peripheral ========== */
#define PIO_PB18A_SPI1_MISO  (1u << 18)	/**< \brief Spi1 signal: SPI1_MISO */
#define PIO_PB19A_SPI1_MOSI  (1u << 19)	/**< \brief Spi1 signal: SPI1_MOSI */
#define PIO_PB21A_SPI1_NPCS0 (1u << 21)	/**< \brief Spi1 signal: SPI1_NPCS0 */
#define PIO_PA26C_SPI1_NPCS1 (1u << 26)	/**< \brief Spi1 signal: SPI1_NPCS1 */
#define PIO_PB22A_SPI1_NPCS1 (1u << 22)	/**< \brief Spi1 signal: SPI1_NPCS1 */
#define PIO_PA27C_SPI1_NPCS2 (1u << 27)	/**< \brief Spi1 signal: SPI1_NPCS2 */
#define PIO_PB23A_SPI1_NPCS2 (1u << 23)	/**< \brief Spi1 signal: SPI1_NPCS2 */
#define PIO_PA28C_SPI1_NPCS3 (1u << 28)	/**< \brief Spi1 signal: SPI1_NPCS3 */
#define PIO_PB27A_SPI1_NPCS3 (1u << 27)	/**< \brief Spi1 signal: SPI1_NPCS3 */
#define PIO_PB20A_SPI1_SPCK  (1u << 20)	/**< \brief Spi1 signal: SPI1_SPCK */
/* ========== Pio definition for SPI2 peripheral ========== */
#define PIO_PD11B_SPI2_MISO  (1u << 11)	/**< \brief Spi2 signal: SPI2_MISO */
#define PIO_PD13B_SPI2_MOSI  (1u << 13)	/**< \brief Spi2 signal: SPI2_MOSI */
#define PIO_PD17B_SPI2_NPCS0 (1u << 17)	/**< \brief Spi2 signal: SPI2_NPCS0 */
#define PIO_PB14B_SPI2_NPCS1 (1u << 14)	/**< \brief Spi2 signal: SPI2_NPCS1 */
#define PIO_PB15B_SPI2_NPCS2 (1u << 15)	/**< \brief Spi2 signal: SPI2_NPCS2 */
#define PIO_PB28A_SPI2_NPCS3 (1u << 28)	/**< \brief Spi2 signal: SPI2_NPCS3 */
#define PIO_PD15B_SPI2_SPCK  (1u << 15)	/**< \brief Spi2 signal: SPI2_SPCK */
/* ========== Pio definition for SSC0 peripheral ========== */
#define PIO_PB29B_RD0        (1u << 29)	/**< \brief Ssc0 signal: RD0 */
#define PIO_PB30B_RF0        (1u << 30)	/**< \brief Ssc0 signal: RF0 */
#define PIO_PB26B_RK0        (1u << 26)	/**< \brief Ssc0 signal: RK0 */
#define PIO_PA25B_TD0        (1u << 25)	/**< \brief Ssc0 signal: TD0 */
#define PIO_PB28B_TD0        (1u << 28)	/**< \brief Ssc0 signal: TD0 */
#define PIO_PB31B_TF0        (1u << 31)	/**< \brief Ssc0 signal: TF0 */
#define PIO_PB27B_TK0        (1u << 27)	/**< \brief Ssc0 signal: TK0 */
/* ========== Pio definition for SSC1 peripheral ========== */
#define PIO_PC23B_RD1        (1u << 23)	/**< \brief Ssc1 signal: RD1 */
#define PIO_PC22B_RF1        (1u << 22)	/**< \brief Ssc1 signal: RF1 */
#define PIO_PC24B_RK1        (1u << 24)	/**< \brief Ssc1 signal: RK1 */
#define PIO_PC21B_TD1        (1u << 21)	/**< \brief Ssc1 signal: TD1 */
#define PIO_PC20B_TF1        (1u << 20)	/**< \brief Ssc1 signal: TF1 */
#define PIO_PC19B_TK1        (1u << 19)	/**< \brief Ssc1 signal: TK1 */
/* ========== Pio definition for TC0 peripheral ========== */
#define PIO_PE17C_TCLK0      (1u << 17)	/**< \brief Tc0 signal: TCLK0 */
#define PIO_PE14B_TCLK1      (1u << 14)	/**< \brief Tc0 signal: TCLK1 */
#define PIO_PE11B_TCLK2      (1u << 11)	/**< \brief Tc0 signal: TCLK2 */
#define PIO_PE15C_TIOA0      (1u << 15)	/**< \brief Tc0 signal: TIOA0 */
#define PIO_PE12B_TIOA1      (1u << 12)	/**< \brief Tc0 signal: TIOA1 */
#define PIO_PE9B_TIOA2       (1u << 9)	/**< \brief Tc0 signal: TIOA2 */
#define PIO_PE16C_TIOB0      (1u << 16)	/**< \brief Tc0 signal: TIOB0 */
#define PIO_PE13B_TIOB1      (1u << 13)	/**< \brief Tc0 signal: TIOB1 */
#define PIO_PE10B_TIOB2      (1u << 10)	/**< \brief Tc0 signal: TIOB2 */
/* ========== Pio definition for TC1 peripheral ========== */
#define PIO_PE8B_TCLK3       (1u << 8)	/**< \brief Tc1 signal: TCLK3 */
#define PIO_PE23B_TCLK4      (1u << 23)	/**< \brief Tc1 signal: TCLK4 */
#define PIO_PE20B_TCLK5      (1u << 20)	/**< \brief Tc1 signal: TCLK5 */
#define PIO_PE6B_TIOA3       (1u << 6)	/**< \brief Tc1 signal: TIOA3 */
#define PIO_PE21B_TIOA4      (1u << 21)	/**< \brief Tc1 signal: TIOA4 */
#define PIO_PE18B_TIOA5      (1u << 18)	/**< \brief Tc1 signal: TIOA5 */
#define PIO_PE7B_TIOB3       (1u << 7)	/**< \brief Tc1 signal: TIOB3 */
#define PIO_PE22B_TIOB4      (1u << 22)	/**< \brief Tc1 signal: TIOB4 */
#define PIO_PE19B_TIOB5      (1u << 19)	/**< \brief Tc1 signal: TIOB5 */
/* ========== Pio definition for TWI0 peripheral ========== */
#define PIO_PA31A_TWCK0      (1u << 31)	/**< \brief Twi0 signal: TWCK0 */
#define PIO_PA30A_TWD0       (1u << 30)	/**< \brief Twi0 signal: TWD0 */
/* ========== Pio definition for TWI1 peripheral ========== */
#define PIO_PE30C_TWCK1      (1u << 30)	/**< \brief Twi1 signal: TWCK1 */
#define PIO_PE29C_TWD1       (1u << 29)	/**< \brief Twi1 signal: TWD1 */
/* ========== Pio definition for TWI2 peripheral ========== */
#define PIO_PB30A_TWCK2      (1u << 30)	/**< \brief Twi2 signal: TWCK2 */
#define PIO_PB29A_TWD2       (1u << 29)	/**< \brief Twi2 signal: TWD2 */
/* ========== Pio definition for TWI3 peripheral ========== */
#define PIO_PC26B_TWCK3      (1u << 26)	/**< \brief Twi3 signal: TWCK3 */
#define PIO_PC25B_TWD3       (1u << 25)	/**< \brief Twi3 signal: TWD3 */
/* ========== Pio definition for UART0 peripheral ========== */
#define PIO_PE29B_URXD0      (1u << 29)	/**< \brief Uart0 signal: URXD0 */
#define PIO_PE30B_UTXD0      (1u << 30)	/**< \brief Uart0 signal: UTXD0 */
/* ========== Pio definition for UART1 peripheral ========== */
#define PIO_PC25C_URXD1      (1u << 25)	/**< \brief Uart1 signal: URXD1 */
#define PIO_PC26C_UTXD1      (1u << 26)	/**< \brief Uart1 signal: UTXD1 */
/* ========== Pio definition for USART0 peripheral ========== */
#define PIO_PD10A_CTS0       (1u << 10)	/**< \brief Usart0 signal: CTS0 */
#define PIO_PD11A_RTS0       (1u << 11)	/**< \brief Usart0 signal: RTS0 */
#define PIO_PD12A_RXD0       (1u << 12)	/**< \brief Usart0 signal: RXD0 */
#define PIO_PD28A_SCK0       (1u << 28)	/**< \brief Usart0 signal: SCK0 */
#define PIO_PD13A_TXD0       (1u << 13)	/**< \brief Usart0 signal: TXD0 */
/* ========== Pio definition for USART1 peripheral ========== */
#define PIO_PD14A_CTS1       (1u << 14)	/**< \brief Usart1 signal: CTS1 */
#define PIO_PD15A_RTS1       (1u << 15)	/**< \brief Usart1 signal: RTS1 */
#define PIO_PD16A_RXD1       (1u << 16)	/**< \brief Usart1 signal: RXD1 */
#define PIO_PD29A_SCK1       (1u << 29)	/**< \brief Usart1 signal: SCK1 */
#define PIO_PD17A_TXD1       (1u << 17)	/**< \brief Usart1 signal: TXD1 */
/* ========== Pio definition for USART2 peripheral ========== */
#define PIO_PB3B_CTS2        (1u << 3)	/**< \brief Usart2 signal: CTS2 */
#define PIO_PB11B_RTS2       (1u << 11)	/**< \brief Usart2 signal: RTS2 */
#define PIO_PB4B_RXD2        (1u << 4)	/**< \brief Usart2 signal: RXD2 */
#define PIO_PB1B_SCK2        (1u << 1)	/**< \brief Usart2 signal: SCK2 */
#define PIO_PB5B_TXD2        (1u << 5)	/**< \brief Usart2 signal: TXD2 */
/* ========== Pio definition for USART3 peripheral ========== */
#define PIO_PE5B_CTS3        (1u << 5)	/**< \brief Usart3 signal: CTS3 */
#define PIO_PE24B_RTS3       (1u << 24)	/**< \brief Usart3 signal: RTS3 */
#define PIO_PE16B_RXD3       (1u << 16)	/**< \brief Usart3 signal: RXD3 */
#define PIO_PE15B_SCK3       (1u << 15)	/**< \brief Usart3 signal: SCK3 */
#define PIO_PE17B_TXD3       (1u << 17)	/**< \brief Usart3 signal: TXD3 */
/* ========== Pio definition for USART4 peripheral ========== */
#define PIO_PE0C_CTS4        (1u << 0)	/**< \brief Usart4 signal: CTS4 */
#define PIO_PE28B_RTS4       (1u << 28)	/**< \brief Usart4 signal: RTS4 */
#define PIO_PE26B_RXD4       (1u << 26)	/**< \brief Usart4 signal: RXD4 */
#define PIO_PE25B_SCK4       (1u << 25)	/**< \brief Usart4 signal: SCK4 */
#define PIO_PE27B_TXD4       (1u << 27)	/**< \brief Usart4 signal: TXD4 */
/* ========== Pio indexes ========== */
#define PIO_PA0_IDX          0
#define PIO_PA1_IDX          1
#define PIO_PA2_IDX          2
#define PIO_PA3_IDX          3
#define PIO_PA4_IDX          4
#define PIO_PA5_IDX          5
#define PIO_PA6_IDX          6
#define PIO_PA7_IDX          7
#define PIO_PA8_IDX          8
#define PIO_PA9_IDX          9
#define PIO_PA10_IDX         10
#define PIO_PA11_IDX         11
#define PIO_PA12_IDX         12
#define PIO_PA13_IDX         13
#define PIO_PA14_IDX         14
#define PIO_PA15_IDX         15
#define PIO_PA16_IDX         16
#define PIO_PA17_IDX         17
#define PIO_PA18_IDX         18
#define PIO_PA19_IDX         19
#define PIO_PA20_IDX         20
#define PIO_PA21_IDX         21
#define PIO_PA22_IDX         22
#define PIO_PA23_IDX         23
#define PIO_PA24_IDX         24
#define PIO_PA25_IDX         25
#define PIO_PA26_IDX         26
#define PIO_PA27_IDX         27
#define PIO_PA28_IDX         28
#define PIO_PA29_IDX         29
#define PIO_PA30_IDX         30
#define PIO_PA31_IDX         31
#define PIO_PB0_IDX          32
#define PIO_PB1_IDX          33
#define PIO_PB2_IDX          34
#define PIO_PB3_IDX          35
#define PIO_PB4_IDX          36
#define PIO_PB5_IDX          37
#define PIO_PB6_IDX          38
#define PIO_PB7_IDX          39
#define PIO_PB8_IDX          40
#define PIO_PB9_IDX          41
#define PIO_PB10_IDX         42
#define PIO_PB11_IDX         43
#define PIO_PB12_IDX         44
#define PIO_PB13_IDX         45
#define PIO_PB14_IDX         46
#define PIO_PB15_IDX         47
#define PIO_PB16_IDX         48
#define PIO_PB17_IDX         49
#define PIO_PB18_IDX         50
#define PIO_PB19_IDX         51
#define PIO_PB20_IDX         52
#define PIO_PB21_IDX         53
#define PIO_PB22_IDX         54
#define PIO_PB23_IDX         55
#define PIO_PB24_IDX         56
#define PIO_PB25_IDX         57
#define PIO_PB26_IDX         58
#define PIO_PB27_IDX         59
#define PIO_PB28_IDX         60
#define PIO_PB29_IDX         61
#define PIO_PB30_IDX         62
#define PIO_PB31_IDX         63
#define PIO_PC0_IDX          64
#define PIO_PC1_IDX          65
#define PIO_PC2_IDX          66
#define PIO_PC3_IDX          67
#define PIO_PC4_IDX          68
#define PIO_PC5_IDX          69
#define PIO_PC6_IDX          70
#define PIO_PC7_IDX          71
#define PIO_PC8_IDX          72
#define PIO_PC9_IDX          73
#define PIO_PC10_IDX         74
#define PIO_PC11_IDX         75
#define PIO_PC12_IDX         76
#define PIO_PC13_IDX         77
#define PIO_PC14_IDX         78
#define PIO_PC15_IDX         79
#define PIO_PC16_IDX         80
#define PIO_PC17_IDX         81
#define PIO_PC18_IDX         82
#define PIO_PC27_IDX         91
#define PIO_PC28_IDX         92
#define PIO_PC29_IDX         93
#define PIO_PC30_IDX         94
#define PIO_PC31_IDX         95
#define PIO_PD0_IDX          96
#define PIO_PD1_IDX          97
#define PIO_PD2_IDX          98
#define PIO_PD3_IDX          99
#define PIO_PD4_IDX          100
#define PIO_PD5_IDX          101
#define PIO_PD6_IDX          102
#define PIO_PD7_IDX          103
#define PIO_PD8_IDX          104
#define PIO_PD9_IDX          105
#define PIO_PD10_IDX         106
#define PIO_PD11_IDX         107
#define PIO_PD12_IDX         108
#define PIO_PD13_IDX         109
#define PIO_PD14_IDX         110
#define PIO_PD15_IDX         111
#define PIO_PD16_IDX         112
#define PIO_PD17_IDX         113
#define PIO_PD18_IDX         114
#define PIO_PD19_IDX         115
#define PIO_PD20_IDX         116
#define PIO_PD21_IDX         117
#define PIO_PD22_IDX         118
#define PIO_PD23_IDX         119
#define PIO_PD24_IDX         120
#define PIO_PD25_IDX         121
#define PIO_PD26_IDX         122
#define PIO_PD27_IDX         123
#define PIO_PD28_IDX         124
#define PIO_PD29_IDX         125
#define PIO_PD30_IDX         126
#define PIO_PD31_IDX         127
#define PIO_PE0_IDX          128
#define PIO_PE1_IDX          129
#define PIO_PE2_IDX          130
#define PIO_PE3_IDX          131
#define PIO_PE4_IDX          132
#define PIO_PE5_IDX          133
#define PIO_PE6_IDX          134
#define PIO_PE7_IDX          135
#define PIO_PE8_IDX          136
#define PIO_PE9_IDX          137
#define PIO_PE10_IDX         138
#define PIO_PE11_IDX         139
#define PIO_PE12_IDX         140
#define PIO_PE13_IDX         141
#define PIO_PE14_IDX         142
#define PIO_PE15_IDX         143
#define PIO_PE16_IDX         144
#define PIO_PE17_IDX         145
#define PIO_PE24_IDX         152
#define PIO_PE25_IDX         153
#define PIO_PE26_IDX         154
#define PIO_PE27_IDX         155
#define PIO_PE28_IDX         156
#define PIO_PE29_IDX         157
#define PIO_PE30_IDX         158
#define PIO_PE31_IDX         159

#endif				/* _SAMA5D43_PIO_ */
