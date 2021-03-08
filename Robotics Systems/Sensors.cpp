//
//  Sensors.cpp
//  Robotics Systems
//
//  Created by Robbie Woolterton on 01/03/2021.
//  Copyright © 2021 Robbie Woolterton. All rights reserved.
//

#include "Sensors.h"
#include <iostream>


Sensors::Sensors(Sensor_Stream *pSensor1Inject,Sensor_Stream *pSensor2Inject, Sensor_Stream *pSensor3Inject)
{
	std::cout << "Initialising Sensors class \n";
	
	pSensor1 = pSensor1Inject;
	pSensor2 = pSensor2Inject;
	pSensor3 = pSensor3Inject;
};

void Sensors::fetch_data()
{
//	std::cout << "Fetching sensor data \n";
	
	Sensor1.value = pSensor1->get_data(&state1);
	Sensor2.value = pSensor2->get_data(&state2);
	Sensor3.value = pSensor3->get_data(&state3);
	
};

void Sensors::convert_data()
{
//	std::cout << "Converting sensor data \n";
	
	Sensor1.value = (2.0/3.0) * sqrt(Sensor1.value);
	
	Sensor2.temporary_value = Sensor2.value;
	Sensor2.value = Sensor2.value - Sensor2.previous_value;
	Sensor2.previous_value = Sensor2.temporary_value;

	Sensor3.value = Sensor3.value; // sensor 3 does not need to be converted
}

void Sensors::scale_data()
{
//	std::cout << "Scaling sensor data \n";
	
	Sensor1.value = 2.7 * (Sensor1.value - 1.0);
	Sensor2.value = 0.7 * (Sensor2.value + 0.5);
	Sensor3.value = 1.0 * (Sensor3.value - 0.2);
}

// swap to pointer
float Sensors::return_value(Sensor_Stream::sensorId_t sensor_id)
{
	switch (sensor_id) {
		case Sensor_Stream::SENSOR_1:
			return Sensor1.value;
			break;
		case Sensor_Stream::SENSOR_2:
			return Sensor2.value;
			break;
		case Sensor_Stream::SENSOR_3:
			return Sensor3.value;
			break;
		default:
			std::cout << "Invalid sensor ID \n";
			break;
	}
}


float Sensors::fuse_data()
{
//	std::cout << "Returning sensor data \n";
	return ((3.0*(Sensor1.value - Sensor3.value)) / Sensor2.value) - 3.0;
}


void Sensors::get_states(Sensor_Stream::flagState_t *pState1In, Sensor_Stream::flagState_t *pState2In, Sensor_Stream::flagState_t *pState3In)
{
	*pState1In = state1;
	*pState2In = state2;
	*pState3In = state3;
	
	switch (state1)
	{
		case Sensor_Stream::FLAG_DATA_GOOD:
			break;
		case Sensor_Stream::FLAG_DATA_LINE_ERROR:
			std::cout << "Sensor 1 line error \n";
			break;
		case Sensor_Stream::FLAG_DATA_FILE_END:
			std::cout << "Sensor 1 file end reached \n";
			break;
		case Sensor_Stream::FLAG_DATA_FILE_CLOSED:
			std::cout << "Sensor 1 stream not open \n";
			break;
	}
	switch (state2)
	{
		case Sensor_Stream::FLAG_DATA_GOOD:
			break;
		case Sensor_Stream::FLAG_DATA_LINE_ERROR:
			std::cout << "Sensor 2 line error \n";
			break;
		case Sensor_Stream::FLAG_DATA_FILE_END:
			std::cout << "Sensor 2 file end reached \n";
			break;
		case Sensor_Stream::FLAG_DATA_FILE_CLOSED:
			std::cout << "Sensor 2 stream not open \n";
			break;
	}
	switch (state1)
	{
		case Sensor_Stream::FLAG_DATA_GOOD:
			break;
		case Sensor_Stream::FLAG_DATA_LINE_ERROR:
			std::cout << "Sensor 2 line error \n";
			break;
		case Sensor_Stream::FLAG_DATA_FILE_END:
			std::cout << "Sensor 2 file end reached \n";
			break;
		case Sensor_Stream::FLAG_DATA_FILE_CLOSED:
			std::cout << "Sensor 2 stream not open \n";
			break;
	}

}
