/*
 * relay.hpp
 *
 *  Created on: 18-Feb-2026
 *      Author: Sivaraj
 */

#ifndef HCU_DEVICES_RELAY_HPP_
#define HCU_DEVICES_RELAY_HPP_

#include "hal_gpio.hpp"

class relay
{
	public:
		relay(hal_GPIO& gpio, bool active_low = false) : _active_low(active_low), _gpio(gpio) {};
		~relay() = default;	
		
		void init(void)
		{
			// relay initialization
			_gpio.init();
		}
		
		void on(void)
		{
			if(_active_low)
			{
				_gpio.set_state(false);
				return;
			}
			
			_gpio.set_state(true);
		}
		
		void off(void)
		{
			if(_active_low)
			{
				_gpio.set_state(true);
				return;
			}
			
			_gpio.set_state(false);			
		}
		
	private:
		bool _active_low;
		hal_GPIO& _gpio;
};

#endif /* MANAGED_COMPONENTS_HCU_DEVICES_RELAY_HPP_ */
