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

};

#endif /* HAL_STM32F103C8T6_BOARD_CONFIG_HPP_ */
