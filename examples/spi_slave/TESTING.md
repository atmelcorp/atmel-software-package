SPI_SLAVE EXAMPLE
============

# Objectives
------------
This example aims to test SPI slave mode.


# Example Description
---------------------
This example demonstrates control of the SPI slave, how to configure and
transfer data with SPI slave. By default, example runs in SPI slave mode,
waiting for SPI slave & DBGU input.


# Test
------
## Supported targets
--------------------
* SAM9XX5-EK
* SAM9X60-EK
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
* SAMA5D3-EK
* SAMA5D4-EK
* SAMA5D4-XPLAINED

## Setup
--------
Step needed to set up the example.

* Build the program and download it inside the evaluation board.
* On the computer, open and configure a terminal application (e.g. HyperTerminal
 on Microsoft Windows) with these settings:
	- 115200 bauds
	- 8 bits of data
	- No parity
	- 1 stop bit
	- No flow control
* Start the application (SAMA5D2-XPLAINED,SAMA5D3-XPLAINED,SAMA5D3-EK,SAMA5D4-XPLAINED,SAMA5D4-EK)
* In the terminal window, the following text should appear (values depend on the
 board and chip used):
```
 -- SPI Slave Example xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
 Menu :
 ------
   0: Set SPCK =     500 kHz
   1: Set SPCK =    1000 kHz
   2: Set SPCK =    5000 kHz
   s: Perform SPI transfer start
   h: Display menu
```

## Start the application
------------------------

### Connection
connect the SPI pins on the board before running the example.

__Connection for SAMA5D2 Xplained Ultra:__

MASTER (SPI0 IOSET1)              | SLAVE (SPI1 IOSET3)
--------------------------------- | ---------------------------------------
SPI0_MOSI (EXP_PA15 on J17 pin 5) | SPI1_MOSI  (EXP/XPRO_PD26 on J20 pin 4)
SPI0_MISO (EXP_PA16 on J8 pin 1)  | SPI1_MISO  (EXP/XPRO_PD27 on J20 pin 5)
SPI0_SPCK (EXP_PA14 on J17 pin 4) | SPI1_SPCK  (EXP/XPRO_PD25 on J20 pin 6)
SPI0_NPCS2 (EXP_PA19 on J9 pin 1) | SPI1_NPCS0 (EXP/XPRO_PD28 on J20 pin 3)

__Connection for SAMA5D27_SOM1_EK:__

MASTER (FLEXSPI4 IOSET1)          | SLAVE (FLEXSPI3 IOSET2)
--------------------------------- | ---------------------------------------
FLEXSPI4_MOSI (PC28 on J24 pin 6) | SPI1_MOSI  (PC20 on J20 pin 4)
FLEXSPI4_MISO (PC29 on J24 pin 5) | SPI1_MISO  (PC19 on J20 pin 2)
FLEXSPI4_SPCK (PC30 on J24 pin 4) | SPI1_SPCK  (PC18 on J23 pin 1)
FLEXSPI4_NPCS2 (PD0 on J24 pin 3) | SPI1_NPCS0 (PC21 on J20 pin 6)

__Connection for SAMA5D3 EK:__

MASTER (SPI0)                  | SLAVE (SPI1)
------------------------------ | ------------------------------
SPI0_MISO  (PD10 on J3 pin 22) | SPI1_MISO (PC22 on J2 pin 18)
SPI0_MOSI  (PD11 on J3 pin 24) | SPI1_MOSI (PC23 on J2 pin 20)
SPI0_SPCK  (PD12 on J3 pin 26) | SPI1_SPCK (PC24 on J2 pin 22)
SPI0_NPCS2 (PD15 on J3 pin 32) | SPI1_NPCS0 (PC25 on J2 pin 24)

`Also remember to mount the following resistors: R6, R50, and R51.`

__Connection for SAMA5D4 EK:__

MASTER (SPI1)                           | SLAVE (SPI2)
--------------------------------------- | -----------------------------------------
SPI1_MOSI (LCD_SPI1_SI on J10 pin 32)   | SPI2_MOSI (XPRO_PD13 on J11 XPRO pin 16)
SPI1_MISO (LCD_SPI1_SO on J10 pin 31)   | SPI2_MISO (XPRO_PD11 on J11 XPRO pin 17)
SPI1_SPCK (LCD_SPI1_CLK on J10 pin 33)  | SPI2_SPCK (XPRO_PD15 on J11 XPRO pin 18)
SPI1_NPCS2 (LCD_SPI1_CS2 on J10 pin 34) | SPI2_NPCS0 (XPRO_PD17 on J11 XPRO pin 14)

__Connection for SAMA5D4 Xplained Ultra:__

MASTER (SPI1)                           | SLAVE (SPI2)
--------------------------------------- | ---------------------------------------
SPI1_MOSI (EXP/XPRO_PB19 on J17 pin 4)  | SPI2_MOSI (EXP/XPRO_PD13 on J19 pin 5)
SPI1_MISO (EXP/XPRO_PB18 on J17 pin 5)  | SPI2_MISO (EXP/XPRO_PD11 on J15 pin 30)
SPI1_SPCK (EXP/XPRO_PB20 on J17 pin 6)  | SPI2_SPCK (EXP/XPRO_PD15 on J15 pin 8)
SPI1_NPCS3(EXP/XPRO_PB27 on J15 pin 4)  | SPI2_NPCS0(EXP/XPRO_PD17 on J19 pin 3)

__Connection for SAM9XX5 EK:__

MASTER (SPI0)                 | SLAVE (SPI1)
----------------------------- | ------------------------------
SPI0_MISO (PA11 on J1 pin 27) | SPI1_MISO (PA21 on J1 pin 16)
SPI0_MOSI (PA12 on J1 pin 29) | SPI1_MOSI (PA22 on J1 pin 18)
SPI0_SPCK (PA13 on J1 pin 31) | SPI1_SPCK (PA23 on J1 pin 20)
SPI0_NPCS1 (PA7 on J1 pin 19) | SPI1_NPCS0 (PA8 on J1 pin 21) 

__Connection for SAM9X60 EK:__

MASTER (SPI0)                  | SLAVE (SPI1)
------------------------------ | ------------------------------
SPI0_MISO (PA11 on J15 pin 5)  | SPI1_MISO (PA01 on J15 pin 12)
SPI0_MOSI (PA12 on J15 pin 6)  | SPI1_MOSI (PA00 on J15 pin 11)
SPI0_SPCK (PA13 on J15 pin 4)  | SPI1_SPCK (PA04 on J17 pin 15)
SPI0_NPCS0 (PA14 on J15 pin 3) | SPI1_NPCS1 (PA03 on J17 pin 13)

Tested with IAR and GCC (sram and ddram configurations)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'h' | Print the menu on screen | PASSED | PASSED
Press '0' | Print `Next SPI master transfer will use 500kHz clock.` on screen | PASSED | PASSED
Press 's' | Print `Slave sending, Master receiving...` ... `Received data matched.` on screen | PASSED | PASSED
Press '1' | Print `Next SPI master transfer will use 1000kHz clock.` on screen | PASSED | PASSED
Press 's' | Print `Slave sending, Master receiving...` ... `Received data matched.` on screen | PASSED | PASSED
Press '2' | Print `Next SPI master transfer will use 5000kHz clock.` on screen | PASSED | PASSED
Press 's' | Print `Slave sending, Master receiving...` ... `Received data matched.` on screen | PASSED | PASSED
