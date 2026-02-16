/*
 * bsp_can.hpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */

#ifndef HAL_CAN_HPP_
#define HAL_CAN_HPP_

#include <cstdint>
#include "logger.hpp"

class hal_CAN
{
    public:
        using Callback = void (*)(void* ctx);
        ~hal_CAN(void) = default;

        static hal_CAN& instance(void)
        {
            static hal_CAN ins;
            return ins;
        }

        void init(void) const
        {
            logger.info(TAG, "Initialized");
        }

        void onRXIntruppt(void) const
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

        void recieve(uint8_t* buffer, size_t size)
        {
            logger.info(TAG, "recieved successfully");
        }

        void send(uint8_t* buffer, size_t size)
        {
            logger.info(TAG, "sent successfully");
        }

    private:
        inline static constexpr char TAG[] = "CANI";
        hal_CAN() = default;
        Callback cb = nullptr;
        void* ctx = nullptr;
};

#if 0
extern "C" void halCANRX(void)
{
	hal_CAN::instance().onRXIntruppt();
}
#endif

#endif /* HAL_CAN_HPP_ */
