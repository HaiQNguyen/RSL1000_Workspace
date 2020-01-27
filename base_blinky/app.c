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
 *
 * ----------------------------------------------------------------------------
 * app.c
 *  - Simple example on how to use RSL10 gpio driver
 * ------------------------------------------------------------------------- */
#include <app.h>


/* Global variables */
DRIVER_GPIO_t *gpio;
ARM_DRIVER_USART *uart;
ARM_DRIVER_I2C *i2c;


void Delay_ms(uint32_t ms)
{
	Sys_Delay_ProgramROM((ms / 1000.0) * SystemCoreClock);
}

void Button_EventCallback(uint32_t event)
{
}

/* ----------------------------------------------------------------------------
 * Function      : void Button_EventCallback(void)
 * ----------------------------------------------------------------------------
 * Description   : This function is a callback registered by the function
 *                 Initialize. Based on event argument different actions are
 *                 executed.
 * Inputs        : None
 * Outputs       : None
 * Assumptions   : None
 * ------------------------------------------------------------------------- */
void Usart_EventCallBack(uint32_t event)
{
}

/* ----------------------------------------------------------------------------
 * Function      : void Initialize(void)
 * ----------------------------------------------------------------------------
 * Description   : Initialize the drivers.
 * Inputs        : None
 * Outputs       : None
 * Assumptions   : None
 * ------------------------------------------------------------------------- */
void Initialize(void)
{
    /* Mask all interrupts */
    __set_PRIMASK(PRIMASK_DISABLE_INTERRUPTS);

    /* Disable all existing interrupts, clear all pending source */
    Sys_NVIC_DisableAllInt();
    Sys_NVIC_ClearAllPendingInt();

    /* Test DIO12 to pause the program to make it easy to re-flash */
    DIO->CFG[RECOVERY_DIO] = DIO_MODE_INPUT  | DIO_WEAK_PULL_UP |
                             DIO_LPF_DISABLE | DIO_6X_DRIVE;
    while (DIO_DATA->ALIAS[RECOVERY_DIO] == 0);

    /* Prepare the 48 MHz crystal
	  * Start and configure VDDRF */
	 ACS_VDDRF_CTRL->ENABLE_ALIAS = VDDRF_ENABLE_BITBAND;
	 ACS_VDDRF_CTRL->CLAMP_ALIAS  = VDDRF_DISABLE_HIZ_BITBAND;

	 /* Wait until VDDRF supply has powered up */
	 while (ACS_VDDRF_CTRL->READY_ALIAS != VDDRF_READY_BITBAND);

	 /* Enable RF power switches */
	 SYSCTRL_RF_POWER_CFG->RF_POWER_ALIAS   = RF_POWER_ENABLE_BITBAND;

	 /* Remove RF isolation */
	 SYSCTRL_RF_ACCESS_CFG->RF_ACCESS_ALIAS = RF_ACCESS_ENABLE_BITBAND;

	 /* Start the 48 MHz oscillator without changing the other register bits */
	 RF->XTAL_CTRL = ((RF->XTAL_CTRL & ~XTAL_CTRL_DISABLE_OSCILLATOR) |
					  XTAL_CTRL_REG_VALUE_SEL_INTERNAL);

	 /* Enable 48 MHz oscillator divider at desired prescale value */
	 RF_REG2F->CK_DIV_1_6_CK_DIV_1_6_BYTE = CK_DIV_1_6_PRESCALE_1_BYTE;

	 /* Wait until 48 MHz oscillator is started */
	 while (RF_REG39->ANALOG_INFO_CLK_DIG_READY_ALIAS !=
			ANALOG_INFO_CLK_DIG_READY_BITBAND);

	 /* Switch to 48 MHz oscillator clock */
	 Sys_Clocks_SystemClkConfig(JTCK_PRESCALE_1   |
								EXTCLK_PRESCALE_1 |
								SYSCLK_CLKSRC_RFCLK);

	/* Disable unused JTAG Pin */
	 DIO_JTAG_SW_PAD_CFG->CM3_JTAG_DATA_EN_ALIAS = 0;

    /* Initialize GPIO structure */
    gpio = &Driver_GPIO;

    /* Initialize GPIO driver */
    gpio->Initialize(Button_EventCallback);

    /* Initialize usart driver structure */
   uart = &Driver_USART0;

	/* Initialize usart, register callback function */

	uart->Initialize(Usart_EventCallBack);
	uart->PowerControl(ARM_POWER_FULL);
	uart->Control(ARM_USART_MODE_ASYNCHRONOUS |
			ARM_USART_FLOW_CONTROL_NONE |
			ARM_USART_DATA_BITS_8 |
			ARM_USART_PARITY_NONE |
			ARM_USART_STOP_BITS_1, 115200);


	i2c = &Driver_I2C0;

	i2c->Initialize(NULL);
	i2c->PowerControl(ARM_POWER_FULL);
	i2c->Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_STANDARD);
	i2c->Control(ARM_I2C_BUS_CLEAR, 0);

    /* Stop masking interrupts */
    __set_PRIMASK(PRIMASK_ENABLE_INTERRUPTS);
    __set_FAULTMASK(FAULTMASK_ENABLE_INTERRUPTS);
}

/* ----------------------------------------------------------------------------
 * Function      : int main(void)
 * ----------------------------------------------------------------------------
 * Description   : Initialize the drivers. Configure the button interrupt
 *                 and toggles led pin on button press.
 * Inputs        : None
 * Outputs       : None
 * Assumptions   : None
 * ------------------------------------------------------------------------- */
int main(void)
{
	char tx[] = "Hello World\n";
    /* Initialize the system */
    Initialize();

    /* RGB LED driver */


    /* Spin loop */
    while (true)
    {
        /* Refresh Watchdog */
        Sys_Watchdog_Refresh();
        uart->Send(tx, 12); /* start transmission */
        gpio->ToggleValue(LED_DIO);
        Delay_ms(100);
    }
}
