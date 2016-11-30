/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"

#include "gpio/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/qspi.h"
#include "crypto/trng.h"

#include "memories/qspiflash.h"
#include "misc/cache.h"
#include "misc/console.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

CACHE_ALIGNED static uint8_t buf[768];

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

static struct _pin pins_qspi[] = QSPIFLASH_PINS;

int main(void)
{
	/* Initialize TRNG */
	trng_enable();

	/* Output example information */
	console_example_info("QSPI Example");

	pio_configure(pins_qspi, ARRAY_SIZE(pins_qspi));

	qspi_initialize(QSPIFLASH_ADDR);
	uint32_t baudrate = qspi_set_baudrate(QSPIFLASH_ADDR, QSPIFLASH_BAUDRATE);
	printf("set baudrate to %u\r\n", (unsigned)baudrate);

	struct _qspiflash flash;
	int rc = qspiflash_configure(&flash, QSPIFLASH_ADDR);
	printf("configure returns %d\r\n", rc);

	uint32_t start = 0x280000;

	printf("erasing block at 0x%08x\r\n", (int)start);
	rc = qspiflash_erase_block(&flash, start, 64 * 1024);
	printf("erase returns %d\r\n", rc);

	printf("reading %d bytes at 0x%08x\r\n", sizeof(buf), (int)start);
	memset(buf, 0, sizeof(buf));
	rc = qspiflash_read(&flash, start, buf, sizeof(buf));
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
	rc = qspiflash_write(&flash, start, buf, sizeof(buf));
	printf("write returns %d\r\n", rc);

	printf("reading %d bytes at 0x%08x\r\n", sizeof(buf), (int)start);
	memset(buf, 0, sizeof(buf));
	rc = qspiflash_read(&flash, start, buf, sizeof(buf));
	printf("read returns %d\r\n", rc);
	_display_buf(buf, sizeof(buf));

	while (1) { }
}
