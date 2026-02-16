/*
 * app_wrapper.cpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */
#include "button.hpp"
#include "hal_can.hpp"
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
static bsp_GPIO gpio_up_button(UP_BUTTON_GPIO, UP_BUTTON_GPIO_GONFIG);
static bsp_GPIO gpio_down_button(UP_BUTTON_GPIO, UP_BUTTON_GPIO_GONFIG);
static bsp_GPIO gpio_home(UP_BUTTON_GPIO, UP_BUTTON_GPIO_GONFIG);
static bsp_CAN  CAN;

static SysTick SysTick;

// devices
static led led_can_rx(gpio_can_rx_led);
static button btn_up(gpio_up_button, SysTick);
static button btn_down(gpio_down_button, SysTick);
static button limit_sw_home(gpio_home, SysTick);

static HCU hcu_instance(led_can_rx, btn_up, btn_down, limit_sw_home, CAN, SysTick);

extern "C" void HCU_init_wrapper(void)
{
    hcu_instance.init();
}

extern "C" void HCU_run_wrapper(void)
{
	hcu_instance.run();
}
