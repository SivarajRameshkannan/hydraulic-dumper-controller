/*
 * button.cpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */
#include "button.hpp"
#include "logger.hpp"

constexpr char button::TAG[];

void button::init(void)
{
    gpio.init();
    gpio.register_intr_cb(on_intr, (void*)this);
    gpio.enable_intr();
}

void button::on_intr(void* ctx)
{
    auto* self = static_cast<button*>(ctx);
    self->gpio.disable_intr();
    self->debounce_pending = true;
    self->debounce_start_time = self->systick.get_time_ms();
}

void button::process(void)
{
    if (!debounce_pending)
    {
        // If button is currently pressed, check duration
        if (!curr_state) // active low
        {
            uint32_t held_time = systick.get_time_ms() - press_start_time;
            if ((held_time > _long_press_period) && (btn_state != btn_States::LONG_PRESS))
            {
				btn_state = btn_States::LONG_PRESS;
            }
        }
        return;
    }

    // Debounce handling
    if ((systick.get_time_ms() - debounce_start_time) > _debounce_period)
    {
        bool reading = gpio.get_state();
        debounce_pending = false;

        if (reading != curr_state)
        {
            curr_state = reading;

            if (curr_state == !_active_low)   // pressed (active low)
            {
				btn_state = btn_States::PRESSED;
                press_start_time = systick.get_time_ms(); // start timing here
            }
            else
            {
                btn_state = btn_States::RELEASED;
            }
        }
        
        gpio.enable_intr();
    }
    
    handle_events();
}

button::btn_States button::read_state(void) const
{
	return btn_state;
}

void button::handle_events(void)
{
	callback cb = nullptr;
	void* ctx = nullptr;
	
	switch(read_state())
	{
		case btn_States::PRESSED:
			cb = cb_pressed;
			ctx = ctx_pressed;
			break;
		case btn_States::RELEASED:
			cb = cb_released;
			ctx = ctx_released;
			break;
		case btn_States::LONG_PRESS:
			cb = cb_long_pressed;
			ctx = ctx_long_pressed;
			break;
		default:
			break;	
	}
	
	if(cb)
	{
		cb(ctx);
	}
}