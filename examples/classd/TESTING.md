CLASSD EXAMPLE
============

# Objectives
------------
This example aims to test the CLASSD peripheral.

# Example Description
---------------------
The demonstration program tests the CLASSD output. When the board runs this
program, it can play a music sample on a small speaker.



# Test
------

## Supported targets
--------------------
* SAMA5D2-XPLAINED: support classd right channel.
* SAM9X60-EK: support classd left channel, [MCK is 196.608MHz](../../flash_loaders/README.md).

## Setup
--------
On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:
 - 115200 bauds
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control

## Start the application
--------
First, connect an external speaker to the Class-D audio output of the board,
usually available on a 4-way terminal block.
Second, place the jumper which powers the Class-D output stage from the
on-board +5V power rail.

In the terminal window, the following text should appear (actual values depend
on the board and chip used):
```
-- CLASSD Example --
Softpack vx.xx
Built for xxxxxxx-xx

Configuring ClassD: Full H-Bridge at 48000Hz
Setting attenuation to -30dB

Select an option:
-----------------
1 -> Play the Demo Audio in polling mode
2 -> Play the Demo Audio in DMA mode
3 -> Output Audio PMC Clock to PCK1 IOS2
+ -> Increase the volume (attenuation reduced by 3dB)
- -> Decrease the volume (attenuation increased by 3dB)
=>
```

Tested with IAR and GCC (ddram configuration only)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press '+' | Increase the volume of sound | PASSED | PASSED
Press '-' | Decrease the volume of sound | PASSED | PASSED
Press '1' | Play the demo audio in polling mode, sound is heard | PASSED | PASSED
Press '2' | Play the demo audio using DMA, sound is heard | PASSED | PASSED
Press '3' | Output Audio PMC Clock to PCK1 IOS2, connect the pin with oscillograph | PASSED | PASSED
