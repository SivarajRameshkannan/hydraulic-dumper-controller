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
#include "systick.hpp"

class cylinder
{
	public:
		cylinder(hal_PWM& pwm, relay& relay_up, relay& relay_down, button& limit_sw, SysTick& systick) 
		: 	_pwm(pwm), 
			_relay_up(relay_up), 
			_relay_down(relay_down), 
			_limit_sw(limit_sw),
			_systick(systick),
			_motion_state(motion_state::HOMING), 
			_prev_state(motion_state::IDLE),
			state_changed(false),
			motion_start_time(0)
			{}
			
		~cylinder() = default;

	    enum class motion_state
	    {
	        IDLE,
	        MOVING_UP,
	        MOVING_DOWN,
	        HOMING
	    };
		
		void init(void);
		void process(void);
		void move_up(void) { _motion_state = motion_state::MOVING_UP; }
		void move_down(void) { _motion_state = motion_state::MOVING_DOWN; }
		void move_stop(void) { _motion_state = motion_state::IDLE; }
		void move_home(void) { _motion_state = motion_state::HOMING; }
		
	private:
		static constexpr uint16_t MOTION_TIMEOUT_MS  = 4000U;
		
		hal_PWM& _pwm;
		relay& _relay_up;
		relay& _relay_down;
		button& _limit_sw;
		SysTick& _systick;
		
		motion_state _motion_state;
		motion_state _prev_state;		
		bool state_changed;
		
		uint64_t motion_start_time;
		
		void handle_move_up(void);
		void handle_move_down(void);
		void handle_move_home(void);
		void handle_move_stop(void);
		void handle_timeout(void);
};

#endif /* MANAGED_COMPONENTS_HCU_DEVICES_HYDRAULIC_CONTROLLER_HPP_ */
