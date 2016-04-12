#ifndef __CONFIG_SAMA5D4_EK_H__
#define __CONFIG_SAMA5D4_EK_H__

/* =================== definition for example "usart_iso7816" =================== */
/* IO TXD bidirectionnal */
/* SCK	*/
#define PIN_COM2_ISO7816  {PIN_USART1_TXD, PIN_USART1_SCK}

/** NCN4555MN STOP pin definition */
/* Connected to CTS */
#define PIN_STOP_ISO7816  { PIO_GROUP_D, PIO_PD14A_CTS1, PIO_OUTPUT_1, PIO_PULLUP }

/** NCN4555MN MOD VCC pin definition */
/* Connected to RXD */
#define PIN_MODE_VCC_ISO7816 { PIO_GROUP_D, PIO_PD16A_RXD1, PIO_OUTPUT_1, PIO_PULLUP }

/** NCN4555MN RST pin definition */
/* Connected to RTS */
#define PIN_RST_ISO7816 { PIO_GROUP_D, PIO_PD15A_RTS1, PIO_OUTPUT_0, PIO_DEFAULT }

#define ID_USART ID_USART1

#define USART_ADDR USART1

#endif
