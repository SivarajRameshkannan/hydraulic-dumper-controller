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
	_relay.init();
	g_logger.info(TAG, "initialized");
}

void HCU::process(void)
{
	systick.delay_ms(500);
	_relay.on();
		
	g_logger.info(TAG, "Current Duty Cycle = %d", duty_cycle);
	
	systick.delay_ms(100);
	
	_relay.off();
}

void HCU::run(void)
{
    g_logger.info(TAG, "-----------------------------------------------running------------------------------------------------------\r\n");
    process();
}