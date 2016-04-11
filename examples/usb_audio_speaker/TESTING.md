USB_AUDIO_SPEAKER EXAMPLE
=========================

# Objectives
------------
This example aims to test the USB Device Port(UDP) and USB Audio Class.

# Example Description
---------------------
The demonstration program simulates an USB Desktop Speaker. When the board
running this program connected to a host (PC for example), with USB cable, the
board appears as a desktop speaker for the host. Then the host can play sound
through host software. The audio stream from the host is then sent to the
board, and eventually sent to audio DAC connected to the amplifier.

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
When connecting USB cable to host, the host reports a new USB device
attachment. The new "USB Audio Device" appear in the hardware device list, then
play sound in host side through the USB Audio Device, and it can be heard from
the speaker connected to the board.

In the terminal window, the following text should appear (values depend on the board and chip used):
```
 -- USB Device Audio Speaker Example xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
```

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Play sound through host software | Sound is heard | PASSED | PASSED


# Log
-----

## Current version
------------------
 - v1.3

## History
----------
