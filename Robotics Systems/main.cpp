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
#include "Sensors.hpp"

Sensor_Stream Sensor1(Sensor_Stream::SENSOR_1);
Sensor_Stream Sensor2(Sensor_Stream::SENSOR_2);
Sensor_Stream Sensor3(Sensor_Stream::SENSOR_3);




//float convert_data(Sensor_Stream::sensorId_t sensor_id, float value, float previous_value = 0);
//float scale_data(Sensor_Stream::sensorId_t sensorid, float value);

//struct values_t
//{
//	float value;
//	float previous_value = 0; // we only use this for sensor 2
//	float temporary_value = 0;
//};
//values_t sensor1;
//values_t sensor2;
//values_t sensor3;

float fused_value;
float motorA;
float motorB;


Logger log_point_A(Logger::LOG_POINT_A, "/Users/robbiewoolterton/Documents/GitHub/Robotics Systems/Robotics Systems/Logs");
Logger log_point_B(Logger::LOG_POINT_B, "/Users/robbiewoolterton/Documents/GitHub/Robotics Systems/Robotics Systems/Logs");

Logger log_point_C(Logger::LOG_POINT_C, "/Users/robbiewoolterton/Documents/GitHub/Robotics Systems/Robotics Systems/Logs");
Logger log_point_D(Logger::LOG_POINT_D, "/Users/robbiewoolterton/Documents/GitHub/Robotics Systems/Robotics Systems/Logs");
Logger log_point_E(Logger::LOG_POINT_E, "/Users/robbiewoolterton/Documents/GitHub/Robotics Systems/Robotics Systems/Logs");
Logger log_point_F(Logger::LOG_POINT_F, "/Users/robbiewoolterton/Documents/GitHub/Robotics Systems/Robotics Systems/Logs");

int main(int argc, const char * argv[])
{
	
	Sensors Sensors(&Sensor1, &Sensor2, &Sensor3);
	
	std::cout << "Hello, World!\n";

	Sensors.get_data();
	
	Sensors.convert_data();
	log_point_A.log_value(Sensors.Sensor1.value);
	log_point_B.log_value(Sensors.Sensor2.value);
	
	Sensors.scale_data();
	log_point_C.log_value(Sensors.Sensor1.value);
	log_point_D.log_value(Sensors.Sensor2.value);
	log_point_E.log_value(Sensors.Sensor3.value);
	
	fused_value = Sensors.fuse_data();
	log_point_F.log_value(fused_value);
	std::cout << Sensors.fuse_data() << "\n";
	
	
//	float fusedSensor;
	
//	bool stream_ok = true;
//	while (stream_ok)
//	{
//		sensor1.value = Sensor1.get_data(&state1);
//		sensor2.value = Sensor2.get_data(&state2);
//		sensor3.value = Sensor3.get_data(&state3);
		
//		switch (state1)
//		{
//			case Sensor_Stream::FLAG_DATA_GOOD: // if the data is good
////				std::cout << "The values of the sensors are \t" << sensor1.value << ",\t";
////				std::cout << sensor2.value << ",\t" << sensor3.value << "\n";
////				sensor1.value = convert_data(Sensor_Stream::SENSOR_1, sensor1.value);
////				Sensor1Log.log_value(sensor1.value);
////				Sensor2Log.log_value(sensor2.value);
////				sensor2.temporary_value = sensor2.value;
////				sensor2.value = convert_data(Sensor_Stream::SENSOR_2, sensor2.value, sensor2.previous_value);
////				sensor2.previous_value = sensor2.temporary_value;
////
////				sensor3.value = convert_data(Sensor_Stream::SENSOR_3, sensor3.value);
//
////				std::cout << "The adjusted values are: \t \t" << sensor1.value << "\t";
////				std::cout << sensor2.value << ",\t" << sensor3.value << "\n";
////				std::cout << "\n";
//
//
////				sensor1.value = scale_data(Sensor_Stream::SENSOR_1, sensor1.value);
////				sensor2.value = scale_data(Sensor_Stream::SENSOR_2, sensor2.value);
////				sensor3.value = scale_data(Sensor_Stream::SENSOR_3, sensor3.value);
////
////				// sensor fusion
////				fusedSensor = ((3*(sensor1.value - sensor3.value)) / sensor2.value) - 3;
////				std::cout << fusedSensor << "\n";
//
//				motorA = fusedSensor;
//				if (motorA > 1)
//				{
//					motorA = 1;
//				}
//				else if (motorA < -1)
//				{
//					motorA = -1;
//				}
//				motorB = -1 * motorA;
//
////				std::cout << motorA << "\t" << motorB << "\n";
//
//				break;
//			case Sensor_Stream::FLAG_DATA_LINE_ERROR: // if we have errors in getting the data
//				std::cout << "Data line error \n";
//				stream_ok = false;
//				break;
//			case Sensor_Stream::FLAG_DATA_FILE_END:
//				std::cout << "Reached end of sensor stream \n";
//				stream_ok = false;
//				break;
//			case Sensor_Stream::FLAG_DATA_FILE_CLOSED:
//				std::cout << "File is closed";
//				stream_ok = false;
//				break;
//		}
//	}
	return 0;

}

//float convert_data(Sensor_Stream::sensorId_t sensor_id, float value, float previous_value)
//{
//	switch (sensor_id)
//	{
//		case Sensor_Stream::SENSOR_1:
//			value = (2.0/3.0) * sqrt(value);
//			break;
//		case Sensor_Stream::SENSOR_2:
//			value = value - previous_value;
//			break;
//		case Sensor_Stream::SENSOR_3:
//			value = value;
//			break;
//	}
//	return value;
//}
//
//float scale_data(Sensor_Stream::sensorId_t sensorid, float value)
//{
//	switch (sensorid) {
//		case Sensor_Stream::SENSOR_1:
//			value = 2.7 * (value - 1);
//			break;
//		case Sensor_Stream::SENSOR_2:
//			value = 0.7 * (value + 0.50);
//			break;
//		case Sensor_Stream::SENSOR_3:
//			value = value - 0.2;
//			break;
//	}
//	return value;
//}
