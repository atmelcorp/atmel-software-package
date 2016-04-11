USB_HID_AUD EXAMPLE
===================

# Objectives
------------
This example aims to test the USB Device Port(UDP) and USB Composite HID Audio
classes.

# Example Description
---------------------
The demonstration program simulates a USB device that integrates HID Keyboard
and Audio Desktop Speaker function. When the board running this program
connected to a host (PC for example), with USB cable, the board appears as a
desktop speaker and a USB Humen Interface Device for the host. Then the host
can play sound and input characters through board.

# Test
------

## Setup
--------
On the computer, open and configure a terminal application (e.g. HyperTerminal
on Microsoft Windows) with these settings:
 - 115200 bauds
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control

## Start the application (SAMA5D2-XPLAINED)
-------------------------------------------
When connecting USB cable to windows, the host reports a new USB device
attachment. You can find new "USB Composite Device" and "USB Audio Device"
appear in the hardware device list. Play sound in host side through the USB
Audio Device, and it can be heard from the amplifier connected to the board.
The character input by keyboard also display in console.

In the terminal window, the following text should appear (values depend on the
board and chip used):
```
 -- USB HID + Audio Device Example xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
 -- : DBG key 1 2 used as buttons
 -- : 1st press to push, 2nd press to release
```

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Play sound through host software | Sound is heard | PASSED | PASSED
Input '1' in console | Print 'Key 0 pressed' in console | PASSED | PASSED
Input '2' in console | Print 'Key 1 pressed' in console | PASSED | PASSED
Input any character except '1' and '2' in console | the character input is display in console | PASSED | PASSED


# Log
-----

## Current version
------------------
 - v1.3

## History
----------
