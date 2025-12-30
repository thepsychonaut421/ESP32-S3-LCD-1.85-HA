# Known Issues and Caveats (Waveshare ESP32-S3-LCD-1.85)

## Display (QSPI)

- **High-speed QSPI timing:** Some panels fail above 40 MHz. If artifacts appear (vertical stripes, color swap), drop the QSPI clock to 40 MHz and ensure `DC` and `RST` are correctly driven before init.
- **DC on a strapping pin:** `LCD_DC` uses GPIO0, a boot strapping pin. Keep it high during reset to avoid entering download mode inadvertently.
- **TE polarity:** The tearing-effect line (GPIO3) may need polarity selection in your driver; mismatched polarity shows a single rolling tear during v-sync testing.
- **Backlight noise:** PWM on GPIO5 can couple into the audio rail; if audible whine is present, move the PWM to a timer group not shared with I2S and keep PWM at ≥20 kHz.

## Audio

- **Amp enable pop:** Driving `SPK_EN` high while the DAC output is floating can produce a loud pop. Gate audio to mute before toggling `SPK_EN` and ramp volume after enabling.
- **MCLK dependency:** Some codecs expect MCLK (GPIO48) even when operating at 48 kHz; without it the mic path may be silent. Provide MCLK if audio capture fails.

## microSD and I²C

- **SD and IMU share GPIO14:** If an IMU interrupt is wired to GPIO14, SD card CLK may conflict. Disable the interrupt or rewire the IMU INT when using SD.
- **Bus pull-ups:** The I²C bus relies on on-board pull-ups. If long wires are used, add stronger external pull-ups to avoid NACKs at 400 kHz.

## Power and boot

- **Boot strap interference:** Avoid pulling GPIO0/2/15 low during reset or you may enter bootloader mode. Peripherals on these pins should idle high.  
- **USB vs. external 5 V:** Noise on external 5 V rails can brownout the panel during QSPI bursts; prefer USB power for bring-up or add local bulk capacitance.
