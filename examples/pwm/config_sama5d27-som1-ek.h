#ifndef __CONFIG_SAMA5D27_SOM1_EK_H__
#define __CONFIG_SAMA5D27_SOM1_EK_H__

/* =================== definition for example "pwm" =================== */

#define PWM_ADDR PWM0

/** define PWM channel to output PWM signal */
#define CHANNEL_PWM PWM_LED_CH_1

/** define PWM pin to output PWM signal */
#define PIN_PWM PIN_PWM_LED_1

/** define capture tc */
#define TC_CAPTURE TC1

/** define TC channel to output the waveform */
#define CHANNEL_TC_CAPTURE_IN 1

/** define TC pin to capture the waveform */
#define PIN_TC_CAPTURE_IN \
	 { PIO_GROUP_C, PIO_PC9D_TIOA4,  PIO_PERIPH_D, PIO_DEFAULT }
#endif
