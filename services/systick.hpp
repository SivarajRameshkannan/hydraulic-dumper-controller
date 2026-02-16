/*
 * delay.hpp
 *
 *  Created on: 09-Feb-2026
 *      Author: Sivaraj
 */

#ifndef APP_SERVICES_DELAY_HPP_
#define APP_SERVICES_DELAY_HPP_

#include "bsp_systick.hpp"
#include "hal_systick.hpp"
#include <cstdint>

class SysTick
{
	public:	
		SysTick() : obj(d) {}; 
		~SysTick() = default;
		
		void init(void)
		{
			obj.init();
		}

		void delay_ms(uint16_t ms) const
		{
			obj.sleep_ms(ms);
		}

		uint32_t get_time_ms() const
		{
			return obj.millis();
		}
		
	private:
		bsp_SYSTICK d;
		hal_SYSTICK& obj;
};

#endif /* APP_SERVICES_DELAY_HPP_ */
