/*
 * bsp_systick.hpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */
 
#ifndef HAL_DELAY_HPP_
#define HAL_DELAY_HPP_

#if __cplusplus
extern "C"
{
#endif

#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "esp_timer.h"

#if __cplusplus	
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
			return;
		}

		uint64_t millis(void) const override
		{
			return esp_timer_get_time() / 1000U; 
		}

		void sleep_ms(uint32_t ms) const override
		{
			vTaskDelay(pdMS_TO_TICKS(ms));
		}

	private:
};



#endif /* HAL_DELAY_HPP_ */
