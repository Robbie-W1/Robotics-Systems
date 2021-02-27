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

float convert_data(Sensor_Stream::sensorId_t sensor_id, float value, float previous_value = 0);
float scale_data(Sensor_Stream::sensorId_t sensorid, float value);

struct values_t
{
	float value;
	float previous_value = 0; // we only use this for sensor 2
	float temporary_value = 0;
};
values_t sensor1;
values_t sensor2;
values_t sensor3;

float motorA;
float motorB;

// try making objects outside of main

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

	sensor1.value = Sensor1.get_data(&state1);
	sensor2.value = Sensor2.get_data(&state2);
	sensor3.value = Sensor3.get_data(&state3);
	float fusedSensor;
	
	bool stream_ok = true;
	while (stream_ok)
	{
		sensor1.value = Sensor1.get_data(&state1);
		sensor2.value = Sensor2.get_data(&state2);
		sensor3.value = Sensor3.get_data(&state3);
		
		switch (state1)
		{
			case Sensor_Stream::FLAG_DATA_GOOD: // if the data is good
//				std::cout << "The values of the sensors are \t" << sensor1.value << ",\t";
//				std::cout << sensor2.value << ",\t" << sensor3.value << "\n";
				sensor1.value = convert_data(Sensor_Stream::SENSOR_1, sensor1.value);
				
				sensor2.temporary_value = sensor2.value;
				sensor2.value = convert_data(Sensor_Stream::SENSOR_2, sensor2.value, sensor2.previous_value);
				sensor2.previous_value = sensor2.temporary_value;
				
				sensor3.value = convert_data(Sensor_Stream::SENSOR_3, sensor3.value);
				
//				std::cout << "The adjusted values are: \t \t" << sensor1.value << "\t";
//				std::cout << sensor2.value << ",\t" << sensor3.value << "\n";
//				std::cout << "\n";
				
				
				sensor1.value = scale_data(Sensor_Stream::SENSOR_1, sensor1.value);
				sensor2.value = scale_data(Sensor_Stream::SENSOR_2, sensor2.value);
				sensor3.value = scale_data(Sensor_Stream::SENSOR_3, sensor3.value);

				// sensor fusion
				fusedSensor = ((3*(sensor1.value - sensor3.value)) / sensor2.value) - 3;
//				std::cout << fusedSensor << "\n";
				
				motorA = fusedSensor;
				
				if (motorA > 1)
				{
					motorA = 1;
				}
				else if (motorA < -1)
				{
					motorA = -1;
				}
				
				motorB = -1 * motorA;
				
				std::cout << motorA << "\t" << motorB << "\n";
				
				break;
			case Sensor_Stream::FLAG_DATA_LINE_ERROR: // if we have errors in getting the data
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
	return 0;
}

float convert_data(Sensor_Stream::sensorId_t sensor_id, float value, float previous_value)
{
	switch (sensor_id)
	{
		case Sensor_Stream::SENSOR_1:
			value = (2.0/3.0) * sqrt(value);
			break;
		case Sensor_Stream::SENSOR_2:
			value = value - previous_value;
			break;
		case Sensor_Stream::SENSOR_3:
			value = value;
			break;
	}
	return value;
}

float scale_data(Sensor_Stream::sensorId_t sensorid, float value)
{
	switch (sensorid) {
		case Sensor_Stream::SENSOR_1:
			value = 2.7 * (value - 1);
			break;
		case Sensor_Stream::SENSOR_2:
			value = 0.7 * (value + 0.50);
			break;
		case Sensor_Stream::SENSOR_3:
			value = value - 0.2;
			break;
	}
	return value;
}
