USB_HID_TRANSFER EXAMPLE
========================

# Objectives
------------
This example aims to test the USB Device Port(UDP) and USB Human Interface
Device class (HID).

# Example Description
---------------------
The demonstration program simulates a customized HID device that reports
customized data stream, in which informations on LEDs and buttons are packed to
host.

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

When this program runs connected to a host (PC for example), with USB cable,
the board appears as a "USB Human Interface Device" for the host. Use the
client application to read/write on it.

In the terminal window, the following text should appear (values depend on the
board and chip used):
```
 -- USB Device HID Transfer Project xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
```
Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
LED control | Press the LED button in hidTest.exe to open and close the len in board | PASSED | PASSED
Read/Write data | Press the read or write button in hidTest.exe to read or write data | PASSED | PASSED
Get/Set Report | Press the get or set report in hidTest.exe to read or write report | PASSED | PASSED
Get/Set Feature | Press the get or set feature in hidTest.exe to read or write feature | PASSED | PASSED
Monitor buttons | Press the monitor button in hidTest.exe to display the status of monitor button | PASSED | PASSED
