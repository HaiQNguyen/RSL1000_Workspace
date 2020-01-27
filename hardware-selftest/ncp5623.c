#include "ncp5623.h"

enum {
    REG_SHUTDOWN,
    REG_ILED,
    REG_RED,
    REG_GREEN,
    REG_BLUE,
    REG_UPWARD_IEND,
    REG_DOWNWARD_IEND,
    REG_DIMMING
} reg;

static ARM_DRIVER_I2C *g_i2c = NULL;
static uint8_t g_address = 0x00;

static void write_reg(uint8_t reg, uint8_t value)
{
    uint8_t data = (reg<<5) | (value&0x1F);
    g_i2c->MasterTransmit(g_address, &data, 1, true);
    while (g_i2c->GetStatus().busy);
}

int ncp5623_init(ARM_DRIVER_I2C* bus, uint8_t address)
{
    if (!bus || address < 0x20 || address > 0xEE)
        return -1;
    g_i2c = bus;
    g_address = address;
    return 0;
}

void ncp5623_off(void)
{
    write_reg(REG_SHUTDOWN, 0);
}

void ncp5623_iled(uint8_t iled)
{
    write_reg(REG_ILED, iled);
}

void ncp5623_color(uint8_t r, uint8_t g, uint8_t b)
{
    write_reg(REG_RED, r);
    write_reg(REG_GREEN, g);
    write_reg(REG_BLUE, b);
}

void ncp5623_upward(uint8_t iend, uint8_t step)
{
    write_reg(REG_UPWARD_IEND, iend);
    write_reg(REG_DIMMING, step);
}

void ncp5623_downward(uint8_t iend, uint8_t step)
{
    write_reg(REG_DOWNWARD_IEND, iend);
    write_reg(REG_DIMMING, step);
}
