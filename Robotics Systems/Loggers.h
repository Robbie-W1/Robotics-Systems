//
//  Loggers.h
//  Robotics Systems
//
//  Created by Robbie Woolterton on 31/03/2021.
//  Custom class to handle all data logging and motor outputs
//

#ifndef Loggers_h
#define Loggers_h

#include <stdio.h>
#include "Logger.h"
#include "Control_Output.h"


class Loggers
{
private:
	Logger *plogPointA;
	Logger *plogPointB;
	Logger *plogPointC;
	Logger *plogPointD;
	Logger *plogPointE;
	Logger *plogPointF;
	
	Control_Output *pMotorOutput;
	
	bool success;
	
	std::string logEnumToString(Logger::logType_t input);
	
public:
	// constructor, takes pointers to all objects of the classes
	Loggers(Logger *pLogAInject, Logger *pLogBInject, Logger *pLogCInject, Logger *pLogDInject, Logger *pLogEInject, Logger *pLogFInject, Control_Output *pMotorOutputInject);
	
	// for logging to the log a,b,c,d,e,f files
	bool log(float dataIn, Logger::logType_t log_id);
	
	// for logging to the motor ouput (we know its the motor if there are two data points) 
	bool log(float dataIn1, float dataIn2);



};
#endif /* Loggers_hpp */


// add method for logging to files
// running = 'method name'
// add code to print what the error was if one occured

