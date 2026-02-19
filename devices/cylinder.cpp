/*
 * cylinder.cpp
 *
 *  Created on: 19-Feb-2026
 *      Author: tz
 */
#include "cylinder.hpp"

void cylinder::process(void)
{
	state_changed = (_prev_state != _motion_state);
	_prev_state = _motion_state;
	
	switch(_motion_state)
	{
		case motion_state::MOVING_UP:
			handle_move_up();			
			break;
		case motion_state::MOVING_DOWN:
			handle_move_down();
			break;
		case motion_state::HOMING:
			handle_move_home();
			break;
		case motion_state::IDLE:
		default:
			handle_move_stop();
			break;
	}
}

void cylinder::handle_move_up(void)
{
	if(!state_changed) return;
	
    _relay_down.off();
    _pwm.set_duty_cycle(50U, hal_PWM::PAIR::A);
    _pwm.start();
    _relay_up.on();
}

void cylinder::handle_move_down(void)
{
	if(!state_changed) return;
	
    _relay_up.off();
    _pwm.set_duty_cycle(100U, hal_PWM::PAIR::A);
    _pwm.start();
    _relay_down.on();			
}

void cylinder::handle_move_home(void)
{
	if(state_changed)
	{
	    _relay_up.off();
	    _pwm.set_duty_cycle(100U, hal_PWM::PAIR::A);
	    _pwm.start();
	    _relay_down.on();					
	}
	
	if(_limit_sw.read_state() != button::btn_States::RELEASED)
	{
		_motion_state = motion_state::IDLE;
		return;
	};
}

void cylinder::handle_move_stop(void)
{	
	if(!state_changed) return;
	
    _pwm.stop();
    _relay_up.off();
    _relay_down.off();
}
