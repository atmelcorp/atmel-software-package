#ifndef __CONFIG_SAMA5D27_SOM1_EK_H__
#define __CONFIG_SAMA5D27_SOM1_EK_H__

/** define the SPI master bus */
#define SPI_MASTER_BUS BUS(BUS_TYPE_SPI, 0)
/** define the CS signal of SPI master */
#define SPI_MASTER_CS 1
/** define the bitrate of SPI master */
#define SPI_MASTER_BITRATE 1000
/** define the pins of SPI master */
#define SPI_MASTER_PINS PINS_FLEXCOM4_SPI_NPCS1_IOS1

/** define the address of SPI slave */
#define SPI_SLAVE_ADDR FLEXSPI3
/** define the pins of SPI slave */
#define SPI_SLAVE_PINS PINS_FLEXCOM3_SPI_NPCS0_IOS2

#endif
