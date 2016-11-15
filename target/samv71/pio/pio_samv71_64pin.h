/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2016, Atmel Corporation                                        */
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

#ifndef _SAMV71_PIO_
#define _SAMV71_PIO_

#define PIO_PA3                   (1u << 3)  /**< \brief Pin Controlled by PA3 */
#define PIO_PA4                   (1u << 4)  /**< \brief Pin Controlled by PA4 */
#define PIO_PA5                   (1u << 5)  /**< \brief Pin Controlled by PA5 */
#define PIO_PA7                   (1u << 7)  /**< \brief Pin Controlled by PA7 */
#define PIO_PA8                   (1u << 8)  /**< \brief Pin Controlled by PA8 */
#define PIO_PA9                   (1u << 9)  /**< \brief Pin Controlled by PA9 */
#define PIO_PA10                  (1u << 10) /**< \brief Pin Controlled by PA10 */
#define PIO_PA11                  (1u << 11) /**< \brief Pin Controlled by PA11 */
#define PIO_PA12                  (1u << 12) /**< \brief Pin Controlled by PA12 */
#define PIO_PA13                  (1u << 13) /**< \brief Pin Controlled by PA13 */
#define PIO_PA14                  (1u << 14) /**< \brief Pin Controlled by PA14 */
#define PIO_PA21                  (1u << 21) /**< \brief Pin Controlled by PA21 */
#define PIO_PA22                  (1u << 22) /**< \brief Pin Controlled by PA22 */
#define PIO_PA24                  (1u << 24) /**< \brief Pin Controlled by PA24 */
#define PIO_PA27                  (1u << 27) /**< \brief Pin Controlled by PA27 */
#define PIO_PB0                   (1u << 0)  /**< \brief Pin Controlled by PB0 */
#define PIO_PB1                   (1u << 1)  /**< \brief Pin Controlled by PB1 */
#define PIO_PB2                   (1u << 2)  /**< \brief Pin Controlled by PB2 */
#define PIO_PB3                   (1u << 3)  /**< \brief Pin Controlled by PB3 */
#define PIO_PB4                   (1u << 4)  /**< \brief Pin Controlled by PB4 */
#define PIO_PB5                   (1u << 5)  /**< \brief Pin Controlled by PB5 */
#define PIO_PB6                   (1u << 6)  /**< \brief Pin Controlled by PB6 */
#define PIO_PB7                   (1u << 7)  /**< \brief Pin Controlled by PB7 */
#define PIO_PB8                   (1u << 8)  /**< \brief Pin Controlled by PB8 */
#define PIO_PB9                   (1u << 9)  /**< \brief Pin Controlled by PB9 */
#define PIO_PB12                  (1u << 12) /**< \brief Pin Controlled by PB12 */
#define PIO_PD0                   (1u << 0)  /**< \brief Pin Controlled by PD0 */
#define PIO_PD1                   (1u << 1)  /**< \brief Pin Controlled by PD1 */
#define PIO_PD2                   (1u << 2)  /**< \brief Pin Controlled by PD2 */
#define PIO_PD3                   (1u << 3)  /**< \brief Pin Controlled by PD3 */
#define PIO_PD4                   (1u << 4)  /**< \brief Pin Controlled by PD4 */
#define PIO_PD5                   (1u << 5)  /**< \brief Pin Controlled by PD5 */
#define PIO_PD6                   (1u << 6)  /**< \brief Pin Controlled by PD6 */
#define PIO_PD7                   (1u << 7)  /**< \brief Pin Controlled by PD7 */
#define PIO_PD8                   (1u << 8)  /**< \brief Pin Controlled by PD8 */
#define PIO_PD9                   (1u << 9)  /**< \brief Pin Controlled by PD9 */
#define PIO_PD10                  (1u << 10) /**< \brief Pin Controlled by PD10 */
#define PIO_PD11                  (1u << 11) /**< \brief Pin Controlled by PD11 */
#define PIO_PD12                  (1u << 12) /**< \brief Pin Controlled by PD12 */
#define PIO_PD21                  (1u << 21) /**< \brief Pin Controlled by PD21 */
#define PIO_PD22                  (1u << 22) /**< \brief Pin Controlled by PD22 */
#define PIO_PD24                  (1u << 24) /**< \brief Pin Controlled by PD24 */
#define PIO_PD25                  (1u << 25) /**< \brief Pin Controlled by PD25 */
#define PIO_PD26                  (1u << 26) /**< \brief Pin Controlled by PD26 */
#define PIO_PD31                  (1u << 31) /**< \brief Pin Controlled by PD31 */
/* ========== Pio definition for AFEC0 peripheral ========== */
#define PIO_PD30X1_AFE0_AD0       (1u << 30) /**< \brief Afec0 signal: AFE0_AD0 */
#define PIO_PA21X1_AFE0_AD1       (1u << 21) /**< \brief Afec0 signal: AFE0_AD1/PIODCEN2 */
#define PIO_PA21X1_PIODCEN2       (1u << 21) /**< \brief Afec0 signal: AFE0_AD1/PIODCEN2 */
#define PIO_PB0X1_AFE0_AD10       (1u << 0)  /**< \brief Afec0 signal: AFE0_AD10/RTCOUT0 */
#define PIO_PB0X1_RTCOUT0         (1u << 0)  /**< \brief Afec0 signal: AFE0_AD10/RTCOUT0 */
#define PIO_PB3X1_AFE0_AD2        (1u << 3)  /**< \brief Afec0 signal: AFE0_AD2/WKUP12 */
#define PIO_PB3X1_WKUP12          (1u << 3)  /**< \brief Afec0 signal: AFE0_AD2/WKUP12 */
#define PIO_PB2X1_AFE0_AD5        (1u << 2)  /**< \brief Afec0 signal: AFE0_AD5 */
#define PIO_PA17X1_AFE0_AD6       (1u << 17) /**< \brief Afec0 signal: AFE0_AD6 */
#define PIO_PA18X1_AFE0_AD7       (1u << 18) /**< \brief Afec0 signal: AFE0_AD7 */
#define PIO_PA19X1_AFE0_AD8       (1u << 19) /**< \brief Afec0 signal: AFE0_AD8/WKUP9 */
#define PIO_PA19X1_WKUP9          (1u << 19) /**< \brief Afec0 signal: AFE0_AD8/WKUP9 */
#define PIO_PA20X1_AFE0_AD9       (1u << 20) /**< \brief Afec0 signal: AFE0_AD9/WKUP10 */
#define PIO_PA20X1_WKUP10         (1u << 20) /**< \brief Afec0 signal: AFE0_AD9/WKUP10 */
#define PIO_PA8B_AFE0_ADTRG       (1u << 8)  /**< \brief Afec0 signal: AFE0_ADTRG */
/* ========== Pio definition for AFEC1 peripheral ========== */
#define PIO_PB1X1_AFE1_AD0        (1u << 1)  /**< \brief Afec1 signal: AFE1_AD0/RTCOUT1 */
#define PIO_PB1X1_RTCOUT1         (1u << 1)  /**< \brief Afec1 signal: AFE1_AD0/RTCOUT1 */
#define PIO_PD9C_AFE1_ADTRG       (1u << 9)  /**< \brief Afec1 signal: AFE1_ADTRG */
/* ========== Pio definition for ARM peripheral ========== */
#define PIO_PB7X1_SWCLK           (1u << 7)  /**< \brief Arm signal: SWCLK/TCK */
#define PIO_PB7X1_TCK             (1u << 7)  /**< \brief Arm signal: SWCLK/TCK */
#define PIO_PB6X1_SWDIO           (1u << 6)  /**< \brief Arm signal: SWDIO/TMS */
#define PIO_PB6X1_TMS             (1u << 6)  /**< \brief Arm signal: SWDIO/TMS */
#define PIO_PB4X1_TDI             (1u << 4)  /**< \brief Arm signal: TDI */
#define PIO_PB5X1_TDO             (1u << 5)  /**< \brief Arm signal: TDO/TRACESWO/WKUP13 */
#define PIO_PB5X1_TRACESWO        (1u << 5)  /**< \brief Arm signal: TDO/TRACESWO/WKUP13 */
#define PIO_PB5X1_WKUP13          (1u << 5)  /**< \brief Arm signal: TDO/TRACESWO/WKUP13 */
/* ========== Pio definition for DACC peripheral ========== */
#define PIO_PB13X1_DAC0           (1u << 13) /**< \brief Dacc signal: DAC0 */
#define PIO_PD0X1_DAC1            (1u << 0)  /**< \brief Dacc signal: DAC1 */
/* ========== Pio definition for GMAC0 peripheral ========== */
#ifdef GMAC0
#define PIO_PD10A_GCRS            (1u << 10) /**< \brief Gmac signal: GCRS */
#define PIO_PD8A_GMDC             (1u << 8)  /**< \brief Gmac signal: GMDC */
#define PIO_PD9A_GMDIO            (1u << 9)  /**< \brief Gmac signal: GMDIO */
#define PIO_PD5A_GRX0             (1u << 5)  /**< \brief Gmac signal: GRX0 */
#define PIO_PD6A_GRX1             (1u << 6)  /**< \brief Gmac signal: GRX1 */
#define PIO_PD11A_GRX2            (1u << 11) /**< \brief Gmac signal: GRX2 */
#define PIO_PD12A_GRX3            (1u << 12) /**< \brief Gmac signal: GRX3 */
#define PIO_PD4A_GRXDV            (1u << 4)  /**< \brief Gmac signal: GRXDV */
#define PIO_PD7A_GRXER            (1u << 7)  /**< \brief Gmac signal: GRXER */
#define PIO_PB1B_GTSUCOMP         (1u << 1)  /**< \brief Gmac signal: GTSUCOMP */
#define PIO_PB12B_GTSUCOMP        (1u << 12) /**< \brief Gmac signal: GTSUCOMP */
#define PIO_PD11C_GTSUCOMP        (1u << 11) /**< \brief Gmac signal: GTSUCOMP */
#define PIO_PD2A_GTX0             (1u << 2)  /**< \brief Gmac signal: GTX0 */
#define PIO_PD3A_GTX1             (1u << 3)  /**< \brief Gmac signal: GTX1 */
#define PIO_PD0A_GTXCK            (1u << 0)  /**< \brief Gmac signal: GTXCK */
#define PIO_PD1A_GTXEN            (1u << 1)  /**< \brief Gmac signal: GTXEN */
#endif
/* ========== Pio definition for HSMCI peripheral ========== */
#define PIO_PA27C_MCDA3           (1u << 27) /**< \brief Hsmci signal: MCDA3 */
/* ========== Pio definition for ISI peripheral ========== */
#define PIO_PD22D_ISI_D0          (1u << 22) /**< \brief Isi signal: ISI_D0 */
#define PIO_PD21D_ISI_D1          (1u << 21) /**< \brief Isi signal: ISI_D1 */
#define PIO_PD31D_ISI_D11         (1u << 31) /**< \brief Isi signal: ISI_D11 */
#define PIO_PB3D_ISI_D2           (1u << 3)  /**< \brief Isi signal: ISI_D2 */
#define PIO_PA9B_ISI_D3           (1u << 9)  /**< \brief Isi signal: ISI_D3 */
#define PIO_PA5B_ISI_D4           (1u << 5)  /**< \brief Isi signal: ISI_D4 */
#define PIO_PD11D_ISI_D5          (1u << 11) /**< \brief Isi signal: ISI_D5 */
#define PIO_PD12D_ISI_D6          (1u << 12) /**< \brief Isi signal: ISI_D6 */
#define PIO_PA27D_ISI_D7          (1u << 27) /**< \brief Isi signal: ISI_D7 */
#define PIO_PD24D_ISI_HSYNC       (1u << 24) /**< \brief Isi signal: ISI_HSYNC */
#define PIO_PA24D_ISI_PCK         (1u << 24) /**< \brief Isi signal: ISI_PCK */
#define PIO_PD25D_ISI_VSYNC       (1u << 25) /**< \brief Isi signal: ISI_VSYNC */
/* ========== Pio definition for MCAN0 peripheral ========== */
#ifdef MCAN0
#define PIO_PB3A_CANRX0           (1u << 3)  /**< \brief Mcan0 signal: CANRX0 */
#define PIO_PB2A_CANTX0           (1u << 2)  /**< \brief Mcan0 signal: CANTX0 */
#endif
/* ========== Pio definition for MCAN1 peripheral ========== */
#ifdef MCAN1
#define PIO_PD12B_CANTX1          (1u << 12) /**< \brief Mcan1 signal: CANTX1 */
#endif
/* ========== Pio definition for MLB peripheral ========== */
#ifdef MLB
#define PIO_PB4C_MLBCLK           (1u << 4)  /**< \brief Mlb signal: MLBCLK */
#define PIO_PB5C_MLBDAT           (1u << 5)  /**< \brief Mlb signal: MLBDAT */
#define PIO_PD10D_MLBSIG          (1u << 10) /**< \brief Mlb signal: MLBSIG */
#endif
/* ========== Pio definition for PIOA peripheral ========== */
#define PIO_PA21X1_AFE0_AD1       (1u << 21) /**< \brief Pioa signal: AFE0_AD1/PIODCEN2 */
#define PIO_PA21X1_PIODCEN2       (1u << 21) /**< \brief Pioa signal: AFE0_AD1/PIODCEN2 */
#define PIO_PA3X1_PIODC0          (1u << 3)  /**< \brief Pioa signal: PIODC0 */
#define PIO_PA10X1_PIODC4         (1u << 10) /**< \brief Pioa signal: PIODC4 */
#define PIO_PA12X1_PIODC6         (1u << 12) /**< \brief Pioa signal: PIODC6 */
#define PIO_PA13X1_PIODC7         (1u << 13) /**< \brief Pioa signal: PIODC7 */
#define PIO_PA22X1_PIODCCLK       (1u << 22) /**< \brief Pioa signal: PIODCCLK */
#define PIO_PA4X1_WKUP3           (1u << 4)  /**< \brief Pioa signal: WKUP3/PIODC1 */
#define PIO_PA4X1_PIODC1          (1u << 4)  /**< \brief Pioa signal: WKUP3/PIODC1 */
#define PIO_PA5X1_WKUP4           (1u << 5)  /**< \brief Pioa signal: WKUP4/PIODC2 */
#define PIO_PA5X1_PIODC2          (1u << 5)  /**< \brief Pioa signal: WKUP4/PIODC2 */
#define PIO_PA9X1_WKUP6           (1u << 9)  /**< \brief Pioa signal: WKUP6/PIODC3 */
#define PIO_PA9X1_PIODC3          (1u << 9)  /**< \brief Pioa signal: WKUP6/PIODC3 */
#define PIO_PA11X1_WKUP7          (1u << 11) /**< \brief Pioa signal: WKUP7/PIODC5 */
#define PIO_PA11X1_PIODC5         (1u << 11) /**< \brief Pioa signal: WKUP7/PIODC5 */
#define PIO_PA14X1_WKUP8          (1u << 14) /**< \brief Pioa signal: WKUP8/PIODCEN1 */
#define PIO_PA14X1_PIODCEN1       (1u << 14) /**< \brief Pioa signal: WKUP8/PIODCEN1 */
/* ========== Pio definition for PMC peripheral ========== */
#define PIO_PB12D_PCK0            (1u << 12) /**< \brief Pmc signal: PCK0 */
#define PIO_PA21B_PCK1            (1u << 21) /**< \brief Pmc signal: PCK1 */
#define PIO_PA3C_PCK2             (1u << 3)  /**< \brief Pmc signal: PCK2 */
#define PIO_PB3B_PCK2             (1u << 3)  /**< \brief Pmc signal: PCK2 */
#define PIO_PD31C_PCK2            (1u << 31) /**< \brief Pmc signal: PCK2 */
/* ========== Pio definition for PWM0 peripheral ========== */
#define PIO_PA10B_PWM0_EXTRG0     (1u << 10) /**< \brief Pwm0 signal: PWM0_EXTRG0 */
#define PIO_PA22B_PWM0_EXTRG1     (1u << 22) /**< \brief Pwm0 signal: PWM0_EXTRG1 */
#define PIO_PA9C_PWM0_FI0         (1u << 9)  /**< \brief Pwm0 signal: PWM0_FI0 */
#define PIO_PD8B_PWM0_FI1         (1u << 8)  /**< \brief Pwm0 signal: PWM0_FI1 */
#define PIO_PD9B_PWM0_FI2         (1u << 9)  /**< \brief Pwm0 signal: PWM0_FI2 */
#define PIO_PA11B_PWM0_H0         (1u << 11) /**< \brief Pwm0 signal: PWM0_H0 */
#define PIO_PB0A_PWM0_H0          (1u << 0)  /**< \brief Pwm0 signal: PWM0_H0 */
#define PIO_PD11B_PWM0_H0         (1u << 11) /**< \brief Pwm0 signal: PWM0_H0 */
#define PIO_PA12B_PWM0_H1         (1u << 12) /**< \brief Pwm0 signal: PWM0_H1 */
#define PIO_PA24B_PWM0_H1         (1u << 24) /**< \brief Pwm0 signal: PWM0_H1 */
#define PIO_PB1A_PWM0_H1          (1u << 1)  /**< \brief Pwm0 signal: PWM0_H1 */
#define PIO_PD21A_PWM0_H1         (1u << 21) /**< \brief Pwm0 signal: PWM0_H1 */
#define PIO_PA13B_PWM0_H2         (1u << 13) /**< \brief Pwm0 signal: PWM0_H2 */
#define PIO_PB4B_PWM0_H2          (1u << 4)  /**< \brief Pwm0 signal: PWM0_H2 */
#define PIO_PD22A_PWM0_H2         (1u << 22) /**< \brief Pwm0 signal: PWM0_H2 */
#define PIO_PA7B_PWM0_H3          (1u << 7)  /**< \brief Pwm0 signal: PWM0_H3 */
#define PIO_PA14B_PWM0_H3         (1u << 14) /**< \brief Pwm0 signal: PWM0_H3 */
#define PIO_PB5B_PWM0_L0          (1u << 5)  /**< \brief Pwm0 signal: PWM0_L0 */
#define PIO_PD10B_PWM0_L0         (1u << 10) /**< \brief Pwm0 signal: PWM0_L0 */
#define PIO_PD24A_PWM0_L0         (1u << 24) /**< \brief Pwm0 signal: PWM0_L0 */
#define PIO_PB12A_PWM0_L1         (1u << 12) /**< \brief Pwm0 signal: PWM0_L1 */
#define PIO_PD25A_PWM0_L1         (1u << 25) /**< \brief Pwm0 signal: PWM0_L1 */
#define PIO_PD26A_PWM0_L2         (1u << 26) /**< \brief Pwm0 signal: PWM0_L2 */
/* ========== Pio definition for PWM1 peripheral ========== */
#define PIO_PA21C_PWM1_FI0        (1u << 21) /**< \brief Pwm1 signal: PWM1_FI0 */
#define PIO_PA12C_PWM1_H0         (1u << 12) /**< \brief Pwm1 signal: PWM1_H0 */
#define PIO_PD1B_PWM1_H0          (1u << 1)  /**< \brief Pwm1 signal: PWM1_H0 */
#define PIO_PA14C_PWM1_H1         (1u << 14) /**< \brief Pwm1 signal: PWM1_H1 */
#define PIO_PD3B_PWM1_H1          (1u << 3)  /**< \brief Pwm1 signal: PWM1_H1 */
#define PIO_PD5B_PWM1_H2          (1u << 5)  /**< \brief Pwm1 signal: PWM1_H2 */
#define PIO_PA8A_PWM1_H3          (1u << 8)  /**< \brief Pwm1 signal: PWM1_H3 */
#define PIO_PD7B_PWM1_H3          (1u << 7)  /**< \brief Pwm1 signal: PWM1_H3 */
#define PIO_PA11C_PWM1_L0         (1u << 11) /**< \brief Pwm1 signal: PWM1_L0 */
#define PIO_PD0B_PWM1_L0          (1u << 0)  /**< \brief Pwm1 signal: PWM1_L0 */
#define PIO_PA13C_PWM1_L1         (1u << 13) /**< \brief Pwm1 signal: PWM1_L1 */
#define PIO_PD2B_PWM1_L1          (1u << 2)  /**< \brief Pwm1 signal: PWM1_L1 */
#define PIO_PD4B_PWM1_L2          (1u << 4)  /**< \brief Pwm1 signal: PWM1_L2 */
#define PIO_PA5A_PWM1_L3          (1u << 5)  /**< \brief Pwm1 signal: PWM1_L3 */
#define PIO_PD6B_PWM1_L3          (1u << 6)  /**< \brief Pwm1 signal: PWM1_L3 */
/* ========== Pio definition for QSPI0 peripheral ========== */
#define PIO_PA11A_QSPI0_CS        (1u << 11) /**< \brief Qspi0 signal: CS */
#define PIO_PA13A_QSPI0_IO0       (1u << 13) /**< \brief Qspi0 signal: IO0 */
#define PIO_PA12A_QSPI0_IO1       (1u << 12) /**< \brief Qspi0 signal: IO1 */
#define PIO_PD31A_QSPI0_IO3       (1u << 31) /**< \brief Qspi0 signal: IO3 */
#define PIO_PA14A_QSPI0_SCK       (1u << 14) /**< \brief Qspi0 signal: SCK */
/* ========== Pio definition for SPI0 peripheral ========== */
#define PIO_PD21B_SPI0_MOSI       (1u << 21) /**< \brief Spi0 signal: SPI0_MOSI */
#define PIO_PB2D_SPI0_NPCS0       (1u << 2)  /**< \brief Spi0 signal: SPI0_NPCS0 */
#define PIO_PD25B_SPI0_NPCS1      (1u << 25) /**< \brief Spi0 signal: SPI0_NPCS1 */
#define PIO_PD12C_SPI0_NPCS2      (1u << 12) /**< \brief Spi0 signal: SPI0_NPCS2 */
#define PIO_PD22B_SPI0_SPCK       (1u << 22) /**< \brief Spi0 signal: SPI0_SPCK */
/* ========== Pio definition for SPI1 peripheral ========== */
#define PIO_PD0C_SPI1_NPCS1       (1u << 0)  /**< \brief Spi1 signal: SPI1_NPCS1 */
#define PIO_PD1C_SPI1_NPCS2       (1u << 1)  /**< \brief Spi1 signal: SPI1_NPCS2 */
#define PIO_PD2C_SPI1_NPCS3       (1u << 2)  /**< \brief Spi1 signal: SPI1_NPCS3 */
/* ========== Pio definition for SSC peripheral ========== */
#define PIO_PA10C_RD              (1u << 10) /**< \brief Ssc signal: RD */
#define PIO_PD24B_RF              (1u << 24) /**< \brief Ssc signal: RF */
#define PIO_PA22A_RK              (1u << 22) /**< \brief Ssc signal: RK */
#define PIO_PB5D_TD               (1u << 5)  /**< \brief Ssc signal: TD */
#define PIO_PD10C_TD              (1u << 10) /**< \brief Ssc signal: TD */
#define PIO_PD26B_TD              (1u << 26) /**< \brief Ssc signal: TD */
#define PIO_PB0D_TF               (1u << 0)  /**< \brief Ssc signal: TF */
#define PIO_PB1D_TK               (1u << 1)  /**< \brief Ssc signal: TK */
/* ========== Pio definition for TC0 peripheral ========== */
#define PIO_PA4B_TCLK0            (1u << 4)  /**< \brief Tc0 signal: TCLK0 */
#define PIO_PA27B_TIOB2           (1u << 27) /**< \brief Tc0 signal: TIOB2 */
/* ========== Pio definition for TC3 peripheral ========== */
#define PIO_PD24C_TCLK11          (1u << 24) /**< \brief Tc3 signal: TCLK11 */
#define PIO_PD21C_TIOA11          (1u << 21) /**< \brief Tc3 signal: TIOA11 */
#define PIO_PD22C_TIOB11          (1u << 22) /**< \brief Tc3 signal: TIOB11 */
/* ========== Pio definition for TWI0 peripheral ========== */
#define PIO_PA4A_TWCK0            (1u << 4)  /**< \brief Twi0 signal: TWCK0 */
#define PIO_PA3A_TWD0             (1u << 3)  /**< \brief Twi0 signal: TWD0 */
/* ========== Pio definition for TWI1 peripheral ========== */
#define PIO_PB5A_TWCK1            (1u << 5)  /**< \brief Twi1 signal: TWCK1 */
#define PIO_PB4A_TWD1             (1u << 4)  /**< \brief Twi1 signal: TWD1 */
/* ========== Pio definition for UART0 peripheral ========== */
#define PIO_PA9A_URXD0            (1u << 9)  /**< \brief Uart0 signal: URXD0 */
#define PIO_PA10A_UTXD0           (1u << 10) /**< \brief Uart0 signal: UTXD0 */
/* ========== Pio definition for UART1 peripheral ========== */
#define PIO_PA5C_URXD1            (1u << 5)  /**< \brief Uart1 signal: URXD1 */
#define PIO_PA4C_UTXD1            (1u << 4)  /**< \brief Uart1 signal: UTXD1 */
#define PIO_PD26D_UTXD1           (1u << 26) /**< \brief Uart1 signal: UTXD1 */
/* ========== Pio definition for UART2 peripheral ========== */
#define PIO_PD25C_URXD2           (1u << 25) /**< \brief Uart2 signal: URXD2 */
#define PIO_PD26C_UTXD2           (1u << 26) /**< \brief Uart2 signal: UTXD2 */
/* ========== Pio definition for UART3 peripheral ========== */
#define PIO_PD31B_UTXD3           (1u << 31) /**< \brief Uart3 signal: UTXD3 */
/* ========== Pio definition for UART4 peripheral ========== */
#define PIO_PD3C_UTXD4            (1u << 3)  /**< \brief Uart4 signal: UTXD4 */
/* ========== Pio definition for USART0 peripheral ========== */
#define PIO_PB2C_CTS0             (1u << 2)  /**< \brief Usart0 signal: CTS0 */
#define PIO_PD0D_DCD0             (1u << 0)  /**< \brief Usart0 signal: DCD0 */
#define PIO_PD2D_DSR0             (1u << 2)  /**< \brief Usart0 signal: DSR0 */
#define PIO_PD1D_DTR0             (1u << 1)  /**< \brief Usart0 signal: DTR0 */
#define PIO_PD3D_RI0              (1u << 3)  /**< \brief Usart0 signal: RI0 */
#define PIO_PB3C_RTS0             (1u << 3)  /**< \brief Usart0 signal: RTS0 */
#define PIO_PB0C_RXD0             (1u << 0)  /**< \brief Usart0 signal: RXD0 */
#define PIO_PB1C_TXD0             (1u << 1)  /**< \brief Usart0 signal: TXD0 */
/* ========== Pio definition for USART1 peripheral ========== */
#define PIO_PA27A_DTR1            (1u << 27) /**< \brief Usart1 signal: DTR1 */
#define PIO_PA3B_LONCOL1          (1u << 3)  /**< \brief Usart1 signal: LONCOL1 */
#define PIO_PA24A_RTS1            (1u << 24) /**< \brief Usart1 signal: RTS1 */
#define PIO_PA21A_RXD1            (1u << 21) /**< \brief Usart1 signal: RXD1 */
#define PIO_PB4D_TXD1             (1u << 4)  /**< \brief Usart1 signal: TXD1 */
/* ========== Pio definition for USART2 peripheral ========== */
#define PIO_PD4D_DCD2             (1u << 4)  /**< \brief Usart2 signal: DCD2 */
#define PIO_PD6D_DSR2             (1u << 6)  /**< \brief Usart2 signal: DSR2 */
#define PIO_PD5D_DTR2             (1u << 5)  /**< \brief Usart2 signal: DTR2 */
#define PIO_PD7D_RI2              (1u << 7)  /**< \brief Usart2 signal: RI2 */
/* ========== Pio indexes ========== */
#define PIO_PA3_IDX               3
#define PIO_PA4_IDX               4
#define PIO_PA5_IDX               5
#define PIO_PA7_IDX               7
#define PIO_PA8_IDX               8
#define PIO_PA9_IDX               9
#define PIO_PA10_IDX              10
#define PIO_PA11_IDX              11
#define PIO_PA12_IDX              12
#define PIO_PA13_IDX              13
#define PIO_PA14_IDX              14
#define PIO_PA21_IDX              21
#define PIO_PA22_IDX              22
#define PIO_PA24_IDX              24
#define PIO_PA27_IDX              27
#define PIO_PB0_IDX               32
#define PIO_PB1_IDX               33
#define PIO_PB2_IDX               34
#define PIO_PB3_IDX               35
#define PIO_PB4_IDX               36
#define PIO_PB5_IDX               37
#define PIO_PB6_IDX               38
#define PIO_PB7_IDX               39
#define PIO_PB8_IDX               40
#define PIO_PB9_IDX               41
#define PIO_PB12_IDX              44
#define PIO_PD0_IDX               96
#define PIO_PD1_IDX               97
#define PIO_PD2_IDX               98
#define PIO_PD3_IDX               99
#define PIO_PD4_IDX               100
#define PIO_PD5_IDX               101
#define PIO_PD6_IDX               102
#define PIO_PD7_IDX               103
#define PIO_PD8_IDX               104
#define PIO_PD9_IDX               105
#define PIO_PD10_IDX              106
#define PIO_PD11_IDX              107
#define PIO_PD12_IDX              108
#define PIO_PD21_IDX              117
#define PIO_PD22_IDX              118
#define PIO_PD24_IDX              120
#define PIO_PD25_IDX              121
#define PIO_PD26_IDX              122
#define PIO_PD31_IDX              127

#endif /* _SAMV71_PIO_ */
