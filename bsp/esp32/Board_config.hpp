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

namespace BOARD_CONFIG
{
	constexpr gpio_num_t PWM_OUTPUT = GPIO_NUM_2;
    
    // Configure MCPWM
    inline mcpwm_config_t PWM_CONFIG = 
    {
		.frequency = 1000,
	    .cmpr_a = 0,              // Initial duty cycle = 0%
	    .cmpr_b = 0,
	    .duty_mode = MCPWM_DUTY_MODE_0,
	    .counter_mode = MCPWM_UP_COUNTER
	};
};

#endif /* HAL_STM32F103C8T6_BOARD_CONFIG_HPP_ */
