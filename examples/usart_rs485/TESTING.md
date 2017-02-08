USART RS485 EXAMPLE
===================

# Objectives
------------
This example aims to perform peripheral data transfer over USART rs485 mode.

# Example Description
---------------------
The example handles the transfer between two USART peripherals,
transfer/receive data to/from USART rs485 mode.

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

### sama5dx\same70\samv71 board
--------------------
 *  This package can be used with SAMA5Dx/SAME70/SAMV71 board. Before running, make sure to connect
 *  two boards with RS485 lines. The rs485 adapt board(ADM3485ARZ) for this purpose.
 *  Match each paired pins of two boards respectively with A to A,
 *  B to B and FGND to FGND(the central pin of J3).
 *  this part is connect with Sama5Dx board and ADM3485ARZ
 *   -  Board 1                                                  Board 2
 *   -  TXD(sama5dx/same70/samv71 board) <-> DI(ADM3485ARZ)      TXD(sama5dx/same70/samv71 board) <-> DI(ADM3485ARZ)
 *   -  RXD(sama5dx/same70/samv71 board) <-> RO(ADM3485ARZ)      RXD(sama5dx/same70/samv71 board) <-> RO(ADM3485ARZ)
 *   -  RTS(sama5dx/same70/samv71 board) <-> DE(ADM3485ARZ)      RTS(sama5dx/same70/samv71 board) <-> DE(ADM3485ARZ)
 *   -  3.3v                                   3.3v
 *   -  GND                                    GND
 *   -  2 ways to connect !RE(ADM3485ARZ)
 *   -  1. RTS(sama5dx/same70/samv71 board) <-> RE(ADM3485ARZ)   RTS(sama5dx/same70/samv71 board) <-> RE(ADM3485ARZ)
 *   -  2. RE(ADM3485ARZ) <-> GND                                RE(ADM3485ARZ) <-> GND
 *  this part is connect with 2 ADM3485ARZ
 *      A              <-------------------->  A
 *      B              <-------------------->  B
 *      PGND           <-------------------->  PGND

## Start the application
------------------------

t
      Transmit pattern to another usart 
r
      Receive data from another usart
m
      Display menu

Tested with IAR and GCC (sram ddram configration)


In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 't' | write text through usart | receive characters on another board | PASSED
Press 'r' | Receive text from another board | display the characters  | PASSED
Press 'm'| Display the menu | Display the help menu on console | PASSED

