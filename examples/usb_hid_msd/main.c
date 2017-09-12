/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
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
/** \cond usb_hid_msd
 * \page usb_hid_msd USB HID(Keyboard)+MSD Example
 *
 * \section Purpose
 *
 * The USB COMPOSITE Project will help you to get familiar with the
 * USB Device Port(UDP)interface and also some of the other interfaces in
 * SAM9 microcontrollers. Also it can help you to be familiar with the USB
 * Framework that is used for rapid development of USB-compliant class
 * drivers such as USB Communication Device class (CDC), and how to combine
 * two USB functions to a single composite device (such as CDC + MSD).
 *
 * \section Requirements
 *
 * This package can be used with some of Atmel evaluation kits that have UDP
 * interface, depending on the functions included.
 *
 *  \section win_drv_update Windows Driver Update
 *
 * The composite device is generally supported by Microsoft windows, but some
 * patches are needed for muti-interface functions such as CDC & Audio. The
 * example composite devices are tested under windows XP (SP3). For CDC
 * serial port, additional windows driver file (CompositeCDCSerial.inf) can
 * be found at usb\\device\\composite\\drv.
 *
 * The following is alternate update to fix the composite device support
 * on windows XP:
 *
 * \subsection install_win_sp3 Install Windows Service Pack 3 (SP3)
 *
 * All the fixes for USB generic driver are included in window XP service pack
 * 3. It can be found at
 * http://technet.microsoft.com/zh-cn/windows/bb794714(en-us).aspx .
 *
 * \subsection install_win_hotfix Install Windows Hot Fixes
 *
 * Two hot fixes are necessary for window to recognize the composite device
 * correctly:
 *
 * -# http://support.microsoft.com/kb/814560
 * -# http://support.microsoft.com/kb/918365
 *
 * \section Description
 *
 * The demo simulates a USB composite device with HID Keyboard function and
 * USB Disk function integrated.
 *
 * When an EK running this program connected to a host (PC for example), with
 * USB cable, host will notice the attachment of a USB device. No device
 * driver offered for the device now.
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board. Please
 *    refer to the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6421.pdf">
 *    SAM-BA User Guide</a>, the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *    GNU-Based Software Development</a> application note or to the
 *    <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *    IAR EWARM User Guide</a>, depending on your chosen solution.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *     \code
 *     -- USB HIDMSD Device Project xxx --
 *     -- SAMxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 * -# When connecting USB cable to windows, the LED blinks, and the host
 *    reports a new USB device attachment.
 * -# For the windows driver installation and the test functions, please
 *      refer to "USB HID Keyboard Project" &
 *      "USB Device Mass Storage Project".
 *
 * \section References
 * - usb_hid_msd/main.c
 * - pio: Pin configurations and peripheral configure.
 * - memories: Storage Media interface for MSD
 * - usb: USB Device Framework, USB CDC driver and UDP interface driver
 *    - \ref usbd_framework
 *        - \ref usbd_api
 *    - \ref usbd_composite "composite"
 *       - \ref usbd_composite_drv
 *    - \ref usbd_hid "hid" \\ \ref usbd_hid_key "hid-keyboard"
 *       - \ref usbd_hid_kbd_drv
 *    - \ref usbd_msd "massstorage"
 *       - \ref usbd_msd_drv
 * - projects:
 *    - \ref usb_hid_keyboard
 *    - \ref usb_massstorage
 *
 */

/**
 * \file
 *
 * This file contains all the specific code for the
 * usb_hid_msd
 *
 * \section Contents
 *
 * The code can be roughly broken down as follows:
 *    - Configuration functions
 *       - vbus_configure
 *       - pio configurations in start of main
 *    - Interrupt handlers
 *       - ISR_Vbus
 *    - Callback functions
 *       - usbd_callbacks_request_received
 *    - The main function, which implements the program behavior
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "trace.h"

#include "gpio/pio.h"

#include "libstoragemedia/media.h"
#include "libstoragemedia/media_private.h"
#include "libstoragemedia/media_ramdisk.h"

#include "serial/console.h"
#include "led/led.h"

#include "usb/device/msd/msd_driver.h"
#include "usb/device/msd/msd_lun.h"
#include "usb/device/composite/hid_msd_driver.h"
#include "usb/device/hid/hidd_keyboard.h"
#include "usb/device/hid/hidd_keyboard_driver.h"
#include "../usb_common/main_usb_common.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*---------------------------------------------------------------------------
 *      Definitions
 *---------------------------------------------------------------------------*/

/** Master clock frequency in Hz */
#define MCK                 BOARD_MCK

/** Number of keys used in the example. */
#define NUM_KEYS            3

/** Num lock LED index. */
#define LED_NUMLOCK         0


/** Maximum number of LUNs which can be defined. */
#define MAX_LUNS            1
/** Media index for different disks */
#define DRV_RAMDISK         0    /**< RAM disk */
#define DRV_SDMMC           1    /**< SD card */
#define DRV_NAND            2    /**< Nand flash */

/** Size of one block in bytes. */
#define BLOCK_SIZE          512

/** Size of the MSD IO buffer in bytes (6K, more the better). */
#define MSD_BUFFER_SIZE     (128*BLOCK_SIZE)

/** Ramdisk size: at least 20K (Windows can not format the disk if lower than 20K) */
#if defined(CONFIG_BOARD_SAME70_XPLAINED) || defined(CONFIG_BOARD_SAMV71_XPLAINED)
  #define RAMDISK_SIZE        (32*1024)
#else
  #define RAMDISK_SIZE        (8*1024*1024)
#endif

/** Size of the reserved DDRAM (32M) */
#define DDRAM_RESERVE_SIZE  (32*1024*1024)

/** Delay loop for MSD refresh */
#define MSD_REFRESH_LOOP    500000

/*----------------------------------------------------------------------------
 *        External variables
 *----------------------------------------------------------------------------*/

/** Descriptor list for device enumeration */
extern const USBDDriverDescriptors hid_msdd_driver_descriptors;

/*----------------------------------------------------------------------------
 *        Global variables
 *----------------------------------------------------------------------------*/

/*- HID */

#ifdef PIN_PUSHBUTTON_1
/** Push button pin to configure for the application. */
static struct _pin pin_push_button = PIN_PUSHBUTTON_1;
#endif

/** Array of key codes produced by each button. */
static uint8_t key_codes[NUM_KEYS] = {
	HIDKeypad_T,
	HIDKeypad_U,
	HIDKeypad_NUMLOCK,
};

SECTION(".region_ddr")
ALIGNED(BLOCK_SIZE)
static uint8_t ramdisk_reserved[RAMDISK_SIZE];

/** Current status (pressed or not) for each key. */
static bool key_status[NUM_KEYS];

/*- MSD */
/** Available medias. */
struct _media medias[MAX_LUNS];

/** Device LUNs. */
MSDLun luns[MAX_LUNS];

/** LUN read/write buffer. */
SECTION(".region_ddr")
ALIGNED(BLOCK_SIZE)
uint8_t msd_buffer[MSD_BUFFER_SIZE];

/** Total data write to disk */
uint32_t msd_write_total = 0;
/** Delay for data write refresh */
uint32_t msd_refresh_delay = MSD_REFRESH_LOOP;

/**
 * Invoked when the configuration of the device changes. Parse used endpoints.
 * \param cfgnum New configuration number.
 */
void usbd_driver_callbacks_configuration_changed(uint8_t cfgnum)
{
	hid_msdd_driver_configuration_changed_handler(cfgnum);
}

/**
 * Invoked when a new SETUP request is received from the host. Forwards the
 * request to the Mass Storage device driver handler function.
 * \param request  Pointer to a USBGenericRequest instance.
 */
void usbd_callbacks_request_received(const USBGenericRequest *request)
{
	hid_msdd_driver_request_handler(request);
}

/*----------------------------------------------------------------------------
 *         Callbacks
 *----------------------------------------------------------------------------*/

/**
 * Invoked when the MSD finish a READ/WRITE.
 * \param flowDirection 1 - device to host (READ10)
 *                      0 - host to device (WRITE10)
 * \param dataLength Length of data transferred in bytes.
 * \param fifoNullCount Times that FIFO is NULL to wait
 * \param fifoFullCount Times that FIFO is filled to wait
 */
static void msd_callbacks_data(uint8_t flow_direction,
								uint32_t  data_length,
								uint32_t  fifo_null_count,
								uint32_t  fifo_full_count)
{
	fifo_null_count = fifo_null_count; /*dummy */
	fifo_full_count = fifo_full_count; /*dummy */

	if (!flow_direction)
		msd_write_total += data_length;
}

/*---------------------------------------------------------------------------
 *         Internal functions
 *---------------------------------------------------------------------------*/

/**
 * Invoked when the status of the keyboard LEDs changes. Turns the num. lock
 * LED on or off.
 * \param numLockStatus Indicates the current status of the num. lock key.
 * \param capsLockStatus Indicates the current status of the caps lock key.
 * \param scrollLockStatus Indicates the current status of the scroll lock key
 */
void hidd_keyboard_callbacks_leds_changed(
	uint8_t num_lock_status,
	uint8_t caps_lock_status,
	uint8_t scroll_lock_status)
{
	caps_lock_status = caps_lock_status; /*dummy */
	scroll_lock_status = scroll_lock_status; /*dummy */

	/* Num. lock */
	if (num_lock_status)
		led_set(LED_NUMLOCK);
	else
		led_clear(LED_NUMLOCK);
}

/*---------------------------------------------------------------------------
 *         Internal functions
 *---------------------------------------------------------------------------*/

/**
 * Monitor keyboard buttons & Update key status in HID driver
 */
static void hidd_keyboard_process_keys(void)
{
	uint32_t i;
	uint8_t pressed_keys[NUM_KEYS];
	uint8_t pressed_keys_size = 0;
	uint8_t released_keys[NUM_KEYS];
	uint8_t released_keys_size = 0;

	/* Monitor buttons */
	if (console_is_rx_ready()) {
		uint8_t key = console_get_char();

		switch (key) {
		case '1':
		case '2':
			i = key - '1' + 1;
			key_status[i] = !key_status[i];
			if (key_status[i]) {
				/* Key press simulation */
				trace_info("Key %u pressed\n\r", (unsigned)i);
				pressed_keys[pressed_keys_size] = key_codes[i];
				pressed_keys_size++;
				hidd_keyboard_remote_wakeup();
			} else {
				/* Key release simulation */
				trace_info("Key %u released\n\r", (unsigned)i);
				released_keys[released_keys_size] = key_codes[i];
				released_keys_size++;
			}
			break;
		default:
			console_put_char(key);
		}
	}

#ifdef PIN_PUSHBUTTON_1
	/* Check if button state has changed */
	bool is_button_pressed = !pio_get(&pin_push_button);
	if (is_button_pressed != key_status[0]) {
		/* Update button state */
		key_status[0] = !key_status[0];
		if (!is_button_pressed) {
			/* Key has been pressed */
			trace_info("BP has been pressed\n\r");
			pressed_keys[pressed_keys_size] = key_codes[0];
			pressed_keys_size++;
			hidd_keyboard_driver_remote_wakeup();
		} else {
			/* Key has been released */
			trace_info("BP has been released\n\r");
			released_keys[released_keys_size] = key_codes[0];
			released_keys_size++;
		}
	}
#endif

	/* Update key status in the HID driver if necessary */
	if ((pressed_keys_size != 0) || (released_keys_size != 0)) {
		uint8_t status;

		do {
			status = hidd_keyboard_driver_change_keys(pressed_keys,
											pressed_keys_size,
											released_keys,
											released_keys_size);
		} while (status != USBD_STATUS_SUCCESS);
	}
}

/**
 * Initialize DDRAM to assign ramdisk block
 */
static void ram_disk_init(void)
{
	trace_info("RamDisk @ %x, size %d\n\r", (DDR_CS_ADDR + DDRAM_RESERVE_SIZE),
			RAMDISK_SIZE);

	media_ramdisk_init(&(medias[DRV_RAMDISK]),
			((uint32_t)&ramdisk_reserved) / BLOCK_SIZE,
			RAMDISK_SIZE / BLOCK_SIZE,
			BLOCK_SIZE);

	lun_init(&(luns[DRV_RAMDISK]),
				&(medias[DRV_RAMDISK]),
				msd_buffer, MSD_BUFFER_SIZE,
				0, 0, 0, 0,
				msd_callbacks_data);

}

/**
 * Initialize MSD Media & LUNs
 */
static void _memories_initialize(void)
{
	uint32_t i;

	/* Reset all LUNs */
	for (i = 0; i < MAX_LUNS; i++)
		lun_init(&luns[i], 0, 0, 0, 0, 0, 0, 0, 0);

	/* RAM disk initialize */
	ram_disk_init();
}

/*---------------------------------------------------------------------------
 *         Exported function
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 *          Main
 *---------------------------------------------------------------------------*/

/**
 * Initializes drivers and start the USB composite device.
 */
int main(void)
{
	uint8_t usb_connected = 0;

	/* Output example information */
	console_example_info("USB HIDMSD Device Example");

	/* Initialize all USB power (off) */
	usb_power_configure();

	/* ----- HID Function Initialize */
	printf("-- : DBG key 1 2 used as buttons\n\r");
	printf("-- : 1st press to push, 2nd press to release\n\r");

#ifdef PIN_PUSHBUTTON_1
	/* Initialize key statuses and configure push buttons */
	pio_configure(&pin_push_button, 1);
#endif

	memset(key_status, 0, sizeof(key_status));

	_memories_initialize();

	/* USB COMPOSITE driver initialization */
	hid_msdd_driver_initialize(&hid_msdd_driver_descriptors, luns, MAX_LUNS);

	/* connect if needed */
	usb_vbus_configure();

	/* Driver loop */
	while (1) {
		/* Device is not configured */
		if (usbd_get_state() < USBD_STATE_CONFIGURED) {
			if (usb_connected) {
				printf("-I- USB Disconnect/Suspend\n\r");
				usb_connected = 0;
			}
		} else {
			if (usb_connected == 0) {
				printf("-I- USB Connect\n\r");
				usb_connected = 1;
			}

			hidd_keyboard_process_keys();
			msd_function_state_machine();

			if (msd_refresh_delay-- > 0) {
				msd_refresh_delay = MSD_REFRESH_LOOP;

				if (msd_write_total < 5 * 1024) {
					/* Flush Disk Media */
				}
				msd_write_total = 0;
			}
		}
	}
}
/** \endcond */
