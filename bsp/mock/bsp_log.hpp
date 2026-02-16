/*
 * bsp_log.hpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */
#pragma once

#include "hal_log.hpp"
#include <iostream>

class bsp_log : public hal_LOG
{
    public:
        bsp_log() = default;
        ~bsp_log() = default;

		void info(const char* TAG, const char* msg) const override
        {
            std::cout << "[" << "info" << "] " << TAG << ": " << msg << std::endl;
        } 

		void warn(const char* TAG, const char* msg) const override
        {
            std::cout << "[" << "warn" << "] " << TAG << ": " << msg << std::endl;
        };

		void error(const char* TAG, const char* msg) const override
        {
            std::cout << "[" << "error" << "] " << TAG << ": " << msg << std::endl;
        };

    private:
};
