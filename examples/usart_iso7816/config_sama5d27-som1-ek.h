#ifndef __CONFIG_SAMA5D27_SOM1_EK_H__
#define __CONFIG_SAMA5D27_SOM1_EK_H__

/* =================== definition for example "usart_iso7816" =================== */

/** NCN4555MN usart pin definition */
/* IO TXD bidirectionnal */
/* SCK	*/
#define PIN_COM2_ISO7816  PINS_FLEXCOM3_USART_ISO7816_IOS2

/** NCN4555MN STOP pin definition */
/* Connected to CTS */
#define PIN_STOP_ISO7816 { PIO_GROUP_C, PIO_PC21E_FLEXCOM3_IO3, PIO_OUTPUT_1, PIO_PULLUP }

/** NCN4555MN MOD VCC pin definition */
/* Connected to RXD */
#define PIN_MODE_VCC_ISO7816 { PIO_GROUP_C, PIO_PC19E_FLEXCOM3_IO1, PIO_OUTPUT_1, PIO_PULLUP }

/** NCN4555MN RST pin definition */
/* Connected to RTS */
#define PIN_RST_ISO7816 { PIO_GROUP_C, PIO_PC22E_FLEXCOM3_IO4, PIO_OUTPUT_0, PIO_DEFAULT }

#define ID_USART ID_FLEXCOM3

#define USART_ADDR FLEXUSART3

#endif
