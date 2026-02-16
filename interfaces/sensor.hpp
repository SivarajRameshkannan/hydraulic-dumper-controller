/*
 * sensor.hpp
 *
 *  Created on: Feb 7, 2026
 *      Author: Sivaraj
 */

#ifndef INTERFACES_SENSOR_HPP_
#define INTERFACES_SENSOR_HPP_

class Sensor
{
    public:
		enum class Types : uint8_t
		{
		    VSENS = 0U,
		    TSENS,
		    ISENS,
		    PSENS,
		    LSENS,
		    NONE,
		    COUNT
		};

        virtual void init(void) const = 0;
        virtual int32_t read(void) const = 0;
        virtual float conv(int32_t adc) const = 0;
        virtual ~Sensor(void) = default;
    private:
};

#endif /* INTERFACES_SENSOR_HPP_ */
