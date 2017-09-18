USB_MASS_STORAGE EXAMPLE
========================

# Objectives
------------
This example aims to test the USB Device Port(UDP) and USB Mass Storage class
(MSD).

# Example Description
---------------------
The demonstration program simulates an USB massstorage device. When the board
running this program connected to a host (PC for example), with USB cable, the
board appears as a USB Disk for the host, then the host can format/read/write
on the disk.

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

When connecting USB cable to windows, the host reports a new USB device
attachment and Disk installation. Then new "USB Mass Storage Device" and "ATMEL
Mass Storage MSD USB Device" and "Generic volume" appear in hardware device
list.

In the terminal window, the following text should appear (values depend on the
board and chip used):
```
 -- USB DeviceMass Storage Example xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
```

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
SD card detect | Runing the program with sd card instert, SD card can appear as one disk | PASSED | PASSED
Format disk | Format all disk | PASSED | PASSED
Write and read disk | Create a file in disk, write some string to file and save, close the file and then read the content | PASSED | PASSED

