/*
 * hcu.cpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */
#include "hcu.hpp"
#include "button.hpp"
#include "command_frame.hpp"
#include "hal_can.hpp"
#include "hal_pwm_ctrl.hpp"
#include "led.hpp"
#include "logger.hpp"

void HCU::init(void) const
{
	pwm.init();
	g_logger.info(TAG, "initialized");
}

void HCU::process(void)
{	
	if(duty_cycle > 99)
	{
		dir = false;
		pwm.start();
	}
	
	if(duty_cycle < 1)
	{
		dir = true;
		pwm.stop();
	}
	
	if(dir)
	{
		duty_cycle += 1;
	}
	else 
	{
		duty_cycle -= 1;
	}
	
	pwm.set_duty_cycle(duty_cycle, hal_PWM::PAIR::A);
	g_logger.info(TAG, "Current Duty Cycle = %d", duty_cycle);
	
	systick.delay_ms(20);
}

void HCU::run(void)
{
    g_logger.info(TAG, "-----------------------------------------------running------------------------------------------------------\r\n");
    process();
}