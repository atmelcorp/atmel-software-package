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
#include "peripherals/dma.h"
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

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static uint8_t hsmci_cancel_command(struct hsmci_set *set);
static uint8_t hsmci_release_dma(struct hsmci_set *set);
static void hsmci_finish_cmd(struct hsmci_set *set, uint8_t bStatus);

static void hsmci_power_device(struct hsmci_set *set, bool on)
{
	assert(set);

	if ((on && set->state != MCID_OFF) || (!on && set->state == MCID_OFF))
		return;
	if (on) {
		trace_debug("Power the device on\n\r");
		board_power_sdmmc_device(set->id, true);
		hsmci_enable(set->regs);
		set->state = MCID_IDLE;
		return;
	}
	trace_debug("Release and power the device off\n\r");
	if (set->state == MCID_CMD)
		hsmci_cancel_command(set);
	/* Cut the power rail supplying signals to/from the device */
	set->dev_freq = 0;
	hsmci_disable(set->regs);
	/* Reset the Mode Register */
	hsmci_cfg_mode(set->regs, hsmci_get_mode(set->regs)
		& (HSMCI_MR_CLKDIV_Msk | HSMCI_MR_PWSDIV_Msk));
	/* Reset the Block Register */
	hsmci_cfg_xfer(set->regs, 0, 0);
	/* Reset the peripheral. This will reset almost all registers. */
	hsmci_reset(set->regs, true);
	board_power_sdmmc_device(set->id, false);
	set->state = MCID_OFF;
}

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
	uint32_t dwSr, dwMaskedSr;
	assert(regs);

	/* Do nothing if no pending command */
	if (pCmd == NULL) {
		if (set->state >= MCID_CMD)
			set->state = MCID_LOCKED;
		return;
	}

	if (set->use_polling)
		dma_poll();

	/* Read status */
	dwSr = hsmci_get_status(regs);
	dwMaskedSr = dwSr & hsmci_get_it_mask(regs);
	/* Check errors */
	if (dwMaskedSr & STATUS_ERRORS) {
		if (dwMaskedSr & HSMCI_SR_RTOE)
			pCmd->bStatus = SDMMC_ERROR_NORESPONSE;
		else
			pCmd->bStatus = SDMMC_ERR_IO;
		set->state = MCID_ERROR;
		trace_debug("HSMCI_SR 0x%08lx\n\r", dwSr);
	}

	/* Check command complete */
	if (dwMaskedSr & HSMCI_SR_CMDRDY) {
		hsmci_disable_it(regs, HSMCI_IDR_CMDRDY);
		set->nxt_evts &= ~(uint32_t)HSMCI_IMR_CMDRDY;
		trace_debug("CMDRDY\n\r");
	}
	/* Check if not busy */
	if (dwMaskedSr & HSMCI_SR_NOTBUSY) {
		hsmci_disable_it(regs, HSMCI_IDR_NOTBUSY);
		set->nxt_evts &= ~(uint32_t)HSMCI_IMR_NOTBUSY;
		trace_debug("NOTBUSY\n\r");
	}
	/* Check if FIFO empty (all data sent) */
	if (dwMaskedSr & HSMCI_SR_FIFOEMPTY) {
		hsmci_disable_it(regs, HSMCI_IDR_FIFOEMPTY);
		set->nxt_evts &= ~(uint32_t)HSMCI_IMR_FIFOEMPTY;
		trace_debug("FIFOEMPTY\n\r");
	}
	/* Check if data transfer has completed */
	if (dwMaskedSr & HSMCI_SR_XFRDONE) {
		hsmci_disable_it(regs, HSMCI_IDR_XFRDONE);
		set->nxt_evts &= ~(uint32_t)HSMCI_IMR_XFRDONE;
		trace_debug("XFRDONE\n\r");
	}

	/* All none error mask done, complete the command */
	if (set->nxt_evts == 0 || set->state == MCID_ERROR) {
		/* Disable interrupts */
		hsmci_disable_it(regs, ~0ul);
		/* Halt the DMA (if used) */
		hsmci_release_dma(set);
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
		hsmci_release_dma(set);
		hsmci_reset(set->regs, true);
		/* Command is finished */
		hsmci_finish_cmd(set, SDMMC_ERROR_USER_CANCEL);
	}
	return SDMMC_OK;
}

static void _hsmci_dma_callback_wrapper(struct dma_channel *channel,
	void *arg)
{
	struct hsmci_set *set = (struct hsmci_set*) arg;

	(void) channel;
	assert(set);
	assert(set->regs);

	hsmci_enable_it(set->regs, HSMCI_IER_XFRDONE);
}

/**
 * \brief Release the DMA channel
 * \return SDMMC_SUCCESS if the DMA channel has been released without issue.
 */
static uint8_t hsmci_release_dma(struct hsmci_set *set)
{
	uint32_t rc;
	uint8_t res = SDMMC_SUCCESS;

	assert(set);

	if (set->dma_channel == NULL)
		return SDMMC_ERROR_STATE;
	rc = dma_stop_transfer(set->dma_channel);
	if (rc != DMA_OK) {
		trace_error("Error halting DMA channel\n\r");
		res = SDMMC_ERROR_STATE;
	}
	rc = dma_free_channel(set->dma_channel);
	if (rc != DMA_OK) {
		trace_error("Couldn't free DMA channel\n\r");
		res = SDMMC_ERROR_STATE;
	}
	set->dma_channel = NULL;
	return res;
}

/**
 * \brief Prepare a DMA channel
 * \return SDMMC_SUCCESS if the DMA channel is ready for transfer setup.
 */
static uint8_t hsmci_prepare_dma(struct hsmci_set *set, uint8_t bRd)
{
	uint32_t rc;

	assert(set);

	set->dma_channel = dma_allocate_channel(
		bRd ? set->id : DMA_PERIPH_MEMORY,
		bRd ? DMA_PERIPH_MEMORY : set->id);
	if (NULL == set->dma_channel)
		return SDMMC_ERROR_BUSY;
	rc = dma_set_callback(set->dma_channel, _hsmci_dma_callback_wrapper,
		set);
	if (rc != DMA_OK) {
		hsmci_release_dma(set);
		return SDMMC_ERROR_STATE;
	}
	return SDMMC_SUCCESS;
}

/**
 * \brief Configure and start DMA for the specified data transfer
 * \return SDMMC_SUCCESS if the DMA transfer has been started.
 */
static uint8_t hsmci_configure_dma(struct hsmci_set *set, uint8_t bRd)
{
	sSdmmcCommand * const cmd = set->cmd;

	assert(set);
	assert(cmd);
	assert(cmd->wBlockSize != 0 && cmd->wNbBlocks != 0);

	const uint32_t ubl_len_max = DMA_MAX_BT_SIZE;
	const uint32_t ubl_cnt_max = (DMA_MAX_BLOCK_LEN + 1ul);
	const uint8_t unit = cmd->wBlockSize & 0x3 ? 1 : 4;
	uint32_t rc, ubl_len, ubl_cnt, quot;
	uint8_t shift, fail;
	struct dma_xfer_cfg dma_cfg;

	dma_cfg.chunk_size = XDMAC_CC_CSIZE_CHK_1;
	dma_cfg.data_width = (unit == 1) ? DMA_DATA_WIDTH_BYTE : DMA_DATA_WIDTH_WORD;
	if (bRd) {
		dma_cfg.upd_sa_per_data = 0;
		dma_cfg.upd_da_per_data = 1;
	} else {
		dma_cfg.upd_sa_per_data = 1;
		dma_cfg.upd_da_per_data = 0;
	}
	/* Configure data count per microblock */
	ubl_len = (cmd->wBlockSize / unit) * (uint32_t)cmd->wNbBlocks;
	/* Configure microblock count per block */
	ubl_cnt = 1;
	if (ubl_len > ubl_len_max) {
		/* Split transfer to fit the limit that each XDMAC level has */
		if (cmd->wBlockSize / unit <= ubl_len_max
			&& cmd->wNbBlocks <= ubl_cnt_max) {
			ubl_len = cmd->wBlockSize / unit;
			ubl_cnt = cmd->wNbBlocks;
		}
		else if (cmd->wBlockSize / unit <= ubl_cnt_max
			&& cmd->wNbBlocks <= ubl_len_max) {
			ubl_len = cmd->wNbBlocks;
			ubl_cnt = cmd->wBlockSize / unit;
		}
		else {
			/* Try dividing size by 2, 4, 8, etc. */
			quot = CEIL_INT_DIV(ubl_len, ubl_len_max);
			for (fail = 0, shift = 0; !fail; shift++) {
				if (ubl_len & 1ul << shift
					|| 2ul << shift > ubl_cnt_max)
					fail = 1;
				else if (2ul << shift >= quot)
					break;
			}
			/* Note that we may try harder, dividing size by
			 * quot +0, +1, +2, etc. however it would be slow. */
			if (fail)
				return SDMMC_ERROR_PARAM;
			ubl_len >>= shift + 1;
			ubl_cnt = 2ul << shift;
		}
	}
	dma_cfg.blk_size = ubl_len;
	dma_cfg.len = ubl_cnt - 1;
	/* We may transfer to/from HSMCI_FIFO, however, on ATSAMV71, using
	 * HSMCI_TDR and HSMCI_RDR registers is as fast as using HSMCI_FIFO. */
	dma_cfg.sa = bRd ? (void*)&set->regs->HSMCI_RDR : cmd->pData;
	dma_cfg.da = bRd ? cmd->pData : (void*)&set->regs->HSMCI_TDR;
	/* Configure a single block per master transfer, i.e. no linked list */
	rc = dma_configure_transfer(set->dma_channel, &dma_cfg);
	if (rc != DMA_OK)
		return SDMMC_ERROR_BUSY;
	if (bRd)
		/* Invalidate the corresponding data cache lines now, so this
		 * buffer is protected against a global cache clean operation,
		 * that concurrent code may trigger.
		 * Warning: until the command is reported as complete, no code
		 * should read from this buffer, nor from variables cached in
		 * the same lines. If such anticipated reading had to be
		 * supported, the data cache lines would need to be invalidated
		 * twice: both now and upon completion of the DMA transfer. */
		cache_invalidate_region(cmd->pData, cmd->wBlockSize
			* (uint32_t)cmd->wNbBlocks);
	else
		cache_clean_region(cmd->pData, cmd->wBlockSize
			* (uint32_t)cmd->wNbBlocks);
	rc = dma_start_transfer(set->dma_channel);
	return rc == DMA_OK ? SDMMC_SUCCESS : SDMMC_ERROR_STATE;
}

static void hsmci_finish_cmd(struct hsmci_set *set, uint8_t bStatus)
{
	sSdmmcCommand * const cmd = set->cmd;

	/* Release DMA channel (if used) */
	hsmci_release_dma(set);
	/* Release command */
	set->cmd = NULL;
	set->state = MCID_LOCKED;
	if (cmd == NULL)
		return;
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
		hsmci_power_device(set, *param_u32 ? true : false);
		break;

	case SDMMC_IOCTL_RESET:
		/* Release the device. The device may have been removed. */
		hsmci_power_device(set, false);
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
	uint32_t cmdr = 0;
	uint16_t blkr_len, blkr_cnt;
	uint8_t rc, is_read, blk_io = 0;
	const uint8_t has_data = cmd->cmdOp.bmBits.xfrData == SDMMC_CMD_TX
		|| cmd->cmdOp.bmBits.xfrData == SDMMC_CMD_RX;

	if (has_data && (cmd->wBlockSize == 0 || cmd->wNbBlocks == 0
		|| cmd->pData == NULL))
		return SDMMC_ERROR_PARAM;
	if (hsmci_is_busy(set))
		return SDMMC_ERROR_BUSY;

	trace_debug("cmd %d, op 0x%04x, %d x %d, arg 0x%08lx, status %d\n\r",
		cmd->bCmd, cmd->cmdOp.wVal, cmd->wBlockSize, cmd->wNbBlocks,
		cmd->dwArg, cmd->bStatus);
	hsmci_disable_it(regs, ~0ul);
	hsmci_disable(regs);

	set->state = MCID_CMD;
	set->cmd = cmd;
	cmd->bStatus = SDMMC_SUCCESS;
	set->nxt_evts = 0;
	mr = hsmci_get_mode(regs) & ~HSMCI_MR_WRPROOF & ~HSMCI_MR_RDPROOF
		& ~HSMCI_MR_FBYTE;

	/* Special: PowerON Init */
	if (cmd->cmdOp.wVal == SDMMC_CMD_POWERONINIT) {
		hsmci_cfg_mode(regs, mr);
		set->nxt_evts = ier = HSMCI_IER_XFRDONE;
	}
	/* Normal command: idle the bus */
	else if (cmd->cmdOp.bmBits.xfrData == SDMMC_CMD_STOPXFR) {
		hsmci_cfg_mode(regs, mr);
		set->nxt_evts = HSMCI_IER_XFRDONE;
		ier = set->nxt_evts | STATUS_ERRORS_RESP;
	}
	else if ((cmd->cmdOp.wVal & SDMMC_CMD_CNODATA(0xf))
		== SDMMC_CMD_CNODATA(0)) {
		/* Command without response */
		hsmci_cfg_mode(regs, mr);
		set->nxt_evts = HSMCI_IER_XFRDONE;
		ier = set->nxt_evts | STATUS_ERRORS_RESP;
	}
	else if (!has_data) {
		hsmci_cfg_mode(regs, mr | HSMCI_MR_WRPROOF | HSMCI_MR_RDPROOF);
		hsmci_cfg_xfer(regs, 0, 0);
		set->nxt_evts = HSMCI_IER_XFRDONE;
		ier = set->nxt_evts | STATUS_ERRORS_RESP;
	}
	/* Command with data */
	else {
		if (cmd->cmdOp.bmBits.ioCmd && cmd->bCmd == 53) {
			SdioCmd53Arg *cmd_arg = (SdioCmd53Arg*)&cmd->dwArg;
			blk_io = cmd_arg->blockMode;
		}
		/* Setup transfer size */
		if (cmd->cmdOp.bmBits.sendCmd) {
			blkr_len = cmd->cmdOp.bmBits.ioCmd && !blk_io
				? 0 : cmd->wBlockSize;
			blkr_cnt = cmd->cmdOp.bmBits.ioCmd && !blk_io
				? cmd->wBlockSize : cmd->wNbBlocks;
			hsmci_cfg_xfer(regs, blkr_len, blkr_cnt);
		}
		/* Data chunks and blocks - including SDIO byte operations -
		 * whose size is not a multiple of 4 bytes are supported with
		 * specific handling. */
		if (cmd->wBlockSize & 0x3)
			mr |= HSMCI_MR_FBYTE;
		/* Set block size & MR */
		hsmci_cfg_mode(regs, mr | HSMCI_MR_WRPROOF | HSMCI_MR_RDPROOF);

		is_read = (cmd->cmdOp.bmBits.xfrData == SDMMC_CMD_TX) ? 0 : 1;
		rc = hsmci_prepare_dma(set, is_read);
		if (rc == SDMMC_SUCCESS)
			rc = hsmci_configure_dma(set, is_read);
		if (rc != SDMMC_SUCCESS) {
			hsmci_enable(regs);
			hsmci_finish_cmd(set, rc);
			trace_error("DMA error %u\n\r", rc);
			return rc;
		}
		set->nxt_evts = HSMCI_IER_XFRDONE;
		/* Let's ensure the DMA transfer has completed, before enabling
		 * the XFRDONE interrupt that will close the request. */
		ier = STATUS_ERRORS_RESP | STATUS_ERRORS_DATA;
	}

	if (cmd->cmdOp.wVal & (SDMMC_CMD_bmPOWERON | SDMMC_CMD_bmCOMMAND)) {
		cmdr = cmd->bCmd;
		if (cmd->cmdOp.bmBits.powerON)
			cmdr |= HSMCI_CMDR_OPDCMD | HSMCI_CMDR_SPCMD_INIT;
		if (cmd->cmdOp.bmBits.odON)
			cmdr |= HSMCI_CMDR_OPDCMD;
		if (cmd->cmdOp.bmBits.sendCmd)
			cmdr |= HSMCI_CMDR_MAXLAT;
		switch (cmd->cmdOp.bmBits.xfrData) {
			case SDMMC_CMD_RX:
				cmdr |= HSMCI_CMDR_TRDIR_READ;
			case SDMMC_CMD_TX:
				cmdr |= HSMCI_CMDR_TRCMD_START_DATA;
				if (cmd->cmdOp.bmBits.ioCmd)
					cmdr |= blk_io ? HSMCI_CMDR_TRTYP_BLOCK
						: HSMCI_CMDR_TRTYP_BYTE;
				else
					cmdr |= cmd->wNbBlocks > 1
						? HSMCI_CMDR_TRTYP_MULTIPLE
						: HSMCI_CMDR_TRTYP_SINGLE;
				break;

			case SDMMC_CMD_STOPXFR:
				cmdr |= HSMCI_CMDR_TRCMD_STOP_DATA;
				break;
		}
		switch (cmd->cmdOp.bmBits.respType) {
			case 3:
				/* The R3 response misses the CRC */
				ier &= ~(uint32_t)HSMCI_IER_RCRCE;
			case 4:
				if (cmd->cmdOp.bmBits.respType == 4
					&& cmd->cmdOp.bmBits.ioCmd)
					/* SDIO R4 response misses the CRC */
					ier &= ~(uint32_t)HSMCI_IER_RCRCE;
			case 1: case 5: case 6: case 7:
				cmdr |= cmd->cmdOp.bmBits.checkBsy
					? HSMCI_CMDR_RSPTYP_R1B
					: HSMCI_CMDR_RSPTYP_48_BIT;
				break;
			case 2:
				cmdr |= HSMCI_CMDR_RSPTYP_136_BIT;
				break;
			default:
				/* No response, ignore Response Time-out */
				ier &= ~(uint32_t)HSMCI_IER_RTOE;
				break;
		}
	}

	hsmci_enable(regs);
	hsmci_enable_it(regs, ier);
	if (cmd->cmdOp.wVal & (SDMMC_CMD_bmPOWERON | SDMMC_CMD_bmCOMMAND))
		hsmci_send_cmd(regs, cmdr, cmd->dwArg);
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
	uint32_t tc_id, uint32_t tc_ch)
{
	assert(set);
	assert(regs);
	assert(periph_id <= 0xff);
	assert(tc_ch < TCCHANNEL_NUMBER);

	Tc * const tc_module = get_tc_addr_from_id(tc_id);

	assert(tc_module);
	memset(set, 0, sizeof(*set));
	set->id = periph_id;
	set->regs = regs;
	set->tc_id = tc_id;
	set->timer = &tc_module->TC_CHANNEL[tc_ch];
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
