#ifndef __CONFIG_SAMA5D3_XPLAINED_H__
#define __CONFIG_SAMA5D3_XPLAINED_H__

/* =================== definition for example "usart_iso7816" =================== */

/* IO TXD bidirectionnal */
/* SCK	*/
#define PIN_COM2_ISO7816  PINS_USART2_ISO7816

/** NCN4555MN STOP pin definition */
/* Connected to CTS */
#define PIN_STOP_ISO7816  { PIO_GROUP_E, PIO_PE23B_CTS2, PIO_OUTPUT_1, PIO_PULLUP }

/** NCN4555MN MOD VCC pin definition */
/* Connected to RXD */
#define PIN_MODE_VCC_ISO7816 { PIO_GROUP_E, PIO_PE25B_RXD2, PIO_OUTPUT_1, PIO_PULLUP }

/** NCN4555MN RST pin definition */
/* Connected to RTS */
#define PIN_RST_ISO7816 { PIO_GROUP_E, PIO_PE24B_RTS2, PIO_OUTPUT_0, PIO_DEFAULT }

#define ID_USART ID_USART2

#define USART_ADDR USART2

#endif
