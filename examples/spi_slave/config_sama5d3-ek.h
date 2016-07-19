#ifndef __CONFIG_SAMA5D3_EK_H__
#define __CONFIG_SAMA5D3_EK_H__

/** define the address of SPI master */
#define SPI_MASTER_ADDR SPI1
/** define the CS signal of SPI master */
#define SPI_MASTER_CS 0
/** define the pins of SPI master */
#define SPI_MASTER_PINS PINS_SPI1_NPCS0

/** define the address of SPI slave */
#define SPI_SLAVE_ADDR SPI0
/** define the CS signal of SPI slave */
#define SPI_SLAVE_CS 0
/** define the pins of SPI slave */
#define SPI_SLAVE_PINS PINS_SPI0_NPCS0

#endif
