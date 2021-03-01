//
//  Sensors.h
//  
//
//  Created by Robbie Woolterton on 01/03/2021.
//

#ifndef Sensors_h
#define Sensors_h

#include <stdio.h>
#include "Sensor_Stream.h"

#endif /* Sensors_hpp */

class Sensors
{
private:
	Sensor_Stream *pSensor1;
	Sensor_Stream *pSensor2;
	Sensor_Stream *pSensor3;
	
public:
	Sensors(Sensor_Stream *pSensor1Inject,Sensor_Stream *pSensor2Inject, Sensor_Stream *pSensor3Inject);
	
	void get_data();
	
};
