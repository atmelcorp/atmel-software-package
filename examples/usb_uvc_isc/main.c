/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
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
 * \page usb_video USB Video Example
 *
 * \section Purpose
 *
 * The USB Video Example will help you to get familiar with the
 * USB Device Port(UDP) and ISC interface on SAMA5D2 microcontrollers.
 *
 * \section Requirements
 *
 * - On-board ISC interface.
 * - External sensor, in the example, Omnivision OV2643/OV5640/OV7740/OV7670/OV9740
 * sensor could be used.
 * When an EK running this program connected to a host (PC for example), with
 * USB cable, the EK appears as a video camera for the host.
 *
 * \note
 * For the limitation of external memory size, this example only support for
 * VGA/QVGA format.
 *
 * \section Description
 * The USB video can help you to be familiar with the ISC (Image Sensor
 * controller) to connects a CMOS-type image sensor to the processor and
 * provides image capture in various formats.
 * Data stream Pipe line: ISC PFE->RLP(DAT8)->DAM8->USB YUV2 display
 *
 * \section Usage
 *
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 baud rates
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *     \code
 *     -- USB UVC ISC Example xxx --
 *     -- SAMxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 * -# When connecting USB cable to windows, the
 *    new "xxx USB Device" appears in the
 *    hardware %device list.
 * -# Once the device is connected and configured on windows XP,
 *    "USB Video Device" will appear in "My Computer", you can double click
 *    it to preview with default resolution - QVGA.
 * -# Other video camera programs can also be used to monitor the capture
 *    output. The demo is tested on windows XP through "AmCap.exe".
 *
 * \section References
 * - usb_uvc_isc/main.c
 */

/**
 * \file
 *
 * This file contains all the specific code for the
 * usb_uvc_isc
 *
 * \section Contents
 *
 * The code can be roughly broken down as follows:
 *    - Configuration functions
 *       - Configure TWI
 *       - Configure pins for OV sensor
 *       - Configure ISC controller
 *    - Interrupt handlers
 *       - ISC_Handler
 *    - The main function, which implements the program behaviour
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"
#include "rand.h"

#include "misc/console.h"
#include "timer.h"

#include "peripherals/aic.h"
#include "peripherals/isc.h"
#include "misc/cache.h"
#include "peripherals/pio.h"
#include "peripherals/pit.h"
#include "peripherals/pmc.h"
#include "peripherals/twid.h"

#include "video/image_sensor_inf.h"

#include "usb/common/uvc/usb_video.h"
#include "usb/common/uvc/uvc_descriptors.h"
#include "usb/device/usbd_driver.h"
#include "usb/device/usbd.h"
#include "usb/device/usbd_hal.h"
#include "usb/device/uvc/uvc_driver.h"
#include "usb/device/uvc/uvc_function.h"

#include "../usb_common/main_usb_common.h"

#include <string.h>
#include <stdbool.h>
#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** TWI clock frequency in Hz. */
#define TWCK 400000

#define NUM_FRAME_BUFFER     4

/*----------------------------------------------------------------------------
 *          External variables
 *----------------------------------------------------------------------------*/

extern const USBDDriverDescriptors usbdDriverDescriptors;

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** PIO pins to configured for ISC */
const struct _pin pins_twi[] = ISC_TWI_PINS;

/** Descriptor view 0 is used when the pixel or data stream is packed */
CACHE_ALIGNED static struct _isc_dma_view0 isc_dma_desc[NUM_FRAME_BUFFER];

/** TWI driver instance.*/
static struct _twi_desc twid = {
	.addr = ISC_TWI_ADDR,
	.freq = TWCK,
	.transfer_mode = TWID_MODE_POLLING
};

static volatile bool capture_started = false;

static uint8_t sensor_idx;

/* Image output bit width */
static sensor_output_bit_t sensor_output_bit_width;

/* Image resolution */
static sensor_output_resolution_t image_resolution = QVGA;

/* Image size in preview mode */
static uint32_t image_width, image_height;

static uint8_t frame_format;

static volatile uint32_t frame_idx = 0;

/** Supported sensor profiles */
static const sensor_profile_t *sensor_profiles[6] = {
	&ov2640_profile,
	&ov2643_profile,
	&ov5640_profile,
	&ov7670_profile,
	&ov7740_profile,
	&ov9740_profile
};

/** Video buffers */
CACHE_ALIGNED_DDR
static uint8_t stream_buffers[FRAME_BUFFER_SIZEC(640, 480) * NUM_FRAME_BUFFER];

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief TWI initialization.
 */
static void configure_twi(void)
{
	/* Configure TWI pins. */
	pio_configure(pins_twi, ARRAY_SIZE(pins_twi));
	/* Enable TWI peripheral clock */
	pmc_enable_peripheral(get_twi_id_from_addr(ISC_TWI_ADDR));
	/* Configure TWI */
	twid_configure(&twid);
}

/**
 * \brief Set up DMA Descriptors.
 */
static void configure_dma_linklist(void)
{
	uint8_t i;

	for(i = 0; i < NUM_FRAME_BUFFER; i++) {
		isc_dma_desc[i].ctrl = ISC_DCTRL_DVIEW_PACKED | ISC_DCTRL_DE;
		isc_dma_desc[i].next_desc = (uint32_t)&isc_dma_desc[i + 1];
		isc_dma_desc[i].addr = (uint32_t)stream_buffers + i * FRAME_BUFFER_SIZEC(image_width, image_height);
		isc_dma_desc[i].stride = 0;
	}
	isc_dma_desc[i - 1].next_desc = (uint32_t)&isc_dma_desc[0];
	cache_clean_region(&isc_dma_desc, sizeof(isc_dma_desc));
}

/**
 * \brief ISC interrupt handler.
 */
static void isc_handler(void)
{
	uint32_t status = isc_interrupt_status();

	if ((status & ISC_INTSR_VD) == ISC_INTSR_VD) {
		if (!capture_started) {
			isc_start_capture();
			capture_started = true;
			printf("CapS\r\n");
		}
		frame_idx = (frame_idx == (NUM_FRAME_BUFFER - 1)) ? 0 : (frame_idx + 1);
		uvc_function_update_frame_idx(frame_idx);
	}
}

/**
 * \brief ISC initialization.
 */
static void configure_isc(void)
{
	/* Configurer the Parallel Front End module performs data
	 * re-sampling across clock domain boundary. ISC_PFE_CFG0.BPS
	 * shows the number of bits per sample depends on the bit
	 * width of sensor output. The PFE module outputs a 12-bit
	 * data on the vp_data[11:0] bus */
	aic_disable(ID_ISC);
	isc_software_reset();
	isc_pfe_set_video_mode(ISC_PFE_CFG0_MODE_PROGRESSIVE);
	isc_pfe_set_bps(ISC_PFE_CFG0_BPS(sensor_output_bit_width));
	isc_pfe_set_sync_polarity(0, ISC_PFE_CFG0_VPOL);

	/* Set Continuous Acquisition mode */
	isc_pfe_set_continuous_shot();
	isc_cfa_enabled(0);
	isc_wb_enabled(0);
	isc_gamma_enabled(0, 0);
	isc_csc_enabled(0);
	isc_sub422_enabled(0);
	isc_sub420_configure(0,0);
	isc_update_profile();

	/* Configure DAT8 output format before the DMA master module */
	isc_rlp_configure(ISC_RLP_CFG_MODE_DAT8, 0);

	/* Set DAM for 8-bit packaged stream with descriptor view 0 used
	   for the data stream is packed*/
	isc_dma_configure_input_mode(ISC_DCFG_IMODE_PACKED8);
	isc_dma_configure_desc_entry((uint32_t)&isc_dma_desc);
	isc_dma_enable(ISC_DCTRL_DVIEW_PACKED | ISC_DCTRL_DE);
	isc_dma_adderss(0, (uint32_t)stream_buffers, 0);

	isc_update_profile();
	aic_set_source_vector(ID_ISC, isc_handler);
	isc_interrupt_status();
	isc_enable_interrupt(ISC_INTEN_VD);
	capture_started = false;
	aic_enable(ID_ISC);
}

static void start_preview(void)
{
	sensor_output_format_t sensor_mode = YUV_422;

	/* Re-configure sensor with giving resolution */
	if (sensor_setup(&twid, sensor_profiles[sensor_idx], image_resolution, sensor_mode) != SENSOR_OK) {
		printf("-E- Sensor setup failed.");
		while (1);
	}
	/* Retrieve sensor output format and size */
	sensor_get_output(image_resolution, sensor_mode, &sensor_output_bit_width,
			&image_width, &image_height);

	printf("-I- Bit width = %d, Image Width = %d, Image Height=%d \n\r",
			(unsigned)(sensor_output_bit_width + 8),
			(unsigned)image_width, (unsigned)image_height);

	/* Configure ISC */
	configure_dma_linklist();
	configure_isc();
}


/**
 *  Invoked whenever a SETUP request is received from the host. Forwards the
 *  request to the standard handler.
 */
void usbd_callbacks_request_received(const USBGenericRequest *request)
{
	uvc_driver_request_handler(request);
}

/**
 * Invoked whenever the active setting of an interface is changed by the
 * host. Reset streaming interface.
 * \param interface Interface number.
 * \param setting Newly active setting.
 */
void usbd_driver_callbacks_interface_setting_changed(uint8_t interface, uint8_t setting )
{
	uvc_driver_interface_setting_changed_handler(interface, setting);
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Application entry point for ISI USB video example.
 *
 * \return Unused (ANSI-C compatibility).
 */
extern int main( void )
{
	int i;
	uint8_t key;
	bool is_usb_vid_on = false;

	/* Output example information */
	console_example_info("USB UVC ISC Example");

	/* TWI Initialize */
	configure_twi();

	printf("Image Sensor Selection:\n\r");
	for (i = 0; i < ARRAY_SIZE(sensor_profiles); i++)
		printf("- '%d' %s\n\r", i + 1, sensor_profiles[i]->name);
	for(;;) {
		printf("Press [1..%d] to select sensor\n\r",
			ARRAY_SIZE(sensor_profiles));
		key = console_get_char();
		if ((key >= '1') && (key <= ('1' + ARRAY_SIZE(sensor_profiles)))) {
			sensor_idx = key - '1';
			break;
		}
	}

	usb_power_configure();

	uvc_driver_initialize(&usbdDriverDescriptors, (uint32_t)stream_buffers, NUM_FRAME_BUFFER);

	/* connect if needed */
	usb_vbus_configure();

	/* clear video buffer */

	while (1) {
		if (usbd_get_state() < USBD_STATE_CONFIGURED) {
			continue;
		}

		if (is_usb_vid_on) {
			if (!uvc_function_is_video_on()) {
				is_usb_vid_on = false;
				isc_stop_capture();
				isc_disable_interrupt(-1);
				capture_started = false;
				printf("CapE\r\n");
				printf("vidE\r\n");
				frame_idx = 0;
			}
		} else {
			if (uvc_function_is_video_on()) {
				is_usb_vid_on = true;
				frame_format = uvc_function_get_frame_format();
				if (frame_format == 1) {
					image_resolution = QVGA;
				}
				else if (frame_format == 2) {
					image_resolution = VGA;
				} else {
					printf ("-I- Only support VGA and QVGA format\r\n");
					image_resolution = QVGA;
				}
				memset(stream_buffers, 0, sizeof(stream_buffers));
				cache_clean_region(stream_buffers, sizeof(stream_buffers));
				start_preview();
				uvc_function_payload_sent(NULL, USBD_STATUS_SUCCESS, 0, 0);
				printf("vidS\r\n");
			}
		}
	}
}
