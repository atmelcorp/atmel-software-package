/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"

#include "peripherals/aic.h"
#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/qspi.h"
#include "peripherals/trng.h"
#include "peripherals/wdt.h"

#include "memories/qspiflash.h"
#include "misc/console.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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
	/* Disable watchdog */
	wdt_disable();

	/* Disable all PIO interrupts */
	pio_reset_all_it();

	/* Configure console */
	board_cfg_console();

	/* Initialize TRNG */
	trng_enable();

	/* Output example information */
	printf("-- QSPI test %s --\n\r", SOFTPACK_VERSION);
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	pio_configure(pins_qspi, ARRAY_SIZE(pins_qspi));

	qspi_initialize(QSPIFLASH_ADDR);
	uint32_t baudrate = qspi_set_baudrate(QSPIFLASH_ADDR, QSPIFLASH_BAUDRATE);
	printf("set baudrate to %u\r\n", (unsigned)baudrate);

	struct _qspiflash flash;
	bool rc = qspiflash_configure(&flash, QSPIFLASH_ADDR);
	printf("configure returns %s\r\n", rc ? "true" : "false");

	uint32_t start = 0x280000;

	uint8_t buf[768];

	printf("erasing block at 0x%08x\r\n", (int)start);
	rc = qspiflash_erase_block(&flash, start, 64 * 1024);
	printf("erase returns %s\r\n", rc ? "true" : "false");

	printf("reading %d bytes at 0x%08x\r\n", sizeof(buf), (int)start);
	memset(buf, 0, sizeof(buf));
	rc = qspiflash_read(&flash, start, buf, sizeof(buf));
	printf("read returns %s\r\n", rc ? "true" : "false");
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
	printf("write returns %s\r\n", rc ? "true" : "false");

	printf("reading %d bytes at 0x%08x\r\n", sizeof(buf), (int)start);
	memset(buf, 0, sizeof(buf));
	rc = qspiflash_read(&flash, start, buf, sizeof(buf));
	printf("read returns %s\r\n", rc ? "true" : "false");
	_display_buf(buf, sizeof(buf));

	while (1) { }
}
