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

#ifndef _SAMA5D4_ADC_COMPONENT_
#define _SAMA5D4_ADC_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Analog-to-Digital Converter */
/* ============================================================================= */
/** \addtogroup SAMA5D4_ADC Analog-to-Digital Converter */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Adc hardware registers */
typedef struct {
	__O  uint32_t ADC_CR;       /**< \brief (Adc Offset: 0x00) Control Register */
	__IO uint32_t ADC_MR;       /**< \brief (Adc Offset: 0x04) Mode Register */
	__IO uint32_t ADC_SEQR1;    /**< \brief (Adc Offset: 0x08) Channel Sequence Register 1 */
	__I  uint32_t Reserved1[1];
	__O  uint32_t ADC_CHER;     /**< \brief (Adc Offset: 0x10) Channel Enable Register */
	__O  uint32_t ADC_CHDR;     /**< \brief (Adc Offset: 0x14) Channel Disable Register */
	__I  uint32_t ADC_CHSR;     /**< \brief (Adc Offset: 0x18) Channel Status Register */
	__I  uint32_t Reserved2[1];
	__I  uint32_t ADC_LCDR;     /**< \brief (Adc Offset: 0x20) Last Converted Data Register */
	__O  uint32_t ADC_IER;      /**< \brief (Adc Offset: 0x24) Interrupt Enable Register */
	__O  uint32_t ADC_IDR;      /**< \brief (Adc Offset: 0x28) Interrupt Disable Register */
	__I  uint32_t ADC_IMR;      /**< \brief (Adc Offset: 0x2C) Interrupt Mask Register */
	__I  uint32_t ADC_ISR;      /**< \brief (Adc Offset: 0x30) Interrupt Status Register */
	__I  uint32_t Reserved3[2];
	__I  uint32_t ADC_OVER;     /**< \brief (Adc Offset: 0x3C) Overrun Status Register */
	__IO uint32_t ADC_EMR;      /**< \brief (Adc Offset: 0x40) Extended Mode Register */
	__IO uint32_t ADC_CWR;      /**< \brief (Adc Offset: 0x44) Compare Window Register */
	__I  uint32_t Reserved4[2];
	__I  uint32_t ADC_CDR[5];   /**< \brief (Adc Offset: 0x50) Channel Data Register */
	__I  uint32_t Reserved5[12];
	__IO uint32_t ADC_ACR;      /**< \brief (Adc Offset: 0x94) Analog Control Register */
	__I  uint32_t Reserved6[6];
	__IO uint32_t ADC_TSMR;     /**< \brief (Adc Offset: 0xB0) Touchscreen Mode Register */
	__I  uint32_t ADC_XPOSR;    /**< \brief (Adc Offset: 0xB4) Touchscreen X Position Register */
	__I  uint32_t ADC_YPOSR;    /**< \brief (Adc Offset: 0xB8) Touchscreen Y Position Register */
	__I  uint32_t ADC_PRESSR;   /**< \brief (Adc Offset: 0xBC) Touchscreen Pressure Register */
	__IO uint32_t ADC_TRGR;     /**< \brief (Adc Offset: 0xC0) Trigger Register */
	__I  uint32_t Reserved7[8];
	__IO uint32_t ADC_WPMR;     /**< \brief (Adc Offset: 0xE4) Write Protection Mode Register */
	__I  uint32_t ADC_WPSR;     /**< \brief (Adc Offset: 0xE8) Write Protection Status Register */
} Adc;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- ADC_CR : (ADC Offset: 0x00) Control Register -------- */
#define ADC_CR_SWRST (0x1u << 0) /**< \brief (ADC_CR) Software Reset */
#define ADC_CR_START (0x1u << 1) /**< \brief (ADC_CR) Start Conversion */
#define ADC_CR_TSCALIB (0x1u << 2) /**< \brief (ADC_CR) Touchscreen Calibration */
/* -------- ADC_MR : (ADC Offset: 0x04) Mode Register -------- */
#define ADC_MR_TRGSEL_Pos 1
#define ADC_MR_TRGSEL_Msk (0x7u << ADC_MR_TRGSEL_Pos) /**< \brief (ADC_MR) Trigger Selection */
#define ADC_MR_TRGSEL(value) ((ADC_MR_TRGSEL_Msk & ((value) << ADC_MR_TRGSEL_Pos)))
#define   ADC_MR_TRGSEL_ADC_TRIG0 (0x0u << 1) /**< \brief (ADC_MR) ADTRG */
#define   ADC_MR_TRGSEL_ADC_TRIG1 (0x1u << 1) /**< \brief (ADC_MR) TIOA0 */
#define   ADC_MR_TRGSEL_ADC_TRIG2 (0x2u << 1) /**< \brief (ADC_MR) TIOA1 */
#define   ADC_MR_TRGSEL_ADC_TRIG3 (0x3u << 1) /**< \brief (ADC_MR) TIOA2 */
#define   ADC_MR_TRGSEL_ADC_TRIG4 (0x4u << 1) /**< \brief (ADC_MR) PWM event line 0 */
#define   ADC_MR_TRGSEL_ADC_TRIG5 (0x5u << 1) /**< \brief (ADC_MR) PWM_even line 1 */
#define ADC_MR_LOWRES (0x1u << 4) /**< \brief (ADC_MR) Resolution */
#define   ADC_MR_LOWRES_BITS_10 (0x0u << 4) /**< \brief (ADC_MR) 10-bit resolution */
#define   ADC_MR_LOWRES_BITS_8 (0x1u << 4) /**< \brief (ADC_MR) 8-bit resolution */
#define ADC_MR_SLEEP (0x1u << 5) /**< \brief (ADC_MR) Sleep Mode */
#define   ADC_MR_SLEEP_NORMAL (0x0u << 5) /**< \brief (ADC_MR) Normal Mode: The ADC Core and reference voltage circuitry are kept ON between conversions */
#define   ADC_MR_SLEEP_SLEEP (0x1u << 5) /**< \brief (ADC_MR) Sleep Mode: The ADC Core and reference voltage circuitry are OFF between conversions */
#define ADC_MR_PRESCAL_Pos 8
#define ADC_MR_PRESCAL_Msk (0xffu << ADC_MR_PRESCAL_Pos) /**< \brief (ADC_MR) Prescaler Rate Selection */
#define ADC_MR_PRESCAL(value) ((ADC_MR_PRESCAL_Msk & ((value) << ADC_MR_PRESCAL_Pos)))
#define ADC_MR_STARTUP_Pos 16
#define ADC_MR_STARTUP_Msk (0xfu << ADC_MR_STARTUP_Pos) /**< \brief (ADC_MR) Startup Time */
#define ADC_MR_STARTUP(value) ((ADC_MR_STARTUP_Msk & ((value) << ADC_MR_STARTUP_Pos)))
#define   ADC_MR_STARTUP_SUT0 (0x0u << 16) /**< \brief (ADC_MR) 0 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT8 (0x1u << 16) /**< \brief (ADC_MR) 8 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT16 (0x2u << 16) /**< \brief (ADC_MR) 16 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT24 (0x3u << 16) /**< \brief (ADC_MR) 24 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT64 (0x4u << 16) /**< \brief (ADC_MR) 64 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT80 (0x5u << 16) /**< \brief (ADC_MR) 80 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT96 (0x6u << 16) /**< \brief (ADC_MR) 96 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT112 (0x7u << 16) /**< \brief (ADC_MR) 112 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT512 (0x8u << 16) /**< \brief (ADC_MR) 512 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT576 (0x9u << 16) /**< \brief (ADC_MR) 576 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT640 (0xAu << 16) /**< \brief (ADC_MR) 640 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT704 (0xBu << 16) /**< \brief (ADC_MR) 704 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT768 (0xCu << 16) /**< \brief (ADC_MR) 768 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT832 (0xDu << 16) /**< \brief (ADC_MR) 832 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT896 (0xEu << 16) /**< \brief (ADC_MR) 896 periods of ADCClock */
#define   ADC_MR_STARTUP_SUT960 (0xFu << 16) /**< \brief (ADC_MR) 960 periods of ADCClock */
#define ADC_MR_TRACKTIM_Pos 24
#define ADC_MR_TRACKTIM_Msk (0xfu << ADC_MR_TRACKTIM_Pos) /**< \brief (ADC_MR) Tracking Time */
#define ADC_MR_TRACKTIM(value) ((ADC_MR_TRACKTIM_Msk & ((value) << ADC_MR_TRACKTIM_Pos)))
#define ADC_MR_USEQ (0x1u << 31) /**< \brief (ADC_MR) Use Sequence Enable */
#define   ADC_MR_USEQ_NUM_ORDER (0x0u << 31) /**< \brief (ADC_MR) Normal Mode */
#define   ADC_MR_USEQ_REG_ORDER (0x1u << 31) /**< \brief (ADC_MR) User Sequence Mode */
/* -------- ADC_SEQR1 : (ADC Offset: 0x08) Channel Sequence Register 1 -------- */
#define ADC_SEQR1_USCH1_Pos 0
#define ADC_SEQR1_USCH1_Msk (0xfu << ADC_SEQR1_USCH1_Pos) /**< \brief (ADC_SEQR1) User Sequence Number 1 */
#define ADC_SEQR1_USCH1(value) ((ADC_SEQR1_USCH1_Msk & ((value) << ADC_SEQR1_USCH1_Pos)))
#define ADC_SEQR1_USCH2_Pos 4
#define ADC_SEQR1_USCH2_Msk (0xfu << ADC_SEQR1_USCH2_Pos) /**< \brief (ADC_SEQR1) User Sequence Number 2 */
#define ADC_SEQR1_USCH2(value) ((ADC_SEQR1_USCH2_Msk & ((value) << ADC_SEQR1_USCH2_Pos)))
#define ADC_SEQR1_USCH3_Pos 8
#define ADC_SEQR1_USCH3_Msk (0xfu << ADC_SEQR1_USCH3_Pos) /**< \brief (ADC_SEQR1) User Sequence Number 3 */
#define ADC_SEQR1_USCH3(value) ((ADC_SEQR1_USCH3_Msk & ((value) << ADC_SEQR1_USCH3_Pos)))
#define ADC_SEQR1_USCH4_Pos 12
#define ADC_SEQR1_USCH4_Msk (0xfu << ADC_SEQR1_USCH4_Pos) /**< \brief (ADC_SEQR1) User Sequence Number 4 */
#define ADC_SEQR1_USCH4(value) ((ADC_SEQR1_USCH4_Msk & ((value) << ADC_SEQR1_USCH4_Pos)))
/* -------- ADC_CHER : (ADC Offset: 0x10) Channel Enable Register -------- */
#define ADC_CHER_CH0 (0x1u << 0) /**< \brief (ADC_CHER) Channel 0 Enable */
#define ADC_CHER_CH1 (0x1u << 1) /**< \brief (ADC_CHER) Channel 1 Enable */
#define ADC_CHER_CH2 (0x1u << 2) /**< \brief (ADC_CHER) Channel 2 Enable */
#define ADC_CHER_CH3 (0x1u << 3) /**< \brief (ADC_CHER) Channel 3 Enable */
#define ADC_CHER_CH4 (0x1u << 4) /**< \brief (ADC_CHER) Channel 4 Enable */
/* -------- ADC_CHDR : (ADC Offset: 0x14) Channel Disable Register -------- */
#define ADC_CHDR_CH0 (0x1u << 0) /**< \brief (ADC_CHDR) Channel 0 Disable */
#define ADC_CHDR_CH1 (0x1u << 1) /**< \brief (ADC_CHDR) Channel 1 Disable */
#define ADC_CHDR_CH2 (0x1u << 2) /**< \brief (ADC_CHDR) Channel 2 Disable */
#define ADC_CHDR_CH3 (0x1u << 3) /**< \brief (ADC_CHDR) Channel 3 Disable */
#define ADC_CHDR_CH4 (0x1u << 4) /**< \brief (ADC_CHDR) Channel 4 Disable */
/* -------- ADC_CHSR : (ADC Offset: 0x18) Channel Status Register -------- */
#define ADC_CHSR_CH0 (0x1u << 0) /**< \brief (ADC_CHSR) Channel 0 Status */
#define ADC_CHSR_CH1 (0x1u << 1) /**< \brief (ADC_CHSR) Channel 1 Status */
#define ADC_CHSR_CH2 (0x1u << 2) /**< \brief (ADC_CHSR) Channel 2 Status */
#define ADC_CHSR_CH3 (0x1u << 3) /**< \brief (ADC_CHSR) Channel 3 Status */
#define ADC_CHSR_CH4 (0x1u << 4) /**< \brief (ADC_CHSR) Channel 4 Status */
/* -------- ADC_LCDR : (ADC Offset: 0x20) Last Converted Data Register -------- */
#define ADC_LCDR_LDATA_Pos 0
#define ADC_LCDR_LDATA_Msk (0xfffu << ADC_LCDR_LDATA_Pos) /**< \brief (ADC_LCDR) Last Data Converted */
#define ADC_LCDR_CHNB_Pos 12
#define ADC_LCDR_CHNB_Msk (0xfu << ADC_LCDR_CHNB_Pos) /**< \brief (ADC_LCDR) Channel Number */
/* -------- ADC_IER : (ADC Offset: 0x24) Interrupt Enable Register -------- */
#define ADC_IER_EOC0 (0x1u << 0) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 0 */
#define ADC_IER_EOC1 (0x1u << 1) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 1 */
#define ADC_IER_EOC2 (0x1u << 2) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 2 */
#define ADC_IER_EOC3 (0x1u << 3) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 3 */
#define ADC_IER_EOC4 (0x1u << 4) /**< \brief (ADC_IER) End of Conversion Interrupt Enable 4 */
#define ADC_IER_XRDY (0x1u << 20) /**< \brief (ADC_IER) Touchscreen Measure XPOS Ready Interrupt Enable */
#define ADC_IER_YRDY (0x1u << 21) /**< \brief (ADC_IER) Touchscreen Measure YPOS Ready Interrupt Enable */
#define ADC_IER_PRDY (0x1u << 22) /**< \brief (ADC_IER) Touchscreen Measure Pressure Ready Interrupt Enable */
#define ADC_IER_DRDY (0x1u << 24) /**< \brief (ADC_IER) Data Ready Interrupt Enable */
#define ADC_IER_GOVRE (0x1u << 25) /**< \brief (ADC_IER) General Overrun Error Interrupt Enable */
#define ADC_IER_COMPE (0x1u << 26) /**< \brief (ADC_IER) Comparison Event Interrupt Enable */
#define ADC_IER_PEN (0x1u << 29) /**< \brief (ADC_IER) Pen Contact Interrupt Enable */
#define ADC_IER_NOPEN (0x1u << 30) /**< \brief (ADC_IER) No Pen Contact Interrupt Enable */
/* -------- ADC_IDR : (ADC Offset: 0x28) Interrupt Disable Register -------- */
#define ADC_IDR_EOC0 (0x1u << 0) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 0 */
#define ADC_IDR_EOC1 (0x1u << 1) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 1 */
#define ADC_IDR_EOC2 (0x1u << 2) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 2 */
#define ADC_IDR_EOC3 (0x1u << 3) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 3 */
#define ADC_IDR_EOC4 (0x1u << 4) /**< \brief (ADC_IDR) End of Conversion Interrupt Disable 4 */
#define ADC_IDR_XRDY (0x1u << 20) /**< \brief (ADC_IDR) Touchscreen Measure XPOS Ready Interrupt Disable */
#define ADC_IDR_YRDY (0x1u << 21) /**< \brief (ADC_IDR) Touchscreen Measure YPOS Ready Interrupt Disable */
#define ADC_IDR_PRDY (0x1u << 22) /**< \brief (ADC_IDR) Touchscreen Measure Pressure Ready Interrupt Disable */
#define ADC_IDR_DRDY (0x1u << 24) /**< \brief (ADC_IDR) Data Ready Interrupt Disable */
#define ADC_IDR_GOVRE (0x1u << 25) /**< \brief (ADC_IDR) General Overrun Error Interrupt Disable */
#define ADC_IDR_COMPE (0x1u << 26) /**< \brief (ADC_IDR) Comparison Event Interrupt Disable */
#define ADC_IDR_PEN (0x1u << 29) /**< \brief (ADC_IDR) Pen Contact Interrupt Disable */
#define ADC_IDR_NOPEN (0x1u << 30) /**< \brief (ADC_IDR) No Pen Contact Interrupt Disable */
/* -------- ADC_IMR : (ADC Offset: 0x2C) Interrupt Mask Register -------- */
#define ADC_IMR_EOC0 (0x1u << 0) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 0 */
#define ADC_IMR_EOC1 (0x1u << 1) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 1 */
#define ADC_IMR_EOC2 (0x1u << 2) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 2 */
#define ADC_IMR_EOC3 (0x1u << 3) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 3 */
#define ADC_IMR_EOC4 (0x1u << 4) /**< \brief (ADC_IMR) End of Conversion Interrupt Mask 4 */
#define ADC_IMR_XRDY (0x1u << 20) /**< \brief (ADC_IMR) Touchscreen Measure XPOS Ready Interrupt Mask */
#define ADC_IMR_YRDY (0x1u << 21) /**< \brief (ADC_IMR) Touchscreen Measure YPOS Ready Interrupt Mask */
#define ADC_IMR_PRDY (0x1u << 22) /**< \brief (ADC_IMR) Touchscreen Measure Pressure Ready Interrupt Mask */
#define ADC_IMR_DRDY (0x1u << 24) /**< \brief (ADC_IMR) Data Ready Interrupt Mask */
#define ADC_IMR_GOVRE (0x1u << 25) /**< \brief (ADC_IMR) General Overrun Error Interrupt Mask */
#define ADC_IMR_COMPE (0x1u << 26) /**< \brief (ADC_IMR) Comparison Event Interrupt Mask */
#define ADC_IMR_PEN (0x1u << 29) /**< \brief (ADC_IMR) Pen Contact Interrupt Mask */
#define ADC_IMR_NOPEN (0x1u << 30) /**< \brief (ADC_IMR) No Pen Contact Interrupt Mask */
/* -------- ADC_ISR : (ADC Offset: 0x30) Interrupt Status Register -------- */
#define ADC_ISR_EOC0 (0x1u << 0) /**< \brief (ADC_ISR) End of Conversion 0 */
#define ADC_ISR_EOC1 (0x1u << 1) /**< \brief (ADC_ISR) End of Conversion 1 */
#define ADC_ISR_EOC2 (0x1u << 2) /**< \brief (ADC_ISR) End of Conversion 2 */
#define ADC_ISR_EOC3 (0x1u << 3) /**< \brief (ADC_ISR) End of Conversion 3 */
#define ADC_ISR_EOC4 (0x1u << 4) /**< \brief (ADC_ISR) End of Conversion 4 */
#define ADC_ISR_XRDY (0x1u << 20) /**< \brief (ADC_ISR) Touchscreen XPOS Measure Ready */
#define ADC_ISR_YRDY (0x1u << 21) /**< \brief (ADC_ISR) Touchscreen YPOS Measure Ready */
#define ADC_ISR_PRDY (0x1u << 22) /**< \brief (ADC_ISR) Touchscreen Pressure Measure Ready */
#define ADC_ISR_DRDY (0x1u << 24) /**< \brief (ADC_ISR) Data Ready */
#define ADC_ISR_GOVRE (0x1u << 25) /**< \brief (ADC_ISR) General Overrun Error */
#define ADC_ISR_COMPE (0x1u << 26) /**< \brief (ADC_ISR) Comparison Event */
#define ADC_ISR_PEN (0x1u << 29) /**< \brief (ADC_ISR) Pen contact */
#define ADC_ISR_NOPEN (0x1u << 30) /**< \brief (ADC_ISR) No Pen Contact */
#define ADC_ISR_PENS (0x1u << 31) /**< \brief (ADC_ISR) Pen Detect Status */
/* -------- ADC_OVER : (ADC Offset: 0x3C) Overrun Status Register -------- */
#define ADC_OVER_OVRE0 (0x1u << 0) /**< \brief (ADC_OVER) Overrun Error 0 */
#define ADC_OVER_OVRE1 (0x1u << 1) /**< \brief (ADC_OVER) Overrun Error 1 */
#define ADC_OVER_OVRE2 (0x1u << 2) /**< \brief (ADC_OVER) Overrun Error 2 */
#define ADC_OVER_OVRE3 (0x1u << 3) /**< \brief (ADC_OVER) Overrun Error 3 */
#define ADC_OVER_OVRE4 (0x1u << 4) /**< \brief (ADC_OVER) Overrun Error 4 */
/* -------- ADC_EMR : (ADC Offset: 0x40) Extended Mode Register -------- */
#define ADC_EMR_CMPMODE_Pos 0
#define ADC_EMR_CMPMODE_Msk (0x3u << ADC_EMR_CMPMODE_Pos) /**< \brief (ADC_EMR) Comparison Mode */
#define ADC_EMR_CMPMODE(value) ((ADC_EMR_CMPMODE_Msk & ((value) << ADC_EMR_CMPMODE_Pos)))
#define   ADC_EMR_CMPMODE_LOW (0x0u << 0) /**< \brief (ADC_EMR) Generates an event when the converted data is lower than the low threshold of the window. */
#define   ADC_EMR_CMPMODE_HIGH (0x1u << 0) /**< \brief (ADC_EMR) Generates an event when the converted data is higher than the high threshold of the window. */
#define   ADC_EMR_CMPMODE_IN (0x2u << 0) /**< \brief (ADC_EMR) Generates an event when the converted data is in the comparison window. */
#define   ADC_EMR_CMPMODE_OUT (0x3u << 0) /**< \brief (ADC_EMR) Generates an event when the converted data is out of the comparison window. */
#define ADC_EMR_CMPSEL_Pos 4
#define ADC_EMR_CMPSEL_Msk (0xfu << ADC_EMR_CMPSEL_Pos) /**< \brief (ADC_EMR) Comparison Selected Channel */
#define ADC_EMR_CMPSEL(value) ((ADC_EMR_CMPSEL_Msk & ((value) << ADC_EMR_CMPSEL_Pos)))
#define ADC_EMR_CMPALL (0x1u << 9) /**< \brief (ADC_EMR) Compare All Channels */
#define ADC_EMR_CMPFILTER_Pos 12
#define ADC_EMR_CMPFILTER_Msk (0x3u << ADC_EMR_CMPFILTER_Pos) /**< \brief (ADC_EMR) Compare Event Filtering */
#define ADC_EMR_CMPFILTER(value) ((ADC_EMR_CMPFILTER_Msk & ((value) << ADC_EMR_CMPFILTER_Pos)))
#define ADC_EMR_OSR_Pos 16
#define ADC_EMR_OSR_Msk (0x3u << ADC_EMR_OSR_Pos) /**< \brief (ADC_EMR) Over Sampling Rate */
#define ADC_EMR_OSR(value) ((ADC_EMR_OSR_Msk & ((value) << ADC_EMR_OSR_Pos)))
#define   ADC_EMR_OSR_NO_AVERAGE (0x0u << 16) /**< \brief (ADC_EMR) No averaging. ADC sample rate is maximum. */
#define   ADC_EMR_OSR_OSR4 (0x1u << 16)	/**< \brief (ADC_EMR) 1-bit enhanced resolution by averaging. ADC sample rate divided by 4. */
#define   ADC_EMR_OSR_OSR16 (0x2u << 16) /**< \brief (ADC_EMR) 2-bit enhanced resolution by averaging. ADC sample rate divided by 16. */
#define ADC_EMR_ASTE (0x1u << 20) /**< \brief (ADC_EMR) Averaging on Single Trigger Event */
#define   ADC_EMR_ASTE_MULTI_TRIG_AVERAGE (0x0u << 20) /**< \brief (ADC_EMR) The average requests several trigger events. */
#define   ADC_EMR_ASTE_SINGLE_TRIG_AVERAGE (0x1u << 20)	/**< \brief (ADC_EMR) The average requests only one trigger event. */
#define ADC_EMR_TAG (0x1u << 24) /**< \brief (ADC_EMR) Tag of the ADC_LCDR register */
/* -------- ADC_CWR : (ADC Offset: 0x44) Compare Window Register -------- */
#define ADC_CWR_LOWTHRES_Pos 0
#define ADC_CWR_LOWTHRES_Msk (0xfffu << ADC_CWR_LOWTHRES_Pos) /**< \brief (ADC_CWR) Low Threshold */
#define ADC_CWR_LOWTHRES(value) ((ADC_CWR_LOWTHRES_Msk & ((value) << ADC_CWR_LOWTHRES_Pos)))
#define ADC_CWR_HIGHTHRES_Pos 16
#define ADC_CWR_HIGHTHRES_Msk (0xfffu << ADC_CWR_HIGHTHRES_Pos) /**< \brief (ADC_CWR) High Threshold */
#define ADC_CWR_HIGHTHRES(value) ((ADC_CWR_HIGHTHRES_Msk & ((value) << ADC_CWR_HIGHTHRES_Pos)))
/* -------- ADC_CDR[5] : (ADC Offset: 0x50) Channel Data Register -------- */
#define ADC_CDR_DATA_Pos 0
#define ADC_CDR_DATA_Msk (0xfffu << ADC_CDR_DATA_Pos) /**< \brief (ADC_CDR[5]) Converted Data */
/* -------- ADC_ACR : (ADC Offset: 0x94) Analog Control Register -------- */
#define ADC_ACR_PENDETSENS_Pos 0
#define ADC_ACR_PENDETSENS_Msk (0x3u << ADC_ACR_PENDETSENS_Pos) /**< \brief (ADC_ACR) Pen Detection Sensitivity */
#define ADC_ACR_PENDETSENS(value) ((ADC_ACR_PENDETSENS_Msk & ((value) << ADC_ACR_PENDETSENS_Pos)))
/* -------- ADC_TSMR : (ADC Offset: 0xB0) Touchscreen Mode Register -------- */
#define ADC_TSMR_TSMODE_Pos 0
#define ADC_TSMR_TSMODE_Msk (0x3u << ADC_TSMR_TSMODE_Pos) /**< \brief (ADC_TSMR) Touchscreen Mode */
#define ADC_TSMR_TSMODE(value) ((ADC_TSMR_TSMODE_Msk & ((value) << ADC_TSMR_TSMODE_Pos)))
#define   ADC_TSMR_TSMODE_NONE (0x0u << 0) /**< \brief (ADC_TSMR) No Touchscreen */
#define   ADC_TSMR_TSMODE_4_WIRE_NO_PM (0x1u << 0) /**< \brief (ADC_TSMR) 4-wire Touchscreen without pressure measurement */
#define   ADC_TSMR_TSMODE_4_WIRE (0x2u << 0) /**< \brief (ADC_TSMR) 4-wire Touchscreen with pressure measurement */
#define   ADC_TSMR_TSMODE_5_WIRE (0x3u << 0) /**< \brief (ADC_TSMR) 5-wire Touchscreen */
#define ADC_TSMR_TSAV_Pos 4
#define ADC_TSMR_TSAV_Msk (0x3u << ADC_TSMR_TSAV_Pos) /**< \brief (ADC_TSMR) Touchscreen Average */
#define ADC_TSMR_TSAV(value) ((ADC_TSMR_TSAV_Msk & ((value) << ADC_TSMR_TSAV_Pos)))
#define   ADC_TSMR_TSAV_NO_FILTER (0x0u << 4) /**< \brief (ADC_TSMR) No Filtering. Only one ADC conversion per measure */
#define   ADC_TSMR_TSAV_AVG2CONV (0x1u << 4) /**< \brief (ADC_TSMR) Averages 2 ADC conversions */
#define   ADC_TSMR_TSAV_AVG4CONV (0x2u << 4) /**< \brief (ADC_TSMR) Averages 4 ADC conversions */
#define   ADC_TSMR_TSAV_AVG8CONV (0x3u << 4) /**< \brief (ADC_TSMR) Averages 8 ADC conversions */
#define ADC_TSMR_TSFREQ_Pos 8
#define ADC_TSMR_TSFREQ_Msk (0xfu << ADC_TSMR_TSFREQ_Pos) /**< \brief (ADC_TSMR) Touchscreen Frequency */
#define ADC_TSMR_TSFREQ(value) ((ADC_TSMR_TSFREQ_Msk & ((value) << ADC_TSMR_TSFREQ_Pos)))
#define ADC_TSMR_TSSCTIM_Pos 16
#define ADC_TSMR_TSSCTIM_Msk (0xfu << ADC_TSMR_TSSCTIM_Pos) /**< \brief (ADC_TSMR) Touchscreen Switches Closure Time */
#define ADC_TSMR_TSSCTIM(value) ((ADC_TSMR_TSSCTIM_Msk & ((value) << ADC_TSMR_TSSCTIM_Pos)))
#define ADC_TSMR_NOTSDMA (0x1u << 22) /**< \brief (ADC_TSMR) No TouchScreen DMA */
#define ADC_TSMR_PENDET (0x1u << 24) /**< \brief (ADC_TSMR) Pen Contact Detection Enable */
#define ADC_TSMR_PENDBC_Pos 28
#define ADC_TSMR_PENDBC_Msk (0xfu << ADC_TSMR_PENDBC_Pos) /**< \brief (ADC_TSMR) Pen Detect Debouncing Period */
#define ADC_TSMR_PENDBC(value) ((ADC_TSMR_PENDBC_Msk & ((value) << ADC_TSMR_PENDBC_Pos)))
/* -------- ADC_XPOSR : (ADC Offset: 0xB4) Touchscreen X Position Register -------- */
#define ADC_XPOSR_XPOS_Pos 0
#define ADC_XPOSR_XPOS_Msk (0xfffu << ADC_XPOSR_XPOS_Pos) /**< \brief (ADC_XPOSR) X Position */
#define ADC_XPOSR_XSCALE_Pos 16
#define ADC_XPOSR_XSCALE_Msk (0xfffu << ADC_XPOSR_XSCALE_Pos) /**< \brief (ADC_XPOSR) Scale of XPOS */
/* -------- ADC_YPOSR : (ADC Offset: 0xB8) Touchscreen Y Position Register -------- */
#define ADC_YPOSR_YPOS_Pos 0
#define ADC_YPOSR_YPOS_Msk (0xfffu << ADC_YPOSR_YPOS_Pos) /**< \brief (ADC_YPOSR) Y Position */
#define ADC_YPOSR_YSCALE_Pos 16
#define ADC_YPOSR_YSCALE_Msk (0xfffu << ADC_YPOSR_YSCALE_Pos) /**< \brief (ADC_YPOSR) Scale of YPOS */
/* -------- ADC_PRESSR : (ADC Offset: 0xBC) Touchscreen Pressure Register -------- */
#define ADC_PRESSR_Z1_Pos 0
#define ADC_PRESSR_Z1_Msk (0xfffu << ADC_PRESSR_Z1_Pos) /**< \brief (ADC_PRESSR) Data of Z1 Measurement */
#define ADC_PRESSR_Z2_Pos 16
#define ADC_PRESSR_Z2_Msk (0xfffu << ADC_PRESSR_Z2_Pos) /**< \brief (ADC_PRESSR) Data of Z2 Measurement */
/* -------- ADC_TRGR : (ADC Offset: 0xC0) Trigger Register -------- */
#define ADC_TRGR_TRGMOD_Pos 0
#define ADC_TRGR_TRGMOD_Msk (0x7u << ADC_TRGR_TRGMOD_Pos) /**< \brief (ADC_TRGR) Trigger Mode */
#define ADC_TRGR_TRGMOD(value) ((ADC_TRGR_TRGMOD_Msk & ((value) << ADC_TRGR_TRGMOD_Pos)))
#define   ADC_TRGR_TRGMOD_NO_TRIGGER (0x0u << 0) /**< \brief (ADC_TRGR) No trigger, only software trigger can start conversions */
#define   ADC_TRGR_TRGMOD_EXT_TRIG_RISE (0x1u << 0) /**< \brief (ADC_TRGR) External Trigger Rising Edge */
#define   ADC_TRGR_TRGMOD_EXT_TRIG_FALL (0x2u << 0) /**< \brief (ADC_TRGR) External Trigger Falling Edge */
#define   ADC_TRGR_TRGMOD_EXT_TRIG_ANY (0x3u << 0) /**< \brief (ADC_TRGR) External Trigger Any Edge */
#define   ADC_TRGR_TRGMOD_PEN_TRIG (0x4u << 0) /**< \brief (ADC_TRGR) Pen Detect Trigger (shall be selected only if PENDET is set and TSAMOD = Touchscreen only mode) */
#define   ADC_TRGR_TRGMOD_PERIOD_TRIG (0x5u << 0) /**< \brief (ADC_TRGR) ADC Internal Periodic Trigger (see field TRGPER) */
#define   ADC_TRGR_TRGMOD_CONTINUOUS (0x6u << 0) /**< \brief (ADC_TRGR) Continuous Mode */
#define ADC_TRGR_TRGPER_Pos 16
#define ADC_TRGR_TRGPER_Msk (0xffffu << ADC_TRGR_TRGPER_Pos) /**< \brief (ADC_TRGR) Trigger Period */
#define ADC_TRGR_TRGPER(value) ((ADC_TRGR_TRGPER_Msk & ((value) << ADC_TRGR_TRGPER_Pos)))
/* -------- ADC_WPMR : (ADC Offset: 0xE4) Write Protection Mode Register -------- */
#define ADC_WPMR_WPEN (0x1u << 0) /**< \brief (ADC_WPMR) Write Protection Enable */
#define ADC_WPMR_WPKEY_Pos 8
#define ADC_WPMR_WPKEY_Msk (0xffffffu << ADC_WPMR_WPKEY_Pos) /**< \brief (ADC_WPMR) Write Protection Key */
#define ADC_WPMR_WPKEY(value) ((ADC_WPMR_WPKEY_Msk & ((value) << ADC_WPMR_WPKEY_Pos)))
#define   ADC_WPMR_WPKEY_PASSWD (0x414443u << 8) /**< \brief (ADC_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit.Always reads as 0 */
/* -------- ADC_WPSR : (ADC Offset: 0xE8) Write Protection Status Register -------- */
#define ADC_WPSR_WPVS (0x1u << 0) /**< \brief (ADC_WPSR) Write Protection Violation Status */
#define ADC_WPSR_WPVSRC_Pos 8
#define ADC_WPSR_WPVSRC_Msk (0xffffu << ADC_WPSR_WPVSRC_Pos) /**< \brief (ADC_WPSR) Write Protection Violation Source */

/*@}*/

#endif /* _SAMA5D4_ADC_COMPONENT_ */
