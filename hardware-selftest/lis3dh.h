#ifndef LIS3DH_H_
#define LIS3DH_H_

/* MEMS digital output motion sensor */

#include <Driver_I2C.h>
#include <stdint.h>
#include <stdbool.h>

int lis3dh_init(ARM_DRIVER_I2C* bus, uint8_t address);
void lis3dh_power(uint8_t rate, bool low_res, bool x, bool y, bool z);
void lis3dh_out(uint16_t *x, uint16_t *y, uint16_t *z);
#endif /* LIS3DH_H_ */
