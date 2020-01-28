#ifndef NCP5623_H_
#define NCP5623_H_

/* Triple Output I2C Controlled RGB LED Driver*/

#include <Driver_I2C.h>
#include <stdint.h>

/**
 *  @brief          Initialize driver
 *  @param bus      Instance to CMSIS's I2C driver
 *  @param address  Chip I2C address
 *  @returns        0 if success and chip found, -1 if error
 */
int ncp5623_init(ARM_DRIVER_I2C* bus, uint8_t address);

/**
 *  @brief          Turn all PWM channels off
 */
void ncp5623_off(void);

/**
 *  @brief          Set led current
 *  @param iled      Encoded value ranges from 0 to 31
 */
void ncp5623_iled(uint8_t iled);

/**
 *  @brief          Set color
 *  @param r        Red
 *  @param g        Green
 *  @param b        Blue
 *  @note           values range from 0 to 31
 */
void ncp5623_color(uint8_t r, uint8_t g, uint8_t b);

/**
 *  @brief          Exponentially brighten to specified level
 *  @param iend     Target LED current (0-31)
 *  @step           Time between consecutive current increments (0-31)
 */
void ncp5623_upward(uint8_t iend, uint8_t step);

/**
 *  @brief          Exponentially dim to specified level
 *  @param iend     Target LED current (0-31)
 *  @step           Time between consecutive current decrements (0-31)
 */
void ncp5623_downward(uint8_t iend, uint8_t step);

#endif /* NCP5623_H_ */
