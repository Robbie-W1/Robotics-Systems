/*************************
 * DO NOT EDIT THIS FILE *
 *************************/
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "Sensor_Stream.h"

Sensor_Stream::Sensor_Stream(sensorId_t sensor_id)
{
    switch (sensor_id)
    {
    case SENSOR_1:
        _mFile.open(_sensor_folder + "/sensor_1.csv", std::ios_base::in);
        break;

    case SENSOR_2:
        _mFile.open(_sensor_folder + "/sensor_2.csv", std::ios_base::in);
        break;

    case SENSOR_3:
        _mFile.open(_sensor_folder + "/sensor_3.csv", std::ios_base::in);
        break;

    default:
        std::cout << "Sensor ID Unknown" << std::endl;
    }

    if (!_mFile.is_open())
    {
        std::cout << "Failed to open file. Is the sensor data in a folder named " << _sensor_folder << "?" << std::endl;
    }
}

Sensor_Stream::~Sensor_Stream()
{
    Sensor_Stream::close_stream();
}

float Sensor_Stream::get_data(flagState_t *pFlag)
{
    *pFlag = FLAG_DATA_GOOD;
    float result = std::nanf("");

    if (_mFile.is_open())
    {
        std::string str;

        if (std::getline(_mFile, str))
        {
            int lineno;
            int n;

            n = std::sscanf(str.c_str(), "%i, %f", &lineno, &result);

            if (n == 2)
                *pFlag = FLAG_DATA_GOOD;
            else
                *pFlag = FLAG_DATA_LINE_ERROR;
        }
        else
            *pFlag = FLAG_DATA_FILE_END;
    }
    else
        *pFlag = FLAG_DATA_FILE_CLOSED;

    return result;
}

void Sensor_Stream::close_stream()
{
    if (_mFile.is_open())
    {
        _mFile.close();
    }
}

// EOF
