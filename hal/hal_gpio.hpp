/*
 * hal_gpio.hpp
 *
 *  Created on: 11-Feb-2026
 *      Author: Sivaraj
 */

#ifndef APP_HAL_HAL_GPIO_HPP_
#define APP_HAL_HAL_GPIO_HPP_

#include "hal_Intr.hpp"

class hal_GPIO : public hal_Intruppt
{
	public:
		hal_GPIO() {}
        virtual ~hal_GPIO() = default;
		
        virtual void init(void) const = 0;
        virtual bool get_state(void) const = 0;
        virtual void set_state(bool) const = 0;
        virtual void toggle_state(void) = 0;
        
	private:
};


#endif /* APP_HAL_HAL_GPIO_HPP_ */
