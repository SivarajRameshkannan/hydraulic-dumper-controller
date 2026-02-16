/*
 * hal_intr.hpp
 *
 *  Created on: 11-Feb-2026
 *      Author: Sivaraj
 */
#pragma once

class hal_Intruppt {
public:
    using callback = void (*)(void*);
    
    hal_Intruppt() : _cb(nullptr), _ctx(nullptr){}
  
    virtual ~hal_Intruppt(void) = default;
    virtual void register_intr_cb(callback cb, void* ctx)
    {
		this->_cb = cb;
		this->_ctx = ctx;
	};
	
    // Called when the interrupt triggers
    virtual void _onInterrupt(void)
    {
		if(this->_cb)
		{
			this->_cb(this->_ctx);
		}
	};

    // Optional: enable or disable the interrupt
    virtual void enable_intr(void) const = 0;
    virtual void disable_intr(void) const = 0;
    
private:
	callback _cb;
	void* _ctx;
};
