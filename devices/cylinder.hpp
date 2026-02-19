/*
 * hydraulic_controller.hpp
 *
 *  Created on: 18-Feb-2026
 *      Author: Sivaraj
 */

#ifndef HCU_DEVICES_HYDRAULIC_CONTROLLER_HPP_
#define HCU_DEVICES_HYDRAULIC_CONTROLLER_HPP_

#include "hal_pwm_ctrl.hpp"
#include "relay.hpp"

class cylinder
{
	public:
		cylinder(hal_PWM& pwm, relay& relay_up, relay& relay_down) : _pwm(pwm), _relay_up(relay_up), _relay_down(relay_down) {}
		~cylinder() = default;
		
		void init(void)
		{
			_pwm.init();
			_relay_up.init();
			_relay_down.init();
			
			_pwm.set_period(1000U);
		}
		
		void move_up(void)
		{
			_pwm.set_duty_cycle(50U, hal_PWM::PAIR::A);
			_pwm.start();
			_relay_up.on();
		}
		
		void move_down(void)
		{
			_pwm.set_duty_cycle(100U, hal_PWM::PAIR::A);
			_pwm.start();			
			_relay_down.on();			
		}
		
		void move_home(void)
		{
			// TO DO: add home detection in this scope.
			_pwm.set_duty_cycle(100U, hal_PWM::PAIR::A);
			_relay_down.on();			
		}
		
		void move_stop(void)
		{
			_pwm.stop();			
			_relay_down.off();
			_relay_up.off();
		}
		
	private:
		hal_PWM& _pwm;
		relay& _relay_up;
		relay& _relay_down;
};

#endif /* MANAGED_COMPONENTS_HCU_DEVICES_HYDRAULIC_CONTROLLER_HPP_ */
