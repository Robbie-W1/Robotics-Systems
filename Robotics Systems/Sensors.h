//
//  Sensors.h
//  Robotics Systems
//
//  Created by Robbie Woolterton on 01/03/2021.
//  Copyright © 2021 Robbie Woolterton. All rights reserved.
//
//  Custom class which inherits from the Sensor_Stream class given to us.
// The methods and variables in this class allow all necessary data collection, conversion, scaling, and fusing for the sensors
//

#ifndef Sensors_h
#define Sensors_h

#include <stdio.h>
#include <math.h>
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
	
	struct values_t // stores the values of each sensors
	{
		float value;
		float previous_value = -1;
		float temporary_value = 0;
	};

	values_t Sensor1;
	values_t Sensor2;
	values_t Sensor3;
	
public:
	// constructor, takes pointers to the 3 Sensor_Stream objects for each sensor
	Sensors(Sensor_Stream *pSensor1Inject, Sensor_Stream *pSensor2Inject, Sensor_Stream *pSensor3Inject);
	void fetch_data(); // gets the daa from the 3 streams
	void convert_data(); // converts the data using the given formulae
	void scale_data(); // scales the data using the given formulae
	float return_value(Sensor_Stream::sensorId_t sensor_id); // returns the value of the inputted sensor
	float fuse_data(); // runs the sensor fusion formula and outputs this value
	void get_states(Sensor_Stream::flagState_t *pState1In, Sensor_Stream::flagState_t *pState2In, Sensor_Stream::flagState_t *pState3In); // gets the states of each sensor stream, using pointers. The states are private, to stop them being changed accidentally
};

#endif /* Sensors_hpp */




