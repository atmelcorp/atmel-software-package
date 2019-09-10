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

* SAMA5D2-PTC-EK
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK
* SAMA5D3-EK
* SAMA5D3-XPLAINED
* SAMA5D4-EK
* SAMA5D4-XPLAINED
* SAM9X60-EK

## Setup

On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:
 - 115200 bauds
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control
 
### VARIANTs

This program support both SRAM and DRAM variants. 

In DRAM variant, we run the code in SRAM while keep DRAM in self-refresh mode. 
In this way, we can reach a much lower power consumption. 
(Be careful, we need to disable DRAM access from all peripherals).

## Start the application

### VARIANT = DRAM
In the terminal window, the following text should appear (values depend on the
 board and chip used): 
 
```
 -- Low Power mode --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
 Select an option :
NULL
```

Tested with IAR and GCC, with the following process:

Step | Text received from terminal | Expected Result | Result
-----|-----------------------------|-----------------|-------
NULL
### VARIANT = SRAM

In the terminal window, the following text should appear (values depend on the
 board and chip used): 

```
 -- Low Power mode --
 -- SAMxxxxx-xx
 -- Compiled: xxx xx xxxx xx:xx:xx --
 Select an option :
NULL
```

Tested with IAR and GCC, with the following process:

Step | Text received from terminal | Expected Result | Result
-----|-----------------------------|-----------------|-------
NULL


# Note:
-------
 * Some DDR related operations are omitted while running out of DDR.
 * The battery should be mounted and 'Force Power UP' jumper should be opened to support the BackUp mode correctly.
 * There are two ULP modes for SAMA5D2 while only one ULP mode for SAMA5D4.
 * The JTAG connection is lost with ULP1 or BackUp mode.
 