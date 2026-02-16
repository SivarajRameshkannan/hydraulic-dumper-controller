/*
 * hal_log.hpp
 *
 *  Created on: 11-Feb-2026
 *      Author: Sivaraj
 */

#ifndef APP_HAL_HAL_LOG_HPP_
#define APP_HAL_HAL_LOG_HPP_

class hal_LOG
{
	public:
		hal_LOG() = default;
		virtual ~hal_LOG() = default;
		
		virtual void info(const char* TAG, const char* msg) const = 0;
		virtual void warn(const char* TAG, const char* msg) const = 0;
		virtual void error(const char* TAG, const char* msg) const = 0;
	private:
};


#endif /* APP_HAL_HAL_LOG_HPP_ */
