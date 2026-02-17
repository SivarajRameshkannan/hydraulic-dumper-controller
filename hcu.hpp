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
#include "hal_pwm_ctrl.hpp"
#include "led.hpp"
#include "hal_timer.hpp"
#include "command_frame.hpp"
#include "response_frame.hpp"
#include "systick.hpp"

class HCU
{
    public:
        HCU(hal_PWM& _pwm, SysTick& systick)
         : 	pwm(_pwm), 
        	duty_cycle(0U),
        	dir(true),
        	systick(systick)
        	{}
        
        ~HCU(void)
        {
        };

        void init(void) const;
        void run(void);

    private:
    	//constants
        static constexpr char TAG[] = "HCU";
        static constexpr uint8_t rx_led_time = 50U;
		static constexpr uint8_t CAN_QUEUE_SIZE = 10U;
	    static constexpr uint8_t FRAME_SIZE = static_cast<uint8_t>(commandFrame::Frame::COUNT);
		
		
		// devices
        hal_PWM& pwm;
        uint8_t duty_cycle;
        bool dir;
                
        // services
        SysTick& systick; 
		
        void process(void);
};


#endif /* HCU_HPP_ */
