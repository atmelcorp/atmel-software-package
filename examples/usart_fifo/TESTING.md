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
 - 115200 bauds
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control

## Start the application (SAMA5D2-Xplained)
--------

-- ESC to Enable/Disable ECHO on Usart --
-- Press 't' to send test data to Usart --
Tested with IAR and GCC (sram ddram configration)

This example can be tested either in loopback mode (by connecting TX to RX) or
with a PC connected to the USART TX/RX.

### Loopback testing

Connect together pins F3_TXD and F3_RXD on the board.

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 't' on console | send test data to Usart | received test data is displayed on console | PASSED

### PC testing

Connect pins F3_TXD and F3_RXD pins of the board to the PC serial port.
Configure this serial port with the same settings as the console (see section
Setup).

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 't' on console | send test data to Usart | PC receives test data | PASSED
Send '1234' from PC to Usart | send test data | received data '1234' is displayed on console | PASSED
Press 'ESC' on console | enable Usart echo | console displays "USART Echo ON"  | PASSED
Send '1234' from PC to Usart | send test data | PC receives '1234' from Usart | PASSED

# Log
------

## Current version
--------
 - v1.3

## History
--------
