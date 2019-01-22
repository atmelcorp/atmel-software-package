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

#ifndef __CONFIG_SAM9X60_EK_H__
#define __CONFIG_SAM9X60_EK_H__

/* =================== definition for example "pwm" =================== */

#define PWM_ADDR PWM0

/** define PWM channel to output PWM signal */
#define CHANNEL_PWM 0

/** define PWM pin to output PWM signal */
#define PIN_PWM \
	{ PIO_GROUP_B, PIO_PB11B_PWM0, PIO_PERIPH_B, PIO_DEFAULT}

/** define capture tc */
#define TC_CAPTURE TC0

/** define TC channel to output the waveform */
#define CHANNEL_TC_CAPTURE_IN 0

/** define TC pin to capture the waveform */
#define PIN_TC_CAPTURE_IN \
	{ PIO_GROUP_A, PIO_PA21A_TIOA0, PIO_PERIPH_A, PIO_DEFAULT }

/** set PA29 low to connect PIO_PA21A_TIOA0 with J15 pin 14*/
#define SETUP_CAPTURE_PIN do{ \
		const struct _pin pin_tioa0_connect = \
		    { PIO_GROUP_A, PIO_PA29, PIO_OUTPUT_0, PIO_DEFAULT }; \
		pio_configure(&pin_tioa0_connect, 1); \
	}while(0)

#endif
