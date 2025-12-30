# ESP32-S3-LCD-1.85-HA

## Configs

- `esphome/esp32-s3-lcd-185.yaml` — Voice Assistant-focused config based on the ESP32-S3-BOX reference hardware.
- `esphome/waveshare-1_85-hello.yaml` — Minimal “hello screen” for the Waveshare ESP32-S3-LCD-1.85 board using the QSPI ST77916 panel and the PCA9554 reset expander.

The Waveshare example expects:

- I2C on `GPIO10/GPIO11` (main bus for the PCA9554).
- Backlight on `GPIO5` (LEDC).
- QSPI pins: `CLK=GPIO40`, data `[GPIO46, GPIO45, GPIO42, GPIO41]`, `CS=GPIO21`.

Flash the desired YAML with ESPHome to bring the display up quickly.
