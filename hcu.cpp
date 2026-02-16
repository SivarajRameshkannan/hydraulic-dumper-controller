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
	g_logger.info(TAG, "initialized");
}

void HCU::process(void)
{
	can_rx_led.toggle();	
	systick.delay_ms(300);
}

void HCU::handle_hydraulic_cmds(commandFrame::HydraulicCommands hC)
{
    switch(hC)
    {
        case commandFrame::HydraulicCommands::MOVE_UP:
            break;
        case commandFrame::HydraulicCommands::MOVE_DOWN:
            break;
        case commandFrame::HydraulicCommands::MOVE_HOME:
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