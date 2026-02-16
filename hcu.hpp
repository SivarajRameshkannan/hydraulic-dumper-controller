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
        HCU(led& led, SysTick& systick)
         : 	can_rx_led(led), 
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
        led& can_rx_led;
                
        // services
        SysTick& systick; 
		
        void process(void);
        
        // handle functions
        void handle_message(void);
        
        void handle_hydraulic_cmds(commandFrame::HydraulicCommands hC);
        void handle_sensor_request(Sensor::Types sT);
};


#endif /* HCU_HPP_ */
