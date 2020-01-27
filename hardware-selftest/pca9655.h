#ifndef PCA9655_H_
#define PCA9655_H_

/* PCA9655E Remote 16-bit I/O Expander for I2C Bus with Interrupt */

#include <Driver_I2C.h>
#include <stdint.h>

/**
 *  @brief          Initialize driver
 *  @param bus      Instance to CMSIS's I2C driver
 *  @param address  Chip I2C address
 *  @returns        0 if success and chip found, -1 if error
 */
int pca9655_init(ARM_DRIVER_I2C* bus, uint8_t address);

/**
 *  @brief          Set pin direction on specific port.
 *  @param port     Indicate port to be configured. Can be 0 or 1.
 *  @param value    Sets pins direction in port. Bit value 1 is input, 0 is output.
 *  @note           Value is written to register, it's not OR'ed
 */
void pca9655_port_dir(uint8_t port, uint8_t value);

/**
 *  @brief          Set port value
 *  @param port     Indicate port to be set. Can be 0 or 1.
 *  @param value    8-bit value to be written
 *  @note           Value is written to register, it's not OR'ed
 */
void pca9655_port_set(uint8_t port, uint8_t value);

/**
 *  @brief          Set port polarity
 *  @param port     Indicate port to be set. Can be 0 or 1.
 *  @param value    Sets pin direction. Bit value 1 corresponds to inverted polarity.
 *  @note           Value is written to register, it's not OR'ed
 */
void pca9655_port_polarity(uint8_t port, uint8_t value);

/**
 *  @brief          Get port value
 *  @param port     Indicate port to be set. Can be 0 or 1.
 *  @return         8-bit value of port
 */
uint8_t pca9666_port_get(uint8_t port);


#endif /* PCA9655_H_ */
