/*
 * voltage_sensor.hpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */

#ifndef DEVICES_VOLTAGE_SENSOR_HPP_
#define DEVICES_VOLTAGE_SENSOR_HPP_

#include "sensor.hpp"
#include "logger.hpp"
#include <cstdint>

class Vsens : public Sensor
{
    public:
        Vsens(uint8_t vref, uint8_t adc_res) : vref(vref), adc_res(adc_res){}
        ~Vsens(void) = default;

        enum class VSENSErrors : uint8_t
        {
            OUT_OF_RANGE = 0U,
            SENSOR_FAILURE,
            NOMINAL,
            OVER_VOLTAGE,
            UNDER_VOLTAGE,
            COUNT
        };

        void init(void) const override
        {
            g_logger.info(TAG, "Initialized");
        }

        int32_t read(void) const override
        {
            return (1 << adc_res);;
        }

        float conv(int32_t adc) const override
        {
            return (static_cast<float>(adc) / adc_res) * vref;
        }

    private:
        const uint8_t vref;
        const uint8_t adc_res;
        inline static constexpr char TAG[] = "VSENS";
};

#endif /* DEVICES_VOLTAGE_SENSOR_HPP_ */
