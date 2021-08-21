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
	
	bool success; // for storing whether or not the logging was successfull
	
	/**
	 * Converts the digit of the logType_t enum to a string to describe the enum, ie 0 -> log A
	 * Used when outputting an error message in the log method
	 * @param input - logType_t enum
	 *
	 * @returns string to describe which logger we are using
	*/
	std::string logEnumToString(Logger::logType_t input);
	
public:

	/**
	 * Constructor for Loggers class, takes pointers to all of the Logger and Control_Output class instances already created
	 *
	 * @param pLogAInject pointer to the instance of the looger class used for point A
	 * @param pLogBInject pointer to the instance of the looger class used for point B
	 * @param pLogCInject pointer to the instance of the looger class used for point C
	 * @param pLogDInject pointer to the instance of the looger class used for point D
	 * @param pLogEInject pointer to the instance of the looger class used for point E
	 * @param pLogFInject pointer to the instance of the looger class used for point F
	 * @param pMotorOutputInject pointer to the instance of the Control_Output class used for logging the motor outputs
	 */
	Loggers(Logger *pLogAInject, Logger *pLogBInject, Logger *pLogCInject, Logger *pLogDInject, Logger *pLogEInject, Logger *pLogFInject, Control_Output *pMotorOutputInject);
	
	/**
	 * Logs the data to the respective log file
	 *
	 * @param dataIn value of the data you want to log (float)
	 * @param log_id logType_t enum, for specifying which log file you want to log to
	 *
	 * @return tells you whether the data was successfully logged. Returns true if it was, false if there was an error
	 */
	bool log(float dataIn, Logger::logType_t log_id);
	
	/**
	 * Logs the motor output to the control output log
	 * Note, the method does not check which log you are using, since them motor log is the only one which logs two data points at once
	 *
	 * @param dataIn1 the float value for motor A
	 * @param dataIn2 the float value for motor B
	 *
	 * @return tells you whether the data was successfully logged. Returns true if it was, false if there was an error
	 */
	bool log(float dataIn1, float dataIn2);

};

#endif /* Loggers_h */
