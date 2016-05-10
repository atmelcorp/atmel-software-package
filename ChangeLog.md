# Atmel SAMA5D2x Software Package

## Version ?.? - 2016-??

### New drivers/examples

- New QSPI AESB example

### Changes

- Function prototype for board_cfg_console was changed to allow custom
  baudrate.  Passing 0 as baudrate parameter selects default baudrate for the
  board.
- Introduction of audio device API to use SSC or CLASSD device to play sounds

### Enhancements

- Function board_cfg_pmic has been added to remove board specific PMIC configuration
  from examples main.c
- Add support of AESB address space in QSPI driver

### Fixes

- Multiple fixes to remove dead assignements, dead increments, and possible
  null pointer dereferences



## Version 2.0 - 2016-04

### New drivers/examples

- New SECUMOD driver and example for SAMA5D4

### Changes

- Baudrate of console on SAMA5D2 is now 115200 (previously was 57600)
- MMU, I-Cache and D-Cache are now enabled by default in low level init
- DDRAM variant now generates bootable binaries (to be loaded by at91bootstrap)

### Enhancements

- new SoC support: SAMA5D4 is now supported by the softpack
- New generic targets (sama5dX-generic) to build SAM-BA applets
- Examples prepared to support more architectures
- Unified interface for TWI driver between SAMA5D2 and SAMA5D4 and
  removed twi_legacy driver
- Improve independance from example to the direct use of SoC features
- New qspi0 and qspi1 variants to generate XIP-bootable binaries on QSPI
- IAR project files now include all variants which can build/run on a target
- Board support for SDMMC improved

### Fixes

- Multiple fixes inside ADC example
- Fixes in XDMAC driver
- Fixes in USB Mass Storage stack
- Multiple fixes in ISI example
- Fixes in PMC driver
- Fixes in SHDWC drivers



## Version 1.3 - 2016-04

### New drivers/examples

- new TC Capture Waveform example
- new DDR memory tester example
- new SPI slave example
- new driver for SFC (Secure Fuse Controller)
- added definitions for SECUMOD and boot configuration registers
- new IrDA example using FLEXCOM USART
- new Security Module (SECUMOD) driver and example
- new PDMIC driver and example
- new USB examples: composite, hid, audio
- new QSPI XIP example

### Changes

- the console helper (misc/console.h) is no longer initialized automatically on
  first use.  The new board-specific function board_cfg_console must be called
  explicitely before any console use (including printf/traces)
- NAND API changed to be easier to use
- SAM-BA applet API has changed (most parameters are now expressed in pages
  instead of bytes, to support bigger memories). The new API is not compatible
  with SAM-BA <= 3.0
- AT25 and QSPIFLASH drivers now share a common device database.
- Functions at25_erase_block and qspiflash_erase_block now take the erase block
  size as parameter.

### Enhancements

- Support for LPDDR2 (MT42L128M16) and LPDDR3 (EDF8164A3MA)
- Several functions added to TC driver
- Several functions added to PWM driver, existing example updated to make use
  of these new features
- Console helper can now be configured at runtime (serial peripheral, baudrate,
  pins)
- TWI eeprom example now contains a 'TWI slave' example emulating a AT24 eeprom

### Fixes

- several NAND bugfixes
- GCC linker scripts: fixed stacks/heap handling
- fixed cp15_is_dcache_enabled function
- L2CC driver now configures the L2 SRAM before enabling the cache
- several fixes to QSPIFLASH driver related to Quad-mode activation (Micron,
  Macronix, Spansion).
- fixed QSPI MMU mapping and enabled MMU and caches in QSPI example



## Version 1.2 - 2015-12

### New drivers/examples

- USB Device examples and stack: CDC Serial, HID Keyboard, HID Mouse, Audio,
  Mass Storage and some composite examples.
- NAND flash driver and examples: supports MLC/SLC, up to 32-bit ECC.
- SDMMC/eMMC driver and example
- Low Power examples: power_consumption_pll, pmc_clock_switching,
  low_power_mode
- New storagemedia library to abstract storage devices (only supports RAM disk
  for now, but will support SDMMC/eMMC and NAND flash in later releases)

### Enhancements

- Several new functions in PMC driver, notably 'pmc_set_custom_pck_mck' that
  allow changing easily the main clock settings.
- IAR project generator now uses defines and include directories from
  CFLAGS_DEFS and CFLAGS_INC mkefile variables. It also generates projects with
  CMSIS-DAP debugger selected and proper optimization level.

### Fixes

- Fix CP15 driver to invalidate caches before enable. This fixes some lock-ups
  when caches were previously enabled and still contain stale data.



## Version 1.1 - 2015-10

### New drivers

- Class-D audio driver + example

### Enhancements

- Support for ISO7816 and LIN modes to UART driver + example
- Several functions added to PMC driver, mostly UPLL and AudioPLL support
- ISC/sensors: support for new capture modes / resolutions

### Fixes

- Several fixes to ADC driver and example
- Fixed MMU setup (some memory regions where not defined)



## Version 1.0 - 2015-09

### New drivers

- MCAN driver + example

### Changes

- sama5d2-xplained target adapted for final revA board

### Enhancements

- Clock initialization changed to be more reliable
- PMC driver now supports setting generated clocks on sama5d2
- Add support for new memory models to at25 driver (MX25L12835F, MX25L4005,
  N25Q032, S25FL127S)



## Version 0.3 -- 2015-08

### New drivers

- ACC driver
- ADC driver + example
- AES / TDES / SHA drivers + examples
- L2CC driver
- GMAC driver + examples (using ad-hoc / LWIP / UIP stacks)
- QT1070 driver
- SHDWC driver

### Enhancements

- FPU is now enabled in GCC startup (was already enabled for IAR)
- ISC example now demonstrates Auto White Balance / Auto Exposure
- SPID/TWID/USARTD drivers now switch the Flexcom mode when appropriate
- MMU is now has a non-cacheable DDR region (used by LCD and GMAC examples)

### Fixes

- RAM timings / configuration adjusted for sama5d2-xplained target
- Component headers in target/sama5d2/components updated to reflect latest
  datasheet updates
- PIO and TRNG callbacks now have a configurable user-defined argument
