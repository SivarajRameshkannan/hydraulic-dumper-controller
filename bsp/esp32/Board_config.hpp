/*
 * Board_config.hpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */
#ifndef HAL_STM32F103C8T6_BOARD_CONFIG_HPP_
#define HAL_STM32F103C8T6_BOARD_CONFIG_HPP_

#if __cplusplus
extern "C"
{
#endif

#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"
#include "driver/gpio.h"
#include "driver/gpio.h"
#include "hal/gpio_types.h"

#if __cplusplus	
}
#endif

#include <cstdint>
#include "bsp_pwm_ctrl.hpp"

namespace BOARD_CONFIG
{
	
	constexpr gpio_num_t RELAY_GPIO = GPIO_NUM_2;
	
	inline gpio_config_t RELAY_CONFIG = 
	{
		.pin_bit_mask = (1ULL << RELAY_GPIO),
		.mode = GPIO_MODE_OUTPUT,
		.pull_up_en = GPIO_PULLUP_ENABLE,
		.pull_down_en = GPIO_PULLDOWN_DISABLE,
		.intr_type = GPIO_INTR_DISABLE
	};
	
};

#endif /* HAL_STM32F103C8T6_BOARD_CONFIG_HPP_ */
