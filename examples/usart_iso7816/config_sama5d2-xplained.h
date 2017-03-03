#ifndef __CONFIG_SAMA5D2_XPLAINED_H__
#define __CONFIG_SAMA5D2_XPLAINED_H__

/* =================== definition for example "usart_iso7816" =================== */

/** NCN4555MN usart pin definition */
/* IO TXD bidirectionnal */
/* SCK	*/
#define PIN_COM2_ISO7816  PINS_FLEXCOM0_USART_ISO7816_IOS1

/** NCN4555MN STOP pin definition */
/* Connected to CTS */
#define PIN_STOP_ISO7816 { PIO_GROUP_B, PIO_PB31C_FLEXCOM0_IO3, PIO_OUTPUT_1, PIO_PULLUP }

/** NCN4555MN MOD VCC pin definition */
/* Connected to RXD */
#define PIN_MODE_VCC_ISO7816 { PIO_GROUP_B, PIO_PB29C_FLEXCOM0_IO1, PIO_OUTPUT_1, PIO_PULLUP }

/** NCN4555MN RST pin definition */
/* Connected to RTS */
#define PIN_RST_ISO7816 { PIO_GROUP_C, PIO_PC0C_FLEXCOM0_IO4, PIO_OUTPUT_0, PIO_DEFAULT }

#define ID_USART ID_FLEXCOM0

#define USART_ADDR FLEXUSART0

#endif
