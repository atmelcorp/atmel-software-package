QSPI_FLASH EXAMPLE
============

# Objectives
------------
This example aims to test SPI-NOR memories.


# Example Description
---------------------
This example demonstrates how to using QSPI flash.


# Test
------
## Supported targets
--------------------
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK

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

* Start the application
-----------------------

* In the terminal window, the following text should appear (values depend on the
 board and chip used):
```
 -- QSPI exmaple xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
```

Tested with IAR and GCC (sram and ddram configurations)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Run this example | Print ... `configure returns true` ... `erase returns true` ... `read returns true` ... `write returns true` ... `read returns true` ... on screen | PASSED | PASSED
