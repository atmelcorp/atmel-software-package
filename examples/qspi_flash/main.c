/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "board.h"
#include "board_spi.h"
#include "chip.h"
#include "compiler.h"
#include "crypto/trng.h"
#include "gpio/pio.h"
#include "mm/cache.h"
#include "nvm/spi-nor/spi-nor.h"
#include "peripherals/pmc.h"
#include "serial/console.h"
#include "spi/qspi.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

CACHE_ALIGNED static uint8_t buf[768];

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static void _display_buf(uint8_t *buffer, uint32_t size)
{
	int i;
	for (i = 0; i < size; i++) {
		printf("%02x ", buffer[i]);
		if ((i & 31) == 31)
			printf("\r\n");
		else if ((i & 3) == 3)
			printf(" ");
	}
	printf("\r\n");
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

#define BOARD_SPI_FLASH_QSPI0 0

int main(void)
{
	uint32_t start = 0x280000;
	struct spi_flash* flash = board_get_spi_flash(BOARD_SPI_FLASH_QSPI0);
	int rc;

	/* Initialize TRNG */
	trng_enable();

	/* Output example information */
	console_example_info("QSPI Example");

	printf("erasing block at 0x%08x\r\n", (int)start);
	rc = spi_nor_erase(flash, start, 4 * 1024);
	printf("erase returns %d\r\n", rc);

	printf("reading %d bytes at 0x%08x\r\n", sizeof(buf), (int)start);
	memset(buf, 0, sizeof(buf));
	rc = spi_nor_read(flash, start, buf, sizeof(buf));
	printf("read returns %d\r\n", rc);
	_display_buf(buf, sizeof(buf));

	printf("preparing write buffer\r\n");
	uint8_t r = trng_get_random_data() & 0xff;
	uint32_t i = 0;
	while (i * 32 < sizeof(buf)) {
		memset(buf + i * 32, r + i, 32);
		i++;
	}
	_display_buf(buf, sizeof(buf));

	printf("writing %d bytes at 0x%08x\r\n", sizeof(buf), (int)start);
	rc = spi_nor_write(flash, start, buf, sizeof(buf));
	printf("write returns %d\r\n", rc);

	printf("reading %d bytes at 0x%08x\r\n", sizeof(buf), (int)start);
	memset(buf, 0, sizeof(buf));
	rc = spi_nor_read(flash, start, buf, sizeof(buf));
	printf("read returns %d\r\n", rc);
	_display_buf(buf, sizeof(buf));

	while (1) { }
}
