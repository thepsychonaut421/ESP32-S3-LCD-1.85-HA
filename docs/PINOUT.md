# Waveshare ESP32-S3-LCD-1.85 Pinout

> Pin map is based on the vendor reference design for the Waveshare ESP32-S3-LCD-1.85 (16 MB Flash / 8 MB PSRAM) and should be double-checked against your hardware revision or schematic when wiring alternate peripherals.

## Core power and control

| Function | Pin | Notes |
| --- | --- | --- |
| 5 V input | 5 V | USB-C or external 5 V rail |
| 3V3 rail | 3V3 | On-board regulator output |
| Boot/Download | GPIO0 | Strapping; keep high during normal boot |
| EN | EN | Reset/enable line |

## Display (QSPI)

| Signal | Pin | Notes |
| --- | --- | --- |
| LCD_CS | GPIO6 | QSPI chip select |
| LCD_CLK | GPIO15 | QSPI clock |
| LCD_D0 | GPIO16 | QSPI data 0 (IO0) |
| LCD_D1 | GPIO17 | QSPI data 1 (IO1) |
| LCD_D2 | GPIO18 | QSPI data 2 (IO2) |
| LCD_D3 | GPIO7 | QSPI data 3 (IO3) |
| LCD_DC | GPIO0 | Data/command select (shared strapping) |
| LCD_RST | GPIO4 | Display reset (active low) |
| LCD_TE | GPIO3 | Tearing-effect input (optional) |
| LCD_BL | GPIO5 | Backlight enable/PWM |

## Audio (I2S)

| Signal | Pin | Notes |
| --- | --- | --- |
| I2S_MCLK | GPIO48 | Master clock for audio codec path |
| I2S_BCLK | GPIO46 | Bit clock |
| I2S_LRCK | GPIO9 | Word-select / LRCK |
| I2S_DOUT (SPK) | GPIO10 | Speaker / DAC data out |
| I2S_DIN (MIC) | GPIO11 | Microphone data in |
| SPK_EN | GPIO45 | Amplifier enable (high = on) |

## I²C peripherals

| Signal | Pin | Notes |
| --- | --- | --- |
| I2C_SDA | GPIO1 | Pull-ups populated on board |
| I2C_SCL | GPIO2 | Pull-ups populated on board |
| IMU_INT | GPIO14 | IMU/gesture interrupt (if populated) |

## microSD (SPI)

| Signal | Pin | Notes |
| --- | --- | --- |
| SD_CS | GPIO12 | Card select |
| SD_CLK | GPIO14 | Clock (shared with IMU_INT; isolate if both used) |
| SD_MOSI | GPIO13 | Data out |
| SD_MISO | GPIO21 | Data in |
| SD_CD | GPIO40 | Card-detect switch (active low) |

