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
#include "led.hpp"
#include "logger.hpp"

void HCU::init(void) const
{
	can_rx_led.init();
	
	btn.init();	
	btn.register_btn_callback(HCU::pressed, (void*) this, button::btn_States::PRESSED);
	btn.register_btn_callback(HCU::released, (void*) this, button::btn_States::RELEASED);
	btn.register_btn_callback(HCU::long_press, (void*) this, button::btn_States::LONG_PRESS);
	g_logger.info(TAG, "initialized");
} 

void HCU::process(void)
{
	btn.process();
	systick.delay_ms(300);
}

void HCU::pressed(void* ctx)
{
	auto* self = static_cast<HCU*>(ctx);
	self->can_rx_led.on();
	g_logger.info(TAG, "button pressed");	
}

void HCU::released(void* ctx)
{
	auto* self = static_cast<HCU*>(ctx);
	self->can_rx_led.off();
	g_logger.info(TAG, "button released");	
}

void HCU::long_press(void* ctx)
{
	auto* self = static_cast<HCU*>(ctx);
	self->can_rx_led.off();
	g_logger.info(TAG, "button long press detected");
}


void HCU::run(void)
{
    g_logger.info(TAG, "-----------------------------------------------running------------------------------------------------------\r\n");
    process();
}