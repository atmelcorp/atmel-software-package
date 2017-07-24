DDRAM EXAMPLE
============

# Objectives
------------
This example aims to access DDRAM with Multi-port DDR-SDRAM Controller (MPDDRC)
peripheral.

# Example Description
---------------------
This basic application shows how to initialize and perform read and write a
DDRAM memory

# Test
------
## Supported targets
--------------------
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
* SAMA5D2-PTC-EK
* SAMA5D3-EK
* SAMA5D3-XPLAINED
* SAMA5D4-EK
* SAMA5D4-XPLAINED
* SAME70-XPLAINED
* SAMV71-XPLAINED

## Setup
--------
On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:
 - 115200 bauds
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control

## Start the application
------------------------

In order to test this example, the process is the following:

Tested with IAR and GCC (sram configration)

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
loop1 | write/read/compare full DRR | PASSED | PASSED
loop2 | write/read/compare full DRR | PASSED | PASSED
loop3 | write/read/compare full DRR | PASSED | PASSED
