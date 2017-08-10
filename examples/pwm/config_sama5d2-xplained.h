#ifndef __CONFIG_SAMA5D2_XPLAINED_H__
#define __CONFIG_SAMA5D2_XPLAINED_H__

/* =================== definition for example "pwm" =================== */

#define PWM_ADDR PWM0

/** define PWM channel to output PWM signal */
#define CHANNEL_PWM PWM_LED_CH_0

/** define PWM pin to output PWM signal */
#define PIN_PWM PIN_PWM_LED_0

/** define capture tc */
#define TC_CAPTURE TC0

/** define TC channel to output the waveform */
#define CHANNEL_TC_CAPTURE_IN 2

/** define TC pin to capture the waveform */
#define PIN_TC_CAPTURE_IN \
	{ PIO_GROUP_B, PIO_PB22D_TIOA2, PIO_PERIPH_D, PIO_DEFAULT }

#endif
