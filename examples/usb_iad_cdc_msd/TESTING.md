USB_IAD_CDC_MSD EXAMPLE
=======================

# Objectives
------------
This example aims to test the USB Device Port(UDP), USB Communication Device
class(CDC) and USB Mass Storage class (MSD).

# Example Description
---------------------
The demonstration program simulates a USB composite device that integrates USB
CDC Serial RS232 Converter function and USB Disk function. When the board
running this program connected to a host (PC for example), with USB cable, the
board appears as a USB Disk for the host, then the host can format/read/write
on the disk. At the same time, the usb serial also can be open by host
software.

# Test
------
## Supported targets
--------------------
* SAM9XX5-EK
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
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

In the terminal window, the following text should appear (values depend on the
board and chip used):
```
 -- USB CDCMSD Device Project xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
```

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Open serial | Open serial through host software e.g. HyperTerminal on Microsoft Window | PASSED | PASSED
Format ramdisk | Format ramdisk | PASSED | PASSED
Write and read disk | Create a file on disk, write some string to file and save, close the file and then read the content | PASSED | PASSED


# Log
-----

## Current version
------------------
 - v1.3

## History
----------
