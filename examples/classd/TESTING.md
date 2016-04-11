CLASSD EXAMPLE
============

# Objectives
------------
This example aims to test the CLASSD peripheral.

# Example Description
---------------------
The demonstration program test the CLASSD Speaker. When the board running this
program, it can play demonstration music with speaker.

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

## Start the application (SAMA5D2-XPLAINED)
--------
Firstly connect the speaker to the classd interface of main board.

In the terminal window, the following text should appear (values depend on the
board and chip used):
```
 -- CLASSD Example xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
 Select an option :
 -----------------	
 1 -> Display Demo Audio Information
 2 -> Play the Demo Audio without DMA
 3 -> Play the Demo Audio with DMA	
 4 -> Output Audio PMC Clock to PCK1 IOS2
 + -> Increase the volume (attenuation reduced by 3dB)
 - -> Decrease the volume (attenuation increased by 3dB)
 =>	
```

Tested with IAR and GCC (ddram configuration only)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press '1' | Display demo audio information | PASSED | PASSED
Press '2' | Play the demo audio without DMA, sound is heard | PASSED | PASSED
Press '3' | Play the demo audio with DMA, sound is heard | PASSED | PASSED
Press '4' | Output Audio PMC Clock to PCK1 IOS2, connect the pin with oscillograph | PASSED | PASSED
Press '+' | Increase the volume of sound | PASSED | PASSED
Press '-' | Decrease the volume of sound | PASSED | PASSED


# Log
------

## Current version
--------
 - v1.3

## History
--------
