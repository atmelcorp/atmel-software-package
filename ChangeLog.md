# Atmel Software Package

The Atmel Softpack can be found on [GitHub](https://github.com/atmelcorp/atmel-software-package).

## Version 2.11 - 2017-11

### New drivers/examples

- Add SDRAM support for SAM9XX5.
- Add example "secumod", "low_power_mode" for SAMA5D27 SOM1 EK board.
- Add more ethernet examples and audio examples for SAME70 XPLAINED and SAMV71 XPLAINED.

### Fixes

- Fix misplaced buffer allocation for example "adc".
- Fix PIO schmitt settings for SAM9XX5, SAMA5D3, SAMA5D4 and SAMV71.
- Fix the sector number for QSPI flash m25p05, m25p10.
- Fix qspi_xip example for SAMA5D27 SOM1 EK board.

### Enhancements

- Fully configurate the matrix for SAMA5D2 and SAMA5D4.
- Align the memory allocation for target "DDRAM" for SAMV71 examples.


## Version 2.10 - 2017-10

### Fixes

- Fix build issues with new SPI-NOR driver on IAR.
- Disable SFDP on SST26 memories (non-uniform erase map is not yet supported.)
- Fix SPI-NOR driver to return an error code when no memory is detected.
- Fix build issue with generic targets when the device has QSPI.
- Enable interrupts for all GMAC queues.
- Several fixes to high level ADC driver (adcd) and ADC example.
- Fix NAND issue: 8-bit bus width was broken
- Fix NAND applet displaying invalid warning about ECC requirements


## Version 2.9 - 2017-09

### New drivers/examples

- Add support for SAMA5D27 SOM1 EK board (examples listed in softpack.md).
- Add more drivers/examples for SAME70 XPLAINED, SAMV71 XPLAINED boards.
- Add support for SST26VF032B, S25FL064P QSPI flash memory.
- Add USBHS support for USB examples of Cortex-M7 MCUs.
- Add support for newer QSPI peripheral.
- Add SFDP for serial flash memories.

### Enhancements

- Enhance support for at24 series memories by adjusting the timings.
- Improve the DDR settings for higher performance.
- Re-factor drivers for CAN/MCAN.
- Improve the video stream for USB video devices.
- Add write-protection support for SD/MMC.
- Update the pin definitions for FLEXCOM.
- Rework the drivers for NAND flash memories.
- Upgrade the applets for SAM-BA.
- Update USB drivers/examples for compliance tests in USB20CV.
- Update the flash loaders.
- Update drivers for SPI NOR flash memories.

### Fixes

- Fix TDES transfers in DMA mode.
- Fix timings for DDRAM.
- Fix RTC assert conditions.
- Fix the IRQ for Cortex-M7 MCUs while running examples in DDRAM using GCC.
- Fix DMA unstable issue caused by the loop field in the configuration not
  initialized before be used.
- Fix bootstrap halt issue while running examples in DDRAM using GCC.
- Fix SAM-BA applets support for >4G eMMC.


## Version 2.8 - 2017-01

### New drivers/examples

- Add preliminary support for SAME70/S70/V70/V71 Cortex-M7 MCUs: support for
  running from SRAM and flash, few drivers and examples supported (see
  softpack.md).
- Add generic API for IRQ handling. All drivers updated to use this new API.
- Add generic DMA API: simplification and scatter-gather management. All
  drivers updated to use this new API.
- Add support for IS42S16100E SDRAM.
- Add common bus API covering SPI and I2C.
- Add high-level TC driver (supports counter, waveform and capture). All
  examples and drivers updated to use this new API.

### Enhancements

- Fixed system time counting. Less interrupts triggered now and micro-second
  precision.
- Reorganized source files in drivers/ directory.
- Changed build output directory: now ./build/<target>/<variant>.
- IAR entry point is now configurable from Makefiles.
- Rename CONFIG_SOC_xxx to CONFIG_CHIP for actual device name.
- Move CPU core drivers to a new arch/ directory.
- Group common code from target/<target>/board_support to target/common:
  CLASSD, ISC, ISI, LCD, PDMIC, QSPI, SSC, timer.
- Group common chip code to target/common/chip_common.{c,h}:
  get_xxx_addr_from_id and get_xxx_id_from_addr functions.
- Reworked l1/l2 cache API.
- Upgrade LWIP to 2.0.0. Add HTTP and iperf server examples.
- Audio device driver now handles DMA setup.
- Reuse allocated DMA channels in all drivers instead of reallocating them on
  each transfer.
- Change several drivers to return errno values.
- Improve SHA driver and implement message padding
- Renamed several peripherals: PWM to PWM0, CLASSD to CLASSD0, PDMIC to PDMIC0,
  TWIHSx to TWIx.
- Renamed Flexcom devices: now FLEXUSARTx, FLEXTWIx and FLEXSPIx.
- Merge SAMA5D2 headers: now single header for all SAMA5D2x devices.
- Handle variation between SAMA5D3 devices.

### Fixes

- Fix ClassD stereo playing in polling mode.
- Fix AES CFB transfer size.
- Add support for missing group E to PIO3 driver.
- Fix xdmac_enable_channels/xdmac_disable_channels to support more than 8
  channels.
- Fix inversion of slow clock frequency between internal RC and external
  crystal.


## Version 2.7 - 2016-12

### New drivers/examples

- Added IRQ abstraction (irq/irq.h) with support for interrupt sharing.
- Added CAN bus abstraction, with support for both MCAN (SAMA5D2) and
  CAN (SAM9XX5, SAMA5D3).
- Added QT1070 driver
- Added adcd driver: handle configuration and DMA transfer on its own
- Added iscd driver: handle configuration and DMA transfer on its own
- Added isid driver: handle configuration and DMA transfer on its own

### Enhancements

- Some board initialization was made common between all targets (SPI, TWI, ISI,
  Ethernet).
- Reworked directory hierarchy for drivers (work in progress, this effort will
  continue on the next release).
- Compilation of several drivers is now conditional. This improves the build
  time for building programs that do not use all drivers.
- Improved pmc_configure_peripheral function. GCK and peripheral divisor can
  now be configured in a single call.
- Added support for KSZ9021 and KSZ9031 PHY.
- Added support for UTC mode and Persian calendar to RTC driver
- Removed direct TC usingthe DDRAM initialization, use new functions from timer
  driver instead.
- Added utils/errno.h with POSIX error codes. Used in QSPI and AT25 drivers,
  will be used in more drivers in later releases.
- SAMA5D3-EK support updated to support boards revision D or later. Older
  revisions are not supported anymore.

### Fixes

- Fixed pin definitions for GMAC MII and RMII modes on SAMA5D3
- Reduced default stack size in linker scripts to 1KB
- Fixed twi_eeprom example to have a working slave implementation on all
  targets.
- Fixed internal RC / external oscillator clock frequency inversion in PMC


## Version 2.6.1 - 2016-11

### Fixes

- Fixed an issue with timer on SAMA5D2. Timer would run too fast on cold reset.


## Version 2.6 - 2016-11

### New drivers/examples

- Added shad driver: handle configuration and DMA transfer on its own
- Added tdesd driver: handle configuration and DMA transfer on its own
- Added aesd driver: handle configuration and DMA transfer on its own
- Added AD1934 driver and audio_device support
- Added usb_audio_multi_channels example
- Added usart_rs485 example

### Enhancements

- Use a TC instead of the PIT (fix sdmmc reuse of timer to get precise timing)
- Add sleep(), mlseep(), usleep(): use the default system time counter
- Video sensor auto-detection
- Rework DMA examples to behave the same
- DMA driver handles linked list dynamically using a static pool of elements
- Reworked component headers for all supported devices to ease comparison

### Fixes

- Fixed an hardware bug in the protect mode of the AIC/SAIC
- Renamed variables named 'protected'
- Fix the spi_slave broken after the development of spi-bus


## Version 2.5.1 - 2016-09

### Enhancements

- Improved twi_eeprom example to include a slave device emulating an AT24C02.

### Fixes

- Fixed build issue for the following examples: usart_irda, usb_mass_storage,
  xdmac
- Fixed issue with ISC drivers resetting ISC_CFA_CTRL instead of ISC_CC_CTRL in
  function isc_cc_enabled.
- Fixed timeout handling in USART driver
- Rebuilt getting-started binary included in qspi_xip example
- Disable build of eth_lwip and eth_uip examples for SRAM variant, they do not
  fit anymore



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
