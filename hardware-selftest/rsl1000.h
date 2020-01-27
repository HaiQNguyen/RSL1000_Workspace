
#ifndef RSL1000_H_
#define RSL1000_H_

#include <rsl10.h>
#include <rte_driver/I2C_RSLxx.h>
#include <rte_driver/USART_RSLxx.h>
#include "pca9655.h"
#include "ncp5623.h"
#include "noa1305.h"
#include "lis3dh.h"

#define CONCAT(x, y)            x##y
#define DIO_SRC(x)              CONCAT(DIO_SRC_DIO_, x)

/* On board LED and button definitions */
#define RSL1000_LED	            6  /* DIO6_LED */
#define RSL1000_S2_BUTTON       5  /* DIO5_BTN */
#define RSL1000_S3_BUTTON       12 /* DIO12_BTN */

/* IO Expander I2C address */
#define RSL1000_IOEXP_ADDRESS   0x20

/* IO Expander LEDs */
#define RSL1000_IOEXP_LED_PORT  1
#define RSL1000_IOEXP_LEDS_MASK 0xF0
#define RSL1000_IOEXP_LED1      0x80
#define RSL1000_IOEXP_LED2      0x40
#define RSL1000_IOEXP_LED3      0x20
#define RSL1000_IOEXP_LED4      0x10

/* I2C bus instance. For pin configuration refer RTE_Device.h  */
#if (RTE_I2C0 == 1)
    extern ARM_DRIVER_I2C       Driver_I2C0;
#   define RSL1000_I2C          (&Driver_I2C0)
#endif

/* UART bus instance. For pin configuration refer RTE_Device.h  */
#if (RTE_USART0 == 1)
    extern ARM_DRIVER_USART	        Driver_USART0;
#   define RSL1000_UART	            (&Driver_USART0)
#   define RSL1000_UART_BAUDRATE    115200
#endif

#endif /* RSL1000_H_ */
