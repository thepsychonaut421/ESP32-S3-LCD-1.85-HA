import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import CONF_ADDRESS, CONF_ID

DEPENDENCIES = ["i2c"]

waveshare_exio_ns = cg.esphome_ns.namespace("waveshare_exio")
WaveshareExio = waveshare_exio_ns.class_("WaveshareExio", cg.Component, i2c.I2CDevice)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(WaveshareExio),
        }
    )
    .extend(i2c.i2c_device_schema(default_address=0x20))
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)
