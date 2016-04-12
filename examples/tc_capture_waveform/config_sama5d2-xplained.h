#ifndef __CONFIG_SAMA5D2_XPLAINED_H__
#define __CONFIG_SAMA5D2_XPLAINED_H__

/* ============ definition for example "tc_capture_waveform" ============== */
/** define channel to output the waveform */
#define CHANNEL_TC_WAVEFORM_OUT 0

/** define pin to output the waveform */
#define PIN_TC_WAVEFORM_OUT \
	{ PIO_GROUP_A, PIO_PA19D_TIOA0, PIO_PERIPH_D, PIO_DEFAULT }

/** define channel to output the waveform */
#define CHANNEL_TC_CAPTURE_IN 2

/** define pin to capture the waveform */
#define PIN_TC_CAPTURE_IN \
	{ PIO_GROUP_B, PIO_PB22D_TIOA2, PIO_PERIPH_D, PIO_DEFAULT }

#endif