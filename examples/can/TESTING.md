CAN EXAMPLE
============

# Objectives
------------
This example aims to help new users get familiar with the MCAN (Controller Area Network) peripheral.

# Example Description
---------------------
The demonstration program transmits several different CAN messages. Since it
also enables the CAN loopback mode, the transmitted messages are reflected back
as received messages too. Both standard CAN and CAN FD operation can be tested.

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

## Start the application (SAMA5D2-XPLAINED)
--------

 Press [c|f|s] to set CAN or CAN FD mode
    -  c: ISO 11898-1 CAN
    -  f: ISO 11898-7 CAN FD, 64-byte data
    -  s: ISO 11898-7 CAN FD, 64-byte data, 2 Mbps data bit
Press [l] to toggle the integrated MCAN loop-back on/off
p: Send sample messages
h: Display this menu

In order to test this example, the process is the following:

Tested with IAR and GCC (sram ddram configration)

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'c'.'p' | ISO 11898-1 CAN,| PASSED | PASSED
Press 'f'.'p' | ISO 11898-7 CAN FD, 64-byte data| PASSED | PASSED
Press 's'.'p' | ISO 11898-7 CAN FD, 64-byte data, 2 Mbps data bit| PASSED | PASSED
Press 'l'.'p' | toggle the integrated MCAN loop-back off| FAILED | PASSED
Press 'l' | toggle the integrated MCAN loop-back on| PASSED | PASSED

# Log
------

## Current version
--------
 - v1.3

## History
--------
