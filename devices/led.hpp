/*
 * led.hpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */
#ifndef DEVICES_LED_HPP_
#define DEVICES_LED_HPP_

#include "hal_gpio.hpp"

class led
{
    public:
        explicit led(hal_GPIO& g) : gpio(g) {}
        ~led(void) = default;

        void init(void) const;
        void on(void) const;
        void off(void) const;
        void toggle(void);

    private:
        hal_GPIO& gpio;
        static constexpr char TAG[] = "LED";
};

#endif /* DEVICES_LED_HPP_ */
