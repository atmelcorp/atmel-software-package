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

#include "peripherals/pmc.h"
#include "peripherals/spi.h"
#include "peripherals/spid.h"
#include "peripherals/aic.h"

#include "trace.h"

#include <stddef.h>
#include <stdint.h>

#define SPID_ATTRIBUTE_MASK     (SPI_MR_PS | SPI_MR_MODFDIS | SPI_MR_MSTR)

#ifdef CONFIG_HAVE_SPI_FIFO
static void spid_fifo_error(void)
{
	trace_error("Fifo pointer error encountered !!\r\n");
}

void spid_set_mode_to_fifo(struct _spi_desc* desc)
{
	if (desc->transfert_mode != SPID_MODE_FIFO) {
		spi_fifo_configure(desc->addr, SPI_FIFO_DEPTH, SPI_FIFO_DEPTH,
				   SPI_FMR_TXRDYM_ONE_DATA | SPI_FMR_RXRDYM_ONE_DATA);
	}
	desc->transfert_mode = SPID_MODE_FIFO;
}
#endif

void spid_configure(struct _spi_desc* desc)
{
	spi_configure(desc->addr, (desc->attributes & SPID_ATTRIBUTE_MASK) | SPI_MR_MSTR);
	spi_chip_select(desc->addr, desc->chip_select);
	spi_configure_cs(desc->addr, desc->chip_select, desc->bitrate,
			 desc->dlybs, desc->dlybct, desc->spi_mode, 0);
#ifdef CONFIG_HAVE_SPI_FIFO
	if (desc->transfert_mode == SPID_MODE_FIFO) {
		spi_fifo_configure(desc->addr, SPI_FIFO_DEPTH, SPI_FIFO_DEPTH,
				   SPI_FMR_TXRDYM_ONE_DATA | SPI_FMR_RXRDYM_ONE_DATA);
	}
	aic_set_source_vector(desc->id, spid_fifo_error);
	spi_enable_it(desc->addr, SPI_IER_TXFPTEF | SPI_IER_RXFPTEF);
	aic_enable(desc->id);
#endif
	pmc_enable_peripheral(desc->id);
	spi_enable(desc->addr);
}

void spid_begin_transfert(struct _spi_desc* desc)
{
	spi_chip_select(desc->addr, desc->chip_select);
	spi_configure_cs_mode(desc->addr, desc->chip_select, SPI_KEEP_CS_OW);
}

uint32_t spid_transfert(struct _spi_desc* desc, struct _buffer* rx,
			struct _buffer* tx, spid_callback_t cb,
			void* user_args)
{
	Spi* spi = desc->addr;
	uint32_t i = 0;

	if (!desc->mutex) {
		return SPID_ERROR_LOCK;
	}

	desc->mutex--;

	switch (desc->transfert_mode) {
	case SPID_MODE_POLLING:
		if (tx) {
			for (i = 0; i < tx->size; ++i) {
				spi_write(spi, desc->chip_select, tx->data[i]);
			}
		}
		if (rx) {
			for (i = 0; i < rx->size; ++i) {
				rx->data[i] = spi_read(spi);
			}
		}
		desc->mutex++;
		if (cb)
			cb(desc, user_args);
		break;
	case SPID_MODE_DMA:
		break;
#ifdef CONFIG_HAVE_SPI_FIFO
	case SPID_MODE_FIFO:
		if (tx) {
			spi_write_stream(spi, desc->chip_select,
					 tx->data, tx->size);
		}
		if (rx) {
			spi_read_stream(spi, desc->chip_select,
					rx->data, rx->size);
		}
		desc->mutex++;
		if (cb)
			cb(desc, user_args);
		break;
#endif
	default:
		trace_debug("Unkown mode");
	}

	return SPID_SUCCESS;
}

void spid_finish_transfert_callback(struct _spi_desc* desc, void* user_args)
{
	(void)user_args;
	spid_finish_transfert(desc);
}

void spid_finish_transfert(struct _spi_desc* desc)
{
	spi_release_cs(desc->addr);
}

void spid_close(const struct _spi_desc* desc)
{
	spi_disable(desc->addr);
	pmc_disable_peripheral(desc->id);
}

uint32_t spid_is_busy(const struct _spi_desc* desc)
{
	if (desc->mutex) {
		return 0;
	}
	return 0;
}

void spid_wait_transfert(const struct _spi_desc* desc)
{
	while(!desc->mutex);
}
