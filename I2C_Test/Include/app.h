/* ----------------------------------------------------------------------------
 * Copyright (c) 2019 Semiconductor Components Industries, LLC (d/b/a
 * ON Semiconductor), All Rights Reserved
 *
 * This code is the property of ON Semiconductor and may not be redistributed
 * in any form without prior written permission from ON Semiconductor.
 * The terms of use and warranty for this code are covered by contractual
 * agreements between ON Semiconductor and the licensee.
 *
 * This is Reusable Code.
 * ----------------------------------------------------------------------------
 * app.h
 * - Application header file for the RSL10 GPIO driver sample application
 * ------------------------------------------------------------------------- */

#ifndef APP_H
#define APP_H

/* ----------------------------------------------------------------------------
 * If building with a C++ compiler, make all of the definitions in this header
 * have a C binding.
 * ------------------------------------------------------------------------- */
#ifdef __cplusplus
extern "C"
{
#endif    /* ifdef __cplusplus */

/* ----------------------------------------------------------------------------
 * Include files
 * --------------------------------------------------------------------------*/
#include <RTE_Device.h>
#include <rsl10.h>
#include <GPIO_RSLxx.h>

/* ----------------------------------------------------------------------------
 * Defines
 * --------------------------------------------------------------------------*/
#if !RTE_GPIO
    #error "Please configure GPIO in RTE_Device.h"
#endif    /* if !RTE_USART0 */

/* DIO number that is used for easy re-flashing (recovery mode) */
#define RECOVERY_DIO                    12

/* GPIO definitions */
#define LED_DIO                         6
#define BUTTON_DIO                      5
#define TEST_DIO                        11


/* ----------------------------------------------------------------------------
 * Global variables and types
 * --------------------------------------------------------------------------*/
extern DRIVER_GPIO_t Driver_GPIO;

/* ---------------------------------------------------------------------------
* Function prototype definitions
* --------------------------------------------------------------------------*/
extern void Initialize(void);
void Button_EventCallback(uint32_t event);

/* ----------------------------------------------------------------------------
 * Close the 'extern "C"' block
 * ------------------------------------------------------------------------- */
#ifdef __cplusplus
}
#endif    /* ifdef __cplusplus */

#endif    /* APP_H */
