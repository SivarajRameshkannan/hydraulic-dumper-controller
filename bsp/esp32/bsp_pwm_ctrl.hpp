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

struct pwm_struct
{
	gpio_num_t pin_a;
	mcpwm_io_signals_t io_a;
	
	gpio_num_t pin_b;
	mcpwm_io_signals_t io_b;
	
	mcpwm_unit_t unit;
	mcpwm_timer_t source;
	
	mcpwm_config_t config;
};

class bsp_PWM : public hal_PWM
{
	public:
		bsp_PWM(pwm_struct pwm_info) : _pwm_info(pwm_info) {};
		~bsp_PWM() = default;
		
		void init(void) override
		{
			mcpwm_gpio_init(_pwm_info.unit, _pwm_info.io_a, _pwm_info.pin_a);
			mcpwm_init(_pwm_info.unit, _pwm_info.source, &_pwm_info.config);
		}
		
		void start(void) override
		{
			mcpwm_start(_pwm_info.unit, _pwm_info.source);
		}
		
		void stop(void) override
		{
			mcpwm_stop(_pwm_info.unit, _pwm_info.source);
		}
		
		void set_period(uint16_t period) override
		{
			mcpwm_set_frequency(_pwm_info.unit, _pwm_info.source, period);
		}
		
		void set_duty_cycle(uint8_t perc, PAIR p) override
		{
			mcpwm_generator_t oper = MCPWM_OPR_A;
			if(p == PAIR::B) oper = MCPWM_OPR_B;

			mcpwm_set_duty(_pwm_info.unit, _pwm_info.source, oper, perc);
		}	
		
	private:
		pwm_struct _pwm_info;
};

#endif /* MANAGED_COMPONENTS_HCU_BSP_ESP32_BSP_PWM_CTRL_HPP_ */
