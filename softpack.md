Atmel SAMA5 Software Package
----------------------------

# Code

The Atmel Softpack can be found on [GitHub](https://github.com/atmelcorp/atmel-software-package).

# Hardware Support

The Atmel Softpack support multiple devices and multiple targets.

## Devices

* SAMA5D2x family
* SAMA5D3x family
* SAMA5D4x family

## Targets

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
* dmac: Example of DMAC usage
* gettting-started: LED blink (uses PIT and PIO)
* eth: GMAC/EMAC example using a simple IP stack
* eth_lwip: GMAC/EMAC example using LWIP stack
* eth_uip_helloworld: GMAC/EMAC example using UIP stack (UIP helloworld example)
* eth_uip_telnetd: GMAC/EMAC example using UIP stack (UIP telnetd example)
* eth_uip_webserver: GMAC/EMAC example using UIP stack (UIP webserver example)
* hsmc_nandflash_mlc: Example of NAND Flash MLC
* hsmc_nandflash_slc: Example of NAND Flash SLC
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
* spi_serialflash: Read/Write/Delete commands to an SPI serial flash
* spi_slave: Set up the SAMA5D2 as a SPI slave
* ssc_dma_audio: Example of SSC to play sound
* tc_capture_waveform: Use TC in capture mode to measure pulse frequency of an external signal
* trng: Example using hardware RNG (interrupt mode)
* twi_eeprom: Read/Write/Delete commands to an Two-Wire EEPROM
* usart_fifo: Test Flexcom USART FIFO
* usart_irda: Example of communication over IrDA sensors (FieldBus extension board)
* usart_iso7816: Example of USART configured for ISO7816
* usart_lin: Example of USART configured for LIN
* usart_dma: Bidirectionnal Usart-memory DMA transfert example
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
* xdma: Memory-to-memory DMA transfert example

# Compatibility

Examples               | sama5d2-xplained | sama5d3-xplained | sama5d3-ek | sama5d4-xplained | sama5d4-ek
---------------------- | ---------------- | ---------------- | ---------- | ---------------- | ----------
adc                    | X                | X                | X          | X                | X
audio_recorder         | X                | N/A              | BROKEN     | N/A              | BROKEN
can                    | X                | N/A              | N/A        | N/A              | N/A
classd                 | X                | N/A              | N/A        | N/A              | N/A
crypto_aes             | X                | X                | X          | X                | X
crypto_aesb            | X                | N/A              | N/A        | X                | X
crypto_icm             | X                | N/A              | N/A        | X                | X
crypto_qspi_aesb       | X                | N/A              | N/A        | N/A              | N/A
crypto_sha             | X                | X                | X          | X                | X
crypto_tdes            | X                | X                | X          | X                | X
ddram                  | X                | X                | X          | X                | X
dmac                   | N/A              | X                | X          | N/A              | N/A
gettting-started       | X                | X                | X          | X                | X
eth                    | X                | X                | X          | X                | X
eth_lwip               | X                | X                | X          | X                | X
eth_uip_helloworld     | X                | X                | X          | X                | X
eth_uip_telnetd        | X                | X                | X          | X                | X
eth_uip_webserver      | X                | X                | X          | X                | X
hsmc_nandflash_mlc     | X                | X                | X          | X                | X
hsmc_nandflash_slc     | X                | X                | X          | X                | X
isc                    | X                | N/A              | N/A        | N/A              | N/A
isi                    | N/A              | X                | X          | X                | X
lcd                    | X                | X                | X          | X                | X
low_power_mode         | X                | X                | X          | X                | X
pdmic                  | X                | N/A              | N/A        | N/A              | N/A
pmc_clock_switching    | X                | X                | X          | X                | X
power_consumption_pll  | X                | X                | X          | X                | X
pwm                    | X                | N/A              | X          | X                | X
qspi_flash             | X                | N/A              | N/A        | N/A              | N/A
qspi_xip               | X                | N/A              | N/A        | N/A              | N/A
rtc                    | X                | X                | X          | X                | X
sdmmc_sdcard           | X                | TODO             | TODO       | X                | X
secumod                | X                | N/A              | N/A        | X                | X
spi_serialflash        | X                | X                | X          | X                | X
spi_slave              | X                | N/A              | TODO       | X                | X
ssc_dma_audio          | TODO             | X                | X          | X                | X
tc_capture_waveform    | X                | X                | X          | X                | X
trng                   | X                | X                | X          | X                | X
twi_eeprom             | X                | X                | X          | X                | X
usart_fifo             | X                | N/A              | N/A        | N/A              | N/A
usart_irda             | X                | TODO             | TODO       | X                | X
usart_iso7816          | X                | TODO             | TODO       | X                | X
usart_lin              | X                | N/A              | N/A        | N/A              | N/A
usart_dma              | X                | X                | TODO       | X                | X
usb_audio_looprec      | X                | X                | X          | X                | X
usb_audio_speaker      | X                | N/A              | X          | N/A              | X
usb_cdc_serial         | X                | X                | X          | X                | X
usb_hid_aud            | X                | N/A              | X          | N/A              | X
usb_hid_keyboard       | X                | X                | X          | X                | X
usb_hid_mouse          | X                | X                | X          | X                | X
usb_hid_msd            | X                | X                | X          | X                | X
usb_hid_transfer       | X                | X                | X          | X                | X
usb_iad_cdc_aud        | X                | N/A              | X          | N/A              | X
usb_iad_cdc_cdc        | X                | X                | X          | X                | X
usb_iad_cdc_hid        | X                | X                | X          | X                | X
usb_iad_cdc_msd        | X                | X                | X          | X                | X
usb_mass_storage       | X                | TODO             | TODO       | TODO             | TODO
usb_usv_isc            | X                | N/A              | N/A        | N/A              | N/A
usb_usv_isi            | N/A              | N/A              | X          | N/A              | X
wdt                    | X                | X                | X          | X                | X
xdma                   | X                | N/A              | N/A        | X                | X

