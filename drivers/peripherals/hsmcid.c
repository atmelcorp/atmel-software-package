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

/** \file
 *
 * driver for High Speed MultiMedia Card Interface (HSMCI).
 */

/* By default, do not compile debug-level traces of this module. Expect them to
 * be enabled explicitly, e.g. in the Makefile of the application. */
#ifdef SDMMC_DRV_TRACE_LEVEL
# undef TRACE_LEVEL
# define TRACE_LEVEL SDMMC_DRV_TRACE_LEVEL
#elif TRACE_LEVEL > 4
# undef TRACE_LEVEL
# define TRACE_LEVEL 4
#endif

/*---------------------------------------------------------------------------
 *         Headers
 *---------------------------------------------------------------------------*/

#include "trace.h"
#include "board.h"
#include "intmath.h"
#include "timer.h"
#include "peripherals/pmc.h"
#include "peripherals/tc.h"
#include "peripherals/hsmcic.h"
#include "peripherals/hsmcid.h"
#include "peripherals/xdmac.h"
#include "peripherals/xdmad.h"
#include "libsdmmc/sdmmc_hal.h"
#include "libsdmmc/sdmmc_api.h"
#include "misc/cache.h"

#include <assert.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** Driver state */
#define MCID_OFF    0       /**< Device not powered */
#define MCID_IDLE   1       /**< Idle */
#define MCID_LOCKED 2       /**< Locked for specific slot */
#define MCID_CMD    3       /**< Processing the command */
#define MCID_ERROR  4       /**< Command error */

/** Return word(32-bit) count from byte count */
#define toWCOUNT(byteCnt)  (((byteCnt)&0x3) ? (((byteCnt)/4)+1) : ((byteCnt)/4))

/** Bit mask for status register errors. */
#define STATUS_ERRORS ((uint32_t)(HSMCI_SR_UNRE  \
                       | HSMCI_SR_OVRE \
                       | HSMCI_SR_ACKRCVE \
                       | HSMCI_SR_CSTOE \
                       | HSMCI_SR_DTOE \
                       | HSMCI_SR_DCRCE \
                       | HSMCI_SR_RTOE \
                       | HSMCI_SR_RENDE \
                       | HSMCI_SR_RCRCE \
                       | HSMCI_SR_RDIRE \
                       | HSMCI_SR_RINDE))

/** Bit mask for response errors */
#define STATUS_ERRORS_RESP ((uint32_t)(HSMCI_SR_CSTOE \
							| HSMCI_SR_RTOE \
							| HSMCI_SR_RENDE \
							| HSMCI_SR_RCRCE \
							| HSMCI_SR_RDIRE \
							| HSMCI_SR_RINDE))

/** Bit mask for data errors */
#define STATUS_ERRORS_DATA ((uint32_t)(HSMCI_SR_UNRE \
							| HSMCI_SR_OVRE \
							| HSMCI_SR_DTOE \
							| HSMCI_SR_DCRCE))

/** Max DMA size in a single transfer */
#define MAX_DMA_SIZE (XDMAC_MAX_BT_SIZE & 0xffffff00)

static void hsmci_finish_cmd(struct hsmci_set *set, uint8_t bStatus);

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static uint8_t hsmci_set_speed_mode(struct hsmci_set *set, uint8_t mode)
{
	assert(set);

	Hsmci *regs = set->regs;

	if ((mode > SDMMC_TIM_MMC_HS_SDR && mode < SDMMC_TIM_SD_DS)
		|| mode > SDMMC_TIM_SD_HS)
		return SDMMC_ERROR_PARAM;

	if ((mode == SDMMC_TIM_MMC_BC) || (mode == SDMMC_TIM_SD_DS))
		hsmci_enable_hs(regs, false);
	else
		hsmci_enable_hs(regs, true);
	set->tim_mode = mode;

	return SDMMC_OK;
}

static void hsmci_set_device_clock(struct hsmci_set *set, uint32_t freq)
{
	assert(set);
	assert(freq);

	Hsmci *regs = set->regs;
	uint32_t div, new_freq;
	uint32_t mck = pmc_get_master_clock();

	if ((mck % freq) == 0)
		div = mck / freq;
	else
		div = (mck + freq) / freq;
	new_freq = mck / div;

	/* Modify MR */
	hsmci_set_clock(regs, div, 0x7);
	set->dev_freq = new_freq;
}

static void hsmci_handler(struct hsmci_set *set)
{
	Hsmci *regs = set->regs;
	sSdmmcCommand *pCmd = set->cmd;
	uint32_t dwSr, dwMsk, dwMaskedSr;
	assert(regs);

	/* Do nothing if no pending command */
	if (pCmd == NULL) {
		if (set->state >= MCID_CMD)
			set->state = MCID_LOCKED;
		return;
	}

	xdmad_poll();

	/* Read status */
	dwSr  = hsmci_get_status(regs);
	dwMsk = hsmci_get_it_mask(regs);
	dwMaskedSr = dwSr & dwMsk;
	/* Check errors */
	if (dwMaskedSr & STATUS_ERRORS) {
		if (dwMaskedSr & HSMCI_SR_RTOE)
			pCmd->bStatus = SDMMC_ERROR_NORESPONSE;

		if (pCmd->bCmd != 12)
			set->state = MCID_ERROR;
		trace_warning("error status: 0x%08lx\n\r", dwMaskedSr);
	}
	dwMsk &= ~STATUS_ERRORS;

	/* Check command complete */
	if (dwMaskedSr & HSMCI_SR_CMDRDY) {
		trace_debug("CMDRDY \n\r");
		hsmci_disable_it(regs, HSMCI_IDR_CMDRDY);
		dwMsk &= ~(uint32_t)HSMCI_IMR_CMDRDY;
	}

	/* Check if not busy */
	if (dwMaskedSr & HSMCI_SR_NOTBUSY) {
		trace_debug("NOTBUSY ");
		hsmci_disable_it(regs, HSMCI_IDR_NOTBUSY);
		dwMsk &= ~(uint32_t)HSMCI_IMR_NOTBUSY;
	}
	/* Check if TX ready */
	if (dwMaskedSr & HSMCI_SR_TXRDY) {
		trace_debug("TXRDY ");
		dwMsk &= ~(uint32_t)HSMCI_IMR_TXRDY;
	}
	/* Check if FIFO empty (all data sent) */
	if (dwMaskedSr & HSMCI_SR_FIFOEMPTY) {
		/* Disable FIFO empty */
		hsmci_disable_it(regs, HSMCI_IDR_FIFOEMPTY);
		dwMsk &= ~(uint32_t)HSMCI_IMR_FIFOEMPTY;
		trace_debug("FIFOEMPTY %lx \n\r", dwMsk);
	}

	/* Check if DMA finished */
	if (dwMaskedSr & HSMCI_SR_XFRDONE) {

		hsmci_disable_it(regs, HSMCI_IDR_XFRDONE);
		dwMsk &= ~(uint32_t)HSMCI_IMR_XFRDONE;
		trace_debug("XFRDONE %lx \n\r", dwMsk);
	}

	/* All none error mask done, complete the command */
	if (0 == dwMsk || set->state == MCID_ERROR) {
		/* Error reset */
		if (set->state == MCID_ERROR)
			hsmci_reset(regs, true);
		else {
			pCmd->bStatus = SDMMC_SUCCESS;

			if (pCmd->pResp) {
				uint8_t bRspSize, i;
				switch(pCmd->cmdOp.bmBits.respType) {
				case 1: case 3: case 4: case 5: case 6: case 7:
					bRspSize = 1;
					break;
				case 2:
					bRspSize = 4;
					break;
				default:
					bRspSize = 0;
				}
				for (i = 0; i < bRspSize; i ++)
					pCmd->pResp[i] =
						hsmci_get_response(regs);
			}
		}
		/* Disable interrupts */
		hsmci_disable_it(regs, hsmci_get_it_mask(regs));
		/* Command is finished */
		hsmci_finish_cmd(set, pCmd->bStatus);
	}
}

/**
 * \brief Check if the command is finished.
 */
static bool hsmci_is_busy(struct hsmci_set *set)
{
	assert(set->state != MCID_OFF);

	if (set->use_polling)
		hsmci_handler(set);
	if (set->state == MCID_CMD)
		return true;
	return false;
}

static uint8_t hsmci_cancel_command(struct hsmci_set *set)
{
	assert(set);

	if (set->state == MCID_IDLE)
		return SDMMC_ERROR_STATE;
	if (set->state == MCID_CMD) {
		/* Cancel ... */
		hsmci_reset(set->regs, true);
		/* Command is finished */
		hsmci_finish_cmd(set, SDMMC_ERROR_USER_CANCEL);
	}
	return SDMMC_OK;
}

static void _hsmci_xdmad_callback_wrapper(struct _xdmad_channel *channel,
	void *arg)
{
	struct hsmci_set *set = (struct hsmci_set*) arg;

	(void) channel;

	if (set->region_start && set->region_size)
		cache_invalidate_region((void *)set->region_start,
			set->region_size);
}

/**
 * HSMCI DMA R/W prepare
 */
static uint32_t hsmci_prepare_dma(struct hsmci_set *set, uint8_t bRd)
{
	set->dma_channel = xdmad_allocate_channel(
		bRd ? set->id : XDMAD_PERIPH_MEMORY,
		bRd ? XDMAD_PERIPH_MEMORY : set->id);
	if (NULL == set->dma_channel)
		return SDMMC_ERROR_BUSY;
	xdmad_set_callback(set->dma_channel, _hsmci_xdmad_callback_wrapper,
		set);
	return SDMMC_SUCCESS;
}

static uint32_t hsmci_dma(struct hsmci_set *set, uint32_t bFByte, uint8_t bRd)
{
	Hsmci *regs = set->regs;
	sSdmmcCommand *cmd = set->cmd;
	struct _xdmad_cfg xdma_cfg;
	uint32_t xdmaCndc;
	uint8_t i;
	uint32_t totalSize = cmd->wNbBlocks * cmd->wBlockSize;
	uint32_t maxXSize;
	uint32_t memAddress;
	uint8_t  bMByte;

	if (set->dwXfrNdx >= totalSize)
		return 0;

	memset(&xdma_cfg, 0, sizeof(xdma_cfg));
	/* Prepare DMA transfer */
	if (cmd->wBlockSize != 1) {
		set->dwXSize = totalSize - set->dwXfrNdx;
		if (bRd) {
			trace_debug("hsmci_dma read %d,%d \n\r",
				cmd->wBlockSize, cmd->bCmd);
			assert(cmd->wNbBlocks <= set->link_list_size);
			for (i = 0; i < cmd->wNbBlocks; i++) {
				set->dma_link_list[i].mbr_ubc =
					XDMA_UBC_NVIEW_NDV1
					| (i == cmd->wNbBlocks - 1
					? 0 : XDMA_UBC_NDE_FETCH_EN)
					| XDMA_UBC_NDEN_UPDATED
					| cmd->wBlockSize / 4;
				set->dma_link_list[i].mbr_sa = (uint32_t*)
					&regs->HSMCI_FIFO[i];
				set->dma_link_list[i].mbr_da =
					&cmd->pData[i * cmd->wBlockSize];
				set->dma_link_list[i].mbr_nda =
					i == cmd->wNbBlocks - 1 ?
					NULL : &set->dma_link_list[i + 1];
			}
			set->region_start = (uint32_t)cmd->pData;
			set->region_size = totalSize;
			xdma_cfg.cfg = XDMAC_CC_TYPE_PER_TRAN
				| XDMAC_CC_MBSIZE_SINGLE
				| XDMAC_CC_DSYNC_PER2MEM
				| XDMAC_CC_CSIZE_CHK_1
				| XDMAC_CC_DWIDTH_WORD
				| XDMAC_CC_SIF_AHB_IF1
				| XDMAC_CC_DIF_AHB_IF0
				| XDMAC_CC_SAM_FIXED_AM
				| XDMAC_CC_DAM_INCREMENTED_AM;
		} else {
			trace_debug("hsmci_dma write %d,%d \n\r",
				cmd->wBlockSize, cmd->bCmd);
			assert(cmd->wNbBlocks <= set->link_list_size);
			for (i = 0; i < cmd->wNbBlocks; i++) {
				set->dma_link_list[i].mbr_ubc =
					XDMA_UBC_NVIEW_NDV1
					| (i == cmd->wNbBlocks - 1
					? 0 : XDMA_UBC_NDE_FETCH_EN)
					| XDMA_UBC_NDEN_UPDATED
					| cmd->wBlockSize / 4;
				set->dma_link_list[i].mbr_sa =
					&cmd->pData[i * cmd->wBlockSize];
				set->dma_link_list[i].mbr_da = (uint32_t*)
					&regs->HSMCI_FIFO[i];
				set->dma_link_list[i].mbr_nda =
					i == cmd->wNbBlocks - 1 ?
					NULL : &set->dma_link_list[i + 1];
			}
			set->region_size = 0;
			cache_clean_region(cmd->pData, totalSize);
			xdma_cfg.cfg = XDMAC_CC_TYPE_PER_TRAN
				| XDMAC_CC_MBSIZE_SINGLE
				| XDMAC_CC_DSYNC_MEM2PER
				| XDMAC_CC_CSIZE_CHK_1
				| XDMAC_CC_DWIDTH_WORD
				| XDMAC_CC_SIF_AHB_IF0
				| XDMAC_CC_DIF_AHB_IF1
				| XDMAC_CC_SAM_INCREMENTED_AM
				| XDMAC_CC_DAM_FIXED_AM;
		}
		xdmaCndc = XDMAC_CNDC_NDVIEW_NDV1
				| XDMAC_CNDC_NDE_DSCR_FETCH_EN
				| XDMAC_CNDC_NDSUP_SRC_PARAMS_UPDATED
				| XDMAC_CNDC_NDDUP_DST_PARAMS_UPDATED;
		cache_clean_region(set->dma_link_list,
			set->link_list_size * sizeof(struct _xdmad_desc_view1));
		if (xdmad_configure_transfer(set->dma_channel, &xdma_cfg,
			xdmaCndc, set->dma_link_list))
			return 0;
	} else {
		/* Memory address and alignment */
		memAddress = (uint32_t)&cmd->pData[set->dwXfrNdx];
		bMByte = bFByte ? 1 : (memAddress & 0x3) || (totalSize & 0x3);
		/* P to M: Max size is P size */
		if (bRd)
			maxXSize = bFByte ? MAX_DMA_SIZE : (MAX_DMA_SIZE * 4);
		/* M to P: Max size is M size */
		else
			maxXSize = bMByte ? MAX_DMA_SIZE : (MAX_DMA_SIZE * 4);
		/* Update index */
		set->dwXSize = totalSize - set->dwXfrNdx;
		if (set->dwXSize > maxXSize)
			set->dwXSize = maxXSize;
		/* Prepare DMA transfer */
		if (bRd) {
			xdma_cfg.ubc = bFByte
				? set->dwXSize : toWCOUNT(set->dwXSize);
			xdma_cfg.sa = (uint32_t*)&regs->HSMCI_RDR;
			xdma_cfg.da = (void *)memAddress;
			xdma_cfg.cfg = XDMAC_CC_TYPE_PER_TRAN
					| XDMAC_CC_MEMSET_NORMAL_MODE
					| XDMAC_CC_DSYNC_PER2MEM
					| XDMAC_CC_CSIZE_CHK_1
					| (bFByte ? XDMAC_CC_DWIDTH_BYTE
					: XDMAC_CC_DWIDTH_WORD)
					| XDMAC_CC_SIF_AHB_IF1
					| XDMAC_CC_DIF_AHB_IF0
					| XDMAC_CC_SAM_FIXED_AM
					| XDMAC_CC_DAM_INCREMENTED_AM;
			set->region_start = memAddress;
			set->region_size = xdma_cfg.ubc;
		} else {
			xdma_cfg.ubc = bFByte
				? set->dwXSize : toWCOUNT(set->dwXSize);
			xdma_cfg.sa = (void *)memAddress;
			xdma_cfg.da = (uint32_t*)&regs->HSMCI_TDR;
			xdma_cfg.cfg = XDMAC_CC_TYPE_PER_TRAN
					| XDMAC_CC_MEMSET_NORMAL_MODE
					| XDMAC_CC_DSYNC_MEM2PER
					| XDMAC_CC_CSIZE_CHK_1
					| (bFByte ? XDMAC_CC_DWIDTH_BYTE
					: XDMAC_CC_DWIDTH_WORD)
					| XDMAC_CC_SIF_AHB_IF0
					| XDMAC_CC_DIF_AHB_IF1
					| XDMAC_CC_SAM_INCREMENTED_AM
					| XDMAC_CC_DAM_FIXED_AM;
			set->region_size = 0;
			cache_clean_region((void *)memAddress,
				xdma_cfg.ubc);
		}
		xdma_cfg.bc = 0;
		if (xdmad_configure_transfer(set->dma_channel, &xdma_cfg, 0, 0))
			return 0;
	}
	if (xdmad_start_transfer(set->dma_channel))
		return 0;
	return 1;
}

static void hsmci_finish_cmd(struct hsmci_set *set, uint8_t bStatus)
{
	sSdmmcCommand *cmd = set->cmd;

	/* Release DMA channel (if used) */
	if (set->dma_channel != NULL) {
		if (!xdmad_is_transfer_done(set->dma_channel))
			xdmad_stop_transfer(set->dma_channel);
		if (xdmad_free_channel(set->dma_channel)) {
			trace_error("Can't free xdma channel\n\r");
		}
		set->dma_channel = NULL;
	}
	/* Release command */
	set->cmd = NULL;
	set->state = MCID_LOCKED;
	cmd->bStatus = bStatus;
	/* Invoke callback */
	if (cmd->fCallback)
		(cmd->fCallback)(cmd->bStatus, cmd->pArg);
}

/*----------------------------------------------------------------------------
 *        HAL for the SD/MMC library
 *----------------------------------------------------------------------------*/

/**
 * Here is the fSdmmcLock-type callback.
 * Lock the driver for slot N access.
 * TODO implement, once used by the library.
 */
static uint32_t hsmci_lock(void *_set, uint8_t slot)
{
	assert(_set);

	struct hsmci_set *set = (struct hsmci_set *)_set;
	Hsmci *regs = set->regs;

	if (slot > 0)
		return SDMMC_ERROR_PARAM;
	if (set->state >= MCID_LOCKED)
		return SDMMC_ERROR_LOCKED;
	set->state = MCID_LOCKED;
	hsmci_set_slot(regs, slot);
	return SDMMC_OK;
}

/**
 * Here is the fSdmmcRelease-type callback.
 * Release the driver.
 * TODO implement, once used by the library.
 */
static uint32_t hsmci_release(void *_set)
{
	assert(_set);

	struct hsmci_set *set = (struct hsmci_set *)_set;

	if (set->state >= MCID_CMD)
		return SDMMC_ERROR_BUSY;
	set->state = MCID_IDLE;
	return SDMMC_OK;
}

/**
 * Here is the fSdmmcIOCtrl-type callback.
 * IO control functions.
 * \param _set  Pointer to driver instance data (struct sdmmc_set).
 * \param bCtl  IO control code.
 * \param param  IO control parameter. Optional, depends on the IO control code.
 * \return Return code, from the eSDMMC_RC enumeration.
 */
static uint32_t hsmci_control(void *_set, uint32_t bCtl, uint32_t param)
{
	assert(_set);

	struct hsmci_set *set = (struct hsmci_set *)_set;
	uint32_t rc = SDMMC_OK, *param_u32 = (uint32_t *)param;
	uint8_t byte;
	bool on;

#if TRACE_LEVEL >= TRACE_LEVEL_DEBUG
	if (bCtl != SDMMC_IOCTL_BUSY_CHECK && bCtl != SDMMC_IOCTL_GET_DEVICE)
		trace_debug("SDMMC_IOCTL_%s(%lu)\n\r", SD_StringifyIOCtrl(bCtl),
			param ? *param_u32 : 0);
#endif

	switch (bCtl) {
	case SDMMC_IOCTL_GET_DEVICE:
		if (!param)
			return SDMMC_ERROR_PARAM;
		*param_u32 = board_is_sdmmc_inserted(set->id) ? 1 : 0;
		break;

	case SDMMC_IOCTL_POWER:
		if (!param)
			return SDMMC_ERROR_PARAM;
		on = *param_u32 ? true : false;
		if ((on && set->state != MCID_OFF)
			|| (!on && set->state == MCID_OFF)) {
		} else {
			board_power_sdmmc_device(set->id, on);
			if (!on)
				hsmci_reset(set->regs, true);
			set->state = on ? MCID_IDLE : MCID_OFF;
		}
		break;

	case SDMMC_IOCTL_RESET:
		/* Release the device. The device may have been removed. */
		board_power_sdmmc_device(set->id, false);
		hsmci_reset(set->regs, true);
		break;

	case SDMMC_IOCTL_GET_BUSMODE:
		if (!param)
			return SDMMC_ERROR_PARAM;
		byte = hsmci_get_bus_width(set->regs);
		*param_u32 = byte;
		break;

	case SDMMC_IOCTL_SET_BUSMODE:
		if (!param)
			return SDMMC_ERROR_PARAM;
		if (*param_u32 > 0xff)
			return SDMMC_ERROR_PARAM;
		hsmci_set_bus_width(set->regs, (uint8_t)*param_u32);
		byte = hsmci_get_bus_width(set->regs);
		trace_debug("Using a %u-bit data bus\n\r", byte);
		if (byte != (uint8_t)*param_u32)
			rc = SDMMC_ERROR_PARAM;
		break;

	case SDMMC_IOCTL_GET_HSMODE:
		if (!param)
			return SDMMC_ERROR_PARAM;
		if (*param_u32 > 0xff) {
			*param_u32 = 0;
			break;
		}
		byte = (uint8_t)*param_u32;
		if (byte == SDMMC_TIM_MMC_BC || byte == SDMMC_TIM_SD_DS
			|| byte == SDMMC_TIM_MMC_HS_SDR
			|| byte == SDMMC_TIM_SD_HS)
			*param_u32 = 1;
		else
			*param_u32 = 0;
		break;

	case SDMMC_IOCTL_SET_HSMODE:
		if (!param)
			return SDMMC_ERROR_PARAM;
		if (*param_u32 > 0xff)
			return SDMMC_ERROR_PARAM;
		rc = hsmci_set_speed_mode(set, (uint8_t)*param_u32);
		*param_u32 = set->tim_mode;
		trace_debug("Using timing mode 0x%02x\n\r", set->tim_mode);
		break;

	case SDMMC_IOCTL_SET_CLOCK:
		if (!param)
			return SDMMC_ERROR_PARAM;
		if (*param_u32 == 0)
			return SDMMC_ERROR_PARAM;
		hsmci_set_device_clock(set, *param_u32);
		trace_debug("Clocking the device at %lu Hz\n\r", set->dev_freq);
		if (set->dev_freq != *param_u32) {
			rc = rc == SDMMC_OK ? SDMMC_CHANGED : rc;
			*param_u32 = set->dev_freq;
		}
		break;

	case SDMMC_IOCTL_SET_LENPREFIX:
		if (!param)
			return SDMMC_ERROR_PARAM;
		*param_u32 = 0;
		break;

	case SDMMC_IOCTL_GET_XFERCOMPL:
		if (!param)
			return SDMMC_ERROR_PARAM;
		*param_u32 = 0;
		break;

	case SDMMC_IOCTL_BUSY_CHECK:
		if (!param)
			return SDMMC_ERROR_PARAM;
		if (set->state == MCID_OFF)
			*param_u32 = 0;
		else
			*param_u32 = hsmci_is_busy(set) ? 1 : 0;
		break;

	case SDMMC_IOCTL_CANCEL_CMD:
		if (set->state == MCID_OFF)
			rc = SDMMC_STATE;
		else
			rc = hsmci_cancel_command(set);
		break;

	case SDMMC_IOCTL_GET_CLOCK:
	case SDMMC_IOCTL_SET_BOOTMODE:
	case SDMMC_IOCTL_GET_BOOTMODE:
	default:
		rc = SDMMC_ERROR_NOT_SUPPORT;
		break;
	}
#if TRACE_LEVEL >= TRACE_LEVEL_ERROR
	if (rc != SDMMC_OK && rc != SDMMC_CHANGED
		&& bCtl != SDMMC_IOCTL_BUSY_CHECK) {
		trace_error("SDMMC_IOCTL_%s ended with %s\n\r",
			SD_StringifyIOCtrl(bCtl), SD_StringifyRetCode(rc));
	}
#endif
	return rc;
}

/**
 * Here is the fSdmmcSendCommand-type callback.
 * SD/MMC command.
 * \param _set  Pointer to driver instance data (struct hsmci_set).
 * \param cmd  Pointer to the command to be sent. Owned by the caller. Shall
 * remain valid until the command is completed or stopped. For commands which
 * transfer data, mind the peripheral and DMA alignment requirements that the
 * external data buffer shall meet. Especially when DMA is used to read from the
 * device, in which case the buffer shall be aligned on entire cache lines.
 * \return Return code, from the eSDMMC_RC enumeration. If SDMMC_OK, the command
 * has been issued and the caller should:
 *   1. poll on sdmmc_is_busy(),
 *   2. once finished, check the result of the command in cmd->bStatus.
 * TODO in future when libsdmmc will set it: call sSdmmcCommand::fCallback.
 */
static uint32_t hsmci_send_command(void *_set, sSdmmcCommand *cmd)
{
	assert(_set);
	assert(cmd);

	struct hsmci_set *set = (struct hsmci_set *)_set;
	Hsmci *regs = set->regs;
	uint32_t mr, ier;
	uint32_t cmdr;
	uint8_t is_read;

	if (hsmci_is_busy(set))
		return SDMMC_ERROR_BUSY;

	set->state = MCID_CMD;
	set->cmd   = cmd;

	trace_debug("cmd %d, op 0x%04x, %d x %d, arg 0x%08lx, status %d\n\r",
		cmd->bCmd, cmd->cmdOp.wVal, cmd->wBlockSize, cmd->wNbBlocks,
		cmd->dwArg, cmd->bStatus);

	hsmci_disable(regs);
	mr = hsmci_get_mode(regs) & ~HSMCI_MR_WRPROOF & ~HSMCI_MR_RDPROOF
		& ~HSMCI_MR_FBYTE;

	/* Special: PowerON Init */
	if (cmd->cmdOp.wVal == SDMMC_CMD_POWERONINIT) {
		hsmci_cfg_mode(regs, mr);
		ier = HSMCI_IER_XFRDONE;
	}
	/* Normal command: idle the bus */
	else if (cmd->cmdOp.bmBits.xfrData == SDMMC_CMD_STOPXFR) {
		hsmci_cfg_mode(regs, mr);
		ier = HSMCI_IER_XFRDONE | STATUS_ERRORS_RESP;
	}
	/* No data transfer */
	else if ((cmd->cmdOp.wVal & SDMMC_CMD_CNODATA(0xf))
		== SDMMC_CMD_CNODATA(0)) {
		ier = HSMCI_IER_XFRDONE | STATUS_ERRORS_RESP;
		/* R3 response, no CRC */
		if (cmd->cmdOp.bmBits.respType == 3)
			ier &= ~(uint32_t)HSMCI_IER_RCRCE;
	}
	/* Data command but no following */
	else if (cmd->wNbBlocks == 0 || cmd->pData == 0) {
		hsmci_cfg_mode(regs, mr | HSMCI_MR_WRPROOF | HSMCI_MR_RDPROOF);
		hsmci_cfg_xfer(regs, cmd->wBlockSize, cmd->wNbBlocks);
		ier = HSMCI_IER_CMDRDY | STATUS_ERRORS_RESP;
	}
	/* Command with data */
	else {
		/* Setup block size */
		if (cmd->cmdOp.bmBits.sendCmd)
			hsmci_cfg_xfer(regs, cmd->wBlockSize, cmd->wNbBlocks);
		/* Block size is 0, force byte */
		if (cmd->wBlockSize == 0)
			cmd->wBlockSize = 1;

		/* Force byte transfer */
		if (cmd->wBlockSize & 0x3)
			mr |= HSMCI_MR_FBYTE;
		/* Set block size & MR */
		hsmci_cfg_mode(regs, mr | HSMCI_MR_WRPROOF | HSMCI_MR_RDPROOF);

		is_read = (cmd->cmdOp.bmBits.xfrData == SDMMC_CMD_TX) ? 0 : 1;
		if (hsmci_prepare_dma(set, is_read)) {
			hsmci_finish_cmd(set, SDMMC_ERROR_BUSY);
			return SDMMC_ERROR_BUSY;
		}
		trace_debug("DMA %s\n\r", is_read ? "read" : "write");
		hsmci_dma(set, mr & HSMCI_MR_FBYTE, is_read);

		ier = HSMCI_IER_XFRDONE | STATUS_ERRORS_DATA;
		if (cmd->wNbBlocks > 1)
			ier |= HSMCI_IER_FIFOEMPTY;
	}
	hsmci_enable(regs);
	if (cmd->cmdOp.wVal & (SDMMC_CMD_bmPOWERON | SDMMC_CMD_bmCOMMAND)) {
		cmdr = cmd->bCmd;

		if (cmd->cmdOp.bmBits.powerON)
			cmdr |= HSMCI_CMDR_OPDCMD | HSMCI_CMDR_SPCMD_INIT;
		if (cmd->cmdOp.bmBits.odON)
			cmdr |= HSMCI_CMDR_OPDCMD;
		if (cmd->cmdOp.bmBits.sendCmd)
			cmdr |= HSMCI_CMDR_MAXLAT;
		switch (cmd->cmdOp.bmBits.xfrData) {
			case SDMMC_CMD_TX:
				cmdr |= HSMCI_CMDR_TRCMD_START_DATA;
				if (cmd->cmdOp.bmBits.ioCmd)
					cmdr |= cmd->wBlockSize == 1
						? HSMCI_CMDR_TRTYP_BYTE
						: HSMCI_CMDR_TRTYP_BLOCK;
				else
					cmdr |= cmd->wNbBlocks == 1
						? HSMCI_CMDR_TRTYP_SINGLE
						: HSMCI_CMDR_TRTYP_MULTIPLE;
				break;

			case SDMMC_CMD_RX:
				cmdr |= HSMCI_CMDR_TRDIR_READ
					| HSMCI_CMDR_TRCMD_START_DATA;
				if (cmd->cmdOp.bmBits.ioCmd)
					cmdr |= cmd->wBlockSize == 1
						? HSMCI_CMDR_TRTYP_BYTE
						: HSMCI_CMDR_TRTYP_BLOCK;
				else
					cmdr |= cmd->wNbBlocks == 1
						? HSMCI_CMDR_TRTYP_SINGLE
						: HSMCI_CMDR_TRTYP_MULTIPLE;
				break;

			case SDMMC_CMD_STOPXFR:
				cmdr |= HSMCI_CMDR_TRCMD_STOP_DATA;
				break;
		}
		switch (cmd->cmdOp.bmBits.respType) {
			case 3: case 4:
				/* ignore CRC error */
				ier &= ~(uint32_t)HSMCI_IER_RCRCE;
			case 1: case 5: case 6: case 7:
				cmdr |= HSMCI_CMDR_RSPTYP_48_BIT;
				break;
			case 2:
				cmdr |= HSMCI_CMDR_RSPTYP_136_BIT;
				break;
			/* No response, ignore RTOE */
			default:
				ier &= ~(uint32_t)HSMCI_IER_RTOE;
				break;
		}

		hsmci_send_cmd(regs, cmdr, cmd->dwArg);
	}

	/* Ignore CRC error for R3 & R4 */
	if (cmd->cmdOp.bmBits.xfrData == SDMMC_CMD_STOPXFR)
		ier &= ~STATUS_ERRORS_DATA;

	/* Enable status flags */
	hsmci_enable_it(regs, ier);

	return SDMMC_OK;
}

static sSdHalFunctions sdHal = {
	.fLock = hsmci_lock,
	.fRelease = hsmci_release,
	.fCommand = hsmci_send_command,
	.fIOCtrl = hsmci_control,
};

/*---------------------------------------------------------------------------
 *         Exported functions
 *---------------------------------------------------------------------------*/

bool hsmci_initialize(struct hsmci_set *set, Hsmci *regs, uint32_t periph_id,
	uint32_t tc_id, uint32_t tc_ch,
	struct _xdmad_desc_view1 *dma_dlist, uint32_t dlist_size)
{
	assert(set);
	assert(regs);
	assert(periph_id <= 0xff);
	assert(tc_ch < TCCHANNEL_NUMBER);
	assert(dma_dlist);

	Tc * const tc_module = get_tc_addr_from_id(tc_id);

	assert(tc_module);
	memset(set, 0, sizeof(*set));
	set->id = periph_id;
	set->regs = regs;
	set->tc_id = tc_id;
	set->timer = &tc_module->TC_CHANNEL[tc_ch];
	set->link_list_size = dlist_size;
	set->dma_link_list = dma_dlist;
	set->use_polling = true;
	set->state = MCID_OFF;

	/* Prepare our Timer/Counter */
	tc_configure(tc_module, tc_ch, TC_CMR_WAVE | TC_CMR_WAVSEL_UP
		| TC_CMR_CPCDIS | TC_CMR_BURST_NONE
		| TC_CMR_TCCLKS_TIMER_CLOCK2);
	set->timer->TC_EMR |= TC_EMR_NODIVCLK;

	hsmci_disable_it(regs, ~0ul);
	hsmci_reset(set->regs, false);
	hsmci_disable_it(regs, ~0ul);

	hsmci_enable(regs);
	hsmci_configure(regs, HSMCI_CFG_FIFOMODE | HSMCI_CFG_FERRCTRL);
	hsmci_enable_dma(regs, true);
	hsmci_cfg_data_timeout(regs, HSMCI_DTOR_DTOCYC_Msk
		| HSMCI_DTOR_DTOMUL_1048576);
	hsmci_cfg_compl_timeout(regs, HSMCI_CSTOR_CSTOCYC_Msk
		| HSMCI_CSTOR_CSTOMUL_1048576);
	return true;
}

/**
 * \brief Initialize the SD/MMC library instance for SD/MMC bus mode (versus
 * SPI mode, not supported by this driver). Provide it with the HAL callback
 * functions implemented here.
 * \param pSd   Pointer to SD/MMC library instance data.
 * \param pDrv  Pointer to driver instance data (struct sdmmc_set).
 * \param bSlot Slot number.
 */
void SDD_InitializeSdmmcMode(sSdCard *pSd, void *pDrv, uint8_t bSlot)
{
	SDD_Initialize(pSd, pDrv, bSlot, &sdHal);
}
