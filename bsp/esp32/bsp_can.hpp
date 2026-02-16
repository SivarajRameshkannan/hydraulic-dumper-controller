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
#include "hal_can.hpp"

class bsp_CAN : public hal_CAN
{
    public:
        using Callback = void (*)(void* ctx);
        bsp_CAN() = default;
        ~bsp_CAN(void) = default;

        void init(void) const
        {
        }

        CAN_status send(uint8_t*, size_t size) const
        {
			return CAN_status::OK;
        }

        CAN_status recv(uint8_t*, size_t size) const
        {
			return CAN_status::OK;
        }

		void enable_intr(void) const
		{
			
		}
		
		void disable_intr(void) const
		{
			
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
