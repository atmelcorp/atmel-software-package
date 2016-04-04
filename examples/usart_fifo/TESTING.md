FIFO EXAMPLE
============

# Objectives
------------
This example aims to performs USART data transfer in FIFO mode.

# Example Description
---------------------
The example handle the transfer between two USART peripherals, transfer/receive
data to/from USART with Usart FIFO mode.

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

## SAMA5D2-xPlained
Connect the F3_TXD and F3_RXD pins of board to the serial of PC.

On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:
 - 115200 bauds
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control

## Start the application (SAMA5D2-xPlained)
--------

-- ESC to Enable/Disable ECHO on Usart --
-- Press 't' to send test data to Usart --
Tested with IAR and GCC (sram ddram configration)


In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 't' | send test data to Usart | receive test data from flexcom3 | PASSED
Press '1234' on Flexcom3 | send test data | display 1234 from flexcom3 | PASSED
Press 'ESC' | Echo off | PASSED | PASSED
Press '1234' on Flexcom3 | send test data | Nothing | PASSED

# Log
------

## Current version
--------
 - v1.3

## History
--------
