/*
 * logger.hpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */

#ifndef SERVICES_LOGGER_HPP_
#define SERVICES_LOGGER_HPP_

#include <cstdint>

#include "bsp_log.hpp"
#include "hal_log.hpp"

class logger
{
   public:
      static logger& instance(void)
      {
          static logger logger_instance;
          return logger_instance;
      }
  
	  logger& operator=(const logger&) = delete;
	  logger(const logger&) = delete;      

	 ~logger(void) = default;
	
	void info(const char* TAG, const char* fmt, ...) const;
	void error(const char* TAG, const char* fmt, ...) const;	
	void warn(const char* TAG, const char* fmt, ...) const;
	
   private:
        logger() : log_obj(l){}
        
        bsp_log l;
        const hal_LOG& log_obj;
        static constexpr uint16_t buffer_size = 256U;
};

inline logger& g_logger = logger::instance();

#endif /* SERVICES_LOGGER_HPP_ */
