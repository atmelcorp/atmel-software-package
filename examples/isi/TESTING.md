ISC EXAMPLE
============

# Objectives
------------
This example aims to manages incoming data from CMOS sensor with the Image
Sensor Controller (ISI).

# Example Description
---------------------
This example shows how to configure the internal image processor.
It introduces how to samples data stream to expected data format and 
transfer with DMA master module. The example support the image sensor with a data 
width of 8 bits in YUV format.

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

Connect OV7740 image sensor with on board J15 ISI.
Connect LCD with on board J9 LCD interface.

## Start the application (SAMA5D4-EK)
--------

Tested with IAR and GCC (ddram configration)
In order to test this example, the process is the following:

Press [0|1|2|3|4][5] to select supported sensor
- '0' omnivision 2640
- '1' omnivision 2643
- '2' omnivision 5640
- '3' omnivision 7740
- '4' omnivision 9740

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press '3'| Select Image sensor 7740 | Video output in YUV | PASSED

-I- Press 'C' to capture image, press 'P' back to preview mode

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'C' | Capture image | PASSED | PASSED
Press 'P' | Preview mode  | PASSED | PASSED

# Log
------

## Current version
--------
 - v1.3

## History
--------
