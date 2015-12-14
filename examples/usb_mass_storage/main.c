/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2015, Atmel Corporation                                        */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Atmel's name may not be used to endorse or promote products derived from     */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR   */
/* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE   */
/* DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,      */
/* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,  */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    */
/* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING         */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/* ---------------------------------------------------------------------------- */

/** \cond usb_massstorage
 * \page usb_massstorage USB Device Mass Storage Example
 *
 * \section Purpose
 *
 * The USB Mass storage Example will help you to get familiar with the
 * USB Device Port(UDP) on SAMV7/E7 Microcontrollers. Also
 * it can help you to be familiar with the USB Framework that is used for
 * rapid development of USB-compliant class drivers such as USB Mass
 * Storage class (MSD).
 *
 * \section Requirements
 *
 * This package can be used with SAMV71 Xplained Ultra board or SAME70 Xplained board
 * This package can be used with all Atmel Xplained board that have USB interface
 *
 * \section Description
 *
 * The demo simulates a SD/MMC USB disk.
 *
 * When the board running this program connected to a host (PC for example), with
 * USB cable, the board appears as a USB Disk for the host. Then the host can
 * format/read/write on the disk.
 *
 * \section Usage
 *
 *  -# Build the program and download it inside the board.
 *     Please refer to the Getting Started with SAM V71/E70 Microcontrollers.pdf
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 baud rate
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *     \code
 *     -- USB Device Mass Storage Example xxx --
 *     -- SAMxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 * -# When connecting USB cable to windows, the host
 *    reports a new USB %device attachment and Disk installation.
 *  . Then new "USB Mass Storage Device" and
 *    "ATMEL Mass Storage MSD USB Device" and "Generic volume" appear in
 *    hardware %device list.
 * -# You can find the new disk on host, and to create/write file to it.
 *
 * \section References
 * - usb_massstorage/main.c
 * - pio.h
 * - pio_it.h
 * - memories: Storage Media interface for MSD
 * - usb: USB Framework, USB MSD driver and UDP interface driver
 *    - \ref usbd_framework
 *       - \ref usbd_api
 *    - \ref usbd_msd
 *       - \ref usbd_msd_drv
 */

/**
 * \file
 *
 * This file contains all the specific code for the
 * usb_massstorage.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "trace.h"

#include "cortex-a/mmu.h"
#include "cortex-a/cp15.h"
#include "peripherals/pio.h"
#include "peripherals/wdt.h"

#include "libstoragemedia/media.h"
#include "libstoragemedia/media_private.h"
#include "libstoragemedia/media_ramdisk.h"

#include "usb/device/msd/msd_driver.h"
#include "usb/device/msd/msd_lun.h"

#include "../usb_common/main_usb_common.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** Maximum number of LUNs which can be defined. */
#define MAX_LUNS 1

/** Size of one block in bytes. */
#define BLOCK_SIZE 512

/* Media index for different disks */
#define DRV_RAMDISK 0 /**< RAM disk */

/** RamDisk size (WinXP can not format the disk if lower than 20K) */
#define RAMDISK_SIZE (8 * 1024 * 1024)

SECTION(".region_ddr")
ALIGNED(BLOCK_SIZE)
static uint8_t ramdisk_reserved[RAMDISK_SIZE];

/** Size of the MSD IO buffer in bytes (more the better). */
#define MSD_BUFFER_SIZE (128 * BLOCK_SIZE)

/*----------------------------------------------------------------------------
 *        Global variables
 *----------------------------------------------------------------------------*/

/** MSD Driver Descriptors List */
extern const USBDDriverDescriptors msd_driver_descriptors;

/** Available media. */
struct _media medias[MAX_LUNS];

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** Device LUNs. */
static MSDLun luns[MAX_LUNS];

/** LUN read/write buffer. */
SECTION(".region_ddr")
ALIGNED(32)
static uint8_t ram_buffer[MSD_BUFFER_SIZE];

/** Total data write to disk */
uint32_t msd_write_total = 0;

/** Delay TO event */
uint8_t  msd_refresh = 0;

/*-----------------------------------------------------------------------------
 *         Callback re-implementation
 *-----------------------------------------------------------------------------*/

/**
 * Invoked when a new SETUP request is received from the host. Forwards the
 * request to the Mass Storage device driver handler function.
 * \param request  Pointer to a USBGenericRequest instance.
 */
void usbd_callbacks_request_received(const USBGenericRequest *request)
{
	msd_driver_request_handler(request);
}

/**
 * Invoked when the configuration of the device changes. Resets the mass
 * storage driver.
 * \param cfgnum New configuration number.
 */
void usbd_driver_callbacks_configuration_changed(unsigned char cfgnum)
{
	msd_driver_configuration_change_handler(cfgnum);
}

/*----------------------------------------------------------------------------
 *        Callbacks
 *----------------------------------------------------------------------------*/

/**
 * Invoked when the MSD finish a READ/WRITE.
 * \param flow_direction 1 - device to host (READ10)
 *                       0 - host to device (WRITE10)
 * \param data_length Length of data transferred in bytes.
 * \param fifo_null_count Times that FIFO is NULL to wait
 * \param fifo_full_count Times that FIFO is filled to wait
 */
static void msd_callbacks_data(uint8_t flow_direction, uint32_t data_length,
		uint32_t fifo_null_count, uint32_t fifo_full_count)
{
	if (!flow_direction) {
		msd_write_total += data_length;
	}
}

/*----------------------------------------------------------------------------
 *         Internal functions
 *----------------------------------------------------------------------------*/

/**
 * Initialize RAM to assign RamDisk block
 */
static void ramdisk_init(void)
{
	trace_info("RamDisk @ %x, size %d\n\r", (unsigned)&ramdisk_reserved, RAMDISK_SIZE);

	media_ramdisk_init(&(medias[DRV_RAMDISK]),
			((uint32_t)&ramdisk_reserved) / BLOCK_SIZE,
			RAMDISK_SIZE / BLOCK_SIZE,
			BLOCK_SIZE);

	lun_init(&(luns[DRV_RAMDISK]),
			&(medias[DRV_RAMDISK]),
			ram_buffer, MSD_BUFFER_SIZE,
			0, 0, 0, 0,
			msd_callbacks_data);
}

/**
 * Initialize MSD Media & LUNs
 */
static void _MemoriesInitialize(void)
{
	int i;

	/* Reset all LUNs */
	for (i = 0; i < MAX_LUNS; i++)
		lun_init(&luns[i], 0, 0, 0, 0, 0, 0, 0, 0);

	/* Initialize RAM disk */
	ramdisk_init();
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief usb_massstorage Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	/* Disable watchdog */
	wdt_disable();

#ifndef VARIANT_DDRAM
	/* Initialize DDR */
	board_cfg_ddram();
#endif

	printf("-- USB Device Mass Storage Example " SOFTPACK_VERSION " --\n\r");
	printf("-- " BOARD_NAME " --\n\r");
	printf( "-- Compiled: " __DATE__ " " __TIME__ " --\n\r");

	/* If they are present, configure Vbus & Wake-up pins */
	pio_reset_all_it();

	/* Initialize all USB power (off) */
	usb_power_configure();

	/* Initialize Media */
	_MemoriesInitialize();

	/* BOT driver initialization */
	msd_driver_initialize(&msd_driver_descriptors, luns, MAX_LUNS);

	/* connect if needed */
	usb_vbus_configure();

	while (1) {
		/* Mass storage state machine */
		if (usbd_get_state() >= USBD_STATE_CONFIGURED) {
			msd_driver_state_machine();
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
