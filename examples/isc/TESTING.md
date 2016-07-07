ISC EXAMPLE
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
format and 10 bits raw Bayer format.

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

Connect OV7740 image sensor with on board J18 ISC.
Connect LCD with on board J2 LCD interface.

## Start the application (SAMA5D2-XPLAINED)
--------

Tested with IAR and GCC (ddram configration)
In order to test this example, the process is the following:

 - 'Y' Test YUV mode input

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'Y'| Test YUV input mode | Video output in YUV | PASSED
Press 'S'| Switch mode | PASSED | PASSED

- 'B' Test RAW BAYER mode input
- '0' Test RGB565 output
- '1' Test YC422P output
- '2' Test YC422SP output
- '3' Test YC420P output
- '4' Test YC420SP output
Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'B' | Test RAW BAYER mode input | PASSED | PASSED
Press '0' | Test RGB565 output | video output with RGB565 | PASSED
Press 'S' | Switch mode | PASSED | PASSED
Press '1' | YC422P output | video output with YC422P | PASSED
Press 'S' | Switch mode | PASSED | PASSED
Press '2' | Test YC422SP output | video output with YC422SP | PASSED
Press 'S' | Switch mode | PASSED | PASSED
Press '3' | Test YC420P output | video output with YC420P | PASSED
Press 'S' | Switch mode | PASSED | PASSED
Press '4' | Test YC420SP output | video output with YC420SP | PASSED
