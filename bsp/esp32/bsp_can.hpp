/*
 * CAN.hpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */

#ifndef HAL_CAN_HPP_
#define HAL_CAN_HPP_

#include <cstddef>
#include <cstdint>
#include "hal_COM.hpp"
#include "hal_can.hpp"

class bsp_CAN : public hal_CAN
{
    public:        
        bsp_CAN() = default;
        ~bsp_CAN(void) = default;

        void init(void) const override
        {
			// implement init function
        }
		
		void process(void) override
		{
			hal_COM::process();
		}
		
        COM_status send(uint8_t*, size_t size) const override
        {
			return COM_status::OK;
        }

        COM_status recv(uint8_t*, size_t size) const override
        {
			return COM_status::OK;
        }
		
    private:
};

#if 0
extern "C" void halCANRX(void)
{
	hal_CAN::instance().onRXIntruppt();
}
#endif

#endif /* HAL_CAN_HPP_ */
