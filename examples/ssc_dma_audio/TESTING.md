SSC_DMA_AUDIO EXAMPLE
=========================

# Objectives
------------
This example aims to test the SSC dma audio example.

# Example Description
---------------------
The demonstration program uses the Synchronous Serial Controller (SSC) of an SAMA5D4x
microcontroller to output an audio stream through the on-board WM8904 CODEC.

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

## Start the application (SAMA5D4-EK)
-------------------------------------------
This program plays a WAV file from PC via Line-In. The audio stream is sent through 
the SSC interface connected to the on-board WM8904, enabling the sound to be audible 
using a pair of headphones.

In the terminal window, the following text should appear (values depend on the board and chip used):
```
 -- SSC DMA Audio Example xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
```

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Play sound through host software | Sound is heard using a pair of headphones | PASSED | PASSED


# Log
-----

## Current version
------------------
 - v1.3

## History
----------
