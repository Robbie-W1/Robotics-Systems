//
//  Sensors.cpp
//  Robotics Systems
//
//  Created by Robbie Woolterton on 01/03/2021.
//  Copyright © 2021 Robbie Woolterton. All rights reserved.
//

#include "Sensors.hpp"
#include <iostream>


Sensors::Sensors(Sensor_Stream *pSensor1Inject,Sensor_Stream *pSensor2Inject, Sensor_Stream *pSensor3Inject)
{
	pSensor1 = pSensor1Inject;
	pSensor2 = pSensor2Inject;
	pSensor3 = pSensor3Inject;


	std::cout << "Initialising Sensors class \n";
};

void Sensors::get_data()
{
	Sensor1.value = pSensor1->get_data(&state1);
	Sensor2.value = pSensor2->get_data(&state2);
	Sensor3.value = pSensor3->get_data(&state3);
};
