/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation

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

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include <assert.h>
#include <string.h>
#include <stdint.h>
#include "compiler.h"
#include "timer.h"
#include "libsdmmc.h"
#include "sdmmc_trace.h"

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
/**     @}*/

/*----------------------------------------------------------------------------
 *         Macros
 *----------------------------------------------------------------------------*/

/** Return SD/MMC card address */
#define CARD_ADDR(pSd)          (pSd->wAddress)

/** Return SD/MMC card block size (Default size now, 512B) */
#define BLOCK_SIZE(pSd)         (pSd->wCurrBlockLen)

/** Convert block address to SD/MMC command parameter */
#define SD_ADDRESS(pSd, address) \
    ( ((pSd)->dwTotalSize >= 0xFFFFFFFF) ? \
                            (address):((address) << 9) )

#define MMC_ADDRESS(pSd, address) \
    ( ((pSd)->dwTotalSize >= 0x7FFFFFFF) ? \
                            (address):((address) << 9) )

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

/** Check if MMC card support HS mode (4.0 or later) */
#define MMC_IsHsModeSupported(pSd)  \
    (MMC_IsCSDVer1_2(pSd)&&(MMC_EXT_CARD_TYPE(pSd->EXT)&0x2))

/*----------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

/** SD/MMC transfer rate unit codes (10K) list */
static const uint32_t sdmmcTransUnits[7] = {
	10, 100, 1000, 10000,
	0, 0, 0
};

/** SD transfer multiplier factor codes (1/10) list */
static const uint32_t sdTransMultipliers[16] = {
	0, 10, 12, 13, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 70, 80
};

/** MMC transfer multiplier factor codes (1/10) list */
static const uint32_t mmcTransMultipliers[16] = {
	0, 10, 12, 13, 15, 20, 26, 30, 35, 40, 45, 52, 55, 60, 70, 80
};

#ifdef NOTRACE
static const char sdmmcEmptyString[] = "";
#else
static const char sdmmcInvalidIOCtrl[] = "!Invalid IO Control!";
static const struct stringEntry_s sdmmcIOCtrlNames[] = {
	{ SDMMC_IOCTL_BUSY_CHECK,	"SDMMC_IOCTL_BUSY_CHECK",	},
	{ SDMMC_IOCTL_POWER,		"SDMMC_IOCTL_POWER",		},
	{ SDMMC_IOCTL_CANCEL_CMD,	"SDMMC_IOCTL_CANCEL_CMD",	},
	{ SDMMC_IOCTL_RESET,		"SDMMC_IOCTL_RESET",		},
	{ SDMMC_IOCTL_SET_CLOCK,	"SDMMC_IOCTL_SET_CLOCK",	},
	{ SDMMC_IOCTL_SET_BUSMODE,	"SDMMC_IOCTL_SET_BUSMODE",	},
	{ SDMMC_IOCTL_SET_HSMODE,	"SDMMC_IOCTL_SET_HSMODE",	},
	{ SDMMC_IOCTL_SET_BOOTMODE,	"SDMMC_IOCTL_SET_BOOTMODE",	},
	{ SDMMC_IOCTL_SET_LENPREFIX,	"SDMMC_IOCTL_SET_LENPREFIX",	},
	{ SDMMC_IOCTL_GET_CLOCK,	"SDMMC_IOCTL_GET_CLOCK",	},
	{ SDMMC_IOCTL_GET_BUSMODE,	"SDMMC_IOCTL_GET_BUSMODE",	},
	{ SDMMC_IOCTL_GET_HSMODE,	"SDMMC_IOCTL_GET_HSMODE",	},
	{ SDMMC_IOCTL_GET_BOOTMODE,	"SDMMC_IOCTL_GET_BOOTMODE",	},
	{ SDMMC_IOCTL_GET_XFERCOMPL,	"SDMMC_IOCTL_GET_XFERCOMPL",	},
};

static const char sdmmcInvalidRCode[] = "!Invalid return code!";
static const struct stringEntry_s sdmmcRCodeNames[] = {
	{ SDMMC_SUCCESS,		"SDMMC_OK",			},
	{ SDMMC_ERROR_LOCKED,		"SDMMC_ERROR_LOCKED",		},
	{ SDMMC_ERROR_BUSY,		"SDMMC_ERROR_BUSY",		},
	{ SDMMC_ERROR_NORESPONSE,	"SDMMC_ERROR_NO_RESPONSE",	},
	{ SDMMC_CHANGED,		"SDMMC_OK_CHANGED",		},
	{ SDMMC_ERROR,			"SDMMC_ERROR",			},
	{ SDMMC_ERR_IO,			"SDMMC_ERROR_IO",		},
	{ SDMMC_ERR_RESP,		"SDMMC_ERROR_RESP",		},
	{ SDMMC_ERROR_NOT_INITIALIZED,	"SDMMC_ERROR_NOT_INITIALIZED",	},
	{ SDMMC_ERROR_PARAM,		"SDMMC_ERROR_PARAM",		},
	{ SDMMC_ERROR_STATE,		"SDMMC_ERROR_STATE",		},
	{ SDMMC_ERROR_USER_CANCEL,	"SDMMC_ERROR_USER_CANCEL",	},
	{ SDMMC_ERROR_NOT_SUPPORT,	"SDMMC_ERROR_NO_SUPPORT",	},
};
#endif

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

/**
 * Delay some loop
 */
static void
Delay(volatile unsigned int loop)
{
	for (; loop > 0; loop--) ;
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
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	sSdHalFunctions *pHal = pSd->pHalf;
	void *pDrv = pSd->pDrv;
	uint8_t bRc;

	pCmd->fCallback = fCallback;
	pCmd->pArg = pCbArg;
	bRc = pHal->fCommand(pSd->pDrv, pCmd);

	if (fCallback == NULL) {
		uint32_t busy = 1;
		int32_t to = 0;
		for (; busy == 1;) {
			pHal->fIOCtrl(pDrv, SDMMC_IOCTL_BUSY_CHECK,
				      (uint32_t) & busy);
#if 1
			if (++to > 0x100000 + 0x100000 * pCmd->wNbBlocks / 1024) {
				pHal->fIOCtrl(pDrv, SDMMC_IOCTL_CANCEL_CMD, 0);
				pCmd->bStatus = SDMMC_NO_RESPONSE;
				break;
			}
#endif
		}
		return pCmd->bStatus;
	}

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
static uint8_t
_HwGetHsMode(sSdCard * pSd)
{
	sSdHalFunctions *pHal = pSd->pHalf;
	void *pDrv = pSd->pDrv;
	uint32_t hsMode = 0;
	pHal->fIOCtrl(pDrv, SDMMC_IOCTL_GET_HSMODE, (uint32_t) & hsMode);
	return hsMode;
}

/**
 */
static uint8_t
_HwSetHsMode(sSdCard * pSd, uint8_t newHsMode)
{
	sSdHalFunctions *pHal = pSd->pHalf;
	void *pDrv = pSd->pDrv;
	uint32_t hsMode = newHsMode;
	uint32_t rc;
	rc = pHal->fIOCtrl(pDrv, SDMMC_IOCTL_SET_HSMODE, (uint32_t) & hsMode);
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
		if (error) {
			trace_error("SdioFindTuples.RdDirect: %d\n\r", error);
			return error;
		}
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
		      const uint32_t * unitCodes, const uint32_t * multiCodes)
{
	uint32_t speed;
	uint8_t unitI, mulI;

	/* Unit code is valid ? */
	unitI = (code & 0x7);
	if (unitCodes[unitI] == 0)
		return 0;

	/* Multi code is valid ? */
	mulI = (code >> 3) & 0xF;
	if (multiCodes[mulI] == 0)
		return 0;

	speed = unitCodes[unitI] * multiCodes[mulI];
	return speed;
}

/**
 * Initialization delay: The maximum of 1 msec, 74 clock cycles and supply ramp
 * up time.
 * Returns the command transfer result (see SendMciCommand).
 * \param pSd Pointer to \ref sSdCard instance.
 */
static inline uint8_t
Pon(sSdCard * pSd)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	trace_debug("PwrOn()\n\r");
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
static inline uint8_t
Cmd0(sSdCard * pSd, uint8_t arg)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	trace_debug("Cmd0()\n\r");
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
 * \param pSd Pointer to \ref sSdCard instance.
 * \param pOCR Pointer to fill OCR value to send and get.
 */
static inline uint8_t
Cmd1(sSdCard * pSd, uint8_t * pHd)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;
	uint32_t dwArg;

	trace_debug("Cmd1()\n\r");
	_ResetCmd(pCmd);

	dwArg = SD_HOST_VOLTAGE_RANGE | MMC_OCR_ACCESS_SECTOR;

	/* Fill command */
	pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(3)
	    | SDMMC_CMD_bmOD;
	pCmd->bCmd = 1;
	pCmd->dwArg = dwArg;
	pCmd->pResp = &dwArg;

	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);

	/* Check result */
	if (bRc)
		return bRc;

	if (dwArg & SD_OCR_BUSY) {
		*pHd = 0;
		if ((dwArg & MMC_OCR_ACCESS_MODE) == MMC_OCR_ACCESS_SECTOR) {
			*pHd = 1;
		}
		return 0;
	}
	return SDMMC_ERROR_NOT_INITIALIZED;
}

/**
 * Asks any card to send the CID numbers
 * on the CMD line (any card that is
 * connected to the host will respond)
 * Returns the command transfer result (see SendMciCommand).
 * \param pSd  Pointer to a SD card driver instance.
 * \param pCID Pointer to buffer for storing the CID numbers.
 */
static inline uint8_t
Cmd2(sSdCard * pSd)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	trace_debug("Cmd2()\n\r");
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

	trace_debug("Cmd3()\n\r");
	_ResetCmd(pCmd);

	/* Fill command */
	pCmd->bCmd = 3;
	pCmd->pResp = &dwResp;

	if (pSd->bCardType == CARD_MMC || pSd->bCardType == CARD_MMCHD) {
		uint16_t wNewAddr = CARD_ADDR(pSd) + 1;
		if (wNewAddr == 0)
			wNewAddr++;
		pCmd->dwArg = wNewAddr << 16;

		pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(1) | SDMMC_CMD_bmOD;
		bRc = _SendCmd(pSd, NULL, NULL);
		if (bRc == SDMMC_OK) {
			CARD_ADDR(pSd) = wNewAddr;
		}
	} else {
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
static uint8_t
Cmd5(sSdCard * pSd, uint32_t * pIo)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	trace_debug("Cmd5()\n\r");
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

/**
 * Switches the mode of operation of the selected card.
 * CMD6 is valid under the "trans" state.
 * \return The command transfer result (see SendMciCommand).
 * \param  pSd         Pointer to a SD/MMC card driver instance.
 * \param  pSwitchArg  Pointer to a MmcCmd6Arg instance.
 * \param  pStatus     Pointer to where the 512bit status is returned.
 * \param  pResp       Pointer to where the response is returned.
 */
static uint8_t
SdCmd6(sSdCard * pSd,
       const void *pSwitchArg, uint32_t * pStatus, uint32_t * pResp)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;
	SdCmd6Arg *pSdSwitch;

	assert(pSd);
	assert(pSwitchArg);

	trace_debug("Cmd6()\n\r");
	_ResetCmd(pCmd);

	pSdSwitch = (SdCmd6Arg *) pSwitchArg;
	pCmd->bCmd = 6;
	pCmd->cmdOp.wVal = SDMMC_CMD_CDATARX(1);
	pCmd->dwArg = (pSdSwitch->mode << 31)
	    | (pSdSwitch->reserved << 30)
	    | (pSdSwitch->reserveFG6 << 20)
	    | (pSdSwitch->reserveFG5 << 16)
	    | (pSdSwitch->reserveFG4 << 12)
	    | (pSdSwitch->reserveFG3 << 8)
	    | (pSdSwitch->command << 4)
	    | (pSdSwitch->accessMode << 0);
	if (pStatus) {
		pCmd->wBlockSize = 512 / 8;
		pCmd->wNbBlocks = 1;
		pCmd->pData = (uint8_t *) pStatus;
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

	trace_debug("Cmd6()\n\r");
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

	trace_debug("Cmd7()\n\r");
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
	uint32_t dwResp;
	uint8_t bRc;

	trace_debug("Cmd8()\n\r");
	_ResetCmd(pCmd);

	/* Fill command information */
	pCmd->bCmd = 8;
	pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(7)
	    | SDMMC_CMD_bmOD;
	pCmd->dwArg = (supplyVoltage << 8) | (0xAA);
	pCmd->pResp = &dwResp;

	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);

	/* Check result */
	if (bRc == SDMMC_ERROR_NORESPONSE) {
		return SDMMC_ERROR_NORESPONSE;
	}
	/* SD_R7
	 * Bit 0 - 7: check pattern (echo-back)
	 * Bit 8 -11: voltage accepted
	 */
	else if (!bRc &&
		 ((dwResp & 0x00000FFF) ==
		  ((uint32_t) (supplyVoltage << 8) | 0xAA))) {
		return 0;
	} else {
		return SDMMC_ERROR;
	}
}

/**
 * SEND_EXT_CSD, to get EXT_CSD register as a block of data.
 * Valid under "trans" state.
 * \param pSd   Pointer to a SD card driver instance.
 * \param pEXT  512 byte buffer pointer for EXT_CSD data.
 * \return 0 if successful;
 *         otherwise returns SD_ERROR_NORESPONSE if the card did not answer
 *         the command, or SDMMC_ERROR.
 */
static uint8_t
MmcCmd8(sSdCard * pSd, uint8_t * pEXT)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	trace_debug("Cmd8()\n\r");
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

	trace_debug("Cmd9()\n\r");
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
 * Forces the card to stop transmission
 * \param pSd      Pointer to a SD card driver instance.
 * \param pStatus  Pointer to a status variable.
 */
static uint8_t
Cmd12(sSdCard * pSd, uint32_t * pStatus)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	trace_debug("Cmd12()\n\r");
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

	trace_debug("Cmd13()\n\r");
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

	trace_debug("Cmd16()\n\r");
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
 * \param pData     Pointer to the DW aligned buffer to be filled.
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

	trace_debug("Cmd17()\n\r");
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
 * \param pData     Pointer to the DW aligned buffer to be filled.
 * \param len       Length of data in byte
 * \param pStatus   Pointer response buffer as status return.
 */
static uint8_t
Cmd14(sSdCard * pSd, uint8_t * pData, uint8_t len, uint32_t * pStatus)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	trace_debug("Cmd14()\n\r");
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
 * \param pData     Pointer to the DW aligned buffer to be filled.
 * \param len       Length of data in byte
 * \param pStatus   Pointer response buffer as status return.
*/
static uint8_t
Cmd19(sSdCard * pSd, uint8_t * pData, uint8_t len, uint32_t * pStatus)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	trace_debug("Cmd19()\n\r");
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

/**
 * Continously transfers datablocks from card to host until interrupted by a
 * STOP_TRANSMISSION command.
 * \param pSd       Pointer to a SD card driver instance.
 * \param nbBlocks  Number of blocks to send.
 * \param pData     Pointer to the DW aligned buffer to be filled.
 * \param address   Data Address on SD/MMC card.
 * \param pStatus   Pointer to the response status.
 * \param fCallback Pointer to optional callback invoked on command end.
 *                  NULL:    Function return until command finished.
 *                  Pointer: Return immediately and invoke callback at end.
 *                  Callback argument is fixed to a pointer to sSdCard instance.
 */
static uint8_t
Cmd18(sSdCard * pSd,
      uint16_t nbBlock,
      uint8_t * pData,
      uint32_t address, uint32_t * pStatus, fSdmmcCallback callback)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	trace_debug("Cmd18()\n\r");
	_ResetCmd(pCmd);

	/* Fill command */
	pCmd->cmdOp.wVal = SDMMC_CMD_CDATARX(1);
	pCmd->bCmd = 18;
	pCmd->dwArg = address;
	pCmd->pResp = pStatus;
	pCmd->wBlockSize = BLOCK_SIZE(pSd);
	pCmd->wNbBlocks = nbBlock;
	pCmd->pData = pData;
	pCmd->fCallback = callback;
	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
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

	trace_debug("Cmd23()\n\r");
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
 * \param pData     Pointer to the DW aligned buffer to be filled.
 * \param address   Data Address on SD/MMC card.
 * \param pStatus   Pointer to response buffer as status.
 * \param fCallback Pointer to optional callback invoked on command end.
 *                  NULL:    Function return until command finished.
 *                  Pointer: Return immediately and invoke callback at end.
 *                  Callback argument is fixed to a pointer to sSdCard instance.
 */
static inline uint8_t
Cmd24(sSdCard * pSd,
      uint8_t * pData,
      uint32_t address, uint32_t * pStatus, fSdmmcCallback callback)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	trace_debug("Cmd24()\n\r");
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
 * \param pData     Pointer to the DW aligned buffer to be filled.
 * \param address   Data Address on SD/MMC card.
 * \param pStatus   Pointer to the response buffer as status.
 * \param fCallback Pointer to optional callback invoked on command end.
 *                  NULL:    Function return until command finished.
 *                  Pointer: Return immediately and invoke callback at end.
 *                  Callback argument is fixed to a pointer to sSdCard instance.
 */
static uint8_t
Cmd25(sSdCard * pSd,
      uint16_t nbBlock,
      uint8_t * pData,
      uint32_t address, uint32_t * pStatus, fSdmmcCallback callback)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	trace_debug("Cmd25()\n\r");
	_ResetCmd(pCmd);

	/* Fill command */
	pCmd->cmdOp.wVal = SDMMC_CMD_CDATATX(1);
	pCmd->bCmd = 25;
	pCmd->dwArg = address;
	pCmd->pResp = pStatus;
	pCmd->wBlockSize = BLOCK_SIZE(pSd);
	pCmd->wNbBlocks = nbBlock;
	pCmd->pData = pData;
	pCmd->fCallback = callback;
	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
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

	trace_debug("Cmd52()\n\r");
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
	pArg53 = (SdioCmd53Arg *) pArgResp;
	pArg53->rwFlag = wrFlag;
	pArg53->functionNum = funcNb;
	pArg53->blockMode = blockMode;
	pArg53->opCode = incAddr;
	pArg53->regAddress = addr;
	pArg53->count = len;

	trace_debug("Cmd53()\n\r");

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
	} else {
		/* Force byte mode */
		pCmd->wBlockSize = 0;
		//pCmd->wBlockSize = 1;
	}
	pCmd->dwArg = *pArgResp;
	pCmd->pResp = pArgResp;
	pCmd->pData = pIoData;
	pCmd->wNbBlocks = len;
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

	trace_debug("Cmd55()\n\r");
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
 * Should be invoked after SdmmcCmd55().
 * \param pSd     Pointer to a SD card driver instance.
 * \param arg     Argument for this command.
 * \param pStatus Pointer to buffer for command response as status.
 * \return the command transfer result (see SendMciCommand).
 */
static uint8_t
SdAcmd6(sSdCard * pSd, uint32_t arg, uint32_t * pStatus)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	trace_debug("Acmd6()\n\r");
	_ResetCmd(pCmd);

	/* Fill command information */
	pCmd->bCmd = 6;
	pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(1);
	pCmd->pResp = pStatus;
	pCmd->dwArg = arg;

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
	uint8_t error;
	uint32_t arg;
	error = Cmd55(pSd, CARD_ADDR(pSd));
	if (error) {
		trace_error("Acmd6.cmd55:%d\n\r", error);
		return error;
	}
	arg = (busWidth == 4)
	    ? SD_ST_DATA_BUS_WIDTH_4BIT : SD_ST_DATA_BUS_WIDTH_1BIT;
	return SdAcmd6(pSd, arg, NULL);
}

/**
 * Asks to all cards to send their operations conditions.
 * Returns the command transfer result (see SendMciCommand).
 * Should be invoked after SdmmcCmd55().
 * \param pSd   Pointer to a SD card driver instance.
 * \param pOpIo Pointer to argument that should be sent and OCR content.
 */
static uint8_t
SdAcmd41(sSdCard * pSd, uint32_t * pOpIo)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t bRc;

	trace_debug("Acmd41()\n\r");
	_ResetCmd(pCmd);

	/* Fill command information */
	pCmd->bCmd = 41;
	pCmd->cmdOp.wVal = SDMMC_CMD_CNODATA(3);
	pCmd->dwArg = *pOpIo;
	pCmd->pResp = pOpIo;

	/* Send command */
	bRc = _SendCmd(pSd, NULL, NULL);
	return bRc;
}

/**
 * Asks to all cards to send their operations conditions.
 * Returns the command transfer result (see SendCommand).
 * \param pSd  Pointer to a SD card driver instance.
 * \param hcs  Shall be true if Host support High capacity.
 * \param pCCS  Set the pointed flag to 1 if hcs != 0 and SD OCR CCS flag is set.
 */
static uint8_t
Acmd41(sSdCard * pSd, uint8_t hcs, uint8_t * pCCS)
{
	uint8_t error;
	uint32_t arg;
	do {
		error = Cmd55(pSd, 0);
		if (error) {
			trace_error("Acmd41.cmd55:%d\n\r", error);
			return error;
		}
		arg = SD_HOST_VOLTAGE_RANGE;
		if (hcs)
			arg |= SD_OCR_CCS;
		error = SdAcmd41(pSd, &arg);
		if (error) {
			trace_error("Acmd41.cmd41:%d\n\r", error);
			return error;
		}
		*pCCS = ((arg & SD_OCR_CCS) != 0);
	} while ((arg & SD_OCR_BUSY) != SD_OCR_BUSY);
	return 0;
}

/**
 * From the selected card get its SD CARD Configuration Register (SCR).
 * ACMD51 is valid under the Transfer state.
 * \param pSd  Pointer to a SD card driver instance.
 * \param pCCS  Pointer to an 8-byte buffer receiving the contents of the SCR.
 * \param pResp  Pointer to where the response is returned.
 * \return The command transfer result (see SendCommand).
 */
static uint8_t
Acmd51(sSdCard * pSd, uint8_t * pSCR, uint32_t * pResp)
{
	sSdmmcCommand *pCmd = &pSd->sdCmd;
	uint8_t error;

	assert(pSd);

	error = Cmd55(pSd, CARD_ADDR(pSd));
	if (error) {
		trace_error("Acmd51.cmd55:%u\n\r", error);
		return error;
	}

	trace_debug("Acmd51()\n\r");
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
	if (error) {
		trace_error("Acmd51.cmd51:%u\n\r", error);
		return error;
	}
	return 0;
}

#if 0
/**
 * Continue to transfer datablocks from card to host until interrupted by a
 * STOP_TRANSMISSION command.
 * \param pSd  Pointer to a SD card driver instance.
 * \param blockSize Block size (shall be set to 512 in case of high capacity).
 * \param nbBlock   Number of blocks to send.
 * \param pData     Pointer to the application buffer to be filled.
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
 * Try SW Reset several times (CMD0 with ARG 0)
 * \param pSd      Pointer to a SD card driver instance.
 * \param retry    Retry times.
 * \return 0 or MCI error code.
 */
static uint8_t
SwReset(sSdCard * pSd, uint32_t retry)
{
	uint32_t i;
	uint8_t error = 0;

	for (i = 0; i < retry; i++) {
		error = Cmd0(pSd, 0);
		if (error != SDMMC_ERROR_NORESPONSE)
			break;
	}
	return error;
}

/**
 * Stop TX/RX
 */

#if defined ( __ICCARM__ )	/* IAR Ewarm */
#pragma location = "region_dma_nocache"
#elif defined (  __GNUC__  )	/* GCC CS3 */
__attribute__ ((__section__(".region_dma_nocache")))
#endif
uint32_t status1;

static uint8_t
_StopCmd(sSdCard * pSd)
{
	//uint32_t status, state;
	uint32_t state;
	volatile uint32_t i, j;
	uint8_t error = 0;
	/* Retry stop for 9 times */
	for (i = 0; i < 9; i++) {
		error = Cmd12(pSd, &status1);

		if (error) {
			trace_error("_StopC.Cmd12: %u\n\r", error);
			return error;
		}
		/* Check status for 299 times */
		for (j = 0; j < 299; j++) {
			error = Cmd13(pSd, &status1);
			// Wait
			for (i = 0; i < 0x1600; i++) ;
			if (error) {
				trace_error("_StopC.Cmd13: %u\n\r", error);
				return error;
			}
			state = status1 & STATUS_STATE;

			/* Invalid state */
			if (state == STATUS_IDLE
			    || state == STATUS_READY
			    || state == STATUS_IDENT
			    || state == STATUS_STBY || state == STATUS_DIS) {
				trace_error("_StopC.state\n\r");
				return SDMMC_ERROR_NOT_INITIALIZED;
			}

			/* Ready? */
			if ((status1 & STATUS_READY_FOR_DATA) ==
			    STATUS_READY_FOR_DATA && state == STATUS_TRAN)
				return SDMMC_SUCCESS;

		}
		/* For write, try stop command again */
		if (state != STATUS_RCV)
			break;
	}
	return SDMMC_ERROR_STATE;
}

static uint8_t
_WaitUntilReady(sSdCard * pSd)
{
	uint32_t timer_res_prv, state;
	uint8_t err, count;

	for (count = 0; count < 51; count++) {
		state = status1 & STATUS_STATE;
		if (state == STATUS_TRAN && status1 & STATUS_READY_FOR_DATA)
			return SDMMC_SUCCESS;
		/* Sending-data and Receive-data states may be encountered
		 * temporarily further to single-block data transfers. */
		/* FIXME state 15 "reserved for I/O mode" may be allowed */
		if (state != STATUS_TRAN && state != STATUS_PRG
		    && state != STATUS_DATA && state != STATUS_RCV)
			return SDMMC_ERROR_NOT_INITIALIZED;
		/* Wait for about 10 ms */
		timer_res_prv = timer_get_resolution();
		timer_configure(10000);
		timer_sleep(1);
		timer_configure(timer_res_prv);

		err = Cmd13(pSd, &status1);
		if (err)
			return err;
	}
	return SDMMC_ERROR_BUSY;
}

/**
 * Perform single block transfer
 */
static uint8_t
PerformSingleTransfer(sSdCard * pSd,
		      uint32_t address, uint8_t * pData, uint8_t isRead)
{
	uint8_t result = SDMMC_OK, error;
	uint8_t sd, mmc;
	uint32_t sdmmc_address, status;

	sd = ((pSd->bCardType & CARD_TYPE_bmSDMMC) == CARD_TYPE_bmSD);
	mmc = ((pSd->bCardType & CARD_TYPE_bmSDMMC) == CARD_TYPE_bmMMC);
	if (mmc)
		sdmmc_address = MMC_ADDRESS(pSd, address);
	else if (sd)
		sdmmc_address = SD_ADDRESS(pSd, address);
	else
		return SDMMC_PARAM;
	if (isRead)
		/* Read a single data block */
		error = Cmd17(pSd, pData, sdmmc_address, &status1, NULL);
	else
		/* Write a single data block */
		error = Cmd24(pSd, pData, sdmmc_address, &status1, NULL);
	if (!error) {
		status = status1 & (isRead ? 0xffffffff : STATUS_WRITE);
		status = status & ~STATUS_READY_FOR_DATA & ~STATUS_STATE;
		if (status) {
			trace_error("CMD%u(0x%lx).stat: %lx\n\r", isRead
			    ? 17 : 24, sdmmc_address, status);
			error = SDMMC_ERROR;
		}
	}
	if (error) {
		trace_error("SingleTx.Cmd%u: %u\n\r", isRead ? 17 : 24, error);
		result = error;
		error = Cmd13(pSd, &status1);
		if (error) {
			trace_error("SingleTx.Cmd13: %u\n\r", error);
			pSd->bStatus = error;
			return result;
		}
		error = _WaitUntilReady(pSd);
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
 * \param nbBlocks Number of blocks to be transfer, 0 for infinite transfer.
 * \param pData    Data buffer whose size is at least the block size.
 * \param isRead   1 for read data and 0 for write data.
 */
static uint8_t
MoveToTransferState(sSdCard * pSd,
		    uint32_t address,
		    uint16_t nbBlocks, uint8_t * pData, uint8_t isRead)
{
	uint8_t result = SDMMC_OK, error;
	uint8_t sd, mmc;
	uint32_t sdmmc_address, state, status;

	sd = ((pSd->bCardType & CARD_TYPE_bmSDMMC) == CARD_TYPE_bmSD);
	mmc = ((pSd->bCardType & CARD_TYPE_bmSDMMC) == CARD_TYPE_bmMMC);
	if (mmc)
		sdmmc_address = MMC_ADDRESS(pSd, address);
	else if (sd)
		sdmmc_address = SD_ADDRESS(pSd, address);
	else
		return SDMMC_PARAM;
	if (pSd->bSetBlkCnt) {
		error = Cmd23(pSd, 0, nbBlocks, &status1);
		if (error) {
			trace_error("MoveToTransferState.Cmd23: %u\n\r", error);
			return error;
		}
	}
	if (isRead)
		/* Move to Receiving data state */
		error = Cmd18(pSd, nbBlocks, pData, sdmmc_address, &status1,
		    NULL);
	else
		/* Move to Sending data state */
		error = Cmd25(pSd, nbBlocks, pData, sdmmc_address, &status1,
		    NULL);
	if (!error) {
		status = status1 & (isRead ? 0xffffffff : STATUS_WRITE);
		status = status & ~STATUS_READY_FOR_DATA & ~STATUS_STATE;

		if (pSd->bStopMultXfer)
			error = _StopCmd(pSd);

		if (status) {
			trace_error("CMD%u(0x%lx, %u).stat: %lx\n\r", isRead
			    ? 18 : 25, sdmmc_address, nbBlocks, status);
			error = SDMMC_ERROR;
		}
	}
	if (error) {
		trace_error("MoveToTransferState.Cmd%u: %u\n\r", isRead
		    ? 18 : 25, error);
		result = error;
		error = Cmd13(pSd, &status1);
		if (error) {
			trace_error("MoveToTransferState.Cmd13: %u\n\r", error);
			pSd->bStatus = error;
			return result;
		}
		state = status1 & STATUS_STATE;
		if (state == STATUS_DATA || state == STATUS_RCV) {
			error = Cmd12(pSd, &status1);
			if (error == SDMMC_OK) {
				trace_debug("MoveToTransferState.stat: %lx\n\r",
				    status1);
				if (status1 & (STATUS_ERASE_SEQ_ERROR
				    | STATUS_ERASE_PARAM | STATUS_UN_LOCK_FAILED
				    | STATUS_ILLEGAL_COMMAND
				    | STATUS_CIDCSD_OVERWRITE
				    | STATUS_ERASE_RESET | STATUS_SWITCH_ERROR))
					result = SDMMC_STATE;
				else if (status1 & (STATUS_COM_CRC_ERROR
				    | STATUS_CARD_ECC_FAILED | STATUS_ERROR))
					result = SDMMC_ERR_IO;
				else if (status1 & (STATUS_ADDR_OUT_OR_RANGE
				    | STATUS_ADDRESS_MISALIGN
				    | STATUS_BLOCK_LEN_ERROR
				    | STATUS_WP_VIOLATION
				    | STATUS_WP_ERASE_SKIP))
					result = SDMMC_PARAM;
				else if (status1 & STATUS_CC_ERROR)
					result = SDMMC_ERR;
			}
			else if (error == SDMMC_ERROR_NORESPONSE)
				error = Cmd13(pSd, &status1);
			if (error) {
				pSd->bStatus = error;
				return result;
			}
		}
		error = _WaitUntilReady(pSd);
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
MmcSelectCard(sSdCard * pSd, uint16_t address, uint8_t statCheck)
{
	uint8_t error;
	//uint32_t  status;
	uint32_t targetState = address ? STATUS_TRAN : STATUS_STBY;
	uint32_t srcState = address ? STATUS_STBY : STATUS_TRAN;

	/* At this stage the Initialization and identification process is achieved
	 * The SD card is supposed to be in Stand-by State */
	while (statCheck) {
		error = Cmd13(pSd, &status1);
		if (error) {
			trace_error("MmcSelectCard.Cmd13 (%d)\n\r", error);
			return error;
		}
		if ((status1 & STATUS_READY_FOR_DATA)) {
			uint32_t currState = status1 & STATUS_STATE;
			if (currState == targetState)
				return 0;
			if (currState != srcState) {
				trace_error("MmcSelectCard, wrong state %x\n\r",
					    (unsigned int) currState);
				return SDMMC_ERROR;
			}
			break;
		}
	}

	/* witch to TRAN mode to Select the current SD/MMC
	 * so that SD ACMD6 can process or EXT_CSD can read. */
	error = Cmd7(pSd, address);
	if (error == SDMMC_ERROR_NOT_INITIALIZED && address == 0) {
	} else if (error) {
		trace_error("MmcSelectCard.Cmd7 (%d)\n\r", error);
	}

	return error;
}

/**
 * Get MMC EXT_CSD information
 * \param pSd      Pointer to a SD card driver instance.
 */
static void
MmcGetExtInformation(sSdCard * pSd)
{
	uint8_t error;
	/* MMC 4.0 Higher version */
	if (SD_CSD_STRUCTURE(pSd->CSD) >= 2 && MMC_IsVer4(pSd)) {

		error = MmcCmd8(pSd, (uint8_t *) pSd->EXT);
		if (error) {
			trace_error("MmcGetExt.Cmd8: %d\n\r", error);
		}
	}
}

/**
 * Get SD/MMC memory max transfer speed in K.
 * \param pSd Pointer to a SD card driver instance.
 */
static uint32_t
SdmmcGetMaxSpeed(sSdCard * pSd)
{
	uint32_t speed = 0;
	trace_info(" .TRAN_SPEED         0x%X\r\n",
		   (unsigned int) SD_CSD_TRAN_SPEED(pSd->CSD));
	if (pSd->bCardType & CARD_TYPE_bmSDMMC) {
		speed = SdmmcDecodeTransSpeed(SD_CSD_TRAN_SPEED(pSd->CSD),
					      sdmmcTransUnits,
					      ((pSd->
						bCardType & CARD_TYPE_bmSDMMC)
					       ==
					       CARD_TYPE_bmSD) ?
					      sdTransMultipliers :
					      mmcTransMultipliers);
	}
	return speed;
}

/**
 * Get SDIO max transfer speed, in K.
 * \param pSd Pointer to a SD card driver instance.
 */
static uint32_t
SdioGetMaxSpeed(sSdCard * pSd)
{
	uint8_t error;
	uint32_t speed = 0;
	uint32_t addr = 0;
	uint8_t buf[6];
	if (pSd->bCardType & CARD_TYPE_bmSDIO) {
		/* Check Func0 tuple in CIS area */
		error = SDIO_ReadDirect(pSd,
					SDIO_CIA, SDIO_CIS_PTR_REG,
					(uint8_t *) & addr, 3);
		if (error) {
			trace_error
			    ("SdioUpdateCardInformation.RdDirect: %d\n\r",
			     error);
			return error;
		}
		error = SdioFindTuples(pSd, addr, 256, NULL, &addr);
		if (error) {
			trace_error
			    ("SdioUpdateCardInformation.FindTuple: %d\n\r",
			     error);
			return error;
		}
		if (addr) {
			/* Fun0 tuple: fn0_blk_siz & max_tran_speed */
			SDIO_ReadDirect(pSd, SDIO_CIA, addr, buf, 6);
			speed = SdmmcDecodeTransSpeed(buf[5],
						      sdmmcTransUnits,
						      sdTransMultipliers);
		}
	}
	return speed;
}

/**
 * Get SCR and SD Status information
 * \param pSd      Pointer to a SD card driver instance.
 */
static void
SdGetExtInformation(sSdCard * pSd)
{
	uint32_t card_status;
	uint8_t error;

	error = Acmd51(pSd, pSd->SCR, &status1);
	if (error)
		return;
	card_status = status1 & ~STATUS_READY_FOR_DATA;
	if (card_status != (STATUS_APP_CMD | STATUS_TRAN)) {
		trace_error("Acmd51.stat: 0x%lx\n\r", card_status);
		return;
	}
	if (SD_SCR_STRUCTURE(pSd->SCR) != SD_SCR_STRUCTURE_1_0)
		trace_warning("Unknown SCR structure version\n\r");
	trace_info("SD Physical Layer Specification Version ");
	if (SD_SCR_SD_SPEC(pSd->SCR) == SD_SCR_SD_SPEC_1_0)
		trace_info_wp("1.0X\n\r")
	else if (SD_SCR_SD_SPEC(pSd->SCR) == SD_SCR_SD_SPEC_1_10)
		trace_info_wp("1.10\n\r")
	else if (SD_SCR_SD_SPEC(pSd->SCR) == SD_SCR_SD_SPEC_2_00) {
		if (SD_SCR_SD_SPEC3(pSd->SCR) == SD_SCR_SD_SPEC_3_0)
			trace_info_wp("3.0X\n\r")
		else
			trace_info_wp("2.00\n\r");
	}
	else
		trace_info_wp("unknown\n\r");
}

/**
 * Update SD/MMC information.
 * Update CSD for card speed switch.
 * Update ExtDATA for any card function switch.
 * \param pSd      Pointer to a SD card driver instance.
 * \return error code when update CSD error.
 */
static void
SdMmcUpdateInformation(sSdCard * pSd, uint8_t csd, uint8_t extData)
{
	uint8_t error;

	/* Update CSD for new TRAN_SPEED value */
	if (csd) {
		MmcSelectCard(pSd, 0, 1);
		Delay(800);
		error = Cmd9(pSd);
		if (error) {
			trace_error("SdMmcUpdateInfo.Cmd9 (%d)\n\r", error);
			return;
		}
		error = MmcSelectCard(pSd, pSd->wAddress, 1);
	}
	if (extData) {
		switch (pSd->bCardType & CARD_TYPE_bmSDMMC) {
		case CARD_TYPE_bmSD:
			SdGetExtInformation(pSd);
			break;
		case CARD_TYPE_bmMMC:
			MmcGetExtInformation(pSd);
			break;
		default:
			break;
		}
	}
}

#if defined ( __ICCARM__ )	/* IAR Ewarm */
#pragma location = "region_dma_nocache"
#elif defined (  __GNUC__  )	/* GCC CS3 */
__attribute__ ((__section__(".region_dma_nocache")))
#endif
uint32_t switchStatus[512 / 32];

/**
 * \brief Check HS capability and enable it
 * \param pSd Pointer to sSdCard instance.
 */
static uint8_t
SdMmcEnableHighSpeed(sSdCard * pSd)
{
	uint8_t error;
	uint8_t io, sd, mmc;

	io = ((pSd->bCardType & CARD_TYPE_bmSDIO) > 0);
	sd = ((pSd->bCardType & CARD_TYPE_bmSDMMC) == CARD_TYPE_bmSD);
	mmc = ((pSd->bCardType & CARD_TYPE_bmSDMMC) == CARD_TYPE_bmMMC);

	/* Check host driver capability */
	if (_HwGetHsMode(pSd) == 0) {
		return SDMMC_ERROR_NOT_SUPPORT;
	}
	/* Check MMC */
	if (mmc) {
		/* MMC card type 3 (HS) */
		//if (SD_CSD_STRUCTURE(pSd->CSD) >= 2 && (MMC_EXT_CARD_TYPE(pSd) & 0x2)) {
		if (MMC_IsHsModeSupported(pSd)) {
			/* Try switch to HS mode */
			MmcCmd6Arg cmd6Arg = {
				0x3,
				MMC_EXT_HS_TIMING_I,
				MMC_EXT_HS_TIMING_EN,
				0
			};
			error = MmcCmd6(pSd, &cmd6Arg, &status1);
			if (error) {
				trace_error("SdMmcEnableHS.Cmd6: %d\n\r",
					    error);
				return SDMMC_ERROR;
			} else if (status1 & STATUS_MMC_SWITCH) {
				trace_error("Mmc Switch HS: %x\n\r",
					    (unsigned int) status1);
				return SDMMC_ERROR_NOT_SUPPORT;
			}
		} else {
			trace_info("MMC without HS support\n\r");
			return SDMMC_ERROR_NOT_SUPPORT;
		}
		trace_warning("MMC HS Enabled\n\r");
	}
	/* SD (+IO) */
	else {
		if (io) {
			/* Check CIA.HS */
			status1 = 0;
			error =
			    Cmd52(pSd, 0, SDIO_CIA, 0, SDIO_HS_REG, &status1);
			if (error) {
				trace_error("SdMmcEnableHS.Cmd52: %d\n\r",
					    error);
				return SDMMC_ERROR;
			}
			if ((status1 & SDIO_SHS) == 0) {
				trace_info("HS Mode not supported by SDIO\n\r");
				return SDMMC_ERROR_NOT_SUPPORT;
			}
			/* Enable HS mode */
			else {
				status1 = SDIO_EHS;
				error =
				    Cmd52(pSd, 1, SDIO_CIA, 1, SDIO_HS_REG,
					  &status1);
				if (error) {
					trace_error
					    ("SdMmcEnableHS.Cmd52 H: %d\n\r",
					     error);
					return SDMMC_ERROR;
				}
				if (status1 & SDIO_EHS) {
					trace_warning("SDIO HS Enabled\n\r");
				}
			}
		}
		if (sd) {
			/* Check version */
			//if (SD_IsHsModeSupported(pSd)) {
			/* Try enable HS mode */
			SdCmd6Arg cmd6Arg = {
				1, 0, 0xF, 0xF, 0xF, 0xF, 0, 1
			};
			//uint32_t switchStatus[512/32];
			error = SdCmd6(pSd, &cmd6Arg, switchStatus, &status1);
			if (error || (status1 & STATUS_SWITCH_ERROR)) {
				trace_info("SD HS Fail\n\r");
				return SDMMC_ERROR;
			} else if (SD_SWITCH_ST_FUN_GRP1_RC(switchStatus)
				   == SD_SWITCH_ST_FUN_GRP_RC_ERROR) {
				trace_info("SD HS Not Supported\n\r");
				return SDMMC_ERROR_NOT_SUPPORT;
			} else if (SD_SWITCH_ST_FUN_GRP1_BUSY(switchStatus)) {
				trace_info("SD HS Locked\n\r");
				return SDMMC_ERROR_BUSY;
			} else {
				trace_warning("SD HS Enabled\n\r");
			}
		}
	}

	/* Enable Host HS mode */
	_HwSetHsMode(pSd, 1);
	return 0;
}

static uint8_t
mmcSelectBuswidth(sSdCard * pSd, uint8_t busWidth)
{
	uint8_t error;
	uint32_t status;
	MmcCmd6Arg cmd6Arg = {
		.access = 0x3,   /* Write byte in the EXT_CSD register */
		.index = MMC_EXT_BUS_WIDTH_I,   /* Target byte in EXT_CSD */
		.value = MMC_EXT_BUS_WIDTH_1BIT,   /* Byte value */
	};

	if (busWidth == 8)
		cmd6Arg.value = MMC_EXT_BUS_WIDTH_8BUTS;
	else if (busWidth == 4)
		cmd6Arg.value = MMC_EXT_BUS_WIDTH_4BITS;
	else if (busWidth != 1)
		return SDMMC_ERROR_PARAM;
	error = MmcCmd6(pSd, &cmd6Arg, &status);
	if (error) {
		trace_error("SdMmcSetBuswidth.Cmd6: %d\n\r", error);
		return SDMMC_ERROR;
	} else {
		if (status & STATUS_MMC_SWITCH) {
			trace_error("MMC Bus Switch error %x\n\r",
				    (unsigned int) status);
			return SDMMC_ERROR_NOT_SUPPORT;
		}
		trace_warning("MMC Bus mode %x\n\r", busWidth);
	}
	return SDMMC_OK;
}

#if defined ( __ICCARM__ )	/* IAR Ewarm */
#pragma location = "region_dma_nocache"
#elif defined (  __GNUC__  )	/* GCC CS3 */
__attribute__ ((__section__(".region_dma_nocache")))
#endif
uint8_t bustest_data[8] = { 0 };

#if defined ( __ICCARM__ )	/* IAR Ewarm */
#pragma location = "region_dma_nocache"
#elif defined (  __GNUC__  )	/* GCC CS3 */
__attribute__ ((__section__(".region_dma_nocache")))
#endif
uint8_t read_data[8];

static uint8_t
mmcDetectBuswidth(sSdCard * pSd)
{
	uint8_t error, busWidth, mask = 0xff, i, len;

	for (busWidth = 8; busWidth != 0; busWidth /= busWidth == 8 ? 2 : 4) {
		error = _HwSetBusWidth(pSd, busWidth);
		if (error)
			continue;
		switch (busWidth) {
		case 8:
			bustest_data[0] = 0x55;
			bustest_data[1] = 0xaa;
			break;
		case 4:
			bustest_data[0] = 0x5a;
			bustest_data[1] = 0;
			break;
		case 1:
			bustest_data[0] = 0x80;
			bustest_data[1] = 0;
			break;
		}
		len = busWidth >= 2 ? busWidth : 2;
		error = Cmd19(pSd, bustest_data, len, &status1);
		if (error) {
			trace_error("Cmd19 %u, %lx\n\r", error, status1);
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
		error = Cmd14(pSd, read_data, busWidth, &status1);
		if (error) {
			trace_error("Cmd14 %u, %lx\n\r", error, status1);
			continue;
		}
		if (busWidth == 1) {
			mask = 0xc0;
			read_data[0] &= mask;
		}
		len = busWidth == 8 ? 2 : 1;
		for (i = 0; i < len; i++) {
			if ((bustest_data[i] ^ read_data[i]) != mask)
				break;
		}
		if (i == len) {
			printf("MMC: %d-bit bus width detected\n\r", busWidth);
			break;
		}
	}
	return busWidth;
}

/**
 * \brief Check bus width capability and enable it
 */
static uint8_t
SdMmcDesideBuswidth(sSdCard * pSd)
{
	uint8_t error, busWidth = 1;
	const uint8_t mmc = (pSd->bCardType & CARD_TYPE_bmSDMMC)
	    == CARD_TYPE_bmMMC;
	const uint8_t sd = (pSd->bCardType & CARD_TYPE_bmSDMMC)
	    == CARD_TYPE_bmSD;
	const uint8_t io = (pSd->bCardType & CARD_TYPE_bmSDIO) != 0;

	if (io)
		busWidth = 1;   /* SDIO => 1 bit only */
	else if (mmc) {
		/* Check MMC revision 4 or later (1/4/8 bit mode) */
		if (MMC_CSD_SPEC_VERS(pSd->CSD) >= 4)
			busWidth = mmcDetectBuswidth(pSd);
		else
			trace_warning("MMC 1-bit only\n\r");
	} else if (sd) {
		busWidth = 4;   /* default to 4-bit mode */
		error = _HwSetBusWidth(pSd, busWidth);
		if (error)
			busWidth = 1;
	}
	if (busWidth == 0)
		busWidth = 1;
	/* Switch to selected bus mode */
	if (mmc && busWidth > 1) {
		error = mmcSelectBuswidth(pSd, busWidth);
		if (error)
			return error;
	}
	else if (sd && busWidth > 1) {
		error = Acmd6(pSd, busWidth);
		if (error)
			return error;
	}
	error = _HwSetBusWidth(pSd, busWidth);
	if (error)
		return error;
	pSd->bBusMode = busWidth;
	trace_info("%u-bit data bus\n\r", busWidth);
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
	uint8_t mem = 0, io = 0, f8 = 0, mp = 1, ccs = 0;
	//uint32_t status;
	uint8_t error;
	/* Reset HC to default HS and BusMode */
	_HwSetHsMode(pSd, 0);
	_HwSetBusWidth(pSd, 1);
	/* Reset SDIO: CMD52, write 1 to RES bit in CCCR (bit 3 of register 6) */
	status1 = SDIO_RES;
	error = Cmd52(pSd, 1, SDIO_CIA, 0, SDIO_IOA_REG, &status1);
	if (!error && ((status1 & STATUS_SDIO_R5) == 0)) {
	} else if (error == SDMMC_ERROR_NORESPONSE) {
	} else {
		trace_debug("SdMmcIdentify.Cmd52 fail: %u, %lx\n\r", error,
			    status1);
	}
	/* Reset MEM: CMD0 */
	error = SwReset(pSd, 1);
	if (error) {
		trace_debug("SdMmcIdentify.SwReset fail: %u\n\r", error);
	}

	/* CMD8 is newly added in the Physical Layer Specification Version 2.00 to
	 * support multiple voltage ranges and used to check whether the card
	 * supports supplied voltage. The version 2.00 host shall issue CMD8 and
	 * verify voltage before card initialization.
	 * The host that does not support CMD8 shall supply high voltage range... */
	error = SdCmd8(pSd, 1);
	if (error == 0)
		f8 = 1;
	else if (error != SDMMC_ERROR_NORESPONSE) {
		trace_error("SdMmcIdentify.Cmd8: %d\n\r", error);
		return SDMMC_ERROR;
	}
	/* Delay after "no response" */
	else
		Delay(8000);

	/* CMD5 is newly added for SDIO initialize & power on */
	status1 = 0;
	error = Cmd5(pSd, &status1);
	if (error) {
		trace_info("SdMmcIdentify.Cmd5: %d\n\r", error)
	}
	/* Card has SDIO function */
	else if ((status1 & SDIO_OCR_NF) > 0) {
		unsigned int cmd5Retries = 10000;
		do {
			status1 &= SD_HOST_VOLTAGE_RANGE;
			error = Cmd5(pSd, &status1);
			if (status1 & SD_OCR_BUSY)
				break;
		} while (!error && cmd5Retries--);
		if (error) {
			trace_error("SdMmcIdentify.Cmd5 V: %d\n\r", error);
			return SDMMC_ERROR;
		}
		io = 1;
		trace_info("SDIO\n\r");
		/* IO only ? */
		mp = ((status1 & SDIO_OCR_MP) > 0);
	}
	/* Has memory: SD/MMC/COMBO */
	if (mp) {
		/* Try SD memory initialize */
		error = Acmd41(pSd, f8, &ccs);
		if (error) {
			unsigned int cmd1Retries = 10000;
			trace_debug("SdMmcIdentify.Acmd41: %u, try MMC\n\r",
				    error);
			/* Try MMC initialize */
			error = SwReset(pSd, 10);
			if (error) {
				trace_error("SdMmcIdentify.Mmc.SwReset: %d\n\r",
					    error);
				return SDMMC_ERROR;
			}
			ccs = 1;
			do {
				error = Cmd1(pSd, &ccs);
			} while (error && cmd1Retries-- > 0);
			if (error) {
				trace_error("SdMmcIdentify.Cmd1: %d\n\r",
					    error);
				return SDMMC_ERROR;
			} else if (ccs)
				pSd->bCardType = CARD_MMCHD;
			else
				pSd->bCardType = CARD_MMC;
			/* MMC card identification OK */
			trace_info("MMC Card\n\r");
			return 0;
		} else if (ccs) {
			trace_info("SDHC MEM\n\r");
		} else {
			trace_info("SD MEM\n\r");
		}
		mem = 1;
	}
	/* SD(IO) + MEM ? */
	if (!mem) {
		if (io)
			pSd->bCardType = CARD_SDIO;
		else {
			trace_error("Unknown card\n\r");
			return SDMMC_ERROR;
		}
	}
	/* SD(HC) combo */
	else if (io)
		pSd->bCardType = ccs ? CARD_SDHCCOMBO : CARD_SDCOMBO;
	/* SD(HC) */
	else
		pSd->bCardType = ccs ? CARD_SDHC : CARD_SD;

	return 0;
}

/**
 * \brief Run the SD/MMC/SDIO enumeration sequence.
 * This function runs after the initialization and identification procedure. It
 * gets all necessary information from the card and deside transfer block size,
 * clock speed and bus width. It sets the SD/MMC/SDIO card in transfer
 * (or command) state.
 * \param pSd  Pointer to a SD card driver instance.
 * \return 0 if successful; otherwise returns an \ref sdmmc_rc "SD_ERROR code".
 */
static uint8_t
SdMmcEnum(sSdCard * pSd)
{
	uint8_t mem, io;
	uint8_t error;
	uint32_t ioSpeed = 0, memSpeed = 0;
	uint8_t hsExec = 0;

	/* - has Memory/IO/High-Capacigy - */
	mem = ((pSd->bCardType & CARD_TYPE_bmSDMMC) > 0);
	io = ((pSd->bCardType & CARD_TYPE_bmSDIO) > 0);

	/* For MEMORY cards:
	 * The host then issues the command ALL_SEND_CID (CMD2) to the card to get
	 * its unique card identification (CID) number.
	 * Card that is unidentified (i.e. which is in Ready State) sends its CID
	 * number as the response (on the CMD line). */
	if (mem) {
		error = Cmd2(pSd);
		if (error) {
			trace_error("SdMmcInit.cmd2(%d)\n\r", error);
			return error;
		}
	}

	/* For MEMORY and SDIO cards:
	 * Thereafter, the host issues CMD3 (SEND_RELATIVE_ADDR) asks the
	 * card to publish a new relative card address (RCA), which is shorter than
	 * CID and which is used to address the card in the future data transfer
	 * mode. Once the RCA is received the card state changes to the Stand-by
	 * State. At this point, if the host wants to assign another RCA number, it
	 * can ask the card to publish a new number by sending another CMD3 command
	 * to the card. The last published RCA is the actual RCA number of the
	 * card. */
	error = Cmd3(pSd);
	if (error) {
		trace_error("SdMmcInit.cmd3(%d)\n\r", error);
		return error;
	}
	else
		trace_debug("Relative Card Address %u\n\r", CARD_ADDR(pSd));

	/* For MEMORY cards:
	 * SEND_CSD (CMD9) to obtain the Card Specific Data (CSD register),
	 * e.g. block length, card storage capacity, etc... */
	if (mem) {
		error = Cmd9(pSd);
		if (error) {
			trace_error("SdMmcInit.cmd9(%d)\n\r", error);
			return error;
		}
	}

	/* Now select the card, to TRAN state */
	error = MmcSelectCard(pSd, CARD_ADDR(pSd), 0);
	if (error) {
		trace_error("SdMmcInit.SelCard(%d)\n\r", error);
		return error;
	}

	/* - Now in TRAN, obtain extended setup information - */

	/* If the card support EXT_CSD, read it! */
	trace_info("Card Type %d, CSD_STRUCTURE %u\n\r",
		   (unsigned int) pSd->bCardType,
		   (unsigned int) SD_CSD_STRUCTURE(pSd->CSD));

	/* Get extended information of the card */
	SdMmcUpdateInformation(pSd, 1, 1);

	/* Calculate transfer speed */
	if (io)
		ioSpeed = SdioGetMaxSpeed(pSd);
	if (mem)
		memSpeed = SdmmcGetMaxSpeed(pSd);

	/* Combo, min speed */
	if (io && mem) {
		pSd->dwTranSpeed = (ioSpeed > memSpeed) ? memSpeed : ioSpeed;
	}
	/* SDIO only */
	else if (io) {
		pSd->dwTranSpeed = ioSpeed;
	}
	/* Memory card only */
	else if (mem) {
		pSd->dwTranSpeed = memSpeed;
	}
	pSd->dwTranSpeed *= 1000;

	/* Enable more bus width Mode */
	error = SdMmcDesideBuswidth(pSd);
	if (error) {
		trace_error("SdmmcEnum.DesideBusWidth: %u\n\r", error);
		return SDMMC_ERROR;
	}

	/* Enable High-Speed Mode */
	error = SdMmcEnableHighSpeed(pSd);
	if (!error)
		hsExec = 1;
	//else if (error != SDMMC_ERROR_NOT_SUPPORT) {
	//  return SDMMC_ERROR;
	//}

	/* In HS mode transfer speed *2 */
	if (hsExec)
		pSd->dwTranSpeed *= 2;

	/* Update card information since status changed */
	if (hsExec || pSd->bBusMode > 1)
		SdMmcUpdateInformation(pSd, hsExec, 1);

	return 0;
}

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
 * Read Blocks of data in a buffer pointed by pData. The buffer size must be at
 * least 512 byte long. This function checks the SD card status register and
 * address the card if required before sending the read command.
 * \return 0 if successful; otherwise returns an \ref sdmmc_rc "error code".
 * \param pSd      Pointer to a SD card driver instance.
 * \param address  Address of the block to read.
 * \param pData    Data buffer whose size is at least the block size, it can
 *            be 1,2 or 4-bytes aligned when used with DMA.
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
	uint8_t error;

	assert(pSd != NULL);
	assert(pData != NULL);

	if (length == 0)
		/* Avoid starting an open-ended multiple block read */
		return 0;
	error = MoveToTransferState(pSd, address, length, (uint8_t *) pData, 1);
	trace_debug("SDrd(%lu,%lu) %s\n\r", address, length, error ?
	    SD_StringifyRetCode(error) : "");
	return error;
}

/**
 * Write Blocks of data in a buffer pointed by pData. The buffer size must be at
 * least 512 byte long. This function checks the SD card status register and
 * address the card if required before sending the read command.
 * \return 0 if successful; otherwise returns an \ref sdmmc_rc "error code".
 * \param pSd      Pointer to a SD card driver instance.
 * \param address  Address of the block to write.
 * \param pData    Data buffer whose size is at least the block size, it can
 *            be 1,2 or 4-bytes aligned when used with DMA.
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
	uint8_t error;

	assert(pSd != NULL);
	assert(pData != NULL);

	if (length == 0)
		return 0;
	error = MoveToTransferState(pSd, address, length, (uint8_t *) pData, 0);
	trace_debug("SDwr(%lu,%lu) %s\n\r", address, length, error ?
	    SD_StringifyRetCode(error) : "");
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
 * \param pData    Data buffer whose size is at least the block size, it can
 *            be 1,2 or 4-bytes aligned when used with DMA.
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
 * \param pData    Data buffer whose size is at least the block size, it can
 *            be 1,2 or 4-bytes aligned when used with DMA.
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
 * Reset SD/MMC driver runtime parameters.
 */
static void
_SdParamReset(sSdCard * pSd)
{
	uint32_t i;

	pSd->dwTranSpeed = 0;
	pSd->dwTotalSize = 0;
	pSd->dwNbBlocks = 0;
	pSd->wBlockSize = 0;

	pSd->wCurrBlockLen = 0;
	pSd->dwCurrSpeed = 0;
	pSd->wAddress = 0;

	pSd->bCardType = 0;
	pSd->bStatus = 0;
	pSd->bSetBlkCnt = 0;
	pSd->bStopMultXfer = 0;

	/* Clear our device register cache */
	for (i = 0; i < 128 / 8 / 4; i++)
		pSd->CID[i] = 0;
	for (i = 0; i < 128 / 8 / 4; i++)
		pSd->CSD[i] = 0;
	for (i = 0; i < 512 / 4; i++)
		pSd->EXT[i] = 0;
	memset(pSd->SCR, 0, sizeof(pSd->SCR));
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
	uint8_t error;
	uint32_t clock, drv_param, drv_err;

	_SdParamReset(pSd);

	/* Power the device and the bus on */
	_HwPowerDevice(pSd, 1);

	/* Set low speed for device identification (LS device max speed) */
	clock = 400000;
	_HwSetClock(pSd, &clock);

	/* Initialization delay: The maximum of 1 msec, 74 clock cycles and supply
	 * ramp up time. Supply ramp up time provides the time that the power is
	 * built up to the operating level (the bus master supply voltage) and the
	 * time to wait until the SD card can accept the first command. */
	/* Power On Init Special Command */
	error = Pon(pSd);
	if (error) {
		trace_error("SD_Init.PowON:%d\n\r", error);
		return error;
	}

	/* After power-on or CMD0, all cards?
	 * CMD lines are in input mode, waiting for start bit of the next command.
	 * The cards are initialized with a default relative card address
	 * (RCA=0x0000) and with a default driver stage register setting
	 * (lowest speed, highest driving current capability). */
	error = SdMmcIdentify(pSd);
	if (error) {
		trace_error("SD_Init.Identify: %d\n\r", error);
		return error;
	}
	error = SdMmcEnum(pSd);
	if (error) {
		trace_error("SD_Init.Enum: %d\n\r", error);
		return error;
	}

	/* Find out if the device supports the SET_BLOCK_COUNT command.
	 * MMC devices have it part of both the block-oriented read and the
	 * block-oriented write commands, i.e. class 2 and class 4 commands.
	 * FIXME we should normally check CSD.CCC before issuing any MMC block-
	 * oriented read/write command.
	 * SD devices advertise in SCR.CMD_SUPPORT whether or not they handle
	 * the SET_BLOCK_COUNT command. */
	if ((pSd->bCardType & CARD_TYPE_bmSDMMC) == CARD_TYPE_bmMMC)
		pSd->bSetBlkCnt = 1;
	else if ((pSd->bCardType & CARD_TYPE_bmSDMMC) == CARD_TYPE_bmSD)
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
		if (error) {
			trace_error("SD_Init.Enum: %d\n\r", error);
			return error;
		}
	}
	pSd->wCurrBlockLen = SDMMC_BLOCK_SIZE;

	/* If MMC Card & get size from EXT_CSD */
	if ((pSd->bCardType & CARD_TYPE_bmSDMMC) == CARD_TYPE_bmMMC
	    && SD_CSD_C_SIZE(pSd->CSD) == 0xFFF) {
		if (MMC_EXT_DATA_SECTOR_SIZE(pSd->EXT)
		    == MMC_EXT_DATA_SECT_4KIB)
			pSd->wBlockSize = 4096;
		else
			pSd->wBlockSize = 512;
		pSd->dwNbBlocks = MMC_EXT_SEC_COUNT(pSd->EXT)
		    / (pSd->wBlockSize / 512UL);
		/* Device density >= 4 GiB does not fit 32-bit dwTotalSize */
		if (pSd->dwNbBlocks >= 0x800000)
			pSd->dwTotalSize = 0xFFFFFFFF;
		else
			pSd->dwTotalSize = MMC_EXT_SEC_COUNT(pSd->EXT) * 512UL;
	}
	/* If SD CSD v2.0 */
	else if ((pSd->bCardType & CARD_TYPE_bmSDMMC) == CARD_TYPE_bmSD
		 && SD_CSD_STRUCTURE(pSd->CSD) >= 1) {
		pSd->wBlockSize = 512;
		pSd->dwNbBlocks = SD_CSD_BLOCKNR_HC(pSd->CSD);
		pSd->dwTotalSize = 0xFFFFFFFF;
	}
	/* Normal SD/MMC card */
	else if (pSd->bCardType & CARD_TYPE_bmSDMMC) {
		pSd->wBlockSize = 512;	//SD_CSD_BLOCK_LEN(pSd->CSD);
		pSd->dwTotalSize = SD_CSD_TOTAL_SIZE(pSd->CSD);
		pSd->dwNbBlocks = pSd->dwTotalSize / 512;	//SD_CSD_BLOCKNR(pSd->CSD);
	}

	if (pSd->bCardType == CARD_UNKNOWN) {
		return SDMMC_ERROR_NOT_INITIALIZED;
	}
	/* Automatically select the max clock */
	clock = pSd->dwTranSpeed;
	_HwSetClock(pSd, &clock);
	trace_warning_wp("-I- Set SD/MMC clock to %uK\n\r",
			 (unsigned int) clock / 1000);
	pSd->dwCurrSpeed = clock;
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
SD_GetStatus(sSdCard * pSd)
{
	assert(pSd != NULL);

	/* TODO develop an extra SDMMC_IOCTL control to query whether the device
	 * is present. Return SDMMC_NOT_SUPPORTED if removed. */

	return pSd->bStatus == SDMMC_NOT_SUPPORTED ? SDMMC_ERR : pSd->bStatus;
}

/**
 * Return type of the card.
 * \param pSd Pointer to \ref sSdCard instance.
 * \sa sdmmc_cardtype
 */
uint8_t
SD_GetCardType(sSdCard * pSd)
{
	assert(pSd != NULL);

	return pSd->bCardType;
}

/**
 * Return size of the SD/MMC card, in KiB.
 * \param pSd Pointer to \ref sSdCard instance.
 */
uint32_t
SD_GetTotalSizeKB(sSdCard * pSd)
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
SD_GetBlockSize(sSdCard * pSd)
{
	assert(pSd != NULL);

	return pSd->wBlockSize;
}

/**
 * Return reported number of blocks for the SD/MMC card.
 * \param pSd Pointer to \ref sSdCard instance.
 */
uint32_t
SD_GetNumberBlocks(sSdCard * pSd)
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
			if (error) {
				trace_error("IO_RdDirect.Cmd52: %d\n\r", error);
				return SDMMC_ERROR;
			} else if (status & STATUS_SDIO_R5) {
				trace_error("RD_DIRECT(%u, %u) st %x\n\r",
					    (unsigned int) address,
					    (unsigned int) size,
					    (unsigned int) status);
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
 * \param dataByte    Data to write.
 * \return 0 if successful; otherwise returns an \ref sdmmc_rc "error code".
 */
uint8_t
SDIO_WriteDirect(sSdCard * pSd,
		 uint8_t functionNum, uint32_t address, uint8_t dataByte)
{
	uint8_t error;
	uint32_t status;

	assert(pSd != NULL);

	if (pSd->bCardType & CARD_TYPE_bmSDIO) {
		status = dataByte;
		error = Cmd52(pSd, 1, functionNum, 0, address, &status);
		if (error) {
			trace_error("SDIO_WrDirect.Cmd52: %d\n\r", error);
			return SDMMC_ERROR;
		} else if (status & STATUS_SDIO_R5) {
			trace_error("WR_DIRECT(%u) st %x\n\r",
				    (unsigned int) address,
				    (unsigned int) status);
			return SDMMC_ERROR;
		}
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
		if (error) {
			trace_error("IO_RdBytes.Cmd53: %d\n\r", error);
			return SDMMC_ERROR;
		} else if (status & STATUS_SDIO_R5) {
			trace_error("RD_EXT st %x\n\r", (unsigned int) status);
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
		Delay(100);
		if (error) {
			trace_error("IO_WrBytes.Cmd53: %d\n\r", error);
			return SDMMC_ERROR;
		} else if (status & STATUS_SDIO_R5) {
			trace_error("WR_EXT st %x\n\r", (unsigned int) status);
			return SDMMC_ERROR;
		}
	} else {
		return SDMMC_ERROR_NOT_SUPPORT;
	}
	return 0;
}

/**
 * Display SDIO card informations (CIS, tuple ...)
 * \param pSd Pointer to \ref sSdCard instance.
 */
void
SDIO_DumpCardInformation(sSdCard * pSd)
{
	uint32_t tmp = 0, addrCIS = 0, addrManfID = 0, addrFunc0 = 0;
	uint8_t *p = (uint8_t *) & tmp;
	uint8_t buf[8];
	//printf("** trace : %d %x %X\n\r", DYN_TRACES, TRACE_LEVEL, dwTraceLevel);
	switch (pSd->bCardType) {
	case CARD_SDIO:
		trace_info("** SDIO ONLY card\n\r");
		break;
	case CARD_SDCOMBO:
	case CARD_SDHCCOMBO:
		trace_info("** SDIO Combo card\n\r");
		break;
	default:
		trace_info("** NO SDIO\n\r");
		return;
	}
	/* CCCR */
	trace_info("====== CCCR ======\n\r");
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_CCCR_REG, p, 1);
	trace_info(".SDIO       %02lX\n\r", (tmp & SDIO_SDIO) >> 4);
	trace_info(".CCCR       %02lX\n\r", (tmp & SDIO_CCCR) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_SD_REV_REG, p, 1);
	trace_info(".SD         %02lX\n\r", (tmp & SDIO_SD) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_IOE_REG, p, 1);
	trace_info(".IOE        %02lX\n\r", (tmp & SDIO_IOE) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_IOR_REG, p, 1);
	trace_info(".IOR        %02lX\n\r", (tmp & SDIO_IOR) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_IEN_REG, p, 1);
	trace_info(".IEN        %02lX\n\r", (tmp & SDIO_IEN) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_INT_REG, p, 1);
	trace_info(".INT        %u\n\r", (unsigned int) (tmp & SDIO_INT));
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_BUS_CTRL_REG, p, 1);
	trace_info(".CD         %lx\n\r", (tmp & SDIO_CD) >> 7);
	trace_info(".SCSI       %lx\n\r", (tmp & SDIO_SCSI) >> 6);
	trace_info(".ECSI       %lx\n\r", (tmp & SDIO_ECSI) >> 5);
	trace_info(".BUS_WIDTH  %lx\n\r", (tmp & SDIO_BUSWIDTH) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_CAP_REG, p, 1);
	trace_info(".4BLS       %lx\n\r", (tmp & SDIO_4BLS) >> 7);
	trace_info(".LSC        %lx\n\r", (tmp & SDIO_LSC) >> 6);
	trace_info(".E4MI       %lx\n\r", (tmp & SDIO_E4MI) >> 5);
	trace_info(".S4MI       %lx\n\r", (tmp & SDIO_S4MI) >> 4);
	trace_info(".SBS        %lx\n\r", (tmp & SDIO_SBS) >> 3);
	trace_info(".SRW        %lx\n\r", (tmp & SDIO_SRW) >> 2);
	trace_info(".SMB        %lx\n\r", (tmp & SDIO_SMB) >> 1);
	trace_info(".SDC        %lx\n\r", (tmp & SDIO_SDC) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_CIS_PTR_REG, p, 3);
	trace_info(".CIS_PTR    %06X\n\r", (unsigned int) tmp);
	addrCIS = tmp;
	tmp = 0;
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_BUS_SUSP_REG, p, 1);
	trace_info(".BR         %lx\n\r", (tmp & SDIO_BR) >> 1);
	trace_info(".BS         %lx\n\r", (tmp & SDIO_BS) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_FUN_SEL_REG, p, 1);
	trace_info(".DF         %lx\n\r", (tmp & SDIO_DF) >> 7);
	trace_info(".FS         %lx\n\r", (tmp & SDIO_FS) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_EXEC_REG, p, 1);
	trace_info(".EX         %lx\n\r", (tmp & SDIO_EX));
	trace_info(".EXM        %lx\n\r", (tmp & SDIO_EXM) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_READY_REG, p, 1);
	trace_info(".RF         %lx\n\r", (tmp & SDIO_RF));
	trace_info(".RFM        %lx\n\r", (tmp & SDIO_RFM) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_FN0_BLKSIZ_REG, p, 2);
	trace_info(".FN0_SIZE   %u(%04X)\n\r", (unsigned int) tmp,
		   (unsigned int) tmp);
	tmp = 0;
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_POWER_REG, p, 1);
	trace_info(".EMPC       %lx\n\r", (tmp & SDIO_EMPC) >> 1);
	trace_info(".SMPC       %lx\n\r", (tmp & SDIO_SMPC) >> 0);
	SDIO_ReadDirect(pSd, SDIO_CIA, SDIO_HS_REG, p, 1);
	trace_info(".EHS        %lx\n\r", (tmp & SDIO_EHS) >> 1);
	trace_info(".SHS        %lx\n\r", (tmp & SDIO_SHS) >> 0);
	/* Metaformat */
	SdioFindTuples(pSd, addrCIS, 128, &addrManfID, &addrFunc0);
	if (addrManfID != 0) {
		SDIO_ReadDirect(pSd, SDIO_CIA, addrManfID, buf, 6);
		trace_info("==== CISTPL_MANFID ====\n\r");
		trace_info("._MANF %04X\n\r", buf[2] + (buf[3] << 8));
		trace_info("._CARD %04X\n\r", buf[4] + (buf[5] << 8));
	}
	if (addrFunc0 != 0) {
		SDIO_ReadDirect(pSd, SDIO_CIA, addrFunc0, buf, 6);
		trace_info("== CISTPL_FUNCE Fun0 ==\n\r");
		trace_info("._FN0_BLK_SIZE   %d(0x%04X)\n\r",
			   buf[3] + (buf[4] << 8), buf[3] + (buf[4] << 8));
		trace_info("._MAX_TRAN_SPEED %02X\n\r", buf[5]);
	}
}

/**
 * Display the content of the CID register
 * \param pCID Pointer to CID data.
 */
void
SD_DumpCID(void *pCID)
{
	trace_info("======= Card IDentification =======\n\r");
	trace_info(" .MID Manufacturer ID             %02X\n\r",
		   (unsigned int) SD_CID_MID(pCID));

	trace_info(" .CBX Card/BGA (eMMC)             %X\n\r",
		   (unsigned int) eMMC_CID_CBX(pCID));

	trace_info(" .OID OEM/Application ID (SD)     %c%c\n\r",
		   (char) SD_CID_OID1(pCID), (char) SD_CID_OID0(pCID));
	trace_info(" .OID OEM/Application ID (MMC)    %x\n\r",
		   (unsigned int) eMMC_CID_OID(pCID));

	trace_info(" .PNM Product name (SD)           %c%c%c%c%c\n\r",
		   (char) SD_CID_PNM4(pCID),
		   (char) SD_CID_PNM3(pCID),
		   (char) SD_CID_PNM2(pCID),
		   (char) SD_CID_PNM1(pCID), (char) SD_CID_PNM0(pCID));
	trace_info(" .PNM Product name (MMC)          %c%c%c%c%c%c\n\r",
		   (char) MMC_CID_PNM5(pCID),
		   (char) MMC_CID_PNM4(pCID),
		   (char) MMC_CID_PNM3(pCID),
		   (char) MMC_CID_PNM2(pCID),
		   (char) MMC_CID_PNM1(pCID), (char) MMC_CID_PNM0(pCID));

	trace_info(" .PRV Product revision (SD)       %x\n\r",
		   (unsigned int) SD_CID_PRV(pCID));
	trace_info(" .PRV Product revision (MMC)      %x\n\r",
		   (unsigned int) MMC_CID_PRV(pCID));

	trace_info(" .PSN Product serial number (SD)  %02X%02X%02X%02X\n\r",
		   (unsigned int) SD_CID_PSN3(pCID),
		   (unsigned int) SD_CID_PSN2(pCID),
		   (unsigned int) SD_CID_PSN1(pCID),
		   (unsigned int) SD_CID_PSN0(pCID));
	trace_info(" .PSN Product serial number (MMC) %02X%02X%02X%02X\n\r",
		   (unsigned int) MMC_CID_PSN3(pCID),
		   (unsigned int) MMC_CID_PSN2(pCID),
		   (unsigned int) MMC_CID_PSN1(pCID),
		   (unsigned int) MMC_CID_PSN0(pCID));

	trace_info(" .MDT Manufacturing date (SD)     %04d/%02d\n\r",
		   (uint16_t) (SD_CID_MDT_Y(pCID) + 2000),
		   (uint8_t) SD_CID_MDT_M(pCID));
	trace_info(" .MDT Manufacturing date (MMC)    %04d/%02d\n\r",
		   (uint16_t) (MMC_CID_MDT_Y(pCID) + 1997),
		   (uint8_t) SD_CID_MDT_M(pCID));

	trace_info(" .CRC checksum              %02X\n\r",
		   (unsigned int) SD_CID_CRC(pCID));
}

/**
 * Display the content of the CSD register
 * \param pCSD Pointer to \ref sSdCard instance.
 */
void
SD_DumpCSD(void *pCSD)
{
	trace_info("======= Card-Specific Data =======\n\r");
	trace_info(" .CSD_STRUCTURE      0x%x\r\n",
		   (unsigned int) SD_CSD_STRUCTURE(pCSD));
	trace_info(" .SPEC_VERS (eMMC)   0x%x\r\n",
		   (unsigned int) MMC_CSD_SPEC_VERS(pCSD));
	trace_info(" .TAAC               0x%X\r\n",
		   (unsigned int) SD_CSD_TAAC(pCSD));
	trace_info(" .NSAC               0x%X\r\n",
		   (unsigned int) SD_CSD_NSAC(pCSD));
	trace_info(" .TRAN_SPEED         0x%X\r\n",
		   (unsigned int) SD_CSD_TRAN_SPEED(pCSD));
	trace_info(" .CCC                0x%X\r\n",
		   (unsigned int) SD_CSD_CCC(pCSD));
	trace_info(" .READ_BL_LEN        0x%X\r\n",
		   (unsigned int) SD_CSD_READ_BL_LEN(pCSD));
	trace_info(" .READ_BL_PARTIAL    0x%X\r\n",
		   (unsigned int) SD_CSD_READ_BL_PARTIAL(pCSD));
	trace_info(" .WRITE_BLK_MISALIGN 0x%X\r\n",
		   (unsigned int) SD_CSD_WRITE_BLK_MISALIGN(pCSD));
	trace_info(" .READ_BLK_MISALIGN  0x%X\r\n",
		   (unsigned int) SD_CSD_READ_BLK_MISALIGN(pCSD));
	trace_info(" .DSR_IMP            0x%X\r\n",
		   (unsigned int) SD_CSD_DSR_IMP(pCSD));
	trace_info(" .C_SIZE             0x%X\r\n",
		   (unsigned int) SD_CSD_C_SIZE(pCSD));
	trace_info(" .C_SIZE_HC          0x%X\r\n",
		   (unsigned int) SD2_CSD_C_SIZE(pCSD));
	trace_info(" .VDD_R_CURR_MIN     0x%X\r\n",
		   (unsigned int) SD_CSD_VDD_R_CURR_MIN(pCSD));
	trace_info(" .VDD_R_CURR_MAX     0x%X\r\n",
		   (unsigned int) SD_CSD_VDD_R_CURR_MAX(pCSD));
	trace_info(" .VDD_W_CURR_MIN     0x%X\r\n",
		   (unsigned int) SD_CSD_VDD_W_CURR_MIN(pCSD));
	trace_info(" .VDD_W_CURR_MAX     0x%X\r\n",
		   (unsigned int) SD_CSD_VDD_W_CURR_MAX(pCSD));
	trace_info(" .C_SIZE_MULT        0x%X\r\n",
		   (unsigned int) SD_CSD_C_SIZE_MULT(pCSD));
	trace_info(" .ERASE_BLK_EN       0x%X\r\n",
		   (unsigned int) SD_CSD_ERASE_BLK_EN(pCSD));
	trace_info(" .SECTOR_SIZE        0x%X\r\n",
		   (unsigned int) SD_CSD_SECTOR_SIZE(pCSD));
	trace_info(" .WP_GRP_SIZE        0x%X\r\n",
		   (unsigned int) SD_CSD_WP_GRP_SIZE(pCSD));
	trace_info(" .WP_GRP_ENABLE      0x%X\r\n",
		   (unsigned int) SD_CSD_WP_GRP_ENABLE(pCSD));
	trace_info(" .R2W_FACTOR         0x%X\r\n",
		   (unsigned int) SD_CSD_R2W_FACTOR(pCSD));
	trace_info(" .WRITE_BL_LEN       0x%X\r\n",
		   (unsigned int) SD_CSD_WRITE_BL_LEN(pCSD));
	trace_info(" .WRITE_BL_PARTIAL   0x%X\r\n",
		   (unsigned int) SD_CSD_WRITE_BL_PARTIAL(pCSD));
	trace_info(" .FILE_FORMAT_GRP    0x%X\r\n",
		   (unsigned int) SD_CSD_FILE_FORMAT_GRP(pCSD));
	trace_info(" .COPY               0x%X\r\n",
		   (unsigned int) SD_CSD_COPY(pCSD));
	trace_info(" .PERM_WRITE_PROTECT 0x%X\r\n",
		   (unsigned int) SD_CSD_PERM_WRITE_PROTECT(pCSD));
	trace_info(" .TMP_WRITE_PROTECT  0x%X\r\n",
		   (unsigned int) SD_CSD_TMP_WRITE_PROTECT(pCSD));
	trace_info(" .FILE_FORMAT        0x%X\r\n",
		   (unsigned int) SD_CSD_FILE_FORMAT(pCSD));
	trace_info(" .ECC (MMC)          0x%X\r\n",
		   (unsigned int) MMC_CSD_ECC(pCSD));
	trace_info(" .CRC                0x%X\r\n",
		   (unsigned int) SD_CSD_CRC(pCSD));
	trace_info(" .MULT               0x%X\r\n",
		   (unsigned int) SD_CSD_MULT(pCSD));
	trace_info(" .BLOCKNR            0x%X\r\n",
		   (unsigned int) SD_CSD_BLOCKNR(pCSD));
	trace_info(" .BLOCKNR_HC         0x%X\r\n",
		   (unsigned int) SD_CSD_BLOCKNR_HC(pCSD));
	trace_info(" .BLOCK_LEN          0x%X\r\n",
		   (unsigned int) SD_CSD_BLOCK_LEN(pCSD));
	trace_info(" -TOTAL_SIZE         0x%X\r\n",
		   (unsigned int) SD_CSD_TOTAL_SIZE(pCSD));
	trace_info(" -TOTAL_SIZE_HC      0x%X\r\n",
		   (unsigned int) SD_CSD_TOTAL_SIZE_HC(pCSD));
}

/**
 * Display the content of the EXT_CSD register
 * \param pExtCSD Pointer to extended CSD data.
 */
void
SD_DumpExtCSD(void *pExtCSD)
{
	trace_info("======= Extended Device Specific Data =======\n\r");
	trace_info(" .S_CMD_SET            : 0x%X\n\r",
		   MMC_EXT_S_CMD_SET(pExtCSD));
	trace_info(" .BOOT_INFO            : 0x%X\n\r",
		   MMC_EXT_BOOT_INFO(pExtCSD));
	trace_info(" .BOOT_SIZE_MULTI      : 0x%X\n\r",
		   MMC_EXT_BOOT_SIZE_MULTI(pExtCSD));
	trace_info(" .ACC_SIZE             : 0x%X\n\r",
		   MMC_EXT_ACC_SIZE(pExtCSD));
	trace_info(" .HC_ERASE_GRP_SIZE    : 0x%X\n\r",
		   MMC_EXT_HC_ERASE_GRP_SIZE(pExtCSD));
	trace_info(" .ERASE_TIMEOUT_MULT   : 0x%X\n\r",
		   MMC_EXT_ERASE_TIMEOUT_MULT(pExtCSD));
	trace_info(" .REL_WR_SEC_C         : 0x%X\n\r",
		   MMC_EXT_REL_WR_SEC_C(pExtCSD));
	trace_info(" .HC_WP_GRP_SIZE       : 0x%X\n\r",
		   MMC_EXT_HC_WP_GRP_SIZE(pExtCSD));
	trace_info(" .S_C_VCC              : 0x%X\n\r",
		   MMC_EXT_S_C_VCC(pExtCSD));
	trace_info(" .S_C_VCCQ             : 0x%X\n\r",
		   MMC_EXT_S_C_VCCQ(pExtCSD));
	trace_info(" .S_A_TIMEOUT          : 0x%X\n\r",
		   MMC_EXT_S_A_TIMEOUT(pExtCSD));
	trace_info(" .SEC_COUNT            : 0x%X\n\r",
		   MMC_EXT_SEC_COUNT(pExtCSD));
	trace_info(" .MIN_PERF_W_8_52      : 0x%X\n\r",
		   MMC_EXT_MIN_PERF_W_8_52(pExtCSD));
	trace_info(" .MIN_PERF_R_8_52      : 0x%X\n\r",
		   MMC_EXT_MIN_PERF_R_8_52(pExtCSD));
	trace_info(" .MIN_PERF_W_8_26_4_52 : 0x%X\n\r",
		   MMC_EXT_MIN_PERF_W_8_26_4_52(pExtCSD));
	trace_info(" .MIN_PERF_R_8_26_4_52 : 0x%X\n\r",
		   MMC_EXT_MIN_PERF_R_8_26_4_52(pExtCSD));
	trace_info(" .MIN_PERF_W_4_26      : 0x%X\n\r",
		   MMC_EXT_MIN_PERF_W_4_26(pExtCSD));
	trace_info(" .MIN_PERF_R_4_26      : 0x%X\n\r",
		   MMC_EXT_MIN_PERF_R_4_26(pExtCSD));
	trace_info(" .PWR_CL_26_360        : 0x%X\n\r",
		   MMC_EXT_PWR_CL_26_360(pExtCSD));
	trace_info(" .PWR_CL_52_360        : 0x%X\n\r",
		   MMC_EXT_PWR_CL_52_360(pExtCSD));
	trace_info(" .PWR_CL_26_195        : 0x%X\n\r",
		   MMC_EXT_PWR_CL_26_195(pExtCSD));
	trace_info(" .PWR_CL_52_195        : 0x%X\n\r",
		   MMC_EXT_PWR_CL_52_195(pExtCSD));
	trace_info(" .CARD_TYPE            : 0x%X\n\r",
		   MMC_EXT_CARD_TYPE(pExtCSD));
	trace_info(" .CSD_STRUCTURE        : 0x%X\n\r",
		   MMC_EXT_CSD_STRUCTURE(pExtCSD));
	trace_info(" .EXT_CSD_REV          : 0x%X\n\r",
		   MMC_EXT_EXT_CSD_REV(pExtCSD));
	trace_info(" .CMD_SET              : 0x%X\n\r",
		   MMC_EXT_CMD_SET(pExtCSD));
	trace_info(" .CMD_SET_REV          : 0x%X\n\r",
		   MMC_EXT_CMD_SET_REV(pExtCSD));
	trace_info(" .POWER_CLASS          : 0x%X\n\r",
		   MMC_EXT_POWER_CLASS(pExtCSD));
	trace_info(" .HS_TIMING            : 0x%X\n\r",
		   MMC_EXT_HS_TIMING(pExtCSD));
	trace_info(" .BUS_WIDTH            : 0x%X\n\r",
		   MMC_EXT_BUS_WIDTH(pExtCSD));
	trace_info(" .ERASED_MEM_CONT      : 0x%X\n\r",
		   MMC_EXT_ERASED_MEM_CONT(pExtCSD));
	trace_info(" .BOOT_CONFIG          : 0x%X\n\r",
		   MMC_EXT_BOOT_CONFIG(pExtCSD));
	trace_info(" .BOOT_BUS_WIDTH       : 0x%X\n\r",
		   MMC_EXT_BOOT_BUS_WIDTH(pExtCSD));
	trace_info(" .ERASE_GROUP_DEF      : 0x%X\n\r",
		   MMC_EXT_ERASE_GROUP_DEF(pExtCSD));
}

/**
 * Display the content of the SCR register
 * \param pSCR  Pointer to SCR data.
 */
void
SD_DumpSCR(void *pSCR)
{
	trace_info("========== SCR ==========");
	trace_info_wp("\n\r");

	trace_info(" .SCR_STRUCTURE         :0x%X\n\r",
		   (unsigned int) SD_SCR_STRUCTURE(pSCR));
	trace_info(" .SD_SPEC               :0x%X\n\r",
		   (unsigned int) SD_SCR_SD_SPEC(pSCR));
	trace_info(" .DATA_STAT_AFTER_ERASE :0x%X\n\r",
		   (unsigned int) SD_SCR_DATA_STAT_AFTER_ERASE(pSCR));
	trace_info(" .SD_SECURITY           :0x%X\n\r",
		   (unsigned int) SD_SCR_SD_SECURITY(pSCR));
	trace_info(" .SD_BUS_WIDTHS         :0x%X\n\r",
		   (unsigned int) SD_SCR_SD_BUS_WIDTHS(pSCR));
}

/**
 * Display the content of the SD Status
 * \param pSdST  Pointer to SD card status data.
 */
void
SD_DumpSdStatus(void *pSdST)
{
	trace_info("=========== STAT ============");
	trace_info_wp("\n\r");

	trace_info(" .DAT_BUS_WIDTH          :0x%X\n\r",
		   (unsigned int) SD_ST_DAT_BUS_WIDTH(pSdST));
	trace_info(" .SECURED_MODE           :0x%X\n\r",
		   (unsigned int) SD_ST_SECURED_MODE(pSdST));
	trace_info(" .SD_CARD_TYPE           :0x%X\n\r",
		   (unsigned int) SD_ST_CARD_TYPE(pSdST));
	// trace_info(" .SIZE_OF_PROTECTED_AREA :0x%X\n\r",
	//   (unsigned int)SD_ST_SIZE_OF_PROTECTED_AREA(pSdST));
	trace_info(" .SPEED_CLASS            :0x%X\n\r",
		   (unsigned int) SD_ST_SPEED_CLASS(pSdST));
	trace_info(" .PERFORMANCE_MOVE       :0x%X\n\r",
		   (unsigned int) SD_ST_PERFORMANCE_MOVE(pSdST));
	trace_info(" .AU_SIZE                :0x%X\n\r",
		   (unsigned int) SD_ST_AU_SIZE(pSdST));
	trace_info(" .ERASE_SIZE             :0x%X\n\r",
		   (unsigned int) SD_ST_ERASE_SIZE(pSdST));
	trace_info(" .ERASE_TIMEOUT          :0x%X\n\r",
		   (unsigned int) SD_ST_ERASE_TIMEOUT(pSdST));
	trace_info(" .ERASE_OFFSET           :0x%X\n\r",
		   (unsigned int) SD_ST_ERASE_OFFSET(pSdST));
}

/**
 * Provide a textual name matching the specified IO Control
 * \param dwCtrl  IO Control code (SDMMC_IOCTL_xxx).
 */
const char *
SD_StringifyIOCtrl(uint32_t dwCtrl)
{
#ifdef NOTRACE
	(void) dwCtrl;
	return sdmmcEmptyString;
#else
	const uint8_t bound = ARRAY_SIZE(sdmmcIOCtrlNames);
	uint8_t ix;

	for (ix = 0; ix < bound; ix++) {
		if (dwCtrl == (uint32_t)sdmmcIOCtrlNames[ix].key)
			return sdmmcIOCtrlNames[ix].name;
	}

	return sdmmcInvalidIOCtrl;
#endif
}

/**
 * Provide a textual name matching the specified return code
 * \param dwRCode  Return code, from the eSDMMC_RC enumeration.
 */
const char *
SD_StringifyRetCode(uint32_t dwRCode)
{
#ifdef NOTRACE
	(void) dwRCode;
	return sdmmcEmptyString;
#else
	const uint8_t bound = ARRAY_SIZE(sdmmcRCodeNames);
	uint8_t ix;

	for (ix = 0; ix < bound; ix++) {
		if (dwRCode == (uint32_t)sdmmcRCodeNames[ix].key)
			return sdmmcRCodeNames[ix].name;
	}

	return sdmmcInvalidRCode;
#endif
}

/**@}*/
