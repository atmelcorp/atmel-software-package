Atmel SAMA5 Software Package
----------------------------

# Code

The Atmel Softpack can be found on [GitHub](https://github.com/atmelcorp/atmel-software-package).

# Hardware Support

The Atmel Softpack support multiple devices and multiple targets.

## Devices

* SAM9xx5 family
* SAMA5D2x family
* SAMA5D3x family
* SAMA5D4x family

## Targets

* SAM9xx5 EVALUATION KIT (sam9g15-ek, sam9g25-ek, sam9g35-ek, sam9x25-ek, sam9x35-ek)
* SAMA5D2 XPLAINED ULTRA (sama5d2-xplained)
* SAMA5D3 XPLAINED ULTRA (sama5d3-xplained)
* SAMA5D3 EVALUATION KIT (sama5d3-ek)
* SAMA5D4 XPLAINED ULTRA (sama5d4-xplained)
* SAMA5D4 EVALUATION KIT (sama5d4-ek)

# Example List

This release contains the following examples:

* adc: Example using ADC 
* audio_recorder: Example to record sound
* can: Example using CAN
* classd: Example using Class-D Audio
* crypto_aes: AES hardware computation (with and without DMA)
* crypto_aesb: AESB hardware computation to read/write in DDRAM (with and without DMA)
* crypto_icm: ICM hardware computation to read/write in DDRAM (with and without DMA)
* crypto_qspi_aesb: AESB hardware computation to read/write in QSPI (with and without DMA)
* crypto_sha: SHA hardware computation (with and without DMA)
* crypto_tdes: Triple-DES hardware computation (with and without DMA)
* ddram: Example of DDRAM usage
* dma: Example of DMA usage with generic API
* dma_dmac: Example of DMAC usage
* dma_xdmac: Example of XDMAC usage
* getting_started: LED blink (uses PIT, TC and PIO)
* eth: GMAC/EMAC example using a simple IP stack
* eth_lwip: GMAC/EMAC example using LWIP stack
* eth_uip_helloworld: GMAC/EMAC example using UIP stack (UIP helloworld example)
* eth_uip_telnetd: GMAC/EMAC example using UIP stack (UIP telnetd example)
* eth_uip_webserver: GMAC/EMAC example using UIP stack (UIP webserver example)
* isi: Example using ISI controller
* isc: Example using ISC controller
* lcd: Example using LCD controller
* low_power_mode: Example of low power mode
* pdmic: Example using the FieldBus extension board to test PDMIC interface and Class-D
* pmc_clock_switching: Switch clock to low/high speed
* power_consumption_pll: Measure power consumption
* pwm: Example of PWM
* qspi_flash: Read/Write/Delete commands to a QSPI serial flash
* qspi_xip: Load a binary into QSPI memory and jump to it
* rtc: RTC Example
* sdmmc_sdcard: Example of Read/Write access from/to SD Cards, MMC Cards, e.MMC devices
* secumod: Example of Security Module
* smc_nandflash_mlc: Example of NAND Flash MLC
* smc_nandflash_slc: Example of NAND Flash SLC
* spi_serialflash: Read/Write/Delete commands to an SPI serial flash
* spi_slave: Set up the SAMA5D2 as a SPI slave
* ssc_dma_audio: Example of SSC to play sound
* tc_capture_waveform: Use TC in capture mode to measure pulse frequency of an external signal
* test-pio: Simple example to test PIO features
* timer: Example of time function usage
* trng: Example using hardware RNG (interrupt mode)
* twi_eeprom: Read/Write/Delete commands to an Two-Wire EEPROM
* usart: Example of communication over USART
* usart_irda: Example of communication over IrDA sensors (FieldBus extension board)
* usart_iso7816: Example of USART configured for ISO7816
* usart_lin: Example of USART configured for LIN
* usb_audio_looprec: Set up a SAMA5D2x as a USB Audio Device to record sounds
* usb_audio_speaker: Set up a SAMA5D2x as a USB Audio Speaker
* usb_cdc_serial: Example of Virtual COM Port
* usb_hid_aud: Example of USB Device Port (UDP) and Class-D for SAMA5D2x
* usb_hid_keyboard: Example of usb HID keyboard device
* usb_hid_mouse: Example of usb HID moude device
* usb_hid_msd: Example of usb composite device: HID device and usb mass storage
* usb_hid_transfer: Example of USB HID device
* usb_iad_cdc_aud: Example of usb composite device: virtual com port and usb class-d device
* usb_iad_cdc_cdc: Example of usb composite device: 2 virtual com ports
* usb_iad_cdc_hid: Example of usb composite device: virtual com port and usb mass storage device
* usb_iad_cdc_msd: Example of SAMA5D2x configured as a CDC USB Mass Storage device
* usb_mass_storage: Example of SAMA5D2x configured as a USB Mass Storage device
* usb_usv_isi: Example of SAMA5D4x configured as a USB Video Device
* usb_usv_isc: Example of SAMA5D2x configured as a USB Video Device
* wdt: Example using watchdog timer

# Compatibility

Examples               | sama5d2 xplained | sama5d3 xplained | sama5d3 ek | sama5d4 xplained | sama5d4 ek | sam9xx5 ek
---------------------- | ---------------- | ---------------- | ---------- | ---------------- | ---------- | ----------
adc                    | OK               | OK               | OK         | OK               | OK         | OK
audio_recorder         | OK               | x                | OK         | x                | OK         | OK
can                    | OK               | x                | x          | x                | x          | x
classd                 | OK               | x                | x          | x                | x          | x
crypto_aes             | OK               | OK               | OK         | OK               | OK         | x
crypto_aesb            | OK               | x                | x          | OK               | OK         | x
crypto_icm             | OK               | x                | x          | OK               | OK         | x
crypto_qspi_aesb       | OK               | x                | x          | x                | x          | x
crypto_sha             | OK               | OK               | OK         | OK               | OK         | x
crypto_tdes            | OK               | OK               | OK         | OK               | OK         | x
ddram                  | OK               | OK               | OK         | OK               | OK         | OK
dma                    | OK               | OK               | OK         | OK               | OK         | OK
dma_dmac               | x                | OK               | OK         | x                | x          | OK
dma_xdmac              | OK               | x                | x          | OK               | OK         | x
getting_started        | OK               | OK               | OK         | OK               | OK         | OK
eth                    | OK               | OK               | OK         | OK               | OK         | OK
eth_lwip               | OK               | OK               | OK         | OK               | OK         | OK
eth_uip_helloworld     | OK               | OK               | OK         | OK               | OK         | OK
eth_uip_telnetd        | OK               | OK               | OK         | OK               | OK         | OK
eth_uip_webserver      | OK               | OK               | OK         | OK               | OK         | OK
isc                    | OK               | x                | x          | x                | x          | x
isi                    | x                | OK               | OK         | OK               | OK         | x
lcd                    | OK               | OK               | OK         | OK               | OK         | OK
low_power_mode         | OK               | OK               | OK         | OK               | OK         | TODO
pdmic                  | OK               | x                | x          | x                | x          | x
pmc_clock_switching    | OK               | OK               | OK         | OK               | OK         | OK
power_consumption_pll  | OK               | OK               | OK         | OK               | OK         | OK
pwm                    | OK               | x                | OK         | OK               | OK         | OK
qspi_flash             | OK               | x                | x          | x                | x          | x
qspi_xip               | OK               | x                | x          | x                | x          | x
rtc                    | OK               | OK               | OK         | OK               | OK         | OK
sdmmc_sdcard           | OK               | OK               | OK         | OK               | OK         | OK
secumod                | OK               | x                | x          | OK               | OK         | x
smc_nandflash_mlc      | OK               | OK               | OK         | OK               | OK         | OK
smc_nandflash_slc      | OK               | OK               | OK         | OK               | OK         | OK
spi_serialflash        | OK               | OK               | OK         | OK               | OK         | OK
spi_slave              | BROKEN           | x                | TODO       | BROKEN           | BROKEN     | BROKEN
ssc_dma_audio          | TODO             | OK               | OK         | OK               | OK         | OK
tc_capture_waveform    | OK               | OK               | OK         | OK               | OK         | OK
test-pio               | OK               | OK               | TODO       | OK               | OK         | OK
timer                  | OK               | OK               | OK         | OK               | OK         | OK
trng                   | OK               | OK               | OK         | OK               | OK         | x
twi_eeprom             | OK               | TODO             | TODO       | OK               | OK         | OK
usart                  | OK               | OK               | TODO       | OK               | OK         | OK
usart_irda             | OK               | TODO             | TODO       | OK               | OK         | OK
usart_iso7816          | OK               | OK               | OK         | OK               | OK         | OK
usart_lin              | OK               | x                | x          | x                | x          | x
usb_audio_looprec      | OK               | OK               | OK         | OK               | OK         | TODO
usb_audio_speaker      | OK               | x                | OK         | x                | OK         | OK
usb_cdc_serial         | OK               | OK               | OK         | OK               | OK         | OK
usb_hid_aud            | OK               | x                | OK         | x                | OK         | OK
usb_hid_keyboard       | OK               | OK               | OK         | OK               | OK         | OK
usb_hid_mouse          | OK               | OK               | OK         | OK               | OK         | OK
usb_hid_msd            | OK               | OK               | OK         | OK               | OK         | OK
usb_hid_transfer       | OK               | OK               | OK         | OK               | OK         | OK
usb_iad_cdc_aud        | OK               | x                | OK         | x                | OK         | OK
usb_iad_cdc_cdc        | OK               | OK               | OK         | OK               | OK         | OK
usb_iad_cdc_hid        | OK               | OK               | OK         | OK               | OK         | OK
usb_iad_cdc_msd        | OK               | OK               | OK         | OK               | OK         | OK
usb_mass_storage       | OK               | OK               | OK         | OK               | OK         | OK
usb_usv_isc            | OK               | x                | x          | x                | x          | x
usb_usv_isi            | x                | x                | OK         | x                | OK         | OK
wdt                    | OK               | x                | x          | OK               | OK         | x

Legend:
  * "x" means "Not Applicable"
  * "OK" means "Supported"
  * "TODO" means "Hardware supports it but not yet implemented/validated"
