/*
 * bsp_log.hpp
 *
 *  Created on: 09-Feb-2026
 *      Author: Sivaraj
 */

#ifndef APP_HAL_ESP32_LOG_HPP_
#define APP_HAL_ESP32_LOG_HPP_

#include <cstdint>
#include "hal_log.hpp"

class bsp_log : public hal_LOG
{
	public:
		bsp_log() = default;
		~bsp_log() = default;
		
		void info(const char* TAG, const char* msg) const;
		void warn(const char* TAG, const char* msg) const;
		void error(const char* TAG, const char* msg) const;
		
	private:
		 
};
 
#endif /* APP_HAL_ESP32_LOG_HPP_ */
