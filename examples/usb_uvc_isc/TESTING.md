USB_UVC_ISC EXAMPLE
============

# Objectives
------------
This example aims to manages incoming data from CMOS sensor with the Image
Sensor Controller (ISC).

# Example Description
---------------------
 This example shows how to configure the internal image processor includes
color filter array interpolation, gamma correction, 12 bits to 10 bits
compression, color space conversion, luminance adjustment. It introduces how to
samples data stream to expected data format and transfer with DMA master
module. The example support the image sensor with a data width of 8 bits in YUV
format.

# Test
------
## Supported targets
--------------------
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK

## Setup
--------
On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:
 - 115200 bauds
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control
 
--- SAMA5D2-XPLAINED
Connect image sensor with on board J18 ISC.

--- SAMA5D27-SOM1-EK
Connect image sensor with on board J27 ISC. (it requires cross-wire D0-D11 shift to D0-D4)

## Start the application
--------

Image Sensor Selection:
- '1' OV2640
- '2' OV2643
- '3' OV5640
- '4' OV7670
- '5' OV7740
- '6' OV9740
Press [1..6] to select supported sensor

Tested with IAR and GCC (ddram configration)
In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Open USB camera application on Host PC, preview start...
