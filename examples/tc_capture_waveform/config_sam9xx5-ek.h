#ifndef __CONFIG_SAM9XX5_EK_H__
#define __CONFIG_SAM9XX5_EK_H__

/* ============ definition for example "tc_capture_waveform" ============== */

/** define channel to output the waveform */
#define CHANNEL_TC_WAVEFORM_OUT 1

/** define pin to output the waveform */
#define PIN_TC_WAVEFORM_OUT \
	{ PIO_GROUP_A, PIO_PA22A_TIOA1, PIO_PERIPH_A, PIO_DEFAULT }

/** define channel to output the waveform */
#define CHANNEL_TC_CAPTURE_IN 2

/** define pin to capture the waveform */
#define PIN_TC_CAPTURE_IN \
	{ PIO_GROUP_A, PIO_PA23A_TIOA2, PIO_PERIPH_A, PIO_DEFAULT }

#endif
