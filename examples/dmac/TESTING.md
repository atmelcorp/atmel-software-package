DMAC EXAMPLE
============

# Objectives
------------
This example aims to help new users get familiar with DMAC peripherial.

# Example Description
---------------------
This basic example evaluates the DMAC data transfer. The available types of
DMAC multiple buffers transfer can be switched by the corresponding options.

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

## Start the application (SAMA5D3-EK,SAMA5D3-XPLAINED)
-------------------------------------------

Menu :
------
- 1-9, A, B: Programming DMAC for Multiple Buffer Transfers
    1: Single Buffer or Last buffer of a multiple buffer transfer
    2: Multi Buffer transfer with contiguous DADDR
    3: Multi Buffer transfer with contiguous SADDR
    4: Multi Buffer transfer with LLI support
    5: Multi Buffer transfer with DADDR reloaded
    6: Multi Buffer transfer with SADDR reloaded
    7: Multi Buffer transfer with BTSIZE reloaded and contiguous DADDR
    8: Multi Buffer transfer with BTSIZE reloaded and contiguous SADDR
    9: Automatic mode channel is stalling BTsize is reloaded
    A: Automatic mode BTSIZE, SADDR and DADDR reloaded
    B: Automatic mode BTSIZE, SADDR reloaded and DADDR contiguous
- h: Display this menu

In order to test this example, the process is the following:

Tested with IAR and GCC (sram configration)

Step | Description | Expected Result | Result
-----|-------------|-----------------|-------
Press '1', | Single Buffer or Last buffer of a multiple buffer transfer | PASSED | PASSED
Press '2', | Multi Buffer transfer with contiguous DADDR | PASSED | PASSED
Press '3', | Multi Buffer transfer with contiguous SADDR | PASSED | PASSED
Press '4', | Multi Buffer transfer with LLI support | PASSED | PASSED
Press '5', | Multi Buffer transfer with DADDR reloaded | PASSED | PASSED
Press '6', | Multi Buffer transfer with SADDR reloaded | PASSED | PASSED
Press '7', | Multi Buffer transfer with BTSIZE reloaded and contiguous DADDR | PASSED | PASSED
Press '8', | Multi Buffer transfer with BTSIZE reloaded and contiguous SADDR | PASSED | PASSED
Press '9', | Automatic mode channel is stalling BTsize is reloaded | PASSED | PASSED
Press 'A', | Automatic mode BTSIZE, SADDR and DADDR reloaded | PASSED | PASSED
Press 'B', | Automatic mode BTSIZE, SADDR reloaded and DADDR contiguous | PASSED | PASSED
