//
//  main.cpp
//  Robotics Systems
//
//  Created by Robbie Woolterton on 17/02/2021.
//  Copyright © 2021 Robbie Woolterton. All rights reserved.
//

#include <iostream> // used for outputting to the console
#include "Sensor_Stream.h" // gives us access to the classes declared in other files
#include "Logger.h"
#include "Control_Output.h"



int main(int argc, const char * argv[])
{
	std::cout << "Hello, World!\n";
	
	
	
	Sensor_Stream Sensor1(Sensor_Stream::SENSOR_2);

	

	
	return 0;
}
