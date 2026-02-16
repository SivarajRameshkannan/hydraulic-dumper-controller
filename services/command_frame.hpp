/*
 * command_frame.hpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */
#pragma once

#include <cstdint>
#include <cstddef>
#include <array>

#include "sensor.hpp"
#include "logger.hpp"

class commandFrame
{
    public:    	
        commandFrame() = default;
        ~commandFrame() = default;

        enum class ID : uint8_t
        {
            HYDRAULIC_COMMAND = 0U,
            SENSOR_REQUEST,
            INVALID,
            COUNT
        };

        enum HydraulicCommands : uint8_t
        {
            MOVE_UP = 0U,
            MOVE_DOWN,
            MOVE_HOME,
            INVALID,
            COUNT
        };

        enum class Frame : uint8_t
        {
            ID = 0U,
            HCMD_SENSOR_RQ,
            RESERVED_1,
            RESERVED_2,
            RESERVED_3,
            RESERVED_4,
            RESERVED_5,
            RESERVED_6,
            COUNT
        };

    	using frame_type = std::array<uint8_t, static_cast<size_t>(Frame::COUNT)>;

        ID get_id(void) const
        {
			size_t idx = static_cast<size_t>(Frame::ID);
			uint8_t val = buffer[idx];
			
            if(!checkValidID(val))
            {
                return ID::INVALID;
            }
            else
            {
                return static_cast<ID>(val);
            }
        }

        HydraulicCommands get_hCmd(void) const
        {
			size_t idx = static_cast<size_t>(Frame::HCMD_SENSOR_RQ);
			uint8_t val = buffer[idx];
			
            if(!check_valid_hC(val))
            {
                return HydraulicCommands::INVALID;
            }
            else
            {
                return static_cast<HydraulicCommands>(val);
            }
        }

        Sensor::Types get_sensor_type(void) const
        {
			size_t idx = static_cast<size_t>(Frame::HCMD_SENSOR_RQ);
			uint8_t val = buffer[idx];
			
            if(!check_valid_sT(val))
            {
                return Sensor::Types::NONE;
            }
            else
            {
                return static_cast<Sensor::Types>(val);
            }
        }

        frame_type& get_buffer_addr(void)
        {
            return buffer;
        }

    private:
        inline static constexpr char TAG[] = "CMD_HANDLE";

		frame_type buffer{};
		
/*        struct frameBuffer
        {
            uint8_t buffer[static_cast<size_t>(Frame::COUNT)];
            
		    // Read-only access (for const functions)
		    const uint8_t& operator[](Frame f) const
		    {
		        return buffer[static_cast<size_t>(f)];
		    }
            // Writable access (used in ISR / non-const context)
            uint8_t& operator[](Frame f)
            {
                return buffer[static_cast<size_t>(f)];
            }

            frameBuffer() : buffer{0x00}{}
        };

        frameBuffer frame;
*/

        bool checkValidID(uint8_t& id) const
        {
            uint8_t max_ids = static_cast<uint8_t>(ID::COUNT);
            if(id >= max_ids)
            {
                g_logger.error(TAG, "NOT A VALID ID");
                return false;
            }

            return true;
        }

        bool check_valid_hC(uint8_t& Command) const
        {
            uint8_t max_HC = static_cast<uint8_t>(HydraulicCommands::COUNT);
            if(Command >= max_HC)
            {
                g_logger.error(TAG, "NOT A VALID ID");
                return false;
            }

            return true;
        }

        bool check_valid_sT(uint8_t& sT) const
        {
            uint8_t max_sT = static_cast<uint8_t>(Sensor::Types::COUNT);
            if(sT >= max_sT)
            {
                g_logger.error(TAG, "NOT A VALID ID");
                return false;
            }

            return true;
        }
};




