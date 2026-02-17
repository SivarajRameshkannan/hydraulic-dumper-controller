/*
 * bsp_pwm_ctrl.hpp
 *
 *  Created on: 17-Feb-2026
 *      Author: tz
 */

#ifndef MANAGED_COMPONENTS_HCU_BSP_ESP32_BSP_PWM_CTRL_HPP_
#define MANAGED_COMPONENTS_HCU_BSP_ESP32_BSP_PWM_CTRL_HPP_

class bsp_PWM : public hal_PWM
{
	public:
		bsp_PWM() = default;
		~bsp_PWM() = default;
		
		void init(void) override
		{
			
		}
		
		void start(void) override
		{
			
		}
		
		void stop(void) override
		{
			
		}
		
		void set_period(uint16_t period) override
		{
			
		}
		
		void set_duty_cycle(uint16_t perc) override
		{
			
		}	
		
	private:
};

#endif /* MANAGED_COMPONENTS_HCU_BSP_ESP32_BSP_PWM_CTRL_HPP_ */
