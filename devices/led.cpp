/*
 * led.cpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */

#include "led.hpp"
//#include "logger.hpp"

constexpr char led::TAG[];

void led::init(void) const
{
	gpio.init();
}

void led::on(void) const
{
	gpio.set_state(true);
}

void led::off(void) const
{
	gpio.set_state(false);
}

void led::toggle(void) 
{
	gpio.toggle_state();
}

