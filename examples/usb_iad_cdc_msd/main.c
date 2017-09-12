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
/** \cond usb_iad_cdc_msd
 * \page usb_iad_cdc_msd USB CDC(Serial)+MSD Example
 *
 * \section Purpose
 *
 * The USB CDCMSD Project will help you to get familiar with the
 * USB Device Port(UDP)interface and also some of the other interfaces in
 * SAMA5 microcontrollers. Also it can help you to be familiar with the USB
 * Framework that is used for rapid development of USB-compliant class
 * drivers such as USB Communication Device class (CDC), and how to combine
 * two USB functions to a single CDCMSD device (such as CDC + MSD).
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
 * The demo simulates a USB composite device that integrates USB CDC Serial
 * RS232 Converter function and USB Disk function.
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
 *     -- USB CDCMSD Device Project xxx --
 *     -- SAMxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 * -# When connecting USB cable to windows, the LED blinks, and the host
 *    reports a new USB device attachment.
 * -# For the windows driver installation and the test functions, please
 *      refer to "USB CDC serial converter" &
 *      "USB Device Mass Storage Project".
 * -# You can use the inf file
 *    libraries\\usb\\device\\composite\\drv\\CompositeCDCSerial.inf
 *    to install the CDC serial  port.
 *
 * \section References
 *
 * - usb_iad_cdc_msd/main.c
 * - pio: Pin configurations and peripheral configure.
 * - memories: Storage Media interface for MSD
 * - usb: USB Device Framework, USB CDC driver and UDP interface driver
 *    - \ref usbd_framework
 *        - \ref usbd_api
 *    - \ref usbd_composite "composite"
 *       - \ref usbd_composite_drv
 *    - \ref usbd_msd "massstorage"
 *       - \ref usbd_msd_drv
 *    - \ref usbd_cdc "cdc-serial"
 *       - \ref usbd_cdc_serial_drv
 * - projects:
 *    - \ref usb_massstorage
 *    - \ref usb_cdc_serial
 */

/**
 * \file
 *
 * \section Purpose
 *
 * This file contains all the specific code for the
 * usb_iad_cdc_msd project
 */

/*---------------------------------------------------------------------------
 *         Headers
 *---------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"
#include "trace.h"

#include "compiler.h"

#include "serial/console.h"

#include "gpio/pio.h"


#include "libstoragemedia/media.h"
#include "libstoragemedia/media_private.h"
#include "libstoragemedia/media_ramdisk.h"

#include "usb/device/msd/msd_driver.h"
#include "usb/device/msd/msd_lun.h"
#include "usb/device/composite/cdc_msd_driver.h"
#include "usb/device/cdc/cdcd_serial.h"
#include "../usb_common/main_usb_common.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*---------------------------------------------------------------------------
 *      Definitions
 *---------------------------------------------------------------------------*/

/** Size in bytes of the packet used for reading data from USB */
#define DATAPACKETSIZE 1024

/** Size in bytes of the buffer used for reading data from the USB & USART */
#define DATABUFFERSIZE (DATAPACKETSIZE+2)

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

/* Ramdisk size: at least 20K (Windows can not format the disk if lower than 20K) */
#if defined(CONFIG_BOARD_SAME70_XPLAINED) || defined(CONFIG_BOARD_SAMV71_XPLAINED)
  #define RAMDISK_SIZE        (32*1024)
#else
  #define RAMDISK_SIZE        (8*1024*1024)
#endif

/** Size of the reserved DDRAM (32M) */
#define DDRAM_RESERVE_SIZE  (32*1024*1024)

/** Size of the reserved Nand Flash (4M) */
#define NF_RESERVE_SIZE     (4*1024*1024)

/** Size of the managed Nand Flash (128M) */
#define NF_MANAGED_SIZE     (128*1024*1024)

/** Delay for MSD refresh (*4ms) */
#define MSD_REFRESH_DELAY    250

/** Delay for waiting DBGU input (*4ms) */
#define INPUT_DELAY          (2*250)

/*---------------------------------------------------------------------------
 *      External variables
 *---------------------------------------------------------------------------*/

/** Descriptor list for the device to bring up */
extern const USBDDriverDescriptors cdc_msdd_driver_descriptors;

/*---------------------------------------------------------------------------
 *      Internal variables
 *---------------------------------------------------------------------------*/
SECTION(".region_ddr")
ALIGNED(BLOCK_SIZE)
static uint8_t ramdisk_reserved[RAMDISK_SIZE];

/** Buffer for storing incoming USB data. */
SECTION(".region_ddr")
ALIGNED(BLOCK_SIZE)
static uint8_t usb_serial_buffer0[DATABUFFERSIZE];

/** Serial port openned */
static uint8_t is_serial_port_on = 0;

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
uint32_t msd_delay = MSD_REFRESH_DELAY;
/** Delay TO event */
uint8_t  msd_refresh = 0;


/**
 * Invoked when the configuration of the device changes. Parse used endpoints.
 * \param cfgnum New configuration number.
 */
void usbd_driver_callbacks_configuration_changed(uint8_t cfgnum)
{
	cdc_msd_driver_configuration_changed_handler(cfgnum);
}

/**
 * Invoked when a new SETUP request is received from the host. Forwards the
 * request to the Mass Storage device driver handler function.
 * \param request  Pointer to a USBGenericRequest instance.
 */
void usbd_callbacks_request_received(const USBGenericRequest *request)
{
	cdc_msd_driver_request_handler(request);
}

/*----------------------------------------------------------------------------
 *         Callbacks
 *----------------------------------------------------------------------------*/

/**
 * Invoked when the MSD finish a READ/WRITE.
 * \param flow_direction 1 - device to host (READ10)
 *                      0 - host to device (WRITE10)
 * \param data_length Length of data transferred in bytes.
 * \param fifo_null_count Times that FIFO is NULL to wait
 * \param fifo_full_count Times that FIFO is filled to wait
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


/**
 * Invoked when the CDC ControlLineState is changed
 * \param DTR   New DTR value.
 * \param RTS   New RTS value.
 */
void cdcd_serial_control_line_sate_changed(uint8_t DTR, uint8_t RTS);
void cdcd_serial_control_line_sate_changed(uint8_t DTR, uint8_t RTS)
{
	is_serial_port_on = DTR;
	RTS = RTS; /* dummy */
}

/**
 * Invoked when the CDC LineCoding is requested to changed
 * \param pLineCoding   Pointer to new LineCoding settings.
 * \return USBRC_SUCCESS if ready to receive the line coding.
 */
uint8_t cdcd_serial_line_coding_is_to_change(CDCLineCoding *line_coding)
{
	line_coding = line_coding; /*dummy */
	return USBD_STATUS_SUCCESS;
}

/*---------------------------------------------------------------------------
 *         Internal functions
 *---------------------------------------------------------------------------*/

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
	uint32_t i ;

	/* Reset all LUNs */
	for (i = 0; i < MAX_LUNS; i ++)
		lun_init(&luns[i], 0, 0, 0, 0, 0, 0, 0, 0);

	/* RAM disk initialize */
	ram_disk_init();
}

static void _usb_data_received(void *read, uint8_t status, uint32_t received,
							   uint32_t remaining)
{
	if (status == USBD_STATUS_SUCCESS)
		*(uint32_t *)read = 1;
	else
		trace_warning( "_usb_data_received: Transfer error\n\r");
}

/*---------------------------------------------------------------------------
 *         Exported function
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 *          Main
 *---------------------------------------------------------------------------*/

/**
 * Initializes drivers and start the USB CDCMSD device.
 */
int main(void)
{
	uint8_t usb_connected = 0, serial_on = 0;
	uint8_t serial_read = 1;

	/* Output example information */
	console_example_info("USB CDCMSD Device Example");

	/* If there is on board power, switch it off */
	usb_power_configure();

	/* ----- MSD Function Initialize */
	/* Configure memories */
	_memories_initialize();

	/* USB CDCMSD driver initialization */
	cdc_msd_driver_initialize(&cdc_msdd_driver_descriptors, luns, MAX_LUNS);

	/* connect if needed */
	usb_vbus_configure();

	/* Driver loop */
	while (1) {
		/* Device is not configured */
		if (usbd_get_state() < USBD_STATE_CONFIGURED) {
			if (usb_connected) {
				printf("-I- USB Disconnect/Suspend\n\r");
				usb_connected = 0;

				/* Serial port closed */
				is_serial_port_on = 0;
			}
		} else {
			if (usb_connected == 0) {
				printf("-I- USB Connect\n\r");
				usb_connected = 1;
			}

			if (!serial_on && is_serial_port_on) {
				printf("-I- SerialPort ON\n\r");
				/* Start receiving data on the USART */
				/* Start receiving data on the USB */
				if (serial_read == 1) {
					serial_read = 0;
					cdcd_serial_read(usb_serial_buffer0, DATAPACKETSIZE, _usb_data_received, &serial_read);
				}
				serial_on = 1;
			} else if (serial_on && !is_serial_port_on) {
				printf("-I- SerialPort OFF\n\r");
				serial_on = 0;
			}
			msd_function_state_machine();

			if (msd_refresh) {
				msd_refresh = 0;

				if (msd_write_total < 50 * 1000) {
					/* Flush Disk Media */
				}

				msd_write_total = 0;
			}
		}
	}
}
/** \endcond */
