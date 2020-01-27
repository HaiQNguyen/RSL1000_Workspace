#include "pca9655.h"

enum {
    CMD_INPUT_PORT_0,
    CMD_INPUT_PORT_1,
    CMD_OUTPUT_PORT_0,
    CMD_OUTPUT_PORT_1,
    CMD_POLARITY_INVERSION_0,
    CMD_POLARITY_INVERSION_1,
    CMD_CONFIGURATION_0,
    CMD_CONFIGURATION_1,
} command;

static ARM_DRIVER_I2C *g_i2c = NULL;
static uint8_t g_address = 0x00;

static void write_reg(uint8_t reg, uint8_t value)
{
    uint8_t data[] = { reg, value };
    g_i2c->MasterTransmit(g_address, data, sizeof(data), false);
    while (g_i2c->GetStatus().busy);
}

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

int pca9655_init(ARM_DRIVER_I2C* bus, uint8_t address)
{
    if (!bus || address < 0x20 || address > 0xEE)
        return -1;
    g_i2c = bus;
    g_address = address;
    return 0;
}

void pca9655_port_dir(uint8_t port, uint8_t mask)
{
    write_reg(CMD_CONFIGURATION_0 + port, mask);
}

void pca9655_port_set(uint8_t port, uint8_t value)
{
    write_reg(CMD_OUTPUT_PORT_0 + port, value);
}

uint8_t pca9655_port_get(uint8_t port)
{
    return read_reg(CMD_INPUT_PORT_0 + port);
}

void pca9655_port_polarity(uint8_t port, uint8_t mask)
{
    write_reg(CMD_POLARITY_INVERSION_0 + port, mask);
}

