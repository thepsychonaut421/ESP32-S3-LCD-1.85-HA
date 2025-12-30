#include "waveshare_exio.h"
#include "esphome/core/log.h"

namespace esphome {
namespace waveshare_exio {

static const char *const TAG = "waveshare_exio";

// PCA/TCA9554 registers (compatible for basic I/O)
static const uint8_t REG_INPUT = 0x00;
static const uint8_t REG_OUTPUT = 0x01;
static const uint8_t REG_CONFIG = 0x03;

void WaveshareExio::setup() {
  ESP_LOGI(TAG, "Setting up EXIO expander...");
  // Many 9554 parts default to all inputs; read current state for visibility.
  config_ = read_reg_(REG_CONFIG);
  output_ = read_reg_(REG_OUTPUT);
  ESP_LOGI(TAG, "Initial REG_CONFIG=0x%02X REG_OUTPUT=0x%02X", config_, output_);
}

void WaveshareExio::dump_config() {
  ESP_LOGCONFIG(TAG, "Waveshare EXIO (PCA/TCA9554)");
  LOG_I2C_DEVICE(this);
}

void WaveshareExio::set_pin_output(uint8_t pin, bool output) {
  if (pin > 7) {
    ESP_LOGW(TAG, "Invalid pin %u", pin);
    return;
  }
  // config bit: 1=input, 0=output
  if (output) {
    config_ &= static_cast<uint8_t>(~(1 << pin));
  } else {
    config_ |= static_cast<uint8_t>(1 << pin);
  }
  write_reg_(REG_CONFIG, config_);
}

void WaveshareExio::write_pin(uint8_t pin, bool high) {
  if (pin > 7) {
    ESP_LOGW(TAG, "Invalid pin %u", pin);
    return;
  }
  if (high) {
    output_ |= static_cast<uint8_t>(1 << pin);
  } else {
    output_ &= static_cast<uint8_t>(~(1 << pin));
  }
  write_reg_(REG_OUTPUT, output_);
}

void WaveshareExio::write_reg_(uint8_t reg, uint8_t value) {
  uint8_t data[2] = {reg, value};
  auto err = this->write(data, 2);
  if (err != i2c::ERROR_OK) {
    ESP_LOGW(TAG, "I2C write reg 0x%02X failed", reg);
  }
}

uint8_t WaveshareExio::read_reg_(uint8_t reg) {
  uint8_t val = 0;
  auto err = this->write_read(&reg, 1, &val, 1);
  if (err != i2c::ERROR_OK) {
    ESP_LOGW(TAG, "I2C read reg 0x%02X failed", reg);
  }
  return val;
}

}  // namespace waveshare_exio
}  // namespace esphome
