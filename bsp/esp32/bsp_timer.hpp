/*
 * bsp_timer.hpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */

#ifndef HAL_TIMER_HPP_
#define HAL_TIMER_HPP_

#include "logger.hpp"

class hal_timer
{
    public:
        using Callback = void (*)(void* ctx);

        static hal_timer& instance(void)
        {
            static hal_timer timer_instance;
            return timer_instance;
        }

        void init(uint8_t trigger_every)
        {
        }

        void timerISR(void) const
        {
            if(cb)
            {
                cb(ctx);
            }
        }

        void register_cb(Callback cb, void* ctx)
        {
            this->cb = cb;
            this->ctx = ctx;
        }

        void unregister_cb(void)
        {
            this->cb = nullptr;
            this->ctx = nullptr;
        }

        void start(void) const
        {
        }

        void stop(void) const
        {
        }

        void reload(void) const
        {
        }

        ~hal_timer(void) = default;

    private:
        inline static constexpr char TAG[] = "Timer";
        hal_timer() = default;
        Callback cb;
        void* ctx;
};

#if 0
extern "C" void timerIntruppt(void)
{
    hal_timer::instance().timerISR();
}
#endif

#endif /* HAL_TIMER_HPP_ */
