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
## Supported targets
--------------------
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK (Hardware need modification)

## Setup
--------
On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:
 - 115200 bauds
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control

-- SAMA5D2-XPLAINED
Connect image sensor with on board J18 ISC.
Connect LCD with on board J2 LCD interface.

--- SAMA5D27-SOM1-EK
Connect image sensor with on board J27 ISC. Connect LCD with on board J26 LCD interface.
We cannot simply connect Microchip's Sensor daughter board directly to get correct image.

- CONNECT Microchip's Sensor daughter board TO SAMA5D27-SOM1-EK will not work
	ISC_D11 ---------- SENSOR D11
	ISC_D10 ---------- SENSOR D10
	ISC_D9 ----------- SENSOR D9
	ISC_D8 ----------- SENSOR D8
	ISC_D7 ----------- SENSOR D7
	ISC_D6 ----------- SENSOR D6
	ISC_D5 ----------- SENSOR D5
	ISC_D4 ----------- SENSOR D4
	ISC_D3 ----------- SENSOR D3
	ISC_D2 ----------- SENSOR D2
	ISC_D1 ----------- SENSOR D1
	ISC_D0 ----------- SENSOR D0
	
	For example:
	Data Mapping Raw Bayer Raw Bayer YUV422     YUV422
	             12-bit    10-bit    8-bit      10-bit
	ISC_D11      RGGB[11]  RGGB[9]   YC422[7]   YC422[9]
	ISC_D10      RGGB[10]  RGGB[8]   YC422[6]   YC422[8]
	ISC_D9       RGGB[9]   RGGB[7]   YC422[5]   YC422[7]
	ISC_D8       RGGB[8]   RGGB[6]   YC422[4]   YC422[6]
	ISC_D7       RGGB[7]   RGGB[5]   YC422[3]   YC422[5]
	ISC_D6       RGGB[6]   RGGB[4]   YC422[2]   YC422[4]
	ISC_D5       RGGB[5]   RGGB[3]   YC422[1]   YC422[3]
	ISC_D4       RGGB[4]   RGGB[2]   YC422[0]   YC422[2]
	ISC_D3       RGGB[3]   RGGB[1]   0          YC422[1]
	ISC_D2       RGGB[2]   RGGB[0]   0          YC422[0]
	ISC_D1       RGGB[1]   RGGB[9]   0          0
	ISC_D0       RGGB[0]   RGGB[8]   0          0
	
	The ISC data pins is always aligned with highest bit, 8-bit YUV422 mode for example, ISC_(D0 - D3) are not used.
	
- CORRECT CONNECTION (8-BITS MODE) ARE:
	ISC_D11  ---------- SENSOR D7
	ISC_D10 ----------- SENSOR D6
	ISC_D9  ----------- SENSOR D5
	ISC_D8  ----------- SENSOR D4
	ISC_D7  ----------- SENSOR D3
	ISC_D6  ----------- SENSOR D2
	ISC_D5  ----------- SENSOR D1
	ISC_D4  ----------- SENSOR D0

## Start the application
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
