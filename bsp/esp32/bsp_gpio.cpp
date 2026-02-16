/*
 * gpio.cpp
 *
 *  Created on: 09-Feb-2026
 *      Author: Sivaraj
 */

#include <cstdint>

#if __cplusplus
extern "C"
{
#endif

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#if __cplusplus	
}
#endif

#include "bsp_gpio.hpp"

extern "C" void IRAM_ATTR gpio_isr_handler(void *arg)
{
    auto* self = static_cast<bsp_GPIO*>(arg);
    self->_onInterrupt();
}

void bsp_GPIO::init(void) const
{
    gpio_config(&config);	

	if(config.intr_type != GPIO_INTR_DISABLE)
	{
	    // Install ISR service
	    gpio_install_isr_service(0);
	
	    // Attach ISR handler
	    gpio_isr_handler_add(pin, gpio_isr_handler, (void*)this); 	 	
	}
}

bool bsp_GPIO::get_state(void) const
{
	return static_cast<bool>(gpio_get_level(pin));	
}

void bsp_GPIO::set_state(bool state) const
{
	gpio_set_level(pin, static_cast<uint32_t>(state));
}

void bsp_GPIO::toggle_state(void) 
{
	if(config.mode != GPIO_MODE_INPUT_OUTPUT)
	{
		config.mode = GPIO_MODE_INPUT_OUTPUT;
		init();
	}
	
	bool curr = get_state();
	set_state(!curr);
}

void bsp_GPIO::enable_intr(void) const
{
	gpio_intr_enable(static_cast<gpio_num_t>(get_pin()));
};

void bsp_GPIO::disable_intr(void) const
{
	gpio_intr_disable(static_cast<gpio_num_t>(get_pin()));
};

