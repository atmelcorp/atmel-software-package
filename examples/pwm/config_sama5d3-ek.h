#ifndef __CONFIG_SAMA5D3_EK_H__
#define __CONFIG_SAMA5D3_EK_H__

/* =================== definition for example "pwm" =================== */

#define PWM_ADDR PWM0

/** define PWM channel to output PWM signal */
#define CHANNEL_PWM 1

/** define PWM pin to output PWM signal */
#define PIN_PWM \
	{ PIO_GROUP_A, PIO_PA22B_PWM0_H1, PIO_PERIPH_B, PIO_DEFAULT}

/** define capture tc */
#define TC_CAPTURE TC0

/** define TC channel to output the waveform */
#define CHANNEL_TC_CAPTURE_IN 1

/** define TC pin to capture the waveform */
#define PIN_TC_CAPTURE_IN \
	{ PIO_GROUP_C, PIO_PC12B_TIOA1, PIO_PERIPH_B, PIO_DEFAULT }

#endif
