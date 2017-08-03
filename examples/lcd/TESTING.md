LCD EXAMPLE
============

# Objectives
------------
This example aims to  demonstrates how to configure the LCD Controller (LCDC)
to use the LCD on the board.

# Example Description
---------------------
The example configures the LCDC for LCD to display and then draw test patterns on LCD.
4 layers are displayed:
 - Base: The layer at bottom, show test pattern with color blocks.
 - OVR1: The layer over base, used as canvas to draw shapes.
 - OVR2: The layer over base, used as canvas to draw shapes.
 - HEO:  The next layer, showed scaled ('F') which flips or rotates once  for a while.

# Test
------
## Supported targets
--------------------
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
* SAMA5D3-EK
* SAMA5D3-XPLAINED
* SAMA5D4-EK
* SAMA5D4-XPLAINED

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

Tested with IAR and GCC (sram and ddram configration)

PASSED

