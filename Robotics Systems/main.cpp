//
//  main.cpp
//  Robotics Systems
//
//  Created by Robbie Woolterton on 17/02/2021.
//  Copyright © 2021 Robbie Woolterton. All rights reserved.
//

#include <iostream> // used for outputting to the console

// Open up the other code files
#include "Sensor_Stream.h"
#include "Logger.h"
#include "Control_Output.h"


int main(int argc, const char * argv[])
{
	std::cout << "Hello, World!\n";

//	 making a Sensor_Stream object for Sensor1
	Sensor_Stream Sensor1(Sensor_Stream::SENSOR_1);
	enum Sensor_Stream::flagState_t state1 = Sensor_Stream::FLAG_DATA_GOOD;

	Sensor_Stream Sensor2(Sensor_Stream::SENSOR_2);
	enum Sensor_Stream::flagState_t state2 = Sensor_Stream::FLAG_DATA_GOOD;
	
	Sensor_Stream Sensor3(Sensor_Stream::SENSOR_3);
	enum Sensor_Stream::flagState_t state3 = Sensor_Stream::FLAG_DATA_GOOD;
	
	bool streamOk = true;
	while (streamOk)
	{
		float x = Sensor1.get_data(&state1);
		float y = Sensor2.get_data(&state2);
		float z = Sensor3.get_data(&state3);
		switch (state1)
		{
			case Sensor_Stream::FLAG_DATA_GOOD:
				std::cout << "The values of the sensors are " << x << ",\t" << y << ",\t" << z << "\n";
				break;
			case 1:
				std::cout << "Data line error \n";
				streamOk = false;
				break;
			case Sensor_Stream::FLAG_DATA_FILE_END:
				std::cout << "Reached end of data stream \n";
				streamOk = false;
				break;
			case Sensor_Stream::FLAG_DATA_FILE_CLOSED:
				std::cout << "File is closed";
				streamOk = false;
				break;
		}
		
		
	}
	
	// add a switch case statement for each sensor stream based off the flag
	
	// add function for conversion and scaling taking both sensor number and value as input
	

	return 0;
}
