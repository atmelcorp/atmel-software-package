USB_HID_MSD EXAMPLE
===================

# Objectives
------------
This example aims to test the USB Device Port(UDP) and USB Composite HID MSD
classes.

# Example Description
---------------------
The demonstration program simulates a USB device that integrates HID Keyboard
and mass storage function. When the board running this program connected to a
host (PC for example), with USB cable, the board appears as a ramdisk and a USB
Human Interface Device for the host. Then the host can read or write the
ramdisk and input characters through board.

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
 -- USB HIDMSD Device Project xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
```

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Input '1' in console | Print 'Key 0 pressed' in console | PASSED | PASSED
Input '2' in console | Print 'Key 1 pressed' in console | PASSED | PASSED
Input any character except '1' and '2' in console | the character input is display in console | PASSED | PASSED
Format disk | Format all disk | PASSED | PASSED
Write and read disk | Create a file in disk, write some string to file and save, close the file and then read the content | PASSED | PASSED
