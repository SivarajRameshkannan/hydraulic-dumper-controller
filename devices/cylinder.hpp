/*
 * hydraulic_controller.hpp
 *
 *  Created on: 18-Feb-2026
 *      Author: Sivaraj
 */

#ifndef HCU_DEVICES_HYDRAULIC_CONTROLLER_HPP_
#define HCU_DEVICES_HYDRAULIC_CONTROLLER_HPP_

#include "button.hpp"
#include "hal_pwm_ctrl.hpp"
#include "relay.hpp"

class cylinder
{
	public:
		cylinder(hal_PWM& pwm, relay& relay_up, relay& relay_down, button& limit_sw) 
		: 	_pwm(pwm), 
			_relay_up(relay_up), 
			_relay_down(relay_down), 
			_limit_sw(limit_sw),
			_motion_state(motion_state::IDLE), 
			_prev_state(motion_state::IDLE)
			{}
			
		~cylinder() = default;

	    enum class motion_state
	    {
	        IDLE,
	        MOVING_UP,
	        MOVING_DOWN,
	        HOMING
	    };
		
		void init(void)
		{
			_pwm.init();
			_relay_up.init();
			_relay_down.init();
			
			_pwm.set_period(1000U);
			_pwm.stop();
		}
		
		void process(void);
		void move_up(void) { _motion_state = motion_state::MOVING_UP; }
		void move_down(void) { _motion_state = motion_state::MOVING_DOWN; }
		void move_stop(void) { _motion_state = motion_state::IDLE; }
		void move_home(void) { _motion_state = motion_state::HOMING; }
		
	private:
		hal_PWM& _pwm;
		relay& _relay_up;
		relay& _relay_down;
		button& _limit_sw;
		
		motion_state _motion_state;
		motion_state _prev_state;
		bool state_changed;
		
		void handle_move_up(void);
		void handle_move_down(void);
		void handle_move_home(void);
		void handle_move_stop(void);
};

#endif /* MANAGED_COMPONENTS_HCU_DEVICES_HYDRAULIC_CONTROLLER_HPP_ */
