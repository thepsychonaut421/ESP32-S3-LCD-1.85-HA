#pragma once

#include "esphome/core/component.h"
#include "esphome/components/i2c/i2c.h"

namespace esphome {
namespace waveshare_exio {

class WaveshareExio : public Component, public i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;

  void set_pin_output(uint8_t pin, bool output);
  void write_pin(uint8_t pin, bool high);

 protected:
  uint8_t config_ = 0xFF;  // 1=input, 0=output (PCA/TCA9554 style)
  uint8_t output_ = 0xFF;  // output register

  void write_reg_(uint8_t reg, uint8_t value);
  uint8_t read_reg_(uint8_t reg);
};

}  // namespace waveshare_exio
}  // namespace esphome
