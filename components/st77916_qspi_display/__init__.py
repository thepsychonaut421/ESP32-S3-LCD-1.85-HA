import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import display
from esphome.const import CONF_HEIGHT, CONF_ID, CONF_ROTATION, CONF_WIDTH

DEPENDENCIES = ["display"]

CONF_CLK_PIN = "clk_pin"
CONF_CS_PIN = "cs_pin"
CONF_D0_PIN = "d0_pin"
CONF_D1_PIN = "d1_pin"
CONF_D2_PIN = "d2_pin"
CONF_D3_PIN = "d3_pin"

st77916_ns = cg.esphome_ns.namespace("st77916_qspi_display")
ST77916QSPI = st77916_ns.class_("ST77916QSPI", display.DisplayBuffer, cg.Component)

CONFIG_SCHEMA = (
    display.BASIC_DISPLAY_SCHEMA.extend(
        {
            cv.GenerateID(): cv.declare_id(ST77916QSPI),
            cv.Required(CONF_CLK_PIN): cv.int_,
            cv.Required(CONF_CS_PIN): cv.int_,
            cv.Required(CONF_D0_PIN): cv.int_,
            cv.Required(CONF_D1_PIN): cv.int_,
            cv.Required(CONF_D2_PIN): cv.int_,
            cv.Required(CONF_D3_PIN): cv.int_,
            cv.Optional(CONF_WIDTH, default=360): cv.int_range(min=1, max=800),
            cv.Optional(CONF_HEIGHT, default=360): cv.int_range(min=1, max=800),
            cv.Optional(CONF_ROTATION, default=0): cv.int_range(min=0, max=359),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await display.register_display(var, config)

    cg.add(
        var.set_pins(
            config[CONF_CLK_PIN],
            config[CONF_CS_PIN],
            config[CONF_D0_PIN],
            config[CONF_D1_PIN],
            config[CONF_D2_PIN],
            config[CONF_D3_PIN],
        )
    )
    cg.add(var.set_size(config[CONF_WIDTH], config[CONF_HEIGHT]))
    cg.add(var.set_rotation(config[CONF_ROTATION]))
