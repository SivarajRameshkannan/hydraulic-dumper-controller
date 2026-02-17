/*
 * hal_pwm_ctrl.hpp
 *
 *  Created on: 17-Feb-2026
 *      Author: Sivaraj
 */

#ifndef MANAGED_COMPONENTS_HCU_HAL_HAL_PWM_CTRL_HPP_
#define MANAGED_COMPONENTS_HCU_HAL_HAL_PWM_CTRL_HPP_

#include <cstdio>

class hal_PWM
{
	public:
		hal_PWM() = default;
		virtual ~hal_PWM() = default;
		
		virtual void init(void) = 0;
		virtual void start(void) = 0;
		virtual void stop(void) = 0;
		virtual void set_period(uint16_t period) = 0;
		virtual void set_duty_cycle(uint16_t perc) = 0;
	private:
};

#endif /* MANAGED_COMPONENTS_HCU_HAL_HAL_PWM_CTRL_HPP_ */
