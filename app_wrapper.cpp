/*
 * app_wrapper.cpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */
#include "bsp_gpio.hpp"
#include "button.hpp"
#include "hal_pwm_ctrl.hpp"
#include "hcu.hpp"
#include "led.hpp"

#include "bsp_pwm_ctrl.hpp"
#include "systick.hpp"
#include "Board_config.hpp"

using namespace BOARD_CONFIG;

// LL drivers
static bsp_GPIO relay_gpio(RELAY_GPIO, RELAY_CONFIG);
static relay relay_module(relay_gpio, true);

static SysTick SysTick;

// devices

static HCU hcu_instance(relay_module, SysTick);

extern "C" void HCU_init_wrapper(void)
{
    hcu_instance.init();
}

extern "C" void HCU_run_wrapper(void)
{
	hcu_instance.run();
}
