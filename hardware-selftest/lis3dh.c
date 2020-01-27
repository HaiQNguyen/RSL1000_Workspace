#include "lis3dh.h"

enum {
    STATUS_REG_AUX = 0x07,
    OUT_ADC1_L,
    OUT_ADC1_H,
    OUT_ADC2_L,
    OUT_ADC2_H,
    OUT_ADC3_L,
    OUT_ADC3_H,
    WHO_AM_I = 0x0f,
    CTRL_REG0 = 0x1E,
    TEMP_CFG_REG,
    CTRL_REG1,
    CTRL_REG2,
    CTRL_REG3,
    CTRL_REG4,
    CTRL_REG5,
    CTRL_REG6,
    REFERENCE,
    STATUS_REG,
    OUT_X_L,
    OUT_X_H,
    OUT_Y_L,
    OUT_Y_H,
    OUT_Z_L,
    OUT_Z_H,
    FIFO_CTRL_REG,
    FIFO_SRC_REG,
} reg;

static ARM_DRIVER_I2C *g_i2c = NULL;
static uint8_t g_address = 0x00;

static void write_reg(uint8_t reg, uint8_t value)
{
    uint8_t data[] = { reg, value };
    g_i2c->MasterTransmit(g_address, data, sizeof(data), false);
    while (g_i2c->GetStatus().busy);
}

static void read_reg(uint8_t reg, uint8_t len, uint8_t *read)
{
    uint8_t data[] = { reg };
    g_i2c->MasterTransmit(g_address, data, sizeof(data), true);
    while (g_i2c->GetStatus().busy);

    while(len) {
        g_i2c->MasterReceive (g_address, read, 1, (len >= 1));
        while (g_i2c->GetStatus().busy);
        read++;
        len--;
    }
}

int lis3dh_init(ARM_DRIVER_I2C* bus, uint8_t address)
{
    uint8_t dev_id;
    if (!bus || (address != 0x18 && address != 0x19))
        return -1;
    g_i2c = bus;
    g_address = address;
    uint8_t id = 0x00;
    read_reg(WHO_AM_I, 1, &id);
    if (id != 0x33)
        return -1;
    return 0;
}

void lis3dh_power(uint8_t rate, bool low_res, bool x, bool y, bool z)
{
    uint8_t regval = ((rate&0xF)<<4) | (low_res << 3) | (z << 2) | (y << 1) | x;
    write_reg(CTRL_REG1, regval);
}

void lis3dh_out(uint16_t *x, uint16_t *y, uint16_t *z)
{
    uint8_t val;
    read_reg(OUT_X_L, 1, &val);
    *x = val;
    read_reg(OUT_X_H, 1, &val);
    *x |= (val << 8);
}
