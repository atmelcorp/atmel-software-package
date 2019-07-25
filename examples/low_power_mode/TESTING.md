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
 0 -> Select clock setting
 1 -> Enter BackUp mode
 2 -> Enter Ultra Low Power mode 0
 3 -> Enter Ultra Low Power mode 1
 4 -> Enter Idle mode
```

Tested with IAR and GCC, with the following process:

Step | Text received from terminal | Expected Result | Result
-----|-----------------------------|-----------------|-------
Press '0' | Will use clock setting for test: PCK = MCK = Crystal 12MHz | PASSED | PASSED
Press '0' | Will use clock setting for test: PCK = MCK = Crystal 12MHz/16 = 750k Hz | PASSED | PASSED
Press '0' | Will use clock setting for test: PCK = MCK = Crystal 12MHz/64 = 187.5k Hz | PASSED | PASSED
Press '0' | Will use clock setting for test: PCK = MCK = Crystal 32k Hz | PASSED | PASSED
Press '0' | Will use clock setting for test: PCK = MCK = Crystal 32k/64 = 512 Hz | PASSED | PASSED
Press '0' | Will use clock setting for test: PCK = MCK = RC 12MHz | PASSED | PASSED
Press '0' | Will use clock setting for test: PCK = 396, MCK = 132MHz | PASSED | PASSED
Press '0' | Will use clock setting for test: PCK = 498, MCK = 166MHz | PASSED | PASSED
Press '1' | Enter Backup mode | PASSED | PASSED
Press WAKE_UP |	RomBOOT | PASSED | PASSED
Press '2' | Enter Ultra Low Power mode 0 | PASSED | PASSED
Press USER_BTN | Leave Ultra Low Power mode | PASSED | PASSED
Press '3' | Enter Ultra Low Power mode 1 ... Leave Ultra Low Power mode | PASSED | PASSED
Press '4' | Configure button with debouncing ... Enter Idle mode | PASSED | PASSED
Press any key | Leave Idle mode | PASSED | PASSED

### VARIANT = SRAM

In the terminal window, the following text should appear (values depend on the
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

Tested with IAR and GCC, with the following process:

Step | Text received from terminal | Expected Result | Result
-----|-----------------------------|-----------------|-------
Press '0' | Will use clock setting for test: PCK = MCK = Crystal 12MHz | PASSED | PASSED
Press '0' | Will use clock setting for test: PCK = MCK = Crystal 12MHz/16 = 750k Hz | PASSED | PASSED
Press '0' | Will use clock setting for test: PCK = MCK = Crystal 12MHz/64 = 187.5k Hz | PASSED | PASSED
Press '0' | Will use clock setting for test: PCK = MCK = Crystal 32k Hz | PASSED | PASSED
Press '0' | Will use clock setting for test: PCK = MCK = Crystal 32k/64 = 512 Hz | PASSED | PASSED
Press '0' | Will use clock setting for test: PCK = MCK = RC 12MHz | PASSED | PASSED
Press '0' | Will use clock setting for test: PCK = 396, MCK = 132MHz | PASSED | PASSED
Press '0' | Will use clock setting for test: PCK = 498, MCK = 166MHz | PASSED | PASSED
Press '1' | Enter Backup mode | PASSED | PASSED
Press WAKE_UP |	RomBOOT | PASSED | PASSED
Press '2' | Enter Ultra Low Power mode 0 | PASSED | PASSED
Press USER_BTN | Leave Ultra Low Power mode | PASSED | PASSED
Press '3' | Enter Ultra Low Power mode 1 ... Leave Ultra Low Power mode | PASSED | PASSED
Press '4' | Configure button with debouncing ... Enter Idle mode | PASSED | PASSED
Press any key | Leave Idle mode | PASSED | PASSED
Press 'A' | Init DDR ... | PASSED | PASSED
Press 'B' | Write data into DDR ... end of init | PASSED | PASSED
Press 'C' | Verify data in DDR` ... `data OK | PASSED | PASSED
Press 'D' | Set DDR into self-refresh | PASSED | PASSED
Press 'E' | Out of DDR Self refresh state | PASSED | PASSED
Press 'D' | Set DDR into self-refresh | PASSED | PASSED
Press '3' | Enter Ultra Low Power mode 1 ... | PASSED | PASSED
Press `WAKE UP` | Leave Ultra Low Power mode | PASSED | PASSED
Press 'C' | Verify data in DDR ... data OK | PASSED | PASSED


# Note:
-------
 * Some DDR related operations are omitted while running out of DDR.
 * The battery should be mounted and 'Force Power UP' jumper should be opened to support the BackUp mode correctly.
 * There are two ULP modes for SAMA5D2 while only one ULP mode for SAMA5D4.
 * SAMA5D2-PTC-EK and SAMA5D27-SOM1-EK's clock source are 24MHz crystal oscillator,therefore, MCK=164Mhz, PLLA = 492 Mhz, Processor clock = 492 Mhz as default setup.
 * The JTAG connection is lost with ULP1 or BackUp mode.
 * The RTC is configured to work with 32.768kHz Crystal Oscillator isn't bypassed, so it can work on SAM9X60-EK REVA(back) and SAM9X60-EK REVB boards not SAM9X60-EK REVA(green).

 