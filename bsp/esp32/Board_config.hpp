/*
 * Board_config.hpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */
#ifndef HAL_STM32F103C8T6_BOARD_CONFIG_HPP_
#define HAL_STM32F103C8T6_BOARD_CONFIG_HPP_

#include <cstdint>
#include "driver/gpio.h"
#include "hal/gpio_types.h"
#include "bsp_pwm_ctrl.hpp"

namespace BOARD_CONFIG
{
	constexpr gpio_num_t CAN_RX_LED_GPIO 	= GPIO_NUM_2;
	constexpr gpio_num_t UP_BUTTON_GPIO		= GPIO_NUM_0;

    inline gpio_config_t CAN_RX_LED_GPIO_GONFIG = {
        .pin_bit_mask = (1ULL << CAN_RX_LED_GPIO),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    inline gpio_config_t UP_BUTTON_GPIO_GONFIG = {
        .pin_bit_mask = (1ULL << UP_BUTTON_GPIO),
        .mode = GPIO_MODE_INPUT, 
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_ANYEDGE
    };

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
