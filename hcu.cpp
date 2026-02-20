/*
 * hcu.cpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */
#include "hcu.hpp"
#include "button.hpp"
#include "command_frame.hpp"
#include "can_manager.hpp"
#include "hal_can.hpp"
#include "led.hpp"
#include "logger.hpp"

void HCU::init(void)
{
	can_rx_led.init();
	
	btn_up.init();
	btn_down.init();
	_cylinder.init();
	CM.init();
	
	systick.delay_ms(100);
	
	g_logger.info(TAG, "initialized");
}

void HCU::process(void)
{
	btn_up.process();
	btn_down.process();
	_cylinder.process();
	CM.process();
	
	handle_message();
	handle_button_up();
	handle_button_down();
	
	handle_events();
	
	handle_device_states();
	
	systick.delay_ms(10);
}

void HCU::handle_events(void)
{
	if(curr_device_state == DeviceStates::MOVING_HOME)
	{
	    if(btn_requested_state == DeviceStates::STOPPED ||
	       can_requested_state == DeviceStates::STOPPED)
	    {
	        curr_device_state = DeviceStates::STOPPED;
	    }
	    return;
	}
	
	if(btn_requested_state != DeviceStates::NONE)
	{
		curr_device_state = btn_requested_state;
		btn_requested_state = DeviceStates::NONE;
		can_requested_state = DeviceStates::NONE;
		return;
	}
	
	if(can_requested_state != DeviceStates::NONE)
	{
		curr_device_state = can_requested_state;
		can_requested_state = DeviceStates::NONE;	
	}
}

void HCU::handle_device_states(void)
{
	switch(curr_device_state)
	{
		case DeviceStates::MOVING_UP:
			handle_moving_up();
			break;
		case DeviceStates::MOVING_DOWN:
			handle_moving_down();
			break;
		case DeviceStates::MOVING_HOME:
			handle_moving_home();
			break;
		case DeviceStates::IN_HOME:
			handle_in_home();
			break;
		case DeviceStates::STOPPED:
			handle_stopped();
			break;
		default:
			break;
	}
}

void HCU::handle_button_up(void)
{
	button::btn_States state = btn_up.read_state();
		
	switch(state)
	{
		case button::btn_States::PRESSED:
			btn_requested_state = DeviceStates::MOVING_UP;
			break;
		case button::btn_States::RELEASED:
			btn_requested_state = DeviceStates::STOPPED;
			break;
		case button::btn_States::LONG_PRESS:
			btn_requested_state = DeviceStates::MOVING_DOWN;
			break;
		default:
			break;
	}
}

void HCU::handle_button_down(void)
{
	button::btn_States state = btn_down.read_state();

	switch(state)
	{
		case button::btn_States::PRESSED:
			btn_requested_state = DeviceStates::MOVING_DOWN;
			break;
		case button::btn_States::RELEASED:
			btn_requested_state = DeviceStates::STOPPED;
			break;
		case button::btn_States::LONG_PRESS:
			btn_requested_state = DeviceStates::MOVING_DOWN;
			break;
		default:
			break;
	}
}

void HCU::handle_message(void)
{
	if(CM.read_msg(rxBuffer.get_buffer_addr()) == CM_Status::RX_BUFFER_EMPTY)
	{
		g_logger.info(TAG, "CAN Recieve buffer empty");
		return;
	}

	switch(rxBuffer.get_id())
	{
		case commandFrame::ID::HYDRAULIC_COMMAND:
			handle_hydraulic_cmds(rxBuffer.get_hCmd());
			break;
		case commandFrame::ID::SENSOR_REQUEST:
			handle_sensor_request(rxBuffer.get_sensor_type());
			break;
		default:
			break;
	}
}

void HCU::handle_hydraulic_cmds(commandFrame::HydraulicCommands hC)
{
    switch(hC)
    {
        case commandFrame::HydraulicCommands::MOVE_UP:
        	can_requested_state = DeviceStates::MOVING_UP;
            break;
        case commandFrame::HydraulicCommands::MOVE_DOWN:
        	can_requested_state = DeviceStates::MOVING_DOWN;
            break;
        case commandFrame::HydraulicCommands::MOVE_HOME:
        	can_requested_state = DeviceStates::MOVING_HOME;
            break;
        case commandFrame::HydraulicCommands::STOP:
        	can_requested_state = DeviceStates::STOPPED;
        	break;
        default:
            break;
    }
}

void HCU::handle_sensor_request(Sensor::Types sT)
{
    switch(sT)
    {
        case Sensor::Types::VSENS:
            break;
        case Sensor::Types::TSENS:
            break;
        case Sensor::Types::ISENS:
            break;
        case Sensor::Types::PSENS:
            break;
        case Sensor::Types::LSENS:
            break;
        default:
            break;
    }
}

void HCU::run(void)
{
    g_logger.info(TAG, "-----------------------------------------------running------------------------------------------------------\r\n");
    process();
}

void HCU::handle_moving_up(void)
{
	
}

void HCU::handle_moving_down(void)
{
	
}

void HCU::handle_moving_home(void)
{
#if 0
	if(check_dumper_in_home_pos())
	{
		curr_device_state = DeviceStates::IN_HOME;	
	}
	else 
	{
		// motor movement	
	}	
#endif
}

void HCU::handle_in_home(void)
{
	
}

void HCU::handle_stopped(void)
{
	
}

