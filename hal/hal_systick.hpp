/*
 * hal_systick.hpp
 *
 *  Created on: 11-Feb-2026
 *      Author: Sivaraj
 */
#pragma once

#include <cstdint>

class hal_SYSTICK {
public:
    virtual void init(void) = 0;      
    virtual uint64_t millis(void) const = 0;
    virtual void sleep_ms(uint32_t ms) const = 0;
private:
};
