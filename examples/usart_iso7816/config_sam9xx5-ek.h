#ifndef __CONFIG_SAM9XX5_EK_H__
#define __CONFIG_SAM9XX5_EK_H__

/* =================== definition for example "usart_iso7816" =================== */

/* IO TXD bidirectionnal */
/* SCK	*/
#define PIN_COM2_ISO7816  PINS_USART0_ISO7816

/** NCN4555MN STOP pin definition */
/* Connected to CTS */
#define PIN_STOP_ISO7816  { PIO_GROUP_A, PIO_PA3A_CTS0, PIO_OUTPUT_1, PIO_PULLUP }

/** NCN4555MN MOD VCC pin definition */
/* Connected to RXD */
#define PIN_MODE_VCC_ISO7816 { PIO_GROUP_A, PIO_PA1A_RXD0, PIO_OUTPUT_1, PIO_PULLUP }

/** NCN4555MN RST pin definition */
/* Connected to RTS */
#define PIN_RST_ISO7816 { PIO_GROUP_A, PIO_PA2A_RTS0, PIO_OUTPUT_0, PIO_DEFAULT }

#define ID_USART ID_USART0

#define USART_ADDR USART0

#endif
