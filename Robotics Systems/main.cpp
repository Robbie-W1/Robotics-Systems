//
//  main.cpp
//  Robotics Systems
//
//  Created by Robbie Woolterton on 17/02/2021.
//  Copyright © 2021 Robbie Woolterton. All rights reserved.
//

#include <iostream> // used for outputting to the console
#include <math.h>

// Open up the other code files
#include "Sensor_Stream.h"
#include "Logger.h"
#include "Control_Output.h"

float convert_data(Sensor_Stream::sensorId_t sensor_id, float value);

int main(int argc, const char * argv[])
{
	std::cout << "Hello, World!\n";

	//	making Sensor_Stream objects
	Sensor_Stream Sensor1(Sensor_Stream::SENSOR_1);
	enum Sensor_Stream::flagState_t state1 = Sensor_Stream::FLAG_DATA_GOOD;

	Sensor_Stream Sensor2(Sensor_Stream::SENSOR_2);
	enum Sensor_Stream::flagState_t state2 = Sensor_Stream::FLAG_DATA_GOOD;
	
	Sensor_Stream Sensor3(Sensor_Stream::SENSOR_3);
	enum Sensor_Stream::flagState_t state3 = Sensor_Stream::FLAG_DATA_GOOD;

	float x = Sensor1.get_data(&state1);
	float y = Sensor2.get_data(&state2);
	float z = Sensor3.get_data(&state3);

//	std::cout << conver_data(Sensor_Stream::SENSOR_1, 33333) << "\n";
	
	bool stream_ok = true;
	while (stream_ok)
	{
		x = Sensor1.get_data(&state1);
		y = Sensor2.get_data(&state2);
		z = Sensor3.get_data(&state3);
		switch (state1)
		{
			case Sensor_Stream::FLAG_DATA_GOOD: // if the data is good
				std::cout << "The values of the sensors are " << x << ",\t" << y << ",\t" << z << "\n";
				x = convert_data(Sensor_Stream::SENSOR_1, x);
				break;
			// if we have errors in getting the data
			case Sensor_Stream::FLAG_DATA_LINE_ERROR:
				std::cout << "Data line error \n";
				stream_ok = false;
				break;
			case Sensor_Stream::FLAG_DATA_FILE_END:
				std::cout << "Reached end of sensor stream \n";
				stream_ok = false;
				break;
			case Sensor_Stream::FLAG_DATA_FILE_CLOSED:
				std::cout << "File is closed";
				stream_ok = false;
				break;
		}
	}
	
	// add function for conversion and scaling taking both sensor number and value as input
	
	return 0;
}

float convert_data(Sensor_Stream::sensorId_t sensor_id, float value)
{
	switch (sensor_id)
	{
		case Sensor_Stream::SENSOR_1:
			value = (2/3.0) * sqrt(value);
			std::cout << "The adjusted value for sensor 1 is: " << value << "\n";
			break;
		case Sensor_Stream::SENSOR_2:

			break;
		case Sensor_Stream::SENSOR_3:
			
			break;
	}
	return value;
}
