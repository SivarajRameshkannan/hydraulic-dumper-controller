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
    inline pwm_struct PWM_INFO = 
    {
		.pin_a = GPIO_NUM_2,
		.io_a = MCPWM0A,
		.pin_b = GPIO_NUM_NC,
		.io_b = MCPWM0A,

		.unit = MCPWM_UNIT_0,	 
		.source = MCPWM_TIMER_0,

        .config = {
            1000,              // frequency
            0,                 // cmpr_a
            0,                 // cmpr_b
            MCPWM_DUTY_MODE_0, // duty_mode
            MCPWM_UP_COUNTER   // counter_mode
        },
	};
    
};

#endif /* HAL_STM32F103C8T6_BOARD_CONFIG_HPP_ */
