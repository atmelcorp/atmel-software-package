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
 * \page sdcard Secure Digital Memory Card.
 * An example using the SD/MMC peripherals of SAMA5Dxx MPUs.
 *
 * \section Purpose
 *
 * The Secure Digital Memory Card example will help new users
 * get familiar with the SD/MMC peripheral used in Atmel's
 * SAMA5Dxx MPUs.
 *
 * \section Requirements
 *
 * This package is compatible with the evaluation boards listed below:
 * - SAMA5D2-VB
 * - SAMA5D2-XULT
 * - SAMA5D4-EK
 * - SAMA5D4-XULT
 *
 * \section Description
 *
 * The demonstration program... TODO
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board. Please
 *    refer to the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *    SAM-BA User Guide</a>, the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *    GNU-Based Software Development</a>
 *    application note or to the
 *    <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *    IAR EWARM User Guide</a>,
 *    depending on your chosen solution.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# In the terminal window, the
 *    following text should appear (values depend on the board and chip used):
 *    \code
 *     -- Secure Digital Memory Card (SDMMC) Example xxx --
 *     -- xxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *
 *     SD card menu:
 *     TODO
 *     \endcode
 * -# Input command according to the menu.
 *
 * \section References
 * - TODO
 */

/** \file
 *
 *  This file contains all the specific code for the SD Card
 *  example.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdint.h>

#include "board.h"
#include "chip.h"
#include "trace.h"
#include "swab.h"

#ifdef CONFIG_HAVE_SHA
#include "crypto/shad.h"
#include "intmath.h"
#endif

#include "mm/cache.h"
#include "serial/console.h"
#include "peripherals/pmc.h"

#ifdef CONFIG_HAVE_SDMMC
#  include "sdmmc/sdmmc.h"
#elif defined(CONFIG_HAVE_HSMCI)
#  include "sdmmc/hsmci.h"
#  include "sdmmc/hsmcid.h"
#else
#  error No peripheral for SD/MMC devices
#endif

#include "libsdmmc/libsdmmc.h"
#include "fatfs/src/ff.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#define BLOCK_CNT_MAX               256u
#define DMADL_CNT_MAX               512u
#define BLOCK_CNT                   3u

/* Allocate 2 Timers/Counters, that are not used already by the libraries and
 * drivers this example depends on. */
#define TIMER0_MODULE                 ID_TC0
#define TIMER0_CHANNEL                0
#define TIMER1_MODULE                 ID_TC0
#define TIMER1_CHANNEL                1u

#ifdef CONFIG_BOARD_SAMA5D2_XPLAINED
#  define SLOT0_ID                    ID_SDMMC0
#  define SLOT0_TAG                   "(e.MMC)"
#  define SLOT1_ID                    ID_SDMMC1
#  define SLOT1_TAG                   "(SD/MMC)"
#elif defined(CONFIG_BOARD_SAMA5D27_SOM1_EK)
#  define SLOT0_ID                    ID_SDMMC0
#  define SLOT0_TAG                   "(SD/MMC)"
#  define SLOT1_ID                    ID_SDMMC1
#  define SLOT1_TAG                   "(SD/MMC)"
#elif defined(CONFIG_BOARD_SAMA5D3_EK)
#  define SLOT0_ID                    ID_HSMCI0
#  define SLOT0_TAG                   "(SD/MMC)"
#  define SLOT1_ID                    ID_HSMCI1
#  define SLOT1_TAG                   "(microSD)"
#elif defined(CONFIG_BOARD_SAMA5D3_XPLAINED)
#  define SLOT0_ID                    ID_HSMCI0
#  define SLOT0_TAG                   "(SD/MMC)"
#  define SLOT1_ID                    ID_HSMCI1
#  define SLOT1_TAG                   "(microSD)"
#elif defined(CONFIG_BOARD_SAMA5D4_EK)
#  define SLOT0_ID                    ID_HSMCI0
#  define SLOT0_TAG                   "(SD/MMC)"
#  define SLOT1_ID                    ID_HSMCI1
#  define SLOT1_TAG                   "(microSD)"
#elif defined(CONFIG_BOARD_SAMA5D4_XPLAINED)
#  define SLOT0_ID                    ID_HSMCI0
#  define SLOT0_TAG                   "(microSD)"
#  define SLOT1_ID                    ID_HSMCI1
#  define SLOT1_TAG                   "(SD/MMC)"
#elif defined(CONFIG_BOARD_SAM9G15_EK) ||\
      defined(CONFIG_BOARD_SAM9G25_EK) ||\
      defined(CONFIG_BOARD_SAM9G35_EK) ||\
      defined(CONFIG_BOARD_SAM9X25_EK) ||\
      defined(CONFIG_BOARD_SAM9X35_EK)
#  define SLOT0_ID                    ID_HSMCI0
#  define SLOT0_TAG                   "(microSD)"
#  define SLOT1_ID                    ID_HSMCI1
#  define SLOT1_TAG                   "(SD/MMC)"
#elif defined(CONFIG_BOARD_SAME70_XPLAINED)
#  define SLOT0_ID                    ID_HSMCI0
#  define SLOT0_TAG                   "(SD/MMC)"
#elif defined(CONFIG_BOARD_SAMV71_XPLAINED)
#  define SLOT0_ID                    ID_HSMCI0
#  define SLOT0_TAG                   "(SD/MMC)"
#endif

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

const char test_file_path[] = "test_data.bin";

#ifdef CONFIG_HAVE_SDMMC

/* Driver instance data (a.k.a. MCI driver instance) */
static struct sdmmc_set drv0 = { 0 };
#ifdef SLOT1_ID
static struct sdmmc_set drv1 = { 0 };
#endif

/* Buffer dedicated to the driver, refer to the driver API. Aligning it on
 * cache lines is optional. */
CACHE_ALIGNED_DDR static uint32_t dma_table[DMADL_CNT_MAX * SDMMC_DMADL_SIZE];
static bool use_dma = false;

#elif defined(CONFIG_HAVE_HSMCI)

/* MCI driver instance data */
static const struct _hsmci_cfg drv0_config = {
	.periph_id = ID_HSMCI0,
	.slot = BOARD_HSMCI0_SLOT,
#ifdef BOARD_HSMCI0_WP_PIN
	.wp_pin = BOARD_HSMCI0_WP_PIN,
#else
	.wp_pin = 0,
#endif
	.use_polling = false,
	.ops = {
		.get_card_detect_status = board_get_hsmci_card_detect_status,
		.set_card_power = board_set_hsmci_card_power,
	},
};
static struct _hsmci_set drv0 = { 0 };

#ifdef SLOT1_ID

static const struct _hsmci_cfg drv1_config = {
	.periph_id = ID_HSMCI1,
	.slot = BOARD_HSMCI1_SLOT,
#ifdef BOARD_HSMCI0_WP_PIN
	.wp_pin = BOARD_HSMCI0_WP_PIN,
#else
	.wp_pin = 0,
#endif
	.use_polling = false,
	.ops = {
		.get_card_detect_status = board_get_hsmci_card_detect_status,
		.set_card_power = board_set_hsmci_card_power,
	},
};
static struct _hsmci_set drv1 = { 0 };

#endif /* SLOT1_ID */

#endif /* CONFIG_HAVE_HSMCI */

/* Library instance data (a.k.a. SDCard driver instance) */
CACHE_ALIGNED_DDR static sSdCard lib0;
#ifdef SLOT1_ID
CACHE_ALIGNED_DDR static sSdCard lib1;
#endif

/* Read/write data buffer.
 * It may receive data transferred from the device by the DMA. As the L1 data
 * cache won't notice when RAM is updated directly, the driver will invalidate
 * any matching cache lines.
 * May this buffer fail to be aligned on cache lines, cached changes to adjacent
 * variables would be lost at the time the dirty and shared cache lines were
 * invalidated.
 * Alternatively, we might consider allocating this buffer from a
 * non-cacheable memory region. */
CACHE_ALIGNED_DDR static uint8_t data_buf[BLOCK_CNT_MAX * 512ul];

NOT_CACHED static FATFS fs_header;
NOT_CACHED static FIL f_header;

#ifdef CONFIG_HAVE_SHA
static struct _shad_desc shad;
static uint32_t hash[5] = { 0 };
static struct _buffer sha_buf;
#endif

static uint8_t slot;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Trace buffer contents in hex.
 */
static void print_buffer(uint32_t len, const uint8_t *data)
{
	const char format[] = { ' ', '%', '0', '2', 'x', '\0' };
	const uint8_t * const data_nxt = data + len;
	uint32_t ix;

	for (ix = 0; data < data_nxt; data++, ix++) {
		if (ix % 32 == 0)
			printf("\n\r%03lx:    ", ix);
		printf(format + (ix % 4 ? 1 : 0), *data);
	}
	printf("\n\r");
}

/**
 * \brief Display main menu.
 */
static void display_menu(void)
{
	printf("\n\rSD Card menu:\n\r");
	printf("   h: Display this menu\n\r");
#ifdef SLOT1_ID
	printf("   t: Toggle between Slot%c0%c" SLOT0_TAG " and Slot%c1%c"
	    SLOT1_TAG "\n\r", slot ? ' ' : '[', slot ? ' ' : ']', slot ? '[' : ' ',
	    slot ? ']' : ' ');
#endif
#ifdef CONFIG_HAVE_SDMMC
	printf("   d: Select either %cCPU programmed I/O%c or %cDMA operation%c"
	    "\n\r", use_dma ? ' ' : '[', use_dma ? ' ' : ']',
	    use_dma ? '[' : ' ', use_dma ? ']' : ' ');
#endif
	printf("   i: Display device info\n\r");
	printf("   l: Mount FAT file system and list files\n\r");
	printf("   r: Read the file named '%s'\n\r", test_file_path);
	printf("   w: Perform a basic RAW read/write test.\n\r");
	printf("\n\r");
}

static void initialize(void)
{
#if defined(CONFIG_HAVE_SDMMC)

	/* As long as we do not transfer from/to the two peripherals at the same
	 * time, we can have the two instances sharing a single DMA buffer. */

	sdmmc_initialize(&drv0, SLOT0_ID,
	    TIMER0_MODULE, TIMER0_CHANNEL,
	    use_dma ? dma_table : NULL, use_dma ? ARRAY_SIZE(dma_table) : 0, false);
	SDD_InitializeSdmmcMode(&lib0, &drv0, 0);

#ifdef SLOT1_ID
	sdmmc_initialize(&drv1, SLOT1_ID,
	    TIMER1_MODULE, TIMER1_CHANNEL,
	    use_dma ? dma_table : NULL, use_dma ? ARRAY_SIZE(dma_table) : 0, false);
	SDD_InitializeSdmmcMode(&lib1, &drv1, 0);
#endif /* SLOT1_ID */

#elif defined(CONFIG_HAVE_HSMCI)

	hsmci_initialize(&drv0, &drv0_config);
	SDD_InitializeSdmmcMode(&lib0, &drv0, 0);

#ifdef SLOT1_ID
	hsmci_initialize(&drv1, &drv1_config);
	SDD_InitializeSdmmcMode(&lib1, &drv1, 0);
#endif /* SLOT1_ID */

#endif

#ifdef CONFIG_HAVE_SHA
	shad.cfg.algo = ALGO_SHA_1;
	shad.cfg.transfer_mode = SHAD_TRANS_DMA;
	shad_init(&shad);
#endif
}

static bool open_device(sSdCard *pSd)
{
	uint8_t rc;

	rc = SD_Init(pSd);
	if (rc != SDMMC_OK) {
		trace_error("SD/MMC device initialization failed: %d\n\r", rc);
		return false;
	}
	trace_info("SD/MMC device initialization successful\n\r");
	return true;
}

static bool close_device(sSdCard *pSd)
{
	SD_DeInit(pSd);
	return true;
}

static bool show_device_info(sSdCard *pSd)
{
#ifndef SDMMC_TRIM_INFO
	const uint8_t card_type = SD_GetCardType(pSd);
#endif

	SD_DumpStatus(pSd);
#ifndef SDMMC_TRIM_INFO
	if (card_type & CARD_TYPE_bmSDMMC)
		SD_DumpCID(pSd);
	if (card_type & CARD_TYPE_bmSD) {
		SD_DumpSCR(pSd->SCR);
		SD_DumpSSR(pSd->SSR);
	}
	if (card_type & CARD_TYPE_bmSDMMC)
		SD_DumpCSD(pSd);
#ifndef SDMMC_TRIM_MMC
	if (card_type & CARD_TYPE_bmMMC)
		SD_DumpExtCSD(pSd->EXT);
#endif
#ifndef SDMMC_TRIM_SDIO
	if (card_type & CARD_TYPE_bmSDIO)
		SDIO_DumpCardInformation(pSd);
#endif
	printf("\n\r");
#endif
	return true;
}

static bool mount_volume(uint8_t slot_ix, sSdCard *pSd, FATFS *fs)
{
	const TCHAR drive_path[] = { '0' + slot_ix, ':', '\0' };
	DIR dir = { .sect = 0 };
	FILINFO fno = { 0 };
	FRESULT res;
	bool is_dir, rc = true;

	memset(fs, 0, sizeof(FATFS));
	res = f_mount(fs, drive_path, 1);
	if (res != FR_OK) {
		printf("Failed to mount FAT file system, error %d\n\r", res);
		return false;
	}
	res = f_opendir(&dir, drive_path);
	if (res != FR_OK) {
		printf("Failed to change to root directory, error %d\n\r", res);
		return false;
	}
	printf("Listing the files present in the root directory:\n\r");
	for ( ; ; ) {
		res = f_readdir(&dir, &fno);
		if (res != FR_OK) {
			trace_error("Error (%d) while listing files\n\r", res);
			rc = false;
			break;
		}
		if (fno.fname[0] == '\0')
			break;
		is_dir = fno.fattrib & AM_DIR ? true : false;
		printf("    %s%s%c\n\r", is_dir ? "[" : "", fno.fname,
		    is_dir ? ']' : ' ');
	}

	res = f_closedir(&dir);
	if (res != FR_OK) {
		trace_error("Failed to close directory, error %d\n\r", res);
		rc = false;
	}
	return rc;
}

static bool read_file(uint8_t slot_ix, sSdCard *pSd, FATFS *fs)
{
	const TCHAR drive_path[] = { '0' + slot_ix, ':', '\0' };
	const UINT buf_size = BLOCK_CNT_MAX * 512ul;
	TCHAR file_path[sizeof(drive_path) + sizeof(test_file_path)];
	uint32_t file_size;
	UINT len;
	FRESULT res;
	bool rc = true;

	memset(fs, 0, sizeof(FATFS));
	res = f_mount(fs, drive_path, 1);
	if (res != FR_OK) {
		printf("Failed to mount FAT file system, error %d\n\r", res);
		return false;
	}
	strcpy(file_path, drive_path);
	strcat(file_path, test_file_path);
	res = f_open(&f_header, file_path, FA_OPEN_EXISTING | FA_READ);
	if (res != FR_OK) {
		printf("Failed to open \"%s\", error %d\n\r", file_path, res);
		return false;
	}
#ifdef CONFIG_HAVE_SHA
	shad_start(&shad);
#endif
	for (file_size = 0, len = buf_size; res == FR_OK && len == buf_size;
	    file_size += len) {
		res = f_read(&f_header, data_buf, buf_size, &len);
		if (res == FR_OK) {
#ifdef CONFIG_HAVE_SHA
			sha_buf.attr = 0;
			sha_buf.data = (uint8_t*)data_buf;
			sha_buf.size = len;
			shad_update(&shad, &sha_buf, NULL);
			shad_wait_completion(&shad);
#endif
		}
		else
			printf("Error %d while attempting to read file\n\r",
				res);
	}
#ifdef CONFIG_HAVE_SHA
	if (res == FR_OK) {
		sha_buf.attr = 0;
		sha_buf.data = (uint8_t*)hash;
		sha_buf.size = shad_get_output_size(shad.cfg.algo);
		shad_finish(&shad, &sha_buf, NULL);
		shad_wait_completion(&shad);
		printf("Read %lu bytes. Their SHA-1 was %08lx%08lx%08lx%08lx"
		    "%08lx.\n\r", file_size,
				swab32(hash[0]),
				swab32(hash[1]),
				swab32(hash[2]),
				swab32(hash[3]),
				swab32(hash[4]));
	}
#endif
	res = f_close(&f_header);
	if (res != FR_OK) {
		trace_error("Failed to close file, error %d\n\r", res);
		return false;
	}
	return rc;
}

static bool unmount_volume(uint8_t slot_ix, sSdCard *pSd)
{
	const TCHAR drive_path[] = { '0' + slot_ix, ':', '\0' };
	FRESULT res;
	bool rc = true;

	res = f_mount(NULL, drive_path, 0);
	if (res != FR_OK)
		rc = false;
	SD_DeInit(pSd);
	return rc;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/* Refer to sdmmc_ff.c */
bool SD_GetInstance(uint8_t index, sSdCard **holder);

bool SD_GetInstance(uint8_t index, sSdCard **holder)
{
	assert(holder);

	switch (index) {
	case 0:
		*holder = &lib0;
		break;
#ifdef SLOT1_ID
	case 1:
		*holder = &lib1;
		break;
#endif /* SLOT1_ID */
	default:
		return false;
	}
	return true;
}

/**
 *  \brief SD Card Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
#ifdef CONFIG_HAVE_SDMMC
	struct _pmc_audio_cfg audio_pll_cfg = {
		.fracr = 0,
		.div = 3,
		.qdaudio = 24,
	};
#endif
	sSdCard *lib = NULL;
	uint8_t user_key, rc;

	/* Output example information */
	console_example_info("SD/MMC Example");

	pmc_configure_peripheral(TIMER0_MODULE, NULL, true);
#if TIMER1_MODULE != TIMER0_MODULE
	pmc_configure_peripheral(TIMER1_MODULE, NULL, true);
#endif

	/* The HSMCI peripherals are clocked by the Master Clock (at least on
	 * SAMA5D4x).
	 * The SDMMC peripherals are clocked by their Peripheral Clock, the
	 * Master Clock, and a Generated Clock (at least on SAMA5D2x). */
	pmc_configure_peripheral(SLOT0_ID, NULL, true);
#ifdef SLOT1_ID
	pmc_configure_peripheral(SLOT1_ID, NULL, true);
#endif

#ifdef CONFIG_HAVE_SDMMC
#ifdef SDMMC_USE_FASTEST_CLK
	/* Running on a board which has its SDMMC0 slot equipped with an e.MMC
	 * device supporting the HS200 bus speed mode, or accepts UHS-I SD
	 * devices. Target the maximum device clock frequency supported by
	 * SAMA5D2x MPUs, that is 120 MHz.
	 * Use the UTMI PLL, since it runs at 480 MHz. */
	pmc_enable_upll_clock();
	pmc_enable_upll_bias();

	struct _pmc_periph_cfg cfg = {
		.gck = {
			.css = PMC_PCR_GCKCSS_UPLL_CLK,
			.div = 1,
		},
	};
	pmc_configure_peripheral(SLOT0_ID, &cfg, true);

#ifdef SLOT1_ID
	/* On the SDMMC1 slot, target SD High Speed mode @ 50 MHz.
	 * Use the Audio PLL and set AUDIOCORECLK frequency to
	 * 12 * (57 + 1 + 1398101/2^22) =~ 700 MHz.
	 * Set AUDIOPLLCK frequency to 700 / (6 + 1) = 100 MHz. */
	audio_pll_cfg.nd = 57;
	audio_pll_cfg.fracr = 1398101;
	audio_pll_cfg.qdpmc = 6;
	pmc_configure_audio(&audio_pll_cfg);
	pmc_enable_audio(true, false);

	cfg.gck.css = PMC_PCR_GCKCSS_AUDIO_CLK;
	pmc_configure_peripheral(SLOT1_ID, &cfg,true);
#endif /* SLOT1_ID */
#else /* !SDMMC_USE_FASTEST_CLK */
	/* The regular SAMA5D2-XULT board wires on the SDMMC0 slot an e.MMC
	 * device whose fastest timing mode is High Speed DDR mode @ 52 MHz.
	 * Target a device clock frequency of 52 MHz. Use the Audio PLL and set
	 * AUDIOCORECLK frequency to 12 * (51 + 1 + 0/2^22) = 624 MHz.
	 * And set AUDIOPLLCK frequency to 624 / (5 + 1) = 104 MHz. */
	audio_pll_cfg.nd = 51;
	audio_pll_cfg.qdpmc = 5;
	pmc_configure_audio(&audio_pll_cfg);
	pmc_enable_audio(true, false);

	struct _pmc_periph_cfg cfg = {
		.gck = {
			.css = PMC_PCR_GCKCSS_AUDIO_CLK,
			.div = 1,
		},
	};
	pmc_configure_peripheral(SLOT0_ID, &cfg, true);

#ifdef SLOT1_ID
	/* The regular SAMA5D2-XULT board wires on the SDMMC1 slot a MMC/SD
	 * connector. SD cards are the most likely devices. Since the SDMMC1
	 * peripheral supports 3.3V signaling level only, target SD High Speed
	 * mode @ 50 MHz.
	 * The Audio PLL being optimized for SDMMC0, fall back on PLLA, since,
	 * as of writing, PLLACK/2 is configured to run at 498 MHz. */
	cfg.gck.css = PMC_PCR_GCKCSS_PLLA_CLK;
	pmc_configure_peripheral(SLOT1_ID, &cfg, true);
#endif /* SLOT1_ID */
#endif /* !SDMMC_USE_FASTEST_CLK */
#endif /* CONFIG_HAVE_SDMMC */

	rc = board_cfg_sdmmc(SLOT0_ID) ? 1 : 0;
#ifdef SLOT1_ID
	rc &= board_cfg_sdmmc(SLOT1_ID) ? 1 : 0;
#endif
	if (!rc)
		trace_error("Failed to cfg cells\n\r");

#ifdef CONFIG_HAVE_SDMMC
	rc = IS_CACHE_ALIGNED(&data_buf);
	rc &= IS_CACHE_ALIGNED(sizeof(data_buf));
	rc &= IS_CACHE_ALIGNED(&lib0.EXT);
	rc &= IS_CACHE_ALIGNED(sizeof(lib0.EXT));
#ifdef SLOT1_ID
	rc &= IS_CACHE_ALIGNED(&lib1.EXT);
	rc &= IS_CACHE_ALIGNED(sizeof(lib1.EXT));
#endif
	if (!rc) {
		trace_error("WARNING: buffers are not aligned on data cache "
		    "lines. Please fix this before enabling DMA.\n\r");
		use_dma = false;
	} else {
		use_dma = true;
	}
#endif
	initialize();

	/* Display menu */
	slot = 0;
	lib = &lib0;
	display_menu();

	while (true) {
		user_key = tolower(console_get_char());
		switch (user_key) {
		case 'h':
			display_menu();
			break;
#ifdef SLOT1_ID
		case 't':
			slot = slot ? 0 : 1;
			lib = slot ? &lib1 : &lib0;
			display_menu();
			break;
#endif /* SLOT1_ID */
#ifdef CONFIG_HAVE_SDMMC
		case 'd':
			use_dma = !use_dma;
			initialize();
			display_menu();
			break;
#endif
		case 'i':
			if (SD_GetStatus(lib) == SDMMC_NOT_SUPPORTED) {
				printf("Device not detected.\n\r");
				break;
			}
			if (open_device(lib))
				show_device_info(lib);
			close_device(lib);
			break;
		case 'l':
			if (SD_GetStatus(lib) == SDMMC_NOT_SUPPORTED) {
				printf("Device not detected.\n\r");
				break;
			}
			mount_volume(slot, lib, &fs_header);
			unmount_volume(slot, lib);
			break;
		case 'r':
			if (SD_GetStatus(lib) == SDMMC_NOT_SUPPORTED) {
				printf("Device not detected.\n\r");
				break;
			}
			read_file(slot, lib, &fs_header);
			unmount_volume(slot, lib);
			break;
		case 'w':
			if (SD_GetStatus(lib) == SDMMC_NOT_SUPPORTED) {
				printf("Device not detected.\n\r");
				break;
			}
			if (SD_GetWpStatus(lib) == SDMMC_LOCKED) {
				printf("Device is write protected.\n\r");
				break;
			}
			if (open_device(lib)) {
				uint32_t block = 254;

				printf("Reading blocks #%lu-%lu\n\r", block, block + BLOCK_CNT - 1);
				rc = SD_Read(lib, block, data_buf, BLOCK_CNT, NULL, NULL);
				if (rc != SDMMC_OK)
					trace_error("%s\n\r", SD_StringifyRetCode(rc));
				if (rc == SDMMC_OK) {
					printf("Printing contents of blocks #%lu-%lu before we alter them\n\r", block, block + BLOCK_CNT - 1);
					print_buffer(BLOCK_CNT * 512ul, data_buf);

					printf("Rewriting blocks #%lu-%lu\n\r", block, block + BLOCK_CNT - 1);
					memset(data_buf, 0x55, BLOCK_CNT * 512ul);
					rc = SD_Write(lib, block, data_buf, BLOCK_CNT, NULL, NULL);
					if (rc != SDMMC_OK)
						trace_error("%s\n\r", SD_StringifyRetCode(rc));
				}
				if (rc == SDMMC_OK) {
					memset(data_buf, 0, BLOCK_CNT * 512ul);
					printf("Reading blocks #%lu-%lu again\n\r", block, block + BLOCK_CNT - 1);
					rc = SD_Read(lib, block, data_buf, BLOCK_CNT, NULL, NULL);
					if (rc != SDMMC_OK)
						trace_error("%s\n\r", SD_StringifyRetCode(rc));
				}
				if (rc == SDMMC_OK) {
					printf("Printing contents of blocks #%lu-%lu\n\r", block, block + BLOCK_CNT - 1);
					print_buffer(BLOCK_CNT * 512ul, data_buf);
				}
			}
			close_device(lib);
			break;
		}
	}

	/* This code is never reached */
}
