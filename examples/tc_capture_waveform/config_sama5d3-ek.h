#ifndef __CONFIG_SAMA5D3_EK_H__
#define __CONFIG_SAMA5D3_EK_H__

/* ============ definition for example "tc_capture_waveform" ============== */

/** define channel to output the waveform */
#define CHANNEL_TC_WAVEFORM_OUT 2

/** define pin to output the waveform */
#define PIN_TC_WAVEFORM_OUT \
	{ PIO_GROUP_E, PIO_PE27B_TIOA2, PIO_PERIPH_B, PIO_DEFAULT }

/** define channel to output the waveform */
#define CHANNEL_TC_CAPTURE_IN 1

/** define pin to capture the waveform */
#define PIN_TC_CAPTURE_IN \
	{ PIO_GROUP_C, PIO_PC12B_TIOA1, PIO_PERIPH_B, PIO_DEFAULT }

#endif
