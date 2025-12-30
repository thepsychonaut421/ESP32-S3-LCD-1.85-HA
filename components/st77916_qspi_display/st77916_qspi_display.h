#pragma once

#include <vector>

#include "esphome/core/component.h"
#include "esphome/components/display/display_buffer.h"

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"

namespace esphome {
namespace st77916_qspi_display {

class ST77916QSPI : public display::DisplayBuffer, public Component {
 public:
  void set_pins(int clk, int cs, int d0, int d1, int d2, int d3) {
    clk_ = clk;
    cs_ = cs;
    d0_ = d0;
    d1_ = d1;
    d2_ = d2;
    d3_ = d3;
  }
  void set_size(int w, int h) {
    width_ = w;
    height_ = h;
  }
  void set_rotation(int r) { rotation_ = r; }

  void setup() override;
  void update() override;
  void dump_config() override;

  int get_width_internal() override { return width_; }
  int get_height_internal() override { return height_; }
  display::DisplayType get_display_type() override { return display::DisplayType::DISPLAY_TYPE_COLOR; }

 protected:
  void draw_absolute_pixel_internal(int x, int y, Color color) override;

  int clk_{-1}, cs_{-1}, d0_{-1}, d1_{-1}, d2_{-1}, d3_{-1};
  int width_{360}, height_{360}, rotation_{0};

  esp_lcd_panel_io_handle_t io_{nullptr};
  esp_lcd_panel_handle_t panel_{nullptr};

  std::vector<uint16_t> fb_;  // RGB565 framebuffer
};

}  // namespace st77916_qspi_display
}  // namespace esphome
