//
//  Sensors.hpp
//  Robotics Systems
//
//  Created by Robbie Woolterton on 01/03/2021.
//  Copyright © 2021 Robbie Woolterton. All rights reserved.
//

#ifndef Sensors_hpp
#define Sensors_hpp

#include <stdio.h>
#include "Sensor_Stream.h"

class Sensors
{
private:
	Sensor_Stream *pSensor1;
	Sensor_Stream *pSensor2;
	Sensor_Stream *pSensor3;
	
	enum Sensor_Stream::flagState_t state1 = Sensor_Stream::FLAG_DATA_GOOD;
	enum Sensor_Stream::flagState_t state2 = Sensor_Stream::FLAG_DATA_GOOD;
	enum Sensor_Stream::flagState_t state3 = Sensor_Stream::FLAG_DATA_GOOD;
	struct values_t
	{
		float value;
		float previous_value;
		float temporary_value;
	};

	
public:
	Sensors(Sensor_Stream *pSensor1Inject,Sensor_Stream *pSensor2Inject, Sensor_Stream *pSensor3Inject);
	void get_data();
	
	values_t Sensor1;
	values_t Sensor2;
	values_t Sensor3;
};

	


#endif /* Sensors_hpp */




