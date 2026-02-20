/*
 * hcu.hpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */

#ifndef HCU_HPP_
#define HCU_HPP_

#include "button.hpp"
#include "can_manager.hpp"
#include "hal_can.hpp"
#include "led.hpp"
#include "hal_timer.hpp"
#include "command_frame.hpp"
#include "response_frame.hpp"
#include "systick.hpp"

class HCU
{
    public:
        HCU(led& led, button& up, SysTick& systick)
         : 	can_rx_led(led), 
        	btn(up), 
        	systick(systick)
        	{}
        
        ~HCU(void)
        {
        };

        void init(void) const;
        void run(void);

        static void pressed(void* ctx);
        static void released(void* ctx);
        static void long_press(void* ctx);
        
    private:
    	//constants
        static constexpr char TAG[] = "HCU";
        static constexpr uint8_t rx_led_time = 50U;
		static constexpr uint8_t CAN_QUEUE_SIZE = 10U;
	    static constexpr uint8_t FRAME_SIZE = static_cast<uint8_t>(commandFrame::Frame::COUNT);
		
		
		// devices
        led& can_rx_led;
        button& btn;
                
        // services
        SysTick& systick; 
        commandFrame rxBuffer;
        Responseframe txBuffer;
		
        void process(void);
};


#endif /* HCU_HPP_ */
