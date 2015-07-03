/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2011, Atmel Corporation
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


/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "peripherals/twihs.h"
#include "peripherals/twihsd.h"
#include "peripherals/xdmad.h"
#include "cortex-a/cp15.h"
#include "trace.h"

#include <assert.h>

/*----------------------------------------------------------------------------
 *        Definition
 *----------------------------------------------------------------------------*/
#define TWITIMEOUTMAX 0xfffff

static struct _xdmad_cfg twi_dmaCfg;
static struct _xdmad_channel *dmaWriteChannel;
static struct _xdmad_channel *dmaReadChannel;
static struct _xdmad_desc_view1 dmaWriteLinkList[1];
static struct _xdmad_desc_view1 dmaReadLinkList[1];

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

/** TWI driver callback function.*/
typedef void (*TwiCallback)(Async *);

/** \brief TWI asynchronous transfer descriptor.*/
typedef struct _AsyncTwi {

	/** Asynchronous transfer status. */
	volatile uint8_t status;
	/** Callback function to invoke when transfer completes or fails.*/
	TwiCallback callback;
	/** Pointer to the data buffer.*/
	uint8_t *pData;
	/** Total number of bytes to transfer.*/
	uint32_t num;
	/** Number of already transferred bytes.*/
	uint32_t transferred;

} AsyncTwi;

/**
 * \brief Initializes a TWI DMA Read channel.
 */
static void twihsd_dma_initialize_read(uint8_t TWIHS_ID)
{
	/* Allocate a XDMA channel, Read accesses into TWI_THR */
	dmaReadChannel = xdmad_allocate_channel( TWIHS_ID, XDMAD_PERIPH_MEMORY);
	if ( !dmaReadChannel ) {
		printf("-E- Can't allocate XDMA channel\n\r");
	}
	xdmad_prepare_channel(dmaReadChannel );
}

/**
 * \brief Initializes a TWI DMA write channel.
 */
static void twihsd_dma_initialize_write(uint8_t TWIHS_ID)
{
	/* Allocate a XDMA channel, Write accesses into TWI_THR */
	dmaWriteChannel = xdmad_allocate_channel(XDMAD_PERIPH_MEMORY, TWIHS_ID);
	if ( !dmaWriteChannel ) {
		printf("-E- Can't allocate XDMA channel\n\r");
	}
	xdmad_prepare_channel(dmaWriteChannel );
}

/**
 * \brief Configure xDMA write linker list for TWI transfer.
 */
static void twihsd_dma_configure_write(uint8_t *buf, uint32_t len, uint8_t twi_id) {
	uint32_t xdmaCndc, Thr;
	uint32_t i;
	Thr = (uint32_t)&(TWIHS0->TWIHS_THR);
	if(twi_id == ID_TWIHS1) {
		Thr = (uint32_t)&(TWIHS1->TWIHS_THR);
	}
	
	for (i = 0; i < 1; i++) {
		dmaWriteLinkList[i].ublock_size = XDMA_UBC_NVIEW_NDV1
		    | ((i == len - 1) ? 0 : XDMA_UBC_NDE_FETCH_EN)
		    | len;
		dmaWriteLinkList[i].src_addr = & buf[i];
		dmaWriteLinkList[i].dest_addr = (void*)Thr;
		if (i == len - 1)
			dmaWriteLinkList[i].next_desc = 0;
		else
			dmaWriteLinkList[i].next_desc =
			    & dmaWriteLinkList[i + 1];
	}
	twi_dmaCfg.cfg.uint32_value = XDMAC_CC_TYPE_PER_TRAN
	    | XDMAC_CC_MBSIZE_SINGLE
	    | XDMAC_CC_DSYNC_MEM2PER
	    | XDMAC_CC_CSIZE_CHK_1
	    | XDMAC_CC_DWIDTH_BYTE
	    | XDMAC_CC_SIF_AHB_IF0
	    | XDMAC_CC_DIF_AHB_IF1
	    | XDMAC_CC_SAM_INCREMENTED_AM
	    | XDMAC_CC_DAM_FIXED_AM
	    |
	    XDMAC_CC_PERID(get_peripheral_xdma_channel(twi_id, XDMAC0, true));
	xdmaCndc =
	    XDMAC_CNDC_NDVIEW_NDV1 | XDMAC_CNDC_NDE_DSCR_FETCH_EN |
	    XDMAC_CNDC_NDSUP_SRC_PARAMS_UPDATED |
	    XDMAC_CNDC_NDDUP_DST_PARAMS_UNCHANGED;
	cp15_coherent_dcache_for_dma((uint32_t) & dmaWriteLinkList,
				     ((uint32_t) & dmaWriteLinkList +
				      sizeof (*dmaWriteLinkList) * len));
	xdmad_configure_transfer(dmaWriteChannel, &twi_dmaCfg,
				xdmaCndc, dmaWriteLinkList);
}


/**
 * \brief Configure xDMA read linker list for TWI transfer.
 */
static void twihsd_dma_configure_read(uint8_t *buf, uint32_t len , uint8_t twi_id) {
	uint32_t xdmaCndc, Rhr;
	uint32_t i;
	Rhr = (uint32_t)&(TWIHS0->TWIHS_RHR);
	if( twi_id ==ID_TWIHS1) {
		Rhr = (uint32_t)&(TWIHS1->TWIHS_RHR);
	}
	
	for (i = 0; i < 1; i++) {
		dmaReadLinkList[i].ublock_size = XDMA_UBC_NVIEW_NDV1
		    | ((i == len - 1) ? 0 : XDMA_UBC_NDE_FETCH_EN)
		    | len;
		dmaReadLinkList[i].src_addr = (void*)Rhr;
		dmaReadLinkList[i].dest_addr = & buf[i];
		if (i == len - 1)
			dmaReadLinkList[i].next_desc = 0;
		else
			dmaReadLinkList[i].next_desc =
			    & dmaReadLinkList[i + 1];
	}
	twi_dmaCfg.cfg.uint32_value = XDMAC_CC_TYPE_PER_TRAN
	    | XDMAC_CC_MBSIZE_SINGLE
	    | XDMAC_CC_DSYNC_PER2MEM
	    | XDMAC_CC_CSIZE_CHK_1
	    | XDMAC_CC_DWIDTH_BYTE
	    | XDMAC_CC_SIF_AHB_IF1
	    | XDMAC_CC_DIF_AHB_IF0
	    | XDMAC_CC_SAM_FIXED_AM
	    | XDMAC_CC_DAM_INCREMENTED_AM
	    |
	    XDMAC_CC_PERID(get_peripheral_xdma_channel(twi_id, XDMAC0, false));
	xdmaCndc =
	    XDMAC_CNDC_NDVIEW_NDV1 | XDMAC_CNDC_NDE_DSCR_FETCH_EN |
	    XDMAC_CNDC_NDSUP_SRC_PARAMS_UPDATED |
	    XDMAC_CNDC_NDDUP_DST_PARAMS_UPDATED;
	cp15_coherent_dcache_for_dma((uint32_t) & dmaReadLinkList,
				     ((uint32_t) & dmaReadLinkList +
				      sizeof (*dmaReadLinkList) * len));
	xdmad_configure_transfer(dmaReadChannel, &twi_dmaCfg, xdmaCndc,
				dmaReadLinkList);
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Returns 1 if the given transfer has ended; otherwise returns 0.
 * \param pAsync  Pointer to an Async instance.
 */
uint32_t twihsd_async_is_finished( Async* pAsync )
{
	return (pAsync->status != ASYNC_STATUS_PENDING) ;
}

/**
 * \brief Initializes a TWI driver instance, using the given TWI peripheral.
 * \note The peripheral must have been initialized properly before calling this
 * function.
 * \param pTwid  Pointer to the Twid instance to initialize.
 * \param pTwi  Pointer to the TWI peripheral to use.
 */
void twihsd_initialize(Twihsd *pTwid, Twihs *pTwi)
{
	trace_debug( "twihsd_initialize()\n\r" ) ;
	assert( pTwid != NULL ) ;
	assert( pTwi != NULL ) ;

	/* Initialize driver. */
	pTwid->pTwi = pTwi;
	pTwid->pTransfer = 0;
}

/**
 * \brief Interrupt handler for a TWI peripheral. Manages asynchronous transfer
 * occurring on the bus. This function MUST be called by the interrupt service
 * routine of the TWI peripheral if asynchronous read/write are needed.
 * \param pTwid  Pointer to a Twid instance.
 */
void twihsd_handler( Twihsd *pTwid )
{
	uint8_t status;
	AsyncTwi *pTransfer ;
	Twihs *pTwi ;

	assert( pTwid != NULL ) ;

	pTransfer = (AsyncTwi*)pTwid->pTransfer ;
	assert( pTransfer != NULL ) ;
	pTwi = pTwid->pTwi ;
	assert( pTwi != NULL ) ;

	/* Retrieve interrupt status */
	status = twihs_get_masked_status(pTwi);

	/* Byte received */
	if (TWIHS_STATUS_RXRDY(status)) {

		pTransfer->pData[pTransfer->transferred] = twihs_read_byte(pTwi);
		pTransfer->transferred++;

		/* check for transfer finish */
		if (pTransfer->transferred == pTransfer->num) {

			twihs_disable_it(pTwi, TWIHS_IDR_RXRDY);
			twihs_enable_it(pTwi, TWIHS_IER_TXCOMP);
		}
		/* Last byte? */
		else if (pTransfer->transferred == (pTransfer->num - 1)) {

			twihs_stop(pTwi);
		}
	}
	/* Byte sent*/
	else if (TWIHS_STATUS_TXRDY(status)) {

		/* Transfer finished ? */
		if (pTransfer->transferred == pTransfer->num) {

			twihs_disable_it(pTwi, TWIHS_IDR_TXRDY);
			twihs_enable_it(pTwi, TWIHS_IER_TXCOMP);
			twihs_send_stop_condition(pTwi);
		}
		/* Bytes remaining */
		else {

			twihs_write_byte(pTwi, pTransfer->pData[pTransfer->transferred]);
			pTransfer->transferred++;
		}
	}
	/* Transfer complete*/
	else if (TWIHS_STATUS_TXCOMP(status)) {

		twihs_disable_it(pTwi, TWIHS_IDR_TXCOMP);
		pTransfer->status = 0;
		if (pTransfer->callback) {
			pTransfer->callback((Async *) pTransfer);
		}
		pTwid->pTransfer = 0;
	}
}

/**
 * \brief Asynchronously reads data from a slave on the TWI bus. An optional
 * callback function is triggered when the transfer is complete.
 * \param pTwid  Pointer to a Twid instance.
 * \param address  TWI slave address.
 * \param iaddress  Optional slave internal address.
 * \param isize  Internal address size in bytes.
 * \param pData  Data buffer for storing received bytes.
 * \param num  Number of bytes to read.
 * \param pAsync  Asynchronous transfer descriptor.
 * \return 0 if the transfer has been started; otherwise returns a TWI error code.
 */
uint8_t twihsd_read(
		Twihsd *pTwihsd,
		uint8_t address,
		uint32_t iaddress,
		uint8_t isize,
		uint8_t *pData,
		uint32_t num,
		Async *pAsync)
{
	Twihs *pTwi;
	AsyncTwi *pTransfer;
	uint32_t timeout = 0;
	assert( pTwihsd != NULL ) ;
	pTwi = pTwihsd->pTwi;
	pTransfer = (AsyncTwi *) pTwihsd->pTransfer;

	assert( (address & 0x80) == 0 ) ;
	assert( (iaddress & 0xFF000000) == 0 ) ;
	assert( isize < 4 ) ;

	/* Check that no transfer is already pending*/
	if (pTransfer) {

		trace_error("twihsd_read: A transfer is already pending\n\r");
		return TWID_ERROR_BUSY;
	}

	/* Set STOP signal if only one byte is sent*/
	if (num == 1) {

		twihs_stop(pTwi);
	}

	/* Asynchronous transfer*/
	if (pAsync) {

		/* Update the transfer descriptor */
		pTwihsd->pTransfer = pAsync;
		pTransfer = (AsyncTwi *) pAsync;
		pTransfer->status = ASYNC_STATUS_PENDING;
		pTransfer->pData = pData;
		pTransfer->num = num;
		pTransfer->transferred = 0;

		/* Enable read interrupt and start the transfer */
		twihs_enable_it(pTwi, TWIHS_IER_RXRDY);
		twihs_start_read(pTwi, address, iaddress, isize);
	}
	/* Synchronous transfer*/
	else {
		/* Start read*/
		twihs_start_read(pTwi, address, iaddress, isize);

		/* Read all bytes, setting STOP before the last byte*/
		while (num > 0) {

			/* Last byte ?*/
			if (num == 1) {
				twihs_stop(pTwi);
			}
			/* Wait for byte then read and store it*/
			timeout = 0;
			while( !twihs_is_byte_received(pTwi)) {
				if (++timeout >= TWITIMEOUTMAX) {
					trace_error("TWID Timeout BR\n\r");
					break;
				}
			}
			
			*pData++ = twihs_read_byte(pTwi);
			num--;
		}
		timeout = 0;
		/* Wait for transfer to be complete */
		while( !twihs_is_transfer_complete(pTwi)) {
			if (++timeout >= TWITIMEOUTMAX) {
				trace_error("TWID Timeout TC\n\r");
				break;
			}
		}
	}
	return 0;
}

/**
 * \brief Asynchronously sends data to a slave on the TWI bus. An optional 
 * callback function is invoked whenever the transfer is complete.
 * \param pTwid  Pointer to a Twid instance.
 * \param address  TWI slave address.
 * \param iaddress  Optional slave internal address.
 * \param isize  Number of internal address bytes.
 * \param pData  Data buffer for storing received bytes.
 * \param num  Data buffer to send.
 * \param pAsync  Asynchronous transfer descriptor.
 * \return 0 if the transfer has been started; otherwise returns a TWI error code.
 */
uint8_t twihsd_write(
		Twihsd *pTwid,
		uint8_t address,
		uint32_t iaddress,
		uint8_t isize,
		uint8_t *pData,
		uint32_t num,
		Async *pAsync)
{
	Twihs *pTwi = pTwid->pTwi;
	AsyncTwi *pTransfer = (AsyncTwi *) pTwid->pTransfer;
	uint32_t timeout = 0;

	assert( pTwi != NULL ) ;
	assert( (address & 0x80) == 0 ) ;
	assert( (iaddress & 0xFF000000) == 0 ) ;
	assert( isize < 4 ) ;
	if (num == 1)
	/* Check that no transfer is already pending */
	if (pTransfer) {
		trace_error("TWI_Write: A transfer is already pending\n\r");
		return TWID_ERROR_BUSY;
	}

	/* Asynchronous transfer */
	if (pAsync) {
		/* Update the transfer descriptor */
		pTwid->pTransfer = pAsync;
		pTransfer = (AsyncTwi *) pAsync;
		pTransfer->status = ASYNC_STATUS_PENDING;
		pTransfer->pData = pData;
		pTransfer->num = num;
		pTransfer->transferred = 1;

		/* Enable write interrupt and start the transfer */
		twihs_start_write(pTwi, address, iaddress, isize, *pData);
		twihs_enable_it(pTwi, TWIHS_IER_TXRDY);
		
	} else {
		/* Synchronous transfer*/
		// Start write
		twihs_start_write(pTwi, address, iaddress, isize, *pData++);
		num--;
		/* Send all bytes */
		while (num > 0) {
			/* Wait before sending the next byte */
			timeout = 0;
			while( !twihs_byte_sent(pTwi)){
				if (++timeout >= TWITIMEOUTMAX) {
					trace_error("TWID Timeout BS\n\r");
					break;
				}
			}
			twihs_write_byte(pTwi, *pData++);
			num--;
		}
		/* Wait for actual end of transfer */
		/* Send a STOP condition */
		twihs_send_stop_condition(pTwi);
		timeout = 0;
		while( !twihs_is_transfer_complete(pTwi)){
			if ((++timeout >= TWITIMEOUTMAX)) {
				trace_error("TWID Timeout TC2\n\r");
				break;
			}
		}
	}

	return 0;
}

/**
 * \brief Asynchronously reads data from a slave on the TWI bus. An optional
 * callback function is triggered when the transfer is complete.
 * \param pTwid  Pointer to a Twid instance.
 * \param address  TWI slave address.
 * \param iaddress  Optional slave internal address.
 * \param isize  Internal address size in bytes.
 * \param pData  Data buffer for storing received bytes.
 * \param num  Number of bytes to read.
 * \param pAsync  Asynchronous transfer descriptor.
 * \param TWI_ID  TWI ID for TWI0, TWIHS1, TWIHS2.
 * \return 0 if the transfer has been started; otherwise returns a TWI error code.
 */
uint8_t twihsd_dma_read(
		Twihsd *pTwid,
		uint8_t address,
		uint32_t iaddress,
		uint8_t isize,
		uint8_t *pData,
		uint32_t num,
		Async *pAsync,
        uint8_t twi_id)
{
	AsyncTwi *pTransfer;
	Twihs *pTwi = pTwid->pTwi;
	uint32_t status, timeout;

	pTransfer = (AsyncTwi *)pTwid->pTransfer;

	assert( (address & 0x80) == 0 ) ;
	assert( (iaddress & 0xFF000000) == 0 ) ;
	assert( isize < 4 ) ;

	/* Check that no transfer is already pending*/
	if (pTransfer) {

		trace_error("twihsd_read: A transfer is already pending\n\r");
		return TWID_ERROR_BUSY;
	}
	/* Asynchronous transfer*/
	if (pAsync) {
		/* Update the transfer descriptor */
		pTwid->pTransfer = pAsync;
		pTransfer = (AsyncTwi *) pAsync;
		pTransfer->status = ASYNC_STATUS_PENDING;
		pTransfer->pData = pData;
		pTransfer->num = num;
		pTransfer->transferred = 0;

		/* Enable read interrupt and start the transfer */
		twihs_enable_it(pTwi, TWIHS_IER_RXRDY);
		twihs_start_read(pTwi, address, iaddress, isize);
	} else {
	/* Synchronous transfer*/
		twihsd_dma_initialize_read(ID_TWIHS0);
		twihsd_dma_configure_read(pData, (num - 2),ID_TWIHS0);
		
		// cache maintenance before starting DMA Xfr 
		// ..
		/* Start read*/
		xdmad_start_transfer(dmaReadChannel );
		twihs_start_read(pTwi, address, iaddress, isize);

		while( !xdmad_is_transfer_done(dmaReadChannel))
			xdmad_poll();
		status = twihs_get_status(pTwi);
		timeout = 0;
		while( !(status & TWIHS_SR_RXRDY)) {
			status = twihs_get_status(pTwi);
			if (++timeout >= TWITIMEOUTMAX) {
				trace_error("TWID DMA not done\n\r");
				break;
			}
		}
		twihs_stop(pTwi);
		
		pData[num - 2] = twihs_read_byte(pTwi);
		status = twihs_get_status(pTwi);
		timeout = 0;
		while( !(status & TWIHS_SR_RXRDY)) {
			status = twihs_get_status(pTwi);
			if (++timeout >= TWITIMEOUTMAX){
				trace_error("TWID Timeout Read\n\r");
				break;
			}
		}
		pData[num-1] = twihs_read_byte(pTwi);
		status = twihs_get_status(pTwi);
		timeout = 0;
		while( !(status & TWIHS_SR_TXCOMP)) {
			status = twihs_get_status(pTwi);
			if ((++timeout >= TWITIMEOUTMAX)) {
				trace_error("TWID Timeout Read\n\r");
				break;
			}
		}
		xdmad_stop_transfer( dmaReadChannel );
		xdmad_free_channel( dmaWriteChannel);
	}
	return 0;
}

/**
 * \brief Asynchronously sends data to a slave on the TWI bus. An optional 
 * callback function is invoked whenever the transfer is complete.
 * \param pTwid  Pointer to a Twid instance.
 * \param address  TWI slave address.
 * \param iaddress  Optional slave internal address.
 * \param isize  Number of internal address bytes.
 * \param pData  Data buffer for storing received bytes.
 * \param num  Data buffer to send.
 * \param pAsync  Asynchronous transfer descriptor.
 * \param TWI_ID  TWIHS ID for TWIHS0, TWIHS1, TWIHS2.
 * \return 0 if the transfer has been started; otherwise returns a TWI error code.
 */
uint8_t twihsd_dma_write(
		Twihsd *pTwid,
		uint8_t address,
		uint32_t iaddress,
		uint8_t isize,
		uint8_t *pData,
		uint32_t num,
		Async *pAsync ,
		uint8_t twi_id)
{
	Twihs *pTwi = pTwid->pTwi;
	AsyncTwi *pTransfer = (AsyncTwi *) pTwid->pTransfer;
	uint32_t status, timeout;
	//uint8_t singleTransfer = 0;
	
	assert( pTwi != NULL ) ;
	assert( (address & 0x80) == 0 ) ;
	assert( (iaddress & 0xFF000000) == 0 ) ;
	assert( isize < 4 ) ;

	//    if(num == 1) singleTransfer = 1;
	/* Check that no transfer is already pending */
	if (pTransfer) {

		trace_error("TWI_Write: A transfer is already pending\n\r");
		return TWID_ERROR_BUSY;
	}

	/* Asynchronous transfer */
	if (pAsync) {

		/* Update the transfer descriptor */
		pTwid->pTransfer = pAsync;
		pTransfer = (AsyncTwi *) pAsync;
		pTransfer->status = ASYNC_STATUS_PENDING;
		pTransfer->pData = pData;
		pTransfer->num = num;
		pTransfer->transferred = 1;

		/* Enable write interrupt and start the transfer */
		twihs_start_write(pTwi, address, iaddress, isize, *pData);
		twihs_enable_it(pTwi, TWIHS_IER_TXRDY);
	} else {
	/* Synchronous transfer*/
		twihsd_dma_initialize_write(twi_id);
		twihsd_dma_configure_write( pData, (num - 1) ,twi_id );
		/* Set slave address and number of internal address bytes. */
		pTwi->TWIHS_MMR = 0;
		pTwi->TWIHS_MMR = (isize << 8) | (address << 16);

		/* Set internal address bytes. */
		pTwi->TWIHS_IADR = 0;
		pTwi->TWIHS_IADR = iaddress;
		
		// cache maintenance before starting DMA Xfr 

		xdmad_start_transfer( dmaWriteChannel );
		timeout = 0;
		while( (xdmad_is_transfer_done( dmaWriteChannel)) ) {
			if ((++timeout >= TWITIMEOUTMAX)) {
				trace_error("TWID DMA not done \n\r" );
						
				break;
			}
		}
		status = twihs_get_status(pTwi);
		timeout = 0;
		
		while( !(status & TWIHS_SR_TXRDY)) {
			status = twihs_get_status(pTwi);
			if ((++timeout >= TWITIMEOUTMAX)) {
				trace_error("TWID Timeout TXRDY\n\r");
				break;
			}
		}
		/* Send a STOP condition */
		twihs_stop(pTwi);

		twihs_write_byte(pTwi, pData[num-1]);
		status = twihs_get_status(pTwi);
		timeout = 0;
		
		while( !(status & TWIHS_SR_TXCOMP)) {
			status = twihs_get_status(pTwi);
			if ((++timeout >= TWITIMEOUTMAX)) {
				trace_error("TWID Timeout Write\n\r");
				break;
			}
		}
		xdmad_stop_transfer(dmaWriteChannel );
		xdmad_free_channel( dmaWriteChannel);
		
	} 
	return 0;
}
