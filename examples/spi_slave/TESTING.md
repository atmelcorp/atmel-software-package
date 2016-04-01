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

## Setup
--------
Step needed to set up the example.

* Build the program and download it inside the evaluation board.
* On the computer, open and configure a terminal application (e.g. HyperTerminal
 on Microsoft Windows) with these settings:
	- 57600 bauds (for sama5d2-xplained)
	- 115200 bauds (for sama5d4-xplained)
	- 8 bits of data
	- No parity
	- 1 stop bit
	- No flow control
* Start the application.
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
### Connection
connect the SPI pins on the board before running the example.

__Connection for SAMA5D2 Xplained Ultra:__
SPI0 IOSET1 (MASTER) | SPI1 IOSET3 (SLAVE)
------------ | -------------
SPI0_NPCS2 (EXP_PA19 on J9 pin 1) | SPI1_NPCS0 (EXP/XPRO_PD28 on J20 pin 3)
SPI0_MOSI  (EXP_PA15 on J17 pin 5) | SPI1_MOSI  (EXP/XPRO_PD26 on J20 pin 4)
SPI0_MISO  (EXP_PA16 on J8 pin 1) | SPI1_MISO  (EXP/XPRO_PD27 on J20 pin 5)
SPI0_SPCK  (EXP_PA14 on J17 pin 4) | SPI1_SPCK  (EXP/XPRO_PD25 on J20 pin 6)

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


# Log
------

## Current version
--------
 - v1.3

## History
--------
