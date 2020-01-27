#include "rsl1000.h"


static void UART_EventCallBack(uint32_t event);

static inline void Initialize_System(void)
{
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
}

 static inline void Initialize_Board(void)
 {
	 /* Setup DIO5 as a GPIO input with interrupts on transitions, DIO6 as a
	  * GPIO output. Use the integrated debounce circuit to ensure that only a
	  * single interrupt event occurs for each push of the pushbutton.
	  * The debounce circuit always has to be used in combination with the
	  * transition mode to deal with the debounce circuit limitations.
	  * A debounce filter time of 50 ms is used. */
	 Sys_DIO_Config(RSL1000_S2_BUTTON, DIO_MODE_GPIO_IN_0 | DIO_WEAK_PULL_UP |
					DIO_LPF_DISABLE);

	 Sys_DIO_IntConfig(0, DIO_EVENT_TRANSITION | DIO_SRC(RSL1000_S2_BUTTON) |
						   DIO_DEBOUNCE_ENABLE,
						   DIO_DEBOUNCE_SLOWCLK_DIV1024, 49);

	 Sys_DIO_Config(RSL1000_S3_BUTTON, DIO_MODE_GPIO_IN_0 | DIO_WEAK_PULL_UP |
							DIO_LPF_DISABLE);

	 Sys_DIO_Config(RSL1000_LED, DIO_MODE_GPIO_OUT_0);

#if defined(RSL1000_I2C)
	 /* Initialize I2C peripheral and reset bus */
	 RSL1000_I2C->Initialize(NULL);
	 RSL1000_I2C->PowerControl(ARM_POWER_FULL);
	 RSL1000_I2C->Control(ARM_I2C_BUS_SPEED, ARM_I2C_BUS_SPEED_STANDARD);
	 RSL1000_I2C->Control(ARM_I2C_BUS_CLEAR, 0);
#endif

#if defined(RSL1000_UART)
	 /* Initialize UART peripheral */
	 RSL1000_UART->Initialize(UART_EventCallBack);
	 RSL1000_UART->PowerControl(ARM_POWER_FULL);
	 RSL1000_UART->Control(ARM_USART_MODE_ASYNCHRONOUS |
	                   ARM_USART_FLOW_CONTROL_NONE |
	                   ARM_USART_DATA_BITS_8 |
	                   ARM_USART_PARITY_NONE |
	                   ARM_USART_STOP_BITS_1, RSL1000_UART_BAUDRATE);
#endif
 }

/* ----------------------------------------------------------------------------
 * Function      : void Initialize(void)
 * ----------------------------------------------------------------------------
 * Description   : Initialize the system by disabling interrupts, switching to
 *                 the 8 MHz clock (divided from the 48 MHz crystal) and
 *                 configuring the required DIOs to use the UART.
 * Inputs        : None
 * Outputs       : None
 * Assumptions   : None
 * ------------------------------------------------------------------------- */
void Initialize(void)
{
    /* Mask all interrupts */
    __set_PRIMASK(PRIMASK_DISABLE_INTERRUPTS);

    /* Disable all existing interrupts, clearing all pending source */
    Sys_NVIC_DisableAllInt();
    Sys_NVIC_ClearAllPendingInt();

    Initialize_System();
    Initialize_Board();

    /* Enable RSL1000_S2_BUTTON interrupt */
    NVIC_EnableIRQ(DIO0_IRQn);

    /* Stop masking interrupts */
    __set_PRIMASK(PRIMASK_ENABLE_INTERRUPTS);
    __set_FAULTMASK(FAULTMASK_ENABLE_INTERRUPTS);
}

void DIO0_IRQHandler(void)
{
    if (DIO_DATA->ALIAS[RSL1000_S2_BUTTON] == 1)
    {
        Sys_GPIO_Set_Low(RSL1000_LED);

    } else {
        Sys_GPIO_Set_High(RSL1000_LED);
    }
}

void UART_EventCallBack(uint32_t event)
{
    switch (event)
    {
        case ARM_USART_EVENT_RECEIVE_COMPLETE:
        {
            volatile int i;
            for(i = 0; i < 100; i++);
        }
        break;
        case ARM_USART_EVENT_SEND_COMPLETE:
        {
            volatile int i;
            for(i = 0; i < 100; i++);
        }
        break;
    }
}

/* main function */
int main(void)
{
  Initialize();
  /* I/O expander */
  pca9655_init(RSL1000_I2C, RSL1000_IOEXP_ADDRESS);
  pca9655_port_dir(RSL1000_IOEXP_LED_PORT, (uint8_t) ~RSL1000_IOEXP_LEDS_MASK);
  pca9655_port_set(RSL1000_IOEXP_LED_PORT, (uint8_t) ~RSL1000_IOEXP_LEDS_MASK);


  /* Accelerometer */
  lis3dh_init(RSL1000_I2C, 0x18);
  lis3dh_power(0x02, false, true, true, true);
  /* Ambient light sensor */
  //noa1305_init(RSL1000_I2C);

  /* RGB LED driver */
  ncp5623_init(RSL1000_I2C, 0x38);
  ncp5623_off();
  ncp5623_color(25,25,25);



  /* Infinite loop */
  uint8_t pv = RSL1000_IOEXP_LED2 | RSL1000_IOEXP_LED4;
  uint32_t divider;
  while (1)
  {
      if (DIO_DATA->ALIAS[RSL1000_S3_BUTTON])
          divider = SystemCoreClock;
      else
          divider = SystemCoreClock>>4;

      /* Blink LEDS */
      pca9655_port_set(RSL1000_IOEXP_LED_PORT, pv);
      if (pv&0x10) {
          pv <<= 1;
          ncp5623_downward(1, 3);
      } else {
          pv >>= 1;
          ncp5623_upward(31,3);
      }



      Sys_Watchdog_Refresh();
      Sys_Delay_ProgramROM(divider);
  }

}

