/*
 * button.hpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */
 
#ifndef DEVICES_BUTTON_HPP_
#define DEVICES_BUTTON_HPP_

#include "hal_gpio.hpp"
#include "systick.hpp"
#include <atomic>

class button
{
public:
    button(hal_GPIO& gpio, SysTick& systick, uint8_t debounce_period = 50U, uint16_t long_press_period = 3000U, bool active_low = true)
        : gpio(gpio),
          systick(systick),
          curr_state(this->gpio.get_state()),
          _debounce_period(debounce_period),
          _long_press_period(long_press_period),
          _active_low(active_low),
          debounce_pending(false),
          debounce_start_time(0),
          press_start_time(0),
		  btn_state(btn_States::RELEASED)
    {
	}
	
	~button(void) = default;
	
	enum class btn_States : uint8_t
	{
		PRESSED = 0U,
		RELEASED,
		LONG_PRESS
	};

    void init(void);
    void process(void);
    btn_States read_state(void) const;
    static void on_intr(void* ctx);

private:
    hal_GPIO& gpio;
    SysTick& systick;

    bool curr_state;
    
    const uint8_t _debounce_period;
    const uint16_t _long_press_period;
    const bool _active_low;
    
    std::atomic<bool> debounce_pending;
    std::atomic<uint64_t> debounce_start_time;
	std::atomic<uint64_t> press_start_time;
	
	std::atomic<btn_States> btn_state;
	
    static constexpr char TAG[] = "button";
};


#endif /* DEVICES_BUTTON_HPP_ */
