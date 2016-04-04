XDMA_USART EXAMPLE
============

# Objectives
------------
This example aims to perform peripheral data transfer with XDMA peripheral.

# Example Description
---------------------
The example handles the transfer between two USART peripherals,
transfer/receive data to/from USART each other with XDMA.

# Test
------

## Setup
--------
On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:
 - 57600 bauds (for sama5d2-xplained)
 - 115200 bauds (for sama5d4-xplained)
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control

Connect USART with on board J21
XPRO_PD12 TXD
XPRO_PD13 RXD

On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:
 - 115200 bauds
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control

## Start the application (SAMA5D2-xPlained)
-------------------------------------------

r size
      Wait to recieve 'size' characters from usart and
      print the result string (block call)
w str
      Write 'str' throught usart
m
      Print this menu

Tested with IAR and GCC (sram ddram configration)


In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'w 11223344' | write string throught usart1 | receive "11223344" in usart4 | PASSED
Press 'r 200' | Receive 100 characters from usart4 | Waiting... | PASSED
Send text file from usart4|Send string | Receive 100 characters from usart4 | PASSED

# Log
------

## Current version
------------------
 - v1.3

## History
----------
