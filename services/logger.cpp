/*
 * logger.cpp
 *
 *  Created on: 09-Feb-2026
 *      Author: Sivaraj
 */
 
#include <cstdarg>
#include <cstdio>   // for vsnprintf 
#include <cstdarg>
#include <cstdint>
#include "logger.hpp"

void logger::info(const char* TAG, const char* fmt, ...) const
{
	char buffer[buffer_size];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args); 
	
	log_obj.info(TAG, buffer);       
}

void logger::error(const char* TAG, const char* fmt, ...) const
{
	char buffer[buffer_size];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	
	log_obj.error(TAG, buffer);    
}

void logger::warn(const char* TAG, const char* fmt, ...) const
{
	char buffer[buffer_size];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	
	log_obj.warn(TAG, buffer);		
}

