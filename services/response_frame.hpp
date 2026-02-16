/*
 * response_frame.hpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */

#ifndef SERVICES_RESPONSE_FRAME_HPP_
#define SERVICES_RESPONSE_FRAME_HPP_

#include <cstdint>
#include "voltage_sensor.hpp"

class Responseframe
{
    public:
        Responseframe()
        {
            set_hydraulic_state(HydraulicStates::MOVING_UP);
            set_sensor_type(Sensor::Types::NONE);
            set_sensor_data(0.0f);
            set_error_code(static_cast<uint8_t>(Vsens::VSENSErrors::NOMINAL));
        };

        ~Responseframe() = default;


		enum class HydraulicStates : uint8_t
		{
			MOVING_UP = 0U,
			MOVING_DOWN,
			MOVING_HOME,
			IN_HOME,
			STOPPED,
			COUNT
		};


        void set_hydraulic_state(HydraulicStates hState)
        {
            frame[frameBytes::HYDRAULIC_STATE] = static_cast<uint8_t>(hState);
        }

        void set_sensor_type(Sensor::Types sType)
        {
            frame[frameBytes::SENSOR_TYPE] = static_cast<uint8_t>(sType);
        }

        void set_sensor_data(float data)
        {
            data *= sensor_data_prec;
            uint16_t d = static_cast<uint16_t>(data);
            frame[frameBytes::SENSOR_DATA_MSB] = (d >> 8) & 0xff;
            frame[frameBytes::SENSOR_DATA_LSB] = (d & 0xff);
        }

        void set_error_code(uint8_t errorCode)
        {
            frame[frameBytes::ERROR_CODE] = static_cast<uint8_t>(errorCode);
        }

        const uint8_t* get_frame(void) const
        {
            return frame.get_arr();
        }

    private:
        enum class frameBytes : uint8_t
        {
            HYDRAULIC_STATE = 0U,
            SENSOR_TYPE,
            SENSOR_DATA_LSB,
            SENSOR_DATA_MSB,
            ERROR_CODE,
            RESERVED_1,
            RESERVED_2,
            RESERVED_3,
            COUNT
        };

        struct frameStruct
        {
            uint8_t data[static_cast<size_t>(frameBytes::COUNT)];

            uint8_t& operator[](frameBytes f)
            {
                return data[static_cast<size_t>(f)];
            }

            const uint8_t* get_arr(void) const
            {
                return data;
            }

            frameStruct() : data{0x00} {}
        };

        frameStruct frame;
        inline static constexpr char TAG[] = "ResponseframeHandler";
        inline static constexpr uint8_t sensor_data_prec = 100U;
};

#endif /* SERVICES_RESPONSE_FRAME_HPP_ */
