/*
 * hal_can.hpp
 *
 *  Created on: 11-Feb-2026
 *      Author: Sivaraj
 */

#ifndef APP_HAL_HAL_CAN_HPP_
#define APP_HAL_HAL_CAN_HPP_

#include "hal_COM.hpp"
#include <cstdint>
#include <cstddef>

class hal_CAN : public hal_COM
{
	public:		        	
		hal_CAN() = default;
		virtual ~hal_CAN() = default;
	
	private:	
};



#endif /* APP_HAL_HAL_CAN_HPP_ */
