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
#include "Sensors.h"

Sensor_Stream Sensor1_Stream(Sensor_Stream::SENSOR_1);
Sensor_Stream Sensor2_Stream(Sensor_Stream::SENSOR_2);
Sensor_Stream Sensor3_Stream(Sensor_Stream::SENSOR_3);

float fused_value;
float motorA;
float motorB;

std::string save_location = "/Users/robbiewoolterton/Documents/GitHub/Robotics Systems/Robotics Systems/Logs";

//Logger log_point_A(Logger::LOG_POINT_A, save_location);
//Logger log_point_B(Logger::LOG_POINT_B, save_location);
//Logger log_point_C(Logger::LOG_POINT_C, save_location);
//Logger log_point_D(Logger::LOG_POINT_D, save_location);
//Logger log_point_E(Logger::LOG_POINT_E, save_location);
Logger log_point_F(Logger::LOG_POINT_F, save_location);
Control_Output motor_output(save_location);

enum Sensor_Stream::flagState_t sensorState1 = Sensor_Stream::FLAG_DATA_GOOD;
enum Sensor_Stream::flagState_t sensorState2 = Sensor_Stream::FLAG_DATA_GOOD;
enum Sensor_Stream::flagState_t sensorState3 = Sensor_Stream::FLAG_DATA_GOOD;

int main(int argc, const char * argv[])
{
	
	Sensors Sensors(&Sensor1_Stream, &Sensor2_Stream, &Sensor3_Stream);
	
	
	while (true)
	{
		if (sensorState1 == 0 && sensorState2 == 0 && sensorState3 == 0)
		{
			
			Sensors.fetch_data();
			
			Sensors.get_states(&sensorState1, & sensorState2, &sensorState3);
//			std::cout << sensorState1 << "\t" << sensorState2 << "\t" << sensorState3 << "\n";
			
			Sensors.convert_data();
	//		log_point_A.log_value(Sensors.return_value(Sensor_Stream::SENSOR_1));
	//		log_point_B.log_value(Sensors.return_value(Sensor_Stream::SENSOR_2));
			
			Sensors.scale_data();
	//		log_point_C.log_value(Sensors.return_value(Sensor_Stream::SENSOR_1));
	//		log_point_D.log_value(Sensors.return_value(Sensor_Stream::SENSOR_2));
	//		log_point_E.log_value(Sensors.return_value(Sensor_Stream::SENSOR_3));
			
			fused_value = Sensors.fuse_data();
			log_point_F.log_value(fused_value);
			
			motorA = fused_value;
			
			// constrain the value of motorA to be between 1 & -1
			if (motorA > 1)
			{
				motorA = 1;
			}
			else if (motorA < -1)
			{
				motorA = -1;
			}
			
			motorB = -1 * motorA; // motorB is the inverse of motorA
			
			motor_output.set_output(motorA, motorB);
		}
		else
		{
			break;
		}
	}
	return 0;
}
