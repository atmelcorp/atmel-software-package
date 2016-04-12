#ifndef __CONFIG_SAMA5D4_XPLAINED_H__
#define __CONFIG_SAMA5D4_XPLAINED_H__

/* ============ definition for example "tc_capture_waveform" ============== */
/** define channel to output the waveform */
#define CHANNEL_TC_WAVEFORM_OUT 0

/** define pin to output the waveform */
#define PIN_TC_WAVEFORM_OUT \
	{ PIO_GROUP_E, PIO_PE15C_TIOA0, PIO_PERIPH_C, PIO_DEFAULT }

/** define channel to output the waveform */
#define CHANNEL_TC_CAPTURE_IN 1

/** define pin to capture the waveform */
#define PIN_TC_CAPTURE_IN \
	{ PIO_GROUP_E, PIO_PE12B_TIOA1, PIO_PERIPH_B, PIO_DEFAULT }

#endif