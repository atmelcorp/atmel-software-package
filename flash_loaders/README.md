IAR Flash Loader
----------------

## Overview

A flash loader is an agent of **IAR Embedded Workbench** that is downloaded to
the target, it is needed when running examples out of "ddram" or "qspi".

## Directory Architecture

- **flash_loaders/applets/**
  Source code for IAR flash loader

- **flash_loaders/samxxx-generic**
  files for the flash loaders (.out, .mac, .board, .flash files)

## Build

### Environment Variable

**TARGET**: Name of the target (sama5d2-generic for SAMA5D2 boards, sama5d3-generic for SAMA5D3 boards).

### IAR Project generation

An IAR project can be generated with GNU make, run in the applets directory (extram or qspiflash):

``make TARGET=target iar``

### Build the Flash Loader

Launch the project generated above, the flash loader would be copied automatically
 to flash_loaders/samxxx-generic/ after build.

Notice:
When CLASSD is used on sam9x60 the MCK need to be 196.608MHz, generate the project using:
``make TARGET=sam9x60-generic CONFIG_AUDIO=y iar``
