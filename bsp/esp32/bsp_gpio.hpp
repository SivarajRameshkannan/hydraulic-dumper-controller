/*
 * bsp_gpio.hpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */
#ifndef GPIO_HPP_
#define GPIO_HPP_

#if __cplusplus
extern "C"
{
#endif

#include "driver/gpio.h"
#include "hal_gpio.hpp"

#if __cplusplus	
}
#endif

#include <cstdint>

class bsp_GPIO : public hal_GPIO
{
    public:
		bsp_GPIO(gpio_num_t pin, gpio_config_t config) : pin(pin), config(config) {}
        ~bsp_GPIO() = default;

        void init(void) const override;
        bool get_state(void) const override;
        void set_state(bool) const override;
		void toggle_state(void) override;
        
		void enable_intr(void) const override;
		void disable_intr(void) const override;
		        
    protected:
         uint16_t get_pin(void) const {return pin; };
         uint16_t get_port(void) const; 
        
    private:
    	const gpio_num_t pin;
    	gpio_config_t config;
};


#endif /* GPIO_HPP_ */
