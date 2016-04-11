PDMIC EXAMPLE
============

# Objectives
------------
This example aims to test the PDMIC peripheral.

# Example Description
---------------------
The demonstration program test the PDMIC to record sound. When the board
running this program, it can recore sound through PDMIC for serveal seconds and
then play the record sound using CLASSD speaker.

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
Connect the main board with the Audio xplainedboard, then connect the speaker
to the CLASSD interface of main board.

In the terminal window, the following text should appear (values depend on the
board and chip used):
```
 -- PDMIC Example xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
 Select an option :
 -----------------	
 1 -> Record the sound with DMA
 2 -> Record the sound for polling
 3 -> Playback the record sound using CLASSD	
 + -> Increase the gain of record sound(increased 10dB)
 - -> Decrease the gain of record sound(reduced 10dB)
 =>	
```

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press '1' | Record the sound with DMA | PASSED | PASSED
Press '2' | Record the sound for polling | PASSED | PASSED
Press '3' | Playback the record sound using CLASSD, sound is heard | PASSED | PASSED
Press '+' | Increase the gain of record sound | PASSED | PASSED
Press '-' | Decrease the gain of record sound | PASSED | PASSED


# Log
------

## Current version
--------
 - v1.3

## History
--------
