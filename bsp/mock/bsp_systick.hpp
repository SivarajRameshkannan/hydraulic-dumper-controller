/*
 * bsp_systick.hpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */

#ifndef HAL_DELAY_HPP_
#define HAL_DELAY_HPP_

#ifdef __cplusplus
extern "C" {
#endif

#include <windows.h>

#ifdef __cplusplus
}
#endif

#include "hal_systick.hpp"
#include <cstdint>

class bsp_SYSTICK : public hal_SYSTICK
{
	public:
		bsp_SYSTICK() = default;
		~bsp_SYSTICK() = default;

		void init(void) 
		{

		}

		uint32_t millis(void) const override
		{
			return static_cast<uint32_t>(GetTickCount());
		}

		void sleep_ms(uint32_t ms) const override
		{
			Sleep(ms);
		}

	private:
};



#endif /* HAL_DELAY_HPP_ */
