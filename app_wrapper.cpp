/*
 * app_wrapper.cpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */
#include "button.hpp"
#include "hal_can.hpp"
#include "hal_pwm_ctrl.hpp"
#include "hcu.hpp"
#include "led.hpp"
#include "hal_gpio.hpp"

#include "bsp_gpio.hpp"
#include "bsp_can.hpp"
#include "Board_config.hpp"
#include "systick.hpp"

using namespace BOARD_CONFIG;

// LL drivers
static bsp_GPIO gpio_can_rx_led(CAN_RX_LED_GPIO, CAN_RX_LED_GPIO_GONFIG);


static SysTick SysTick;

// devices
static led led_can_rx(gpio_can_rx_led);

static HCU hcu_instance(led_can_rx, SysTick);

extern "C" void HCU_init_wrapper(void)
{
    hcu_instance.init();
}

extern "C" void HCU_run_wrapper(void)
{
	hcu_instance.run();
}
