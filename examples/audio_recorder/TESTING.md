Audio Recorder EXAMPLE
============

# Objectives
------------
This example aims to test the Audio Recorder peripheral.

# Example Description
---------------------
The demonstration program test the audio device to record sound. When the board
running this program, it can record sound through SSC or PDMIC for serveral seconds and
then play the record sound.

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
Connect the main board with the Audio xplainedboard for SAMA5D2-XPLAINED board or 
insert line-in cable with PC headphone for SAMA5D4-EK board.

In the terminal window, the following text should appear (values depend on the
board and chip used):
```
 -- Audio Recorder Example xxx --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
 Select an option :
 -----------------	
 R -> Record the sound
 P -> Playback the record sound
 + -> Increase the volume of playback sound
 - -> Decrease the volume of playback sound
 =>	
```

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press 'R' | Record the sound | PASSED | PASSED
Press 'P' | Playback the record sound, sound is heard | PASSED | PASSED
Press '+' | Increase the volume of playback sound | PASSED | PASSED
Press '-' | Decrease the volume of playback sound | PASSED | PASSED


# Log
------

## Current version
--------
 - v2.1

## History
--------
