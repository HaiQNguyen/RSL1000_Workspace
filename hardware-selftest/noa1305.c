#include "noa1305.h"

enum {
    REG_POWER_CONTROL,
    REG_RESET,
    REG_INTEGRATION_TIME,
    REG_INT_SELECT,
    REG_THRESH_LSB,
    REG_THRESH_MSB,
    REG_ALS_DATA_LSB,
    REG_ALS_DATA_MSB,
    REG_DEVICE_ID_LSB,
    REG_DEVICE_ID_MSB,
} reg;

static ARM_DRIVER_I2C *g_i2c = NULL;
static uint8_t g_address = 0x00;

static uint8_t read_reg(uint8_t reg)
{
    uint8_t data[] = { reg };
    uint8_t value;
    g_i2c->MasterTransmit(g_address, data, sizeof(data), true);
    while (g_i2c->GetStatus().busy);
    g_i2c->MasterReceive (g_address, &value, 1, false);
    while (g_i2c->GetStatus().busy);
    return value;
}

int noa1305_init(ARM_DRIVER_I2C* bus, uint8_t address)
{
    uint16_t dev_id;
    if (!bus)
        return -1;
    g_i2c = bus;
    g_address = address;
    dev_id = noa1305_device_id();
    return (dev_id != 0x0519);
}

uint16_t noa1305_device_id()
{
    return (uint16_t)(read_reg(REG_DEVICE_ID_MSB) << 8) | read_reg(REG_DEVICE_ID_LSB);
}
