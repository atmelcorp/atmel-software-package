USB_IAD_CDC_AUD EXAMPLE
=======================

# Objectives
------------
This example aims to test the USB Device Port(UDP) and USB Composite Device
have a USB Virtual COM port with a USB Audio Device.

# Example Description
---------------------
The demonstration program simulates a USB serial and a USB audio device. When
the board running this program connected to a host (PC for example), with USB
cable, the board appears as a "USB Composite Device" and "USB Audio Device" in
the hardware device list.

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
-------------------------------------------
In the terminal window, the following text should appear (values depend on the
board and chip used):
```
 -- USB CDC + Audio Device Example xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
```

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Play sound through host software | Sound is heard | PASSED | PASSED
Serial echo | open the virtual com and echo the character input | PASSED | PASSED


# Log
-----

## Current version
------------------
 - v1.3

## History
----------
