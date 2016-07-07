USB_UVC_IS1 EXAMPLE
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

Connect image sensor with on board J15 ISI.

## Start the application (SAMA5D4-EK,SAMA5D4-XPLAINED)
--------

Tested with IAR and GCC (ddram configration)
In order to test this example, the process is the following:


Image Sensor Selection:
- '1' OV2640
- '2' OV2643
- '3' OV5640
- '4' OV7670
- '5' OV7740
- '6' OV9740
Press [1..6] to select supported sensor

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press '5'| Select Image sensor 7740 | Video output in YUV | PASSED

Open USB camera application on Host PC, preview start...


