# Atmel SAMA5D2x Software Package

## Version 0.x -- ?

### New drivers

- MCAN driver + example

### Enhancements

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
