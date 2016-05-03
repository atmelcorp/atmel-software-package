Atmel SAMA5D2x/SAMA5D4x Software Package
----------------------------------------

# Overview

This softpack comes as an early delivery and all presented APIs are subject to
change.

Each software module is provided with full source code, example of usage, and
ready-to-use projects.

This softpack is hosted on GitHub:
https://github.com/atmelcorp/atmel-software-package

## Supported Platforms

Windows and Linux with the gnu GCC ARM Embedded toolchain. It is downloadable
at this address: https://launchpad.net/gcc-arm-embedded (Mac OS X should also
work but as not been tested yet).
Dependencies:
- GNU make (from MinGW, Cygwin or GnuWin32 for Windows architectures)
- bash (from MinGW, Cygwin for Windows architectures)

Windows with IAR Embedded Workbench.
Dependencies:
- IAR Embedded Workbench (Tested on version 7.40)
- bash (from MinGW, Cygwin or GnuWin32) for IAR project generation
- GNU make (from MinGW, Cygwin or GnuWin32) for IAR project generation
- mktemp (from MinGW, Cygwin or GnuWin32) for IAR project generation

# Contents

## Directory Architecture

- target/sama5d2
  All sama5d2 chip and board specific source files

- target/sama5d2/toolchain/
  Linker and debugger scripts for sama5d2

- target/sama5d4
  All sama5d4 chip and board specific source files

- target/sama5d4/toolchain/
  Linker and debugger scripts for sama5d4

- scripts/
  generators and build script templates (Makefiles)

- drivers/
  Driver source files

- examples/
  All examples

- samba_applets/
  Source code for SAM-BA 3.x applets

## Examples

# List of examples

The examples are listed in [SAMA5D2 README](examples/README.SAMA5D2.md) and
[SAMA5D4 README](examples/README.SAMA5D4.md).

# Usage (GCC ARM Embedded)

## Environment Variable

TARGET: Name of the wanted target (sama5d2-xplained for SAMA5D2 XPLAINED ULTRA
boards). This variable is always mandatory.

DEBUG: Build with debug flags (default).

TRACE_LEVEL: The wanted log level, 5 correspond to full, 0 to none (default to 5)

RELEASE: Build with the release flags

only TARGET must be provided or set at each make invocation.

## Build

Run:

``make``

or if TARGET is not set:

``make TARGET=wanted_target``

## Run and Debug (with GDB)

To run examples with gdb, JLinkGDBServer must be started. It can be downloaded
for each platform at http://www.segger.com

A make target is provided to launch the test with the correct gdb command
arguments, run:

``make debug``

or if TARGET is not set:

``make TARGET=wanted_target debug``

# Usage (IAR)

The Win version of this softpack release comes with pregenerated IAR projects
compatible with IAR Systems Embedded Workbench for ARM version 7.40.

The C-SPY device description files and device selections files are not included
and must be installed manually.

## IAR Project generation

An IAR project can be generated with GNU make, run in the example directory:

``make iar``

or if TARGET is not set:

``make TARGET=wanted_target iar``

All needed IAR project files will be put in the example directory, including a
default workspace one.

Notice:
GNU make may fail on Windows platforms if the Makefile contains UNIX line endings.
You can use unix2dos on all Makefile files in scripts/ directory to fix this issue.
