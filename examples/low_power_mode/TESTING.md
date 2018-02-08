LOW_POWER_MODE EXAMPLE
============

# Objectives
------------
This example aims to test Low-power modes.


# Example Description
---------------------
The demonstration program offers methods to make the device enter low power
mode, users can also change the settings of clock and DDR.

Power consumptions could be measured by ammeters connected between the jumpers
of `VDDCORE` or `VDDBU`.


# Test
------
## Supported targets
--------------------
* SAMA5D2-PTC-EK
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
* SAMA5D3-EK
* SAMA5D3-XPLAINED
* SAMA5D4-EK
* SAMA5D4-XPLAINED

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
------------------------
* In the terminal window, the following text should appear (values depend on the
 board and chip used):
```
 -- Low Power mode --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
 Select an option :
 0 -> Select clock setting
 1 -> Enter BackUp mode
 2 -> Enter Ultra Low Power mode 0
 3 -> Enter Ultra Low Power mode 1
 4 -> Enter Idle mode
 A -> Init DDR
 B -> Write data in DDR
 C -> Check data in DDR
 D -> Set DDR self-refresh mode and isolate Pads
 E -> Reset DDR to normal mode and reconnect Pads
```
```
Note:
 * some DDR related operations are omitted while running out of DDR.
 * The battery should be mounted to support the BackUp mode correctly.
 * There are two ULP modes for SAMA5D2 while only one ULP mode for SAMA5D4.
 * SAMA5D2-PTC-EK and SAMA5D27-SOM1-EK's clock source are 24MHz crystal oscillator,therefore, MCK=164Mhz, PLLA = 492 Mhz, Processor clock = 492 Mhz as default setup.
 
```

Tested with IAR and GCC (sram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press '0' | Print `Will use clock setting for test: PCK = MCK = Crystal 12MHz` on screen | PASSED | PASSED
Press '0' | Print `Will use clock setting for test: PCK = MCK = Crystal 12MHz/16 = 750k Hz` on screen | PASSED | PASSED
Press '0' | Print `Will use clock setting for test: PCK = MCK = Crystal 12MHz/64 = 187.5k Hz` on screen | PASSED | PASSED
Press '0' | Print `Will use clock setting for test: PCK = MCK = Crystal 32k Hz` on screen | PASSED | PASSED
Press '0' | Print `Will use clock setting for test: PCK = MCK = Crystal 32k/64 = 512 Hz` on screen | PASSED | PASSED
Press '0' | Print `Will use clock setting for test: PCK = MCK = RC 12MHz` on screen | PASSED | PASSED
Press '0' | Print `Will use clock setting for test: PCK = 396, MCK = 132MHz` on screen | PASSED | PASSED
Press '0' | Print `Will use clock setting for test: PCK = 498, MCK = 166MHz` on screen | PASSED | PASSED
Press '1' | Print `Enter Backup mode` on screen | PASSED | PASSED
Press '2' | Print `Enter Ultra Low Power mode 0` on screen | PASSED | PASSED
Press '3' | Print `Enter Ultra Low Power mode 1` ... `Leave Ultra Low Power mode` on screen | PASSED | PASSED
Press '4' | Print `Configure button with debouncing` ... `Enter Idle mode` on screen | PASSED | PASSED
Press any key | Print `Leave Idle mode` on screen | PASSED | PASSED
Press 'A' | Print `Init DDR` ... on screen | PASSED | PASSED
Press 'B' | Print `Write data into DDR` ... `end of init` on screen | PASSED | PASSED
Press 'C' | Print `Verify data in DDR` ... `data OK` on screen | PASSED | PASSED
Press 'D' | Print `Set DDR into self-refresh` on screen | PASSED | PASSED
Press 'E' | Print `Out of DDR Self refresh state` on screen | PASSED | PASSED
Press 'D' | Print `Set DDR into self-refresh` on screen | PASSED | PASSED
Press '3' | Print `Enter Ultra Low Power mode 1` ... on screen | PASSED | PASSED
Press `WAKE UP` | Print `Leave Ultra Low Power mode` on screen | PASSED | PASSED
Press 'C' | Print `Verify data in DDR` ... `data OK` on screen | PASSED | FAILED

