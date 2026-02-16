/*
 * hal_can.hpp
 *
 *  Created on: 11-Feb-2026
 *      Author: Sivaraj
 */

#ifndef APP_HAL_HAL_CAN_HPP_
#define APP_HAL_HAL_CAN_HPP_

#include "hal_Intr.hpp"
#include <cstdint>
#include <cstddef>

class hal_CAN : public hal_Intruppt
{
	public:
		enum class CAN_status : uint8_t
		{
			OK = 0,
			FAILURE,
			MAX_STATUS
		};
		
		hal_CAN() = default;
		virtual ~hal_CAN() = default;

        virtual void init(void) const = 0;
        virtual CAN_status send(uint8_t*, size_t size) const = 0;
        virtual CAN_status recv(uint8_t*, size_t size) const = 0;
	private:	
};



#endif /* APP_HAL_HAL_CAN_HPP_ */
