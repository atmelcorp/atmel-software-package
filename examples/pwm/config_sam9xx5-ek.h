#ifndef __CONFIG_SAM9XX5_EK_H__
#define __CONFIG_SAM9XX5_EK_H__

/* =================== definition for example "pwm" =================== */

#define PWM_ADDR PWM0

/** define PWM channel to output PWM signal */
#define CHANNEL_PWM 1

/** define PWM pin to output PWM signal */
#define PIN_PWM \
	{ PIO_GROUP_C, PIO_PC11C_PWM0_1, PIO_PERIPH_C, PIO_DEFAULT}

/** define capture tc */
#define TC_CAPTURE TC0

/** define TC channel to output the waveform */
#define CHANNEL_TC_CAPTURE_IN 1

/** define TC pin to capture the waveform */
#define PIN_TC_CAPTURE_IN \
	{ PIO_GROUP_A, PIO_PA22A_TIOA1, PIO_PERIPH_A, PIO_DEFAULT }

#endif
