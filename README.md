Microchip Software Package
----------------------------

## Overview

This softpack comes as an early delivery and all presented APIs are subject to
change.

Each software module is provided with full source code, example of usage, and
ready-to-use projects.

This softpack is hosted on [GitHub](https://github.com/atmelcorp/atmel-software-package).

## Supported Platforms

Windows and Linux with the gnu **GCC ARM Embedded** toolchain. It is downloadable
at this address: [launchpad.net/gcc-arm-embedded](https://launchpad.net/gcc-arm-embedded)
(Mac OS X should also work but as not been tested yet).

Dependencies:
- GNU make (from MinGW, Cygwin or GnuWin32 for Windows architectures)
- bash (from MinGW, Cygwin for Windows architectures)
- *recommended on Windows architectures:* winpty (from MSYS2's package manager)

Windows with **IAR Embedded Workbench**.
Dependencies:
- IAR Embedded Workbench (Tested on version 7.80)
- bash (from MinGW, Cygwin or GnuWin32) for IAR project generation
- GNU make (from MinGW, Cygwin or GnuWin32) for IAR project generation
- mktemp (from MinGW, Cygwin or GnuWin32) for IAR project generation

## Contents

### Directory Architecture

- **target/_xxx_**
  All chip and board specific source files for _xxx_ devices

- **target/_xxx_/toolchain/**
  Linker and debugger scripts for _xxx_ devices

- **scripts/**
  generators and build script templates (Makefiles)

- **arch/**
  CPU Core driver source files

- **drivers/**
  Driver source files

- **examples/**
  All examples

- **samba_applets/**
  Source code for SAM-BA 3.x applets

- **flash_loader/**
  Source code for IAR flash loader

### Examples

The examples are listed in [softpack.md](softpack.md).

## Usage (GCC ARM Embedded)

### Environment Variable

**TARGET**: Name of the target (sama5d2-xplained for SAMA5D2 XPLAINED ULTRA
boards).

**VARIANT**: Build variant, for example "sram","ddram" or "qspi".

**DEBUG**: Build with debug flags (default).

**TRACE_LEVEL**: Log level, 5 correspond to full, 0 to none (default to 5)

**RELEASE**: Build for release, otherwise build for debug.

**V=1**: Verbose build

All these variables are optional except for TARGET that must be provided or set
at each make invocation.

### Build

Run:

``make TARGET=target``

### Run and Debug (with GDB)

To run examples with gdb, JLinkGDBServer must be started. It can be downloaded
for each platform at  [www.segger.com](http://www.segger.com)

A make target is provided to launch the test with the correct gdb command
arguments, run:

``make TARGET=target debug``

## Usage (IAR)

The Win version of this softpack release comes with pregenerated IAR projects
compatible with IAR Systems Embedded Workbench for ARM version 7.80.

The C-SPY device description files and device selections files are not included
and must be installed manually.

### IAR Project generation

An IAR project can be generated with GNU make, run in the example directory:

``make TARGET=target iar``

All needed IAR project files will be put in the example directory, including a
default workspace one. Each IAR project is configured to **JLINK** as default debugger
driver, as for other setting, you can set up in IAR IDE to suit your connection such as
cmsis-dap driver. IAR flash loader is an agent that is downloaded to the target, more
flash loaders are provided in this software package, each build variant, for example
"sram","ddram", "flash" or "qspi", have it's dedicated flash loader.

Notice:
GNU make may fail on Windows platforms if the Makefile contains UNIX line endings.
You can use unix2dos on all Makefile files in scripts/ directory to fix this issue.

Please visit [README for FreeRTOS](lib/freertos/README.md) to use examples/freertos_*.