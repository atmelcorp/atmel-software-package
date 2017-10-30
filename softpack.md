Atmel Software Package
----------------------

# Code

The Atmel Softpack can be found on [GitHub](https://github.com/atmelcorp/atmel-software-package).

# Hardware Support

The Atmel Softpack support multiple devices and multiple targets.

## Devices

* SAM9xx5 family (SAM9G15, SAM9G25, SAM9G35, SAM9X25, SAM9X35)
* SAMA5D2 family (SAMA5D21, SAMA5D22, SAMA5D23, SAMA5D24, SAMA5D26, SAMA5D27, SAMA5D28)
* SAMA5D3 family (SAMA5D31, SAMA5D33, SAMA5D34, SAMA5D35, SAMA5D36)
* SAMA5D4 family (SAMA5D41, SAMA5D42, SAMA5D43, SAMA5D44)
* SAMV71 family (SAME70, SAMS70, SAMV70, SAMV71)

## Targets

* SAM9xx5 EVALUATION KIT (sam9g15-ek, sam9g25-ek, sam9g35-ek, sam9x25-ek, sam9x35-ek)
* SAMA5D2 XPLAINED ULTRA (sama5d2-xplained)
* SAMA5D27 SOM1 EK (sama5d27-som1-ek)
* SAMA5D3 XPLAINED (sama5d3-xplained)
* SAMA5D3 EVALUATION KIT (sama5d3-ek)
* SAMA5D4 XPLAINED ULTRA (sama5d4-xplained)
* SAMA5D4 EVALUATION KIT (sama5d4-ek)
* SAME70 XPLAINED (same70-xplained)
* SAMV71 XPLAINED ULTRA (samv71-xplained)

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
* crypto_trng: Example using hardware RNG (interrupt mode)
* ddram: Example of DDRAM usage
* dma: Example of DMA usage with generic API
* getting_started: LED blink (uses PIT, TC and PIO)
* eefc: Internal Flash Example
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
* spi_slave: Set up an SPI slave
* ssc_dma_audio: Example of SSC to play sound
* tc: Use TC driver
* test-pio: Simple example to test PIO features
* timer: Example of time function usage
* twi_eeprom: Read/Write/Delete commands to an Two-Wire EEPROM
* usart: Example of communication over USART
* usart_irda: Example of communication over IrDA sensors (FieldBus extension board)
* usart_iso7816: Example of USART configured for ISO7816
* usart_lin: Example of USART configured for LIN
* usart_rs485: Example of RS485 transfer
* usb_audio_looprec: Set up a USB Audio Device to record sounds
* usb_audio_multi_channels: Set up a mutichannel USB Audio Device
* usb_audio_speaker: Set up a USB Audio Speaker
* usb_cdc_serial: Example of Virtual COM Port
* usb_hid_aud: Example of USB Device Port (UDP) and Class-D for SAMA5D2x
* usb_hid_keyboard: Example of USB HID keyboard device
* usb_hid_mouse: Example of USB HID moude device
* usb_hid_msd: Example of USB composite device: HID device and usb mass storage
* usb_hid_transfer: Example of USB HID device
* usb_iad_cdc_aud: Example of USB composite device: virtual com port and usb class-d device
* usb_iad_cdc_cdc: Example of USB composite device: 2 virtual com ports
* usb_iad_cdc_hid: Example of USB composite device: virtual com port and usb mass storage device
* usb_iad_cdc_msd: Example of a CDC USB Mass Storage device
* usb_mass_storage: Example of a USB Mass Storage device
* usb_uvc_isi: Example of a USB Video Device
* usb_uvc_isc: Example of a USB Video Device
* wdt: Example using watchdog timer

# Compatibility

Examples               | sama5d2 xplained | sama5d27 som1 ek | sama5d3 xplained | sama5d3 ek | sama5d4 xplained | sama5d4 ek
---------------------- | ---------------- | ---------------- | ---------------- | ---------- | ---------------- | ----------
adc                    | OK               | x                | OK               | OK         | OK               | OK
audio_recorder         | OK               | x                | x                | OK         | x                | OK
can                    | OK               | OK               | x                | x          | x                | x
classd                 | OK               | x                | x                | x          | x                | x
crypto_aes             | OK               | OK               | OK               | OK         | OK               | OK
crypto_aesb            | OK               | OK               | x                | x          | OK               | OK
crypto_icm             | OK               | OK               | x                | x          | OK               | OK
crypto_qspi_aesb       | OK               | OK               | x                | x          | x                | x
crypto_sha             | OK               | OK               | OK               | OK         | OK               | OK
crypto_tdes            | OK               | OK               | OK               | OK         | OK               | OK
crypto_trng            | OK               | OK               | OK               | OK         | OK               | OK
ddram                  | OK               | OK               | OK               | OK         | OK               | OK
dma                    | OK               | OK               | OK               | OK         | OK               | OK
getting_started        | OK               | OK               | OK               | OK         | OK               | OK
eefc                   | x                | x                | x                | x          | x                | x
eth                    | OK               | OK               | OK               | OK         | OK               | OK
eth_lwip               | OK               | OK               | OK               | OK         | OK               | OK
eth_uip_helloworld     | OK               | OK               | OK               | OK         | OK               | OK
eth_uip_telnetd        | OK               | OK               | OK               | OK         | OK               | OK
eth_uip_webserver      | OK               | OK               | OK               | OK         | OK               | OK
isc                    | OK               | OK               | x                | x          | x                | x
isi                    | x                | x                | x                | x          | x                | OK
lcd                    | OK               | OK               | OK               | OK         | OK               | OK
low_power_mode         | OK               | OK               | OK               | OK         | OK               | OK
pdmic                  | OK               | x                | x                | x          | x                | x
pmc_clock_switching    | OK               | OK               | OK               | OK         | OK               | OK
power_consumption_pll  | OK               | OK               | OK               | OK         | OK               | OK
pwm                    | OK               | OK               | x                | OK         | OK               | OK
qspi_flash             | OK               | OK               | x                | x          | x                | x
qspi_xip               | OK               | OK               | x                | x          | x                | x
rtc                    | OK               | OK               | OK               | OK         | OK               | OK
sdmmc_sdcard           | OK               | OK               | OK               | OK         | OK               | OK
secumod                | OK               | OK               | x                | x          | OK               | OK
smc_nandflash_mlc      | OK               | x                | OK               | OK         | OK               | OK
smc_nandflash_slc      | OK               | x                | OK               | OK         | OK               | OK
spi_serialflash        | OK               | x                | OK               | OK         | OK               | OK
spi_slave              | OK               | OK               | x                | OK         | OK               | OK
ssc_dma_audio          | TODO             | x                | OK               | OK         | OK               | OK
tc                     | OK               | x                | OK               | OK         | OK               | OK
test-pio               | OK               | OK               | OK               | TODO       | OK               | OK
timer                  | OK               | OK               | OK               | OK         | OK               | OK
twi_eeprom             | OK               | OK               | OK               | OK         | OK               | OK
usart                  | OK               | OK               | OK               | TODO       | OK               | OK
usart_irda             | OK               | x                | TODO             | TODO       | OK               | OK
usart_iso7816          | OK               | OK               | OK               | OK         | OK               | OK
usart_lin              | OK               | x                | x                | x          | x                | x
usart_rs485            | OK               | x                | OK               | OK         | OK               | OK
usb_audio_looprec      | OK               | x                | OK               | OK         | OK               | OK
usb_audio_multi_channels | OK             | x                | TODO             | TODO       | TODO             | TODO
usb_audio_speaker      | OK               | x                | x                | OK         | x                | OK
usb_cdc_serial         | OK               | OK               | OK               | OK         | OK               | OK
usb_hid_aud            | OK               | x                | x                | OK         | x                | OK
usb_hid_keyboard       | OK               | OK               | OK               | OK         | OK               | OK
usb_hid_mouse          | OK               | OK               | OK               | OK         | OK               | OK
usb_hid_msd            | OK               | OK               | OK               | OK         | OK               | OK
usb_hid_transfer       | OK               | OK               | OK               | OK         | OK               | OK
usb_iad_cdc_aud        | OK               | x                | x                | OK         | x                | OK
usb_iad_cdc_cdc        | OK               | OK               | OK               | OK         | OK               | OK
usb_iad_cdc_hid        | OK               | OK               | OK               | OK         | OK               | OK
usb_iad_cdc_msd        | OK               | OK               | OK               | OK         | OK               | OK
usb_mass_storage       | OK               | OK               | OK               | OK         | OK               | OK
usb_uvc_isc            | OK               | OK               | x                | x          | x                | x
usb_uvc_isi            | x                | x                | x                | OK         | x                | OK
wdt                    | OK               | OK               | x                | x          | OK               | OK

(Cont.)

Examples               | sam9xx5 ek | same70 xplained | samv71 xplained
---------------------- | ---------- | --------------- | ---------------
adc                    | OK         | TODO            | TODO
audio_recorder         | OK         | x               | TODO
can                    | x          | OK              | OK
classd                 | x          | x               | x
crypto_aes             | x          | OK              | OK
crypto_aesb            | x          | x               | x
crypto_icm             | x          | OK              | OK
crypto_qspi_aesb       | x          | x               | x
crypto_sha             | x          | x               | x
crypto_tdes            | x          | x               | x
crypto_trng            | x          | OK              | OK
ddram                  | OK         | OK              | OK
dma                    | OK         | OK              | OK
getting_started        | OK         | OK              | OK
eefc                   | x          | OK              | OK
eth                    | OK         | OK              | OK
eth_lwip               | OK         | OK              | OK
eth_uip_helloworld     | OK         | OK              | OK
eth_uip_telnetd        | OK         | OK              | OK
eth_uip_webserver      | OK         | OK              | OK
isc                    | x          | x               | x
isi                    | x          | x               | x
lcd                    | OK         | x               | TODO
low_power_mode         | TODO       | TODO            | TODO
pdmic                  | x          | TODO            | TODO
pmc_clock_switching    | OK         | TODO            | OK
power_consumption_pll  | OK         | OK              | TODO
pwm                    | OK         | OK              | OK
qspi_flash             | x          | x               | TODO
qspi_xip               | x          | x               | TODO
rtc                    | OK         | OK              | OK
sdmmc_sdcard           | OK         | OK              | OK
secumod                | x          | x               | x
smc_nandflash_mlc      | OK         | x               | x
smc_nandflash_slc      | OK         | x               | x
spi_serialflash        | OK         | x               | x
spi_slave              | OK         | x               | x
ssc_dma_audio          | OK         | x               | OK
tc                     | OK         | OK              | OK
test-pio               | OK         | OK              | OK
timer                  | OK         | OK              | OK
twi_eeprom             | OK         | OK              | OK
usart                  | OK         | OK              | OK
usart_irda             | OK         | TODO            | TODO
usart_iso7816          | OK         | TODO            | OK
usart_lin              | x          | TODO            | TODO
usart_rs485            | TODO       | OK              | OK
usb_audio_looprec      | TODO       | x               | TODO
usb_audio_multi_channels | TODO     | x               | TODO
usb_audio_speaker      | OK         | x               | OK
usb_cdc_serial         | OK         | OK              | OK
usb_hid_aud            | OK         | x               | OK
usb_hid_keyboard       | OK         | OK              | OK
usb_hid_mouse          | OK         | OK              | OK
usb_hid_msd            | OK         | OK              | OK
usb_hid_transfer       | OK         | OK              | OK
usb_iad_cdc_aud        | OK         | x               | OK
usb_iad_cdc_cdc        | OK         | OK              | OK
usb_iad_cdc_hid        | OK         | OK              | OK
usb_iad_cdc_msd        | OK         | OK              | OK
usb_mass_storage       | OK         | OK              | OK
usb_uvc_isc            | x          | x               | x
usb_uvc_isi            | OK         | TODO            | TODO
wdt                    | x          | OK              | OK

Legend:
  * "x" means "Not Applicable"
  * "OK" means "Supported"
  * "TODO" means "Hardware supports it but not yet implemented/validated"
