USB_UVC_ISI EXAMPLE
============

# Objectives
------------
This example aims to manage incoming data from CMOS sensor with the Image Sensor Interface (ISI).
Running this example, the kit operates as a USB webcam.

# Example Description
---------------------
This example shows how to configure the internal image processor.
It introduces how to sample data stream to expected data format and transfer with DMA master module.
The example supports the image sensor with a data width of 8 bits in YUV format.

# Test
------
## Supported targets
--------------------

* SAM9XX5-EK with the ++AT91SAM9G25-CM++ CPU Module (sam9g25-ek)
* SAM9X60-EK Rev. B (sam9x60-ek)
* SAMA5D3-EK
* SAMA5D4-EK

Supported ISI modules:
* CAMx-OV2640-EB
* CAMx-OV2643-EB
* CAMx-OV5640-EB
* CAMx-OV7670-EB
* CAMx-OV7740-EB
* CAMx-OV9740-EB

## Setup
--------
On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:
 - 115200 bauds
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control

-- SAM9XX5-EK
Plug a male-to-male header on the ISI/LCD connector (J21). Plug the ISI Module on top of it.

-- SAM9X60-EK Rev. B
Plug the ISI Module on the ISI connector (J17).

-- SAMA5D3-EK
Plug the ISI Module on the ISI connector (J11).

-- SAMA5D4-EK
Plug the ISI Module on the ISI connector (J15).

## Start the application
--------

Tested with IAR<sup>®</sup> and GCC (ddram configration)
In order to test this example, the process is the following:

Begin with the board's USB device port disconnected from the host computer.

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
(No further action required) | Automatic detection and configuration of the image sensor | The PID of the sensor is displayed | PASS
Connect to the USB host computer | Host computer enumerates the USB Video Device | The USB Video Device shows up in Device Manager<sup>®</sup> | PASS
Have Skype<sup>®</sup> / Camera<sup>®</sup> or equivalent SW open the USB Video Device | The board streams video to the host computer | The webcam application plays the live stream from the image sensor | PASS

The example offers to stream the video in QVGA (320x240) or VGA (640x480) resolution.
Skype<sup>®</sup> may select QVGA resolution by default.
The Camera<sup>®</sup> app may select VGA resolution by default.
