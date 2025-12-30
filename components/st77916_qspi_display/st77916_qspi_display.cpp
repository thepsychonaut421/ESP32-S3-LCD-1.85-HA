#include "st77916_qspi_display.h"

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esphome/core/log.h"
#include "esp_lcd_panel_interface.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_st77916.h"

namespace esphome {
namespace st77916_qspi_display {

static const char *const TAG = "st77916_qspi";

void ST77916QSPI::setup() {
  ESP_LOGI(TAG, "Setting up ST77916 QSPI display...");

  fb_.assign(static_cast<size_t>(width_ * height_), 0x0000);  // RGB565 black
  this->init_internal_(width_, height_);

  spi_bus_config_t buscfg = {};
  buscfg.sclk_io_num = clk_;
  buscfg.data0_io_num = d0_;
  buscfg.data1_io_num = d1_;
  buscfg.data2_io_num = d2_;
  buscfg.data3_io_num = d3_;
  buscfg.max_transfer_sz = static_cast<int>(fb_.size() * sizeof(uint16_t) + 8);
  buscfg.flags = SPICOMMON_BUSFLAG_MASTER | SPICOMMON_BUSFLAG_GPIO_PINS | SPICOMMON_BUSFLAG_QUAD;

  ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO));

  esp_lcd_panel_io_spi_config_t io_config = {};
  io_config.cs_gpio_num = cs_;
  io_config.dc_gpio_num = -1;  // QSPI panel without DC
  io_config.spi_mode = 0;
  io_config.pclk_hz = 40 * 1000 * 1000;
  io_config.trans_queue_depth = 10;
  io_config.lcd_cmd_bits = 8;
  io_config.lcd_param_bits = 8;
  io_config.flags.quad_mode = 1;

  ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t) SPI2_HOST, &io_config, &io_));

  esp_lcd_panel_dev_config_t panel_config = {};
  panel_config.reset_gpio_num = -1;  // Reset is handled via expander
  panel_config.rgb_endian = LCD_RGB_ENDIAN_BGR;
  panel_config.bits_per_pixel = 16;

  ESP_ERROR_CHECK(esp_lcd_new_panel_st77916(io_, &panel_config, &panel_));

  ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_));
  ESP_ERROR_CHECK(esp_lcd_panel_init(panel_));
  ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_, true));

  ESP_LOGI(TAG, "Display initialized (%dx%d)", width_, height_);
}

void ST77916QSPI::dump_config() {
  ESP_LOGCONFIG(TAG, "ST77916 QSPI Display");
  ESP_LOGCONFIG(TAG, "  Size: %dx%d", width_, height_);
  ESP_LOGCONFIG(TAG, "  Rotation: %d", rotation_);
  ESP_LOGCONFIG(TAG, "  Pins: CLK=%d CS=%d D0=%d D1=%d D2=%d D3=%d", clk_, cs_, d0_, d1_, d2_, d3_);
}

void ST77916QSPI::draw_absolute_pixel_internal(int x, int y, Color color) {
  if (x < 0 || y < 0 || x >= width_ || y >= height_)
    return;
  // Convert RGB888 -> RGB565
  uint16_t c = static_cast<uint16_t>(((color.r & 0xF8) << 8) | ((color.g & 0xFC) << 3) | (color.b >> 3));
  fb_[static_cast<size_t>(y * width_ + x)] = c;
}

void ST77916QSPI::update() {
  if (!panel_)
    return;

  ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(panel_, 0, 0, width_, height_, fb_.data()));
}

}  // namespace st77916_qspi_display
}  // namespace esphome
