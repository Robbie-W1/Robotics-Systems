//
//  Sensors.cpp
//  Robotics Systems
//
//  Created by Robbie Woolterton on 01/03/2021.
//  Copyright © 2021 Robbie Woolterton. All rights reserved.
//

#include "Sensors.hpp"
#include <iostream>
#include <math.h>


Sensors::Sensors(Sensor_Stream *pSensor1Inject,Sensor_Stream *pSensor2Inject, Sensor_Stream *pSensor3Inject)
{
	std::cout << "Initialising Sensors class \n";
	
	pSensor1 = pSensor1Inject;
	pSensor2 = pSensor2Inject;
	pSensor3 = pSensor3Inject;
};

void Sensors::get_data()
{
	std::cout << "Fetching sensor data \n";
	
	Sensor1.value = pSensor1->get_data(&state1);
	Sensor2.value = pSensor2->get_data(&state2);
	Sensor3.value = pSensor3->get_data(&state3);
};

void Sensors::convert_data()
{
	std::cout << "Converting sensor data \n";
	
	Sensor1.value = (2.0/3.0) * sqrt(Sensor1.value);
	
	Sensor2.temporary_value = Sensor2.value - Sensor2.previous_value;
	Sensor2.previous_value = Sensor2.value;
	Sensor2.value = Sensor2.temporary_value;
	
	// sensor 3 does not need to be converted
}

void Sensors::scale_data()
{
	std::cout << "Scaling sensor data \n";
	
	Sensor1.value = 2.7 * (Sensor1.value - 1.0);
	Sensor2.value = 0.7 * (Sensor2.value + 0.5);
	Sensor3.value = 1.0 * (Sensor2.value - 0.2);
}

float Sensors::fuse_data()
{
	return ((3*(Sensor1.value - Sensor3.value)) / Sensor2.value) - 3;
}

