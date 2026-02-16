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
	limit_sw_home.init();
	CM.init();
	
	systick.delay_ms(100);
	
	if(!check_dumper_home_pos())
	{
		curr_device_state = DeviceStates::MOVING_HOME;
	}
	
	g_logger.info(TAG, "initialized");
}

void HCU::process(void)
{
	btn_up.process();
	btn_down.process();
	limit_sw_home.process();
	CM.process();
	
	handle_message();
	handle_button_up();
	handle_button_down();
	handle_device_states();
	
	systick.delay_ms(100);
}

void HCU::handle_device_states(void)
{
	switch(curr_device_state)
	{
		case DeviceStates::MOVING_UP:
			break;
		case DeviceStates::MOVING_DOWN:
			break;
		case DeviceStates::MOVING_HOME:
			break;
		case DeviceStates::IN_HOME:
			break;
		case DeviceStates::STOPPED:
			break;
		default:
			break;
	}
}

void HCU::handle_button_up(void)
{
	button::btn_States state = btn_up.read_state();
	
	if(curr_device_state == DeviceStates::MOVING_HOME)
	{
		return;
	} 
	
	switch(state)
	{
		case button::btn_States::PRESSED:
			curr_device_state = DeviceStates::MOVING_UP;
			break;
		case button::btn_States::RELEASED:
			break;
		case button::btn_States::LONG_PRESS:
			break;
		default:
			break;
	}
}

void HCU::handle_button_down(void)
{
	button::btn_States state = btn_down.read_state();

	if(curr_device_state == DeviceStates::MOVING_HOME)
	{
		return;
	} 

	switch(state)
	{
		case button::btn_States::PRESSED:
			curr_device_state = DeviceStates::MOVING_DOWN;
			break;
		case button::btn_States::RELEASED:
			break;
		case button::btn_States::LONG_PRESS:
			break;
		default:
			break;
	}
}

void HCU::handle_message(void)
{ 
	if(CM.read_msg(rxBuffer.get_buffer_addr()) != CM_Status::RX_BUFFER_EMPTY)
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
	if(curr_device_state == DeviceStates::MOVING_HOME)
	{
		return;
	}

    switch(hC)
    {
        case commandFrame::HydraulicCommands::MOVE_UP:
        	curr_device_state = DeviceStates::MOVING_UP;
            break;
        case commandFrame::HydraulicCommands::MOVE_DOWN:
        	curr_device_state = DeviceStates::MOVING_DOWN;
            break;
        case commandFrame::HydraulicCommands::MOVE_HOME:
        	curr_device_state = DeviceStates::MOVING_HOME;
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