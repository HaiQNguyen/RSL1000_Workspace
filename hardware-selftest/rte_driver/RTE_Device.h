/* ----------------------------------------------------------------------------
 * Copyright (c) 2018 Semiconductor Components Industries, LLC (d/b/a
 * ON Semiconductor), All Rights Reserved
 *
 * This code is the property of ON Semiconductor and may not be redistributed
 * in any form without prior written permission from ON Semiconductor.
 * The terms of use and warranty for this code are covered by contractual
 * agreements between ON Semiconductor and the licensee.
 *
 * This is Reusable Code.
 *
 * ----------------------------------------------------------------------------
 * RTE_Device.h
 * - RTE Drivers configuration file. This file is used to enable/disable a
 *   certain driver and to configure the pin mapping for each interface.
 * ----------------------------------------------------------------------------
 * $Revision: 1.4 $
 * $Date: 2018/03/08 04:07:40 $
 * ------------------------------------------------------------------------- */

#ifndef RTE_DEVICE_H
#define RTE_DEVICE_H

/* <e> USART0 (Universal synchronous asynchronous receiver transmitter) [Driver_USART0]
 * <i> Configuration settings for Driver_USART0 in component ::CMSIS Driver:USART */
#define RTE_USART0                       1

/*   <o> USART0_TX Pin <0-15> */
#define RTE_USART0_TX_PIN                14

/*   <o> USART0_RX Pin <0-15> */
#define RTE_USART0_RX_PIN                13

/* </e> */

/* <e> SPI0 (Serial Peripheral Interface 0) [Driver_SPI0]
 * <i> Configuration settings for Driver_SPI0 in component ::CMSIS Driver:SPI */
#define RTE_SPI0                         0

/*   <o> SPI0_MOSI Pin <0-15> */
#define RTE_SPI0_MOSI_PIN                3

/*   <o> SPI0_MISO Pin <0-15> */
#define RTE_SPI0_MISO_PIN                2

/*   <o> SPI0_SSEL Pin <0-15> */
#define RTE_SPI0_SSEL_PIN                1

/*   <o> SPI0_SCLK Pin <0-15> */
#define RTE_SPI0_SCLK_PIN                0

/* <e> SPI1 (Serial Peripheral Interface 1) [Driver_SPI1]
 * <i> Configuration settings for Driver_SPI1 in component ::CMSIS Driver:SPI */
#define RTE_SPI1                         0

/*   <o> SPI1_MOSI Pin <0-15> */
#define RTE_SPI1_MOSI_PIN                15

/*   <o> SPI1_MISO Pin <0-15> */
#define RTE_SPI1_MISO_PIN                10

/*   <o> SPI1_SSEL Pin <0-15> */
#define RTE_SPI1_SSEL_PIN                13

/*   <o> SPI1_SCLK Pin <0-15> */
#define RTE_SPI1_SCLK_PIN                4

/* <e> I2C0 (Inter-integrated Circuit Interface 0)
 * <i> Configuration settings for Driver_I2C0 in component ::CMSIS Driver:I2C */
#define RTE_I2C0                         1

/*   <o> I2C0_SCL Pin <0-15> */
#define RTE_I2C0_SCL_PIN                 9

/*   <o> SPI1_SDA Pin <0-15> */
#define RTE_I2C0_SDA_PIN                 8

/*   <o> I2C0 DIO Low Pass Filter  <0=>DISABLED <1=>ENABLED */
#define RTE_I2C0_DIO_LPF_OPTION          1

/*   <o> I2C0 DIO Drive Strength  <0=>2X <1=>3X <2=>5X <3=>6X */
#define RTE_I2C0_DIO_DRIVE_OPTION        3

/*   <o> I2C0 DIO Pull Selection <0=>No pull <1=>Weak pull-up
 *                               <2=>Weak pull-down <3=>Strong pull-up */
#define RTE_I2C0_DIO_PULL_OPTION         3

/* Error checking for I2C0 configuration */
#if (RTE_I2C0 == 1)

#if ((RTE_I2C0_SCL_PIN == RTE_I2C0_SDA_PIN) || \
    (RTE_I2C0_SCL_PIN > 15) || (RTE_I2C0_SCL_PIN < 0) || \
    (RTE_I2C0_SDA_PIN > 15) || (RTE_I2C0_SDA_PIN < 0))
    #error "Invalid I2C0 pin configuration!"
#endif    /* if ((RTE_I2C0_SCL_PIN == RTE_I2C0_SDA_PIN) || (RTE_I2C0_SCL_PIN > 15) || (RTE_I2C0_SCL_PIN < 0) ||
           * (RTE_I2C0_SDA_PIN > 15) || (RTE_I2C0_SDA_PIN < 0)) */

#if (RTE_I2C0_DIO_LPF_OPTION == 0)
#define RTE_I2C0_DIO_LPF             DIO_LPF_DISABLE
#elif (RTE_I2C0_DIO_LPF_OPTION == 1)
#define RTE_I2C0_DIO_LPF             DIO_LPF_ENABLE
#else    /* if (RTE_I2C0_DIO_LPF_OPTION == 0) */
    #error "Invalid I2C0_DIO_LPF configuration!"
#endif    /* if (RTE_I2C0_DIO_LPF_OPTION == 0) */

#if    (RTE_I2C0_DIO_DRIVE_OPTION == 0)
#define RTE_I2C0_DIO_DRIVE           DIO_2X_DRIVE
#elif  (RTE_I2C0_DIO_DRIVE_OPTION == 1)
#define RTE_I2C0_DIO_DRIVE           DIO_3X_DRIVE
#elif  (RTE_I2C0_DIO_DRIVE_OPTION == 2)
#define RTE_I2C0_DIO_DRIVE           DIO_5X_DRIVE
#elif  (RTE_I2C0_DIO_DRIVE_OPTION == 3)
#define RTE_I2C0_DIO_DRIVE           DIO_6X_DRIVE
#else    /* if    (RTE_I2C0_DIO_DRIVE_OPTION == 0) */
    #error "Invalid I2C0_DIO_DRIVE configuration!"
#endif    /* if    (RTE_I2C0_DIO_DRIVE_OPTION == 0) */

#if    (RTE_I2C0_DIO_PULL_OPTION == 0)
#define RTE_I2C0_DIO_PULL            DIO_NO_PULL
#elif  (RTE_I2C0_DIO_PULL_OPTION == 1)
#define RTE_I2C0_DIO_PULL            DIO_WEAK_PULL_UP
#elif  (RTE_I2C0_DIO_PULL_OPTION == 2)
#define RTE_I2C0_DIO_PULL            DIO_WEAK_PULL_DOWN
#elif  (RTE_I2C0_DIO_PULL_OPTION == 3)
#define RTE_I2C0_DIO_PULL            DIO_STRONG_PULL_UP
#else    /* if    (RTE_I2C0_DIO_PULL_OPTION == 0) */
    #error "Invalid I2C0_DIO_PULL configuration!"
#endif    /* if    (RTE_I2C0_DIO_PULL_OPTION == 0) */

#endif    /* (RTE_I2C0 == 1) */

#endif    /* RTE_DEVICE_H */
