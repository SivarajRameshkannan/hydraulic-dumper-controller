/*
 * bsp_pwm_ctrl.hpp
 *
 *  Created on: 17-Feb-2026
 *      Author: Sivaraj
 */

#ifndef HCU_BSP_ESP32_BSP_PWM_CTRL_HPP_
#define HCU_BSP_ESP32_BSP_PWM_CTRL_HPP_

#if __cplusplus
extern "C"
{
#endif

#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"
#include "driver/gpio.h"

#if __cplusplus	
}
#endif

class bsp_PWM : public hal_PWM
{
	public:
		bsp_PWM(gpio_num_t pin, mcpwm_config_t pwm_config) : _pin(pin), _pwm_config(pwm_config) {};
		~bsp_PWM() = default;
		
		void init(void) override
		{
			mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, _pin);
			mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &_pwm_config);
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
		
		void set_duty_cycle(uint8_t perc) override
		{
			mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, perc);
		}	
		
	private:
		const gpio_num_t _pin;
		mcpwm_config_t _pwm_config;
};

#endif /* MANAGED_COMPONENTS_HCU_BSP_ESP32_BSP_PWM_CTRL_HPP_ */
