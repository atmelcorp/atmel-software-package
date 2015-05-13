/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2011, Atmel Corporation
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
 *  \file
 *
 *  \section Purpose
 *
 *  Interface for configuration the Analog-to-Digital Converter (ADC) peripheral.
 *
 *  \section Usage
 *
 *  -# Configurate the pins for ADC.
 *  -# Initialize the ADC with adc_initialize().
 *  -# Set ADC clock and timing with adc_set_clock() and adc_set_timing().
 *  -# Select the active channel using adc_enable_channel().
 *  -# Start the conversion with adc_start_conversion().
 *  -# Wait the end of the conversion by polling status with adc_get_status().
 *  -# Finally, get the converted data using adc_get_converted_data() or adc_get_last_converted_data().
 *
*/
#ifndef _ADC_
#define _ADC_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include <assert.h>
#include <stdint.h>

/*------------------------------------------------------------------------------
 *         Definitions
 *------------------------------------------------------------------------------*/

/* Max. ADC Clock Frequency (Hz) */
#define ADC_CLOCK_MAX   20000000

/* Max. normal ADC startup time (us) */
#define ADC_STARTUP_NORMAL_MAX     40
/* Max. fast ADC startup time (us) */
#define ADC_STARTUP_FAST_MAX       12

/* Definitions for ADC channels */
#define ADC_CHANNEL_0  0
#define ADC_CHANNEL_1  1
#define ADC_CHANNEL_2  2
#define ADC_CHANNEL_3  3
#define ADC_CHANNEL_4  4

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------
 *         Macros function of register access
 *------------------------------------------------------------------------------*/

#define adc_get_mode_reg( pAdc )                ((pAdc)->ADC_MR)

#define adc_start_conversion( pAdc )           ((pAdc)->ADC_CR = ADC_CR_START)

#define adc_enable_channel( pAdc, dwChannel )    {\
            (pAdc)->ADC_CHER = (1 << (dwChannel));\
        }

#define adc_disable_channel(pAdc, dwChannel)  {\
            (pAdc)->ADC_CHDR = (1 << (dwChannel));\
        }

#define adc_enable_interrupt(pAdc, dwMode)            {\
            (pAdc)->ADC_IER = (dwMode);\
        }

#define adc_disable_interrupt(pAdc, dwMode)           {\
            (pAdc)->ADC_IDR = (dwMode);\
        }

#define adc_set_channel_gain(pAdc,dwMode)       {\
            (pAdc)->ADC_CGR = dwMode;\
        }

#define adc_enable_data_ready_it(pAdc)         ((pAdc)->ADC_IER = ADC_IER_DRDY)

#define adc_get_status(pAdc)                 ((pAdc)->ADC_ISR)

#define adc_get_compare_mode(pAdc)            (((pAdc)->ADC_EMR)& (ADC_EMR_CMPMODE_Msk))

#define adc_get_channel_status(pAdc)          ((pAdc)->ADC_CHSR)

#define adc_interrupt_mask_status(pAdc)    ((pAdc)->ADC_IMR)

#define adc_get_last_converted_data(pAdc)      ((pAdc)->ADC_LCDR)

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/
void adc_initialize(Adc * pAdc, uint32_t dwId);
extern uint32_t adc_set_clock(Adc * pAdc, uint32_t dwPres, uint32_t dwMck);
void adc_set_timing(Adc * pAdc, uint32_t dwStartup,
			  uint32_t dwTracking, uint32_t dwSettling);
void adc_set_trigger(Adc * pAdc, uint32_t dwTrgSel);
void adc_set_trigger_mode(Adc * pAdc, uint32_t dwMode);
void adc_set_low_resolution(Adc * pAdc, uint32_t bEnDis);
void adc_set_sleep_mode(Adc * pAdc, uint8_t bEnDis);
void adc_set_fast_wakeup(Adc * pAdc, uint8_t bEnDis);
void adc_set_sequence_mode(Adc * pAdc, uint8_t bEnDis);
void adc_set_sequence(Adc * pAdc, uint32_t dwSEQ1, uint32_t dwSEQ2);
void adc_set_sequence_by_list(Adc * pAdc, uint8_t ucChList[],
				  uint8_t ucNumCh);
void adc_set_tag_enable(Adc * pAdc, uint8_t bEnDis);
void adc_configure_ext_mode(Adc * pAdc, uint32_t dwMode);
void adc_set_compare_channel(Adc * pAdc, uint32_t dwChannel);
void adc_set_compare_mode(Adc * pAdc, uint32_t dwMode);
void adc_set_comparison_window(Adc * pAdc, uint32_t dwHi_Lo);
extern uint8_t adc_set_configuration(Adc * pAdc, uint32_t dwMcK);
extern uint32_t adc_get_converted_data(Adc * pAdc, uint32_t dwChannel);
void adc_set_ts_average(Adc * pADC, uint32_t dwAvg2Conv);
extern uint32_t adc_get_ts_xposition(Adc * pADC);
extern uint32_t adc_get_ts_yposition(Adc * pADC);
extern uint32_t adc_get_ts_pressure(Adc * pADC);
void adc_set_ts_debounce(Adc * pADC, uint32_t dwTime);
void adc_set_ts_pen_detect(Adc * pADC, uint8_t bEnDis);
void adc_set_startup_time(Adc * pAdc, uint32_t dwUs);
void adc_set_tracking_time(Adc * pAdc, uint32_t dwNs);
void adc_set_trigger_period(Adc * pAdc, uint32_t dwPeriod);
void adc_set_ts_mode(Adc * pADC, uint32_t dwMode);
void adc_ts_calibration(Adc * pAdc);

#ifdef __cplusplus
}
#endif
#endif				/* #ifndef _ADC_ */
