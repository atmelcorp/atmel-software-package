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


/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"

#ifdef CONFIG_HAVE_FLEXCOM
#include "peripherals/flexcom.h"
#endif
#include "gpio/pio.h"
#include "peripherals/pmc.h"
#include "serial/usart.h"
#include "serial/usart_lin.h"

#include "lin.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** LIN Version Supported LIN_13 or LIN_20 */
#define USART_LIN_VERSION LIN_2x

/** LIN node number */
#define LIN_NODE_NUM 2

/** LIN buffer size */
#define LIN_BUFF_SIZE 64

/** LIN frame node number */
#define NUMBER_OF_LIN_FRAMES_NODE 8

/** The frame identifier used to carry diagnostic data */
#define USART_LIN_DIAGNOSTIC_FRAME_ID 60

/** LIN error offset */
#define USART_LIN_ERROR_OFFSET 25

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/* Array of structure of type:'st_lin_message' */
struct _lin_message lin_msg_list_node[LIN_NODE_NUM][NUMBER_OF_LIN_FRAMES_NODE];

/* Error counter */
uint16_t lin_error_number_node[LIN_NODE_NUM] = { 0 };

/* OK rx frame counter */
uint16_t lin_rx_frame_counter[LIN_NODE_NUM] = { 0 };

/* Last error[node_num][n]: lin_handle | status - length = 4 */
uint16_t lin_last_errors_node[LIN_NODE_NUM][LIN_LAST_ERR_LENGTH];

/* Tx Buffer message */
uint8_t lin_tx_buffer_node[LIN_NODE_NUM][LIN_BUFF_SIZE];

/* Rx Buffer message */
uint8_t lin_rx_buffer_node[LIN_NODE_NUM][LIN_BUFF_SIZE];

/**  Instance of the USART IP used */
Usart *usart_lin_node[LIN_NODE_NUM];

/** PDC data packet. */
struct _transfer_packet transfer_packet[LIN_NODE_NUM];

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief  This function commands the sending of a LIN header and response,
 * MASTER task only.
 *
 * \param node Node Value.
 * \param handle  Handle on the descriptor list.
 * \param len     Message length corresponding to the message pointed by the
 * handle in the descriptor list.
 *
 * \return Status PASS / FAIL.
 *
 */
static void _lin_tx_header_and_data(Usart *usart, uint8_t node, uint8_t handle, uint8_t len)
{
	lin_tx_buffer_node[node][0] = lin_msg_list_node[node][handle].id;

	/* Write IDCHR in FLEX_US_LINIR to send the header */
	usart_lin_set_tx_identifier(usart, lin_tx_buffer_node[node][0]);

	if(len) {
		memcpy(&lin_tx_buffer_node[node][1], lin_msg_list_node[node][handle].pdata, len);
	}
	usart_lin_write_stream(usart, &lin_tx_buffer_node[node][1], len);
}

/**
 * \brief  This function commands the sending of a LIN response, SLAVE task of
 * MASTER or SLAVE node.
 *
 * \param node Node Value.
 * \param p_data    Pointer on the data corresponding to the message pointed by
 * the handle in the descriptor list.
 * \param len     Message length corresponding to the message pointed by the
 * handle in the descriptor list.
 *
 * \return Status PASS / FAIL.
 *
 */
static uint8_t _lin_tx_frame(Usart *usart, uint8_t node, uint8_t *pdata, uint8_t len)
{
//	usart_lin_write_stream(usart, &lin_tx_buffer_node[node][0], 1);
	return (uint8_t)usart_lin_write_stream(usart, pdata, len);
}

/**
 * \brief  This function commands the reception of a LIN response, SLAVE task
 * of MASTER or SLAVE node.
 *
 * \param node Node Value.
 * \param handle  Handle on the descriptor list.
 * \param len     Message length corresponding to the message pointed by the
 * handle in the descriptor list.
 *
 * \return Status PASS / FAIL.
 *
 */
static uint8_t _lin_rx_frame(Usart *usart, uint8_t node, uint8_t len)
{
	return (uint8_t)usart_lin_read_stream(usart, &lin_rx_buffer_node[node][0], len);
}

static void _lin_display_info (uint32_t status, uint8_t node, uint8_t handle, uint8_t rx_len)
{
	uint8_t i;
	uint8_t *pdata = lin_msg_list_node[node][handle].pdata;

	printf("\n\r");
	printf(" LIN MESSAGE Node:%02d Handle:%02d RxLen:0x%02x \n\r", node, handle, rx_len);
	printf(" ID message     0x%02x \n\r", lin_msg_list_node[node][handle].id);
	printf(" Length message 0x%02x \n\r",lin_msg_list_node[node][handle].dlc );
	printf(" Command        0x%02x \n\r", lin_msg_list_node[node][handle].lin_cmd);
	printf(" Status         0x%02x \n\r", lin_msg_list_node[node][handle].status);
	printf(" .... Data      ");
	for (i=0; i<rx_len; i++) {
		printf("0x%02X ", pdata[i]);
	}
	printf("\n\r\n\r");

	printf(" LIN STATUS \n\r");
	printf(" [%1d] FRAME   Framing Error \n\r", (status & US_CSR_FRAME) ? 1 : 0);
	printf(" [%1d] PARE    Parity Error \n\r", (status & US_CSR_PARE) ? 1 : 0);
	printf(" [%1d] TIMEOUT Receiver Timeout \n\r", (status & US_CSR_TIMEOUT) ? 1 : 0);
	printf(" [%1d] LINBK   Break Sent or Received \n\r", (status & US_CSR_LINBK) ? 1 : 0);
	printf(" [%1d] LINID   Identifier Sent or Received \n\r", (status & US_CSR_LINID) ? 1 : 0);
	printf(" [%1d] LINTC   Transfer Completed \n\r", (status & US_CSR_LINTC) ? 1 : 0);
	printf(" [%1d] LINBLS  Bus Line Status \n\r", (status & US_CSR_LINBLS) ? 1 : 0);
	printf(" [%1d] LINBE   Bit Error \n\r", (status & US_CSR_LINBE) ? 1 : 0);
	printf(" [%1d] LINISFE Inconsistent Synch Field Error \n\r", (status & US_CSR_LINISFE) ? 1 : 0);
	printf(" [%1d] LINIPE  Identifier Parity Error \n\r", (status & US_CSR_LINIPE) ? 1 : 0);
	printf(" [%1d] LINCE   Checksum Error \n\r", (status & US_CSR_LINCE) ? 1 : 0);
	printf(" [%1d] LINSNRE Slave Not Responding Error \n\r", (status & US_CSR_LINSNRE) ? 1 : 0);
	printf(" [%1d] LINSTE  Synch Tolerance Error \n\r", (status & US_CSR_LINSTE) ? 1 : 0);
	printf(" [%1d] LINHTE  LIN Header Timeout Error \n\r", (status & US_CSR_LINHTE) ? 1 : 0);
	printf("\n\r");
}

static void _display_frame (uint8_t node, uint8_t handle, uint8_t len)
{
	uint8_t *pdata = lin_msg_list_node[node][handle].pdata;
	printf ("Rx Frame ... Node:%d Handle:%d Count:%04d [ ", node, handle, lin_rx_frame_counter[node]);
	while (len--) {
		printf ("0x%02X ", *(pdata++));
	}
	printf ("]\r");
}


/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief  This function initializes the LIN controller.
 *
 * \param usart_node Pointer to the usart instance.
 * \param b_master true for master, false for slave.
 * \param node Node Value.
 * \param rate Baudrate Value.
 *
 * \return Status PASS / FAIL.
 */
uint8_t lin_init(struct _lin_desc* lin_desc, uint8_t node)
{
	uint32_t id = get_usart_id_from_addr(lin_desc->addr);

	usart_lin_node[node] = lin_desc->addr;

	/* Configure ENABLE pin */
	pio_configure(&lin_desc->pin_enable, 1);

	pmc_configure_peripheral(id, NULL, true);

#ifdef CONFIG_HAVE_FLEXCOM
	{
		/* Flexcom mode Usart */
		Flexcom* flexcom = get_flexcom_addr_from_id(id);
		flexcom_select(flexcom, FLEX_MR_OPMODE_USART);
	}
#endif

	/* Configure usart mode */
	usart_configure(lin_desc->addr, lin_desc->mode, lin_desc->baudrate);

#ifdef CONFIG_HAVE_USART_FIFO
	/* Mode fifo */
	usart_fifo_configure(lin_desc->addr, 16, 16, 16);
	usart_fifo_enable(lin_desc->addr);
#endif
	return 0;
}

/**
 * \brief  This function initializes the LIN message descriptor.
 *
 * \param node LIN node id.
 * \param frame_id Frame node id.
 * \param lin_desc Specific LIN descriptor.
 *
 * \return Status PASS / FAIL.
 *
 */
uint8_t lin_register_descriptor(uint8_t node, uint8_t frame_id, struct _lin_message *msg)
{
	lin_msg_list_node[node][frame_id].id = msg->id;
	lin_msg_list_node[node][frame_id].dlc = msg->dlc;
	lin_msg_list_node[node][frame_id].lin_cmd = msg->lin_cmd;
	lin_msg_list_node[node][frame_id].status = msg->status;
	lin_msg_list_node[node][frame_id].pdata = msg->pdata;
	lin_msg_list_node[node][frame_id].pfnct = msg->pfnct;

	return 0;
}


/**
 * \brief USART LIN handler: manage ID reception.
 *
 * \param node Node Value.
 *
 */
void lin_slave_usart_handler(uint8_t node)
{
	uint8_t handle = 0xFF;
	uint8_t i, frame_len;
	Usart *usart = usart_lin_node[node];
	uint32_t lin_status = usart_get_status(usart);

	/* Check ID Value for the current message */
	for (i = 0; i < NUMBER_OF_LIN_FRAMES_NODE; i++) {
		/* Read IDCHR in FLEX_US_RHR */
		/* Check if the ID received is registered into the lin description list */
		if (lin_msg_list_node[node][i].id == usart_lin_read_identifier(usart_lin_node[node])) {
			handle = i;
			break;
		}
	}
	/* Check if error */
	if (handle != 0xFF) {
			/* Start of the associated task */
			if (lin_msg_list_node[node][handle].pfnct != NULL) {
				lin_msg_list_node[node][handle].pfnct(lin_msg_list_node[node][handle].pdata);
			}

		/* Check Error Status */
		usart_reset_status(usart_lin_node[node]);
		/* Check if US_CSR_LINBE | US_CSR_LINISFE | US_CSR_LINIPE | US_CSR_LINCE */
		if (lin_status & US_CSR_LIN_ERROR) {
			lin_msg_list_node[node][handle].status = (lin_status & US_CSR_LIN_ERROR) >> USART_LIN_ERROR_OFFSET;
			lin_last_errors_node[node][(((uint8_t) lin_error_number_node[node]) &(LIN_LAST_ERR_LENGTH - 1))] \
				= ((((uint16_t)handle) <<8) | (lin_status & US_CSR_LIN_ERROR) >> USART_LIN_ERROR_OFFSET);
			lin_error_number_node[node]++;
			_lin_display_info (lin_status, node, handle, usart_fifo_get_rx_size(usart));
		}
		/* Here the communication go on only in case no error is detected!!! */
		else {

			/* If the NACT configuration for this frame is PUBLISH,
			 * FLEX_US_LINMR must be written with NACT = PUBLISH even if this
			 * field is already correctly configured, in order to set the TXREADY
			 * flag and the corresponding write transfer request. */
			usart_lin_set_node_action(usart_lin_node[node], lin_msg_list_node[node][handle].lin_cmd);
			/* Configure Parity */
			usart_lin_enable_parity(usart);
			/* Configure Checksum */
			usart_lin_enable_checksum(usart);
			/* Configure Checksum Type */
			usart_lin_set_checksum_type(usart, USART_LIN_ENHANCED_CHECKSUM);
			/* Configure Frameslot */
			usart_lin_enable_frame_slot(usart);
			/* Configure Frame Length */
			//usart_lin_set_data_len_mode(usart, USART_LIN_DLM_IDCHR);
			//usart_lin_set_response_data_len(usart, lin_msg_list_node[node][handle].dlc);
			usart_lin_set_data_len_mode(usart, USART_LIN_DLM_DLC);
			usart_lin_set_frame_data_len(usart, lin_msg_list_node[node][handle].dlc);

			/* Diagnostic frames in LIN 2.0/2.1 */
			if ((usart_lin_read_identifier(usart) >= USART_LIN_DIAGNOSTIC_FRAME_ID)) {
				usart_lin_set_checksum_type( usart, USART_LIN_CLASSIC_CHECKSUM);
				/* Configure Frame Length */
				usart_lin_set_data_len_mode( usart, USART_LIN_DLM_DLC);
			}

			switch (lin_msg_list_node[node][handle].lin_cmd) {
			case PUBLISH:
				_lin_tx_frame(usart, node, lin_msg_list_node[node][handle].pdata, lin_msg_list_node[node][handle].dlc);
				break;

			case SUBSCRIBE:
				frame_len = _lin_rx_frame(usart, node, lin_msg_list_node[node][handle].dlc);
				if (frame_len) {
					lin_rx_frame_counter[node]++;
					memcpy(lin_msg_list_node[node][handle].pdata,  &lin_rx_buffer_node[node][0], frame_len);
					_display_frame (node, handle, frame_len);
				}
				break;

			case IGNORE:
			default:
				break;
			}
		}
	}
	usart_lin_reset_status_bits(usart);
}

/**
 * \brief  This function commands the sending of the LIN header, MASTER task of
 * MASTER node.
 *
 * \param node Node Value.
 * \param id  LIN identifier value. In case of `LIN_1X', the coded length is
 * transported into the LIN identifier.
 * \param len True length (not coded), number of data bytes transported in
 * the response.
 *
 * \return Status PASS / FAIL.
 *
 */
uint8_t lin_send_cmd(uint8_t node, uint8_t id, uint8_t len)
{
	uint8_t i;
	uint8_t handle = 0;
	Usart *usart = usart_lin_node[node];

	/* Clear error in case of previous communication */
	usart_reset_status(usart);

	for (i = 0; i < NUMBER_OF_LIN_FRAMES_NODE; i++) {
		if (lin_msg_list_node[node][i].id == id) {
			handle = i;
			break;
		}
	}

	if (handle != 0xFF) {
		/* action: 0 for PUBLISH, 1 for SUBSCRIBE, 2 for IGNORE */
		usart_lin_set_node_action(usart, lin_msg_list_node[node][handle].lin_cmd);
		/* Configure Parity */
		usart_lin_enable_parity(usart);
		/* Configure Checksum */
		usart_lin_enable_checksum(usart);
		/* Configure Checksum Type */
		usart_lin_set_checksum_type(usart, USART_LIN_ENHANCED_CHECKSUM);
		/* Configure Frameslot */
		usart_lin_enable_frame_slot(usart);
		/* Configure Frame Length */
		usart_lin_set_data_len_mode(usart, USART_LIN_DLM_DLC);
		usart_lin_set_frame_data_len(usart, len);

		/* Switch to Classic Checksum if diagnostic ID request */
		if (lin_msg_list_node[node][handle].id >= USART_LIN_DIAGNOSTIC_FRAME_ID) {
			usart_lin_set_checksum_type(usart, USART_LIN_CLASSIC_CHECKSUM);
			/* Configure Frame Length */
			usart_lin_set_data_len_mode(usart, USART_LIN_DLM_IDCHR);
		}

		switch (lin_msg_list_node[node][handle].lin_cmd) {

		/* Master in PUBLISH and Slave in SUBSCRIBE
		 * -> Data transfer from the master to the all slaves in SUBSCRIBE */
		case PUBLISH:
			_lin_tx_header_and_data(usart, node, handle, len);
			break;

		/* Master in SUBSCRIBE and Slave in PUBLISH
		 * -> Data transfer from the slave to the master */
		case SUBSCRIBE:
			_lin_tx_header_and_data(usart, node, handle, 0);
			break;

		default:
			break;
		}
		return 0;
	} else {
		return 1;
	}
}

void lin_master_usart_handler(uint8_t node)
{
	uint8_t handle = 0xFF;
	uint8_t i, rx_len;
	Usart *usart = usart_lin_node[node];
	uint32_t lin_status = usart_get_status(usart);

	/* Check ID Value for the current message */
	for (i = 0; i < NUMBER_OF_LIN_FRAMES_NODE; i++) {
		/* Read IDCHR in FLEX_US_RHR */
		/* Check if the ID received is registered into the lin description list */
		if (lin_msg_list_node[node][i].id == usart_lin_read_identifier(usart_lin_node[node])) {
			handle = i;
			break;
		}
	}

	/* Check if a LIN error occured */
	if (lin_status & US_CSR_LIN_ERROR) {
		lin_msg_list_node[node][handle].status = (lin_status & US_CSR_LIN_ERROR) >> USART_LIN_ERROR_OFFSET;
		lin_last_errors_node[node][(((uint8_t) lin_error_number_node[node]) &(LIN_LAST_ERR_LENGTH - 1))] \
			= ((((uint16_t)handle) <<8) | (lin_status & US_CSR_LIN_ERROR) >> USART_LIN_ERROR_OFFSET);
		lin_error_number_node[node]++;
		_lin_display_info (lin_status, node, handle, usart_fifo_get_rx_size(usart));
	}
	/* Here the communication go on only in case no error is detected */
	else {
		rx_len = usart_fifo_get_rx_size(usart);
		rx_len = _lin_rx_frame(usart, node, rx_len);
		if (rx_len) {
			lin_rx_frame_counter[node]++;
			memcpy(lin_msg_list_node[node][handle].pdata,  &lin_rx_buffer_node[node][0], rx_len);
			_display_frame (node, handle, rx_len);
		}
	}
	usart_lin_reset_status_bits(usart);
}
