/*
 * bsp_gpio.hpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */

#ifndef GPIO_HPP_
#define GPIO_HPP_

#include <cstdint>
#include "hal_gpio.hpp"

struct gpio_struct_t
{
    // internals may vary based on board
};

class bsp_GPIO : public hal_GPIO
{
    public:
		bsp_GPIO(gpio_struct_t g) : gpio_data(g) {}
        ~bsp_GPIO() = default;

        void init(void) const override
        {

        }

        bool get_state(void) const override
        {
        	return true;
        }

        void set_state(bool state) const override
        {
            (void)state;
        }

        void toggle_state(void) override
        {
            return;
        }

        void enable_intr(void) override
        {
            std::cout << "intruppt Enabled" << std::endl;
        }

        void disable_intr(void) override
        {
            std::cout << "intruppt Disabled" << std::endl;
        }

    protected:
        const uint16_t get_pin(void) const
        {
            return 0;
        }

        const uint16_t get_port(void) const
        {
            return 1;
        }

    private:
        gpio_struct_t gpio_data;
};

extern "C" void EXTI_Callback(void)
{
    // triggered by hardware
}

#endif /* GPIO_HPP_ */
