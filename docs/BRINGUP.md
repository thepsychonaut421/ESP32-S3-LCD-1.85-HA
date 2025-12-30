# ESP32-S3-LCD-1.85 Home Assistant Bring-Up

This checklist walks through verifying the Waveshare ESP32-S3-LCD-1.85 hardware for a Home Assistant (HA) target before layering your full firmware stack. It assumes the pin map in [`PINOUT.md`](./PINOUT.md).

## Minimal HA bring-up

1. **Flash connectivity/console**  
   - Enter download mode (GPIO0 low on reset) and verify `esptool.py flash_id` succeeds.  
   - Flash a minimal HA build (e.g., a stripped `esphome` sketch) that boots to the serial console at 115200 baud. Confirm the boot log shows 8 MB PSRAM detected and no brownout/reset loops.
2. **Wi-Fi + OTA heartbeat**  
   - Configure Wi-Fi credentials and enable OTA.  
   - Confirm the device registers in HA and that OTA updates complete twice in a row without manual intervention.
3. **GPIO sanity**  
   - Confirm the backlight line (GPIO5) idles low on reset to avoid flash during boot.  
   - Toggle a visible LED or logline from a spare GPIO (e.g., GPIO38) to prove general pin control.

## Backlight proof-of-life

1. Drive GPIO5 high for a second, then PWM at ~1 kHz to verify brightness control.  
2. Confirm no display artifacts are present when toggling backlight alone (if they appear, check shared grounds and noise on the 5 V rail).  
3. If PWM causes noise on the speaker rail, move the PWM channel to a timer not shared with I2S.

## Display QSPI bring-up

1. **Bus configuration**  
   - Configure QSPI with `LCD_CS=6`, `CLK=15`, `D0=16`, `D1=17`, `D2=18`, `D3=7`, `DC=0`, `RST=4`, `TE=3`.  
   - Set 80 MHz clock only after basic frames work at 40 MHz; confirm mode 0.
2. **Reset + orientation**  
   - Issue a hardware reset (GPIO4 low for >10 µs) before the init sequence.  
   - Verify the MADCTL/rotation matches the glass orientation (1.85" round glass is 240×280; origin at top-left when flex tail points down).
3. **Test pattern**  
   - Push solid colors, then a 16-color gradient to validate data lines.  
   - Enable tearing-effect input (GPIO3) and verify VSync-aligned updates for smooth animation.

## OTA validation

1. Trigger two successive OTA updates (small config change) to confirm the dual-partition scheme and rollback work.  
2. Verify network recovery: power-cycle mid-OTA and confirm the device returns to the previous firmware.  
3. Capture logs to ensure flash/PSRAM timing changes for the display do not break OTA stability.

## Audio path tests

1. **Codec setup**  
   - Configure I2S with `MCLK=48`, `BCLK=46`, `LRCK=9`, `DOUT=10` (speaker), `DIN=11` (mic), and drive `SPK_EN=45` high after init.  
   - If the codec/amp uses I²C control, use `SDA=1`, `SCL=2`.
2. **Playback**  
   - Play a 1 kHz sine at -12 dBFS and check for clipping or distortion.  
   - Sweep volume to ensure `SPK_EN` gating works and that there is no pop when enabling the amp.
3. **Capture**  
   - Record a short sample; verify the channel order is correct and that LRCK/BCLK polarity matches expectations.  
   - Check for crosstalk or display-induced noise by running a display refresh while recording.

## Storage + sensors

1. **microSD**  
   - Mount the card using `CS=12`, `CLK=14`, `MOSI=13`, `MISO=21`, `CD=40`.  
   - Run a read/write test file and confirm stable operation at 20 MHz SPI; fall back to 10 MHz if errors appear.
2. **I²C sensors**  
   - Probe the bus (`SDA=1`, `SCL=2`) and verify expected addresses (e.g., IMU at `0x6A`/`0x6B`).  
   - Confirm interrupt (GPIO14) fires for motion/gesture events if the sensor is populated.

## Regression matrix before HA integration

- OTA twice in succession after display and audio drivers are enabled.  
- Display: two full-screen updates per second for 5 minutes without tearing or QSPI checksum errors.  
- Audio: simultaneous playback + capture for 60 seconds without I2S underrun/overrun.  
- microSD: 10 MB sequential write/read loop with CRC verification.  
- I²C: 10 minute sensor poll without timeouts.
