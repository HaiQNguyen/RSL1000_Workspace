#ifndef NOA1305_H_
#define NOA1305_H_

/* Triple Output I2C Controlled RGB LED Driver*/

#include <Driver_I2C.h>
#include <stdint.h>

int noa1305_init(ARM_DRIVER_I2C* bus, uint8_t address);
uint16_t noa1305_device_id(void);


#endif /* NOA1305_H_ */
