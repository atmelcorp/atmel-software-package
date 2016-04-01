USB_IAD_CDC_CDC EXAMPLE
=======================

# Objectives
------------
This example aims to test the USB Device Port(UDP) and dual USB Communication
Device class (CDC).

# Example Description
---------------------
The demonstration program simulates two serial device. When the board running
this program connected to a host (PC for example), with USB cable, the board
appears two serial for the host, and one can display the character which
another input.

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

## Start the application (SAMA5D2-XPLAINED)
-------------------------------------------
In the terminal window, the following text should appear (values depend on the
board and chip used):
```
 -- USB Dual CDC Device Project xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
```
Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Open one serial | open one serial through host software, print 'SerialPort0 ON' | PASSED | PASSED
Open another serial | open another serial through host software, print 'SerialPort1 ON' | PASSED | PASSED
Communicate with each other | input letter in one serial, another would display, vice-versa | PASSED | PASSED

# Log
-----

## Current version
------------------
 - v1.3

## History
----------
