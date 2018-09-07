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

/** \file */

/** \addtogroup sdmmc_api
 *  @{
 */

/* By default, do not compile debug-level traces of this module. Expect them to
 * be enabled explicitly, e.g. in the Makefile of the application. */
#ifdef SDMMC_LIB_TRACE_LEVEL
# undef TRACE_LEVEL
# define TRACE_LEVEL SDMMC_LIB_TRACE_LEVEL
#elif TRACE_LEVEL > 4
# undef TRACE_LEVEL
# define TRACE_LEVEL 4
#endif

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "trace.h"
#include "chip.h"
#include "compiler.h"
#include "intmath.h"
#include "timer.h"
#include "libsdmmc.h"

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

/*----------------------------------------------------------------------------
 *         Local definitions
 *----------------------------------------------------------------------------*/

struct stringEntry_s
{
	const uint8_t key;
	const char *name;
};

/*----------------------------------------------------------------------------
 *         Global variables
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *         Local constants
 *----------------------------------------------------------------------------*/

/** \addtogroup sdmmc_status_bm SD/MMC Status register constants
 *      @{*/
#define STATUS_APP_CMD          (1UL << 5)
#define STATUS_SWITCH_ERROR     (1UL << 7)
#define STATUS_READY_FOR_DATA   (1UL << 8)
#define STATUS_IDLE             (0UL << 9)
#define STATUS_READY            (1UL << 9)
#define STATUS_IDENT            (2UL << 9)
#define STATUS_STBY             (3UL << 9)
#define STATUS_TRAN             (4UL << 9)
#define STATUS_DATA             (5UL << 9)
#define STATUS_RCV              (6UL << 9)
#define STATUS_PRG              (7UL << 9)
#define STATUS_DIS              (8UL << 9)
#define STATUS_BTST             (9UL << 9)
#define STATUS_SLEEP            (10UL << 9)
#define STATUS_STATE            (0xFUL << 9)
#define STATUS_ERASE_RESET       (1UL << 13)
#define STATUS_WP_ERASE_SKIP     (1UL << 15)
#define STATUS_CIDCSD_OVERWRITE  (1UL << 16)
#define STATUS_OVERRUN           (1UL << 17)
#define STATUS_UNERRUN           (1UL << 18)
#define STATUS_ERROR             (1UL << 19)
#define STATUS_CC_ERROR          (1UL << 20)
#define STATUS_CARD_ECC_FAILED   (1UL << 21)
#define STATUS_ILLEGAL_COMMAND   (1UL << 22)
#define STATUS_COM_CRC_ERROR     (1UL << 23)
#define STATUS_UN_LOCK_FAILED    (1UL << 24)
#define STATUS_CARD_IS_LOCKED    (1UL << 25)
#define STATUS_WP_VIOLATION      (1UL << 26)
#define STATUS_ERASE_PARAM       (1UL << 27)
#define STATUS_ERASE_SEQ_ERROR   (1UL << 28)
#define STATUS_BLOCK_LEN_ERROR   (1UL << 29)
#define STATUS_ADDRESS_MISALIGN  (1UL << 30)
#define STATUS_ADDR_OUT_OR_RANGE (1UL << 31)

#define STATUS_STOP ((uint32_t)( STATUS_CARD_IS_LOCKED \
                        | STATUS_COM_CRC_ERROR \
                        | STATUS_ILLEGAL_COMMAND \
                        | STATUS_CC_ERROR \
                        | STATUS_ERROR \
                        | STATUS_STATE \
                        | STATUS_READY_FOR_DATA ))

#define STATUS_WRITE ((uint32_t)( STATUS_ADDR_OUT_OR_RANGE \
                        | STATUS_ADDRESS_MISALIGN \
                        | STATUS_BLOCK_LEN_ERROR \
                        | STATUS_WP_VIOLATION \
                        | STATUS_CARD_IS_LOCKED \
                        | STATUS_COM_CRC_ERROR \
                        | STATUS_ILLEGAL_COMMAND \
                        | STATUS_CC_ERROR \
                        | STATUS_ERROR \
                        | STATUS_ERASE_RESET \
                        | STATUS_STATE \
                        | STATUS_READY_FOR_DATA ))

#define STATUS_READ  ((uint32_t)( STATUS_ADDR_OUT_OR_RANGE \
                        | STATUS_ADDRESS_MISALIGN \
                        | STATUS_BLOCK_LEN_ERROR \
                        | STATUS_CARD_IS_LOCKED \
                        | STATUS_COM_CRC_ERROR \
                        | STATUS_ILLEGAL_COMMAND \
                        | STATUS_CARD_ECC_FAILED \
                        | STATUS_CC_ERROR \
                        | STATUS_ERROR \
                        | STATUS_ERASE_RESET \
                        | STATUS_STATE \
                        | STATUS_READY_FOR_DATA ))

#define STATUS_SD_SWITCH ((uint32_t)( STATUS_ADDR_OUT_OR_RANGE \
                            | STATUS_CARD_IS_LOCKED \
                            | STATUS_COM_CRC_ERROR \
                            | STATUS_ILLEGAL_COMMAND \
                            | STATUS_CARD_ECC_FAILED \
                            | STATUS_CC_ERROR \
                            | STATUS_ERROR \
                            | STATUS_UNERRUN \
                            | STATUS_OVERRUN \
                            /*| STATUS_STATE*/))

#define STATUS_MMC_SWITCH ((uint32_t)( STATUS_CARD_IS_LOCKED \
                            | STATUS_COM_CRC_ERROR \
                            | STATUS_ILLEGAL_COMMAND \
                            | STATUS_CC_ERROR \
                            | STATUS_ERROR \
                            | STATUS_ERASE_RESET \
                            /*| STATUS_STATE*/ \
                            /*| STATUS_READY_FOR_DATA*/ \
                            | STATUS_SWITCH_ERROR ))
/**     @}*/

/** \addtogroup sdio_status_bm SDIO Status definitions
 *      @{*/
/** The CRC check of the previous command failed. */
#define SDIO_COM_CRC_ERROR   (1UL << 15)
/** Command not legal for the card state. */
#define SDIO_ILLEGAL_COMMAND (1UL << 14)

/** Status bits mask for SDIO R6 */
#define STATUS_SDIO_R6  (SDIO_COM_CRC_ERROR \
                         | SDIO_ILLEGAL_COMMAND \
                         | SDIO_R6_ERROR)
/** Status bits mask for SDIO R5 */
#define STATUS_SDIO_R5  (0/*SDIO_R5_STATE*/ \
                         | SDIO_R5_ERROR \
                         | SDIO_R5_FUNCN_ERROR \
                         | SDIO_R5_OUT_OF_RANGE)

#define DATA_SDIO_R5(response)  ((response) & 0xffu)
/**     @}*/

/*----------------------------------------------------------------------------
 *         Macros
 *----------------------------------------------------------------------------*/

/** Return SD/MMC card address */
#define CARD_ADDR(pSd)          (pSd->wAddress)

/** Return SD/MMC card block size (Default size now, 512B) */
#define BLOCK_SIZE(pSd)         (pSd->wCurrBlockLen)

/** Check if SD Spec version 1.10 or later */
#define SD_IsVer1_10(pSd) \
    ( SD_SCR_SD_SPEC(pSd->SCR) >= SD_SCR_SD_SPEC_1_10 )

/** Check if SD card support HS mode (1.10 or later) */
#define SD_IsHsModeSupported(pSd)  \
    ( /*SD_IsVer1_10(pSd)||*/(SD_CSD_STRUCTURE(pSd->CSD)>=1) )

/** Check if SD card support 4-bit mode (All SD card) */
#define SD_IsBusModeSupported(pSd) (1)

/** Check if MMC Spec version 4 */
#define MMC_IsVer4(pSd)     ( MMC_CSD_SPEC_VERS(pSd->CSD) >= 4 )

/** Check if MMC CSD structure is 1.2 (3.1 or later) */
#define MMC_IsCSDVer1_2(pSd) \
    (  (SD_CSD_STRUCTURE(pSd->CSD)==2) \
     ||(SD_CSD_STRUCTURE(pSd->CSD)>2&&MMC_EXT_CSD_STRUCTURE(pSd->EXT)>=2) )

/** Check if MMC card support boot mode (4.3 or later) */
#define MMC_IsBootModeSupported(pSd) \
    (  (MMC_IsVer4(pSd)&&(eMMC_CID_CBX(pSd->CID)==0x01)  )

/** Check if MMC card support 8-bit mode (4.0 or later) */
#define MMC_IsBusModeSupported(pSd) (MMC_IsVer4(pSd))

/*----------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

/** SD/MMC transfer rate unit codes (10K) list */
static const uint16_t sdmmcTransUnits[8] = {
	10, 100, 1000, 10000,
	0, 0, 0, 0
};

/** SD transfer multiplier factor codes (1/10) list */
static const uint8_t sdTransMultipliers[16] = {
	0, 10, 12, 13, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 70, 80
};

/** MMC transfer multiplier factor codes (1/10) list */
#ifndef SDMMC_TRIM_MMC
static const uint8_t mmcTransMultipliers[16] = {
	0, 10, 12, 13, 15, 20, 26, 30, 35, 40, 45, 52, 55, 60, 70, 80
};
#endif

static const char sdmmcInvalidCode[] = "!Invalid!";
static const struct stringEntry_s sdmmcIOCtrlNames[] = {
	{ SDMMC_IOCTL_BUSY_CHECK,	"BUSY_CHECK",		},
	{ SDMMC_IOCTL_POWER,		"POWER",		},
	{ SDMMC_IOCTL_CANCEL_CMD,	"CANCEL_CMD",		},
	{ SDMMC_IOCTL_RESET,		"RESET",		},
	{ SDMMC_IOCTL_SET_CLOCK,	"SET_CLOCK",		},
	{ SDMMC_IOCTL_SET_BUSMODE,	"SET_BUSMODE",		},
	{ SDMMC_IOCTL_SET_HSMODE,	"SET_HSMODE",		},
	{ SDMMC_IOCTL_SET_BOOTMODE,	"SET_BOOTMODE",		},
	{ SDMMC_IOCTL_SET_LENPREFIX,	"SET_LENPREFIX",	},
	{ SDMMC_IOCTL_GET_CLOCK,	"GET_CLOCK",		},
	{ SDMMC_IOCTL_GET_BUSMODE,	"GET_BUSMODE",		},
	{ SDMMC_IOCTL_GET_HSMODE,	"GET_HSMODE",		},
	{ SDMMC_IOCTL_GET_BOOTMODE,	"GET_BOOTMODE",		},
	{ SDMMC_IOCTL_GET_XFERCOMPL,	"GET_XFERCOMPL",	},
	{ SDMMC_IOCTL_GET_DEVICE,	"GET_DEVICE",		},
};

static const struct stringEntry_s sdmmcRCodeNames[] = {
	{ SDMMC_SUCCESS,		"OK",			},
	{ SDMMC_ERROR_LOCKED,		"ERR_LOCKED",		},
	{ SDMMC_ERROR_BUSY,		"ERR_BUSY",		},
	{ SDMMC_ERROR_NORESPONSE,	"ERR_NO_RESPONSE",	},
	{ SDMMC_CHANGED,		"OK_CHANGED",		},
	{ SDMMC_ERROR,			"ERROR",		},
	{ SDMMC_ERR_IO,			"ERR_IO",		},
	{ SDMMC_ERR_RESP,		"ERR_RESP",		},
	{ SDMMC_ERROR_NOT_INITIALIZED,	"ERR_NOT_INITIALIZED",	},
	{ SDMMC_ERROR_PARAM,		"ERR_PARAM",		},
	{ SDMMC_ERROR_STATE,		"ERR_STATE",		},
	{ SDMMC_ERROR_USER_CANCEL,	"ERR_USER_CANCEL",	},
	{ SDMMC_ERROR_NOT_SUPPORT,	"ERR_NO_SUPPORT",	},
};

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static void
_PrintTitle(const char *title)
{
	int count;

	count = printf("=== %s ", title);
	if (count < 0)
		return;
	for ( ; count < 40; count++)
		putchar('=');
	printf("\n\r");
}

#ifdef __GNUC__
__attribute__ ((format (gnu_printf, 2, 3)))
#endif
static void
_PrintField(const char *name, const char *format, ...)
{
	va_list contents;
	int count;

	count = printf(" .%s", name);
	if (count < 0)
		return;
	for ( ; count < 29; count++)
		putchar(' ');
	va_start(contents, format);
	vprintf(format, contents);
	va_end(contents);
	printf("\n\r");
}

/**
 * Reset SD/MMC driver runtime parameters.
 */
static void
_SdParamReset(sSdCard * pSd)
{
	pSd->dwTotalSize = 0;
	pSd->dwNbBlocks = 0;
	pSd->wBlockSize = 0;

	pSd->wCurrBlockLen = 0;
	pSd->dwCurrSpeed = 0;
	pSd->wAddress = 0;

	pSd->bCardType = 0;
	pSd->bCardSigLevel = 2;
	pSd->bSpeedMode = SDMMC_TIM_MMC_BC;
	pSd->bBusMode = 1;
	pSd->bStatus = SDMMC_NOT_INITIALIZED;
	pSd->bSetBlkCnt = 0;
	pSd->bStopMultXfer = 0;

	memset(&pSd->sdCmd, 0, sizeof(pSd->sdCmd));

	/* Clear our device register cache */
	memset(pSd->CID, 0, 16);
	memset(pSd->CSD, 0, 16);
	memset(pSd->EXT, 0, 512);
	memset(pSd->SSR, 0, 64);
	memset(pSd->SCR, 0, 8);
}

/**
 */
static void
_ResetCmd(sSdmmcCommand * pCmd)
{
	memset(pCmd, 0, sizeof (sSdmmcCommand));
}

/**
 */
static uint8_t
_SendCmd(sSdCard * pSd, fSdmmcCallback fCallback, void *pCbArg)
{
	struct _timeout timeout;
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	sSdHalFunctions *pHal = pSd->pHalf;
	void *pDrv = pSd->pDrv;
	uint32_t err, drv_is_busy;
	uint8_t bRc;
	bool elapsed = false;

	if (pCmd->bCmd != 55)
		trace_debug("Cmd%u(%lx)\n\r", pCmd->bCmd, pCmd->dwArg);
	pCmd->fCallback = fCallback;
	pCmd->pArg = pCbArg;
	bRc = pHal->fCommand(pSd->pDrv, pCmd);

	if (fCallback == NULL) {
		/* Poll command status.
		 * The driver is responsible for detecting and reporting
		 * timeout conditions. Here we only start a backup timer, in
		 * case the driver or the peripheral meets an unexpected
		 * condition. Mind that defining how long a command such as
		 * WRITE_MULTIPLE_BLOCK could take in total may only lead to an
		 * experimental value, lesser than the unrealistic theoretical
		 * maximum.
		 * Abort the command if the driver is still busy after 30s,
		 * which equals 30*1000 system ticks. */
		timer_start_timeout(&timeout, 30000);
		do {
			if (timer_timeout_reached(&timeout))
				elapsed = true;
			drv_is_busy = 1;
			err = pHal->fIOCtrl(pDrv, SDMMC_IOCTL_BUSY_CHECK,
			    (uint32_t)&drv_is_busy);
		}
		while (drv_is_busy && err == SDMMC_OK && !elapsed);
		if (err != SDMMC_OK)
			pCmd->bStatus = (uint8_t)err;
		else if (drv_is_busy) {
			pHal->fIOCtrl(pDrv, SDMMC_IOCTL_CANCEL_CMD, 0);
			pCmd->bStatus = SDMMC_NO_RESPONSE;
		}
		bRc = pCmd->bStatus;
	}

	if (bRc == SDMMC_CHANGED)
		trace_warning("Cmd%u %s\n\r", pCmd->bCmd,
		    SD_StringifyRetCode(bRc));
	else if (bRc != SDMMC_OK)
		trace_error("Cmd%u %s\n\r", pCmd->bCmd,
		    SD_StringifyRetCode(bRc));
	else if (pCmd->cmdOp.bmBits.respType == 1 && pCmd->pResp)
		trace_debug("Cmd%u st %lx\n\r", pCmd->bCmd, *pCmd->pResp);
	return bRc;
}

/**
 */
static uint8_t
_HwSetBusWidth(sSdCard * pSd, uint8_t newWidth)
{
	sSdHalFunctions *pHal = pSd->pHalf;
	void *pDrv = pSd->pDrv;
	uint32_t busWidth = newWidth;
	uint32_t rc;

	rc = pHal->fIOCtrl(pDrv, SDMMC_IOCTL_SET_BUSMODE,
			   (uint32_t) & busWidth);
	return rc;
}

/**
 */
static bool
_HwIsTimingSupported(sSdCard * pSd, uint8_t timingMode)
{
	sSdHalFunctions *pHal = pSd->pHalf;
	void *pDrv = pSd->pDrv;
	uint32_t rc, mode = timingMode;

	rc = pHal->fIOCtrl(pDrv, SDMMC_IOCTL_GET_HSMODE, (uint32_t) & mode);
	return rc == SDMMC_OK ? (mode ? true : false) : false;
}

/**
 */
static uint8_t
_HwSetHsMode(sSdCard * pSd, uint8_t timingMode)
{
	sSdHalFunctions *pHal = pSd->pHalf;
	void *pDrv = pSd->pDrv;
	uint32_t mode = timingMode;
	uint32_t rc;

	rc = pHal->fIOCtrl(pDrv, SDMMC_IOCTL_SET_HSMODE, (uint32_t) & mode);
	if ((rc == SDMMC_OK || rc == SDMMC_CHANGED)
	    && (mode > 0xff || mode != (uint32_t)timingMode))
		rc = SDMMC_CHANGED;
	return rc;
}

/**
 */
static uint8_t
_HwPowerDevice(sSdCard * pSd, uint8_t nowSwitchOn)
{
	sSdHalFunctions *pHal = pSd->pHalf;
	void *pDrv = pSd->pDrv;
	uint32_t switchOn = nowSwitchOn;
	uint32_t rc;
	rc = pHal->fIOCtrl(pDrv, SDMMC_IOCTL_POWER, (uint32_t) & switchOn);
	return rc;
}

/**
 */
static uint8_t
_HwSetClock(sSdCard * pSd, uint32_t * pIoValClk)
{
	sSdHalFunctions *pHal = pSd->pHalf;
	void *pDrv = pSd->pDrv;
	uint32_t clock = *pIoValClk;
	uint32_t rc;
	rc = pHal->fIOCtrl(pDrv, SDMMC_IOCTL_SET_CLOCK, (uint32_t) & clock);
	if (rc == SDMMC_SUCCESS || rc == SDMMC_CHANGED) {
		*pIoValClk = clock;
		trace_info("Device clk %lu kHz\n\r", clock / 1000UL);
	}
	return rc;
}

/**
 */
static uint8_t
_HwReset(sSdCard * pSd)
{
	sSdHalFunctions *pHal = pSd->pHalf;
	void *pDrv = pSd->pDrv;
	uint32_t rc;
	rc = pHal->fIOCtrl(pDrv, SDMMC_IOCTL_RESET, 0);
	return rc;
}

/**
 * Find SDIO ManfID, Fun0 tuple.
 * \param pSd         Pointer to \ref sSdCard instance.
 * \param address     Search area start address.
 * \param size        Search area size.
 * \param pAddrManfID Pointer to ManfID address value buffer.
 * \param pAddrFunc0  Pointer to Func0 address value buffer.
 */
static uint8_t
SdioFindTuples(sSdCard * pSd,
	       uint32_t address, uint32_t size,
	       uint32_t * pAddrManfID, uint32_t * pAddrFunc0)
{
	uint8_t error, tmp[3];
	uint32_t addr = address;
	uint8_t flagFound = 0;	/* 1:Manf, 2:Func0 */
	uint32_t addManfID = 0, addFunc0 = 0;
	for (; flagFound != 3;) {
		error = SDIO_ReadDirect(pSd, SDIO_CIA, addr, tmp, 3);
		if (error)
			return error;
		/* End */
		if (tmp[0] == CISTPL_END)
			break;
		/* ManfID */
		else if (tmp[0] == CISTPL_MANFID) {
			flagFound |= 1;
			addManfID = addr;
		}
		/* Func0 */
		else if (tmp[0] == CISTPL_FUNCE && tmp[2] == 0x00) {
			flagFound |= 2;
			addFunc0 = addr;
		}
		/* Tuple error ? */
		if (tmp[1] == 0)
			break;
		/* Next address */
		addr += (tmp[1] + 2);
		if (addr > (address + size))
			break;
	}
	if (pAddrManfID)
		*pAddrManfID = addManfID;
	if (pAddrFunc0)
		*pAddrFunc0 = addFunc0;
	return 0;
}

/**
 * \brief Decode Trans Speed Value
 * \param code The trans speed code value.
 * \param unitCodes  Unit list in 10K, 0 as unused value.
 * \param multiCodes Multiplier list in 1/10, index 1 ~ 15 is valid.
 */
static uint32_t
SdmmcDecodeTransSpeed(uint32_t code,
		      const uint16_t * unitCodes, const uint8_t * multiCodes)
{
	uint32_t speed;
	uint8_t unitI, mulI;

	/* Unit code is valid ? */
	unitI = code & 0x7;
	if (unitCodes[unitI] == 0)
		return 0;

	/* Multi code is valid ? */
	mulI = (code >> 3) & 0xF;
	if (multiCodes[mulI] == 0)
		return 0;

	speed = (uint32_t)unitCodes[unitI] * multiCodes[mulI];
	return speed;
}

/**
 * Initialization delay: The maximum of 1 msec, 74 clock cycles and supply ramp
 * up time.
 * Returns the command transfer result (see SendMciCommand).
 * \param pSd Pointer to \ref sSdCard instance.
 */
static uint8_t
Pon(sSdCard * pSd)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	trace_debug("PwrON\n\r");
	_ResetCmd(pCmd);

	/* Fill command */
	pCmd->cmdOp.wVal = SDMMC_CMD_POWERONINIT;

	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
	return bRc;
}

/**
 * Resets all cards to idle state
 * \param pSd Pointer to \ref sSdCard instance.
 * \param arg  Argument used.
 * \return the command transfer result (see SendMciCommand).
 */
static uint8_t
Cmd0(sSdCard * pSd, uint8_t arg)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	_ResetCmd(pCmd);

	/* Fill command */
	pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(0);
	pCmd->dwArg = arg;
	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
	return bRc;
}

/**
 * MMC send operation condition command.
 * Sends host capacity support information and activates the card's
 * initialization process.
 * Returns the command transfer result (see SendMciCommand).
 * \param pSd  Pointer to \ref sSdCard instance.
 * \param hc  Upon success tells whether the device is a high capacity device.
 */
#ifndef SDMMC_TRIM_MMC
static uint8_t
Cmd1(sSdCard * pSd, bool * hc)
{
	struct _timeout timeout;
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint32_t arg, ocr = 0;
	uint8_t rc;
	int8_t elapsed = -1;

	/* Tell the device that the host supports 512-byte sector addressing */
	arg = MMC_OCR_ACCESS_SECTOR;
	/* Tell the MMC device which voltage the host supplies to the VDD line
	 * (MMC card) or VCC line (e.MMC device).
	 * TODO get this board-specific value from platform code. On the
	 * SAMA5D2-XULT board, VDD is 3.3V ± 1%. */
	arg |= SD_OCR_VDD_32_33 | SD_OCR_VDD_33_34;

	/* Fill command */
	_ResetCmd(pCmd);
	pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(3) | SDMMC_CMD_bmOD;
	pCmd->bCmd = 1;
	pCmd->dwArg = arg;
	pCmd->pResp = &ocr;

	do {
		rc = _SendCmd(pSd, NULL, NULL);
		if (rc == SDMMC_SUCCESS && !(ocr & SD_OCR_BUSYN))
			rc = SDMMC_ERROR_BUSY;
		/* Allow the device to be busy for up to 1s,
		 * which equals 1000 system ticks. */
		if (elapsed < 0) {
			timer_start_timeout(&timeout, 1000);
			elapsed = 0;
		}
		else if (timer_timeout_reached(&timeout))
			elapsed = 1;
	}
	while (rc == SDMMC_ERROR_BUSY && !elapsed);
	if (rc != SDMMC_SUCCESS)
		return rc;

	/* Analyze the final contents of the OCR Register */
	trace_info("Device supports%s%s 3.0V:[%c%c%c%c%c%c]"
	    " 3.3V:[%c%c%c%c%c%c]\n\r",
	    ocr & MMC_OCR_VDD_170_195 ? " 1.8V" : "",
	    ocr & MMC_OCR_VDD_200_270 ? " 2.xV" : "",
	    ocr & SD_OCR_VDD_27_28 ? 'X' : '.',
	    ocr & SD_OCR_VDD_28_29 ? 'X' : '.',
	    ocr & SD_OCR_VDD_29_30 ? 'X' : '.',
	    ocr & SD_OCR_VDD_30_31 ? 'X' : '.',
	    ocr & SD_OCR_VDD_31_32 ? 'X' : '.',
	    ocr & SD_OCR_VDD_32_33 ? 'X' : '.',
	    ocr & SD_OCR_VDD_30_31 ? 'X' : '.',
	    ocr & SD_OCR_VDD_31_32 ? 'X' : '.',
	    ocr & SD_OCR_VDD_32_33 ? 'X' : '.',
	    ocr & SD_OCR_VDD_33_34 ? 'X' : '.',
	    ocr & SD_OCR_VDD_34_35 ? 'X' : '.',
	    ocr & SD_OCR_VDD_35_36 ? 'X' : '.');
	trace_info("Device access 0x%lx\n\r", ocr >> 29 & 0x3ul);
	*hc = (ocr & MMC_OCR_ACCESS_MODE) == MMC_OCR_ACCESS_SECTOR
	    ? true : false;
	return SDMMC_SUCCESS;
}
#endif

/**
 * Asks any card to send the CID numbers
 * on the CMD line (any card that is
 * connected to the host will respond)
 * Returns the command transfer result (see SendMciCommand).
 * \param pSd  Pointer to a SD card driver instance.
 * \param pCID Pointer to buffer for storing the CID numbers.
 */
static uint8_t
Cmd2(sSdCard * pSd)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	_ResetCmd(pCmd);

	/* Fill command */
	pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(2)
	    | SDMMC_CMD_bmOD;
	pCmd->bCmd = 2;
	pCmd->pResp = pSd->CID;

	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
	return bRc;
}

/**
 * Ask the SD card to publish a new relative address (RCA)
 *         or
 * Assign relative address to the MMC card
 * Returns the command transfer result (see SendMciCommand).
 * \param pSd   Pointer to a SD card driver instance.
 * \param pRsp  Pointer to buffer to fill response (address on 31:16).
 */
static uint8_t
Cmd3(sSdCard * pSd)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint32_t dwResp;
	uint8_t bRc;

	_ResetCmd(pCmd);

	/* Fill command */
	pCmd->bCmd = 3;
	pCmd->pResp = &dwResp;

#ifndef SDMMC_TRIM_MMC
	if (pSd->bCardType == CARD_MMC || pSd->bCardType == CARD_MMCHD) {
		uint16_t wNewAddr = (uint16_t)max_u32((CARD_ADDR(pSd) + 1)
		    & 0xffff, 2);
		pCmd->dwArg = wNewAddr << 16;

		pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(1) | SDMMC_CMD_bmOD;
		bRc = _SendCmd(pSd, NULL, NULL);
		if (bRc == SDMMC_OK) {
			CARD_ADDR(pSd) = wNewAddr;
		}
	}
	else
#endif
	{
		pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(6) | SDMMC_CMD_bmOD;
		bRc = _SendCmd(pSd, NULL, NULL);
		if (bRc == SDMMC_OK) {
			CARD_ADDR(pSd) = dwResp >> 16;
		}
	}
	return bRc;
}

/**
 * SDIO SEND OPERATION CONDITION (OCR) command.
 * Sends host capacity support information and acrivates the card's
 * initialization process.
 * \return The command transfer result (see SendMciCommand).
 * \param pSd     Pointer to a SD/MMC card driver instance.
 * \param pIo     Pointer to data sent as well as response buffer (32bit).
 */
#ifndef SDMMC_TRIM_SDIO
static uint8_t
Cmd5(sSdCard * pSd, uint32_t * pIo)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	_ResetCmd(pCmd);

	/* Fill command */
	pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(4) | SDMMC_CMD_bmIO
	    | SDMMC_CMD_bmOD;
	pCmd->bCmd = 5;
	pCmd->dwArg = *pIo;
	pCmd->pResp = pIo;

	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
	return bRc;
}
#endif

/**
 * Switches the mode of operation of the selected card.
 * CMD6 is valid under the "trans" state.
 * \return The command transfer result (see SendMciCommand).
 * \param  pSd         Pointer to a SD/MMC card driver instance.
 * \param  pSwitchArg  Pointer to the SWITCH_FUNC command argument.
 * \param  pStatus     Pointer to where the 512bit status is returned.
 * The buffer shall follow the peripheral and DMA alignment requirements.
 * \param  pResp       Pointer to where the response is returned.
 */
static uint8_t
SdCmd6(sSdCard * pSd,
       const SdCmd6Arg * pSwitchArg, uint8_t * pStatus, uint32_t * pResp)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	assert(pSd);
	assert(pSwitchArg);

	_ResetCmd(pCmd);

	pCmd->bCmd = 6;
	pCmd->cmdOp.wVal = SDMMC_CMD_CDATARX(1);
	pCmd->dwArg = (pSwitchArg->set << 31)
	    | (pSwitchArg->reserved << 30)
	    | (pSwitchArg->func_grp6 << 20)
	    | (pSwitchArg->func_grp5 << 16)
	    | (pSwitchArg->pwr_limit << 12)
	    | (pSwitchArg->drv_strgth << 8)
	    | (pSwitchArg->cmd_sys << 4)
	    | (pSwitchArg->acc_mode << 0);
	if (pStatus) {
		pCmd->wBlockSize = 512 / 8;
		pCmd->wNbBlocks = 1;
		pCmd->pData = pStatus;
	}
	pCmd->pResp = pResp;

	bRc = _SendCmd(pSd, NULL, NULL);
	return bRc;
}

/**
 * Switches the mode of operation of the selected card or
 * Modifies the EXT_CSD registers.
 * CMD6 is valid under the "trans" state.
 * \return The command transfer result (see SendMciCommand).
 * \param  pSd         Pointer to a SD/MMC card driver instance.
 * \param  pSwitchArg  Pointer to a MmcCmd6Arg instance.
 * \param  pResp       Pointer to where the response is returned.
 */
static uint8_t
MmcCmd6(sSdCard * pSd, const void *pSwitchArg, uint32_t * pResp)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;
	MmcCmd6Arg *pMmcSwitch;

	assert(pSd);
	assert(pSwitchArg);

	_ResetCmd(pCmd);

	pMmcSwitch = (MmcCmd6Arg *) pSwitchArg;
	pCmd->bCmd = 6;
	pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(1) | SDMMC_CMD_bmBUSY;
	pCmd->dwArg = (pMmcSwitch->access << 24)
	    | (pMmcSwitch->index << 16)
	    | (pMmcSwitch->value << 8)
	    | (pMmcSwitch->cmdSet << 0);
	pCmd->pResp = pResp;

	bRc = _SendCmd(pSd, NULL, NULL);
	if (!bRc && pResp && *pResp & STATUS_MMC_SWITCH)
		trace_error("st %lx\n\r", *pResp);
	return bRc;
}

/**
 * Command toggles a card between the
 * stand-by and transfer states or between
 * the programming and disconnect states.
 * Returns the command transfer result (see SendMciCommand).
 * \param pSd       Pointer to a SD card driver instance.
 * \param cardAddr  Relative Card Address (0 deselects all).
 */
static uint8_t
Cmd7(sSdCard * pSd, uint16_t address)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	_ResetCmd(pCmd);

	/* Fill command */
	/* If this function is used to transition the MMC device from the
	 * Disconnected to Programming state, then busy checking is required */
	if (address)
		pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(1) | SDMMC_CMD_bmBUSY;
	else
		pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(0);
	pCmd->bCmd = 7;
	pCmd->dwArg = address << 16;

	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
	return bRc;
}

/**
 * Sends SD Memory Card interface condition, which includes host supply
 * voltage information and asks the card whether card supports voltage.
 * Should be performed at initialization time to detect the card type.
 * \param pSd             Pointer to a SD card driver instance.
 * \param supplyVoltage   Expected supply voltage(SD).
 * \return 0 if successful;
 *         otherwise returns SD_ERROR_NORESPONSE if the card did not answer
 *         the command, or SDMMC_ERROR.
 */
static uint8_t
SdCmd8(sSdCard * pSd, uint8_t supplyVoltage)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	const uint32_t arg = supplyVoltage << SD_IFC_VHS_Pos
	    | SD_IFC_CHK_PATTERN_STD;
	uint32_t dwResp = 0;
	uint8_t bRc;

	_ResetCmd(pCmd);

	/* Fill command information */
	pCmd->bCmd = 8;
	pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(7)
	    | SDMMC_CMD_bmOD;
	pCmd->dwArg = arg;
	pCmd->pResp = &dwResp;

	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);

	/* Expect the R7 response, which is the card interface condition.
	 * Expect VCA to match VHS, and the check pattern to match as well. */
	if (bRc == SDMMC_SUCCESS
	    && (dwResp & (SD_IFC_VHS_Msk | SD_IFC_CHK_PATTERN_Msk)) == arg)
		return SDMMC_SUCCESS;
	else if (bRc == SDMMC_ERROR_NORESPONSE)
		return SDMMC_ERROR_NORESPONSE;
	else
		return SDMMC_ERROR;
}

/**
 * SEND_EXT_CSD, to get EXT_CSD register as a block of data.
 * Valid under "trans" state.
 * \param pSd   Pointer to a SD card driver instance.
 * \param pEXT  512 byte buffer pointer for EXT_CSD data.
 * The buffer shall follow the peripheral and DMA alignment requirements.
 * \return 0 if successful;
 *         otherwise returns SD_ERROR_NORESPONSE if the card did not answer
 *         the command, or SDMMC_ERROR.
 */
#ifndef SDMMC_TRIM_MMC
static uint8_t
MmcCmd8(sSdCard * pSd, uint8_t * pEXT)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	_ResetCmd(pCmd);

	/* Fill command */
	pCmd->bCmd = 8;
	pCmd->cmdOp.wVal = SDMMC_CMD_CDATARX(1);
	pCmd->wBlockSize = 512;
	pCmd->wNbBlocks = 1;
	pCmd->pData = pEXT;

	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
	return bRc;
}
#endif

/**
 * Addressed card sends its card-specific
 * data (CSD) on the CMD line.
 * Returns the command transfer result (see SendMciCommand).
 * \param pSd       Pointer to a SD card driver instance.
 * \param cardAddr  Card Relative Address.
 * \param pCSD      Pointer to buffer for CSD data.
 */
static uint8_t
Cmd9(sSdCard * pSd)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	_ResetCmd(pCmd);

	/* Fill command */
	pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(2);
	pCmd->bCmd = 9;
	pCmd->dwArg = CARD_ADDR(pSd) << 16;
	pCmd->pResp = pSd->CSD;

	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
	return bRc;
}

/**
 * Switch the SD card bus to low signaling voltage level.
 * \param pSd       Pointer to a SD card driver instance.
 * \param pStatus   Pointer to a status variable.
 * \return Command transfer result.
 */
static uint8_t
Cmd11(sSdCard * pSd, uint32_t * pStatus)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	_ResetCmd(pCmd);

	/* Fill command */
	pCmd->bCmd = 11;
	pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(1);
	pCmd->dwArg = 0;
	pCmd->pResp = pStatus;

	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
	return bRc;
}

/**
 * Forces the card to stop transmission
 * \param pSd      Pointer to a SD card driver instance.
 * \param pStatus  Pointer to a status variable.
 */
static uint8_t
Cmd12(sSdCard * pSd, uint32_t * pStatus)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	_ResetCmd(pCmd);

	/* Fill command */
	pCmd->bCmd = 12;
	pCmd->cmdOp.wVal = SDMMC_CMD_CSTOP | SDMMC_CMD_bmBUSY;
	pCmd->pResp = pStatus;

	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
	return bRc;
}

/**
 * Addressed card sends its status register.
 * Returns the command transfer result (see SendMciCommand).
 * \param pSd       Pointer to a SD card driver instance.
 * \param pStatus   Pointer to a status variable.
 */
static uint8_t
Cmd13(sSdCard * pSd, uint32_t * pStatus)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	_ResetCmd(pCmd);

	/* Fill command */
	pCmd->bCmd = 13;
	pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(1);
	pCmd->dwArg = CARD_ADDR(pSd) << 16;
	pCmd->pResp = pStatus;

	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
	return bRc;
}

/**
 * In the case of a Standard Capacity SD Memory Card, this command sets the
 * block length (in bytes) for all following block commands
 * (read, write, lock).
 * Default block length is fixed to 512 Bytes.
 * Set length is valid for memory access commands only if partial block read
 * operation are allowed in CSD.
 * In the case of a High Capacity SD Memory Card, block length set by CMD16
 * command does not affect the memory read and write commands. Always 512
 * Bytes fixed block length is used. This command is effective for LOCK_UNLOCK
 * command. In both cases, if block length is set larger than 512Bytes, the
 * card sets the BLOCK_LEN_ERROR bit.
 * \param pSd  Pointer to a SD card driver instance.
 * \param blockLength  Block length in bytes.
 */
static uint8_t
Cmd16(sSdCard * pSd, uint16_t blkLen)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	_ResetCmd(pCmd);

	/* Fill command */
	pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(1);
	pCmd->bCmd = 16;
	pCmd->dwArg = blkLen;

	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
	return bRc;
}

/**
 * Read single block command
 * \param pSd  Pointer to a SD card driver instance.
 * \param pData     Pointer to the buffer to be filled.
 * The buffer shall follow the peripheral and DMA alignment requirements.
 * \param address   Data Address on SD/MMC card.
 * \param pStatus   Pointer response buffer as status return.
 * \param fCallback Pointer to optional callback invoked on command end.
 *                  NULL:    Function return until command finished.
 *                  Pointer: Return immediately and invoke callback at end.
 *                  Callback argument is fixed to a pointer to sSdCard instance.
 */
static uint8_t
Cmd17(sSdCard * pSd,
      uint8_t * pData,
      uint32_t address, uint32_t * pStatus, fSdmmcCallback callback)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	_ResetCmd(pCmd);

	/* Fill command */
	pCmd->cmdOp.wVal = SDMMC_CMD_CDATARX(1);
	pCmd->bCmd = 17;
	pCmd->dwArg = address;
	pCmd->pResp = pStatus;
	pCmd->wBlockSize = BLOCK_SIZE(pSd);
	pCmd->wNbBlocks = 1;
	pCmd->pData = pData;
	pCmd->fCallback = callback;

	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
	return bRc;
}

/**
 * A host reads the reversed bus testing data pattern from a card
 * \param pSd  Pointer to a SD card driver instance.
 * \param pData     Pointer to the buffer to be filled.
 * The buffer shall follow the peripheral and DMA alignment requirements.
 * \param len       Length of data in byte
 * \param pStatus   Pointer response buffer as status return.
 */
#ifndef SDMMC_TRIM_MMC
static uint8_t
Cmd14(sSdCard * pSd, uint8_t * pData, uint8_t len, uint32_t * pStatus)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	_ResetCmd(pCmd);

	/* Fill command */
	pCmd->cmdOp.wVal = SDMMC_CMD_CDATARX(1);
	pCmd->bCmd = 14;
	pCmd->pResp = pStatus;
	pCmd->wBlockSize = len;
	pCmd->wNbBlocks = 1;
	pCmd->pData = pData;

	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
	return bRc;
}

/**
 * A host sends the bus test data pattern to a card.
 * \param pSd  Pointer to a SD card driver instance.
 * \param pData     Pointer to the buffer to be filled.
 * The buffer shall follow the peripheral and DMA alignment requirements.
 * \param len       Length of data in byte
 * \param pStatus   Pointer response buffer as status return.
*/
static uint8_t
Cmd19(sSdCard * pSd, uint8_t * pData, uint8_t len, uint32_t * pStatus)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	_ResetCmd(pCmd);

	/* Fill command */
	pCmd->cmdOp.wVal = SDMMC_CMD_CDATATX(1);
	pCmd->bCmd = 19;
	pCmd->pResp = pStatus;
	pCmd->wBlockSize = len;
	pCmd->wNbBlocks = 1;
	pCmd->pData = pData;

	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
	return bRc;
}
#endif

/**
 * Continously transfers datablocks from card to host until interrupted by a
 * STOP_TRANSMISSION command.
 * \param pSd       Pointer to a SD card driver instance.
 * \param nbBlocks  Number of blocks to send.
 * \param pData     Pointer to the buffer to be filled.
 * The buffer shall follow the peripheral and DMA alignment requirements.
 * \param address   Data Address on SD/MMC card.
 * \param pStatus   Pointer to the response status.
 * \param fCallback Pointer to optional callback invoked on command end.
 *                  NULL:    Function return until command finished.
 *                  Pointer: Return immediately and invoke callback at end.
 *                  Callback argument is fixed to a pointer to sSdCard instance.
 */
static uint8_t
Cmd18(sSdCard * pSd,
      uint16_t * nbBlock,
      uint8_t * pData,
      uint32_t address, uint32_t * pStatus, fSdmmcCallback callback)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	_ResetCmd(pCmd);

	/* Fill command */
	pCmd->cmdOp.wVal = SDMMC_CMD_CDATARX(1);
	pCmd->bCmd = 18;
	pCmd->dwArg = address;
	pCmd->pResp = pStatus;
	pCmd->wBlockSize = BLOCK_SIZE(pSd);
	pCmd->wNbBlocks = *nbBlock;
	pCmd->pData = pData;
	pCmd->fCallback = callback;
	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
	if (bRc == SDMMC_CHANGED)
		*nbBlock = pCmd->wNbBlocks;
	return bRc;
}

/**
 * Defines the number of blocks (read/write) and the reliable writer parameter
 * (write) for a block read or write command
 * data (CSD) on the CMD line.
 * Returns the command transfer result (see SendMciCommand).
 * \param pSd       Pointer to a SD card driver instance.
 * \param write     Write Request parameter.
 * \param blocks    number of blocks.
 */
static uint8_t
Cmd23(sSdCard * pSd, uint8_t write, uint32_t blocks, uint32_t * pStatus)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	_ResetCmd(pCmd);

	/* Fill command */
	pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(1);
	pCmd->bCmd = 23;
	pCmd->wNbBlocks = 0;
	pCmd->dwArg = write << 31 | blocks;
	pCmd->pResp = pStatus;

	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
	return bRc;
}

/**
 * Write single block command
 * \param pSd  Pointer to a SD card driver instance.
 * \param blockSize Block size (shall be set to 512 in case of high capacity).
 * \param pData     Pointer to the buffer to be filled.
 * The buffer shall follow the peripheral and DMA alignment requirements.
 * \param address   Data Address on SD/MMC card.
 * \param pStatus   Pointer to response buffer as status.
 * \param fCallback Pointer to optional callback invoked on command end.
 *                  NULL:    Function return until command finished.
 *                  Pointer: Return immediately and invoke callback at end.
 *                  Callback argument is fixed to a pointer to sSdCard instance.
 */
static uint8_t
Cmd24(sSdCard * pSd,
      uint8_t * pData,
      uint32_t address, uint32_t * pStatus, fSdmmcCallback callback)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	_ResetCmd(pCmd);

	/* Fill command */
	pCmd->cmdOp.wVal = SDMMC_CMD_CDATATX(1);
	pCmd->bCmd = 24;
	pCmd->dwArg = address;
	pCmd->pResp = pStatus;
	pCmd->wBlockSize = BLOCK_SIZE(pSd);
	pCmd->wNbBlocks = 1;
	pCmd->pData = pData;
	pCmd->fCallback = callback;
	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
	return bRc;
}

/**
 * Write multiple block command
 * \param pSd  Pointer to a SD card driver instance.
 * \param blockSize Block size (shall be set to 512 in case of high capacity).
 * \param nbBlock   Number of blocks to send.
 * \param pData     Pointer to the buffer to be filled.
 * The buffer shall follow the peripheral and DMA alignment requirements.
 * \param address   Data Address on SD/MMC card.
 * \param pStatus   Pointer to the response buffer as status.
 * \param fCallback Pointer to optional callback invoked on command end.
 *                  NULL:    Function return until command finished.
 *                  Pointer: Return immediately and invoke callback at end.
 *                  Callback argument is fixed to a pointer to sSdCard instance.
 */
static uint8_t
Cmd25(sSdCard * pSd,
      uint16_t * nbBlock,
      uint8_t * pData,
      uint32_t address, uint32_t * pStatus, fSdmmcCallback callback)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	_ResetCmd(pCmd);

	/* Fill command */
	pCmd->cmdOp.wVal = SDMMC_CMD_CDATATX(1);
	pCmd->bCmd = 25;
	pCmd->dwArg = address;
	pCmd->pResp = pStatus;
	pCmd->wBlockSize = BLOCK_SIZE(pSd);
	pCmd->wNbBlocks = *nbBlock;
	pCmd->pData = pData;
	pCmd->fCallback = callback;
	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
	if (bRc == SDMMC_CHANGED)
		*nbBlock = pCmd->wNbBlocks;
	return bRc;
}

/**
 * SDIO IO_RW_DIRECT command, response R5.
 * \return the command transfer result (see SendMciCommand).
 * \param pSd       Pointer to a SD card driver instance.
 * \param pIoData   Pointer to input argument (\ref SdioRwDirectArg) and
 *                  response (\ref SdmmcR5) buffer.
 * \param fCallback Pointer to optional callback invoked on command end.
 *                  NULL:    Function return until command finished.
 *                  Pointer: Return immediately and invoke callback at end.
 *                  Callback argument is fixed to a pointer to sSdCard instance.
 */
static uint8_t
Cmd52(sSdCard * pSd,
      uint8_t wrFlag,
      uint8_t funcNb, uint8_t rdAfterWr, uint32_t addr, uint32_t * pIoData)
{
	SdioCmd52Arg *pArg52 = (SdioCmd52Arg *) pIoData;
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	pArg52->rwFlag = wrFlag;
	pArg52->functionNum = funcNb;
	pArg52->rawFlag = rdAfterWr;
	pArg52->regAddress = addr;

	_ResetCmd(pCmd);

	/* Fill command */
	pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(5) | SDMMC_CMD_bmIO;
	pCmd->bCmd = 52;
	pCmd->dwArg = *pIoData;
	pCmd->pResp = pIoData;

	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
	return bRc;
}

/**
 * SDIO IO_RW_EXTENDED command, response R5.
 * \param pSd       Pointer to a SD card driver instance.
 * \param pArgResp  Pointer to input argument (\ref SdioRwExtArg)
 *                  and response (\ref SdmmcR5) buffer.
 * \param pData     Pointer to data buffer to transfer.
 * The buffer shall follow the peripheral and DMA alignment requirements.
 * \param size      Transfer data size.
 * \param fCallback Pointer to optional callback invoked on command end.
 *                  NULL:    Function return until command finished.
 *                  Pointer: Return immediately and invoke callback at end.
 *                  Callback argument is fixed to a pointer to sSdCard instance.
 * \param pArg Callback argument.
 */
static uint8_t
Cmd53(sSdCard * pSd,
      uint8_t wrFlag,
      uint8_t funcNb,
      uint8_t blockMode,
      uint8_t incAddr,
      uint32_t addr,
      uint8_t * pIoData,
      uint16_t len, uint32_t * pArgResp, fSdmmcCallback fCallback, void *pCbArg)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	SdioCmd53Arg *pArg53;
	/* TODO check that all input values fit the argument fields */
	pArg53 = (SdioCmd53Arg *) pArgResp;
	pArg53->rwFlag = wrFlag;
	pArg53->functionNum = funcNb;
	pArg53->blockMode = blockMode;
	pArg53->opCode = incAddr;
	pArg53->regAddress = addr;
	pArg53->count = len < 512 ? len : 0;

	/* Fill command */
	pCmd->bCmd = 53;
	pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(5)
	    | SDMMC_CMD_bmIO;
	if (wrFlag) {
		pCmd->cmdOp.wVal |= SDMMC_CMD_bmDATATX;
	} else {
		pCmd->cmdOp.wVal |= SDMMC_CMD_bmDATARX;
	}
	if (blockMode) {
		pCmd->wBlockSize = pSd->wCurrBlockLen;
		pCmd->wNbBlocks = len;
	} else {
		pCmd->wBlockSize = len;
		pCmd->wNbBlocks = 1;
	}
	pCmd->dwArg = *pArgResp;
	pCmd->pResp = pArgResp;
	pCmd->pData = pIoData;
	pCmd->fCallback = fCallback;
	pCmd->pArg = pCbArg;

	bRc = _SendCmd(pSd, NULL, NULL);
	return bRc;
}

/**
 * Indicates to the card that the next command is an application specific
 * command rather than a standard command.
 * \return the command transfer result (see SendMciCommand).
 * \param pSd       Pointer to a SD card driver instance.
 * \param cardAddr  Card Relative Address.
 */
static uint8_t
Cmd55(sSdCard * pSd, uint16_t cardAddr)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint32_t dwResp;
	uint8_t bRc;

	_ResetCmd(pCmd);

	/* Fill command information */
	pCmd->bCmd = 55;
	pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(1)
	    | (cardAddr ? 0 : SDMMC_CMD_bmOD);
	pCmd->dwArg = cardAddr << 16;
	pCmd->pResp = &dwResp;

	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
	return bRc;
}

/**
 * Defines the data bus width (00=1bit or 10=4 bits bus) to be used for data
 * transfer.
 * The allowed data bus widths are given in SCR register.
 * \param pSd  Pointer to a SD card driver instance.
 * \param busWidth  Bus width in bits (4 or 1).
 * \return the command transfer result (see SendCommand).
 */
static uint8_t
Acmd6(sSdCard * pSd, uint8_t busWidth)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t error;

	trace_debug("Acmd%u\n\r", 6);
	error = Cmd55(pSd, CARD_ADDR(pSd));
	if (error)
		goto End;
	_ResetCmd(pCmd);
	pCmd->bCmd = 6;
	pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(1);
	pCmd->dwArg = (busWidth == 4)
	    ? SD_SSR_DATA_BUS_WIDTH_4BIT : SD_SSR_DATA_BUS_WIDTH_1BIT;
	error = _SendCmd(pSd, NULL, NULL);

End:
	if (error)
		trace_error("Acmd%u %s\n\r", 6, SD_StringifyRetCode(error));
	return error;
}

/**
 * From the selected card get its SD Status Register (SSR).
 * ACMD13 is valid under the Transfer state.
 * \param pSd  Pointer to a SD card driver instance.
 * \param pSSR  Pointer to a 64-byte buffer receiving the contents of the SSR.
 * The buffer shall follow the peripheral and DMA alignment requirements.
 * \param pResp  Pointer to where the response is returned.
 * \return The command transfer result (see SendCommand).
 */
static uint8_t
Acmd13(sSdCard * pSd, uint8_t * pSSR, uint32_t * pResp)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t error;

	assert(pSd);

	trace_debug("Acmd%u\n\r", 13);
	error = Cmd55(pSd, CARD_ADDR(pSd));
	if (error)
		goto End;
	_ResetCmd(pCmd);
	pCmd->bCmd = 13;
	pCmd->cmdOp.wVal = SDMMC_CMD_CDATARX(1);
	if (pSSR) {
		pCmd->wBlockSize = 512 / 8;
		pCmd->wNbBlocks = 1;
		pCmd->pData = pSSR;
	}
	pCmd->pResp = pResp;
	error = _SendCmd(pSd, NULL, NULL);

End:
	if (error)
		trace_error("Acmd%u %s\n\r", 13, SD_StringifyRetCode(error));
	return error;
}

/**
 * Asks to all cards to send their operations conditions.
 * Returns the command transfer result (see SendCommand).
 * \param pSd  Pointer to a SD card driver instance.
 * \param low_sig_lvl  In: tells whether the host supports UHS-I timing modes.
 * Out: tells whether the device may switch to low signaling level.
 * \param hc  In: tells whether the device has replied to SEND_IF_COND.
 * Out: tells whether the device is a high capacity device.
 */
static uint8_t
Acmd41(sSdCard * pSd, bool * low_sig_lvl, bool * hc)
{
	struct _timeout timeout;
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	/* TODO get this board-specific value from platform code. On the
	 * SAMA5D2-XULT board, VDD is 3.3V ± 1%. */
	const uint32_t vdd_range = SD_OCR_VDD_32_33 | SD_OCR_VDD_33_34;
	uint32_t arg, ocr = 0;
	uint8_t rc;
	int8_t elapsed = -1;

	trace_debug("Acmd%u\n\r", 41);
	/* Provided the device has answered the SEND_IF_COND command, raise the
	 * Host Capacity Support flag. Also, set the SDXC Power Control flag.
	 * TODO assign XPC depending on board capabilities. */
	arg = *hc ? SD_OPC_HCS | SD_OPC_XPC : 0;
	/* Preparing UHS-I timing modes, ask the device whether it's in a
	 * position to switch to low signaling voltage. */
	arg |= *low_sig_lvl ? SD_OPC_S18R : 0;
	/* Tell the SD device which voltage the host supplies to the VDD line */
	arg |= vdd_range;

	do {
		rc = Cmd55(pSd, 0);
		if (rc != SDMMC_SUCCESS)
			break;
		_ResetCmd(pCmd);
		pCmd->bCmd = 41;
		pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(3);
		pCmd->dwArg = arg;
		pCmd->pResp = &ocr;
		rc = _SendCmd(pSd, NULL, NULL);
		if (rc != SDMMC_SUCCESS)
			break;
		/* Allow the device to be busy for up to 1s,
		 * which equals 1000 system ticks. */
		if (elapsed < 0) {
			timer_start_timeout(&timeout, 1000);
			elapsed = 0;
		}
		else if (timer_timeout_reached(&timeout))
			elapsed = 1;
	} while (!(ocr & SD_OCR_BUSYN) && !elapsed);

	if (!(ocr & SD_OCR_BUSYN) && rc == SDMMC_SUCCESS)
		/* Supply voltage range is incompatible */
		rc = SDMMC_ERROR_BUSY;
	if (rc != SDMMC_SUCCESS)
		trace_error("Acmd%u %s\n\r", 41, SD_StringifyRetCode(rc));
	else {
		/* Analyze the final contents of the OCR Register */
		trace_info("Device supports%s%s 3.0V:[%c%c%c%c%c%c]"
		    " 3.3V:[%c%c%c%c%c%c]\n\r",
		    ocr & SD_OCR_VDD_LOW ? " 1.xV" : "", "",
		    ocr & SD_OCR_VDD_27_28 ? 'X' : '.',
		    ocr & SD_OCR_VDD_28_29 ? 'X' : '.',
		    ocr & SD_OCR_VDD_29_30 ? 'X' : '.',
		    ocr & SD_OCR_VDD_30_31 ? 'X' : '.',
		    ocr & SD_OCR_VDD_31_32 ? 'X' : '.',
		    ocr & SD_OCR_VDD_32_33 ? 'X' : '.',
		    ocr & SD_OCR_VDD_30_31 ? 'X' : '.',
		    ocr & SD_OCR_VDD_31_32 ? 'X' : '.',
		    ocr & SD_OCR_VDD_32_33 ? 'X' : '.',
		    ocr & SD_OCR_VDD_33_34 ? 'X' : '.',
		    ocr & SD_OCR_VDD_34_35 ? 'X' : '.',
		    ocr & SD_OCR_VDD_35_36 ? 'X' : '.');
		/* Verify that arg[23:15] range fits within OCR[23:15] range */
		if ((ocr & vdd_range) != vdd_range)
			rc = SDMMC_ERROR_NOT_SUPPORT;
		if (*low_sig_lvl)
			*low_sig_lvl = ocr & SD_OCR_S18A ? true : false;
		*hc = ocr & SD_OCR_CCS ? true : false;
	}
	return rc;
}

/**
 * From the selected card get its SD CARD Configuration Register (SCR).
 * ACMD51 is valid under the Transfer state.
 * \param pSd  Pointer to a SD card driver instance.
 * \param pSCR  Pointer to an 8-byte buffer receiving the contents of the SCR.
 * The buffer shall follow the peripheral and DMA alignment requirements.
 * \param pResp  Pointer to where the response is returned.
 * \return The command transfer result (see SendCommand).
 */
static uint8_t
Acmd51(sSdCard * pSd, uint8_t * pSCR, uint32_t * pResp)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t error;

	assert(pSd);

	trace_debug("Acmd%u\n\r", 51);
	error = Cmd55(pSd, CARD_ADDR(pSd));
	if (error)
		goto End;
	_ResetCmd(pCmd);
	pCmd->bCmd = 51;
	pCmd->cmdOp.wVal = SDMMC_CMD_CDATARX(1);
	if (pSCR) {
		pCmd->wBlockSize = 64 / 8;
		pCmd->wNbBlocks = 1;
		pCmd->pData = pSCR;
	}
	pCmd->pResp = pResp;
	error = _SendCmd(pSd, NULL, NULL);

End:
	if (error)
		trace_error("Acmd%u %s\n\r", 51, SD_StringifyRetCode(error));
	return error;
}

#if 0
/**
 * Continue to transfer datablocks from card to host until interrupted by a
 * STOP_TRANSMISSION command.
 * \param pSd  Pointer to a SD card driver instance.
 * \param blockSize Block size (shall be set to 512 in case of high capacity).
 * \param nbBlock   Number of blocks to send.
 * \param pData     Pointer to the application buffer to be filled.
 * The buffer shall follow the peripheral and DMA alignment requirements.
 * \param fCallback Pointer to optional callback invoked on command end.
 *                  NULL:    Function return until command finished.
 *                  Pointer: Return immediately and invoke callback at end.
 * \param pArg Callback argument.
 */
static uint8_t
SdmmcRead(sSdCard * pSd,
	  uint16_t blockSize,
	  uint16_t nbBlock,
	  uint8_t * pData, fSdmmcCallback fCallback, void *pArg)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	trace_debug("Read()\n\r");
	_ResetCmd(pCmd);

	/* Fill command information */
	pCmd->cmdOp.wVal = SDMMC_CMD_DATARX;
	pCmd->wBlockSize = blockSize;
	pCmd->wNbBlocks = nbBlock;
	pCmd->pData = pData;

	/* Send command */
	bRc = _SendCmd(pSd, fCallback, pArg);
	return bRc;
}

/**
 * Continue to transfer datablocks from host to card until interrupted by a
 * STOP_TRANSMISSION command.
 * \param pSd  Pointer to a SD card driver instance.
 * \param blockSize Block size (shall be set to 512 in case of high capacity).
 * \param nbBlock   Number of blocks to send.
 * \param pData  Pointer to the application buffer to be filled.
 * The buffer shall follow the peripheral and DMA alignment requirements.
 * \param fCallback Pointer to optional callback invoked on command end.
 *                  NULL:    Function return until command finished.
 *                  Pointer: Return immediately and invoke callback at end.
 * \param pArg Callback argument.
 */
static uint8_t
SdmmcWrite(sSdCard * pSd,
	   uint16_t blockSize,
	   uint16_t nbBlock,
	   const uint8_t * pData, fSdmmcCallback fCallback, void *pArg)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	trace_debug("Write()\n\r");
	_ResetCmd(pCmd);

	/* Fill command information */
	pCmd->cmdOp.wVal = SDMMC_CMD_DATATX;
	pCmd->wBlockSize = blockSize;
	pCmd->wNbBlocks = nbBlock;
	pCmd->pData = (uint8_t *) pData;

	/* Send command */
	bRc = _SendCmd(pSd, fCallback, pArg);
	return bRc;
}
#endif

/**
 * Stop TX/RX
 */
static uint8_t
_StopCmd(sSdCard * pSd)
{
	uint32_t status, state = STATUS_RCV;
	uint32_t i;
	uint8_t err, count;
	/* When stopping a write operation, allow retrying several times */
	for (i = 0; i < 9 && state == STATUS_RCV; i++) {
		err = Cmd12(pSd, &status);
		if (err)
			return err;
		/* TODO handle any exception, raised in status; report that
		 * the data transfer has failed. */

		/* Wait until ready. Allow 30 ms. */
		for (count = 0; count < 6; count++) {
			/* Wait for about 5 ms - which equals 5 system ticks */
			msleep(5);
			err = Cmd13(pSd, &status);
			if (err)
				return err;
			state = status & STATUS_STATE;

			/* Invalid state */
			if (state == STATUS_IDLE || state == STATUS_READY
			    || state == STATUS_IDENT || state == STATUS_STBY
			    || state == STATUS_DIS)
				return SDMMC_ERROR_NOT_INITIALIZED;

			/* Ready? */
			if ((status & STATUS_READY_FOR_DATA) ==
			    STATUS_READY_FOR_DATA && state == STATUS_TRAN)
				return SDMMC_SUCCESS;
		}
	}
	return SDMMC_ERROR_STATE;
}

static uint8_t
_WaitUntilReady(sSdCard * pSd, uint32_t last_dev_status)
{
	uint32_t state, status = last_dev_status;
	uint8_t err, count;

	for (count = 0; count < 51; count++) {
		state = status & STATUS_STATE;
		if (state == STATUS_TRAN && status & STATUS_READY_FOR_DATA)
			return SDMMC_SUCCESS;
		/* Sending-data and Receive-data states may be encountered
		 * temporarily further to single-block data transfers. */
		/* FIXME state 15 "reserved for I/O mode" may be allowed */
		if (state != STATUS_TRAN && state != STATUS_PRG
		    && state != STATUS_DATA && state != STATUS_RCV)
			return SDMMC_ERROR_NOT_INITIALIZED;
		/* Wait for about 10 ms - which equals 10 system ticks */
		msleep(10);
		err = Cmd13(pSd, &status);
		if (err)
			return err;
	}
	return SDMMC_ERROR_BUSY;
}

/**
 * Transfer a single data block.
 * The device shall be in its Transfer State already.
 * \param pSd      Pointer to a SD card driver instance.
 * \param address  Address of the block to transfer.
 * \param pData    Data buffer, whose size is at least one block size.
 * \param isRead   Either 1 to read data from the device or 0 to write data.
 * \return a \ref sdmmc_rc result code.
 */
static uint8_t
PerformSingleTransfer(sSdCard * pSd,
		      uint32_t address, uint8_t * pData, uint8_t isRead)
{
	uint8_t result = SDMMC_OK, error;
	uint32_t sdmmc_address, status;

	/* Convert block address into device-expected unit */
	if (pSd->bCardType & CARD_TYPE_bmHC)
		sdmmc_address = address;
	else if (address <= 0xfffffffful / pSd->wCurrBlockLen)
		sdmmc_address = address * pSd->wCurrBlockLen;
	else
		return SDMMC_PARAM;
	if (isRead)
		/* Read a single data block */
		error = Cmd17(pSd, pData, sdmmc_address, &status, NULL);
	else
		/* Write a single data block */
		error = Cmd24(pSd, pData, sdmmc_address, &status, NULL);
	if (!error) {
		status = status & (isRead ? STATUS_READ : STATUS_WRITE)
		    & ~STATUS_READY_FOR_DATA & ~STATUS_STATE;
		if (status) {
			trace_error("st %lx\n\r", status);
			error = SDMMC_ERROR;
		}
	}
	if (error) {
		trace_error("Cmd%u(0x%lx) %s\n\r", isRead ? 17 : 24,
		    sdmmc_address, SD_StringifyRetCode(error));
		result = error;
		error = Cmd13(pSd, &status);
		if (error) {
			pSd->bStatus = error;
			return result;
		}
		error = _WaitUntilReady(pSd, status);
		if (error) {
			pSd->bStatus = error;
			return result;
		}
	}
	return result;
}

/**
 * Move SD card to transfer state. The buffer size must be at
 * least 512 byte long. This function checks the SD card status register and
 * address the card if required before sending the transfer command.
 * Returns 0 if successful; otherwise returns an code describing the error.
 * \param pSd      Pointer to a SD card driver instance.
 * \param address  Address of the block to transfer.
 * \param nbBlocks Pointer to count of blocks to transfer. Pointer to 0
 * for infinite transfer. Upon return, points to the count of blocks actually
 * transferred.
 * \param pData    Data buffer whose size is at least the block size.
 * \param isRead   1 for read data and 0 for write data.
 */
static uint8_t
MoveToTransferState(sSdCard * pSd,
		    uint32_t address,
		    uint16_t * nbBlocks, uint8_t * pData, uint8_t isRead)
{
	uint8_t result = SDMMC_OK, error;
	uint32_t sdmmc_address, state, status;

	assert(pSd != NULL);
	assert(nbBlocks != NULL);

	/* Convert block address into device-expected unit */
	if (pSd->bCardType & CARD_TYPE_bmHC)
		sdmmc_address = address;
	else if (address <= 0xfffffffful / pSd->wCurrBlockLen)
		sdmmc_address = address * pSd->wCurrBlockLen;
	else
		return SDMMC_PARAM;
	if (pSd->bSetBlkCnt) {
		error = Cmd23(pSd, 0, *nbBlocks, &status);
		if (error)
			return error;
	}
	if (isRead)
		/* Move to Receiving data state */
		error = Cmd18(pSd, nbBlocks, pData, sdmmc_address, &status,
		    NULL);
	else
		/* Move to Sending data state */
		error = Cmd25(pSd, nbBlocks, pData, sdmmc_address, &status,
		    NULL);
	if (error == SDMMC_CHANGED)
		error = SDMMC_OK;
	if (!error) {
		status = status & (isRead ? STATUS_READ : STATUS_WRITE)
		    & ~STATUS_READY_FOR_DATA & ~STATUS_STATE;

		if (pSd->bStopMultXfer)
			error = _StopCmd(pSd);

		if (status) {
			trace_error("st %lx\n\r", status);
			/* TODO ignore STATUS_ADDR_OUT_OR_RANGE if the read
			 * operation is for the last block of memory area. */
			error = SDMMC_ERROR;
		}
		/* FIXME when not using the STOP_TRANSMISSION command (using the
		 * SET_BLOCK_COUNT command instead), we should issue the
		 * SEND_STATUS command, eat and handle any Execution Mode
		 * exception. */
	}
	if (error) {
		trace_error("Cmd%u(0x%lx, %u) %s\n\r", isRead ? 18 : 25,
		    sdmmc_address, *nbBlocks, SD_StringifyRetCode(error));
		result = error;
		error = Cmd13(pSd, &status);
		if (error) {
			pSd->bStatus = error;
			return result;
		}
		state = status & STATUS_STATE;
		if (state == STATUS_DATA || state == STATUS_RCV) {
			error = Cmd12(pSd, &status);
			if (error == SDMMC_OK) {
				trace_debug("st %lx\n\r", status);
				if (status & (STATUS_ERASE_SEQ_ERROR
				    | STATUS_ERASE_PARAM | STATUS_UN_LOCK_FAILED
				    | STATUS_ILLEGAL_COMMAND
				    | STATUS_CIDCSD_OVERWRITE
				    | STATUS_ERASE_RESET | STATUS_SWITCH_ERROR))
					result = SDMMC_STATE;
				else if (status & (STATUS_COM_CRC_ERROR
				    | STATUS_CARD_ECC_FAILED | STATUS_ERROR))
					result = SDMMC_ERR_IO;
				else if (status & (STATUS_ADDR_OUT_OR_RANGE
				    | STATUS_ADDRESS_MISALIGN
				    | STATUS_BLOCK_LEN_ERROR
				    | STATUS_WP_VIOLATION
				    | STATUS_WP_ERASE_SKIP))
					result = SDMMC_PARAM;
				else if (status & STATUS_CC_ERROR)
					result = SDMMC_ERR;
			}
			else if (error == SDMMC_ERROR_NORESPONSE)
				error = Cmd13(pSd, &status);
			if (error) {
				pSd->bStatus = error;
				return result;
			}
		}
		error = _WaitUntilReady(pSd, status);
		if (error) {
			pSd->bStatus = error;
			return result;
		}
	}
	return result;
}

/**
 * Switch card state between STBY and TRAN (or CMD and TRAN)
 * \param pSd       Pointer to a SD card driver instance.
 * \param address   Card address to TRAN, 0 to STBY
 * \param statCheck Whether to check the status before CMD7.
 */
static uint8_t
SdMmcSelect(sSdCard * pSd, uint16_t address, uint8_t statCheck)
{
	uint8_t error;
	uint32_t status, currState;
	uint32_t targetState = address ? STATUS_TRAN : STATUS_STBY;
	uint32_t srcState = address ? STATUS_STBY : STATUS_TRAN;

	/* At this stage the Initialization and identification process is achieved
	 * The SD card is supposed to be in Stand-by State */
	while (statCheck) {
		error = Cmd13(pSd, &status);
		if (error)
			return error;
		if (status & STATUS_READY_FOR_DATA) {
			currState = status & STATUS_STATE;
			if (currState == targetState)
				return 0;
			if (currState != srcState) {
				trace_error("st %lx\n\r", currState);
				return SDMMC_ERROR;
			}
			break;
		}
	}

	/* Switch to Transfer state. Select the current SD/MMC
	 * so that SD ACMD6 can process or EXT_CSD can read. */
	error = Cmd7(pSd, address);
	return error;
}

/**
 * Get MMC EXT_CSD information
 * \param pSd      Pointer to a SD card driver instance.
 */
#ifndef SDMMC_TRIM_MMC
static uint8_t
MmcGetExtInformation(sSdCard * pSd)
{
	/* MMC 4.0 Higher version */
	if (SD_CSD_STRUCTURE(pSd->CSD) >= 2 && MMC_IsVer4(pSd))
		return MmcCmd8(pSd, pSd->EXT);
	else
		return SDMMC_NOT_SUPPORTED;
}
#endif

/**
 * Retrieve the maximum clock frequency supported by the SD/MMC memory device,
 * in the current timing mode.
 * \param pSd Pointer to a SD card driver instance.
 * \return Frequency in Hz.
 */
static uint32_t
SdmmcGetMaxFreq(sSdCard * pSd)
{
	uint32_t rate = 0;

#ifndef SDMMC_TRIM_MMC
	if ((pSd->bCardType & CARD_TYPE_bmSDMMC) == CARD_TYPE_bmMMC) {
		if (pSd->bSpeedMode == SDMMC_TIM_MMC_HS200)
			rate = 200000ul;
		else if (pSd->bSpeedMode == SDMMC_TIM_MMC_HS_DDR
		    || (pSd->bSpeedMode == SDMMC_TIM_MMC_HS_SDR
		    && MMC_EXT_CARD_TYPE(pSd->EXT) & 0x2))
			rate = 52000ul;
		else if (pSd->bSpeedMode == SDMMC_TIM_MMC_HS_SDR)
			rate = 26000ul;
		else
			rate = SdmmcDecodeTransSpeed(SD_CSD_TRAN_SPEED(pSd->CSD),
			    sdmmcTransUnits, mmcTransMultipliers);
	}
#endif

	if ((pSd->bCardType & CARD_TYPE_bmSDMMC) == CARD_TYPE_bmSD) {
		rate = SdmmcDecodeTransSpeed(SD_CSD_TRAN_SPEED(pSd->CSD),
		    sdmmcTransUnits, sdTransMultipliers);
		if (pSd->bSpeedMode == SDMMC_TIM_SD_SDR104 && rate == 200000ul)
			rate = 208000ul;
		else if (pSd->bSpeedMode == SDMMC_TIM_SD_DDR50)
			rate /= 2ul;
	}

	return rate * 1000ul;
}

/**
 * Retrieve the maximum clock frequency supported by the SDIO device, in the
 * current timing mode.
 * \param pSd Pointer to a SD card driver instance.
 * \return Frequency in Hz.
 */
#ifndef SDMMC_TRIM_SDIO
static uint32_t
SdioGetMaxFreq(sSdCard * pSd)
{
	uint8_t error;
	uint32_t addr = 0, rate;
	uint8_t buf[6];

	/* Check Func0 tuple in CIS area */
	error = SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_CIS_PTR_REG,
	    (uint8_t *)&addr, 3);
	if (error)
		return 0;
	error = SdioFindTuples(pSd, addr, 256, NULL, &addr);
	if (error || !addr)
		return 0;
	/* Fun0 tuple: fn0_blk_siz & max_tran_speed */
	error = SDIO_ReadDirect(pSd, SDIO_CIA, addr, buf, 6);
	if (error)
		return 0;
	rate = SdmmcDecodeTransSpeed(buf[5], sdmmcTransUnits,
	    sdTransMultipliers);
	if (pSd->bSpeedMode == SDMMC_TIM_SD_SDR104 && rate == 200000ul)
		rate = 208000ul;
	else if (pSd->bSpeedMode == SDMMC_TIM_SD_DDR50)
		rate /= 2ul;
	else if (pSd->bSpeedMode == SDMMC_TIM_SD_HS && rate == 25000ul)
		rate *= 2ul;
	return rate * 1000ul;
}
#endif

/**
 * Get SCR and SD Status information
 * \param pSd      Pointer to a SD card driver instance.
 */
static void
SdGetExtInformation(sSdCard * pSd)
{
	uint32_t card_status;
	uint8_t error;

	error = Acmd51(pSd, pSd->SCR, &card_status);
	if (error == SDMMC_OK) {
		card_status &= ~STATUS_READY_FOR_DATA;
		if (card_status != (STATUS_APP_CMD | STATUS_TRAN))
			trace_error("SCR st %lx\n\r", card_status);
	}

	error = Acmd13(pSd, pSd->SSR, &card_status);
	if (error == SDMMC_OK) {
		card_status &= ~STATUS_READY_FOR_DATA;
		if (card_status != (STATUS_APP_CMD | STATUS_TRAN))
			trace_error("SSR st %lx\n\r", card_status);
	}
}

/**
 * Update SD/MMC information.
 * Update CSD for card speed switch.
 * Update ExtDATA for any card function switch.
 * \param pSd      Pointer to a SD card driver instance.
 * \return error code when update CSD error.
 */
static void
SdMmcUpdateInformation(sSdCard * pSd, bool csd, bool extData)
{
	uint8_t error;

	/* Update CSD for new TRAN_SPEED value */
	if (csd) {
		SdMmcSelect(pSd, 0, 1);
		/* Wait for 14 usec (or more) */
		usleep(20);

		error = Cmd9(pSd);
		if (error)
			return;
		SdMmcSelect(pSd, pSd->wAddress, 1);
	}
	if (extData) {
		if ((pSd->bCardType & CARD_TYPE_bmSDMMC) == CARD_TYPE_bmSD)
			SdGetExtInformation(pSd);
#ifndef SDMMC_TRIM_MMC
		else if ((pSd->bCardType & CARD_TYPE_bmSDMMC) == CARD_TYPE_bmMMC)
			MmcGetExtInformation(pSd);
#endif
	}
}

static void
SdSelectSlowerTiming(bool high_sig, uint8_t * mode)
{
	if (high_sig)
		*mode = SDMMC_TIM_SD_DS;
	else if (*mode > SDMMC_TIM_SD_SDR50)
		*mode = SDMMC_TIM_SD_SDR50;
	else if (*mode > SDMMC_TIM_SD_SDR25)
		*mode = SDMMC_TIM_SD_SDR25;
	else
		*mode = SDMMC_TIM_SD_SDR12;
}

static uint8_t
SdGetTimingFunction(uint8_t mode) {
	if (mode == SDMMC_TIM_SD_SDR104)
		return SD_SWITCH_ST_ACC_SDR104;
	else if (mode == SDMMC_TIM_SD_DDR50)
		return SD_SWITCH_ST_ACC_DDR50;
	else if (mode == SDMMC_TIM_SD_SDR50)
		return SD_SWITCH_ST_ACC_SDR50;
	else if (mode == SDMMC_TIM_SD_HS || mode == SDMMC_TIM_SD_SDR25)
		return SD_SWITCH_ST_ACC_HS;
	else
		return SD_SWITCH_ST_ACC_DS;
}

/**
 * \brief Negotiate and enable the fastest timing mode, among the ones that are
 * supported by both the slot and the device.
 * \param pSd Pointer to sSdCard instance.
 * \return A \ref sdmmc_rc result code.
 * \note Specifically, SDMMC_ERROR_STATE reports that the current host and
 * device signaling levels do not match.
 */
static uint8_t
SdEnableHighSpeed(sSdCard * pSd)
{
	SdCmd6Arg request = {
		.acc_mode	= 0xf,
		.cmd_sys	= 0xf,
		.drv_strgth	= 0xf,
		.pwr_limit	= 0xf,
		.func_grp5	= 0xf,
		.func_grp6	= 0xf,
		.set		= 0,
	};
	uint32_t status;
	uint16_t mode_mask, val;
	uint8_t mode = pSd->bCardSigLevel ? SDMMC_TIM_SD_DS : SDMMC_TIM_SD_SDR12;
	uint8_t error, mode_func, pwr_func = SD_SWITCH_ST_MAX_PWR_1_44W;
	const bool has_io = pSd->bCardType & CARD_TYPE_bmSDIO ? true : false;
	const bool has_mem = pSd->bCardType & CARD_TYPE_bmSD ? true : false;
	const bool has_switch = SD_CSD_CCC(pSd->CSD) & 1 << 10 ? true : false;
	bool sfs_v1 = false;

	assert(sizeof(pSd->sandbox1) >= 512 / 8);

#ifndef SDMMC_TRIM_SDIO
	/* TODO consider the UHS-I timing modes for SDIO devices too */
	if (has_io && !(has_mem && !has_switch)
	    && _HwIsTimingSupported(pSd, SDMMC_TIM_SD_HS)) {
		/* Check CIA.HS */
		status = 0;
		error = Cmd52(pSd, 0, SDIO_CIA, 0, SDIO_HS_REG, &status);
		if (error)
			return SDMMC_ERROR;
		if (status & SDIO_SHS) {
			/* Enable High Speed timing mode */
			status = SDIO_EHS;
			error = Cmd52(pSd, 1, SDIO_CIA, 1, SDIO_HS_REG,
			    &status);
			if (error || !(status & SDIO_EHS))
				return SDMMC_ERROR;
			mode = SDMMC_TIM_SD_HS;
		}
	}
#endif

	if (!has_mem || !has_switch)
		goto Apply;
	/* Search for the fastest supported timing mode */
	error = SdCmd6(pSd, &request, pSd->sandbox1, &status);
	if (error || status & STATUS_SWITCH_ERROR)
		return SDMMC_ERROR;
	sfs_v1 = SD_SWITCH_ST_DATA_STRUCT_VER(pSd->sandbox1) >= 0x01;
	mode_mask = SD_SWITCH_ST_FUN_GRP1_INFO(pSd->sandbox1);
	trace_debug("Device timing functions: 0x%04x\n\r", mode_mask);
	if (has_io && mode == SDMMC_TIM_SD_HS
	    && !(mode_mask & 1 << SD_SWITCH_ST_ACC_HS))
		return SDMMC_ERROR_NOT_SUPPORT;
	else if (has_io) {
		/* Have SDMEM use the same timing mode as SDIO */
	} else if (mode_mask & 1 << SD_SWITCH_ST_ACC_SDR104
	    && _HwIsTimingSupported(pSd, SDMMC_TIM_SD_SDR104))
		mode = SDMMC_TIM_SD_SDR104;
	else if (mode_mask & 1 << SD_SWITCH_ST_ACC_DDR50
	    && _HwIsTimingSupported(pSd, SDMMC_TIM_SD_DDR50))
		mode = SDMMC_TIM_SD_DDR50;
	else if (mode_mask & 1 << SD_SWITCH_ST_ACC_SDR50
	    && _HwIsTimingSupported(pSd, SDMMC_TIM_SD_SDR50))
		mode = SDMMC_TIM_SD_SDR50;
	else if (mode_mask & 1 << SD_SWITCH_ST_ACC_HS
	    && _HwIsTimingSupported(pSd, SDMMC_TIM_SD_HS))
		mode = SDMMC_TIM_SD_HS;
	else
		mode = SDMMC_TIM_SD_DS;
	/* Verify current signaling level is the one expected by the device */
	if ((mode >= SDMMC_TIM_SD_SDR50 && pSd->bCardSigLevel != 0)
	    || (mode < SDMMC_TIM_SD_SDR50 && pSd->bCardSigLevel == 0))
		return SDMMC_ERROR_STATE;
	/* Check the electrical power requirements of this device */
	val = SD_SWITCH_ST_FUN_GRP4_INFO(pSd->sandbox1);
	trace_debug("Device pwr & strength functions: 0x%04x & 0x%04x\n\r", val,
	    SD_SWITCH_ST_FUN_GRP3_INFO(pSd->sandbox1));
	if (!(val & 1 << SD_SWITCH_ST_MAX_PWR_1_44W))
		pwr_func = SD_SWITCH_ST_MAX_PWR_0_72W;
	request.acc_mode = mode_func = SdGetTimingFunction(mode);
	request.drv_strgth = SD_SWITCH_ST_OUT_DRV_B;
	request.pwr_limit = SD_SWITCH_ST_MAX_PWR_0_72W;
	error = SdCmd6(pSd, &request, pSd->sandbox1, &status);
	if (error || status & STATUS_SWITCH_ERROR)
		return SDMMC_ERROR;
	val = SD_SWITCH_ST_MAX_CURR_CONSUMPTION(pSd->sandbox1);
	trace_info("Device max current: %u mA\n\r", val);
	if (val == 0 || val > (1440 * 10) / 36)
		SdSelectSlowerTiming(pSd->bCardSigLevel != 0, &mode);
	else if (sfs_v1) {
		val = SD_SWITCH_ST_FUN_GRP4_BUSY(pSd->sandbox1);
		if (val & 1 << SD_SWITCH_ST_MAX_PWR_1_44W)
			pwr_func = SD_SWITCH_ST_MAX_PWR_0_72W;
		val = SD_SWITCH_ST_FUN_GRP1_BUSY(pSd->sandbox1);
		if (val & 1 << mode_func)
			SdSelectSlowerTiming(pSd->bCardSigLevel != 0, &mode);
	}

	/* Select device output Driver Type B, i.e. 50 ohm nominal output
	 * impedance.
	 * FIXME select the optimal device output Driver Type, which depends on
	 * board design. An oscilloscope should be used to observe signal
	 * integrity, then among the driver types that meet rise and fall time
	 * requirements, the weakest should be selected.
	 */
	request.acc_mode = 0xf;
	request.pwr_limit = 0xf;
	request.set = 1;
	error = SdCmd6(pSd, &request, pSd->sandbox1, &status);
	if (error || status & STATUS_SWITCH_ERROR)
		return SDMMC_ERROR;
	val = SD_SWITCH_ST_FUN_GRP3_RC(pSd->sandbox1);
	if (val != request.drv_strgth)
		SdSelectSlowerTiming(pSd->bCardSigLevel != 0, &mode);

Switch:
	/* Now switch the memory device to the candidating mode */
	request.acc_mode = mode_func = SdGetTimingFunction(mode);
	request.cmd_sys = 0x0;
	request.drv_strgth = 0xf;
	request.pwr_limit = pwr_func;
	error = SdCmd6(pSd, &request, pSd->sandbox1, &status);
	if (error || status & STATUS_SWITCH_ERROR)
		return SDMMC_ERROR;
	val = SD_SWITCH_ST_FUN_GRP1_RC(pSd->sandbox1);
	while (val != mode_func && val != SD_SWITCH_ST_FUN_GRP_RC_ERROR) {
		/* FIXME break upon timeout condition */
		request.acc_mode = 0xf;
		request.cmd_sys = 0xf;
		request.pwr_limit = 0xf;
		request.set = 0;
		error = SdCmd6(pSd, &request, pSd->sandbox1, &status);
		if (error || status & STATUS_SWITCH_ERROR)
			return SDMMC_ERROR;
		val = SD_SWITCH_ST_FUN_GRP1_RC(pSd->sandbox1);
		if (val != mode_func && sfs_v1
		    && !(SD_SWITCH_ST_FUN_GRP1_BUSY(pSd->sandbox1)
		    & 1 << mode_func))
			break;
	}
	if (val != mode_func
	    && (mode == SDMMC_TIM_SD_DS || mode == SDMMC_TIM_SD_SDR12))
		return SDMMC_ERROR;
	else if (val != mode_func) {
		SdSelectSlowerTiming(pSd->bCardSigLevel != 0, &mode);
		goto Switch;
	}
	val = SD_SWITCH_ST_FUN_GRP4_RC(pSd->sandbox1);
	if (val != pwr_func)
		trace_warning("Device power limit 0x%x\n\r", val);

Apply:
	error = _HwSetHsMode(pSd, mode);
	if (error == SDMMC_OK)
		pSd->bSpeedMode = mode;
	else
		return SDMMC_ERROR;
	return SDMMC_OK;
}

#ifndef SDMMC_TRIM_MMC
static uint8_t
mmcSelectBuswidth(sSdCard * pSd, uint8_t busWidth, bool ddr)
{
	uint8_t error;
	uint32_t status;
	MmcCmd6Arg cmd6Arg = {
		.access = 0x3,   /* Write byte in the EXT_CSD register */
		.index = MMC_EXT_BUS_WIDTH_I,   /* Target byte in EXT_CSD */
		.value = MMC_EXT_BUS_WIDTH_1BIT,   /* Byte value */
	};

	if (busWidth == 8)
		cmd6Arg.value = MMC_EXT_BUS_WIDTH_8BITS
		    | (ddr ? MMC_EXT_BUS_WIDTH_DDR : 0);
	else if (busWidth == 4)
		cmd6Arg.value = MMC_EXT_BUS_WIDTH_4BITS
		    | (ddr ? MMC_EXT_BUS_WIDTH_DDR : 0);
	else if (busWidth != 1)
		return SDMMC_ERROR_PARAM;
	error = MmcCmd6(pSd, &cmd6Arg, &status);
	if (error)
		return SDMMC_ERROR;
	else if (status & STATUS_MMC_SWITCH)
		return SDMMC_ERROR_NOT_SUPPORT;
	return SDMMC_OK;
}

static uint8_t
mmcDetectBuswidth(sSdCard * pSd)
{
	uint8_t error, busWidth, mask = 0xff, i, len;

	assert(sizeof(pSd->sandbox1) >= 8);
	assert(sizeof(pSd->sandbox2) >= 8);

	memset(pSd->sandbox1, 0, 8);
	for (busWidth = 8; busWidth != 0; busWidth /= busWidth == 8 ? 2 : 4) {
		error = _HwSetBusWidth(pSd, busWidth);
		if (error)
			continue;
		switch (busWidth) {
		case 8:
			pSd->sandbox1[0] = 0x55;
			pSd->sandbox1[1] = 0xaa;
			break;
		case 4:
			pSd->sandbox1[0] = 0x5a;
			pSd->sandbox1[1] = 0;
			break;
		case 1:
			pSd->sandbox1[0] = 0x80;
			pSd->sandbox1[1] = 0;
			break;
		}
		len = (uint8_t)max_u32(busWidth, 2);
		error = Cmd19(pSd, pSd->sandbox1, len, NULL);
		if (error) {
			/* Devices which do not respond to CMD19 - which results
			 * in the driver returning SDMMC_ERROR_NORESPONSE -
			 * simply do not support the bus test procedure.
			 * When the device responds to CMD19, mind the
			 * difference with other data write commands: further
			 * to host data, the device does not emit the CRC status
			 * token. Typically the peripheral reports the anomaly,
			 * and the driver is likely to return SDMMC_ERR_IO. */
			if (error != SDMMC_ERR_IO)
				return 0;
		}
		error = Cmd14(pSd, pSd->sandbox2, busWidth, NULL);
		if (error)
			continue;
		if (busWidth == 1) {
			mask = 0xc0;
			pSd->sandbox2[0] &= mask;
		}
		len = busWidth == 8 ? 2 : 1;
		for (i = 0; i < len; i++) {
			if ((pSd->sandbox1[i] ^ pSd->sandbox2[i]) != mask)
				break;
		}
		if (i == len)
			break;
	}
	return busWidth;
}
#endif

/**
 * \brief Check bus width capability and enable it
 */
static uint8_t
SdDecideBuswidth(sSdCard * pSd)
{
	uint8_t error, busWidth = 1;
	const uint8_t sd = (pSd->bCardType & CARD_TYPE_bmSDMMC)
	    == CARD_TYPE_bmSD;
	const uint8_t io = (pSd->bCardType & CARD_TYPE_bmSDIO) != 0;

	if (io)
		busWidth = 1;   /* SDIO => 1 bit only. TODO: assign CCCR. */
	else if (sd) {
		busWidth = 4;   /* default to 4-bit mode */
		error = _HwSetBusWidth(pSd, busWidth);
		if (error)
			busWidth = 1;
	}
	/* Switch to selected bus mode */
	if (sd && busWidth > 1)
		error = Acmd6(pSd, busWidth);
	else
		error = _HwSetBusWidth(pSd, busWidth);
	if (error)
		return error;
	pSd->bBusMode = busWidth;
	return 0;
}

/**
 * \brief Run the SD/MMC/SDIO Mode initialization sequence.
 * This function runs the initialization procedure and the identification
 * process. Then it leaves the card in ready state. The following procedure must
 * check the card type and continue to put the card into tran(for memory card)
 * or cmd(for io card) state for data exchange.
 * \param pSd  Pointer to a SD card driver instance.
 * \return 0 if successful; otherwise returns an \ref sdmmc_rc "SD_ERROR code".
 */
static uint8_t
SdMmcIdentify(sSdCard * pSd)
{
	uint8_t error, dev_type = CARD_UNKNOWN;
	bool sd_v2 = false, high_capacity;

#ifndef SDMMC_TRIM_SDIO
	/* Reset SDIO: CMD52, write 1 to RES bit in CCCR */
	{
		uint32_t status = SDIO_RES;

		error = Cmd52(pSd, 1, SDIO_CIA, 0, SDIO_IOA_REG, &status);
		if ((error && error != SDMMC_ERROR_NORESPONSE)
		    || (!error && status & STATUS_SDIO_R5))
			trace_error("IOrst %s st %lx\n\r",
			    SD_StringifyRetCode(error), status);
	}
#endif

	/* Reset MEM: CMD0 */
	error = Cmd0(pSd, 0);
	if (error)
		trace_debug("rst %s\n\r", SD_StringifyRetCode(error));

	/* CMD8 is newly added in the Physical Layer Specification Version 2.00 to
	 * support multiple voltage ranges and used to check whether the card
	 * supports supplied voltage. The version 2.00 host shall issue CMD8 and
	 * verify voltage before card initialization.
	 * The host that does not support CMD8 shall supply high voltage range... */
	error = SdCmd8(pSd, SD_IFC_VHS_27_36 >> SD_IFC_VHS_Pos);
	if (!error)
		sd_v2 = true;
	else if (error != SDMMC_ERROR_NORESPONSE)
		return SDMMC_ERROR;
	else {
		/* No response to CMD8. Wait for 130 usec (or more). */
		usleep(130);
	}

#ifndef SDMMC_TRIM_SDIO
	/* CMD5 is newly added for SDIO initialize & power on */
	{
		uint32_t status = 0;

		error = Cmd5(pSd, &status);
		if (!error && (status & SDIO_OCR_NF) > 0) {
			struct _timeout timeout;
			int8_t elapsed;

			/* Card has SDIO function. Wait until it raises the
			 * IORDY flag, which may take up to 1s, i.e. 1000 system
			 * ticks. */
			timer_start_timeout(&timeout, 1000);
			for (elapsed = 0;
			    !(status & SD_OCR_BUSYN) && !error && !elapsed; ) {
				if (timer_timeout_reached(&timeout))
					elapsed = 1;
				status &= SD_HOST_VOLTAGE_RANGE;
				error = Cmd5(pSd, &status);
			}
			if (!(status & SD_OCR_BUSYN) && !error)
				error = SDMMC_ERROR_BUSY;
			if (error) {
				trace_error("SDIO oc %s\n\r",
				    SD_StringifyRetCode(error));
				return SDMMC_ERROR;
			}
			trace_info("SDIO\n\r");
			dev_type = status & SDIO_OCR_MP
			    ? CARD_SDCOMBO : CARD_SDIO;
		}
	}
#endif

	if (dev_type != CARD_SDIO) {
		/* The device should have memory (MMC or SD or COMBO).
		 * Try to initialize SD memory. */
		bool low_sig_lvl =
		    _HwIsTimingSupported(pSd, SDMMC_TIM_SD_SDR12);

		high_capacity = sd_v2;
		error = Acmd41(pSd, &low_sig_lvl, &high_capacity);
		if (!error) {
			trace_info("SD%s MEM\n\r", high_capacity ? "HC" : "");
			dev_type |= high_capacity ? CARD_SDHC : CARD_SD;
			if (pSd->bCardSigLevel == 2 && low_sig_lvl)
				pSd->bCardSigLevel = 1;
		}
		else if (dev_type == CARD_SDCOMBO)
			dev_type = CARD_SDIO;
	}

#ifndef SDMMC_TRIM_MMC
	if (dev_type == CARD_UNKNOWN) {
		/* Try MMC initialize */
		uint8_t count;

		for (error = SDMMC_ERROR_NORESPONSE, count = 0;
		    error == SDMMC_ERROR_NORESPONSE && count < 10;
		    count++)
			error = Cmd0(pSd, 0);
		if (error) {
			trace_error("MMC rst %s\n\r",
			    SD_StringifyRetCode(error));
			return SDMMC_ERROR;
		}
		high_capacity = false;
		error = Cmd1(pSd, &high_capacity);
		if (error) {
			trace_error("MMC oc %s\n\r",
			    SD_StringifyRetCode(error));
			return SDMMC_ERROR;
		}
		/* MMC card identification OK */
		trace_info("MMC\n\r");
		dev_type = high_capacity ? CARD_MMCHD : CARD_MMC;
	}
#endif

	if (dev_type == CARD_UNKNOWN) {
		trace_error("Unknown card\n\r");
		return SDMMC_ERROR;
	}
	pSd->bCardType = dev_type;
	return 0;
}

#ifndef SDMMC_TRIM_MMC
static uint8_t
MmcInit(sSdCard * pSd)
{
	MmcCmd6Arg sw_arg = {
		.access = 0x3,   /* Write byte in the EXT_CSD register */
	};
	uint64_t mem_size;
	uint32_t freq, drv_param, drv_err, status;
	uint8_t error, tim_mode, pwr_class, width;
	bool flag;

	tim_mode = pSd->bSpeedMode = SDMMC_TIM_MMC_BC;
	/* The host then issues the command ALL_SEND_CID (CMD2) to the card to get
	 * its unique card identification (CID) number.
	 * Card that is unidentified (i.e. which is in Ready State) sends its CID
	 * number as the response (on the CMD line). */
	error = Cmd2(pSd);
	if (error)
		return error;

	/* Thereafter, the host issues SET_RELATIVE_ADDR (CMD3) to assign the
	 * device a dedicated relative card address (RCA), which is shorter than
	 * CID and which is used to address the card in the future data transfer
	 * mode. Once the RCA is received the card state changes to the Stand-by
	 * State. */
	error = Cmd3(pSd);
	if (error)
		return error;
	else
		trace_debug("RCA=%u\n\r", CARD_ADDR(pSd));

	/* SEND_CSD (CMD9) to obtain the Card Specific Data (CSD register),
	 * e.g. block length, card storage capacity, etc... */
	error = Cmd9(pSd);
	if (error)
		return error;

	/* Calculate transfer speed */
	freq = SdmmcGetMaxFreq(pSd);
	error = _HwSetClock(pSd, &freq);
	if (error != SDMMC_SUCCESS && error != SDMMC_CHANGED)
		return error;
	pSd->dwCurrSpeed = freq;

	/* Now select the card, to TRAN state */
	error = SdMmcSelect(pSd, CARD_ADDR(pSd), 0);
	if (error)
		return error;

	/* If CSD:SPEC_VERS indicates v4.0 or higher, read EXT_CSD */
	error = MmcGetExtInformation(pSd);
	/* Consider HS200 timing mode */
	if (error == SDMMC_OK && MMC_EXT_EXT_CSD_REV(pSd->EXT) >= 6
	    && MMC_IsCSDVer1_2(pSd) && MMC_EXT_CARD_TYPE(pSd->EXT) & 0x10
	    && _HwIsTimingSupported(pSd, SDMMC_TIM_MMC_HS200))
		tim_mode = SDMMC_TIM_MMC_HS200;
	/* Consider High Speed DDR timing mode */
	else if (error == SDMMC_OK && MMC_EXT_EXT_CSD_REV(pSd->EXT) >= 4
	    && MMC_IsCSDVer1_2(pSd) && MMC_EXT_CARD_TYPE(pSd->EXT) & 0x4
	    && _HwIsTimingSupported(pSd, SDMMC_TIM_MMC_HS_DDR))
		tim_mode = SDMMC_TIM_MMC_HS_DDR;
	/* Consider High Speed SDR timing mode */
	else if (error == SDMMC_OK
	    && MMC_IsCSDVer1_2(pSd) && MMC_EXT_CARD_TYPE(pSd->EXT) & 0x1
	    && _HwIsTimingSupported(pSd, SDMMC_TIM_MMC_HS_SDR))
		tim_mode = SDMMC_TIM_MMC_HS_SDR;
	/* Check power requirements of the device */
	if (error == SDMMC_OK) {
		if (tim_mode == SDMMC_TIM_MMC_HS200)
			pwr_class = MMC_EXT_PWR_CL_200_195(pSd->EXT);
		else if (tim_mode == SDMMC_TIM_MMC_HS_DDR)
			pwr_class = MMC_EXT_PWR_CL_DDR_52_360(pSd->EXT);
		else if (tim_mode == SDMMC_TIM_MMC_HS_SDR)
			pwr_class = MMC_EXT_PWR_CL_52_360(pSd->EXT);
		else
			pwr_class = MMC_EXT_PWR_CL_26_360(pSd->EXT);
		if (pwr_class != 0) {
			sw_arg.index = MMC_EXT_POWER_CLASS_I;
			sw_arg.value = 0xf;
			error = MmcCmd6(pSd, &sw_arg, &status);
			if (error)
				trace_error("Pwr class %s\n\r",
				    SD_StringifyRetCode(error));
		}
	}

	/* Enable High Speed SDR timing mode */
	if (tim_mode == SDMMC_TIM_MMC_HS_SDR
	    || tim_mode == SDMMC_TIM_MMC_HS_DDR) {
		sw_arg.index = MMC_EXT_HS_TIMING_I;
		sw_arg.value = MMC_EXT_HS_TIMING_EN;
		error = MmcCmd6(pSd, &sw_arg, &status);
		if (error == SDMMC_OK)
			error = _HwSetHsMode(pSd, SDMMC_TIM_MMC_HS_SDR);
		if (error == SDMMC_OK)
			error = Cmd13(pSd, &status);
		if (error == SDMMC_OK && (status & ~STATUS_STATE
		    & ~STATUS_READY_FOR_DATA
		    || (status & STATUS_STATE) != STATUS_TRAN))
			error = SDMMC_ERROR_STATE;
		if (error == SDMMC_OK) {
			pSd->bSpeedMode = SDMMC_TIM_MMC_HS_SDR;
			freq = SdmmcGetMaxFreq(pSd);
			error = _HwSetClock(pSd, &freq);
			pSd->dwCurrSpeed = freq;
			error = error == SDMMC_CHANGED ? SDMMC_OK : error;
		}
		if (error != SDMMC_OK) {
			trace_error("HS %s\n\r", SD_StringifyRetCode(error));
			return error;
		}
	}

	/* Consider using the widest supported data bus */
	if (MMC_IsCSDVer1_2(pSd) && MMC_IsVer4(pSd)) {
		width = mmcDetectBuswidth(pSd);
		if (width > 1) {
			error = mmcSelectBuswidth(pSd, width,
			    tim_mode == SDMMC_TIM_MMC_HS_DDR);
			if (error == SDMMC_OK)
				error = _HwSetBusWidth(pSd, width);
			if (error == SDMMC_OK)
				pSd->bBusMode = width;
			if (error == SDMMC_OK
			    && tim_mode == SDMMC_TIM_MMC_HS_DDR)
				/* Switch to High Speed DDR timing mode */
				error = _HwSetHsMode(pSd, tim_mode);
			if (error == SDMMC_OK)
				error = Cmd13(pSd, &status);
			if (error == SDMMC_OK && (status & ~STATUS_STATE
			    & ~STATUS_READY_FOR_DATA
			    || (status & STATUS_STATE) != STATUS_TRAN))
				error = SDMMC_ERROR_STATE;
			if (error == SDMMC_OK
			    && tim_mode == SDMMC_TIM_MMC_HS_DDR)
				pSd->bSpeedMode = tim_mode;
			else if (error) {
				trace_error("Width/DDR %s\n\r",
				    SD_StringifyRetCode(error));
				return error;
			}
		}
	}

	/* Enable HS200 timing mode */
	if (tim_mode == SDMMC_TIM_MMC_HS200 && pSd->bBusMode > 1) {
		sw_arg.index = MMC_EXT_HS_TIMING_I;
		/* Select device output Driver Type-0, i.e. 50 ohm nominal
		 * output impedance.
		 * TODO select the optimal device output Driver Type.
		 * That depends on board design. Use an oscilloscope to observe
		 * signal integrity, and among the driver types that meet rise
		 * and fall time requirements, select the weakest. */
		sw_arg.value = MMC_EXT_HS_TIMING_HS200 | MMC_EXT_HS_TIMING_50R;
		error = MmcCmd6(pSd, &sw_arg, &status);
		if (error == SDMMC_OK)
			error = _HwSetHsMode(pSd, tim_mode);
		if (error == SDMMC_OK) {
			error = Cmd13(pSd, &status);
			if (error == SDMMC_OK && (status & ~STATUS_STATE
			    & ~STATUS_READY_FOR_DATA
			    || (status & STATUS_STATE) != STATUS_TRAN))
				error = SDMMC_ERROR_STATE;
		}
		if (error == SDMMC_OK) {
			pSd->bSpeedMode = tim_mode;
			freq = SdmmcGetMaxFreq(pSd);
			error = _HwSetClock(pSd, &freq);
			pSd->dwCurrSpeed = freq;
			error = error == SDMMC_CHANGED ? SDMMC_OK : error;
		}
		if (error != SDMMC_OK) {
			trace_error("HS200 %s\n\r", SD_StringifyRetCode(error));
			return error;
		}
	}

	/* Update card information since status changed */
	flag = pSd->bSpeedMode >= SDMMC_TIM_MMC_HS_SDR;
	if (flag || pSd->bBusMode > 1)
		SdMmcUpdateInformation(pSd, flag, true);

	/* MMC devices have the SET_BLOCK_COUNT command part of both the
	 * block-oriented read and the block-oriented write commands,
	 * i.e. class 2 and class 4 commands.
	 * FIXME we should normally check CSD.CCC before issuing any MMC block-
	 * oriented read/write command. */
	pSd->bSetBlkCnt = 1;
	/* Ask the driver to implicitly send the SET_BLOCK_COUNT command,
	 * immediately before every READ_MULTIPLE_BLOCK and WRITE_MULTIPLE_BLOCK
	 * command. */
	drv_param = pSd->bSetBlkCnt;
	drv_err = pSd->pHalf->fIOCtrl(pSd->pDrv, SDMMC_IOCTL_SET_LENPREFIX,
	    (uint32_t)&drv_param);
	/* In case the driver does not support this function, we'll take it in
	 * charge. */
	if (pSd->bSetBlkCnt && drv_err == SDMMC_OK && drv_param)
		pSd->bSetBlkCnt = 0;

	pSd->wCurrBlockLen = SDMMC_BLOCK_SIZE;

	if (MMC_IsCSDVer1_2(pSd) && MMC_IsVer4(pSd)) {
		if (MMC_EXT_DATA_SECTOR_SIZE(pSd->EXT)
		    == MMC_EXT_DATA_SECT_4KIB)
			pSd->wBlockSize = 4096;
		else
			pSd->wBlockSize = 512;
		pSd->dwNbBlocks = MMC_EXT_SEC_COUNT(pSd->EXT)
		    / (pSd->wBlockSize / 512UL);
		if(MMC_CSD_C_SIZE(pSd->CSD) == 0xfff) {
			/* Device density >= 4 GiB does not fit 32-bit dwTotalSize */
			pSd->dwTotalSize = MMC_EXT_SEC_COUNT(pSd->EXT);
			pSd->dwTotalSize *= 512UL;
		}
		else {
			pSd->dwNbBlocks = MMC_CSD_C_SIZE(pSd->CSD)
							* (1 << (MMC_CSD_C_SIZE_MULT(pSd->CSD) + 2));
			pSd->dwTotalSize = pSd->dwNbBlocks * (1 << MMC_CSD_READ_BL_LEN(pSd->CSD));
		}
	}
	else {
		pSd->wBlockSize = 512;
		mem_size = SD_CSD_TOTAL_SIZE(pSd->CSD);
		pSd->dwNbBlocks = (uint32_t)(mem_size >> 9);
		pSd->dwTotalSize = mem_size >> 32 ? 0xFFFFFFFF
		    : (uint32_t)mem_size;
	}

	/* Check device status and eat past exceptions, which would otherwise
	 * prevent upcoming data transaction routines from reliably checking
	 * fresh exceptions. */
	error = Cmd13(pSd, &status);
	if (error)
		return error;
	status = status & ~STATUS_STATE & ~STATUS_READY_FOR_DATA
	    & ~STATUS_APP_CMD;
	if (status)
		trace_warning("st %lx\n\r", status);

	return SDMMC_SUCCESS;
}
#endif

static uint8_t
SdInit(sSdCard * pSd, bool * retry)
{
	uint64_t mem_size;
	uint32_t freq, drv_param, drv_err, status;
	uint8_t error;
	bool flag;

	*retry = false;
	pSd->bSpeedMode = pSd->bCardSigLevel == 0 ? SDMMC_TIM_SD_SDR12
	    : SDMMC_TIM_SD_DS;
	_HwSetHsMode(pSd, pSd->bSpeedMode);

	/* Consider switching to low signaling level, as a prerequisite to
	 * switching to any UHS-I timing mode */
	if (pSd->bCardSigLevel == 1) {
		error = Cmd11(pSd, &status);
		if (error)
			return error;
		if ((status & STATUS_STATE) != STATUS_READY)
			trace_warning("st %lx\n\r", status);
		pSd->bCardSigLevel = 0;
		error = _HwPowerDevice(pSd, SDMMC_PWR_STD_VDD_LOW_IO);
		if (error)
			return error;
		error = _HwSetHsMode(pSd, SDMMC_TIM_SD_SDR12);
		if (error)
			return error;
		pSd->bSpeedMode = SDMMC_TIM_SD_SDR12;
	}

	/* The host then issues the command ALL_SEND_CID (CMD2) to the card to get
	 * its unique card identification (CID) number.
	 * Card that is unidentified (i.e. which is in Ready State) sends its CID
	 * number as the response (on the CMD line). */
	error = Cmd2(pSd);
	if (error)
		return error;

	/* Thereafter, the host issues CMD3 (SEND_RELATIVE_ADDR) asks the
	 * card to publish a new relative card address (RCA), which is shorter than
	 * CID and which is used to address the card in the future data transfer
	 * mode. Once the RCA is received the card state changes to the Stand-by
	 * State. At this point, if the host wants to assign another RCA number, it
	 * can ask the card to publish a new number by sending another CMD3 command
	 * to the card. The last published RCA is the actual RCA number of the
	 * card. */
	error = Cmd3(pSd);
	if (error)
		return error;
	else
		trace_debug("RCA=%u\n\r", CARD_ADDR(pSd));

	/* SEND_CSD (CMD9) to obtain the Card Specific Data (CSD register),
	 * e.g. block length, card storage capacity, etc... */
	error = Cmd9(pSd);
	if (error)
		return error;

	/* Now select the card, to TRAN state */
	error = SdMmcSelect(pSd, CARD_ADDR(pSd), 0);
	if (error)
		return error;

	/* Get extended information of the card */
	SdMmcUpdateInformation(pSd, true, true);

	/* Enable more bus width Mode */
	error = SdDecideBuswidth(pSd);
	if (error) {
		trace_error("Bus width %s\n\r", SD_StringifyRetCode(error));
		return SDMMC_ERROR;
	}

	/* Consider HS and UHS-I timing modes */
	error = SdEnableHighSpeed(pSd);
	if (error) {
		*retry = error == SDMMC_ERROR_STATE && pSd->bCardSigLevel != 0;
		return error;
	}

	/* Update card information since status changed */
	flag = pSd->bSpeedMode != SDMMC_TIM_SD_DS
	    && pSd->bSpeedMode != SDMMC_TIM_SD_SDR12;
	if (flag || pSd->bBusMode > 1)
		SdMmcUpdateInformation(pSd, flag, true);

	/* Find out if the device supports the SET_BLOCK_COUNT command.
	 * SD devices advertise in SCR.CMD_SUPPORT whether or not they handle
	 * the SET_BLOCK_COUNT command. */
	pSd->bSetBlkCnt = SD_SCR_CMD23_SUPPORT(pSd->SCR);
	/* Now, if the device does not support the SET_BLOCK_COUNT command, then
	 * the legacy STOP_TRANSMISSION command shall be issued, though not at
	 * the same timing. */
	if (!pSd->bSetBlkCnt) {
		/* In case the driver does not automatically issue the
		 * STOP_TRANSMISSION command, we'll have to do it ourselves. */
		drv_param = 0;
		drv_err = pSd->pHalf->fIOCtrl(pSd->pDrv,
		    SDMMC_IOCTL_GET_XFERCOMPL, (uint32_t)&drv_param);
		if (drv_err != SDMMC_OK || !drv_param)
			pSd->bStopMultXfer = 1;
	}
	/* Ask the driver to implicitly send the SET_BLOCK_COUNT command,
	 * immediately before every READ_MULTIPLE_BLOCK and WRITE_MULTIPLE_BLOCK
	 * command. Or, if the current device does not support SET_BLOCK_COUNT,
	 * instruct the driver to stop using this command. */
	drv_param = pSd->bSetBlkCnt;
	drv_err = pSd->pHalf->fIOCtrl(pSd->pDrv, SDMMC_IOCTL_SET_LENPREFIX,
	    (uint32_t)&drv_param);
	/* In case the driver does not support this function, we'll take it in
	 * charge. */
	if (pSd->bSetBlkCnt && drv_err == SDMMC_OK && drv_param)
		pSd->bSetBlkCnt = 0;

	/* In the case of a Standard Capacity SD Memory Card, this command sets the
	 * block length (in bytes) for all following block commands
	 * (read, write, lock).
	 * Default block length is fixed to 512 Bytes.
	 * Set length is valid for memory access commands only if partial block read
	 * operation are allowed in CSD.
	 * In the case of a High Capacity SD Memory Card, block length set by CMD16
	 * command does not affect the memory read and write commands. Always 512
	 * Bytes fixed block length is used. This command is effective for
	 * LOCK_UNLOCK command.
	 * In both cases, if block length is set larger than 512Bytes, the card sets
	 * the BLOCK_LEN_ERROR bit. */
	if (pSd->bCardType == CARD_SD) {
		error = Cmd16(pSd, SDMMC_BLOCK_SIZE);
		if (error)
			return error;
	}
	pSd->wCurrBlockLen = SDMMC_BLOCK_SIZE;

	if (SD_CSD_STRUCTURE(pSd->CSD) >= 1) {
		pSd->wBlockSize = 512;
		mem_size = SD_CSD_BLOCKNR_HC(pSd->CSD);
		pSd->dwNbBlocks = mem_size >> 32 ? 0xFFFFFFFF
		    : (uint32_t)mem_size;
		if (pSd->dwNbBlocks >= 0x800000)
			pSd->dwTotalSize = 0xFFFFFFFF;
		else
			pSd->dwTotalSize = pSd->dwNbBlocks * 512UL;
	}
	else {
		pSd->wBlockSize = 512;
		mem_size = SD_CSD_TOTAL_SIZE(pSd->CSD);
		pSd->dwNbBlocks = (uint32_t)(mem_size >> 9);
		pSd->dwTotalSize = mem_size >> 32 ? 0xFFFFFFFF
		    : (uint32_t)mem_size;
	}

	/* Automatically select the max device clock frequency */
	/* Calculate transfer speed */
	freq = SdmmcGetMaxFreq(pSd);
#ifndef SDMMC_TRIM_SDIO
	if (pSd->bCardType & CARD_TYPE_bmSDIO)
		freq = min_u32(freq, SdioGetMaxFreq(pSd));
#endif
	error = _HwSetClock(pSd, &freq);
	pSd->dwCurrSpeed = freq;
	if (error != SDMMC_OK && error != SDMMC_CHANGED) {
		trace_error("clk %s\n\r", SD_StringifyRetCode(error));
		return error;
	}

	/* Check device status and eat past exceptions, which would otherwise
	 * prevent upcoming data transaction routines from reliably checking
	 * fresh exceptions. */
	error = Cmd13(pSd, &status);
	if (error)
		return error;
	status = status & ~STATUS_STATE & ~STATUS_READY_FOR_DATA
	    & ~STATUS_APP_CMD;
	if (status)
		trace_warning("st %lx\n\r", status);

	return SDMMC_SUCCESS;
}

#ifndef SDMMC_TRIM_SDIO
static uint8_t
SdioInit(sSdCard * pSd)
{
	uint32_t freq;
	uint8_t error;

	pSd->bSpeedMode = SDMMC_TIM_SD_DS;
	_HwSetHsMode(pSd, pSd->bSpeedMode);
	/* Thereafter, the host issues CMD3 (SEND_RELATIVE_ADDR) asks the
	 * card to publish a new relative card address (RCA), which is shorter than
	 * CID and which is used to address the card in the future data transfer
	 * mode. Once the RCA is received the card state changes to the Stand-by
	 * State. At this point, if the host wants to assign another RCA number, it
	 * can ask the card to publish a new number by sending another CMD3 command
	 * to the card. The last published RCA is the actual RCA number of the
	 * card. */
	error = Cmd3(pSd);
	if (error)
		return error;
	else
		trace_debug("RCA=%u\n\r", CARD_ADDR(pSd));

	/* Now select the card, to TRAN state */
	error = SdMmcSelect(pSd, CARD_ADDR(pSd), 0);
	if (error)
		return error;

	/* Enable more bus width Mode */
	error = SdDecideBuswidth(pSd);
	if (error) {
		trace_error("Bus width %s\n\r", SD_StringifyRetCode(error));
		return SDMMC_ERROR;
	}

	/* Consider High-Speed timing mode */
	error = SdEnableHighSpeed(pSd);
	if (error)
		return error;

	/* Increase device clock frequency */
	freq = SdioGetMaxFreq(pSd);
	error = _HwSetClock(pSd, &freq);
	pSd->dwCurrSpeed = freq;
	if (error != SDMMC_OK && error != SDMMC_CHANGED) {
		trace_error("clk %s\n\r", SD_StringifyRetCode(error));
		return error;
	}

	return SDMMC_SUCCESS;
}
#endif

/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/

/** \brief Dump register.
 */
void
_DumpREG(void *pREG, uint32_t dwSize)
{
	uint8_t *p = (uint8_t *) pREG;
	uint32_t i;
	for (i = 0; i < dwSize; i++) {
		if ((i % 16) == 0)
			printf("\n\r [%04X]", (unsigned int) i);
		printf(" %02X", p[i]);
	}
	printf("\n\r");
}

/**
 * From a wide-width device register extract the requested field.
 * \param reg  Contents of the register
 * \param reg_len  Length of the register, in bits
 * \param field_start  Offset (address of the least significant bit) of the
 * requested field, in bits
 * \param field_len  Length of the requested field, in bits
 * \return The value of the field.
 */
uint32_t
SD_GetField(const uint8_t *reg, uint16_t reg_len, uint16_t field_start,
            uint8_t field_len)
{
	uint32_t val = 0;
	uint8_t byte, expected_bits = field_len, new_bits;

	assert(reg);
	assert(reg_len % 8 == 0);
	assert(field_len != 0 && field_len <= 32 && field_len <= reg_len);
	assert(field_start <= reg_len - field_len);

	reg += (reg_len - field_start - field_len) / 8;
	while (expected_bits) {
		byte = *reg;
		new_bits = (field_start + expected_bits) % 8;
		if (new_bits)
			byte &= (1 << new_bits) - 1;
		else
			new_bits = 8;
		if (new_bits <= expected_bits)
			val |= (uint32_t)byte << (expected_bits - new_bits);
		else {
			byte >>= new_bits - expected_bits;
			val |= byte;
			new_bits = expected_bits;
		}
		expected_bits -= new_bits;
		reg++;
	}
	assert((val & ~0 << field_len) == 0);
	return val;
}

/**
 * Read Blocks of data in a buffer pointed by pData. The buffer size must be at
 * least 512 byte long. This function checks the SD card status register and
 * address the card if required before sending the read command.
 * \return 0 if successful; otherwise returns an \ref sdmmc_rc "error code".
 * \param pSd      Pointer to a SD card driver instance.
 * \param address  Address of the block to read.
 * \param pData    Data buffer whose size is at least the block size. It shall
 * follow the peripheral and DMA alignment requirements.
 * \param length   Number of blocks to be read.
 * \param pCallback Pointer to callback function that invoked when read done.
 *                  0 to start a blocked read.
 * \param pArgs     Pointer to callback function arguments.
 */
uint8_t
SD_Read(sSdCard * pSd,
	uint32_t address,
	void *pData, uint32_t length, fSdmmcCallback pCallback, void *pArgs)
{
	uint8_t *out = NULL;
	uint32_t remaining, blk_no;
	uint16_t limited;
	uint8_t error = SDMMC_OK;

	assert(pSd != NULL);
	assert(pData != NULL);

	for (blk_no = address, remaining = length, out = (uint8_t *)pData;
	    remaining != 0 && error == SDMMC_OK;
	    blk_no += limited, remaining -= limited,
	    out += (uint32_t)limited * (uint32_t)BLOCK_SIZE(pSd)) {
		limited = (uint16_t)min_u32(remaining, 65535);
		error = MoveToTransferState(pSd, blk_no, &limited, out, 1);
	}
	trace_debug("SDrd(%lu,%lu) %s\n\r", address, length,
	    SD_StringifyRetCode(error));
	return error;
}

/**
 * Write Blocks of data in a buffer pointed by pData. The buffer size must be at
 * least 512 byte long. This function checks the SD card status register and
 * address the card if required before sending the read command.
 * \return 0 if successful; otherwise returns an \ref sdmmc_rc "error code".
 * \param pSd      Pointer to a SD card driver instance.
 * \param address  Address of the block to write.
 * \param pData    Data buffer whose size is at least the block size. It shall
 * follow the peripheral and DMA alignment requirements.
 * \param length   Number of blocks to be write.
 * \param pCallback Pointer to callback function that invoked when write done.
 *                  0 to start a blocked write.
 * \param pArgs     Pointer to callback function arguments.
 */
uint8_t
SD_Write(sSdCard * pSd,
	 uint32_t address,
	 const void *pData,
	 uint32_t length, fSdmmcCallback pCallback, void *pArgs)
{
	uint8_t *in = NULL;
	uint32_t remaining, blk_no;
	uint16_t limited;
	uint8_t error = SDMMC_OK;

	assert(pSd != NULL);
	assert(pData != NULL);

	for (blk_no = address, remaining = length, in = (uint8_t *)pData;
	    remaining != 0 && error == SDMMC_OK;
	    blk_no += limited, remaining -= limited,
	    in += (uint32_t)limited * (uint32_t)BLOCK_SIZE(pSd)) {
		limited = (uint16_t)min_u32(remaining, 65535);
		error = MoveToTransferState(pSd, blk_no, &limited, in, 0);
	}
	trace_debug("SDwr(%lu,%lu) %s\n\r", address, length,
	    SD_StringifyRetCode(error));
	return error;
}

/**
 * Read Blocks of data in a buffer pointed by pData. The buffer size must be at
 * least 512 byte long. This function checks the SD card status register and
 * address the card if required before sending the read command.
 * \return 0 if successful; otherwise returns an \ref sdmmc_rc "error code".
 * \param pSd  Pointer to a SD card driver instance.
 * \param address  Address of the block to read.
 * \param nbBlocks Number of blocks to be read.
 * \param pData    Data buffer whose size is at least the block size. It shall
 * follow the peripheral and DMA alignment requirements.
 */
uint8_t
SD_ReadBlocks(sSdCard * pSd, uint32_t address, void *pData, uint32_t nbBlocks)
{
	uint8_t error = 0;
	uint8_t *pBytes = (uint8_t *) pData;

	assert(pSd != NULL);
	assert(pData != NULL);
	assert(nbBlocks != 0);

	trace_debug("RdBlks(%lu,%lu)\n\r", address, nbBlocks);
	while (nbBlocks--) {
		error = PerformSingleTransfer(pSd, address, pBytes, 1);
		if (error)
			break;
		address += 1;
		pBytes = &pBytes[512];
	}
	return error;
}

/**
 * Write Block of data pointed by pData. The buffer size must be at
 * least 512 byte long. This function checks the SD card status register and
 * address the card if required before sending the read command.
 * \return 0 if successful; otherwise returns an \ref sdmmc_rc "error code".
 * \param pSd  Pointer to a SD card driver instance.
 * \param address  Address of block to write.
 * \param nbBlocks Number of blocks to be read
 * \param pData    Data buffer whose size is at least the block size. It shall
 * follow the peripheral and DMA alignment requirements.
 */
uint8_t
SD_WriteBlocks(sSdCard * pSd,
	       uint32_t address, const void *pData, uint32_t nbBlocks)
{
	uint8_t error = 0;
	uint8_t *pB = (uint8_t *) pData;

	assert(pSd != NULL);
	assert(pData != NULL);
	assert(nbBlocks != 0);

	trace_debug("WrBlks(%lu,%lu)\n\r", address, nbBlocks);

	while (nbBlocks--) {
		error = PerformSingleTransfer(pSd, address, pB, 0);
		if (error)
			break;
		address += 1;
		pB = &pB[512];
	}
	return error;
}

/**
 * Initialize SD/MMC driver struct.
 * \param pSd   Pointer to a SD card driver instance.
 * \param pDrv  Pointer to low level driver instance.
 * \param bSlot Slot number.
 * \param pHalf Pointer to hardware access functions.
 */
void
SDD_Initialize(sSdCard * pSd,
	       const void *pDrv, uint8_t bSlot, const sSdHalFunctions * pHalf)
{
	pSd->pDrv = (void *) pDrv;
	pSd->pHalf = (sSdHalFunctions *) pHalf;
	pSd->pExt = NULL;
	pSd->bSlot = bSlot;

	_SdParamReset(pSd);
}

/**
 * Run the SDcard initialization sequence. This function runs the
 * initialisation procedure and the identification process, then it sets the
 * SD card in transfer state to set the block length and the bus width.
 * \return 0 if successful; otherwise returns an \ref sdmmc_rc "error code".
 * \param pSd  Pointer to a SD card driver instance.
 */
uint8_t
SD_Init(sSdCard * pSd)
{
	uint32_t freq;
	uint8_t error;
	bool retry = false;

	_SdParamReset(pSd);

	/* Power the device and the bus on */
	_HwPowerDevice(pSd, SDMMC_PWR_STD);
	/* Reset the controller to default timing mode and data bus width */
	_HwSetHsMode(pSd, SDMMC_TIM_MMC_BC);
	_HwSetBusWidth(pSd, 1);
	/* For device identification, clock the device at fOD */
	freq = 400000ul;
	error = _HwSetClock(pSd, &freq);
	if (error != SDMMC_OK && error != SDMMC_CHANGED)
		return error;

	/* Initialization delay: The maximum of 1 msec, 74 clock cycles and supply
	 * ramp up time. Supply ramp up time provides the time that the power is
	 * built up to the operating level (the bus master supply voltage) and the
	 * time to wait until the SD card can accept the first command. */
	/* Power On Init Special Command */
	error = Pon(pSd);
	if (error)
		return error;

Retry:
	/* After power-on or CMD0, all cards?
	 * CMD lines are in input mode, waiting for start bit of the next command.
	 * The cards are initialized with a default relative card address
	 * (RCA=0x0000) and with a default driver stage register setting
	 * (lowest speed, highest driving current capability). */
	error = SdMmcIdentify(pSd);
	if (error) {
		trace_error("Identify %s\n\r", SD_StringifyRetCode(error));
		return error;
	}

	if ((pSd->bCardType & CARD_TYPE_bmSDMMC) == CARD_TYPE_bmSD) {
		error = SdInit(pSd, &retry);
		/* Handle the case where the both the slot and the device are
		 * UHS-I-capable, but the system doesn't support powering the
		 * card off, when SD_DeInit is called. As a result, from the
		 * device's perspective, the voltage switch sequence has been
		 * taken already. */
		if (error && retry) {
			_HwPowerDevice(pSd, SDMMC_PWR_STD_VDD_LOW_IO);
			pSd->bCardSigLevel = 0;
			error = _HwSetHsMode(pSd, SDMMC_TIM_SD_SDR12);
			_HwSetBusWidth(pSd, 1);
			if (!error) {
				pSd->bSpeedMode = SDMMC_TIM_SD_SDR12;
				goto Retry;
			}
		}
	}
#ifndef SDMMC_TRIM_SDIO
	else if (pSd->bCardType & CARD_TYPE_bmSDIO)
		error = SdioInit(pSd);
#endif
#ifndef SDMMC_TRIM_MMC
	else if ((pSd->bCardType & CARD_TYPE_bmSDMMC) == CARD_TYPE_bmMMC)
		error = MmcInit(pSd);
#endif
	else {
		trace_error("Identify %s\n\r", "failed");
		return SDMMC_ERROR_NOT_INITIALIZED;
	}
	if (error) {
		trace_error("Init %s\n\r", SD_StringifyRetCode(error));
		return error;
	}

	pSd->bStatus = SDMMC_OK;
	return 0;
}

/**
 * De-initialize the driver. Invoked when SD card disconnected.
 * \param pSd  Pointer to a SD card driver instance.
 */
void
SD_DeInit(sSdCard * pSd)
{
	if (pSd->pDrv) {
		_HwReset(pSd);
		_SdParamReset(pSd);
	}
}

/**
 * Query whether the device is present, and ready for data transfer.
 * \param pSd Pointer to \ref sSdCard instance.
 * \return an \ref sdmmc_rc "error code", as follows:
 * - SDMMC_NOT_SUPPORTED if the device has been removed,
 * - SDMMC_OK if the device is present and ready,
 * - an error code if the device is present but is in an unexpected and
 *   presumably unrecoverable condition. In this event the application may
 *   recover by calling SD_DeInit() and SD_Init().
 */
uint8_t
SD_GetStatus(const sSdCard * pSd)
{
	uint32_t rc, drv_param = 0;

	assert(pSd != NULL);

	rc = pSd->pHalf->fIOCtrl(pSd->pDrv, SDMMC_IOCTL_GET_DEVICE,
	    (uint32_t)&drv_param);
	if (rc != SDMMC_OK || !drv_param)
		return SDMMC_NOT_SUPPORTED;

	return pSd->bStatus == SDMMC_NOT_SUPPORTED ? SDMMC_ERR : pSd->bStatus;
}


/**
 * Query whether the card is writeprotected or not by mechanical 
 write protect switch.
 * \param pSd Pointer to \ref sSdCard instance.
 * \return an \ref sdmmc_rc "error code", as follows:
 * - SDMMC_LOCKED if the device has been mechanical write protected.
 * - SDMMC_OK if the card is not write-protected.
 */
uint8_t
SD_GetWpStatus(const sSdCard * pSd)
{
	uint32_t rc, drv_param = 0;

	assert(pSd != NULL);

	rc = pSd->pHalf->fIOCtrl(pSd->pDrv, SDMMC_IOCTL_GET_WP,
	    (uint32_t)&drv_param);
	if (rc != SDMMC_OK)
		return SDMMC_NOT_SUPPORTED;
    if (!drv_param) 
		return SDMMC_LOCKED;
	else
		return SDMMC_OK;
}

/**
 * Return type of the card.
 * \param pSd Pointer to \ref sSdCard instance.
 * \sa sdmmc_cardtype
 */
uint8_t
SD_GetCardType(const sSdCard * pSd)
{
	assert(pSd != NULL);

	return pSd->bCardType;
}

/**
 * Return size of the SD/MMC card, in KiB.
 * \param pSd Pointer to \ref sSdCard instance.
 */
uint32_t
SD_GetTotalSizeKB(const sSdCard * pSd)
{
	assert(pSd != NULL);

	if (pSd->dwTotalSize == 0xFFFFFFFF)
		return (pSd->dwNbBlocks / 1024) * pSd->wBlockSize;
	else
		return pSd->dwTotalSize / 1024;
}

/**
 * Return reported block size of the SD/MMC card.
 * (SD/MMC access block size is always 512B for R/W).
 * \param pSd Pointer to \ref sSdCard instance.
 */
uint32_t
SD_GetBlockSize(const sSdCard * pSd)
{
	assert(pSd != NULL);

	return pSd->wBlockSize;
}

/**
 * Return reported number of blocks for the SD/MMC card.
 * \param pSd Pointer to \ref sSdCard instance.
 */
uint32_t
SD_GetNumberBlocks(const sSdCard * pSd)
{
	assert(pSd != NULL);

	return pSd->dwNbBlocks;
}

/**
 * Read one or more bytes from SDIO card, using RW_DIRECT command.
 * \param pSd         Pointer to SdCard instance.
 * \param functionNum Function number.
 * \param address     First register address to read from.
 * \param pData       Pointer to data buffer.
 * \param size        Buffer size, number of bytes to read.
 * \return 0 if successful; otherwise returns an \ref sdmmc_rc "error code".
 */
uint8_t
SDIO_ReadDirect(sSdCard * pSd,
		uint8_t functionNum,
		uint32_t address, uint8_t * pData, uint32_t size)
{
	uint8_t error;
	uint32_t status;

	assert(pSd != NULL);

	if (pSd->bCardType & CARD_TYPE_bmSDIO) {
		if (size == 0)
			return SDMMC_ERROR_PARAM;
		while (size--) {
			status = 0;
			error =
			    Cmd52(pSd, 0, functionNum, 0, address++, &status);
			if (pData)
				*pData++ = (uint8_t) status;
			if (error || status & STATUS_SDIO_R5) {
				trace_error("IOrdRegs %luB@%lu %s st %lx\n\r",
				    size, address, SD_StringifyRetCode(error),
				    status);
				return SDMMC_ERROR;
			}
		}
	} else {
		return SDMMC_ERROR_NOT_SUPPORT;
	}
	return 0;
}

/**
 * Write one byte to SDIO card, using RW_DIRECT command.
 * \param pSd         Pointer to SdCard instance.
 * \param functionNum Function number.
 * \param address     Register address to write to.
 * \param pData       Pointer to the value to be written.
 * \param rdAfterWr   Boolean, true to read the register back, returning the new
 * value of the register in *pData.
 * \return 0 if successful; otherwise returns an \ref sdmmc_rc "error code".
 */
uint8_t
SDIO_WriteDirect(sSdCard * pSd,
		 uint8_t functionNum,
		 uint32_t address, uint8_t * pData, uint8_t rdAfterWr)
{
	uint8_t error;
	uint32_t status;

	assert(pSd != NULL);
	assert(pData);

	if (pSd->bCardType & CARD_TYPE_bmSDIO) {
		status = 0 | *pData;
		error = Cmd52(pSd, 1, functionNum, rdAfterWr ? 1 : 0, address,
		    &status);
		if (error || status & STATUS_SDIO_R5) {
			trace_error("IOwrReg %lu %s st %lx\n\r", address,
			    SD_StringifyRetCode(error), status);
			return SDMMC_ERROR;
		}
		error = DATA_SDIO_R5(status);
		if (!rdAfterWr && error != *pData) {
			trace_error("IOwrReg mismatch 0x%02x\n\r", error);
			return SDMMC_ERROR;
		}
		if (rdAfterWr)
			*pData = error;
	} else {
		return SDMMC_ERROR_NOT_SUPPORT;
	}
	return 0;
}

/**
 * Read byte by byte from SDIO card, using RW_EXTENDED command.
 * \param pSd            Pointer to SdCard instance.
 * \param functionNum    Function number.
 * \param address        First byte address of data in SDIO card.
 * \param isFixedAddress During transfer the data address is never increased.
 * \param pData          Pointer to data buffer.
 * The buffer shall follow the peripheral and DMA alignment requirements.
 * \param size           Size of data to read (1 ~ 512).
 * \param fCallback      Callback function invoked when transfer finished.
 * \param pArg           Pointer to callback argument.
 * \return 0 if successful; otherwise returns an \ref sdmmc_rc "error code".
 */
uint8_t
SDIO_ReadBytes(sSdCard * pSd,
	       uint8_t functionNum,
	       uint32_t address,
	       uint8_t isFixedAddress,
	       uint8_t * pData,
	       uint16_t size, fSdmmcCallback fCallback, void *pArg)
{
	uint8_t error;
	uint32_t status;

	assert(pSd != NULL);

	if (pSd->bCardType & CARD_TYPE_bmSDIO) {
		if (size == 0)
			return SDMMC_ERROR_PARAM;
		error = Cmd53(pSd,
			      0, functionNum, 0, !isFixedAddress,
			      address, pData, size, &status, fCallback, pArg);
		if (error || status & STATUS_SDIO_R5) {
			trace_error("IOrdExt %s st %lx\n\r",
			    SD_StringifyRetCode(error), status);
			return SDMMC_ERROR;
		}
	} else {
		return SDMMC_ERROR_NOT_SUPPORT;
	}
	return 0;
}

/**
 * Write byte by byte to SDIO card, using RW_EXTENDED command.
 * \param pSd            Pointer to SdCard instance.
 * \param functionNum    Function number.
 * \param address        First byte address of data in SDIO card.
 * \param isFixedAddress During transfer the data address is never increased.
 * \param pData          Pointer to data buffer.
 * The buffer shall follow the peripheral and DMA alignment requirements.
 * \param size           Size of data to write (1 ~ 512).
 * \param fCallback      Callback function invoked when transfer finished.
 * \param pArg           Pointer to callback argument.
 * \return 0 if successful; otherwise returns an \ref sdmmc_rc "error code".
 */
uint8_t
SDIO_WriteBytes(sSdCard * pSd,
		uint8_t functionNum,
		uint32_t address,
		uint8_t isFixedAddress,
		uint8_t * pData,
		uint16_t size, fSdmmcCallback fCallback, void *pArg)
{
	uint8_t error;
	uint32_t status;

	assert(pSd != NULL);

	if (pSd->bCardType & CARD_TYPE_bmSDIO) {
		if (size == 0)
			return SDMMC_ERROR_PARAM;
		error = Cmd53(pSd,
			      1, functionNum, 0, !isFixedAddress,
			      address, pData, size,
			      (uint32_t *) & status, fCallback, pArg);
		if (error || status & STATUS_SDIO_R5) {
			trace_error("IOwrExt %s st %lx\n\r",
			    SD_StringifyRetCode(error), status);
			return SDMMC_ERROR;
		}
	} else {
		return SDMMC_ERROR_NOT_SUPPORT;
	}
	return 0;
}

/**
 * Read block-sized chunks from SDIO card, using IO_RW_EXTENDED command.
 * \param pSd            Pointer to SdCard instance.
 * \param functionNum    Function number.
 * \param address        First byte address of data in SDIO card.
 * \param isFixedAddress During transfer the data address is never increased.
 * \param pData          Pointer to data buffer.
 * \param count          Number of data blocks to read (1 ~ 511).
 * \param fCallback      Callback function invoked when transfer finished.
 * \param pArg           Pointer to callback argument.
 * \return a \ref sdmmc_rc "result code".
 */
uint8_t
SDIO_ReadBlocks(sSdCard * pSd,
                uint8_t functionNum,
                uint32_t address,
                uint8_t isFixedAddress,
                uint8_t * pData,
                uint16_t count, fSdmmcCallback fCallback, void * pArg)
{
	uint8_t error;
	uint32_t status;

	assert(pSd);

	if (!(pSd->bCardType & CARD_TYPE_bmSDIO))
		return SDMMC_ERROR_NOT_SUPPORT;
	if (count == 0 || count > 511)
		return SDMMC_ERROR_PARAM;
	error = Cmd53(pSd, 0, functionNum, 1, !isFixedAddress, address, pData,
	    count, &status, fCallback, pArg);
	if (error != SDMMC_SUCCESS || status & STATUS_SDIO_R5) {
		trace_error("IOrdExt %s st %lx\n\r",
		    SD_StringifyRetCode(error), status);
		return error != SDMMC_SUCCESS ? error : SDMMC_ERROR;
	}
	return SDMMC_SUCCESS;
}

/**
 * Write block-sized chunks to SDIO card, using IO_RW_EXTENDED command.
 * \param pSd            Pointer to SdCard instance.
 * \param functionNum    Function number.
 * \param address        First byte address of data in SDIO card.
 * \param isFixedAddress During transfer the data address is never increased.
 * \param pData          Pointer to data buffer.
 * \param count          Number of data blocks to write (1 ~ 511).
 * \param fCallback      Callback function invoked when transfer finished.
 * \param pArg           Pointer to callback argument.
 * \return a \ref sdmmc_rc "result code".
 */
uint8_t
SDIO_WriteBlocks(sSdCard * pSd,
                 uint8_t functionNum,
                 uint32_t address,
                 uint8_t isFixedAddress,
                 uint8_t * pData,
                 uint16_t count, fSdmmcCallback fCallback, void * pArg)
{
	uint8_t error;
	uint32_t status;

	assert(pSd);

	if (!(pSd->bCardType & CARD_TYPE_bmSDIO))
		return SDMMC_ERROR_NOT_SUPPORT;
	if (count == 0 || count > 511)
		return SDMMC_ERROR_PARAM;
	error = Cmd53(pSd, 1, functionNum, 1, !isFixedAddress, address, pData,
	    count, &status, fCallback, pArg);
	if (error != SDMMC_SUCCESS || status & STATUS_SDIO_R5) {
		trace_error("IOwrExt %s st %lx\n\r",
		    SD_StringifyRetCode(error), status);
		return error != SDMMC_SUCCESS ? error : SDMMC_ERROR;
	}
	return SDMMC_SUCCESS;
}

/**
 * Read from SDIO device, using the RW_EXTENDED command and byte or block I/O
 * automatically.
 * When data size reaches or exceeds two SDIO blocks, block I/O is used.
 * Byte I/O is used for excess bytes, small data chunks, or when block I/O
 * is disabled or simply not supported.
 * \param pSd            Pointer to SdCard instance.
 * \param functionNum    Function number.
 * \param address        First byte address of data in SDIO card.
 * \param isFixedAddress During transfer the data address is never increased.
 * \param pData          Pointer to data buffer.
 * The buffer shall follow the peripheral and DMA alignment requirements.
 * \param size           Size of data to read.
 * \param fCallback      Callback function invoked when transfer finished.
 * \param pArg           Pointer to callback argument.
 * \return 0 if successful; otherwise returns an \ref sdmmc_rc "error code".
 */
uint8_t
SDIO_Read(sSdCard * pSd,
          uint8_t functionNum,
          uint32_t address,
          uint8_t isFixedAddress,
          uint8_t * pData,
          uint32_t size, fSdmmcCallback fCallback, void *pArg)
{
	uint8_t *out = NULL;
	uint32_t addr_now, remaining, limited = 0;
	/* TODO retrieve and cache the I/O block size negotiated for the
	 * specified I/O Function. In case the device doesn't support block
	 * I/O, assign 0. */
	uint16_t blk_size = 0;
	uint8_t rc = SDMMC_SUCCESS, blk_rc;

	assert(pSd);
	assert(pData);

	if (!(pSd->bCardType & CARD_TYPE_bmSDIO))
		return SDMMC_ERROR_NOT_SUPPORT;

	for (addr_now = address, remaining = size, out = pData;
	    (blk_size ? remaining / blk_size >= (blk_size > 512 ? 1 : 2) : 0)
	    && rc == SDMMC_SUCCESS;
	    addr_now += limited * blk_size, remaining -= limited * blk_size,
	    out += limited * blk_size) {
		limited = remaining / blk_size;
		limited = min_u32(limited, 511);
		rc = SDIO_ReadBlocks(pSd, functionNum, isFixedAddress
		    ? address : addr_now, isFixedAddress, out,
		    (uint16_t)limited, NULL, NULL);
	}
	blk_rc = rc;
	if (blk_rc != SDMMC_SUCCESS)
		trace_error("IOrdExt failed %lu blocks from 0x%lx\n\r", limited,
		    addr_now - limited * blk_size);

	for ( ; remaining >= 1 && rc == SDMMC_SUCCESS;
	    addr_now += limited, remaining -= limited, out += limited) {
		limited = min_u32(remaining, 512);
		rc = SDIO_ReadBytes(pSd, functionNum, isFixedAddress
		    ? address : addr_now, isFixedAddress, out,
		    (uint16_t)limited, NULL, NULL);
	}
	if (blk_rc == SDMMC_SUCCESS && rc != SDMMC_SUCCESS)
		trace_error("IOrdExt failed %luB from 0x%lx\n\r", limited,
		    addr_now - limited);

	/* Invoke the optional callback */
	if (fCallback)
		(fCallback)(rc, pArg);
	return rc;
}

/**
 * Write to SDIO device, using the RW_EXTENDED command and byte or block I/O
 * automatically.
 * When data size reaches or exceeds two SDIO blocks, block I/O is used.
 * Byte I/O is used for excess bytes, small data chunks, or when block I/O
 * is disabled or simply not supported.
 * \param pSd            Pointer to SdCard instance.
 * \param functionNum    Function number.
 * \param address        First byte address of data in SDIO card.
 * \param isFixedAddress During transfer the data address is never increased.
 * \param pData          Pointer to data buffer.
 * The buffer shall follow the peripheral and DMA alignment requirements.
 * \param size           Size of data to write.
 * \param fCallback      Callback function invoked when transfer finished.
 * \param pArg           Pointer to callback argument.
 * \return 0 if successful; otherwise returns an \ref sdmmc_rc "error code".
 */
uint8_t
SDIO_Write(sSdCard * pSd,
           uint8_t functionNum,
           uint32_t address,
           uint8_t isFixedAddress,
           uint8_t * pData,
           uint32_t size, fSdmmcCallback fCallback, void *pArg)
{
	uint8_t *in = NULL;
	uint32_t addr_now, remaining, limited = 0;
	uint16_t blk_size = 0; /* TODO retrieve and cache I/O block size */
	uint8_t rc = SDMMC_SUCCESS, blk_rc;

	assert(pSd);
	assert(pData);

	if (!(pSd->bCardType & CARD_TYPE_bmSDIO))
		return SDMMC_ERROR_NOT_SUPPORT;

	for (addr_now = address, remaining = size, in = pData;
	    (blk_size ? remaining / blk_size >= (blk_size > 512 ? 1 : 2) : 0)
	    && rc == SDMMC_SUCCESS;
	    addr_now += limited * blk_size, remaining -= limited * blk_size,
	    in += limited * blk_size) {
		limited = remaining / blk_size;
		limited = min_u32(limited, 511);
		rc = SDIO_WriteBlocks(pSd, functionNum, isFixedAddress
		    ? address : addr_now, isFixedAddress, in, (uint16_t)limited,
		    NULL, NULL);
	}
	blk_rc = rc;
	if (blk_rc != SDMMC_SUCCESS)
		trace_error("IOwrExt failed %lu blocks to 0x%lx\n\r", limited,
		    addr_now - limited * blk_size);

	for ( ; remaining >= 1 && rc == SDMMC_SUCCESS;
	    addr_now += limited, remaining -= limited, in += limited) {
		limited = min_u32(remaining, 512);
		rc = SDIO_WriteBytes(pSd, functionNum, isFixedAddress
		    ? address : addr_now, isFixedAddress, in, (uint16_t)limited,
		    NULL, NULL);
	}
	if (blk_rc == SDMMC_SUCCESS && rc != SDMMC_SUCCESS)
		trace_error("IOwrExt failed %luB to 0x%lx\n\r", limited,
		    addr_now - limited);

	/* Invoke the optional callback */
	if (fCallback)
		(fCallback)(rc, pArg);
	return rc;
}

/**
 * Print brief device type and interface status
 * \param pSd Pointer to \ref sSdCard instance.
 */
void
SD_DumpStatus(const sSdCard *pSd)
{
	char text[40] = "";
	char mode[20] = "";
	char vers[7] = { ' ', 'v', '1', '.', '0', '\0', '\0' };

	assert(pSd != NULL);

	if (pSd->bCardType & CARD_TYPE_bmHC)
		strcat(text, "High-capacity ");
	if (pSd->bCardType & CARD_TYPE_bmSDIO
	    && pSd->bCardType & CARD_TYPE_bmSD)
		strcat(text, "SDIO combo card");
	else if (pSd->bCardType & CARD_TYPE_bmSDIO)
		strcat(text, "SDIO device");
	else if (pSd->bCardType & CARD_TYPE_bmSD)
		strcat(text, "SD card");
#ifndef SDMMC_TRIM_MMC
	else if (pSd->bCardType & CARD_TYPE_bmMMC)
		strcat(text, "MMC device");
#endif
	else
		strcat(text, "unrecognized device");

	if (pSd->bCardType & CARD_TYPE_bmMMC) {
#ifndef SDMMC_TRIM_MMC
		const uint8_t csd = MMC_CSD_SPEC_VERS(pSd->CSD);
		const uint8_t ext = MMC_EXT_EXT_CSD_REV(pSd->EXT);

		if (csd == MMC_CSD_SPEC_VERS_1_4)
			vers[4] = '4';
		else if (csd == MMC_CSD_SPEC_VERS_2_0) {
			vers[2] = '2';
			vers[4] = 'x';
		}
		else if (csd == MMC_CSD_SPEC_VERS_3_1) {
			vers[2] = '3';
			vers[4] = 'x';
		}
		else if (csd == MMC_CSD_SPEC_VERS_4_0) {
			vers[2] = ext <= 6 ? '4' : '5';
			if (ext <= 4)
				vers[4] = '0' + ext;
			else if (ext == 5) {
				vers[4] = '4';
				vers[5] = '1';
			}
			else if (ext == 6) {
				vers[4] = '5';
				vers[5] = 'x';
			}
			else if (ext == 7)
				vers[5] = 'x';
			else if (ext == 8)
				vers[4] = '1';
			else
				vers[4] = 'x';
		}
		else if (csd != MMC_CSD_SPEC_VERS_1_0)
			vers[2] = vers[4] = '?';
		strcat(text, vers);
#endif
	}
	else if (pSd->bCardType & CARD_TYPE_bmSD
	    && SD_SCR_STRUCTURE(pSd->SCR) == SD_SCR_STRUCTURE_1_0) {
		if (SD_SCR_SD_SPEC(pSd->SCR) == SD_SCR_SD_SPEC_1_0)
			vers[5] = 'x';
		else if (SD_SCR_SD_SPEC(pSd->SCR) == SD_SCR_SD_SPEC_1_10) {
			vers[4] = '1';
			vers[5] = '0';
		}
		else if (SD_SCR_SD_SPEC(pSd->SCR) == SD_SCR_SD_SPEC_2_00) {
			if (SD_SCR_SD_SPEC4(pSd->SCR) == SD_SCR_SD_SPEC_4_X) {
				vers[2] = '4';
				vers[4] = vers[5] = 'x';
			}
			else if (SD_SCR_SD_SPEC3(pSd->SCR)
			    == SD_SCR_SD_SPEC_3_0) {
				vers[2] = '3';
				vers[5] = 'x';
			}
			else {
				vers[2] = '2';
				vers[5] = '0';
			}
		}
		else
			vers[2] = vers[4] = '?';
		strcat(text, vers);
	}

	if (pSd->bSpeedMode == SDMMC_TIM_MMC_BC)
		strcat(mode, "Backward-compatible");
#ifndef SDMMC_TRIM_MMC
	else if (pSd->bSpeedMode == SDMMC_TIM_MMC_HS_SDR)
		strcat(mode, "HS SDR");
	else if (pSd->bSpeedMode == SDMMC_TIM_MMC_HS_DDR)
		strcat(mode, "HS DDR");
	else if (pSd->bSpeedMode == SDMMC_TIM_MMC_HS200)
		strcat(mode, "HS200");
#endif
	else if (pSd->bSpeedMode == SDMMC_TIM_SD_DS)
		strcat(mode, "DS");
	else if (pSd->bSpeedMode == SDMMC_TIM_SD_HS)
		strcat(mode, "HS");
	else if (pSd->bSpeedMode >= SDMMC_TIM_SD_SDR12
	    && pSd->bSpeedMode <= SDMMC_TIM_SD_SDR104) {
		char uhs_mode[10] = "UHS-I SDR";

		if (pSd->bSpeedMode == SDMMC_TIM_SD_DDR50)
			uhs_mode[6] = 'D';
		strcat(mode, uhs_mode);
		if (pSd->bSpeedMode == SDMMC_TIM_SD_SDR12)
			strcat(mode, "12");
		else if (pSd->bSpeedMode == SDMMC_TIM_SD_SDR25)
			strcat(mode, "25");
		else if (pSd->bSpeedMode == SDMMC_TIM_SD_SDR50
		    || pSd->bSpeedMode == SDMMC_TIM_SD_DDR50)
			strcat(mode, "50");
		else
			strcat(mode, "104");
	}
	printf("%s, %u-bit data, in %s mode at %lu kHz\n\r", text,
	    pSd->bBusMode, mode, pSd->dwCurrSpeed / 1000UL);

	if (pSd->bCardType & CARD_TYPE_bmSDMMC)
		printf("Device memory size: %lu MiB, %lu * %uB\n\r",
		    SD_GetTotalSizeKB(pSd) / 1024ul, pSd->dwNbBlocks,
		    pSd->wBlockSize);
}

/**
 * Display SDIO card informations (CIS, tuple ...)
 * \param pSd Pointer to \ref sSdCard instance.
 */
void
SDIO_DumpCardInformation(sSdCard * pSd)
{
	uint32_t tmp = 0, addrCIS = 0, addrManfID = 0, addrFuncE = 0;
	uint8_t *p = (uint8_t *) & tmp;
	uint8_t buf[16];

	/* CCCR */
	_PrintTitle("CCCR");
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_CCCR_REG, p, 1);
	_PrintField("SDIO", "0x%02lX", (tmp & SDIO_SDIO) >> 4);
	_PrintField("CCCR", "0x%02lX", (tmp & SDIO_CCCR) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_SD_REV_REG, p, 1);
	_PrintField("SD",   "0x%02lX", (tmp & SDIO_SD) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_IOE_REG, p, 1);
	_PrintField("IOE",  "0x%02lX", (tmp & SDIO_IOE) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_IOR_REG, p, 1);
	_PrintField("IOR",  "0x%02lX", (tmp & SDIO_IOR) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_IEN_REG, p, 1);
	_PrintField("IEN",  "0x%02lX", (tmp & SDIO_IEN) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_INT_REG, p, 1);
	_PrintField("INT",  "%lu",     (tmp & SDIO_INT) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_BUS_CTRL_REG, p, 1);
	_PrintField("CD",   "0x%lX",   (tmp & SDIO_CD) >> 7);
	_PrintField("SCSI", "0x%lX",   (tmp & SDIO_SCSI) >> 6);
	_PrintField("ECSI", "0x%lX",   (tmp & SDIO_ECSI) >> 5);
	_PrintField("BUS_WIDTH", "0x%lX", (tmp & SDIO_BUSWIDTH) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_CAP_REG, p, 1);
	_PrintField("4BLS", "0x%lX",   (tmp & SDIO_4BLS) >> 7);
	_PrintField("LSC",  "0x%lX",   (tmp & SDIO_LSC) >> 6);
	_PrintField("E4MI", "0x%lX",   (tmp & SDIO_E4MI) >> 5);
	_PrintField("S4MI", "0x%lX",   (tmp & SDIO_S4MI) >> 4);
	_PrintField("SBS",  "0x%lX",   (tmp & SDIO_SBS) >> 3);
	_PrintField("SRW",  "0x%lX",   (tmp & SDIO_SRW) >> 2);
	_PrintField("SMB",  "0x%lX",   (tmp & SDIO_SMB) >> 1);
	_PrintField("SDC",  "0x%lX",   (tmp & SDIO_SDC) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_CIS_PTR_REG, p, 3);
	_PrintField("CIS_PTR", "0x%06lX", tmp);
	addrCIS = tmp;
	tmp = 0;
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_BUS_SUSP_REG, p, 1);
	_PrintField("BR",   "0x%lX",   (tmp & SDIO_BR) >> 1);
	_PrintField("BS",   "0x%lX",   (tmp & SDIO_BS) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_FUN_SEL_REG, p, 1);
	_PrintField("DF",   "0x%lX",   (tmp & SDIO_DF) >> 7);
	_PrintField("FS",   "0x%lX",   (tmp & SDIO_FS) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_EXEC_REG, p, 1);
	_PrintField("EX",   "0x%lX",   (tmp & SDIO_EX) >> 0);
	_PrintField("EXM",  "0x%lX",   (tmp & SDIO_EXM) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_READY_REG, p, 1);
	_PrintField("RF",   "0x%lX",   (tmp & SDIO_RF) >> 1);
	_PrintField("RFM",  "0x%lX",   (tmp & SDIO_RFM) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_FN0_BLKSIZ_REG, p, 2);
	_PrintField("FN0_SIZE", "%lu", tmp);
	tmp = 0;
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_POWER_REG, p, 1);
	_PrintField("EMPC", "0x%lX",   (tmp & SDIO_EMPC) >> 1);
	_PrintField("SMPC", "0x%lX",   (tmp & SDIO_SMPC) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_HS_REG, p, 1);
	_PrintField("EHS",  "0x%lX",   (tmp & SDIO_EHS) >> 1);
	_PrintField("SHS",  "0x%lX",   (tmp & SDIO_SHS) >> 0);
	/* Metaformat */
	SdioFindTuples(pSd, addrCIS, 128, &addrManfID, &addrFuncE);
	if (addrManfID != 0) {
		SDIO_ReadDirect(pSd, SDIO_CIA, addrManfID, buf, 6);
		_PrintTitle("CISTPL_MANFID");
		_PrintField("MANF", "0x%04X", (uint16_t)buf[3] << 8 | buf[2]);
		_PrintField("CARD", "0x%04X", (uint16_t)buf[5] << 8 | buf[4]);
	}
	if (addrFuncE != 0) {
		SDIO_ReadDirect(pSd, SDIO_CIA, addrFuncE, buf, 6);
		_PrintTitle("CISTPL_FUNCE Fun0");
		_PrintField("BL_SIZE", "%u", (uint16_t)buf[4] << 8 | buf[3]);
		_PrintField("MAX_TRAN_SPD", "0x%02X", buf[5]);
	}
	/* I/O function 1 */
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_FBR_ADDR(1, SDIO_FBR_CIS_PTR),
	    p, 3);
	addrFuncE = 0;
	/* TODO Augment SdioFindTuples so it finds CISTPL_FUNCE for Function 1
	 * with Extended Data 01h */
	SdioFindTuples(pSd, tmp, 256, NULL, &addrFuncE);
	if (addrFuncE != 0) {
		SDIO_ReadDirect(pSd, SDIO_CIA, addrFuncE, buf, 16);
		_PrintTitle("CISTPL_FUNCE Fun1");
		_PrintField("MAX_BLK_SIZE", "%u", (uint16_t)buf[0xf] << 8
		    | buf[0xe]);
	}
}

/**
 * Display the content of the CID register
 * \param pSd  Pointer to SdCard instance.
 */
void
SD_DumpCID(const sSdCard *pSd)
{
	const uint8_t sd_device = (pSd->bCardType & CARD_TYPE_bmSDMMC)
	    == CARD_TYPE_bmSD;

	/* Function-only SDIO devices have no CID register */
	if ((pSd->bCardType & CARD_TYPE_bmSDMMC) == CARD_TYPE_bmUNKNOWN)
		return;

	_PrintTitle("Card IDentification");
	_PrintField("MID", "0x%02X", SD_CID_MID(pSd->CID));

	if (sd_device) {
		_PrintField("OID", "%c%c", (char) SD_CID_OID1(pSd->CID),
		    (char) SD_CID_OID0(pSd->CID));
		_PrintField("PNM", "%c%c%c%c%c", (char) SD_CID_PNM4(pSd->CID),
		    (char) SD_CID_PNM3(pSd->CID), (char) SD_CID_PNM2(pSd->CID),
		    (char) SD_CID_PNM1(pSd->CID), (char) SD_CID_PNM0(pSd->CID));
		_PrintField("PRV", "%u.%u", SD_CID_PRV1(pSd->CID),
		    SD_CID_PRV0(pSd->CID));
		_PrintField("PSN", "0x%02X%02X%02X%02X", SD_CID_PSN3(pSd->CID),
		    SD_CID_PSN2(pSd->CID), SD_CID_PSN1(pSd->CID),
		    SD_CID_PSN0(pSd->CID));
		_PrintField("MDT", "%u/%02u", 2000 + SD_CID_MDT_Y(pSd->CID),
		    SD_CID_MDT_M(pSd->CID));
	}
#ifndef SDMMC_TRIM_MMC
	else {
		uint16_t year = 1997 + MMC_CID_MDT_Y(pSd->CID);

		if (MMC_EXT_EXT_CSD_REV(pSd->EXT) >= 3) {
			_PrintField("CBX", "%u", eMMC_CID_CBX(pSd->CID));
			_PrintField("OID", "0x%02X", eMMC_CID_OID(pSd->CID));
		}
		else
			_PrintField("OID", "0x%04X", MMC_CID_OID(pSd->CID));
		_PrintField("PNM", "%c%c%c%c%c%c",
		    (char) MMC_CID_PNM5(pSd->CID),
		    (char) MMC_CID_PNM4(pSd->CID),
		    (char) MMC_CID_PNM3(pSd->CID),
		    (char) MMC_CID_PNM2(pSd->CID),
		    (char) MMC_CID_PNM1(pSd->CID),
		    (char) MMC_CID_PNM0(pSd->CID));
		_PrintField("PRV", "%u.%u", MMC_CID_PRV1(pSd->CID),
		    MMC_CID_PRV0(pSd->CID));
		_PrintField("PSN", "0x%02X%02X%02X%02X", MMC_CID_PSN3(pSd->CID),
		    MMC_CID_PSN2(pSd->CID), MMC_CID_PSN1(pSd->CID),
		    MMC_CID_PSN0(pSd->CID));
		if (MMC_EXT_EXT_CSD_REV(pSd->EXT) > 4 && year < 2010)
			year = year - 1997 + 2013;
		_PrintField("MDT", "%u/%02u", year, MMC_CID_MDT_M(pSd->CID));
	}
#endif

	_PrintField("CRC", "0x%02X", SD_CID_CRC(pSd->CID));
}

/**
 * Display the content of the CSD register
 * \param pSd  Pointer to SdCard instance.
 */
void
SD_DumpCSD(const sSdCard *pSd)
{
	const uint8_t sd_device = (pSd->bCardType & CARD_TYPE_bmSDMMC)
	    == CARD_TYPE_bmSD;
	const uint8_t sd_csd_v2 = sd_device
	    && SD_CSD_STRUCTURE(pSd->CSD) >= 0x1;

	_PrintTitle("Card-Specific Data");
	_PrintField("CSD_STRUCT", "0x%X", SD_CSD_STRUCTURE(pSd->CSD));
#ifndef SDMMC_TRIM_MMC
	if (!sd_device)
		_PrintField("SPEC_V", "0x%X", MMC_CSD_SPEC_VERS(pSd->CSD));
#endif
	_PrintField("TAAC", "0x%X", SD_CSD_TAAC(pSd->CSD));
	_PrintField("NSAC", "0x%X", SD_CSD_NSAC(pSd->CSD));
	_PrintField("TRAN_SPD", "0x%X", SD_CSD_TRAN_SPEED(pSd->CSD));
	_PrintField("CCC", "0x%X", SD_CSD_CCC(pSd->CSD));
	_PrintField("RD_BL_LEN", "0x%X", SD_CSD_READ_BL_LEN(pSd->CSD));
	_PrintField("RD_BL_PART", "%u", SD_CSD_READ_BL_PARTIAL(pSd->CSD));
	_PrintField("WR_BL_MALIGN", "%u", SD_CSD_WRITE_BLK_MISALIGN(pSd->CSD));
	_PrintField("RD_BL_MALIGN", "%u", SD_CSD_READ_BLK_MISALIGN(pSd->CSD));
	_PrintField("DSR_IMP", "%u", SD_CSD_DSR_IMP(pSd->CSD));
	_PrintField("C_SIZE", "0x%lX", sd_csd_v2 ? SD2_CSD_C_SIZE(pSd->CSD)
	    : SD_CSD_C_SIZE(pSd->CSD));
	if (!sd_csd_v2) {
		_PrintField("RD_CUR_MIN", "0x%X",
		    SD_CSD_VDD_R_CURR_MIN(pSd->CSD));
		_PrintField("RD_CUR_MAX", "0x%X",
		    SD_CSD_VDD_R_CURR_MAX(pSd->CSD));
		_PrintField("WR_CUR_MIN", "0x%X",
		    SD_CSD_VDD_W_CURR_MIN(pSd->CSD));
		_PrintField("WR_CUR_MAX", "0x%X",
		    SD_CSD_VDD_W_CURR_MAX(pSd->CSD));
		_PrintField("C_SIZE_MULT", "0x%X",
		    SD_CSD_C_SIZE_MULT(pSd->CSD));
	}
	if (sd_device) {
		_PrintField("ER_BL_EN", "%u", SD_CSD_ERASE_BLK_EN(pSd->CSD));
		_PrintField("SECT_SIZE", "0x%X", SD_CSD_SECTOR_SIZE(pSd->CSD));
	}
#ifndef SDMMC_TRIM_MMC
	else {
		_PrintField("ER_GRP_SIZE", "0x%X",
		    MMC_CSD_ERASE_GRP_SIZE(pSd->CSD));
		_PrintField("ER_GRP_MULT", "0x%X",
		    MMC_CSD_ERASE_GRP_MULT(pSd->CSD));
	}
#endif
#ifdef SDMMC_TRIM_MMC
	_PrintField("WP_GRP_SIZE", "0x%X", SD_CSD_WP_GRP_SIZE(pSd->CSD));
#else
	_PrintField("WP_GRP_SIZE", "0x%X", sd_device ?
	    SD_CSD_WP_GRP_SIZE(pSd->CSD) : MMC_CSD_WP_GRP_SIZE(pSd->CSD));
#endif
	_PrintField("WP_GRP_EN", "%u", SD_CSD_WP_GRP_ENABLE(pSd->CSD));
#ifndef SDMMC_TRIM_MMC
	if (!sd_device)
		_PrintField("DEF_ECC", "0x%X", MMC_CSD_DEFAULT_ECC(pSd->CSD));
#endif
	_PrintField("R2W_FACT", "0x%X", SD_CSD_R2W_FACTOR(pSd->CSD));
	_PrintField("WR_BL_LEN", "0x%X", SD_CSD_WRITE_BL_LEN(pSd->CSD));
	_PrintField("WR_BL_PART", "%u", SD_CSD_WRITE_BL_PARTIAL(pSd->CSD));
	_PrintField("FILE_FMT_GRP", "%u", SD_CSD_FILE_FORMAT_GRP(pSd->CSD));
	_PrintField("COPY", "%u", SD_CSD_COPY(pSd->CSD));
	_PrintField("PERM_WP", "%u", SD_CSD_PERM_WRITE_PROTECT(pSd->CSD));
	_PrintField("TMP_WP", "%u", SD_CSD_TMP_WRITE_PROTECT(pSd->CSD));
	_PrintField("FILE_FMT", "0x%X", SD_CSD_FILE_FORMAT(pSd->CSD));
#ifndef SDMMC_TRIM_MMC
	if (!sd_device)
		_PrintField("ECC", "0x%X", MMC_CSD_ECC(pSd->CSD));
#endif
	_PrintField("CRC", "0x%X", SD_CSD_CRC(pSd->CSD));
}

/**
 * Display the content of the EXT_CSD register
 * \param pExtCSD Pointer to extended CSD data.
 */
void
SD_DumpExtCSD(const uint8_t *pExtCSD)
{
	_PrintTitle("Extended Device Specific Data");
	_PrintField("S_CMD_SET", "0x%X", MMC_EXT_S_CMD_SET(pExtCSD));
	_PrintField("BOOT_INFO", "0x%X", MMC_EXT_BOOT_INFO(pExtCSD));
	_PrintField("BOOT_SIZE_MULTI", "0x%X",
	    MMC_EXT_BOOT_SIZE_MULTI(pExtCSD));
	_PrintField("ACC_SIZE", "0x%X", MMC_EXT_ACC_SIZE(pExtCSD));
	_PrintField("HC_ER_GRP_SIZE", "0x%X",
	    MMC_EXT_HC_ERASE_GRP_SIZE(pExtCSD));
	_PrintField("ER_TIMEOUT_MULT", "0x%X",
	    MMC_EXT_ERASE_TIMEOUT_MULT(pExtCSD));
	_PrintField("REL_WR_SEC_C", "0x%X", MMC_EXT_REL_WR_SEC_C(pExtCSD));
	_PrintField("HC_WP_GRP_SIZE", "0x%X", MMC_EXT_HC_WP_GRP_SIZE(pExtCSD));
	_PrintField("S_C_VCC", "0x%X", MMC_EXT_S_C_VCC(pExtCSD));
	_PrintField("S_C_VCCQ", "0x%X", MMC_EXT_S_C_VCCQ(pExtCSD));
	_PrintField("S_A_TIMEOUT", "0x%X", MMC_EXT_S_A_TIMEOUT(pExtCSD));
	_PrintField("SEC_CNT", "0x%lX", MMC_EXT_SEC_COUNT(pExtCSD));
	_PrintField("MIN_PE_W_8_52", "0x%X", MMC_EXT_MIN_PERF_W_8_52(pExtCSD));
	_PrintField("MIN_PE_R_8_52", "0x%X", MMC_EXT_MIN_PERF_R_8_52(pExtCSD));
	_PrintField("MIN_PE_W_8_26_4_52", "0x%X",
	    MMC_EXT_MIN_PERF_W_8_26_4_52(pExtCSD));
	_PrintField("MIN_PE_R_8_26_4_52", "0x%X",
	    MMC_EXT_MIN_PERF_R_8_26_4_52(pExtCSD));
	_PrintField("MIN_PE_W_4_26", "0x%X", MMC_EXT_MIN_PERF_W_4_26(pExtCSD));
	_PrintField("MIN_PE_R_4_26", "0x%X", MMC_EXT_MIN_PERF_R_4_26(pExtCSD));
	_PrintField("PWR_CL_26_360", "0x%X", MMC_EXT_PWR_CL_26_360(pExtCSD));
	_PrintField("PWR_CL_52_360", "0x%X", MMC_EXT_PWR_CL_52_360(pExtCSD));
	_PrintField("PWR_CL_26_195", "0x%X", MMC_EXT_PWR_CL_26_195(pExtCSD));
	_PrintField("PWR_CL_52_195", "0x%X", MMC_EXT_PWR_CL_52_195(pExtCSD));
	_PrintField("DRV_STR", "0x%X", MMC_EXT_DRV_STRENGTH(pExtCSD));
	_PrintField("CARD_TYPE", "0x%X", MMC_EXT_CARD_TYPE(pExtCSD));
	_PrintField("CSD_STRUCT", "0x%X", MMC_EXT_CSD_STRUCTURE(pExtCSD));
	_PrintField("EXT_CSD_REV", "0x%X", MMC_EXT_EXT_CSD_REV(pExtCSD));
	_PrintField("CMD_SET", "0x%X", MMC_EXT_CMD_SET(pExtCSD));
	_PrintField("CMD_SET_REV", "0x%X", MMC_EXT_CMD_SET_REV(pExtCSD));
	_PrintField("PWR_CLASS", "0x%X", MMC_EXT_POWER_CLASS(pExtCSD));
	_PrintField("HS_TIM", "0x%X", MMC_EXT_HS_TIMING(pExtCSD));
	_PrintField("BUS_WIDTH", "0x%X", MMC_EXT_BUS_WIDTH(pExtCSD));
	_PrintField("ER_MEM_CONT", "0x%X", MMC_EXT_ERASED_MEM_CONT(pExtCSD));
	_PrintField("BOOT_CFG", "0x%X", MMC_EXT_BOOT_CONFIG(pExtCSD));
	_PrintField("BOOT_BUS_WIDTH", "0x%X", MMC_EXT_BOOT_BUS_WIDTH(pExtCSD));
	_PrintField("ER_GRP_DEF", "0x%X", MMC_EXT_ERASE_GROUP_DEF(pExtCSD));
}

/**
 * Display the content of the SCR register
 * \param pSCR  Pointer to SCR data.
 */
void
SD_DumpSCR(const uint8_t *pSCR)
{
	_PrintTitle("SD Card Configuration");
	_PrintField("SCR_STRUCT", "0x%X", SD_SCR_STRUCTURE(pSCR));
	_PrintField("SD_SPEC", "0x%X", SD_SCR_SD_SPEC(pSCR));
	_PrintField("SD_SPEC3", "%u", SD_SCR_SD_SPEC3(pSCR));
	_PrintField("SD_SPEC4", "%u", SD_SCR_SD_SPEC4(pSCR));
	_PrintField("DATA_ST_AFTER_ER", "%u",
	    SD_SCR_DATA_STAT_AFTER_ERASE(pSCR));
	_PrintField("SD_SEC", "0x%X", SD_SCR_SD_SECURITY(pSCR));
	_PrintField("EX_SEC", "0x%X", SD_SCR_EX_SECURITY(pSCR));
	_PrintField("SD_BUS_WIDTHS", "0x%X", SD_SCR_SD_BUS_WIDTHS(pSCR));
	_PrintField("CMD20", "%u", SD_SCR_CMD20_SUPPORT(pSCR));
	_PrintField("CMD23", "%u", SD_SCR_CMD23_SUPPORT(pSCR));
	_PrintField("CMD48/49", "%u", SD_SCR_CMD48_SUPPORT(pSCR));
	_PrintField("CMD58/59", "%u", SD_SCR_CMD58_SUPPORT(pSCR));
}

/**
 * Display the content of the SD Status Register
 * \param pSSR  Pointer to SSR data.
 */
void
SD_DumpSSR(const uint8_t *pSSR)
{
	_PrintTitle("SD Status");
	_PrintField("DAT_BUS_WIDTH", "0x%X", SD_SSR_DAT_BUS_WIDTH(pSSR));
	_PrintField("SEC_MODE", "%u", SD_SSR_SECURED_MODE(pSSR));
	_PrintField("SD_CARD_TYPE", "0x%04X", SD_SSR_CARD_TYPE(pSSR));
	_PrintField("PAREA_SIZE", "%lu",
	    SD_SSR_SIZE_OF_PROTECTED_AREA(pSSR));
	_PrintField("SPD_CLASS", "0x%02X", SD_SSR_SPEED_CLASS(pSSR));
	_PrintField("UHS_SPD_GRADE", "0x%X", SD_SSR_UHS_SPEED_GRADE(pSSR));
	_PrintField("PE_MOVE", "%u MB/sec", SD_SSR_PERFORMANCE_MOVE(pSSR));
	_PrintField("AU_SIZE", "0x%X", SD_SSR_AU_SIZE(pSSR));
	_PrintField("UHS_AU_SIZE", "0x%X", SD_SSR_UHS_AU_SIZE(pSSR));
	_PrintField("ER_SIZE", "%u AU", SD_SSR_ERASE_SIZE(pSSR));
	_PrintField("ER_TIMEOUT", "%u sec", SD_SSR_ERASE_TIMEOUT(pSSR));
	_PrintField("ER_OFFS", "%u sec", SD_SSR_ERASE_OFFSET(pSSR));
}

/**
 * Provide a textual name matching the specified IO Control
 * \param dwCtrl  IO Control code (SDMMC_IOCTL_xxx).
 */
const char *
SD_StringifyIOCtrl(uint32_t dwCtrl)
{
	const uint8_t bound = ARRAY_SIZE(sdmmcIOCtrlNames);
	uint8_t ix;

	for (ix = 0; ix < bound; ix++) {
		if (dwCtrl == (uint32_t)sdmmcIOCtrlNames[ix].key)
			return sdmmcIOCtrlNames[ix].name;
	}

	return sdmmcInvalidCode;
}

/**
 * Provide a textual name matching the specified return code
 * \param dwRCode  Return code, from the eSDMMC_RC enumeration.
 */
const char *
SD_StringifyRetCode(uint32_t dwRCode)
{
	const uint8_t bound = ARRAY_SIZE(sdmmcRCodeNames);
	uint8_t ix;

	for (ix = 0; ix < bound; ix++) {
		if (dwRCode == (uint32_t)sdmmcRCodeNames[ix].key)
			return sdmmcRCodeNames[ix].name;
	}

	return sdmmcInvalidCode;
}

uint8_t
mmc_configure_partition(sSdCard * pSd, uint32_t config)
{
	uint8_t error;
	uint32_t status;

	/* Check if MMC */
	if ((pSd->bCardType & CARD_TYPE_bmSDMMC) != CARD_TYPE_bmMMC) {
		trace_error("mmc_configure_partition: Not an MMC\n\r");
		return SDMMC_ERROR_NOT_SUPPORT;
	}

	if (MMC_EXT_BOOT_SIZE_MULTI(pSd->EXT)) {
		/* Try switch to HS mode */
		MmcCmd6Arg cmd6Arg = {
			.access = 0x3,                  /* Write byte in the EXT_CSD register */
			.index = MMC_EXT_BOOT_CONFIG_I, /* Target byte in EXT_CSD */
			.value = config,                /* Byte value */
		};
		error = MmcCmd6(pSd, &cmd6Arg, &status);
		if (error) {
			trace_error("mmc_configure_partition.Cmd6: %d\n\r", error);
			return SDMMC_ERROR;
		} else if (status & STATUS_MMC_SWITCH) {
			trace_error("mmc_configure_partition: %x\n\r", (unsigned)status);
			return SDMMC_ERROR_NOT_SUPPORT;
		}
	} else {
		trace_error("mmc_configure_partition: MMC without boot partition support\n\r");
		return SDMMC_ERROR_NOT_SUPPORT;
	}

	return SDMMC_OK;
}


uint8_t
mmc_configure_boot_bus(sSdCard * pSd, uint32_t config)
{
	uint8_t error;
	uint32_t status;

	/* Check if MMC */
	if ((pSd->bCardType & CARD_TYPE_bmSDMMC) != CARD_TYPE_bmMMC) {
		trace_error("mmc_configure_boot_bus: not an MMC\n\r");
		return SDMMC_ERROR_NOT_SUPPORT;
	}

	if (MMC_EXT_BOOT_SIZE_MULTI(pSd->EXT)) {
		/* Try switch to HS mode */
		MmcCmd6Arg cmd6Arg = {
			.access = 0x3,                     /* Write byte in the EXT_CSD register */
			.index = MMC_EXT_BOOT_BUS_WIDTH_I, /* Target byte in EXT_CSD */
			.value = config,                   /* Byte value */
		};
		error = MmcCmd6(pSd, &cmd6Arg, &status);
		if (error) {
			trace_error("mmc_configure_boot_bus.Cmd6: %d\n\r", error);
			return SDMMC_ERROR;
		} else if (status & STATUS_MMC_SWITCH) {
			trace_error("mmc_configure_boot_bus: %x\n\r", (unsigned)status);
			return SDMMC_ERROR_NOT_SUPPORT;
		}
	} else {
		trace_error("mmc_configure_boot_bus: MMC without boot partition support\n\r");
		return SDMMC_ERROR_NOT_SUPPORT;
	}

	return SDMMC_OK;
}

/**@}*/
