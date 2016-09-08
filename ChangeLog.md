# Atmel SAMA5 Software Package

## Version 2.5 - 2016-09

### New drivers/examples

- Added support for Microchip SST26 memories
- Added support for DM9161AEP ethernet PHY
- Added driver for wm8731 audio codec

### Enhancements

- Improved support for sam9xx5 targets in most drivers and examples
- Added IAR support for sam9xx5-ek targets
- Major SPI driver rework: better support for DMA/ASYNC modes and FIFOs.
- Added a new SPI Bus API
- Major USART driver rework: support for FIFOs, ASYNC mode and full-duplex.
- Added interrupt support for HSMCI and SDMMC drivers
- Major AT24 driver rework: driver now supports all AT24 variants
- SAM-BA applets now use DMA where possible (SDMMC, NAND, QSPI/SPI Flash)

### Fixes

- Fixed issue with linker files that caused oversized binaries
- Fixed issue that was causing non-bootable QSPI XIP binaries
- Fixed automatic selection of ECC correctability value based on ONFI tables in SAM-BA NAND applet



## Version 2.4 - 2016-08

### New drivers/examples

- Added initial support for SAM9 5 series chips (SAM9G15, SAM9G25, SAM9G35,
  SAM9X25 and SAM9X35.)  The chip family is called "sam9xx5" in the softpack
  and the targets are "sam9g15-ek", "sam9g25-ek", "sam9g35-ek", "sam9x25-ek"
  and "sam9x35-ek".  Supported examples include: getting-started,
  smc_nandflash_mlc, smc_nandflash_slc and test-pio.
- Added SAM-BA applet support for SAM9 5 series chips (SPI serialflash, NAND).

### Changes

- Remove untested QT1070 driver for now. Will be added again later with proper
  validation.
- TWI driver interface changed to correctly support all modes
  (polling/interrupt/dma, with/without FIFOs.)  Also added scatter-gather to
  TWI API.
- HSMC driver split into several smaller drivers for each peripheral part (SMC,
  NFC, PMECC, PMERRLOC)

### Enhancements

- Add DMA support to QSPI driver
- Enable caching of QSPI region when running in XIP mode
- Removed all use of board-specific constants from drivers
- Several clean-ups in drivers using TWI
- HSMCI support on SAMA5D3
- NAND Flash examples validated for SAMA5D3
- Added support for N25Q512A


## Version 2.3.1 - 2016-07

### Fixes

- Fix build of generic targets (used for SAM-BA applets)


## Version 2.3 - 2016-07

### New drivers/examples

- New EMAC driver for SAMA5D3
- New ETH driver to support both EMAC and GMAC driver
- New DMA driver which provides a generic DMA API to handle XDMAC and DMAC
- New IS31FL3728 LED driver (ATQT6 XPRO SURFACE extension board)

### Changes

- Rename AIC driver from iac.c to aic5.c
- Rename usart_xdma to usart_dma
- Port drivers to use the newly generic DMA API

### Enhancements

- Improve uvc_driver, usb_uvc_isi, and usb_uvc_isc example to support multiple
  buffering
- Add ISI support for SAMA5D3
- Add LCD support for SAMA5D3
- Add support for MT47H64M16 DDR2 DDRAM
- Reworked DDRAM driver to prepare for inclusion of older SAM devices and use
  TC instead of PIT for initialization delays
- Improve L2CC driver and cache maintainance operation
- Add Ultra High Speed mode to SDMMC driver
- Add support for SAMA5D3 for several examples
- Implemented AE/AWB for ISC example
- Fix PWM issues with fault mode
- Update QSPI driver to handle >16MB memories without switching to 4-byte
  addressing mode

### Fixes

- Fixes in PWM driver and example
- Fixes in mutex implementation
- Fix SSC0 pin definition for SAMA5D4
- Fix MMU configuration for QSPI
- Several fixes for audio device driver and examples
- Fixed mutex use in TWID and SPID drivers
- Fix NANDFlash examples for SAMA5D4-EK
- Fix VGA subsample for OV2643


## Version 2.2 - 2016-06

### New drivers/examples

- New HSMCI driver for SAMA5D4.
- New audio_recorder example.
- Add QSPI XIP IAR flashloader for sama5d2-xplained board.
- Initial support for SAMA5D3 SOC family in the softpack (DMA is not yet supported.)
- Add DMAC driver for SAMA5D3
- Add DMAC example to demonstrte the DMAC features

### Changes

- Introduce board_init() function called at startup before main() to initialize the
  board. It simplifies the examples a lot and allow common initialization for each board.
- Rename the XDMA configuration fields to match the datasheet names.
- Add new section in SRAM and DDRAM to hold only aligned variable on cache line size.
  It allows to use cache maintance functions over those variables without risking to flush/clean
  variables located in the same cache line.

### Enhancements

- Add support for views view0, view2 and view3 in the XDMA example.
- Improve audio_device driver to support also record feature over PDMIC, and SSC.
- sdmmc_sdcard is fully supported for the SAMA5D4 SOC family.
- Add volume control in audio examples.
- SAM-BA applets can now compile with IAR.
- Improve the libsdmmc.
- Caching is enabled on the QSPI memory region.
- Rework clock API and PCK clocks

### Fixes

- Fix a bug in pmc_configure_gck that was causing initialization problems on
  some boards.
- Fix cache alignement issues all over the examples.
- Fix a bug in USB Device Unhalt function.
- Fix PIO3 bugs.
- Fix ADC example to also work with TC trigger and ADTRG.
- Fix NAND ECC configuration.
- Fix image sensor OV9740 VGA configuration.



## Version 2.1 - 2016-05

### New drivers/examples

- New QSPI AESB example
- New USB UVC driver and example (for ISI and ISC) available for SAMA5D2 and SAMA5D4
- Function board_cfg_pmic was introduced to handle PMIC configuration

### Changes

- Function prototype for board_cfg_console was changed to allow custom
  baudrate.  Passing 0 as baudrate parameter selects default baudrate for the
  board.
- Introduction of audio device API to use SSC or CLASSD device to play sounds

### Enhancements

- Function board_cfg_pmic has been added to remove board specific PMIC configuration
  from examples main.c
- Add support of AESB address space in QSPI driver
- Decrease build time by modularization of peripherals

### Fixes

- Multiple fixes to remove dead assignements, dead increments, and possible
  null pointer dereferences
- Fix Audio PLL configuration
- Fix configuration errors for ISI image sensors
- Fix buffer alignment errors



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
