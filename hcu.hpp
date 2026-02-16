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
        HCU(led& led, button& up, button& down, button& home, hal_CAN& can, SysTick& systick)
         : 	can_rx_led(led), 
        	btn_up(up), 
        	btn_down(down),
        	limit_sw_home(home),
        	systick(systick),
        	CM(can)
        	{}
        
        ~HCU(void)
        {
        };

		enum class DeviceStates : uint8_t
		{
			MOVING_UP = 0U,
			MOVING_DOWN,
			MOVING_HOME,
			IN_HOME,
			STOPPED,
			COUNT
		};
		
        void init(void) const;
        void run(void);

    private:
    	//constants
        static constexpr char TAG[] = "HCU";
        static constexpr uint8_t rx_led_time = 50U;
		static constexpr uint8_t CAN_QUEUE_SIZE = 10U;
	    static constexpr uint8_t FRAME_SIZE = static_cast<uint8_t>(commandFrame::Frame::COUNT);
		
		// control states
		DeviceStates curr_device_state;
		
		// devices
        led& can_rx_led;
        button& btn_up;
        button& btn_down;
        button& limit_sw_home;
                
        // services
        SysTick& systick; 
        commandFrame rxBuffer;
        Responseframe txBuffer;
	    CAN_Manager<CAN_QUEUE_SIZE, FRAME_SIZE> CM; 
		
        void process(void);
        
        // handle functions
        void handle_message(void);
        void handle_button_up(void);
        void handle_button_down(void);
        void handle_limit_sw_home(void);
        void handle_device_states(void);
        
        void handle_hydraulic_cmds(commandFrame::HydraulicCommands hC);
        void handle_sensor_request(Sensor::Types sT);
};


#endif /* HCU_HPP_ */
