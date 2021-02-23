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
	
	enum Sensor_Stream::flagState_t state = Sensor_Stream::FLAG_DATA_GOOD;
//	std::cout << "State is " << state << "\n";

	float x = Sensor1.get_data(&state);
	std::cout << "The value is " << x << "\n";
	
	
//	//	 testing pointers
//	int foo = 10; // foo is the value
//	int *pFoo;
//	pFoo = &foo; // pFoo is the pointer to foo at address pFoo
//
//	std::cout << "The value of foo is: " << *pFoo << " at address: " << pFoo << "\n";

	return 0;
}
