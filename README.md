# ESP32-S3-LCD-1.85-HA

## Configs

- `esphome/esp32-s3-lcd-185.yaml` — Voice Assistant-focused config based on the ESP32-S3-BOX reference hardware.
- `esphome/waveshare-1_85-hello.yaml` — Minimal “hello screen” for the Waveshare ESP32-S3-LCD-1.85 board using the local external components.

### Waveshare “hello” hardware map (1.85" round)

- I2C on `GPIO10/GPIO11` (main bus for the PCA9554).
- Backlight on `GPIO5` (LEDC).
- QSPI pins: `CLK=GPIO40`, data `[GPIO46, GPIO45, GPIO42, GPIO41]`, `CS=GPIO21`.

Flash the desired YAML with ESPHome to bring the display up quickly.

## Local external components

- `components/waveshare_exio/` — PCA/TCA9554 helper for driving the LCD reset (EXIO2).
- `components/st77916_qspi_display/` — QSPI ST77916 display driver built on ESP-IDF `esp_lcd`.

Both are pulled in automatically by `esphome/waveshare-1_85-hello.yaml` via `external_components:`.
