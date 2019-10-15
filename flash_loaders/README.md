IAR Flash Loader
----------------

## Overview

A flash loader is an agent of **IAR Embedded Workbench** that is downloaded to
the target, it is needed when running examples out of "ddram" or "qspi".

## Directory Architecture

### flash_loaders/applets
  Source code for IAR flash loader

### flash_loaders/samxxx-generic
  Files for the flash loaders (.out, .mac, .board, .flash)

#### board-file
  The flash memory system specification file is an XML file (filename extension `board`) which describes for C-SPY the flash loading properties of the complete development board. This file can sometimes contain references to more than one flash memory (through the appropriate .flash), if the board has more than one type of flash memory that needs to be programmed separately in several passes. In this case, the .board also specifies specific address ranges of the image which belongs to different flash memories.

#### flash-file
  The flash memory configuration file is an XML file (filename extension `flash`) which describes for C-SPY all relevant
 properties of a certain flash memory. For example, the base address of the flash memory and details such as block and page
 sizes. The file also specifies which flash loader to use.

#### output-file
  Flash loader executable file with extension `.out` for various devices.
  
#### macro-file
  Specifies the path to a C-SPY macro file with extension `.mac`, which will be loaded in conjunction with downloading the flash loader. There are three C-SPY macro functions that will be called automatically if they are defined in this macro file.

## Boards support

|Flash | Device  | Board            | board-file             | flash-file
------ | ------- | ---------------- | ---------------------- | ---------------------------
|ddram | sam9xx5 | sam9xx5-ek       | sam9x25-generic.board  | sam9x25-generic_ddram.flash
|ddram | sam9x60 | sam9x60-ek       | sam9x60-ek.board       | sam9x60-generic_ddram.flash
|qspi  | sam9x60 | sam9x60-ek       | sam9x60-ek.board       | sam9x60-generic_qspi0.flash
|ddram | sama5d2 | sama5d2-xplained | sama5d2-xplained.board | sama5d2-generic_ddram.flash
|ddram | sama5d2 | sama5d2-ptc-ek   | sama5d2-ptc-ek.board   | sama5d2-generic_ddram.flash
|ddram | sama5d2 | sama5d27-som1-ek | sama5d27-som1-ek.board | sama5d2-generic_ddram.flash
|qspi0 | sama5d2 | sama5d2-xplained | sama5d2-xplained.board | sama5d2-generic_qspi0.flash
|qspi1 | sama5d2 | sama5d2-xplained | sama5d2-xplained.board | sama5d2-generic_qspi1.flash
|qspi0 | sama5d2 | sama5d2-ptc-ek   | sama5d2-ptc-ek.board   | sama5d2-generic_qspi0.flash
|qspi1 | sama5d2 | sama5d2-ptc-ek   | sama5d2-ptc-ek.board   | sama5d2-generic_qspi1.flash
|qspi0 | sama5d2 | sama5d27-som1-ek | sama5d27-som1-ek.board | sama5d2-generic_qspi0.flash
|qspi1 | sama5d2 | sama5d27-som1-ek | sama5d27-som1-ek.board | sama5d2-generic_qspi1.flash
|ddram | sama5d3 | sama5d3-xplained | sama5d3-xplained.board | sama5d3-generic_ddram.flash
|ddram | sama5d3 | sama5d3-ek       | sama5d3-ek.board       | sama5d3-generic_ddram.flash
|ddram | sama5d4 | sama5d4-xplained | sama5d4-xplained.board | sama5d4-generic_ddram.flash
|ddram | sama5d4 | sama5d4-ek       | sama5d4-ek.board       | sama5d4-generic_ddram.flash
|ddram | samv71  | samv71-xplained  | samv71-xplained.board  | samv71-generic_ddram.flash
|ddram | same70  | same70-xplained  | same70-xplained.board  | samv71-generic_ddram.flash


## DDRAM support

|Type | Device          | Preset ID* | bus width(bits)
------ | -------------- | ---------  | --------- 
|ddram | MT47H128M8     | 0          | 32
|ddram | MT47H64M16     | 1          | 16
|ddram | MT47H128M16    | 2          | 32
|ddram | MT42L128M16    | 3          | 32
|ddram | MT41K128M16    | 4          | 16
|ddram | EDF8164A3MA    | 5          | 32
|sdram | IS42S16100E    | 6          | 16
|sdram | W981216BH      | 7          | 16
|ddram | W971GG6SB      | 8          | 16
|ddram | W972GG6KB      | 9          | 32
|sdram | AS4C16M16SA    | 10         | 16
|ddram | W972GG6KB_16   | 11         | 16
|ddram | MT41K128M16_16 | 12         | 32
|ddram | AD220032D      | 13         | 32
|ddram | AD210032D      | 14         | 32
|ddram | W9712G6KB      | 15         | 32
|sdram | W9751G6KB      | 16         | 16
|ddram | MT47H64M16_X2  | 17         | 32

  Note: ``--preset`` is flash_loader argument in ddram/sdram flash_loader application to indicate which ddram/sdram device used in target board.

## Build

### Environment Variable

**TARGET**: Name of the target (sama5d2-generic for SAMA5D2 boards, sama5d3-generic for SAMA5D3 boards).

### IAR Project generation

An IAR project can be generated with GNU make, run in the applets directory (extram or qspiflash):

``make TARGET=target iar``

#### SAM9X25,SAM9GX25,SAM9X35,SAM9G35,SAM9G15 support
``make TARGET=sam9x25-generic iar``

#### SAM9X60 support
``make TARGET=sam9x60-generic iar``

#### SAMA5D2 support
``make TARGET=sama5d2-generic iar``

#### SAMA5D3 support
``make TARGET=sama5d3-generic iar``

#### SAMA5D4 support
``make TARGET=sama5d4-generic iar``

### Build the Flash Loader

Launch the project generated above, the flash loader would be copied automatically
 to flash_loaders/samxxx-generic/ after build.

Notice:
When CLASSD is used on sam9x60 the MCK need to be 196.608MHz, generate the project using:
``make TARGET=sam9x60-generic CONFIG_AUDIO=y iar``

## Setting up the Flash Loader(s) in EWARM IAR IDE
To use a flash loader for downloading your application:
1. Choose **Project>Options**.
2. Choose **Debugger** category and click the **Download** tab.
3. Select **Use Flash loader(s)** option. A default flash loader configured the device you have specified will be used. The configuration is specifed in preconfigured ``.board`` file.
4. To override the default flash loader or to modify the behavior of the default flash loader to suit your board, select the **Override default board-file** option, and **Edit** to open the **Flash loader Configuration** dialog box. A copy of the ``.board`` file will be created in your project directory and the path to the ``.board`` file will be updated accordingly.


