QSPI_XIP EXAMPLE
================

# Objectives
------------
This examples demonstrates how to setup the QSPI Flash in XIP mode to execute
code from QSPI flash.

# Example Description
---------------------
This example writes the getting-started example into flash via SPI and enables quad
mode spi to read code and to execute from it.

# Test
------

## Supported targets
--------------------
* SAMA5D2-XPLAINED
* SAMA5D27-SOM1-EK

## Setup
--------
On the computer, open and configure a terminal application
(e.g. HyperTerminal on Microsoft Windows) with these settings:
 - 115200 bauds
 - 8 bits of data
 - No parity
 - 1 stop bit
 - No flow control

This package can be used with SAMA5D2-XPLAINED with QSPI memory onboard.

## Start the application
------------------------

### First run

In the terminal window, the following text should appear (values depend on the
board and chip used):
```
-I- MMU enabled.
-I- D cache enabled.
-I- I cache enabled.
-- QSPI XIP Example xxx --
-- SAMxxxxxx-xx
-- Compiled: xxx xx xxxx xx:xx:xx --
-D- ../../drivers/power/act8945a.c:458 Charge Level: 450mA
-D- ../../examples/qspi_xip/main.c:198 Initializing QSPI drivers...
-D- ../../examples/qspi_xip/main.c:200 QSPI drivers initialized.
-D- ../../examples/qspi_xip/main.c:203 QSPI baudrate set to 41500000Hz
-D- ../../examples/qspi_xip/main.c:205 Configuring QSPI Flash...
-D- ../../drivers/memories/qspiflash.c:614 Trying protocol 0 opcode 0x9f
-D- ../../drivers/memories/qspiflash.c:629 Found memory with JEDEC ID 0x001a20c2.
-D- ../../drivers/memories/qspiflash.c:649 Found supported memory with JEDEC ID 0x001a20c2 (MX25L51245G).
-D- ../../drivers/memories/qspiflash.c:331 QSPI Flash: Macronix Quad mode already enabled
-D- ../../examples/qspi_xip/main.c:209 QSPI Flash configured.
-I- Data at the beginning of QSPI: ffffffff ffffffff ffffffff ffffffff
-I- No valid application found in QSPI, will one program first
Erasing 16x4KB at beginning of memory...
Erase done.
Writing to QSPI...
Example code written to memory (0x7ae0 bytes).
Verifying...
Everything is OK

 Running code from QSPI flash
=========================================================
-- Getting Started Example xxx --
(...)
```

### Subsequent runs

In the terminal window, the following text should appear (values depend on the
board and chip used):

```
-- QSPI XIP Example  xxx --
-- SAMxxxxx-xx
-- Compiled: xxx xx xxxx xx:xx:xx --
-D- ../../drivers/power/act8945a.c:458 Charge Level: 450mA
-D- ../../examples/qspi_xip/main.c:198 Initializing QSPI drivers...
-D- ../../examples/qspi_xip/main.c:200 QSPI drivers initialized.
-D- ../../examples/qspi_xip/main.c:203 QSPI baudrate set to 41500000Hz
-D- ../../examples/qspi_xip/main.c:205 Configuring QSPI Flash...
-D- ../../drivers/memories/qspiflash.c:614 Trying protocol 0 opcode 0x9f
-D- ../../drivers/memories/qspiflash.c:629 Found memory with JEDEC ID 0x001a20c2.
-D- ../../drivers/memories/qspiflash.c:649 Found supported memory with JEDEC ID 0x001a20c2 (MX25L51245G).
-D- ../../drivers/memories/qspiflash.c:331 QSPI Flash: Macronix Quad mode already enabled
-D- ../../examples/qspi_xip/main.c:209 QSPI Flash configured.
-I- Data at the beginning of QSPI: e59ff018 e59ff018 e59ff018 e59ff018
-I- Valid application already in QSPI, will run it using QSPI XIP
-I- Starting continuous read mode to enter in XIP mode
-- Getting Started Example xxx --
(...)
```

Tested with IAR and GCC (sram and ddram configuration)

In order to test this example, the process is the following:

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Erase QSPI | Erase the begining of the QSPI memory using SAM-BA or any other tool | N/A | N/A
First run | Execute the qspi_xip example, it should display a log similar to "First run" | PASSED | PASSED
Reset | Reset the board (to ensure the QSPI memory leaves the XIP mode) | N/A | N/A
Second run | Execute the qspi_xip example gain, it should display a log similar to "Subsequent runs" | PASSED | PASSED

