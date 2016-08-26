USART EXAMPLE
=============

# Objectives
------------
This example aims to perform peripheral data transfer over USART.

# Example Description
---------------------
The example handles the transfer between two USART peripherals,
transfer/receive data to/from USART each other with polling mode, using IRQs, or DMA.

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

### sama5d2-xplained
--------------------
Connect USART0 (RX on J22:3, TX on J22:4)

### sama5d4-xplained
--------------------
Connect USART4

### sama5d4-ek
--------------
Connect USART4

### sama5d3-xplained
--------------------
Connect USART3 (pin 1 on J20 and pin 2 on J20)

## Start the application
------------------------

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

