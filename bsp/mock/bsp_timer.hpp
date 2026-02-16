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
//            std::string msg = "trigger every ";
//           msg += std::to_string(trigger_every);
//           msg += "ms";

            logger.info(TAG, "trigger every");
            logger.info(TAG, "Initialized");
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
           logger.info(TAG, "started");
        }

        void stop(void) const
        {
            logger.info(TAG, "stopped");
        }

        void reload(void) const
        {
            logger.info(TAG, "reloading successfull");
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
